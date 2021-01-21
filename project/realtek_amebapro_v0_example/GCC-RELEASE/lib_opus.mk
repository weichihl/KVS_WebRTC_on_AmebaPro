
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
INCLUDES += -I../../../component/common/drivers/wlan/realtek/include
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/IAR/ARM_RTL8195B
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/include
INCLUDES += -I../../../component/common/file_system/fatfs/r0.14
INCLUDES += -I../../../component/common/file_system/fatfs
INCLUDES += -I../../../component/common/audio/opus-1.3.1/celt
INCLUDES += -I../../../component/common/audio/opus-1.3.1/silk
INCLUDES += -I../../../component/common/audio/opus-1.3.1/silk/fixed
INCLUDES += -I../../../component/common/audio/opus-1.3.1/src
INCLUDES += -I../../../component/common/audio/opus-1.3.1/include


# Source file list
# -------------------------------------------------------------------

SRC_C =
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/A2NLSF.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/ana_filt_bank_1.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/analysis.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/apply_sine_window_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/autocorr_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/bands.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/biquad_alt.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/burg_modified_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/bwexpander.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/bwexpander_32.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/celt.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/celt_decoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/celt_encoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/celt_lpc.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/check_control_input.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/CNG.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/code_signs.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/control_audio_bandwidth.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/control_codec.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/control_SNR.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/corrMatrix_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/cwrs.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/dec_API.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/decode_core.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/decode_frame.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/decode_indices.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/decode_parameters.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/decode_pitch.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/decode_pulses.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/decoder_set_fs.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/enc_API.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/encode_frame_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/encode_indices.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/encode_pulses.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/entcode.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/entdec.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/entenc.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/find_LPC_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/find_LTP_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/find_pitch_lags_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/find_pred_coefs_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/gain_quant.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/HP_variable_cutoff.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/init_decoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/init_encoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/inner_prod_aligned.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/interpolate.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/k2a_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/k2a_Q16_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/kiss_fft.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/laplace.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/lin2log.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/log2lin.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/LP_variable_cutoff.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/LPC_analysis_filter.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/LPC_fit.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/LPC_inv_pred_gain.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/LTP_analysis_filter_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/LTP_scale_ctrl_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/mapping_matrix.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/mathops.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/mdct.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/mlp.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/mlp_data.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/modes.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF2A.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF_decode.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF_del_dec_quant.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF_encode.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF_stabilize.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF_unpack.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF_VQ.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NLSF_VQ_weights_laroia.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/noise_shape_analysis_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NSQ.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/NSQ_del_dec.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus_decoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus_encoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus_multistream.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus_multistream_decoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus_multistream_encoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus_projection_decoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/opus_projection_encoder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/pitch.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/pitch_analysis_core_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/pitch_est_tables.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/PLC.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/process_gains_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/process_NLSFs.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/quant_bands.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/quant_LTP_gains.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/rate.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/regularize_correlations_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/src/repacketizer.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler_down2.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler_down2_3.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler_private_AR2.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler_private_down_FIR.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler_private_IIR_FIR.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler_private_up2_HQ.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/resampler_rom.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/residual_energy16_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/residual_energy_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/schur64_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/schur_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/shell_coder.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/sigm_Q15.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/sort.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/stereo_decode_pred.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/stereo_encode_pred.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/stereo_find_predictor.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/stereo_LR_to_MS.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/stereo_MS_to_LR.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/stereo_quant_pred.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/sum_sqr_shift.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/table_LSF_cos.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/tables_gain.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/tables_LTP.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/tables_NLSF_CB_NB_MB.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/tables_NLSF_CB_WB.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/tables_other.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/tables_pitch_lag.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/tables_pulses_per_block.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/VAD.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/vector_ops_FIX.c
SRC_C += ../../../component/common/audio/opus-1.3.1/celt/vq.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/VQ_WMat_EC.c
SRC_C += ../../../component/common/audio/opus-1.3.1/silk/fixed/warped_autocorrelation_FIX.c


# User CFLAGS
# -------------------------------------------------------------------
USER_CFLAGS =
USER_CFLAGS += -DFIXED_POINT=1
USER_CFLAGS += -DOPUS_BUILD=1
USER_CFLAGS += -DNONTHREADSAFE_PSEUDOSTACK

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