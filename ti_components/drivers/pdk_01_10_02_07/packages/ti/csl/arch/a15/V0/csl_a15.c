/**
 * \file   a15_startup.c
 *
 * \brief  Interrupt vector is copied to the internal Ram. After that the
 *         control is given to the application.
 *
 *  \copyright Copyright (C) 2013-2017 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/**
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/csl.h>
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/arch/a15/V0/csl_a15.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** ============================================================================
 *   @n@b CSL_a15SetMmuFirstLevelShortDesc
 *
 *   @b Description
 *   @n This API sets the short descriptor entry of first level.
 *
 *   @b Arguments
      @verbatim
          virtualAddr   The virtual address.
          attrs         Attribute to be set for short descriptor entry of first level.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15SetMmuFirstLevelShortDesc(virtualAddr, &attrs);

     @endverbatim
 * =============================================================================
 */
void CSL_a15SetMmuFirstLevelShortDesc
(
    CSL_A15MmuShortDescObj *obj,
    const void *virtualAddr,
    const void *phyAddr,
    const CSL_A15MmuShortDescAttr *attrs
)
{
    Uint32 desc = 0U;
    Uint32 index = (Uint32)virtualAddr >> CSL_A15_MMU_SHORT_DESC_LVL1_SECTION_ADDR_SHIFT;

    /* Determine which kind of descriptor. */
    switch (attrs->type) {
        case CSL_A15_MMU_SHORT_DESC_TYPE_PAGE_TABLE:
            /* Page table descriptor */
            desc = (Uint32)CSL_A15_MMU_SHORT_DESC_TYPE_PAGE_TABLE;
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_IMPL, attrs->imp);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_DOMAIN, attrs->domain);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_TABLE_ADDR, (Uint32)phyAddr);
            break;

        /* Section descriptor */
        case CSL_A15_MMU_SHORT_DESC_TYPE_SECTION:
            desc = (Uint32)CSL_A15_MMU_SHORT_DESC_TYPE_SECTION;
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_B, attrs->bufferable);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_C, attrs->cacheable);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_XN, attrs->noexecute);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_DOMAIN, attrs->domain);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_IMPL, attrs->imp);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_AP, attrs->accPerm);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_TEX, attrs->tex);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_SHARABLE, attrs->shareable);
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_NON_SECURE, (Uint32)(attrs->nonSecure));
            CSL_FINS(desc, A15_MMU_SHORT_DESC_LVL1_SECTION_ADDR,
                (Uint32)phyAddr >> CSL_A15_MMU_SHORT_DESC_LVL1_SECTION_ADDR_SHIFT);
            break;

        default:
            break;
    }

    /* set the entry in the first level descriptor table */
    obj->firstLvlTableBuf[index] = desc;
}

/** ============================================================================
 *   @n@b CSL_a15InitMmuShortDescAttrs
 *
 *   @b Description
 *   @n This API sets the init configuration of short descriptor entry.
 *
 *   @b Arguments
      @verbatim
          attrs         Attribute to be set for short descriptor entry.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15InitMmuShortDescAttrs(&attrs);

     @endverbatim
 * =============================================================================
 */
void CSL_a15InitMmuShortDescAttrs(CSL_A15MmuShortDescAttr *attrs)
{
    attrs->type = CSL_A15_MMU_SHORT_DESC_TYPE_INVALID0;
    attrs->bufferable = 0U;
    attrs->cacheable = 0U;
    attrs->shareable = 0U;
    attrs->noexecute = 0U;
    attrs->imp = 0U;
    attrs->domain = 0U;
    attrs->accPerm = 0U;
    attrs->tex = 0U;
    attrs->nonSecure = 1U;
}

/** ============================================================================
 *   @n@b CSL_a15InitMmuShortDesc
 *
 *   @b Description
 *   @n This function is used to initialize MMU registers.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15InitMmuShortDesc();

     @endverbatim
 * =============================================================================
 */
