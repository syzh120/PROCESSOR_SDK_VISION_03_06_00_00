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
#include "VXLIB_harrisCornersNMS_i32f_idat.h"

static float    staticRefInput[]=
{
       4.8f,   1.0f,     1.1f,   0.0f,
       0.0f,   5.0f,     4.0f,   0.0f,
       4.9f,   3.0f,   -12.0f,   0.0f,
       0.0f,   0.0f,     0.0f,   0.0f,
};

static uint16_t    staticRefOutput[]=
{
    1, 1
};

static float    staticRefStr[]=
{
    5.0f
};

static uint32_t    staticNumCorners[]=
{
    1
};

static harrisCornersNMS_i32f_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut, *staticOutStr, *num_corners,
           width, height, stride, corners_capacity,
           strength_thresh, min_distance
        },
    *********************************************/
    {
        STATIC,
        staticRefInput, staticRefOutput, staticRefStr, staticNumCorners,
        4, 4, 4*4, 1,
        4.3f, 30.0f
    },

    /* Strides == widths */
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        16, 16, 16*4, ((16-2)*(16-2))/8,
        0.04f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        32, 16, 32*4, ((32-2)*(16-2))/8,
        0.04f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        64, 48, 64*4, ((64-2)*(48-2))/8,
        2.0f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        128, 22, 128*4, ((128-2)*(22-2))/8,
        4.0f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        240, 320, 240*4, ((240-2)*(320-2))/8,
        12.6f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        640, 480, 640*4, ((640-2)*(480-2))/8,
        8.324f, 30.0f
    },
    /* Strides > Widths */
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        32, 16, 35*4, ((32-2)*(16-2))/8,
        1.23f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        65, 48, 70*4, ((64-2)*(48-2))/8,
        3.666f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        240, 320, 242*4, ((240-2)*(320-2))/8,
        15.852f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        641, 200, 643*4, ((640-2)*(200-2))/8,
        4.333f, 30.0f
    },
    /* Test capacity limit */
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        32, 16, 32*4, 2,
        0.05f, 30.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL,
        32, 16, 32*4, 1,
        0.25f, 30.0f
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void harrisCornersNMS_i32f_getTestParams(harrisCornersNMS_i32f_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(harrisCornersNMS_i32f_testParams_t);
}

