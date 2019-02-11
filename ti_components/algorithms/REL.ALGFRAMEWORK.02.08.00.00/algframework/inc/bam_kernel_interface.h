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


/**
 *  @file       bam_kernel_interface.h
 *
 *  @brief      This header defines interfaces for inserting kernels into BAM
 */

#ifndef BAM_KERNEL_INTERFACE_H
#define BAM_KERNEL_INTERFACE_H

#include "bam_types.h"

#define BAM_MAX_NODE_INPUT_OUTPUT 10U

#define BAM_METAINFO_NEIGHBORHOOD_OP(M, N)               (((uint32_t)M) << 16 | ((uint32_t)N))
#define BAM_METAINFO_FEAT_MATCHING_OP(Sh, Sv, M, N)      0
#define BAM_METAINFO_MATRIX_MULT_OP(M, N)                (((uint32_t)M) << 16 | ((uint32_t)N))
#define BAM_METAINFO_BLOCK_STATS_OP(statSize)            ((uint32_t)statSize)
#define BAM_METAINFO_FRAME_STATS_OP(statSize)            ((uint32_t)statSize)
#define BAM_METAINFO_RECURSIVE_OP(orderNum)               ((uint32_t)orderNum)

#define BAM_CONSTRAINT_COMPUTE_OUTPUT_SIZE_MULT(W, H)    (((uint32_t)W) << 16 | ((uint32_t)H))
#define BAM_CONSTRAINT_REQUIRES_ONLY_VALID_DATA(V)       (((uint32_t)V) << 31)

#define BAM_OPTIMIZATION_EQUAL_INOUT_WIDTHS_STRIDES(V)   ((uint32_t)V)


/**
 *  @brief      This structure extends the BAM_KernelInfo structure while providing backward compatability.
 */
typedef struct
{

    /**
     *  @brief  Meta-information to further characterize the computation type
     *           Use one of the following macro function to encode several attributes into the field metaInfo:
     *  BAM_METAINFO_NEIGHBORHOOD_OP(M, N) where M and N are the filter's horizontal and vertical dimensions respectively
     *  BAM_METAINFO_FEAT_MATCHING_OP(Sh, Sv, M, N) where Sh and Sv are the horizontal and vertical dimensions of the search range,
     *                                              M & N are the cost aggregation window's dimensions
     *  BAM_METAINFO_MATRIX_MULT_OP(M, N) where M, N are the dimensions of the matrix
     *  BAM_METAINFO_BLOCK_STATS_OP(statSize) where statSize is the length in bytes of of the set of statistical variables generated.
     *  BAM_METAINFO_FRAME_STATS_OP(statSize) where statSize is the length in bytes of of the set of statistical variables generated.
     *  BAM_METAINFO_RECURSIVE_OP(oderNum) where orderNum is the order of the filter
     *
     *  If any meta-info value is not known at compile time but is derived at runtime then assign the value -1.
     */
    uint32_t metaInfo;

    /**
     *  @brief  Constraint-information to identify constraints of the kernel API
     *           OR the results of the following macro functions together to encode several attributes into the field constraintInfo:
     *  BAM_CONSTRAINT_COMPUTE_OUTPUT_SIZE_MULT(W, H) where W and H are the output block width and height multiple constraints, respectivly.
     *  BAM_CONSTRAINT_REQUIRES_ONLY_VALID_DATA(V), V:1 means that the input block must not contain invalid data.
     */
    uint32_t constraintInfo;

    /**
     *  @brief  Optimization-information to identify performance or code size optimization potential of the kernel API
     *           OR the results of the following macro functions together to encode several attributes into the field optimizationInfo:
     *  BAM_OPTIMIZATION_EQUAL_INOUT_WIDTHS_STRIDES(V) V:1 means that the performance is better if the input and output widths are equal, and
     *           the widths take up the full strides (C6X DSP: all lines in block computed in single loop).
     *
     */
    uint32_t optimizationInfo;

    /**
     *  @brief  Data-block access pattern specifies the order blocks of data are read/written from/to external memory:
     *  BAM_BLOCK_ACCESS_PATTERN_ANY,
     *  BAM_BLOCK_ACCESS_PATTERN_HORZ_RASTERSCAN,
     *  BAM_BLOCK_ACCESS_PATTERN_HORZ_ZIGZAG,
     *  BAM_BLOCK_ACCESS_PATTERN_VERT_RASTERSCAN,
     *  BAM_BLOCK_ACCESS_PATTERN_VERT_ZIGZAG,
     *  BAM_BLOCK_ACCESS_PATTERN_SCATTER_GATHER,
     * 
     *  The symbol BAM_ACCESS_PATTERN_ANY is used when the kernel can handle any arbitrary access pattern.
     *
     *  @sa     BAM_BlockAccessPattern
     */
    uint8_t sourceBlockAccessPattern;
    uint8_t sinkBlockAccessPattern;

    /**
     *  @brief  Sampling factors for each input and output block. These arrays can contain up to BAM_MAX_NODE_INPUT_OUTPUT
     *           values. BAM_MAX_NODE_INPUT_OUTPUT is the maximum number of input or output blocks that can be attached to a node.
     *           The sampling factors for the input blocks are listed first, immediately followed by the sampling factors for the
     *           output blocks.
     */
    float horzSamplingFactor[BAM_MAX_NODE_INPUT_OUTPUT];
    float vertSamplingFactor[BAM_MAX_NODE_INPUT_OUTPUT];

    /**
     *  @brief  Type of the elements composing each input and output block. The type VXLIB_dataType_e should be used to
     *           initialize these members.
     */
    uint8_t typeInputElmt[BAM_MAX_NODE_INPUT_OUTPUT];
    uint8_t typeOutputElmt[BAM_MAX_NODE_INPUT_OUTPUT];

} BAM_KernelExtraInfo;


