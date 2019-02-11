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




#ifndef BAM_COMMON_H
#define BAM_COMMON_H

#include "bam_types.h"
#include "bam_kernel_interface.h"

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/**
 * These version numbers are returned by BAM_getVersion()
 */
#define BAM_MAJOR_VERSION 2 /**< Major version number, for new set of features/roadmap point of view */
#define BAM_MINOR_VERSION 8 /**< Minor version number, for feature additions – interface changes are expected */
#define BAM_PATCH_VERSION 0 /**< Patch version number, for bug fixes, performance enhancements, interface changes are not expected*/
#define BAM_BUILD_VERSION 0 /**< Build version number, mainly for minor bug fixes during test cycle or changes like comment updates, minor doc fixes*/

#define MAX_NODES   128U                     /**< Maximum number of possible nodes in a graph */
#define BAM_END_NODE_MARKER 255U             /**< End of the nodes in a graph */
#define BAM_NULL_NODE              254U      /**< To connect unused output port from compute node */
#define BAM_MAX_NODE_INPUT_OUTPUT     10U    /**< Maximum number of possible input output nodes */

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/*Function-like macro definition */
/* Deviation allowed since it is a single statement best implemented through a macro function */
#define BAM_ALIGN_WORD(s) (((s) + (sizeof(void*)-1)) & (uint32_t)(~(sizeof(void*)-1)))  /**< BAM Word alignment */
/* RESET_MISRA("19.7")  -> Reset rule 19.7*/

/**
 * @brief Enumerate different on-chip buffers.
 *  In EVE case, VCOP_MEMHEAP is an internal type defined in vcopmem.h from the APR32 rts library but for host emulation and DSP case
 *  this type is defined below
 */
#if defined(HOST_EMULATION) || defined(CORE_DSP) 
typedef enum memheap
{
    VCOP_NONE   = -1,
    VCOP_IBUFLA = 0,
    VCOP_IBUFHA,
    VCOP_IBUFLB,
    VCOP_IBUFHB,
    VCOP_WMEM
} VCOP_MEMHEAP;
#endif

#ifndef CORE_DSP
#define BAM_IMGBUF_GAP 0x20000
#endif
#define BAM_MEM_DEFAULT_ALIGNMENT 32 /**< Default byte alignment for memory records. On EVE, it is 32 bytes as it is the alignment requirement for tables used in table lookup */
/**
 *  @brief      Generic byte pointer type.
 */
typedef uint8_t *BAM_BytePtr;

/**
 *  @brief      Specifies the type of Data Block connection to a kernel.
 */
typedef enum
{
    BAM_INPUT = 1, /**< Input data block */
    BAM_OUTPUT = 2 /**< Output data block */
} BAM_DataBlockDir;

/**
 *  @brief      Specifies the type of node in a graph.
 */
