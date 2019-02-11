/*
********************************************************************************
* HDVICP2.0 Based JPEG Encoder
*
* "HDVICP2.0 Based JPEG Encoder" is software module developed for
* TI's HDVICP2 based SoCs. This module is capable of encoding a raw image
* by compressing it into a JPEG bitstream compliant with ISO/IEC IS 10918-1.
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
* @file      jpegenc_ti_InterruptVecTable.c
*
* @brief     Interrupt vector table for Ducati Host
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Vasudev]
*******************************************************************************
*/

/* -------------------- compilation control switches -------------------------*/

#define STACK_SIZE       0x400

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include "stdio.h"

/*--------------------- program files ----------------------------------------*/

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
typedef void(*ISR_VECTOR_TABLE)();

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/
void resetHandler();
void NMIHandler();
void HFHandler();
void SVCallISR();
extern void Done();
void MemManageHandler();
void init_ivt();
extern int _c_int00();
unsigned int stack_base[STACK_SIZE];

#pragma DATA_SECTION(vectorTable, ".intvecs");
const ISR_VECTOR_TABLE vectorTable[] =
{
  NULL,
  (ISR_VECTOR_TABLE)_c_int00,    /*resetHandler,                              */
  NMIHandler, HFHandler, MemManageHandler,/*Populate if using MemManage(MPU)  */
  (ISR_VECTOR_TABLE)10,          /*Populate if using Bus fault                */
  0,                             /*Populate if using Usage Fault              */
  0, 0, 0, 0,                    /*reserved slots                             */
  SVCallISR, 0,                  /*Populate if using a debug monitor          */
  0,                             /*Reserved                                   */
  0,                             /*Populate if using pendable service request */
  0,                             /*Populate if using SysTick                  */
  0,                             /*Timer1ISR,   external interrupts start here*/
  0,                             /*GpioInISR                                  */
  0,                             /*GpioOutISR,                                */
  0,                             /*I2CIsr                                     */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*IVAHD ISR       */
  0, 0, 0, 0, 0, 0, 0
};

interrupt void resetHandler(){}

interrupt void NMIHandler(){}

interrupt void HFHandler()
{
  printf("hardfault");
}

interrupt void SVCallISR()
{
  int cnt = 0;
  cnt++;
  printf("swi");
  return ;
}

interrupt void MemManageHandler()
{
  printf("address =%x", vectorTable);
  return ;
}

void init_ivt()
{
  printf("address = %x", vectorTable);
}


