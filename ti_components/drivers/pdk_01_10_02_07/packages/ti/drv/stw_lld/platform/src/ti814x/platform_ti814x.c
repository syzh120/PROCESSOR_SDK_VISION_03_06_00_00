/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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

/*
 * \file startup.c
 *
 * \brief  Configures the PLL registers to achieve the required Operating
 *         frequency. Power and sleep controller is activated for UART and
 *         Interuppt controller. Interrupt vector is copied to the shared Ram.
 *         After doing all the above, controller is given to the application.
 *
 */

#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/hw_types.h>

/***********************************************************************
**                            MACRO DEFINITIONS
***********************************************************************/
#define E_PASS                         (0)
#define E_FAIL                         (-(int32_t)1)

/***********************************************************************
**                     EXTERNAL FUNCTION PROTOTYPES
***********************************************************************/

/**********************************************************************
 *                   INTERNAL FUNCTION PROTOTYPES
 **********************************************************************/

static void PlatformMCSPIPrcmEnable(void);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

void PlatformMCASP2SetPinMux(void)
{
    HW_WR_REG32(PAD39_CNTRL, 0x60001); /* ACLKX  */
    HW_WR_REG32(PAD40_CNTRL, 0x60001); /* FSX    */
    HW_WR_REG32(PAD41_CNTRL, 0x60001); /* AXR0   */
    HW_WR_REG32(PAD42_CNTRL, 0x60001); /* AXR1   */
    HW_WR_REG32(PAD16_CNTRL, 0x60001); /* AHCLKX */
}

void PlatformMCASP5SetPinMux(void)
{
    HW_WR_REG32(PAD55_CNTRL, 0x60001); /* ACLKX  */
    HW_WR_REG32(PAD56_CNTRL, 0x60001); /* FSX    */
    HW_WR_REG32(PAD57_CNTRL, 0x60001); /* AXR0   */
    HW_WR_REG32(PAD58_CNTRL, 0x60001); /* AXR1   */
    HW_WR_REG32(PAD16_CNTRL, 0x60008); /* AHCLKX */
}

void PlatformMCSPI0SetPinMux(void)
{
    HW_WR_REG32(PAD80_CNTRL, 0x60001); /* CS1  */
    HW_WR_REG32(PAD81_CNTRL, 0x60001); /* CS0  */
    HW_WR_REG32(PAD82_CNTRL, 0x40001); /* SCLK */
    HW_WR_REG32(PAD83_CNTRL, 0x40001); /* D1   */
    HW_WR_REG32(PAD84_CNTRL, 0x60001); /* D0   */
}

void PlatformMCSPI1SetPinMux(void)
{
    HW_WR_REG32(PAD85_CNTRL, 0x60001); /* CS1  */
    HW_WR_REG32(PAD86_CNTRL, 0x60001); /* CS0  */
    HW_WR_REG32(PAD87_CNTRL, 0x40001); /* SCLK */
    HW_WR_REG32(PAD88_CNTRL, 0x40001); /* D1   */
    HW_WR_REG32(PAD89_CNTRL, 0x60001); /* D0   */
}

void PlatformMCASP2PrcmEnable(void)
{
    HW_WR_REG32(CM_ALWON_MCASP_2_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_MCASP_2_CLKCTRL) != 0x2U)
    {
        ;
    }
}

void PlatformEDMAPrcmEnable(void)
{
    HW_WR_REG32(CM_ALWON_TPCC_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_TPCC_CLKCTRL) != 0x2U)
    {
        ;
    }

    HW_WR_REG32(CM_ALWON_TPTC0_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_TPTC0_CLKCTRL) != 0x2U)
    {
        ;
    }

    HW_WR_REG32(CM_ALWON_TPTC1_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_TPTC1_CLKCTRL) != 0x2U)
    {
        ;
    }

    HW_WR_REG32(CM_ALWON_TPTC2_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_TPTC2_CLKCTRL) != 0x2U)
    {
        ;
    }

    HW_WR_REG32(CM_ALWON_TPTC3_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_TPTC3_CLKCTRL) != 0x2U)
    {
        ;
    }
}

void PlatformUARTClockEnable(void)
{
    /* UARTs */
    HW_WR_REG32(CM_ALWON_UART_0_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_UART_0_CLKCTRL) != 0x2U)
    {
        ;
    }

    HW_WR_REG32(CM_ALWON_UART_1_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_UART_1_CLKCTRL) != 0x2U)
    {
        ;
    }

    HW_WR_REG32(CM_ALWON_UART_2_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_UART_2_CLKCTRL) != 0x2U)
    {
        ;
    }

    while ((HW_RD_REG32(CM_ALWON_L3_SLOW_CLKSTCTRL) & 0x2100U) != 0x2100U)
    {
        ;
    }
}

