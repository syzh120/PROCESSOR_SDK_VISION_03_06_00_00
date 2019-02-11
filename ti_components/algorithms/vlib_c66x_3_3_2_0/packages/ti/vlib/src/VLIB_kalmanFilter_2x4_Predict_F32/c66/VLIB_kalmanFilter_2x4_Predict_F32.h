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

#ifndef VLIB_KALMANFILTER2X4_PREDICT_F32_H_
#define VLIB_KALMANFILTER2X4_PREDICT_F32_H_ 1

/** @defgroup VLIB_kalmanFilter_2x4_Predict_F32 */
/** @ingroup  VLIB_kalmanFilter_2x4_Predict_F32 */
/* @{ */
/**
 * @par Description:
 * The state of the Kalman filter is defined using the following structure.
 * The expected bit precision for each matrix is noted in the comments.
 * The variable sD and mD represent the dimensionality of the state and
 * measurement vectors and have values of 4 and 2 respectively
 * @verbatim
  typedef struct VLIB_kalmanFilter_2x4_F32{
    VLIB_F32 transition[sD_2x4*sD_2x4];          // state transition matrix
    VLIB_F32 errorCov[sD_2x4*sD_2x4];            // a priori error covariance matrix
    VLIB_F32 predictedErrorCov[sD_2x4*sD_2x4];   //  predicted error covariance matrix
    VLIB_F32 state[sD_2x4];                      // state of the process
    VLIB_F32 predictedState[sD_2x4];             // predicted state of the process
    VLIB_F32 measurement[mD_2x4*sD_2x4];         // measurement matrix (relating state to measurement)
    VLIB_F32 processNoiseCov[sD_2x4*sD_2x4];     // process noise covariance matrix
    VLIB_F32 measurementNoiseCov[mD_2x4*mD_2x4]; // measurement noise covariance matrix
    VLIB_F32 kalmanGain[sD_2x4*mD_2x4];          // Kalman gain
    VLIB_F32 temp1[sD_2x4*sD_2x4];
    VLIB_F32 temp2[sD_2x4*sD_2x4];
    VLIB_F32 temp3[sD_2x4*sD_2x4];
} VLIB_kalmanFilter_2x4_F32;
@endverbatim
 * In VLIB_kalmanFilter_2x4_Predict_F32, input and output parameters are VLIB_F32 type
 * @par
 *    @param [in,out]  *KF        Pointer to struct VLIB_kalmanFilter_2x4_F32
 * @par Implementation Notes:
 *    - This code is compatible with C66x floating-point processors
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
void VLIB_kalmanFilter_2x4_Predict_F32(VLIB_kalmanFilter_2x4_F32 *KF);

/** @} */
#endif /* VLIB_KALMANFILTER2X4_F32_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_2x4_Predict_F32.h                       */
/* ======================================================================== */