/**
 *  @brief      This structure provides to BAM contextual information about a kernel
 */
typedef struct
{

    /**
     *  @brief  System-wide unique identifier of a kernel.
     *  Initially set to 0 when the structure is defined in bam_<kernel_name>_helper_func.c
     *  Later it gets automatically initialized by BAM_initKernelDB() with the ID defined
     *  in the kernel database passed to the function BAM_initKernelDB().
     */
    BAM_KernelId kernelId;

    /**
     *  @brief  Size of the kernel's context structure BAM_<kernel_name>_Context, which is a private structure specific
     *  to the kernel that contains members such as pointers to the input, internal scratch, output data blocks
     *  as well as arguments for the compute kernel. This structure content must follow a specific pattern, described in the BAM user's guide.
     *  By convention, the structure is declared in file bam_<kernel_name>_helper_func.h and defined in file bam_<kernel_name>_helper_func.c
     *  The operator sizeof() should be used to initialize this member kernelContextSize for ease of code maintenance. Ex: sizeof(BAM_<kernel_name>_Context).
     */
    uint32_t kernelContextSize;

    /**
     *  @brief  Size of the kernels' arguments structure BAM_<kernel_name>_Args that is exposed to the application. Such structure becomes the list of parameters
     *  that will be passed to the kernel's compute function. Since it is exposed to the application, it must be declared in the kernel public
     *  header file which is bam_<kernel_name>.h . The way the application will communicate the argument's values is by providing pointers to
     *  initialized BAM_<kernel_name>_Args structures through the nodes' list passed to BAM_createGraph().
     *  The operator sizeof() should be used to initialize this member kernelArgSize for ease of code maintenance. Ex: sizeof(BAM_<kernel_name>_Args).
     */
    uint32_t kernelArgSize;

    /**
     * @brief Type of the processing core on which the kernel is implemented on: BAM_EVE_ARP32, BAM_EVE_VCOP, BAM_EVE_DSP_C64x, etc
     */
    BAM_CoreType    coreType;

    /**
     *  @brief  Type of node the kernel must be associated to:
     *          BAM_NODE_SOURCE,
     *          BAM_NODE_SINK,
     *          BAM_NODE_COMPUTE (DEPRECATED),
     *          BAM_NODE_COMPUTE_UNKNOWN_OP,
     *          BAM_NODE_COMPUTE_POINT_TO_POINT_OP,
     *          BAM_NODE_COMPUTE_NEIGHBORHOOD_OP,
     *          BAM_NODE_COMPUTE_FEAT_MATCHING_OP,
     *          BAM_NODE_COMPUTE_MATRIX_MULT_OP,
     *          BAM_NODE_COMPUTE_BLOCK_STATS_OP,
     *          BAM_NODE_COMPUTE_FRAME_STATS_OP,
     *          BAM_NODE_COMPUTE_MAP_TO_LIST_OP,
     *          BAM_NODE_COMPUTE_RECURSIVE_OP,
     *    Note that BAM_NODE_COMPUTE should not be used anymore for new kernels that have extra information. If the kernel cannot be categorized,
     *    use BAM_NODE_COMPUTE_UNKNOWN.
     *
     *  @sa     BAM_NodeType
     */
    uint8_t nodeType;

    /**
     *  @brief  Number of input data blocks to the kernel.
     */
    uint8_t numInputDataBlocks;

    /**
     *  @brief  Number of output data blocks to the kernel.
     */
    uint8_t numOutputDataBlocks;

    /**
     *  @brief  Number of on-chip memory records required by the kernel during
     *          kernel execution. These memory segments are internal to the
     *          kernel and are used as scratch buffers or to store constant.
     */
    uint8_t numRecInternal;

#ifdef CORE_DSP
    /**
     *  @brief  Additional information which is necessary for a complete
     *          automation of the graph creation process.
     */
    BAM_KernelExtraInfo kernelExtraInfo;
#endif

} BAM_KernelInfo;


