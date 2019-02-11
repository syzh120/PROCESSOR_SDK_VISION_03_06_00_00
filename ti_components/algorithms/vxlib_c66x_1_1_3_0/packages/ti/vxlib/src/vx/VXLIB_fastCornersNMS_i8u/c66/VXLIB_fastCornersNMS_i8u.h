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

#ifndef VXLIB_FASTCORNERSNMS_I8U_H_
#define VXLIB_FASTCORNERSNMS_I8U_H_ 1

#include "../../../common/VXLIB_types.h"

/** @defgroup VXLIB_fastCornersNMS_i8u */
/** @ingroup  VXLIB_fastCornersNMS_i8u */
/* @{ */
/**
 * @par Description:
 *  Performs the FAST9 non-maximum suppression on a corner list.  
 *
 * @par Method:
 *  Feature is kept if it's strength is >= a feature on the left, and
 *  the 3 features to the top, and it's strength is > a feature on the
 *  right, and the 3 features to the bottom.
 *
 * @par
 *   @param [in]  src_addr[]        Pointer to structure containing dimensional information of src
 *   @param [in]  corners_in[]      Pointer to array containing input corner keypoint list (UQ32.0)
 *   @param [in]  strengths_in[]    Pointer to array containing input strength list, coresponding to corners_in[] (UQ8.0)
 *   @param [in]  num_corners_in    Total number of corners in the corners_in list.
 *   @param [out] corners_out[]     Pointer to array containing output corner keypoint list (UQ32.0)
 *   @param [out] strengths_out[]   Pointer to array containing output strength list, coresponding to corners_out[] (UQ8.0)
 *   @param [out] *num_corners_out  Total number of corners returned in the corners_out list.
 *   @param [in]  scratch[]         Pointer to scratch buffer (UQ8.0)
 *   @param [in]  scratch_size      Size of the scratch buffer (for parameter checking)
 *
 * @par Assumptions:
 *    - I/O buffer pointers are assumed to be not aliased.
 *    - The corners_in[] array is ordered in raster-scan across and image
 *    - Each 32-bit word in corners[] array is composed of 2 16-bit half words representing
 *      x and y coordinates, such that corners[i] = (y(i) << 16) | x(i);
 *    - The strengths_in[] array corresponds to the corners_in list
 *    - The scratch buffer should be 8 byte aligned.
 *    - The scratch buffer should be at least (4 * src_addr->dim_x) + num_corners_in + 15 bytes
 *    - The scratch buffer should be filled with 0s prior to calling the function each time.
 *
 * @par Performance Considerations:
 *    - For best performance, the following parameter settings are recommended:
 *      - When the num_corners_in parameter is a multiple of 4.
 */
VXLIB_STATUS    VXLIB_fastCornersNMS_i8u(const VXLIB_bufParams2D_t * src_addr,
                                      const uint32_t corners_in[],
                                      const uint8_t strengths_in[],
                                      uint32_t num_corners_in,
                                      uint32_t corners_out[],
                                      uint8_t strengths_out[],
                                      uint32_t *num_corners_out,
                                      uint8_t scratch[],
                                      uint32_t scratch_size);

/**
 * @par Description:
 *  Checks the parameters for programming errors for the VXLIB_fastCornersNMS_i8u function.
 *
 * @par Method:
 *  The following checks are made:
 *    - There shall be no NULL pointers
 *
 * @par
 *   @param [in]  src_addr[]        Pointer to structure containing dimensional information of src
 *   @param [in]  corners_in[]      Pointer to array containing input corner keypoint list (UQ32.0)
 *   @param [in]  strengths_in[]    Pointer to array containing input strength list, coresponding to corners_in[] (UQ8.0)
 *   @param [in]  num_corners_in    Total number of corners in the corners_in list.
 *   @param [out] corners_out[]     Pointer to array containing output corner keypoint list (UQ32.0)
 *   @param [out] strengths_out[]   Pointer to array containing output strength list, coresponding to corners_out[] (UQ8.0)
 *   @param [out] *num_corners_out  Total number of corners returned in the corners_out list.
 *   @param [in]  scratch[]         Pointer to scratch buffer (UQ8.0)
 *   @param [in]  scratch_size      Size of the scratch buffer (for parameter checking)
 *
 */
VXLIB_STATUS    VXLIB_fastCornersNMS_i8u_checkParams(const VXLIB_bufParams2D_t * src_addr,
                                                  const uint32_t corners_in[],
                                                  const uint8_t strengths_in[],
                                                  uint32_t num_corners_in,
                                                  const uint32_t corners_out[],
                                                  const uint8_t strengths_out[],
                                                  const uint32_t *num_corners_out,
                                                  const uint8_t scratch[],
                                                  uint32_t scratch_size);
/** @} */
#endif

