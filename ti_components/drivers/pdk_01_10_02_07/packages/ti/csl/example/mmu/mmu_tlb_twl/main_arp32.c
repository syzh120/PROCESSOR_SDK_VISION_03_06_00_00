/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
/**
 *  Filename       main_arp32.c
 *
 *  Description    Default code for testcase
 *                 Just returns RET_OK
 *
 * ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mmu.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

/* External memory mappping as a super section of 16 MB*/
#define TWL_PHY_ADDR1    (0x88000000)
#define TWL_VIRT_ADDR1   (0x11000000)

#define TWL_PHY_ADDR2    (0x89000000)
#define TWL_VIRT_ADDR2   (0x21000000)

/* External memory mappping as a super section of 16 MB*/
#define TLB_PHY_ADDR1    (0x8A000000)
#define TLB_VIRT_ADDR1   (0x31000000)

#define TTB_ADDRESS   (0x80500000)

volatile uint32_t mmu_intr_occurred = 0;

uint32_t MMU_Configure()
{
    MMU_TlbEntry_t mmu_entry;

    /* Configure last MMU Tlb Entry for DDR Data  as 16 MB Supersection
     * The last entry is used as the GEL/SBL would configure some of the first
     * few entries of the MMU.
     */
    mmu_entry.phyAddr        = TLB_PHY_ADDR1;
    mmu_entry.virtAddr       = TLB_VIRT_ADDR1;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_EVE_MMU0_BASE, 31, &mmu_entry);

    /* Configure another page with same address as virtual and physical address
     * to later verify
     */
    mmu_entry.phyAddr        = TLB_PHY_ADDR1;
    mmu_entry.virtAddr       = TLB_PHY_ADDR1;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_EVE_MMU0_BASE, 30, &mmu_entry);

    /* Configure another page with same address as virtual and physical address
     * to later verify
     */
    mmu_entry.phyAddr        = TWL_PHY_ADDR1;
    mmu_entry.virtAddr       = TWL_PHY_ADDR1;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_EVE_MMU0_BASE, 29, &mmu_entry);

    /* Configure another page with same address as virtual and physical address
     * to later verify
     */
    mmu_entry.phyAddr        = TWL_PHY_ADDR2;
    mmu_entry.virtAddr       = TWL_PHY_ADDR2;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_EVE_MMU0_BASE, 28, &mmu_entry);

    memset((void *) TTB_ADDRESS, 0, 0x4000);

    /* Configure MMU page table entry for DDR Data  as 16 MB Supersection*/
    MMUSuperSection
    (
        TWL_PHY_ADDR1,
        TWL_VIRT_ADDR1,
        TTB_ADDRESS,
        MMU_Little_Endian,
        MMU_NoTranslation_ElementSize,
        MMU_CPUES,
        MMU_NO_FAULT
    );

    /* Configure MMU page table entry for DDR Data  as 1 MB Supersection*/
    MMUSection
    (
        TWL_PHY_ADDR2,
        TWL_VIRT_ADDR2,
        TTB_ADDRESS,
        MMU_Little_Endian,
        MMU_NoTranslation_ElementSize,
        MMU_CPUES,
        MMU_NO_FAULT
    );

    /*Enable all mmu interrupts*/
    MMUIrqEnable(SOC_EVE_MMU0_BASE, MMU_INT_All);

    /*Set TTB*/
    MMUTTBSet(SOC_EVE_MMU0_BASE, TTB_ADDRESS);

    /*Enable TWL*/
    MMUWtlEnable(SOC_EVE_MMU0_BASE);

    /* Enable MMU */
    MMUEnable(SOC_EVE_MMU0_BASE);

    return 0;
}

int main(void)
{
    uint32_t          rd_value, i, flag = 0;

    /*Set MMU to no idle mode*/
    MMUSetMode(SOC_EVE_MMU0_BASE, MMU_NO_IDLE);

    /* Configure the MMU, enable MMU interrupt  */
    MMU_Configure();

    rd_value = MMUIrqGetStatus(SOC_EVE_MMU0_BASE);
    if (!rd_value)
    {
        printf("No fault occurred\r\n");
    }

    /* Write pattern to virtual memory starting from TWL_PHY_ADDR1 and
     * TLB_PHY_ADDR1*/
    for (i = 0; i < 10; i++)
    {
        HW_WR_REG32(TLB_VIRT_ADDR1 + (i * 4), i);
    }

    for (i = 0; i < 10; i++)
    {
        HW_WR_REG32(TWL_VIRT_ADDR1 + (i * 4), i);
    }

    for (i = 0; i < 10; i++)
    {
        HW_WR_REG32(TWL_VIRT_ADDR2 + (i * 4), i);
    }

    /* Read from virtual memory TWL_PHY_ADDR1, TWL_PHY_ADDR2 and TLB_PHY_ADDR1.
     * This is a one-one mapping hence the final physical address will be the
     * same as those accessed by the virtual addresses accessed above.
     */
    for (i = 0; i < 10; i++)
    {
        if ((HW_RD_REG32(TLB_PHY_ADDR1 + (i * 4))) != i)
        {
            flag = 1;
        }
    }

    for (i = 0; i < 10; i++)
    {
        if ((HW_RD_REG32(TWL_PHY_ADDR1 + (i * 4))) != i)
        {
            flag = 1;
        }
    }

    for (i = 0; i < 10; i++)
    {
        if ((HW_RD_REG32(TWL_PHY_ADDR2 + (i * 4))) != i)
        {
            flag = 1;
        }
    }

    if (!flag)
    {
        printf("Data is read successfully based on TLB and TWL entries\r\n");
        printf("MMU configuration successful\r\n");
    }
    else
    {
        printf("MMU configuration failed\r\n");
    }
    return 0;
}

