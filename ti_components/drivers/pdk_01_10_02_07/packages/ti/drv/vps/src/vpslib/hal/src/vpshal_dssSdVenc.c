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
 *  \file vpshal_dssSdVenc.c
 *
 *  \brief HAL implementation for DSS SD VENC
 *  This file implements the HAL APIs of the SD VENC in DSS Module.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/csl/soc.h>

#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_dss.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal_dssSdVenc.h>

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_015)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-861)
 */
/**
 *  VpsHal_dssSdVencInit
 *  \brief Enable and reset the VENC .
 *  This function should be called before calling any of SD-VENC HAL API's.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */

Int32 VpsHal_dssSdVencInit(void)
{
    UInt32 temp_count = 0;
    Int32  retVal     = BSP_SOK;

    /* Enable the SDVENC */
    HW_WR_FIELD32(SOC_DSSREG_BASE + DSS_DSSREG_VENC_CTRL,
                  DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE,
                  DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE);

    /* Disabling the paralled DPI output - its only fed to SD-VENC */
    HW_WR_REG32(SOC_DSSREG_BASE + DSS_DSSREG_DPI_CTRL,
                DSS_DSSREG_DPI_CTRL_ENABLE_DISABLE);

    /* Reset the SD-VENC*/
    HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_F_CONTROL, (UInt32) 1 << 8);

    HW_WR_REG32(SOC_DSSREG_BASE + DSS_DSSREG_DPI_CTRL,
                DSS_DSSREG_DPI_CTRL_ENABLE);

    while ((temp_count < 15U))
    {
        temp_count = temp_count + 1U;
    }

    HW_WR_FIELD32(SOC_DSSREG_BASE + DSS_DSSREG_VENC_CTRL,
                  DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE,
                  DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE_DISABLE);

    return retVal;
}

/**
 *  VpsHal_dssSdVencDeInit
 *  \brief SDVENC HAL Deinit function.
 *
 *  \return                success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_dssSdVencDeInit(void)
{
    Int32 retVal = BSP_SOK;

    /* Power down the Composite Output */
    HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_OUTPUT_CONTROL, 0x0);

    return retVal;
}

/**
 * DES_ID : DOX_DES_TAG(DES_VPS_DSS_015)
 */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-862) DOX_REQ_TAG(PDK-863)
 */
/**
 *  VpsHal_dssSdVencInit
 *  \brief Configures SDVENC for a particular video mode
 *  This function will configure the SD-VENC for a particular video mode.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_dssSdVencConfigure(UInt32 videoStandard)
{
    Int32 retVal = BSP_SOK;

    Vps_DssDispcSdVencAdvConfig config;
    /* config.videoStandard should be set to get proper default values */
    config.videoStandard = videoStandard;

    retVal = VpsHal_dssGetDefAdvSdVencParams(&config);

    if (retVal == BSP_SOK)
    {
        retVal = VpsHal_dssSetAdvSdVencParams(&config);
    }

    return retVal;
}

/**
 *  VpsHal_dssGetDefAdvSdVencParams
 *  \brief Initialize the config object for the user passed settings
 *  This function will initialize the Vps_DssDispcSdVencAdvConfig object for
 *  the user passed settings. The initialized object can be passed to the
 *  VpsHal_dssSetAdvSdVencParams function.
 *
 *  \param                  pointer to Vps_DssDispcSdVencAdvConfig structure
 *  \param                  Video standard enum
 *  \return                   success    0
 *                               failure    error value
 *
 */
