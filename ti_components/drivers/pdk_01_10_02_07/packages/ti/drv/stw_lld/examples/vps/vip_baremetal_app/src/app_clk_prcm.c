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
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

static Int32 Platform_PllCfg(UInt32 baseAddr,
                             UInt32 N,
                             UInt32 M,
                             UInt32 M2,
                             UInt32 clkCtrlValue);
static Int32 Platform_TI814xConfigHdvpssPll();
static Int32 Platform_TI814xEnableHdvpssClk();
static Int32 Platform_PllCfg(UInt32 baseAddr,
                             UInt32 N,
                             UInt32 M,
                             UInt32 M2,
                             UInt32 clkCtrlValue);
static Int32 Vps_platformTI814xSetPinMux(void);

#define REG32(x)                        *((volatile unsigned int *) (x))
#define PULLUDENABLE_ENABLE             (0x01U)
#define PULLUDENABLE_DISABLE            (0x00U)
#define PULLTYPESELECT_DOWN             (0x00U)
#define PULLTYPESELECT_UP               (0x02U)
#define INPUTENABLE_OUT                 (0x00U)
#define INPUTENABLE_BI                  (0x04U)
#define DEFAULT                         (0xFF)

/** \brief Control module base address */
#define CSL_TI814x_CTRL_MODULE_BASE      (0x48140000U)

#define CLKCTRL     0x4
#define TENABLE     0x8
#define TENABLEDIV  0xC
#define M2NDIV      0x10
#define MN2DIV      0x14
#define STATUS      0x24
#define OSC_FREQ    20

static void udelay(UInt32 delay)
{
    delay = delay * 100;
    while (delay--) ;
}

Int32 Platform_TI814xInit()
{
    Int32 retVal = BSP_SOK;
    retVal |= Vps_platformTI814xSetPinMux();
    retVal |= Platform_TI814xConfigHdvpssPll();
    retVal |= Platform_TI814xEnableHdvpssClk();
    return retVal;
}

static Int32 Platform_TI814xConfigHdvpssPll()
{
    return Platform_PllCfg(0x481C5170, 19, 800, 4, 0x801);
}

#define RM_HDVPSS_RSTCTRL           0x10u
#define CM_HDVPSS_CLKSTCTRL         0x00u
#define CM_HDVPSS_HDVPSS_CLK_CTRL   0x20u
#define CM_HDVPSS_HDMI_CLKCTRL      0x24u
/** \brief Function to enable HDVPSS clock */
static Int32 Platform_TI814xEnableHdvpssClk()
{
    volatile UInt32 repeatCnt;
    volatile UInt32 regValue;

    /* Bring the HDVPSS and HDMI out of reset */
    HW_WR_REG32(0x48180E00 + RM_HDVPSS_RSTCTRL, 0x0);

    /* Start a software forced  wakeup transition on the domain.*/
    regValue = 0x2;
    HW_WR_REG32(0x48180800 + CM_HDVPSS_CLKSTCTRL, regValue);
    /* Wait for 1000 cycles before checking for power update */
    udelay(1000);

    /* Enable HDVPSS Clocks */
    regValue = 0x2;
    HW_WR_REG32(0x48180800 + CM_HDVPSS_HDVPSS_CLK_CTRL, regValue);
    /* Enable HDMI Clocks */
    regValue = 0x2;
    HW_WR_REG32(0x48180800 + CM_HDVPSS_HDMI_CLKCTRL, regValue);

    repeatCnt = 0;
    while (repeatCnt < 1000)
    {
        /* Check for
         * Current Power State Status
         * HDVPSS memory state status
         * Logic state status */
        regValue = HW_RD_REG32(0x48180800 + CM_HDVPSS_CLKSTCTRL);
        if ((regValue & 0x100) == 0x100)
        {
            break;
        }
        udelay(1000);
        repeatCnt++;
    }
    if ((regValue & 0x100) != 0x100)
    {
        return -1;
    }
    repeatCnt = 0;
    while (repeatCnt < 1000)
    {
        /* Check for
         * Current Power State Status
         * HDVPSS memory state status
         * Logic state status */
        regValue = HW_RD_REG32(0x48180800 + CM_HDVPSS_HDVPSS_CLK_CTRL);
        if ((regValue & 0x2) == 0x2)
        {
            break;
        }
        udelay(1000);
        repeatCnt++;
    }
    if ((regValue & 0x2) != 0x2)
    {
        return -1;
    }
    /* Bring the HDVPSS and HDMI out of reset */
    HW_WR_REG32(0x48180E00 + RM_HDVPSS_RSTCTRL, 0x0);
    return (BSP_SOK);
}

