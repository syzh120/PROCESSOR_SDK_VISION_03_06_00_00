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
 *  \file vpsdrv_m2mVpeApi.c
 *
 *  \brief VPS VPE M2M driver for the VPE paths.
 *  This file implements the VPS VPE M2M driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <vpedrv/src/vpsdrv_m2mVpePriv.h>

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
static Fdrv_Handle VpsMdrv_vpeCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 VpsMdrv_vpeDelete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 VpsMdrv_vpeControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
static Int32 VpsMdrv_vpeProcessFrms(Fdrv_Handle        handle,
                                    Fvid2_ProcessList *procList);
static Int32 VpsMdrv_vpeGetProcessedFrms(Fdrv_Handle        handle,
                                         Fvid2_ProcessList *procList,
                                         UInt32             timeout);
#ifdef __cplusplus
}
#endif
static Int32 vpsMdrvVpeSetPrmsIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
static Int32 vpsMdrvVpeGetPrmsIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                    Ptr                         cmdArgs);
static Int32 vpsMdrvVpeGetCtxInfoIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                       Ptr                         cmdArgs);
static Int32 vpsMdrvVpeSetCtxBufIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                      Ptr                         cmdArgs);
static Int32 vpsMdrvVpeGetCtxBufIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                      Ptr                         cmdArgs);
static Int32 vpsMdrvVpeOverridePrevFldBufIoctl(
    const VpsMdrv_VpeHandleObj *hObj,
    Ptr
    cmdArgs);

static Int32 vpsMdrvVpeSetScCoeffIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);
static Int32 vpsMdrvVpeStopIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs);

static Int32 vpsMdrvVpeCheckProcList(const VpsMdrv_VpeHandleObj *hObj,
                                     const Fvid2_ProcessList    *procList);
static Int32 vpsMdrvVpeCheckParams(const Vps_M2mCreateParams *createPrms,
                                   const VpsMdrv_VpeInstObj  *instObj,
                                   UInt32                     instId);

static UInt32 vpsMdrvVpeIsCtxFieldsSet(const VpsMdrv_VpeHandleObj *hObj);
static Int32 vpsMdrvVpeReleaseCtxFields(VpsMdrv_VpeHandleObj *hObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \breif VPE M2M driver function pointer. */
static const Fvid2_DrvOps VpsMdrvVpeOps =
{
    FVID2_VPS_M2M_DRV,                  /* Driver ID */
    &VpsMdrv_vpeCreate,                 /* Create */
    &VpsMdrv_vpeDelete,                 /* Delete */
    &VpsMdrv_vpeControl,                /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    &VpsMdrv_vpeProcessFrms,            /* ProcessFrames */
    &VpsMdrv_vpeGetProcessedFrms,       /* GetProcessedFrames */
    NULL,                               /* ProcessRequest */
    NULL                                /* GetProcessedRequest */
};

/* ========================================================================== */
/*                          FVID2 API Functions                               */
/* ========================================================================== */

/**
 *  VpsMdrv_vpeInit
 *  \brief VPE M2M driver init function.
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
Int32 VpsMdrv_vpeInit(UInt32                       numInst,
                      const VpsMdrv_VpeInitParams *initPrms)
{
    Int32 retVal = FVID2_SOK;

    /* Check for errors */
    GT_assert(VpsMdrvVpeTrace, (NULL != initPrms));

    /* Initialize the internal objects */
    retVal = vpsMdrvVpeInit(numInst, initPrms);
    if(FVID2_SOK == retVal)
    {
        /* Register the driver to the driver manager */
        retVal = Fvid2_registerDriver(&VpsMdrvVpeOps);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Uninitialize the internal objects if error occurs */
            vpsMdrvVpeDeInit();
        }
    }

    return (retVal);
}

/**
 *  VpsMdrv_vpeDeInit
 *  \brief VPE M2M driver exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_vpeDeInit(void)
{
    Int32 retVal = FVID2_SOK;

    /* Unregister from driver manager */
    retVal = Fvid2_unRegisterDriver(&VpsMdrvVpeOps);
    if(FVID2_SOK != retVal)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                  "Unregistering from FVID2 driver manager failed\r\n");
    }

    /* Uninitialize the internal objects */
    retVal += vpsMdrvVpeDeInit();

    return (retVal);
}

