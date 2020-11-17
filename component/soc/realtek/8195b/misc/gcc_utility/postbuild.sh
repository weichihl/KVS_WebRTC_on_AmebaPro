#!/bin/sh
#===============================================================================
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

if [ $xip_text -gt $remap_addr ]; then
	echo "This is remapped firmware"
	mode=1
elif [ $xip_text -lt $fw2_text ]; then
	echo "This is firmware ota1"
	if [ -e application_is/firmware_is_ota1.bin ]; then
		rm application_is/flash_is_ota1.bin
		rm application_is/firmware_is_ota1.bin
	fi
	mv application_is/flash_is.bin application_is/flash_is_ota1.bin
	mv application_is/firmware_is.bin application_is/firmware_is_ota1.bin
	mode=0
else
	echo "This is firmware ota1"
	if [ -e application_is/firmware_is_ota2.bin ]; then
		rm application_is/flash_is_ota2.bin
		rm application_is/firmware_is_ota2.bin
	fi
	mv application_is/flash_is.bin application_is/flash_is_ota2.bin
	mv application_is/firmware_is.bin application_is/firmware_is_ota2.bin
	mode=0
fi

#echo mode=$mode
if [ $mode -eq 1 ]; then
	echo "generate ota_is.bin"
	$1 otamerge application_is/firmware_is.bin application_is/firmware_is.bin application_is/ota_is.bin
	exit
fi

ota=$(echo "0")
#echo $ota
if [ -e application_is/firmware_is_ota1.bin ]; then
	echo "firmware ota1 exist"
	ota=$(echo "1")
	#echo $ota
else
	echo "firmware ota1 not exist"
fi
if [ -e application_is/firmware_is_ota2.bin ]; then
	echo "firmware ota2 exist"
	ota=`echo $(($ota +1))`
	#echo $ota
else
	echo "firmware ota2 not exist"
fi
if [ $ota = 2 ]; then
	echo "combine ota1/ota2"
	#echo `pwd`
	#echo $1
	$1 otamerge application_is/firmware_is_ota1.bin application_is/firmware_is_ota2.bin application_is/ota_is.bin
	#../../../component/soc/realtek/8195b/misc/iar_utility/elf2bin.exe otamerge application_is/firmware_is_ota1.bin application_is/firmware_is_ota2.bin application_is/ota_is.bin
fi
exit