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
 *  \file dspdrv_tc358778Ctrl.c
 *
 *  \brief driver file for TC358778 Parallel port to MIPI DSI Controller.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <lcdCtrl/src/bspdrv_lcdCtrlPriv.h>
#include <ti/drv/vps/include/fvid2/fvid2_drvMgr.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* Register offsets */
/* Global(16-bit addressable) */
#define CHIPID          ((UInt16)0x0000U)
#define SYSCTL          ((UInt16)0x0002U)
#define CONFCTL         ((UInt16)0x0004U)
#define VSDLY           ((UInt16)0x0006U)
#define DATAFMT         ((UInt16)0x0008U)
#define GPIOEN          ((UInt16)0x000EU)
#define GPIODIR         ((UInt16)0x0010U)
#define GPIOIN          ((UInt16)0x0012U)
#define GPIOOUT         ((UInt16)0x0014U)
#define PLLCTL0         ((UInt16)0x0016U)
#define PLLCTL1         ((UInt16)0x0018U)
#define CMDBYTE         ((UInt16)0x0022U)
#define PP_MISC         ((UInt16)0x0032U)
#define DSITX_DT        ((UInt16)0x0050U)
#define FIFOSTATUS      ((UInt16)0x00F8U)

/* TX PHY(32-bit addressable) */
#define CLW_DPHYCONTTX      ((UInt16)0x0100U)
#define D0W_DPHYCONTTX      ((UInt16)0x0104U)
#define D1W_DPHYCONTTX      ((UInt16)0x0108U)
#define D2W_DPHYCONTTX      ((UInt16)0x010CU)
#define D3W_DPHYCONTTX      ((UInt16)0x0110U)
#define CLW_CNTRL           ((UInt16)0x0140U)
#define D0W_CNTRL           ((UInt16)0x0144U)
#define D1W_CNTRL           ((UInt16)0x0148U)
#define D2W_CNTRL           ((UInt16)0x014CU)
#define D3W_CNTRL           ((UInt16)0x0150U)

/* TX PPI(32-bit addressable) */
#define STARTCNTRL     ((UInt16)0x0204U)  /* DSITX Start Control Register */
#define DSITXSTATUS    ((UInt16)0x0208U)  /* DSITX Status Register */
#define LINEINITCNT    ((UInt16)0x0210U)  /* DSITX Line Init Control Register */
#define LPTXTIMECNT    ((UInt16)0x0214U)  /* SYSLPTX Timing Generation Counter */
#define TCLK_HEADERCNT ((UInt16)0x0218U)  /* TCLK_ZERO and TCLK_PREPARE Counter */
#define TCLK_TRAILCNT  ((UInt16)0x021CU)  /* TCLK_TRAIL Counter */
#define THS_HEADERCNT  ((UInt16)0x0220U)  /* THS_ZERO and THS_PREPARE Counter */
#define TWAKEUP        ((UInt16)0x0224U)  /* TWAKEUP Counter */
#define TCLK_POSTCNT   ((UInt16)0x0228U)  /* TCLK_POST Counter */
#define THS_TRAILCNT   ((UInt16)0x022CU)  /* THS_TRAIL Counter */
#define HSTXVREGCNT    ((UInt16)0x0230U)  /* TX Voltage Regulator setup Wait Counter */
#define HSTXVREGEN     ((UInt16)0x0234U)  /* Voltage regulator enable for
                                    HSTX Data Lanes */
#define TXOPTIONCNTRL  ((UInt16)0x0238U)  /* TX Option Control */
#define BTACNTRL1      ((UInt16)0x023CU)  /* BTA Control */

/* TX CTRL(32-bit addressable) */
#define DSI_CONTROL         ((UInt16)0x040CU)
#define DSI_STATUS          ((UInt16)0x0410U)
#define DSI_INT             ((UInt16)0x0414U)
#define DSI_INT_ENA         ((UInt16)0x0418U)
#define DSICMD_RXFIFO       ((UInt16)0x0430U)
#define DSI_ACKERR          ((UInt16)0x0434U)
#define DSI_ACKERR_INTENA   ((UInt16)0x0438U)
#define DSI_ACKERR_HALT     ((UInt16)0x043CU)
#define DSI_RXERR           ((UInt16)0x0440U)
#define DSI_RXERR_INTENA    ((UInt16)0x0444U)
#define DSI_RXERR_HALT      ((UInt16)0x0448U)
#define DSI_ERR             ((UInt16)0x044CU)
#define DSI_ERR_INTENA      ((UInt16)0x0450U)
#define DSI_ERR_HALT        ((UInt16)0x0454U)
#define DSI_CONFW           ((UInt16)0x0500U)
#define DSI_RESET           ((UInt16)0x0504U)
#define DSI_INT_CLR         ((UInt16)0x050CU)
#define DSI_START           ((UInt16)0x0518U)

