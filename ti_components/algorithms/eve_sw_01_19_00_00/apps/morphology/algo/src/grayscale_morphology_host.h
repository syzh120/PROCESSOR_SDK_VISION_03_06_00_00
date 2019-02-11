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


/** @file   grayscale_morphology.h
 *
 *  @brief  Grayscale Morphological Filtering Applet
 *
 *  @date   22 March 2013
 *
 *  This applet supports grayscale morphological filtering using a generic
 *  flat structuring element. The structuring element need to be specified
 *  as a mask of ones and zeros in an array of length se_width x se_height
 *  in 'struct_elem'. The user is also expected to provide the reflected
 *  structuring element array required for dilation in 'struct_elem_refl'.
 *  The input grayscale images are assumed to be 8-bit. The output is also
 *  an 8-bit grayscale image.
 *
 *  The supported grayscale morphological operations include: dilation,
 *  erosion, opening, closing, top hat, bottom hat and morphological gradient.
 *  Internally the applet processes the input image in blocks of 32x32. Hence
 *  the srcImageWidth and srcImageHeight needs to be multiples of 32 inorder to
 *  process the entire image.
 *
 */

#ifndef GRAYSCALE_MORPHOLOGY_HOST_H_
#define GRAYSCALE_MORPHOLOGY_HOST_H_

#include "imorphology_ti.h"


typedef struct
{
    MORPHOLOGY_TI_StructuringElementShape  seShape;
    MORPHOLOGY_TI_Operation                morphologyMode;
    uint16_t  blkWidth;
    uint16_t  blkStride;
    uint16_t  blkHeight;
    uint8_t  *dataPtr_A;
    uint16_t  seWidth;
    uint16_t  seHeight;
    uint8_t  *sePtr_C;
    uint8_t  *seReflPtr_C;
    uint8_t  *scratchPtr_C;
    uint8_t  *scratchPtr_A;
    uint8_t  *outputPtr_B;
} Grayscale_Morphology_ExecParams;

/**
*  @brief     Frame-level Grayscale Morphological Filtering API for Host Emulation

*  Grayscale_Morphology_exec performs the specified grayscale morphological
*  operation on the input 8-bit grayscale image provided in src buffer with
*  the structuring element provided in struct_elem and writes the output into
*  dst buffer in Host Emulation.
*
*  @code
*      void Grayscale_Morphology_exec(void *args)
*  @endcode
*
*  @param[in]   args               Pointer to the Grayscale_Morphology_ExecParams.
*
*/
void Grayscale_Morphology_exec(void *args);


#endif /*  GRAYSCALE_MORPHOLOGY_HOST_H_ */

