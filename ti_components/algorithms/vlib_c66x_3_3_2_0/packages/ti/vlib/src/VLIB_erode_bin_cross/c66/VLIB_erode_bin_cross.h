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

#ifndef VLIB_ERODE_BIN_CROSS_H_
#define VLIB_ERODE_BIN_CROSS_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_erode_bin_cross */
/** @ingroup  VLIB_erode_bin_cross */
/* @{ */

/**
* @par Description:
*  This function implements binary erosion using s cross-shaped 3x3 mask on a
*  bit-packed binary image. So, every bit of input and output images represents a pixel.
 * @verbatim

           0 1 0
    mask = 1 1 1    (3x3 cross)
           0 1 0
   @endverbatim
*  The mask differs from the 3x3 square mask in that
*  all corner pixels are disregarded (set to zero) and don't contribute to the
*  binary product.  The erosion operator generates output pixels by performing a
*  binary AND of all pixels under the cross-shaped input mask to generate an output
*  pixel at the location of the center pixel of the mask.
* @par
*    @param [in]  in_data    Input image pointer (32-bit packed binary, UQ8.0)
*    @param [out] out_data   Output image pointer (32-bit packed binary, UQ8.0)
*    @param [in]  cols       Number of pixels (bits) to be processed (SQ31.0)
*    @param [in]  pitch      Pitch of the input image (SQ31.0)
*
* @par Assumptions:
*    - I/O buffers are assumed to be four byte aligned and not aliased.
*    - The inputs \c cols and \c pitch must be multiples of 32.
*    - The bit-packed input and output are ordered the same way as pixels in the image.
*      This is different from the IMGLIB requirement for bit-reversed binary pixels within
*      32-bit words.
*    - If the data is a region of interest within a larger image, then \c pitch < \c cols.
*    - The function causes a shift in the output image with respect to the input image.
*      The shift is one pixel to the left and one pixel to the top. See
*      @ref filter_shift for more information. The vertical shift can be avoided by passing
*      pointer to the second row of output as the argument \c out_data to the function.
*      Since the image is 32-bit backed binary data, horizontal shift cannot be avoided.
*    - Border pixels will not contain valid data, in particular, the first and last row (if
*      input and output are vertically aligned), as well as two rightmost columns of the
*      output do not contain valid data.
*
* @par Implementation Notes:
*    - This code is fully interruptible
*    - This code is compatible with C6XXX fixed-point processors
*
* @par Benchmarks:
*  See VLIB_Test_Report.html for cycle and memory information.
*
*/

void VLIB_erode_bin_cross(const uint8_t *restrict in_data,
                          uint8_t *restrict out_data,
                          int32_t cols,
                          int32_t pitch);

/** @} */

#endif /* VLIB_ERODE_BIN_CROSS_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_erode_bin_cross.h                                    */
/* ======================================================================== */

