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

#ifndef VLIB_CANNY_EDGE_DETECTION_H_
#define VLIB_CANNY_EDGE_DETECTION_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_Canny_Edge_Detection */
/** @ingroup  VLIB_Canny_Edge_Detection */
/* @{ */

/**
 * @par Description:
 *  This function is a wrapper function around the full Canny Edge Detection
 *  algorithms.  It internally calls, in sequence on the image: \ref VLIB_conv_7x7_i8_c8s
 *  (image smoothing), \ref VLIB_xyGradientsAndMagnitude, \ref VLIB_nonMaximumSuppressionCanny,
 *  \ref VLIB_doublethresholding and \ref VLIB_edgeRelaxation.  It requires externally
 *  allocated intermediate buffers to be provided and takes care of border conditions in between
 *  internal function calls.  The above mentioned APIs are independently callable in case
 *  a different sequence is required, intermeidate processing is required, or differ buffer
 *  management is required.
 *
 * @par
 *   @param [in]  *pInput           Pointer to input image array
 *   @param [out] *pBufGradX        Pointer to array containing X gradient
 *   @param [out] *pBufGradY        Pointer to array containing Y gradient
 *   @param [out] *pBufMag          Pointer to array containing magnitude
 *   @param [out] *pBufOut          Pointer to output buffer
 *   @param [out] *pScratch         Pointer to scratch buffer
 *   @param [out] *numItems         Pointer to scalar number of items
 *   @param [in]   width            Input width
 *   @param [in]   height           Input height
 *
 * @par Assumptions:
 *    - The input array and output arrays should not overlap
 *    - The output array must be 32-bit aligned
 *    - The width parameter must be a multiple of 2 and >= 18
 *    - The height parameter must be > 10
 *    - pBufGradX should be a buffer of (width * height * 2) bytes
 *    - pBufGradY should be a buffer of (width * height * 2) bytes
 *    - pBufMag should be a buffer of (width * height * 2) bytes
 *    - pBufOut should be a buffer of (width * height) bytes
 *    - pScratch should be a buffer of (width * height) bytes
 */
void VLIB_Canny_Edge_Detection(const uint8_t *pInput,
                               int16_t *pBufGradX,
                               int16_t *pBufGradY,
                               int16_t *pBufMag,
                               uint8_t *pBufOut,
                               uint8_t *pScratch,
                               int32_t *numItems,
                               uint16_t width,
                               uint16_t height);

/**
 * @par Description:
 *  The convolution kernel accepts seven rows of 'pitch' input pixels
 *  and produces one row of 'width' output pixels using the 7 pixel
 *  square filter mask provided on input.
 * @par
 *  The input mask is rotated 180 degrees before passing it to the
 *  convolution kernel.  The convolution sum is calculated as a point by
 *  point multiplication of the rotated mask with the input image. The
 *  49 resulting multiplications are summed together to produce a 32-bit
 *  intermediate sum. Overflow during accumulation is not prevented,
 *  though assumptions may be applied to filter gain to avoid overflow.
 * @par
 *  The user defined shift value is used to shift the convolution sum
 *  down to an 8-bit range prior to storing in the output array. The
 *  stored result is saturated as an unsigned 8-bit quantity. The mask is
 *  moved one column at a time, advancing the mask over the image until
 *  the entire 'width' is processed.
 * @par
 *   @param [in]  *imgin_ptr      Pointer to an input image of 8-bit pixels
 *   @param [out] *imgout_ptr     Pointer to an output image of 8-bit pixels
 *   @param [in]   width          Number of output pixels
 *   @param [in]   pitch          Number of columns in the image
 *   @param [in]  *mask_ptr       Pointer to an 8-bit filter mask
 *   @param [in]   shift          User specified right shift on sum
 *
 * @par Assumptions:
 *    - The input array and output array should not overlap
 *    - The output array must be 32-bit aligned
 *    - The width parameter must be a non-zero multiple of 2
 *    - The image pitch must be greater than or equal to the width
 *    - Due to wraparound of the filtering on each line edge, the function processes only valid
 *      non-border pixels of the input correctly and this results in the output being cropped
 *      to have only (input_width - 6) x (input_height - 6) valid pixels. Border thickness is
 *      three pixels as the window size used is 7x7.
 *      Also, as the first output pixel is obtained by processing the first valid non-border
 *      input pixel, there is a shift in the output image with respect to the input image.
 *      The shift is three pixels to the left and three pixels to the top. The shift can be
 *      avoided by passing the pointer to the fourth pixel of the fourth row of output as the
 *      argument \c imgout_ptr to the function. Since the output is cropped, its border pixels
 *      do not contain valid data. If the shift is avoided, the output border pixels are invalid.
 *      If the shift is not avoided, six rightmost columns and six bottommost rows of the output
 *      do not contain valid data. This output crop can be avoided by padding input and output
 *      borders with meaningful data, and passing the pointer offset of output to the function.
 *      See @ref filter_shift for more information.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C66x processors
 */
