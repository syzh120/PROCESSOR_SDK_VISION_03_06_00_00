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
 *  @file       ibin_image_to_list_ti.h
 *
 *  @brief      This file defines the ivision interface for Binary Image to List
 *               applet
 *  @version 0.0 (Apr 2015) : Base version.
 */

/** @ingroup    ti_ivision_BIN_IMAGE_TO_LIST */
/*@{*/
#ifndef IBIN_IMAGE_TO_LIST_TI_H_
#define IBIN_IMAGE_TO_LIST_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the BIN_IMAGE_TO_LIST_TI.
 */
extern const IVISION_Fxns BIN_IMAGE_TO_LIST_TI_VISION_FXNS;

/**
* @brief IRES interface of the BIN_IMAGE_TO_LIST_TI_ algorithm
*/
extern const IRES_Fxns BIN_IMAGE_TO_LIST_TI_IRES;

#define BIN_IMAGE_TO_LIST_TI_MAX_QFORMAT (5U)

typedef enum
{
  BIN_IMAGE_TO_LIST_TI_ERRORTYPE_FORMAT_UNSUPPORTED = IALG_CUSTOMFAILBASE,
  BIN_IMAGE_TO_LIST_TI_ERRORTYPE_QFORMAT_NOT_FEASIBLE,
  BIN_IMAGE_TO_LIST_TI_ERRORTYPE_WIDTH_NON_MULTIPLE_OF_8,
  BIN_IMAGE_TO_LIST_TI_ERRORTYPE_IMAGE_DIMENSION_UNSUPPORTED,
  BIN_IMAGE_TO_LIST_TI_ERRORTYPE_IMAGE_DIMENSION_MISMATCH,
  BIN_IMAGE_TO_LIST_TI_ERRORTYPE_MAX_ERROR_CODE
} BIN_IMAGE_TO_LIST_TI_ErrorType;

/*
 *  @brief  Input format supported
 */
typedef enum
{
  BIN_IMAGE_TO_LIST_TI_INPUT_DATA_FORMAT_BIT_PACKED = 0,
  BIN_IMAGE_TO_LIST_TI_INPUT_DATA_FORMAT_MAX
} BIN_IMAGE_TO_LIST_TI_InputDataFormat;

/**
  @brief Enums to select the order of x and y in the output buffer

  BIN_IMAGE_TO_LIST_TI_ORDER_XY:
    Output will have X coordinate (upper 16 bit )followed by Y
  coordinate (lower 16 bits) for each  edge point. Each X or Y is a 16  bit entry.

   BIN_IMAGE_TO_LIST_TI_ORDER_YX:
     Output will have Y coordinate (upper 16 bit )followed by X
   coordinate (lower 16 bits) for each  edge point. Each X or Y is a 16  bit entry.

*/

typedef enum
{
  BIN_IMAGE_TO_LIST_TI_ORDER_XY = 0,
  BIN_IMAGE_TO_LIST_TI_ORDER_YX
} BIN_IMAGE_TO_LIST_TI_Order ;

/*
 *  @brief  Enums to select the format of input mask image
 BIN_IMAGE_TO_LIST_TI_INPUT_MASK_FORMAT_BYTE_MAP:
    Input mask is a byte mask with 1 at all byte locations where user want to detect corners
    and 0 at other byte location.

 */
typedef enum
{
  BIN_IMAGE_TO_LIST_TI_INPUT_MASK_FORMAT_BYTE_MAP = 0,
  BIN_IMAGE_TO_LIST_TI_INPUT_MASK_FORMAT_MAX
} BIN_IMAGE_TO_LIST_TI_InputMaskFormat;

/**
  @brief Following enums should be used to select the method to be
            used when enableListSuppression in BIN_IMAGE_TO_LIST_TI_CreateParams
            is enabled
  BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_PERCENTAGE:
           In this method the list suppression is based on the percentage of list elements
           user wants to be pick from all the detected number of points. Percentage value
           should be provided via suppressionValue parameter present in BIN_IMAGE_TO_LIST_TI_InArgs.
           Value can range from 1 ot 100

   BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE:
           In this method the list suppression is based on the max value given by the user. Final
           number of list points detected will be less than the max value provided by the user.
           Max value should be provided via suppressionValue parameter present in
           BIN_IMAGE_TO_LIST_TI_InArgs.
*/

typedef enum
{
  BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_PERCENTAGE = 0,
  BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE,
  BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_MAX
} BIN_IMAGE_TO_LIST_ListSuppressionMethod ;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER:
  This buffer descriptor (inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER])
   should point to a  buf descriptor pointing to input binary image data which needs to be converted
   to list.  This buffer format is decided by the inputFormat field in createParams. Width should
   be multiple of 8

   BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER:
   This buffer descriptor (inBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER])
   should point to a buf descriptor pointing to the byte mask which needs to be applied to the image.
   Byte mask should contain 1 at location which you want to keep and 0 at other locations. This buffer
   is only required if you are enabling masking using enableMasking field of create params.

  BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL :
  Total number of input buffers
*/

