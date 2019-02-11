/*
*
* Copyright (c) 2007-2017 Texas Instruments Incorporated
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

/**
 *  @Component    MBOX - Mailbox library component
 *  @Filename    mbox.c
 *  @Description    The mailbox library component offers basic mailbox
 *                  functionality that can be used to transmit 32-bit messages
 *                  between CPUs using the OMAP4.0 Mailbox
 *
 *//*======================================================================== */

/* =============================================================================
 * STANDARD INCLUDE FILES
 * =============================================================================
 */

/* =============================================================================
 * PROJECT SPECIFIC INCLUDE FILES
 * =============================================================================
 */
#include "GlobalTypes.h"
#include "cram.h"

/*#pragma CHECK_MISRA ("none")*/
#include "baseaddress.h"
#include "mlb_cred.h"
/*#pragma RESET_MISRA ("required")*/

#include "mbox.h"

/* =============================================================================
 * GLOBAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* =============================================================================
 * LOCAL TYPES AND DEFINITIONS
 * =============================================================================
 */
/* width/mask in bits of MBOX Id */
#define MBOX_ID_WIDTH           2U
#define MBOX_ID_MASK            0x3U

/****************************************************************/

/* =============================================================================
 * LOCAL VARIABLES DECLARATIONS
 * =============================================================================
 */

/* =============================================================================
 * LOCAL FUNCTIONS PROTOTYPES
 * =============================================================================
 */

/* =============================================================================
 * FUNCTIONS
 * =============================================================================
 */

UWORD32 EVE_MBOX_Read( CRED_index_t  component,
                 MBOX_Id_t     mailBoxId)
{
    UWORD32 message = 0;

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */

    /* Read 32-bit message in mail box */
    message = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_MESSAGE_REGSET_0_15, MLB__MAILBOX_MESSAGE, mailBoxId, MLB__MAILBOX_MESSAGE_REGSET_0_15__ELSIZE, MLB__MAILBOX_MESSAGE__OFFSET);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    return message;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_Write( CRED_index_t  component,
                 MBOX_Id_t     mailBoxId,
                 UWORD32       writeValue )
{
    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    /* Write 32-bit value to mailbox */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_MESSAGE_REGSET_0_15, MLB__MAILBOX_MESSAGE, mailBoxId, writeValue, MLB__MAILBOX_MESSAGE_REGSET_0_15__ELSIZE, MLB__MAILBOX_MESSAGE__OFFSET);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */
    return;
}

/* ======================== Function Separator ============================= */
ReturnCode_t EVE_MBOX_Reset( CRED_index_t  component )
{
    UWORD32      timeoutCounter = 0xFFFU;
    ReturnCode_t returnCode = RET_OK;

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    /* Write 32-bit value to mailbox */

    /* set soft reset bit in Mailbox */
    WR_FIELD_32(component, MLB__MAILBOX_SYSCONFIG, MLB__MAILBOX_SYSCONFIG__SOFTRESET, (UWORD32)MLB__MAILBOX_SYSCONFIG__SOFTRESET__B1, MLB__MAILBOX_SYSCONFIG__SOFTRESET__POS);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */


    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
    /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    /* Write 32-bit value to mailbox */

    /* wait until reset complete and avoid infinite loop */
    while((RD_FIELD_32(component, MLB__MAILBOX_SYSCONFIG, MLB__MAILBOX_SYSCONFIG__SOFTRESET, MLB__MAILBOX_SYSCONFIG__SOFTRESET__POS)!= MLB__MAILBOX_SYSCONFIG__SOFTRESET__B0) &&
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */
          ((timeoutCounter) != 0)                                                   )
    {
        --timeoutCounter;
    }

    /* if timeout occurred */
    if (timeoutCounter == 0)
    {
        returnCode = RET_TIMEOUT;
    }

    return returnCode;
}

/* ======================== Function Separator ============================= */

