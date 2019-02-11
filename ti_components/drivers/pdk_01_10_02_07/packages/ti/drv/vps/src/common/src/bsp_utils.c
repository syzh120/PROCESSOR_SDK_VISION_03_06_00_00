/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file bsp_utils.c
 *
 *  \brief Utility functions implementation file.
 *  This file defines the helper functions like create, add and remove nodes
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <bsp_commonPriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static BspUtils_Node *dutilsLinkCircularPri(BspUtils_Node *headNode,
                                            BspUtils_Node *node,
                                            void          *data,
                                            UInt32         priority);
static Int32 dutilsLinkDoublePri(BspUtilsLinkListObj *llobj,
                                 BspUtils_Node       *node,
                                 void                *data,
                                 UInt32               priority,
                                 UInt32               linkUniqePriNodes);
static BspUtils_Node *dutilsUnLinkCircularPri(BspUtils_Node *headNode,
                                              BspUtils_Node *node);
static void dutilsUnLinkDoublePri(BspUtilsLinkListObj *llobj,
                                  BspUtils_Node       *node);
static BspUtils_Node *dutilsUnLinkDouble(BspUtilsLinkListObj *llobj,
                                         BspUtils_NodDir      dir,
                                         const BspUtils_Node *nodeToBeRem);
static BspUtils_Node *dutilsLinkDouble(BspUtilsLinkListObj *llobj,
                                       BspUtils_Node       *node,
                                       void                *data,
                                       BspUtils_NodDir      dir);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  BspUtils_init
 *  \brief Initializes the Util objects and create pool semaphore
 *
 *  \returns                Returns 0 on success else returns error value
 */
Int32 BspUtils_init(void)
{
    return (BSP_SOK);
}

/**
 *  BspUtils_deInit
 *  \brief De-Initializes the Util objects by removing pool semaphore
 *
 *  \param arg              Not used currently. Meant for future purpose
 *
 *  \return                 Returns 0 on success else returns error value
 */
Int32 BspUtils_deInit(Ptr arg)
{
    return (BSP_SOK);
}

/**
 *  BspUtils_memset
 *  \brief Sets the memory with the given value. Access memory as byte.
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer
 *  \param ch               Byte value to fill with
 *  \param byteCount        Number of bytes to fill
 *
 *  \return                 The destination memory pointer
 */
void *BspUtils_memset(Ptr mem, UInt8 ch, UInt32 byteCount)
{
    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != mem));

    return memset(mem, (Int32) ch, byteCount);
}

/**
 *  BspUtils_memsetw
 *  \brief Sets the memory with the given value. Access memory as word.
 *  Hence memory pointer should be aligned to 4 byte boundary
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer
 *  \param word             Word value to fill with
 *  \param wordCount        Number of words to fill
 *
 *  \return                 The destination memory pointer
 */
void *BspUtils_memsetw(Ptr mem, UInt32 word, UInt32 wordCount)
{
    UInt32  count;
    UInt32 *memPtr = NULL;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != mem));

    memPtr = (UInt32 *) mem;
    for (count = 0; count < wordCount; count++)
    {
        memPtr[count] = word;
    }

    return (mem);
}

/**
 *  BspUtils_memcpy
 *  \brief Copies source memory into destination memory. Access memory as byte.
 *  Returns the destination memory pointer.
 *
 *  \param dest             Destination memory pointer
 *  \param src              Source memory pointer
 *  \param byteCount        Number of bytes to copy
 *
 *  \return                 The destination memory pointer
 */
void *BspUtils_memcpy(Ptr dest, const void *src, UInt32 byteCount)
{
    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != dest));
    GT_assert(BspUtilsTrace, (NULL != src));

    return memcpy(dest, src, byteCount);
}

/**
 *  BspUtils_memcmp
 *  \brief Compare memory block 1 with memory block 2. Access memory as byte.
 *  Returns 0 if two memories are  identical.
 *
 *  \param mem1             memory block 1
 *  \param mem2              memory block 2
 *  \param byteCount        Number of bytes to compare
 *
 *  \return                 0 if two memory are identical other return 1
 */
Int32 BspUtils_memcmp(const void *mem1, const void *mem2, UInt32 byteCount)
{
    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != mem1));
    GT_assert(BspUtilsTrace, (NULL != mem2));

    return memcmp(mem1, mem2, byteCount);
}

