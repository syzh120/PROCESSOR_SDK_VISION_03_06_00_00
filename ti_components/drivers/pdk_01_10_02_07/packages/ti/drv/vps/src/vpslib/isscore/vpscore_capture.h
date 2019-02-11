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
 *  \file vpscore_capture.h
 *
 *  \brief  Provides interfaces to control / configure ISS based capture.
 *              Methods to configure capture via CAL OR LVDS.
 *
 *          With each instance of capture opened, one or more stream can be
 *          captured.
 */

#ifndef VPSCORE_ISS_CAPTURE_H_
#define VPSCORE_ISS_CAPTURE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/include/iss/vps_isscommon.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum number of opens supported per instance of core */
#define VCORE_ISS_CAPT_MAX_OPEN             (0x1U)

/** \brief When CAL alone is built, the control base will not defined. */
#ifndef VPS_ISS_IOCTL_CAL_IOCTL_BASE

/** \brief CAL Control Command base start */
#define VPS_ISS_IOCTL_CAL_IOCTL_BASE        (0x0U)

#endif

/** \brief IOCTL base address for the common IOCTLs listed below. TODO TBD
 *      Should derive from a common base */
#define VCORE_ISS_CAPT_BASE_IOCTL           (VPS_ISS_IOCTL_CAL_IOCTL_BASE)

/** \brief Configure CAL based on the config supplied by a pointer to instance
 *          of type vpsissCalCfg_t as argument.
 *          vpsissCalCfg_t defined in starterware_\include\vps\iss\vps_cfgcal.h
 */
#define VCORE_ISS_CAPT_CAL_SET_PARAMS       (VCORE_ISS_CAPT_BASE_IOCTL + 1U)

/** \brief CAL streams config, used to identify streams that are not written
 *          by CAL. Written by an entity outside CAL. (ISP)
 *          This is mandatory for OTF mode, not required for others. */
#define VCORE_ISS_CAPT_CAL_SET_STREAMS_MAP  (VCORE_ISS_CAPT_BASE_IOCTL + 2U)

/** \brief Enable/Disable error in CAL
 *    vpsissCalErrorCfg_t defined in starterware_\include\vps\iss\vps_cfgcal.h
 */
#define VCORE_ISS_CAPT_CAL_SET_ERR_PRMS     (VCORE_ISS_CAPT_BASE_IOCTL + 3U)

/** \brief Enable CB on reception of Nth line and end of frame
 *   a pointer of type vcoreissCaptSubFrameCfg_t
 */
#define VCORE_ISS_CAPT_CAL_SET_SUB_FRM_PRMS (VCORE_ISS_CAPT_BASE_IOCTL + 4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct vcoreissCaptInterface
 *  \brief Different physical interface supported.
 */
typedef enum vcoreissCaptInterface
{
    VPSCORE_ISS_CAPT_IF_CSI2    = 0x0,
    /**< CSI2 Interface */
    VPSCORE_ISS_CAPT_IF_LVDS    = 0x1,
    /**< LVDS Interface */
    VPSCORE_ISS_CAPT_IF_CPI     = 0x2,
    /**< CPI / Parallel interface */
    VPSCORE_ISS_CAPT_IF_MAX     = 0x3,
    /**< End Marker */
    VPSCORE_ISS_CAPT_IF_FORCE_INT = 0x7FFFFFFF
                                    /**< This will ensure enum is not packed,
                                     *      will always be contained in int */
} vcoreissCaptInterface_t;

/**
 *  struct vcoreissCaptInitParams
 *  \brief Different modes of capture supported. LVDS & CAL based capture cannot
 *          not co-exist.
 */
typedef struct vcoreissCaptInitParams
{
    vpsissCaptInstId_t         instId;
    /**< Capture core instance ID, CAL OR LVDS */
    const VpsLib_PlatformData *halPlatformData;
    /**< HAL information */
    issemInstId_t              irqNum;
    /**< Interrupt number associated with this instance.
     *      The design / implementation, assumes single IRQ is used, if multi
     *      ple IRQ are used, we would require to guard ISR with interrupt
     *      enable / disable. */
    uint32_t                   subModules;
    /**< ISS Sub-modules required to be enabled for this instance */
    Ptr                        arg;
    /**< Not used for now, reserved */
} vcoreissCaptInitParams_t;

/**
 *  \brief Open Parameters.
 */
