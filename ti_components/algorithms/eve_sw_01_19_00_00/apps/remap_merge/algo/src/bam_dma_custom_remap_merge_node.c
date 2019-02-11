/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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
 *****************************************************************************
 * @file
 *  bam_dma_custom_remap_merge_node.c
 *
 * @brief
 *
 * @version 0.1 (Dec 2013) : First version of custom DMA node for Remap Merge Applet.
 *
 *****************************************************************************
 *//*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/*-----------------------------------------------------------------------*/
/*  Standard header includes for c environment.                          */
/*-----------------------------------------------------------------------*/

#include "algframework.h"
#include "bam_common.h"

/*-----------------------------------------------------------------------*/
/*  These are the include files that are needed for edma/qdma.           */
/*-----------------------------------------------------------------------*/
#include "evestarterware.h"
#include "edma_utils.h"
#include "edma_utils_context_size.h"
#include "edma_utils_memcpy.h"
#include "edma_utils_autoincrement.h"
#include "edma_utils_autoincrement_1d.h"
#include "edma_utils_scatterGather.h"
#include "xdais_types.h"
#include "iremap_merge_ti.h"

#if VCOP_HOST_EMULATION
#include "vcop_host.h"
#endif

#include <vcop.h>
#include "remap.h"
#include "remap_common.h"

#include "bam_dma_custom_remap_merge_node.h"

int8_t remapNumTiles;

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define ALIGN_TLU(a)    (((uint32_t)((a) + (uint32_t)32U - (uint32_t)1U)) & ((uint32_t)~((uint32_t)32U -(uint32_t)1U)))
#define ALIGN_SHORT(a)  (((a) + (uint32_t)2U  - (uint32_t)1U) & (uint32_t)~((uint32_t)2U - (uint32_t)1U))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

#define REMAP_MERGE_IMG_BUF_A_B_OFFSET          (0x20000U)

/* Memory Pointer descriptor indexes */
/* For Source Node */
#define REMAP_MERGE_SOURCE_NUM_INPUT_BLOCKS     (0)

#define REMAP_MERGE_SOURCE_NUM_INTERNAL_BLOCKS  (0)
#define REMAP_MERGE_BLOCKINFO_PTR_IDX           (0)

#define REMAP_SOURCE_NUM_OUTPUT_BLOCKS          (2U)
#define REMAP_MERGE_SOURCE_NUM_OUTPUT_BLOCKS    (4U)
#define REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX   (0)
#define REMAP_MERGE_LUT_PTR_IDX                 (1U)
#define REMAP_MERGE_MERGE_BLOCK_PTR_IDX         (2U)
#define REMAP_MERGE_ALPHA_BLOCK_PTR_IDX         (3U)

/* For Sink Node */
#define REMAP_MERGE_SINK_NUM_INPUT_BLOCKS       (1U)
#define REMAP_MERGE_OUTPUT_PTR_IDX              (0)
#define REMAP_MERGE_SINK_NUM_INTERNAL_BLOCKS    (0)
#define REMAP_MERGE_SINK_NUM_OUTPUT_BLOCKS      (0)


#define MAX_NUM_PLANES                (2U)
#define MAX_NUM_SCATTER_GATHER_PLANES (5U)
#define MAX_NUM_OUTPUT_BLOCKS         (1024U)

/*!

  @struct Buffer

  @brief  This structure contains the parameters which helps defining an input/output
          buffer

  @param  *ptr   : pointer to the input/output buffer
  @param  stride : stride of the input/output buffer in pixels

*/
typedef struct {
    uint8_t (*ptr)[];      /* pointer to the input/output buffer          */
    uint32_t stride;   /* stride of the input/output buffer in pixels */
} Buffer;

/*!

  @struct dma_scatthergather_params

  @brief  This structure contains the parameters which helps defining an input/output
          buffer

  @param  srcPtr           : pointer to the external buffer
  @param  dstPtr           : pointer to the internal buffer
  @param  srcPtrStride  : stride of the external buffer
  @param  dstPtrStride  : stride of the internal buffer
  @param  blkWidth       : block width
  @param  blkHeight      : block height

*/
typedef struct dma_scatthergather_params {
    uint8_t *srcPtr[MAX_NUM_SCATTER_GATHER_PLANES];
    uint8_t *dstPtr[MAX_NUM_SCATTER_GATHER_PLANES];
    uint16_t srcPtrStride[MAX_NUM_SCATTER_GATHER_PLANES];
    uint16_t dstPtrStride[MAX_NUM_SCATTER_GATHER_PLANES];
    uint16_t blkWidth[MAX_NUM_SCATTER_GATHER_PLANES];
    uint16_t blkHeight[MAX_NUM_SCATTER_GATHER_PLANES];
} DMA_scattherGather_params;


/*!

  @struct bam_dam_custom_remap_merge_node_context

  @brief  This structure is the context of the DMA Source and Sink Node

  @param  autoIncrementDMAContext  : context of Auto Increment 2D DMA
  @param  blockInfoDMAContext          : context of Auto Increment 1D DMA for blockInfo
  @param  inputImageDMAContext       : context of Scatter Gather DMA
  @param  inputImageDMAProp             : properties of Scatter Gather DMA
  @param  scatterGatherParams           : parameters of Scatter Gather DMA
  @param  blockInfoArry                       : Array of ConvertMapBlockInfo
  @param  extImageBlkPtr                    : External Source pointer
  @param  intImageBlkPtr                     : Internal Source pointer
  @param  extLUTPtr                            : External LUT pointer
  @param  intLUTPtr                             : Internal LUT pointer
  @param  srcPixelSize                          : Source Pixel size
  @param  dstPixelSize                          : Destination Pixel size
  @param  flag                                      : Ping Pong flag
  @param  dmaArgs                              : DMA Node Parameters

*/

typedef struct bam_dam_custom_remap_merge_node_context {
    uint8_t               autoIncrementDMAContext[EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE];
    uint8_t               blockInfoDMAContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
    uint8_t               lutDMAContext[EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE];
    uint8_t               inputImageDMAContext[EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE];
    EDMA_UTILS_scattherGather_transferProperties   inputImageDMAProp;
    DMA_scattherGather_params                      scatterGatherParams;
    convertMapBlockInfo   blockInfoArry[2U];
    sTileInfo             tileInfoArry[2U];
    uint8_t             (*extLUTRunningPtr)[];
    uint8_t               numTiles;
    uint8_t               numTilesNext;
    uint8_t               sinkTriggered;
    uint8_t               sourceTriggered;
    int16_t               numBlocks;
    uint16_t              maxNumOutputBlocks;
    uint8_t               outputBlkInfo[MAX_NUM_OUTPUT_BLOCKS];
    Buffer                extImageBlkPtr[MAX_NUM_PLANES];
    uint8_t             (*intImageBlkPtr)[];
    uint8_t             (*extLUTPtr)[];
    uint8_t             (*intLUTPtr)[];
    uint8_t               srcPixelSize;
    uint8_t               dstPixelSize;
    uint8_t               flag;
    uint16_t             *pingPongScatterOffsetPtr[2U];
    uint8_t               pingPongScatterOffsetFlag;
    uint8_t               enableTileApproach;
    int16_t               offsetToDstBufferEnd;
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args dmaArgs;
}BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context;


/* FUNCTION Prototypes */
static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr(
                  void * edmaContext,  void * params);


