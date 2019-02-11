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
 *  \file vpshal_iss.c
 *
 *  \brief This file implements generic functions for ISS block.
 *
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
#include <ti/drv/vps/src/vpslib/common/vps_common.h>

#include <ti/csl/cslr_iss.h>
#include <ti/csl/hw_types.h>

#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>

#include <ti/drv/vps/src/vpslib/hal/vpshal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_iss.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_isscal.h>
#include <ti/drv/vps/src/vpslib/hal/vpshal_platform.h>

#include <ti/csl/soc.h>


/* ========================================================================== */
/*                           Constants                                        */
/* ========================================================================== */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct isshalIssCtrlPrms
 *  \brief ISS common / control configurations.
 */
typedef struct isshalIssCtrlPrms
{
    uint32_t               isInitDone;
    /**< Flag to indicate whether init is done or not */
    uint32_t               issBaseAddr;
    /**< Register base address */
    uint32_t               ispSys1BaseAddr;
    /**< ISP SYS1 baseaddress */
    uint32_t               ispSys2BaseAddr;
    /**< ISP SYS2 baseaddress */
    uint32_t               ispSys3BaseAddr;
    /**< ISP SYS3 baseaddress */
    uint32_t               vmuxMode;
    /**< 0x0, in legacy mode. Explicit control otherwise. */
    VpsHal_issUtilMemCpy_t issMemcpy;
    /**< Apps supplied mem copy function. */
} isshalIssCtrlPrms_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#if defined (VPS_CAL_BUILD)

#if defined (SOC_TDA3XX)
static isshalCalInstParams_t      gIssHalCalInstParams
[CSL_CAL_PER_CNT] =
{{0, ISS_CALA_BASE_REGISTER, ISS_CALA_CAMERARX_CORE_0_BASE_REGISTER, NULL, NULL}
    ,
 {1, ISS_CALB_BASE_REGISTER, NULL, NULL}}; /* CAL B */
#endif

#if defined (SOC_TDA2PX)
static isshalCalInstParams_t      gIssHalCalInstParams
[CSL_CAL_PER_CNT] =
{{0, ISS_CALA_BASE_REGISTER,
    ISS_CALA_CAMERARX_CORE_0_BASE_REGISTER,
    ISS_CALA_CAMERARX_CORE_1_BASE_REGISTER, NULL} /* CAL A (Seperate CAL instance present for capture. */
    ,
 {1, ISS_CALB_BASE_REGISTER, NULL, NULL},/* CAL B (It is CAL A instance of ISS used in m2m mode for ISP)*/
 {2, ISS_CALC_BASE_REGISTER, NULL, NULL}};/* CAL C (It is CAL A instance of ISS used in m2m mode for Format conversion) */
#endif

#if defined (SOC_TDA2EX) || defined (SOC_AM571x)
static isshalCalInstParams_t gIssHalCalInstParams [CSL_CAL_PER_CNT] = {{0,
                                ISS_CALA_BASE_REGISTER,
                                ISS_CALA_CAMERARX_CORE_0_BASE_REGISTER,
                                ISS_CALA_CAMERARX_CORE_1_BASE_REGISTER, NULL}};
#endif

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalCalPlatformData' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer to structure is accessed in the hal, not direct access of
 * this variable.
 */

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalCalPlatformData' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer to structure is accessed in the hal, not direct access of
 * this variable.
 */
/* CAUTION - Since PHY is not connected to CAL B, Set the count to max - 1.
   Essentially initializing CAL A only */
#if defined (VPS_ISS_BUILD)
static vpshalissCalPlatformData_t gIssHalCalPlatformData =
{(CSL_CAL_PER_CNT), NULL, NULL,
  CSL_ISS_LVDSRX_PER_CNT, NULL};
#else
static vpshalissCalPlatformData_t gIssHalCalPlatformData =
{(CSL_CAL_PER_CNT), NULL};
#endif

#endif

#if defined (VPS_ISS_BUILD)

/**< Place holder to define the VMUX ports */
static uint32_t gVmuxValidMap[SRC_PORT_MAX];

/**
 *  isshalIssCtrlPrms_t gIssHalIssCtrlCfg
 *  \brief Pool of VMUX objects.
 */
static isshalIssCtrlPrms_t        gIssHalIssCtrlCfg = {(uint32_t)FALSE};

static isshallvdsrxInstParams_t   gIssHalLvdsRxInstParams
[CSL_ISS_LVDSRX_PER_CNT] =
{
    {ISSHAL_LVDSRX_INST_0, ISS_LVDSRX_BASE_REGISTER, 1U, 4U}
};

static isshalIssCtrlInitParams_t  gIssCtrlInitParam =
{ISS_TOP_BASE_REGISTER,
 ISS_ISP_SYS1_BASE_REGISTER,
 ISS_ISP_SYS2_BASE_REGISTER,
 ISS_ISP_SYS3_BASE_REGISTER,1U,  NULL,
 NULL};

static vpshalissIspPlatformData_t gIssHalIspPlatformData =
{
    /* CAL */
    NULL,
    CSL_CAL_PER_CNT,
    /* IPIPEIF */
    {ISSHAL_IPIPEIF_INST_0,        ISS_ISP_IPIPEIF_BASE_REGISTER,
     {ISS_ISP_IPIPEIF_LUT0_ADDR},  ISS_ISP_IPIPEIF_LUT0_SIZE,
     {ISS_ISP_IPIPEIF_LUT1_ADDR},  ISS_ISP_IPIPEIF_LUT1_SIZE,
     {ISS_ISP_IPIPEIF_LUT2_ADDR},  ISS_ISP_IPIPEIF_LUT2_SIZE,
     NULL},
    CSL_ISS_IPIPEIF_PER_CNT,
    /* IPIPE*/
    {ISSHAL_IPIPE_INST_0,          ISS_ISP_IPIPE_BASE_REGISTER,
     ISS_ISP_IPIPE_GAMMA_R_ADDR,   ISS_ISP_IPIPE_GAMMA_G_ADDR,
     ISS_ISP_IPIPE_GAMMA_B_ADDR,
     ISS_ISP_IPIPE_3DLUT_MEM0_ADDR,ISS_ISP_IPIPE_3DLUT_MEM1_ADDR,
     ISS_ISP_IPIPE_3DLUT_MEM2_ADDR,ISS_ISP_IPIPE_3DLUT_MEM3_ADDR,
     ISS_ISP_IPIPE_YEE_TABLE_ADDR, ISS_ISP_IPIPE_YEE_TABLE_SIZE},
    CSL_ISS_IPIPE_PER_CNT,
    /* ISIF */
    {ISSHAL_ISIF_INST_0,           ISS_ISP_ISIF_BASE_REGISTER},
    CSL_ISS_ISIF_PER_CNT,
    /* NSF3 */
    {
        {ISSHAL_NSF3_INST_0,       ISS_ISP_NSF3_INST0_BASE_REGISTER,
         ISSHAL_ISS_MODULE_NSF3},
        {ISSHAL_NSF3_INST_1,       ISS_ISP_NSF3_INST1_BASE_REGISTER,
         ISSHAL_ISS_MODULE_CNFA}
    },
    CSL_ISS_NSF3_PER_CNT,
    /* RSZ */
    {ISSHAL_RSZ_INST_0,            ISS_ISP_RSZ_BASE_REGISTER},
    CSL_ISS_RSZ_PER_CNT,
    /* H3A */
    {ISSHAL_H3A_INST_0,            ISS_ISP_H3A_BASE_REGISTER},
    CSL_ISS_H3A_PER_CNT,
    /* GLBCE */
    {ISSHAL_GLBCE_INST_0, ISS_ISP_GLBCE_BASE_REGISTER,
     ISS_ISP_GLBCE_STATS_MEM_ADDR, ISS_ISP_GLBCE_STATS_MEM_SIZE},
    CSL_ISS_GLBCE_PER_CNT,
    /* ISS_TOP */
    NULL
};
#endif

