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



#include <stdio.h>
#include <vcop.h>

#include "test_profile.h"

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;

#define   TRANSPOSE_WIDTH   (8)
#define   IN_W              (32)
#define   IN_H              (64)
#define   N0                (IN_W * IN_H)
#define   N0_div2           (N0/2 + N0/(2 * TRANSPOSE_WIDTH))

/*-------------------------------------------------------------------------*/
/* BLOCK_WIDTH must be a multiple of 16.                                   */
/* BLOCK_HEIGHT must be a multiple of 8.                                   */
/*-------------------------------------------------------------------------*/

#define BLOCK_WIDTH         (32)
#define BLOCK_HEIGHT        (64)

#define   INPUT_TYPE        0   // 0 - uchar, 1 - char, 2 - ushort, 3 - short 
#define   INTER_TYPE        2   // 0 - char, 1 - short, 2 - word, BUT set to 2 as this is the most optimal implementation
#define   OUTPUT_TYPE       2   // 0 - char, 1 - short, 2 - word, for II, always set to 2

#pragma DATA_SECTION(A, "Adata");
const Uint8 A[N0] = { 

         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
                                                                                                                                          
                                                                                                                                          
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
                                                                                                                                          
                                                                                                                                          
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
                                                                                                                                          
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
                                                                                                                                          
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
                                                                                                                                          
                                                                                                                                          
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
         1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,    2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 ,
                                                                                                                                          
                                                                                                                                          
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
                                                                           
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,
         3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,    4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 ,

};

