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
 * \file iSfmMapAlgo.h
 *
 * \brief Interface file
 *
 *        This algorithm is only for demonstrative purpose. 
 *        It is NOT product quality.
 *
 * \version 0.0 (Dec 2015) : Mueller
 *
 *******************************************************************************
 */

#ifndef _I_SFM_MAP_ALGO_H_
#define _I_SFM_MAP_ALGO_H_

#include "sfmCommonDefs.h"

/*******************************************************************************
 * Macros
 *******************************************************************************/
#define SFM_MAP_NUM_OG_CELLS_LIMIT (22500) /*maximum number of cells supported (ca. 3m x 3m with 0.02m resolution)*/
#define SFM_MAP_NUM_BOXES_LIMIT (12) /*maximum number of boxes supported*/

#define OG_LABEL_ENABLE (0) /*1 = enable label map output*/
#define OG_LABEL_UNKNOWN (128)
#define OG_LABEL_FREE (255)
#define OG_LABEL_OCCUPIED (0)

typedef enum
{
  RESET_MAP
} SfmMapControlCommand;

/*******************************************************************************
* Data Structures
*******************************************************************************/
typedef struct
{
	Point3D_f vertex[8];
} Box3D_f;

typedef struct {
	Box3D_f box;
	Point3D_f center;
	UInt32 sumProbs;
	UInt32 age;
} ObjectBox;

/*******************************************************************************
* Parameters
********************************************************************************/

typedef struct 
{
	Flouble dx, dy; //OG's cell width (x,y) in m 
	Flouble xmin, xmax, ymin, ymax; //OG grid's bounds in m
	Flouble minConfid; //minimum confidence for a point to be mapped
	Flouble maxHeight; //maximum height in m for OG map
	Flouble minHeight; //minimum height in m for OG cell to be considered for box generation
	Flouble minDistBoxTracking;//minimum distance between two box centroids to be considered tracked as the same
	UInt32 numInPoints; //max number of 3D points (3d point input buffer size in # points)
	UInt32 minProbPerCell; //minimum probability [0,255] for a OG cell to be considered for box generation
	Int32 dilateRange; //range of dilation filter for cell clustering
	Int32 erodeRange; //range of erosion filter to undo spread from dilation filter 
	Int32 maxNumBoxes; //maximum number of boxes that will be tracked
	UInt32 minSumProbs;// minimum sum of probs for a connected component to be considered an object box candidate
} SfmMap_CreateParams;

typedef struct
{
	SfmMapControlCommand controlCommand;
} SfmMap_ControlParams;


/*******************************************************************************
*  Functions
********************************************************************************/
void Alg_SfmMapMemQuery(
			SfmMap_CreateParams *createParams,
			AlgLink_MemRequests *memPtr,
			UInt8 FirstTimeQuery);
void *Alg_SfmMapCreate(
			SfmMap_CreateParams *createParams,
			AlgLink_MemRequests *memPtr);
Int32	Alg_SfmMapProcess(
			void *algHandle,
			Point3D_f *xyzwInPtr, //3D points in world coordinates
			Flouble *confidsInPtr, //confidence for each 3D point
			Pose3D_f *systemPose_ewInPtr, //pose of vehicle in world map
			ObjectBox * boxesOutPtr,//boxes representing objects
			UInt8 *labelMapOutPtr); //label map (unknown, free, occupied) 
Int32	Alg_SfmMapControl(
			void *algHandle,
			SfmMap_ControlParams *controlParams);
Int32	Alg_SfmMapDelete(
			void *algHandle,
			AlgLink_MemRequests *memPtr);

#endif



