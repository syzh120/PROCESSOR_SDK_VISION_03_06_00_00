/*
*
* Copyright (c) 2008-2017 Texas Instruments Incorporated
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
 *  @Component    INTH - Interrupt (IRQ) handler library component
 *
 *  @Filename     INTH.c
 *
 *  @Description  Interrupt handling utilities
 *
 *//*======================================================================== */

/* ============================================================================
* STANDARD INCLUDE FILES
* =============================================================================
*/

/* ============================================================================
* PROJECT SPECIFIC INCLUDE FILES
* =============================================================================
*/
#include "GlobalTypes.h"
#include "utils.h"

#include "INTH.h"
/*#pragma CHECK_MISRA ("none")*/
#include "baseaddress.h"
/*#pragma RESET_MISRA ("required")*/

#include "INTCTL.h"

/* ============================================================================
* GLOBAL VARIABLES DECLARATIONS
* =============================================================================
*/

/* ============================================================================
* LOCAL TYPES AND DEFINITIONS
* =============================================================================
*/

extern  WORD32  NMI_IRQ_ASM1(void);
extern  WORD32  NMI_IRQ_ASM2(void);

#define INTCPS_U_BASE (EVE_CONTROL)

#ifdef VAYU_PLATFORM
/* number of T16 interrupt inputs 0..127 */
#define INTH_INT_TABLE_SIZE     128U
#endif

#ifdef VME_PLATFORM
/* number of T16 interrupt inputs 0..31 */
#define INTH_INT_TABLE_SIZE     32U
#endif

/* number max of interrupt handlers */
#define INTH_INT_NUM_MAX          (INTH_INT_TABLE_SIZE - 1U)

/* array of interrupt handlers */
/* #pragma DATA_SECTION(inth_IrqHandler, ".dmem_int_sec")*/
  static INTH_Handler_t inth_IrqHandler[INTH_INT_TABLE_SIZE];

/* array of interrupt counter */
  static UWORD32 inth_IrqCount[INTH_INT_TABLE_SIZE];

  /* This is used but, referenced  from intvect.asm */
  UWORD32 IRQ_intTable[8];

  UWORD32 lock_en = 0;

/* ============================================================================
* LOCAL FUNCTIONS PROTOTYPES
* =============================================================================
*/
void INTH_EnableLock(void);
interrupt void NMI_IRQ(void);
interrupt void SWI_IRQ(void);
interrupt void INTH_IRQ4(void);
interrupt void INTH_IRQ5(void);
interrupt void INTH_IRQ6(void);
interrupt void INTH_IRQ7(void);

#ifdef VAYU_PLATFORM
interrupt void INTH_IRQ8(void);
interrupt void INTH_IRQ9(void);
interrupt void INTH_IRQ10(void);
interrupt void INTH_IRQ11(void);
interrupt void INTH_IRQ12(void);
interrupt void INTH_IRQ13(void);
interrupt void INTH_IRQ14(void);
interrupt void INTH_IRQ15(void);
#endif

/* ============================================================================
* FUNCTIONS
* =============================================================================
*/

ReturnCode_t EVE_INTH_InterruptSetup( const UWORD8               intVector,
                                  const UWORD32       intHandler,
                                  const INTH_InterruptKind_t intKind,
                                  const INTH_Priority_t      intPriority)
{
    ReturnCode_t returnCode = RET_OK;

    /* Call interrupt Controler Configuration */
    returnCode = EVE_INTCTL_LevelInit ( INTCPS_U_BASE,
                                    intVector,
                                    (INTCTL_InterruptKind_t) intKind,
                                    (INTCTL_Priority_t) intPriority);
    if ( returnCode == RET_OK )
    {
      /* reset counter and install handler */
      inth_IrqCount[intVector] = 0;
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Its function pointer converted to int  */
      inth_IrqHandler[intVector] = (INTH_Handler_t)intHandler;
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

    return returnCode;

} /* EVE_INTH_InterruptSetup() */


ReturnCode_t EVE_INTH_InterruptEnable( const UWORD8 intVector)
{
   ReturnCode_t returnCode = RET_OK;

   returnCode = EVE_INTCTL_OneITEnable ( INTCPS_U_BASE,
                                     intVector,
                                     INTCTL_ENABLE);

    return returnCode;

} /* EVE_INTH_InterruptEnable() */

ReturnCode_t EVE_INTH_InterruptDisable( const UWORD8 intVector)
{

    ReturnCode_t returnCode = RET_OK;


    returnCode = EVE_INTCTL_OneITEnable ( INTCPS_U_BASE,
                                      intVector,
                                      INTCTL_DISABLE);

    return returnCode;

} /* EVE_INTH_InterruptDisable() */

void INTH_EnableLock(void)
{
  lock_en = 1U;
}


interrupt void NMI_IRQ(void)
{
/*     asm("       STRF    R7, R0             ");
     asm("       MVC    LSA0, R0            ");
     asm("       MVC     LEA0, R1           ");
     asm("       MVC     LCNT0, R2          ");
     asm("       MVC     LSA1, R3           ");
     asm("       MVC     LEA1, R4           ");
     asm("       MVC     LCNT1, R5          ");
     asm("       MVC     LCNT0RLD, R6       ");
     asm("       STRF    R6, R0             "); */
     NMI_IRQ_ASM1();

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
     /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_NMI,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_NMI);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }
/*   return; */

    NMI_IRQ_ASM2();
/*     asm("    LDRF    R0, R6       ");
     asm("    MVC     R0, LSA0     ");
     asm("    MVC     R1, LEA0     ");
     asm("    MVC     R2, LCNT0    ");
     asm("    MVC     R3, LSA1     ");
     asm("    MVC     R4, LEA1     ");
     asm("    MVC     R5, LCNT1    ");
     asm("    MVC     R6, LCNT0RLD ");
     asm("    LDRF    R0, R7       ");
    asm("     NOP                  ");
    asm("     NOP                  ");
    asm("     ADD 4, SP            ");
    asm("     BNRP                 ");
    asm("     NOP                  ");
    asm("     NOP                  ");*/

}

interrupt void SWI_IRQ(void)
{
/*
    UWORD16 lvInterrupt;*/
    /* Get pending interrupt */
/*    EVE_INTCTL_Ack (INTCPS_U_BASE,*/         /* BaseAddress */
/*                INTCTL_IRQ,*/           /* Interrupt Priority */
/*                &lvInterrupt); */       /* Interrupt Id */
    /* increment interrupt counter */
 /*   inth_IrqCount[lvInterrupt]++;*/

    /* if an interrupt handler has been registered */
/*    if (inth_IrqHandler[lvInterrupt])
    {*/
        /* call regitered interrupt handler */
/*        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }*/

    /* Enable for Valid next IRQ*/
/*    EVE_INTCTL_NextValid(INTCPS_U_BASE, */   /* BaseAddress */
/*                     INTCTL_IRQ); */    /* Interrupt Priority */
/*   return;*/

}

interrupt void INTH_IRQ4(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT4,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT4);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ5(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT5,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT5);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ6(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT6,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT6);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ7(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT7,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT7);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

#ifdef VAYU_PLATFORM
interrupt void INTH_IRQ8(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT8,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT8);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt])
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ9(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT9,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT9);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt]  != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ10(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT10,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT10);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ11(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT11,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT11);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ12(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT12,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT12);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ13(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT13,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT13);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ14(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT14,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT14);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}

interrupt void INTH_IRQ15(void)
{
    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0xC7EAD20AU);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }


    UWORD16 lvInterrupt = 0;
    /* Get pending interrupt */
    EVE_INTCTL_Ack (INTCPS_U_BASE,         /* BaseAddress */
                INTCTL_INT15,           /* Interrupt Priority */
                &lvInterrupt);        /* Interrupt Id */

    /* Enable for Valid next IRQ*/
    EVE_INTCTL_NextValid(INTCPS_U_BASE,    /* BaseAddress */
                     INTCTL_INT15);     /* Interrupt Priority */

    /* increment interrupt counter */
    inth_IrqCount[lvInterrupt]++;

    /* if an interrupt handler has been registered */
    if (inth_IrqHandler[lvInterrupt] != NULL)
    {
        /* call regitered interrupt handler */
        inth_IrqHandler[lvInterrupt](lvInterrupt);
    }

    if(lock_en == 1U) {
      /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
      /* MISRA.CAST.PTR_TO_INT : A cast should not be performed between a pointer type and an integral type */
      /* Memory mapped regsiters and other hardware features access requires typecasting of pointer to integer.
      The address space is 32 bit and type casting to integer will not result into any loss because of TI's
      compiler teratment to integer.   */
      WR_MEM_32(0x40080310U,0x12345678U);
      /*RESET_MISRA("11.3")  -> Reset rule 11.3 for MISRA.CAST.PTR_TO_INT */
    }

   return;

}
#endif
