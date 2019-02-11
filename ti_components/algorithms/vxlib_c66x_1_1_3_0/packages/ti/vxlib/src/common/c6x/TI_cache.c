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

#include "../TI_memory.h"

/* DSP L1 and L2 cache registers. */
#define L2CFG  *((volatile unsigned int *)(0x01840000))
#define L2WBINV *((volatile unsigned int *)(0x01845004))
#define L2INV *((volatile unsigned int *)(0x01845008))

#define L1PCFG *((volatile unsigned int *)(L2CFG + 0x20))
#define L1PINV *((volatile unsigned int *)(0x01845028))

#define L1DCFG *((volatile unsigned int *)(L2CFG + 0x40))
#define L1DWBINV *((volatile unsigned int *)(0x01845044))
#define L1DINV *((volatile unsigned int *)(0x01845048))

#define L2_SIZE_NONE    0
#define L2_SIZE_32K     1
#define L2_SIZE_64K     2
#define L2_SIZE_128K    3
#define L2_SIZE_256K    4
#define L2_SIZE_MAX     7

int TI_cache_init(void)
{
    int    status = 0;

#ifndef _HOST_BUILD
    int                      i;
    int                      extraRam = 0;
    int                      availableRam = 0; /* Default is none */
    uint32_t                 l2config = L2_SIZE_256K; /* Default is full cache */
    volatile unsigned int   *pMAR = (volatile unsigned int *)0x01848200;

    /* DSP L1 and L2 cache configurations. */
    L1PCFG = 0x00000004u;   /* L1 program cache is configured to 32K */
    L1DCFG = 0x00000004u;   /* L1 data cache is configured to 32K */

#if defined (_TMS320C6600)
    extraRam = 32;
#endif

#ifdef SIZE_L2CACHE

#if     (SIZE_L2CACHE == 128)
    l2config  = L2_SIZE_128K;   /* L2 cache is enabled with 128K. */
    availableRam = 256 - 128;
#elif  (SIZE_L2CACHE == 64)
    l2config  = L2_SIZE_64K;    /* L2 cache is enabled with 64K. */
    availableRam = 256 - 64;
#elif  (SIZE_L2CACHE == 32)
    l2config  = L2_SIZE_32K;    /* L2 cache is enabled with 32K. */
    availableRam = 256 - 32;
#elif  (SIZE_L2CACHE == 0)
    l2config  = L2_SIZE_NONE;   /* L2 cache is disabled. */
    availableRam = 256 - 0;
#endif

#endif /* #ifdef SIZE_L2CACHE */

    status = TI_meminit(availableRam + extraRam);

    if( status ) {
        return (status); /* ERROR: There is no room in the L2SRAM, exit before enabling L2 Cache */
    }

    L2CFG  = l2config; /* Enable the L2$ according to selected configuration */

    for( i=0; i < 16; i++ ) { /* Enable cacheability for DDR: 8000 0000h - 8FFF FFFFh*/
        pMAR[i] = 1u;
    }

#endif /* #ifndef _HOST_BUILD */

    return (status);
}

int TI_cache_inval(void)
{
#ifndef _HOST_BUILD
    L1PINV = 1;     /* Invalidate L1P */
    L1DWBINV = 1;   /* Write-back, then invalidate L1D */
    L2WBINV = 1;    /* Write-back, then invalidate L2 */
#endif

    return (0);
}