/**
 *  BspUtils_constructLinkList
 *  \brief Constructs a link list object with the provided properties.
 *
 *  \param llobj pointer to object of type BspUtilsLinkListObj
 *  \param listType         List type - circular/double link list.
 *  \param addMode          Node addition mode - Top/Bottom/Priority based.
 *
 *  \return                 Returns BSP_SOK on success else returns error
 *                          value.
 */
Int32 BspUtils_constructLinkList(BspUtilsLinkListObj  *llobj,
                                 BspUtils_LinkListType listType,
                                 BspUtils_LinkAddMode  addMode)
{
    Int32 retVal = BSP_SOK;
    if ((BSPUTILS_LLT_CIRCULAR == listType) &&
        (BSPUTILS_LAM_PRIORITY != addMode))
    {
        GT_0trace(BspUtilsTrace, GT_DEBUG,
                  "Non-Priority circular link list not Supported\r\n");
        retVal = BSP_EBADARGS;
    }
    else
    {
        GT_assert(BspUtilsTrace, (NULL != llobj));
        /* Initialize the variables */
        llobj->listType    = listType;
        llobj->addMode     = addMode;
        llobj->headNode    = NULL;
        llobj->tailNode    = NULL;
        llobj->numElements = 0U;
        llobj->priorityCnt = 0;
    }

    return retVal;
}

/**
 *  BspUtils_destructLinkList
 *  \brief Destructs a link list object.
 *
 *  \param llobj pointer to object of type BspUtilsLinkListObj
 *
 *  \return                 Returns BSP_SOK on success else returns error value.
 */
Int32 BspUtils_destructLinkList(BspUtilsLinkListObj *llobj)
{
    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != llobj));
    GT_assert(BspUtilsTrace, (NULL == llobj->headNode));
    GT_assert(BspUtilsTrace, (NULL == llobj->tailNode));

    /* Free link list object */
    BspUtils_memset(llobj, 0, sizeof (BspUtilsLinkListObj));

    return (BSP_SOK);
}

/**
 *  BspUtils_unLinkAllNodes
 *  \brief Releases all nodes without modifying any of the property.
 *         CAUTION - Memory is NOT de-allocated, its the responsibility of the
 *                   caller to ensure de-allocation of memory.
 *
 *  \param handle           Link list handle.
 *
 *  \return                 Returns 0 on success else returns error value.
 */
Int32 BspUtils_unLinkAllNodes(BspUtils_Handle handle)
{
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj              = (BspUtilsLinkListObj *) handle;
    llobj->headNode    = NULL;
    llobj->tailNode    = NULL;
    llobj->numElements = 0U;
    llobj->priorityCnt = 0;

    return (0);
}

/**
 *  BspUtils_linkNodePri
 *  \brief Links a node to the linked list according to the list type
 *  The memory to the node object should be allocated by the caller. This
 *  is used for link list with priority.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param priority         Priority of the node used for priority based
 *                          addition of nodes. Priority is in descending order
 *                          the value. So 0 is the highest priority and is
 *                          added to the top of the node.
 *                          Nodes with the same priority are always added to
 *                          the bottom of the existing nodes with same
 *                          priority.
 *                          For non-priority based modes, this parameter
 *                          is ignored and could be set to 0.
 */
void BspUtils_linkNodePri(BspUtils_Handle handle,
                          BspUtils_Node  *node,
                          UInt32          priority)
{
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));
    GT_assert(BspUtilsTrace, (NULL != node));

    llobj = (BspUtilsLinkListObj *) handle;

    if (BSPUTILS_LLT_CIRCULAR == llobj->listType)
    {
        llobj->headNode = dutilsLinkCircularPri(
            llobj->headNode,
            node,
            node->data,
            priority);
    }
    else if (BSPUTILS_LLT_DOUBLE == llobj->listType)
    {
        dutilsLinkDoublePri(llobj, node, node->data, priority, (UInt32) FALSE);
    }
    else
    {
        GT_assert(BspUtilsTrace, FALSE);
    }

    return;
}

