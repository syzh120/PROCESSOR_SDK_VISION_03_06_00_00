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
#include "../../common/VXLIB_types.h"
#include "VXLIB_harrisCornersScore_i32s_i32s_o32f_idat.h"


static int32_t    staticRefInputX[]=
{
    0, 24480,  -24480,  12240,  100,    5,  800, -4000,
    0, 24480,  0x8000, -12240,  -20,  100,  200, -1000,
    0, 24480,  -24480,  12240,  100,    5,  800, -4000,
    0, 24480,  0x8000, -12240,  -20,  100,  200, -1000
};

static int32_t    staticRefInputY[]=
{
    0,     0,       0, -12240,  -20,  100,  200, -1000,
    0, 24480,  0x8000,  12240,  100,    5,  800, -4000,
    0,     0,       0, -12240,  -20,  100,  200, -1000,
    0, 24480,  0x8000,  12240,  100,    5,  800, -4000
};

static float    staticRefOut[]=
{
    -10688.5886f,  16857.7143f, 12011.2387f, -1382.3205f,  0.0014319359f,  0.74242051457f,
    -60778.3582f, -11676.1519f,  4368.5355f, -1382.3205f,  0.0014319359f,  0.74242051457f
};

static harrisCornersScore_i32s_i32s_o32f_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInX, *staticInY, staticOut,
           width_in, height_in, width_out, height_out, stride_in, stride_out, sensitivity, gradient_size, block_size
        },
    *********************************************/
    {
        STATIC,
        staticRefInputX, staticRefInputY, staticRefOut,
        8, 4,       6, 2,       8*4, 6*4,     0.15f, 3, 3
    },
    /* Fast, mode 1 */
    {
        RANDOM,
        NULL, NULL, NULL,
        16, 8,      16, 4,       16*4, 16*4,     0.15f, 3, 5
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16,     32, 10,     32*4, 32*4,     0.10f, 3, 7
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48,     64, 46,     64*4, 64*4,     0.04f, 5, 3
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 240,   320, 236,   320*4, 320*4,     0.15f, 5, 5
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480,   640, 474,   640*4, 640*4,     0.10f, 5, 7
    },
    /* mode 2 */
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16,     32, 14,     100*4, 32*4,     0.04f, 3, 3    /* in stride != in width */
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48,     61, 46,     64*4, 64*4,     0.15f, 7, 3      /* out width != in width */
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320,   230, 316,   240*4, 230*4,     0.10f, 7, 5    /* out width != in width && out stride != in stride */
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480,   640, 474,   640*4, 641*4,     0.04f, 7, 7   /* out stride != out width */
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void harrisCornersScore_i32s_i32s_o32f_getTestParams(harrisCornersScore_i32s_i32s_o32f_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(harrisCornersScore_i32s_i32s_o32f_testParams_t);
}

