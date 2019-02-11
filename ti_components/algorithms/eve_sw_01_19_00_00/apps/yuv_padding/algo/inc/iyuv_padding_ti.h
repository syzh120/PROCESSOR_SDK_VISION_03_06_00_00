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
 *  @file       iyuv_padding_ti.h
 *
 *  @brief      This file defines the ivision interface for YUV Padding Applet
 *  @version 0.0 (Mar 2014) : Base version.
 */

/** @ingroup    iYUV_PADDING */
/*@{*/
#ifndef IYUV_PADDING_TI_H
#define IYUV_PADDING_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>


/**
 * @brief The unique const funtion table for the YUV_PADDING_TI.
 */
extern const IVISION_Fxns YUV_PADDING_TI_VISION_FXNS;

/**
 * @brief IRES interface of the YUV_PADDING_TI_ algorithm
 */
extern const IRES_Fxns YUV_PADDING_TI_IRES;

/**
 * @brief Buffer index for input image data
  This buffer width has to be greater than or equal to the
  processing width aligned to 64. This buffer height has to
  be greater than or equal to the processing height aligned to 64
 */
#define YUV_PADDING_TI_IN_IMAGE_BUF_IDX (0)

/**
 * @brief Buffer index for output input image data
  Both input and output will be pointing to same memory
  region with an offset for inplace padding use case
  This buffer width has to be greater than or equal to the
  processing width aligned to 64 + left and right padding. This buffer
  height has to be greater than or equal to the processing height
  aligned to 64 + top and bottom padding
 */
#define YUV_PADDING_TI_OUT_IMAGE_BUF_IDX (0)

/**

  @struct YUV_PADDING__TI_CreateParams
  @brief  This structure contains all the parameters which controls
          YUV Padding Applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxImageWidth
          MAximum image with supported

  @param  topPadding
          Number of row to be padded on top

  @param  leftPadding
          Number of coloms to be padded on left

  @param  BottomPadding
          Number of row to be padded on bottom

  @param  rightPadding
          Number of coloms to be padded on rignts


 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t maxImageWidth    ;
    uint16_t topPadding    ;
    uint16_t leftPadding   ;
    uint16_t rightPadding  ;
    uint16_t BottomPadding ;
} YUV_PADDING_TI_CreateParams;


/**

  @struct YUV_PADDINGTI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules
 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
} YUV_PADDING_TI_outArgs;

/*@}*/
/* iYUV_PADDING */

#endif /*YUV_PADDING */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


