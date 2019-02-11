/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file utils_prcm_stats.c
 *
 * \brief  APIs to execute PRCM Stats , Dpll states, Junction temperature,
 *         Voltage.
 *
 * \version 0.0 (May 2015) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_temperature.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/pm/include/pmic/pmhal_tps65917.h>
#include <ti/drv/pm/include/pmic/pmhal_tps659039.h>
#include <ti/drv/pm/include/pmic/pmhal_lp87565.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8731.h>
#include <ti/drv/pm/include/pmic/pmhal_lp8733.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/include/boards/bsp_board.h>

/**
 *******************************************************************************
 * \brief Structure and Enum
 *******************************************************************************
 */
/**
 * \brief Structure contains ModuleId list clocklId list
 *
 */
typedef struct
{
    char               *moduleCharId;
    /**< module Id for debugging */
    pmhalPrcmModuleId_t modId;
    /**< module Id */
    char               *clkCharId;
    /**< clock id for debugging*/
    pmhalPrcmClockId_t  clkId;
    /**< clock Id */
}cpuClockList_t;


/**
 * \brief Module Power State names
 */
const char *moduleState_names[] =
{
    "DISABLED",
    "AUTO_CLOCKGATED",
    "ENABLED"
};

/**
 * \brief Module SIDLE State names
 */
const char *moduleSIdleState_names[] =
{
    "FUNCTIONAL",
    "IN_TRANSITION",
    "INTERFACE_IDLE",
    "DISABLED",
    "DETERMINED BY CLK STATE"
};

/**
 * \brief clock Activity State names
 */
const char *clockActivityState_names[] =
{
    "CLOCK_GATED",
    "CLOCK_ENABLED"
};

/**
 * \brief Power Domain Activity State names
 */
const char *powerDoaminState_names[] =
{
    "OFF",
    "RETENTION",
    "ON_INACTIVE",
    "ON_ACTIVE",
};

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        pmhalPrcmClockId_t enum in starterware.
 */
cpuClockList_t           cpuClockList[] =
{
#ifdef PROC_A15_0_INCLUDE
    {
        "MPU",
        PMHAL_PRCM_MOD_MPU,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC
    },
#endif
#ifdef PROC_IPU1_0_INCLUDE
    {
        "IPU1_0",
        PMHAL_PRCM_MOD_IPU1,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC
    },
#endif
#ifdef PROC_IPU1_1_INCLUDE
    {
        "IPU1_1",
        PMHAL_PRCM_MOD_IPU1,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC
    },
#endif
#ifdef PROC_IPU2_INCLUDE
    {
        "IPU2",
        PMHAL_PRCM_MOD_IPU2,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC
    },
#endif
#ifdef PROC_DSP1_INCLUDE
    {
        "DSP1",
        PMHAL_PRCM_MOD_DSP1,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC
    },
#endif
#ifdef PROC_DSP2_INCLUDE
    {
        "DSP2",
        PMHAL_PRCM_MOD_DSP2,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC
    },
#endif
#ifdef PROC_EVE1_INCLUDE
    {
        "EVE1",
        PMHAL_PRCM_MOD_EVE1,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC,
    },
#endif
#ifdef PROC_EVE2_INCLUDE
    {
        "EVE2",
        PMHAL_PRCM_MOD_EVE2,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC,
    },
#endif
#ifdef PROC_EVE3_INCLUDE
    {
        "EVE3",
        PMHAL_PRCM_MOD_EVE3,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC,
    },
#endif
#ifdef PROC_EVE4_INCLUDE
    {
        "EVE4",
        PMHAL_PRCM_MOD_EVE4,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC,
    },
#endif
#ifdef IVAHD_INCLUDE
    {
        "IVA",
        PMHAL_PRCM_MOD_IVA,
        "PMHAL_PRCM_CLK_GENERIC",
        PMHAL_PRCM_CLK_GENERIC
    },
#endif
};

/**
 * \brief Structure to define the clocks that one wants to set. The frequency is
 *        given in Hz. Generic clock is used when ever the user does not want to
 *        set any specific clock.
 *        One can look at the generic clocks list to know which module's clock
 *        is defined as generic. To program a specific clock refer
 *        pmhalPrcmClockId_t enum in starterware.
 */
