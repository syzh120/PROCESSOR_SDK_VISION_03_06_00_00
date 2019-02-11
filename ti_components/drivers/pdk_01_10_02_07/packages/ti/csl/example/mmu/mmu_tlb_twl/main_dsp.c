/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  /file       main_dsp
 *
 *  /brief    Default code for testcase
 *                 Just returns RET_OK
 *
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mmu.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
#if defined (SOC_AM574x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_DRA75x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
#include <ti/csl/arch/c66x/dsp_config.h>
#endif

/* ========================================================================== */
/*                                Macros & typedef                            */
/* ========================================================================== */
/* External memory mappping as a super section of 16 MB*/
#define PHY_ADDR2    (0x80000000)
#define VIRT_ADDR2   (0x80000000)

#define PHY_ADDR3    (0x90000000)
#define VIRT_ADDR3   (0x48000000)

/* OCMCRAM region0 as 4KB section        */
#define PHY_ADDR4    (0x00800000)
#define VIRT_ADDR4   (0x00800000)

/* MMU Register memory region 4KB section        */
#define PHY_ADDR6    (SOC_DSP_MMU0CFG_BASE)
#define VIRT_ADDR6   (SOC_DSP_MMU0CFG_BASE)

/* External memory mappping as a super section of 16 MB*/
#define PHY_ADDR7    (0x85000000)
#define VIRT_ADDR7   (0x81000000)

/* External memory mappping as a super section of 16 MB*/
#define PHY_ADDR8    (0x82000000)
#define VIRT_ADDR8   (0x88000000)

#define PHY_ADDR9    (0x4031C000)
#define VIRT_ADDR9   (0x4031C000)

#define PHY_ADDR10    (0x8B000000)
#define VIRT_ADDR10   (0x8B000000)

#define PHY_ADDR11    (0x83000000)
#define VIRT_ADDR11   (0x83000000)

#define TTB_ADDRESS   (0x80500000)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t mmu_intr_occurred = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
uint32_t MMU_Configure()
{
    MMU_TlbEntry_t mmu_entry;

    /* Configure MMU Tlb Entry for mapping reset vector of 4KB*/
    mmu_entry.phyAddr        = PHY_ADDR6;
    mmu_entry.virtAddr       = VIRT_ADDR6;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Large_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 1, &mmu_entry);

    mmu_entry.phyAddr        = PHY_ADDR3;
    mmu_entry.virtAddr       = VIRT_ADDR3;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Section_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 2, &mmu_entry);

    /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
    mmu_entry.phyAddr        = PHY_ADDR2;
    mmu_entry.virtAddr       = VIRT_ADDR2;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 3, &mmu_entry);

    /*ocmc ram initialization for MMU TLB Entry*/
    mmu_entry.phyAddr        = PHY_ADDR4;
    mmu_entry.virtAddr       = VIRT_ADDR4;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Large_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 4, &mmu_entry);

    /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
    mmu_entry.phyAddr        = PHY_ADDR8;
    mmu_entry.virtAddr       = VIRT_ADDR8;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 5, &mmu_entry);

    /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
    mmu_entry.phyAddr        = PHY_ADDR9;
    mmu_entry.virtAddr       = VIRT_ADDR9;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_Large_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 6, &mmu_entry);

    /* Configure MMU Tlb Entry for DDR Data  as 16 MB Supersection*/
    mmu_entry.phyAddr        = PHY_ADDR10;
    mmu_entry.virtAddr       = VIRT_ADDR10;
    mmu_entry.valid          = TRUE;
    mmu_entry.pageSize       = MMU_SuperSection_Size;
    mmu_entry.endianness     = MMU_Little_Endian;
    mmu_entry.elementSize    = MMU_NoTranslation_ElementSize;
    mmu_entry.tlbElementSize = MMU_CPU_ElementSize;
    mmu_entry.preserve       = TRUE;
    MMUTlbEntrySet(SOC_DSP_MMU0CFG_BASE, 7, &mmu_entry);

    memset((void *) TTB_ADDRESS, 0, 0x4000);

    /* Configure MMU page table entry for DDR Data  as 16 MB Supersection*/
    MMUSuperSection
    (
        PHY_ADDR7,
        VIRT_ADDR7,
        TTB_ADDRESS,
        MMU_Little_Endian,
        MMU_NoTranslation_ElementSize,
        MMU_CPUES,
        MMU_NO_FAULT
    );

    /* Configure MMU page table entry for DDR Data  as 1 MB Supersection*/
    MMUSection
    (
        PHY_ADDR11,
        VIRT_ADDR11,
        TTB_ADDRESS,
        MMU_Little_Endian,
        MMU_NoTranslation_ElementSize,
        MMU_CPUES,
        MMU_NO_FAULT
    );

    /*Enable all mmu interrupts*/
    MMUIrqEnable(SOC_DSP_MMU0CFG_BASE, MMU_INT_All);

    /*Set TTB*/
    MMUTTBSet(SOC_DSP_MMU0CFG_BASE, TTB_ADDRESS);

    /*Enable TWL*/
    MMUWtlEnable(SOC_DSP_MMU0CFG_BASE);

    /* Enable MMU */
    MMUEnable(SOC_DSP_MMU0CFG_BASE);

    return 0;
}

