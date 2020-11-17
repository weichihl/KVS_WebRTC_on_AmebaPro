SD CARD HOTPLUG EXAMPLE 

Description:
The example show how to use the hot plug and sd card reset from standby mode.
The default setting is hotplug example.
Configuration:
[example_sd_hotplug.c]
1.Config SD CARD power pin
#define USE_DEMO_BOARD //For Demo board PH_0, other is QFN128 PE_12
#define ENABLE_SD_POWER_RESET //Power rest for sd card to avoid the unstable state for sd card.
#define SD_POWER_RESET_DELAY_TIME 50 //Wait 50ms to do power reset cycle.
2.Demo mode
#define SD_REST_TEST_STANDBY_MODE// Enter the standby mode to test the mount status.
3.Card Detect type
#define USE_GPIO_DETECT //Use GPIO to detect the SD Card insert and remove by sd driver.
#define USE_SD_DETECT   //Use SD driver to detect the hotplug 

[platform_opts.h]
	#define CONFIG_EXAMPLE_SD_HOT_PLUT    1

Execution:
First  mode(Normal mode) : Please plug or unplug sd card to test.This is for non reset mode.
Second mode(Reset mode)  : Please inset the sd card before run the example. Check teset status is ongoing. 

[Supported List]
	Supported :
	    Ameba-pro
