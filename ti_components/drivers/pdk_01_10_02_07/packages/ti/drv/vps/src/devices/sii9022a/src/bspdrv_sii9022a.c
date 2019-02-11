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
 *  \file bspdrv_sii9022a.c
 *
 *  \brief SII9022A video encoder FVID2 driver API file.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <sii9022a/src/bspdrv_sii9022aPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TPI_INPUTBUS_PIXEL_REP_BIT4_MASK    (0x10U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    Fvid2_Standard standard;
    UInt32         modeCode;
    UInt32         pixClk;
    UInt32         vFreq;
    UInt32         pixels;
    UInt32         lines;
    struct
    {
        UInt32 hBitToHSync;
        UInt32 field2Offset;
        UInt32 hWidth;
        UInt32 vBitToVSync;
        UInt32 vWidth;
    }              embSyncPrms;
    struct
    {
        UInt32 deDelay;
        /**< Width of the area to the left of the active display */
        UInt32 deTop;
        /**< Height of the area to the top of the active display */
        UInt32 deCnt;
        /**< Width of the active display */
        UInt32 deLine;
        /**< Height of the active display */
    } extSyncPrms;
} Bsp_Sii9022aModeInfo;

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
static Fdrv_Handle Bsp_sii9022aCreate(UInt32                   drvId,
                                      UInt32                   instId,
                                      Ptr                      createPrms,
                                      Ptr                      createStatusArgs,
                                      const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 Bsp_sii9022aDelete(Fdrv_Handle handle, Ptr deleteArgs);
static Int32 Bsp_sii9022aControl(Fdrv_Handle handle,
                                 UInt32      cmd,
                                 Ptr         cmdArgs,
                                 Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif

static Bsp_Sii9022aHandleObj *Bsp_sii9022aAllocObj(void);
static Int32 Bsp_sii9022aFreeObj(Bsp_Sii9022aHandleObj *pObj);

static Int32 Bsp_sii9022aUnlockObj(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aLockObj(const Bsp_Sii9022aHandleObj *pObj);

static Int32 Bsp_sii9022aUnlock(void);
static Int32 Bsp_sii9022aLock(void);

static Int32 Bsp_sii9022aGetDetailedChipId(
    const Bsp_Sii9022aHandleObj *pObj,
    Bsp_Sii9022aHdmiChipId      *
    hdmiChipId);
static Int32 Bsp_sii9022aSetMode(Bsp_Sii9022aHandleObj        *pObj,
                                 const Bsp_VidEncConfigParams *cfgPrms);
static Int32 Bsp_sii9022aSetPrms(Bsp_Sii9022aHandleObj    *pObj,
                                 const Bsp_Sii9022aParams *prms);
static Int32 Bsp_sii9022aGetPrms(const Bsp_Sii9022aHandleObj *pObj,
                                 Bsp_Sii9022aParams          *prms);
static Int32 Bsp_sii9022aGetHpd(const Bsp_Sii9022aHandleObj *pObj,
                                Bsp_Sii9022aHpdParams       *hpdPrms);
static Int32 Bsp_sii9022aStart(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aStop(const Bsp_Sii9022aHandleObj *pObj);

static Int32 Bsp_sii9022aDeviceInit(Bsp_Sii9022aHandleObj *pObj);

static Int32 Bsp_sii9022aGetHdmiChipId(const Bsp_Sii9022aHandleObj *pObj,
                                       Bsp_Sii9022aHdmiChipId      *hdmiChipId);

static Int32 Bsp_sii9022aReset(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aEnable(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aPowerUpTxm(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aCfgInBus(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aCfgYcMode(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aCfgSyncMode(const Bsp_Sii9022aHandleObj *pObj);
static Int32 Bsp_sii9022aPrgmEmbSyncTimingInfo(
    Bsp_Sii9022aHandleObj      *pObj,
    const Bsp_Sii9022aModeInfo *modeInfo);
static Int32 Bsp_sii9022aPrgmExtSyncTimingInfo(
    Bsp_Sii9022aHandleObj      *pObj,
    const Bsp_Sii9022aModeInfo *modeInfo);
static Int32 Bsp_sii9022aPrgmAvInfoFrame(
    const Bsp_Sii9022aHandleObj *pObj,
    const Bsp_Sii9022aModeInfo  *modeInfo);
static Int32 Bsp_sii9022aPrgmMdResetRegs(
    Bsp_Sii9022aHandleObj      *pObj,
    const Bsp_Sii9022aModeInfo *modeInfo);
static Int32 Bsp_sii9022aCalcCRC(UInt8  *regAddr,
                                 UInt8  *regValue,
                                 UInt32 *regCnt);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief SII9022A driver function pointer. */
static const Fvid2_DrvOps    gBspSii9022aDrvOps =
{
    FVID2_VID_ENC_SII9022A_DRV,         /* Driver ID */
    &Bsp_sii9022aCreate,                /* Create */
    &Bsp_sii9022aDelete,                /* Delete */
    &Bsp_sii9022aControl,               /* Control */
    NULL,                               /* Queue */
    NULL,                               /* Dequeue */
    NULL,                               /* ProcessFrames */
    NULL,                               /* GetProcessedFrames */
    NULL,                               /* ProcessRequest */
    NULL                                /* GetProcessedRequest */
};

/* Global object storing all information related to all HDMI driver handles */
static Bsp_Sii9022aCommonObj gBspSii9022aObj;

static Bsp_Sii9022aModeInfo  gBspSii9022aModeInfo[] =
{
    {FVID2_STD_480P,     3,   2700,  60,
      858, 525,
      {16,                 0,   62,    9,
      6}, {122,          36,  720,   480}},
    {FVID2_STD_NTSC,     3,   2700,  60,
      858, 525,
      {16,                 264, 62,    9,
      6}, {122,          36,  720,   480}},
    {FVID2_STD_PAL,      18,  2700,  50,864,   625,
      {12,                 314, 64,    5,
      5}, {132,          44,  720,   576}},
    {FVID2_STD_576P,     18,  2700,  50,864,   625,
      {12,                 0,   64,    5,
      5}, {132,          44,  720,   576}},
    {FVID2_STD_XGA_60,   0,   6500,  60,1344,  806,
      {136,                 0,  24,    3,
      6}, {184,          35,  1024,  768}},
    {FVID2_STD_XGA_DSS_TDM_60,   2,   6400,  60,1344,  806,
      {136,                 0,  24,    3,
      6}, {184,          35,  1024,  768}},
    {FVID2_STD_720P_60,  4,   7425,  60,1650,  750,
      {110,                0,   40,    5,
      5}, {260,          25,  1280,  720}},
    {FVID2_STD_720P_50,  19,  7425,  50,1980,  750,
      {440,                0,   40,    5,
      5}, {260,          25,  1280,  720}},
    {FVID2_STD_1080P_30, 34,  7425,  30,2200,  1125,
      {88,                 0,   44,    4,
      5}, {192,          41,  1920,  1080}},
    {FVID2_STD_1080P_50, 16,  7425,  50,2640,  1125,
      {528,                0,   44,    4,
      5}, {192,          41,  1920,  1080}},
    {FVID2_STD_1080P_60, 16,  14850, 60,2200,  1125,
      {88,                 0,   44,    4,
      5}, {192,          41,  1920,  1080}},
    {FVID2_STD_1080I_60, 5,   7425,  60,2200,  1125,
      {88,                 564, 44,    2,
      5}, {192,          20,  1920,  540}},
    {FVID2_STD_1080I_50, 20,  7425,  50,2640,  1125,
      {528,                564, 44,    2,
      5}, {192,          20,  1920,  540}},
    {FVID2_STD_WXGA_60,   2,   8350,  60, 1680,  828,
      {128,                 0,  72,    3,
      6}, {272,          28,  1280,  800}},
};

#define BSP_SII9022A_MAX_MODES  (sizeof(gBspSii9022aModeInfo) / \
                                 sizeof(Bsp_Sii9022aModeInfo))

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief System init for SII9022A driver
 *
 *  This API
 *      - create semaphore locks needed
 *      - registers driver to FVID2 sub-system
 *      - gets called as part of Bsp_deviceInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_sii9022aInit(void)
{
    Int32 retVal = FVID2_SOK;
    Int32 initValue;

    /* Memset global object */
    BspUtils_memset(&gBspSii9022aObj, 0, sizeof(gBspSii9022aObj));

    /* Create global SII9022A lock */
    initValue = (Int32) 1;
    gBspSii9022aObj.lock = BspOsal_semCreate(initValue, (Bool) TRUE);
    if(NULL == gBspSii9022aObj.lock)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Global semaphore create failed\r\n");
        retVal = FVID2_EALLOC;
    }

    if(FVID2_SOK == retVal)
    {
        gBspSii9022aObj.deviceState = BSP_SII9022A_NOT_INITED;

        /* Register SII9022A driver with FVID2 sub-system */
        retVal = Fvid2_registerDriver(&gBspSii9022aDrvOps);
        if(FVID2_SOK != retVal)
        {
            GT_0trace(BspDeviceTrace, GT_ERR,
                      "Registering to FVID2 driver manager failed\r\n");
            /* Error - free acquired resources */
            BspOsal_semDelete(&gBspSii9022aObj.lock);
        }
    }

    return (retVal);
}

/**
 *  \brief System de-init for SII9022A driver
 *
 *  This API
 *      - de-registers driver from FVID2 sub-system
 *      - delete's allocated semaphore locks
 *      - gets called as part of Bsp_deviceDeInit()
 *
 *  \return                 Returns FVID2_SOK on success else returns
 *                          appropriate error code.
 */
Int32 Bsp_sii9022aDeInit(void)
{
    /* Unregister FVID2 driver */
    Fvid2_unRegisterDriver(&gBspSii9022aDrvOps);

    /* Delete semaphore's. */
    BspOsal_semDelete(&gBspSii9022aObj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief SII9022A create API that gets called when Fvid2_create is called.
 *
 *  This API does not configure the SII9022A is any way.
 *
 *  This API
 *      - validates parameters
 *      - allocates driver handle
 *      - stores create arguments in its internal data structure.
 *
 *  Later the create arguments will be used when doing I2C communcation with
 *  SII9022A.
 *
 *  \param drvId            [IN] Driver ID, must be
 *                          FVID2_VID_ENC_SII9022A_DRV.
 *  \param instId           [IN] Must be 0.
 *  \param createPrms       [IN] Create arguments - pointer to valid
 *                          Bsp_VidEncCreateParams. This parameter should
 *                          be non-NULL.
 *  \param createStatusArgs [OUT] SII9022A driver return parameter -
 *                          pointer to Bsp_VidEncCreateStatus.
 *                          This parameter could be NULL and the driver fills
 *                          the retVal information only if this is not NULL.
 *  \param fdmCbPrms        [IN] Not used. Set to NULL
 *
 *  \return                 Returns NULL in case of any error. Otherwise
 *                          returns a valid handle.
 */
static Fdrv_Handle Bsp_sii9022aCreate(UInt32                   drvId,
                                      UInt32                   instId,
                                      Ptr                      createPrms,
                                      Ptr                      createStatusArgs,
                                      const Fvid2_DrvCbParams *fdmCbPrms)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Sii9022aHandleObj  *pObj = NULL;
    Bsp_VidEncCreateParams *vidEncCreatePrms;
    Bsp_VidEncCreateStatus *vidEncCreateStatus;

    /* Check parameters */
    if((NULL == createPrms) ||
       (drvId != FVID2_VID_ENC_SII9022A_DRV) ||
       (instId != 0U))
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer/Invalid parameters\r\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        vidEncCreatePrms = (Bsp_VidEncCreateParams *) createPrms;
        if(vidEncCreatePrms->deviceI2cInstId >= BSP_DEVICE_I2C_INST_ID_MAX)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Invalid I2C instance ID\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Allocate driver handle */
        pObj = Bsp_sii9022aAllocObj();
        if(NULL == pObj)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Alloc object failed\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if(FVID2_SOK == retVal)
    {
        /* Copy parameters to allocate driver handle */
        BspUtils_memcpy(
            &pObj->createPrms,
            vidEncCreatePrms,
            sizeof(*vidEncCreatePrms));

        pObj->prms.outputFormat = BSP_SII9022A_HDMI_RGB;

        /* These settings are for Embedded sync, in SET_MODE IOCTL according to
         * the Video infetface mode it will be set accordingly. */
        pObj->syncCfgReg = 0x04U;
        pObj->inBusCfg   = 0x70U;

        /* FALSE to latch data on falling clock edge. Rising edge otherwise */
        /* Bit 4 of of TPI Input bus and pixel repetation */
        if(pObj->createPrms.clkEdge == FALSE)
        {
            pObj->inBusCfg &= ~((UInt32) TPI_INPUTBUS_PIXEL_REP_BIT4_MASK);
        }
        else
        {
            pObj->inBusCfg |= TPI_INPUTBUS_PIXEL_REP_BIT4_MASK;
        }

        /* Enable DE in syncpolarity register at 0x63 */
        pObj->syncPolarityReg = 0x40U;
        Bsp_sii9022aDeviceInit(pObj);
    }

    /* Fill the retVal if possible */
    if(NULL != createStatusArgs)
    {
        vidEncCreateStatus =
            (Bsp_VidEncCreateStatus *) createStatusArgs;
        vidEncCreateStatus->retVal = retVal;
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
static Int32 Bsp_sii9022aDelete(Fdrv_Handle handle, Ptr deleteArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Sii9022aHandleObj *pObj;

    /* Check parameters */
    if(NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        /* Free driver handle object */
        pObj   = (Bsp_Sii9022aHandleObj *) handle;
        retVal = Bsp_sii9022aFreeObj(pObj);
        if(FVID2_SOK != retVal)
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
 *  \param handle           [IN] SII9022A driver handle returned by
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
static Int32 Bsp_sii9022aControl(Fdrv_Handle handle,
                                 UInt32      cmd,
                                 Ptr         cmdArgs,
                                 Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_SOK;
    Bsp_Sii9022aHandleObj *pObj = NULL;

    /* Check parameters */
    if(NULL == handle)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        pObj = (Bsp_Sii9022aHandleObj *) handle;

        /* lock handle */
        Bsp_sii9022aLockObj(pObj);

        switch(cmd)
        {
            case IOCTL_BSP_VID_ENC_GET_CHIP_ID:
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;

            case IOCTL_BSP_SII9022A_GET_DETAILED_CHIP_ID:
                retVal = Bsp_sii9022aGetDetailedChipId(
                    pObj,
                    (Bsp_Sii9022aHdmiChipId *) cmdArgs);
                break;

            case IOCTL_BSP_VID_ENC_SET_MODE:
                retVal = Bsp_sii9022aSetMode(
                    pObj,
                    (const Bsp_VidEncConfigParams *) cmdArgs);
                break;

            case IOCTL_BSP_SII9022A_SET_PARAMS:
                retVal = Bsp_sii9022aSetPrms(
                    pObj, (const Bsp_Sii9022aParams *) cmdArgs);
                break;

            case IOCTL_BSP_SII9022A_GET_PARAMS:
                retVal = Bsp_sii9022aGetPrms(
                    pObj,
                    (Bsp_Sii9022aParams *) cmdArgs);
                break;

            case IOCTL_BSP_SII9022A_QUERY_HPD:
                retVal = Bsp_sii9022aGetHpd(
                    pObj,
                    (Bsp_Sii9022aHpdParams *) cmdArgs);
                break;

            case FVID2_START:
                retVal = Bsp_sii9022aStart(pObj);
                break;

            case FVID2_STOP:
                retVal = Bsp_sii9022aStop(pObj);
                break;

            default:
                GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported command\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }

        /* Unlock handle */
        Bsp_sii9022aUnlockObj(pObj);
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
static Bsp_Sii9022aHandleObj *Bsp_sii9022aAllocObj(void)
{
    UInt32 handleId;
    Bsp_Sii9022aHandleObj *pObj = NULL;
    Int32  initValue;

    /* Take global lock to avoid race condition */
    Bsp_sii9022aLock();

    /* Find a unallocated object in pool */
    for(handleId = 0U; handleId < BSP_DEVICE_MAX_HANDLES; handleId++)
    {
        if(BSP_SII9022A_OBJ_STATE_UNUSED ==
           gBspSii9022aObj.handlePool[handleId].state)
        {
            /* Free object found */
            pObj = &gBspSii9022aObj.handlePool[handleId];

            /* Init state and handle ID */
            BspUtils_memset(pObj, 0, sizeof(*pObj));
            pObj->state    = BSP_SII9022A_OBJ_STATE_IDLE;
            pObj->handleId = handleId;

            /* Create driver object specific semaphore lock */
            initValue  = 1;
            pObj->lock = BspOsal_semCreate(initValue, (Bool) TRUE);
            if(NULL == pObj->lock)
            {
                GT_0trace(BspDeviceTrace, GT_ERR,
                          "Handle semaphore create failed\r\n");
                /* Error - release object */
                pObj->state = BSP_SII9022A_OBJ_STATE_UNUSED;
                pObj        = NULL;
            }
            break;
        }
    }

    /* Release global lock */
    Bsp_sii9022aUnlock();

    return (pObj);
}

/**
 *  \brief De-Allocate driver object.
 *
 *  Marks handle as 'NOT IN USE'.
 *  Also delete's handle level semaphore lock.
 */
static Int32 Bsp_sii9022aFreeObj(Bsp_Sii9022aHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    /* Take global lock to avoid race condition */
    Bsp_sii9022aLock();

    if(pObj->state != BSP_SII9022A_OBJ_STATE_UNUSED)
    {
        /* Mark state as unused */
        pObj->state = BSP_SII9022A_OBJ_STATE_UNUSED;

        /* Delete object locking semaphore */
        BspOsal_semDelete(&pObj->lock);
    }

    /* Release global lock */
    Bsp_sii9022aUnlock();

    return (FVID2_SOK);
}

/**
 *  \brief Handle level lock.
 */
static Int32 Bsp_sii9022aLockObj(const Bsp_Sii9022aHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Handle level unlock
 */
static Int32 Bsp_sii9022aUnlockObj(const Bsp_Sii9022aHandleObj *pObj)
{
    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    BspOsal_semPost(pObj->lock);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level lock.
 */
static Int32 Bsp_sii9022aLock(void)
{
    BspOsal_semWait(gBspSii9022aObj.lock, BSP_OSAL_WAIT_FOREVER);

    return (FVID2_SOK);
}

/**
 *  \brief Global driver level unlock.
 */
static Int32 Bsp_sii9022aUnlock(void)
{
    BspOsal_semPost(gBspSii9022aObj.lock);

    return (FVID2_SOK);
}

/**
 *  \brief Get chip ID, revision ID and firmware patch ID.
 */
static Int32 Bsp_sii9022aGetDetailedChipId(
    const Bsp_Sii9022aHandleObj *pObj,
    Bsp_Sii9022aHdmiChipId      *
    hdmiChipId)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == hdmiChipId)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        if(BSP_SII9022A_INITED == gBspSii9022aObj.deviceState)
        {
            hdmiChipId->deviceId        = pObj->hdmiChipId.deviceId;
            hdmiChipId->deviceProdRevId = pObj->hdmiChipId.deviceProdRevId;
            hdmiChipId->tpiRevId        = pObj->hdmiChipId.tpiRevId;
            hdmiChipId->hdcpRevTpi      = pObj->hdmiChipId.hdcpRevTpi;
        }
        else
        {
            retVal = FVID2_EFAIL;
        }
    }

    return (retVal);
}

/**
 *  \brief Set Mode
 */
static Int32 Bsp_sii9022aSetMode(Bsp_Sii9022aHandleObj        *pObj,
                                 const Bsp_VidEncConfigParams *cfgPrms)
{
    Int32  retVal = FVID2_SOK;
    UInt32 modeCnt;
    Bsp_Sii9022aModeInfo *modeInfo = NULL;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == cfgPrms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        for(modeCnt = 0U; modeCnt < BSP_SII9022A_MAX_MODES; modeCnt++)
        {
            if(cfgPrms->standard == gBspSii9022aModeInfo[modeCnt].standard)
            {
                modeInfo = &gBspSii9022aModeInfo[modeCnt];
                break;
            }
        }

        if(NULL == modeInfo)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Unsupported mode\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        if(FVID2_VIFM_SCH_ES == cfgPrms->videoIfMode)
        {
            if((FVID2_VIFW_8BIT == cfgPrms->videoIfWidth) ||
               (FVID2_VIFW_10BIT == cfgPrms->videoIfWidth))
            {
                /* Set YC mux mode for 8 and 10-bit interfaces. */
                pObj->syncCfgReg = 0xA4U;
            }
            else
            {
                pObj->syncCfgReg = 0x84U;
            }
            retVal += Bsp_sii9022aCfgSyncMode(pObj);
            retVal += Bsp_sii9022aPrgmEmbSyncTimingInfo(pObj, modeInfo);
        }
        else if(FVID2_VIFM_SCH_DS_AVID_VSYNC == cfgPrms->videoIfMode)
        {
            pObj->syncCfgReg = 0x04U;
            retVal           = Bsp_sii9022aCfgSyncMode(pObj);
            if(FVID2_SOK == retVal)
            {
                retVal = Bsp_sii9022aPrgmExtSyncTimingInfo(pObj, modeInfo);
            }
        }
        else
        {
            retVal = FVID2_EINVALID_PARAMS;
        }

        if(FVID2_SOK == retVal)
        {
            retVal += Bsp_sii9022aPrgmAvInfoFrame(pObj, modeInfo);
            retVal += Bsp_sii9022aPrgmMdResetRegs(pObj, modeInfo);
        }
    }

    return (retVal);
}

static Int32 Bsp_sii9022aSetPrms(Bsp_Sii9022aHandleObj    *pObj,
                                 const Bsp_Sii9022aParams *prms)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == prms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        if(prms->outputFormat >= BSP_SII9022A_MAX_FORMAT)
        {
            GT_0trace(BspDeviceTrace, GT_ERR, "Sii9022A: Wrong output Type\r\n");
            retVal = FVID2_EINVALID_PARAMS;
        }
    }

    if(FVID2_SOK == retVal)
    {
        pObj->prms.outputFormat = prms->outputFormat;
    }

    return (retVal);
}

static Int32 Bsp_sii9022aGetPrms(const Bsp_Sii9022aHandleObj *pObj,
                                 Bsp_Sii9022aParams          *prms)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == prms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        prms->outputFormat = pObj->prms.outputFormat;
    }

    return (retVal);
}

static Int32 Bsp_sii9022aGetHpd(const Bsp_Sii9022aHandleObj *pObj,
                                Bsp_Sii9022aHpdParams       *hpdPrms)
{
    Int32 retVal   = FVID2_SOK;
    UInt8 regValue = (UInt8) 0U, regAddr;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    if(NULL == hpdPrms)
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "Null pointer\n");
        retVal = FVID2_EBADARGS;
    }

    if(FVID2_SOK == retVal)
    {
        regAddr = (UInt8) 0x3DU;
        retVal  = Bsp_deviceRead8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr,
            &regAddr,
            &regValue,
            (UInt32) 1U);
        if(FVID2_SOK == retVal)
        {
            hpdPrms->hpdEvtPending = ((UInt32) regValue & 0x01U);
            hpdPrms->busError      = ((UInt32) regValue & 0x02U);
            hpdPrms->hpdStatus     = ((UInt32) regValue & 0x04U);
        }
    }

    return (retVal);
}

/* Enable TMDS output */
static Int32 Bsp_sii9022aStart(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32  retVal   = FVID2_SOK;
    UInt8  regValue = (UInt8) 0U, regAddr;
    UInt32 regValue32;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    regAddr = (UInt8) 0x1AU;
    retVal  = Bsp_deviceRead8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);
    if(FVID2_SOK == retVal)
    {
        regValue32 = (UInt32) regValue;
        /* Enable HDMI output */
        regValue32 |= 0x01U;
        /* Enable Output TMDS */
        regValue32 &= 0xEFU;

        regValue = (UInt8) regValue32;

        retVal = Bsp_deviceWrite8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr,
            &regAddr,
            &regValue,
            (UInt32) 1U);

        /* Configure Input Bus after starting */
        retVal += Bsp_sii9022aCfgInBus(pObj);
    }

    return (retVal);
}

/* Disable TMDS output */
static Int32 Bsp_sii9022aStop(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32  retVal   = FVID2_SOK;
    UInt8  regValue = (UInt8) 0U, regAddr;
    UInt32 regValue32;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    regAddr = (UInt8) 0x1AU;
    retVal  = Bsp_deviceRead8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);
    if(FVID2_SOK == retVal)
    {
        regValue32 = (UInt32) regValue;
        /* Enable HDMI output */
        regValue32 |= 0x01U;
        /* Power Down Output TMDS Clock */
        regValue32 |= 0x10U;

        regValue = (UInt8) regValue32;

        retVal = Bsp_deviceWrite8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr,
            &regAddr,
            &regValue,
            (UInt32) 1U);
    }

    return (retVal);
}

