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

#ifndef _chains_lvdsVipMultiCam_3d_perception_H_
#define _chains_lvdsVipMultiCam_3d_perception_H_

#include <include/link_api/system.h>
#include <include/link_api/captureLink.h>
#include <include/alglink_api/algorithmLink_sparseOpticalFlow.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/syncLink.h>
#include <include/alglink_api/algorithmLink_sfmMain.h>
#include <include/alglink_api/algorithmLink_sfmLinearTwoView.h>
#include <include/link_api/dupLink.h>
#include <include/alglink_api/algorithmLink_sfmMap.h>
#include <include/link_api/sgx3DsfmLink.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/grpxSrcLink.h>
#include <include/link_api/displayLink.h>

typedef struct {
       UInt32    CaptureLinkID;
       UInt32    Sync_1LinkID;
       UInt32    Dup_capLinkID;
       UInt32    IPCOut_IPU1_0_A15_0_0LinkID;
       UInt32    IPCIn_A15_0_IPU1_0_0LinkID;
       UInt32    Dup_sofLinkID;
       UInt32    IPCOut_IPU1_0_EVE4_4LinkID;
       UInt32    IPCIn_EVE4_IPU1_0_0LinkID;
       UInt32    Alg_SparseOpticalFlow_3LinkID;
       UInt32    IPCOut_EVE4_DSP1_0LinkID;
       UInt32    IPCIn_DSP1_EVE4_3LinkID;
       UInt32    IPCOut_IPU1_0_EVE3_3LinkID;
       UInt32    IPCIn_EVE3_IPU1_0_0LinkID;
       UInt32    Alg_SparseOpticalFlow_2LinkID;
       UInt32    IPCOut_EVE3_DSP1_0LinkID;
       UInt32    IPCIn_DSP1_EVE3_2LinkID;
       UInt32    IPCOut_IPU1_0_EVE2_2LinkID;
       UInt32    IPCIn_EVE2_IPU1_0_0LinkID;
       UInt32    Alg_SparseOpticalFlow_1LinkID;
       UInt32    IPCOut_EVE2_DSP1_0LinkID;
       UInt32    IPCIn_DSP1_EVE2_1LinkID;
       UInt32    IPCOut_IPU1_0_EVE1_1LinkID;
       UInt32    IPCIn_EVE1_IPU1_0_0LinkID;
       UInt32    Alg_SparseOpticalFlow_0LinkID;
       UInt32    IPCOut_EVE1_DSP1_0LinkID;
       UInt32    IPCIn_DSP1_EVE1_0LinkID;
       UInt32    MergeLinkID;
       UInt32    Sync_2LinkID;
       UInt32    Alg_SfmMainLinkID;
       UInt32    IPCOut_DSP1_DSP2_2LinkID;
       UInt32    IPCIn_DSP2_DSP1_0LinkID;
       UInt32    Alg_SfmLinearTwoViewLinkID;
       UInt32    Dup_poseLinkID;
       UInt32    IPCOut_DSP1_A15_0_0LinkID;
       UInt32    IPCIn_A15_0_DSP1_1LinkID;
       UInt32    Alg_SfmMapLinkID;
       UInt32    IPCOut_DSP1_A15_0_1LinkID;
       UInt32    IPCIn_A15_0_DSP1_2LinkID;
       UInt32    Sgx3DsfmLinkID;
       UInt32    IPCOut_A15_0_IPU1_0_0LinkID;
       UInt32    IPCIn_IPU1_0_A15_0_0LinkID;
       UInt32    Display_M4LinkID;
       UInt32    GrpxSrcLinkID;
       UInt32    Display_GrpxLinkID;

       CaptureLink_CreateParams                CapturePrm;
       SyncLink_CreateParams                   Sync_1Prm;
       DupLink_CreateParams                    Dup_capPrm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_A15_0_0Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_IPU1_0_0Prm;
       DupLink_CreateParams                    Dup_sofPrm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_EVE4_4Prm;
       IpcLink_CreateParams                    IPCIn_EVE4_IPU1_0_0Prm;
       AlgorithmLink_SparseOpticalFlowCreateParams Alg_SparseOpticalFlow_3Prm;
       IpcLink_CreateParams                    IPCOut_EVE4_DSP1_0Prm;
       IpcLink_CreateParams                    IPCIn_DSP1_EVE4_3Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_EVE3_3Prm;
       IpcLink_CreateParams                    IPCIn_EVE3_IPU1_0_0Prm;
       AlgorithmLink_SparseOpticalFlowCreateParams Alg_SparseOpticalFlow_2Prm;
       IpcLink_CreateParams                    IPCOut_EVE3_DSP1_0Prm;
       IpcLink_CreateParams                    IPCIn_DSP1_EVE3_2Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_EVE2_2Prm;
       IpcLink_CreateParams                    IPCIn_EVE2_IPU1_0_0Prm;
       AlgorithmLink_SparseOpticalFlowCreateParams Alg_SparseOpticalFlow_1Prm;
       IpcLink_CreateParams                    IPCOut_EVE2_DSP1_0Prm;
       IpcLink_CreateParams                    IPCIn_DSP1_EVE2_1Prm;
       IpcLink_CreateParams                    IPCOut_IPU1_0_EVE1_1Prm;
       IpcLink_CreateParams                    IPCIn_EVE1_IPU1_0_0Prm;
       AlgorithmLink_SparseOpticalFlowCreateParams Alg_SparseOpticalFlow_0Prm;
       IpcLink_CreateParams                    IPCOut_EVE1_DSP1_0Prm;
       IpcLink_CreateParams                    IPCIn_DSP1_EVE1_0Prm;
       MergeLink_CreateParams                  MergePrm;
       SyncLink_CreateParams                   Sync_2Prm;
       AlgorithmLink_SfmMainCreateParams       Alg_SfmMainPrm;
       IpcLink_CreateParams                    IPCOut_DSP1_DSP2_2Prm;
       IpcLink_CreateParams                    IPCIn_DSP2_DSP1_0Prm;
       AlgorithmLink_SfmLinearTwoViewCreateParams Alg_SfmLinearTwoViewPrm;
       DupLink_CreateParams                    Dup_posePrm;
       IpcLink_CreateParams                    IPCOut_DSP1_A15_0_0Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_DSP1_1Prm;
       AlgorithmLink_SfmMapCreateParams        Alg_SfmMapPrm;
       IpcLink_CreateParams                    IPCOut_DSP1_A15_0_1Prm;
       IpcLink_CreateParams                    IPCIn_A15_0_DSP1_2Prm;
       Sgx3DsfmLink_CreateParams               Sgx3DsfmPrm;
       IpcLink_CreateParams                    IPCOut_A15_0_IPU1_0_0Prm;
       IpcLink_CreateParams                    IPCIn_IPU1_0_A15_0_0Prm;
       DisplayLink_CreateParams                Display_M4Prm;
       GrpxSrcLink_CreateParams                GrpxSrcPrm;
       DisplayLink_CreateParams                Display_GrpxPrm;
} chains_lvdsVipMultiCam_3d_perceptionObj;

Void chains_lvdsVipMultiCam_3d_perception_SetLinkId(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Void chains_lvdsVipMultiCam_3d_perception_ResetLinkPrms(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Void chains_lvdsVipMultiCam_3d_perception_SetPrms(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Void chains_lvdsVipMultiCam_3d_perception_ConnectLinks(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Int32 chains_lvdsVipMultiCam_3d_perception_Create(chains_lvdsVipMultiCam_3d_perceptionObj *pObj, Void *appObj);

Int32 chains_lvdsVipMultiCam_3d_perception_Start(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Int32 chains_lvdsVipMultiCam_3d_perception_Stop(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Int32 chains_lvdsVipMultiCam_3d_perception_Delete(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Void chains_lvdsVipMultiCam_3d_perception_printBufferStatistics(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Void chains_lvdsVipMultiCam_3d_perception_printStatistics(chains_lvdsVipMultiCam_3d_perceptionObj *pObj);

Void chains_lvdsVipMultiCam_3d_perception_SetAppPrms(chains_lvdsVipMultiCam_3d_perceptionObj *pObj, Void *appObj);

#endif /* _chains_lvdsVipMultiCam_3d_perception_H_ */