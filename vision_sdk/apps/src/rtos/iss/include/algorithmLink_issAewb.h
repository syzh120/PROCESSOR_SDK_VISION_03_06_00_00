/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

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
 * \ingroup  ALGORITHM_LINK_PLUGIN
 * \defgroup ALGORITHM_LINK_ISS_AEWB  ISS AEWB API
 *
 * \brief  This module has the interface for using ISS AEWB algorithm
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_issAewb.h
 *
 * \brief Algorithm Link API specific to ISS AEWB algorithm
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_ISS_AEWB_H_
#define ALGORITHM_LINK_ISS_AEWB_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* Max number of H3A Planes/buffers and thus output parameters supported */
#define ALGORITHM_AEWB1_MAX_PLANES              (2U)

/* Maximum number of dynamic parameter configuration supported
   for Auto Exposure Algorithm */
#define ALGORITHM_AEWB1_MAX_AE_DYN_PARAMS       (10U)

/* maximal number of reference 1, actual use 17 */
#define ALGORITHM_AEWB1_MAX_REF1        (30U)

/* maximal number of reference 2, actual use 7 */
#define ALGORITHM_AEWB1_MAX_REF2        (15U)

/* maximal number of gray 2 used, actual use 4 */
#define ALGORITHM_AEWB1_MAX_GRAY        (4U)

/* DCC input buffer Size */
#define ALGORITHM_AEWB1_DCC_IN_BUF_SIZE (128U*1024U)

/**
    \ingroup LINK_API_CMD
    \addtogroup ALGORITHM_AEWB_LINK_API_CMD  ISS AEWB Control Commands

    @{
*/

/**
 *******************************************************************************
 * \brief Link CMD: Command to set the Auto Exposure Dynamic Params
 *
 *   \param AlgorithmLink_IssAewbAeDynamicParams *pPrm [IN] AE Dynamic Parameters.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_AEWB_LINK_CMD_SET_AE_DYNAMIC_PARAMS   (0x1000)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set AWB Calibration Data
 *
 *   \param AlgorithmLink_IssAewbAwbCalbData *pPrm [IN] AWB Calibration Parameters.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_AEWB_LINK_CMD_SET_AWB_CALB_DATA       (0x1001)

/**
 *******************************************************************************
 * \brief Link CMD: Command to parse DCC bin file and set parameters in ISP
 *
 *   \param AlgorithmLink_IssAewbDccParams *pPrm [IN] DCC Parameters,
 *          contains pointer to DCC file and size of the DCC file.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_AEWB_LINK_CMD_PARSE_AND_SET_DCC_PARAMS (0x1002)

/**
 *******************************************************************************
 * \brief Link CMD: Command to get the DCC buffer parameters
 *        Used by the network tool kit to get the DCC input buffer, where
 *        DCC bin file is stored.
 *
 *   \param AlgorithmLink_IssAewbDccParams *pPrm [IN] DCC Parameters,
 *          contains pointer to DCC file and size of the DCC file.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_AEWB_LINK_CMD_GET_DCC_BUF_PARAMS (0x1003)

/**
 *******************************************************************************
 * \brief Link CMD: Command to set DCC camera Information
 *        Used for setting up DCC camera Information like camera ID
 *
 *   \param AlgorithmLink_IssAewbDccCameraInfo *pPrm [IN] DCC Parameters,
 *          contains pointer to Dcc Camera id.
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_AEWB_LINK_CMD_SET_CAMERA_INFO    (0x1004)

/**
 *******************************************************************************
 * \brief Link CMD: Command to get 2A Parameters
 *                  Used for setting AE/AWB manual or Auto mode.
 *                  When in manual mode, fixed output parameters for AE/AWB
 *                  can be specified.
 *
 *        This ioctl can be used only if AEWB is enabled at create time
 *
 *   \param AlgorithmLink_IssAewb2AParams *pPrm [IN] 2A Parameters
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_AEWB_LINK_CMD_SET_2A_PARAMS      (0x1005)

/**
 *******************************************************************************
 * \brief Link CMD: Command to get 2A Parameters
 *
 *  This ioctl can be used only if AEWB is enabled at create time
 *
 *   \param AlgorithmLink_IssAewb2AParams *pPrm [OUT] 2A Parameters
 *
 *   Supported only on TDA3xx Iss UseCase
 *
 *******************************************************************************
*/
#define ALGORITHM_AEWB_LINK_CMD_GET_2A_PARAMS      (0x1006)

