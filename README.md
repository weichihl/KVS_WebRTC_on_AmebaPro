# AmebaPro with KVS WebRTC and Producer
This project is going to demonstrate how to use KVS with WebRTC and Producer on AmebaPro  

## Brief Introduction for Amazon KVS  
:blue_book: **Amazon Kinesis Video Streams** include two main services, which are Producer and WebRTC  
https://aws.amazon.com/kinesis/video-streams/?nc1=h_ls&amazon-kinesis-video-streams-resources-blog.sort-by=item.additionalFields.createdDate&amazon-kinesis-video-streams-resources-blog.sort-order=desc  
:blue_book: **KVS Producer** can be used to stream live video from devices to the AWS Cloud, or build applications for batch-oriented video analytics.  
https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/what-is-kinesis-video.html  
:blue_book: **KVS WebRTC** is an open technology specification for enabling real-time communication (RTC) across browsers and mobile applications via simple APIs.  
https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/what-is-kvswebrtc.html  


## Description  
This article introduces users how to develop AmebaPro with KVS service.  

:bulb: **KVS WebRTC**  
`project\component\common\example\kvs_webrtc` :point_right: 
<a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_WebRTC_Getting_Started_Guide_v1.0.pdf">
  <img src="https://img.shields.io/badge/-Getting%20Started-green" alt="test image size" height="13%" width="13%"/>
</a>  
  
:bulb: **KVS Producer**  
`project\component\common\example\kvs_producer` :point_right: 
<a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_Producer_Getting_Started_Guide_v1.0.pdf">
  <img src="https://img.shields.io/badge/-Getting%20Started-green" alt="test image size" height="13%" width="13%"/>
</a>  


## Requirement
Supported IDE/toolchain: IAR, GCC
#### IAR Embedded Workbench - IAR Systems  
Please use IAR version 8.3 (There may be some compiler problems with v8.4)  
#### GCC toolchain
Linux: asdk-6.4.1-linux-newlib-build-3026-x86_64  
Cygwin: asdk-6.4.1-cygwin-newlib-build-2778-i686  


## Clone Project  
To check out this repository:  

```
git clone --recurse-submodules https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro.git
```

If you already have a checkout, run the following command to sync submodules:

```
git submodule update --init
```