/*
 *  Device Init
 */
static Int32 Bsp_sii9022aDeviceInit(Bsp_Sii9022aHandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    retVal = Bsp_sii9022aReset(pObj);
    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9022aGetHdmiChipId(pObj, &(pObj->hdmiChipId));
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9022aPowerUpTxm(pObj);
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9022aEnable(pObj);
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9022aCfgInBus(pObj);
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9022aCfgYcMode(pObj);
    }

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9022aCfgSyncMode(pObj);
    }

    if(FVID2_SOK == retVal)
    {
        gBspSii9022aObj.deviceState = BSP_SII9022A_INITED;
    }

    return (retVal);
}

/**
 *  \brief Device Reset
 */
static Int32 Bsp_sii9022aReset(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr[4U];
    UInt8  regValue[4U];
    UInt8  numRegs;
    UInt32 rptCnt = 0U;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    numRegs           = (UInt8) 0U;
    regAddr[numRegs]  = (UInt8) 0xC7U;
    regValue[numRegs] = (UInt8) 0x00U;
    numRegs++;

    for(rptCnt = 0U; rptCnt < 5U; rptCnt++)
    {
        retVal = Bsp_deviceWrite8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr,
            regAddr,
            regValue,
            (UInt32) numRegs);
        if(FVID2_SOK == retVal)
        {
            break;
        }
    }

    if(FVID2_SOK != retVal)
    {
        retVal = FVID2_ETIMEOUT;
    }

    return (retVal);
}

