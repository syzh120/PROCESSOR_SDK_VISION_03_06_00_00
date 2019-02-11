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
 *  @file       iCensus_ti.h
 *
 *  @brief      This file defines the ivision interface for census transform Applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    iCENSUS */
/*@{*/
#ifndef ICENSUS_TI_H
#define ICENSUS_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

/**
 * @brief Macro symbols used as command passed to the control API
 */
#define CENSUS_GET_OUTPUT_BLOCK_DIM 0x0 /* Get output block's dimensions (width & height) derived during applet creation */

/**
 * @brief Macro symbols used as error code returned by the alloc init, process, control or deinit APIs.
 *
 *  CENSUS_ERROR_INVALID_ROI_DIM: One of the ROI dimensions (width/height) passed to process API is not multiple of the output block width/height
 *
 */
typedef enum
{
    CENSUS_ERROR_INVALID_ROI_DIM = IALG_CUSTOMFAILBASE
} CENSUS_TI_ErrorCodes ;
#define CENSUS_ERROR_INVALID_ROI_DIM (-256) /* One of the ROI dimensions (width/height) passed to process API is not multiple of the output block width/height */ 
/**
 * @brief The unique const funtion table for the CENSUS_TI.
 */
extern const IVISION_Fxns CENSUS_TI_VISION_FXNS;

/**
 * @brief IRES interface of the CENSUS_TI_ algorithm
 */
extern const IRES_Fxns CENSUS_TI_IRES;

/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of buffer
            There is 1 input buffers descriptor
            
            CENSUS_BUFDESC_IN: This buffer descriptor provides the
            actual left image data required by algorithm. The data is composed of 8-bits or 16-bits data
            
*/
typedef enum 
{
    CENSUS_BUFDESC_IN = 0,
    CENSUS_BUFDESC_IN_TOTAL
} CENSUS_InBufOrder ;
   
/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of out buffer
            There is 1 output buffers descriptor
            
            CENSUS_BUFDESC_OUT: This buffer is filled up by the algorithm and will contain 
            the census codewords. Number of bytes to be allocated is computed as follow:
            imageFrameWidth * imageFrameHeight * numBytesPerCensus
            where numBytesPerCensus= ( ((winWidth + winHorzStep -1) / winHorzStep )*(( winHeight + winVertStep -1) /winVertStep ) + 7)/8
*/
typedef enum 
{
    CENSUS_BUFDESC_OUT = 0,
    CENSUS_BUFDESC_OUT_TOTAL
} CENSUS_OutBufOrder ;

/**

  @struct CENSUS_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          census transform applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in pixels for the input image

  @param  imgFrameHeight
          Height in number of lines for the input image

  @param  inputBitDepth
          Bit depth of the input (8 or 16 supported)

  @param  winWidth
          Width of the support window, that defines the neighborhood in which census transform is applied around each pixel.
          
  @param  winHeight
          Height of the support window, that defines the neighborhood in which census transform is applied around each pixel.
          
  @param  winHorzStep
          Horizontal step between each orientation in the support window. Typically 1 or 2. 
          
  @param  winVertStep
          Vertical step between each orientation in the support window. Typically 1 or 2.
          
 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    uint8_t inputBitDepth;
    uint8_t winWidth;
    uint8_t winHeight;
    uint8_t winHorzStep;
    uint8_t winVertStep;
} CENSUS_TI_CreateParams;


/**

  @struct CENSUS_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules

  @param  activeImgWidth
          Width in bytes of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameWidth + TOTAL_FILTER_SZ)

  @param  activeImgHeight
          Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameHeight + TOTAL_FILTER_SZ)

  @param  outputBlockWidth
          Output block width in number of pixels returned by BAM_createGraph(). That's useful information to understand performance.

  @param  outputBlockheight
          Output block height in number of rows returned by BAM_createGraph(). That's useful information to understand performance.

  @param  codeWordLen
          Census transform codeword's length in bytes
 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t activeImgWidth;
    uint16_t activeImgHeight;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;
    uint8_t numBytesPerCensus;

} CENSUS_TI_outArgs;

/**

  @struct CENSUS_TI_ControlInParams
  @brief  This structure contains all the input parameters which controls
          the applet after creation. 
          In the case of Census transform, it does not have any additional parameters
          than the default algParams from which it inherits the content.

  @param  algParams
          Common params for all IALG based modules

 */
typedef struct
{
    IALG_Params algParams;
} CENSUS_TI_ControlInParams;

/**

  @struct CENSUS_TI_ControlOutputParams
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
    
} CENSUS_TI_ControlOutParams;

/*@}*/
/* iCENSUS */

#endif /*ICENSUS_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


