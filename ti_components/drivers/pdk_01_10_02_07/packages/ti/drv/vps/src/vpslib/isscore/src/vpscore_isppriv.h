/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file vpscore_captureIsppriv.h
 *
 *  \brief  ISP Capture internal header file.
 *
 */

#ifndef VPSCORE_CAPTURE_ISP_PRIV_H_
#define VPSCORE_CAPTURE_ISP_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/common/vps_common.h>
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/iss/vps_cfgisif.h>
#include <ti/drv/vps/include/iss/vps_cfgh3a.h>
#include <ti/drv/vps/include/iss/vps_cfgipipe.h>
#include <ti/drv/vps/include/iss/vps_cfgnsf3.h>
#include <ti/drv/vps/include/iss/vps_cfgcnf.h>
#include <ti/drv/vps/include/iss/vps_cfgrsz.h>
#include <ti/drv/vps/include/iss/vps_cfgisp.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isscal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issh3a.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issipipeif.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issipipe.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issisif.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issnsf3.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issglbce.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_issrsz.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_isp.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_isscommoncfg.h>
#include <ti/drv/vps/src/vpslib/isscore/vpscore_m2m.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief maximum number of ISP objects supported
 */
#define VCORE_MAX_ISP_OBJECTS   (VPSCORE_ISS_M2M_ISP_MAX_HANDLES)

/** \brief IOCTL base address for the internal ISP layer. */
#define VCORE_ISS_ISP_INT_BASE_IOCTL            (0x00100000U)

/** \brief IOCTL for setting default configuration in ISP modules
 *
 *  \param  ispHndl     Handle to the ISP Object
 *
 *  \return FVID2_SOK on Success
 *          FVID2_Error code on failure
 */
#define VCORE_ISS_ISP_SET_DEFAULT_CFG           (VCORE_ISS_ISP_INT_BASE_IOCTL + \
                                                 1U)

/** \brief IOCTL for setting default configuration in ISP modules
 *
 *  \param  ispHndl     Handle to the ISP Object
 *
 *  \return FVID2_SOK on Success
 *          FVID2_Error code on failure
 */
#define VCORE_ISS_ISP_GET_ISP_BLANK_INFO        (VCORE_ISS_ISP_INT_BASE_IOCTL + \
                                                 2U)

/** \brief IOCTL for setting default configuration in ISP modules
 *
 *  \param  ispHndl     Handle to the ISP Object
 *
 *  \return FVID2_SOK on Success
 *          FVID2_Error code on failure
 */
#define VCORE_ISS_ISP_GET_GLBCE_NSF3_BLANK_INFO (VCORE_ISS_ISP_INT_BASE_IOCTL + \
                                                 3U)

/* Default Frame width */
#define VPSCORE_ISS_M2M_DEF_FRAME_WIDTH         (720U)
/* Default Frame Height */
#define VPSCORE_ISS_M2M_DEF_FRAME_HEIGHT        (480U)
/* Default BPP */
#define VPSCORE_ISS_M2M_DEF_FRAME_BPP           (FVID2_BPP_BITS10)
/* Default Bayer Format */
#define VPSCORE_ISS_M2M_DEF_BAYER_FMT           (FVID2_DF_BAYER_RGGB)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef enum vcoreIspOpenMode
{
    VCORE_ISP_OPEN_MODE_M2M = 0,
    /**< M2M Mode for ISP */
    VCORE_ISP_OPEN_MODE_CAPTURE = 1,
    /**< Capture Mode for ISP */
    VCORE_ISP_OPEN_FORCE_INT = 0x7FFFFFFF
                               /**< This will ensure enum is not packed, will always be contained in int */
} vcoreIspOpenMode_t;

