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
/*     NAME                                                                 */
/*     vcop_yuv_scalar_cn.h.h                                               */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*         This is the c-reference header for the                           */
/*         YUV scalar  kernel                                               */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (Dec 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_LOCATION_MATRIX_CN
#define _VCOP_LOCATION_MATRIX_CN  1

/* generic re-sizer for 8 bit Luma Image */
void vcop_resize_cn_y(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);
/* 8 bit Luma Image re-sizer. Vertical re-sizer followed by Horizontal Re-sizer*/
void vcop_resize_cn_y_s(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);
/* generic re-sizer for 8 bit Interleaved chroma Image */
void vcop_resize_cn_uv(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);
/* 8 bit  Interleaved chroma Image re-sizer. Vertical re-sizer followed by Horizontal Re-sizer*/
void vcop_resize_cn_uv_s(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift);

/* Luma vertical resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_luma_vertical_cn(uint8_t *inBlkPtr, uint8_t *interBlkPtr, uint16_t *yIndexPtr, uint8_t *yFracPtr, uint16_t inBlockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);
/* Luma Horizontal resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_luma_Horizontal_cn(uint8_t *interBlkPtr, uint8_t *outBlkPtr, uint16_t *xIndexPtr, uint8_t *xFracPtr, uint16_t inBlockWidth, uint16_t blockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);
/* Chroma vertical resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_chroma_vertical_cn(uint8_t *inBlkPtr, uint8_t *interBlkPtr, uint16_t *yIndexPtr, uint8_t *yFracPtr, uint16_t inBlockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);
/* Chroma Horizontal resize : Natrual C-version of Kernel to utilizing look tables for resizing */
void vcop_scaler_chroma_Horizontal_cn(uint8_t *interBlkPtr, uint8_t *outBlkPtr, uint16_t *xIndexPtr, uint8_t *xFracPtr, uint16_t inBlockWidth, uint16_t blockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift);

#endif /* _VCOP_LOCATION_MATRIX_CN */

