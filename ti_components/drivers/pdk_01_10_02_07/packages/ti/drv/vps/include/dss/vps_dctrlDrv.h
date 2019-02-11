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
 *  \file vps_dctrlDrv.h
 *
 *  \brief Baremetal interface file for DSS Display controller driver.
 *  Caution: This library cannot co-exist with VPS RTOS driver.
 *
 */

#ifndef VPS_DCTRLDRV_H_
#define VPS_DCTRLDRV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dctrl.h>
#include <ti/drv/vps/include/vps_displayCtrlDataTypes.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_DctrlInstObj_t VpsDrv_DctrlInstObj;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsDrv_DctrlInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
} VpsDrv_DctrlInitParams;

/**
 *  struct VpsDrv_CaptInstObj
 *  \brief Instance specific parameters used at init call.
 */
struct VpsDrv_DctrlInstObj_t
{
    UInt32             drvInstId;
    /**< Instance ID. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
};

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsDrv_dctrlInit
 *  \brief VPS DSS capture driver init function.
 *
 *  \param initPrms           Pointer to #VpsDrv_DispInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */

Int32 VpsDrv_dctrlInit(const VpsDrv_DctrlInitParams *initPrms);

/**
 *  VpsDrv_dctrlDeInit
 *  \brief VPS DSS capture driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dctrlDeInit(void);

/**
 *  VpsDrv_captOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_DctrlInstObj *VpsDrv_dctrlOpen(void);

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
Int32 VpsDrv_dctrlClose(VpsDrv_DctrlInstObj *pObj);

/**
 *  vpsDrv_DctrlSetConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetConfig(VpsDrv_DctrlInstObj *pObj,
                            Vps_DctrlConfig     *dctrlCfg);

/**
 *  vpsDrv_DctrlCleatConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlClearConfig(VpsDrv_DctrlInstObj *pObj,
                              Vps_DctrlConfig     *dctrlCfg);

/**
 *  vpsDrv_DctrlSetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info);

/**
 *  vpsDrv_DctrlGetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlGetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info);

/**
 *  vpsDrv_DctrlSetVencDivisor
 *  \brief Sets the Venc divisor values to get desired pixel clock.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencDivisor(VpsDrv_DctrlInstObj      *pObj,
                                 Vps_DctrlVencDivisorInfo *vencDivisor);

/**
 *  vpsDrv_DctrlSetOvlyParms
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetOvlyParams(VpsDrv_DctrlInstObj         *pObj,
                                Vps_DssDispcOvlyPanelConfig *panelconfig);

/**
 *  vpsDrv_DctrlSetPipelineParms
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetPipelineParams(VpsDrv_DctrlInstObj        *pObj,
                                    Vps_DssDispcOvlyPipeConfig *ovlpipeconfig);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_DCTRLDRV_H_ */
