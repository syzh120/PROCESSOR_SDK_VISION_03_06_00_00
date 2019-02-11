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
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_CHAIN APIs for selecting the usecase chain.
 *
 * \brief  APIs for selecting the required usecase chain and run
 *         time menu configurations .
 *         It also provide API's for instrumentation of load and heap usage
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains_radar.h
 *
 * \brief APIs for selecting the required usecase chain.
 *
 * \version 0.0 (Aug 2016) : [PG] First version
 *
 *******************************************************************************
 */

#ifndef CHAINS_RADAR_H_
#define CHAINS_RADAR_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <system_cfg.h>
#include <src/include/chains.h>
#include <src/include/chains_common.h>
#include <include/common/chains_radar_cfg.h>
#include <include/link_api/issCaptureLink.h>
#include <include/link_api/captureLink.h>
#include <include/alg_fxns/radarFFT_if.h>
#include <include/alg_fxns/radarPkDetect_if.h>
#include <include/alg_fxns/radarBeamForm_if.h>
#include <include/alg_fxns/radarDrawFFTHeatMap_if.h>
#include <include/alg_fxns/radarDraw_if.h>
#include <include/alg_fxns/radarFrameCopy_if.h>
#include <include/alg_fxns/radarDspProcess_if.h>

#include <ti/drv/vps/include/devices/bsp_ar12xx.h>
#include <ti/drv/stw_lld/platform/platform.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#undef PULLUDENABLE_ENABLE
#undef PULLUDENABLE_DISABLE
#undef PULLTYPESELECT_PULL_UP
#undef PULLTYPESELECT_PULL_DOWN
#undef INPUTENABLE_ENABLE
#undef INPUTENABLE_DISABLE
#undef SLEWCONTROL_FAST_SLEW
#undef SLEWCONTROL_SLOW_SLEW
#undef WAKEUPENABLE_ENABLE
#undef WAKEUPENABLE_DISABLE

#define PULLUDENABLE_ENABLE         (1U)
#define PULLUDENABLE_DISABLE        (0U)
#define PULLTYPESELECT_PULL_UP      (1U)
#define PULLTYPESELECT_PULL_DOWN    (0U)
#define INPUTENABLE_ENABLE          (1U)
#define INPUTENABLE_DISABLE         (0U)
#define SLEWCONTROL_FAST_SLEW       (1U)
#define SLEWCONTROL_SLOW_SLEW       (0U)
#define WAKEUPENABLE_ENABLE         (1U)
#define WAKEUPENABLE_DISABLE        (0U)

/**
 * On the TDA3x EVM and the ALPS board the CSI data lane positions are
 * as below:
 *
 *        TDA                              AR
 *   ----------------                 ------------------
 *   csi2_0_dx/y0   |-----------------| dx/dy0
 *   csi2_0_dx/y1   |-----------------| dx/dy2 ** Note
 *   csi2_0_dx/y2   |-----------------| dx/dy1 ** Note
 *   csi2_0_dx/y3   |-----------------| dx/dy3
 *   csi2_0_dx/y4   |-----------------| dx/dy4
 *   ----------------                 ------------------
 */
/** \brief AR CSI clock lane position */
#define CHAINS_AR1243_CSI_CLOCKLANE_POS        (3U)
/** \brief AR CSI first data lane position */
#define CHAINS_AR1243_CSI_DATA1LANE_POS        (1U)
/** \brief AR CSI second data lane position */
#define CHAINS_AR1243_CSI_DATA2LANE_POS        (2U)
/** \brief AR CSI third data lane position */
#define CHAINS_AR1243_CSI_DATA3LANE_POS        (4U)
/** \brief AR CSI fourth data lane position */
#define CHAINS_AR1243_CSI_DATA4LANE_POS        (5U)

