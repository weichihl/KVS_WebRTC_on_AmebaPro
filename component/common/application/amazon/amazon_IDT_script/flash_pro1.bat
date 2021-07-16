set IARDir="C:\Program Files (x86)\IAR Systems\Embedded Workbench 8.1"
set IARProjectDir=D:\WFH_RTK\W_R\KVS_WebRTC_on_AmebaPro\project\realtek_amebapro_v0_example\EWARM-RELEASE
set PorjectName=application_is


set RootDir=%CD%
cd %IARProjectDir%
%IARDir%\common\bin\cspybat %IARDir%\arm\bin\armproc.dll %IARDir%\arm\bin\armjlink2.dll %IARProjectDir%\Debug\Exe\application_is.out --plugin %IARDir%\arm\bin\armbat.dll --macro %IARProjectDir%\debug.mac --flash_loader %IARProjectDir%\..\..\..\component\soc\realtek\8195b\misc\iar_utility\flashloader\FlashRTL8195b.board --backend --endian=little --cpu=Cortex-M33 --device=Cortex-M33 --cmse --fpu=VFPv5_SP -p %IARProjectDir%\..\..\..\component\soc\realtek\8195b\misc\iar_utility\8195bh.ddf --semihosting=none --drv_communication=USB0 --drv_interface_speed=4000 --jlink_reset_strategy=0,0 --drv_interface=SWD --drv_catch_exceptions=0x000 --drv_swo_clock_setup=25000000,1,2000000
cd %RootDir%

pause