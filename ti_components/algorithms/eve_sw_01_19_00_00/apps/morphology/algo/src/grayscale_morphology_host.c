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


/** @file grayscale_morphology.c
 *
 *  @brief  This file implements an applet for grayscale morphology
 *
 *  @author Anoop K P <a-kp@ti.com>
 *
 *  @date   22 March 2013
 *
 *  Description
 *    This file contains code to perform grayscale morphological processing
 *    at the frame level.
 */


#include <stdint.h>
#include <vcop.h>
#include "xdais_types.h"
#include <stdio.h>

#include "imorphology_ti.h"
#include "grayscale_morphology_host.h"

#include "vcop_grayscale_morphology_kernel.h"
#include "vcop_grayscale_morphology.h"



void Grayscale_Morphology_exec(void *args)
{
  Grayscale_Morphology_ExecParams *execParams  = (Grayscale_Morphology_ExecParams *)args;
  MORPHOLOGY_TI_StructuringElementShape  seShape        = execParams->seShape;
  MORPHOLOGY_TI_Operation                morphologyMode = execParams->morphologyMode;
  uint16_t  blkWidth     = execParams->blkWidth;
  uint16_t  blkStride    = execParams->blkStride;
  uint16_t  blkHeight    = execParams->blkHeight;
  uint8_t  *dataPtr_A    = execParams->dataPtr_A;
  uint16_t  seWidth      = execParams->seWidth;
  uint16_t  seHeight     = execParams->seHeight;
  uint8_t  *sePtr_C      = execParams->sePtr_C;
  uint8_t  *seReflPtr_C  = execParams->seReflPtr_C;
  uint8_t  *scratchPtr_C = execParams->scratchPtr_C;
  uint8_t  *scratchPtr_A = execParams->scratchPtr_A;
  uint8_t  *outputPtr_B  = execParams->outputPtr_B;

  switch ( morphologyMode )
  {
    case MORPHOLOGY_TI_DILATE:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_dilate_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, seReflPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_dilate_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_dilate_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, (seHeight-1)/2, (seWidth-1)/2, scratchPtr_C, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_ERODE:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_erode_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_erode_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_erode_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, (seHeight-1)/2, (seWidth-1)/2, scratchPtr_C, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_OPEN:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_open_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_open_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_open_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_CLOSE:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_close_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_close_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_close_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_TOPHAT:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_tophat_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_tophat_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_tophat_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_BOTTOMHAT:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_bottomhat_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_bottomhat_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_bottomhat_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
    case MORPHOLOGY_TI_GRADIENT:

      switch ( seShape )
      {
        case MORPHOLOGY_TI_CUSTOM_SE:
          vcop_grayscale_morph_grad_mask(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, sePtr_C, seReflPtr_C, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_RECT_SE:
          vcop_grayscale_morph_grad_rect(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
        case MORPHOLOGY_TI_CROSS_SE:
          vcop_grayscale_morph_grad_cross(blkWidth, blkStride, blkHeight, dataPtr_A,
              seWidth, seHeight, scratchPtr_C, scratchPtr_A, outputPtr_B);

        break;
      }

    break;
  }
}

