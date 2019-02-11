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
 * \file utils_ipc_que.c
 *
 * \brief  This file implements the UTILS_IPC_QUE_API APIs
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_ipc_que.h>
#include <include/link_api/system_ipc_if.h>

/**
 *******************************************************************************
 *
 * \brief Create a IPC queue handle
 *
 *        The size of memory pointed by sharedMemBaseAddr allocated by the user
 *        - should atleast be
 *            maxElements*elementSize + sizeof(System_IpcQueHeader)
 *        - it should be allocated in a non-cache region (for both CPUs)
 *          which is visible to both the CPUs acessing this memory
 *
 * \param handle             [OUT] Initialized queue handle
 * \param maxElements        [IN]  Maximum elements that can reside in the queue
 *                                 at any given point of time
 * \param sharedMemBaseAddr  [IN]  Address of queue data area
 * \param elementSize        [IN]  Size of each element of the queue
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32  Utils_ipcQueCreate(Utils_IpcQueHandle * handle,
                            UInt32 maxElements,
                            Ptr sharedMemBaseAddr,
                            UInt32 elementSize)
{
    volatile UInt32 oldIntState;
    volatile System_IpcQueHeader *pShm;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(     (handle == NULL           )
        ||  (maxElements == 0         )
        ||  (sharedMemBaseAddr == NULL)
        ||  (elementSize == 0         )
        )
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {

        /* set values in local handle */
        handle->elementSize = elementSize;
        handle->maxElements = maxElements;
        handle->sharedMemBaseAddr = sharedMemBaseAddr;

        pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

        oldIntState = Hwi_disable();

        /* reset read and write index in shared memory handle */
        pShm->curRd = 0;
        pShm->curWr = 0;

        /* set element size and max number of elements in shared memory handle */
        pShm->elementSize = handle->elementSize;
        pShm->maxElements = handle->maxElements;

        Hwi_restore(oldIntState);
    }

    return status;
}


