/*
********************************************************************************
* HDVICP2.0 Based JPEG Decoder
*
* "HDVICP2.0 Based JPEG Decoder" is software module developed on
* TI's HDVICP2 based SOCs. This module is capable of generating a raw image 
* by de-compressing/decoding a jpeg bit-stream based on ISO/IEC IS 10918-1. 
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
* ALL RIGHTS RESERVED 
********************************************************************************
*/

/**
*******************************************************************************
* @file jpegvdec_ti_interruptvectable.c
*
* @brief  This file contains Interuppt vector table and initialisations for
*         cortex M3 processor for OMAP4
*
* @author: Multimedia Codecs TI
*
* @version 0.0 (Nov 2008) : Base version for IVAHD developement
*                           [Multimedia Codecs TI]
*
* @version 0.1 (Apr 2010) : Review Comments Added
*                           [Ananya]
*
******************************************************************************
*/

/******************************************************************************
*                             INCLUDE FILES                           
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

#include<stdio.h>

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/

/*---------------------- data declarations -----------------------------------*/

/*----------------------------------------------------------------------------*/
/* Stack size for the isr functions                                           */
/*----------------------------------------------------------------------------*/
#define STACK_SIZE 0x3000

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

/*----------------------------------------------------------------------------*/
/*Function pointer to int Vec table                                           */
/*----------------------------------------------------------------------------*/
typedef void (*ISR_VECTOR_TABLE)();

void resetHandler();
void NMIHandler();
void HFHandler();
void SVCallISR();
extern void Done();
void MemManageHandler();
void init_ivt();
extern int _c_int00();

#pragma DATA_SECTION(stack_base, ".stack");
/*----------------------------------------------------------------------*/
/* Define stack for the ISR functions                                   */
/*----------------------------------------------------------------------*/
unsigned char stack_base[STACK_SIZE];

#pragma DATA_SECTION(vector_table, ".intvecs");
ISR_VECTOR_TABLE vector_table[] =
{
  NULL,                          /*  stack_base + STACK_SIZE*4,         */
  (ISR_VECTOR_TABLE)_c_int00,    /*  resetHandler,                      */
  NMIHandler,
  HFHandler,
  MemManageHandler,      /*   Populate if using MemManage (MPU)         */
  (ISR_VECTOR_TABLE)10,  /*   Populate if using Bus fault               */
  0,                     /*   Populate if using Usage Fault             */
  0,
  0,
  0,
  0,                  /*   reserved slots                               */
  SVCallISR,
  0,                  /*   Populate if using a debug monitor            */
  0,                  /*   Reserved                                     */
  0,                  /*   Populate if using pendable service request   */
  0,                  /*   Populate if using SysTick                    */
  0,                  /*  Timer1ISR,   external interrupts start here   */
  0,                  /*  GpioInISR                                     */
  0,                  /*  GpioOutISR,                                   */
  0,                  /*  I2CIsr                                        */
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
/** 
*******************************************************************************
*  @fn     resetHandler
*
*  @brief  
*  @return none
*
*******************************************************************************
*/
interrupt void resetHandler()
{
  /* asm ( " B _c_int00"); */
}
/** 
*******************************************************************************
*  @fn     NMIHandler
*
*  @brief  
*  @return none
*
*******************************************************************************
*/
interrupt void NMIHandler()
{
}
/** 
*******************************************************************************
*  @fn     HFHandler
*
*  @brief  This function is called whenever there is a hard fault interrupt 
*
*  @return none
*
*******************************************************************************
*/
interrupt void HFHandler()
{
  printf("hardfault\n");
}
/** 
*******************************************************************************
*  @fn     SVCallISR
*
*  @brief  
*  @return none
*
*******************************************************************************
*/
interrupt void SVCallISR()
{
  int i=0;
  i++;
  printf("swi");
  return;
}
/** 
*******************************************************************************
*  @fn     MemManageHandler
*
*  @brief  
*  @return none
*
*******************************************************************************
*/
interrupt void MemManageHandler()
{
  printf("address =%x", vector_table);
  return;
}
/** 
*******************************************************************************
*  @fn     init_ivt
*
*  @brief  This function prints the address of the interrupt vector table base
*          address
*
*  @return none
*
*******************************************************************************
*/
void init_ivt()
{
  printf("address = %x", vector_table);
}





