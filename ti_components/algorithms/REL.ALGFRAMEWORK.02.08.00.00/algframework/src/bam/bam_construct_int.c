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




#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <string.h>
#pragma RESET_MISRA ("required")
#include "cpu.h"
#include "algframework.h"
#include "bam_kernel_interface.h"
#include "bam_construct_int.h"
#include "bam_utils.h"
#include "bam_mempkt.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7 */
/* Function-like macro definition */
/* Deviation allowed here because MAX is a very simple operation better implemented in form of a macro */
#define MAX(a,b) (((a)>(b))?(a):(b))
/* RESET_MISRA("19.7")  -> Reset rule 19.7*/

/* CHECK_MISRA("-10.5")  -> Disable rule 10.5 */
/* The result of bitwise operation on unsigned char or short is not cast back to original type */
/* There seems to be false positive for this MISRA rule when the macro BAM_ALIGN_WORD() is invoked throughout the code */
/* That's why we disable this rule */

#define NO_SRC_SINK_OVERLAP

int32_t BAM_getMemPacket(BAM_Packet **packet, VCOP_MEMHEAP space, int32_t alignment, uint32_t size);
void BAM_releaseMemPacket(void **memTabBase);
void BAM_releaseMemPacketForOutput(void *memTabExt[], void **memTabBase);

BAM_Status BAM_copyNodeList(BAM_CreateGraphParams *createParams, BAM_NodeParamsInt copyOfNodeList[]) {

    BAM_NodeParams (*nodeList)[];

    BAM_Status status = BAM_S_SUCCESS;
    uint32_t j= 0;

    nodeList= (BAM_NodeParams (*)[])(void*)createParams->nodeList;

    while((*nodeList)[j].nodeIndex!= BAM_END_NODE_MARKER) {
        createParams->onChipScratchMemConsumed+= sizeof(BAM_NodeParamsInt);
        if (createParams->onChipScratchMemConsumed > createParams->onChipScratchMemSize) {
            status= BAM_E_INVALID_MEM_SIZE;
            goto Exit;
        }
        copyOfNodeList[j].nodeIndex= (*nodeList)[j].nodeIndex;
        copyOfNodeList[j].kernelId= (*nodeList)[j].kernelId;
        copyOfNodeList[j].kernelArgs= (*nodeList)[j].kernelArgs;
        copyOfNodeList[j].kernelInfo= NULL;

        j++;
    }

    createParams->onChipScratchMemConsumed+= sizeof(BAM_NodeParamsInt);
    if (createParams->onChipScratchMemConsumed > createParams->onChipScratchMemSize) {
        status= BAM_E_INVALID_MEM_SIZE;
        goto Exit;
    }
    copyOfNodeList[j].nodeIndex= BAM_END_NODE_MARKER;

    Exit:
    return status;
}

BAM_Status BAM_fillKernelInfo(BAM_CoreType coreType, const BAM_KernelDBdef *kernelDBDef, BAM_NodeParamsInt nodeList[]) {

    const BAM_KernelHostDBdef (*kernelHostDbArray)[];
    BAM_Status status = BAM_S_SUCCESS;
    uint8_t i, j;

    kernelHostDbArray= (const BAM_KernelHostDBdef (*)[])(const void*)(kernelDBDef->kernelHostFuncDB);

    j=0;
    /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
    /* Iteration statement has more than one break or goto for loop termination */
    /* Deviation is allowed because all the GOTOs point to a single exit point */
    while(nodeList[j].nodeIndex!= BAM_END_NODE_MARKER) {
        for (i = 0; i < kernelDBDef->numBAMKernels; i++)
        {
            if (nodeList[j].kernelId == (*kernelHostDbArray)[i].kernelId)
            {
                break; /* MISRA waiver */
            }
        }

        if (i == kernelDBDef->numBAMKernels)
        {
            PRINTF("kernelId provided not found in database!!!\n");
            status= BAM_E_FAIL;
            goto Exit;
        }

        if ((coreType==  BAM_EVE) || (coreType == BAM_DSP_C66x) || (coreType == BAM_DSP_C71x)) {
            if (((*kernelHostDbArray)[i].kernelInfo->coreType != BAM_EVE) && ((*kernelHostDbArray)[i].kernelInfo->coreType != BAM_EVE_ARP32)
                && ((*kernelHostDbArray)[i].kernelInfo->coreType != BAM_DSP_C66x) && ((*kernelHostDbArray)[i].kernelInfo->coreType != BAM_DSP_C71x)) {
                PRINTF("Kernel's core type doesn't match graph's core type !\n");
                status= BAM_E_CORETYPE_INVALID;
                goto Exit;
            }

        }
        else if (coreType!=  (*kernelHostDbArray)[i].kernelInfo->coreType) {
            PRINTF("Kernel's core type doesn't match graph's core type !\n");
            status= BAM_E_CORETYPE_INVALID;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }
        else {
            PRINTF("Invalid core type !\n");
            status= BAM_E_CORETYPE_INVALID;
            /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
            /* GOTO is used at error check to jump to end of function, to exit.   */
            goto Exit;
            /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
        }

        nodeList[j].kernelInfo = (*kernelHostDbArray)[i].kernelInfo;

        j++;

    }
    /* RESET_MISRA("14.6")  -> Reset rule 14.6*/

    Exit:
    return status;
}


BAM_Status BAM_getGraphMemSize(const BAM_NodeParamsInt nodeList[], const BAM_EdgeParams edgeList[], uint32_t *graphMemSize, uint32_t *numMemtabs)
{
    BAM_Status status = BAM_S_SUCCESS;
    uint16_t totalNodes, numDataBlocks;
    int16_t i;

    /* Check for null arguments */
    if ((NULL == graphMemSize))
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* graphdef, kernelInfo & kernelContext are included in the graphDef. Here graphdef & kernelInfo
     * is accounted for. Additionally add the size of kernelContext. Can't do it here, since it depends
     * on the actual kernel. note that kernelInfo & kernelContext must fit within the size
     * MAX_GRAPH_MEM_CONTEXT_SIZE_SUPPORTED
     */
    *graphMemSize = 0;
    *numMemtabs = 0;
    i=0;
    while(nodeList[i].nodeIndex!= BAM_END_NODE_MARKER)
    {
        *graphMemSize += BAM_ALIGN_WORD(nodeList[i].kernelInfo->kernelContextSize);
        /* In case a kernel's compute node is entirely implemented on ARP32, we double kernelContextSize
         * We actually want to keep 2 copies of the context in order to handle ping-pong buffering for ARP32 kernels.
         * Indeed each pointer in context->pInternalBlock[], context->pInBlock[], context->pOutBlock[]
         * needs to have 2 versions: one that points to img buffer A and one that points to img buffer B
         * BAM_finaliseGraph() will be in charge to create both versions of each pointer.
         */
        if (((nodeList[i].kernelInfo->coreType== BAM_EVE_ARP32) ||(nodeList[i].kernelInfo->coreType == BAM_DSP_C66x) ||(nodeList[i].kernelInfo->coreType == BAM_DSP_C71x)) && (nodeList[i].kernelInfo->nodeType >= BAM_NODE_COMPUTE)) {
            *graphMemSize += BAM_ALIGN_WORD(nodeList[i].kernelInfo->kernelContextSize);
        }

        *numMemtabs += nodeList[i].kernelInfo->numRecInternal;
        *numMemtabs += nodeList[i].kernelInfo->numOutputDataBlocks;
        i++;
    }
    totalNodes= (uint16_t)i;

    if (BAM_MAX_NODES < totalNodes)
    {
        status = BAM_E_INVALID_NODE_COUNT;
        goto Exit;
    }

    /* From the list of edges, compute number of datablocks that will need to be allocated
            Basically every time, the pair (upStreamNodeId, upStreamNodePort) changes, a data block must be created
     */
    i=1;
    numDataBlocks= 1U;
    while (edgeList[i].upStreamNode.id != BAM_END_NODE_MARKER) {
        if ((edgeList[i].upStreamNode.id != edgeList[i-1].upStreamNode.id) || (edgeList[i].upStreamNode.port != edgeList[i-1].upStreamNode.port)) {
            numDataBlocks++;
        }
        i++;
    }

    /* Calculate total memory required to store graph definition */
    *graphMemSize += ((uint32_t)sizeof(BAM_GraphDef) + ((uint32_t)sizeof(BAM_NodeDef) * (uint32_t)totalNodes) + ((uint32_t)sizeof(BAM_DataBlockDef) * (uint32_t)numDataBlocks));

    Exit:
    return (status);
}

