/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file  mmu.c
 *
 *  \brief MMU device abstraction layer APIs
 *
 *   This file contains the device abstraction layer APIs for MMU.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_mmu.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define MMU_TTB_MASK             (0xFFFFC000U)
#define MMU_SECTION_ADDR_MASK    (0xFFF00000U)
#define MMU_SSECTION_ADDR_MASK   (0xFF000000U)
#define MMU_PAGE_TABLE_MASK      (0xFFFFFC00U)
#define MMU_LARGE_PAGE_MASK      (0xFFFF0000U)
#define MMU_SMALL_PAGE_MASK      (0xFFFFF000U)
#define MMU_ELEMENTSIZE_MAX      (3U)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void MMUCurrentVictimSet(uint32_t baseAddr, uint32_t tlbEntry)
{
    HW_WR_FIELD32(baseAddr + MMU_LOCK, MMU_LOCK_CURRENTVICTIM, tlbEntry);
}

uint32_t MMUCurrentVictimGet(uint32_t baseAddr)
{
    return (HW_RD_FIELD32(baseAddr + MMU_LOCK, MMU_LOCK_CURRENTVICTIM));
}

void MMUTlbLockSet(uint32_t baseAddr, uint32_t tlbEntry)
{
    HW_WR_FIELD32(baseAddr + MMU_LOCK, MMU_LOCK_BASEVALUE, tlbEntry);
}

uint32_t MMUTlbLockGet(uint32_t baseAddr)
{
    return (HW_RD_FIELD32(baseAddr + MMU_LOCK, MMU_LOCK_BASEVALUE));
}

void MMUGlobalFlush(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MMU_GFLUSH,
        MMU_GFLUSH_GLOBALFLUSH,
        MMU_GFLUSH_GLOBALFLUSH_WRITE1);
}

void MMUTlbEntryFlush(uint32_t baseAddr, uint32_t virtAddress)
{
    HW_WR_FIELD32(
        baseAddr + MMU_CAM,
        MMU_CAM_VATAG,
        virtAddress >> MMU_CAM_VATAG_SHIFT);

    HW_WR_FIELD32(
        baseAddr + MMU_FLUSH_ENTRY,
        MMU_FLUSH_ENTRY_FLUSHENTRY,
        MMU_FLUSH_ENTRY_FLUSHENTRY_WRITE1);
}

void MMUSoftReset(uint32_t baseAddr)
{
#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /* reset not required */
#else
    uint32_t resetDone;
#endif

    HW_WR_FIELD32(
        baseAddr + MMU_SYSCONFIG,
        MMU_SYSCONFIG_SOFTRESET,
        MMU_SYSCONFIG_SOFTRESET_WRITE1);

#if defined (TI814X_BUILD) || defined (TI8149_BUILD) || defined (TI811X_BUILD)
    /*reset not required*/
#else
    resetDone = 0U;
    while (0U == resetDone)
    {
        resetDone = HW_RD_FIELD32(
            baseAddr + MMU_SYSSTATUS,
            MMU_SYSSTATUS_RESETDONE);
    }
#endif
}

void MMUSetMode(uint32_t baseAddr, MMU_Mode mode)
{
    HW_WR_FIELD32(
        baseAddr + MMU_SYSCONFIG,
        MMU_SYSCONFIG_IDLEMODE,
        mode);
}

uint32_t MMUIrqGetStatus(uint32_t baseAddr)
{
    uint32_t rdVal;

    rdVal = HW_RD_REG32(baseAddr + MMU_IRQSTATUS);

    rdVal &= MMU_INT_All;

    return rdVal;
}

void MMUIrqClearStatus(uint32_t baseAddr, MMU_IntType_t intType)
{
    uint32_t lVal;

    lVal = intType & MMU_INT_All;

    HW_WR_REG32(baseAddr + MMU_IRQSTATUS, lVal);
}

void MMUIrqEnable(uint32_t baseAddr, MMU_IntType_t intType)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + MMU_IRQENABLE);

    regVal |= (intType & MMU_INT_All);

    HW_WR_REG32(baseAddr + MMU_IRQENABLE, regVal);
}

void MMUIrqDisable(uint32_t baseAddr, MMU_IntType_t intType)
{
    uint32_t regVal;

    regVal = HW_RD_REG32(baseAddr + MMU_IRQENABLE);

    regVal |= ((~((uint32_t) intType)) & MMU_INT_All);

    HW_WR_REG32(baseAddr + MMU_IRQENABLE, regVal);
}

