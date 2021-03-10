
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
INCLUDES += -I../../../lib_amazon/gcc_include
INCLUDES += -I../../../component/os/os_dep/include
INCLUDES += -I../../../component/common/api
INCLUDES += -I../../../component/common/api/platform
INCLUDES += -I../../../component/common/api/network/include
INCLUDES += -I../../../component/common/api/wifi
INCLUDES += -I../../../component/common/network/ssl/mbedtls-2.16.6/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include/posix
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/freertos
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek
INCLUDES += -I../../../component/common/network/ssl/ssl_ram_map/rom
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include/portable/realtek/rtl8195
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include/FreeRTOS_POSIX__
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include/private
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/include
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/client/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/common/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/heap/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/state/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/trace/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/view/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/mkvgen/include
INCLUDES += -I../../../lib_amazon/libwebsockets/include
INCLUDES += -I../../../lib_amazon/libwebsockets
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/include
INCLUDES += -I../../../lib_amazon/libsrtp/include
INCLUDES += -I../../../component/common/file_system/fatfs/r0.14
INCLUDES += -I../../../component/common/file_system/fatfs
INCLUDES += -I../../../lib_amazon/libusrsctp/usrsctplib
INCLUDES += -I../../../lib_amazon/libusrsctp/usrsctplib/netinet
INCLUDES += -I../../../lib_amazon/libusrsctp/usrsctplib/netinet6


# Source file list
# -------------------------------------------------------------------

SRC_C =

##crypto
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Crypto/Dtls.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Crypto/Dtls_mbedtls.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Crypto/IOBuffer.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Crypto/Tls.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Crypto/Tls_mbedtls.c
##ice
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/ConnectionListener.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/IceAgent.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/IceAgentStateMachine.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/IceUtils.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/NatBehaviorDiscovery.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/Network.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/SocketConnection.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Ice/TurnConnection.c
##metrics
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Metrics/Metrics.c
##PeerConnection
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/DataChannel.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/JitterBuffer.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/jsmn.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/PeerConnection.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/Retransimitter.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/Rtcp.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/Rtp.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/PeerConnection/SessionDescription.c
##Rtcp
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtcp/RollingBuffer.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtcp/RtcpPacket.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtcp/RtpRollingBuffer.c
##Rtp
#Codecs
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtp/Codecs/RtpG711Payloader.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtp/Codecs/RtpH264Payloader.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtp/Codecs/RtpOpusPayloader.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtp/Codecs/RtpVP8Payloader.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Rtp/RtpPacket.c
##Sctp
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Sctp/Sctp.c
##Sdp
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Sdp/Deserialize.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Sdp/Serialize.c
##signaling
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Signaling/ChannelInfo.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Signaling/Client.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Signaling/FileCache.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Signaling/LwsApiCalls.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Signaling/Signaling.c
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Signaling/StateMachine.c
##Srtp
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Srtp/SrtpSession.c
##Stun
SRC_C += ../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/source/Stun/Stun.c



# User CFLAGS
# -------------------------------------------------------------------
USER_CFLAGS =
USER_CFLAGS += -D__IEEE_LITTLE_ENDIAN
USER_CFLAGS += -DKVS_USE_MBEDTLS
USER_CFLAGS += -DKVS_BUILD_WITH_LWS
USER_CFLAGS += -DKVS_PLAT_RTK_FREERTOS
USER_CFLAGS += -DLWS_RTK_PLATFORM
USER_CFLAGS += -DLWS_AMAZON_RTOS
USER_CFLAGS += -DBUILD_CLIENT
USER_CFLAGS += -DENABLE_STREAMING
USER_CFLAGS += -DENABLE_DATA_CHANNEL___

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