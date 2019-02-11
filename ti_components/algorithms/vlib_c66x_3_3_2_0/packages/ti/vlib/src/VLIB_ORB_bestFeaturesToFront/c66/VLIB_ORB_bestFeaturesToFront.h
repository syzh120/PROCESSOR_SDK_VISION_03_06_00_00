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
**|        Copyright (c) 2007 - 2013 Texas Instruments Incorporated          |**
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

#ifndef VLIB_ORB_BESTFEATURESTOFRONT_H_
#define VLIB_ORB_BESTFEATURESTOFRONT_H_ 1

#include "../../common/VLIB_types.h"
#include "../../common/VLIB_orb.h"

/** @defgroup VLIB_ORB_bestFeaturesToFront */
/** @ingroup  VLIB_ORB_bestFeaturesToFront */
/* @{ */

/**
 * @par Description:
 *  Once the fast corners are detected and the harris scores for each have been obtained (\ref VLIB_ORB_getHarrisScore),
 *  this function can be called. If the number of features found (output->n_features) is less than or equal to the
 *  number of desired features requested (parameters->n_features_desired), then this function returns without doing
 *  anything. Otherise, it modifies the feature list (output->features and output->n_features) to return only the subset
 *  of features which have the highest Harris scores, though not necessarily sorted.  In case the final requested feature
 *  has the same score as others, all of the features of that score will be included in the modified list.  For this reason,
 *  the modified output->n_features parameter may be larger than the parameters->n_features_desired parameter.
 *
 * @par
 *  @param [in]  *parameters   The parameters for ORB
 *  @param [in]  *input        The input data for ORB
 *  @param [out] *output       The output data for ORB
 *
 * @par Assumptions:
 * - Pointer to the features list in \c output must be double-word(64-bit) aligned.
 * - One of the following FAST corner detectors is run prior to this function:
 *     - @ref VLIB_afast9_detectCorners
 *     - @ref VLIB_originalfast9_detectCorners
 *     - @ref VLIB_afast12_detectCorners
 *     - @ref VLIB_originalfast12_detectCorners
 * - @ref VLIB_ORB_getHarrisScore is run after the corner detector but before running this function.
 * - This function uses the input->scratchBuffer, so be sure that this buffer has been allocated at least
 *   (output->n_features + 1024) * 2 bytes.  In general, the input->scratchBuffer size can be overallocated to max
 *   possible requirement for ORB by calling the getRequiredScratchSize() function during initialization time.
 * - The input->scratchBuffer pointer must be 8 byte aligned.
 *
 * @par Implementation Notes:
 * - This code is compatible with C6XXX fixed point processors.
 *
 * @par Benchmarks:
 *  See VLIB_Test_Report.html for cycle and memory information.
 *
 */
CORBResult VLIB_ORB_bestFeaturesToFront(const CORBParameters *parameters,
                                        const CORBInput *input,
                                        CORBOutput *output);

/** @} */
#endif /* VLIB_ORB_BESTFEATURESTOFRONT_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_ORB_bestFeaturesToFront.h                            */
/* ======================================================================== */