/**
 *  \brief Device Enable
 */
static Int32 Bsp_sii9022aEnable(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regAddr[4];
    UInt8 regValue[4];
    UInt8 numRegs;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    numRegs           = (UInt8) 0U;
    regAddr[numRegs]  = (UInt8) 0xBCU;
    regValue[numRegs] = (UInt8) 0x01U;
    numRegs++;

    regAddr[numRegs]  = 0xBDU;
    regValue[numRegs] = 0x82U;
    numRegs++;

    retVal = Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        regAddr,
        regValue,
        (UInt32) numRegs);
    if(FVID2_SOK == retVal)
    {
        numRegs           = 0;
        regAddr[numRegs]  = 0xBEU;
        regValue[numRegs] = 0x01U;
        numRegs++;

        retVal = Bsp_deviceRead8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr,
            regAddr,
            regValue,
            (UInt32) numRegs);
        if(FVID2_SOK == retVal)
        {
            regValue[0U] |= 0x01U;
            retVal        = Bsp_deviceWrite8(
                pObj->createPrms.deviceI2cInstId,
                pObj->createPrms.deviceI2cAddr,
                regAddr,
                regValue,
                (UInt32) numRegs);
        }
    }

    return (retVal);
}

/**
 *  \brief Device Power up Transmitter
 */
