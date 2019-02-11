/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vpshal_calCsi2Tda3x.c
 *
 *  \brief This file the function to initialize CSI2 PHY for TDA3x platform
 *
 *  TODO / TBD
 *  3. Pad Control Register base address - should be received as we do for CAL
 *      and PHY. SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE
 *  4. Pad PULL UP / DOWN Control reg same as above
 *      CTRL_CORE_PAD_IO_SMA_SW_10
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/stw_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>

#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_iss.h>

#include <ti/drv/vps/include/iss/vps_cfgcal.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isscal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SMA_SW_CSI2_X0_UP_MASK             (0x00000001U)
#define SMA_SW_CSI2_Y0_UP_MASK             (0x00000002U)

#define SMA_SW_CSI2_X1_UP_MASK             (0x00000004U)
#define SMA_SW_CSI2_Y1_UP_MASK             (0x00000008U)

#define SMA_SW_CSI2_X2_UP_MASK             (0x00000010U)
#define SMA_SW_CSI2_Y2_UP_MASK             (0x00000020U)

#define SMA_SW_CSI2_X3_UP_MASK             (0x00000040U)
#define SMA_SW_CSI2_Y3_UP_MASK             (0x00000080U)

#define SMA_SW_CSI2_X4_UP_MASK             (0x00000100U)
#define SMA_SW_CSI2_Y4_UP_MASK             (0x00000200U)

#define SMA_SW_CSI2_X0_DW_MASK             (0x00000400U)
#define SMA_SW_CSI2_Y0_DW_MASK             (0x00000800U)

#define SMA_SW_CSI2_X1_DW_MASK             (0x00001000U)
#define SMA_SW_CSI2_Y1_DW_MASK             (0x00002000U)

#define SMA_SW_CSI2_X2_DW_MASK             (0x00004000U)
#define SMA_SW_CSI2_Y2_DW_MASK             (0x00008000U)

#define SMA_SW_CSI2_X3_DW_MASK             (0x00010000U)
#define SMA_SW_CSI2_Y3_DW_MASK             (0x00020000U)

#define SMA_SW_CSI2_X4_DW_MASK             (0x00040000U)
#define SMA_SW_CSI2_Y4_DW_MASK             (0x00080000U)

/**< Bit 2 set, used to compute register values for lanes enabled. */
#define CSI2_X_LANE_ENABLED                ((uint32_t)0x4U)

/**< Functional PHY clock is expected to be 96 MHz
        Period of PHY clock in nS is 10.41666
        ((1/<PHY Clock) / 1e-9) */
#define DPHY_FUNCTIONAL_CLK_PERIOD  (10.41666)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Prototype                                */
/* ========================================================================== */

static void ConfigureCamRxCtrl(const vpsissCalCmplxIoCfg_t *pCmplxIoCfg,
                                uint32_t inst);
static void ConfigureStopStateTimeouts(uint32_t camRxCoreBaseAddr,
                                        uint32_t csi2Clk, uint32_t inst);

/* ========================================================================== */
/*                          Function Implementations                          */
/* ========================================================================== */

