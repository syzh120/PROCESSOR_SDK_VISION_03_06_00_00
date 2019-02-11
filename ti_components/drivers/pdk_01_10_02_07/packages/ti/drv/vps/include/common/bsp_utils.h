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
 *  \file bsp_utils.h
 *
 *  \brief BSP Utility functions header file
 *  This file declares the functions required to create, add and remove nodes.
 *  Also provides various memset functions.
 *
 */

#ifndef BSP_UTILS_H_
#define BSP_UTILS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< \brief Number of timestamp log entries. */
#define BSPUTILS_NUM_TIMESTAMP_LOG      (100U)

/**
 *  struct BspUtils_LinkListType
 *  \brief Enums for the type of link list to be created.
 */
typedef enum
{
    BSPUTILS_LLT_DOUBLE,
    /**< Double link list. */
    BSPUTILS_LLT_CIRCULAR
    /**< Circular link list using double link list. */
} BspUtils_LinkListType;

/**
 *  struct BspUtils_LinkAddMode
 *  \brief Enums for the different modes of adding a node to a link list.
 */
typedef enum
{
    BSPUTILS_LAM_TOP,
    /**< Add nodes to the top of the list. */
    BSPUTILS_LAM_BOTTOM,
    /**< Add nodes to the bottom of the list. */
    BSPUTILS_LAM_PRIORITY
    /**< Add nodes to the list based on ascending order of priority.
     *   Nodes with the same priority are always added to the bottom of the
     *   existing nodes with same priority. */
} BspUtils_LinkAddMode;

/**
 *  struct BspUtils_LinkAddMode
 *  \brief Enums for the different modes of adding a node to a link list.
 */
typedef enum
{
    BSPUTILS_NODE_DIR_HEAD,
    /**< Add nodes to the top of the list. */
    BSPUTILS_NODE_DIR_TAIL
    /**< Add nodes to the bottom of the list. */
} BspUtils_NodDir;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**< \brief Typedef for Node structure. */
typedef struct BspUtils_Node_t BspUtils_Node;

/**
 *  struct BspUtils_Node_t
 *  \brief Self referential structure for double link list.
 */
struct BspUtils_Node_t
{
    BspUtils_Node *next;
    /**< Pointer to the next node. */
    BspUtils_Node *prev;
    /**< Pointer to the previous node. */
    void          *data;
    /**< Node data pointer. */
    UInt32         priority;
    /**< Priority of the node. Used for priority based linked list. */
};

/**
 *  struct BspUtils_QElem
 *  \brief Typedef for Queue Node element.
 */
typedef BspUtils_Node BspUtils_QElem;

/**
 *  struct BspUtils_PoolParams
 *  \brief Create parameters for the fixed size pool.
 */
typedef struct
{
    void   *mem;
    /**< Pointer to the pool memory. */
    UInt32  numElem;
    /**< Number of elements in the pool. */
    UInt32  elemSize;
    /**< Size of each element in bytes. */
    UInt32 *flag;
    /**< Array of flag variable used by pool manager to indicate whether a pool
     *   element is allocated or not. The size of this array should be
     *   equal to the number of elements in this pool. */
    UInt32  numFreeElem;
    /**< Count to keep track of the number of free elements in the pool. */
} BspUtils_PoolParams;

/**
 *  struct BspUtils_TsPrfLog
 *  \brief Timestamp Performance log structure in BSP OSAL timestamp ticks.
 */
typedef struct
{
    UInt64 startTime;
    /**< Start time - updated in start function. */
    UInt64 total;
    /**< Total duration of all log entires.
     *   To get average divide by totalCnt. */
    UInt32 totalCnt;
    /**< Total number of log entires. */
    UInt64 min;
    /**< Minimum duration. */
    UInt64 max;
    /**< Maximum duration. */
    UInt32 prfLogIndex;
    /**< Current index. This will wrap around every BSPUTILS_NUM_TIMESTAMP_LOG
     *   count. */
    UInt64 prfLog[BSPUTILS_NUM_TIMESTAMP_LOG];
    /**< History of the past BSPUTILS_NUM_TIMESTAMP_LOG entires. */
} BspUtils_TsPrfLog;

