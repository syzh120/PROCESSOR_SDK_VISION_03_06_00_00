

-stack  0x4000                            /* SOFTWARE STACK SIZE           */
-heap   0x4000                             /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
        IRAM_MEM:       org = 0x40300000  len = 0x1C000            /* RAM 0x1FBFF*/
        MMU_TLB:        ORIGIN = 0x4031C000  LENGTH = 0x000004000
        DDR3_A8:        org = 0x80500000 len =  0xA000000     /* 176 MB */
        DDR3_DSP:       org = 0x8B000000 len = 0x02000000    /* 32 MB */
        DDR3_M3VPSS:    org = 0x8D000000 len = 0x01000000    /* 16 MB */
        DDR3_M3VIDEO:   org = 0x8E000000 len = 0x01000000    /* 16 MB */
        DDR3_SR0:       org = 0x8F000000 len = 0x01000000    /* 16 MB */
        GPMC_NOR:       org = 0x08000000 len = 0x1000 /* 4 MB */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .init     : load > DDR3_A8

    .text     : load > DDR3_A8              /* CODE                         */
    .data     : load > DDR3_A8              /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss      : load > DDR3_A8              /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                     RUN_START(bss_start)
                     RUN_END(bss_end)
    .const    : load > DDR3_A8              /* GLOBAL CONSTANTS             */
    .cinit    : load > DDR3_A8
    .stack    : load > DDR3_A8              /* SOFTWARE SYSTEM STACK        */
    .gpmc_mem : load >    GPMC_NOR
    .sysmem   : load > DDR3_A8
    .plt      : load > DDR3_A8
}

