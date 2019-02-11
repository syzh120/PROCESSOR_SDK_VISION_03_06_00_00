/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
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
#ifndef CSLR_MDIO_H
#define CSLR_MDIO_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for user_group
**************************************************************************/
typedef struct {
    volatile Uint32 USER_ACCESS_REG;
    volatile Uint32 USER_PHY_SEL_REG;
} CSL_MdioUser_groupRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile Uint32 VERSION_REG;
    volatile Uint32 CONTROL_REG;
    volatile Uint32 ALIVE_REG;
    volatile Uint32 LINK_REG;
    volatile Uint32 LINK_INT_RAW_REG;
    volatile Uint32 LINK_INT_MASKED_REG;
    volatile Uint8  RSVD0[8];
    volatile Uint32 USER_INT_RAW_REG;
    volatile Uint32 USER_INT_MASKED_REG;
    volatile Uint32 USER_INT_MASK_SET_REG;
    volatile Uint32 USER_INT_MASK_CLEAR_REG;
    volatile Uint8  RSVD1[80];
    CSL_MdioUser_groupRegs	USER_GROUP[2];
} CSL_MdioRegs;




/**************************************************************************
* Register Macros
**************************************************************************/

/* USER_ACCESS_REG */
#define CSL_MDIO_USER_ACCESS_REG(n)                             ((uint32_t)0x80U + ((n) * ((uint32_t)(0x8U))))

/* USER_PHY_SEL_REG */
#define CSL_MDIO_USER_PHY_SEL_REG(n)                            ((uint32_t)0x84U + ((n) * ((uint32_t)(0x8U))))

/* VERSION_REG */
#define CSL_MDIO_VERSION_REG                                    ((uint32_t)(0x0U))

/* CONTROL_REG */
#define CSL_MDIO_CONTROL_REG                                    ((uint32_t)(0x4U))

/* ALIVE_REG */
#define CSL_MDIO_ALIVE_REG                                      ((uint32_t)(0x8U))

/* LINK_REG */
#define CSL_MDIO_LINK_REG                                       ((uint32_t)(0xCU))

/* LINK_INT_RAW_REG */
#define CSL_MDIO_LINK_INT_RAW_REG                               ((uint32_t)(0x10U))

/* LINK_INT_MASKED_REG */
#define CSL_MDIO_LINK_INT_MASKED_REG                            ((uint32_t)(0x14U))

/* USER_INT_RAW_REG */
#define CSL_MDIO_USER_INT_RAW_REG                               ((uint32_t)(0x20U))

/* USER_INT_MASKED_REG */
#define CSL_MDIO_USER_INT_MASKED_REG                            ((uint32_t)(0x24U))

/* USER_INT_MASK_SET_REG */
#define CSL_MDIO_USER_INT_MASK_SET_REG                          ((uint32_t)(0x28U))

/* USER_INT_MASK_CLEAR_REG */
#define CSL_MDIO_USER_INT_MASK_CLEAR_REG                        ((uint32_t)(0x2CU))


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* USER_ACCESS_REG */

#define CSL_MDIO_USER_ACCESS_REG_DATA_MASK                      ((uint32_t)(0x0000FFFFU))
#define CSL_MDIO_USER_ACCESS_REG_DATA_SHIFT                     ((uint32_t)(0U))
#define CSL_MDIO_USER_ACCESS_REG_DATA_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_ACCESS_REG_DATA_MAX                       ((uint32_t)(0x0000ffffU))

#define CSL_MDIO_USER_ACCESS_REG_PHYADR_MASK                    ((uint32_t)(0x001F0000U))
#define CSL_MDIO_USER_ACCESS_REG_PHYADR_SHIFT                   ((uint32_t)(16U))
#define CSL_MDIO_USER_ACCESS_REG_PHYADR_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_ACCESS_REG_PHYADR_MAX                     ((uint32_t)(0x0000001fU))

#define CSL_MDIO_USER_ACCESS_REG_REGADR_MASK                    ((uint32_t)(0x03E00000U))
#define CSL_MDIO_USER_ACCESS_REG_REGADR_SHIFT                   ((uint32_t)(21U))
#define CSL_MDIO_USER_ACCESS_REG_REGADR_RESETVAL                ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_ACCESS_REG_REGADR_MAX                     ((uint32_t)(0x0000001fU))

#define CSL_MDIO_USER_ACCESS_REG_ACK_MASK                       ((uint32_t)(0x20000000U))
#define CSL_MDIO_USER_ACCESS_REG_ACK_SHIFT                      ((uint32_t)(29U))
#define CSL_MDIO_USER_ACCESS_REG_ACK_RESETVAL                   ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_ACCESS_REG_ACK_MAX                        ((uint32_t)(0x00000001U))

