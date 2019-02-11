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
#ifndef PROC_H
#define PROC_H

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

enum ProcType {
    IPU1_0, IPU1_1, IPU2, A15, DSP1, DSP2, EVE1, EVE2, EVE3, EVE4, NUMPROC
};
static string procName[] = { "IPU1_0", "IPU1_1", "IPU2", "A15_0", "DSP1", "DSP2",
        "EVE1", "EVE2", "EVE3", "EVE4" };

enum ClassType {
    cAVBReceive,
    cAVBTransmit,
    cTFDTPReceive,
    cAlg,
    cAlg_ColorToGray,
    cAlg_DMASwMs,
    cAlg_VPESwMs,
    cAlg_DenseOptFlow,
    cAlg_EdgeDetect,
    cAlg_SoftIsp,
    cAlg_FrameCopy,
    cAlg_SafeFrameCopy,
    cAlg_MyAlgFinish,
    cAlg_MyAlg1,
    cAlg_MyAlg2,
    cAlg_MyAlg3,
    cAlg_Census,
    cAlg_DisparityHamDist,
    cAlg_UltrasonicFusion,
    cAlg_FeaturePlaneComputation,
    cAlg_ImagePreProcess,
    cAlg_ImgPyramid,
    cAlg_FPCompute,
    cAlg_ObjectDetection,
    cAlg_ObjectClassification,
    cAlg_DriverMonitor,
    cAlg_GeoAlign,
    cAlg_GeoAlign3D,
    cAlg_ObjectDraw,
    cAlg_PhotoAlign,
    cAlg_Synthesis,
    cAlg_SparseOpticalFlow,
    cAlg_SfmLinearTwoView,
    cAlg_SfmMain,
    cAlg_SfmMap,
    cAlg_SfmSurround,
    cAlg_LaneDetect,
    cAlg_Clr,
    cAlg_Sfm,
    cAlg_Fcw,
    cAlg_VectoImg,
    cAlg_IssAewb,
    cAlg_Crc,
    cAlg_DeWarp,
    cAlg_OpenCVCanny,
    cAlg_RadarProcess,
    cAlg_RadarDraw,
    cAlg_RadarFrameCopy,
    cAlg_RadarPostProc,
    cAlg_UndistortTracks,
    cAlg_Triangulation,
    cAlg_tidl,
    cAlg_tiop,
    cAlg_tidlpreproc,
    cAlg_tidlpostproc,
    cCapture,
    cIssCapture,
    cIssM2mIsp,
    cIssM2mSimcop,
    cIssM2mResizer,
    cRadarDraw,
    cUltrasonicCapture,
    cDecode,
    cDisplayCtrl,
    cDisplay,
    cDisplayMultiPipe,
    cDup,
    cSplit,
    cGate,
    cEncode,
    cGrpxSrc,
    cIPCIn,
    cIPCOut,
    cMerge,
    cNull,
    cNullSource,
    cSelect,
    cSgxFrmcpy,
    cDrmDisplay,
    cDispDistSrc,
    cSgx3Dsrv,
    cSgx3Dsfm,
    cSgxLink,
    cSync,
    cVPE,
    cDssM2mWb,
    cHcf,
    cDefLink,
    cDataCollect,
    cAlg_SubframeCopy,
    cAlg_RemapMerge,
    cAlg_StereoPostProcess,
    cAlg_SceneObstructionDetect,
    cAlg_AutoChartDetect,
    cAlg_PoseEstimate,
    cEpLink,
    cLidarCapture,
    cLidarCloud,
    cLidarCloudXForm,
    cLidarGPCLink,
    cImuLink,
    cDumpLink,
    cUndumpLink,
    cOGLink,
    cSlam,
    cAlg_AutoRemap,
    cAlg_StereoApp,
    cAlg_drawRearview,
    cNetworkTx,
    cNetworkRx,
    cAutosarIpcIn,
    cAutosarIpcOut,
    cAlg_SeamDetection,
    cAlg_Stitching,
    cAlg_AdaptiveBowl,
    ClassCount
};
//Last enum used to keep count

class Processor {
    int objsAsgn[NUMPROC][ClassCount]; //holds no of objs assigned the Proc
    int objCount[NUMPROC]; //Total no of objs assigned to a processor
    int linkIDAsgn[ClassCount]; //TODO: Where to put and see if better idea

public:
    Processor();
    int getProcID(ProcType pType, ClassType cType, string name);
    int getObjsAssgn(ProcType pType);
    string getLinkID(ProcType pType, ClassType cType, int procID, string name);
    string allocDynamicLinkId(ProcType pType, ClassType cType, string name);
    string freeDynamicLinkId(ProcType pType, ClassType cType, string name);
    string getLinkIdType(ClassType cType, string name);
};

#endif