/* Expected output image, make sure it is in DMEM */
#pragma DATA_SECTION(EOut, "EOutdata");
const Uint32 EOut[N0] = { 

0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000a, 0x000b, 0x000c, 0x000d, 0x000e, 0x000f, 0x0010,
0x0012, 0x0014, 0x0016, 0x0018, 0x001a, 0x001c, 0x001e, 0x0020, 0x0022, 0x0024, 0x0026, 0x0028, 0x002a, 0x002c, 0x002e, 0x0030,

0x0002, 0x0004, 0x0006, 0x0008, 0x000a, 0x000c, 0x000e, 0x0010, 0x0012, 0x0014, 0x0016, 0x0018, 0x001a, 0x001c, 0x001e, 0x0020,
0x0024, 0x0028, 0x002c, 0x0030, 0x0034, 0x0038, 0x003c, 0x0040, 0x0044, 0x0048, 0x004c, 0x0050, 0x0054, 0x0058, 0x005c, 0x0060,

0x0003, 0x0006, 0x0009, 0x000c, 0x000f, 0x0012, 0x0015, 0x0018, 0x001b, 0x001e, 0x0021, 0x0024, 0x0027, 0x002a, 0x002d, 0x0030,
0x0036, 0x003c, 0x0042, 0x0048, 0x004e, 0x0054, 0x005a, 0x0060, 0x0066, 0x006c, 0x0072, 0x0078, 0x007e, 0x0084, 0x008a, 0x0090,

0x0004, 0x0008, 0x000c, 0x0010, 0x0014, 0x0018, 0x001c, 0x0020, 0x0024, 0x0028, 0x002c, 0x0030, 0x0034, 0x0038, 0x003c, 0x0040,
0x0048, 0x0050, 0x0058, 0x0060, 0x0068, 0x0070, 0x0078, 0x0080, 0x0088, 0x0090, 0x0098, 0x00a0, 0x00a8, 0x00b0, 0x00b8, 0x00c0,

0x0005, 0x000a, 0x000f, 0x0014, 0x0019, 0x001e, 0x0023, 0x0028, 0x002d, 0x0032, 0x0037, 0x003c, 0x0041, 0x0046, 0x004b, 0x0050,
0x005a, 0x0064, 0x006e, 0x0078, 0x0082, 0x008c, 0x0096, 0x00a0, 0x00aa, 0x00b4, 0x00be, 0x00c8, 0x00d2, 0x00dc, 0x00e6, 0x00f0,

0x0006, 0x000c, 0x0012, 0x0018, 0x001e, 0x0024, 0x002a, 0x0030, 0x0036, 0x003c, 0x0042, 0x0048, 0x004e, 0x0054, 0x005a, 0x0060,
0x006c, 0x0078, 0x0084, 0x0090, 0x009c, 0x00a8, 0x00b4, 0x00c0, 0x00cc, 0x00d8, 0x00e4, 0x00f0, 0x00fc, 0x0108, 0x0114, 0x0120,

0x0007, 0x000e, 0x0015, 0x001c, 0x0023, 0x002a, 0x0031, 0x0038, 0x003f, 0x0046, 0x004d, 0x0054, 0x005b, 0x0062, 0x0069, 0x0070,
0x007e, 0x008c, 0x009a, 0x00a8, 0x00b6, 0x00c4, 0x00d2, 0x00e0, 0x00ee, 0x00fc, 0x010a, 0x0118, 0x0126, 0x0134, 0x0142, 0x0150,

0x0008, 0x0010, 0x0018, 0x0020, 0x0028, 0x0030, 0x0038, 0x0040, 0x0048, 0x0050, 0x0058, 0x0060, 0x0068, 0x0070, 0x0078, 0x0080,
0x0090, 0x00a0, 0x00b0, 0x00c0, 0x00d0, 0x00e0, 0x00f0, 0x0100, 0x0110, 0x0120, 0x0130, 0x0140, 0x0150, 0x0160, 0x0170, 0x0180,

0x0009, 0x0012, 0x001b, 0x0024, 0x002d, 0x0036, 0x003f, 0x0048, 0x0051, 0x005a, 0x0063, 0x006c, 0x0075, 0x007e, 0x0087, 0x0090,
0x00a2, 0x00b4, 0x00c6, 0x00d8, 0x00ea, 0x00fc, 0x010e, 0x0120, 0x0132, 0x0144, 0x0156, 0x0168, 0x017a, 0x018c, 0x019e, 0x01b0,

0x000a, 0x0014, 0x001e, 0x0028, 0x0032, 0x003c, 0x0046, 0x0050, 0x005a, 0x0064, 0x006e, 0x0078, 0x0082, 0x008c, 0x0096, 0x00a0,
0x00b4, 0x00c8, 0x00dc, 0x00f0, 0x0104, 0x0118, 0x012c, 0x0140, 0x0154, 0x0168, 0x017c, 0x0190, 0x01a4, 0x01b8, 0x01cc, 0x01e0,

0x000b, 0x0016, 0x0021, 0x002c, 0x0037, 0x0042, 0x004d, 0x0058, 0x0063, 0x006e, 0x0079, 0x0084, 0x008f, 0x009a, 0x00a5, 0x00b0,
0x00c6, 0x00dc, 0x00f2, 0x0108, 0x011e, 0x0134, 0x014a, 0x0160, 0x0176, 0x018c, 0x01a2, 0x01b8, 0x01ce, 0x01e4, 0x01fa, 0x0210,

0x000c, 0x0018, 0x0024, 0x0030, 0x003c, 0x0048, 0x0054, 0x0060, 0x006c, 0x0078, 0x0084, 0x0090, 0x009c, 0x00a8, 0x00b4, 0x00c0,
0x00d8, 0x00f0, 0x0108, 0x0120, 0x0138, 0x0150, 0x0168, 0x0180, 0x0198, 0x01b0, 0x01c8, 0x01e0, 0x01f8, 0x0210, 0x0228, 0x0240,

0x000d, 0x001a, 0x0027, 0x0034, 0x0041, 0x004e, 0x005b, 0x0068, 0x0075, 0x0082, 0x008f, 0x009c, 0x00a9, 0x00b6, 0x00c3, 0x00d0,
0x00ea, 0x0104, 0x011e, 0x0138, 0x0152, 0x016c, 0x0186, 0x01a0, 0x01ba, 0x01d4, 0x01ee, 0x0208, 0x0222, 0x023c, 0x0256, 0x0270,

0x000e, 0x001c, 0x002a, 0x0038, 0x0046, 0x0054, 0x0062, 0x0070, 0x007e, 0x008c, 0x009a, 0x00a8, 0x00b6, 0x00c4, 0x00d2, 0x00e0,
0x00fc, 0x0118, 0x0134, 0x0150, 0x016c, 0x0188, 0x01a4, 0x01c0, 0x01dc, 0x01f8, 0x0214, 0x0230, 0x024c, 0x0268, 0x0284, 0x02a0,

0x000f, 0x001e, 0x002d, 0x003c, 0x004b, 0x005a, 0x0069, 0x0078, 0x0087, 0x0096, 0x00a5, 0x00b4, 0x00c3, 0x00d2, 0x00e1, 0x00f0,
0x010e, 0x012c, 0x014a, 0x0168, 0x0186, 0x01a4, 0x01c2, 0x01e0, 0x01fe, 0x021c, 0x023a, 0x0258, 0x0276, 0x0294, 0x02b2, 0x02d0,

0x0010, 0x0020, 0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080, 0x0090, 0x00a0, 0x00b0, 0x00c0, 0x00d0, 0x00e0, 0x00f0, 0x0100,
0x0120, 0x0140, 0x0160, 0x0180, 0x01a0, 0x01c0, 0x01e0, 0x0200, 0x0220, 0x0240, 0x0260, 0x0280, 0x02a0, 0x02c0, 0x02e0, 0x0300,

0x0013, 0x0026, 0x0039, 0x004c, 0x005f, 0x0072, 0x0085, 0x0098, 0x00ab, 0x00be, 0x00d1, 0x00e4, 0x00f7, 0x010a, 0x011d, 0x0130,
0x0154, 0x0178, 0x019c, 0x01c0, 0x01e4, 0x0208, 0x022c, 0x0250, 0x0274, 0x0298, 0x02bc, 0x02e0, 0x0304, 0x0328, 0x034c, 0x0370,

0x0016, 0x002c, 0x0042, 0x0058, 0x006e, 0x0084, 0x009a, 0x00b0, 0x00c6, 0x00dc, 0x00f2, 0x0108, 0x011e, 0x0134, 0x014a, 0x0160,
0x0188, 0x01b0, 0x01d8, 0x0200, 0x0228, 0x0250, 0x0278, 0x02a0, 0x02c8, 0x02f0, 0x0318, 0x0340, 0x0368, 0x0390, 0x03b8, 0x03e0,

0x0019, 0x0032, 0x004b, 0x0064, 0x007d, 0x0096, 0x00af, 0x00c8, 0x00e1, 0x00fa, 0x0113, 0x012c, 0x0145, 0x015e, 0x0177, 0x0190,
0x01bc, 0x01e8, 0x0214, 0x0240, 0x026c, 0x0298, 0x02c4, 0x02f0, 0x031c, 0x0348, 0x0374, 0x03a0, 0x03cc, 0x03f8, 0x0424, 0x0450,

0x001c, 0x0038, 0x0054, 0x0070, 0x008c, 0x00a8, 0x00c4, 0x00e0, 0x00fc, 0x0118, 0x0134, 0x0150, 0x016c, 0x0188, 0x01a4, 0x01c0,
0x01f0, 0x0220, 0x0250, 0x0280, 0x02b0, 0x02e0, 0x0310, 0x0340, 0x0370, 0x03a0, 0x03d0, 0x0400, 0x0430, 0x0460, 0x0490, 0x04c0,

0x001f, 0x003e, 0x005d, 0x007c, 0x009b, 0x00ba, 0x00d9, 0x00f8, 0x0117, 0x0136, 0x0155, 0x0174, 0x0193, 0x01b2, 0x01d1, 0x01f0,
0x0224, 0x0258, 0x028c, 0x02c0, 0x02f4, 0x0328, 0x035c, 0x0390, 0x03c4, 0x03f8, 0x042c, 0x0460, 0x0494, 0x04c8, 0x04fc, 0x0530,

0x0022, 0x0044, 0x0066, 0x0088, 0x00aa, 0x00cc, 0x00ee, 0x0110, 0x0132, 0x0154, 0x0176, 0x0198, 0x01ba, 0x01dc, 0x01fe, 0x0220,
0x0258, 0x0290, 0x02c8, 0x0300, 0x0338, 0x0370, 0x03a8, 0x03e0, 0x0418, 0x0450, 0x0488, 0x04c0, 0x04f8, 0x0530, 0x0568, 0x05a0,

0x0025, 0x004a, 0x006f, 0x0094, 0x00b9, 0x00de, 0x0103, 0x0128, 0x014d, 0x0172, 0x0197, 0x01bc, 0x01e1, 0x0206, 0x022b, 0x0250,
0x028c, 0x02c8, 0x0304, 0x0340, 0x037c, 0x03b8, 0x03f4, 0x0430, 0x046c, 0x04a8, 0x04e4, 0x0520, 0x055c, 0x0598, 0x05d4, 0x0610,

0x0028, 0x0050, 0x0078, 0x00a0, 0x00c8, 0x00f0, 0x0118, 0x0140, 0x0168, 0x0190, 0x01b8, 0x01e0, 0x0208, 0x0230, 0x0258, 0x0280,
0x02c0, 0x0300, 0x0340, 0x0380, 0x03c0, 0x0400, 0x0440, 0x0480, 0x04c0, 0x0500, 0x0540, 0x0580, 0x05c0, 0x0600, 0x0640, 0x0680,

0x002b, 0x0056, 0x0081, 0x00ac, 0x00d7, 0x0102, 0x012d, 0x0158, 0x0183, 0x01ae, 0x01d9, 0x0204, 0x022f, 0x025a, 0x0285, 0x02b0,
0x02f4, 0x0338, 0x037c, 0x03c0, 0x0404, 0x0448, 0x048c, 0x04d0, 0x0514, 0x0558, 0x059c, 0x05e0, 0x0624, 0x0668, 0x06ac, 0x06f0,

0x002e, 0x005c, 0x008a, 0x00b8, 0x00e6, 0x0114, 0x0142, 0x0170, 0x019e, 0x01cc, 0x01fa, 0x0228, 0x0256, 0x0284, 0x02b2, 0x02e0,
0x0328, 0x0370, 0x03b8, 0x0400, 0x0448, 0x0490, 0x04d8, 0x0520, 0x0568, 0x05b0, 0x05f8, 0x0640, 0x0688, 0x06d0, 0x0718, 0x0760,

0x0031, 0x0062, 0x0093, 0x00c4, 0x00f5, 0x0126, 0x0157, 0x0188, 0x01b9, 0x01ea, 0x021b, 0x024c, 0x027d, 0x02ae, 0x02df, 0x0310,
0x035c, 0x03a8, 0x03f4, 0x0440, 0x048c, 0x04d8, 0x0524, 0x0570, 0x05bc, 0x0608, 0x0654, 0x06a0, 0x06ec, 0x0738, 0x0784, 0x07d0,

0x0034, 0x0068, 0x009c, 0x00d0, 0x0104, 0x0138, 0x016c, 0x01a0, 0x01d4, 0x0208, 0x023c, 0x0270, 0x02a4, 0x02d8, 0x030c, 0x0340,
0x0390, 0x03e0, 0x0430, 0x0480, 0x04d0, 0x0520, 0x0570, 0x05c0, 0x0610, 0x0660, 0x06b0, 0x0700, 0x0750, 0x07a0, 0x07f0, 0x0840,

0x0037, 0x006e, 0x00a5, 0x00dc, 0x0113, 0x014a, 0x0181, 0x01b8, 0x01ef, 0x0226, 0x025d, 0x0294, 0x02cb, 0x0302, 0x0339, 0x0370,
0x03c4, 0x0418, 0x046c, 0x04c0, 0x0514, 0x0568, 0x05bc, 0x0610, 0x0664, 0x06b8, 0x070c, 0x0760, 0x07b4, 0x0808, 0x085c, 0x08b0,

0x003a, 0x0074, 0x00ae, 0x00e8, 0x0122, 0x015c, 0x0196, 0x01d0, 0x020a, 0x0244, 0x027e, 0x02b8, 0x02f2, 0x032c, 0x0366, 0x03a0,
0x03f8, 0x0450, 0x04a8, 0x0500, 0x0558, 0x05b0, 0x0608, 0x0660, 0x06b8, 0x0710, 0x0768, 0x07c0, 0x0818, 0x0870, 0x08c8, 0x0920,

0x003d, 0x007a, 0x00b7, 0x00f4, 0x0131, 0x016e, 0x01ab, 0x01e8, 0x0225, 0x0262, 0x029f, 0x02dc, 0x0319, 0x0356, 0x0393, 0x03d0,
0x042c, 0x0488, 0x04e4, 0x0540, 0x059c, 0x05f8, 0x0654, 0x06b0, 0x070c, 0x0768, 0x07c4, 0x0820, 0x087c, 0x08d8, 0x0934, 0x0990,

0x0040, 0x0080, 0x00c0, 0x0100, 0x0140, 0x0180, 0x01c0, 0x0200, 0x0240, 0x0280, 0x02c0, 0x0300, 0x0340, 0x0380, 0x03c0, 0x0400,
0x0460, 0x04c0, 0x0520, 0x0580, 0x05e0, 0x0640, 0x06a0, 0x0700, 0x0760, 0x07c0, 0x0820, 0x0880, 0x08e0, 0x0940, 0x09a0, 0x0a00,

0x0041, 0x0082, 0x00c3, 0x0104, 0x0145, 0x0186, 0x01c7, 0x0208, 0x0249, 0x028a, 0x02cb, 0x030c, 0x034d, 0x038e, 0x03cf, 0x0410,
0x0472, 0x04d4, 0x0536, 0x0598, 0x05fa, 0x065c, 0x06be, 0x0720, 0x0782, 0x07e4, 0x0846, 0x08a8, 0x090a, 0x096c, 0x09ce, 0x0a30,

0x0042, 0x0084, 0x00c6, 0x0108, 0x014a, 0x018c, 0x01ce, 0x0210, 0x0252, 0x0294, 0x02d6, 0x0318, 0x035a, 0x039c, 0x03de, 0x0420,
0x0484, 0x04e8, 0x054c, 0x05b0, 0x0614, 0x0678, 0x06dc, 0x0740, 0x07a4, 0x0808, 0x086c, 0x08d0, 0x0934, 0x0998, 0x09fc, 0x0a60,

0x0043, 0x0086, 0x00c9, 0x010c, 0x014f, 0x0192, 0x01d5, 0x0218, 0x025b, 0x029e, 0x02e1, 0x0324, 0x0367, 0x03aa, 0x03ed, 0x0430,
0x0496, 0x04fc, 0x0562, 0x05c8, 0x062e, 0x0694, 0x06fa, 0x0760, 0x07c6, 0x082c, 0x0892, 0x08f8, 0x095e, 0x09c4, 0x0a2a, 0x0a90,

0x0044, 0x0088, 0x00cc, 0x0110, 0x0154, 0x0198, 0x01dc, 0x0220, 0x0264, 0x02a8, 0x02ec, 0x0330, 0x0374, 0x03b8, 0x03fc, 0x0440,
0x04a8, 0x0510, 0x0578, 0x05e0, 0x0648, 0x06b0, 0x0718, 0x0780, 0x07e8, 0x0850, 0x08b8, 0x0920, 0x0988, 0x09f0, 0x0a58, 0x0ac0,

0x0045, 0x008a, 0x00cf, 0x0114, 0x0159, 0x019e, 0x01e3, 0x0228, 0x026d, 0x02b2, 0x02f7, 0x033c, 0x0381, 0x03c6, 0x040b, 0x0450,
0x04ba, 0x0524, 0x058e, 0x05f8, 0x0662, 0x06cc, 0x0736, 0x07a0, 0x080a, 0x0874, 0x08de, 0x0948, 0x09b2, 0x0a1c, 0x0a86, 0x0af0,

0x0046, 0x008c, 0x00d2, 0x0118, 0x015e, 0x01a4, 0x01ea, 0x0230, 0x0276, 0x02bc, 0x0302, 0x0348, 0x038e, 0x03d4, 0x041a, 0x0460,
0x04cc, 0x0538, 0x05a4, 0x0610, 0x067c, 0x06e8, 0x0754, 0x07c0, 0x082c, 0x0898, 0x0904, 0x0970, 0x09dc, 0x0a48, 0x0ab4, 0x0b20,

0x0047, 0x008e, 0x00d5, 0x011c, 0x0163, 0x01aa, 0x01f1, 0x0238, 0x027f, 0x02c6, 0x030d, 0x0354, 0x039b, 0x03e2, 0x0429, 0x0470,
0x04de, 0x054c, 0x05ba, 0x0628, 0x0696, 0x0704, 0x0772, 0x07e0, 0x084e, 0x08bc, 0x092a, 0x0998, 0x0a06, 0x0a74, 0x0ae2, 0x0b50,

0x0048, 0x0090, 0x00d8, 0x0120, 0x0168, 0x01b0, 0x01f8, 0x0240, 0x0288, 0x02d0, 0x0318, 0x0360, 0x03a8, 0x03f0, 0x0438, 0x0480,
0x04f0, 0x0560, 0x05d0, 0x0640, 0x06b0, 0x0720, 0x0790, 0x0800, 0x0870, 0x08e0, 0x0950, 0x09c0, 0x0a30, 0x0aa0, 0x0b10, 0x0b80,

0x0049, 0x0092, 0x00db, 0x0124, 0x016d, 0x01b6, 0x01ff, 0x0248, 0x0291, 0x02da, 0x0323, 0x036c, 0x03b5, 0x03fe, 0x0447, 0x0490,
0x0502, 0x0574, 0x05e6, 0x0658, 0x06ca, 0x073c, 0x07ae, 0x0820, 0x0892, 0x0904, 0x0976, 0x09e8, 0x0a5a, 0x0acc, 0x0b3e, 0x0bb0,

0x004a, 0x0094, 0x00de, 0x0128, 0x0172, 0x01bc, 0x0206, 0x0250, 0x029a, 0x02e4, 0x032e, 0x0378, 0x03c2, 0x040c, 0x0456, 0x04a0,
0x0514, 0x0588, 0x05fc, 0x0670, 0x06e4, 0x0758, 0x07cc, 0x0840, 0x08b4, 0x0928, 0x099c, 0x0a10, 0x0a84, 0x0af8, 0x0b6c, 0x0be0,

0x004b, 0x0096, 0x00e1, 0x012c, 0x0177, 0x01c2, 0x020d, 0x0258, 0x02a3, 0x02ee, 0x0339, 0x0384, 0x03cf, 0x041a, 0x0465, 0x04b0,
0x0526, 0x059c, 0x0612, 0x0688, 0x06fe, 0x0774, 0x07ea, 0x0860, 0x08d6, 0x094c, 0x09c2, 0x0a38, 0x0aae, 0x0b24, 0x0b9a, 0x0c10,

0x004c, 0x0098, 0x00e4, 0x0130, 0x017c, 0x01c8, 0x0214, 0x0260, 0x02ac, 0x02f8, 0x0344, 0x0390, 0x03dc, 0x0428, 0x0474, 0x04c0,
0x0538, 0x05b0, 0x0628, 0x06a0, 0x0718, 0x0790, 0x0808, 0x0880, 0x08f8, 0x0970, 0x09e8, 0x0a60, 0x0ad8, 0x0b50, 0x0bc8, 0x0c40,

0x004d, 0x009a, 0x00e7, 0x0134, 0x0181, 0x01ce, 0x021b, 0x0268, 0x02b5, 0x0302, 0x034f, 0x039c, 0x03e9, 0x0436, 0x0483, 0x04d0,
0x054a, 0x05c4, 0x063e, 0x06b8, 0x0732, 0x07ac, 0x0826, 0x08a0, 0x091a, 0x0994, 0x0a0e, 0x0a88, 0x0b02, 0x0b7c, 0x0bf6, 0x0c70,

0x004e, 0x009c, 0x00ea, 0x0138, 0x0186, 0x01d4, 0x0222, 0x0270, 0x02be, 0x030c, 0x035a, 0x03a8, 0x03f6, 0x0444, 0x0492, 0x04e0,
0x055c, 0x05d8, 0x0654, 0x06d0, 0x074c, 0x07c8, 0x0844, 0x08c0, 0x093c, 0x09b8, 0x0a34, 0x0ab0, 0x0b2c, 0x0ba8, 0x0c24, 0x0ca0,

0x004f, 0x009e, 0x00ed, 0x013c, 0x018b, 0x01da, 0x0229, 0x0278, 0x02c7, 0x0316, 0x0365, 0x03b4, 0x0403, 0x0452, 0x04a1, 0x04f0,
0x056e, 0x05ec, 0x066a, 0x06e8, 0x0766, 0x07e4, 0x0862, 0x08e0, 0x095e, 0x09dc, 0x0a5a, 0x0ad8, 0x0b56, 0x0bd4, 0x0c52, 0x0cd0,

0x0050, 0x00a0, 0x00f0, 0x0140, 0x0190, 0x01e0, 0x0230, 0x0280, 0x02d0, 0x0320, 0x0370, 0x03c0, 0x0410, 0x0460, 0x04b0, 0x0500,
0x0580, 0x0600, 0x0680, 0x0700, 0x0780, 0x0800, 0x0880, 0x0900, 0x0980, 0x0a00, 0x0a80, 0x0b00, 0x0b80, 0x0c00, 0x0c80, 0x0d00,

0x0053, 0x00a6, 0x00f9, 0x014c, 0x019f, 0x01f2, 0x0245, 0x0298, 0x02eb, 0x033e, 0x0391, 0x03e4, 0x0437, 0x048a, 0x04dd, 0x0530,
0x05b4, 0x0638, 0x06bc, 0x0740, 0x07c4, 0x0848, 0x08cc, 0x0950, 0x09d4, 0x0a58, 0x0adc, 0x0b60, 0x0be4, 0x0c68, 0x0cec, 0x0d70,

0x0056, 0x00ac, 0x0102, 0x0158, 0x01ae, 0x0204, 0x025a, 0x02b0, 0x0306, 0x035c, 0x03b2, 0x0408, 0x045e, 0x04b4, 0x050a, 0x0560,
0x05e8, 0x0670, 0x06f8, 0x0780, 0x0808, 0x0890, 0x0918, 0x09a0, 0x0a28, 0x0ab0, 0x0b38, 0x0bc0, 0x0c48, 0x0cd0, 0x0d58, 0x0de0,

0x0059, 0x00b2, 0x010b, 0x0164, 0x01bd, 0x0216, 0x026f, 0x02c8, 0x0321, 0x037a, 0x03d3, 0x042c, 0x0485, 0x04de, 0x0537, 0x0590,
0x061c, 0x06a8, 0x0734, 0x07c0, 0x084c, 0x08d8, 0x0964, 0x09f0, 0x0a7c, 0x0b08, 0x0b94, 0x0c20, 0x0cac, 0x0d38, 0x0dc4, 0x0e50,

0x005c, 0x00b8, 0x0114, 0x0170, 0x01cc, 0x0228, 0x0284, 0x02e0, 0x033c, 0x0398, 0x03f4, 0x0450, 0x04ac, 0x0508, 0x0564, 0x05c0,
0x0650, 0x06e0, 0x0770, 0x0800, 0x0890, 0x0920, 0x09b0, 0x0a40, 0x0ad0, 0x0b60, 0x0bf0, 0x0c80, 0x0d10, 0x0da0, 0x0e30, 0x0ec0,

0x005f, 0x00be, 0x011d, 0x017c, 0x01db, 0x023a, 0x0299, 0x02f8, 0x0357, 0x03b6, 0x0415, 0x0474, 0x04d3, 0x0532, 0x0591, 0x05f0,
0x0684, 0x0718, 0x07ac, 0x0840, 0x08d4, 0x0968, 0x09fc, 0x0a90, 0x0b24, 0x0bb8, 0x0c4c, 0x0ce0, 0x0d74, 0x0e08, 0x0e9c, 0x0f30,

0x0062, 0x00c4, 0x0126, 0x0188, 0x01ea, 0x024c, 0x02ae, 0x0310, 0x0372, 0x03d4, 0x0436, 0x0498, 0x04fa, 0x055c, 0x05be, 0x0620,
0x06b8, 0x0750, 0x07e8, 0x0880, 0x0918, 0x09b0, 0x0a48, 0x0ae0, 0x0b78, 0x0c10, 0x0ca8, 0x0d40, 0x0dd8, 0x0e70, 0x0f08, 0x0fa0,

0x0065, 0x00ca, 0x012f, 0x0194, 0x01f9, 0x025e, 0x02c3, 0x0328, 0x038d, 0x03f2, 0x0457, 0x04bc, 0x0521, 0x0586, 0x05eb, 0x0650,
0x06ec, 0x0788, 0x0824, 0x08c0, 0x095c, 0x09f8, 0x0a94, 0x0b30, 0x0bcc, 0x0c68, 0x0d04, 0x0da0, 0x0e3c, 0x0ed8, 0x0f74, 0x1010,

0x0068, 0x00d0, 0x0138, 0x01a0, 0x0208, 0x0270, 0x02d8, 0x0340, 0x03a8, 0x0410, 0x0478, 0x04e0, 0x0548, 0x05b0, 0x0618, 0x0680,
0x0720, 0x07c0, 0x0860, 0x0900, 0x09a0, 0x0a40, 0x0ae0, 0x0b80, 0x0c20, 0x0cc0, 0x0d60, 0x0e00, 0x0ea0, 0x0f40, 0x0fe0, 0x1080,

0x006b, 0x00d6, 0x0141, 0x01ac, 0x0217, 0x0282, 0x02ed, 0x0358, 0x03c3, 0x042e, 0x0499, 0x0504, 0x056f, 0x05da, 0x0645, 0x06b0,
0x0754, 0x07f8, 0x089c, 0x0940, 0x09e4, 0x0a88, 0x0b2c, 0x0bd0, 0x0c74, 0x0d18, 0x0dbc, 0x0e60, 0x0f04, 0x0fa8, 0x104c, 0x10f0,

0x006e, 0x00dc, 0x014a, 0x01b8, 0x0226, 0x0294, 0x0302, 0x0370, 0x03de, 0x044c, 0x04ba, 0x0528, 0x0596, 0x0604, 0x0672, 0x06e0,
0x0788, 0x0830, 0x08d8, 0x0980, 0x0a28, 0x0ad0, 0x0b78, 0x0c20, 0x0cc8, 0x0d70, 0x0e18, 0x0ec0, 0x0f68, 0x1010, 0x10b8, 0x1160,

0x0071, 0x00e2, 0x0153, 0x01c4, 0x0235, 0x02a6, 0x0317, 0x0388, 0x03f9, 0x046a, 0x04db, 0x054c, 0x05bd, 0x062e, 0x069f, 0x0710,
0x07bc, 0x0868, 0x0914, 0x09c0, 0x0a6c, 0x0b18, 0x0bc4, 0x0c70, 0x0d1c, 0x0dc8, 0x0e74, 0x0f20, 0x0fcc, 0x1078, 0x1124, 0x11d0,

0x0074, 0x00e8, 0x015c, 0x01d0, 0x0244, 0x02b8, 0x032c, 0x03a0, 0x0414, 0x0488, 0x04fc, 0x0570, 0x05e4, 0x0658, 0x06cc, 0x0740,
0x07f0, 0x08a0, 0x0950, 0x0a00, 0x0ab0, 0x0b60, 0x0c10, 0x0cc0, 0x0d70, 0x0e20, 0x0ed0, 0x0f80, 0x1030, 0x10e0, 0x1190, 0x1240,

0x0077, 0x00ee, 0x0165, 0x01dc, 0x0253, 0x02ca, 0x0341, 0x03b8, 0x042f, 0x04a6, 0x051d, 0x0594, 0x060b, 0x0682, 0x06f9, 0x0770,
0x0824, 0x08d8, 0x098c, 0x0a40, 0x0af4, 0x0ba8, 0x0c5c, 0x0d10, 0x0dc4, 0x0e78, 0x0f2c, 0x0fe0, 0x1094, 0x1148, 0x11fc, 0x12b0,

0x007a, 0x00f4, 0x016e, 0x01e8, 0x0262, 0x02dc, 0x0356, 0x03d0, 0x044a, 0x04c4, 0x053e, 0x05b8, 0x0632, 0x06ac, 0x0726, 0x07a0,
0x0858, 0x0910, 0x09c8, 0x0a80, 0x0b38, 0x0bf0, 0x0ca8, 0x0d60, 0x0e18, 0x0ed0, 0x0f88, 0x1040, 0x10f8, 0x11b0, 0x1268, 0x1320,

0x007d, 0x00fa, 0x0177, 0x01f4, 0x0271, 0x02ee, 0x036b, 0x03e8, 0x0465, 0x04e2, 0x055f, 0x05dc, 0x0659, 0x06d6, 0x0753, 0x07d0,
0x088c, 0x0948, 0x0a04, 0x0ac0, 0x0b7c, 0x0c38, 0x0cf4, 0x0db0, 0x0e6c, 0x0f28, 0x0fe4, 0x10a0, 0x115c, 0x1218, 0x12d4, 0x1390,

0x0080, 0x0100, 0x0180, 0x0200, 0x0280, 0x0300, 0x0380, 0x0400, 0x0480, 0x0500, 0x0580, 0x0600, 0x0680, 0x0700, 0x0780, 0x0800,
0x08c0, 0x0980, 0x0a40, 0x0b00, 0x0bc0, 0x0c80, 0x0d40, 0x0e00, 0x0ec0, 0x0f80, 0x1040, 0x1100, 0x11c0, 0x1280, 0x1340, 0x1400,

};

