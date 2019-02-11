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
**|         Copyright (c) 2007 - 2017 Texas Instruments Incorporated         |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

/* Linker for DSP1 instance, not DSP2 */

-stack 0x2000
-heap 0x800000
-l ../../../../../../lib/vxlib.lib
-l ../../../../../../lib/vxlib_cn.lib
-l ../../../../../../lib/common.lib

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
      vxlib.a*<*.o*> (.text:optimized)
    } SIZE(_kernel_size)

    .kernel_data {
      vxlib.a*<*.o*> (.bss)
      vxlib.a*<*.o*> (.const)
      vxlib.a*<*.o*> (.neardata)
      vxlib.a*<*.o*> (.rodata)
      vxlib.a*<*.o*> (.far)
      vxlib.a*<*.o*> (.fardata)
      vxlib.a*<*.o*> (.switch)
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
    vxlib.a*<*.o*> (.text:optimized)
  } SIZE(_kernel_size) > EXT_MEM

  .kernel_data {
    vxlib.a*<*.o*> (.bss)
    vxlib.a*<*.o*> (.const)
    vxlib.a*<*.o*> (.neardata)
    vxlib.a*<*.o*> (.rodata)
    vxlib.a*<*.o*> (.far)
    vxlib.a*<*.o*> (.fardata)
    vxlib.a*<*.o*> (.switch)
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

#endif
