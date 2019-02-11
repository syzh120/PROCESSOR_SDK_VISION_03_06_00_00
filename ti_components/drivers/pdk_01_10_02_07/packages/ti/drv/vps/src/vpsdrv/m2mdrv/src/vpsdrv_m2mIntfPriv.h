/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014-2015
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
 *  \file vpsdrv_m2mIntfPriv.h
 *
 *  \brief VPS M2M driver internal header file.
 */

#ifndef VPSDRV_M2MINTFPRIV_H_
#define VPSDRV_M2MINTFPRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_cfgMem.h>

#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/iss/vps_m2mIss.h>

#include <ti/drv/vps/include/vps_m2mIntf.h>
#include <m2mdrv/vpsdrv_m2mintf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Forward declaration for instance object. */
typedef struct VpsMDrv_IntfInstObj_t VpsMDrv_IntfInstObj;

/** \brief Forward declaration for handle object. */
typedef struct VpsMDrv_IntfHandleObj_t VpsMDrv_IntfHandleObj;

typedef struct
{
    BspUtils_QElem         qElem;
    /**< VPS utils queue element used in node addition. */
    VpsMDrv_IntfHandleObj *hObj;
    /**< Handle Object reference for this Queue object */
    Fvid2_FrameList        inFrmList;
    /**< FVID2 frame list for store list of input frames. */
    Fvid2_FrameList        outFrmList;
    /**< FVID2 frame list for store list of output frames. */
    VpsCore_Frame          frm[VPS_MAX_STREAMS];
    /**< Core Array of frames */
    VpsCore_Frame         *pFrm[VPS_MAX_STREAMS];
    /**< Array of VpsCore_Frame pointers,
     *   Core supports putFrame APi, which takes pointer to an array
     *   of VpsCore_frames, so Queue Object has an array of
     *   VpsCore Frame pointer */
    Int32                  statIdx;
    /**< Index used in the statistisc collector.
     *   When request is submitted to the driver, it is used as an
     *   index into statistics array to get the stat object. This stat object
     *   is used for storing different statistics. */
} VpsMDrv_IntfQueueObj;

struct VpsMDrv_IntfHandleObj_t
{
    VpsMDrv_IntfInstObj    *instObj;
    /**< Pointer to instance object */
    Vps_M2mIntfCreateParams createPrms;
    /**< Create parameters. */
    Fvid2_DrvCbParams       fdmCbPrms;
    /**< FVID2 driver manager callback function parameters. */

    BspOsal_SemHandle       ctrlSem;
    /**< Semaphore to block the control command until they are finished.
     *   This will typically used for programming coefficients where the
     *   coefficient update request is submitted to MLM and control ioctl is
     *   waiting for the coefficient request to be completed. */
    BspOsal_SemHandle       stopSyncSem;
    /**< Semaphore to block the FIVD2 stop command until the current transfer
     *   is complete. After this no further pending requests will be
     *   processed. */
    VpsCore_Handle          coreHandle[VPSMDRV_INTF_MAX_CORE];
    /**< Core handles for VWB cores. */

    BspUtils_QHandle        freeQueue;
    /**< Queue for queueing all the free queue objects for this handle. */
    BspUtils_Handle         outQueue;
    /**< Queue object to put the processed output requests. */

    UInt32                  numPendReq;
    /**< Number of pending requests to be dequeued by application once
     *   submitted to driver. */
    UInt32                  numProcessedReq;
    /**< Number of requests yet to be processed by driver. */
    UInt32                  numErrorReq;
    /**< Number of Erroroneous request */

    volatile UInt32         isStopped;
    /**< Flag to indicate if driver is being stopped, FALSE is normal operation
     *   TRUE to indicate mlmCb not to Q up new requests */
    Fvid2_FrameList         tempFrameList;
    /**< When driver is stopped, all the fields held as context fields would
     *   required to be released back to apps. On stop all the fields are copied
     *   into this frameList and put back as completed qObj. On de-q, the normal
     *   de-q operation is performed and qObj would be released.
     *   frameList required here, as qObj, has processList but not frameList.
     *   Currently assuming that we can have maximum of
     *   VPS_M2M_MAX_CH_PER_HANDLE channel at any time, so a maximum of
     *   VPS_M2M_MAX_CH_PER_HANDLE * 3 context fields requires to be
     *   released to apps. The below compilation gaurd is to ensure that. */

    Vps_M2mIntfFrameStats *frmStats;
    /**< Pointer to the array of frame statistics */
    UInt32                 curStatsIdx;
    /**< Current Index of the frame statistics */

    Vps_TimeStampFxn       tsFxn;
    /**< Timer function pointer, using which driver gets the time value */

    BspUtilsLinkListObj    freeLlObj;
    /**< Linked List object for freeQueue. */
    BspUtilsLinkListObj    outLlObj;
    /**< Linked List object for outQueue. */
    VpsMDrv_IntfQueueObj   m2mIntfQObj[BSP_CFG_M2M_INTF_QUEUE_LEN_PER_CH];
    /**< Display queue objects. */
};

struct VpsMDrv_IntfInstObj_t
{
    UInt32                drvInstId;
    /**< Driver instance ID. */
    UInt32                isMultiChSupported;
    /**< Flag to indicate if this instance supports multiple channels or not */
    UInt32                numCores;
    /**< Number of valid entries in coreInstId and coreOps */
    VpsCore_Inst          coreInstId[VPSMDRV_INTF_MAX_CORE];
    /**< Core instance number/ID. */
    const VpsCore_Ops    *coreOps[VPSMDRV_INTF_MAX_CORE];
    /**< VPE, VWB core function pointers. */

    UInt32                openCnt;
    /**< Open count. */
    UInt32                initDone;
    /**< Flag to indicate intialization is done or not for an instance. */
    UInt32                isResAllocated;
    /**< Flag to indicate if resource alloc API/IOCTL is called or not
     *   All other APIs/IOCTL can be called only after this flag is
     *   set to TRUE. */

    BspOsal_SemHandle     instSem;
    /**< Semaphore to protect the open/close calls. */

    Vps_TimeStampParams   tsPrms;
    /**< Timestamp parameters, which contains user provided function
     *   pointer for getting time stamp */

    VpsMDrv_IntfQueueObj *activeQObj;
    /**< Flag to indicate if any request is active and already
     *   submitted to hardware. */

    BspUtils_QHandle      inQueue;
    /**< Queue object to put the input requests. */

    Ptr                   drvCoreOps;
    /**< Pointer to driver core operations */

    BspUtilsLinkListObj   inLlObj;
    /**< Linked List object for inQueue. */
};

typedef struct
{
    VpsMDrv_IntfInstObj *instObj[VPS_M2M_INTF_INST_MAX];
    /**< Array of instance objects */
    UInt32               numInsts;
    /**< Number of Valid entries in instObj */
} VpsMDrv_IntfCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MINTFPRIV_H_ */

