

ENTRY(Entry)

/* SPECIFY THE SYSTEM MEMORY MAP */
__TI_STACK_SIZE = 0x4000;
__STACK_SIZE = __TI_STACK_SIZE;

__HEAP_SIZE = 0x400;
MEMORY
{
    SRAM (RWX) : org = 0x402f0000, len = 0x10000
    OCMCRAM1      : org = 0x40300000,  len = 0x0007FC00  /* OCMC RAM1        */
    /* Below area is reserved for vector table. Do not allocate anything here*/
    OCMC_VEC_TBL  : org = 0x4037FC00,  len = 0x400
    OCMC_RAM2 : org = 0x40400000, len = 0x100000
    OCMC_RAM3 : org = 0x40500000, len = 0x100000
    APP_CODE_MEM : org = 0x80001000, len = 0x1ff000
    /* The below memory section is reserved for memory alloc */
    APP_CACHED_DATA_MALLOC_MEM : org = 0x80200000, len = 0x4000000
    APP_CACHED_DATA_MEM : org = 0x84200000, len = 0x4000000
    APP_UNCACHED_DATA_BLK3_MEM : org = 0xa0000000, len = 0x200000
    APP_CACHED_DATA_BLK1_MEM : org = 0x88200000, len = 0xFE00000
    APP_CACHED_DATA_BLK2_MEM : org = 0x98000000, len = 0x8000000
}

/*
 * In order to put the .bass, .text, .data, .heap or .stack into a
 * different memory section, change the corresponding REGION_ALIAS.
 */
REGION_ALIAS("REGION_BSS", APP_CACHED_DATA_MEM);
REGION_ALIAS("REGION_TEXT", APP_CODE_MEM);
REGION_ALIAS("REGION_DATA", APP_CACHED_DATA_MEM);
REGION_ALIAS("REGION_STACK", APP_CACHED_DATA_MEM);
REGION_ALIAS("REGION_HEAP", APP_CACHED_DATA_MEM);
REGION_ALIAS("REGION_ARM_EXTAB", APP_CACHED_DATA_MEM);
REGION_ALIAS("REGION_ARM_EXIDX", APP_CACHED_DATA_MEM);

/* SPECIFY THE SYSTEM MEMORY MAP */
SECTIONS
{
    .bss:mallocSection (NOLOAD) : {*(.bss:mallocSection)}  > APP_CACHED_DATA_MALLOC_MEM
	.bss:extMemNonCache:vpdma : {*(.bss:extMemNonCache:vpdma)}  > APP_UNCACHED_DATA_BLK3_MEM
    .bss:frameBuffer (NOLOAD) : {*(.bss:frameBuffer)}  > APP_CACHED_DATA_BLK1_MEM
    .bss:tilerBuffer (NOLOAD) : {*(.bss:tilerBuffer)}  > APP_CACHED_DATA_BLK2_MEM
    .plt : {*(.plt)}  > APP_CODE_MEM
    BOARD_IO_DELAY_DATA : {*(BOARD_IO_DELAY_DATA)}  > OCMC_RAM1
    BOARD_IO_DELAY_CODE : {*(BOARD_IO_DELAY_CODE)}  > OCMC_RAM1
    .vecs : {*(.vecs)}  > APP_CODE_MEM
    .c_int00 : {
        KEEP (*(.c_int00))
    } > REGION_TEXT

    .text : {
        CREATE_OBJECT_SYMBOLS
        KEEP (*(.resetVecs))
        KEEP (*(.text))
        *(.text.*)
        *(.gnu.linkonce.t*)
        *(.gnu.warning)
        *(.glue*)
        . = ALIGN(0x4);
        KEEP (*(.ctors))
        *(.gnu.linkonce.r.*)
        . = ALIGN(0x4);
        __init_array_start = .;
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        __init_array_end = .;
        *(.init)
        *(.fini*)
    } > REGION_TEXT
    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > REGION_TEXT

    .ARM.extab : {
        *(.ARM.extab*)
        *(.gnu.linkonce.armextab.*)
    } > REGION_ARM_EXTAB

    .ARM.exidx : {
        __exidx_start = .;
        *(.ARM.exidx*)
        *(.gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > REGION_ARM_EXIDX

    etext   = .;
    _etext  = .;
    __etext = .;

    .data : {
        __data_load__ = LOADADDR (.data);
        __data_start__ = .;
        *(.got.plt)
        *(.got)
        *(.shdata)
        KEEP (*(.data))
        KEEP (*(.data*))
        *(.gnu.linkonce.d.*)
        . = ALIGN (4);
        __data_end__ = .;
    } > REGION_DATA

    /*
     * Place .heap section before .bss and .stack as the _sbrk
     * implementation in librdimon.a compares the (heap_end + incr)
     * to the current SP value to check if the heap has overlapped
     * with the stack. 
     *
     * If .heap is placed between .bss and .stack in a SYS/BIOS app,
     * when the task stack (allocated in .bss) is the current stack,
     * the heap check in _sbrk will fail and trigger an error even
     * though the heap might not have actually overlapped with the
     * system stack.
     */
    .heap : ALIGN(0x100) {
        __heap_start__ = .;
        end = __heap_start__;
        _end = end;
        __end = end;
        . += __HEAP_SIZE;
        __heap_end__ = .;
        __HeapLimit = __heap_end__;
    } > REGION_HEAP

    .bss ALIGN(0x04): {
        _bss_start = .;
        *(.shbss)
        KEEP (*(.bss))
        *(.bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN (4);
        _bss_end = .;
    } > REGION_BSS

    .stack : ALIGN(0x0008) {
        __TI_STACK_BASE = .;
        stack_start = .;
        *(.stack.*) ;
        . += __TI_STACK_SIZE;
        stack_end = .;
    } > REGION_STACK

    .stab           0 : { *(.stab) }
    .stabstr        0 : { *(.stabstr) }
    .stab.excl      0 : { *(.stab.excl) }
    .stab.exclstr   0 : { *(.stab.exclstr) }
    .stab.index     0 : { *(.stab.index) }
    .stab.indexstr  0 : { *(.stab.indexstr) }
    .comment        0 : { *(.comment) }

    .debug          0 : { *(.debug) }
    .line           0 : { *(.line)  }
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_info     0 : { *(.debug_info) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    .debug_weaknames    0 : { *(.debug_weaknames) }
    .debug_funcnames    0 : { *(.debug_funcnames) }
    .debug_typenames    0 : { *(.debug_typenames) }
    .debug_varnames     0 : { *(.debug_varnames) }
    .debug_pubtypes     0 : { *(.debug_pubtypes) }
    .debug_ranges       0 : { *(.debug_ranges) }

     _stack = stack_end;
     .a15_vector_table : {
     __vector_base__ = .;
        *(.a15_vector_table.*) ;
     __vector_base_end__ = .;
    } > OCMC_VEC_TBL
}