/**
 *******************************************************************************
 *
 * \brief Reset local handle and optionally reset IPC shared memory
 *        queue index's
 *
 * \param handle             [OUT] Initialized queue handle
 * \param sharedMemBaseAddr  [IN]  Address of queue data area
 * \param resetRdIdx         [IN]  TRUE: reset read index,
 *                                 FALSE: read index not modified
 * \param resetWrIdx         [IN]  TRUE: reset write index,
 *                                 FALSE: write index not modified
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32  Utils_ipcQueReset(Utils_IpcQueHandle * handle,
                            Ptr sharedMemBaseAddr,
                            Bool resetRdIdx,
                            Bool resetWrIdx
                        )
{
    volatile UInt32 oldIntState;
    volatile System_IpcQueHeader *pShm;
    volatile UInt32 value;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(     (handle == NULL             )
        ||  (sharedMemBaseAddr == NULL)
        )
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
    /* set values in local handle */
        handle->sharedMemBaseAddr = sharedMemBaseAddr;

        pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

        /*
         * set element size and max number of elements in local handle
         * from shared memory handle
         */
        handle->elementSize = pShm->elementSize;
        handle->maxElements = pShm->maxElements;

        if(     (handle->maxElements == (UInt32)0U)
            ||  (handle->elementSize == (UInt32)0U)
            )
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
        else
        {
            oldIntState = Hwi_disable();

            /*
             * reset read and write index in shared memory handle,
             * if requested by user
             */
            if(resetRdIdx)
            {
                pShm->curRd = (UInt32)0U;
            }

            if(resetWrIdx)
            {
                pShm->curWr = (UInt32)0U;
            }

            /* dummy read to ensure write to shared memory has completed */
            value = pShm->curWr;

            Hwi_restore(oldIntState);
        }
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Free resource's allocated during create
 *
 * \param handle             [IN]  queue handle
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
Int32  Utils_ipcQueDelete(const Utils_IpcQueHandle * handle)
{
    volatile UInt32 oldIntState;
    volatile System_IpcQueHeader *pShm;
    volatile UInt32 value;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(    (handle == NULL)
        || (handle->sharedMemBaseAddr == NULL)
      )
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

        oldIntState = Hwi_disable();

        /*
         * set element size and max number of elements in shared memory handle
         * to 0
         */
        pShm->elementSize = 0;
        pShm->maxElements = 0;

        /* dummy read to ensure write to shared memory has completed */
        value = pShm->curWr;

        Hwi_restore(oldIntState);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Write data into the queue
 *
 *        'dataSize' MUST be <= to elementSize set during queue create
 *
 *        Calling Utils_ipcQueWrite() once is equivalent to adding one element
 *        in the queue, even if dataSize < elementSize.
 *
 * \param handle             [IN]  queue handle
 * \param data               [IN]  local buffer from where data is written to
 *                                 the queue
 * \param dataSize           [IN]  amount of data to write to the queue
 *
 * \return TRUE, queue is empty
 *         FALSE, queue is not empty
 *
 *******************************************************************************
 */
Int32  Utils_ipcQueWrite(const Utils_IpcQueHandle * handle,
                         const volatile UInt8 *data,
                         volatile UInt32 dataSize)
{
    volatile UInt32 oldIntState;
    volatile System_IpcQueHeader *pShm;
    volatile UInt8 *pWrite;
    volatile UInt32 writeIdx;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(handle == NULL)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        if(dataSize > handle->elementSize)
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
        else
        {
            if (handle->sharedMemBaseAddr == NULL)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {
                pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

                if(     (pShm->maxElements != handle->maxElements)
                    ||  (pShm->elementSize != handle->elementSize)
                    )
                {
                    status =  SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                }
                else
                {
                    if(Utils_ipcQueIsFull(handle))
                    {
                        /* if queue is full then return */
                      status = SYSTEM_LINK_STATUS_EAGAIN;
                    }
                    else
                    {
                        /* queue is not full, write one element to the queue */
                        oldIntState = Hwi_disable();

                        writeIdx = pShm->curWr;

                        if(writeIdx < handle->maxElements)
                        {
                            /* MISRA.PTR.ARITH
                             * MISRAC_2004 Rule_17.1 & MISRAC_2004 Rule_17.4
                             * MISRAC_WAIVER:
                             * The if condition prevents any out of bound
                     .       * access
                             */

                            pWrite =  (UInt8*)handle->sharedMemBaseAddr
                                    + sizeof(System_IpcQueHeader)
                                    + (writeIdx * (handle->elementSize));

                            memcpy((void*)pWrite, (void*)data, dataSize);

                            /* move writeIdx */
                            pShm->curWr = (writeIdx+(UInt32)1U)%handle->maxElements;

                            /* dummy readback to ensure idx is written to memory */
                            writeIdx = pShm->curWr;
                        }

                        Hwi_restore(oldIntState);
                    }
                }
            }
        }
    }
    return status;

}

/**
 *******************************************************************************
 *
 * \brief Read data from the queue
 *
 *        'dataSize' MUST be <= to elementSize set during queue create
 *
 *        Reader should aware before hand what is size of element that it needs
 *        to read
 *
 *        Calling Utils_ipcQueRead() once is equivalent to removing  one element
 *        from the queue, even if dataSize < elementSize.
 *
 *        It is users responsibility to ensure it does not read partial elements
 *
 * \param handle             [IN]  queue handle
 * \param data               [IN]  local buffer into which data is read
 * \param dataSize           [IN]  amount of data to read from the queue
 *
 * \return TRUE, queue is empty
 *         FALSE, queue is not empty
 *
 *******************************************************************************
 */
