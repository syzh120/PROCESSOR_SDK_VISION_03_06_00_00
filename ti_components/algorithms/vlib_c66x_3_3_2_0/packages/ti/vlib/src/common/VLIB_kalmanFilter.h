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

#ifndef VLIB_KALMANFILTER_H_
#define VLIB_KALMANFILTER_H_ 1

#define mD_1x2 (1)
#define sD_1x2 (2)

#define mD_2x4 (2)
#define sD_2x4 (4)

#define mD_4x6 (4)
#define sD_4x6 (6)

#define mD_4x8 (4)
#define sD_4x8 (8)

#define mD_4x12 (4)
#define sD_4x12 (12)

/*!
 * \brief Structure defining the state of the Kalman filter, 2x4 (2-Dimension Observation x 4-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_2x4 {
    int16_t transition[sD_2x4 * sD_2x4];          /*!< SQ15.0, state transition matrix, A */
    int16_t errorCov[sD_2x4 * sD_2x4];            /*!< SQ13.2, a priori error covariance matrix, P */
    int16_t predictedErrorCov[sD_2x4 * sD_2x4];   /*!< SQ13.2, predicted error covariance matrix, P1 */
    int16_t state[sD_2x4];                        /*!< SQ10.5, state of the process, X */
    int16_t predictedState[sD_2x4];               /*!< SQ10.5, predicted state of the process, X1 */
    int16_t measurement[mD_2x4 * sD_2x4];         /*!< SQ15.0, measurement matrix (relating state to measurement), H */
    int16_t processNoiseCov[sD_2x4 * sD_2x4];     /*!< SQ13.2, process noise covariance matrix, Q */
    int16_t measurementNoiseCov[mD_2x4 * mD_2x4]; /*!< SQ15.0, measurement noise covariance matrix, R */
    int16_t kalmanGain[sD_2x4 * mD_2x4];          /*!< SQ0.15, Kalman gain, K */
    int16_t temp1[sD_2x4 * sD_2x4];
    int16_t temp2[sD_2x4 * sD_2x4];
    int16_t temp3[sD_2x4 * sD_2x4];
} VLIB_kalmanFilter_2x4;