typedef enum
{
  BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_BUFFER = 0,
  BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_MASK_BUFFER,
  BIN_IMAGE_TO_LIST_TI_BUFDESC_IN_TOTAL
} BIN_IMAGE_TO_LIST_TI_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST:
  This buffer descriptor (outBufs->bufDesc[BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST]) should
  point to the output buffer which will contain XY list of the after BIN_IMAGE_TO_LIST with thresholding.
  This list is expected to be in packed 32 bit format with order of X and Y determined by inArgs
  outputListOrder field. Size of this buffer should be the worst case size which will be equal to
  imageWidth * imageHeight * sizeof(uint32_t).
  If user given size of the buffer is less than the above mentioned then applet will return a warning saying
  not enough buffer. It is important to note that for the cases when buffer is not sufficient this applet
  behavior is undefined.
  Size of this buffer should be the worst cases size if suppresion is disabled.
  If suppression is enabled and method is BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE
  then buffer should be of maxSize + 128 to take care of the extra buffer required by the applet

  BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL:
  Total Number of output buffers

*/

typedef enum
{
  BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_LIST = 0,
  BIN_IMAGE_TO_LIST_TI_BUFDESC_OUT_TOTAL
} BIN_IMAGE_TO_LIST_TI_OutBufOrder ;

/**

  @struct BIN_IMAGE_TO_LIST_TI_CreateParams
  @brief  This structure contains all the parameters needed
              at create time for this applet

  @brief  inputDataFormat
             Describes the format of the input data. It could be a byte binary image
             or could be bit packed binary image
             Refer BIN_IMAGE_TO_LIST_TI_InputDataFormat for valid supported enteries

  @brief  inputMaskFormat
             Describes the format of the mask to be applied on the input data. It could be a byte binary image
             or could be bit packed binary image
             Refer BIN_IMAGE_TO_LIST_TI_InputMaskFormat for valid supported enteries

  @brief enableMasking
            User can enable masking by separately providing a byte mask buffer with
            1 at location where it wants to keep the points and 0 at other places

@brief enableListSuppression
          User can enable suppression of the list  by setting the value of this parameter to be 1. If list suppression is enable
          then based on user defined method itnernally we will uniformly downsample the image to reach the number of points
          or the ratio given by the user via BIN_IMAGE_TO_LIST_TI_InArgs

@brief maxImageWidth
          Maximum image width for which this applet will be used

@brief maxImageHeight
          Maximum image height for which this applet will be used
*/

typedef struct
{
  IVISION_Params visionParams;
  uint8_t        inputDataFormat;
  uint8_t        inputMaskFormat;
  uint8_t        enableMasking;
  uint8_t        enableListSuppression;
  uint16_t       maxImageWidth;
  uint16_t       maxImageHeight;
} BIN_IMAGE_TO_LIST_TI_CreateParams;


/**

  @struct BIN_IMAGE_TO_LIST_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to this applet at frame level

  @param  iVisionInArgs
                Common InArgs  for all ivison based modules
  @param  outputListOrder
                The order of X and Y in output List. Refer BIN_IMAGE_TO_LIST_TI_Order for valid vlaues
  @param  outputListQFormat
                The Qformat in which output is expected. The coordinates are shifted by outputListQFormat
                amount while packing the coordinates into list
  @param  startX
                X offset to be added to each X coordinate
  @param  startY
                Y offset to be added to each Y coordinate
  @param listSuppressionMethod
                This parameter is only valid if enableListSuppression is enabled. User can choose
                two kind of suppression method as described in BIN_IMAGE_TO_LIST_ListSuppressionMethod
  @param suppressionValue
               This parameter is only valid if enableListSuppression is enabled. This parameter
               has different meaning based on the listSuppressionMethod selected.
              listSuppressionMethod = BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_PERCENTAGE
                  This parameter should tell the percentage of points which should be picked from all
                  the points detected. A value of 0 will return all the points as detected by the input binary image
              listSuppressionMethod = BIN_IMAGE_TO_LIST_TI_LIST_SUPPRESSION_BY_MAX_VALUE
                   This parameter should be Maximum number of list points required. A value of 0 will return
                   all the points as detected by the input binary image. Otherwise this value will be used to
                   internally uniformly select points from all the points detected.
*/
typedef struct
{
  IVISION_InArgs  iVisionInArgs;
  uint8_t         outputListOrder;
  uint8_t         outputListQFormat;
  uint16_t        startX;
  uint16_t        startY;
  uint8_t         listSuppressionMethod;
  uint32_t        suppressionValue;
} BIN_IMAGE_TO_LIST_TI_InArgs;


/**

  @struct BIN_IMAGE_TO_LIST_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by this applet  at frame level

  @param  iVisionOutArgs
             Common outArgs for all ivison based modules

@param  numListPoints
              Number of points in the list

*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint32_t         numListPoints;
} BIN_IMAGE_TO_LIST_TI_OutArgs;

/*@}*/
/* ti_ivision_BIN_IMAGE_TO_LIST */

#endif /*IBIN_IMAGE_TO_LIST_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

