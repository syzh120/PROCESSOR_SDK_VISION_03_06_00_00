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

#ifndef VLIB_TRACKFEATURESLUCASKANADE_H_
#define VLIB_TRACKFEATURESLUCASKANADE_H_ 1

/** @defgroup VLIB_trackFeaturesLucasKanade_7x7 */
/** @ingroup  VLIB_trackFeaturesLucasKanade_7x7 */
/* @{ */

/**
 * @par Description
 *  This function considers a 7x7 patch centered about the feature coordinate.
 *  Bilinear sampling is used so that the tracked feature coordinates have sub-pixel accuracy.
 *  The number of iterations typically can be between 6 and 10. This API also calculates
 *  transaltion error ( sum of the absolute difference ) between two frames.
 *
 *  The error contains the sum of absolute differences between the window in im1 around (x,y) and
 *  the window in im2 around (outx,outy). Window size is equal to patch size. This error can be
 *  used to discard features whose track_error exceeds a user defined threshold. For features that
 *  have moved very close to the borders of the image, error value returned is 65535.
 *  The algorithm is inverse compositional.
 *
 * @par
 * @param [in]     im1[]          Input Luma image 1,typically points to
                                   previous frame where feature locations
                                   are known.                      (UQ8.0)
 * @param [in]     im2[]          Input Luma image 2,typically points to
                                   current frame where tracked location of
                                   feature points needs to be evaluated.
                                                                   (UQ8.0)
 * @param [in]     gradX[]        X gradient of im1. If this parameter is
                                   passed as NULL then gradient is calculate
                                   inside the kernel.If is provided by user
                                   then its buffer pitch should be same input
                                   image and that is equal to width(SQ15.0)
 * @param [in]     gradY[]        Y gradient of im1. If this parameter is
                                   passed as NULL then gradient is calculate
                                   inside the kernel.If is provided by user
                                   then its buffer pitch should be same input
                                   image and that is equal to width(SQ15.0)
 * @param [in]      width          Image width                     (UQ16.0)
 * @param [in]      height         Image height                    (UQ16.0)
 * @param [in]      nfeatures      Number of features. It should be multiple
                                   of two                          (UQ32.0)
 * @param [in]     x[]            X feature coordinates in im1    (UQ12.4)
 * @param [in]     y[]            Y feature coordinates in im1    (UQ12.4)
 * @param [in,out] outx[]         X feature coordinates in im2, user has to
                                   provide initial estimate of the location
                                   in current frame. In normal situation
                                   user can set this as same as previous
                                   frame location. If a feature goes out
                                   of boundary then its value is set to -1
                                   (ie. 0xFFFFU).
                                                                  (UQ12.4)
 * @param [in,out] outy[]         Y feature coordinates in im2user has to
                                   provide initial estimate of the location
                                   in current frame. In normal situation
                                   user can set this as same as previous
                                   frame location. If a feature goes out
                                   of boundary then its value is set to -1.
                                   (ie. 0xFFFFU).
                                                                  (UQ12.4)
 * @param [out]    error[]        Pure translational error for
                                   each feature point. If this pointer is
                                   provided as NULL then no error calculation
                                   will be done, and less cycle will be
                                   consumed inside the kernel.     (UQ16.0)
 * @param [in]      max_iters      Maximum number of iterations    (UQ32.0)
 * @param [in]      earlyExitTh    Threshold for exiting the iteration
                                   loop. if sum of the absolute differences
                                   of flow vectors in x and y direction is
                                   less than this threshold then iteration
                                   loop is terminated. For no termination
                                   this threshold can be set to zero
                                                                   (UQ32.0)
 * @param [in]     scratch[]      Scratch memory. It is always good to
                                   allocate scratch buffer in L1D. Total size of
                                   the scratch buffer required is 839
                                                                   (UQ8.0)
 *
 * @par Assumptions
 * - The input pointer 'scratch' should be pointing at a memory buffer of 839 bytes.
 *   It should ideally be located in on-chip memory.
 * - The parameters outx and outy are expected to contain initial estimates of feature coordinates in im2.
 *   The function will overwrite these values with refined values. If initial estimates are not known, they
 *   should typically be equal to feature coordinates of im1 (i.e. parameter x & y).
 * - The parameters x, y, outx and outy are expected to be in Q12.4 format. So, the pixel level coordinates
 *   should be left shifted by four before passing them to the function.
 * - No feature coordinates are rejected, so the length of outputs outx and outy is same as the length
 *   of inputs x and y.
 * - Number of features should be multiple of two.
 * - Return value from this function is total number of internal loop execution. If any un-valid
 *   parameter is passed to this kernel then this value returned will be zero. In no early exit
 *   scenario, this value will be equal to max_iters*nfeatures.  If there is early exit for some features,
 *   this value will be between nfeatures <= value < max_iters*nfeatures.  This information can be used to
 *   help aid in performance reporting and the adjustment of the setting of the max_iters paramter.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

int32_t    VLIB_trackFeaturesLucasKanade_7x7(const uint8_t im1[restrict],
                                             const uint8_t im2[restrict],
                                             const int16_t gradX[restrict],
                                             const int16_t gradY[restrict],
                                             uint16_t width,
                                             uint16_t height,
                                             uint32_t nfeatures,
                                             const uint16_t x[restrict],
                                             const uint16_t y[restrict],
                                             uint16_t outx[restrict],
                                             uint16_t outy[restrict],
                                             uint16_t error[restrict],
                                             uint32_t max_iters,
                                             uint32_t earlyExitTh,
                                             uint8_t scratch[restrict]);
/** @} */
#endif /* VLIB_TRACKFEATURESLUCASKANADE_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_trackFeaturesLucasKanade_7x7.h                       */
/* ======================================================================== */