/** @brief      Command number for the cmdId field of BAM_KernelCommonControlArgs which
 *               sends the BAM_KernelCommonControlFrameArgs data structure as the payload */
#define BAM_CTRL_CMD_ID_SET_FRAME_ARGS   0xFFFFFFFFU

/**
 *  @brief      Command structure passed to the BAM_KernelCtlFunc function of each kernel.
 *               The cmdId is a unique number used to determine what the payload is based on each kernel.
 */
typedef struct
{
    uint32_t cmdId;   /**< @brief Command of the control message */
    void * payload;

} BAM_KernelCommonControlArgs;

/**
 *  @brief      Common structure that can be used to send information about the frame processing to the kernel.
 *               This information can be used by the kernel to derive number of blocks to be processed
 *               in each direction in case the kernel needs to keep track.  This structure is passed as a
 *               pointer to the payload parameter of the BAM_KernelCommonControlArgs structure when cmdId is
 *               BAM_CTRL_CMD_ID_SET_FRAME_ARGS.
 */
typedef struct
{
    uint16_t frameWidth;   /**< @brief Width dimention of the frame */
    uint16_t frameHeight;  /**< @brief Height dimention of the frame */
    uint16_t blockWidth;   /**< @brief Width dimention of the block */
    uint16_t blockHeight;  /**< @brief Height dimention of the block */
} BAM_KernelCommonControlFrameArgs;

/**
 *  @brief      Type definition for BAM kernel GetMemRec function pointer
 */
typedef BAM_Status (*BAM_KernelGetMemRecFunc)(const void *kernelArgs, BAM_MemRec *memRecInternal,
        BAM_MemRec *memRecOutputDataBlock, uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock);

/**
 *  @brief      Type definition for BAM kernel SetMemRec function pointer
 */
typedef BAM_Status (*BAM_KernelSetMemRecFunc)(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs);

/**
 *  @brief      Type definition for BAM kernel GetExtraInfo function pointer
 */
typedef BAM_Status (*BAM_KernelGetExtraInfoFunc)(const void *kernelArgs, BAM_KernelExtraInfo *extraInfo);


/**
 *  @brief      Helper functions are defined on the core on which the constructor
 *              is executed: Arp32, M3, M4, A15.
 */

typedef struct
{
    /**
     *  @brief  Function to get kernels memory records. BAM will call it when
     *          BAM_createGraph() or BAM_optimizeGraph() is invoked by the applet.
     */
    BAM_KernelGetMemRecFunc getKernelMemRec;

    /**
     *  @brief  Function to set kernels memory records. BAM will call it when
     *          BAM_createGraph() or BAM_optimizeGraph() is invoked by the applet.
     */
    BAM_KernelSetMemRecFunc setKernelMemRec;

#ifdef CORE_DSP
    /**
     *  @brief  Function to get kernels extra information . BAM will call it when
     *          BAM_createGraph() or BAM_optimizeGraph() is invoked by the applet.
     *          Note that this is only needed if some of the parameters in the extraInfo
     *          structure are not constant for the kernel, but may change based on
     *          configuration.
     */
    BAM_KernelGetExtraInfoFunc getKernelExtraInfo;
#endif

#if 0
    /**
     *  @brief  Function used to initialize members pertaining to the
     *          constraints of the different datablocks structures that
     *          constitute either the input or output of the compute function.
     *          BAM will call it when BAM_initNodeProcArgs() is invoked by
     *          the applet.
     */
    BAM_KernelInitConstraintsFunc   initDataBlocksConstraints;
    /**
     *  @brief  Function used to check whether the argument values are valid.
     *          BAM will call it when BAM_initNodeProcArgs() is invoked by the
     *          applet.
     */
    BAM_KernelCheckArgsFunc         checkArgs;
#endif
} BAM_KernelHelperFuncDef;

