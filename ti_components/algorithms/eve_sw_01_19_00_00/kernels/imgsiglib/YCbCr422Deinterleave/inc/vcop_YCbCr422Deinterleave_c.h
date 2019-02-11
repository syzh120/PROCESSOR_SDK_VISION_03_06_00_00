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


/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDeinterleave : Test bench data                 */ 
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDeinterleave" accepts  8 or 16-bit data */
/* in the form of 8 or 16-bit "Y", "Cb" and "Cr", and writes out   */
/* 8-bit "Y", 8-bit "Cb" and "Cr". The input data can be of 444 or */
/* 422 format, the output can be of 444, 422 or 420 formats.       */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_YCbCrDeinterleave                                     */
/* (                                                               */
/*     unsigned int   YCbCr[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  Y[],                                         */
/*     unsigned char  Cb[],                                        */
/*     unsigned char  Cr[]                                         */
/* )                                                               */
/*                                                                 */
/*                                                                 */
/*=================================================================*/


#ifndef __VCOP_YCbCr_Deinterleave_H__
#define __VCOP_YCbCr_Deinterleave_H__  1

void vcop_YCbCr444_Deinterleave444_char
(
    unsigned char  YCbCr[],
    unsigned int   npixels,
    unsigned char  Y[],
    unsigned char  Cb[],
    unsigned char  Cr[]
);


void vcop_YCbCr444_Deinterleave444_short
(
    unsigned short  YCbCr[],
    unsigned int    npixels,
    unsigned short  Y[],
    unsigned short  Cb[],
    unsigned short  Cr[]
);

void vcop_YCbCr422_Deinterleave422_char
(
    unsigned char  YCbCr[],
    unsigned int   npixels,
    unsigned char  Y[],
    unsigned char  Cb[],
    unsigned char  Cr[]
);

void vcop_YCbCr422_Deinterleave422_short
(
    unsigned short  YCbCr[],
    unsigned int    npixels,
    unsigned short  Y[],
    unsigned short  Cb[],
    unsigned short  Cr[]
);

#endif

/*-----------------------------------------------------------------*/
/* End of file: vcop_YCbCr_Deinterleave_c.h                        */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

