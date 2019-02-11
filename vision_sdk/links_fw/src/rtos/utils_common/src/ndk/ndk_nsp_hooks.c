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

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *   \file  ndk_nsp_hooks.c
 *
 *   \brief Do all necessary board level initialization for NDK.
 *
 *******************************************************************************
 */


/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

/* Standard language headers */
#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

/* OS/Posix headers */

/* NDK Dependencies */
#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/_stack.h>
#include <ti/ndk/inc/tools/servers.h>
#include <ti/ndk/inc/tools/console.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw.h>
#include <ti/nsp/drv/inc/gmacsw_config.h>

/* Project dependency headers */
#include <src/rtos/utils_common/include/utils.h>
#include <include/link_api/systemLink_common.h>
#include <include/link_api/networkCtrl_api.h>

#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define CPDMA_BUFFDESC_DDR_MEM (1)
#define GMACSW_CPDMA_BUF_DESC_COUNT  (512U)

#if (defined(CPDMA_BUFFDESC_DDR_MEM) && defined(BOARD_TYPE_TDA2EX_EVM))
/*! CPDMA descriptor memory. Make sure this is non-cached region */
#if defined(__GNUC__)
CPDMA_BuffDesc cpdmaBuffDescMem[GMACSW_CPDMA_BUF_DESC_COUNT]__attribute__(( aligned(128), section(".bss:CPDMA_BUFFDESC") ));
#else
#pragma DATA_ALIGN(cpdmaBuffDescMem, 128);
#pragma DATA_SECTION(cpdmaBuffDescMem, ".bss:CPDMA_BUFFDESC")
CPDMA_BuffDesc cpdmaBuffDescMem[GMACSW_CPDMA_BUF_DESC_COUNT];
#endif
#endif

#define NET_IF_IDX  (1)

/* Ethernet MAC ID registers(Devcice configuration) from EFuse */
#define MAC_ID0_LO              (*(volatile uint32_t*)0x4A002514)
#define MAC_ID0_HI              (*(volatile uint32_t*)0x4A002518)
#define MAC_ID1_LO              (*(volatile uint32_t*)0x4A00251C)
#define MAC_ID1_HI              (*(volatile uint32_t*)0x4A002520)

/* I/O Delay related registers */
#define CFG_IO_DELAY_UNLOCK_KEY     (0x0000AAAA)
#define CFG_IO_DELAY_LOCK_KEY       (0x0000AAAB)

#define CFG_IO_DELAY_ACCESS_PATTERN (0x00029000)
#define CFG_IO_DELAY_LOCK_MASK      (0x400)

#define CFG_IO_DELAY_BASE           (0x4844A000)
#define CFG_IO_DELAY_LOCK           (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0x02C))
#define CFG_RGMII0_TXCTL_OUT        (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0x74C))
#define CFG_RGMII0_TXD0_OUT         (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0x758))
#define CFG_RGMII0_TXD1_OUT         (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0x764))
#define CFG_RGMII0_TXD2_OUT         (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0x770))
#define CFG_RGMII0_TXD3_OUT         (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0x77C))
#define CFG_VIN2A_D13_OUT           (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0xA7C))
#define CFG_VIN2A_D17_OUT           (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0xAAC))
#define CFG_VIN2A_D16_OUT           (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0xAA0))
#define CFG_VIN2A_D15_OUT           (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0xA94))
#define CFG_VIN2A_D14_OUT           (*(volatile uint32_t*)(CFG_IO_DELAY_BASE + 0xA88))

/* PAD Configuration Registers */
#define SYSCFG_PAD_RGMII0_TXCTL     (*(volatile uint32_t*)(0x4A003654))
#define SYSCFG_PAD_RGMII0_TXD3      (*(volatile uint32_t*)(0x4A003658))
#define SYSCFG_PAD_RGMII0_TXD2      (*(volatile uint32_t*)(0x4A00365C))
#define SYSCFG_PAD_RGMII0_TXD1      (*(volatile uint32_t*)(0x4A003660))
#define SYSCFG_PAD_RGMII0_TXD0      (*(volatile uint32_t*)(0x4A003664))
#define SYSCFG_PAD_VIN2A_D13        (*(volatile uint32_t*)(0x4A00359C))
#define SYSCFG_PAD_VIN2A_D14        (*(volatile uint32_t*)(0x4A0035A0))
#define SYSCFG_PAD_VIN2A_D15        (*(volatile uint32_t*)(0x4A0035A4))
#define SYSCFG_PAD_VIN2A_D16        (*(volatile uint32_t*)(0x4A0035A8))
#define SYSCFG_PAD_VIN2A_D17        (*(volatile uint32_t*)(0x4A0035AC))

#define CTRL_MODULE_CTRL_CORE_SMA_SW_1 (*(volatile uint32_t*) (0x4A002534))

#if ( defined (BOARD_TYPE_TDA3XX_RVP) || \
      defined (BOARD_TYPE_TDA2PX_EVM) || \
      defined (BOARD_TDA2XX_CASCADE_RADAR) || \
      defined (BOARD_TYPE_TDA2EX_EVM) )
/* DP83867IR Register details for delay configuration */
#define DP83867_CTRL         (0x1FU)
#define DP83867_RGMIICTL     (0x0032U)
#define DP83867_RGMIIDCTL    (0x0086U)
#define DP83867_IO_MUX_CTRL  (0x0170U)
/* PHY CTRL bits */
#define DP83867_SW_RESET    (15)
#define DP83867_SW_RESTART  (14)
#define DP83867_PHYCR_FIFO_DEPTH_3_B_NIB    (0x00U)
#define DP83867_PHYCR_FIFO_DEPTH_4_B_NIB    (0x01U)
#define DP83867_PHYCR_FIFO_DEPTH_6_B_NIB    (0x02U)
#define DP83867_PHYCR_FIFO_DEPTH_8_B_NIB    (0x03U)
/* RGMIIDCTL internal delay for rx and tx */
#define DP83867_RGMIIDCTL_250_PS     (0x0U)
#define DP83867_RGMIIDCTL_500_PS     (0x1U)
#define DP83867_RGMIIDCTL_750_PS     (0x2U)
#define DP83867_RGMIIDCTL_1_NS       (0x3U)
#define DP83867_RGMIIDCTL_1_25_NS    (0x4U)
#define DP83867_RGMIIDCTL_1_50_NS    (0x5U)
#define DP83867_RGMIIDCTL_1_75_NS    (0x6U)
#define DP83867_RGMIIDCTL_2_00_NS    (0x7U)
#define DP83867_RGMIIDCTL_2_25_NS    (0x8U)
#define DP83867_RGMIIDCTL_2_50_NS    (0x9U)
#define DP83867_RGMIIDCTL_2_75_NS    (0xaU)
#define DP83867_RGMIIDCTL_3_00_NS    (0xbU)
#define DP83867_RGMIIDCTL_3_25_NS    (0xcU)
#define DP83867_RGMIIDCTL_3_50_NS    (0xdU)
#define DP83867_RGMIIDCTL_3_75_NS    (0xeU)
#define DP83867_RGMIIDCTL_4_00_NS    (0xfU)
#endif