void PlatformUARTSetPinMux(void)
{
    HW_WR_REG32(PAD70_CNTRL, 0x60001);
    HW_WR_REG32(PAD71_CNTRL, 0x60001);
    HW_WR_REG32(PAD72_CNTRL, 0x60001);
    HW_WR_REG32(PAD73_CNTRL, 0x60001);
}

void PlatformI2CClockEnable(void)
{
    /* Set the access to the I2c registers */
    HW_WR_REG32(CM_ALWON_I2C_0_CLKCTRL, 0x2);
    HW_WR_REG32(CM_ALWON_I2C_2_CLKCTRL, 0x2);
}

void PlatformI2CSetPinMux(void)
{
    /* I2c2  configuration Function 6*/
    HW_WR_REG32(PADCTRL_BASE + (uint32_t) 0x0924, 0x60020); /* i2c2_scl_mux0 */
    HW_WR_REG32(PADCTRL_BASE + (uint32_t) 0x0928, 0x60020); /* i2c2_sda_mux0 */

    /* I2c0 configuration function 1*/
    HW_WR_REG32(PADCTRL_BASE + (uint32_t) 0x0c18, 0x60001);   /* i2c0_scl */
    HW_WR_REG32(PADCTRL_BASE + (uint32_t) 0x0c1c, 0x60001);   /* i2c0_sda */
}

void PlatformXBARIntMux(uint32_t xbarIntNum, uint32_t XBARNum)
{
    uint32_t regIndex = 0, regBitPos, val;
    uint32_t tmpOffset;

    /*Get Register index*/
    regIndex = XBARNum / 4U;

    /*Get bit position of MUX to be configured */
    regBitPos = (XBARNum % 4U) * 8U;

    /*Program the XBAR with peripheral crossbar interrupt num*/
    tmpOffset = DUCATI_INTMUX_0_3_CNTL + (regIndex * 4U);
    val       = HW_RD_REG32(tmpOffset);
    val       = (val & ((uint32_t) 0xFF << (regBitPos))) |
                (xbarIntNum << regBitPos);
    tmpOffset = DUCATI_INTMUX_0_3_CNTL + (regIndex * 4U);
    HW_WR_REG32(tmpOffset, val);
}

