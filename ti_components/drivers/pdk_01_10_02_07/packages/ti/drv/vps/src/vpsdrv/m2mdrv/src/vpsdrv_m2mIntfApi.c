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
 *  \file vpsdrv_m2mIntfApi.c
 *
 *  \brief VPS M2M common interface driver.
 *  This file implements the generic M2M driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <vpsdrv_m2mIntfPriv.h>
#include <vpsdrv_m2mIntfCore.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*  VpsMdrv_m2mIntfCreate
 *
 *  \brief Opens FVID2 M2M driver. This function allocates the resources,
 *         opens the core, allocates the handle object and returns
 *         FVID handle to the driver
 *
 *         Before Creating FVID2 driver for an instance, instances must be
 *         initialized.
 *
 *  \param drvId            M2M Driver Id
 *  \param instId           M2M Driver instance
 *  \param createArgs       Pointer to the structure #Vps_M2mIntfCreateArgs
 *  \param createStatusArgs Pointer to the structure
 *                          #Vps_M2mIntfCreateStatusArgs
 *  \param fdmCbPrms        FVID2 Callback parameters
 *
 *  \return                 return Handle to the driver on success
 *                          or NULL
 */
static Fdrv_Handle VpsMdrv_m2mIntfCreate(
    UInt32                   drvId,
    UInt32                   instId,
    Ptr                      createArgs,
    Ptr                      createStatusArgs,
    const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 VpsMdrv_m2mIntfDelete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 VpsMdrv_m2mIntfControl(
    Fdrv_Handle handle,
    UInt32      cmd,
    Ptr         cmdArgs,
    Ptr         cmdStatusArgs);
static Int32 VpsMdrv_m2mIntfProcessRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList);
static Int32 VpsMdrv_m2mIntfGetProcessedRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList,
    UInt32           timeout);
#ifdef __cplusplus
}
#endif

static Int32 vpsMdrvIntfInit(
    UInt32                           numInst,
    const VpsMdrv_M2mIntfInitParams *initPrms);
static Int32 vpsMdrvIntfDeInit(void *arg);
static Int32 vpsMdrvCheckCreateArgs(
    const VpsMDrv_IntfInstObj     *instObj,
    const Vps_M2mIntfCreateParams *createPrms);

static VpsMDrv_IntfInstObj *vpsMdrvIntfGetInstObj(UInt32 instId);
static VpsMDrv_IntfHandleObj *vpsMdrvIntfAllocHandleObj(
    VpsMDrv_IntfInstObj           *instObj,
    const Vps_M2mIntfCreateParams *createPrms,
    const Fvid2_DrvCbParams       *fdmCbPrms);
static Int32 vpsMdrvIntfFreeHandleObj(VpsMDrv_IntfHandleObj *hObj);

static Int32 vpsMdrvIntfAllocStatsObj(VpsMDrv_IntfHandleObj *hObj);

static Int32 vpsMdrvIntfSetStatsParams(
    const VpsMDrv_IntfInstObj    *instObj,
    VpsMDrv_IntfHandleObj        *hObj,
    const Vps_M2mIntfStatsParams *statsPrms);
static Int32 vpsMdrvIntfGetStats(
    const VpsMDrv_IntfInstObj   *instObj,
    const VpsMDrv_IntfHandleObj *hObj,
    Vps_M2mIntfStats            *stats);
static Int32 vpsMdrvIntfResetStats(
    VpsMDrv_IntfInstObj   *instObj,
    VpsMDrv_IntfHandleObj *hObj);

static Int32 vpsMdrvIntfOpenCores(
    VpsMDrv_IntfHandleObj         *hObj,
    const Vps_M2mIntfCreateParams *createPrms,
    Vps_M2mIntfCreateStatus       *createStatus);
static Int32 vpsMdrvIntfCloseCores(VpsMDrv_IntfHandleObj *hObj);

Int32 vpsMdrvIntfFrmDoneNotifyCb(void *drvData);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \breif M2M driver function pointer. */
static const Fvid2_DrvOps    VpsMdrvIntfOps =
{
    FVID2_VPS_COMMON_M2M_INTF_DRV,      /* Driver ID */
    &VpsMdrv_m2mIntfCreate,             /* Create */
    &VpsMdrv_m2mIntfDelete,             /* Delete */
    &VpsMdrv_m2mIntfControl,            /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    &VpsMdrv_m2mIntfProcessRequest,     /* ProcessRequest */
    &VpsMdrv_m2mIntfGetProcessedRequest /* GetProcessedRequest */
};

static VpsMDrv_IntfCommonObj gVpsMDrvIntfCommonObj;
static VpsMDrv_IntfInstObj   gVpsMDrvIntfInstObj[VPS_M2M_INTF_INST_MAX];

/** \brief M2M Drv Intf Handle Objects */
static VpsMDrv_IntfHandleObj gVpsMDrvIntfHandleMemPool[VPS_M2M_INTF_INST_MAX *
                                                       VPS_M2M_INTF_MAX_HANDLE_PER_INST
];

/** \brief Pool parameters for M2M Drv Intf Handle Objects pool memory */
static BspUtils_PoolParams   gVpsMDrvIntfHandlePoolParams;

/**
 *  \brief The flag variable represents whether a given context object is
 *  allocated or not
 */
static UInt32 gVpsMDrvIntfHandleMemFlag[VPS_M2M_INTF_INST_MAX *
                                        VPS_M2M_INTF_MAX_HANDLE_PER_INST];

/* Moved from header file to here Misra changes */
const VpsMDrv_M2mCoreOps     gVpsMDrvIntfCoreOps[] =
{
#ifdef VPS_ISS_BUILD
    {VPS_M2M_ISS_INST_CAL_ISP, &vpsMdrvIssSubmitReq,    &vpsMdrvIssControl   },
#endif
#ifdef VPS_SIMCOP_BUILD
    {VPS_M2M_ISS_INST_SIMCOP,  &vpsMdrvSimcopSubmitReq, &vpsMdrvSimcopControl},
#endif
#ifdef VPS_ISS_CALM2M_BUILD
    {VPS_M2M_ISS_INST_CALM2M,    &vpsMdrvCalm2mSubmitReq, &vpsMdrvCalm2mControl},
#endif
};

/* ========================================================================== */
/*                          FVID2 API Functions                               */
/* ========================================================================== */

/**
 *  VpsMdrv_intfInit
 *  \brief M2M driver init function.
 *  Initializes driver objects, allocates memory etc.
 *  This function should be called before calling any of M2M driver API.
 *
 *  \param numInst      Number of instance objects to be initialized.
 *  \param initPrms     Pointer to the instance parameter containing
 *                      instance specific information. If the number of
 *                      instance is greater than 1, then this pointer
 *                      should point to an array of init parameter
 *                      structure of size numInst.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_intfInit(UInt32                           numInst,
                       const VpsMdrv_M2mIntfInitParams *initPrms)
{
    Int32 status = FVID2_SOK;

    /* Check for errors */
    GT_assert(VpsMDrvTrace, (NULL != initPrms));

    /* Initialize the internal objects */
    status = vpsMdrvIntfInit(numInst, initPrms);
    if (FVID2_SOK == status)
    {
        /* Register the driver to the driver manager */
        status = Fvid2_registerDriver(&VpsMdrvIntfOps);
        if (FVID2_SOK != status)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Uninitialize the internal objects if error occurs */
            vpsMdrvIntfDeInit(NULL);
        }
    }

    return (status);
}

