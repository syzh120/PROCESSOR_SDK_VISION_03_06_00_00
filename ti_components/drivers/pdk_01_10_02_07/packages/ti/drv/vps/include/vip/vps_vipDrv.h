/*
 *  Copyright (c) Texas Instruments Incorporated 2013
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
 *  \file vps_vipDrv.h
 *
 *  \brief Baremetal interface file for VIP capture driver.
 *  Caution: This library cannot co-exist with VPS RTOS driver.
 *
 */

#ifndef VPS_VIP_DRV_H_
#define VPS_VIP_DRV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Capture instance - MAX instances. */
#define VPS_CAPT_VIP_INST_MAX (VPS_VIP_MAX * VPS_VIP_SLICE_MAX * \
                               VPS_VIP_PORT_MAX)

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_CaptInstObj_t VpsDrv_CaptInstObj;

/** \brief SubFrame CallBack, only addr field of subFrame is valid and subFrame
 *  pointer is not active after the call is returned. */
typedef Int32 (*VpsDrv_SubFrameCb)(VpsDrv_CaptInstObj  *pObj,
                                   const VpsCore_Frame *subFrame);

/** \brief Overflow callback. */
typedef void (*VpsDrv_VipOverflowFxn)(Ptr pObj);

/** \brief User command base address. */
#define VPS_USER_BASE                 (0x10000000U)

/** \brief IOCTL base address for the capture driver IOCTLs. */
#define VPS_CAPT_IOCTL_BASE             (VPS_USER_BASE + 0x00030000U)

/** \brief VIP capture driver IOCTL base. */
#define VPS_CAPT_VIP_IOCTL_BASE         (VPS_CAPT_IOCTL_BASE + 0x0100U)

/**
 *  \brief Set VIP parameters.
 *
 *  This IOCTL can be used to set the VIP hardware specific parameters.
 *  This IOCTL should be called after creating any VIP capture driver instance
 *  and before queueing or starting the capture driver. Starting the capture
 *  driver without calling this IOCTL will result in error.
 *
 *  Once the capture is started this IOCTL can't be invoked and will result in
 *  error.
 *
 *  Once the capture is stopped, application could call this IOCTL to
 *  reconfigure the VIP block with a different set of parameters.
 *
 *  \param cmdArgs       [IN]  const Vps_CaptVipParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_SET_VIP_PARAMS   (VPS_CAPT_VIP_IOCTL_BASE + 0x0000U)

/**
 *  \brief Get VIP parameters.
 *
 *  This IOCTL can be used to get the VIP hardware parameters.
 *  This IOCTL could be called at anytime after creating VIP capture
 *  driver instance.
 *
 *  \param cmdArgs       [IN]  Vps_CaptVipParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_GET_VIP_PARAMS   (VPS_CAPT_VIP_IOCTL_BASE + 0x0001U)

/**
 *  \brief Enable overflow interrupt.
 *
 *  This IOCTL can be used to enable the overflow interrupt. User needs to pass
 *  overflow ISR which will be called when overflow occurs on VIP and the
 *  application handle corrosponding to that VIP instance.
 *
 *  \param cmdArgs       [IN]  Vps_OverflowParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */

#define IOCTL_VPS_CAPT_REGISTER_OVF_INTR (VPS_CAPT_VIP_IOCTL_BASE + 0x0002U)

/**
 *  \brief Disable overflow interrupt.
 *
 *  This IOCTL can be used to unregister from the overflow
 *  interrupt. This will unregister on the VIP instance of the handle passed.
 *
 *  \param cmdArgs       [IN]  NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */

#define IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR (VPS_CAPT_VIP_IOCTL_BASE + 0x0003U)

/**
 *  \brief Get VIP parameters.
 *
 *  This IOCTL can be used to get the status of overflow registers. This can be
 *  used with intrrupt  mode as well as polling mode. It will check
 *  overflow status on the handle passed and return the value
 *  in the parameter passed.
 *
 *  \param cmdArgs       [IN]  NULL
 *  \param cmdArgsStatus [OUT] vps_overflowCheckParams *
 *
 *  \return FVID2_SOK on success, else failure.
 */

#define IOCTL_VPS_CAPT_CHECK_OVERFLOW (VPS_CAPT_VIP_IOCTL_BASE + 0x0004U)

/**
 *  \brief Stop VIP port.
 *
 *  This IOCTL can be used to stop the vip port corrosponding to the handle
 *  passed. It sets the s/w reset bit of
 *  the VIP. This can be called in ISR context. It is used to stop the
 *  continuous
 *  overflow and come out of ISR
 *
 *  \param cmdArgs       [IN]  NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */

#define IOCTL_VPS_CAPT_RESET_VIP_PORT (VPS_CAPT_VIP_IOCTL_BASE + 0x0005U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsDrv_CaptInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32             drvInstId;
    /**< Instance ID. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
} VpsDrv_CaptInitParams;

/**
 *  \brief Platform specific data containing base address information of
 *  VIP module.
 */
typedef struct
{
    VpsDrv_CaptInitParams captDrvInitPrms[VPS_CAPT_VIP_INST_MAX];
    /**< Capture driver init parameters. */
} VpsDrv_VipPlatformData;

/**
 *  struct VpsDrv_CaptStrmObj
 *  \brief Used for sub-frame callback
 *  WARNING!!!: This structure may change
 */
typedef struct
{
    VpsDrv_CaptInstObj *pObj;
    /**< Parent */
    UInt32              strmId;
    /**< Stream ID in Parent */
} VpsDrv_CaptStrmObj;

