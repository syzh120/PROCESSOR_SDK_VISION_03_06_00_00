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
 * \file iSfmLinearTwoViewAlgo.h
 *
 * \brief Interface file SfM Linear Two View Algorithm
 *
 *        This algorithm is only for demonstrative purpose. 
 *        It is NOT product quality.
 *
 * \version 0.0 (Dec 2015) : Mueller
 *
 *******************************************************************************
 */

#ifndef _I_SFM_LINEAR_TWO_VIEW_ALGO_H_
#define _I_SFM_LINEAR_TWO_VIEW_ALGO_H_

#include "sfmCommonDefs.h"

/*******************************************************************************
 * Macros
 *******************************************************************************/
#define SFM_QRD_FUNCTION 2 /*0-numerical recipes, 1-DSPF C natural, 2-DSPF optimized*/
#define SFM_SVD_FUNCTION 2 /*0-numerical recipes, 1-DSPF C natural, 2-DSPF optimized*/
#define SFM_SVD_NUM_POINTS_LIMIT (1024) /*maximum number of points allowed in SVD (=max #rows)*/

#define SFM_TRIANGULATE_FUNCTION (1) /*0: local linear, inhomogeneous, two-view using QRD
									   1: VLIB, two-views*/
#define SFM_ESSENTIAL_MATRIX_FUNCTION (0) /*0: custom function based on DSPLIB SVD
											1: VLIB's findFmat kernel (currently only for PC)*/

/*******************************************************************************
* Parameters
********************************************************************************/

typedef struct
{
	Flouble ransac_threshold;		//threshold for RANSAC estimation of E
	Flouble ransac_maxCondNumber;	//if condition number of system matrix in E estimation is larger than this -> skip frame
	UInt32 ransac_errorMeasure;			//error measure for full estimation of E, 1 - geometric, 0 - algebraic. FIXME: Currently hardcoded
	UInt32 ransac_iters;				//number of RANSAC iterations on E-estimation   
	UInt32 ransac_minNumInliers;		//if # inliers smaller than this -> skip frame 
	UInt32 ransac_points;				//Number of points for Ransac
} SfmLinearTwoView_TuningParams;

typedef struct {
	SfmLinearTwoView_TuningParams tuning_prms;
	UInt32 numCams;
	UInt32 maxNumPoints;
	UInt32 maxNumInliers; //use only first maxNumInliers inliers for full E-estimation
} SfmLinearTwoView_CreateParams;

typedef struct
{
	UInt32 none;
} SfmLinearTwoView_ControlParams;

/*******************************************************************************
* API
*******************************************************************************/
/*-------------------------------------------------------------------------------
*SfmLtv_API
* - input and output pointers
* - input pointers are read-only
* - output pointers are read and write (in-place)
* - allocated memories are owned by calling function
*    --> calling function needs to ensure that memory is protected
*-------------------------------------------------------------------------------*/

typedef struct {
	/*Inputs*/
	Point2D_f *xy_prv_in[SFM_NUM_CAMS_LIMIT]; //points in 2D normalized image coordinates in first and second L2-frame
	Flouble *confids_prv_in[SFM_NUM_CAMS_LIMIT]; //confidence measures associated with xy_L1_L2OutPtr
	Point2D_f *xy_can_in[SFM_NUM_CAMS_LIMIT]; //points in 2D normalized image coordinates in first and second L2-frame
	Flouble *confids_can_in[SFM_NUM_CAMS_LIMIT]; //confidence measures associated with xy_L1_L2OutPtr
	UInt8 *bCorr_in[SFM_NUM_CAMS_LIMIT]; //boolean array, >0 if entry is a valid point correspondence, 0 otherwise
	/*Outputs*/
	Point3D_f *xyzc_out[SFM_NUM_CAMS_LIMIT]; //points in 3D camera coordinates at second L2-frame
	Pose3D_f *camMotion_out[SFM_NUM_CAMS_LIMIT]; //camera motion, first L2-frame -> second L2-frame
	Flouble *reprojErrs_out[SFM_NUM_CAMS_LIMIT]; //reprojection Errors
	/*Input&Output*/
	UInt8 *status[SFM_NUM_CAMS_LIMIT]; //To indicate if a frame is accepted or rejected in LTV 
} SfmLtv_API;

/*******************************************************************************
*  Functions
********************************************************************************/
void Alg_SfmLinearTwoViewMemQuery(
			SfmLinearTwoView_CreateParams *createParams,
			AlgLink_MemRequests *memPtr,
			UInt8 FirstTimeQuery);
void *Alg_SfmLinearTwoViewCreate(
			SfmLinearTwoView_CreateParams *createParams,
			AlgLink_MemRequests *memPtr);
Int32 Alg_SfmLinearTwoViewProcess(
			void *ah,
			SfmLtv_API *dataInPtr);
Int32 Alg_SfmLinearTwoViewControl( 
			void *ah,
			SfmLinearTwoView_ControlParams *controlParams);
Int32 Alg_SfmLinearTwoViewDelete(
			void *ah,
			AlgLink_MemRequests *memPtr);


#endif


