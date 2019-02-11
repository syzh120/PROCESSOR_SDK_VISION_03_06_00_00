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


#ifndef CONVERTMAP_H
#define CONVERTMAP_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint.h>
#include "remap_common.h"


/*!

  @struct convertMapBlockInfo

  @brief  This structure contains the parameters which assist Remap module to
          perform block level Pixel Remap. It is produced by convert map module
          and cosumed by Remap.


  @param collectStatFlag [In]
         0: do not collect statistics, 1: collect statistics
  @param maxWidthRatio  [out]
         maximum of all the ratios between input block's width output block's
         width is returned here
  @param minWidthRatio  [out]
         minimum of all the ratios between input block's width output block's
         width is returned here
  @param averWidthRatio [out]
         average of all the ratios between input block's
         width output block's width is returned here
  @param maxHeightRatio [out]
         maximum of all the ratios between input block's height
         output block's height is returned here
  @param minHeightRatio [out]
         minimum of all the ratios between input block's height
         output block's height is returned here
  @param averHeightRatio[out]
         average of all the ratios between input block's height
         output block's height is returned here

*/

typedef struct {
    uint8_t collectStatFlag;
    float maxWidthRatio;
    float minWidthRatio;
    float averWidthRatio;
    float maxHeightRatio;
    float minHeightRatio;
    float averHeightRatio;
} RemapStat;


/*!

  @func convertMap_tileApproach_getMemorysizeBlockMap

  @brief  This function retruns the memory size needed by Block Map

*/
int32_t convertMap_tileApproach_getMemorysizeBlockMap(sConvertMap *maps);


/*!

  @func convertMap_tileApproach

  @brief  This function perform the LUT table conversion from Frame format
          to block format
  @param  maps [In]
          It is pointer to memory are to hold block level LUT
          @sa sConvertMap
  @param  stat
          It is pointer to memory are to hold Statistics for Remap
          @sa RemapStat
@param  enableMerge
          It is a Boolean to input if Merge is enabled. It will be used for optimization.
          @sa uint8_t

*/
int32_t convertMap_tileApproach(sConvertMap *maps, RemapStat *stat, void *memLUT, uint8_t enableMerge);


/*!

  @func convertMap_tileApproach_getMemorysizeBlockMap

  @brief  This function retruns the memory size needed by Block Map

*/
int32_t convertMap_bbApproach_getMemorysizeBlockMap(sConvertMap *maps);


/*!

  @func convertMap_tileApproach

  @brief  This function perform the LUT table conversion from Frame format
          to block format
  @param  maps [In]
          It is pointer to memory are to hold block level LUT
          @sa sConvertMap
  @param  stat
          It is pointer to memory are to hold Statistics for Remap
          @sa RemapStat
@param  enableMerge
          It is a Boolean to input if Merge is enabled. Will be used to calculate memory availability.
          @sa uint8_t

*/
int32_t convertMap_bbApproach(sConvertMap *maps, RemapStat *stat, void *memLUT);


#ifdef __cplusplus
 }
#endif

#endif
