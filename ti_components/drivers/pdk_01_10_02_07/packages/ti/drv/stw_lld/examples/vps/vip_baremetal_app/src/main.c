/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>
#endif

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>

#include <app_frameBufMgmt.h>
#include <app_vipConfigure.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/drv/stw_lld/boards/stw_board.h>
#include <ti/drv/stw_lld/devices/stw_device.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>

#define TEST_CASE_DURATION (10)
#define TEST_CASE_LOOP     (20)

UInt32             gEnableInfiniteCaptLoop = 0;
volatile UInt32    gsubFrmCbCnt_s0portA    = 0;
volatile UInt32    gsubFrmCbCnt_s0portB    = 0;
volatile int       gNLinIntCount_s0portA   = 0;
volatile int       gNLinIntCount_s0portB   = 0;
volatile UInt32    gsubFrmAdd_s0portA;
volatile UInt32    gDqCount_portA = 0;
volatile UInt32    gDqCount_portB = 0;

Fvid2_SubFrameInfo gSubFrmInfo_s0portA;

extern UInt32      subFrmCallBackCount;
extern Int32 Platform_TI814xInit();
void vipCaptAppInit(void);
int32_t vipCaptModuleInit();

VpsCore_Frame *App_queBufs(void *drvData, UInt32 streamId, UInt32 chId)
{
    return (VpsCore_Frame *) App_GetFrameBuf((UInt32) drvData);
}

Int32 App_deQueBufs(void *drvData, VpsCore_Frame *frmBufList)
{
    if (BUF_ARRAY_IDX_PORTA == (UInt32) drvData)
    {
        gDqCount_portA++;
        /* Reset the subFrm call back count once frame is completely
         * captured */
        gsubFrmCbCnt_s0portA = 0;
    }
    else if (BUF_ARRAY_IDX_PORTB == (UInt32) drvData)
    {
        gDqCount_portB++;
        gsubFrmCbCnt_s0portB = 0;
    }

    App_ReleaseFrameBuf(frmBufList);
    return 0;
}