static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_frameInitChannel(
                       void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_trigger(
                       void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_wait(
                       void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_trigger(
                       void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_wait(
                       void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr(
                                                     void * edmaContext, void * params);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_frameInitChannel(
                                                                            void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_trigger(void * edmaContext);

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_wait(void * edmaContext);




/* Source node is a Scatter Gather + AutoIncrement + AutoIncrement1D node. */

/* Function Definitions */
static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
    const BAM_Remap_Args                       *remapParams;
#if (VCOP_HOST_EMULATION)
    const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *args = (const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *)edmaArgs;
#else
    /* Typecasting by (const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *) will lead to MISRA C 11.5. */
    const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *args = edmaArgs;
#endif
    uint16_t inputTileWidth, inputTileHeight, maxNumPixelsinTile, enableTileApproach;
    uint16_t blockWidth, blockHeight, srcPixelSize, inputTileSize;
    uint32_t outputBlockSize, blockMapBlockSize;
    Format   format;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((edmaArgs == NULL) || (numRecInternal == NULL) || (numRecOutputDataBlock == NULL) || (memRecOutputDataBlock == NULL))
    {
#ifdef DEBUG
      PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_getMemRecFunc ERROR : Argument pointer is NULL\n");
#endif
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    remapParams     = &(args->remapParams);
    if(remapParams->maps.maxInputBlockSize != 0)
    {
        enableTileApproach = 0U;
    }
    else
    {
        enableTileApproach = 1U;
    }

    blockWidth      = remapParams->maps.outputBlockDim.width;
    blockHeight     = remapParams->maps.outputBlockDim.height;
    outputBlockSize = (uint32_t)blockWidth*blockHeight;
    format          = remapParams->maps.srcFormat;

    if(enableTileApproach)
    {
        inputTileWidth  = remapParams->maps.inputTileDim.width;
        inputTileHeight = remapParams->maps.inputTileDim.height;
        inputTileSize   = (inputTileWidth + HORZ_TILE_PADDING) * (inputTileHeight + VERT_TILE_PADDING);

        maxNumPixelsinTile = remapParams->maps.maxNumPixelsinTile;
        blockMapBlockSize  = (uint32_t)(sizeof(uint16_t)+sizeof(uint8_t)+sizeof(uint16_t))*maxNumPixelsinTile;

        /* The 4 bytes are added to store the numMappedPixels and numEvenMappedPixels */
        /* The 16 bytes are added to padding to Scatter store internal buffer */
        blockMapBlockSize += (uint32_t)((3U*sizeof(uint16_t)) + (8U*sizeof(uint16_t)) + 200U);
    }
    else
    {
        inputTileSize     = remapParams->maps.maxInputBlockSize;
        blockMapBlockSize = sizeof(convertMapBlockInfo) + ((sizeof(uint16_t)+sizeof(uint8_t))*outputBlockSize);
    }

    if (format == YUV_420SP) {
        srcPixelSize = 1U;
    }
    else {
        srcPixelSize = (uint16_t)sizeofFormat(format);
    }

    /* Memory for holding the Input Image block in IBUFL */
    /* Input Image block should have stride of multiples of 32 */
    memRecOutputDataBlock[REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX].size = srcPixelSize * inputTileSize;
    memRecOutputDataBlock[REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX].alignment  = 32;

    if(format == YUV_420SP)
    {
        /* Memory for holding the Input Chroma Image block in IBUFL for 420 SP. */
        /* adding 31 because this memory should be 32 bytes aligned as is requirement for (1,2) Table lookup. */
        /* This allocation can be optimized as only maxInputBlockSize/2 is needed.  */
        memRecOutputDataBlock[REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX].size += ((uint32_t)31U + ((uint32_t)inputTileSize/2U));
    }

    /* Memory for holding the blockInfo + LUT block in IBUFL */
    memRecOutputDataBlock[REMAP_MERGE_LUT_PTR_IDX].space = BAM_MEMSPACE_IBUFLA;
    memRecOutputDataBlock[REMAP_MERGE_LUT_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[REMAP_MERGE_LUT_PTR_IDX].size = blockMapBlockSize;
    memRecOutputDataBlock[REMAP_MERGE_LUT_PTR_IDX].alignment  = 32;


    /* Proxy Mem recs for Tile Approach, as during graph creation, it was
            mentioned that there will be 4 edges from Source Node to Remap and Merge node */
    if((enableTileApproach == 1U) && (args->enableMerge == 0U))
    {
        /* Memory for holding the Merge block in IBUFL. Size is multiplied by 2 to consider Chroma. */
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].space = BAM_MEMSPACE_WBUF;
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].size = 4U;
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].alignment  = 4;

        /* Memory for holding the Alpha block in IBUFL */
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].space = BAM_MEMSPACE_WBUF;
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].size = 4U;
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].alignment  = 4;
    }

    if(args->enableMerge == 1)
    {
        /* Memory for holding the Merge block in IBUFL. Size is multiplied by 2 to consider Chroma. */
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].size = 2U * outputBlockSize;
        memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX].alignment  = 4;

        /* Memory for holding the Alpha block in IBUFL */
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].space = BAM_MEMSPACE_IBUFLA;
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].size = outputBlockSize;
        memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX].alignment  = 4;
    }

    *numRecInternal        = REMAP_MERGE_SOURCE_NUM_INTERNAL_BLOCKS;
    *numRecOutputDataBlock = REMAP_SOURCE_NUM_OUTPUT_BLOCKS;
    if((args->enableMerge == 1) || (enableTileApproach != 0))
    {
        *numRecOutputDataBlock = REMAP_MERGE_SOURCE_NUM_OUTPUT_BLOCKS;
    }

EXIT:
    return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
#if (VCOP_HOST_EMULATION)
    const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *args = (const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *)edmaArgs;
#else
    /* Typecasting by (const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *) will lead to MISRA C 11.5. */
    const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *args = edmaArgs;