#if  defined(TDA2EX_ETHSRV_BOARD)
#define TDA2EX_ETHSRVSWITCH_SMI_CMD                   (0x0)
#define TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIBUSY           (15)
#define TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIMODE           (12)
#define TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIOP             (10)
#define TDA2EX_ETHSRVSWITCH_SMI_CMD_DEVADDR           (5)
#define TDA2EX_ETHSRVSWITCH_SMI_CMD_REGADDR           (0)

#define TDA2EX_ETHSRVSWITCH_SMI_DATA                  (0x01)
#define TDA2EX_ETHSRVSWITCH_SWITCH_ID                 (0x03)
#define TDA2EX_ETHSRVSWITCH_GLB1                      (0x1B)
#define TDA2EX_ETHSRVSWITCH_SWITCH_GLB_STAT           (0x00)
#define TDA2EX_ETHSRVSWITCH_SWITCH_GLB_STAT_INITSTATE (15)
#define TDA2EX_ETHSRVSWITCH_SWITCH_GLB_STAT_INITREADY (11)
#define TDA2EX_ETHSRVSWITCH_GLB_CTRL2                 (0x1C)
#define TDA2EX_ETHSRVSWITCH_GLB_CTRL2_DACHECK         (11)
#define TDA2EX_ETHSRVSWITCH_GLB_CTRL2_RMUMODE         (8)
#define TDA2EX_ETHSRVSWITCH_GLB2                      (0x1C)
#define TDA2EX_ETHSRVSWITCH_PHY_CTRL                  (0x01)
#define TDA2EX_ETHSRVSWITCH_PHY_CTRL_RXTIMING         (15)
#define TDA2EX_ETHSRVSWITCH_PHY_CTRL_TXTIMING         (14)

#define TDA2EX_ETHSRVSWITCH_VLAN_MAP 0x06
#define TDA2EX_ETHSRVSWITCH_FORCE_MAP 0x800

#define WR_MEM_32(addr, data)    *(volatile unsigned int *)(addr) =(unsigned int)(data)
#define RD_MEM_32(addr)          *(volatile unsigned int *)(addr)
/*
 * MDIO base address and register offsets. This is needed for direct access to
 * MDIO without NSP
 */
#define MDIOBASE                0x48485000
#define MDIO_USERACCESS0        0x80
#define MDIO_USERPHYSEL0        0x84

#define USERACCESS_GO           0x80000000
#define USERACCESS_READ         0x00000000
#define USERACCESS_WRITE        0x40000000
#define USERACCESS_DATA         0x0000ffff

volatile UInt32 gConfiguredSwitchDelays = 0U;
void Tda2Ex_EthSrvConfigureSwitchDelays(uint32_t portNum);
#endif


/*******************************************************************************
 *  Function's
 *******************************************************************************
 */
static void LOCAL_linkStatus( uint32_t phy, uint32_t linkStatus );
static void LOCAL_phyFoundCb(uint32_t portNum, uint32_t phy);
void LOCAL_disableRGMIIInternalDelays(void);
void stackInitHookStaticEth1(void *hCfg);
void stackInitHookDynEth1(void *hCfg);

/*******************************************************************************
 *  Global's
 *******************************************************************************
 */

/* This string array corresponds to link state */
static char *LinkStr[] = { "No Link",
                           "None",
                           "10Mb/s Half Duplex",
                           "10Mb/s Full Duplex",
                           "100Mb/s Half Duplex",
                           "100Mb/s Full Duplex",
                           "1000Mb/s Half Duplex", /*not suported*/
                           "1000Mb/s Full Duplex"};


/**
 *******************************************************************************
 *
 * \brief HW specific initialization
 *
 *        We changed our CFG file to point call this private init
 *        function. Here we initialize our board and read in our
 *        MAC address.
 *
 *******************************************************************************
 */

void NDK_NSP_Init( void )
{
#if (defined(TDA2XX_FAMILY_BUILD) &&    \
    (defined(BOARD_TYPE_TDA2XX_EVM) ||  \
     defined(BOARD_TYPE_TDA2XX_RVP) ||  \
     defined(BOARD_TYPE_TDA2EX_EVM) ||  \
     defined(BOARD_TYPE_TDA2PX_EVM)))

    uint32_t enableIODelayFlag, regValue;
    uint32_t siliconRev = PlatformGetSiliconRev();

    /*
     * We do I/O delay adjustments only if GMAC internal delays are enabled.
     * With TDA2xx & TDA2EX PG2.0 the option of disabling internal delays is
     * added. SBL will disable the internal delays if siliconRev is PG2.0 so no need
     * to adjust I/O delay here.
     * NOTE: For TDA2 PG2.0 silicon revision is 2 but for TDA2EX PG2.0 silicon
     * revision is 1 so we need to make decision to disbale delays based on
     * plaform build
     */
#if (defined (TDA2EX_BUILD))
    if (siliconRev >= 1U)
    {
        enableIODelayFlag = (uint32_t)FALSE;
    }
#elif (defined(TDA2PX_BUILD))
        enableIODelayFlag = (uint32_t)FALSE;
#else
    if (siliconRev >= 2U)
    {
        enableIODelayFlag = (uint32_t)FALSE;
#if !defined(BOARD_TDA2XX_CASCADE_RADAR)
        LOCAL_disableRGMIIInternalDelays();
#endif
    }
    else
    {
        enableIODelayFlag = (uint32_t)TRUE;
    }
