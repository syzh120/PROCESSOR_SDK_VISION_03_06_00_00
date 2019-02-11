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
 *  \File: iUltrasonicFusionAlgo.h
 *
 *  \brief Interface file for UltrasonicFusion algorithm
 *
 *        This UltrasonicFusion algorithm is only for
 *        demonstrative purpose. 
 *        It is NOT product quality.
 *
 * \version 1.0 (July 1 2014)
 *=======================================================================*/

#ifndef _IULTRASONICFUSIONALGO_H_
#define _IULTRASONICFUSIONALGO_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *  INCLUDE FILES
 ******************************************************************************/
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
	
typedef struct {
	
	Byte numUSensors; 	//number of ultrasonic sensors in use
	Byte numViews; //number of SV views
	Word16		SVOutDisplayHeight;
	Word16		SVOutDisplayWidth;
	Word16 numArcPoints; //number of arc points to draw
	Byte showSensorPosition; //show sensor position in SV?
	Byte drawDetectionArc; //draw detection arcs in SV?
	UInt32 lineColor; //color of lines for arc overlay, 0 -red;
	UInt32 lineSize; //size of lines for arc overlay
	Int32 sensorPositionLineLength;//line distance for sensor position overlay
} SV_UFusion_CreationParamsStruct; //Ultrasonic fusion creation parameters

/*******************************************************************************
 *  Functions
 * 
 *  Note: put all functions that should be exposed to FW here
 ******************************************************************************/
typedef struct
{
	Byte dummy;
} SV_UFusion_ControlParams;
/*******************************************************************************
 *
 * \brief Implementation of memory query function for ultrasonic fusion algo
 *
 * \param  pCreateParams    [IN] Creation parameters 
 * \param  memPtr           [IN] dummy pointer to memory
 * \param  firstTimeFlag    [IN] This is temporary input, to remove from ALL three MemQuery functions
 *                               1 - first time call, return memory size for algHandle (algo private structure)
 *                               0 - 2nd time call, return memory size required for varibles inside algHandle
 *
 * \return nothing, but memPtr will be updated with proper memory needed
 *
 ******************************************************************************/
void Alg_UltrasonicFusionMemQuery(SV_UFusion_CreationParamsStruct *pCreateParams,
                                      AlgLink_MemRequests *memPtr,
                                      Byte firstTimeFlag);


 /*******************************************************************************
 *
 * \brief Implementation of create for ultrasonic fusion algo
 *
 * \param  pCreateParams    [IN] Creation parameters for ultrasonic fusion Algorithm
 * \param  memPtr           [IN] valid memory pointer to algorithm
 *
 * \return  Handle to algorithm if creation successful; if not, return NULL
 *
 ******************************************************************************/
void * Alg_UltrasonicFusionCreate(
    SV_UFusion_CreationParamsStruct *pCreateParams,
    AlgLink_MemRequests *memPtr);

/*******************************************************************************
*
* \brief Implementation of Process for ultrasonic fusion algo
*
*
* \param  algHandle      [IN] Algorithm object handle
* \param  inUPtr         [IN] Pointer to ultrasonic sensor input
* \param  inUCaliLUTPtr  [IN] Pointer to ultrasonic calibration output LUT
* \param  outUPtr        [OUT] Pointer to ultrasonic output for cone drawing using lines
* \param  outURegionsPtr [OUT] Pointer to regions map output (16bit image) //MM141008
* \return  SYSTEM_LINK_STATUS_OK on success
*
*******************************************************************************/
Int32 Alg_UltrasonicFusionProcess(void  *algHandle,
								  void  *ultrasonicCaptureInPtr,
								  float	*pixelsPerCmInPtr,
								  void	*detectionArcsOutPtr,
								  void  *overlaydataOutPtr
								 );
/**
 *******************************************************************************
 *
 * \brief Implementation of Control for geometric alignment algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 * \param  GAlign_Mode			 [IN] Pointer to Control Params
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_UltrasonicFusionControl(void                       *pAlgHandle,
                           SV_UFusion_ControlParams *pControlParams);

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete for ultrasonic fusion algo
 *
 * \param  algHandle             [IN] Algorithm object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 Alg_UltrasonicFusionDelete(void                *algHandle,
                                    AlgLink_MemRequests *memPtr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


