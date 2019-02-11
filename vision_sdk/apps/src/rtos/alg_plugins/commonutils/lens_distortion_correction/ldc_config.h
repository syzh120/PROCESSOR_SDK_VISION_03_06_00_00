/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*                           EP Systems Lab
*                    Perception & Analytics Lab R&D
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
*  File: ldc_config.h
*
=======================================================================*/

/*platform-specific data types*/
#ifdef PC_VERSION
    typedef int Int32;
#else
    #include <include/link_api/system.h>
#endif

/*user parameters*/
#define LDC_LIB_DATA_TYPE               0       /* 0: float, 1:double */
#define LDC_LIB_U2D_LUT_TYPE            2       /* 0: theta[rad]->rd/ru, 1: ru->rd/ru, 2: theta[rad]->rd */
#define LDC_LIB_D2U_LUT_TYPE            0       /* 0: rdSquared->ru/rd */
#define LDC_LIB_INTERPOLATION_METHOD    2       /* 0: 'previous', 1: 'nearest', 2:'linear' */

#define LDC_MAX_NUM_CAMERAS             (6)     /* maximum number of cameras allowed */
#define LDC_U2D_TABLE_MAX_LENGTH        (1024)  /* maximum u2d table length allowed */
#define LDC_D2U_TABLE_MAX_LENGTH        (1024)  /* maximum d2d table length allowed */

typedef struct
{
    Int32 ldcLUT_numCams;
    /**< Num of cameras */
    Int32 ldcLUT_distortionCenters[2*LDC_MAX_NUM_CAMERAS];
    /**< Num of Lens Distortion centres */
    float ldcLUT_focalLength;
    /**< Lens focal length */

    Int32 U2D_type;
    /**< Lens Undistort to Distort type (must match macro LDC_LIB_U2D_LUT_TYPE)*/
    Int32 ldcLUT_U2D_length;
    /**< Lens Undistort to Distort length */
    float ldcLUT_U2D_step;
    /**< Lens Undistort to Distort step */
    float ldcLUT_U2D_table[LDC_U2D_TABLE_MAX_LENGTH];
    /**< Lens Undistort to Distort table */

    Int32 D2U_type;
    /**< Lens Distort to Undistort type (must match macro LDC_LIB_D2U_LUT_TYPE)*/
    Int32 ldcLUT_D2U_length;
    /**< Lens Distort to Undistort length */
    float ldcLUT_D2U_step;
    /**< Lens Distort to Undistort step */
    float ldcLUT_D2U_table[LDC_D2U_TABLE_MAX_LENGTH];
    /**< Lens Distort to Undistort table */
}ldc_lensParameters;

