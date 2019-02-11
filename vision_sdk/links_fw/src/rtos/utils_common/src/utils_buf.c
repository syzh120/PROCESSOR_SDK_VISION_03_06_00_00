/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file utils_buf.c
 *
 * \brief This file has the implementation of the system buffer exchange queue
 *        API
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_buf.h>

/**
 *******************************************************************************
 *
 * \brief Create a system buffer handle
 *
 *        When blockOnGet/blockOnPut is TRUE a semaphore gets allocated
 *        internally. In order to reduce resource usuage keep this as FALSE
 *        if application does not plan to use the blocking API feature.
 *
 * \param pHndl        [OUT] Created handle
 * \param blockOnGet   [IN]  Enable blocking on 'get' API
 * \param blockOnPut   [IN]  Enable blocking on 'put' API
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufCreate(Utils_BufHndl * pHndl, Bool blockOnGet, Bool blockOnPut)
{
    Int32 status;
    UInt32 flags;

    flags = UTILS_QUE_FLAG_NO_BLOCK_QUE;

    if (blockOnGet)
    {
        flags |= UTILS_QUE_FLAG_BLOCK_QUE_GET;
    }

    if (blockOnPut)
    {
        flags |= UTILS_QUE_FLAG_BLOCK_QUE_PUT;
    }

    status = Utils_queCreate(&pHndl->emptyQue,
                             UTILS_BUF_MAX_QUE_SIZE, pHndl->emptyQueMem, flags);
    UTILS_assert(status == (Int32) SYSTEM_LINK_STATUS_SOK);

    status = Utils_queCreate(&pHndl->fullQue,
                             UTILS_BUF_MAX_QUE_SIZE, pHndl->fullQueMem, flags);
    UTILS_assert(status == (Int32) SYSTEM_LINK_STATUS_SOK);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Delete system buffer handle
 *
 *        Free's resources like semaphore allocated during create
 *
 * \param pHndl    [IN] Buffer handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufDelete(Utils_BufHndl * pHndl)
{
    Utils_queDelete(&pHndl->emptyQue);
    Utils_queDelete(&pHndl->fullQue);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get system buffers from empty queue
 *
 *        This API is used to get multiple empty buffers in a single API call.
 *        When timeout == BSP_OSAL_NO_WAIT,
 *             maximum possible buffer are returned.
 *        When timeout != BSP_OSAL_NO_WAIT,
 *             upto max pBufList->numBuf are returned.
 *
 *        On return pBufList->numBuf is set to number of buffers
 *        that are returned.
 *
 *        When during create
 *        - 'blockOnGet' = TRUE
 *            - timeout can be BSP_OSAL_WAIT_FOREVER or BSP_OSAL_NO_WAIT or
 *              amount of time in units of OS ticks that it should block
 *        - 'blockOnGet' = FALSE
 *            - timeout must be BSP_OSAL_NO_WAIT
 *
 * \param pHndl        [IN]     Buffer handle
 * \param pBufList     [IN/OUT] Buffers returned by the API
 * \param timeout      [IN]     BSP_OSAL_NO_WAIT or BSP_OSAL_WAIT_FOREVER or
 *                              amount of time in units of OS ticks that
 *                              it should block
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufGetEmpty(Utils_BufHndl * pHndl, System_BufferList * pBufList,
                        UInt32 timeout)
{
    UInt32 idx, maxBufs;
    Int32  status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBufList != NULL);

    if (timeout == BSP_OSAL_NO_WAIT)
    {
        maxBufs = (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST;
    }
    else
    {
        maxBufs = pBufList->numBuf;
    }

    UTILS_assert(maxBufs <= (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0U; idx < maxBufs; idx++)
    {
        status =
            Utils_queGet(&pHndl->emptyQue,
                        (Ptr*)&pBufList->buffers[idx], 1U,
                         timeout);
        /*  MISRA.CAST.PTR
         *  MISRAC_2004_Rule_11.4:Cast between a pointer to object type and
         *                        a different pointer to object type
         *  State: FIXED IN LATER RELEASE -> Waiver -> Case by case
         *  Pointers to different layer's handles are stored as void*.
         *
         */
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }
    }

    pBufList->numBuf = idx;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get a system buffer from empty queue
 *
 *        Same as Utils_bufGetEmpty() except that only a single buffer is
 *        returned
 *
 * \param pHndl        [IN]  Buffer handle
 * \param pBuf         [OUT] Buffer that is returned by the API
 * \param timeout      [IN]  BSP_OSAL_NO_WAIT or BSP_OSAL_WAIT_FOREVER or
 *                           amount of time in units of OS ticks that
 *                           it should block
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufGetEmptyBuffer(Utils_BufHndl * pHndl,
                              System_Buffer ** pBuf, UInt32 timeout)
{
    Int32 status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBuf != NULL);

    *pBuf = NULL;

    status = Utils_queGet(&pHndl->emptyQue, (Ptr *)pBuf, 1U, timeout);
    /*  MISRA.CAST.PTR
     *  MISRAC_2004_Rule_11.4:Cast between a pointer to object type and
     *                        a different pointer to object type
     *  State: FIXED IN LATER RELEASE -> Waiver -> Case by case
     *  Pointers to different layer's handles are stored as void*.
     *
     */

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Get number of system buffers available in the empty queue
 *
 * \param pHndl        [IN] Buffer handle
 *
 * \return Empty buffers count
 *
 *******************************************************************************
 */
