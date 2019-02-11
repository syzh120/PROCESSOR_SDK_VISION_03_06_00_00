/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|        Copyright (c) 2017 Texas Instruments Incorporated                 |**
**|                                                                          |**
**|              All rights reserved not granted herein.                     |**
**|                                                                          |**
**|                         Limited License.                                 |**
**|                                                                          |**
**|  Texas Instruments Incorporated grants a world-wide, royalty-free,       |**
**|  non-exclusive license under copyrights and patents it now or            |**
**|  hereafter owns or controls to make, have made, use, import, offer to    |**
**|  sell and sell ("Utilize") this software subject to the terms herein.    |**
**|  With respect to the foregoing patent license, such license is granted   |**
**|  solely to the extent that any such patent is necessary to Utilize the   |**
**|  software alone.  The patent license shall not apply to any              |**
**|  combinations which include this software, other than combinations       |**
**|  with devices manufactured by or for TI ("TI Devices").  No hardware     |**
**|  patent is licensed hereunder.                                           |**
**|                                                                          |**
**|  Redistributions must preserve existing copyright notices and            |**
**|  reproduce this license (including the above copyright notice and the    |**
**|  disclaimer and (if applicable) source code license limitations below)   |**
**|  in the documentation and/or other materials provided with the           |**
**|  distribution                                                            |**
**|                                                                          |**
**|  Redistribution and use in binary form, without modification, are        |**
**|  permitted provided that the following conditions are met:               |**
**|                                                                          |**
**|    *  No reverse engineering, decompilation, or disassembly of this      |**
**|  software is permitted with respect to any software provided in binary   |**
**|  form.                                                                   |**
**|                                                                          |**
**|    *  any redistribution and use are licensed by TI for use only with    |**
**|  TI Devices.                                                             |**
**|                                                                          |**
**|    *  Nothing shall obligate TI to provide you with source code for      |**
**|  the software licensed and provided to you in object code.               |**
**|                                                                          |**
**|  If software source code is provided to you, modification and            |**
**|  redistribution of the source code are permitted provided that the       |**
**|  following conditions are met:                                           |**
**|                                                                          |**
**|    *  any redistribution and use of the source code, including any       |**
**|  resulting derivative works, are licensed by TI for use only with TI     |**
**|  Devices.                                                                |**
**|                                                                          |**
**|    *  any redistribution and use of any object code compiled from the    |**
**|  source code and any resulting derivative works, are licensed by TI      |**
**|  for use only with TI Devices.                                           |**
**|                                                                          |**
**|  Neither the name of Texas Instruments Incorporated nor the names of     |**
**|  its suppliers may be used to endorse or promote products derived from   |**
**|  this software without specific prior written permission.                |**
**|                                                                          |**
**|  DISCLAIMER.                                                             |**
**|                                                                          |**
**|  THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY      |**
**|  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE       |**
**|  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      |**
**|  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE      |**
**|  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR     |**
**|  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF    |**
**|  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR         |**
**|  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,   |**
**|  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE    |**
**|  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,       |**
**|  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#include "cpu.h"
#include "BAM_VXLIB_doubleThreshold_i16u_i8u_int.h"
#include "../VXLIB_doubleThreshold_i16u_i8u.h"

/***********************************************************************************************/
/*  Below are the helper  functions related to VXLIB_doubleThreshold_i16u_i8u kernel            */
/***********************************************************************************************/
static BAM_Status BAM_VXLIB_doubleThreshold_i16u_i8u_initFrame(void *kernelContext);
static BAM_Status BAM_VXLIB_doubleThreshold_i16u_i8u_compute(void *kernelContext);
static BAM_Status BAM_VXLIB_doubleThreshold_i16u_i8u_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_VXLIB_doubleThreshold_i16u_i8u_initFrame(void *kernelContext)
{
    BAM_VXLIB_doubleThreshold_i16u_i8u_Context *context = \
                            (BAM_VXLIB_doubleThreshold_i16u_i8u_Context *)kernelContext;

    context->blockContext.blkCntTotal = context->blockContext.numBlocksTotal;
    context->blockContext.blkCntHorz = 0;
    context->blockContext.blkCntVert = 1;

    context->bufParamsLast[0].dim_x = context->lastSize.lastWidth;
    context->bufParamsLast[0].dim_y = context->kernelInitArgs.bufParams[0].dim_y;

    context->bufParamsLast[1].dim_x = context->lastSize.lastWidth;
    context->bufParamsLast[1].dim_y = context->kernelInitArgs.bufParams[1].dim_y;

    context->numEdges = 0;

    return BAM_S_SUCCESS;
}

