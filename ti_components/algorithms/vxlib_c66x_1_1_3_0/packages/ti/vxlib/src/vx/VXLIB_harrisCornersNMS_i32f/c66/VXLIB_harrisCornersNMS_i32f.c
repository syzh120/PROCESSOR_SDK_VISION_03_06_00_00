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

#include "VXLIB_harrisCornersNMS_i32f.h"
#include <string.h>

CODE_SECTION(VXLIB_harrisCornersNMS_i32f,              ".text:optimized")
CODE_SECTION(VXLIB_harrisCornersNMS_i32f_core,         ".text:optimized")
CODE_SECTION(VXLIB_harrisCornersNMS_i32f_checkParams,  ".text:optimized")

/* MISRA.ITER.ONETERM
 * MISRAC_2004 Rule_14.6
 * MISRAC_WAIVER:
 * There are 2 loops in this function which have 2 break statments each.
 * I am able to remove one or both of these by adding a flag that the
 * loop can conditionally terminate in, but the performance suffers by
 * as much as a hundred cycles per feature per iteration (>15%).
 * Therefore, we are requesting a waiver for this in the interest of
 * performance.
 */

static inline void VXLIB_harrisCornersNMS_i32f_core(const uint32_t corners_in[restrict],
                                                  const VXLIB_F32 strengths_in[restrict],
                                                  uint32_t num_corners_in,
                                                  uint32_t corners_out[restrict],
                                                  VXLIB_F32 strengths_out[restrict],
                                                  uint32_t corners_out_capacity,
                                                  uint32_t *num_corners_out,
                                                  uint16_t neighbor_index[restrict],
                                                  int8_t   valid[restrict],
                                                  VXLIB_F32 min_distance,
                                                  uint8_t *iterations);

static inline void VXLIB_harrisCornersNMS_i32f_core(const uint32_t corners_in[restrict],
                                                  const VXLIB_F32 strengths_in[restrict],
                                                  uint32_t num_corners_in,
                                                  uint32_t corners_out[restrict],
                                                  VXLIB_F32 strengths_out[restrict],
                                                  uint32_t corners_out_capacity,
                                                  uint32_t *num_corners_out,
                                                  uint16_t neighbor_index[restrict],
                                                  int8_t   valid[restrict],
                                                  VXLIB_F32 min_distance,
                                                  uint8_t *iterations)
{
    uint32_t i, outNum;
    int32_t j, z, iters;
    uint32_t marked = 0;
    uint32_t x1, y1;
    int32_t dxi, dyi;
    VXLIB_F32 dx, dy, distance;
    __float2_t dydx, dydxsq;
    
    VXLIB_F32 distsq = min_distance*min_distance;

    /* Allow user to set maximum iterations, otherwise set to some high number */
    if( (iterations == NULL) || (*iterations == 0) ) {
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
                uint32_t x = corners_in[i] & 0xFFFFU;
                uint32_t y = corners_in[i] >> 16;
                uint32_t found = 0;
                uint32_t neighbor_cnt = 0;

                /* Search backward through list until we are beyond the min_distance, vertically */
                for ( j = (int32_t)i-1; j >= 0; j-- ) {

                    /* Skip the suppressed pixels */
                    if (valid[j] != -1) {

                        x1 = corners_in[j] & 0xFFFFU;
                        y1 = corners_in[j] >> 16;

                        dxi = (int32_t)x1 - (int32_t)x;
                        dyi = (int32_t)y1 - (int32_t)y;

                        dx = (VXLIB_F32)dxi;
                        dy = (VXLIB_F32)dyi;

                        /* Exit early if we are beyond the min_distance, vertically */
                        if( _fabsf(dy) > min_distance ) {
                            break;
                        }
                        dydx = _ftof2(dy, dx);
                        dydxsq = _dmpysp(dydx, dydx);
                        distance = _lof2(dydxsq) + _hif2(dydxsq);

                        /* If feature is within radius */
                        if( distance < distsq ) {

                            /* If feature is stronger, then exit, not a strong feature */
                            if ( strengths_in[j] > strengths_in[i] ) {
                                found = 1U;
                                break;
                            } else {
                                /* If feature is weaker, then add to neighbor list for possible suppression */
                                neighbor_index[neighbor_cnt] = (uint16_t)j;
                                neighbor_cnt++;
                            }
                        }
                    }
                }
                if(found == 0) {
                    /* Search forward through list until we are beyond the min_distance, vertically */
                    for ( j = (int32_t)i+1; j < (int32_t)num_corners_in; j++ ) {

                        /* Skip the suppressed pixels */
                        if (valid[j] != -1) {

                            x1 = corners_in[j] & 0xFFFFU;
                            y1 = corners_in[j] >> 16;

                            dxi = (int32_t)x1 - (int32_t)x;
                            dyi = (int32_t)y1 - (int32_t)y;

                            dx = (VXLIB_F32)dxi;
                            dy = (VXLIB_F32)dyi;

                            /* Exit early if we are beyond the min_distance, vertically */
                            if( _fabsf(dy) > min_distance ) {
                                break;
                            }

                            dydx = _ftof2(dy, dx);
                            dydxsq = _dmpysp(dydx, dydx);
                            distance = _lof2(dydxsq) + _hif2(dydxsq);

                            /* If feature is within radius */
                            if( distance < distsq ) {

                                /* If feature is stronger, then exit, not a strong feature */
                                if ( strengths_in[j] >= strengths_in[i] ) {
                                    found = 1U;
                                    break;
                                } else {
                                    /* If feature is weaker, then add to neighbor list for possible suppression */
                                    neighbor_index[neighbor_cnt] = (uint16_t)j;
                                    neighbor_cnt++;
                                }
                            }
                        }
                    }
                }

                /* If no neighbors were found to be stronger, mark as valid feature and suppress neighbors */
                if(found == 0) {
                    valid[i] = 1;
                    marked++;

                    /* 1 cycle per neighbor pixel */
                    for ( j = 0; j < (int32_t)neighbor_cnt; j++ ) {
                        valid[neighbor_index[j]] = (int8_t)-1;
                        marked++;
                    }
                }
            }
        }
        if(marked >= num_corners_in) {
            break;
        }
    }

    outNum = 0;

    /* Copy local maximal pixels to output list */
    /* 3 cycles per input feature */
    for( i = 0; i < num_corners_in; i++ ) {
        if (valid[i] == 1) {
            if(outNum < corners_out_capacity) {
                _amem4(&corners_out[outNum]) = _amem4_const(&corners_in[i]);
                _amem4(&strengths_out[outNum]) = _amem4_const(&strengths_in[i]);
            }
            outNum++;
        }
    }

    /* Copy number of maximal pixels to output parameter */
    *num_corners_out = outNum;
    if(iterations != NULL) {
        *iterations = (uint8_t)z+1U;
    }
}