void CSL_a15InitMmuShortDesc (CSL_A15MmuShortDescObj *obj)
{
    Uint32 i = 0U;
    Uint32 tableBuf = (Uint32) obj;
    CSL_A15MmuShortDescAttr attrs;

#if 0
    asm("mov  r1, #0                 \n\t" /*TTBR0 used and desc uses Short format*/
        "mcr  p15, #0, r1, c2, c0, #2\n\t" /*write r1 to TTBCR                */
        "isb                         \n\t" /*flush instruction pipeline       */
        "                            \n\t" /*isb makes sure cp15 changes      */
        "                            \n\t" /*are visible to all subsequent    */
        "                            \n\t" /*instructions                     */
        "mov  r1, #0                 \n\t"
        "mcr  p15, #0, r1, c8, c7, #0\n\t" /*invalidate unified TLB           */
        "dsb                         \n\t" /*wait for invalidation to complete*/
        "isb                         \n\t" /*flush instruction pipeline       */
        "                            \n\t"
        "mov  r0, %[input]           \n\t" /*get page table pointer           */
        "mcr  p15, #0, r0, c2, c0, #0\n\t" /*write TTBR0 with Module->tableBuf.*/
        "                            \n\t"
        "sub  r1, r1, #1             \n\t"
        "mcr  p15, #0, r1, c3, c0, #0\n\t" /*write domain access regs.        */
                :
                : [input] "r" (tableBuf));
#else
    CSL_a15EnableMmuShortDescTranslationTable();
    CSL_a15InvalidateAllMmuTranslationTable();
    CSL_a15SetMmuShortDescTranslationTable(tableBuf);
#endif

    CSL_a15InitMmuShortDescAttrs(&attrs);
    CSL_a15SetMmuFirstLevelShortDesc(obj, (void *)0U, (void *)0U, &attrs);

    for(i = 0U; i < obj->numFirstLvlEntires; i++)
    {
        obj->firstLvlTableBuf[i] = obj->firstLvlTableBuf[0];
    }
}

/** ============================================================================
 *   @n@b CSL_a15SetMmuFirstLevelLongDesc
 *
 *   @b Description
 *   @n This API sets the long descriptor entry of first level.
 *
 *   @b Arguments
      @verbatim
          virtualAddr   The virtual address.
          attrs         Attribute to be set for long descriptor entry of first level.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15SetMmuFirstLevelLongDesc(virtualAddr, &attrs);

     @endverbatim
 * =============================================================================
 */
