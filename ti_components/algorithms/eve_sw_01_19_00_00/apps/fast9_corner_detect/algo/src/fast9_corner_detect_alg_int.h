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
 *  @file       fast_corner_detect_alg_int.h
 *
 *  @brief      This file defines the functions for FAST9 applet
 *  @version 0.0 (Dec 2013) : Base version.
 */


#ifndef FAST9_CORNER_DETECT_ALG_INT_H
#define FAST9_CORNER_DETECT_ALG_INT_H

/*--------------------------------------------------------------------------*/
/* This header file inclusion is only for XDAIS module. It accepts specific */
/* data types defined externally                                            */
/*--------------------------------------------------------------------------*/
#include <xdais_types.h>

#include "ifast9_corner_detect_ti.h"
#include "fast9_corner_detect_graph_int.h"
#include "binary_image_to_list_graph_int.h"

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for FAST9 Corner Detector application
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_HANDLE_INT_MEMREC,
  /* Memory records for Fast9 graph */
  FAST9_GRAPH_OBJ_MEMREC,
  /* For all the external memory if same copy is expected to be present in
  DMEM than they should be kept consecutive in this enum. This is needed
  because alg activate and deactivate has this assumption*/
  FAST9_GRAPH_OBJ_INT_MEMREC,
  FAST9_GRAPH_SCRATCH_MEMREC,
  FAST9_GRAPH_CONTEXT_MEMREC,
  FAST9_GRAPH_ARGS_MEMREC,
  /* Memory records for Binary image to list graph */
  BIN2LIST_GRAPH_OBJ_MEMREC,
  BIN2LIST_GRAPH_OBJ_INT_MEMREC,
  BIN2LIST_GRAPH_SCRATCH_MEMREC,
  BIN2LIST_GRAPH_CONTEXT_MEMREC,
  BIN2LIST_GRAPH_ARGS_MEMREC,
  /* Applet specific scratch buffers */
  BIN_IMG_SCRATCH_MEMREC,
  NUM_MEMRECS
} eMemrecs;

/**
 *  @enum   eAlgState
 *  @brief  State of Fast9 corner detect application
*/
typedef enum
{
  ALG_NOT_ACTIVE,
  ALG_ACTIVE
} eAlgState;

/**
  @struct FAST9_CORNER_DETECT_TI_Obj
  @brief  This structure is the main handle of fast9 corner detect
          applet.

  @param  ivision    All public function pointers
  @param  algState   State of algorithm to indicate
  @param  numMemRecs Number of memory records
  @param  memRec     Array of memory records
  @param  graphMem   BAM specific memory for graph creation
  @param  numLevels  Number of levels for which this applet needs to run
  @param  activeImageWidth[]   active image width on which this applet will be working for all levels
  @param  activeImageHeight[]  active image height on which this applet will be working for all levels
  @param blockWidth[] blockWidth to be used for all levels
  @param blockHeight[] blockHeight to be used for all levels
  @param  dx[]  Horizontal Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
  @param  dy[]  Vertical Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
  @param  activeBinImgWidth[]   active image width on which this applet will be working for all levels for bin to img list graph
  @param  activeBinImgHeight[]  active image height on which this applet will be working for all levels for bin to img list graph
  @param blockWidthBinImgToList[] blockWidth to be used for all levels for bin to img list graph
  @param blockHeightBinImgToList[] blockHeight to be used for all levels for bin to img list graph
  @param  dx_binImg[]  Horizontal Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
  @param  dy_binImg[]  Vertical Offset of the partial image on which corner detection is working to
              satisfy DMA and kernel constraints for all levels
*/
typedef struct
{
  const IVISION_Fxns* ivision;
  uint8_t       algState;
  uint32_t      numMemRecs;
  IALG_MemRec   memRec[NUM_MEMRECS];
  BAM_GraphMem  fast9GraphMem;
  BAM_GraphMem  binToListGraphMem;
  uint8_t       numLevels;
  /* Fast9 corner detect parameters */
  uint16_t      activeImageWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      activeImageHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dx[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dy[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  /* Binary image to list parameters*/
  uint16_t      activeBinImgWidth[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      activeBinImgHeight[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockWidthBinImgToList[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      blockHeightBinImgToList[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dx_binImg[FAST9_CORNER_DETECT_TI_MAXLEVELS];
  uint16_t      dy_binImg[FAST9_CORNER_DETECT_TI_MAXLEVELS];
} FAST9_CORNER_DETECT_TI_Obj;

typedef FAST9_CORNER_DETECT_TI_Obj * FAST9_CORNER_DETECT_TI_Handle;


/*--------------------------------------------------------*/
/* IALG functions                                         */
/* Refer XDAIS ialg.h file for details on these functions */
/*--------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_numAlloc(void);
int32_t FAST9_CORNER_DETECT_TI_alloc(const IALG_Params *params,
  IALG_Fxns **parentFxns, IALG_MemRec memRec[]);
int32_t FAST9_CORNER_DETECT_TI_init(IALG_Handle handle,
  const IALG_MemRec memRec[], IALG_Handle parent, const IALG_Params *params);
void  FAST9_CORNER_DETECT_TI_activate(IALG_Handle handle);
void  FAST9_CORNER_DETECT_TI_deactivate(IALG_Handle handle);
int32_t FAST9_CORNER_DETECT_TI_free(IALG_Handle handle, IALG_MemRec memRec[]);

int32_t FAST9_CORNER_DETECT_TI_control(IVISION_Handle handle, IALG_Cmd cmd,
    const IALG_Params *inParams, IALG_Params *outParams);

int32_t FAST9_CORNER_DETECT_TI_process(IVISION_Handle handle, IVISION_InBufs *inBufs,
    IVISION_OutBufs *outBufs, IVISION_InArgs *inArgs,
    IVISION_OutArgs *outArgs);

/*--------------------------------------------------------*/
/* IRES functions                                         */
/*--------------------------------------------------------*/
int32_t FAST9_CORNER_DETECT_TI_getResourceDescriptors(IALG_Handle handle, IRES_ResourceDescriptor *resDesc);

#endif /* FAST9_CORNER_DETECT_ALG_INT_H */

