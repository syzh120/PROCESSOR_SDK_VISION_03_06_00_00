
/* ========================================================================= */
/*            Copyright (C) 2008 Texas Instruments, Incorporated.            */
/*                           All Rights Reserved.                            */
/*  Exclusive property of the DSPS R&D Center, Texas Instruments Inc. Any    */
/*   handling, use, disclosure, reproduction, duplication, transmission, or   */
/*   storage of any part of this work by any means is subject to restrictions */
/*  and prior written permission set forth in TI's program license agreements*/
/*  and associated software documentation.                                   */
/*                                       */
/*  This copyright notice, restricted rights legend, or other proprietary    */
/*  markings must be reproduced without modification in any authorized       */
/*  copies of any part of this work.  Removal or modification of any part    */
/*  of this notice is prohibited.                                            */
/*                                       */
/*  =========================================================================*/

/*!  
 *****************************************************************************
 * \file                                     
 *  InterruptVecTable.c                           
 *                                       
 * \brief                                   
 *  Interrupt vector table for Ducati Host     
 *  
 * \version 0.1
 *
 * \date Nov 2008
 *
 * \author                                     
 *  MMCodecs TI India
 *****************************************************************************
 */
#include <stdlib.h>
#include <stdio.h> 
typedef void (*ISR_VECTOR_TABLE)();

#define STACK_SIZE 0x3500

void resetHandler();
void NMIHandler();
void HFHandler();
void SVCallISR();
extern void Done();

void MemManageHandler();
void init_ivt();

extern int _c_int00();

unsigned int stack_base[STACK_SIZE];
typedef unsigned int U32;

#pragma DATA_SECTION(vector_table, ".intvecs");
const U32 vector_table[] = 
{
    (U32)stack_base,/* stack_base + STACK_SIZE*4,                             */
    (U32)_c_int00,/* resetHandler,                                            */
    (U32)NMIHandler,
    (U32)HFHandler,
    (U32)MemManageHandler, /*  Populate if using MemManage (MPU)              */
    (U32)10, /*  Populate if using Bus fault                                  */
    0, /*  Populate if using Usage Fault                                      */
    0,
    0, 
    0, 
    0, /*  reserved slots                                                     */
    (U32)SVCallISR,
    0, /*  Populate if using a debug monitor                                  */
    0, /*  Reserved                                                           */
    0, /*  Populate if using pendable service request                         */
    0, /*  Populate if using SysTick                                          */
    0,/* Timer1ISR,    external interrupts start here                         */
    0,/* GpioInISR                                                            */
    0,/* GpioOutISR,                                                          */
    0,/* I2CIsr                                                               */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,/* IVAHD ISR                                                            */
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/*  extern void c_int00();                                                    */
interrupt void resetHandler()
{
    /* asm ( " B _c_int00");                                                  */
}

interrupt void NMIHandler()
{
}

interrupt void HFHandler()
{
    printf( "hardfault");
}

interrupt void SVCallISR()
{
    int i=0;
    i++;
    printf("swi");
    return;
}

interrupt void MemManageHandler()
{
    printf("address =%x", vector_table);
    return;
}

void init_ivt()
{
    printf("address = %x", vector_table);
}