void CSL_a15SetMmuFirstLevelLongDesc
(
    CSL_A15MmuLongDescObj *obj,
    const void *virtualAddr,
    const void *phyAddr,
    const CSL_A15MmuLongDescAttr *attrs
)
{
    Uint32 desc0 = 0U;
    Uint32 desc1 = 0U;
    Uint32 index = (Uint32)virtualAddr >> CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_ADDR_SHIFT;
    Uint32 phyAddr0 = 0U;
    Uint32 phyAddr1 = 0U;

    /* Determine which kind of descriptor. */
    switch (attrs->type) {
        case CSL_A15_MMU_LONG_DESC_TYPE_TABLE:
            /* Page table descriptor */
            desc0 = (Uint32)CSL_A15_MMU_LONG_DESC_TYPE_TABLE;
            phyAddr0 = (Uint32)phyAddr >> CSL_A15_MMU_LONG_DESC_WD0_TBL_ADDR_SHIFT;
            CSL_FINS(desc0, A15_MMU_LONG_DESC_WD0_TBL_ADDR, phyAddr0);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_ADDR, phyAddr1);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_PXN, (Uint32)(attrs->pxnTable));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_XN, (Uint32)(attrs->xnTable));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_AP, (Uint32)(attrs->apTable));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_NS, (Uint32)(attrs->nsTable));
            break;

        /* Section descriptor */
        case CSL_A15_MMU_LONG_DESC_TYPE_BLOCK:
            desc0 = (Uint32)CSL_A15_MMU_LONG_DESC_TYPE_BLOCK;
            phyAddr0 = (Uint32)phyAddr >> CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_ADDR_SHIFT;
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL1_WD0_BLK_ATTR_IDX, (Uint32)(attrs->attrIndx));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL1_WD0_BLK_NS, (Uint32)(attrs->nonSecure));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL1_WD0_BLK_AP, (Uint32)(attrs->accPerm));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL1_WD0_BLK_SH, (Uint32)(attrs->shareable));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL1_WD0_BLK_AF, (Uint32)(attrs->accessFlag));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL1_WD0_BLK_NG, (Uint32)(attrs->notGlobal));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL1_WD0_BLK_ADDR, phyAddr0);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_LVL1_WD1_BLK_ADDR, phyAddr1);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_LVL1_WD1_BLK_CONTG, (Uint32)(attrs->contiguous));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_LVL1_WD1_BLK_PXN, (Uint32)(attrs->privNoExecute));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_LVL1_WD1_BLK_XN, (Uint32)(attrs->noExecute));
            break;

        default:
            break;
    }

    /* set the entry in the first level descriptor table */
    obj->firstLvlTableBuf[index] = desc0;
    obj->firstLvlTableBuf[index + 1U] = desc1;
}

/** ============================================================================
 *   @n@b CSL_a15SetMmuSecondLevelLongDesc
 *
 *   @b Description
 *   @n This API sets the Long descriptor entry of second level.
 *
 *   @b Arguments
      @verbatim
          virtualAddr   The virtual address.
          attrs         Attribute to be set for long descriptor entry of second level.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15SetMmuSecondLevelLongDesc(virtualAddr, &attrs);

     @endverbatim
 * =============================================================================
 */
void CSL_a15SetMmuSecondLevelLongDesc
(
    CSL_A15MmuLongDescObj *obj,
    const void *virtualAddr,
    const void *phyAddr,
    const CSL_A15MmuLongDescAttr *attrs
)
{
    Uint32 desc0 = 0;
    Uint32 desc1 = 0;
    Uint32 index = (Uint32)virtualAddr >> CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_ADDR_SHIFT;
    Uint32 phyAddr0 = 0U;
    Uint32 phyAddr1 = 0U;

    /* Determine which kind of descriptor. */
    switch (attrs->type) {
        case CSL_A15_MMU_LONG_DESC_TYPE_TABLE:
            /* Page table descriptor */
            desc0 = (Uint32)CSL_A15_MMU_LONG_DESC_TYPE_TABLE;
            phyAddr0 = (Uint32)phyAddr >> CSL_A15_MMU_LONG_DESC_WD0_TBL_ADDR_SHIFT;
            CSL_FINS(desc0, A15_MMU_LONG_DESC_WD0_TBL_ADDR, phyAddr0);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_ADDR, phyAddr1);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_PXN, (Uint32)(attrs->pxnTable));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_XN, (Uint32)(attrs->xnTable));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_AP, (Uint32)(attrs->apTable));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_WD1_TBL_NS, (Uint32)(attrs->nsTable));
            break;

            /* Section descriptor */
        case CSL_A15_MMU_LONG_DESC_TYPE_BLOCK:
            desc0 = (Uint32)CSL_A15_MMU_LONG_DESC_TYPE_BLOCK;
            phyAddr0 = (Uint32)phyAddr >> CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_ADDR_SHIFT;
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL2_WD0_BLK_MEM_ATTR, (Uint32)(attrs->attrIndx));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL2_WD0_BLK_NS, (Uint32)(attrs->nonSecure));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL2_WD0_BLK_AP, (Uint32)(attrs->accPerm));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL2_WD0_BLK_SH, (Uint32)(attrs->shareable));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL2_WD0_BLK_AF, (Uint32)(attrs->accessFlag));
            CSL_FINS(desc0, A15_MMU_LONG_DESC_LVL2_WD0_BLK_ADDR, phyAddr0);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_LVL2_WD1_BLK_ADDR, phyAddr1);
            CSL_FINS(desc1, A15_MMU_LONG_DESC_LVL2_WD1_BLK_CONTG, (Uint32)(attrs->contiguous));
            CSL_FINS(desc1, A15_MMU_LONG_DESC_LVL2_WD1_BLK_XN, (Uint32)(attrs->noExecute));
            break;

        default:
            break;
    }

    /* set the entry in the first level descriptor table */
    obj->secondLvlTableBuf[index >> 9U][2U * (index & 0x1FFU)] = desc0;
    obj->secondLvlTableBuf[index >> 9U][(2U * (index & 0x1FFU)) + 1U] = desc1;
}

