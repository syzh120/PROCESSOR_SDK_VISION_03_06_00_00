/******************************************************************************
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
******************************************************************************/

/**
  ******************************************************************************
 * \file rtiLink_tsk.c
 *
 * \brief  This file has the implementation of RTI Link
 *
 *         This file implements the state machine logic for this link.
 *         It also include HAL function calls to setup and use the RTI module
 *
 * \version 0.1 (Aug 2015) : [CSG] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "rtiLink_priv.h"

#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_rti.h>
#include <ti/csl/csl_rti.h>
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmlib.h>

#include <ti/sysbios/family/shared/vayu/IntXbar.h>
#ifdef BUILD_DSP
#include <ti/sysbios/family/c64p/EventCombiner.h>
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define RTI_CLOCK_SOURCE_SYSCLK1_DIV4_FREQ_KHZ      (5000000U)
#define RTI_CLOCK_SOURCE_SYSCLK2_DIV4_FREQ_KHZ      (5644800U)
#define RTI_CLOCK_SOURCE_32KHZ_FREQ_KHZ             (32786U)

/*
 * \brief Commands supported using the SYSTEM LINK infrastructure
 */

/* Supported on all cores except IPU1_C1 - used to start WWDT servicing on the
 * CPU - should not be sent by application.
 * Application must use System_rtiEnableAll()
 */
#define SYSTEM_LINK_CMD_RTI_ENABLE                  (0xABCDF001U)

/* Supported on all cores except IPU1_C1 - used to stop WWDT servicing on the
 * CPU - should not be sent by application.
 * Application must use System_rtiDisableAll()
 */
#define SYSTEM_LINK_CMD_RTI_DISABLE                 (0xABCDF002U)

/* Supported on all cores except IPU1_C1 - used to stop WWDT servicing on the
 * CPU - should not be sent by application.
 * Application must use System_rtiDisableAll()
 */
#define SYSTEM_LINK_CMD_RTI_MONITOR_CORE_ENABLE(x)  (0xABCDF003U + x)

/* Supported on all cores - used to enable WWDT expiry monitoring on the
 * CPU - should not be sent by application.
 * Link will use this internally.
 */
#define SYSTEM_LINK_CMD_RTI_MONITOR_CORE_DISABLE(x) \
            (SYSTEM_LINK_CMD_RTI_MONITOR_CORE_ENABLE(SYSTEM_PROC_MAX) + x)

/* Supported on all cores - used to disable WWDT expiry monitoring on the
 * CPU - should not be sent by application.
 * Link will use this internally.
 */
#define SYSTEM_LINK_CMD_RTI_MONITOR_CORE_MAX \
            (SYSTEM_LINK_CMD_RTI_MONITOR_CORE_DISABLE(SYSTEM_PROC_MAX))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \brief  Enum to select the clock source for RTI module.
 */
typedef enum rtiClockSource
{
    RTI_CLOCK_SOURCE_SYSCLK1_DIV4 = PMHAL_PRCM_DIV_SYS_CLK1,
    /**< to select clock frequency of (sysclk1/4) */
    RTI_CLOCK_SOURCE_SYSCLK2_DIV4 = PMHAL_PRCM_DIV_SYS_CLK2,
    /**< to select clock frequency of (sysclk1/4) */
    RTI_CLOCK_SOURCE_32KHZ = PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
                             /**< to select clock frequency of 32KHz */
}rtiClockSource_t;

/**
 * \brief  Enum to select the Suspend lines for RTI module.
 */
typedef enum rtiSuspendLineCore
{
    RTI_SUSPEND_LINE_CORE_IPU_C0 = 0x00000031U,
    /**< to select suspend line for IPU core 0 */
    RTI_SUSPEND_LINE_CORE_IPU_C1 = 0x00000041U,
    /**< to select suspend line for IPU core  */
    RTI_SUSPEND_LINE_CORE_DSP_C0 = 0x00000001U,
    /**< to select suspend line for DSP core 0 */
    RTI_SUSPEND_LINE_CORE_DSP_C1 = 0x00000071U,
    /**< to select suspend line for DSP core 1 */
    RTI_SUSPEND_LINE_CORE_EVE = 0x000000A1U,
    /**< to select suspend line for EVE */
    RTI_SUSPEND_LINE_CORE_NONE = 0x00000000U
    /**< Disable suspend feature */
}rtiSuspendLineCore_t;

/**
 * \brief Base Addresses for RTI modules, used for RTI HAL usage
 */
const UInt32 gRtiModuleBaseAddr[RTI_LINK_NUM_RTI_MODULES] =
{
    SOC_RTI1_BASE, /* RTI1 */
    SOC_RTI2_BASE, /* RTI2 */
    SOC_RTI3_BASE, /* RTI3 */
    SOC_RTI4_BASE, /* RTI4 */
    SOC_RTI5_BASE  /* RTI5 */
};

/**
 * \brief Interrupt lines used on IPU1_C0/IPU1_C1
 */
const UInt32 gRtiIpuIntrId[RTI_LINK_NUM_RTI_MODULES] =
{
    35U, /* RTI1 */
    36U, /* RTI2 */
    37U, /* RTI3 */
    38U, /* RTI4 */
    39U  /* RTI5 */
};

/**
 * \brief Interrupt lines used on DSP1/DSP2
 */
const UInt32 gRtiDspIntrId[RTI_LINK_NUM_RTI_MODULES] =
{
    39U, /* RTI1 */
    40U, /* RTI2 */
    41U, /* RTI3 */
    42U, /* RTI4 */
    43U  /* RTI5 */
};