#if defined(VPS_ISS_ISP_DEF)
/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gIssHalCalPlatformData' visibility is too wide.
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * Pointer to structure is accessed in the hal, not direct access of
 * this variable.
 */
static issemInitParams_t    gIssHalCommonPlatformData =
{
    1U,
    {IEM_INST_ID_IRQ0,          IEM_INST_ID_IRQ1,
     IEM_INST_ID_IRQ2,          IEM_INST_ID_IRQ3,
     IEM_INST_ID_IRQ4,          IEM_INST_ID_IRQ5},
    {CSL_ISS_IRQ0_NUM,          CSL_ISS_IRQ1_NUM,
     CSL_ISS_IRQ2_NUM,          CSL_ISS_IRQ3_NUM,
     CSL_ISS_IRQ4_NUM,          CSL_ISS_IRQ5_NUM},
    IEM_MODULE_ISS_MAX,
    {
    #if defined (SOC_TDA2PX)
        ISS_CALC_BASE_REGISTER,
    #else
        ISS_CALA_BASE_REGISTER,
    #endif
     ISS_TOP_BASE_REGISTER,
     ISS_ISP_SYS1_BASE_REGISTER,
     ISS_ISP_SYS2_BASE_REGISTER,ISS_ISP_SYS3_BASE_REGISTER,
     ISS_SIMCOP_BASE_REGISTER,  ISS_LVDSRX_BASE_REGISTER,
     ISS_CALB_BASE_REGISTER}
};
#endif


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

#if defined (VPS_ISS_BUILD)
int32_t VpsHal_issctrlInit(const isshalIssCtrlInitParams_t *initPrms, Ptr arg)
{
    volatile uint32_t regVal, clkStat, tempCounter;
    uint32_t          cnt;
    int32_t           status = BSP_SOK;

    /* Arguments check */
    GT_assert(VpsHalTrace, (NULL != initPrms));

    if((uint32_t)FALSE == gIssHalIssCtrlCfg.isInitDone)
    {
        gIssHalIssCtrlCfg.issBaseAddr     = initPrms->issBaseAddress;
        gIssHalIssCtrlCfg.ispSys1BaseAddr = initPrms->ispSys1BaseAddress;
        gIssHalIssCtrlCfg.ispSys2BaseAddr = initPrms->ispSys2BaseAddress;
        gIssHalIssCtrlCfg.ispSys3BaseAddr = initPrms->ispSys3BaseAddress;
        gIssHalIssCtrlCfg.vmuxMode        = initPrms->vmuxMod;
        gIssHalIssCtrlCfg.issMemcpy       = initPrms->utilsMemCpy;

        /* Set up common control / config
         * . Perform soft reset
         * . Gate all clocks to ISP at video mux
         * . Clear the FIFO in Video Mux
         * . Configure Video mux mode
         * .
         */
        /* Soft reset */
#ifdef NOT_YET
        tempCounter = 0xFFFF;
        regVal      = HW_RD_REG32(
            gIssHalIssCtrlCfg.issBaseAddr + ISS_HL_SYSCONFIG);
        regVal |= ISS_HL_SYSCONFIG_SOFTRESET_MASK;
        regVal &= ~ISS_HL_SYSCONFIG_STANDBYMODE_MASK;
        regVal |=
            (ISS_HL_SYSCONFIG_STANDBYMODE_NO <<
             ISS_HL_SYSCONFIG_STANDBYMODE_SHIFT);
        HWREG(gIssHalIssCtrlCfg.issBaseAddr + ISS_HL_SYSCONFIG) = regVal;
        while((0x0 != tempCounter) &&
              (ISS_HL_SYSCONFIG_SOFTRESET_MASK ==
               (regVal & ISS_HL_SYSCONFIG_SOFTRESET_MASK)))
        {
            regVal = HW_RD_REG32(
                gIssHalIssCtrlCfg.issBaseAddr + ISS_HL_SYSCONFIG);
            tempCounter--;
        }
        GT_assert(VpsHalTrace, (0 < tempCounter));

        /* Gate all clocks to ISP at video mux */
        regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKSTAT);
        clkStat = (ISS_CLKCTRL_SIMCOP_MASK | ISS_CLKCTRL_ISP_MASK |
                   ISS_CLKCTRL_BYS_A_MASK | ISS_CLKCTRL_BYS_B_MASK |
                   ISS_CLKCTRL_CAL_A_MASK | ISS_CLKCTRL_CAL_B_MASK |
                   ISS_CLKCTRL_CAL_A_BYS_OUT_PCLK_MASK |
                   ISS_CLKCTRL_CAL_B_BYS_OUT_PCLK_MASK |
                   ISS_CLKCTRL_CAL_A_OUT_PCLK_MASK |
                   ISS_CLKCTRL_CAL_B_OUT_PCLK_MASK |
                   ISS_CLKCTRL_BYS_A_OUT_PCLK_MASK |
                   ISS_CLKCTRL_BYS_B_OUT_PCLK_MASK |
                   ISS_CLKCTRL_LVDSRX_MASK | ISS_CLKCTRL_CTSET_MASK |
                   ISS_CLKCTRL_PARALLEL_A_PCLK_MASK |
                   ISS_CLKCTRL_NSF3V_OUT_PCLK_MASK |
                   ISS_CLKCTRL_GLBCE_OUT_PCLK_MASK |
                   ISS_CLKCTRL_LVDSRX_OUT0_PCLK_MASK |
                   ISS_CLKCTRL_LVDSRX_OUT1_PCLK_MASK |
                   ISS_CLKCTRL_LVDSRX_OUT2_PCLK_MASK |
                   ISS_CLKCTRL_LVDSRX_OUT3_PCLK_MASK);

        /* Somehow PARALLEL_A_CLK and CCP2_PCLK is not getting reset */
        clkStat &=
            ~(ISS_CLKCTRL_CCP2_PCLK_MASK|ISS_CLKCTRL_PARALLEL_A_PCLK_MASK);

        regVal &= ~clkStat;
        HWREG(gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKCTRL) = regVal;

        /* Ensure its indeed gated - TODO check if CPU based sleep is required.
        **/
        BspOsal_sleep(1);
        regVal = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKSTAT);

        GT_assert(VpsHalTrace, (0 == (regVal & clkStat)));
