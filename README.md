# AmebaPro with KVS WebRTC and Producer
This project is going to demonstrate how to use KVS with WebRTC and Producer on AmebaPro  

## Brief Introduction for Amazon KVS  
**Amazon Kinesis Video Streams** include two main services, which are Producer and WebRTC  
https://aws.amazon.com/kinesis/video-streams/?nc1=h_ls&amazon-kinesis-video-streams-resources-blog.sort-by=item.additionalFields.createdDate&amazon-kinesis-video-streams-resources-blog.sort-order=desc  
**KVS Producer** can be used to stream live video from devices to the AWS Cloud, or build applications for batch-oriented video analytics.  
https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/what-is-kinesis-video.html  
**KVS WebRTC** is an open technology specification for enabling real-time communication (RTC) across browsers and mobile applications via simple APIs.  
https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/what-is-kvswebrtc.html  


## Description  
This article introduces users how to develop AmebaPro with KVS service.  

**Note: Currently, the source code of WebRTC on FreeRTOS is public, so we can clone the repository as submodule directly. However, the Producer on FreeRTOS still in development stage, source code will be released in the future.**  

The related example code:  
`project\component\common\example\kvs_webrtc`  
`project\component\common\example\kvs_producer` (will be supported in the future)  


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

## Prerequisites  
> ### Set Up an AWS Account and Create an Administrator  
> Please refer AWS official instruction to get **Access key ID** and **Secret access key**  
> https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/gs-account.html  
> 
> Aftering getting the key, enter your key and sinaling channel name in the following file `example_kvs_webrtc.h`  
> ```
> #define KVS_WEBRTC_ACCESS_KEY   "XXXXXXXX"  
> #define KVS_WEBRTC_SECRET_KEY   "XXXXXXXX"  
> #define KVS_WEBRTC_CHANNEL_NAME "XXXXXXXX"  
> ```
> 
> ### Put the CA file in SD card   
> If using WebRTC example, please prepare a SD card for AWS certificate  
> There is a `cert.pem` file in `lib_amazon\amazon-kinesis-video-streams-webrtc-sdk-c\certs`  
> Please copy it to your SD card, then insert it into AmabaPro.  
> 
> ### Choose the KVS demo  
> All examples provided by RTK exist in folder: SDK_path/common/example. Open `platform_opts.h` to specify the exampleto run.  
> For example, if users are going to use KVS WebRTC, compile flag CONFIG_EXAMPLE_KVS_WEBRTC should be set to 1, which means  
> `#define CONFIG_EXAMPLE_KVS_WEBRTC 1`  

  
## Build The Project  
> ### Compile program with IAR Embedded Workbench
> > AmebaPro use the newest Big-Little architecture. Since the big CPU will depend on the setting of small CPU, it is necessary to compile the small CPU before the big CPU.  
> > 
> > #### Compile little CPU
> > Step1. Open SDK/project/realtek_amebapro_v0_example/EWARMRELEASE/Project_lp.eww.  
> > Step2. Confirm application_lp in WorkSpace, right click application_lp and choose “Rebuild All” to compile.  
> > Step3. Make sure there is no error after compile.  
> > 
> > #### Compile big CPU
> > Step1. Open SDK/project/realtek_amebapro_v0_example/EWARMRELEASE/Project_is.eww.  
> > Step2. Confirm application_is in WorkSpace, right click application_is and choose “Rebuild All” to compile.  
> > Step3. Make sure there is no error after compile.  
> > 
> > #### Generating image (Bin)
> > After compile, the images partition.bin, boot.bin, firmware_is.bin and flash_is.bin can be seen in the EWARM-RELEASE\Debug\Exe.  
> > flash_is.bin links partition.bin, boot.bin and firmware_is.bin. Users need to choose flash_is.bin when downloading the image to board by Image Tool.  
> 
> ### Compile program with GCC toolchain  
> > If using Linux environment or Cygwin on windows, follow the instructions below to build the project  
> > ```
> > cd project/realtek_amebapro_v0_example/GCC-RELEASE  
> > ```
> > If using GCC toolchain to build the project, it is necessary to configure some value in "FreeRTOS_POSIX_portable_default.h"  
> > ```
> > #define posixconfigENABLE_CLOCKID_T  0  
> > #define posixconfigENABLE_MODE_T     0  
> > #define posixconfigENABLE_TIMER_T    0  
> > ```
> > Build the library and the example by running make in the directory  
> > ```
> > make -f Makefile_amazon_kvs all
> > ```
> > If somehow it built failed, you can try to type `make -f Makefile_amazon_kvs clean` and then redo the make procedure.  
> > After successfully build, there should be a directory named “application_is” created under GCC-RELEASE/ directory.  
> > The image file `flash_is.bin` is located in ”application_is” directory.  
> > #### Note:
> > if there is compile error with shell script, you may need to run following command to deal with the problem  
> > ```
> > dos2unix component/soc/realtek/8195b/misc/gcc_utility/*
> > ```

