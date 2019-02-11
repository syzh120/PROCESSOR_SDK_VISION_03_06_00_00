

-stack  0x8000                          /* SOFTWARE STACK SIZE           */
-heap   0x400                           /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    L2_ROM : org = 0x0, len = 0x4000
    L2_RAM : org = 0x20000000, len = 0x10000
    OCMC_RAM1 : org = 0x40300000, len = 0x80000
    OCMC_RAM2 : org = 0x40400000, len = 0x100000
    OCMC_RAM3 : org = 0x40500000, len = 0x100000
    RST_START : org = 0x00800000  len = 0x0300
    IRAM_MEM:   org = 0x00800300  len = 0x7c00
    APP_CODE_MEM : org = 0x80001000, len = 0x1ff000
    /* The below memory section is reserved for memory alloc */  
    APP_CACHED_DATA_MALLOC_MEM : org = 0x80200000, len = 0x4000000
	APP_CACHED_DATA_MEM : org = 0x84200000, len = 0x4000000
    APP_UNCACHED_DATA_BLK3_MEM : org = 0xa0000000, len = 0x200000
    APP_CACHED_DATA_BLK1_MEM : org = 0x88200000, len = 0xFE00000
    APP_CACHED_DATA_BLK2_MEM : org = 0x98000000, len = 0x8000000
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */
SECTIONS
{
    .bss:mallocSection       : load > APP_CACHED_DATA_MALLOC_MEM, type = NOLOAD
    .bss:extMemNonCache:vpdma: load > APP_UNCACHED_DATA_BLK3_MEM
    .bss:frameBuffer: load > APP_CACHED_DATA_BLK1_MEM, type = NOLOAD
    .bss:tilerBuffer: load > APP_CACHED_DATA_BLK2_MEM, type = NOLOAD
    .text: load >> APP_CODE_MEM
    BOARD_IO_DELAY_DATA : {*(BOARD_IO_DELAY_DATA)}  > OCMC_RAM1
    BOARD_IO_DELAY_CODE : {*(BOARD_IO_DELAY_CODE)}  > OCMC_RAM1
    .csl_vect : load > RST_START
    .vects : load > IRAM_MEM
    .l2_int  : load > IRAM_MEM
    .stack: load > APP_CACHED_DATA_MEM
    GROUP: load > APP_CACHED_DATA_MEM
    {
        .bss:
        .neardata:
        .rodata:
    }
    .binit: load > APP_CODE_MEM
    .cinit: load > APP_CODE_MEM
    .init_array: load > APP_CODE_MEM
    .const: load >> APP_CODE_MEM
    .data: load >> APP_CACHED_DATA_MEM
    .fardata: load >> APP_CACHED_DATA_MEM
    .switch: load >> APP_CACHED_DATA_MEM
    .sysmem: load > APP_CACHED_DATA_MEM
    .far: load >> APP_CACHED_DATA_MEM
    .args: load > APP_CACHED_DATA_MEM align = 0x4, fill = 0 {_argsize = 0x0; }
    .cio: load >> APP_CACHED_DATA_MEM
    .bootVecs:  type = DSECT
    .resetVecs: load > 0x400
    .vecs: load > 0x400, type = DSECT
    .plt: load > APP_CODE_MEM

}


