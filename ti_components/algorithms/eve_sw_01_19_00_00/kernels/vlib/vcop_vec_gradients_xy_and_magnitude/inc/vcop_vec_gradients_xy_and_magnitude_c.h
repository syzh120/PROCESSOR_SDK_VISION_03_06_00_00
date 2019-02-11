/*
*
* Copyright (c) 2010-2017 Texas Instruments Incorporated
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

/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef vcop_vec_gradients_xy_and_magnitude_CN
#define vcop_vec_gradients_xy_and_magnitude_CN  1

#include <stdint.h>

void vcop_vec_gradients_xy_and_magnitude_cn
(
    uint8_t  pIn[],
    int16_t          pGradX[],
    int16_t          pGradY[],
    int16_t          pMag[],
    uint16_t width,
    uint16_t height,
    uint16_t pitch
);

void vcop_vec_gradients_xy_and_magnitude_cn2
(
        uint8_t  pIn[],
        int16_t          pGradX[],
        int16_t          pGradY[],
        int16_t          pMag[],
        uint16_t width,
        uint16_t height,
        uint16_t srcStride,
        uint16_t dstStride
);

/* ==================================================
 *  @func     vcop_gradients_xy_list_cn
 *
 *  @desc     This is natural C implementation which  calculates the gradient from the input image and edge data
 *                and outputs a list of points where edgeMap is one and gradients at those
 *                points in packed format
 *
 *  @inputs   This func takes following Inputs
 *                  pIn :
 *                          Pointer the the input gray scale buffer ( 8bit data)
 *                          Size of this buffer should be width * height
 *                  pUpperLeftXY :
 *                          This is pointer to the buffer which contains the upper left corner coordinates
 *                           Size of this array should be  sizeof(uint32_t)
 *                  pEdgeMap :
 *                          Pointer to the binary image containing 1 at locations where edges are present.
 *                          Size of this buffer should be width * height
 *                  width :
 *                          Width of the input buffer
 *                  height :
 *                          Height of the input buffer
 *                  pitchInData :
 *                          Pitch of the input buffer
 *                  pitchEdgeMap :
 *                          Pitch of the edgeMap buffer. The (0,0) pixel of this buffer should correspond to
 *                          (1,1) pixel in image buffer
 *
 *  @outputs   This func produce following outputs
 *                  pGradXY :
 *                          Pointer to the buffer output gradient buffer containing gradient in both X and Y direction in packed format
 *                          for all the pixels for which edgeMap = 1. Output is stored like ( gx<<16) | gy
 *                          Size of this buffer should be (width * height * sizeof(int32_t))
 *                  pEdgeListXY :
 *                          Pointer to the buffer which will contain the x and y coordinates stored in packed format in
 *                          a 32 bit container. ( x<<16) | y.
 *                          Size of this buffer should be width * height * sizeof(uint32_t))
 *                  pListSize :
 *                          Pointer to the buffer which will contain the size of the list of edges.
 *                          Size of this buffer should be sizeof(uint16_t) * 8
 *
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_gradients_xy_list_cn
(
    uint8_t   *pIn,
    uint32_t  *pUpperLeftXy,
    uint8_t   *pEdgeMap,
    int32_t   *pGradXY,
    uint32_t  *pEdgeListXY,
    uint16_t  *pListSize,
    uint16_t   width,
    uint16_t   height,
    uint16_t   pitchInData,
    uint16_t   pitchEdgeMap
);

/* ==================================================
 *  @func     vcop_gradients_xy_mag_lut_index_calulcation_cn
 *
 *  @desc     This is natural C implementation which calculates the index to be used for lookup in reciprocal square root table.
 *                It also outputs (int)log4(a)
 *
 *  @inputs   This func takes following Inputs
 *                  gradXY :
 *                          Pointer to the gradient buffer containing gradient in both X and Y direction in packed format
 *                          for all the pixels for which edgeMap = 1. Gradients are stored as ( gx<<16) | gy
 *                          Size of this buffer should be (width * height * sizeof(int32_t))
 *                  width :
 *                          Width of the input buffer
 *                  height :
 *                          Height of the input buffer
 *                  pitch :
 *                          Pitch of the input buffer
 *
 *  @outputs   This func produce following outputs
 *                  lutIdxPtr :
 *                          This is pointer to the buffer which will contain the index of the reciprocal sqaure root table
 *                           Size of this array should be width * height * sizeof(int16_t)
 *                  log4aPtr :
 *                          This is pointer to the buffer which will contain the value of (int)log4(a). This will be used to
 *                          calculate the square root
 *                           Size of this array should be width * height * sizeof(uint8_t)
 *
 *
 *  @return    NONE
 *
 *  =======================================================
 */

void vcop_gradients_xy_mag_lut_index_calulcation_cn(
                        int16_t  *gradXY,
                        uint16_t *lutIdxPtr,
                        int8_t   *log4aPtr,
                        uint16_t width,
                        uint16_t height,
                        uint16_t pitch);

/* ==================================================
 *  @func     vcop_reciprocal_sqrt_lookup_cn
 *
 *  @desc     This is natural C implementation which does 8 way  lookup in reciprocal square root table.
 *
 *  @inputs   This func takes following Inputs
 *                  lutIdxPtr :
 *                          This is pointer to the buffer which will contain the index of the reciprocal sqaure root table
 *                           Size of this array should be width * height * sizeof(int16_t)
 *                  reciprocalLut :
 *                          This is pointer to the 8 way lookup table.
 *                          Size of this should be  768 * 8
 *                  listSize :
 *                          Size of the list for which lookup is required

 *
 *  @outputs   This func produce following outputs
 *                  reciprocalLutOutput :
 *                          This is pointer to the buffer which will contain the value after the lookup from the given table
 *                           Size of this array should be width * height * sizeof(uint8_t)
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_reciprocal_sqrt_lookup_cn(
                uint16_t    *lutIdxPtr,
                uint8_t     *reciprocalLut,
                uint8_t     *reciprocalLutOutput,
                uint16_t listSize);


/* ==================================================
 *  @func     vcop_gradients_xy_unit_vecs_cn
 *
 *  @desc     This is natural C implementation which calculates the normalized gradients
 *
 *  @inputs   This func takes following Inputs
 *                  gradXY :
 *                          Pointer to the gradient buffer containing gradient in both X and Y direction in packed format
 *                          for all the pixels for which edgeMap = 1. Gradients are stored as ( gx<<16) | gy
 *                          Size of this buffer should be (width * height * sizeof(int32_t))
 *                  log4aPtr :
 *                          This is pointer to the buffer which  contain the value of (int)log4(a). This will be used to
 *                          calculate the square root
 *                           Size of this array should be width * height * sizeof(uint8_t)
 *                  reciprocalLutOutput :
 *                          This is pointer to the buffer which  contain the value after the lookup from the given table
 *                           Size of this array should be width * height * sizeof(uint8_t)
 *                  listSize :
 *                          Size of the list for which normalized gradient is expexted to be computed
 *
 *  @outputs   This func produce following outputs
 *                  unitXYptr :
 *                          This is pointer to the buffer which will contain the normalized gradients in X and Y direction
 *                          in packed format as (Ux<<16) | Uy;
 *                           Size of this array should be width * height * sizeof(u32nt8_t)
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void vcop_gradients_xy_unit_vecs_cn(
                        int16_t     *gradXY,
                        int8_t      *log4aPtr,
                        uint8_t     *reciprocalLutOutput,
                        int32_t     *unitXYPtr,
                        uint16_t listSize);




#endif

/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude_c.h                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