#pragma DATA_SECTION(B0, "Bdata");
Uint32 B0[N0_div2];

#pragma DATA_SECTION(B1, "Cdata");
Uint32 B1[N0_div2];

#pragma DATA_SECTION(C0, "Bdata");
Uint32 C0[N0_div2];

#pragma DATA_SECTION(ACC_H, "Cdata");
Uint32 ACC_H[IN_W];

/*-------------------------------------------------------------------------*/
/* Size of ACC_V should be equal to the height of the image.               */
/* This is a 1-D array, with size of 'height' of the image.                */
/*-------------------------------------------------------------------------*/

#pragma DATA_SECTION(ACC_V, "Cdata");
Uint32 ACC_V[IN_H];

#pragma DATA_SECTION(C1, "Cdata");
Uint32 C1[N0_div2];

#pragma DATA_SECTION(out, "Cdata");
Uint32 out[N0];
        
#if VCOP_HOST_EMULATION
  #include "eve_integral_image_kernel.k"    // kernel source
#else
  #include "../inc/eve_integral_image_kernel.h"    // translated kernel
#endif

int print_verify_output();
void reset_acc_mem( Uint32 *in, int size);

int main()
{
    
    unsigned short no_blks_w;
    unsigned short no_blks_h;
    unsigned char  *in_char;
    unsigned short *in_short;
    unsigned int   *outptr;
    unsigned int   *acc_v;
    unsigned int   *acc_h;
    int ok;
#ifdef REPORT
FILE* fpReport = fopen("../../../report.csv","a+");
#ifdef SCTM
unsigned int sctm_t1, sctm_t2, exec_diff;
unsigned int overflow;
EVE_SCTM_Enable(CTM);
EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);
#endif   
#endif
    /*---------------------------------------------------------------------*/
    /* This is the integral image processing loop, where tackle the IMAGE  */
    /* blocks first in the vertical direction, then in the horizontal      */
    /* direction, thus the inner loop, loops over the vertical blocks      */
    /* first, the outer loop, loops over the horizontal blocks.            */
    /*---------------------------------------------------------------------*/
    
    /*---------------------------------------------------------------------*/
    /* Clear the vertical accumulator array before beginning of each       */
    /* horizontal row of blocks. i.e., the left most block starts with     */
    /* an accumulator reset to zeros. Thus, for ONLY blocks with           */
    /* no_blks_w == 0, ACC_V is reset.                                     */
    /*---------------------------------------------------------------------*/
    
    reset_acc_mem(ACC_V, IN_H);
    
    
    /*---------------------------------------------------------------------*/
    /* Clear the horizontal accumulator array before begining of each      */
    /* vertical column of blocks. i.e., the top most block starts with     */
    /* an accumulator reset to zeros. Thus, for ALL blocks with            */
    /* no_blks_h == 0, ACC_H is reset.                                     */
    /*---------------------------------------------------------------------*/
     
    reset_acc_mem(ACC_H, IN_W);
    
    /*----------------------------------------------------------------------*/
    /*  Invoke the kernel implementation for the integral image             */
    /*  function which accepts input array 'in', accumulates                */
    /* row wise and then column wise and write out the result.              */
    /*----------------------------------------------------------------------*/
 #ifdef REPORT
