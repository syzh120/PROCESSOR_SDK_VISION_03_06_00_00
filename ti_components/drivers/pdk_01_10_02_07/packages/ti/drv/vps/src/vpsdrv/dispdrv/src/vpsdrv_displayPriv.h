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
 *  \file vpsdrv_displayPriv.h
 *
 *  \brief Display driver private header file.
 *
 */

#ifndef VPSDRV_DISPLAY_PRIV_H_
#define VPSDRV_DISPLAY_PRIV_H_

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
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_display.h>
#include <ti/drv/vps/src/vpslib/common/vpscore.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>
#include <dispdrv/vpsdrv_display.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Minimum number of buffers needed for starting the display operation.
 */
#define VPS_DRV_DISP_MIN_PRIME_BUFFERS  (1U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsDrv_DispStates
 *  \brief Different states of the driver.
 */
typedef struct
{
    UInt32 isInit;
    /**< Flag to indicate intialization is done or not for an instance. */
    UInt32 isOpened;
    /**< Flag to indicate whether a instance is opened or not. */
    UInt32 isStarted;
    /**< Flag to indicate whether the display has started or not. */
} VpsDrv_DispStates;

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_DispInstObj_t VpsDrv_DispInstObj;

/**
 *  \brief Structure defining the queue object used in queue/dequeue operation.
 *  Instead of creating frame objects, this is used so that any other
 *  information could be queued/dequeued along with the frame.
 *  Already qElem is added to avoid dynamic allocation of Queue nodes.
 */
typedef struct
{
    BspUtils_QElem      qElem;
    /**< BSP utils queue element used in node addition. */
    VpsDrv_DispInstObj *instObj;
    /**< Reference to the instance object for this queue object. */
    Fvid2_Frame        *frm;
    /**< FVID2 frame to store the incoming/outgoing IO packets. */
    VpsCore_Frame       coreFrm;
    /**< Frame information as needed by the core. This is used as the core
     *   requires different frame parameters compared to #Fvid2_Frame. */
    UInt32              creditCnt;
    /**< Number of times the frame is queued to the core for display.
     *   This counter is used to determine the number of times the frame is
     *   repeated.
     *
     *   Initial value of the counter is zero.
     *   For every queue to the core the counter is incremented.
     *   For every dequeue from the core the counter is decremented.
     *   When the counter becomes 0 in dequeue from core, the frame is ready
     *   to be given to the application depending on the buffer mode
     *   selected. */
} VpsDrv_DispQueObj;

/**
 *  \brief Structure to store the buffer management functionality variables.
 */
typedef struct
{
    UInt32 isProgressive;
    /**< Flag to indicate whether the display is progressive or interlaced. */

    UInt32 bypassLowLatencyCheck;
    /**< TRUE  - Bypass the low latency check and directly program the
     *           buffer in hardware.
     *   FALSE - Enable low latency check - Normal operation. */

    UInt32 curFid;
    /**< Indicates current field ID. Used in interlaced display. */
    UInt32 expectedFid;
    /**< Indicates the next set field expected. This is used to check if
     *   display is occurring at proper sequence without any field misses. */

    UInt32 fieldMerged;
    /**< This variable is used to specify whether two fields are merged for
     *   frame display or they in separate planes. */

    /*
     * Initially all the queue elements will be in freeQ.
     *
     * For every application queue operation,   freeQ -> reqQ
     * For every request submitted to core,     reqQ  -> curQ
     * For every request completion from core,  curQ  -> doneQ (per Instance)
     * For every application dequeue operation, doneQ -> freeQ
     */
    BspUtilsLinkListObj *freeQ;
    /**< Queue for queueing all the free queue objects. */
    BspUtilsLinkListObj *reqQ;
    /**< Queue object to put the input requests. */
    BspUtilsLinkListObj *curQ;
    /**< Buffers that are queued to hardware/core but not yet fully
     *   displayed. */
    BspUtilsLinkListObj *doneQ;
    /**< Queue object to put the displayed output requests. */
    BspUtilsLinkListObj  freeLlObj;
    /**< Linked List object for freeQ. */
    BspUtilsLinkListObj  reqLlObj;
    /**< Linked List object for reqQ. */
    BspUtilsLinkListObj  curLlObj;
    /**< Linked List object for curQ. */
    BspUtilsLinkListObj  doneLlObj;
    /**< Linked List object for doneQ. */
    VpsDrv_DispQueObj    dispQObj[BSP_CFG_DISP_QUEUE_LEN_PER_INST];
    /**< Display queue objects. */
} VpsDrv_DispBufManObj;

