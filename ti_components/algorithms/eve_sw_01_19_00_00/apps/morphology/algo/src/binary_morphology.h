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


/** @file   binary_morphology.h
 *
 *  @brief  Binary Morphological Filtering Applet
 *
 *  @date   Jan 2015
 *
 *  This applet supports binary morphological filtering using a generic
 *  flat structuring element. The structuring element need to be specified
 *  as a mask of ones and zeros in an array of length se_width x se_height
 *  in 'struct_elem'. The user is also expected to provide the reflected
 *  structuring element array required for dilation in 'struct_elem_refl'.
 *  The input binary images are assumed to be 8-bit. The output is also
 *  an 8-bit binary image.
 *
 *  The supported binary morphological operations include: dilation,
 *  erosion, opening, closing, top hat, bottom hat and morphological gradient.
 *  Internally the applet processes the input image in blocks of 32x32. Hence
 *  the srcImageWidth and srcImageHeight needs to be multiples of 32 inorder to
 *  process the entire image.
 *
 */

#ifndef BINARY_MORPHOLOGY_H_
#define BINARY_MORPHOLOGY_H_

#include "edma_utils_context_size.h"
#include "vcop_grayscale_morphology.h"

/* 240*PACKED_PIXEL_COUNT = 1920 */
#define BIN_MORPH_MAX_IMAGE_WIDTH  (240U)

typedef struct
{
    uint32_t                *srcPtr_A;
    uint32_t                *seCompCol1Ptr_C;
    uint32_t                *seCompCol2Ptr_C;
    uint32_t                *seCompCol3Ptr_C;
    uint32_t                *seReflCol1Ptr_C;
    uint32_t                *seReflCol2Ptr_C;
    uint32_t                *seReflCol3Ptr_C;
    uint32_t                *scratchPtr_C;
    uint32_t                *scratchPtr_A;
    uint32_t                *outputPtr_B;
    uint8_t                  autoIncrementContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
    stblock_morph_t          stParamBlock;
    stblock_open_close_t     stParamBlock_open_close;
} Binary_Morphology_Obj;


void Binary_Morphology_Init(Binary_Morphology_Obj *handle);


/**
*  @brief     Frame-level Binary Morphological Filtering API

*  EVELIB_binaryMorphology performs the specified binary morphological
*  operation on the input 8-bit binary image provided in src buffer with
*  the structuring element provided in struct_elem and writes the output into
*  dst buffer.
*
*  @code
*      void Binary_Morphology_Process(unsigned char  *src,
*                                      unsigned int    srcImageWidth,
*                                      unsigned int    srcImageHeight,
*                                      int             srcImagePitch,
*                                      unsigned char  *dst,
*                                      unsigned int    dstImageWidth,
*                                      unsigned int    dstImageHeight,
*                                      int             dstImagePitch,
*                                      unsigned char   struct_elem[],
*                                      unsigned char   struct_elem_refl[],
*                                      unsigned int    se_height,
*                                      unsigned int    se_width,
*                                      BinaryMorphologyOperation  operation)
*  @endcode
*
*  @param[in]   src               Pointer to the source buffer in SDRAM.
*  @param[in]   srcImageWidth     Input image width. Need to be a multiple of 32.
*  @param[in]   srcImageHeight    Input image height. Need to be a multiple of 32.
*  @param[in]   srcImagePitch     Stride of the input buffer.
*  @param[out]  dst               Pointer to the destination buffer in SDRAM.
*  @param[in]   dstImageWidth     Output image width.
*  @param[in]   dstImageHeight    Output image height.
*  @param[in]   dstImagePitch     Stride of the output buffer.
*  @param[in]   struct_elem       Pointer to structuring element array.
*  @param[in]   struct_elem_refl  Pointer to reflected structuring element array.
*  @param[in]   operation         Binary morphological operation to be performed.
*
*/
void Binary_Morphology_Process(
                         Binary_Morphology_Obj *handle,
                         uint8_t      *src,
                         uint16_t      srcImageWidth,
                         uint16_t      srcImageHeight,
                         uint16_t      srcImagePitch,
                         uint8_t      *dst,
                         uint16_t      dstImageWidth,
                         uint16_t      dstImageHeight,
                         uint16_t      dstImagePitch,
                         uint8_t       struct_elem[],
                         uint8_t       seShape,
                         uint8_t       operation);


void Binary_Morphology_Deinit(Binary_Morphology_Obj *handle);


#endif /*  BINARY_MORPHOLOGY_H_ */

