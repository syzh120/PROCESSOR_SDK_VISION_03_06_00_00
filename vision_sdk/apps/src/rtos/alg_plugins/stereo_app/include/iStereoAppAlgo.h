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
 * \file iStereoAppAlgo.h
 *
 * \brief Interface file for Alg_StereoApp algorithm on DSP
 *
 *
 *
 * \version 0.0 (2016) : First version
 *
 *******************************************************************************
 */

#ifndef _ISTEREOAPPALGO_H_
#define _ISTEREOAPPALGO_H_

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

#include "stereoAppCommonDefs.h"
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

    Int16 numPairs;

    Int16 inPCLWidth;
    Int16 inPCLHeight;


	// start idx and end idx of ROI in each dimension
    UInt16 xRoiSIdx;
    UInt16 xRoiEIdx; 
    UInt16 yRoiSIdx;
    UInt16 yRoiEIdx; 
    UInt16 zRoiSIdx;
    UInt16 zRoiEIdx;

    // Safety bubble idx
    UInt16 xSbSIdx; 
    UInt16 xSbEIdx;
    UInt16 ySbSIdx;
    UInt16 ySbEIdx;
    UInt16 zSbSIdx;
    UInt16 zSbEIdx;

    UInt16 uniGridSizeX;
    UInt16 uniGridSizeY;
    UInt16 uniGridSizeZ;

    UInt8  droneMoveSZRange;   // Z range where drone can move - start idx
    UInt8  droneMoveEZRange;   // Z range where dreon can move - end idx

    Int32  wayPoint[3];

    double objectDSigma;
    double objectDSigmaMin;


    // stereo cam params
    float baseline;
    float scale_x;
    float scale_y;
    float dc_x;
    float dc_y;
    float ofst_x;
    float ofst_y;
    float f;
    float calmat[12];

    UInt8 bDataStreaming;
    UInt8 bSenseAvoid;
    UInt8 objectDetectMode;

    UInt8 useDispRoiForPCL;
    Int16 dispRoiStartX;
    Int16 dispRoiStartY;
    Int16 dispRoiWidth;
    Int16 dispRoiHeight;

} StereoApp_CreationParamsStruct;


/**
 *******************************************************************************
 *
 *   \brief Structure containing the stereo app control parameters
 *
 *******************************************************************************
*/

typedef struct
{
	// do-kwon: to add
	Bool reserved;
} StereoApp_ControlParams;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*******************************************************************************
 *
 * \brief Implementation of memory query function for stereo app algorithm
 *
 * \param  StereoApp_CreateParams    [IN] Creation parameters for stereo app Algorithm
 *
 * \return  Handle to algorithm
 *
 ******************************************************************************/
void Alg_StereoAppMemQuery(StereoApp_CreationParamsStruct *pCreateParams,
                            AlgLink_MemRequests *memPtr,
                            Byte FirstTimeQuery);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for stereo app algo
 *
 * \param  pCreateParams    [IN] Creation parameters for stereo app Algorithm
 *
 * \return  Handle to algorithm if creation is successful else return NULL
 *
 *******************************************************************************
 */
void *Alg_StereoAppCreate(StereoApp_CreationParamsStruct *pCreateParams,
	                      AlgLink_MemRequests *memPtr);


/**
 *******************************************************************************
 *
 * \brief Implementation of Process for stereo application algo
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
Word32  Alg_StereoAppProcess(void      *algHandle,
                             //void    *inPtr[MAX_INPUT_STEREO_PAIRS],
                             void      *inPtr,
                             Bool      firstFrame,
                             Int16     * mvOffset,
#if PC_VERSION
                             Int16     *outPcl,
                             UInt8     *outOGmap
#else
                             Int16     *restrict outPcl,
                             UInt8     *restrict outOGmap
#endif
                             );


/**
 *******************************************************************************
 *
 * \brief Implementation of Control for stereo application algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams		 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Word32 Alg_StereoAppControl(void                    *algHandle,
                            StereoApp_ControlParams *pControlParams);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for stereo application algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Word32 Alg_StereoAppDelete(void *algHandle,
                           AlgLink_MemRequests *memPtr);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
