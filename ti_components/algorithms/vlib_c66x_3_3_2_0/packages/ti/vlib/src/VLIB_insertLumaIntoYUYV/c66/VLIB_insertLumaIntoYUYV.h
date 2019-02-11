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

#ifndef VLIB_INSERTLUMAINTOYUYV_H_
#define VLIB_INSERTLUMAINTOYUYV_H_ 1

/** @defgroup VLIB_insertLumaIntoYUYV*/
/** @ingroup  VLIB_insertLumaIntoYUYV */
/* @{ */

/**
 * @par Introduction and Use Cases:
 *   When the image data is stored in the YUV422 format but the processing needs to be done on its
 *   luminance component only, it is often desirable to extract the Y component and store it in a separate
 *   buffer. This is particularly useful when data needs to be contiguous.  After the luma-only processing
 *   is complete, it may be desirable to reinsert the modified luma data back into the original YUV422
 *   image.
 *
 * @par Description:
 *   This function overwrites the luminance data of the pOutYUYV interleaved image using the the luma-only
 *   pInYbuffer data. The chrominance components of the output image are unaffected.
 *
 * @par
 *   @param [in]     *pInY          Luma-only input image       (UQ8.0)
 *   @param [in]      inCols        Width of input image        (in luma pixels)
 *   @param [in]      inPitch       Pitch of pOutYUYV image     (in luma pixels)
 *   @param [in]      inRows        Height of input image       (in luma pixels)
 *   @param [in,out] *pOutYUYV      Output YUV422 image         (UQ8.0)
 *
 * @par Assumptions
 *  - All arrays should be 64-bit aligned.
 *  - inCols should be a multiple of 16, and greater than 0
 *  - inPitch should be a multiple of 4, and >= inCols
 *  - inPitch applies to the number of luma pixels per row of the pOutYUYV buffer, it
 *    doesn't apply to the pInY buffer.  The pitch of the pInY buffer is assumed to be
 *    the same as inCols.
 *
 * @par Implementation Notes:
 *  - Internally, there are 2 modes:
 *    - Mode 1: Most efficient mode is when inPitch == inCols
 *    - Mode 2: Kernel supports when inPitch > inCols, but less performance
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t VLIB_insertLumaIntoYUYV(const uint8_t *restrict pInY,
                                uint16_t inCols,
                                uint16_t inPitch,
                                uint16_t inRows,
                                uint8_t *restrict pOutYUYV);

#endif /* VLIB_INSERTLUMAINTOYUYV_H_*/

/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_insertLumaIntoYUYV.h                                */
/* ======================================================================== */

