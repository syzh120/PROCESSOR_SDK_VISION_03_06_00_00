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
 *  TDA2EX_CAL_TODO i913 errata for CSI2 / CAL.
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
#include <ti/csl/cslr_cal.h>

#include <ti/drv/vps/include/iss/vps_cfgcal.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isscal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< Bit feilds definition for CTRL_CORE_CAMERRX_CONTROL reg */
#define CTRL_CORE_CAMERRX_CONTROL_CSI0_MODE_MASK                (0x00020000U)
#define CTRL_CORE_CAMERRX_CONTROL_CSI0_LANEENABLE_MASK          (0x0001E000U)
#define CTRL_CORE_CAMERRX_CONTROL_CSI0_CAMMODE_MASK             (0x00001800U)
#define CTRL_CORE_CAMERRX_CONTROL_CSI0_CTRLCLKEN_MASK           (0x00000400U)

#define CTRL_CORE_CAMERRX_CONTROL_CSI1_MODE_MASK                (0x00000020U)
#define CTRL_CORE_CAMERRX_CONTROL_CSI1_LANEENABLE_MASK          (0x00000018U)
#define CTRL_CORE_CAMERRX_CONTROL_CSI1_CAMMODE_MASK             (0x00000006U)
#define CTRL_CORE_CAMERRX_CONTROL_CSI1_CTRLCLKEN_MASK           (0x00000001U)

/**< Bit 2 set, used to compute register values for lanes enabled. */
#define CSI1_X_LANE_ENABLED                ((uint32_t)0x2U)
/**< Bit 12 set, used to compute register values for lanes enabled. */
#define CSI0_X_LANE_ENABLED                ((uint32_t)0x800U)


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
static void ConfigureLdoi913Errata(uint32_t camRxCoreBaseAddr);

/* ========================================================================== */
/*                          Function Implementations                          */
/* ========================================================================== */

int32_t VpsHal_calPhyEnClockAndReset(uint32_t            baseAddr,
                                     uint32_t            cam0RxCoreBaseAddr,
                                     uint32_t            cam1RxCoreBaseAddr,
                                     const isshalCalInstCfg_t *pCfg)
{
    int32_t                rtnVal;
    uint32_t               idx, rxCoreBaseAddr;
    volatile uint32_t      reg, timeOut;

    GT_assert(VpsHalTrace, (0U != baseAddr));
    GT_assert(VpsHalTrace, (0U != cam0RxCoreBaseAddr));
    GT_assert(VpsHalTrace, (0U != cam1RxCoreBaseAddr));
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
    for(idx = 0U; idx < pCfg->numCmplxIoInst; idx++)
    {
        if (TRUE == pCfg->cmplxIoCfg[idx].enable)
        {
            /* 1. Configure D-PHY mode and enable required lanes */
            ConfigureCamRxCtrl((const vpsissCalCmplxIoCfg_t *)
                                &pCfg->cmplxIoCfg[idx], idx);
            rxCoreBaseAddr = cam0RxCoreBaseAddr;
            if (idx > 0U)
            {
                rxCoreBaseAddr = cam1RxCoreBaseAddr;
                if (idx >= CSL_CAL_CMPLXIO_CNT)
                {
                    GT_assert(VpsHalTrace, ((uint32_t)FALSE));
                }
            }

/* C & C++ INVARIANT_CONDITION.GEN
 * Expression 'FVID2_SOK == rtnVal' used in the condition always yields the
 * same result.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * In cases where value in the if condition  is dependent on the return of a
 * function and currently the function is hardcoded to return a value. Code is
 * currently unreachable but as the implementation of the function changes, it
 * will not be unreachable.
 */
            if((FVID2_SOK == rtnVal) && (0U != rxCoreBaseAddr))
            {
                /* 2. Reset complex IO - Do not wait for reset completion */
                reg = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                reg |= CAL_CSI2_COMPLEXIO_CFG_RESET_CTRL_MASK;
                HW_WR_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx), reg);
                /* Dummy read to allow SCP to complete */
                reg     = HW_RD_REG32(baseAddr + CAL_CSI2_COMPLEXIO_CFG(idx));
                timeOut = 0xFFFFFU;

                /* Timeouts */
                ConfigureStopStateTimeouts(rxCoreBaseAddr,
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
                ConfigureLdoi913Errata(rxCoreBaseAddr);
            }
        }
    }

    return rtnVal;
}


