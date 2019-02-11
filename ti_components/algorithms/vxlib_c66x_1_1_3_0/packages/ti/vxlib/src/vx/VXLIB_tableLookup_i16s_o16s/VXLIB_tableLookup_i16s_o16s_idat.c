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
#include "VXLIB_tableLookup_i16s_o16s_idat.h"


static int16_t    staticRefInput0[]=
{
    -4, -3, -2, -1, 8, 9, 10, 11,
    0, 1, 2, 3, 4, 5,  6,  7,
};

static int16_t    staticRefInput1[]=
{
    1, 10, 20, 16,  8, 12, 14, -4,
    2, -18, 24, -36, 40, 48, -44, 23
};

static int16_t    staticRefOut[]=
{
     1, 10, 20, 16, 40, 48, -44, 23,
    8, 12, 14, -4, 2, -18, 24, -36
};

/* Must choose dimension such that there are at least 255 entries for LUT */
static tableLookup_i16s_o16s_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn0, staticIn1, staticOut
           width, height, stride, count, offset
        },
    *********************************************/
    {
        STATIC,
        staticRefInput0, staticRefInput1, staticRefOut,
        8, 2, 16, 16, 4
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 64, 256, 0
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48, 128, 0x10000, 0
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 480, 256, 128
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480, 1280, 0x10000, 0x8000
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL, NULL, NULL,
        17, 8, 34, 256, 0
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        33, 8, 70, 256, 0
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        31, 16, 70, 256, 0
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 82, 6000, 25
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48, 142, 6000, 5000
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 484, 0x10000, 25000
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480, 1284, 899, 0
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void tableLookup_i16s_o16s_getTestParams(tableLookup_i16s_o16s_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(tableLookup_i16s_o16s_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

