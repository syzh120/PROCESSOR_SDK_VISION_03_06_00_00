/*
 *  Copyright (C) 2014-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file  intctl.c
 *
 *  \brief INTCTL library function configures the MPU interrupt handler
 *         with basic functions like routing (to fiq or irq) ,enabling ,
 *         prioritizing, masking each interrupt.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <intctl.h>
#include <ti/csl/cslr_eve.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define INTCTL_INT_TABLE_SIZE     128U
#define INTCTL_PRIORITY_MAX     (INTCTL_INT15)


uint32_t currentInterruptNumber = 0U;
#pragma DATA_SECTION(intctl_IrqPriority, ".dmem_int_sec")
static uint8_t intctl_IrqPriority[INTCTL_INT_TABLE_SIZE];


/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

int32_t EVE_INTCTL_LevelInit (const uint32_t                 baseAddress,
                               const uint8_t                  itNumber,
                               const INTCTL_InterruptKind_t  interruptKind,
                               const INTCTL_Priority_t       priority)
{
    int32_t returnCode = STW_SOK;
    if(itNumber > INTCTL_INT_TABLE_SIZE) {
      returnCode = STW_EFAIL;
    }

    if((itNumber < 32U) && (priority < INTCTL_INT8)) {
      switch ( priority ) {
        case INTCTL_NMI:
          intctl_IrqPriority[itNumber] = INTCTL_NMI;
          break;
        case INTCTL_INT4:
          intctl_IrqPriority[itNumber] = INTCTL_INT4;
          break;
        case INTCTL_INT5:
          intctl_IrqPriority[itNumber] = INTCTL_INT5;
          break;
        case INTCTL_INT6:
          intctl_IrqPriority[itNumber] = INTCTL_INT6;
          break;
        case INTCTL_INT7:
          intctl_IrqPriority[itNumber] = INTCTL_INT7;
          break;
        default:
          break;
      }
    }
    else if(((itNumber >= 32U) && (itNumber < 64U)) &&
            ((priority >= INTCTL_INT8) && (priority < INTCTL_INT12))) {
      switch ( priority ) {
        case INTCTL_INT8:
          intctl_IrqPriority[itNumber] = INTCTL_INT8;
          break;
        case INTCTL_INT9:
          intctl_IrqPriority[itNumber] = INTCTL_INT9;
          break;
        case INTCTL_INT10:
          intctl_IrqPriority[itNumber] = INTCTL_INT10;
          break;
        case INTCTL_INT11:
          intctl_IrqPriority[itNumber] = INTCTL_INT11;
          break;
        default:
          break;
      }
    }
    else if(((itNumber >= 64U) && (itNumber < 96U)) &&
            ((priority >= INTCTL_INT12) && (priority < INTCTL_INT14))) {
      switch ( priority ) {
        case INTCTL_INT12:
          intctl_IrqPriority[itNumber] = INTCTL_INT12;
          break;
        case INTCTL_INT13:
          intctl_IrqPriority[itNumber] = INTCTL_INT13;
          break;
        default:
          break;
      }
    }
    else if(((itNumber >= 96U) && (itNumber < 128U)) &&
            ((priority >= INTCTL_INT14) && (priority <= INTCTL_INT15))) {
      switch ( priority ) {
        case INTCTL_INT14:
          intctl_IrqPriority[itNumber] = INTCTL_INT14;
          break;
        case INTCTL_INT15:
          intctl_IrqPriority[itNumber] = INTCTL_INT15;
          break;
        default:
          break;
      }
    }
    else {
      returnCode = STW_EFAIL;
    }

    return(returnCode);
}

int32_t EVE_INTCTL_OneITEnable(const uint32_t            baseAddress,
                                const uint8_t             itNumber,
                                const INTCTL_Enable_t    enableNdisable)
{
    int32_t returnCode = STW_SOK;
    uint8_t checkPriority;

    checkPriority = intctl_IrqPriority[itNumber];

    if(checkPriority == INTCTL_NMI) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_nmi_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_NMI_IRQENABLE_SET),
                    (uint32_t)1U<<(itNumber));
      }
      else {
        /*write_nmi_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_NMI_IRQENABLE_SET),
                    (uint32_t)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT4) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int4_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT4_IRQENABLE_SET),
                    (uint32_t)1U<<(itNumber));
      }
      else {
        /*write_int4_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT4_IRQENABLE_CLR),
                    (uint32_t)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT5) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int5_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT5_IRQENABLE_SET),
                    (uint32_t)1U<<(itNumber));
      }
      else {
        /*write_int5_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT5_IRQENABLE_CLR),
                    (uint32_t)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT6) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int6_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT6_IRQENABLE_SET),
                    (uint32_t)1U<<(itNumber));
      }
      else {
        /*write_int6_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT6_IRQENABLE_CLR),
                    (uint32_t)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT7) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int7_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT7_IRQENABLE_SET),
                    (uint32_t)1U<<(itNumber));
      }
      else {
        /*write_int7_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT7_IRQENABLE_CLR),
                    (uint32_t)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT8) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int8_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT8_IRQENABLE_SET),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int8_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT8_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT9) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int9_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT9_IRQENABLE_SET),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int9_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT9_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT10) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int10_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT10_IRQENABLE_SET),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int10_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT10_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT11) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int11_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT11_IRQENABLE_SET),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int11_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT11_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT12) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int12_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT12_IRQENABLE_SET),
                   (uint32_t)1U<<((itNumber) - 64U));
      }
      else {
        /*write_int12_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT12_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 64U));
      }
    }
    if(checkPriority == INTCTL_INT13) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int13_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT13_IRQENABLE_SET),
                    (uint32_t)1U<<((itNumber) - 64U));
      }
      else {
        /*write_int13_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT13_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 64U));
      }
    }
    if(checkPriority == INTCTL_INT14) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int14_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT14_IRQENABLE_SET),
                    (uint32_t)1U<<((itNumber) - 96U));
      }
      else {
        /*write_int14_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT14_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 96U));
      }
    }
    if(checkPriority == INTCTL_INT15) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int15_enable*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT15_IRQENABLE_SET),
                    (uint32_t)1U<<((itNumber) - 96U));
      }
      else {
        /*write_int15_clear*/
        HW_WR_REG32((baseAddress+EVE_ARP32_INT15_IRQENABLE_CLR),
                    (uint32_t)1U<<((itNumber) - 96U));
      }
    }
    return (returnCode);
}

