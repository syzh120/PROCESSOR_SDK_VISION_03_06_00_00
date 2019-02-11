/*
*
* Copyright (c) 2007-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

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
**|                                                                          |**
**|                                                                          |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

/* Linker for DSP1 instance, not DSP2 */

-stack 0x3000
-heap 0x7000000

MEMORY {
   L1P_SRAM           : origin = 0x00E00000,  len = 0x8000
   L1D_SRAM           : origin = 0x00F00000,  len = 0x4000     /* 16 KB SRAM  */
   L1D_CACHE          : origin = 0x00F04000,  len = 0x4000     /* 16 KB cache */
   L2_SRAM            : origin = 0x00800000,  len = 0x28000    /* SARAM in L2, = 256 + 32 - 128 = 160 KB*/ 
   L2_CACHE           : origin = 0x00828000,  len = 0x20000    /* Cache for L2, which is configured as 128 KB*/
   DSP2_L2_SRAM       : origin = 0x40800000,  len = 0x48000
   SL2_SRAM           : origin = 0x5B000000,  len = 0x40000
   EXT_MEM_CACHE      : origin = 0x80000000,  len = 0x08000000 /* DSP Used cachable area */
}

SECTIONS
{
  vectors   :> EXT_MEM_CACHE
  .cinit    :> EXT_MEM_CACHE
  .cio      :> EXT_MEM_CACHE
  .bss      :> EXT_MEM_CACHE
  .text     :> EXT_MEM_CACHE
  .const    :> EXT_MEM_CACHE
  .far      :> EXT_MEM_CACHE
  .fardata  :> EXT_MEM_CACHE
  .neardata :> EXT_MEM_CACHE
  .rodata   :> EXT_MEM_CACHE
  .sysmem   :> EXT_MEM_CACHE
  .switch   :> EXT_MEM_CACHE

  .L2SramSect   :> L2_SRAM
  .stack        :> L2_SRAM
}
