/* Linker script to configure memory regions. */

/* !! the include symbole may failed if the symbol file name is too long!! */
/* this symbol file is from S & NS symbol merged */
INCLUDE "../../../component/soc/realtek/8195b/misc/bsp/ROM/romsym_is.so"

MEMORY
{
  ITCM_RAM (rx) 		: ORIGIN = 0x00200000, LENGTH = 0x00020000
  /* The vector table, it must start with 256 bytes aligned address */
  VECTORS_RAM (rwx)     : ORIGIN = 0x20000000, LENGTH = 0x20000100 - 0x20000000
  /* 0x20000000 ~ 0x20000400 is reserved for C-Cut(and after) ROM code */
  DTCM_RAM (wrx) 		: ORIGIN = 0x20000400, LENGTH = 0x20010000 - 0x20000400
  
  RAM (rwx)             : ORIGIN = 0x20172000, LENGTH = 0x20174000 - 0x20172000
  RAM_RO (rwx)          : ORIGIN = 0x20174000, LENGTH = 0x20179D00 - 0x20174000
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x20179D00, LENGTH = 0x20179F00 - 0x20179D00
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
_start_addr = 0x000000c0;
ENTRY(_start_addr)

SECTIONS
{
	/* templary BSS for boot loader, it will be recycled
	   and be used by FW code */
	.boot_temp_use.bss :
	{
		. = ALIGN(4);
		__boot_temp_bss_start__ = .;
		KEEP(*(.rom_temp.bss))		
		__boot_temp_bss_end__ = .;
		__boot_sboot_bss_start__ = .;
		KEEP(*(.sboot.bss))		
		__boot_sboot_bss_end__ = .;
		
	} > DTCM_RAM

	.ram.vector :
	{
		. = ALIGN(256);
		__ram_vector_start__ = .;
		KEEP(*(.ram_vector_table))
		__ram_vector_end__ = .;
		. = ALIGN(4);
	} > VECTORS_RAM

	.ram.func.table :
	{
		/* Boot image start here. for image decryption, 
		  the image start addr. should be aligned to 16 */
		. = ALIGN(32);
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;

	} > RAM_FUN_TABLE

/*
	.ram.img.signature :
	{
		__ram_img_signature__ = .;
		KEEP(*(.start.ram.sign*))		
	} > RAM_IMG_SIGN
*/
	.ram.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	.ram.data : AT (__data_start__)
	{
		. = ALIGN(16);
		__fw_img_start__ = .;
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

	} > RAM_RO

	.ram.code_text : AT (__ram_code_text_start__)
	{
		. = ALIGN(32);
		__ram_code_text_start__ = .;

		__ram_img_signature__ = .;
		KEEP(*(.start.ram.sign*))		

		*(.text*)
		
		__ram_code_text_end__ = .;
	} > RAM_RO

	.ram.code_rodata :
	{
		__ram_code_rodata_start__ = .;

		*(.rodata*)
		*(.rodata.str1*)
		__ram_code_rodata_end__ = .;
	} > RAM_RO

	.heap (COPY):
	{
		__HeapBase = .;
		__end__ = .;
		end = __end__;
		KEEP(*(.heap*))
		__HeapLimit = .;
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
/* TODO:	ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack") */
}
