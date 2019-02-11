/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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




#ifndef BAM_CONSTRUCT_INT_H
#define BAM_CONSTRUCT_INT_H

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")
#include "bam_construct.h"
#include "bam_mempkt.h"

#ifdef _MSC_VER /* If using MS Visual Studio C Compiler */
    #if !defined(__cplusplus)
        #if (_MSC_VER < 1800) /* Before MS Visual Studio 2013 (v12), C99 was not supported */
            typedef unsigned int _Bool;
            #define bool _Bool
            #define true 1
            #define false 0
        #else
            #include <stdbool.h>
        #endif
    #endif
#endif

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation is allowed because none of the type names listed in this file startingwith _ conflicts with any language entity*/

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

#define MAX_MEMRECORDS_PER_NODE 10

#define BAM_MAX_NODE_INTERNAL   8

#define BAM_MAX_NODE_OUTPUTS    8

#define BAM_MAX_NODES           ((uint8_t)48)

#define BAM_MAX_NUM_READER_NODES    ((uint8_t)255)

#define BAM_INVALID_NODE        (BAM_MAX_NODES)

#define BAM_DATA_BLOCKS         ((uint8_t)255)

typedef struct
{
    uint8_t         nodeIndex;      /**< Index of the node in the graph */
    BAM_KernelId    kernelId;       /**< Id of the kernel attached to the node */
    BAM_CoreType    coreType;       /**< Type of the core */
    void            *kernelArgs;    /**< Pointer to the kernel arguments structure */
    BAM_KernelInfo  *kernelInfo;    /**< pointer to the BAM kernel info */
} BAM_NodeParamsInt;

/**
 *  @brief      Specifies properties of a kernel graph. This structure is
 *              passed while creating a graph definition.
 */
typedef struct
{
    /**
     *  @brief  Number of source nodes in the graph.
     */
    uint32_t numSourceNodes;

    /**
     *  @brief  Number of sink nodes in the graph.
     */
    uint32_t numSinkNodes;

    /**
     *  @brief  Number of compute nodes in the graph.
     */
    uint32_t numComputeNodes;

    /**
     *  @brief  Number of data blocks in the graph.
     */
    uint32_t numDataBlocks;

} BAM_GraphDefParams;

/**
 *  @brief      BAM graph defenition. Contains whole information regarding a graph inside an algorithm.
 *
 *  @remarks    Size of this structure is not fixed but depends on the graph and its internal nodes.
 */
typedef struct _bam_graphdef
{
    uint32_t size;                  /**< Size of this structure*/
    void *thisPtr;      /**< Pointer to this present structure, used to recalculate all the member kernelContext of all the nodes in case the graph changes location */
    /* Graph specific entries */
    BAM_GraphDefStatus status;      /**< Status showing state of the graph. initialized or non-initialized */
    BAM_GraphDefParams params;      /**< Specifies properties of a kernel graph */
    uint16_t totalNodes;            /**< Total number of nodes in the graph. It includes Source, Sink nodes and compute nodes */
    uint32_t numMemTabs;            /**< Numbers of memory records tab pointed by the following member memRec */
    BAM_MemRec *memRec;             /**< Point to the list of memory records used to allocate memories inside VCOP, DMEM or in ext mem during graph creation time, only used at graph creation */
    BAM_Packet *packetPool;         /**< Point to the pool of memory packets used by the smart memory allocator in lieu of vcop_malloc() */
    uint32_t nodeDefArrOffset;      /**< Offset in bytes to the start of node definition array from the address of contextMem member of this structure */
    uint32_t dataBlockDefArrOffset; /**< Offset in bytes to the start of data block definition array from the address of contextMem member of this structure */

    uint32_t curFreeNode;           /**< Index of the current free node in the node definition array */
    uint32_t curFreeDataBlock;      /**< Index of the current free datablock in the datablock definition array */
    uint32_t curFreeKernelContextOffset; /**< Index of the current free kernel context in the kernel context definition array */

    /* Instance specific entries */
    uint32_t initInstanceDone;      /**< Status indicating whether initInstance() of each node inside the graph is done or not*/

    const BAM_KernelDBdef *kernelDBDef; /**< Pointer to BAM kernel defenition database */

    uint32_t        graphMemSize;       /**< Size occupied by the entire graph including node array, data block array, etc */
    void            *extMem; /**< Point to external memory (DDR) that will be used to store context saving restore data*/
    uint32_t        extMemSize;  /**< Upon returning from BAM_createGraph() the actual number of bytes consumed in extMem is available here  */


    /* Place holder to the context Mem. Actual size required may be different */
    uint8_t contextMem[4];              /**< Dummy variable after which variable sized fields such as node array, data block array, kernel context array etc are located */
} BAM_GraphDef;

