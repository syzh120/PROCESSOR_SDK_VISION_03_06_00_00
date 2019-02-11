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
 *
 * \file hdvicp2_config.c
 *
 * \brief  This file contains device level configuration information for IVA-HD.
 *         Used for HDVICP PRCM and Reset
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 * \version 0.1 (Jul 2014) : [SS] Second version
 *
 *******************************************************************************
 */

/****************************************************************
*  INCLUDE FILES
****************************************************************/
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <ti/sysbios/hal/Hwi.h>
#include <src/rtos/utils_common/include/utils.h>
#include <ti/ipc/remoteproc/Resource.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>

/****************************************************************
*  DEFINES
****************************************************************/

/* Enable this to get the debug prints for IVA PRCM */
//#define SYSTEM_DEBUG_IVA_PRCM_IVA_PRCM

#define IVAHD_REG(off)            (*(volatile unsigned int *)(0x4AE06F00 + (off)))

#define PM_IVAHD_PWRSTCTRL        IVAHD_REG(0x00)
#define RM_IVAHD_RSTCTRL          IVAHD_REG(0x10)
#define RM_IVAHD_RSTST            IVAHD_REG(0x14)

#define CM_IVAHD_CLKSTCTRL        (*(volatile unsigned int *)0x4A008F00)
#define CM_IVAHD_CLKCTRL          (*(volatile unsigned int *)0x4A008F20)
#define CM_IVAHD_SL2_CLKCTRL      (*(volatile unsigned int *)0x4A008F28)
#define CM_DIV_DPLL_IVA           (*(volatile unsigned int *)0x4A0051B0)
#define IVAHD_CONFIG_REG_BASE     (0x5A000000)

#define ICONT1_ITCM_BASE          (IVAHD_CONFIG_REG_BASE + 0x08000)
#define ICONT2_ITCM_BASE          (IVAHD_CONFIG_REG_BASE + 0x18000)

#define  HDVICP_NUM_RESOURCES     (1)


/*******************************************************************************
 *   Hex code to set for Stack setting, Interrupt vector setting
 *   and instruction to put ICONT in WFI mode.
 *   This shall be placed at TCM_BASE_ADDRESS of given IVAHD, which is
 *   0x0000 locally after reset.
 *******************************************************************************/

const unsigned int    icont_boot[] =
{
    0xEA000006,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xEAFFFFFE,
    0xE3A00000,
    0xEE070F9A,
    0xEE070F90,
    0xE3A00000,
    0xEAFFFFFE,
    0xEAFFFFF1
};

static void ivahd_boot(void)
{
    int                      i;
    volatile unsigned int   *icont1_itcm_base_addr =
        (unsigned int *)ICONT1_ITCM_BASE;
    volatile unsigned int   *icont2_itcm_base_addr =
        (unsigned int *)ICONT2_ITCM_BASE;

    /*
     * Reset IVA HD, SL2 and ICONTs
     */
#ifdef SYSTEM_DEBUG_IVA_PRCM
    Vps_printf(" IVA_PRCM: IVA_PRCM: Booting IVAHD...Start!!!");
#endif

    /* Sequence
     * Apply Reset (0xAA306F10 = 0x7)
     * Turn IVA power state to on (0xAA306F00 = 0x3)
     * Set CM to SW WKUP (0xAA008F00 = 0x2)
     * Set IVA CLK to Auto (0xAA008F20 = 0x1)
     * Set SL2 CLK to Auto (0xAA008F28 = 0x1)
     * Apply reset to ICONT1 and ICONT2 and remove SL2 reset (0xAA306F10 = 0x3)
     * Code load ICONTs
     * Release Reset for ICONT1 and ICONT2 (0xAA306F10 = 0x0)
    */

    RM_IVAHD_RSTCTRL = 0x00000007;
    BspOsal_sleep(10);

    /*POWERSTATE : IVAHD_PRM:PM_IVAHD_PWRSTCTRL*/
    PM_IVAHD_PWRSTCTRL = 0x00000003;
    BspOsal_sleep(10);

    /*IVAHD_CM2:CM_IVAHD_CLKSTCTRL = SW_WKUP*/
    CM_IVAHD_CLKSTCTRL = 0x00000002;
    BspOsal_sleep(10);

    /*IVAHD_CM2:CM_IVAHD_IVAHD_CLKCTRL*/
    CM_IVAHD_CLKCTRL= 0x00000001;
    BspOsal_sleep(10);

    /*IVAHD_CM2:CM_IVAHD_SL2_CLKCTRL*/
    CM_IVAHD_SL2_CLKCTRL = 0x00000001;
    BspOsal_sleep(10);

    /* put ICONT1 & ICONT2 in reset and remove SL2 reset */
#ifdef SYSTEM_DEBUG_IVA_PRCM
    Vps_printf(" IVA_PRCM:Putting [ICONT1 ICONT2]: RESET and SL2:OutOfRESET...");
#endif

    RM_IVAHD_RSTCTRL = 0x00000003;
    BspOsal_sleep(10);

    /* Copy boot code to ICONT1 & ICONT2 memory */
    for( i = 0; i < (sizeof(icont_boot) / sizeof(unsigned int)); i++ ) {
        *icont1_itcm_base_addr++ = icont_boot[i];
        *icont2_itcm_base_addr++ = icont_boot[i];
    }
    // *icont1_itcm_base_addr = 0xEAFFFFFE;
    // *icont2_itcm_base_addr = 0xEAFFFFFE;

    BspOsal_sleep(10);

    RM_IVAHD_RSTCTRL = 0x00000000;
    BspOsal_sleep(10);

    /*Read1 IVAHD_ROOT_CLK is running or gatng/ungating transition is on-going*/
#ifdef SYSTEM_DEBUG_IVA_PRCM
    Vps_printf(" IVA_PRCM:Waiting for IVAHD to go out of reset\n");
#endif

    while(((CM_IVAHD_CLKSTCTRL) & 0x100) & ~0x100 ) {
        ;
    }

#ifdef SYSTEM_DEBUG_IVA_PRCM
    Vps_printf(" IVA_PRCM:Booting IVAHD...Done!!!");
#endif

}

