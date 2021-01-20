
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
INCLUDES += -I../../../lib_amazon/libwebsockets
INCLUDES += -I../../../lib_amazon/libwebsockets/include
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/core
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/core-net
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/event-libs
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/event-libs/poll
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/plat/freertos
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/plat/freertos/esp32
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/h1
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/h2
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/http
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/ws
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/system/smd
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include/internal
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include/openssl
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include/platform
INCLUDES += -I../../../component/common/network/ssl/mbedtls-2.16.6/include
INCLUDES += -I../../../component/common/network/ssl/ssl_ram_map/rom
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/secure
INCLUDES += -I../../../component/os/os_dep/include
INCLUDES += -I../../../component/common/api
INCLUDES += -I../../../component/common/api/platform
INCLUDES += -I../../../component/common/api/network/include
INCLUDES += -I../../../component/common/api/wifi
INCLUDES += -I../../../component/soc/realtek/8195b/misc/utilities/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-core/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/rtl_printf/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/lib/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/stdio_port
INCLUDES += -I../../../component/soc/realtek/8195b/misc/utilities/include
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/hal_ext
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/targets/hal/rtl8195bh
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include/usb_otg
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/include/usb_otg
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/isp/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/freertos
INCLUDES += -I../../../component/common/file_system/fatfs
INCLUDES += -I../../../component/common/file_system/fatfs/r0.14
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include/portable/realtek/rtl8195
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include/private


# Source file list
# -------------------------------------------------------------------

SRC_C =

###core
SRC_C += ../../../lib_amazon/libwebsockets/lib/core/alloc.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core/buflist.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core/context.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core/libwebsockets.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core/logs.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core/lws_dll2.c
###core-net
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/adopt.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/client.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/close.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/connect.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/dummy-callback.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/network.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/output.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/pollfd.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/sequencer.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/service.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/sorted-usec-list.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/state.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/vhost.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/wsi-timeout.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/core-net/wsi.c
###event-libs
SRC_C += ../../../lib_amazon/libwebsockets/lib/event-libs/poll/poll.c
###misc
SRC_C += ../../../lib_amazon/libwebsockets/lib/misc/base64-decode.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/misc/lejp.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/misc/lws-ring.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/misc/lwsac/lwsac.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/misc/romfs.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/misc/sha-1.c
###plat
SRC_C += ../../../lib_amazon/libwebsockets/lib/plat/freertos/freertos-fds.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/plat/freertos/freertos-init.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/plat/freertos/freertos-misc.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/plat/freertos/freertos-pipe.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/plat/freertos/freertos-service.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/plat/freertos/freertos-sockets.c
###roles
##h1
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/h1/ops-h1.c
##h2
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/h2/hpack.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/h2/http2.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/h2/ops-h2.c
##http
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/http/client/client-handshake.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/http/client/client-http.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/http/header.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/http/parsers.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/http/server/ranges.c
##pipe
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/pipe/ops-pipe.c
##raw
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/raw-file/ops-raw-file.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/raw-skt/ops-raw-skt.c
##ws
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/ws/client-parser-ws.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/ws/client-ws.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/roles/ws/ops-ws.c
###system
SRC_C += ../../../lib_amazon/libwebsockets/lib/system/smd/smd.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/system/system.c
###tls
##mbedtls
#wrapper
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/library/ssl_cert.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/library/ssl_lib.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/library/ssl_methods.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/library/ssl_pkey.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/platform/ssl_pm.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/platform/ssl_port.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/library/ssl_stack.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/library/ssl_x509.c
##mbedtls
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/mbedtls-client.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/mbedtls-ssl.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/mbedtls-tls.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/mbedtls/mbedtls-x509.c
###tls
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/tls-client.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/tls-network.c
SRC_C += ../../../lib_amazon/libwebsockets/lib/tls/tls.c


# User CFLAGS
# -------------------------------------------------------------------
USER_CFLAGS =
USER_CFLAGS += -DLWS_AMAZON_RTOS
USER_CFLAGS += -DLWS_RTK_PLATFORM

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