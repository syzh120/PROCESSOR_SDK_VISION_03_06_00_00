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

-stack 0x2000
-heap 0x800000
-l ../../../../../lib/vlib.lib
-l ../../../../../lib/vlib_cn.lib
-l ../../../../../lib/common.lib

MEMORY {
   L1P_SRAM     : origin = 0x00E00000,  len = 0x8000
   L1D_SRAM     : origin = 0x00F00000,  len = 0x8000
   L2_SRAM      : origin = 0x00800000,  len = 0x48000
   DSP2_L2_SRAM : origin = 0x40800000,  len = 0x48000
   SL2_SRAM     : origin = 0x5B000000,  len = 0x40000
   EXT_MEM      : origin = 0x80000000,  len = 0x10000000
}

#if defined(LINK_L2SRAM)

SECTIONS
{

  GROUP (SRAM_SECTIONS) {

    .kernel {
      vlib.a*<*.o*> (.text:optimized)
    } SIZE(_kernel_size)

    .kernel_data {
      vlib.a*<*.o*> (.bss)
      vlib.a*<*.o*> (.const)
      vlib.a*<*.o*> (.neardata)
      vlib.a*<*.o*> (.rodata)
      vlib.a*<*.o*> (.far)
      vlib.a*<*.o*> (.fardata)
      vlib.a*<*.o*> (.switch)
    } SIZE(_data_size)

    .rts_mem {
      rts*<memcpy64.o*> (.text)
      rts*<memset.o*> (.text)
      rts*<strasg.o*> (.text)
      rts*<divi.o*> (.text)
      rts*<divu.o*> (.text)
      rts*<divd.o*> (.text)
      rts*<divf.o*> (.text)
      rts*<modf.o*> (.text)
      rts*<fixfu.o*> (.text)
      rts*<fixdu.o*> (.text)
      rts*<pow.o*> (.text)
      rts*<atan.o*> (.text)
      rts*<atan2.o*> (.text)
      rts*<sqrt.o*> (.text)
      rts*<round.o*> (.text)
      rts*<remu.o*> (.text)
      rts*<frcmpyd_div.o*> (.text)
      rts*<llshift.o*> (.text)
      rts*<trunc.o*> (.text)
      rts*<errno.o*> (.text)
      rts*<ldexp.o*> (.text)
      rts*<frexp.o*> (.text)
    } SIZE(_rts_size)

    .stack
    .sram_start

  } START(_sram_start) > L2_SRAM

    vectors   :> EXT_MEM
    .cinit    :> EXT_MEM
    .cio      :> EXT_MEM
    .text     :> EXT_MEM
    .bss      :> EXT_MEM
    .const    :> EXT_MEM
    .far      :> EXT_MEM
    .fardata  :> EXT_MEM
    .neardata :> EXT_MEM
    .rodata   :> EXT_MEM
    .sysmem   :> EXT_MEM
    .switch   :> EXT_MEM
}

#else

SECTIONS
{
  .sram_start START(_sram_start) > L2_SRAM NOINIT

  .kernel {
    vlib.a*<*.o*> (.text:optimized)
  } SIZE(_kernel_size) > EXT_MEM

  .kernel_data {
    vlib.a*<*.o*> (.bss)
    vlib.a*<*.o*> (.const)
    vlib.a*<*.o*> (.neardata)
    vlib.a*<*.o*> (.rodata)
    vlib.a*<*.o*> (.far)
    vlib.a*<*.o*> (.fardata)
    vlib.a*<*.o*> (.switch)
  } SIZE(_data_size) > EXT_MEM

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
}
