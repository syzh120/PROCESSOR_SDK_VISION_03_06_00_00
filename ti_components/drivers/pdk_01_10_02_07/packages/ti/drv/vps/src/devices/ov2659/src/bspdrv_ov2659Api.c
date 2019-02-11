/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file bspdrv_ov2659Api.c
 *
 *  \brief OV2659 video sensor FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ov2659/src/bspdrv_ov2659Priv.h>

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
static Int32 Bsp_ov2659Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);

static Fdrv_Handle Bsp_ov2659Create(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);

static Int32 Bsp_ov2659Delete(Fdrv_Handle handle, Ptr deleteArgs);
#ifdef __cplusplus
}
#endif
static Int32 Bsp_ov2659Unlock(void);
static Int32 Bsp_ov2659Lock(void);
static Int32 Bsp_ov2659LockObj(Bsp_Ov2659HandleObj *pObj);
static Int32 Bsp_ov2659UnlockObj(Bsp_Ov2659HandleObj *pObj);
static Int32 Bsp_ov2659FreeObj(Bsp_Ov2659HandleObj *pObj);
static Bsp_Ov2659HandleObj *Bsp_ov2659AllocObj(void);

/** \brief OV2659 driver function pointer. */
static const Fvid2_DrvOps gBspOv2659DrvOps =
{
    FVID2_VID_SENSOR_OV2659_DRV,           /* Driver ID */
    &Bsp_ov2659Create,                     /* Create */
    &Bsp_ov2659Delete,                     /* Delete */
    &Bsp_ov2659Control,                    /* Control */
    NULL,                                   /* Queue */
    NULL,                                   /* Dequeue */
    NULL,                                   /* ProcessFrames */
    NULL,                                   /* GetProcessedFrames */
    NULL,                                   /* ProcessRequest */
    NULL                                    /* GetProcessedRequest */
};

/**
 *  \brief Global object storing all information related to all OV2659 driver
 *  handles.
 */
static Bsp_Ov2659Obj     gBspOv2659Obj;

/**
 *  \brief System init for OV2659  driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ov2659Init(void)
{
    Int32 status = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspOv2659Obj, 0, sizeof (gBspOv2659Obj));

    /* Create global OV2659 lock */
    initValue = 1;
    gBspOv2659Obj.lock = BspOsal_semCreate(initValue, (Bool)TRUE);
    if (NULL == gBspOv2659Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        status = FVID2_EALLOC;
    }

    if (FVID2_SOK == status)
    {
        /* Register OV2659 driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspOv2659DrvOps);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspOv2659Obj.lock);
        }
    }

    return (status);
}

/**
 *  \brief System de-init for OV2659 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_ov2659DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspOv2659DrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspOv2659Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief OV2659 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the OV2659 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  OV2659.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          either FVID2_VID_SENSOR_OV2659_DRV
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidSensorCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] OV2659 driver return parameter -
 *                          pointer to Bsp_VidSensorCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the status information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_ov2659Create(UInt32                   nDrvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 status = FVID2_SOK;
    Bsp_Ov2659HandleObj      *pObj = NULL;
    Bsp_VidSensorCreateParams *sensorCreatePrms;
    Bsp_VidSensorCreateStatus *sensorCreateStatus;

    /* Check parameters */
    if ((NULL == createPrms) ||
        ((nDrvId != FVID2_VID_SENSOR_OV2659_DRV)))
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
        pObj = Bsp_ov2659AllocObj();
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
    if (FVID2_SOK == status)
    {
        /*Get sensor features for future referece */
        status = Bsp_ov2659GetSensorFeatures(pObj, &pObj->sensorFeature);
    }

    if (FVID2_SOK == status)
    {
        if (sensorCreatePrms->sensorCfg == NULL)
        {
            /* Configure sensor with default configuration :1280x800 */
            status = Bsp_ov2659SensorConfig(pObj, NULL, 0);
        }
        else
        {
            status = Bsp_ov2659SensorConfig(pObj,
                                             sensorCreatePrms->sensorCfg,
                                             sensorCreatePrms->numSensorCfg
                                             );
        }

        pObj->sensorConfig.dataformat   = FVID2_DF_YUV422I_YUYV;
        pObj->sensorConfig.standard     = FVID2_STD_720P_60;
        pObj->sensorConfig.fps          = FVID2_FPS_30;
        pObj->sensorConfig.videoIfWidth = FVID2_VIFW_8BIT;
    }

    if (FVID2_SOK == status)
    {
        /* Take sensor to standby state */
        status = Bsp_ov2659SensorStartStop(pObj, (UInt32)FALSE);
    }

    if ((FVID2_SOK != status) && (pObj != NULL))
    {
        Bsp_ov2659FreeObj(pObj);
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
static Int32 Bsp_ov2659Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_Ov2659HandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* Free driver handle object */
        pObj   = (Bsp_Ov2659HandleObj *) handle;
        status = Bsp_ov2659FreeObj(pObj);
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
 *  \param handle           [IN] OV2659 driver handle returned by
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
static Int32 Bsp_ov2659Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_Ov2659HandleObj *pObj = NULL;
    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        pObj = (Bsp_Ov2659HandleObj *) handle;

        /* lock handle */
        Bsp_ov2659LockObj(pObj);

        switch (cmd)
        {
            case IOCTL_BSP_VID_SENSOR_RESET:
                status = Bsp_ov2659SoftwareReset(pObj);
                break;

            case IOCTL_BSP_VID_SENSOR_GET_CHIP_ID:
                status = Bsp_ov2659GetChipId(
                    pObj,
                    (Bsp_VidSensorChipIdParams *) cmdArgs,
                    (Bsp_VidSensorChipIdStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                status = Bsp_ov2659SensorStartStop(pObj, (UInt32)TRUE);
                break;

            case FVID2_STOP:
                status = Bsp_ov2659SensorStartStop(pObj, (UInt32)FALSE);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_WRITE:
                status = Bsp_ov2659RegWrite(
                    pObj,
                    (Bsp_VidSensorRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_SENSOR_REG_READ:
                status = Bsp_ov2659RegRead(
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
                    Bsp_ov2659SetConfig(pObj,
                                         ((Bsp_VidSensorConfigParams *) (
                                              cmdArgs)));
                break;
            case IOCTL_BSP_VID_SENSOR_SET_FLIP_PARAMS:
                status =
                    Bsp_ov2659SetFlipParams(pObj,
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
        Bsp_ov2659UnlockObj(pObj);
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
static Bsp_Ov2659HandleObj *Bsp_ov2659AllocObj(void)
{
    UInt32 handleId;
    Bsp_Ov2659HandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_ov2659Lock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_OV2659_OBJ_STATE_UNUSED ==
            gBspOv2659Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspOv2659Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_OV2659_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool)TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\r\n");
                /* Error - release object */
                pObj->state = BSP_OV2659_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_ov2659Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_ov2659FreeObj(Bsp_Ov2659HandleObj *pObj)
{
    Int32 status = FVID2_EFAIL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_ov2659Lock();

    if (pObj->state != BSP_OV2659_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_OV2659_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);

        status = FVID2_SOK;
    }

    /* Release global lock */
    Bsp_ov2659Unlock();

    return (status);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_ov2659LockObj(Bsp_Ov2659HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_ov2659UnlockObj(Bsp_Ov2659HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_ov2659Lock(void)
{
    BspOsal_semWait(gBspOv2659Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_ov2659Unlock(void)
{
    BspOsal_semPost(gBspOv2659Obj.lock);

    return (FVID2_SOK);
}

