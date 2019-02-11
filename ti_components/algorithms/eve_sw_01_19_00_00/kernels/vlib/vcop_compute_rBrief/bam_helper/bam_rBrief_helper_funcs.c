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


/**
 *  @file       bam_rBrief_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating rBrief into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "algframework.h"
#include "bam_rBrief_int.h"
#include "vcop_compute_rBrief_kernel.h"

const int8_t BAM_RBRIEF_TI_MOMENTS_COL_MASK[MOMENTS_PATCH_SIZE*MOMENTS_PATCH_SIZE] =
 {     0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,-3,-2,-1, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,  0,  0,  0,  0, 0,
       0,  0,  0,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,  0,  0,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,  0,  0,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,  0,  0,  0, 0,
       0,  0,  0,  0,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,-3,-2,-1, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0
 };


 const int8_t BAM_RBRIEF_TI_MOMENTS_ROW_MASK[MOMENTS_PATCH_SIZE*MOMENTS_PATCH_SIZE] =
 {     0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,-15,-15,-15,-15,-15,-15,-15,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10, 0, 0, 0, 0, 0,
       0, 0, 0,-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,-9, 0, 0, 0, 0,
       0, 0,-8,-8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,-8,-8, 0, 0, 0,
       0, 0,-7,-7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,-7,-7, 0, 0, 0,
       0,-6,-6,-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,-6,-6,-6, 0, 0,
       0,-5,-5,-5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,-5,-5,-5, 0, 0,
       0,-4,-4,-4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4,-4,-4,-4, 0, 0,
      -3,-3,-3,-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,-3,-3,-3,-3, 0,
      -2,-2,-2,-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,-2,-2,-2,-2, 0,
      -1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1,-1,-1, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 1, 1, 1, 0,
       2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2, 2, 0,
       3, 3, 3, 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 3, 3, 3, 3, 0,
       0, 4, 4, 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 4, 4, 4, 0, 0,
       0, 5, 5, 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 5, 5, 5, 0, 0,
       0, 6, 6, 6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 0, 0,
       0, 0, 7, 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 7, 7, 0, 0, 0,
       0, 0, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 0, 0, 0,
       0, 0, 0, 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 9, 0, 0, 0, 0,
       0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15, 15, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0
 };

 const int16_t  BAM_RBRIEF_TI_SINQ14_2[33]  = {0,
     0   ,  3406,  6663,  9630, 12175, 14188, 15582, 16294,
     3406,  6663,  9630, 12175, 14188, 15582, 16294, 16294,
     0   , -3407, -6664, -9631,-12176,-14189,-15583,-16295,
     -3407, -6664, -9631,-12176,-14189,-15583,-16295,-16295
 };

 const int16_t  BAM_RBRIEF_TI_COSQ14_2[33]  = {0,
     16384, 16025, 14967, 13254, 10963,  8192,  5062,  1712,
     -16025,-14967,-13254,-10963, -8192, -5062, -1712,  1712,
     -16384,-16025,-14967,-13254,-10963, -8192, -5062, -1712,
     16025, 14967, 13254, 10963,  8192,  5062,  1712, -1712
 };

 const uint16_t BAM_RBRIEF_TI_ARCTAN_XTHR[8] = {0, 54U, 114U,186U,284U,443U,788U,2436U};

 const uint16_t  BAM_RBRIEF_TI_TRAN_OFFSET[8] = {0,1U*BYTE_OFFSET,2U*BYTE_OFFSET,3U*BYTE_OFFSET,
                                         4U*BYTE_OFFSET,5U*BYTE_OFFSET,6U*BYTE_OFFSET,7U*BYTE_OFFSET};

/* Function Prototypes */
static BAM_Status BAM_rBrief_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_rBrief_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if (!VCOP_HOST_EMULATION)
    internalBlock[RBRIEF_INTERNAL_PARAMS_IDX].size = 2U*vcop_compute_rBrief_param_count();
#else
    internalBlock[RBRIEF_INTERNAL_PARAMS_IDX].size = 16U;