/* @} */


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct AlgorithmLink_IssAewbOutParams_t AlgorithmLink_IssAewbOutParams;

/*******************************************************************************
 *  \brief Algorithm Callback function
 *******************************************************************************
 */

/**< Callback function for applying AEWB output to the ISP */
typedef Void (*AlgorithmLink_IssAewbConfig) (
    AlgorithmLink_IssAewbOutParams *algoOutPrms, Ptr pIspCfgPrms,
    Void *appData);

/**< Callback function for applying ISP Configuration.
     Used only when DCC profile is provided over network.
     The first pointer #pIspCfgPrms points to the
     #IssIspConfigurationParameters and second pointer #pSimcopCfgPrm
     points to the #IssM2mSimcopLink_ConfigParams,
     Keeping them Void * to make this header file independent of ISP/Simcop
     Drv data structures */
typedef Void (*AlgorithmLink_IssAewbDccUpdate) (
    Ptr pIspCfgPrms, Ptr pSimcopCfgPrm, Void *appData);

/*******************************************************************************
 *  \brief AEWB Algorithm Mode
 *******************************************************************************
 */
typedef enum {
    ALGORITHMS_ISS_AEWB_MODE_AWB        = 0,
    /**< Auto White Balance Mode only */
    ALGORITHMS_ISS_AEWB_MODE_AE         = 1,
    /**< Auto Exposure Mode only */
    ALGORITHMS_ISS_AEWB_MODE_AEWB       = 2,
    /**< Auto Exposure and Auto White Balance Mode */
    ALGORITHMS_ISS_AEWB_MODE_NONE       = 3,
    /**< None of AEWB Mode,
         Used when DCC Functionality is required, but not AEWB
         Also used when AEWB is dynamically enabled/disabled using DCC */
    ALGORITHMS_ISS_AEWB_MODE_MAX        = 4,
    /**< Max mode value, used for error checking */
    ALGORITHMS_ISS_AEWB_MODE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmLink_IssAewbMode;

/*******************************************************************************
 *  \brief H3A params that are used by ISP
 *******************************************************************************
 */
typedef struct {

    UInt32 winCountH;
    /**< Number of H3A windows in H-direction */
    UInt32 winCountV;
    /**< Number of H3A windows in V-direction */
    UInt32 winSizeH;
    /**< Width of each H3A window in H-direction */
    UInt32 winSizeV;
    /**< Height of each H3A window in H-direction */
    UInt32 winSkipH;
    /**< Number of pixels skipped inside each H3A window in H-direction */
    UInt32 winSkipV;
    /**< Number of pixels skipped inside each H3A window in V-direction */

} AlgorithmLink_IssAewbH3aParams;

/*******************************************************************************
 *  \brief Min/Max Range, used in AWB calibration data
 *******************************************************************************
 */
typedef struct {
    UInt32 min;
    /**< Min Value */
    UInt32 max;
    /**< Max Value */
} AlgorithmLink_IssAewbRange;

/*******************************************************************************
 *  \brief Sensor Specific Auto Exposure Dynamic Parameters
 *******************************************************************************
 */
typedef struct {
    AlgorithmLink_IssAewbRange exposureTimeRange[ALGORITHM_AEWB1_MAX_AE_DYN_PARAMS];
    /**< range of exposure time, unit is same with exposure time */
    AlgorithmLink_IssAewbRange apertureLevelRange[ALGORITHM_AEWB1_MAX_AE_DYN_PARAMS];
    /**< range of aperture level, unit is same with aperture level */
    AlgorithmLink_IssAewbRange sensorGainRange[ALGORITHM_AEWB1_MAX_AE_DYN_PARAMS];
    /**< range of sensor gain, unit is same with sensor gain */
    AlgorithmLink_IssAewbRange ipipeGainRange[ALGORITHM_AEWB1_MAX_AE_DYN_PARAMS];
    /**< range of IPIPE gain, unit is same with IPIPE gain */
    UInt32                     numAeDynParams;
    /**< Number of Valid Entries in above arrays */
    AlgorithmLink_IssAewbRange targetBrightnessRange;
    /**< range of target brightness */
    UInt32                     targetBrightness;
    /**< target brightness value */
    UInt32                     threshold;
    /**< threshold for not using history brightness information */
    UInt32                     exposureTimeStepSize;
    /**< step size of exposure time adjustment */
    UInt32                     enableBlc;
    /**< TRUE enables Backlight compensation, disabled otherwise */
} AlgorithmLink_IssAewbAeDynamicParams;

/*******************************************************************************
 *  \brief 2A Parameters, Used by the DCC to control 2A parameters
 *         It could be used to enable/disable AE/AWB or used to fix
 *         output of AE/AWB
 *******************************************************************************
 */
typedef struct {
    UInt32                aeMode;
    /**< AE Mode, used to enable/disable AE.
         It could be either AUTO (0) or manual (1),
         Auto mode is default and runs the AE algorithms
         Manual mode uses below AE parameters value as AE output */
    UInt32                digitalGain;
    /**< Digital Gain for manual AE mode */
    UInt32                analogGain;
    /**< Analog Gain for manual AE mode */
    UInt32                expTime;
    /**< Exposure time for manual AE mode */
    UInt32                awbMode;
    /**< AWB Mode, used to enable/disable AWB.
         It could be either AUTO (0) or manual (1),
         Auto mode is default and runs the AWB algorithms
         Manual mode uses below AWB parameters value as AE output */
    UInt32                rGain;
    /**< Red color gain for manual AWB mode*/
    UInt32                gGain;
    /**< Green color gain for manual AWB mode*/
    UInt32                bGain;
    /**< Blue color gain for manual AWB mode*/

    UInt32                colorTemp;
    /**< Color Temperature for manual AWB mode*/
} AlgorithmLink_IssAewb2AParams;

/*******************************************************************************
 *  \brief Sensor Specific AWB calibration Data
 *         Caution: Do not change size of any array as this will be
 *         internally by the algorithm
 *******************************************************************************
 */
typedef struct {
    UInt32    numRef1;
    UInt32    numRef2;
    UInt32    numGray;

    UInt32    colorTemp1[ALGORITHM_AEWB1_MAX_REF1];

    Int32     wbReferenceCb[ALGORITHM_AEWB1_MAX_REF1][ALGORITHM_AEWB1_MAX_GRAY];
    Int32     wbReferenceCr[ALGORITHM_AEWB1_MAX_REF1][ALGORITHM_AEWB1_MAX_GRAY];

    UInt32    refGrayR1[ALGORITHM_AEWB1_MAX_REF1][ALGORITHM_AEWB1_MAX_GRAY];
    UInt32    refGrayG1[ALGORITHM_AEWB1_MAX_REF1][ALGORITHM_AEWB1_MAX_GRAY];
    UInt32    refGrayB1[ALGORITHM_AEWB1_MAX_REF1][ALGORITHM_AEWB1_MAX_GRAY];

    UInt32    refIndex2[ALGORITHM_AEWB1_MAX_REF2];
    UInt32    colorTemp2[ALGORITHM_AEWB1_MAX_REF2];

    UInt32    imgRef[ALGORITHM_AEWB1_MAX_REF2 * 1120U];

    Int32     refCb2[ALGORITHM_AEWB1_MAX_REF2][ALGORITHM_AEWB1_MAX_GRAY];
    Int32     refCr2[ALGORITHM_AEWB1_MAX_REF2][ALGORITHM_AEWB1_MAX_GRAY];

    UInt32    refGrayR2[ALGORITHM_AEWB1_MAX_REF2][ALGORITHM_AEWB1_MAX_GRAY];
    UInt32    refGrayG2[ALGORITHM_AEWB1_MAX_REF2][ALGORITHM_AEWB1_MAX_GRAY];
    UInt32    refGrayB2[ALGORITHM_AEWB1_MAX_REF2][ALGORITHM_AEWB1_MAX_GRAY];


    /* Sensor specific tuning parameters */
    UInt32    radius;

    Int32     lumaAwbMin;
    Int32     lumaAwbMax;

    UInt32    lowColorTempThreshold;

    UInt32    applyRgbAdjust;

    Int32     redAdjust;
    Int32     blueAdjust;

    UInt32    sb1;
    UInt32    sb2;

    UInt32    sbLowBound;

    UInt32    defaultTH;
    UInt32    defaultTMH;
    UInt32    defaultTML;
    UInt32    defaultTL;

    UInt32    defaultTHIndex;
    UInt32    defaultTMHIndex;
    UInt32    defaultTMLIndex;
    UInt32    defaultTLIndex;

    UInt32    bestGrayIndexDefault;
} AlgorithmLink_IssAewbAwbCalbData;

/*******************************************************************************
 *  \brief Structure of AEWB output parameters
 *******************************************************************************
 */
struct AlgorithmLink_IssAewbOutParams_t {
    UInt32 channelId;
    /**< Channel Id for which this output params are valid */

    struct {
        UInt32 useAeCfg;
        /**< Flag to indicate whether to use exposureTime, analogGain
             and digital Gains or not */
        UInt32 exposureTime;
        /**< Exposure Time in micro seconds */
        UInt32 analogGain;
        /**< Analog Gains,
             Step size is same as Sensor gain step size */
        UInt32 digitalGain;
        /**< Digital Gains,
             Step size is same IPIPE gain step size */

        UInt32 useWbCfg;
        /**< Flag to indicate whether to use White balance gains or not */
        UInt32 gain[4U];
        /**< [0] = r, [1] = Gr, [2] = Gb, [3] = B */
        UInt32 offset[4U];
        /**< [0] = r, [1] = Gr, [2] = Gb, [3] = B */

        UInt32 useColorTemp;
        /* Flag to indicate whether to use color temp or not */
        UInt32 colorTemparature;
        /**< Color Temperature */
    } outPrms[2U];
    /**< For 2 PASS WDR. Currently applying for only 1 PASS */

    UInt32 numParams;
    /**< Number of valid entries in outPrms */

#if 1 //Gang_AE:
    struct {
        UInt32 useAeCfg;
        /**< Flag to indicate whether to use exposureTime, analogGain
             and digital Gains or not */
        UInt32 exposureTime;
        /**< Exposure Time in micro seconds */
        UInt32 analogGain;
        /**< Analog Gains,
             Step size is same as Sensor gain step size */
        UInt32 digitalGain;
        /**< Digital Gains,
             Step size is same IPIPE gain step size */

        UInt32 useWbCfg;
        /**< Flag to indicate whether to use White balance gains or not */
        UInt32 gain[4U];
        /**< [0] = r, [1] = Gr, [2] = Gb, [3] = B */
        UInt32 offset[4U];
        /**< [0] = r, [1] = Gr, [2] = Gb, [3] = B */

        UInt32 useColorTemp;
        /* Flag to indicate whether to use color temp or not */
        UInt32 colorTemparature;
        /**< Color Temperature */
    } camAePrms[4U];
#endif

};

/*******************************************************************************
 *  \brief Alg Link create params
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_CreateParams  baseClassCreate;
    /**< Base class create params. This structure should be first element */
    UInt32                      channelId;
    /**< Channel Id for which this AEWB algo is created */
    AlgorithmLink_IssAewbMode   mode;
    /**< Algorithm Mode */
    System_LinkInQueParams      inQueParams;
    /**< Input queue information */
    UInt32                      numOutBuffers;
    /**< Number of output Buffers */
    UInt32                      numH3aPlanes;
    /**< Number of H3A buffer, which will provided in a single new request */
    AlgorithmLink_IssAewbH3aParams h3aParams;
    /**< H3A params used by ISP. This MUST match the ISP setting */
    System_VideoDataFormat      dataFormat;
    /**< H3A input Bayer format, Must match with the ISP settings */
    UInt32                      numSteps;
    /**< AWB Algorithm Step size, After each numSteps, algo will run */

    /* AE Parameters */
    AlgorithmLink_IssAewbAeDynamicParams aeDynParams;
    /**< Array of Auto Exposure Dynamic Parameters */

    AlgorithmLink_IssAewbAwbCalbData *calbData;
    /**< Sensor Specific Calibration data for the AutoWhite Balance
         If set to NULL, default calibration data will be used */

    Void                            *appData;
    /**< Private Application data */
    AlgorithmLink_IssAewbConfig     cfgCbFxn;
    /**< Callback function, AEWB algorithm calls this callback with the
         output parameters, this callback should apply output parameters to
         the appropriate hardware modules/sensors */

    UInt32                          isWdrEnable;
    /**< Flag to indicate whether WDR Merge is enabled or not,
         This flag is just used to call mergeCbFxn callback function and
         configure ISP */
    AlgorithmLink_IssAewbConfig     mergeCbFxn;
    /**< Callback function to get the exposure ratio from sensor and
         apply merge parameters in ISP based on exposure ratio,
         used only when isWdrMergeEnable flag is set
         Called on every #numSteps frames processing,
         It could be set to null if fixed exposure ratio is used
         in sensor/isp */

    Void                            *dccAppData;
    /**< Private Application data for DCC Callback */
    AlgorithmLink_IssAewbDccUpdate  dccIspCfgFxn;
    /**< Callback function to update DCC Configuration in ISP,
         After reading ISP configuration from file, it will be updated
         in ISP using this function. */
    UInt32                         dccCameraId;
    /**< FVID2 ID of the Sensor/Camera, Used by the DCC Parser.
         DCC bin file will be used only if this id matches with the
         id in the bin file. */

    System_LinkMemAllocInfo memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

    UInt32                         enableDcc;
    /**< Flag to enable DCC support for this AEWB instance */

    UInt32                         runAewbOnlyForOneCh;
    /**< Flag to enable/disable AEWB only for one of the input channels
         TRUE: Enables AEWB only for one of the input channels, for all
               the other input cannels, same ouput params will be applied
               #chId parameter selects the id of the channel for which AEWB
               will be run */
    UInt32                         chId;
    /**< Id of the channel for which AEWB to be run,
         used only when #runAewbOnlyForOneCh flag is set to TRUE */

} AlgorithmLink_IssAewbCreateParams;

