/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
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
 * \defgroup ALGORITHM_RADARDSPPROCESS  DSP based Radar Processing
 *
 * \brief  This file contains plug in functions for radar processing on the DSP.
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file radarDspProcess_if.h
 *
 * \brief This file contains plug in functions for radar processing on the DSP.
 *
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_RADAR_DSP_PROCESS_H_
#define ALGORITHM_LINK_RADAR_DSP_PROCESS_H_

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

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ALGORITHM_FXN_RADAR_DSP_PROCESS_CMD_CHANGE_GUI          (0x1015U)
/**< Command ID for changing the GUI Parameters */

#define ALGORITHM_FXN_RADAR_DSP_PROCESS_CMD_RUN_CALIBRATION     (0x1016U)
/**< Command to run the calibration operation */

/**  \brief Maximum Number of channels supported.
 *   Channels here is used to capture the number of input channels connected to
 *   this algorithm function.
 */
#define ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_CHANNELS            (4U)

/**  \brief Maximum number of Radars per channel.
 *   This parameter is used to see how many Radars are connected per
 *   channel.
 */
#define ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_RADAR_SENSOR        (4U)

/**  \brief Maximum number of profiles */
#define ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE             (4U)

/**  \brief Maximum Number of virtual antennas. This is calculated as
 *          Number of sensors x Number of Tx Antennas x Number of Rx Antennas.
 */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA             (192U)

/**  \brief Maximum Number of Trasmit Antennas = Num Sensors * 3U */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_NUM_TX_ANTENNA           (12U)

/**  \brief Maximum Number of the Range Bins */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_RANGEBINS                (256U)

/**  \brief Maximum Number of the Doppler Bins */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_DOPPLERBINS              (256U)

/**  \brief Maximum Number of the Doppler Bins */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_DOPPLERBINS              (256U)

/**  \brief Maximum Number Objects that can be detected by the
 *          Algorithm Functions.
 */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS                  (400U)

/**  \brief Maximum number of azimuth FFTs */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_AZIMUTH_FFT              (4U)

/**  \brief Maximum number of overlapped antenna pairs */
#define ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OVERLAPPED_ANTENNA_PAIRS (32U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
/** \brief   Enum for CFAR types. */
typedef enum
{
    ALG_FXN_RADAR_DSP_PROCESS_CFAR_CA = 0U,
    /**< CA-CFAR type: cell average*/
    ALG_FXN_RADAR_DSP_PROCESS_CFAR_CAGO = 1U,
    /**< CA-CFAR type: greater of two side noise variances*/
    ALG_FXN_RADAR_DSP_PROCESS_CFAR_CASO = 2U,
    /**< CA-CFAR type: smaller of two side noise variances*/
    ALG_FXN_RADAR_DSP_PROCESS_CFAR_CACC = 3U
    /**< CA-CFAR type: cell accumulation*/
} AlgFxn_RadarDspProcessCaCfarType;

/**
 * \brief Enumeration for the types of the DSP Processing output.
 */
typedef enum
{
    ALGORITHMFXN_RADAR_DSP_PROCESS_OP_DETECTED_POINTS = 1U,
    /**< Detected output Points */
    ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_PROFILE   = 2U,
    /**< Range Profile Output */
    ALGORITHMFXN_RADAR_DSP_PROCESS_OP_AZIMUT_STATIC_HEAT_MAP = 3U,
    /**< Azimuth Static Heat Map */
    ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_DOPPLER_HEAT_MAP = 4U,
    /**< Range Doppler Heat Map */
    ALGORITHMFXN_RADAR_DSP_PROCESS_OP_SYSTEM_INFO = 5U,
    /**< System Information Section */
    ALGORITHMFXN_RADAR_DSP_PROCESS_OP_CALIBRATION_COEFFS = 6U
    /**< Calibration Coefficients */
} AlgorithmFxn_RadarDspProcessOpSectionType;

/**
 *  \brief   Enumeration for Angle of Arrival calibration state
 */
typedef enum
{
    ALGORITHMFXN_RADAR_DSP_PROCESS_NORMAL_RUNNING,
    /**< Normal running state */
    ALGORITHMFXN_RADAR_DSP_PROCESS_CALIBRATION
    /**< Calibration statte */
} AlgorithmFxn_RadarDspProcessCalibState;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 * \brief Complex Number Definition.
 */
typedef struct
{
    float imag;
    /**< Floating point Imaginary Numbers */
    float real;
    /**< Floating point real numbers */
} AlgorithmFxn_RadarDspProcessComplexNum;

/**
 * \brief 16 Bit Complex Number Definition.
 */
typedef struct
{
    Int16 imag;
    /**< 16 bit Imaginary Numbers */
    Int16 real;
    /**< 16 bit real numbers */
} AlgorithmFxn_RadarDspProcessComplexNum16bit;

