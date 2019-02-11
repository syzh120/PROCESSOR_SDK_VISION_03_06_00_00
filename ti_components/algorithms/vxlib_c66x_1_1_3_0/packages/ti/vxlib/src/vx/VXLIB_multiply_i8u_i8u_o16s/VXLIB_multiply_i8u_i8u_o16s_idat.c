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
#include "VXLIB_multiply_i8u_i8u_o16s_idat.h"


static uint8_t    staticRefInput0[]=
{
    1,  2,  3,  4,  5,  6,  7, 8,
    9, 10, 11, 12, 13, 14, 15, 16
};

static uint8_t    staticRefInput1[]=
{
    8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8
};

static int16_t    staticRefOut[]=
{
    8, 16, 24, 32, 40, 48, 56, 64,
    72, 80, 88, 96, 104, 112, 120, 128
};

static int16_t    staticRefOutConstWrap[]=
{
    0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01,
    0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01, 0xfe01
};

static int16_t    staticRefOutConstSat[]=
{
    0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff,
    0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff, 0x7fff,
};

static multiply_i8u_i8u_o16s_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn0, staticIn1, staticOut
           width, height, stride, overflow, scale
        },
    *********************************************/
    {
        STATIC,
        staticRefInput0, staticRefInput1, staticRefOut,
        8, 2, 8, VXLIB_CONVERT_POLICY_WRAP, 1.0f
    },
    {
        CONSTANT,
        NULL, NULL, staticRefOutConstWrap,
        8, 2, 8, VXLIB_CONVERT_POLICY_WRAP, 1.0f
    },
    {
        CONSTANT,
        NULL, NULL, staticRefOutConstSat,
        8, 2, 8, VXLIB_CONVERT_POLICY_SATURATE, 1.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 32, VXLIB_CONVERT_POLICY_WRAP, 1.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 240, VXLIB_CONVERT_POLICY_WRAP, (1.0f/255)
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480, 640, VXLIB_CONVERT_POLICY_WRAP, 1.3f
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 50, VXLIB_CONVERT_POLICY_WRAP, (1.0f/(1<<15))
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48, 100, VXLIB_CONVERT_POLICY_WRAP, (1.0f/(1<<14))
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 241, VXLIB_CONVERT_POLICY_WRAP, (1.0f/(1<<13))
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480, 642, VXLIB_CONVERT_POLICY_WRAP, (1.0f/(1<<12))
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 17, VXLIB_CONVERT_POLICY_WRAP, (1.0f/(1<<11))
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 19, VXLIB_CONVERT_POLICY_WRAP, 1.0f
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 19, VXLIB_CONVERT_POLICY_WRAP, (1.0f/(1<<10))
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 19, VXLIB_CONVERT_POLICY_WRAP, (1.0f/(1<<9))
    },
    {
        STATIC,
        staticRefInput0, staticRefInput1, staticRefOut,
        8, 2, 8, VXLIB_CONVERT_POLICY_SATURATE, 1.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480, 642, VXLIB_CONVERT_POLICY_SATURATE, (1.0f/(1<<8))
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 241, VXLIB_CONVERT_POLICY_SATURATE, 1.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48, 100, VXLIB_CONVERT_POLICY_SATURATE, (1.0f/(1<<7))
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 48, 100, VXLIB_CONVERT_POLICY_SATURATE, (0.96f)
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 50, VXLIB_CONVERT_POLICY_SATURATE, (1.0f/(1<<5))
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        640, 480, 640, VXLIB_CONVERT_POLICY_SATURATE, 3.0f
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        240, 320, 240, VXLIB_CONVERT_POLICY_SATURATE, (1.0f/(1<<4))
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        32, 16, 32, VXLIB_CONVERT_POLICY_SATURATE, 1.0f
    },
    { // Exercises branch where width%8 != 0, width == stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 17, VXLIB_CONVERT_POLICY_SATURATE, 0.55f
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 19, VXLIB_CONVERT_POLICY_SATURATE, 1.0f
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 19, VXLIB_CONVERT_POLICY_SATURATE, (1.0f/(1<<3))
    },
    { // Exercises branch where width%8 != 0, width != stride
        RANDOM,
        NULL, NULL, NULL,
        17, 2, 19, VXLIB_CONVERT_POLICY_SATURATE, (1.0f/(1<<2))
    },
    { // Exercises branch where width%8 != 0, width != stride, less than nearest multiple of 8
        RANDOM,
        NULL, NULL, NULL,
        15, 2, 19, VXLIB_CONVERT_POLICY_SATURATE, (1.0f/(1<<1))
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void multiply_i8u_i8u_o16s_getTestParams(multiply_i8u_i8u_o16s_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(multiply_i8u_i8u_o16s_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2016 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