static BAM_Status BAM_VXLIB_doubleThreshold_i16u_i8u_compute(void *kernelContext)
{
    BAM_VXLIB_doubleThreshold_i16u_i8u_Context *context = \
                            (BAM_VXLIB_doubleThreshold_i16u_i8u_Context *)kernelContext;

    uint32_t numItems = 0;
    uint32_t *edgeList_t;
    uint32_t startPosition;
    uint32_t localCapacity;
    VXLIB_bufParams2D_t *bufParams[2];
    VXLIB_STATUS    status_vx;
    BAM_Status     status_bam = BAM_S_SUCCESS;

    /* HACK: For now assume that we need to index into magnitude buffer by one line and 1 pixel (graph dependent) */
    uint16_t *pMag = (uint16_t*)context->pInBlock[BAM_VXLIB_DOUBLETHRESHOLD_I16S_I8U_INPUT_MAG_PORT];
    pMag = &pMag[(context->kernelInitArgs.bufParams[0].stride_y/2) + 1];

    startPosition = (((context->blockContext.blkCntVert-1U) * context->kernelInitArgs.bufParams[1].dim_y) *
                      context->kernelInitArgs.params.edgeMapLineOffset) +
                      (context->blockContext.blkCntHorz * context->kernelInitArgs.bufParams[1].dim_x);

    bufParams[0] = &context->kernelInitArgs.bufParams[0];
    bufParams[1] = &context->kernelInitArgs.bufParams[1];

    context->blockContext.blkCntTotal--;
    context->blockContext.blkCntHorz++;

    if(context->blockContext.equalSizeFlag == 0)
    {
        if(0 == context->blockContext.blkCntTotal)
        {
            context->bufParamsLast[0].dim_x = context->lastSize.lastWidth;
            context->bufParamsLast[0].dim_y = context->lastSize.lastHeight;
            context->bufParamsLast[1].dim_x = context->lastSize.lastWidth;
            context->bufParamsLast[1].dim_y = context->lastSize.lastHeight;
            bufParams[0] = &context->bufParamsLast[0];
            bufParams[1] = &context->bufParamsLast[1];
        }
        else if(context->blockContext.blkCntHorz == context->blockContext.numBlocksHorz)
        {
            bufParams[0] = &context->bufParamsLast[0];
            bufParams[1] = &context->bufParamsLast[1];
            context->blockContext.blkCntHorz = 0;
            context->blockContext.blkCntVert++;
        }
        else if(context->blockContext.blkCntVert == context->blockContext.numBlocksVert)
        {
            context->bufParamsLast[0].dim_x = context->kernelInitArgs.bufParams[0].dim_x;
            context->bufParamsLast[0].dim_y = context->lastSize.lastHeight;
            context->bufParamsLast[1].dim_x = context->kernelInitArgs.bufParams[1].dim_x;
            context->bufParamsLast[1].dim_y = context->lastSize.lastHeight;
            bufParams[0] = &context->bufParamsLast[0];
            bufParams[1] = &context->bufParamsLast[1];
        }
        else
        {
            /* Do nothing, MISRAC requirement */
        }
    }

    edgeList_t    = (uint32_t *)&context->kernelInitArgs.params.edgeList[ context->numEdges ];

    localCapacity = context->kernelInitArgs.params.edgeListCapacity - context->numEdges;

    status_vx = VXLIB_doubleThreshold_i16u_i8u((const uint16_t*)pMag,
                               bufParams[0],
                               (uint8_t*)context->pInBlock[BAM_VXLIB_DOUBLETHRESHOLD_I16S_I8U_INPUT_EDGEMAP_PORT],
                               bufParams[1],
                               context->kernelInitArgs.params.edgeMapLineOffset,
                               edgeList_t,
                               localCapacity,
                               &numItems,
                               startPosition,
                               context->kernelInitArgs.params.loThreshold,
                               context->kernelInitArgs.params.hiThreshold);

    context->numEdges += numItems;

    if( status_vx != VXLIB_SUCCESS )
    {
        status_bam = BAM_E_FAIL_RUNTIME;
    }

    return status_bam;
}

