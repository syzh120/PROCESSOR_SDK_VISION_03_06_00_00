/*
 *  @file  hw_mbox.c
 *
 *  @brief  Functions required to program MMU
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2011, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */



#include <ti/syslink/Std.h>
#include <GlobalTypes.h>
#include <MMURegAcM.h>
#include <hw_defs.h>
#include <hw_mmu.h>

#define MMU_BASE_VAL_MASK        0xFC00
#define MMU_PAGE_MAX             3
#define MMU_ELEMENTSIZE_MAX      3
#define MMU_ADDR_MASK            0xFFFFF000
#define MMU_TTB_MASK             0xFFFFC000
#define MMU_SECTION_ADDR_MASK    0xFFF00000
#define MMU_SSECTION_ADDR_MASK   0xFF000000
#define MMU_PAGE_TABLE_MASK      0xFFFFFC00
#define MMU_LARGE_PAGE_MASK      0xFFFF0000
#define MMU_SMALL_PAGE_MASK      0xFFFFF000

#define MMU_LOAD_TLB        0x00000001
#define NUM_TLB_ENTRIES 32

/*
* type: hw_mmu_pgsiz_t
*
* desc:  Enumerated Type used to specify the MMU Page Size(SLSS)
*
*
*/
enum hw_mmu_pgsiz_t {
    HW_MMU_SECTION,
    HW_MMU_LARGE_PAGE,
    HW_MMU_SMALL_PAGE,
    HW_MMU_SUPERSECTION

};

/*
* function : mmu_flsh_entry
*/

static hw_status mmu_flsh_entry(const UInt32   base_address);

 /*
* function : mme_set_cam_entry
*
*/

static hw_status mme_set_cam_entry(const UInt32    base_address,
    const UInt32    page_size,
    const UInt32    preserve_bit,
    const UInt32    valid_bit,
    const UInt32    virt_addr_tag);

/*
* function  : mmu_set_ram_entry
*/
static hw_status mmu_set_ram_entry(const UInt32        base_address,
    const UInt32        physical_addr,
    enum hw_endianism_t      endianism,
    enum hw_elemnt_siz_t    element_size,
    enum hw_mmu_mixed_size_t   mixedSize);

/*
* hw functions
*
*/

hw_status hw_mmu_enable(const UInt32 base_address)
{
    hw_status status = RET_OK;

    MMUMMU_CNTLMMUEnableWrite32(base_address, HW_SET);

    return status;
}

hw_status hw_mmu_disable(const UInt32 base_address)
{
    hw_status status = RET_OK;

    MMUMMU_CNTLMMUEnableWrite32(base_address, HW_CLEAR);

    return status;
}

hw_status hw_mmu_nulck_set(const UInt32 base_address, UInt32 *num_lcked_entries)
{
    hw_status status = RET_OK;

    *num_lcked_entries = MMUMMU_LOCKBaseValueRead32(base_address);

    return status;
}


hw_status hw_mmu_numlocked_set(const UInt32 base_address, UInt32 num_lcked_entries)
{
    hw_status status = RET_OK;

    MMUMMU_LOCKBaseValueWrite32(base_address, num_lcked_entries);

    return status;
}



hw_status hw_mmu_vctm_numget(const UInt32 base_address, UInt32 *vctm_entry_num)
{
    hw_status status = RET_OK;

    *vctm_entry_num = MMUMMU_LOCKCurrentVictimRead32(base_address);

    return status;
}



hw_status hw_mmu_victim_numset(const UInt32 base_address, UInt32 vctm_entry_num)
{
    hw_status status = RET_OK;

    mmu_lck_crnt_vctmwite32(base_address, vctm_entry_num);

    return status;
}

hw_status hw_mmu_tlb_flushAll(const UInt32 base_address)
{
    hw_status status = RET_OK;

    MMUMMU_GFLUSHGlobalFlushWrite32(base_address, HW_SET);

    return status;
}

hw_status hw_mmu_eventack(const UInt32 base_address, UInt32 irq_mask)
{
    hw_status status = RET_OK;

    MMUMMU_IRQSTATUSWriteRegister32(base_address, irq_mask);

    return status;
}

hw_status hw_mmu_event_disable(const UInt32 base_address, UInt32 irq_mask)
{
    hw_status status = RET_OK;
    UInt32 irqReg;
    irqReg = MMUMMU_IRQENABLEReadRegister32(base_address);

    MMUMMU_IRQENABLEWriteRegister32(base_address, irqReg & ~irq_mask);

    return status;
}

