
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
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/secure
INCLUDES += -I../../../component/os/os_dep/include
INCLUDES += -I../../../component/soc/realtek/8195b/misc/utilities/include
INCLUDES += -I../../../component/soc/realtek/8195b/misc/platform
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include/usb_otg
INCLUDES += -I../../../component/common/api
INCLUDES += -I../../../component/common/api/at_cmd
INCLUDES += -I../../../component/common/api/platform
INCLUDES += -I../../../component/common/api/wifi
INCLUDES += -I../../../component/common/api/network/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/freertos
INCLUDES += -I../../../component/common/network
INCLUDES += -I../../../component/common/drivers/wlan/realtek/include
INCLUDES += -I../../../component/common/drivers/wlan/realtek/src/osdep
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/hal
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/hal_ext
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-drivers/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/include
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/targets/hal/rtl8195bh
INCLUDES += -I../../../component/common/drivers/sdio/realtek/sdio_host/inc
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-core/include
INCLUDES += -I../../../component/soc/realtek/8195a/fwlib/rtl8195a
INCLUDES += -I../../../component/soc/realtek/8195a/misc/os
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/targets/hal/rtl8195bh
INCLUDES += -I../../../component/common/api/wifi/rtw_wpa_supplicant/src
INCLUDES += -I../../../component/soc/realtek/8711b/swlib/std_lib/include
INCLUDES += -I../../../component/common/network/ssl/mbedtls-2.16.6/include
INCLUDES += -I../../../component/common/network/ssl/ssl_ram_map/rom
INCLUDES += -I../../../component/common/drivers/i2s
INCLUDES += -I../../../component/common/utilities
INCLUDES += -I../../../component/common/application
INCLUDES += -I../../../component/soc/realtek/8195b/app/xmodem/rom
INCLUDES += -I../../../component/common/mbed/hal
INCLUDES += -I../../../component/common/mbed/hal_ext
INCLUDES += -I../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh
INCLUDES += -I../../../component/soc/realtek/8195b/misc/driver
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include/portable/realtek/rtl8195
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include/private
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/utils/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/logging/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/wifi/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/unity/src
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/unity/extras/fixture/src
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/platform/freertos/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/platform/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/secure_sockets/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include/private
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/pkcs11/corePKCS11/source/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/pkcs11/corePKCS11/source/dependency/3rdparty/pkcs11
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include/private
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include/private
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/backoff_algorithm/source/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/interface
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/transport/secure_sockets
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/coreMQTT/source/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/jsmn
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls_utils
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls_config______
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls/include______
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/crypto/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/demos/dev_mode_key_provisioning/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/defender/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/serializer/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/test/access
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/dependency/3rdparty/http_parser
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/https/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/https/test/access
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/test/mock
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/src
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/tls/include
INCLUDES += -I../../../common/application/amazon/amazon-freertos-202012.00/demos/common/pkcs11_helpers
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/demos/common/pkcs11_helpers
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/demos/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/demos/network_manager
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/aws_demos/config_files
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/demos/common/http_demo_helpers
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/device_shadow_for_aws/source/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/coreJSON/source/include
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/demos/common/mqtt_demo_helpers
INCLUDES += -I../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/test


# Source file list
# -------------------------------------------------------------------

SRC_C =

###libraries
##3rdparty
#jsmn
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/jsmn/jsmn.c
#mbedtls_utils
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls_utils/mbedtls_error.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls_utils/mbedtls_utils.c
#tinycbor
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborencoder.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborencoder_close_container_checked.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborerrorstrings.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborparser.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborparser_dup_string.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborpretty.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborpretty_stdio.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src/cborvalidation.c
#unity
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/unity/src/unity.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/3rdparty/unity/extras/fixture/src/unity_fixture.c
##abstractions
#backoff_algorithm
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/backoff_algorithm/source/backoff_algorithm.c
#pkcs11
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/pkcs11/corePKCS11/source/portable/mbedtls/core_pkcs11_mbedtls.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/pkcs11/corePKCS11/source/core_pkcs11.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/pkcs11/corePKCS11/source/core_pki_utils.c
#platform - freertos
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/platform/freertos/iot_clock_freertos.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/platform/freertos/iot_metrics.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/platform/freertos/iot_network_freertos.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/platform/freertos/iot_threads_freertos.c
#transport - secure_sockets
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/abstractions/transport/secure_sockets/transport_secure_sockets.c
##c_sdk
#aws - defender
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/defender/src/aws_iot_defender_api.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/defender/src/aws_iot_defender_collector.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/defender/src/aws_iot_defender_mqtt.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/defender/src/aws_iot_defender_v1.c
#shadow
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/src/aws_iot_shadow_api.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/src/aws_iot_shadow_operation.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/src/aws_iot_shadow_parser.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/src/aws_iot_shadow_static_memory.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/src/aws_iot_shadow_subscription.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/src/aws_shadow.c
#standard
#common - taskpool
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/taskpool/iot_taskpool.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/taskpool/iot_taskpool_static_memory.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/iot_device_metrics.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/iot_init.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/iot_static_memory_common.c
#https
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/https/src/iot_https_client.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/https/src/iot_https_utils.c
#mqtt
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_agent.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_api.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_context_connection.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_managed_function_wrapper.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_mutex_wrapper.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_network.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_operation.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_publish_duplicates.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_serializer_deserializer_wrapper.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_static_memory.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_subscription.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_subscription_container.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src/iot_mqtt_validate.c
##coreHTTP
#http_parser
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/dependency/3rdparty/http_parser/http_parser.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/core_http_client.c
##coreJSON
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/coreJSON/source/core_json.c
##coreMQTT
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/coreMQTT/source/core_mqtt.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/coreMQTT/source/core_mqtt_serializer.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/coreMQTT/source/core_mqtt_state.c
##device_shadow_for_aws
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/device_shadow_for_aws/source/shadow.c
##freertos_plus
#aws
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/src/aws_iot_ota_agent.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/src/mqtt/aws_iot_ota_cbor.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/src/aws_iot_ota_interface.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/src/mqtt/aws_iot_ota_mqtt.c
#standard
#crypto
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/crypto/src/iot_crypto.c
#tls
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/tls/src/iot_tls.c
#utils
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/utils/src/iot_system_init.c
##logging
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/logging/iot_logging.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/libraries/logging/iot_logging_task_dynamic_buffers.c

###vendor
##port
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/ports/ota/aws_ota_amebapro.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/ports/ota/aws_ota_pal.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/ports/pkcs11/core_pkcs11_pal.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/ports/secure_sockets/iot_secure_sockets.c
SRC_C += ../../../lib_amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/ports/wifi/iot_wifi.c



# User CFLAGS
# -------------------------------------------------------------------
USER_CFLAGS =
#USER_CFLAGS += -DXXXXXX

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
CFLAGS += -D__thumb2__ -DCONFIG_PLATFORM_8195B -DCONFIG_PLATFORM_8195BHP -D__FPU_PRESENT -D__ARM_ARCH_7M__=0 -D__ARM_ARCH_7EM__=0 -D__ARM_ARCH_8M_MAIN__=1 -D__ARM_ARCH_8M_BASE__=0 
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