/**
 *******************************************************************************
 *   \brief Structure containing control parameters for AE Dynamic Parameters
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    AlgorithmLink_IssAewbAeDynamicParams *aeDynParams;
    /**< Auto Exposure Dynamic Parameters */

} AlgorithmLink_IssAewbAeControlParams;

/*******************************************************************************
 *  \brief Structure containing control parameters for AWB Calibration data
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    AlgorithmLink_IssAewbAwbCalbData *calbData;
    /**< Sensor Specific Calibration data for the AutoWhite Balance */
} AlgorithmLink_IssAewbAwbControlParams;

/**
 *******************************************************************************
 *   \brief Structure containing control parameters for DCC
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt8       *dccBuf;
    /**< Pointer to the DCC File */

    UInt32      dccBufSize;
    /**< DCC Buffer Size */
} AlgorithmLink_IssAewbDccControlParams;

/**
 *******************************************************************************
 *   \brief Structure containing control parameters for DCC Camera Information
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32 cameraId;
    /**< DCC Camera Id */

    UInt32 width;
    /**< Capture frame width */
    UInt32 height;
    /**< Capture frame height */
} AlgorithmLink_IssAewbDccCameraInfo;

/**
 *******************************************************************************
 *   \brief Structure containing control parameters for 2A State Information
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams     baseClassControl;
    /**< Base class control params */
    AlgorithmLink_IssAewb2AParams   aewb2APrms;
    /**< 2A Parameters */
} AlgorithmLink_IssAewb2AControlParams;