VXLIB_STATUS VXLIB_harrisCornersNMS_i32f(const uint32_t corners_in[restrict],
                                     const VXLIB_F32 strengths_in[restrict],
                                     uint32_t num_corners_in,
                                     uint32_t corners_out[restrict],
                                     VXLIB_F32 strengths_out[restrict],
                                     uint32_t corners_out_capacity,
                                     uint32_t *num_corners_out,
                                     int8_t   scratch[restrict],
                                     uint32_t scratch_size,
                                     VXLIB_F32 min_distance,
                                     uint8_t *iterations)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;

#if defined(VXLIB_CHECK_PARAMS) || defined(VXLIB_HARRISCORNERSNMS_I32F_CHECK_PARAMS)
    status = VXLIB_harrisCornersNMS_i32f_checkParams(corners_in, strengths_in, num_corners_in, corners_out, strengths_out, corners_out_capacity, num_corners_out, scratch, scratch_size, min_distance, iterations);
    if( status == VXLIB_SUCCESS )
#endif
    {
        VXLIB_F32 ceilingOfDistance = min_distance+1.0f;
        int32_t  neighborhood_side = (int32_t)ceilingOfDistance*2;
        int32_t  neighborhood_size = (neighborhood_side*neighborhood_side)/9;
        uint16_t *neighbor_index = (uint16_t*)scratch;
        int8_t   *valid = (int8_t*)&scratch[2*VXLIB_min(neighborhood_size, (int32_t)num_corners_in)];

        VXLIB_harrisCornersNMS_i32f_core(corners_in, strengths_in, num_corners_in, corners_out, strengths_out, corners_out_capacity,
                                     num_corners_out, neighbor_index, valid, min_distance, iterations);
    }
    return (status);
}

#if (!defined(VXLIB_REMOVE_CHECK_PARAMS) && !defined(VXLIB_HARRISCORNERSNMS_I32F_REMOVE_CHECK_PARAMS)) || (defined(VXLIB_CHECK_PARAMS)) || (defined(VXLIB_HARRISCORNERSNMS_I32F_CHECK_PARAMS))

VXLIB_STATUS VXLIB_harrisCornersNMS_i32f_checkParams(const uint32_t corners_in[],
                                                 const VXLIB_F32 strengths_in[],
                                                 uint32_t num_corners_in,
                                                 const uint32_t corners_out[],
                                                 const VXLIB_F32 strengths_out[],
                                                 uint32_t corners_out_capacity,
                                                 const uint32_t *num_corners_out,
                                                 const int8_t scratch[],
                                                 uint32_t scratch_size,
                                                 VXLIB_F32 min_distance,
                                                 const uint8_t *iterations)
{
    VXLIB_STATUS    status = VXLIB_SUCCESS;
    VXLIB_F32 ceilingOfDistance = min_distance+1.0f;
    int32_t  neighborhood_side = (int32_t)ceilingOfDistance*2;
    int32_t  neighborhood_size = (neighborhood_side*neighborhood_side)/9;

    if((corners_in == NULL) || (strengths_in == NULL) || (corners_out == NULL) ||
       (strengths_out == NULL) || (num_corners_out == NULL) || (scratch == NULL)) {
        status = VXLIB_ERR_NULL_POINTER;
    } else if((int32_t)scratch_size < (2*VXLIB_min(neighborhood_size, (int32_t)num_corners_in)) ) {
        status = VXLIB_ERR_BUFFER_TOO_SMALL;
    } else {
        status = VXLIB_SUCCESS;
    }
    return (status);
}
#endif
