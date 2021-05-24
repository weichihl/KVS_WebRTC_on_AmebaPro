# AmebaPro with KVS WebRTC and Producer
This project is going to demonstrate how to use KVS Producer and WebRTC on AmebaPro
<a href="https://www.amebaiot.com/zh/amebapro/">
  <img src="https://img.shields.io/badge/Realtek%20IoT-AmebaPro-blue" valign="middle" alt="test image size" height="15%" width="15%"/>
</a>  

## Brief Introduction to Amazon KVS  
:blue_book: **Amazon Kinesis Video Streams**  
&nbsp; include two main services, which are Producer and WebRTC
<a href="https://aws.amazon.com/kinesis/video-streams/?nc1=h_ls&amazon-kinesis-video-streams-resources-blog.sort-by=item.additionalFields.createdDate&amazon-kinesis-video-streams-resources-blog.sort-order=desc">
  <img src="https://img.shields.io/badge/-Link-lightgrey" valign="middle" alt="test image size" height="4%" width="4%"/>
</a>  
:blue_book: **KVS Producer**  
&nbsp; stream live video from devices to the AWS Cloud, or build applications for batch-oriented video analytics.
<a href="https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/what-is-kinesis-video.html">
  <img src="https://img.shields.io/badge/-Link-lightgrey" valign="middle" alt="test image size" height="4%" width="4%"/>
</a>  
:blue_book: **KVS WebRTC**  
&nbsp; enable real-time communication (RTC) across browsers and mobile applications via simple APIs.
<a href="https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/what-is-kvswebrtc.html">
  <img src="https://img.shields.io/badge/-Link-lightgrey" valign="middle" alt="test image size" height="4%" width="4%"/>
</a>  

## Applications on AmebaPro  
### :bulb: AI Face Detection
&nbsp; AmebaPro(Producer) + Rekognition(AWS AI) = video cloud storage and content analytics :cloud:  
<table style="width:100%; table-layout:fixed">
  <tr>
    <td><img src="photo/face_detection.jpg" valign="middle" alt="test image size" height=233px width=400px /></td>
    <td align=Left>1. Stream live video from AmebaPro to KVS<BR>2. AI face detection by using AWS Rekognition API</td>
    <td>
      <a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_Producer_Getting_Started_Guide_v1.0.pdf">
        <img src="https://img.shields.io/badge/-Getting%20Started-green"/>
      </a>
    </td>
  </tr>
</table>  

### :bulb: Real-time communucation  
&nbsp; AmebaPro(WebRTC master) + Viewer(WebRTC Client) = real-time communication, 1-way video & 2-way audio  
<table style="width:100%; table-layout:fixed">
  <tr>
    <td><img src="photo/p2p.jpg" valign="middle" alt="test image size" height=224px width=435px /></td>
    <td align=Left>1. AmebaPro start a signaling channel to run as a master<BR>2. Use the browser to run as a viewer and start P2P connection</td>
    <td>
      <a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_WebRTC_Getting_Started_Guide_v1.0.pdf">
        <img src="https://img.shields.io/badge/-Getting%20Started-green"/>
      </a>
    </td>
  </tr>
</table>


## Demo code  
:pencil2: **KVS WebRTC** &nbsp; &nbsp; :point_right: &nbsp; &nbsp; `project/component/common/example/kvs_webrtc`  
:pencil2: **KVS Producer** &nbsp; &nbsp; :point_right: &nbsp; &nbsp;`project/component/common/example/kvs_producer`  


## IDE/toolchain Requirement
:hammer: **IAR Embedded Workbench - IAR Systems**  
&nbsp; Please use IAR version 8.3  
:hammer: **GCC toolchain**  
&nbsp; Linux: asdk-6.4.1-linux-newlib-build-3026-x86_64  
&nbsp; Cygwin: asdk-6.4.1-cygwin-newlib-build-2778-i686  


## Clone Project  
To check out this repository:  

```
git clone --recurse-submodules https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro.git
```

If you already have a checkout, run the following command to sync submodules:

```
git submodule update --init
```
