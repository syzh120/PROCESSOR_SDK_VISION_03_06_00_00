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
 *  \file bsputils_buf.c
 *
 *  \brief This file implements application level buffer handling functions.
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
#include <ti/drv/vps/include/fvid2/fvid2.h>
#include <ti/drv/vps/examples/utility/bsputils_buf.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 BspUtils_bufCreate(BspUtils_BufHndl *pHndl,
                         Bool              blockOnGet,
                         Bool              blockOnPut)
{
    Int32  status;
    UInt32 flags;

    flags = BSPUTILS_QUE_FLAG_NO_BLOCK_QUE;

    if (blockOnGet)
    {
        flags |= BSPUTILS_QUE_FLAG_BLOCK_QUE_GET;
    }
    if (blockOnPut)
    {
        flags |= BSPUTILS_QUE_FLAG_BLOCK_QUE_PUT;
    }

    status = BspUtils_queCreate(
        &pHndl->emptyQue,
        (UInt32) BSPUTILS_BUF_MAX_QUE_SIZE,
        pHndl->emptyQueMem,
        flags);
    GT_assert(GT_DEFAULT_MASK, status == FVID2_SOK);

    status = BspUtils_queCreate(
        &pHndl->fullQue,
        (UInt32) BSPUTILS_BUF_MAX_QUE_SIZE,
        pHndl->fullQueMem,
        flags);
    GT_assert(GT_DEFAULT_MASK, status == FVID2_SOK);

    return (status);
}

Int32 BspUtils_bufDelete(BspUtils_BufHndl *pHndl)
{
    BspUtils_queDelete(&pHndl->emptyQue);
    BspUtils_queDelete(&pHndl->fullQue);

    return FVID2_SOK;
}

Int32 BspUtils_bufGetEmpty(BspUtils_BufHndl *pHndl,
                           Fvid2_FrameList  *pFrameList,
                           UInt32            timeout)
{
    UInt32 idx, maxFrames;
    Int32  status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, pFrameList != NULL);

    if (timeout == BSP_OSAL_NO_WAIT)
    {
        maxFrames = FVID2_MAX_FRAME_PTR;
    }
    else
    {
        maxFrames = pFrameList->numFrames;
    }

    GT_assert(GT_DEFAULT_MASK, maxFrames <= FVID2_MAX_FRAME_PTR);

    for (idx = 0U; idx < maxFrames; idx++)
    {
        status = BspUtils_queGet(
            &pHndl->emptyQue,
            (Ptr *) &pFrameList->frames[idx],
            (UInt32) 1U,
            timeout);
        if (status != FVID2_SOK)
        {
            break;
        }
    }

    pFrameList->numFrames = idx;

    return (FVID2_SOK);
}

Int32 BspUtils_bufGetEmptyFrame(BspUtils_BufHndl *pHndl,
                                Fvid2_Frame     **pFrame,
                                UInt32            timeout)
{
    Int32 status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, pFrame != NULL);

    *pFrame = NULL;
    status  = BspUtils_queGet(&pHndl->emptyQue, (Ptr *) pFrame, (UInt32) 1U,
                              timeout);

    return (status);
}

Int32 BspUtils_bufPutEmpty(BspUtils_BufHndl *pHndl, Fvid2_FrameList *pFrameList)
{
    UInt32 idx;
    Int32  status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, pFrameList != NULL);
    GT_assert(GT_DEFAULT_MASK,
              (pFrameList->numFrames <= FVID2_MAX_FRAME_PTR));

    for (idx = 0U; idx < pFrameList->numFrames; idx++)
    {
        status = BspUtils_quePut(
            &pHndl->emptyQue,
            pFrameList->frames[idx],
            BSP_OSAL_NO_WAIT);
        GT_assert(GT_DEFAULT_MASK, status == FVID2_SOK);
    }

    return (FVID2_SOK);
}

Int32 BspUtils_bufPutEmptyFrame(BspUtils_BufHndl *pHndl, Fvid2_Frame *pFrame)
{
    Int32 status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);

    status = BspUtils_quePut(&pHndl->emptyQue, pFrame, BSP_OSAL_NO_WAIT);
    GT_assert(GT_DEFAULT_MASK, status == FVID2_SOK);

    return (FVID2_SOK);
}

Int32 BspUtils_bufGetFull(BspUtils_BufHndl *pHndl,
                          Fvid2_FrameList  *pFrameList,
                          UInt32            timeout)
{
    UInt32 idx, maxFrames;
    Int32  status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, pFrameList != NULL);

    if (timeout == BSP_OSAL_NO_WAIT)
    {
        maxFrames = FVID2_MAX_FRAME_PTR;
    }
    else
    {
        maxFrames = pFrameList->numFrames;
    }

    GT_assert(GT_DEFAULT_MASK, maxFrames <= FVID2_MAX_FRAME_PTR);

    for (idx = 0U; idx < maxFrames; idx++)
    {
        status = BspUtils_queGet(
            &pHndl->fullQue,
            (Ptr *) &pFrameList->frames[idx],
            (UInt32) 1U,
            timeout);
        if (status != FVID2_SOK)
        {
            break;
        }
    }

    pFrameList->numFrames = idx;

    return (FVID2_SOK);
}

Int32 BspUtils_bufGetFullFrame(BspUtils_BufHndl *pHndl,
                               Fvid2_Frame     **pFrame,
                               UInt32            timeout)
{
    Int32 status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, pFrame != NULL);

    *pFrame = NULL;
    status  = BspUtils_queGet(&pHndl->fullQue, (Ptr *) pFrame, (UInt32) 1U,
                              timeout);

    return (status);
}

Int32 BspUtils_bufPutFull(BspUtils_BufHndl *pHndl, Fvid2_FrameList *pFrameList)
{
    UInt32 idx;
    Int32  status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);
    GT_assert(GT_DEFAULT_MASK, pFrameList != NULL);
    GT_assert(GT_DEFAULT_MASK,
              (pFrameList->numFrames <= FVID2_MAX_FRAME_PTR));

    for (idx = 0; idx < pFrameList->numFrames; idx++)
    {
        status = BspUtils_quePut(
            &pHndl->fullQue,
            pFrameList->frames[idx],
            BSP_OSAL_NO_WAIT);
        GT_assert(GT_DEFAULT_MASK, status == FVID2_SOK);
    }

    return (FVID2_SOK);
}

Int32 BspUtils_bufPutFullFrame(BspUtils_BufHndl *pHndl, Fvid2_Frame *pFrame)
{
    Int32 status;

    GT_assert(GT_DEFAULT_MASK, pHndl != NULL);

    status = BspUtils_quePut(&pHndl->fullQue, pFrame, BSP_OSAL_NO_WAIT);
    if (status != FVID2_SOK)
    {
        #if 0
        Bsp_rprintf(
            "%d: ERROR: In BspUtils_bufPutFullFrame(), "
            "BspUtils_quePut() failed !!!\r\n",
            BspOsal_getCurTimeInMsec());
        #endif
    }

    return (status);
}

