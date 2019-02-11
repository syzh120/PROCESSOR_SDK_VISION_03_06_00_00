/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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

/*
 * main.c
 */
#include "stdint.h"
#include "stdio.h"
#include "interrupt.h"
#include "irq_xbar.h"
#include "hw_ctrl_core.h"
#include "mailbox.h"
#include "hw_types.h"

#include "TCASECFG.h"


char *return_string[2] = {
  ">>Test case passed\r\n ",
  ">>Test case failed\r\n "
};

#pragma DATA_SECTION(sbl_regression_result, ".OCMC_RESULT")
uint32_t sbl_regression_result = 0;

#pragma DATA_SECTION(slaveStatus, ".OCMC_SYNC")
uint32_t slaveStatus[4] = { 0 };

#pragma DATA_SECTION(slaveResult, ".OCMC_SYNC")
uint32_t slaveResult[4] = { 0 };

volatile uint32_t dsp1Status = 0, dsp2Status = 0, eveStatus = 0;

volatile uint32_t msg = 0, msgStatus = MESSAGE_INVALID;
void mailboxisr (void *handle);
void HAL_CTRL_UnlockMMR (void);
void AMMU_Config ();
void AMMUConfigforEVE ();
uint32_t test_function ();
#define VTOR_Register_Address         (0xE000ED08)

#define IPU_MMU_CFG 0x55080000
#define OCMC_BOOT 1
#define IRAM_BOOT 0
#if OCMC_BOOT
#define vector_table_base_address     (0x00340000)
#elif IRAM_BOOT
#define vector_table_base_address     (0x00020000)
#endif

int
main (void)
{
  uint32_t checkReturn = 0;

  printf ("IPUCORE0:Test case Started\r\n");
  /*Unlock the Crossbar register */
  HAL_CTRL_UnlockMMR ();
  /*Putting the vector table to OCMC RAM to reduce size of bin file */
  HWREG (VTOR_Register_Address) = vector_table_base_address;
  Intc_IntEnable (0);
  Intc_Init ();

  checkReturn = TestFunction ();

  printf ("\r\nIPUCORE0:Test case finished, result=%s",
     return_string[checkReturn]);

  if (checkReturn == RET_OK)
    {
      test_pass ();      //sbl_regression_result[0] = 0x50415353; /*ASCII PASS*/
    }
  else
    {
      test_fail ();      //sbl_regression_result[0] = 0x4641494c; /*ASCII FAIL*/
    }
  /*  issue warm reset        */
  while (1);
  HWREG (SOC_DEVICE_PRM_BASE) |= 0x00000001;
}


void
HAL_CTRL_UnlockMMR (void)
{
  /* unlock MMR1 space for region 0x0100 to 0x079F */
  HWREG (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
    CTRL_CORE_MMR_LOCK_1) = CTRL_CORE_MMR_LOCK_1_TOUNLOCK;
  /* unlock MMR2 space for region 0x07A0 to 0x0D9F */
  HWREG (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
    CTRL_CORE_MMR_LOCK_2) = CTRL_CORE_MMR_LOCK_2_TOUNLOCK;
  /* unlock MMR3 space for region 0x0DA0 to 0x0FFF */
  HWREG (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
    CTRL_CORE_MMR_LOCK_3) = CTRL_CORE_MMR_LOCK_3_TOUNLOCK;
  /* unlock MMR4 space for region 0x1000 to 0x13FF */
  HWREG (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
    CTRL_CORE_MMR_LOCK_4) = CTRL_CORE_MMR_LOCK_4_TOUNLOCK;
  /* unlock MMR5 space for region 0x1400 to 0x1FFF */
  HWREG (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
    CTRL_CORE_MMR_LOCK_5) = CTRL_CORE_MMR_LOCK_5_TOUNLOCK;
}            /* HAL_CTRL_UnlockMMR */

void
test_pass ()
{
  sbl_regression_result = 0x50415353;   /*ASCII PASS */

}

void
test_fail ()
{
  sbl_regression_result = 0x4641494c;   /*ASCII FAIL */
}

void
AMMU_config ()
{
  uint32_t regAddr;

  printf ("--->>>Starting A-MMU config... <<<---\n");

    /*---------------- Setup the UNICACHE MMU -----------------*/
  /*Large Page Translations */
  /* Logical Address */
  regAddr = IPU_MMU_CFG;
  regAddr += 0x800;
  HW_WR_REG32 (regAddr, 0xA0000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x80000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x60000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x40000000);
  regAddr += 0x4;

  /* Physical Address */
  regAddr = IPU_MMU_CFG;
  regAddr += 0x820;
  HW_WR_REG32 (regAddr, 0x80000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x80000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x40000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x40000000);
  regAddr += 0x4;

  /* Policy Register */
  regAddr = IPU_MMU_CFG;
  regAddr += 0x840;
  HW_WR_REG32 (regAddr, 0x00000003);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00030003);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000003);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000003);
  regAddr += 0x4;

  /*Medium Page */
  //  regAddr = IPU_MMU_CFG;
  //  regAddr += 0x860;
  //  HW_WR_REG32(regAddr,         0x00300000); regAddr += 0x4;
  //  HW_WR_REG32(regAddr,         0x00340000); regAddr += 0x4;
  //
  //  regAddr = IPU_MMU_CFG;
  //  regAddr += 0x8A0;
  //  HW_WR_REG32(regAddr,         0x40300000); regAddr += 0x4;
  //  HW_WR_REG32(regAddr,         0x40340000); regAddr += 0x4;
  //
  //  regAddr = IPU_MMU_CFG;
  //  regAddr += 0x8E0;
  //  HW_WR_REG32(regAddr,         0x00030003); regAddr += 0x4;
  //  HW_WR_REG32(regAddr,         0x00030003); regAddr += 0x4;

  /*Small Page */
  //Small page Physical Address
  regAddr = IPU_MMU_CFG;
  //skipping first two small pages.
  regAddr += 0x928;      //0x920
  HW_WR_REG32 (regAddr, 0x00002000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00004000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00008000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x0000C000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
//    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
//    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;

  //Small page Virtual Address
  regAddr = IPU_MMU_CFG;
  regAddr += 0x9A8;      //0x9A0
  HW_WR_REG32 (regAddr, 0x55020000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x55024000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x55028000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x5502C000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
//    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;
//    HW_WR_REG32(regAddr,         0x00000000); regAddr += 0x4;

  regAddr = IPU_MMU_CFG;
  regAddr += 0xA28;      //0xA20
  HW_WR_REG32 (regAddr, 0x00030003);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00030003);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00030003);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00030003);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
  HW_WR_REG32 (regAddr, 0x00000000);
  regAddr += 0x4;
//    WR_MEM_32(regAddr,         0x00000000); regAddr += 0x4;
//    WR_MEM_32(regAddr,         0x00000000); regAddr += 0x4;


  printf ("--->>> A-MMU config completed. <<<---\n");
}

void
AMMUConfigforEVE ()
{
  uint32_t regAddr = 0;
  regAddr = IPU_MMU_CFG;   /*IPU_MMU_CFG */
  regAddr += 0x80C;
  HW_WR_REG32 (regAddr, 0x60000000);
  regAddr += 0x4;

  /* Physical Address */
  regAddr = IPU_MMU_CFG;
  regAddr += 0x82C;
  HW_WR_REG32 (regAddr, 0x40000000);
  regAddr += 0x4;

  /* Policy Register */
  regAddr = IPU_MMU_CFG;
  regAddr += 0x84C;
  HW_WR_REG32 (regAddr, 0x00000007);
  regAddr += 0x4;
}
