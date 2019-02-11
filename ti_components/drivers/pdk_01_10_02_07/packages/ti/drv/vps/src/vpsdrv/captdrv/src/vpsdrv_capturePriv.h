/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file vpsdrv_capturePriv.h
 *
 *  \brief VIP capture driver private header file.
 *
 */

#ifndef VPSDRV_CAPTURE_PRIV_H_
#define VPSDRV_CAPTURE_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_cfgMem.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/vps_capture.h>
#include <ti/csl/soc.h>

#ifdef VPS_DSS_BUILD
#include <ti/drv/vps/include/dss/vps_captureDssWb.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dssWb.h>
#endif

#include <ti/drv/vps/src/vpslib/common/vpscore.h>

#ifdef VPS_VIP_BUILD
#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>
#endif

#include <captdrv/vpsdrv_capture.h>

#ifdef VPS_CAL_BUILD
#include <ti/drv/vps/src/vpslib/common/iem_evtmgr.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>

#if defined (SOC_TDA3XX)
#include <ti/drv/vps/src/vpslib/isscore/vpscore_capture.h>
#endif /* SOC_TDA3XX */
#if defined (SOC_TDA2EX) || defined (SOC_AM571x) || defined (SOC_TDA2PX)
#include <ti/drv/vps/src/vpslib/calcore/vpscore_capture.h>
#endif

#include <ti/drv/vps/include/iss/vps_captureIss.h>
#include <ti/drv/vps/include/iss/vps_cfgcal.h>
#endif /* VPS_CAL_BUILD */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/*
 * State transitions are explained below
 *
 * IDLE - initial or not open state
 *  |
 * CREATED - state after calling Fvid2_create
 *  |
 * DO_START - temporary state when Fvid2_start() is called
 *  |         this means driver has requested CLM to start the instance
 *  |
 * RUNNING  - this is the state after Fvid2_start() completes, this means
 *  |         CLM started capture and now it is running, it remains in this
 *  |         state
 *  |         until Fvid2_stop()  is called
 *  |
 * DO_STOP  - temporary state when Fvid2_stop is called()
 *  |         this means driver has request CLM to stop the instance
 *  |
 * STOPPED  - this is the state after Fvid2_stop() completes, this means
 *  |         CLM has stopped this instance
 *  |
 * IDLE     - this is the state after Fvid2_delete() completes
 */
/** \brief Driver is not open and is idle. */
#define VPS_CAPT_STATE_IDLE             (0)
/** \brief Driver is created. */
#define VPS_CAPT_STATE_CREATED          (1)
/** \brief Driver is requesting a start. */
#define VPS_CAPT_STATE_DO_START         (2)
/** \brief Driver is running. */
#define VPS_CAPT_STATE_RUNNING          (3)
/** \brief Driver is requesting a stop. */
#define VPS_CAPT_STATE_DO_STOP          (4)
/** \brief Driver is stopped. */
#define VPS_CAPT_STATE_STOPPED          (5)

#define VPS_CAPT_CH_MAP_IDX_MAX         (VPS_CAPT_STREAM_ID_MAX *   \
                                         VPS_CAPT_CH_PER_PORT_MAX * \
                                         VPS_CAPT_INST_ID_MAX)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_CaptInstObj_t VpsDrv_CaptInstObj;

/** \brief Forward declaration for channel object. */
typedef struct VpsDrv_CaptChObj_t VpsDrv_CaptChObj;

/**
 *  struct VpsDrv_CaptQueObj
 *  \brief Structure defining the queue object used in queue/dequeue operation.
 *  Instead of creating frame objects, this is used so that any other
 *  information could be queued/dequeued along with the frame.
 *  Already qElem is added to avoid dynamic allocation of Queue nodes.
 */
typedef struct
{
    BspUtils_QElem       qElem;
    /**< BSP utils queue element used in node addition. */
    VpsDrv_CaptChObj    *chObj;
    /**< Reference to the channel object for this queue object. */
    Fvid2_Frame         *frm;
    /**< FVID2 frame to store the incoming/outgoing IO packets. */
    VpsCore_Frame        coreFrm;
    /**< Frame information as needed by the core. This is used as the core
     *   requires different frame parameters compared to #Fvid2_Frame. */
#ifdef VPS_VIP_BUILD
    VpsCore_VipCoreStats vipCoreStat;
    /**< VIP core error stats. */
#endif

    UInt32               creditCnt;
    /**< Number of times the frame is queued to the core for capture.
     *   This counter is used to determine the number of times the frame is
     *   repeated.
     *
     *   Initial value of the counter is zero.
     *   For every queue to the core the counter is incremented.
     *   For every dequeue from the core the counter is decremented.
     *   When the counter becomes 0 in dequeue from core, the frame is ready
     *   to be given to the application depending on the buffer mode
     *   selected. */
} VpsDrv_CaptQueObj;

