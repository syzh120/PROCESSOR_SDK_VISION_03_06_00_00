/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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


#ifndef CACHE_H_
#define CACHE_H_

#include <xdais_types.h>

#if (!HOST_EMULATION)

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#pragma RESET_MISRA ("required")

#define Cache_EMIFA_CFG 0x1e00000
#define Cache_EMIFA_BASE 0x2000000
#define Cache_EMIFA_LENGTH 0x8000000

#define Cache_EMIFB_CFG 0x20000000
#define Cache_EMIFB_BASE 0x80000000
#define Cache_EMIFB_LENGTH 0x10000000

#define Cache_EMIFC_CFG 0x1e00000
#define Cache_EMIFC_BASE 0x42000000
#define Cache_EMIFC_LENGTH 0x8000000

#define L2CFG    (volatile unsigned int *)0x01840000
#define L1PCFG   (volatile unsigned int *)0x01840020
#define L1PCC    (volatile unsigned int *)0x01840024
#define L1DCFG   (volatile unsigned int *)0x01840040
#define L1DCC    (volatile unsigned int *)0x01840044
#define L2WBAR   (volatile unsigned int *)0x01844000
#define L2WWC    (volatile unsigned int *)0x01844004
#define L2WIBAR  (volatile unsigned int *)0x01844010
#define L2IBAR   (volatile unsigned int *)0x01844018
#define L2WBINV  (volatile unsigned int *)0x01845004
#define L1DWBINV (volatile unsigned int *)0x01845044
#define L1DINV   (volatile unsigned int *)0x01845048
#define L2INV    (volatile unsigned int *)0x01845008
#define L1DWb    (volatile unsigned int *)0x01845040
#define L2Wb     (volatile unsigned int *)0x01845000

#define L1DWWC   (volatile unsigned int *)0x0184404C

#define MAXWC    0xFF00      /* Max word count per cache operations */

/*
 *  ======== Cache_inv ========
 *  Invalidate the range of memory within the specified starting address and
 *  byte count.  The range of addresses operated on gets quantized to whole
 *  cache lines in each cache.  All cache lines in range are invalidated in L1P
 *  cache.  All cache lines in range are invalidated in L1D cache.
 *  All cache lines in range are invaliated in L2 cache.
 */
Void Cache_inv(uint8_t* blockPtr, unsigned int byteCnt, bool wait);

/*
 *  ======== Cache_wb ========
 *  Writes back the range of memory within the specified starting address
 *  and byte count.  The range of addresses operated on gets quantized to
 *  whole cache lines in each cache.  There is no effect on L1P cache.
 *  All cache lines within the range are left valid in L1D cache and the data
 *  within the range in L1D cache will be written back to L2 or external.
 *  All cache lines within the range are left valid in L2 cache and the data
 *  within the range in L2 cache will be written back to external.
 */
Void Cache_wb(uint8_t* blockPtr, unsigned int byteCnt, bool wait);

/*
 *  ======== Cache_wbInv ========
 *  Writes back and invalidates the range of memory within the specified
 *  starting address and byte count.  The range of addresses operated on gets
 *  quantized to whole cache lines in each cache.  All cache lines within range
 *  are invalidated in L1P cache.  All cache lines within the range are
 *  written back to L2 or external and then invalidated in L1D cache
 *  All cache lines within the range are written back to external and then
 *  invalidated in L2 cache.
 */
Void Cache_wbInv(uint8_t* blockPtr, unsigned int byteCnt, bool wait);

/* Writeback Invalidate Cache */
void Cache_WbInvAll();

/* Invalidate Cache */
void Cache_InvAll();

/* Writeback Cache */
void Cache_WbAll();

#endif
#endif /* CACHE_H_ */
