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

#ifndef VLIB_BLOBANALYSIS_TYPES_H_
#define VLIB_BLOBANALYSIS_TYPES_H_

#include "../common/VLIB_types.h"

/*!
 * \brief Structure defining the parameters of each blob
 */
typedef struct vlib_blob {
    int32_t xmin;          /*!< The min x coordinate */
    int32_t xmax;          /*!< The max x coordinate */
    int32_t ymin;          /*!< The min y coordinate */
    int32_t ymax;          /*!< The max y coordinate */
    int32_t area;          /*!< The number of pixels in the blob */
    int32_t numIntervals;  /*!< The number of intervals of the blob */
    int32_t iiValue;       /*!< The interval value of the blob in global interval image */
    int32_t ccmapColor;    /*!< The int16 value which identifies the blob in ccmap  */
}VLIB_blob;

/*!
 * \brief Structure defining common parameters for all the blobs of a image and the pointer to blob parameter array
 */
typedef struct vlib_blobList {
    int32_t    numBlobs;       /*!<  The number of blobs in the image after merging */
    int32_t    maxSize_y;      /*!<  The maximal height in y direction of all the blobs */
    int32_t    maxSize_x;      /*!<  The maximal width in x direction of all the blobs */
    int32_t    maxNumItervals; /*!<  The maximal number of intervals of all the blobs */
    VLIB_blob *blobList;       /*!<  List to the blobs after merging */
}VLIB_blobList;

/*!
 * \brief Structure defining the x and y coordinates of a point/pixel
 */
typedef struct vlib_blobAnalysis_point {
    VLIB_F32 x;        /*!<  The x coordinate of a pixel */
    VLIB_F32 y;        /*!<  The y coordinate of a pixel */
}VLIB_blobAnalysis_point;

/*!
 * \brief Structure defining the characteristics of a minimal enclosed rectangle
 */
typedef struct vlib_blobAnalysis_box {
    VLIB_F32 x;        /*!<  The x coordinate of the center of the minimal enclosed rectangle */
    VLIB_F32 y;        /*!<  The y coordinate of the center of the minimal enclosed rectangle */
    VLIB_F32 w;        /*!<  The width of the minimal enclosed rectangle */
    VLIB_F32 h;        /*!<  The height of the minimal enclosed rectangle */
    VLIB_F32 angle;    /*!<  The rotation degree of the minimal enclosed rectangle */
}VLIB_blobAnalysis_box;


/*!
 * \brief Structure defining the characteristics of a minimal enclosed circle
 */
typedef struct vlib_blobAnalysis_circle {
    VLIB_F32 x;        /*!<  The x coordinate of the center of the minimal enclosed circle */
    VLIB_F32 y;        /*!<  The y coordinate of the center of the minimal enclosed circle */
    VLIB_F32 radius;   /*!<  The radius of the center of the minimal enclosed circle */
}VLIB_blobAnalysis_circle;

#endif /* VLIB_BLOBANALYSIS_TYPES_H_ */

