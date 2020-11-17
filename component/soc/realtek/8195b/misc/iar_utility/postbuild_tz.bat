::echo TARGET_DIR %1
::echo PROJ_DIR %2
::echo CONFIG_NAME %3
::echo IAR_TOOL_DIR %4

::pause
cd /D %2

set tooldir=%2\..\..\..\component\soc\realtek\8195b\misc\iar_utility
::set libdir=%2\..\..\..\component\soc\realtek\8195b\misc\bsp
set cfgdir=%3
set iartooldir=%4

::update key.json
%tooldir%\elf2bin.exe keygen keycfg.json > postbuild_tz_log.txt
%tooldir%\elf2bin.exe convert amebapro_bootloader.json PARTITIONTABLE >> postbuild_tz_log.txt
%tooldir%\elf2bin.exe convert amebapro_firmware_tz.json FIRMWARE >> postbuild_tz_log.txt
%tooldir%\elf2bin.exe combine Debug/Exe/flash_tz.bin PTAB=Debug/Exe/partition.bin,BOOT=Debug/Exe/boot.bin,FW1=Debug/Exe/firmware_tz.bin >> postbuild_tz_log.txt

%iartooldir%\bin\ielfdumparm.exe --code Debug/Exe/application_s.out Debug/Exe/application_s.asm
%iartooldir%\bin\ielfdumparm.exe --code Debug/Exe/application_ns.out Debug/Exe/application_ns.asm
::pause
