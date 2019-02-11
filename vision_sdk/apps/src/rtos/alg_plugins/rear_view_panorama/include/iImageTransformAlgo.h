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
*  File: iImageTransformAlgo.h
*
=======================================================================*/

#ifndef _IIMAGETRANSFORMALGO_H_
#define _IIMAGETRANSFORMALGO_H_

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
    #include "RVPCommonDefs.h"
    #include <include/alglink_api/algorithmLink_imageTransform.h>
    #include <include/link_api/system.h>
    #include <include/link_api/system_common.h>
    #include <src/rtos/utils_common/include/utils_mem.h>
#else
    #include "../algorithmSrc/include/rvpGenerateLDCLUT.h"
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

/**
 *******************************************************************************
 *
 *   \brief Structure containing the synthesis create time parameters
 *
 *******************************************************************************
*/
typedef struct {

	//Input frame size
	Word16		RVPInCamFrmHeight;
	Word16		RVPInCamFrmWidth;

	//output frame size
	Word16		RVPOutDisplayHeight;
	Word16		RVPOutDisplayWidth;

	// Disparity map input size
	Word16      RVPDisparityHeight;
	Word16      RVPDisparityWidth;

	//number of cameras
	Byte        numCameras;

	// Transformed frame buffer
	Byte*	TransformedfrmBuffer[RVP_MAX_NUM_VIEWS];

	//Transformed disparity buffer
	Byte*	TransformedDisparityFrame;

	// Calmatbuffer
	float calmatBuffer[12 * RVP_MAX_NUM_VIEWS];
	//float *calmatBuffer;

	// Persmatbuffer
	float persmatBuffer[27];

	//Other RVP Parameters:

	//scale virtual camera default physical location (midpoint between mirror cameras)
	float vc_scale_height; //scale in z-direction
	float vc_scale_depth; //scale in y-direction

	Word16 vc_wall_distance; //distance of wall from virtual camera
	float vc_vf; //virtual camera focal length
	Word16 vc_rotx; //rotation of virtual camera about x-axis
	Word16 vc_roty;
	Word16 vc_rotz;

	float *cam_world_loc;// [3 * RVP_MAX_NUM_VIEWS]; //world locations of the cameras
	float *vcam_proj_mat; //virtual camera projection matrix

	float focalLength; // Input camera focal length

	Byte stereo_offsetX, stereo_offsetY; // Stereo parameters decided by max disparity/downsampling factor, census transform on stereo engine

	// Simcop LDC output height, width for images (currently it is the same for all images)
	Word16 LDC_op_width;
	Word16 LDC_op_height;

	//projective transformation matrices for cameras 0 (right mirror), 1 (left stereo), and 2 (left mirror)
	//	1-D array with 9 elements representing a 3x3 matrix for each camera
	float *perstransform;
	
	Word16 *transformedCoordsx;
	Word16 *transformedCoordsy;

	Word32 Trans_RVP_width[RVP_MAX_NUM_VIEWS+1];
	Word32 Trans_RVP_height[RVP_MAX_NUM_VIEWS+1];
	Word32 start_x_in_op[RVP_MAX_NUM_VIEWS + 1];

	// LDC table params
	Word16 *LDCLUTRVP[RVP_MAX_NUM_VIEWS + 1];

	// Subsample ratio for LDC
	Byte    LDC_subsamplefactor;

} RVP_ImageTransform_CreationParamsStruct;
/**
 *******************************************************************************
 *
 *   \brief Structure containing the Image Transformation control parameters
 *
 *******************************************************************************
*/
typedef struct{
	Byte dummy; //to be extended later
} RVP_ImageTransform_ControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*******************************************************************************
*
* \brief Implementation of memory query function for Image Transformation algorithm
*
******************************************************************************/
void Alg_ImageTransformMemQuery(RVP_ImageTransform_CreationParamsStruct *rvpImageTransformCreationParams,
	AlgLink_MemRequests *memPtr,
	Byte FirstTimeQuery);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for Image Transformation algo
 *
 * \param  pCreateParams    [IN] Creation parameters for Image Transformation Algorithm
 *
 * \AlgLink_Memrequests handle
 *
 *******************************************************************************
 */
void	*Alg_ImageTransformCreate(RVP_ImageTransform_CreationParamsStruct 	*pCreateParams,
								  AlgLink_MemRequests *memPtr);

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for Image Transformation algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV 
 *        It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned. 
 *        
 * \param  algHandle				[IN] Algorithm object handle
 * \param  pInputVideoFrames[]      [IN] Matrix of input pointers
 *									First Index: Plane Index
 *										Index 0 - Pointer to Y data in case of YUV420SP, 
 *                                      - Single pointer for YUV422IL or RGB
 *										Index 1 - Pointer to UV data in case of YUV420SP
 *									 Second Index: View ID Index
 *									 Index 0 - view ID 0
 *									 Index 1 - view ID 1 and so on.
 * \param  inputPitch[]				[IN] Array of pitch of input image (Address offset 
 *									b.n. two  consecutive lines, interms of bytes)
 *									Indexing similar to array of input pointers
 *									First Index
 * \param pTransformedImageFrames   Transformed image output pointer
 * \param pInputDisparityFrame      Input Disparity Map
 * \param pTransformedDisparityFrame  Transformed disparity map output pointer
 * \param pInputCalibParams         Input calibration parameters for cameras
 * \param  ImageTransform_Mode   [IN] 0:disabled 1:enabled (TBD)
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32	Alg_ImageTransformProcess(void			    				*algHandle,
								  System_VideoFrameCompositeBuffer	*pInputVideoFrames,
								  System_VideoFrameCompositeBuffer	*pTransformedImageFrames,
								  System_VideoFrameBuffer 			*pInputDisparityFrame,
#ifdef PC_VERSION
								  // outDisparity Frame is combined with input images in embedded implementation because, they need to be on the same composite buffer for Sync Link
								  System_VideoFrameBuffer           *pTransformedDisparityFrame,
#endif
								  uWord32             				inputPitch[],
								  float            					*pInputCalibParams,
								  Byte								ImageTransform_Mode);
/**
 *******************************************************************************
 *
 * \brief Implementation of Control for Image Transformation algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  GAlign_Mode			 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32	Alg_ImageTransformControl(void      *algHandle,
                                  RVP_ImageTransform_ControlParams *pControlParams);

Int32 Alg_ImageTransformDelete(void *algHandle, AlgLink_MemRequests *memPtr);
 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
