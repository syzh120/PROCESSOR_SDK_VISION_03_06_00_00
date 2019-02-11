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
**|  with devices manufactured by or for TI ('TI Devices').  No hardware     |**
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

#ifndef VLIB_GRAYSCALE_MORPHOLOGY_H_

#define VLIB_GRAYSCALE_MORPHOLOGY_H_ 1

#include "../../common/VLIB_types.h"
#include "../VLIB_grayscale_morphology_types.h"

/** @defgroup VLIB_grayscale_morphology */
/** @ingroup  VLIB_grayscale_morphology */
/* @{ */

/**
 * @par Description:
 *   This is a wrapper function that internally calls one of the grayscale morphology
 *   operations depending on the \c operation parameter being set to one of the options
 *   listed in \ref GrayscaleMorphologyOperation.
 *
 * @par
 *   @param [in]  blk_w            width of input block, in elements                           (UQ16.0)
 *   @param [in]  line_ofst        offset between input lines, in elements                     (UQ16.0)
 *   @param [in]  blk_h            height of input block                                       (UQ16.0)
 *   @param [in]  data_ptr[]       input data pointer                                          (UQ8.0)
 *   @param [in]  se_w             width of structuring element block, in elements             (UQ16.0)
 *   @param [in]  se_h             height of structuring element block                         (UQ16.0)
 *   @param [in]  se_ptr[]         structuring element data pointer                            (UQ8.0)
 *   @param [in]  refl_se_ptr[]    Reflected structuring element data pointer                  (UQ8.0)
 *   @param [in]  scratch1_ptr[]   scratch 1 pointer. Size of this scratch buffer should be
 *                                 equal to input image size                                   (UQ8.0)
 *   @param [in]  scratch2_ptr[]   scratch 2 pointer. This scratch buffer is for temproray data
 *                                 storage and it is used only when se_h =1, and all the
 *                                 elements of structuring element is one and
 *                                (blk_h - (se_h-1))%se_h = 0. Size of this buffer should be 32*se_h (UQ8.0)
 *   @param [out] output_ptr[]     output data pointer                                         (UQ8.0)
 *   @param [in]  operation        Operation selection \ref GrayscaleMorphologyOperation       (UQ8.0)
 *
 * @par Assumptions:
 *    - For this API 'se_w' and 'se_h' both should be any odd positive number and one of them should be
 *      greater than or equal to 3.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed and floating point processors
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_grayscale_morphology
(
    uint16_t blk_w,
    uint16_t line_ofst,
    uint16_t blk_h,
    const uint8_t data_ptr[],
    uint16_t se_w,
    uint16_t se_h,
    const uint8_t se_ptr[],
    const uint8_t refl_se_ptr[],
    uint8_t scratch1_ptr[],
    uint8_t scratch2_ptr[],
    uint8_t output_ptr[],
    uint8_t operation
);

/**
 * @par Description:
 *  Performs grayscale dilation of an 8-bit grayscale input image
 *  at data_ptr, of size blk_w by blk_h, with a flat structuring
 *  element of size se_w by se_h, specified with a mask of 1's
 *  and 0's at se_ptr. The dilation operator considers only the non zero values
 *  of input mask, and finds the maximum of all corresponding input pixels under
 *  the mask which is the value of output pixel at the location of the center
 *  pixel of the mask. The output is written into output_ptr.
 *  This API internally calls other specific API's suited for specific sizes.
 * @verbatim
    Example:
    For the mask
    0 1 0
    1 1 1
    0 1 0

    The output pixel is the maximum of input (center) pixel, its north, east, west and south neighbors.
   @endverbatim
 *
 *
 * @par
 *   @param [in]  blk_w            width of input block, in elements                            (UQ16.0)
 *   @param [in]  line_ofst        offset between input lines, in elements                      (UQ16.0)
 *   @param [in]  blk_h            height of input block                                        (UQ16.0)
 *   @param [in]  data_ptr[]       input data pointer                                           (UQ8.0)
 *   @param [in]  se_w             width of structuring element block, in elements              (UQ16.0)
 *   @param [in]  se_h             height of structuring element block                          (UQ16.0)
 *   @param [in]  se_ptr[]         structuring element data pointer                             (UQ8.0)
 *   @param [in]  scratchBuf[]     scratch buffer for temproray data storage and it is used
 *                                 only when se_h=1, and all the elements of structuring element
 *                                 are one and (blk_h - (se_h-1))%se_h = 0. Size of this buffer should
 *                                 be 32*se_h                                                   (UQ8.0)
 *   @param [out] output_ptr[]     output data pointer                                          (UQ8.0)
 *
 * @par Assumptions:
 *    - For this API 'se_w' and 'se_h' both should be any odd positive number and one of them should be
 *      greater than or equal to 3.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed and floating point processors
 *    - For Mx1 structuring elements where all the elements are '1', better
 *      performance number can be achieved if (blk_h - (se_h-1))%se_h = 0. To satisfy
 *      this condition extra dummy rows can be provided along with input image.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_grayscale_dilate_mask
(
    uint16_t blk_w,
    uint16_t line_ofst,
    uint16_t blk_h,
    const uint8_t data_ptr[restrict],
    uint16_t se_w,
    uint16_t se_h,
    const uint8_t se_ptr[restrict],
    uint8_t scratchBuf[restrict],
    uint8_t output_ptr[restrict]
);

/**
 * @par Description:
 *  Performs image difference operation between two 8-bit gray-
 *  scale images at data_ptr and data2_ptr, both of size blk_w
 *  by blk_h, and writes the output into output_ptr. The function
 *  assumes that the image pixel values at data_ptr is greater
 *  than the corresponding pixel values at data2_ptr. Also it has
 *  been assumed that subtraction results fits in 8 bit.
 *
 * @par
 *   @param [in]   blk_w            width of input block, in elements          (UQ16.0)
 *   @param [in]   line_ofst        offset between input lines, in elements    (UQ16.0)
 *   @param [in]   blk_h            height of input block                      (UQ16.0)
 *   @param [in]   data_ptr[]       input 1 data pointer                       (UQ8.0)
 *   @param [in]   data2_ptr[]      input 2 data pointer                       (UQ8.0)
 *   @param [out]  output_ptr[]     output data pointer                        (UQ8.0)
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed and floating point processors
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void VLIB_grayscale_morp_diff(uint16_t blk_w,
                              uint16_t line_ofst,
                              uint16_t blk_h,
                              const uint8_t data_ptr[restrict],
                              const uint8_t data2_ptr[restrict],
                              const uint8_t output_ptr[restrict]);

/**
 * @par Description:
 *  Performs image gradient operation by finding the difference between
 *  the dilated and eroded input image, both of size blk_w
 *  by blk_h, and writes the output into output_ptr. The function
 *  assumes that the image pixel values in dilated image is greater
 *  than the corresponding pixel values in eroded image.
 *
 * @par
 *   @param [in]   blk_w            width of input block, in elements          (UQ16.0)
 *   @param [in]   line_ofst        offset between input lines, in elements    (UQ16.0)
 *   @param [in]   blk_h            height of input block                      (UQ16.0)
 *   @param [in]   data_ptr[]       input data pointer                       (UQ8.0)
 *   @param [in]   se_w             width of structuring element block, in elements  (UQ16.0)
 *   @param [in]   se_h             height of structuring element block              (UQ16.0)
 *   @param [in]   se_ptr[]         structuring element data pointer                 (UQ8.0)
 *   @param [in]   refl_se_ptr[]    Reflected structuring element data pointer       (UQ8.0)
 *   @param [in]  scratchBuf[]      scratch Buffer for temproray data storage and it is used
 *                                  only when se_h=1, and all the elements of structuring element
 *                                  is one and (blk_h - (se_h-1))%se_h = 0. Size of this buffer should
 *                                  be 32*se_h                                 (UQ8.0)
 *   @param [out]  output_ptr[]     output data pointer                        (UQ8.0)
 *
 * @par Assumptions:
 *    - For this API se_w and se_h both should odd positive number and one of them should be
 *      greater than equal to 3.
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed and floating point processors
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_grayscale_gradient_mask
(
    uint16_t blk_w,
    uint16_t line_ofst,
    uint16_t blk_h,
    const uint8_t data_ptr[restrict],
    uint16_t se_w,
    uint16_t se_h,
    const uint8_t se_ptr[restrict],
    const uint8_t refl_se_ptr[restrict],
    uint8_t scratchBuf[restrict],
    uint8_t output_ptr[restrict]
);

/**
 * @par Description:
 *  Performs grayscale erosion of an 8-bit grayscale input image
 *  at data_ptr, of size blk_w by blk_h, with a flat structuring
 *  element of size se_w by se_h, specified with a mask of 1's
 *  and 0's at se_ptr. The erosion operator considers only the non zero values
 *  of input mask, and finds the minimum of all corresponding input pixels under
 *  the mask which is the value of output pixel at the location of the center
 *  pixel of the mask. The output is written into output_ptr.
 * @verbatim
    Example:
    For the mask
    0 1 0
    1 1 1
    0 1 0

    The output pixel is the minimum of input (center) pixel, its north, east, west and south neighbors.
   @endverbatim
 *
 * @par
 *   @param [in]   blk_w            width of input block, in elements                            (UQ16.0)
 *   @param [in]   line_ofst        offset between input lines, in elements                      (UQ16.0)
 *   @param [in]   blk_h            height of input block                                        (UQ16.0)
 *   @param [in]   data_ptr[]       input data pointer                                           (UQ8.0)
 *   @param [in]   se_w             width of structuring element block, in elements              (UQ16.0)
 *   @param [in]   se_h             height of structuring element block                          (UQ16.0)
 *   @param [in]   se_ptr[]         structuring element data pointer                             (UQ8.0)
 *   @param [in]  scratchBuf[]      scratch Buffer for temproray data storage and it is used
 *                                  only when se_h=1, and all the elements of structuring element
 *                                  is one and (blk_h - (se_h-1))%se_h = 0. Size of this buffer should
 *                                  be 32*se_h                                                   (UQ8.0)

 *   @param [out]  output_ptr[]     output data pointer                                          (UQ8.0)
 *
 * @par Assumptions:
 *    - For this API 'se_w' and 'se_h' both should be any odd positive number and one of them should be
 *      greater than or equal to 3.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX floating point processors
 *    - For Mx1 structuring elements where all the elements are '1', better
 *      performance number can be achieved if (blk_h - (se_h-1))%se_h = 0. To satisfy
 *      this condition extra dummy rows can be provided along with input image.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void    VLIB_grayscale_erode_mask
(
    uint16_t blk_w,
    uint16_t line_ofst,
    uint16_t blk_h,
    const uint8_t data_ptr[restrict],
    uint16_t se_w,
    uint16_t se_h,
    const uint8_t se_ptr[restrict],
    uint8_t scratchBuf[restrict],
    uint8_t output_ptr[restrict]
);


#endif /* VLIB_GRAYSCALE_MORPHOLOGY_H_ */

/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_grayscale_morphology.h                                */
/* ======================================================================== */

