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
#include <src/rtos/alg_plugins/surroundview/include/svCommonDefs.h>
#include <src/include/chains_common.h>
#include <src/include/chains_common_surround_view.h>
#include <src/include/chains_common_osal.h>
#include <src/include/chains_common_srv_calib.h>
#include <src/rtos/iss/include/iss_sensors.h>
#include <src/rtos/iss/include/iss_utils.h>
#include "chains_issMultCaptIspDeWarpRearView3dSv_priv.h"
#include "chains_issMultCaptIspDeWarpRearView3dSv.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Enable the LDC slice parameters locally
 *
 *******************************************************************************
*/
//#define LOCAL_LDC_SLICE_PRM

/*******************************************************************************
 *  Global Variables
 *******************************************************************************
 */
static Chain_Common_SRV_mediaObj gSrvMediaObj;

#ifdef LOCAL_LDC_SLICE_PRM
    extern SRV_UC_3D_LDC_SLICE_PRM gLdcSlicePrmNo;

    AlgorithmLink_ldcSlicePrm \
    static gLdcSlicePrm[SRV_UC_3D_LDC_SLICE_PRM_MAX][ALGLINK_SRV_COMMON_MAX_CAMERAS] =
    {
        /* 0:1 slice with 16x16 block size */
        {
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 1:1 slice with 16x8 block size */
        {
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 2:2 slices with 16x16 and 16x8 block sizes */
        {
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 3:2 slices with 16x16 and 16x4 block sizes */
        {
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,50,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,50,100,50,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,50,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                50,0,50,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 4:1 slice with 16x4 block size */
        {
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   1,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 5:2 slices with 16x8 and 16x4 block sizes */
        {
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,400,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                0,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,0,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   2,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                288,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },

        /* 6:3 slices with 16x16, 16x8 and 16x4 block sizes */
        {
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                216,320,320,112,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,400,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                0,216,112,576,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                0,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                216,0,320,112,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                248,0,224,32,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
            {   3,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,100,100,16,16,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                208,216,112,576,16,8,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS,
                288,392,32,224,16,4,
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_PERCENT,
                0,0,0,0,0,0,
            },
        },
    };
#endif

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */
static Int32 mediaReadCompressedLdcViewPointParams(
                chains_issMultCaptIspDewarpSv_DisplayAppObj *pChainsObj,
                AlgorithmLink_SrvCommonViewPointParams *pSrvViewPointsParam,
                System_VideoFrameCompositeBuffer *pVidCompBuf,
                UInt32 numCameras,
                UInt32 ldcLutSize)
{
    UInt32 cnt, idx;
    UInt32 alignedLdcLutSize, alignedHeaderSize;
    AlgorithmLink_SrvCommonViewPointParams *pLocalSrvParams;
    System_VideoFrameCompositeBuffer *pLocalVidCompBuf;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 start,end;
    UInt32 idxBufPtr;
    Chain_Common_SRV_mediaObj *pMediaObj = &gSrvMediaObj;
    UInt32 carImgOffset, viewPointOffset;
    start = Utils_getCurTimeInMsec();

    /*Read the first view point*/
    status = Chain_Common_SRV_Comp_mediaInit(pMediaObj, SRV_MEDIA_FILE_VIEWPOINT_ZERO);

    if( status != SYSTEM_LINK_STATUS_EFAIL)
    {
        /*Get the number of View Points*/
        UInt32 numViewPoints = (UInt32)(*(pMediaObj->ldcIdxBuf));
        pChainsObj->numViewPoints = numViewPoints;

        /*Fill the AlgorithmLink_SrvCommonViewPointParams structure with each view point data*/
        for (cnt = 0; cnt < numViewPoints; cnt ++)
        {
            pLocalSrvParams = pSrvViewPointsParam + cnt;
            pLocalVidCompBuf = pVidCompBuf + cnt;

            alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);
            alignedHeaderSize = SystemUtils_align(SRV_MEDIA_SIZE_HEADER, 128U);

            /*
             *  Get the View point data size from the index buffer
             */
            idxBufPtr = (cnt * 2) + (SRV_MEDIA_SIZE_METADATA >> 2);
            viewPointOffset = *(pMediaObj->ldcIdxBuf + idxBufPtr);
            carImgOffset = *(pMediaObj->carImgIdxBuf + idxBufPtr);

            memcpy(pLocalSrvParams, (pMediaObj->ldcBuf + viewPointOffset), \
                                    sizeof(AlgorithmLink_SrvCommonViewPointParams));
            pLocalSrvParams->pCompBuf = pLocalVidCompBuf;

            for (idx = 0; idx < numCameras; idx++)
            {
                pLocalVidCompBuf->metaBufAddr[idx] = (Void*)
                            ((UInt32)(pMediaObj->ldcBuf + viewPointOffset) + \
                            alignedHeaderSize + \
                            (alignedLdcLutSize * idx));
            }

            pLocalVidCompBuf->numFrames = numCameras;

            if (TRUE == pChainsObj->useUserBlendTable3DLDC)
            {
                pLocalSrvParams->blendTableAddr = (Void*)
                    ((UInt32)(pMediaObj->ldcBuf + viewPointOffset) + alignedHeaderSize
                    + (alignedLdcLutSize * numCameras));
            }
            else
            {
                pLocalSrvParams->blendTableAddr = NULL;
            }

            pLocalSrvParams->carImgPtr = (UInt32 *)(pMediaObj->carImgBuf + carImgOffset);

    #ifdef LOCAL_LDC_SLICE_PRM
            memcpy(
                &pLocalSrvParams->slicePrm,
                &gLdcSlicePrm[gLdcSlicePrmNo],
                sizeof(AlgorithmLink_ldcSlicePrm) * ALGLINK_SRV_COMMON_MAX_CAMERAS);
    #endif
            if(0U == cnt)
            {
                /*
                 *  Start the SRV use case when the first view point parameters are
                 *  available
                 */
                BspOsal_semPost(pChainsObj->startSrvDemo);

                /* Wait for the complete chain creation */
                BspOsal_semWait(pChainsObj->startSrvDemo, BSP_OSAL_WAIT_FOREVER);

                /*Start the read of the remaining View Points*/
                Chain_Common_SRV_Comp_mediaInit(pMediaObj, SRV_MEDIA_FILE_LUT);
            }
        }
        end = Utils_getCurTimeInMsec();

        Vps_printf(" SRV_MEDIA: Time taken to read %d view point data = %d msec\n",
                   numViewPoints, (end - start));
    }
    return status;
}


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

Void chains_issMultCaptIspDeWarpRearView3dSv_MediaTask(UArg arg1, UArg arg2)
{
    UInt32 lineOffset, ldcLutSize;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    chains_issMultCaptIspDewarpSv_DisplayAppObj *pChainsObj;

    UTILS_COMPILETIME_ASSERT (SRV_MEDIA_SIZE_HEADER >= \
                                sizeof(AlgorithmLink_SrvCommonViewPointParams));

    pChainsObj = (chains_issMultCaptIspDewarpSv_DisplayAppObj *)arg1;
    UTILS_assert(NULL != pChainsObj);

    lineOffset = (SRV_UC_3D_LDC_OUTPUT_WIDTH_MAX /
                    (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8)) + 1U;
    lineOffset += 15;
    lineOffset &= ~0xF;
    lineOffset *= 4;

    ldcLutSize = lineOffset * ((SRV_UC_3D_LDC_OUTPUT_HEIGHT_MAX /
                                (1U << VPS_ISS_LDC_LUT_DOWN_SCALE_FACTOR_8))
                                + 1U);

    while (SYSTEM_LINK_STATUS_SOK == status)
    {
        /*
         *  The LDC LUT are available in the file therefore allocate the
         *  buffers and read the LUTs.
         */
        status = mediaReadCompressedLdcViewPointParams(
                                    pChainsObj,
                                    &pChainsObj->algViewParams[0U],
                                    &pChainsObj->ldcMeshTableContainer[0U],
                                    SRV_UC_3D_NUM_CAMERAS,
                                    ldcLutSize);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == status);
        pChainsObj->freeToSwitch = TRUE;

        break;
    }
}

Int32 chains_issMultCaptIspDeWarpRearView3dSv_FreeBufs()
{
    Chain_Common_SRV_mediaObj *pMediaObj = &gSrvMediaObj;

    ChainsCommon_Osal_memFree(
                            pMediaObj->carImgIdxBuf,
                            SRV_MEDIA_SIZE_MAXIDX);

    ChainsCommon_Osal_memFree(
                            pMediaObj->ldcIdxBuf,
                            SRV_MEDIA_SIZE_MAXIDX);

    ChainsCommon_Osal_memFree(
                            pMediaObj->carImgBuf,
                            pMediaObj->carImgBufSize);

    ChainsCommon_Osal_memFree(
                            pMediaObj->ldcBuf,
                            pMediaObj->ldcBufSize);

    return SYSTEM_LINK_STATUS_SOK;
}