void VLIB_conv_7x7_i8_c8s(const uint8_t *restrict imgin_ptr,
                          uint8_t *restrict imgout_ptr,
                          uint32_t width,
                          int16_t pitch,
                          const int8_t *restrict mask_ptr,
                          int16_t shift);

/**
 * @par Description:
 *  As the third stage in Canny Edge Detection, non-maximum suppression identifies potential edge pixels. It
 *  suppresses all pixels whose edge strength is not a local maximum along the gradient direction.
 *
 * @par Method:
 *  Creates an 8-bit edge map labeling each pixel location as a non-Edge (0) or possible-edge (127).
 *  For each pixel location, the gradient direction is established. Two
 *  virtual points, say at a and b lying along the gradient direction on either side of the current location c are
 *  interpolated using the gradient magnitudes from surrounding neighbors. Locations that achieve a local
 *  maximum are regarded as possible edges, such as, Gmag(c) > Gmag(a) AND Gmag(c) >= Gmag(b);
 *  otherwise, these points are declared non-edges.
 *
 * @par
 *   @param [in]   *pInMag           Pointer to array containing magnitude
 *   @param [in]   *pInGradX         Pointer to array containing X gradient
 *   @param [in]   *pInGradY         Pointer to array containing Y gradient
 *   @param [out]  *pOut             Pointer to output data
 *   @param [in]    width            Input width
 *   @param [in]    pitch            Input pitch
 *   @param [in]    height           input height
 *
 * @par Assumptions:
 *    - This function uses a 3x3 kernel and operates on rows instead of pixels. The
 *      function accepts 3 rows of input (Gx, Gy and Gmag) for every single row of the edge map that is
 *      calculated. This function introduces another 1-pixel border of invalid data around the center-portion of the
 *      edge map. The input pointers should be the top left corner of the image where the processing starts. Take care
 *      in adjusting the pointers according to the filter used for convolution.
 *    - The width should be a multiple of 2 and >= 10
 */
int32_t VLIB_nonMaximumSuppressionCanny(const int16_t *restrict pInMag,
                                        const int16_t *restrict pInGradX,
                                        const int16_t *restrict pInGradY,
                                        uint8_t *restrict pOut,
                                        uint16_t width,
                                        uint16_t pitch,
                                        uint16_t height);