/**
 *  VpsMdrv_intfDeInit
 *  \brief M2M driver exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_intfDeInit(void)
{
    Int32 status = FVID2_SOK;

    /* Unregister from driver manager */
    status = Fvid2_unRegisterDriver(&VpsMdrvIntfOps);
    if (FVID2_SOK != status)
    {
        GT_0trace(VpsMDrvTrace, GT_ERR,
                  "Unregistering from FVID2 driver manager failed\r\n");
    }

    /* Uninitialize the internal objects */
    status += vpsMdrvIntfDeInit(NULL);

    return (status);
}

/**
 *  VpsMdrv_m2mIntfCreate
 *  \brief M2M driver create function.
 *  Opens an instance of the driver, opens the associated cores.
 *
 *  \return             Returns FVID2_Handle on success else returns NULL.
 */
static Fdrv_Handle VpsMdrv_m2mIntfCreate(
    UInt32                   drvId,
    UInt32                   instId,
    Ptr                      createArgs,
    Ptr                      createStatusArgs,
    const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 status = FVID2_SOK, tempstatus;
    VpsMDrv_IntfInstObj     *instObj      = NULL;
    Vps_M2mIntfCreateParams *createPrms   = NULL;
    Vps_M2mIntfCreateStatus *createStatus = NULL;
    VpsMDrv_IntfHandleObj   *hObj         = NULL;

    /* Check for the NULL pointer */
    if ((NULL == createArgs) ||
        (NULL == createStatusArgs) ||
        (NULL == fdmCbPrms))
    {
        GT_0trace(VpsMDrvTrace, GT_ERR, "NULL pointer\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        /* Get Instance Object */
        instObj = vpsMdrvIntfGetInstObj(instId);

        if (NULL == instObj)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR, "Wrong instance id\r\n");
            status = FVID2_EINVALID_PARAMS;
        }
        else
        {
            /* This instance is not initialized */
            if (FALSE == instObj->initDone)
            {
                GT_0trace(VpsMDrvTrace, GT_ERR,
                          "Not Initialized Instance id\r\n");

                instObj = NULL;
                status  = FVID2_EINVALID_PARAMS;
            }
        }
    }

    /* Instance object is not null and it is initialized,
     * If it is not the case, instObj will be set to NULL. */
    if (NULL != instObj)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->instSem, BSP_OSAL_WAIT_FOREVER);
    }

    if (FVID2_SOK == status)
    {
        /* Check if a instance is opened more than the supported handles */
        if (instObj->openCnt >= VPS_M2M_INTF_MAX_HANDLE_PER_INST)
        {
            GT_1trace(VpsMDrvTrace, GT_ERR,
                      "Only %d handles supported per instance!\r\n",
                      VPS_M2M_INTF_MAX_HANDLE_PER_INST);
            status = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == status)
    {
        createPrms   = (Vps_M2mIntfCreateParams *) createArgs;
        createStatus = (Vps_M2mIntfCreateStatus *) createStatusArgs;
        status       = vpsMdrvCheckCreateArgs(instObj, createPrms);
    }

    /* Allocate Handle Object */
    if (FVID2_SOK == status)
    {
        hObj = vpsMdrvIntfAllocHandleObj(instObj, createPrms, fdmCbPrms);
    }

    /* Open Cores */
    if (FVID2_SOK == status)
    {
        status = vpsMdrvIntfOpenCores(hObj, createPrms, createStatus);
    }

    if (FVID2_SOK == status)
    {
        /* Allocate the memory for storing statistics */
        status = vpsMdrvIntfAllocStatsObj(hObj);
    }

    if (FVID2_SOK == status)
    {
        /* Increment the count to keep track of number of handles opened */
        instObj->openCnt++;
    }
    else
    {
        /* Deallocate if error occurs */
        if (NULL != hObj)
        {
            /* Free allocated handle object */
            tempstatus = vpsMdrvIntfFreeHandleObj(hObj);

            /* Already returning null handle, ie Create fail, so no need
             * to return this error
             * Also this function returns always success unless handle
             * object is null */
            GT_assert(VpsMDrvTrace, (FVID2_SOK == tempstatus));
            hObj = NULL;
        }
    }

    /* Return the status if possible */
    if (NULL != createStatus)
    {
        BspUtils_memset(createStatus, 0x0, sizeof (Vps_M2mIntfCreateStatus));

        createStatus->retVal = status;
        if (FVID2_SOK == status)
        {
            createStatus->maxHandles = VPS_M2M_INTF_MAX_HANDLE_PER_INST;

            /* Multi Channel open is supported */
            if (TRUE == instObj->isMultiChSupported)
            {
                createStatus->maxChPerHandle = VPS_M2M_INTF_MAX_CH_PER_HANDLE;
            }
            else
            {
                createStatus->maxChPerHandle = 1U;
            }
        }
    }

    if (NULL != instObj)
    {
        /* Release the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return ((Fdrv_Handle) hObj);
}

/**
 *  VpsMdrv_m2mIntfDelete
 *  \brief M2M driver delete function.
 *  closes an instance of the driver, closes the associated cores, cleansup
 *  handle object.
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mIntfDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 status = FVID2_SOK, tempstatus;
    VpsMDrv_IntfInstObj   *instObj = NULL;
    VpsMDrv_IntfHandleObj *hObj    = NULL;

    if (NULL == handle)
    {
        GT_0trace(VpsMDrvTrace, GT_ERR, "NULL pointer\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_IntfHandleObj *) handle;
        if (NULL == hObj->instObj)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR, "NULL pointer\n");
            status = FVID2_EBADARGS;
        }
        else
        {
            instObj = hObj->instObj;
        }
    }

    if (NULL != instObj)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->instSem, BSP_OSAL_WAIT_FOREVER);
    }

    if (FVID2_SOK == status)
    {
        /* Check if still some request are pending with driver */
        if (0U != hObj->numPendReq)
        {
            GT_1trace(
                VpsMDrvTrace, GT_ERR,
                "Still %d request pending. Dequeue all before closing!!\r\n",
                hObj->numPendReq);

            /* Size of outQueue and num of pending requests must be same,
             * if they are not same, there is some corruption, so asserting
             * here. */
            GT_assert(VpsMDrvTrace,
                      (hObj->numPendReq == BspUtils_getNumQElem(hObj->outQueue)));
            status = FVID2_EAGAIN;
        }
    }

    if (FVID2_SOK == status)
    {
        /* All handles are already closed */
        if (0U == instObj->openCnt)
        {
            status = FVID2_EFAIL;
        }
        else
        {
            /* Close the opened cores */
            tempstatus = vpsMdrvIntfCloseCores(hObj);
            /* TODO: Can we do anything when closing of core fails */
            GT_assert(VpsMDrvTrace, (FVID2_SOK == tempstatus));

            /* Free allocated handle object */
            tempstatus = vpsMdrvIntfFreeHandleObj(hObj);
            /* TODO: Can we do anything when this fails */
            GT_assert(VpsMDrvTrace, (FVID2_SOK == tempstatus));

            /* Decrement number of handle open count */
            instObj->openCnt--;

            /* For the last instance, unregister and
             * deallocate resource */
            if (0U == instObj->openCnt)
            {
                /* TODO: Free up the resources if there are any */
            }

            hObj = NULL;
        }
    }

    if (NULL != instObj)
    {
        /* release the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return (status);
}

/**
 *  VpsMdrv_m2mIntfControl
 *  \brief M2M driver control function.
 *  Processes driver specific control commands, calls core whenever required.
 *
 *  Caution: All ioctls are protected using instance semaphore, so these ioctls
 *  cannot be called from ISR context.
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mIntfControl(Fdrv_Handle handle,
                                    UInt32      cmd,
                                    Ptr         cmdArgs,
                                    Ptr         cmdStatusArgs)
{
    Int32 status = FVID2_SOK;
    VpsMDrv_IntfInstObj   *instObj    = NULL;
    VpsMDrv_IntfHandleObj *hObj       = NULL;
    VpsMDrv_M2mCoreOps    *drvCoreOps = NULL;

    /* Check for NULL pointers */
    if (NULL == handle)
    {
        GT_0trace(VpsMDrvTrace, GT_ERR, "Handle NULL pointer\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_IntfHandleObj *) handle;
        if (NULL == hObj->instObj)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR,
                      "Instance Object NULL pointer\n");
            status = FVID2_EBADARGS;
        }
        else
        {
            instObj = hObj->instObj;
        }
    }

    if (NULL != instObj)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->instSem, BSP_OSAL_WAIT_FOREVER);
    }

    if (FVID2_SOK == status)
    {
        switch (cmd)
        {
            case IOCTL_VPS_M2M_INTF_ABORT:
                break;

            case IOCTL_VPS_M2M_INTF_SET_STATS_PARAMS:
                status = vpsMdrvIntfSetStatsParams(
                    instObj,
                    hObj,
                    (Vps_M2mIntfStatsParams *) cmdArgs);
                break;

            case IOCTL_VPS_M2M_INTF_GET_STATS:
                status = vpsMdrvIntfGetStats(
                    instObj,
                    hObj,
                    (Vps_M2mIntfStats *) cmdArgs);
                break;

            case IOCTL_VPS_M2M_INTF_RESET_STATS:
                status = vpsMdrvIntfResetStats(instObj, hObj);
                break;

            /* Set the App provided timer function,
             * If the timer function is not provided, driver uses OSAL layer
             * timer function to get time in micro seconds */
            case IOCTL_VPS_REGISTER_TIMESTAMP_FXN:
                if (NULL != cmdArgs)
                {
                    BspUtils_memcpy(
                        &instObj->tsPrms,
                        (Vps_TimeStampParams *) cmdArgs,
                        sizeof (Vps_TimeStampParams));

                    /* By default, use OSAL layer API to get the timer ticks */
                    if (NULL == instObj->tsPrms.timeStampFxn)
                    {
                        instObj->tsPrms.timeStampFxn =
                            (Vps_TimeStampFxn) (&BspOsal_getCurTimeInMsec);
                    }
                }
                else
                {
                    status = FVID2_EBADARGS;
                }
                break;

            /* Driver specific ioctls */
            default:
                /* This pointer should not be null */
                GT_assert(VpsMDrvTrace, (NULL != instObj->drvCoreOps));
                drvCoreOps = (VpsMDrv_M2mCoreOps *) instObj->drvCoreOps;

                /* Driver specific submit request */
                if (NULL != drvCoreOps->control)
                {
                    status = drvCoreOps->control(
                        hObj,
                        cmd,
                        cmdArgs,
                        cmdStatusArgs);
                }
                else
                {
                    status = FVID2_EUNSUPPORTED_CMD;
                }
                break;
        }
    }

    if (NULL != instObj)
    {
        /* Release the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return (status);
}

/**
 *  VpsMdrv_m2mIntfProcessRequest
 *  \brief M2M driver process request.
 *  Processes single channel M2M processing request
 *
 *  This api can be called from the ISR context
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mIntfProcessRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList)
{
    Int32  status = FVID2_SOK;
    UInt32 cookie;
    VpsMDrv_IntfInstObj   *instObj    = NULL;
    VpsMDrv_IntfHandleObj *hObj       = NULL;
    VpsMDrv_IntfQueueObj  *qObj       = NULL;
    VpsMDrv_M2mCoreOps    *drvCoreOps = NULL;
    Vps_M2mIntfFrameStats *frmStat    = NULL;

    /* Check for NULL pointers */
    if (NULL == handle)
    {
        GT_0trace(VpsMDrvTrace, GT_ERR, "handle NULL pointer\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_IntfHandleObj *) handle;
        if (NULL == hObj->instObj)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR, "Instance Object NULL pointer\n");
            status = FVID2_EBADARGS;
        }
        else
        {
            instObj = hObj->instObj;

            if (hObj->createPrms.chInQueueLength <= hObj->numPendReq)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                          "Trying to submit more frame than allocated.\
                          Try again after dequeuing some frames!!\r\n");

                instObj = NULL;
                status  = FVID2_EAGAIN;
            }
        }
    }

    /* No need to disable interrupts in case of error condition */
    if (NULL != instObj)
    {
        /* Disable global interrupts */
        cookie = BspOsal_disableInterrupt();
    }

    if (FVID2_SOK == status)
    {
        /* Get a queue object from the free queue */
        qObj = (VpsMDrv_IntfQueueObj *) BspUtils_dequeue(hObj->freeQueue);

        if (NULL == qObj)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                      "Failed to allocate queue object. Try again!!\r\n");
            status = FVID2_EAGAIN;
        }
        else
        {
            qObj->hObj = hObj;
            /* Copy the application's process list to request objects lists */
            Fvid2_copyFrameList(&qObj->inFrmList, inFrmList);
            Fvid2_copyFrameList(&qObj->outFrmList, outFrmList);

            /* Initialize qObject */
            qObj->statIdx = (-((Int32) 1));

            /* Get the statistics, if they are enabled */
            if ((NULL != hObj->tsFxn) &&
                (hObj->curStatsIdx < hObj->createPrms.maxStatsInst))
            {
                /* This pointer should not be null */
                GT_assert(VpsMDrvTrace, (NULL != hObj->frmStats));

                frmStat = hObj->frmStats + hObj->curStatsIdx;

                /* ProcessRequest can be called from the ISR context, so
                 * timer function should not be blocked */
                frmStat->queueTimeStamp = hObj->tsFxn(NULL);

                /* Store the current Index in the Queue Object */
                qObj->statIdx = hObj->curStatsIdx;
            }
        }
    }

    if (FVID2_SOK == status)
    {
        if (NULL != instObj->activeQObj)
        {
            /* Another request is already active, so enqueue this request
             * in the input queue */
            BspUtils_queue(instObj->inQueue, &qObj->qElem, qObj);
        }
        else
        {
            /* Driver specific submit request */
            /* This pointer should not be null */
            GT_assert(VpsMDrvTrace, (NULL != instObj->drvCoreOps));
            drvCoreOps = (VpsMDrv_M2mCoreOps *) instObj->drvCoreOps;

            if ((NULL != hObj->tsFxn) &&
                ((-((Int32) 1)) != qObj->statIdx))
            {
                /* TODO: Move it outside of disable Interrupt */
                /* This pointer should not be null */
                GT_assert(VpsMDrvTrace, (NULL != hObj->frmStats));

                frmStat = hObj->frmStats + qObj->statIdx;

                /* ProcessRequest can be called from the ISR context, so
                 * timer function should not be blocked */
                frmStat->startProcTimeStamp = hObj->tsFxn(NULL);
            }

            /* Driver specific submit request */
            if (NULL != drvCoreOps->submitReq)
            {
                status = drvCoreOps->submitReq(hObj, qObj);
            }
            else
            {
                GT_0trace(VpsMDrvTrace, GT_ERR,
                          "No Core Function to submit the request\r\n");
                status = FVID2_EFAIL;
            }

            if (FVID2_SOK == status)
            {
                instObj->activeQObj = qObj;

                /* In all the cases, start Index will not be -1, so
                 * increment current statistics index. */
                if ((-((Int32) 1)) != qObj->statIdx)
                {
                    /* Move to next object */
                    hObj->curStatsIdx++;
                }
            }
            else
            {
                qObj->statIdx = (-((Int32) 1));
                /* Return Queue object back to free queue */
                BspUtils_queue(hObj->freeQueue, &qObj->qElem, qObj);
            }
        }
    }

    if (FVID2_SOK == status)
    {
        hObj->numPendReq++;
    }

    if (NULL != instObj)
    {
        /* Enable Interrupts,
         * TODO: Enable only ISS interrupts */
        BspOsal_restoreInterrupt(cookie);
    }

    return (status);
}