int main(void)
{
    uint32_t          rd_value, i, flag = 0;
    volatile uint32_t done = 1;

    /*Write pattern to physical memory startinf from PHY_ADDR7 and PHY_ADDR8*/
    for (i = 0; i < 10; i++)
    {
        HW_WR_REG32(PHY_ADDR7 + (i * 4), i);
    }

    for (i = 0; i < 10; i++)
    {
        HW_WR_REG32(PHY_ADDR8 + (i * 4), i);
    }

    for (i = 0; i < 10; i++)
    {
        HW_WR_REG32(PHY_ADDR11 + (i * 4), i);
    }

    /*Reset MMU*/
    MMUSoftReset(SOC_DSP_MMU0CFG_BASE);

    /*Set MMU to no idle mode*/
    MMUSetMode(SOC_DSP_MMU0CFG_BASE, MMU_NO_IDLE);

    /* Configure the MMU, enable MMU interrupt  */
    MMU_Configure();

    /*
     * Even after doing Global flush the preserved entries are protected
     * and are not flushed
     */
    MMUGlobalFlush(SOC_DSP_MMU0CFG_BASE);

#if defined (SOC_AM574x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM572x) || defined (SOC_AM571x) || defined (SOC_DRA75x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Enable MMU in DSPSS */
    DSPSysMmuConfig(SOC_DSP_SYSTEM_BASE, DSP_SYS_MMU_INSTANCE0, DSP_SYS_MMU_EN,
                    DSP_SYS_MMU_ABORT_DIS);
#endif

    rd_value = MMUIrqGetStatus(SOC_DSP_MMU0CFG_BASE);
    if (!rd_value)
    {
        printf("No fault occurred\n");
    }

    /* Read from virtual memory VIRT_ADDR7 and VIRT_ADDR8 to match
     * the pattern written in physical memory PHY_ADDR7 and PHY_ADDR8.
     * Both the pattern should be same
     */
    for (i = 0; i < 10; i++)
    {
        if ((HW_RD_REG32(VIRT_ADDR8 + (i * 4))) != i)
        {
            flag = 1;
        }
    }

    for (i = 0; i < 10; i++)
    {
        if ((HW_RD_REG32(VIRT_ADDR7 + (i * 4))) != i)
        {
            flag = 1;
        }
    }

    for (i = 0; i < 10; i++)
    {
        if ((HW_RD_REG32(VIRT_ADDR11 + (i * 4))) != i)
        {
            flag = 1;
        }
    }

    if (!flag)
    {
        printf(
            "Data is read successfully even after doing global flush since the TLB entries are preserved\n");
        printf("MMU configuration successful\n");
    }
    else
    {
        printf("MMU configuration failed\n");
    }

    /* Disable MMU */
    MMUDisable(SOC_DSP_MMU0CFG_BASE);

    while (done) ;

    return 0;
}
/********************************* End of file ******************************/