Int32 VpsHal_dssGetDefAdvSdVencParams(Vps_DssDispcSdVencAdvConfig *config)
{
    Int32 retVal = BSP_SOK;

    if (config != NULL)
    {
        config->vencFCtrl     = 0;
        config->vidoutCtrl    = 1;
        config->syncCtrl      = 0x8040;
        config->totalPixels   = 0x359;
        config->totalLines    = 0x36;
        config->filterCtrl    = 0;
        config->freqCodeCtrl  = 0x043F2631;
        config->cPhase        = 0;
        config->gainU         = 0x102;
        config->gainV         = 0x16C;
        config->gainY         = 0x13F;
        config->blackLevel    = 0x43;
        config->blankLevel    = 0x38;
        config->xColorCtrl    = 0x7;
        config->mControl      = 0x1;
        config->bstampWssData = 0x38;
        config->colorSubFreq  = 0x21F07C1F;
        config->line21        = 0;
        config->lineSel       = 0x01310011;
        config->wcCtrlL21     = 0x0000F003;
        config->hvTrigger     = 0;

        config->actVidSet         = 0x069300F4;
        config->fieldSet          = 0x00030036;
        config->lalPhaseReset     = 0x0002001C;
        config->hsyncIntConf      = 0x007C034E;
        config->hsyncExtConf      = 0x000F0359;
        config->vSyncIntStr       = 0x01A00000;
        config->vSyncIntStrStp    = 0x005401A0;
        config->vSyncIntStpExtStr = 0x01AC0004;
        config->vSyncExtStpExtStr = 0x003701AC;
        config->vSyncExtStpY      = 0x00000001;
        config->aVidStrStpX       = 0x03520080;
        config->aVidStrStpY       = 0x00360004;
        config->fidIntStrXStrY    = 0x0001008A;
        config->fidIntOffYExtStrX = 0x01AC0027;
        config->fidExtStrYExtOffY = 0x00270001;
        config->tvdetgpIntStrStpX = 0x00140001;
        config->tvdetgpIntStrStpY = 0x00020001;
        config->genCtrl           = 0x00F90001;
        config->outputCtrl        = 0xF;

        if (config->videoStandard == FVID2_STD_NTSC)
        {
            config->totalLines        = 0x20C;
            config->fieldSet          = 0x0016020c;
            config->lalPhaseReset     = 0x00060107;
            config->hsyncIntConf      = 0x008E035A;
            config->hsyncExtConf      = 0x000F0359;
            config->vSyncIntStr       = 0x01A00000;
            config->vSyncIntStrStp    = 0x020701A0;
            config->vSyncIntStpExtStr = 0x01AC0024;
            config->vSyncExtStpExtStr = 0x020D01AC;
            config->vSyncExtStpY      = 0x00000006;
            config->aVidStrStpX       = 0x03520080;
            config->aVidStrStpY       = 0x02000020;
            config->fidIntStrXStrY    = 0x0001008A;
            config->fidIntOffYExtStrX = 0x01AC0106;
            config->fidExtStrYExtOffY = 0x01060006;

            config->tvdetgpIntStrStpY = 0x00020001;
            config->genCtrl           = 0x00F90001;
        }

        if (config->videoStandard == FVID2_STD_PAL)
        {
            config->syncCtrl      = 0x40;
            config->totalPixels   = 0x35F;
            config->totalLines    = 0x270;
            config->freqCodeCtrl  = 0x2F7225ED;
            config->gainU         = 0x111;
            config->gainV         = 0x181;
            config->gainY         = 0x140;
            config->blackLevel    = 0x3B;
            config->mControl      = 0x2;
            config->bstampWssData = 0x3F;
            config->colorSubFreq  = 0x2A098ACB;
            config->lineSel       = 0x01290015;
            config->wcCtrlL21     = 0x0000F603;
            config->actVidSet     = 0x06A70108;
            config->fieldSet      = 0x00180270;
            config->lalPhaseReset = 0x00040135;
            config->hsyncIntConf  = 0x007F034F;

            config->hsyncExtConf      = 0x000F035F;
            config->vSyncIntStr       = 0x01A70000;
            config->vSyncIntStrStp    = 0x000001A7;
            config->vSyncIntStpExtStr = 0x01AF0000;
            config->vSyncExtStpExtStr = 0x000101AF;
            config->vSyncExtStpY      = 0x00000025;
            config->aVidStrStpX       = 0x03530081;
            config->aVidStrStpY       = 0x026E002E;
            config->fidIntStrXStrY    = 0x0001008A;
            config->fidIntOffYExtStrX = 0x002E0138;
            config->fidExtStrYExtOffY = 0x01380001;

            config->tvdetgpIntStrStpY = 0x00010001;
            config->genCtrl           = 0x00FF0000;
        }
    }
    else
    {
        retVal = BSP_EBADARGS;
    }
    return retVal;
}