/**
 * \brief Interrupt lines used on EVE
 */
const UInt32 gRtiEveIntrId[RTI_LINK_NUM_RTI_MODULES] =
{
    1U, /* RTI1 */
    2U, /* RTI2 */
    3U, /* RTI3 */
    4U, /* RTI4 */
    7U  /* RTI5 */
};

/**
 * \brief Register offsets for mapping the suspend lines from CPU to
 *        different RTI modules
 */
const UInt32 gRtiDrmSuspendLine[RTI_LINK_NUM_RTI_MODULES] =
{
    0x250U, /* RTI1: SOC_I_DRM_BASE_SUSPEND_CTRL20 */
    0x254U, /* RTI2: SOC_I_DRM_BASE_SUSPEND_CTRL21 */
    0x258U, /* RTI3: SOC_I_DRM_BASE_SUSPEND_CTRL22 */
    0x25CU, /* RTI4: SOC_I_DRM_BASE_SUSPEND_CTRL23 */
    0x260U  /* RTI5: SOC_I_DRM_BASE_SUSPEND_CTRL24 */
};

/**
 * \brief Crossbar instances for RTIx_IRQ_WWD - interrupt for invalid windowed
 *        watchdog operation.
 */
const UInt32 gRtiXbarId[RTI_LINK_NUM_RTI_MODULES] =
{
    RTI1_IRQ_WWD,
    RTI2_IRQ_WWD,
    RTI3_IRQ_WWD,
    RTI4_IRQ_WWD,
    RTI5_IRQ_WWD
};

#pragma DATA_ALIGN(gRtiLink_tskStack, 32)
#pragma DATA_SECTION(gRtiLink_tskStack, ".bss:taskStackSection")
UInt8 gRtiLink_tskStack[SYSTEM_TSK_STACK_SIZE];

/**
 *******************************************************************************
 * \brief Link object, stores all link related information
 *******************************************************************************
 */
RtiLink_Obj gRtiLink_obj;

/* ========================================================================== */
/*                         Function definitions                               */
/* ========================================================================== */

/**
 * \brief Call the PMLIB APIs to reset the specified CPU core
 */
static UInt32 rti_resetCore(UInt32 procId)
{
    UInt32 retVal = 0U;

    switch (procId)
    {
        case SYSTEM_PROC_IPU1_1:
            retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);
            break;
        case SYSTEM_PROC_DSP1:
            retVal = PMHALResetAssert(PMHAL_PRCM_RG_DSP1_RST);
            break;
        case SYSTEM_PROC_DSP2:
            retVal = PMHALResetAssert(PMHAL_PRCM_RG_DSP2_RST);
            break;
        case SYSTEM_PROC_EVE1:
            retVal = PMHALResetAssert(PMHAL_PRCM_RG_EVE1_CPU_RST);
            break;
        default:
            break;
    }

    return retVal;
}

/**
 * \brief Get the RTI module associated with specified CPU core
 */
static UInt32 rti_getCoreRtiModule(UInt32 procId)
{
    UInt32 i = 0U;
    UInt32 retVal = 0U;
    RtiLink_Obj *pObj = &gRtiLink_obj;

    for(i = 0U; i < RTI_LINK_NUM_RTI_MODULES; i++)
    {
        if(procId == pObj->procMap[i])
        {
            retVal = gRtiModuleBaseAddr[i];
            break;
        }
    }

    return retVal;
}

/**
 * \brief Get the period of the watchdog-timer for specified core.
 *        This is not configurable as this will depend on system loads and
 *        needs to be set at compile time only.
 */
static UInt32 rti_getCoreRtiTimeoutVal(UInt32 procId)
{
    UInt32 retVal = 4000U;

    switch (procId)
    {
        case SYSTEM_PROC_IPU1_0:
            retVal = 4000U;
            break;
        case SYSTEM_PROC_DSP1:
            retVal = 4000U;
            break;
        case SYSTEM_PROC_DSP2:
            retVal = 4000U;
            break;
        case SYSTEM_PROC_EVE1:
            retVal = 4000U;
            break;
        default:
            break;
    }

    return retVal;
}

/**
 * \brief Get the window-size for processing the WWDT for specified core.
 *        This is not configurable as this will depend on system loads and
 *        needs to be set at compile time only.
 *        As per current design of the RTI link, it should never return
 *        RTI_DWWD_WINDOWSIZE_100_PERCENT - otherwise the RTI link task will
 *        keep on executing continuously.
 */
static UInt32 rti_getCoreRtiWindowSize(UInt32 procId)
{
    UInt32 retVal = RTI_DWWD_WINDOWSIZE_50_PERCENT;

    switch (procId)
    {
        case SYSTEM_PROC_IPU1_0:
            retVal = RTI_DWWD_WINDOWSIZE_50_PERCENT;
            break;
        case SYSTEM_PROC_DSP1:
            retVal = RTI_DWWD_WINDOWSIZE_50_PERCENT;
            break;
        case SYSTEM_PROC_DSP2:
            retVal = RTI_DWWD_WINDOWSIZE_50_PERCENT;
            break;
        case SYSTEM_PROC_EVE1:
            retVal = RTI_DWWD_WINDOWSIZE_50_PERCENT;
            break;
        default:
            break;
    }

    return retVal;
}

/**
 * \brief Get clock value in Hz for the specified clock source
 */
