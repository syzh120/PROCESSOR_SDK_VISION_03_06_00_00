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
 * \file bsp_utilsQue.c
 *
 * \brief Utils layer - Array based queue
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/common/bsp_utilsQue.h>

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

static void queExtractElement(BspUtils_QueHandle *handle, Ptr *data);
static void queInsertElement(BspUtils_QueHandle *handle, Ptr data);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* See bsp_utilsQue.h for function documentation  */
Int32 BspUtils_queCreate(BspUtils_QueHandle *handle,
                         UInt32              maxElements,
                         Ptr                 queueMem,
                         UInt32              flags)
{
    /* init handle to 0's */
    BspUtils_memset(handle, 0, sizeof (*handle));

    /*
     * init handle with user parameters
     */
    handle->maxElements = maxElements;
    handle->flags       = flags;

    /*
     * queue data element memory cannot be NULL
     */
    GT_assert(BspUtilsTrace, (queueMem != NULL));

    handle->queue = (Ptr *) queueMem;
    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
    {
        /*
         * user requested block on que get
         * create semaphore for it
         */
        handle->semRd = BspOsal_semCreate(0, FALSE);
        GT_assert(BspUtilsTrace, (handle->semRd != NULL));
    }

    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
    {
        /*
         * user requested block on que put
         * create semaphore for it
         */
        handle->semWr = BspOsal_semCreate((Int32) maxElements, FALSE);
        GT_assert(BspUtilsTrace, (handle->semWr != NULL));
    }

    return (BSP_SOK);
}

Int32 BspUtils_queDelete(BspUtils_QueHandle *handle)
{
    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
    {
        /*
         * user requested block on que get
         * delete associated semaphore
         */
        BspOsal_semDelete(&handle->semRd);
    }
    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
    {
        /*
         * user requested block on que put
         * delete associated semaphore
         */
        BspOsal_semDelete(&handle->semWr);
    }

    return (BSP_SOK);
}
static void queInsertElement(BspUtils_QueHandle *handle, Ptr data)
{
    /* insert element */
    handle->queue[handle->curWr] = data;

    /* increment put pointer */
    handle->curWr = (handle->curWr + 1) % handle->maxElements;

    /* increment count of number element in que */
    handle->count++;

}

Int32 BspUtils_quePut(BspUtils_QueHandle *handle, Ptr data, UInt32 timeout)
{
    Int32  status = BSP_EFAIL;               /* init status to error */
    UInt32 cookie;

    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
    {
        if (!BspOsal_semWait(handle->semWr, timeout))
        {
            /* timeout happend, exit with error  */
        }
        else
        {
            /* Semaphore is aquired. Insert element in queue. */
            /* disable interrupts */
            cookie = BspOsal_disableInterrupt();
            
            queInsertElement(handle, data);

            if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
            {
                /* blocking on que get enabled.
                 * post semaphore to unblock, blocked tasks.
                 */
                BspOsal_semPost(handle->semRd);
            }

            /* exit, with success */
            status = BSP_SOK;

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);
        }
    }
    else
    {
        /* disable interrupts */
        cookie = BspOsal_disableInterrupt();
        if (handle->count < handle->maxElements)
        {
            /* Free space available in queue. Insert the element. */
            queInsertElement(handle, data);

            if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
            {
                /* blocking on que get enabled.
                 * post semaphore to unblock, blocked tasks.
                 */
                BspOsal_semPost(handle->semRd);
            }

            /* exit, with success */
            status = BSP_SOK;

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);
        }
        else
        {
            /* que is full. exit with error  */
            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);
        }
    }

    return (status);
}

static void queExtractElement(BspUtils_QueHandle *handle, Ptr *data)
{
    /* extract the element */
    *data = handle->queue[handle->curRd];

    /* increment get pointer */
    handle->curRd = (handle->curRd + 1) % handle->maxElements;

    /* decrmeent number of elements in que */
    handle->count--;
}

Int32 BspUtils_queGet(BspUtils_QueHandle *handle,
                      Ptr                *data,
                      UInt32              minCount,
                      UInt32              timeout)
{
    Int32  status = BSP_EFAIL;               /* init status to error */
    UInt32 cookie;

    /*
     * adjust minCount between 1 and handle->maxElements
     */
    if (0U == minCount)
    {
        minCount = 1U;
    }
    if (minCount > handle->maxElements)
    {
        minCount = handle->maxElements;
    }

    
    if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_GET)
    {
        if (!BspOsal_semWait(handle->semRd, timeout))
        {
            /* timeout happend, exit with error. */
        }
        else
        {
            /* disable interrupts */
            cookie = BspOsal_disableInterrupt();
            
            /* rdSem is aquired extract the element from queue. */
            queExtractElement(handle, data);

            if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
            {
                /* blocking on que get enabled.
                 * post semaphore to unblock, blocked tasks.
                 */
                BspOsal_semPost(handle->semWr);
            }
            /* exit, with success */
            status = BSP_SOK;

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);
        }
    }
    else
    {
        /* disable interrupts */
        cookie = BspOsal_disableInterrupt();
        if (handle->count >= minCount)
        {
            /*
             * data elements available in que is >=
             * minimum data elements requested by user
             */
            queExtractElement(handle, data);

            /* set status as success */
            status = BSP_SOK;

            if (handle->flags & BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT)
            {
                /* post semaphore to unblock, blocked tasks */
                BspOsal_semPost(handle->semWr);
            }

            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);
        }
        else
        {
            /*
             * no elements or not enough element (minCount) in que to extract.
             * Exit with error.
             */
            /* restore interrupts */
            BspOsal_restoreInterrupt(cookie);

        }
    }

    return (status);
}

UInt32 BspUtils_queIsEmpty(const BspUtils_QueHandle *handle)
{
    UInt32 isEmpty;
    UInt32 cookie;

    /* disable interrupts */
    cookie = BspOsal_disableInterrupt();

    /* check if que is empty */
    if (handle->count)
    {
        isEmpty = (UInt32) FALSE;    /* not empty  */
    }
    else
    {
        isEmpty = (UInt32) TRUE;     /* empty  */
    }

    /* restore interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (isEmpty);
}

Int32 BspUtils_quePeek(const BspUtils_QueHandle *handle, Ptr *data)
{
    Int32  status = BSP_EFAIL;               /* init status as error  */
    UInt32 cookie;

    *data = NULL;

    /* disable interrupts */
    cookie = BspOsal_disableInterrupt();

    if (handle->count)
    {
        /*
         * que is not empty
         */

        /* get value of top element, but do not extract it from que */
        *data = handle->queue[handle->curRd];

        /* set status as success */
        status = BSP_SOK;
    }

    /* restore interrupts */
    BspOsal_restoreInterrupt(cookie);

    return (status);
}