#endif

    /* Set attribute for all the tables as const as we dont want them to be restored during BAM activate call */
    internalBlock[RBRIEF_INTERNAL_WBUF_TABLES_IDX].size            = sizeof(RBRIEF_INTERNAL_MEMORY_WBUF_tables);
    internalBlock[RBRIEF_INTERNAL_WBUF_TABLES_IDX].attrs.memAttrs  = BAM_MEMATTRS_CONST;
    internalBlock[RBRIEF_INTERNAL_WBUF_TABLES_IDX].space           = BAM_MEMSPACE_WBUF;
    internalBlock[RBRIEF_INTERNAL_WBUF_TABLES_IDX].alignment       = 32U;

    internalBlock[RBRIEF_INTERNAL_IBUFLA_TABLES_IDX].size            = sizeof(RBRIEF_INTERNAL_MEMORY_IBUFLA_tables);
    internalBlock[RBRIEF_INTERNAL_IBUFLA_TABLES_IDX].attrs.memAttrs  = BAM_MEMATTRS_CONST;
    internalBlock[RBRIEF_INTERNAL_IBUFLA_TABLES_IDX].space           = BAM_MEMSPACE_IBUFLA;
    internalBlock[RBRIEF_INTERNAL_IBUFLA_TABLES_IDX].alignment       = 32U;

    internalBlock[RBRIEF_INTERNAL_IBUFHA_TABLES_IDX].size            = sizeof(RBRIEF_INTERNAL_MEMORY_IBUFHA_tables);
    internalBlock[RBRIEF_INTERNAL_IBUFHA_TABLES_IDX].attrs.memAttrs  = BAM_MEMATTRS_CONST;
    internalBlock[RBRIEF_INTERNAL_IBUFHA_TABLES_IDX].space           = BAM_MEMSPACE_IBUFHA;
    internalBlock[RBRIEF_INTERNAL_IBUFHA_TABLES_IDX].alignment       = 32U;

    /* All other buffer attribute is set to scratch */
    internalBlock[RBRIEF_INTERNAL_WBUF_IDX].size            = sizeof(RBRIEF_INTERNAL_MEMORY_WBUF);
    internalBlock[RBRIEF_INTERNAL_WBUF_IDX].attrs.memAttrs  = BAM_MEMATTRS_SCRATCH;
    internalBlock[RBRIEF_INTERNAL_WBUF_IDX].space           = BAM_MEMSPACE_WBUF;
    internalBlock[RBRIEF_INTERNAL_WBUF_IDX].alignment       = 32U;

    internalBlock[RBRIEF_INTERNAL_IBUFLA_IDX].size            = sizeof(RBRIEF_INTERNAL_MEMORY_IBUFLA);
    internalBlock[RBRIEF_INTERNAL_IBUFLA_IDX].attrs.memAttrs  = BAM_MEMATTRS_SCRATCH;
    internalBlock[RBRIEF_INTERNAL_IBUFLA_IDX].space           = BAM_MEMSPACE_IBUFLA;
    internalBlock[RBRIEF_INTERNAL_IBUFLA_IDX].alignment       = 32U;

    internalBlock[RBRIEF_INTERNAL_IBUFHA_IDX].size            = sizeof(RBRIEF_INTERNAL_MEMORY_IBUFHA);
    internalBlock[RBRIEF_INTERNAL_IBUFHA_IDX].attrs.memAttrs  = BAM_MEMATTRS_SCRATCH;
    internalBlock[RBRIEF_INTERNAL_IBUFHA_IDX].space           = BAM_MEMSPACE_IBUFHA;
    internalBlock[RBRIEF_INTERNAL_IBUFHA_IDX].alignment       = 32U;

    /* Output Buffer */
    outBlock[RBRIEF_OUT_BRIEF_DESCRIPTOR_IDX].size            = 32U;
    outBlock[RBRIEF_OUT_BRIEF_DESCRIPTOR_IDX].attrs.memAttrs  = BAM_MEMATTRS_SCRATCH;
    outBlock[RBRIEF_OUT_BRIEF_DESCRIPTOR_IDX].space           = BAM_MEMSPACE_IBUFHA;
    outBlock[RBRIEF_OUT_BRIEF_DESCRIPTOR_IDX].alignment       = 32U;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_rBriefKernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_rBrief_Context),
        sizeof(BAM_rBrief_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_rBriefHelperFunc =
{ &BAM_rBrief_getMemRecFunc, NULL};