static UInt32 rti_getClkVal(UInt32 clkSrc)
{
    UInt32 retVal = RTI_CLOCK_SOURCE_32KHZ_FREQ_KHZ;
    switch (clkSrc)
    {
        case RTI_CLOCK_SOURCE_32KHZ:
            retVal = RTI_CLOCK_SOURCE_32KHZ_FREQ_KHZ;
            break;
        case RTI_CLOCK_SOURCE_SYSCLK1_DIV4:
            retVal = RTI_CLOCK_SOURCE_SYSCLK1_DIV4_FREQ_KHZ;
            break;
        case RTI_CLOCK_SOURCE_SYSCLK2_DIV4:
            retVal = RTI_CLOCK_SOURCE_SYSCLK2_DIV4_FREQ_KHZ;
            break;
        default:
            break;
    }

    return retVal;
}

/**
 * \brief Get the clock source to be used in the RTI module for the specified
 *        processor.
 *        The mapping of clock to RTI module is done compile-time only.
 *        The choice of clock source depends upon the period of the watchdog
 *        timer.
 */
static UInt32 rti_getCoreRtiClkSrc(UInt32 procId)
{
    UInt32 retVal = RTI_CLOCK_SOURCE_32KHZ;

    switch (procId)
    {
        case SYSTEM_PROC_IPU1_0:
            retVal = RTI_CLOCK_SOURCE_32KHZ;
            break;
        case SYSTEM_PROC_DSP1:
            retVal = RTI_CLOCK_SOURCE_32KHZ;
            break;
        case SYSTEM_PROC_DSP2:
            retVal = RTI_CLOCK_SOURCE_32KHZ;
            break;
        case SYSTEM_PROC_EVE1:
            retVal = RTI_CLOCK_SOURCE_32KHZ;
            break;
        default:
            break;
    }

    return retVal;
}

/**
 * \brief Get the clock source to be used in the specified RTI module.
 *        The mapping of clock to RTI module is done compile-time only.
 *        The choice of clock source depends upon the period of the watchdog
 *        timer.
 */
static void rti_setClockSource(UInt32 rtiModule,
                               UInt32 rtiClockSourceSelect)
{
    switch (rtiModule) {
        case SOC_RTI1_BASE:
            HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE +
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL,
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1,
                          rtiClockSourceSelect);
            break;
        case SOC_RTI2_BASE:
            HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE +
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL,
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2,
                          rtiClockSourceSelect);
            break;
        case SOC_RTI3_BASE:
            HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE +
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL,
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3,
                          rtiClockSourceSelect);
            break;
        case SOC_RTI4_BASE:
            HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE +
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL,
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4,
                          rtiClockSourceSelect);
            break;
        case SOC_RTI5_BASE:
            HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE +
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL,
                          CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5,
                          rtiClockSourceSelect);
            break;
        default:
            break;
    }
}

/**
 * \brief For the specified clock-source and period in milliseconds, calculate
 *        the number of clock-ticks that need to be configured in the RTI
 *        module
 */
static UInt32 rti_getPreloadValue(UInt32 rtiClkSource, UInt32 timeoutMilliSec)
{
    UInt32 timeoutNumCycles = 0;
    UInt32 clkHz            = rti_getClkVal(rtiClkSource);

    /* Get the clock ticks for given time-out value
     * Dividing by 1000 since timeoutMilliSec is in milliseconds
     */
    timeoutNumCycles = timeoutMilliSec * clkHz / 1000U;
    return timeoutNumCycles;
}

/**
 * \brief Get the reaction mode to be used on RTI modules associated with the
 *        specified source.
 *        This mapping must be done at compile-time as this is dependent on how
 *        the SW uses these event. Typically, RTI modules associated with
 *        master cores like IPU1_C0 will be configured to generate a SoC reset.
 */
static UInt32 rti_getCoreRtiReaction(UInt32 procId)
{
    UInt32 retVal = RTI_DWWD_REACTION_GENERATE_NMI;

    switch (procId)
    {
        case SYSTEM_PROC_IPU1_0:
            retVal = RTI_DWWD_REACTION_GENERATE_RESET;
            break;
        case SYSTEM_PROC_DSP1:
            retVal = RTI_DWWD_REACTION_GENERATE_NMI;
            break;
        case SYSTEM_PROC_DSP2:
            retVal = RTI_DWWD_REACTION_GENERATE_NMI;
            break;
        case SYSTEM_PROC_EVE1:
            retVal = RTI_DWWD_REACTION_GENERATE_NMI;
            break;
        default:
            break;
    }

    return retVal;
}

/**
 * \brief This function must be called only from IPU1_C0
 *        This will send a SYSTEM_LINK_CMD_RTI_ENABLE or
 *        SYSTEM_LINK_CMD_RTI_DISABLE message to all cores to respectively
 *        start or stop RTI WWDT handling.
 */
static Int32 rti_enableRtiLink(UInt32 enable)
{
    Int32 status;
    Int32 mesg = SYSTEM_LINK_CMD_RTI_ENABLE;
    UInt32 i, selfProcId = System_getSelfProcId();
    UInt32 retVal = SYSTEM_LINK_STATUS_SOK;
    RtiLink_Obj *pObj = &gRtiLink_obj;

    if(FALSE == enable)
    {
        mesg = SYSTEM_LINK_CMD_RTI_DISABLE;
    }

    for(i = 0U; i < RTI_LINK_NUM_RTI_MODULES; i++)
    {
        /* Send message if RTI module is handled by some core and it had not
           expired previously */
        if((SYSTEM_PROC_MAX != pObj->procMap[i]) &&
           (FALSE == pObj->rtiExpired[i]))
        {
            if(TRUE == System_isProcEnabled(pObj->procMap[i]))
            {
                status = System_linkControl(
                    SYSTEM_MAKE_LINK_ID(pObj->procMap[i],
                                        SYSTEM_LINK_ID_PROCK_LINK_ID),
                    mesg,
                    NULL,
                    0,
                    TRUE);
                UTILS_assert(0 == status);
            }
        }
    }

    return retVal;
}

