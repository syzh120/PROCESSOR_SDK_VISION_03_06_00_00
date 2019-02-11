/**
 *   @file  a15.h
 *
 *   @brief
 *      This is the A15 Auxilary Header File which exposes the various
 *      CSL Functional Layer API's to configure the A15 Module.
 *
 *  \par
 *  ============================================================================
 *  @n   (C) Copyright 2002 - 2017 Texas Instruments, Inc.
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

/** @defgroup CSL_A15_V0_API A15_V0
 *
 */

#ifndef CSL_A15_V0_H
#define CSL_A15_V0_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/csl/csl.h>

/**
@defgroup CSL_A15_V0_SYMBOL  A15_V0 Symbols Defined
@ingroup CSL_A15_V0_API
*/
/**
@defgroup CSL_A15_V0_ENUM  A15_V0 Enumerated Data Types
@ingroup CSL_A15_V0_API
*/
/**
@defgroup CSL_A15_V0_FUNCTION  A15_V0 Functions
@ingroup CSL_A15_V0_API
*/


/**
@addtogroup CSL_A15_V0_SYMBOL
@{
*/

/******************************************************************************\
* global macro declarations
\******************************************************************************/

#define CSL_A15_MMU_SHORT_DESC_LVL1_ENTIRES                 (((uint32_t)4U) * ((uint32_t)1024U))

#define CSL_A15_MMU_LONG_DESC_LVL1_ENTIRES                  ((uint32_t)(4U))
#define CSL_A15_MMU_LONG_DESC_LVL2_ENTIRES                  ((uint32_t)(512U))
#define CSL_A15_MMU_MAIR_LEN_BYTES                          ((uint32_t)(8U))

/** @brief Default hardware setup parameters */
#define CSL_A15_MMU_SHORT_DESC_LVL1_SECTION_ADDR_MASK       ((uint32_t)(0xFFF00000U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_SECTION_ADDR_SHIFT      ((uint32_t)(20U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_NON_SECURE_MASK         ((uint32_t)(0x00080000U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_NON_SECURE_SHIFT        ((uint32_t)(19U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_SHARABLE_MASK           ((uint32_t)(0x00010000U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_SHARABLE_SHIFT          ((uint32_t)(16U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_TEX_MASK                ((uint32_t)(0x00007000U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_TEX_SHIFT               ((uint32_t)(12U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_AP_MASK                 ((uint32_t)(0x00008C00U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_AP_SHIFT                ((uint32_t)(10U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_IMPL_MASK               ((uint32_t)(0x00000200U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_IMPL_SHIFT              ((uint32_t)(9U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_DOMAIN_MASK             ((uint32_t)(0x000001E0U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_DOMAIN_SHIFT            ((uint32_t)(5U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_XN_MASK                 ((uint32_t)(0x00000010U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_XN_SHIFT                ((uint32_t)(4U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_C_MASK                  ((uint32_t)(0x00000008U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_C_SHIFT                 ((uint32_t)(3U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_B_MASK                  ((uint32_t)(0x00000004U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_B_SHIFT                 ((uint32_t)(2U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_TYPE_MASK               ((uint32_t)(0x00000003U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_TYPE_SHIFT              ((uint32_t)(0U))

/** @brief Default hardware setup parameters */
#define CSL_A15_MMU_SHORT_DESC_LVL1_TABLE_ADDR_MASK         ((uint32_t)(0xFFFFF000U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_TABLE_ADDR_SHIFT        ((uint32_t)(12U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_IMPL_MASK               ((uint32_t)(0x00000200U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_IMPL_SHIFT              ((uint32_t)(9U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_DOMAIN_MASK             ((uint32_t)(0x000001E0U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_DOMAIN_SHIFT            ((uint32_t)(5U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_TYPE_MASK               ((uint32_t)(0x00000003U))
#define CSL_A15_MMU_SHORT_DESC_LVL1_TYPE_SHIFT              ((uint32_t)(0U))