/* DSITX CTRL(16-bit addressable) */
#define DSICMD_TX       ((UInt16)0x0600U)
#define DSICMD_TYPE     ((UInt16)0x0602U)
#define DSICMD_WC       ((UInt16)0x0604U)
#define DSICMD_WD0      ((UInt16)0x0610U)
#define DSICMD_WD1      ((UInt16)0x0612U)
#define DSICMD_WD2      ((UInt16)0x0614U)
#define DSICMD_WD3      ((UInt16)0x0616U)
#define DSI_EVENT       ((UInt16)0x0620U)
#define DSI_VSW         ((UInt16)0x0622U)
#define DSI_VBPR        ((UInt16)0x0624U)
#define DSI_VACT        ((UInt16)0x0626U)
#define DSI_HSW         ((UInt16)0x0628U)
#define DSI_HBPR        ((UInt16)0x062AU)
#define DSI_HACT        ((UInt16)0x062CU)

/* Debug(16-bit addressable) */
#define VBUFCTL         ((UInt16)0x00E0U)
#define DBG_WIDTH       ((UInt16)0x00E2U)
#define DBG_VBLANK      ((UInt16)0x00E4U)
#define DBG_DATA        ((UInt16)0x00E8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    UInt32 fbd;
    UInt32 prd;
    UInt32 frs;
    UInt32 bitclk;
} BspDrv_lcdBridgeParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static Int32 LcdBridge_16bWrite(UInt32 deviceI2cInstId,
                                UInt32 slaveAddr,
                                UInt16 reg,
                                UInt16 data);
static Int32 LcdBridge_32bWrite(UInt32 deviceI2cInstId,
                                UInt32 slaveAddr,
                                UInt16 reg,
                                UInt32 data);
static Int32 Tc358778_setupPll(UInt32                   deviceI2cInstId,
                               UInt32                   slaveAddr,
                               BspDrv_lcdBridgeParams  *bridgeParams,
                               const Fvid2_ModeInfo    *mInfo);
static void Tc358778_getLcdTiming (Fvid2_ModeInfo *mInfo);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static Int32 LcdBridge_16bWrite(UInt32 deviceI2cInstId,
                                UInt32 slaveAddr,
                                UInt16 reg,
                                UInt16 data)
{
    UInt8 i2cdata[4];
    Int32 retVal = FVID2_SOK;

    i2cdata[0] = (UInt8)((reg & (UInt16)0xFF00U) >> 8);  /*Register[15:8] */
    i2cdata[1] = (UInt8)(reg & (UInt16)0x00FFU);       /*Register[7:0]*/
    i2cdata[2] = (UInt8)((data & (UInt16)0xFF00U) >> 8); /*data[15:8]*/
    i2cdata[3] = (UInt8)(data & (UInt16)0x00FFU);      /*data[7:0]*/
    retVal     = Bsp_deviceRawWrite8(deviceI2cInstId,
                                     slaveAddr,
                                     i2cdata,
                                     (UInt32)4U);
    BspOsal_sleep(2U);
    return retVal;
}

static Int32 LcdBridge_32bWrite(UInt32 deviceI2cInstId,
                                UInt32 slaveAddr,
                                UInt16 reg,
                                UInt32 data)
{
    UInt8 i2cdata[6];
    Int32 retVal = FVID2_SOK;

    i2cdata[0] = (UInt8)((reg & (UInt16)0xFF00U) >> 8);       /*Register[15:8] */
    i2cdata[1] = (UInt8)(reg & (UInt16)0x00FFU);            /*Register[7:0]*/
    i2cdata[2] = (UInt8)((data & (UInt32)0xFF00U) >> 8);      /*data[15:8]*/
    i2cdata[3] = (UInt8)(data & (UInt32)0x00FFU);           /*data[7:0]*/
    i2cdata[4] = (UInt8)((data & (UInt32)0xFF000000U) >> 24); /*data[31:24]*/
    i2cdata[5] = (UInt8)((data & (UInt32)0x00FF0000U) >> 16); /*data[23:16]*/
    retVal     = Bsp_deviceRawWrite8(deviceI2cInstId,
                                     slaveAddr,
                                     i2cdata,
                                     (UInt32)6U);
    BspOsal_sleep(2U);
    return retVal;
}