/**
 *  VpsMdrv_vpeSetLazyLoadParams
 *  \brief VPE driver set lazy load parameter for a given instance and scaler.
 *
 *  \param lazyPrms     Pointer to lazy loading parameter. This can't be NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_vpeSetLazyLoadParams(const Vps_ScLazyLoadingParams *lazyPrms)
{
    Int32 retVal = FVID2_SOK;
    VpsMdrv_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != lazyPrms));

    /* Get the instance object for this instance */
    instObj = vpsMdrvVpeGetInstObj(lazyPrms->vpeInstId);
    if(NULL == instObj)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid instance ID\r\n");
        retVal = FVID2_EINVALID_PARAMS;
    }

    if(NULL != instObj)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->instSem, BSP_OSAL_WAIT_FOREVER);
    }

    if(FVID2_SOK == retVal)
    {
        if(instObj->openCnt != 0U)
        {
            GT_0trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Can't set lazy load params when the driver is open\r\n");
            retVal = FVID2_EDRIVER_INUSE;
        }
    }

    if(FVID2_SOK == retVal)
    {
        if(lazyPrms->scalerId >= VPS_M2M_SCALER_ID_MAX)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid scaler ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Set the lazy loading settings */
        instObj->lazyLoadingEnable[lazyPrms->scalerId] =
            lazyPrms->lazyLoadingEnable;
    }

    if(NULL != instObj)
    {
        /* Post the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return (retVal);
}

/**
 *  VpsMdrv_vpeCreate
 */
static Fdrv_Handle VpsMdrv_vpeCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32  retVal, tempRetVal;
    UInt32 coreOpenFlag           = FALSE;
    VpsMdrv_VpeInstObj   *instObj = NULL;
    Vps_M2mCreateParams  *createPrms;
    VpsMdrv_VpeHandleObj *hObj = NULL;
    Vps_M2mCreateStatus  *createStatus;

    /* Check for NULL pointers */
    if((NULL == createArgs) ||
       (NULL == createStatusArgs) ||
       (NULL == fdmCbPrms))
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        /* Get the instance object for this instance */
        instObj = vpsMdrvVpeGetInstObj(instId);
        if(NULL == instObj)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid instance ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
        else
        {
            retVal = FVID2_SOK;
        }
    }

    if(NULL != instObj)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->instSem, BSP_OSAL_WAIT_FOREVER);
    }

    if(FVID2_SOK == retVal)
    {
        /* Check if a instance is opened more than the supported handles */
        if(instObj->openCnt >= VPS_M2M_MAX_HANDLE_PER_INST)
        {
            GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                      "Only %d handles supported per instance!\r\n",
                      VPS_M2M_MAX_HANDLE_PER_INST);
            retVal = FVID2_EALLOC;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Check for valid create parameters */
        createPrms = (Vps_M2mCreateParams *) createArgs;
        retVal     = vpsMdrvVpeCheckParams(createPrms, instObj, instId);
    }

    if(FVID2_SOK == retVal)
    {
        /* Allocate handle object memory including some of the members */
        hObj = vpsMdrvVpeAllocHandleObj(
            createPrms,
            instObj,
            fdmCbPrms);
        if(NULL == hObj)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Handle allocation failed\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Open the cores */
        retVal = vpsMdrvVpeOpenCores(hObj);
        if(FVID2_SOK == retVal)
        {
            coreOpenFlag = (UInt32) TRUE;
        }
        else
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Opening of cores failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        if(0U == instObj->openCnt)
        {
            /* Register with MLM if first handle is opened.
             * Channels are non-static, there is no need to
             * provide channel numbers here. */
            instObj->mlmInfo.reqCompleteCb   = &VpsMdrv_vpeMlmCbFxn;
            instObj->mlmInfo.isChannelStatic = (UInt32) FALSE;
            instObj->mlmInfo.clientType      = MLM_CT_VPE;
            /* Fmd call back function registered here */
            if(TRUE == createPrms->isDeiFmdEnable)
            {
                instObj->mlmInfo.deiFmdCb = &VpsMdrv_vpeMlmFmdCbFxn;
            }
            else
            {
                instObj->mlmInfo.deiFmdCb = NULL;
            }
            instObj->mlmHandle = Mlm_register(&instObj->mlmInfo, NULL);
            if(NULL == instObj->mlmHandle)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Registration with MLM failed!\r\n");
                retVal = FVID2_EALLOC;
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Increment the count to keep track of number of handles opened */
        instObj->openCnt++;
    }

    /* Deallocate if error occurs */
    if(FVID2_SOK != retVal)
    {
        if(NULL != hObj)
        {
            if(NULL != instObj->mlmHandle)
            {
                /* Unregister from MLM */
                Mlm_unRegister(instObj->mlmHandle);
                instObj->mlmHandle = NULL;
            }

            if(coreOpenFlag == (UInt32) TRUE)
            {
                /* Close the opened cores */
                tempRetVal = vpsMdrvVpeCloseCores(hObj);
                GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
            }

            /* Free allocated handle object */
            tempRetVal = vpsMdrvVpeFreeHandleObj(hObj);
            GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
            hObj = NULL;
        }
    }

    /* Return the status if possible */
    if(NULL != createStatusArgs)
    {
        createStatus         = (Vps_M2mCreateStatus *) createStatusArgs;
        createStatus->retVal = retVal;
        if(FVID2_SOK == retVal)
        {
            createStatus->maxHandles          = VPS_M2M_MAX_HANDLE_PER_INST;
            createStatus->maxChPerHandle      = VPS_M2M_MAX_CH_PER_HANDLE;
            createStatus->maxSameChPerRequest = 1U;
        }
    }

    if(NULL != instObj)
    {
        /* Post the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return ((Fdrv_Handle) hObj);
}

/**
 *  VpsMdrv_vpeDelete
 */
static Int32 VpsMdrv_vpeDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 chCnt;
    VpsMdrv_VpeInstObj   *instObj;
    VpsMdrv_VpeHandleObj *hObj;

    /* Check for NULL pointers */
    if(NULL == handle)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        hObj    = (VpsMdrv_VpeHandleObj *) handle;
        instObj = hObj->instObj;
        /* NULL pointer check */
        GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

        /* Check if still some request are pending with driver */
        if(0U != hObj->numPendReq)
        {
            GT_1trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Still %d request pending. Dequeue all before closing!!\r\n",
                hObj->numPendReq);
            retVal = FVID2_EAGAIN;
        }

        if(vpsMdrvVpeIsCtxFieldsSet(hObj) == (UInt32) TRUE)
        {
            GT_0trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Context fields are not retrived back. Try Fvid2_stop () \
                 before closing!!\r\n");
            retVal = FVID2_EAGAIN;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Take the instance semaphore */
        BspOsal_semWait(instObj->instSem, BSP_OSAL_WAIT_FOREVER);

        /* Decrement number of handle open count */
        GT_assert(VpsMdrvVpeTrace, (0U != instObj->openCnt));
        instObj->openCnt--;

        /* For the last instance, unregister from MLM and deallocate resource */
        if(0U == instObj->openCnt)
        {
            if(NULL != instObj->mlmHandle)
            {
                /* Unregister from MLM */
                Mlm_unRegister(instObj->mlmHandle);
                instObj->mlmHandle = NULL;
            }
        }

        for(chCnt = 0U; chCnt < hObj->createPrms.numCh; chCnt++)
        {
            /* Free the memories allocated for cores */
            tempRetVal = vpsMdrvVpeFreeCoreMem(hObj, hObj->chObjs[chCnt]);
            GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));

            /* Reset the params flag since we have freed core memory */
            hObj->chObjs[chCnt]->isParamSet = (UInt32) FALSE;
        }

        /* Close the opened cores */
        tempRetVal = vpsMdrvVpeCloseCores(hObj);
        GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));

        /* Free allocated handle object */
        tempRetVal = vpsMdrvVpeFreeHandleObj(hObj);
        GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
        hObj = NULL;

        /* Post the instance semaphore */
        BspOsal_semPost(instObj->instSem);
    }

    return (retVal);
}

/**
 *  VpsMdrv_vpeControl
 */