/**
 *  struct VpsDrv_CaptInstObj
 *  \brief Instance specific parameters used at init call.
 */
struct VpsDrv_CaptInstObj_t
{
    UInt32                drvInstId;
    /**< Instance ID. */
    VpsCore_Inst          coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops    *coreOps;
    /**< Core function pointers. */
    VpsCore_Handle       *coreHandle;
    /**< Core Handle opened using VpsDrv_captCreate pointers TODO. */
    void                 *vemHandle;
    /**< Event Manager Handle for handling ISRs */
    void                 *overflowVemHandle;
    /**< Event Manager Handle for handling overflow ISRs */
    VpsDrv_SubFrameCb     subFrameCb[VPSCORE_VIP_STREAM_ID_MAX];
    /**< Variable to save subframeCb Info in CaptInst object */
    void                 *vemSubFrmHandle[VPSCORE_VIP_STREAM_ID_MAX];
    /**< Event Manager Handle for handling sub frame ISRs */
    VpsDrv_CaptStrmObj    strmObj[VPSCORE_VIP_STREAM_ID_MAX];
    /**< Stream Object */
    VpsDrv_VipOverflowFxn overflowCbFxn;
    /**<Application callback function, to be called by the overflow ISR */
    void                 *appOverFlowCbPrms;
    /**<Parameters to be passed to the overflowCbFxn */
    UInt32                overflowCount;
    /**<Variable to keep record, if the overflow on a VIP has occured or not. */
};

/**
 *  struct VpsDrv_VipParams
 *  \brief VIP configuration and supporting sub-frame callbacks.
 */
typedef struct
{
    const VpsCore_VipParams *pathCfg;
    /**< Core function pointers. */
    VpsDrv_SubFrameCb        subFrameCb[VPSCORE_VIP_STREAM_ID_MAX];
    /**< Sub-frame callback pointers for each stream TODO. */
} VpsDrv_VipParams;

/**
 *  struct Vps_OverflowParams
 *  \brief Capture overflow parameters, to sent while enabling the
 * overflow interrupt..
 */

typedef struct
{
    VpsDrv_VipOverflowFxn overflowCbFxn;
    /**< Application callback function to be called when overflow occurs */
    void                 *retParams;
    /**< Application handle returned to the callback function as return
     *      parameter */
}Vps_OverflowParams;

/**
 *  struct Vps_OverflowCheckParams
 *  \brief Capture overflow parameters, will be filled by the driver during
 *   check for overflow.
 */
typedef struct
{
    UInt32 isOverflowOccured;
    /**< Parameter to store if overflow occured. */
}Vps_OverflowCheckParams;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Vps_init
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param args               Pointer to arguments.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_init(Ptr args);

/**
 *  Vps_deInit
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param args               Pointer to arguments.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_deInit(Ptr args);

/**
 *  VpsDrv_captOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param vipInstId         VIP Instance ID Vps_VipInst
 *  \param captureOpenParams Capture Driver parameters VpsCore_OpenPrms
 *  \param vipOpenParams     VIP specific parameters VpsCore_VipOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_CaptInstObj *VpsDrv_captOpen(
    UInt32                       vipInstId,
    const VpsCore_OpenPrms      *captureOpenParams,
    const VpsCore_VipOpenParams *vipOpenParams);

/**
 *  VpsDrv_captClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Capture Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captClose(VpsDrv_CaptInstObj *pObj);

/**
 *  VpsDrv_captStart
 *  \brief Start capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captStart(VpsDrv_CaptInstObj *pObj);

/**
 *  VpsDrv_captStop
 *  \brief Stop capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captStop(VpsDrv_CaptInstObj *pObj);

/**
 *  VpsDrv_captSetParams
 *  \brief Set capture params for specified handle
 *
 *  \param pObj           Capture Handle #VpsDrv_CaptInstObj
 *  \param captVipParams  Path configuration VpsCore_VipParams
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captSetParams(VpsDrv_CaptInstObj     *pObj,
                           const VpsDrv_VipParams *captVipParams);

/**
 *  VpsDrv_captGetParams
 *  \brief Get capture params for specified handle. If not configured, this will
 *  return a default configuration
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *  \param vipParams    Pointer to VpsCore_VipParams where configuration will
 *                      be copied
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captGetParams(VpsDrv_CaptInstObj *pObj,
                           VpsCore_VipParams  *vipParams);

/**
 *  VpsDrv_resetPort
 *  \brief Reset specified PORT. For TI814X_BUILD, you MUST call this
 *  function for all active PORTs. This is not required for TDA2x/3x.
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_resetPort(VpsDrv_CaptInstObj *pObj);
/**
 *  VpsDrv_captControl
 *  \brief capture driver control function. This function implements various
 *  IOCTLS.
 *
 *  All IOCTLS are blocking and could not be called from ISR context unless
 *  otherwise specified for a particular IOCTL.
 *
 *  \param pObj             [IN] Display driver instance handle returned by
 *                          create function.
 *  \param cmd              [IN] Supports the above mentioned commands.
 *  \param cmdArgs          [IN] Depending on the command this will vary.
 *  \param cmdStatusArgs    [OUT] Depending on the command this will vary.
 *
 *  \return                 Returns BSP_SOK on success else returns
 *                          appropriate error code.
 */

Int32 VpsDrv_captControl(VpsDrv_CaptInstObj *pObj,
                         UInt32              cmd,
                         Ptr                 cmdArgs,
                         Ptr                 cmdStatusArgs);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_VIP_DRV_H_ */