UInt32 Utils_bufGetEmptyBufferCount(const Utils_BufHndl * pHndl)
{
    UInt32 emptyBufCnt;

    UTILS_assert(pHndl != NULL);
    emptyBufCnt = Utils_queGetQueuedCount(&pHndl->emptyQue);

    return emptyBufCnt;
}

/**
 *******************************************************************************
 *
 * \brief Put system buffers into empty queue
 *
 *        This API is used to put multiple buffers in the empty queue in a
 *        single API call. pBufList->numBuf is set to number of buffers
 *        that are to be returned.
 *
 * \param pHndl        [IN] Buffer handle
 * \param pBufList     [IN] Buffers to be put
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufPutEmpty(Utils_BufHndl * pHndl, System_BufferList * pBufList)
{
    UInt32 idx;
    Int32 status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0U; idx < pBufList->numBuf; idx++)
    {
        status =
            Utils_quePut(
                &pHndl->emptyQue,
                (Ptr)pBufList->buffers[idx],
                BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Put a system buffer into empty queue
 *
 *        Same as Utils_bufPutEmpty() except that only a single buffer is put
 *
 * \param pHndl        [IN] Buffer handle
 * \param pBuf         [OUT] Buffer that is to be returned to the queue
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufPutEmptyBuffer(Utils_BufHndl * pHndl, System_Buffer * pBuf)
{
    Int32 status;

    UTILS_assert(pHndl != NULL);

    status = Utils_quePut(&pHndl->emptyQue, (Ptr)pBuf, BSP_OSAL_NO_WAIT);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get system buffers from full queue
 *
 *        This API is used to get multiple full buffers in a single API call.
 *        When timeout == BSP_OSAL_NO_WAIT,
 *             maximum possible buffer are returned.
 *        When timeout != BSP_OSAL_NO_WAIT,
 *             upto max pBufList->numBuf are returned.
 *
 *        On return pBufList->numBuf is set to number of buffers
 *        that are returned.
 *
 *        When during create
 *        - 'blockOnGet' = TRUE
 *            - timeout can be BSP_OSAL_WAIT_FOREVER or BSP_OSAL_NO_WAIT or
 *              amount of time in units of OS ticks that it should block
 *        - 'blockOnGet' = FALSE
 *            - timeout must be BSP_OSAL_NO_WAIT
 *
 * \param pHndl        [IN]     Buffer handle
 * \param pBufList     [IN/OUT] Buffers returned by the API
 * \param timeout      [IN]     BSP_OSAL_NO_WAIT or BSP_OSAL_WAIT_FOREVER or
 *                              amount of time in units of OS ticks that
 *                              it should block
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufGetFull(Utils_BufHndl * pHndl, System_BufferList * pBufList,
                       UInt32 timeout)
{
    UInt32 idx, maxBufs;
    Int32 status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBufList != NULL);

    if (timeout == BSP_OSAL_NO_WAIT)
    {
        maxBufs = (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST;
    }
    else
    {
        maxBufs = pBufList->numBuf;
    }

    UTILS_assert(maxBufs <= (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < maxBufs; idx++)
    {
        status =
            Utils_queGet(&pHndl->fullQue, (Ptr *)&pBufList->buffers[idx], 1U,
                         timeout);
        /*  MISRA.CAST.PTR
         *  MISRAC_2004_Rule_11.4:Cast between a pointer to object type and
         *                        a different pointer to object type
         *  State: FIXED IN LATER RELEASE -> Waiver -> Case by case
         *  Pointers to different layer's handles are stored as void*.
         *
         */
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }
    }

    pBufList->numBuf = idx;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get number of system buffers available in the full queue
 *
 * \param pHndl        [IN] Buffer handle
 *
 * \return Full buffers count
 *
 *******************************************************************************
 */
UInt32 Utils_bufGetFullBufferCount(const Utils_BufHndl * pHndl)
{
    UInt32 fullBufCnt;

    UTILS_assert(pHndl != NULL);
    fullBufCnt = Utils_queGetQueuedCount(&pHndl->fullQue);

    return fullBufCnt;
}

