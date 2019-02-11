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
 * \file iAutoChartDetectAlgo.h
 *
 * \brief Interface file for Alg_AutoChartDetect algorithm on DSP
 *
 *        This Alg_InitialPersmat algorithm is only for demonstrative purpose.
 *        It is NOT product quality.
 *
 * \version 0.0 (Oct 2013) : [PS, IP] First version
 *
 *******************************************************************************
 */

#ifndef _IAUTOCHARTDETECTALGO_H_
#define _IAUTOCHARTDETECTALGO_H_

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
#include "svACDCommonDefs.h"
#include "memRequestAlgo.h"

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

// CREATION PARAMETERS
typedef struct {

    //Input frame size and output frame size
    Word16              SVInCamFrmHeight;
    Word16              SVInCamFrmWidth;
    Word16              SVOutDisplayHeight;
    Word16              SVOutDisplayWidth;
    //number of color channels
    Byte                numColorChannels;
    //number of cameras
    Byte                numCameras;

    Word16              DMAblockSizeV;
    Word16              DMAblockSizeH;
    Word16              saladbowlFocalLength;
    Word16              defaultFocalLength;
    Word16              downsamp_ratio;

    Word16              SVROIWidth;
    Word16              SVROIHeight;
    Word16              binarizeOffset;
    Word16              borderOffset;
    Word16              smallestCenter;
    Word16              largestCenter;
    Word16              maxWinWidth;
    Word16              maxWinHeight;
    Word16              maxBandLen;
    Word16              minBandLen;
    Word16              minSampleInCluster;
    Word16              firstROITop;
    Word16              firstROIBottom;
    Word16              firstROILeft;
    Word16              firstROIRight;
    Word16              secondROITop;
    Word16              secondROIBottom;
    Word16              secondROILeft;
    Word16              secondROIRight;


    //SV_CarBox_ParamsStruct svCarBoxParams;
    Void *pLensPrm;

} SV_ACDetect_CreationParamsStruct;


/**
 *******************************************************************************
 *
 *   \brief Structure containing the automatic chart detect control parameters
 *
 *******************************************************************************
*/

typedef struct
{
	/**< Any parameter if it needs to be altered on the fly */
    Byte     ACDetect_Mode;	 // 0 - disabled
							 // 1 - initial chart based calibration
							 // 2 - dynamic calibration (nonexistent for now)
} SV_ACDetect_ControlParams;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*******************************************************************************
 *
 * \brief Implementation of memory query function for automatic chart detect algo
 *
 * \param  ACDetect_CreateParams    [IN] Creation parameters for automatic chart detect Algorithm
 *
 * \return  Handle to algorithm
 *
 ******************************************************************************/
void Alg_AutoChartDetectMemQuery(SV_ACDetect_CreationParamsStruct *ACDetect_CreateParams,
								 AlgLink_MemRequests *memPtr,
								 Byte FirstTimeQuery);

 /**
 *******************************************************************************
 *
 * \brief Implementation of create for automatic chart detect algo
 *
 * \param  pCreateParams    [IN] Creation parameters for automatic chart detect Algorithm
 *
 * \return  Handle to algorithm if creation is successful else return NULL
 *
 *******************************************************************************
 */
void *Alg_AutoChartDetectCreate(SV_ACDetect_CreationParamsStruct *pCreateParams,
	                            AlgLink_MemRequests *memPtr);


/**
 *******************************************************************************
 *
 * \brief Implementation of Process for automatic chart detect algo
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
 * \param  ACDetect_Mode   [IN] 0:disabled
 *							  1:initial chart based calibration
 *							  2:dynamic calibration
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Word32	Alg_AutoChartDetectProcess(void		*algHandle,
								   System_VideoFrameCompositeBuffer *pCompositeBuffer,
							       uWord32   inPitch[],
								   Word32   *outCornerPoints,
							       uWord32   ACDetect_Mode);



/**
 *******************************************************************************
 *
 * \brief Implementation of Control for automatic chart detect algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  ACDetect_Mode		 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_AutoChartDectectControl(void	 	 	           *algHandle,
						          SV_ACDetect_ControlParams  *ACDetect_Mode);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for automatic chart detect algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_AutoChartDetectDelete(void *algHandle,
                                AlgLink_MemRequests *memPtr);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
