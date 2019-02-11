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
#include "VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u_idat.h"

static uint8_t    staticRefInput0[]=
{
    130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 255,   0, 128,
    128,   0, 255, 250, 240, 230, 220, 210, 200, 190, 180, 170, 160, 150, 140, 130
};

static uint8_t    staticRefOut0[]=
{
    174, 103, 151, 255, 194, 123, 171, 255, 255, 100, 255, 255, 255, 120, 255, 255, 255,  98, 255, 255, 255, 118, 255, 255, 250, 206, 255, 255,   0,  0,  225, 255,
    255,  84,   0, 255, 255, 211,  28, 255, 255, 146, 255, 255, 255, 126, 255, 255, 255, 148, 255, 255, 238, 128, 255, 255, 162, 151, 199, 255, 142, 131, 179, 255
};

static uint8_t    staticRefOut1[]=
{
    170, 123, 143, 255, 190, 143, 163, 255, 255, 121, 254, 255, 255, 141, 255, 255, 255, 118, 255, 255, 255, 138, 255, 255,  75, 255, 255, 255,   0, 177, 255, 255,
    178,   0,   0, 255, 255, 159, 250, 255, 255, 125, 255, 255, 255, 105, 255, 255, 255, 128, 255, 255, 242, 108, 255, 255, 166, 130, 206, 255, 146, 110, 186, 255
};


static colorConvert_YUVXtoRGBX_i8u_o8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn0,
           staticOut0,
           width, height, stride, x_value, src_space
        },
    *********************************************/
   {
        STATIC,
        staticRefInput0,
        staticRefOut0,
        8, 2, 8, 0, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        32, 16, 32, 0, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        64, 48, 64, 0, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        240, 320, 240, 0, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        640, 480, 640, 0, 2
    },
    {
        RANDOM,
        NULL,
        NULL,
        32, 16, 50, 0, 2
    },
    {
        RANDOM,
        NULL,
        NULL,
        64, 48, 100, 0, 2
    },
    {
        RANDOM,
        NULL,
        NULL,
        240, 320, 241, 0, 3
    },
    {
        RANDOM,
        NULL,
        NULL,
        640, 480, 642, 0, 3
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL,
        NULL,
        34, 2, 34, 0, 3
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL,
        NULL,
        34, 2, 38, 0, 3
    },
    { // Exercises branch where width%8 != 0, width != stride, less than nearest multiple of 8
        RANDOM,
        NULL,
        NULL,
        30, 2, 38, 0, 3
    },
    {
        STATIC,
        staticRefInput0,
        staticRefOut1,
        8, 2, 8, 1, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        32, 16, 32, 1, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        64, 48, 64, 1, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        240, 320, 240, 1, 1
    },
    {
        RANDOM,
        NULL,
        NULL,
        640, 480, 640, 1, 2
    },
    {
        RANDOM,
        NULL,
        NULL,
        32, 16, 50, 1, 2
    },
    {
        RANDOM,
        NULL,
        NULL,
        64, 48, 100, 1, 2
    },
    {
        RANDOM,
        NULL,
        NULL,
        240, 320, 241, 1, 2
    },
    {
        RANDOM,
        NULL,
        NULL,
        640, 480, 642, 1, 3
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL,
        NULL,
        34, 2, 34, 1, 3
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL,
        NULL,
        34, 2, 38, 1, 3
    },
    { // Exercises branch where width%8 != 0, width != stride, less than nearest multiple of 8
        RANDOM,
        NULL,
        NULL,
        30, 2, 38, 1, 3
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void colorConvert_YUVXtoRGBX_i8u_o8u_getTestParams(colorConvert_YUVXtoRGBX_i8u_o8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(colorConvert_YUVXtoRGBX_i8u_o8u_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

