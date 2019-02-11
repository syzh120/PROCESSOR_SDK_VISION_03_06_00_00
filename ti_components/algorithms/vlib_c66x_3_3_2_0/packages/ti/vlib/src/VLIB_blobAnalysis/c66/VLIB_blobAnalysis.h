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

#ifndef VLIB_BLOBANALYSIS_H
#define VLIB_BLOBANALYSIS_H 1

#include "../VLIB_blobAnalysis_types.h"
#include "VLIB_calcPerimeter.h"

/** @defgroup VLIB_createBlobList */
/** @ingroup  VLIB_createBlobList */
/* @{ */

/**
 * @par Description:
 *  This function works on the output of connected component labeling (CCL).
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
 *    - All pointers are assumed not aliased.
 */
int32_t VLIB_createBlobList(VLIB_CCHandle *handle,
                            VLIB_blobList *blobObj);

/** @} */

/** @defgroup VLIB_getblobIIBufSize */
/** @ingroup  VLIB_getblobIIBufSize */
/* @{ */

/**
 * @par Description:
 *  This function computes the buffer size required to allocate to the blob_ii buffer needed in the following functions: \ref VLIB_createBlobIntervalImg,
 *  \ref VLIB_calcBlobPerimeter, and \ref VLIB_calcBlobMinEnclosedPolygon.
 *
 * @par
 *   @param [in]    height           Number of rows in the image                 (UQ16.0)
 *   @param [in]    maxNumIntervals  The value of the blobObj->maxNumItervals parameter at the output of the \ref VLIB_createBlobList function. (SQ31.0)
 *   @param [out]  *size             Returns the size in number of bytes to allocate to the blob_ii buffer. (UQ32.0)
 *
 * @par Implementation Notes:
 *  The formula for the size is: size = 12 + 8*(height + maxNumIntervals); These constants are based on the size
 *  of internal data structures used to store computation information.
 *
 * @par Assumptions:
 *    - All pointers are assumed not aliased.
 */
int32_t VLIB_getblobIIBufSize(uint16_t height,
                              int32_t maxNumIntervals,
                              uint32_t  *size);

/** @} */

/** @defgroup VLIB_createBlobIntervalImg */
/** @ingroup  VLIB_createBlobIntervalImg */
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
 *    @param [in]  blob       The pointer to the blob parameter structure        (VLIB_blob)
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
int32_t   VLIB_createBlobIntervalImg(VLIB_CCHandle    *handle,
                                     AVMii      *blob_ii,
                                     const VLIB_blob  *blob);
/** @} */

/** @defgroup VLIB_calcBlobMinEnclosedPolygon */
/** @ingroup  VLIB_calcBlobMinEnclosedPolygon */
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
 *                                  coordinate of the blob.
 *                                  The application must allocate enough buffer to store all the
 *                                  boundary pixels of the blob. During blob list creation, function
 *                                  \ref VLIB_createBlobList returns the maximal height and width of all the blobs
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
int32_t VLIB_calcBlobMinEnclosedPolygon(const AVMii                *blob_ii,
                                        VLIB_blobAnalysis_point   *blobBoundary,
                                        VLIB_blobAnalysis_point   *polygonBoundary,
                                        int32_t                     *numPolygonPt);

/** @} */

/** @defgroup VLIB_calcBlobMinEnclosedRect */
/** @ingroup  VLIB_calcBlobMinEnclosedRect */
/* @{ */

/**
 * @par Description:
 *  This function finds the minimlal enclosed rectangle of a blob. The enclosed polygon
 *  parameters (which is generated by \ref VLIB_calcBlobMinEnclosedPolygon) of the blob are
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
int32_t VLIB_calcBlobMinEnclosedRect(int32_t numPolygonPt,
                                     VLIB_blobAnalysis_point    *polygonBoundary,
                                     VLIB_blobAnalysis_box      *box);

/** @} */


/** @defgroup VLIB_calcBlobMinEnclosedCircle */
/** @ingroup  VLIB_calcBlobMinEnclosedCircle */
/* @{ */

/**
 * @par Description:
 *  This function finds the minimlal enclosed circle of a blob.
 *  The enclosed polygon parameters (which is generated by \ref VLIB_calcBlobMinEnclosedPolygon) of the blob
 *  are input to this module. The enclosed polygon parameters consist of the number and position of polygon vertices.
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

int32_t VLIB_calcBlobMinEnclosedCircle(int32_t numPolygonPt,
                                       const VLIB_blobAnalysis_point  *polygonBoundary,
                                       VLIB_blobAnalysis_circle *circle);

/** @} */

/************************************************************************************
The blob analysis is the post processing of connected component labeling (CC labeling).
The connected component labeling identifies blobs in a image. The blob analysis calculates
the detailed parameters of each blob such as perimeter, minimal enclosed rectangle and
minimal enclosed circle. The blob analysis depends on three types of output of CC labeling:
The ccmap, the global interval image and the blob list. The global interval image is a
internal result of CC labeling. Please refer to the example below for detailed information.

The steps to perform blob analysis are:
        Functionality                                           | API
---------------------------------------------------------------------------------------------------------------------
for the whole image                                             |
[1] Connected component labeling(see Note1)                     | VLIB_createConnectedComponentsList & VLIB_createCCMap16Bit
[2] Create blob list by extracting the internal                 | VLIB_createBlobList
    information of CCL                                          |
[3] Allocate the scratch buffer. The buffer size depends        | VLIB_getblobIIBufSize & malloc
    on the maximal blob size of the image. These parameters     |
    are counted during blob list creation                       |
for each blob                                                   |
{                                                               |
    [4] Create the interval image of the blob                   | VLIB_createBlobIntervalImg
    [5] Calculate the perimeter of the blob                     | VLIB_calcBlobPerimeter
    [6] Calculate the minimal enclosed polygon of the blob      | VLIB_calcBlobMinEnclosedPolygon
    [7] Calculate the minimal enclosed rectangle of the blob    | VLIB_calcBlobMinEnclosedRect
    [8] Calculate the minimal enclosed circle of the blob       | VLIB_calcBlobMinEnclosedCircle
}
step [5],[6],[7],[8] are optional depends on the application
The dependency between modules are:
    [2] depends on [1] for globlal interval image and the blob list (before blob list creation)
    [3] depends on [2] for maximal blob parameters
    [4] depends on [1,2,3] for globlal interval image, blob parameter and output buffer
    [5] depends on [1,4] for ccmap and blob interval image
    [6] depends on [3,4] for scratch buffer and blob interval image
    [7] depends on [6] for vertex point list of minimal enclosed polygon
    [8] depends on [6] for vertex point list of minimal enclosed polygon

=============================================== Benchmark unit is(ms) ======================================================
test case  num of blobs,  for createBlobList, make interval image, perimeter, polygon, minRectan, minCircle
   1          7 blobs,           0.01,                0.01,        0.00,       0.01,     0.04,     0.02
   2         47 blobs,           0.16,                0.16,        0.65,       0.27,     0.44,     0.20
   3         80 blobs,           0.13,                0.25,        0.26,       0.27,     0.80,     0.30
   4         41 blobs,           0.06,                0.06,        0.15,       0.11,     0.41,     0.18
   5          5 blobs,           0.09,                0.06,        0.36,       0.12,     0.07,     0.03
************************************************************************************/

#endif /* VLIB_BLOBANALYSIS_H */

/* ======================================================================== */
/*  End of file:  VLIB_blobAnalysis.h                                       */
/* ======================================================================== */

