/*
 *  Copyright (c) Texas Instruments Incorporated 2015
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
 *  \ingroup CSL_ARCH_A15
 *  \defgroup CSL_ARCH_A15_MMU MMU
 *
 *  @{
 */
/**
 *  \file     mmu_a15.h
 *
 *  \brief    This file contains the interfaces present in the A15 MMU HAL.
 *            This also contains some related macros, structures and enums.
 *            This implementation supports only two levels of translation
 *            tables. Physical address is 40 bits long instead of 32 bits.
 */

#ifndef MMU_A15_H_
#define MMU_A15_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  This macro defines the number of entries in first level table buffer.
 */
#define MMU_A15_NUM_FIRST_LEVEL_BUFFER_ENTRIES         ((uint32_t) 4U)

/**
 * \brief  This macro defines the number of entries in second level table
 *         buffer.
 */
#define MMU_A15_NUM_SECOND_LEVEL_BUFFER_ENTRIES        ((uint32_t) 512U)

/**
 * \brief  This macro defines that next table is in secure space
 */
#define MMU_A15_NT_MEM_SPACE_SECURE                    ((uint32_t) 0U)

/**
 * \brief  This macro defines that next table is in non-secure space
 */
#define MMU_A15_NT_MEM_SPACE_NON_SECURE                ((uint32_t) 1U)

/**
 * \brief  This macro defines the access permissions for look-up as no effect
 */
#define MMU_A15_NT_ACC_PERM_NO_EFFECT                   ((uint32_t) 0U)

/**
 * \brief  This macro defines the access permissions for look-up as no access
 *         at PL0.
 */
#define MMU_A15_NT_ACC_PERM_NO_ACCESS_PL0              ((uint32_t) 1U)

/**
 * \brief  This macro defines the access permissions for look-up as no write
 *         access.
 */
#define MMU_A15_NT_ACC_PERM_NO_WR                      ((uint32_t) 2U)

/**
 * \brief  This macro defines the access permissions for look-up as no write
 *         access and no read access at PL0
 */
#define MMU_A15_NT_ACC_PERM_NO_WR_NO_RD_PL0            ((uint32_t) 3U)

/**
 * \brief  This macro defines the execute never bit for subsequent look-up
 *         as no effect.
 */
#define MMU_A15_NT_XN_NO_EFFECT                        ((uint32_t) 0U)

/**
 * \brief  This macro defines the execute never bit for subsequent look-up
 *         as always 1.
 */
#define MMU_A15_NT_XN_ALWAYS_ON                        ((uint32_t) 1U)

/**
 * \brief  This macro defines the privilege execute never bit for subsequent
 *         look-up as no effect.
 */
#define MMU_A15_NT_PXN_NO_EFFECT                       ((uint32_t) 0U)

/**
 * \brief  This macro defines the privilege execute never bit for subsequent
 *         look-up as always 1.
 */
#define MMU_A15_NT_PXN_ALWAYS_ON                       ((uint32_t) 1U)

/**
 * \brief  This macro enables the execute never  bit.
 */
#define MMU_A15_XN_ENABLE                              ((uint32_t) 1U)

/**
 * \brief  This macro disables the execute never  bit.
 */
#define MMU_A15_XN_DISABLE                             ((uint32_t) 0U)

/**
 * \brief  This macro enables the privilege execute never  bit.
 */
#define MMU_A15_PXN_ENABLE                             ((uint32_t) 1U)

/**
 * \brief  This macro disables the privilege execute never  bit.
 */
#define MMU_A15_PXN_DISABLE                            ((uint32_t) 0U)

/**
 * \brief  This macro enables the contiguous hint.
 */
#define MMU_A15_CONTIGUOUS_HINT_ENABLE                 ((uint32_t) 1U)

/**
 * \brief  This macro disables the contiguous hint.
 */
#define MMU_A15_CONTIGUOUS_HINT_DISABLE                ((uint32_t) 0U)