BAM_Status BAM_initGraph(const BAM_NodeParamsInt nodeList[], const BAM_EdgeParams edgeList[], BAM_GraphHandle graphHandle, uint32_t graphMemSize)
{
    BAM_Status status = BAM_S_SUCCESS;
    BAM_NodeDef (*nodeDef)[];
    uint16_t dataIndex;
    uint16_t numDataBlocks;
    uint8_t nodeIndex;
    uint8_t dataBlockId;
    int16_t i;

    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;

    dataBlockId= 0;
    /* Check for null params */
    if ((NULL == graphHandle))
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Initialize status */
    graphDef->size = graphMemSize;
    graphDef->status = BAM_GRAPH_INITIALIZED;

    /* Save graph definition record size and graph params */
    i=0;
    graphDef->params.numSourceNodes= 0;
    graphDef->params.numComputeNodes= 0;
    graphDef->params.numSinkNodes= 0;
    while(nodeList[i].nodeIndex!= BAM_END_NODE_MARKER)
    {
        if (nodeList[i].kernelInfo->nodeType== BAM_NODE_SOURCE){
            graphDef->params.numSourceNodes++;
        }
        else if (nodeList[i].kernelInfo->nodeType >= BAM_NODE_COMPUTE) {
            graphDef->params.numComputeNodes++;
        }
        else if (nodeList[i].kernelInfo->nodeType== BAM_NODE_SINK) {
            graphDef->params.numSinkNodes++;
        }
        else {
            status = BAM_E_INVALID_NODE_TYPE;
            goto Exit;
        }
        i++;
    }
    graphDef->totalNodes= i;

    /* From the list of edges, compute number of datablocks that will need to be allocated
            Basically every time, the pair (upStreamNodeId, upStreamNodePort) changes, a data block must be created
     */
    i=1;
    numDataBlocks= 1U;
    while (edgeList[i].upStreamNode.id != BAM_END_NODE_MARKER) {
        if ((edgeList[i].upStreamNode.id != edgeList[i-1].upStreamNode.id) || (edgeList[i].upStreamNode.port != edgeList[i-1].upStreamNode.port)) {
            numDataBlocks++;
        }
        i++;
    }

    graphDef->params.numDataBlocks= numDataBlocks;


    graphDef->nodeDefArrOffset = 0;
    nodeDef = (BAM_NodeDef (*)[])(void*)((BAM_BytePtr) &graphDef->contextMem[graphDef->nodeDefArrOffset]);

    graphDef->dataBlockDefArrOffset = graphDef->nodeDefArrOffset  + (sizeof(BAM_NodeDef) * graphDef->totalNodes);
    graphDef->curFreeKernelContextOffset = graphDef->dataBlockDefArrOffset
            + (sizeof(BAM_DataBlockDef) * graphDef->params.numDataBlocks);

    /* Initialize node definition array */
    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; ++nodeIndex)
    {
        (*nodeDef)[nodeIndex].kernelInfo.kernelId = BAM_INVALID_KERNEL_ID;

        for (dataIndex = 0; dataIndex < BAM_MAX_NODE_INPUT_OUTPUT; ++dataIndex)
        {
            (*nodeDef)[nodeIndex].inDataBlockIndex[dataIndex] = BAM_INVALID_INDEX;
        }
        for (dataIndex = 0; dataIndex < BAM_MAX_NODE_INPUT_OUTPUT; ++dataIndex)
        {
            (*nodeDef)[nodeIndex].outDataBlockIndex[dataIndex] = BAM_INVALID_INDEX;
        }
    }

    graphDef->initInstanceDone = 0;

    /* Mark all node structures free */
    graphDef->curFreeNode = 0;
    graphDef->curFreeDataBlock = 0;

    /* Create nodes */
    /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
    /* Iteration statement has more than one break or goto for loop termination */
    /* Deviation is allowed because all the GOTOs point to a single exit point */
    for (i=0;i<graphDef->totalNodes ;i++) {
        status= BAM_newNode(graphHandle, nodeList[i].kernelInfo, &nodeIndex);

        if(status != BAM_S_SUCCESS)
        {
            goto Exit;
        }

        if (nodeIndex != nodeList[i].nodeIndex){
            PRINTF("Error in BAM_createGraph(): nodeIndex mismatches !");
            status = BAM_E_INVALID_NODE_INDEX;
            goto Exit;
        }
    }

    /* Create data blocks and the connections between data block and nodes from the list of edges */
    i= 0;
    /* Create the first data block */
    status= BAM_newDataBlock(graphHandle, &dataBlockId);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }
    /* Create the connection from the upstream node to the datablock */
    status = BAM_attachDataBlockToNode(graphHandle, BAM_OUTPUT, dataBlockId, edgeList[i].upStreamNode.id, edgeList[i].upStreamNode.port);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }
    /* Create the connection from the downstream node to the datablock */
    status = BAM_attachDataBlockToNode(graphHandle, BAM_INPUT, dataBlockId, edgeList[i].downStreamNode.id, edgeList[i].downStreamNode.port);
    if(status != BAM_S_SUCCESS)
    {
        goto Exit;
    }

    /* From the list of edges, create a datablocks when needed and make the necessary connections
         Basically every time, the pair (upStreamNodeId, upStreamNodePort) changes, a data block is created
     */
    i++;
    while (edgeList[i].upStreamNode.id != BAM_END_NODE_MARKER) {
        if ((edgeList[i].upStreamNode.id != edgeList[i-1].upStreamNode.id) || (edgeList[i].upStreamNode.port != edgeList[i-1].upStreamNode.port)) {
            status= BAM_newDataBlock(graphHandle, &dataBlockId);
            if(status != BAM_S_SUCCESS)
            {
                goto Exit;
            }
        }
        /* Create the connection from the upstream node to the datablock */
        status = BAM_attachDataBlockToNode(graphHandle, BAM_OUTPUT, dataBlockId, edgeList[i].upStreamNode.id, edgeList[i].upStreamNode.port);
        if(status != BAM_S_SUCCESS)
        {
            goto Exit;
        }
        /* Create the connection from the downstream node to the datablock */
        status = BAM_attachDataBlockToNode(graphHandle, BAM_INPUT, dataBlockId, edgeList[i].downStreamNode.id, edgeList[i].downStreamNode.port);
        if(status != BAM_S_SUCCESS)
        {
            goto Exit;
        }
        i++;
    }
    /* RESET_MISRA("14.6")  -> Reset rule 14.6*/

    /* Search if we missed any output data block for the compute nodes. In particular some output datablock may not have been created because
     * the no port connection was specified in the edge list. In this case we return the error BAM_E_PORT_NOT_CONNECTED.
     * The programmer can rectify the error by connecting the unused port to the node BAM_NULL_NODE= 255 .
     * This will make sure that a datablock gets created and can be used to store the output of the kernel associated to the unconnected port. Even if not used, the kernel still produces
     * data, which needs to go somewhere.
     * No need to do this for a source node.
     * */
    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; ++nodeIndex) {
        if ((*nodeDef)[nodeIndex].kernelInfo.nodeType >= BAM_NODE_COMPUTE) {
            for (dataIndex = 0; dataIndex < (*nodeDef)[nodeIndex].kernelInfo.numOutputDataBlocks; ++dataIndex)
            {
                if ((*nodeDef)[nodeIndex].outDataBlockIndex[dataIndex]== BAM_INVALID_INDEX) {
                    status= BAM_E_PORT_NOT_CONNECTED;
                    goto Exit;
                }
            }
        }
    }

    Exit:
    return (status);
}


BAM_Status  BAM_deInitGraph(BAM_GraphHandle graphHandle, BAM_MemRec graphHandleMemRec[])
{
    int32_t status = BAM_S_SUCCESS;
    int32_t memReci = 0;

    if(graphHandleMemRec)
    {
        BAM_NodeDef (*node)[];
        BAM_DataBlockDef (*dataBlockArr)[];
        uint8_t dataBlkIndex = 0, nodeIndex = 0;

        /* get the graph handle */
        BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;

        /* Get mapped index of the data block */
        dataBlockArr = (BAM_DataBlockDef (*)[])(void*)(&graphDef->contextMem[graphDef->dataBlockDefArrOffset]);

        node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

        for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
        {
            /* save only output data blocks. input data blocks are outputs of other nodes */
            for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numOutputDataBlocks; dataBlkIndex++)
            {
                graphHandleMemRec[memReci] = ((*dataBlockArr)[(*node)[nodeIndex].outDataBlockIndex[dataBlkIndex]].mem);
                memReci++;
            }
            /* save internal data blocks.*/
            for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numRecInternal; dataBlkIndex++)
            {
                graphHandleMemRec[memReci] = ((*node)[nodeIndex].internalBlock[dataBlkIndex]);
                memReci++;
            }
        }
    }
    else
    {
        status = BAM_E_FAIL;
    }
    return status;
}

BAM_Status BAM_updateNodes(BAM_GraphHandle graphHandle, BAM_CreateGraphParams *createParams, uint32_t callSetMemRec){

    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    BAM_Status status = BAM_S_SUCCESS;
    uint16_t i= 0;

    BAM_MemRec (*memRec)[];

    memRec= (BAM_MemRec (*)[])(void*)graphDef->memRec;

    if (createParams->useSmartMemAlloc== true) {
        for (i = 0; i < graphDef->numMemTabs; i++)
        {
            (*memRec)[i].size = 0;
            (*memRec)[i].alignment = 1; /* 1 byte alignment */
            (*memRec)[i].base = 0;
            (*memRec)[i].ext = 0;
            (*memRec)[i].space = VCOP_MEMSPACE_NONE;
            (*memRec)[i].name= NULL;
        }

        status = BAM_getMemRec(graphHandle, createParams, graphDef->memRec);
        if (status != BAM_S_SUCCESS) {
            goto Exit;
        }


        status = BAM_autoAllocMemRec(graphHandle, createParams, graphDef->memRec);
        if (status != BAM_S_SUCCESS) {
            goto Exit;
        }
    }
    else {
        status = BAM_getMemRec(graphHandle, createParams, graphDef->memRec);
        if (status != BAM_S_SUCCESS) {
            goto Exit;
        }
    }

    if (callSetMemRec== (uint32_t)true) {
#ifdef CORE_DSP
        status = BAM_setMemRec(graphHandle, graphDef->memRec, createParams->nodeList, &createParams->intMemParams);
#else
        status = BAM_setMemRec(graphHandle, graphDef->memRec, createParams->nodeList, NULL);
#endif
        if (status != BAM_S_SUCCESS) {
            goto Exit;
        }
    }

    Exit:
    return (status);
}