static Int32 Platform_PllCfg(UInt32 baseAddr,
                             UInt32 N,
                             UInt32 M,
                             UInt32 M2,
                             UInt32 clkCtrlValue)
{
    Int32           rtnValue;
    UInt32          m2nval, mn2val, read_clkctrl;
    volatile UInt32 repeatCnt = 0;
    volatile UInt32 clkCtrlVal;
    uint32_t tmpRegVal;

    /* Put the PLL in bypass mode */
    clkCtrlVal  = HW_RD_REG32(baseAddr + CLKCTRL);
    clkCtrlVal |= 0x1 << 23;
    HW_WR_REG32(baseAddr + CLKCTRL, clkCtrlVal);

    repeatCnt = 0U;
    while (repeatCnt < 1000)
    {
        if (((HW_RD_REG32(baseAddr + STATUS)) & 0x00000101) == 0x00000101)
        {
            break;
        }
        /* Wait for the 100 cycles */
        udelay(10000);
        repeatCnt++;
    }
    if (((HW_RD_REG32(baseAddr + STATUS)) & 0x00000101) == 0x00000101)
    {}
    else
    {
        return -1;
    }

    /* we would require a soft reset before we program the dividers */
    tmpRegVal = HW_RD_REG32(baseAddr + CLKCTRL);
    tmpRegVal &= 0xfffffffe;
    HW_WR_REG32(baseAddr + CLKCTRL, tmpRegVal);
    udelay(3);

    /* Program the PLL for required frequency */
    m2nval = (M2 << 16) | N;
    mn2val = M;
    /*ref_clk     = OSC_FREQ/(N+1);
     * clkout_dco  = ref_clk*M;
     * clk_out     = clkout_dco/M2;
     */
    HW_WR_REG32(baseAddr + M2NDIV, m2nval);
    HW_WR_REG32(baseAddr + MN2DIV, mn2val);
    udelay(3);
    HW_WR_REG32(baseAddr + TENABLEDIV, 0x1);
    udelay(3);
    HW_WR_REG32(baseAddr + TENABLEDIV, 0x0);
    udelay(3);
    HW_WR_REG32(baseAddr + TENABLE, 0x1);
    udelay(3);
    HW_WR_REG32(baseAddr + TENABLE, 0x0);
    udelay(3);
    read_clkctrl = HW_RD_REG32(baseAddr + CLKCTRL);
    /*configure the TINITZ(bit0) and CLKDCO bits if required */
    HW_WR_REG32(baseAddr + CLKCTRL, ((read_clkctrl & 0xff7fe3ff) | clkCtrlValue));
    read_clkctrl = HW_RD_REG32(baseAddr + CLKCTRL);

    /* poll for the freq,phase lock to occur */
    repeatCnt = 0U;
    while (repeatCnt < 1000)
    {
        if (((HW_RD_REG32(baseAddr + STATUS)) & 0x00000600) == 0x00000600)
        {
            break;
        }
        /* Wait for the 100 cycles */
        udelay(10000);
        repeatCnt++;
    }
    if (((HW_RD_REG32(baseAddr + STATUS)) & 0x00000600) == 0x00000600)
    {
        rtnValue = 0;
    }
    else
    {
        rtnValue = -1;
    }
    /*wait fot the clocks to get stabized */
    udelay(1000);
    return (rtnValue);
}

