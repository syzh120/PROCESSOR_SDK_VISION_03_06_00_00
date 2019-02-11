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
**|        Copyright (c) 2007 - 2014 Texas Instruments Incorporated          |**
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

#ifndef VLIB_BLOBANALYSIS_CN_H
#define VLIB_BLOBANALYSIS_CN_H 1

#include "VLIB_blobAnalysis_types.h"
#include "../VLIB_Connected_Components_Labeling/AVMClasses.h"

/** @defgroup VLIB_createBlobList_cn */
/** @ingroup  VLIB_createBlobList_cn */
/* @{ */

/**
 * @par Description:
 *  This function works on the output of connected component labeling(CCL).
 *  It fills the VLIB_blobList from the internal results of the CCL handle.
 *
 * @par
 *   @param [in]   *handle        Pointer to CC handle, the CC handle is used for
 *                                 connected component labeling and contains all the
 *                                 internal results of cc labeling including the global
 *                                 interval image                                           (VLIB_CCHandle)
 *   @param [out]   blobObj       Pointer to the output blob structure which consists of the
 *                                 blob list and some common blob parameters                (VLIB_blobList)
 *
 * @par Assumptions:
 *    - blobObj is assumed not aliased.
 */
int32_t VLIB_createBlobList_cn(VLIB_CCHandle *handle,
                               VLIB_blobList *blobObj);

/** @} */


/** @defgroup VLIB_createBlobIntervalImg_cn */
/** @ingroup  VLIB_createBlobIntervalImg_cn */
/* @{ */

/**
 * @par Description:
 *  This function constructs the interval image of the blob. The blob is specified by
 *  input parameters. The blob interval image is extracted from the global interval
 *  image which is the internal result of connected component labeling. So the connected
 *  component labeling needs to be performed before calling this module.
 *
 * @par
 *    @param [in]  handle     Pointer to CC handle, the CC handle is used for
 *                             connected component labeling and contains all the
 *                             internal results of cc labeling, including the global
 *                             interval image                                     (VLIB_CCHandle)
 *    @param [out] blob_ii    Pointer to the output interval image of the blob. The buffer size pointed to by this pointer should be
 *                             be equal to the size parameter returned by the \ref VLIB_getblobIIBufSize function.   (AVMii)
 *    @param [in]  blob        The pointer to the blob parameter structure        (VLIB_blob)
 *
 * @par Assumptions:
 *    - All I/O buffers are assumed to be not aliased.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C66 floating-point processors
 *
 * @par Performance Notes:
 *      NA
 */
int32_t   VLIB_createBlobIntervalImg_cn(VLIB_CCHandle    *handle,
                                        AVMii            *blob_ii,
                                        VLIB_blob        *blob);
/** @} */


/** @defgroup VLIB_calcBlobPerimeter_cn */
/** @ingroup  VLIB_calcBlobPerimeter_cn */
/* @{ */

/**
 * @par Description:
 *  This function calculates the perimeter of a blob. If the blob has hole inside, then the perimeter
 *  of the hole is also counted.
 * @par
 *    @param [in]  ccmapColor   The ccmap color of the blob. The ccmap is one of the outputs of connected component labeling. (Q32.0)
 *    @param [in]  width        The width of the ccmap, used to calculate some internal offset  (Q32.0)
 *    @param [in]  blob_ii      The pointer to interval image of the blob                       (AVMii)
 *    @param [in]  pBlobMap     The pointer to ccmap of uint8_t type of data                    (Q8.0)
 *    @param [out] perimeter    The output address of the perimeter. The output is single word. (Q32.0)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be not aliased.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C66 floating-point processors
 *
 * @par Performance Notes:
 *      NA
 */
int32_t VLIB_calcBlobPerimeter_cn(int32_t ccmapColor,
                                  int32_t width,
                                  AVMii             *blob_ii,
                                  uint8_t           *pBlobMap,
                                  uint32_t          *perimeter);
/** @} */

/** @defgroup VLIB_calcBlobMinEnclosedPolygon_cn */
/** @ingroup  VLIB_calcBlobMinEnclosedPolygon_cn */
/* @{ */

