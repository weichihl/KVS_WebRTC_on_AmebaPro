/* Linker script to configure memory regions. */
MEMORY
{
  ROM (rx) 				: ORIGIN = 0x00000000, LENGTH = 0x0003F800
  ROM_STUB (rx) 		: ORIGIN = 0x0003F800, LENGTH = 0x00040000 - 0x0003F800
  VECTORS_RAM (rwx)     : ORIGIN = 0x20000000, LENGTH = 0x00000100
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x20000100, LENGTH = 0x20000180 - 0x20000100
  ROM_USED_RAM (rwx)    : ORIGIN = 0x20000180, LENGTH = 0x20000800 - 0x20000180
  RAM (rwx)             : ORIGIN = 0x20000800, LENGTH = 0x20010000 - 0x20000800
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
		KEEP(*(.sysstart.text))
		KEEP(*(.sys_misc.text))

		/**** HAL ROM Code ****/
		KEEP(*(.rom.hal_uart.text))
		KEEP(*(.rom.hal_uart.rodata))
		KEEP(*(.rom.hal_timer.text))
		KEEP(*(.rom.hal_timer.rodata))
		KEEP(*(.rom.hal_timer_ba.rodata))
		KEEP(*(.rom.hal_pwm.text))
		KEEP(*(.rom.hal_pwm.rodata))

		/**** Utility ROM code ****/
		KEEP(*(.infra.rom.text))
		KEEP(*(.xprintf.text))
		KEEP(*(.xprintf.rodata))
		KEEP(*(.shell.text))
		KEEP(*(.shell.rodata))
		KEEP(*(.shellcmd.text))
		KEEP(*(.shellcmd.rodata))
		KEEP(*(.ccmd.text))
		KEEP(*(.ccmd.rodata))

		KEEP(*xprintf.o(.rodata))
		KEEP(*strproc.o(.rodata))
		KEEP(*rtl8195blp_uart.o(.rodata))

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

		KEEP(*rtl8195blp_vectors.o(.rodata.str1*))
		KEEP(*rtl8195blp_timer.o(.rodata.str1*))
		KEEP(*rtl8195blp_pwm.o(.rodata.str1*))
		KEEP(*rtl8195blp_uart.o(.rodata.str1*))
		KEEP(*rtl8195blp_gdma.o(.rodata.str1*))

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

/************* End of ROM **************/

	.ram.vector :
	{
		. = ALIGN(4);
		__ram_vector_start__ = .;
		KEEP(*(.ram_vector_table))
		KEEP(*(.ram_user_irq_table))
		__ram_vector_end__ = .;
		. = ALIGN(4);
	} > VECTORS_RAM

	.ram.func.table :
	{
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;

	} > RAM_FUN_TABLE

	.rtx_rodata :
	{
		. = ALIGN(4);

		__rtx_rodata_start = .;
		KEEP(*RTX_Conf_CM.o(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))))
		__rtx_rodata_end = .;
		
		/*
		. = ALIGN(8);
		KEEP(*(SORT_BY_NAME(.rtx.callback.text)))
		*/
		
	} > ROM_USED_RAM

	/* initial data load from "__rom_etext" which @ ROM */
	.data_of_rom : AT (__rom_etext)		/* for ROM image building */
	{
		. = ALIGN(4);
		__rom_data_start__ = .;

		/**** ROM data ****/
		KEEP(*(.rom.hal_uart.data))
		KEEP(*(.rom.hal_timer.data))
		KEEP(*(.rom.hal_pwm.data))
		KEEP(*(.xprintf.data))

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
		KEEP(*(.diag.bss))
		KEEP(*(.rom.hal_uart.bss))
		KEEP(*(.rom.hal_timer.bss))
		KEEP(*(.rom.hal_pwm.bss))
		KEEP(*(.xprintf.bss))

		__rtx_bss_start = .;
		KEEP(*RTX_Conf_CM.o(.bss*))
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
		__rtx_bss_end = .;

		/**** ROM Data for Shell command ****/
		/* Put shell command at button of ROM used RAM, 
		   so the RAM space can be recycled by RAM code */
		KEEP(*(.rom_shellcmd.bss))
		KEEP(*(.shell.bss))
		KEEP(*(.shellcmd.bss))

		__rom_bss_end__ = .;

	} > ROM_USED_RAM

	__etext = .; 

	.data : AT (__etext)
	{
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

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	.stack_dummy (COPY):
	{
		KEEP(*(.stack*))
	} > RAM

	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
	__StackTop = ORIGIN(RAM) + LENGTH(RAM);
	__StackLimit = __StackTop - SIZEOF(.stack_dummy);
	PROVIDE(__stack = __StackTop);

	/* Check if data + heap + stack exceeds RAM limit */
	ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
