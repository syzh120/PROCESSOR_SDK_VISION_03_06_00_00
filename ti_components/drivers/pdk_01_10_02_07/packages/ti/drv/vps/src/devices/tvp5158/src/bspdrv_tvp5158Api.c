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
 *  \file bspdrv_tvp5158Api.c
 *
 *  \brief TVP5158 video encoder FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <tvp5158/src/bspdrv_tvp5158Priv.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>

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
static Fdrv_Handle Bsp_tvp5158Create(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 Bsp_tvp5158Delete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 Bsp_tvp5158Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif
static Bsp_Tvp5158HandleObj *Bsp_tvp5158AllocObj(void);
static Int32 Bsp_tvp5158FreeObj(Bsp_Tvp5158HandleObj *pObj);

static Int32 Bsp_tvp5158LockObj(Bsp_Tvp5158HandleObj *pObj);
static Int32 Bsp_tvp5158UnlockObj(Bsp_Tvp5158HandleObj *pObj);
static Int32 Bsp_tvp5158Lock(void);
static Int32 Bsp_tvp5158Unlock(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief TVP5158 driver function pointer. */
static const Fvid2_DrvOps gBspTvp5158DrvOps =
{
    FVID2_VID_DEC_TVP5158_DRV,          /* Driver ID */
    &Bsp_tvp5158Create,                 /* Create */
    &Bsp_tvp5158Delete,                 /* Delete */
    &Bsp_tvp5158Control,                /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    NULL,                               /* ProcessRequest */
    NULL                                /* GetProcessedRequest */
};

/**
 *  \brief Global object storing all information related to all TVP5158 driver
 *  handles.
 */
static Bsp_Tvp5158Obj     gBspTvp5158Obj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for TVP5158 driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_tvp5158Init(void)
{
    Int32 retVal = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspTvp5158Obj, 0, sizeof (gBspTvp5158Obj));

    /* Create global TVP5158 lock */
    initValue = 1;
    gBspTvp5158Obj.lock = BspOsal_semCreate(initValue, (Bool)TRUE);
    if (NULL == gBspTvp5158Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        retVal = FVID2_EALLOC;
    }

    if (FVID2_SOK == retVal)
    {
        /* Register TVP5158 driver with FVID2 sub-system */
        retVal = Fvid2_registerDriver(&gBspTvp5158DrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspTvp5158Obj.lock);
        }
    }

    return (retVal);
}

