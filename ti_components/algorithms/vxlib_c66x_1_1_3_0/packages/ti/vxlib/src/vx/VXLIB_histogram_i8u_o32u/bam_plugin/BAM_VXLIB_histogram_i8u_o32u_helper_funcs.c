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
**|        Copyright (c) 2017 Texas Instruments Incorporated                 |**
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

#include "BAM_VXLIB_histogram_i8u_o32u_int.h"

static BAM_Status BAM_VXLIB_histogram_i8u_o32u_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_VXLIB_histogram_i8u_o32u_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)
{
    internalBlock[BAM_VXLIB_HISTOGRAM_I8U_O32U_INTERNAL_SCRATCH].size = 1024U * sizeof(uint32_t);
    internalBlock[BAM_VXLIB_HISTOGRAM_I8U_O32U_INTERNAL_SCRATCH].alignment = 8;
    internalBlock[BAM_VXLIB_HISTOGRAM_I8U_O32U_INTERNAL_SCRATCH].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[BAM_VXLIB_HISTOGRAM_I8U_O32U_INTERNAL_SCRATCH].space = BAM_MEMSPACE_SCRATCH_OR_CONST;

    return BAM_S_SUCCESS;
}

void BAM_VXLIB_histogram_i8u_o32u_getKernelInfo(BAM_VXLIB_histogram_i8u_o32u_params *kernelArgs,
                                                     BAM_KernelInfo *kernelInfo)
{
    /* This function either copies the entire structure, if all values are constant, or it can additionally
     * update some parameters based on the kernelArgs configuration */
    memcpy(kernelInfo, &gBAM_VXLIB_histogram_i8u_o32u_kernel, sizeof(BAM_KernelInfo));

    return;
}

BAM_KernelInfo gBAM_VXLIB_histogram_i8u_o32u_kernel =
{
    0,                                   /* kernelId */
    sizeof(BAM_VXLIB_histogram_i8u_o32u_Context),
    sizeof(BAM_VXLIB_histogram_i8u_o32u_Args),
    BAM_DSP_C66x,                        /* coreType */
    BAM_NODE_COMPUTE_FRAME_STATS_OP,     /* nodeType */
    BAM_VXLIB_HISTOGRAM_I8U_O32U_NUM_INPUT_BLOCKS,
    BAM_VXLIB_HISTOGRAM_I8U_O32U_NUM_OUTPUT_BLOCKS,
    BAM_VXLIB_HISTOGRAM_I8U_O32U_INTERNAL_NUM_BLOCK,
    {
        BAM_METAINFO_FRAME_STATS_OP(256 * sizeof(uint32_t)), /* metaInfo */
        BAM_CONSTRAINT_REQUIRES_ONLY_VALID_DATA(1), /* constraintInfo */
        BAM_OPTIMIZATION_EQUAL_INOUT_WIDTHS_STRIDES(1), /* optimizationInfo */
        BAM_BLOCK_ACCESS_PATTERN_ANY, /* sourceBlockAccessPattern */
        BAM_BLOCK_ACCESS_PATTERN_ANY, /* sinkBlockAccessPattern */
        {1.0f}, /* horzSamplingFactor */
        {1.0f}, /* vertSamplingFactor */
        { VXLIB_UINT8 }, /* typeInputElmt */
        {0}, /* typeOutputElmt */
    }
};

BAM_KernelHelperFuncDef gBAM_VXLIB_histogram_i8u_o32u_helperFunc =
{
    &BAM_VXLIB_histogram_i8u_o32u_getMemRecFunc,
    NULL,
    NULL
};
