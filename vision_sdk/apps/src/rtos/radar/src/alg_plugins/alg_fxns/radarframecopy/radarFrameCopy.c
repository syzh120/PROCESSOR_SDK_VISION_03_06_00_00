/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 * \file    RadarFrameCopy.c
 *
 * \brief  This file contains algorithm functions for drawing the radar related
 *         metadata output on the display.
 *
 * \version 0.0 (Sept 2016) : [PG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "radarFrameCopy_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 * \brief   Global structure containing Algorithm Functions
 *******************************************************************************
 */
static AlgRadarProcessFxns_FxnTable gAlgorithmFxn_RadarFrameCopy_fxns =
{
    &AlgorithmFxn_RadarFrameCopyCreate,
    &AlgorithmFxn_RadarFrameCopyProcess,
    &AlgorithmFxn_RadarFrameCopyControl,
    &AlgorithmFxn_RadarFrameCopyDelete
};

/**
 *******************************************************************************
 *
 * \brief Implementation of get functions for the algorithm functions
 *
 *        This function will be called to get the pointer to the table of
 *        functions which correspond to this algorithm.
 *
 * \return  AlgRadarProcessFxns_FxnTable pointer.
 *
 *******************************************************************************
 */
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarFrameCopy_getFunctions(void)
{
    return &gAlgorithmFxn_RadarFrameCopy_fxns;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for radar draw
 *
 *  \param createParams Create Parameters corresponding to the algorithm
 *                      function.
 *
 *  \param opParams     These parameters are provided from the algorithm fxn to
 *                      the alg plugin to allow for the alg plugin to know
 *                      alg function specific requirements with respect to
 *                      output buffer size and type.
 *
 *  \return algHandle   This function is expected to allocate memory for the
 *                      algorithm handle. This handle is later used by the alg
 *                      function during process and delete calls.
 *
 *******************************************************************************
 */
void * AlgorithmFxn_RadarFrameCopyCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams)
{
    AlgorithmFxn_RadarFrameCopyCreateParams      * pLinkCreateParams;
    System_LinkChInfo * pOutChInfo;
    AlgorithmFxn_RadarFrameCopyObj * pAlgFxnObj;
    System_LinkInfo              prevLinkInfo;
    UInt32                       prevLinkQueId;
    UInt32 chId;

    pLinkCreateParams = (AlgorithmFxn_RadarFrameCopyCreateParams *)createParams;

    pAlgFxnObj = (AlgorithmFxn_RadarFrameCopyObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmFxn_RadarFrameCopyObj), 32);
    UTILS_assert(pAlgFxnObj != NULL);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy(
            (void*)(&pAlgFxnObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmFxn_RadarFrameCopyCreateParams)
           );

    /* Fill the output buffer information */
    for (chId = 0; chId < SYSTEM_MAX_CH_PER_OUT_QUE; chId++)
    {
        pOutChInfo          = &opParams->outputChannelInfo[chId];

        pOutChInfo->height = pLinkCreateParams->imgFrameHeight;
        pOutChInfo->width  = pLinkCreateParams->imgFrameWidth;
        pOutChInfo->startX = 0;
        pOutChInfo->startY = 0;
        pOutChInfo->flags  = 0;

        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
                                                pOutChInfo->flags,
                                                SYSTEM_SF_PROGRESSIVE);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Mem_Type(
                                                pOutChInfo->flags,
                                                SYSTEM_MT_NONTILEDMEM);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(
                                                pOutChInfo->flags,
                                                pLinkCreateParams->dataFormat);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
                                                pOutChInfo->flags,
                                                SYSTEM_BUFFER_TYPE_VIDEO_FRAME);

        pOutChInfo->pitch[0] = pLinkCreateParams->outputBufferpitch;
        pOutChInfo->pitch[1] = pOutChInfo->pitch[0];
        pOutChInfo->pitch[2] = pOutChInfo->pitch[0];
        pAlgFxnObj->pitch = pOutChInfo->pitch[0];

        opParams->outputBufferSize[chId] = pOutChInfo->pitch[0] * pOutChInfo->height * 4;
    }
    opParams->outputBufferType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;

    System_linkGetInfo(createParams->inQueParams.prevLinkId,
                                &prevLinkInfo);
    prevLinkQueId = createParams->inQueParams.prevLinkQueId;
    opParams->numOutputCh = prevLinkInfo.queInfo[prevLinkQueId].numCh;
    memcpy(&pAlgFxnObj->prevChInfo, &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]),
            sizeof(System_LinkChInfo)
           );

    return (void *) pAlgFxnObj;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process function for radar draw
 *
 *  \param  alg_handle      Algorithm Handle which was created during the create
 *                          algorithm function call.
 *  \param  in_buf          Input buffer pointer.
 *  \param  out_buf         Output buffer pointer.
 *
 *  \return status          Status of the success or failure of the process
 *                          operations.
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarFrameCopyProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf)
{
    Int32                          status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarFrameCopyObj *pAlgFxnObj;
    System_VideoFrameBuffer        *pInputVideoBuffer;
    System_VideoFrameBuffer        *pOutputVideoBuffer;
    UInt8                          *inBufAddr, *outBufAddr;

    System_LinkChInfo *pInputChInfo;
    UInt32            inWidth, inHeight, inpitch;
    UInt32            rowIdx, colIdx;

    pAlgFxnObj = (AlgorithmFxn_RadarFrameCopyObj *)alg_handle;

    pInputVideoBuffer   = (System_VideoFrameBuffer *) in_buf->payload;
    inBufAddr           = (UInt8 *)pInputVideoBuffer->bufAddr[0];
    pOutputVideoBuffer  = (System_VideoFrameBuffer *)out_buf->payload;
    outBufAddr          = (UInt8 *)pOutputVideoBuffer->bufAddr[0];

    pInputChInfo = &pAlgFxnObj->prevChInfo;
    inWidth      = pInputChInfo->width;
    inHeight     = pInputChInfo->height;
    inpitch      = pInputChInfo->pitch[0];

    if(pAlgFxnObj->algLinkCreateParams.dataFormat == SYSTEM_DF_BAYER_BGGR)
    {
        inWidth = (inWidth*2);
    }
    else
    {
        return SYSTEM_LINK_STATUS_EFAIL;
    }

    for(rowIdx = 0; rowIdx < inHeight ; rowIdx++)
    {
        for(colIdx = 0; colIdx < inWidth ; colIdx++)
        {
            *(outBufAddr+colIdx) = *(inBufAddr+colIdx);
        }
        inBufAddr += inpitch;
        outBufAddr += pAlgFxnObj->pitch;
    }

    return status;
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Control function for radar draw
 *
 *  \param  alg_handle      Algorithm Handle which was created during the create
 *  \param  controlParams   Control parameters which can change the algorithm
 *                          parameters at run time.
 *
 *  \return status          Status of the success or failure of the control
 *                          operations.
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarFrameCopyControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams)
{
    return SYSTEM_LINK_STATUS_SOK;
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Delete function for radar draw
 *
 *  \param  alg_handle  Algorithm Handle which was created during the create
 *                      algorithm function call.
 *
 *  \return status      Status of the success or failure of the process
 *                      operations.
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarFrameCopyDelete(void *alg_handle)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarFrameCopyObj                   * pAlgFxnObj;

    pAlgFxnObj = (AlgorithmFxn_RadarFrameCopyObj *)alg_handle;

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                  pAlgFxnObj,
                  sizeof(AlgorithmFxn_RadarFrameCopyObj)
                    );

    return status;
}
