.PHONY: sensor

empty:=
s? = $(subst $(empty) ,?,$1)
?s = $(subst ?, ,$1)
dirx = $(call ?s,$(dir $(call s?,$1)))

sensor:
	@echo Sensor binary auto selection 
	@chmod +x ../../../component/soc/realtek/8195b/misc/gcc_utility/sensor_autosel.sh
	../../../component/soc/realtek/8195b/misc/gcc_utility/sensor_autosel.sh "$(call dirx ,$(abspath $(firstword $(MAKEFILE_LIST))))"