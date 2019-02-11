/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
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
 *  \file vps_dctrlDrv.c
 *
 *  \brief File containing the DCTRL driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/src/vpslib/common/vps_common.h>

#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/dss/vps_dctrlDrv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsDrv_DctrlInstObj gDctrlDrvObj;
static UInt32 gDrvInit = 0;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static VpsDrv_DctrlInstObj *VpsDrv_DctrlGetInst(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsDrv_dctrlInit
 *  \brief VPS DSS capture driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_DispInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dctrlInit(const VpsDrv_DctrlInitParams *initPrms)
{
    gDctrlDrvObj.drvInstId   = 0;
    gDctrlDrvObj.coreInstObj = initPrms->coreInstObj;
    gDctrlDrvObj.coreOps     = initPrms->coreOps;

    gDrvInit = 1U;
    return BSP_SOK;
}

/**
 *  VpsDrv_dispDeInit
 *  \brief VPS DSS capture driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dctrlDeInit(void)
{
    gDctrlDrvObj.drvInstId   = 0U;
    gDctrlDrvObj.coreInstObj = NULL;
    gDctrlDrvObj.coreOps     = NULL;
    gDrvInit = 0;

    return BSP_SOK;
}

/**
 *  VpsDrv_DctrlGetInst
 *  \brief Get Handle to the Driver control instance as per specified ID
 *
 *  \param instId             Driver control Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */

static VpsDrv_DctrlInstObj *VpsDrv_DctrlGetInst(void)
{
    VpsDrv_DctrlInstObj *pObj = NULL;
    if (gDrvInit)
    {
        if (NULL != gDctrlDrvObj.coreInstObj)
        {
            pObj = &gDctrlDrvObj;
        }
    }
    return pObj;
}

/**
 *  VpsDrv_DctrlOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param captureOpenParams Capture Driver parameters #VpsCore_OpenPrms
 *  \param vipOpenParams     VIP specific parameters #VpsCore_VipOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_DctrlInstObj *VpsDrv_dctrlOpen(void)
{
    VpsDrv_DctrlInstObj *pObj;

    pObj = (VpsDrv_DctrlInstObj *) VpsDrv_DctrlGetInst();
    return pObj;
}

/**
 *  VpsDrv_DctrlClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Capture Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dctrlClose(VpsDrv_DctrlInstObj *pObj)
{
    Int32 retVal = BSP_SOK;

    return retVal;
}

/**
 *  vpsDrv_DctrlSetConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetConfig(VpsDrv_DctrlInstObj *pObj,
                            Vps_DctrlConfig     *dctrlCfg)

{
    Int32 retVal = BSP_SOK;

    if (NULL == pObj)
    {
        Bsp_printf("Invalid argument!!\r\n");
        retVal = BSP_EBADARGS;
    }
    else
    {
        retVal = pObj->coreOps->control(
            pObj,
            IOCTL_VPSCORE_DCTRL_SET_CONFIG,
            dctrlCfg,
            (Ptr) pObj->coreInstObj);

        if (BSP_SOK != retVal)
        {
            Bsp_printf("Core control: Set Config failed!!\r\n");
        }
    }
    return (retVal);
}

/**
 *  vpsDrv_DctrlCleatConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlClearConfig(VpsDrv_DctrlInstObj *pObj,
                              Vps_DctrlConfig     *dctrlCfg)

{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointers */
    /* GT_assert(VpsDrvDctrlTrace, (NULL != dctrlCfg)); */

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_CLEAR_CONFIG,
        dctrlCfg,
        (Ptr) pObj->coreInstObj);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: clear config failed!!\r\n");
    }

    return (retVal);
}

/**
 *  vpsDrv_DctrlSetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info)

{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_VENC_OUTPUT,
        dctrl_info,
        (Ptr) pObj->coreInstObj);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: Set venc output failed!!\r\n");
    }

    return (retVal);
}

/**
 *  vpsDrv_DctrlGetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlGetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info)

{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_GET_VENC_OUTPUT,
        dctrl_info,
        (Ptr) pObj->coreInstObj);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("Core control: Get venc output failed!!\r\n");
    }

    return (retVal);
}

/**
 *  vpsDrvDctrlSetVencDivisorIoctl
 *  \brief Sets the Venc divisor values to get desired pixel clock.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencDivisor(
    VpsDrv_DctrlInstObj *pObj,
    Vps_DctrlVencDivisorInfo *
    vencDivisor)

{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointers */
    /* GT_assert(VpsDrvDctrlTrace, (NULL != vencDivisor)); */

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_VENC_PCLK_DIVISORS,
        vencDivisor,
        (Ptr) pObj->coreInstObj);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("Core control: Set panelconfig failed!!\r\n");
    }

    return (retVal);
}

/**
 *  vpsDrv_DctrlSetOvlyParms
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetOvlyParams(
    VpsDrv_DctrlInstObj *pObj,
    Vps_DssDispcOvlyPanelConfig *
    panelconfig)

{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_OVLY_PARAMS,
        panelconfig,
        (Ptr) pObj->coreInstObj);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: Set panelconfig failed!!\r\n");
    }

    return (retVal);
}

/**
 *  vpsDrvDctrlSetPipelineParmsIoctl
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetPipelineParams(
    VpsDrv_DctrlInstObj        *pObj,
    Vps_DssDispcOvlyPipeConfig *ovlpipeconfig)

{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointers */
    /* GT_assert(VpsDrvDctrlTrace, (NULL != ovlpipeconfig)); */

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_PIPELINE_PARAMS,
        ovlpipeconfig,
        (Ptr) pObj->coreInstObj);

    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: Set pipelineconfig failed!!\r\n");
    }

    return (retVal);
}