/**
 *  VpsHal_dssSetAdvSdVencParams
 *  \brief Configures SDVENC with the user passed configuration
 *  This function will configure the SD-VENC for user passed settings.
 *
 *  \param                  pointer to Vps_DssDispcSdVencAdvConfig structure
 *  \return                   success    0
 *                               failure    error value
 *
 */
Int32 VpsHal_dssSetAdvSdVencParams(const Vps_DssDispcSdVencAdvConfig *config)
{
    Int32 retVal = BSP_SOK;

    if (NULL != config)
    {
        HW_WR_FIELD32(SOC_DSSREG_BASE + DSS_DSSREG_VENC_CTRL,
                      DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE,
                      DSS_DSSREG_VENC_CTRL_CLOCK_4X_ENABLE);

        HW_WR_REG32(SOC_DSSREG_BASE + DSS_DSSREG_DPI_CTRL,
                    DSS_DSSREG_DPI_CTRL_ENABLE_DISABLE);

        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_F_CONTROL, (UInt32) 1 << 8);
        HW_WR_FIELD32(SOC_DSSREG_BASE + DSS_DSSREG_VENC_CTRL,
                      DSS_DSSREG_VENC_CTRL_DAC_POWERDN_BGZ,
                      DSS_DSSREG_VENC_CTRL_DAC_POWERDN_BGZ_ENABLE);

        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_F_CONTROL, 0);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_OUTPUT_CONTROL, config->outputCtrl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_LLEN, config->totalPixels);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_FLENS, config->totalLines);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_CC_CARR_WSS, config->freqCodeCtrl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_C_PHASE, config->cPhase);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_GAIN_U, config->gainU);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_GAIN_V, config->gainV);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_GAIN_Y, config->gainY);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_BLACK_LEVEL, config->blackLevel);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_BLANK_LEVEL, config->blankLevel);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_M_CONTROL, config->mControl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_BSTAMP_WSS_DATA,
                    config->bstampWssData);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_S_CARR, config->colorSubFreq);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_L21_WC_CTL, config->wcCtrlL21);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_SAVID_EAVID, config->actVidSet);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_FLEN_FAL, config->fieldSet);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_LAL_PHASE_RESET,
                    config->lalPhaseReset);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_HS_INT_START_STOP_X,
                    config->hsyncIntConf);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_HS_EXT_START_STOP_X,
                    config->hsyncExtConf);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_VS_INT_START_X,
                    config->vSyncIntStr);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_VS_INT_STOP_X_START_Y,
                    config->vSyncIntStrStp);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_VS_INT_STOP_Y_EXT_START_X,
                    config->vSyncIntStpExtStr);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_VS_EXT_STOP_X_START_Y,
                    config->vSyncExtStpExtStr);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_VS_EXT_STOP_Y,
                    config->vSyncExtStpY);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_AVID_START_STOP_X,
                    config->aVidStrStpX);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_AVID_START_STOP_Y,
                    config->aVidStrStpY);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_FID_INT_START_X_Y,
                    config->fidIntStrXStrY);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_FID_INT_OFFSET_Y_EXT_START_X,
                    config->fidIntOffYExtStrX);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_FID_EXT_START_Y_OFFSET,
                    config->fidExtStrYExtOffY);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_VIDOUT_CTRL, config->vidoutCtrl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_HFLTR_CTRL, config->filterCtrl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_X_COLOR, config->xColorCtrl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_LINE21, config->line21);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_LN_SEL, config->lineSel);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_HTRIGGER_VTRIGGER,
                    config->hvTrigger);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_TVDETGP_INT_START_STOP_X,
                    config->tvdetgpIntStrStpX);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_TVDETGP_INT_START_STOP_Y,
                    config->tvdetgpIntStrStpY);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_GEN_CTRL, config->genCtrl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_F_CONTROL, config->vencFCtrl);
        HW_WR_REG32(SOC_VENC_BASE + DSS_VENC_SYNC_CTRL, config->syncCtrl);
    }
    else
    {
        retVal = BSP_EBADARGS;
    }
    return retVal;
}

