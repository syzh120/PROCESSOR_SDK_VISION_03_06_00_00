/******************************************************************************
Copyright (c) 2017 Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup  ALGORITHM_FUNCTION
 * \defgroup ALGORITHM_RADARPKDETECT  Peak Detection API
 *
 * \brief  This file contains plug in functions for radar Peak detection.
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file radarPkDetect_if.h
 *
 * \brief Algorithm Function for Radar peak detection.
 *
 * \version 0.0 (Jul 2017) : [PG] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_RADAR_PKDETECT_H_
#define ALGORITHM_LINK_RADAR_PKDETECT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/common/alg_functions.h>
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include "ipeak_detection_ti.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/** \brief Maximum possible transmit antennas */
#define RADAR_PKDETECT_MAX_TX (12U)

/** \brief Maximum possible recieve antennas */
#define RADAR_PKDETECT_MAX_RX (16U)

/** \brief Maximum possible detected Objects. Taking the worst case range
  *        and doppler dimension for this value.
  */
#define RADAR_PKDETECT_MAX_DETECTED_OBJS (8192U)

/** \brief Maximum possible number of profiles.
  */
#define RADAR_PKDETECT_MAX_NUM_PROFILE (4U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Peak Detecion
 *          algorithm.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_RadarProcessCreateParams baseClassCreateParams;
      /**< Base Class Create Parameters. This should be the first element
       *   of this structure.
       */
    UInt16       maxNumAntenna;
    /**< Maximum number of antennas in the system */
    UInt16       maxNumTx;
    /**< Maximum number of transmitter antennas in system */
    UInt16       maxRangeDimension;
    /**< Maximum range dimension */
    UInt16       maxDopplerDimension;
    /**< Maximum doppler dimension */
    UInt8        detectionMethod;
    /**< Method to be used for detection of objects. Refer
      *         PEAK_DETECTION_TI_METHOD to know the supported
      *         methods.
      */
    UInt8        enableAntennaDataOut;
    /**< If enabled the applet will extract the antenna data corresponding
      *         to the detection and returns as one of the output bufffer
      *         (PEAK_DETECTION_TI_BUFDESC_OUT_ANTENNA_DATA).
      */
    PEAK_DETECTION_TI_AlgoCreateParams algoCreateParams;
    /**< Algorithm specific create time parameter. For supported
      *         algorithms refer PEAK_DETECTION_TI_METHOD
      */
    PEAK_DETECTION_TI_CfarCaDbParams cfarCaDb;
    /**< Run time parameter to be used if detection method is
      *       PEAK_DETECTION_TI_METHOD_CFARCA_DB
      */
    UInt8        enableTxDecoding;
    /**< Enable/Disable Tx decoding. A value of 1 enables tx decoding */
    UInt16       numTx[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Current Number of transmitters in the system. */
    UInt16       numRx[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Number of receivers in the system. */
    Int16        txDecodingCoefficients[RADAR_PKDETECT_MAX_TX * RADAR_PKDETECT_MAX_TX];
    /**< Coefficients required for tx decoding. This is only
      *  required if enableTxDecoding = 1. This is a matrix of
      *  numTx X numTx elements. For Tx decoding data received at each
      *  transmitter is multiplied by Tx decoding matrix to decode individual.
      */
    UInt16       rangeDim[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Current Range Dimension */
    UInt16       dopplerDim[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Current doppler Dimension */
    UInt8        numProfiles;
    /**< Number of profiles supported */
}AlgorithmFxn_RadarPkDetectCreateParams;

typedef struct
{
    UInt16 dopplerIdx;
    /**< Doppler Index of the detected Object */
    UInt16 rangeIdx;
    /**< Range Index of the detected Object */
} AlgorithmFxn_RadarPkDetectObjIdx;

/**
 *******************************************************************************
 *
 *   \brief Structure is used to describe the buffers output params from
 *          the peak detection algorithm.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                           numDetections;
    /**< Number of detected objects */
    UInt32                           profileId;
    /**< Index of the profile for which the frame is generated */
    AlgorithmFxn_RadarPkDetectObjIdx objBuf[RADAR_PKDETECT_MAX_DETECTED_OBJS];
    /**< List of detected Objects */
    UInt16                           energyBuf[RADAR_PKDETECT_MAX_DETECTED_OBJS];
    /**< List of energy corresponding to each detected object */
    UInt32                           antData[
        RADAR_PKDETECT_MAX_DETECTED_OBJS * RADAR_PKDETECT_MAX_RX *
        RADAR_PKDETECT_MAX_TX];
    /**< List of antenna data corresponding to each detected object */
}AlgorithmFxn_RadarPkDetectBuffDescriptor;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Object Draw
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_RadarProcessControlParams baseClassControl;
    /**< Base class control parameters */
    PEAK_DETECTION_TI_CfarCaDbParams cfarCaDb;
    /**< Run time parameter to be used if detection method is
     *       PEAK_DETECTION_TI_METHOD_CFARCA_DB
     */
    UInt8        enableTxDecoding;
    /**< Enable/Disable Tx decoding. A value of 1 enables tx decoding */
    UInt16       numTx[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Number of transmitters in the system. */
    UInt16       numRx[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Number of receivers in the system. */
    Int8         txDecodingCoefficients[RADAR_PKDETECT_MAX_TX * RADAR_PKDETECT_MAX_TX];
    /**< Coefficients required for tx decoding. This is only
      *  required if enableTxDecoding = 1. This is a matrix of
      *  numTx X numTx elements. For Tx decoding data received at each
      *  transmitter is multiplied by Tx decoding matrix to decode individual.
      */
    UInt16       rangeDim[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Current Range Dimension */
    UInt16       dopplerDim[RADAR_PKDETECT_MAX_NUM_PROFILE];
    /**< Current doppler Dimension */
} AlgorithmFxn_RadarPkDetectControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarPkDetect_Init(
                                AlgorithmFxn_RadarPkDetectCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarPkDetect_Init(
    AlgorithmFxn_RadarPkDetectCreateParams *pPrm)
{
    /* MISRA.ONEDEFRULE.FUNC
     * MISRAC_2004 Rule 8.5
     * Function Definition in header file
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER: This function initializes the create time argument to default.
     *  Defining this in the header file aids maintainability.
     */
    /* Update the size of the parameter */
    pPrm->baseClassCreateParams.baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmFxn_RadarPkDetectCreateParams);
    strcpy(pPrm->baseClassCreateParams.algFxnName, "ti.radar.pkDetect");
    pPrm->maxNumAntenna = 12;
    pPrm->maxNumTx      = 3;
    pPrm->maxRangeDimension = 1024;
    pPrm->maxDopplerDimension = 128;
    pPrm->detectionMethod = PEAK_DETECTION_TI_METHOD_CFARCA_DB;
    pPrm->enableAntennaDataOut = 1;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of get functions for the algorithm functions
 *
 *        This function will be called to get the pointer to the table of
 *        functions which correspond to this algorithm.
 *
 * \return  AlgRadarProcessFxns_FxnTable pointer.
 *
 *******************************************************************************
 */
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarPkDetect_getFunctions(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
