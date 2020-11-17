This is an example for transmiting isp image to PC through USB.
In order to use this example, you can utilize vlc media player to stream uvcd video.

[Supported List]
	Supported :
		Ameba-pro
	Source code not in project :
	    Ameba-1, Ameba-z
		
Note: It can only choice the dual or single uvc at the same time.The dual uvc only support at linux version. 
Dual UVC need to non exclude the below files
example_media_dual_uvcd.c
module_dual_uvcd.c
usbd_dual_uvc_parm.c

Normal UVC need to non exclude the below files
example_media_uvcd.c
module_uvcd.c
usbd_uvc_parm.c

The default driver is normal uvc. The dual uvc need to generate new driver to support.