/**************************Function Separator**********************************/

static void ConfigureCamRxCtrl(const vpsissCalCmplxIoCfg_t *pCmplxIoCfg,
                                uint32_t inst)
{
    volatile uint32_t reg, enabledLanes;
    uint32_t modeMask, camModeMask, ctrlClkEnMask, laneEnMask;
    uint32_t laneEn;

    modeMask =  CTRL_CORE_CAMERRX_CONTROL_CSI0_MODE_MASK;
    laneEnMask = CTRL_CORE_CAMERRX_CONTROL_CSI0_LANEENABLE_MASK;
    camModeMask = CTRL_CORE_CAMERRX_CONTROL_CSI0_CAMMODE_MASK;
    ctrlClkEnMask = CTRL_CORE_CAMERRX_CONTROL_CSI0_CTRLCLKEN_MASK;
    laneEn = CSI0_X_LANE_ENABLED;

    if (1U == inst)
    {
        modeMask =  CTRL_CORE_CAMERRX_CONTROL_CSI1_MODE_MASK;
        laneEnMask = CTRL_CORE_CAMERRX_CONTROL_CSI1_LANEENABLE_MASK;
        camModeMask = CTRL_CORE_CAMERRX_CONTROL_CSI1_CAMMODE_MASK;
        ctrlClkEnMask = CTRL_CORE_CAMERRX_CONTROL_CSI1_CTRLCLKEN_MASK;
        laneEn = CSI1_X_LANE_ENABLED;
    }

    reg = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                      CTRL_CORE_CAMERRX_CONTROL);
    reg &= ~((UInt32) (modeMask | laneEnMask | camModeMask | ctrlClkEnMask));

    /* Enable mode */
    reg |= modeMask;

    /* Enable Required lanes */
    enabledLanes = 0x0;
    if((uint32_t)TRUE == pCmplxIoCfg->enable)
    {
        /* All lane modules requires to be enabled, when operting with 1, 2
            3 lane mode */

        /* Clock lane is fixed at position 1 */
        enabledLanes = (enabledLanes | (laneEn << 2U));
        enabledLanes = (enabledLanes | (laneEn << 3U));

        /* Second PHY has only 2 lanes */
        if (0U == inst)
        {
            enabledLanes = (enabledLanes | (laneEn << 4U));
            enabledLanes = (enabledLanes | (laneEn << 5U));
        }

        reg |= (laneEnMask & enabledLanes);
    }

    /* Enable DPHY Mode */
    reg &= ~camModeMask;

    /* Enable CTRL CLK */
    reg |= ctrlClkEnMask;

    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_PAD_REGISTERS_BASE +
                CTRL_CORE_CAMERRX_CONTROL, reg);
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

static void ConfigureLdoi913Errata(uint32_t camRxCoreBaseAddr)
{
    /* Extracts from the errata
        i913 CSI2 LDO Needs to Be Disabled when Module Is Powered On.
        CRITICALITY: High
        DESCRIPTION: Enabling CSI2 LDO shorts it to core supply. It is crucial
                        the 2 CSI2 LDOs on the device are disabled if CSI-2
                        module is powered on
                        ((0x4845 B304 | 0x4845 B384) [28:27] = 0x1)
                        or in ULPS (0x4845 B304 | 0x4845 B384 [28:27] = 0x2).
        Common concerns include: high current draw on the module supply in
                                    active mode.
        Errata does not apply when CSI-2 module is powered off
                ((0x4845 B304 | 0x4845 B384)[28:27] = 0x0).
        WORKAROUND
        NOTE: DRA71x CSI2 interface do not support CSI2_PHY2.
        CSI-2 module enabled:
        Set the following register bits to disable the LDO:
        • For CSI2_PHY1: Set bit 6 of 0x4845 B828
        • For CSI2_PHY2: Set bit 6 of 0x4845 B928
    */
    volatile uint32_t reg;

    reg = HW_RD_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG10);

    reg = (uint32_t)(reg & ~(uint32_t)CAL_CSI2_PHY_REG10_LDO_DISABLE_MASK);

    HW_WR_REG32(camRxCoreBaseAddr + CAL_CSI2_PHY_REG10, reg);
}