static Int32 VpsMdrv_vpeControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    VpsMdrv_VpeHandleObj *hObj;

    /* Check for NULL pointers */
    if(NULL == handle)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        hObj = (VpsMdrv_VpeHandleObj *) handle;
        switch(cmd)
        {
            case IOCTL_VPS_M2M_SET_VPE_PARAMS:
                /* Set VPE params IOCTL */
                retVal = vpsMdrvVpeSetPrmsIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_M2M_GET_VPE_PARAMS:
                /* Get VPE params IOCTL */
                retVal = vpsMdrvVpeGetPrmsIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_GET_DEI_CTX_INFO:
                /* Get DEI context information IOCTL */
                retVal = vpsMdrvVpeGetCtxInfoIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_SET_DEI_CTX_BUF:
                /* Set DEI context buffer IOCTL */
                retVal = vpsMdrvVpeSetCtxBufIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_GET_DEI_CTX_BUF:
                /* Get DEI context buffer IOCTL */
                retVal = vpsMdrvVpeGetCtxBufIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_VPE_OVERRIDE_PREV_FLD_BUF:
                /* Get DEI context buffer IOCTL */
                retVal = vpsMdrvVpeOverridePrevFldBufIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_SET_COEFFS:
                /* Set scaler coefficient IOCTL */
                retVal = vpsMdrvVpeSetScCoeffIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_READ_ADV_DEI_CFG:
                /* Read DEI advance configuration IOCTL */
                retVal = vpsMdrvVpeDeiRdAdvCfgIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_WRITE_ADV_DEI_CFG:
                /* Write DEI advance configuration IOCTL */
                retVal = vpsMdrvVpeDeiWrAdvCfgIoctl(hObj, cmdArgs);
                break;
/* TODO */
#if 0
            case IOCTL_VPS_READ_ADV_SC_CFG:
                /* Read Scaler advance configuration IOCTL */
                retVal = vpsMdrvVpeScRdAdvCfgIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_WRITE_ADV_SC_CFG:
                /* Write Scaler advance configuration IOCTL */
                retVal = vpsMdrvVpeScWrAdvCfgIoctl(hObj, cmdArgs);
                break;
#endif

            case IOCTL_VPS_SET_DEI_FMD_CFG:
                /* Set FMD configuration IOCTL */
                retVal = vpsMdrvVpeDeiSetFmdCfgIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_RD_DEI_FMD_STAT:
                /* Read FMD Status register IOCTL */
                retVal = vpsMdrvVpeDeiRdFmdStatIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_WR_DEI_FMD_UPDATE:
                /* Write FMD Update IOCTL */
                retVal = vpsMdrvVpeDeiUpdateFmdIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_SET_RANGE_MAP_REDUCT_CFG:
                /* Set Range Mapping and Range Reduction configuration IOCTL */
                retVal = vpsMdrvVpeSetRangMapRedtCfgIoctl(hObj, cmdArgs);
                break;

            case IOCTL_VPS_GET_RANGE_MAP_REDUCT_CFG:
                /* Get Range Mapping and Range Reduction configuration IOCTL */
                retVal = vpsMdrvVpeGetRangMapRedtCfgIoctl(hObj, cmdArgs);
                break;

            case FVID2_STOP:
                /* Release all the fields queued up and held context fields */
                retVal = vpsMdrvVpeStopIoctl(hObj, cmdArgs);
                break;

            default:
                GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                          "UNSUPPORTED_CMD: IOCTL (%d) not supported\r\n", cmd);
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (retVal);
}

/**
 *  VpsMdrv_vpeProcessFrms
 */
static Int32 VpsMdrv_vpeProcessFrms(Fdrv_Handle        handle,
                                    Fvid2_ProcessList *procList)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    VpsMdrv_VpeQueueObj  *qObj = NULL;
    VpsMdrv_VpeHandleObj *hObj = NULL;

    /* Check for NULL pointers */
    if((NULL == handle) || (NULL == procList))
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMdrv_VpeHandleObj *) handle;

        /* Check for error in parameters */
        retVal = vpsMdrvVpeCheckProcList(hObj, procList);
    }

    /* Disable global interrupts */
    cookie = BspOsal_disableInterrupt();

    if(FVID2_SOK == retVal)
    {
        /* Check if the driver was stopped, being re-started (with new fields)
         * ensure to clear up the flag */
        if(hObj->isStopped == TRUE)
        {
            hObj->isStopped = (UInt32) FALSE;
        }

        /* Get a queue object from the free queue */
        qObj = (VpsMdrv_VpeQueueObj *) BspUtils_dequeue(hObj->freeQ);
        if(NULL == qObj)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                      "Failed to allocate queue object. Try again!!\r\n");
            retVal = FVID2_EAGAIN;
        }
        else
        {
            /* Copy the application's process list to driver's process list */
            Fvid2_copyProcessList(&qObj->procList, procList);
            qObj->qObjType = VPSMDRV_QOBJ_TYPE_FRAMES;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get a free descriptor to work with */
        qObj->descSetInUse = vpsMdrvVpeAllocDescSet(hObj);
        if(VPSMDRV_VPE_INVALID_DESC_SET == qObj->descSetInUse)
        {
            /* We did not get the free desc set so queue the request
             * until the call back is called. */
            BspUtils_queue(hObj->reqQ, &qObj->qElem, qObj);
        }
        else
        {
            /* We have a free descriptor set, update the descriptors, link the
             * channels and queue it to MLM for processing */
            retVal = vpsMdrvVpeProcessReq(hObj, qObj);
            if(FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                          "Process request failed\r\n");
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Increment the pending request count */
        hObj->numPendReq++;
        hObj->numUnProcessedReq++;
    }

    /* Deallocate if error occurs */
    if(FVID2_SOK != retVal)
    {
        if(NULL != qObj)
        {
            /* Free the descriptor set if already allocated */
            if(VPSMDRV_VPE_INVALID_DESC_SET != qObj->descSetInUse)
            {
                GT_assert(VpsMdrvVpeTrace,
                          (VPSMDRV_VPE_MAX_DESC_SET == qObj->descSetInUse));
                vpsMdrvVpeFreeDescSet(hObj, qObj->descSetInUse);
                qObj->descSetInUse = VPSMDRV_VPE_INVALID_DESC_SET;
            }

            /* Return back the queue object to the free queue */
            BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);
            qObj = NULL;
        }
    }

    /* Restore global interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

/**
 *  VpsMdrv_vpeGetProcessedFrms
 */
static Int32 VpsMdrv_vpeGetProcessedFrms(Fdrv_Handle        handle,
                                         Fvid2_ProcessList *procList,
                                         UInt32             timeout)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    VpsMdrv_VpeQueueObj  *qObj = NULL;
    VpsMdrv_VpeHandleObj *hObj = NULL;

    /* Check for NULL pointers */
    if((NULL == handle) || (NULL == procList))
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        hObj = (VpsMdrv_VpeHandleObj *) handle;

        /* Disable global interrupts */
        cookie = BspOsal_disableInterrupt();

        /* Dequeue the completed request from done queue */
        qObj = (VpsMdrv_VpeQueueObj *) BspUtils_dequeue(hObj->doneQ);
        if(NULL == qObj)
        {
            /* Check if requests are pending with driver */
            if(0U == hObj->numPendReq)
            {
                /* Nothing is queued */
                GT_0trace(
                    VpsMdrvVpeTrace, GT_DEBUG,
                    "Nothing to dequeue. No request pending with driver!!\r\n");
                retVal = FVID2_ENO_MORE_BUFFERS;
            }
            else
            {
                /* If no request have completed, return try again */
                GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                          "Nothing to dequeue. Try again!!\r\n");
                retVal = FVID2_EAGAIN;
            }
        }
        else
        {
            /* Copy the driver's process list to application's process list */
            Fvid2_copyProcessList(procList, &qObj->procList);

            /* Return back the queue object to the free queue */
            qObj->descSetInUse = VPSMDRV_VPE_INVALID_DESC_SET;
            BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);

            /* Decrement the pending request count. When stopped, there could
             * instances when we have no pending requests but application
             * might have stopped the driver (instructing to release held
             * context fileds.*/
            if(0U != hObj->numPendReq)
            {
                hObj->numPendReq--;
            }
        }

        /* Restore global interrupts */
        BspOsal_restoreInterrupt(cookie);
    }

    return (retVal);
}