#endif

    if ((uint32_t)FALSE != enableIODelayFlag)
    {
        uint32_t delta, coarse, fine;

        /*
        * Adjust I/O delays on the Tx control and data lines of each MAC port. This is
        * a workaround in order to work properly with the DP83865 PHYs on the EVM. In 3COM
        * RGMII mode this PHY applies it's own internal clock delay, so we essentially need to
        * counteract the DRA7xx internal delay, and we do this by delaying the control and
        * data lines. If not using this PHY, you probably don't need to do this stuff!
        */

        /* Global unlock for I/O Delay registers */
        CFG_IO_DELAY_LOCK = CFG_IO_DELAY_UNLOCK_KEY;

        /* Tweaks to RGMII0 Tx Control and Data */
        CFG_RGMII0_TXCTL_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_RGMII0_TXCTL = (SYSCFG_PAD_RGMII0_TXCTL & ~0xF) | 0x0;
        delta       = (0x3 << 5) + 0x8;     /* Delay value to add to calibrated value */
        regValue    = CFG_RGMII0_TXCTL_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_RGMII0_TXCTL_OUT = regValue;

        CFG_RGMII0_TXD0_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_RGMII0_TXD0 = (SYSCFG_PAD_RGMII0_TXD0 & ~0xF) | 0x0;
        delta       = (0x3 << 5) + 0x8;     /* Delay value to add to calibrated value */
        regValue    = CFG_RGMII0_TXD0_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_RGMII0_TXD0_OUT = regValue;

        CFG_RGMII0_TXD1_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_RGMII0_TXD1 = (SYSCFG_PAD_RGMII0_TXD1 & ~0xF) | 0x0;
        delta       = (0x3 << 5) + 0x2;     /* Delay value to add to calibrated value */
        regValue    = CFG_RGMII0_TXD1_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_RGMII0_TXD1_OUT = regValue;

        CFG_RGMII0_TXD2_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_RGMII0_TXD2 = (SYSCFG_PAD_RGMII0_TXD2 & ~0xF) | 0x0;
        delta       = (0x4 << 5) + 0x0;     /* Delay value to add to calibrated value */
        regValue    = CFG_RGMII0_TXD2_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_RGMII0_TXD2_OUT = regValue;

        CFG_RGMII0_TXD3_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_RGMII0_TXD3 = (SYSCFG_PAD_RGMII0_TXD3 & ~0xF) | 0x0;
        delta       = (0x4 << 5) + 0x0;     /* Delay value to add to calibrated value */
        regValue    = CFG_RGMII0_TXD3_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_RGMII0_TXD3_OUT = regValue;

        /* Tweaks to RGMII1 Tx Control and Data */
        CFG_VIN2A_D13_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_VIN2A_D13 = (SYSCFG_PAD_VIN2A_D13 & ~0xF) | 0x3;
        delta       = (0x3 << 5) + 0x8;     /* Delay value to add to calibrated value */
        regValue    = CFG_VIN2A_D13_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_VIN2A_D13_OUT = regValue;

        CFG_VIN2A_D17_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_VIN2A_D17 = (SYSCFG_PAD_VIN2A_D17 & ~0xF) | 0x3;
        delta       = (0x3 << 5) + 0x8;
        regValue    = CFG_VIN2A_D17_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_VIN2A_D17_OUT = regValue;

        CFG_VIN2A_D16_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_VIN2A_D16 = (SYSCFG_PAD_VIN2A_D16 & ~0xF) | 0x3;
        delta       = (0x3 << 5) + 0x2;
        regValue    = CFG_VIN2A_D16_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_VIN2A_D16_OUT = regValue;

        CFG_VIN2A_D15_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_VIN2A_D15 = (SYSCFG_PAD_VIN2A_D15 & ~0xF) | 0x3;
        delta       = (0x4 << 5) + 0x0;
        regValue    = CFG_VIN2A_D15_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_VIN2A_D15_OUT = regValue;

        CFG_VIN2A_D14_OUT = (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
        SYSCFG_PAD_VIN2A_D14 = (SYSCFG_PAD_VIN2A_D14 & ~0xF) | 0x3;
        delta       = (0x4 << 5) + 0x0;
        regValue    = CFG_VIN2A_D14_OUT & ~0xFFFFFC00;
        coarse      = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
        coarse      = (coarse > 0x1F) ? (0x1F) : (coarse);
        fine        = (regValue & 0x1F) + (delta & 0x1F);
        fine        = (fine > 0x1F) ? (0x1F) : (fine);
        regValue    = CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5) | (fine));
        CFG_VIN2A_D14_OUT = regValue;

        /* Global lock */
        CFG_IO_DELAY_LOCK = CFG_IO_DELAY_LOCK_KEY;
    }
#endif

}

/**
 *******************************************************************************
 *
 * \brief Callback to get GMAC HW config
 *
 *        This is a callback from the Ethernet driver. This function
 *        is used by the driver to an application-specific config structure
 *        for the GMACSW driver. Typically it will be used to provide the
 *        MAC address(es) and the link status update callback function.
 *
 *******************************************************************************
 */
