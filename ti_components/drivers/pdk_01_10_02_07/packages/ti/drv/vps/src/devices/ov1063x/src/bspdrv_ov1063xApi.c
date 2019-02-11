/*
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
 *  \file bspdrv_ov1063xApi.c
 *
 *  \brief OV1063x video sensor FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov1063x/src/bspdrv_ov1063xPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
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
static Int32 Bsp_ov1063xControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);

static Fdrv_Handle Bsp_ov1063xCreate(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);

static Int32 Bsp_ov1063xDelete(Fdrv_Handle handle, Ptr deleteArgs);
#ifdef __cplusplus
}
#endif
static Int32 Bsp_ov1063xUnlock(void);
static Int32 Bsp_ov1063xLock(void);
static Int32 Bsp_ov1063xLockObj(Bsp_Ov1063xHandleObj *pObj);
static Int32 Bsp_ov1063xUnlockObj(Bsp_Ov1063xHandleObj *pObj);
static Int32 Bsp_ov1063xFreeObj(Bsp_Ov1063xHandleObj *pObj);
static Bsp_Ov1063xHandleObj *Bsp_ov1063xAllocObj(void);

/** \brief OV1063x driver function pointer. */
static const Fvid2_DrvOps gBspOv1063xDrvOps =
{
    FVID2_VID_SENSOR_OV1063X_DRV,           /* Driver ID */
    &Bsp_ov1063xCreate,                     /* Create */
    &Bsp_ov1063xDelete,                     /* Delete */
    &Bsp_ov1063xControl,                    /* Control */
    NULL,                                   /* Queue */
    NULL,                                   /* Dequeue */
    NULL,                                   /* ProcessFrames */
    NULL,                                   /* GetProcessedFrames */
    NULL,                                   /* ProcessRequest */
    NULL                                    /* GetProcessedRequest */
};

/** \brief LI OV1063X driver function pointer. */
static const Fvid2_DrvOps gBspLIOv1063xDrvOps =
{
    FVID2_VID_SENSOR_LI_OV1063X_DRV,        /* Driver ID */
    &Bsp_ov1063xCreate,                     /* Create */
    &Bsp_ov1063xDelete,                     /* Delete */
    &Bsp_ov1063xControl,                    /* Control */
    NULL,                                   /* Queue */
    NULL,                                   /* Dequeue */
    NULL,                                   /* ProcessFrames */
    NULL,                                   /* GetProcessedFrames */
    NULL,                                   /* ProcessRequest */
    NULL                                    /* GetProcessedRequest */
};

/** \brief Multi deserializer OV1063X driver function pointer. */
static const Fvid2_DrvOps gBspMulDesOv1063xDrvOps =
{
    FVID2_VID_SENSOR_MULDES_OV1063X_DRV,    /* Driver ID */
    &Bsp_ov1063xCreate,                     /* Create */
    &Bsp_ov1063xDelete,                     /* Delete */
    &Bsp_ov1063xControl,                    /* Control */
    NULL,                                   /* Queue */
    NULL,                                   /* Dequeue */
    NULL,                                   /* ProcessFrames */
    NULL,                                   /* GetProcessedFrames */
    NULL,                                   /* ProcessRequest */
    NULL                                    /* GetProcessedRequest */
};

/**
 *  \brief Global object storing all information related to all OV1063x driver
 *  handles.
 */
static Bsp_Ov1063xObj     gBspOv1063xObj;

/**
 *  \brief System init for OV1063x  driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ov1063xInit(void)
{
    Int32 status = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspOv1063xObj, 0, sizeof (gBspOv1063xObj));

    /* Create global OV1063x lock */
    initValue = 1;
    gBspOv1063xObj.lock = BspOsal_semCreate(initValue, (Bool)TRUE);
    if (NULL == gBspOv1063xObj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        status = FVID2_EALLOC;
    }

    if (FVID2_SOK == status)
    {
        /* Register OV1063x driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspOv1063xDrvOps);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspOv1063xObj.lock);
        }

        if (status == FVID2_SOK)
        {
            /* Register LI OV1063X driver with FVID2 sub-system */
            status = Fvid2_registerDriver(&gBspLIOv1063xDrvOps);
            if (FVID2_SOK != status)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Registering to FVID2 driver manager failed\r\n");

                /* Error - free acquired resources */
                Fvid2_unRegisterDriver(&gBspOv1063xDrvOps);
                BspOsal_semDelete(&gBspOv1063xObj.lock);
            }
        }

        if (status == FVID2_SOK)
        {
            /* Register MulDes OV1063X driver with FVID2 sub-system */
            status = Fvid2_registerDriver(&gBspMulDesOv1063xDrvOps);
            if (FVID2_SOK != status)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Registering to FVID2 driver manager failed\r\n");

                /* Error - free acquired resources */
                Fvid2_unRegisterDriver(&gBspLIOv1063xDrvOps);
                Fvid2_unRegisterDriver(&gBspOv1063xDrvOps);
                BspOsal_semDelete(&gBspOv1063xObj.lock);
            }
        }
    }

    return (status);
}