static Int32 Bsp_sii9022aPowerUpTxm(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regAddr;
    UInt8  regValue = (UInt8) 0U;
    UInt32 regValue32;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    regAddr = (UInt8) 0x1EU;
    retVal  = Bsp_deviceRead8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);
    if(FVID2_SOK == retVal)
    {
        regValue32  = (UInt32) regValue;
        regValue32 &= 0xFCU;
        regValue    = (UInt8) regValue32;
        retVal      = Bsp_deviceWrite8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr,
            &regAddr,
            &regValue,
            (UInt32) 1U);
    }

    return (retVal);
}

/**
 *  \brief Configure Input Bus and pixel repetation
 */
static Int32 Bsp_sii9022aCfgInBus(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regAddr;
    UInt8 regValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    regAddr  = (UInt8) 0x08U;
    regValue = pObj->inBusCfg;

    retVal = Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);

    return (retVal);
}

/**
 *  \brief Configure YC Mode
 */
static Int32 Bsp_sii9022aCfgYcMode(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regAddr;
    UInt8 regValue;

    regAddr  = (UInt8) 0x0BU;
    regValue = (UInt8) 0x00U;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    retVal = Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);

    return (retVal);
}

/**
 *  \brief Configure Sync Mode
 */
static Int32 Bsp_sii9022aCfgSyncMode(const Bsp_Sii9022aHandleObj *pObj)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regAddr;
    UInt8 regValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    regAddr  = (UInt8) 0x60U;
    regValue = pObj->syncCfgReg;
    retVal   = Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);

    return (retVal);
}