GMACSW_Config *GMACSW_getConfig(void)
{
    uint32_t i = 0;
    uint8_t macAddr[6];
    uint32_t siliconRev = PlatformGetSiliconRev();

    /* Get digital loopback starting config */
    GMACSW_Config *pGMACSWConfig = NULL;

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    pGMACSWConfig = GMACSW_CONFIG_getDefaultConfig();
    #if ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) && defined(BOARD_TYPE_TDA2EX_EVM))
        #if CPDMA_BUFFDESC_DDR_MEM
        pGMACSWConfig->cpdmaInitCfg.buffDescMemCfg.buffDescCnt = GMACSW_CPDMA_BUF_DESC_COUNT;
        pGMACSWConfig->cpdmaInitCfg.buffDescMemCfg.buffDescMem = &(cpdmaBuffDescMem[0]);
        #endif
    #endif
#endif

    if(NULL != pGMACSWConfig)
    {
        pGMACSWConfig->activeMACPortMask = PORT_MASK_MAC_BOTH;
        /* Update default config with the correct MAC addresses */
        for(i=0U; i<MAC_NUM_PORTS; i++)
        {
            if( ((uint32_t)1U << i) & (uint32_t)pGMACSWConfig->activeMACPortMask )
            {
                if (0U==i)
                {
                    /* Get the MAC Address from control module register space */
                    macAddr[5] = (uint8_t)((MAC_ID0_LO & 0x000000FFu) >> 0u );
                    macAddr[4] = (uint8_t)((MAC_ID0_LO & 0x0000FF00u) >> 8u );
                    macAddr[3] = (uint8_t)((MAC_ID0_LO & 0x00FF0000u) >> 16u);

                    macAddr[2] = (uint8_t)((MAC_ID0_HI & 0x000000FFu) >> 0u );
                    macAddr[1] = (uint8_t)((MAC_ID0_HI & 0x0000FF00u) >> 8u );
                    macAddr[0] = (uint8_t)((MAC_ID0_HI & 0x00FF0000u) >> 16u);
                }
                else
                {
                    /* Get the MAC Address from control module register space */
                    macAddr[5] = (uint8_t)((MAC_ID1_LO & 0x000000FFu) >> 0u );
                    macAddr[4] = (uint8_t)((MAC_ID1_LO & 0x0000FF00u) >> 8u );
                    macAddr[3] = (uint8_t)((MAC_ID1_LO & 0x00FF0000u) >> 16u);

                    macAddr[2] = (uint8_t)((MAC_ID1_HI & 0x000000FFu) >> 0u );
                    macAddr[1] = (uint8_t)((MAC_ID1_HI & 0x0000FF00u) >> 8u );
                    macAddr[0] = (uint8_t)((MAC_ID1_HI & 0x00FF0000u) >> 16u);
                }

                printf("\nMAC Port %d Address:\n\t%02x-%02x-%02x-%02x-%02x-%02x\n", (int32_t)i,
                        macAddr[0], macAddr[1], macAddr[2],
                        macAddr[3], macAddr[4], macAddr[5]);

                /* Copy the correct MAC address into the driver config */
                memcpy( (void *)&(pGMACSWConfig->macInitCfg[i].macAddr[0]), (void *)&macAddr[0], 6U );

                #if (defined(TDA2XX_FAMILY_BUILD) &&    \
                    (defined(BOARD_TYPE_TDA2XX_EVM) ||  \
                     defined(BOARD_TYPE_TDA2EX_EVM) ||  \
                     defined(BOARD_TYPE_TDA2PX_EVM)))
                    /*
                     * Adjust the PHY mask numbers for the Vayu EVM. The first MAC
                     * port is connected to a PHY with address = 2, the second MAC
                     * port is connected to a PHY with address = 3.
                     */
                    #ifndef TDA2EX_BUILD
                        pGMACSWConfig->macInitCfg[i].phyMask = (uint32_t)((uint32_t)0x1 << (uint32_t)(2U + i));
                    #else
                        if (siliconRev >= 1U)
                        {
                            /*
                            *  For TDA2EX 2.0 EVM the PHY address is 2 for first PHY and 3 for second
                            *  PHY
                            */
                            pGMACSWConfig->macInitCfg[i].phyMask = (uint32_t)((uint32_t)0x1 << (uint32_t)(2U + i));
                            #if  defined(TDA2EX_ETHSRV_BOARD)
                                if (i == 0U)
                                {
                                    Vps_printf(" Network: Set NOPHY Mode for RGMII0 \n");
                                    pGMACSWConfig->macInitCfg[i].mdioModeFlags = MDIO_MODEFLG_NOPHY;
                                }
                                else
                                {
                                    Vps_printf(" Network: Setting PHY_ADDR=0 for RGMII1\n");
                                    pGMACSWConfig->macInitCfg[i].phyMask = 1;
                                }
                            #endif
                        }
                        else
                        {
                            /*
                            *  For TDA2EX 1.0 EVM the PHY address is 8 for first PHY and 2 for second
                            *  PHY
                            */
                            pGMACSWConfig->macInitCfg[i].phyMask = (uint32_t)((uint32_t)0x8 >> (uint32_t)(i*2U));
                        }
                    #endif
                #elif defined (BOARD_TYPE_TDA2XX_RVP)
                      pGMACSWConfig->macInitCfg[i].phyMask = (uint32_t)((uint32_t)0x1 << (uint32_t)(1U - i));
                #endif

                #if defined(TDA3XX_FAMILY_BUILD)
                    #ifdef BOARD_TYPE_TDA3XX_RVP
                        /*
                         * Adjust the PHY mask numbers for the TDA3XX RVP. The first MAC
                         * port is connected to a PHY with address = 12, the second MAC
                         * port is connected to a PHY with address = 11.
                         */
                        pGMACSWConfig->macInitCfg[i].phyMask = (uint32_t)((uint32_t)0x1 << (uint32_t)(12U - i));
                    #else
                        /*
                         * Adjust the PHY mask numbers for TDA3xx EVM. The first MAC
                         * port is connected to a PHY with address = 0, the second MAC
                         * port is connected to a PHY with address = 1.
                         */
                        pGMACSWConfig->macInitCfg[i].phyMask = (uint32_t)((uint32_t)0x1 << (uint32_t)i);
                    #endif

                    pGMACSWConfig->macInitCfg[i].macConnectionType =
                            MAC_CONNECTION_TYPE_RGMII_DETECT_INBAND;
                #endif

                #if (defined(TDA2XX_FAMILY_BUILD) &&    \
                    (defined(BOARD_TYPE_TDA2XX_EVM) ||  \
                     defined(BOARD_TYPE_TDA2XX_RVP) ||  \
                     defined(BOARD_TYPE_TDA2EX_EVM) ||  \
                     defined(BOARD_TYPE_TDA2PX_EVM)))
                    #ifdef TDA2EX_BUILD
                        siliconRev = PlatformGetSiliconRev();
                        if (siliconRev >= 1U)
                        {
                            #if  defined(TDA2EX_ETHSRV_BOARD)
                                /* Force gigabit full duplex because SWITCH doesn't support inband detection. */
                                pGMACSWConfig->macInitCfg[i].macConnectionType =
                                                   MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL;
                            #else
                                /*
                                * TDA2EX REVC EVM has DP83867 which supports inband detection.
                                */
                                pGMACSWConfig->macInitCfg[i].macConnectionType =
                                                 MAC_CONNECTION_TYPE_RGMII_DETECT_INBAND;
                            #endif
                        }
                        else
                        {
                            /*
                            * National PHY on TDA2EX Rev A/B EVM does not work with the default INBAND detection mode.
                            * It would seem the Rx clock from the PHY is not generated unless the Tx clock
                            * from the Vayu device is present. So set the mode to force 1Gbps to start.
                            */
                            pGMACSWConfig->macInitCfg[i].macConnectionType =
                                               MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL;
                        }
                    #else
                        #if defined (BOARD_TYPE_TDA2PX_EVM)
                        /*
                        * TDA2P EVM has DP83867 which supports inband detection.
                        */
                        pGMACSWConfig->macInitCfg[i].macConnectionType =
                                            MAC_CONNECTION_TYPE_RGMII_DETECT_INBAND;
                        #else
                        /*
                         * National PHY on Vayu EVM does not work with the default INBAND detection mode.
                         * It would seem the Rx clock from the PHY is not generated unless the Tx clock
                         * from the Vayu device is present. So set the mode to force 1Gbps to start.
                         */
                        pGMACSWConfig->macInitCfg[i].macConnectionType =
                                                MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL;
                        #endif
                    #endif
                #endif
            }
        }
        pGMACSWConfig->mdioCfg.phyFoundCallback = &LOCAL_phyFoundCb;
        pGMACSWConfig->linkStatusCallback = &LOCAL_linkStatus;
    }
    else 
    {
        /*do nothing, GMACSW_CONFIG_getDefaultConfig returned a NULL*/
    }
    /* Return the config */
    return pGMACSWConfig;
}

