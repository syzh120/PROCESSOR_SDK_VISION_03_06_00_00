/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file iSfmMainAlgo.h
 *
 * \brief Interface file Main SfM Algorithm
 *
 *        This algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *
 * \version 0.0 (Dec 2015) : Mueller
 *
 *******************************************************************************
 */

#ifndef _I_SFM_MAIN_ALGO_H_
#define _I_SFM_MAIN_ALGO_H_

#include "sfmCommonDefs.h"
#include "iSfmLinearTwoViewAlgo.h"


/*******************************************************************************
 * Macros
 *******************************************************************************/

/*******************************************************************************
* Data Structures
*******************************************************************************/
/*These defines are dependent on Sparse Optical Flow input data*/
#define MAX_NUM_FRAMES_TO_TRACK (16) /*SOF number of tracked frames*/
#define SOF_QVAL_INVERSE (0.0625) /*Factor to convert SOF tracks to float
                                    = 1/(2^4), since SOF format is Q12.4*/
#define SOF_OFFSET (16) /*Offset to convert SOF tracks to float*/

/*******************************************************************************
* Parameters
********************************************************************************/
typedef struct {
	Flouble y_roi[SFM_NUM_CAMS_LIMIT];		//input by the user, and on the fish eye camera.
	Flouble em_fisheyeRadius;	//points with fisheye radius larger than this are not considered
	Flouble em_thresh_init;	//initial threshold for motion thresholding
	Flouble em_min_mag;		//offset in meters for motion thresholding
	Flouble em_min_num_inliers;//minimum number of feature points required
	Flouble gpem_roi_xmin; //in mm, start of GPEM region of interest in x-axis
	Flouble gpem_roi_ymin; //in mm, start of GPEM region of interest in y-axis
	Flouble gpem_roi_width; //in mm, width of GPEM region of interest in both x and y
	Flouble fc_max_radius;		//use only feature correspondences which lie within this radius around fisheye distortion center
	Flouble fc_min_numTracks;	//minimum number of tracks, if less -> reset Layer 2
	Flouble fc_max_y[SFM_NUM_CAMS_LIMIT]; //maximum y for point to be considered (in terms of fisheye, but threshold will happen in normalized domain)
	Flouble maxHeightGround; //maximum height of a point to be considered ground in mm
	Flouble movingAvgWindow; //averaging triangulation error over that many frames
	UInt32  em_num_iter;			//number of motion thresholding iterations
	UInt32  dummy;					// For memory alignment
} SfmMain_TuningParams;

typedef struct {
	float stillPointsRatioTresh; //threshold for ratio of #still points/# points, if ratio>threshold --> standstill
	Int32 pixelDiffThresh; //nom=256=Q4*Q4 from SOF, denom=<pixelthresh>^2
	UInt32 numCamsInMotionThresh; //if more than <> cameras are in motion --> system in motion
} SfmMain_MotionDetectParams;

typedef struct {
	SfmMain_TuningParams tuning_prms;
	SfmMain_MotionDetectParams motionDetect_prms;
	UInt32 numCams; //number of cameras in use
	UInt32 maxNumPoints; //maximum number of points that will be processed
	Int32 resetAfterNumIdleFrames; //reset everything after that many frames of standstill

    Void *pLensPrm;

} SfmMain_CreateParams;

typedef struct
{
	UInt32 none;
} SfmMain_ControlParams;


/*******************************************************************************
*  Functions
********************************************************************************/
void Alg_SfmMainMemQuery(
			SfmMain_CreateParams *createParams,
			AlgLink_MemRequests *memPtr,
			UInt8 FirstTimeQuery);
void *Alg_SfmMainCreate(
			SfmMain_CreateParams *createParams,
			AlgLink_MemRequests *memPtr);
Int32	Alg_SfmMainProcess(
		void *algHandle,
		Int32 *calibDataInPtr, //calmat matrices proving transforms from ground(chart) to camera
		void *tracksInPtr[SFM_NUM_CAMS_LIMIT], //optical flow field (from SOF)
		UInt16 **trackErrsInPtr, //tracking errors (from SOF)
		Pose3D_f *systemPose_ewOutPtr, //current ego system pose: world -> ego-system
		Pose3D_f *camPoses_cwOutPtr, //current camera poses: world -> camera
		Point3D_f *xyzwOutPtr, //3D points in world coordinates
		Flouble *confidsOutPtr, //confidence for each 3D point (-1 if 3D is not valid)
		SfmLtv_API *L2DataOutPtr, //L2 data (to/from LTV)
		UInt32 LTVavailableFlag, //1-LTV link is idle/available 0-LTV link is busy
		UInt32 newCalibrationDataFlag, //new calibration data available->update calibration, 0 - keep old calibration
		Int32 *executeMode); //executeMode to inform framework was happened inside SfmMain
Int32	Alg_SfmMainControl(
			void *algHandle,
			SfmMain_ControlParams *controlParams);
Int32	Alg_SfmMainDelete(
			void *algHandle,
			AlgLink_MemRequests *memPtr);
#endif


