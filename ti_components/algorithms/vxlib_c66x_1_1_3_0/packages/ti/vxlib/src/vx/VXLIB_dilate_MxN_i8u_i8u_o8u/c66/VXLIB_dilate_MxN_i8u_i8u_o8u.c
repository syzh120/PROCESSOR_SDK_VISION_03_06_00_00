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

#include "VXLIB_dilate_MxN_i8u_i8u_o8u.h"

CODE_SECTION(VXLIB_dilate_MxN_i8u_i8u_o8u,              ".text:optimized")
CODE_SECTION(VXLIB_dilate_MxN_i8u_i8u_o8u_core,         ".text:optimized")
CODE_SECTION(VXLIB_dilate_MxN_i8u_i8u_o8u_checkParams,  ".text:optimized")

static void VXLIB_dilate_MxN_i8u_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    const uint8_t mask[restrict],
                                    const int64_t mask8[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth,
                                    int32_t maskWidth,
                                    int32_t maskHeight);

static void VXLIB_dilate_MxN_i8u_i8u_o8u_core(const uint8_t src[restrict],
                                    uint8_t dst[restrict],
                                    const uint8_t mask[restrict],
                                    const int64_t mask8[restrict],
                                    int32_t srcStride,
                                    int32_t outWidth,
                                    int32_t maskWidth,
                                    int32_t maskHeight)
{
    int32_t x, j, i;
    int32_t offsetImage;

    /* Case 1: SIMD of 16 pixels at a time */
    /* 3/16*maskWidth*maskHeight cycles per output pixel (3x3 = 1.6875; 5x5 = 4.6875) */
    for(x=0; x < (outWidth/16); x++) {

        /* Initialize min values to 0, and offset of source image */
        int64_t max8_0 = 0;
        int64_t max8_1 = 0;
        offsetImage = x*16;
        j = 0;

        /* Collapse 2D processing into a single loop to reduce cycles due to
         * pipe-up and pipe-down since the loop will be so small */
        #pragma MUST_ITERATE(2, 81, );
        for(i=0; i < (maskWidth*maskHeight); i++) {

            /* Fetch 16 input pixels for each mask value */
            int64_t src8_0 = _mem8(&src[offsetImage+j]);
            int64_t src8_1 = _mem8(&src[offsetImage+j+8]);

            /* Mask values are 0xFF if TRUE, 0x00 if FALSE, so AND with src */
            uint64_t src8_0_mask = (uint64_t)src8_0 & (uint64_t)mask8[i];
            uint64_t src8_1_mask = (uint64_t)src8_1 & (uint64_t)mask8[i]; 

            /* Find min of result of mask operation */
            max8_0 = _dmaxu4(max8_0, (int64_t)src8_0_mask);
            max8_1 = _dmaxu4(max8_1, (int64_t)src8_1_mask);

            /* The remaining code is done to manage the update of src image pointer when
             * we have reached the end of processing each row of the mask */
            j++;

            if(j == maskWidth) {
                j = 0;
                offsetImage += srcStride;
            }
        }

        /* Write out the results of the max of the full structuring element patch */
        _mem8(&dst[x*16]) = max8_0;
        _mem8(&dst[(x*16)+8]) = max8_1;
    }

/* Setting macro to 1 for now ... priority is for reads to not read past input buffer vs code size.
 * Perhaps this will change in future depending on usage */
#if (!defined(VXLIB_ALIGNED16_WIDTHS) && !defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_ALIGNED16_WIDTHS))
    /* Case 2: Process remaining pixels beyond multiple of 16 */
    /* 3*maskWidth*maskHeight cycles per output pixel (3x3 = 27; 5x5 = 75) cycle per pixel */
    for(x*=16; x < outWidth; x++) {

        /* Initialize max values to 0, and offset of source image */
        uint32_t max = 0;
        offsetImage = x;
        j = 0;

        /* Collapse 2D processing into a single loop to reduce cycles due to
         * pipe-up and pipe-down since the loop will be so small */
        #pragma MUST_ITERATE(2, 81, );
        for(i=0; i < (maskWidth*maskHeight); i++) {

            /* Mask values are 0xFF if TRUE, 0x00 if FALSE, so OR the inverse of mask with src,
             * and find max of result */
            uint32_t src_mask = (uint32_t)src[offsetImage+j] & (uint32_t)mask[i]; 
            max = _maxu4(src_mask, max);

            /* The remaining code is done to manage the update of image pointers when
             * we have reached the end of processing each row of the mask */
            j++;

            if(j == maskWidth) {
                j = 0;
                offsetImage += srcStride;
            }
        }

        /* Write out the results of the max of the full structuring element patch */
        dst[x] = (uint8_t)max;
    }
#endif
}

