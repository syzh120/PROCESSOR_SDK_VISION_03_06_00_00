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
#include "featurePlaneCompLink_priv.h"

Int32 Alg_featureComputeCreate(
            Alg_FeatureComputeObj *pObj,
            Alg_ImagePyramidObj *pImgPyramidObj,
            UInt32 *outBufSize
      )
{
    Int32 status;
    UInt16 i;

    memset(pObj, 0, sizeof(*pObj));

    pObj->prms.visionParams.algParams.size =
        sizeof(pObj->prms);

    pObj->prms.visionParams.cacheWriteBack = NULL;

    pObj->prms.imgFrameWidth    = pImgPyramidObj->scalePrms[0].orgWidth;
    pObj->prms.imgFrameHeight   = pImgPyramidObj->scalePrms[0].orgHeight;
    pObj->prms.leftPadPels      = 0;
    pObj->prms.topPadPels       = 0;
    pObj->prms.cellSize         = 4;
    pObj->prms.blockSize        = 4;
    pObj->prms.blockOverlap     = 0;
    pObj->prms.sreachStep       = pImgPyramidObj->sreachStep;
    pObj->prms.maxNumScales     = pImgPyramidObj->numScales;
    pObj->prms.numBins          = 6;
    pObj->prms.gradientMethod   = 0;
    pObj->prms.enableCellSum    = 0;
    pObj->prms.scaleRatioQ12    = 0; /* NOT USED */
    pObj->prms.additionalPlaneFLag = (1<<0)|(1<<1)|(1<<2);
    pObj->prms.outPutBufSize    = 0;
    pObj->prms.outFormat        = 0;

    for(i = 0; i<pImgPyramidObj->numScales; i++)
    {
        pObj->prms.scaleParams[i]
            = pImgPyramidObj->scalePrms[i];
    }

    pObj->handle = AlgIvision_create(
                &PD_FEATURE_PLANE_COMPUTATION_TI_VISION_FXNS,
                (IALG_Params*)&pObj->prms
                );
    UTILS_assert(pObj->handle!=NULL);

    pObj->inArgs.iVisionInArgs.size =
        sizeof(pObj->inArgs);

    pObj->inArgs.numScales = pImgPyramidObj->numScales;

    pObj->outArgs.iVisionOutArgs.size =
        sizeof(pObj->outArgs);

    pObj->inBufs.size = sizeof(pObj->inBufs);
    pObj->inBufs.numBufs = pObj->prms.maxNumScales;
    pObj->inBufs.bufDesc  = pObj->inBufDescList;

    pObj->outBufs.size = sizeof(pObj->outBufs);
    pObj->outBufs.numBufs = PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_TOTAL;
    pObj->outBufs.bufDesc = pObj->outBufDescList;

    for(i=0; i<pObj->prms.maxNumScales; i++)
    {
        pObj->inBufDescList[i] = &pObj->inBufDesc[i];

        pObj->inBufDesc[i].numPlanes                          = 2;
        pObj->inBufDesc[i].bufPlanes[0].width                 = pImgPyramidObj->outPitch[i][0];
        pObj->inBufDesc[i].bufPlanes[0].height                = pImgPyramidObj->scalePrms[i].height;
        pObj->inBufDesc[i].bufPlanes[0].frameROI.width        = pImgPyramidObj->scalePrms[i].width;
        pObj->inBufDesc[i].bufPlanes[0].frameROI.height       = pImgPyramidObj->scalePrms[i].height;
        pObj->inBufDesc[i].bufPlanes[0].planeType             = 0; //Luma Y
        pObj->inBufDesc[i].bufPlanes[0].buf                   = pImgPyramidObj->outBufAddr[i][0];

        pObj->inBufDesc[i].bufPlanes[1].width                 = pImgPyramidObj->outPitch[i][1];
        pObj->inBufDesc[i].bufPlanes[1].height                = pImgPyramidObj->scalePrms[i].height/2;
        pObj->inBufDesc[i].bufPlanes[1].frameROI.width        = pImgPyramidObj->scalePrms[i].width;
        pObj->inBufDesc[i].bufPlanes[1].frameROI.height       = pImgPyramidObj->scalePrms[i].height/2;
        pObj->inBufDesc[i].bufPlanes[1].planeType             = 1; //C
        pObj->inBufDesc[i].bufPlanes[1].buf                   = pImgPyramidObj->outBufAddr[i][1];

        if(i%pImgPyramidObj->scaleSteps)
        {
            pObj->inBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = 0;
            pObj->inBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = 0;
            pObj->inBufDesc[i].bufPlanes[1].frameROI.topLeft.x    = 0;
            pObj->inBufDesc[i].bufPlanes[1].frameROI.topLeft.y    = 0;
        }
        else
        {
            pObj->inBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = pImgPyramidObj->scalePrms[i].x;
            pObj->inBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = pImgPyramidObj->scalePrms[i].y;
            pObj->inBufDesc[i].bufPlanes[1].frameROI.topLeft.x    = pImgPyramidObj->scalePrms[i].x;
            pObj->inBufDesc[i].bufPlanes[1].frameROI.topLeft.y    = pImgPyramidObj->scalePrms[i].y/2;
        }
    }

    status = AlgIvision_control(pObj->handle,
                                TI_PD_CONTROL_GET_OUTPUT_BUF_SIZE,
                                (IALG_Params *)&pObj->prms,
                                (IALG_Params *)&pObj->prms);
    UTILS_assert(status==0);

    *outBufSize = pObj->prms.outPutBufSize;

    pObj->outBufDescList[PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_FEATURE_PLANES_BUFFER] = &pObj->outBufDesc;

    pObj->outBufDesc.numPlanes                          = 1;
    pObj->outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
    pObj->outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
    pObj->outBufDesc.bufPlanes[0].width                 = pObj->prms.outPutBufSize;
    pObj->outBufDesc.bufPlanes[0].height                = 1;
    pObj->outBufDesc.bufPlanes[0].frameROI.width        = pObj->prms.outPutBufSize;
    pObj->outBufDesc.bufPlanes[0].frameROI.height       = 1;
    pObj->outBufDesc.bufPlanes[0].planeType             = 0;
    pObj->outBufDesc.bufPlanes[0].buf                   = NULL;

    return 0;
}

Int32 Alg_featureComputeProcess(
            Alg_FeatureComputeObj *pObj,
            Void *outBufAddr
      )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    pObj->outBufDesc.bufPlanes[0].buf = outBufAddr;

    status = AlgIvision_process(
                pObj->handle,
                &pObj->inBufs,
                &pObj->outBufs,
                (IVISION_InArgs*)&pObj->inArgs,
                (IVISION_OutArgs*)&pObj->outArgs
            );
    UTILS_assert(status==0);

    return status;
}

Int32 Alg_featureComputeDelete(
            Alg_FeatureComputeObj *pObj
      )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    status = AlgIvision_delete(pObj->handle);
    UTILS_assert(status==0);

    return status;
}
