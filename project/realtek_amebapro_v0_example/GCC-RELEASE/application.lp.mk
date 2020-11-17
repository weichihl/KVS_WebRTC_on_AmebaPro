
# Initialize tool chain
# -------------------------------------------------------------------
#ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/gcc6/bin/

AMEBAPRO_TOOLDIR	= ../../../component/soc/realtek/8195b/misc/iar_utility
#FLASH_TOOLDIR = ../../../component/soc/realtek/8195a/misc/gcc_utility/

OS := $(shell uname)

ifeq ($(findstring CYGWIN, $(OS)), CYGWIN)
	ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/cygwin/newlib/bin
	ELF2BIN = $(AMEBAPRO_TOOLDIR)/elf2bin.exe
endif

ifeq ($(findstring MINGW32, $(OS)), MINGW32)
	ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/mingw32/newlib/bin
	ELF2BIN = $(AMEBAPRO_TOOLDIR)/elf2bin.exe
endif

ifeq ($(findstring Linux, $(OS)), Linux)
	ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/linux/newlib/bin
	ELF2BIN = $(AMEBAPRO_TOOLDIR)/elf2bin.linux	
endif

#CROSS_COMPILE = $(ARM_GCC_TOOLCHAIN)/arm-none-eabi-
CROSS_COMPILE = $(ARM_GCC_TOOLCHAIN)/arm-none-eabi-

# Compilation tools
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
LD = $(CROSS_COMPILE)gcc
GDB = $(CROSS_COMPILE)gdb
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

OS := $(shell uname)

LDSCRIPT := ./rtl8195blp_ram.ld

# Initialize target name and target object files
# -------------------------------------------------------------------

all: application_lp

#mp: application manipulate_images

TARGET=application_lp

OBJ_DIR=$(TARGET)/Debug/obj
BIN_DIR=$(TARGET)/Debug/bin
INFO_DIR=$(TARGET)/Debug/info

# Include folder list
# -------------------------------------------------------------------

INCLUDES =
INCLUDES += -I../inc

INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-lp/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-core/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/rtl_printf/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/shell
INCLUDES += -I../../../component/soc/realtek/8195b/app/stdio_port
INCLUDES += -I../../../component/soc/realtek/8195b/misc/utilities/include
INCLUDES += -I../../../component/soc/realtek/8195b/misc/driver
INCLUDES += -I../../../component/common/api
INCLUDES += -I../../../component/common/mbed/api
INCLUDES += -I../../../component/common/api/platform
INCLUDES += -I../../../component/os/RTX/INC
INCLUDES += -I../../../component/os/RTX/rom/SRC
INCLUDES += -I../../../component/os/RTX/rtl8195blp
INCLUDES += -I../../../component/os/RTX/rom/rtl8195blp
INCLUDES += -I../../../component/common/mbed/hal
INCLUDES += -I../../../component/common/mbed/hal_ext
INCLUDES += -I../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl


# Source file list
# -------------------------------------------------------------------

SRC_C =
#cmsis
SRC_C += ../../../component/soc/realtek/8195b/cmsis/rtl8195b-lp/source/app_start.c

#console
SRC_C += ../../../component/soc/realtek/8195b/app/shell/cmd_shell.c

#os
SRC_C += ../../../component/os/RTX/rtl8195blp/cmsis_os_stubs.c
SRC_C += ../../../component/os/RTX/rtl8195blp/RTX_Conf_CM.c
SRC_C += ../../../component/os/RTX/rtl8195blp/RTX_os_callback.c

#peripheral - api
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/analogin_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/cir_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/dma_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/efuse_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/gpio_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/gpio_irq_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/i2c_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/icc_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/pinmap.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/pinmap_common.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/power_mode_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/pwmout_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/rtc_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/serial_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/sgpio_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/timer_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/us_ticker.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/us_ticker_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/wait_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bl/wdt_api.c

