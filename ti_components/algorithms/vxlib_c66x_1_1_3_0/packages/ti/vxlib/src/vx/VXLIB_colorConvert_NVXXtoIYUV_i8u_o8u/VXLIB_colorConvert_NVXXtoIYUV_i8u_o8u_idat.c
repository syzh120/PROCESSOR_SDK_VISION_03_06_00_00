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
#include "VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u_idat.h"

static uint8_t    staticRefInput0[]=
{
    18, 48, 72, 28, 58, 25, 38, 68,
    18, 48, 72, 28, 58, 25, 38, 68
};

static uint8_t    staticRefInput1[]=
{
    10, 20, 30, 40, 50, 60, 70, 80
};

static uint8_t    staticRefOut0[]=
{
    18, 48, 72, 28, 58, 25, 38, 68,
    18, 48, 72, 28, 58, 25, 38, 68
};

static uint8_t    staticRefOut1[]=
{
    10, 30, 50, 70,
};

static uint8_t    staticRefOut2[]=
{
    20, 40, 60, 80
};

static colorConvert_NVXXtoIYUV_i8u_o8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn0, *staticIn1, 
           staticOut0, staticOut1, staticOut2, 
           width, height, stride, u_pix
        },
    *********************************************/
   {
        STATIC,
        staticRefInput0, staticRefInput1,
        staticRefOut0, staticRefOut1, staticRefOut2,
        8, 2, 8, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        32, 16, 32, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        64, 48, 64, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        240, 320, 240, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        640, 480, 640, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        32, 16, 50, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        64, 48, 100, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        240, 320, 241, 0
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        640, 480, 642, 0
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        34, 2, 34, 0
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        34, 2, 38, 0
    },
    { // Exercises branch where width%8 != 0, width != stride, less than nearest multiple of 8
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        30, 2, 38, 0
    },
    {
        STATIC,
        staticRefInput0, staticRefInput1,
        staticRefOut0, staticRefOut2, staticRefOut1,
        8, 2, 8, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        32, 16, 32, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        64, 48, 64, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        240, 320, 240, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        640, 480, 640, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        32, 16, 50, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        64, 48, 100, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        240, 320, 241, 1
    },
    {
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        640, 480, 642, 1
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        34, 2, 34, 1
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        34, 2, 38, 1
    },
    { // Exercises branch where width%8 != 0, width != stride, less than nearest multiple of 8
        RANDOM,
        NULL, NULL,
        NULL, NULL, NULL,
        30, 2, 38, 1
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void colorConvert_NVXXtoIYUV_i8u_o8u_getTestParams(colorConvert_NVXXtoIYUV_i8u_o8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(colorConvert_NVXXtoIYUV_i8u_o8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

