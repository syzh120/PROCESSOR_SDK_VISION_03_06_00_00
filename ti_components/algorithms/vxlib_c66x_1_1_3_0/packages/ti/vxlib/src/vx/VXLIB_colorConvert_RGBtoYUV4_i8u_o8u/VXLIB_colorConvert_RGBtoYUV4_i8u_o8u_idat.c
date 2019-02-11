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
#include "VXLIB_colorConvert_RGBtoYUV4_i8u_o8u_idat.h"

    /*
    Y'= 0.2126*R' + 0.7152*G' + 0.0722*B'
    U'=-0.1146*R' - 0.3854*G' + 0.5000*B'
    V'= 0.5000*R' - 0.4542*G' - 0.0458*B'
    */
static uint8_t    staticRefInput[]=
{
    10, 20, 30, 40, 50, 60, 70, 80, 10, 20, 30, 40, 50, 60, 70, 80, 10, 20, 30, 40, 50, 60, 70, 80,
    10, 20, 30, 40, 50, 60, 70, 80, 10, 20, 30, 40, 50, 60, 70, 80, 10, 20, 30, 40, 50, 0,  0, 255
};

static uint8_t    staticRefOut0[]=
{
    19, 48, 73, 28, 58, 25, 38, 68,
    19, 48, 73, 28, 58, 25, 38, 18
};

static uint8_t    staticRefOut1[]=
{
    134, 134, 94, 134, 134, 125, 134, 134,
    134, 134, 94, 134, 134, 125, 134, 255
};

static uint8_t    staticRefOut2[]=
{
    123, 123, 126, 123, 123, 163, 123, 123,
    123, 123, 126, 123, 123, 163, 123, 116
};

static colorConvert_RGBtoYUV4_i8u_o8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn0,
           staticOut0, staticOut1, staticOut2, 
           width, height, stride
        },
    *********************************************/
    {
        STATIC,
        staticRefInput,
        staticRefOut0, staticRefOut1, staticRefOut2,
        8, 2, 8
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        32, 16, 32
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        64, 48, 64
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        240, 320, 240
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        640, 480, 640
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        32, 16, 50
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        64, 48, 100
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        240, 320, 241
    },
    {
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        640, 480, 642
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        34, 2, 34
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        34, 2, 38
    },
    { // Exercises branch where width%8 != 0, width != stride, less than nearest multiple of 8
        RANDOM,
        NULL,
        NULL, NULL, NULL,
        15, 2, 19
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void colorConvert_RGBtoYUV4_i8u_o8u_getTestParams(colorConvert_RGBtoYUV4_i8u_o8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(colorConvert_RGBtoYUV4_i8u_o8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

