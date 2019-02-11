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

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*
*******************************************************************************
*
* IMPORTANT NOTE:
*  This file is AUTO-GENERATED by Vision SDK use case generation tool
*
*******************************************************************************
*/
#include "chains_vipSingleCameraObjectDetect2Tda3xx_priv.h"
Void chains_vipSingleCameraObjectDetect2Tda3xx_SetLinkId(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){
       pObj->CaptureLinkID                  = SYSTEM_LINK_ID_CAPTURE_0;
       pObj->IPCOut_IPU1_0_EVE1_0LinkID     = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_EVE1_IPU1_0_0LinkID      = EVE1_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Alg_ImagePreProcessLinkID      = EVE1_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->IPCOut_EVE1_IPU1_0_0LinkID     = EVE1_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_IPU1_0_EVE1_0LinkID      = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Dup_captureLinkID              = IPU1_0_LINK (SYSTEM_LINK_ID_DUP_0);
       pObj->Alg_ImgPyramidLinkID           = IPU1_0_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->Dup_imgPyramidLinkID           = IPU1_0_LINK (SYSTEM_LINK_ID_DUP_1);
       pObj->IPCOut_IPU1_0_DSP1_2LinkID     = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_2);
       pObj->IPCIn_DSP1_IPU1_0_1LinkID      = DSP1_LINK (SYSTEM_LINK_ID_IPC_IN_1);
       pObj->IPCOut_IPU1_0_EVE1_1LinkID     = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_OUT_1);
       pObj->IPCIn_EVE1_IPU1_0_1LinkID      = EVE1_LINK (SYSTEM_LINK_ID_IPC_IN_1);
       pObj->Alg_FPComputeLinkID            = EVE1_LINK (SYSTEM_LINK_ID_ALG_1);
       pObj->IPCOut_EVE1_DSP1_1LinkID       = EVE1_LINK (SYSTEM_LINK_ID_IPC_OUT_1);
       pObj->IPCIn_DSP1_EVE1_0LinkID        = DSP1_LINK (SYSTEM_LINK_ID_IPC_IN_0);
       pObj->Alg_ObjectDetectionLinkID      = DSP1_LINK (SYSTEM_LINK_ID_ALG_0);
       pObj->Merge_objectDetectLinkID       = DSP1_LINK (SYSTEM_LINK_ID_MERGE_0);
       pObj->Sync_objectDetectLinkID        = DSP1_LINK (SYSTEM_LINK_ID_SYNC_0);
       pObj->Alg_ObjectClassificationLinkID = DSP1_LINK (SYSTEM_LINK_ID_ALG_1);
       pObj->IPCOut_DSP1_IPU1_0_0LinkID     = DSP1_LINK (SYSTEM_LINK_ID_IPC_OUT_0);
       pObj->IPCIn_IPU1_0_DSP1_1LinkID      = IPU1_0_LINK (SYSTEM_LINK_ID_IPC_IN_1);
       pObj->Merge_algLinkID                = IPU1_0_LINK (SYSTEM_LINK_ID_MERGE_0);
       pObj->Sync_algLinkID                 = IPU1_0_LINK (SYSTEM_LINK_ID_SYNC_0);
       pObj->Alg_ObjectDrawLinkID           = IPU1_0_LINK (SYSTEM_LINK_ID_ALG_1);
       pObj->Display_algLinkID              = SYSTEM_LINK_ID_DISPLAY_0;
       pObj->GrpxSrcLinkID                  = IPU1_0_LINK (SYSTEM_LINK_ID_GRPX_SRC_0);
       pObj->Display_GrpxLinkID             = SYSTEM_LINK_ID_DISPLAY_1;
}

