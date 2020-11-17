This example shows how to use dfu to update OTA FW.

NOTE: 1.It only support the linux version.
      2.You need to prepare the usb line.One connect to Ameba Pro(Device port) and the ohter to PC host.

[Supported List]
	Supported :
	    Ameba-Pro

Please use the dfu-util 0.9 to update the fw. It need to use the development version.
It also need to install libusb
The command sa below
sudo ./dfu-util -d 1d6b:0202 -a 0 -D ota_is.bin

http://dfu-util.sourceforge.net/