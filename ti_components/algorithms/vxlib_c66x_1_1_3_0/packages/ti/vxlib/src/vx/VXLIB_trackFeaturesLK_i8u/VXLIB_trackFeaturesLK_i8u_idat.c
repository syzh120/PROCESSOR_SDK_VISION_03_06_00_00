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
#include "VXLIB_trackFeaturesLK_i8u_idat.h"


static float oldPoints[16]         = { 15.3f, 14.7f, 
                                         25.2f, 32.9f, 
                                         49.0f, 32.1f,
                                         20.2f, 40.9f,
                                          8.2f, 13.2f,
                                          6.2f,  9.2f,
                                         10.0f, 20.0f,
                                         16.0f, 16.0f };

static float newPoints5x5[16]      = { 16.30f,   15.6999f, 
                                         44.796f,  62.4777f,
                                         47.5147f, 32.49766f,
                                         21.1973f, 41.89944f,
                                         10.1f,    15.1f,
                                          7.2015f, 10.1996f,
                                         11.0356f, 20.9973f,
                                         17.0009f, 17.0009f };

static float newPoints7x7[16]      = { 16.30f,   15.6999f, 
                                         53.2213f, 54.9832f,
                                         48.1424f, 32.3945f,
                                         21.1973f, 41.89944f,
                                         10.199f,  14.198f,
                                          7.199f,  10.1989f,
                                         11.0356f, 20.9973f,
                                         17.0009f, 17.0009f };

static float newPoints9x9[16]      = { 16.30f,   15.6999f, 
                                         50.660f,  44.3429f,
                                         48.6963f, 32.3457f,
                                         21.1973f, 41.89944f,
                                          9.205f,  14.1974f,
                                          7.2015f, 10.1996f,
                                         11.0356f, 20.9973f,
                                         17.0009f, 17.0009f };

static uint8_t    oldStatus[8]   = { 1, 1, 1, 1, 1, 1, 1, 1 };
static uint8_t    newStatus[8]   = { 1, 1, 1, 1, 1, 1, 1, 1 };

static float estPoints[16]          = { 16.0f, 15.7f, 
                                         25.5f, 33.3f, 
                                         49.5f, 32.8f,
                                         20.7f, 41.5f,
                                         10.1f, 15.1f,
                                          8.1f, 11.2f,
                                         10.0f, 20.0f,
                                         16.0f, 16.0f };

static trackFeaturesLK_i8u_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInOld, *staticInNew,
           *staticOldPoints, *staticNewPoints, *staticEstPoints,
           *staticOldStatus, *staticNewStatus,
           width, height, stride, num_points,
           max_iters, epsilon, scale, window_size, level, termination
        },
    *********************************************/
    {
        CUSTOM,
        NULL, NULL,
        oldPoints, newPoints5x5, estPoints,
        oldStatus, newStatus,
        64, 64, 64, 8,
        10, 0.0001f, 1.f, 5, 1, VXLIB_TERM_ITERATIONS
    },

    {
        CUSTOM,
        NULL, NULL,
        oldPoints, newPoints7x7, estPoints,
        oldStatus, newStatus,
        64, 64, 64, 8,
        10, 0.0001f, 1.f, 7, 1, VXLIB_TERM_ITERATIONS
    },
    {
        CUSTOM,
        NULL, NULL,
        oldPoints, newPoints9x9, estPoints,
        oldStatus, newStatus,
        64, 64, 64, 8,
        10, 0.0001f, 1.f, 9, 1, VXLIB_TERM_ITERATIONS
    },
    {
        CUSTOM,
        NULL, NULL,
        oldPoints, newPoints5x5, estPoints,
        oldStatus, newStatus,
        64, 64, 64, 8,
        12, 0.0001f, 1.f, 5, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        64, 64, 64, 8,
        12, 0.0001f, 1.f, 7, 0, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        64, 64, 64, 8,
        12, 0.0001f, 1.f, 9, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        176, 144, 176, 6,
        6, 0.0001f, 1.f, 5, 1, VXLIB_TERM_ITERATIONS
    },
    {
        SEQUENTIAL,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        80, 80, 80, 6,
        8, 0.0001f, 1.f, 7, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        81, 81, 81, 5,
        4, 0.0001f, 1.f, 9, 1, VXLIB_TERM_ITERATIONS
    },

    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        181, 181, 181, 6,
        8, 0.0001f, 1.f, 5, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        181, 181, 181, 6,
        9, 0.0001f, 1.f, 7, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        320, 240, 320, 5,
        12, 0.0001f, 1.f, 9, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        320, 240, 320, 5,
        9, 0.0001f, 1.f, 5, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        320, 240, 320, 8,
        9, 0.0001f, 1.f, 7, 1, VXLIB_TERM_ITERATIONS
    },
    {
        RANDOM,
        NULL, NULL,
        oldPoints, NULL, NULL,
        oldStatus, NULL,
        320, 240, 320, 8,
        9, 0.0001f, 1.f, 9, 1, VXLIB_TERM_ITERATIONS
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void trackFeaturesLK_i8u_getTestParams(trackFeaturesLK_i8u_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(trackFeaturesLK_i8u_testParams_t);
}

