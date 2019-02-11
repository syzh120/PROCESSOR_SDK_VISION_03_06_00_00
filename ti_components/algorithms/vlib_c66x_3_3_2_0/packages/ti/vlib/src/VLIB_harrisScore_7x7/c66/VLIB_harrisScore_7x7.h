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

#ifndef VLIB_HARRISSCORE_7X7_H_
#define VLIB_HARRISSCORE_7X7_H_ 1

/** @defgroup VLIB_harrisScore_7x7*/
/** @ingroup  VLIB_harrisScore_7x7 */
/* @{ */

/**
 * @par Description
 *  This function computes the Harris corner score for each pixel in a luma image. As input, the function takes the
 *  horizontal and vertical gradients of the image. This gives flexibility to the user in selecting the scale for
 *  gradient computations.
 *
 * @par
 * @param [in]  gradX[]  Horizontal gradient of the input luma image (SQ15.0)
 * @param [in]  gradY[]  Vertical gradient of the input luma image   (SQ15.0)
 * @param [in]  width    Image width                                 (SQ31.0)
 * @param [in]  height   Image height                                (SQ31.0)
 * @param [out] outm[]   Harris (cornerness) score                (exp=6 man=10)
 * @param [in]  k        Sensitivity parameter                       (UQ1.15)
 * @param [in]  buffer[] Scratch buffer                              (UQ8.0)
 *
 * @par Method
 *  For each pixel, the following equations together compute the 2x2 gradient covariance matrix M,
 *  where the summations are over 7x7 pixel neighborhoods:
 *  @verbatim

    M(1,1) = sum(gradX)^2
    M(1,2) = M(2,1) = sum(gradX x gradY)
    M(2,2) = sum(gradY)^2
    @endverbatim
 *  The cornerness score is defined as in the following equation, where k is a tunable sensitivity parameter, typically around 0.04. The underlying score computation
 *  generates a signed 47 bit result, which is internally computed using signed 64-bit data types (int64_t).
 *  @verbatim
    Score (signed 47-bit)   = det(M) - k * trace(M)^2
@endverbatim
 *  To save memory storing this data, the algorithm compresses this output to 16 bits using an approximation of the binary log.  Order relationships between different
 *  score values is maintained in this format, up to the quantization limits.  Such a format is superior compared to simple rounding in therms of quantization errors
 *  as the below format preserves maximum number of bits from the original score.  The exact format of Harris score stored in outm[] is as follows:
 *  @verbatim

    Exponent = 7bit, Mantissa = 9 bit (eg. EEEE EEEM MMMM MMMMb)
                                            where E: Exponent bits, M: Mantissa bits
    @endverbatim
 *  The exponent corresponds to the location of the leading non-redundant sign-bit in the score (where the lsb is location = 1, and msb is location = 64).  The mantissa contains the
 *  relevant bits (9 bits) starting from the leading non-redundant sign bit.
 *  @par
 *  The exponent is 0 if the absolute value of the score is less than 2^9.  If the absolute value of the score is greater, (lmb - 9) is stored in the exponent for positive scores,
 *  and -(lmb - 9) is stored in the exponent for negative scores.  For example, a signed score of 571717286 (= 0010 0010 0001 0011 1011 0110 1010 0110b) will be encoded as =
 *  (30-9)*2^9 + (571717286)>>(30-9)=11024.
 *
 * @par Assumptions
 *  - Garbage may be written in the output margins, which are 3 pixels wide on each side. If the input gradient
 *  also has a margin of 1 pixel, then there is an overall output margin of 4 pixels.
 *  - This method uses a scratch buffer which must be at least 96 * \c width bytes.

 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
int32_t    VLIB_harrisScore_7x7(const int16_t gradX[restrict],
                                const int16_t gradY[restrict],
                                int32_t width,
                                int32_t height,
                                int16_t outm[restrict],
                                uint16_t k,
                                uint8_t buffer[]);

/** @} */

#endif /* VLIB_HARRISSCORE_7X7_ */

/* ======================================================================== */
/*  End of file:  VLIB_harrisScore_7x7.h                                    */
/* ======================================================================== */