Int32  Utils_ipcQueRead(const Utils_IpcQueHandle * handle,
                            volatile UInt8 *data,
                            volatile UInt32 dataSize)
{
    volatile UInt32 oldIntState;
    volatile System_IpcQueHeader *pShm;
    volatile UInt8 *pRead;
    volatile UInt32 readIdx;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if (handle == NULL)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        if(dataSize > (handle->elementSize))
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
        else
        {
            if ((handle->sharedMemBaseAddr) == NULL)
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
            else
            {

                pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

                if(     (pShm->maxElements != handle->maxElements)
                    ||  (pShm->elementSize != handle->elementSize)
                    )
                {
                    status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
                }
                else
                {
                    if(Utils_ipcQueIsEmpty(handle))
                    {
                        /* if queue is empty then return */
                        status = SYSTEM_LINK_STATUS_EAGAIN;
                    }
                    else
                    {
                        /* queue is not empty, read one element from the queue */
                        oldIntState = Hwi_disable();

                        readIdx = pShm->curRd;

                        if(readIdx < handle->maxElements)
                        {
                            /* MISRA.PTR.ARITH
                             * MISRAC_2004 Rule_17.1 & MISRAC_2004 Rule_17.4
                             * MISRAC_WAIVER:
                             * The if condition prevents any out of bound
                     .       * access
                             */
                            pRead =   (UInt8*)handle->sharedMemBaseAddr
                                    + sizeof(System_IpcQueHeader)
                                    + (readIdx * (handle->elementSize));

                            memcpy((void*)data, (void*)pRead, dataSize);

                            /* move readIdx */
                            pShm->curRd = (readIdx+(UInt32)1U)%handle->maxElements;

                            /* dummy readback to ensure idx is written to memory */
                            readIdx = pShm->curRd;
                        }
                        else
                        {
                              status = SYSTEM_LINK_STATUS_EFAIL;
                        }

                        Hwi_restore(oldIntState);
                    }
                }
            }
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Check if queue is empty
 *
 * \param handle             [IN]  queue handle
 *
 * \return TRUE, queue is empty
 *         FALSE, queue is not empty
 *
 *******************************************************************************
 */
UInt32 Utils_ipcQueIsEmpty(const Utils_IpcQueHandle * handle)
{
    volatile UInt32 oldIntState;
    volatile UInt32 readIdx, writeIdx;
    volatile System_IpcQueHeader *pShm;
    UInt32 isEmpty;

    if(    (handle == NULL)
        || (handle->sharedMemBaseAddr == NULL)
      )
    {
        isEmpty = (UInt32)FALSE;
    }
    else
    {
        pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

        oldIntState = Hwi_disable();

        readIdx = pShm->curRd;
        writeIdx = pShm->curWr;

        Hwi_restore(oldIntState);

        if( readIdx == writeIdx )
        {
            isEmpty = (UInt32)TRUE;
        }
        else
        {
            isEmpty = (UInt32)FALSE;
        }
    }

    return isEmpty;
}

/**
 *******************************************************************************
 *
 * \brief Check if queue is full
 *
 * \param handle             [IN]  queue handle
 *
 * \return TRUE, queue is full
 *         FALSE, queue is not full
 *
 *******************************************************************************
 */
UInt32 Utils_ipcQueIsFull(const Utils_IpcQueHandle * handle)
{
    volatile UInt32 oldIntState;
    volatile UInt32 readIdx, writeIdx, numFull;
    volatile System_IpcQueHeader *pShm;
    UInt32 isFull;

    if(    (handle == NULL                   )
        || (handle->sharedMemBaseAddr == NULL)
      )
    {
        isFull = (UInt32)FALSE;
    }
    else
    {

        pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

        oldIntState = Hwi_disable();

        readIdx = pShm->curRd;
        writeIdx = pShm->curWr;

        numFull = ((handle->maxElements - readIdx) + writeIdx)%handle->maxElements;

        Hwi_restore(oldIntState);

        if (numFull == (handle->maxElements-1U))
        {
            isFull = (UInt32)TRUE;
        }
        else
        {
            isFull = (UInt32)FALSE;
        }
    }

    return isFull;
}

Int32 Utils_ipcQueWriteString(const Utils_IpcQueHandle * handle, const char pString[])
{
    Int32 status = 0;
    volatile UInt32 maxBytes, numBytes, copyBytes;
    volatile UInt32 curWr, curRd, idx = 0U;
    volatile UInt8 *pDst;
    volatile System_IpcQueHeader *pShm;

    if (handle == NULL)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        if ((handle->sharedMemBaseAddr) == NULL)
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
        else
        {

            pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

            if(     (pShm->maxElements != handle->maxElements)
                ||  (pShm->elementSize != handle->elementSize)
                ||  (handle->elementSize != 1)
                )
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
        }
    }
    if (0 == status)
    {
        numBytes = strlen(pString);

        if (numBytes <= 0)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if (0 == status)
    {
        curWr = pShm->curWr;
        curRd = pShm->curRd;

        if (curWr < curRd)
        {
            maxBytes = curRd - curWr;
        }
        else
        {
            maxBytes = (handle->maxElements - curWr) + curRd;
        }

        if (numBytes > (maxBytes - 1U))
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if (0 == status)
    {
        pDst = (UInt8*)handle->sharedMemBaseAddr
                                    + sizeof(System_IpcQueHeader);

        for (copyBytes = 0; copyBytes < numBytes; copyBytes++)
        {
            if (curWr >= handle->maxElements)
            {
                curWr = 0;
            }
            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * Pointer is used in arithmetic or array index expression.
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Pointer is accessed as an array
             * Check is added to make sure that
             * pointer is never accessed beyond size of the array.
             */
            pDst[curWr] = (UInt8)pString[idx];
            curWr ++;
            idx ++;
        }

        if (curWr >= handle->maxElements)
        {
            curWr = 0U;
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * Pointer is used in arithmetic or array index expression.
         * KW State: Ignore -> Waiver -> Case by case
         * MISRAC_WAIVER:
         * Pointer is accessed as an array
         * Check is added to make sure that
         * pointer is never accessed beyond size of the array.
         */
        pDst[curWr] = 0U;
        curWr ++ ;

        if (curWr >= handle->maxElements)
        {
            curWr = 0U;
        }

        pShm->curWr = curWr;

        /* dummy read to resure data is written to memory */
        curWr = pShm->curWr;
    }

    return (status);
}

Int32 Utils_ipcQueReadString(const Utils_IpcQueHandle * handle, char pString[], UInt32 *strSize)
{
    Int32 status = 0;
    volatile UInt32 breakLoop;
    volatile UInt32 numBytes = 0U, copyBytes = 0U, curWr;
    volatile UInt32 curRd, idx = 0U;
    volatile UInt8 curChar;
    volatile UInt8 *pSrc;
    volatile System_IpcQueHeader *pShm;

    if (handle == NULL)
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        if ((handle->sharedMemBaseAddr) == NULL)
        {
            status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
        }
        else
        {

            pShm = (System_IpcQueHeader*)handle->sharedMemBaseAddr;

            if(     (pShm->maxElements != handle->maxElements)
                ||  (pShm->elementSize != handle->elementSize)
                ||  (handle->elementSize != 1)
                )
            {
                status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
            }
        }
    }
    if (0 == status)
    {
        curWr = pShm->curWr;
        curRd = pShm->curRd;

        if(curRd > curWr)
        {
            numBytes = (handle->maxElements - curRd) + curWr;
        }
        else
        {
            numBytes = curWr - curRd;
        }

        if(numBytes > 0U)
        {
            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * Pointer is used in arithmetic or array index expression.
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Pointer is initialized with the address of array variable and
             * then accessed as an array. Check is added to make sure that
             * pointer is never accessed beyond size of the array.
             */
            pSrc = (UInt8*)handle->sharedMemBaseAddr
                                    + sizeof(System_IpcQueHeader);

            for(copyBytes = 0U; copyBytes < numBytes; copyBytes ++)
            {
                if(curRd >= handle->maxElements)
                {
                    curRd = 0;
                }

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Pointer is initialized with the address of array variable and
                 * then accessed as an array
                 * Check is added to make sure that array/pointer access
                 * is never beyond its size
                 */
                curChar = pSrc[curRd];

                curRd++;

                if (curChar==(UInt8)0xA0)
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (curChar==(UInt8)'\r')
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (curChar==(UInt8)'\n')
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (curChar==(UInt8)0)
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (copyBytes >= handle->maxElements)
                {
                    breakLoop = (UInt32)TRUE;
                }
                else
                {
                    pString[idx] = (char)curChar;
                    idx ++;
                    breakLoop = (UInt32)FALSE;
                }

                if ((UInt32)TRUE == breakLoop)
                {
                    break;
                }
            }

            pShm->curRd = curRd;

            /* dummy read to resure data is written to memory */
            curRd = pShm->curRd;
        }

        pString[idx] = (char)0;
        *strSize = copyBytes;
    }

    return (Int32)numBytes;
}