/** @brief Default hardware setup parameters */
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_XN_MASK          ((uint32_t)(0x00800000U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_XN_SHIFT         ((uint32_t)(22U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_PXN_MASK         ((uint32_t)(0x00400000U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_PXN_SHIFT        ((uint32_t)(21U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_CONTG_MASK       ((uint32_t)(0x00200000U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_CONTG_SHIFT      ((uint32_t)(20U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_ADDR_MASK        ((uint32_t)(0x000000FFU))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD1_BLK_ADDR_SHIFT       ((uint32_t)(0U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_ADDR_MASK        ((uint32_t)(0xC0000000U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_ADDR_SHIFT       ((uint32_t)(30U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_NG_MASK          ((uint32_t)(0x00000800U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_NG_SHIFT         ((uint32_t)(11U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_AF_MASK          ((uint32_t)(0x00000400U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_AF_SHIFT         ((uint32_t)(10U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_SH_MASK          ((uint32_t)(0x00000300U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_SH_SHIFT         ((uint32_t)(8U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_AP_MASK          ((uint32_t)(0x000000C0U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_AP_SHIFT         ((uint32_t)(6U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_NS_MASK          ((uint32_t)(0x00000020U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_NS_SHIFT         ((uint32_t)(5U))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_ATTR_IDX_MASK    ((uint32_t)(0x0000001CU))
#define CSL_A15_MMU_LONG_DESC_LVL1_WD0_BLK_ATTR_IDX_SHIFT   ((uint32_t)(2U))

/** @brief Default hardware setup parameters */
#define CSL_A15_MMU_LONG_DESC_LVL2_WD1_BLK_XN_MASK          ((uint32_t)(0x00800000U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD1_BLK_XN_SHIFT         ((uint32_t)(22U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD1_BLK_CONTG_MASK       ((uint32_t)(0x00200000U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD1_BLK_CONTG_SHIFT      ((uint32_t)(20U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD1_BLK_ADDR_MASK        ((uint32_t)(0x000000FFU))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD1_BLK_ADDR_SHIFT       ((uint32_t)(0U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_ADDR_MASK        ((uint32_t)(0xFFE00000U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_ADDR_SHIFT       ((uint32_t)(21U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_AF_MASK          ((uint32_t)(0x00000400U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_AF_SHIFT         ((uint32_t)(10U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_SH_MASK          ((uint32_t)(0x00000300U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_SH_SHIFT         ((uint32_t)(8U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_AP_MASK          ((uint32_t)(0x000000C0U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_AP_SHIFT         ((uint32_t)(6U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_NS_MASK          ((uint32_t)(0x00000020U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_NS_SHIFT         ((uint32_t)(5U))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_MEM_ATTR_MASK    ((uint32_t)(0x0000003CU))
#define CSL_A15_MMU_LONG_DESC_LVL2_WD0_BLK_MEM_ATTR_SHIFT   ((uint32_t)(2U))

/** @brief Default hardware setup parameters */
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_NS_MASK               ((uint32_t)(0x80000000U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_NS_SHIFT              ((uint32_t)(31U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_AP_MASK               ((uint32_t)(0x60000000U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_AP_SHIFT              ((uint32_t)(29U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_XN_MASK               ((uint32_t)(0x10000000U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_XN_SHIFT              ((uint32_t)(28U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_PXN_MASK              ((uint32_t)(0x08000000U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_PXN_SHIFT             ((uint32_t)(27U))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_ADDR_MASK             ((uint32_t)(0x000000FFU))
#define CSL_A15_MMU_LONG_DESC_WD1_TBL_ADDR_SHIFT            ((uint32_t)(0U))
#define CSL_A15_MMU_LONG_DESC_WD0_TBL_ADDR_MASK             ((uint32_t)(0xFFFFF000U))
#define CSL_A15_MMU_LONG_DESC_WD0_TBL_ADDR_SHIFT            ((uint32_t)(12U))

/** @brief Cache feature macros. */
#define CSL_A15_CACHE_TYPE_L1P                              (0x1)
#define CSL_A15_CACHE_TYPE_L1D                              (0x2)
#define CSL_A15_CACHE_TYPE_L1                               (0x3)
#define CSL_A15_CACHE_TYPE_L2P                              (0x4)
#define CSL_A15_CACHE_TYPE_L2D                              (0x8)
#define CSL_A15_CACHE_TYPE_L2                               (0xC)
#define CSL_A15_CACHE_TYPE_ALLP                             (0x5)
#define CSL_A15_CACHE_TYPE_ALLD                             (0xA)
#define CSL_A15_CACHE_TYPE_ALL                              (0x7fff)

/**
@}
*/

/**
@addtogroup CSL_A15_V0_ENUM
@{
*/

/**
 * General purpose global type def declarations
 */

/**
 *  @brief This enum describes the commands used to control the GP timer through
 *  CSL_tmrHwControl()
 */
typedef enum {
    /**
     * @brief	Loads the watchdog key
     * @param	Uint16
     */
    CSL_A15_MMU_SHORT_DESC_TYPE_INVALID0 = 0U,

    /**
     * @brief   Loads the GP Timer Reload Register Low
     * @param   Uint32 *
     */
    CSL_A15_MMU_SHORT_DESC_TYPE_PAGE_TABLE = 1U,
    /**
     * @brief	Loads the watchdog key
     * @param	Uint16
     */
    CSL_A15_MMU_SHORT_DESC_TYPE_SECTION = 2U,

    /**
     * @brief   Loads the GP Timer Reload Register High
     * @param   Uint32 *
     */
    CSL_A15_MMU_SHORT_DESC_TYPE_INVALID1 = 3U
} CSL_A15MmuShortDescType;

/**
 *  @brief This enum describes the commands used to control the GP timer through
 *  CSL_tmrHwControl()
 */
typedef enum {
    /**
     * @brief	Loads the watchdog key
     * @param	Uint16
     */
    CSL_A15_MMU_LONG_DESC_TYPE_INVALID0 = 0U,

    /**
     * @brief   Loads the GP Timer Reload Register Low
     * @param   Uint32 *
     */
    CSL_A15_MMU_LONG_DESC_TYPE_BLOCK = 1U,
    /**
     * @brief	Loads the watchdog key
     * @param	Uint16
     */
    CSL_A15_MMU_LONG_DESC_TYPE_INVALID1 = 2U,

    /**
     * @brief   Loads the GP Timer Reload Register High
     * @param   Uint32 *
     */
    CSL_A15_MMU_LONG_DESC_TYPE_TABLE = 3U
} CSL_A15MmuLongDescType;

/**
@}
*/

/** @addtogroup CSL_A15_V0_DATASTRUCT
 @{ */

/**
 * @brief Hardware setup structure.
 */
typedef struct {
    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 firstLvlTableBuf[CSL_A15_MMU_SHORT_DESC_LVL1_ENTIRES];

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 numFirstLvlEntires;
} CSL_A15MmuShortDescObj;

/**
 * @brief Hardware setup structure.
 */
typedef struct {
    /** 32 bit load value to be loaded to Timer Period Register low */
    CSL_A15MmuShortDescType type;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 phyAddr;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 bufferable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 cacheable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 shareable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 noexecute;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 imp;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 domain;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 accPerm;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 tex;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 nonSecure;
} CSL_A15MmuShortDescAttr;

/**
 * @brief Hardware setup structure.
 */
typedef struct {
    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 secondLvlTableBuf[CSL_A15_MMU_LONG_DESC_LVL1_ENTIRES][CSL_A15_MMU_LONG_DESC_LVL2_ENTIRES * 2U];

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 firstLvlTableBuf[CSL_A15_MMU_LONG_DESC_LVL1_ENTIRES * 2U];

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 mairAttr[CSL_A15_MMU_MAIR_LEN_BYTES];

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 numFirstLvlEntires;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 numSecondLvlEntires;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 mairEntires;
} CSL_A15MmuLongDescObj;

/**
 * @brief Hardware setup structure.
 */
typedef struct {
    /** 32 bit load value to be loaded to Timer Period Register low */
    CSL_A15MmuLongDescType type;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint32 phyAddr[2];

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 pxnTable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 xnTable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 apTable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 nsTable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 noExecute;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 privNoExecute;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 contiguous;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 notGlobal;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 accessFlag;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 shareable;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 accPerm;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 nonSecure;

    /** 32 bit load value to be loaded to Timer Period Register low */
    Uint8 attrIndx;
} CSL_A15MmuLongDescAttr;

/**
@}
*/

/** @addtogroup CSL_A15_V0_FUNCTION
 @{ */

/** ============================================================================
 *   @n@b CSL_a15SwitchToPrivMode
 *
 *   @b Description
 *   @n This function is used to initialize MMU registers.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15SwitchToPrivMode();

     @endverbatim
 * =============================================================================
 */
void CSL_a15SwitchToPrivMode(void);

/** ============================================================================
 *   @n@b CSL_a15SwitchToUserMode
 *
 *   @b Description
 *   @n This function is used to disable the MMU.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15SwitchToUserMode();

     @endverbatim
 * =============================================================================
 */
void CSL_a15SwitchToUserMode(void);

/** ============================================================================
 *   @n@b CSL_a15IntrStatus
 *
 *   @b Description
 *   @n This function is used to check if MMU is enabled.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15IntrStatus(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
Uint32 CSL_a15IntrStatus(void);

/** ============================================================================
 *   @n@b CSL_a15DisableIrq
 *
 *   @b Description
 *   @n This API disables the ARM core IRQ interrupt.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15DisableIrq();

     @endverbatim
 * =============================================================================
 */
void CSL_a15DisableIrq(void);

/** ============================================================================
 *   @n@b CSL_a15EnableIrq
 *
 *   @b Description
 *   @n This API enables the ARM core IRQ interrupt.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15EnableIrq();

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableIrq(void);

/** ============================================================================
 *   @n@b CSL_a15DisableFiq
 *
 *   @b Description
 *   @n This API disables the ARM core FIQ interrupt.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15DisableFiq();

     @endverbatim
 * =============================================================================
 */
void CSL_a15DisableFiq(void);

/** ============================================================================
 *   @n@b CSL_a15EnableFiq
 *
 *   @b Description
 *   @n This API enables the ARM core FIQ interrupt.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15EnableFiq();

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableFiq(void);

/** ============================================================================
 *   @n@b CSL_a15SetVectorTable
 *
 *   @b Description
 *   @n This API enables the ARM core FIQ interrupt.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15SetVectorTable();

     @endverbatim
 * =============================================================================
 */
void CSL_a15SetVectorTable(Uint32 vecTableBaseaddr);

/** ============================================================================
 *   @n@b CSL_a15DisableMmu
 *
 *   @b Description
 *   @n This function is used to disable the MMU.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  If the data cache is enabled, write back invalidate all of data cache.
 *       If the program cache is enabled, invalidate all of program cache.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15DisableMmu(); // Disable the MMU

     @endverbatim
 * =============================================================================
 */
void CSL_a15DisableMmu (void);

/** ============================================================================
 *   @n@b CSL_a15EnableMmu
 *
 *   @b Description
 *   @n This function is used to enable the MMU.
 *
 *   @b Arguments
      @verbatim
          tablePtr      Address of the page table
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  I=If the program cache is enabled, invalidate all of program cache.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15EnableMmu(); // Enable the MMU

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableMmu (void);

/** ============================================================================
 *   @n@b CSL_a15IsMmuEnabled
 *
 *   @b Description
 *   @n This function is used to check if MMU is enabled.
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

        CSL_a15IsMmuEnabled(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
uint32_t CSL_a15IsMmuEnabled (void);

/** ============================================================================
 *   @n@b CSL_a15EnbaleMmuLongDescTranslationTable
 *
 *   @b Description
 *   @n This function is used to the 40-bit translation system, with the
 *      Long-descriptor translation table format
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

        CSL_a15EnbaleMmuLongDescTranslationTable(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableMmuLongDescTranslationTable (void);

/** ============================================================================
 *   @n@b CSL_a15EnableMmuShortDescTranslationTable
 *
 *   @b Description
 *   @n This function is used to the 32-bit translation system, with the
 *      Short-descriptor translation table format
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

        CSL_a15EnableMmuShortDescTranslationTable(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableMmuShortDescTranslationTable (void);

/** ============================================================================
 *   @n@b CSL_a15SetMmuLongDescTranslationTable
 *
 *   @b Description
 *   @n This API sets translation table for Long-descriptor translation table format.
 *
 *   @b Arguments
      @verbatim
          tableAddr     translation table base address.
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

        CSL_a15SetMmuLongDescTranslationTable(index, attr);

     @endverbatim
 * =============================================================================
 */
void CSL_a15SetMmuLongDescTranslationTable
(
    Uint32      tableAddr
);

/** ============================================================================
 *   @n@b CSL_a15SetMmuShortDescTranslationTable
 *
 *   @b Description
 *   @n This API sets translation table for Short-descriptor translation table format.
 *
 *   @b Arguments
      @verbatim
          tableAddr     translation table base address.
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

        CSL_a15SetMmuShortDescTranslationTable(index, attr);

     @endverbatim
 * =============================================================================
 */
void CSL_a15SetMmuShortDescTranslationTable
(
    Uint32      tableAddr
);

/** ============================================================================
 *   @n@b CSL_a15InvalidateAllMmuTranslationTable
 *
 *   @b Description
 *   @n This function invalidates all translation tables
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

        CSL_a15InvalidateAllMmuTranslationTable(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15InvalidateAllMmuTranslationTable (void);

/** ============================================================================
 *   @n@b CSL_a15SetMmuMair
 *
 *   @b Description
 *   @n This API sets the MAIR attributes.
 *
 *   @b Arguments
      @verbatim
          idx         Index of MAIRn register. 0 for MAIR0 and 1 for MAIR1.
          attr          Attribute to be written into MAIRn.
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

        CSL_a15SetMmuMair(idx, attr);

     @endverbatim
 * =============================================================================
 */
void CSL_a15SetMmuMair
(
    Uint32      idx,
    Uint32      attr
);

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
);

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
void CSL_a15InitMmuShortDescAttrs(CSL_A15MmuShortDescAttr *attrs);

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
void CSL_a15InitMmuShortDesc (CSL_A15MmuShortDescObj *obj);

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
);

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
);

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
void CSL_a15InitMmuLongDescAttrs(CSL_A15MmuLongDescAttr *attrs);

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
void CSL_a15InitMmuLongDesc (CSL_A15MmuLongDescObj *obj);

/** ============================================================================
 *   @n@b CSL_a15DisableDataCache
 *
 *   @b Description
 *   @n This function is used to disable the data cache.
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

        CSL_a15DisableDataCache(); // Disable the L1D cache

        CSL_a15WbInvAllDataCache(); // Push out all of L1D

     @endverbatim
 * =============================================================================
 */
void CSL_a15DisableDataCache (void);

/** ============================================================================
 *   @n@b CSL_a15DisableInstrCache
 *
 *   @b Description
 *   @n This function is used to disable the instruction cache.
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

        CSL_a15DisableInstrCache(); // Disable the L1D cache

        CSL_a15InvAllInstrCache(); // Invalidate all ICache

     @endverbatim
 * =============================================================================
 */
void CSL_a15DisableInstrCache (void);

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
void CSL_a15DisableCache (void);

/** ============================================================================
 *   @n@b CSL_a15EnableDataCache
 *
 *   @b Description
 *   @n This function is used to enable the data cache.
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

        CSL_a15EnableDataCache(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableDataCache (void);

/** ============================================================================
 *   @n@b CSL_a15EnableInstrCache
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

        CSL_a15InvAllInstrCache(); // Invalidate all ICache

        CSL_a15EnableInstrCache(); // Enable the L1D cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15EnableInstrCache (void);

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
void CSL_a15EnableCache (void);

/** ============================================================================
 *   @n@b CSL_a15InvDataCache
 *
 *   @b Description
 *   @n This function is used to invalidate a block in the data cache. Although
 *      the block size can be specified in the number of bytes, the cache
 *      controller operates on whole cache lines. To prevent unintended behavior
 *      "blockPtr" should be aligned on the cache line size and "byteCnt" should
 *      be a multiple of the cache line size.
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

        Uint8* ptr_buffer;

        // Invalidate 128 bytes of the buffer.
        CSL_a15InvDataCache((void *)ptr_buffer, 128);

     @endverbatim
 * =============================================================================
 */
void CSL_a15InvDataCache
(
    void*       blockPtr,
    Uint32      byteCnt
);

/** ============================================================================
 *   @n@b CSL_a15InvInstrCache
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
        CSL_a15InvInstrCache((void *)&foo, 128);

     @endverbatim
 * =============================================================================
 */
void CSL_a15InvInstrCache
(
    void*       blockPtr,
    Uint32      byteCnt
);

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
);

/** ============================================================================
 *   @n@b CSL_a15InvAllDataCache
 *
 *   @b Description
 *   @n This function is used to invalidate the entire data cache.
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

        CSL_a15InvAllDataCache(); // Invalidate the L1D cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15InvAllDataCache (void);

/** ============================================================================
 *   @n@b CSL_a15InvAllInstrCache
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

        CSL_a15InvAllInstrCache();

     @endverbatim
 * =============================================================================
 */
void CSL_a15InvAllInstrCache (void);

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
void CSL_a15InvAllCache (void);

/** ============================================================================
 *   @n@b CSL_a15WbDataCache
 *
 *   @b Description
 *   @n This function is used to writeback the dirty lines of the block address.
 *      Although the block size can be specified in the number of bytes, the cache
 *      controller operates on whole cache lines. To prevent unintended behavior
 *      "blockPtr" should be aligned on the cache line size and "byteCnt" should
 *      be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be written back
          byteCnt       Size of the block to be written back.
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

        Uint8* ptr_buffer;

        // Writeback 128 bytes of the buffer.
        CSL_a15WbDataCache((void *)ptr_buffer, 128);

     @endverbatim
 * =============================================================================
 */
void CSL_a15WbDataCache
(
    void*       blockPtr,
    Uint32      byteCnt
);

/** ============================================================================
 *   @n@b CSL_a15WbInvDataCache
 *
 *   @b Description
 *   @n This function is used to invalidate and writeback the dirty lines
 *      of the block address.  Although the block size can be specified in
 *      the number of bytes, the cache controller operates on whole cache lines.
 *      To prevent unintended behavior "blockPtr" should be aligned on the
 *      cache line size and "byteCnt" should be a multiple of the cache line size.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be invalidated/written back
          byteCnt       Size of the block to be invalidated/written back.
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

        Uint8* ptr_buffer;

        // Writeback/Invalidate 128 bytes of the buffer.
        CSL_a15WbInvDataCache((void *)ptr_buffer, 128);

     @endverbatim
 * =============================================================================
 */
void CSL_a15WbInvDataCache
(
    void*       blockPtr,
    Uint32      byteCnt
);

/** ============================================================================
 *   @n@b CSL_a15WbAllDataCache
 *
 *   @b Description
 *   @n This function is used to writeback the dirty lines of the data cache
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

        CSL_a15WbAllDataCache(); // Writeback the Dirty Lines of the data cache

     @endverbatim
 * =============================================================================
 */
void CSL_a15WbAllDataCache (void);

/** ============================================================================
 *   @n@b CSL_a15WbInvAllDataCache
 *
 *   @b Description
 *   @n This function is used to invalidate and writeback the dirty lines of the
 *      data Cache
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

        CSL_a15WbInvAllDataCache();

     @endverbatim
 * =============================================================================
 */
void  CSL_a15WbInvAllDataCache (void);

/** ============================================================================
 *   @n@b CSL_a15CachePreload
 *
 *   @b Description
 *   @n This function loads a memory block into the L2 cache. The memory block
 *      is loaded into cache one L2 cache line at time. The byteCnt argument
 *      must be less than or equal to an L2 cache size. An assert is generated
 *      if this rule is violated. Except for the normal L1 instruction cache
 *      behavior during code execution, the L1 instruction cache is unaffected
 *      by this API. The L1 data cache will be temporarily polluted by the
 *      contents of the referenced memory block.
 *
 *   @b Arguments
      @verbatim
          blockPtr      Address of the block which is to be loaded
          byteCnt       Size of the block to be loaded
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  Interrupts are disabled for the entire time the memory block is being
 *       loaded into cache. For this reason, use of this API is probably best
 *       at system intialization time (ie: within 'main()').
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        // Load 128 bytes of the memory block.
        CSL_a15CachePreload((void *)blockPtr, 128);

     @endverbatim
 * =============================================================================
 */
void CSL_a15CachePreload
(
    void*       blockPtr,
    Uint32      byteCnt
);

/** ============================================================================
 *   @n@b CSL_a15DisableBranchPrediction
 *
 *   @b Description
 *   @n This API disables the HW branch predictor.
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

        CSL_a15DisableBranchPrediction();

     @endverbatim
 * =============================================================================
 */
void  CSL_a15DisableBranchPrediction (void);

/** ============================================================================
 *   @n@b CSL_a15EnableBranchPrediction
 *
 *   @b Description
 *   @n This API enables the HW branch predictor.
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

        CSL_a15EnableBranchPrediction();

     @endverbatim
 * =============================================================================
 */
void  CSL_a15EnableBranchPrediction (void);

/** ============================================================================
 *   @n@b CSL_a15ReadCoreId
 *
 *   @b Description
 *   @n This API returns the core ID.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
     @verbatim
          coreId Returns the core ID
     @endverbatim
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        coreId = CSL_a15ReadCoreId();

     @endverbatim
 * =============================================================================
 */
uint32_t CSL_a15ReadCoreId(void);

/** ============================================================================
 *   @n@b CSL_a15FPUEnable
 *
 *   @b Description
 *   @n This API enables FPU
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

        CSL_a15FPUEnable();

     @endverbatim
 * =============================================================================
 */
void CSL_a15FPUEnable(void);

/** ============================================================================
 *   @n@b CSL_a15VectorBaseAddrSet
 *
 *   @b Description
 *   @n This API Set the exception table base address
 *
 *   @b Arguments
 *   @verbatim
 *      addr The base address of the exception vector table
 *   @endverbatim
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

        CSL_a15VectorBaseAddrSet(addr);

     @endverbatim
 * =============================================================================
 */
void CSL_a15VectorBaseAddrSet(uint32_t addr);

/** ============================================================================
 *   @n@b CSL_a15CycleCntEnable
 *
 *   @b Description
 *   @n This API enables the A15's Cycle Count Register after resetting it.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15CycleCntEnable();

     @endverbatim
 * =============================================================================
 */
void CSL_a15CycleCntEnable(void);

/** ============================================================================
 *   @n@b CSL_a15CycleCntRead
 *
 *   @b Description
 *   @n This API reads the A15's Cycle Count Register(CCNT). CCNT Read returns
 *      clock value divided by 64 cycles. To get the actual CPU cycle multiply
 *      it with 64.
 *
 *   @b Arguments
     @verbatim
        None
     @endverbatim
 *
 *   <b> Return Value </b>
     @verbatim
          ccntVal Returns the Counter Value
     @endverbatim
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        ccntVal = CSL_a15CycleCntRead();

     @endverbatim
 * =============================================================================
 */
void CSL_a15CycleCntRead(void);

/** ============================================================================
 *   @n@b CSL_a15ECCEnable
 *
 *   @b Description
 *   @n This function enables the A15 ECC.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15ECCEnable();

     @endverbatim
 * =============================================================================
 */
void CSL_a15ECCEnable(void);


/** ============================================================================
 *   @n@b CSL_a15ECCDisable
 *
 *   @b Description
 *   @n This function disables the A15 ECC.
 *
 *   @b Arguments
     @verbatim
        None
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

        CSL_a15ECCDisable();

     @endverbatim
 * =============================================================================
 */
void CSL_a15ECCDisable(void);

/** ============================================================================
 *   @n@b CSL_a15ECCGetErrStatus
 *
 *   @b Description
 *   @n This function will return A15 L2 ECC 2 bit Error status
 *
 *   @b Arguments
     @verbatim
        None
     @endverbatim
 *
 *   <b> Return Value </b>
     @verbatim
          errStatus Returns the error status
     @endverbatim
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15ECCGetErrStatus();

     @endverbatim
 * =============================================================================
 */
uint32_t CSL_a15ECCGetErrStatus(void);

/**
@}
*/

/** ============================================================================
 *   @n@b CSL_a15GetCacheType
 *
 *   @b Description
 *   @n This function will check if Cache is Enabled and return the type of
 *      cache currently enabled.
 *
 *   @b Arguments
     @verbatim
        None
     @endverbatim
 *
 *   <b> Return Value </b>
     @verbatim
          cacheType  Cache type presently enabled.
     @endverbatim
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Example
 *   @verbatim

        CSL_a15GetCacheType();

     @endverbatim
 * =============================================================================
 */
uint32_t CSL_a15GetCacheType(void);

/** ============================================================================
*   @n@b CSL_armGicGlobalDisableInterrupt
*
*   @b Description
*   @n This API disables the interrupt globally.
*
*   @b Arguments
     @verbatim
*       None
     @endverbatim
*
*   <b> Return Value </b>
*   @n  CPSR value before disable interrupt
*
*   <b> Pre Condition </b>
*   @n  None
*
*   <b> Post Condition </b>
*   @n  None
*
*   @b Example
*   @verbatim

       uint32_t   key;
      key     = CSL_armGicGlobalDisableInterrupt();

     @endverbatim
* =============================================================================
*/
extern uint32_t  CSL_armGicGlobalDisableInterrupt(void);

/** ============================================================================
*   @n@b CSL_armGicGlobalRestoreInterrupt
*
*   @b Description
*   @n This API restores the interrupt globally.
*
*   @b Arguments
     @verbatim
*       None
     @endverbatim
*
*   <b> Return Value </b>
*   @n  CPSR value to be restored
*
*   <b> Pre Condition </b>
*   @n  Call the CSL_armGicGlobalDisableInterrupt() to get the key
*
*   <b> Post Condition </b>
*   @n  None
*
*   @b Example
*   @verbatim

      uint32_t   key;
      key     = CSL_armGicGlobalDisableInterrupt();
      ...
      ...
      ...
      CSL_armGicGlobalRestoreInterrupt(key);

     @endverbatim
* =============================================================================
*/
extern void CSL_armGicGlobalRestoreInterrupt (uint32_t restoreValue);

#ifdef __cplusplus
}
#endif

#endif /*CSL_A15_V0_H*/