BOOL EVE_MBOX_IsFull( CRED_index_t  component,
                  MBOX_Id_t     mailBoxId )
{
    UWORD32 fullStatus;
    BOOL returnValue;

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    fullStatus = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_FIFOSTATUS_REGSET_0_15, MLB__MAILBOX_FIFOSTATUS, mailBoxId, MLB__MAILBOX_FIFOSTATUS_REGSET_0_15__ELSIZE, MLB__MAILBOX_FIFOSTATUS__OFFSET);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    /* fill in return parameter */
    if(fullStatus == 0)
    {
        returnValue = (BOOL)false;
    }
    else /* (fullStatus != 0) */
    {
        returnValue = (BOOL)true;
    }

    return returnValue;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_GetNumMsg(
                       CRED_index_t  component,
                     MBOX_Id_t     mailBoxId
                      )
{
    UWORD32       NumMsg = 0;

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    /* Get number of messages available for MailBox */
    NumMsg = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_MSGSTATUS_REGSET_0_15, MLB__MAILBOX_MSGSTATUS, mailBoxId, MLB__MAILBOX_MSGSTATUS_REGSET_0_15__ELSIZE, MLB__MAILBOX_MSGSTATUS__OFFSET);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
        /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    return NumMsg;
} /* MBOX_GetNumMsg() */

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqEnable( CRED_index_t    component,
                   MBOX_Id_t       mailBoxId,
                     MBOX_UserId_t   userId,
                     MBOX_Int_t      enableIrq )
{
    UWORD32     irqEnableReg;
    UWORD32     irqStatusReg = 0;

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    /* Get current enable status */
    irqEnableReg = RD_BUNDLE_ARRAY_32((UWORD32)component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQENABLE_SET, (UWORD32)userId, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQENABLE_SET__OFFSET);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    /* remove previous value for that field*/
    irqEnableReg &= ~(((UWORD32)(MBOX_ID_MASK)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH));

    /* if enabling the not full status bit */
    if(enableIrq != MBOX_INT_NONE)
    {
        /* calculate new enable value to write */
        UWORD32 temp = ((UWORD32)(enableIrq)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH); /*misra fix 12.1*/
        irqEnableReg |=  temp;

        /* Read Irq Status for specified userId */
        /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
        /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
         /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
        /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
        The address space is 32 bit and type casting to integer will not result into any loss because of TI's
        compiler teratment to integer.   */
        irqStatusReg = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQSTATUS_RAW, userId, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQSTATUS_RAW__OFFSET) & (((UWORD32)(MBOX_ID_MASK)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH));
        /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
        /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

        /* Clear status interrupt */
        EVE_MBOX_IrqClearStatus(component, userId, irqStatusReg);
    }

    /* write new enable status */
     /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    /* Write 32-bit value to mailbox */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQENABLE_SET, userId, irqEnableReg, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQENABLE_SET__OFFSET);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    return;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqDisable( CRED_index_t    component,
                      MBOX_Id_t       mailBoxId,
                      MBOX_UserId_t   userId,
                      MBOX_Int_t      disableIrq )
{
    UWORD32      irqDisableReg;

    /* calculate irq bitfields to disable */
    irqDisableReg = (UWORD32)disableIrq << ((UWORD32)mailBoxId * MBOX_ID_WIDTH);

     /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    /* Write 32-bit value to mailbox */
    /* write new enable status */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQENABLE_CLR, userId, irqDisableReg, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQENABLE_CLR__OFFSET);
     /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
     /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    return;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatus( CRED_index_t    component,
         MBOX_Id_t       mailBoxId,
                           MBOX_UserId_t   userId )
{
    UWORD32      irqStatusReg;

    /* Get Irq Status for specified mailbox/User Id */
    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    irqStatusReg = RD_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQSTATUS_RAW, (UWORD32)userId, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQSTATUS_RAW__OFFSET) & (((UWORD32)(MBOX_ID_MASK)) << (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH));
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    return irqStatusReg;
}

/* ======================== Function Separator ============================= */
UWORD32 EVE_MBOX_IrqGetStatusMboxId( MBOX_Id_t       mailBoxId,
                                 UWORD32         irqStatus )
{
    UWORD32 mbox_irqStatus = 0;

    /* Get Irq Status for specified mailbox */
    mbox_irqStatus = ((irqStatus >> (((UWORD32)(mailBoxId))*MBOX_ID_WIDTH)) & ((UWORD32)(MBOX_ID_MASK)));

    return mbox_irqStatus;
}

/* ======================== Function Separator ============================= */
void EVE_MBOX_IrqClearStatus( CRED_index_t     component,
                          MBOX_UserId_t    userId,
                          UWORD32          irqStatus )
{
    /* clear Irq Status for specified userId */
     /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
     /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */
    WR_BUNDLE_ARRAY_32(component, MLB__MAILBOX_IRQ_REGSET_0_3, MLB__MAILBOX_IRQSTATUS_CLR, userId, irqStatus, MLB__MAILBOX_IRQ_REGSET_0_3__ELSIZE, MLB__MAILBOX_IRQSTATUS_CLR__OFFSET);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    /* CHECK_MISRA("-10.3")  -> Disable rule 10.3  */
    /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
    /* MISRA.CAST.INT/ MISRA.CAST.PTR_TO_INT : The value of a complex expression of integer type shall only be */
    /* cast to a type of the same signedness that is no wider than the underlying type of the expression */
    /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
    The address space is 32 bit and type casting to integer will not result into any loss because of TI's
    compiler teratment to integer.   */

    /* clear EOI register for specified userId */
    WR_REG_32(component, MLB__MAILBOX_IRQ_EOI, userId);
    /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    /*RESET_MISRA("10.3")  -> Reset rule 10.3 for MISRA.CAST.INT */

    return;
}
