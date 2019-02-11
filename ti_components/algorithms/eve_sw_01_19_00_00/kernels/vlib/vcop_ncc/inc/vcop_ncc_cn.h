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



#ifndef _VCOP_NCC_CN_H_
#define _VCOP_NCC_CN_H_

#include <stdint.h>
#include "vcop_ncc.h"

typedef int32_t (*NccFunc)(
        uint8_t     orgImg[],           /*original input image data pointer */
        int32_t     orgImgWidth,        /*original input image width*/
        int32_t     orgImgHeight,       /*original input image height*/
        int32_t     orgImgPitch,        /*original input image pitch*/
        int16_t     tempImg[],          /*template image pointer*/
        int32_t     tempImgWidth,       /*template image width*/
        int32_t     tempImgHeight,      /*template image height*/
        int32_t     tempImgPitch,       /*template image pitch*/
        uint8_t     sizeQshift,         /*number of fractional bits used to compute the inverse of the size of the template*/
        uint8_t     qShift,             /*number of fractional bits */
        uint8_t     xDirJump,           /*Jump in x direction while searching*/
        uint8_t     yDirJump,           /*Jump in y direction while searching*/
        int32_t     outNumCC[],         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        uint32_t    outDenomVar[],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        int32_t     outPitch,           /*Out Score buffer pitch*/
        int32_t     scratch[],
        int32_t     scratchStride,
        uint32_t     sum[],
        int32_t     sumStride
        );


int32_t vcop_ncc_cn(
        uint8_t     orgImg[],           /*original input image data pointer */
        int32_t     orgImgWidth,        /*original input image width*/
        int32_t     orgImgHeight,       /*original input image height*/
        int32_t     orgImgPitch,        /*original input image pitch*/
        int16_t     tempImg[],          /*template image pointer*/
        int32_t     tempImgWidth,       /*template image width*/
        int32_t     tempImgHeight,      /*template image height*/
        int32_t     tempImgPitch,       /*template image pitch*/
        uint8_t     sizeQshift,         /*number of fractional bits used to compute the inverse of the size of the template*/
        uint8_t     qShift,             /*number of fractional bits */
        uint8_t     xDirJump,           /*Jump in x direction while searching*/
        uint8_t     yDirJump,           /*Jump in y direction while searching*/
        int32_t     outNumCC[],         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        uint32_t    outDenomVar[],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        int32_t     outPitch,           /*Out Score buffer pitch*/
        int32_t     scratch[],
        int32_t     scratchStride,
        uint32_t     sum[],
        int32_t     sumStride
        );

int32_t vcop_ncc_opt_cn(
        uint8_t     orgImg[],           /*original input image data pointer */
        int32_t     orgImgWidth,        /*original input image width*/
        int32_t     orgImgHeight,       /*original input image height*/
        int32_t     orgImgPitch,        /*original input image pitch*/
        int16_t     tempImg[],          /*template image pointer*/
        int32_t     tempImgWidth,       /*template image width*/
        int32_t     tempImgHeight,      /*template image height*/
        int32_t     tempImgPitch,       /*template image pitch*/
        uint8_t     sizeQshift,         /*number of fractional bits used to compute the inverse of the size of the template*/
        uint8_t     qShift,             /*number of fractional bits */
        uint8_t     xDirJump,           /*Jump in x direction while searching*/
        uint8_t     yDirJump,           /*Jump in y direction while searching*/
        int32_t     outNumCC[],         /* numerator output corresponding to the cross-correlation between the input and the template = sum(f'(x,y)*t'(x-u,y-v)) */
        uint32_t    outDenomVar[],       /* denominator output corresponding to the input variance = sum(f'(x,y)^2) */
        int32_t     outPitch,           /*Out Score buffer pitch*/
        int32_t     scratch[],
        int32_t     scratchStride,
        uint32_t    sum[],
        int32_t     sumStride
);

#endif
