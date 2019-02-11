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
#include "VXLIB_minMaxLoc_i8u_idat.h"


static uint8_t    staticRefInput[]=
{
    1,  2,  3, 16,  5,  6,  7, 8,
    9, 10, 11, 12,  1, 14, 15, 16
};

static uint8_t    staticPminVal[]=
{
    1
};

static uint8_t    staticPmaxVal[]=
{
    16
};

static uint32_t    staticPminCount[]=
{
    2
};

static uint32_t    staticPmaxCount[]=
{
    2
};

static uint32_t    staticMinLoc[]=
{
    0,  0,  4,  1,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0
};

static uint32_t    staticMaxLoc[]=
{
    3,  0,  7,  1,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0
};

static minMaxLoc_i8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn,
           width, height, stride,
           minLocCapacity, maxLocCapacity,
           *pMinVal, *pMaxVal,
           *pMinCount, *pMaxCount,
           *minLoc, *maxLoc, mode
        },
    *********************************************/
    {
        STATIC,
        staticRefInput,
        8, 2, 8, 16, 16,
        staticPminVal, staticPmaxVal,
        staticPminCount, staticPmaxCount,
        staticMinLoc, staticMaxLoc, 3
    },
    {
        RANDOM,
        NULL,
        32, 16, 32, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 1
    },
    {
        RANDOM,
        NULL,
        32, 16, 32, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 2
    },
    {
        RANDOM,
        NULL,
        32, 16, 32, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    {
        RANDOM,
        NULL,
        64, 48, 64, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 1
    },
    {
        RANDOM,
        NULL,
        64, 48, 64, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 2
    },
    {
        RANDOM,
        NULL,
        64, 48, 64, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    {
        RANDOM,
        NULL,
        240, 320, 240, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    {
        RANDOM,
        NULL,
        640, 480, 640, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    {
        RANDOM,
        NULL,
        8, 2, 9, 16, 16,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 1
    },
    {
        RANDOM,
        NULL,
        8, 2, 9, 16, 16,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 2
    },
    {
        RANDOM,
        NULL,
        32, 16, 50, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 1
    },
    {
        RANDOM,
        NULL,
        32, 16, 50, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 2
    },
    {
        RANDOM,
        NULL,
        32, 16, 50, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    {
        RANDOM,
        NULL,
        64, 48, 100, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 1
    },
    {
        RANDOM,
        NULL,
        64, 48, 100, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 2
    },
    {
        RANDOM,
        NULL,
        64, 48, 100, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    {
        RANDOM,
        NULL,
        240, 320, 241, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 1
    },
    {
        RANDOM,
        NULL,
        240, 320, 241, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 2
    },
    {
        RANDOM,
        NULL,
        240, 320, 241, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    {
        RANDOM,
        NULL,
        640, 480, 642, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL,
        17, 8, 17, 17*8, 17*8,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL,
        33, 8, 35, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL,
        31, 16, 35, 300, 300,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL, 3
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void minMaxLoc_i8u_getTestParams(minMaxLoc_i8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(minMaxLoc_i8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