#ifdef BOARD_TYPE_TDA3XX_RVP
/** \brief TDA CSI clock lane position */
#define CHAINS_AR1243_TDA_CSI_CLOCKLANE_POS    (1U)
/** \brief TDA CSI first data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA1LANE_POS    (2U)
/** \brief TDA CSI second data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA2LANE_POS    (3U)
/** \brief TDA CSI third data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA3LANE_POS    (4U)
/** \brief TDA CSI fourth data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA4LANE_POS    (5U)
#elif (defined(TDA2PX_BUILD) && defined(PLATFORM_EVM_SI))
/** \brief TDA CSI clock lane position */
#define CHAINS_AR1243_TDA_CSI_CLOCKLANE_POS    (1U)
/** \brief TDA CSI first data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA1LANE_POS    (2U)
/** \brief TDA CSI second data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA2LANE_POS    (3U)
/** \brief TDA CSI third data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA3LANE_POS    (4U)
/** \brief TDA CSI fourth data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA4LANE_POS    (5U)
#else
/** \brief TDA CSI clock lane position */
#define CHAINS_AR1243_TDA_CSI_CLOCKLANE_POS    (2U)
/** \brief TDA CSI first data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA1LANE_POS    (1U)
/** \brief TDA CSI second data lane position */
/** \brief TDA CSI second data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA2LANE_POS    (3U)
/** \brief TDA CSI third data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA3LANE_POS    (4U)
/** \brief TDA CSI fourth data lane position */
#define CHAINS_AR1243_TDA_CSI_DATA4LANE_POS    (5U)
#endif

/** \brief Macros for time calculation */
#define CHAINS_AR1243_TIME_MS_TO_5NS(x) ((x * 1000000)/5)
#define CHAINS_AR1243_TIME_US_TO_10NS(x) (x * 100)

#define CHAINS_AR1243_TIME_5NS_TO_MS(x) (((x) * 5)/1000000)

#define CHAINS_AR1243_FREQ_CONST (3.6 * 1000000000.0/67108864.0)

/** \brief Macro for Frequency Calculation. Input 'x' is in GHz */
#define CHAINS_AR1243_FREQ_GHZ_CONV(x) ((rlUInt32_t)(((float)x * 1000000000.0 + CHAINS_AR1243_FREQ_CONST)/CHAINS_AR1243_FREQ_CONST))

#define CHAINS_AR1243_FREQ_SLOPE_CONST (CHAINS_AR1243_FREQ_CONST * 900.0/1000.0)

/** \brief Macro for frequency slope conversion. Input 'x' is in MHz/us */
#define CHAINS_AR1243_FREQ_MHZ_PER_MICRO_S_SLOPE_CONV(x) ((rlInt16_t)((x * 1000.0 + CHAINS_AR1243_FREQ_SLOPE_CONST)/CHAINS_AR1243_FREQ_SLOPE_CONST))

/** \brief Compile time assert for the array size not correct */
#define COMPILE_TIME_ASSERT(expr) \
    extern UInt8 check_parameter_size[2]; \
    extern UInt8 check_parameter_size[expr? 1: 2]

#define CHAINS_UB960_CSI_DATA_RATE (800U)
/* Max number of chirp config could be up to 512 */
#define CHAINS_RADAR_MAX_NUM_CHIRP_CFG                              (64U)
#define CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA                         (12U)
#define CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA_PERSENSOR               (3U)
#define CHAINS_RADAR_CASCADE_MAX_RX_ANTENNA_PERSENSOR               (4U)
#define CHAINS_RADAR_CASCADE_NUMSENSORS                             (4U)

/*******************************************************************************
 *  Structure declaration
 *******************************************************************************
 */
typedef struct
{
    UInt16 azimOffset;
    UInt16 elevOffset;
} Chanis_RadarAntOffset;

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Data Read/Write Mode for Null and Null source links
 *******************************************************************************
 */