static Int32 Vps_platformTI814xSetPinMux(void)
{
    /* Vout 0 configuration DVO2 Function 1*/
    /* TODO There are two pins for the fid. Need to see whichone is used */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AB8) = 0x1;   /* vout0_fid_mux1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0ABC) = 0x1;   /* vout0_clk */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AC0) = 0x1;   /* vout0_hsync */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AC4) = 0x1;   /* vout0_vsync */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AC8) = 0x1;   /* vout0_avid */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0ACC) = 0x1;   /* vout0_b_cb_c[2] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AD0) = 0x1;   /* vout0_b_cb_c[3] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AD4) = 0x1;   /* vout0_b_cb_c[4] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AD8) = 0x1;   /* vout0_b_cb_c[5] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0ADC) = 0x1;   /* vout0_b_cb_c[6] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AE0) = 0x1;   /* vout0_b_cb_c[7] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AE4) = 0x1;   /* vout0_b_cb_c[8] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AE8) = 0x1;   /* vout0_b_cb_c[9] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AEC) = 0x1;   /* vout0_g_y_yc[2] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AF0) = 0x1;   /* vout0_g_y_yc[3] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AF4) = 0x1;   /* vout0_g_y_yc[4] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AF8) = 0x1;   /* vout0_g_y_yc[5] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0AFC) = 0x1;   /* vout0_g_y_yc[6] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B00) = 0x1;   /* vout0_g_y_yc[7] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B04) = 0x1;   /* vout0_g_y_yc[8] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B08) = 0x1;   /* vout0_g_y_yc[9] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B0C) = 0x1;   /* vout0_r_cr[2] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B10) = 0x1;   /* vout0_r_cr[3] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B14) = 0x1;   /* vout0_r_cr[4] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B18) = 0x1;   /* vout0_r_cr[5] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B1C) = 0x1;   /* vout0_r_cr[6] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B20) = 0x1;   /* vout0_r_cr[7] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B24) = 0x1;   /* vout0_r_cr[8] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B28) = 0x1;   /* vout0_r_cr[9] */

    /* HDMI I2C_scl and I2C_sda Function 2*/
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0934) = 0x60002;  /* hdmi_ddc_scl_mux0
                                                            **/
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0938) = 0x60002;  /* hdmi_ddc_sda_mux0
                                                            **/
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x09BC) = 0x40010;  /*hdmi_hpd_mux0
                                                             *pinmmr112[4]*/
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x09B8) = 0x60010;  /*hdmi_cec_mux0
                                                             *pinmmr111[4] */
    /* TODO HDMI CEC and HPD to be added in pinmux */
    /* Currently its shared with GPMC. */

    /* VIN0 TODO Do we need to enable RXACTIVE Bit in pinmux for input pins? */
    /* Vin0 hsync1 and vin0 vsync1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A14) = 0x50001;  /* vin0_clk1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A18) = 0x0;      /* vin0_de0_mux0 -
                                                             *DeSelect input */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A1C) = 0x50001;  /* vin0_fld0_mux0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A20) = 0x50001;  /* vin0_clk0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A24) = 0x50001;  /* vin0_hsync0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A28) = 0x50001;  /* vin0_vsync0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A2C) = 0x50001;  /* vin0_d0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A30) = 0x50001;  /* vin0_d1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A34) = 0x50001;  /* vin0_d2 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A38) = 0x50001;  /* vin0_d3 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A3c) = 0x50001;  /* vin0_d4 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A40) = 0x50001;  /* vin0_d5 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A44) = 0x50001;  /* vin0_d6 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A48) = 0x50001;  /* vin0_d7 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A4c) = 0x50001;  /* vin0_d8 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A50) = 0x50001;  /* vin0_d9 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A54) = 0x50001;  /* vin0_d10 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A58) = 0x50001;  /* vin0_d11 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A5C) = 0x50001;  /* vin0_d12 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A60) = 0x50001;  /* vin0_d13 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A64) = 0x50001;  /* vin0_d14 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A68) = 0x50001;  /* vin0_d15 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A6C) = 0x50001;  /* vin0_d16 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A70) = 0x50001;  /* vin0_d17 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A74) = 0x50001;  /* vin0_d18 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A78) = 0x50001;  /* vin0_d19 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A7C) = 0x50001;  /* vin0_d20 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A80) = 0x50001;  /* vin0_d21 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A84) = 0x50001;  /* vin0_d22 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A88) = 0x50001;  /* vin0_d23 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A8C) = 0x50001;  /* vin0_de0_mux1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A90) = 0x50001;  /* vin0_de1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A94) = 0x50001;  /* vin0_fld0_mux1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0A98) = 0x50001;  /* vin0_fld1 */

    /* VIN1 Configuration Function 3*/
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B2C) = 0x50004;   /* vin1_hsync0 */
    /* this is function 2 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x09F0) = 0x50002;   /* vin1_clk1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B30) = 0x50004;   /* vin1_vsync0 */