#define CSL_MDIO_USER_ACCESS_REG_ACK_PASS                                                    ((uint32_t)(1U))
#define CSL_MDIO_USER_ACCESS_REG_ACK_FAIL                                                    ((uint32_t)(0U))
#define CSL_MDIO_USER_ACCESS_REG_WRITE_MASK                     ((uint32_t)(0x40000000U))
#define CSL_MDIO_USER_ACCESS_REG_WRITE_SHIFT                    ((uint32_t)(30U))
#define CSL_MDIO_USER_ACCESS_REG_WRITE_RESETVAL                 ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_ACCESS_REG_WRITE_MAX                      ((uint32_t)(0x00000001U))

#define CSL_MDIO_USER_ACCESS_REG_READ                   ((uint32_t)(0U))
#define CSL_MDIO_USER_ACCESS_REG_WRITE                                                       ((uint32_t)(1U))
#define CSL_MDIO_USER_ACCESS_REG_GO_MASK                        ((uint32_t)(0x80000000U))
#define CSL_MDIO_USER_ACCESS_REG_GO_SHIFT                       ((uint32_t)(31U))
#define CSL_MDIO_USER_ACCESS_REG_GO_RESETVAL                    ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_ACCESS_REG_GO_MAX                         ((uint32_t)(0x00000001U))
#define CSL_MDIO_USER_ACCESS_REG_GO_EN_0x1                                                   ((uint32_t)(1U))
#define CSL_MDIO_USER_ACCESS_REG_GO_EN_0x0                                                   ((uint32_t)(0U))

#define CSL_MDIO_USER_ACCESS_REG_RESETVAL                       ((uint32_t)(0x00000000U))

/* USER_PHY_SEL_REG */

#define CSL_MDIO_USER_PHY_SEL_REG_PHYADR_MON_MASK               ((uint32_t)(0x0000001FU))
#define CSL_MDIO_USER_PHY_SEL_REG_PHYADR_MON_SHIFT              ((uint32_t)(0U))
#define CSL_MDIO_USER_PHY_SEL_REG_PHYADR_MON_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_PHY_SEL_REG_PHYADR_MON_MAX                ((uint32_t)(0x0000001fU))

#define CSL_MDIO_USER_PHY_SEL_REG_LINKINT_ENABLE_MASK           ((uint32_t)(0x00000040U))
#define CSL_MDIO_USER_PHY_SEL_REG_LINKINT_ENABLE_SHIFT          ((uint32_t)(6U))
#define CSL_MDIO_USER_PHY_SEL_REG_LINKINT_ENABLE_RESETVAL       ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_PHY_SEL_REG_LINKINT_ENABLE_MAX            ((uint32_t)(0x00000001U))

#define CSL_MDIO_USER_PHY_SEL_REG_LINKSEL_MASK                  ((uint32_t)(0x00000080U))
#define CSL_MDIO_USER_PHY_SEL_REG_LINKSEL_SHIFT                 ((uint32_t)(7U))
#define CSL_MDIO_USER_PHY_SEL_REG_LINKSEL_RESETVAL              ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_PHY_SEL_REG_LINKSEL_MAX                   ((uint32_t)(0x00000001U))

#define CSL_MDIO_USER_PHY_SEL_REG_RESETVAL                      ((uint32_t)(0x00000000U))

/* VERSION_REG */

#define CSL_MDIO_VERSION_REG_REVMINOR_MASK                      ((uint32_t)(0x000000FFU))
#define CSL_MDIO_VERSION_REG_REVMINOR_SHIFT                     ((uint32_t)(0U))
#define CSL_MDIO_VERSION_REG_REVMINOR_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_MDIO_VERSION_REG_REVMINOR_MAX                       ((uint32_t)(0x000000ffU))

#define CSL_MDIO_VERSION_REG_REVMAJ_MASK                        ((uint32_t)(0x0000FF00U))
#define CSL_MDIO_VERSION_REG_REVMAJ_SHIFT                       ((uint32_t)(8U))
#define CSL_MDIO_VERSION_REG_REVMAJ_RESETVAL                    ((uint32_t)(0x00000000U))
#define CSL_MDIO_VERSION_REG_REVMAJ_MAX                         ((uint32_t)(0x000000ffU))

#define CSL_MDIO_VERSION_REG_MODID_MASK                         ((uint32_t)(0xFFFF0000U))
#define CSL_MDIO_VERSION_REG_MODID_SHIFT                        ((uint32_t)(16U))
#define CSL_MDIO_VERSION_REG_MODID_RESETVAL                     ((uint32_t)(0x00000000U))
#define CSL_MDIO_VERSION_REG_MODID_MAX                          ((uint32_t)(0x0000ffffU))

