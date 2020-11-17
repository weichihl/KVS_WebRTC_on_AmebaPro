/* Linker script to configure memory regions. */

ENTRY(ram_start)
/* !! the include symbole may failed if the symbol file name is too long!! */
INCLUDE "romsym_ns.so"

/* Select External RAM type - 1: LPDDR SDRAM 2: PSRAM */
useERAM = 1;

MEMORY
{
  ITCM_RAM (rx) 		: ORIGIN = 0x00010000, LENGTH = 0x00030000 - 0x00010000
  DTCM_RAM (wrx) 		: ORIGIN = 0x20008000, LENGTH = 0x00008000

  /* The vector table, it must start with 256 bytes aligned address */
  /* The Reset_Handler also is the NS region code entry function */
  VECTORS_RAM (rwx)     : ORIGIN = 0x20100000, LENGTH = 0x20100100 - 0x20100000
  
  /* 0x20100100 ~ 0x201008FF is reserved for ROM code */
  
  /* RAM functions entry table */
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x20100900, LENGTH = 0x20100A00 - 0x20100900
  
  /* Internal SRAM for text, rodata & data */
  RAM (rwx)             : ORIGIN = 0x20100A00, LENGTH = 0x20110000 - 0x20100A00

  /* Non-Cacheable memory, defined by MPU configuration */
  RAM_NC (rwx)          : ORIGIN = 0x20110000, LENGTH = 0x20114000 - 0x20110000

  /* Following RAM(136K) is shared by CPU and Video Encoder, CPU can use it only when Video Encoder is off */
  RAM_SHARED (rwx)      : ORIGIN = 0x20140000, LENGTH = 0x2017A000 - 0x20140000

  /* PSRAM memory */
  /* the range of PSRAM memory in non-secure region must match with the SAU setting at ram_start() */
  PSRAM (rx) 		    : ORIGIN = 0x60100000, LENGTH = 0x60800000 - 0x60100000
  
  /* LPDDR memory */
  /* the range of LPDDR memory in non-secure region must match with the SAU setting at ram_start() */
  RAM_LPDDR (rx) 		: ORIGIN = 0x70000000, LENGTH = 0x71C00000 - 0x70000000

  /* External RAM memroy */
  EXTERNAL_RAM (rwx)    : ORIGIN = useERAM==2 ? ORIGIN(PSRAM) : ORIGIN(RAM_LPDDR), LENGTH = useERAM==2 ? LENGTH(PSRAM) : LENGTH(RAM_LPDDR)
  
  /* Flash memory for XIP, the start address should be aligned to 16K/32K/64K(depends on SCE configuration) */
  /* the range of XIP memory in non-secure region must match with the SAU setting at ram_start() */
  XIP_FLASH (rx) 		: ORIGIN = 0x9BF80000, LENGTH = 0x9C000000 - 0x9BF80000
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

__sram_end__ = ORIGIN(RAM) + LENGTH(RAM);
__eram_end__ = ORIGIN(EXTERNAL_RAM) + LENGTH(EXTERNAL_RAM);

SECTIONS
{
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
		. = ALIGN(16);
		__fw_img_start__ = .;
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;

	} > RAM_FUN_TABLE

	.itcm_ram.code_rodata :
	{
		__itcm_ram_code_rodata_start__ = .;

		*(.itcm_ram.text*)
		*(.itcm_ram.rodata*)

		*freertos_service.o(.text*)
		*cmsis_os.o(.text*)
		*croutine.o(.text*)
		*event_groups.o(.text*)
		*list.o(.text*)
		*queue.o(.text*)
		*stream_buffer.o(.text*)
		*tasks.o(.text*)
		*timers.o(.text*)
		*port.o(.text*)
		*heap_4_2.o(.text*)

		*freertos_service.o(.rodata*)
		*cmsis_os.o(.rodata*)
		*croutine.o(.rodata*)
		*event_groups.o(.rodata*)
		*list.o(.rodata*)
		*queue.o(.rodata*)
		*stream_buffer.o(.rodata*)
		*tasks.o(.rodata*)
		*timers.o(.rodata*)
		*port.o(.rodata*)
		*heap_4_2.o(.rodata*)
		
		*freertos_service.o(.rodata*)
		*freertos_service.o(.rodata.str1*)
		
		__itcm_ram_code_rodata_end__ = .;
	} > ITCM_RAM

	.dtcm_ram.bss :
	{
		/* Note: Boot loader data buffer & stack is allocated in DTCM RAM !! */
		/*       so do not allocate data/rodata/text in this section, it may cause boot loader failed */
		__dtcm_ram_bss_start__ = .;

		*(.dtcm_ram.bss*)
		
		__dtcm_ram_bss_end__ = .;
	} > DTCM_RAM

	.ram.data : AT (__etext)
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

	.eram.data : AT (__eram_etext)
	{
		. = ALIGN(16);
	    __eram_etext = .; 
		__psram_data_start__ = .;
		__lpddr_data_start__ = .;

		*(.lpddr.data*)
		*(.psram.data*)

		__psram_data_end__ = .;
		__lpddr_data_end__ = .;

	} > EXTERNAL_RAM

	/* Set the XIP memory range for the SAU configuration */
	__XIP_Start = ORIGIN(XIP_FLASH);
	__XIP_Limit = __XIP_Start + LENGTH(XIP_FLASH);

	.xip_reserved :
	{
		/* XIP image section must start with 64K aligned address, reserve 0x140 for image header */
		. += 0x140;
	} > XIP_FLASH

	.xip.code_text : AT (__xip_code_text_start__)
	{
		. = ALIGN(16);
		__xip_code_text_start__ = .;

		*dwc_otg*.o(.text*)
		*usb.o(.text*)
		*usbd_vendor.o(.text*)

		*(.xip.text*)
		
		__xip_code_text_end__ = .;
	} > XIP_FLASH

	.xip.code_rodata : AT (__xip_code_rodata_start__)
	{
		. = ALIGN(4);
		__xip_code_rodata_start__ = .;

		*dwc_otg*.o(.rodata*)
		*dwc_otg*.o(.rodata.str1*)
		
		*usb.o(.rodata*)
		*usb.o(.rodata.str1*)
		
		*usbd_vendor.o(.rodata*)
		*usbd_vendor.o(.rodata.str1*)

		*(.xip.rodata*)
		
		. = ALIGN(4);
		__xip_code_rodata_end__ = .;
	} > XIP_FLASH

	.eram.code_text : AT (__eram_code_text_start__)
	{
		. = ALIGN(16);
		__eram_code_text_start__ = .;
		__psram_code_text_start__ = .;
		__lpddr_code_text_start__ = .;

		*(.lpddr.text*)
		*(.psram.text*)
		
		__psram_code_text_end__ = .;
		__lpddr_code_text_end__ = .;
	} > EXTERNAL_RAM

	.eram.code_rodata : AT (__eram_code_rodata_start__)
	{
		. = ALIGN(16);
		__eram_code_rodata_start__ = .;
		__psram_code_rodata_start__ = .;
		__lpddr_code_rodata_start__ = .;

		*(.lpddr.rodata*)
		*(.psram.rodata*)

		. = ALIGN(4);
		__psram_code_rodata_end__ = .;
		__lpddr_code_rodata_end__ = .;
	} > EXTERNAL_RAM

	.eram.bss :
	{
		. = ALIGN(16);
		*(.lpddr.bss.noinit*)

		__eram_bss_start__ = .;
		__psram_bss_start__ = .;
		__lpddr_bss_start__ = .;

		*(.lpddr.bss*)
		*(.psram.bss*)

		__eram_bss_end__ = .;
		__lpddr_bss_end__ = .;
		__psram_bss_end__ = .;
	} > EXTERNAL_RAM

	.ram.code_text : AT (__ram_code_text_start__)
	{
		. = ALIGN(16);
		__etext2 = .;
		__ram_code_text_start__ = .;

		*(.text*)
		
		. = ALIGN(4);
		__ram_code_text_end__ = .;
	} > RAM

	.ram.code_rodata :
	{
		. = ALIGN(16);
		__ram_code_rodata_start__ = .;

		*(.rodata*)
		*(.rodata.str1*)
		. = ALIGN(4);
		__ram_code_rodata_end__ = .;
	} > RAM

	.ram.bss :
	{
		. = ALIGN(16);
		*(.ram.bss.noinit*)
		
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	/* Non-Cacheable memory, the memory range should be configured by a MPU region */
	.non_cacheable_data :
	{
		. = ALIGN(32);
		__nc_mem_start__ = .;
		__nc_data_start__ = .;
		*(.non_cache.data*)
		__nc_data_end__ = .;
	} > RAM_NC

	.non_cacheable_bss :
	{
		. = ALIGN(32);
		__nc_bss_start__ = .;
		*(.non_cache.bss*)
		__nc_bss_end__ = .;
		__nc_mem_end__ = .;
	} > RAM_NC

	/* RAM_SHARED memory is shared by CPU and Video Encoder, CPU can locate memory here only when Video Encoder is off */
	.share_ram :
	{
	} > RAM_SHARED

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
