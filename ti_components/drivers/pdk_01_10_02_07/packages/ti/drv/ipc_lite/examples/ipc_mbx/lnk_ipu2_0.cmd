

-stack  0x20000                            /* SOFTWARE STACK SIZE           */
-heap   0x20000                            /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    /* Vector table for IPU cores is copied to 0x00000400U during the init */
    IRAM_MEM:     org = 0x00000000 len = 0x400        /* RAM 0x1FBFF*/
    /* Memory assigned to move vector table for IPU core */
    IRAM_IPU_VTBL:   org = 0x00000400 len = 0x800

    DDR3_BOOT     : org = 0x8B000000,  len = 0x00010000    /* 64 KB */
    DDR3_DSP1     : org = 0x8B010000,  len = 0x00FF0000    /* 16 MB */
    DDR3_DSP2     : org = 0x8C000000,  len = 0x01000000    /* 16 MB */
    DDR3_IPU1_0   : org = 0x8D000000,  len = 0x00800000    /* 8  MB */
    DDR3_IPU1_1   : org = 0x8D800000,  len = 0x00800000    /* 8  MB */
    DDR3_IPU2_0   : org = 0x8E000000,  len = 0x00800000    /* 8  MB */
    DDR3_IPU2_1   : org = 0x8E800000,  len = 0x00800000    /* 8  MB */
    DDR3_SR0      : org = 0x8F000000,  len = 0x00800000    /* 8  MB */
    DDR3_A15      : org = 0x8F800000,  len = 0x00800000    /* 8  MB */

}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs : load > IRAM_MEM
    .intc_text : load > IRAM_MEM
    .TI.noinit : load > IRAM_IPU_VTBL
    .init    : load > DDR3_IPU2_0

    .text    : load > DDR3_IPU2_0 /* CODE                         */
    .data    : load > DDR3_IPU2_0 /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss     : load > DDR3_IPU2_0 /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const   : load > DDR3_IPU2_0              /* GLOBAL CONSTANTS             */
    .cinit   : load > DDR3_IPU2_0
    .stack   : load > DDR3_IPU2_0            /* SOFTWARE SYSTEM STACK        */
    .plt     : load > DDR3_IPU2_0
    .sysmem  : load > DDR3_IPU2_0
    .my_sect_ddr : load > DDR3_IPU2_0

}

