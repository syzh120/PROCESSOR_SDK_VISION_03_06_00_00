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
 *  @file        iremap_merge_ti.h
 *
 *  @brief      This file defines the ivision interface for Remap Merge Applet
 *  @version 0.0 (January, 2014) : Base version.
 */

/** @ingroup    ti_ivision_REMAP_MERGE */
/*@{*/
#ifndef IREMAP_MERGE_TI_H
#define IREMAP_MERGE_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

#include "remap_common.h"

#ifdef __cplusplus
    extern "C" {
#endif

/**
 * @brief The unique const funtion table for the REMAP_MERGE_TI.
 */
extern const IVISION_Fxns REMAP_MERGE_TI_VISION_FXNS;

/**
* @brief IRES interface of the REMAP_MERGE_TI_ algorithm
*/
extern const IRES_Fxns REMAP_MERGE_TI_IRES;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer
         There only 1 input buffers descriptor needed by this applet

  REMAP_MERGE_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet.

  REMAP_MERGE_TI_BUFDESC_IN_LUTBUFFER: This buffer descriptor provides the
  Look up Table required by applet.

  REMAP_MERGE_TI_BUFDESC_IN_MERGEBUFFER: This buffer descriptor provides the
  merge frame required by applet.

  REMAP_MERGE_TI_BUFDESC_IN_ALPHABUFFER: This buffer descriptor provides the
  alpha frame required by applet.

  REMAP_MERGE_TI_BUFDESC_IN_REMAP_TOTAL: Total number of Remap buffer descriptors
  when Merge is not enabled.

  REMAP_MERGE_TI_BUFDESC_IN_REMAP_MERGE_TOTAL: Total number of Remap buffer descriptors
  when Merge is enabled.

*/
typedef enum
{
  REMAP_MERGE_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  REMAP_MERGE_TI_BUFDESC_IN_LUTBUFFER   = 1,
  REMAP_MERGE_TI_BUFDESC_IN_MERGEBUFFER = 2,
  REMAP_MERGE_TI_BUFDESC_IN_ALPHABUFFER = 3,
  REMAP_MERGE_TI_BUFDESC_IN_REMAP_TOTAL = REMAP_MERGE_TI_BUFDESC_IN_LUTBUFFER + 1U,
  REMAP_MERGE_TI_BUFDESC_IN_REMAP_MERGE_TOTAL = REMAP_MERGE_TI_BUFDESC_IN_ALPHABUFFER + 1U
} IREMAP_MERGE_InBufOrder ;

/**
  @brief User provides most of the information through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER: This buffer descriptor provides the
  image output generated by applet.

*/

typedef enum
{
  REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER = 0,
  REMAP_MERGE_TI_BUFDESC_OUT_TOTAL
} IREMAP_MERGE_OutBufOrder ;


/**

  @struct REMAP_MERGE_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          Remap and Merge applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  remapParams
          param structure to configure Remap

  @param  enableMerge
          Boolean to enable and disable Alpha Blend

  @param  dstFormat
          Format of output.
*/
typedef struct
{
  IVISION_Params visionParams;
  RemapParms     remapParams;
  uint8_t        enableMerge;
  Format         dstFormat;

} REMAP_MERGE_TI_CreateParams;


#ifdef __cplusplus
 }
#endif

/*@}*/
/* ti_ivision_REMAP_MERGE */

#endif /*IREMAP_MERGE_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


