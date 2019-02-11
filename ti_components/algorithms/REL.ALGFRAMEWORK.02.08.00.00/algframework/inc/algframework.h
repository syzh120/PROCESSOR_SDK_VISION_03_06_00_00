/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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


/**
 *  @file       algframework.h
 *
 *  @brief      This header defines types & constants shared by all implementations
 *              of the "generic" algorithm interface.
 */

#ifndef ALGFRAMEWORK_H
#define ALGFRAMEWORK_H

#pragma CHECK_MISRA ("none")
#include "starterware.h"
#pragma RESET_MISRA ("required")
#include "bam.h"
#include "ibamalgtypes.h"

/* included in order to use the default provided ext mem allocatoer in libeveextmem.eve.lib*/
/* The test can choose to define and use different malloc functions as shown in alg_osal_memory.c */
#ifdef CORE_DSP
#define VCOP_SIMD_WIDTH 8 
#endif

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/*Function-like macro definition */
/* Deviation allowed since it is a single statement best implemented through a macro function */
#define ALIGN_SIMD(a)   (((a) + (uint32_t)VCOP_SIMD_WIDTH-1U) & ~((uint32_t)VCOP_SIMD_WIDTH-1U)) /**< macro to help align any value to the next multiple of VCOP_SIMD_WIDTH */
#define ALIGN_2SIMD(a)   (((a) + 2U*(uint32_t)VCOP_SIMD_WIDTH-1U) & ~(2U*(uint32_t)VCOP_SIMD_WIDTH-1U)) /**< macro to help align any value to the next multiple of 2*VCOP_SIMD_WIDTH */
/* RESET_MISRA("19.7")  -> Reset rule 19.7*/

typedef enum IBAMALG_mem_heap_enum_id
{
    IBAMALG_NONE    = (VCOP_NONE),
    IBAMALG_IBUFLA  = (VCOP_IBUFLA),
    IBAMALG_IBUFHA  = (VCOP_IBUFHA),
    IBAMALG_IBUFLB  = (VCOP_IBUFLB),
    IBAMALG_IBUFHB  = (VCOP_IBUFHB),
    IBAMALG_WMEM    = (VCOP_WMEM),

    IBAMALG_ANY_VCOPBUF            =( VCOP_WMEM+1),
    IBAMALG_MEMHEAP_DMEM           = (VCOP_WMEM+2),
    IBAMALG_MEMHEAP_EXTMEM         = (VCOP_WMEM+3),

    IBAMALG_MEMHEAP_INTMEM_NUM     = (IBAMALG_MEMHEAP_DMEM+1),
    IBAMALG_MEMHEAP_NUM            = (IBAMALG_MEMHEAP_EXTMEM+1)

}IBAMALG_MemHeapId;

#endif
