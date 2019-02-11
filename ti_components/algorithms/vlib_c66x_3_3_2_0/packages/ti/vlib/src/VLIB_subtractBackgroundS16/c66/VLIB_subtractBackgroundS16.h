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

#ifndef VLIB_SUBTRACTBACKGROUNDS16_H_
#define VLIB_SUBTRACTBACKGROUNDS16_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_subtractBackgroundS16 */
/** @ingroup  VLIB_subtractBackgroundS16 */
/* @{ */

/**
 * @par Description:
 *  The function VLIB_subtractBackgroundS16() implements a statistical background
 *  segmentation algorithm. For each pixel, the running mean and variance statistics
 *  are available.  Given a novel luma observation, we test whether its squared
 *  distance from the mean is larger than a multiplicative factor of its variance.
 *  For a pixel to pass the test, its distance should also be greater than a
 *  predefined global threshold, designed to capture inherent camera noise. When
 *  these conditions are satisfied, the observation is deemed to stem from a
 *  foreground object (and not from the modeled background), and the corresponding
 *  mask pixel value is set to 1.
 *
 * @par
 *    @param [out] mask32packed     Binary mask to be computed (32-bit packed)
 *    @param [in]  newLuma          Most recent Luma buffer (UQ8.0)
 *    @param [in]  runningMean      Exponentially weighted running mean buffer (SQ8.7)
 *    @param [in]  runningVar       Exponentially weighted running variance buffer (SQ12.3)
 *    @param [in]  thresholdGlobal  Global threshold value (SQ12.3)
 *    @param [in]  thresholdFactor  Multiplicative factor for threshold (SQ4.11)
 *    @param [in]  PixelCount       Number of pixels to process (UQ32.0)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be double-word aligned and not aliased.
 *    - The PixelCount must be a multiple of 32.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed-point processors
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

int32_t VLIB_subtractBackgroundS16(uint32_t *restrict mask32packed,
                                   const uint8_t *restrict newLuma,
                                   const int16_t *restrict runningMean,
                                   const int16_t *restrict runningVar,
                                   const int16_t thresholdGlobal,
                                   const int16_t thresholdFactor,
                                   const uint32_t PixelCount);

/** @} */
#endif /* VLIB_SUBTRACTBACKGROUNDS16_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_subtractBackgroundS16.h                              */
/* ======================================================================== */

