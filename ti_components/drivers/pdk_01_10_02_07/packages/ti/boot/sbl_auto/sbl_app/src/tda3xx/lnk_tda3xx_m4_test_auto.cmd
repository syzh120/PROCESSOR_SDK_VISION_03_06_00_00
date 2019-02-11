/**
 *  \file     lnk_tda3xx_m4_test_auto.cmd
 *
 *  \brief    This file contains the System Memory Map used by test automation
 *            Secondary Bootloader (SBL) for QSPI and QSPI_SD boot mode for
 *            tda3xx SoC.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

-stack  0x2000                            /* SOFTWARE STACK SIZE */
-heap   0x2000                            /* HEAP AREA SIZE */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    IRAM_MEM:     org = 0x00000000 len = 0x4000      /* IRAM */
    OCMCRAM1_0:   org = 0x00300000 len = 0x00000100  /* OCMC RAM mapped
                                                        to 0x40300000 */
    OCMCRAM1_1:   org = 0x00300100 len = 0x00000100  /* OCMC RAM mapped
                                                        to 0x40300100 */
    OCMCRAM1_2:   org = 0x40300200 len = 0x00000100  /* OCMC RAM */
    OCMCRAM1_4:   org = 0x40300300 len = 0x00000100  /* OCMC RAM */
    OCMCRAM1_3:   org = 0x00300400 len = 0x0007FC00  /* OCMC RAM mapped
                                                        to 0x40300300 */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs     : load > OCMCRAM1_3
    .intc_text   : load > OCMCRAM1_3
    .sbl_init    : load > OCMCRAM1_0
    .ipu1_1_init : load > OCMCRAM1_1
    .init        : load > OCMCRAM1_3

    .text        : load > OCMCRAM1_3      /* CODE */
    .data        : load > OCMCRAM1_3      /* INITIALIZED GLOBAL AND STATIC VARIABLES */
    .const       : load > OCMCRAM1_3      /* GLOBAL CONSTANTS */
    .cinit       : load > OCMCRAM1_3
    .bss         : load > OCMCRAM1_3      /* UNINITIALIZED OR ZERO INITIALIZED */
                                          /* GLOBAL & STATIC VARIABLES */
                    RUN_START(bssStart)
                    RUN_END(bssEnd)
    .stack       : load > OCMCRAM1_3      /* SOFTWARE SYSTEM STACK */
                    RUN_START(stackStart)
                    RUN_END(stackEnd)
    .plt         : load > OCMCRAM1_3
    .sysmem      : load > OCMCRAM1_3
    .img_hdr     : load > OCMCRAM1_2
    .img_hdr1    : load > OCMCRAM1_4

}

