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
 *  @file       isoft_isp_ti.h
 *
 *  @brief      This file defines the ivision interface for software Image
 *              Signal Processor (ISP) applet
 *
 *  @version 0.1 (April 2014) : Base version.
 */

/** @ingroup    ti_ivision_SOFT_ISP */
/*@{*/
#ifndef ISOFT_ISP_TI_H_
#define ISOFT_ISP_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the SOFT_ISP_TI.
 */
extern const IVISION_Fxns SOFT_ISP_TI_VISION_FXNS;

/**
* @brief IRES interface of the SOFT_ISP_TI algorithm
*/
extern const IRES_Fxns SOFT_ISP_TI_IRES;

/**
  @brief Extended error codes for the SOFT_ISP_TI algorithm

  ISOFT_ISP_ERRORTYPE_INVALID_IMAGE_DIM
  Input image dimensions, either imageWidth or imageHeight, provided during
  create-time is not a multiple of 2 for the input RCCC image.

*/
typedef enum
{
  ISOFT_ISP_ERRORTYPE_INVALID_IMAGE_DIM = IALG_CUSTOMFAILBASE,
  ISOFT_ISP_ERRORTYPE_UNSUPPORTED_STAT_BLK_DIM,
  ISOFT_ISP_ERRORTYPE_STAT_BLK_TOO_BIG
} ISOFT_ISP_ErrorType;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  SOFT_ISP_TI_BUFDESC_IN_RCCC_IMAGE
  This buffer descriptor (inBufs->bufDesc[SOFT_ISP_TI_BUFDESC_IN_RCCC_IMAGE])
  provides the input RCCC image data expected by applet. The input image is
  expected to be of 16-bit per pixel.

*/
typedef enum
{
  SOFT_ISP_TI_BUFDESC_IN_RCCC_IMAGE = 0,
  SOFT_ISP_TI_BUFDESC_IN_TOTAL
} ISoftIsp_InBufOrder;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE
  This buffer descriptor (outBufs->bufDesc[SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE])
  should point to a buffer capable of holding the SOFT ISP clear pixel output.
  The output is in 8-bit per pixel format.

  SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF
  This buffer descriptor should point to a buffer capable of holding statistics
  from the input image. This buffer needs to be provided if the algorithm
  object was created with enableStats flag enabled.  If the flag was disabled
  during create time then the content of this buffer descriptor won't be used.

  SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE
  This buffer descriptor should point to a buffer for holding the R pixels
  extracted from the input frame. The output R pixels values will be of
  8-bits per pixel. This buffer needs to be provided if the algorithm
  object was created with enableExtractR flag enabled.  If the flag was
  disabled during create time then the content of this buffer descriptor
  won't be used. Also note that the buffer descriptor for R Image should
  always be the third buffer descriptor in the buffer descriptor list
  irrespective of whether the statistics buffer descriptor is present or not.

*/
typedef enum
{
  SOFT_ISP_TI_BUFDESC_OUT_CCCC_IMAGE = 0,
  SOFT_ISP_TI_BUFDESC_OUT_STATS_BUF,
  SOFT_ISP_TI_BUFDESC_OUT_R_IMAGE,
  SOFT_ISP_TI_BUFDESC_OUT_TOTAL
} ISoftIsp_OutBufOrder;

/**
  @brief Control Command indices for the SOFT_ISP_TI algorithm

  TI_SOFT_ISP_CONTROL_GET_BUF_SIZE
  The algorithm expects the input and output buffers to be satisfy certain
  contraints. These details are communicated to the user using a control
  call with this index. Given the input create time parameters, the control
  call return the buffer constraints through the output parameters of
  SOFT_ISP_TI_CreateParams structure.

*/
typedef enum
{
  TI_SOFT_ISP_CONTROL_GET_BUF_SIZE,
  TI_SOFT_ISP_CONTROL_MAX
} TI_SOFT_ISP_ControlCommand;


/**

  @struct SOFT_ISP_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          SOFT_ISP applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imageWidth
          Width in pixels for the input image

  @param  imageHeight
          Height in number of lines for the input image

  @param  enableExtractR
          Flag to indicate whether R pixels needs to be extracted or not.

  @param  enableStats
          Flag to indicate whether Statistics Collector needs to
          be enabled for the current object or not.

  @param  statBlkWidth
          Block width at which statistics needs to be collected.

  @param  statBlkHeight
          Block height at which statistics needs to be collected.

  @param  minInputBufHeight
          Minimum height expected for input buffer. The algorihtm will
          access the extra lines after valid imageHeight during
          processing, but the image content there will not effect the
          final output.

  @param  extraInputMem
          Extra number of bytes required after the last valid input
          pixel (for a buffer size of imageWidth by imageHeight).

  @param  minOutputBufStride
          Minimum output buffer stride (in bytes) expected to be provided
          to hold the output for the given input image dimension.

  @param  minOutputBufHeight
          Minimum height of the output buffer to hold processed output
          for the given input image dimension.

  @param  statBufWidth
          Width of the statistics buffer in bytes

  @param  statBufHeight
          Height of the statistics buffer

  @param  statBufStride
          Minimum stride required for the statistics buffer.

*/
typedef struct
{
  IVISION_Params visionParams;
  uint16_t       imageWidth;
  uint16_t       imageHeight;
  uint8_t        enableExtractR;
  uint8_t        enableStats;
  uint16_t       statBlkWidth;
  uint16_t       statBlkHeight;

  /* Output parameters */
  uint16_t       minInputBufHeight;
  uint16_t       extraInputMem;
  uint16_t       minOutputBufStride;
  uint16_t       minOutputBufHeight;
  uint16_t       statBufWidth;
  uint16_t       statBufHeight;
  uint16_t       statBufStride;
} SOFT_ISP_TI_CreateParams;


