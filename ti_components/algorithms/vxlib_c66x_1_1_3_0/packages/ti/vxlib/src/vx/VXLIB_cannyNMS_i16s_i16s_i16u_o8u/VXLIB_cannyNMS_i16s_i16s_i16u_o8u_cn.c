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

#include "VXLIB_cannyNMS_i16s_i16s_i16u_o8u_cn.h"

#define BITS 15
#define TAN22 0.4142135623730950488016887242097

CODE_SECTION(VXLIB_cannyNMS_i16s_i16s_i16u_o8u_cn,              ".text:ansi")
CODE_SECTION(VXLIB_cannyNMS_i16s_i16s_i16u_o8u_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_cannyNMS_i16s_i16s_i16u_o8u_cn(int16_t src_x[],
                                                  VXLIB_bufParams2D_t * src_x_addr,
                                                  int16_t src_y[],
                                                  VXLIB_bufParams2D_t * src_y_addr,
                                                  uint16_t src_mag[],
                                                  VXLIB_bufParams2D_t * src_mag_addr,
                                                  uint8_t dst[],
                                                  VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_cannyNMS_i16s_i16s_i16u_o8u_checkParams_cn(src_x, src_x_addr, src_y, src_y_addr, src_mag, src_mag_addr, dst, dst_addr);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t        x, y;

        /* Constant values for tan(22.5 degrees) and tan(67.5 degrees) as
         * the border between the octants */
        const uint32_t tan22 = (uint32_t)(TAN22*(1<<BITS) + 0.5);
        uint32_t tan67 = (uint32_t)(tan22+(1<<(BITS+1)));

        int32_t outWidth = VXLIB_min(dst_addr->dim_x, src_mag_addr->dim_x-2);
        int32_t outHeight = VXLIB_min(dst_addr->dim_y, src_mag_addr->dim_y-2);

        for(y=0; y < outHeight; y++) {
            for(x=0; x < outWidth; x++) {

                uint8_t edge;

                /* Fetch two X and Y gradient pixels from center row */
                int32_t X = src_x[(y+1)*(src_x_addr->stride_y/2)+(x+1)];
                int32_t Y = src_y[(y+1)*(src_y_addr->stride_y/2)+(x+1)];

                /* Fetch the center magnitude to compare against
                 * its neighors */
                int32_t mag = src_mag[(y+1)*(src_mag_addr->stride_y/2)+(x+1)];

                /* Determine the octant of the gradient direction
                 * - Take the absolute value of the gradients so we consider
                 *   only three regions within the positive quadrant.
                 * - These three regions are defined to determine if the
                 *   direction of the quadrant is:
                 *   1. horizontal (to compare against neighbor pixels to the
                 *       left and right of center pixel), defined by
                 *       tan(22.5 degrees)
                 *   2. vertical (to compare against the neighbor pixels to the
                 *       top and bottom of the center pixel), defined by
                 *       tan(67.5 degrees)
                 *   3. diagonal (to compare against the neighbor pixels in the
                 *       respective corners), defined by the else condition of
                 *       1 & 2 above.
                 *
                 *   +-----------(+)
                 *   |\``--__       Y-gradient < tan(22.5 degress) = horizontal
                 *   | \     ```--
                 *   |  \  tan(22.5 degress) <= Y-gradient <= tan(67.5 degress) = diagonal
                 *  (+)
                 *      Y-gradient < tan(67.5 degress) = vertical
                 */

                uint32_t absX = abs(X);
                uint32_t absY = abs(Y);

                /* The c model logic was modified to match the MPYLIR/MPYHIR optimized version here
                 * so that compares can be done on 16-bit values instead of 32-bit values (better SIMD).
                 * This loses some precision here affecting rounding on the borders of the octants */
                uint32_t tan22X = (tan22*absX+(1<<(BITS-1)))>>BITS;

                /* If octant is touching X axis (gradient is horizontal)
                 * Compare against neighbor pixels on horizontal axis */
                if(tan22X > absY) {
                    edge = (mag > src_mag[(y+1)*(src_mag_addr->stride_y/2)+x] && mag >= src_mag[(y+1)*(src_mag_addr->stride_y/2)+x+2]) ? 127 : 0;
                } else {
                    /* The c model logic was modified to match the MPYLIR/MPYHIR optimized version here
                     * so that compares can be done on 16-bit values instead of 32-bit values (better SIMD).
                     * This loses some precision here affecting rounding on the borders of the octants */
                    uint32_t tan67X = (tan67*absX+(1<<(BITS-1)))>>BITS;

                    /* If octant is touching Y axis (gradient is vertical) 
                     * Compare against  neighbor pixels on vertical axis */
                    if(tan67X < absY) {
                        edge = (mag > src_mag[y*(src_mag_addr->stride_y/2)+(x+1)] && mag >= src_mag[(y+2)*(src_mag_addr->stride_y/2)+(x+1)]) ? 127 : 0;

                    /* If octant is half way between X and Y axis (gradient is diagonal)
                     * Compare against neighbor pixels on respective diagonal axis */
                    } else {
                        /* Determine the slope of the diagonal graident to know which two pixels to compare against */
                        /* - The sobel gradients used have positive gradients
                         *   in the direction of increasing column number (horizontally)
                         *   and increasing row number (vertically).
                         * - Therefore, a positive slope is along the diagonals in Q0
                         *   and Q3, whereas a negative slope is along the diagonal in
                         *   Q1 and Q2
                         *
                         *   Q0         (-)          Q1
                         *       +       |       -
                         *          +    |    -
                         *             + | -
                         *  (-)----------+-----------(+)
                         *             - | +
                         *          -    |    +
                         *       -       |       +
                         *   Q2         (+)          Q3
                         *
                         */
                        int32_t slope = (X ^ Y) < 0 ? -1 : 1;
                        edge = (mag > src_mag[y*(src_mag_addr->stride_y/2)+(x+1)-slope] && mag > src_mag[(y+2)*(src_mag_addr->stride_y/2)+(x+1)+slope]) ? 127 : 0;
                    }
                }
                dst[y*(dst_addr->stride_y)+x] = edge;
            }
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_cannyNMS_i16s_i16s_i16u_o8u_checkParams_cn(int16_t src_x[],
                                                              VXLIB_bufParams2D_t * src_x_addr,
                                                              int16_t src_y[],
                                                              VXLIB_bufParams2D_t * src_y_addr,
                                                              uint16_t src_mag[],
                                                              VXLIB_bufParams2D_t * src_mag_addr,
                                                              uint8_t dst[],
                                                              VXLIB_bufParams2D_t * dst_addr)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

    if((src_x == NULL) || (src_y == NULL) || (src_mag == NULL) || (dst == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((src_x_addr->dim_x != src_y_addr->dim_x) ||
               (src_x_addr->dim_x != src_mag_addr->dim_x) ||
               (src_x_addr->dim_x < dst_addr->dim_x) ||
               (src_x_addr->dim_y != src_y_addr->dim_y) ||
               (src_x_addr->dim_y != src_mag_addr->dim_y) ||
               (src_x_addr->dim_y-2 != dst_addr->dim_y) ||
               ((uint32_t)src_x_addr->stride_y < src_x_addr->dim_x*2) ||
               ((uint32_t)src_y_addr->stride_y < src_y_addr->dim_x*2) ||
               ((uint32_t)src_mag_addr->stride_y < src_mag_addr->dim_x*2) ||
               ((uint32_t)dst_addr->stride_y < dst_addr->dim_x)) {
        status = VXLIB_ERR_INVALID_DIMENSION;
    } else if((src_x_addr->data_type != VXLIB_INT16) ||
               (src_y_addr->data_type != VXLIB_INT16) ||
               (src_mag_addr->data_type != VXLIB_UINT16) ||
               (dst_addr->data_type != VXLIB_UINT8)) {
        status = VXLIB_ERR_INVALID_TYPE;
    }
    return (status);
}