#endif

        /* Enable ISP */
        VpsHal_issPowerCtrl(SUB_MODULE_ISP, (uint32_t)TRUE);

        /* Reset ISP */
        regVal = HW_RD_REG32(
            gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_SYSCONFIG);
        regVal |= ISP5_SYSCONFIG_SOFTRESET_MASK;
        HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_SYSCONFIG, regVal);
        tempCounter = 0xFFFFU;
        while(0U < tempCounter)
        {
            regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr +
                                 ISP5_SYSCONFIG);

            if(ISP5_SYSCONFIG_SOFTRESET_DONE == (regVal &
                                                 ISP5_SYSCONFIG_SOFTRESET_MASK))
            {
                break;
            }
            tempCounter--;
        }
        if(0x0U == tempCounter)
        {
            status = BSP_EFAIL;
        }
        /* Somehow PSYNC_CLK requires to be enabled on zebu,
           TODO: Check why input pclk is more 213MHZ on zebu */
        regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL);
        regVal |= 0x100U;
        /* Remove Standby mode */
        regVal &= ~((uint32_t)1U << (uint32_t)24U);
        HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL, regVal);

        /* Enabling all modules */
        for(cnt = 0U; cnt < ISSHAL_ISS_MODULE_SYNC; cnt++)
        {
            VpsHal_issEnableModule((isshalIssModuleId_t) cnt, (uint32_t)TRUE);
        }

        regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CTRL);
        regVal  = (uint32_t)regVal & ~(uint32_t)ISS_CTRL_INPUT_SEL_MASK;
        regVal |= ((UInt32) ISS_CTRL_INPUT_SEL_PAR << ISS_CTRL_INPUT_SEL_SHIFT);
        HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CTRL, regVal);

        /* Set up Video Mux mode */
        regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CTRL1);
        regVal |= ISS_CTRL1_ENABLE_VMUX_MASK;
        if(0x0U == gIssHalIssCtrlCfg.vmuxMode)
        {
            regVal &= ~((UInt32) ISS_CTRL1_ENABLE_VMUX_MASK);
        }
        HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CTRL1, regVal);

        /* Hard coding the map, will later be used in set path */
        BspUtils_memset(&gVmuxValidMap[0U], 0U, sizeof(gVmuxValidMap));
        gVmuxValidMap[SRC_PORT_CAL_A_BYS_OUT] = SINK_PORT_NSFV3_IN |
                                                SINK_PORT_GLBCE_IN;
        gVmuxValidMap[SRC_PORT_CAL_A_VP]      = SINK_PORT_ISP_IN;
        gVmuxValidMap[SRC_PORT_CAL_B_BYS_OUT] = SINK_PORT_NSFV3_IN |
                                                SINK_PORT_GLBCE_IN;
        gVmuxValidMap[SRC_PORT_CAL_B_VP]   = SINK_PORT_ISP_IN;
        gVmuxValidMap[SRC_PORT_PARALLEL_A] = SINK_PORT_ISP_IN;
        gVmuxValidMap[SRC_PORT_NSF3V_OUT]  = SINK_PORT_CAL_A_BYS_IN |
                                             SINK_PORT_CAL_B_BYS_IN;
        gVmuxValidMap[SRC_PORT_GLBCE_OUT] = SINK_PORT_CAL_A_BYS_IN |
                                            SINK_PORT_CAL_B_BYS_IN;
        gVmuxValidMap[SRC_PORT_LVDSRX_OUT_0] = SINK_PORT_ISP_IN |
                                               SINK_PORT_CAL_A_BYS_IN |
                                               SINK_PORT_CAL_B_BYS_IN;
        gVmuxValidMap[SRC_PORT_LVDSRX_OUT_3] = SINK_PORT_ISP_IN |
                                               SINK_PORT_CAL_A_BYS_IN |
                                               SINK_PORT_CAL_B_BYS_IN;

        gIssHalIssCtrlCfg.isInitDone = (uint32_t)TRUE;
    }

    return (status);
}

/* Function Separator */

int32_t VpsHal_issctrlDeInit(Ptr arg)
{
    BspUtils_memset(&gVmuxValidMap[0U], 0U, sizeof(gVmuxValidMap));
    gIssHalIssCtrlCfg.isInitDone = (uint32_t)FALSE;
    return (BSP_SOK);
}

/* Function Separator */

int32_t VpsHal_issispInit(const isshalIspInitParams_t *initPrms)
{
    return (BSP_SOK);
}

/* Function Separator */

int32_t VpsHal_issispDeInit(void)
{
    return (BSP_SOK);
}

/* Function Separator */

/* Function Separator */

/* Function Separator */
int32_t VpsHal_issvmuxClkCtrl(isshalVMuxSrcPorts_t  srcPort,
                              isshalVMuxSinkPorts_t sinkPort,
                              uint32_t              flags)
{
    uint32_t          useIssClkCtrl = (uint32_t)FALSE;
    int32_t           rtnValue      = BSP_EBADARGS;
    volatile uint32_t issClkCtrl, issClkCtrlMask;

    if((0U < srcPort) && (SRC_PORT_MAX > srcPort))
    {
        /* Valid sink, check if source can routed to this sink */
        if(0x0U != (gVmuxValidMap[srcPort] & sinkPort))
        {
            rtnValue = BSP_SOK;
        }
    }

    if(BSP_SOK == rtnValue)
    {
        /* TODO: Reading from CLKSTAT register as CLKCTRL bits are not
         *       readable in simulator */
        issClkCtrl = HW_RD_REG32(
            gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKSTAT);
        issClkCtrlMask = 0x0U;
        switch(srcPort)
        {
            case SRC_PORT_CAL_A_BYS_OUT:
                issClkCtrlMask |= ISS_CLKCTRL_CAL_A_BYS_OUT_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_CAL_A_VP:
                issClkCtrlMask |= ISS_CLKCTRL_CAL_A_OUT_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_CAL_B_BYS_OUT:
                issClkCtrlMask |= ISS_CLKCTRL_CAL_B_BYS_OUT_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_CAL_B_VP:
                issClkCtrlMask |= ISS_CLKCTRL_CAL_B_OUT_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_PARALLEL_A:
                issClkCtrlMask |= ISS_CLKCTRL_PARALLEL_A_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_NSF3V_OUT:
                issClkCtrlMask |= ISS_CLKCTRL_NSF3V_OUT_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_GLBCE_OUT:
                issClkCtrlMask |= ISS_CLKCTRL_GLBCE_OUT_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_LVDSRX_OUT_0:
                issClkCtrlMask |= ISS_CLKCTRL_LVDSRX_OUT0_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            case SRC_PORT_LVDSRX_OUT_3:
                issClkCtrlMask |= ISS_CLKCTRL_LVDSRX_OUT3_PCLK_MASK;
                useIssClkCtrl   = (uint32_t)TRUE;
                break;

            default:
                rtnValue = BSP_EBADARGS;
                break;
        }

        switch(sinkPort)
        {
            case SINK_PORT_ISP_IN:
                /* TODO */
                break;

            case SINK_PORT_NSFV3_IN:
                /* TODO */
                break;

            case SINK_PORT_GLBCE_IN:
                /* TODO */
                break;

            case SINK_PORT_CAL_A_BYS_IN:
                /* TODO */
                break;

            case SINK_PORT_CAL_B_BYS_IN:
                /* TODO */
                break;

            default:
                rtnValue = BSP_EBADARGS;
                break;
        }

        if((uint32_t)TRUE == useIssClkCtrl)
        {
            if((uint32_t)TRUE == flags)
            {
                issClkCtrl |= issClkCtrlMask;
            }
            else
            {
                issClkCtrl &= ~issClkCtrlMask;
            }
            HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKCTRL,
                        issClkCtrl);
            BspOsal_sleep(1U); /* TODO check if CPU based sleep is required. */
        }
    }
    return (rtnValue);
}