/** ============================================================================
 *   @n@b CSL_a15InitMmuLongDescAttrs
 *
 *   @b Description
 *   @n This API sets the init configuration of long descriptor entry.
 *
 *   @b Arguments
      @verbatim
          attrs         Attribute to be set for long descriptor entry.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15InitMmuLongDescAttrs(&attrs);

     @endverbatim
 * =============================================================================
 */
void CSL_a15InitMmuLongDescAttrs(CSL_A15MmuLongDescAttr *attrs)
{
    attrs->type = CSL_A15_MMU_LONG_DESC_TYPE_INVALID0;
    attrs->nsTable = 1U;
    attrs->apTable = 0U;
    attrs->xnTable = 0U;
    attrs->pxnTable = 0U;
    attrs->noExecute = 0U;
    attrs->privNoExecute = 0U;
    attrs->contiguous = 0U;
    attrs->notGlobal = 0U;
    attrs->accessFlag = 1U;
    attrs->shareable = 0U;
    attrs->accPerm = 0U;
    attrs->nonSecure = 1U;
    attrs->attrIndx = 0U;
}

/** ============================================================================
 *   @n@b CSL_a15CommonFiqEnable
 *
 *   @b Description
 *   @n This API initializes the long descriptor buffer.
 *
 *   @b Arguments
      @verbatim
          obj         Object for long descriptor MMU configuration.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        Mmu_initLongDescTableBuf(&obj);

     @endverbatim
 * =============================================================================
 */