/**
 *  VpsMdrv_m2mIntfGetProcessedRequest
 *  \brief M2M driver get processed request.
 *  Returns completed processed request.
 *
 *  This api can be called from the ISR context
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mIntfGetProcessedRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList,
    UInt32           timeout)
{
    Int32  status = FVID2_SOK;
    UInt32 cookie;
    VpsMDrv_IntfHandleObj *hObj    = NULL;
    VpsMDrv_IntfQueueObj  *qObj    = NULL;
    Vps_M2mIntfFrameStats *frmStat = NULL;

    /* Check for NULL pointers */
    if ((NULL == handle) || (NULL == inFrmList) || (NULL == outFrmList))
    {
        GT_0trace(VpsMDrvTrace, GT_ERR, "Handle NULL pointer\n");
        status = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_IntfHandleObj *) handle;
    }

    if (FVID2_SOK == status)
    {
        /* Disable global interrupts. */
        cookie = BspOsal_disableInterrupt();

        /* Dequeue the completed request from done queue */
        qObj = (VpsMDrv_IntfQueueObj *) BspUtils_dequeue(hObj->outQueue);
        if (NULL == qObj)
        {
            /* Check if requests are pending with driver */
            if (0U == hObj->numPendReq)
            {
                /* Nothing is queued */
                GT_0trace(
                    VpsMDrvTrace, GT_DEBUG,
                    "Nothing to dequeue. No request pending with driver!!\r\n");
                status = FVID2_ENO_MORE_BUFFERS;
            }
            else
            {
                /* If no request have completed, return try again */
                GT_0trace(VpsMDrvTrace, GT_DEBUG,
                          "Nothing to dequeue. Try again!!\r\n");
                status = FVID2_EAGAIN;
            }
        }
        else
        {
            /* Copy the driver's process list to application's process list */
            Fvid2_copyFrameList(inFrmList, &qObj->inFrmList);
            Fvid2_copyFrameList(outFrmList, &qObj->outFrmList);

            /* Return back the queue object to the free queue */
            /* If the Timer function pointer is not null, then statistics
             * collection is enabled */
            if ((NULL != hObj->tsFxn) &&
                ((-((Int32) 1)) != qObj->statIdx))
            {
                /* This pointer should not be null */
                GT_assert(VpsMDrvTrace, (NULL != hObj->frmStats));

                frmStat = hObj->frmStats + qObj->statIdx;

                /* GetProcessRequest can be called from the ISR context, so
                 * timer function should not be blocked */
                frmStat->dequeueTimeStamp = hObj->tsFxn(NULL);
            }

            BspUtils_queue(hObj->freeQueue, &qObj->qElem, qObj);

            /* Decrement the pending request count. */
            if (0U != hObj->numPendReq)
            {
                hObj->numPendReq--;
            }
        }

        /* Enable Interrupts,
         * TODO: Enable only ISS interrupts */
        BspOsal_restoreInterrupt(cookie);
    }

    return (status);
}