/* Function Separator */

int32_t VpsHal_issvmuxSetPath(isshalVMuxSrcPorts_t  srcPort,
                              isshalVMuxSinkPorts_t sinkPort,
                              uint32_t              isEnable)
{
    int32_t           rtnValue = BSP_EBADARGS;
    volatile uint32_t regVal;
    /*  1. Ensure the path is valid
     *  2. Check if the clock sources is gated the sink/source clocks at
     *      VMUX level
     *  3. Map, reset FIFO before map
     */
    if((0U < srcPort) && (SRC_PORT_MAX > srcPort))
    {
        /* Valid sink, check if source can routed to this sink */
        if(0x0U != (gVmuxValidMap[srcPort] & sinkPort))
        {
            rtnValue = BSP_SOK;
        }
    }

    if(BSP_SOK == rtnValue)
    {
        regVal = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_VMUX);
        /* A source could feed into multiple sinks */
        switch(srcPort)
        {
            case SRC_PORT_CAL_A_BYS_OUT:
                if((sinkPort & SINK_PORT_NSFV3_IN) == SINK_PORT_NSFV3_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_NSF3V_IN_MASK);
                    if(TRUE == isEnable)
                    {
                        regVal |= ((UInt32) ISS_VMUX_NSF3V_IN_CAL_A_BYS_OUT <<
                                            ISS_VMUX_NSF3V_IN_SHIFT);
                    }
                }
                else
                {
                    regVal &= ~((UInt32) ISS_VMUX_GLBCE_IN_MASK);
                    if(TRUE == isEnable)
                    {
                        regVal |= ((UInt32) ISS_VMUX_GLBCE_IN_CAL_A_BYS_OUT <<
                                            ISS_VMUX_GLBCE_IN_SHIFT);
                    }
                }
                break;
            case SRC_PORT_CAL_A_VP:
                regVal &= ~((UInt32) ISS_VMUX_ISP_IN_MASK);
                if(TRUE == isEnable)
                {
                    regVal |= ((UInt32) ISS_VMUX_ISP_IN_CAL_A_OUT <<
                                        ISS_VMUX_ISP_IN_SHIFT);
                }
                break;
            case SRC_PORT_CAL_B_BYS_OUT:
                if((sinkPort & SINK_PORT_NSFV3_IN) == SINK_PORT_NSFV3_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_NSF3V_IN_MASK);
                    if(TRUE == isEnable)
                    {
                        regVal |= ((UInt32) ISS_VMUX_NSF3V_IN_CAL_B_BYS_OUT <<
                                            ISS_VMUX_NSF3V_IN_SHIFT);
                    }
                }
                else
                {
                    regVal &= ~((UInt32) ISS_VMUX_GLBCE_IN_MASK);
                    if(TRUE == isEnable)
                    {
                        regVal |= ((UInt32) ISS_VMUX_GLBCE_IN_CAL_B_BYS_OUT <<
                                            ISS_VMUX_GLBCE_IN_SHIFT);
                    }
                }
                break;
            case SRC_PORT_CAL_B_VP:
                regVal &= ~((UInt32) ISS_VMUX_ISP_IN_MASK);
                if(TRUE == isEnable)
                {
                    regVal |= ((UInt32) ISS_VMUX_ISP_IN_CAL_B_OUT <<
                                        ISS_VMUX_ISP_IN_SHIFT);
                }
                break;
            case SRC_PORT_PARALLEL_A:
                regVal &= ~((UInt32) ISS_VMUX_ISP_IN_MASK);
                regVal |= ((UInt32) ISS_VMUX_ISP_IN_PARALLEL_A <<
                                    ISS_VMUX_ISP_IN_SHIFT);
                break;
            case SRC_PORT_NSF3V_OUT:
                if((sinkPort & SINK_PORT_CAL_A_BYS_IN) ==
                   SINK_PORT_CAL_A_BYS_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_A_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_A_BYS_IN_NSF3V_OUT <<
                                        ISS_VMUX_CAL_A_BYS_IN_SHIFT);
                }
                else
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_B_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_A_BYS_IN_GLBCE_OUT <<
                                        ISS_VMUX_CAL_B_BYS_IN_SHIFT);
                }
                break;
            case SRC_PORT_GLBCE_OUT:
                if((sinkPort & SINK_PORT_CAL_A_BYS_IN) ==
                   SINK_PORT_CAL_A_BYS_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_A_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_A_BYS_IN_GLBCE_OUT <<
                                        ISS_VMUX_CAL_A_BYS_IN_SHIFT);
                }
                else
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_B_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_B_BYS_IN_GLBCE_OUT <<
                                        ISS_VMUX_CAL_B_BYS_IN_SHIFT);
                }
                break;
            case SRC_PORT_LVDSRX_OUT_0:
                if((sinkPort & SINK_PORT_ISP_IN) == SINK_PORT_ISP_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_ISP_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_ISP_IN_LVDSRX_OUT0 <<
                                        ISS_VMUX_ISP_IN_SHIFT);
                }
                else if((sinkPort & SINK_PORT_CAL_A_BYS_IN) ==
                        SINK_PORT_CAL_A_BYS_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_A_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_A_BYS_IN_LVDSRX_OUT0 <<
                                        ISS_VMUX_GLBCE_IN_SHIFT);
                }
                else
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_B_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_B_BYS_IN_LVDSRX_OUT1 <<
                                        ISS_VMUX_GLBCE_IN_SHIFT);
                }
                break;
            case SRC_PORT_LVDSRX_OUT_3:
                if((sinkPort & SINK_PORT_ISP_IN) == SINK_PORT_ISP_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_ISP_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_ISP_IN_LVDSRX_OUT3 <<
                                        ISS_VMUX_CAL_A_BYS_IN_SHIFT);
                }
                else if((sinkPort & SINK_PORT_CAL_A_BYS_IN) ==
                        SINK_PORT_CAL_A_BYS_IN)
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_A_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_A_BYS_IN_LVDSRX_OUT3 <<
                                        ISS_VMUX_CAL_A_BYS_IN_SHIFT);
                }
                else
                {
                    regVal &= ~((UInt32) ISS_VMUX_CAL_B_BYS_IN_MASK);
                    regVal |= ((UInt32) ISS_VMUX_CAL_B_BYS_IN_LDVSRX_OUT3 <<
                                        ISS_VMUX_CAL_B_BYS_IN_SHIFT);
                }
                break;
            default:
                /* Why would this ever happen */
                rtnValue = BSP_EFAIL;
                break;
        }
        if(BSP_SOK == rtnValue)
        {
            HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_VMUX, regVal);
        }
    }

    return (rtnValue);
}

/* Function Separator */

