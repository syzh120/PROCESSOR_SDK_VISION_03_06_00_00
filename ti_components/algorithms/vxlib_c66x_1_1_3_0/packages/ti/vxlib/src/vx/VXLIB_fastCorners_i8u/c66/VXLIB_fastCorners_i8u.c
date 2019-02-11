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

#include "VXLIB_fastCorners_i8u.h"
#include "../../VXLIB_fastCornersDetect_i8u/c66/VXLIB_fastCornersDetect_i8u.h"
#include "../../VXLIB_fastCornersScore_i8u/c66/VXLIB_fastCornersScore_i8u.h"
#include "../../VXLIB_fastCornersNMS_i8u/c66/VXLIB_fastCornersNMS_i8u.h"

CODE_SECTION(VXLIB_fastCorners_i8u,              ".text:optimized")
CODE_SECTION(VXLIB_fastCorners_i8u_checkParams,  ".text:optimized")

VXLIB_STATUS VXLIB_fastCorners_i8u(const uint8_t src[],
                                const VXLIB_bufParams2D_t *src_addr,
                                uint32_t corners[],
                                uint8_t strengths[],
                                uint32_t corners_capacity,
                                uint8_t strength_thresh,
                                uint32_t *num_corners,
                                uint8_t do_nonmax,
                                uint8_t scratch[],
                                uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_FASTCORNERS_I8U_CHECK_PARAMS)
    status = VXLIB_fastCorners_i8u_checkParams(src, src_addr, corners, strengths, corners_capacity, strength_thresh,
                                            num_corners, do_nonmax, scratch, scratch_size);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t   nCorners;

        if( scratch_size >= 64U ) {

            status = VXLIB_fastCornersDetect_i8u(src, src_addr, corners, corners_capacity, strength_thresh, num_corners, scratch, scratch_size);

            if( (status == VXLIB_SUCCESS) && (strengths != NULL) ) {

                if( scratch_size >= 463U ) {

                    nCorners = VXLIB_min(corners_capacity, *num_corners);

                    status = VXLIB_fastCornersScore_i8u(src, src_addr, corners, strengths, strength_thresh, nCorners, scratch, scratch_size);

                    if( (status == VXLIB_SUCCESS) && (do_nonmax == (uint8_t)1) ) {

                        int32_t i;
                        uint32_t scratch_size_calc = (src_addr->dim_x * 4U) + nCorners + 30U;

                        if( scratch_size >= scratch_size_calc ) {

                            /* Clear scratch memory */
                            /* 1/16 cycles per byte */
                            #pragma MUST_ITERATE(0,,2)
                            for( i=0; i < (((int32_t)scratch_size_calc/16)*2); i++ ) {
                                _amem8(&scratch[i*8]) = 0;
                            }

                            status = VXLIB_fastCornersNMS_i8u(src_addr, corners, strengths, nCorners, corners, strengths, &nCorners, (uint8_t*)scratch, scratch_size);
                        } else {
                            status = VXLIB_ERR_BUFFER_TOO_SMALL;
                        }
                        *num_corners = nCorners;
                    }
                } else {
                    status = VXLIB_ERR_BUFFER_TOO_SMALL;
                }
            }
        } else {
            status = VXLIB_ERR_BUFFER_TOO_SMALL;
        }
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_FASTCORNERS_I8U_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_FASTCORNERS_I8U_CHECK_PARAMS))

VXLIB_STATUS VXLIB_fastCorners_i8u_checkParams(const uint8_t src[],
                                            const VXLIB_bufParams2D_t * src_addr,
                                            const uint32_t corners[],
                                            const uint8_t strengths[],
                                            uint32_t corners_capacity,
                                            uint8_t strength_thresh,
                                            const uint32_t *num_corners,
                                            uint8_t do_nonmax,
                                            const uint8_t scratch[],
                                            uint32_t scratch_size)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    status = VXLIB_fastCornersDetect_i8u_checkParams(src, src_addr, corners, corners_capacity, strength_thresh, num_corners, scratch, scratch_size);

    if( (status == VXLIB_SUCCESS) && (strengths != NULL) ) {
        status = VXLIB_fastCornersScore_i8u_checkParams(src, src_addr, corners, strengths, strength_thresh, corners_capacity, scratch, scratch_size);
    }

    if( (status == VXLIB_SUCCESS) && (do_nonmax == (uint8_t)1) ) {
        status = VXLIB_fastCornersNMS_i8u_checkParams(src_addr, corners, strengths, corners_capacity, corners, strengths, &corners_capacity, scratch, scratch_size);
    }

    if( status == VXLIB_SUCCESS ) {
        if (src_addr->data_type != VXLIB_UINT8) {
            status = VXLIB_ERR_INVALID_TYPE;
        } else if( do_nonmax > 1U) {
            status = VXLIB_ERR_INVALID_VALUE;
        } 
        else {
            status = VXLIB_SUCCESS;
        }
    }

    return (status);
}
#endif