/**
 *  \brief System de-init for OV1063x driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ov1063xDeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspOv1063xDrvOps);
    Fvid2_unRegisterDriver(&gBspLIOv1063xDrvOps);
    Fvid2_unRegisterDriver(&gBspMulDesOv1063xDrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspOv1063xObj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief OV1063x create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the OV1063x is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  OV1063x.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          either FVID2_VID_SENSOR_OV1063X_DRV or
 *                          FVID2_VID_SENSOR_LI_OV1063X_DRV or
 *                          FVID2_VID_SENSOR_MULDES_OV1063X_DRV.
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidSensorCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] OV1063x driver return parameter -
 *                          pointer to Bsp_VidSensorCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the status information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_ov1063xCreate(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 status = FVID2_SOK;
    Bsp_Ov1063xHandleObj      *pObj = NULL;
    Bsp_VidSensorCreateParams *sensorCreatePrms;
    Bsp_VidSensorCreateStatus *sensorCreateStatus;

    /* Check parameters */
    if ((NULL == createPrms) ||
        ((nDrvId != FVID2_VID_SENSOR_OV1063X_DRV) &&
         (nDrvId != FVID2_VID_SENSOR_LI_OV1063X_DRV) &&
         (nDrvId != FVID2_VID_SENSOR_MULDES_OV1063X_DRV)))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        sensorCreatePrms = (Bsp_VidSensorCreateParams *) createPrms;
        if (sensorCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\r\n");
            status = FVID2_EINVALID_PARAMS;
        }
        if (sensorCreatePrms->numDevicesAtPort >=
            BSP_VID_SENSOR_DEV_PER_PORT_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid device per port\r\n");
            status = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Allocate driver handle */
        pObj = Bsp_ov1063xAllocObj();
        if (NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\r\n");
            status = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == status)
    {
        /* Store the Driver ID in pObj */
        pObj->nDrvId = nDrvId;
    }

    if (FVID2_SOK == status)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            sensorCreatePrms,
            sizeof (*sensorCreatePrms));
    }

#ifndef VSDK_OPTIM_SENSOR_INIT
    if (FVID2_SOK == status)
    {
        /*Get sensor features for future referece */
        status = Bsp_ov1063xGetSensorFeatures(pObj, &pObj->sensorFeature);
    }
#endif

    if (FVID2_SOK == status)
    {
        if (sensorCreatePrms->sensorCfg == NULL)
        {
            /* Configure sensor with default configuration :1280x800 */
            status = Bsp_ov1063xSensorConfig(pObj, NULL, 0);
        }
        else
        {
            status = Bsp_ov1063xSensorConfig(pObj,
                                             sensorCreatePrms->sensorCfg,
                                             sensorCreatePrms->numSensorCfg
                                             );
        }

        pObj->sensorConfig.dataformat   = FVID2_DF_YUV422I_YUYV;
        pObj->sensorConfig.standard     = FVID2_STD_720P_60;
        pObj->sensorConfig.fps          = FVID2_FPS_30;
        pObj->sensorConfig.videoIfWidth = FVID2_VIFW_10BIT;
    }

    if (FVID2_SOK == status)
    {
        /* Take sensor to standby state */
        status = Bsp_ov1063xSensorStartStop(pObj, (UInt32)FALSE);
    }

    if ((FVID2_SOK != status) && (pObj != NULL))
    {
        Bsp_ov1063xFreeObj(pObj);
        pObj = NULL;
    }

    /* Fill the status if possible */
    if (NULL != createStatusArgs)
    {
        sensorCreateStatus =
            (Bsp_VidSensorCreateStatus *) createStatusArgs;
        sensorCreateStatus->retVal = status;
    }

    return (pObj);
}