#hal
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_adc.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_cir.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_comp.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_efuse.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_i2c.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_icc.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_icc_app.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_pwm.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_qdec.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/Hal_rtc.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_sgpio.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_uart.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/source/hal_timer.c


#user
SRC_C += ../src/main_lp.c


# Generate obj list
# -------------------------------------------------------------------

SRC_O = $(patsubst %.c,%.o,$(SRC_C))

DEPENDENCY_LIST =
DEPENDENCY_LIST += $(patsubst %.c,%.d,$(SRC_C))

SRC_C_LIST = $(notdir $(SRC_C)) $(notdir $(DRAM_C))
OBJ_LIST = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(SRC_C_LIST)))

# Compile options
# -------------------------------------------------------------------

CFLAGS =
CFLAGS += -march=armv8-m.base -mthumb -O2 -g -gdwarf-3 --save-temps -c -MMD
CFLAGS += -fstack-usage -fdata-sections -ffunction-sections 
CFLAGS += -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Wno-write-strings -Wno-maybe-uninitialized  
CFLAGS += -D__thumb2__ -DCONFIG_PLATFORM_8195B -DCONFIG_PLATFORM_8195BLP -D__ARM_ARCH_7M__=0 -D__ARM_ARCH_7EM__=0 -D__ARM_ARCH_8M_MAIN__=0 -D__ARM_ARCH_8M_BASE__=1 
CFLAGS += -D__ARM_FEATURE_DSP=0 -D__CORTEX_M0 -DCONFIG_BUILD_RAM=1 
CFLAGS += -DCONFIG_DISABLE_LP_SHELL -DCONFIG_SWWDT_EN=1 -DCONFIG_LS_RESET_REQ_EN=1


LFLAGS = 
LFLAGS += -O2 -march=armv8-m.base -mthumb -mcmse  
LFLAGS += -nostartfiles -nodefaultlibs -nostdlib -specs=nosys.specs 
LFLAGS += -Wl,--gc-sections -Wl,--warn-section-align -Wl,--cref -Wl,--build-id=none -Wl,--use-blx
LFLAGS += -Wl,-Map=$(BIN_DIR)/$(TARGET).map 

LIBFLAGS =
all: LIBFLAGS += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-lp/lib/lib/hal_pmc_lp.a
all: LIBFLAGS += ../../../component/soc/realtek/8195b/misc/bsp/lib/common/GCC/lib_soc_lp.a


RAMALL_BIN =
OTA_BIN = 

# Compile
# -------------------------------------------------------------------

.PHONY: application_lp
#application: prerequirement build_info $(SRC_O) $(DRAM_O)
application_lp: prerequirement $(SRC_O) $(DRAM_O)
	$(LD) $(LFLAGS) -o $(BIN_DIR)/$(TARGET).axf  $(OBJ_LIST) $(LIB_A) $(ROMIMG) $(LIBFLAGS) -T$(LDSCRIPT)
	$(OBJDUMP) -d $(BIN_DIR)/$(TARGET).axf > $(BIN_DIR)/$(TARGET).asm


# Generate build info
# -------------------------------------------------------------------	


.PHONY: prerequirement
prerequirement:
	@echo ===========================================================
	@echo Build $(TARGET)
	@echo ===========================================================
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(INFO_DIR)
	

$(SRC_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	#$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)


-include $(DEPENDENCY_LIST)

# Generate build info
# -------------------------------------------------------------------	
#ifeq (setup,$(firstword $(MAKECMDGOALS)))
#  # use the rest as arguments for "run"
#  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
#  # ...and turn them into do-nothing targets
#  $(eval $(RUN_ARGS):;@:)
#endif



.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -f $(patsubst %.o,%.d,$(SRC_O)) $(patsubst %.o,%.d,$(DRAM_O))
	rm -f $(patsubst %.o,%.su,$(SRC_O)) $(patsubst %.o,%.su,$(DRAM_O))
	rm -f $(SRC_O) $(DRAM_O)
	rm -f *.i
	rm -f *.s