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

#include "VXLIB_harrisCornersNMS_i32f_cn.h"
#include <math.h>
#include <string.h>

CODE_SECTION(VXLIB_harrisCornersNMS_i32f_cn,              ".text:ansi")
CODE_SECTION(VXLIB_harrisCornersNMS_i32f_checkParams_cn,  ".text:ansi")

VXLIB_STATUS VXLIB_harrisCornersNMS_i32f_cn(uint32_t corners_in[],
                                        VXLIB_F32 strengths_in[],
                                        uint32_t num_corners_in,
                                        uint32_t corners_out[],
                                        VXLIB_F32 strengths_out[],
                                        uint32_t corners_out_capacity,
                                        uint32_t *num_corners_out,
                                        int8_t scratch[],
                                        uint32_t scratch_size,
                                        VXLIB_F32 min_distance,
                                        uint8_t *iterations)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#ifdef VXLIB_CHECK_PARAMS
    status = VXLIB_harrisCornersNMS_i32f_checkParams_cn(corners_in, strengths_in, num_corners_in, corners_out, strengths_out, corners_out_capacity, num_corners_out,
                                                        scratch, scratch_size, min_distance, iterations);
    if( status == VXLIB_SUCCESS )
#endif
    {
        uint32_t i, outNum;
        int32_t j;
        int32_t x1, y1;
        VXLIB_F32 dx, dy, distance;
        uint32_t   neighborhood_size = ((min_distance+1.0f)*2)*((min_distance+1.0f)*2)/9;
        uint16_t *neighbor_index = (uint16_t*)scratch;
        int8_t   *valid = (int8_t*)(scratch + 2*VXLIB_min(neighborhood_size, num_corners_in));
        int32_t z, iters;
        int32_t marked = 0;

        /* Allow user to set maximum iterations, otherwise set to some high number */
        if(iterations == NULL || *iterations == 0) {
            iters = 30;
        } else {
            iters = (int32_t)*iterations;
        }

        /* Clear valid list to zeros */
        memset(valid, 0, num_corners_in);

        /* Number of iterations limited by the user */
        for( z = 0; z < iters; z++) {

            /* For each input corner */
            for( i = 0; i < num_corners_in; i++ ) {

                /* Only look at the ones which have not yet been chosen or rejected yet */
                if(valid[i] == 0) {
                    int32_t x = corners_in[i] & 0xFFFF;
                    int32_t y = corners_in[i] >> 16;
                    uint32_t found = 0;
                    uint32_t neighbor_cnt = 0;

                    /* Search backward through list until we are beyond the min_distance, vertically */
                    for ( j = i-1; j >= 0; j-- ) {

                        /* Skip the suppressed pixels */
                        if (valid[j] == -1) {
                            continue;
                        }

                        x1 = corners_in[j] & 0xFFFF;
                        y1 = corners_in[j] >> 16;

                        dx = (VXLIB_F32)(x1 - x);
                        dy = (VXLIB_F32)(y1 - y);

                        /* Exit early if we are beyond the min_distance, vertically */
                        if( fabsf(dy) > min_distance ) {
                            break;
                        }

                        distance = sqrtf((dx*dx) + (dy*dy));

                        /* If feature is within radius */
                        if( distance < min_distance ) {

                            /* If feature is stronger, then exit, not a strong feature */
                            if ( strengths_in[j] > strengths_in[i] ) {
                                found = 1;
                                break;
                            } else {
                                /* If feature is weaker, then add to neighbor list for possible suppression */
                                neighbor_index[neighbor_cnt] = j;
                                neighbor_cnt++;
                            }
                        }
                    }
                    if(found == 0) {
                        /* Search forward through list until we are beyond the min_distance, vertically */
                        for ( j = i+1; j < num_corners_in; j++ ) {

                            /* Skip the suppressed pixels */
                            if (valid[j] == -1) {
                                continue;
                            }
                            x1 = corners_in[j] & 0xFFFF;
                            y1 = corners_in[j] >> 16;

                            dx = (VXLIB_F32)(x1 - x);
                            dy = (VXLIB_F32)(y1 - y);

                            /* Exit early if we are beyond the min_distance, vertically */
                            if( fabsf(dy) > min_distance ) {
                                break;
                            }

                            distance = sqrtf((dx*dx) + (dy*dy));

                            /* If feature is within radius */
                            if( distance < min_distance ) {

                                /* If feature is stronger, then exit, not a strong feature */
                                if ( strengths_in[j] >= strengths_in[i] ) {
                                    found = 1;
                                    break;
                                } else {
                                    /* If feature is weaker, then add to neighbor list for possible suppression */
                                    neighbor_index[neighbor_cnt] = j;
                                    neighbor_cnt++;
                                }
                            }
                        }
                    }

                    /* If no neighbors were found to be stronger, mark as valid feature and suppress neighbors */
                    if(found == 0) {
                        valid[i] = 1;
                        marked++;

                        for ( j = 0; j < neighbor_cnt; j++ ) {
                            valid[neighbor_index[j]] = -1;
                            marked++;
                        }
                    }
                }
            }
            if(marked == num_corners_in) {
                break;
            }
        }

        /* Copy local maximal pixels to output list */
        outNum = 0;
        for( i = 0; i < num_corners_in; i++ ) {
            if (valid[i] == 1) {
                if(outNum < corners_out_capacity) {
                    corners_out[outNum] = corners_in[i];
                    strengths_out[outNum] = strengths_in[i];
                }
                outNum++;
            }
        }

        /* Copy number of maximal pixels to output parameter */
        *num_corners_out = outNum;
        if(iterations) {
            *iterations = z+1;
        }
    }
    return (status);
}

VXLIB_STATUS VXLIB_harrisCornersNMS_i32f_checkParams_cn(uint32_t corners_in[],
                                                    VXLIB_F32 strengths_in[],
                                                    uint32_t num_corners_in,
                                                    uint32_t corners_out[],
                                                    VXLIB_F32 strengths_out[],
                                                    uint32_t corners_out_capacity,
                                                    uint32_t *num_corners_out,
                                                    int8_t scratch[],
                                                    uint32_t scratch_size,
                                                    VXLIB_F32 min_distance,
                                                    uint8_t *iterations)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;
    uint32_t   neighborhood_size = ((min_distance+1.0f)*2)*((min_distance+1.0f)*2)/9;

    if((corners_in == NULL) || (strengths_in == NULL) || (corners_out == NULL) ||
       (strengths_out == NULL) || (num_corners_out == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if(scratch_size < (2*VXLIB_min(neighborhood_size, num_corners_in)) ) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}

