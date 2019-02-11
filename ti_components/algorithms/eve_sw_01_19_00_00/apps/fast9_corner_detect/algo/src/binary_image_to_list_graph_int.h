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
 *  @file       binary_image_to_list_graph_int.h
 *
 *  @brief      This file defines the interface for binary image to list graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef BIN_IMAGE_TO_LIST_TI_GRAPH_INT_H
#define BIN_IMAGE_TO_LIST_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "algframework.h"
#include "edma_utils.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_scatterGather.h"
#include "edma_utils_context_size.h"
#include "bin_img_to_list_bam_dma_node.h"
#include "bam_bin_image_to_list.h"
#include "bam_common.h"
#include "ifast9_corner_detect_ti.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_GRAPH_OBJ_SIZE             (2652)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_GRAPH_SCRATCH_SIZE         (416)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define BIN_IMAGE_TO_LIST_GRAPH_CONTEXT_SIZE         (4)

/**
  @struct BIN_IMAGE_TO_LIST_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.
  @param  binToListKernelArgs     Parameters for binary image to list kernel
*/
typedef struct
{
  BAM_Bin_image_to_list_Args                     binToListKernelArgs;
} BIN_IMAGE_TO_LIST_TI_graphArgs;


/**
  @struct BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs
  @brief  This structure contains parameters which can be configured
              for DMA using control call
  @param  imgWidth     Image Width
  @param  imgHeight    Image Height
  @param  imgPitch     Image Pitch
  @param  blkWidth     Block width for dma
  @param  blkHeight    Block height for dma
  @param  dx     delta x from startx
  @param  dx     delta y from startx
  @param  *pListSize     Pointer to the list size
  @param  level     Current level for the process call
*/
typedef struct
{
    uint16_t    imgWidth;
    uint16_t    imgHeight;
    uint16_t    imgPitch;
    uint16_t    blkWidth;
    uint16_t    blkHeight;
    uint16_t    dx;
    uint16_t    dy;
    uint32_t    *pListSize;
    uint8_t     level;
}
BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           BIN_IMAGE_TO_LIST_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_graphCreate(const BAM_GraphMem * graphMem,
                                         BIN_IMAGE_TO_LIST_TI_graphArgs * createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_graphControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function controls the kernel parameters for the graph
 *  @pre           BIN_IMAGE_TO_LIST_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    binToImgListCtrlArgs   : Pointer to control parameter for the kernels
 *                       refer BAM_Bin_image_to_list_ctrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_graphControl(
        const BAM_GraphMem *graphMem,
        BAM_Bin_image_to_list_ctrlArgs * binToImgListCtrlArgs
        );

/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_graphDmaControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function is used to control the dma parameter before
 *                 calling process call
 *  @pre           BIN_IMAGE_TO_LIST_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    inBufDesc   : Pointer to input ivision buf
 *  @param [in]    outBufDesc   : Pointer to output ivision buf
 *  @param [in]    dmaCtrlParams   : : Pointer to control parameter for the dma nodes
 *                       refer BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */

int32_t BIN_IMAGE_TO_LIST_TI_graphDmaControl(
              const BAM_GraphMem *graphMem,
              const IVISION_BufDesc *inBufDesc,
              const IVISION_BufDesc *outBufDesc,
              const BIN_IMAGE_TO_LIST_TI_dmaCtrlArgs * dmaCtrlParams);


/**
 *******************************************************************************
 *  @ingroup       BAM_binImgToList
 *  @func          BIN_IMAGE_TO_LIST_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           BIN_IMAGE_TO_LIST_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t BIN_IMAGE_TO_LIST_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

#endif