int32_t EVE_INTCTL_Ack(const uint32_t                   baseAddress,
                        const INTCTL_Priority_t         interruptPriority,
                        uint16_t *const                  interruptNumber)
{
    uint32_t status_reg;
    uint32_t i;

    switch(interruptPriority) {
      case INTCTL_NMI:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_NMI_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t) i;
            break;
          }
        }
        break;
      case INTCTL_INT4:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT4_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t) i;
            break;
          }
        }
        break;
      case INTCTL_INT5:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT5_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t) i;
            break;
          }
        }
        break;
      case INTCTL_INT6:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT6_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t) i;
            break;
          }
        }
        break;
      case INTCTL_INT7:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT7_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t) i;
            break;
          }
        }
        break;
      case INTCTL_INT8:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT8_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT9:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT9_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT10:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT10_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT11:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT11_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT12:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT12_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 64U);
            break;
          }
        }
        break;
      case INTCTL_INT13:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT13_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 64U);
            break;
          }
        }
        break;
      case INTCTL_INT14:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT14_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 96U);
            break;
          }
        }
        break;
      case INTCTL_INT15:
        status_reg = HW_RD_REG32(baseAddress+EVE_ARP32_INT15_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((uint32_t)1U << i)) == ((uint32_t)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (uint16_t)(i + 96U);
            break;
          }
        }
        break;
      default:
        break;
    }
    return(STW_SOK);
}

int32_t EVE_INTCTL_NextValid(const uint32_t                   baseAddress,
                              const INTCTL_Priority_t         interruptPriority)
{
    switch(interruptPriority) {
      case INTCTL_NMI:
        HW_WR_REG32(baseAddress+EVE_ARP32_NMI_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT4:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT4_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT5:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT5_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT6:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT6_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT7:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT7_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT8:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT8_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT9:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT9_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT10:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT10_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT11:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT11_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT12:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT12_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT13:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT13_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT14:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT14_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT15:
        HW_WR_REG32(baseAddress+EVE_ARP32_INT15_IRQSTATUS,
                   ( (uint32_t)1U << currentInterruptNumber ));
        break;
      default:
        break;
    }

  return ( STW_SOK );

}