/**
 * \brief This set up the connection of emulation suspend line of the specified
 *        RTI module to the specified core specified by #rtiSuspendLineCore
 */
static void rti_setSuspendLine(UInt32 rtiModule, UInt32 deviceCore)
{
    UInt32 i;

    for(i = 0U; i < RTI_LINK_NUM_RTI_MODULES; i++)
    {
        if(rtiModule == gRtiModuleBaseAddr[i])
        {
            HW_WR_REG32(SOC_I_DRM_BASE + gRtiDrmSuspendLine[i],
                        deviceCore);
            break;
        }
    }
}

/**
 * \brief This set up the connection of emulation suspend line of the specified
 *        RTI module to the specified core.
 *        RTI module can be set to run independent of debugger state by
 *        setting enable to 0.
 */
static void rti_coreSuspendDbgLine(UInt32 rtiModule,
                                   UInt32 procId,
                                   UInt32 enable)
{
    UInt32 deviceCore = RTI_SUSPEND_LINE_CORE_NONE;

    switch (procId)
    {
        case SYSTEM_PROC_IPU1_0:
            deviceCore = RTI_SUSPEND_LINE_CORE_IPU_C0;
            break;
        case SYSTEM_PROC_DSP1:
            deviceCore = RTI_SUSPEND_LINE_CORE_DSP_C0;
            break;
        case SYSTEM_PROC_DSP2:
            deviceCore = RTI_SUSPEND_LINE_CORE_DSP_C1;
            break;
        case SYSTEM_PROC_EVE1:
            deviceCore = RTI_SUSPEND_LINE_CORE_EVE;
            break;
        default:
            break;
    }

    if(FALSE == enable)
    {
        deviceCore = RTI_SUSPEND_LINE_CORE_NONE;
    }

    rti_setSuspendLine(rtiModule, deviceCore);
}

/**
 * \brief Setup the RTI module based on specified window size, watchdog timer
 *        period and reaction type.
 *        Configuration sequence differs based on whether RTI WWDT counter is
 *        already enabled or not.
 *        rtiWindowSize cannot be 100% - Setting to 100% will cause RTI task to
 *        run continuously.
 */
static void rti_setup(UInt32 rtiWindowSize,
                      UInt32 rtiTimeoutMilliSec,
                      UInt32 rtiReaction)
{
    UInt32 selfProcId = System_getSelfProcId();
    UInt32 rtiModule = rti_getCoreRtiModule(selfProcId);
    UInt32 rtiPreloadValue;
    Int32  status;
    UInt32 cookie, intrStatus;

    if(FALSE == RTIDwwdIsCounterEnabled(rtiModule))
    {
        /* Configuration sequence is straight forward if RTI was never enabled
         *  - Set Clock source in control module
         *  - Calculate preload value
         *  - Set emulation suspend lines as required
         *      - This is currently mapped to whichever core the RTI module's
         *        WWDT is processed by.
         *  - Call HAL API - RTIDwwdWindowConfig
         *      - Set Window size in RTI register
         *      - Set Preload register
         *      - Set Reaction register
         *      - Start WWDT counter
         */

        /* Select RTI module clock source */
        rti_setClockSource(rtiModule, rti_getCoreRtiClkSrc(selfProcId));

        /* Configure everything for RTI if it was never enabled */
        rtiPreloadValue =
            rti_getPreloadValue(rti_getCoreRtiClkSrc(selfProcId),
                                rtiTimeoutMilliSec);

        rti_coreSuspendDbgLine(rtiModule, selfProcId, FALSE);

        status = RTIDwwdWindowConfig(rtiModule,
                                     rtiReaction,
                                     rtiPreloadValue,
                                     rtiWindowSize);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

        RTIDwwdCounterEnable(rtiModule);
    }
    else
    {
        /* In case RTI WWDT was previously enabled, and the monitoring was
         * disabled, configuration sequence changes.
         * This is not a typical RTI use-case, but it used in VisionSDK for
         * demo purposes.
         * For demo, RTI WWDT can be enabled/disabled as required.
         * To allow such a usage, when the WWDT is disabled, it should be
         * reconfigured to set window-size to 100% - this allows us to enable
         * WWDT processing from a clean-state by reconfiguring RTI without any
         * delay.
         * We need to handle following cases explicitly in this section
         *      - RTI WWDT may expire when WWDT handling is disabled. We need
         *        to clear such interrupts
         *      - If WWDT had expired, reconfiguration can generate additional
         *        interrupts. We need to ignore this.
         */

        /* RTI_DISABLE configures window as 100%
         * So configure window the new value */
        RTIDwwdSetWindowSize(rtiModule, rtiWindowSize);

        /* All reconfiguration is time-sensitive, so disable interrupts */
        cookie = BspOsal_disableInterrupt();

        /* Clear interrupts generated due to RTI WWDT expiry */
        intrStatus = RTIDwwdGetStatus(rtiModule);
        RTIDwwdClearStatus(rtiModule, intrStatus);

        /* Window is assumed to be set to 100% when WWDT handling was disabled
         * So service immediately to change the window size to new value
         */
        RTIDwwdService(rtiModule);

        /* Clear interrupts generated due to RTI WWDT expiry */
        intrStatus = RTIDwwdGetStatus(rtiModule);
        RTIDwwdClearStatus(rtiModule, intrStatus);

        /* Since RTI was just serviced, and window size is not 100%,
         * change reaction to new value - this will take effect immediately */
        RTIDwwdSetReaction(rtiModule, rtiReaction);

        /* Trap any unexpected interrupts */
        intrStatus = RTIDwwdGetStatus(rtiModule);
        if(0U != intrStatus)
        {
            Vps_printf(" RTI-LINK: Unexpected intr %x with reaction update!!\n",
                       intrStatus);
            UTILS_assert(FALSE);
        }

        BspOsal_restoreInterrupt(cookie);
    }
}

