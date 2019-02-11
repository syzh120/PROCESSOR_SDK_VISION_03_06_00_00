/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2016 - 2017 Texas Instruments Incorporated          |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VXLIB_MINMAXLOC_I8U_H_
#define VXLIB_MINMAXLOC_I8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_minMaxLoc_i8u */
/** @ingroup  VXLIB_minMaxLoc_i8u */
/* @{ */
/**
 * @par Description:
 *  Finds the minimum and maximum values in an image and a location for each.
 *
 * @par Method:
 *  The minimum and maximum is found in a first pass through the image.
 *  The minCount and maxCounts are optionally found in a second pass through the image
 *  The minLoc and maxLoc list of pixel coordinates are optionally found in a third pass
 *  through the image. 
 *
 * @verbatim

    minVal = min(src(x',y')) where 0 <= x' < width, 0 <= y' < height
    maxVal = max(src(x',y')) where 0 <= x' < width, 0 <= y' < height

   @endverbatim
 *
 *
 * @par
 *   @param [in]      src[]              Pointer to array containing input image (UQ8.0)
 *   @param [in]      src_addr[]         Pointer to structure containing dimensional information of src
 *   @param [in,out]  *pMinVal           Minimum value in the image
 *   @param [in,out]  *pMaxVal           Maximum value in the image
 *   @param [in,out]  *pMinCount         Total number of detected minimum values in the image (optional)
 *   @param [in,out]  *pMaxCount         Total number of detected maximum values in the image (optional)
 *   @param [in]      minLocCapacity     Allocated array size of minLoc array.
 *   @param [in]      maxLocCapacity     Allocated array size of maxLoc array.
 *   @param [in,out]  minLoc[]           Coordinates of minimum values in the image (x,y) (optional)
 *   @param [in,out]  maxLoc[]           Coordinates of maximum values in the image (x,y) (optional)
 *   @param [in]      startX             Starting x coordinate in the image corresponding to the src pointer
 *   @param [in]      startY             Starting y coordinate in the image corresponding to the src pointer
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - PARAMETER INITIALIZATION:
 *        - pMinVal and pMaxVal should be externally initialized to 0xff and 0x00, respectively,
 *          before calling the function for the first time for each image.
 *        - If the optional parameters pMinCount or pMaxCount are to be passed (not set to NULL), then
 *          they each need to be externally initialized to 0 before calling the function for the first
 *          time for each image.
 *        - The reason the above parameters are not internally initialized is in case a user wants to
 *          divide processing of the image into smaller pieces, and call this function for each piece.
 *          In this case, the external intitialization only needs to happen on the first block of the image, and
 *          the same parameters can be updated internally by subsequent blocks.
 *        - startX and startY may be non-zero when the user sets minLoc or maxLoc pointers to non-NULL values, AND
 *          divides the processing of the image into smaller pieces.
 *    - PARAMETER DEPENDENCIES:
 *        - if minLoc is non-NULL, then pMinCount should be non-NULL so that the user knows how much of the array
 *          was filled.  If the pMinCount returned is > minLocCapacity, then there are only minLocCapacity items
 *          filled in the array.
 *        - if maxLoc is non-NULL, then pMaxCount should be non-NULL so that the user knows how much of the array
 *          was filled.  If the pMaxCount returned is > maxLocCapacity, then there are only maxLocCapacity items
 *          filled in the array.
 *        - if minLoc is NULL, then minLocCapacity is ignored by the function
 *        - if maxLoc is NULL, then maxLocCapacity and startX parameters are ignored by the function
 *        - if minLoc and maxLoc are both NULL then startX and startY parameters are also ignored by the function
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - Set widths equal to strides
 *      - Set all stride values to a multiple of 8
 *      - Set all width values to a multiple of 8
 *      - The highest performing mode is when all the "optional" parameters are set to NULL, such that only min
 *        and max values are found.
 *      - The second highest performing mode is when the minLoc and maxLoc pointers are set to NULL, such that
 *        only min and max values and counts are found, not the locations.
 * 
 */
VXLIB_STATUS    VXLIB_minMaxLoc_i8u(const uint8_t src[restrict],
                                 const VXLIB_bufParams2D_t * src_addr,
                                 uint8_t * pMinVal,
                                 uint8_t * pMaxVal,
                                 uint32_t * pMinCount,
                                 uint32_t * pMaxCount,
                                 size_t minLocCapacity,
                                 size_t maxLocCapacity,
                                 uint32_t minLoc[restrict],
                                 uint32_t maxLoc[restrict],
                                 uint16_t startX,
                                 uint16_t startY);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_minMaxLoc_i8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - src, pMinVal, and pMaxVal shall not have NULL pointers
 *    - The strides of each image shall be equal to or greater than the x dimension
 *
 * @par
 *   @param [in]  src[]        Pointer to array containing input image (UQ8.0)
 *   @param [in]  src_addr[]   Pointer to structure containing dimensional information of src
 *   @param [in]  *pMinVal     Minimum value in the image
 *   @param [in]  *pMaxVal     Maximum value in the image
 *
 */
VXLIB_STATUS    VXLIB_minMaxLoc_i8u_checkParams(const uint8_t src[],
                                             const VXLIB_bufParams2D_t * src_addr,
                                             const uint8_t *pMinVal,
                                             const uint8_t *pMaxVal);
/** @} */
#endif