VXLIB_STATUS VXLIB_dilate_MxN_i8u_i8u_o8u(const uint8_t src[restrict],
                            const VXLIB_bufParams2D_t *src_addr,
                            uint8_t dst[restrict],
                            const VXLIB_bufParams2D_t *dst_addr,
                            const uint8_t mask[restrict],
                            const VXLIB_bufParams2D_t *mask_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_CHECK_PARAMS)
    status = VXLIB_dilate_MxN_i8u_i8u_o8u_checkParams(src, src_addr, dst, dst_addr, mask, mask_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        int32_t i;
        int64_t mask8[9*9];

        /* 2 cycles per mask value */
        for(i=0; i<(mask_addr->dim_x*mask_addr->dim_y); i++)
        {
            /* Pack the mask values into 32 bits */
            uint32_t temp = ( (uint32_t)mask[i] << 24) |
                             ( (uint32_t)mask[i] << 16) |
                             ( (uint32_t)mask[i] << 8) |
                             ( (uint32_t)mask[i] << 0);

            /* NOT the result, and pack into 64 bits */
            mask8[i] = _itoll(temp, temp);
        }

#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        if((src_addr->dim_x == src_addr->stride_y) &&
           (dst_addr->dim_x == dst_addr->stride_y) &&
           (dst_addr->dim_x == src_addr->dim_x))
#endif
        {
            VXLIB_dilate_MxN_i8u_i8u_o8u_core(src, dst, mask, mask8, src_addr->stride_y, (dst_addr->stride_y * dst_addr->dim_y) - (mask_addr->dim_x-1),
                                            mask_addr->dim_x, mask_addr->dim_y);
        }
#if !defined(VXLIB_EQUAL_WIDTH_STRIDE) && !defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
        else {

            int32_t    y;
            int32_t    width = VXLIB_min(dst_addr->dim_x, (src_addr->dim_x-(mask_addr->dim_x-1)));

            for( y=0; y < dst_addr->dim_y; y++ ) {

                const uint8_t  *src_t = (const uint8_t *)&src[ y * src_addr->stride_y];
                uint8_t         *dst_t  = (uint8_t *)&dst[ y * dst_addr->stride_y];

                VXLIB_dilate_MxN_i8u_i8u_o8u_core(src_t, dst_t, mask, mask8, src_addr->stride_y, width, mask_addr->dim_x, mask_addr->dim_y);

            }
        }
#endif
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_dilate_MxN_i8u_i8u_o8u_checkParams(const uint8_t src[restrict],
                                           const VXLIB_bufParams2D_t *src_addr,
                                           const uint8_t dst[restrict],
                                           const VXLIB_bufParams2D_t *dst_addr,
                                           const uint8_t mask[restrict],
                                           const VXLIB_bufParams2D_t *mask_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src == NULL) || (dst == NULL) || (mask == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_addr->dim_x < dst_addr->dim_x) ||
               ((src_addr->dim_y-(mask_addr->dim_y-1)) !=  dst_addr->dim_y) ||
               (src_addr->stride_y < src_addr->dim_x) ||
               (dst_addr->stride_y < dst_addr->dim_x) ||
               (mask_addr->stride_y != mask_addr->dim_x) ||
               (mask_addr->dim_x < 1) ||
               (mask_addr->dim_y < 1) ||
               (mask_addr->dim_x > 9) ||
               (mask_addr->dim_y > 9)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_addr->data_type != VXLIB_UINT8) ||
               (dst_addr->data_type != VXLIB_UINT8) ||
               (mask_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
#if defined(VXLIB_EQUAL_WIDTH_STRIDE) || defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_EQUAL_WIDTH_STRIDE)
    else if((src_addr->dim_x != src_addr->stride_y) ||
             (dst_addr->dim_x != dst_addr->stride_y) ||
             (src_addr->dim_x != dst_addr->dim_x)) {
        status = VXLIB_ERR_NOT_EQUAL_WIDTH_STRIDE;
    }
#endif
#if (defined(VXLIB_ALIGNED16_WIDTHS) || defined(VXLIB_DILATE_MXN_I8U_I8U_O8U_ALIGNED16_WIDTHS))
    else if((dst_addr->dim_x % 16U) != 0) {
        status = VXLIB_ERR_NOT_ALIGNED_WIDTHS;
    }
#endif
    else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

#endif
