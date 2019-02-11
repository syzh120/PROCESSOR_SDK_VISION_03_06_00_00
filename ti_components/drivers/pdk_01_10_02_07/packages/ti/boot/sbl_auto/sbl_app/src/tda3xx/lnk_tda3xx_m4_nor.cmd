/**
 *  \file     lnk_tda3xx_m4_nor.cmd
 *
 *  \brief    This file contains the System Memory Map used by Secondary
 *            Bootloader (SBL) for NOR boot mode for tda3xx SoC.
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

-stack  0x1000                            /* SOFTWARE STACK SIZE           */
-heap   0x1000                            /* HEAP AREA SIZE                */

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
    NOR_0:        org = 0x08000000 len = 0x00000200  /* NOR Memory Region1
                                                          - NOR Init Code */
    NOR_1:        org = 0x08000200 len = 0x00000100  /* NOR Memory Region2
                                                          - IPU Core1 Init */
    NOR_2:        org = 0x08000300 len = 0x03FFFD00  /* NOR Memory Region3
                                                          - Common */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs     : load > NOR_2
    .intc_text   : load > NOR_2
    .sbl_init    : load > NOR_0
    .ipu1_1_init : load > NOR_1
    .init        : load > NOR_2

    .text        : load > NOR_2           /* CODE */
    .data        : load = NOR_2, run = OCMCRAM1_3
                     LOAD_START(dataLoadStart)
                     LOAD_END(dataLoadEnd)
                     RUN_START(dataRunStart)
    .const       : load > NOR_2           /* GLOBAL CONSTANTS */
    .cinit       : load > NOR_2
    .bss         : load > OCMCRAM1_3      /* UNINITIALIZED OR ZERO INITIALIZED */
                                          /* GLOBAL & STATIC VARIABLES */
                    RUN_START(bssStart)
                    RUN_END(bssEnd)
    .stack       : load > OCMCRAM1_3      /* SOFTWARE SYSTEM STACK */
                    RUN_START(stackStart)
                    RUN_END(stackEnd)
    .plt         : load > NOR_2
    .sysmem      : load > NOR_2
    .img_hdr     : load > OCMCRAM1_2
    .img_hdr1    : load > OCMCRAM1_4

}

