/*
 *  Copyright (c) Texas Instruments Incorporated 2017
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
 *  \file vpsdrv_m2mDssPriv.h
 *
 *  \brief VPS DSS M2M driver internal header file.
 */

#ifndef VPSDRV_M2MDSSPRIV_H_
#define VPSDRV_M2MDSSPRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_cfgMem.h>

#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dssWb.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/dss/vps_m2mDss.h>
#include <m2mdrv_dss/vpsdrv_m2mDss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_dssDispcOvly.h>

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
typedef struct VpsMDrv_DssInstObj_t VpsMDrv_DssInstObj;

/** \brief Forward declaration for handle object. */
typedef struct VpsMDrv_DssHandleObj_t VpsMDrv_DssHandleObj;

typedef struct
{
    VpsMDrv_DssInstObj         *instObj;
    /**< Pointer to instance object */
    UInt32                      pipeIdx;
    /**< Pipe index to get back the reference for which pipe the cb occurs */
} VpsMDrv_DssCoreDrvData;

typedef struct
{
    BspUtils_QElem          qElem;
    /**< VPS utils queue element used in node addition. */
    VpsMDrv_DssHandleObj   *hObj;
    /**< Handle Object reference for this Queue object */
    Fvid2_FrameList         inFrmList;
    /**< FVID2 frame list for store list of input frames. */
    Fvid2_FrameList         outFrmList;
    /**< FVID2 frame list for store list of output frames. */
    VpsCore_Frame           coreFrm[VPS_DSS_DISPC_PIPE_MAX];
    /**< Core Array of frames */
} VpsMDrv_DssQueueObj;

struct VpsMDrv_DssHandleObj_t
{
    VpsMDrv_DssInstObj         *instObj;
    /**< Pointer to instance object */
    Vps_M2mDssCreateParams      createPrms;
    /**< Create parameters. */
    Fvid2_DrvCbParams           fdmCbPrms;
    /**< FVID2 driver manager callback function parameters. */
    Vps_M2mDssParams            dssPrms;
    /**< DSS params. */
    Vps_DssDispcAdvDmaConfig    advDmaCfg[VPS_DSS_DISPC_PIPE_MAX];
    /**< Advance DMA configuraion for video/grpx pipes. */
    Vps_DssDispcVidVC1Config    vc1Cfg[VPS_DSS_DISPC_PIPE_MAX];
    /**< VC1 range config structure for video pipes. */
    Vps_DssDispcAdvDmaConfig    advDmaCfgWb;
    /**< Advance DMA configuraion for writeback pipe. */

    volatile UInt32             numPendReq;
    /**< Number of pending requests to be dequeued by application once
     *   submitted to driver. */
    volatile UInt32             numProcessedReq;
    /**< Number of requests yet to be processed by driver. */

    Vps_TimeStampFxn            tsFxn;
    /**< Timer function pointer, using which driver gets the time value */

    BspUtils_QHandle            freeQ;
    /**< Queue for queueing all the free queue objects for this handle. */
    BspUtils_QHandle            outQ;
    /**< Queue object to put the processed output requests. */
    BspUtilsLinkListObj         freeLlObj;
    /**< Linked List object for freeQ. */
    BspUtilsLinkListObj         outLlObj;
    /**< Linked List object for outQ. */
    VpsMDrv_DssQueueObj         m2mDssQObj[BSP_CFG_M2M_DSS_QUEUE_LEN_HANDLE];
    /**< Display queue objects. */
    VpsMDrv_DssCoreDrvData      drvData[VPS_DSS_DISPC_PIPE_MAX];
    /**< Core driver data for each input core. */
};

struct VpsMDrv_DssInstObj_t
{
    UInt32                  drvInstId;
    /**< Driver instance ID. */
    VpsCore_Inst            inCoreInstObj;
    /**< Input pipe core instance object used in core open. */
    const VpsCore_Ops      *inCoreOps;
    /**< Input pipe core function pointers. */
    VpsCore_Inst            outCoreInstObj;
    /**< Input pipe core instance object used in core open. */
    const VpsCore_Ops      *outCoreOps;
    /**< Input pipe core function pointers. */

