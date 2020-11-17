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

:: check boot.bin exist, copy default
if not exist %cfgdir%\Exe\boot.bin (
	copy %libdir%\image\boot.bin %cfgdir%\Exe\boot.bin
)

:: check bootloader.out exist, copy default
if not exist %cfgdir%\Exe\bootloader.out (
	copy %libdir%\image\bootloader.out %cfgdir%\Exe\bootloader.out
)

::update key.json
%tooldir%\elf2bin.exe keygen keycfg.json > postbuild_is_log.txt
%tooldir%\elf2bin.exe convert amebapro_bootloader.json PARTITIONTABLE >> postbuild_is_log.txt
%tooldir%\elf2bin.exe convert amebapro_firmware_is.json FIRMWARE >> postbuild_is_log.txt
%tooldir%\checksum.exe Debug\Exe\firmware_is.bin
%tooldir%\elf2bin.exe combine Debug/Exe/flash_is.bin PTAB=Debug\Exe\partition.bin,BOOT=Debug\Exe\boot.bin,FW1=Debug\Exe\firmware_is.bin >> postbuild_is_log.txt

:: For flash download and debug
:: find main symbol
for /f "tokens=2" %%i in ('cmd /c findstr "^main" Debug\List\application_is.map') do set main_addr=%%i
::echo main=%main_addr%

set /a tmp = %main_addr:'=%-1 
call :toHex %tmp% main_addr
::echo main=%main_addr%

:: rename
if exist Debug\Exe\application_is.dbg.out (
	del Debug\Exe\application_is.dbg.out
)

rename Debug\Exe\application_is.out application_is.dbg.out
%iartooldir%\bin\ilinkarm.exe %tooldir%\ilinkhappy.o --image_input Debug\Exe\flash_is.bin,flash,firmware,32 --cpu Cortex-M33 --fpu=VFPv5 --no_entry --keep flash --define_symbol main=0x%main_addr% --define_symbol __vector_table=0x00 -o Debug\Exe\application_is.out


for /f "tokens=2" %%i in ('cmd /c findstr /i "^XIP_TEXT$$BASE ^XIP_TEXT$$Base" Debug\List\application_is.map') do set tmp=%%i
set /a xip_text = %tmp:'=%-0x98000000
echo xip_text=%xip_text%

for /f "tokens=5" %%i in ('cmd /c findstr "FW2_FLASH_start" xip_fw.icf') do set tmp=%%i
set /a fw2_text = %tmp:;=%-0x98000000 
echo fw2_text=%fw2_text%

set /a remap_addr = 0x9be00000-0x98000000
if %xip_text% GTR %remap_addr% (
	echo %xip_text%
	echo %remap_addr%
	echo This is remapped firmware 
	set /a mode=1
	goto :generate_ota
)

if %xip_text% LSS %fw2_text% (
	echo This is firmware ota1
	:: rename firmware name to flash_is.bin firmware_is.bin to flash_is_ota1.bin firmware_is_ota1.bin
	del Debug\Exe\flash_is_ota1.bin
	del Debug\Exe\firmware_is_ota1.bin
	rename Debug\Exe\flash_is.bin flash_is_ota1.bin
	rename Debug\Exe\firmware_is.bin firmware_is_ota1.bin
	set /a mode=0
	goto :generate_ota
)

if %xip_text% GTR %fw2_text% (
	echo This is firmware ota2
	:: rename firmware name to flash_is.bin firmware_is.bin to flash_is_ota2.bin firmware_is_ota2.bin
	del Debug\Exe\flash_is_ota2.bin
	del Debug\Exe\firmware_is_ota2.bin
	rename Debug\Exe\flash_is.bin flash_is_ota2.bin
	rename Debug\Exe\firmware_is.bin firmware_is_ota2.bin
	set /a mode=0
	goto :generate_ota
)

:generate_ota

if %mode% EQU 1 (
	echo generate ota_is.bin
	%tooldir%\elf2bin.exe otamerge Debug\Exe\firmware_is.bin Debug\Exe\firmware_is.bin Debug\Exe\ota_is.bin
	goto :end
)

if exist Debug\Exe\firmware_is_ota1.bin set ota=1
if exist Debug\Exe\firmware_is_ota2.bin set /a ota+=1

if %ota% EQU 2 (
	echo combine ota1/ota2
	%tooldir%\elf2bin.exe otamerge Debug\Exe\firmware_is_ota1.bin Debug\Exe\firmware_is_ota2.bin Debug\Exe\ota_is.bin
)

:end

:: disassembly, very long time, turn on if needed
::%iartooldir%\bin\ielfdumparm.exe --code Debug\Exe\application_is.dbg.out Debug\Exe\application_is.asm

exit


:toHex dec hex -- convert a decimal number to hexadecimal, i.e. -20 to FFFFFFEC or 26 to 0000001A
@echo off
SETLOCAL ENABLEDELAYEDEXPANSION
set /a dec=%~1
set "hex="
set "map=0123456789ABCDEF"
for /L %%N in (1,1,8) do (
    set /a "d=dec&15,dec>>=4"
    for %%D in (!d!) do set "hex=!map:~%%D,1!!hex!"
)

( ENDLOCAL & REM RETURN VALUES
    IF "%~2" NEQ "" (SET %~2=%hex%) ELSE ECHO.%hex%
)
EXIT /b