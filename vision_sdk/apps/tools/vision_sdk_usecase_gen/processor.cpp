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
#include "processor.h"
#include "error.h"
#include "support.h"

Processor::Processor() {
    for (int i = 0; i < NUMPROC; i++)
        for (int j = 0; j < ClassCount; j++)
            objsAsgn[i][j] = 0;
    for (int i = 0; i < NUMPROC; i++)
        objCount[i] = 0;
    for (int i = 0; i < ClassCount; i++)
        linkIDAsgn[i] = 0;
}

int Processor::getProcID(ProcType pType, ClassType cType, string name) {
    int num;
    switch (cType) {
        case cAVBReceive:
        case cAVBTransmit:
        case cTFDTPReceive:
            if(!(pType == IPU1_1 || pType == IPU1_0 || pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0, IPU1_1, A15])");
            break;
        case cDataCollect:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15])");
            break;
        case cLidarCapture:
        case cLidarCloud:
        case cLidarCloudXForm:
            if (!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15])");
            break;
        case cLidarGPCLink:
            if (!(pType == A15 || pType == IPU1_0 || pType == IPU1_1 || pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15, DSP1, DSP2, IPU1_0, IPU1_1])");
            break;
        case cImuLink:
            if (!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15])");
            break;
        case cDumpLink:
            if (!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15])");
            break;
        case cUndumpLink:
            if (!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15])");
            break;
        case cOGLink:
            if (!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15])");
            break;
        case cDecode:
        case cDisplayCtrl:
        case cDisplay:
        case cDisplayMultiPipe:
        case cEncode:
        case cGrpxSrc:
        case cVPE:
        case cHcf:
        case cCapture:
        case cDssM2mWb:
        case cAutosarIpcIn:
        case cAutosarIpcOut:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cIssCapture:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cIssM2mIsp:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cIssM2mSimcop:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cIssM2mResizer:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cRadarDraw:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cUltrasonicCapture:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;

        case cSgxFrmcpy:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cDrmDisplay:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cDispDistSrc:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cSgx3Dsrv:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cSgx3Dsfm:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cSgxLink:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cAlg_ColorToGray:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_DMASwMs:
            if(!(pType == DSP1 || pType == DSP2 || pType == A15 || pType == IPU1_0 || pType == IPU1_1 || pType == IPU2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2, A15, IPU1_0, IPU1_1, IPU2]) !!!");
            break;
            case cAlg_VPESwMs:
            if(!(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0, IPU1_1, IPU2]) !!!");
            break;
        case cAlg_DenseOptFlow:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_EdgeDetect:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_SoftIsp:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_IssAewb:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;

        case cAlg_FrameCopy:
            if(!(pType == DSP1 || pType == DSP2 || pType == A15 || pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2, A15, EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_SafeFrameCopy:
            if(!(pType == DSP1 || pType == DSP2 || pType == A15 || pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2, A15, EVE1, EVE2, EVE3, EVE4]) !!!");
            break;

        case cAlg_MyAlgFinish:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;

        case cAlg_MyAlg1:
        case cAlg_MyAlg2:
        case cAlg_MyAlg3:
            if(!(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2 || pType == DSP1 || pType == DSP2 || pType == A15 || pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2, A15, EVE1, EVE2, EVE3, EVE4, IPU1_0, IPU1_1, IPU2]) !!!");
            break;

        case cAlg_Census:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_DisparityHamDist:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_UltrasonicFusion:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_FeaturePlaneComputation:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_ImagePreProcess:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_ImgPyramid:
            if(!(pType == IPU1_0 || pType == IPU1_1))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0, IPU1_1]) !!!");
            break;
        case cAlg_FPCompute:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_ObjectDetection:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_ObjectClassification:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_DriverMonitor:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_GeoAlign:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_GeoAlign3D:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_LaneDetect:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_Sfm:
        case cAlg_Fcw:
        case cAlg_Clr:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_ObjectDraw:
            if(!(pType == IPU1_0 || pType == IPU1_1 || pType == IPU2 || pType == DSP1 || pType == DSP2 || pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0, IPU1_1, IPU2, DSP1, DSP2, A15]) !!!");
            break;
        case cAlg_PhotoAlign:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_Synthesis:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_SfmLinearTwoView:
             if(!(pType == DSP1 || pType == DSP2))
                 CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
             break;
        case cAlg_SfmMain:
             if(!(pType == DSP1 || pType == DSP2))
                 CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
             break;
        case cAlg_SfmMap:
             if(!(pType == DSP1 || pType == DSP2))
                 CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
             break;
        case cAlg_SfmSurround:
             if(!(pType == DSP1 || pType == DSP2))
                 CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
             break;
        case cAlg_VectoImg:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_SubframeCopy:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_RemapMerge:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4]) !!!");
            break;
        case cAlg_StereoPostProcess:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_SceneObstructionDetect:
            if(!(pType == DSP1 || pType == DSP2 || pType == A15 || pType == IPU1_0 || pType == IPU1_1))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2, A15, IPU1_0, IPU1_1]) !!!");
            break;
        case cAlg_Crc:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cAlg_AutoChartDetect:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_PoseEstimate:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cEpLink:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cAlg_DeWarp:
            if(!(pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[IPU1_0]) !!!");
            break;
        case cAlg_OpenCVCanny:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cAlg_UndistortTracks:
             if(!(pType == DSP1 || pType == DSP2))
                 CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
             break;
        case cAlg_Triangulation:
             if(!(pType == DSP1 || pType == DSP2))
                 CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
             break;
        case cAlg_AutoRemap:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_StereoApp:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_SeamDetection:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_Stitching:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_AdaptiveBowl:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_tidl:
            if(!(pType == EVE1 || pType == EVE2 || pType == EVE3 || pType == EVE4 || pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[EVE1, EVE2, EVE3, EVE4, DSP1, DSP2]) !!!");
            break;
        case cAlg_tiop:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
        case cAlg_tidlpreproc:
            if(!(pType == A15 || pType == IPU1_0))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15, IPU1_0]) !!!");
            break;
        case cAlg_tidlpostproc:
            if(!(pType == A15))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[A15]) !!!");
            break;
        case cAlg_drawRearview:
            if(!(pType == DSP1 || pType == DSP2))
                CHECK_ERROR(SHOULD_NOT_REACH, "Error: Link [" + name + "] cannot be assigned to CPU [" + procName[pType] + "] (Valid CPUs:[DSP1, DSP2]) !!!");
            break;
    }
    if (getRoot(name) == "Alg")
        cType = cAlg;
    num = objsAsgn[pType][cType];
    objsAsgn[pType][cType]++;
    objCount[pType]++;
    return num;
}