/**
 *  struct BspUtilsLinkListObj
 *  \brief Structure to the link list object information.
 */
typedef struct
{
    BspUtils_LinkListType listType;
    /**< Type of linked list. */
    BspUtils_LinkAddMode  addMode;
    /**< Mode of adding a node to a link list. */
    BspUtils_Node        *headNode;
    /**< Head Node. */
    BspUtils_Node        *tailNode;
    /**< Tail Node Node. */
    UInt32                numElements;
    /**< Number of elements in the linked list. */
    UInt32                priorityCnt;
    /**< Priority count of the linked list. */
} BspUtilsLinkListObj;

/**
 *  struct BspUtils_Handle
 *  \brief Typedef for BSP Utils handle.
 */
typedef BspUtilsLinkListObj *BspUtils_Handle;

/**
 *  struct BspUtils_QHandle
 *  \brief Typedef for BSP Utils Queue Handle.
 */
typedef BspUtils_Handle BspUtils_QHandle;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  BspUtils_memset
 *  \brief Sets the memory with the given value. Access memory as byte.
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer.
 *  \param ch               Byte value to fill with.
 *  \param byteCount        Number of bytes to fill.
 *
 *  \return                 The destination memory pointer.
 */
void *BspUtils_memset(Ptr mem, UInt8 ch, UInt32 byteCount);

/**
 *  BspUtils_memsetw
 *  \brief Sets the memory with the given value. Access memory as word.
 *  Hence memory pointer should be aligned to 4 byte boundary
 *  Returns the memory pointer.
 *
 *  \param mem              Destination memory pointer.
 *  \param word             Word value to fill with.
 *  \param wordCount        Number of words to fill.
 *
 *  \return                 The destination memory pointer.
 */
void *BspUtils_memsetw(Ptr mem, UInt32 word, UInt32 wordCount);

/**
 *  BspUtils_memcpy
 *  \brief Copies source memory into destination memory. Access memory as byte.
 *  Returns the destination memory pointer.
 *
 *  \param dest             Destination memory pointer.
 *  \param src              Source memory pointer.
 *  \param byteCount        Number of bytes to copy.
 *
 *  \return                 The destination memory pointer.
 */
void *BspUtils_memcpy(Ptr dest, const void *src, UInt32 byteCount);

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
Int32 BspUtils_memcmp(const void *mem1, const void *mem2, UInt32 byteCount);

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
                                 BspUtils_LinkAddMode  addMode);

/**
 *  BspUtils_destructLinkList
 *  \brief Destructs a link list object.
 *
 *  \param llobj pointer to object of type BspUtilsLinkListObj
 *
 *  \return                 Returns BSP_SOK on success else returns error value.
 */
Int32 BspUtils_destructLinkList(BspUtilsLinkListObj *llobj);

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
                          UInt32          priority);

/**
 *  BspUtils_linkUniqePriNode
 *  \brief Very similar to BspUtils_linkNode, except that on equal priority
 *          nodes will not be inserted. An error (BSP_EBADARGS) would be
 *          returned.
 *          Applicable for double linked list only.
 *  ToDo Update to handle circular list also.
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
                                UInt32          priority);

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
Int32 BspUtils_unLinkAllNodes(BspUtils_Handle handle);

/**
 *  BspUtils_unLinkNodePri
 *  \brief Unlinks the node from the list. Used for the Priority linklists.
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void BspUtils_unLinkNodePri(BspUtils_Handle handle, BspUtils_Node *node);

/**
 *  BspUtils_unLinkNode
 *  \brief Unlinks the node from the list. Used for Non-priority linked lists
 *
 *  \param handle           Link list handle.
 *  \param node             Node pointer to be unlinked from the list.
 */
void BspUtils_unLinkNode(BspUtils_Handle handle, const BspUtils_Node *node);

/**
 *  BspUtils_linkNodeToHead
 *  \brief                  Link the node to the head of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 *
 */
void BspUtils_linkNodeToHead(BspUtils_Handle handle,
                             BspUtils_Node  *node);

