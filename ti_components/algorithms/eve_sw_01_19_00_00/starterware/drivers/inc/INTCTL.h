/*
*
* Copyright (c) 2003-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/*------------------------------------------------------------------------*//** ============================================================================
 *
 *            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION
 *
 *   Property of Texas Instruments
 *   For Unrestricted Internal Use Only
 *   Unauthorized reproduction and/or distribution is strictly prohibited.
 *   This product is protected under copyright law and trade secret law as an unpublished work.
 *   Created 2003, (C) Copyright 2003 Texas Instruments.  All rights reserved.
 */
/*
 *   @Component    INTCTL
 *
 *   @Filename     INTCTL.h
 *
 *   @Description  INTCTL library function configures the MPU interrupt handler
 *                 with basic functions like routing (to fiq or irq) ,enabling ,
 *                 prioritizing, masking each interrupt.
 *
 *
 *   Available Functions:
 *                 EVE_INTCTL_LevelInit       - Configure the priority and Interrupt kind
 *                                          for each input interrupt number
 *                 EVE_INTCTL_OneITEnable     - Enable the speciifed interrupt
 *                 EVE_INTCTL_AllITEnable     - Enable all the interrupt
 *                 EVE_INTCTL_Ack             - Read the interrupt status register
 *                 EVE_INTCTL_NextValid       - Enable for the next valid interrupt
 *                 EVE_INTCTL_GlobalMask      - Enable or disable the global mask
 *                 EVE_INTCTL_ISRSetNClear    - Set or clear the specified S/W interrupt
 *                 EVE_INTCTL_ISRSetNClearAll - Set or clear all the S/W interrupt
 *                 EVE_INTCTL_AutoGating      - Enable or Disable autogating for ocp or
 *                                          functional clock
 *                 EVE_INTCTL_Protection      - Enable or Disable protection of other registers
 *                 EVE_INTCTL_SwReset         - Reset the INTC module.(S/W reset)
 *                 EVE_INTCTL_TurboBit        - Enable/Disable input sync autogating.
 *
 *//*======================================================================== */
/**
*  @file       INTCTL.h
*
*  @brief      INTCTL library function configures the MPU interrupt handler
*              with basic functions like routing (to fiq or irq) ,enabling ,
*              prioritizing, masking each interrupt.
*
*  This header provides a generic APIs interrupt controller for EVE
*
*/
#ifndef INTCTL_H
#define INTCTL_H

/* ============================================================================
 * EXPORTED TYPES
 * ============================================================================
 */

/*------------------------------------------------------------------------*//**
 * @brief          INTCTL_InterruptKind_t
 *
 * @brief         kind of interrupt: either FIQ/IRQ
 *
 * @details       Identify the kind of interrupt: either FIQ/IRQ
 *
 *//*----------------------------------------------------------------------- */
typedef  enum INTCTL_InterruptKind_label{
    INTCTL_IRQ = 0,                                       /**< IRQ */
    INTCTL_FIQ = 1                                        /**< FIQ */
} INTCTL_InterruptKind_t,*pINTCTL_InterruptKind_t;        /**< INTCTL_InterruptKind_t,*pINTCTL_InterruptKind_t */


/*------------------------------------------------------------------------*//**
 * @brief          INTCTL_Priority_t
 *
 * @brief         Priority level
 *
 * @details       Priority level of the interrupt. 0=highest priority ,as the
 *                level increases priority decreases.
 *
 *//*----------------------------------------------------------------------- */

typedef enum INTCTL_InterruptPriority
{
  INTCTL_NMI = 1,                                  /**< interrupt priority NMI */
  INTCTL_INT4 = 2,                                     /**< interrupt priority INT4   */
  INTCTL_INT5 = 3,                                     /**< interrupt priority INT5   */
  INTCTL_INT6 = 4,                                     /**< interrupt priority INT6   */
  INTCTL_INT7 = 5,                                     /**< interrupt priority INT7   */
  INTCTL_INT8 = 6,                                     /**< interrupt priority INT8   */
  INTCTL_INT9 = 7,                                     /**< interrupt priority INT9   */
  INTCTL_INT10 = 8,                                    /**< interrupt priority INT10  */
  INTCTL_INT11 = 9,                                    /**< interrupt priority INT11  */
  INTCTL_INT12 = 10,                                    /**< interrupt priority INT12  */
  INTCTL_INT13 = 11,                                    /**< interrupt priority INT13  */
  INTCTL_INT14 = 12,                                    /**< interrupt priority INT14  */
  INTCTL_INT15 = 13,                                    /**< interrupt priority INT15  */
  INTCTL_INT_MAX = INTCTL_INT15                    /**< maximum interrupt priority */
} INTCTL_Priority_t;


/*------------------------------------------------------------------------*//**
 * @brief          INTCTL_Enable_t
 *
 * @brief         Enable or disable
 *
 * @details       Enumerated Type used to specify either enable or disable the interrupt
 *
 *//*----------------------------------------------------------------------- */
typedef  enum INTCTL_Enable_label{
    INTCTL_DISABLE = 0,                       /**< interrupt disable */
    INTCTL_ENABLE  = 1                        /**< interrupt enable */
} INTCTL_Enable_t,*pINTCTL_Enable_t;          /**< INTCTL_Enable_t,*pINTCTL_Enable_t */


