/* Linker script to configure memory regions. */

ENTRY(Reset_Handler)

INCLUDE "../../../component/soc/realtek/8195b/misc/bsp/ROM/romsym_8195bl.so"

MEMORY
{
  DTCM_ROM_BSS (wrx)	: ORIGIN = 0x20000000, LENGTH = 0x00000500
  DTCM_RAM (wrx) 		: ORIGIN = 0x20000500, LENGTH = 0x00000B00
  VECTORS_RAM (rwx)     : ORIGIN = 0x20200000, LENGTH = 0x00000100
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
 *   __sys_bss_start__
 *   __sys_bss_end__
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

SECTIONS
{
	.ram.vector :
	{
		. = ALIGN(4);
		__ram_vector_start__ = .;
		KEEP(*(.ram_vector_table))
		__ram_vector_end__ = .;
		. = ALIGN(4);
	} > VECTORS_RAM

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

	.sys.bss : 
	{
		. = ALIGN(4);
		__sys_bss_start__ = .;
		*(.sys.bss*)
		__sys_bss_end__ = .;	
	} > DTCM_RAM
	
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
		/*__HeapLimit = .;*/
		__HeapLimit = ORIGIN(RAM) + LENGTH(RAM) - 16;
	} > RAM

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