/**
 *  BspUtils_linkNodeToTail
 *  \brief                  Link the node to the tail of the double linked list.
 *                          No priority
 *
 *  \param handle           Link list handle.
 *  \param node             Node object pointer used for linking.
 */
void BspUtils_linkNodeToTail(BspUtils_Handle handle,
                             BspUtils_Node  *node);

/**
 *  BspUtils_unLinkNodeFromHead
 *  \brief                  Returns the node from head. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \return                 Pointer to unlinked node.
 *
 */
BspUtils_Node *BspUtils_unLinkNodeFromHead(BspUtils_Handle handle);

/**
 *  BspUtils_unLinkNodeFromTail
 *  \brief                  Returns the node from tail. Removes the  node from
 *                          the list.
 *
 *  \param handle           Link list handle.
 *  \return                 Pointer to unlinked node.
 *
 */
BspUtils_Node *BspUtils_unLinkNodeFromTail(BspUtils_Handle handle);

/**
 *  BspUtils_getHeadNode
 *  \brief                  Returns the reference to the headNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 */
BspUtils_Node *BspUtils_getHeadNode(BspUtils_Handle handle);

/**
 *  BspUtils_getTailNode
 *  \brief                  Returns the reference to the TailNode. Does
 *                          not remove the node from the head.
 *
 *  \param handle           Link list handle.
 *  \return                 Reference  to tail node.  Acutally  node is not
 *                          unlinked from list.
 *
 */
BspUtils_Node *BspUtils_getTailNode(BspUtils_Handle handle);

/**
 *  BspUtils_isListEmpty
 *  \brief Checks whether a list is empty or not.
 *
 *  \param handle           List handle.
 *
 *  \return                 TRUE if List is empty else returns FALSE.
 */
UInt32 BspUtils_isListEmpty(BspUtils_Handle handle);

/**
 *  BspUtils_getNumNodes
 *  \brief Returns the number of nodes present in a list.
 *
 *  \param handle           List handle.
 *
 *  \return                 Number of nodes present in a list.
 */
UInt32 BspUtils_getNumNodes(BspUtils_Handle handle);

/**
 *  BspUtils_getNodeCnt
 *  \brief Returns the number of nodes in the link list
 *
 *  \param handle           Link list handle.
 *
 *
 *  \return                 Returns the number of nodes in the list.
 */
UInt32 BspUtils_getNodeCnt(BspUtils_Handle handle);

/**
 *  BspUtils_constructQ
 *  \brief Constructs a Queue object.
 *
 * \param llobj pointer to object of type BspUtilsLinkListObj
 *
 *  \return                 Returns BSP_SOK on success else returns error value.
 */
Int32 BspUtils_constructQ(BspUtilsLinkListObj *llobj);

/**
 *  BspUtils_destructQ
 *  \brief Destructs a Queue object.
 *
 * \param llobj pointer to object of type BspUtilsLinkListObj
 *
 *  \return                 Returns BSP_SOK on success else returns error value.
 */
Int32 BspUtils_destructQ(BspUtilsLinkListObj *llobj);

/**
 *  BspUtils_queue
 *  \brief Adds the data to the queue.
 *  The memory to the node object should be allocated by the caller.
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void BspUtils_queue(BspUtils_QHandle handle,
                    BspUtils_QElem  *qElem,
                    Ptr              data);

/**
 *  BspUtils_dequeue
 *  \brief Removes a element from the queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Returns the removed data pointer.
 */
void *BspUtils_dequeue(BspUtils_QHandle handle);

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
void *BspUtils_peakHead(BspUtils_QHandle handle);

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
void *BspUtils_peakTail(BspUtils_QHandle handle);

/**
 *  BspUtils_queueBack
 *  \brief Adds the data to start of the queue.
 *  The memory to the node object should be allocated by the caller.
 *
 *  \param handle           Queue handle.
 *  \param qElem            Queue Element object pointer used for linking.
 *  \param data             Data pointer to be added to the list.
 *                          This should be unique.
 */