/*!
 * \brief Structure defining the state of the Kalman filter, 4x6 (4-Dimension Observation x 6-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_4x6 {
    int16_t transition[sD_4x6 * sD_4x6];          /*!< SQ15.0, state transition matrix, A */
    int16_t errorCov[sD_4x6 * sD_4x6];            /*!< SQ13.2, a priori error covariance matrix, P */
    int16_t predictedErrorCov[sD_4x6 * sD_4x6];   /*!< SQ13.2, predicted error covariance matrix, P1 */
    int16_t state[sD_4x6];                        /*!< SQ10.5, state of the process, X */
    int16_t predictedState[sD_4x6];               /*!< SQ10.5, predicted state of the process, X1 */
    int16_t measurement[mD_4x6 * sD_4x6];         /*!< SQ15.0, measurement matrix (relating state to measurement), H */
    int16_t processNoiseCov[sD_4x6 * sD_4x6];     /*!< SQ13.2, process noise covariance matrix, Q */
    int16_t measurementNoiseCov[mD_4x6 * mD_4x6]; /*!< SQ15.0, measurement noise covariance matrix, R */
    int16_t kalmanGain[sD_4x6 * mD_4x6];          /*!< SQ0.15, Kalman gain, K */
    int16_t temp1[sD_4x6 * sD_4x6];
    int16_t temp2[sD_4x6 * sD_4x6];
    int16_t temp3[sD_4x6 * sD_4x6];
    int32_t tempBuffers[mD_4x6 * mD_4x6 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VLIB_kalmanFilter_4x6;

/*!
 * \brief Structure defining the state of the Kalman filter for the S16_F32, 2x4 (2-Dimension Observation x 4-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_2x4_S16_F32 {
    VLIB_F32 transition[sD_2x4 * sD_2x4];          /*!< state transition matrix, A */
    VLIB_F32 errorCov[sD_2x4 * sD_2x4];            /*!< a priori error covariance matrix, P */
    VLIB_F32 predictedErrorCov[sD_2x4 * sD_2x4];   /*!< predicted error covariance matrix, P1 */
    int16_t  state[sD_2x4];                       /*!< state of the process, X */
    VLIB_F32 predictedState[sD_2x4];               /*!< predicted state of the process, X1 */
    VLIB_F32 measurement[mD_2x4 * sD_2x4];         /*!< measurement matrix (relating state to measurement), H */
    VLIB_F32 processNoiseCov[sD_2x4 * sD_2x4];     /*!< process noise covariance matrix, Q */
    VLIB_F32 measurementNoiseCov[mD_2x4 * mD_2x4]; /*!< measurement noise covariance matrix, R */
    VLIB_F32 kalmanGain[sD_2x4 * mD_2x4];          /*!< Kalman gain, K */
    VLIB_F32 temp1[sD_2x4 * sD_2x4];
    VLIB_F32 temp2[sD_2x4 * sD_2x4];
    VLIB_F32 temp3[sD_2x4 * sD_2x4];
} VLIB_kalmanFilter_2x4_S16_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the S16_F32, 4x6 (4-Dimension Observation x 6-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_4x6_S16_F32 {
    VLIB_F32 transition[sD_4x6 * sD_4x6];          /*!< state transition matrix, A */
    VLIB_F32 errorCov[sD_4x6 * sD_4x6];            /*!< a priori error covariance matrix, P */
    VLIB_F32 predictedErrorCov[sD_4x6 * sD_4x6];   /*!< predicted error covariance matrix, P1 */
    int16_t  state[sD_4x6];                       /*!< state of the process, X */
    VLIB_F32 predictedState[sD_4x6];               /*!< predicted state of the process, X1 */
    VLIB_F32 measurement[mD_4x6 * sD_4x6];         /*!< measurement matrix (relating state to measurement), H */
    VLIB_F32 processNoiseCov[sD_4x6 * sD_4x6];     /*!< process noise covariance matrix, Q */
    VLIB_F32 measurementNoiseCov[mD_4x6 * mD_4x6]; /*!< measurement noise covariance matrix, R */
    VLIB_F32 kalmanGain[sD_4x6 * mD_4x6];          /*!< Kalman gain, K */
    VLIB_F32 temp1[sD_4x6 * sD_4x6];
    VLIB_F32 temp2[sD_4x6 * sD_4x6];
    VLIB_F32 temp3[sD_4x6 * sD_4x6];
    VLIB_F32 tempBuffers[mD_4x6 * mD_4x6 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VLIB_kalmanFilter_4x6_S16_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 2x4 (2-Dimension Observation x 4-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_2x4_F32 {
    VLIB_F32 transition[sD_2x4 * sD_2x4];          /*!< state transition matrix, A*/
    VLIB_F32 errorCov[sD_2x4 * sD_2x4];            /*!< a priori error covariance matrix, P*/
    VLIB_F32 predictedErrorCov[sD_2x4 * sD_2x4];   /*!< predicted error covariance matrix, P1*/
    VLIB_F32 state[sD_2x4];                        /*!< state of the process, X*/
    VLIB_F32 predictedState[sD_2x4];               /*!< predicted state of the process, X1*/
    VLIB_F32 measurement[mD_2x4 * sD_2x4];         /*!< measurement matrix (relating state to measurement), H*/
    VLIB_F32 processNoiseCov[sD_2x4 * sD_2x4];     /*!< process noise covariance matrix, Q*/
    VLIB_F32 measurementNoiseCov[mD_2x4 * mD_2x4]; /*!< measurement noise covariance matrix, R*/
    VLIB_F32 kalmanGain[sD_2x4 * mD_2x4];          /*!< Kalman gain, K*/
    VLIB_F32 temp1[sD_2x4 * sD_2x4];
    VLIB_F32 temp2[sD_2x4 * sD_2x4];
    VLIB_F32 temp3[sD_2x4 * sD_2x4];
} VLIB_kalmanFilter_2x4_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x6 (4-Dimension Observation x 6-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_4x6_F32 {
    VLIB_F32 transition[sD_4x6 * sD_4x6];          /*!< state transition matrix, A*/
    VLIB_F32 errorCov[sD_4x6 * sD_4x6];            /*!< a priori error covariance matrix, P*/
    VLIB_F32 predictedErrorCov[sD_4x6 * sD_4x6];   /*!< predicted error covariance matrix, P1*/
    VLIB_F32 state[sD_4x6];                        /*!< state of the process, X*/
    VLIB_F32 predictedState[sD_4x6];               /*!< predicted state of the process, X1*/
    VLIB_F32 measurement[mD_4x6 * sD_4x6];         /*!< measurement matrix (relating state to measurement), H*/
    VLIB_F32 processNoiseCov[sD_4x6 * sD_4x6];     /*!< process noise covariance matrix, Q*/
    VLIB_F32 measurementNoiseCov[mD_4x6 * mD_4x6]; /*!< measurement noise covariance matrix, R*/
    VLIB_F32 kalmanGain[sD_4x6 * mD_4x6];          /*!< Kalman gain, K*/
    VLIB_F32 temp1[sD_4x6 * sD_4x6];
    VLIB_F32 temp2[sD_4x6 * sD_4x6];
    VLIB_F32 temp3[sD_4x6 * sD_4x6];
    int32_t  tempBuffers[mD_4x6 * mD_4x6 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VLIB_kalmanFilter_4x6_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x8 (4-Dimension Observation x 8-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_4x8_F32 {
    VLIB_F32 transition[sD_4x8 * sD_4x8];          /*!< state transition matrix, A*/
    VLIB_F32 errorCov[sD_4x8 * sD_4x8];            /*!< a priori error covariance matrix, P*/
    VLIB_F32 predictedErrorCov[sD_4x8 * sD_4x8];   /*!< predicted error covariance matrix, P1*/
    VLIB_F32 state[sD_4x8];                        /*!< state of the process, X*/
    VLIB_F32 predictedState[sD_4x8];               /*!< predicted state of the process, X1*/
    VLIB_F32 measurement[mD_4x8 * sD_4x8];         /*!< measurement matrix (relating state to measurement), H*/
    VLIB_F32 processNoiseCov[sD_4x8 * sD_4x8];     /*!< process noise covariance matrix, Q*/
    VLIB_F32 measurementNoiseCov[mD_4x8 * mD_4x8]; /*!< measurement noise covariance matrix, R*/
    VLIB_F32 kalmanGain[sD_4x8 * mD_4x8];          /*!< Kalman gain, K*/
    VLIB_F32 temp1[sD_4x8 * sD_4x8];
    VLIB_F32 temp2[sD_4x8 * sD_4x8];
    VLIB_F32 temp3[sD_4x8 * sD_4x8];
    int32_t  tempBuffers[mD_4x8 * mD_4x8 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VLIB_kalmanFilter_4x8_F32;


/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x12 (4-Dimension Observation x 12-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_4x12_F32 {
    VLIB_F32 transition[sD_4x12 * sD_4x12];          /*!< state transition matrix, A*/
    VLIB_F32 errorCov[sD_4x12 * sD_4x12];            /*!< a priori error covariance matrix, P*/
    VLIB_F32 predictedErrorCov[sD_4x12 * sD_4x12];   /*!< predicted error covariance matrix, P1*/
    VLIB_F32 state[sD_4x12];                        /*!< state of the process, X*/
    VLIB_F32 predictedState[sD_4x12];               /*!< predicted state of the process, X1*/
    VLIB_F32 measurement[mD_4x12 * sD_4x12];         /*!< measurement matrix (relating state to measurement), H*/
    VLIB_F32 processNoiseCov[sD_4x12 * sD_4x12];     /*!< process noise covariance matrix, Q*/
    VLIB_F32 measurementNoiseCov[mD_4x12 * mD_4x12]; /*!< measurement noise covariance matrix, R*/
    VLIB_F32 kalmanGain[sD_4x12 * mD_4x12];          /*!< Kalman gain, K*/
    VLIB_F32 temp1[sD_4x12 * sD_4x12];
    VLIB_F32 temp2[sD_4x12 * sD_4x12];
    VLIB_F32 temp3[sD_4x12 * sD_4x12];
    int32_t  tempBuffers[mD_4x12 * mD_4x12 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VLIB_kalmanFilter_4x12_F32;

/*!
 * \brief Structure defining the state of the Kalman filter for the F32, 4x12 (4-Dimension Observation x 12-Dimension State Vectors) variant
 */
typedef struct vlib_kalmanFilter_1x2_F32 {
    VLIB_F32 transition[sD_1x2 * sD_1x2];          /*!< state transition matrix, A*/
    VLIB_F32 errorCov[sD_1x2 * sD_1x2];            /*!< a priori error covariance matrix, P*/
    VLIB_F32 predictedErrorCov[sD_1x2 * sD_1x2];   /*!< predicted error covariance matrix, P1*/
    VLIB_F32 state[sD_1x2];                        /*!< state of the process, X*/
    VLIB_F32 predictedState[sD_1x2];               /*!< predicted state of the process, X1*/
    VLIB_F32 measurement[mD_1x2 * sD_1x2];         /*!< measurement matrix (relating state to measurement), H*/
    VLIB_F32 processNoiseCov[sD_1x2 * sD_1x2];     /*!< process noise covariance matrix, Q*/
    VLIB_F32 measurementNoiseCov[mD_1x2 * mD_1x2]; /*!< measurement noise covariance matrix, R*/
    VLIB_F32 kalmanGain[sD_1x2 * mD_1x2];          /*!< Kalman gain, K*/
    VLIB_F32 temp1[sD_1x2 * sD_1x2];
    VLIB_F32 temp2[sD_1x2 * sD_1x2];
    VLIB_F32 temp3[sD_1x2 * sD_1x2];
    int32_t  tempBuffers[mD_1x2 * mD_1x2 * 2];

    int32_t scaleFactor;   /*!< Scales the matrix M = (H*P1*H' + R) to ensure that its inverse does not overflow 32 bits.
                            The scaling is done by right shifting each element of M by the quantity assigned to scaleFactor.
                            The computed inverse is then scaled back to ensure the correct result based on the identity
                            inv(M) = inv(M/k)/k */

} VLIB_kalmanFilter_1x2_F32;
#endif

/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter.h                                       */
/* ======================================================================== */