/**
 * \brief Send message to other cores to enable or disable monitoring of
 *        RTI WWDT expiry interrupts.
 */
static void rti_triggerExpiryMonitor(RtiLink_Obj *pObj, UInt32 enable)
{
    UInt32 i, mesg;
    Int32  status;
    UInt32 selfProcId = System_getSelfProcId();
    UInt32 dstProcId;

    if(TRUE == enable)
    {
        mesg = SYSTEM_LINK_CMD_RTI_MONITOR_CORE_ENABLE(selfProcId);
    }
    else
    {
        mesg = SYSTEM_LINK_CMD_RTI_MONITOR_CORE_DISABLE(selfProcId);
    }

    /* Scan through all RTI modules to check if current core is handling any
     * of them
     */
    for(i = 0; i < RTI_LINK_NUM_RTI_MODULES; i++)
    {
        /* Only send message if RTI handling is enabled on current core */
        if(selfProcId == pObj->procMap[i])
        {
            for(dstProcId = 0; dstProcId < SYSTEM_PROC_MAX; dstProcId++)
            {
                if(dstProcId == selfProcId)
                {
                    /* Start monitoring locally */
                    pObj->rtiMonitorEnabled[i] = enable;
                }
                else if((TRUE == System_isProcEnabled(dstProcId)) &&
                        (SYSTEM_CORE_STATE_ACTIVE == System_getCoreState(dstProcId)))
                {
                    /* Send message to all cores that are active in build and
                     * not dead.
                     */
                    status = System_linkControl(
                        SYSTEM_MAKE_LINK_ID(dstProcId,
                                            SYSTEM_LINK_ID_PROCK_LINK_ID),
                        mesg,
                        NULL,
                        0,
                        TRUE);
                    UTILS_assert(0 == status);
                }
            }
        }
    }
}

/**
 * \brief RTI WWDT service routine.
 *        This function will sleep until the WWDT service window is open.
 *        This provides additional argument to disable interrupt before
 *        servicing. This is useful when WWDT monitoring needs to be disabled.
 */
static UInt32 rti_wwdtServiceSequence(UInt32 rtiModule, UInt32 disableIntr)
{
    UInt32 cookie = 0;
    UInt32 ticksToOpenWindow;
    UInt32 timeToSleepMilliSec;
    UInt32 selfProcId = System_getSelfProcId();
    UInt32 clkSrc = rti_getCoreRtiClkSrc(selfProcId);
    UInt32 clkHz  = rti_getClkVal(clkSrc);

    /* Get time in milliseconds until the WWDT service window is open */
    ticksToOpenWindow = RTIDwwdGetTicksToOpenWindow(rtiModule);
    timeToSleepMilliSec = (ticksToOpenWindow * 1000U / clkHz);

    /*
     * Don't sleep if window is already open!
     */
    if(0 != ticksToOpenWindow)
    {
        /*
         * Sleep 1ms more to avoid waiting for window to open due to rounding
         * errors.
         */
        BspOsal_sleep(timeToSleepMilliSec + 1U);
    }

    /* Confirm that window is actually open */
    while (RTIDwwdIsClosedWindow(rtiModule))
    {
    }

    /* Disable interrupts if required */
    if(TRUE == disableIntr)
    {
        cookie = BspOsal_disableInterrupt();
    }
    RTIDwwdService(rtiModule);

    /* Return value valid only if interrupts were disabled */
    return cookie;
}

/**
 * \brief Contains main execution loop of RTI link
 *        This will be triggered by SYSTEM_LINK_CMD_RTI_ENABLE command which
 *        in turn sends a SYSTEM_CMD_NEW_DATA command
 *        This will keep on servicing the RTI whenever the service window opens.
 *        It will go into sleep() for the rest of the period
 *        This function will exit when rtiServiceEnabled is set to 0 by
 *        SYSTEM_LINK_CMD_RTI_DISABLE.
 */