cpuClockList_t           PeripheralClockList[] =
{
    {
        "PMHAL_PRCM_MOD_QSPI",
        PMHAL_PRCM_MOD_QSPI,
        "PMHAL_PRCM_CLK_QSPI_GFCLK",
        PMHAL_PRCM_CLK_QSPI_GFCLK
    },
    {
        "PMHAL_PRCM_MOD_DSS",
        PMHAL_PRCM_MOD_DSS,
        "PMHAL_PRCM_CLK_DSS_GFCLK",
        PMHAL_PRCM_CLK_DSS_GFCLK
    }
};

/*
 * \brief Table containing pointers to the functions to program I2C to talk to
 *        PMIC IC.
 */
static const pmhalI2cCommOperations_t pmicI2cfunc = {
    &Utils_prcmVoltageInit,
    &Bsp_deviceRead8,
    &Bsp_deviceWrite8,
    &Bsp_deviceReadAddr8Data16,
    &Bsp_deviceWriteAddr8Data16
};

/**
 * \brief Voltage rail names for power measurement.
 */
const char *pmhalRegulator_names[] =
{
    "VD_MPU    ",
    "VD_CORE   ",
    "VD_IVA    ",
    "VD_DSPEVE ",
    "VD_GPU    ",
    "VD_MMC13V3",
    "VD_SHV5   ",
    "VD_1V8PHY ",
    "VD_1V8PLL "
};

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Dummy I2C initialization function for PMIC Communication.
 *
 * \return PM_SUCCESS always to indicate success of operation.
 *
 *******************************************************************************
 */
