/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*                    Perception and Analytics Lab
*
*         Copyright (c) 2016 Texas Instruments, Incorporated.
*                        All Rights Reserved.
*
*
*          FOR TI INTERNAL USE ONLY. NOT TO BE REDISTRIBUTED.
*
*                 TI Confidential - Maximum Restrictions
*
*
*
*=======================================================================
*
*  File: iSeamDetectionAlgo.h
*
=======================================================================*/

#ifndef _ISEAMDETECTIONALGO_H_
#define _ISEAMDETECTIONALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "memRequestAlgo.h"
#include "../algorithmSrc/include/RVPGlobalDefs.h"

#ifndef PC_VERSION
	#include <include/alglink_api/algorithmLink_seamDetection.h>
	#include <include/link_api/system.h>
	#include <include/link_api/system_common.h>
	#include <src/rtos/utils_common/include/utils_mem.h>
        #include "RVPCommonDefs.h"
#else
        #include "../algorithmSrc/include/Aux_calib_functions.h"
#endif


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

//CREATION PARAMETERS
typedef struct {
	//Input frame size

	Word16		RVPInCamFrmHeight;
	Word16		RVPInCamFrmWidth;

	//output frame size
	Word16		RVPOutDisplayHeight;
	Word16		RVPOutDisplayWidth;

	//number of cameras
	Byte        numCameras;

	// Transformed frame buffer
	Byte*	TransformedfrmBuffer[MAX_INPUT_CAMERAS];

	//Transformed disparity buffer
	Byte*	TransformedDisparityFrame;

	//blendLUT buffer (output buffer)
	Byte*	outBlendBuffer;

	//blendLUT buffer (intermediate buffer)
	Byte*	intBlendBuffer;

	//blendLUT buffer (previous buffer)
	Byte*	prevBlendBuffer;

	//previous seam start and end x-coordinates; order: seam1_x1, seam1_x2, seam2_x1, seam2_x2
	Word16* prevSeamX;
	Word16* currSeamX;

	//distance from previous seam cost buffer
	float*	prevCostBuffer;

	//calibration parameters
	float calmatBuffer[12 * RVP_MAX_NUM_VIEWS];
	float *cam_world_loc; //world locations of the cameras

	//overlapping bounds
	Word16 overlapBounds[8];

	Byte seamdetectionMode; //1-wall; 2-ground; 3-combine
	Byte wallDispDelta; // Search is restricted to a small disparity range around the wall distance
	Byte maxDisparity;  // Maximum disparity provided by stereo

	Byte stereo_offsetX, stereo_offsetY; // Stereo parameters decided by max disparity/downsampling factor, census transform on stereo engine

	Byte minSeamDiff; //minimum difference from previous seam; to prevent jitter
	Byte maxSeamDiff; //maximum difference from previous seam; to prevent jumping

	//temporal smoothing parameters
	float temporalWeight; //1st method, using temporal weighting of cost function
	Byte temporalSmoothing_maxPix; //2nd method: maximum pixel displacement from previous seam allowed for newly-selected seam
	Byte temporalSmoothing_minPix; //2nd method: minimum displacement between new & old seams for newly-selected seam to replace previous seam; prevent jitter

	Byte  Stitch_blendlength;

	Word16 searchspacewidth; //Search space width for non-vertical seam locations
	Word16 searchspacestep; //Search space steps-ze for non-vertical seam locations (search only few possible locations)


	float focalLength; // Input camera focal length

	Word16 *xseambuffer;
	Word16 *xseam;

	//Other RVP Parameters:

	//scale virtual camera default physical location (midpoint between mirror cameras)
	float vc_scale_height; //scale in z-direction
	float vc_scale_depth; //scale in y-direction

	Word16 vc_wall_distance; //distance of wall from virtual camera
	float vc_vf; //virtual camera focal length
	Word16 vc_rotx; //rotation of virtual camera about x-axis
	Word16 vc_roty;
	Word16 vc_rotz;

	float *vcam_proj_mat; //virtual camera projection matrix

	//Image Transformation params
	Word32 Trans_RVP_width[RVP_MAX_NUM_VIEWS + 1];
	Word32 Trans_RVP_height[RVP_MAX_NUM_VIEWS + 1];
	Word32 start_x_in_op[RVP_MAX_NUM_VIEWS + 1];

} RVP_SeamDetection_CreationParamsStruct;


/**
 *******************************************************************************
 *
 *   \brief Structure containing the Seam Detection control parameters
 *
 *******************************************************************************
*/
typedef struct{
	Byte dummy; //to be extended later
} RVP_SeamDetection_ControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
/*******************************************************************************
*
* \brief Implementation of memory query function for Seam Detection algorithm
*
******************************************************************************/
void Alg_SeamDetectionMemQuery(RVP_SeamDetection_CreationParamsStruct *rvpSeamDetectionCreationParams,
	AlgLink_MemRequests *memPtr,
	Byte FirstTimeQuery);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for Seam Detection algo
 *
 * \param  pCreateParams    [IN] Creation parameters for Seam Detection Algorithm
 *
 * \return  Handle to algorithm if creation is successful else return NULL
 *
 *******************************************************************************
 */
void *Alg_SeamDetectionCreate(RVP_SeamDetection_CreationParamsStruct *pCreateParams,
							  AlgLink_MemRequests *memPtr);

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for Seam Detection algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV 
 *        It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned. 
 *        
 * \param  algHandle				  [IN] Algorithm object handle
 * \param pTransformedImageFrames     Transformed image output pointer
 * \param pTransformedDisparityFrame  Transformed disparity map output pointer
 * \param previousLUTPtr              Blend LUT from previous frame for temporal consistency
 * \param outputLUTPtr                Blend LUT for current frame
 * \param pInputCalibParams           Input calibration parameters for cameras
 * \param  SeamDetection_Mode		  [IN] 0:disabled 1:enabled (TBD)
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 *
 *******************************************************************************
 */
Int32 Alg_SeamDetectionProcess(void	  *algHandle,
	System_VideoFrameCompositeBuffer  *pTransformedImageFrames,
#ifdef PC_VERSION
        // outDisparity Frame is combined with input images in embedded implementation because, they need to be on the same composite buffer for Sync Link
	System_VideoFrameBuffer           *pTransformedDisparityFrame,
#endif
	void*                             previousLUTPtr,
	void*                             outputLUTPtr,
	Word16                            *poutseam1,
	Word16                            *poutseam2,
	float                             *pInputCalibParams,
	Byte                              SeamDetection_Mode);
/**
 *******************************************************************************
 *
 * \brief Implementation of Control for Seam Detection algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  GAlign_Mode			 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32	Alg_SeamDetectionControl(	void			        *algHandle,
									RVP_SeamDetection_ControlParams *pControlParams);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for Seam Detection algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32	Alg_SeamDetectionDelete(	void	*algHandle, AlgLink_MemRequests *memPtr);

void *passOutBlendBuffer(void *algHandle);
void *passCurrSeams(void *algHandle, Byte seamNo);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