typedef enum {

    CHAINS_RADAR_LINKTYPE_NETWORK,
     /**< Use network mode for null and null source */
     CHAINS_RADAR_LINKTYPE_FILE
     /**< Use File mode for null and null source */
} Chains_DataRdWrType;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief   Single Channel radar sensor (AR1243) capture and SD Card write
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarcaptureonly(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Pre-recorded SD card read, radar frame copy and write to SD Card
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarobjectdetectdisplay(Chains_Ctrl *chainsCfg);
Void Chains_radarobjectdetectnull(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Pre-recorded SD card read, radar fft and write to SD Card
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarreadfftwrite(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Single Channel radar sensor (AR1243) capture, frame copy and SD
 *          Card write
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarcaptureprocess(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Pre-recorded SD card read, radar object detect and write to SD Card
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_radarfilereadobjdetectwrite(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Cascade 4 channel radar sensor (AWR1243) capture and network output
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_cascadeRadarCapture(Chains_Ctrl *chainsCfg);

/**
 *******************************************************************************
 *
 * \brief   Cascade 4 channel radar sensor (AWR1243) capture, object detection
 *          and network output
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_cascadeRadarOd(Chains_Ctrl *chainsCfg);

Void Chains_multiradarcapturefftdisplay(Chains_Ctrl *chainsCfg);

Void ChainsCommon_ar12xxConfig(ChainsCommon_Ar12xxConfigOut *pCfgOut);
Void ChainsCommon_ar12xxStart();
Void ChainsCommon_ar12xxStop(ChainsCommon_Ar12xxConfigOut *pCfgOut);
Void ChainsCommon_ar12xxSetIssCaptureParams(IssCaptureLink_CreateParams *pIssCapturePrm,
                                            ChainsCommon_Ar12xxConfigOut *pCfgOut);
Void ChainsCommon_ar12xxSetMultiVipCaptureParams(
                        CaptureLink_CreateParams *pPrm,
                        ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
                        UInt32 portId[]);
Void ChainsCommon_ar12xxSetFFTParams(
        AlgorithmFxn_RadarFftCreateParams *pFFTParams,
        ChainsCommon_Ar12xxConfigOut *pAr12xxCfg);
Void ChainsCommon_ar12xxSetFFTHeatMapParams(
        AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *pRadarDrawFFTHeatMapPrm,
        ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
        UInt32 displayWidth, UInt32 displayHeight);
Int32 ChainsCommon_ar12xxCheckParameters(ChainsCommon_Ar12xxConfigOut *pCfgOut);
Void ChainsCommon_ar12xxFirmwareFlash(void);
Void ChainsCommon_ar12xxDeInit(ChainsCommon_Ar12xxConfigOut *pCfgOut);

/* Set data read/write mode for null and null source based use-cases */
Chains_DataRdWrType Chains_getDataRdWrMode();

Void ChainsCommon_ar12xxSetFFTHeatMapProfile(UInt32 algId,
                                             ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
                                             UInt32 profId);
Int32 ChainsCommon_ar12xxChangeParameters(UInt32 algId, ChainsCommon_Ar12xxConfigOut *pCfgOut);
Void ChainsCommon_ar12xxSetPkDetectParams(AlgorithmFxn_RadarPkDetectCreateParams *pPkDetParams,
                                          ChainsCommon_Ar12xxConfigOut *pAr12xxCfg);
Void ChainsCommon_ar12xxSetBeamFormParams(
    AlgorithmFxn_RadarBeamFormCreateParams *pBeamFormParams,
    ChainsCommon_Ar12xxConfigOut *pAr12xxCfg);
Void Chains_RadarCalculateSteeringMatrix(Int16 * buffer,
    double horzAngleStep, int32_t numHorzAntenna,
    double vertAngleStep, int32_t numVertAntenna,
    double antSeparation,
    double maxHorzAbsAngle, double maxVertAbsAngle);
Void ChainsCommon_ar12xxBeamFormDeInit(
    ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
    AlgorithmFxn_RadarBeamFormCreateParams *pBeamFormParams);
Void ChainsCommon_ar12xxSetRadarDrawParams(
        AlgorithmFxn_RadarDrawCreateParams *pRadarDrawPrm,
        ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
        UInt32 displayWidth, UInt32 displayHeight);
Void ChainsCommon_ar12xxSetDrawProfile(UInt32 algId,
                                      ChainsCommon_Ar12xxConfigOut *pAr12xxCfg,
                                      UInt32 profId);
UInt32 Chains_ar12xxCountOnes(UInt32 num);
void configure_pad(const pad_config_t *pad_array, uint32_t elements);
Int32 ChainsCommon_fpgaPowerUp(UInt32 fpgaNum);
Int32 ChainsCommon_fpgaStart(UInt32 fpgaNum);

Int32 Chains_ar12xxGetSampleConfig(ChainsCommon_Ar12xxConfigOut *pCfgOut, UInt32 fusionEnabled);
Int32 Chains_ar12xxGetSampleCascadeConfig(ChainsCommon_Ar12xxConfigOut *pCfgOut);
Int32 Chains_ar12xxSetCascadePhaseShifterBeamForm(void);
Int32 Chains_ar12xxGetSampleCascadeConfigBeamForm(ChainsCommon_Ar12xxConfigOut *pCfgOut);

char ChainsCommon_ar12xxRunTimeMenu(char * pMenu);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup EXAMPLES_API Example code implementation
 *
 *******************************************************************************
 */