Void chains_vipSingleCameraObjectDetect2Tda3xx_ResetLinkPrms(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){
       CaptureLink_CreateParams_Init(&pObj->CapturePrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_EVE1_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_EVE1_IPU1_0_0Prm);
       AlgorithmLink_ImagePreProcess_Init(&pObj->Alg_ImagePreProcessPrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_EVE1_IPU1_0_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_IPU1_0_EVE1_0Prm);
       DupLink_CreateParams_Init(&pObj->Dup_capturePrm);
       AlgorithmLink_ImgPyramid_Init(&pObj->Alg_ImgPyramidPrm);
       DupLink_CreateParams_Init(&pObj->Dup_imgPyramidPrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_DSP1_2Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_DSP1_IPU1_0_1Prm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_IPU1_0_EVE1_1Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_EVE1_IPU1_0_1Prm);
       AlgorithmLink_FPCompute_Init(&pObj->Alg_FPComputePrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_EVE1_DSP1_1Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_DSP1_EVE1_0Prm);
       AlgorithmLink_ObjectDetection_Init(&pObj->Alg_ObjectDetectionPrm);
       MergeLink_CreateParams_Init(&pObj->Merge_objectDetectPrm);
       SyncLink_CreateParams_Init(&pObj->Sync_objectDetectPrm);
       AlgorithmLink_ObjectClassification_Init(&pObj->Alg_ObjectClassificationPrm);
       IpcLink_CreateParams_Init(&pObj->IPCOut_DSP1_IPU1_0_0Prm);
       IpcLink_CreateParams_Init(&pObj->IPCIn_IPU1_0_DSP1_1Prm);
       MergeLink_CreateParams_Init(&pObj->Merge_algPrm);
       SyncLink_CreateParams_Init(&pObj->Sync_algPrm);
       AlgorithmLink_ObjectDraw_Init(&pObj->Alg_ObjectDrawPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_algPrm);
       GrpxSrcLink_CreateParams_Init(&pObj->GrpxSrcPrm);
       DisplayLink_CreateParams_Init(&pObj->Display_GrpxPrm);
}

Void chains_vipSingleCameraObjectDetect2Tda3xx_SetPrms(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){
       (pObj->Alg_ImagePreProcessPrm).baseClassCreate.size  = sizeof(AlgorithmLink_ImagePreProcessCreateParams);
       (pObj->Alg_ImagePreProcessPrm).baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_IMAGEPREPROCESS;
       (pObj->Dup_capturePrm).numOutQue = 2;
       (pObj->Alg_ImgPyramidPrm).baseClassCreate.size  = sizeof(AlgorithmLink_ImgPyramidCreateParams);
       (pObj->Alg_ImgPyramidPrm).baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_IMG_PYRAMID;
       (pObj->Dup_imgPyramidPrm).numOutQue = 2;
       (pObj->Alg_FPComputePrm).baseClassCreate.size  = sizeof(AlgorithmLink_FPComputeCreateParams);
       (pObj->Alg_FPComputePrm).baseClassCreate.algId  = ALGORITHM_LINK_EVE_ALG_FPCOMPUTE;
       (pObj->Alg_ObjectDetectionPrm).baseClassCreate.size  = sizeof(AlgorithmLink_ObjectDetectionCreateParams);
       (pObj->Alg_ObjectDetectionPrm).baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_OBJECTDETECTION;
       (pObj->Merge_objectDetectPrm).numInQue = 2;
       (pObj->Alg_ObjectClassificationPrm).baseClassCreate.size  = sizeof(AlgorithmLink_ObjectClassificationCreateParams);
       (pObj->Alg_ObjectClassificationPrm).baseClassCreate.algId  = ALGORITHM_LINK_DSP_ALG_OBJECTCLASSIFICATION;
       (pObj->Merge_algPrm).numInQue = 2;
       (pObj->Alg_ObjectDrawPrm).baseClassCreate.size  = sizeof(AlgorithmLink_ObjectDrawCreateParams);
       (pObj->Alg_ObjectDrawPrm).baseClassCreate.algId  = ALGORITHM_LINK_IPU_ALG_OBJECT_DRAW;
}