static void rti_service(RtiLink_Obj *pObj)
{
    UInt32 cookie;
    UInt32 selfProcId = System_getSelfProcId();
    UInt32 rtiModule = rti_getCoreRtiModule(selfProcId);

    /* Trigger monitoring task on all cores */
    rti_triggerExpiryMonitor(pObj, TRUE);

    /* Keep looping until SYSTEM_LINK_CMD_RTI_DISABLE sets rtiServiceEnabled
     * to 0.
     */
    while(pObj->rtiServiceEnabled)
    {
        rti_wwdtServiceSequence(rtiModule, FALSE);
    }

    /* The following configuration sequence is required so the RTI WWDT
     * handling can be enabled again.
     */

    /* Change window to 50% to allow immediate update of RTI reactionType after
     * the servicing the WWDT */
    RTIDwwdSetWindowSize(rtiModule, RTI_DWWD_WINDOWSIZE_50_PERCENT);

    /* Service the WWDT.
     * Also disable interrupts due to time-sensitive nature of further
     * reconfiguration.
     */
    cookie = rti_wwdtServiceSequence(rtiModule, TRUE);

    /* Since window was set to 50% and interrupts were disabled after servicing,
     * RTI is guaranteed to be in closed window
     * This ensures reaction change will take effect immediately.
     * Restore interrupts after changing the reaction.
     */
    RTIDwwdSetReaction(rti_getCoreRtiModule(selfProcId),
                       RTI_DWWD_REACTION_GENERATE_NMI);
    BspOsal_restoreInterrupt(cookie);

    /* Maintain delay between reaction change and window-size change since we
     * are changing window-size to 100%.
     * This is required since if window-size is set to 100% at the same time as
     * reaction type change, the reaction type change may not take effect since
     * the 100% reconfiguration moves us into an open window.
     */
    BspOsal_sleep(1);
    RTIDwwdSetWindowSize(rti_getCoreRtiModule(selfProcId),
                         RTI_DWWD_WINDOWSIZE_100_PERCENT);

    /* Disable monitoring on all cores */
    rti_triggerExpiryMonitor(pObj, FALSE);
    Vps_printf(" RTI-LINK: Service Exit\n");
}

/** \brief Handle RTI WWDT expiry events.
 *         ISR argument is the base address of RTI module
 *         Clear interrupts from IPU1_C0 only.
 *         In case WWDT expiry monitoring is disabled
 *              - Ignore them.
 *         In case WWDT expiry monitoring is enabled
 *              - Update rtiExpired entry corresponding to expired WWDT
 *              - In case of ISRs on IPU1_C0, reset the expired core as well
 */
static void rti_isr(UArg ctx)
{
    UInt32 i;
    UInt32 intrStatus;
    RtiLink_Obj *pObj = &gRtiLink_obj;
    UInt32 selfProcId = System_getSelfProcId();

    UInt32 rtiModule = (UInt32) ctx;
    for(i = 0U; i < RTI_LINK_NUM_RTI_MODULES; i++)
    {
        if(rtiModule == gRtiModuleBaseAddr[i])
        {
            if(TRUE == pObj->rtiMonitorEnabled[i])
            {
                pObj->rtiExpired[i] = TRUE;
                System_setCoreState(pObj->procMap[i], SYSTEM_CORE_STATE_RTI_EXPIRED);
                Vps_printf(" RTI-LINK: RTI%d expired!!\n", i+1);

                /* Reset only from IPU1_0 and Don't reset yourself! */
                if((SYSTEM_PROC_IPU1_0 == selfProcId) &&
                   (SYSTEM_PROC_IPU1_0 != pObj->procMap[i]))
                {
                    /* Reset core whose RTI expired */
                    rti_resetCore(pObj->procMap[i]);
                }
            }

            if (SYSTEM_PROC_IPU1_0 == selfProcId)
            {
                /* Clear interrupt status only from IPU1_C0 */
                intrStatus = RTIDwwdGetStatus(gRtiModuleBaseAddr[i]);
                RTIDwwdClearStatus(gRtiModuleBaseAddr[i], intrStatus);
            }
        }
    }
}

/**
 *  \brief Map RTI expiry events to all CPUs
 */
static Void rti_registerInterrupts(RtiLink_Obj *pObj)
{
    UInt32 i;
    UInt32 selfProcId = System_getSelfProcId();

    for(i = 1U; i < RTI_LINK_NUM_RTI_MODULES; i++)
    {
        if(SYSTEM_PROC_IPU1_0 == selfProcId)
        {
            IntXbar_connectIRQ(gRtiIpuIntrId[i], gRtiXbarId[i]);
            pObj->rtiHwiHandle[i] = BspOsal_registerIntr(
                                        gRtiIpuIntrId[i],
                                        (BspOsal_IntrFuncPtr)(rti_isr),
                                        (Void *)gRtiModuleBaseAddr[i]);
            UTILS_assert(NULL != pObj->rtiHwiHandle[i]);
        }
        if(SYSTEM_PROC_IPU1_1 == selfProcId)
        {
            pObj->rtiHwiHandle[i] = BspOsal_registerIntr(
                                        gRtiIpuIntrId[i],
                                        (BspOsal_IntrFuncPtr)(rti_isr),
                                        (Void *)gRtiModuleBaseAddr[i]);
            UTILS_assert(NULL != pObj->rtiHwiHandle[i]);
        }
        if(SYSTEM_PROC_DSP1 == selfProcId)
        {
            IntXbar_connectIRQ(gRtiDspIntrId[i], gRtiXbarId[i]);
#ifdef BUILD_DSP
            EventCombiner_dispatchPlug(
                            gRtiDspIntrId[i],
                            (EventCombiner_FuncPtr)(&rti_isr),
                            (UArg)gRtiModuleBaseAddr[i],
                            1
                            );
            EventCombiner_enableEvent(gRtiDspIntrId[i]);
#endif
        }
        if(SYSTEM_PROC_DSP2 == selfProcId)
        {
            IntXbar_connectIRQ(gRtiDspIntrId[i], gRtiXbarId[i]);
#ifdef BUILD_DSP
            EventCombiner_dispatchPlug(
                            gRtiDspIntrId[i],
                            (EventCombiner_FuncPtr)(&rti_isr),
                            (UArg)gRtiModuleBaseAddr[i],
                            1
                            );
            EventCombiner_enableEvent(gRtiDspIntrId[i]);
#endif
        }
        if(SYSTEM_PROC_EVE1 == selfProcId)
        {
            IntXbar_connectIRQ(gRtiEveIntrId[i], gRtiXbarId[i]);
            pObj->rtiHwiHandle[i] = BspOsal_registerIntr(
                                        (gRtiEveIntrId[i] + 32U),
                                        (BspOsal_IntrFuncPtr)(rti_isr),
                                        (Void *)gRtiModuleBaseAddr[i]);
            UTILS_assert(NULL != pObj->rtiHwiHandle[i]);
        }
    }
}

