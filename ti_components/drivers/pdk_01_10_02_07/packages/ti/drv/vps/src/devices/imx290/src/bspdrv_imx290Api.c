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
 *  \file bspdrv_imx290Api.c
 *
 *  \brief IMX290 video sensor FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <imx290/src/bspdrv_imx290Priv.h>

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
static Int32 Bsp_imx290Control(Fdrv_Handle handle,
                               UInt32      cmd,
                               Ptr         cmdArgs,
                               Ptr         cmdStatusArgs);

static Fdrv_Handle Bsp_imx290Create(UInt32                   nDrvId,
                                    UInt32                   instId,
                                    Ptr                      createPrms,
                                    Ptr                      createStatusArgs,
                                    const Fvid2_DrvCbParams *fdmCbPrms);

static Int32 Bsp_imx290Delete(Fdrv_Handle handle, Ptr deleteArgs);
#ifdef __cplusplus
}
#endif
static Int32 Bsp_imx290Unlock(void);
static Int32 Bsp_imx290Lock(void);
static Int32 Bsp_imx290FreeObj(Bsp_imx290HandleObj *pObj);
static Bsp_imx290HandleObj *Bsp_imx290AllocObj(void);

/** \brief IMX290 driver function pointer. */
static const Fvid2_DrvOps gBspimx290Csi2DrvOps =
{
    FVID2_VID_SENSOR_GW4200_IMX290_DRV,     /* Driver ID */
    &Bsp_imx290Create,                      /* Create */
    &Bsp_imx290Delete,                      /* Delete */
    &Bsp_imx290Control,                     /* Control */
    NULL,                                   /* Queue */
    NULL,                                   /* Dequeue */
    NULL,                                   /* ProcessFrames */
    NULL,                                   /* GetProcessedFrames */
    NULL,                                   /* ProcessRequest */
    NULL                                    /* GetProcessedRequest */
};

/**
 *  \brief Global object storing all information related to all IMX290 driver
 *  handles.
 */
static Bsp_imx290Obj      gBspimx290Obj;

/**
 *  \brief System init for IMX290  driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_imx290Init(void)
{
    Int32 status = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspimx290Obj, 0, sizeof (gBspimx290Obj));

    /* Create global IMX290 lock */
    initValue          = 1;
    gBspimx290Obj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if (NULL == gBspimx290Obj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        status = FVID2_EALLOC;
    }

    if (FVID2_SOK == status)
    {
        /* Register IMX290 driver with FVID2 sub-system */
        status = Fvid2_registerDriver(&gBspimx290Csi2DrvOps);
        if (FVID2_SOK != status)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspimx290Obj.lock);
        }
    }

    return (status);
}

/**
 *  \brief System de-init for IMX290 driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_imx290DeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspimx290Csi2DrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspimx290Obj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief IMX290 create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the IMX290 is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          either FVID2_VID_SENSOR_GW4200_IMX290_DRV
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Not used. Set to NULL.
 *  \param createStatusArgs [OUT] Not used. Set to NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_imx290Create(UInt32                   nDrvId,
                                    UInt32                   instId,
                                    Ptr                      createPrms,
                                    Ptr                      createStatusArgs,
                                    const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 status = FVID2_SOK;
    Bsp_imx290HandleObj *pObj = NULL;

    /* Check parameters */
    if (nDrvId != FVID2_VID_SENSOR_GW4200_IMX290_DRV)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Invalid parameters\r\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* Allocate driver handle */
        pObj = Bsp_imx290AllocObj();
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
        pObj->instId = instId;
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
static Int32 Bsp_imx290Delete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 status = FVID2_SOK;
    Bsp_imx290HandleObj *pObj;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
    }

    if (FVID2_SOK == status)
    {
        /* Free driver handle object */
        pObj   = (Bsp_imx290HandleObj *) handle;
        status = Bsp_imx290FreeObj(pObj);
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
 *  \param handle           [IN] IMX290 driver handle returned by
 *                          create function.
 *  \param cmd              [IN] Not used. Set to NULL.
 *  \param cmdArgs          [IN] Not used. Set to NULL.
 *  \param cmdStatusArgs    [OUT] Not used. Set to NULL.
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error codes for illegal parameters and
 *                          I2C command RX/TX error.
 */
static Int32 Bsp_imx290Control(Fdrv_Handle handle,
                               UInt32      cmd,
                               Ptr         cmdArgs,
                               Ptr         cmdStatusArgs)
{
    Int32 status = FVID2_SOK;

    /* Check parameters */
    if (NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        status = FVID2_EBADARGS;
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
static Bsp_imx290HandleObj *Bsp_imx290AllocObj(void)
{
    UInt32 handleId;
    Bsp_imx290HandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_imx290Lock();

    /* Find a unallocated object in pool */
    for (handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if (BSP_IMX290_OBJ_STATE_UNUSED ==
            gBspimx290Obj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspimx290Obj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof (*pObj));
            pObj->state    = BSP_IMX290_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue  = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool) TRUE);
            if (NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\r\n");
                /* Error - release object */
                pObj->state = BSP_IMX290_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_imx290Unlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_imx290FreeObj(Bsp_imx290HandleObj *pObj)
{
    Int32 status = FVID2_EFAIL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_imx290Lock();

    if (pObj->state != BSP_IMX290_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_IMX290_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);

        status = FVID2_SOK;
    }

    /* Release global lock */
    Bsp_imx290Unlock();

    return (status);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_imx290Lock(void)
{
    BspOsal_semWait(gBspimx290Obj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_imx290Unlock(void)
{
    BspOsal_semPost(gBspimx290Obj.lock);

    return (FVID2_SOK);
}