#if ( defined (BOARD_TYPE_TDA3XX_RVP) || \
      defined (BOARD_TYPE_TDA2PX_EVM) || \
      defined (BOARD_TDA2XX_CASCADE_RADAR) || \
      defined (BOARD_TYPE_TDA2EX_EVM) )
/**
 *******************************************************************************
 *
 * \brief PHY DP83867IR delay config function
 *
 *        This function is used for configuring the receive and transmit delays
 *        for DP83867IR PHY on TDA2EX PG 2.0 EVM (RevC).
 *        For PHY configuration, need to configure DP83867’s RGMII Control
 *        Register (RGMIICTL) for RGMII mode and RGMII Delay Control Register
 *        (RGMIIDCTL) for 0ns TX delay, 2.25ns RX delay. Set IO Drive Strength
 *        Register (IO_IMPEDANCE_CTRL) to maximum drive.
 *        NOTE: Call this function after NSP initialization as it requires GMAC
 *        handle to call GMAC IOCTL.
 *
 *******************************************************************************
 */
void DP83867_configurePhyDelays(GMACSW_DeviceHandle hGMACSW, uint32_t portNum)
{
        MDIO_rdWrphyRegIoctlCmd cmd;
        uint32_t regVal;
        cmd.portNum = portNum;

        /* PHY software reset */
        regVal = (1U << DP83867_SW_RESET);
        cmd.regAddr = DP83867_CTRL;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        /* Set RGMII Delay values: Tx delay 0 and Rx delay 2.25ns */
        regVal = 0x08;
        cmd.regAddr = DP83867_RGMIIDCTL;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        /* Enable RGMII and CLK delay bits */
        regVal = 0x0D1;
        cmd.regAddr = DP83867_RGMIICTL;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        /* Set Drive Strength bits */
        regVal = 0x61F;
        cmd.regAddr = DP83867_IO_MUX_CTRL;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        /* software restart */
        regVal = (1U << DP83867_SW_RESTART);
        cmd.regAddr = DP83867_CTRL;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));
}
#endif

#ifdef TDA3XX_AR12_ALPS
void Tda3x_Alps_Reconfig_Phy_BootStrap(GMACSW_DeviceHandle hGMACSW)
{
    MDIO_rdWrphyRegIoctlCmd cmd;
    uint32_t regVal, i;

    /* MAC port number */
    for (i = 0; i < MAC_NUM_PORTS; i++)
    {
        cmd.portNum = i;

        regVal = 0x3100;
        cmd.regAddr = 0; /* Hard code
                          * Phy bootstrap value in PHY control registers
                          */
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_PHY_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));
    }
}
#endif

/**
 *******************************************************************************
 * \brief String to displayed on telnet terminal
 *******************************************************************************
 */
char *VerStr = "\n\n **** Vision SDK **** \n\n";

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    static HANDLE hEcho = 0;
    static HANDLE hEchoUdp = 0;
    static HANDLE hData = 0;
    static HANDLE hNull = 0;
    static HANDLE hOob = 0;

#endif

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )
/**
 *******************************************************************************
 *
 * \brief IPv6 initialization callback function
 *
 *******************************************************************************
 */

#if defined(NDK_ENABLE_IPV6)
static void IPv6DADStatus(IP6N Address, unsigned short dev_index,
        unsigned char Status)
{
    char strIPAddress[40];

    /* Convert the IP Address to String Format. */
    inet_ntop(AF_INET6, &Address, strIPAddress, 40);

    /* Print the status of the address. */
    Vps_printf("  Network :Address %s on device %d is %s\n", strIPAddress, dev_index,
            (Status == 1) ? "UNIQUE" : "DUPLICATE");

    System_flush();

    return;
}
#endif
#endif
/**
 *******************************************************************************
 *
 * \brief Stack init hook function to configure the second mac port
 *
 *******************************************************************************
 */
void stackInitHookStaticEth1(void *hCfg)
{
    /*Static IP Address settings for interface 2*/
    const char *ip_addr_2 = "192.168.2.4";
    const char *ip_mask_2 = "255.255.255.0";
    const char *ip_gateway_2 = "192.168.2.1";

    CI_IPNET ip_net;
    CI_ROUTE route;
    /*Add IP Address for the interface 2*/
    ip_net.IPAddr = inet_addr(ip_addr_2);
    ip_net.IPMask = inet_addr(ip_mask_2);
    CfgAddEntry(hCfg, (uint32_t)CFGTAG_IPNET, 2U, 0U, (int32_t)sizeof(CI_IPNET), (UINT8 *)(void *)&ip_net, 0);

    /*Add gateway for interface 2*/
    bzero(&route, sizeof(route));
    route.IPDestAddr = 0;
    route.IPDestMask = 0;
    route.IPGateAddr = inet_addr(ip_gateway_2);
    CfgAddEntry(hCfg, (uint32_t)CFGTAG_ROUTE, 0U, 0U, (int32_t)sizeof(CI_ROUTE), (UINT8 *)(void *)&route, 0);

}

void stackInitHookDynEth1(void *hCfg)
{
    /*Add the setup for DHCP for interface 2*/
    CI_SERVICE_DHCPC dhcpc;
    static UINT8 DHCP_OPTIONS[] = { DHCPOPT_SUBNET_MASK };

    bzero(&dhcpc, sizeof(dhcpc));
    dhcpc.cisargs.Mode = 1U;
    dhcpc.cisargs.IfIdx = 2U;
    dhcpc.param.pOptions = DHCP_OPTIONS;
    dhcpc.param.len = 1;

    CfgAddEntry(hCfg, (uint32_t)CFGTAG_SERVICE, (uint32_t)CFGITEM_SERVICE_DHCPCLIENT, 0U, (int32_t)sizeof(dhcpc), (UINT8 *)(void *)&dhcpc, 0);
}
/**
 *******************************************************************************
 *
 * \brief NDK callback to start DEAMON services
 *
 *******************************************************************************
 */