/* ========================================================================== */
/*                          Internal Functions                                */
/* ========================================================================== */

/*
 *  Allocates the instance object and initializes it.
 */
static Int32 vpsMdrvIntfInit(
    UInt32                           numInst,
    const VpsMdrv_M2mIntfInitParams *initPrms)
{
    Int32  status = FVID2_SOK;
    UInt32 instCnt;
    UInt32 cnt, opsCnt;
    VpsMDrv_IntfInstObj *instObj = NULL;

    /* Error Checking */
    if (numInst >= VPS_M2M_INTF_INST_MAX)
    {
        status = FVID2_EOUT_OF_RANGE;
    }
    if (NULL == initPrms)
    {
        status = FVID2_EBADARGS;
    }

    /* Check for errors in the init params */
    for (instCnt = 0U; (instCnt < numInst) && (FVID2_SOK == status); instCnt++)
    {
        /* At least, one core required for each instance */
        if ((0U == initPrms[instCnt].numCores) ||
            (VPSMDRV_INTF_MAX_CORE <= initPrms[instCnt].numCores))
        {
            GT_0trace(
                VpsMDrvTrace, GT_ERR,
                "Invalid value of numCores!!\r\n");
            status = FVID2_EINVALID_PARAMS;
            break;
        }

        /* Core ops should not be null */
        for (cnt = 0U; cnt < initPrms[instCnt].numCores; cnt++)
        {
            if (NULL == initPrms[instCnt].coreOps[cnt])
            {
                status = FVID2_EBADARGS;
                break;
            }
        }
    }

    if (FVID2_SOK == status)
    {
        BspUtils_memset(
            &gVpsMDrvIntfCommonObj,
            0x0U,
            sizeof (VpsMDrv_IntfCommonObj));

        for (instCnt = 0U; (instCnt < numInst) && (FVID2_SOK == status);
             instCnt++)
        {
            /* Assign memory for all instance objects */
            gVpsMDrvIntfCommonObj.instObj[instCnt] =
                &gVpsMDrvIntfInstObj[instCnt];
            if (FVID2_SOK == status)
            {
                instObj = gVpsMDrvIntfCommonObj.instObj[instCnt];

                BspUtils_memset(
                    instObj,
                    0x0U,
                    sizeof (VpsMDrv_IntfInstObj));

                /* Copy Core Instance Id and Core operation pointer to
                 * instance object */
                instObj->isMultiChSupported =
                    initPrms[instCnt].isMultiChSupported;
                instObj->drvInstId = initPrms[instCnt].drvInstId;
                instObj->numCores  = initPrms[instCnt].numCores;
                for (cnt = 0U; cnt < initPrms[instCnt].numCores; cnt++)
                {
                    instObj->coreInstId[cnt] =
                        initPrms[instCnt].coreInstId[cnt];
                    instObj->coreOps[cnt] = initPrms[instCnt].coreOps[cnt];
                }

                instObj->instSem = BspOsal_semCreate((Int32) 1U, (Bool) TRUE);
                if (NULL == instObj->instSem)
                {
                    GT_0trace(VpsMDrvTrace, GT_ERR,
                              "Instance semaphore create failed!!\r\n");
                    status = FVID2_EALLOC;
                }
                if (FVID2_SOK == status)
                {
                    /* Create the different queues - request, done and free
                     * queues
                     * Assumes BspUtils are already initialized */
                    status = BspUtils_constructQ(&instObj->inLlObj);
                    GT_assert(VpsMDrvTrace, (status == BSP_SOK));
                    instObj->inQueue = &instObj->inLlObj;

                    if (FVID2_SOK == status)
                    {
                        for (opsCnt = 0U; opsCnt <
                             (sizeof (gVpsMDrvIntfCoreOps) /
                              sizeof (VpsMDrv_M2mCoreOps));
                             opsCnt++)
                        {
                            if (instObj->drvInstId ==
                                gVpsMDrvIntfCoreOps[opsCnt].drvInstId)
                            {
                                instObj->drvCoreOps = (Ptr) &
                                                      gVpsMDrvIntfCoreOps[
                                    opsCnt];
                            }
                        }

                        /* By default, use OSAL layer API to get the timer ticks
                        **/
                        instObj->tsPrms.timeStampFxn =
                            (Vps_TimeStampFxn) (&BspOsal_getCurTimeInMsec);
                        instObj->isResAllocated = (UInt32) FALSE;
                        instObj->initDone       = (UInt32) TRUE;
                    }
                }
            }
            if (FVID2_SOK != status)
            {
                break;
            }
        }
    }

    if (FVID2_SOK == status)
    {
        /* init M2M Drv Intf Handle Objects pool */
        BspUtils_initPool(
            &gVpsMDrvIntfHandlePoolParams,
            (void *) gVpsMDrvIntfHandleMemPool,
            VPS_M2M_INTF_INST_MAX *
            VPS_M2M_INTF_MAX_HANDLE_PER_INST,
            sizeof (VpsMDrv_IntfHandleObj),
            gVpsMDrvIntfHandleMemFlag,
            VpsMDrvTrace);
    }

    if (FVID2_SOK != status)
    {
        vpsMdrvIntfDeInit(NULL);
    }
    else
    {
        gVpsMDrvIntfCommonObj.numInsts = numInst;
    }

    return (status);
}

static Int32 vpsMdrvIntfDeInit(void *arg)
{
    Int32  status = FVID2_SOK;
    UInt32 instCnt;
    VpsMDrv_IntfInstObj *instObj = NULL;

    for (instCnt = 0U; instCnt < VPS_M2M_INTF_INST_MAX; instCnt++)
    {
        instObj = gVpsMDrvIntfCommonObj.instObj[instCnt];

        if (NULL != instObj)
        {
            /* Check if any handle is opened or not */
            if (0U != instObj->openCnt)
            {
                GT_2trace(VpsMDrvTrace, GT_ERR,
                          "%d handles of driver inst %d not closed!\r\n",
                          instObj->openCnt,
                          instCnt);
                status = FVID2_EDRIVER_INUSE;
                break;
            }

            if (NULL != instObj->inQueue)
            {
                /* Input Queue must be empty */
                GT_assert(VpsMDrvTrace,
                          ((UInt32) TRUE ==
                           BspUtils_isQEmpty(instObj->inQueue)));

                /* Delete the input/request Q */
                BspUtils_destructQ(instObj->inQueue);
                instObj->inQueue = NULL;
            }

            /* Free up instance semaphore */
            if (NULL != instObj->instSem)
            {
                BspOsal_semDelete(&instObj->instSem);
                instObj->instSem = NULL;
            }

            BspUtils_memset(instObj, 0x0U, sizeof (VpsMDrv_IntfInstObj));

            gVpsMDrvIntfCommonObj.instObj[instCnt] = NULL;
        }
        gVpsMDrvIntfCommonObj.numInsts = 0U;
    }

    return (status);
}

/**
 *  vpsMdrvIntfGetInstObj
 *  Returns the instance object pointer for the instance id.
 */
static VpsMDrv_IntfInstObj *vpsMdrvIntfGetInstObj(UInt32 instId)
{
    UInt32 instCnt;
    VpsMDrv_IntfInstObj *instObj = NULL;

    /* Find out the instance to which this channel belongs to */
    for (instCnt = 0U; instCnt < VPS_M2M_INTF_INST_MAX; instCnt++)
    {
        if ((gVpsMDrvIntfCommonObj.instObj[instCnt] != NULL) &&
            (gVpsMDrvIntfCommonObj.instObj[instCnt]->drvInstId == instId))
        {
            instObj = gVpsMDrvIntfCommonObj.instObj[instCnt];
            break;
        }
    }

    return (instObj);
}

