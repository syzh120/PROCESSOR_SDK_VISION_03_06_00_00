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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "alg_filter2d.h"

Int32 Alg_claheCreate(
            Alg_ClaheObj *pObj,
            UInt32 inWidth,
            UInt32 inHeight,
            UInt32 inPitch,
            UInt32 outPitch
            )
{
    pObj->prms.visionParams.algParams.size =
        sizeof(pObj->prms);
    pObj->prms.visionParams.cacheWriteBack = NULL;
    pObj->prms.maxWidth = inWidth;
    pObj->prms.maxHeight = inHeight;
    pObj->prms.tileWidth = 160;
    pObj->prms.tileHeight = 90;

    pObj->handle = AlgIvision_create(
                &CLAHE_TI_VISION_FXNS,
                (IALG_Params*)&pObj->prms
                );
    UTILS_assert(pObj->handle!=NULL);

    pObj->inArgs.iVisionInArgs.size =
        sizeof(pObj->inArgs);

    pObj->inArgs.clipLimit = 2;

    pObj->outArgs.iVisionOutArgs.size =
        sizeof(pObj->outArgs);

    pObj->inBufs.size = sizeof(pObj->inBufs);
    pObj->inBufs.numBufs = CLAHE_TI_BUFDESC_IN_TOTAL;
    pObj->inBufs.bufDesc  = pObj->inBufDescList;

    pObj->outBufs.size = sizeof(pObj->outBufs);
    pObj->outBufs.numBufs = CLAHE_TI_BUFDESC_OUT_TOTAL;
    pObj->outBufs.bufDesc = pObj->outBufDescList;

    pObj->inBufDescList[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER] = &pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER];
    pObj->outBufDescList[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER] = &pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER];

    pObj->inBufDescList[CLAHE_TI_BUFDESC_IN_LUT_BUFFER] = &pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER];
    pObj->outBufDescList[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER] = &pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER];

    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].numPlanes                          = 1;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].frameROI.topLeft.x    = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].frameROI.topLeft.y    = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].width                 = inPitch;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].height                = inHeight;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].frameROI.width        = inWidth;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].frameROI.height       = inHeight;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].planeType             = 0;

    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].numPlanes                          = 1;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].frameROI.topLeft.x    = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].frameROI.topLeft.y    = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].width                 = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].height                = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].frameROI.width        = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].frameROI.height       = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].planeType             = 0;
    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].buf                   = NULL;

    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].numPlanes                          = 1;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].frameROI.topLeft.x    = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].frameROI.topLeft.y    = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].width                 = outPitch;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].height                = inHeight;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].frameROI.width        = inWidth;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].frameROI.height       = inHeight;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].planeType             = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].buf                   = NULL;

    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].numPlanes                          = 1;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].frameROI.topLeft.x    = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].frameROI.topLeft.y    = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].width                 = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].height                = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].frameROI.width        = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].frameROI.height       = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].planeType             = 0;
    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].buf                   = NULL;

    pObj->lutBufSize = (256*inWidth*inHeight)/(pObj->prms.tileWidth*pObj->prms.tileHeight);

    pObj->lutBufAddr[0] =
        Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->lutBufSize,
            32
        );
    UTILS_assert(pObj->lutBufAddr[0]!=NULL);

    pObj->lutBufAddr[1] =
        Utils_memAlloc(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->lutBufSize,
            32
        );
    UTILS_assert(pObj->lutBufAddr[1]!=NULL);

    pObj->lutBufId = 0;

    return 0;
}

Int32 Alg_claheProcess(
            Alg_ClaheObj *pObj,
            Void *inBufAddr,
            Void *outBufAddr
        )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_IMAGE_BUFFER].bufPlanes[0].buf = inBufAddr;

    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_IMAGE_BUFFER].bufPlanes[0].buf = outBufAddr;

    pObj->inBufDesc[CLAHE_TI_BUFDESC_IN_LUT_BUFFER].bufPlanes[0].buf =
        pObj->lutBufAddr[pObj->lutBufId];

    pObj->outBufDesc[CLAHE_TI_BUFDESC_OUT_LUT_BUFFER].bufPlanes[0].buf =
        pObj->lutBufAddr[pObj->lutBufId ^ 1];

    status = AlgIvision_process(
                pObj->handle,
                &pObj->inBufs,
                &pObj->outBufs,
                (IVISION_InArgs*)&pObj->inArgs,
                (IVISION_OutArgs*)&pObj->outArgs
            );
    UTILS_assert(status==0);

    /* switch LUT buffers */
    pObj->lutBufId  = pObj->lutBufId ^ 1;

    return status;
}


Int32 Alg_claheDelete(Alg_ClaheObj *pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(pObj->handle)
    {
        status = AlgIvision_delete(pObj->handle);
        UTILS_assert(status==0);
    }

    if(pObj->lutBufAddr[0])
    {
        status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->lutBufAddr[0],
            pObj->lutBufSize
        );
        UTILS_assert(status==0);
    }

    if(pObj->lutBufAddr[1])
    {
        status = Utils_memFree(
            UTILS_HEAPID_DDR_CACHED_SR,
            pObj->lutBufAddr[1],
            pObj->lutBufSize
        );
    }
    return status;
}

