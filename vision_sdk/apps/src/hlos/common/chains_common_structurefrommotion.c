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
#include <src/hlos/common/chains_common.h>

/**
 *******************************************************************************
 *
 * \brief   Set SfM create parameters
 *
 *******************************************************************************
*/
Void ChainsCommon_StructureFromMotion_SetParams(
		SfmMain_CreateParams *mainprms,
		SfmLinearTwoView_CreateParams *ltvprms,
		SfmMap_CreateParams *mapprms,
		UInt32 numCams,
		UInt32 maxNumPoints)
{
    //Sfm Main
	mainprms->numCams = numCams ; //number of cameras in use
    mainprms->maxNumPoints = maxNumPoints;  //maximum number of points that will be processed

    mainprms->resetAfterNumIdleFrames = 600;

    mainprms->tuning_prms.y_roi[0] = 280;
    mainprms->tuning_prms.y_roi[1] = 235;
    mainprms->tuning_prms.y_roi[2] = 250;
    mainprms->tuning_prms.y_roi[3] = 210;
    mainprms->tuning_prms.y_roi[4] = 0; //NA
    mainprms->tuning_prms.y_roi[5] = 0; //NA

    mainprms->tuning_prms.em_fisheyeRadius 	= 500;
    mainprms->tuning_prms.em_thresh_init 		= 4;
    mainprms->tuning_prms.em_num_iter 			= 4;
    mainprms->tuning_prms.em_min_mag 			= 5e-1;
    mainprms->tuning_prms.em_min_num_inliers 	= 5;

    mainprms->tuning_prms.gpem_roi_xmin = 110;
    mainprms->tuning_prms.gpem_roi_ymin = 240;
    mainprms->tuning_prms.gpem_roi_width = 500;

    mainprms->tuning_prms.fc_max_radius 	= 500;
    mainprms->tuning_prms.fc_min_numTracks = 30;

    mainprms->tuning_prms.fc_max_y[0] = 1e30;
    mainprms->tuning_prms.fc_max_y[1] = 660;
    mainprms->tuning_prms.fc_max_y[2] = 1e30;
    mainprms->tuning_prms.fc_max_y[3] = 700;
    mainprms->tuning_prms.fc_max_y[4] = 0; //NA
    mainprms->tuning_prms.fc_max_y[5] = 0; //NA

    mainprms->tuning_prms.maxHeightGround = 10;
    mainprms->tuning_prms.movingAvgWindow  = 3;

    mainprms->motionDetect_prms.stillPointsRatioTresh = 0.1f;
    mainprms->motionDetect_prms.pixelDiffThresh = 256 / 128;
    mainprms->motionDetect_prms.numCamsInMotionThresh = 2;

    //Sfm Linear Two View
    ltvprms->numCams = numCams ; //number of cameras in use
    ltvprms->maxNumPoints = maxNumPoints;  //maximum number of points that will be processed

    ltvprms->tuning_prms.ransac_errorMeasure 	= 0;
    ltvprms->tuning_prms.ransac_iters 			= 200;
    ltvprms->tuning_prms.ransac_minNumInliers 	= 16;
    ltvprms->tuning_prms.ransac_points 			= 9;
    ltvprms->tuning_prms.ransac_threshold 		= 0.002;
    ltvprms->tuning_prms.ransac_maxCondNumber 	= 2000;
    ltvprms->maxNumInliers = 1024;

    //Sfm Mapping
	mapprms->numInPoints = numCams * maxNumPoints;
    mapprms->dx = 20;
	mapprms->dy = 20;
	mapprms->xmin = -900;
	mapprms->xmax =  900;
	mapprms->ymin = -1000; //was -500
	mapprms->ymax =  2000; //was -2500
	mapprms->minConfid = 0.85;
	mapprms->maxHeight = 500;
	mapprms->minHeight = 70;
	mapprms->minProbPerCell = 2;
	mapprms->dilateRange = 2;
	mapprms->erodeRange = 1;
	mapprms->maxNumBoxes = 12;
	mapprms->minSumProbs = 10;
	mapprms->minDistBoxTracking = 120;

}

