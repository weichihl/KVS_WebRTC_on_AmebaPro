/* Linker script to configure memory regions. */

/* Select External RAM type - 1: LPDDR SDRAM 2: PSRAM */
useERAM = 1;

MEMORY
{
  /* !!! These memory map configuration MUST match with the SAU setting !!! */
  ITCM_ROM (rx) 		: ORIGIN = 0x00000000, LENGTH = 0x00003000
  ROM (rx) 				: ORIGIN = 0x1007E000, LENGTH = 0x100AEC00 - 0x1007E000
  ROM_STUB (rx) 		: ORIGIN = 0x100AEC00, LENGTH = 0x100B0000 - 0x100AEC00
  /* The vector table, it must start with 256 bytes aligned address */
  VECTORS_RAM (rwx)     : ORIGIN = 0x20000000, LENGTH = 0x20000100 - 0x20000000
  /* reserved for ROM code */
  ROM_USED_RAM (rwx)    : ORIGIN = 0x20000100, LENGTH = 0x20000400 - 0x20000100
  DTCM_RAM (wrx) 		: ORIGIN = 0x20000400, LENGTH = 0x2000A000 - 0x20000400 
  DTCM_ROM (rx) 		: ORIGIN = 0x20017000, LENGTH = 0x20018000 - 0x20017000

  /* Non-Secure Callable: for Non-Secure callable functions and secure gateway */  
  NSC (rwx)             : ORIGIN = 0x20114000, LENGTH = 0x2011A000 - 0x20114000

  /* Internal SRAM for text, rodata & data */
  RAM (rwx)             : ORIGIN = 0x2011A000, LENGTH = 0x20124000 - 0x2011A000

  /* Non-Cacheable memory, defined by MPU configuration */
  RAM_NC (rwx)          : ORIGIN = 0x20124000, LENGTH = 0x20127F00 - 0x20124000
  
  /* RAM functions entry table */
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x20127F00, LENGTH = 0x20127FF0 - 0x20127F00
  
  /* RAM image Signature */
  RAM_IMG_SIGN (rwx)    : ORIGIN = 0x20127FF0, LENGTH = 0x20128000 - 0x20127FF0


  /* Following RAM(96K) is shared by CPU and Video Encoder, CPU can use it only when Video Encoder is off */
  RAM_SHARED (rwx)      : ORIGIN = 0x20128000, LENGTH = 0x20158000 - 0x20128000

  /* PSRAM memory */
  /* the range of PSRAM memory in secure region must match with the SAU setting at ram_start() */
  PSRAM (rx) 		    : ORIGIN = 0x60000000, LENGTH = 0x60100000 - 0x60000000

  /* LPDDR memory */
  /* the range of LPDDR memory in secure region must match with the SAU setting at ram_start() */
  RAM_LPDDR (rx) 		: ORIGIN = 0x71C00000, LENGTH = 0x72000000 - 0x71C00000

  /* External RAM memroy */
  EXTERNAL_RAM (rwx)    : ORIGIN = useERAM==2 ? ORIGIN(PSRAM) : ORIGIN(RAM_LPDDR), LENGTH = useERAM==2 ? LENGTH(PSRAM) : LENGTH(RAM_LPDDR)
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

__sram_end__ = ORIGIN(RAM) + LENGTH(RAM);
__eram_end__ = ORIGIN(EXTERNAL_RAM) + LENGTH(EXTERNAL_RAM);

SECTIONS
{
	.rom.vector_tbl :
	{
		KEEP(*(.rom.vectors))
		__Vectors_End = .;
		__Vectors_Size = __Vectors_End - __Vectors;

		__end__ = .;

	} > ITCM_ROM

	.rom.dtcm.data :
	{
		/* Only ROM boot code ro-data can be put here, 
		 * these data cannot be referenced after jump to RAM code */
		KEEP(*fw_flash_boot.o(.rodata*))
		KEEP(*startup_rtl8195bhp.o(.rodata.str1*))
		KEEP(*startup.o(.rodata.str1*))
		KEEP(*fw_flash_boot.o(.rodata.str1*))
	} > DTCM_ROM

	.rom.itcm.text :
	{
		__itcm_rom_start__ = .;
		/* boot ROM code */
		KEEP(*startup_rtl8195bhp.o(.text*))
		KEEP(*(.sysstart.text))
		KEEP(*startup.o(.rodata*))
		KEEP(*startup.o(.rodata.str1*))
 	    KEEP(*fw_flash_boot.o(.text*))
/*		KEEP(*fw_flash_boot.o(.rodata*)) */
/*		KEEP(*memory.o(.infra.rom.text))
		KEEP(*memory.o(.rodata*))
		KEEP(*fw_flash_boot.o(.rodata.str1*))
*/		
		__itcm_rom_end__ = .;
	} > ITCM_ROM

	.rom.text :
	{
		. = ALIGN(0x100);

		KEEP(*system_rtl8195bhp.o(.text*))
		KEEP(*(.startup.text))
		KEEP(*(.vector.text))
		KEEP(*(.sys_misc.text))
		KEEP(*(.rom.irq.rodata*))

		/**** HAL ROM Code ****/
		KEEP(*(.rom.hal_syson.text))
		KEEP(*(.rom.hal_syson.rodata))
		KEEP(*(.rom.hal_uart.text))
		KEEP(*(.rom.hal_uart.rodata))
		KEEP(*(.rom.hal_timer.text))
		KEEP(*(.rom.hal_timer.rodata))
		KEEP(*(.rom.hal_timer_ba.rodata))
		KEEP(*(.rom.hal_icc.text))
		KEEP(*(.rom.hal_icc.rodata))
		KEEP(*(.rom.hal_efuse.text))
		KEEP(*(.rom.hal_efuse.rodata))
		KEEP(*(.rom.hal_gdma.text*))
		KEEP(*(.rom.hal_gdma.rodata*))
		KEEP(*(.rom.hal_spic.text*))
		KEEP(*(.rom.hal_spic.rodata*))
		KEEP(*(.rom.hal_flash.text*))
		KEEP(*(.rom.hal_flash.rodata*))
		KEEP(*(.rom.hal_cache.text*))
		KEEP(*(.rom.hal_cache.rodata*))
		KEEP(*(.rom.hal_sce.text*))
		KEEP(*(.rom.hal_sce.rodata*))

		KEEP(*rtl8195bhp_syson.o(.rodata*))
		KEEP(*rtl8195bhp_uart.o(.rodata*))
		KEEP(*rtl8195bhp_gdma.o(.text*))
		KEEP(*rtl8195bhp_gdma.o(.rodata*))
		KEEP(*rtl8195bhp_pinmux.o(.text*))
		KEEP(*rtl8195bhp_pinmux.o(.rodata*))
		KEEP(*(.rom.hal_pinmux.rodata*))		
		KEEP(*rtl8195bhp_rom_s_crypto.o(.text*))
		KEEP(*rtl8195bhp_rom_s_crypto.o(.rodata*))

		/**** Utility ROM code ****/
		KEEP(*(.infra.rom.text))
		KEEP(*(.stdioport.text))
		KEEP(*(.rtlprintf.text))
		KEEP(*(.rtlprintf.rodata))
		KEEP(*(.rtlprintf.text))
		KEEP(*(.shell.text))
		KEEP(*(.shell.rodata))
		KEEP(*(.shellcmd.text))
		KEEP(*(.shellcmd.rodata))
		KEEP(*(.ccmd.text))
		KEEP(*(.ccmd.rodata))
		KEEP(*(.rom.utility.text*))

		KEEP(*rtl_printf.o(.rodata*))
		KEEP(*strproc.o(.text*))
		KEEP(*strproc.o(.rodata*))
		KEEP(*atoi.o(.text*))
		KEEP(*atoi.o(.rodata*))

		KEEP(*xmodem.o(.text*))
		KEEP(*xmodem.o(.rodata*))
		KEEP(*xmport_uart.o(.text*))
		KEEP(*xmport_uart.o(.rodata*))
		KEEP(*fw_otu.o(.text*))
		KEEP(*fw_otu.o(.rodata*))
		KEEP(*fw_otu.o(.rodata.str1*))
		KEEP(*fw_uart_boot.o(.text*))
		KEEP(*fw_uart_boot.o(.rodata*))
		KEEP(*fw_uart_boot.o(.rodata.str1*))
		KEEP(*fw_sdio_boot.o(.text*))
		KEEP(*fw_sdio_boot.o(.rodata*))
		KEEP(*fw_sdio_boot.o(.rodata.str1*))
		
/*		KEEP(*cmse_nonsecure_call.o(.text)) */

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

		KEEP(*shell.o(.rodata.str1*))
		KEEP(*rtl_printf.o(.rodata.str1*))
		KEEP(*utility.o(.rodata.str1*))

		KEEP(*rtl8195bhp_irq.o(.rodata.str1*))
		KEEP(*rtl8195bhp_uart.o(.rodata.str1*))
		KEEP(*rtl8195bhp_timer.o(.rodata.str1*))
		KEEP(*rtl8195bhp_icc.o(.rodata.str1*))
		KEEP(*rtl8195bhp_efuse.o(.rodata.str1*))
		KEEP(*rtl8195bhp_gdma.o(.rodata.str1*))
		KEEP(*rtl8195bhp_spic.o(.rodata.str1*))
		KEEP(*rtl8195bhp_flash.o(.rodata.str1*))
		KEEP(*rtl8195bhp_pinmux.o(.rodata.str1*))
		KEEP(*rtl8195bhp_rom_s_crypto.o(.rodata.str1*))
		KEEP(*rtl8195bhp_syson.o(.rodata.str1*))
		KEEP(*rtl8195bhp_misc.o(.rodata.str1*))		
		KEEP(*fw_flash_boot.o(.rodata.str1*))
		KEEP(*rtl8195bhp_sce.o(.rodata.str1*))

  	    KEEP(*rtl8195bhp_*.o(.rodata.str1*))

		KEEP(*rtl8195bhp_uart.o(.rodata*))		
		KEEP(*rtl8195bhp_icc.o(.rodata*))		
		KEEP(*rtl8195bhp_efuse.o(.rodata*))		
		KEEP(*rtl8195bhp_gdma.o(.rodata*))		
		KEEP(*rtl8195bhp_pinmux.o(.rodata*))		
		KEEP(*rtl8195bhp_misc.o(.rodata*))		
		KEEP(*rtl8195bhp_sce.o(.rodata*))		

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

	.rom.stubs :
	{
		. = ALIGN(0x10);
		__rom_stubs_hal_syson = .;
		KEEP(*(.rom.hal_syson.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_timer = .;
		__rom_stubs_hal_timer_s = .;
		KEEP(*(.rom.hal_timer.stubs))

		. = ALIGN(0x10);
		__rom_stubs_int_vector = .;
		KEEP(*(.rom.hal_vector.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_crypto = .;
		KEEP(*(.rom.hal_crypto_s.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_uart = .;
		KEEP(*(.rom.hal_uart.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_icc = .;
		KEEP(*(.rom.hal_icc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_efuse = .;
		KEEP(*(.rom.hal_efuse.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_gdma = .;
		__rom_stubs_hal_gdma_s = .;
		KEEP(*(.rom.hal_gdma.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_spic = .;
		KEEP(*(.rom.hal_spic.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_flash = .;
		KEEP(*(.rom.hal_flash.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_pinmux = .;
		KEEP(*(.rom.hal_pinmux.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_cache = .;
		KEEP(*(.rom.hal_cache.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_sce = .;
		KEEP(*(.rom.hal_sce.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_misc = .;
		KEEP(*(.rom.hal_misc.stubs))		

		. = ALIGN(0x10);
		__rom_stubs_flash_boot = .;
		KEEP(*(.rom.sboot.stubs))		
        
		. = ALIGN(0x10);
		__rom_stubs_stdprintf_s = .;
		KEEP(*(.rom.printf.stubs))		

		. = ALIGN(0x10);
		__rom_stubs_strproc = .;
		KEEP(*(.rom.strproc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_utility = .;
		KEEP(*(.rom.utility.stubs))	

		/**** New stubs for B-Cut ROM start from here ****/
		
		. = ALIGN(0x10);
		__b_cut_rom_stubs_start_s = .;
		
		__rom_stubs_hal_crypto_s_ext = .;
		KEEP(*(.rom.hal_crypto_s_ext.stubs))	

	} > ROM_STUB


/************* End of ROM **************/

/* MPU protection Area Start */
	.ram.vector :
	{
		. = ALIGN(4);
		__ram_vector_start__ = .;
		KEEP(*(.ram_vector_table))
		__ram_vector_end__ = .;
		. = ALIGN(4);
		/* thses should be protected by MPU */
		KEEP(*(.rom.irq.bss))
	} > VECTORS_RAM
/* MPU protection Area End */

	.data_of_rom : AT (__rom_etext)		/* for ROM image building */
	{
		. = ALIGN(4);
		__rom_data_start__ = .;

		/**** ROM data ****/
		KEEP(*system_rtl8195bhp.o(.data*))
		KEEP(*startup.o(.data*))
		KEEP(*rtl8195bhp_irq.o(.data*))
		KEEP(*fw_flash_boot.o(.data*))
		KEEP(*fw_otu.o(.data*))
		KEEP(*fw_uart_boot.o(.data*))
		KEEP(*(.rom.hal_cache.data))
		KEEP(*(.rom.hal_flash.data))
		KEEP(*(.rom.hal_gdma.data))
		KEEP(*(.rom.hal_uart.data))
		KEEP(*(.rom.hal_timer.data))
		KEEP(*(.rom.hal_icc.data))
		KEEP(*(.rom.hal_efuse.data))
		KEEP(*(.rom.hal_spic.data))
		KEEP(*(.rom.hal_crypto_s.data))
		KEEP(*rtl8195bhp_rom_s_crypto.o(.data*))

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
		KEEP(*(.rom.hal_syson.bss))
		KEEP(*(.rom.hal_uart.bss))
		KEEP(*(.rom.hal_timer.bss))
		KEEP(*(.rom.hal_icc.bss))
		KEEP(*(.rom.hal_efuse.bss))
        KEEP(*(.rom.hal_gdma.bss))
        KEEP(*(.rom.hal_spic.bss))
        KEEP(*(.rom.hal_flash.bss))        
		KEEP(*(.rom.hal_pinmux.bss))
		KEEP(*(.rom.hal_cache.bss))
		KEEP(*(.rom.hal_sce.bss))
		KEEP(*(.infra.rom.bss))
		KEEP(*(.stdioport.bss))
		KEEP(*strproc.o(.bss*))
		KEEP(*(.rom.wlan.bss))
		KEEP(*(.rom.hal_crypto_s.bss))
		__rom_bss_end__ = .;

	} > ROM_USED_RAM

	/* Non-secure callable function */
	/* .sgstubs : for Old ASDK */
	.sgstubs :
	{
		KEEP(*(.ns_entry_func.text*))
	} > NSC

	.gnu.sgstubs :
	{
		__nsc_start__ = .;
		KEEP(*(.ns_entry_func.text*))
		__nsc_end__ = .;
	} > NSC

	.ram.img.signature :
	{
		__ram_img_signature__ = .;
		KEEP(*(.start.ram.sign*))		
	} > RAM_IMG_SIGN

	.ram.func.table :
	{
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;

	} > RAM_FUN_TABLE

	.ram.data : AT (__etext)
	{
		__fw_img_start__ = .;
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
		__psram_bss_end__ = .;
		__lpddr_bss_end__ = .;
	} > EXTERNAL_RAM

	.ram.code_text : AT (__etext2)
	{
		. = ALIGN(4);
		__etext2 = .;

		. = ALIGN(32);
		__ram_entry_text_start__ = .;
		*(.ram_entry_func.text*)
		__ram_entry_text_end__ = .;
		
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

	.ram.bss :
	{
		. = ALIGN(16);
		*(.ram.bss.noinit*)

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

	/* templary BSS for ROM code, it will be recycled
	   and be used by RAM code */
	.rom_temp_use.bss :
	{
		. = ALIGN(4);
		__rom_temp_bss_start__ = .;
		KEEP(*(.rom_temp.bss))		
		__rom_temp_bss_end__ = .;

		. = ALIGN(32);
		
		__rom_sboot_bss_start__ = .;
		KEEP(*(.rom.sboot.bss))		
		__rom_sboot_bss_end__ = .;

		. = ALIGN(32);

		__rom_boot_loader_tmp_buf_start__ = .;
		KEEP(*(.rom_boot_export.bss*))		
		__rom_boot_loader_tmp_buf_end__ = .;
		

	} > DTCM_RAM

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