void netOpenHook(void)
{

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    /* Create our local servers */
    hEcho = DaemonNew( SOCK_STREAMNC, 0, 7, dtask_tcp_echo,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
    hEchoUdp = DaemonNew( SOCK_DGRAM, 0, 7, dtask_udp_echo,
                          OS_TASKPRINORM, OS_TASKSTKNORM, 0, 1 );
    hData = DaemonNew( SOCK_STREAM, 0, 1000, dtask_tcp_datasrv,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
    hNull = DaemonNew( SOCK_STREAMNC, 0, 1001, dtask_tcp_nullsrv,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );
    hOob  = DaemonNew( SOCK_STREAMNC, 0, 999, dtask_tcp_oobsrv,
                       OS_TASKPRINORM, OS_TASKSTKNORM, 0, 3 );

    /* NetworkCtrl_init(); */

#if defined (NDK_ENABLE_IPV6)
    Error_Block eb;
    Int32 status;
    UInt32 dev_index = 1;

    /* Make sure Error_Block is initialized */
    Error_init(&eb);

    status = IPv6InterfaceInit(dev_index, IPv6DADStatus);
    if (status < 0) {
        Vps_printf("  Network: Error %d: failed to add IPv6 interface\n", status);
    }
#endif
#endif

}

/**
 *******************************************************************************
 *
 * \brief NDK callback to stop DEAMON services
 *
 *******************************************************************************
 */
void netCloseHook(void)
{

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    /* Kill any active console */
    /*ConsoleClose(); */
    /*NetworkCtrl_deInit(); */

#if defined (NDK_ENABLE_IPV6)

    Int32 status;
    UInt32 dev_index = 1;
    /* Enter the kernel Mode. */
    llEnter ();
    status = IPv6InterfaceDeInit(dev_index);
    llExit ();

    /* Were we able to deinitialize the stack? */
    if (status < 0)
    {
        Vps_printf(
                "  Network: Error - Unable to de-initialize the IPv6 stack on device %d\n",
                dev_index);
    }
    else
    {
        Vps_printf("  Network: IPv6 stack has been deinitialized on %d\n", dev_index);
    }
#endif

    DaemonFree(hOob);
    DaemonFree(hNull);
    DaemonFree(hData);
    DaemonFree(hEchoUdp);
    DaemonFree(hEcho);

#endif

}

/**
 *******************************************************************************
 *
 * \brief Print link status
 *
 *        This is a callback from the Ethernet driver. This function
 *        is called whenever there is a change in link state. The
 *        current PHY and current link state are passed as parameters.
 *
 *******************************************************************************
 */
static void LOCAL_linkStatus( uint32_t phy, uint32_t linkStatus )
{
    Vps_printf(" NDK: Link Status: %s on PHY %" PRIu32 "\n",LinkStr[linkStatus],phy);
}

/**
 *******************************************************************************
 *
 * \brief PHY Found callback
 *
 *        This is a callback from the Ethernet driver. This function
 *        is called when PHY is found at PHY mask. This can be used for PHY
 *        specific configuration.
 *
 *******************************************************************************
 */
static void LOCAL_phyFoundCb(uint32_t portNum, uint32_t phy)
{
    Vps_printf(" NSP GMAC: PHY %d Found on MAC Port %" PRIu32 "\n",phy, portNum);

#if ( defined(BOARD_TYPE_TDA2EX_EVM) || \
      defined(BOARD_TYPE_TDA2PX_EVM) || \
      defined(BOARD_TYPE_TDA3XX_RVP) || \
      defined(BOARD_TDA2XX_CASCADE_RADAR) || \
      defined(TDA3XX_AR12_ALPS) )
    /* Configure Rx/Tx delays for DP83867IR (on PG2.0 J6ECO EVM) */
    GMACSW_DeviceHandle hGMACSW = GMACSW_open(NULL);
    if (hGMACSW != NULL)
    {

#if ( defined (BOARD_TYPE_TDA3XX_RVP) || \
      defined (BOARD_TYPE_TDA2PX_EVM) || \
      defined (BOARD_TYPE_TDA2EX_EVM) )

#ifdef BOARD_TYPE_TDA2EX_EVM
        /* For TDA2EX only SR2 EVM has DP83867 */
        if (PlatformGetSiliconRev() >= 1U)
#endif
        {
            /* Configure receive and transmit delays */
            DP83867_configurePhyDelays(hGMACSW, portNum);
        }
#endif

#ifdef TDA3XX_AR12_ALPS
    /* Configure the AR8031 Enthernet phy boot mode (on TDA3X Radar ALPS board) */
        Tda3x_Alps_Reconfig_Phy_BootStrap(hGMACSW);
#endif
#if defined (BOARD_TDA2XX_CASCADE_RADAR)
    /* Configure receive and transmit delays */
    DP83867_configurePhyDelays(hGMACSW, portNum);
#endif
        /* Now close the driver */
        if(0U != GMACSW_close(hGMACSW))
        {
            Vps_printf(" NDK: GMACSW Close Returned error" PRIu32 "\n");
        }
    }
    else
    {
        Vps_printf(" NDK: GMAC Open Failed \n");
    }
#endif

#if  defined(TDA2EX_ETHSRV_BOARD)
    /* Configure switch delays. We can call delay config function here as
     * we are using direct PHY access functions and dont use NSP IOCTLS */
    if (0U == gConfiguredSwitchDelays)
    {
        /*
         * HACK: Configure switch here as we need to make sure switch MDIO address is configured
         * by bsp_init.
         */
        Tda2Ex_EthSrvConfigureSwitchDelays(0);
        gConfiguredSwitchDelays = 1U;
    }
#endif
}

/* Disable RGMII Internal delays (RGMIIID). By default it is enabled */
void LOCAL_disableRGMIIInternalDelays(void)
{
    uint32_t regValue;
    /* Disable RGMII half cycle delay for ES2.0 silicon */
    regValue = CTRL_MODULE_CTRL_CORE_SMA_SW_1;
    /* Disable half cycle delay for RGMII0 */
    regValue |= ((UInt32)0x1U << 25U);
    /* Disable half cycle delay for RGMII1 */
    regValue |= ((UInt32)0x1U  << 26U);
    CTRL_MODULE_CTRL_CORE_SMA_SW_1 = regValue;
}

/**
 * \brief Return ID of processor on which networking runs
 */
UInt32 Utils_netGetProcId(void)
{
    UInt32 procId = SYSTEM_PROC_INVALID;

    #ifdef NDK_PROC_TO_USE_IPU1_0
    procId = SYSTEM_PROC_IPU1_0;
    #endif

    #ifdef NDK_PROC_TO_USE_IPU1_1
    procId = SYSTEM_PROC_IPU1_1;
    #endif

    #ifdef NDK_PROC_TO_USE_IPU2
    procId = SYSTEM_PROC_IPU2;
    #endif

    #ifdef NDK_PROC_TO_USE_A15_0
    procId = SYSTEM_PROC_A15_0;
    #endif

    return procId;
}