typedef struct vcoreissCaptOpenParams
{
    vcoreissCaptInterface_t captIf;
    /**< Type of interface
     *   Some interfaces are possible only in few instances,
     *   like CSI2 is possible only on CALA/B instances,
     #vcoreissCaptInterface_t  */
    uint32_t                numStreams;
    /**< Define number of streams that is required. */
    UInt32                  subModules[VPS_ISS_CAL_MAX_STREAMS];
    /**< Identify the modules required for each stream.
     *  e.g. modulesReq[0] =
     *      VPS_ISS_CAPT_CAL_SUB_PPI_ID | VPS_ISS_CAPT_CAL_SUB_PIX_EXTRACT_ID
     *      resources are defined in vpsissCaptureSubModuleId_t
     *  Only 2 modules required, 1 to decode CSI2 and write received data */
    uint32_t                isCmplxIoCfgValid[CSL_CAL_CMPLXIO_CNT];
    /**< Specify if the complex IO configurations should be applied or the
     *      default config should be applied.
     *  TRUE - Complex IO configuration provided below is valid and will be
     *          applied.
     *  FALSE - Default complex IO configuration would be applied. */
    vpsissCalCmplxIoCfg_t   cmplxIoCfg[CSL_CAL_CMPLXIO_CNT];
    /**< Specify the CSI2 lanes configurations */
    uint32_t                csi2PhyClock[CSL_CAL_CMPLXIO_CNT];
    /**< Specify the CSI2 PHY clock in MHz. e.g. if 400 MHz is the clock
     *      \code csi2PhyClock = 400; */
    Ptr                     otfOpenPrms;
    /**< Open Parameters for ISP */
    Ptr                     arg;
    /**< Not Used as of now */
} vcoreissCaptOpenParams_t;

/**
 *  \brief Details returned by open operation
 */
typedef struct vcoreissCaptOpenRetParams
{
    int32_t  streamAllocError;
    /**< In case there no free streams available, status would be set to
     *      FVID2_EALLOC this variable will hold FVID2_EALLOC */
    uint32_t numStreamsAlloc;
    /**< Returns the number of streams allocated */
    UInt32   cportIdAlloc[VPS_ISS_CAL_MAX_STREAMS];
    /**< Instances of the sub modules allocated */
    UInt32   isStreamOpt[VPS_ISS_CAL_MAX_STREAMS];
    /**< Indicates streams that do not result in a write to memory.
     *      i.e. consumed internally by the CAL and for which memory need not
     *              be allocated. */
    Ptr      arg;
    /**< Not used as of now */
} vcoreissCaptOpenRetParams_t;

/**
 *  struct vcoreissCaptSubFrameCfg
 *  \brief CAL could be configured to notify application on end of frame or on
 *          reception of first X lines.
 *
 *  Limitation on first x lines callback : Currently this can be enabled for
 *      one stream and stream should be of type VPS_ISS_CAL_TAG_PIX_DATA
 *
 */
typedef struct vcoreissCaptSubFrameCfg
{
    uint32_t numStream;
    /**< Number of streams, which requires to be monitored for end of frame,
            and or first X lines */
    uint32_t streamId[VPS_ISS_CAL_MAX_STREAMS];
    /**< Specify the stream ID, which requires to be monitored */
    uint32_t notifyAfterFirstXLines[VPS_ISS_CAL_MAX_STREAMS];
    /**< Will call the application provided callback, after reception of
        number of lines specified here.
        Restriction :
            This can be supported for only VPS_ISS_CAL_MAX_X_LINE_MONITOR_CNT
            virtual channel */
    uint32_t notifyAfterEndOfFrame[VPS_ISS_CAL_MAX_STREAMS];
    /**< Will call the application provided callback, after reception of
        End Of Frame short packet */
    VpsCore_SubFrameCbFxn appCb;
    /**< Application callback */
    Ptr     pAppCbArgs;
    /**< Argument that would be passed when appCb is called. */
    Ptr     pAdditionalArgs;
    /**< Not used for now - should be set to NULL */
} vcoreissCaptSubFrameCfg_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Function to initialize capture via ISS. Performs h/w initializations
 *          if required.
 *
 *  \param numInst          number of instances to be initialized
 *  \param initParams       Init parameters, containing HAL
 *                          initialization parameters.
 *  \param arg              not used as of now
 *
 *  \return                 FVID2_SOK: on successful completion, otherwise
 *                          appropriate error code.
 */
int32_t VpsCore_issCaptInit(
    uint32_t                  numInst,
    const vcoreissCaptInitParams_t *initParams,
    Ptr                       arg);

/**
 *  \brief DeInitializes Capture instances.
 *
 *  \param arg            Not used as of now.
 *
 *  \return                 FVID2_SOK: on successful completion, otherwise
 *                          appropriate error code.
 */
int32_t VpsCore_issCaptDeInit(Ptr arg);

/**
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return  Returns the pointer to core function pointer table. NULL on errors.
 */
const VpsCore_Ops *VpsCore_issCaptGetCoreOps(void);

/**
 *  \brief Returns the pointer to the core instance object
 *
 *  \return  A Valid pointer on success else a NULL pointer.
 */
VpsCore_Inst VpsCore_issCaptGetCoreInstObj(vpsissCaptInstId_t inst);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSCORE_ISS_CAPTURE_H_ */
