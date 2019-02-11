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
 * \file utils_buf_ext.c
 *
 * \brief This file has the implementation of the system buffer exchange queue
 *        API
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/rtos/utils_common/include/utils_buf_ext.h>

Int32 Utils_bufCreateExt(Utils_BufHndlExt * pHndl, Bool blockOnGet,
                         Bool blockOnPut, UInt32 numAllocPools)
{
    Int32 status;
    UInt32 flags;
    UInt32 i;

    flags = UTILS_QUE_FLAG_NO_BLOCK_QUE;

    if (blockOnGet)
    {
        flags |= UTILS_QUE_FLAG_BLOCK_QUE_GET;
    }
    if (blockOnPut)
    {
        flags |= UTILS_QUE_FLAG_BLOCK_QUE_PUT;
    }

    for (i = 0U; i < numAllocPools; i++)
    {
        status = Utils_queCreate(&pHndl->emptyQue[i],
                                 UTILS_BUF_MAX_QUE_SIZE,
                                 pHndl->emptyQueMem[i], flags);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    pHndl->numAllocPools = numAllocPools;

    status = Utils_queCreate(&pHndl->fullQue,
                             UTILS_BUF_MAX_QUE_SIZE, pHndl->fullQueMem, flags);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}

Int32 Utils_bufDeleteExt(Utils_BufHndlExt * pHndl)
{
    Int i;

    for (i = 0; i < pHndl->numAllocPools; i++)
    {
       Utils_queDelete(&pHndl->emptyQue[i]);
    }
    pHndl->numAllocPools = 0;
    Utils_queDelete(&pHndl->fullQue);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_bufGetEmptyExt(Utils_BufHndlExt * pHndl,
                           System_BufferList * pBufList,
                           UInt32 allocPoolID, UInt32 timeout)
{
    UInt32 idx, maxBufs;
    Int32 status;
    Utils_EncDecLinkPvtInfo *linkPvtInfo;

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
    UTILS_assert(allocPoolID < pHndl->numAllocPools);

    for (idx = 0; idx < maxBufs; idx++)
    {
        /* MISRA.CAST.PTR
         * MISRAC_2004_Rule_11.4
         * MISRAC_WAIVER:
         * Generic implementation of queGet requires argument in Ptr *
         * format, so typecasting.
         */
        status =
            Utils_queGet(&(pHndl->emptyQue[allocPoolID]),
                         (Ptr *)&pBufList->buffers[idx], 1U, timeout);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }
        linkPvtInfo =
            (Utils_EncDecLinkPvtInfo*) pBufList->buffers[idx]->pEncDecLinkPrivate;
        UTILS_assert(linkPvtInfo != NULL);

        linkPvtInfo->allocPoolID = allocPoolID;
    }

    pBufList->numBuf = idx;

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_bufGetEmptyBufferExt(Utils_BufHndlExt * pHndl,
                                System_Buffer ** pBuf,
                                UInt32 allocPoolID, UInt32 timeout)
{
    Int32 status;
    Utils_EncDecLinkPvtInfo *linkPvtInfo;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBuf != NULL);

    *pBuf = NULL;
    UTILS_assert(allocPoolID < pHndl->numAllocPools);
    /* MISRA.CAST.PTR
     * MISRAC_2004_Rule_11.4
     * MISRAC_WAIVER:
     * Generic implementation of queGet requires argument in Ptr *
     * format, so typecasting.
     */
    status = Utils_queGet(&(pHndl->emptyQue[allocPoolID]),
                         (Ptr *)pBuf, 1U, timeout);

    if (status == SYSTEM_LINK_STATUS_SOK)
    {
        linkPvtInfo = (Utils_EncDecLinkPvtInfo *) (*pBuf)->pEncDecLinkPrivate;
        UTILS_assert(linkPvtInfo != NULL);
        linkPvtInfo->allocPoolID = allocPoolID;
    }

    return status;
}

Int32 Utils_bufPutEmptyExt(Utils_BufHndlExt * pHndl,
                           System_BufferList * pBufList)
{
    UInt32 idx;
    Int32 status;
    UInt32 allocPoolID;
    Utils_EncDecLinkPvtInfo *linkPvtInfo;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < pBufList->numBuf; idx++)
    {
        linkPvtInfo =
            (Utils_EncDecLinkPvtInfo *) pBufList->buffers[idx]->pEncDecLinkPrivate;
        UTILS_assert(linkPvtInfo != NULL);
        allocPoolID = linkPvtInfo->allocPoolID;

        UTILS_assert(allocPoolID < pHndl->numAllocPools);
        status =
            Utils_quePut(&(pHndl->emptyQue[allocPoolID]),
                         pBufList->buffers[idx], BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_bufPutEmptyBufferExt(Utils_BufHndlExt * pHndl, System_Buffer * pBuf)
{
    Int32 status;
    Utils_EncDecLinkPvtInfo *linkPvtInfo;

    linkPvtInfo = (Utils_EncDecLinkPvtInfo *) pBuf->pEncDecLinkPrivate;
    UTILS_assert(pHndl != NULL);
    UTILS_assert(linkPvtInfo != NULL);
    UTILS_assert(linkPvtInfo->allocPoolID < pHndl->numAllocPools);

    status = Utils_quePut(&(pHndl->emptyQue[linkPvtInfo->allocPoolID]),
                         pBuf, BSP_OSAL_NO_WAIT);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_bufGetFullExt(Utils_BufHndlExt * pHndl,
                          System_BufferList * pBufList, UInt32 timeout)
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
        /* MISRA.CAST.PTR
         * MISRAC_2004_Rule_11.4
         * MISRAC_WAIVER:
         * Generic implementation of queGet requires argument in Ptr *
         * format, so typecasting.
         */
        status =
            Utils_queGet(&pHndl->fullQue, (Ptr *)&pBufList->buffers[idx], 1U,
                         timeout);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            break;
        }
    }

    pBufList->numBuf = idx;

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_bufGetFullBufferExt(Utils_BufHndlExt * pHndl,
                                System_Buffer ** pBuf, UInt32 timeout)
{
    Int32 status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBuf != NULL);

    *pBuf = NULL;
    /* MISRA.CAST.PTR
     * MISRAC_2004_Rule_11.4
     * MISRAC_WAIVER:
     * Generic implementation of queGet requires argument in Ptr *
     * format, so typecasting.
     */
    status = Utils_queGet(&pHndl->fullQue, (Ptr *)pBuf, 1U, timeout);

    return status;
}

Int32 Utils_bufPutFullExt(Utils_BufHndlExt * pHndl,
                          System_BufferList * pBufList)
{
    UInt32 idx;
    Int32 status;

    UTILS_assert(pHndl != NULL);
    UTILS_assert(pBufList != NULL);
    UTILS_assert(pBufList->numBuf <= (UInt32)SYSTEM_MAX_BUFFERS_IN_BUFFER_LIST);

    for (idx = 0; idx < pBufList->numBuf; idx++)
    {
        status =
            Utils_quePut(&pHndl->fullQue, pBufList->buffers[idx],
                         BSP_OSAL_NO_WAIT);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_bufPutFullBufferExt(Utils_BufHndlExt * pHndl, System_Buffer * pBuf)
{
    Int32 status;

    UTILS_assert(pHndl != NULL);

    status = Utils_quePut(&pHndl->fullQue, pBuf, BSP_OSAL_NO_WAIT);
    if (status != SYSTEM_LINK_STATUS_SOK)
    {
#if 0
        Vps_printf
            (" ERROR: In Utils_bufPutFullBufExt(), Utils_quePut() failed !!!\n");
#endif
    }

    return status;
}

Void Utils_bufExtPrintStatus(UInt8 *str, Utils_BufHndlExt * pHndl)
{
    Uint8 i;

    Vps_printf("%s BufExt Q Status\n", str);
    for (i=0; i<pHndl->numAllocPools; i++)
    {
        Vps_printf(" Empty Q %d -> count %d, wrPtr %d, rdPtr %d\n", i,
        pHndl->emptyQue[i].count, pHndl->emptyQue[i].curWr, pHndl->emptyQue[i].curRd);
    }
    Vps_printf(" Full Q -> count %d, wrPtr %d, rdPtr %d\n", pHndl->fullQue.count,
        pHndl->fullQue.curWr, pHndl->fullQue.curRd);
}