static BAM_Status BAM_autoAllocMemRec(BAM_GraphHandle graphHandle, BAM_CreateGraphParams *createParams, BAM_MemRec memTab[])
{

    uint8_t memSequence[3]={BAM_MEMSPACE_IBUFLA, BAM_MEMSPACE_IBUFHA, BAM_MEMSPACE_WBUF};
    BAM_Status status = BAM_S_SUCCESS;
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    BAM_DataBlockDef (*dataBlockArr)[];
    BAM_NodeDef (*nodeArr)[];
    uint8_t (*extMem)[];
    BAM_DataBlockDef *pOutDataBlock= 0;
    uint32_t useWMEM= (uint32_t)true;
    BAM_Packet *packetPool= graphDef->packetPool;

    BAM_MemSpace space= 0;
    uint8_t numRecInternal = 0;
    uint8_t numRecOutputDataBlock = 0;

    uint8_t nodeIndex = 0;

    uint8_t kernelIndex = 0;
    uint8_t type= 0;
    uint8_t i= 0, j=0;
    uint8_t curMemSpace= 0;
    uint8_t outIndex= 0;
    int16_t curMemTab = 0;
    uint16_t tempMemTab = 0;
    int16_t lastMemTab= 0;
    int16_t firstInternalMemTab= 0;
    uint8_t numReaderNodes;
    uint8_t attrs;

    void *ptr = 0;
    uint8_t (*ptrMem)[32];
    uint32_t wMemSize= 0;
    uint32_t size= 0;
    BAM_Packet *packetPtr= NULL;


    BAM_NodeParams (*nodeList)[];

    nodeList= (BAM_NodeParams (*)[])(void*)createParams->nodeList;
    /* When BAM_autoAllocMemRec() is called, we start from fresh, as if no memory has been allocated before.
     * Rewind the amount of ext memory consumed to the starting point as we don't want extMemConsumed to be increased every time  BAM_autoAllocMemRec() is called
     * Same thing for scratch memory located in on-chip (DMEM for EVE)
     * */
    createParams->extMemConsumed= 0;
    createParams->graphMemConsumed= graphDef->graphMemSize;

    /* Get mapped index of the data block */
    dataBlockArr = (BAM_DataBlockDef (*)[])(void*)(&graphDef->contextMem[graphDef->dataBlockDefArrOffset]);
    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

#ifdef DEBUG_BAM_MALLOC
    vcop_minit();
#endif
#ifdef CORE_DSP
    bam_minit(packetPool, graphDef->numMemTabs + BAM_NUM_GUARD_PACKETS,&createParams->intMemParams);
#else
    bam_minit(packetPool, graphDef->numMemTabs + BAM_NUM_GUARD_PACKETS,NULL);
  
#endif
    wMemSize= 0;

    /* Allocate first the memory records that are in WMEM and are persistent or constant.
     * The reason we do that first is to prevent them from being overlapped with the output data blocks
     * which can be overlaid on top of each others.
     * At the same time, calculate the total amount of persisent memory allocated in WMEM as wMemSize
     * */
    curMemTab = 0;
    for (kernelIndex = 0; kernelIndex < graphDef->totalNodes; kernelIndex++) {

        nodeIndex = (*nodeList)[kernelIndex].nodeIndex;
        numRecInternal = (*nodeArr)[nodeIndex].kernelInfo.numRecInternal;
        numRecOutputDataBlock =  (*nodeArr)[nodeIndex].kernelInfo.numOutputDataBlocks;

        /* Compute the sum of the size of the constant or persistent blocks that have to be allocated in WMEM */
        /* Create nodes */
        /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
        /* Iteration statement has more than one break or goto for loop termination */
        /* Deviation is allowed because all the GOTOs point to a single exit point */
        for (j=0; j < numRecInternal; j++) {
            /* In case the internal memory record's attribute was set to BAM_MEMATTRS_PERSIST or BAM_MEMATTRS_CONST and its space set to BAM_MEMSPACE_ANY_VCOPBUF
             * we change the space to BAM_MEMSPACE_WBUF
             */
            if (((memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_PERSIST) || (memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_CONST)) && (memTab[curMemTab].space== BAM_MEMSPACE_ANY_VCOPBUF)) {
                memTab[curMemTab].space= BAM_MEMSPACE_WBUF;
            }

            if ((memTab[curMemTab].space== BAM_MEMSPACE_WBUF) && ((memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_PERSIST) || (memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_CONST))) {
                size= memTab[curMemTab].size;
                wMemSize+= size;

                status= BAM_getMemPacket(&packetPtr, (VCOP_MEMHEAP)memTab[curMemTab].space, memTab[curMemTab].alignment, size);
                /* If BAM_getMemPacket() successful, we record packetPtr into memTab[curMemTab].base. We need to keep track of this packet because it contains 
                 * meta information that will be needed by BAM_releaseMemPacket().
                 * Later when we release the packet, BAM_releaseMemPacket() will record packetPtr->ptr into memTab[curMemTab].base because
                 * after this point, the meta-information is no longer required. We only need to save the actual location of the allocated memory. 
                 * */
                if (status== BAM_S_SUCCESS) {
                    memTab[curMemTab].base= (void*)packetPtr;
                }
                else{
                    lastMemTab= curMemTab;
                    goto Exit;
                }

#ifdef SHOW_MEM
                PRINTF("[BAM node #%d]\t%d\t0x%x\t0x%x\t%d\n", nodeIndex, curMemTab, packetPtr->ptr, memTab[curMemTab].size, memTab[curMemTab].space);
#endif
                /* if the space for base is internal memory, and the type is persistent allocate an additional external memory to enable context save/restore. */
                if ((size!=0) && (memTab[curMemTab].ext == NULL) && (memTab[curMemTab].attrs.memAttrs== (uint8_t)BAM_MEMATTRS_PERSIST) && (memTab[curMemTab].space != BAM_MEMSPACE_EXTMEM) ) {
                    ptrMem= (uint8_t (*)[32])(void*)createParams->extMem;
                    ptr = (void*)&((*ptrMem)[createParams->extMemConsumed]);
                    createParams->extMemConsumed += size;
                    if (createParams->extMemConsumed >  createParams->extMemSize) {
                        status= BAM_E_INVALID_MEM_SIZE;
#ifdef DEBUG
                        PRINTF("[BAM node #%d] BAM_autoAllocMemRec() failed to allocate %d bytes in EXTMEM for context saving purpose, please increase createParams->extMemsize  !!!\n", nodeIndex, size);
#endif
                        goto Exit;
                    }
                    memTab[curMemTab].ext= ptr;
#ifdef SHOW_MEM
                    PRINTF("[BAM node #%d context saving]\t%d\t0x%x\t0x%x\t%d\n", nodeIndex, curMemTab, ptr, memTab[curMemTab].size, BAM_MEMSPACE_EXTMEM);
#endif
                }

            }

            curMemTab++;
        }
        /* RESET_MISRA("14.6")  -> Reset rule 14.6*/
        curMemTab+= (int16_t)numRecOutputDataBlock;
    }

    /* Note the position of the lastMemTab, will need it whenever we free the pointers */
    lastMemTab= curMemTab - 1;
    /* If wMemSize exceeds a certain threshold then we don't use WMEM anymore for the rest of the memory allocation */
    /* Below lines are commented out as they may not yield to any improvement in memory allocation */
    /*
    if (wMemSize >= ((int32_t)WMEM_SIZE*3)/4) {
        useWMEM= false;
    }
    else {
        useWMEM= true;
    }
     */

    /* Allocate output data blocks of each kernel */
    curMemTab= 0;

    for (kernelIndex = 0; kernelIndex < graphDef->totalNodes; kernelIndex++) {
        nodeIndex = (*nodeList)[kernelIndex].nodeIndex;
        numRecOutputDataBlock =  (*nodeArr)[nodeIndex].kernelInfo.numOutputDataBlocks;
        numRecInternal = (*nodeArr)[nodeIndex].kernelInfo.numRecInternal;
        outIndex= 0;

        /* Modify the memTab[].space that have the initial value BAM_MEMSPACE_ANY and memAttrs set to BAM_MEMATTRS_SCRATCH to one of the following: BAM_MEMSPACE_IBUFLA, IBUFHA or WMEM
         * For now, the algorithm naively cyclically alternates the memtabs in order to minimize access to the same memories. Basically the first eligible memTab[].space should be set
         * to IBUFLA, then second to IBUFHA, the third to WMEM, the fourth to IBUFLA, etc
         * For source node, WMEM is excluded as EDMA cannot write into it.
         * For a node upstream to a sink node, WMEM is also for an output block as EDMA cannot read from it
         *
         * This method won't always produce the best solution but is better than nothing
         */

        /* Find the last input's block mem space, which will set the starting point of the cyclical sequence
         * */
        if ((*nodeArr)[nodeIndex].kernelInfo.numInputDataBlocks) {
            space= (*dataBlockArr)[(*nodeArr)[nodeIndex].inDataBlockIndex[(*nodeArr)[nodeIndex].kernelInfo.numInputDataBlocks-1]].mem.space;
            if (space== BAM_MEMSPACE_IBUFLA){
                curMemSpace= 1U;
            }
            else if (space== (BAM_MemSpace)BAM_MEMSPACE_IBUFHA){
                if (useWMEM== (uint32_t)true) {
                    curMemSpace= 2U;
                }
                else {
                    curMemSpace= 0U;
                }
            }
            else {
                curMemSpace= 0U;
            }
        }

        /* Now we are going to assign the eligible internal and output data block's mem space in a cyclical manner. */
        for (j=0; j < (numRecInternal + numRecOutputDataBlock); j++) {
            /* Look for eligible mem data block, the one whose mem space is set to IBAMALG_ANYEVE_MEM and contain scratch data */
            if ((memTab[curMemTab+(int16_t)j].space== (BAM_MemSpace)BAM_MEMSPACE_ANY_VCOPBUF) && (memTab[curMemTab+(int16_t)j].attrs.memAttrs== (uint8_t)BAM_MEMATTRS_SCRATCH)) {
                type= (uint8_t)memTab[curMemTab+(int16_t)j].attrs.memType;
                /* In case the block is an output block, we need to add some additional constraints on the value of curMemSpace */
                if (type== BAM_MEMTYPE_NODEMEM_OUTPUT) {
                    /* In case NO_SRC_SINK_OVERLAP is enabled, we want to avoid the output blocks of source nodes to overlap with input blocks of sink nodes
                     * Overlapping source and sink memory blocks can cause memory corruptions if the sink channels DMA don't complete before the source channels DMA.
                     */
#ifdef NO_SRC_SINK_OVERLAP
                    /* If node is a source node, make sure to set the output block space to  BAM_MEMSPACE_IBUFLA*/
                    if ((*nodeArr)[nodeIndex].nodeType== BAM_NODE_SOURCE) {
                        curMemSpace= BAM_MEMSPACE_IBUFLA;
                    }
                    else /* otherwise check if the block is attached to a sink node by checking if any of the reader of the block is a sink node */
                    {
                        pOutDataBlock= &((*dataBlockArr)[(*nodeArr)[nodeIndex].outDataBlockIndex[outIndex]]);
                        for (i=0; i<pOutDataBlock->numReaderNodes;i++) {
                            /* Set the output block memspace to BAM_MEMSPACE_IBUFHA */
                            if(pOutDataBlock->readerNodeIndex[i] < graphDef->totalNodes)
                            {
                                if ((*nodeArr)[pOutDataBlock->readerNodeIndex[i]].nodeType== BAM_NODE_SINK) {
                                    curMemSpace= (uint8_t)BAM_MEMSPACE_IBUFHA;
                                    break;
                                }
                            }
                        }
                    }
#else
                    /* If the data block is an output block and if the node is a source node, then make sure that the memspace is not WMEM
                     * Because blocks that are destinated to be DMAed cann only be located in IMBUF.
                     * So we set curMemSpace to 0 if necessary
                     * Same thing if one of the output block is chained to a sink node  */
                    /* if WMEM */
                    if (curMemSpace== 2) {
                        /* if node is a source node */
                        if ((*nodeArr)[nodeIndex].nodeType== BAM_NODE_SOURCE) {
                            curMemSpace= 0;
                        }
                        else /* otherwise check if any of the reader of the block is a sink node */
                        {
                            pOutDataBlock= &((*dataBlockArr)[(*nodeArr)[nodeIndex].outDataBlockIndex[outIndex]]);
                            for (i=0; i<pOutDataBlock->numReaderNodes;i++) {
                                if(pOutDataBlock->readerNodeIndex[i] < graphDef->totalNodes)
                                {
                                    if ((*nodeArr)[pOutDataBlock->readerNodeIndex[i]].nodeType== BAM_NODE_SINK) {
                                        curMemSpace= 0;
                                        break;
                                    }
                                }
                            }
                        }
                    }
#endif
                    outIndex++;
                }
                memTab[curMemTab+(int16_t)j].space= (BAM_MemSpace)memSequence[curMemSpace];

                /* Go through the mem spaces in a cyclic manner */
                if (useWMEM== (uint32_t)true) {
                    if (curMemSpace== 2U) {
                        curMemSpace= 0U;
                    }
                    else {
                        curMemSpace++;
                    }

                }
                else {
                    if (curMemSpace== 1U) {
                        curMemSpace= 0U;
                    }
                    else {
                        curMemSpace++;
                    }

                }
            }
        }

        outIndex= 0;
        /* Allocate memory blocks in EVE memory */
        firstInternalMemTab= curMemTab;
        /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
        /* Iteration statement has more than one break or goto for loop termination */
        /* Deviation is allowed because all the GOTOs point to a single exit point */
        for (j=0; j < (numRecInternal + numRecOutputDataBlock); j++) {
            space= memTab[curMemTab].space;
            size= memTab[curMemTab].size;
            type= memTab[curMemTab].attrs.memType;

            /* Skip the memory records that are in WMEM and are persisent or constant as they have already been allocated at the beginning of the function */
            if (!((memTab[curMemTab].space== BAM_MEMSPACE_WBUF) && ((memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_PERSIST) || (memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_CONST)))) {
                if (size== 0) {
                    status= BAM_E_INVALID_MEM_SIZE;
#ifdef DEBUG
                    PRINTF("[BAM node #%d] BAM_autoAllocMemRec() size should not be 0!!!\n");
#endif
                    goto ExitLoop;
                }

                if(space < IBAMALG_MEMHEAP_DMEM) {

                    status= BAM_getMemPacket(&packetPtr, (VCOP_MEMHEAP)space, memTab[curMemTab].alignment, size);

                    if (status == BAM_E_BLOCK_DIM_TOO_BIG) {

                        /* if allocation failed and was in WBUF, then try again in IBUFLA and then IBUFHA */
                        if (space== BAM_MEMSPACE_WBUF) {
                            useWMEM= (uint32_t)false; /* For now on, we avoid using WMEM since allocation failed one time, likely due to big constant tables in WMEM */
                            space= memTab[curMemTab].space= BAM_MEMSPACE_IBUFLA;
                            status= BAM_getMemPacket(&packetPtr, (VCOP_MEMHEAP)space, memTab[curMemTab].alignment, size);

                            if (status== BAM_E_BLOCK_DIM_TOO_BIG) {
                                space= memTab[curMemTab].space= BAM_MEMSPACE_IBUFHA;
                                status= BAM_getMemPacket(&packetPtr, (VCOP_MEMHEAP)space, memTab[curMemTab].alignment, size);
                            }
                        }
                    }

                    if (status!= BAM_S_SUCCESS) {
                        goto ExitLoop;
                    }

                } else if(space == IBAMALG_MEMHEAP_DMEM) {
                    /* 8/22/2016: We are preventing allocation in DMEM as it is causing issue since at create time, DMEM is not accessible  */
                    /*
                    ptrMem= (uint8_t (*)[32])createParams->graphMem;
                    ptr= (void*)(&((*ptrMem)[createParams->graphMemConsumed]));
                    createParams->graphMemConsumed += size;
                    if (createParams->graphMemConsumed >  createParams->graphMemSize) {
                        status= BAM_E_INVALID_MEM_SIZE;
#ifdef DEBUG
                        PRINTF("[BAM node #%d] BAM_autoAllocMemRec() failed to allocate %d bytes in DMEM!!!\n", nodeIndex, size);
#endif
                        goto ExitLoop;
                    }
                     */
                    status= BAM_E_INVALID_MEM_SPACE;
#ifdef DEBUG
                    PRINTF("[BAM node #%d] BAM_autoAllocMemRec() does not support memory record's space of IBAMALG_MEMHEAP_DMEM!!!\n", nodeIndex);
#endif
                    goto ExitLoop;

                } /* currently allocation in EXTMEM is allowed only for memory records that are constant */
                else if((space == IBAMALG_MEMHEAP_EXTMEM) && (memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_CONST))
                {                  
                    extMem= (uint8_t (*)[])createParams->extMem;
                    ptr = (void*)&((*extMem)[createParams->extMemConsumed]);
                    createParams->extMemConsumed += size;
                    if (createParams->extMemConsumed >  createParams->extMemSize) {
                        status= BAM_E_INVALID_MEM_SIZE;
#ifdef DEBUG
                        PRINTF("[BAM node #%d] BAM_autoAllocMemRec() failed to allocate %d bytes in EXTMEM, please increase createParams->extMemsize  !!!\n", nodeIndex, size);
#endif
                        goto ExitLoop;
                    }
                }
                else
                {
                    status= BAM_E_INVALID_MEM_SPACE;
#ifdef DEBUG
                    PRINTF("[BAM node #%d] BAM_autoAllocMemRec() Invalid memory record's space !!!\n", nodeIndex);
#endif
                    goto ExitLoop;
                }

#ifdef SHOW_MEM
                PRINTF("[BAM node #%d]\t%d\t0x%x\t0x%x\t%d\n", nodeIndex, curMemTab, ptr, memTab[curMemTab].size, memTab[curMemTab].space);
#endif

                /* In case the space was neither IBAMALG_MEMHEAP_EXTMEM, nor IBAMALG_MEMHEAP_DMEM, we used BAM_getMemPacket
                 * to allocate the memory, thus we have to record packetPtr into memTab[curMemTab].base, in order
                 * to keep the meta-information that will later be used by BAM_releaseMemPacket().
                 */
                if (memTab[curMemTab].space < IBAMALG_MEMHEAP_DMEM ) {
                    memTab[curMemTab].base= (void*)packetPtr;
                }
                else {
                    memTab[curMemTab].base= ptr;
                }

                if (type== BAM_MEMTYPE_NODEMEM_OUTPUT) {
                    /* We store the memTab in the associated dataBlock because we will need to later to look it up
                     * as part of an input data block in order to free it after consumption
                     */
                    (*dataBlockArr)[(*nodeArr)[nodeIndex].outDataBlockIndex[outIndex]].mem = memTab[curMemTab];

                    /* In case the block is output and is not IBAMALG_MEMHEAP_EXTMEM, nor IBAMALG_MEMHEAP_DMEM
                     * we actually move packetPtr, which was in memTab[curMemTab].base, into memTab[curMemTab].ext
                     * and record packetPtr->ptr into memTab[curMemTab].base.
                     * That's because output data block will require the function BAM_releaseOutputMemPacket() to be called
                     */
                    if (memTab[curMemTab].space < IBAMALG_MEMHEAP_DMEM) {
                        packetPtr= (BAM_Packet*)(memTab[curMemTab].base);
                        ptr= packetPtr->ptr;
                        memTab[curMemTab].base= ptr;
                        memTab[curMemTab].ext= packetPtr;
                    }

                    memTab[curMemTab].attrs.dataBlockIndex= (*nodeArr)[nodeIndex].outDataBlockIndex[outIndex];
                    outIndex++;
                }
            }
            curMemTab++;
        }
        /* RESET_MISRA("14.6")  -> Reset rule 14.6*/

        /* Check if any of the output data block we just allocated is actually connected to a BAM_NULL_NODE. If yes, we can just free it right now since its content
         * will never be consumed. This way we make space for the next node.
         * In addition we also check that no output data block has 0 reader. If it happens then something got corrupted or the graph was not properly specified
         * and we return BAM_E_SMART_MEM_ALLOCATOR
         * */
        tempMemTab= (uint16_t)curMemTab -1U;
        /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
        /* Iteration statement has more than one break or goto for loop termination */
        /* Deviation is allowed because all the GOTOs point to a single exit point */
        for (j=0; j <  numRecOutputDataBlock; j++) {
            numReaderNodes= (*dataBlockArr)[memTab[tempMemTab].attrs.dataBlockIndex].numReaderNodes;
            if (numReaderNodes == 0) {
                status= BAM_E_SMART_MEM_ALLOCATOR; /* 0 reader not allowed, return error */
                goto ExitLoop;
            }
            else {
                /* Check if the last reader was a BAM_NULL_NODE, if yes, then free. Also check that in case last reader is a BAM_NULL_NODE, it is the unique reader
                 * If not, something went wrong
                 * */
                if ((*dataBlockArr)[memTab[tempMemTab].attrs.dataBlockIndex].readerNodeIndex[numReaderNodes-1U]== (uint8_t)BAM_NULL_NODE) {
                    if (numReaderNodes != 1U) {
                        status= BAM_E_SMART_MEM_ALLOCATOR; /* 0 reader not allowed, return error */
                        goto ExitLoop;
                    } else {
                        if(space < IBAMALG_MEMHEAP_DMEM)
                        {
                            BAM_releaseMemPacket(&((*dataBlockArr)[memTab[tempMemTab].attrs.dataBlockIndex].mem.base));
                        }
                        (*dataBlockArr)[memTab[tempMemTab].attrs.dataBlockIndex].tempNumReaderNodes= 0;
                    }
                }
            }
            tempMemTab--;
        }
        /* RESET_MISRA("14.6")  -> Reset rule 14.6*/

        ExitLoop:
        /* Go through all the input buffers connected to the node and decrement the running number of
         * readers.
         * Free any input buffer for whose the running number of reader has reached 0 and reset the running number
         * to its initial value.
         * This is a memory optimization that allows reuse of memory blocks that have been consumed
         *
         * */
        for (j = 0; j < (*nodeArr)[nodeIndex].kernelInfo.numInputDataBlocks; j++) {
            if ((*dataBlockArr)[(*nodeArr)[nodeIndex].inDataBlockIndex[j]].tempNumReaderNodes > 0) {
                (*dataBlockArr)[(*nodeArr)[nodeIndex].inDataBlockIndex[j]].tempNumReaderNodes--;
                if ((*dataBlockArr)[(*nodeArr)[nodeIndex].inDataBlockIndex[j]].tempNumReaderNodes== 0) {
                    space= (*dataBlockArr)[(*nodeArr)[nodeIndex].inDataBlockIndex[j]].mem.space;
                    if((space < IBAMALG_MEMHEAP_DMEM) && ((*dataBlockArr)[(*nodeArr)[nodeIndex].inDataBlockIndex[j]].mem.attrs.memAttrs== BAM_MEMATTRS_SCRATCH)) {
                        BAM_releaseMemPacket(&((*dataBlockArr)[(*nodeArr)[nodeIndex].inDataBlockIndex[j]].mem.base));
                    }
                }

            }
        }

        /* Go through all the internal buffers that are scratched and free them
         *
         * */

        tempMemTab= (uint16_t)firstInternalMemTab;
        for (j = 0; j < numRecInternal; j++) {
            space= memTab[tempMemTab].space;
            if (memTab[tempMemTab].attrs.memAttrs== BAM_MEMATTRS_SCRATCH) {
                if((space < IBAMALG_MEMHEAP_DMEM) && (memTab[tempMemTab].base != NULL)) {
                    BAM_releaseMemPacket(&memTab[tempMemTab].base);
                }
            }
            tempMemTab++;
        }

        if (status!=  BAM_S_SUCCESS) {
            break;
        }
    }

    Exit:

    /*if (simulateAllocation== true || status== BAM_E_BLOCK_DIM_TOO_BIG ) {*/

    /* We start from the last memTab and go reverse to free memory memtabs that were allocated
     * This freeing is necessary as we used vcop_malloc() as a tool to partition the memory. We don't want to lock
     * the memory allocated because next time BAM_autoAllocMemRec(), we need to have the entire VCOP memory available again.
     */
    curMemTab= lastMemTab;

    while (curMemTab >= 0) {

        if (memTab[curMemTab].base != NULL) {
            type= memTab[curMemTab].attrs.memType;
            attrs= memTab[curMemTab].attrs.memAttrs;
            space= memTab[curMemTab].space;

            /* Memories allocated in IBAMALG_MEMHEAP_DMEM or IBAMALG_MEMHEAP_EXTMEM didn't not use dynamic allocation so don't need to be freed */
            if(space < IBAMALG_MEMHEAP_DMEM) {
                /* We only free memories that have not yet been freed. Internal records that are scratched have been freed, as well as output memory block that do not have any reader left
                 * So we only free memory records that are internal but not scratch, as well as output memory blocks that still have readers left or that are not scratch, We also avoid freeing memories that were allocated in external memory */
                if ( ((type== BAM_MEMTYPE_NODEMEM_INTERNAL) && (attrs !=  BAM_MEMATTRS_SCRATCH)) || ( (type== BAM_MEMTYPE_NODEMEM_OUTPUT) && ((*dataBlockArr)[memTab[curMemTab].attrs.dataBlockIndex].tempNumReaderNodes!= 0)) || ( (type== BAM_MEMTYPE_NODEMEM_OUTPUT) && (attrs !=  BAM_MEMATTRS_SCRATCH))) {
                    if (type== BAM_MEMTYPE_NODEMEM_OUTPUT) {
                        BAM_releaseMemPacketForOutput(&memTab[curMemTab].ext, &memTab[curMemTab].base);
                    }
                    else {
                        BAM_releaseMemPacket(&memTab[curMemTab].base);
                    }
                }
            }
            if (type== BAM_MEMTYPE_NODEMEM_OUTPUT) {
                (*dataBlockArr)[memTab[curMemTab].attrs.dataBlockIndex].tempNumReaderNodes= (*dataBlockArr)[memTab[curMemTab].attrs.dataBlockIndex].numReaderNodes;
            }
        }

        curMemTab--;
    }
    /* }*/


    graphDef->graphMemSize= createParams->graphMemConsumed;
    graphDef->extMemSize= createParams->extMemConsumed;

    /* Call bam_check() to check the consistancy of the heap after everything has been freed
     * Basically it is expected that the heap has returned to its initial state. 
     * If an error is returned then it means that something was not freed or incorrectly freed.
     */
    if (bam_mcheck() !=  BAM_S_SUCCESS ) {
        status= BAM_E_SMART_MEM_ALLOCATOR;
    }

    return (status);

}

