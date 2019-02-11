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

--heap_size=0x1000

MEMORY {
        L2ROM:		o = 0x007E0000, l = 0x4000
        L1PRAM:		o = 0x00E00000, l = 0x8000
        L1DRAM :	o = 0x00F00000, l = 0x8000
        L2RAM:		o = 0x00800000, l = 0x10000
        L2DATA:		o = 0x00810000, l = 0x10000

	OCMCRAM:	o = 0x40300000, l = 0x0007fe00
	SYNC_AREA	o = 0x4037fe00, l = 0x00000100
	DDR		o = 0x80000000, l = 0x80000000
}

SECTIONS
{
    GROUP
    {
        .vects:      {. = align(8);}
	.l2_int:     {. = align(8);}
        .switch:     {. = align(8);}	
        .const:      {. += 0x100;}	
        .text:       {. = align(4);}   
        .int_code:   {. = align(4);}   
        .lib_code:   {. = align(4);}   
        .sysinit:    {. = align(4);}   
        .syssaram:   {. = align(4);}   
        .cinit:	     {. = align(4);}
        .pinit:	     {. = align(4);}
        .data16:     {. = align(2);}
        .data:       {. = align(2);} 
        .bss:	     {. = align(8);} 
        .far:	     {. = align(8);} 
        .cio:        {. = align(8);}
	.sysmem:     {. = align(16);}
	 gem_l2ram_usr_init:   {. = align(8);}
	 gem_l2ram_usr_uninit: {. = align(8);}
        .stack:	     {. = align(8);}
        .sysstack:   {. = align(8);} 
   } > L2RAM

   SectionSync:  load = SYNC_AREA
   GEM1L2_data: > L2DATA
}