void MMUWtlEnable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MMU_CNTL,
        MMU_CNTL_TWLENABLE,
        MMU_CNTL_TWLENABLE_TWLEN);
}

void MMUWtlDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MMU_CNTL,
        MMU_CNTL_TWLENABLE,
        MMU_CNTL_TWLENABLE_TWLDIS);
}

void MMUEnable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MMU_CNTL,
        MMU_CNTL_MMUENABLE,
        MMU_CNTL_MMUENABLE_MMUEN);
}

void MMULoadTLB(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MMU_LD_TLB,
        MMU_LD_TLB_LDTLBITEM,
        MMU_LD_TLB_LDTLBITEM_WRITE1);
}

void MMUWriteCAM(uint32_t baseAddr, uint32_t cam)
{
    HW_WR_REG32(baseAddr + MMU_CAM, cam);
}

void MMUWriteRAM(uint32_t baseAddr, uint32_t ram)
{
    HW_WR_REG32(baseAddr + MMU_RAM, ram);
}

uint32_t MMUReadCAM(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + MMU_CAM);
}

uint32_t MMUReadRAM(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + MMU_RAM);
}

uint32_t MMUFaultAddrGet(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + MMU_FAULT_AD);
}

uint32_t MMUTTBGet(uint32_t baseAddr)
{
    return HW_RD_REG32(baseAddr + MMU_TTB);
}

void MMUTTBSet(uint32_t baseAddr, uint32_t ttb)
{
    HW_WR_REG32(baseAddr + MMU_TTB, ttb);
}

void MMUDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MMU_CNTL,
        MMU_CNTL_MMUENABLE,
        MMU_CNTL_MMUENABLE_MMUDIS);
}

MMU_Return_t MMUTlbEntrySet(uint32_t              baseAddr,
                            uint32_t              tlbEntry,
                            const MMU_TlbEntry_t *mmuTlbEntry)

{
    MMU_Return_t returnCode = RET_OK;
    uint32_t     lVal;

    /* Check parameters */
    /* Add */

    /* Prepare CAM register Value */
    lVal = mmuTlbEntry->virtAddr & MMU_CAM_VATAG_MASK;
    lVal =
        ((lVal & (~((uint32_t) MMU_CAM_P_MASK))) |
         ((uint32_t) ((mmuTlbEntry->preserve) <<
                      MMU_CAM_P_SHIFT) & MMU_CAM_P_MASK));
    lVal =
        ((lVal &
          (~((uint32_t) MMU_CAM_V_MASK))) |
         ((uint32_t) ((mmuTlbEntry->valid) << MMU_CAM_V_SHIFT) & MMU_CAM_V_MASK));
    lVal =
        ((lVal &
          (~((uint32_t) MMU_CAM_PAGESIZE_MASK))) |
         ((uint32_t) ((mmuTlbEntry->pageSize) <<
                      MMU_CAM_PAGESIZE_SHIFT) & MMU_CAM_PAGESIZE_MASK));

    /* Write CAM Register */
    MMUWriteCAM(baseAddr, lVal);

    /* Prepare RAM register Value */
    lVal = mmuTlbEntry->phyAddr & MMU_RAM_PHYSICALADDRESS_MASK;
    lVal =
        ((lVal &
          (~((uint32_t) MMU_RAM_ENDIANNESS_MASK))) |
         ((uint32_t) ((mmuTlbEntry->endianness) <<
                      MMU_RAM_ENDIANNESS_SHIFT) & MMU_RAM_ENDIANNESS_MASK));
    lVal =
        ((lVal &
          (~((uint32_t) MMU_RAM_ELEMENTSIZE_MASK))) |
         ((uint32_t) ((mmuTlbEntry->elementSize) <<
                      MMU_RAM_ELEMENTSIZE_SHIFT) & MMU_RAM_ELEMENTSIZE_MASK));
    lVal =
        ((lVal &
          (~((uint32_t) MMU_RAM_MIXED_MASK))) |
         ((uint32_t) ((mmuTlbEntry->tlbElementSize) <<
                      MMU_RAM_MIXED_SHIFT) & MMU_RAM_MIXED_MASK));

    /* Write RAM Register */
    MMUWriteRAM(baseAddr, lVal);

    /* Set Desired TLB Entry */
    MMUCurrentVictimSet(baseAddr, tlbEntry);

    /* Load Tlb */
    MMULoadTLB(baseAddr);

    return returnCode;
}

