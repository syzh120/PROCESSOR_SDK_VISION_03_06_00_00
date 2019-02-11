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

#ifndef VLIB_KALMANFILTER4X6_CORRECT_H_
#define VLIB_KALMANFILTER4X6_CORRECT_H_ 1

/** @defgroup VLIB_kalmanFilter_4x6_Correct */
/** @ingroup  VLIB_kalmanFilter_4x6_Correct */
/* @{ */

/**
 * @par Description:
 * The state of the Kalman filter is defined using the following structure
 *(the expected bit precision for each matrix is noted in the comments).
 * The variable sD and mD represent the dimensionality of the state and
 * measurement vectors and have values of 6 and 4 respectively.
 * @verbatim
  typedef struct VLIB_kalmanFilter_4x6 {
   int16_t transition[sD_4x6*sD_4x6];            // state transition matrix
   int16_t errorCov[sD_4x6*sD_4x6];              // a priori error covariance matrix
   int16_t predictedErrorCov[sD_4x6*sD_4x6];     // predicted error covariance matrix
   int16_t state[sD_4x6];                        // state of the process
   int16_t predictedState[sD_4x6];               // predicted state of the process
   int16_t measurement[mD_4x6*sD_4x6];           // measurement matrix (relating state to measurement)
   int16_t processNoiseCov[sD_4x6*sD_4x6];       // process noise covariance matrix
   int16_t measurementNoiseCov[mD_4x6*mD_4x6];   // measurement noise covariance matrix
   int16_t kalmanGain[sD_4x6*mD_4x6];            // Kalman gain, K
   int16_t temp1[sD_4x6*sD_4x6];
   int16_t temp2[sD_4x6*sD_4x6];
   int16_t temp3[sD_4x6*sD_4x6];
   int16_t tempBuffers[mD_4x6*mD_4x6*2];
   int32_t scaleFactor;                    // Scales the matrix M = (H*P1*H' + R)
                                       //to ensure that its inverse does not overflow 32 bits.
   }VLIB_kalmanFilter_4x6;
@endverbatim
 * In VLIB_kalmanFilter_4x6_Correct, input and output are int16_t type
 *
 * @par
 *    @param [in,out] *KF        Pointer to struct VLIB_kalmanFilter_4x6
 *    @param [in]     *Z         Pointer to array (dimension 4x1) containing measurement  (SQ10.5)
 *    @param [out]    *Residual  Pointer to array to store the residual error             (SQ10.5)
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_kalmanFilter.h"

void VLIB_kalmanFilter_4x6_Correct(VLIB_kalmanFilter_4x6 *KF,
                                   const int16_t *restrict Z,
                                   int16_t *restrict Residual);
/** @} */
#endif /* VLIB_KALMANFILTER4X6_CORRECT_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_4x6_Correct.h                           */
/* ======================================================================== */