    VpsCore_Handle          inCoreHandle[VPS_DSS_DISPC_PIPE_MAX];
    /**< Input pipe core handle. */
    VpsCore_Handle          outCoreHandle;
    /**< Output pipe core handle. */

    UInt32                  openCnt;
    /**< Open count. */
    UInt32                  initDone;
    /**< Flag to indicate intialization is done or not for an instance. */

    BspOsal_SemHandle       instSem;
    /**< Semaphore to protect the open/close calls. */
    VpsMDrv_DssQueueObj    *activeQObj;
    /**< Flag to indicate if any request is active and already
     *   submitted to hardware. */
    BspUtils_QHandle        inQueue;
    /**< Queue object to put the input requests. */
    BspUtilsLinkListObj     inLlObj;
    /**< Linked List object for inQueue. */
};

typedef struct
{
    UInt32                  numInsts;
    /**< Number of Valid entries in instObj */
    VpsMDrv_DssInstObj      instObj[VPS_M2M_DSS_INST_MAX];
    /**< Array of instance objects */

    VpsMDrv_DssHandleObj    handleMemPool[VPS_M2M_DSS_INST_MAX *
                                          VPS_M2M_DSS_MAX_HANDLE_PER_INST];
    /**< Memory pool for the handle objects. This memory is allocated
     *   statically and is common for all of the instance objects.
     *   Any instance can take any handle object. */
    UInt32                  handleMemFlag[VPS_M2M_DSS_INST_MAX *
                                          VPS_M2M_DSS_MAX_HANDLE_PER_INST];
    /**< The flag variable represents whether a handle object is allocated
     *   or not. */
    BspUtils_PoolParams     handlePoolPrm;
    /**< Pool params for handle memory. */
} VpsMDrv_DssCommonObj;

/** \breif DSS M2M driver common object. */
extern VpsMDrv_DssCommonObj gVpsMDrvDssCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Processing APIs */
VpsCore_Frame *vpsMdrvDssInCoreReqFrameCb(void  *drvData,
                                          UInt32 streamId,
                                          UInt32 chId);
VpsCore_Frame *vpsMdrvDssOutCoreReqFrameCb(void  *drvData,
                                           UInt32 streamId,
                                           UInt32 chId);
Int32 vpsMdrvDssProcessReq(VpsMDrv_DssInstObj *instObj,
                           const VpsMDrv_DssQueueObj *qObj);
Int32 vpsMdrvDssFrmDoneCb(void *drvData, const VpsCore_Frame *frm);

/* Core APIs */
Int32 vpsMdrvDssOpenCores(VpsMDrv_DssInstObj *instObj,
                          VpsMDrv_DssHandleObj *hObj);
Int32 vpsMdrvDssCloseCores(VpsMDrv_DssInstObj *instObj);
Int32 vpsMdrvDssSetPrmsIoctl(VpsMDrv_DssHandleObj *hObj, Ptr cmdArgs);
Int32 vpsMdrvDssSetCscCoeffIoctl(const VpsMDrv_DssHandleObj *hObj, Ptr cmdArgs);

/* Helper functions */
Int32 vpsMdrvCheckCreateArgs(const VpsMDrv_DssInstObj     *instObj,
                             const Vps_M2mDssCreateParams *createPrms);
VpsMDrv_DssInstObj *vpsMdrvDssGetInstObj(UInt32 instId);
VpsMDrv_DssHandleObj *vpsMdrvDssAllocHandleObj(
    VpsMDrv_DssInstObj           *instObj,
    const Vps_M2mDssCreateParams *createPrms,
    const Fvid2_DrvCbParams      *fdmCbPrms);
Int32 vpsMdrvDssFreeHandleObj(VpsMDrv_DssHandleObj *hObj);
VpsCore_Handle vpsMdrvDssGetInCoreHandle(const VpsMDrv_DssHandleObj *hObj,
                                         UInt32 inPipeId);

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MDSSPRIV_H_ */