/**
 * @par Description:
 *  This function finds the minimal enclosed polygon of a blob. The blob interval
 *  image is input to the module.
 *  By using the interval image, the boundary pixels are extracted and stored
 *  into the blobBoundary buffer.  By filtering the boundary pixels, the vertices of
 *  minimal enclosed convex polygon are extracted and stored into polygonBoundary buffer.
 *  The number of vertices in the polygonBoundary array is written to pointer
 *  numPolygonPt
 *
 * @par
 *    @param [in]  blob_ii         The pointer to the interval image of the blob                     (AVMii)
 *    @param [in]  blobBoundary    The buffer pointer to store output boundary pixels's (x,y)
 *                                  coordinate  of the blob.
 *                                  The application must allocate enough buffer to store all the
 *                                  boundary pixels of the blob. During blob list creation, function
 *                                  \ref VLIB_createBlobList_cn returns the maximal height and width of all the blobs
 *                                  in the image. These parameters can be used to calculate the maximal
 *                                  buffer buffers needed.                                          (VLIB_blobAnalysis_point)
 *    @param [out] polygonBoundary The buffer pointer to store output vertex's (x,y) coordinate
 *                                  of the polygon. The application must allocate enough buffer to
 *                                  store all the vertex pixels of the blob. The same buffer size
 *                                  as for blobBoundary is enough.                                  (VLIB_blobAnalysis_point)
 *    @param [out] numPolygonPt    The pointer to return the number of vertices of the polygon     (Q32.0)
 *
 * @par Assumptions:
 *    - All I/O buffers are assumed to be not aliased.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C66 floating-point processors
 *
 * @par Performance Notes:
 *      NA
 */
int32_t VLIB_calcBlobMinEnclosedPolygon_cn(AVMii                      *blob_ii,
                                           VLIB_blobAnalysis_point    *blobBoundary,
                                           VLIB_blobAnalysis_point    *polygonBoundary,
                                           int32_t                    *numPolygonPt);

/** @} */

/** @defgroup VLIB_calcBlobMinEnclosedRect_cn */
/** @ingroup  VLIB_calcBlobMinEnclosedRect_cn */
/* @{ */

/**
 * @par Description:
 *  This function finds the minimlal enclosed rectangle of a blob. The enclosed polygon
 *  parameters (which is generated by \ref VLIB_calcBlobMinEnclosedPolygon_cn) of the blob are
 *  input to this module. The enclosed polygon parameters consist of the number and
 *  position of vertices. The parameters of the minimal enclosed rectangle which consists of
 *  The center position(x,y), the rotation angle and the width/height are output in
 *  structure \ref VLIB_blobAnalysis_box
 *
 * @par
 *    @param [in]  numPolygonPt     The number of vertices of the enclosed polygon         (Q32.0)
 *    @param [in]  polygonBoundary  The pointer to vertices position array of the
 *                                   enclosed polygon                                       (VLIB_blobAnalysis_point)
 *    @param [out] box              The pointer to minimal enclosed rectangle parameters   (VLIB_blobAnalysis_box)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be not aliased.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C66 floating-point processors
 *
 * @par Performance Notes:
 *      NA
 */
int32_t VLIB_calcBlobMinEnclosedRect_cn(int32_t numPolygonPt,
                                        VLIB_blobAnalysis_point    *polygonBoundary,
                                        VLIB_blobAnalysis_box      *box);

/** @} */

/** @defgroup VLIB_calcBlobMinEnclosedCircle_cn */
/** @ingroup  VLIB_calcBlobMinEnclosedCircle_cn */
/* @{ */

/**
 * @par Description:
 *  This function finds the minimlal enclosed circle of a blob.
 *  The enclosed polygon parameters (which is generated by \ref VLIB_calcBlobMinEnclosedPolygon_cn) of the blob
 *  are input to this module. The enclosed polygon parameters consist of the number and position of polygon vertexes.
 *  The parameters of the enclosed circle which consist of center position(x,y) and radius are output
 *  in structure VLIB_blobAnalysis_circle
 *
 * @par
 *    @param [in]  numPolygonPt        The number of vertices of the enclosed polygon              (Q32.0)
 *    @param [in]  polygonBoundary     The pointer to vertices position of the enclosed polygon    (VLIB_blobAnalysis_point)
 *    @param [out] circle              The pointer to minimal enclosed circle parameters           (VLIB_blobAnalysis_circle)
 *
 * @par Assumptions:
 *    - I/O buffers are assumed to be not aliased.
 *
 * @par Implementation Notes:
 *    - This code is fully interruptible
 *    - This code is compatible with C66 floating-point processors
 *
 * @par Performance Notes:
 *      NA
 */

int32_t VLIB_calcBlobMinEnclosedCircle_cn(int32_t numPolygonPt,
                                          VLIB_blobAnalysis_point  *polygonBoundary,
                                          VLIB_blobAnalysis_circle *circle);

/** @} */

#endif /* VLIB_BLOBANALYSIS_CN_H */

/* ======================================================================== */
/*  End of file:  VLIB_blobAnalysis_cn.h                                    */
/* ======================================================================== */