/**
 *  \brief System de-init for TVP5158 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_tvp5158DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspTvp5158DrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspTvp5158Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief TVP5158 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the TVP5158 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  TVP5158.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          FVID2_VID_DEC_TVP5158_DRV.
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidDecCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] TVP5158 driver return parameter -
 *                          pointer to Bsp_VidDecCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the retVal information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_tvp5158Create(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Tvp5158HandleObj   *pObj = NULL;
    Bsp_VidDecCreateParams *vidDecCreatePrms;
    Bsp_VidDecCreateStatus *vidDecCreateStatus;

    /* Check parameters */
    if ((NULL == createPrms) ||
        (drvId != FVID2_VID_DEC_TVP5158_DRV) ||
        (instId != 0U))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        vidDecCreatePrms = (Bsp_VidDecCreateParams *) createPrms;
        if (vidDecCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Allocate driver handle */
        pObj = Bsp_tvp5158AllocObj();
        if (NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            vidDecCreatePrms,
            sizeof (*vidDecCreatePrms));
    }

    /* Fill the retVal if possible */
    if (NULL != createStatusArgs)
    {
        vidDecCreateStatus =
            (Bsp_VidDecCreateStatus *) createStatusArgs;
        vidDecCreateStatus->retVal = retVal;
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
static Int32 Bsp_tvp5158Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Tvp5158HandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Free driver handle object */
        pObj   = (Bsp_Tvp5158HandleObj *) handle;
        retVal = Bsp_tvp5158FreeObj(pObj);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Free object failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  \brief Control API that gets called when Fvid2_control is called.
 *
 *  This API does handle level semaphore locking
 *
 *  \param handle           [IN] TVP5158 driver handle returned by
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
static Int32 Bsp_tvp5158Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Tvp5158HandleObj *pObj = NULL;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        pObj = (Bsp_Tvp5158HandleObj *) handle;

        /* lock handle */
        Bsp_tvp5158LockObj(pObj);

        switch (cmd)
        {
            case IOCTL_BSP_VID_DEC_RESET:
                retVal = Bsp_tvp5158Reset(pObj);
                break;

            case IOCTL_BSP_VID_DEC_GET_CHIP_ID:
                retVal = Bsp_tvp5158GetChipId(
                    pObj,
                    (Bsp_VidDecChipIdParams *) cmdArgs,
                    (Bsp_VidDecChipIdStatus *) cmdStatusArgs);
                break;

            case IOCTL_BSP_VID_DEC_SET_VIDEO_MODE:
                retVal = Bsp_tvp5158SetVideoMode(
                    pObj,
                    (Bsp_VidDecVideoModeParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS:
                retVal = Bsp_tvp5158GetVideoStatus(
                    pObj,
                    (Bsp_VidDecVideoStatusParams *) cmdArgs,
                    (Bsp_VidDecVideoStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                retVal = Bsp_tvp5158Start(pObj);
                break;

            case FVID2_STOP:
                retVal = Bsp_tvp5158Stop(pObj);
                break;

            case IOCTL_BSP_VID_DEC_REG_WRITE:
                retVal = Bsp_tvp5158RegWrite(
                    pObj,
                    (Bsp_VidDecRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_DEC_REG_READ:
                retVal = Bsp_tvp5158RegRead(
                    pObj,
                    (Bsp_VidDecRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_DEC_SET_VIDEO_COLOR:
                retVal = Bsp_tvp5158SetVideoColor(
                    pObj,
                    (Bsp_VidDecColorParams *) cmdArgs);
                break;

            case IOCTL_BSP_TVP5158_SET_VIDEO_NF:
                retVal = Bsp_tvp5158SetVideoNf(
                    pObj,
                    (Bsp_Tvp5158VideoNfParams *) cmdArgs);
                break;

            case IOCTL_BSP_TVP5158_SET_AUDIO_MODE:
                retVal = Bsp_tvp5158SetAudioMode(
                    pObj,
                    (Bsp_Tvp5158AudioModeParams *) cmdArgs);
                break;

            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_tvp5158UnlockObj(pObj);
    }

    return (retVal);
}

/**
 *  \brief Allocates driver object.
 *
 *  Searches in list of driver handles and allocate's a 'NOT IN USE' handle
 *  Also create's handle level semaphore lock.
 *
 *  Returns NULL in case handle could not be allocated.
 */
static Bsp_Tvp5158HandleObj *Bsp_tvp5158AllocObj(void)
{
    UInt32 handleId;
    Bsp_Tvp5158HandleObj *pObj = NULL;
    Int32 initValue;

    /* Take global lock to avoid race condition */
    Bsp_tvp5158Lock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_TVP5158_OBJ_STATE_UNUSED ==
            gBspTvp5158Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspTvp5158Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_TVP5158_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool)TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\r\n");
                /* Error - release object */
                pObj->state = BSP_TVP5158_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_tvp5158Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_tvp5158FreeObj(Bsp_Tvp5158HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_tvp5158Lock();

    if (pObj->state != BSP_TVP5158_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_TVP5158_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);
    }

    /* Release global lock */
    Bsp_tvp5158Unlock();

    return (FVID2_SOK);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_tvp5158LockObj(Bsp_Tvp5158HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_tvp5158UnlockObj(Bsp_Tvp5158HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_tvp5158Lock(void)
{
    BspOsal_semWait(gBspTvp5158Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_tvp5158Unlock(void)
{
    BspOsal_semPost(gBspTvp5158Obj.lock);

    return (FVID2_SOK);
}

