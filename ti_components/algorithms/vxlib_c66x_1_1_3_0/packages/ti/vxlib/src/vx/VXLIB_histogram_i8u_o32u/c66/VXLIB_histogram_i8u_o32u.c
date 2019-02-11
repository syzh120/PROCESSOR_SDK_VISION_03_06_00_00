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
**|         Copyright (c) 2016 - 2017 Texas Instruments Incorporated         |**
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

#include "VXLIB_histogram_i8u_o32u.h"
#include "../../VXLIB_histogramSimple_i8u_o32u/c66/VXLIB_histogramSimple_i8u_o32u.h"

CODE_SECTION(VXLIB_histogram_i8u_o32u,              ".text:optimized")
CODE_SECTION(VXLIB_histogram_i8u_o32u_checkParams,  ".text:optimized")

VXLIB_STATUS VXLIB_histogram_i8u_o32u(const uint8_t src[restrict],
                              const VXLIB_bufParams2D_t *src_addr,
                              uint32_t dist[restrict], 
                              uint32_t scratch[restrict],
                              uint8_t offset,
                              uint16_t range,
                              uint16_t numBins,
                              uint8_t lastBlock)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_HISTOGRAM_I8U_O32U_CHECK_PARAMS)
    status = VXLIB_histogram_i8u_o32u_checkParams(src, src_addr, dist, scratch, offset, range, numBins, lastBlock);
    if( status == VXLIB_SUCCESS )
#endif
    {
        /* This function doesn't need minValue, so setting it to a dummy value */
        uint32_t minValue = 0;

        /* Call the optimized simple histogram function, which gives ~1.25 cycles per input pixel */
        /* Use the top of the scratch buffer to also be the intermediate dist buffer, since it doesn't
         * get written until the lastBlock = 1 anyway */
        status = VXLIB_histogramSimple_i8u_o32u(src, src_addr, scratch, scratch, &minValue, lastBlock);

        /* If calling the function on the lastBlock, then redistribute the histogram according to
         * function parameters (offset/range/numBins) */
        if( lastBlock == 1U ) {

            uint16_t index;
            uint16_t x;
            uint16_t offset_16 = (uint16_t)offset;

            /* 7 cycles per input bin (range bins) */
            /* Max range == 256 (256*7 = 1792 cycles) */
            for(x=offset_16; x < (offset_16 + range); x++) {
                index = ((x - offset_16) * numBins) / range;
                dist[index] += scratch[x];
            }
        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_HISTOGRAM_I8U_O32U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_HISTOGRAM_I8U_O32U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_histogram_i8u_o32u_checkParams(const uint8_t src[],
                                          const VXLIB_bufParams2D_t *src_addr,
                                          const uint32_t dist[restrict],
                                          const uint32_t scratch[restrict],
                                          uint8_t offset,
                                          uint16_t range,
                                          uint16_t numBins,
                                          uint8_t lastBlock)
{
    VXLIB_STATUS    status;

    if( (src == NULL) || (dist == NULL) || (scratch == NULL) ) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if( src_addr->stride_y < src_addr->dim_x ) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if( src_addr->data_type != VXLIB_UINT8 ) {
        status = VXLIB_ERR_INVALID_TYPE;
    } else if( ((uint32_t)offset + (uint32_t)range) > 256U ) {
        status = VXLIB_ERR_INVALID_VALUE;
    } else if( ((uint32_t)numBins > 256U)  || (lastBlock > 1U) ) {
        status = VXLIB_ERR_INVALID_VALUE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_HISTOGRAM_I8U_O32U_EQUAL_WIDTH_STRIDE)
    else if( src_addr->dim_x != src_addr->stride_y ) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if defined(VXLIB_ALIGNED4_PTRS_STRIDES) || defined(VXLIB_HISTOGRAM_I8U_O32U_ALIGNED4_PTRS_STRIDES)
    else if((((uint32_t)src % 4U) != 0) ||
            ((src_addr->stride_y % 4U) != 0)) {
        status = VXLIB_ERR_NOT_ALIGNED_PTRS_STRIDES;
    }
#endif
#if defined(VXLIB_ALIGNED8_WIDTHS) || defined(VXLIB_HISTOGRAM_I8U_O32U_ALIGNED8_WIDTHS)
    else if((src_addr->dim_x % 8U) != 0 ) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif

