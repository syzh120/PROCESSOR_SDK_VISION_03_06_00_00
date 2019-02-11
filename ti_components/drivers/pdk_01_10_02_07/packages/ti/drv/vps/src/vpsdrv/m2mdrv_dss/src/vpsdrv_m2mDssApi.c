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
 *  \file vpsdrv_m2mDssApi.c
 *
 *  \brief VPS DSS M2M common interface driver.
 *  This file implements the DSS M2M driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <m2mdrv_dss/src/vpsdrv_m2mDssPriv.h>

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

static Fdrv_Handle VpsMdrv_m2mDssCreate(
    UInt32                   drvId,
    UInt32                   instId,
    Ptr                      createArgs,
    Ptr                      createStatusArgs,
    const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 VpsMdrv_m2mDssDelete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 VpsMdrv_m2mDssControl(
    Fdrv_Handle handle,
    UInt32      cmd,
    Ptr         cmdArgs,
    Ptr         cmdStatusArgs);
static Int32 VpsMdrv_m2mDssProcessRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList);
static Int32 VpsMdrv_m2mDssGetProcessedRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList,
    UInt32           timeout);
#ifdef __cplusplus
}
#endif

static Int32 vpsMdrvDssInit(UInt32 numInst,
                            const VpsMdrv_DssInitParams *initPrms);
static Int32 vpsMdrvDssDeInit(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \breif M2M driver function pointer. */
static const Fvid2_DrvOps    VpsMdrvDssOps =
{
    FVID2_VPS_DSS_M2M_DRV,              /* Driver ID */
    &VpsMdrv_m2mDssCreate,              /* Create */
    &VpsMdrv_m2mDssDelete,              /* Delete */
    &VpsMdrv_m2mDssControl,             /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    &VpsMdrv_m2mDssProcessRequest,      /* ProcessRequest */
    &VpsMdrv_m2mDssGetProcessedRequest  /* GetProcessedRequest */
};

/** \breif DSS M2M driver common object. */
VpsMDrv_DssCommonObj gVpsMDrvDssCommonObj;

/* ========================================================================== */
/*                          FVID2 API Functions                               */
/* ========================================================================== */

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_001)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-740) DOX_REQ_TAG(PDK-1765) DOX_REQ_TAG(PDK-1792)
 */
/**
 *  VpsMdrv_dssInit
 *  \brief DSS M2M driver init function.
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
Int32 VpsMdrv_dssInit(UInt32 numInst,
                      const VpsMdrv_DssInitParams *initPrms)
{
    Int32 retVal = FVID2_SOK;

    /* Check for errors */
    GT_assert(VpsMDrvDssTrace, (NULL != initPrms));

    /* Initialize the internal objects */
    retVal = vpsMdrvDssInit(numInst, initPrms);
    if (FVID2_SOK == retVal)
    {
        /* Register the driver to the driver manager */
        retVal = Fvid2_registerDriver(&VpsMdrvDssOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Uninitialize the internal objects if error occurs */
            vpsMdrvDssDeInit();
        }
    }

    return (retVal);
}

/**
 *  VpsMdrv_dssDeInit
 *  \brief DSS M2M driver exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_dssDeInit(void)
{
    Int32 retVal = FVID2_SOK;

    /* Unregister from driver manager */
    retVal = Fvid2_unRegisterDriver(&VpsMdrvDssOps);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR,
                  "Unregistering from FVID2 driver manager failed!!\r\n");
    }

    /* Uninitialize the internal objects */
    retVal += vpsMdrvDssDeInit();

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_019)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1766)
 */
/**
 *  VpsMdrv_m2mDssCreate
 *  \brief M2M driver create function.
 *  Opens an instance of the driver, opens the associated cores.
 *
 *  \return             Returns FVID2_Handle on success else returns NULL.
 */
