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
 * \file iPoseEstimationAlgo.h
 *
 * \brief Interface file for Alg_PoseEstimation algorithm on DSP
 *
 *        This Alg_PoseEstimation algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *
 * \version 0.0
 *
 *******************************************************************************
 */

#ifndef _IPOSEESTIMATION_H_
#define _IPOSEESTIMATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#ifndef PC_VERSION
	#include <include/link_api/system.h>
#endif

#include "svAutoCalibCommonDefs.h"
#include "svPECommonDefs.h"
#include "memRequestAlgo.h"

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



// CREATION PARAMETERS
typedef struct {
	//number of cameras
	Byte        numCameras;
	Word16		defaultFocalLength;

	Word16		SVInCamFrmHeight;
	Word16		SVInCamFrmWidth;

    Void *pLensPrm;

} SV_PEstimate_CreationParamsStruct;



/**
 *******************************************************************************
 *
 *   \brief Structure containing the initial persmat control parameters
 *
 *******************************************************************************
*/

typedef struct
{
	/**< Any parameter if it needs to be altered on the fly */
    Byte     PEstimate_Mode;	 // 0 - disabled
						   	     // 1 - initial pose estimate
							     // 2 - dynamic pose estimate (nonexistent for now)
} SV_PEstimate_ControlParams;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*******************************************************************************
 *
 * \brief Implementation of memory query function for pose estimate algo
 *
 * \param  PEstimate_CreateParams    [IN] Creation parameters for pose estimate Algorithm
 *
 * \return  Handle to algorithm
 *
 ******************************************************************************/
void Alg_PoseEstimateMemQuery(SV_PEstimate_CreationParamsStruct *PEstimate_CreateParams,
							  AlgLink_MemRequests *memPtr,
							  Byte FirstTimeQuery);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for pose estimate algo
 *
 * \param  pCreateParams    [IN] Creation parameters for pose estimate Algorithm
 *
 * \return  Handle to algorithm if creation is successful else return NULL
 *
 *******************************************************************************
 */
void *Alg_PoseEstimateCreate(SV_PEstimate_CreationParamsStruct *pCreateParams,
	                         AlgLink_MemRequests *memPtr);


/**
 *******************************************************************************
 *
 * \brief Implementation of Process for pose estimate algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV
 *        It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned.
 *
 * \param  algHandle     [IN] Algorithm object handle
 * \param  inPtr[]       [IN] Matrix of input pointers
 *                           First Index: Plane Index
 *                              Index 0 - Pointer to Y data in case of YUV420SP,
 *                                      - Single pointer for YUV422IL or RGB
 *                              Index 1 - Pointer to UV data in case of YUV420SP
 *                           Second Index: View ID Index
 *                              Index 0 - view ID 0
 *                              Index 1 - view ID 1 and so on.
 * \param  inPitch[]     [IN] Array of pitch of input image (Address offset
 *                           b.n. two  consecutive lines, interms of bytes)
 *                           Indexing similar to array of input pointers
 *                           First Index
 * \param  GAlign_Mode   [IN] 0:disabled
 *							  1:initial chart based calibration
 *							  2:dynamic calibration
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Word32	Alg_PoseEstimateProcess(void		*algHandle,
								Word32	    *outpersmat,
								Word32      *inCornerPoints,
							    uWord32     PEstimate_Mode);



/**
 *******************************************************************************
 *
 * \brief Implementation of Control for pose estimate algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  IPersmat_Mode		 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_PoseEstimateControl(void	 	 	           *algHandle,
						      SV_PEstimate_ControlParams *PEstimate_Mode);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for pose estimate algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_PoseEstimateDelete(void *algHandle,
                             AlgLink_MemRequests *memPtr);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/* Nothing beyond this point */