/**
 *  BspUtils_linkUniqePriNode
 *  \brief Very similar to BspUtils_linkNodePri, except that on equal priority
 *          nodes will not be inserted. An error (BSP_EBADARGS) would be
 *          returned.
 *          Applicable for double linked list only.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param priority         Priority of the node used for priority based
 *                          addition of nodes. Priority is in descending order
 *                          the value. So 0 is the highest priority and is
 *                          added to the top of the node.
 *                          Nodes with the same priority are always added to
 *                          the bottom of the existing nodes with same
 *                          priority.
 *                          For non-priority based modes, this parameter
 *                          is ignored and could be set to 0.
 */
Int32 BspUtils_linkUniqePriNode(BspUtils_Handle handle,
                                BspUtils_Node  *node,
                                UInt32          priority)
{
    BspUtilsLinkListObj *llobj;
    Int32 rtnValue = BSP_SOK;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));
    GT_assert(BspUtilsTrace, (NULL != node));

    llobj = (BspUtilsLinkListObj *) handle;

    if (BSPUTILS_LAM_PRIORITY != llobj->addMode)
    {
        if (BSPUTILS_LAM_TOP == llobj->addMode)
        {
            llobj->priorityCnt--;
        }
        else if (BSPUTILS_LAM_BOTTOM == llobj->addMode)
        {
            llobj->priorityCnt++;
        }
        else
        {
            GT_assert(BspUtilsTrace, FALSE);
        }
        priority = llobj->priorityCnt;
    }

    if (BSPUTILS_LLT_CIRCULAR == llobj->listType)
    {
        llobj->headNode = dutilsLinkCircularPri(
            llobj->headNode,
            node,
            node->data,
            priority);
    }
    else if (BSPUTILS_LLT_DOUBLE == llobj->listType)
    {
        rtnValue = dutilsLinkDoublePri(
            llobj,
            node,
            node->data,
            priority,
            (UInt32) TRUE);
        if (rtnValue == BSP_SOK)
        {
            llobj->numElements++;
        }
    }
    else
    {
        GT_assert(BspUtilsTrace, FALSE);
    }

    return (rtnValue);
}

/**
 *  BspUtils_unLinkNodePri
 *  \brief Unlinks the node from the list. Used for the Priority linklists.
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void BspUtils_unLinkNodePri(BspUtils_Handle handle, BspUtils_Node *node)
{
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));
    GT_assert(BspUtilsTrace, (NULL != node));

    llobj = (BspUtilsLinkListObj *) handle;
    if (BSPUTILS_LLT_CIRCULAR == llobj->listType)
    {
        llobj->headNode = dutilsUnLinkCircularPri(llobj->headNode, node);
    }
    else if (BSPUTILS_LLT_DOUBLE == llobj->listType)
    {
        dutilsUnLinkDoublePri(llobj, node);
    }
    else
    {
        GT_assert(BspUtilsTrace, FALSE);
    }

    return;
}

/**
 *  BspUtils_unLinkNode
 *  \brief Unlinks the node from the list. Used for Non-priority linked lists
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void BspUtils_unLinkNode(BspUtils_Handle handle, const BspUtils_Node *node)
{
    BspUtilsLinkListObj *llobj;
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_HEAD;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));
    GT_assert(BspUtilsTrace, (NULL != node));

    llobj = (BspUtilsLinkListObj *) handle;
    dutilsUnLinkDouble(llobj, dir, node);

    return;
}

/**
 *  BspUtils_linkNodeToTail
 *  \brief                  Link the node to the tail of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
void BspUtils_linkNodeToTail(BspUtils_Handle handle, BspUtils_Node *node)
{
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_TAIL;
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != node));
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    dutilsLinkDouble(llobj, node, node->data, dir);

    return;
}

/**
 *  BspUtils_linkNodeToHead
 *  \brief                  Link the node to the head of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
void BspUtils_linkNodeToHead(BspUtils_Handle handle, BspUtils_Node *node)
{
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_HEAD;
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != node));
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    dutilsLinkDouble(llobj, node, node->data, dir);

    return;
}

/**
 *  BspUtils_unLinkNodeFromHead
 *  \brief                  Returns the node from head. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
BspUtils_Node *BspUtils_unLinkNodeFromHead(BspUtils_Handle handle)
{
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_HEAD;
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    return (dutilsUnLinkDouble(llobj, dir, NULL));
}

/**
 *  BspUtils_unLinkNodeFromTail
 *  \brief                  Returns the node from tail. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
BspUtils_Node *BspUtils_unLinkNodeFromTail(BspUtils_Handle handle)
{
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_TAIL;
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    return (dutilsUnLinkDouble(llobj, dir, NULL));
}

/**
 *  BspUtils_getHeadNode
 *  \brief                  Returns the reference to the headNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
BspUtils_Node *BspUtils_getHeadNode(BspUtils_Handle handle)
{
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;

    return (llobj->headNode);
}

/**
 *  BspUtils_getTailNode
 *  \brief                  Returns the reference to the TailNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 *
 */
