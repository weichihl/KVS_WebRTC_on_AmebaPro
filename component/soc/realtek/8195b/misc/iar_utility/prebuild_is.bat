::echo TARGET_DIR %1
::echo PROJ_DIR %2
::echo CONFIG_NAME %3
::echo IAR_TOOL_DIR %4

::pause
cd /D %2

set tooldir=%2\..\..\..\component\soc\realtek\8195b\misc\iar_utility
set libdir=%2\..\..\..\component\soc\realtek\8195b\misc\bsp
set cfgdir=%3
set iartooldir=%4

::;*****************************************************************************#
::;                      Select FreeRTOS version                                #
::;   compiling will begain and at that time prebuild may not be finished       #
::;   So symbolic link must execute in the begginning of batch                  #
::;*****************************************************************************#
if exist %2\..\..\..\component\os\freertos\freertos.bat (
call %2\..\..\..\component\os\freertos\freertos.bat %2
)

::update key.json
%tooldir%\elf2bin.exe prebuild IAR xip_fw.icf FW

:: Generate build_info.h
echo off
::echo %date:~0,10%-%time:~0,8%
::echo %USERNAME%
for /f "usebackq" %%i in (`hostname`) do set hostname=%%i
::echo %hostname%

echo #define RTL_FW_COMPILE_TIME RTL8195BFW_COMPILE_TIME > ..\inc\build_info.h
echo #define RTL_FW_COMPILE_DATE RTL8195BFW_COMPILE_DATE >> ..\inc\build_info.h
echo #define UTS_VERSION "%date:~0,10%-%time:~0,8%" >> ..\inc\build_info.h
echo #define RTL8195BFW_COMPILE_TIME "%date:~0,10%-%time:~0,8%" >> ..\inc\build_info.h
echo #define RTL8195BFW_COMPILE_DATE "%date:~0,10%" >> ..\inc\build_info.h
echo #define RTL8195BFW_COMPILE_BY "%USERNAME%" >> ..\inc\build_info.h
echo #define RTL8195BFW_COMPILE_HOST "%hostname%" >> ..\inc\build_info.h
echo #define RTL8195BFW_COMPILE_DOMAIN >> ..\inc\build_info.h
echo #define RTL8195BFW_COMPILER "IAR compiler" >> ..\inc\build_info.h

::;*****************************************************************************#
::;                      Auto Select Sensor firmware                            #
::;*****************************************************************************#
call %tooldir%\sensor_autosel.bat %2




