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
*  File: iStitchingAlgo.h
*
=======================================================================*/

#ifndef _ISTITCHINGALGO_H_
#define _ISTITCHINGALGO_H_

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
	#include <include/alglink_api/algorithmLink_stitching.h>
	#include <include/link_api/system.h>
	#include <include/link_api/system_common.h>
	#include <src/rtos/utils_common/include/utils_mem.h>
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
typedef struct
{		
	//Input frame size

	Word16		RVPInCamFrmHeight;
	Word16		RVPInCamFrmWidth;

	//output frame size
	Word16		RVPOutDisplayHeight;
	Word16		RVPOutDisplayWidth;

	//number of cameras
	Byte        numCameras;

	//blentLUT buffer (output buffer)
	Byte*	outBlendBuffer;

	//output buffer
	Byte*	outputBuffer;

	Word16 overlapBounds[8];

	Word32 Trans_RVP_width[RVP_MAX_NUM_VIEWS + 1];
	Word32 Trans_RVP_height[RVP_MAX_NUM_VIEWS + 1];
	Word32 start_x_in_op[RVP_MAX_NUM_VIEWS + 1];

} RVP_Stitching_CreationParamsStruct;
/**
 *******************************************************************************
 *
 *   \brief Structure containing the geometric alignment control parameters
 *
 *******************************************************************************
*/
typedef struct{
	Byte dummy; //to be extended later
} RVP_Stitching_ControlParams;

/*******************************************************************************
*  Functions
*******************************************************************************
*/

/*******************************************************************************
*
* \brief Definition of memory query function for Stitching algorithm
*
******************************************************************************/
void Alg_StitchingMemQuery(RVP_Stitching_CreationParamsStruct *rvpStitchingCreationParams,
	AlgLink_MemRequests *memPtr,
	Byte FirstTimeQuery);


/**
*******************************************************************************
*
* \brief Implementation of create for Stitching algo
*
* \param  pCreateParams    [IN] Creation parameters for Stitching Algorithm
*
* \return  Handle to algorithm if creation is successful else return NULL
*
*******************************************************************************
*/
void *Alg_StitchingCreate(	RVP_Stitching_CreationParamsStruct *pCreateParams,
							AlgLink_MemRequests *memPtr);

/**
*******************************************************************************
*
* \brief Implementation of Process for Stitching algo
*
*        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV
*        It is assumed that the width of the image will
*        be multiple of 4 and buffer pointers are 32-bit aligned.
*
* \param  algHandle     [IN] Algorithm object handle
*        TBD
* \param  Stitching_Mode   [IN] 0:disabled
*
* \return  SYSTEM_LINK_STATUS_SOK on success
*
*******************************************************************************
*/
Int32	Alg_StitchingProcess(
	void                              *algHandle,
	System_VideoFrameCompositeBuffer  *pTransformedImageFrames,
	System_VideoFrameBuffer           *pOutputVideoFrames,
	uWord32                           outputPitch[],
	void                              *pOutputLUT,
	Word16                            *pinseam1,
	Word16                            *pinseam2,
	Byte                              Stitching_Mode);
/**
*******************************************************************************
*
* \brief Implementation of Control for Stitching algo
*
* \param  algHandle             [IN] Algorithm object handle
*
* \return  SYSTEM_LINK_STATUS_SOK on success
*
*******************************************************************************
*/
Int32	Alg_StitchingControl(void			        *algHandle,
								RVP_Stitching_ControlParams *pControlParams);

/**
*******************************************************************************
*
* \brief Implementation of Delete for Stitching algo
*
* \param  algHandle             [IN] Algorithm object handle
*
* \return  SYSTEM_LINK_STATUS_SOK on success
*
*******************************************************************************
*/
Int32 Alg_StitchingDelete(void *algHandle, AlgLink_MemRequests *memPtr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_ISTITCHINGALGO_H_

/* Nothing beyond this point */
