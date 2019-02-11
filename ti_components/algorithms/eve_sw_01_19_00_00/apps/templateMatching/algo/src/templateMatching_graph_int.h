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
 *  @file       templateMatching_graph_int.h
 *
 *  @brief      This file defines the interface for template matching graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef TEMPLATE_MATCHING_TI_GRAPH_INT_H
#define TEMPLATE_MATCHING_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "algframework.h"
#include "bam_common.h"

#include "bam_ncc.h"
#include "bam_natcNcc.h"

#include "edma_utils_autoincrement.h"

#include "iTemplateMatching_ti.h"
#include "templateMatching_alg_int.h"

#define MAX_KERNEL_ID (255)

typedef enum
{
    BAM_TI_KERNELID_DMAREAD_AUTOINCREMENT= 0,
    BAM_TI_KERNELID_NCC= 1,
    BAM_TI_KERNELID_DMAWRITE_AUTOINCREMENT= 2,
    BAM_TI_KERNELID_NATCNCC= 3,
    BAM_TI_KERNELID_MAX = MAX_KERNEL_ID
} BAM_TI_KernelID;

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define TEMPLATE_MATCHING_TI_GRAPH_OBJ_SIZE             (2644)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
 */
#define TEMPLATE_MATCHING_TI_GRAPH_SCRATCH_SIZE         (1092)

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
  For this algorithm actually 0 bytes is necessary but since we already allocate a memTab
  for this purpose, we just set the size to a non-zero value such as 1 bytes
  so malloc() doesn't fail. Later if actual external memory is required, it is easy
  just to update the below number
 */
#define TEMPLATE_MATCHING_TI_GRAPH_CONTEXT_SIZE         (1)

/*--------------------------------------------------------------------*/
/* These are macros which are algorithm specfic and indicative to BAM */
/* to help decide the optimal block dimensions                        */
/*--------------------------------------------------------------------*/

#define TEMPLATE_MATCHING_TI_BLK_WIDTH      16 /* Minimum width of the processing block that will be picked by the function */
#define TEMPLATE_MATCHING_TI_BLK_HEIGHT     16 /* Minimum height of the processing block that will be picked by the function */
#define TEMPLATE_MATCHING_TI_BLK_WIDTH_STEP 16 /* Step size used during the search for the best processing block's width */
#define TEMPLATE_MATCHING_TI_BLK_HEIGHT_STEP 8 /* Step size used during the search for the best processing block's height */

/** ========================================================
 *  @name   TEMPLATE_MATCHING_TI_graphConstructParams
 *
 *  @desc   This structure specifies the properties needed for constructing
 *          template matching transform  graph
 *
 * @param  imgFrameWidth
 *         Width in pixels for the input image
 *
 * @param  imgFrameHeight
 *         height in number of lines for the input image
 *
 * @param  activeImgWidth   Width in bytes of the area that will be accessed by the EDMA when reading the frame.
 *                          For this function, it should always be equal to (createParams->imgFrameWidth)
 *
 * @param  activeImgHeight   Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
 *                           For this function, it should always be equal to (createParams->imgFrameHeight)
 *
 * @param  templateWidth
 *        Width of the 16-bits 0-mean template in Q-format.
 *
 * @param  templateHeight
 *        Height of the 16-bits 0-mean template in Q-format.
 *
 * @param  qShift
 *        Number of fractional bits of the Q-format used to format the output
 *
 * @param  sizeQshift
 *        Number of fractional bits of the Q-format for calculating K=1/(templateWidth*templateHeight).
 *        K is used when calculating the mean of the input region to be matched witht the template.
 *        The function TEMPLATE_MATCHING_TI_init() automatically derives the optimal sizeQshift.
 *
 * @param  outputBlockWidth
 *         Output block width returned by BAM_createGraph(). That's useful information to understand performance.
 *
 * @param  outputBlockheight
 *         Output block height returned by BAM_createGraph(). That's useful information to understand performance.
 *
 *  ===============================================================
 */
typedef struct
{
    uint16_t      imgFrameWidth;
    uint16_t      imgFrameHeight;

    uint16_t      templateWidth;
    uint16_t      templateHeight;
    
    uint8_t       qShift;
    uint8_t       sizeQshift;

    uint16_t      activeImgWidth;
    uint16_t      activeImgHeight;

    uint16_t      outputBlockWidth;
    uint16_t      outputBlockHeight;

} TEMPLATE_MATCHING_TI_graphCreateParams;

/*--------------------------------------------------------------------*/
/**
  @struct TEMPLATE_MATCHING_TI_graphArgs
  @brief  This structure is the information holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  dmaWriteKernelArgs      Parameters for DMA SINK node
  @param  templateMatchingArgs Parameters arguments for the template matching method
  @param  createParams            Creation time parameters
 */
typedef struct
{
    EDMA_UTILS_autoIncrement_initParam dmaReadKernelArgs;
    EDMA_UTILS_autoIncrement_initParam dmaWriteKernelArgs;
    BAM_Ncc_Args templateMatchingArgs;
    TEMPLATE_MATCHING_TI_graphCreateParams *createParams;
} TEMPLATE_MATCHING_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_templateMatching
 *  @func          TEMPLATE_MATCHING_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t TEMPLATE_MATCHING_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_imagePyramid_u8
 *  @func          TEMPLATE_MATCHING_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           TEMPLATE_MATCHING_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t TEMPLATE_MATCHING_TI_graphCreate(const BAM_GraphMem * graphMem,
        TEMPLATE_MATCHING_TI_graphCreateParams* createParams);
/**
 *******************************************************************************
 *  @ingroup       BAM_templateMatching
 *  @func          TEMPLATE_MATCHING_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           TEMPLATE_MATCHING_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t TEMPLATE_MATCHING_TI_execute(BAM_GraphMem *graphMem,
        const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);

/**
 *******************************************************************************
 *  @ingroup       TEMPLATE_MATCHING
 *  @func          TEMPLATE_MATCHING_TI_dmaControl
 *  @brief         This function can be called after the graph is created and before TEMPLATE_MATCHING_TI_execute()
 *                 to control the source and sink node's parameters. 
 *  @pre           TEMPLATE_MATCHING_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inBufs  : Pointer to input buffer's descriptions
 *  @param [in]    outBufs : Pointer to output buffer's descriptions
 *  @param [in]    intAlgHandle: handle to the algorithm object
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t TEMPLATE_MATCHING_TI_dmaControl(const BAM_GraphMem *graphMem, const TEMPLATE_MATCHING_TI_Handle intAlgHandle, const IVISION_BufDesc *inBufDesc[], const IVISION_BufDesc *outBufDesc[]);

#endif