static BAM_Status BAM_newNode(BAM_GraphHandle graphHandle, const BAM_KernelInfo *kernelInfo, uint8_t *nodeId)
{
    BAM_Status status = BAM_S_SUCCESS;
    BAM_NodeDef (*nodeArr)[];
    uint8_t nodeIndex = 0;

    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;

    /* Check for null params */
    if ((NULL == graphDef) || (NULL == kernelInfo))
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    nodeIndex = graphDef->curFreeNode;
    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    (*nodeArr)[nodeIndex].nodeType = kernelInfo->nodeType;

    /* Save kernel info */
    (*nodeArr)[nodeIndex].kernelInfo = *kernelInfo;

    (*nodeArr)[nodeIndex].kernelContext = (BAM_NodeDef *)(void*)(&graphDef->contextMem[graphDef->curFreeKernelContextOffset]);


    if ( (*nodeArr)[nodeIndex].nodeType == BAM_NODE_SINK)
    {
        if ( (*nodeArr)[nodeIndex].kernelInfo.kernelContextSize == 0 )
        {
            (*nodeArr)[nodeIndex].kernelContext = NULL;
        }
    }

    graphDef->curFreeKernelContextOffset += BAM_ALIGN_WORD((*nodeArr)[nodeIndex].kernelInfo.kernelContextSize);
    /* In case a kernel's compute node is entirely implemented on ARP32, we double kernelContextSize
     * We actually want to keep 2 copies of the context in order to handle ping-pong buffering for ARP32 kernels.
     * Indeed each pointer in context->pInternalBlock[], context->pInBlock[], context->pOutBlock[]
     * needs to have 2 versions: one that points to img buffer A and one that points to img buffer B
     * BAM_finaliseGraph() will be in charge to create both versions of each pointer.
     */
    if ((((*nodeArr)[nodeIndex].kernelInfo.coreType== BAM_EVE_ARP32) ||((*nodeArr)[nodeIndex].kernelInfo.coreType == BAM_DSP_C66x) ||((*nodeArr)[nodeIndex].kernelInfo.coreType == BAM_DSP_C71x)) && ((*nodeArr)[nodeIndex].kernelInfo.nodeType >= BAM_NODE_COMPUTE)) {
        graphDef->curFreeKernelContextOffset += BAM_ALIGN_WORD((*nodeArr)[nodeIndex].kernelInfo.kernelContextSize);
    }

    /* Return new node id */
    *nodeId = graphDef->curFreeNode;
    /* Increment free node index */
    graphDef->curFreeNode++;

    Exit:
    return (status);
}