#endif
    EDMA_UTILS_autoIncrement1D_initParam     lutInitParam;
    EDMA_UTILS_autoIncrement_initParam       initParam;
    const BAM_Remap_Args                    *params;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint8_t *alphaBlockPtr;
    uint8_t (*mergeBlockPtr)[];
    uint16_t roiWidth, roiHeight, blockWidth, blockHeight, i;
    uint16_t numHorzBlocks, numVertBlocks, dstPixelSize, srcPixelSize;
    uint32_t blockInfoSize, blockMapBlockSize, outputBlockSize, autoIncrementContextSize;
    int32_t  status = 0;
    Format   srcFormat, dstFormat;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */

    /* Condition checks */
    if ((context == NULL) || (args == NULL) || (memRecOutputDataBlock == NULL))
    {
#ifdef DEBUG
      PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_setMemRecFunc ERROR : Argument pointer is NULL\n");
#endif
      errCode = DMANODE_EDMA_ERR_NULL_ARGS;
      goto EXIT;
    }

    params = &(args->remapParams);

    if(params->maps.maxInputBlockSize != 0)
    {
        context->enableTileApproach = 0;
    }
    else
    {
        context->enableTileApproach = 1;
    }

    if (numRecInternal != REMAP_MERGE_SOURCE_NUM_INTERNAL_BLOCKS)
    {
#ifdef DEBUG
      PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_setMemRecFunc ERROR : Argument numRecInternal (%d) value is incorrect\n", numRecInternal);
#endif
      errCode = DMANODE_EDMA_ERR_FAILED;
      goto EXIT;
    }

    if((args->enableMerge == 1) || (context->enableTileApproach == 1))
    {
        if (numRecOutputDataBlock != REMAP_MERGE_SOURCE_NUM_OUTPUT_BLOCKS)
        {
#ifdef DEBUG
          PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_setMemRecFunc ERROR : Argument numRecOutputDataBlock (%d) value is incorrect\n", numRecOutputDataBlock);
#endif
          errCode = DMANODE_EDMA_ERR_FAILED;
          goto EXIT;
        }
    }
    else
    {
        if (numRecOutputDataBlock != REMAP_SOURCE_NUM_OUTPUT_BLOCKS)
        {
#ifdef DEBUG
          PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_setMemRecFunc ERROR : Argument numRecOutputDataBlock (%d) value is incorrect\n", numRecOutputDataBlock);
#endif
          errCode = DMANODE_EDMA_ERR_FAILED;
          goto EXIT;
        }
    }

    /* Save configuration params in context */
    context->dmaArgs = *args;

    if(memRecOutputDataBlock[REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      goto EXIT;
    }
    context->intImageBlkPtr = (uint8_t (*)[])memRecOutputDataBlock[REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX]->base;

    if(memRecOutputDataBlock[REMAP_MERGE_LUT_PTR_IDX]->base == NULL)
    {
      errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
      goto EXIT;
    }
    context->intLUTPtr = (uint8_t (*)[])memRecOutputDataBlock[REMAP_MERGE_LUT_PTR_IDX]->base;

    if(args->enableMerge == 1)
    {
        if(memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX]->base == NULL)
        {
          errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
          goto EXIT;
        }
        mergeBlockPtr = (uint8_t (*)[])memRecOutputDataBlock[REMAP_MERGE_MERGE_BLOCK_PTR_IDX]->base;

        if(memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX]->base == NULL)
        {
          errCode = DMANODE_EDMA_ERR_NULL_INT_MEMORY_PTR;
          goto EXIT;
        }
        alphaBlockPtr = (uint8_t *)memRecOutputDataBlock[REMAP_MERGE_ALPHA_BLOCK_PTR_IDX]->base;
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    roiWidth        = params->maps.mapDim.width;
    roiHeight       = params->maps.mapDim.height;
    blockWidth      = params->maps.outputBlockDim.width;
    blockHeight     = params->maps.outputBlockDim.height;
    outputBlockSize = (uint32_t)blockWidth*blockHeight;
    srcFormat       = params->maps.srcFormat;
    dstFormat       = args->dstFormat;

    if(context->enableTileApproach == 0U)
    {
        numHorzBlocks     = roiWidth/blockWidth;
        numVertBlocks     = roiHeight/blockHeight;
        blockInfoSize     = sizeof(convertMapBlockInfo);
        blockMapBlockSize = blockInfoSize + ((sizeof(uint16_t)+sizeof(uint8_t))*outputBlockSize);
    }

    if (dstFormat == YUV_420SP) {
        dstPixelSize = 1U;
    }
    else {
        dstPixelSize = (uint16_t)sizeofFormat(dstFormat);
    }
    context->dstPixelSize = dstPixelSize;

    if (srcFormat == YUV_420SP) {
        srcPixelSize = 1U;
    }
    else {
        srcPixelSize = (uint16_t)sizeofFormat(srcFormat);
    }
    context->srcPixelSize = srcPixelSize;

    /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
    EDMA_UTILS_globalReset();

    /* ------------------------------------------------------------------ */
    /* Configure channel for EDMA transfer. We will use 2 channels, one to DMA In      */
    /* TLU and the other to DMA Out the Remapped and Merged output Image.          */
    /* ------------------------------------------------------------------ */
    i = 0;
    initParam.transferType      = EDMA_UTILS_TRANSFER_IN;

    if(context->enableTileApproach == 0U)
    {
        /* DMA In Channel for ConvertMapBlockInfo + Block_LUT for BB Approach */
        /* In Tile Approach since LUT size is variable, Scatter Gather Utility is used to DMA In */
        lutInitParam.numInTransfers    = 1;
        lutInitParam.numOutTransfers   = 0;
        lutInitParam.transferType      = EDMA_UTILS_TRANSFER_IN;

        lutInitParam.transferProp[0].totalLength          = blockMapBlockSize * numHorzBlocks * numVertBlocks;
        lutInitParam.transferProp[0].numBytes             = blockMapBlockSize;
        lutInitParam.transferProp[0].extMemIncrement      = blockMapBlockSize;
        lutInitParam.transferProp[0].intMemIncrement      = 0;
        lutInitParam.transferProp[0].numCircBuf           = 1;
        lutInitParam.transferProp[0].extMemPtr            = (uint8_t *)params->maps.blockMap;
        lutInitParam.transferProp[0].interMemPtr          = (uint8_t *)*(context->intLUTPtr);
        lutInitParam.transferProp[0].dmaQueNo             = 1;

        autoIncrementContextSize = (uint32_t)EDMA_UTILS_autoIncrement1D_getContextSize();

        /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
        /* Redundant parentheses are added for code readability and is waived.   */

        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */

        /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
        /* REMAP_ASSERT will currently never fail but hence code is unreachable but  */
        /* as the implementation of the function changes, it will not be unreachable.   */
        REMAP_ASSERT(autoIncrementContextSize == EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE, DMANODE_EDMA_ERR_FAILED);
        /* RESET_MISRA("14.1")  -> Reset rule 14.1      */

        status = EDMA_UTILS_autoIncrement1D_init(context->lutDMAContext, &lutInitParam);
        REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);

        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

    }

    if(args->enableMerge == 1) {
        /* DMA In Channel for Merge Frame */
        initParam.transferProp[i].roiWidth             = roiWidth * dstPixelSize;
        initParam.transferProp[i].roiHeight            = roiHeight;
        initParam.transferProp[i].roiOffset            = 0;
        initParam.transferProp[i].blkWidth             = blockWidth * dstPixelSize;
        initParam.transferProp[i].blkHeight            = blockHeight;
        initParam.transferProp[i].extBlkIncrementX     = blockWidth * dstPixelSize;
        initParam.transferProp[i].extBlkIncrementY     = blockHeight;
        initParam.transferProp[i].intBlkIncrementX     = 0;
        initParam.transferProp[i].intBlkIncrementY     = 0;
        initParam.transferProp[i].extMemPtrStride      = roiWidth * dstPixelSize;
        initParam.transferProp[i].interMemPtrStride    = blockWidth * dstPixelSize;
        initParam.transferProp[i].extMemPtr            = NULL;
        initParam.transferProp[i].interMemPtr          = (uint8_t *)*mergeBlockPtr;
        initParam.transferProp[i].dmaQueNo             = 1;
        i++;

        /* DMA In of Chroma of Merge Frame if it is YUV_420 */
        if (dstFormat == YUV_420SP) {
            initParam.transferProp[i].roiWidth             = roiWidth;
            initParam.transferProp[i].roiHeight            = roiHeight >> 1;
            initParam.transferProp[i].roiOffset            = 0;
            initParam.transferProp[i].blkWidth             = blockWidth;
            initParam.transferProp[i].blkHeight            = blockHeight >> 1;
            initParam.transferProp[i].extBlkIncrementX     = blockWidth;
            initParam.transferProp[i].extBlkIncrementY     = blockHeight >> 1;
            initParam.transferProp[i].intBlkIncrementX     = 0;
            initParam.transferProp[i].intBlkIncrementY     = 0;
            initParam.transferProp[i].extMemPtrStride      = roiWidth;
            initParam.transferProp[i].interMemPtrStride    = blockWidth;
            initParam.transferProp[i].extMemPtr            = NULL;
            initParam.transferProp[i].interMemPtr          = (uint8_t *)&(*mergeBlockPtr)[outputBlockSize];
            initParam.transferProp[i].dmaQueNo             = 1;
            i++;
        }

        /* DMA In Channel for Alpha */
        initParam.transferProp[i].roiWidth             = roiWidth;
        initParam.transferProp[i].roiHeight            = roiHeight;
        initParam.transferProp[i].roiOffset            = 0;
        initParam.transferProp[i].blkWidth             = blockWidth;
        initParam.transferProp[i].blkHeight            = blockHeight;
        initParam.transferProp[i].extBlkIncrementX     = blockWidth;
        initParam.transferProp[i].extBlkIncrementY     = blockHeight;
        initParam.transferProp[i].intBlkIncrementX     = 0;
        initParam.transferProp[i].intBlkIncrementY     = 0;
        initParam.transferProp[i].extMemPtrStride      = roiWidth;
        initParam.transferProp[i].interMemPtrStride    = blockWidth;
        initParam.transferProp[i].extMemPtr            = NULL;
        initParam.transferProp[i].interMemPtr          = (uint8_t *)alphaBlockPtr;
        initParam.transferProp[i].dmaQueNo             = 1;
        i++;
    }
    initParam.numInTransfers = i;
    initParam.numOutTransfers = 0;

    autoIncrementContextSize = (uint32_t)EDMA_UTILS_autoIncrement_getContextSize();

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */

    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /* REMAP_ASSERT will currently never fail but hence code is unreachable but  */
    /* as the implementation of the function changes, it will not be unreachable.   */
    REMAP_ASSERT(autoIncrementContextSize == EDMA_UTILS_AUTOINCREMENT_CONTEXT_SIZE,
                                                        DMANODE_EDMA_ERR_FAILED);
    /* RESET_MISRA("14.1")  -> Reset rule 14.1     */

    status = EDMA_UTILS_autoIncrement_init(context->autoIncrementDMAContext,&initParam);
    REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);

    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

EXIT:
    return errCode;
}



