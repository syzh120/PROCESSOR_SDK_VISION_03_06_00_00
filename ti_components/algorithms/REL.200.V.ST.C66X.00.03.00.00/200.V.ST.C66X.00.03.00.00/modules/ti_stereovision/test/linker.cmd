/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

/* Linker for DSP1 instance, not DSP2 */

-stack 0x1800
-heap 0x18000000

MEMORY {
   L1P_SRAM         : origin = 0x00E00000,  len = 0x8000
   L1D_SRAM         : origin = 0x00F00000,  len = 0x6000
   L2_SRAM          : origin = 0x00800000,  len = 0x20000
   EXT_MEM          : origin = 0x80000000,  len = 0x1F000000
   EXT_MEM_NONCACHE : origin = 0x9F000000,  len = 0x01000000   
}

SECTIONS
{
    vectors   :> EXT_MEM
    .cinit    :> EXT_MEM
    .cio      :> EXT_MEM
    .text     :> EXT_MEM
    .stack    :> EXT_MEM
    .bss      :> EXT_MEM
    .const    :> EXT_MEM
    .far      :> EXT_MEM
    .fardata  :> EXT_MEM
    .neardata :> EXT_MEM
    .rodata   :> EXT_MEM
    .sysmem   :> EXT_MEM
    .switch   :> EXT_MEM
    .dmemSect :> L1D_SRAM
    .l2memSect :> L2_SRAM
    .ddrnoncacheSect :> EXT_MEM_NONCACHE
}