void PlatformGPMCPinCtrl(void)
{
    HW_WR_REG32(PAD89_CNTRL, 0x00010001);  /* GPMC_D[0] */
    HW_WR_REG32(PAD90_CNTRL, 0x00010001);  /* GPMC_D[1] */
    HW_WR_REG32(PAD91_CNTRL, 0x00010001);  /* GPMC_D[2] */
    HW_WR_REG32(PAD92_CNTRL, 0x00010001);  /* GPMC_D[3] */
    HW_WR_REG32(PAD93_CNTRL, 0x00010001);  /* GPMC_D[4] */
    HW_WR_REG32(PAD94_CNTRL, 0x00010001);  /* GPMC_D[5] */
    HW_WR_REG32(PAD95_CNTRL, 0x00010001);  /* GPMC_D[6] */
    HW_WR_REG32(PAD96_CNTRL, 0x00010001);  /* GPMC_D[7] */
    HW_WR_REG32(PAD97_CNTRL, 0x00010001);  /* GPMC_D[8] */
    HW_WR_REG32(PAD98_CNTRL, 0x00010001);  /* GPMC_D[9] */
    HW_WR_REG32(PAD99_CNTRL, 0x00010001);  /* GPMC_D[10] */
    HW_WR_REG32(PAD100_CNTRL, 0x00010001); /* GPMC_D[11] */
    HW_WR_REG32(PAD101_CNTRL, 0x00010001); /* GPMC_D[12] */
    HW_WR_REG32(PAD102_CNTRL, 0x00010001); /* GPMC_D[13] */
    HW_WR_REG32(PAD103_CNTRL, 0x00010001); /* GPMC_D[14] */
    HW_WR_REG32(PAD104_CNTRL, 0x00010001); /* GPMC_D[15] */

    HW_WR_REG32(PAD235_CNTRL, HW_RD_REG32(PAD235_CNTRL) | 0x01U);

    HW_WR_REG32(PAD117_CNTRL, 0x00010002); /* GPMC_A[1] */
    HW_WR_REG32(PAD118_CNTRL, 0x00010002); /* GPMC_A[2] */
    HW_WR_REG32(PAD119_CNTRL, 0x00010002); /* GPMC_A[3] */
    HW_WR_REG32(PAD120_CNTRL, 0x00010002); /* GPMC_A[4] */
    HW_WR_REG32(PAD168_CNTRL, 0x00010010); /* GPMC_A[5] */
    HW_WR_REG32(PAD169_CNTRL, 0x00010010); /* GPMC_A[6] */
    HW_WR_REG32(PAD170_CNTRL, 0x00010010); /* GPMC_A[7] */
    HW_WR_REG32(PAD171_CNTRL, 0x00010010); /* GPMC_A[8] */
    HW_WR_REG32(PAD172_CNTRL, 0x00010010); /* GPMC_A[9] */
    HW_WR_REG32(PAD173_CNTRL, 0x00010010); /* GPMC_A[10] */
    HW_WR_REG32(PAD174_CNTRL, 0x00010010); /* GPMC_A[11] */
    HW_WR_REG32(PAD175_CNTRL, 0x00010010); /* GPMC_A[12] */
    HW_WR_REG32(PAD228_CNTRL, 0x00010002); /* GPMC_A[13] */
    HW_WR_REG32(PAD229_CNTRL, 0x00010002); /* GPMC_A[14] */
    HW_WR_REG32(PAD230_CNTRL, 0x00010002); /* GPMC_A[15] */
    HW_WR_REG32(PAD105_CNTRL, 0x00010001); /* GPMC_A[16] */
    HW_WR_REG32(PAD106_CNTRL, 0x00010001); /* GPMC_A[17] */
    HW_WR_REG32(PAD107_CNTRL, 0x00010001); /* GPMC_A[18] */
    HW_WR_REG32(PAD108_CNTRL, 0x00010001); /* GPMC_A[19] */
    HW_WR_REG32(PAD109_CNTRL, 0x00010001); /* GPMC_A[20] */
    HW_WR_REG32(PAD110_CNTRL, 0x00010001); /* GPMC_A[21] */
    HW_WR_REG32(PAD111_CNTRL, 0x00010001); /* GPMC_A[22] */
    HW_WR_REG32(PAD112_CNTRL, 0x00010001); /* GPMC_A[23] */
    HW_WR_REG32(PAD124_CNTRL, 0x00010002); /* GPMC_A[24] */
    HW_WR_REG32(PAD123_CNTRL, 0x00010002); /* GPMC_A[25] */
    HW_WR_REG32(PAD116_CNTRL, 0x00010002); /* GPMC_A[27] */
    /* gpmc_CS0 */
    HW_WR_REG32(PAD122_CNTRL, HW_RD_REG32(PAD122_CNTRL) | 0x01U);
    /* gpmc_CS3 */
    HW_WR_REG32(PAD125_CNTRL, HW_RD_REG32(PAD125_CNTRL) | 0x01U);
    /* gpmc_CS4 */
    HW_WR_REG32(PAD126_CNTRL, HW_RD_REG32(PAD126_CNTRL) | 0x01U);
    /* gpmc_clk */
    HW_WR_REG32(PAD127_CNTRL, HW_RD_REG32(PAD127_CNTRL) | 0x01U);
    /* gpmc_advn_ale */
    HW_WR_REG32(PAD128_CNTRL, HW_RD_REG32(PAD128_CNTRL) | 0x01U);
    /* gpmc_oen_ren */
    HW_WR_REG32(PAD129_CNTRL, HW_RD_REG32(PAD129_CNTRL) | 0x01U);
    /* gpmc_wen */
    HW_WR_REG32(PAD130_CNTRL, HW_RD_REG32(PAD130_CNTRL) | 0x01U);
    /* gpmc_ben[0] */
    HW_WR_REG32(PAD131_CNTRL, HW_RD_REG32(PAD131_CNTRL) | 0x01U);
    /* gpmc_ben[1] */
    HW_WR_REG32(PAD132_CNTRL, HW_RD_REG32(PAD132_CNTRL) | 0x01U);
    /* gpmc_wait0 */
    HW_WR_REG32(PAD133_CNTRL, HW_RD_REG32(PAD133_CNTRL) | 0x01U);

    HW_WR_REG32(PAD243_CNTRL, HW_RD_REG32(PAD243_CNTRL) | 0x10U);
    HW_WR_REG32(PAD244_CNTRL, HW_RD_REG32(PAD244_CNTRL) | 0x10U);
    HW_WR_REG32(PAD245_CNTRL, HW_RD_REG32(PAD245_CNTRL) | 0x10U);
    HW_WR_REG32(PAD246_CNTRL, HW_RD_REG32(PAD246_CNTRL) | 0x10U);
    HW_WR_REG32(PAD247_CNTRL, HW_RD_REG32(PAD247_CNTRL) | 0x10U);
    HW_WR_REG32(PAD248_CNTRL, HW_RD_REG32(PAD248_CNTRL) | 0x10U);
    HW_WR_REG32(PAD249_CNTRL, HW_RD_REG32(PAD249_CNTRL) | 0x10U);
    HW_WR_REG32(PAD250_CNTRL, HW_RD_REG32(PAD250_CNTRL) | 0x10U);
    HW_WR_REG32(PAD251_CNTRL, HW_RD_REG32(PAD251_CNTRL) | 0x10U);
    HW_WR_REG32(PAD252_CNTRL, HW_RD_REG32(PAD252_CNTRL) | 0x10U);
    HW_WR_REG32(PAD253_CNTRL, HW_RD_REG32(PAD253_CNTRL) | 0x10U);
    HW_WR_REG32(PAD254_CNTRL, HW_RD_REG32(PAD254_CNTRL) | 0x10U);
    HW_WR_REG32(PAD255_CNTRL, HW_RD_REG32(PAD255_CNTRL) | 0x10U);
    HW_WR_REG32(PAD256_CNTRL, HW_RD_REG32(PAD256_CNTRL) | 0x10U);
    HW_WR_REG32(PAD257_CNTRL, HW_RD_REG32(PAD257_CNTRL) | 0x10U);
    HW_WR_REG32(PAD258_CNTRL, HW_RD_REG32(PAD258_CNTRL) | 0x10U);

    HW_WR_REG32(PAD115_CNTRL, 0x00020080);  /* NOR_EN */
}

