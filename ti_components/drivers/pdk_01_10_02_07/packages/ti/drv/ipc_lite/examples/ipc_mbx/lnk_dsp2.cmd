

-stack  0x1000                             /* SOFTWARE STACK SIZE           */
-heap   0x2000                             /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    IRAM_MEM:       org = 0x00800000  len = 0x8000
    MMU_TLB:        ORIGIN = 0x4031C000  LENGTH = 0x000004000

    DDR3_DSP1_BOOT : org = 0x8B000000,  len = 0x00008000    /* 32 KB */
    DDR3_DSP2_BOOT : org = 0x8B008000,  len = 0x00008000    /* 32 KB */
    DDR3_DSP1      : org = 0x8B010000,  len = 0x00FF0000    /* 16 MB */
    DDR3_DSP2      : org = 0x8C000000,  len = 0x01000000    /* 16 MB */
    DDR3_IPU1_0    : org = 0x8D000000,  len = 0x00800000    /* 8  MB */
    DDR3_IPU1_1    : org = 0x8D800000,  len = 0x00800000    /* 8  MB */
    DDR3_IPU2_0    : org = 0x8E000000,  len = 0x00800000    /* 8  MB */
    DDR3_IPU2_1    : org = 0x8E800000,  len = 0x00800000    /* 8  MB */
    DDR3_SR0       : org = 0x8F000000,  len = 0x00800000    /* 8  MB */
    DDR3_A15       : org = 0x8F800000,  len = 0x00800000    /* 8  MB */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    boot :
    {
     rts*.lib<boot.obj>(.text)
    }load > DDR3_DSP2_BOOT

    GROUP: load > DDR3_DSP2
    {
        .bss:       /* UNINITIALIZED OR ZERO INITIALIZED */
        .neardata:
        .rodata:
    }

    .vects : load > IRAM_MEM
    .l2_int  : load > IRAM_MEM
    .pmIdleFunc : load > IRAM_MEM
    .init    : load > DDR3_DSP2
    .cio     : load > DDR3_DSP2

    .text    : load > DDR3_DSP2              /* CODE                         */
    .data    : load > DDR3_DSP2              /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const   : load > DDR3_DSP2              /* GLOBAL CONSTANTS             */
    .cinit   : load > DDR3_DSP2
    .stack   : load > DDR3_DSP2            /* SOFTWARE SYSTEM STACK        */
    .far     : load > DDR3_DSP2
    .plt     : load > DDR3_DSP2
    .fardata : load > DDR3_DSP2
    .switch  : load > DDR3_DSP2
    .my_sect_ddr : load > DDR3_DSP2
    .sysmem : load > DDR3_DSP2
}