Int32 Utils_prcmVoltageInit(Void)
{
    /* I2C initialization already finished during the Bsp_deviceInit function
     * Hence this is a dummy function which gets called.
     */
    return (Int32) PM_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief Print the temperature value for Available Temperature
 *        Sensor for given Voltage Id.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintTempValues(UInt32 voltId)
{
    pmhalBgapRange_t currTempRange = {0, 0};
    Int32 retVal = PM_SUCCESS;

    retVal = PMHALBgapGetCurrTemperature((pmhalPrcmVdId_t)voltId, &currTempRange);

    if(PM_SUCCESS == retVal)
    {
        Vps_printf("  %20s ||     [%d.%3d , %d.%3d]    \n",
               pmhalVoltageDomain_t_names[voltId],
               currTempRange.minTemp/1000, abs(currTempRange.minTemp) % 1000,
               currTempRange.maxTemp/1000, abs(currTempRange.maxTemp) % 1000);
    }
    else
    {
        Vps_printf(" UTILS_PRCM_STATS: Get Temperature Failed!!\n");
    }
}

/**
 *******************************************************************************
 *
 * \brief Print all the temperature value for Available Temperature Sensor.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllVDTempValues(void)
{
    UInt32 voltId;

    Vps_printf(" \r\n");
    Vps_printf(" UTILS_PRCM_STATS:  Current Temperature,\r\n");
    Vps_printf(" \r\n");
    Vps_printf("  Voltage Rail         ||   Curr Temp Min - Max   \r\n");
    Vps_printf(" --------------------------------------------------------- \r\n");
    for(voltId = PMHAL_PRCM_VD_MIN;voltId < (pmhalPrcmVdId_t)PMHAL_BGAP_NUM_FSM;voltId++)
    {
        Utils_prcmPrintTempValues(voltId);
    }
    Vps_printf("\n");

}

/**
 *******************************************************************************
 *
 * \brief Print the Voltage value for Available Voltage rails corrosponding to
 *         given voltage id
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintVoltageValues(UInt32 voltId)
{
    Int32 retVal = PM_SUCCESS;
    UInt32 voltage = 0U;

    retVal = PMHALVMGetCurrentVoltage((pmhalPrcmVdId_t)voltId, &voltage);

    if(PM_SUCCESS == retVal)
    {
        Vps_printf("  %20s     ||      %d mV  \n",pmhalVoltageDomain_t_names[voltId],voltage);
    }
    else
    {
        Vps_printf(" UTILS_PRCM_STATS: Get Voltage Failed!! \n");
    }

}

/**
 *******************************************************************************
 *
 * \brief Print all the Voltage value for available Voltage Rails.
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllVoltageValues(void)
{
    UInt32 voltId;
    Vps_printf(" --------------------------------------------------------- \r\n");
    Vps_printf(" \r\n");
    Vps_printf(" UTILS_PRCM_STATS:  Current Voltage          \r\n");
    Vps_printf(" \r\n");
    Vps_printf("     Voltage Rail          ||      Voltage  \r\n");
    Vps_printf(" --------------------------------------------------------- \r\n");
    for(voltId = PMHAL_PRCM_VD_MIN;voltId < PMHAL_PRCM_VD_COUNT;voltId++)
    {
        Utils_prcmPrintVoltageValues(voltId);
    }
    Vps_printf("\n");
    Vps_printf(" --------------------------------------------------------- \r\n");
}

/**
 *******************************************************************************
 *
 * \brief Print all PRCM Register data and the current state .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmDumpRegisterData(void)
{
    Int32 status;
    pmhalPrcmPdId_t pdIdx;
    pmhalPrcmCdId_t cdIdx;
    pmhalPrcmModuleId_t modIdx;
    pmhalPDStats_t pdStatus;
    pmhalCDStats_t cdStatus;
    pmhalModuleStats_t modStatus;

    Vps_printf(" \r\n");
    Vps_printf(" UTILS_PRCM_STATS:  PRCM DUMP Statistics         \r\n");
    Vps_printf(" \r\n");
    Vps_printf(" -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \r\n");
    for(pdIdx = (pmhalPrcmPdId_t)0U; pdIdx < PMHAL_PRCM_PD_COUNT; pdIdx++)
    {
        Vps_printf(" \r\n");
        Vps_printf(" POWER DOMAIN    %20s \r\n", pmhalPowerDomain_t_names[pdIdx]);
        Vps_printf(" -------------------------------------------------------------------- \r\n");
        status = PMHALPrcmStatsGetPdRegData(pdIdx,&pdStatus);
        if(status == PM_SUCCESS)
        {
            Vps_printf("                                         |  Reg. Address  |  Value ");
            Vps_printf(" -------------------------------------------------------------------- \r\n");
            Vps_printf("                               PWRSTCTRL |  0x%8x    |  %08x        \n",
                        pdStatus.pwrStateCtrlRegAddr,
                        pdStatus.pwrStateCtrlRegVal);

            Vps_printf("                                 PWRSTST |  0x%8x    |  %08x      \n",
                        pdStatus.pwrStateStatusRegAddr,
                        pdStatus.pwrStateStatusRegVal);
        }
        else
        {
            Vps_printf(" PWRSTCTRL and PWRSTST Not Available        ");
        }

        if(pdStatus.numClockDomain)
        {
            for(cdIdx = (pmhalPrcmCdId_t)0U; cdIdx < pdStatus.numClockDomain; cdIdx++)
            {
                Vps_printf(" -------------------------------------------------------------------- \r\n");
                /* MISRA.PTR.ARITH
                 * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
                 *                       arithmetic or array index expression
                 * KW State: Defer -> Waiver -> Case by case
                 *
                 * Pointer arithmetic is required for performance like auto increment in loop.
                 * The harmful side effect of violating this rule (accessing outside valid memory)
                 * shall be checked by another code checker like Klocwork.
                 */
                Vps_printf("        CLOCK DOMAIN      %s \r\n",  pmhalClkDomain_t_names[pdStatus.prcmCdList[cdIdx]]);
                Vps_printf(" -------------------------------------------------------------------- \r\n");
                /* MISRA.PTR.ARITH
                 * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
                 *                       arithmetic or array index expression
                 * KW State: Defer -> Waiver -> Case by case
                 *
                 * Pointer arithmetic is required for performance like auto increment in loop.
                 * The harmful side effect of violating this rule (accessing outside valid memory)
                 * shall be checked by another code checker like Klocwork.
                 */
                status = PMHALPrcmStatsGetCdRegData(pdStatus.prcmCdList[cdIdx],&cdStatus);

                if(status == PM_SUCCESS)
                {
                    Vps_printf("                                         |  Reg. Address  |   Value ");
                    Vps_printf(" -------------------------------------------------------------------- \r\n");
                    if(0x00 != cdStatus.clkStCtrlAddr)
                    {
                        Vps_printf("                               CLKSTCTRL |  0x%8x    |  %08x        \n",
                                cdStatus.clkStCtrlAddr,
                                cdStatus.clkStCtrlRegVal);
                    }
                    else
                    {
                        Vps_printf("                               CLKSTCTRL |  CLKSTCTRL REG NOT PRESENT \n");
                    }

                    if(0x00 != cdStatus.staticDepAddr)
                    {
                        Vps_printf("                       STATIC DEPENDENCY |  0x%8x    |  %08x      \n",
                                cdStatus.staticDepAddr,
                                cdStatus.staticDepRegVal);
                    }
                    else
                    {
                        Vps_printf("                       STATIC DEPENDENCY |    NOT PRESENT \n");
                    }
                }

                if(cdStatus.numModulesInCd)
                {
                    Vps_printf(" -------------------------------------------------------------------- \r\n");
                    Vps_printf("            MODULE  NAME                 | CLKCTRL Address|    Value   ");
                    Vps_printf(" -------------------------------------------------------------------- \r\n");
                    for(modIdx = (pmhalPrcmModuleId_t)0U; modIdx < cdStatus.numModulesInCd; modIdx++)
                    {
                        modStatus.clkCtrlRegAddr = 0U;
                        /* MISRA.PTR.ARITH
                         * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
                         *                       arithmetic or array index expression
                         * KW State: Defer -> Waiver -> Case by case
                         *
                         * Pointer arithmetic is required for performance like auto increment in loop.
                         * The harmful side effect of violating this rule (accessing outside valid memory)
                         * shall be checked by another code checker like Klocwork.
                         */
                        PMHALPrcmStatsGetModRegData(
                                    cdStatus.prcmModList[modIdx],&modStatus);
                        if(0x00 != modStatus.clkCtrlRegAddr)
                        {
                            /* MISRA.PTR.ARITH
                             * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
                             *                       arithmetic or array index expression
                             * KW State: Defer -> Waiver -> Case by case
                             *
                             * Pointer arithmetic is required for performance like auto increment in loop.
                             * The harmful side effect of violating this rule (accessing outside valid memory)
                             * shall be checked by another code checker like Klocwork.
                             */

                            Vps_printf("%40s |  0x%8x    |  %08x        ""\r\n",
                            pmhalNodeList_names[(cdStatus.prcmModList[modIdx])],
                            modStatus.clkCtrlRegAddr,
                            modStatus.clkCtrlRegVal);
                        }
                        else
                        {
                            /* MISRA.PTR.ARITH
                             * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4: Pointer is used in
                             *                       arithmetic or array index expression
                             * KW State: Defer -> Waiver -> Case by case
                             *
                             * Pointer arithmetic is required for performance like auto increment in loop.
                             * The harmful side effect of violating this rule (accessing outside valid memory)
                             * shall be checked by another code checker like Klocwork.
                             */

                            Vps_printf("%40s |  CLKCTRL  REG NOT PRESENT \n",
                            pmhalNodeList_names[(cdStatus.prcmModList[modIdx])]);
                        }
                        BspOsal_sleep(50U);
                    }
                }
            }
            Vps_printf(" \r\n");
            Vps_printf(" -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \r\n");
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief Print all Dpll Register data and the current state .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllDpllValues(void)
{
    UInt32 status;
    Bool skipReadClkStatus = FALSE;
    pmhalPrcmNodeId_t idx;
    UInt32 mulValue,divValue,rootFreq,lockFreq,clkSpeed;
    UInt32 maxPostDiv, postDivCount;
    pmhalPrcmClockActivityState_t clkStatus;
    Vps_printf(" \r\n");
    Vps_printf(" UTILS_PRCM_STATS:  DPLL Statistics         \r\n");
    Vps_printf(" \r\n");

    for (idx = PMHAL_PRCM_DPLL_MIN; idx < PMHAL_PRCM_DPLL_MAX; idx++)
    {
        pmhalPrcmPllPostDivValue_t divConfig[PMHAL_PRCM_DPLL_POST_DIV_COUNT];
        Vps_printf(" ----------------------------------------------- \r\n");
        Vps_printf(" %s          \n",pmhalNodeList_names[idx]);
        Vps_printf(" ----------------------------------------------- \r\n");
        Vps_printf(" \r\n");
        status = PMHALCMDpllLockStatus(idx);
        if((UInt32)0U == status)
        {
            Vps_printf(" NOT LOCKED \n");
            Vps_printf(" \r\n");
        }
        else
        {
            mulValue = PMHALCMDpllGetMultiplier(idx);
            divValue = PMHALCMDpllGetDivider(idx);
            maxPostDiv = (UInt32)PMHALCMDpllGetAllPostDivStatus(idx,divConfig);
            rootFreq = 20U;
            lockFreq = (2U * rootFreq * mulValue)/(divValue + 1U);
            Vps_printf(" LOCKED with \n");
            Vps_printf(" Ref. Frequency (MHz) = %d \n",rootFreq);
            Vps_printf(" M Multiplier Factor  = %d \n",mulValue);
            Vps_printf(" N Divider Factor     = %d \n",divValue);
            Vps_printf(" DCOLDO Freq    (MHz) = %d \n",lockFreq);
            Vps_printf(" \r\n");
            Vps_printf(" Supported Number of Post Dividers = %d \n",maxPostDiv);
            Vps_printf(" \r\n");
            for(postDivCount = 0U;
                postDivCount < maxPostDiv;
                postDivCount++)
            {
#ifdef TDA2PX_BUILD
                if((divConfig[postDivCount].postDivId == PMHAL_CTRL_POSTDIV_DPLL_CORE_H21) ||
                        (divConfig[postDivCount].postDivId == PMHAL_CTRL_POSTDIV_DPLL_GMAC_H14))
                {
                    skipReadClkStatus = (UInt32)TRUE;
                }
#endif
                if(skipReadClkStatus == (UInt32)FALSE)
                {
                    PMHALCMDpllGetPostDivClkStatus(idx,
                                                divConfig[postDivCount].postDivId,
                                                &clkStatus);
                    Vps_printf(" %s \n",
                        pmhalPostDivList_names[divConfig[postDivCount].postDivId]);
                    if(clkStatus == PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_GATED)
                    {
                        Vps_printf(" Gated \n");
                    }
                    else
                    {
                        Vps_printf(" Enabled \n");
                    }
                    Vps_printf(" Clock Divider = %d \n",
                        divConfig[postDivCount].configValue);

                    if(divConfig[postDivCount].postDivId == PMHAL_PRCM_DPLL_POST_DIV_M2)
                    {
                        clkSpeed = lockFreq /((UInt32)2U*divConfig[postDivCount].configValue);
                    }
                    else
                    {
                        clkSpeed = lockFreq /(divConfig[postDivCount].configValue);
                    }
                    Vps_printf(" Clock Speed (MHz) = %d \n",
                        clkSpeed);
                    Vps_printf(" \r\n");
                }
            }
            Vps_printf(" \r\n");
        }
    }
    Vps_printf(" --------------------------------------------------------- \r\n");
    Vps_printf("\n");
}