#ifdef SCTM
sctm_t1 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
#endif
#endif   	   
    for ( no_blks_w = 0; no_blks_w < IN_W/BLOCK_WIDTH; no_blks_w++)
    {
        
        /*-----------------------------------------------------------------*/
        /* Set the horizontal accumulator to the correct location for      */
        /* horizontal block being processed.                               */
        /*-----------------------------------------------------------------*/
        
        acc_h          = ACC_H + (no_blks_w * BLOCK_WIDTH);
        
        /*-----------------------------------------------------------------*/
        /* We first process all the BLOCK_WIDTH * BLOCK_HEIGHT blocks      */
        /* going in the vertical direction of the image. This makes sure   */
        /* we use the correct accumulator and reuse memory as much as      */
        /* possible.                                                       */
        /*-----------------------------------------------------------------*/ 
        
        for ( no_blks_h = 0; no_blks_h < IN_H/BLOCK_HEIGHT; no_blks_h++)
        {
            
            acc_v       = ACC_V + (no_blks_h * BLOCK_HEIGHT);
            outptr      = out   + (no_blks_w * BLOCK_WIDTH)  + (no_blks_h * IN_W  * BLOCK_HEIGHT); 
            
            /*-------------------------------------------------------------*/
            /*  Invoke the kernel implementation for the integral image    */
            /*  function which accepts input array 'in', accumulates       */
            /* row wise and then column wise and write out the result.     */
            /*-------------------------------------------------------------*/  
            
            /*----------------------------------------------------------------------*/
            /* For input type of 'char' or 'uchar', we call the function            */
            /* eve_integral_image_char_int_int().                                   */
            /*----------------------------------------------------------------------*/
            
            if ( ((INPUT_TYPE == 0) || (INPUT_TYPE == 1) )&& ( INTER_TYPE == 2) && (OUTPUT_TYPE == 2))
            {
                
                in_char = (unsigned char *)A + (no_blks_w * BLOCK_WIDTH)  + (no_blks_h * IN_W  * BLOCK_HEIGHT);        
                
                eve_integral_image_u8_int_int
                ( 
                     BLOCK_WIDTH, 
                     BLOCK_HEIGHT, 
                     IN_W,
                     acc_h,
                     acc_v,
                     in_char,         
                     B0, 
                     B1, 
                     C0, 
                     C1, 
                     outptr,
                     acc_h
                ); 
            }
            
            /*----------------------------------------------------------------------*/
            /* For input type of 'short' or 'ushort', we call the function          */
            /* eve_integral_image_short_int_int().                                  */
            /*----------------------------------------------------------------------*/
            
            if ( ( (INPUT_TYPE == 2) || (INPUT_TYPE == 3)) && ( INTER_TYPE == 2) && (OUTPUT_TYPE == 2))
            {
                
               in_short = (unsigned short *) A + (no_blks_w * BLOCK_WIDTH)  + (no_blks_h * IN_W  * BLOCK_HEIGHT);          
                
                eve_integral_image_u16_int_int
                ( 
                     BLOCK_WIDTH, 
                     BLOCK_HEIGHT, 
                     IN_W,
                     acc_h,
                     acc_v,
                     in_short,         
                     B0, 
                     B1, 
                     C0, 
                     C1, 
                     outptr					 
                ); 
                            
            }
        }
    }
