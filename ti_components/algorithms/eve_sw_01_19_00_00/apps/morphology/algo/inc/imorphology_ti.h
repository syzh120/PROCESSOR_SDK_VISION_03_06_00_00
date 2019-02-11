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
 *  @file       imorphology_ti.h
 *
 *  @brief      This file defines the ivision interface for Morphology
 *               applet.
 *  @version 0.0 (July 2014) : Base version.
 */

/** @ingroup    ti_ivision_MORPHOLOGY */
/*@{*/
#ifndef IMORPHOLOGY_TI_H_
#define IMORPHOLOGY_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

#define MORPHOLOGY_TI_MAX_GRAYSCALE_SE_WIDTH  (13U)
#define MORPHOLOGY_TI_MAX_GRAYSCALE_SE_HEIGHT (13U)

#define MORPHOLOGY_TI_BINARY_SE_WIDTH         (3U)
#define MORPHOLOGY_TI_BINARY_SE_HEIGHT        (3U)

/**
 * @brief The unique const funtion table for the MORPHOLOGY_TI.
 */
extern const IVISION_Fxns MORPHOLOGY_TI_VISION_FXNS;

/**
* @brief IRES interface of the MORPHOLOGY_TI_ algorithm
*/
extern const IRES_Fxns MORPHOLOGY_TI_IRES;


typedef enum
{
  MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_IMAGE_TYPE = IALG_CUSTOMFAILBASE,
  MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_SE_SHAPE,
  MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_SE_DIMENSION,
  MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_INPUTBUF_DIMENSION,
  MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_OUTPUTBUF_DIMENSION,
  MORPHOLOGY_TI_ERRORTYPE_UNSUPPORTED_OPERATION,
  MORPHOLOGY_TI_ERRORTYPE_MAX_ERROR_CODE
} MORPHOLOGY_TI_ErrorType;


/**
  @brief User provides most of the information through buffer descriptor
         during process call. Below enums define the purpose of buffer

  MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet.

  MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER: This buffer descriptor provides the
  Structuring Element required by applet. This needs to be provided only when Mask is
  set to generic.

  MORPHOLOGY_TI_BUFDESC_IN_TOTAL :
  Total number of input buffers.
*/

typedef enum
{
  MORPHOLOGY_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  MORPHOLOGY_TI_BUFDESC_IN_SEBUFFER    = 1,
  MORPHOLOGY_TI_BUFDESC_IN_TOTAL       = 2
} MORPHOLOGY_TI_InBufOrder ;


/**
  @brief User provides most of the information through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  MORPHOLOGY_TI_BUFDESC_OUT_BUFFER:This buffer descriptor provides the
  output buffer to store the data after morphology processing.

  MORPHOLOGY_TI_BUFDESC_OUT_TOTAL :
  Total number of output buffers.
*/

typedef enum
{
  MORPHOLOGY_TI_BUFDESC_OUT_BUFFER = 0,
  MORPHOLOGY_TI_BUFDESC_OUT_TOTAL  = 1
} MORPHOLOGY_TI_OutBufOrder ;


typedef enum
{
  MORPHOLOGY_TI_BINARY_IMAGE    = 0,
  MORPHOLOGY_TI_GRAYSCALE_IMAGE = 1,
  MORPHOLOGY_TI_IMAGE_TYPES_MAX = 2
} MORPHOLOGY_TI_ImageType ;

typedef enum
{
  MORPHOLOGY_TI_CUSTOM_SE    = 0,
  MORPHOLOGY_TI_RECT_SE      = 1,
  MORPHOLOGY_TI_CROSS_SE     = 2,
  MORPHOLOGY_TI_SE_SHAPE_MAX = 3
} MORPHOLOGY_TI_StructuringElementShape ;

typedef enum
{
  MORPHOLOGY_TI_DILATE        = 0,
  MORPHOLOGY_TI_ERODE         = 1,
  MORPHOLOGY_TI_OPEN          = 2,
  MORPHOLOGY_TI_CLOSE         = 3,
  MORPHOLOGY_TI_TOPHAT        = 4,
  MORPHOLOGY_TI_BOTTOMHAT     = 5,
  MORPHOLOGY_TI_GRADIENT      = 6,
  MORPHOLOGY_TI_OPERATION_MAX = 7
} MORPHOLOGY_TI_Operation ;


/**
  @struct MORPHOLOGY_TI_CreateParams
  @brief  This structure contains all the parameters needed
              at create time for this applet

@param  srcType
              Source Image type. Should be one of the following denoted
              by the enum MORPHOLOGY_TI_ImageType.

*/

typedef struct
{
  uint8_t        srcType;
  IVISION_Params visionParams;
} MORPHOLOGY_TI_CreateParams;


/**
  @struct MORPHOLOGY_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to Filter at frame level

  @param  iVisionInArgs
                Common InArgs  for all ivision based modules

  @param  morphologyOperation
                Morphology Operation to be performed. Should be one of the following denoted
                by the enum MORPHOLOGY_TI_Operation.

  @param  srcWidth
                Source Image frame width.

  @param  srcPitch
                Source Image frame stride/pitch.

  @param  srcHeight
                Source Image frame height.

  @param  dstWidth
                Output frame width.

  @param  dstPitch
                Output frame stride/pitch.

  @param  dstHeight
                Output frame height.

  @param  seShape
                Structuring Element shape. Should be one of the following denoted
                by the enum MORPHOLOGY_TI_StructuringElementShape.

  @param  seWidth
                Structuring Element width.

  @param  seHeight
                Structuring Element height.
*/

typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint8_t        morphologyOperation;
  uint8_t        seShape;
  uint16_t       seWidth;
  uint16_t       seHeight;
} MORPHOLOGY_TI_InArgs;


/**
  @struct MORPHOLOGY_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by Filter  at frame level

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules
*/

typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
} MORPHOLOGY_TI_OutArgs;


/*@}*/
/* ti_ivision_MORPHOLOGY */

#endif /*IMORPHOLOGY_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

