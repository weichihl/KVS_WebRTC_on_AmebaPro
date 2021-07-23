# Edge AI + Cloud AI - Human Detection on AmebaPro and Face Detection on AWS Cloud

## What can We Get After Integrating Edge AI and Cloud AI?

We can detect the person on edge device and recognize the person by AWS Rekognition service, the following is our simple video demo (We use AmebaPro to shoot PC screen with a youtube video playing)

* The **White Box** is the human detection result from AmebaPro   
* The **Green Box** is the face detection result from AWS Rekognition  

https://user-images.githubusercontent.com/56305789/126762071-dae24867-e60d-4cda-8d8a-98b2274fe6ee.mp4

https://user-images.githubusercontent.com/56305789/126761671-6fb2a1da-c486-42b6-836d-c9b81c262d93.mp4

video src: https://www.youtube.com/watch?v=Zv1fgmd1pr4&ab_channel=JonnyTechnology  

## How to Integrate Edge AI and Cloud AI to Implement Human Detection and Face Recognition

### Check the Model of Camera Sensor 

Please check your camera sensor model, and define it in <AmebaPro_SDK>/project/realtek_amebapro_v0_example/inc/sensor.h.

```
#define SENSOR_USE      	SENSOR_XXXX
```

### Configure Example Setting

Before run the example, you need to check the object detection is enabled in <AmebaPro_SDK>/project/realtek_amebapro_v0_example/inc/platform_opts.h.

```
/* For object detection example */
#define CONFIG_EXAMPLE_OBJECT_DETECTION         1
```

Then, enable the USE_KVS_PRODUCER in <AmebaPro_SDK>/project/realtek_amebapro_v0_example/src/obj_detect/object_detection_init.h to upload the video to KVS

```
#define USE_RTSP 0
#define USE_KVS_PRODUCER 1
```

### Configure AWS KVS Setting

After getting AWS account key, enter the key pair and stream name in <AmebaPro_SDK>/component/common/example/kvs_producer/sample_config.h
```
/* KVS general configuration */
#define AWS_ACCESS_KEY                  "xxxxxxxxxxxxxxxxxxxx"
#define AWS_SECRET_KEY                  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

/* KVS stream configuration */
#define KVS_STREAM_NAME                 "kvs_example_camera_stream"
#define AWS_KVS_REGION                  "us-east-1"
```

[How to get AWS account key? See section 2.3 in KVS producer user guide](https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_Producer_Getting_Started_Guide_v1.1.pdf)

### Build project and Flash Image

To build the example run the following command:

```
cd <AmebaPro_SDK>/project/realtek_amebapro_v0_example/GCC-RELEASE
make -f Makefile_amazon_kvs all
```

If there is compile error with shell script in "component/soc/realtek/8195b/misc/gcc_utility/", you may need to run following command

```
$ dos2unix component/soc/realtek/8195b/misc/gcc_utility/*
```

The image is located in <AmebaPro_SDK>/project/realtek_amebapro_v0_example/GCC-RELEASE/application_is/flash_is.bin

Make sure your AmebaPro is connected and powered on. Use the Realtek image tool to flash image and check the logs.

[How to use Realtek image tool? See section 1.3 in AmebaPro's application note](https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/doc/AN0300%20Realtek%20AmebaPro%20application%20note.en.pdf)

### Run the Example and Check if Video is being Uploaded

Reboot your device and check the logs.  

If everything works fine, you should see the following logs.
```
...
PUT MEDIA endpoint: s-xxxxxxxx.kinesisvideo.us-east-1.amazonaws.com
Try to put media
Info: 100-continue
Info: Fragment buffering, timecode:1620367399995
Info: Fragment received, timecode:1620367399995
Info: Fragment buffering, timecode:1620367401795
Info: Fragment persisted, timecode:1620367399995
Info: Fragment received, timecode:1620367401795
Info: Fragment buffering, timecode:1620367403595
```

### Start Rekognition and Get the Results

We shoud use AWS python API to do following things:  

1. Start the stream processor to enable Rekognition to do face detection  

2. Get stored video from kinesis video stream(KVS)  

3. Get the face detection result from kinesis data stream   

then, draw the face detection boounding boxes on the video to get the final visualized result.

We provide a simple python code in <AmebaPro_SDK>component/common/example/kvs_producer/**producer_rekognition_test.py**. The python code is for reference only.  

Please refer the section 8 in KVS producer user guide:
[KVS Producer + Rekognition Example](https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_Producer_Getting_Started_Guide_v1.1.pdf)

Note: you may need to specify the frame rate in producer_rekognition_test.py.  
```
...
video_fps = 15;  #### set your kvs video frame rate here ####
```