BspUtils_Node *BspUtils_getTailNode(BspUtils_Handle handle)
{
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    return (llobj->tailNode);
}

/**
 *  BspUtils_isListEmpty
 *  \brief Checks whether a list is empty or not.
 *
 *  \param handle           List handle.
 *
 *  \return                 TRUE if List is empty else returns FALSE.
 */
UInt32 BspUtils_isListEmpty(BspUtils_Handle handle)
{
    UInt32 isEmpty = FALSE;
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    if (NULL == llobj->headNode)
    {
        isEmpty = (UInt32) TRUE;
    }

    return (isEmpty);
}

/**
 *  BspUtils_getNumNodes
 *  \brief Returns the number of nodes present in a list.
 *
 *  \param handle           List handle.
 *
 *  \return                 Number of nodes present in a list.
 */
UInt32 BspUtils_getNumNodes(BspUtils_Handle handle)
{
    BspUtils_Node       *node = NULL;
    BspUtilsLinkListObj *llobj;
    UInt32 numNodes = 0U;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    if (BSPUTILS_LLT_CIRCULAR == llobj->listType)
    {
        node = llobj->headNode;
        while (NULL != node)
        {
            numNodes++;
            node = node->next;
            /* Not supposed to have NULL in circular list */
            GT_assert(BspUtilsTrace, (NULL != node));

            /* Check if we have come to the end of the list */
            if (node == llobj->headNode)
            {
                break;
            }
        }
    }
    else if (BSPUTILS_LLT_DOUBLE == llobj->listType)
    {
        node = llobj->headNode;
        while (NULL != node)
        {
            numNodes++;
            node = node->next;
        }
    }
    else
    {
        GT_assert(BspUtilsTrace, FALSE);
    }

    return (numNodes);
}

/**
 *  BspUtils_constructQ
 *  \brief Constructs a Queue object.
 *
 * \param llobj pointer to object of type BspUtilsLinkListObj
 *
 *  \return                 Returns BSP_SOK on success else returns error value.
 */
Int32 BspUtils_constructQ(BspUtilsLinkListObj *llobj)
{
    return BspUtils_constructLinkList(llobj, BSPUTILS_LLT_DOUBLE,
                                      BSPUTILS_LAM_BOTTOM);
}

/**
 *  BspUtils_destructQ
 *  \brief Destructs a Queue object.
 *
 * \param llobj pointer to object of type BspUtilsLinkListObj
 *
 *  \return                 Returns BSP_SOK on success else returns error value.
 */
Int32 BspUtils_destructQ(BspUtilsLinkListObj *llobj)
{
    return BspUtils_destructLinkList(llobj);
}

/**
 *  BspUtils_queue
 *  \brief Adds the data to the queue. Add the node to the tail of the queue.
 *
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void BspUtils_queue(BspUtils_QHandle handle,
                    BspUtils_QElem  *qElem,
                    Ptr              data)
{
    BspUtilsLinkListObj *llobj;
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_TAIL;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    dutilsLinkDouble(llobj, qElem, data, dir);

    return;
}

/**
 *  BspUtils_dequeue
 *  \brief Removes a element from the queue. Removes the element from the head
 *   of the queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the removed data pointer.
 */
void *BspUtils_dequeue(BspUtils_QHandle handle)
{
    BspUtils_Node       *node;
    void                *data = NULL;
    BspUtilsLinkListObj *llobj;
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_HEAD;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    node  = dutilsUnLinkDouble(llobj, dir, NULL);
    if (NULL != node)
    {
        data = node->data;
    }
    else
    {
        data = NULL;
    }

    return (data);
}

/**
 *  BspUtils_peakHead
 *  \brief Returns the reference of the first queued element.
 *
 *  This doesn't remove the element from the queue.
 *  If the queue is empty, then this returns NULL.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the reference of the first element.
 */
