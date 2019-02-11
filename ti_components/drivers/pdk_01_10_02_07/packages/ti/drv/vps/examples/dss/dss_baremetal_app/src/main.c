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
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>

#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <AlignPattern_720_480.h>
#include <BitPattern_720_480.h>
#include <ColorPattern_720_480.h>
#include <ImagePattern_720_480.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define BUF_DSS_STRIDE          (720 * 2) /* Should be multiple of 16 */
#define BUF_DSS_HEIGHT          (480)

#define MAX_NUM_BUFS_PER_PIPE   (4)
#define MAX_NUM_VID_PIPE        (4)

#define MAX_DSS_BUF_SIZE        (BUF_DSS_STRIDE * BUF_DSS_HEIGHT)

#define HSI2C_INST              (HSI2C_INST_0)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

extern int App_DssRun(void);
extern void App_boardInit(void);
extern void App_logResult(void);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
static void App_DssSetLCD1PixClkPOlarity(UInt32 polarity);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern UInt32   AlignImg[];
extern UInt32   BitImg[];
extern UInt32   ColorImg[];
extern UInt32   Image[];

UInt32          FrameBufArrayDss[MAX_NUM_VID_PIPE][MAX_NUM_BUFS_PER_PIPE];
int32_t         gTestStatus = STW_SOK;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    UInt32 vidPipeIdx = 0, numBuff = 0;

    App_boardInit();

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    App_DssSetLCD1PixClkPOlarity(1);
#endif

    FrameBufArrayDss[vidPipeIdx][numBuff]     = (UInt32) AlignImg;
    FrameBufArrayDss[vidPipeIdx][numBuff + 1] = (UInt32) BitImg;
    FrameBufArrayDss[vidPipeIdx][numBuff + 2] = (UInt32) ColorImg;
    FrameBufArrayDss[vidPipeIdx][numBuff + 3] = (UInt32) Image;

    App_DssRun();

    App_logResult();

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
static void App_DssSetLCD1PixClkPOlarity(UInt32 polarity)
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
