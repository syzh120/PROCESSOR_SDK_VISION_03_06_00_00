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
 *  @file       iyuv_scalar_ti.h
 *
 *  @brief      This file defines the ivision interface for YUV Scalar Applet
 *  @version 0.0 (Mar 2014) : Base version.
 */

/** @ingroup    iYUV_SCALAR */
/*@{*/
#ifndef IYUV_SCALAR_TI_H
#define IYUV_SCALAR_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>


/**
 * @brief The unique const funtion table for the YUV_SCALAR_TI.
 */
extern const IVISION_Fxns YUV_SCALAR_TI_VISION_FXNS;

/**
 * @brief IRES interface of the YUV_SCALAR_TI_ algorithm
 */
extern const IRES_Fxns YUV_SCALAR_TI_IRES;

/**
 * @brief Macro symbols used as command passed to the control API
 */
#define YUV_SCALAR_TI_GET_OUTPUT_BLOCK_DIM 0x0 /* Get output block's dimensions (width & height) derived during applet creation */

/**
  @brief  Below enums define the types supported scaling methods

  YUV_SCALAR_TI_METHOD_BI_LINEAR_INTERPOLATION: Bi-Linear interpolation based scaling

*/typedef enum
{
  YUV_SCALAR_TI_METHOD_BI_LINEAR_INTERPOLATION,
  YUV_SCALAR_TI_METHOD_MAX
} YUV_SCALAR_TI_ScalingMethods; 

/**

  @struct YUV_SCALAR_TI_CreateParams
  @brief  This structure contains all the parameters which YUV scalar
          applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxWidth
         The maximum output width. 

  @param  maxWidth
         The maximum output height. 

  @param  scaleRatioQ12
             Scalaing rati in Q12 format. 
  @param  scalingMethod
          Scaling methos to be used. Refer 
           YUV_SCALAR_TI_ScalingMethods for suported methods
  @param  fracQFmt 
          Q format for fraction pixel location represenatation (as well as filter co-efficients). 
  @param  outStartX
          Horizontal offset in the ouput image (Refer the user guide for more information)

  @param  outStartY
          Vertical offset in the ouput image (Refer the user guide for more information)

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t maxWidth;
    uint16_t maxHeight;
    uint16_t scaleRatioQ12;
    uint8_t  scalingMethod;
    uint8_t  fracQFmt;
    uint16_t outStartX;
    uint16_t outStartY;
} YUV_SCALAR_TI_CreateParams;




/**

  @struct YUV_SCALAR_TI_InArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  iVisionInArgs
          Common inArgs for all ivison based modules
 */

typedef struct
{
    IVISION_InArgs iVisionInArgs;
} YUV_SCALAR_TI_InArgs;

/**

  @struct YUV_SCALAR_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time
          Please refer the user guide for output buffer size requirement.

  @param  visionParams
          Common outArgs for all ivison based modules
 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
} YUV_SCALAR_TI_outArgs;

/**

  @struct YUV_SCALAR_TI_ControlInParams
  @brief  This structure contains all the input parameters which controls
          the applet after creation. 
          In the case of DiffOfGauss transform, it does not have any additional parameters
          than the default algParams from which it inherits the content.

  @param  algParams
          Common params for all IALG based modules

 */
typedef struct
{
    IALG_Params algParams;
} YUV_SCALAR_TI_ControlInParams;

/**

  @struct YUV_SCALAR_TI_ControlOutParams
  @brief  This structure contains all the output parameters written by the control function
          the applet after creation. Mainly it contains output block dimensions which can be queried
          after graph creation. The application should use these values to make sure that any ROI's width and height
          are multiple of the output block's width and height.

  @param  algParams
          Common params for all IALG based modules

  @param  outputBlockWidth
          output block width
          
  @param  outputBlockHeight
          output block height

 */
typedef struct
{
    IALG_Params algParams;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;
    
} YUV_SCALAR_TI_ControlOutParams;

/*@}*/
/* iYUV_SCALAR */

#endif /*IYUV_SCALAR_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


