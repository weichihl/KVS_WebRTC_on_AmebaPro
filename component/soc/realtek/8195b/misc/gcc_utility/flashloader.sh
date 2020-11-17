#!/bin/sh

xip_text=`grep __xip_code_text_start__ application_is/Debug/bin/application_is.map | head -1 | gawk '{print $1}'`
#echo $xip_text
xip_text=`echo $(($xip_text -0x98000000))`
#echo $xip_text
fw2_text=`grep FW2_FLASH_start xip_fw.ld | head -1 | gawk '{print $3}'`
#echo $fw2_text
fw2_text=`echo $(($fw2_text -0x98000000))`
#echo $fw2_text
remap_addr=`echo $((0x9be00000 -0x98000000))`
#echo $remap_addr

#===============================================================================

if [ $xip_text -gt $remap_addr ]; then
	FIRMWARENAME="application_is/flash_is.bin"
elif [ $xip_text -lt $fw2_text ]; then
	FIRMWARENAME="application_is/flash_is_ota1.bin"
else
	FIRMWARENAME="application_is/flash_is_ota2.bin"
fi

echo $FIRMWARENAME

#===============================================================================
#get file size
FIRMWARE_SIZE=$(stat -c %s $FIRMWARENAME)

echo "set \$FirmwareName = \"$FIRMWARENAME\"" > fwinfo.gdb
echo "set \$FirmwareSize = $FIRMWARE_SIZE" >> fwinfo.gdb

echo "restore $FIRMWARENAME binary (int)&FlashBufferStart-\$Offset \$ReadPtr \$ReadEndPtr" > restore.gdb
exit