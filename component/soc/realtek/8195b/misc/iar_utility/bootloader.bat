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

%tooldir%\elf2bin.exe convert amebapro_bootloader.json BOOTLOADER

%iartooldir%\bin\ielfdumparm.exe --code Debug/Exe/bootloader.out Debug/Exe/bootloader.asm

:: update boot.bin, bootloader.out for application
copy Debug\Exe\boot.bin %libdir%\image\boot.bin
copy Debug\Exe\bootloader.out %libdir%\image\bootloader.out

::pause