/* ========================================================================== */
/*                             Local Functions                                */
/* ========================================================================== */

/**
 *  vpsMdrvVpeSetPrmsIoctl
 */
static Int32 vpsMdrvVpeSetPrmsIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    const Vps_M2mVpeParams *vpePrms;
    VpsMdrv_VpeChObj *chObj;
    UInt32 coreAllocFlag = FALSE;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    if(NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        /* Don't allow to set params when requests are pending with driver */
        if(0U != hObj->numUnProcessedReq)
        {
            GT_1trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Can't set params when %d requests are pending!!\r\n",
                hObj->numUnProcessedReq);
            retVal = FVID2_EAGAIN;
        }
    }

    if(FVID2_SOK == retVal)
    {
        vpePrms = (const Vps_M2mVpeParams *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if(vpePrms->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get the channel object */
        chObj = hObj->chObjs[vpePrms->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
        GT_assert(VpsMdrvVpeTrace, (chObj->chNum == vpePrms->chNum));

        /* Copy VPE params */
        retVal = vpsMdrvVpeCopyVpePrms(chObj, vpePrms);
    }

    if(FVID2_SOK == retVal)
    {
        /* Free the already allocated memories */
        retVal = vpsMdrvVpeFreeCoreMem(hObj, chObj);
        GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == retVal));

        /* Reset the params flag since we have freed core memory */
        chObj->isParamSet = (UInt32) FALSE;

        retVal = vpsMdrvVpeConfigCores(hObj, chObj);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Configuring of cores failed\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        retVal = vpsMdrvVpeAllocCoreMem(hObj, chObj);
        if(FVID2_SOK == retVal)
        {
            coreAllocFlag = (UInt32) TRUE;
            /* Program the descriptor memories of cores */
            retVal = vpsMdrvVpeProgramDesc(hObj, chObj);
            if(FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Programming of cores failed\r\n");
            }
        }
        else
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Core memory alloc failed\r\n");
        }
    }

    if((FVID2_SOK == retVal) && (TRUE == hObj->createPrms.isDeiFmdEnable))
    {
        /* FMD Initialization */
        reg_init(&hObj->dei_fmd_reg_blck, hObj);
        fmd_init(&hObj->dei_fmd_reg_blck, &hObj->dei_fmd_blck);
    }

    if((FVID2_SOK != retVal) && ((UInt32) TRUE == coreAllocFlag))
    {
        /* Free the already allocated memory in case of error */
        tempRetVal = vpsMdrvVpeFreeCoreMem(hObj, chObj);
        GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
    }

    if(FVID2_SOK == retVal)
    {
        /* Params set successfully */
        chObj->isParamSet = (UInt32) TRUE;
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeGetPrmsIoctl
 */
static Int32 vpsMdrvVpeGetPrmsIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                    Ptr                         cmdArgs)
{
    Int32 retVal = FVID2_SOK;
    Vps_M2mVpeParams *vpePrms;
    VpsMdrv_VpeChObj *chObj;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    if(NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        vpePrms = (Vps_M2mVpeParams *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if(vpePrms->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get the channel object */
        chObj = hObj->chObjs[vpePrms->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
        GT_assert(VpsMdrvVpeTrace, (chObj->chNum == vpePrms->chNum));
        GT_assert(VpsMdrvVpeTrace, (chObj->chNum == chObj->vpePrms.chNum));

        BspUtils_memcpy(vpePrms, &chObj->vpePrms, sizeof(Vps_M2mVpeParams));
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeGetCtxInfoIoctl
 */
static Int32 vpsMdrvVpeGetCtxInfoIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                       Ptr                         cmdArgs)
{
    Int32 retVal = FVID2_SOK;
    Vps_DeiCtxInfo   *deiCtxInfo;
    VpsMdrv_VpeChObj *chObj;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    if(NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        deiCtxInfo = (Vps_DeiCtxInfo *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if(deiCtxInfo->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get the channel object */
        chObj = hObj->chObjs[deiCtxInfo->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
        GT_assert(VpsMdrvVpeTrace, (chObj->chNum == deiCtxInfo->chNum));

        if(TRUE != chObj->isParamSet)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Set the params before calling this IOCTL\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Copy the context information from channel object */
        BspUtils_memcpy(deiCtxInfo, &chObj->deiCtxInfo, sizeof(Vps_DeiCtxInfo));

        /* For platform TI814X, apps needs not allocate context buffers for
         * fields Ensure to clear them. */
        deiCtxInfo->numFld     = 0x0U;
        deiCtxInfo->fldBufSize = 0x0U;
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeSetCtxBufIoctl
 */
static Int32 vpsMdrvVpeSetCtxBufIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                      Ptr                         cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    UInt32 bufCnt;
    Vps_DeiCtxBuf    *deiCtxBuf;
    VpsMdrv_VpeChObj *chObj;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    if(NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    /* Disable global interrupts */
    cookie = BspOsal_disableInterrupt();

    if(FVID2_SOK == retVal)
    {
        deiCtxBuf = (Vps_DeiCtxBuf *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if(deiCtxBuf->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
        /* Don't allow to set the buffer address when requests are pending
         * with driver */
        if(0U != hObj->numUnProcessedReq)
        {
            GT_1trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Can't set context buffers when %d request are pending!!\r\n",
                hObj->numUnProcessedReq);
            retVal = FVID2_EAGAIN;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get the channel object */
        chObj = hObj->chObjs[deiCtxBuf->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
        GT_assert(VpsMdrvVpeTrace, (chObj->chNum == deiCtxBuf->chNum));
        GT_assert(VpsMdrvVpeTrace,
                  (chObj->deiCtxInfo.numFld <= VPS_DEI_MAX_CTX_FLD_BUF));
        GT_assert(VpsMdrvVpeTrace,
                  (chObj->deiCtxInfo.numMv <= VPS_DEI_MAX_CTX_MV_BUF));
        GT_assert(VpsMdrvVpeTrace,
                  (chObj->deiCtxInfo.numMvstm <= VPS_DEI_MAX_CTX_MVSTM_BUF));

        for(bufCnt = 0U; bufCnt < chObj->deiCtxInfo.numMv; bufCnt++)
        {
            if(NULL == deiCtxBuf->mvBuf[bufCnt])
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "MV buffer NULL pointer\n");
                retVal = FVID2_EBADARGS;
                break;
            }
        }
        for(bufCnt = 0U; bufCnt < chObj->deiCtxInfo.numMvstm; bufCnt++)
        {
            if(NULL == deiCtxBuf->mvstmBuf[bufCnt])
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "MV buffer NULL pointer\n");
                retVal = FVID2_EBADARGS;
                break;
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        if(TRUE != chObj->isParamSet)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Set the params before calling this IOCTL\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Copy the context buffer to the channel object */
        BspUtils_memcpy(&chObj->deiCtxBuf, deiCtxBuf, sizeof(Vps_DeiCtxBuf));
        chObj->isDeiCtxBufSet = (UInt32) TRUE;
    }

    /* Restore global interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

/**
 *  vpsMdrvVpeGetCtxBufIoctl
 */
static Int32 vpsMdrvVpeGetCtxBufIoctl(const VpsMdrv_VpeHandleObj *hObj,
                                      Ptr                         cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;
    UInt32 bufCnt, ptrCnt;
    Vps_DeiCtxBuf          *deiCtxBuf;
    VpsMdrv_VpeChObj       *chObj;
    Vcore_VpeUpdateContext *vpeCoreCtxBuf;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    if(NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    /* Disable global interrupts */
    cookie = BspOsal_disableInterrupt();

    if(FVID2_SOK == retVal)
    {
        deiCtxBuf = (Vps_DeiCtxBuf *) cmdArgs;
        /* Check if the channel number is within the allocated one */
        if(deiCtxBuf->chNum >= hObj->createPrms.numCh)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
            retVal = FVID2_EOUT_OF_RANGE;
        }
        /* Don't allow to get the buffer address when requests are pending
         * with driver */
        if(0U != hObj->numUnProcessedReq)
        {
            GT_1trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Can't get context buffers when %d request are pending!!\r\n",
                hObj->numUnProcessedReq);
            retVal = FVID2_EAGAIN;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get the channel object */
        chObj = hObj->chObjs[deiCtxBuf->chNum];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));
        GT_assert(VpsMdrvVpeTrace, (chObj->chNum == deiCtxBuf->chNum));
        GT_assert(VpsMdrvVpeTrace,
                  (chObj->deiCtxInfo.numFld <= VPS_DEI_MAX_CTX_FLD_BUF));
        GT_assert(VpsMdrvVpeTrace,
                  (chObj->deiCtxInfo.numMv <= VPS_DEI_MAX_CTX_MV_BUF));
        GT_assert(VpsMdrvVpeTrace,
                  (chObj->deiCtxInfo.numMvstm <= VPS_DEI_MAX_CTX_MVSTM_BUF));

        if(TRUE != chObj->isParamSet)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Set the params before calling this IOCTL\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Copy the context buffer from the channel object */
        BspUtils_memcpy(deiCtxBuf, &chObj->deiCtxBuf, sizeof(Vps_DeiCtxBuf));

        /* Clear the context buffers */
        chObj->isDeiCtxBufSet = (UInt32) FALSE;
        for(bufCnt = 0U; bufCnt < chObj->deiCtxInfo.numFld; bufCnt++)
        {
            chObj->deiCtxBuf.fldBuf[bufCnt] = NULL;
        }
        for(bufCnt = 0U; bufCnt < chObj->deiCtxInfo.numMv; bufCnt++)
        {
            chObj->deiCtxBuf.mvBuf[bufCnt] = NULL;
        }
        for(bufCnt = 0U; bufCnt < chObj->deiCtxInfo.numMvstm; bufCnt++)
        {
            chObj->deiCtxBuf.mvstmBuf[bufCnt] = NULL;
        }

        /* Clear the core context buffers */
        vpeCoreCtxBuf = &chObj->vpeCoreCtxBuf;
        for(bufCnt = 0U; bufCnt < VCORE_VPE_MAX_PREV_FLD; bufCnt++)
        {
            for(ptrCnt = 0U; ptrCnt < VCORE_VPE_NUM_DESC_PER_FIELD; ptrCnt++)
            {
                vpeCoreCtxBuf->prevInBuf[bufCnt][ptrCnt] = NULL;
            }
        }
        for(bufCnt = 0U; bufCnt < VCORE_VPE_MAX_OUT_FLD; bufCnt++)
        {
            for(ptrCnt = 0U; ptrCnt < VCORE_VPE_NUM_DESC_PER_FIELD; ptrCnt++)
            {
                vpeCoreCtxBuf->curOutBuf[bufCnt][ptrCnt] = NULL;
            }
        }
        for(bufCnt = 0U; bufCnt < VCORE_VPE_MAX_MV_IN; bufCnt++)
        {
            vpeCoreCtxBuf->mvInBuf[bufCnt] = NULL;
        }
        vpeCoreCtxBuf->mvOutBuf = NULL;
        for(bufCnt = 0U; bufCnt < (VCORE_VPE_MAX_MVSTM_IN + 1U); bufCnt++)
        {
            vpeCoreCtxBuf->mvstmInBuf[bufCnt] = NULL;
        }
        vpeCoreCtxBuf->mvstmOutBuf = NULL;
    }

    /* Restore global interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

/**
 *  vpsMdrvVpeOverridePrevFldBufIoctl
 */
static Int32 vpsMdrvVpeOverridePrevFldBufIoctl(
    const VpsMdrv_VpeHandleObj *hObj,
    Ptr
    cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 chNum;
    UInt32 fldCnt, frmCnt, numFrames;
    Fvid2_Frame      *frame;
    Fvid2_Frame      *prevFrame[VPSMDRV_VPE_MAX_FIELD_CONTEXT];
    VpsMdrv_VpeChObj *chObj;
    Vps_M2mVpeOverridePrevFldBuf *prevFldBuf;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    if(NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        /* Don't allow to override buffer address when requests are pending
         * with driver */
        if(0U != hObj->numUnProcessedReq)
        {
            GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                      "Can't override previous field buffers when %d requests "
                      "are pending!!\r\n", hObj->numUnProcessedReq);
            retVal = FVID2_EAGAIN;
        }
    }

    if(FVID2_SOK == retVal)
    {
        prevFldBuf = (Vps_M2mVpeOverridePrevFldBuf *) cmdArgs;
        if(prevFldBuf->numFldBufLists != VPSMDRV_VPE_MAX_FIELD_CONTEXT)
        {
            GT_1trace(VpsMdrvVpeTrace, GT_ERR,
                      "Number of field buffers should be %d\r\n",
                      VPSMDRV_VPE_MAX_FIELD_CONTEXT);
            retVal = FVID2_EINVALID_PARAMS;
        }
        else
        {
            for(fldCnt = 0U; fldCnt < prevFldBuf->numFldBufLists; fldCnt++)
            {
                if(NULL == prevFldBuf->fldBufFrameList[fldCnt])
                {
                    retVal = FVID2_EBADARGS;
                    break;
                }
            }
        }
    }

    if(FVID2_SOK == retVal)
    {
        numFrames = prevFldBuf->fldBufFrameList[0U]->numFrames;
        for(frmCnt = 0U; frmCnt < numFrames; frmCnt++)
        {
            frame = prevFldBuf->fldBufFrameList[0U]->frames[frmCnt];
            GT_assert(VpsMdrvVpeTrace, (NULL != frame));

            /* Get the channel number frame list's frame pointer */
            chNum = frame->chNum;

            /* Check if the channel number is within the allocated one */
            if(chNum >= hObj->createPrms.numCh)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid channel number\n");
                retVal = FVID2_EOUT_OF_RANGE;
            }

            if(FVID2_SOK == retVal)
            {
                /* Get the channel object */
                chObj = hObj->chObjs[chNum];
                GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

                if(TRUE != chObj->isParamSet)
                {
                    GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                              "Set the params before calling this IOCTL\r\n");
                    retVal = FVID2_EFAIL;
                }
            }

            if(FVID2_SOK == retVal)
            {
                /* Store the driver held buffers locally so that it could be
                 * returned back to the application in the same IOCTL after
                 * copying */
                for(fldCnt = 0U;
                    fldCnt < VPSMDRV_VPE_MAX_FIELD_CONTEXT;
                    fldCnt++)
                {
                    /* Skip current input frame (0th index) as it is stored in
                     * the last index in next step */
                    prevFrame[fldCnt] =
                        chObj->ctxFieldFifo[fldCnt + 1U].fieldCtxBuf;
                }

                /* Store the current input frame at the last index so that it
                 * is put in context queue while doing rotation in next queue
                 * call */
                chObj->ctxFieldFifo[VPSMDRV_VPE_MAX_FIELD_CONTEXT].fieldCtxBuf
                    =
                        chObj->ctxFieldFifo[0U].fieldCtxBuf;

                for(fldCnt = 0U; fldCnt < prevFldBuf->numFldBufLists; fldCnt++)
                {
                    /* Copy the user provided frame to the channel object
                     * context FIFO. While copying, copy N-1 (0th index of
                     * fldBufFrameList represents N-1 frame) to N, N-2
                     * (1st index) to N-1 and so on, so that when age context
                     * buffer function is called during next queue call, frames
                     * will fall in place!! */
                    frame =
                        prevFldBuf->fldBufFrameList[fldCnt]->frames[frmCnt];
                    GT_assert(VpsMdrvVpeTrace, (NULL != frame));
                    chObj->ctxFieldFifo[fldCnt].fieldCtxBuf = frame;

                    /* Return the replaced frame to the application in the same
                     * structure */
                    prevFldBuf->fldBufFrameList[fldCnt]->frames[frmCnt] =
                        prevFrame[fldCnt];
                }

                if(FALSE == chObj->isCtxFieldInit)
                {
                    for(fldCnt = 0U;
                        fldCnt <= VPSMDRV_VPE_MAX_FIELD_CONTEXT;
                        fldCnt++)
                    {
                        chObj->ctxFieldFifo[fldCnt].tth =
                            VPSMDRV_VPE_MAX_FIELD_CONTEXT - fldCnt;
                    }
                    chObj->isCtxFieldInit = (UInt32) TRUE;
                }
            }

            if(FVID2_SOK != retVal)
            {
                break;
            }
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeSetScCoeffIoctl
 */
static Int32 vpsMdrvVpeSetScCoeffIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK, tempRetVal;
    UInt32 cookie;
    UInt32 coreCnt;
    UInt8 *coeffDesc = NULL, *descPtr = NULL;
    const Vcore_M2mOps        *coreOps = NULL;
    VpsMdrv_VpeQueueObj       *qObj    = NULL;
    VpsMdrv_VpeChObj          *chObj;
    VpsMdrv_VpeInstObj        *instObj;
    const Vps_ScCoeffParams   *scCoeffPrms;
    Vcore_M2mScUserCoeffParams coreUserCoeffPrms;
    Vcore_M2mScGetCoeffParams coreGetCoeffPrms;
    UInt32 tempDestAddr;

    /* Check for NULL pointers */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    if(NULL == cmdArgs)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "NULL pointer\n");
        retVal = FVID2_EBADARGS;
    }

    /* Disable global interrupts */
    cookie = BspOsal_disableInterrupt();

    if(FVID2_SOK == retVal)
    {
        scCoeffPrms = (Vps_ScCoeffParams *) cmdArgs;
        instObj     = hObj->instObj;
        GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

        /* TODO: Assuming first channel information */
        chObj = hObj->chObjs[0U];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

        if(TRUE != chObj->isParamSet)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Set the params before calling this IOCTL\r\n");
            retVal = FVID2_EFAIL;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Get the core to which the scaler ID matches */
        coreCnt = instObj->scalerCoreId[scCoeffPrms->scalerId];
        GT_assert(VpsMdrvVpeTrace, (VPSMDRV_VPE_MAX_CORE != coreCnt));
        coreOps = instObj->coreOps[coreCnt];
        /* Check if the scaler ID is valid */
        if(NULL == coreOps)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Invalid Scaler ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Allocate coeff descriptor and memory */
        coeffDesc = (UInt8 *) vpsMdrvVpeAllocCoeffDesc();
        /* Get a queue object from the free queue */
        qObj = (VpsMdrv_VpeQueueObj *) BspUtils_dequeue(hObj->freeQ);
        if((NULL == coeffDesc) || (NULL == qObj))
        {
            GT_0trace(
                VpsMdrvVpeTrace, GT_ERR,
                "Could not allocate coeff memory/descriptor/queue object\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* NULL pointer check */
        GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->programUserCoeff));

        /* Program the user coefficient */
        coreUserCoeffPrms.hScalingSet  = scCoeffPrms->hScalingSet;
        coreUserCoeffPrms.vScalingSet  = scCoeffPrms->vScalingSet;
        coreUserCoeffPrms.userCoeffPtr = NULL;
        retVal = coreOps->programUserCoeff(
            hObj->coreHandle[coreCnt],
            0U,
            &coreUserCoeffPrms);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Could not program coeff memory\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* NULL pointer check */
        GT_assert(VpsMdrvVpeTrace, (NULL != coreOps->getScCoeff));

        /* Get the pointers to coefficient memory */
        coreGetCoeffPrms.hScalingSet = scCoeffPrms->hScalingSet;
        coreGetCoeffPrms.vScalingSet = scCoeffPrms->vScalingSet;
        retVal = coreOps->getScCoeff(
            hObj->coreHandle[coreCnt],
            0U,
            &coreGetCoeffPrms);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Could not program coeff memory\r\n");
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* First create the horizontal coeff descriptor. */
        descPtr = coeffDesc;
        GT_assert(VpsMdrvVpeTrace, (NULL != coreGetCoeffPrms.horzCoeffMemPtr));
        VpsHal_vpdmaCreateConfigDesc(
            descPtr,
            chObj->coeffConfigDest[coreCnt],
            VPSHAL_VPDMA_CPT_BLOCK_SET,
            VPSHAL_VPDMA_CCT_INDIRECT,
            chObj->horzCoeffOvlySize[coreCnt],
            coreGetCoeffPrms.horzCoeffMemPtr,
            0U,
            (UInt16) chObj->horzCoeffOvlySize[coreCnt]);

        /* Now create the vertical coeff descriptor. */
        descPtr += VPSHAL_VPDMA_CONFIG_DESC_SIZE;
        GT_assert(VpsMdrvVpeTrace, (NULL != coreGetCoeffPrms.vertCoeffMemPtr));
        VpsHal_vpdmaCreateConfigDesc(
            descPtr,
            chObj->coeffConfigDest[coreCnt],
            VPSHAL_VPDMA_CPT_BLOCK_SET,
            VPSHAL_VPDMA_CCT_INDIRECT,
            chObj->vertCoeffOvlySize[coreCnt],
            coreGetCoeffPrms.vertCoeffMemPtr,
            (Ptr) (chObj->horzCoeffOvlySize[coreCnt]),
            (UInt16) chObj->vertCoeffOvlySize[coreCnt]);

        /* Create the vertical bilinear coeff descriptor only if HQ scaler,
         * otherwise create dummy descriptor. */
        descPtr += VPSHAL_VPDMA_CONFIG_DESC_SIZE;
        if(NULL != coreGetCoeffPrms.vertBilinearCoeffMemPtr)
        {
            tempDestAddr =
                chObj->horzCoeffOvlySize[0] + chObj->vertCoeffOvlySize[0];
            VpsHal_vpdmaCreateConfigDesc(
                descPtr,
                chObj->coeffConfigDest[coreCnt],
                VPSHAL_VPDMA_CPT_BLOCK_SET,
                VPSHAL_VPDMA_CCT_INDIRECT,
                chObj->vertBilinearCoeffOvlySize[0],
                coreGetCoeffPrms.vertBilinearCoeffMemPtr,
                (Ptr) (tempDestAddr),
                (UInt16) chObj->vertBilinearCoeffOvlySize[0]);
        }
        else
        {
            VpsHal_vpdmaCreateDummyDesc(descPtr);
        }

        /*
         * Update the MLM parameters and submit the request to MLM
         */
        qObj->qObjType = VPSMDRV_QOBJ_TYPE_COEFF;
        qObj->mlmReqInfo.reqStartAddr     = coeffDesc;
        qObj->mlmReqInfo.firstChannelSize =
            ((VPSMDRV_VPE_MAX_COEFF_CFG_DESC * VPSHAL_VPDMA_CONFIG_DESC_SIZE) +
             VPSHAL_VPDMA_CTRL_DESC_SIZE);
        qObj->mlmReqInfo.lastRlDescAddr = (coeffDesc +
                                           (VPSMDRV_VPE_MAX_COEFF_CFG_DESC *
                                            VPSHAL_VPDMA_CONFIG_DESC_SIZE));
        qObj->mlmReqInfo.submitReqType = MLM_SRT_NO_SOC;
        qObj->mlmReqInfo.cbArg         = qObj;
        qObj->mlmReqInfo.numChannels   = 0U;
        retVal = Mlm_submit(instObj->mlmHandle, &qObj->mlmReqInfo);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Submission to MLM failed\r\n");
        }
        else
        {
            /* Increment the pending request count */
            hObj->numPendReq++;
            hObj->numUnProcessedReq++;

            /* Restore global interrupts */
            BspOsal_restoreInterrupt(cookie);

            /* Wait for completion of coefficient programming */
            BspOsal_semWait(hObj->ctrlSem, BSP_OSAL_WAIT_FOREVER);

            /* Disable global interrupts */
            cookie = BspOsal_disableInterrupt();

            /* Decrement the pending request count */
            GT_assert(VpsMdrvVpeTrace, (0U != hObj->numPendReq));
            GT_assert(VpsMdrvVpeTrace, (0U != hObj->numUnProcessedReq));
            hObj->numUnProcessedReq--;
            hObj->numPendReq--;
        }
    }

    /* Free the memories if already allocated */
    if(NULL != coeffDesc)
    {
        tempRetVal = vpsMdrvVpeFreeCoeffDesc(coeffDesc);
        GT_assert(VpsMdrvVpeTrace, (FVID2_SOK == tempRetVal));
    }
    if(NULL != qObj)
    {
        /* Return back the queue object to the free queue */
        BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);
    }

    /* Restore global interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

/**
 *  vpsMdrvVpeCheckProcList
 */
static Int32 vpsMdrvVpeCheckProcList(const VpsMdrv_VpeHandleObj *hObj,
                                     const Fvid2_ProcessList    *procList)
{
    Int32 retVal = FVID2_SOK;
    VpsMdrv_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    GT_assert(VpsMdrvVpeTrace, (NULL != procList));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    /* Check for error in process list */
    retVal = Fvid2_checkProcessList(
        procList,
        instObj->numInListReq,
        instObj->numOutListReq,
        hObj->createPrms.numCh,
        FALSE);
    if(FVID2_SOK != retVal)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Error in process list\r\n");
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeCheckParams
 *  Checks for valid create parameters.
 */
static Int32 vpsMdrvVpeCheckParams(const Vps_M2mCreateParams *createPrms,
                                   const VpsMdrv_VpeInstObj  *instObj,
                                   UInt32                     instId)
{
    Int32 retVal = FVID2_SOK;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != createPrms));
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    if(createPrms->chInQueueLength <= 0U)
    {
        GT_1trace(VpsDrvCaptTrace, GT_ERR,
                  "Invalid in queue length(%d)\r\n", createPrms->chInQueueLength);
        retVal = FVID2_EINVALID_PARAMS;
    }

    if((createPrms->numCh > VPS_M2M_MAX_CH_PER_HANDLE) ||
       (createPrms->numCh <= 0U))
    {
        GT_2trace(
            VpsMdrvVpeTrace, GT_ERR,
            "Invalid number of channels(%d) - Supported max channels %d\r\n",
            createPrms->numCh,
            VPS_M2M_MAX_CH_PER_HANDLE);
        retVal = FVID2_EINVALID_PARAMS;
    }

    if((instObj->numChAllocated + createPrms->numCh) > VPS_M2M_MAX_CH_PER_INST)
    {
        GT_1trace(
            VpsMdrvVpeTrace, GT_ERR,
            "Exceeds number of channels per instance (Max %d per instance)\r\n",
            VPS_M2M_MAX_CH_PER_INST);
        retVal = FVID2_EINVALID_PARAMS;
    }

    return (retVal);
}

/**
 * vpsMdrvVpeIsCtxFieldsSet
 * Check if any of the channel(s) has its context field set
 */
static UInt32 vpsMdrvVpeIsCtxFieldsSet(const VpsMdrv_VpeHandleObj *hObj)
{
    UInt32 retVal = FALSE;
    UInt32 chIndex;
    VpsMdrv_VpeChObj *chObj;

    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    for(chIndex = 0U; chIndex < hObj->createPrms.numCh; chIndex++)
    {
        chObj = hObj->chObjs[chIndex];
        GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

        if(chObj->isCtxFieldInit != FALSE)
        {
            retVal = (UInt32) TRUE;
            break;
        }
    }

    return (retVal);
}

/**
 * vpsMdrvVpeReleaseCtxFields
 * Relenquishes all the fields held by the driver. This function requires to be
 * called with interrupts disabled.
 */
static Int32 vpsMdrvVpeReleaseCtxFields(VpsMdrv_VpeHandleObj *hObj)
{
    Int32        retVal = FVID2_SOK;
    UInt32       chIndex, fifoIndex, frameIndex, ctxFldIdx;
    Fvid2_Frame *heldFields;
    VpsMdrv_VpeChObj       *chObj;
    VpsMdrv_VpeQueueObj    *qObj;
    Vcore_VpeUpdateContext *vpeCoreCtxBuf;

    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));

    qObj = (VpsMdrv_VpeQueueObj *) BspUtils_dequeue(hObj->freeQ);
    if(NULL == qObj)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_DEBUG,
                  "Failed to allocate queue object. Required to stop!!\r\n");
        retVal = FVID2_EAGAIN;
    }
    else
    {
        qObj->qObjType = VPSMDRV_QOBJ_TYPE_FRAMES;

        hObj->tempFrameList.numFrames = 0U;
        frameIndex = 0U;
        for(chIndex = 0U; chIndex < hObj->createPrms.numCh; chIndex++)
        {
            chObj = hObj->chObjs[chIndex];
            GT_assert(VpsMdrvVpeTrace, (NULL != chObj));

            /* Mark the context fields as reset - would require to refill
             * context in case apps decided to restart without closing the
             * driver
             * In case context was not initialized - nothing to release for
             * this channel - move on to next channel */
            if(chObj->isCtxFieldInit == TRUE)
            {
                chObj->isCtxFieldInit = (UInt32) FALSE;

                /* For each channel - get the context buffers - including the
                 * current field */
                for(fifoIndex = 0U;
                    fifoIndex <= VPSMDRV_VPE_MAX_FIELD_CONTEXT;
                    fifoIndex++)
                {
                    heldFields = chObj->ctxFieldFifo[fifoIndex].fieldCtxBuf;
                    GT_assert(VpsMdrvVpeTrace, (NULL != heldFields));

                    /* Ensure not to release duplicated context, for the current
                     * field, VPSMDRV_VPE_MAX_FIELD_CONTEXT would be the
                     * TTH value. Duplicated context will be >
                     * VPSMDRV_VPE_MAX_FIELD_CONTEXT */
                    if(chObj->ctxFieldFifo[fifoIndex].tth <=
                       VPSMDRV_VPE_MAX_FIELD_CONTEXT)
                    {
                        hObj->tempFrameList.frames[frameIndex] = heldFields;
                        frameIndex++;
                        GT_assert(VpsMdrvVpeTrace,
                                  (FVID2_MAX_FRAME_PTR >= frameIndex));
                    }
                }

                vpeCoreCtxBuf = &chObj->vpeCoreCtxBuf;
                GT_assert(VpsMdrvVpeTrace, (NULL != vpeCoreCtxBuf));
                for(ctxFldIdx = 0U;
                    ctxFldIdx < chObj->vpeCoreCtxInfo.numPrevFld;
                    ctxFldIdx++)
                {
                    /* Clear out Y and CbCr buffer pointers */
                    vpeCoreCtxBuf->prevInBuf[ctxFldIdx]
                    [FVID2_YUV_SP_Y_ADDR_IDX] = NULL;
                    vpeCoreCtxBuf->prevInBuf[ctxFldIdx]
                    [FVID2_YUV_SP_CBCR_ADDR_IDX]        = NULL;
                    vpeCoreCtxBuf->prevInFid[ctxFldIdx] = 0U;
                }
            }
            else
            {
                /* move on to next channel */
            }
        }

        /* Check if we indeed have fields to be released. Otherwise, when
         * release context fields is called twice, we would endup queuing
         * a dummy completed request */
        /* Its OK to compare with 0, as minimum context fields required is
         * > 0U and we release context for a given channel at once */
        if(frameIndex != 0U)
        {
            hObj->tempFrameList.numFrames  = frameIndex;
            qObj->procList.inFrameList[0U] = &hObj->tempFrameList;
            qObj->procList.numInLists      = 1U;
            /* Ensure to clear up the outFrameList - as we do not have any in
             * this list */
            qObj->procList.numOutLists = 0U;
            BspUtils_queue(hObj->doneQ, &qObj->qElem, qObj);
        }
        else
        {
            /* Put back into free Q */
            BspUtils_queue(hObj->freeQ, &qObj->qElem, qObj);
        }
    }

    return (retVal);
}

/**
 * vpsMdrvVpeStopIoctl
 * Stops processing of fields queued up.
 */
static Int32 vpsMdrvVpeStopIoctl(VpsMdrv_VpeHandleObj *hObj, Ptr cmdArgs)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cookie;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));

    cookie = BspOsal_disableInterrupt();

    /* Check if have unprocessed request, if so, release them */
    if(0U != hObj->numUnProcessedReq)
    {
        /* Let the mlmCb know that we are trying to stop, do not process
         * Queued up fields and mlmCb is reponsible of releasing up the
         * context fields */
        hObj->isStopped = (UInt32) TRUE;

        BspOsal_restoreInterrupt(cookie);

        /* Wait for current transfer to complete */
        BspOsal_semWait(hObj->stopSyncSem, BSP_OSAL_WAIT_FOREVER);

        cookie = BspOsal_disableInterrupt();
    }

    /* Q up the stored context fields as completed fields */
    retVal = vpsMdrvVpeReleaseCtxFields(hObj);

    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