typedef struct vcoreIspHandleObj
{
    uint32_t                    isAllocated;
    /**< Flag to mark if this isp object is allocated or not */
    uint32_t                    isModReq[VPS_ISS_ISP_MAX_MODULE];
    /**< Bit mask of the ISP modules enabled */
    VpsHal_Handle               halHandles[VPS_ISS_ISP_MAX_MODULE];
    /**< Array of Hal Handles, enum #vcoreCaptIspModules_t is used as
         an array index to get the hal handle */
    vpsissIspParams_t           params;
    /**< ISP Parameters */
    vcoreIspOpenMode_t          openMode;
    /**< ISP Mode */
    VpsCore_OpenPrms            openPrms;
    /**< Used in case OTF Capture to get new frame from the upper layer */

    isshalnsf3FrameSizeParams_t nsf3FrmSize[2U];
    /**< Input Frame size of NSF3/CNF */
    vpsissNsf3Config_t          nsf3Cfg[2U];
    /**< Structure containing NSF3 Configuration for NSF3 and CNF instances
         TODO: Remove hardcoded number of instances Brijesh */
    isshalipipeConfig_t         ipipeCfg;
    /**< Structure containing IPIPE Configuration */
    isshalisifConfig_t          isifCfg;
    /**< Structure containing ISIF Configuration */
    isshalIpipeifCfg_t          ipipeifCfg;
    /**< Structure containing IPIPEIF Configuration */
    isshalrszConfig_t           rszCfg;
    /**< Structure containing Resizer configuration */
    isshalglbceConfig_t         glbceCfg;
    /**< Structure containing GLBCE configuration */
    isshalh3aConfig_t           h3aCfg;
    /**< Structure containing H3A configuration */
    isshalCalCfg_t              calCfg;
    /**< Structure containing CAL configuration */
    isshalCalDmaVcCfg_t         calDmaCfg;
    /**< Configuration expected to updated by core / driver */
    isshalissCnfConfig_t        cnfPrms;
    /**< Structure containing CNF configuration */
    vpsissCnfConfig_t           cnfCfg;
    /**< Cnf Configuration */
    isshalissVp1Config_t        vp1Cfg;
    /**< VP1 Configuration */
    isshalissVp2Config_t        vp2Cfg;
    /**< VP2 Configuration */

    VpsCore_Frame              *curFrm[VPS_ISS_STREAM_ID_MAX];
    /**< Array of current frame pointers
         The frames which are currently programmed in the hardware are
         stored in this array */
    issemClientCbFxn            cbFxn;
    /**< Driver Callback function, used only for M2M case */
    Ptr                         arg;
    /**< Argument to passed back to upper layer along with the callback */
    isshalissStartModuleFxn     startModuleFxn[VPS_ISS_ISP_MAX_MODULE];
    /**< Array of function pointer to the start functions
     *   of the modules */
    isshalissStopModuleFxn      stopModuleFxn[VPS_ISS_ISP_MAX_MODULE];
    /**< Array of function pointer to the stop functions
     *   of the modules */
    isshalissControlModuleFxn   controlFxn[VPS_ISS_ISP_MAX_MODULE];
    /**< Function pointer to control command function of the hal modules */
    isshalIpipeifRtCfg_t        ipipeifRtCfg;
    /**< Ipipeif RunTime configuration, used to enable/disable WDR merging */
    uint32_t                    captStreamMap[VPS_ISS_STREAM_ID_MAX];
    /**< When the ISP is operating in capture mode, this variable maps the
            ISP stream IDs to capture drivers stream ID.
            The relation between ISP stream ID and capture drivers stream ID
            is a dis-joint set, linked by this map.
            Applicable only when openMode == VCORE_ISP_OPEN_MODE_CAPTURE */
    uint32_t                    rszFlipOffset[VPS_ISS_RSZ_SCALER_MAX][
        FVID2_MAX_PLANES];
    /**< Address offset that need to be added to actual buffer address
         in case flipping is enabled. */
} vcoreIspHandleObj_t;

typedef struct vcoreIspCommonObj
{
    uint32_t            isInited;
    /**< Flag to indicate if the common object is initialized or not */
    uint32_t            openCnt;
    /**< ISP layer open count */
    vcoreIspHandleObj_t handleObj[VCORE_MAX_ISP_OBJECTS];
    /**< ISP Handle Object */
    void               *errEvntHndle;
    /**< Handle to Error Event handler */
    void               *emEofIntrHndl;
    /**< Handle to the Event Manager Handler */
} vcoreIspCommonObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t vcoreIspInit(const VpsLib_PlatformData *platData);
int32_t vcoreIspDeInit(Ptr arg);
vcoreIspHandleObj_t *vcoreIspOpenHals(
    const vpsissIspOpenParams_t *coreOpenPrms,
    vcoreIspOpenMode_t           openMode,
    const VpsCore_OpenPrms      *openPrms,
    vpsissIspOpenRetParams_t    *coreReturnPrms,
    Ptr                          arg);
int32_t vcoreIspCloseHals(vcoreIspHandleObj_t *hIspObj, Ptr arg);
int32_t vcoreIspControl(vcoreIspHandleObj_t *hIspObj,
                        uint32_t             cmd,
                        void                *appArgs,
                        void                *drvArgs);
int32_t vcoreIspStart(vcoreIspHandleObj_t *hIspObj, Ptr arg);
int32_t vcoreIspStop(vcoreIspHandleObj_t *hIspObj, Ptr arg);
int32_t vcoreIspSetParams(vcoreIspHandleObj_t     *hIspObj,
                          const vpsissIspParams_t *prms);
int32_t vcoreIspSetDefaultConfig(vcoreIspHandleObj_t *hIspObj);
int32_t vcoreIspRegisterIsr(
    vcoreIspHandleObj_t *hIspObj,
    uint32_t             irqNum,
    issemClientCbFxn     drvCbFxn,
    issemPriority_t      prio,
    Ptr                  arg);
int32_t vcoreIspUnRegisterIsr(vcoreIspHandleObj_t *hIspObj);
int32_t vcoreIspProgBuf(
    vcoreIspHandleObj_t *hIspObj,
    uint32_t             streamId,
    VpsCore_Frame       *frm);
int32_t vcoreIspGetIspBlankInfo(
    vcoreIspHandleObj_t     *hIspObj,
    isshalissBlankingInfo_t *blnkInfo,
    Ptr                      arg);
int32_t vcoreIspGetGlbceNsf3BlankInfo(
    vcoreIspHandleObj_t     *hIspObj,
    isshalissBlankingInfo_t *blnkInfo,
    Ptr                      arg);
int32_t vcoreIspSetSrcSize(vcoreIspHandleObj_t *hIspObj);
int32_t vcoreIspSetCaptStrmMap(vcoreIspHandleObj_t              *hIspObj,
                               const vpsissCalOtfStreamMapCfg_t *streamMap);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSCORE_CAPTURE_ISP_PRIV_H_ */
