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
 *  File: svACDetectStruct.h
 *
 =======================================================================*/


#ifndef _SV_ACDETECT_STRUCT_INCLUDED_
#define _SV_ACDETECT_STRUCT_INCLUDED_

#include "../include/globalDefs.h"
#include "../include/svAutoCalibCommonDefs.h"
#include "../include/svACDCommonDefs.h"
#include "../include/memRequestAlgo.h"
#include "../../commonutils/lens_distortion_correction/lens_distortion_correction.h"

typedef struct {
    Byte        enableSV_ACDetect;
    Byte        thresholdMode;
    Byte        windowMode;
    Byte        Ransac;
    Byte        SingleChartPose;

    Word16      SVInCamFrmHeight;
    Word16      SVInCamFrmWidth;
    Word16      SVOutDisplayHeight;
    Word16      SVOutDisplayWidth;

    uWord32     SVInPitch[2];

    SV_ACDetect_FPBoundaryPos *svFPBoundaryPosStruct;

    Byte        numColorChannels;           // number of color channels
    Byte        numCameras;                 // number of cameras

    // pointers to input frames
    Byte        *currFrm[MAX_INPUT_CAMERAS];    // current input frames
    Byte        * bwLumaFrame;

    Word32      *persmat;                   // perspective matrix parameters
    //uWord16     *sinatanLUT;                // LUT that holds sin(atan(x)) values
    //uWord16     *tanasinLUT;                // LUT that holds tan(asin(x)) values
    /*
    uWord16	    *InCamFrmDistortionCen;     // frame distortion centers for cameras
    */

    Word16	    *focalLength;               // focal length for fish-eye lens model
    Word16      defaultFocalLength;             // default focal length

    //Word16      DMAblockSizeV;              // vertical DMA block size
    //Word16      DMAblockSizeH;              // horizontal DMA block size

    //Word32      temp_locver; // to hold vertical pixel coordinate temporarily
    //Word32      temp_lochor; // to hold horizontal pixel coordinate temporarily

    Word16      *candFPId;
    Word16      *candFPx;
    Word16      *candFPy;

    Word16      *candidCenter;

    double      *outCenter;    // MAX_FP_ALL * 2 [y/x]
    Word16      *intOutCenter;
    Word16      *outCenterNum; // MAX_FP_ALL

    double      *boundX;
    double      *boundY;
    double      *fcBoundX;
    double      *fcBoundY;
    double      *tempBoundX;   // scratch buffer
    double      *tempBoundY;
    uWord32     *IntegralRows;
    uWord32     *IntegralImg;

    double     *line1PtsX;    // scratch buffer
    double      *line1PtsY;
    double      *line2PtsX;
    double      *line2PtsY;

    Word32      *finalCorners[MAX_INPUT_CAMERAS][FP_TO_DETECT];   // FP_TO_DETECT * 4 [FPs] * 2 [y/x]
    Word32      *candidCorners[MAX_FP_ALL];      // MAX_FP_ALL * 4 * 2
    double      *matchScore;   // MAX_FP_ALL

    double      *tempCorner;         // 4 [FPs] * 2 [y/x]
    double      *tempCorner1;        // 4 [FPs] * 2 [y/x]
    double      *tempCorner2;        // 4 [FPs] * 2 [y/x]

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

    //LDC
    LensDistortionCorrection *ldc;

    AlgLink_MemRequests memRequestStruct; //memory, added by BZ, 11/14

    ldc_lensParameters *pLensPrm;

} svACDetectStruct;

#endif