static BAM_Status BAM_newDataBlock(BAM_GraphHandle graphHandle, uint8_t *dataBlockId)
{
    BAM_Status status = BAM_S_SUCCESS;
    BAM_DataBlockDef (*dataBlockArr)[];

    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;

    /* Check for null params */
    if (NULL == graphDef)
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    if (graphDef->curFreeDataBlock >= graphDef->params.numDataBlocks)
    {
        status = BAM_E_INVALID_DATA_BLOCK_INDEX;
        goto Exit;
    }

    /* Get mapped index of the data block */
    dataBlockArr = (BAM_DataBlockDef (*)[])(void*)(&graphDef->contextMem[graphDef->dataBlockDefArrOffset]);
    (*dataBlockArr)[graphDef->curFreeDataBlock].numReaderNodes = 0;
    memset(&(*dataBlockArr)[graphDef->curFreeDataBlock].mem, 0, sizeof((*dataBlockArr)[graphDef->curFreeDataBlock].mem));

    *dataBlockId = graphDef->curFreeDataBlock;

    ++graphDef->curFreeDataBlock;

    Exit:
    return (status);
}

static BAM_Status BAM_attachDataBlockToNode(BAM_GraphHandle graphHandle, BAM_DataBlockDir direction, uint8_t dataBlockId,
        uint8_t nodeId, uint8_t inputOutputBlockIndex)
{
    BAM_Status status = BAM_S_SUCCESS;
    BAM_NodeDef (*nodeArr)[];
    BAM_DataBlockDef (*dataBlockArr)[];
    uint8_t numReaderNodes = 0;
    uint8_t nodeType = 0;

    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;

    /* Check for null params */
    if (NULL == graphDef)
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    if (dataBlockId >= graphDef->curFreeDataBlock)
    {
        /* Data block is not yet allocated */
        status = BAM_E_INVALID_DATA_BLOCK_INDEX;
        goto Exit;
    }

    /* Node is not yet allocated */
    if ((nodeId >= graphDef->curFreeNode) && (nodeId != BAM_NULL_NODE))
    {
        status = BAM_E_INVALID_NODE_INDEX;
        goto Exit;
    }

    /* Check data block direction arg */
    if ((BAM_INPUT != direction) && (BAM_OUTPUT != direction))
    {
        status = BAM_E_INVALID_DATA_BLOCK_DIR;
        goto Exit;
    }

    /* Check input/ouput data block index arg */
    if (BAM_MAX_NODE_INPUT_OUTPUT <= inputOutputBlockIndex)
    {
        status = BAM_E_INVALID_DATA_BLOCK_INDEX;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    /* Save connection to the input/output data block */
    /* Calculate source node array in graph definition record */
    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

    dataBlockArr = (BAM_DataBlockDef (*)[])(void*)(&graphDef->contextMem[graphDef->dataBlockDefArrOffset]);

    /* Get mapped index of the data block */
    if (nodeId != BAM_NULL_NODE) { /* if nodeId is BAM_NULL_NODE, skip the section of code below */

        nodeType = (*nodeArr)[nodeId].nodeType;

        if ( (nodeType < BAM_NODE_SOURCE) || (nodeType >= BAM_NODE_MAX))
        {
            /* Not possible */
            status = BAM_E_INVALID_NODE_TYPE;
            goto Exit;
        }

        if (((BAM_NODE_SOURCE == nodeType) && (BAM_OUTPUT != direction)) ||
                ((BAM_NODE_SINK == nodeType) && (BAM_INPUT != direction)))
        {
            status = BAM_E_INVALID_DATA_BLOCK_DIR;
            goto Exit;
        }
        else {
        }
    }

    if (BAM_INPUT == direction)
    {

        numReaderNodes = (*dataBlockArr)[dataBlockId].numReaderNodes;
        (*dataBlockArr)[dataBlockId].readerNodeIndex[numReaderNodes] = nodeId;
        (*dataBlockArr)[dataBlockId].numReaderNodes++;
        /* Used by BAM_autoAllocMemRec() */
        (*dataBlockArr)[dataBlockId].tempNumReaderNodes= (*dataBlockArr)[dataBlockId].numReaderNodes;

        if (nodeId != BAM_NULL_NODE) {
            (*nodeArr)[nodeId].inDataBlockIndex[inputOutputBlockIndex] = dataBlockId;

            /* In case it is not the first connection to a downstream node, check if the previous connection was made to a BAM_NULL_NODE
             * if yes, throw an error because it is not allowed.
             */
            if (numReaderNodes >=1U ) {
                if ((*dataBlockArr)[dataBlockId].readerNodeIndex[numReaderNodes]== BAM_NULL_NODE) {
                    status= BAM_E_INVALID_NODE_INDEX;
                    goto Exit;
                }
            }
        }
        else {
            if ((*dataBlockArr)[dataBlockId].numReaderNodes != 1) {
                status= BAM_E_INVALID_NODE_INDEX;   /* We do not allow any other connection if the datablock is connected to a BAM_NULL_NODE */
                goto Exit;
            }
        }
    }
    else
    {
        (*nodeArr)[nodeId].outDataBlockIndex[inputOutputBlockIndex] = dataBlockId;
        (*dataBlockArr)[dataBlockId].writerNodeIndex = nodeId;
    }

    Exit:
    return (status);
}


/* algAlloc */
static BAM_Status BAM_getMemRec(BAM_GraphHandle graphHandle, const BAM_CreateGraphParams *createParams, BAM_MemRec memTab[])
{
    BAM_Status status = BAM_S_SUCCESS;
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;
    BAM_NodeParams (*nodeList)[];
    BAM_NodeDef (*nodeArr)[];
    uint8_t nodeIndex = 0;
    uint8_t numRecInternal = 0;
    uint8_t numRecOutputDataBlock = 0;
    const BAM_KernelHostDBdef (*kernelHostDbArray)[];
    BAM_MemRec memRecInternal[MAX_MEMRECORDS_PER_NODE];
    BAM_MemRec memRecOutputDataBlock[MAX_MEMRECORDS_PER_NODE];
    uint16_t j= 0;
    uint8_t memRecIndex = 0;
    uint8_t kernelIndex = 0;
    uint8_t curMemTab = 0;

    curMemTab = 0;

    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    nodeList= (BAM_NodeParams (*)[])(void*)createParams->nodeList;

    /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
    /* Iteration statement has more than one break or goto for loop termination */
    /* Deviation is allowed because all the GOTOs point to a single exit point */
    for (kernelIndex = 0; kernelIndex < graphDef->totalNodes; kernelIndex++)
    {
        nodeIndex = (*nodeList)[kernelIndex].nodeIndex;

        numRecOutputDataBlock =  (*nodeArr)[nodeIndex].kernelInfo.numOutputDataBlocks;
        numRecInternal = (*nodeArr)[nodeIndex].kernelInfo.numRecInternal;

        if ((numRecOutputDataBlock > (uint8_t)BAM_MAX_NODE_INPUT_OUTPUT) || (numRecInternal > (uint8_t)BAM_MAX_NODE_INTERNAL)) {
            status= BAM_E_NUM_MEM_RECORDS;
            goto Exit;
        }

        /* Initialize memRecInternal attributes with default values */
        for (memRecIndex = 0; memRecIndex < numRecInternal; memRecIndex++) {
            memRecInternal[memRecIndex].alignment= BAM_MEM_DEFAULT_ALIGNMENT;  /* To match the alignment of vcop_malloc() */
            memRecInternal[memRecIndex].attrs.memAttrs = BAM_MEMATTRS_CONST;
            memRecInternal[memRecIndex].space= BAM_MEMSPACE_ANY_VCOPBUF;
        }

        /* Initialize memRecOutputDataBlock attributes with default values */
        for (memRecIndex = 0; memRecIndex < numRecOutputDataBlock; memRecIndex++) {
            memRecOutputDataBlock[memRecIndex].alignment= BAM_MEM_DEFAULT_ALIGNMENT; /* To match the alignment of vcop_malloc() */
            memRecOutputDataBlock[memRecIndex].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
            memRecOutputDataBlock[memRecIndex].space= BAM_MEMSPACE_ANY_VCOPBUF;
        }

        status = BAM_getNodeMemRec(graphDef, nodeIndex, (*nodeList)[kernelIndex].kernelArgs,
                memRecInternal, memRecOutputDataBlock, &numRecInternal, &numRecOutputDataBlock);

        /* In the case of DMA source nodes, the max number of memrecs listed in the kernel info can be larger than what is
           actually required. Upodate the node structure with the actual requirements
         */
        if((*nodeArr)[nodeIndex].kernelInfo.nodeType == BAM_NODE_SOURCE)
        {
            (*nodeArr)[nodeIndex].kernelInfo.numRecInternal       = numRecInternal;
            (*nodeArr)[nodeIndex].kernelInfo.numInputDataBlocks   = 0;
            (*nodeArr)[nodeIndex].kernelInfo.numOutputDataBlocks  = numRecOutputDataBlock;
        }
        else {
            if ((*nodeArr)[nodeIndex].kernelInfo.nodeType == BAM_NODE_SINK) {
                /* For sink node, the number of input data blocks originally supplied in nodeArr[nodeIndex].kernelInfo.numInputDataBlocks represent
                 * a worst case. The actual number of input data blocks can actually be deduced by inspecting the array nodeArr[nodeIndex].inDataBlockIndex
                 * and count the number of valid data block index until the an entry with value BAM_INVALID_INDEX is reached.
                 */
                for (j=0; j < MAX((*nodeArr)[nodeIndex].kernelInfo.numInputDataBlocks+1U, (uint8_t)BAM_MAX_NODE_INPUT_OUTPUT); j++) {
                    if ((*nodeArr)[nodeIndex].inDataBlockIndex[j]== BAM_INVALID_INDEX) {
                        break;
                    }
                }

                (*nodeArr)[nodeIndex].kernelInfo.numRecInternal       = numRecInternal;
                (*nodeArr)[nodeIndex].kernelInfo.numOutputDataBlocks  = 0;
                (*nodeArr)[nodeIndex].kernelInfo.numInputDataBlocks   = j;
            }
        }

        if ((status != BAM_S_SUCCESS) || (numRecInternal > (uint8_t)MAX_MEMRECORDS_PER_NODE))
        {
            status = BAM_E_INVALID_STATUS;
            PRINTF("BAM_getNodeMemRec() returned error = %d!!!", status);
            goto Exit;
        }
        else {
            ;
        }

        kernelHostDbArray= (const BAM_KernelHostDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelHostFuncDB);

        for (memRecIndex = 0; memRecIndex < numRecInternal; memRecIndex++)
        {
            /* If the user has passed its own memory records table (useSmartMemAlloc== false) then we ignore what the kernel's getMemRec has returned
             * otherwise we copy memRecInternal[.] into memTab[.]
             */
            if (createParams->useSmartMemAlloc== true) {
                memTab[curMemTab] = memRecInternal[memRecIndex];
#if 0
                /* If a kernel's getMemRec() function changed an internal memory record's attribute to scratch
                 * then make sure that space is set to BAM_MEMSPACE_ANY_VCOPBUF
                 */
                if (memTab[curMemTab].attrs.memAttrs== BAM_MEMATTRS_SCRATCH) {
                    memTab[curMemTab].space= BAM_MEMSPACE_ANY_VCOPBUF;
                }
#endif

                memTab[curMemTab].base = 0;
                memTab[curMemTab].ext = 0;

                memTab[curMemTab].attrs.nodeIndex = (*nodeList)[kernelIndex].nodeIndex;
                memTab[curMemTab].attrs.memType = BAM_MEMTYPE_NODEMEM_INTERNAL;
                memTab[curMemTab].name= (*kernelHostDbArray)[(*nodeArr)[nodeIndex].kernelInfo.kernelId].name;
            }
            curMemTab++;

        }

        for (memRecIndex = 0; memRecIndex < numRecOutputDataBlock; memRecIndex++)
        {
            /* If the user has passed its own memory records table (useSmartMemAlloc== false) then we ignore what the kernel's getMemRec has returned
             * otherwise we copy memRecOutputDataBlock[.] into memTab[.]
             */
            if (createParams->useSmartMemAlloc== true) {
                memTab[curMemTab] = memRecOutputDataBlock[memRecIndex];

                memTab[curMemTab].base = 0;
                memTab[curMemTab].ext = 0;

                memTab[curMemTab].attrs.nodeIndex = (*nodeList)[kernelIndex].nodeIndex;
                memTab[curMemTab].attrs.memType = BAM_MEMTYPE_NODEMEM_OUTPUT;
                memTab[curMemTab].name= (*kernelHostDbArray)[(*nodeArr)[nodeIndex].kernelInfo.kernelId].name;
            }
            curMemTab++;
        }
    }
    /* RESET_MISRA("14.6")  -> Reset rule 14.6*/

    /* Replace numMemTabs with the actual number of memory records obtained, as DMA nodes may have less requirement than originally thought */
    graphDef->numMemTabs= curMemTab;

    Exit:
    return (status);
}

/* algInit */
static BAM_Status BAM_setMemRec(BAM_GraphHandle graphHandle, const BAM_MemRec memTab[], const BAM_NodeParams nodeList[], const BAM_InternalMemParams * intMemParams)
{

    BAM_Status status = BAM_S_SUCCESS;
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;

    uint8_t numRecInternal = 0;
    uint8_t numRecOutputDataBlock = 0;

    uint8_t nodeIndex = 0;
    BAM_NodeDef (*nodeArr)[];

    uint8_t kernelIndex = 0;
    uint8_t curMemTab = 0;

    curMemTab = 0;
    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

    for (kernelIndex = 0; kernelIndex < graphDef->totalNodes; kernelIndex++)
    {
        nodeIndex = nodeList[kernelIndex].nodeIndex;
        numRecOutputDataBlock =  (*nodeArr)[nodeIndex].kernelInfo.numOutputDataBlocks;
        numRecInternal = (*nodeArr)[nodeIndex].kernelInfo.numRecInternal;

        status = BAM_setNodeMemRec(graphDef, nodeIndex, &(memTab[curMemTab]),
                &(memTab[curMemTab + numRecInternal]), numRecInternal, numRecOutputDataBlock);

        if (status != BAM_S_SUCCESS)
        {
            PRINTF("BAM_setNodeMemRec() returned error!!!");
            goto Exit;
        }

        curMemTab += (numRecInternal + numRecOutputDataBlock);
    }

    /* final setup of the graph */
    status = BAM_finaliseGraph(graphDef, nodeList, intMemParams);

    if (status != BAM_S_SUCCESS)
    {
        PRINTF("BAM_finaliseGraph() returned error!!!");
        goto Exit;
    }

    Exit:
    return (status);
}

static BAM_Status BAM_getNodeMemRec(const BAM_GraphDef *graphDef, uint8_t nodeIndex, const void *kernelArgs, BAM_MemRec *memRecInternal,
        BAM_MemRec *memRecOutputDataBlock, uint8_t *numRecInternal, uint8_t *numRecOutputDataBlock)
{
    const BAM_KernelHostDBdef (*kernelHostDbArray)[];
    BAM_Status status = BAM_S_SUCCESS;
    BAM_NodeDef (*nodeArr)[];
    uint8_t kernelId = 0;

    /* Check for null params */
    if (NULL == graphDef)
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);
    kernelHostDbArray= (const BAM_KernelHostDBdef (*)[])(const void*)(graphDef->kernelDBDef->kernelHostFuncDB);

    /* Save connection to the input/output data block */
    kernelId = (*nodeArr)[nodeIndex].kernelInfo.kernelId;
    (*kernelHostDbArray)[kernelId].kernelHelperFunc->getKernelMemRec(kernelArgs, memRecInternal, memRecOutputDataBlock,
            numRecInternal, numRecOutputDataBlock);

    Exit:
    return (status);
}


