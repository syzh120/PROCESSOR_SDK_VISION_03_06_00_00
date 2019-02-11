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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_BUF_API Frame buffer exchange API
 *
 *  APIs defined in this file are used by links-and-chains example to exchange
 *  frames between two tasks
 *
 *  Internally this consists of two queues
 *  - empty or input queue
 *  - full or output queue
 *
 *  The queue implementation uses fixed size array based queue data structure,
 *  with mutual exclusion built inside the queue implementation.
 *
 *  Optional blocking of Get and/or Put operation is possible
 *
 *  The element that can be inserted/extracted from the queue is of
 *  type Fvid2_Frame *
 *
 *  The basic operation in the example is as below
 *
 *  - When a producer task needs to output some data, it first 'gets' a empty
 *    frame to output the data from the buffer handle.
 *  - The task outputs the data to the empty frame
 *  - The task then 'puts' this data as full data into the buffer handle
 *  - The consumer task, then 'gets' this full frame from the buffer handle
 *  - After using or consuming this frame, it 'puts' this frame as empty frame
 *    into this buffer handle.
 *  - This way frames are exchanged between a producer and consumer.
 *
 *  @{
 */

/**
 *  \file bsputils_buf.h
 *  \brief Frame buffer exchange API
 */

#ifndef BSPUTILS_BUF_H_
#define BSPUTILS_BUF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum size of buffer in the queue. */
#define BSPUTILS_BUF_MAX_QUE_SIZE       (FVID2_MAX_FRAME_PTR * 4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Frame Buffer Handle
 */
typedef struct
{
    BspUtils_QueHandle emptyQue;
    /**< Empty or input queue */
    BspUtils_QueHandle fullQue;
    /**< Full or output queue */
    Fvid2_Frame       *emptyQueMem[BSPUTILS_BUF_MAX_QUE_SIZE];
    /**< Memory for empty que data */
    Fvid2_Frame       *fullQueMem[BSPUTILS_BUF_MAX_QUE_SIZE];
    /**< Memory for empty que data */
} BspUtils_BufHndl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Create a frame buffer handle
 *
 *  When blockOnGet/blockOnPut is TRUE a semaphore gets allocated internally.
 *  In order to reduce resource usuage keep this as FALSE if application
 *  doesnt plan to use the blocking API feature.
 *
 *  \param pHndl        [OUT] Created handle
 *  \param blockOnGet   [IN]  Enable blocking on 'get' API
 *  \param blockOnPut   [IN]  Enable blocking on 'put' API
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufCreate(BspUtils_BufHndl *pHndl,
                         Bool              blockOnGet,
                         Bool              blockOnPut);

/**
 *  \brief Delete frame buffer handle
 *
 *  Free's resources like semaphore allocated during create
 *
 *  \param pHndl    [IN] Buffer handle
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufDelete(BspUtils_BufHndl *pHndl);

/**
 *  \brief Get frame's from empty queue
 *
 *  This API is used to get multiple frames in a single API call.
 *  Fvid2_FrameList.numFrames is set to number of frames
 *  that are returned.
 *
 *  When during create
 *  - 'blockOnGet' = TRUE
 *    - timeout can be BIOS_WAIT_FOREVER or BIOS_NO_WAIT
 *  - 'blockOnGet' = FALSE
 *    - timeout must be BIOS_NO_WAIT
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrameList   [OUT] Frame's returned by the API
 *  \param timeout      [IN] BIOS_NO_WAIT or BIOS_WAIT_FOREVER
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufGetEmpty(BspUtils_BufHndl *pHndl,
                           Fvid2_FrameList  *pFrameList,
                           UInt32            timeout);

/**
 *  \brief Put frame's into full queue
 *
 *  This API is used to return multiple frames in a single API call.
 *  Fvid2_FrameList.numFrames is set to number of frames
 *  that are to be returned.
 *
 *  When during create
 *  - 'blockOnPut' = TRUE
 *    - API will block until space is available in the queue to put the frames
 *  - 'blockOnPut' = FALSE
 *    - API will return error in case space is not available in the queue
 *      to put the frames
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrameList   [IN] Frame's to be put
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufPutFull(BspUtils_BufHndl *pHndl,
                          Fvid2_FrameList  *pFrameList);

/**
 *  \brief Get frame's from full queue
 *
 *  This API is used to get multiple frame's in a single API call.
 *  Fvid2_FrameList.numFrames is set to number of frames
 *  that are returned.
 *
 *  When during create
 *  - 'blockOnGet' = TRUE
 *    - timeout can be BIOS_WAIT_FOREVER or BIOS_NO_WAIT
 *  - 'blockOnGet' = FALSE
 *    - timeout must be BIOS_NO_WAIT
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrameList   [OUT] Frame's returned by the API
 *  \param timeout      [IN] BIOS_NO_WAIT or BIOS_WAIT_FOREVER
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufGetFull(BspUtils_BufHndl *pHndl,
                          Fvid2_FrameList  *pFrameList,
                          UInt32            timeout);

/**
 *  \brief Put frame's into empty queue
 *
 *  This API is used to return multiple frames in a single API call.
 *  Fvid2_FrameList.numFrames is set to number of frames
 *  that are to be returned.
 *
 *  When during create
 *  - 'blockOnPut' = TRUE
 *    - API will block until space is available in the queue to put the frames
 *  - 'blockOnPut' = FALSE
 *    - API will return error in case space is not available in the queue
 *      to put the frames
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrameList   [IN] Frame's to be put
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufPutEmpty(BspUtils_BufHndl *pHndl,
                           Fvid2_FrameList  *pFrameList);

/**
 *  \brief Get a frame from empty queue
 *
 *  Same as BspUtils_bufGetEmpty() except that only a single frame is returned
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrame       [OUT] Frame that is returned by the API
 *  \param timeout      [IN] BIOS_NO_WAIT or BIOS_WAIT_FOREVER
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufGetEmptyFrame(BspUtils_BufHndl *pHndl,
                                Fvid2_Frame     **pFrame,
                                UInt32            timeout);

/**
 *  \brief Get a frame from full queue
 *
 *  Same as BspUtils_bufGetFull() except that only a single frame is returned
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrame       [OUT] Frame that is returned by the API
 *  \param timeout      [IN] BIOS_NO_WAIT or BIOS_WAIT_FOREVER
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufGetFullFrame(BspUtils_BufHndl *pHndl,
                               Fvid2_Frame     **pFrame,
                               UInt32            timeout);

/**
 *  \brief Put a frame into full queue
 *
 *  Same as BspUtils_bufPutFull() except that only a single frame is put
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrame       [OUT] Frame that is to be returned to the queue
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufPutFullFrame(BspUtils_BufHndl *pHndl,
                               Fvid2_Frame      *pFrame);

/**
 *  \brief Put a frame into empty queue
 *
 *  Same as BspUtils_bufPutEmpty() except that only a single frame is put
 *
 *  \param pHndl        [IN] Buffer handle
 *  \param pFrame       [OUT] Frame that is to be returned to the queue
 *
 *  \return FVID2_SOK on success, else failure
 */
Int32 BspUtils_bufPutEmptyFrame(BspUtils_BufHndl *pHndl,
                                Fvid2_Frame      *pFrame);

/**
 *  \brief Peek into empty queue
 *
 *  This only peeks at the top of the queue but does not remove the
 *  frame from the queue
 *
 *  \param pHndl        [IN] Buffer handle
 *
 *  \return frame pointer is frame is present in the queue, else NULL
 */
static inline Fvid2_Frame *BspUtils_bufPeekEmpty(const BspUtils_BufHndl *pHndl);

/**
 *  \brief Peek into full queue
 *
 *  This only peeks at the top of the queue but does not remove the
 *  frame from the queue
 *
 *  \param pHndl        [IN] Buffer handle
 *
 *  \return frame pointer is frame is present in the queue, else NULL
 */
static inline Fvid2_Frame *BspUtils_bufPeekFull(const BspUtils_BufHndl *pHndl);

/* ========================================================================== */
/*                          Static Function Definition                        */
/* ========================================================================== */

static inline Fvid2_Frame *BspUtils_bufPeekEmpty(const BspUtils_BufHndl *pHndl)
{
    Fvid2_Frame *pFrame;

    BspUtils_quePeek(&pHndl->emptyQue, (Ptr *) &pFrame);

    return pFrame;
}

static inline Fvid2_Frame *BspUtils_bufPeekFull(const BspUtils_BufHndl *pHndl)
{
    Fvid2_Frame *pFrame;

    BspUtils_quePeek(&pHndl->fullQue, (Ptr *) &pFrame);

    return pFrame;
}

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_BUF_H_ */

/* @} */