hw_status hw_mmu_event_enable(const UInt32 base_address, UInt32 irq_mask)
{
    hw_status status = RET_OK;
    UInt32 irqReg;

    irqReg = MMUMMU_IRQENABLEReadRegister32(base_address);

    MMUMMU_IRQENABLEWriteRegister32(base_address, irqReg | irq_mask);

    return status;
}

hw_status hw_mmu_event_status(const UInt32 base_address, UInt32 *irq_mask)
{
    hw_status status = RET_OK;

    *irq_mask = MMUMMU_IRQSTATUSReadRegister32(base_address);

    return status;
}

hw_status hw_mmu_flt_adr_rd(const UInt32 base_address, UInt32 *addr)
{
    hw_status status = RET_OK;

    /*Check the input Parameters*/
    CHECK_INPUT_PARAM(base_address, 0, RET_BAD_NULL_PARAM,
                    RES_MMU_BASE + RES_INVALID_INPUT_PARAM);
    /* read values from register */
    *addr = MMUMMU_FAULT_ADReadRegister32(base_address);

    return status;
}


hw_status hw_mmu_ttbset(const UInt32 base_address, UInt32 ttb_phys_addr)
{
    hw_status status = RET_OK;
    UInt32 loadTTB;

    /*Check the input Parameters*/
    CHECK_INPUT_PARAM(base_address, 0, RET_BAD_NULL_PARAM,
                    RES_MMU_BASE + RES_INVALID_INPUT_PARAM);

    loadTTB = ttb_phys_addr & ~0x7FUL;
    /* write values to register */
    MMUMMU_TTBWriteRegister32(base_address, loadTTB);

    return status;
}

hw_status hw_mmu_twl_enable(const UInt32 base_address)
{
    hw_status status = RET_OK;

    MMUMMU_CNTLTWLEnableWrite32(base_address, HW_SET);

    return status;
}

hw_status hw_mmu_twl_disable(const UInt32 base_address)
{
    hw_status status = RET_OK;

    MMUMMU_CNTLTWLEnableWrite32(base_address, HW_CLEAR);

    return status;
}


hw_status hw_mmu_tlb_flush(const UInt32 base_address,
    UInt32 virtual_addr,
    UInt32 page_size)
{
    hw_status status = RET_OK;
    UInt32 virt_addr_tag;
    enum hw_mmu_pgsiz_t pg_sizeBits;

    switch (page_size) {
    case HW_PAGE_SIZE_4KB:
    pg_sizeBits = HW_MMU_SMALL_PAGE;
    break;

    case HW_PAGE_SIZE_64KB:
    pg_sizeBits = HW_MMU_LARGE_PAGE;
    break;

    case HW_PAGE_SIZE_1MB:
    pg_sizeBits = HW_MMU_SECTION;
    break;

    case HW_PAGE_SIZE_16MB:
    pg_sizeBits = HW_MMU_SUPERSECTION;
    break;

    default:
    return RET_FAIL;
    }

    /* Generate the 20-bit tag from virtual address */
    virt_addr_tag = ((virtual_addr & MMU_ADDR_MASK) >> 12);

    mme_set_cam_entry(base_address, pg_sizeBits, 0, 0, virt_addr_tag);

    mmu_flsh_entry(base_address);

    return status;
}


hw_status hw_mmu_tlb_add(const UInt32        base_address,
    UInt32              physical_addr,
    UInt32              virtual_addr,
    UInt32              page_size,
    UInt32              entryNum,
    struct hw_mmu_map_attrs_t    *map_attrs,
    enum hw_set_clear_t       preserve_bit,
    enum hw_set_clear_t       valid_bit)
{
    hw_status  status = RET_OK;
    UInt32 lockReg;
    UInt32 virt_addr_tag;
    enum hw_mmu_pgsiz_t mmu_pg_size;

    /*Check the input Parameters*/
    CHECK_INPUT_PARAM(base_address, 0, RET_BAD_NULL_PARAM,
                RES_MMU_BASE + RES_INVALID_INPUT_PARAM);
    CHECK_INPUT_RANGE_MIN0(page_size, MMU_PAGE_MAX, RET_PARAM_OUT_OF_RANGE,
                RES_MMU_BASE + RES_INVALID_INPUT_PARAM);
    CHECK_INPUT_RANGE_MIN0(map_attrs->element_size,
            MMU_ELEMENTSIZE_MAX, RET_PARAM_OUT_OF_RANGE,
                RES_MMU_BASE + RES_INVALID_INPUT_PARAM);