MMU_Return_t MMUSuperSection(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    )
{
    uint32_t secCnt;
    MMU_Return_t returnCode = RET_OK;
    uint32_t     addrOfL1Desc, l1DescSSection, TTB_13_to_7, VA_31_to_25,
                 desc_13_to_7;

    /* Generate the ADDRESS of First Level Descriptor for a Super section
     *address */
    TTB_13_to_7  = ((TTB >> 7U) & 0x0000007FU);
    VA_31_to_25  = ((virtualAddr >> 25U) & 0x0000007FU);
    desc_13_to_7 = (((TTB_13_to_7 + VA_31_to_25) & 0x0000007FU) << 7U);

    addrOfL1Desc =
        ((TTB &
          MMU_TTB_MASK) | desc_13_to_7 |
         ((virtualAddr >> 18U) & 0x0000007CU));

    /* Generate the First Level Descriptor for a Super section address */
    if (faultType == MMU_FAULT_DESC1)
    {
        l1DescSSection = (((physicalAddr & MMU_SSECTION_ADDR_MASK) |
                           ((uint32_t) endianism << 15U) |
                           ((uint32_t) elementSize << 10U) |
                           ((uint32_t) mixedSize << 17U)
                           ) | 0x40000U
                          );
    }
    else
    {
        l1DescSSection = (((physicalAddr & MMU_SSECTION_ADDR_MASK) |
                           ((uint32_t) endianism << 15U) |
                           ((uint32_t) elementSize << 10U) | 2U |
                           ((uint32_t) mixedSize << 17U)
                           ) | 0x40000U
                          );
    }

    /*
     *  Each entry is for a 1 MB section.
     *  And for a super section of 16 MB,
     *  the 16 consecutive entries should be identical
     */
    for(secCnt = 0;secCnt < 16U;secCnt++)
    {
        HW_WR_REG32((addrOfL1Desc + (secCnt * 4U)), l1DescSSection);
    }

    return returnCode;
}

MMU_Return_t MMUSection(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    )
{
    MMU_Return_t returnCode = RET_OK;
    uint32_t     addrOfL1Desc, l1DescSection, TTB_13_to_7, VA_31_to_25,
                 desc_13_to_7;

    /* Generate the ADDRESS of First Level Descriptor for a section address */
    TTB_13_to_7  = ((TTB >> 7U) & 0x0000007FU);
    VA_31_to_25  = ((virtualAddr >> 25U) & 0x0000007FU);
    desc_13_to_7 = (((TTB_13_to_7 + VA_31_to_25) & 0x0000007FU) << 7U);

    addrOfL1Desc =
        ((TTB &
          MMU_TTB_MASK) | desc_13_to_7 |
         ((virtualAddr >> 18U) & 0x0000007CU));

    /* Generate the first Level Descriptor for a section address */
    if (faultType == MMU_FAULT_DESC1)
    {
        l1DescSection = (((physicalAddr & MMU_SECTION_ADDR_MASK) |
                          ((uint32_t) endianism << 15U) |
                          ((uint32_t) elementSize << 10U) |
                          ((uint32_t) mixedSize << 17U)
                          ) & 0xFFFBFFFFU
                         );
    }
    else
    {
        l1DescSection = (((physicalAddr & MMU_SECTION_ADDR_MASK) |
                          ((uint32_t) endianism << 15U) |
                          ((uint32_t) elementSize << 10U) |
                          ((uint32_t) mixedSize << 17U) |
                          2U
                          ) & 0xFFFBFFFFU
                         );
    }

    HW_WR_REG32(addrOfL1Desc, l1DescSection);

    return returnCode;
}