static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr(
                  void * edmaContext,  void * params)
{
    IVISION_InBufs                          *inBufs  = (IVISION_InBufs *)params;
    IVISION_BufDesc                       *(*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_REMAP_MERGE_TOTAL];
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args    *args    = &(context->dmaArgs);
    EDMA_UTILS_autoIncrement_updateParams    updateParams;
    EDMA_UTILS_autoIncrement1D_updateParams  lutUpdateParams;
    BAM_Remap_Args                          *remapParams;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
    Format   srcFormat, dstFormat;
    uint16_t dstPixelSize, i, planes, max_planes;
    BAM_Status  status = 0;

    if ((context == NULL) || (inBufs == NULL))
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr ERROR : Context Structure pointer is NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    remapParams     = &(args->remapParams);
    srcFormat       = remapParams->maps.srcFormat;
    dstFormat       = args->dstFormat;
    dstPixelSize    = context->dstPixelSize;
    inBufDesc       = (IVISION_BufDesc *(*)[REMAP_MERGE_TI_BUFDESC_IN_REMAP_MERGE_TOTAL])(void *)inBufs->bufDesc;


    i = 0;
    updateParams.transferType = EDMA_UTILS_TRANSFER_IN;
    updateParams.updateMask   = EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

    /* Update Input Image Block data */
    if (srcFormat == YUV_420SP) {
        max_planes = 2U;
    } else {
        max_planes = 1U;
    }

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    for ( planes = 0; planes < max_planes ; planes++)
    {
        context->extImageBlkPtr[planes].ptr =
            (uint8_t (*)[])(*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[planes].buf;
        context->extImageBlkPtr[planes].stride =
            (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[planes].width;

        if ( context->extImageBlkPtr[planes].ptr == NULL )
        {
#ifdef DEBUG
            PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr ERROR : NULL DDR PTR\n");
#endif
            errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto EXIT;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        }
    }

    /* Update LUT Block Info data */
    context->extLUTPtr        = (uint8_t (*)[])(*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_LUTBUFFER]->bufPlanes[0].buf;
    context->extLUTRunningPtr = context->extLUTPtr;

    if(context->enableTileApproach == 0U)
    {
        lutUpdateParams.transferType = EDMA_UTILS_TRANSFER_IN;
        lutUpdateParams.updateMask = EDMA_UTILS_AUTOINCREMENT_1D_UPDATE_MASK_EXTMEMPTR;
        lutUpdateParams.updateParams[0].extMemPtr = *(context->extLUTPtr);

        status = EDMA_UTILS_autoIncrement1D_update(context->lutDMAContext, &lutUpdateParams);

        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    if( args->enableMerge == 1 )
    {
        /* Update Merge Block data */
        if (dstFormat == YUV_420SP) {
            max_planes = 2U;
        } else {
            max_planes = 1U;
        }
        for ( planes = 0; planes < max_planes ; planes++ )
        {
            updateParams.updateParams[i].extMemPtr       =
              (uint8_t *)(*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_MERGEBUFFER]->bufPlanes[planes].buf;
            updateParams.updateParams[i].extMemPtrStride =
              (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_MERGEBUFFER]->bufPlanes[planes].width *
                  dstPixelSize;

            if ( updateParams.updateParams[i].extMemPtr == NULL )
            {
#ifdef DEBUG
                PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr ERROR : NULL DDR PTR\n");
#endif
                errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
                /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
                /* GOTO is used at error check to jump to end of function, to exit.   */
                goto EXIT;
                /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
            }
            i++;
        }

        /* Update Alpha Block data */
        updateParams.updateParams[i].extMemPtr = (uint8_t *)
            (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_ALPHABUFFER]->bufPlanes[0].buf;
        updateParams.updateParams[i].extMemPtrStride =
            (*inBufDesc)[REMAP_MERGE_TI_BUFDESC_IN_ALPHABUFFER]->bufPlanes[0].width;

        if ( updateParams.updateParams[i].extMemPtr == NULL )
        {
#ifdef DEBUG
            PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr ERROR : NULL DDR PTR\n");
#endif
            errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto EXIT;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
        }

        status = EDMA_UTILS_autoIncrement_update(context->autoIncrementDMAContext , &updateParams);

        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    }
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

 EXIT:
    return errCode;

}

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_frameInitChannel(
                       void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args    *args;
    DMA_scattherGather_params               *scatterGatherParams;
    EDMA_UTILS_autoIncrement1D_initParam          blockInfoinitParam;
    EDMA_UTILS_scattherGather_transferProperties *inputImageTransferProp;
    BAM_Remap_Args                               *params;
    uint16_t numTransfers, roiWidth, roiHeight, blockWidth, blockHeight, i;
    uint16_t numHorzBlocks, numVertBlocks, numBlocks, srcPixelSize;
    uint32_t autoIncrementContextSize, scatterGatherContextSize;
    Format   srcFormat;
    BAM_Status  status = 0;
    DMANODE_EdmaErr  errCode = DMANODE_EDMA_ERR_SUCCESS;
    convertMapBlockInfo                          *blockInfo;
    uint32_t   blockInfoSize, blockMapBlockSize, outputBlockSize;
    uint16_t   inputTileWidth, inputTileHeight, inputTileSize, maxNumPixelsinTile;
    uint32_t   tileInfoSize;
    sTileInfo *tileInfo;
#if (VCOP_HOST_EMULATION)
    uint16_t  *scatterOffsetPtr;
#endif

    if (context == NULL)
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_frameInitChannel ERROR :\
                            Context Structure pointer is NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    args                   = &(context->dmaArgs);
    params                 = &(args->remapParams);
    inputImageTransferProp = &(context->inputImageDMAProp);
    scatterGatherParams    = &(context->scatterGatherParams);

    /* Reset globalStateStruct for every new frame for IN channels before configuring EDMA */
    EDMA_UTILS_globalReset();

    roiWidth        = params->maps.mapDim.width;
    roiHeight       = params->maps.mapDim.height;
    blockWidth      = params->maps.outputBlockDim.width;
    blockHeight     = params->maps.outputBlockDim.height;
    numHorzBlocks   = roiWidth/blockWidth;
    numVertBlocks   = roiHeight/blockHeight;
    numBlocks       = numHorzBlocks * numVertBlocks;
    srcFormat       = params->maps.srcFormat;
    srcPixelSize    = context->srcPixelSize;
    outputBlockSize = (uint32_t)blockWidth*blockHeight;

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    if(context->enableTileApproach)
    {
        inputTileWidth  = params->maps.inputTileDim.width;
        inputTileHeight = params->maps.inputTileDim.height;
        inputTileSize   = (inputTileWidth + HORZ_TILE_PADDING) * (inputTileHeight + VERT_TILE_PADDING);
        tileInfoSize    = params->maps.tileInfoSize;
        maxNumPixelsinTile = params->maps.maxNumPixelsinTile;
        context->maxNumOutputBlocks = numBlocks;

        if(numBlocks <= MAX_NUM_OUTPUT_BLOCKS)
        {
            status = EDMA_UTILS_memcpy2D((void *)context->outputBlkInfo, (const void *)params->maps.outputBlkInfo, numBlocks,
                                         (uint16_t)1, (int16_t)0, (int16_t)0);
        } else
        {
            status = EDMA_UTILS_memcpy2D((void *)context->outputBlkInfo, (const void *)params->maps.outputBlkInfo, MAX_NUM_OUTPUT_BLOCKS,
                                         (uint16_t)1, (int16_t)0, (int16_t)0);
        }
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    } else
    {
        blockInfoSize     = sizeof(convertMapBlockInfo);
        blockMapBlockSize = blockInfoSize + ((sizeof(uint16_t) + sizeof(uint8_t))*outputBlockSize);
    }

    /* ------------------------------------------------------------------ */
    /* Configure channel for EDMA transfer of ConvertMapBlockInfo to DMEM.                           */
    /* ------------------------------------------------------------------ */
    blockInfoinitParam.numInTransfers    = 1;
    blockInfoinitParam.numOutTransfers   = 0;
    blockInfoinitParam.transferType      = EDMA_UTILS_TRANSFER_IN;

    if(context->enableTileApproach)
    {
        blockInfoinitParam.transferProp[0].totalLength          = tileInfoSize;
        blockInfoinitParam.transferProp[0].numBytes             = sizeof(sTileInfo);
        blockInfoinitParam.transferProp[0].extMemIncrement      = sizeof(sTileInfo);
        blockInfoinitParam.transferProp[0].intMemIncrement      = sizeof(sTileInfo);
        blockInfoinitParam.transferProp[0].numCircBuf           = 2;
        blockInfoinitParam.transferProp[0].extMemPtr            = (uint8_t *)(void *)params->maps.tileInfo;
        blockInfoinitParam.transferProp[0].interMemPtr          = (uint8_t *)(void *)context->tileInfoArry;
        blockInfoinitParam.transferProp[0].dmaQueNo             = 1;
    } else
    {
        blockInfoinitParam.transferProp[0].totalLength          = (blockMapBlockSize * numBlocks) - (blockMapBlockSize - blockInfoSize);
        blockInfoinitParam.transferProp[0].numBytes             = blockInfoSize;
        blockInfoinitParam.transferProp[0].extMemIncrement      = blockMapBlockSize;
        blockInfoinitParam.transferProp[0].intMemIncrement      = blockInfoSize;
        blockInfoinitParam.transferProp[0].numCircBuf           = 2;
        blockInfoinitParam.transferProp[0].extMemPtr            = (uint8_t *)*(context->extLUTPtr);
        blockInfoinitParam.transferProp[0].interMemPtr          = (uint8_t *)context->blockInfoArry;
        blockInfoinitParam.transferProp[0].dmaQueNo             = 0;
    }
    autoIncrementContextSize = (uint32_t)EDMA_UTILS_autoIncrement1D_getContextSize();

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */

    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /* REMAP_ASSERT will currently never fail but hence code is unreachable but  */
    /* as the implementation of the function changes, it will not be unreachable.   */
    REMAP_ASSERT(autoIncrementContextSize == EDMA_UTILS_AUTOINCREMENT_1D_CONTEXT_SIZE,
                                                        DMANODE_EDMA_ERR_FAILED);
    /* RESET_MISRA("14.1")  -> Reset rule 14.1     */

    status = EDMA_UTILS_autoIncrement1D_init(context->blockInfoDMAContext,&blockInfoinitParam);
    REMAP_ASSERT((status == 0), DMANODE_EDMA_ERR_FAILED);

    status = EDMA_UTILS_autoIncrement1D_configure(context->blockInfoDMAContext , EDMA_UTILS_TRANSFER_IN);
    REMAP_ASSERT((status == 0), DMANODE_EDMA_ERR_FAILED);

    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    /* ------------------------------------------------------------------ */
    /* Wait for BlockInfo to be available in DMEM to Configure transfer of Input Image Block      */
    /* ------------------------------------------------------------------ */
    EDMA_UTILS_autoIncrement1D_triggerInChannel(context->blockInfoDMAContext);

    if(context->enableTileApproach)
    {
        tileInfo      = &(context->tileInfoArry[0]);
    } else
    {
        blockInfo     = &(context->blockInfoArry[0]);
    }
    context->flag = 1;
    context->pingPongScatterOffsetFlag = 0;

    /* ------------------------------------------------------------------ */
    /* Wait for BlockInfo to be available in DMEM to Configure transfer of Input Image Block      */
    /* ------------------------------------------------------------------ */
    EDMA_UTILS_autoIncrement1D_waitInChannel(context->blockInfoDMAContext);

    /* ------------------------------------------------------------------ */
    /* Configure channel for EDMA transfer of Input Image Block of variable size.                       */
    /* ------------------------------------------------------------------ */
    scatterGatherContextSize = (uint32_t)EDMA_UTILS_scattherGather_getContextSize();

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    REMAP_ASSERT(scatterGatherContextSize == EDMA_UTILS_SCATTERGATHER_CONTEXT_SIZE,
                                                        DMANODE_EDMA_ERR_FAILED);
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    /* ----------------------------------------------------- */
    /* Use the DMA'ed IN blockInfo information to configure and DMA IN         */
    /* Input Image Block/Tile and/or LUT.                                                      */
    /* ----------------------------------------------------- */
    i = 0;

    if(context->enableTileApproach)
    {
        scatterGatherParams->srcPtr[i]       = *(context->extImageBlkPtr[0].ptr) +
                                               ((tileInfo->inBlock_x + (tileInfo->inBlock_y*context->extImageBlkPtr[0].stride)) * srcPixelSize);
        scatterGatherParams->dstPtr[i]       = *(context->intImageBlkPtr);
        scatterGatherParams->srcPtrStride[i] = context->extImageBlkPtr[0].stride * srcPixelSize;
        scatterGatherParams->dstPtrStride[i] = (inputTileWidth + HORZ_TILE_PADDING) * srcPixelSize;
        scatterGatherParams->blkWidth[i]     = (inputTileWidth + HORZ_TILE_PADDING) * srcPixelSize;
        scatterGatherParams->blkHeight[i]    = inputTileHeight + VERT_TILE_PADDING;
        i++;

        if (srcFormat == YUV_420SP) {
            scatterGatherParams->srcPtr[i]       = *(context->extImageBlkPtr[1].ptr) +
                                                   (tileInfo->inBlock_x + ((tileInfo->inBlock_y >> 1)*context->extImageBlkPtr[1].stride));
            scatterGatherParams->dstPtr[i]       = *(context->intImageBlkPtr) + (uint32_t)ALIGN_TLU((uint32_t)inputTileSize);
            scatterGatherParams->srcPtrStride[i] = context->extImageBlkPtr[1].stride;
            scatterGatherParams->dstPtrStride[i] = inputTileWidth + HORZ_TILE_PADDING;
            scatterGatherParams->blkWidth[i]     = inputTileWidth + HORZ_TILE_PADDING;
            scatterGatherParams->blkHeight[i]    = (inputTileHeight + VERT_TILE_PADDING) >> 1;
            i++;
        }

        /* ------------------------------------------------------------------ */
        /* Configure channel for EDMA transfer of LUT to IBUFL.                                                      */
        /* ------------------------------------------------------------------ */
        /* EDMA configuration for LUT integer indexes + sTileLutHeader. */
        scatterGatherParams->srcPtr[i]       = *(context->extLUTRunningPtr);
        /* intLUTPtr is 32 B aligned. And LUT integer indexes should start at 32B aligned address. */
        scatterGatherParams->dstPtr[i]       = *(context->intLUTPtr) + (32 - sizeof(sTileLutHeader));
        scatterGatherParams->srcPtrStride[i] = sizeof(sTileLutHeader) + (tileInfo->numPixels*sizeof(uint16_t));
        scatterGatherParams->dstPtrStride[i] = sizeof(sTileLutHeader) + (tileInfo->numPixels*sizeof(uint16_t));
        scatterGatherParams->blkWidth[i]     = sizeof(sTileLutHeader) + (tileInfo->numPixels*sizeof(uint16_t));
        scatterGatherParams->blkHeight[i]    = 1U;
        i++;
        context->extLUTRunningPtr = (uint8_t (*)[])(*(context->extLUTRunningPtr) +
                                    (sizeof(sTileLutHeader) + (tileInfo->numPixels*sizeof(uint16_t))));

        /* EDMA configuration for LUT fractional indexes. */
        scatterGatherParams->srcPtr[i]       = *(context->extLUTRunningPtr);
        scatterGatherParams->dstPtr[i]       = *(uint8_t (*)[])(void *)scatterGatherParams->dstPtr[i - 1U] +
                                               sizeof(sTileLutHeader) + (ALIGN_TLU((uint32_t)maxNumPixelsinTile)*sizeof(uint16_t));
        scatterGatherParams->srcPtrStride[i] = tileInfo->numPixels*sizeof(uint8_t);
        scatterGatherParams->dstPtrStride[i] = tileInfo->numPixels*sizeof(uint8_t);
        scatterGatherParams->blkWidth[i]     = tileInfo->numPixels*sizeof(uint8_t);
        scatterGatherParams->blkHeight[i]    = 1U;
        i++;
        context->extLUTRunningPtr = (uint8_t (*)[])(*(context->extLUTRunningPtr) +
                                    (ALIGN_SHORT((uint32_t)tileInfo->numPixels)*sizeof(uint8_t)));

        /* EDMA configuration for output scatter offset indexes. */
        scatterGatherParams->srcPtr[i]       = *(context->extLUTRunningPtr);
        scatterGatherParams->dstPtr[i]       = *(uint8_t (*)[])(void *)scatterGatherParams->dstPtr[i - 1U] +
                                               (ALIGN_TLU((uint32_t)maxNumPixelsinTile)*sizeof(uint8_t));
        scatterGatherParams->srcPtrStride[i] = tileInfo->numPixels*sizeof(uint16_t);
        scatterGatherParams->dstPtrStride[i] = tileInfo->numPixels*sizeof(uint16_t);
        scatterGatherParams->blkWidth[i]     = tileInfo->numPixels*sizeof(uint16_t);
        scatterGatherParams->blkHeight[i]    = 1U;
        i++;

        context->extLUTRunningPtr = (uint8_t (*)[])(*(context->extLUTRunningPtr) +
                                    (tileInfo->numPixels*sizeof(uint16_t)));
        numTransfers = i;

        inputImageTransferProp->updateMask   = (uint8_t)(EDMA_UTILS_SCATTERGATHER_UPDATE_BLOCK_W | EDMA_UTILS_SCATTERGATHER_UPDATE_SRCPTR_STRIDE);

        /* Calculating a safe scatteroffset based on the format. A safe offset is typically
              the end of the destination buffer. During memory allocation of this buffer, extra memory is
              considered to support scatter storing into end of buffer. */
        if ((srcFormat== U8BIT) || (srcFormat== S8BIT) || (srcFormat== YUV_422ILE) || (srcFormat== YUV_422IBE)) {
            context->offsetToDstBufferEnd = outputBlockSize;
        } else if (srcFormat== YUV_420SP) {
            context->offsetToDstBufferEnd = (3U*outputBlockSize)/2U;
        } else {
            context->offsetToDstBufferEnd = 2U*outputBlockSize;
        }

        /* The kernel will read scatterOffsets in blocks of 8 (VCOP_SIMD_WIDTH).
              Since scatterOffsets can be of variable length, it is necessary to append or post-fix
              the scatterOffsets with a safe offset, so that the kernel does not read junk scatteroffsets
              and store pixels into those random locations, thereby corrupting the memory.*/
        context->pingPongScatterOffsetPtr[0] = (uint16_t *)(void *)scatterGatherParams->dstPtr[i - 1U];
#if (!VCOP_HOST_EMULATION)
        context->pingPongScatterOffsetPtr[1] = *(uint16_t (*)[])(void *)scatterGatherParams->dstPtr[i - 1U] +
                                                             (REMAP_MERGE_IMG_BUF_A_B_OFFSET/2U);
#else
        context->pingPongScatterOffsetPtr[1] = (uint16_t *)(void *)scatterGatherParams->dstPtr[i - 1U];

        /* Because of difference in code flow between Host Emulation and Target, the below code is
              required. In Target, since the first Trigger_wait() is invoked before the first VCOP processing, the code
              to update offsets at end of Scatter offset is in Trigger_wait(). */
        scatterOffsetPtr  = context->pingPongScatterOffsetPtr[context->pingPongScatterOffsetFlag] +
                            context->tileInfoArry[context->pingPongScatterOffsetFlag].numPixels;

        for(i = 0; i < VCOP_SIMD_WIDTH; i++)
        {
            *scatterOffsetPtr++ = context->offsetToDstBufferEnd;
        }
        context->pingPongScatterOffsetFlag = context->pingPongScatterOffsetFlag^1;
#endif

    } else
    {
        numTransfers = 1U;
        scatterGatherParams->srcPtr[0]       = *(context->extImageBlkPtr[0].ptr) +
                                               ((blockInfo->inBlock_x + (blockInfo->inBlock_y*context->extImageBlkPtr[0].stride)) * srcPixelSize);
        scatterGatherParams->dstPtr[0]       = *(context->intImageBlkPtr);
        scatterGatherParams->srcPtrStride[0] = context->extImageBlkPtr[0].stride * srcPixelSize;
        scatterGatherParams->dstPtrStride[0] = blockInfo->inputBlockWidth * srcPixelSize;
        scatterGatherParams->blkWidth[0]     = blockInfo->inputBlockWidth * srcPixelSize;
        scatterGatherParams->blkHeight[0]    = blockInfo->inputBlockHeight;

        if (srcFormat == YUV_420SP) {
            numTransfers = 2U;
            scatterGatherParams->srcPtr[1]       = *(context->extImageBlkPtr[1].ptr) +
                                                   (blockInfo->inBlock_x + ((blockInfo->inBlock_y >> 1)*context->extImageBlkPtr[1].stride));
            scatterGatherParams->dstPtr[1]       = *(context->intImageBlkPtr) + ALIGN_TLU((uint32_t)params->maps.maxInputBlockSize);
            scatterGatherParams->srcPtrStride[1] = context->extImageBlkPtr[1].stride;
            scatterGatherParams->dstPtrStride[1] = blockInfo->inputBlockWidth;
            scatterGatherParams->blkWidth[1]     = blockInfo->inputBlockWidth;
            scatterGatherParams->blkHeight[1]    = blockInfo->inputBlockHeight >> (uint16_t)1U;
        }
        inputImageTransferProp->updateMask   = (uint8_t)EDMA_UTILS_SCATTERGATHER_UPDATE_ALL;

    }

    inputImageTransferProp->dmaQueNo     = 0;
    inputImageTransferProp->srcPtr       = scatterGatherParams->srcPtr;
    inputImageTransferProp->dstPtr       = scatterGatherParams->dstPtr;
    inputImageTransferProp->srcPtrStride = scatterGatherParams->srcPtrStride;
    inputImageTransferProp->dstPtrStride = scatterGatherParams->dstPtrStride;
    inputImageTransferProp->blkWidth     = scatterGatherParams->blkWidth;
    inputImageTransferProp->blkHeight    = scatterGatherParams->blkHeight;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */

    status = EDMA_UTILS_scattherGather_init((void *)context->inputImageDMAContext, inputImageTransferProp, (uint8_t)numTransfers);
    REMAP_ASSERT((status == 0), DMANODE_EDMA_ERR_FAILED);

    if(context->enableTileApproach == 0U)
    {
        status = EDMA_UTILS_autoIncrement1D_configure(context->lutDMAContext, EDMA_UTILS_TRANSFER_IN);
        REMAP_ASSERT((status == 0), DMANODE_EDMA_ERR_FAILED);
    }

    if(args->enableMerge == 1)
    {
        status = EDMA_UTILS_autoIncrement_configure(context->autoIncrementDMAContext , EDMA_UTILS_TRANSFER_IN);
        REMAP_ASSERT((status == 0), DMANODE_EDMA_ERR_FAILED);
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

EXIT:
    return errCode;
}


static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_trigger(
                    void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

#ifdef DEBUG
    BAM_Status         status;
    status = 0;
#endif

    EDMA_UTILS_autoIncrement1D_triggerInChannel(context->blockInfoDMAContext);
#ifdef DEBUG
    status =
#endif
    EDMA_UTILS_scattherGather_updateNtrigger(context->inputImageDMAContext, &(context->inputImageDMAProp));

    if((context->numTilesNext == 1) || ((context->numTiles == 2) && (context->dmaArgs.enableMerge == 1)))
    {
        EDMA_UTILS_autoIncrement_triggerInChannel(context->autoIncrementDMAContext);
        context->sourceTriggered = 1;
        context->numTilesNext = 0;
    }

#ifdef DEBUG
    if ( status != 0)
    {
      PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_trigger ERROR : EDMA_UTILS_scattherGather_updateNtrigger\
              Returned an error \n");
      errCode = DMANODE_EDMA_ERR_FAILED;
    }
#endif

    return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_wait(
                      void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context      *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    EDMA_UTILS_scattherGather_transferProperties *inputImageTransferProp = &(context->inputImageDMAProp);
    sTileInfo *tileInfo;
    uint16_t (*scatterOffsetPtr)[];
    uint8_t *(*scatterGatherPtrList)[];
    uint16_t (*scatterGatherWidthList)[];
    uint8_t    i;


    EDMA_UTILS_autoIncrement1D_waitInChannel(context->blockInfoDMAContext);

    /* This corresponds to the tileInfo DMA'ed in the previous iteration */
    tileInfo  = &(context->tileInfoArry[context->flag]);

    /* Ping - Pong */
    context->flag = context->flag^(1U);

    /* ------------------------------------------------------------- */
    /* Use the BlockInfo to configure and DMA In Input Image Block for (N) Block */
    /* ------------------------------------------------------------- */
    scatterGatherPtrList   = (uint8_t *(*)[])(void *)inputImageTransferProp->srcPtr;
    scatterGatherWidthList = (uint16_t (*)[])(void *)inputImageTransferProp->blkWidth;

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    i = 0;
    (*scatterGatherPtrList)[i] = *(context->extImageBlkPtr[0].ptr) +
                              ((tileInfo->inBlock_x + (tileInfo->inBlock_y*context->extImageBlkPtr[0].stride)) * context->srcPixelSize);
    i++;

    if (context->dmaArgs.remapParams.maps.srcFormat == YUV_420SP) {
        (*scatterGatherPtrList)[i] = *(context->extImageBlkPtr[1].ptr) +
                                      (tileInfo->inBlock_x + ((tileInfo->inBlock_y >> 1)*context->extImageBlkPtr[1].stride));
        i++;
    }

    (*scatterGatherPtrList)[i]   = *(context->extLUTRunningPtr);
    (*scatterGatherWidthList)[i] = ((uint16_t)3U + tileInfo->numPixels)*sizeof(uint16_t);
    i++;
    context->extLUTRunningPtr    = (uint8_t (*)[])(*(context->extLUTRunningPtr) +
                                   ((3U + tileInfo->numPixels)*sizeof(uint16_t)));

    (*scatterGatherPtrList)[i]   = *(context->extLUTRunningPtr);
    (*scatterGatherWidthList)[i] = tileInfo->numPixels*sizeof(uint8_t);
    i++;
    context->extLUTRunningPtr    = (uint8_t (*)[])(*(context->extLUTRunningPtr) +
                                   (ALIGN_SHORT((uint32_t)tileInfo->numPixels)*sizeof(uint8_t)));

    (*scatterGatherPtrList)[i]   = *(context->extLUTRunningPtr);
    (*scatterGatherWidthList)[i] = tileInfo->numPixels*sizeof(uint16_t);

    context->extLUTRunningPtr    = (uint8_t (*)[])(*(context->extLUTRunningPtr) +
                                   (tileInfo->numPixels*sizeof(uint16_t)));


    scatterOffsetPtr  = (uint16_t (*)[])(void *)(*(uint16_t (*)[])(void *)context->pingPongScatterOffsetPtr[context->pingPongScatterOffsetFlag] +
                        context->tileInfoArry[context->pingPongScatterOffsetFlag].numPixels);

    for(i = 0; i < VCOP_SIMD_WIDTH; i++)
    {
        (*scatterOffsetPtr)[i] = context->offsetToDstBufferEnd;
    }

    context->pingPongScatterOffsetFlag = context->pingPongScatterOffsetFlag ^ (1U);

    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

    /* Wait ony in the last but one iteration */
    if(context->sourceTriggered)
    {
        EDMA_UTILS_autoIncrement_waitInChannel(context->autoIncrementDMAContext);
        context->sourceTriggered = 0;
    }

    EDMA_UTILS_scattherGather_wait(context->inputImageDMAContext);

    return DMANODE_EDMA_ERR_SUCCESS;
}


/* Source Trigger and Wait functions for BB Approach. */
static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_trigger(
                        void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

#ifdef DEBUG
    BAM_Status         status;
    status = 0;
#endif

    EDMA_UTILS_autoIncrement1D_triggerInChannel(context->blockInfoDMAContext);
    EDMA_UTILS_autoIncrement1D_triggerInChannel(context->lutDMAContext);

#ifdef DEBUG
    status =
#endif
    EDMA_UTILS_scattherGather_updateNtrigger(context->inputImageDMAContext, &(context->inputImageDMAProp));

    if(context->dmaArgs.enableMerge == 1)
    {
        EDMA_UTILS_autoIncrement_triggerInChannel(context->autoIncrementDMAContext);
    }

#ifdef DEBUG
    if ( status != 0)
    {
#ifdef DEBUG
      PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_trigger ERROR : EDMA_UTILS_scattherGather_updateNtrigger\
              Returned an error \n");
#endif
      errCode = DMANODE_EDMA_ERR_FAILED;
    }
#endif

    return errCode;
}

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_wait(
                      void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context      *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    EDMA_UTILS_scattherGather_transferProperties *inputImageTransferProp = &(context->inputImageDMAProp);
    convertMapBlockInfo                          *blockInfo;

    EDMA_UTILS_autoIncrement1D_waitInChannel(context->blockInfoDMAContext);

    /* This corresponds to the ConvertMapBlockInfo DMA'ed in the previous iteration */
    blockInfo = &(context->blockInfoArry[context->flag]);

    context->flag = context->flag^(1U);

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    /* ------------------------------------------------------------- */
    /* Use the BlockInfo to configure and DMA In Input Image Block for (N) Block */
    /* ------------------------------------------------------------- */
    (*(uint8_t *(*)[])(void *)inputImageTransferProp->srcPtr)[0]       = *(context->extImageBlkPtr[0].ptr) +
                                  ((blockInfo->inBlock_x + (blockInfo->inBlock_y*context->extImageBlkPtr[0].stride)) * context->srcPixelSize);
    (*(uint16_t (*)[])(void *)inputImageTransferProp->dstPtrStride)[0] = blockInfo->inputBlockWidth * context->srcPixelSize;
    (*(uint16_t (*)[])(void *)inputImageTransferProp->blkWidth)[0]     = blockInfo->inputBlockWidth * context->srcPixelSize;
    (*(uint16_t (*)[])(void *)inputImageTransferProp->blkHeight)[0]    = blockInfo->inputBlockHeight;

    if (context->dmaArgs.remapParams.maps.srcFormat == YUV_420SP) {
        (*(uint8_t *(*)[])(void *)inputImageTransferProp->srcPtr)[1]       = *(context->extImageBlkPtr[1].ptr) +
                                       (blockInfo->inBlock_x + ((blockInfo->inBlock_y >> 1)*context->extImageBlkPtr[1].stride));
        (*(uint16_t (*)[])(void *)inputImageTransferProp->dstPtrStride)[1] = blockInfo->inputBlockWidth;
        (*(uint16_t (*)[])(void *)inputImageTransferProp->blkWidth)[1]     = blockInfo->inputBlockWidth;
        (*(uint16_t (*)[])(void *)inputImageTransferProp->blkHeight)[1]    = blockInfo->inputBlockHeight >> (uint16_t)1U;
    }

    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

    EDMA_UTILS_autoIncrement_waitInChannel(context->autoIncrementDMAContext);
    EDMA_UTILS_autoIncrement1D_waitInChannel(context->lutDMAContext);

    if(context->dmaArgs.enableMerge == 1)
    {
        EDMA_UTILS_scattherGather_wait(context->inputImageDMAContext);
    }
    return DMANODE_EDMA_ERR_SUCCESS;
}



BAM_KernelInfo gBAM_TI_dmaCustomRemapMergeTileApproachNodeReadKernel =
{
  0,                                         /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context),
  sizeof(BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args),
  BAM_EVE_ARP32,                             /*coreType*/
  BAM_NODE_SOURCE,                           /*nodeType*/
  REMAP_MERGE_SOURCE_NUM_INPUT_BLOCKS,       /*numInputDataBlocks */
  REMAP_MERGE_SOURCE_NUM_OUTPUT_BLOCKS,      /*numOutputDataBlocks */
  REMAP_MERGE_SOURCE_NUM_INTERNAL_BLOCKS     /*numRecInternal */
};

BAM_KernelInfo gBAM_TI_dmaCustomRemapMergeBBApproachNodeReadKernel =
{
  0,                                         /*kernelId*/
  sizeof(BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context),
  sizeof(BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args),
  BAM_EVE_ARP32,                             /*coreType*/
  BAM_NODE_SOURCE,                           /*nodeType*/
  REMAP_MERGE_SOURCE_NUM_INPUT_BLOCKS,       /*numInputDataBlocks */
  REMAP_MERGE_SOURCE_NUM_OUTPUT_BLOCKS,      /*numOutputDataBlocks */
  REMAP_MERGE_SOURCE_NUM_INTERNAL_BLOCKS     /*numRecInternal */
};


/* Source Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_dmaCustomRemapMergeNodeReadKernelHelperFunc =
{
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_setMemRecFunc  /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

/* Exec Func for Tile Approach */
BAM_KernelExecFuncDef gBAM_TI_dmaCustomRemapMergeTileApproachNodeReadKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_frameInitChannel,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_trigger,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_TileApproach_wait,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr,
  NULL
};


/* Exec Func for BB Approach */
BAM_KernelExecFuncDef gBAM_TI_dmaCustomRemapMergeBBApproachNodeReadKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_frameInitChannel,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_trigger,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_BBApproach_wait,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SOURCE_updateDDRptr,
  NULL
};



static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_getMemRecFunc(
        const void *edmaArgs, BAM_MemRec memRecInternal[], BAM_MemRec memRecOutputDataBlock[],
        uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;

    /* Not checking memRecInternal pointer since it is not used in this function */
    if ((edmaArgs == NULL) || (numRecInternal == NULL) || (numRecOutputDataBlock == NULL))
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_getMemRecFunc ERROR : Argument pointer is NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    *numRecOutputDataBlock = 0;
    *numRecInternal = 0;

EXIT:
    return errCode;
}



static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_setMemRecFunc(
        const BAM_MemRec *memRecInternal[], const BAM_MemRec *memRecInputDataBlock[],
        const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecInputDataBlock,
        uint8_t numRecOutputDataBlock, void *edmaContext, const void *edmaArgs)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
#if (VCOP_HOST_EMULATION)
    const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *args = (const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *)edmaArgs;
#else
    /* Typecasting by (const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *) will lead to MISRA C 11.5. */
    const BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args *args = edmaArgs;
#endif
    EDMA_UTILS_autoIncrement_initParam       initParam;
    const BAM_Remap_Args                    *params;
    DMANODE_EdmaErr errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint16_t roiWidth, roiHeight, blockWidth, blockHeight, dstPixelSize;
    uint32_t outputBlockSize;
    Format   dstFormat;
    int32_t  status = 0;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */

    if (edmaContext == NULL)
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_setMemRecFunc ERROR : Context Structure pointer is NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }
    if ((memRecInputDataBlock == NULL) || (args == NULL))
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_setMemRecFunc ERROR : Argument pointer is NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }

    if (numRecInputDataBlock != REMAP_MERGE_SINK_NUM_INPUT_BLOCKS)
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_setMemRecFunc ERROR : Argument numRecInputDataBlock \
                (%d) value is incorrect\n", numRecInputDataBlock);