#ifdef ORIGIAL_PORT
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B34) = 0x50004;   /* vin1_fid0 */
#endif /* ORIGIAL_PORT */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B34) = 0x50008;   /* vin1_de0 */

    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B38) = 0x50004;   /* vin1_clk0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B3C) = 0x50004;   /* vin1a_d[0] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B40) = 0x50004;   /* vin1a_d[1] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B44) = 0x50004;   /* vin1a_d[2] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B48) = 0x50004;   /* vin1a_d[3] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B4C) = 0x50004;   /* vin1a_d[4] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B50) = 0x50004;   /* vin1a_d[5] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B54) = 0x50004;   /* vin1a_d[6] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B58) = 0x50004;   /* vin1a_d[8] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B5C) = 0x50004;   /* vin1a_d[9] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B60) = 0x50004;   /* vin1a_d[10] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B64) = 0x50004;   /* vin1a_d[11] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B68) = 0x50004;   /* vin1a_d[12] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B6C) = 0x50004;   /* vin1a_d[13] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B70) = 0x50004;   /* vin1a_d[14] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B74) = 0x50004;   /* vin1a_d[15] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B78) = 0x50004;   /* vin1a_d[16] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B7C) = 0x50004;   /* vin1a_d[17] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B80) = 0x50004;   /* vin1a_d[18] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B84) = 0x50004;   /* vin1a_d[19] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B88) = 0x50004;   /* vin1a_d[20] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B8C) = 0x50004;   /* vin1a_d[21] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B90) = 0x50004;   /* vin1a_d[22] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B94) = 0x50004;   /* vin1a_d[23] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B98) = 0x50004;   /* vin1a_d[7] */

#ifdef ORIGIAL_PORT
    /* Function 2 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BA8) = 0x50002;   /* vin1a_d[0] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BAC) = 0x50002;   /* vin1a_d[1] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BB0) = 0x50002;   /* vin1a_d[2] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BB4) = 0x50002;   /* vin1a_d[3] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BB8) = 0x50002;   /* vin1a_d[4] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BBC) = 0x50002;   /* vin1a_d[5] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BC0) = 0x50002;   /* vin1a_d[6] */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0BC4) = 0x50002;   /* vin1a_d[7] */
#endif /* ORIGIAL_PORT */

    /* I2c2  configuration Function 6*/
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0924) = 0x60020;   /* i2c2_scl_mux0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0928) = 0x60020;   /* i2c2_sda_mux0 */

    /* TODO Find proper place for this Set the divider for the SYSCLK10 */
    *(UInt32 *) 0x48180324 = 3;

#if 0                                                      /* Idea was to make
                                                            * *VIP 1 vSync hSync
                                                            * *and clkc as input
                                                            *and watch GPIO */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B2C) = 0x50080; /* vin1_hsync0 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x09F0) = 0x50080; /* vin1_clk1 */
    REG32(CSL_TI814x_CTRL_MODULE_BASE + 0x0B30) = 0x50080; /* vin1_vsync0 */
#endif

    return (BSP_SOK);
}