MMU_Return_t MMUCoarseLargePage(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    const uint32_t    pageTableBase,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    )
{
    MMU_Return_t returnCode = RET_OK;
    uint32_t     addrOfL1Desc, l1DescCoarseLP, addrOfL2Desc, l2DescCoarseLP, i;
    uint32_t     TTB_13_to_7, VA_31_to_25, desc_13_to_7;

    /*Check the input Parameters*/
    /*CHECK_INPUT_RANGE_MIN0(elementSize,MMU_ELEMENTSIZE_MAX,RET_PARAM_OUT_OF_RANGE,RES_MMU_BASE
    *+ RES_INVALID_INPUT_PARAM);*/

    /* Generate the ADDRESS of First Level Descriptor for a Coarse Large Page */
    TTB_13_to_7  = ((TTB >> 7U) & 0x0000007FU);
    VA_31_to_25  = ((virtualAddr >> 25U) & 0x0000007FU);
    desc_13_to_7 = (((TTB_13_to_7 + VA_31_to_25) & 0x0000007FU) << 7U);
    addrOfL1Desc =
        ((TTB &
          MMU_TTB_MASK) | desc_13_to_7 |
         ((virtualAddr >> 18U) & 0x0000007CU));

    /* Generate the First Level Descriptor for a Coarse Large Page */
    if (faultType == MMU_FAULT_DESC1)
    {
        l1DescCoarseLP = (pageTableBase & MMU_PAGE_TABLE_MASK);
    }
    else
    {
        l1DescCoarseLP = ((pageTableBase & MMU_PAGE_TABLE_MASK) | 1U);
    }

    /* Generate the ADDRESS of Second Level Descriptor for a Coarse Large Page
    **/
    addrOfL2Desc = ((pageTableBase & MMU_PAGE_TABLE_MASK) |
                    (((virtualAddr &
                       0x000FF000U) >> 10U) & 0x000003FCU)
                    );

    /* Generate the Second Level Descriptor for a Coarse Large Page */
    if (faultType == MMU_FAULT_DESC2)
    {
        l2DescCoarseLP = ((physicalAddr & MMU_LARGE_PAGE_MASK) |
                          ((uint32_t) endianism << 9U) |
                          ((uint32_t) elementSize << 4U) |
                          ((uint32_t) mixedSize << 11U)
                          );
    }
    else
    {
        l2DescCoarseLP = ((physicalAddr & MMU_LARGE_PAGE_MASK) |
                          ((uint32_t) endianism << 9U) |
                          ((uint32_t) elementSize << 4U) |
                          ((uint32_t) mixedSize << 11U) | 1U
                          );
    }

    HW_WR_REG32(addrOfL1Desc, l1DescCoarseLP);

    for (i = 0; i < 16U; i++)
    {
        HW_WR_REG32(addrOfL2Desc + (4U * i), l2DescCoarseLP);
    }

    return returnCode;
}

MMU_Return_t MMUCoarseSmallPage(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    const uint32_t    pageTableBase,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    )
{
    MMU_Return_t returnCode = RET_OK;
    uint32_t     addrOfL1Desc, l1DescCoarseSP, addrOfL2Desc, l2DescCoarseSP;
    uint32_t     TTB_13_to_7, VA_31_to_25, desc_13_to_7;

    /*Check the input Parameters*/
    /*CHECK_INPUT_RANGE_MIN0(elementSize,MMU_ELEMENTSIZE_MAX,RET_PARAM_OUT_OF_RANGE,RES_MMU_BASE
    *+ RES_INVALID_INPUT_PARAM);*/

    /* Generate the ADDRESS of First Level Descriptor for a Coarse Small Page */
    TTB_13_to_7  = ((TTB >> 7U) & 0x0000007FU);
    VA_31_to_25  = ((virtualAddr >> 25U) & 0x0000007FU);
    desc_13_to_7 = (((TTB_13_to_7 + VA_31_to_25) & 0x0000007FU) << 7U);
    addrOfL1Desc =
        ((TTB &
          MMU_TTB_MASK) | desc_13_to_7 |
         ((virtualAddr >> 18U) & 0x0000007CU));

    /* Generate the First Level Descriptor for a Coarse Small Page */
    if (faultType == MMU_FAULT_DESC1)
    {
        l1DescCoarseSP = (pageTableBase & MMU_PAGE_TABLE_MASK);
    }
    else
    {
        l1DescCoarseSP = ((pageTableBase & MMU_PAGE_TABLE_MASK) | 1U);
    }

    /* Generate the ADDRESS of Second Level Descriptor for a Coarse Small Page
    **/
    addrOfL2Desc = ((pageTableBase & MMU_PAGE_TABLE_MASK) |
                    (((virtualAddr &
                       0x000FF000U) >> 10U) & 0x000003FCU)
                    );

    /* Generate the Second Level Descriptor for a Coarse Small Page */
    if (faultType == MMU_FAULT_DESC2)
    {
        l2DescCoarseSP = ((physicalAddr & MMU_SMALL_PAGE_MASK) |
                          ((uint32_t) endianism << 9U) |
                          ((uint32_t) elementSize << 4U) |
                          ((uint32_t) mixedSize << 11U)
                          );
    }
    else
    {
        l2DescCoarseSP = ((physicalAddr & MMU_SMALL_PAGE_MASK) |
                          ((uint32_t) endianism << 9U) |
                          ((uint32_t) elementSize << 4U) |
                          ((uint32_t) mixedSize << 11U) |
                          2U
                          );
    }

    HW_WR_REG32(addrOfL1Desc, l1DescCoarseSP);
    HW_WR_REG32(addrOfL2Desc, l2DescCoarseSP);

    return returnCode;
}
/********************************* End of file ******************************/
