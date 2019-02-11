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
 *  Filename       eve1/ref_tc_eve1.c
 *
 *  Description    Default code for testcase
 *                 Just returns RET_OK
 *
 * ========================================================================== */
#include "GlobalTypes.h"
#include "baseaddress.h"
#include "common_utils.h"
#include "INTH.h"

#include  <stdio.h>
#include  <stdlib.h>
#include  <arp32.h>
#include  <vcop/vcop.h>

void Bfswitch_error_Intr_Handler();

volatile unsigned int error_intr_ARP32_occurred = 0;

ReturnCode_t checkReturn = RET_OK;

#pragma DATA_SECTION (in1, "Adata");
unsigned int in1[100] = {0};

#pragma DATA_SECTION (in2, "Bdata");
unsigned int in2[100] = {0};

#pragma DATA_SECTION (in3, "Cdata");
unsigned int in3[100] = {0};

#pragma DATA_SECTION (in4, "Ddata");
unsigned int in4[100] = {0};

#pragma DATA_SECTION (in5, "Edata");
unsigned int in5[100] = {0};

/* Following define is defined temparorily because currently we dont have
starterware API for buffer switch */
#define EVE_MEMSWITCH_ERR_IRQENABLE_SET_REG    	0x40080118
#define EVE_MEMSWITCH_ERR_IRQENABLE_CLR_REG 	0x4008011C
#define EVE_MEMSWITCH_ERR_IRQENABLE_STATUS_REG 	0x40080114
#define EVE_MEMSWITCH_ERR_REG 					0x40080028
#define EVE_MEMSWITCH_ERR_ADDR_REG 				0x4008002C

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


void gen_error (unsigned int *ptr, unsigned int val)
{
    *ptr  = val;

    /* Wait for error to be generated and clear error  */
    while (error_intr_ARP32_occurred != 1);
    error_intr_ARP32_occurred = 0;
}

ReturnCode_t test_main( void )
{

    _tsc_start();

    /* Enable interrupt in EVE interrupt controller */
    EVE_INTH_InterruptSetup(EVE_MSW_ERR_INT,
                      (UWORD32)Bfswitch_error_Intr_Handler,
                      INTH_DEFAULT_INTERRUPT_KIND,
                      INTH_INT4);

    /* Actually set Enable bit in the interrupt controller */
    EVE_INTH_InterruptEnable(EVE_MSW_ERR_INT);

    /* Actually enable the bit in MSW_ERR IRQ enable for all MSW errors*/
    //WR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQENABLE_SET, 0xF);
	WR_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_SET_REG, 0xF );

    /* Purposefully transfer IBUFLA to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_VCOP);

    /* Write and generate an error */
    gen_error (&in1[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in1[99], 0xFEADFADE);

    /* Purposefully transfer IBUFLB to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_VCOP, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in2[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in2[99], 0xFEADFADE);

    /* Purposefully transfer WBUF to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in3[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in3[99], 0xFEADFADE);

    /* Purposefully transfer IBUFLB to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in4[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in4[99], 0xFEADFADE);

    /* Purposefully transfer IBUFHB to VCOP and write to generate error  */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_VCOP, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    /* Write and generate an error */
    gen_error (&in5[0], 0xDEADBEEF);

    /* Write and generate another error */
    gen_error (&in5[99], 0xFEADFADE);

    /* Set pass code.                                  */
    checkReturn = RET_OK;
  
    /* Actually disable the bit in MSW_ERR IRQ enable */
    //WR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQENABLE_CLR, 0xF);
	WR_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_CLR_REG, 0xF );

    /* Transfer all buffers back to system            */
    VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    Check_status (checkReturn);

    return checkReturn;
}

void Bfswitch_error_Intr_Handler( void )
{
  unsigned int value;
  unsigned int err_addr;
  unsigned int value_MSW_IRQStatus;

  
  //value_MSW_IRQStatus = RD_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQSTATUS);
  value_MSW_IRQStatus = RD_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_STATUS_REG);

  //value     = RD_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR);
  value     = RD_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_REG);
  //err_addr  = RD_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERRADDR);
  err_addr     = RD_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_ADDR_REG);

  if (value & 1)
  {

  printf ("Fatal ARP32 Error at address 0x%.8x \n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 1, 1);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 1, 1);
  }

  if (value & 2)
  {
      printf ("Fatal VCOP Error at address 0x%.8x \n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 2, 2);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 2, 2);
  }

  if (value & 4)
  {
      printf ("Fatal DMA error at 0x%.8x \n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 4, 4);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 4, 4);
  }
      
  if (value & 8)
  {
      printf ("Fatal External Host DSP/ARM error at 0x%.8x\n", err_addr);
      //MASKWR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR, 8, 8);
	  MASKWR_REG_32 (EVE_MEMSWITCH_ERR_REG, 8, 8);
  }

  if (value)  error_intr_ARP32_occurred++;

  //WR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQSTATUS, value_MSW_IRQStatus);
  WR_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_STATUS_REG, value_MSW_IRQStatus);
}