        switch (page_size) {
        case HW_PAGE_SIZE_4KB:
        mmu_pg_size = HW_MMU_SMALL_PAGE;
        break;

        case HW_PAGE_SIZE_64KB:
        mmu_pg_size = HW_MMU_LARGE_PAGE;
        break;

        case HW_PAGE_SIZE_1MB:
        mmu_pg_size = HW_MMU_SECTION;
        break;

        case HW_PAGE_SIZE_16MB:
        mmu_pg_size = HW_MMU_SUPERSECTION;
        break;

        default:
        return RET_FAIL;
        }

    lockReg = mmu_lckread_reg_32(base_address);

    /* Generate the 20-bit tag from virtual address */
    virt_addr_tag = ((virtual_addr & MMU_ADDR_MASK) >> 12);

    /* Write the fields in the CAM Entry Register */
    mme_set_cam_entry(base_address,  mmu_pg_size, preserve_bit, valid_bit,
    virt_addr_tag);

    /* Write the different fields of the RAM Entry Register */
    /* endianism of the page,Element Size of the page (8, 16, 32, 64 bit) */
    mmu_set_ram_entry(base_address, physical_addr,
    map_attrs->endianism, map_attrs->element_size, map_attrs->mixedSize);

    /* Update the MMU Lock Register */
    /* currentVictim between lockedBaseValue and (MMU_Entries_Number - 1) */
    mmu_lck_crnt_vctmwite32(base_address, entryNum);

    /* Enable loading of an entry in TLB by writing 1 into LD_TLB_REG
    register */
    mmu_ld_tlbwrt_reg32(base_address, MMU_LOAD_TLB);


    mmu_lck_write_reg32(base_address, lockReg);

    return status;
}



hw_status hw_mmu_pte_set(const UInt32        pg_tbl_va,
    UInt32              physical_addr,
    UInt32              virtual_addr,
    UInt32              page_size,
    struct hw_mmu_map_attrs_t    *map_attrs)
{
    hw_status status = RET_OK;
    UInt32 pte_addr, pte_val;
    long int num_entries = 1;

    switch (page_size) {

    case HW_PAGE_SIZE_4KB:
    pte_addr = hw_mmu_pte_addr_l2(pg_tbl_va, virtual_addr &
        MMU_SMALL_PAGE_MASK);
    pte_val = ((physical_addr & MMU_SMALL_PAGE_MASK) |
    (map_attrs->endianism << 9) |
    (map_attrs->element_size << 4) |
    (map_attrs->mixedSize << 11) | 2
    );
    break;

    case HW_PAGE_SIZE_64KB:
    num_entries = 16;
    pte_addr = hw_mmu_pte_addr_l2(pg_tbl_va, virtual_addr &
        MMU_LARGE_PAGE_MASK);
    pte_val = ((physical_addr & MMU_LARGE_PAGE_MASK) |
    (map_attrs->endianism << 9) |
    (map_attrs->element_size << 4) |
    (map_attrs->mixedSize << 11) | 1
    );
    break;

    case HW_PAGE_SIZE_1MB:
    pte_addr = hw_mmu_pte_addr_l1(pg_tbl_va, virtual_addr &
        MMU_SECTION_ADDR_MASK);
    pte_val = ((((physical_addr & MMU_SECTION_ADDR_MASK) |
    (map_attrs->endianism << 15) |
    (map_attrs->element_size << 10) |
    (map_attrs->mixedSize << 17)) &
    ~0x40000) | 0x2
    );
    break;

    case HW_PAGE_SIZE_16MB:
    num_entries = 16;
    pte_addr = hw_mmu_pte_addr_l1(pg_tbl_va, virtual_addr &
        MMU_SSECTION_ADDR_MASK);
    pte_val = ((physical_addr & MMU_SSECTION_ADDR_MASK) |0x40022);
    break;

    case HW_MMU_COARSE_PAGE_SIZE:
    pte_addr = hw_mmu_pte_addr_l1(pg_tbl_va, virtual_addr &
        MMU_SECTION_ADDR_MASK);
    pte_val = (physical_addr & MMU_PAGE_TABLE_MASK) | 1;
    break;

    default:
    return RET_FAIL;
    }

    while (--num_entries >= 0)
        ((ULONG*)pte_addr)[num_entries] = pte_val;


    return status;
}