/**
 *******************************************************************************
 * \brief Retrun IP address as a string
 *
 *        If network stack is not initialized correctly 0.0.0.0 IP address
 *        is returned
 *
 * \param ipAddrStr [OUT] Assigned IP address as a string
 *
 *******************************************************************************
 */
void Utils_ndkGetIpAddrStr(char *ipAddrStr, UInt32 ifIdx)
{
    IPN ipAddr;

    memset(&ipAddr, 0, sizeof(ipAddr));

    strcpy(ipAddrStr,"none");

#if ( defined(NDK_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(NDK_PROC_TO_USE_IPU1_1) && defined(BUILD_M4_1) ) || \
    ( defined(NDK_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) ) || \
    ( defined(NDK_PROC_TO_USE_A15_0)  && defined(BUILD_A15) )

    NtIfIdx2Ip(ifIdx, &ipAddr);
    NtIPN2Str(ipAddr, ipAddrStr);

#endif

}

Int32 Utils_netGetIpAddrStr(char *ipAddr, UInt32 ifIdx)
{
    UInt32 linkId, procId;
    Int32 status;
    SystemCommon_IpAddr prm;

    prm.ifIdx = ifIdx;

    strcpy(ipAddr, "none" );

    procId = Utils_netGetProcId();

    if(procId==SYSTEM_PROC_INVALID)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        status = System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_GET_IP_ADDR,
            &prm,
            sizeof(prm),
            TRUE
        );

        if(status==SYSTEM_LINK_STATUS_SOK)
        {
            strcpy(ipAddr, prm.ipAddr);
        }
    }

    return status;
}

Bool Utils_netIsNetworkEnabled(void)
{
    Bool status = (Bool)FALSE;

#if ( defined(NDK_PROC_TO_USE_IPU1_0) ) ||\
    ( defined(NDK_PROC_TO_USE_IPU1_1) ) ||\
    ( defined(NDK_PROC_TO_USE_IPU2  ) ) ||\
    ( defined(NDK_PROC_TO_USE_A15_0 ) )

    status = (Bool)TRUE;

#endif

    return status;
}

#if  defined(TDA2EX_ETHSRV_BOARD)

void delay_mdio (uint32_t cnt)
{
        uint32_t i;
        for (i = 0; i < cnt; i++);
}

/* wait for go bit to 0 and ack bit to become 1 */
void wait_for_user_access ()
{
        uint32_t reg;
        reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x80000000;
        while (reg != 0x0)
        {
                delay_mdio (10000);
                delay_mdio (10000);
                reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x80000000;
        }
        reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x20000000;
        while (reg != 0x20000000)
        {
                delay_mdio (10000);
                delay_mdio (10000);
                reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0) & 0x20000000;
        }

}

uint32_t cpsw_mdio_read (unsigned char phy_reg, uint32_t PHY_ADDR)
{
        uint32_t reg = 0;
        reg =
                (USERACCESS_GO | USERACCESS_READ | (phy_reg << 21) | (PHY_ADDR << 16));
        WR_MEM_32 ((MDIOBASE + MDIO_USERACCESS0), reg);
        wait_for_user_access ();
        reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0);
        reg = reg & 0x0000ffff;
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
        Vps_printf (" Network: PHYREG READ VALUE =  %x \n", reg);
#endif
    return reg;
}

void cpsw_mdio_write (unsigned char phy_reg, unsigned short data, uint32_t PHY_ADDR)
{
        uint32_t reg = 0;
        reg =
                (USERACCESS_GO | USERACCESS_WRITE | (phy_reg << 21) | (PHY_ADDR << 16) |
                 (data & USERACCESS_DATA));
        WR_MEM_32 ((MDIOBASE + MDIO_USERACCESS0), reg);
        wait_for_user_access ();
        reg = RD_MEM_32 (MDIOBASE + MDIO_USERACCESS0);
        reg = reg & 0x0000ffff;
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
        Vps_printf (" Network: PHYREG WRITE VALUE  is  = %x \n", reg);
#endif
}

void Tda2Ex_EthSrvSwitch_reg_write(uint32_t portNum, uint32_t regAddr, uint32_t regVal)
{
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
    Vps_printf(" Network: REG 0x%02x WRITE 0x%x\n", regAddr, regVal);
#endif
    cpsw_mdio_write (regAddr, regVal, 0x3);
}

void Tda2Ex_EthSrvSwitch_reg_read(uint32_t portNum, uint32_t regAddr, uint32_t *regVal)
{
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
    Vps_printf(" Network: REG 0x%02x READ 0x%x\n", regAddr, *regVal);
#endif
    *regVal = cpsw_mdio_read(regAddr, 0x3);
}

void Tda2Ex_EthSrvSwitch_wait_for_access(uint32_t portNum, uint32_t *smi_regVal)
{
    do
    {
        Tda2Ex_EthSrvSwitch_reg_read(portNum, TDA2EX_ETHSRVSWITCH_SMI_CMD, smi_regVal);
    } while ((*smi_regVal & (1U << TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIBUSY)) != 0);
}

void Tda2Ex_EthSrvSwitch_dev_reg_write(uint32_t portNum, uint32_t devAddr, uint32_t regAddr, uint32_t regVal)
{
    uint32_t smi_regVal;

    Tda2Ex_EthSrvSwitch_wait_for_access(portNum, &smi_regVal);

    Tda2Ex_EthSrvSwitch_reg_write(portNum, TDA2EX_ETHSRVSWITCH_SMI_DATA, regVal);

    smi_regVal = (1U << TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIMODE)
                | (1U << TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIOP)
                | (devAddr << TDA2EX_ETHSRVSWITCH_SMI_CMD_DEVADDR)
                | (regAddr << TDA2EX_ETHSRVSWITCH_SMI_CMD_REGADDR);
    Tda2Ex_EthSrvSwitch_reg_write(portNum, TDA2EX_ETHSRVSWITCH_SMI_CMD, smi_regVal);

    smi_regVal |= (1U << TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIBUSY);
    Tda2Ex_EthSrvSwitch_reg_write(portNum, TDA2EX_ETHSRVSWITCH_SMI_CMD, smi_regVal);

    Tda2Ex_EthSrvSwitch_wait_for_access(portNum, &smi_regVal);
}

