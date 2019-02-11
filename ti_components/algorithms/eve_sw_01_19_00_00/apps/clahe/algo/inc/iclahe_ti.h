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
*  @file       iclahe_ti.h
*
*  @brief      This file defines the ivision interface for CLAHE Applet
*  @version 0.1 (Nov 2014) : Base version.
*/

/** @ingroup    iclahe */
/*@{*/
#ifndef ICLAHE_TI_H
#define ICLAHE_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>


/**
* @brief The unique const funtion table for the CLAHE_TI.
*/
extern const IVISION_Fxns CLAHE_TI_VISION_FXNS;

/**
* @brief IRES interface of the CLAHE_TI_ algorithm
*/
extern const IRES_Fxns CLAHE_TI_IRES;



/**
@brief Error code returned by the CIRCULAR LIGHT RECOGNITION algorithm

CLAHE_TI_ERRORTYPE_INVALID_IMAGE_DIMS: Image dimensions are
beyond supported

CLAHE_TI_ERRORTYPE_INVALID_ROI_DIMS: ROI dimensions are
beyond image dimensions

CLAHE_TI_ERRORTYPE_INVALID_ROI_ALIGN: ROI dimensions are
not multiple of tile width or height

CLAHE_TI_ERRORTYPE_INVALID_TILE_DIMS: TILE dimensions are
beyond supported value. Please try smaller tile

CLAHE_TI_ERRORTYPE_INVALID_TILE_ALIGN: TILE width and \
height are not aligned to 16

CLAHE_TI_ERRORTYPE_CLIP_LIMIT_BEYOND_RANGE: Clip limit value is 
beyond supported


*/
typedef enum
{
  CLAHE_TI_ERRORTYPE_INVALID_IMAGE_DIMS = IVISION_CUSTOMFAILBASE,
  CLAHE_TI_ERRORTYPE_INVALID_ROI_DIMS,
  CLAHE_TI_ERRORTYPE_INVALID_ROI_ALIGN,
  CLAHE_TI_ERRORTYPE_INVALID_TILE_DIMS,
  CLAHE_TI_ERRORTYPE_INVALID_TILE_ALIGN,
  CLAHE_TI_ERRORTYPE_CLIP_LIMIT_BEYOND_RANGE,
  CLAHE_TI_ERRORTYPE_MAX
} CLAHE_TI_ErrorType;


/**
@brief User provides most of the infomration through buffer descriptor
during process call. Below enums define the purpose of buffer
There is 2 input buffers descriptors

CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER: This buffer descriptor provides the
actual image (Luma only) data required by algorithm.

CLAHE_TI_BUFDESC_IN_LUT_BUFFER: This buffer descriptor provides the
LUT for each tile, that needs to be used for current frame processing.

*/
typedef enum
{
  CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER = 0,
  CLAHE_TI_BUFDESC_IN_LUT_BUFFER,
  CLAHE_TI_BUFDESC_IN_TOTAL
} CLAHE_TI_InBufOrder ;

/**
@brief User provides most of the infomration through buffer descriptor
during process call. Below enums define the purpose of buffer
There is 2 output buffer descriptors

CLAHE_TI_BUFDESC_OUT_OBJ_BUFFER: This buffer descriptor has the
propsecced image output

CLAHE_TI_BUFDESC_OUT_LUT_BUFFER: This buffer descriptor has the
LUT for each tile that can be used for next frame

*/
typedef enum
{
  CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER = 0,
  CLAHE_TI_BUFDESC_OUT_LUT_BUFFER,
  CLAHE_TI_BUFDESC_OUT_TOTAL
} CLAHE_TI_OutBufOrder ;

/**

@struct CLAHE_TI_CreateParams
@brief  This structure contains all the parameters which CLAHE
applet at create time

@param  visionParams
Common parmeters for all ivison based modules

@param  maxWidth
The maximum output width. 

@param  maxWidth
The maximum output height. 

@param  tileWidth
Tile Width for Histogram computation. This shall be multiple of 16 
tileWidth*tileHeight s ahll be less than or equal to 16128

@param  tileHeight
Tile Hight for Histogram computation. This shall be multiple of 16 
tileWidth*tileHeight s ahll be less than or equal to 16128


*/
typedef struct
{
  IVISION_Params visionParams;
  uint16_t maxWidth;
  uint16_t maxHeight;
  uint16_t tileWidth;
  uint16_t tileHeight;
} CLAHE_TI_CreateParams;


/**

@struct CLAHE_TI_InArgs
@brief  This structure contains all the parameters which controls
the applet at create time

@param  iVisionInArgs
Common inArgs for all ivison based modules

@param  clipLimit
Clip Limit for contrast adaptive contarst control
*/

typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint16_t clipLimit;
} CLAHE_TI_InArgs;

/**

@struct CLAHE_TI_outArgs
@brief  This structure contains all the parameters which controls
the applet at create time

@param  visionParams
Common outArgs for all ivison based modules
*/

typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
} CLAHE_TI_outArgs;

/*@}*/
/* iCLAHE */

#endif /*ICLAHE_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