/**
 *******************************************************************************
 *
 * \brief Init PMLIB ClockRate. Initialize during system init
 *
 * \return None
 *
 *******************************************************************************
 */
Int32 Utils_prcmClockRateInit(void)
{
    static UInt32                *rootClkFreqList;
    static pmlibBoardVdRailShare_t *vdRailShareList;
    Int32  retVal = PM_SUCCESS;

#ifdef TDA3XX_BUILD
    UInt32  siliconPackageType;
    Bsp_BoardId boardId;
    Bsp_BoardRev baseBoardRev;
#endif

    const pmhalPmicOperations_t *pmicOps;
#ifdef TDA2EX_BUILD
    UInt32 siliconPackageType = PlatformGetSiliconPackageType();
    if (PLATFORM_SILICON_PACKAGE_TYPE_17X17== siliconPackageType)
    {
        pmicOps = PMHALLP8733GetPMICOps();
    }
    else
    {
    pmicOps = PMHALTps65917GetPMICOps();
    }
#elif defined(TDA2XX_BUILD)
    pmicOps = PMHALTps659039GetPMICOps();
#elif defined(TDA2PX_BUILD)
    pmicOps = PMHALLP87565GetPMICOps();
#elif defined TDA3XX_BUILD
    siliconPackageType = PlatformGetSiliconPackageType();
    if (PLATFORM_SILICON_PACKAGE_TYPE_15X15 == siliconPackageType)
    {
        boardId = Bsp_boardGetId();

        switch (boardId)
        {
            case BSP_BOARD_BASE_TDA3XX:
            case BSP_BOARD_TDA3XX_AR12XX_RADAR:
                baseBoardRev = Bsp_boardGetBaseBoardRev();

                if (BSP_BOARD_REV_D >= baseBoardRev)
                {
                    pmicOps = PMHALLP8733GetPMICOps();
                }
                else
                {
                    pmicOps = PMHALTps65917GetPMICOps();
                }

                break;

            case BSP_BOARD_TDA3XX_RVP_ALPHA:
                pmicOps = PMHALTps65917GetPMICOps();
                break;

            case BSP_BOARD_TDA3XX_RVP_BETA:
            case BSP_BOARD_TDA3XX_RVP_A:
            case BSP_BOARD_TDA3XX_D3_SK:
                pmicOps = PMHALLP8733GetPMICOps();
                break;

            default:
                pmicOps = PMHALTps65917GetPMICOps();
                break;
        }
    }
    else
    {
        pmicOps = PMHALLP8731GetPMICOps();
    }
#endif
    /* Register the I2C functions with the PMIC Communication to ensure the
     * PMIC can be communicated with I2C driver specific to BSP
     */
    PMHALI2CCommRegister(&pmicI2cfunc);
    retVal = (pmErrCode_t) PMHALPmicRegister(pmicOps);
    rootClkFreqList = PMLIBBoardConfigGetRootClks();
    vdRailShareList = PMLIBBoardConfigGetVdRailShareInfo();
    retVal         += PMLIBClkRateInit(rootClkFreqList, vdRailShareList);

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief Print all CPU Frequency .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllCPUFrequency(void)
{
    Int32 status;
    UInt32 idx;
    UInt32    size = sizeof(cpuClockList)/sizeof(cpuClockList_t);
    Vps_printf(" --------------------------------------------------------- \r\n");
    Vps_printf(" \r\n");
    Vps_printf(" UTILS_PRCM_STATS:  CPU Frequency                          \r\n");
    Vps_printf(" \r\n");
    Vps_printf("     Core Name          ||      Freq in Mhz  \r\n");
    Vps_printf(" --------------------------------------------------------- \r\n");
    for (idx = 0U; idx < size; idx++)
    {
        UInt32 clkGetRate = 0U;
        status = PMLIBClkRateGet(cpuClockList[idx].modId,
                                 cpuClockList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            Vps_printf("  %20s  ||      %d.%2d    \n",
                cpuClockList[idx].moduleCharId,
                clkGetRate/(UInt32)1000000U,
                clkGetRate%(UInt32)1000000U);
        }
    }
    Vps_printf("\n");
    Vps_printf(" --------------------------------------------------------- \r\n");
}

/**
 *******************************************************************************
 *
 * \brief Print all the Peripheral Frequency .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllPeripheralsFrequency(void)
{
    Int32 status;
    UInt32 idx;
    UInt32    size = sizeof(PeripheralClockList)/sizeof(cpuClockList_t);
    Vps_printf(" --------------------------------------------------------- \r\n");
    Vps_printf(" \r\n");
    Vps_printf(" UTILS_PRCM_STATS:  Peripheral Frequency                   \r\n");
    Vps_printf(" \r\n");
    Vps_printf("     Peripheral Name           ||      Freq in Mhz  \r\n");
    Vps_printf(" --------------------------------------------------------- \r\n");
    for (idx = 0U; idx < size; idx++)
    {
        UInt32 clkGetRate = 0U;
        status = PMLIBClkRateGet(PeripheralClockList[idx].modId,
                                 PeripheralClockList[idx].clkId,
                                 &clkGetRate);

        if (status == PM_SUCCESS)
        {
            Vps_printf("  %20s     ||      %d.%2d    \n",
                PeripheralClockList[idx].moduleCharId,
                clkGetRate/(UInt32)1000000U,
                clkGetRate%(UInt32)1000000U);
        }
    }
    Vps_printf("\n");
    Vps_printf(" --------------------------------------------------------- \r\n");
}

/**
 *******************************************************************************
 *
 * \brief Print all Module current state .
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintAllModuleState(void)
{

    pmhalPrcmModuleId_t modIdx;
    pmlibSysConfigDetailedState_t detailedState;
    pmlibSysConfigPowerState_t    moduleState;

    Vps_printf(" \r\n");
    Vps_printf(" UTILS_PRCM_STATS:  PRCM Module Statistics         \r\n");
    Vps_printf(" \r\n");

    Vps_printf(" ---------------------------------------------------------- \r\n");
    Vps_printf("            MODULE  NAME                 |  Module State    \n");

    for(modIdx = (pmhalPrcmModuleId_t)((UInt32)PMHAL_PRCM_MOD_LOWER_BOUND + 1U);
        modIdx < PMHAL_PRCM_MOD_COUNT;
        modIdx++)
    {
        moduleState = PMLIB_SYS_CONFIG_INVALID;
        detailedState.moduleMode = PMHAL_PRCM_MODULE_IDLEST_MIN;
        detailedState.clockMode = PMHAL_PRCM_MODULE_CLOCKACTIVITY_CLK_MIN;
        detailedState.pdMode = PMHAL_PRCM_PD_STATUS_MIN;
        PMLIBSysConfigGetPowerState(modIdx, &moduleState, &detailedState);

        if(moduleState != PMLIB_SYS_CONFIG_INVALID)
        {
            Vps_printf(" ---------------------------------------------------------- \r\n");
            Vps_printf("%40s | %15s    \r\n",
                            pmhalNodeList_names[modIdx],
                            moduleState_names[moduleState]);
            Vps_printf("                      Module SIDLE State | %15s \n",
                    moduleSIdleState_names[detailedState.moduleMode]);
            Vps_printf("                    Clock Activite State | %15s \n",
                            clockActivityState_names[detailedState.clockMode]);
            Vps_printf("                      Power Domain State | %15s \n",
                            powerDoaminState_names[detailedState.pdMode]);
        }
        else
        {
            Vps_printf(" ---------------------------------------------------------- \r\n");
            Vps_printf("%40s \r\n",
                            pmhalNodeList_names[modIdx]);
            Vps_printf(" moduleState returned PMLIB_SYS_CONFIG_INVALID \n");

            Vps_printf("                      Module SIDLE State | %15s \n",
                    moduleSIdleState_names[detailedState.moduleMode]);
            Vps_printf("                    Clock Activite State | %15s \n",
                            clockActivityState_names[detailedState.clockMode]);
            Vps_printf("                      Power Domain State | %15s \n",
                            powerDoaminState_names[detailedState.pdMode]);
        }
        BspOsal_sleep(50U);
    }
}

/**
 *******************************************************************************
 *
 * \brief Initialize the INA226 to print the power consumption
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintPowerConsumptionInit(Void)
{
    /* Ultrasonic uses the UART10 pin mux for the GPIO6_14/15 lines
     * This conflicts with the power measurement. Hence the power measurement
     * initialization code is placed in the condition of ULTRASONIC_INCLUDE
     * not being defined.
     */
#if (defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)) && !defined(ULTRASONIC_INCLUDE) && !defined(BOARD_TYPE_TDA2XX_RVP) && !defined(BOARD_TDA2XX_CASCADE_RADAR)
    pmhalPrcmPmicRegulatorId_t regId;
    pmErrCode_t status = PM_SUCCESS;
    /* Use the I2C3 for accessing INA registers */
    PlatformI2C3SetPinMux();
    for (regId = PMHAL_PRCM_PMIC_REGULATOR_MIN;
         regId < PMHAL_PRCM_PMIC_REGULATOR_COUNT;
         regId = (pmhalPrcmPmicRegulatorId_t) ((Int32) regId + 1))
    {
        /* 8.244 ms and 1024 averages is the best combination for lowest
         * noise.
         */
        status += (Int32) PMHALINA226SetBusVoltConversionTime(
            regId, PMHAL_INA226_CONV_TIME_8P244_MILLIS);
        status += (Int32) PMHALINA226SetShuntVoltConversionTime(
            regId, PMHAL_INA226_CONV_TIME_8P244_MILLIS);
        status += (Int32) PMHALINA226SetAverage(regId,
                                                  PMHAL_INA226_NUM_AVERAGE_1024);
    }
    if (PM_SUCCESS != status)
    {
        Vps_printf(
        " UTILS_PRCM_STATS: INA226 Setup Failed. Check if INA226 is connected on I2C3 Lines\n");
    }
#endif
}