static BAM_Status BAM_setNodeMemRec(const BAM_GraphDef *graphDef, uint8_t nodeIndex, const BAM_MemRec memRecInternal[],
        const BAM_MemRec memRecOutputDataBlock[], uint8_t numRecInternal, uint8_t numRecOutputDataBlock)
{
    BAM_Status status = BAM_S_SUCCESS;
    BAM_NodeDef (*nodeArr)[];
    BAM_DataBlockDef (*dataBlockArr)[];
    uint8_t i = 0;

    /* Check for null params */
    if (NULL == graphDef)
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    nodeArr = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

    /* Get mapped index of the data block */
    dataBlockArr = (BAM_DataBlockDef (*)[])(void*)(&graphDef->contextMem[graphDef->dataBlockDefArrOffset]);

    for (i = 0; i < numRecOutputDataBlock; i++)
    {
        if((memRecOutputDataBlock[i].base!=NULL) && (memRecOutputDataBlock[i].size!=0))
        {
            (*dataBlockArr)[(*nodeArr)[nodeIndex].outDataBlockIndex[i]].mem = memRecOutputDataBlock[i];
        }
    }

    for (i = 0; i < numRecInternal; i++)
    {
        (*nodeArr)[nodeIndex].internalBlock[i] = memRecInternal[i];
    }

    Exit:
    return (status);
}

