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

/*****************************************************************************
* INCLUDE FILES
******************************************************************************
*/

#include "GlobalTypes.h"
#include "cram.h"
/*#pragma CHECK_MISRA ("none")*/
#include "baseaddress.h"
#include "eve_control_cred.h"
/*#pragma RESET_MISRA ("required")*/
#include "INTCTL.h"

/*
****************************************************************************
* GLOBAL VARIABLES DECLARATIONS
******************************************************************************
*/
#ifdef VAYU_PLATFORM
#define INTCTL_INT_TABLE_SIZE     128U
#define INTCTL_PRIORITY_MAX     (INTCTL_INT15)
#endif

#ifdef VME_PLATFORM
#define INTCTL_INT_TABLE_SIZE     32U
#define INTCTL_PRIORITY_MAX     (INTCTL_INT7)
#endif


UWORD32 currentInterruptNumber = 0U;
#pragma DATA_SECTION(intctl_IrqPriority, ".dmem_int_sec")
static UWORD8 intctl_IrqPriority[INTCTL_INT_TABLE_SIZE];


/*
****************************************************************************
* LOCAL TYPES AND DEFINITIONS
******************************************************************************
*/

/*
*****************************************************************************
* LOCAL VARIABLES DECLARATIONS
******************************************************************************
*/

/*
****************************************************************************
* LOCAL FUNCTIONS PROTOTYPES
******************************************************************************
*/

/*
****************************************************************************
* FUNCTIONS
******************************************************************************
*/
/*
****************************************************************************
* INTCTLInitLevel
*****************************************************************************
*/

ReturnCode_t EVE_INTCTL_LevelInit (const UWORD32                 baseAddress,
                               const UWORD8                  itNumber,
                               const INTCTL_InterruptKind_t  interruptKind,
                               const INTCTL_Priority_t       priority)
{
    ReturnCode_t returnCode = RET_OK;
    if(itNumber > INTCTL_INT_TABLE_SIZE) {
      returnCode = RET_FAIL;
    }

    if (priority > INTCTL_PRIORITY_MAX) {
      returnCode = RET_FAIL;
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
#ifdef VAYU_PLATFORM
    else if(((itNumber >= 32U) && (itNumber < 64U)) && ((priority >= INTCTL_INT8) && (priority < INTCTL_INT12))) {
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
    else if(((itNumber >= 64U) && (itNumber < 96U)) && ((priority >= INTCTL_INT12) && (priority < INTCTL_INT14))) {
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
    else if(((itNumber >= 96U) && (itNumber < 128U)) && ((priority >= INTCTL_INT14) && (priority <= INTCTL_INT15))) {
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
#endif
    else {
      returnCode = RET_FAIL;
    }

    return(returnCode);
}/*EVE_INTCTL_LevelInit()*/


/*
*****************************************************************************
* INTCTLEnableOneIT
*****************************************************************************
*/

ReturnCode_t EVE_INTCTL_OneITEnable(const UWORD32            baseAddress,
                                const UWORD8             itNumber,
                                const INTCTL_Enable_t    enableNdisable)
{
    ReturnCode_t returnCode = RET_OK;
    UWORD8 checkPriority;

    checkPriority = intctl_IrqPriority[itNumber];

  /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
  /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
  /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
   The address space is 32 bit and type casting to integer will not result into any loss because of TI's
  compiler teratment to integer.   */

    if(checkPriority == INTCTL_NMI) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_nmi_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_nmi_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT4) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int4_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int4_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT5) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int5_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int5_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT6) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int6_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int6_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
    if(checkPriority == INTCTL_INT7) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int7_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQENABLE_SET,(UWORD32)1U<<(itNumber));
      }
      else {
        /*write_int7_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQENABLE_CLR,(UWORD32)1U<<(itNumber));
      }
    }
#ifdef VAYU_PLATFORM
    if(checkPriority == INTCTL_INT8) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int8_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int8_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT9) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int9_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int9_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT10) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int10_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int10_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT11) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int11_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 32U));
      }
      else {
        /*write_int11_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 32U));
      }
    }
    if(checkPriority == INTCTL_INT12) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int12_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 64U));
      }
      else {
        /*write_int12_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 64U));
      }
    }
    if(checkPriority == INTCTL_INT13) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int13_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 64U));
      }
      else {
        /*write_int13_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 64U));
      }
    }
    if(checkPriority == INTCTL_INT14) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int14_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 96U));
      }
      else {
        /*write_int14_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 96U));
      }
    }
    if(checkPriority == INTCTL_INT15) {
      if(enableNdisable == INTCTL_ENABLE) {
        /*write_int15_enable*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQENABLE_SET,(UWORD32)1U<<((itNumber) - 96U));
      }
      else {
        /*write_int15_clear*/
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQENABLE_CLR,(UWORD32)1U<<((itNumber) - 96U));
      }
    }
#endif
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    return (returnCode);
}/*INTCTLEnableOneIT()*/

ReturnCode_t EVE_INTCTL_Ack(const UWORD32                   baseAddress,
                        const INTCTL_Priority_t         interruptPriority,
                        UWORD16 *const                  interruptNumber)
{
    UWORD32 status_reg;
    UWORD32 i;

   /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
   /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
   /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
   /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
   compiler teratment to integer.   */

    switch(interruptPriority) {
      case INTCTL_NMI:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)i;
            break;
          }
        }
        break;
      case INTCTL_INT4:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)i;
            break;
          }
        }
        break;
      case INTCTL_INT5:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)i;
            break;
          }
        }
        break;
      case INTCTL_INT6:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)i;
            break;
          }
        }
        break;
      case INTCTL_INT7:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)i;
            break;
          }
        }
        break;
#ifdef VAYU_PLATFORM
      case INTCTL_INT8:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT9:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT10:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT11:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 32U);
            break;
          }
        }
        break;
      case INTCTL_INT12:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 64U);
            break;
          }
        }
        break;
      case INTCTL_INT13:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 64U);
            break;
          }
        }
        break;
      case INTCTL_INT14:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 96U);
            break;
          }
        }
        break;
      case INTCTL_INT15:
        status_reg = RD_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQSTATUS);
        for(i = 0; i < 32U; i++) {
          if((status_reg & ((UWORD32)1U << i)) == ((UWORD32)1U << (i))) {
            currentInterruptNumber = i;
            *interruptNumber = (UWORD16)(i + 96U);
            break;
          }
        }
        break;
#endif
      default:
        break;
    }
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */
    return(RET_OK);
}/*EVE_INTCTL_Ack()*/

/*
*****************************************************************************
* EVE_INTCTL_NextValid
*****************************************************************************
*/
ReturnCode_t EVE_INTCTL_NextValid(const UWORD32                   baseAddress,
                              const INTCTL_Priority_t         interruptPriority)
{
   /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
   /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
   /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
   /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
   compiler teratment to integer.   */

    switch(interruptPriority) {
      case INTCTL_NMI:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_NMI_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT4:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT4_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT5:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT5_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT6:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT6_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT7:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT7_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
#ifdef VAYU_PLATFORM
      case INTCTL_INT8:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT8_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT9:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT9_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT10:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT10_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT11:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT11_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT12:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT12_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT13:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT13_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT14:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT14_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
      case INTCTL_INT15:
        WR_REG_32(baseAddress,EVE_CONTROL__ARP32_INT15_IRQSTATUS,( (UWORD32)1U << currentInterruptNumber ));
        break;
#endif
      default:
        break;
    }
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

  return ( RET_OK );

}/*EVE_INTCTL_NextValid()*/