static void Tc358778_getLcdTiming (Fvid2_ModeInfo *mInfo)
{
    GT_assert(BspAppTrace, (NULL != mInfo));
#if defined (BSP_LCDCTRL_IDK_LCD_32FPS)
    mInfo->width       = 1920;
    mInfo->height      = 1200;
    mInfo->pixelClock  = 78000;
    mInfo->hFrontPorch = 112;
    mInfo->hBackPorch  = 32;
    mInfo->hSyncLen    = 16;
    mInfo->vFrontPorch = 17;
    mInfo->vBackPorch  = 16;
    mInfo->vSyncLen    = 2;
#else
    mInfo->width       = 1920;
    mInfo->height      = 1200;
    mInfo->pixelClock  = 147000;
    mInfo->hFrontPorch = 32;
    mInfo->hBackPorch  = 32;
    mInfo->hSyncLen    = 16;
    mInfo->vFrontPorch = 7;
    mInfo->vBackPorch  = 16;
    mInfo->vSyncLen    = 2;
#endif
}
static Int32 Tc358778_setupPll(UInt32                   deviceI2cInstId,
                               UInt32                   slaveAddr,
                               BspDrv_lcdBridgeParams  *bridgeParams,
                               const Fvid2_ModeInfo    *mInfo)
{
    Int32           retVal = BSP_SOK;
    UInt32          fbd, prd, frs;
    UInt32          pll;
    UInt32          target;
    UInt64          refclk;
    Bool            found = FALSE;

    /* target byteclk */
    /* (pclk * dpi num data lines / 8 / dsi num data lanes) */
    target = ((mInfo->pixelClock) * (24U / 8U)) / 4U;

    /* target pll clk */
    target = target * (4U * 2U);

    if (target >= 500000U)
    {
        frs = 0;
    }
    else if (target >= 250000U)
    {
        frs = 1U;
    }
    else if (target >= 125000U)
    {
        frs = 2U;
    }
    else if (target >= 62500U)
    {
        frs = 3U;
    }
    else
    {
        GT_0trace(BspDeviceTrace, GT_ERR, "target pll clk out of range!!\r\n");
        retVal = BSP_EFAIL;
    }

    if (retVal == BSP_SOK)
    {
        /* Calculate fbd and prd values to pregram using below formula */
        /* pll_clk = RefClk * [(FBD + 1)/ (PRD + 1)] * [1 / (2^FRS)] */
        refclk = 20000U;

        for (prd = 0; prd < 16U; ++prd)
        {
            for (fbd = 0; fbd < 512U; ++fbd)
            {
                UInt64 tempNum;
                UInt32 tempDen;
                tempNum = (UInt64) refclk * ((UInt64) fbd + (UInt64) 1U);
                tempDen = (prd + 1U) * ((UInt32) 1 << frs);
                pll = (UInt32)(tempNum / tempDen);

                if (pll == target)
                {
                    bridgeParams->fbd = fbd;
                    bridgeParams->prd = prd;
                    bridgeParams->frs = frs;
                    bridgeParams->bitclk = pll / 2U;
                    found = TRUE;
                    break;
                }
            }
            if (found == TRUE)
            {
                break;
            }
        }
        if (found == FALSE)
        {
            retVal = BSP_EFAIL;
            GT_0trace(BspDeviceTrace, GT_ERR, "set pll clk failed!!\r\n");
        }
    }
    if (retVal == BSP_SOK)
    {
        UInt32 tempVal;
        /* Program DSI Tx PLL */
#if defined (BSP_LCDCTRL_IDK_LCD_32FPS)
        tempVal = (prd << 12) | fbd;
        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, PLLCTL0,
            (UInt16) tempVal);
#else
        /* For 60 FPS configuration calculated value doesnot work.
         * Hardcoded as of now. */
        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, PLLCTL0,
            (UInt16) 0x5127U);
#endif
        tempVal = (frs << 10) | ((UInt32) 0x2 << 8) | ((UInt32) 0 << 4) |
            ((UInt32) 1 << 1) | ((UInt32) 1 << 0);
        /* PRD[15:12], FBD[8:0] */
        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, PLLCTL1,
            (UInt16) tempVal);
        /* FRS[11:10],LBWS[9:8], Clock Enable[4], ResetB[1], PLL En[0] */
        BspOsal_sleep(10U);
        tempVal = (frs << 10) | ((UInt32) 0x2 << 8) | ((UInt32) 1 << 4) |
            ((UInt32) 1 << 1) | ((UInt32) 1 << 0);
        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, PLLCTL1,
            (UInt16) tempVal);
        /* FRS[11:10],LBWS[9:8], Clock Enable[4], ResetB[1], PLL En[0] */
    }
    return retVal;
}

