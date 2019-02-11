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
 *  @file       iTemplateMatching_ti.h
 *
 *  @brief      This file defines the ivision interface for template matching Applet
 *  @version 0.0 (Dec 2016) : Base version.
 */

/** @ingroup    iTEMPLATE_MATCHING */
/*@{*/
#ifndef ITEMPLATE_MATCHING_TI_H
#define ITEMPLATE_MATCHING_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

/**
 * @brief Macro symbols used as command passed to the control API
 */
#define TEMPLATE_MATCHING_TI_GET_OUTPUT_BLOCK_DIM 0x0 /* Get output block's dimensions (width & height) derived during applet creation */
#define TEMPLATE_MATCHING_TI_MAX_TEMPLATE_DIM     (128U*128U)

/**
 * @brief Macro symbols used as error code returned by the alloc init, process, control or deinit APIs.
 *
 *  TEMPLATE_MATCHING_ERROR_INVALID_ROI_DIM: One of the ROI dimensions (width/height) passed to process API is not multiple of the output block width/height
 *  TEMPLATE_MATCHING_TI_ERROR_MAX: templateWidth x templateHeight exceeds the maximum allowed size of TEMPLATE_MATCHING_TI_MAX_TEMPLATE_DIM
 */
typedef enum
{
    TEMPLATE_MATCHING_TI_ERROR_INVALID_ROI_DIM = IALG_CUSTOMFAILBASE,
    TEMPLATE_MATCHING_TI_ERROR_INVALID_TEMPLATE_DIM,
    TEMPLATE_MATCHING_TI_ERROR_MAX
} TEMPLATE_MATCHING_TI_ErrorCodes ;
/**
 * @brief The unique const funtion table for the TEMPLATE_MATCHING_TI.
 */
extern const IVISION_Fxns TEMPLATE_MATCHING_TI_VISION_FXNS;

/**
 * @brief IRES interface of the TEMPLATE_MATCHING_TI_ algorithm
 */
extern const IRES_Fxns TEMPLATE_MATCHING_TI_IRES;

/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of buffer
            There is 1 input buffers descriptor
            
            TEMPLATE_MATCHING_BUFDESC_IN: This buffer descriptor provides the
            actual image data required by algorithm. The data is composed of unsigned 8-bits data

            TEMPLATE_MATCHING_BUFDES_TEMPLATE: This buffer descriptor provides the
            template data required by algorithm. The data is composed of 16-bits data in Q format
            of a 0-mean template. A 0-mean template is obtained by subtrating the mean value from all the pixels.
            The number of fractional bits used for the Q format must match the parameter qShift
            passed to TEMPLATE_MATCHING_TI_CreateParams.
            
*/
typedef enum 
{
    TEMPLATE_MATCHING_TI_BUFDESC_IN = 0,
    TEMPLATE_MATCHING_TI_BUFDESC_IN_TEMPLATE = 1,
    TEMPLATE_MATCHING_TI_BUFDESC_IN_TOTAL = 2
} TEMPLATE_MATCHING_TI_InBufOrder ;
   
/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of out buffer
            There is 1 output buffers descriptor
            
            TEMPLATE_MATCHING_TI_BUFDESC_OUT: This buffer is filled up by the algorithm and will contain
            two planes:
            - plane 0 contains the signed 32-bits numerator values of the cross-correlation.
            - plane 1 contains the unsigned 32-bits denominator values of the cross-correlation, corresponding to the variance of the neighborhood
            of the input location associated to the cross-correlation value.
            All the outputs value are in Q-format with 'qShift' factional bits, where 'qShift' is the parameter passed to TEMPLATE_MATCHING_TI_CreateParams.
*/
typedef enum 
{
    TEMPLATE_MATCHING_TI_BUFDESC_OUT = 0,
    TEMPLATE_MATCHING_TI_BUFDESC_OUT_TOTAL
} TEMPLATE_MATCHING_TI_OutBufOrder ;

/**
    @brief  This enum type defines the method used to perform the template matching

            TEMPLATE_MATCHING_TI_NCC: Normalized cross correlation. Currently the only method supported.

 */
typedef enum {
    TEMPLATE_MATCHING_TI_NCC= 0
} TEMPLATE_MATCHING_TI_Method;

/**

  @struct TEMPLATE_MATCHING_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          template matching transform applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in pixels of the unsigned 8-bits input image

  @param  imgFrameHeight
          Height in number of lines of the unsigned 8-bits input image

  @param  templateWidth
          Width of the 16-bits 0-mean template in Q-format.
          
  @param  templateHeight
          Height of the 16-bits 0-mean template in Q-format.
          
  @param  xDirJump
          Jump in x direction while searching. Ignored at the moment. Always behave as if xDirJump= 1.

  @param  yDirJump
          Jump in y direction while searching. Ignored at the moment. Always behave as if yDirJump= 1.

  @param  method
          Template matching method. Currently only TEMPLATE_MATCHING_TI_NCC supported.

  @param  qShift
          Number of fractional bits of the Q-format used to format the output. qShift=s means Q(32-s).s format.
          For instance qShift=8, means Q24.8 format.
          Note that the greater qShift is, the more precise the outputs are but at the same time, it increases the risk of overflow during computation, leading to incorrect results.

          The following formula can be used to derive a safe value for qShift, for which overflow does not occur:

          qShift= min(7,  floor((22 - log2(templateWidth*templateHeight))/2);

          A value greater than this recommended qShift value can still work, depending on the pixels values of both the template and input images.

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    uint16_t templateWidth;
    uint16_t templateHeight;
    uint8_t xDirJump;
    uint8_t yDirJump;
    uint8_t method;
    uint8_t qShift;
} TEMPLATE_MATCHING_TI_CreateParams;


/**

  @struct TEMPLATE_MATCHING_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules

  @param  activeImgWidth
          Width in bytes of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameWidth + templateWidth - 1)

  @param  activeImgHeight
          Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameHeight + templateHeight - 1)

  @param  outputBlockWidth
          Output block width in number of pixels returned by BAM_createGraph(). That's useful information to understand performance.

  @param  outputBlockheight
          Output block height in number of rows returned by BAM_createGraph(). That's useful information to understand performance.

 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t activeImgWidth;
    uint16_t activeImgHeight;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} TEMPLATE_MATCHING_TI_outArgs;

/**

  @struct TEMPLATE_MATCHING_TI_ControlInParams
  @brief  This structure contains all the input parameters which controls
          the applet after creation. 
          In the case of template matching, it does not have any additional parameters
          than the default algParams from which it inherits the content.

  @param  algParams
          Common params for all IALG based modules

 */
typedef struct
{
    IALG_Params algParams;
} TEMPLATE_MATCHING_TI_ControlInParams;

/**

  @struct TEMPLATE_MATCHING_TI_ControlOutputParams
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
    
} TEMPLATE_MATCHING_TI_ControlOutParams;

/*@}*/
/* iTEMPLATE_MATCHING */

#endif /*ITEMPLATE_MATCHING_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


