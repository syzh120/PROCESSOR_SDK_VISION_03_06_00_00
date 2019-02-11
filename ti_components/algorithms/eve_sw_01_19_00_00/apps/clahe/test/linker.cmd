/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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


//-e _c_int00
-e _reset_handler
-heap  0x1800000 /* For EXTDMEM heap allocation. .sysmem is in EXTDMEM */
-stack 0x3000 /* Need at least 7092 bytes for evelib_imagePyramid_u8.c */
//--define VCOP_CAMA

MEMORY
{
    PAGE 0:
      VECMEM  :    origin      = 0x80000000, length = 0x0100
      CMDMEM  :    origin      = 0x80000100, length = 0x1000
      EXTMEM  :    origin      = 0x80001100, length = 0x20000

    PAGE 1:
      DATMEM  :    origin = 0x40020000 length = 0x8000
      WMEM    :    origin = 0x40040000 length = 0x7FE0
      IMEMLA  :    origin = 0x40050000 length = 0x4000
      IMEMHA  :    origin = 0x40054000 length = 0x4000
      IMEMLB  :    origin = 0x40070000 length = 0x4000
      IMEMHB  :    origin = 0x40074000 length = 0x4000
      GEM0_L2_MEM: origin = 0x40800000 length = 0x8000
      EXTDMEM :    origin = 0x80030000 length = 0x2000000
      L3MEM   :    origin = 0x40300000, length = 0x100000
}



#ifdef VCOP_CAMA
/*---------------------------------------------------------------------------*/
/* VCOP Compiler Assisted Memory Allocation                                  */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Define VCOP heap sizes. These can be smaller than the actual memory region*/
/*---------------------------------------------------------------------------*/

IMEML_SIZE = 0x4000;
IMEMH_SIZE = 0x4000;
WMEM_SIZE  = 0x7D00;

SECTIONS
{
  .imemla: { *(.imemla) . += (IMEML_SIZE - 8); } > IMEMLA PAGE 1
  .imemha: { *(.imemha) . += (IMEMH_SIZE - 8); } > IMEMHA PAGE 1
  .imemlb: { *(.imemlb) . += (IMEML_SIZE - 8); } > IMEMLB PAGE 1
  .imemhb: { *(.imemhb) . += (IMEMH_SIZE - 8); } > IMEMHB PAGE 1
  .wmem  : { *(.wmem)   . += (WMEM_SIZE  - 8); } > WMEM   PAGE 1
}

#else

/*-----------------------------------------------------------------------------*/
/* Disable VCOP Compiler Assisted Memory Allocation by setting heapsize to zero*/
/*-----------------------------------------------------------------------------*/
IMEML_SIZE = 0;
IMEMH_SIZE = 0;
WMEM_SIZE  = 0;

#endif

/*---------------------------------------------------------------------------*/
/* VCOP Manual Allocation                                                    */
/*---------------------------------------------------------------------------*/

SECTIONS
{
  .const       > EXTDMEM  PAGE 1 //moving to extmem due to dmem space constraint
  Adata        > IMEMLA  PAGE 1
  Bdata        > IMEMHA  PAGE 1
  Cdata        > WMEM    PAGE 1
  EOutdata     > DATMEM  PAGE 1
  Sdata        > DATMEM  PAGE 1
  Udata        > WMEM    PAGE 1
  Vdata        > WMEM    PAGE 1
  Ydata        > WMEM    PAGE 1
  .dmemSect    > DATMEM  PAGE 1
  .cint        > DATMEM  PAGE 1
  .stack       > DATMEM  PAGE 1
  .sysmem      > EXTDMEM  PAGE 1
  .cinit       > DATMEM  PAGE 1
  .cio         > DATMEM  PAGE 1
  .far         > EXTDMEM  PAGE 1
  .fardata     > EXTDMEM  PAGE 1
  .text        > EXTMEM  PAGE 0
  .init_array  > DATMEM  PAGE 1
  .vcop_parameter_block > WMEM PAGE 1
}


SECTIONS
{
  .intvecs      > VECMEM  PAGE 0
  .inthandler   > CMDMEM  PAGE 0
  .exitlocation > CMDMEM  PAGE 0


//  .starterware_text
//  {
//    libevestarterware_eve.lib<*.o*> (.text)
//  } SIZE(_starterware_text_size) > EXTMEM   PAGE 0
//
//  .rts_text
//  {
//    rtsarp32_v200.lib<*.o*> (.text)
//  } SIZE(_rts_text_size) > EXTMEM   PAGE 0
//
//  .text
//  {
//    *(.text)
//  } SIZE(_text_size) > EXTMEM   PAGE 0

  
  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1


   SRC_MEM        > EXTDMEM    PAGE 1//, type= NOLOAD
   DDR_MEM        > EXTDMEM    PAGE 1
   DST_MEM        > EXTDMEM    PAGE 1
   IBUFLA         > IMEMLA     PAGE 1
   IBUFHA         > IMEMHA     PAGE 1
   IBUFLB         > IMEMLB     PAGE 1
   IBUFHB         > IMEMHB     PAGE 1
   WBUF           > WMEM       PAGE 1
   DMEM           > DATMEM	   PAGE 1
}