/**
 *******************************************************************************
 *
 * \brief Get a system buffer from full queue
 *
 *        Same as Utils_bufGetFull() except that only a single buffer is
 *        returned
 *
 * \param pHndl        [IN]  Buffer handle
 * \param pBuf         [OUT] Buffer that is returned by the API
 * \param timeout      [IN]  BSP_OSAL_NO_WAIT or BSP_OSAL_WAIT_FOREVER or
 *                           amount of time in units of OS ticks that
 *                           it should block
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufGetFullBuffer(Utils_BufHndl * pHndl,
                            System_Buffer ** pBuf, UInt32 timeout)
{
    Int32 status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBuf != NULL);

    *pBuf = NULL;

    status = Utils_queGet(&pHndl->fullQue, (Ptr *)pBuf, 1U, timeout);
    /*  MISRA.CAST.PTR
     *  MISRAC_2004_Rule_11.4:Cast between a pointer to object type and
     *                        a different pointer to object type
     *  State: FIXED IN LATER RELEASE -> Waiver -> Case by case
     *  Pointers to different layer's handles are stored as void*.
     *
     */

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Put system buffers into full queue
 *
 *        This API is used to put multiple buffers in the full queue in a
 *        single API call. pBufList->numBuf is set to number of buffers
 *        that are to be returned.
 *
 * \param pHndl        [IN] Buffer handle
 * \param pBufList     [IN] Buffers to be put
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufPutFull(Utils_BufHndl * pHndl, System_BufferList * pBufList)
{
    UInt32 idx;
    Int32 status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < pBufList->numBuf; idx++)
    {
        status =
            Utils_quePut(&pHndl->fullQue, (Ptr)pBufList->buffers[idx],
                         BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 * \brief Put a system buffer into full queue
 *
 *        Same as Utils_bufPutFull() except that only a single buffer is put
 *
 * \param pHndl        [IN] Buffer handle
 * \param pBuf         [OUT] Buffer that is to be returned to the queue
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 Utils_bufPutFullBuffer(Utils_BufHndl * pHndl, System_Buffer * pBuf)
{
    Int32 status;

    UTILS_assert(pHndl != NULL);

    status = Utils_quePut(&pHndl->fullQue, (Ptr)pBuf, BSP_OSAL_NO_WAIT);
    if (status != SYSTEM_LINK_STATUS_SOK)
    {
#if 0
        Vps_printf
            (" UTILS: BUF: ERROR: In Utils_bufPutFullBuffer(), Utils_quePut() failed !!!\n",
             );
#endif
    }

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Initialize the given FVID2 Frame using the given System_Buffer
 *
 *        The links communicate with each other using the System_Buffer.
 *        However, the driver interface uses FVID2_Frame. Links that interface
 *        with FVID2 drivers need to convert System_Buffer from/to FVID2_Frame.
 *
 *        This function converts the given System_Buffer into FVID2_Frame.
 *
 * \param pFrame       [OUT] FVID2 Frame to be initialized
 * \param pBuffer      [IN] System_Buffer used to initialize the frame
 *
 *   \return SYSTEM_LINK_SOK on success
 *
 *******************************************************************************
 */
Int32 Utils_bufInitFrame(FVID2_Frame *pFrame, System_Buffer *pBuffer)
{
    UInt32 idx, planes;
    System_VideoFrameBuffer *pVideoFrame;
    UTILS_assert(pBuffer != NULL);

    UTILS_assert((pBuffer->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME) ||
            (pBuffer->bufType == SYSTEM_BUFFER_TYPE_EGLPIXMAP_VIDEO_FRAME));

    pVideoFrame = pBuffer->payload;
    UTILS_assert(pVideoFrame != NULL);

    UTILS_assert(UTILS_ARRAYSIZE(pVideoFrame->bufAddr) >= UTILS_ARRAYSIZE(pFrame->addr[0]));

    memset(pFrame, 0, sizeof(FVID2_Frame));

    pFrame->chNum       = pBuffer->chNum;
    pFrame->timeStamp   = pBuffer->linkLocalTimestamp;
    pFrame->appData     = pBuffer;
    pFrame->fid = System_Video_Frame_Get_Flag_Fid(pVideoFrame->flags);

    planes = UTILS_ARRAYSIZE(pFrame->addr[0]);

    for (idx = 0; idx < planes; idx++)
    {
        pFrame->addr[0][idx] = pVideoFrame->bufAddr[idx];
    }

    return SYSTEM_LINK_STATUS_SOK;
}


/**
 *******************************************************************************
 *
 * \brief Print buffer status of full & empty queues
 *
 * \param str            [IN] prefix string to print
 * \param pHndl          [IN] Buffer handle
 *
 * \return None
 *
 *******************************************************************************
 */
Void Utils_bufPrintStatus(UInt8 *str, Utils_BufHndl * pHndl)
{
    Vps_printf(" [%s] Buffer Q Status,\n", str);
    Vps_printf(" Empty Q :"
               " Elements in Q = %3d, Write Idx = %3d, Read Idx = %3d\n",
                    pHndl->emptyQue.count,
                    pHndl->emptyQue.curWr,
                    pHndl->emptyQue.curRd);
    Vps_printf(" Full  Q :"
               " Elements in Q = %3d, Write Idx = %3d, Read Idx = %3d\n",
                    pHndl->fullQue.count,
                    pHndl->fullQue.curWr,
                    pHndl->fullQue.curRd);
}


