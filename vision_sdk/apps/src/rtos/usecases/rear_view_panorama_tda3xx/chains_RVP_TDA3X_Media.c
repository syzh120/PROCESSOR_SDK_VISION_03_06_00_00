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

#include <src/include/chains_common.h>
#include <src/include/chains_common_dewarp.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include "chains_RVP_TDA3X_priv.h"
#include "chains_RVP_TDA3X.h"

/*******************************************************************************
 *  Global Variables
 *******************************************************************************
 */
static ChainsCommon_DeWarp_mediaObj gDeWarpMediaObj;

AlgorithmLink_ldcSlicePrm gLdcSlicePrm[STEREO_DEWARP_NUM_CAMERAS] =
{
    {
        1,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,REMAP_WIDTH,REMAP_HEIGHT,STEREO_LDC_BLOCK_WIDTH,STEREO_LDC_BLOCK_HEIGHT,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
    },
    {
        1,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,REMAP_WIDTH,REMAP_HEIGHT,STEREO_LDC_BLOCK_WIDTH,STEREO_LDC_BLOCK_HEIGHT,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
    }
};

AlgorithmLink_ldcSlicePrm gLdcSlicePrmImageTransform[IMAGETRANSFORM_DEWARP_NUM_CAMERAS] =
{
    {
        1,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,SIMCOP_OUTPUT_WIDTH,SIMCOP_OUTPUT_HEIGHT,IMAGETRANSFORM_LDC_BLOCK_WIDTH,IMAGETRANSFORM_LDC_BLOCK_HEIGHT,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
    },
    {
        1,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,SIMCOP_OUTPUT_WIDTH,SIMCOP_OUTPUT_HEIGHT,IMAGETRANSFORM_LDC_BLOCK_WIDTH_STEREO_L,IMAGETRANSFORM_LDC_BLOCK_HEIGHT_STEREO_L,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
    },
    {
        1,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,SIMCOP_OUTPUT_WIDTH,SIMCOP_OUTPUT_HEIGHT,IMAGETRANSFORM_LDC_BLOCK_WIDTH,IMAGETRANSFORM_LDC_BLOCK_HEIGHT,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
    },
    {
        1,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,SIMCOP_STEREO_OUTPUT_WIDTH,SIMCOP_STEREO_OUTPUT_HEIGHT,SIMCOP_STEREO_LDC_BLOCK_WIDTH,SIMCOP_STEREO_LDC_BLOCK_HEIGHT, // switch 960 and 480
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
        ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
        0,0,0,0,0,0,
    }
};

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */
static Int32 mediaReadStereoLdcParams(
                Chains_RVPAppObj *pChainsObj,
                ChainsCommon_DeWarp_mediaObj *pMediaObj,
                AlgorithmLink_SrvCommonViewPointParams *pViewPointsParam,
                System_VideoFrameCompositeBuffer *pVidCompBuf,
                UInt32 numViewPoints,
                UInt32 numCameras,
                UInt32 ldcLutSize)
{
    Int32 retVal = 0;
    UInt32 cnt, idx;
    UInt32 rawMemSize, alignedLdcLutSize;
    AlgorithmLink_SrvCommonViewPointParams *pLocalViewParams;
    System_VideoFrameCompositeBuffer *pLocalVidCompBuf;


    Vps_printf("STEREO_MEDIA: Reading LDC LUT for stereo input...\n");

    for (cnt = 0; cnt < numViewPoints; cnt ++)
    {

        pLocalViewParams = pViewPointsParam + cnt;
        pLocalVidCompBuf = pVidCompBuf + cnt;

        pLocalViewParams->pCompBuf = pLocalVidCompBuf;


        alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);

        /* Max size */
        rawMemSize = (alignedLdcLutSize * numCameras);

        pLocalViewParams->baseBufAddr =
                ChainsCommon_DeWarp_memAlloc( rawMemSize, 128U);
        pMediaObj->stereoBufSize[cnt] = rawMemSize;


        /* TO REVISIT - Write viewPointParams manually */
        /*************************************************************/
        pLocalViewParams->viewPointId = cnt;
        pLocalViewParams->numCameras = numCameras;
        pLocalViewParams->remapChannels = 0;

        for (idx = 0; idx < numCameras; idx++ )
        {
            pLocalViewParams->ldcOutFrameWidth[idx] = REMAP_WIDTH;
            pLocalViewParams->ldcOutFrameHeight[idx] = REMAP_HEIGHT;
            pLocalViewParams->ldcOutPadX[idx] = 0;
            pLocalViewParams->ldcOutPadY[idx] = 0;
            pLocalViewParams->ldcOutBlockWidth[idx] = STEREO_LDC_BLOCK_WIDTH;
            pLocalViewParams->ldcOutBlockHeight[idx] = STEREO_LDC_BLOCK_HEIGHT;
        }
        /*************************************************************/

        retVal = ChainsCommon_DeWarp_mediaReadBlock(pMediaObj,
                                                 pLocalViewParams,
                                                 cnt,
                                                 rawMemSize,
                                                 DEWARP_MEDIA_FILE_LUT);
        if (SYSTEM_LINK_STATUS_SOK == retVal)
        {
            for (idx = 0; idx < numCameras; idx++)
            {
                pLocalVidCompBuf->metaBufAddr[idx] = (Void*)
                    ((UInt32) pLocalViewParams->baseBufAddr + (alignedLdcLutSize * idx));
            }

            pLocalVidCompBuf->numFrames = numCameras;
        }

        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

        memcpy(
            &pLocalViewParams->slicePrm,
            &gLdcSlicePrm,
            sizeof(AlgorithmLink_ldcSlicePrm) * 2);
    }

    return retVal;
}