/**
 *******************************************************************************
 *
 * \brief Print Power consumption
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_prcmPrintPowerConsumption(Void)
{
    /* Ultrasonic uses the UART10 pin mux for the GPIO6_14/15 lines
     * This conflicts with the power measurement. Hence the power measurement
     * is placed in the condition of ULTRASONIC_INCLUDE not being defined.
     */
#if (defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)) && !defined(ULTRASONIC_INCLUDE) && !defined(BOARD_TDA2XX_CASCADE_RADAR)
    pmhalPrcmPmicRegulatorId_t regId;
    pmErrCode_t status = PM_SUCCESS;
    pmhalIna226OutputData_t    opData;
    Int64 totalcurrent, totolpower;

    Vps_printf(
            "============================================================================\n");
    Vps_printf(
        "Name      | Bus (mV)\t| Res (mOhm) | Shunt (uV)  | Current (mA) | Power (mW)\n");
    Vps_printf(
        "----------------------------------------------------------------------------\n");
    totolpower   = (Int64) 0;
    totalcurrent = (Int64) 0;
    for (regId = PMHAL_PRCM_PMIC_REGULATOR_MIN;
         regId < PMHAL_PRCM_PMIC_REGULATOR_COUNT;
         regId = (pmhalPrcmPmicRegulatorId_t) ((Int32) regId + 1))
    {
        status = PMHALINA226GetData(regId, &opData);
        if (PM_SUCCESS == status)
        {
            char busVolt[256], shuntVolt[256], current[256], power[256],
                 resistance[5];
            Int32  integerValue, decimal;
            integerValue = (Int32) opData.busVoltage / 1000;
            decimal      = ((Int32) opData.busVoltage % 1000);
            snprintf(busVolt, sizeof(busVolt), "%d.%03d", integerValue, decimal);

            integerValue = (Int32) opData.shuntVoltage / 1000;
            decimal      = ((Int32) opData.shuntVoltage % 1000);
            if (decimal < 0)
            {
                decimal = -(Int32)1 * decimal;
            }
            snprintf(shuntVolt, sizeof(shuntVolt), "%d.%03d", integerValue, decimal);

            integerValue = (Int32) opData.current / 1000;
            decimal      = ((Int32) opData.current % 1000);
            if (decimal < 0)
            {
                decimal = -(Int32)1 * decimal;
            }
            snprintf(current, sizeof(current), "%02d.%03d", integerValue, decimal);

            integerValue = (Int32) opData.power / 1000;
            decimal      = (Int32) (opData.power % 1000);
            if (decimal < 0)
            {
                decimal = -(Int32)1 * decimal;
            }
            snprintf(power, sizeof(power),"%d.%03d", integerValue, decimal);

            integerValue = (Int32) opData.shuntRes;
            snprintf(resistance, sizeof(resistance), "%02d", integerValue);

            Vps_printf(
                "%s| %s\t| %s         | %s\t| %s\t| %s\n",
                pmhalRegulator_names[regId],
                busVolt, resistance, shuntVolt, current, power);
            Vps_printf(
                "----------------------------------------------------------------------------\n");
            Vps_printf("\n");
            totalcurrent += (Int64) opData.current;
            totolpower   += (Int64) opData.power;
        }
        else
        {
            Vps_printf(" UTILS_PRCM_STATS: Reading the regulator data failed\n");
            break;
        }
    }
    if (PM_SUCCESS == status)
    {
        char current[256], power[256];
        Int32  integerValue, decimal;
        integerValue = ((Int32) totalcurrent / 1000);
        decimal      = ((Int32) totalcurrent % 1000);
        snprintf(current, sizeof(current), "%d.%03d", integerValue, decimal);

        integerValue = ((Int32) totolpower / 1000);
        decimal      = ((Int32) totolpower % 1000);
        snprintf(power, sizeof(power), "%d.%03d", integerValue, decimal);

        Vps_printf(
            "Total     |                                     \t| %s\t| %s\n",
            current, power);
        Vps_printf(
            "============================================================================\n");
        Vps_printf("\n");
        Vps_printf(" UTILS_PRCM_STATS: PM INA226 Power Read Successfully !!\n");
    }
    else
    {
        Vps_printf(" UTILS_PRCM_STATS: PM INA226 Power Read Failed !!\n");
    }
#endif
}
