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

/*                                                                          */
/*     @file : vcop_hamming_distance_cn.h                                   */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function namely hamming distance                                     */
/*                                                                          */
/*     The following basic hamming distance function is provided:           */
/*     vcop_hamming_distance_cn                                             */
/*           Computes the hamming distance between two input byte array     */
/*           string pointers. Each byte array pointer is represented        */
/*           as depicted below                                              */
/*     Supports the following two modes                                     */
/*       1. mode = 0 :Many-to-One                                           */
/*          pHammingDistance[i] = HammingDistance(bytearr1[i], bytearr2[0]);*/
/*       2. mode = 1 :One-to-One                                            */
/*          pHammingDistance[i] = HammingDistance(bytearr1[i], bytearr2[i]);*/
/*       where i = 0,1,2, ...ySize-1                                        */
/*                                                                          */
/*                 xpitch                             xpitch                */
/*       <----------------------->          <----------------------->       */
/*            xsize                              xsize                      */
/*       <---------->                       <---------->                    */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[0]            |          |bytearr2[0]            |       */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[1]            |          |bytearr2[1]            |       */
/*       |-----------------------|          |-----------------------|       */
/*       |                       |          |                       |       */
/*       |                       |          |                       |       */
/*       |-----------------------|          |-----------------------|       */
/*       |bytearr1[ysize-1]      |          |bytearr2[ysize-1]      |       */
/*       |-----------------------|          |-----------------------|       */
/*           The output is written into pHammingDistance output array.      */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (July 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_HAMMING_DISTANCE_CN
#define _VCOP_HAMMING_DISTANCE_CN  1

void vcop_hamming_distance_cn
(
    uint8_t           *pString1,            // pointer to first byte array string pointer
    uint8_t           *pString2,            // pointer to second byte array string pointer
    uint32_t           xsize,               // size of each byte array element in bytes
    uint32_t           ysize,               // number of byte array elements with size "xsize" & pitch "xpitch" in first/second string pointer
    uint32_t           mode,                // mode = 0 : Many to one; mode = 1: One to one
    uint32_t           xpitch,              // pitch of each byte array element in bytes
    uint32_t          *pHammingDistance,    // pointer to hamming distance output array
    uint16_t           outStride,
    int16_t            startIdx
);

void vcop_findTwoBestMatches_cn
(
    uint32_t *pHammingDistance,
    uint32_t *pMinDist0,
    uint32_t *pMinDist1,
    uint8_t   stride,
    uint32_t  n
);

void vcop_pickConfidentMatches_cn
(
  uint16_t  *pMinDist0,
  uint16_t  *pMinDist1,
  uint16_t  *pMatchIndex,
  unsigned int   m,
  unsigned short minDistanceThres,
  unsigned short matchConfidence
);

#endif /* _VCOP_HAMMING_DISTANCE_CN */