#endif
        errCode = DMANODE_EDMA_ERR_FAILED;
        goto EXIT;
    }
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    params          = &(args->remapParams);

    roiWidth        = params->maps.mapDim.width;
    roiHeight       = params->maps.mapDim.height;
    blockWidth      = params->maps.outputBlockDim.width;
    blockHeight     = params->maps.outputBlockDim.height;
    outputBlockSize = (uint32_t)blockWidth*blockHeight;
    dstFormat       = args->dstFormat;
    dstPixelSize    = context->dstPixelSize;

    /* DMA Out Channel for Remapped or Format Converted or Alpha Blended Output */
    initParam.numOutTransfers                      = 1;
    initParam.transferType                         = EDMA_UTILS_TRANSFER_OUT;
    initParam.transferProp[0].roiWidth             = roiWidth * dstPixelSize;
    initParam.transferProp[0].roiHeight            = roiHeight;
    initParam.transferProp[0].roiOffset            = 0;
    initParam.transferProp[0].blkWidth             = blockWidth * dstPixelSize;
    initParam.transferProp[0].blkHeight            = blockHeight;
    initParam.transferProp[0].extBlkIncrementX     = blockWidth * dstPixelSize;
    initParam.transferProp[0].extBlkIncrementY     = blockHeight;
    initParam.transferProp[0].intBlkIncrementX     = 0;
    initParam.transferProp[0].intBlkIncrementY     = 0;
    initParam.transferProp[0].extMemPtrStride      = roiWidth * dstPixelSize;
    initParam.transferProp[0].interMemPtrStride    = blockWidth * dstPixelSize;
    initParam.transferProp[0].extMemPtr            = NULL;
    initParam.transferProp[0].interMemPtr          = (uint8_t *)memRecInputDataBlock[0]->base;
    initParam.transferProp[0].dmaQueNo             = 1;


    /* DMA Out Channel of Chroma for YUV_420 */
    if (dstFormat == YUV_420SP) {
        initParam.numOutTransfers                      = 2;
        initParam.transferProp[1].roiWidth             = roiWidth;
        initParam.transferProp[1].roiHeight            = roiHeight >> 1;
        initParam.transferProp[1].roiOffset            = 0;
        initParam.transferProp[1].blkWidth             = blockWidth;
        initParam.transferProp[1].blkHeight            = blockHeight >> 1;
        initParam.transferProp[1].extBlkIncrementX     = blockWidth;
        initParam.transferProp[1].extBlkIncrementY     = blockHeight >> 1;
        initParam.transferProp[1].intBlkIncrementX     = 0;
        initParam.transferProp[1].intBlkIncrementY     = 0;
        initParam.transferProp[1].extMemPtrStride      = roiWidth;
        initParam.transferProp[1].interMemPtrStride    = blockWidth;
        initParam.transferProp[1].extMemPtr            = NULL;
        initParam.transferProp[1].interMemPtr          = *(uint8_t (*)[])memRecInputDataBlock[0]->base + outputBlockSize;
        initParam.transferProp[1].dmaQueNo             = 1;
    }

    /* In case of BB Approach and if Merge is enabled. */
    if((context->enableTileApproach == 0U) && (args->enableMerge == 1U))
    {
        initParam.transferProp[0].dmaQueNo             = 0;
        initParam.transferProp[1].dmaQueNo             = 0;
    }

    status = EDMA_UTILS_autoIncrement_init(context->autoIncrementDMAContext,&initParam);

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