/* These macros enable/disable the not global bit */
#define MMU_A15_NOT_GLOBAL_ENABLE                      ((uint32_t) 1U)
#define MMU_A15_NOT_GLOBAL_DISABLE                     ((uint32_t) 0U)

/* These macros enable/disable the access flag */
#define MMU_A15_ACCESS_FLAG_ENABLE                     ((uint32_t) 1U)
#define MMU_A15_ACCESS_FLAG_DISABLE                    ((uint32_t) 0U)

/* These macros define shareable property as non-shareable, unpredictable,
 * outer and inner
 */
#define MMU_A15_NON_SHAREABLE                          ((uint32_t) 0U)
#define MMU_A15_SHAREABLE_UNPREDICTABLE                ((uint32_t) 1U)
#define MMU_A15_SHAREABLE_OUTER                        ((uint32_t) 2U)
#define MMU_A15_SHAREABLE_INNER                        ((uint32_t) 3U)

/* These macros define access permissions as:
 * 0: Read write, only at PL1
 * 1: Read write at any privilege level
 * 2: Read Only, Only at PL1
 * 3: Read only at any privilege level
 */
#define MMU_A15_ACC_PERM_RW_PL1                        ((uint32_t) 0U)
#define MMU_A15_ACC_PERM_RW_ANY_PL                     ((uint32_t) 1U)
#define MMU_A15_ACC_PERM_RD_PL1                        ((uint32_t) 2U)
#define MMU_A15_ACC_PERM_RD_ANY_PL                     ((uint32_t) 3U)

/* These macros enable/disable the non-secure bit */
#define MMU_A15_NON_SECURE_ENABLE                      ((uint32_t) 1U)
#define MMU_A15_NON_SECURE_DISABLE                     ((uint32_t) 0U)

/* These macros define the Attribute Index that should be used */
#define MMU_A15_ATTR_INDEX_0                           ((uint32_t) 0U)
#define MMU_A15_ATTR_INDEX_1                           ((uint32_t) 1U)
#define MMU_A15_ATTR_INDEX_2                           ((uint32_t) 2U)
#define MMU_A15_ATTR_INDEX_3                           ((uint32_t) 3U)
#define MMU_A15_ATTR_INDEX_4                           ((uint32_t) 4U)
#define MMU_A15_ATTR_INDEX_5                           ((uint32_t) 5U)
#define MMU_A15_ATTR_INDEX_6                           ((uint32_t) 6U)
#define MMU_A15_ATTR_INDEX_7                           ((uint32_t) 7U)

/* These macros defines the number of attribute index entries */
#define MMU_A15_NUM_ATTR_INDEX_ENTRIES                 ((uint32_t) 8U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to select the MMU descriptor type.
 */
typedef enum mmuA15DescriptorType
{
    MMU_A15_DESCRIPTOR_TYPE_INVALID0 = 0x0U,
    /**< Descriptor type is Invalid0 */
    MMU_A15_DESCRIPTOR_TYPE_BLOCK = 0x1U,
    /**< Descriptor type is Block */
    MMU_A15_DESCRIPTOR_TYPE_INVALID1 = 0x2U,
    /**< Descriptor type is Invalid1 */
    MMU_A15_DESCRIPTOR_TYPE_TABLE = 0x3U,
    /**< Descriptor type is Table */
} mmuA15DescriptorType_t;

/**
 *  \brief This structure defines the attributes of A15 MMU descriptor.
 *
 *         Details Table Descriptor:
 *           Bits[58:52] are Ignored
 *           Bits[51:40] are UNK(Unknown on fault)/SBZP (Should be zero or
 *           preserved)
 *           Bits [39:12] Contain Next table address, Bits[11:0] of table
 *           address are 0
 *           Bits [11:2] Ignored
 *           Block Descriptor:
 *           Bits[63:52] Upper Block Attributes
 *           Bits[51:40] are UNK(Unknown on fault)/SBZP (Should be zero or
 *           preserved)
 *           Bits[39:12]
 *           For first level descriptor Bits[39:30] are output address of 1 GB
 *           block, Bits[29:12] are UNK/SBZP
 *           For second level descriptor Bits[39:21] are output address of 2 MB
 *           block, Bits[29:12] are UNK/SBZP
 *           For third level descriptor Bits[39:12] are output address of 4 KB
 *           page.
 *           Bits[11:2] are Lower Block Attributes
 */