static BAM_Status BAM_finaliseGraph(const BAM_GraphDef *graphDef, const BAM_NodeParams nodeList[], const BAM_InternalMemParams * intMemParams)
{
    BAM_Status status = BAM_S_SUCCESS;
    /*uint8_t *context= NULL;*/
    uint8_t (*context)[]; /* To be MISRA-C compliant, replaced original statement uint8_t *context= NULL; */
    /*
    uint8_t *pPrivContext= NULL;

    void **pInBlockArray= NULL;
    void **pOutBlockArray= NULL;
    void **pInternalBlockArray= NULL;
    void *pContextArgs= NULL;
     */

    void *(*pInBlockArray)[]; /* To be MISRA-C compliant, replaced original statement void **pInBlockArray= NULL; */
    void *(*pOutBlockArray)[]; /* To be MISRA-C compliant, replaced original statement void **pOutBlockArray= NULL; */
    void *(*pInternalBlockArray)[]; /* To be MISRA-C compliant, replaced original statement void **pInternalBlockArray= NULL; */
    uint8_t (*pContextArgs)[]; /* To be MISRA-C compliant, replaced original statement void *pContextArgs= NULL; */
    uint8_t (*pPrivContext)[]; /* To be MISRA-C compliant, replaced original statement void uint8_t *pPrivContext= NULL; */

    uint8_t kernelId = 0;
    /*BAM_NodeDef *node = 0;*/
    BAM_NodeDef (*node)[]; /* To be MISRA-C compliant, replaced original statement BAM_NodeDef *node = 0; */
    /*BAM_DataBlockDef *dataBlockArr = 0;*/
    BAM_DataBlockDef (*dataBlockArr)[]; /* To be MISRA-C compliant, replaced original statement BAM_DataBlockDef *dataBlockArr = 0; */
    uint8_t kernelIndex = 0, dataBlkIndex = 0, nodeIndex = 0, kernelIndexFound = 0;
    uint32_t sizePrivContext;

    const BAM_MemRec *memRecInputDataBlock[BAM_MAX_NODE_INPUT_OUTPUT];
    const BAM_MemRec *memRecOutputDataBlock[BAM_MAX_NODE_INPUT_OUTPUT];
    const BAM_MemRec *memRecInternalDataBlock[BAM_MAX_NODE_INTERNAL];

    const BAM_KernelHostDBdef (*kernelHostDbArray)[];

    uint32_t sourceNodeIndex= 0;
    uint32_t imgBufGap;
    uint32_t i;

    /* Initialize arrays memRecInputDataBlock, memRecOutputDataBlock, memRecInternalDataBlock to avoid the Klocwork issue UNINIT.STACK.ARRAY.MIGHT
     */
    for (i=0; i < BAM_MAX_NODE_INPUT_OUTPUT; i++) {
        memRecInputDataBlock[i]= NULL;
    }

    for (i=0; i < BAM_MAX_NODE_INPUT_OUTPUT; i++) {
        memRecOutputDataBlock[i]= NULL;
    }

    for (i=0; i < (uint32_t)BAM_MAX_NODE_INTERNAL; i++) {
        memRecInternalDataBlock[i]= NULL;
    }

    /* Check for null params */
    if (NULL == graphDef)
    {
        status = BAM_E_INVALID_PTR;
        goto Exit;
    }

    /* Add operation is allowed only if status is BAM_GRAPH_INITIALIZED */
    if (BAM_GRAPH_INITIALIZED != graphDef->status)
    {
        status = BAM_E_INVALID_STATUS;
        goto Exit;
    }

    /* Get mapped index of the data block */
    /*dataBlockArr = (BAM_DataBlockDef *) ((BAM_BytePtr) graphDef->contextMem + graphDef->dataBlockDefArrOffset);*/
    dataBlockArr= (BAM_DataBlockDef (*)[])(void*)(&graphDef->contextMem[graphDef->dataBlockDefArrOffset]);

    /*node = (BAM_NodeDef *) ((BAM_BytePtr) graphDef->contextMem + graphDef->nodeDefArrOffset);*/
    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        if ((*node)[nodeIndex].nodeType == BAM_NODE_SOURCE)
        {
            sourceNodeIndex = nodeIndex;
        }
    }

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++)
    {
        for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numInputDataBlocks; dataBlkIndex++)
        {
            memRecInputDataBlock[dataBlkIndex] = &((*dataBlockArr)[(*node)[nodeIndex].inDataBlockIndex[dataBlkIndex]].mem);
        }

        for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numOutputDataBlocks; dataBlkIndex++)
        {
            memRecOutputDataBlock[dataBlkIndex] = &((*dataBlockArr)[(*node)[nodeIndex].outDataBlockIndex[dataBlkIndex]].mem);
        }

        for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numRecInternal; dataBlkIndex++)
        {
            memRecInternalDataBlock[dataBlkIndex] = &((*node)[nodeIndex].internalBlock[dataBlkIndex]);
        }

        for (kernelIndex = 0; kernelIndex < graphDef->totalNodes; kernelIndex++)
        {
            if (nodeList[kernelIndex].nodeIndex== nodeIndex)
            {
                kernelIndexFound = kernelIndex;
                break;
            }
        }

        kernelId = (*node)[nodeIndex].kernelInfo.kernelId;

        /* In case the node is a sink node, if kernelContext is NULL then it means it has to be assigned the same context as the source node */
        if ((*node)[nodeIndex].nodeType == BAM_NODE_SINK)
        {
            if ( (*node)[nodeIndex].kernelContext == NULL)
            {
                (*node)[nodeIndex].kernelContext = (*node)[sourceNodeIndex].kernelContext;
            }
        }

        /* For a compute node, by default BAM copies all the pointers that the memory allocator produced into the corresponding placeholders in the
         * context structure.
         * Also BAM copies each kernel's arguments into the context.
         *
         * For a sink or source node, we don't do any copy because these nodes's context structures don't follow the same template as a compute node.
         */
        /*context= (uint8_t*)(node[nodeIndex].kernelContext);*/
        context= (uint8_t (*)[])((*node)[nodeIndex].kernelContext);

        pInternalBlockArray= (void* (*)[])(void*)&((*context)[0]);
        pInBlockArray= (void* (*)[])(void*)&((*pInternalBlockArray)[(*node)[nodeIndex].kernelInfo.numRecInternal]);
        pOutBlockArray= (void* (*)[])(void*)&((*pInBlockArray)[(*node)[nodeIndex].kernelInfo.numInputDataBlocks]);
        pContextArgs= (uint8_t (*)[])(void*)&((*pOutBlockArray)[(*node)[nodeIndex].kernelInfo.numOutputDataBlocks]);
        pPrivContext= (uint8_t (*)[])(void*)&((*pContextArgs)[(*node)[nodeIndex].kernelInfo.kernelArgSize]);
        /* CHECK_MISRA("-11.3")  -> Disable rule 11.3 */
        /* Cast between a pointer and an integral type */
        /* Deviation is allowed because this is the only way to get the distance between two pointers */
        sizePrivContext= ((*node)[nodeIndex]).kernelInfo.kernelContextSize - ((uintptr_t)&((*pPrivContext)[0]) - (uintptr_t)&((*context)[0]));
        /* RESET_MISRA("11.3")  -> Reset rule 11.3*/
        if ((*node)[nodeIndex].nodeType >= BAM_NODE_COMPUTE) {
            for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numRecInternal; dataBlkIndex++) {
                (*pInternalBlockArray)[dataBlkIndex]= memRecInternalDataBlock[dataBlkIndex]->base;
            }

            for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numInputDataBlocks; dataBlkIndex++) {
                (*pInBlockArray)[dataBlkIndex]= memRecInputDataBlock[dataBlkIndex]->base;
            }

            for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numOutputDataBlocks; dataBlkIndex++) {
                (*pOutBlockArray)[dataBlkIndex]= memRecOutputDataBlock[dataBlkIndex]->base;
            }

            /* Copy the arguments into the context */
            memcpy((*pContextArgs), nodeList[kernelIndexFound].kernelArgs, (*node)[nodeIndex].kernelInfo.kernelArgSize);

            /* If the compute node is entirely implemented on ARP32, then for any blocks allocated in IMGBUFA, we need to create a counterpart
             * of its pointer that reside in IMBUFB since ARP32 does not have any ALIAS view capability.
             * To enable this, we simply create a 2nd copy of the context, in which the pointers are modified to point in IMBUFB
             * Note that function BAM_fillKernelInfo() has previously extended the size of the context, so there is no risk of overwriting data.
             */
            if (((*node)[nodeIndex].kernelInfo.coreType== BAM_EVE_ARP32)
                ||((*node)[nodeIndex].kernelInfo.coreType== BAM_DSP_C66x) ||((*node)[nodeIndex].kernelInfo.coreType== BAM_DSP_C71x)) {

                uint32_t alignedSize;
                uint8_t blockInIbufFound= 0;
                /*
                void **pInBlockArray_b= NULL;
                void **pOutBlockArray_b= NULL;
                void **pInternalBlockArray_b= NULL;
                void *pContextArgs_b= NULL;
                uint8_t *pPrivContext_b= NULL;
                 */
                void *(*pInBlockArray_b)[]; /* To be MISRA-C compliant, replaced original statement void **pInBlockArray_b= NULL; */
                void *(*pOutBlockArray_b)[]; /* To be MISRA-C compliant, replaced original statement void **pOutBlockArray_b= NULL; */
                void *(*pInternalBlockArray_b)[]; /* To be MISRA-C compliant, replaced original statement void **pInternalBlockArray_b= NULL; */
                uint8_t (*pContextArgs_b)[]; /* To be MISRA-C compliant, replaced original statement void *pContextArgs_b= NULL; */
                uint8_t (*pPrivContext_b)[]; /* To be MISRA-C compliant, replaced original statement void uint8_t *pPrivContext_b= NULL; */
                uint8_t (*pImBuf)[];

                alignedSize= BAM_ALIGN_WORD((*node)[nodeIndex].kernelInfo.kernelContextSize)/(sizeof(void*));
                pInternalBlockArray_b= (void* (*)[])(void*)&((*pInternalBlockArray)[alignedSize]);
                pInBlockArray_b= (void* (*)[])(void*)&((*pInBlockArray)[alignedSize]);
                pOutBlockArray_b= (void* (*)[])(void*)&((*pOutBlockArray)[alignedSize]);
                pContextArgs_b= (uint8_t (*)[])(void*)&((*pContextArgs)[(alignedSize*(sizeof(void*)))]);
                pPrivContext_b= (uint8_t (*)[])(void*)&((*pPrivContext)[(alignedSize*(sizeof(void*)))]);

#ifdef CORE_DSP
                imgBufGap= intMemParams->dataIoMemSize/2;
#else
                imgBufGap= BAM_IMGBUF_GAP;
#endif
                for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numRecInternal; dataBlkIndex++) {
#if (defined(HOST_EMULATION) && defined(CORE_EVE))
                    (*pInternalBlockArray_b)[dataBlkIndex]= (*pInternalBlockArray)[dataBlkIndex];
#else
                    if (memRecInternalDataBlock[dataBlkIndex]->space < BAM_MEMSPACE_WBUF) {
                        blockInIbufFound= 1U;
                        /*pInternalBlockArray[dataBlkIndex]=  (void*)(((uint32_t)pInternalBlockArray[dataBlkIndex] & 0xfff0ffffU) | (uint32_t)ibufla);
                        pInternalBlockArray_b[dataBlkIndex]=  (void*)(((uint32_t)pInternalBlockArray[dataBlkIndex] & 0xfff0ffffU) | (uint32_t)ibuflb);*/
                        pImBuf= (uint8_t (*)[])(*pInternalBlockArray)[dataBlkIndex];
                        (*pInternalBlockArray_b)[dataBlkIndex]= (void*)&((*pImBuf)[imgBufGap]);
                    }   /* if the pointer is not imbuf, still need to fill pInternalBlockArray_b, otherwise it would contain garbage */
                    else {
                        (*pInternalBlockArray_b)[dataBlkIndex]= (*pInternalBlockArray)[dataBlkIndex];
                    }
#endif
                }

                for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numInputDataBlocks; dataBlkIndex++) {
#if (HOST_EMULATION && CORE_EVE)
                    (*pInBlockArray_b)[dataBlkIndex]= (*pInBlockArray)[dataBlkIndex];
#else
                    if (memRecInputDataBlock[dataBlkIndex]->space < BAM_MEMSPACE_WBUF) {
                        blockInIbufFound= 1U;
                        /*pInBlockArray[dataBlkIndex]= (void*)(((uint32_t)pInBlockArray[dataBlkIndex] & 0xfff0ffffU) | (uint32_t)ibufla);
                        pInBlockArray_b[dataBlkIndex]= (void*)(((uint32_t)pInBlockArray[dataBlkIndex] & 0xfff0ffffU) | (uint32_t)ibuflb);
                         */
                        pImBuf= (uint8_t (*)[])(*pInBlockArray)[dataBlkIndex];
                        (*pInBlockArray_b)[dataBlkIndex]= (void*)&((*pImBuf)[imgBufGap]);
                    }/* if the pointer is not imbuf, still need to fill pInternalBlockArray_b, otherwise it would contain garbage */
                    else {
                        (*pInBlockArray_b)[dataBlkIndex]= (*pInBlockArray)[dataBlkIndex];
                    }
#endif
                }

                for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numOutputDataBlocks; dataBlkIndex++) {
#if (HOST_EMULATION && CORE_EVE)
                    (*pOutBlockArray_b)[dataBlkIndex]= (*pOutBlockArray)[dataBlkIndex];
#else
                    if (memRecOutputDataBlock[dataBlkIndex]->space < BAM_MEMSPACE_WBUF) {
                        blockInIbufFound= 1U;
                        /*pOutBlockArray[dataBlkIndex]= (void*)(((uint32_t)pOutBlockArray[dataBlkIndex] & 0xfff0ffffU) | (uint32_t)ibufla);
                        pOutBlockArray_b[dataBlkIndex]= (void*)(((uint32_t)pOutBlockArray[dataBlkIndex] & 0xfff0ffffU) | (uint32_t)ibuflb);
                         */
                        pImBuf= (uint8_t (*)[])(*pOutBlockArray)[dataBlkIndex];
                        (*pOutBlockArray_b)[dataBlkIndex]= (void*)&((*pImBuf)[imgBufGap]);
                    }/* if the pointer is not imbuf, still need to fill pInternalBlockArray_b, otherwise it would contain garbage */
                    else {
                        (*pOutBlockArray_b)[dataBlkIndex]= (*pOutBlockArray)[dataBlkIndex];
                    }
#endif
                }
                /* If any of the memory blocks were in image buffers then we complete the dupplication of the context
                 * otherwise we should undo what we did as the node doesn't use any image buffer and thus creating
                 * a coutner part in image buffer B was unnecessary. However we choose not to spend any more cycles to undo things, instead
                 * we change the coreType of the node to BAM_EVE so that BAM_execute() will execute this node in parallel to the sink & source nodes
                 * and vcop compute nodes. This means, that it will run in parallel with EDMA or VCOP and not wait for completion for either one.
                 * This is not the case for BAM_EVE_ARP32 node, in which we assume image buffers are a shared resource with EDMA and vcop.
                 * We should have exposed two types: BAM_EVE_ARP32_IBUF and BAM_EVE_ARP32_DMEM  but in order to simplify interface
                 * we just use BAM_EVE_ARP32 and let BAM recategorize the node using the generic codeType BAM_EVE.
                 */
                if (blockInIbufFound== 1U) {
                    memcpy(*pContextArgs_b, nodeList[kernelIndexFound].kernelArgs, (*node)[nodeIndex].kernelInfo.kernelArgSize);
                    if (sizePrivContext) {
                        memcpy(*pPrivContext_b, *pPrivContext, sizePrivContext);
                    }
                }
                else {
                    (*node)[nodeIndex].kernelInfo.coreType= BAM_EVE; /* could be set to BAM_EVE_VCOP also */
                }
            }
        }

        /* In case setMemRec is set to non-NULL, the kernel may want to initialize some extra members in its context.
         * This is done by calling the kernel's setMemRec functions.
         */
        kernelHostDbArray= (const BAM_KernelHostDBdef (*)[])(void*)(graphDef->kernelDBDef->kernelHostFuncDB);

        if ((*kernelHostDbArray)[kernelId].kernelHelperFunc->setKernelMemRec != NULL) {

                status= (*kernelHostDbArray)[kernelId].kernelHelperFunc->setKernelMemRec((const BAM_MemRec **)memRecInternalDataBlock, (const BAM_MemRec **)memRecInputDataBlock,
                        (const BAM_MemRec **)memRecOutputDataBlock, (*node)[nodeIndex].kernelInfo.numRecInternal, (*node)[nodeIndex].kernelInfo.numInputDataBlocks,
                    (*node)[nodeIndex].kernelInfo.numOutputDataBlocks, (*node)[nodeIndex].kernelContext, nodeList[kernelIndexFound].kernelArgs);

            if (status!= BAM_S_SUCCESS) {
                goto Exit;
            }
        }

    }

    Exit:
    return (status);
}

