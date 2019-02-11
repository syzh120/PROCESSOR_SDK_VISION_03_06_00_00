/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file iAdaptiveBowlAlgo.h
 *
 * \brief Interface file for Adaptive Bowl algorithm on DSP
 *
 *        This Adaptive Bowl algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *
 * \version 0.0 (Oct 2013) : [PS, IP] First version
 *
 *******************************************************************************
 */

#ifndef _IADAPTIVEBOWLALGO_H_
#define _IADAPTIVEBOWLALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
//#define PC_VERSION
#ifndef PC_VERSION
	#include <include/link_api/system.h>
#endif

#include "svCommonDefs.h"
#include "memRequestAlgo.h"
#include "../include/svUFusionStruct.h"
#include "../include/svAdaptiveBowlStruct.h"

#ifndef PC_VERSION
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

typedef struct {
    char     inputChar;
    /**< Input character to update the render configuration */
} AdaptiveBowl_UpdateRenderCfgPrms;

// algorithm parameters
typedef struct {
	Word16		max_num_features;			// Maximum number of features to be kept for each overlapping region for every view
	Word16		min_match_score;			// Minimum score for feature a match to be accepted
	Word16		max_BRIEF_score;			// Minimum BRIEF score for a match to be accepted
	Word16		min_distBW_feats;			// Minimum eucledian distance between accepted features
    Word16		downsamp_ratio;				// Overlapping region downsample ratio, should be either 1 or 2

}SV_AdaptiveBowl_TuningParams;

//CREATION PARAMETERS
typedef struct {
	//Input frame size and output frame size
	Word16		SVInCamFrmHeight;
	Word16		SVInCamFrmWidth;
	Word16		SVOutDisplayHeight;
	Word16		SVOutDisplayWidth;
	Word16		ldcOutFrmWidth;
	Word16		ldcOutFrmHeight;

	//number of color channels
	Byte		numColorChannels;
	//number of cameras
	Byte      numCameras;
	//double BRIEF_scale;
	//Word16		max_num_features;
	Word16		DMAblockSizeV;
	Word16		DMAblockSizeH;
	Word16		saladbowlFocalLength;
	Word16		defaultFocalLength;
	Word16		downsamp_ratio; // Overlapping region downsample ratio, should be either 1 or 2

	SV_CarBox_ParamsStruct svCarBoxParams;
	SV_AdaptiveBowl_TuningParams GAlignTuningParams;


	Byte        outputMode; // 2D or 3D SRV
	// Subsample ratio for 3D SRV
	Byte         subsampleratio;

	//Pixel per Cm computation
	Byte	enablePixelsPerCm;
	Byte	useDefaultPixelsPerCm;

	Byte    ldcDownScaleFactor;

	Void *pLensPrm;
	Void *pLensPrm2D;

	/* XY offsets for adaptive bowl */
	Word32 offsetXleft;
	Word32 offsetXright;
	Word32 offsetYfront;
	Word32 offsetYback;

} SV_AdaptiveBowl_CreationParamsStruct;
/**
 *******************************************************************************
 *
 *   \brief Structure containing the adaptive bowl control parameters
 *
 *******************************************************************************
*/
typedef struct
{
	/**< Any parameter if it needs to be altered on the fly */
    Byte     GAlign_Mode;	// 0 - disabled
							// 1 - initial chart based calibration
							// 2 - dynamic calibration (nonexistent for now)
} SV_AdaptiveBowl_ControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

void checkForNewDepthValues(void *algHandle, UltrasonicCapture_MeasurementInfo *ultrasonicInfo);

/*******************************************************************************
 *
 * \brief Implementation of memory query function for adaptive bowl algo
 *
 * \param  AdaptiveBowl_CreateParams    [IN] Creation parameters for adaptive bowl Algorithm
 *
 * \return  Handle to algorithm
 *
 ******************************************************************************/
void Alg_AdaptiveBowlMemQuery(SV_AdaptiveBowl_CreationParamsStruct *GAlign_CreateParams,
									  AlgLink_MemRequests *memPtr,
									  Byte FirstTimeQuery);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for adaptive bowl algo
 *
 * \param  pCreateParams    [IN] Creation parameters for adaptive bowl Algorithm
 *
 * \return  Handle to algorithm if creation is successful else return NULL
 *
 *******************************************************************************
 */
void *Alg_AdaptiveBowlCreate(SV_AdaptiveBowl_CreationParamsStruct *pCreateParams,
                                    AlgLink_MemRequests *memPtr);

/**
 *******************************************************************************
 *
 * \brief Implementation of Process for adaptive bowl algo
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
 * \param  outGALUTPtr   [IN] Pointer for GA LUT table
 * \param  outGALUT3DPtr   [IN] Pointer for GA LUT 3D table
 * \param  GAlign_Mode   [IN] 0:disabled
 *							  1:initial chart based calibration
 *							  2:dynamic calibration
 * \param  inCalmat      [IN] Pointer for calibration matrix
 * \param  medianFrontDepthValue   [IN] front depth value
 * \param  medianRightDepthValue   [IN] right depth value
 * \param  medianBackDepthValue    [IN] back depth value
 * \param  medianLeftDepthValue    [IN] left depth value
 * \param  offsetXleft   [IN] Left offset value
 * \param  offsetXright  [IN] Right offset value
 * \param  offsetYfront  [IN] Front offset value
 * \param  offsetXback   [IN] Back offset value
 * \param  isFirstTime   [IN] Boolean indicating whether it is the first time through the algo
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_AdaptiveBowlProcess(void        *algHandle,
        void               *ultrasonicCaptureInPtr,
        uWord32            inPitch[],
        uWord32            *outGALUT3DPtr,
        uWord32            GAlign_Mode,
        Word32             *inCalmat,
        Word32             medianFrontDepthValue,
        Word32             medianRightDepthValue,
        Word32             medianBackDepthValue,
        Word32             medianLeftDepthValue,
        Word32             offsetXleft,
        Word32             offsetXright,
        Word32             offsetYfront,
        Word32             offsetYback,
        Bool               isFirstTime,
        UInt8              useWideBowl);

/**
 *******************************************************************************
 *
 * \brief Implementation of Control for adaptive bowl algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  GAlign_Mode			 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_AdaptiveBowlControl(void *algHandle,
                              SV_AdaptiveBowl_ControlParams *GAlign_Mode);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for adaptive bowl algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_AdaptiveBowlDelete(void *algHandle,
                                   AlgLink_MemRequests *memPtr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
