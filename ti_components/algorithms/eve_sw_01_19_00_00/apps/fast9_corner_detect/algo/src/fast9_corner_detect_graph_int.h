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
 *  @file       fast9_corner_detect_graph_int.h
 *
 *  @brief      This file defines the interface for fast9 corner detect graph
 *  @version 0.0 (Dec 2013) : Base version.
 */

#ifndef FAST9_CORNER_DETECT_TI_GRAPH_INT_H
#define FAST9_CORNER_DETECT_TI_GRAPH_INT_H

#include <xdais_types.h>

#include "algframework.h"
#include "bam_common.h"
#include "bam_fast9.h"
#include "ifast9_corner_detect_ti.h"
#include "edma_utils_autoincrement.h"

/**
  Size in bytes of the graph object that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FAST9_CORNER_DETECT_GRAPH_OBJ_SIZE             (2252)
/**
  Size in bytes of the scratch buffer that will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FAST9_CORNER_DETECT_GRAPH_SCRATCH_SIZE         (884 )

/**
  Size of the graph object's context. it will be allocated by user (requested via memTab)
  The size was obtained during development time by trial and error execution.
  A smaller number causes the graph creation to fail and to return the number of bytes required.
*/
#define FAST9_CORNER_DETECT_GRAPH_CONTEXT_SIZE         (368 )

/**
  @struct FAST9_CORNER_DETECT_TI_dmaCtrlArgs
  @brief  This structure contains parameters which can be configured
              for DMA using control call
  @param  activeImageWidth     Image Width
  @param  activeImageHeight    Image Height
  @param  blkWidth     Block width for dma
  @param  blkHeight    Block height for dma
  @param  dx     delta x from startx
  @param  dx     delta y from startx
  @param  level     Current level for the process call
*/
typedef struct
{
    uint16_t    activeImageWidth;
    uint16_t    activeImageHeight;
    uint16_t    blkWidth;
    uint16_t    blkHeight;
    uint16_t    dx;
    uint16_t    dy;
    uint8_t     level;
}FAST9_CORNER_DETECT_TI_dmaCtrlArgs;

/*--------------------------------------------------------------------*/
/**
  @struct FAST9_CORNER_DETECT_TI_graphArgs
  @brief  This structure is the infomration holder for BAM graph.

  @param  dmaReadKernelArgs       Parameters for DMA SOURCE node
  @param  dmaWriteKernelArgs      Parameters for DMA SINK node
  @param  fast9KernelArgs        Parameters for FAST9 corner detect kernel
*/
typedef struct
{
  EDMA_UTILS_autoIncrement_initParam    dmaReadKernelArgs;
  BAM_Fast9_Args                        fast9KernelArgs;
  EDMA_UTILS_autoIncrement_initParam    dmaWriteKernelArgs;
} FAST9_CORNER_DETECT_TI_graphArgs;

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_getGraphMemReq
 *  @brief         This is first function to be called to request garph memory
 *  @param [in]    memReq : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_getGraphMemReq(BAM_GraphMemReq * memReq);

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_graphCreate
 *  @brief         This is function to be called after having memory allocated for
 *                 graph
 *  @pre           FAST9_CORNER_DETECT_TI_getGraphMemReq should be called to know the
 *                 graph memoory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    params   : Pointer to creation time parameter structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_graphCreate(const BAM_GraphMem * graphMem,
                                                            FAST9_CORNER_DETECT_TI_graphArgs* createParams);


/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_graphControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function controls the kernel parameters for the graph
 *  @pre           FAST9_CORNER_DETECT_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    BAM_Fast9_ctrlArgs   : Pointer to control parameter for the kernels
 *                       refer FAST9_CORNER_DETECT_TI_dmaCtrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_graphControl(
        const BAM_GraphMem *graphMem,
        BAM_Fast9_ctrlArgs * fast9KernelCtrlArgs
        );


/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_graphDmaControl
 *  @brief         This is function to be called after having memory allocated for
 *                 graph. This function is used to control the dma parameter before
 *                 calling process call
 *  @pre           FAST9_CORNER_DETECT_TI_getGraphMemReq should be called to know the
 *                 graph memory needs
 *  @param [in]    graphMem : Pointer to graph memory structure
 *  @param [in]    inBufDesc   : Pointer to input ivision buf
 *  @param [in]    outBufDesc   : Pointer to output ivision buf
 *  @param [in]    dmaCtrlParams   : : Pointer to control parameter for the dma nodes
 *                       refer FAST9_CORNER_DETECT_TI_dmaCtrlArgs structure for details
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */

int32_t FAST9_CORNER_DETECT_TI_graphDmaControl(const BAM_GraphMem *graphMem,
        const IVISION_BufDesc *inBufDesc, const IVISION_BufDesc *outBufDesc,
        const FAST9_CORNER_DETECT_TI_dmaCtrlArgs * dmaCtrlParams);

/**
 *******************************************************************************
 *  @ingroup       BAM_fast9CornerDetect
 *  @func          FAST9_CORNER_DETECT_TI_execute
 *  @brief         This is first function to be called once the graph is created
 *  @pre           FAST9_CORNER_DETECT_TI_graphCreate should be called to create graph
 *  @param [in]    graphMem  : Pointer to graph memory structure
 *  @param [in]    inArgs  : Pointer to graph memory structure
 *  @param [in]    outArgs : Pointer to graph memory structure
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t FAST9_CORNER_DETECT_TI_execute(BAM_GraphMem *graphMem,
                                const BAM_InArgs *inArgs,  BAM_OutArgs *outArgs);



#endif