typedef enum
{
    /*! \brief Source node */
    BAM_NODE_SOURCE = 1,

    /*! \brief Sink node */
    BAM_NODE_SINK = 2,

    /*! \brief Unknown operation node:
     *  Used if the kernel can not be categorized using any of the other operation identifiers.  User will need to provide
     *  DMA and kernel configuration using initKernelsArgsFunc() or before calling BAM_construct() function.  This is same as
     *  legacy BAM_NODE_COMPUTE value from BAM v2.5.2 and older.
     **/
    BAM_NODE_COMPUTE_UNKNOWN_OP = 3,

    /*! \brief Compute node (DEPRECATED) */
    BAM_NODE_COMPUTE = BAM_NODE_COMPUTE_UNKNOWN_OP,

    /*! \brief Point-to-point operation node:
     *  In this type of computation,  one input block is combined with other input blocks, at pixel basis to produce an output
     *  block of the same dimensions. Examples:
     *  - Point-to-point add, sub, multiply, division
     *  - table lookup
     *  - color space conversion would actually fall in this category. Although it is implemented by a matrix multiplication,
     *    the color matrix is stored in internal memory at initialization time and is not read from external memory at every block.
     *  An input block of W x H pixels would produce an output block of W x H pixels.
     **/
    BAM_NODE_COMPUTE_POINT_TO_POINT_OP = 4,

    /*! \brief Neighborhood operation node:
     *  Input data is a NxM neighborhood centered around a given pixel. There is one output pixel produced per NxM neighborhood.
     *  To produce WxH pixels, the NxM neighborhood is translated as many as WxH times, like a sliding window. The input block
     *  must be of dimensions (W + M - 1) x (H + N - 1) so each of the (W x H) neighborhood position contain valid pixels. Examples:
     *  - FIR filter
     *  - Morphology operations
     *  - Neighborhood max/min such as NMS
     *  - Feature extractors based on neighborhood: Census transform, fast8, HOG.
     *  An input block of (W + M) x (H + N) pixels would produce an output block of W x H pixels, where M and N are the filter
     *  dimensions.
     **/
    BAM_NODE_COMPUTE_NEIGHBORHOOD_OP = 5,

    /*! \brief Feature matching operation node:
     *  Typically there is a reference and a target frame.  Each element in the target frame is matched against several elements
     *  contained in a search window of dimensions Sh x Sv belonging to the reference frame and centered around the same position
     *  as the target pixel.  Also the matching generally involves computing some cost within a cost aggregation window of
     *  dimensions M x N.
     *  For instance, in case of  disparity calculation used in stereovision, Sh would be the number of disparities, Sv would be
     *  1, M and N would be the dimensions of the cost aggregation window.
     **/
    BAM_NODE_COMPUTE_FEAT_MATCHING_OP = 6,

    /*! \brief Matrix-multiplication operation node (including vector to matrix, dot product):
     *  An input matrix of dimensions [I x J] multiplied by a matrix of dimensions [K x I] produces an output of dimensions [K x J].
     *  An input block will typically contain multiple input matrices arranged in tiles. Each of the input matrix is multiplied
     *  with the same second input matrix. That second matrix resides in internal memory and is read once at initialization time.
     **/
    BAM_NODE_COMPUTE_MATRIX_MULT_OP = 7,

    /*! \brief Block statistics operation node:
     *  Various statistics are calculated for each input block. The statistics from each input block are written out to the
     *  external memory. Examples:
     *  - Block variance
     *  - Block average
     *  - Block histogram
     **/
    BAM_NODE_COMPUTE_BLOCK_STATS_OP = 8,

    /*! \brief Frame statistics operation node:
     *  Various statistics are calculated for each input block. The statistics from each input block are also combined together
     *  to produce statistics data for an entire frame. In this scenario, the output DMA only needs to be triggered at the end
     *  of the frame.
     *  - Frame variance
     *  - Frame average
     *  - Frame histogram
     **/
    BAM_NODE_COMPUTE_FRAME_STATS_OP = 9,

    /*! \brief Map-to-list operation node:
     *  A list of (X,Y) coordinates is produced from a integer bitmap. Only the coordinates corresponding to non-zero pixels
     *  are written out and concatenated to a running list, which grows as more blocks are processed.
     **/
    BAM_NODE_COMPUTE_MAP_TO_LIST_OP = 10,

    /*! \brief Recursive operation node:
     *  A type of operation which re-uses one or more of its outputs as an input.  Integral image or IIR would fall in this
     *  category as it needs some carry-over results.
     **/
    BAM_NODE_COMPUTE_RECURSIVE_OP = 11,

    /*! \brief Maximum node type value:
     *  Used for parameter range checking.
     **/
    BAM_NODE_MAX = 12

} BAM_NodeType;


/**
 *  @brief      Specifies the Block Access Pattern of the kernel
 */
typedef enum
{
    /*! \brief The kernel can handle any arbitrary access pattern */
    BAM_BLOCK_ACCESS_PATTERN_ANY = 1,

    /*! \brief Horizontal raster-scan pattern */
    BAM_BLOCK_ACCESS_PATTERN_HORZ_RASTERSCAN = 2,

    /*! \brief Horizontal zigzag pattern */
    BAM_BLOCK_ACCESS_PATTERN_HORZ_ZIGZAG = 3,

    /*! \brief Vertical raster-scan pattern */
    BAM_BLOCK_ACCESS_PATTERN_VERT_RASTERSCAN = 4,

    /*! \brief Vertical zigzag pattern */
    BAM_BLOCK_ACCESS_PATTERN_VERT_ZIGZAG = 5,

    /*! \brief Statter-gather pattern */
    BAM_BLOCK_ACCESS_PATTERN_SCATTER_GATHER = 6,

    /*! \brief Maximum block access pattern value:
     *  Used for parameter range checking.
     */
    BAM_BLOCK_ACCESS_PATTERN_MAX = 7

} BAM_BlockAccessPattern;

