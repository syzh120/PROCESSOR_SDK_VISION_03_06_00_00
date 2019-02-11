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
#include "VXLIB_sobel_7x7_i8u_o16s_o16s_idat.h"


#if 0 /* Sequential input */
static uint8_t    staticRefInput[]=
{
    0,  1,  2,  3,  4,  5,  6,  7,
    8,  9, 10 ,11, 12, 13, 14, 15,
   16, 17, 18, 19, 20, 21, 22, 23,
   24, 25, 26, 27, 28, 29, 30, 31,
   32, 33, 34, 35, 36, 37, 38, 39,
   40, 41, 42, 43, 44, 45, 46, 47,
   48, 49, 50, 51, 52, 53, 54, 55,
   56, 57, 58, 59, 60, 61, 62, 63
};
#endif

static int16_t    staticRefOutX[]=
{
   2048, 2048,
   2048, 2048,
};

static int16_t    staticRefOutY[]=
{
   16384, 16384,
   16384, 16384,
};


static sobel_7x7_i8u_o16s_o16s_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOutX, *staticOutY, 
           width_in, height_in, width_out, height_out, stride_in, stride_out
        },
    *********************************************/
    {
        SEQUENTIAL,
        NULL, staticRefOutX, staticRefOutY,
        8, 8,       2, 2,       8, 2*2,
    },
    /* Fast, mode 1 */
    {
        RANDOM,
        NULL, NULL, NULL,
        16, 8,     16, 2,       16, 16*2,
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16,     32, 10,     32, 32*4,
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48,     64, 42,     64, 64*2,
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 240,   320, 234,   320, 320*2,
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480,   640, 474,   640, 640*2,
    },
    /* mode 2 */
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16,     32, 10,     100, 32*2,    /* in stride != in width */
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48,     58, 42,     64, 64*2,      /* out width != in width */
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320,   230, 314,   240, 230*2,    /* out width != in width && out stride != in stride */
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480,   640, 474,   640, 641*2,    /* out stride != out width */
    },
};
/*
 *  Sends the test parameter structure and number of tests
 */
void sobel_7x7_i8u_o16s_o16s_getTestParams(sobel_7x7_i8u_o16s_o16s_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(sobel_7x7_i8u_o16s_o16s_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

