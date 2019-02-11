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
#include "VXLIB_channelCombine_4to1_i8u_o8u_idat.h"


static uint8_t    staticRefInput0[]=
{
    1,  5,  9,  13, 17, 21, 25, 29,
    33, 37, 41, 45, 49, 53, 57, 61
};

static uint8_t    staticRefInput1[]=
{
     2,  6, 10, 14, 18, 22, 26, 30,
    34, 38, 42, 46, 50, 54, 58, 62
};

static uint8_t    staticRefInput2[]=
{
     3,  7, 11, 15, 19, 23, 27, 31,
    35, 39, 43, 47, 51, 55, 59, 63
};

static uint8_t    staticRefInput3[]=
{
     4,  8, 12, 16, 20, 24, 28, 32,
    36, 40, 44, 48, 52, 56, 60, 64
};

static uint8_t    staticRefOut[]=
{
    1,  2,  3,  4,  5,  6,  7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 52, 53, 54, 55, 56,
    57, 58, 59, 60, 61, 62, 63, 64
};

static channelCombine_4to1_i8u_o8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn0, *staticIn1, *staticIn2, *staticIn3, staticOut
           width, height, stride_8, stride_32
        },
    *********************************************/
    {
        STATIC,
        staticRefInput0, staticRefInput1, staticRefInput2, staticRefInput3, staticRefOut,
        8, 2, 8, 32
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        32, 16, 32, 128
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        64, 48, 64, 256
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        240, 320, 240, 960
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        640, 480, 640, 2560
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        32, 16, 100, 400
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        64, 48, 100, 400
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        240, 320, 241, 964
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        640, 480, 642, 2568
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        17, 2, 17, 68
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        17, 2, 19, 93
    },
    { // Exercises branch where width%8 != 0, width != stride, less than nearest multiple of 8
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        15, 2, 19, 80
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void channelCombine_4to1_i8u_o8u_getTestParams(channelCombine_4to1_i8u_o8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(channelCombine_4to1_i8u_o8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