Void chains_vipSingleCameraObjectDetect2Tda3xx_ConnectLinks(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){

       //Capture -> IPCOut_IPU1_0_EVE1_0
       pObj->CapturePrm.outQueParams.nextLink = pObj->IPCOut_IPU1_0_EVE1_0LinkID;
       pObj->IPCOut_IPU1_0_EVE1_0Prm.inQueParams.prevLinkId = pObj->CaptureLinkID;
       pObj->IPCOut_IPU1_0_EVE1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_IPU1_0_EVE1_0 -> IPCIn_EVE1_IPU1_0_0
       pObj->IPCOut_IPU1_0_EVE1_0Prm.outQueParams.nextLink = pObj->IPCIn_EVE1_IPU1_0_0LinkID;
       pObj->IPCIn_EVE1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_EVE1_0LinkID;
       pObj->IPCIn_EVE1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_EVE1_IPU1_0_0 -> Alg_ImagePreProcess
       pObj->IPCIn_EVE1_IPU1_0_0Prm.outQueParams.nextLink = pObj->Alg_ImagePreProcessLinkID;
       pObj->Alg_ImagePreProcessPrm.inQueParams.prevLinkId = pObj->IPCIn_EVE1_IPU1_0_0LinkID;
       pObj->Alg_ImagePreProcessPrm.inQueParams.prevLinkQueId = 0;

       //Alg_ImagePreProcess -> IPCOut_EVE1_IPU1_0_0
       pObj->Alg_ImagePreProcessPrm.outQueParams.nextLink = pObj->IPCOut_EVE1_IPU1_0_0LinkID;
       pObj->IPCOut_EVE1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->Alg_ImagePreProcessLinkID;
       pObj->IPCOut_EVE1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_EVE1_IPU1_0_0 -> IPCIn_IPU1_0_EVE1_0
       pObj->IPCOut_EVE1_IPU1_0_0Prm.outQueParams.nextLink = pObj->IPCIn_IPU1_0_EVE1_0LinkID;
       pObj->IPCIn_IPU1_0_EVE1_0Prm.inQueParams.prevLinkId = pObj->IPCOut_EVE1_IPU1_0_0LinkID;
       pObj->IPCIn_IPU1_0_EVE1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_IPU1_0_EVE1_0 -> Dup_capture
       pObj->IPCIn_IPU1_0_EVE1_0Prm.outQueParams.nextLink = pObj->Dup_captureLinkID;
       pObj->Dup_capturePrm.inQueParams.prevLinkId = pObj->IPCIn_IPU1_0_EVE1_0LinkID;
       pObj->Dup_capturePrm.inQueParams.prevLinkQueId = 0;

       //Dup_capture -> Merge_alg
       pObj->Dup_capturePrm.outQueParams[0].nextLink = pObj->Merge_algLinkID;
       pObj->Merge_algPrm.inQueParams[0].prevLinkId = pObj->Dup_captureLinkID;
       pObj->Merge_algPrm.inQueParams[0].prevLinkQueId = 0;

       //Dup_capture -> Alg_ImgPyramid
       pObj->Dup_capturePrm.outQueParams[1].nextLink = pObj->Alg_ImgPyramidLinkID;
       pObj->Alg_ImgPyramidPrm.inQueParams.prevLinkId = pObj->Dup_captureLinkID;
       pObj->Alg_ImgPyramidPrm.inQueParams.prevLinkQueId = 1;

       //Alg_ImgPyramid -> Dup_imgPyramid
       pObj->Alg_ImgPyramidPrm.outQueParams.nextLink = pObj->Dup_imgPyramidLinkID;
       pObj->Dup_imgPyramidPrm.inQueParams.prevLinkId = pObj->Alg_ImgPyramidLinkID;
       pObj->Dup_imgPyramidPrm.inQueParams.prevLinkQueId = 0;

       //Dup_imgPyramid -> IPCOut_IPU1_0_EVE1_1
       pObj->Dup_imgPyramidPrm.outQueParams[0].nextLink = pObj->IPCOut_IPU1_0_EVE1_1LinkID;
       pObj->IPCOut_IPU1_0_EVE1_1Prm.inQueParams.prevLinkId = pObj->Dup_imgPyramidLinkID;
       pObj->IPCOut_IPU1_0_EVE1_1Prm.inQueParams.prevLinkQueId = 0;

       //Dup_imgPyramid -> IPCOut_IPU1_0_DSP1_2
       pObj->Dup_imgPyramidPrm.outQueParams[1].nextLink = pObj->IPCOut_IPU1_0_DSP1_2LinkID;
       pObj->IPCOut_IPU1_0_DSP1_2Prm.inQueParams.prevLinkId = pObj->Dup_imgPyramidLinkID;
       pObj->IPCOut_IPU1_0_DSP1_2Prm.inQueParams.prevLinkQueId = 1;

       //IPCOut_IPU1_0_DSP1_2 -> IPCIn_DSP1_IPU1_0_1
       pObj->IPCOut_IPU1_0_DSP1_2Prm.outQueParams.nextLink = pObj->IPCIn_DSP1_IPU1_0_1LinkID;
       pObj->IPCIn_DSP1_IPU1_0_1Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_DSP1_2LinkID;
       pObj->IPCIn_DSP1_IPU1_0_1Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_DSP1_IPU1_0_1 -> Merge_objectDetect
       pObj->IPCIn_DSP1_IPU1_0_1Prm.outQueParams.nextLink = pObj->Merge_objectDetectLinkID;
       pObj->Merge_objectDetectPrm.inQueParams[1].prevLinkId = pObj->IPCIn_DSP1_IPU1_0_1LinkID;
       pObj->Merge_objectDetectPrm.inQueParams[1].prevLinkQueId = 0;

       //IPCOut_IPU1_0_EVE1_1 -> IPCIn_EVE1_IPU1_0_1
       pObj->IPCOut_IPU1_0_EVE1_1Prm.outQueParams.nextLink = pObj->IPCIn_EVE1_IPU1_0_1LinkID;
       pObj->IPCIn_EVE1_IPU1_0_1Prm.inQueParams.prevLinkId = pObj->IPCOut_IPU1_0_EVE1_1LinkID;
       pObj->IPCIn_EVE1_IPU1_0_1Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_EVE1_IPU1_0_1 -> Alg_FPCompute
       pObj->IPCIn_EVE1_IPU1_0_1Prm.outQueParams.nextLink = pObj->Alg_FPComputeLinkID;
       pObj->Alg_FPComputePrm.inQueParams.prevLinkId = pObj->IPCIn_EVE1_IPU1_0_1LinkID;
       pObj->Alg_FPComputePrm.inQueParams.prevLinkQueId = 0;

       //Alg_FPCompute -> IPCOut_EVE1_DSP1_1
       pObj->Alg_FPComputePrm.outQueParams.nextLink = pObj->IPCOut_EVE1_DSP1_1LinkID;
       pObj->IPCOut_EVE1_DSP1_1Prm.inQueParams.prevLinkId = pObj->Alg_FPComputeLinkID;
       pObj->IPCOut_EVE1_DSP1_1Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_EVE1_DSP1_1 -> IPCIn_DSP1_EVE1_0
       pObj->IPCOut_EVE1_DSP1_1Prm.outQueParams.nextLink = pObj->IPCIn_DSP1_EVE1_0LinkID;
       pObj->IPCIn_DSP1_EVE1_0Prm.inQueParams.prevLinkId = pObj->IPCOut_EVE1_DSP1_1LinkID;
       pObj->IPCIn_DSP1_EVE1_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_DSP1_EVE1_0 -> Alg_ObjectDetection
       pObj->IPCIn_DSP1_EVE1_0Prm.outQueParams.nextLink = pObj->Alg_ObjectDetectionLinkID;
       pObj->Alg_ObjectDetectionPrm.inQueParams.prevLinkId = pObj->IPCIn_DSP1_EVE1_0LinkID;
       pObj->Alg_ObjectDetectionPrm.inQueParams.prevLinkQueId = 0;

       //Alg_ObjectDetection -> Merge_objectDetect
       pObj->Alg_ObjectDetectionPrm.outQueParams.nextLink = pObj->Merge_objectDetectLinkID;
       pObj->Merge_objectDetectPrm.inQueParams[0].prevLinkId = pObj->Alg_ObjectDetectionLinkID;
       pObj->Merge_objectDetectPrm.inQueParams[0].prevLinkQueId = 0;

       //Merge_objectDetect -> Sync_objectDetect
       pObj->Merge_objectDetectPrm.outQueParams.nextLink = pObj->Sync_objectDetectLinkID;
       pObj->Sync_objectDetectPrm.inQueParams.prevLinkId = pObj->Merge_objectDetectLinkID;
       pObj->Sync_objectDetectPrm.inQueParams.prevLinkQueId = 0;

       //Sync_objectDetect -> Alg_ObjectClassification
       pObj->Sync_objectDetectPrm.outQueParams.nextLink = pObj->Alg_ObjectClassificationLinkID;
       pObj->Alg_ObjectClassificationPrm.inQueParams.prevLinkId = pObj->Sync_objectDetectLinkID;
       pObj->Alg_ObjectClassificationPrm.inQueParams.prevLinkQueId = 0;

       //Alg_ObjectClassification -> IPCOut_DSP1_IPU1_0_0
       pObj->Alg_ObjectClassificationPrm.outQueParams.nextLink = pObj->IPCOut_DSP1_IPU1_0_0LinkID;
       pObj->IPCOut_DSP1_IPU1_0_0Prm.inQueParams.prevLinkId = pObj->Alg_ObjectClassificationLinkID;
       pObj->IPCOut_DSP1_IPU1_0_0Prm.inQueParams.prevLinkQueId = 0;

       //IPCOut_DSP1_IPU1_0_0 -> IPCIn_IPU1_0_DSP1_1
       pObj->IPCOut_DSP1_IPU1_0_0Prm.outQueParams.nextLink = pObj->IPCIn_IPU1_0_DSP1_1LinkID;
       pObj->IPCIn_IPU1_0_DSP1_1Prm.inQueParams.prevLinkId = pObj->IPCOut_DSP1_IPU1_0_0LinkID;
       pObj->IPCIn_IPU1_0_DSP1_1Prm.inQueParams.prevLinkQueId = 0;

       //IPCIn_IPU1_0_DSP1_1 -> Merge_alg
       pObj->IPCIn_IPU1_0_DSP1_1Prm.outQueParams.nextLink = pObj->Merge_algLinkID;
       pObj->Merge_algPrm.inQueParams[1].prevLinkId = pObj->IPCIn_IPU1_0_DSP1_1LinkID;
       pObj->Merge_algPrm.inQueParams[1].prevLinkQueId = 0;

       //Merge_alg -> Sync_alg
       pObj->Merge_algPrm.outQueParams.nextLink = pObj->Sync_algLinkID;
       pObj->Sync_algPrm.inQueParams.prevLinkId = pObj->Merge_algLinkID;
       pObj->Sync_algPrm.inQueParams.prevLinkQueId = 0;

       //Sync_alg -> Alg_ObjectDraw
       pObj->Sync_algPrm.outQueParams.nextLink = pObj->Alg_ObjectDrawLinkID;
       pObj->Alg_ObjectDrawPrm.inQueParams.prevLinkId = pObj->Sync_algLinkID;
       pObj->Alg_ObjectDrawPrm.inQueParams.prevLinkQueId = 0;

       //Alg_ObjectDraw -> Display_alg
       pObj->Alg_ObjectDrawPrm.outQueParams.nextLink = pObj->Display_algLinkID;
       pObj->Display_algPrm.inQueParams.prevLinkId = pObj->Alg_ObjectDrawLinkID;
       pObj->Display_algPrm.inQueParams.prevLinkQueId = 0;

       //GrpxSrc -> Display_Grpx
       pObj->GrpxSrcPrm.outQueParams.nextLink = pObj->Display_GrpxLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkId = pObj->GrpxSrcLinkID;
       pObj->Display_GrpxPrm.inQueParams.prevLinkQueId = 0;

}