static Fdrv_Handle VpsMdrv_m2mDssCreate(
    UInt32                   drvId,
    UInt32                   instId,
    Ptr                      createArgs,
    Ptr                      createStatusArgs,
    const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 retVal = FVID2_SOK, tempstatus;
    VpsMDrv_DssInstObj     *instObj      = NULL;
    Vps_M2mDssCreateParams *createPrms;
    Vps_M2mDssCreateStatus *createStatus = NULL;
    VpsMDrv_DssHandleObj   *hObj         = NULL;

    /* Check for the NULL pointer */
    if ((NULL == createArgs) ||
        (NULL == createStatusArgs) ||
        (NULL == fdmCbPrms))
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Get Instance Object */
        instObj = vpsMdrvDssGetInstObj(instId);
        if (NULL == instObj)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "Wrong instance id\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        else
        {
            /* This instance is not initialized */
            if (FALSE == instObj->initDone)
            {
                GT_0trace(VpsMDrvDssTrace, GT_ERR,
                          "Not Initialized Instance id\r\n");
                retVal  = FVID2_EINVALID_PARAMS;
                instObj = NULL;
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

    if (FVID2_SOK == retVal)
    {
        /* Check if a instance is opened more than the supported handles */
        if (instObj->openCnt >= VPS_M2M_DSS_MAX_HANDLE_PER_INST)
        {
            GT_1trace(VpsMDrvDssTrace, GT_ERR,
                      "Only %d handles supported per instance!\r\n",
                      VPS_M2M_DSS_MAX_HANDLE_PER_INST);
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        createPrms   = (Vps_M2mDssCreateParams *) createArgs;
        createStatus = (Vps_M2mDssCreateStatus *) createStatusArgs;
        retVal       = vpsMdrvCheckCreateArgs(instObj, createPrms);
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate handle object */
        hObj = vpsMdrvDssAllocHandleObj(instObj, createPrms, fdmCbPrms);
        if (NULL == hObj)
        {
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        if (0U == instObj->openCnt)
        {
            /* Open core when the first handle is opened */
            retVal = vpsMdrvDssOpenCores(instObj, hObj);
        }
    }

    if (FVID2_SOK == retVal)
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
            tempstatus = vpsMdrvDssFreeHandleObj(hObj);

            /* Already returning null handle, ie Create fail, so no need
             * to return this error
             * Also this function returns always success unless handle
             * object is null */
            GT_assert(VpsMDrvDssTrace, (FVID2_SOK == tempstatus));
            hObj = NULL;
        }
    }

    /* Return the retVal if possible */
    if (NULL != createStatus)
    {
        BspUtils_memset(createStatus, 0x0, sizeof (Vps_M2mDssCreateStatus));
        createStatus->retVal = retVal;
        if (FVID2_SOK == retVal)
        {
            createStatus->maxHandles = VPS_M2M_DSS_MAX_HANDLE_PER_INST;
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
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_019)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1767)
 */
/**
 *  VpsMdrv_m2mDssDelete
 *  \brief M2M driver delete function.
 *  closes an instance of the driver, closes the associated cores, cleansup
 *  handle object.
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mDssDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 retVal = FVID2_SOK, tempstatus;
    VpsMDrv_DssInstObj   *instObj = NULL;
    VpsMDrv_DssHandleObj *hObj    = NULL;

    if (NULL == handle)
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_DssHandleObj *) handle;
        if (NULL == hObj->instObj)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "NULL pointer\n");
            retVal = FVID2_EBADARGS;
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

    if (FVID2_SOK == retVal)
    {
        /* Check if still some request are pending with driver */
        if (0U != hObj->numPendReq)
        {
            GT_1trace(
                VpsMDrvDssTrace, GT_ERR,
                "Still %d request pending. Dequeue all before closing!!\r\n",
                hObj->numPendReq);

            /* Size of outQ and num of pending requests must be same,
             * if they are not same, there is some corruption, so asserting
             * here. */
            GT_assert(VpsMDrvDssTrace,
                      (hObj->numPendReq == BspUtils_getNumQElem(hObj->outQ)));
            retVal = FVID2_EAGAIN;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* All handles are already closed */
        if (0U == instObj->openCnt)
        {
            retVal = FVID2_EFAIL;
        }
        else
        {
            /* Free allocated handle object */
            tempstatus = vpsMdrvDssFreeHandleObj(hObj);
            GT_assert(VpsMDrvDssTrace, (FVID2_SOK == tempstatus));

            /* Decrement number of handle open count */
            instObj->openCnt--;

            /* For the last instance, unregister and deallocate resource */
            if (0U == instObj->openCnt)
            {
                /* Close the opened cores */
                tempstatus = vpsMdrvDssCloseCores(instObj);
                GT_assert(VpsMDrvDssTrace, (FVID2_SOK == tempstatus));
            }
        }
    }

    if (NULL != instObj)
    {
        /* release the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return (retVal);
}

/**
 *  VpsMdrv_m2mDssControl
 *  \brief M2M driver control function.
 *  Processes driver specific control commands, calls core whenever required.
 *
 *  Caution: All ioctls are protected using instance semaphore, so these ioctls
 *  cannot be called from ISR context.
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mDssControl(Fdrv_Handle handle,
                                   UInt32      cmd,
                                   Ptr         cmdArgs,
                                   Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    VpsMDrv_DssInstObj   *instObj   = NULL;
    VpsMDrv_DssHandleObj *hObj      = NULL;

    /* Check for NULL pointers */
    if (NULL == handle)
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "Handle NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_DssHandleObj *) handle;
        if (NULL == hObj->instObj)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR,
                      "Instance Object NULL pointer\n");
            retVal = FVID2_EBADARGS;
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

    if (FVID2_SOK == retVal)
    {
        switch (cmd)
        {
            case IOCTL_VPS_M2M_DSS_SET_PARAMS:
                retVal = vpsMdrvDssSetPrmsIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_M2M_DSS_SET_CSC_COEFF:
                retVal = vpsMdrvDssSetCscCoeffIoctl(hObj, cmdArgs);
                break;

            default:
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    if (NULL != instObj)
    {
        /* Release the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_019)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1768)
 */
/**
 *  VpsMdrv_m2mDssProcessRequest
 *  \brief M2M driver process request.
 *  Processes single channel M2M processing request
 *
 *  This api can be called from the ISR context
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mDssProcessRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    VpsMDrv_DssInstObj   *instObj    = NULL;
    VpsMDrv_DssHandleObj *hObj       = NULL;
    VpsMDrv_DssQueueObj  *qObj       = NULL;

    /* Check for NULL pointers */
    if (NULL == handle)
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "handle NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_DssHandleObj *) handle;
        if (NULL == hObj->instObj)
        {
            GT_0trace(VpsMDrvDssTrace, GT_ERR, "Instance Object NULL pointer\n");
            retVal = FVID2_EBADARGS;
        }
        else
        {
            instObj = hObj->instObj;
            if (hObj->createPrms.inQueueLength <= hObj->numPendReq)
            {
                GT_0trace(VpsMDrvDssTrace, GT_DEBUG,
                          "Trying to submit more frame than allocated.\
                          Try again after dequeuing some frames!!\r\n");
                instObj = NULL;
                retVal  = FVID2_EAGAIN;
            }
        }
    }

    /* No need to disable interrupts in case of error condition */
    if (NULL != instObj)
    {
        /* Disable global interrupts */
        cookie = BspOsal_disableInterrupt();
    }

    if (FVID2_SOK == retVal)
    {
        /* Get a queue object from the free queue */
        qObj = (VpsMDrv_DssQueueObj *) BspUtils_dequeue(hObj->freeQ);
        if (NULL == qObj)
        {
            GT_0trace(VpsMDrvDssTrace, GT_DEBUG,
                      "Failed to allocate queue object. Try again!!\r\n");
            retVal = FVID2_EAGAIN;
        }
        else
        {
            qObj->hObj = hObj;
            /* Copy the application's process list to request objects lists */
            Fvid2_copyFrameList(&qObj->inFrmList, inFrmList);
            Fvid2_copyFrameList(&qObj->outFrmList, outFrmList);
        }
    }

    if (FVID2_SOK == retVal)
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
            instObj->activeQObj = qObj;
            retVal = vpsMdrvDssProcessReq(instObj, qObj);
            if (FVID2_SOK != retVal)
            {
                /* Return queue object back to free queue */
                BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        hObj->numPendReq++;
    }

    if (NULL != instObj)
    {
        /* Enable Interrupts */
        BspOsal_restoreInterrupt(cookie);
    }

    return (retVal);
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_019)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1769)
 */
/**
 *  VpsMdrv_m2mDssGetProcessedRequest
 *  \brief M2M driver get processed request.
 *  Returns completed processed request.
 *
 *  This api can be called from the ISR context
 *
 *  \return             Returns FVID2_SOK on success else returns
 *                      negative error code.
 */
static Int32 VpsMdrv_m2mDssGetProcessedRequest(
    Fdrv_Handle      handle,
    Fvid2_FrameList *inFrmList,
    Fvid2_FrameList *outFrmList,
    UInt32           timeout)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    VpsMDrv_DssHandleObj *hObj    = NULL;
    VpsMDrv_DssQueueObj  *qObj    = NULL;

    /* Check for NULL pointers */
    if ((NULL == handle) || (NULL == inFrmList) || (NULL == outFrmList))
    {
        GT_0trace(VpsMDrvDssTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMDrv_DssHandleObj *) handle;
    }

    if (FVID2_SOK == retVal)
    {
        /* Disable global interrupts. */
        cookie = BspOsal_disableInterrupt();

        /* Dequeue the completed request from done queue */
        qObj = (VpsMDrv_DssQueueObj *) BspUtils_dequeue(hObj->outQ);
        if (NULL == qObj)
        {
            /* Check if requests are pending with driver */
            if (0U == hObj->numPendReq)
            {
                /* Nothing is queued */
                GT_0trace(
                    VpsMDrvDssTrace, GT_DEBUG,
                    "Nothing to dequeue. No request pending with driver!!\r\n");
                retVal = FVID2_ENO_MORE_BUFFERS;
            }
            else
            {
                /* If no request have completed, return try again */
                GT_0trace(VpsMDrvDssTrace, GT_DEBUG,
                          "Nothing to dequeue. Try again!!\r\n");
                retVal = FVID2_EAGAIN;
            }
        }
        else
        {
            /* Copy the driver's process list to application's process list */
            Fvid2_copyFrameList(inFrmList, &qObj->inFrmList);
            Fvid2_copyFrameList(outFrmList, &qObj->outFrmList);

            /* Return back the queue object to the free queue */
            BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);

            /* Decrement the pending request count. */
            if (0U != hObj->numPendReq)
            {
                hObj->numPendReq--;
            }
        }

        /* Enable Interrupts */
        BspOsal_restoreInterrupt(cookie);
    }

    return (retVal);
}

/* ========================================================================== */
/*                          Internal Functions                                */
/* ========================================================================== */

/*
 *  Allocates the instance object and initializes it.
 */
static Int32 vpsMdrvDssInit(UInt32 numInst,
                            const VpsMdrv_DssInitParams *initPrms)
{
    Int32               retVal = FVID2_SOK;
    UInt32              instCnt;
    VpsMDrv_DssInstObj *instObj;

    /* Error Checking */
    if (numInst > VPS_M2M_DSS_INST_MAX)
    {
        retVal = FVID2_EOUT_OF_RANGE;
    }
    if (NULL == initPrms)
    {
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Check for errors in the init params */
        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            /* Core ops should not be null */
            if ((NULL == initPrms[instCnt].inCoreOps) ||
                (NULL == initPrms[instCnt].outCoreOps))
            {
                retVal = FVID2_EBADARGS;
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        BspUtils_memset(
            &gVpsMDrvDssCommonObj,
            0x0U,
            sizeof (VpsMDrv_DssCommonObj));

        for (instCnt = 0U; instCnt < numInst; instCnt++)
        {
            /* Assign memory for all instance objects */
            instObj = &gVpsMDrvDssCommonObj.instObj[instCnt];

            BspUtils_memset(instObj, 0x0U, sizeof (VpsMDrv_DssInstObj));

            /* Copy Core Instance Id and Core operation pointer to
             * instance object */
            instObj->drvInstId      = initPrms[instCnt].drvInstId;
            instObj->inCoreInstObj  = initPrms[instCnt].inCoreInstObj;
            instObj->inCoreOps      = initPrms[instCnt].inCoreOps;
            instObj->outCoreInstObj = initPrms[instCnt].outCoreInstObj;
            instObj->outCoreOps     = initPrms[instCnt].outCoreOps;

            instObj->instSem = BspOsal_semCreate((Int32) 1U, (Bool) TRUE);
            if (NULL == instObj->instSem)
            {
                GT_0trace(VpsMDrvDssTrace, GT_ERR,
                            "Instance semaphore create failed!!\r\n");
                retVal = FVID2_EALLOC;
            }

            if (FVID2_SOK == retVal)
            {
                /* Create the different queues - request, done and free
                 * queues Assumes BspUtils are already initialized */
                retVal = BspUtils_constructQ(&instObj->inLlObj);
                GT_assert(VpsMDrvDssTrace, (retVal == BSP_SOK));
                instObj->inQueue = &instObj->inLlObj;
            }

            if (FVID2_SOK == retVal)
            {
                instObj->initDone = (UInt32) TRUE;
            }

            if (FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Init DSS M2M handle objects pool */
        BspUtils_initPool(
            &gVpsMDrvDssCommonObj.handlePoolPrm,
            (void *) &gVpsMDrvDssCommonObj.handleMemPool,
            (VPS_M2M_DSS_INST_MAX * VPS_M2M_DSS_MAX_HANDLE_PER_INST),
            sizeof (VpsMDrv_DssHandleObj),
            &gVpsMDrvDssCommonObj.handleMemFlag[0U],
            VpsMDrvDssTrace);
    }

    if (FVID2_SOK != retVal)
    {
        vpsMdrvDssDeInit();
    }
    else
    {
        gVpsMDrvDssCommonObj.numInsts = numInst;
    }

    return (retVal);
}

static Int32 vpsMdrvDssDeInit(void)
{
    Int32  retVal = FVID2_SOK;
    UInt32 instCnt;
    VpsMDrv_DssInstObj *instObj;

    for (instCnt = 0U; instCnt < VPS_M2M_DSS_INST_MAX; instCnt++)
    {
        instObj = &gVpsMDrvDssCommonObj.instObj[instCnt];

        /* Check if any handle is opened or not */
        if (0U != instObj->openCnt)
        {
            GT_2trace(VpsMDrvDssTrace, GT_ERR,
                      "%d handles of driver inst %d not closed!\r\n",
                      instObj->openCnt,
                      instCnt);
            retVal = FVID2_EDRIVER_INUSE;
            break;
        }

        if (NULL != instObj->inQueue)
        {
            /* Input Queue must be empty */
            GT_assert(VpsMDrvDssTrace,
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

        BspUtils_memset(instObj, 0x0U, sizeof (VpsMDrv_DssInstObj));
    }
    gVpsMDrvDssCommonObj.numInsts = 0U;

    return (retVal);
}
