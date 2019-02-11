/*
 * Copyright (C) 2013, Texas Instruments Incorporated  - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *   @file  vayu_init.c
 *
 *   @brief
 *       Do all necessary board level initialization for NDK example.
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

/* OS/Posix headers */

/* NDK Dependencies */
#include <ti/ndk/inc/netmain.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw.h>
#include <ti/nsp/drv/inc/gmacsw_config.h>

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define PAB_MII (0)
#define PAB_RMII (0)
/* Enable this for J6ECo Rev C or later EVM and J6Entry EVM */
#define BOARDTYPE_TDA2EX_REV_C_EVM (1)

/* Ethernet MAC ID registers(Devcice configuration) from EFuse */
#define MAC_ID0_LO                (*(volatile uint32_t*)0x4A002514)
#define MAC_ID0_HI                (*(volatile uint32_t*)0x4A002518)
#define MAC_ID1_LO                (*(volatile uint32_t*)0x4A00251C)
#define MAC_ID1_HI                (*(volatile uint32_t*)0x4A002520)

#define GMACSW_CPDMA_BUF_DESC_COUNT  (512U)
#define CPDMA_BUFFDESC_DDR_MEM (1U)

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

#define CTRL_MODULE_CTRL_WKUP_ID_CODE  (*(volatile uint32_t*)(0x4AE0C204))
#define CTRL_MODULE_CTRL_CORE_SMA_SW_1 (*(volatile uint32_t*) (0x4A002534))

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void LOCAL_linkStatus( uint32_t phy, uint32_t linkStatus );
static void LOCAL_phyFoundCb(uint32_t portNum, uint32_t phy);
static void LOCAL_dp83867J6eConfigDelays(GMACSW_DeviceHandle hGMACSW, uint32_t portNum);

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

/* This string array corresponds to link state */
static char *LinkStr[] = { "No Link",
                           "None",
                           "10Mb/s Half Duplex",
                           "10Mb/s Full Duplex",
                           "100Mb/s Half Duplex",
                           "100Mb/s Full Duplex",
                           "1000Mb/s Half Duplex", /*not suported*/
                           "1000Mb/s Full Duplex"};


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if (1 == CPDMA_BUFFDESC_DDR_MEM)
/*! CPDMA descriptor memory. Make sure this is non-cached region */
#if defined(__GNUC__)
CPDMA_BuffDesc cpdmaBuffDescMem[GMACSW_CPDMA_BUF_DESC_COUNT]__attribute__(( aligned(128), section(".bss:CPDMA_BUFFDESC") ));
#else
#pragma DATA_ALIGN(cpdmaBuffDescMem, 128);
#pragma DATA_SECTION(cpdmaBuffDescMem, ".bss:CPDMA_BUFFDESC")
CPDMA_BuffDesc cpdmaBuffDescMem[GMACSW_CPDMA_BUF_DESC_COUNT];
#endif
#endif

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/
/**
 * \brief       This API provides the Silicon Rev Value.
 *
 * \param       None.
 *
 * \return      Silicon Revision.
 *
 * \note        For TDA2xx
 *              0: Silicon Rev 1.0
 *              1: Silicon Rev 1.1
 *              2: Silicon Rev 2.0
 *              For TDA3xx
 *              0: Silicon Rev 1.0
 **/
uint32_t PlatformGetSiliconRev(void)
{
    uint32_t siliconRev;

    siliconRev = CTRL_MODULE_CTRL_WKUP_ID_CODE;

    siliconRev = (siliconRev & 0xF0000000U) >> 28U;

    return (siliconRev);
}

/*
 * We changed our CFG file to point call this private init
 * function. Here we initialize our some particulars for
 * our board/device.
 */