int32_t VpsHal_calPhyEnClockAndReset(uint32_t            baseAddr,
                                     uint32_t            cam0RxCoreBaseAddr,
                                     uint32_t            cam1RxCoreBaseAddr,
                                     const isshalCalInstCfg_t *pCfg)
{
    int32_t                rtnVal;
    uint32_t               idx;
    volatile uint32_t      reg, timeOut;

    GT_assert(VpsHalTrace, (0U != baseAddr));
    GT_assert(VpsHalTrace, (0U != cam0RxCoreBaseAddr));
    GT_assert(VpsHalTrace, (NULL != pCfg));

    rtnVal = FVID2_SOK;
    /* Steps
     *  1. Configure D-PHY mode and enable required lanes
     *  2. Reset complex IO - Wait for completion of reset
     *          Note if the external sensor is not sending byte clock, the
     *          reset will timeout
     *  3 Program Stop States
     *      A. Program THS_TERM, THS_SETTLE, etc... Timings parameters in terms
     *              of DDR clock periods
     *      B. Enable stop state transition timeouts
     *  4.Force FORCERXMODE
     *      D. Enable pull down using pad control
     *      E. Power up PHY
     *      F. Wait for power up completion
     *      G. Wait for all enabled lane to reach stop state
     *      H. Disable pull down using pad control
     */
    for(idx = 0U; ((idx < pCfg->numCmplxIoInst) &&
                    (TRUE == pCfg->cmplxIoCfg[idx].enable)); idx++)
    {
        /* 1. Configure D-PHY mode and enable required lanes */
        ConfigureCamRxCtrl((const vpsissCalCmplxIoCfg_t *)
                            &pCfg->cmplxIoCfg[idx], idx);

        if((FVID2_SOK == rtnVal) && (0U != cam0RxCoreBaseAddr))
        {
            /* 2. Reset complex IO - Do not wait for reset completion */
            reg  = reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg |= CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);
            /* Dummy read to allow SCP to complete */
            reg     = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            timeOut = 0xFFFFFU;

            /* Timeouts */
            ConfigureStopStateTimeouts(cam0RxCoreBaseAddr,
                                        pCfg->csi2PhyClock[idx], idx);

            /* B. Enable stop state transition timeouts */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_TIMING(idx));

            reg &= ~((UInt32) (CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK |
                               CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK |
                               CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK |
                               CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK));
            reg |= CAL_CSI2_TIMING_STOP_STATE_X16_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_x16_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X16_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_X4_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_x4_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_X4_IO1_SHIFT);
            reg |= CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_MASK &
                   (pCfg->ppiCfg[idx].csi2Cfg.stop_state_counter_I01 <<
                    CAL_CSI2_TIMING_STOP_STATE_COUNTER_IO1_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_TIMING(idx), reg);

            /* 4 Force FORCERXMODE */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_TIMING(idx));
            reg |= CAL_CSI2_TIMING_FORCE_RX_MODE_IO1_MASK;
            HW_WR_REG32(baseAddr + CAL_CSI2_TIMING(idx), reg);

            /* D. Enable pull down on all lanes used */
            reg = HW_RD_REG32(
                SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10);
            /* These are active low */
            /* Assert PULL DOWN */
            reg &= ~(SMA_SW_CSI2_X0_DW_MASK | SMA_SW_CSI2_Y0_DW_MASK |
                     SMA_SW_CSI2_X1_DW_MASK | SMA_SW_CSI2_Y1_DW_MASK |
                     SMA_SW_CSI2_X2_DW_MASK | SMA_SW_CSI2_Y2_DW_MASK |
                     SMA_SW_CSI2_X3_DW_MASK | SMA_SW_CSI2_Y3_DW_MASK |
                     SMA_SW_CSI2_X4_DW_MASK | SMA_SW_CSI2_Y4_DW_MASK);

            /* De Assert PULL UP */
            reg |= (SMA_SW_CSI2_X0_UP_MASK | SMA_SW_CSI2_Y0_UP_MASK |
                    SMA_SW_CSI2_X1_UP_MASK | SMA_SW_CSI2_Y1_UP_MASK |
                    SMA_SW_CSI2_X2_UP_MASK | SMA_SW_CSI2_Y2_UP_MASK |
                    SMA_SW_CSI2_X3_UP_MASK | SMA_SW_CSI2_Y3_UP_MASK |
                    SMA_SW_CSI2_X4_UP_MASK | SMA_SW_CSI2_Y4_UP_MASK);
            HW_WR_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10,
                        reg);

            /* E. Power up the PHY using the complex IO */
            reg  = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
            reg |= CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_MASK &
                   ((UInt32) CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_STATE_ON <<
                             CAL_CSI2_COMPLEXIO_CFG_PWR_CMD_SHIFT);
            HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);

            /* F. Wait for power up completion */
            timeOut = 0xFFFFFFU;
            while(timeOut)
            {
                reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                reg = (reg & CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_MASK);
                reg = (reg >> CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_SHIFT);
                if(CAL_CSI2_COMPLEXIO_CFG_PWR_STATUS_STATE_ON == reg)
                {
                    break;
                }
                timeOut--;
            }
            if(0U == timeOut)
            {
                /* Could not power up the PHY... */
                rtnVal = FVID2_ETIMEOUT;
                GT_assert(VpsHalTrace, ((uint32_t)FALSE));
                break;
            }

            /* These are active low */
            /* De Assert PULL DOWN */
            reg = HW_RD_REG32(
                SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10);
            reg |= (SMA_SW_CSI2_X0_DW_MASK | SMA_SW_CSI2_Y0_DW_MASK |
                    SMA_SW_CSI2_X1_DW_MASK | SMA_SW_CSI2_Y1_DW_MASK |
                    SMA_SW_CSI2_X2_DW_MASK | SMA_SW_CSI2_Y2_DW_MASK |
                    SMA_SW_CSI2_X3_DW_MASK | SMA_SW_CSI2_Y3_DW_MASK |
                    SMA_SW_CSI2_X4_DW_MASK | SMA_SW_CSI2_Y4_DW_MASK);

            /* Assert PULL UP */
            reg &= ~((UInt32) (SMA_SW_CSI2_X0_UP_MASK | SMA_SW_CSI2_Y0_UP_MASK |
                               SMA_SW_CSI2_X1_UP_MASK | SMA_SW_CSI2_Y1_UP_MASK |
                               SMA_SW_CSI2_X2_UP_MASK | SMA_SW_CSI2_Y2_UP_MASK |
                               SMA_SW_CSI2_X3_UP_MASK | SMA_SW_CSI2_Y3_UP_MASK |
                               SMA_SW_CSI2_X4_UP_MASK | SMA_SW_CSI2_Y4_UP_MASK));
            HW_WR_REG32(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_PAD_IO_SMA_SW_10,
                        reg);
        }
    }

    return rtnVal;
}

