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
 * \file iAutoRemapAlgo.h
 *
 * \brief Interface file for Alg_AutoRemap algorithm on DSP
 *
 *
 *
 * \version 0.0 (2016) : First version
 *
 *******************************************************************************
 */

#ifndef _IAUTO_REMAP_ALGO_H_
#define _IAUTO_REMAP_ALGO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#ifndef PC_VERSION
	#include <include/link_api/system.h>
    #include <include/link_api/system_common.h>
    #include <src/rtos/utils_common/include/utils_mem.h>
#endif

#include "autoRemapCommonDefs.h"
#include "memRequestAlgo.h"
#include "remap_common.h"

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

	Int16       numCameras;
	Int16       numPairs;
	//Int16       numColorChannels;

	Bool        fishEyeRect;
	Bool        autoRemapForTDA2x;

	Int16       inFrameWidth;
	Int16       inFrameHeight;

	Int16       cropOffsetX;
	Int16       cropOffsetY;


	Int16       lutWidth; 
	Int16       lutHeight;

	Bool        useRansac;
	Int16       numRansacIters;
	Int16       numRansacData;

	FLOAT       roiRegion;

	FLOAT       sfWidth;
	FLOAT       sfHeight; 

	Int16       outFrameWidth;
	Int16       outFrameHeight;

	Int16       remapBlockWidth;
	Int16       remapBlockHeight;


    UInt32      enableMerge;
    UInt32      dstFormat;
    UInt32      srcFormat;
    UInt32      isSrcMapFloat;
    UInt32      interpolationLuma;
    UInt32      interpolationChroma;
    UInt32      mapQshift;
    UInt32      rightShift;
    UInt32      sat_high;
    UInt32      sat_high_set;
    UInt32      sat_low;
    UInt32      sat_low_set;
    UInt32      pairIdx;
		
} AutoRemap_CreationParamsStruct;


/**
 *******************************************************************************
 *
 *   \brief Structure containing the Harris + BRIEF control parameters
 *
 *******************************************************************************
*/

typedef struct
{
	// do-kwon: to add
	Int8 autoRemapMode;
} AutoRemap_ControlParams;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*******************************************************************************
 *
 * \brief Implementation of memory query function for Harris + BRIEF algo
 *
 * \param  ACDetect_CreateParams    [IN] Creation parameters for Harris + BRIEF Algorithm
 *
 * \return  Handle to algorithm
 *
 ******************************************************************************/
void Alg_AutoRemapMemQuery(AutoRemap_CreationParamsStruct *pCreateParams,  
					  		 AlgLink_MemRequests *memPtr,
							 Byte FirstTimeQuery);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for Harris + BRIEF algo
 *
 * \param  pCreateParams    [IN] Creation parameters for Harris + BRIEF Algorithm
 *
 * \return  Handle to algorithm if creation is successful else return NULL
 *
 *******************************************************************************
 */
void *Alg_AutoRemapCreate(AutoRemap_CreationParamsStruct *pCreateParams,
	                        AlgLink_MemRequests *memPtr);


/**
 *******************************************************************************
 *
 * \brief Implementation of Process for Harris + BRIEF algo
 * 
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
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Word32	Alg_AutoRemapProcess(void		*algHandle,
		                     System_VideoFrameCompositeBuffer *pCompositeBuffer,
						 	 Bool      firstFrame,
						 	 UInt8 *   featureInfo,
						 	 UInt8 *   featurePts,
						 	 UInt8 *   outEVELUTs,
						 	 Int32 *   eveLUTSize,
							 UInt8     mode,
							 Bool      tda2x);


Word32 getMemorySizeBlockMap_convertMap(sConvertMap *maps);



/**
 *******************************************************************************
 *
 * \brief Implementation of Control for Harris + BRIEF algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams		 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Word32 Alg_AutoRemapControl(void	 	 	           *algHandle,
                            AutoRemap_ControlParams *pControlParams,
                            Int8                     mode);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for Harris + BRIEF algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Word32 Alg_AutoRemapDelete(void *algHandle,
                             AlgLink_MemRequests *memPtr);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
