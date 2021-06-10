#!/bin/bash

APP_VERSION_MAJOR=`cat ../amazon-freertos-202012.00/demos/include/aws_application_version.h | grep -i VERSION_MAJOR | cut -d " " -f 6`
JSON_VERSION=`cat ../../../../../project/realtek_amebapro_v0_example/EWARM-RELEASE/amebapro_firmware_is.json | grep -i serial | sed -n 8p | cut -d ":" -f 2 | sed "s/^[ \t]*//g"`

if [ "${APP_VERSION_MAJOR}" != "${JSON_VERSION}" ]
then
	echo "APP_VERSION_MAJOR  = $APP_VERSION_MAJOR"
	echo "serial = $JSON_VERSION"
	echo "!!! Please check FW version setting in \"aws_application_version.h\" and \"amebaz2_firmware_is.json\". The version must same !!!"
	echo "!!! Please check FW version setting in \"aws_application_version.h\" and \"amebaz2_firmware_is.json\". The version must same !!!"
	exit 1
fi
