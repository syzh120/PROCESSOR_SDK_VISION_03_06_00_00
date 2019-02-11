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

#ifndef VLIB_UPDATEUWRMEANS16_H_
#define VLIB_UPDATEUWRMEANS16_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_updateUWRMeanS16 */
/** @ingroup  VLIB_updateUWRMeanS16 */
/* @{ */
/**
 * @par Description:
 *  The function VLIB_updateUWRMeanS16() updates the uniformly-weighted running
 *  mean of a video buffer. This is accomplished by computing the difference between
 *  the oldest and newest frames, weighting it appropriately, and adding the result
 *  to the current running mean value.  If the foreground mask flag bit of either
 *  the newest or the oldest data is set, the running mean is not updated for the
 *  associated region.
 *
 * @par
 *    @param [out] updatedMean          Updated running 16-bit mean (SQ8.7)
 *    @param [in]  previousMean         Current running 16-bit mean (SQ8.7)
 *    @param [in]  newestData           Most recent Luma buffer (UQ8.0)
 *    @param [in]  oldestData           Oldest Luma buffer(UQ8.0)
 *    @param [in]  newestMask32packed   Most recent foreground object mask (32-bit packed)
 *    @param [in]  oldestMask32packed   Oldest foreground object mask (32-bit packed)
 *    @param [in]  pixelCount           Number of pixels to process (UQ32.0)
 *    @param [in]  frameCount           Number of frames in video buffer being averaged (UQ8.0)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be double-word aligned and not aliased.
 *    - The pixelCount must be a multiple of 8.
 *    - frameCount is greater than 1
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C6XXX fixed-point processors
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

int32_t VLIB_updateUWRMeanS16(int16_t *restrict updatedMean,
                              const int16_t *restrict previousMean,
                              const uint8_t *restrict newestData,
                              const uint8_t *restrict oldestData,
                              const uint32_t *restrict newestMask32packed,
                              const uint32_t *restrict oldestMask32packed,
                              const uint32_t pixelCount,
                              const uint8_t frameCount);
#endif /* VLIB_UPDATEUWRMEANS16_H_ */
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_updateUWRMeanS16.h                                   */
/* ======================================================================== */