void *BspUtils_peakHead(BspUtils_QHandle handle)
{
    void *data = NULL;
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    if (llobj->headNode != NULL)
    {
        data = llobj->headNode->data;
    }

    return (data);
}

/**
 *  BspUtils_peakTail
 *  \brief Returns the reference of the last queued element.
 *
 *  This doesn't remove the element from the queue.
 *  If the queue is empty, then this returns NULL.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the reference of the last queued element.
 */
void *BspUtils_peakTail(BspUtils_QHandle handle)
{
    void *data = NULL;
    BspUtilsLinkListObj *llobj;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    if (llobj->tailNode != NULL)
    {
        data = llobj->tailNode->data;
    }

    return (data);
}

/**
 *  BspUtils_queueBack
 *  \brief Adds the data to start of the queue. Queue the data back to the
 *  head of the queue.
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void BspUtils_queueBack(BspUtils_QHandle handle,
                        BspUtils_QElem  *qElem,
                        void            *data)
{
    BspUtilsLinkListObj *llobj;
    BspUtils_NodDir      dir = BSPUTILS_NODE_DIR_HEAD;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    llobj = (BspUtilsLinkListObj *) handle;
    dutilsLinkDouble(llobj, qElem, data, dir);

    return;
}

/**
 *  BspUtils_isQEmpty
 *  \brief Checks whether a queue is empty or not.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 TRUE if queue is empty else returns FALSE.
 */
UInt32 BspUtils_isQEmpty(BspUtils_QHandle handle)
{
    return BspUtils_isListEmpty(handle);
}

/**
 *  BspUtils_getNumQElem
 *  \brief Returns the number of Queue Elements present in a Queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Number of Queue Elements present in a Queue.
 */
UInt32 BspUtils_getNumQElem(BspUtils_QHandle handle)
{
    return BspUtils_getNumNodes(handle);
}

/**
 *  dutilsLinkCircularPri
 *  \brief Links a node to a circular link list based on priority.
 *  For nodes with same priority, the new node will be added to the last.
 */
static BspUtils_Node *dutilsLinkCircularPri(BspUtils_Node *headNode,
                                            BspUtils_Node *node,
                                            void          *data,
                                            UInt32         priority)
{
    BspUtils_Node *curNode;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != node));

    node->data     = data;
    node->priority = priority;

    /* Check if this is the first node. */
    if (NULL != headNode)
    {
        /* Add to the list based on priority */
        curNode = headNode;
        do
        {
            /* Nodes with the same priority are always added to the bottom
             * of the existing nodes with same priority. */
            if (priority < curNode->priority)
            {
                if (curNode == headNode)
                {
                    /* Adding to the top of the list */
                    headNode = node;
                }
                break;
            }

            /* Move to next node */
            curNode = curNode->next;
            /* Not supposed to have NULL in circular list */
            GT_assert(BspUtilsTrace, (NULL != curNode));
        } while (curNode != headNode);
        /* Check if we have come to the end of the list */

        /* Add the node before the current node as we have traversed one
         * extra node. */
        node->next = curNode;
        node->prev = curNode->prev;

        /* Not supposed to have NULL in circular list */
        GT_assert(BspUtilsTrace, (NULL != curNode->prev));
        GT_assert(BspUtilsTrace, (NULL != curNode->prev->next));
        curNode->prev->next = node;
        curNode->prev       = node;
    }
    else
    {
        /* First node. Add to as head node */
        headNode   = node;
        node->next = node;
        node->prev = node;
    }

    return (headNode);
}

/**
 *  dutilsLinkDoublePri
 *  \brief Links a node to a double link list based on priority.
 *  For nodes with same priority, the new node will be added to the last.
 *
 *  ToDo - Remove multiple return statements - Have one exit point for the
 *         Function.
 */
