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
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
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

#ifndef VLIB_CONVERTUYVYPL_TO_YUVINT_H_
#define VLIB_CONVERTUYVYPL_TO_YUVINT_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_convertUYVYpl_to_YUVint */
/** @ingroup  VLIB_convertUYVYpl_to_YUVint */
/* @{ */

/**
 * @par Introduction and Use Cases:
 *   YUV422 is a common imaging data format. If the information stored in the planar YUV format needs
 *   to be displayed it often needs to be interleaved first. This functions efficiently interleaves the YUV color
 *   channels.
 *
 * @par Description:
 *   This function interleaves the three YUV422 planar channels into a single YUV422 interleaved format.
 *
 * @par
 *  @param [in]  *y          Luma plane (8-bit)                           (UQ8.0)
 *  @param [in]  *cr         Cr chroma plane (8-bit)                      (UQ8.0)
 *  @param [in]  *cb         Cb chroma plane (8-bit)                      (UQ8.0)
 *  @param [in]   width      Width of input image (number of luma pixels) (in pixels)
 *  @param [in]   pitch      Pitch of input image (number of luma pixels) (in pixels)
 *  @param [in]   height     Height of input image(number of luma pixels) (in pixels)
 *  @param [out] *yc         Interleaved luma/chroma                      (UQ8.0)
 *
 * @par Assumptions
 *  - All arrays should be 64-bit aligned.
 *  - width should be a multiple of 16, and greater than 0
 *  - pitch should be a multiple of 16, and >= width
 *  - the *y buffer is of pitch bytes between start of each line
 *  - the *cr and *cb buffers is of pitch/2 bytes between start of each line
 *  - *yc buffer stores each line of width with no gap in between (pitch only applies
 *    to input buffers).
 *
 * @par Implementation Notes:
 *  - Internally, there are 2 modes:
 *    - Mode 1: Most efficient mode is when pitch == width
 *    - Mode 2: Kernel supports when pitch > width, but less performance
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 * @par References:
 *  -# <em> Digital Image Processing </em> by R.C.Gonzales and R.E.Woods, Prentice-Hall, 2007
 *
 */
int32_t VLIB_convertUYVYpl_to_YUVint(const uint8_t *restrict y,
                                     const uint8_t *restrict cr,
                                     const uint8_t *restrict cb,
                                     uint32_t width,
                                     int32_t pitch,
                                     uint32_t height,
                                     uint8_t *restrict yc);

/** @} */
#endif /* VLIB_CONVERTUYVYPL_TO_YUVINT_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYpl_to_YUVint.h                         */
/* ======================================================================== */

