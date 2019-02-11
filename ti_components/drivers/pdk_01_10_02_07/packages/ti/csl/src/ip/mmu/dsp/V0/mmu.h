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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_MMU MMU
 *
 *  @{
 */
/**
 *  \file  mmu.h
 *
 *  \brief This file contains the device HAL APIs for MMU.
 *
 *
 **/

#ifndef MMU_H_
#define MMU_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/cslr_mmu.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief        Interrupt enable/status types
 *
 **/
typedef enum MMU_IntType
{
    MMU_INT_TLBMiss          = MMU_IRQSTATUS_TLBMISS_MASK,
    MMU_INT_TranslationFault = MMU_IRQSTATUS_TRANSLATIONFAULT_MASK,
    MMU_INT_EMUMiss          = MMU_IRQSTATUS_EMUMISS_MASK,
    MMU_INT_TableWalkFault   = MMU_IRQSTATUS_TABLEWALKFAULT_MASK,
    MMU_INT_MultiHitFault    = MMU_IRQSTATUS_MULTIHITFAULT_MASK,
    MMU_INT_All              = 0x1FU
} MMU_IntType_t;

/**
 *
 * \brief        Enumerated Type used to specify Page size
 *
**/
typedef enum MMU_PageSize
{
    MMU_Section_Size      = MMU_CAM_PAGESIZE_SECTION,
    MMU_Large_Size        = MMU_CAM_PAGESIZE_LARGE,
    MMU_Small_Size        = MMU_CAM_PAGESIZE_SMALL,
    MMU_SuperSection_Size = MMU_CAM_PAGESIZE_SUPER,

    /* Additional enums to make them readable */
    MMU_PAGESIZE_1MB      = MMU_CAM_PAGESIZE_SECTION,
    MMU_PAGESIZE_64KB     = MMU_CAM_PAGESIZE_LARGE,
    MMU_PAGESIZE_4KB      = MMU_CAM_PAGESIZE_SMALL,
    MMU_PAGESIZE_16MB     = MMU_CAM_PAGESIZE_SUPER
} MMU_PageSize_t;

/**
 *
 * \brief        Enumerated Type used to specify Endianness
 *
 **/
typedef enum MMU_Endianness
{
    MMU_Little_Endian = 0x0,
    MMU_Big_Endian    = 0x1
} MMU_Endianness_t;

/**
 *
 * \brief        Enumerated Type used to specify Element size
 *
 **/
typedef enum MMU_ElementSize
{
    MMU_Byte_ElementSize          = 0x0,
    MMU_Short_ElementSize         = 0x1,
    MMU_Long_ElementSize          = 0x2,
    MMU_NoTranslation_ElementSize = 0x3
} MMU_ElementSize_t;

/**
 *
 * \brief        Enumerated Type used to Mixed Page Attribute use
 *
**/
typedef enum MMU_MixedPageAttr
{
    MMU_TLB_ElementSize = 0x0,
    MMU_CPU_ElementSize = 0x1
} MMU_MixedPageAttr_t;

/**
 *
 * \brief        Enumerated Type used to set MMU mode of operation
 *
**/
typedef enum
{
    MMU_FORCE_IDLE = 0x0,
    MMU_NO_IDLE    = 0x1,
    MMU_SMART_IDLE = 0x2
} MMU_Mode;

/**
 *
 * \brief        Status return from page table entry API's
 *
**/
typedef enum
{
    RET_OK,
    RET_FAIL
}MMU_Return_t;

/**
 *
 * \brief        Structure holding all MMU Table Entry parameters
 *
 **/
typedef struct MMU_TlbEntry
{
    uint32_t            phyAddr;
    uint32_t            virtAddr;
    uint32_t            valid;
    MMU_PageSize_t      pageSize;
    MMU_Endianness_t    endianness;
    MMU_ElementSize_t   elementSize;
    MMU_MixedPageAttr_t tlbElementSize;
    uint32_t            preserve;
} MMU_TlbEntry_t;

/**
 *
 * \brief        MMU element size
 *               Enumerated Type used to specify whther to follow CPU/TLB
 *               Element siz
 *
 **/

typedef enum MMUMixedSize
{
    MMU_TLBES,
    MMU_CPUES
} MMUMixedSize_t;

/**
 *
 * \brief        MMU fault type
 *               Enumerated Type used to specify the particular fault to be
 *               generated
 *
 **/
typedef enum MMUfault
{
    MMU_NO_FAULT,
    MMU_FAULT_DESC1,
    MMU_FAULT_DESC2
} MMUFault_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *
 * \brief     Set Tlb Entry in Lock register
 *            Set Current Victim in Lock register.
 * \param     baseAddr    Base address of the instance
 * \param     tlbEntry     uint32_t entry to be set in MMU
 *
 * \return    None
 *
 * \note      Fill Lock register current victim. Do not modify Locked
 *            entries.
 *
 **/
void MMUCurrentVictimSet(uint32_t baseAddr, uint32_t tlbEntry);

/**
 *
 * \brief         Set Tlb Entry in Lock register
 *                Get Current Victim from Lock register.
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return       Victim value
 *
 * \note        Return  Lock register current victim.
 *
 **/
uint32_t MMUCurrentVictimGet(uint32_t baseAddr);

/**
 * \brief         Set Tlb Lock entry in Lock register
 *                Set Tlb Lock in Lock register.
 *
 * \param         baseAddr    Base address of the instance
 * \param         tlbEntry     uint32_t entry to be locked in MMU
 *
 * \return        None
 * \note          Fill Lock register Base Value. Do not modify victim entries.
 *
 **/
void MMUTlbLockSet(uint32_t baseAddr, uint32_t tlbEntry);

/**
 * \brief         Set Tlb Lock entry in Lock register
 *                Get Tlb Base Lock from Lock register.
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        Lock base value
 *
 * \note          Get Lock register Base Value.
 *
 **/
uint32_t MMUTlbLockGet(uint32_t baseAddr);

/**
 * \brief         Flush all MMU entries
 *                Flush all Tlb entrties in MMU.
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUGlobalFlush(uint32_t baseAddr);

/**
 * \brief         Flush MMU entry for the virtual address passed
 *                Flush Specific Tlb entrties in MMU pointed by specified Virt.
 *                Addr.
 *
 * \param         baseAddr     Base address of the instance
 * \param         virtAddress  uint32_t Virtual Address of entry to be flushed
 *
 * \return        none
 *
 * \note          Write proper registers.
 *
 **/
void MMUTlbEntryFlush(uint32_t baseAddr, uint32_t virtAddress);

/**
 *
 * \brief         Reset MMU
 *                Reset MMU and wait for reset done
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        none
 *
 * \note          Set reset bit and wait for reset done.
 *
 **/
void MMUSoftReset(uint32_t baseAddr);

/**
 *
 * \brief         Set MMU operation mode
 *                Set MMU operation mode
 *
 * \param         baseAddr    Base address of the instance
 *
 * \param         mode        Operation mode
 *
 * \return        none
 *
 * \note          Set MMU operation field bits
 *
 **/
void MMUSetMode(uint32_t baseAddr, MMU_Mode mode);

/**
 *
 * \brief         Get MMU Irq Status
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        IRQ Status
 *
 * \note          Read proper register.
 *
 **/
uint32_t MMUIrqGetStatus(uint32_t baseAddr);

/**
 *
 * \brief         Clear MMU Irq Status
 *
 * \param         baseAddr    Base address of the instance
 * \param         intType      MMU_IntType_t interrupt Type to Clear
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUIrqClearStatus(uint32_t baseAddr, MMU_IntType_t intType);

/**
 *
 * \brief         Get MMU Irq Status
 *                Enable selected interrupt
 *
 * \param         baseAddr    Base address of the instance
 * \param         intType      MMU_IntType_t interrupt Type to enable
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUIrqEnable(uint32_t baseAddr, MMU_IntType_t intType);

/**
 *
 * \brief         Get MMU Irq Status
 *                Disable selected interrupt
 *
 * \param         baseAddr    Base address of the instance
 * \param         intType      MMU_IntType_t interrupt Type to be disabled
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUIrqDisable(uint32_t baseAddr, MMU_IntType_t intType);

/**
 *
 * \brief         Enable MMU Walking table logic
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUWtlEnable(uint32_t baseAddr);

/**
 *
 * \brief         Disable MMU Walking table logic
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUWtlDisable(uint32_t baseAddr);

/**
 *
 * \brief         Enable MMU
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUEnable(uint32_t baseAddr);

/**
 *
 * \brief         Disable MMU
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUDisable(uint32_t baseAddr);

/**
 *
 * \brief         Load an entry into TLB
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMULoadTLB(uint32_t baseAddr);

/**
 *
 * \brief         Write to CAM Register
 *
 * \param         baseAddr    Base address of the instance
 * \param         cam         CAM value to be entered
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUWriteCAM(uint32_t baseAddr, uint32_t cam);

/**
 *
 * \brief         Write to RAM Register
 *
 * \param         baseAddr    Base address of the instance
 * \param         ram         RAM value to be entered
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUWriteRAM(uint32_t baseAddr, uint32_t ram);

/**
 *
 * \brief         Read CAM value
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        CAM value
 *
 * \note          Write proper register.
 *
 **/
uint32_t MMUReadCAM(uint32_t baseAddr);

/**
 *
 * \brief         Read RAM value
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        RAM value
 *
 * \note          Write proper register.
 *
 **/
uint32_t MMUReadRAM(uint32_t baseAddr);

/**
 *
 * \brief         Read fault address
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        fault address
 *
 * \note          Write proper register.
 *
 **/
uint32_t MMUFaultAddrGet(uint32_t baseAddr);

/**
 *
 * \brief         Read TTB value
 *
 * \param         baseAddr    Base address of the instance
 *
 * \return        TTB value
 *
 * \note          Write proper register.
 *
 **/
uint32_t MMUTTBGet(uint32_t baseAddr);

/**
 *
 * \brief         sets TTB value
 *
 * \param         baseAddr    Base address of the instance
 * \param         ttb         TTB value to be set
 *
 * \return        none
 *
 * \note          Write proper register.
 *
 **/
void MMUTTBSet(uint32_t baseAddr, uint32_t ttb);

/**
 *
 * \brief         Fill MMU TLB Entry
 *
 * \param         baseAddr    Base address of the instance
 * \param         tlbEntry     uint32_t entry to be set in MMU
 * \param         mmuTlbEntry  MMU_TlbEntry_t * pointer to MMU Table Entry
 *
 * \return        MMU_Return_t    RET_OK                   No errors occured
 *
 * \note          Fill all necessary registers to properly configure one MMU
 *                Table entry.
 *
 **/
MMU_Return_t MMUTlbEntrySet(uint32_t              baseAddr,
                            uint32_t              tlbEntry,
                            const MMU_TlbEntry_t *mmuTlbEntry);

/**
 *
 * \brief         Fill MMU page table supersection
 *
 * \param         physicalAddr     physical address
 * \param         virtualAddr      virtual address
 * \param         TTB              translation table base addr
 * \param         endianism        endianness
 * \param         elementSize      element size of the page
 * \param         mixedSize        mixed page attribute
 * \param         faultType        fault type
 *
 *
 * \return        MMU_Return_t    RET_OK                   No errors occured
 *
 * \note          Fill  necessary memory location to properly configure one MMU
 *                supersection entry.
 *
 **/
MMU_Return_t  MMUSuperSection(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

/**
 *
 * \brief         Fill MMU page table section
 *
 * \param         physicalAddr     physical address
 * \param         virtualAddr      virtual address
 * \param         TTB              translation table base addr
 * \param         endianism        endianness
 * \param         elementSize      element size of the page
 * \param         mixedSize        mixed page attribute
 * \param         faultType        fault type
 *
 *
 * \return        MMU_Return_t    RET_OK                   No errors occured
 *
 * \note          Fill  necessary memory location to properly configure one MMU
 *                 section entry.
 *
 **/

MMU_Return_t MMUSection(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

/**
 *
 * \brief         Fill MMU page table CoarseLargePage entry
 *
 * \param         physicalAddr     physical address
 * \param         virtualAddr      virtual address
 * \param         TTB              translation table base addr
 * \param         pageTableBase   page  table base addr
 * \param         endianism        endianness
 * \param         elementSize      element size of the page
 * \param         mixedSize        mixed page attribute
 * \param         faultType        fault type
 *
 *
 * \return        MMU_Return_t    RET_OK                   No errors occured
 *
 * \note          Fill  necessary memory location to properly configure one MMU
 *                CoarseLargePage entry.
 *
 **/
MMU_Return_t MMUCoarseLargePage(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    const uint32_t    pageTableBase,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

/**
 *
 * \brief         Fill MMU page table CoarseSmallPage
 *
 * \param         physicalAddr     physical address
 * \param         virtualAddr      virtual address
 * \param         TTB              translation table base addr
 * \param         pageTableBase    page table base addr
 * \param         endianism        endianness
 * \param         elementSize      element size of the page
 * \param         mixedSize        mixed page attribute
 * \param         faultType        fault type
 *
 * \return        MMU_Return_t    RET_OK                   No errors occured
 *
 * \note          Fill  necessary memory location to properly configure one MMU
 *                CoarseSmallPage entry.
 *
 **/
MMU_Return_t MMUCoarseSmallPage(
    const uint32_t    physicalAddr,
    const uint32_t    virtualAddr,
    const uint32_t    TTB,
    const uint32_t    pageTableBase,
    MMU_Endianness_t  endianism,
    MMU_ElementSize_t elementSize,
    MMUMixedSize_t    mixedSize,
    MMUFault_t        faultType
    );

#ifdef __cplusplus
}
#endif
#endif  /* MMU_H_ */
 /** @} */
/********************************* End of file ******************************/