int32_t VpsHal_issPowerCtrl(isshalSubModules_t module, uint32_t flags)
{
    int32_t           rtnValue = BSP_EBADARGS;
    volatile uint32_t modulesUnSigned;
    volatile uint32_t regVal = 0x0U, mask;

    modulesUnSigned = (uint32_t) module;
    mask = 0x0U;

    /* Power enable bits are write only bits, so read the status from
     * CLKSTAT register */
    regVal = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKSTAT);
    while(0x0U < modulesUnSigned)
    {
        if((modulesUnSigned & SUB_MODULE_LVDSRX) == SUB_MODULE_LVDSRX)
        {
            mask |= ISS_CLKCTRL_LVDSRX_MASK;
            modulesUnSigned &= ~((UInt32) SUB_MODULE_LVDSRX);
            rtnValue         = BSP_SOK;
        }
        else if((modulesUnSigned & SUB_MODULE_CAL_A) == SUB_MODULE_CAL_A)
        {
            mask |= ISS_CLKCTRL_CAL_A_MASK;
            modulesUnSigned &= ~((UInt32) SUB_MODULE_CAL_A);
            rtnValue         = BSP_SOK;
        }
        else if((modulesUnSigned & SUB_MODULE_BYS_A) == SUB_MODULE_BYS_A)
        {
            mask |= ISS_CLKCTRL_BYS_A_MASK;
            modulesUnSigned &= ~((UInt32) SUB_MODULE_BYS_A);
            rtnValue         = BSP_SOK;
        }
        else if((modulesUnSigned & SUB_MODULE_CAL_B) == SUB_MODULE_CAL_B)
        {
            mask |= ISS_CLKCTRL_CAL_B_MASK;
            modulesUnSigned &= ~((UInt32) SUB_MODULE_CAL_B);
            rtnValue         = BSP_SOK;
        }
        else if((modulesUnSigned & SUB_MODULE_BYS_B) == SUB_MODULE_BYS_B)
        {
            mask |= ISS_CLKCTRL_BYS_B_MASK;
            modulesUnSigned &= ~((UInt32) SUB_MODULE_BYS_B);
            rtnValue         = BSP_SOK;
        }
        else if((modulesUnSigned & SUB_MODULE_ISP) == SUB_MODULE_ISP)
        {
            mask |= ISS_CLKCTRL_ISP_MASK;
            modulesUnSigned &= ~((UInt32) SUB_MODULE_ISP);
            rtnValue         = BSP_SOK;
        }
        else if((modulesUnSigned & SUB_MODULE_SIMCOP) == SUB_MODULE_SIMCOP)
        {
            mask |= ISS_CLKCTRL_SIMCOP_MASK;
            modulesUnSigned &= ~((UInt32) SUB_MODULE_SIMCOP);
            rtnValue         = BSP_SOK;
        }
        else
        {
            if(BSP_SOK != rtnValue)
            {
                GT_assert(VpsHalTrace, (FALSE));
            }
        }
    }
    if(BSP_SOK == rtnValue)
    {
        if(TRUE == flags)
        {
            regVal |= mask;
        }
        else
        {
            regVal &= ~mask;
        }

        HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKCTRL, regVal);

        /* TODO - small delay required? */

        regVal = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_CLKSTAT);
        if(TRUE == flags)
        {
            uint32_t tempCheck = regVal & mask;
            if (tempCheck != mask)
            {
                GT_assert(VpsHalTrace, FALSE);
            }
        }
        /* TODO - ISP power down dosent seem to work. Will have to check this
            on the silicon */
        /* On Silicon also this is not working. The power down has an issue? */
#ifdef NOT_YET
        else
        {
            /* Just need to check if these bits are reset or not */
            GT_assert(VpsHalTrace, (0x0 == (regVal & mask)));
        }
#endif
    }

    return (rtnValue);
}

/* Enable/disble given module */
int32_t VpsHal_issEnableModule(
    isshalIssModuleId_t moduleId,
    uint32_t            enableFlag)
{
    int32_t           status = FVID2_SOK;
    uint32_t          mask;
    volatile uint32_t regVal;

    switch(moduleId)
    {
        case ISSHAL_ISS_MODULE_IPIPEIF:
            mask = ISP5_CTRL_IPIPEIF_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_IPIPE:
            mask = ISP5_CTRL_IPIPE_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_RSZ:
            mask = ISP5_CTRL_RSZ_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_H3A:
            mask = ISP5_CTRL_H3A_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_ISIF:
            mask = ISP5_CTRL_ISIF_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_BL:
            mask = ISP5_CTRL_BL_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_CNFA:
            mask = ISP5_CTRL_CNFA_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_CNFB:
            mask = ISP5_CTRL_CNFB_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_NSF3:
            mask = ISP5_CTRL_NSF3V_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_GLBCE:
            mask = ISP5_CTRL_GLBCE_CLK_ENABLE_MASK;
            break;
        case ISSHAL_ISS_MODULE_SYNC:
            mask = ISP5_CTRL_SYNC_ENABLE_MASK;
            break;
        default:
            status = FVID2_EINVALID_PARAMS;
            break;
    }

    if(FVID2_SOK == status)
    {
        regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL);
        if(TRUE == enableFlag)
        {
            regVal |= mask;
        }
        else
        {
            regVal &= ~mask;
        }
        HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL, regVal);
    }

    return (status);
}

void VpsHal_issEnableVdPulseExt(uint32_t enableFlag)
{
    volatile uint32_t regVal;

    regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL);
    if(TRUE == enableFlag)
    {
        regVal |= ISP5_CTRL_VD_PULSE_EXT_MASK;
    }
    else
    {
        regVal &= ~ISP5_CTRL_VD_PULSE_EXT_MASK;
    }
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL, regVal);
}

void VpsHal_issEnablePixClkInvert(uint32_t enableFlag)
{
    volatile uint32_t regVal;

    regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL);
    if(TRUE == enableFlag)
    {
        regVal |= ISP5_CTRL_PCLK_INV_MASK;
    }
    else
    {
        regVal &= ~ISP5_CTRL_PCLK_INV_MASK;
    }
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL, regVal);
}

void VpsHal_issEnablePostedWrite(uint32_t enableFlag)
{
    volatile uint32_t regVal;

    regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL);
    if(TRUE == enableFlag)
    {
        regVal |= ISP5_CTRL_OCP_WRNP_MASK;
    }
    else
    {
        regVal &= ~((UInt32) ISP5_CTRL_OCP_WRNP_MASK);
    }
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL, regVal);
}

void VpsHal_issSetVbusMPriority(isshalIssVBusMPriority_t prio)
{
    uint32_t regVal;

    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL);
    regVal &= ~((UInt32) ISP5_CTRL_VBUSM_CPRIORITY_MASK);
    regVal |= (((uint32_t) prio) << ISP5_CTRL_VBUSM_CPRIORITY_SHIFT) &
              ISP5_CTRL_VBUSM_CPRIORITY_MASK;
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_CTRL, regVal);
}

void VpsHal_issIspReset(void)
{
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_SYSCONFIG,
                HW_RD_REG32(
                    gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_SYSCONFIG) |
                ISP5_SYSCONFIG_SOFTRESET_MASK);
}