EXIT:
    return errCode;
}



static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr(
                                                     void * edmaContext, void * params)
{
    IVISION_OutBufs                             *outBufs = (IVISION_OutBufs *)params;
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args    *args    = &(context->dmaArgs);
    EDMA_UTILS_autoIncrement_updateParams    updateParams;
    IVISION_BufDesc      *(*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_TOTAL];
    BAM_Status                 status = 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;
    uint32_t                dstPixelSize;

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */

    if (context == NULL)
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr ERROR : Context Structure pointer is NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        goto EXIT;
    }

    if (outBufs == NULL)
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr ERROR : updateParams NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_ARGS;
        goto EXIT;
    }
    outBufDesc = (IVISION_BufDesc *(*)[REMAP_MERGE_TI_BUFDESC_OUT_TOTAL])(void *)outBufs->bufDesc;

    dstPixelSize    = context->dstPixelSize;

    updateParams.transferType = EDMA_UTILS_TRANSFER_OUT;
    updateParams.updateMask   = EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTR |
                                EDMA_UTILS_AUTOINCREMENT_UPDATE_MASK_EXTMEMPTRSTRIDE;

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    updateParams.updateParams[0].extMemPtr       =
        (uint8_t *)(*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER]->bufPlanes[0].buf;
    updateParams.updateParams[0].extMemPtrStride =
                   (*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER]->bufPlanes[0].width * dstPixelSize;

    if (updateParams.updateParams[0].extMemPtr == NULL)
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr ERROR : NULL DDR PTR\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
        goto EXIT;
    }

    if (args->dstFormat == YUV_420SP)
    {
        updateParams.updateParams[1].extMemPtr       =
          (uint8_t *)(*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER]->bufPlanes[1].buf;
        updateParams.updateParams[1].extMemPtrStride =
                     (*outBufDesc)[REMAP_MERGE_TI_BUFDESC_OUT_REMAPBUFFER]->bufPlanes[1].width;

        if (updateParams.updateParams[1].extMemPtr == NULL)
        {
#ifdef DEBUG
            PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr ERROR : NULL DDR PTR\n");
#endif
            errCode = DMANODE_EDMA_ERR_NULL_DDR_PTR;
            goto EXIT;
        }

    }

    status = EDMA_UTILS_autoIncrement_update(context->autoIncrementDMAContext , &updateParams);
    REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);

    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

