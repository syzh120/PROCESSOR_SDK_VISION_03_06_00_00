/*=======================================================================
 *
 *            Texas Instruments Internal Reference Software
 *
 *                           EP Systems Lab
 *                     Embedded Signal Processing
 *                             Imaging R&D
 *
 *         Copyright (c) 2015 Texas Instruments, Incorporated.
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
 *  File: svAutoDetectChart.h
 *
 =======================================================================*/
#ifndef _SV_AUTO_DETECT_CHART_H_
#define _SV_AUTO_DETECT_CHART_H_

#include "../include/svACDetectStruct.h"


// functions in svAutoDetectChart.c
Word32 svAutoDetectChart(svACDetectStruct* sv, Byte acDetectMode, void *inPtr[][NUM_MAX_VIEWS], uWord32* inPitch, Word32 *outCornerPoints, UInt8* pointNum, UInt8 *bLeftChart);

static Word16 svGetFinderPatterns(svACDetectStruct* sv, uWord32* inPitch, Word16 view_number);
static void svBinarizeImage(svACDetectStruct* sv, uWord32* inPitch, Word16 view_number);
static Word32 svSearchFinderPatterns(svACDetectStruct* sv, Word16 view_number);
static Byte svCheckPatternProfileLowDia(svACDetectStruct* sv, Byte* bwLumaFrame, Word16 posy, Word16 posx, Word16 height, Word16 width, SV_ACDetect_FPBoundaryPos* svFPBoundaryPosA, SV_ACDetect_FPBoundaryPos* svFPBoundaryPosB, double slope, Byte bScreen);
static Byte svCheckPatternProfileHiDia(svACDetectStruct* sv, Byte* bwLumaFrame, Word16 posy, Word16 posx, Word16 height, Word16 width, SV_ACDetect_FPBoundaryPos* svFPBoundaryPosA, SV_ACDetect_FPBoundaryPos* svFPBoundaryPosB, double slope, Byte bScreen);
static Byte svCheckAllDirections(svACDetectStruct* sv, Word16 view_number);
static Word16 svFindFPCentroids(svACDetectStruct* sv, Word16 view_number, Word16 numPts);
static Word16 svSearchCluster(svACDetectStruct* sv, Word16 y, Word16 x, Word16 numCenters);

static Word16 svRemoveNoiseFP(svACDetectStruct* sv, Word16 view_number, Word16 numFPs);
static void svInterpolateMissingBoundary(double* inY, double* inX, double* tempY, double* tempX, Word16 numPts);
static void svGetInitialLines(svACDetectStruct* sv, double* inY, double* inX, double* fcY, double* fcX, Word16 numPts, Word16* lineStart, Word16* lineEnd);
static double svRefineFPCorner(svACDetectStruct* sv, double* inY, double* inX, double *fcY, double* fcX, double* corner, Word16 numPts, Word16* lineStart, Word16* lineEnd, LensDistortionCorrection *ldc, Byte bFisheye);
static double svUpdateBoundaryPoints(svACDetectStruct* sv, double* inY, double* inX, Word16 numPts, Word16* startPos, Word16* endPos, Byte* NaNSlope, double* slope, double* icpt, double* XValue, Byte lineIdx1st, Byte lineIdx2nd, Byte bHorDist1, Byte bHorDist2);
static Byte svCheckFPCondition(svACDetectStruct* sv, double* inputCorner);
static double svGetLineFitError(double* linePtsY, double* linePtsX, Byte* NaNSlope, double* XValue, double* slope, double* icpt, Word16 numPtLine, Byte bHorDist);
static double svGetLine(svACDetectStruct* sv, double* inY, double* inX, Word16 numPts, Word16* startPos, Word16* endPos, Byte* NaNSlope, double* slope, double* icpt, double* XValue, Byte lineIdx, Byte bHorDist);
static void svGetCornerFromLine(double* corner, Byte* NaNSlope, double* slope, double*icpt, double* XValue, Byte lineIdx1st, Byte lineIdx2nd, Byte cornerIdx);

static void svGetLineFrom2Pts(svACDetectStruct* sv, Byte* NaNSlope, double* slope, double* icpt, double* xIcpt, Byte lineIdx);
static double svRansacLineFit(svACDetectStruct* sv, double* inY, double* inX, double* fcY, double* fcX, double* corner, Word16 numPts, LensDistortionCorrection *ldc);
static double Calculate1DErrorForPoint(double ptx, double pty, Byte NaNslope, double slope, double icpt, double xIcpt, Byte bHorDist);
static double svAssociatePointsToLine(svACDetectStruct* sv, Byte* NaNslope, double* slope, double* icpt, double* xIcpt, Word16 totalPoints, Byte errTh, UInt8 candLineIdx[128][4], UInt8* LineIdxArr, UInt8* numOutlier);
static double GetLineAfterRansac(svACDetectStruct* sv, UInt8* optLineIdxArr, Byte* NaNSlope, double* slope, double* icpt, double* XValue, Byte totalPoints, Byte lineIdx);

static UInt32 myrandPE(void);
static void svRandomPerm(UInt32 max_index, UInt32 *array_in, UInt32 count, UInt32 *array_out);
#endif