/**
 *  \brief Main task for the RTI link
 *         Executes only all CPUs in the system.
 *         For cores not handling any RTI modules, it will not do anything as
 *         it will never receive SYSTEM_CMD_NEW_DATA message
 */
static Void rti_wwdtProcess(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg)
{
    UInt32 selfProcId = System_getSelfProcId();
    UInt32 cmd = Utils_msgGetCmd(pMsg);
    Bool ackMsg, done;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    RtiLink_Obj *pObj;

    UTILS_assert(pTsk != NULL);
    pObj = (RtiLink_Obj *) pTsk->appData;
    UTILS_assert(pObj != NULL);

    if (cmd != SYSTEM_CMD_CREATE)
    {
        Utils_tskAckOrFreeMsg(pMsg, FVID2_EFAIL);
        return;
    }

    Utils_tskAckOrFreeMsg(pMsg, status);
    pObj->state = SYSTEM_LINK_STATE_RUNNING;

    Vps_printf(" RTI-LINK: Initialized RTI link\n");

    done = FALSE;
    ackMsg = FALSE;

    while (!done)
    {
        status = Utils_tskRecvMsg(pTsk, &pMsg, BIOS_WAIT_FOREVER);
        if (status != SYSTEM_LINK_STATUS_SOK)
            break;

        cmd = Utils_msgGetCmd(pMsg);

        switch (cmd)
        {
            case SYSTEM_CMD_DELETE:
                pObj->state = SYSTEM_LINK_STATE_IDLE;
                done = TRUE;
                ackMsg = TRUE;
                break;

            case SYSTEM_CMD_NEW_DATA:
                Utils_tskAckOrFreeMsg(pMsg, status);
                UTILS_assert(pObj->state==SYSTEM_LINK_STATE_RUNNING);

                /* Configure the RTI registers */
                rti_setup(rti_getCoreRtiWindowSize(selfProcId),
                          rti_getCoreRtiTimeoutVal(selfProcId),
                          rti_getCoreRtiReaction(selfProcId));

                /* Execute the loop for WWDT handling */
                rti_service(pObj);

                /* SEM_WAIT started in SYSTEM_LINK_CMD_RTI_DISABLE.
                 * Release lock only after clean exit from service
                 * Avoids start during exit process
                 */
                BspOsal_semPost(pObj->lock);
                break;

            default:
                Utils_tskAckOrFreeMsg(pMsg, status);
                break;
        }
    }

    if (ackMsg && pMsg != NULL)
        Utils_tskAckOrFreeMsg(pMsg, status);

    return;
}

/**
 *  \brief Handles command sent via System_link APIs
 *         Supported commands
 *           - SYSTEM_LINK_CMD_RTI_ENABLE
 *                  - Send SYSTEM_CMD_NEW_DATA to start WWDT servicing
 *           - SYSTEM_LINK_CMD_RTI_DISABLE
 *                  - Set rtiServiceEnabled to 0 to stop WWDT servicing loop
 *           - SYSTEM_LINK_CMD_RTI_MONITOR_CORE_ENABLE/DISABLE(x)
 *                  - Monitor RTI WWDT expiry events corresponding to RTI
 *                    modules servicing WWDT on other cores.
 *          Ensures SYSTEM_LINK_CMD_RTI_ENABLE and SYSTEM_LINK_CMD_RTI_DISABLE
 *          don't happen simultaneously by using semaphores.
 */