/**
 *  \brief Per instance information.
 */
struct VpsDrv_DispInstObj_t
{
    UInt32               drvInstId;
    /**< Instance ID. */
    VpsCore_Inst         coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops   *coreOps;
    /**< Core function pointers. */

    VpsCore_Property     coreProperty;
    /**< Core properties. */

    Vps_DispCreateParams createPrms;
    /**< Create parameters. */
    Fvid2_DrvCbParams    fdmCbPrms;
    /**< FVID2 driver manager callback function parameters. */
    Vps_DispBufPrgmCbFxn bufPrgmCbFxn;
    /**< Buffer program callback function. */

    VpsDrv_DispStates    state;
    /**< Instance state. */

    VpsDrv_DispBufManObj bmObj;
    /**< Channel buffer management object. */

    Vps_DispStatus       stat;
    /**< Instance statistics object. */

    VpsCore_Handle       coreHandle;
    /**< Core handle. */
    UInt32               isPrevBufRep;
    /**< Flag to check if previous buffer is repeated. */
    volatile UInt32      isInIsrContext;
    /**< Flag to check if queue operation is called from the DSS ISR callback
     *   context. */

    UInt32               standard;
    /**< VENC Standard like NTSC, 1080p etc to which the display driver
     *   path is connected. For valid values see #FVID2_Standard. */

    UInt32               dispWidth;
    /**< Width of the display at the VENC in pixels to which the
     *   display driver path is connected. */

    UInt32               dispHeight;
    /**< Height of the display at the VENC in linesto which the
     *   display driver path is connected. */

    UInt32               vencId;
    /**< Venc ID to which this display instance is connected. */

    BspOsal_SemHandle    lockSem;
    /**< Semaphore to protect the open/close calls and other memory
     *   allocation per instance. */
};

/**
 *  \brief Display driver global/common driver object.
 */
typedef struct
{
    Fvid2_DrvOps        fvidDrvOps;
    /**< FVID2 driver ops. */
    UInt32              isRegistered;
    /**< FVID2 registeration complete flag. */

    UInt32              numInst;
    /**< Number of valid instance. */
    VpsDrv_DispInstObj *instObj;
    /**< Display instance objects pointer. */
} VpsDrv_DispCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/*
 * Global variables
 */
extern VpsDrv_DispCommonObj gVpsDispCommonObj;

/*
 * Process related functions
 */
VpsCore_Frame *vpsDrvDispCoreReqFrameCb(void  *drvData,
                                        UInt32 streamId,
                                        UInt32 chId);
Int32 vpsDrvDispCoreFrameDoneCb(void *drvData, const VpsCore_Frame *coreFrm);

/*
 * Private functions
 */
Int32 vpsDrvDispPrivInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms);
Int32 vpsDrvDispPrivDeInit(void);

VpsDrv_DispInstObj *vpsDrvDispGetInstObj(UInt32 instId);
Int32 vpsDrvDispCheckParams(const VpsDrv_DispInstObj   *instObj,
                            const Vps_DispCreateParams *createPrms);

Int32 vpsDrvDispCreateInstObj(VpsDrv_DispInstObj *instObj);
Int32 vpsDrvDispDeleteInstObj(VpsDrv_DispInstObj *instObj);

/*
 * Core functions
 */
Int32 vpsDrvDispOpenCore(VpsDrv_DispInstObj *instObj);
Int32 vpsDrvDispCloseCore(VpsDrv_DispInstObj *instObj);
Int32 vpsDrvDispSetDssCoreParams(VpsDrv_DispInstObj      *instObj,
                                 const Vps_DispDssParams *dssPrms);
Int32 vpsDrvDispGetDssCoreParams(VpsDrv_DispInstObj *instObj,
                                 Vps_DispDssParams  *dssPrms);
Int32 vpsDrvDispGetCoreErrStat(VpsDrv_DispInstObj        *instObj,
                               VpsCore_DssVidErrorStatus *errStatus);
Int32 vpsDrvDispStartCore(VpsDrv_DispInstObj *instObj);
Int32 vpsDrvDispStopCore(VpsDrv_DispInstObj *instObj);
Int32 vpsDrvDispSetDssCscCoeff(VpsDrv_DispInstObj    *instObj,
                               Vps_DssCscCoeff *cscCoeff);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSDRV_DISPLAY_PRIV_H_ */
