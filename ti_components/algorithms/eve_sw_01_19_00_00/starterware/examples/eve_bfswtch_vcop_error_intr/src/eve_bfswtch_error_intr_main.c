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
#include "vcop_array_add_uns_char_intlv_kernel.h"

#pragma DATA_SECTION(pblock_eve_array_add_uns_char_intlv, ".vcop_parameter_block")
#pragma DATA_ALIGN(pblock_eve_array_add_uns_char_intlv, __ALIGNOF__(int));

/* Following define is defined temparorily because currently we dont have
starterware API for buffer switch */
#define EVE_MEMSWITCH_ERR_IRQENABLE_SET_REG    	0x40080118
#define EVE_MEMSWITCH_ERR_IRQENABLE_CLR_REG 	0x4008011C
#define EVE_MEMSWITCH_ERR_IRQENABLE_STATUS_REG 	0x40080114
#define EVE_MEMSWITCH_ERR_REG 					0x40080028
#define EVE_MEMSWITCH_ERR_ADDR_REG 				0x4008002C


unsigned short pblock_eve_array_add_uns_char_intlv[12];


void Bfswitch_error_Intr_Handler();

volatile unsigned int error_intr_ARP32_occurred = 0;

#define W_INPUT 16
#define H_INPUT 4
#define N0         (W_INPUT * H_INPUT)
#define PAD        (16)
#define N1         (N0 + PAD)


#define W_OUTPUT 16
#define H_OUTPUT 5


#pragma DATA_SECTION (in1, "Adata");
unsigned char in1[N0] = 
{
   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
   0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
   0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
   0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
   0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
   0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
   0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
   0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
}; 

#pragma DATA_SECTION (profile_array, "Adata");
unsigned int profile_array[2];


#pragma DATA_SECTION (in2, "Bdata");
unsigned char in2[N1] = 
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F
};

#pragma DATA_SECTION (out, "Cdata");
unsigned char out[N1] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

unsigned int eve_array_add_uns_char_intlv_init
(
   __vptr_uint8      in1_ptr,
   __vptr_uint8      in2_ptr,
   __vptr_uint8      optr,
   unsigned short    width,
   unsigned short    height,
   unsigned short    *pblock
);

void eve_array_add_uns_char_intlv_vloops(unsigned short *pblock);

void my_eve_array_add_uns_char_intlv_custom
(
   __vptr_uint8     in1_ptr,
   __vptr_uint8     in2_ptr,
   __vptr_uint8     optr,
   unsigned short   width,
   unsigned short   height,
   unsigned short   *pblock
)
{
   /*  Initialize arguments for VCOP                                               */
   
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
   eve_array_add_uns_char_intlv_init (in1_ptr, in2_ptr, optr, width, height, pblock);

   /* Purposefuly hand off A instance to system to tigger VCOP buffer switch error */

   
   VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_VCOP, IBUFLB_VCOP, IBUFHA_SYST, IBUFLA_SYST);
   eve_array_add_uns_char_intlv_vloops(pblock);

   /* Synchronize and return all buffers back to system.                         */
   _vcop_vloop_done();
   
   VCOP_BUF_SWITCH_SET(WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);
}

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


#define W_INPUT 16
#define H_INPUT 4

ReturnCode_t test_main( void )
{
  int     i ;
  unsigned int t0, t1;
  ReturnCode_t checkReturn = RET_OK;

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

  /*  Call VCOP function, with purposeful error injection           */

  for (i = 0; i < 2; i++)
  my_eve_array_add_uns_char_intlv_custom (in1, (in2 + 1), out, W_INPUT, H_INPUT, pblock_eve_array_add_uns_char_intlv);

  /* Actually disable the bit in MSW_ERR IRQ enable */
    //WR_REG_32 (EVE_CONTROL, EVE_CONTROL__EVE_MSW_ERR_IRQENABLE_CLR, 0xF);
	WR_MEM_32_VOLATILE (EVE_MEMSWITCH_ERR_IRQENABLE_CLR_REG, 0xF );

  Check_status (checkReturn);

  return checkReturn;
}

#define VCOP_ERROR_ADDR (0x40084010)

void Bfswitch_error_Intr_Handler( void )
{
  unsigned int value;
  unsigned int err_addr;
  unsigned int value_MSW_IRQStatus;
  unsigned int vcop_error;
  
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
      /* Read and Clear VCOP error register for detecting subsequent errors */

      vcop_error =  RD_MEM_32_VOLATILE(VCOP_ERROR_ADDR);
      WR_MEM_32_VOLATILE (VCOP_ERROR_ADDR, vcop_error);
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