#define BAM_GRAPH_INITIALIZED       1   /**< Status of the BAM graph showing initialized state*/
#define BAM_GRAPH_VERIFY_SUCCESS    2   /**< Status of the BAM graph verification showing success*/
#define BAM_GRAPH_VERIFY_FAILURE    3   /**< Status of the BAM graph verification showing failure*/

/**
 *  Status of the BAM graph Handle
 */
typedef uint32_t BAM_GraphDefStatus;

/**
 * Graph handle. Actual prototype is defined else where
 */
typedef void *BAM_GraphHandle;

/**
 *  @brief      Specifies the node parameters
 */
typedef struct
{
    uint8_t         nodeIndex;      /**< @brief Index of the node in the graph. Arbitrarily defined by the application. */
    BAM_KernelId    kernelId;       /**< @brief Unique ID of the kernel associated to the node, must correspond to an ID in the kernel database pointed by kernelDB from BAM_CreateGraphParams. */
    void            *kernelArgs;    /**< @brief Pointer to the kernel's arguments structure with initialized values */
} BAM_NodeParams;


/**
 *  @brief      Specifies the edge parameters
 *              which is a data connection between two nodes
 */
typedef struct
{
    struct {
        uint8_t id; /**< @brief Id of the upstream node */
        uint8_t port; /**< @brief Data port of the upstream node, this edge connects to */
    } upStreamNode; /**< @brief Upstream node id and port the edge connects to */
    /**
     *   @brief Downstream node id and port the edge connects to
     */
    struct {
        uint8_t id; /**< @brief Id of the downstream node */
        uint8_t port; /**< @brief Data port of the downstream node, this edge connects to */
    } downStreamNode; /**< @brief Downstream node id and port the edge connects to */
} BAM_EdgeParams;

/**
 *  @brief      Specifies the block dimension structure passed to BAM_createGraph()
 *   This structure contains block dimension variables that BAM_createGraph() will update during the search
 *   for their optimal values as well as step size used for the update process.
 *   These variables are blockWidth and blockHeight, that are updated using blockWidthStep and blockHeightStep.
 */
typedef struct {
    int32_t blockWidth;        /**< @brief Processing block width */
    int32_t blockHeight;       /**< @brief Processing block height */
    int32_t blockWidthStep;    /**< @brief Step size used to increment the processing block width during the optimization process */
    int32_t blockHeightStep;   /**< @brief Step size used to increment the processing block height during the optimization process */
    int32_t blockWidthDivisorOf; /**< @brief Integer the blockWidth must be divisor of, usually a processing ROI's width.  If 0, then ignored */
    int32_t blockHeightDivisorOf; /**< @brief Integer the blockHeight must be divisor of, usually a processing ROI's height. If 0, then ignored */
    int32_t blockWidthMax;     /**< @brief Integer the blockWidth must be less than or equal to this value, usually a processing ROI's width */
    int32_t blockHeightMax;    /**< @brief Integer the blockHeight must be less than or equal to this value, usually a processing ROI's height */
} BAM_BlockDimParams;


/**
 *  @brief      Internal Memory parameters that will be used by BAM for 
 * allocating input/output and working memories of Kernels
 */
typedef struct {
    void  * dataIoMem;             /**< @brief Input/Output data memory Base Pointer */
    void  * scratchOrConstMem;     /**< @brief Memory to store scratch or constant data Base Pointer */
    int32_t dataIoMemSize;         /**< @brief Size of Input/Output data memory in bytes and must be multiple of 4. Note that BAM splits this memory into a ping and a pong buffer of equal size, hence with respect to EDMA programming, the value dataIoMemSize/2 should be used to initialize the parameter pingPongOffset of EDMA_UTILS_autoIncrement_initParams_v2 .*/
    int32_t scratchOrConstMemSize; /**< @brief Size of scratch or constant buffer in bytes*/
} BAM_InternalMemParams;

