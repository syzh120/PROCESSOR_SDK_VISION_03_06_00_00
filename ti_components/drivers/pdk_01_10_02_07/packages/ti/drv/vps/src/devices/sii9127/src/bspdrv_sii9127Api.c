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
 *  \file bspdrv_sii9127Api.c
 *
 *  \brief SII9127 video decoder FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <sii9127/src/bspdrv_sii9127Priv.h>

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
static Fdrv_Handle Bsp_sii9127Create(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 Bsp_sii9127Delete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 Bsp_sii9127Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif
static Bsp_Sii9127HandleObj *Bsp_sii9127AllocObj(void);
static Int32 Bsp_sii9127FreeObj(Bsp_Sii9127HandleObj *pObj);

static Int32 Bsp_sii9127LockObj(Bsp_Sii9127HandleObj *pObj);
static Int32 Bsp_sii9127UnlockObj(Bsp_Sii9127HandleObj *pObj);
static Int32 Bsp_sii9127Lock(void);
static Int32 Bsp_sii9127Unlock(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief SII9127 driver function pointer. */
static const Fvid2_DrvOps gBspSii9127DrvOps =
{
    FVID2_VID_DEC_SII9127_DRV,          /* Driver ID */
    &Bsp_sii9127Create,                 /* Create */
    &Bsp_sii9127Delete,                 /* Delete */
    &Bsp_sii9127Control,                /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    NULL,                               /* ProcessRequest */
    NULL                                /* GetProcessedRequest */
};

/**
 *  \brief Global object storing all information related to all SII9127 driver
 *  handles.
 */
static Bsp_Sii9127Obj     gBspSii9127Obj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for SII9127 driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_sii9127Init(void)
{
    Int32 retVal = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspSii9127Obj, 0, sizeof (gBspSii9127Obj));

    /* Create global SII9127 lock */
    initValue           = (Int32) 1;
    gBspSii9127Obj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBspSii9127Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        retVal = FVID2_EALLOC;
    }

    if (FVID2_SOK == retVal)
    {
        /* Register SII9127 driver with FVID2 sub-system */
        retVal = Fvid2_registerDriver(&gBspSii9127DrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspSii9127Obj.lock);
        }
    }

    return (retVal);
}

/**
 *  \brief System de-init for SII9127 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_sii9127DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspSii9127DrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspSii9127Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief SII9127 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the SII9127 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  SII9127.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          FVID2_VID_DEC_SII9127_DRV.
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidDecCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] SII9127 driver return parameter -
 *                          pointer to Bsp_VidDecCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the retVal information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_sii9127Create(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createPrms,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Sii9127HandleObj   *pObj = NULL;
    Bsp_VidDecCreateParams *vidDecCreatePrms;
    Bsp_VidDecCreateStatus *vidDecCreateStatus;

    /* Check parameters */
    if ((NULL == createPrms) ||
        (drvId != FVID2_VID_DEC_SII9127_DRV) ||
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
        pObj = Bsp_sii9127AllocObj();
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

        Bsp_sii9127ResetRegCache(pObj);
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
static Int32 Bsp_sii9127Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Sii9127HandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        /* Free driver handle object */
        pObj   = (Bsp_Sii9127HandleObj *) handle;
        retVal = Bsp_sii9127FreeObj(pObj);
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
 *  \param handle           [IN] SII9127 driver handle returned by
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
static Int32 Bsp_sii9127Control(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Sii9127HandleObj *pObj = NULL;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if (FVID2_SOK == retVal)
    {
        pObj = (Bsp_Sii9127HandleObj *) handle;

        /* lock handle */
        Bsp_sii9127LockObj(pObj);

        switch (cmd)
        {
            case IOCTL_BSP_VID_DEC_RESET:
                retVal = Bsp_sii9127Reset(pObj);
                break;

            case IOCTL_BSP_VID_DEC_GET_CHIP_ID:
                retVal = Bsp_sii9127GetChipId(
                    pObj,
                    (Bsp_VidDecChipIdParams *) cmdArgs,
                    (Bsp_VidDecChipIdStatus *) cmdStatusArgs);
                break;

            case IOCTL_BSP_VID_DEC_SET_VIDEO_MODE:
                retVal = Bsp_sii9127SetVideoMode(
                    pObj,
                    (Bsp_VidDecVideoModeParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_DEC_GET_VIDEO_STATUS:
                retVal = Bsp_sii9127GetVideoStatus(
                    pObj,
                    (Bsp_VidDecVideoStatusParams *) cmdArgs,
                    (Bsp_VidDecVideoStatus *) cmdStatusArgs);
                break;

            case FVID2_START:
                retVal = Bsp_sii9127Start(pObj);
                break;

            case FVID2_STOP:
                retVal = Bsp_sii9127Stop(pObj);
                break;

            case IOCTL_BSP_VID_DEC_REG_WRITE:
                retVal = Bsp_sii9127RegWrite(
                    pObj,
                    (Bsp_VidDecRegRdWrParams *) cmdArgs);
                break;

            case IOCTL_BSP_VID_DEC_REG_READ:
                retVal = Bsp_sii9127RegRead(
                    pObj,
                    (Bsp_VidDecRegRdWrParams *) cmdArgs);
                break;

            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_sii9127UnlockObj(pObj);
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
static Bsp_Sii9127HandleObj *Bsp_sii9127AllocObj(void)
{
    UInt32 handleId;
    Bsp_Sii9127HandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_sii9127Lock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_SII9127_OBJ_STATE_UNUSED ==
            gBspSii9127Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspSii9127Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_SII9127_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue  = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool) TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\r\n");
                /* Error - release object */
                pObj->state = BSP_SII9127_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_sii9127Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_sii9127FreeObj(Bsp_Sii9127HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_sii9127Lock();

    if (pObj->state != BSP_SII9127_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_SII9127_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);
    }

    /* Release global lock */
    Bsp_sii9127Unlock();

    return (FVID2_SOK);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_sii9127LockObj(Bsp_Sii9127HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_sii9127UnlockObj(Bsp_Sii9127HandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_sii9127Lock(void)
{
    BspOsal_semWait(gBspSii9127Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_sii9127Unlock(void)
{
    BspOsal_semPost(gBspSii9127Obj.lock);

    return (FVID2_SOK);
}

