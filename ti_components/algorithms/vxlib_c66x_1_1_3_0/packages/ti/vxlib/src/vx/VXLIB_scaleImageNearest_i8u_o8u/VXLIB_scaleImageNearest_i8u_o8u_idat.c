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
#include "VXLIB_scaleImageNearest_i8u_o8u_idat.h"

static uint8_t    staticRefInput[]=
{
    1,  2,  3,  4,  5,  6,  7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32
};

static uint8_t    staticRefOutBy1[]=
{
    1,  2,  3,  4,  5,  6,  7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32
};

static uint8_t    staticRefOutBy2[]=
{
     1,  3,  5,  7,
    17, 19, 21, 23,
};

static scaleImageNearest_i8u_o8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, staticOut,
           srcWidth, srcHeight, srcStride,
           dstWidth, dstHeight, dstStride

        },
    *********************************************/
    {
        STATIC,
        staticRefInput, staticRefOutBy1, 
        8, 4, 8,
        8, 4, 8
    },
    {
        STATIC,
        staticRefInput, staticRefOutBy2,
        8, 4, 8,
        4, 2, 4
    },
    {
        RANDOM,
        NULL, NULL,
        36, 20, 36,     // scale(x, y) = 1.125, 1.25
        32, 16, 32
    },
    {
        RANDOM,
        NULL, NULL,
        25, 15, 25,     // scale(x, y) = 0.390625, 0.3125
        64, 48, 64
    },
    {
        RANDOM,
        NULL, NULL,
        185, 555, 185,  // scale(x, y) = 0.7708, 1.734
        240, 320, 240
    },
    {
        RANDOM,
        NULL, NULL,
        115, 92, 115,  // scale(x, y) = 0.1797, 0.1917
        640, 480, 640
    },
    { // Exercises branch where width%4 != 0, width == stride
        RANDOM,
        NULL, NULL,
        17, 8, 17,
        17, 8, 17
    },
    { // Exercises branch where width%4 != 0, width != stride
        RANDOM,
        NULL, NULL,
        33, 8, 35,
        33, 8, 35
    },
    { // Exercises branch where width%4 != 0, width != stride
        RANDOM,
        NULL, NULL,
        31, 16, 35,
        31, 16, 35
    },
    {
        RANDOM,
        NULL, NULL,
        350, 251, 351,  // scale(x, y) = 10.9375, 15.6875
        32, 16, 41
    },
    {
        RANDOM,
        NULL, NULL,
        401, 12, 414,  // scale(x, y) = 6.265625, 0.25
        64, 48, 71
    },
    {
        RANDOM,
        NULL, NULL,
        480, 640, 482,   // scale(x, y) = 2, 2
        240, 320, 242
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240, 324,  // scale(x, y) = 0.5, 0.5
        640, 480, 642
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void scaleImageNearest_i8u_o8u_getTestParams(scaleImageNearest_i8u_o8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(scaleImageNearest_i8u_o8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