void Tda2Ex_EthSrvSwitch_dev_reg_read(uint32_t portNum, uint32_t devAddr, uint32_t regAddr, uint32_t *regVal)
{
    uint32_t smi_regVal;

    Tda2Ex_EthSrvSwitch_wait_for_access(portNum, &smi_regVal);

    smi_regVal = (1U << TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIMODE)
                | (2U << TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIOP)
                | (devAddr << TDA2EX_ETHSRVSWITCH_SMI_CMD_DEVADDR)
                | (regAddr << TDA2EX_ETHSRVSWITCH_SMI_CMD_REGADDR);
    Tda2Ex_EthSrvSwitch_reg_write(portNum, TDA2EX_ETHSRVSWITCH_SMI_CMD, smi_regVal);

    smi_regVal |= (1U << TDA2EX_ETHSRVSWITCH_SMI_CMD_SMIBUSY);
    Tda2Ex_EthSrvSwitch_reg_write(portNum, TDA2EX_ETHSRVSWITCH_SMI_CMD, smi_regVal);

    Tda2Ex_EthSrvSwitch_wait_for_access(portNum, &smi_regVal);

    Tda2Ex_EthSrvSwitch_reg_read(portNum, TDA2EX_ETHSRVSWITCH_SMI_DATA, regVal);
}


enum Tda2Ex_EthSrvSwitch_ports {
    TDA2EX_ETHSRVSWITCH_PORT0 = 0x1,
    TDA2EX_ETHSRVSWITCH_PORT1 = 0x2,
    TDA2EX_ETHSRVSWITCH_PORT2 = 0x4,
    TDA2EX_ETHSRVSWITCH_PORT3 = 0x8,
    TDA2EX_ETHSRVSWITCH_PORT4 = 0x10,
    TDA2EX_ETHSRVSWITCH_PORT5 = 0x20,
    TDA2EX_ETHSRVSWITCH_PORT6 = 0x40,
    TDA2EX_ETHSRVSWITCH_PORT7 = 0x80,
    TDA2EX_ETHSRVSWITCH_PORT8 = 0x100,
};


void Tda2Ex_EthSrvConfigureSwitchDelays(uint32_t portNum)
{
    uint32_t regVal, regValPrevious;
    int dev, reg;

    regVal = 0;
    regValPrevious = 0;

    Vps_printf(" Network: Enable RGMII half-cycle-delay for 0, disable for 1\n");
    uint32_t regValue;
    regValue = CTRL_MODULE_CTRL_CORE_SMA_SW_1;

    /* Enable half cycle delay for RGMII0 connected via MAC-to-MAC */
    regValue |= (0x0 << 25U);

    /* Disable half cycle delay for RGMII1 connected to DP83867 PHY */
    regValue |= (0x1  << 26U);

    CTRL_MODULE_CTRL_CORE_SMA_SW_1 = regValue;


    Vps_printf(" Network: Waiting for switch to initialize...");
    do
    {
        Tda2Ex_EthSrvSwitch_dev_reg_read(portNum, TDA2EX_ETHSRVSWITCH_GLB1, TDA2EX_ETHSRVSWITCH_SWITCH_GLB_STAT, &regVal);
        if (regVal != regValPrevious)
        {
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
            Vps_printf(" Network: SWITCH_GLB_STAT: %08x", regVal);
#endif
            regValPrevious = regVal;
        }
    } while ((regVal & (1U << TDA2EX_ETHSRVSWITCH_SWITCH_GLB_STAT_INITREADY)) == 0);

    Tda2Ex_EthSrvSwitch_dev_reg_read(portNum, TDA2EX_ETHSRVSWITCH_GLB1, TDA2EX_ETHSRVSWITCH_GLB_CTRL2, &regVal);
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
    Vps_printf(" Network: GLB_CTRL2: %08x", regVal);
#endif

    /* Clear DA Check: Allows ANY RMU packet to be interpretted. TODO: Maybe set this bit and configure device address in ATU? */
    regVal &= ~(1U << TDA2EX_ETHSRVSWITCH_GLB_CTRL2_DACHECK);

    /* Set RMUMode to 0x2: Port 7 is RMU port (This allows external PC on J20 to configure switch. Change to 0x3 for port 8 when RMU access support is added) */
    regVal &= ~(3U << TDA2EX_ETHSRVSWITCH_GLB_CTRL2_RMUMODE);
    regVal |= (2U << TDA2EX_ETHSRVSWITCH_GLB_CTRL2_RMUMODE);
    Tda2Ex_EthSrvSwitch_dev_reg_write(portNum, TDA2EX_ETHSRVSWITCH_GLB1, TDA2EX_ETHSRVSWITCH_GLB_CTRL2, regVal);

    Tda2Ex_EthSrvSwitch_dev_reg_read(portNum, TDA2EX_ETHSRVSWITCH_GLB1, TDA2EX_ETHSRVSWITCH_GLB_CTRL2, &regVal);
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
    Vps_printf(" Network: GLB_CTRL2: %08x", regVal);
#endif

    dev = 8;
    Tda2Ex_EthSrvSwitch_dev_reg_read(portNum, dev, TDA2EX_ETHSRVSWITCH_PHY_CTRL, &regVal);
    regVal |= (0U << TDA2EX_ETHSRVSWITCH_PHY_CTRL_RXTIMING);
    regVal |= (1U << TDA2EX_ETHSRVSWITCH_PHY_CTRL_TXTIMING);
    Tda2Ex_EthSrvSwitch_dev_reg_write(portNum, dev, TDA2EX_ETHSRVSWITCH_PHY_CTRL, regVal);

    /* For Ports 1 through 5 (Main + 4 cameras) */
    for (dev = 1; dev <= 5; dev++) {
        /* Forward only to these ports */
        regVal = TDA2EX_ETHSRVSWITCH_PORT0 | TDA2EX_ETHSRVSWITCH_PORT6 | TDA2EX_ETHSRVSWITCH_PORT7 | TDA2EX_ETHSRVSWITCH_PORT8;
        Tda2Ex_EthSrvSwitch_dev_reg_write(portNum, dev, TDA2EX_ETHSRVSWITCH_VLAN_MAP, regVal);
    }

    for (dev = 0; dev <= 8; ++dev) {
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
        Vps_printf(" Network: Switch port %d:\n", dev);
#endif
        for (reg = 0; reg <= 6; ++reg) {
            Tda2Ex_EthSrvSwitch_dev_reg_read(portNum, dev, reg, &regVal);
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
            Vps_printf(" Network: reg %d = %08x\n", reg, regVal);
#endif
        }
        reg = 0x1F;
        Tda2Ex_EthSrvSwitch_dev_reg_read(portNum, dev, reg, &regVal);
#if defined(DEBUG_TDA2EX_ETHSRVSWITCH_SMI)
        Vps_printf(" Network: reg %d = %08x\n", reg, regVal);
#endif
    }

    Vps_printf(" Network: TDA2EX ETHSRV board switch configuration done!\n");
}
#endif

