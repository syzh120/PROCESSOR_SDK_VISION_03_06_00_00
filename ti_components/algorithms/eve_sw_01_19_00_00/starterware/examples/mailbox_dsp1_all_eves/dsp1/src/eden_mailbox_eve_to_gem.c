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
 *  Filename       gem1/ref_tc_gem1.c
 *
 *  Description    Default code for testcase
 *                 Just returns RET_OK
 *
 * ========================================================================== */
#include <c6x.h>
#include "GlobalTypes.h"
#include "baseaddress.h"

#include "eden_mbids.h"
#include "mbox.h"
#include "INTH_dsp.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INTH_INT_ID_EVE11SYNC 90
#define INTH_INT_ID_EVE22SYNC 91
#define INTH_INT_ID_EVE33SYNC 92
#define INTH_INT_ID_EVE44SYNC 93

#define EVE1__MAILBOX (EVE1__MLB0)
#define EVE2__MAILBOX (EVE2__MLB0)
#define EVE3__MAILBOX (EVE3__MLB0)
#define EVE4__MAILBOX (EVE4__MLB0)

void Mailbox_Intr_Handler(unsigned int evt_no);

volatile unsigned int mailbox_intr_occurred_eve1 = 0;
volatile unsigned int mailbox_intr_occurred_eve2 = 0;
volatile unsigned int mailbox_intr_occurred_eve3 = 0;
volatile unsigned int mailbox_intr_occurred_eve4 = 0;

void TSC_enable();
long long TSC_read();  
unsigned int profile_array[2];
ReturnCode_t checkReturn = RET_OK;

extern void INTH_Init();

void Check_status (int return_value) 
{
    if (return_value == RET_OK) 
    {
        printf("PASS \n");
    }
    else 
    {
        printf("Fail \n");
    }
}


ReturnCode_t test_main( void )
{
  long long t0, t1;
  int       all_msgs = 0;

  INTH_Init();

  TSC_enable();

  /* Enable interrupt in EVE interrupt controller for all EVE's*/
  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE11SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE22SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE33SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  EVE_HOST_INTH_InterruptSetup(INTH_INT_ID_EVE44SYNC,
                      Mailbox_Intr_Handler,
                      INTH_TYPE_IRQ,
                      INTH_DEFAULT_PRIORITY);

  printf("DSP - Interrupt Setup Done \n");
  /* Actually set Enable bit in the interrupt controller */
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE11SYNC);
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE22SYNC);
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE33SYNC);
  EVE_HOST_INTH_InterruptEnable(INTH_INT_ID_EVE44SYNC);

  printf("DSP - Interrupt Enable Done \n");  
  /* Enable interrupt in the mailbox for all EVE's */

  EVE_MBOX_IrqEnable( EVE1__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */
  EVE_MBOX_IrqEnable( EVE2__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */
  EVE_MBOX_IrqEnable( EVE3__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */
  EVE_MBOX_IrqEnable( EVE4__MAILBOX, GEM1_MBID, MBOX_USER_1, MBOX_INT_NEW_MSG_ONLY ); /* enableIrq */

  t0   =  TSC_read();

  

  /* Wait for message from eve1 */
  while (all_msgs != 4)
  {
      all_msgs = (
                    mailbox_intr_occurred_eve1 +
                    mailbox_intr_occurred_eve2 +
                    mailbox_intr_occurred_eve3 +
                    mailbox_intr_occurred_eve4 
                 );

  }

  t1   =  TSC_read();

  profile_array[0] = (t1 - t0);

  t0  =   TSC_read();

  if (mailbox_intr_occurred_eve1  == 0)  checkReturn = RET_FAIL;
  if (mailbox_intr_occurred_eve2  == 0)  checkReturn = RET_FAIL;
  if (mailbox_intr_occurred_eve3  == 0)  checkReturn = RET_FAIL;
  if (mailbox_intr_occurred_eve4  == 0)  checkReturn = RET_FAIL;

  t1 = TSC_read();

  profile_array[1] = (t1 - t0);

  Check_status (checkReturn);

  return checkReturn;
}

void Mailbox_Intr_Handler(unsigned int event)
{
  UWORD32 irqStatusReg = 0;
  MBOX_UserId_t userId = MBOX_USER_1;

  CRED_index_t mailbox;
  UWORD32      rcv_msg;
  UWORD32      snd_msg;
  UWORD32      eve_no;
  UWORD32      rcvd_msg;

  switch (event)
  {
      case INTH_INT_ID_EVE11SYNC:
          mailbox = EVE1__MAILBOX;
          rcv_msg = 0xbadebabe;
          snd_msg = 0x12345678;
          eve_no  = 0;
          mailbox_intr_occurred_eve1++;
          break;

      case INTH_INT_ID_EVE22SYNC:
          mailbox = EVE2__MAILBOX;
          rcv_msg = 0xbadebabf;
          snd_msg = 0x12345679;
          eve_no  = 1;
          mailbox_intr_occurred_eve2++;
          break;

      case INTH_INT_ID_EVE33SYNC:
          mailbox = EVE3__MAILBOX;
          rcv_msg = 0xbadebac0;
          snd_msg = 0x1234567A;
          eve_no  = 2;
          mailbox_intr_occurred_eve3++;
          break;

      case INTH_INT_ID_EVE44SYNC:
          mailbox = EVE4__MAILBOX;
          rcv_msg = 0xbadebac1;
          snd_msg = 0x1234567B;
          eve_no  = 3;
          mailbox_intr_occurred_eve4++;
          break;
 }

 assert ((event >=90) && (event <= 93));

  if ( EVE_MBOX_GetNumMsg( mailbox, /* component */
                   GEM1_MBID /* mailBoxId */
                   ) != 0 )
         {
             rcvd_msg = EVE_MBOX_Read(mailbox, GEM1_MBID);

             if (rcvd_msg == rcv_msg)
             {
                irqStatusReg = EVE_MBOX_IrqGetStatus( mailbox, /* component */
                               GEM1_MBID, /* mailBoxId */
                               userId ) ;

                EVE_MBOX_IrqClearStatus(mailbox, userId, irqStatusReg);

                /* After receiving correct message, send a message to eve1 */
                EVE_MBOX_Write(mailbox,
                    EVE_MBID, /* mailBoxId */
                    snd_msg ); /* writeValue */
              }
              else
              {
                checkReturn = RET_FAIL;
              } /* Correct message ? */
          } /* num message ? */
          else
          {
             checkReturn = RET_FAIL;
          }

  printf ("Saw message from EVE :%d, message:0x%.8x \n", eve_no, rcvd_msg);

}