uint32_t VpsHal_issIspIsResetdone(void)
{
    uint32_t flag;

    if((HW_RD_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_SYSCONFIG) &
        ISP5_SYSCONFIG_SOFTRESET_MASK) == ISP5_SYSCONFIG_SOFTRESET_MASK)
    {
        flag = (uint32_t)FALSE;
    }
    else
    {
        flag = (uint32_t)TRUE;
    }

    return (flag);
}

void VpsHal_issSetModuleBwCtrl(isshalIssBwCtrlModule_t module, uint32_t bwCtrl)
{
    uint32_t regVal;

    switch(module)
    {
        case ISSHAL_ISS_BW_CTRL_MODULE_ISIF_READ:
            regVal = HW_RD_REG32(
                gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_BL_MTC_1);
            regVal &= ~ISP5_BL_MTC_1_ISIF_R_MASK;
            regVal |= (bwCtrl << ISP5_BL_MTC_1_ISIF_R_SHIFT) &
                      ISP5_BL_MTC_1_ISIF_R_MASK;
            HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_BL_MTC_1,
                        regVal);
            break;

        case ISSHAL_ISS_BW_CTRL_MODULE_IPIPEIF_READ:
            regVal = HW_RD_REG32(
                gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_BL_MTC_1);
            regVal &= ~((UInt32) ISP5_BL_MTC_1_IPIPEIF_R_MASK);
            regVal |= (bwCtrl << ISP5_BL_MTC_1_IPIPEIF_R_SHIFT) &
                      ISP5_BL_MTC_1_IPIPEIF_R_MASK;
            HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_BL_MTC_1,
                        regVal);
            break;

        case ISSHAL_ISS_BW_CTRL_MODULE_H3A_WRITE:
            regVal = HW_RD_REG32(
                gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_BL_MTC_2);
            regVal &= ~ISP5_BL_MTC_2_H3A_W_MASK;
            regVal |= (bwCtrl << ISP5_BL_MTC_2_H3A_W_SHIFT) &
                      ISP5_BL_MTC_2_H3A_W_MASK;
            HW_WR_REG32(gIssHalIssCtrlCfg.ispSys1BaseAddr + ISP5_BL_MTC_2,
                        regVal);
            break;
        default:
            break;
    }
}

int32_t VpsHal_issSetCnfConfig(const isshalissCnfConfig_t *cnfCfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regAddr;
    uint32_t regVal;

    /* Null Pointer Check */
    GT_assert(VpsHalTrace, (NULL != cnfCfg));

    /* Check for errors */
    if(TRUE == cnfCfg->enable)
    {
        if(TRUE == cnfCfg->enableCds)
        {
            if(0U != (cnfCfg->frameHeight % 2U))
            {
                status = FVID2_EINVALID_PARAMS;
            }
            if(0U != (cnfCfg->frameWidth % 4U))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
        else
        {
            if(0U != (cnfCfg->frameWidth % 2U))
            {
                status = FVID2_EINVALID_PARAMS;
            }
        }
    }

    if(FVID2_SOK == status)
    {
        if(ISSHAL_ISS_CNF_A == cnfCfg->instId)
        {
            regAddr = gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_CNFA_SIZ;
        }
        else
        {
            regAddr = gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_CNFB_SIZ;
        }

        regVal = (cnfCfg->frameWidth << ISP_CNFA_SIZ_WIDTH_SHIFT) &
                 ISP_CNFA_SIZ_WIDTH_MASK;
        regVal |= (cnfCfg->frameHeight << ISP_CNFA_SIZ_HEIGHT_SHIFT) &
                  ISP_CNFA_SIZ_HEIGHT_MASK;

        HW_WR_REG32(regAddr, regVal);

        regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_CNF_EN);
        if(ISSHAL_ISS_CNF_A == cnfCfg->instId)
        {
            regVal &= ~((UInt32) ISP_CNF_EN_CNFA_CDSEN_MASK);
            if(TRUE == cnfCfg->enableCds)
            {
                regVal |= ISP_CNF_EN_CNFA_CDSEN_MASK;
            }

            regVal &= ~((UInt32) ISP_CNF_EN_CNFA_MASK);
            if(TRUE == cnfCfg->enable)
            {
                regVal |= ISP_CNF_EN_CNFA_MASK;
            }
        }
        else
        {
            regVal &= ~((UInt32) ISP_CNF_EN_CNFB_CDSEN_MASK);
            if(TRUE == cnfCfg->enableCds)
            {
                regVal |= ISP_CNF_EN_CNFB_CDSEN_MASK;
            }

            regVal &= ~((UInt32) ISP_CNF_EN_CNFB_MASK);
            if(TRUE == cnfCfg->enable)
            {
                regVal |= ISP_CNF_EN_CNFB_MASK;
            }
        }
        HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_CNF_EN, regVal);
    }

    return (status);
}

void VpsHal_issSetGlbceSwitch(isshalGlbceSwitchModule_t module,
                              isshalGlbceSwitchCtrl_t   ctrl)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_SWT_SEL);

    if(ISSHAL_GLBCE_SWITCH_NSF3 == module)
    {
        regVal &= ~((UInt32) ISP_SWT_SEL_NSF3V_MASK);
        regVal |= (ctrl << ISP_SWT_SEL_NSF3V_SHIFT) &
                  ISP_SWT_SEL_NSF3V_MASK;
    }
    else /* GLBCE Module */
    {
        regVal &= ~((UInt32) ISP_SWT_SEL_GLBCE_MASK);
        regVal |= (ctrl << ISP_SWT_SEL_GLBCE_SHIFT) &
                  ISP_SWT_SEL_GLBCE_MASK;
    }

    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_SWT_SEL, regVal);
}

void VpsHal_issDpcBeforeNsf3(uint32_t enable)
{
    volatile uint32_t regVal;

    regVal = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_SWT_SEL);
    if(TRUE == enable)
    {
        regVal |=
            ISP_SWT_SEL_DPC_MASK;
    }
    else
    {
        regVal &=
            ~((UInt32) ISP_SWT_SEL_DPC_MASK);
    }
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_SWT_SEL, regVal);
}