Int32 chains_vipSingleCameraObjectDetect2Tda3xx_Create(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj, Void *appObj){

       Int32 status;

       chains_vipSingleCameraObjectDetect2Tda3xx_SetLinkId(pObj);
       chains_vipSingleCameraObjectDetect2Tda3xx_ResetLinkPrms(pObj);

       chains_vipSingleCameraObjectDetect2Tda3xx_SetPrms(pObj);
       chains_vipSingleCameraObjectDetect2Tda3xx_SetAppPrms(pObj, appObj);

       chains_vipSingleCameraObjectDetect2Tda3xx_ConnectLinks(pObj);
       status = System_linkCreate(pObj->CaptureLinkID, &pObj->CapturePrm, sizeof(pObj->CapturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_EVE1_0LinkID, &pObj->IPCOut_IPU1_0_EVE1_0Prm, sizeof(pObj->IPCOut_IPU1_0_EVE1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_EVE1_IPU1_0_0LinkID, &pObj->IPCIn_EVE1_IPU1_0_0Prm, sizeof(pObj->IPCIn_EVE1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_ImagePreProcessLinkID, &pObj->Alg_ImagePreProcessPrm, sizeof(pObj->Alg_ImagePreProcessPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_EVE1_IPU1_0_0LinkID, &pObj->IPCOut_EVE1_IPU1_0_0Prm, sizeof(pObj->IPCOut_EVE1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_IPU1_0_EVE1_0LinkID, &pObj->IPCIn_IPU1_0_EVE1_0Prm, sizeof(pObj->IPCIn_IPU1_0_EVE1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Dup_captureLinkID, &pObj->Dup_capturePrm, sizeof(pObj->Dup_capturePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_ImgPyramidLinkID, &pObj->Alg_ImgPyramidPrm, sizeof(pObj->Alg_ImgPyramidPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Dup_imgPyramidLinkID, &pObj->Dup_imgPyramidPrm, sizeof(pObj->Dup_imgPyramidPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_DSP1_2LinkID, &pObj->IPCOut_IPU1_0_DSP1_2Prm, sizeof(pObj->IPCOut_IPU1_0_DSP1_2Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_DSP1_IPU1_0_1LinkID, &pObj->IPCIn_DSP1_IPU1_0_1Prm, sizeof(pObj->IPCIn_DSP1_IPU1_0_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_IPU1_0_EVE1_1LinkID, &pObj->IPCOut_IPU1_0_EVE1_1Prm, sizeof(pObj->IPCOut_IPU1_0_EVE1_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_EVE1_IPU1_0_1LinkID, &pObj->IPCIn_EVE1_IPU1_0_1Prm, sizeof(pObj->IPCIn_EVE1_IPU1_0_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_FPComputeLinkID, &pObj->Alg_FPComputePrm, sizeof(pObj->Alg_FPComputePrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_EVE1_DSP1_1LinkID, &pObj->IPCOut_EVE1_DSP1_1Prm, sizeof(pObj->IPCOut_EVE1_DSP1_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_DSP1_EVE1_0LinkID, &pObj->IPCIn_DSP1_EVE1_0Prm, sizeof(pObj->IPCIn_DSP1_EVE1_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_ObjectDetectionLinkID, &pObj->Alg_ObjectDetectionPrm, sizeof(pObj->Alg_ObjectDetectionPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Merge_objectDetectLinkID, &pObj->Merge_objectDetectPrm, sizeof(pObj->Merge_objectDetectPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Sync_objectDetectLinkID, &pObj->Sync_objectDetectPrm, sizeof(pObj->Sync_objectDetectPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_ObjectClassificationLinkID, &pObj->Alg_ObjectClassificationPrm, sizeof(pObj->Alg_ObjectClassificationPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCOut_DSP1_IPU1_0_0LinkID, &pObj->IPCOut_DSP1_IPU1_0_0Prm, sizeof(pObj->IPCOut_DSP1_IPU1_0_0Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->IPCIn_IPU1_0_DSP1_1LinkID, &pObj->IPCIn_IPU1_0_DSP1_1Prm, sizeof(pObj->IPCIn_IPU1_0_DSP1_1Prm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Merge_algLinkID, &pObj->Merge_algPrm, sizeof(pObj->Merge_algPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Sync_algLinkID, &pObj->Sync_algPrm, sizeof(pObj->Sync_algPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Alg_ObjectDrawLinkID, &pObj->Alg_ObjectDrawPrm, sizeof(pObj->Alg_ObjectDrawPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_algLinkID, &pObj->Display_algPrm, sizeof(pObj->Display_algPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->GrpxSrcLinkID, &pObj->GrpxSrcPrm, sizeof(pObj->GrpxSrcPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkCreate(pObj->Display_GrpxLinkID, &pObj->Display_GrpxPrm, sizeof(pObj->Display_GrpxPrm));
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCameraObjectDetect2Tda3xx_Start(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){

       Int32 status;

       status = System_linkStart(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Display_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_ObjectDrawLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Sync_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Merge_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_IPU1_0_DSP1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_ObjectClassificationLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Sync_objectDetectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Merge_objectDetectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_ObjectDetectionLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_DSP1_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_EVE1_DSP1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_FPComputeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_EVE1_IPU1_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_EVE1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_DSP1_IPU1_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_DSP1_2LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Dup_imgPyramidLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_ImgPyramidLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Dup_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->Alg_ImagePreProcessLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStart(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCameraObjectDetect2Tda3xx_Stop(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){

       Int32 status;

       status = System_linkStop(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Display_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_ObjectDrawLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Sync_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Merge_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_IPU1_0_DSP1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_ObjectClassificationLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Sync_objectDetectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Merge_objectDetectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_ObjectDetectionLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_DSP1_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_EVE1_DSP1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_FPComputeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_EVE1_IPU1_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_EVE1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_DSP1_IPU1_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_DSP1_2LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Dup_imgPyramidLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_ImgPyramidLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Dup_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->Alg_ImagePreProcessLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkStop(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Int32 chains_vipSingleCameraObjectDetect2Tda3xx_Delete(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){

       Int32 status;

       status = System_linkDelete(pObj->Display_GrpxLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->GrpxSrcLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Display_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_ObjectDrawLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Sync_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Merge_algLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_IPU1_0_DSP1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_ObjectClassificationLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Sync_objectDetectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Merge_objectDetectLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_ObjectDetectionLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_DSP1_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_EVE1_DSP1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_FPComputeLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_EVE1_IPU1_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_EVE1_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_DSP1_IPU1_0_1LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_DSP1_2LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Dup_imgPyramidLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_ImgPyramidLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Dup_captureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->Alg_ImagePreProcessLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       status = System_linkDelete(pObj->CaptureLinkID);
       UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

       return status;
}

Void chains_vipSingleCameraObjectDetect2Tda3xx_printBufferStatistics(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){
       System_linkPrintBufferStatistics(pObj->CaptureLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_ImagePreProcessLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_EVE1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_IPU1_0_EVE1_0LinkID);
       System_linkPrintBufferStatistics(pObj->Dup_captureLinkID);
       System_linkPrintBufferStatistics(pObj->Alg_ImgPyramidLinkID);
       System_linkPrintBufferStatistics(pObj->Dup_imgPyramidLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_DSP1_2LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_DSP1_IPU1_0_1LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCOut_IPU1_0_EVE1_1LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_EVE1_IPU1_0_1LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_FPComputeLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_EVE1_DSP1_1LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_DSP1_EVE1_0LinkID);
       System_linkPrintBufferStatistics(pObj->Alg_ObjectDetectionLinkID);
       System_linkPrintBufferStatistics(pObj->Merge_objectDetectLinkID);
       System_linkPrintBufferStatistics(pObj->Sync_objectDetectLinkID);
       System_linkPrintBufferStatistics(pObj->Alg_ObjectClassificationLinkID);
       System_linkPrintBufferStatistics(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintBufferStatistics(pObj->IPCIn_IPU1_0_DSP1_1LinkID);
       System_linkPrintBufferStatistics(pObj->Merge_algLinkID);
       System_linkPrintBufferStatistics(pObj->Sync_algLinkID);
       System_linkPrintBufferStatistics(pObj->Alg_ObjectDrawLinkID);
       System_linkPrintBufferStatistics(pObj->Display_algLinkID);
       System_linkPrintBufferStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintBufferStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}

Void chains_vipSingleCameraObjectDetect2Tda3xx_printStatistics(chains_vipSingleCameraObjectDetect2Tda3xxObj *pObj){
       System_linkPrintStatistics(pObj->CaptureLinkID);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_EVE1_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_EVE1_IPU1_0_0LinkID);
       System_linkPrintStatistics(pObj->Alg_ImagePreProcessLinkID);
       System_linkPrintStatistics(pObj->IPCOut_EVE1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_IPU1_0_EVE1_0LinkID);
       System_linkPrintStatistics(pObj->Dup_captureLinkID);
       System_linkPrintStatistics(pObj->Alg_ImgPyramidLinkID);
       System_linkPrintStatistics(pObj->Dup_imgPyramidLinkID);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_DSP1_2LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_DSP1_IPU1_0_1LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCOut_IPU1_0_EVE1_1LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_EVE1_IPU1_0_1LinkID);
       System_linkPrintStatistics(pObj->Alg_FPComputeLinkID);
       System_linkPrintStatistics(pObj->IPCOut_EVE1_DSP1_1LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_DSP1_EVE1_0LinkID);
       System_linkPrintStatistics(pObj->Alg_ObjectDetectionLinkID);
       System_linkPrintStatistics(pObj->Merge_objectDetectLinkID);
       System_linkPrintStatistics(pObj->Sync_objectDetectLinkID);
       System_linkPrintStatistics(pObj->Alg_ObjectClassificationLinkID);
       System_linkPrintStatistics(pObj->IPCOut_DSP1_IPU1_0_0LinkID);
       Task_sleep(500);
       System_linkPrintStatistics(pObj->IPCIn_IPU1_0_DSP1_1LinkID);
       System_linkPrintStatistics(pObj->Merge_algLinkID);
       System_linkPrintStatistics(pObj->Sync_algLinkID);
       System_linkPrintStatistics(pObj->Alg_ObjectDrawLinkID);
       System_linkPrintStatistics(pObj->Display_algLinkID);
       System_linkPrintStatistics(pObj->GrpxSrcLinkID);
       System_linkPrintStatistics(pObj->Display_GrpxLinkID);
       Task_sleep(500);
}
