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

#ifndef VLIB_KALMANFILTER4X6_PREDICT_F32_H_
#define VLIB_KALMANFILTER4X6_PREDICT_F32_H_ 1

#include "../../common/VLIB_kalmanFilter.h"

/** @defgroup VLIB_kalmanFilter_4x6_Predict_F32 */
/** @ingroup  VLIB_kalmanFilter_4x6_Predict_F32 */
/* @{ */

/**
 * @par Description:
 * The state of the Kalman filter is defined using the following structure
 *(the expected bit precision for each matrix is noted in the comments).
 * The variable sD and mD represent the dimensionality of the state and
 * measurement vectors and have values of 6 and 4 respectively.
 * @verbatim
typedef struct VLIB_kalmanFilter_4x6_F32{

    VLIB_F32 transition[sD_4x6*sD_4x6];          // state transition matrix
    VLIB_F32 errorCov[sD_4x6*sD_4x6];            // a priori error covariance matrix
    VLIB_F32 predictedErrorCov[sD_4x6*sD_4x6];   // predicted error covariance matrix
    VLIB_F32 state[sD_4x6];                      //state of the process
    VLIB_F32 predictedState[sD_4x6];             // predicted state of the process
    VLIB_F32 measurement[mD_4x6*sD_4x6];         // measurement matrix (relating state to measurement)
    VLIB_F32 processNoiseCov[sD_4x6*sD_4x6];     // process noise covariance matrix
    VLIB_F32 measurementNoiseCov[mD_4x6*mD_4x6]; // measurement noise covariance matrix
    VLIB_F32 kalmanGain[sD_4x6*mD_4x6];          // Kalman gain
    VLIB_F32 temp1[sD_4x6*sD_4x6];
    VLIB_F32 temp2[sD_4x6*sD_4x6];
    VLIB_F32 temp3[sD_4x6*sD_4x6];
    int32_t tempBuffers[mD_4x6*mD_4x6*2];
    int32_t scaleFactor;
    // Scales the matrix M = (H*P1*H' + R) to ensure that its inverse
    //  does not overflow 32 bits.
    //  The scaling is done by right shifting each element of M by the
    // quantity assigned to scaleFactor.
    //  The computed inverse is then scaled back to ensure the correct result
    //  based on the identity inv(M) = inv(M/k)/k
} VLIB_kalmanFilter_4x6_F32;
@endverbatim
 * In VLIB_kalmanFilter_4x6_Predict_F32, input and output are VLIB_F32 type
 *
 * @par
 *    @param [in,out]  *KF        Pointer to struct VLIB_kalmanFilter_4x6_F32
 * @par Implementation Notes:
 *    - This code is compatible with C66x floating-point processors
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

void VLIB_kalmanFilter_4x6_Predict_F32(VLIB_kalmanFilter_4x6_F32 *KF);

#endif
/** @} */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_4x6_Predict_F32.h                       */
/* ======================================================================== */