int32_t VpsHal_issSetVp1Config(const isshalissVp1Config_t *cfg)
{
    int32_t  status = FVID2_SOK;
    uint32_t regVal;

    GT_assert(VpsHalTrace, (NULL != cfg));

    /* Select the processing Window */
    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_SPH);
    regVal &= ~((UInt32) ISP_VP1_SPH_MASK);
    regVal |= (cfg->cropWin.cropStartX << ISP_VP1_SPH_SHIFT) &
              ISP_VP1_SPH_MASK;
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_SPH, regVal);

    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_LNH);
    regVal &= ~((UInt32) ISP_VP1_LNH_MASK);
    regVal |= (((UInt32) (cfg->cropWin.cropWidth - 1U)) << ISP_VP1_LNH_SHIFT) &
              ISP_VP1_LNH_MASK;
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_LNH, regVal);

    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_SLV);
    regVal &= ~((UInt32) ISP_VP1_SLV_MASK);
    regVal |= (cfg->cropWin.cropStartY << ISP_VP1_SLV_SHIFT) &
              ISP_VP1_SLV_MASK;
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_SLV, regVal);

    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_LNV);
    regVal &= ~((UInt32) ISP_VP1_LNV_MASK);
    regVal |= (((UInt32) (cfg->cropWin.cropHeight - 1U)) << ISP_VP1_LNV_SHIFT) &
              ISP_VP1_LNV_MASK;
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_LNV, regVal);

    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_CCDCFG);
    regVal &= ~(ISP_VP1_CCDCFG_EE_MASK | ISP_VP1_CCDCFG_EO_MASK |
                ISP_VP1_CCDCFG_OE_MASK | ISP_VP1_CCDCFG_OO_MASK);

    if(FVID2_DF_BAYER_GRBG == cfg->bayerDataFormat)
    {
        regVal |= ISP_VP1_CCDCFG_EE_GR | ISP_VP1_CCDCFG_EO_R |
                  ISP_VP1_CCDCFG_OE_B | ISP_VP1_CCDCFG_OO_GB;
    }
    else if(FVID2_DF_BAYER_RGGB == cfg->bayerDataFormat)
    {
        regVal |= ISP_VP1_CCDCFG_EE_R | ISP_VP1_CCDCFG_EO_GR |
                  ISP_VP1_CCDCFG_OE_GB | ISP_VP1_CCDCFG_OO_B;
    }
    else if(FVID2_DF_BAYER_BGGR == cfg->bayerDataFormat)
    {
        regVal |= ISP_VP1_CCDCFG_EE_B | ISP_VP1_CCDCFG_EO_GB |
                  ISP_VP1_CCDCFG_OE_GR | ISP_VP1_CCDCFG_OO_R;
    }
    else /* FVID2_DF_BAYER_GBRG */
    {
        regVal |= ISP_VP1_CCDCFG_EE_GB | ISP_VP1_CCDCFG_EO_B |
                  ISP_VP1_CCDCFG_OE_R | ISP_VP1_CCDCFG_OO_GR;
    }

    regVal &= ~((UInt32) ISP_VP1_CCDCFG_YCINSWP_MASK);
    if(TRUE == cfg->enableYcSwap)
    {
        regVal |= ISP_VP1_CCDCFG_YCINSWP_MASK;
    }
    regVal &= ~((UInt32) ISP_VP1_CCDCFG_Y8POS_MASK);
    if(TRUE == cfg->enableLumaOddPos)
    {
        regVal |= ISP_VP1_CCDCFG_Y8POS_MASK;
    }
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_CCDCFG, regVal);

    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_DLAY);
    regVal &= ~((UInt32) ISP_VP1_DLAY_DELAY_SWT_MASK);
    if(TRUE == cfg->enableDelay)
    {
        regVal |= ISP_VP1_DLAY_DELAY_SWT_MASK;

        regVal &= ~((UInt32) ISP_VP1_DLAY_DLV_MASK);
        regVal |= (cfg->vertDelay << ISP_VP1_DLAY_DLV_SHIFT) &
                  ISP_VP1_DLAY_DLV_MASK;

        regVal &= ~((UInt32) ISP_VP1_DLAY_DLH_MASK);
        regVal |= (cfg->horzDelay << ISP_VP1_DLAY_DLH_SHIFT) &
                  ISP_VP1_DLAY_DLH_MASK;
    }
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP1_DLAY, regVal);

    regVal  = HW_RD_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_NSF3V_MODESET);
    regVal &= ~((UInt32) ISP_NSF3V_MODESET_INPMOD_MASK);
    regVal |= (((uint32_t) cfg->inpDataFormat) <<
               ISP_NSF3V_MODESET_INPMOD_SHIFT) &
              ISP_NSF3V_MODESET_INPMOD_MASK;

    regVal &= ~((UInt32) ISP_NSF3V_MODESET_DPOL_MASK);
    if(TRUE == cfg->isInvertData)
    {
        regVal |= ISP_NSF3V_MODESET_DPOL_MASK;
    }

    regVal &= ~((UInt32) ISP_NSF3V_MODESET_HDPOL_MASK);
    if(FVID2_POL_LOW == cfg->hdPol)
    {
        regVal |= ISP_NSF3V_MODESET_HDPOL_MASK;
    }

    regVal &= ~((UInt32) ISP_NSF3V_MODESET_VDPOL_MASK);
    if(FVID2_POL_LOW == cfg->vdPol)
    {
        regVal |= ISP_NSF3V_MODESET_VDPOL_MASK;
    }
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_NSF3V_MODESET, regVal);

    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_NSF3V_CGAMMAWD,
                (((uint32_t) cfg->inMsbPos) << ISP_NSF3V_CGAMMAWD_GWDI_SHIFT) &
                ISP_NSF3V_CGAMMAWD_GWDI_MASK);

    return (status);
}

int32_t VpsHal_issSetVp2Config(const isshalissVp2Config_t *cfg)
{
    int32_t status = FVID2_SOK;

    GT_assert(VpsHalTrace, (NULL != cfg));

    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP2_DLAY,
                ((cfg->horzDelay << ISP_VP2_DLAY_DLH_SHIFT) &
                 ISP_VP2_DLAY_DLH_MASK) |
                ((cfg->vertDelay << ISP_VP2_DLAY_DLV_SHIFT) &
                 ISP_VP2_DLAY_DLV_MASK));

    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP2_SPH,
                (cfg->pos.startX << ISP_VP2_SPH_SHIFT) & ISP_VP2_SPH_MASK);
    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_VP2_SLV,
                (cfg->pos.startY << ISP_VP2_SLV_SHIFT) & ISP_VP2_SLV_MASK);

    HW_WR_REG32(gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP_GLBCE_CGAMMAWD,
                ((((uint32_t) cfg->outMsbPos) <<
                  ISP_GLBCE_CGAMMAWD_GWDO_SHIFT) &
                 ISP_GLBCE_CGAMMAWD_GWDO_MASK) |
                ((((uint32_t) cfg->inMsbPos) <<
                  ISP_GLBCE_CGAMMAWD_GWDI_SHIFT) &
                 ISP_GLBCE_CGAMMAWD_GWDI_MASK));

    return (status);
}

int32_t VpsHal_issUtilMemCpy(uint32_t *dest[],
                             const uint32_t *src[], uint32_t byteCount[],
                             uint32_t numCpy)
{
    int32_t  rtnVal = FVID2_SOK;
    uint32_t cpyNum;

    if(NULL != gIssHalIssCtrlCfg.issMemcpy)
    {
        rtnVal = gIssHalIssCtrlCfg.issMemcpy(dest, src, byteCount, numCpy);
    }
    else
    {
        for(cpyNum = 0; ((cpyNum < numCpy) && (FVID2_SOK == rtnVal)); cpyNum++)
        {
            BspUtils_memcpy((Ptr) (dest[cpyNum]),
                            (const void *) (src[cpyNum]),
                            byteCount[cpyNum]);
        }
    }

    return (rtnVal);
}

