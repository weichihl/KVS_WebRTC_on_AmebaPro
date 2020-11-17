/* Linker script to configure memory regions. */
MEMORY
{
  ROM (rx) 				: ORIGIN = 0x00000000, LENGTH = 0x0002E800
  ROM_STUB (rx) 		: ORIGIN = 0x0002E800, LENGTH = 0x00030000 - 0x0002E800
  DTCM_RAM (wrx) 		: ORIGIN = 0x20000000, LENGTH = 0x00001000
  VECTORS_RAM (rwx)     : ORIGIN = 0x20200000, LENGTH = 0x00000100
  ROM_USED_RAM (rwx)    : ORIGIN = 0x20200100, LENGTH = 0x20200600 - 0x20200100
  RAM_IMG_SIGN (rwx)    : ORIGIN = 0x20200600, LENGTH = 0x20200610 - 0x20200600
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x20200610, LENGTH = 0x20200800 - 0x20200610
  RAM (rwx)             : ORIGIN = 0x20200800, LENGTH = 0x2020C000 - 0x20200800
}

/* Library configurations */
GROUP(libgcc.a libc.a libm.a libnosys.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __copy_table_start__
 *   __copy_table_end__
 *   __zero_table_start__
 *   __zero_table_end__
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 *   __Vectors_End
 *   __Vectors_Size
 */
ENTRY(Reset_Handler)

SECTIONS
{
	.rom.text :
	{
		KEEP(*(.rom.vectors))
		__Vectors_End = .;
		__Vectors_Size = __Vectors_End - __Vectors;
		__end__ = .;

		. = ALIGN(0x100);

		KEEP(*(.startup.text))
		KEEP(*(.vector.text))
		KEEP(*(.rom.irq.rodata))
		KEEP(*(.sysstart.text))
		KEEP(*(.sys_misc.text))
		KEEP(*startup.o(.rodata*))

		/**** HAL ROM Code ****/
		KEEP(*(.rom.hal_uart.text))
		KEEP(*(.rom.hal_uart.rodata))
		KEEP(*(.rom.hal_timer.text))
		KEEP(*(.rom.hal_timer.rodata))
		KEEP(*(.rom.hal_timer_ba.rodata))
		KEEP(*(.rom.hal_pwm.text))
		KEEP(*(.rom.hal_pwm.rodata))
		KEEP(*(.rom.hal_rtc.text))
		KEEP(*(.rom.hal_rtc.rodata))
		KEEP(*(.rom.hal_chg.text))
		KEEP(*(.rom.hal_chg.rodata))
		KEEP(*(.rom.hal_gdma.text))
		KEEP(*(.rom.hal_gdma.text))
		KEEP(*(.rom.hal_gdma.rodata))
		KEEP(*(.rom.hal_gpio.text))
		KEEP(*(.rom.hal_gpio.rodata))
		KEEP(*(.rom.hal_qdec.text))
		KEEP(*(.rom.hal_qdec.rodata))
		KEEP(*(.rom.hal_sgpio.text))	
		KEEP(*(.rom.hal_sgpio.rodata))		
		KEEP(*(.rom.hal_cir.text))	
		KEEP(*(.rom.hal_cir.rodata))	
				
		KEEP(*(.rom.hal_icc.text))
		KEEP(*(.rom.hal_icc.rodata))
		KEEP(*(.rom.hal_adc.text))
		KEEP(*(.rom.hal_adc.rodata))
		KEEP(*(.rom.hal_comp.text))
		KEEP(*(.rom.hal_comp.rodata))
		KEEP(*(.rom.hal_i2c.text))
		KEEP(*(.rom.hal_i2c.rodata))
		KEEP(*(.rom.hal_efuse.text))
		KEEP(*(.rom.hal_efuse.rodata))
		KEEP(*(.rom.hal_syson.text))
		KEEP(*(.rom.hal_syson.rodata))
        KEEP(*(.rom.hal_spic.text))
		KEEP(*(.rom.hal_spic.rodata))
    	KEEP(*(.rom.hal_flash.text))
		KEEP(*(.rom.hal_flash.rodata))
    	KEEP(*(.rom.hal_lpi.text))
		KEEP(*(.rom.hal_lpi.rodata))
		
		KEEP(*rtl8195blp_cir.o(.text*))
		KEEP(*rtl8195blp_cir.o(.rodata*))
		KEEP(*rtl8195blp_adc.o(.text*))
		KEEP(*rtl8195blp_adc.o(.rodata*))
		KEEP(*rtl8195blp_comp.o(.text*))
		KEEP(*rtl8195blp_comp.o(.rodata*))
		KEEP(*rtl8195blp_pinmux.o(.text*))
		KEEP(*rtl8195blp_pinmux.o(.rodata))
		KEEP(*rtl8195blp_i2c.o(.text*))
		KEEP(*rtl8195blp_i2c.o(.rodata*))
		
		KEEP(*rtl8195blp_uart.o(.rodata*))
		KEEP(*rtl8195blp_timer.o(.rodata*))
		KEEP(*rtl8195blp_pwm.o(.rodata*))
		KEEP(*rtl8195blp_rtc.o(.rodata*))
		KEEP(*rtl8195blp_chg.o(.rodata*))
		KEEP(*rtl8195blp_gpio.o(.rodata*))
		KEEP(*rtl8195blp_qdec.o(.rodata*))
		KEEP(*rtl8195blp_lpi.o(.rodata*))

		/**** Utility ROM code ****/
		KEEP(*(.infra.rom.text))
		KEEP(*(.stdioport.text))
		KEEP(*(.xprintf.text))
		KEEP(*(.xprintf.rodata))
		KEEP(*(.rtlprintf.text))
		KEEP(*(.rtlprintf.rodata))
		KEEP(*(.logbuf.text))
		KEEP(*(.shell.text))
		KEEP(*(.shell.rodata))
		KEEP(*(.shellcmd.text))
		KEEP(*(.shellcmd.rodata))
		KEEP(*(.ccmd.text))
		KEEP(*(.ccmd.rodata))
		KEEP(*(.rom.utility.text*))

		KEEP(*xprintf.o(.rodata*))
		KEEP(*rtl_printf.o(.rodata*))
		KEEP(*strproc.o(.text*))
		KEEP(*strproc.o(.rodata*))
		KEEP(*atoi.o(.text*))
		KEEP(*atoi.o(.rodata*))
		KEEP(*scanf.o(.text*))
		KEEP(*scanf.o(.rodata*))

		/**** RTX rtos Code ****/
		__rtx_text_start = .;
		KEEP(*HAL_CM.o(.text*))
		KEEP(*rt_CMSIS.o(.text*))
		KEEP(*rt_Event.o(.text*))
		KEEP(*rt_List.o(.text*))
		KEEP(*rt_Mailbox.o(.text*))
		KEEP(*rt_MemBox.o(.text*))
		KEEP(*rt_Memory.o(.text*))
		KEEP(*rt_Mutex.o(.text*))
		KEEP(*rt_Robin.o(.text*))
		KEEP(*rt_Semaphore.o(.text*))
		KEEP(*rt_System.o(.text*))
		KEEP(*rt_Task.o(.text*))
		KEEP(*rt_Time.o(.text*))
		KEEP(*rt_Timer.o(.text*))
		KEEP(*HAL_CM0.o(.text*))
		KEEP(*SVC_Table.o(.text*))
		__rtx_text_end = .;

		KEEP(*rtx_service_rom.o(.text*))
		KEEP(*rtx_service_rom.o(.rodata*))

		__lib_gcc_start = .;
		*_arm_cmpdf2.o(.text*)
		*_aeabi_uldivmod.o(.text*)
		*_aeabi_ldivmod.o(.text*)
		*_aeabi_*.o(.text*)
		*bpabi.o(.text*)
		*_muldi3.o(.text*)
		*_divdi3.o(.text*)
		*_fixunsdfsi.o(.text*)
		*_fixdfdi.o(.text*)
		*_fixunsdfdi.o(.text*)
		*_floatdidf.o(.text*)
		*_floatundidf.o(.text*)
		*_udivmoddi4.o(.text*)
		*adddf3.o(.text*)
		*divdf3.o(.text*)
		*eqdf2.o(.text*)
		*gedf2.o(.text*)
		*ledf2.o(.text*)
		*muldf3.o(.text*)
		*subdf3.o(.text*)
		*fixdfsi.o(.text*)
		*floatsidf.o(.text*)
		*floatunsidf.o(.text*)
		*truncdfsf2.o(.text*)
		*_thumb1_case_uhi.o(.text*)
		*_dvmd_tls.o(.text*)
		*_clzsi2.o(.text*)
		*divsf3.o(.text*)
		*mulsf3.o(.text*)
		*addsf3.o(.text*)
		*subsf3.o(.text*)
		*extendsfdf2.o(.text*)
		*_thumb1_case_uqi.o(.text*)
		*floatsisf.o(.text*)
		*_fixunssfsi.o(.text*)
		*fixsfsi.o(.text*)
		*floatunsisf.o(.text*)
		*_arm_cmpsf2.o(.text*)
		*eqsf2.o(.text*)
		*gesf2.o(.text*)
		*lesf2.o(.text*)
		*lib_a-*.o(.text*)
		*lib_a-*.o(.rodata*)
		__lib_gcc_end = .;
		
		KEEP(*(.init))
		KEEP(*(.fini))

		/* .ctors */
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

		/* .dtors */
 		*crtbegin.o(.dtors)
 		*crtbegin?.o(.dtors)
 		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
 		*(SORT(.dtors.*))
 		*(.dtors)

		KEEP(*startup_rtl8195blp.o(.rodata.str1*))
		KEEP(*startup.o(.rodata.str1*))
		KEEP(*consol_cmds.o(.rodata.str1*))
		KEEP(*shell.o(.rodata.str1*))
		KEEP(*xprintf.o(.rodata.str1*))
		KEEP(*rtl_printf.o(.rodata.str1*))
		KEEP(*utility.o(.rodata.str1*))
		KEEP(*rtx_service_rom.o(.rodata.str1*))

		KEEP(*rtl8195blp_irq.o(.rodata.str1*))
		KEEP(*rtl8195blp_timer.o(.rodata.str1*))
		KEEP(*rtl8195blp_pwm.o(.rodata.str1*))
		KEEP(*rtl8195blp_rtc.o(.rodata.str1*))
		KEEP(*rtl8195blp_chg.o(.rodata.str1*))
		KEEP(*rtl8195blp_uart.o(.rodata.str1*))
		KEEP(*rtl8195blp_uart.o(.rodata*))		
		KEEP(*rtl8195blp_gdma.o(.rodata.str1*))
		KEEP(*rtl8195blp_gpio.o(.rodata.str1*))
		KEEP(*rtl8195blp_icc.o(.rodata.str1*))
		KEEP(*rtl8195blp_syson.o(.rodata.str1*))
		KEEP(*rtl8195blp_cir.o(.rodata.str1*))
		KEEP(*rtl8195blp_adc.o(.rodata.str1*))
		KEEP(*rtl8195blp_comp.o(.rodata.str1*))
		KEEP(*rtl8195blp_i2c.o(.rodata.str1*))
		KEEP(*rtl8195blp_qdec.o(.rodata.str1*))
		KEEP(*rtl8195blp_sgpio.o(.rodata.str1*))		
		KEEP(*rtl8195blp_flash.o(.rodata.str1*))
		KEEP(*rtl8195blp_spic.o(.rodata.str1*))
		KEEP(*rtl8195blp_efuse.o(.rodata.str1*))
		KEEP(*rtl8195blp_pinmux.o(.rodata.str1*))
		KEEP(*rtl8195blp_lpi.o(.rodata.str1*))
		KEEP(*rtl8195blp_*.o(.rodata.str1*))
		KEEP(*rtl8195blp_*.o(.rodata*))

		KEEP(*scanf.o(.rodata.str1*))

		KEEP(*(.eh_frame*))
	} > ROM

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > ROM

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > ROM
	__exidx_end = .;

	/* To copy multiple ROM to RAM sections,
	 * uncomment .copy.table section and,
	 * define __STARTUP_COPY_MULTIPLE in startup_ARMCMx.S */
	/*	
	.copy.table :
	{
		. = ALIGN(4);
		__copy_table_start__ = .;
		LONG (__etext)
		LONG (__data_start__)
		LONG (__data_end__ - __data_start__)
		LONG (__etext2)
		LONG (__ram_code_text_start__)
		LONG (__ram_code_text_end__ - __ram_code_text_start__)
		__copy_table_end__ = .;
	} > ROM
	*/	
	. = ALIGN(4);
	__rom_etext = .;

	/* To clear multiple BSS sections,
	 * uncomment .zero.table section and,
	 * define __STARTUP_CLEAR_BSS_MULTIPLE in startup_ARMCMx.S */
	/*
	.zero.table :
	{
		. = ALIGN(4);
		__zero_table_start__ = .;
		LONG (__bss_start__)
		LONG (__bss_end__ - __bss_start__)
		LONG (__bss2_start__)
		LONG (__bss2_end__ - __bss2_start__)
		__zero_table_end__ = .;
	} > ROM
	*/

	.note.gnu.build-id :
	{
		*(.note.gnu.build-id)
	} > ROM

	.rom.stubs :
	{
		. = ALIGN(0x10);
		__rom_stubs_int_vector = .;
		KEEP(*(.rom.hal_vector.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_syson = .;
		KEEP(*(.rom.hal_syson.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_timer = .;
		KEEP(*(.rom.hal_timer.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_pwm = .;
		KEEP(*(.rom.hal_pwm.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_rtc = .;
		KEEP(*(.rom.hal_rtc.stubs))
		
		. = ALIGN(0x10);
		__rom_stubs_hal_chg = .;
		KEEP(*(.rom.hal_chg.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_uart = .;
		KEEP(*(.rom.hal_uart.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_gpio = .;
		KEEP(*(.rom.hal_gpio.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_icc = .;
		KEEP(*(.rom.hal_icc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_adc = .;
		KEEP(*(.rom.hal_adc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_gdma = .;
		KEEP(*(.rom.hal_gdma.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_spic = .;
		KEEP(*(.rom.hal_spic.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_flash = .;
		KEEP(*(.rom.hal_flash.stubs))
						
		. = ALIGN(0x10);
		__rom_stubs_hal_comp = .;
		KEEP(*(.rom.hal_comp.stubs))
		
		. = ALIGN(0x10);
		__rom_stubs_hal_efuse = .;
		KEEP(*(.rom.hal_efuse.stubs))

        	. = ALIGN(0x10);
		__rom_stubs_hal_pinmux = .;
		KEEP(*(.rom.hal_pinmux.stubs))
		
		. = ALIGN(0x10);
		__rom_stubs_hal_i2c = .;
		KEEP(*(.rom.hal_i2c.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_cir = .;	
		KEEP(*(.rom.hal_cir.stubs))
		
		. = ALIGN(0x10);
		__rom_stubs_hal_qdec = .;	
		KEEP(*(.rom.hal_qdec.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_sgpio = .;	
		KEEP(*(.rom.hal_sgpio.stubs))		
		
		. = ALIGN(0x10);
		__rom_stubs_shell = .;
		KEEP(*(.rom.shellcmd.stubs))

		. = ALIGN(0x10);
		__rom_stubs_cmsis_rtx = .;
		KEEP(*(.rom.cmsisrtx.stubs))

		. = ALIGN(0x10);
		__rom_stubs_stdprintf = .;
		KEEP(*(.rom.printf.stubs))

		. = ALIGN(0x10);
		__rom_stubs_strproc = .;
		KEEP(*(.rom.strproc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_utility = .;
		KEEP(*(.rom.utility.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_misc = .;
		KEEP(*(.rom.hal_misc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_lpi = .;
		KEEP(*(.rom.hal_lpi.stubs))

		. = ALIGN(0x10);
		__rom_stubs_rtx_service = .;
		KEEP(*(.rom.rtx_service.stubs))

	} > ROM_STUB


/************* End of ROM **************/

	.ram.vector :
	{
		. = ALIGN(4);
		__ram_vector_start__ = .;
		KEEP(*(.ram_vector_table))
		__ram_vector_end__ = .;
		. = ALIGN(4);
	} > VECTORS_RAM

	.data_of_rom : AT (__rom_etext)		/* for ROM image building */
/*	.data_of_rom :						/* for RAM image building */
	{
		. = ALIGN(16);
		__rom_data_start__ = .;
		/* RTX data */
		KEEP(*rt_CMSIS.o(.data*))
		KEEP(*rt_Robin.o(.data*))
		KEEP(*rt_System.o(.data*))
		KEEP(*rt_Task.o(.data*))
		KEEP(*rt_Time.o(.data*))
		KEEP(*rtx_service_rom.o(.data*))
		
		/**** ROM data ****/
		KEEP(*(.rom.hal_uart.data))
		KEEP(*(.rom.hal_timer.data))
		KEEP(*(.rom.hal_pwm.data))
		KEEP(*(.rom.hal_rtc.data))
		KEEP(*(.rom.hal_chg.data))
		KEEP(*(.rom.hal_gpio.data))
		KEEP(*(.rom.hal_adc.data))
		KEEP(*(.rom.hal_comp.data))
		KEEP(*(.rom.hal_efuse.data))
		KEEP(*(.rom.hal_i2c.data))
		KEEP(*(.rom.hal_cir.data))
		KEEP(*(.rom.hal_qdec.data))	
		KEEP(*(.rom.hal_sgpio.data))		
		KEEP(*(.xprintf.data))

		KEEP(*rtl8195blp_flash.o(.data*))
		KEEP(*rtl8195blp_qdec.o(.data*))
		KEEP(*rtl8195blp_adc.o(.data*))
		KEEP(*rtl8195blp_comp.o(.data*))
		KEEP(*rtl8195blp_i2c.o(.data*))
		KEEP(*rtl8195blp_rtc.o(.data*))
		KEEP(*rtl8195blp_chg.o(.data*))
		/* All ROM data end */
		__rom_data_end__ = .;

	} > ROM_USED_RAM

	.bss_of_rom (NOLOAD) :
	{
		. = ALIGN(4);
		
		/**** ROM BSS ****/
		__rom_bss_start__ = .;
		
		KEEP(*(.sysstart.bss))
		KEEP(*(.sys_misc.bss))
		KEEP(*(.rom.irq.bss))
		KEEP(*(.diag.bss))
		KEEP(*(.rom.hal_uart.bss))
		KEEP(*(.rom.hal_syson.bss))
		KEEP(*(.rom.hal_timer.bss))
		KEEP(*(.rom.hal_pwm.bss))
		KEEP(*(.rom.hal_rtc.bss))
		KEEP(*(.rom.hal_chg.bss))
		KEEP(*(.rom.hal_gpio.bss))
		KEEP(*(.rom.hal_adc.bss))
  		KEEP(*(.rom.hal_gdma.bss))
 		KEEP(*(.rom.hal_spic.bss))
		KEEP(*(.rom.hal_flash.bss)) 		
		KEEP(*(.rom.hal_comp.bss))
		KEEP(*(.rom.hal_efuse.bss))
		KEEP(*(.rom.hal_pinmux.bss))
		KEEP(*(.rom.hal_i2c.bss))
		KEEP(*(.rom.hal_cir.bss))
		KEEP(*(.rom.hal_qdec.bss))
		KEEP(*(.rom.hal_sgpio.bss))		
		KEEP(*(.rom.hal_icc.bss))		
		KEEP(*(.rom.hal_lpi.bss))		
		KEEP(*(.xprintf.bss))
		KEEP(*(.logbuf.bss))
		KEEP(*(.stdioport.bss))
		KEEP(*strproc.o(.bss*))
		KEEP(*rtl8195blp_adc.o(.bss*))
		KEEP(*rtl8195blp_comp.o(.bss*))
		KEEP(*rtl8195blp_i2c.o(.bss*))

		__rtx_bss_start = .;
		KEEP(*rt_System.o(.bss*))
		KEEP(*rt_CMSIS.o(.bss*))
		KEEP(*rt_List.o(.bss*))
		KEEP(*rt_Robin.o(.bss*))
		KEEP(*rt_Task.o(.bss*))
		KEEP(*rt_Time.o(.bss*))
		KEEP(*rt_System.o(COMMON*))
		KEEP(*rt_CMSIS.o(COMMON*))
		KEEP(*rt_List.o(COMMON*))
		KEEP(*rt_Robin.o(COMMON*))
		KEEP(*rt_Task.o(COMMON*))
		KEEP(*rt_Time.o(COMMON*))
		KEEP(*(.rom.rtx.bss*))
		KEEP(*rtx_service_rom.o(.bss*))
		KEEP(*rtx_service_rom.o(COMMON*))
		__rtx_bss_end = .;

		/**** ROM Data for Shell command ****/
		/* Put shell command at button of ROM used RAM, 
		   so the RAM space can be recycled by RAM code */

		__rom_bss_end__ = .;

	} > ROM_USED_RAM

	.ram.img.signature :
	{
		__fw_img_start__ = .;
		__ram_img_signature__ = .;
		KEEP(*(.start.ram.sign*))		
	} > RAM_IMG_SIGN

	.ram.func.table :
	{
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;

	} > RAM_FUN_TABLE

	.data : AT (__etext)
	{
  	    __etext = .; 
		__data_start__ = .;
		*(vtable)
		*(.data*)

		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		/* init data */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);


		. = ALIGN(4);
		/* finit data */
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		KEEP(*(.jcr*))
		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;

	} > RAM

	.ram.code_text : AT (__ram_code_text_start__)
	{
		. = ALIGN(4);
		__etext2 = .;
		__ram_code_text_start__ = .;

		*(.text*)
		
		. = ALIGN(4);
		__ram_code_text_end__ = .;
	} > RAM

	.ram.code_rodata : AT (__ram_code_rodata_start__)
	{
		. = ALIGN(4);
		__ram_code_rodata_start__ = .;

		*(.rodata*)
		*(.rodata.str1*)
		. = ALIGN(4);
		__ram_code_rodata_end__ = .;
	} > RAM

	.bss :
	{
		. = ALIGN(4);
        __sys_bss_start__ = .;
        *(.sys.bss*)
        __sys_bss_end__ = .;

		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	.heap (COPY):
	{
		__HeapBase = .;
		__end__ = .;
		end = __end__;
		KEEP(*(.heap*))
		__HeapLimit = .;
	} > RAM

	/* templary BSS for ROM code, it will be recycled
	   and be used by RAM code */
	.rom_temp_use.bss :
	{
		. = ALIGN(4);
		__rom_temp_bss_start__ = .;
		KEEP(*(.rom_temp.bss))		
		__rom_temp_bss_end__ = .;
	} > DTCM_RAM

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	.stack_dummy (COPY):
	{
		KEEP(*(.stack*))
	} > DTCM_RAM

	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
	__StackTop = ORIGIN(DTCM_RAM) + LENGTH(DTCM_RAM);
	__StackLimit = __StackTop - SIZEOF(.stack_dummy);
	PROVIDE(__stack = __StackTop);

	/* Check if data + heap + stack exceeds RAM limit */
	/* TO DO: */
	/* ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack") */
}
