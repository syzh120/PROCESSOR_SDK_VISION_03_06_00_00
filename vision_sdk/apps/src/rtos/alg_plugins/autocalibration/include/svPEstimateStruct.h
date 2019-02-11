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
 *  File: svPoseEstStruct.h
 *
 =======================================================================*/


#ifndef _SV_POSEEST_STRUCT_INCLUDED_
#define _SV_POSEEST_STRUCT_INCLUDED_

#include "../include/globalDefs.h"
#include "../include/svAutoCalibCommonDefs.h"
#include "../include/svPECommonDefs.h"
#include "../include/memRequestAlgo.h"
#include "../../commonutils/lens_distortion_correction/lens_distortion_correction.h"

typedef struct {
    Byte        enableSV_PEstimate;
    Byte        numCameras;                 // number of cameras
    Byte        Ransac;
    Byte        SingleChartPose;

    Word16      defaultFocalLength;         // default focal length

    Word16      SVInCamFrmHeight;
    Word16      SVInCamFrmWidth;


    //uWord16     *sinatanLUT;              // LUT that holds sin(atan(x)) values
    //uWord16     *tanasinLUT;              // LUT that holds tan(asin(x)) values

    CameraIntrinsicParams *cip[MAX_INPUT_CAMERAS];

    Point2D_f *chartPoints[MAX_INPUT_CAMERAS];
    Point2D_f *cornerPoints[MAX_INPUT_CAMERAS];

    UInt8     detectedPointNum[MAX_INPUT_CAMERAS];
    UInt8     bLeftChartOnly[MAX_INPUT_CAMERAS];

    // camera pose
    Matrix3D_f *H_cg;
    Matrix3D_f *R_cg;
    Matrix3D_f *R_gc;
    Point3D_f  *t_cg;
    Point3D_f  *t_gc;

    Matrix3D_f  Rt;  // temporary matrix


    Point2D_f *baseChartPoints[4];
    Point2D_f chartShift_tl;
    Point2D_f chartShift_tr;
    Point2D_f chartShift_bl;
    Point2D_f chartShift_br;
    Point2D_f *normCornerPoint;

    Point2D_f *points1norm;
    Point2D_f *points2norm;

    // DLT
    Matrix3D_f T1, T1Inv, T2, T2Inv, H, Hnorm, Htemp;

    // Levenberg-Marquardt
    Matrix3D_f P, Pnew;
    Flouble* xvec, *fvec, *bvec, *tempvec, * deltavec;

    Flouble* Jacob;
    Flouble* JacobT;
    Flouble* gammaIdentity;

    // SVD
    Flouble *A;
    Flouble *U;
    Flouble *V;
    Flouble *U1;
    Flouble *Diag;
    Flouble *superDiag;


    // QRD
    Flouble *AInv;
    Flouble *Q;
    Flouble *R;
    Flouble *yvec; // temporary vector


    // in esatimateH_2d_DLT()
    Flouble *h;

    // in estimateRtBetweenChartAndCamera()
    Flouble * R_DLT;
    Flouble * t_DLT;


    /*****************************************/
    /* For 2D perpective matrix              */
    /*****************************************/
    Word16      SVOutDisplayHeight;
    Word16      SVOutDisplayWidth;

    uWord16 *InCamFrmDistortionCen; // frame distortion centers for cameras
    uWord16 *OutDisplayFrmCen;      // output frame center

    carBoxParamsStruct svCarBoxParams; // parameters for the black car box region in the middle of output frame

    Word16 *xx, *yy, *x0, *y0, *x1, *y1, *x2, *y2, *x3, *y3;

    Word32 *xx0, *yy0, *ofxx0, *ofyy0;
    Word32 *xx1, *yy1, *ofxx1, *ofyy1;
    Word32 *xx2, *yy2, *ofxx2, *ofyy2;
    Word32 *xx3, *yy3, *ofxx3, *ofyy3;

    double *pers_mat0;
    double *pers_mat1;
    double *pers_mat2;
    double *pers_mat3;

    double *perscoor0_3_float;
    double *perscoor1_0_float;
    double *perscoor2_1_float;
    double *perscoor3_2_float;

    double *outperscoor0_3_float;
    double *outperscoor1_0_float;
    double *outperscoor2_1_float;
    double *outperscoor3_2_float;


    double *A_matrix; // A*x = b memory holders
    double *B_vector;
    double *q_matrix;
    double *r_matrix;
    double *u_vector;
    double *x_vector;
    double *y_vector;

    double *pers_matrix; // perspective matrix holder during QR decomposition
    double *inv_pers_mat_float; // inverse perspective matrix holder

    Word32      *persmat;                 // 2D perspective matrix parameters
    /******************************************/

    //LDC
    LensDistortionCorrection *ldc;

    AlgLink_MemRequests memRequestStruct; //memory, added by BZ, 11/14

    // Added for TDA3x 3D SRV Calibration
    Word32      *calmat;                   // perspective matrix parameters

    ldc_lensParameters *pLensPrm;

} svPEstimateStruct;


#endif