int32_t VpsHal_issSetInitiatorPriority(vpsissL3Initiator_t  initiator,
                                       vpsissL3RoutingPri_t priority,
                                       uint32_t             cportId)
{
    int32_t           rtnVal = FVID2_EBADARGS;
    volatile uint32_t regVal;

    /* MISRA - No bitwise operations on signed integer */
    uint32_t          priUnSigned = (uint32_t)priority;

    GT_assert(VpsHalTrace, (NULL != gIssHalIssCtrlCfg.issBaseAddr));
    if((VPS_ISS_INIT_CAL_A_CPORT_X == initiator) ||
       (VPS_ISS_INIT_CAL_B_CPORT_X == initiator))
    {
        if(VPS_ISS_CAL_MAX_STREAMS > cportId)
        {
            rtnVal = FVID2_SOK;
            if((0x0U == cportId) &&
               (VPS_ISS_L3_ROUTING_OCPM1 == priority))
            {
                rtnVal = FVID2_WNON_RECOMMENDED_PARAMS;
            }
            if(VPS_ISS_INIT_CAL_A_CPORT_X == initiator)
            {
                regVal = HW_RD_REG32(
                    gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE1);
                regVal &= ~ISS_ROUTE1_CALA_MASK(cportId);
                regVal |= ISS_ROUTE1_CALA_MASK(cportId) &
                          (priUnSigned << ISS_ROUTE1_CALA_SHIFT(cportId));
                HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE1, regVal);
            }
            else
            {
                regVal = HW_RD_REG32(
                    gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE2);
                regVal &= ~ISS_ROUTE2_CALB_MASK(cportId);
                regVal |= ISS_ROUTE2_CALB_MASK(cportId) &
                          (priUnSigned << ISS_ROUTE2_CALB_SHIFT(cportId));
                HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE2, regVal);
            }
        }
    }
    else if((VPS_ISS_INIT_SIMCOP_DMA == initiator) ||
            (VPS_ISS_INIT_SIMCOP_LDC == initiator))
    {
        if(VPS_ISS_L3_ROUTING_OCPM1 != priority)
        {
            rtnVal = FVID2_SOK;
            regVal = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE3);
            if(VPS_ISS_INIT_SIMCOP_LDC == initiator)
            {
                regVal &= ~ISS_ROUTE3_LDC_MASK;
                regVal |= ISS_ROUTE3_LDC_MASK &
                          (priUnSigned << ISS_ROUTE3_LDC_SHIFT);
            }
            else
            {
                regVal &= ~ISS_ROUTE3_SDMA_MASK;
                regVal |= ISS_ROUTE3_SDMA_MASK &
                          (priUnSigned << ISS_ROUTE3_SDMA_SHIFT);
            }
            HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE3, regVal);
        }
    }
    else
    {
        /* ISP */
        rtnVal = FVID2_SOK;
        regVal = HW_RD_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE3);
        switch(initiator)
        {
            case VPS_ISS_INIT_IPIPEIF_RD:
                regVal &= ~((UInt32) ISS_ROUTE3_ISP_IPIPEIF_MASK);
                regVal |= ISS_ROUTE3_ISP_IPIPEIF_MASK &
                          (priUnSigned << ISS_ROUTE3_ISP_IPIPEIF_SHIFT);
                break;
            case VPS_ISS_INIT_ISIF_LSC_RD:
                regVal &= ~((UInt32) ISS_ROUTE3_ISP_LSC_MASK);
                regVal |= ISS_ROUTE3_ISP_LSC_MASK &
                          (priUnSigned << ISS_ROUTE3_ISP_LSC_SHIFT);
                break;
            case VPS_ISS_INIT_ISIF_WR:
                regVal &= ~((UInt32) ISS_ROUTE3_ISP_RAW_MASK);
                regVal |= ISS_ROUTE3_ISP_RAW_MASK &
                          (priUnSigned << ISS_ROUTE3_ISP_RAW_SHIFT);
                break;
            case VPS_ISS_INIT_IPIPE_BOXCAR:
                regVal &= ~((UInt32) ISS_ROUTE3_ISP_BOXCAR_MASK);
                regVal |= ISS_ROUTE3_ISP_BOXCAR_MASK &
                          (priUnSigned << ISS_ROUTE3_ISP_BOXCAR_SHIFT);
                break;
            case VPS_ISS_INIT_ISIF_H3A:
                regVal &= ~((UInt32) ISS_ROUTE3_ISP_H3A_MASK);
                regVal |= ISS_ROUTE3_ISP_H3A_MASK &
                          (priUnSigned << ISS_ROUTE3_ISP_H3A_SHIFT);
                break;
            case VPS_ISS_INIT_RSZ_A:
                regVal &= ~((UInt32) ISS_ROUTE3_ISP_RSZA_MASK);
                regVal |= ISS_ROUTE3_ISP_RSZA_MASK &
                          (priUnSigned << ISS_ROUTE3_ISP_RSZA_SHIFT);
                break;
            case VPS_ISS_INIT_RSZ_B:
                regVal &= ~((UInt32) ISS_ROUTE3_ISP_RSZB_MASK);
                regVal |= ISS_ROUTE3_ISP_RSZB_MASK &
                          (priUnSigned << ISS_ROUTE3_ISP_RSZB_SHIFT);
                break;

            default:
                rtnVal = FVID2_EBADARGS;
                break;
        }
        if(FVID2_SOK == rtnVal)
        {
            HW_WR_REG32(gIssHalIssCtrlCfg.issBaseAddr + ISS_ROUTE3, regVal);
        }
    }

    return (rtnVal);
}

uint32_t VpsHal_issGlbceIsFilterDoneInSys2(void)
{
    return (gIssHalIssCtrlCfg.ispSys3BaseAddr + ISP5_IRQSTATUS_RAW2(0U) &
        ISP5_IRQSTATUS_RAW2_GLBCE_FILTERING_DONE_MASK) >>
        ISP5_IRQSTATUS_RAW2_GLBCE_FILTERING_DONE_SHIFT;
}

vpshalissIspPlatformData_t *VpsHal_getIspPlatformData(void)
{
    vpshalissIspPlatformData_t *platData = NULL;

    {
        gIssHalIspPlatformData.calInstPrms     = &gIssHalCalInstParams[0U];
        gIssHalIspPlatformData.issCtrlInitPrms = &gIssCtrlInitParam;
        platData = &gIssHalIspPlatformData;
    }

    return (platData);
}
#endif

#if defined(VPS_ISS_ISP_DEF)
void VpsHal_initCommonPlatformData(UInt32 irqNum)
{
    /* ISS driver registers only one interrupt out of 6.
     * So replacing in first element. */
    gIssHalCommonPlatformData.irqNum[0] = irqNum;
}

const issemInitParams_t *VpsHal_getCommonPlatformData(void)
{
    const issemInitParams_t *platData = NULL;

    {
        platData = &gIssHalCommonPlatformData;
    }

    return (platData);
}
#endif /* VPS_ISS_ISP_DEF */

#if defined (VPS_CAL_BUILD)
vpshalissCalPlatformData_t *VpsHal_getCalPlatformData(void)
{
    vpshalissCalPlatformData_t *platData = NULL;

    {
        gIssHalCalPlatformData.calInstPrms     = &gIssHalCalInstParams[0U];
#if defined (VPS_ISS_BUILD)
        gIssHalCalPlatformData.lvdsInstPrms    = &gIssHalLvdsRxInstParams[0U];
        gIssHalCalPlatformData.issCtrlInitPrms = &gIssCtrlInitParam;
#endif

        platData = &gIssHalCalPlatformData;
    }
    return (platData);
}
#endif /* VPS_CAL_BUILD */

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