void BspUtils_queueBack(BspUtils_QHandle handle,
                        BspUtils_QElem  *qElem,
                        void            *data);

/**
 *  BspUtils_isQEmpty
 *  \brief Checks whether a queue is empty or not.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 TRUE if queue is empty else returns FALSE.
 */
UInt32 BspUtils_isQEmpty(BspUtils_QHandle handle);

/**
 *  BspUtils_getNumQElem
 *  \brief Returns the number of Queue Elements present in a Queue.
 *
 *  \param handle           Queue handle.
 *
 *  \return                 Number of Queue Elements present in a Queue.
 */
UInt32 BspUtils_getNumQElem(BspUtils_QHandle handle);

/**
 *  BspUtils_initPool
 *  \brief Initializes the pool object structure.
 *
 *  \param params           Pool parameters to be initialized.
 *  \param mem              Pointer to the pool memory.
 *  \param numElem          Number of elements in the pool.
 *  \param elemSize         Size of each element in bytes.
 *  \param flag             Array of flag variable used by pool manager to
 *                          indicate whether a pool element is allocated
 *                          or not. The size of this array should be
 *                          equal to the number of elements in this pool.
 *  \param traceMask        Trace mask used in trace prints.
 */
static inline void BspUtils_initPool(BspUtils_PoolParams *params,
                                     void                *mem,
                                     UInt32               numElem,
                                     UInt32               elemSize,
                                     UInt32              *flag,
                                     UInt32               traceMask);

/**
 *  BspUtils_alloc
 *  \brief Allocates one element from the pool.
 *
 *  \param params           Pool parameters.
 *  \param size             Size in bytes to allocate.
 *  \param traceMask        Trace mask used in trace prints.
 *
 *  \return                 Returns memory pointer on success else returns
 *                          NULL.
 */
static inline void *BspUtils_alloc(BspUtils_PoolParams *params,
                                   UInt32               size,
                                   UInt32               traceMask);

/**
 *  BspUtils_free
 *  \brief Frees the element and returns to the pool.
 *
 *  \param params           Pool parameters.
 *  \param mem              Memory pointer to deallocate.
 *  \param traceMask        Trace mask used in trace prints.
 *
 *  \return                 Returns 0 on success else returns error value.
 */
static inline Int32 BspUtils_free(BspUtils_PoolParams *params,
                                  const void          *mem,
                                  UInt32               traceMask);

/**
 *  BspUtils_initTsPrfLog
 *  \brief Initializes the structure. This should be called once before
 *  calling any other performance functions.
 *
 *  \param tsPrf            Pointer to BspUtils_TsPrfLog structure.
 *
 */
static inline void BspUtils_initTsPrfLog(BspUtils_TsPrfLog *tsPrf);

/**
 *  BspUtils_startTsPrfLog
 *  \brief Log the start entry to the performance structure.
 *
 *  \param tsPrf            Pointer to BspUtils_TsPrfLog structure.
 */
static inline void BspUtils_startTsPrfLog(BspUtils_TsPrfLog *tsPrf);

/**
 *  BspUtils_endTsPrfLog
 *  \brief Log the entry to the performance structure. This uses the previous
 *  startTime stored when calling BspUtils_startTsPrfLog() to calculate the
 *  difference.
 *
 *  \param tsPrf            Pointer to BspUtils_TsPrfLog structure.
 */
static inline void BspUtils_endTsPrfLog(BspUtils_TsPrfLog *tsPrf);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BspUtils_initPool(BspUtils_PoolParams *params,
                                     void                *mem,
                                     UInt32               numElem,
                                     UInt32               elemSize,
                                     UInt32              *flag,
                                     UInt32               traceMask)
{
    UInt32 cnt;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL != params));
    GT_assert(traceMask, (NULL != mem));
    GT_assert(traceMask, (NULL != flag));

    /* Init pool parameters */
    params->mem         = mem;
    params->numElem     = numElem;
    params->elemSize    = elemSize;
    params->flag        = flag;
    params->numFreeElem = numElem;

    /* Set pool flags as free */
    for (cnt = 0U; cnt < params->numElem; cnt++)
    {
        params->flag[cnt] = (UInt32) FALSE;
    }

    return;
}