static Int32 vpsMdrvCheckCreateArgs(
    const VpsMDrv_IntfInstObj     *instObj,
    const Vps_M2mIntfCreateParams *createPrms)
{
    Int32 status = FVID2_SOK;

    if ((NULL == instObj) ||
        (NULL == createPrms))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        /* For non-multichannel instances, number of channels must be 1
         * For multi channel instances, it must be less than
         *  VPS_M2M_INTF_MAX_CH_PER_HANDLE */
        if ((createPrms->numCh <= 0U) ||
            ((FALSE == instObj->isMultiChSupported) &&
             (createPrms->numCh > 1U)) ||
            ((TRUE == instObj->isMultiChSupported) &&
             (createPrms->numCh >= VPS_M2M_INTF_MAX_CH_PER_HANDLE)))
        {
            GT_1trace(VpsMDrvTrace, GT_ERR,
                      "Invalid number of channels(%d)\r\n", createPrms->numCh);

            status = FVID2_EINVALID_PARAMS;
        }

        if ((createPrms->chInQueueLength <= 0U) ||
            (createPrms->chInQueueLength > VPS_M2M_INTF_DEF_QUEUE_LEN_PER_CH))
        {
            GT_1trace(VpsDrvCaptTrace, GT_ERR,
                      "Invalid in queue length(%d)\r\n",
                      createPrms->chInQueueLength);
            status = FVID2_EINVALID_PARAMS;
        }
    }

    return (status);
}

/**
 *  vpsMdrvIntfAllocHandleObj
 *  Allocates handle object and all other memories of the handle like handle
 *  queuesetc.
 *  Returns the handle object pointer on success else returns NULL.
 */
static VpsMDrv_IntfHandleObj *vpsMdrvIntfAllocHandleObj(
    VpsMDrv_IntfInstObj           *instObj,
    const Vps_M2mIntfCreateParams *createPrms,
    const Fvid2_DrvCbParams       *fdmCbPrms)
{
    Int32  status = FVID2_SOK;
    UInt32 qCnt, frmCnt;
    VpsMDrv_IntfQueueObj  *qObj;
    VpsMDrv_IntfHandleObj *hObj = NULL;

    /* NULL pointer check */
    if ((NULL == createPrms) ||
        (NULL == instObj) ||
        (NULL == fdmCbPrms))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        /* Allocate handle memory */
        hObj = (VpsMDrv_IntfHandleObj *) BspUtils_alloc(
            &gVpsMDrvIntfHandlePoolParams,
            sizeof (VpsMDrv_IntfHandleObj),
            VpsMDrvTrace);
        if (NULL == hObj)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR,
                      "Handle object memory alloc failed!!\r\n");
            status = FVID2_EALLOC;
        }
        else
        {
            BspUtils_memset(hObj, 0x0, sizeof (VpsMDrv_IntfHandleObj));

            hObj->instObj = instObj;
        }
    }

    /* Create Queues */
    if (FVID2_SOK == status)
    {
        /* Create Output Queue for the completed frames
         * and freeQueue for the free queue objects */
        status = BspUtils_constructQ(&hObj->freeLlObj);
        GT_assert(VpsMDrvTrace, (status == BSP_SOK));
        hObj->freeQueue = &hObj->freeLlObj;

        status = BspUtils_constructQ(&hObj->outLlObj);
        GT_assert(VpsMDrvTrace, (status == BSP_SOK));
        hObj->outQueue = &hObj->outLlObj;
    }

    if (FVID2_SOK == status)
    {
        /* Create semaphore */
        hObj->ctrlSem = BspOsal_semCreate(0, (Bool) TRUE);
        if (NULL == hObj->ctrlSem)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR,
                      "Control semaphore create failed!!\r\n");
            status = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Create semaphore */
        hObj->stopSyncSem = BspOsal_semCreate(0, (Bool) TRUE);
        if (NULL == hObj->stopSyncSem)
        {
            GT_0trace(VpsMDrvTrace, GT_ERR,
                      "Stop sync semaphore create failed!!\r\n");
            status = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == status)
    {
        if (createPrms->chInQueueLength > BSP_CFG_M2M_INTF_QUEUE_LEN_PER_CH)
        {
            GT_2trace(
                VpsMDrvTrace, GT_ERR,
                "Cant create %d M2M Intf queue objects!!. Maximum supported M2M Intf queue objects are %d\r\n",
                createPrms->chInQueueLength, VPS_M2M_INTF_DEF_QUEUE_LEN_PER_CH);
            status = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Allocate queue object memory and queue them to free queue */
        for (qCnt = 0U; qCnt < createPrms->chInQueueLength; qCnt++)
        {
            /* Assign queue object memory */
            qObj = &hObj->m2mIntfQObj[qCnt];

            /* Assign Frame pointer to the VpsCore_frame, so
             * that it could be used by the sepcific core.
             * Core supports putFrame APi, which takes pointer to an array
             * of VpsCore_frames, so Queue Object has an array of
             * VpsCore Frame pointer */
            for (frmCnt = 0U; frmCnt < VPS_MAX_STREAMS; frmCnt++)
            {
                qObj->pFrm[frmCnt] = &qObj->frm[frmCnt];
            }

            /* Initialize queue object */
            /* Start index is initialized to -1 indicating none of stat
             * object is used for this queue object */
            qObj->statIdx = (-((Int32) 1));
            qObj->hObj    = hObj;

            /* Enqueue queue object to free queue of handle */
            BspUtils_queue(hObj->freeQueue, &qObj->qElem, qObj);
        }
    }

    if (FVID2_SOK == status)
    {
        /* Copy Create Parameters in handle object */
        BspUtils_memcpy(
            &hObj->createPrms,
            createPrms,
            sizeof (hObj->createPrms));

        /* Copy the callback params */
        BspUtils_memcpy(
            &hObj->fdmCbPrms,
            fdmCbPrms,
            sizeof (hObj->fdmCbPrms));
    }
    else /* Deallocate if error occurs */
    {
        if (NULL != hObj)
        {
            vpsMdrvIntfFreeHandleObj(hObj);
            hObj = NULL;
        }
    }

    return (hObj);
}

/**
 *  vpsMdrvIntfFreeHandleObj
 *  Frees the handle object and all other memories of the handle like handle
 *  objects, queues etc.
 */