static Void rti_cmdHandler(UInt32 cmd, Void *pPrm)
{
    UInt32 srcProcId, i;
    UInt32 monitorEnable;
    RtiLink_Obj *pObj = &gRtiLink_obj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if (SYSTEM_LINK_CMD_RTI_ENABLE == cmd)
    {
        BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);
        if(TRUE == pObj->rtiServiceEnabled)
        {
            Vps_printf(" RTI-LINK: Ignoring unexpected RTI_ENABLE command\n");
        }
        else
        {
            pObj->rtiServiceEnabled = TRUE;
            status = System_linkControl(
                pObj->tskId,
                SYSTEM_CMD_NEW_DATA,
                NULL,
                0,
                TRUE);
            UTILS_assert(0 == status);
            Vps_printf(" RTI-LINK: Starting RTI task\n");
        }
        BspOsal_semPost(pObj->lock);
    }
    else if (SYSTEM_LINK_CMD_RTI_DISABLE == cmd)
    {
        BspOsal_semWait(pObj->lock, BSP_OSAL_WAIT_FOREVER);
        pObj->rtiServiceEnabled = FALSE;
        /* Release the LOCK only after service exit */
        Vps_printf(" RTI-LINK: Stopping RTI task\n");
    }
    else if ((cmd >= SYSTEM_LINK_CMD_RTI_MONITOR_CORE_ENABLE(0U)) &&
             (cmd < SYSTEM_LINK_CMD_RTI_MONITOR_CORE_DISABLE(SYSTEM_PROC_MAX)))
    {
        /* Set rtiMonitorEnabled to 0 or 1 as per input message */
        if(cmd < SYSTEM_LINK_CMD_RTI_MONITOR_CORE_ENABLE(SYSTEM_PROC_MAX))
        {
            srcProcId = cmd -
                SYSTEM_LINK_CMD_RTI_MONITOR_CORE_ENABLE(0U);
            monitorEnable = TRUE;
        }
        else
        {
            srcProcId = cmd -
                SYSTEM_LINK_CMD_RTI_MONITOR_CORE_DISABLE(0U);
            monitorEnable = FALSE;
        }
        for(i = 0U; i < RTI_LINK_NUM_RTI_MODULES; i++)
        {
            if(srcProcId == pObj->procMap[i])
            {
                pObj->rtiMonitorEnabled[i] = monitorEnable;
            }
        }
    }
    else
    {
        status = SYSTEM_LINK_STATUS_SOK;
    }
}

/**
 *  \brief Set up the RTI link on all cores
 *         Will set up mapping between CPUs and RTI modules
 *         Create the RTI link task
 */
void System_rtiInit()
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkObj linkObj;
    RtiLink_Obj *pObj = &gRtiLink_obj;
    char tskName[32];
    UInt32 i, selfProcId = System_getSelfProcId();

    SystemLink_registerHandler(rti_cmdHandler);

    memset(pObj, 0, sizeof(*pObj));

    pObj->tskId = SYSTEM_MAKE_LINK_ID(selfProcId, SYSTEM_LINK_ID_RTI_0);
    pObj->state = SYSTEM_LINK_STATE_IDLE;

    memset(&linkObj, 0, sizeof(linkObj));
    linkObj.pTsk = &pObj->tsk;
    linkObj.linkGetFullBuffers= NULL;
    linkObj.linkPutEmptyBuffers= NULL;
    linkObj.getLinkInfo = NULL;

    System_registerLink(pObj->tskId, &linkObj);

    sprintf(tskName, "RTI%u", (unsigned int)selfProcId);
    status = Utils_tskCreate(&pObj->tsk,
                             rti_wwdtProcess,
                             RTI_LINK_TSK_PRI,
                             gRtiLink_tskStack,
                             RTI_LINK_TSK_STACK_SIZE, pObj, tskName,
                             UTILS_TSK_AFFINITY_CORE0);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    pObj->lock = BspOsal_semCreate(1u, TRUE);

    /* Set mapping of RTI modules to different cores */
    for(i = 0U; i < RTI_LINK_NUM_RTI_MODULES; i++)
    {
        rti_getClkVal(gRtiModuleBaseAddr[i]);
        pObj->rtiHwiHandle[i]      = NULL;
        pObj->rtiExpired[i]        = FALSE;
        pObj->procMap[i]           = SYSTEM_PROC_MAX;
        pObj->rtiMonitorEnabled[i] = FALSE;
    }
    pObj->rtiServiceEnabled = FALSE;

    /* Following cores are not supported in Vision SDK
     * EVE is not supported since we need external timer for BIOS clock-ticks
     * due to the power-management implementation and current BIOS does not
     * support this.
     * One workaround for EVE is polling on registers - therefore RTI
     * task must be at minimum priority on EVE. Current priority setting of RTI
     * tasks will prevent LOGS from EVE
     * IPU1_C1 not supported since no algorithms run here.
     */
    pObj->procMap[1] = SYSTEM_PROC_IPU1_0;
    pObj->procMap[2] = SYSTEM_PROC_DSP1;
    pObj->procMap[3] = SYSTEM_PROC_DSP2;
    pObj->procMap[4] = SYSTEM_PROC_EVE1;

    rti_registerInterrupts(pObj);

    status = System_linkControl(
        pObj->tskId,
        SYSTEM_CMD_CREATE,
        NULL,
        0,
        TRUE);
    UTILS_assert(0 == status);
}

/**
 *  \brief Delete the RTI link task
 */
Int32 System_rtiDeinit()
{
    Int32 status;

    status = System_linkControl(
        gRtiLink_obj.tskId,
        SYSTEM_CMD_DELETE,
        NULL,
        0,
        TRUE);
    UTILS_assert(0 == status);

    BspOsal_semDelete(&gRtiLink_obj.lock);
    Utils_tskDelete(&gRtiLink_obj.tsk);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *  \brief Enable RTI WWDT handling and monitoring on all cores
 *         Should be called only from IPU1_C0
 */
Int32 System_rtiEnableAll()
{
    Int32  retVal;
    UInt32 selfProcId = System_getSelfProcId();
    if(SYSTEM_PROC_IPU1_0 == selfProcId)
    {
        retVal = rti_enableRtiLink(TRUE);
    }
    return retVal;
}

/**
 *  \brief Disable RTI WWDT handling and monitoring on all cores
 *         Should be called only from IPU1_C0
 */
Int32 System_rtiDisableAll()
{
    Int32  retVal;
    UInt32 selfProcId = System_getSelfProcId();
    if(SYSTEM_PROC_IPU1_0 == selfProcId)
    {
        retVal = rti_enableRtiLink(FALSE);
    }
    return retVal;
}
