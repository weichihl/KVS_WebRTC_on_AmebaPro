/* Linker script to configure memory regions. */

/* !! the include symbole may failed if the symbol file name is too long!! */
INCLUDE "../../../component/soc/realtek/8195b/misc/bsp/ROM/romsym_s.so"

MEMORY
{
  /* !!! These memory map configuration MUST match with the SAU setting !!! */
  DTCM_RAM (wrx) 		: ORIGIN = 0x20000000, LENGTH = 0x00008000 

  /* Non-Secure Callable: for Non-Secure callable functions and secure gateway */  
  NSC (rwx)             : ORIGIN = 0x20120000, LENGTH = 0x20128000 - 0x20120000

  /* Internal SRAM for text, rodata & data */
  RAM (rwx)             : ORIGIN = 0x20128000, LENGTH = 0x2013D000 - 0x20128000

  /* Non-Cacheable memory, defined by MPU configuration */
  RAM_NC (rwx)          : ORIGIN = 0x2013D000, LENGTH = 0x2013FA00 - 0x2013D000
  
  /* RAM functions entry table */
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x2013FA00, LENGTH = 0x2013FAF0 - 0x2013FA00
  
  /* RAM image Signature */
  RAM_IMG_SIGN (rwx)    : ORIGIN = 0x2013FAF0, LENGTH = 0x2013FB00 - 0x2013FAF0

  /* The vector table, it must start with 256 bytes aligned address */
  VECTORS_RAM (rwx)     : ORIGIN = 0x2013FB00, LENGTH = 0x2013FC00 - 0x2013FB00

  /* 0x2013FC00 ~ 0x2013FFFF is reserved for ROM code */
  
  /* Following RAM(96K) is shared by CPU and Video Encoder, CPU can use it only when Video Encoder is off */
  RAM_SHARED (rwx)      : ORIGIN = 0x20140000, LENGTH = 0x20158000 - 0x20140000

  /* PSRAM memory */
  /* the range of PSRAM memory in secure region must match with the SAU setting at ram_start() */
  PSRAM (rx) 		    : ORIGIN = 0x60000000, LENGTH = 0x60100000 - 0x60000000

  /* LPDDR memory */
  /* the range of LPDDR memory in secure region must match with the SAU setting at ram_start() */
  RAM_LPDDR (rx) 		: ORIGIN = 0x71C00000, LENGTH = 0x72000000 - 0x71C00000

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
	.ram.vector :
	{
		. = ALIGN(0x100);
		__ram_vector_start__ = .;
		KEEP(*(.ram_vector_table))
		__ram_vector_end__ = .;
		. = ALIGN(4);
	} > VECTORS_RAM

	.ram.func.table :
	{
		. = ALIGN(0x10);
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;

	} > RAM

	.ram.img.signature :
	{
		. = ALIGN(0x04);
		__ram_img_signature__ = .;
		KEEP(*(.start.ram.sign*))		
	} > RAM

	/* Non-secure callable function */
	/* for Old ASDK NSC is put in section .sgstubs */
	/* .sgstubs : for Old ASDK */
	.sgstubs :
	{
		. = ALIGN(0x20);
		KEEP(*(.ns_entry_func.text*))
	} > NSC

	.gnu.sgstubs :
	{
		. = ALIGN(0x20);
		__nsc_start__ = .;
		KEEP(*(.ns_entry_func.text*))
		__nsc_end__ = .;
	} > NSC

	.psram.data : AT (__psram_etext)
	{
		. = ALIGN(16);
	    __psram_etext = .; 
		__psram_data_start__ = .;

		*(.psram.data*)

		__psram_data_end__ = .;

	} > PSRAM

	.lpddr.data : AT (__lpddr_etext)
	{
		. = ALIGN(16);
	    __lpddr_etext = .; 
		__lpddr_data_start__ = .;

		*(.lpddr.data*)

		__lpddr_data_end__ = .;

	} > RAM_LPDDR

	.data :
	{
		. = ALIGN(0x20);
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

	} > RAM

	.psram.code_text : AT (__psram_code_text_start__)
	{
		. = ALIGN(16);
		__psram_code_text_start__ = .;

		*(.psram.text*)
		
		__psram_code_text_end__ = .;
	} > PSRAM

	.psram.code_rodata : AT (__psram_code_rodata_start__)
	{
		. = ALIGN(16);
		__psram_code_rodata_start__ = .;

		*(.psram.rodata*)

		. = ALIGN(4);
		__psram_code_rodata_end__ = .;
	} > PSRAM

	.psram.bss :
	{
		. = ALIGN(16);
		__psram_bss_start__ = .;

		*(.psram.bss*)

		__psram_bss_end__ = .;
	} > PSRAM
	
	.lpddr.code_text : AT (__lpddr_code_text_start__)
	{
		. = ALIGN(16);
		__lpddr_code_text_start__ = .;

		*(.lpddr.text*)
		
		__lpddr_code_text_end__ = .;
	} > RAM_LPDDR

	.lpddr.code_rodata : AT (__lpddr_code_rodata_start__)
	{
		. = ALIGN(16);
		__lpddr_code_rodata_start__ = .;

		*(.lpddr.rodata*)

		. = ALIGN(4);
		__lpddr_code_rodata_end__ = .;
	} > RAM_LPDDR

	.lpddr.bss :
	{
		. = ALIGN(16);
		__lpddr_bss_start__ = .;

		*(.lpddr.bss*)

		__lpddr_bss_end__ = .;
	} > RAM_LPDDR

	.ram.code_text :
	{
		. = ALIGN(32);
		__ram_entry_text_start__ = .;
		*(.ram_entry_func.text*)
		__ram_entry_text_end__ = .;

		. = ALIGN(32);		
		__ram_code_text_start__ = .;

		/* SPI flash controller related code should be located in SRAM, never locates them in XIP */
		*hal_spic.o(.text*)

		/* LPDDR controller related code should be located in SRAM, never locates them in LPDDR */
		*hal_lpddr.o(.text*)

		*(.text*)
		. = ALIGN(4);
		__ram_code_text_end__ = .;
	} > RAM

	.ram.code_rodata : AT (__ram_code_rodata_start__)
	{
		. = ALIGN(4);
		__ram_code_rodata_start__ = .;

		/* SPI flash controller related code should be located in SRAM, never locates them in XIP */		
		*hal_spic.o(.rodata*)

		/* LPDDR controller related code should be located in SRAM, never locates them in LPDDR */
		*hal_lpddr.o(.rodata*)

		*(.rodata*)
		*(.rodata.str1*)
		. = ALIGN(4);
		__ram_code_rodata_end__ = .;
	} > RAM

	.system_restore_data :
	{
		. = ALIGN(32);
		*(.sys_restore.bss*)
	} > RAM
	
	.bss :
	{
		. = ALIGN(16);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
	} > RAM

	.non_secure.bss :
	{
		. = ALIGN(16);
		__ns_bss_start__ = .;
		*(.nonsecure.bss*)

		. = ALIGN(4);
		__ns_bss_end__ = .;
		__bss_end__ = .;
	} > RAM

	/* Non-Cacheable memory, the memory range should be configured by a MPU region */
	.non_cacheable :
	{
		. = ALIGN(32);
		__nc_data_start__ = .;
		*(.non_cache.data*)
		__nc_bss_start__ = .;
		*(.non_cache.bss*)
		__nc_bss_end__ = .;
	} > RAM_NC

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