static int    ivahd_use_cnt = 0;

void ivahd_acquire(void)
{
    UInt    hwiKey = Hwi_disable();

    if( ++ivahd_use_cnt == 1 ) {
#ifdef SYSTEM_DEBUG_IVA_PRCM
        Vps_printf(" IVA_PRCM: ivahd acquire");
#endif
        /* switch SW_WAKEUP mode */
        CM_IVAHD_CLKSTCTRL = 0x00000002;
    } else {
#ifdef SYSTEM_DEBUG_IVA_PRCM
        Vps_printf(" IVA_PRCM: ivahd already acquired");
#endif
    }
    Hwi_restore(hwiKey);
}

void ivahd_release(uint32_t swWkupFlag)
{
    UInt    hwiKey = Hwi_disable();

    if( ivahd_use_cnt-- == 1 ) {
#ifdef SYSTEM_DEBUG_IVA_PRCM
        Vps_printf(" IVA_PRCM: ivahd release");
#endif
        if (swWkupFlag == 0U)
        {
            /* switch HW_AUTO mode */
            CM_IVAHD_CLKSTCTRL = 0x00000003;
        }
        else
        {
            /* switch SW_WAKEUP mode */
            CM_IVAHD_CLKSTCTRL = 0x00000002;
        }
    } else {
#ifdef SYSTEM_DEBUG_IVA_PRCM
        Vps_printf(" IVA_PRCM: ivahd still in use");
#endif
    }
    Hwi_restore(hwiKey);
}

Void HDVICP2_Init(void)
{
    pmErrCode_t retVal       = PM_SUCCESS;
    uint32_t clkRate = 0U;
    uint32_t swWkupFlag = 0U;
    retVal = PMLIBClkRateGet(PMHAL_PRCM_MOD_IVA, PMHAL_PRCM_CLK_GENERIC,
            &clkRate);
    /* If the clock rate is equal to 617 MHz then need to make sure the clock
     * is dialed to 532 MHz and then the PRCM transitions should be performed.
     * The IVA is kept in SW_WKUP if the IVA frequency is 617MHz to avoid
     * PRCM transitions.
     */
    if ((retVal == PM_SUCCESS) && (clkRate == 617000000U))
    {
        static pmhalPrcmPllPostDivValue_t dpllIvaPostDivCfgOppHigh_20[] =
        {
            {PMHAL_PRCM_DPLL_POST_DIV_M2, 2}, /* Div_m2_clkcfg */
        };
        pmhalPrcmDpllConfig_t      dpllIvaCfgOppHigh_20 =
        {
            266,
            4,
            0,
            dpllIvaPostDivCfgOppHigh_20,
            (sizeof (dpllIvaPostDivCfgOppHigh_20) / sizeof (pmhalPrcmPllPostDivValue_t)),
            0
        };
        retVal = (pmErrCode_t) PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_IVA,
                                   &dpllIvaCfgOppHigh_20,
                                   PM_TIMEOUT_INFINITE);
        swWkupFlag = 1U;
    }
    if (retVal == PM_SUCCESS)
    {
        ivahd_acquire();
        ivahd_boot();
        ivahd_release(swWkupFlag);
    }
    /* PRCM transitions are now complete. Switch back to 617 MHz */
    if ((retVal == PM_SUCCESS) && (clkRate == 617000000U))
    {
        pmhalPrcmPllPostDivValue_t dpllIvaPostDivCfgOppPlus_20[] =
        {
            {PMHAL_PRCM_DPLL_POST_DIV_M2, 2}, /* Div_m2_clkcfg */
        };
        pmhalPrcmDpllConfig_t      dpllIvaCfgOppPlus_20 =
        {
            617,
            9,
            0,
            dpllIvaPostDivCfgOppPlus_20,
            (sizeof (dpllIvaPostDivCfgOppPlus_20) / sizeof (pmhalPrcmPllPostDivValue_t)),
            0
        };
        retVal = (pmErrCode_t) PMHALCMDpllConfigure(PMHAL_PRCM_DPLL_IVA,
                                   &dpllIvaCfgOppPlus_20,
                                   PM_TIMEOUT_INFINITE);
    }
}

extern UInt ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[];

Void HDVICP2_ClearIVAInterrupts(void)
{
    Int i;

    for (i = 0; i < HDVICP_NUM_RESOURCES; i++)
    {
        Hwi_clearInterrupt(ti_sdo_fc_ires_hdvicp_HDVICP2_interrupts[i]);
    }
}

#ifdef A15_TARGET_OS_LINUX

static unsigned int SyslinkMemUtils_VirtToPhys(Ptr Addr)
{
    unsigned int    pa;

    if( !Addr || Resource_virtToPhys((unsigned int) Addr, &pa)) {
        return (0);
    }
    return (pa);
}

void *MEMUTILS_getPhysicalAddr(Ptr vaddr)
{
    unsigned int    paddr = SyslinkMemUtils_VirtToPhys(vaddr);

    return ((void *)paddr);
}

#endif

/* Nothing beyond this point */


