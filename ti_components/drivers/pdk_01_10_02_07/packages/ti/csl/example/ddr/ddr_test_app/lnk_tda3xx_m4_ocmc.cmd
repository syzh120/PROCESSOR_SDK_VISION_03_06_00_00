

-stack  0x2000                            /* SOFTWARE STACK SIZE           */
-heap   0x2000                            /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    IRAM_MEM:     org = 0x00000000 len = 0x400        /* RAM 0x1FBFF*/
    /* Memory assigned to move vector table for IPU core */
    IRAM_IPU_VTBL:   org = 0x00000400 len = 0x800

    OCMCRAM1_1:   org = 0x00300000 len = 0x00040000    /* OCMC RAM1_1*/
    OCMCRAM1_2:   org = 0x00340000 len = 0x00010000    /* OCMC RAM1_2*/
    OCMCRAM1_3:   org = 0x00350000 len = 0x00030000    /* OCMC RAM1_3*/
	/*SBL will use 1 KB of space from address 0x80000000 for EVE */
    DDR3_A8:      org = 0x80000400 len = (0x02000000 - 0x400)  /* 32 MB */
    DDR3_DSP:     org = 0x82000000 len = 0x02000000  /* 32 MB */
    DDR3_M4:      org = 0x84000000 len = 0x02000000  /* 32 MB */
    DDR3_SR0:     org = 0x86000000 len = 0x01000000  /* 16 MB */
    DDR3_M3VPSS:  org = 0x87000000 len = 0x01000000  /* 16 MB */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs : load > IRAM_MEM
    .intc_text : load > IRAM_MEM
    .TI.noinit : load > IRAM_IPU_VTBL

    .init    : load > OCMCRAM1_3

    .text    : load > OCMCRAM1_3 /* CODE                         */
    .data    : load > OCMCRAM1_3 /* INITIALIZED GLOBAL AND STATIC VARIABLES. */
    .bss     : load > OCMCRAM1_3 /* UNINITIALIZED OR ZERO INITIALIZED */
                                            /* GLOBAL & STATIC VARIABLES.   */
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const   : load > OCMCRAM1_3              /* GLOBAL CONSTANTS             */
    .cinit   : load > OCMCRAM1_3
    .stack   : load > OCMCRAM1_2            /* SOFTWARE SYSTEM STACK        */
    .plt     : load > OCMCRAM1_3
    .sysmem  : load > OCMCRAM1_3
	.my_sect_ddr : load > OCMCRAM1_3

}