/**
 * \brief
 *  Structure containing create time parameters for every channel input to the
 *  Radar DSP Processing Algorithm Function.
 */
typedef struct
{
    UInt8        numSensorDevPerChannel;
    /**< This parameter is used to see how many Radars are connected per
     *   channel.
     *   For the single chip multi-radar (Satellite) case this number is
     *   One.
     *   For the cascade case where there is a single channel and multiple
     *   Radar AWR devices, the value to be populated is equal to the number
     *   of Radars in cascade.
     */
    UInt8        numProfiles;
    /**< Number of profiles to be supported during creation */
    UInt16       numAdcSamples[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Number of ADC samples per chirp. A single radar device can have
     *   multiple profiles. Hence this is an array of maximum number of
     *   profiles. For the cascade scenario where there is a single channel
     *   but multiple radars the radar sensors share a single profile for
     *   coherence. Hence this is not a multi-dimentional array.
     */
    UInt16       numChirpLoops[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Number of chirp loops. A single radar device can have
     *   multiple subframes corresponding to each profile.
     *   Sub frames and profiles are considered equivalent to make sure the
     *   processing chain can understand which subframe is being sent.
     *   Hence this is an array of maximum number of profiles.
     *   For the cascade scenario where there is a single channel
     *   but multiple radars the radar sensors share a single profile for
     *   coherence. Hence this is not a multi-dimentional array.
     */
    UInt8        numTxAnt
        [ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_RADAR_SENSOR]
        [ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Number of Transmit Antennas per radar sensor. This can change
     *   accross sensors and accross subframes/profiles. Hence this is a 2
     *   dimentional array.
     */
    UInt8        numRxAnt
        [ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_RADAR_SENSOR]
        [ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Number of Recieved Antennas per radar sensor This can change
     *   accross sensors and accross subframes/profiles. Hence this is a 2
     *   dimentional array.
     */
    float       rangeRes[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Range Resolution for each profile */
    float       dopplerRes[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Doppler Resolution for each profile */
} AlgorithmFxn_RadarDspProcChCreateParams;

/**
 * \brief
 *  Structure containing create time parameters for DSP based Radar CFAR
 *  Processing.
 *
 */
typedef struct
{
    AlgFxn_RadarDspProcessCaCfarType  cfarType;
    /**< Type of CFAR.*/
    float        pfa;
    /**< Desired false detection ratio.*/
    float        K0;
    /**< Relative detection threshold. If K0 is non-zero value, pfa setting
     *   will be ignored.*/
    float        dopplerSearchRelThr;
    /**< Doppler search relative threshold.*/
    UInt8      enableSecondPassSearch;
    /**< Flag for enabling second pass search, if set to 1. If set to 0,
     *   no second pass search*/
    UInt8      searchWinSizeRange;
    /**< Search window size for range domain search.*/
    UInt8      guardSizeRange;
    /**< Number of guard samples for range domain search.*/
    UInt8      searchWinSizeDoppler;
    /**< Search window size for Doppler domain search.*/
    UInt8      guardSizeDoppler;
    /**< Number of guard samples for Doppler domain search.*/
    UInt8      maxNumDetObj;
    /**< maximum number of detected obj.*/
    UInt8      leftSkipSize;
    /**< number of samples to be skipped on the left side in range domain. */
    UInt8      rightSkipSize;
    /**< number of samples to be skipped on the right side in range domain. */
    UInt8      leftSkipSizeAzimuth;
    /**< number of samples to be skipped on the left side in azimuth domain. */
    UInt8      rightSkipSizeAzimuth;
    /**< number of samples to be skipped on the right side in azimuth domain. */
    UInt32     log2MagFlag;
    /**<use log2(mag) as input*/
} AlgorithmFxn_RadarDspProcCfarCreateParams;

/** \brief Calibration Control Parameters. */
typedef struct
{
    UInt32 state;
    /**< Requested state of the calibration parameters */
    UInt32 numFrames;
    /**< Number of frames for which to perform calibration */
    UInt32 refTargetRangeWindowStart;
    /**< Reference Target Range Window start index */
    UInt32 refTargetRangeWindowEnd;
    /**< Reference Target Range Window stop index */
} AlgorithmFxn_RadarDspProcessCalibParams;

/** \brief Controlling the output for debug GUI Parameters. */
typedef struct
{
    UInt8 pointCloud;
    /**< 1 - Enable showing point cloud. 0 - Disable */
    UInt8 rangeProfile;
    /**< 1 - Enable showing range profile. 0 - Disable */
    UInt8 noiseProfile;
    /**< 1 - Enable showing noise profile. 0 - Disable */
    UInt8 rangeDopHeatMap;
    /**< 1 - Enable showing Range and doppler heat map. 0 - Disable */
    UInt8 azimuthHeatMap;
    /**< 1 - Enable showing azimuth heat map. 0 - Disable */
} AlgorithmFxn_RadarDspProcessOpBlobControlParams;

/**
 * \brief
 *  Structure containing create time parameters for DSP based Radar AoA
 *  Processing.
 *
 */
typedef struct
{
    UInt16       rxAngleIndxLUT
        [ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA];
    /**< Forward LUT azimuth FFT input position */
    UInt16       rxRowIndxLUT
        [ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA];
    /**< Elevation row, not the elevation FFT input position */
    UInt16       rxRowToElevIdxLUT
        [ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_AZIMUTH_FFT];
    UInt16       rxMainRowIndex;
    /**< azimuth FFT output row in which the maximums are search */
    UInt16       azimuthFFTsize;
    /**< Azimuth FFT size */
    UInt16       numAzimuthFFTs;
    /**< Number of azimuth FFTs per detected Range/Doppler point */
    UInt16       elevationFFTsize;
    /**< Elevation FFT Size */
    float        multiPeakThresholdScale;
    /**< Threshold for multiple peak detection */
    UInt32       enableClutterRemoval;
    /**< Enabling flag for clutter removal. */
    UInt32       enableExtendedMaxVelocity;
    /**< Enabling flag for max velocity */
    AlgorithmFxn_RadarDspProcessComplexNum rxChPhaseComp
        [ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA];
    /**< Phase Compensation for the recieve antennas */
    UInt32       overlapAntennaPairs[
        ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OVERLAPPED_ANTENNA_PAIRS];
    /**< Overlapped Antenna Pairs */
    UInt32       numOverlapAntennaPairs;
    /**< Number of overlapped antenna pairs */
    AlgorithmFxn_RadarDspProcessCalibParams calibParams;
    /**< Calibration parameters */
} AlgorithmFxn_RadarDspProcAoaCreateParams;

/**
 * \brief
 *  Structure containing create time parameters for DSP based Radar Processing.
 *
 * \details
 *  The structure is used to define DSP Based Radar Processing params.
 *
 */
typedef struct
{
    AlgorithmLink_RadarProcessCreateParams baseClassCreateParams;
    /**< Base Class Create Parameters. This should be the first element
     *   of this structure.
     */
    UInt32       inputBufferType;
    /**< This flag is used to indicate the buffer input type to be used
     *   This is added to support DSP processing for single channel, multi
     *   channel, cascade configurations.
     *   The valid supported types are
     *   - SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER: for cascade Radar
     *   where the object detection is done for all Radar Devices together.
     *   - SYSTEM_BUFFER_TYPE_VIDEO_FRAME for the satellite/single chip
     *   Radar case where each individual Radar data processing chain is
     *   independent.
     */
    UInt32       numChannels;
    /**< This parameter is used to capture the number of channels connected.
     *   In the case of a single chip multi-radar (Satellite) case where there
     *   are multiple radar channles but each having one AWR1243 this
     *   numChannels is equal to the number of Radars.
     *   In the cascade case where there are multiple Radars but they are
     *   processed together as a single channel this number should be set as
     *   one.
     */
    UInt32       enableClutterRemoval;
    /**< This flag will enable (1) or disable (0) the operation step of
     *   clutter removal after the windowing operation before the 2D FFT is
     *   performed.
     */
    UInt32       skipDopplerFft;
    /**< This flag will skip (1) or perform (0) the Doppler FFT calculation step */
    AlgorithmFxn_RadarDspProcChCreateParams    chCreateParams[
        ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_CHANNELS];
    /**< Parameter for each Channel create to the Algorithm Function */
    AlgorithmFxn_RadarDspProcCfarCreateParams  cfarCreateParams;
    /**< Create parameters for the CFAR DSP Processing */
    AlgorithmFxn_RadarDspProcAoaCreateParams   aoaCreateParams;
    /**< Angle of arrival processing create parameters */
    AlgorithmFxn_RadarDspProcessOpBlobControlParams opControlParams;
    /**< Controls the output in the output blob */
} AlgorithmFxn_RadarDspProcessCreateParams;

/**
 * \brief Output Header format for the output of the Radar DSP Process.
 */
typedef struct
{
    UInt16        syncWord[4U];
    /**< Synchronization pattern at the beginning of the header */
    UInt32        frameId;
    /**< Index of the frame which is sent */
    UInt32        dspId;
    /**< DSP Core Id which has processed this frame */
    UInt32        numSections;
    /**< Number of Sections of the output */
    UInt32        totalOutputSize;
    /**< Size of the current frame output in Bytes */
    UInt32        objectCount;
    /**< Number of Objects Detected */
} AlgorithmFxn_RadarDspProcessOutputHeader;

/**
 *  \brief   Structure contains section header for the different output sections
 *           of the Radar DSP Processing.
 */
typedef struct
{
    UInt32  sectionType;
    /**< Section Type. Refer #AlgorithmFxn_RadarDspProcessOpSectionType for
     *   valid values.
     */
    UInt32  sectionLength;
    /**< Length of the individual section */
} AlgorithmFxn_RadarDspProcessOpSectionHdr;

/**
 *  \brief   Structure contains point information for detected objects
 */
typedef struct {
    Int16          rangeInd;
    /**< Range Index of the detected object */
    Int16          dopplerInd;
    /**< Doppler Index of the detected object */
    Int16          azimuthAngleInd;
    /**< Azimuth Angle Index of the detected object */
    Int16          elevationAngleInd;
    /**< Elevation Angle Index of the detected Object */
    float          range;
    /**< Range of the detected object */
    float          doppler;
    /**< Doppler of the detected object */
    float          azimuthAngle;
    /**< Azimuth Angle of the detected object */
    float          elevationAngle;
    /**< Elevation Angle of the detected object */
    float          snr;
    /**< Signal to noise ratio of the object */
    float          rangeVar;
    /**< Range Variation of the detected object */
    float          dopplerVar;
    /**< Doppler Variation of the detected object */
    float          azimAngleVar;
    /**< Azimuth Angle Variation of the detected object */
    float          elevAngleVar;
    /**< Elevation Angle Variation of the detected object */
} AlgorithmFxn_RadarDspProcessOpCloudPoint;

/**
 *  \brief   Output System Information which is available as the output of this
 *           Radar DSP Processing.
 */
typedef struct
{
    float        rangeRes;
    /**< Range resolution.*/
    float        dopplerRes;
    /**< Doppler resolution.*/
    UInt16       numRangeBins;
    /**< Number of Range Bins in the given Radar Frame */
    UInt16       numDopplerBins;
    /**< Number of Doppler Bins in the given Radar Frame */
    UInt8        numSensors;
    /**< Number of sensors which are in the current channel */
    UInt8        numTxAnt;
    /**< Number of Transmit antennas per Radar Sensor */
    UInt8        numRxAnt;
    /**< Number of Recieve antennas per Radar Sensor */
    UInt8        numTxAzimuthAnt;
    /**< Number of the Azimuth Transmit Antennas */
    UInt8        numTxElevationAnt;
    /**< Number of the Elevation Transmit Antennas */
    UInt8        padding[3U];
    /**< Reserved Entries to ensure 32 bit alignment */
} AlgorithmFxn_RadarDspProcessOpSystemInfo;

/** \brief Output Data Structure of the Radar DSP Processing */
typedef struct
{
    AlgorithmFxn_RadarDspProcessOutputHeader opHdr;
    /**< Output header describing the current frame of the output of the
     *   DSP Processing.
     */
    UInt8 opBlob [
        /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_SYSTEM_INFO */
        sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr) +
            sizeof (AlgorithmFxn_RadarDspProcessOpSystemInfo) +
        /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_CALIBRATION_COEFFS */
        sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr) +
            (sizeof(AlgorithmFxn_RadarDspProcessComplexNum) *
            ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA) +
        /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_PROFILE */
        sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr) +
            (sizeof(float) * ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_RANGEBINS) +
        /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_DOPPLER_HEAT_MAP */
        sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr) +
            (sizeof(float) * ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_RANGEBINS *
            ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_DOPPLERBINS) +
        /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_AZIMUT_STATIC_HEAT_MAP */
        sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr) +
            (sizeof(float) * 2U * ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_RANGEBINS *
            ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA) +
        /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_DETECTED_POINTS */
        sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr) +
            (sizeof(AlgorithmFxn_RadarDspProcessOpCloudPoint) *
            ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS)
        ];
    /**< Output blob which contains the output data */
} AlgorithmFxn_RadarDspProcessOutput;

/**
 * \brief Structure containing control parameters for Cascade
 */
typedef struct
{
    AlgorithmLink_RadarProcessControlParams baseClassControl;
    /**< Base class control parameters */
    AlgorithmFxn_RadarDspProcessCalibParams calibParams;
    /**< Calibration parameters */
    AlgorithmFxn_RadarDspProcessOpBlobControlParams opControlParams;
    /**< Controls the output in the output blob */
    UInt32 dspControlCmd;
    /**< Control command for DSP processing */
} AlgorithmFxn_RadarDspProcessControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarDspProcess_Init(
    AlgorithmFxn_RadarDspProcessCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarDspProcess_Init(
    AlgorithmFxn_RadarDspProcessCreateParams *pPrm)
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
                                sizeof(AlgorithmFxn_RadarDspProcessCreateParams);
    strcpy(pPrm->baseClassCreateParams.algFxnName, "ti.radar.dspprocess");
    pPrm->baseClassCreateParams.numOutputBuffers = 3;
    pPrm->skipDopplerFft = 0U;
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
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDspProcess_getFunctions(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