/**
 *  struct VpsDrv_CaptBufManObj
 *  \brief Structure to store the buffer management functionality variables.
 */
typedef struct
{
    UInt32               isProgressive;
    /**< Flag to indicate whether the capture is progressive or interlaced. */
    Fvid2_BufferFormat   bufFmt;
    /**< Frame capture or field capture for interlaced scan format. */
    UInt32               fieldMerged;
    /**< This variable is used to specify whether two fields are merged for
     *   frame capture or they in separate planes. */

    UInt32               curFid;
    /**< Indicates current field ID. Used in interlaced capture. */
    UInt32               expectedFid;
    /**< Indicates the next set field expected. This is used to check if
     *   capture is occurring at proper sequence without any field misses. */

    VpsCore_Frame        dropCoreFrm;
    /**< Core frame used in case of drop frame. */

#ifdef VPS_VIP_BUILD
    VpsCore_VipCoreStats vipCoreStatDropFrm;
    /**< VIP core error stats for drop frame. */
#endif

    /*
     * Initially all the queue elements will be in freeQ.
     *
     * For every application queue operation,   freeQ -> reqQ
     * For every request submitted to core,     reqQ  -> curQ
     * For every request completion from core,  curQ  -> doneQ (per Stream)
     * For every application dequeue operation, doneQ -> freeQ
     */
    BspUtilsLinkListObj *freeQ;
    /**< Queue for queueing all the free queue objects. */
    BspUtilsLinkListObj *reqQ;
    /**< Queue object to put the input requests. */
    BspUtilsLinkListObj *curQ;
    /**< Buffers that are queued to hardware/core but not yet fully captured. */
    BspUtilsLinkListObj  freeLlObj;
    /**< Linked List object for freeQ. */
    BspUtilsLinkListObj  reqLlObj;
    /**< Linked List object for reqQ. */
    BspUtilsLinkListObj  curLlObj;
    /**< Linked List object for curQ. */
    VpsDrv_CaptQueObj    captQObj[BSP_CFG_CAPT_QUEUE_LEN_PER_CH];
    /**< Capture queue objects. */
} VpsDrv_CaptBufManObj;

/*
 * Channel specific information
 */
struct VpsDrv_CaptChObj_t
{
    VpsDrv_CaptInstObj  *instObj;
    /**< Capture instance objects pointer to which this channel belongs. */

    UInt32               chNum;
    /**< User provided channel number at create time. */
    UInt32               lChNum;
    /**< Driver logical number - is unique across all capture handles. */

    UInt32               streamId;
    /**< Stream ID index to which this channel belongs to. Used for
     *   dereferencing. */
    UInt32               chIdx;
    /**< Channel index to which this channel belongs to. Used for
     *   dereferencing. */

    UInt32               frmSkipMask;
    /**< Frame skip mask for this channel - see vps_capture.h
     *   (#Vps_CaptFrameSkip) for meaning of frameskip mask. */
    UInt32               frmSkipCount;
    /**< Current frame number that is being captured, 0..29. This will
     *   wrap after 29 and is used to skip a particular frame based on skip
     *   mask. */

#ifdef VPS_VIP_BUILD
    void                *vemSubFrmHandle;
    /**< Event manager handle - used for VEM sub-frame interrupts. */

    UInt32               subFrameNum;
    /**< Current sub-frame number in this frame,
     *   range is from 0 to (number of sub-frames in frame - 1). */
    Vps_SubFrameParams   subFrmPrms;
    /**< Sub frame parameters. */
#endif /* VPS_VIP_BUILD */

    VpsDrv_CaptBufManObj bmObj;
    /**< Channel buffer management object. */
    Vps_CaptChStatus     stat;
    /**< Channel statistics object. */

    UInt32               isStreamByPassed;
    /**< Flag that indicates if reception on this stream is optional. */
};