/**
 *  @brief      BAM node definition. Contains information regarding a node inside a graph.
 *
 */
typedef struct _bam_nodedef
{
    BAM_KernelInfo kernelInfo;                              /**< Kernel information structure of the kernel which is assigned to the node */
    uint8_t nodeType;                                       /**< Type of the node SOURCE, SINK or COMPUTE */
    uint8_t numInputs;                                      /**< Number of input blocks taken by the node */
    uint8_t numOutputs;                                     /**< Number of output blocks given by the node */
    uint8_t inDataBlockIndex[BAM_MAX_NODE_INPUT_OUTPUT];    /**< Array containig the index of node's input data blocks in the BAM_GraphDef datablock array*/
    uint8_t outDataBlockIndex[BAM_MAX_NODE_INPUT_OUTPUT];   /**< Array containig the index of node's output data blocks in the BAM_GraphDef datablock array*/
    BAM_MemRec internalBlock[BAM_MAX_NODE_INTERNAL];        /**< Array of BAM_MemRec containing node's entire internal memory requirements */
    void *kernelContext; /* point to kernel context */      /**< Pointer to context of the kernel which is attached to the node. Kernel contexs are stored in kernel context array in BAM_GraphDef */
} BAM_NodeDef;

/**
 *  @brief      BAM datablock definition. Contains information regarding a datablock needed by nodes inside a graph.
 *
 */
typedef struct _bam_datablockdef
{
    BAM_MemRec mem;                                     /**< This keeps a copy of a particular memRec in the graphMemRec array to which the datablock is linked */
    /* BAM_Constraints             dimensionConstraints[MAX_SPATIAL_DIM+1]; */
    /* BAM_Constraints             strideConstraints[MAX_SPATIAL_DIM+1]; */
    uint8_t writerNodeIndex;                            /**< Index of the unique writer of the datablock in the BAM_GraphDef node definition array */
    uint8_t numReaderNodes;                             /**< Number of reader nodes from the data block */
    uint8_t readerNodeIndex[BAM_MAX_NUM_READER_NODES ]; /**< Array containing node indices of those nodes which read the datablock. A data block can have several reader */
    uint8_t tempNumReaderNodes;                             /**< Used by the automatic block allocator to keep track how many readers are still attached to the block as the algorithm descends the graph tree  */
} BAM_DataBlockDef;

BAM_Status BAM_fillKernelInfo(BAM_CoreType coreType, const BAM_KernelDBdef *kernelDBDef, BAM_NodeParamsInt nodeList[]);

BAM_Status BAM_copyNodeList(BAM_CreateGraphParams *createParams, BAM_NodeParamsInt copyOfNodeList[]);

/**
 *  @brief      Get the size of memory required to store a kernel graph
 *              definition. The size depends on the number of nodes and
 *              data blocks present in the graph.
 *
 *  @param[in]  nodeList          Specifies properties of the nodes
 *  @param[in]  edgeList          Specifies properties of the edges
 *  @param[out] graphMemSize    Size of memory required to store the graph definition.
 *  @param[out] numMemtabs      Number of memory records required to hold the memory requirement of each kernel
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
BAM_Status BAM_getGraphMemSize(const BAM_NodeParamsInt nodeList[], const BAM_EdgeParams edgeList[], uint32_t *graphMemSize, uint32_t *numMemtabs);

/**
     *  @brief      Initialize the memory (handle) that stores the graph
     *              definition.
     *
     *  @param[in]  nodeList          Specifies properties of the nodes
     *  @param[in]  edgeList          Specifies properties of the edges
     *  @param[in]  graphHandle        Pointer to the memory where graph is stored.
     *  @param[out] graphMemSize    Size of allocated memory. It should be same as
     *                              returned from BAM_getGraphMemSize function.
     *
     *  @retval     BAM_S_SUCCESS   Success
     */
BAM_Status BAM_initGraph(const BAM_NodeParamsInt nodeList[], const BAM_EdgeParams edgeList[], BAM_GraphHandle graphHandle, uint32_t graphMemSize);

BAM_Status BAM_updateNodes(BAM_GraphHandle graphHandle, BAM_CreateGraphParams *createParams, uint32_t callSetMemRec);

