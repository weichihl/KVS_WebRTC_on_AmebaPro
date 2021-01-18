
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
INCLUDES += -I../../../lib_amazon/iar_include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/client/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/common/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/heap/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/state/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/trace/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/view/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/mkvgen/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include/portable/realtek/rtl8195
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include/FreeRTOS_POSIX__
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include/private
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/include
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/include
INCLUDES += -I../../../component/common/api
INCLUDES += -I../../../component/common/api/platform
INCLUDES += -I../../../component/common/api/network/include
INCLUDES += -I../../../component/common/api/wifi
INCLUDES += -I../../../component/common/network/ssl/mbedtls-2.16.6/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/freertos
INCLUDES += -I../../../component/common/network/ssl/ssl_ram_map/rom
INCLUDES += -I../../../lib_amazon/libwebsockets/include
INCLUDES += -I../../../lib_amazon/libwebsockets
INCLUDES += -I../../../component/common/file_system/fatfs/r0.14
INCLUDES += -I../../../component/common/file_system/fatfs


# Source file list
# -------------------------------------------------------------------

SRC_C =

#state
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/state/src/State.c
#utils
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Allocators.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Atomics.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Base64.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/BitField.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/BitReader.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Crc32.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Directory.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/DoubleLinkedList.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/DynamicLibrary.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Endianness.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/FileIo.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/FileLogger.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/HashTable.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Hex.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/InstrumentedAllocators.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Logger.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Mutex.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Semaphore.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/SingleLinkedList.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/StackQueue.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/String.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Tags.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Thread.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Time.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/TimerQueue.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/src/Version.c

#lws
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/Lws/LwsCall.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/Lws/LwsIotCredentialProvider.c
#common
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/Auth.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/AwsV4Signer.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/FileCredentialProvider.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/IotCredentialProvider.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/jsmn.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/RequestInfo.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/StaticCredentialProvider.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/Util.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/source/Common/Version_c.c

# User CFLAGS
# -------------------------------------------------------------------
USER_CFLAGS =
USER_CFLAGS += -D__IEEE_LITTLE_ENDIAN
USER_CFLAGS += -DKVS_USE_MBEDTLS
USER_CFLAGS += -DKVS_BUILD_WITH_LWS
USER_CFLAGS += -DLWS_AMAZON_RTOS

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