/**
 *  @brief      Type definition for BAM_InitKernelsArgsFunc function pointer
 *   Such function is defined by the application and passed to BAM_createGraph() as callback
 */
typedef BAM_Status (*BAM_InitKernelsArgsFunc)(void *customArg, BAM_BlockDimParams *blockDimParams);

/**
 *  @brief      Specifies the structure passed to BAM_createGraph()
 */
typedef struct
{
    BAM_CoreType           coreType;   /**< @brief Type of the processing core on which the graph will execute. */
    BAM_KernelDBdef      *kernelDB;   /**< @brief Point to the database of processing kernels that the graph nodes will use. The database must have been previously initialized using BAM_initKernelDB(). */
    BAM_NodeParams       *nodeList;             /**< @brief Point to the list of parameters for the nodes that make up the graph */
    BAM_EdgeParams       *edgeList;             /**< @brief Point to the list of parameters for the edges that makes up the graph */
    void            *graphMem;                  /**< @brief Point to on chip memory in which BAM will store the graph object, for EVE, it is recommended to be in DMEM */
    uint32_t        graphMemSize;               /**< @brief Size in bytes of the block of memory pointed by graphMem */
    uint32_t        graphMemConsumed;           /**< @brief Upon returning from BAM_createGraph() the actual number of bytes consumed in graphMem is available here, if BAM_creategraph() returns BAM_E_BLOCK_DIM_TOO_BIG then check if it is because graphMemSizeConsumed > graphMemSize */
    void            *onChipScratchMem;          /**< @brief Point to on chip scratch memory in which BAM will store the graph object, for EVE, it is recommended to be DMEM */
    uint32_t        onChipScratchMemSize;       /**< @brief Size in bytes of the block of memory pointed by onChipScratchMem */
    uint32_t        onChipScratchMemConsumed;   /**< @brief Upon returning from BAM_createGraph() the actual number of bytes consumed in onChipScratchMem is available here, if BAM_creategraph() returns BAM_E_BLOCK_DIM_TOO_BIG then check if it is because onChipScratchMemConsumed > onChipScratchMemSize */
    void            *extMem;                    /**< @brief Point to external memory (DDR usually ) that will be used to store context saving restore data*/
    uint32_t        extMemSize;                 /**< @brief Size in bytes of the block of memory pointed by extMem */
    uint32_t        extMemConsumed;             /**< @brief Upon returning from BAM_createGraph() the actual number of bytes consumed in extMem is available here , if BAM_creategraph() returns BAM_E_OUT_OF_MEM then check if it is because extMemConsumed > extMemSize */
    uint32_t        useSmartMemAlloc;          /**< @brief 1: memory allocation is done dynamically and list of memory records is available in memRec after BAM_createGraph() returns. Location of the list will be in onChipScratchMem so application should save it before recycling onChipScratchMem for other purpose \n
                                                         0: memory allocation is done statically by using the list of memory records pointed by memRec. */
    BAM_MemRec      *memRec;                    /**< @brief Point to list of memory records. When useSmartMemAlloc=true, it is produced by BAM_createGraph(), when useSmartMemAlloc= false, caller must initialize it to a list of existing memory records */
    uint32_t        numMemRec;                  /**< @brief When useSmartMemAlloc== true, number of memory records returned by BAM_createGraph(). When useSmartMemAlloc=1, this member is not relevant */
    uint32_t        optimizeBlockDim;           /**< @brief If optimizeBlockDim== true, BAM_createGraph() will search for the optimium block dimensions and return them in blockDimParams, note that useSmartMemAlloc must be set to true otherwise BAM_E_UNSUPPORTED is returned */
    BAM_InitKernelsArgsFunc initKernelsArgsFunc; /**<@brief Pointer to user-defined callback function invoked by BAM_createGraph() to initialize all the kernel arguments present in nodeList
                                                            When optimizeBlockDim== false, it is called only one time. When optimizeBlockDim== true, it is called more than one time */
    void            *initKernelsArgsParams;     /**<@brief Point to the custom argument structure passed to the user defined callback function initKernelsArgsFunc()  */
    BAM_BlockDimParams blockDimParams;          /**<@brief Pointer to this sctructure is passed to the callback function initKernelsArgsFunc() and specifies the recommended processing block width and height.
                                                        Note that initKernelsArgsFunc() can modify these values by incremeting or decrementing by blockWidthStep or blockHeightStep in order to meet some constraints.
                                                        The final values picked up initKernelsArgsFunc() are returned into blockDimParams for the caller to use.
                                                        When optimizeBlockDim== true, BAM_createGraph() modifies the values in blockDimParams in search for the optimal ones.
                                                        */

#ifdef CORE_DSP
    BAM_InternalMemParams intMemParams;   /**< @brief internal Memory parameters that will be used by BAM for 
                                              * allocating input/output and working memories of Kernels. */                           
#endif
} BAM_CreateGraphParams;

