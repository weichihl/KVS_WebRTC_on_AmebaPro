
# Initialize tool chain
# -------------------------------------------------------------------
OS := $(shell uname)

ifeq ($(findstring CYGWIN, $(OS)), CYGWIN)
	ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/cygwin/newlib/bin
else
	ifeq ($(findstring MINGW32, $(OS)), MINGW32)
		ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/mingw32/newlib/bin
	else
		ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/linux/newlib/bin
	endif		
endif

CROSS_COMPILE = $(ARM_GCC_TOOLCHAIN)/arm-none-eabi-

# Compilation tools
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
OBJCOPY = $(CROSS_COMPILE)objcopy

# Initialize target name and target object files
# -------------------------------------------------------------------

#TARGET=$(basename $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
TARGET=$(basename $(firstword $(MAKEFILE_LIST)))

all: $(TARGET)

OBJ_DIR=$(TARGET)/Debug/obj
BIN_DIR=$(TARGET)/Debug/bin
INFO_DIR=$(TARGET)/Debug/info

# Include folder list
# -------------------------------------------------------------------

INCLUDES =
INCLUDES += -I../inc
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/include
INCLUDES += -I../../../component/common/drivers/sdio/realtek/sdio_host/src
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-core/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/lib/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/rtl_printf/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/shell
INCLUDES += -I../../../component/soc/realtek/8195b/app/stdio_port
INCLUDES += -I../../../component/os/os_dep/include
INCLUDES += -I../../../component/soc/realtek/8195b/misc/utilities/include
INCLUDES += -I../../../component/soc/realtek/8195b/misc/platform
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include/usb_otg
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/video/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/lcdc/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/isp/include
INCLUDES += -I../../../component/common/api
INCLUDES += -I../../../component/common/api/platform
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/include
INCLUDES += -I../../../component/common/file_system/fatfs/r0.14
INCLUDES += -I../../../component/common/file_system/fatfs
INCLUDES += -I../../../component/common/audio/opus-1.3.1/include
INCLUDES += -I../../../component/common/audio/libopusenc-0.2.1/include


# Source file list
# -------------------------------------------------------------------

SRC_C =
SRC_C += ../../../component/common/audio/libopusenc-0.2.1/src/ogg_packer.c
SRC_C += ../../../component/common/audio/libopusenc-0.2.1/src/opus_header.c
SRC_C += ../../../component/common/audio/libopusenc-0.2.1/src/opusenc.c
SRC_C += ../../../component/common/audio/libopusenc-0.2.1/src/resample.c
SRC_C += ../../../component/common/audio/libopusenc-0.2.1/src/unicode_support.c


# User CFLAGS
# -------------------------------------------------------------------
USER_CFLAGS =
USER_CFLAGS += -DOUTSIDE_SPEEX
USER_CFLAGS += -DHAVE_CONFIG_H
USER_CFLAGS += -DDISABLE_FLOAT_API

# Generate obj list
# -------------------------------------------------------------------

SRC_O = $(patsubst %.c,%.o,$(SRC_C))

DEPENDENCY_LIST = 
DEPENDENCY_LIST += $(patsubst %.c,%.d,$(SRC_C))

SRC_C_LIST = $(notdir $(SRC_C))
OBJ_LIST = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(SRC_C_LIST)))

# Compile options
# -------------------------------------------------------------------

CFLAGS =
CFLAGS += -march=armv8-m.main+dsp -mthumb -mcmse -mfloat-abi=softfp -mfpu=fpv5-sp-d16 -g -gdwarf-3 -Os -c -MMD --save-temps
CFLAGS += -nostartfiles -nodefaultlibs -nostdlib -fstack-usage -fdata-sections -ffunction-sections -fno-common
CFLAGS += -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Wno-write-strings -Wno-maybe-uninitialized 
CFLAGS += -D__thumb2__ -DCONFIG_PLATFORM_8195BHP -D__FPU_PRESENT -D__ARM_ARCH_7M__=0 -D__ARM_ARCH_7EM__=0 -D__ARM_ARCH_8M_MAIN__=1 -D__ARM_ARCH_8M_BASE__=0 
CFLAGS += -DCONFIG_BUILD_RAM=1 -DCONFIG_BUILD_LIB=1
CFLAGS += -DV8M_STKOVF
CFLAGS += $(USER_CFLAGS)

# Compile
# -------------------------------------------------------------------

.PHONY: $(TARGET)
$(TARGET): prerequirement $(SRC_O)
	$(AR) rvs $(BIN_DIR)/$(TARGET).a $(OBJ_LIST)
	cp $(BIN_DIR)/$(TARGET).a ../../../component/soc/realtek/8195b/misc/bsp/lib/common/GCC/$(TARGET).a

.PHONY: prerequirement
prerequirement:
	@echo ===========================================================
	@echo Build $(TARGET).a
	@echo ===========================================================
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(SRC_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	#$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(SRAM_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(OBJCOPY) --prefix-alloc-sections .sram $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(ERAM_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(OBJCOPY) --prefix-alloc-sections .eram $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

-include $(DEPENDENCY_LIST)

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -f $(patsubst %.o,%.d,$(SRC_O)) $(patsubst %.o,%.d,$(ERAM_O)) $(patsubst %.o,%.d,$(SRAM_O))
	rm -f $(patsubst %.o,%.su,$(SRC_O)) $(patsubst %.o,%.su,$(ERAM_O)) $(patsubst %.o,%.su,$(SRAM_O))
	rm -f $(SRC_O) $(DRAM_O)
	rm -f *.i
	rm -f *.s