/**
 *  @brief      Helper function database entry
 *
 */
typedef struct
{
    BAM_KernelInfo *kernelInfo;                 /**< @brief Pointer to the kernel's contextual information structure BAM_KernelInfo */
    BAM_KernelHelperFuncDef *kernelHelperFunc;  /**< @brief Pointer to the structure BAM_KernelHelperFuncDef that list the helper functions */
    char *name;                                 /**< @brief Unique name of the kernel */
    BAM_KernelId kernelId;                      /**< @brief Unique ID of the kernel */
} BAM_KernelHostDBdef;

/**
 *  @brief      Type definition for BAM kernel execute function pointer
 *
 */
typedef BAM_Status (*BAM_KernelFunc)(void *kernelContext);

/**
 *  @brief      Type definition for BAM kernel control function pointer
 *
 */
typedef BAM_Status (*BAM_KernelCtlFunc)(void *kernelContext, void *ctlArg);

/**
 *  @brief      Type definition for BAM kernel custom function pointer
 *
 */
typedef void (*BAM_KernelCustom)(uint16_t pBlock[]);


/**
 *  @brief      Specifies Various execute functions of the kernel
 *
 */
typedef struct
{
    /* These 5 functions are only defined on ARP32 (for EVE)
     */
    BAM_KernelFunc kernelInitInstance;  /**< One time initialization function of the kernel. Called the first time the graph is execture or after a context restore */
    BAM_KernelFunc kernelInitFrame;     /**< Initialization function of the kernel which should be called before every frame processing */
    BAM_KernelFunc kernelCompute;       /**< Kernel function which performs the computation on every block of data */
    BAM_KernelFunc kernelWait;          /**< Kernel Function which waits for the completion of computations performed */
    BAM_KernelCtlFunc kernelCtl;        /**< Control function of the kernel*/
    BAM_KernelCustom kernelCustom;      /**< Custom function of the kernel*/
} BAM_KernelExecFuncDef;

/**
 *  @brief      Execute function database entry
 *
 */
typedef struct
{
    BAM_KernelInfo *kernelInfo;             /**< @brief Pointer to the kernel's contextual information structure BAM_KernelInfo */
    BAM_KernelExecFuncDef *kernelExecFunc;  /**< @brief Pointer to the structure BAM_KernelExecFuncDef that list the execution functions  */
    char *name;                             /**< @brief Unique string denoting kernel name*/
    BAM_KernelId kernelId;                  /**< @brief Unique ID of the kernel*/
} BAM_KernelExecFuncDBdef;

/**
 *  @brief  This structure contains reference to the helper functions and execute functions databases.
 *          Reference to this structure can be passed to functions BAM_initKernelDB() and to member kernelDB of BAM_CreateGraphParams
 *          used by BAM_createGraph() and BAM_optimizeGraph().
 */
typedef struct
{
    const int32_t numBAMKernels;                    /**< @brief Number of kernels  recorded in the database */
    const BAM_KernelHostDBdef *kernelHostFuncDB;    /**< @brief Point to the BAM_KernelHostDBdef database */
    const BAM_KernelExecFuncDBdef *kernelExecFuncDB;    /**< @brief Point to the BAM_KernelExecFuncDBdef database */
} BAM_KernelDBdef;

/**
 *  @brief  This structure contains block context information that the kernel context may include to track what block
 *           the kernel is processing for each call to the compute function.
 */
typedef struct
{
    uint16_t numBlocksTotal;
    uint16_t numBlocksHorz;
    uint16_t numBlocksVert;
    uint16_t blkCntTotal;
    uint16_t blkCntHorz;
    uint16_t blkCntVert;
    uint16_t equalSizeFlag;
} BAM_blockContext;

/**
 *  @brief  This structure contains information about the width of the right-most column of blocks, and the height of the
 *           bottom row of blocks.  The kernel compute functions may use an array of these in their local context to adjust
 *           the processing sizes at these special cases.
 */
typedef struct
{
    uint16_t lastWidth;
    uint16_t lastHeight;
} BAM_blockLastSize;

#endif