/*******************************************************************************
 *  Function Prototypes
 *******************************************************************************
 */
static inline void AlgorithmLink_IssAewb_Init(
                            AlgorithmLink_IssAewbCreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_IssAewb_Init(
    AlgorithmLink_IssAewbCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_IssAewbCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                    sizeof(AlgorithmLink_IssAewbCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_IPU_ALG_ISS_AEWB;

    pPrm->channelId = 0U;
    pPrm->appData = NULL;

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->numH3aPlanes = 1U;
    pPrm->numOutBuffers = 3U;

    pPrm->h3aParams.winCountH = 16U;
    pPrm->h3aParams.winCountV = 20U;
    pPrm->h3aParams.winSizeH  = 32U;
    pPrm->h3aParams.winSizeV  = 16U;
    pPrm->h3aParams.winSkipH  = 3U;
    pPrm->h3aParams.winSkipV  = 3U;

    pPrm->dataFormat = SYSTEM_DF_BAYER_GRBG;
    pPrm->numSteps = 6U;
    pPrm->mode = ALGORITHMS_ISS_AEWB_MODE_AWB;
    pPrm->cfgCbFxn = NULL;

    pPrm->isWdrEnable = (UInt32)FALSE;
    pPrm->mergeCbFxn = NULL;
    pPrm->dccIspCfgFxn = NULL;

    pPrm->enableDcc = 1U;

    pPrm->runAewbOnlyForOneCh = (UInt32)FALSE;
    pPrm->chId = 0U;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of AEWB algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_issAewb1_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