/**
 * @par Description:
 *  Hysteresis thresholding is the final stage within Canny edge detection. With an edge map containing
 *  possible edges, hysteresis thresholding identifies and follows edges. Using both High and Low thresholds,
 *  it is able to maintain edge continuity by linking stronger edge segments that are connected to weaker
 *  segments. This stage is split into two functions \ref VLIB_doublethresholding (block based) and
 *  \ref VLIB_edgeRelaxation (Non block based).
 * @par
 *  This function is block based, and implements the first stage of hysteresis thresholding.
 *
 * @par Method:
 *  This function accepts an edge map, with each location labeled with values of either 0
 *  (non-edge) or 127 (possible-edge). It searches for locations where the magnitude is at or above the high
 *  threshold. Values in the edge map are modified from possible-edge
 *  (127) to edge (255) for line segments.
 *
 * @par
 *   @param [in]      *pInMag               Pointer to array containing magnitude
 *   @param [in,out]  *edgeMap              Pointer to array Edge map
 *   @param [out]     *strongEdgeListPtr    Pointer to array strong edge list
 *   @param [in,out]  *numStrongEdges       Number of edges in strongEdgeListPtr arrray
 *   @param [in]       width                Input width
 *   @param [in]       pitch                Input pitch
 *   @param [in]       height               Input height
 *   @param [in]       loThresh             Lower threshold
 *   @param [in]       hiThresh             Upper thershold
 *   @param [in]       pos_frm              Position offset within the frame that pInMag and edgeMap are pointing to
 *
 * @par Assumptions:
 *    - The size of the strongEdgeListPtr is content dependent, but at its
 *      largest, should be large enough to store 32-bit representation for each edge pixel in the entire image.
 *    - This function is called before \ref VLIB_edgeRelaxation.
 */
int32_t VLIB_doublethresholding(const int16_t *restrict pInMag,
                                uint8_t *edgeMap,
                                uint32_t *restrict strongEdgeListPtr,
                                int32_t *numStrongEdges,
                                uint16_t width,
                                uint16_t pitch,
                                uint16_t height,
                                uint8_t loThresh,
                                uint8_t hiThresh,
                                uint32_t pos_frm);

/**
 * @par Description:
 *  Hysteresis thresholding is the final stage within Canny edge detection. With an edge map containing
 *  possible edges, hysteresis thresholding identifies and follows edges. Using both High and Low thresholds,
 *  it is able to maintain edge continuity by linking stronger edge segments that are connected to weaker
 *  segments. This stage is split into two functions \ref VLIB_doublethresholding (block based) and
 *  \ref VLIB_edgeRelaxation (Non block based).
 * @par
 *  This function is non block based, and implements the second stage of hysteresis thresholding.
 *
 * @par Method:
 *  This function grows the edge segments by following a path of connected edges with
 *  magnitude values at or above the low threshold. Values in the edge map are modified from possible-edge
 *  (127) to edge (255) for line segments.
 *
 * @par
 *   @param [in,out]  *edgeMap              Pointer to array Edge map
 *   @param [in,out]  *strongEdgeListPtr    Pointer to array strong edge list
 *   @param [in]      *numStrongEdges       Number of edges in strongEdgeListPtr arrray
 *   @param [in]       width                Input width
 *
 * @par Assumptions:
 *    - This function is called after \ref VLIB_doublethresholding.
 *    - The size of the strongEdgeListPtr is content dependent, but at its
 *      largest, should be large enough to store 32-bit representation for each edge pixel in the entire image.
 *    - If an edge map is desired that only consists of non-edges (0) and edges (255), it will be necessary to
 *      remove the remaining possible-edges (127) after this function completes. Edge linking is image
 *      content dependent. This function is generally frame-based, so it can be difficult to partition this
 *      function into sub-image blocks, especially for large images. Use caution when locating the
 *      strongEdgeListPtr buffer in fast memory areas (L1D/L2D).
 */
int32_t VLIB_edgeRelaxation(uint8_t *edgeMap,
                            uint32_t *restrict strongEdgeListPtr,
                            const int32_t *numStrongEdges,
                            uint16_t width);

#endif /* VLIB_CANNY_EDGE_DETECTION_H_ */

/** @} */

/* ======================================================================== */
/*  End of file:  VLIB_Canny_Edge_Detection.h                               */
/* ======================================================================== */

