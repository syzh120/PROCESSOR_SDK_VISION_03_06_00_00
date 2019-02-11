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

#ifndef VLIB_KALMANFILTER2X4_PREDICT_H_
#define VLIB_KALMANFILTER2X4_PREDICT_H_ 1

/** @defgroup VLIB_kalmanFilter_2x4_Predict */
/** @ingroup  VLIB_kalmanFilter_2x4_Predict */
/* @{ */

/**
 * @par Description:
 * The state of the Kalman filter is defined using the following structure.
 * The expected bit precision for each matrix is noted in the comments.
 * The variable sD and mD represent the dimensionality of the state and
 * measurement vectors and have values of 4 and 2 respectively
 * @verbatim
    typedef struct VLIB_kalmanFilter_2x4{
    int16_t transition[sD*sD];            // SQ15.0, state transition matrix
    int16_t errorCov[sD*sD];              // SQ13.2, a priori error covariance matrix
    int16_t predictedErrorCov[sD*sD];     // SQ13.2, predicted error cov matrix
    int16_t state[sD];                    // SQ10.5, state of the process
    int16_t predictedState[sD];           // SQ10.5, predicted state of the process
    int16_t measurement[mD*sD];           // SQ15.0, measurement matrix
    int16_t processNoiseCov[sD*sD];       // SQ13.2, process noise cov matrix
    int16_t measurementNoiseCov[mD*mD];   // SQ15.0, measurement noise cov
    int16_t kalmanGain[sD*mD];            // SQ0.15, Kalman gain
    int16_t temp1[sD*sD];
    int16_t temp2[sD*sD];
    int16_t temp3[sD*sD];
    }VLIB_kalmanFilter_2x4;
  @endverbatim
 *  In VLIB_kalmanFilter_2x4_Predict, input and output parameters are int16_t type
 * @par
 *    @param [in,out]  *KF        Pointer to struct VLIB_kalmanFilter_2x4
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_kalmanFilter.h"

void VLIB_kalmanFilter_2x4_Predict(VLIB_kalmanFilter_2x4 *KF);

#endif /* VLIB_KALMANFILTER2X4_PREDICT_H_ */
/** @} */
/* ======================================================================== */
/*  End of file:  VLIB_kalmanFilter_2x4_Predict.h                           */
/* ======================================================================== */