static BAM_Status BAM_VXLIB_doubleThreshold_i16u_i8u_control(void *kernelContext, void *kernelCtlArg)
{
    BAM_Status status = BAM_E_UNSUPPORTED;

    BAM_VXLIB_doubleThreshold_i16u_i8u_Context *context = \
                            (BAM_VXLIB_doubleThreshold_i16u_i8u_Context *)kernelContext;

    BAM_KernelCommonControlArgs *message = \
                            (BAM_KernelCommonControlArgs *)kernelCtlArg;

    BAM_KernelCommonControlFrameArgs *ctrlArgs = \
                            (BAM_KernelCommonControlFrameArgs *)message->payload;

    if (message->cmdId == BAM_CTRL_CMD_ID_SET_FRAME_ARGS)
    {
        uint16_t lastWidth, lastHeight;

        context->blockContext.numBlocksHorz = ((ctrlArgs->frameWidth-1) / ctrlArgs->blockWidth) + 1;
        context->blockContext.numBlocksVert = ((ctrlArgs->frameHeight-1) / ctrlArgs->blockHeight) + 1;
        context->blockContext.numBlocksTotal = context->blockContext.numBlocksHorz * context->blockContext.numBlocksVert;

        lastWidth = (uint16_t)(ctrlArgs->frameWidth - ((context->blockContext.numBlocksHorz-1) * ctrlArgs->blockWidth));
        lastHeight = (uint16_t)(ctrlArgs->frameHeight - ((context->blockContext.numBlocksVert-1) * ctrlArgs->blockHeight));

        if((lastWidth == ctrlArgs->blockWidth) && (lastHeight == ctrlArgs->blockHeight))
        {
            context->blockContext.equalSizeFlag = 1U;
        }
        else
        {
            context->blockContext.equalSizeFlag = 0U;
        }

        memcpy(&context->bufParamsLast[0], &context->kernelInitArgs.bufParams[0], sizeof(VXLIB_bufParams2D_t));
        memcpy(&context->bufParamsLast[1], &context->kernelInitArgs.bufParams[1], sizeof(VXLIB_bufParams2D_t));

        context->lastSize.lastWidth = lastWidth;
        context->lastSize.lastHeight = lastHeight;

        status = BAM_S_SUCCESS;
    }
    else if (message->cmdId == VXLIB_DOUBLETHRESHOLD_I16U_I8U_CMD_SET_EDGE_LIST_PTR)
    {
        context->kernelInitArgs.params.edgeList = (uint32_t *)message->payload;

        status = BAM_S_SUCCESS;
    }
    else if(message->cmdId == VXLIB_DOUBLETHRESHOLD_I16U_I8U_CMD_GET_NUM_EDGES)
    {
        *(uint32_t*)message->payload = context->numEdges;

        status = BAM_S_SUCCESS;
    }
    else
    {
        /* Do nothing, MISRAC requirement */
    }


    return status;
}

BAM_KernelExecFuncDef gBAM_VXLIB_doubleThreshold_i16u_i8u_execFunc =
{
    NULL,
    &BAM_VXLIB_doubleThreshold_i16u_i8u_initFrame,
    &BAM_VXLIB_doubleThreshold_i16u_i8u_compute,
    NULL,
    &BAM_VXLIB_doubleThreshold_i16u_i8u_control,
    NULL
};
