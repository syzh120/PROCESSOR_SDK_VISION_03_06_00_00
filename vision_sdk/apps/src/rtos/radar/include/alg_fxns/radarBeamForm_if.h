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
 * \defgroup ALGORITHM_RADARBEAMFORM  Beam Forming API
 *
 * \brief  This file contains plug in functions for radar Beam Forming.
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file radarBeamForm_if.h
 *
 * \brief Algorithm Function for Radar Beam Forming.
 *
 * \version 0.0 (Aug 2017) : [PG] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_RADAR_BEAMFORM_H_
#define ALGORITHM_LINK_RADAR_BEAMFORM_H_

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
#include "ibeam_forming_ti.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/** \brief Maximum possible transmit antennas */
#define RADAR_BEAMFORM_MAX_TX (12U)

/** \brief Maximum possible recieve antennas */
#define RADAR_BEAMFORM_MAX_RX (16U)

/** \brief Maximum possible detected Objects. Taking the worst case range
  *        and doppler dimension for this value.
  */
#define RADAR_BEAMFORM_MAX_DETECTED_OBJS (BEAM_FORMING_TI_MAX_NUM_DETECTIONS)

/** \brief Maximum possible number of profiles.
  */
#define RADAR_BEAMFORM_MAX_NUM_PROFILE (4U)

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
    UInt16                              maxNumAntenna;
    /**< Maximum number of antennas in the system */
    UInt16                              maxNumDetection;
    /**< Maximum number of detections. It is important to note that maximum
     *   number of detection supported is given by
     *   BEAM_FORMING_TI_MAX_NUM_DETECTIONS macro
     */
    UInt16                              maxNumAngle;
    /**< Maximum number of angles */
    UInt16                              coordinateBufFormat;
    /**< This enum is to select the type of format in which coordinate
     *   buffer(BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF) is given to this
     *   applet.
     */
    UInt16                              numAntennas[RADAR_BEAMFORM_MAX_NUM_PROFILE];
    /**< number of antennas. */
    UInt16                              numAngles;
    /**< number of angles/bin for beam forming */
    UInt16                              beamFormingScaling;
    /**< Scaling ( right shift with rounding) that needs to be applied after
     * doing compelx matrix multiplication for beam forming. Mathematically
     * if after complex multiplication either real/imaginary part is
     * x then final output would be equal to (x + 1 << (n - 1) ) >> n, where
     * n is the scaling factor.
     */
    UInt16                              energyScaling;
    /**< Scaling ( right shift with rounding) that needs to be applied after
     *   calculating the energy in 32 bit to convert it to 16 bit.
     *   Mathematically if after energy computation energy is x then final
     *   output would be equal to (x + 1 << (n - 1) ) >> n, where n is the
     *   scaling factor.
     */
    UInt8         *steeringBuf[RADAR_BEAMFORM_MAX_NUM_PROFILE];
    /**< Steering Matrix for Beam Forming */
}AlgorithmFxn_RadarBeamFormCreateParams;

typedef struct
{
  UInt16       velocity;
  /**< velocity or a particular detection. */
  UInt16       range;
  /**< Range dimension for a particular detection */
  UInt16       energy;
  /**< Energy calculated for a particular detection */
  UInt16       angleBin;
  /**< Bin number from the steering matrix corresponding to a particular
   *   detection. User is expected to do the mapping of bin to angle
   */
} AlgorithmFxn_RadarBeamFormObjIdx;

/**
 *******************************************************************************
 *
 *   \brief Structure is used to describe the buffers output params from
 *          the beam forming algorithm.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmFxn_RadarBeamFormObjIdx objBuf[RADAR_BEAMFORM_MAX_DETECTED_OBJS];
    /**< List of detected Objects */
    UInt16                           numDetections;
    /**< Number of detected objects */
    UInt32                           profileId;
    /**< Index of the profile for which the frame is generated */
}AlgorithmFxn_RadarBeamFormBuffDescriptor;

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
    UInt16       numAntennas[RADAR_BEAMFORM_MAX_NUM_PROFILE];
    /**< number of antennas. */
    UInt16       numAngles;
    /**< number of angles/bin for beam forming */
    UInt16       beamFormingScaling;
    /**< Scaling ( right shift with rounding) that needs to be applied after
     * doing compelx matrix multiplication for beam forming. Mathematically
     * if after complex multiplication either real/imaginary part is
     * x then final output would be equal to (x + 1 << (n - 1) ) >> n, where
     * n is the scaling factor.
     */
    UInt16       energyScaling;
    /**< Scaling ( right shift with rounding) that needs to be applied after
     *   calculating the energy in 32 bit to convert it to 16 bit.
     *   Mathematically if after energy computation energy is x then final
     *   output would be equal to (x + 1 << (n - 1) ) >> n, where n is the
     *   scaling factor.
     */
    UInt8*        steeringBuf[RADAR_BEAMFORM_MAX_NUM_PROFILE];
    /**< Steering Matrix for Beam Forming */
} AlgorithmFxn_RadarBeamFormControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarBeamForm_Init(
                                AlgorithmFxn_RadarBeamFormCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarBeamForm_Init(
    AlgorithmFxn_RadarBeamFormCreateParams *pPrm)
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
                                sizeof(AlgorithmFxn_RadarBeamFormCreateParams);
    strcpy(pPrm->baseClassCreateParams.algFxnName, "ti.radar.beamForm");
    pPrm->maxNumAntenna = 12;
    pPrm->maxNumDetection = RADAR_BEAMFORM_MAX_DETECTED_OBJS;
    pPrm->maxNumAngle = 19;
    pPrm->coordinateBufFormat = (UInt16) BEAM_FORMING_TI_COORDINATE_BUF_FORMAT_2;
    pPrm->numAntennas[0] = 4;
    pPrm->numAngles = 19;
    pPrm->beamFormingScaling = 1;
    pPrm->energyScaling = 1;
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
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarBeamForm_getFunctions(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
