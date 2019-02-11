/*
*******************************************************************************
 * HDVICP2.0 Based H.264 HP Decoder
 * 
 * "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on "ISO/IEC 14496-10". 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*******************************************************************************
*/

/**  
********************************************************************************
 * @file <InterruptVecTable.c>                          
 *                                       
 * @brief This File contains Interrupt vector table for Ducati Host. 
 *         
 * @author: Multimedia Codecs TI
 *
 *******************************************************************************
*/

/*******************************************************************************
*                             INCLUDE FILES                           
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <stdio.h>
#include <TestApp_constants.h>


/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
#define STACK_SIZE 0xA000

#pragma DATA_SECTION(stack_base, ".stack");
unsigned char stack_base[STACK_SIZE];


/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

typedef void (*ISR_VECTOR_TABLE)();
void resetHandler();
void NMIHandler();
void HFHandler();
void SVCallISR();
void MemManageHandler();
void init_ivt();
extern void Done();
extern int _c_int00();

#pragma DATA_SECTION(vector_table, ".intvecs");
const unsigned int vector_table[] = 
{
  (unsigned int) (stack_base + STACK_SIZE),     /* Stack_base + STACK_SIZE*4 */
  (unsigned int)_c_int00,                      /* ResetHandler               */
  (unsigned int)NMIHandler,
  (unsigned int)HFHandler,
  (unsigned int)MemManageHandler,       /* Populate if using MemManage(MPU)  */
  (unsigned int)10,                     /* Populate if using Bus fault       */
  0,                                    /* Populate if using Usage Fault     */
  0,
  0, 
  0, 
  0,                            /*   Reserved slots                          */
  (unsigned int)SVCallISR,
  0,                            /* Populate if using debug monitor           */
  0,                            /* Reserved                                  */
  0,                            /* Populate if using pendable service request*/
  0,                            /* Populate if using SysTick                 */
  0,                            /* Timer1ISR, external interrupts start here */
  0,                            /* GPIO Input ISR                            */
  0,                            /* GPIO Output ISR                           */
  0,                            /* I2C ISR                                   */
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
  0,                             /* OMAP4 ISR                                 */
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

/*----------------------------------------------------------------------------*/
/*  Extern void c_int00();                                                    */
/*----------------------------------------------------------------------------*/
interrupt void resetHandler()
{
  /* asm ( " B _c_int00"); */
}

interrupt void NMIHandler()
{
}

interrupt void HFHandler()
{
  printf("hardfault");
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

