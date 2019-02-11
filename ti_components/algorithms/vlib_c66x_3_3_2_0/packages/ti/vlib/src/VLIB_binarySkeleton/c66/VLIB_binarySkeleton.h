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
**|        Copyright (c) 2007 - 2014 Texas Instruments Incorporated          |**
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

#ifndef VLIB_BINARY_SKELETON_H_
#define VLIB_BINARY_SKELETON_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_binarySkeleton */
/** @ingroup  VLIB_binarySkeleton */
/* @{ */

/**
 * @par Description:
 *  This function computes Hit-Miss operation using a single programmable
 *  3x3 mask (\c mask[]) and its respective "don't care" mask (\c mask_d[]).
 *
 *  In Hit-Miss, a single 3x3 mask is represented by 1's (foreground), 0's
 *  (background), and X's (don't cares).  This API uses two parameters to
 *  specify this information:
 *  \c mask[] and \c mask_d[]. The 1's and 0's locations in the mask are
 *  specified using the \c mask[] parameter, and the X's (don't care) locations
 *  are specified by using 1 values in the \c mask_d[] paramter, as shown below.
 * @verbatim
    Example:
           1 0 1             1 0 1              0 0 0
     For:  X 1 X  :  mask =  0 1 0    mask_d =  1 0 1
           X 0 X             0 0 0              1 0 1
   @endverbatim
 *
 *  In the above example, output pixel is 1 if: the input pixel (center pixel) is 1, it has a one valued
 *  northwest and northeast neighbors, and it has a zero valued north and south
 *  neighbors. Other neighbors are not considered (don't cares).
 *
 *  This function may be called by multiple times on the same image using different
 *  structuring elements, such is the case in the \ref VLIB_binarySkeleton function.
 *
 * @par
 *    @param [in]  in_data[]          Input image pointer (32-bit packed binary)
 *    @param [out] out_data[]         Output image pointer (32-bit packed binary)
 *    @param [in]  mask[]             Pointer to a 3x3 structural element mask (UQ8.0)
 *    @param [in]  mask_d[]           Pointer to a 3x3 "don't care" mask (UQ8.0)
 *    @param [in]  cols               Number of pixels to process (SQ31.0)
 *    @param [in]  pitch              Pitch of the input image (in terms of number of bits)  (SQ31.0)
 *
 * @par Assumptions:
 *    - The \c in_data and \c out_data buffers are assumed to be 4 byte aligned and not aliased.
 *    - The input \c pitch must be multiples of 32.
 *    - The input \c cols:
 *      -  must be >= 128, and
 *      -  must be multiples of 64, and
 *      -  should have a maximum value equal to the pitch * (height - 2), where
 *         height is the height of the in_data buffer.  \c cols is equivalent to the number of output
 *         pixels (bits) that are written to starting from the out_data pointer.
 *    - The bit-packed input and output are ordered the same way as pixels in the image.
 *      This is different from the IMGLIB requirement for bit-reversed binary pixels within
 *      32-bit words.
 *    - If the data is a region of interest within a larger image, then \c pitch > \c cols, and
 *      this function should be called separately for each line in the region of interest.
 *    - Due to 3x3 filtering, the output will be shifted up one line, and left one pixel.  This creates
 *      a 2 column border on the right edge, and the output is 2 lines smaller than the input (hence the
 *      requirement on max value of \c cols parameter above). The vertical shift can be avoided by passing
 *      pointer to the second row of output as the argument \c out_data to the function.
 *      Since the image is 32-bit backed binary data, horizontal shift cannot be avoided.
 *    - Border pixels will not contain valid data, in particular, the first and last row (if
 *      input and output are vertically aligned), and the two rightmost columns of
 *      the output do not contain valid data due to wraparound of the filtering on each line edge.
 *      See @ref filter_shift for more information.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *
 */
void    VLIB_hitmiss_bin(const uint32_t in_data[restrict],
                         uint32_t out_data[restrict],
                         const uint8_t mask[restrict],
                         const uint8_t mask_d[restrict],
                         int32_t cols,
                         int32_t pitch);

