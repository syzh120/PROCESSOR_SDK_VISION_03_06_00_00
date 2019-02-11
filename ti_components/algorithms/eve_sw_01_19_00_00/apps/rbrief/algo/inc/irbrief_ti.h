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
 *  @file       irbrief_ti.h
 *
 *  @brief      This file defines the ivision interface for rBRIEF descriptor
 *              generation applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    ti_ivision_RBRIEF */
/*@{*/
#ifndef IRBRIEF_TI_H_
#define IRBRIEF_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the RBRIEF_TI.
 */
extern const IVISION_Fxns RBRIEF_TI_VISION_FXNS;

/**
* @brief IRES interface of the RBRIEF_TI_ algorithm
*/
extern const IRES_Fxns RBRIEF_TI_IRES;

/**
* @brief Maximum number of features allowed by this applet
*/
#define RBRIEF_TI_MAXNUMFEATURES   (2048U)

/**
* @brief Size of feature descripter in bytes
*/
#define RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE (32U)


/**
* @brief Using iVISION buf planes to get multiple pyramid so max value
         allowed (4) is depedant on iVISION
*/
#define RBRIEF_TI_MAXLEVELS   (IVISION_MAX_NUM_PLANES)

typedef enum
{
  IRBRIEF_ERRORTYPE_MAXNUMFEATURES_EXCEEDED = IVISION_CUSTOMFAILBASE

} IRBRIEF_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There are 3 input buffers descriptor

  RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet. This applet works on multi level so
  user can provide multiple buffers. Lets say this applet is used for
  3 levels of image pyramid. then user should provide
  inBufs->bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->numPlanes = 3
  and
  inBufs->bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[level] contains
  the details of each planes buffer pointer and dimensions

  RBRIEF_TI_BUFDESC_IN_XY_LIST:
  This buffer descriptor (inBufs->bufDesc[RBRIEF_TI_BUFDESC_IN_XY_LIST])
  should point to a  plane containing list of XY. It is user responsbility to
  have the X and Y list to have valid data which points in image region excluding
  24 pixels boarder on each side. The applet doesn't perfrom any check for this
  condition and the behavior is undefined if it is not satisfied

  RBRIEF_TI_BUFDESC_IN_LEVEL_ID:
  This buffer descriptor (inBufs->bufDesc[RBRIEF_TI_BUFDESC_IN_LEVEL_ID]) should
  point to a plane containing list of level corresponding to XY list.
  It is user responsbility to have the level list to  have valid data. the level
  buffer should not have any value which is higher than
  inBufs->bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->numPlanes - 1

*/


typedef enum
{
  RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  RBRIEF_TI_BUFDESC_IN_XY_LIST,
  RBRIEF_TI_BUFDESC_IN_LEVEL_ID,
  RBRIEF_TI_BUFDESC_IN_TOTAL
} IRBRIEF_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC:
  This  buffer is filled up by applet and have 256 point descriptor for each
  point in the same order as XY and Level list. so the size of this buffer is
  RBRIEF_TI_MAXNUMFEATURES*(256/8) bytes
*/

typedef enum
{
  RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC = 0,
  RBRIEF_TI_BUFDESC_OUT_TOTAL
} IRBRIEF_OutBufOrder ;


/**

  @struct RBRIEF_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          rBrief applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxNumFeatures
          Number of max Features for which the applet will be used
          User can configure any value <= RBRIEF_TI_MAXNUMFEATURES

  @param  orbPattern
          This pattern defines the position of 256 pairs of src and dst
          to create 256 bit rBRIEF descriptor. Total size of this memory
          are has to be 256*4. For Exact format of this pattern - refer the
          User guide and test bench of this applet

  @param xyListInDmem
          This flag indicates whether xy list is already in DMEM, if not this applet
          will first copy the list in DMEM. Value of 0 indidcates list is in DDR and 1
          indicates the list is in DMEM.

  @param levelListInDmem
          This flag indicates whether level list is already in DMEM, if not this applet
          will first copy the list in DMEM. Value of 0 indidcates list is in DDR and 1
          indicates the list is in DMEM

*/
typedef struct
{
  IVISION_Params visionParams;
  uint16_t       maxNumFeatures;
  const int8_t *orbPattern ;
  uint8_t       xyListInDmem;
  uint8_t       levelListInDmem;
} RBRIEF_TI_CreateParams;


/**

  @struct RBRIEF_TI_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by rBRIEF applet.

  @param  visionParams
          Common outArgs for all ivison based modules

*/

typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
} RBRIEF_TI_OutArgs;

/*@}*/
/* ti_ivision_RBRIEF */

#endif /*IRBRIEF_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