/**

  @struct SOFT_ISP_TI_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to Software ISP applet.

  @param  iVisionInArgs
          Common inArgs for all ivison based modules

  @param  updateToneCurve
          This flag indicates whether the GBCE tone curve needs to be updated for
          the current process call. If the flag is set to 1, the tone curve at
          pGbceToneCurve will be used for brightness and contrast enhancement.
          Else, the tone curve from previous frame will be reused. Note that for
          the very first frame this flag needs to be set to 1. Also the flag needs
          to be set whenever EVE is shared by any other applet or algorithm (in
          between any two process calls of soft ISP) even if the GBCE tone curve
          has not changed.

  @param  pGbceToneCurve
          This points to the buffer containing the tone curve to be used for Global
          Brightness and Contrast Enhancement (GBCE). The tone curve needs to be of
          size 4*4096 bytes. The original tone curve is of 4096 bytes and the factor
          4 indicates the replication required by EVE. Refer to Applet User Guide for
          more details on format of replication.

  @param  sensorBitDepth
          Maximum number of bits required to represent the pixel values. In case
          decomapnading is enabled, i.e. sensor provides companded image, this
          should represent the bit-depth of the decompanded (linearized) pixel
          values.

  @param  rPosition
          Location of the R pixel in the RCCC paxel. The location needs to be
          specified w.r.t the pixel at (frameROI.topLeft.x, frameROI.topLeft.y).
          Possible values are 1, 2, 3 and 4. 1 stands for RCCC, 2 for CRCC,
          3 for CCRC and 4 for CCCR.

  @param  enableDecompand
          Flag to indicate whether sensor data needs to be decompanded or not
          for the current frame. The decompand the sensor data is supported
          only if the companding is piece-wise linear with 3 segments (or
          2 knee-points).

  @param  pout1
          Sensor output at first knee-point in the piece-wise linear response.

  @param  pout2
          Sensor output at second knee-point in the piece-wise linear response.

  @param  slope1
          Slope of the decompanding piece-wise linear curve between the two
          knee points.

  @param  slope2
          Slope of the decompanding piece-wise linear respose after the second
          knee point.

  @param  blackClamp
          The dark current values to be subtracted from each paxel. This is
          an array of 4 values. The four values corresponds to the 4 locations
          in a paxel.

  @param  cBalanceGain
          Gain to be applied to each of the 4 pixels in a paxel. An array of 4
          16-bit values are expected. The value to be programmed is equal to
          the actual gain multiplied by 2^(cBalanceShift).

  @param  cBalanceShift
          The shift (right shift) required to scale down the cBalanceGain values.

  @param  enableExtractR
          Flag to indicate whether R pixels needs to be extracted or not for the
          current frame. This will have effect only if enableExtractR was enabled
          during create time.

  @param  gbceMethod
          This indicates the method to be employed for GBCE computation. There
          are two supported methods - GBCE simple and GBCE interpolated. In GBCE
          simple the pixel value, if more than 12 bits, is truncated to 12-bit
          before looking up in the LUT. In the interpolated GBCE method, the
          output is the result of bilinear interpolation from the two nearby
          entries in the 12-bit LUT. The value 0 stands for simple GBCE and 1
          for interpolated GBCE.

  @param  enableStats
          Flag to indicate whether Statistics Collector needs to
          be enabled for the current frame or not. This will have eeffect only
          if enableStats was enabled during create time.

  @param  saturationLimit
          Pixel value beyond which the pixel will be considered as saturated
          during statistics collection.

*/
typedef struct
{
  IVISION_InArgs iVisionInArgs;
  uint8_t        updateToneCurve;
  uint8_t       *pGbceToneCurve;

  uint8_t        sensorBitDepth;
  uint8_t        rPosition;
  /* Decompanding parameters */
  uint8_t        enableDecompand;
  uint16_t       pout1;
  uint16_t       pout2;
  uint8_t        slope1;
  uint16_t       slope2;
  /* Black clamp and C balance */
  uint16_t       blackClamp[4];
  uint16_t       cBalanceGain[4];
  uint8_t        cBalanceShift;
  /* Extract R pixels */
  uint8_t        enableExtractR;
  /* GBCE parameter */
  uint8_t        gbceMethod;
  /* Stats Collection parameters */
  uint8_t        enableStats;
  uint16_t       saturationLimit;

} SOFT_ISP_TI_InArgs;


/**

  @struct SOFT_ISP_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by Software ISP applet.

  @param  visionParams
          Common outArgs for all ivison based modules

*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
} SOFT_ISP_TI_OutArgs;


/*@}*/
/* ti_ivision_SOFT_ISP */

#endif /*ISOFT_ISP_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