/**
 * @par Description:
 *  This function computes Binary Skeletonization (Thinning) using multiple
 *  iterations of hit-or-miss transform on 90 degree rotated versions of
 *  the given structural elements.  It takes an array of programmable
 *  3x3 masks (\c mask[][]) and their respective "don't care" masks
 *  (\c mask_d[][]).  The number of masks that the \c mask[][] parameter
 *  points to is given by the \c num_st parameter.
 *
 *  In binary skeletonization, a single 3x3 mask is represented by 1's
 *  (foreground), 0's (background), and X's (don't cares).  This API uses
 *  two parameters to specify this information:
 *  \c mask[][] and \c mask_d[][]. The 1's and 0's locations in the mask
 *  are specified using the \c mask[][] parameter, and the X's (don't care)
 *  locations are specified by using 1 values in the \c mask_d[][] paramter,
 *  as shown below.
 * @verbatim
    Example:
           1 0 1             1 0 1              0 0 0
     For:  X 1 X  :  mask =  0 1 0    mask_d =  1 0 1
           X 0 X             0 0 0              1 0 1
   @endverbatim
 *
 *  This function internally calls the \ref VLIB_hitmiss_bin function for
 *  each of the 4 orientations for each structuring element.
 *
 * @par
 *    @param [in]      in_data[]     Input image pointer (32-bit packed binary)
 *    @param [out]     out_data[]    Output image pointer (32-bit packed binary)
 *    @param [in]      scratch[]     Scratch buffer (UQ8.0)
 *    @param [in]      mask[][]      Pointer to array of 3x3 structural element masks (UQ8.0)
 *    @param [in]      mask_d[][]    Pointer to array of 3x3 "don't care" masks (UQ8.0)
 *    @param [in]      width         Width of the image (in terms of bits, since it is packed) (UQ16.0)
 *    @param [in]      height        Height of the image (UQ16.0)
 *    @param [in]      num_st        Number of 3x3 structural elements in mask array, must be > 0. (UQ8.0)
 *    @param [in,out]  iters         As an input, this is the maximum number of iterations to run the algorithm.
 *                                    A value of 0 is the same as setting it to 255.  This value will return the
 *                                    actual number of iterations run. (UQ8.0)
 *
 * @par Assumptions:
 *    - The \c in_data, \c out_data, and \c scratch buffers are assumed to be 4 byte aligned and not aliased.
 *    - The \c out_data buffer should be at least the same size as the \c in_data buffer.
 *    - The \c scratch buffer should be the size as the \c in_data buffer plus 72*num_st bytes.
 *    - The input \c width must be a multiple of 32.
 *    - The result of \c width * \c height:
 *      -  must be >= 128, and
 *      -  must be multiples of 64,
 *    - The bit-packed input and output are ordered the same way as pixels in the image.
 *      This is different from the IMGLIB requirement for bit-reversed binary pixels within
 *      32-bit words.
 *    - Due to 3x3 filtering, the output will be shifted up one line, and left one pixel.  This creates
 *      a 2 column border on the right edge, and the output is 2 lines smaller than the input (hence the
 *      requirement on max value of \c cols parameter above). The vertical shift can be avoided by passing
 *      pointer to the second row of output as the argument \c out_data to the function.
 *      Since the image is 32-bit backed binary data, horizontal shift cannot be avoided.
 *    - Border pixels of \c out_data will not contain valid data, in particular, the two rightmost columns
 *      of the output do not contain valid data.  Additionally, the first and last row of \c out_data are never
 *      written to (if input and output are vertically aligned), so this should be considered during output
 *      buffer initialization, or downstream processing. See @ref filter_shift for more information.
 *    - The terminating condition for this function is = MIN(iters, num_iters), where num_iters is the iteration
 *      number where the the output does not change from the previous iteration.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *
 */
void    VLIB_binarySkeleton(const uint32_t in_data[restrict],
                            uint32_t out_data[restrict],
                            uint32_t scratch[restrict],
                            uint8_t mask[][VLIB_BINSKEL_MASK_SZ],
                            uint8_t mask_d[][VLIB_BINSKEL_MASK_SZ],
                            uint16_t width,
                            uint16_t height,
                            uint8_t num_st,
                            uint8_t * iters
                            );

/** @} */
#endif /* VLIB_BINARY_SKELETON_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_binarySkeleton.h                                     */
/* ======================================================================== */

