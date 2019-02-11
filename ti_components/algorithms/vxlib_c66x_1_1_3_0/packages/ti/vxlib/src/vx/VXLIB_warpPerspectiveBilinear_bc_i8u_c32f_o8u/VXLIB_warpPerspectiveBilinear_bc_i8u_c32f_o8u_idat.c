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
#include "VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u_idat.h"

static uint8_t    staticRefInput[]=
{
    1,  2,  3,  4,  5,  6,  7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32
};

static uint8_t    staticRefOutRotate45[]=
{
    11, 23, 18, 13,  8,  4,  1,  0,
     0, 15, 25, 20, 15, 10,  5,  1,
     0,  0, 16, 26, 21, 16, 11,  6,
     0,  0,  0, 17, 27, 22, 17, 13
};


static float    matrixPassthru[]=
{
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
};

static float    matrixRotate45[]=
{
    0.707106781f, -0.707106781f, 0.0f,
    0.707106781f, 0.707106781f,  0.0f,
    0.0f, 0.0f, 1.0f
};

static warpPerspectiveBilinear_bc_i8u_c32f_o8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, warpMatrixIn, staticOut,
           srcWidth, srcHeight, srcStride,
           dstWidth, dstHeight, dstStride, borderValue

        },
    *********************************************/
    {
        STATIC,
        staticRefInput, matrixPassthru, staticRefInput, 
        8, 4, 8,
        8, 4, 8, 0
    },
    {
        STATIC,
        staticRefInput, matrixRotate45, staticRefOutRotate45,
        8, 4, 8,
        8, 4, 8, 0
    },
    {
        RANDOM,
        NULL, matrixRotate45, NULL,
        32, 16, 32,
        32, 16, 32, 1
    },
    { // src width != dst width && src stride != dst stride
        RANDOM,
        NULL, matrixRotate45, NULL,
        68, 48, 68,
        64, 48, 64, 2
    },
    { // src stride != src width
        RANDOM,
        NULL, matrixRotate45, NULL,
        240, 320, 243,
        240, 320, 240, 127
    },
    { // src width != dst width && src stride != dst stride && src stride != src width
        RANDOM,
        NULL, matrixRotate45, NULL,
        641, 480, 643,
        640, 480, 640, 128
    },
    { // Exercises branch where width%4 != 0, width == stride
        RANDOM,
        NULL, matrixRotate45, NULL,
        17, 8, 17,
        17, 8, 17, 255
    },
    { // Exercises branch where width%4 != 0, width != stride
        RANDOM,
        NULL, matrixRotate45, NULL,
        33, 8, 35,
        33, 8, 35, 0
    },
    { // Exercises branch where width%4 != 0, width != stride
        RANDOM,
        NULL, matrixRotate45, NULL,
        31, 16, 35,
        31, 16, 35, 1
    },
    {
        RANDOM,
        NULL, matrixRotate45, NULL,
        32, 16, 41,
        32, 16, 41, 255
    },
    {
        RANDOM,
        NULL, matrixRotate45, NULL,
        64, 48, 71,
        64, 48, 71, 5
    },
    {
        RANDOM,
        NULL, matrixRotate45, NULL,
        240, 320, 242,
        240, 320, 242, 100
    },
    {
        RANDOM,
        NULL, matrixRotate45, NULL,
        640, 480, 642,
        640, 480, 642, 80
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void warpPerspectiveBilinear_bc_i8u_c32f_o8u_getTestParams(warpPerspectiveBilinear_bc_i8u_c32f_o8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(warpPerspectiveBilinear_bc_i8u_c32f_o8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

