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
#include <stdint.h>
#include <string.h>

/* OS/Posix headers */

/* Project dependency headers */


/*---------------------------------------------------------------------------*\
  |                             Extern Declarations                             |
  \*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
  |                            Local Macros/Defines                             |
  \*---------------------------------------------------------------------------*/

#define PAB_MII (0)
#define PAB_RMII (0)

/* Ethernet MAC ID registers(Devcice configuration) from EFuse */
#define MAC_ID0_LO            (*(volatile uint32_t*)0x4A002514)
#define MAC_ID0_HI            (*(volatile uint32_t*)0x4A002518)
#define MAC_ID1_LO            (*(volatile uint32_t*)0x4A00251C)
#define MAC_ID1_HI            (*(volatile uint32_t*)0x4A002520)

#define CTRL_CORE_SILICON_REV       (*(volatile uint32_t*)(0x4A002204))

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



/*---------------------------------------------------------------------------*\
  |                         Local Variable Declarations                         |
  \*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
  |                         Global Variable Declarations                        |
  \*---------------------------------------------------------------------------*/


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
 * function. Here we initialize our board and read in our
 * MAC address.
 */
   void
vayu_init (void)
{
#if ((PAB_MII != 1) && (PAB_RMII != 1))
    uint32_t regValue;
    /*
     * We do I/O delay adjustments only if GMAC internal delays are enabled.
     * With TDA2xx & TDA2EX PG2.0 the option of disabling internal delays is
     * added. SBL will disable the internal delays if siliconRev is 2 so no need
     * to adjust I/O delay here.
     */
    if (2U != PlatformGetSiliconRev())
    {
      uint32_t regValue, delta, coarse, fine;

      /* Global unlock for I/O Delay resgisters */
      CFG_IO_DELAY_LOCK = CFG_IO_DELAY_UNLOCK_KEY;

      /*
       * Adjust I/O delays on the Tx control and data lines of each MAC port. This is
       * a workaround in order to work properly with the DP83865 PHYs on the EVM. In 3COM
       * RGMII mode this PHY applies it's own internal clock delay, so we essentially need to
       * counteract the DRA7xx internal delay, and we do this by delaying the control and
       * data lines. If not using this PHY, you probably don't need to do this stuff!
       */

      /* Tweaks to RGMII0 Tx Control and Data */

      CFG_RGMII0_TXCTL_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_RGMII0_TXCTL = (SYSCFG_PAD_RGMII0_TXCTL & ~0xF) | 0x0;
      delta = (0x3 << 5) + 0x8;   /* Delay value to add to calibrated value */
      regValue = CFG_RGMII0_TXCTL_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_RGMII0_TXCTL_OUT = regValue;

      CFG_RGMII0_TXD0_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_RGMII0_TXD0 = (SYSCFG_PAD_RGMII0_TXD0 & ~0xF) | 0x0;
      delta = (0x3 << 5) + 0x8;   /* Delay value to add to calibrated value */
      regValue = CFG_RGMII0_TXD0_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_RGMII0_TXD0_OUT = regValue;

      CFG_RGMII0_TXD1_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_RGMII0_TXD1 = (SYSCFG_PAD_RGMII0_TXD1 & ~0xF) | 0x0;
      delta = (0x3 << 5) + 0x2;   /* Delay value to add to calibrated value */
      regValue = CFG_RGMII0_TXD1_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_RGMII0_TXD1_OUT = regValue;

      CFG_RGMII0_TXD2_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_RGMII0_TXD2 = (SYSCFG_PAD_RGMII0_TXD2 & ~0xF) | 0x0;
      delta = (0x4 << 5) + 0x0;   /* Delay value to add to calibrated value */
      regValue = CFG_RGMII0_TXD2_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_RGMII0_TXD2_OUT = regValue;

      CFG_RGMII0_TXD3_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_RGMII0_TXD3 = (SYSCFG_PAD_RGMII0_TXD3 & ~0xF) | 0x0;
      delta = (0x4 << 5) + 0x0;   /* Delay value to add to calibrated value */
      regValue = CFG_RGMII0_TXD3_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_RGMII0_TXD3_OUT = regValue;


      /* Tweaks to RGMII1 Tx Control and Data */
      CFG_VIN2A_D13_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_VIN2A_D13 = (SYSCFG_PAD_VIN2A_D13 & ~0xF) | 0x3;
      delta = (0x3 << 5) + 0x8;   /* Delay value to add to calibrated value */
      regValue = CFG_VIN2A_D13_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_VIN2A_D13_OUT = regValue;

      CFG_VIN2A_D17_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_VIN2A_D17 = (SYSCFG_PAD_VIN2A_D17 & ~0xF) | 0x3;
      delta = (0x3 << 5) + 0x8;
      regValue = CFG_VIN2A_D17_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_VIN2A_D17_OUT = regValue;

      CFG_VIN2A_D16_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_VIN2A_D16 = (SYSCFG_PAD_VIN2A_D16 & ~0xF) | 0x3;
      delta = (0x3 << 5) + 0x2;
      regValue = CFG_VIN2A_D16_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_VIN2A_D16_OUT = regValue;

      CFG_VIN2A_D15_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_VIN2A_D15 = (SYSCFG_PAD_VIN2A_D15 & ~0xF) | 0x3;
      delta = (0x4 << 5) + 0x0;
      regValue = CFG_VIN2A_D15_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_VIN2A_D15_OUT = regValue;

      CFG_VIN2A_D14_OUT =
         (CFG_IO_DELAY_ACCESS_PATTERN & ~CFG_IO_DELAY_LOCK_MASK);
      SYSCFG_PAD_VIN2A_D14 = (SYSCFG_PAD_VIN2A_D14 & ~0xF) | 0x3;
      delta = (0x4 << 5) + 0x0;
      regValue = CFG_VIN2A_D14_OUT & ~0xFFFFFC00;
      coarse = ((regValue >> 5) & 0x1F) + ((delta >> 5) & 0x1F);
      coarse = (coarse > 0x1F) ? (0x1F) : (coarse);
      fine = (regValue & 0x1F) + (delta & 0x1F);
      fine = (fine > 0x1F) ? (0x1F) : (fine);
      regValue =
         CFG_IO_DELAY_ACCESS_PATTERN | CFG_IO_DELAY_LOCK_MASK | ((coarse << 5)
               | (fine));
      CFG_VIN2A_D14_OUT = regValue;

      CFG_IO_DELAY_LOCK = CFG_IO_DELAY_LOCK_KEY;
   }
   else
   {
        /* Disable RGMII half cycle delay for ES2.0 silicon */
        regValue = CTRL_MODULE_CTRL_CORE_SMA_SW_1;
        /* Disable half cycle delay for RGMII0 */
        regValue |= (0x1 << 25U);
        /* Disable half cycle delay for RGMII1 */
        regValue |= (0x1  << 26U);
   }
#endif
}


/*---------------------------------------------------------------------------*\
  |                                 End of File                                 |
  \*---------------------------------------------------------------------------*/
