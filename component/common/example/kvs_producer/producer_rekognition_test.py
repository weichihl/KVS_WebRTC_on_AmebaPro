import boto3
import numpy as np
import cv2
import threading
import botocore
import json
import sys
import time
import base64
import ast

#set steam information
AWSroleArn = 'arn:aws:iam::XXXXXXXXXXX:role/Rekognition-producer'   
KinesisVideoStreamArn = 'arn:aws:kinesisvideo:us-east-1:XXXXXXXXXXX:stream/my-kvs-stream/XXXXXXXXXXX'
KinesisVideoStream_name = 'my-kvs-stream'
KinesisDataStreamArn = 'arn:aws:kinesis:us-east-1:XXXXXXXXXXX:stream/AmazonRekogntionResults'
KinesisDataStream_name = 'AmazonRekogntionResults'
Rekognition_stream_processor_name = 'my-stream-processor'

face_result_list = []
    
def get_kvs_url():
    kvs = boto3.client('kinesisvideo')
    
    # Grab the endpoint from GetDataEndpoint
    endpoint = kvs.get_data_endpoint(
        StreamName = KinesisVideoStream_name,
        APIName = 'GET_HLS_STREAMING_SESSION_URL'
    )['DataEndpoint']
    
    print("[KVS] End point: ", endpoint)
    
    # Grab the HLS Stream URL from the endpoint
    kvam = boto3.client('kinesis-video-archived-media', endpoint_url=endpoint)
    url = ""
    while (not url):
        try:
            url = kvam.get_hls_streaming_session_url(
                StreamName = KinesisVideoStream_name,
                PlaybackMode = "LIVE",
                HLSFragmentSelector = {
                    'FragmentSelectorType': 'PRODUCER_TIMESTAMP'
                },
                ContainerFormat = 'MPEG_TS',  # FRAGMENTED_MP4
                DiscontinuityMode='ALWAYS',
                DisplayFragmentTimestamp = 'NEVER'
            )['HLSStreamingSessionURL']
        except kvam.exceptions.ResourceNotFoundException:
            print("Waiting for the streaming start...")
            time.sleep(2)
            continue
    
    print("[KVS] HLS Streaming URL: ", url)
    
    return url
    
# Use multi-thread to capture the video frame from URL
class KVS_Capture:
    def __init__(self, URL):
        self.Frame = []
        self.FrameList = []
        self.status = False
        self.isstop = False
        self.video_count = 0
        # kvs video URL connection
        self.capture = cv2.VideoCapture(URL)
        self.capture.set(cv2.CAP_PROP_BUFFERSIZE, 2)
        self.frame_width = self.capture.get(cv2.CAP_PROP_FRAME_WIDTH)
        self.frame_height = self.capture.get(cv2.CAP_PROP_FRAME_HEIGHT)

    def start(self):
	# start the video thread, daemon=True means the thread will stop while main thread stop
        print('KVS_Capture thread started!')
        threading.Thread(target=self.queryframe, daemon=True, args=()).start()

    def stop(self):
	# stop the infinity loop
        self.isstop = True
        print('KVS_Capture thread stopped!')
   
    def getframe(self):
	# return the image if required
        return self.Frame
        
    def queryframe(self):
        while (not self.isstop):
            self.status, self.Frame = self.capture.read()
            # print("FrameList length: %d ", len(self.FrameList))
            while len(self.FrameList)>30:
                self.FrameList.pop(0)
            self.FrameList.append(self.Frame)
            self.video_count += 1
            # print(self.video_count)
        
        self.capture.release()
        
    def displayframe(self):
        while True:
            if self.FrameList:
                now = time.time()
                
                pop_img = self.FrameList.pop(0)
                
                if face_result_list:
                    face_result_pos = face_result_list[0]
                    # print("Number of Face: ",len(face_result_pos))
                    for i in range(0,len(face_result_pos)):
                        pos_x = int(self.frame_width*face_result_pos[i]['DetectedFace']['BoundingBox']['Left'])
                        pos_y = int(self.frame_height*face_result_pos[i]['DetectedFace']['BoundingBox']['Top'])
                        x_end = pos_x + int(self.frame_width*face_result_pos[i]['DetectedFace']['BoundingBox']['Width'])
                        y_end = pos_y + int(self.frame_height*face_result_pos[i]['DetectedFace']['BoundingBox']['Height'])
                        cv2.rectangle(pop_img, (pos_x,pos_y), (x_end,y_end), (0,255,0), 4)
                        
                        if face_result_pos[i]['MatchedFaces']:
                            # print(face_result_pos[i]['MatchedFaces'][0]['Face']['ExternalImageId'])
                            cv2.putText(pop_img, face_result_pos[i]['MatchedFaces'][0]['Face']['ExternalImageId'], (pos_x, pos_y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,255,0), 2)
                        else:
                            cv2.putText(pop_img, 'unknown', (pos_x, pos_y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0,255,0), 2)
                
                cv2.imshow('Image', pop_img)
                
                timeDiff = time.time() - now
                # print("timeDiff = ", np.round(timeDiff,3)*1000)
                # while (timeDiff < 1.0/(30)):
                    # timeDiff = time.time() - now
                # cv2.waitKey(33-int(np.round(timeDiff,3)*1000))
                cv2.waitKey(30)
        

        