EXIT:
    return errCode;

}

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_frameInitChannel(
                                                                            void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    BAM_Status                 status = 0;
    DMANODE_EdmaErr         errCode = DMANODE_EDMA_ERR_SUCCESS;

    if (context == NULL)
    {
#ifdef DEBUG
        PRINTF("BAM_DMA_CUSTOM_REMAP_MERGE_SINK_frameInitChannel ERROR : Context Structure pointer is NULL\n");
#endif
        errCode = DMANODE_EDMA_ERR_NULL_CONTEXT;
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto EXIT;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    }

    if(context->enableTileApproach)
    {
        /* numTiles set to 1 to forcefully call TriggerOut as first one is dummy call. */
        context->numTiles      = 1;
        context->numBlocks     = 0;
        context->sinkTriggered = 0;
        context->sourceTriggered = 0;
        if(context->dmaArgs.enableMerge)
        {
            context->numTilesNext  = context->outputBlkInfo[context->numBlocks];
        } else
        {
            context->numTilesNext  = 0;
        }
    }

    status = EDMA_UTILS_autoIncrement_configure(context->autoIncrementDMAContext, EDMA_UTILS_TRANSFER_OUT);

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
    /* GOTO is used at error check to jump to end of function, to exit.   */
    REMAP_ASSERT(status == 0, DMANODE_EDMA_ERR_FAILED);
    /* RESET_MISRA("14.4")  -> Reset rule 14.4     */
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

EXIT:
    return errCode;

}


