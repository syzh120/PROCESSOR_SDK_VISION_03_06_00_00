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
*  @file:       iblock_statistics_ti.h
*
*  @brief:      This file defines the ivision interface for Block Statistics
*               applet
*
*  @version:    0.2 (Aug 2014) : Base version.
*/

/** @ingroup    ti_iBLOCK_STATISTICS */
/*@{*/

#ifndef IBLOCK_STATISTICS_TI_H
#define IBLOCK_STATISTICS_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the BLOCK_STATISTICS_TI.
 */
extern const IVISION_Fxns BLOCK_STATISTICS_TI_VISION_FXNS;

/**
* @brief IRES interface of the BLOCK_STATISTICS_TI algorithm
*/
extern const IRES_Fxns BLOCK_STATISTICS_TI_IRES;


typedef enum
{
  BLOCK_STATISTICS_TI_ERRORTYPE_INSUFFICIENT_MEMORY = IALG_CUSTOMFAILBASE

} BLOCK_STATISTICS_TI_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  image data for which statistics is required to be computed by the applet. The
  input image should be of uint8_t data type.

*/

typedef enum
{
  BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  BLOCK_STATISTICS_TI_BUFDESC_IN_TOTAL
} BLOCK_STATISTICS_TI_InBufOrder;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN]) should point to a buffer capable of
  holding the block minimum output. This buffer should be of uint8_t type.

  BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX]) should point to a buffer capable of
  holding the block maximum output. This buffer should be of uint8_t type.

  BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN]) should point to a buffer capable of
  holding the block mean output. This buffer should be of uint16_t type.

  BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE]) should point to a buffer capable of
  holding the block variance output. This buffer should be of uint32_t type.
*/

typedef enum
{
  BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN = 0,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_TOTAL
} BLOCK_STATISTICS_TI_OutBufOrder;

/**
  @struct BLOCK_STATISTICS_TI_CreateParams

  @brief  This structure contains all the parameters which controls
          BLOCK_STATISTICS applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imageWidth
          Width in pixels of the input image

  @param  imageHeight
          Height of the input image

  @param  statBlockWidth
          Width of the block over which statistics has to be computed

  @param  statBlockHeight
          Height of the block over which statistics has to be computed
*/

typedef struct
{
  IVISION_Params visionParams;
  uint16_t       imageWidth;
  uint16_t       imageHeight;
  uint16_t       statBlockWidth;
  uint16_t       statBlockHeight;
} BLOCK_STATISTICS_TI_CreateParams;

/*@}*/
/* ti_iBLOCK_STATISTICS */

#endif  /* IBLOCK_STATISTICS_TI_H */
