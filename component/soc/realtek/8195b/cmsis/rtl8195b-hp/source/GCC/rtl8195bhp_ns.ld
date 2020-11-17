/* Linker script to configure memory regions. */

/* Select External RAM type - 1: LPDDR SDRAM 2: PSRAM */
useERAM = 1;

MEMORY
{
  ITCM_ROM (rx) 		: ORIGIN = 0x00003000, LENGTH = 0x00008000 - 0x00003000
  ITCM_RAM (rx) 		: ORIGIN = 0x00010000, LENGTH = 0x00030000 - 0x00010000
  ROM_STUB (rx) 		: ORIGIN = 0x10000000, LENGTH = 0x10002000 - 0x10000000
  ROM (rx) 				: ORIGIN = 0x10002000, LENGTH = 0x1007E000 - 0x10002000

  DTCM_RAM (wrx) 		: ORIGIN = 0x2000A000, LENGTH = 0x20010000 - 0x2000A000
  DTCM_ROM (rx) 		: ORIGIN = 0x20010000, LENGTH = 0x20017000 - 0x20010000

  /* The vector table, it must start with 256 bytes aligned address */
  /* The Reset_Handler also is the NS region code entry function */
  VECTORS_RAM (rwx)     : ORIGIN = 0x20100000, LENGTH = 0x20100100 - 0x20100000
  
  /* reserved for ROM code */
  ROM_USED_RAM (rwx)    : ORIGIN = 0x20100100, LENGTH = 0x20100900 - 0x20100100
  
  /* RAM functions entry table */
  RAM_FUN_TABLE (rwx)   : ORIGIN = 0x20100900, LENGTH = 0x20100A00 - 0x20100900
  
  /* Internal SRAM for text, rodata & data */
  RAM (rwx)             : ORIGIN = 0x20100A00, LENGTH = 0x20118000 - 0x20100A00

  /* Non-Cacheable memory, defined by MPU configuration */
  RAM_NC (rwx)          : ORIGIN = 0x20118000, LENGTH = 0x20120000 - 0x20118000

  /* Following RAM(136K) is shared by CPU and Video Encoder, CPU can use it only when Video Encoder is off */
  RAM_SHARED (rwx)      : ORIGIN = 0x20158000, LENGTH = 0x2017A000 - 0x20158000

  /* PSRAM memory */
  /* the range of PSRAM memory in non-secure region must match with the SAU setting at ram_start() */
  PSRAM (rx) 		    : ORIGIN = 0x60100000, LENGTH = 0x60800000 - 0x60100000
  
  /* LPDDR memory */
  /* the range of LPDDR memory in non-secure region must match with the SAU setting at ram_start() */
  RAM_LPDDR (rx) 		: ORIGIN = 0x70000000, LENGTH = 0x71C00000 - 0x70000000

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
_start_addr = 0x1006f000;
ENTRY(_start_addr)

__sram_end__ = ORIGIN(RAM) + LENGTH(RAM);
__eram_end__ = ORIGIN(EXTERNAL_RAM) + LENGTH(EXTERNAL_RAM);

SECTIONS
{
	.rom.itcm.text :
	{
		KEEP(*(.rom.ssl.itcm))
		KEEP(*(.rom.apple.itcm))
	} > ITCM_ROM

	.rom.dtcm.data :
	{
		KEEP(*(.rom.ssl.dtcm))
		KEEP(*(.rom.apple.dtcm))
	} > DTCM_ROM

	.rom.ns_vector_tbl :
	{
		KEEP(*(.rom_ns.vectors))
		__Vectors_End = .;
		__Vectors_Size = __Vectors_End - __Vectors_NS;
		__end__ = .;

	} > ROM

	.rom.text :
	{
		. = ALIGN(0x100);

		KEEP(*startup_rtl8195bhp.o(.text*))
		KEEP(*system_rtl8195bhp.o(.text*))
		KEEP(*(.startup.text))
		KEEP(*(.vector.text))
		KEEP(*(.sysstart.text))
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
		KEEP(*(.rom.hal_pwm.text))
		KEEP(*(.rom.hal_pwm.rodata))
		KEEP(*(.rom.hal_gpio.text))
		KEEP(*(.rom.hal_gpio.rodata))
		KEEP(*(.rom.hal_sdioh.text))
		KEEP(*(.rom.hal_sdioh.rodata))
		KEEP(*(.rom.hal_gdma.text*))
		KEEP(*(.rom.hal_gdma.rodata*))
		KEEP(*(.rom.hal_spic.text*))
		KEEP(*(.rom.hal_spic.rodata*))
		KEEP(*(.rom.hal_flash.text*))
		KEEP(*(.rom.hal_flash.rodata*))
		KEEP(*(.rom.hal_ssi.text*))
		KEEP(*(.rom.hal_ssi.rodata*))
		KEEP(*(.rom.hal_cache.text*))
		KEEP(*(.rom.hal_cache.rodata*))
		KEEP(*(.rom.hal_sgpio.text*))
		KEEP(*(.rom.hal_sgpio.rodata*))
		KEEP(*(.rom.hal_i2s.text*))
		KEEP(*(.rom.hal_i2s.rodata*))		
		KEEP(*(.rom.hal_pcm.text*))
		KEEP(*(.rom.hal_pcm.rodata*))
		KEEP(*(.rom.hal_eth.text))
		KEEP(*(.rom.hal_eth.rodata))
		KEEP(*(.rom.hal_adc.text*))
		KEEP(*(.rom.hal_adc.rodata*))
		KEEP(*(.rom.hal_i2c.text*))
		KEEP(*(.rom.hal_i2c.rodata*))
		KEEP(*(.rom.hal_lpi.text*))
		KEEP(*(.rom.hal_lpi.rodata*))
		KEEP(*(.rom.hal_sdiod.text*))
		KEEP(*(.rom.hal_sdiod.rodata*))
		
		KEEP(*rtl8195bhp_syson.o(.rodata*))
		KEEP(*rtl8195bhp_uart.o(.rodata*))
		KEEP(*rtl8195bhp_gdma.o(.text*))
		KEEP(*rtl8195bhp_gdma.o(.rodata*))
		KEEP(*rtl8195bhp_adc.o(.text*))
		KEEP(*rtl8195bhp_adc.o(.rodata*))
		KEEP(*rtl8195bhp_i2c.o(.text*))
		KEEP(*rtl8195bhp_i2c.o(.rodata*))
		KEEP(*rtl8195bhp_rom_ns_crypto.o(.text*))
		KEEP(*rtl8195bhp_rom_ns_crypto.o(.rodata*))
		KEEP(*rtl8195bhp_lpi.o(.rodata*))
		KEEP(*rtl8195bhp_sdio_dev.o(.rodata*))

		KEEP(*(.rom.hal_icc.text))
		KEEP(*(.rom.hal_icc.rodata))

		/**** Utility ROM code ****/
		KEEP(*(.infra.rom.text))
		KEEP(*(.stdioport.text))
		KEEP(*(.xprintf.text))
		KEEP(*(.xprintf.rodata))
		KEEP(*(.rtlprintf.text))
		KEEP(*(.rtlprintf.rodata))
		KEEP(*(.rtlprintf.text))
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

		/**** WLAN ROM code ****/
		KEEP(*(.rom.wlan.text))
		KEEP(*(.rom.wlan.rodata))

		/**** Apple crypto ROM code ****/
		KEEP(*(.rom.apple.text))
		KEEP(*(.rom.apple.rodata))

		/**** SSL ROM code ****/
		KEEP(*(.rom.ssl.text))
		KEEP(*(.rom.ssl.rodata))

		/**** FAAC ROM code ****/
		KEEP(*(.rom.faac.text))
		KEEP(*(.rom.faac.rodata))

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

		KEEP(*startup_rtl8195bhp.o(.rodata.str1*))
		KEEP(*startup.o(.rodata.str1*))
		KEEP(*consol_cmds.o(.rodata.str1*))
		KEEP(*shell.o(.rodata.str1*))
		KEEP(*xprintf.o(.rodata.str1*))
		KEEP(*rtl_printf.o(.rodata.str1*))
		KEEP(*utility.o(.rodata.str1*))

		KEEP(*rtl8195bhp_syson.o(.rodata.str1*))
		KEEP(*rtl8195bhp_irq_ns.o(.rodata.str1*))
		KEEP(*rtl8195bhp_timer.o(.rodata.str1*))
		KEEP(*rtl8195bhp_pwm.o(.rodata.str1*))
		KEEP(*rtl8195bhp_uart.o(.rodata.str1*))
		KEEP(*rtl8195bhp_gdma.o(.rodata.str1*))
		KEEP(*rtl8195bhp_gpio.o(.rodata.str1*))
		KEEP(*rtl8195bhp_sdio_host.o(.rodata.str1*))
		KEEP(*rtl8195bhp_sgpio.o(.rodata.str1*))
		KEEP(*rtl8195bhp_i2s.o(.rodata.str1*))
		KEEP(*rtl8195bhp_pcm.o(.rodata.str1*))
		KEEP(*rtl8195bhp_adc.o(.rodata.str1*))
		KEEP(*rtl8195bhp_eth.o(.rodata.str1*))
		KEEP(*rtl8195bhp_i2c.o(.rodata.str1*))
		KEEP(*rtl8195bhp_lpi.o(.rodata.str1*))
		KEEP(*rtl8195bhp_misc.o(.rodata.str1*))
		KEEP(*rtl8195bhp_uart.o(.rodata*))		
		KEEP(*rtl8195bhp_gdma.o(.rodata*))		
		KEEP(*rtl8195bhp_ssi.o(.rodata*))		
		KEEP(*rtl8195bhp_misc.o(.rodata*))		
		KEEP(*rtl8195bhp_icc.o(.rodata*))		
		KEEP(*rtl8195bhp_icc.o(.rodata.str1*))
		KEEP(*rtl8195bhp_sdio_dev.o(.rodata.str1*))

		KEEP(*rom_rtw_message_e.o(.rodata.str1*))
		KEEP(*rom_rtw_message_f.o(.rodata.str1*))
		KEEP(*rom_mbedtls_bignum.o(.rodata.str1*))
		KEEP(*rom_mbedtls_ecp.o(.rodata.str1*))
		KEEP(*rom_mbedtls_ecp_curves.o(.rodata.str1*))
		KEEP(*rom_mbedtls_oid.o(.rodata*))
		KEEP(*rom_mbedtls_md.o(.rodata*))
		KEEP(*rom_mbedtls_md_wrap.o(.rodata.str1*))
		KEEP(*rom_mbedtls_pem.o(.rodata.str1*))
		KEEP(*rom_mbedtls_dhm.o(.rodata.str1*))
		KEEP(*rom_mbedtls_ecjpake.o(.rodata.str1*))
		KEEP(*rom_mbedtls_pk.o(.rodata*))
		KEEP(*rom_mbedtls_pk_wrap.o(.rodata.str1*))
		KEEP(*rom_mbedtls_pkwrite.o(.rodata.str1*))

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
	/* __rom_stubs_symb_ns4s always must be the 1st symbol of ROM stubs */
		. = ALIGN(0x10);
		__rom_stubs_symb_ns4s = .;
		KEEP(*(.rom.ns4s.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_syson = .;
		KEEP(*(.rom.hal_syson.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_timer = .;
		KEEP(*(.rom.hal_timer.stubs))

		. = ALIGN(0x10);
		__rom_stubs_int_vector = .;
		KEEP(*(.rom.hal_vector.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_crypto = .;
		__rom_stubs_hal_crypto_ns = .;
		KEEP(*(.rom.hal_crypto_ns.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_pwm = .;
		KEEP(*(.rom.hal_pwm.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_uart = .;
		KEEP(*(.rom.hal_uart.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_gpio = .;
		KEEP(*(.rom.hal_gpio.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_sdioh = .;
		KEEP(*(.rom.hal_sdioh.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_gdma = .;
		__rom_stubs_hal_gdma_ns = .;
		KEEP(*(.rom.hal_gdma.stubs))
 
        . = ALIGN(0x10);
		__rom_stubs_hal_ssi = .;
		KEEP(*(.rom.hal_ssi.stubs))
		
		. = ALIGN(0x10);
		__rom_stubs_hal_cache = .;
		KEEP(*(.rom.hal_cache.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_sgpio = .;
		KEEP(*(.rom.hal_sgpio.stubs))
        . = ALIGN(0x10);
		__rom_stubs_hal_i2s = .;
		KEEP(*(.rom.hal_i2s.stubs))

        . = ALIGN(0x10);
		__rom_stubs_hal_pcm = .;
		KEEP(*(.rom.hal_pcm.stubs))	
   
		
		. = ALIGN(0x10);
		__rom_stubs_hal_adc = .;
		KEEP(*(.rom.hal_adc.stubs))
    
		. = ALIGN(0x10);
		__rom_stubs_hal_i2c = .;
		KEEP(*(.rom.hal_i2c.stubs))
		
		. = ALIGN(0x10);  
		__rom_stubs_hal_eth = .;
		KEEP(*(.rom.hal_eth.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_misc = .;
		KEEP(*(.rom.hal_misc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_hal_lpi = .;
		KEEP(*(.rom.hal_lpi.stubs))
				
		. = ALIGN(0x10);  
		__rom_stubs_shell = .;
		KEEP(*(.rom.shellcmd.stubs))

		. = ALIGN(0x10);
		__rom_stubs_stdprintf_ns = .;
		KEEP(*(.rom.printf.stubs))		

		. = ALIGN(0x10);
		__rom_stubs_strproc = .;
		KEEP(*(.rom.strproc.stubs))

		. = ALIGN(0x10);
		__rom_stubs_utility = .;
		__rom_stubs_utility_ns = .;
		KEEP(*(.rom.utility.stubs))

		. = ALIGN(0x10);
		__rom_stubs_wlan = .;
		KEEP(*(.rom.wlan.stubs))

		. = ALIGN(0x10);
		__rom_stubs_apple = .;
		KEEP(*(.rom.apple.stubs))

		. = ALIGN(0x10);
		__rom_stubs_ssl = .;
		KEEP(*(.rom.ssl.stubs))

		. = ALIGN(0x10);
		__rom_stubs_faac = .;
		KEEP(*(.rom.faac.stubs))

		/**** New stubs for B-Cut ROM start from here ****/
		. = ALIGN(0x10);
		__b_cut_rom_stubs_start_ns = .;

		__rom_stubs_hal_icc = .;
		__rom_stubs_hal_icc_ns = .;
		KEEP(*(.rom.hal_icc.stubs))

		/**** New stubs for C-Cut ROM start from here ****/
		. = ALIGN(0x10);
		__c_cut_rom_stubs_start_ns = .;
		
		__rom_stubs_hal_sdiod = .;
		KEEP(*(.rom.hal_sdiod.stubs))

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
/*	.data_of_rom :						/* for RAM image building */
	{
		. = ALIGN(4);
		__rom_data_start__ = .;

		/**** ROM data ****/
		KEEP(*system_rtl8195bhp.o(.data*))
		KEEP(*rtl8195bhp_handler_ns.o(.data*))
		KEEP(*rtl8195bhp_irq_ns.o(.data*))
		KEEP(*rtl8195bhp_symbns4s.o(.data*))
		KEEP(*startup_ns.o(.data*))
		KEEP(*(.rom.hal_uart.data))
		KEEP(*(.rom.hal_timer.data))
		KEEP(*(.rom.hal_pwm.data))
		KEEP(*(.rom.hal_gpio.data))
		KEEP(*(.rom.hal_sdioh.data))
		KEEP(*(.rom.hal_sgpio.data))
		KEEP(*(.rom.hal_i2s.data))
		KEEP(*(.rom.hal_pcm.data))
		KEEP(*(.rom.hal_eth.data))
		KEEP(*(.rom.hal_cache.data))
		KEEP(*(.rom.hal_gdma.data))
		KEEP(*(.rom.hal_adc.data))
		KEEP(*(.rom.hal_crypto_ns.data))
		KEEP(*(.rom.hal_ssi.data))
		KEEP(*(.rom.hal_i2c.data))
		KEEP(*(.rom.hal_icc.data))		
		KEEP(*(.xprintf.data))
		KEEP(*rtl8195bhp_adc.o(.data*))
		KEEP(*rtl8195bhp_i2c.o(.data*))
		KEEP(*rtl8195bhp_rom_ns_crypto.o(.data*))
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
		KEEP(*(.rom.hal_pwm.bss))
		KEEP(*(.rom.hal_gpio.bss))
		KEEP(*(.rom.hal_adc.bss))
		KEEP(*(.rom.hal_i2c.bss))
        KEEP(*(.rom.hal_gdma.bss))
        KEEP(*(.rom.hal_spic.bss))
        KEEP(*(.rom.hal_flash.bss))
        KEEP(*(.rom.hal_ssi.bss))
		KEEP(*(.rom.hal_sdioh.bss))
		KEEP(*(.rom.hal_cache.bss))
		KEEP(*(.rom.hal_crypto_ns.bss))
		KEEP(*(.rom.hal_sgpio.bss))
		KEEP(*(.rom.hal_i2s.bss))
		KEEP(*(.rom.hal_pcm.bss))
		KEEP(*(.rom.hal_eth.bss))
		KEEP(*(.rom.hal_lpi.bss))
		KEEP(*(.rom.hal_icc.bss))
		KEEP(*(.rom.hal_sdiod.bss))
		KEEP(*(.xprintf.bss))
		KEEP(*(.logbuf.bss))
		KEEP(*(.stdioport.bss))
		KEEP(*strproc.o(.bss*))
		KEEP(*rtl8195bhp_adc.o(.bss*))
		KEEP(*rtl8195bhp_i2c.o(.bss*))
		KEEP(*rtl8195bhp_flash.o(.bss*))

		KEEP(*(.rom.wlan.bss))
		KEEP(*(.rom.ssl.bss))
		__rom_bss_end__ = .;

	} > ROM_USED_RAM

	.ram.func.table :
	{
		__fw_img_start__ = .;
		__ram_start_table_start__ = .;
		KEEP(*(SORT(.start.ram.data*)))
		__ram_start_table_end__ = .;
		
	} > RAM_FUN_TABLE

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
	.non_cacheable :
	{
		. = ALIGN(32);
		__nc_data_start__ = .;
		*(.non_cache.data*)
		__nc_bss_start__ = .;
		*(.non_cache.bss*)
		__nc_bss_end__ = .;
	} > RAM_NC

	/* RAM_SHARED memory is shared by CPU and Video Encoder, CPU can locate memory here only when Video Encoder is off */
	.share_ram :
	{
	} > RAM_SHARED

	/* templary BSS for ROM code, it will be recycled
	   and be used by RAM code */
	.rom_temp_use.bss :
	{
		. = ALIGN(4);
		__rom_temp_bss_start__ = .;
		KEEP(*(.rom_temp.bss))		
		__rom_temp_bss_end__ = .;
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
