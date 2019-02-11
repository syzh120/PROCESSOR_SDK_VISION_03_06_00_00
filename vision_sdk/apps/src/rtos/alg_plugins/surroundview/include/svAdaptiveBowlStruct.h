/*=======================================================================
 *
 *            Texas Instruments Internal Reference Software
 *
 *                           EP Systems Lab
 *                     Embedded Signal Processing
 *                             Imaging R&D
 *
 *         Copyright (c) 2018 Texas Instruments, Incorporated.
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
 *  File: svAdaptiveBowlStruct.h
 *
 =======================================================================*/

/**
 *******************************************************************************
 *
 *   \brief Max number of history for depth values
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#include "../include/svCommonDefs.h"
#include "../include/memRequestAlgo.h"
#include "../include/globalDefs.h"
#include "../include/svUFusionStruct.h"
#include "../../commonutils/lens_distortion_correction/lens_distortion_correction.h"

#define MAX_DEPTH_HISTORY (5)

#define LEFT_INITIAL_DISTANCE 250


#ifndef _SV_ADAPTIVEBOWL_STRUCT_INCLUDED_

#define _SV_ADAPTIVEBOWL_STRUCT_INCLUDED_

//Surround View geometric alignment private structure: Contains all SV geometric alignment input and output parameters.
//To be updated
typedef struct {

    uWord32     enableSV_GAlign;
    //Input frame size and output frame size
    Word16      SVInCamFrmHeight;
    Word16      SVInCamFrmWidth;
    Word16      SVOutDisplayHeight;
    Word16      SVOutDisplayWidth;
    Word16      ldcOutFrmWidth, ldcOutFrmHeight;

    //number of color channels
    Byte        numColorChannels;
    //number of cameras
    Byte        numCameras;
    //number of output parameters from geometric alignment, per camera, per color channel
    Byte        numParamsPAlignPerColorPerCam;

    // Algorithm parameters
    //uWord16       focalLength;

    double BRIEF_scale;
    //// pointers to auxiliary variable arrays


    // pointers to geometric LUT and boundary information
    // uWord16    *GAlignViewLUT[MAX_NUM_CAMERAS];  //geometric LUT for each view
    uWord16    *overlapRegMarkPts;  //The coordinates of the overlapping region corner points in the composite scene
    uWord16    *seamMarkPts;

    // pointers to input frames
    Byte    *currFrm[MAX_INPUT_CAMERAS];            // current input frames

    // pointers to output LUTs
    uWord16     *GAlignLUT;
    uWord16     *GAlignLUT3D;
    float       *GAlignLUT3D_XYZ;
    float       *GAlignLUT3D_undist;
    uWord16     *LDCLUT[MAX_INPUT_CAMERAS];
        Byte         ldcDownScaleFactor;
    //uWord32     *GAlignLUT; //<=== changed from uWord16 to uWord32, BZ 11/14


    //Byte     *GAlignLUT;
    uWord32     *GAlignLUTView02; // LUT data for views 0 and 2
    uWord32     *GAlignLUTView13; // LUT data for views 1 and 3

    uWord16     *DMAPixelLevelLUT; // LUT to hold overlapping region Y data
    uWord16     *DMAPixelLevelLUT1; // LUT to hold non-overlapping region Y data

    uWord16     *DMAPixelLevelLUT_UV; // LUT to hold overlapping region U and V data
    uWord16     *DMAPixelLevelLUT1_UV; // LUT to hold non-overlapping region U and V data

    //Byte     *GAlignOut;

    Word32  *persmat; // perspective matrix parameters
    Word32  *autoPersmat;
    Bool     enableAutoCalib;
    uWord16 *sinatanLUT; // LUT that holds sin(atan(x)) values
    uWord16 *tanasinLUT; // LUT that holds tan(asin(x)) values
    uWord32     *descriptorPatternLUT; //descriptor score for pattern matching, target center location for ultrasonic calibration purpose

    uWord16 *InCamFrmDistortionCen; // frame distortion centers for cameras
    uWord16 *OutDisplayFrmCen; // output frame center

    Word16  *focalLength; // focal length for fish-eye lens model
    Word16 saladbowlFocalLength; // focal length for simulated salad bowl effect
    Word16 defaultFocalLength; // default focal length

    Word32 temp_locver; // to hold vertical pixel coordinate temporarily
    Word32 temp_lochor; // to hold horizontal pixel coordinate temporarily

    Word32 centroidX; // to hold target horizontal coordinate temporarily
    Word32 centroidY; // to hold target horizontal coordinate temporarily

    uWord16 *overlapping_area; // areas that are seen by two cameras

    Word32  *view0_reg3_feat; // features in region 0 of view 0
    Word32  *view3_reg3_feat;
    Word32  *view1_reg0_feat;
    Word32  *view0_reg0_feat;
    Word32  *view2_reg1_feat;
    Word32  *view1_reg1_feat;
    Word32  *view3_reg2_feat;
    Word32  *view2_reg2_feat;

    Word32  *target_corner_loc_feat;

    uWord16 *overlapping_area_Harris; // Harris output of an overlapping area
    uWord16 *blurred_overlapping_area_A; // blurred overlapping area to be used for BRIEF calculation
    uWord16 *blurred_overlapping_area_B; // blurred overlapping area to be used for BRIEF calculation

    Word16 GAlign_Success; // flag for success of geometrix alignment

    Word16  max_num_features; // maximum number of allowed features
    Word16  min_match_score; //added by BZ, 11/14  // minimum score to accept two features as a match
    Word16  max_BRIEF_score; //added by BZ, 11/14  // maximum BRIEF score to accept two features as a match
    Word16  min_distBW_feats; // minimum distance between features
    Word16  downsamp_ratio; // downsample ratio used during harris corner detection

    Word16 DMAblockSizeV; // vertical DMA block size
    Word16 DMAblockSizeH; // horizontal DMA block size

    SV_CarBox_ParamsStruct svCarBoxParams; // parameters for the black car box region in the middle of output frame

    AlgLink_MemRequests memRequestStruct; //memory, added by BZ, 11/14


    Word16 *BRIEF_XY; // BRIEF pair locations

    /////////////////////////////////////
    Word32 *perscoor0_3reg3; // Q27.4, Array Structure: [perscoor0ver, perscoor0hor, perscoor3ver, perscoor3hor], [....], ...
    Word32 *perscoor1_0reg0;
    Word32 *perscoor2_1reg1;
    Word32 *perscoor3_2reg2;

    double *perscoor0_3reg3_float; // floating point versions of input feature coordinates
    double *perscoor1_0reg0_float;
    double *perscoor2_1reg1_float;
    double *perscoor3_2reg2_float;

    double *pers_mat0; // floating point versions of perspective matrices
    double *pers_mat1;
    double *pers_mat2;
    double *pers_mat3;

    double *A_matrix; // A*x = b memory holders
    double *B_vector;
    double *c_vector;
    double *d_vector;

    double *pers_matrix; // perspective matrix holder during QR decomposition
    double *inv_pers_mat_float; // inverse perspective matrix holder

    uWord16 *DMA_LUT; // LUT to hold DMA structure for Y
    uWord16 *DMA_LUT1; // LUT to hold DMA structure for U and V
    uWord16 *DMAtempMemory; // to hold temporary DMA data
    uWord16 *DMAtempMemory1; // to hold temporary DMA data

    Word32 *euc_distance; // eucladian distance

    uWord32 *descriptor_A; // descriptor for features from image A
    uWord32 *descriptor_B; // descriptor for features from image B
    Word32 *orig_dist_mat; // original BRIEF distance matrix
    Word32 *target_corner_brief_dist; // target corner locate finding BRIEF distance matrix
    Word32 *hor_dist_mat; // BRIEF distance matrix sorted horizontally
    Word32 *ver_dist_mat; // BRIEF distance matrix sorted vertically
    Word32 *hor_index_matrix; // BRIEF distance index matrix sorted horizontally
    Word32 *ver_index_matrix; // BRIEF distance index matrix sorted vertically
    Word32 *horq; // to hold temporary horizontal matrix values
    Word32 *verq; // to hold temporary vertical matrix values
    Word32 *strmat; // feature match strength matrix
    Word32 *match_pos_A; // to hold matched feature positions from image A
    Word32 *match_scr_A; // to hold matched feature scores from image A
    Word32 *match_pos_B; // to hold matched feature positions from image B
    Word32 *match_scr_B; // to hold matched feature scores from image B
    Word32 *ordmatvec; // ordered match data
    Word32 *inx; // matched indices
    Word32 *featsubset_A; // subset of features from image A
    Word32 *featsubset_B; // subset of features from image B
    Word32 *modfeatsubset_B; // modified subset of features from image B (after transformation)
    Word32 *modfeat_B; // modified features from image B
    Word32 *pers_mat; // perspective matrix
    /////////////////////////////////
    unsigned long long  *fx2_col_buf; // temporary buffers in Harris score calculation
    unsigned long long  *fy2_col_buf;
    long long *fxfy_col_buf;

    Byte        outputMode; // 0: 2D or 1 : 3D SRV or 2: 2D with LDC
    // Subsample ratio for 3D SRV
    Byte         subsampleratio;

    //Pixel Per Cm Output buffer
    Byte    enablePixelsPerCm;
    float pixelPerCmInternal[MAX_NUM_VIEWS];
    Byte useDefaultPixelsPerCm;
    Word32 *chartFeatPoints;

    // Used for TDA3X 3D SRV
    Word16 *LDCLUT3D[MAX_INPUT_CAMERAS*MAX_NO_VIRTUALVIEWS];
    float *view2worldmesh[MAX_NO_VIRTUALVIEWS];
    Word32 *LDC3D_width;
    Word32 *LDC3D_height;
    Word32 *car_posx;
    Word32 *car_posy;
    Word32 *calmat;
    LensDistortionCorrection *ldc;
    ldc_lensParameters *pLensPrm;
    ldc_lensParameters *pLensPrm2D;

    /* XY offsets for adaptive bowl */
    Word32 offsetXleft;
    Word32 offsetXright;
    Word32 offsetYfront;
    Word32 offsetYback;

    UltrasonicCapture_MeasurementInfo *ultrasonicCaptureInPtr; //input from Ultrasonic Capture

    Bool newDepthValues;
    /**< Flag to indicate that new depth values require a new LUT
     */
    Bool newFrontDepthValues;
    /**< Flag to indicate that there are new front depth values
     */
    Bool newRightDepthValues;
    /**< Flag to indicate that there are new right depth values
     */
    Bool newBackDepthValues;
    /**< Flag to indicate that there are new back depth values
     */
    Bool newLeftDepthValues;
    /**< Flag to indicate that there are new left depth values
     */
    UInt32 previousFrontDepthValue[MAX_DEPTH_HISTORY];
    /**< Contains previous depth value obtained from front sensor
     */
    UInt32 previousRightDepthValue[MAX_DEPTH_HISTORY];
    /**< Contains previous depth value obtained from right sensor
     */
    UInt32 previousBackDepthValue[MAX_DEPTH_HISTORY];
    /**< Contains previous depth value obtained from back sensor
     */
    UInt32 previousLeftDepthValue[MAX_DEPTH_HISTORY];
    /**< Contains previous depth value obtained from left sensor
     */
    UInt32 medianFrontDepthValue;
    /**< Contains median depth value obtained from front sensor
     */
    UInt32 medianRightDepthValue;
    /**< Contains median depth value obtained from right sensor
     */
    UInt32 medianBackDepthValue;
    /**< Contains median depth value obtained from back sensor
     */
    UInt32 medianLeftDepthValue;
    /**< Contains median depth value obtained from left sensor
     */
    UInt32 frontDepthValue;
    /**< Contains front sensor depth value used to generate next bowl
     */
    UInt32 rightDepthValue;
    /**< Contains right sensor depth value used to generate next bowl
     */
    UInt32 backDepthValue;
    /**< Contains back sensor depth value used to generate next bowl
     */
    UInt32 leftDepthValue;
    /**< Contains left sensor depth value used to generate next bowl
     */
    Int64 transitionFrontDepthValue;
    /**< Contains transition front sensor depth value used to generate next bowl
     */
    Int64 transitionRightDepthValue;
    /**< Contains transition right sensor depth value used to generate next bowl
     */
    Int64 transitionBackDepthValue;
    /**< Contains transition back sensor depth value used to generate next bowl
     */
    Int64 transitionLeftDepthValue;
    /**< Contains transition left sensor depth value used to generate next bowl
     */
    UInt32 frontTransitionsRemaining;
    /**< Contains number of transitions remaining to next front bowl
     */
    UInt32 rightTransitionsRemaining;
    /**< Contains number of transitions remaining to next right bowl
     */
    UInt32 backTransitionsRemaining;
    /**< Contains number of transitions remaining to next back bowl
     */
    UInt32 leftTransitionsRemaining;
    /**< Contains number of transitions remaining to next left bowl
     */
    Bool isFirstTime;
    /**< Flag to indicate that it is the first time through the algo.
     */
    UInt8 useWideBowl;
    /**< Flag to indicate whether or not to use wide bowl.
     */
    Bool inIntermediateState;
    /**< Flag to indicate whether or not wide bowl can be enabled/disabled.
     */
    UInt8 usePresetView;
    /**< Flag to indicate whether or not to use preset view.
     */
    Bool inIntermediateViewState;
    /**< Flag to indicate whether or not preset can be enabled/disabled.
     */
    double leftObjectDistance;
    /**< Holds current left object reference distance
     */
} svAdaptiveBowlStruct;

#endif
