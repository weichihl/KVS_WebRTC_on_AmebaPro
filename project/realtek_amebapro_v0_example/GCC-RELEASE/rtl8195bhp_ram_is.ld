/* Linker script to configure memory regions. */

/* !! the include symbole may failed if the symbol file name is too long!! */
INCLUDE "../../../component/soc/realtek/8195b/misc/bsp/ROM/romsym_is.so"

/* Select External RAM type - 1: LPDDR SDRAM 2: PSRAM */
useERAM = 1;

INCLUDE "amebapro_config_is.ld"
INCLUDE "xip_fw.ld"

XIP_OFFSET = 0x40140 - 0x220;

XIP_ORIGIN = linkFW==1 ? (__ICFEDIT_region_XIP_FW1_FLASH_start__ + XIP_OFFSET) : 0;
XIP_ORIGIN = linkFW==2 ? (__ICFEDIT_region_XIP_FW2_FLASH_start__ + XIP_OFFSET) : XIP_ORIGIN;
XIP_ORIGIN = linkFW==3 ? (0x9BE00000 + 0x140) : XIP_ORIGIN;

XIP_END = linkFW==1 ? __ICFEDIT_region_XIP_FW1_FLASH_end__ : 0;
XIP_END = linkFW==2 ? __ICFEDIT_region_XIP_FW2_FLASH_end__ : XIP_END;
XIP_END = linkFW==3 ? 0x9C000000 : XIP_END;

XIP_LENGTH = XIP_END - XIP_ORIGIN;

RAM_ORIGIN = 0x20100A00;
RAM_END = reserveVOE==1 ? 0x20124000 : 0x2013CC00;
RAM_LENGTH = RAM_END - RAM_ORIGIN;

RAM_NC_ORIGIN = reserveVOE==1 ? 0x20124000 : 0x2013CC00;
RAM_NC_END = reserveVOE==1 ? 0x20128000 : 0x2013FC00;
RAM_NC_LENGTH = RAM_NC_END - RAM_NC_ORIGIN;

RAM_SHARED0_ORIGIN = reserveVOE==1 ? 0x20128000 : 0x2013FC00;
RAM_SHARED0_END =  0x2013FC00; 
RAM_SHARED0_LENGTH = RAM_SHARED0_END - RAM_SHARED0_ORIGIN;

