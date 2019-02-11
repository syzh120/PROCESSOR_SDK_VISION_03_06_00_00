/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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
 *
 */

/*
 * main.c
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_gpio.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/dss/vps_dssDrv.h>
#include <ti/drv/vps/include/dss/vps_dctrlDrv.h>
#include <ti/drv/vps/include/dss/vps_dssDrv.h>
#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dctrl.h>
#include <ti/drv/vps/src/vpslib/dispcore/vpscore_dss.h>

#include <app_frameBufMgmt.h>
#include <app_videoLoopbackConfigure.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TEST_CASE_DURATION (1000)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern void App_boardInit(void);
extern void App_logResult(Int32 status);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
static void App_DssSetLCD1PixClkPolarity(UInt32 polarity);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

UInt32                 gEnableInfiniteCaptLoop = 0;
volatile UInt32        gDqCount_portA          = 0;
volatile UInt32        gDqCount_portB          = 0;
volatile int           gNLinIntCount_sxportA   = 0;
volatile int           gNLinIntCount_sxportB   = 0;
Int32                  gTestStatus = STW_SOK;

extern volatile UInt32 gDqCount_vid;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main()
{
    Int32  retVal = 0;
    UInt32 startTime, endTime, numTicks;
    float  timeInMs;
    VpsDrv_CaptInstObj  *captObj_portA = NULL;
    VpsDrv_CaptInstObj  *captObj_portB = NULL;
    VpsDrv_DispInstObj  *DispObj       = NULL;
    VpsDrv_DctrlInstObj *DctrlObj      = NULL;

    App_boardInit();

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    App_DssSetLCD1PixClkPolarity(1);
#endif

    Bsp_printf("***** START :: VPS Init\r\n");
    Vps_init(NULL);
    Bsp_printf("***** STOP  :: VPS Init\r\n");

    App_FrameBufInit();

    /* Initialize & Open the VIP Core */
    Bsp_printf("***** START :: VIP Core Initialization\r\n");
#if defined (SOC_TDA2EX)
    captObj_portA = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_A);
#else
    captObj_portA = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_A);
#endif

#if defined (SOC_TDA2EX)
    captObj_portB = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_B);
#else
    captObj_portB = App_coreOpen(VPSHAL_VIP1, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_B);
#endif
    if ((captObj_portA == NULL) || (captObj_portB == NULL))
    {
        Bsp_printf("***** FAILED :: VIP Core Open  ***** \r\n");
        App_logResult(STW_EFAIL);
        return -1;
    }
    Bsp_printf("***** STOP  :: VIP Core Initialization\r\n");

    /* Configure VIP1 module */
    Bsp_printf("***** START :: Configure VIP\r\n");
#if defined (SOC_TDA2EX)
    retVal = App_configureVIP(captObj_portA, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_A);
#else
    retVal = App_configureVIP(captObj_portA, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_A);
#endif

#if defined (SOC_TDA2EX)
    retVal |= App_configureVIP(captObj_portB, VPSHAL_VIP_S1, VPSHAL_VIP_PORT_B);
#else
    retVal |= App_configureVIP(captObj_portB, VPSHAL_VIP_S0, VPSHAL_VIP_PORT_B);