void PlatformGPIOClockEnable(void)
{
    /* Set the access to the GPIO registers */
    HW_WR_REG32(CM_ALWON_GPIO_0_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_GPIO_0_CLKCTRL) != 0x2U)
    {
        ;
    }
    /* Enable GPI1 System and Functional Clock */
    HW_WR_REG32(CM_ALWON_GPIO_1_CLKCTRL, 0x2);
    /* Poll till Module is functional */
    while (HW_RD_REG32(CM_ALWON_GPIO_1_CLKCTRL) != 0x2U)
    {
        ;
    }
}

void PlatformGPMCClockEnable(void)
{
    /* Set the access to the GPMC registers */
    HW_WR_REG32(CM_ALWON_GPMC_CLKCTRL, 0x2); /* Enable GPMC Clock */
    while (HW_RD_REG32(CM_ALWON_GPMC_CLKCTRL) != 0x2U)
    {
        ;
    }
}

static void PlatformMCSPIPrcmEnable(void)
{
    HW_WR_REG32(CM_ALWON_SPI_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_SPI_CLKCTRL) != 0x2U)
    {
        ;
    }
}

void PlatformMCSPI0PrcmEnable(void)
{
    PlatformMCSPIPrcmEnable();
}

void PlatformMCSPI1PrcmEnable(void)
{
    PlatformMCSPIPrcmEnable();
}

void PlatformUartConsoleSetPinMux(void)
{
    /* For TI814X UART console pin mux not required */
}

/* ========================================================================== */
/*                         Deprecated Functions                               */
/* ========================================================================== */
void GPMC_clock_enable(void)
{
    PlatformGPMCClockEnable();
}

void GPIO_clock_enable(void)
{
    PlatformGPIOClockEnable();
}

void MCASP2_pad_mux_config(void)
{
    PlatformMCASP2SetPinMux();
}

void MCASP5_pad_mux_config(void)
{
    PlatformMCASP5SetPinMux();
}

void MCSPI0_pad_mux_config(void)
{
    PlatformMCSPI0SetPinMux();
}

void MCSPI1_pad_mux_config(void)
{
    PlatformMCSPI1SetPinMux();
}

void MCASP2_prcm_enable(void)
{
    PlatformMCASP2PrcmEnable();
}

void EDMA_prcm_enable(void)
{
    PlatformEDMAPrcmEnable();
}

void UART_clock_enable(void)
{
    PlatformUARTClockEnable();
}

void I2C_clock_enable(void)
{
    PlatformI2CClockEnable();
}

void I2C_pad_mux_config(void)
{
    PlatformI2CSetPinMux();
}

void XBAR_Int_Mux(uint32_t xbarIntNum, uint32_t XBARNum)
{
    PlatformXBARIntMux(xbarIntNum, XBARNum);
}

void GPMC_pin_Ctrl(void)
{
    PlatformGPMCPinCtrl();
}

void MCASP_3_4_5_prcm_enable(void)
{
    HW_WR_REG32(CM_ALWON_MCASP_3_4_5_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_MCASP_3_4_5_CLKCTRL) != 0x2U)
    {
        ;
    }
}

void MCSPI0_1_2_3_prcm_enable(void)
{
    HW_WR_REG32(CM_ALWON_SPI_CLKCTRL, 0x2);
    while (HW_RD_REG32(CM_ALWON_SPI_CLKCTRL) != 0x2U)
    {
        ;
    }
}

/***************************** End Of File ***********************************/
