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
 * \file openvx.c
 *
 * \brief  This file implements Actual OpenVX graph processing.
 *         It creates the graph with the single Harris Corners node and
 *         executes the graph for the YUV420 input image.
 *
 * \version 0.0 (March 2017) : [BJ] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "openvxLink_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/* */
#define OPENVX_DRAW_BLOCK_SIZE  (5u)

/* Create openvx graph and other data objects required for the graph */
Int32 openvxCreate(AlgorithmLink_OpenVxObj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    vx_status vxStatus;
    UInt32 cnt;
    AlgorithmLink_OpenVxCreateParams *pCreatePrms;
    AlgorithmLink_GraphObj *gObj;
    System_LinkChInfo *inChInfo;

    UTILS_assert(NULL != pObj);
    pCreatePrms = &pObj->createPrms;
    UTILS_assert(NULL != pCreatePrms);

    pObj->context = vxCreateContext();
    if (vxGetStatus((vx_reference)pObj->context) != VX_SUCCESS)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        inChInfo = &pObj->inChInfo;

        for (cnt = 0u; cnt < pCreatePrms->numOutputFrames; cnt ++)
        {
            gObj = &pObj->graph[cnt];

            memset(gObj, 0, sizeof(AlgorithmLink_GraphObj));

            gObj->graph = vxCreateGraph(pObj->context);
            if (vxGetStatus((vx_reference)gObj->graph) != VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            gObj->img = vxCreateImage(pObj->context, inChInfo->width,
                inChInfo->height, VX_DF_IMAGE_U8);
            if (vxGetStatus((vx_reference)gObj->img) != VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            gObj->scStrengthThr = vxCreateScalar(pObj->context,
                VX_TYPE_FLOAT32, &pCreatePrms->hcPrms.strength_thr);
            if (vxGetStatus((vx_reference)gObj->scStrengthThr) != VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            gObj->scMinDist = vxCreateScalar(pObj->context,
                VX_TYPE_FLOAT32, &pCreatePrms->hcPrms.min_dist);
            if (vxGetStatus((vx_reference)gObj->scMinDist) != VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            gObj->scSensitivity = vxCreateScalar(pObj->context,
                VX_TYPE_FLOAT32, &pCreatePrms->hcPrms.sensitivity);
            if (vxGetStatus((vx_reference)gObj->scSensitivity) !=
                    VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            gObj->scNumCorners = vxCreateScalar(pObj->context,
                VX_TYPE_SIZE, &pCreatePrms->hcPrms.max_corners);
            if (vxGetStatus((vx_reference)gObj->scNumCorners) !=
                    VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            gObj->arr = vxCreateArray(pObj->context, VX_TYPE_KEYPOINT,
                pCreatePrms->hcPrms.max_corners);
            if (vxGetStatus((vx_reference)gObj->arr) != VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            gObj->node = vxHarrisCornersNode(gObj->graph, gObj->img,
                gObj->scStrengthThr, gObj->scMinDist, gObj->scSensitivity,
                pCreatePrms->hcPrms.grad_size, pCreatePrms->hcPrms.block_size,
                gObj->arr, gObj->scNumCorners);
            if (vxGetStatus((vx_reference)gObj->node) != VX_SUCCESS)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }

            /* Verify the graph */
            vxStatus = vxVerifyGraph(gObj->graph);
            if (VX_SUCCESS != vxStatus)
            {
                status = SYSTEM_LINK_STATUS_EFAIL;
                break;
            }
        }

        if (0 != status)
        {
            openvxDelete(pObj);
        }
        else
        {
            pObj->vxImgAddr.dim_x = inChInfo->width;
            pObj->vxImgAddr.dim_y = inChInfo->height;
            pObj->vxImgAddr.stride_x = 1u;
            pObj->vxImgAddr.stride_y = inChInfo->pitch[0u];
            pObj->vxImgAddr.step_x = 1u;
            pObj->vxImgAddr.step_y = 1u;
        }
    }

    return (status);
}

/* Delete OpenVX Graph and other data objects */
Void openvxDelete(AlgorithmLink_OpenVxObj *pObj)
{
    UInt32 cnt;
    AlgorithmLink_OpenVxCreateParams *pCreatePrms;
    AlgorithmLink_GraphObj *gObj;
    void *old_ptr;
    vx_status vxStatus;

    UTILS_assert(NULL != pObj);
    pCreatePrms = &pObj->createPrms;
    UTILS_assert(NULL != pCreatePrms);

    for (cnt = 0u; cnt < pCreatePrms->numOutputFrames; cnt ++)
    {
        gObj = &pObj->graph[cnt];

        if (vxGetStatus((vx_reference)gObj->img) == VX_SUCCESS)
        {
            /* First get back the buffers, so that OpenVX does not free
               capture buffers */
            vxStatus = vxSwapImageHandle(gObj->img, NULL, &old_ptr, 1u);
            UTILS_assert(VX_SUCCESS == vxStatus);

            vxReleaseImage(&gObj->img);
        }

        if (vxGetStatus((vx_reference)gObj->scStrengthThr) == VX_SUCCESS)
        {
            vxReleaseScalar(&gObj->scStrengthThr);
        }

        if (vxGetStatus((vx_reference)gObj->scMinDist) == VX_SUCCESS)
        {
            vxReleaseScalar(&gObj->scMinDist);
        }

        if (vxGetStatus((vx_reference)gObj->scSensitivity) == VX_SUCCESS)
        {
            vxReleaseScalar(&gObj->scSensitivity);
        }

        if (vxGetStatus((vx_reference)gObj->scNumCorners) == VX_SUCCESS)
        {
            vxReleaseScalar(&gObj->scNumCorners);
        }

        if (vxGetStatus((vx_reference)gObj->arr) == VX_SUCCESS)
        {
            vxReleaseArray(&gObj->arr);
        }

        if (vxGetStatus((vx_reference)gObj->node) == VX_SUCCESS)
        {
            vxReleaseNode(&gObj->node);
        }

        if (vxGetStatus((vx_reference)gObj->graph) == VX_SUCCESS)
        {
            vxReleaseGraph(&gObj->graph);
        }
    }

    if (vxGetStatus((vx_reference)pObj->context) == VX_SUCCESS)
    {
        vxReleaseContext(&pObj->context);
    }
}

/* Executes the openvx graph */
Void openvxProcess(AlgorithmLink_OpenVxObj *pObj,
    AlgorithmLink_GraphObj *pGraphObj, System_VideoFrameBuffer *pVidFrm)
{
    vx_status vxStatus;

    UTILS_assert(NULL != pObj);
    UTILS_assert(NULL != pGraphObj);
    UTILS_assert(NULL != pVidFrm);

    /* Use captured image as the source image in the image data object */
    vxStatus = vxSwapImageHandle(pGraphObj->img, &pVidFrm->bufAddr[0],
        NULL, 1u);
    UTILS_assert(VX_SUCCESS == vxStatus);

    /* Process Graph */
    vxStatus = vxProcessGraph(pGraphObj->graph);
    UTILS_assert(VX_SUCCESS == vxStatus);
}

Void drawCorners(AlgorithmLink_OpenVxObj *pObj,
    AlgorithmLink_GraphObj *pGraphObj, System_VideoFrameBuffer *pVidFrm)
{
    UInt32 cnt, i, j;
    vx_status vxStatus;
    vx_size arrSize;
    vx_map_id arrMapId;
    vx_size stride = sizeof(vx_keypoint_t);
    void *arrBase = NULL;
    UInt8 *lumaAddr, *chromaAddr;
    UInt16 *ptr1;
    UInt16 *ptr2;
    vx_int32 x, y;

    vxStatus = vxQueryArray(pGraphObj->arr, VX_ARRAY_NUMITEMS, &arrSize, sizeof(arrSize));
    if (vxStatus == VX_SUCCESS)
    {
        vxStatus = vxMapArrayRange(pGraphObj->arr, 0, arrSize, &arrMapId,
            &stride, &arrBase, VX_READ_ONLY, VX_MEMORY_TYPE_HOST, 0);
    }

    if (vxStatus == VX_SUCCESS)
    {
        for (cnt = 0u; cnt < arrSize; cnt ++)
        {
            x = vxArrayItem(vx_keypoint_t, arrBase, cnt, stride).x;
            y = vxArrayItem(vx_keypoint_t, arrBase, cnt, stride).y;

            x = x - OPENVX_DRAW_BLOCK_SIZE/2;
            y = y - OPENVX_DRAW_BLOCK_SIZE/2;

            x = x & ~(0x1u);
            y = y & ~(0x1u);

            lumaAddr = vxFormatImagePatchAddress2d(pVidFrm->bufAddr[0], x, y,
                &pObj->vxImgAddr);
            chromaAddr = vxFormatImagePatchAddress2d(pVidFrm->bufAddr[1], x,
                y/2, &pObj->vxImgAddr);

            for (i = 0; i < OPENVX_DRAW_BLOCK_SIZE; i ++)
            {
                ptr1 = (UInt16 *)(lumaAddr + pObj->vxImgAddr.stride_y*i);
                ptr2 = (UInt16 *)(chromaAddr + pObj->vxImgAddr.stride_y*i);

                for (j = 0; j < OPENVX_DRAW_BLOCK_SIZE/2 + 1; j ++)
                {
                    *ptr1 = 0x5151;

                    if (i < OPENVX_DRAW_BLOCK_SIZE/2)
                    {
                        *ptr2 = 0xF05A;
                    }

                    ptr1 ++;
                    ptr2 ++;
                }
            }
        }
    }

    vxUnmapArrayRange(pGraphObj->arr, arrMapId);
}