static Int32 dutilsLinkDoublePri(BspUtilsLinkListObj *llobj,
                                 BspUtils_Node       *node,
                                 void                *data,
                                 UInt32               priority,
                                 UInt32               linkUniqePriNodes)
{
    Int32          retVal = BSP_SOK;
    BspUtils_Node *curNode, *prevNode = NULL;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != node));

    node->data     = data;
    node->priority = priority;

    /* Add to the list based on priority */
    curNode = llobj->headNode;
    while (NULL != curNode)
    {
        /* Nodes with the same priority are always added to the bottom
         * of the existing nodes with same priority. */
        if (priority < curNode->priority)
        {
            break;
        }

        /* Move to next node */
        prevNode = curNode;
        curNode  = curNode->next;
    }

    /* If unique priority check is enabled - check for uniqueness */
    if (linkUniqePriNodes == (UInt32) TRUE)
    {
        if (prevNode != NULL)
        {
            if (priority == prevNode->priority)
            {
                retVal = BSP_EBADARGS;
            }
        }
    }

    if (BSP_SOK == retVal)
    {
        /* Add the node between current and previous nodes */
        node->next = curNode;
        node->prev = prevNode;
        if (NULL != prevNode)
        {
            prevNode->next = node;
        }
        else
        {
            /* Adding to the top of the list */
            llobj->headNode = node;
        }

        if (NULL != curNode)
        {
            curNode->prev = node;
        }
        else
        {
            llobj->tailNode = node;
        }
        retVal = BSP_SOK;
    }

    return (retVal);
}

/**
 *  dutilsUnLinkCircularPri
 *  \brief Unlinks a node from a circular link list.
 */
static BspUtils_Node *dutilsUnLinkCircularPri(BspUtils_Node *headNode,
                                              BspUtils_Node *node)
{
    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != headNode));
    GT_assert(BspUtilsTrace, (NULL != node));

    /* Not supposed to have NULL in circular list */
    GT_assert(BspUtilsTrace, (NULL != node->next));
    GT_assert(BspUtilsTrace, (NULL != node->prev));

    /* Link the node's previous node to node's next node */
    node->prev->next = node->next;
    node->next->prev = node->prev;

    if (node == headNode)
    {
        /* Unlinking head node */
        if ((headNode == headNode->next) || (headNode == headNode->prev))
        {
            /* Unlinking last node */
            GT_assert(BspUtilsTrace,
                      ((headNode == headNode->next) &&
                       (headNode == headNode->prev)));
            headNode = NULL;
        }
        else
        {
            /* Make next node as head node */
            headNode = node->next;
        }
    }

    /* Reset node memory */
    node->next = NULL;
    node->prev = NULL;

    return (headNode);
}

/**
 *  dutilsUnLinkDoublePri
 *  \brief Unlinks a node from a double link list.
 */
static void dutilsUnLinkDoublePri(BspUtilsLinkListObj *llobj,
                                  BspUtils_Node       *node)
{
    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != llobj));
    GT_assert(BspUtilsTrace, (NULL != node));

    if (NULL == node->prev)
    {
        /* Removing head node */
        llobj->headNode = node->next;
    }
    else
    {
        /* Removing non-head node */
        node->prev->next = node->next;
    }

    if (NULL != node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        llobj->tailNode = NULL;
    }

    /* Reset node memory */
    node->next = NULL;
    node->prev = NULL;

    return;
}

/**
 *  dutilsUnLinkDouble
 *  \brief Unlinks a node from a double link list.
 */
