
.PHONY: all clean mk_build_dir build_lib post_process

include $(ROOT_MK)

MKDIR= mkdir

OUTLIB = 

EXT_CC= 

EXT_INC= -I../mbed-hal/hal -I../os/freertos/freertos_v10.0.0/secure -IAlgoObjDetectLib/AlgoHaarDetect_bk -I../hal/hal-rtl8195b-hp/lib/include -IAlgoObjDetectLib/AlgoHaarDetect -I../hal/hal-rtl8195b-hp/lib/video/video/include -I../hal/hal-rtl8195b-hp/lib/video/isp/include -I../hal/hal-rtl8195b-hp/lib/source/ram_ns/usb_otg/device/class/vendor/inc -I../os/utilities/include -I../hal/hal-rtl8195b-hp/lib/video/lcdc/include -I../toggle/AlgoObjDetect -IAlgoObjDetectLib/Common -I../cmsis/cmsis-core/include -I../hal/hal-rtl8195b-hp/lib/source/rom_template -I../os/freertos -I../os/os_dep/include -I../os/freertos/freertos_v10.0.0/include -I../sw/lib/application/apple/WACServer/External/Curve25519 -I../os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B -I../mbed-hal/hal_ext -I../sw/app/xmodem/rom -I../sw/app/shell -I../mbed-hal/targets/hal/rtl8195bh -I../cmsis/rtl8195b-hp/lib/include -IAlgoObjDetectLib/AlgoFullBodyDetect -I../sw/app/shell/rom_ns -I../hal/hal-rtl8195b-hp/include/usb_otg -I../sw/lib/api/platform -I../hal/hal-rtl8195b-hp/lib/include/usb_otg -I../hal/hal-rtl8195b-hp/include -I../hal/hal-rtl8195b-hp/lib/source/ram_ns/usb_otg/device/core/inc -I../mbed-drivers/include -I../hal/hal-rtl8195b-hp/lib/source/ram_ns/usb_otg/device/class/ethernet/inc -I. -I../hal/hal-rtl8195b-hp/lib/video/enc/include -I../hal/hal-rtl8195b-hp/lib/video/vmodel/include -I../sw/app/stdio_port -I../sw/app/rtl_printf/include -I../cmsis/rtl8195b-hp/include -I../cmsis/cmsis-dsp/include -I../sw/lib/application/apple/apple_func_stubs/rom -I../hal/hal-rtl8195b-hp/lib/video/voe/include -I../$(ASDK_DIR)/arm-none-eabi/include

OBJS =  main.o 



CPPSOURCES = 

LIBS= "/cygdrive/c/Work/ameba_pro/ameba_pro_soc_AlgoObjDetect/AlgoObjDetect/AlgoObjDetectLib/libAlgoObjDetectLib.a"

OBJ_LIST = main.o 

all: $(OBJS) obj_copy post_process libs_copy
%.o:%.c
	$(CC) $(EXT_CC) $(EXT_INC) $< -o $@

%.o:%.S
	$(AS) $< -o $@



build_lib:
	$(AR) crv $(LIBOUTDIR)/$(OUTLIB) $(OBJS);
	for f in $(OBJ_LIST); do \
		if [ -a $(OBJOUTDIR)/$$f ];\
		then\
			rm $(OBJOUTDIR)/$$f; \
		fi;\
	done


obj_copy:
	-cp -f $(OBJS) $(OBJCOPYDIR);


post_process:
	-mv -f *.s $(OBJCOPYDIR);
	-mv -f *.i $(OBJCOPYDIR);


libs_copy:
	-cp -f $(LIBS) $(LIBOUTDIR);

clean:


-include $(patsubst %.o,%.d,$(OBJS))
