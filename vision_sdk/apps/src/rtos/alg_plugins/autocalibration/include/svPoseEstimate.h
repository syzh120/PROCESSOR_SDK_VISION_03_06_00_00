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
 *  File: svPoseEstimate.h
 *
 =======================================================================*/
#ifndef _SV_POSE_ESTIMATE_H_
#define _SV_POSE_ESTIMATE_H_

#include "svPEstimateStruct.h"


#include "../../commonutils/linAlg/linAlgBasicTypes.h"

static void initChartPoints(svPEstimateStruct *sv, Byte* inChartPos);

static void copyCornerPoints(svPEstimateStruct *sv, Word32 *inCornerPoints);

static void constructCalmat(svPEstimateStruct *sv);


// Related with Camera intrinsics
static void initializePECameraIntrinsics(CameraIntrinsicParams* cip);

static void svSetFrameCentersPEstimate(svPEstimateStruct* sv);

// functions in svPoseEstimate.c
Word32 svPoseEstimate(svPEstimateStruct *sv, Byte pEstimateMode, Word32 *inCornerPoints, Byte* inChartPos, Word32* ot, UInt8* pointNum, UInt8* bLeftChart);

Word32 svPoseEstimate_2D(svPEstimateStruct *sv, Byte pEstimateMode, Word32 *inCornerPoints, Byte* inChartPos, Word32* outpersmat);

static void svExtrinsicPoseEstimation(svPEstimateStruct *sv, Int16 vIdx, Point2D_f *chartPoints, Point2D_f *cornerPoints, Point2D_f *normCornerPoints, UInt16 focalLength, UInt16 distCentX, UInt16 distCentY);

static void estimateRtBetweenChartAndCamera(svPEstimateStruct *sv, Int16 vIdx, Point2D_f *pointsCharts, Point2D_f *pointsCamera, Point2D_f* points1norm, Point2D_f* points2norm, Matrix3D_f* T1, Matrix3D_f* T1Inv, Matrix3D_f* T2, Matrix3D_f* T2Inv);

static void estimateRtBetweenChartAndCamera_ransac(svPEstimateStruct *sv, Int16 vIdx, Point2D_f *pointsCharts, Point2D_f *pointsCamera, Point2D_f* points1norm, Point2D_f* points2norm, Matrix3D_f* T1, Matrix3D_f* T1Inv, Matrix3D_f* T2, Matrix3D_f* T2Inv);

static Flouble estimateH_2d_DLT_SRV(svPEstimateStruct *sv, Point2D_f *pointsCharts, Point2D_f *pointsCamera, Point2D_f* points1norm, Point2D_f* points2norm, Matrix3D_f* T1, Matrix3D_f* T1Inv, Matrix3D_f* T2, Matrix3D_f* T2Inv, Matrix3D_f* H, Int16 numPoints, Int16 a_nrows, Int16 a_ncols);

static void estimateRt_LM(svPEstimateStruct *sv, Point2D_f *pointsCharts, Point2D_f *pointsCamera, Flouble* R, Flouble* t, Matrix3D_f* P, Matrix3D_f* Pnew, Int16 numPoints);

static void normalizeData_2d(Point2D_f *points, Point2D_f* pointsnorm, Matrix3D_f* T, Matrix3D_f* TInv, Int16 numPoints);

static void scale2UnitMatrix(Matrix3D_f* M);

static void extractRandT(svPEstimateStruct *sv, Matrix3D_f M, Flouble* R, Flouble* t);

static void solveDelta(Int16 Nrows, Int16 Ncols, Flouble* A, Flouble* Q, Flouble* R, Flouble *x, Flouble *b, Flouble* u);

static void getPtArrFromIndex(Point2D_f* inPoints1, Point2D_f* inPoints2, Point2D_f* outPoints1, Point2D_f* outPoints2, UInt32 *idxArray, Int16 numPoints);

static Flouble computePEGeometricError(Point2D_f points1, Point2D_f points2, Matrix3D_f M);


// Levenberg-Marquardt
static void getX(svPEstimateStruct *sv, Point2D_f* points, Flouble* xvec, Flouble* lambda, Int16 numPoints);

static void computeJ(svPEstimateStruct *sv, Point2D_f* points, Matrix3D_f* P, Flouble* lambda, Flouble* J, Flouble* JT, Int16 Nrows, Int16 Ncols, Int16 numPoints);

static Flouble computeCost(svPEstimateStruct *sv, Point2D_f* points, Matrix3D_f* P, Flouble* xvec, Flouble* fvec, Flouble* lambda, Int16 numPoints);

static void computeF(svPEstimateStruct *sv, Point2D_f* points, Matrix3D_f* P, Flouble* fvec, Flouble* lambda, Int16 numPoints);



// matrix utils
static Flouble vecNorm(Flouble * vector, Int16 length, Byte bSqrt);

static Flouble vecSum(Flouble * vector, Int16 length);

static void crossProduct(Flouble *v1, Flouble *v2, Flouble *vout);

static void transposeMatrix(Int16 Nrows, Int16 Ncols, Flouble *inM, Flouble *outM);

static void multiplyMatrix(Int16 Nrows, Int16 Ncols, Int16 Ncols2, Flouble *inM1, Flouble *inM2, Flouble *outM);

static void addMatrix(Int16 Nrows, Int16 Ncols, Flouble *inM1, Flouble *inM2, Flouble *outM);

static void subtractMatrix(Int16 Nrows, Int16 Ncols, Flouble *inM1, Flouble *inM2, Flouble *outM);

static void initMatrix(Int16 Nrows, Int16 Ncols, Flouble* outM, Byte identity);

static void muliplyScalerMatrix(Int16 Nrows, Int16 Ncols, Flouble scaler, Flouble* inM, Flouble* outM);

static void getDiagonal(Int16 Nrows, Int16 Ncols, Flouble* inM, Flouble* diag);

static void printMatrix(Int16 Nrows, Int16 Ncols, Flouble* inM);

static void convert1DMatTo2DMat(Int16 Nrows, Int16 Ncols, Flouble* mat1D, Flouble** mat2D);

static void convert2DMatTo1DMat(Int16 Nrows, Int16 Ncols, Flouble** mat2D, Flouble* mat1D);


// utils
static void randomPerm(Int32 max_index, UInt32 *array_in, Int32 count, UInt32 *array_out);


/*****************************************/
/* For 2D perpective matrix              */
/*****************************************/
static void svGetReferencePoints2D(svPEstimateStruct *sv, Byte* inChartPos);

static void copyCornerPoints2D(svPEstimateStruct *sv, Word32 * inCornerPoints);

static void svSetFrameCentersCarbox(svPEstimateStruct *sv);

static void svCalculateInitialPersmat(svPEstimateStruct* sv);

static double svFindPersTransDir_float(svPEstimateStruct* sv, double* perscoor1_float, double* perscoor2_float, double* persin_float, uWord16 OutDisplayFrmCenVer, uWord16 OutDisplayFrmCenHor);

static void svFisheyeTransformNL(svPEstimateStruct* sv, Word16 region, Word16 idx);



#endif