/**
 *  \brief Get TP5158 chip ID, revision ID and firmware patch ID
 */
static Int32 Bsp_sii9022aGetHdmiChipId(const Bsp_Sii9022aHandleObj *pObj,
                                       Bsp_Sii9022aHdmiChipId      *hdmiChipId)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regAddr[8U];
    UInt8 regValue[8U];
    UInt8 numRegs;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));

    numRegs           = 0;
    regAddr[numRegs]  = 0x1BU;
    regValue[numRegs] = 0;
    numRegs++;

    regAddr[numRegs]  = 0x1CU;
    regValue[numRegs] = 0;
    numRegs++;

    regAddr[numRegs]  = 0x1DU;
    regValue[numRegs] = 0;
    numRegs++;

    regAddr[numRegs]  = 0x30U;
    regValue[numRegs] = 0;
    numRegs++;

    retVal = Bsp_deviceRead8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        regAddr,
        regValue,
        (UInt32) numRegs);
    if(FVID2_SOK == retVal)
    {
        hdmiChipId->deviceId        = regValue[0];
        hdmiChipId->deviceProdRevId = regValue[1];
        hdmiChipId->tpiRevId        = regValue[2];
        hdmiChipId->hdcpRevTpi      = regValue[3];
    }

    return (retVal);
}

