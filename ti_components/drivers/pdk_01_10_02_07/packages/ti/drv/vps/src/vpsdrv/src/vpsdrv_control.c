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
 *  \file vpsdrv_control.c
 *
 *  \brief File containing the VPS control driver APIs commmon to all drivers.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_control.h>
#include <vpsdrv_control.h>
#ifdef VPS_VPE_BUILD
#include <ti/drv/vps/src/vpslib/vpecore/vpscore_m2m.h>
#include <vpedrv/vpsdrv_m2mVpe.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/*
 * struct VpsDrv_CtrlCommonObj
 * \brief Capture driver global/common driver object.
 */
typedef struct
{
    BspOsal_SemHandle lockSem;
    /**< Lock semaphore. */
    Fvid2_DrvOps      fvidDrvOps;
    /**< FVID2 driver ops. */
    Bool              isRegistered;
    /**< FVID2 registeration complete flag. */
} VpsDrv_CtrlCommonObj;

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

/*
 * VPS control API's
 */
static Fdrv_Handle VpsDrv_ctrlCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 VpsDrv_ctrlDelete(Fdrv_Handle handle, Ptr reserved);
static Int32 VpsDrv_ctrlControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif
/*
 * IOCTLs
 */
#ifdef VPS_VPE_BUILD
static Int32 vpsDrvCtrlSetVpeLazyLoadIoctl(
    VpsDrv_CtrlCommonObj          *pObj,
    const Vps_ScLazyLoadingParams *lazyPrms);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsDrv_CtrlCommonObj gVpsCtrlCommonObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS control driver init function.
 */
Int32 VpsDrv_ctrlInit(void)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CtrlCommonObj *pObj;
    Int32 initValue;

    pObj = &gVpsCtrlCommonObj;
    BspUtils_memset(pObj, 0, sizeof (gVpsCtrlCommonObj));

    /* Initialize Driver operations */
    Fvid2DrvOps_init(&pObj->fvidDrvOps);

    pObj->fvidDrvOps.drvId                 = FVID2_VPS_CTRL_DRV;
    pObj->fvidDrvOps.createFxn             = &VpsDrv_ctrlCreate;
    pObj->fvidDrvOps.deleteFxn             = &VpsDrv_ctrlDelete;
    pObj->fvidDrvOps.controlFxn            = &VpsDrv_ctrlControl;

    retVal = Fvid2_registerDriver(&pObj->fvidDrvOps);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvCtrlTrace, GT_ERR,
                  "Registering to FVID2 driver manager failed\r\n");
    }

    if (FVID2_SOK == retVal)
    {
        pObj->isRegistered = (Bool)TRUE;

        /* Allocate lock semaphore */
        initValue = 1;
        pObj->lockSem = BspOsal_semCreate(initValue, FALSE);
        if (NULL == pObj->lockSem)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR,
                      "Instance semaphore create failed!!\r\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK != retVal)
    {
        VpsDrv_ctrlDeInit();
    }

    return (retVal);
}

/**
 *  \brief VPS control driver deinit function.
 */
Int32 VpsDrv_ctrlDeInit(void)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CtrlCommonObj *pObj;

    pObj = &gVpsCtrlCommonObj;
    if (TRUE == pObj->isRegistered)
    {
        /* Unregister from driver manager */
        retVal = Fvid2_unRegisterDriver(&pObj->fvidDrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCtrlTrace, GT_ERR,
                      "Unregistering from FVID2 driver manager failed\r\n");
        }
        pObj->isRegistered = (Bool)FALSE;
    }

    if (NULL != pObj->lockSem)
    {
        BspOsal_semDelete(&pObj->lockSem);
        pObj->lockSem = NULL;
    }

    return (retVal);
}

/**
 *  \brief VPS control driver create function.
 */
static Fdrv_Handle VpsDrv_ctrlCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Fdrv_Handle drvHandle = NULL;

    /* Check for NULL pointers and invalid arguments */
    if ((FVID2_VPS_CTRL_DRV != drvId) || (VPS_CTRL_INST_0 != instId))
    {
        GT_0trace(VpsDrvCtrlTrace, GT_ERR, "Invalid arguments\r\n");
    }
    else
    {
        drvHandle = (Fdrv_Handle) & gVpsCtrlCommonObj;
    }

    return (drvHandle);
}

/**
 *  \brief VPS control driver delete function.
 */
static Int32 VpsDrv_ctrlDelete(Fdrv_Handle handle, Ptr reserved)
{
    Int32 retVal = FVID2_EBADARGS;

    /* Global handle - do nothing */
    if (((Fdrv_Handle) & gVpsCtrlCommonObj) == handle)
    {
        retVal = FVID2_SOK;
    }

    return (retVal);
}

/**
 *  \brief VPS control driver control function.
 */
static Int32 VpsDrv_ctrlControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_EBADARGS;

    if (handle == (Fdrv_Handle) & gVpsCtrlCommonObj)
    {
        retVal = FVID2_SOK;
        switch (cmd)
        {
#ifdef VPS_VPE_BUILD
            case IOCTL_VPS_CTRL_SET_VPE_LAZY_LOADING:
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvCtrlSetVpeLazyLoadIoctl(
                        (VpsDrv_CtrlCommonObj *) handle,
                        (Vps_ScLazyLoadingParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvCtrlTrace, GT_ERR, "NULL argument\r\n");
                    retVal = FVID2_EBADARGS;
                }
                break;
#endif

            default:
                GT_0trace(
                    VpsDrvCtrlTrace, GT_ERR,
                    "UNSUPPORTED_CMD: IOCTL not supported!!\r\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (retVal);
}

#ifdef VPS_VPE_BUILD
static Int32 vpsDrvCtrlSetVpeLazyLoadIoctl(
    VpsDrv_CtrlCommonObj          *pObj,
    const Vps_ScLazyLoadingParams *lazyPrms)
{
    Int32 retVal = FVID2_SOK;

    retVal = VpsMdrv_vpeSetLazyLoadParams(lazyPrms);

    return (retVal);
}

#endif