int Processor::getObjsAssgn(ProcType pType) {
    return objCount[pType];
}

string Processor::getLinkIdType(ClassType cType, string name)
{
    string linkType;

    linkType = string("SYSTEM_LINK_TYPE_");

    switch (cType) {
    case cAVBReceive:
        linkType += string("AVB_RX");
        break;
    case cAVBTransmit:
        linkType += string("AVB_RX");
        break;
    case cAlg:
        linkType += string("ALG");
        break;
    case cCapture:
        linkType += string("CAPTURE");
        break;
    case cIssCapture:
        linkType += string("ISSCAPTURE");
        break;
    case cIssM2mIsp:
        linkType += string("ISSM2MISP");
        break;
    case cIssM2mSimcop:
        linkType += string("ISSM2MSIMCOP");
        break;
    case cIssM2mResizer:
        linkType += string("ISSM2MRESIZER");
        break;
    case cUltrasonicCapture:
        linkType += string("ULTRASONIC_CAPTURE");
        break;
    case cDecode:
        linkType += string("VDEC");
        break;
    case cEncode:
        linkType += string("VENC");
        break;
    case cDisplayCtrl:
        linkType += string("DISPLAY_CTRL");
        break;
    case cDisplay:
        linkType += string("DISPLAY");
        break;
    case cDup:
        linkType += string("DUP");
        break;
    case cSplit:
        linkType += string("SPLIT");
        break;
    case cGate:
        linkType += string("GATE");
        break;
    case cGrpxSrc:
        linkType += string("GRPX_SRC");
        break;
    case cIPCIn:
        linkType += string("IPC_IN");
        break;
    case cIPCOut:
        linkType += string("IPC_OUT");
        break;
    case cMerge:
        linkType += string("MERGE");
        break;
    case cNull:
        linkType += string("NULL");
        break;
    case cNullSource:
        linkType += string("NULL_SRC");
        break;
    case cSelect:
        linkType += string("SELECT");
        break;
    case cSync:
        linkType += string("SYNC");
        break;
    case cSgxFrmcpy:
        linkType += string("SGXFRMCPY");
        break;
    case cSgx3Dsrv:
        linkType += string("SGX3DSRV");
        break;
    case cSgx3Dsfm:
        linkType += string("SGX3DSFM");
        break;
    case cVPE:
        linkType += string("VPE");
        break;
    case cDssM2mWb:
        linkType += string("DSSM2MWB");
        break;
    case cHcf:
        linkType += string("HCF");
        break;
    case cDefLink:
        CHECK_ERROR(false, "Warning: Custom defined Link [" + name + "] found. \n"
                         + "         You will need to manually edit the generated .c file to fill in \n"
                         + "         missing information like Link ID, create parameters !!!");
        break;
    case cEpLink:
        linkType += string("EP");
        break;
    case cNetworkTx:
        linkType += string("NETWORKTX");
        break;
    case cNetworkRx:
        linkType += string("NETWORKRX");
        break;
    case cAutosarIpcIn:
        linkType += string("AUTOSAR_IPC_IN");
        break;
    case cAutosarIpcOut:
        linkType += string("AUTOSAR_IPC_OUT");
        break;
    default:
        CHECK_ERROR_ABORT(false, "Error: Link [" + name + "] name does not match supported links. Use '-h' option to see list of supported links !!!");
    };
    return linkType;
}