static Int32 vpsMdrvIntfFreeHandleObj(VpsMDrv_IntfHandleObj *hObj)
{
    Int32                 status = FVID2_SOK;
    volatile UInt32       qObjCnt;
    VpsMDrv_IntfQueueObj *qObj = NULL;

    /* NULL pointer check */
    if (NULL == hObj)
    {
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        hObj->createPrms.numCh = 0U;

        if (NULL != hObj->ctrlSem)
        {
            /* Delete the control semaphore */
            BspOsal_semDelete(&hObj->ctrlSem);
            hObj->ctrlSem = NULL;
        }

        if (NULL != hObj->stopSyncSem)
        {
            /* Delete the stop sync semaphore */
            BspOsal_semDelete(&hObj->stopSyncSem);
            hObj->stopSyncSem = NULL;
        }

        if (NULL != hObj->outQueue)
        {
            /* Output Queue must be empty
             * asserting here since numPendReq checks for the un-dequeued
             * frames. numPendReq and size of the outQueue are same. */
            GT_assert(VpsMDrvTrace,
                      ((UInt32) TRUE == BspUtils_isQEmpty(hObj->outQueue)));

            /* Delete the output/done Q */
            BspUtils_destructQ(hObj->outQueue);
            hObj->outQueue = NULL;
        }

        if (NULL != hObj->freeQueue)
        {
            qObjCnt = 0U;
            /* Free-up all the queued free queue objects */
            while (1U)
            {
                qObj = (VpsMDrv_IntfQueueObj *) BspUtils_dequeue(
                    hObj->freeQueue);
                if ((qObjCnt >= hObj->createPrms.chInQueueLength) ||
                    (NULL == qObj))
                {
                    /* No more in queue or QObject is not null, but all enqueued
                     * elements
                     * are dequeued */
                    break;
                }

                /* Free queue object memory */
                BspUtils_memset(qObj, 0x0, sizeof (VpsMDrv_IntfQueueObj));
                qObj = NULL;

                qObjCnt++;
            }
            /* QObject should be null, otherwise, request queue has
             * more element than allocated */
            GT_assert(VpsMDrvTrace, (NULL == qObj));

            /* Delete the free Queue */
            BspUtils_destructQ(hObj->freeQueue);
            hObj->freeQueue = NULL;
        }

        hObj->frmStats = NULL;

        /* Reset the variables */
        hObj->instObj = NULL;
        hObj->fdmCbPrms.fdmCbFxn    = NULL;
        hObj->fdmCbPrms.fdmData     = NULL;
        hObj->fdmCbPrms.fdmErrCbFxn = NULL;
        hObj->fdmCbPrms.handle      = NULL;
        hObj->fdmCbPrms.errList     = NULL;

        BspUtils_memset(hObj, 0x0, sizeof (VpsMDrv_IntfHandleObj));

        /* Free handle object memory */
        BspUtils_free(&gVpsMDrvIntfHandlePoolParams, (void *) hObj,
                      VpsMDrvTrace);
    }

    return (status);
}

static Int32 vpsMdrvIntfAllocStatsObj(VpsMDrv_IntfHandleObj *hObj)
{
    Int32 status = FVID2_SOK;

    /* Check for the NULL pointer */
    if (NULL == hObj)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        /* By this time, handle object is already allocated and create
         * params are copied to handle object */

        /* Allocate memory for Vps_M2mIntfFrameStats structure */
        if (0U < hObj->createPrms.maxStatsInst)
        {
            /* maxStatsInst is not 0. check if the passed createPrms.frmStat
             * is not NULL. */
            if (NULL == hObj->createPrms.frmStats)
            {
                GT_0trace(
                    VpsMDrvTrace, GT_ERR,
                    "FrmStat pointer in NULL and maxStatsInst is not 0!!\r\n");
                status = FVID2_EALLOC;
            }
            hObj->frmStats = hObj->createPrms.frmStats;
        }
    }

    return (status);
}

static Int32 vpsMdrvIntfSetStatsParams(
    const VpsMDrv_IntfInstObj    *instObj,
    VpsMDrv_IntfHandleObj        *hObj,
    const Vps_M2mIntfStatsParams *statsPrms)
{
    Int32 status = FVID2_SOK;

    /* Check for NULL Pointer */
    if ((NULL == instObj) ||
        (NULL == hObj) ||
        (NULL == statsPrms))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        if (FALSE == statsPrms->enable)
        {
            /* Statistics collection is disabled */
            hObj->tsFxn = NULL;
        }
        else if (0U == hObj->createPrms.maxStatsInst)
        {
            /* This feature cannot be enabled if maxStatsInst is set to 0 at
             * create time */
            status = FVID2_EINVALID_PARAMS;
        }
        else if ((NULL != hObj->tsFxn) && (0U != hObj->curStatsIdx))
        {
            /* Statistics collection is already enabled */
            status = FVID2_EINVALID_PARAMS;
        }
        else /* Statistics collection is enabled */
        {
            /* Initialize timer function pointer in handle object,
             * Reset the current index */
            hObj->tsFxn       = instObj->tsPrms.timeStampFxn;
            hObj->curStatsIdx = 0U;
        }
    }

    return (status);
}

static Int32 vpsMdrvIntfGetStats(
    const VpsMDrv_IntfInstObj   *instObj,
    const VpsMDrv_IntfHandleObj *hObj,
    Vps_M2mIntfStats            *stats)
{
    Int32 status = FVID2_SOK;

    /* NULL Pointer checking */
    if ((NULL == instObj) ||
        (NULL == hObj) ||
        (NULL == stats))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        if (NULL != hObj->tsFxn)
        {
            /* Statistics collection is enabled */
            stats->frmStats = hObj->frmStats;
            stats->numStats = hObj->curStatsIdx;
        }

        stats->numProcessedReq = hObj->numProcessedReq;
        stats->numPendingReq   = hObj->numPendReq;
        stats->numErrorReq     = hObj->numErrorReq;
    }

    return (status);
}

/**
 *  vpsMdrvIntfOpenCores
 *  Opens all the cores required for this handle.
 */
static Int32 vpsMdrvIntfOpenCores(
    VpsMDrv_IntfHandleObj         *hObj,
    const Vps_M2mIntfCreateParams *createPrms,
    Vps_M2mIntfCreateStatus       *createStatus)
{
    Int32                status = FVID2_SOK;
    UInt32               coreCnt;
    VpsMDrv_IntfInstObj *instObj = NULL;
    VpsCore_OpenPrms     coreOpenPrms;
    const VpsCore_Ops   *coreOps;
    UInt32               vpsMdrvIntfFrmDoneNotifyCbTemp =
        (UInt32) (&vpsMdrvIntfFrmDoneNotifyCb);

    /* NULL pointer check */
    if ((NULL == hObj) ||
        (NULL == createPrms) ||
        (NULL == createStatus))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        instObj = hObj->instObj;

        if (NULL == instObj)
        {
            status = FVID2_EBADARGS;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Reset the handles first */
        for (coreCnt = 0U; coreCnt < VPSMDRV_INTF_MAX_CORE; coreCnt++)
        {
            hObj->coreHandle[coreCnt] = NULL;
        }

        BspUtils_memset(&coreOpenPrms, 0x0, sizeof (coreOpenPrms));

        /* Initialize Core Open Parameters */
        coreOpenPrms.drvData         = hObj;
        coreOpenPrms.reqFrmCb        = NULL;
        coreOpenPrms.frmDoneCb       = NULL;
        coreOpenPrms.frmDoneNotifyCb =
            (VpsCore_FrameDoneNotifyCb) (vpsMdrvIntfFrmDoneNotifyCbTemp);

        for (coreCnt = 0U; coreCnt < instObj->numCores; coreCnt++)
        {
            /* Get the core ops */
            coreOps = instObj->coreOps[coreCnt];

            /* NULL pointer check */
            GT_assert(VpsMDrvTrace, (NULL != coreOps));
            GT_assert(VpsMDrvTrace, (NULL != coreOps->open));

            /* Open core */
            hObj->coreHandle[coreCnt] = coreOps->open(
                instObj->coreInstId[coreCnt],
                &coreOpenPrms,
                createPrms->pAdditionalArgs,
                createStatus->pAdditionalStatus);
            if (NULL == hObj->coreHandle[coreCnt])
            {
                GT_1trace(VpsMDrvTrace, GT_ERR,
                          "Could not open core %d!\r\n", coreCnt);
                status = FVID2_EALLOC;
                break;
            }
        }
    }

    /* Close handles if error occurs */
    if (FVID2_SOK != status)
    {
        vpsMdrvIntfCloseCores(hObj);
    }

    return (status);
}