/**************************Function Separator**********************************/

static void ConfigureCamRxCtrl(const vpsissCalCmplxIoCfg_t *pCmplxIoCfg,
                                uint32_t inst)
{
    volatile uint32_t reg, enaLanes;
    uint32_t laneMode;

    reg = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                      CTRL_CORE_CONTROL_CAMERA_RX);
    reg &= ~((UInt32) (CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_MODE_MASK |
                       CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_MASK |
                       CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_MASK |
                       CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_MASK));

    /* 1. Configure D PHY mode */
    /* Enable clock lane */
    reg |= CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_MODE_MASK;

    /* Enable Required lanes */
    enaLanes    = 0x0;
    if((uint32_t)TRUE == pCmplxIoCfg->enable)
    {
        laneMode = 0U;
        if (0U == inst)
        {
            laneMode = CSI2_X_LANE_ENABLED;
        }

        if(0x0U != pCmplxIoCfg->clockLane.position)
        {
            enaLanes |= laneMode << pCmplxIoCfg->clockLane.position;
        }
        if(0x0U != pCmplxIoCfg->data1Lane.position)
        {
            enaLanes |= laneMode << pCmplxIoCfg->data1Lane.position;
        }
        if(0x0U != pCmplxIoCfg->data2Lane.position)
        {
            enaLanes |= laneMode << pCmplxIoCfg->data2Lane.position;
        }
        if(0x0U != pCmplxIoCfg->data3Lane.position)
        {
            enaLanes |= laneMode << pCmplxIoCfg->data3Lane.position;
        }
        if(0x0U != pCmplxIoCfg->data4Lane.position)
        {
            enaLanes |= laneMode << pCmplxIoCfg->data4Lane.position;
        }
        reg |= enaLanes;
    }

    /* Enable DPHY Mode */
    reg |= CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_MASK &
           ((UInt32) CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_DPHY <<
                     CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_SHIFT);

    /* Enable CTRL CLK */
    reg |= CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_MASK &
           ((UInt32) CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_ENABLE <<
                      CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_SHIFT);

    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CONTROL_CAMERA_RX, reg);
}