## Using Image Tool to Download Image
> Execute ImageTool.exe from location `project\tools\AmebaPro\Image_Tool\ImageTool.exe`  
> As show in the following figure, Image Tool has two tab pages:  
> * Download: used as image download server to transmit images to AmebaPro through UART  
> * Generate: concat separate images and generate a final image  
> 
>  
> <p align="center"> <img src="photo/image_tool_1.png" alt="test image size" height="50%" width="50%"></p>  
> <p align="center"> <img src="photo/hardware_setting.png" alt="test image size" height="50%" width="50%"></p>  
> <p align="center"> <img src="photo/FT232_connection.png" alt="test image size" height="50%" width="50%"></p>  
>  
> Image tool use UART to transmit image to AmebaPro board. Before performing image download function, AmebaPro need to enter UART_DOWNLOAD mode first. Please follow below steps to get AmebaPro into UART_DOWNLOAD mode:  
> 
> <p align="center"> <img src="photo/download_mode.png" alt="test image size" height="50%" width="50%"></p>  
> 
> > Step1: Connect LOGUART with FT pin by jumper cap.  
> > Step2: Connect USB->UART to PC by using micro-USB wire.  
> > Step3: Switch “1” to ON from SW7(2V0、2V1) or Switch “2” to ON from SW7(1V0)  
> > Step4: Push reset button.  
> 
> <p align="center"> <img src="photo/flash_download.png" alt="test image size" height="50%" width="50%"></p>  
> 
> To download image through Image Tool, device need to enter UART_DOWNLOAD mode first.  
> Steps to download flash are as following:  
> 
> > Step1: Application will scan available UART ports. Please choose correct UART port. Please close other UART connection for the target UART port.  
> > Step2: Choose desired baud rate between computer and AmebaPro.  
> > Step3: Choose target flash binary image file “flash_xx.bin”  
> > Step4: Check Mode is “1. Program flash”  
> > Step5: Click “Download”  
> > Step6: Progress will be shown on progress bar and result will be shown after download finish.  
> > Step7: Switch “1” to OFF from SW7(2V0、2V1) or Switch “2” to OFF from SW7(1V0)  
> > Step8: Push reset button to start the program.  

## Setting WIFI SSID/password with AT Command  
In order to run the example, AmebaPro should connect to the network. It can be achieved by run the AT command in uart console. Please refer to the steps below:  
```
ATW0=<WiFi_SSID> : Set the WiFi AP to be connected  
ATW1=<WiFi_Password> : Set the WiFi AP password  
ATWC : Initiate the connection  
```
more information about RTK AT command:  
https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/doc/AN0025%20Realtek%20at%20command.pdf


## Verify the Demo by Test Page  
> ### WebRTC test  
> Refer the link from **AWS labs**, using the WebRTC SDK Test Page to validate the demo  
> https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-js  
> Clone the above project and follow the step in **Development** part to run the test page  
> 
> ### Producer test  
> https://aws-samples.github.io/amazon-kinesis-video-streams-media-viewer  
> Enter the AWS Access Key, AWS Secret Key and Stream name to test the prducer streaming  


## More Information  
> ### Rebuild the library and compile the application project again (IAR)  
> If the source codes in library are modified, the corresponding library should be rebuild.  
> 
> <p align="center"> <img src="photo/library.png" alt="test image size" height="40%" width="40%"></p>  
> 
> Then, go back to application_is project and "Make" again, the updated library can then be linked.
> 
> <p align="center"> <img src="photo/library_update.png" alt="test image size" height="40%" width="40%"></p>  
> 
> ### Add independent and additional include directories to specific example   
> The additional include directories of KVS with WebRTC example is temporarily independent.
> You can add additional include path by right clicking `kvs_webrtc` and choosing `options` --> `C/C++Compiler` --> `Preprocessor`  
> 
> <p align="center"> <img src="photo/example_include_path.png" alt="test image size" height="40%" width="40%"></p>  
> 
> ### Using JTAG/SWD to debug
> AmebaPro support using JTAG/SWD to debug.    
