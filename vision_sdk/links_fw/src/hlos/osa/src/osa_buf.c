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
#include <osa_buf.h>

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
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufCreate(OSA_BufHndl * pHndl, Bool blockOnGet, Bool blockOnPut)
{
    Int32 status;

    status = OSA_queCreate(&pHndl->emptyQue,
                             OSA_BUF_MAX_QUE_SIZE);
    OSA_assert(status == OSA_SOK);

    status = OSA_queCreate(&pHndl->fullQue,
                             OSA_BUF_MAX_QUE_SIZE);
    OSA_assert(status == OSA_SOK);

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
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufDelete(OSA_BufHndl * pHndl)
{
    OSA_queDelete(&pHndl->emptyQue);
    OSA_queDelete(&pHndl->fullQue);

    return OSA_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get system buffers from empty queue
 *
 *        This API is used to get multiple empty buffers in a single API call.
 *        When timeout == OSA_TIMEOUT_NONE,
 *             maximum possible buffer are returned.
 *        When timeout != OSA_TIMEOUT_NONE,
 *             upto max pBufList->numBuf are returned.
 *
 *        On return pBufList->numBuf is set to number of buffers
 *        that are returned.
 *
 *        When during create
 *        - 'blockOnGet' = TRUE
 *            - timeout can be BIOS_WAIT_FOREVER or OSA_TIMEOUT_NONE or
 *              amount of time in units of OS ticks that it should block
 *        - 'blockOnGet' = FALSE
 *            - timeout must be OSA_TIMEOUT_NONE
 *
 * \param pHndl        [IN]     Buffer handle
 * \param pBufList     [IN/OUT] Buffers returned by the API
 * \param timeout      [IN]     OSA_TIMEOUT_NONE or BIOS_WAIT_FOREVER or
 *                              amount of time in units of OS ticks that
 *                              it should block
 *
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufGetEmpty(OSA_BufHndl * pHndl, System_BufferList * pBufList,
                        UInt32 timeout)
{
    UInt32 idx, maxBufs;
    Int32  status;

    OSA_assert(pHndl != NULL);
    OSA_assert(pBufList != NULL);

    if (timeout == OSA_TIMEOUT_NONE)
        maxBufs = SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST;
    else
        maxBufs = pBufList->numBuf;

    OSA_assert(maxBufs <= SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < maxBufs; idx++)
    {
        status =
            OSA_queGet(&pHndl->emptyQue, (Int32 *)&(pBufList->buffers[idx]), timeout);
        if (status != OSA_SOK)
            break;
    }

    pBufList->numBuf = idx;

    return OSA_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get a system buffer from empty queue
 *
 *        Same as OSA_bufGetEmpty() except that only a single buffer is
 *        returned
 *
 * \param pHndl        [IN]  Buffer handle
 * \param pBuf         [OUT] Buffer that is returned by the API
 * \param timeout      [IN]  OSA_TIMEOUT_NONE or BIOS_WAIT_FOREVER or
 *                           amount of time in units of OS ticks that
 *                           it should block
 *
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufGetEmptyBuffer(OSA_BufHndl * pHndl,
                              System_Buffer ** pBuf, UInt32 timeout)
{
    Int32 status;

    OSA_assert(pHndl != NULL);
    OSA_assert(pBuf != NULL);

    *pBuf = NULL;

    status = OSA_queGet(&pHndl->emptyQue, (Int32 *) pBuf, timeout);

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
UInt32 OSA_bufGetEmptyBufferCount(OSA_BufHndl * pHndl)
{
    UInt32 emptyBufCnt;

    OSA_assert(pHndl != NULL);
    emptyBufCnt = OSA_queGetQueuedCount(&pHndl->emptyQue);

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
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufPutEmpty(OSA_BufHndl * pHndl, System_BufferList * pBufList)
{
    UInt32 idx;
    Int32 status;

    OSA_assert(pHndl != NULL);
    OSA_assert(pBufList != NULL);
    OSA_assert(pBufList->numBuf <= SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < pBufList->numBuf; idx++)
    {
        status =
            OSA_quePut(&pHndl->emptyQue, (Int32)pBufList->buffers[idx],
                         OSA_TIMEOUT_NONE);
        OSA_assert(status == OSA_SOK);
    }

    return OSA_SOK;
}

/**
 *******************************************************************************
 * \brief Put a system buffer into empty queue
 *
 *        Same as OSA_bufPutEmpty() except that only a single buffer is put
 *
 * \param pHndl        [IN] Buffer handle
 * \param pBuf         [OUT] Buffer that is to be returned to the queue
 *
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufPutEmptyBuffer(OSA_BufHndl * pHndl, System_Buffer * pBuf)
{
    Int32 status;

    OSA_assert(pHndl != NULL);

    status = OSA_quePut(&pHndl->emptyQue, (Int32)pBuf, OSA_TIMEOUT_NONE);
    OSA_assert(status == OSA_SOK);

    return OSA_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get system buffers from full queue
 *
 *        This API is used to get multiple full buffers in a single API call.
 *        When timeout == OSA_TIMEOUT_NONE,
 *             maximum possible buffer are returned.
 *        When timeout != OSA_TIMEOUT_NONE,
 *             upto max pBufList->numBuf are returned.
 *
 *        On return pBufList->numBuf is set to number of buffers
 *        that are returned.
 *
 *        When during create
 *        - 'blockOnGet' = TRUE
 *            - timeout can be BIOS_WAIT_FOREVER or OSA_TIMEOUT_NONE or
 *              amount of time in units of OS ticks that it should block
 *        - 'blockOnGet' = FALSE
 *            - timeout must be OSA_TIMEOUT_NONE
 *
 * \param pHndl        [IN]     Buffer handle
 * \param pBufList     [IN/OUT] Buffers returned by the API
 * \param timeout      [IN]     OSA_TIMEOUT_NONE or BIOS_WAIT_FOREVER or
 *                              amount of time in units of OS ticks that
 *                              it should block
 *
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufGetFull(OSA_BufHndl * pHndl, System_BufferList * pBufList,
                       UInt32 timeout)
{
    UInt32 idx, maxBufs;
    Int32 status;

    OSA_assert(pHndl != NULL);
    OSA_assert(pBufList != NULL);

    if (timeout == OSA_TIMEOUT_NONE)
        maxBufs = SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST;
    else
        maxBufs = pBufList->numBuf;

    OSA_assert(maxBufs <= SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < maxBufs; idx++)
    {
        status =
            OSA_queGet(&pHndl->fullQue, (Int32 *)&(pBufList->buffers[idx]), timeout);
        if (status != OSA_SOK)
            break;
    }

    pBufList->numBuf = idx;

    return OSA_SOK;
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
UInt32 OSA_bufGetFullBufferCount(OSA_BufHndl * pHndl)
{
    UInt32 fullBufCnt;

    OSA_assert(pHndl != NULL);
    fullBufCnt = OSA_queGetQueuedCount(&pHndl->fullQue);

    return fullBufCnt;
}

/**
 *******************************************************************************
 *
 * \brief Get a system buffer from full queue
 *
 *        Same as OSA_bufGetFull() except that only a single buffer is
 *        returned
 *
 * \param pHndl        [IN]  Buffer handle
 * \param pBuf         [OUT] Buffer that is returned by the API
 * \param timeout      [IN]  OSA_TIMEOUT_NONE or BIOS_WAIT_FOREVER or
 *                           amount of time in units of OS ticks that
 *                           it should block
 *
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufGetFullBuffer(OSA_BufHndl * pHndl,
                            System_Buffer ** pBuf, UInt32 timeout)
{
    Int32 status;

    OSA_assert(pHndl != NULL);
    OSA_assert(pBuf != NULL);

    *pBuf = NULL;

    status = OSA_queGet(&pHndl->fullQue, (Int32 *)pBuf, timeout);

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
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufPutFull(OSA_BufHndl * pHndl, System_BufferList * pBufList)
{
    UInt32 idx;
    Int32 status;

    OSA_assert(pHndl != NULL);
    OSA_assert(pBufList != NULL);
    OSA_assert(pBufList->numBuf <= SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < pBufList->numBuf; idx++)
    {
        status =
            OSA_quePut(&pHndl->fullQue, (Int32)pBufList->buffers[idx],
                         OSA_TIMEOUT_NONE);
        OSA_assert(status == OSA_SOK);
    }

    return OSA_SOK;
}

/**
 *******************************************************************************
 * \brief Put a system buffer into full queue
 *
 *        Same as OSA_bufPutFull() except that only a single buffer is put
 *
 * \param pHndl        [IN] Buffer handle
 * \param pBuf         [OUT] Buffer that is to be returned to the queue
 *
 * \return OSA_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32 OSA_bufPutFullBuffer(OSA_BufHndl * pHndl, System_Buffer * pBuf)
{
    Int32 status;

    OSA_assert(pHndl != NULL);

    status = OSA_quePut(&pHndl->fullQue, (Int32)pBuf, OSA_TIMEOUT_NONE);
    if (status != OSA_SOK)
    {
#if 0
        OSA_printf
            (" OSA: BUF: ERROR: In OSA_bufPutFullBuffer(), OSA_quePut() failed !!!\n",
             );
#endif
    }

    return status;
}


// /**
//  *******************************************************************************
//  *
//  * \brief Initialize the given FVID2 Frame using the given System_Buffer
//  *
//  *        The links communicate with each other using the System_Buffer.
//  *        However, the driver interface uses FVID2_Frame. Links that interface
//  *        with FVID2 drivers need to convert System_Buffer from/to FVID2_Frame.
//  *
//  *        This function converts the given System_Buffer into FVID2_Frame.
//  *
//  * \param pFrame       [OUT] FVID2 Frame to be initialized
//  * \param pBuffer      [IN] System_Buffer used to initialize the frame
//  *
//  *   \return SYSTEM_LINK_SOK on success
//  *
//  *******************************************************************************
//  */
// Int32 OSA_bufInitFrame(FVID2_Frame *pFrame, System_Buffer *pBuffer)
// {
//     UInt32 idx, planes;
//     System_VideoFrameBuffer *pVideoFrame;

//     OSA_assert(pBuffer != NULL);
//     OSA_assert(pBuffer->bufType == SYSTEM_BUFFER_TYPE_VIDEO_FRAME);


//     pVideoFrame = pBuffer->payload;
//     OSA_assert(pVideoFrame != NULL);

//     OSA_assert(OSA_ARRAYSIZE(pVideoFrame->bufAddr) >=
//                  OSA_ARRAYSIZE(pFrame->addr[0]));

//     memset(pFrame, 0, sizeof(*pFrame));

//     pFrame->chNum       = pBuffer->chNum;
//     pFrame->timeStamp   = pBuffer->linkLocalTimestamp;
//     pFrame->appData     = pBuffer;

//     planes = OSA_ARRAYSIZE(pFrame->addr[0]);

//     for (idx = 0; idx < planes; idx++)
//     {
//         pFrame->addr[0][idx] = pVideoFrame->bufAddr[idx];
//     }

//     return OSA_SOK;
// }


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
Void OSA_bufPrintStatus(UInt8 *str, OSA_BufHndl * pHndl)
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


