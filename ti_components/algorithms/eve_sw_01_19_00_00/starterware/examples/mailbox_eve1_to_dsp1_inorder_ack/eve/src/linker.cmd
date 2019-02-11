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

-e _reset_handler
-w
-stack 0x1000
--heap_size=0x800

MEMORY
{
  PAGE 0:
    VECMEM:  origin 	 = 0x80000000, length = 0x0100
    CMDMEM:  origin 	 = 0x80000100, length = 0x0e00
    DDR_CODE: origin     = 0x80001000, length = 0x7000
  PAGE 1:
    DATMEM      : origin = 0x40020000, length = 0x6000
    RES_SET_LOC : origin = 0x40026000, length = 0x0200
    STACKS:  origin 	 = 0x40027000, length = 0x1000
    IMEML :  origin      = 0x40050000, length = 0x4000
    IMEMH :  origin      = 0x40054000, length = 0x4000
    WMEM  :  origin      = 0x40040000, length = 0x8000
    OCMCRAM: origin 	 = 0x40300000, length = 0x0007fe00
    GEM1L2: origin 	     = 0x40810000, length = 0x00010000
    SYNC_AREA: origin 	 = 0x4037fe00, length = 0x00000100
    DDR: origin 	     = 0x80030000, length = 0x00100000
}



SECTIONS
{
	.intvecs	> VECMEM PAGE 0
	.inthandler	> CMDMEM PAGE 0
	.exitlocation	> CMDMEM PAGE 0
	.text: 		> DDR_CODE  PAGE 0
	{
         
	  *.obj(.text)
        }

  GROUP
  {
      .bss            /* This order facilitates a single segment for */
      .data           /* GDP-relative addressing                     */
      .rodata
  }>DATMEM PAGE 1

  .far         > DATMEM  PAGE 1
  .fardata     > DATMEM  PAGE 1
  .cio         > DATMEM  PAGE 1
  .cinit       > DATMEM  PAGE 1

  Adata:    load = IMEML  PAGE 1
  Bdata:    load = IMEML  PAGE 1
  Cdata:    load = IMEMH  PAGE 1
  Pdata:    load = WMEM   PAGE 1
  Sdata:    > DATMEM      PAGE 1
  EOutdata: > DATMEM       PAGE 1
  res_set_sect: > RES_SET_LOC PAGE 1
  .cint:    > DATMEM PAGE 1
  .bss :    > DATMEM PAGE 1
  .const:   > DATMEM PAGE 1
  .data:    > DATMEM PAGE 1
  .sysmem:  > DATMEM PAGE 1
  .stack:   > STACKS PAGE 1
  .dmem_int_sec > DATMEM PAGE 1
  SectionSync:  load = SYNC_AREA PAGE 1
  DDRData:  > DDR PAGE 1
  OCMCRam_data: > OCMCRAM PAGE 1
  GEM1L2_data: > GEM1L2 PAGE 1
}

