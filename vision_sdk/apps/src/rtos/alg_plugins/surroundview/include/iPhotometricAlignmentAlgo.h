/*=======================================================================
 *
 *            Texas Instruments Internal Reference Software
 *
 *                           EP Systems Lab
 *                     Embedded Signal Processing
 *                             Imaging R&D
 *         
 *         Copyright (c) 2013 Texas Instruments, Incorporated.
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
 *  \File: iPhotometricAlignmentAlgo.h
 *
 *  \brief Interface file for Alg_Photometric Alignment algorithm
 *
 *        This Alg_Photometric Alignment algorithm is only for 
 *        demonstrative purpose. 
 *        It is NOT product quality.
 *
 * \version 1.0 (March 28 2014)
 *=======================================================================*/

#ifndef _IPHOTOMETRICALIGNMENTALGO_H_
#define _IPHOTOMETRICALIGNMENTALGO_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *  INCLUDE FILES
 ******************************************************************************/
//#define PC_VERSION
#ifndef PC_VERSION
	#include <include/link_api/system.h>
#endif

#include "svCommonDefs.h"
#include "memRequestAlgo.h"

/*******************************************************************************
 *  Defines
 ******************************************************************************/

/*******************************************************************************
 *  Enum's
 ******************************************************************************/

/*******************************************************************************
 *  Data structures
 * 
 ******************************************************************************/
//CREATION PARAMETERS

// algorithm tuning parameters
typedef struct{
	Byte		nUpGn; 
	Byte		nUpTv; 
	Byte		nAnPts;	
	Word32		inTh;
	Word32		beta;
}SV_PAlign_TuningParams;	
	
typedef struct {
	
	//Input frame size and output frame size
	Word16		SVInCamFrmHeight; 
	Word16		SVInCamFrmWidth;  
	Word16		SVOutDisplayHeight;
	Word16		SVOutDisplayWidth; 
	
	Byte		numColorChannels; //number of color channels
	Byte        numCameras; 	//number of cameras
	
	//Parameters for the car box in the center of the output frame
	SV_CarBox_ParamsStruct svCarBoxParams;  

	SV_PAlign_TuningParams PAlignTuningParams; //Structure for PAlign tuning parameters
	
	//size of block (vertical, horizontal) for PAlign statistics collection 
	Word16      blockSizeV;  //This should be set to DMA size for now, during creation, Buyue
	Word16      blockSizeH;  //This should be set to DMA size for now, during creation, Buyue

} SV_PAlign_CreationParamsStruct; //PAlign creation parameters

//OUTPUT PARAMETERS DURING CREATION
typedef struct {
	Byte		*PAlignLUT_INIT; // pointer to photometric LUT initialial value

} SV_PAlign_CreationOutputStruct; //PAlign creation output structure


/*******************************************************************************
 *
 *   \brief Structure containing the photometric alignment control parameters
 *
 ******************************************************************************/
typedef struct
{
   /**< Any parameter if it needs to be altered on the fly */
   Byte     PAlign_Mode; //0 - disable (input = output)
                         //1 - regular
} SV_PAlign_ControlParams;


/*******************************************************************************
 *  Functions
 * 
 *  Note: put all functions that should be exposed to FW here
 ******************************************************************************/

/*******************************************************************************
 *
 * \brief Implementation of memory query function for photometric alignment algo
 *
 * \param  pCreateParams    [IN] Creation parameters for photometric alignment Algorithm
 * \param  memPtr           [IN] dummy pointer to memory
 * \param  firstTimeFlag    [IN] This is temporary input, to remove from ALL three MemQuery functions
 *                               1 - first time call, return memory size for algHandle (algo private structure)
 *                               0 - 2nd time call, return memory size required for varibles inside algHandle
 *
 * \return nothing, but memPtr will be updated with proper memory needed
 *
 ******************************************************************************/
void Alg_PhotometricAlignmentMemQuery(SV_PAlign_CreationParamsStruct *pCreateParams,  
                                      AlgLink_MemRequests *memPtr,
                                      Byte firstTimeFlag);


 /*******************************************************************************
 *
 * \brief Implementation of create for photometric alignment algo
 *
 * \param  pCreateParams    [IN] Creation parameters for photometric alignment Algorithm
 * \param  memPtr           [IN] valid memory pointer to algorithm
 *
 * \return  Handle to algorithm if creation successful; if not, return NULL
 *
 ******************************************************************************/
void * Alg_PhotometricAlignmentCreate(
    SV_PAlign_CreationParamsStruct *pCreateParams, 
    AlgLink_MemRequests *memPtr);

/*******************************************************************************
 *
 * \brief Implementation of Process for photometric alignment algo
 *
 *        Supported formats are SYSTEM_DF_YUV422I_YUYV, SYSTEM_DF_YUV420SP_UV 
 *        It is assumed that the width of the image will
 *        be multiple of 4 and buffer pointers are 32-bit aligned. 
 *        
 * \param  algHandle    [IN] Algorithm object handle
 * \param  inStatLUTPtr [IN] Pointer for Photometric statistics input 
 * \param  outPAlignLUTPtr  [IN] Pointer for Photometric Correction params output
 * \param  dataFormat   [IN] Different image data formats. Refer 
 *                           System_VideoDataFormat. Assumption that input
 *                           image and output image will have same data format.
 * \Param  PAlign_Mode  [IN] 0: disable PAlign, input = output; 1: enable PAlign
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************/
Int32 Alg_PhotometricAlignmentProcess(void			    *algHandle,
                                      void            *inStatLUTPtr,
                                      //void            *outPAlignLUTPtr, 
									  //Word32          *outPAlignGAIN_RGB,
									  void				*outPAlignLUTPtr,
                                      Word32             dataFormat,
									  Byte               PAlign_Mode
									 );

/*******************************************************************************
 *
 * \brief Implementation of Control for photometric alignment algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  pControlParams        [IN] Pointer to Control Params
 * \Param  PAlign_Mode  [IN] 0: disable PAlign, input = output; 1: enable PAlign
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************/
Int32 Alg_PhotometricAlignmentControl(void			            *algHandle,
									 SV_PAlign_ControlParams    *PAlign_Mode);


/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for photometric alignment algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_PhotometricAlignmentDelete(void                *algHandle, 
                                    AlgLink_MemRequests *memPtr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* Nothing beyond this point */
