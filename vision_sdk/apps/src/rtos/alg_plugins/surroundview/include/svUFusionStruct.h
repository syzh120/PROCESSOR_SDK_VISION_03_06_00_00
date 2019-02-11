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
 *  File: svUFusionStruct.h
 *  
 =======================================================================*/


#ifndef _SV_UFUSION_STRUCT_INCLUDED_

#define _SV_UFUSION_STRUCT_INCLUDED_

#include "svCommonDefs.h"
#include "memRequestAlgo.h"
#include "iUltrasonicFusionAlgo.h"
#include "globalDefs.h"


/*********************************************************************************
* \brief Detection Arcs
* NOTE: Detection Arcs are currently not supported in GPRX link, but may be used
*       for debugging
********************************************************************************/
typedef struct {
	UInt8 drawDetectionArc; //draw this detection arc
	UInt8 showSensorPosition; //show sensor position on SV output?
	UInt16 numArcPoints;
	Point2D detectionPoints[NUM_ARC_POINTS]; //points along detection arc
	Point2D sensorPosition;
	Point2D strutPoints[2]; //radial line from sensor position along cone (only shown if showSensorPosition>0)
	UInt32 lineColor; //color of lines
	UInt32 lineSize; //size of lines
} SV_UFusion_DetectionArc;

typedef struct {
	UInt32 numUSensors; //number of sensors
	SV_UFusion_DetectionArc arc[MAX_INPUT_USENSORS];
} SV_UFusion_DetectionArcs;



/**
*******************************************************************************
* \brief Device measurement info for ultrasonic capture
*******************************************************************************
*/
typedef struct {

	UInt32 deviceId;
	/**< ID of device for which this measurement is done */

	UInt32 distanceLong;
	/**< Detected object distance in cm */

	UInt32 distanceShort;
	/**< Detected object distance in cm */

} UltrasonicCapture_DeviceMeasurementInfo;

typedef struct
{
	UInt32 numSensors;
	/**< Number of sensors for which data is measured */

	UltrasonicCapture_DeviceMeasurementInfo deviceInfo [MAX_INPUT_USENSORS];
	/**< Measurement information of individual device's */

} UltrasonicCapture_MeasurementInfo;

/* *******************************************************************************
Structures related to Zone Overlay
********************************************************************************/
#define SV_UFUSION_MAX_NUM_OVERLAYZONES (15)
#define SV_UFUSION_NUM_OVERLAYZONES (1)
#define SV_UFUSION_NUM_SEGMENTSPERZONE (3)


/* *******************************************************************************
//Surround View Ultrasonic Fusion private structure: Contains all SV Ultrasonic
fusion input and output parameters.
********************************************************************************/
typedef struct {
	SV_UFusion_CreationParamsStruct cparams;
	USensor sensors[MAX_INPUT_USENSORS];

	//--------------------------------------
	//Inputs
	//--------------------------------------
	UltrasonicCapture_MeasurementInfo *ultrasonicCaptureInPtr; //input from Ultrasonic Capture
	float *pixelsPerCmInPtr; //calibration result: ratio pixel/cm in SV output

	//--------------------------------------
	//Outputs
	//--------------------------------------
	SV_UFusion_DetectionArcs *detectionArcsOutPtr;
	UInt16 *overlaydataOutPtr;
	
	//--------------------------------------
	//Internal
	//--------------------------------------
	UInt8 numUSensorsRT; // real time (RT) number of ultrasonic sensors
	Int32 distInPix[MAX_INPUT_USENSORS]; //ultrasonic sensor reading in terms of SV pixels
	float sinPhi[MAX_INPUT_USENSORS]; //sin of azimuth angles
	float cosPhi[MAX_INPUT_USENSORS]; //cos of azimuth angles
	float sinAlpha[NUM_ARC_POINTS]; //sin of sensor view angle
	float cosAlpha[NUM_ARC_POINTS]; //cos of sensor view angle

	//zone overlay
	UInt8 overlayScale; //scale of overlay image w.r.t. SV image
	UInt32 overlayWidth; //SV image width / overlayScale
	UInt32 overlayHeight; //SV image height / overlayScale
	UInt32 overlaySize; //overlayWidth * overlayHeight
	Int32  distInPixOverlayScale[MAX_INPUT_USENSORS]; //ultrasonic sensor reading in terms of SV pixels scaled by overlayScale
	Point2D sensorPosScale[MAX_INPUT_USENSORS]; //sensor positions in terms of SV pixels scaled by overlayScale

	UInt8 activeSegments[SV_UFUSION_MAX_NUM_OVERLAYZONES+1][SV_UFUSION_NUM_SEGMENTSPERZONE]; //each bit indicates if the segment of a zone is active
	UInt16 overlayColorsARGB4444[SV_UFUSION_NUM_SEGMENTSPERZONE+1]; //overlay color (ARGB4444) for each zone

	//Framework
	AlgLink_MemRequests memRequestStruct; //to keep track of internal memory allocations

} SV_UFusion;


#endif