/*------------------------------------------------------------------------*//**
 * @brief          INTCTL_SetNClear_t
 *
 * @brief         Set or Clear
 *
 * @details       Enumerated Type used to specify either Set or Clear the interrupt
 *
 *//*----------------------------------------------------------------------- */
typedef  enum INTCTL_SetNClear_label{
    INTCTL_CLEAR = 0,                            /**< set interrupt */
    INTCTL_SET   = 1                             /**< clear interrupt */
} INTCTL_SetNClear_t,*pINTCTL_SetNClear_t;       /**< INTCTL_SetNClear_t,*pINTCTL_SetNClear_t */


/*------------------------------------------------------------------------*//**
 * @brief          INTCTL_funcNocp_clk_t
 *
 * @brief         OCP or Functional clock
 *
 * @details       Enumerated Type used to specify either functional clock or OCP clock
 *
 *//*----------------------------------------------------------------------- */
typedef  enum INTCTL_funcNocp_clk_label{
    INTCTL_OCPCLK  = 0,                               /**< OCP clock */
    INTCTL_FUNCCLK = 1                                /**< functional clock */
} INTCTL_funcNocp_clk_t,*pINTCTL_funcNocp_clk_t;      /**< INTCTL_funcNocp_clk_t,*pINTCTL_funcNocp_clk_t */


/* ============================================================================
 * EXPORTED FUNCTIONS
 * ============================================================================
 */

/*------------------------------------------------------------------------*//**
 * @brief           EVE_INTCTL_LevelInit
 *
 * @brief        Set priority level of interrupt
 *
 * @param[in]    baseAddress      Base address of the module
 * @param[in]    itNumber         predefined order number is the IT position
 *                                into the Interrupt Level Register  range 0 .. 95
 * @param[in]    interruptKind    Specifies IRQ or FIQ interrupt needs to be generated
 * @param[in]    priority         Priority level of the interrupt 0=highest priority
 *
 * @return       Returns whether the passed parameter is OK or NOT
 *                    RET_OK                   No errors
 *                    RET_BAD_NULL_PARAM       Bad Parameter passed
 *                    RET_PARAM_OUT_OF_RANGE   Parameter out of range
 *
 * @details      Set priority level and dset type of interrupt (IRQ or FIQ)
 *
 *//*----------------------------------------------------------------------- */

extern ReturnCode_t EVE_INTCTL_LevelInit (const UWORD32                baseAddress,
                                      const UWORD8                 itNumber,
                                      const INTCTL_InterruptKind_t interruptKind ,
                                      const INTCTL_Priority_t      priority);


/*------------------------------------------------------------------------*//**
 * @brief           EVE_INTCTL_OneITEnable
 *
 * @brief        Enable or disable interrupt
 *
 * @param[in]    baseAddress      Base address of the module
 * @param[in]    itNumber         The interrupt to process
 * @param[in]    enableNdisable   Enables or Disables the specified interrupt
 *
 * @return       Returns whether the passed parameter is OK or NOT
 *                    RET_OK                   No errors
 *                    RET_BAD_NULL_PARAM       Bad Parameter passed
 *                    RET_PARAM_OUT_OF_RANGE   Parameter out of range
 *
 * @details      Enable or disable the interrupt specified by unmasking
 *               or masking the mask register depending on the parameters passed.
 *
 *//*----------------------------------------------------------------------- */

extern ReturnCode_t EVE_INTCTL_OneITEnable (const UWORD32           baseAddress,
                                        const UWORD8            itNumber,
                                        const INTCTL_Enable_t   enableNdisable);


/*------------------------------------------------------------------------*//**
 * @brief           EVE_INTCTL_Ack
 *
 * @brief        Acknowledge and return number of active interrupt
 *
 * @param[in]    baseAddress      Base address of the module
 * @param[in]    interruptPriority    Priority level of the interrupt 0=highest priority
 * @param[out]   interruptNumber  Number of the active and acknowledged Interrupt
 *
 * @return       Returns whether the passed parameter is OK or NOT
 *                    RET_OK                   No errors
 *                    RET_BAD_NULL_PARAM       Bad Parameter passed
 *
 * @details      Acknowledge the active interrupt and return the origin of the
 *               interrupt by reading the Source IRQ/FIQ register.
 *
 *//*----------------------------------------------------------------------- */

extern ReturnCode_t EVE_INTCTL_Ack (const UWORD32                 baseAddress,
                                const INTCTL_Priority_t       interruptPriority,
                                UWORD16 *const                interruptNumber);


/*------------------------------------------------------------------------*//**
 * @brief           EVE_INTCTL_NextValid
 *
 * @brief        Valid current active interrupt
 *
 * @param[in]    baseAddress      Base address of the module
 * @param[in]    interruptPriority    Priority level of the interrupt 0=highest priority
 *
 * @return       Returns whether the passed parameter is OK or NOT
 *                    RET_OK                   No errors
 *                    RET_BAD_NULL_PARAM       Bad Parameter passed
 *
 * @details      Valid current active interrupt. Effect is clearing of interrupt
 *               in interrupt controller. Thus a new interrupt can be catched.
 *
 *//*----------------------------------------------------------------------- */

extern ReturnCode_t EVE_INTCTL_NextValid (const UWORD32                baseAddress,
                                      const INTCTL_Priority_t      interruptPriority);





#endif  /* INTCTL_H */