/**
 *  \brief Program Timing information for the separate sync input
 */
static Int32 Bsp_sii9022aPrgmExtSyncTimingInfo(
    Bsp_Sii9022aHandleObj      *pObj,
    const Bsp_Sii9022aModeInfo *modeInfo)
{
    Int32  retVal;
    UInt8  regValue[20U], regAddr[20U];
    UInt32 numRegs;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != modeInfo));

    numRegs           = 0;
    regAddr[numRegs]  = 0x62U;
    regValue[numRegs] = (UInt8) (modeInfo->extSyncPrms.deDelay & 0xFFU);
    numRegs++;

    regAddr[numRegs]       = 0x63U;
    pObj->syncPolarityReg &= (UInt8) ~(0x03U);
    pObj->syncPolarityReg |=
        ((modeInfo->extSyncPrms.deDelay & 0x300U) >> 8);
    regValue[numRegs] = (UInt8) (pObj->syncPolarityReg & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x64U;
    regValue[numRegs] = (UInt8) (modeInfo->extSyncPrms.deTop & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x66U;
    regValue[numRegs] = (UInt8) (modeInfo->extSyncPrms.deCnt & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x67U;
    regValue[numRegs] = (UInt8) ((modeInfo->extSyncPrms.deCnt & 0xF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x68U;
    regValue[numRegs] = (UInt8) (modeInfo->extSyncPrms.deLine & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x69U;
    regValue[numRegs] = (UInt8) ((modeInfo->extSyncPrms.deLine & 0x700U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x00U;
    regValue[numRegs] = (UInt8) (modeInfo->pixClk & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x01U;
    regValue[numRegs] = (UInt8) ((modeInfo->pixClk & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x02U;
    regValue[numRegs] = (UInt8) (modeInfo->vFreq & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x03U;
    regValue[numRegs] = (UInt8) ((modeInfo->vFreq & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x04U;
    regValue[numRegs] = (UInt8) (modeInfo->pixels & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x05U;
    regValue[numRegs] = (UInt8) ((modeInfo->pixels & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x06U;
    regValue[numRegs] = (UInt8) (modeInfo->lines & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x07U;
    regValue[numRegs] = (UInt8) ((modeInfo->lines & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x08U;
    regValue[numRegs] = pObj->inBusCfg;
    numRegs++;

    regAddr[numRegs]  = 0x09U;
    regValue[numRegs] = 0x00U;
    numRegs++;

    regAddr[numRegs] = 0x0AU;
    switch(pObj->prms.outputFormat)
    {
        case BSP_SII9022A_HDMI_RGB:
            regValue[numRegs] = 0x10U;
            pObj->isRgbOutput = 1;
            break;

        case BSP_SII9022A_HDMI_YUV444:
            regValue[numRegs] = 0x11U;
            pObj->isRgbOutput = 0;
            break;

        case BSP_SII9022A_HDMI_YUV422:
            regValue[numRegs] = 0x12U;
            pObj->isRgbOutput = 0;
            break;

        case BSP_SII9022A_DVI_RGB:
            regValue[numRegs] = 0x13U;
            pObj->isRgbOutput = 1;
            break;

        default:
            break;
    }
    numRegs++;

    retVal = Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        regAddr,
        regValue,
        numRegs);

    return (retVal);
}

static Int32 Bsp_sii9022aPrgmEmbSyncTimingInfo(
    Bsp_Sii9022aHandleObj      *pObj,
    const Bsp_Sii9022aModeInfo *modeInfo)
{
    Int32  retVal;
    UInt8  regValue[20U], regAddr[20U];
    UInt32 numRegs;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != modeInfo));

    numRegs           = 0;
    regAddr[numRegs]  = 0x62U;
    regValue[numRegs] = (UInt8) (modeInfo->embSyncPrms.hBitToHSync & 0xFFU);
    numRegs++;

    regAddr[numRegs]       = 0x63U;
    pObj->syncPolarityReg &= ((UInt8) ~(0x03U));
    pObj->syncPolarityReg |=
        ((modeInfo->embSyncPrms.hBitToHSync & 0x300U) >> 8);
    regValue[numRegs] = (UInt8) (pObj->syncPolarityReg & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x64U;
    regValue[numRegs] = (UInt8) (modeInfo->embSyncPrms.field2Offset & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x65U;
    regValue[numRegs] = (UInt8) ((modeInfo->embSyncPrms.field2Offset & 0xF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x66U;
    regValue[numRegs] = (UInt8) (modeInfo->embSyncPrms.hWidth & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x67U;
    regValue[numRegs] = (UInt8) ((modeInfo->embSyncPrms.hWidth & 0x300U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x68U;
    regValue[numRegs] = (UInt8) (modeInfo->embSyncPrms.vBitToVSync & 0x3FU);
    numRegs++;

    regAddr[numRegs]  = 0x69U;
    regValue[numRegs] = (UInt8) (modeInfo->embSyncPrms.vWidth & 0x3FU);
    numRegs++;

    regAddr[numRegs]  = 0x00U;
    regValue[numRegs] = (UInt8) (modeInfo->pixClk & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x01U;
    regValue[numRegs] = (UInt8) ((modeInfo->pixClk & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x02U;
    regValue[numRegs] = (UInt8) (modeInfo->vFreq & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x03U;
    regValue[numRegs] = (UInt8) ((modeInfo->vFreq & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x04U;
    regValue[numRegs] = (UInt8) (modeInfo->pixels & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x05U;
    regValue[numRegs] = (UInt8) ((modeInfo->pixels & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x06U;
    regValue[numRegs] = (UInt8) (modeInfo->lines & 0xFFU);
    numRegs++;

    regAddr[numRegs]  = 0x07U;
    regValue[numRegs] = (UInt8) ((modeInfo->lines & 0xFF00U) >> 8);
    numRegs++;

    regAddr[numRegs]  = 0x08U;
    regValue[numRegs] = pObj->inBusCfg;
    numRegs++;

    regAddr[numRegs]  = 0x09U;
    regValue[numRegs] = 0x02U;
    numRegs++;

    regAddr[numRegs] = 0x0AU;
    switch(pObj->prms.outputFormat)
    {
        case BSP_SII9022A_HDMI_RGB:
            regValue[numRegs] = 0x10U;
            pObj->isRgbOutput = 1;
            break;

        case BSP_SII9022A_HDMI_YUV444:
            regValue[numRegs] = 0x11U;
            pObj->isRgbOutput = 0;
            break;

        case BSP_SII9022A_HDMI_YUV422:
            regValue[numRegs] = 0x12U;
            pObj->isRgbOutput = 0;
            break;

        case BSP_SII9022A_DVI_RGB:
            regValue[numRegs] = 0x13U;
            pObj->isRgbOutput = 1;
            break;

        default:
            break;
    }
    numRegs++;

    retVal = Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        regAddr,
        regValue,
        numRegs);

    return (retVal);
}

/* Program AVInfo Frame */
static Int32 Bsp_sii9022aPrgmAvInfoFrame(
    const Bsp_Sii9022aHandleObj *pObj,
    const Bsp_Sii9022aModeInfo  *modeInfo)
{
    Int32  retVal = FVID2_SOK;
    UInt8  regValue[15U], regAddr[15U];
    UInt32 regCnt;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != modeInfo));

    regCnt          = 0;
    regAddr[regCnt] = 0x0DU;
    if(pObj->isRgbOutput)
    {
        regValue[regCnt] = 0x01U;
    }
    else
    {
        regValue[regCnt] = 0x21U;
    }
    regCnt++;

    regAddr[regCnt]  = 0x0EU;
    regValue[regCnt] = 0xA0U;
    regCnt++;

    regAddr[regCnt]  = 0x0FU;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x10U;
    regValue[regCnt] = (UInt8) (modeInfo->modeCode & 0x7FU);
    regCnt++;

    regAddr[regCnt]  = 0x11U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x12U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x13U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x14U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x15U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x16U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x17U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x18U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    regAddr[regCnt]  = 0x19U;
    regValue[regCnt] = 0x00U;
    regCnt++;

    if(FVID2_SOK == retVal)
    {
        retVal = Bsp_sii9022aCalcCRC(regAddr, regValue, &regCnt);
        if(FVID2_SOK == retVal)
        {
            if(BSP_SII9022A_DVI_RGB == pObj->prms.outputFormat)
            {
                BspUtils_memset(regValue, 0, sizeof(regValue));
            }

            retVal = Bsp_deviceWrite8(
                pObj->createPrms.deviceI2cInstId,
                pObj->createPrms.deviceI2cAddr,
                regAddr,
                regValue,
                regCnt);
        }
    }

    regAddr[0]  = 0x19U;
    regValue[0] = 0x00U;
    retVal     += Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        regAddr,
        regValue,
        (UInt32) 1U);

    return (retVal);
}

static Int32 Bsp_sii9022aPrgmMdResetRegs(
    Bsp_Sii9022aHandleObj      *pObj,
    const Bsp_Sii9022aModeInfo *modeInfo)
{
    Int32 retVal = FVID2_SOK;
    UInt8 regAddr, regValue;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != pObj));
    GT_assert(BspDeviceTrace, (NULL != modeInfo));

    regAddr  = (UInt8) 0x63U;
    regValue = pObj->syncPolarityReg;
    retVal   = Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);

    regAddr  = (UInt8) 0x60U;
    regValue = pObj->syncCfgReg;
    retVal  += Bsp_deviceWrite8(
        pObj->createPrms.deviceI2cInstId,
        pObj->createPrms.deviceI2cAddr,
        &regAddr,
        &regValue,
        (UInt32) 1U);
    if(FVID2_SOK == retVal)
    {
        BspOsal_sleep((UInt32) 5U);
        regAddr = (UInt8) 0x61U;
        retVal  = Bsp_deviceRead8(
            pObj->createPrms.deviceI2cInstId,
            pObj->createPrms.deviceI2cAddr,
            &regAddr,
            &regValue,
            (UInt32) 1U);
        if(FVID2_SOK == retVal)
        {
            UInt32 tempSyncPolarityReg;
            UInt32 regValue32;
            /* Set the same sync polarity in 0x63U register */
            regValue32 = (UInt32) regValue;
            tempSyncPolarityReg   = (UInt32) pObj->syncPolarityReg;
            tempSyncPolarityReg  &= (UInt8) (~(0x30U));
            tempSyncPolarityReg  |= ((regValue32 & 0x03U) << 4U);
            pObj->syncPolarityReg = (UInt8) tempSyncPolarityReg;

            regAddr  = (UInt8) 0x63U;
            regValue = pObj->syncPolarityReg;
            retVal   = Bsp_deviceWrite8(
                pObj->createPrms.deviceI2cInstId,
                pObj->createPrms.deviceI2cAddr,
                &regAddr,
                &regValue,
                (UInt32) 1U);
        }
    }

    return (retVal);
}

static Int32 Bsp_sii9022aCalcCRC(UInt8  *regAddr,
                                 UInt8  *regValue,
                                 UInt32 *regCnt)
{
    Int32  retVal = FVID2_SOK;
    UInt32 cnt, sum = 0;

    /* Check for NULL pointers */
    GT_assert(BspDeviceTrace, (NULL != regAddr));
    GT_assert(BspDeviceTrace, (NULL != regValue));
    GT_assert(BspDeviceTrace, (NULL != regCnt));

    for(cnt = 0U; cnt < *regCnt; cnt++)
    {
        sum += regValue[cnt];
    }

    sum += (0x82U + 0x02U + 13U);
    sum &= 0xFFU;
    regValue[*regCnt] = (UInt8) (0x100U - sum);
    regAddr[*regCnt]  = 0x0CU;
    (*regCnt)++;

    return (retVal);
}