/**
 *  struct VpsDrv_CaptInstObj
 *  \brief Per instance information.
 */
struct VpsDrv_CaptInstObj_t
{
    UInt32                 drvInstId;
    /**< Instance ID. */
    VpsCore_Inst           coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops     *coreOps;
    /**< Core function pointers. */
    VpsCore_Property       coreProperty;
    /**< Core properties. */

    Vps_CaptCreateParams   createPrms;
    /**< Create parameters. */
    Fvid2_DrvCbParams      fdmCbPrms;
    /**< FVID2 driver manager callback function parameters. */

#ifdef VPS_VIP_BUILD
    Vps_CaptVipParams      vipPrms;
    /**< VIP parameters - valid only if it is a VIP instance. */
    Vps_CaptVipScParams    scPrms;
    /**< Scaler parameters. Used for memory allocation as input from user
     *   is a pointer. */
    Vps_VipPortConfig      vipPortCfg;
    /**< VIP Parser port config. Used for memory allocation as input from user
     *   is a pointer. */
    Vps_CscConfig          cscCfg;
    /**< CSC config. Used for memory allocation as input from user
     *   is a pointer. */
    Vps_ScCoeffParams      scCoeffCfg;
    /**< Scaler coeff config. Used for memory allocation as input from user
     *   is a pointer. */
    VpsHal_ScFactorConfig  curScFactor;
    /**< Currently configured scaling factor for this instance */
#endif

    VpsDrv_CaptChObj       chObj[VPS_CAPT_STREAM_ID_MAX]
    [VPS_CAPT_CH_PER_PORT_MAX];
    /**< Channel object's for every channel and stream. */

    UInt32                 state;
    /**< Instance state. */

    BspUtilsLinkListObj   *doneQ[VPS_CAPT_STREAM_ID_MAX];
    /**< Queue object to put the processed output requests. This is kept
     *   common for all channels of a stream because frames can be given
     *   back to application in dequeue call without looping over each
     *   channel done queue. */

    BspUtilsLinkListObj    doneLlObj[VPS_CAPT_STREAM_ID_MAX];
    /**< Linked List object for doneQ for all channels of each stream. */

    UInt32                 queueCount;
    /**< Counter to keep track of how many requests are queued to the driver. */
    UInt32                 dequeueCount;
    /**< Counter to keep track of how many requests are dequeued from the
     *  driver. */

    UInt32                 overflowCount;
    /**< Counter to keep track of overflow error per instance. */
    UInt32                 asynOverflowCount;
    /**< Counter to keep track of ASYNC FIFO overflow error per instance. */
    UInt32                 actProtViolationCount;
    /**< Counter to keep track of active video protocol violation error per
     *   instance. */
    UInt32                 ancProtViolationCount;
    /**< Counter to keep track of ancillary video protocol violation error per
     *   instance. */

    Vps_TimeStampFxn       getTimeStamp;
    /**< Get timestamp function. */

    VpsCore_Handle         coreHandle;
    /**< Core handle. */

#ifdef VPS_VIP_BUILD
    void                  *vemHandle[VPSCORE_VIP_CH_ID_MAX];
    /**< Event manager handle - used for VEM interrupts. */
    void                  *overflowVemHandle;
    /**< Event manager handle for overflow interrupts*/
#endif /* #ifdef VPS_VIP_BUILD */

    BspOsal_IntrHandle     intrHandle;
    /**< OSAL interrupt handle - used for direct interrupts. */

    BspOsal_SemHandle      lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance. */
    Vps_CaptVipOverflowFxn overflowCbFxn;
    /**<Application callback function, to be called by the overflow ISR */
    void                  *appOverFlowCbPrms;
    /**<Parameters to be passed to the overflowCbFxn */
    UInt32                 isOverflowOccured;
    /**<Variable to keep record, if the overflow on a VIP has occurred or not.*/
#ifdef VPS_CAL_BUILD
    vpsissCalFrameEventNotifyCfg_t frmEvtNotifyPrms;
    /**< Parameter that were supplied while configuring frame event
            notification */
#endif
};

/*
 * struct VpsDrv_CaptCommonObj
 * \brief Capture driver global/common driver object.
 */