/**
 *  @brief      De-initializes the memory (handle) that stores the graph
 *              definition.
 *
 *  @param[in]  graphHandle             Pointer to the memory where graph is stored.
 *  @param[out] graphHandleMemRec    Array of memRecs. List of graph memRecs to be freed from outside.
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
BAM_Status  BAM_deInitGraph(BAM_GraphHandle graphHandle, BAM_MemRec graphHandleMemRec[]);

/* The remaining prototypes are depreciated functions, not intended to be used by the application directly */

/**
 *  @brief      Automatically allocates the memory records passed in memTab.
 *
 *  @param[in] graphHandle      Handle to the graph definition.
 *  @param[in] createParams    Pointer to the same graph params create structure that was passed to BAM_createGraph2()
 *  @param[out] memTab           Array of memtabs which contains information about memory allocated for
 *                              each node in the order of nodes. Output memory requirements of a node
 *                              are placed after internal memory requirements, excluding all
 *                              input memory requirements.
 *                              The member 'base' of each memory record will be updated by the
 *                              function with the pointer to the allocated memory.
 *
 *  @retval     BAM_S_SUCCESS or BAM_E_BLOCK_DIM_TOO_BIG or BAM_BAM_E_OUT_OF_MEM   Success or fail to allocate all memory records
 */
static BAM_Status BAM_autoAllocMemRec(BAM_GraphHandle graphHandle, BAM_CreateGraphParams *createParams, BAM_MemRec memTab[]);
/**
 * Finish the graph construction process
 * @param graphDef
 * @param kernelArgs
 */
static BAM_Status BAM_finaliseGraph(const BAM_GraphDef *graphDef, const BAM_NodeParams nodeList[], const BAM_InternalMemParams * intMemParams);