static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_trigger(void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;
    int32_t                                  edmaSinkStatus = 0;

    context->numTiles--;
    remapNumTiles = context->numTiles;

    if(context->numTiles == 0)
    {
        edmaSinkStatus = EDMA_UTILS_autoIncrement_triggerOutChannel(context->autoIncrementDMAContext);
        context->numTiles = context->outputBlkInfo[context->numBlocks];
        context->numBlocks++;
        remapNumTiles = context->numTiles;
        context->sinkTriggered = 1;
        if(edmaSinkStatus == 1)
        {
            context->numBlocks = -1;
        }
    }

    if((context->numTiles == 1) && (context->dmaArgs.enableMerge == 1U))
    {
        context->numTilesNext = context->outputBlkInfo[context->numBlocks];
    }

    /* CHECK_MISRA("-14.7")  -> Disable rule 14.7  */
    /* return() to handle exit condition.   */

    /* Exit condition: Once TriggerOut returns 1, wait till all the tiles corresponding to the */
    /* last output block is processed, and then return 1 to BAM as sinkstatus.                 */
    if((context->numTiles == 1) && (context->numBlocks == -1))
    {
        return (1);
    }
    /* RESET_MISRA("14.7")  -> Reset rule 14.7     */

    return (DMANODE_EDMA_ERR_SUCCESS);
}

static BAM_Status BAM_DMA_CUSTOM_REMAP_MERGE_SINK_wait(void * edmaContext)
{
    BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *context = (BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Context *)edmaContext;

    if(context->sinkTriggered)
    {
        if(context->numBlocks == MAX_NUM_OUTPUT_BLOCKS)
        {
            context->maxNumOutputBlocks = context->maxNumOutputBlocks - MAX_NUM_OUTPUT_BLOCKS;
            context->numBlocks = 0;
            if(context->maxNumOutputBlocks <= MAX_NUM_OUTPUT_BLOCKS)
            {
                EDMA_UTILS_memcpy2D(context->outputBlkInfo,
                                   *(uint8_t (*)[])(void *)context->dmaArgs.remapParams.maps.outputBlkInfo + MAX_NUM_OUTPUT_BLOCKS,
                                    context->maxNumOutputBlocks,
                                    (uint16_t)1, 0, 0);
            } else
            {
                EDMA_UTILS_memcpy2D(context->outputBlkInfo,
                                   *(uint8_t (*)[])(void *)context->dmaArgs.remapParams.maps.outputBlkInfo + MAX_NUM_OUTPUT_BLOCKS,
                                    (uint16_t)MAX_NUM_OUTPUT_BLOCKS,
                                    (uint16_t)1, 0, 0);
            }
        }
        EDMA_UTILS_autoIncrement_waitOutChannel(context->autoIncrementDMAContext);
        context->sinkTriggered = 0;
    }

    return (DMANODE_EDMA_ERR_SUCCESS);
}



BAM_KernelInfo gBAM_TI_dmaCustomRemapMergeTileApproachNodeWriteKernel =
{
    0,                                     /*kernelId*/
    0,
    sizeof(BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args),
    BAM_EVE_ARP32,                         /*coreType*/
    BAM_NODE_SINK,                         /*nodeType*/
    REMAP_MERGE_SINK_NUM_INPUT_BLOCKS,     /*numInputDataBlocks */
    REMAP_MERGE_SINK_NUM_OUTPUT_BLOCKS,    /*numOutputDataBlocks */
    REMAP_MERGE_SINK_NUM_INTERNAL_BLOCKS   /*numRecInternal */
};


BAM_KernelInfo gBAM_TI_dmaCustomRemapMergeBBApproachNodeWriteKernel =
{
    0,                                     /*kernelId*/
    0,
    sizeof(BAM_DMA_CUSTOM_REMAP_MERGE_NODE_Args),
    BAM_EVE_ARP32,                         /*coreType*/
    BAM_NODE_SINK,                         /*nodeType*/
    REMAP_MERGE_SINK_NUM_INPUT_BLOCKS,     /*numInputDataBlocks */
    REMAP_MERGE_SINK_NUM_OUTPUT_BLOCKS,    /*numOutputDataBlocks */
    REMAP_MERGE_SINK_NUM_INTERNAL_BLOCKS   /*numRecInternal */
};


/* Sink Node kernel Info, helper, and exec functions */
BAM_KernelHelperFuncDef gBAM_TI_dmaCustomRemapMergeNodeWriteKernelHelperFunc =
{
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_getMemRecFunc, /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_setMemRecFunc  /* function to get kernels memory records BAM will call it when BAM_getNodeMemRec() is invoked by the applet */
};

/* Exec Func for Tile Approach */
BAM_KernelExecFuncDef gBAM_TI_dmaCustomRemapMergeTileApproachNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_frameInitChannel,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_trigger,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_wait,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr,
  NULL
};

/* Exec Func for Bounding Box (BB) Approach */
BAM_KernelExecFuncDef gBAM_TI_dmaCustomRemapMergeBBApproachNodeWriteKernelExecFunc =
{
  NULL,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_frameInitChannel,
  &EDMA_UTILS_autoIncrement_triggerOutChannel,
  &EDMA_UTILS_autoIncrement_waitOutChannel,
  &BAM_DMA_CUSTOM_REMAP_MERGE_SINK_updateDDRptr,
  NULL
};