hw_status hw_mmu_pte_clear(const UInt32  pg_tbl_va,
    UInt32        virtual_addr,
    UInt32        pg_size)
{
    hw_status status = RET_OK;
    UInt32 pte_addr;
    long int num_entries = 1;

    switch (pg_size) {
    case HW_PAGE_SIZE_4KB:
    pte_addr = hw_mmu_pte_addr_l2(pg_tbl_va,
            virtual_addr & MMU_SMALL_PAGE_MASK);
    break;

    case HW_PAGE_SIZE_64KB:
    num_entries = 16;
    pte_addr = hw_mmu_pte_addr_l2(pg_tbl_va,
            virtual_addr & MMU_LARGE_PAGE_MASK);
    break;

    case HW_PAGE_SIZE_1MB:
    case HW_MMU_COARSE_PAGE_SIZE:
    pte_addr = hw_mmu_pte_addr_l1(pg_tbl_va,
            virtual_addr & MMU_SECTION_ADDR_MASK);
    break;

    case HW_PAGE_SIZE_16MB:
    num_entries = 16;
    pte_addr = hw_mmu_pte_addr_l1(pg_tbl_va,
            virtual_addr & MMU_SSECTION_ADDR_MASK);
    break;

    default:
    return RET_FAIL;
    }

    while (--num_entries >= 0)
        ((UInt32 *)pte_addr)[num_entries] = 0;

    return status;
}

/*
* function: mmu_flsh_entry
*/
static hw_status mmu_flsh_entry(const UInt32 base_address)
{
    hw_status status = RET_OK;
    UInt32 flushEntryData = 0x1;

    /*Check the input Parameters*/
    CHECK_INPUT_PARAM(base_address, 0, RET_BAD_NULL_PARAM,
                RES_MMU_BASE + RES_INVALID_INPUT_PARAM);

    /* write values to register */
    MMUMMU_FLUSH_ENTRYWriteRegister32(base_address, flushEntryData);

    return status;
}
/*
* function : mme_set_cam_entry
*/
static hw_status mme_set_cam_entry(const UInt32    base_address,
    const UInt32    page_size,
    const UInt32    preserve_bit,
    const UInt32    valid_bit,
    const UInt32    virt_addr_tag)
{
    hw_status status = RET_OK;
    UInt32 mmuCamReg;

    /*Check the input Parameters*/
    CHECK_INPUT_PARAM(base_address, 0, RET_BAD_NULL_PARAM,
                RES_MMU_BASE + RES_INVALID_INPUT_PARAM);

    mmuCamReg = (virt_addr_tag << 12);
    mmuCamReg = (mmuCamReg) | (page_size) |  (valid_bit << 2)
                        | (preserve_bit << 3);

    /* write values to register */
    MMUMMU_CAMWriteRegister32(base_address, mmuCamReg);

    return status;
}
/*
* function: mmu_set_ram_entry
*/
static hw_status mmu_set_ram_entry(const UInt32       base_address,
    const UInt32       physical_addr,
    enum hw_endianism_t     endianism,
    enum hw_elemnt_siz_t   element_size,
    enum hw_mmu_mixed_size_t  mixedSize)
{
    hw_status status = RET_OK;
    UInt32 mmuRamReg;

    /*Check the input Parameters*/
    CHECK_INPUT_PARAM(base_address, 0, RET_BAD_NULL_PARAM,
                    RES_MMU_BASE + RES_INVALID_INPUT_PARAM);
    CHECK_INPUT_RANGE_MIN0(element_size, MMU_ELEMENTSIZE_MAX,
                    RET_PARAM_OUT_OF_RANGE,
                    RES_MMU_BASE + RES_INVALID_INPUT_PARAM);


    mmuRamReg = (physical_addr & MMU_ADDR_MASK);
    mmuRamReg = (mmuRamReg) | ((endianism << 9) |  (element_size << 7)
                    | (mixedSize << 6));

    /* write values to register */
    MMUMMU_RAMWriteRegister32(base_address, mmuRamReg);

    return status;

}

UInt32 hw_mmu_pte_phyaddr(UInt32 pte_val, UInt32 pte_size)
{
    UInt32    ret_val = 0;

    switch (pte_size) {

    case HW_PAGE_SIZE_4KB:
        ret_val = pte_val & MMU_SMALL_PAGE_MASK;
        break;
    case HW_PAGE_SIZE_64KB:
        ret_val = pte_val & MMU_LARGE_PAGE_MASK;
        break;

    case HW_PAGE_SIZE_1MB:
        ret_val = pte_val & MMU_SECTION_ADDR_MASK;
        break;
    case HW_PAGE_SIZE_16MB:
        ret_val = pte_val & MMU_SSECTION_ADDR_MASK;
        break;
    default:
        /*  Invalid  */
        break;

    }

    return ret_val;
}