typedef struct mmuA15DescriptorAttrs
{
    uint32_t descriptorType;
    /**< Bits[1:0] Descriptor type.
     * Refer enum #mmuA15DescriptorType_t for values.
     */
    uint32_t nsTable;
    /**< Bit[63]
     * Next Level table attribute, Table is in secure or non-secure memory
     * 0: Defined table is in secure physical address space
     * 1: Defined table is in non-secure physical address space
     */
    uint32_t apTable;
    /**< Bits[62:61]
     * Next Level table attribute, access permissions for lookup
     * 0: No effect on permissions in subsequent lookup
     * 1: Access at PL0 is not permitted, regardless of subsequent permissions
     * 2: Write access is not permitted at any privilege level regardless of
     *    subsequent permissions
     * 3: Write access is not permitted at any privilege level and read access
     *    is not permitted at PL0 regardless of subsequent permissions
     */
    uint32_t xnTable;
    /**< Bit[60]
     * Next Level table attribute, execute never
     * 0: No effect
     * 1: Execute never bit is 1 in all subsequent levels
     */
    uint32_t pxnTable;
    /**< Bit[59]
     * Next Level table attribute, privilege execute never
     * 0: No effect
     * 1: Privilege Execute never bit is 1 in all subsequent levels
     */
    uint32_t noExecute;
    /**< Bit [54], Execute Never
     * 1:Enable 0:Disable
     */
    uint32_t privNoExecute;
    /**< Bit[53], Privilege execute never
     * 1:Enable 0:Disable*/
    uint32_t contiguous;
    /**<  Bit[52]
     * Contiguous hint bit, Setting this bit to 1 indicates that 16 adjacent
     * translation table entries point to a contiguous output address range
     */
    uint32_t notGlobal;
    /**< Bit[11]
     * Not Global bit, Setting this bit to 1 indicates that translation is
     * process specific.
     */
    uint32_t accessFlag;
    /**< Bit[10]
     * Access Flag, Access Fault is generated if this flag is 0 and entry is
     * read into TLB
     */
    uint32_t shareable;
    /**< Bits[9:8]
     * Shareablitity field
     * 00: Non-shareable 01:Unpredictable 10:Outer Shareable 11:Inner Shareable
     */
    uint32_t accPerm;
    /**< Bits[7:6] AP[2:1]
     * AP[2]: Disable write access AP[1]: Enable Unprivileged access
     * 00: Read/write, only at PL1 01: Read/write, at any privilege level
     * 10: Read-only, only at PL1  11: Read-only, at any privilege level
     */
    uint32_t nonSecure;
    /**< Bit[5]
     * Non-secure bit. For memory access from secure state, specifies whether
     * output is in secure or non-secure memory
     * 1:Non-secure 0:Secure
     */
    uint32_t attrIndx;
    /**< Bits[4:2]
     * Memory Attributes field, for Memory Attriute Indirection Register MAIR
     * Bit[4]:0 Use MAIR0, 1:Use MAIR1
     * AttrIndx[2:0] gives the value of m in Attrm
     * Attrm[7:4] 0100 Normal memory, outer non-cacheable
     *            1011 Normal memory, outer write through cacheable
     *            1111 Normal memory, outer write back cacheable
     * Attrm[3:0] 0100 Normal memory, inner non-cacheable
     *            1011 Normal memory, inner write through cacheable
     *            1111 Normal memory, inner write back cacheable
     */
}mmuA15DescriptorAttrs_t;