/**
 *  vpsMdrvIntfCloseCores
 *  Closes all the cores opened for this handle.
 */
static Int32 vpsMdrvIntfCloseCores(VpsMDrv_IntfHandleObj *hObj)
{
    Int32  status = FVID2_SOK;
    UInt32 coreCnt, tempStatus;
    VpsMDrv_IntfInstObj *instObj = NULL;
    const VpsCore_Ops   *coreOps;

    /* NULL pointer check */
    if (NULL == hObj)
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        instObj = hObj->instObj;

        if (NULL == instObj)
        {
            status = FVID2_EBADARGS;
        }
    }

    if (FVID2_SOK == status)
    {
        for (coreCnt = 0U; coreCnt < instObj->numCores; coreCnt++)
        {
            coreOps = instObj->coreOps[coreCnt];

            /* NULL pointer check */
            GT_assert(VpsMDrvTrace, (NULL != coreOps));
            GT_assert(VpsMDrvTrace, (NULL != coreOps->close));

            if (NULL != hObj->coreHandle[coreCnt])
            {
                /* Return core close status */
                tempStatus =
                    ((UInt32) status |
                     ((UInt32) coreOps->close(hObj->coreHandle[coreCnt])));
                status = (Int32) tempStatus;

                if (FVID2_SOK == status)
                {
                    /* Core is successfully close,
                     * so resetting handle to null */
                    hObj->coreHandle[coreCnt] = NULL;
                }
            }
        }
    }

    return (status);
}

/** \brief Frame Done callback
 */
Int32 vpsMdrvIntfFrmDoneNotifyCb(void *drvData)
{
    Int32 status;
    UInt32 cookie;
    VpsMDrv_IntfHandleObj *hObj       = (VpsMDrv_IntfHandleObj *) drvData;
    VpsMDrv_IntfInstObj   *instObj    = NULL;
    VpsMDrv_IntfQueueObj  *qObj       = NULL;
    VpsMDrv_M2mCoreOps    *drvCoreOps = NULL;
    Vps_M2mIntfFrameStats *frmStat    = NULL;

    /* NULL pointer check */
    GT_assert(VpsMDrvTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMDrvTrace, (NULL != instObj));
    /* Active Qobject must not be null */
    GT_assert(VpsMDrvTrace, (NULL != instObj->activeQObj));

    /* Disable global interrupts. */
    cookie = BspOsal_disableInterrupt();

    qObj = instObj->activeQObj;
    if ((NULL != hObj->tsFxn) &&
        ((-((Int32) 1)) != qObj->statIdx))
    {
        /* This pointer should not be null */
        GT_assert(VpsMDrvTrace, (NULL != hObj->frmStats));

        frmStat = hObj->frmStats + qObj->statIdx;

        /* ProcessRequest can be called from the ISR context, so
         * timer function should not be blocked */
        frmStat->endProcTimeStamp = hObj->tsFxn(NULL);
    }

    hObj->numProcessedReq++;
    /* Move completed request to output queue */
    BspUtils_queue(hObj->outQueue, &qObj->qElem, qObj);
    instObj->activeQObj = NULL;

    qObj = (VpsMDrv_IntfQueueObj *) BspUtils_dequeue(instObj->inQueue);

    if (NULL == qObj)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                  "No More Buffer to process!!\r\n");
    }
    else
    {
        /* There are more request pending for this instance */
        /* This pointer should not be null */
        GT_assert(VpsMDrvTrace, (NULL != instObj->drvCoreOps));
        drvCoreOps = (VpsMDrv_M2mCoreOps *) instObj->drvCoreOps;
        /* Ensure to use the handle that this request is associated with */
        GT_assert(VpsMDrvTrace, (NULL != qObj->hObj));
        hObj = qObj->hObj;

        if ((NULL != hObj->tsFxn) &&
            ((-((Int32) 1)) != qObj->statIdx))
        {
            /* This pointer should not be null */
            GT_assert(VpsMDrvTrace, (NULL != hObj->frmStats));

            frmStat = hObj->frmStats + qObj->statIdx;

            /* ProcessRequest can be called from the ISR context, so
             * timer function should not be blocked */
            frmStat->startProcTimeStamp = hObj->tsFxn(NULL);
        }

        /* Driver specific submit request */
        if (NULL != drvCoreOps->submitReq)
        {
            status = drvCoreOps->submitReq(hObj, qObj);
        }
        else
        {
            status = FVID2_EFAIL;
        }

        if (FVID2_SOK == status)
        {
            instObj->activeQObj = qObj;
        }
        else
        {
            GT_assert(VpsMDrvTrace, FALSE);
        }
        /* Restore the handle object, for the current completed request */
        hObj = (VpsMDrv_IntfHandleObj *) drvData;
    }

    /* Enable global Interrupts. */
    BspOsal_restoreInterrupt(cookie);

    /* Calling application callback at the last, so that if there is
     * any request in the input queue, it can be submitte before calling
     * this callback, this can maximize hardware usage. */
    status = hObj->fdmCbPrms.fdmCbFxn(hObj->fdmCbPrms.fdmData, NULL);

    return (FVID2_SOK);
}

static Int32 vpsMdrvIntfResetStats(
    VpsMDrv_IntfInstObj   *instObj,
    VpsMDrv_IntfHandleObj *hObj)
{
    Int32  status = FVID2_SOK;
    UInt32 cookie;

    /* Null Pointer check */
    if ((NULL == instObj) || (NULL == hObj))
    {
        status = FVID2_EBADARGS;
    }
    else
    {
        /* Check if statistics collection is enabled or not */
        if (NULL == hObj->tsFxn)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                      "Statistics collection is not enabled!!\r\n");
            status = FVID2_EINVALID_PARAMS;
        }
        if (((UInt32) FALSE == BspUtils_isQEmpty(instObj->inQueue)) ||
            (NULL != instObj->activeQObj))
        {
            GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                      "Cannot reset stats when there are pending requests!!\r\n");
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Disable Interrupts
         * Since FVID2_queue/dequeue can be called from the ISR context,
         * which can change value of numPendReq, protecting this check
         * and update from ISR */
        cookie = BspOsal_disableInterrupt();
        if (0U != hObj->numPendReq)
        {
            status = FVID2_EINVALID_PARAMS;
        }
        else
        {
            /* Reset the curStats Index */
            hObj->curStatsIdx = 0U;
        }
        BspOsal_restoreInterrupt(cookie);
    }

    return (status);
}

