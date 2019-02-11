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

#ifndef VLIB_NONMAXSUPRESS5X5_H_
#define VLIB_NONMAXSUPRESS5X5_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_nonMaxSuppress_5x5_S16*/
/** @ingroup  VLIB_nonMaxSuppress_5x5_S16 */
/* @{ */

/**
 * @par Description
 *  This function compares the value of each input pixel against its neighbors. For an output pixel
 *  to be "on" (numerical value=255), the input pixel value must be both:
 *  - Greater than or equal to its neighbors values
 *  - Greater than the minimum threshold
 * @par
 *  If the above conditions are not met simultaneously, the output will be 0.
 * @par
 *  The function processes only valid non-border pixels of the input and this results
 *  in the output being cropped to have only (\c width - 4) x (\c height - 4) valid pixels.
 *  Border thickness is two pixels as the window size used is 5x5.
 *  Also, as the first output pixel is obtained by processing the first valid non-border
 *  input pixel, there is a shift in the output image with respect to the input image.
 *  The shift is two pixels to the left and two pixels to the top. The shift can be avoided
 *  by passing the pointer to the third pixel of the third row of output as the argument
 *  \c out to the function. Since the output is cropped, its border pixels do not contain
 *  valid data. If the shift is avoided, the output border pixels are invalid. If the shift
 *  is not avoided, four rightmost columns and four bottommost rows of the output do not contain
 *  valid data. See @ref filter_shift for more information.
 *
 * @par
 *    @param [in]  *im       Input image                         (SQ15.0)
 *    @param [in]   width    Image width                         (SQ31.0)
 *    @param [in]   height   Image height                        (SQ31.0)
 *    @param [in]   thresh   Minimum threshold for peaks         (SQ15.0)
 *    @param [out] *out      Binary output indicating peaks      (UQ8.0)
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_nonMaxSuppress_5x5_S16(const int16_t *restrict im,
                                    int32_t width,
                                    int32_t height,
                                    int16_t thresh,
                                    uint8_t *restrict out);

/** @} */

#endif /* VLIB_NONMAXSUPRESS5X5_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_nonMaxSuppress_5x5_S16.h                             */
/* ======================================================================== */

