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
/* NAME : vcop_BayerCFA_interpolate                                */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The "vcop_BayerCFA_interpolate" code accepts 8 or 16-bit data   */
/* in the form of 8 or 16-bit Bayer Pattern, and writes out        */
/* the result as separate R, G and B planes. The output is         */
/* interpolated data to match the input width and height.          */
/* Interpolation is carried out by averaging the left and right    */
/* pixels, or the top and bottom pixels as the case may be.        */
/* In some cases, all four of the top-bottom-left-right pixels are */
/* used to compute the center pixel value.                         */
/*                                                                 */
/*                                                                 */
/* The Bayer pattern is as follows:                                */
/* -------------------------------                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/* B G B G B G B G                                                 */
/* G R G R G R G R                                                 */
/*                                                                 */
/* After demosiacing or deinterleaving step we get:                */
/* ------------------------------------------------                */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/* B  bx B  bx B  bx  B                                            */
/* by bz by bz by bz  by                                           */
/*                                                                 */
/* rz ry rz ry rz  ry ry                                           */
/* rx R  rx R  rx  R  R                                            */
/* rz ry rz ry rz  ry ry                                           */
/* rx R  rx R  rx  R  R                                            */
/*                                                                 */
/* gy G gy  G  gy G  gy                                            */
/* G  gx G  gx G  gx  G                                            */
/* gy G gy  G  gy G  gy                                            */
/* G  gx G  gx G  gx  G                                            */
/*                                                                 */
/* At this stage, bx, by, bz, rx, ry, rz, gx, gy are zeros.        */
/*                                                                 */
/* After interpolating we get:                                     */
/* ---------------------------                                     */
/* Where bx = (Bleft + Bright)/2                                   */
/* Where by = (Btop  + Bbottom)/2                                  */
/* Where bz = (Bleft + Bright + Btop + Bbottom)/4                  */
/*                                                                 */
/* Where rx = (Rleft + Rright)/2                                   */
/* Where ry = (Rtop  + Rbottom)/2                                  */
/* Where rz = (Rleft + Rright + Rtop + Rbottom)/4                  */
/*                                                                 */
/* Where gx = (Gleft + Gright)/2                                   */
/* Where gy = (Gtop  + Gbottom)/2                                  */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_BayerCFA_Interpolate_char                             */
/* (                                                               */
/*     __vptr_uint8   CFA_char,                                    */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint8   R_char,                                      */
/*     __vptr_uint8   G_char,                                      */
/*     __vptr_uint8   B_char                                       */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* void vcop__BayerCFA_Interpolate_short                           */
/* (                                                               */
/*     __vptr_uint16  CFA_short,                                   */
/*     unsigned int   blk_w,                                       */
/*     unsigned int   blk_h,                                       */
/*     __vptr_uint16  R_short,                                     */
/*     __vptr_uint16  G_short,                                     */
/*     __vptr_uint16  B_short                                      */
/* );                                                              */
/*                                                                 */
/*                                                                 */
/* PERFORMANCE                                                     */
/*                                                                 */
/* BayerCFA_interpolate_char:                                      */
/* BayerCFA_interpolate_short:                                     */
/*                                                                 */
/*=================================================================*/


#ifndef __VCOP_BAYER_CFA_INTERPOLATE_C_H__
#define __VCOP_BAYER_CFA_INTERPOLATE_C_H__    1

void vcop_BayerCFA_interpolate_char
(
    unsigned char  *CFA_char,  
    unsigned int   in_w,
    unsigned int   blk_w,
    unsigned int   blk_h,
    unsigned char  *R_char,
    unsigned char  *G_char,
    unsigned char  *B_char
);


void vcop_BayerCFA_interpolate_short
(
    unsigned short  *CFA_short,  
    unsigned int    in_w,
    unsigned int    blk_w,
    unsigned int    blk_h,
    unsigned short  *R_short,
    unsigned short  *G_short,
    unsigned short  *B_short
);

#endif

/*-----------------------------------------------------------------*/
/* End of file: vcop_BayerCFA_interpolate_kernel.h                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