string Processor::allocDynamicLinkId(ProcType pType, ClassType cType, string name)
{
    return string("System_linkIdAlloc( SYSTEM_PROC_")
                + procName[pType] + ", " + getLinkIdType(cType, name) + " )"
                ;
}

string Processor::freeDynamicLinkId(ProcType pType, ClassType cType, string name)
{
    return string("System_linkIdFree( ") + getLinkIdType(cType, name) + string(", ") + name + string(")")
                ;
}

string Processor::getLinkID(ProcType pType, ClassType cType, int procID, string name) //TODO: Confirm this is the way
{
    string linkIDName;
    string pName = procName[pType];
    switch (cType) {
    case cAVBReceive:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                        "Error: Link [AbvRx] cannot have more than one instance !!!")
                ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_AVB_RX)");
        linkIDAsgn[cType]++;
        break;
    case cAVBTransmit:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                        "Error: Link [AbvTx] cannot have more than one instance !!!")
                ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_AVB_TX_") + toString(procID) + string(")");;
        linkIDAsgn[cType]++;
        break;
    case cTFDTPReceive:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                        "Error: Link [AbvRx] cannot have more than one instance !!!")
                ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_TFDTP_RX)");
        linkIDAsgn[cType]++;
        break;
    case cAlg:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_ALG_")
                + toString(procID) + string(")"); //linkIDAsgn[cType]
        linkIDAsgn[cType]++;
        break;
    case cCapture:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 2,
                "Error: Link [Capture] cannot have more than two instance !!!")
        ;
        linkIDName = string("SYSTEM_LINK_ID_CAPTURE_")
            + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cIssCapture:
        linkIDName = string("SYSTEM_LINK_ID_ISSCAPTURE_")
                + toString(procID); //linkIDAsgn[cType]
        linkIDAsgn[cType]++;
        break;
    case cIssM2mIsp:
        linkIDName = string("SYSTEM_LINK_ID_ISSM2MISP_")
                + toString(procID); //linkIDAsgn[cType]
        linkIDAsgn[cType]++;
        break;
    case cIssM2mSimcop:
        linkIDName = string("SYSTEM_LINK_ID_ISSM2MSIMCOP_")
                + toString(procID); //linkIDAsgn[cType]
        linkIDAsgn[cType]++;
        break;
    case cIssM2mResizer:
        linkIDName = string("SYSTEM_LINK_ID_ISS_RESIZER_")
                + toString(procID); //linkIDAsgn[cType]
        linkIDAsgn[cType]++;
        break;
    case cRadarDraw:
        linkIDName = string("SYSTEM_LINK_ID_RADAR_DRAW_")
                + toString(procID); //linkIDAsgn[cType]
        linkIDAsgn[cType]++;
        break;
    case cUltrasonicCapture:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [UltrasonicCapture] cannot have more than one instance !!!")
        ;
        linkIDName = "SYSTEM_LINK_ID_ULTRASONIC_CAPTURE";
        linkIDAsgn[cType]++;
        break;

    case cDecode:
        linkIDName = string("SYSTEM_LINK_ID_VDEC_")
                + toString(linkIDAsgn[cType]); //NO CHECK
        linkIDAsgn[cType]++;
        break;
    case cEncode:
        linkIDName = string("SYSTEM_LINK_ID_VENC_")
                + toString(linkIDAsgn[cType]); //NO CHECK
        linkIDAsgn[cType]++;
        break;
    case cDisplayCtrl:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [DisplayCtrl] cannot have more than one instance !!!")
        ;
        linkIDName = string("SYSTEM_LINK_ID_DISPLAYCTRL")
                + toString(linkIDAsgn[cType]); //NO CHECK
        linkIDAsgn[cType]++;
        break;
    case cDisplay:
        linkIDName = string("SYSTEM_LINK_ID_DISPLAY_")
                + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cDisplayMultiPipe:
        linkIDName = string("SYSTEM_LINK_ID_DISPLAY_MULTI_PIPE_")
                + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cDup:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_DUP_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cSplit:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_SPLIT_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cGate:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_GATE_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cGrpxSrc:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_GRPX_SRC_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cIPCIn:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_IPC_IN_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cIPCOut:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_IPC_OUT_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cMerge:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_MERGE_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cNull:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_NULL_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cDataCollect:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_DATA_COLLECT_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cNullSource:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_NULL_SRC_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cSelect:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_SELECT_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cSync:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_SYNC_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cSgxFrmcpy:
        linkIDName = "SYSTEM_LINK_ID_SGXFRMCPY_" + toString(procID);
        linkIDAsgn[cType]++;
        break;
    case cDrmDisplay:
        linkIDName = "SYSTEM_LINK_ID_DRMDISPLAY_" + toString(procID);
        linkIDAsgn[cType]++;
        break;
    case cDispDistSrc:
        linkIDName = "SYSTEM_LINK_ID_DISPDISTSRC_LINK_" + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cSgx3Dsrv:
        linkIDName = "SYSTEM_LINK_ID_SGX3DSRV_" + toString(procID);
        linkIDAsgn[cType]++;
        break;
    case cSgx3Dsfm:
        linkIDName = "SYSTEM_LINK_ID_SGX3DSFM_" + toString(procID);
        linkIDAsgn[cType]++;
        break;
    case cSgxLink:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [SgxLink] cannot have more than one instance !!!")
        ;
        linkIDName = "SYSTEM_LINK_ID_SGX_LINK";
        linkIDAsgn[cType]++;
        break;
    case cVPE:
        linkIDName = string("SYSTEM_LINK_ID_VPE_")
                + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cDssM2mWb:
        linkIDName = string("SYSTEM_LINK_ID_DSSM2MWB_")
                + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cHcf:
        linkIDName = string("SYSTEM_LINK_ID_HCF_")
                + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cDefLink:
        CHECK_ERROR(false, "Warning: Custom defined Link [" + name + "] found. \n"
                         + "         You will need to manually edit the generated .c file to fill in \n"
                         + "         missing information like Link ID, create parameters !!!");
        break;
    case cEpLink:
        linkIDName = string("SYSTEM_LINK_ID_EP_")
                + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cLidarCapture:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [LidarCloud] cannot have more than one instance !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_LIDAR_CAPTURE)");
        linkIDAsgn[cType]++;
        break;
    case cLidarCloud:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [LidarCloud] cannot have more than one instance !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_LIDAR_CLOUD)");
        linkIDAsgn[cType]++;
        break;
    case cLidarCloudXForm:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [LidarCloudXForm] cannot have more than one instance !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_LIDAR_XFORM)");
        linkIDAsgn[cType]++;
        break;
    case cLidarGPCLink:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [LidarGPC] cannot have more than one instance !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_LIDAR_GPC)");
        linkIDAsgn[cType]++;
        break;
    case cImuLink:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [ImuLink] cannot have more than one instance !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_IMU)");
        linkIDAsgn[cType]++;
        break;
    case cDumpLink:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 4,
                "Error: Link [DumpLink] cannot have more than four instances !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_DUMP_LINK_")
                    + toString(linkIDAsgn[cType]) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cUndumpLink:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 4,
                "Error: Link [UndumpLink] cannot have more than four instances !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_UNDUMP_LINK_")
                    + toString(linkIDAsgn[cType]) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cOGLink:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 2,
                "Error: Link [OGLink] cannot have more than two instances !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_OG_LINK_")
                    + toString(linkIDAsgn[cType]) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cSlam:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 1,
                "Error: Link [Slam] cannot have more than one instance !!!")
        ;
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_SLAM)");
        linkIDAsgn[cType]++;
        break;
    case cNetworkTx:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_NETWORK_TX_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cNetworkRx:
        linkIDName = pName + string("_LINK (SYSTEM_LINK_ID_NETWORK_RX_")
                + toString(procID) + string(")");
        linkIDAsgn[cType]++;
        break;
    case cAutosarIpcIn:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 2,
                "Error: Link [Autosar Ipc In] cannot have more than two instance !!!")
        ;
        linkIDName = string("SYSTEM_LINK_ID_AUTOSAR_IPC_IN_")
            + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    case cAutosarIpcOut:
        CHECK_ERROR_ABORT(linkIDAsgn[cType] < 2,
                "Error: Link [Autosar Ipc Out] cannot have more than two instance !!!")
        ;
        linkIDName = string("SYSTEM_LINK_ID_AUTOSAR_IPC_OUT_")
            + toString(linkIDAsgn[cType]);
        linkIDAsgn[cType]++;
        break;
    default:
        CHECK_ERROR_ABORT(false, "Error: Link [" + name + "] name does not match supported links. Use '-h' option to see list of supported links !!!");
    };
    return linkIDName;
}