BAM_Status BAM_optimizeGraph(BAM_GraphHandle graphHandle, BAM_CreateGraphParams *createGraphParams) {
    /* This function optimize the graph by maximizing the processing block width and block height while all the memory allocations remain succesful.
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
    int32_t tempBlockWidth=0, tempBlockHeight=0;
    BAM_BlockDimParams *blockDimParams= &createGraphParams->blockDimParams;
    BAM_Status status = BAM_S_SUCCESS;

    uint32_t bestBlockWidthFound= (uint32_t)false;
    uint32_t bestBlockHeightFound= (uint32_t)false;

    /* Before searching for the best block width, see if we need to readjust the block height to be divisor of the blockDimParams->blockHeightDivisorOf
     * If we don't do that and enter the loop while (bestBlockWidthFound== (uint32_t)false), then in the first call to createGraphParams->initKernelsArgsFunc()
     * we might pass an invalid block height that is not divisor of blockDimParams->blockHeightDivisorOf if the top application
     * didn't take care of initializing blockDimParams->blockHeight correctly
     */
    /* If (blockDimParams->blockHeightDivisorOf !=0),  need to do some additional adjustment to make blockHeight divisor of blockDimParams->blockHeightDivisorOf,
     * which is usually the processing ROI's height. This is because currently the EDMA can only fetch a number of blocks that is exact divisor
     * of the ROI's width or height.
     */
    if (blockDimParams->blockHeightDivisorOf != 0) {
        tempBlockHeight= blockDimParams->blockHeight;
        while (((blockDimParams->blockHeightDivisorOf % blockDimParams->blockHeight) != 0) && (blockDimParams->blockHeight > blockDimParams->blockHeightStep)) {
            blockDimParams->blockHeight-=blockDimParams->blockHeightStep;
        }

        /* Return error if the resulting blockHeight is too small, meaning that the divisor constraint could not be met */
        if (blockDimParams->blockHeight < blockDimParams->blockHeightStep) {
            status= BAM_E_BLOCK_DIM_NOT_FOUND;
            goto Exit;
        }
    }

    /* If the blockWidthStep is set to 0 then no need to scan the block width for the optimal value */
    if (blockDimParams->blockWidthStep== 0) {
        bestBlockWidthFound= (uint32_t)true;
    }

    /* CHECK_MISRA("-14.6")  -> Disable rule 14.6 */
    /* Iteration statement has more than one break or goto for loop termination */
    /* Deviation is allowed because all the GOTOs point to a single exit point */
    while (bestBlockWidthFound== (uint32_t)false)  {

        /* If (blockDimParams->blockWidthDivisorOf !=0), need to do some additional adjustment to make it divisor of blockDimParams->blockWidthDivisorOf,
         * which is usually the processing ROI's width. 
         * The way if works is that we decrement blockWidth by blockWidthStep as long as it is not a divisor of blockWidthDivisorOf
         */
        if (blockDimParams->blockWidthDivisorOf != 0) {
            tempBlockWidth= blockDimParams->blockWidth;
            while (((blockDimParams->blockWidthDivisorOf % blockDimParams->blockWidth)!= 0) && (blockDimParams->blockWidth > blockDimParams->blockWidthStep)) {
                blockDimParams->blockWidth-=blockDimParams->blockWidthStep;
            }

            /* Return error if the resulting blockWidth is too small, meaning that the divisor constraint could not be met */
            if (blockDimParams->blockWidth < blockDimParams->blockWidthStep) {
                status= BAM_E_BLOCK_DIM_NOT_FOUND;
                goto Exit;
            }
        }

        status= createGraphParams->initKernelsArgsFunc(createGraphParams->initKernelsArgsParams, blockDimParams);

        if (status != BAM_S_SUCCESS) {
            goto Exit;
        }

        if (blockDimParams->blockWidthDivisorOf != 0) {
            blockDimParams->blockWidth= tempBlockWidth;
        }

        status= BAM_updateNodes(graphHandle, createGraphParams, false);

        if ((status== BAM_E_BLOCK_DIM_TOO_BIG) || (blockDimParams->blockWidth > blockDimParams->blockWidthMax)) {
            bestBlockWidthFound= (uint32_t)true;
            blockDimParams->blockWidth-= blockDimParams->blockWidthStep; /* Rewind to previous working value */
            if (blockDimParams->blockWidthDivisorOf != 0) {
                while (((blockDimParams->blockWidthDivisorOf % blockDimParams->blockWidth) != 0) && (blockDimParams->blockWidth > blockDimParams->blockWidthStep)) {
                    blockDimParams->blockWidth-=blockDimParams->blockWidthStep;
                }
            }
        }
        else if (status== BAM_S_SUCCESS)  {
            blockDimParams->blockWidth+= blockDimParams->blockWidthStep; /* It worked so take it a little step further ... */
        }
        else {
            goto Exit;
        }

    }

    /* If the blockHeightStep is set to 0 then no need to scan the block height for the optimal value */
    if (blockDimParams->blockHeightStep== 0) {
        bestBlockHeightFound= (uint32_t)true;
    }

    while (bestBlockHeightFound== (uint32_t)false)  {

        /* If (blockDimParams->blockHeightDivisorOf !=0),  need to do some additional adjustment to make blockHeight divisor of blockDimParams->blockHeightDivisorOf,
         * which is usually the processing ROI's height.
         */
        if (blockDimParams->blockHeightDivisorOf != 0) {
            tempBlockHeight= blockDimParams->blockHeight;
            while (((blockDimParams->blockHeightDivisorOf % blockDimParams->blockHeight) != 0) && (blockDimParams->blockHeight > blockDimParams->blockHeightStep)) {
                blockDimParams->blockHeight-=blockDimParams->blockHeightStep;
            }

            /* Return error if the resulting blockHeight is too small, meaning that the divisor constraint could not be met */
            if (blockDimParams->blockHeight < blockDimParams->blockHeightStep) {
                status= BAM_E_BLOCK_DIM_NOT_FOUND;
                goto Exit;
            }
        }

        status= createGraphParams->initKernelsArgsFunc(createGraphParams->initKernelsArgsParams, blockDimParams);
        if (status != BAM_S_SUCCESS) {
            goto Exit;
        }

        if (blockDimParams->blockHeightDivisorOf != 0) {
            blockDimParams->blockHeight= tempBlockHeight;
        }

        status= BAM_updateNodes(graphHandle, createGraphParams, false);

        if ((status== BAM_E_BLOCK_DIM_TOO_BIG) || (blockDimParams->blockHeight > blockDimParams->blockHeightMax)) {
            bestBlockHeightFound= (uint32_t)true;
            blockDimParams->blockHeight-= blockDimParams->blockHeightStep; /* Rewind to previous working value */
            if (blockDimParams->blockHeightDivisorOf != 0) {
                while (((blockDimParams->blockHeightDivisorOf % blockDimParams->blockHeight)!=0) && (blockDimParams->blockHeight > blockDimParams->blockHeightStep)) {
                    blockDimParams->blockHeight-=blockDimParams->blockHeightStep;
                }
            }
        }
        else if (status== BAM_S_SUCCESS) {
            blockDimParams->blockHeight+= blockDimParams->blockHeightStep; /* It worked so take it a little step further ... */
        }
        else {
            goto Exit;
        }

    }
    /* RESET_MISRA("14.6")  -> Reset rule 14.6*/

    /* Set kernel's arguments to the best blockWidth and blockHeight */
    status= createGraphParams->initKernelsArgsFunc(createGraphParams->initKernelsArgsParams, blockDimParams);
    if (status != BAM_S_SUCCESS) {
        goto Exit;
    }

    /* Need to call BAM_updateNodes() for the last time as node's kernel arguments have changed */
    status= BAM_updateNodes(graphHandle, createGraphParams, (uint32_t)true);
    if (status != BAM_S_SUCCESS) {
        goto Exit;
    }

    Exit:
    return (status);
}

int32_t BAM_copyIntMemRec2ExtMem(BAM_GraphHandle graphHandle) {
    int32_t status = BAM_S_SUCCESS;

    BAM_NodeDef (*node)[];
    uint8_t dataBlkIndex = 0, nodeIndex = 0;
    BAM_MemRec *memRecToBeSaved = 0;

    /* get the restored graph handle */
    BAM_GraphDef *graphDef = (BAM_GraphDef *)graphHandle;

    node = (BAM_NodeDef (*)[])(void*)(&graphDef->contextMem[graphDef->nodeDefArrOffset]);

    for (nodeIndex = 0; nodeIndex < graphDef->totalNodes; nodeIndex++) {
        /* Save internal data blocks that are persistent*/
        for (dataBlkIndex = 0; dataBlkIndex < (*node)[nodeIndex].kernelInfo.numRecInternal; dataBlkIndex++) {
            memRecToBeSaved = &((*node)[nodeIndex].internalBlock[dataBlkIndex]);

            if((memRecToBeSaved->size != 0) && (memRecToBeSaved->base !=NULL) && (memRecToBeSaved->ext != NULL) &&
                    (memRecToBeSaved->attrs.memAttrs != BAM_MEMATTRS_CONST) && (memRecToBeSaved->attrs.memAttrs != BAM_MEMATTRS_SCRATCH)) {
                memcpy(memRecToBeSaved->ext, memRecToBeSaved->base, memRecToBeSaved->size);
            }
        }
    }

    return status;
}


int32_t BAM_getMemPacket(BAM_Packet **packet, VCOP_MEMHEAP space, int32_t alignment, uint32_t size) {

    int32_t status = BAM_S_SUCCESS;

    *packet= bam_getMemPacket(space, alignment, size);

    if (*packet== NULL) {
        status= BAM_E_BLOCK_DIM_TOO_BIG;
#ifdef DEBUG
        PRINTF("BAM_autoAllocMemRec() failed to allocate %d bytes in memspace #%d!!!\n", size, space);
#endif
        goto Exit;
    }
    else if (*packet== LIMIT) {
        status= BAM_E_OUT_OF_MEMPACKETS;
#ifdef DEBUG
        PRINTF("BAM_autoAllocMemRec() not enough BAM_packets, increase BAM_NUM_BAM_Packet in file bam_mempkt.h and recompile !!!\n");
#endif
        goto Exit;
    }
    else {
#ifdef DEBUG_BAM_MALLOC
        void *ptr= NULL;
        ptr =  vcop_malloc(space, size);
        if (*packet != NULL) {
            if (ptr != (*packet)->ptr) {
                PRINTF("bam_malloc error, bam ptr= 0x%x, vcop ptr= 0x%x\n", (*packet)->ptr, ptr);
            }
        }
        else {
            if (ptr != NULL) {
                PRINTF("bam_malloc error, bam packet= 0x%x, vcop ptr= 0x%x\n", NULL, ptr);
            }
        }
#endif
        /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
        /* GOTO is used at error check to jump to end of function, to exit.   */
        goto Exit;
        /* RESET_MISRA("14.4")  -> Reset rule 14.4  */
    }

    Exit:                   
    return status;
}

/* When this function is called ptrPacket is usually assigned to &memTab[tempMemTab].base */
void BAM_releaseMemPacket(void **memTabBase){

    BAM_Packet *packet;

    packet= (BAM_Packet*)(*memTabBase);
    bam_releaseMemPacket(packet);
    *memTabBase= packet->ptr; /* Here we set memTab[tempMemTab].base= packet->ptr */

#ifdef DEBUG_BAM_MALLOC
    vcop_free(packet->ptr);
#endif

}

void BAM_releaseMemPacketForOutput(void* memTabExt[], void **memTabBase){

    BAM_Packet *packet;

    packet= (BAM_Packet*)memTabExt[0];
    bam_releaseMemPacket((BAM_Packet*)packet);
    *memTabBase= packet->ptr; /* Here we set memTab[tempMemTab].base= packet->ptr */

#ifdef DEBUG_BAM_MALLOC
    vcop_free(packet->ptr);
#endif

}

/* RESET_MISRA("10.5")  -> Reset rule 10.5*/