class face_detection:
    def __init__(self):
        self.rekognition_client = boto3.client('rekognition')
        self.kinesis_client = boto3.client('kinesis')  
        self.reset_start_time = time.time()
        
        #try to create stream processor
        while 1:
            try:
                create_response = self.rekognition_client.create_stream_processor(
                    Input={
                        'KinesisVideoStream': {
                            'Arn': KinesisVideoStreamArn
                        }
                    },
                    Output={
                        'KinesisDataStream': {
                            'Arn': KinesisDataStreamArn
                        }
                    },
                    Name=Rekognition_stream_processor_name,
                    Settings={
                        'FaceSearch': {
                            'CollectionId': 'MyCollection',
                            'FaceMatchThreshold': 0
                        }
                    },
                    RoleArn=AWSroleArn
                )
                break
            except self.rekognition_client.exceptions.InvalidParameterException:
                self.rekognition_client.stop_stream_processor(Name=Rekognition_stream_processor_name)
                self.rekognition_client.delete_stream_processor(Name=Rekognition_stream_processor_name)
        
        #start stream processor
        start_response = self.rekognition_client.start_stream_processor(
            Name=Rekognition_stream_processor_name
        )

    def queryface(self):
        while True:
            shard_iterator_response = self.kinesis_client.get_shard_iterator(
                StreamName=KinesisDataStream_name,
                ShardId='shardId-000000000000',
                ShardIteratorType='LATEST'
            )
            
            get_response = self.kinesis_client.get_records(
                ShardIterator=shard_iterator_response['ShardIterator']
            )
            # print(get_response)
            if get_response['Records']:
                face_byte_str = get_response['Records'][0]['Data']
                face_result = ast.literal_eval(face_byte_str.decode('utf-8'))
                if face_result['FaceSearchResponse']:
                    print(face_result['FaceSearchResponse'])
                    face_result_list.clear()
                    face_result_list.append(face_result['FaceSearchResponse'])
                    self.reset_start_time = time.time()
                else:
                    print('no face in video...')
            else:
                print('no face in video...')
            
            if (time.time()-self.reset_start_time)>2: # let bounding box display 2 seconds
                face_result_list.clear()
            
    def start(self):
        print("--- Face Detection Started! ---")
        threading.Thread(target=self.queryface, daemon=True, args=()).start()




def main():
    
    print("--- Get KVS URL ---")
    kvs_url = get_kvs_url()

    # Settin the video thread
    print("--- Set VideoCapture... ---")
    kvs_video = KVS_Capture(kvs_url)
    print("--- Set VideoCapture done ---")
    
    # start video thread
    kvs_video.start()

    # stop 1 sec, waiting for the image filling
    time.sleep(1)
    
    Rekognition_obj = face_detection()
    Rekognition_obj.start()
    
    # Use the infinity loop thresd for capturing the frame until pressing the ESC botton
    threading.Thread(target=kvs_video.displayframe, daemon=True, args=()).start()
    while True:
        cv2.waitKey(100)
        if cv2.waitKey(1) == 27:
            cv2.destroyAllWindows()
            kvs_video.stop()
            break


    
if __name__ == "__main__":
    main()