#endif
    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure VIP \r\n");
        App_logResult(STW_EFAIL);
        return -1;
    }
    Bsp_printf("***** STOP  :: Configure VIP\r\n");

    /* Initialize & Open the VIP Core */
    Bsp_printf("***** START :: DSS Core Initialization\r\n");
    DctrlObj = App_dctrlcoreOpen();
    if (DctrlObj == NULL)
    {
        Bsp_printf("***** FAILED :: Dctrl Core Open  ***** \r\n");
        App_logResult(STW_EFAIL);
        return -1;
    }

    /* Configure Dss and Dctrl module */
    Bsp_printf("***** START :: Configure Dctrl\r\n");
    retVal  = App_configureDctrl(DctrlObj);
    retVal |= App_configureDctrlPipe(DctrlObj);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure Dctrl \r\n");
        App_logResult(STW_EFAIL);
        return -1;
    }

    DispObj = App_dsscoreOpen(VPSDRV_DISP_INST_DSS_VID1);

    Bsp_printf("***** STOP  :: Dss Core Initialization\r\n");

    if (DispObj == NULL)
    {
        Bsp_printf("***** FAILED :: Dss Core Open  ***** \r\n");
        App_logResult(STW_EFAIL);
        return -1;
    }

    retVal = App_dssconfigure(DispObj);

    if (retVal != BSP_SOK)
    {
        Bsp_printf("***** FAIL  :: Configure Dss\r\n");
        App_logResult(STW_EFAIL);
        return -1;
    }
    Bsp_printf("***** STOP  :: Configure Dss\r\n");

    gNLinIntCount_sxportA = 0;
    gNLinIntCount_sxportB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

    /* Start Capture */
    App_coreStart(captObj_portA);
    App_coreStart(captObj_portB);

    /* Start display */
    App_dsscoreStart(DispObj);

    startTime = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    while ((gDqCount_portA < TEST_CASE_DURATION) || gEnableInfiniteCaptLoop)
    {
        /*
         * Wait for TEST_CASE_DURATION number of frames to be captured on
         * PORT A
         */
    }

    endTime = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    if (endTime < startTime)
    {
        /* Counter has wrapped around */
        numTicks = (0xFFFFFFFFU - endTime) + startTime;
    }
    else
    {
        numTicks = endTime - startTime;
    }
    timeInMs = numTicks / (32 * 1024);

    App_coreStop(captObj_portA);
    App_coreStop(captObj_portB);

    Bsp_printf("Frames captured on PortA            : %d   "
               "FPS of capture on Port A : %.2f \r\n",
               gDqCount_portA, (gDqCount_portA / timeInMs));
    Bsp_printf("Frames captured on PortB            : %d   "
               "FPS of capture on Port B : %.2f \r\n",
               gDqCount_portB, (gDqCount_portB / timeInMs));
    Bsp_printf("Sub-frame interrupts recvd on PortA : %d\r\n",
               gNLinIntCount_sxportA);
    Bsp_printf("Sub-frame interrupts recvd on PortB : %d\r\n",
               gNLinIntCount_sxportB);

    App_dsscoreStop(DispObj);

    Bsp_printf("Frames Displayed            : %d   FPS of Display : %.2f \r\n",
               gDqCount_vid, (gDqCount_vid / timeInMs));

    gNLinIntCount_sxportA = 0;
    gNLinIntCount_sxportB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

    /* De-Initialize & Close the VIP Core*/
    App_coreClose(captObj_portA);
    App_coreClose(captObj_portB);

    /* De-Initialize & Close the Dss and Dctrl Core*/
    App_dsscoreClose(DispObj);
    /* Add dctrl clear config */

    /* De-Initialize Frame buffer management and VPS library */
    App_FrameBufDeInit();
    Vps_deInit(NULL);

    App_logResult(gTestStatus);

    return 0;
}

VpsCore_Frame *App_queBufs(void *drvData, UInt32 streamId, UInt32 chId)
{
    return (VpsCore_Frame *) App_GetFrameBuf((UInt32) drvData);
}

Int32 App_deQueBufs(void *drvData, VpsCore_Frame *frmBufList)
{
    if (BUF_ARRAY_IDX_PORTA == (UInt32) drvData)
    {
        gDqCount_portA++;
    }
    else if (BUF_ARRAY_IDX_PORTB == (UInt32) drvData)
    {
        gDqCount_portB++;
    }

    App_ReleaseFrameBuf(frmBufList, (UInt32) drvData);
    return 0;
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
/*
 * Due to HW bug, polarity cannot be set by vencInfo.pixelClkPolarity
 * So need to change the register SMA_SW_1 which mirrors some fields of
 * the control register.setting 1 will make LCD1 Pixel clock to be negative
 * polarity. This is required as there is an inverter in the LCD panel which
 * will effectively cause the source to sample data at rising edge of the
 * clock instead of falling edge. So changing the polarity to negative.
 */
static void App_DssSetLCD1PixClkPolarity(UInt32 polarity)
{
    UInt32 regVal;

    regVal = HW_RD_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1);

    HW_SET_FIELD32(regVal, CTRL_CORE_SMA_SW_1_DSS_CH0_IPC, polarity);

    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_SMA_SW_1,
        regVal);
}

#endif