static Int32 mediaReadImageTransformLdcParams(
                Chains_RVPAppObj *pChainsObj,
                ChainsCommon_DeWarp_mediaObj *pMediaObj,
                AlgorithmLink_SrvCommonViewPointParams *pViewPointsParam,
                System_VideoFrameCompositeBuffer *pVidCompBuf,
                UInt32 numViewPoints,
                UInt32 numCameras,
                UInt32 ldcLutSize)
{
    Int32 retVal = 0;
    UInt32 cnt, idx;
    UInt32 rawMemSize, alignedLdcLutSize, alignedLdcLutSize_trans;
    AlgorithmLink_SrvCommonViewPointParams *pLocalViewParams;
    System_VideoFrameCompositeBuffer *pLocalVidCompBuf;
    UInt32 lineOffset_trans, ldcLutSize_trans;


    Vps_printf("IMAGETRANSFORM_MEDIA: Reading LDC LUT for stereo input...\n");

    for (cnt = 0; cnt < numViewPoints; cnt ++)
    {

        pLocalViewParams = pViewPointsParam + cnt;
        pLocalVidCompBuf = pVidCompBuf + cnt;

        pLocalViewParams->pCompBuf = pLocalVidCompBuf;


        alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);

        /* raw mem size */
        rawMemSize = (alignedLdcLutSize * (numCameras-1)); // No LUT used for stereo right camera

        // Add transposed stereo disparity dewarp table size to rawmemsize
        lineOffset_trans = (SIMCOP_STEREO_OUTPUT_WIDTH /
                                  (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
        lineOffset_trans += 15;
        lineOffset_trans &= ~0xF;
        lineOffset_trans *= 4;

        ldcLutSize_trans = lineOffset_trans * ((SIMCOP_STEREO_OUTPUT_HEIGHT /
                                  (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                  + 1U);

        alignedLdcLutSize_trans = SystemUtils_align(ldcLutSize_trans, 128U);

        /* raw mem size */
        rawMemSize += (alignedLdcLutSize_trans); // Add size of LUT used for transposed stereo right camera

        pLocalViewParams->baseBufAddr =
                ChainsCommon_DeWarp_memAlloc( rawMemSize, 128U);
        pMediaObj->stereoBufSize[cnt] = rawMemSize;


        /* TO REVISIT - Write viewPointParams manually */
        /*************************************************************/
        pLocalViewParams->viewPointId = cnt;
        pLocalViewParams->numCameras = numCameras;
        pLocalViewParams->remapChannels = 0;

        for (idx = 0; idx < numCameras; idx++ )
        {
            pLocalViewParams->ldcOutFrameWidth[idx] = SIMCOP_OUTPUT_WIDTH;
            pLocalViewParams->ldcOutFrameHeight[idx] = SIMCOP_OUTPUT_HEIGHT;
            pLocalViewParams->ldcOutPadX[idx] = 0;
            pLocalViewParams->ldcOutPadY[idx] = 0;
            pLocalViewParams->ldcOutBlockWidth[idx]  = IMAGETRANSFORM_LDC_BLOCK_WIDTH;
            pLocalViewParams->ldcOutBlockHeight[idx] = IMAGETRANSFORM_LDC_BLOCK_HEIGHT;

            if(idx==1)
            {
                pLocalViewParams->ldcOutBlockWidth[idx]  = IMAGETRANSFORM_LDC_BLOCK_WIDTH_STEREO_L;
                pLocalViewParams->ldcOutBlockHeight[idx] = IMAGETRANSFORM_LDC_BLOCK_HEIGHT_STEREO_L;
            }

            if (idx == 3)
            {
                pLocalViewParams->ldcOutFrameWidth[idx] = SIMCOP_STEREO_OUTPUT_WIDTH;
                pLocalViewParams->ldcOutFrameHeight[idx] = SIMCOP_STEREO_OUTPUT_HEIGHT;
                pLocalViewParams->ldcOutBlockWidth[idx]  = SIMCOP_STEREO_LDC_BLOCK_WIDTH;
                pLocalViewParams->ldcOutBlockHeight[idx] = SIMCOP_STEREO_LDC_BLOCK_HEIGHT;
            }
        }
        /*************************************************************/

        retVal = ChainsCommon_DeWarp_mediaReadBlock(pMediaObj,
                                                 pLocalViewParams,
                                                 cnt,
                                                 rawMemSize,
                                                 RSVP_MEDIA_FILE_LUT);
        if (SYSTEM_LINK_STATUS_SOK == retVal)
        {
            for (idx = 0; idx < numCameras; idx++)
            {
                pLocalVidCompBuf->metaBufAddr[idx] = (Void*)
                    ((UInt32) pLocalViewParams->baseBufAddr + (alignedLdcLutSize * idx));
            }

            pLocalVidCompBuf->numFrames = numCameras;
        }

        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

        memcpy(
            &pLocalViewParams->slicePrm,
            &gLdcSlicePrmImageTransform,
            sizeof(AlgorithmLink_ldcSlicePrm) * 4);
    }

    return retVal;
}

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Void chains_RVP_TDA3X_MediaTask_Stereo(Void *appObj)
{
    UInt32 lineOffset, ldcLutSize;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    Chains_RVPAppObj *pChainsObj = (Chains_RVPAppObj *)appObj;
    UTILS_assert(NULL != pChainsObj);

    // TO REVISIT: can we replace REMAP_WIDTH with one in stereo global variable?
    lineOffset = (REMAP_WIDTH /
                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset += 15;
    lineOffset &= ~0xF;
    lineOffset *= 4;

    ldcLutSize = lineOffset * ((REMAP_HEIGHT /
                                (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                + 1U);

    status = ChainsCommon_DeWarp_mediaInit(&gDeWarpMediaObj,
                                           &pChainsObj->lutFilePresent,
                                           &pChainsObj->numViewPoints,
                                           DEWARP_MEDIA_FILE_LUT);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    UTILS_assert(TRUE == pChainsObj->lutFilePresent);

    while (SYSTEM_LINK_STATUS_SOK == status)
    {
        if(pChainsObj->lutFilePresent == TRUE)
        {
            /*
             *  The LDC LUT are available in the file therefore allocate the
             *  buffers and read the LUTs.
             */
            status = mediaReadStereoLdcParams(
                                        pChainsObj,
                                        &gDeWarpMediaObj,
                                        &pChainsObj->algViewParams[0U],
                                        &pChainsObj->ldcMeshTableContainer[0U],
                                        pChainsObj->numViewPoints,
                                        STEREO_DEWARP_NUM_CAMERAS,
                                        ldcLutSize);

            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }

        break;
    }

    ChainsCommon_DeWarp_mediaDeinit(&gDeWarpMediaObj);
}

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Void chains_RVP_TDA3X_MediaTask_RSVP(Void *appObj)
{
    UInt32 lineOffset, ldcLutSize;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    Chains_RVPAppObj *pChainsObj = (Chains_RVPAppObj *)appObj;
    UTILS_assert(NULL != pChainsObj);

    lineOffset = (SIMCOP_OUTPUT_WIDTH /
                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset += 15;
    lineOffset &= ~0xF;
    lineOffset *= 4;

    ldcLutSize = lineOffset * ((SIMCOP_OUTPUT_HEIGHT /
                                (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                + 1U);

    status = ChainsCommon_DeWarp_mediaInit(&gDeWarpMediaObj,
                                           &pChainsObj->lutFilePresentImageTransform,
                                           &pChainsObj->numViewPointsImageTransform,
                                           RSVP_MEDIA_FILE_LUT);
    UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
    UTILS_assert(TRUE == pChainsObj->lutFilePresentImageTransform);

    while (SYSTEM_LINK_STATUS_SOK == status)
    {
        if(pChainsObj->lutFilePresentImageTransform == TRUE)
        {
            /*
             *  The LDC LUT are available in the file therefore allocate the
             *  buffers and read the LUTs.
             */
            status = mediaReadImageTransformLdcParams(
                                        pChainsObj,
                                        &gDeWarpMediaObj,
                                        &pChainsObj->algViewParamsImageTransform[0U],
                                        &pChainsObj->ldcMeshTableContainerImageTransform[0U],
                                        pChainsObj->numViewPointsImageTransform,
                                        IMAGETRANSFORM_DEWARP_NUM_CAMERAS,
                                        ldcLutSize);

            UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        }

        break;
    }

    ChainsCommon_DeWarp_mediaDeinit(&gDeWarpMediaObj);
}

Int32 chains_RVP_TDA3X_FreeBufs(
                Chains_RVPAppObj *pChainsObj)
{
    UInt32 cnt;
    ChainsCommon_DeWarp_mediaObj *pMediaObj = &gDeWarpMediaObj;

    for(cnt = 0;cnt < pChainsObj->numViewPoints;cnt ++)
    {
        if(pChainsObj->algViewParams[cnt].baseBufAddr != NULL)
        {
            ChainsCommon_DeWarp_memFree(
                    pChainsObj->algViewParams[cnt].baseBufAddr,
                    pMediaObj->stereoBufSize[cnt]);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 chains_RVP_TDA3X_FreeBufs_RSVP(
                Chains_RVPAppObj *pChainsObj)
{
    UInt32 cnt;
    ChainsCommon_DeWarp_mediaObj *pMediaObj = &gDeWarpMediaObj;

    for(cnt = 0;cnt < pChainsObj->numViewPointsImageTransform;cnt ++)
    {
        if(pChainsObj->algViewParamsImageTransform[cnt].baseBufAddr != NULL)
        {
            ChainsCommon_DeWarp_memFree(
                    pChainsObj->algViewParamsImageTransform[cnt].baseBufAddr,
                    pMediaObj->stereoBufSize[cnt]);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}