#ifdef REPORT	
#ifdef SCTM
sctm_t2 = EVE_SCTM_CounterRead (CTM, SCTM_Counter_0);
		overflow= EVE_SCTM_OverflowCheck(CTM,SCTM_Counter_0);
		assert(overflow!=1);

exec_diff = sctm_t2 - sctm_t1;		
EVE_SCTM_CounterTimerDisable(CTM, SCTM_Counter_0);
#endif			
#endif

#ifdef REPORT
fprintf(fpReport,"eve_image_varBlk,");
fprintf(fpReport,"%d,",IN_W);
fprintf(fpReport,"%d,",IN_H);
fprintf(fpReport,"%d,",IN_W);
fprintf(fpReport,"%d,",IN_H);
fprintf(fpReport,"1,");
#endif	        
   ok = print_verify_output();
	
 #ifdef CONSOLE		
    printf(ok ? "\n\nKernel-C result : PASS\n" : "FAIL\n"); 
#endif	
#ifdef REPORT   
if(ok){
fprintf(fpReport,"PASS,");
}
else{
fprintf(fpReport,"FAIL,");
}
#ifdef SCTM
fprintf(fpReport,"%d\n",exec_diff);
#endif
if(fpReport){
fclose(fpReport);
}
#endif
return 0;

}

int print_verify_output()
{
    int i, j, ok=1;

    for ( i = 0; i < IN_H; i++)
    {
        for ( j = 0; j < IN_W; j++)
        {
                if (EOut[(i * IN_W) + j] != out[(i * IN_W ) + j])
                {
#ifdef CONSOLE				
                	printf("ERROR: \noutput[%d] = %u\nreference[%d] = %d\n",
                	                    (i * IN_W ) + j, out[(i * IN_W ) + j], (i * IN_W ) + j, EOut[(i * IN_W) + j]); 
#endif										
                    ok = !ok;
                }
        }
    }
#ifdef CONSOLE	
    printf(ok ? "\n\nKernel-C result : PASS\n" : "FAIL\n");                 
#endif	
    
    return ok;
}


/*-------------------------------------------------------------------------*/
/* This is the routine to reset the accumulator array in memory.           */
/*-------------------------------------------------------------------------*/

void reset_acc_mem( Uint32 *in, int size)
{
    int i;

    for ( i = 0; i < size; i++)
        in[i] = 0;

    return;
} 


/* ======================================================================== */
/*  End of file:  eve_integral_image.c                                      */
/*--------------------------------------------------------------------------*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
        

