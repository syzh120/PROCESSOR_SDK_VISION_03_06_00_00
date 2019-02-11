/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2016 - 2017 Texas Instruments Incorporated         |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
 *******************************************************************************/
#include "../../common/TI_memory.h"
#include "VXLIB_remapNearest_bc_i8u_i32f_o8u_idat.h"


static uint8_t    staticRefInput[]=
{
   255,  1,  2,  3, 8, 9, 10, 11,
    12, 13, 14, 15, 4, 5,  6,  7,
};

/* Copy = Direct Mapping */
static float    staticRefRemap1[]=
{
    0,0, 1,0, 2,0, 3,0, 4,0, 5,0, 6,0, 7,0,
    0,1, 1,1, 2,1, 3,1, 4,1, 5,1, 6,1, 7,1
};

static uint8_t    staticRefOut1[]=
{
   255,  1,  2,  3, 8, 9, 10, 11,
    12, 13, 14, 15, 4, 5,  6,  7,
};

/* Test out of bounds and rounding */
static float    staticRefRemap2[]=
{
    -2.0f,0,   -0.55f,0,   -0.45f,0,   2.3f,0.6f,   2.7f,1.4f,   7.4f,0,   7.6f,0,   8.2f,0,
    0,-2.0f,   0,-0.55f,   0,-0.45f,   3.8f,0.1f,   3.3f,0.3f,   0,1.4f,   0,1.6f,   0,2.2f
};

static uint8_t    staticRefOut2[]=
{
     0,  0, 255, 14, 15, 11, 0, 0,
     0,  0, 255,  8,  3, 12, 0, 0,
};

/* Must choose dimension such that there are at least 255 entries for LUT */
static remapNearest_bc_i8u_i32f_o8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, staticInRemap, staticOut
           srcWidth, srcHeight, srcStride,
           dstWidth, dstHeight, dstStride, borderValue
        },
    *********************************************/
    {
        STATIC,
        staticRefInput, staticRefRemap1, staticRefOut1,
        8, 2, 8,
        8, 2, 8, 0
    },
    {
        STATIC,
        staticRefInput, staticRefRemap2, staticRefOut2,
        8, 2, 8,
        8, 2, 8, 0
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 32,
        32, 16, 32, 1
    },
    { // src width != dst width && src stride != dst stride
        RANDOM,
        NULL, NULL, NULL,
        68, 48, 68,
        64, 48, 64, 2
    },
    { // src stride != src width
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 243,
        240, 320, 240, 127
    },
    { // src width != dst width && src stride != dst stride && src stride != src width
        RANDOM,
        NULL, NULL, NULL,
        641, 480, 643,
        640, 480, 640, 128
    },
    { // Exercises branch where width%4 != 0, width == stride
        RANDOM,
        NULL, NULL, NULL,
        17, 8, 17,
        17, 8, 17, 255
    },
    { // Exercises branch where width%4 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        33, 8, 35,
        33, 8, 35, 0
    },
    { // Exercises branch where width%4 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        31, 16, 35,
        31, 16, 35, 1
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 41,
        32, 16, 41, 255
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48, 71,
        64, 48, 71, 5
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 242,
        240, 320, 242, 100
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480, 642,
        640, 480, 642, 80
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void remapNearest_bc_i8u_i32f_o8u_getTestParams(remapNearest_bc_i8u_i32f_o8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(remapNearest_bc_i8u_i32f_o8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