/**************************Function Separator**********************************/

static void ConfigureStopStateTimeouts(uint32_t camRxCoreBaseAddr,
                                        uint32_t csi2Clk, uint32_t inst)
{
    volatile uint32_t reg;
    uint32_t thsTerm, thsSettle, tclkTerm, tclkSettle;
    Float32  ddrClkPeriod, temp;

    /* A. Setup the timings parameters in terms of DDR &
            PHY functional clock */
    reg  = HW_RD_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0);
    reg &= ~((UInt32) (CAL_CSI2_PHY_REG0_THS_TERM_MASK |
                       CAL_CSI2_PHY_REG0_THS_SETTLE_MASK));

    /* Effective time for enabling of termination = synchronizer delay
        + timer delay + LPRX delay + combinational routing delay
        THS_TERM = Floor (20/DDR Clock) */

    /* Get DDR clock period in nS */
    ddrClkPeriod = (Float32)((Float32)csi2Clk * (Float32)1000000U);
    ddrClkPeriod = (Float32)((Float32)1U / ddrClkPeriod);
    ddrClkPeriod = (Float32)(ddrClkPeriod * (Float32)1000000000U);
    GT_assert(VpsHalTrace, ((uint32_t)ddrClkPeriod > 0U));
    temp    = ((Float32)20U / ddrClkPeriod);
    thsTerm = (uint32_t)temp;

    /* Effective Ths-settle seen on line
        (starting to look for sync pattern) THS_SETTLE =
        synchronizer delay + timer delay + LPRX delay + combinational
        routing delay - pipeline delay in HS data path.
        (105 / DDR Clock) + 4
        */
    temp = (Float32)(((Float32)105 / ddrClkPeriod) + (Float32)4U);
    thsSettle = (uint32_t)temp;

    reg |= thsTerm << CAL_CSI2_PHY_REG0_THS_TERM_SHIFT;

    reg |= thsSettle << CAL_CSI2_PHY_REG0_THS_SETTLE_SHIFT;

    HW_WR_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG0, reg);

    reg  = HW_RD_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG1);
    reg &= ~(CAL_CSI2_PHY_REG1_TCLK_TERM_MASK |
             CAL_CSI2_PHY_REG1_TCLK_SETTLE_MASK);
    /* Requirement from D-PHY spec= (Dn Voltage < 450 mV) - 38 ns
        Effective time for enabling of termination (TCLK_TERM) =
            synchronizer delay + timer delay + LPRX delay +
                combinational routing delay
        TCLK_TERM = 23 / Functional clock period - 2
    */
    temp = (((Float32)23U / (Float32)DPHY_FUNCTIONAL_CLK_PERIOD) - (Float32)2U);
    tclkTerm = (uint32_t)temp;

    /* Derived requirement from D-PHY spec = 100 ns to 300ns.
        Effective Ths-settle = synchronizer delay + timer delay +
            LPRX delay + combinational routing delay

        Average of minimum delay + maximum delay / 2

        TCLK_SETTLE = floor(260/<Functional PHY Clock in nS>) - 2
    */
    temp = (((Float32)260U /
             (Float32)DPHY_FUNCTIONAL_CLK_PERIOD) - (Float32)2U);
    tclkSettle = (uint32_t)temp;

    reg |= CAL_CSI2_PHY_REG1_TCLK_TERM_MASK &
           (tclkTerm << CAL_CSI2_PHY_REG1_TCLK_TERM_SHIFT);

    reg |= CAL_CSI2_PHY_REG1_TCLK_SETTLE_MASK &
           (tclkSettle << CAL_CSI2_PHY_REG1_TCLK_SETTLE_SHIFT);

    HW_WR_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG1, reg);
}