static BspUtils_Node *dutilsUnLinkDouble(BspUtilsLinkListObj *llobj,
                                         BspUtils_NodDir      dir,
                                         const BspUtils_Node *nodeToBeRem)
{
    BspUtils_Node *node = NULL, *headNode, *tailNode, *listNode;
    UInt32         nodeCnt;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != llobj));

    if (NULL == nodeToBeRem)
    {
        if ((NULL == llobj->headNode) && (NULL == llobj->tailNode))
        {
            node = NULL;
        }
        /* Check for the last node in the list */
        else if ((NULL != llobj->headNode) &&
                 (NULL == llobj->headNode->next) &&
                 (NULL == llobj->headNode->prev))
        {
            node = llobj->headNode;
            llobj->tailNode = NULL;
            llobj->headNode = NULL;
        }
        else if ((NULL != llobj->headNode) &&
                 (NULL != llobj->tailNode) &&
                 (BSPUTILS_NODE_DIR_HEAD == dir))
        {
            /* Point headnode to the head of the list */
            headNode = llobj->headNode;
            /* headnode points to now next in the list */
            llobj->headNode = headNode->next;
            /* prev of the new headnode point to headNode of the list */
            if (NULL != llobj->headNode)
            {
                llobj->headNode->prev = NULL;
            }
            else
            {
                llobj->tailNode = NULL;
            }
            /* return the detached node */
            node = headNode;
        }
        else if ((NULL != llobj->headNode) &&
                 (NULL != llobj->tailNode) &&
                 (BSPUTILS_NODE_DIR_TAIL == dir))
        {
            /* point to the tail node. */
            tailNode = llobj->tailNode;
            /* tailnode of the list points to the previous node */
            llobj->tailNode = tailNode->prev;
            /* next node of the previous node points to the tail node of list */
            if (NULL != llobj->tailNode)
            {
                llobj->tailNode->next = NULL;
            }
            else
            {
                llobj->headNode = NULL;
            }
            /*  return the tail node */
            node = tailNode;
        }
        else
        {
            GT_assert(BspUtilsTrace, FALSE);
        }
    }
    else
    {
        listNode = llobj->headNode;
        for (nodeCnt = 0; nodeCnt < llobj->numElements; nodeCnt++)
        {
            if (listNode == nodeToBeRem)
            {
                /* Last node in the list */
                if ((llobj->headNode == listNode) &&
                    (llobj->tailNode == listNode))
                {
                    llobj->headNode = NULL;
                    llobj->tailNode = NULL;
                }
                else if (llobj->headNode == listNode)
                {
                    llobj->headNode       = listNode->next;
                    llobj->headNode->prev = NULL;
                }
                else if (llobj->tailNode == listNode)
                {
                    llobj->tailNode       = listNode->prev;
                    llobj->tailNode->next = NULL;
                }
                else
                {
                    listNode->prev->next = listNode->next;
                    listNode->next->prev = listNode->prev;
                }
                node = listNode;
                break;
            }
            listNode = listNode->next;
        }
    }
    if (NULL != node)
    {
        /* Reset node memory */
        node->next = NULL;
        node->prev = NULL;
        llobj->numElements--;
    }

    return (node);
}

/**
 *  BspUtils_getNumNodes
 *  \brief Returns the number of nodes present in a list.
 *
 *  \param handle           List handle.
 *
 *  \return                 Number of nodes present in a list.
 */
UInt32 BspUtils_getNodeCnt(BspUtils_Handle handle)
{
    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != handle));

    return (((BspUtilsLinkListObj *) handle)->numElements);
}

/**
 *  dutilsLinkDouble
 *  \brief Links a node to a double link list either at head of the list or
 *  at tail of the list.
 *
 *
 */
static BspUtils_Node *dutilsLinkDouble(BspUtilsLinkListObj *llobj,
                                       BspUtils_Node       *node,
                                       void                *data,
                                       BspUtils_NodDir      dir)
{
    BspUtils_Node *headNode, *tailNode = NULL;

    /* NULL pointer check */
    GT_assert(BspUtilsTrace, (NULL != node));
    GT_assert(BspUtilsTrace, (NULL != llobj));

    node->data = data;
    /* check for the first element in the list */
    if ((NULL == llobj->headNode) && (NULL == llobj->tailNode))
    {
        /* Add the first element in the list */
        /* head node points to new element */
        llobj->headNode = node;
        /* tail node also points to new element */
        llobj->tailNode = node;
        /* next of node points to tail */
        node->next = NULL;
        /* prev of node points to head */
        node->prev = NULL;
    }
    else if ((NULL != llobj->headNode) &&
             (NULL != llobj->tailNode) &&
             (BSPUTILS_NODE_DIR_HEAD == dir))
    {
        headNode = llobj->headNode;
        /* headNode now points to new node */
        llobj->headNode = node;
        /* previous of new node points to headNode */
        node->prev = NULL;
        /* next of new points to prev head node */
        node->next = headNode;
        /* prev of previous head node head points to new node */
        headNode->prev = node;
    }
    else if ((NULL != llobj->headNode) &&
             (NULL != llobj->tailNode) &&
             (BSPUTILS_NODE_DIR_TAIL == dir))
    {
        tailNode = llobj->tailNode;
        /* next of new node points to tail of list */
        node->next = NULL;
        /* tail of list points to new node */
        llobj->tailNode = node;
        /* next of previous tial node points to new tail node */
        tailNode->next = node;
        /* previous of new tail node points to previous tail node */
        node->prev = tailNode;
    }
    else
    {
        GT_assert(BspUtilsTrace, FALSE);
    }
    llobj->numElements++;
    return (node);
}