typedef struct
{
    Fvid2_DrvOps        fvidDrvOps;
    /**< FVID2 driver ops. */
    UInt32              isRegistered;
    /**< FVID2 registeration complete flag. */

    UInt32              numInst;
    /**< Number of valid instance. */
    VpsDrv_CaptInstObj *instObj;
    /**< Capture instance objects pointer. */

    UInt32              fvidChNumToLogChNumMap[VPS_CAPT_CH_MAP_IDX_MAX];
    /**< User channel number to driver channel number map. */
} VpsDrv_CaptCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Global variables
 */
extern VpsDrv_CaptCommonObj gVpsCaptCommonObj;

/*
 * Process related functions
 */
void vpsDrvCaptVemIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);
void vpsDrvCaptVemOverflowIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);

void vpsDrvCaptVemSubFrmIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);
VpsCore_Frame *vpsDrvCaptCoreReqFrameCb(void  *drvData,
                                        UInt32 streamId,
                                        UInt32 chId);
Int32 vpsDrvCaptCoreFrameDoneCb(void *drvData, const VpsCore_Frame *coreFrm);

/*
 * Private functions
 */
Int32 vpsDrvCaptPrivInit(UInt32 numInst, const VpsDrv_CaptInitParams *initPrms);
Int32 vpsDrvCaptPrivDeInit(void);

VpsDrv_CaptInstObj *vpsDrvCaptGetInstObj(UInt32 instId);
Int32 vpsDrvCaptCheckParams(const VpsDrv_CaptInstObj   *instObj,
                            const Vps_CaptCreateParams *createPrms);

Int32 vpsDrvCaptCreateChObj(VpsDrv_CaptInstObj *instObj);
Int32 vpsDrvCaptDeleteChObj(VpsDrv_CaptInstObj *instObj);

UInt64 vpsDrvCaptClockGetTicks(void *args);

/*
 * Core functions
 */
Int32 vpsDrvCaptGetPropCore(VpsDrv_CaptInstObj *instObj);
Int32 vpsDrvCaptOpenCore(VpsDrv_CaptInstObj *instObj);
Int32 vpsDrvCaptCloseCore(VpsDrv_CaptInstObj *instObj);
Int32 vpsDrvCaptStartCore(VpsDrv_CaptInstObj *instObj);
Int32 vpsDrvCaptStopCore(VpsDrv_CaptInstObj *instObj);

#ifdef VPS_VIP_BUILD
Int32 vpsDrvCaptSetVipCoreParams(VpsDrv_CaptInstObj      *instObj,
                                 const Vps_CaptVipParams *vipPrms);
Int32 vpsDrvCaptGetVipCoreParams(VpsDrv_CaptInstObj *instObj,
                                 Vps_CaptVipParams  *vipPrms);
Int32 vpsDrvCaptSetVipMaxSizePrmsIoctl(
    const VpsDrv_CaptCommonObj *drvObj,
    Vps_VpdmaMaxSizeParams     *
    vipMaxFrmPrms);
#endif

#ifdef VPS_DSS_BUILD
Int32 vpsDrvCaptSetDssWbCoreParams(VpsDrv_CaptInstObj        *instObj,
                                   const Vps_CaptDssWbParams *dssWbPrms);
Int32 vpsDrvCaptSetDssWbCscCoeff(VpsDrv_CaptInstObj *instObj,
                                 void               *cscCoeff);
#endif

#ifdef VPS_CAL_BUILD
Int32 vpsDrvCaptSetIssCoreParams(VpsDrv_CaptInstObj   *instObj,
                                 const vpsissCalCfg_t *pPrms);
#ifdef VPS_ISS_BUILD
Int32 vpsDrvCaptSetIssStreamMap(VpsDrv_CaptInstObj               *instObj,
                                const vpsissCalOtfStreamMapCfg_t *pPrms);
Int32 vpsDrvCaptOtfControl(VpsDrv_CaptInstObj *instObj,
                           UInt32 cmd, Ptr cmdArgs);
#endif /* VPS_ISS_BUILD */

Int32 vpsDrvCaptSetIssErrorParams(VpsDrv_CaptInstObj   *instObj,
                                    const vpsissCalErrorCfg_t *pPrms);
Int32 vpsDrvCaptSetIssSubFrmParams(VpsDrv_CaptInstObj   *instObj,
                                const vpsissCalFrameEventNotifyCfg_t *pPrms);
#endif /* VPS_CAL_BUILD */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSDRV_CAPTURE_PRIV_H_ */