void j6eco_init( void )
{
#if ((PAB_MII != 1) && (PAB_RMII != 1))
    uint32_t regValue, delta, coarse, fine;
    /*
     * We do I/O delay adjustments only if GMAC internal delays are enabled.
     * With TDA2xx & TDA2EX PG2.0 the option of disabling internal delays is
     * added. SBL will disable the internal delays if siliconRev is 1 for TDA2EX
     * and 2 for TDA2xx so no need so adjust I/O delay here.
     */
    if (PlatformGetSiliconRev() < 1U )
    {
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

/*
 * GMACSW_getConfig()
 *
 * This is a callback from the Ethernet driver. This function
 * is used by the driver to an application-specific config structure
 * for the GMACSW driver. Typically it will be used to provide the
 * MAC address(es) and the link status update callback function.
 */
GMACSW_Config *GMACSW_getConfig(void)
{
    int i = 0;
    uint8_t macAddr[6];

    /* Get digital loopback starting config */
    GMACSW_Config *pGMACSWConfig = GMACSW_CONFIG_getDefaultConfig();

    /* Set count of active MAC ports */
    pGMACSWConfig->activeMACPortMask = PORT_MASK_MAC_BOTH;

    /* Update default config with the correct MAC addresses */
    for(i=0; i<MAC_NUM_PORTS; i++)
    {
        if ( (1U << i) & pGMACSWConfig->activeMACPortMask )
        {
            if (0==i)
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

            printf("\nMAC Port %d Address:\n\t%02x-%02x-%02x-%02x-%02x-%02x\n", i,
                    macAddr[0], macAddr[1], macAddr[2],
                    macAddr[3], macAddr[4], macAddr[5]);

            /* Copy the correct MAC address into the driver config */
            memcpy( (void *)&(pGMACSWConfig->macInitCfg[i].macAddr[0]), (void *)&macAddr[0], 6 );

    #if ((PAB_MII == 1) || (PAB_RMII == 1))
            /*
            * Adjust the PHY mask numbers for the Vayu PAB. The first MAC
            * port is connected to a PHY with address = 3, the second MAC
            * port is connected to a PHY with address = 2.
            */
            pGMACSWConfig->macInitCfg[i].phyMask = 0x1 << (3 - i);
            #if (PAB_MII == 1)
                    pGMACSWConfig->macInitCfg[i].macConnectionType =
                        MAC_CONNECTION_TYPE_MII_100;
            #else
                    pGMACSWConfig->macInitCfg[i].macConnectionType =
                        MAC_CONNECTION_TYPE_RMII_100;
            #endif
    #else
            /*
            *  For TDA2EX 2.0 (Rev C) EVM the PHY address is 2 for first PHY and 3
            *  for second PHY
            */
            if (PlatformGetSiliconRev() >= 1U )
            {
                pGMACSWConfig->macInitCfg[i].phyMask = 0x1 << (2 + i);
                //TODO check if required for Rev C EVM
                /*
                * National PHY on Vayu EVM does not work with the default INBAND detection mode.
                * It would seem the Rx clock from the PHY is not generated unless the Tx clock
                * from the Vayu device is present. So set the mode to force 1Gbps to start.
                */
                pGMACSWConfig->macInitCfg[i].macConnectionType =
                    MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL;
            }
            else
            {
                pGMACSWConfig->macInitCfg[i].phyMask = 0x8 >> (i*2);
                /*
                * National PHY on Vayu EVM does not work with the default INBAND detection mode.
                * It would seem the Rx clock from the PHY is not generated unless the Tx clock
                * from the Vayu device is present. So set the mode to force 1Gbps to start.
                */
                pGMACSWConfig->macInitCfg[i].macConnectionType =
                    MAC_CONNECTION_TYPE_RGMII_FORCE_1000_FULL;
            }
    #endif
        }
    }

#if (1 == CPDMA_BUFFDESC_DDR_MEM)
    /* Configure CPDMA descriptor memory config */
    pGMACSWConfig->cpdmaInitCfg.buffDescMemCfg.buffDescCnt = GMACSW_CPDMA_BUF_DESC_COUNT;
    pGMACSWConfig->cpdmaInitCfg.buffDescMemCfg.buffDescMem = &(cpdmaBuffDescMem[0]);
#endif

    pGMACSWConfig->mdioCfg.phyFoundCallback = &LOCAL_phyFoundCb;
    pGMACSWConfig->linkStatusCallback = &LOCAL_linkStatus;

    /* Return the config */
    return pGMACSWConfig;
}

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*
 * LOCAL_linkStatus()
 *
 * This is a callback from the Ethernet driver. This function
 * is called whenever there is a change in link state. The
 * current PHY and current link state are passed as parameters.
 */
static void LOCAL_linkStatus( uint32_t phy, uint32_t linkStatus )
{
    printf("Link Status: %s on PHY %" PRIu32 "\n",LinkStr[linkStatus],phy);
}

/*
 * LOCAL_phyFoundCb()
 *
 * This is a callback from the Ethernet driver. This function
 * is called when PHY is found at PHY mask. This can be used for doing PHY
 * specific configuration.
 */
static void LOCAL_phyFoundCb(uint32_t portNum, uint32_t phy)
{
        GMACSW_DeviceHandle     hGMACSW = GMACSW_open(NULL);
        LOCAL_dp83867J6eConfigDelays(hGMACSW, portNum);
        GMACSW_close(hGMACSW);
}

/*
 * LOCAL_phyFoundCb()
 *
 * Delay configuration function for DP83867 PHY on TDA2EX REV C EVM
 */
static void LOCAL_dp83867J6eConfigDelays(GMACSW_DeviceHandle hGMACSW, uint32_t portNum)
{
    if (PlatformGetSiliconRev() >= 1U )
    {
#if (BOARDTYPE_TDA2EX_REV_C_EVM == 1)
        MDIO_rdWrphyRegIoctlCmd cmd;
        uint32_t regVal;

        /* MAC port number */
        cmd.portNum = portNum;

        regVal = 0x8000;
        cmd.regAddr = 0x1F;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        regVal = 0x08;
        cmd.regAddr = 0x86;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        regVal = 0x0D1;
        cmd.regAddr = 0x32;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        regVal = 0x61F;
        cmd.regAddr = 0x170;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));

        regVal = 0x4000;
        cmd.regAddr = 0x1F;
        cmd.regVal = &regVal;
        GMACSW_ioctl( hGMACSW,
                      GMACSW_IOCTL_MDIO_WRITE_DP83867_PHY_INDIRECT_REGISTER,
                     (void *)&cmd, sizeof(MDIO_rdWrphyRegIoctlCmd));
#endif
    }
}

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/
