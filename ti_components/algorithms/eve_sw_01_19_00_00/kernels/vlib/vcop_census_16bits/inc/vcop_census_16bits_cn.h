/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/**
 *******************************************************************************
 *  @func          vcop_census_16bits_cn
 *  @brief         This is natural C implementation of census transform
 *  @param [in]    input   : Pointer to input 16-bit image
 *  @param [in]    output  : Pointer to bitpacked output
 *
 *  Output format of the buffer is crtical to know. It is as described
 *  Output stride of the buffer in bytes is at least computeWidth*ROUNDUP( ((winWidth+winHorzStep-1)/winHorzStep)*((winHeight+winVertStep-1)/winVertStep)/8)
 *  OutputHeight of the buffer is computeHeight
 *  The way census transform output is organized is as follow:
 *  For any input pixel input(x,y)
 *  bit#0 is '1' if center pixel input(x,y) is greater or equal than pixel at position input(x-winWidth/2 , y-winHeight/2)), which is the upper-left pixel, else it is '0'
 *  bit#1 is '1' if center pixel input(x,y) is greater or equal than pixel at position input(x-winWidth/2 + winHorzStep, y-winHeight/2), else it is '0'
 *  bit#2 is '1' if center pixel input(x,y) is greater or equal than pixel at position input(x-winWidth/2 + 2*winHorzStep, y+winHeight/2), else it is '0'
 *  etc.
 *  
 *  Most significant bits that correspond to non-existent pixel positions are set to 0.
 *
 *  @param [in]    winWidth : width of the census transform support window.
 *  @param [in]    winHeight : height of the census transform support window.
 *  @param [in]    winHorzStep : horizontal step between each orientation in the support window. Typically 1 or 2.
 *  @param [in]    winVertStep : vertical step between each orientation in the support window. Typically 1 or 2.
 *  @param [in]    computeWidth : Number of horizontal pixels to be filtered, not including winWidth-1 border pixels
 *  @param [in]    computeWidth : Number of vertical pixels to be filtered, not including winWHeight-1 border pixels
 *  @param [in]    inStride : Horizontal stride of the input block in number of pixels. Should be greater or equal to computeWidth + winWidth - 1
 *  @param [in]    outStride : Horizontal stride of the output block in number of bytes. Should be greater or equal to computeWidth*ROUNDUP((winWidth*winHeight)/8)
 *  @return        None
 *******************************************************************************
 */

#ifndef _VCOP_CENSUS_16BITS_CN_H_
#define _VCOP_CENSUS_16BITS_CN_H_

#include <stdint.h>

/*#define _DROP_CENTER_PIXEL*/

#ifdef _DROP_CENTER_PIXEL
#define _CENSUS_WIN_SIZE(winWidth, winHeight) ((((winWidth) + (hStep) -1u)/(hStep)) * (((winHeight) + (vStep) -1u)/(vStep)) -  1u)
#define _IS_NOT_CENTER(l, k, winWidth, winHeight) ((k)!= (winHeight)/2u || (l) != (winWidth)/2u)
#else
#define _CENSUS_WIN_SIZE(winWidth, winHeight, hStep, vStep) ((((winWidth) + (hStep) -1u)/(hStep)) * (((winHeight) + (vStep) -1u)/(vStep)))
#define _IS_NOT_CENTER(l, k, winWidth, winHeight) (1)
#endif

#define CENSUS_COMPARE(a,b) ((a)<=(b))

void vcop_census_16bits_cn
(
        uint16_t *input,
        uint8_t *output,
        uint8_t winWidth, /* windWidth * winHeight msut be > 8 */
        uint8_t winHeight,
        uint8_t winHorzStep,
        uint8_t winVertStep,
        uint16_t computeWidth,
        uint16_t computeHeight,
        uint16_t inStride,
        uint16_t outStride /* in bytes */
);

#endif