void CSL_a15InitMmuLongDesc (CSL_A15MmuLongDescObj *obj)
{
    Uint32 desc[2];
    Uint32 i = 0U;
    Uint32 j = 0U;
    Uint32 tableBuf = (Uint32) &(obj->firstLvlTableBuf[0]);
    CSL_A15MmuLongDescAttr attrs;

    CSL_a15InitMmuLongDescAttrs(&attrs);
    attrs.type = CSL_A15_MMU_LONG_DESC_TYPE_TABLE;
    CSL_a15SetMmuFirstLevelLongDesc(obj, (void *)0U, (void *)0U, &attrs);

    for (i = 0; i < obj->numFirstLvlEntires; i++)
    {
        desc[0] = obj->firstLvlTableBuf[0U];
        desc[0] = (desc[0] & 0xFFFU) |
            (((Uint32) &(obj->secondLvlTableBuf[i][0])) & 0xFFFFF000U);
        desc[1] = (obj->firstLvlTableBuf[1U] & 0xFFF00000U);
        obj->firstLvlTableBuf[i * 2U] = desc[0];
        obj->firstLvlTableBuf[(i * 2U) + 1U] = desc[1];
    }

    CSL_a15InitMmuLongDescAttrs(&attrs);
    CSL_a15SetMmuSecondLevelLongDesc(obj, (void *)0U, (void *)0U, &attrs);

    for (i = 0; i < obj->numFirstLvlEntires; i++)
    {
        for (j = 0; j < obj->numSecondLvlEntires; j++)
        {
            obj->secondLvlTableBuf[i][j * 2U] = obj->secondLvlTableBuf[0U][0U];
            obj->secondLvlTableBuf[i][(j * 2U) + 1U] = obj->secondLvlTableBuf[0U][1U];
        }
    }

#if 0
    asm("mov  r1, #1                 \n\t" /*TTBR0 used and desc uses Short format*/
        "lsl  r1, r1, #31            \n\t" /*Set TTBCR.EAE bit                */
        "mcr  p15, #0, r1, c2, c0, #2\n\t" /*write r0 to TTBCR                */
        "isb                         \n\t" /*flush instruction pipeline       */
        "                            \n\t" /*isb makes sure cp15 changes      */
        "                            \n\t" /*are visible to all subsequent    */
        "                            \n\t"); /*instructions                     */
#else
    CSL_a15EnableMmuLongDescTranslationTable();
#endif

    for (i = 0U; i < obj->mairEntires; i++)
    {
        CSL_a15SetMmuMair(i, obj->mairAttr[i]);
    }

#if 0
    asm("mov  r1, #0                 \n\t"
        "mcr  p15, #0, r1, c8, c7, #0\n\t" /*invalidate unified TLB           */
        "mcr  p15, #0, r1, c8, c6, #0\n\t" /*invalidate data TLB              */
        "mcr  p15, #0, r1, c8, c5, #0\n\t" /*invalidate instruction TLB       */
        "dsb                         \n\t" /*wait for invalidation to complete*/
        "isb                         \n\t" /*flush instruction pipeline       */
        "                            \n\t"
        "mov  r2, %[input]           \n\t" /*get page table pointer           */
        "mov  r1, #0                \n\t"   /*get page table address          */
        "mcrr p15, #0, r2, r1, c2   \n\t"
                :
                : [input] "r" (tableBuf));  /*get page table pointer          */
#else
    CSL_a15InvalidateAllMmuTranslationTable();
    CSL_a15SetMmuLongDescTranslationTable(tableBuf);
#endif
}

/** ============================================================================
 *   @n@b CSL_a15DisableCache
 *
 *   @b Description
 *   @n This function is used to disable the cache.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15DisableCache(); // Disable the cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15DisableCache (void)
{
    CSL_a15DisableInstrCache();
    CSL_a15DisableDataCache();
}

/** ============================================================================
 *   @n@b CSL_a15EnableCache
 *
 *   @b Description
 *   @n This function is used to enable the instruction cache.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15EnableCache(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableCache (void)
{
    CSL_a15EnableInstrCache();
    CSL_a15EnableDataCache();
}

/** ============================================================================
 *   @n@b CSL_a15InvCache
 *
 *   @b Description
 *   @n This function is used to invalidate the instruction cache pointed by the block
 *      address. Although the block size can be specified in the number of bytes,
 *      the cache controller operates on whole cache lines. To prevent unintended
 *      behavior "blockPtr" should be aligned on the cache line size and "byteCnt"
 *      should be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be invalidated
          byteCnt       Size of the block to be invalidated.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        // Invalidate the 128 bytes of the function 'foo'
        CSL_a15InvCache((void *)&foo, 128);

     @endverbatim
 * =============================================================================
 */
void CSL_a15InvCache
(
    void*       blockPtr,
    Uint32      byteCnt
)
{
    CSL_a15InvInstrCache(blockPtr, byteCnt);
    CSL_a15InvDataCache(blockPtr, byteCnt);
}

/** ============================================================================
 *   @n@b CSL_a15InvAllCache
 *
 *   @b Description
 *   @n This function is used to invalidate the entire instruction cache
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15InvAllCache();

     @endverbatim
 * =============================================================================
 */
void CSL_a15InvAllCache (void)
{
    CSL_a15InvAllInstrCache();
    CSL_a15InvAllDataCache();
}

/* nothing past this point */
