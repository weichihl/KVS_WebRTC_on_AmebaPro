:: %1 is project path (PROJ_DIR = EWARM-RELEASE)

echo off
set inc_path=%1\..\inc
set ispfw_path=%1\..\..\..\component\soc\realtek\8195b\misc\bsp\image

if [%1]==[] (
echo NEED PROJ_DIR
exit
)

::;*****************************************************************************#
::;                      Auto Select ISP firmware by Sensor                     #
::;*****************************************************************************#

:::: for testing on inc/sensor.h path
::findstr /i /c:"#define SENSOR_USE" sensor.h
::pause

if exist %ispfw_path%\sensor.txt del %ispfw_path%\sensor.txt
for /f "eol=/ tokens=2,3" %%i in ('cmd /c findstr /i /c:"#define SENSOR_USE" %inc_path%\sensor.h') do (
	set var=%%i 
	set sensor_tmp=%%j
	if %%j == SENSOR_ALL (goto :ALL_ISP_BIN) else (goto :ONE_ISP_BIN)
)
:ALL_ISP_BIN
for /f "eol=/ tokens=2,3" %%i in ('cmd /c findstr /i /c:"#define SENSOR_" %inc_path%\sensor.h') do (
	::echo %%i 
	::echo %%j
	if %%i == SENSOR_ALL (goto :ONE_ISP_BIN)
	@echo %%j,%%i>> %ispfw_path%\sensor.txt
)
:ONE_ISP_BIN
::echo %var% 
::echo %sensor_tmp%

:: remove sensor comment
set sensor_x=//%sensor_tmp:*//=%

::echo %sensor_x%

call set sensor=%%sensor_tmp:%sensor_x%=%%

::echo %sensor%

set sensor_mid=%sensor:*_=%

::echo isp_%sensor_mid%.bin

:: move isp_xxxx.bin to isp.bin
if exist %ispfw_path%\isp.bin del %ispfw_path%\isp.bin
if %sensor_mid% == ALL (
%ispfw_path%\ISP_COMBINE %ispfw_path%\sensor.txt %ispfw_path%\
) else (
copy %ispfw_path%\isp_%sensor_mid%.bin %ispfw_path%\isp.bin
)
::pause 