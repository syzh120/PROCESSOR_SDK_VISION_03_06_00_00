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

#ifndef VLIB_CONNECTED_COMPONENTS_LABELING_H_
#define VLIB_CONNECTED_COMPONENTS_LABELING_H_ 1

#include "../../common/VLIB_types.h"

/** @defgroup VLIB_Connected_Components_Labeling */
/** @ingroup  VLIB_Connected_Components_Labeling */
/* @{ */

/**
 * @par Description:
 *  This function estimates the upper bound of the buffer size required
 *  for the connected components list based on image dimensions and minimum
 *  blob area inputs.
 *
 * @par
 *   @param [in]   imgWidth             Input width (SQ15.0)
 *   @param [in]   imgHeight            Input height (SQ15.0)
 *   @param [in]   minArea              Min area (SQ31.0)
 *   @param [out] *maxbytesRequired     Bytes required (SQ31.0)
 */
VLIB_STATUS VLIB_calcConnectedComponentsMaxBufferSize(int16_t imgWidth,
                                                      int16_t imgHeight,
                                                      int32_t minArea,
                                                      int32_t *maxbytesRequired);

/**
 * @par Description:
 *  This function initializes the handle.  It requires that the
 *  \c pBuf buffer has already been allocated with size of \c bytes.
 *
 * @par
 *   @param [out]  *handle      pointer to CC handle
 *   @param [in]   *pBuf        pointer to input buffer
 *   @param [in]    bytes       bytes (SQ31.0)
 */
VLIB_STATUS VLIB_initConnectedComponentsList(VLIB_CCHandle *handle,
                                             void *pBuf,
                                             int32_t bytes);

/**
 * @par Description:
 *  This is the primary function for grouping and labeling foreground components
 *  or blobs in the \c pIn32BitPacked image.  The results are internally stored
 *  within the handle, and can be accessed using the helper functions:
 * \ref VLIB_getNumCCs and \ref VLIB_getCCFeatures.
 *
 * @par
 *   @param [in,out] *handle           Pointer to CC handle
 *   @param [in]      width            Input width (UQ16.0)
 *   @param [in]      height           Input height (UQ16.0)
 *   @param [in]     *pIn32BitPacked   Pointer to input
 *   @param [in]      minBlobArea      Minimum Area (SQ31.0)
 *   @param [in]      connected8Flag   Flag (SQ31.0)
 */
VLIB_STATUS VLIB_createConnectedComponentsList(VLIB_CCHandle *handle,
                                               uint16_t width,
                                               uint16_t height,
                                               uint32_t *pIn32BitPacked,
                                               int32_t minBlobArea,
                                               int32_t connected8Flag);

/**
 * @par Description:
 *  After running \ref VLIB_createConnectedComponentsList, the number
 *  of connected components (\c numCCs) can be obtained by passing
 *  the \c handle to this function.
 *
 * @par
 *   @param [in]  *handle     Poimter to CC handle
 *   @param [out]  numCCs     number of connected components (SQ31.0)
 */
VLIB_STATUS VLIB_getNumCCs(VLIB_CCHandle *handle,
                           int32_t *numCCs);
/**
 * @par Description:
 *  After running \ref VLIB_createConnectedComponentsList, a single
 *  connected component blob can be retrieved by passing the \c handle
 *  and index of the blob to this function.  \ref VLIB_getNumCCs can
 *  be run first in order to determine what the maximum supported value
 *  of \c listIndex is.
 *
 * @par
 *   @param [in]   *handle    Pointer to CC handle
 *   @param [out]  *cc        Pointer to CC
 *   @param [in]   listIndex  Index (SQ15.0)
 *
 * @par Assumptions:
 *    - Maximum supported \c listIndex is (\c numCCs - 1).
 */
VLIB_STATUS VLIB_getCCFeatures(VLIB_CCHandle *handle,
                               VLIB_CC *cc,
                               int16_t listIndex);

/**
 * @par Description:
 *  This function generates a blob map. For each pixel in the scene, the
 *  map assigns a unique index, which is associated with a particular blob.
 *  Unassociated pixels are labeled with index = 0. There are a maximum of
 *  255 unique indices, e.g. blobs, in the map.
 *
 * @par
 *   @param [in]   *handle         Pointer to CC handle
 *   @param [out]  *pOutMap        Pointer to output data
 *   @param [in]    outCols        Input Cols (UQ16.0)
 *   @param [in]    outRows        Input Rows (UQ16.0)
 *
 * @par Assumptions:
 *    - Maximum supported blob to label = 255 (due to bit width of each pixel in the blob map being 8 bits).
 *    - pOutMap is assumed to be double-word aligned and not aliased.
 */
VLIB_STATUS VLIB_createCCMap8Bit(VLIB_CCHandle *handle,
                                 uint8_t *restrict pOutMap,
                                 const uint16_t outCols,
                                 const uint16_t outRows);

/**
 * @par Description:
 *  This function returns the size of the CC Handle.
 *
 * @par
 *   @return  Size of CC Handle in bytes
 *
 */
int32_t VLIB_GetSizeOfCCHandle(void);

/** @} */

#endif /* VLIB_CONNECTED_COMPONENTS_LABELING_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_CONNECTED_COMPONENTS_LABELING.h                      */
/* ======================================================================== */