static inline void *BspUtils_alloc(BspUtils_PoolParams *params,
                                   UInt32               size,
                                   UInt32               traceMask)
{
    UInt32 cnt;
    UInt32 cookie;
    UInt32 tempVal;
    void  *allocMem = NULL;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL != params));
    /* Check if the requested size if within each fixed size element */
    GT_assert(traceMask, (size <= params->elemSize));
    GT_assert(traceMask, (0U != size));

    /* Disable global interrupts */
    cookie = BspOsal_disableInterrupt();

    for (cnt = 0U; cnt < params->numElem; cnt++)
    {
        if ((UInt32) FALSE == params->flag[cnt])
        {
            tempVal = ((UInt32) params->mem) +
                      (params->elemSize * cnt);
            allocMem          = (void *) (tempVal);
            params->flag[cnt] = (UInt32) TRUE;

            /* Decrement free count.
             * Assert if it is zero as it can never happen. */
            GT_assert(traceMask, (0U != params->numFreeElem));
            params->numFreeElem--;
            break;
        }
    }

    /* Restore global interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (allocMem);
}

static inline Int32 BspUtils_free(BspUtils_PoolParams *params,
                                  const void          *mem,
                                  UInt32               traceMask)
{
    UInt32 cnt;
    UInt32 tempVal;
    Int32  retVal = BSP_EFAIL;
    UInt32 cookie;

    /* NULL pointer check */
    GT_assert(traceMask, (NULL != params));
    GT_assert(traceMask, (NULL != mem));

    /* Disable global interrupts */
    cookie = BspOsal_disableInterrupt();

    for (cnt = 0U; cnt < params->numElem; cnt++)
    {
        tempVal = ((UInt32) params->mem) + (params->elemSize * cnt);
        if ((void *) (tempVal) == mem)
        {
            /* Check if the memory is already allocated */
            GT_assert(traceMask, ((UInt32) TRUE == params->flag[cnt]));
            params->flag[cnt] = (UInt32) FALSE;

            /* Increment free count.
             * Assert if it is more than num elements as it can never happen. */
            params->numFreeElem++;
            GT_assert(traceMask, (params->numFreeElem <= params->numElem));

            retVal = BSP_SOK;
            break;
        }
    }

    /* Restore global interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (retVal);
}

static inline void BspUtils_initTsPrfLog(BspUtils_TsPrfLog *tsPrf)
{
    /* NULL pointer check */
    GT_assert(GT_DEFAULT_MASK, (NULL != tsPrf));

    BspUtils_memset(tsPrf, 0, sizeof (BspUtils_TsPrfLog));
    /* Min can't be init to 0, set a higher value so that actual min gets
     * registered */
    tsPrf->min = 0xFFFFFFFFU;

    return;
}

static inline void BspUtils_startTsPrfLog(BspUtils_TsPrfLog *tsPrf)
{
    /* NULL pointer check */
    GT_assert(GT_DEFAULT_MASK, (NULL != tsPrf));

    tsPrf->startTime = BspOsal_getTimestamp64();

    return;
}

static inline void BspUtils_endTsPrfLog(BspUtils_TsPrfLog *tsPrf)
{
    UInt64 endTime, diff;

    /* NULL pointer check */
    GT_assert(GT_DEFAULT_MASK, (NULL != tsPrf));

    endTime = BspOsal_getTimestamp64();
    diff    = endTime - tsPrf->startTime;

    /* Log the difference */
    tsPrf->total += diff;
    tsPrf->totalCnt++;
    if (diff < tsPrf->min)
    {
        tsPrf->min = diff;
    }
    if (diff > tsPrf->max)
    {
        tsPrf->max = diff;
    }
    if (tsPrf->prfLogIndex >= BSPUTILS_NUM_TIMESTAMP_LOG)
    {
        tsPrf->prfLogIndex = 0U;
    }
    tsPrf->prfLog[tsPrf->prfLogIndex] = diff;
    tsPrf->prfLogIndex++;

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_UTILS_H_ */