/**
 *  @brief      Add a node to the graph. Nodes can be one of the types source, sink or compute.
 *
 *  @param[in]  graphHandle        Handle to the graph definition. The handle is
 *                              actually pointer to the memory location where
 *                              graph is stored.
 *  @param[in]  kernelInfo      Pointer to the kernel configuration strcuture.
 *  @param[out] nodeId          Pointer to the location where ID of the
 *                              created node is returned.
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
static BAM_Status BAM_newNode(BAM_GraphHandle graphHandle, const BAM_KernelInfo *kernelInfo, uint8_t *nodeId);

/**
 *  @brief      Add a node to the graph. Nodes can be one of the types source, sink or compute.
 *
 *  @param[in]  graphHandle        Handle to the graph definition.
 *  @param[out] dataBlockId     Pointer to the location where ID of the
 *                              created data block is returned.
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
static BAM_Status BAM_newDataBlock(BAM_GraphHandle graphHandle, uint8_t *dataBlockId);

/**
 *  @brief      Make a connection between a data block and a node.
 *
 *  @param[in]  graphHandle        Handle to the graph definition.
 *  @param[in]  direction       Type of connection to the node. Can be one of
 *                              BAM_INPUT and BAM_OUTPUT.
 *  @param[in]  dataBlockId     Id of the data block returned from
 *                              BAM_newDataBlock call.
 *  @param[in]  nodeId          Id of the node returned from
 *                              BAM_newNode call.
 *  @param[in]  inputOutputBlockIndex   Index of the connection to the node.
 *                              The index starts with 0.
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
static BAM_Status BAM_attachDataBlockToNode(BAM_GraphHandle graphHandle, BAM_DataBlockDir direction, uint8_t dataBlockId,
        uint8_t nodeId, uint8_t inputOutputBlockIndex);

/**
 *  @brief      Gets the entire memory requirements of the graph. It is meant to be used from algAllocMem()
 *              so that algorithm can request memories for the graph accordingly.
 *
 *  @param[in]  graphHandle     Handle to the graph definition.
 *  @param[in]  createParams    Pointer to the create structure which has a a list of node's properties that need to have their member kernelInfo looked up
 *  @param[out] memTab          Array of memtabs which contains memory requirements of
 *                              each node in the order of nodes. Output memory requirements of a node
 *                              are placed after internal memory requirements, excluding all
 *                              input memory requirements.
 *
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
static BAM_Status BAM_getMemRec(BAM_GraphHandle graphHandle,const BAM_CreateGraphParams *createParams, BAM_MemRec memTab[]);

/**
 *  @brief      Sets the entire memory requirements of the graph. It is meant to be used from algInit()
 *              so that algorithm can use allocated memory for the graph accordingly.
 *
 *  @param[in] graphHandle      Handle to the graph definition.
 *  @param[in] memTab           Array of memtabs which contains information about memory allocated for
 *                              each node in the order of nodes. Output memory requirements of a node
 *                              are placed after internal memory requirements, excluding all
 *                              input memory requirements.
 *  @param[in]  nodeList           list of node's properties that need to have their member kernelInfo looked up
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
static BAM_Status BAM_setMemRec(BAM_GraphHandle graphHandle, const BAM_MemRec memTab[], const BAM_NodeParams nodeList[], const BAM_InternalMemParams * intMemParams);

static BAM_Status BAM_getNodeMemRec(const BAM_GraphDef *graphDef, uint8_t nodeIndex, const void *kernelArgs, BAM_MemRec *memRecInternal,
        BAM_MemRec *memRecOutputDataBlock, uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

static BAM_Status BAM_setNodeMemRec(const BAM_GraphDef *graphDef, uint8_t nodeIndex, const BAM_MemRec memRecInternal[],
        const BAM_MemRec memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecOutputDataBlock);

/**
 *  @brief      Optimize the graph
 *
 *  @param[in]  graphHandle                    graph's handle previously returned by BAM_createGraph()
 *  @param[in]  createGraphParams          Point to the structure BAM_CreateGraphParams that specifies the graph parameters to be created
 *..@param[in] optParams                        Point to the structure BAM_OptimizeGraphParams which contains parameters that BAM_optimizegraph() will vary, e,g, block width and block height.
 *..@param[in] initKernelsArgsFunc           Point to the application defined callback function which will be called by BAM_optimizeGraph() during the search for the optimal block width and block height
 *..@param[in] customArgs                      Point to the custom argument structure that BAM_optimizeGraph() will have to pass to initKernelsArgsFunc().
 *  @retval     BAM_S_SUCCESS          Success
 *  @retval     BAM_E_INVALID_MEM_SIZE Allocated space in on-chip or external memories too small. Increase createGraphParams->onChipScratchMemSize or createGraphParams->extMemSize.
 *  @retval     BAM_E_BLOCK_DIM_TOO_BIG Could not allocate memory for all internal and output memory records. The initial optParams->blockWidth and optParams->blockHeight values cause the memory size to exceed the amount of on-chip memory.\n
 *                                      They need to be reduced in order to correct the condition.
 *
 * This function optimize the graph by maximizing the processing block width and block height while keeping all the memory record allocations succesful.
 *
 * 1) The search for the best block width is done by iteratively incrementing optParams->blockWidth until the memory allocation returned by BAM_updateNodes()
 * fails. The increment step is optParams->blockWidthStep, usually equal to 16 in order to align with the processor's number of SIMD ways.
 * In each iteration the function initKernelsArgsFunc() is called to reinitialize the kernel arguments that depend on the optParams->blockWidth value.
 * The function initKernelsArgsFunc() is implemented by the application and is invoked as a callback.
 * In normal behaviour, at least one iteration will succesfully allocate memory. The algorithm will iterate until BAM_updateNodes() returns BAM_E_BLOCK_DIM_TOO_BIG.
 * So once BAM_updateNodes() returns BAM_E_BLOCK_DIM_TOO_BIG, we know the last successful iteration corresponds to the case of optimum value for optParams->blockWidth
 * So we rewind the current value of optParams->blockWidth, by subtracting optParams->blockWidthStep in order to recover the optimum optParams->blockWidth.
 *
 * 2) After finding the optimum optParams->blockWidth, we repeat the same procedure to find the optimum block height by varying optParams->blockHeight
 *
 * 3) Once the algorithm finds both optimal blockwidth and blockHeight, it calls initKernelsArgsFunc() and BAM_updateNodes() for the last time to generate a graph configured with
 * these optimal values.
 *
 */
BAM_Status BAM_optimizeGraph(BAM_GraphHandle graphHandle, BAM_CreateGraphParams *createGraphParams);

uint32_t BAM_getGraphCreateCycles(void);

uint32_t BAM_getKernelsInitCycles(void);

uint32_t BAM_getKernelsExecCycles(void);

/**
 *  @brief      Used by BAM_createGraph() to copy a graph's internal memory records that are persistent into
 *              external memory. The copy is done by memcpy, not QDMA since we cannot assume that, at graph creation time QDMA are available.
 *
 *  @param[in] graphHandle      Handle to the graph definition.
 *
 *  @retval     BAM_S_SUCCESS   Success
 */
int32_t BAM_copyIntMemRec2ExtMem(BAM_GraphHandle graphHandle);

/* RESET_MISRA("20.2")  -> Reset rule 20.2*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BAM_INT_H */