/**
 *  \brief This structure defines the table of the MMU module.
 *
 *  \note  This structure should be placed at an address that is 16K aligned.
 */
typedef struct mmuA15ModuleTable
{
    uint64_t secondLevelTableBuff[
        MMU_A15_NUM_FIRST_LEVEL_BUFFER_ENTRIES][
        MMU_A15_NUM_SECOND_LEVEL_BUFFER_ENTRIES];
    /**< Second Level Table Buffer */
    uint64_t firstLevelTableBuff[
        MMU_A15_NUM_FIRST_LEVEL_BUFFER_ENTRIES];
    /**< First Level Table Buffer */
    uint32_t mairRegAttr[MMU_A15_NUM_ATTR_INDEX_ENTRIES];
    /**< Attributes of MAIR register */
}mmuA15ModuleTable_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function initializes the A15 MMU.
 *
 * \return  None.
 */
void MMUA15Init(void);

/**
 * \brief   This function disables the A15 MMU.
 *
 * \return  None.
 */
void MMUA15Disable(void);

/**
 * \brief   This function enables the A15 MMU.
 *
 * \param   mmuTable     MMU module table.
 *
 * \return  None.
 */
void MMUA15Enable(const mmuA15ModuleTable_t *mmuTable);

/**
 * \brief   This function initializes the descriptor attributes to a default
 *          value.
 *
 * \param   attrs   Descriptor Attributes.
 *
 * \return  None.
 */
void MMUA15InitDescAttrs(mmuA15DescriptorAttrs_t *attrs);

/**
 * \brief   This function determines whether MMU is enabled or not.
 *
 * \return  enabledStatus       MMU Enable Status.
 *                              1:Enabled 0:Disabled
 */
uint32_t MMUA15IsEnabled(void);

/**
 * \brief   This function sets the descriptor for the virtual address.
 *
 * \param   mmuTable     MMU module table.
 * \param   virtualAddr  Virtual Address.
 * \param   phyAddr      Physical Address.
 * \param   attrs        First level descriptor attributes.
 *
 * \return  status       STW_SOK: Success
 *                       STW_EFAIL: Fail
 */
int32_t MMUA15SetFirstLevelDesc(mmuA15ModuleTable_t           *mmuTable,
                                uint32_t                       virtualAddr,
                                uint64_t                       phyAddr,
                                const mmuA15DescriptorAttrs_t *attrs);

/**
 * \brief   This function sets the Memory Attriute Indirection Register for a
 *          particular attribute index.
 *
 * \param   mmuTable  MMU module table.
 * \param   attrIndx  Attriute index.
 * \param   attr      Memory attributes.
 *
 * \return  None.
 */
void MMUA15SetMAIR(mmuA15ModuleTable_t *mmuTable,
                   uint32_t             attrIndx,
                   uint32_t             attr);

/**
 * \brief   This function sets the descriptor for the virtual address.
 *
 * \param   mmuTable     MMU module table.
 * \param   virtualAddr  Virtual Address.
 * \param   phyAddr      Physical Address.
 * \param   attrs        Second level descriptor attributes.
 *
 * \return  status       STW_SOK: Success
 *                       STW_EFAIL: Fail
 */
int32_t MMUA15SetSecondLevelDesc(mmuA15ModuleTable_t           *mmuTable,
                                 uint32_t                       virtualAddr,
                                 uint64_t                       phyAddr,
                                 const mmuA15DescriptorAttrs_t *attrs);

/**
 * \brief   This function invalidates the entire TLB entries for the specified
 *          memory range.
 *
 * \param   startAddr    Start Address.
 * \param   len          Length of memory region.
 *
 * \return  None.
 */
void MMUA15TLBInvalidate(uint32_t startAddr, uint32_t len);

/**
 * \brief   This function invalidates the entire TLB.
 *
 * \return  None.
 */
void MMUA15TLBInvalidateAll(void);

#ifdef __cplusplus
}

#endif

#endif
 /** @} */