void Tc358778_lcdBridgeInit(UInt32 deviceI2cInstId, UInt32 slaveAddr, UInt32 peripheralCmdOn)
{
    BspDrv_lcdBridgeParams bridgeParams = {0};
    Fvid2_ModeInfo mInfo = {0};
    Tc358778_getLcdTiming(&mInfo);
    /* user defined */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, CONFCTL, (UInt16)0x0004U);
    /* Disable Parallel Input */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, SYSCTL, (UInt16)0x0001U);
    /* Assert Reset [0]=1 */
    BspOsal_sleep(10U);
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, SYSCTL, (UInt16)0x0000U);
    /* Release Reset, Exit Sleep */

    /* Program DSI Tx PLL */
    Tc358778_setupPll(deviceI2cInstId, slaveAddr, &bridgeParams, &mInfo);

    /* DPI Input Control */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, VSDLY, (UInt16)0x00D0U);
    /* V/Hsync Delay */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DATAFMT, (UInt16)0x0037U);
    /* DataFmt[7:4]=3, Loose Pk=0, Rsvrd=1, DSITx_En=1, Rsvrd=1 */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSITX_DT, (UInt16)0x003eU);
    /* DSITx DataID, RGB888 0x3E */

    /* DSI Tx PHY */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, CLW_CNTRL, (UInt32)0x00000000U);
    /* Disable DSI Clock Lane */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, D0W_CNTRL, (UInt32)0x00000000U);
    /* Disable DSI Data Lane0 */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, D1W_CNTRL, (UInt32)0x00000000U);
    /* Disable DSI Data Lane1 */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, D2W_CNTRL, (UInt32)0x00000000U);
    /* Disable DSI Data Lane2 */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, D3W_CNTRL, (UInt32)0x00000000U);
    /* Disable DSI Data Lane3 */

    /* DSI Tx PPI */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, LINEINITCNT, (UInt32)0x00002C88U);
    /* LP11 = 100 us for D-PHY Rx Init */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, LPTXTIMECNT, (UInt32)0x00000005U);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, TCLK_HEADERCNT, (UInt32)0x00001F06U);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, TCLK_TRAILCNT, (UInt32)0x00000003U);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, THS_HEADERCNT, (UInt32)0x00000606U);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, TWAKEUP, (UInt32)0x00004A88U);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, TCLK_POSTCNT, (UInt32)0x0000000BU);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, THS_TRAILCNT, (UInt32)0x00000004U);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, HSTXVREGEN, (UInt32)0x0000001FU);
    /* Enable Voltage Regulator for CSI (4 Data + Clk) Lanes */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, TXOPTIONCNTRL, (UInt32)0x00000001U);
    /* [0] = 1, Continuous Clock */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, BTACNTRL1, (UInt32)0x00050005U);
    /* Disable DSI Data Lane3 */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, STARTCNTRL, (UInt32)0x00000001U);
    /* Start PPI */

    /* DSI Tx Timing Control */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSI_EVENT, (UInt16)0x0001U);
    /* Set Event Mode */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSI_VSW,
        (UInt16)(mInfo.vBackPorch + mInfo.vSyncLen));
    /* Set This register to: Vertical Sync Width + VBP */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSI_VBPR, (UInt16)0x0U);
    /* VPBR not used in event mode */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSI_VACT,
        (UInt16) mInfo.height);
    /* Set Vertical Active line */

    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSI_HSW,
        (((mInfo.hBackPorch + mInfo.hSyncLen) * (bridgeParams.bitclk / 4U) *
           4U) / mInfo.pixelClock));
    /* (HSW+HBPR)/PClkFreq*ByteClkFreq*#Lanes */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSI_HBPR, (UInt16)0x0U);
    /* hbp (not used in event mode) */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSI_HACT,
        (UInt16)(mInfo.width * 3));
    /* Set Horizontal Active line byte count */

    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, DSI_START, (UInt32)0x00000001U);
    /* Start DSI Tx */
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, DSI_CONFW, (UInt32)0xA30000A7U);
    LcdBridge_32bWrite(deviceI2cInstId, slaveAddr, DSI_CONFW, (UInt32)0xC3008001U);

    /* clear FrmStop and RstPtr */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, PP_MISC, (UInt16)0x0U);
    /* DSI Panel Programming */

    if (peripheralCmdOn == (UInt32) TRUE)
    {
        /*Turn on Peripheral command*/
        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSICMD_TYPE, (UInt16)0x1032U);
        /* (Short packet, Data ID = Turn on peripheral command) */

        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSICMD_WC,0x0000);
        /*(WC1, WC0=0 for short write)  */

        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSICMD_WD0,0x0000);
        /*(WC=0) */

        LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, DSICMD_TX, (UInt16)0x0001U);
        /* (Start transfer) */
    }

    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, CONFCTL, (UInt16)0x0044U);
    /* Set Event Mode */

    return;
}

void Tc358778_lcdBridgeDeinit(UInt32 deviceI2cInstId, UInt32 slaveAddr)
{
    /* set FrmStop */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, PP_MISC, (UInt16)0x1000U);

    /* wait at least for one frame */
    BspOsal_sleep(50U);

    /* clear PP_en */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, CONFCTL, (UInt16)0x0004U);

    /* set RstPtr */
    LcdBridge_16bWrite(deviceI2cInstId, slaveAddr, PP_MISC, (UInt16)0xC000U);
}