#define CSL_MDIO_VERSION_REG_RESETVAL                           ((uint32_t)(0x00000000U))

/* CONTROL_REG */

#define CSL_MDIO_CONTROL_REG_CLKDIV_MASK                        ((uint32_t)(0x0000FFFFU))
#define CSL_MDIO_CONTROL_REG_CLKDIV_SHIFT                       ((uint32_t)(0U))
#define CSL_MDIO_CONTROL_REG_CLKDIV_RESETVAL                    ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_CLKDIV_MAX                         ((uint32_t)(0x0000ffffU))

#define CSL_MDIO_CONTROL_REG_INT_TEST_ENABLE_MASK               ((uint32_t)(0x00020000U))
#define CSL_MDIO_CONTROL_REG_INT_TEST_ENABLE_SHIFT              ((uint32_t)(17U))
#define CSL_MDIO_CONTROL_REG_INT_TEST_ENABLE_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_INT_TEST_ENABLE_MAX                ((uint32_t)(0x00000001U))

#define CSL_MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_MASK           ((uint32_t)(0x00040000U))
#define CSL_MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_SHIFT          ((uint32_t)(18U))
#define CSL_MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_RESETVAL       ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_MAX            ((uint32_t)(0x00000001U))
#define CSL_MDIO_CONTROL_REG_FAULT_DETECT_ENABLE_0X1                            ((uint32_t)(1U))

#define CSL_MDIO_CONTROL_REG_FAULT_MASK                         ((uint32_t)(0x00080000U))
#define CSL_MDIO_CONTROL_REG_FAULT_SHIFT                        ((uint32_t)(19U))
#define CSL_MDIO_CONTROL_REG_FAULT_RESETVAL                     ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_FAULT_MAX                          ((uint32_t)(0x00000001U))

#define CSL_MDIO_CONTROL_REG_PREAMBLE_MASK                      ((uint32_t)(0x00100000U))
#define CSL_MDIO_CONTROL_REG_PREAMBLE_SHIFT                     ((uint32_t)(20U))
#define CSL_MDIO_CONTROL_REG_PREAMBLE_RESETVAL                  ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_PREAMBLE_MAX                       ((uint32_t)(0x00000001U))
#define CSL_MDIO_CONTROL_REG_PREAMBLE_EN_0X1                                                   ((uint32_t)(1U))

#define CSL_MDIO_CONTROL_REG_HIGHEST_USER_CHANNEL_MASK          ((uint32_t)(0x1F000000U))
#define CSL_MDIO_CONTROL_REG_HIGHEST_USER_CHANNEL_SHIFT         ((uint32_t)(24U))
#define CSL_MDIO_CONTROL_REG_HIGHEST_USER_CHANNEL_RESETVAL      ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_HIGHEST_USER_CHANNEL_MAX           ((uint32_t)(0x0000001fU))

#define CSL_MDIO_CONTROL_REG_ENABLE_MASK                        ((uint32_t)(0x40000000U))
#define CSL_MDIO_CONTROL_REG_ENABLE_SHIFT                       ((uint32_t)(30U))
#define CSL_MDIO_CONTROL_REG_ENABLE_RESETVAL                    ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_ENABLE_MAX                         ((uint32_t)(0x00000001U))
#define CSL_MDIO_CONTROL_REG_ENABLE_0X1                          ((uint32_t)(1U))

#define CSL_MDIO_CONTROL_REG_IDLE_MASK                          ((uint32_t)(0x80000000U))
#define CSL_MDIO_CONTROL_REG_IDLE_SHIFT                         ((uint32_t)(31U))
#define CSL_MDIO_CONTROL_REG_IDLE_RESETVAL                      ((uint32_t)(0x00000000U))
#define CSL_MDIO_CONTROL_REG_IDLE_MAX                           ((uint32_t)(0x00000001U))

#define CSL_MDIO_CONTROL_REG_RESETVAL                           ((uint32_t)(0x00000000U))

/* ALIVE_REG */

#define CSL_MDIO_ALIVE_REG_ALIVE_MASK                           ((uint32_t)(0xFFFFFFFFU))
#define CSL_MDIO_ALIVE_REG_ALIVE_SHIFT                          ((uint32_t)(0U))
#define CSL_MDIO_ALIVE_REG_ALIVE_RESETVAL                       ((uint32_t)(0x00000000U))
#define CSL_MDIO_ALIVE_REG_ALIVE_MAX                            ((uint32_t)(0xffffffffU))