/**
 *  \brief Delete function that is called when Fvid2_delete is called.
 *
 *  This API
 *      - free's driver handle object
 *
 *  \param handle           [IN] Driver handle.
 *  \param deleteArgs       [IN] Not used currently. Meant for future purpose.
 *                          Set this to NULL.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code. *
 */
static Int32 Bsp_ov1063xDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_Ov1063xHandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* Free driver handle object */
        pObj   = (Bsp_Ov1063xHandleObj *) handle;
        status = Bsp_ov1063xFreeObj(pObj);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Free object failed\r\n");
        }
    }

    return (status);
}

/**
 *  \brief Control API that gets called when Fvid2_control is called.
 *
 *  This API does handle level semaphore locking
 *
 *  \param handle           [IN] OV1063x driver handle returned by
 *                          create function.
 *  \param cmd              [IN] Supports the standard video decoder interface
 *                          commands.
 *  \param cmdArgs          [IN] Depending on the command this will vary.
 *  \param cmdStatusArgs    [OUT] Depending on the command this will vary.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error codes for illegal parameters and
 *                          I2C command RX/TX error.
 */
static Int32 Bsp_ov1063xControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_Ov1063xHandleObj *pObj = NULL;
    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pObj = (Bsp_Ov1063xHandleObj *) handle;

        /* lock handle */
        Bsp_ov1063xLockObj(pObj);

        switch (cmd)
        {
            case IOCTL_BSP_VID_SENSOR_RESET:
                status = Bsp_ov1063xSoftwareReset(pObj);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CHIP_ID:
                status = Bsp_ov1063xGetChipId(
                    pObj,
                    (Bsp_VidSensorChipIdParams *) cmdArgs,
                    (Bsp_VidSensorChipIdStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                status = Bsp_ov1063xSensorStartStop(pObj, (UInt32)TRUE);
                break;

            case FVID2_STOP:
                status = Bsp_ov1063xSensorStartStop(pObj, (UInt32)FALSE);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_WRITE:
                status = Bsp_ov1063xRegWrite(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_READ:
                status = Bsp_ov1063xRegRead(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;
            case IOCTL_BSP_VID_SENSOR_GET_FEATURES:
                BspUtils_memcpy((Bsp_VidSensorFeatures *) cmdArgs,
                                &pObj->sensorFeature,
                                sizeof (Bsp_VidSensorFeatures));
                break;
            case IOCTL_BSP_VID_SENSOR_SET_CONFIG:
                status =
                    Bsp_ov1063xSetConfig(pObj,
                                         ((Bsp_VidSensorConfigParams *) (
                                              cmdArgs)));
                break;
            case IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS:
                status =
                    Bsp_ov1063xSetFlipParams(pObj,
                                         ((Bsp_VidSensorFlipParams *) (
                                              cmdArgs)));
                break;
            case IOCTL_BSP_VID_SENSOR_GET_CONFIG:
                BspUtils_memcpy((Bsp_VidSensorConfigParams *) cmdArgs,
                                &pObj->sensorConfig,
                                sizeof (Bsp_VidSensorConfigParams));
                break;
            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\r\n");
                status = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_ov1063xUnlockObj(pObj);
    }

    return (status);
}

/**
 *  \brief Allocates driver object.
 *
 *  Searches in list of driver handles and allocate's a 'NOT IN USE' handle
 *  Also create's handle level semaphore lock.
 *
 *  Returns NULL in case handle could not be allocated.
 */
static Bsp_Ov1063xHandleObj *Bsp_ov1063xAllocObj(void)
{
    UInt32 handleId;
    Bsp_Ov1063xHandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_ov1063xLock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_OV1063X_OBJ_STATE_UNUSED ==
            gBspOv1063xObj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspOv1063xObj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_OV1063X_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool)TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\r\n");
                /* Error - release object */
                pObj->state = BSP_OV1063X_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_ov1063xUnlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_ov1063xFreeObj(Bsp_Ov1063xHandleObj *pObj)
{
    Int32 status = FVID2_EFAIL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_ov1063xLock();

    if (pObj->state != BSP_OV1063X_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_OV1063X_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);

        status = FVID2_SOK;
    }

    /* Release global lock */
    Bsp_ov1063xUnlock();

    return (status);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_ov1063xLockObj(Bsp_Ov1063xHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_ov1063xUnlockObj(Bsp_Ov1063xHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_ov1063xLock(void)
{
    BspOsal_semWait(gBspOv1063xObj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_ov1063xUnlock(void)
{
    BspOsal_semPost(gBspOv1063xObj.lock);

    return (FVID2_SOK);
}