MEMORY
{
  ITCM_RAM (rx) 		: ORIGIN = 0x00010000, LENGTH = 0x0002FFFF - 0x00010000
  
  /* The vector table, it must start with 256 bytes aligned address */
  VECTORS_RAM (rwx)     : ORIGIN = 0x20000000, LENGTH = 0x20000100 - 0x20000000
  /* 0x20000000 ~ 0x20000400 is reserved for C-Cut(and after) ROM code */
  DTCM_RAM (wrx) 		: ORIGIN = 0x20000400, LENGTH = 0x20010000 - 0x20000400
  
  /* 0x201000C0 ~ 0x201008FF is reserved for ROM code */

  /* RAM functions entry table */
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x20100900, LENGTH = 0x201009F0 - 0x20100900

  /* RAM image Signature */
  RAM_IMG_SIGN (rwx)    : ORIGIN = 0x201009F0, LENGTH = 0x20100A00 - 0x201009F0
    
  /* Internal SRAM for text, rodata & data */
  RAM (rwx)             : ORIGIN = RAM_ORIGIN, LENGTH = RAM_LENGTH

  /* Non-Cacheable memory, defined by MPU configuration */
  RAM_NC (rwx)          : ORIGIN = RAM_NC_ORIGIN, LENGTH = RAM_NC_LENGTH

  /* Following RAM(96K) is shared by CPU and Video Encoder, CPU can use it only when Video Encoder is off */
  RAM_SHARED0 (rwx)      : ORIGIN = 0x20128000, LENGTH = RAM_SHARED0_LENGTH

  /* 0x2013FC00 ~ 0x2013FFFF is reserved for B-Cut(and before) ROM code */

  /* Following RAM(96K + 136K) is shared by CPU and Video Encoder, CPU can use it only when Video Encoder is off */
  RAM_SHARED (rwx)      : ORIGIN = RAM_SHARED0_ORIGIN, LENGTH = 0x2017A000 - 0x20140000

  /* PSRAM memory */
  PSRAM (rwx) 		    : ORIGIN = 0x60000000, LENGTH = 0x60800000 - 0x60000000

  /* LPDDR memory */
  RAM_LPDDR (rwx) 		: ORIGIN = 0x70000000, LENGTH = 0x72000000 - 0x70000000

  /* ERAM memroy */
  EXTERNAL_RAM (rwx)    : ORIGIN = useERAM==2 ? ORIGIN(PSRAM) : ORIGIN(RAM_LPDDR), LENGTH = useERAM==2 ? LENGTH(PSRAM) : LENGTH(RAM_LPDDR)

  /* Flash memory for XIP */
  /* XIP image must start with 256K(0x40000) aligned address */
   
  XIP_FLASH (rx) 		: ORIGIN = XIP_ORIGIN, LENGTH = XIP_LENGTH
 
  
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
		. = ALIGN(32);
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;

	} > RAM_FUN_TABLE

	.ram.img.signature :
	{
		__ram_img_signature__ = .;
		KEEP(*(.start.ram.sign*))		
	} > RAM_IMG_SIGN

	/*******************************************************************************************/
	/*   ITCM/DTCM placement                                                                   */
	/*******************************************************************************************/

	.itcm_ram.code_rodata :
	{
		__itcm_ram_code_rodata_start__ = .;

		*(.itcm.text*)
		*(.haac.text*)
		*(.faac.text*)

		__itcm_ram_code_rodata_end__ = .;
	} > ITCM_RAM

	.dtcm_ram.bss :
	{
		/* Note: Boot loader data buffer & stack is allocated in DTCM RAM !! */
		/*       so do not allocate data/rodata/text in this section, it may cause boot loader failed */
		__dtcm_ram_bss_start__ = .;

		*(.dtcm_ram.bss*)
		/* *(.itcm.bss.mem*) */
		
		
		__dtcm_ram_bss_end__ = .;
	} > DTCM_RAM


	/*******************************************************************************************/
	/*   External RAM placement                                                                */
	/*******************************************************************************************/	
	.eram.code_text :
	{
		. = ALIGN(16);
		__eram_code_text_start__ = .;
		__psram_code_text_start__ = .;
		__lpddr_code_text_start__ = .;

		*(.psram.text*)
		*(.lpddr.text*)
		*(.sdram.text*)
		*(.usbd.text*)
		*(.wlan.text*)
		*(.eram.text*)
		*(.speex.text*)

		__psram_code_text_end__ = .;
		__lpddr_code_text_end__ = .;
	} > EXTERNAL_RAM

	.eram.code_rodata :
	{
		. = ALIGN(16);
		__eram_code_rodata_start__ = .;
		__psram_code_rodata_start__ = .;
		__lpddr_code_rodata_start__ = .;

		*(.psram.rodata*)
		*(.lpddr.rodata*)
		*(.sdram.rodata*)
		*(.usbd.rodata*)
		*(.wlan.rodata*)
		*(.eram.rodata*)

		*(.psram.rodata.str1*)
		*(.lpddr.rodata.str1*)
		*(.sdram.rodata.str1*)
		*(.usbd.rodata.str1*)
		*(.wlan.rodata.str1*)
		*(.eram.rodata.str1*)	

		. = ALIGN(4);
		__psram_code_rodata_end__ = .;
		__lpddr_code_rodata_end__ = .;
	} > EXTERNAL_RAM

	.eram.data : AT (__eram_etext)
	{
		. = ALIGN(16);
	    __eram_etext = .; 
		__psram_data_start__ = .;
		__lpddr_data_start__ = .;

		*(.psram.data*)
		*(.lpddr.data*)
		*(.sdram.data*)
		*(.usbd.data*)
		*(.wlan.data*)
		*(.eram.data*)
		*/mem.o (.itcm.bss*)
		*/memp.o (.itcm.bss*)

		__psram_data_end__ = .;
		__lpddr_data_end__ = .;
	} > EXTERNAL_RAM

	.eram.bss :
	{
		. = ALIGN(16);
		*(.lpddr.bss.noinit*)

		__eram_bss_start__ = .;
		__psram_bss_start__ = .;
		__lpddr_bss_start__ = .;

		*(.psram.bss*)
		*(.lpddr.bss*)
		*(.sdram.bss*)
		*(.usbd.bss*)
		*(.wlan.bss*)
		*(.eram.bss*)

		__eram_bss_end__ = .;
		__psram_bss_end__ = .;
		__lpddr_bss_end__ = .;
	} > EXTERNAL_RAM
	

	/*******************************************************************************************/
	/*   Internal RAM placement                                                                */
	/*******************************************************************************************/	
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

		*hal_misc.o(.text*)
		*hal_sys_ctrl.o(.text*)
		*ram_start.o(.text*)
		/* *libgcc.a:*.o(.text*) */

		*(.sram.text*)
		
		. = ALIGN(4);
		__ram_code_text_end__ = .;
	} > RAM

	.ram.code_rodata :
	{
		. = ALIGN(16);
		__ram_code_rodata_start__ = .;

		/* SPI flash controller related code should be located in SRAM, never locates them in XIP */		
		*hal_spic.o(.rodata*)

		/* LPDDR controller related code should be located in SRAM, never locates them in LPDDR */
		*hal_lpddr.o(.rodata*)

		*hal_misc.o(.rodata*)
		*hal_sys_ctrl.o(.rodata*)
		*ram_start.o(.rodata*)

		*(.sram.rodata*)
		*(.sram.rodata.str1*)
		. = ALIGN(4);
		__ram_code_rodata_end__ = .;
	} > RAM

	.ram.data :
	{
		. = ALIGN(16);
		__fw_img_start__ = .;
		__data_start__ = .;
		*(vtable)
		*(.data*)
		*(.sram.data*)
		*(.itcm.data*)
		*(.haac.data*)
		*(.faac.data*)
		*(.speex.data*)

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
	/*******************************************************************************************/
	/*   CINIT placement                                                                       */
	/*******************************************************************************************/
	.cinit.data :
	{
		. = ALIGN(32);
		__cinit_data__ = .;
		__cinit_start_table_start__ = .;
		KEEP(*(*.cinit_entry_func.data*))
		__cinit_start_table_end__ = .;
		*(.cinit.data*)

		/* put C-init data here */
	} > RAM

	.cinit.ro :
	{
		. = ALIGN(16);
		__cinit_ro_start__ = .;

		/* *libgcc.a:*.o(.text*) */
		*libgcc.a:_arm_addsubdf3.o(.text*)
		*libgcc.a:_arm_muldivdf3.o(.text*)
		*libgcc.a:_arm_fixunsdfsi.o(.text*)
		*(.cinit.text*)
		*(.cinit.rodata*)


		/* put C-init ro-data here */

        __cinit_ro_end__ = .;

	} > RAM


	/*******************************************************************************************/
	/*   XIP placement                                                                         */
	/*******************************************************************************************/

	.xip_reserved :
	{
		/* XIP image section must start with 64K aligned address, reserve 0x140 for image header */
		/*. += 0x140;*/
		
	} > XIP_FLASH


	.xip.code_text :
	{
		. = ALIGN(16);
		__xip_code_text_start__ = .;

		*(.text*)
		
		__xip_code_text_end__ = .;
	} > XIP_FLASH
	
	.ARM.exidx : 
	{ 
		__exidx_start = .; 
		*(.ARM.exidx* .gnu.linkonce.armexidx.*) 
		__exidx_end = .; 
	} > XIP_FLASH		

	.xip.code_rodata :
	{
		. = ALIGN(4);
		__xip_code_rodata_start__ = .;

		*(.rodata*)
		*(.itcm.rodata*)
		*(.haac.rodata*)
		*(.faac.rodata*)
		*(.speex.rodata*)
		
		. = ALIGN(4);
		__xip_code_rodata_end__ = .;
	} > XIP_FLASH

	/*******************************************************************************************/
	/*   Others placement                                                                      */
	/*******************************************************************************************/
	.system_restore_data :
	{
		. = ALIGN(32);
		*(.sys_restore.bss*)
	} > RAM
	
	.ram.bss :
	{
		. = ALIGN(16);
		*(.ram.bss.noinit*)

		__cinit_bss_start__ = .;
		*(.cinit.bss*)
		
		/* put C-init BSS here */
		__cinit_bss_end__ = .;

		__bss_start__ = .;
		*(.bss*)
		*(.sram.bss*)
		*(.itcm.bss*)
		*(.haac.bss*)
		*(.faac.bss*)
		*(.speex.bss*)
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