/**
 *  @brief      Structure that will hold timing information of a particular stage after calling BAM_getTimingInfo()
 */
typedef struct {
    uint32_t numExecs; /**< Number of times this stage was executed, CURRENTLY DISABLED */
    uint32_t minCycles; /**< minimum of all the execution times collected so far, CURRENTLY DISABLED  */
    uint32_t maxCycles; /**< minimum of all the execution times collected so far, CURRENTLY DISABLED   */
    uint32_t averCycles; /**< average of all the execution times collected so far, CURRENTLY DISABLED   */
    uint32_t lastCycles; /**< execution time of the last execution */
} BAM_TimingInfo;

/**
 *  @brief  Structure used by BAM_getStats() to communicate benchmark stats to the caller
 */
typedef struct {
    BAM_TimingInfo createGraph; /**< Stats corresponding to BAM_createGraph() */
    BAM_TimingInfo kernelsInit; /**< Stats corresponding to the execution of all kernelCtl(), kernelInitInstance(), kernelInitFrame() functions in the graph */
    BAM_TimingInfo kernelsExec; /**< Stats corresponding to the execution of all kernelCompute() and kernelWait() functions in the graph */
} BAM_Statistics;

#define BAM_INVALID_INDEX   ((uint8_t)0xFF) /**< BAM Invalid Node Index */

/**
 *  @brief      Return benchmark statistics into the structure pointed by stat.
 *  @param[in]  graphHandle      Pointer to the graph handle
 *  @param[in]  stat  Points to the structure of type BAM_Statistics
 *  @retval     BAM_S_SUCCESS   All timing information could be collected.
 *  @retval     BAM_E_UNSUPPORTED The library was built with BAM_LOGPERF undefined so no timing information could be collected.
 */
BAM_Status BAM_getStats(BAM_GraphHandle graphHandle, BAM_Statistics *stat);

/**
 *  @brief      Return BAM library version made of a major, minor and patch numbers
 *  @param[out]  major  Pointer to the placehodler of the major version number
 *  @param[out]  minor  Pointer to the placehodler of the major version number
 *  @param[out]  patch  Pointer to the placehodler of the patch version number
 *  @retval     BAM_S_SUCCESS
 */
BAM_Status BAM_getVersion(uint16_t *major, uint16_t *minor, uint16_t *patch);

/**
 *  @brief      Print to the console all details (node name, type, attribute, base pointer) about each memory record in the table pointed by memRec
 *              This is useful for inspecting the memory allocation produced by the smart memory allocator and decide to do any manual fine-tuning
 *              by manually assigning some kernel's memory records to specific memory space, in the kernel's getMemRec function.
 *  @param[in]  memRec  Pointer to the array of memory records to be printed
 *  @param[in]  numMemRec  Number of memory records in the array
 *  @retval     BAM_S_SUCCESS
 */
BAM_Status BAM_printMemRec(BAM_MemRec memRec[], uint32_t numMemRec);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BAM_COMMON_H */
