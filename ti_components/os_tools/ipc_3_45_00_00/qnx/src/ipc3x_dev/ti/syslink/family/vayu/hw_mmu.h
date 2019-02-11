/*
 *  @file  hw_mbox.h
 *
 *  @brief  Functions required to program MMU
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013, Texas Instruments Incorporated
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

#ifndef __HW_MMU_H
#define __HW_MMU_H


/* Bitmasks for interrupt sources */
#define HW_MMU_TRANSLATION_FAULT   0x2
#define HW_MMU_ALL_INTERRUPTS      0x1F

#define HW_MMU_COARSE_PAGE_SIZE 0x400

/* hw_mmu_mixed_size_t:  Enumerated Type used to specify whether to follow
            CPU/TLB Element size */
enum hw_mmu_mixed_size_t {
    HW_MMU_TLBES,
    HW_MMU_CPUES

} ;

/* hw_mmu_map_attrs_t:  Struct containing MMU mapping attributes */
struct hw_mmu_map_attrs_t {
    enum hw_endianism_t     endianism;
    enum hw_elemnt_siz_t   element_size;
    enum hw_mmu_mixed_size_t  mixedSize;
} ;

extern hw_status hw_mmu_enable(const UInt32 base_address);

extern hw_status hw_mmu_disable(const UInt32 base_address);

extern hw_status hw_mmu_numlocked_set(const UInt32 base_address,
                      UInt32 num_lcked_entries);

extern hw_status hw_mmu_victim_numset(const UInt32 base_address,
                      UInt32 vctm_entry_num);

/* For MMU faults */
extern hw_status hw_mmu_eventack(const UInt32 base_address,
                 UInt32 irq_mask);

extern hw_status hw_mmu_event_disable(const UInt32 base_address,
                      UInt32 irq_mask);

extern hw_status hw_mmu_event_enable(const UInt32 base_address,
                     UInt32 irq_mask);

extern hw_status hw_mmu_event_status(const UInt32 base_address,
                     UInt32 *irq_mask);

extern hw_status hw_mmu_flt_adr_rd(const UInt32 base_address,
                   UInt32 *addr);

/* Set the TT base address */
extern hw_status hw_mmu_ttbset(const UInt32 base_address,
                   UInt32 ttb_phys_addr);

extern hw_status hw_mmu_twl_enable(const UInt32 base_address);

extern hw_status hw_mmu_twl_disable(const UInt32 base_address);

extern hw_status hw_mmu_tlb_flush(const UInt32 base_address,
                  UInt32 virtual_addr,
                  UInt32 page_size);

extern hw_status hw_mmu_tlb_flushAll(const UInt32 base_address);

extern hw_status hw_mmu_tlb_add(const UInt32     base_address,
                UInt32       physical_addr,
                UInt32       virtual_addr,
                UInt32       page_size,
                UInt32        entryNum,
                struct hw_mmu_map_attrs_t *map_attrs,
                enum hw_set_clear_t    preserve_bit,
                enum hw_set_clear_t    valid_bit);


/* For PTEs */
extern hw_status hw_mmu_pte_set(const UInt32     pg_tbl_va,
                UInt32       physical_addr,
                UInt32       virtual_addr,
                UInt32       page_size,
                struct hw_mmu_map_attrs_t *map_attrs);

extern hw_status hw_mmu_pte_clear(const UInt32   pg_tbl_va,
                  UInt32     pg_size,
                  UInt32     virtual_addr);

static inline UInt32 hw_mmu_pte_addr_l1(UInt32 l1_base, UInt32 va)
{
    UInt32 pte_addr;
    UInt32 VA_31_to_20;

    VA_31_to_20  = va >> (20 - 2); /* Left-shift by 2 here itself */
    VA_31_to_20 &= 0xFFFFFFFCUL;
    pte_addr = l1_base + VA_31_to_20;

    return pte_addr;
}

static inline UInt32 hw_mmu_pte_addr_l2(UInt32 l2_base, UInt32 va)
{
    UInt32 pte_addr;

    pte_addr = (l2_base & 0xFFFFFC00) | ((va >> 10) & 0x3FC);

    return pte_addr;
}

static inline UInt32 hw_mmu_pte_coarsel1(UInt32 pte_val)
{
    UInt32 pteCoarse;

    pteCoarse = pte_val & 0xFFFFFC00;

    return pteCoarse;
}

static inline UInt32 hw_mmu_pte_sizel1(UInt32 pte_val)
{
    UInt32 pte_size = 0;

    if ((pte_val & 0x3) == 0x1) {
        /* Points to L2 PT */
        pte_size = HW_MMU_COARSE_PAGE_SIZE;
    }

    if ((pte_val & 0x3) == 0x2) {
        if (pte_val & (1 << 18))
            pte_size = HW_PAGE_SIZE_16MB;
        else
            pte_size = HW_PAGE_SIZE_1MB;
    }

    return pte_size;
}

static inline UInt32 hw_mmu_pte_sizel2(UInt32 pte_val)
{
    UInt32 pte_size = 0;

    if (pte_val & 0x2)
        pte_size = HW_PAGE_SIZE_4KB;
    else if (pte_val & 0x1)
        pte_size = HW_PAGE_SIZE_64KB;

    return pte_size;
}
extern hw_status hw_mmu_tlb_dump(UInt32 base_address, BOOL shw_inv_entries);

extern UInt32 hw_mmu_pte_phyaddr(UInt32 pte_val, UInt32 pte_size);

#endif  /* __HW_MMU_H */