int main()
{
    Int32 retVal = 0;
    VpsDrv_CaptInstObj     *captObj_portA = NULL;
    VpsDrv_CaptInstObj     *captObj_portB = NULL;
    Vps_OverflowCheckParams isOverflowOccuredPortA;
    Vps_OverflowCheckParams isOverflowOccuredPortB;;
    UInt32 loop = 0;

    /*** START POINT ***/
    Bsp_printf("This VIP test will capture %d frames for %d iterations of open/close\r\n", TEST_CASE_DURATION, TEST_CASE_LOOP);
#if defined (TI814X_BUILD)
    Platform_TI814xInit();
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
    vipCaptAppInit();
    vipCaptModuleInit();
#endif

    Bsp_printf("***** START :: VPS Init\r\n");
    Vps_init(NULL);
    Bsp_printf("***** STOP  :: VPS Init\r\n");

    App_FrameBufInit();

    while(loop < TEST_CASE_LOOP)
    {
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
        return -1;
    }
    Bsp_printf("***** STOP  :: Configure VIP\r\n");

    gNLinIntCount_s0portA = 0;
    gNLinIntCount_s0portB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

#if defined (TI814X_BUILD)
    /* Following two function calls are only for TI814X_BUILD.
     * These should be called for all PORTs before calling any App_coreStart()
     */
    App_portReset(captObj_portA);
    App_portReset(captObj_portB);
#endif

    /* Start Capture */
    App_coreStart(captObj_portA);
    App_coreStart(captObj_portB);

    while ((gDqCount_portA < TEST_CASE_DURATION) || gEnableInfiniteCaptLoop)
    {
        /*
         * Wait for TEST_CASE_DURATION number of frames to be captured on
         * PORT A
         */
        /*Keep checking for the overflow*/
        if ((captObj_portA->overflowCount > 0) ||
            (captObj_portB->overflowCount > 0))
        {
            retVal  = App_checkOverflow(captObj_portA, &isOverflowOccuredPortA);
            retVal += App_checkOverflow(captObj_portB, &isOverflowOccuredPortB);
            if (BSP_SOK == retVal)
            {
#if defined (TI814X_BUILD)
                /*If overflow occured on port A or Port B, both ports get
                 * reset*/
                if (((UInt32) TRUE ==
                     isOverflowOccuredPortA.isOverflowOccured) ||
                    ((UInt32) TRUE == isOverflowOccuredPortB.isOverflowOccured))
                {
                    /*Stop the driver*/
                    App_coreStop(captObj_portA);
                    App_coreStop(captObj_portB);

                    /* Reset the VIP */
                    App_portReset(captObj_portA);
                    App_portReset(captObj_portB);
                    /* Restart the driver */
                    App_coreStart(captObj_portA);
                    App_coreStart(captObj_portB);
                    captObj_portA->overflowCount = 0;
                    captObj_portB->overflowCount = 0;
                }
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
                /* In vayu, we have selective reset. We can reset one VIP port
                 * without affecting the
                 * working of other
                 */
                if ((UInt32) TRUE == isOverflowOccuredPortA.isOverflowOccured)
                {
                    /*Stop the driver*/
                    App_coreStop(captObj_portA);

                    /* Reset the VIP */
                    App_portReset(captObj_portA);
                    /* Restart the driver */
                    App_coreStart(captObj_portA);
                    captObj_portA->overflowCount = 0;
                }
                if ((UInt32) TRUE == isOverflowOccuredPortB.isOverflowOccured)
                {
                    /*Stop the driver*/
                    App_coreStop(captObj_portB);

                    /* Reset the VIP */
                    App_portReset(captObj_portB);
                    /* Restart the driver */
                    App_coreStart(captObj_portB);
                    captObj_portB->overflowCount = 0;
                }

#endif
            }
        }
    }

    App_coreStop(captObj_portA);
    App_coreStop(captObj_portB);

    Bsp_printf("Frames captured on PortA            : %d\r\n", gDqCount_portA);
    Bsp_printf("Frames captured on PortB            : %d\r\n", gDqCount_portB);
    Bsp_printf("Sub-frame interrupts recvd on PortA : %d\r\n",
               gNLinIntCount_s0portA);
    Bsp_printf("Sub-frame interrupts recvd on PortB : %d\r\n",
               gNLinIntCount_s0portB);

    gNLinIntCount_s0portA = 0;
    gNLinIntCount_s0portB = 0;
    gDqCount_portA        = 0;
    gDqCount_portB        = 0;

    /* De-Initialize & Close the VIP Core*/
    App_coreClose(captObj_portA);
    App_coreClose(captObj_portB);
    loop++;
    Bsp_printf("Loop %d completed!!!\r\n\r\n", loop);
    }

    /* De-Initialize Frame buffer management and VPS library */
    App_FrameBufDeInit();
    Vps_deInit(NULL);

    Bsp_printf("VIP test Ends!!!\r\n");

    return 0;
}

void vipCaptAppInit(void)
{
    Int32 retVal;
    stwAppInitParams_t stwAppInitParams;

    /* System init */
    Intc_Init();
    Intc_IntEnable(0);

    StwUtils_appInitParams_init(&stwAppInitParams);
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        printf("\r\nSystem Init Failed ");
    }
}

int32_t vipCaptModuleInit()
{
    int32_t retVal = STW_SOK;

#if defined (SOC_TDA2EX)
    /* Set the VIN mux at control module level */
    HW_WR_FIELD32(
        (SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
         CTRL_CORE_VIP_MUX_SELECT),
        CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A,
        CTRL_CORE_VIP_MUX_SELECT_VIP_SEL_2A_GROUP2A);

    /* PinMux Configuration for VIN2A */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_VIP,
                            DEVICE_MODULE_VIP1_S1_PORTA_INST_ID_0,
                            BOARD_MODE_VIDEO_8BIT);

#else
    /* PinMux Configuration for VIN1A */
    BOARDConfigModulePinMux(DEVICE_MODULE_ID_VIP,
                            DEVICE_MODULE_VIP1_S0_PORTA_INST_ID_0,
                            BOARD_MODE_VIDEO_8BIT);
#endif
    return retVal;
}