#define CSL_MDIO_ALIVE_REG_RESETVAL                             ((uint32_t)(0x00000000U))

/* LINK_REG */

#define CSL_MDIO_LINK_REG_LINK_MASK                             ((uint32_t)(0xFFFFFFFFU))
#define CSL_MDIO_LINK_REG_LINK_SHIFT                            ((uint32_t)(0U))
#define CSL_MDIO_LINK_REG_LINK_RESETVAL                         ((uint32_t)(0x00000000U))
#define CSL_MDIO_LINK_REG_LINK_MAX                              ((uint32_t)(0xffffffffU))

#define CSL_MDIO_LINK_REG_RESETVAL                              ((uint32_t)(0x00000000U))

/* LINK_INT_RAW_REG */

#define CSL_MDIO_LINK_INT_RAW_REG_LINKINTRAW_MASK               ((uint32_t)(0x00000003U))
#define CSL_MDIO_LINK_INT_RAW_REG_LINKINTRAW_SHIFT              ((uint32_t)(0U))
#define CSL_MDIO_LINK_INT_RAW_REG_LINKINTRAW_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_MDIO_LINK_INT_RAW_REG_LINKINTRAW_MAX                ((uint32_t)(0x00000003U))

#define CSL_MDIO_LINK_INT_RAW_REG_RESETVAL                      ((uint32_t)(0x00000000U))

/* LINK_INT_MASKED_REG */

#define CSL_MDIO_LINK_INT_MASKED_REG_LINKINTMASKED_MASK         ((uint32_t)(0x00000003U))
#define CSL_MDIO_LINK_INT_MASKED_REG_LINKINTMASKED_SHIFT        ((uint32_t)(0U))
#define CSL_MDIO_LINK_INT_MASKED_REG_LINKINTMASKED_RESETVAL     ((uint32_t)(0x00000000U))
#define CSL_MDIO_LINK_INT_MASKED_REG_LINKINTMASKED_MAX          ((uint32_t)(0x00000003U))

#define CSL_MDIO_LINK_INT_MASKED_REG_RESETVAL                   ((uint32_t)(0x00000000U))

/* USER_INT_RAW_REG */

#define CSL_MDIO_USER_INT_RAW_REG_USERINTRAW_MASK               ((uint32_t)(0x00000003U))
#define CSL_MDIO_USER_INT_RAW_REG_USERINTRAW_SHIFT              ((uint32_t)(0U))
#define CSL_MDIO_USER_INT_RAW_REG_USERINTRAW_RESETVAL           ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_INT_RAW_REG_USERINTRAW_MAX                ((uint32_t)(0x00000003U))

#define CSL_MDIO_USER_INT_RAW_REG_RESETVAL                      ((uint32_t)(0x00000000U))

/* USER_INT_MASKED_REG */

#define CSL_MDIO_USER_INT_MASKED_REG_USERINTMASKED_MASK         ((uint32_t)(0x00000003U))
#define CSL_MDIO_USER_INT_MASKED_REG_USERINTMASKED_SHIFT        ((uint32_t)(0U))
#define CSL_MDIO_USER_INT_MASKED_REG_USERINTMASKED_RESETVAL     ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_INT_MASKED_REG_USERINTMASKED_MAX          ((uint32_t)(0x00000003U))

#define CSL_MDIO_USER_INT_MASKED_REG_RESETVAL                   ((uint32_t)(0x00000000U))

/* USER_INT_MASK_SET_REG */

#define CSL_MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET_MASK      ((uint32_t)(0x00000003U))
#define CSL_MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET_SHIFT     ((uint32_t)(0U))
#define CSL_MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET_RESETVAL  ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_INT_MASK_SET_REG_USERINTMASKSET_MAX       ((uint32_t)(0x00000003U))

#define CSL_MDIO_USER_INT_MASK_SET_REG_RESETVAL                 ((uint32_t)(0x00000000U))

/* USER_INT_MASK_CLEAR_REG */

#define CSL_MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR_MASK    ((uint32_t)(0x00000003U))
#define CSL_MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR_SHIFT   ((uint32_t)(0U))
#define CSL_MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR_RESETVAL  ((uint32_t)(0x00000000U))
#define CSL_MDIO_USER_INT_MASK_CLEAR_REG_USERINTMASKCLR_MAX     ((uint32_t)(0x00000003U))

#define CSL_MDIO_USER_INT_MASK_CLEAR_REG_RESETVAL               ((uint32_t)(0x00000000U))

#ifdef __cplusplus
}
#endif
#endif
