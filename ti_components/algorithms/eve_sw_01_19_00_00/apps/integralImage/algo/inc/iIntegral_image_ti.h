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
 *  @file       ieve_integral_image_ti.h
 *
 *  @brief      This file defines the interface for integral Image Applet
 *  @version 0.0 (Jul 30, 2014) : Base version.
 */

/** @ingroup    ti_ivision_INTEGRAL_IMAGE */
/*@{*/
#ifndef IEVE_INTEGRAL_IMAGE_TI_H
#define IEVE_INTEGRAL_IMAGE_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the INTEGRAL_IMAGE_TI.
 */
extern const IVISION_Fxns INTEGRAL_IMAGE_TI_VISION_FXNS;

/**
* @brief IRES interface of the INTEGRAL_IMAGE_TI_ algorithm
*/
extern const IRES_Fxns INTEGRAL_IMAGE_TI_IRES;

/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of buffer
            There is 1 input buffers descriptor
            
            INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
            actual 8-bits image data required by algorithm. 
*/
typedef enum 
{
    INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER = 0,
    INTEGRAL_IMAGE_BUFDESC_IN_TOTAL
} INTEGRAL_IMAGE_InBufOrder ;
   
/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of out buffer
            There is 1 input buffers descriptor
            
            INTEGRAL_IMAGE_BUFDESC_OUT: This buffer is filled up by the algorithm and will contain 
            the inegral image output.
*/
typedef enum 
{
    INTEGRAL_IMAGE_BUFDESC_OUT = 0,
    INTEGRAL_IMAGE_BUFDESC_OUT_TOTAL
} INTEGRAL_IMAGE_OutBufOrder ;

/**

  @struct INTEGRAL_IMAGE_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          Integral Image applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in bytes for the input image

  @param  imgFrameHeight
          Width in bytes for the input image

*/
typedef struct
{
  IVISION_Params visionParams;
  uint32_t imgFrameWidth;
  uint32_t imgFrameHeight;
} INTEGRAL_IMAGE_TI_CreateParams;

/**

  @struct INTEGRAL_IMAGE_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  blockWidth
          Processing block width in number of pixels returned by BAM_createGraph(). That's useful information to understand performance.

  @param  blockheight
          Processing block height in number of rows returned by BAM_createGraph(). That's useful information to understand performance.

 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t blockWidth;
    uint16_t blockHeight;

} INTEGRAL_IMAGE_TI_outArgs;

/*@}*/
/* ti_ivision_INTEGRAL_IMAGE */

#endif /*IEVE_INTEGRAL_IMAGE_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


