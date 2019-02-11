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
 *  File: globalDefs.h
 *
 =======================================================================*/


#ifndef _GLOBAL_DEFS_INCLUDED_

#define _GLOBAL_DEFS_INCLUDED_

/********************************************/
/*COMMON*/
/********************************************/
#define MAX_INPUT_USENSORS      16

#define RGBp                0
#define RGBi                0
#define YUV420p             0
#define YUV420sp            1
#define YUV422i             0

//#define M_PI 3.14159265358979323846f


/*GENERAL TYPEDEFS*/
typedef struct {
    int x;
    int y;
} Point2D;

typedef struct {
    int x;
    int y;
    int z;
} Point3D;

typedef struct {
    Point3D pos; //position
    short phi; //azimuthal angle in degrees (rotation around z-axis)
    short theta; //pitch angle in degrees (vertical angle)
    short rho; //roll angle in degrees (rotation around view axis of sensor)
} ExtrinsicSensorParams;

typedef struct {
    short alpha; //azimuthal spread angle in degrees
    float intercept; //intercept for sensor data to physical distance calibration (linear fit)
    float slope; //slope for sensor data to physical distance calibration (linear fit)
} IntrinsicUSensorParams;


typedef struct {
    int deviceId;
    ExtrinsicSensorParams extPrms;
    IntrinsicUSensorParams intPrms;
    int data; //current sensor data
    float dist; //physical distance inferred from sensor data
} USensor;

/*===========================================
STATIC VARIABLES
===========================================*/
//YUV to RGB Conversion matrix, Q.8
static int yuv2rgb_Q8[3][3] = {
        { 256, 0, 359 },
        { 256, -88, -183 },
        { 256, 453, 0 } };

//RGB to YUV Conversion matrix, Q.8
static int rgb2yuv_Q8[3][3] = {
        { 77, 150, 29 },
        { -43, -85, 128 },
        { 128, -107, -21 } };



/********************************************/
/*EMBEDDED ONLY*/
/********************************************/
#ifndef PC_VERSION
#define MAX_INPUT_CAMERAS       4
#define MAX_L2_MEMORY_SIZE              0x20000
#endif

/********************************************/
/*PC_VERSION ONLY*/
/********************************************/
#ifdef PC_VERSION

//DEFINE THE PLATFORM-------------------------------------------------------------------

//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//#include "../../include/svCommonDefs.h"



typedef unsigned char  UInt8;
typedef short          Int16;
typedef unsigned short UInt16;
typedef int            Int32;
typedef unsigned int   UInt32;
//typedef long           Int32;



//VARIOUS I/O OPTIONS-------------------------------------------------------------------

#define FILE_IO                 (0x00000001)

#define GRAYSCALE               (0x00000010)
#define YUV420                  (0x00000020)
#define COLORTIFF               (0x00000100)

//DEFAULTS FOR I/O OPTIONS--------------------------------------------------------------
////TODO: change this to simpler notation types
#define DEF_INPUT_TYPE          (FILE_IO | COLORTIFF)
#define DEF_OUTPUT_TYPE         (FILE_IO | COLORTIFF)

//SYSTEM PARAMETERS
//Others
#define DEF_HEADER_LENGTH       0    //Header length for the input sequence file
#define MAX_NUM_OF_INPUT_ARGS   20   //Maximum number of command line input arguments

#define NUM_MAX_VIEWS (6)
#define NUM_MAX_COLORPLANES (3)

#define MAX_FRAME_VSIZE                    3000        //max input size
#define MAX_FRAME_HSIZE                    4000
#define MAX_FRAME_SIZE_FOR_DISPLAY_V       3000
#define MAX_FRAME_SIZE_FOR_DISPLAY_H       4000
#define MAX_EXTERNAL_MEMORY_SIZE           100000000
#define MAX_L2_MEMORY_SIZE                 200000
#define MAX_INPUT_CAMERAS                  NUM_MAX_VIEWS
#define MAX_COLOR_CHANNELS                 NUM_MAX_COLORPLANES

/******************************************************************************
*System Simulator
*******************************************************************************/
#define SYSTEM_MAX_PLANES               (3u)
typedef struct {
    void * bufAddr[SYSTEM_MAX_PLANES][NUM_MAX_VIEWS];
} System_VideoFrameCompositeBuffer;

typedef struct {
    Int32 *bufAddr[SYSTEM_MAX_PLANES];
} System_VideoFrameBuffer;

typedef int Bool;

/**
*******************************************************************************
* \brief Enums for data format.
*
*  All data formats may not be supported by all links. For supported data
*  formats please look link header file.
*
* SUPPORTED in ALL platforms
*
* Reference: copied this enum from
*            \VISION_SDK_02_01_00_00\vision_sdk\include\link_api\system_const.h
*
*******************************************************************************
*/
typedef enum
{
    SYSTEM_DF_YUV422I_UYVY = 0x0000,
    /**< YUV 422 Interleaved format - UYVY. */
    SYSTEM_DF_YUV422I_YUYV,
    /**< YUV 422 Interleaved format - YUYV. */
    SYSTEM_DF_YUV422I_YVYU,
    /**< YUV 422 Interleaved format - YVYU. */
    SYSTEM_DF_YUV422I_VYUY,
    /**< YUV 422 Interleaved format - VYUY. */
    SYSTEM_DF_YUV422SP_UV,
    /**< YUV 422 Semi-Planar - Y separate, UV interleaved. */
    SYSTEM_DF_YUV422SP_VU,
    /**< YUV 422 Semi-Planar - Y separate, VU interleaved. */
    SYSTEM_DF_YUV422P,
    /**< YUV 422 Planar - Y, U and V separate. */
    SYSTEM_DF_YUV420SP_UV,
    /**< YUV 420 Semi-Planar - Y separate, UV interleaved. */
    SYSTEM_DF_YUV420SP_VU,
    /**< YUV 420 Semi-Planar - Y separate, VU interleaved. */
    SYSTEM_DF_YUV420P,
    /**< YUV 420 Planar - Y, U and V separate. */
    SYSTEM_DF_YUV444P,
    /**< YUV 444 Planar - Y, U and V separate. */
    SYSTEM_DF_YUV444I,
    /**< YUV 444 interleaved - YUVYUV... */
    SYSTEM_DF_RGB16_565,
    /**< RGB565 16-bit - 5-bits R, 6-bits G, 5-bits B. */
    SYSTEM_DF_ARGB16_1555,
    /**< ARGB1555 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha (MSB). */
    SYSTEM_DF_RGBA16_5551,
    /**< RGBA5551 16-bit - 5-bits R, 5-bits G, 5-bits B, 1-bit Alpha (LSB). */
    SYSTEM_DF_ARGB16_4444,
    /**< ARGB4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha (MSB). */
    SYSTEM_DF_RGBA16_4444,
    /**< RGBA4444 16-bit - 4-bits R, 4-bits G, 4-bits B, 4-bit Alpha (LSB). */
    SYSTEM_DF_ARGB24_6666,
    /**< ARGB6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha (MSB). */
    SYSTEM_DF_RGBA24_6666,
    /**< RGBA6666 24-bit - 6-bits R, 6-bits G, 6-bits B, 6-bit Alpha (LSB). */
    SYSTEM_DF_RGB24_888,
    /**< RGB24 24-bit - 8-bits R, 8-bits G, 8-bits B. */
    SYSTEM_DF_BGRX_4444,
    /**<RGBx12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused(LSB).*/
    SYSTEM_DF_XBGR_4444,
    /**<xRGB12-16bit- 4-bits R, 4-bits G, 4-bits B, 4-bits unused(MSB).*/
    SYSTEM_DF_ARGB32_8888,
    /**< ARGB32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha (MSB). */
    SYSTEM_DF_RGBA32_8888,
    /**< RGBA32 32-bit - 8-bits R, 8-bits G, 8-bits B, 8-bit Alpha (LSB). */
    SYSTEM_DF_BGR16_565,
    /**< BGR565 16-bit -   5-bits B, 6-bits G, 5-bits R. */
    SYSTEM_DF_ABGR16_1555,
    /**< ABGR1555 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha (MSB). */
    SYSTEM_DF_ABGR16_4444,
    /**< ABGR4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha (MSB). */
    SYSTEM_DF_BGRA16_5551,
    /**< BGRA5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit Alpha (LSB). */
    SYSTEM_DF_BGRA16_4444,
    /**< BGRA4444 16-bit - 4-bits B, 4-bits G, 4-bits R, 4-bit Alpha (LSB). */
    SYSTEM_DF_AGBR16_1555,
    /**< ABGR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit Alpha (MSB). */
    SYSTEM_DF_AGBR16_4444,
    /**< ABGR4444 16-bit - 4-bits G, 4-bits B, 4-bits R, 4-bit Alpha (MSB). */
    SYSTEM_DF_XGBR16_1555,
    /**< XGBR1555 16-bit - 5-bits G, 5-bits B, 5-bits R, 1-bit unused (MSB). */
    SYSTEM_DF_BGRX16_5551,
    /**< BGRX5551 16-bit - 5-bits B, 5-bits G, 5-bits R, 1-bit unused (MSB). */
    SYSTEM_DF_ABGR24_6666,
    /**< ABGR6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha (MSB). */
    SYSTEM_DF_BGR24_888,
    /**< BGR888 24-bit - 8-bits B, 8-bits G, 8-bits R. */
    SYSTEM_DF_XBGR24_8888,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused(MSB) */
    SYSTEM_DF_RGBX24_8888,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused(LSB) */
    SYSTEM_DF_BGRX24_8888,
    /**< xBGR888 24-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit unused(MSB) */
    SYSTEM_DF_ABGR32_8888,
    /**< ABGR8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha (MSB). */
    SYSTEM_DF_BGRA24_6666,
    /**< BGRA6666 24-bit - 6-bits B, 6-bits G, 6-bits R, 6-bit Alpha (LSB). */
    SYSTEM_DF_BGRA32_8888,
    /**< BGRA8888 32-bit - 8-bits B, 8-bits G, 8-bits R, 8-bit Alpha (LSB). */
    SYSTEM_DF_BITMAP8,
    /**< BITMAP 8bpp. */
    SYSTEM_DF_BITMAP4_LOWER,
    /**< BITMAP 4bpp lower address in CLUT. */
    SYSTEM_DF_BITMAP4_UPPER,
    /**< BITMAP 4bpp upper address in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET0,
    /**< BITMAP 2bpp offset 0 in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET1,
    /**< BITMAP 2bpp offset 1 in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET2,
    /**< BITMAP 2bpp offset 2 in CLUT. */
    SYSTEM_DF_BITMAP2_OFFSET3,
    /**< BITMAP 2bpp offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET0,
    /**< BITMAP 1bpp offset 0 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET1,
    /**< BITMAP 1bpp offset 1 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET2,
    /**< BITMAP 1bpp offset 2 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET3,
    /**< BITMAP 1bpp offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET4,
    /**< BITMAP 1bpp offset 4 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET5,
    /**< BITMAP 1bpp offset 5 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET6,
    /**< BITMAP 1bpp offset 6 in CLUT. */
    SYSTEM_DF_BITMAP1_OFFSET7,
    /**< BITMAP 1bpp offset 7 in CLUT. */
    SYSTEM_DF_BITMAP8_BGRA32,
    /**< BITMAP 8bpp BGRA32. */
    SYSTEM_DF_BITMAP4_BGRA32_LOWER,
    /**< BITMAP 4bpp BGRA32 lower address in CLUT. */
    SYSTEM_DF_BITMAP4_BGRA32_UPPER,
    /**< BITMAP 4bpp BGRA32 upper address in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET0,
    /**< BITMAP 2bpp BGRA32 offset 0 in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET1,
    /**< BITMAP 2bpp BGRA32 offset 1 in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET2,
    /**< BITMAP 2bpp BGRA32 offset 2 in CLUT. */
    SYSTEM_DF_BITMAP2_BGRA32_OFFSET3,
    /**< BITMAP 2bpp BGRA32 offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET0,
    /**< BITMAP 1bpp BGRA32 offset 0 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET1,
    /**< BITMAP 1bpp BGRA32 offset 1 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET2,
    /**< BITMAP 1bpp BGRA32 offset 2 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET3,
    /**< BITMAP 1bpp BGRA32 offset 3 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET4,
    /**< BITMAP 1bpp BGRA32 offset 4 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET5,
    /**< BITMAP 1bpp BGRA32 offset 5 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET6,
    /**< BITMAP 1bpp BGRA32 offset 6 in CLUT. */
    SYSTEM_DF_BITMAP1_BGRA32_OFFSET7,
    /**< BITMAP 1bpp BGRA32 offset 7 in CLUT. */
    SYSTEM_DF_BAYER_RAW,
    /**< Bayer pattern. */
    SYSTEM_DF_BAYER_GRBG,
    /** < Raw bayer data color pattern
    * G R G R ...
    * B G B G ...
    */
    SYSTEM_DF_BAYER_RGGB,
    /** < Raw bayer data color pattern
    * R G G R ...
    * G B G B ...
    */
    SYSTEM_DF_BAYER_BGGR,
    /** < Raw bayer data color pattern
    * B G B G ...
    * G B G B ...
    */
    SYSTEM_DF_BAYER_GBRG,
    /** < Raw bayer data color pattern
    * G B G B ...
    * R R R G ...
    */
    SYSTEM_DF_RAW_VBI,
    /**< Raw VBI data. */
    SYSTEM_DF_RAW24,
    /**< 24 bit raw-data. */
    SYSTEM_DF_RAW16,
    /**< 16 bit raw-data. */
    SYSTEM_DF_RAW08,
    /**< 8 bit raw-data. */
    SYSTEM_DF_MISC,
    /**< For future purpose. */
    SYSTEM_DF_INVALID,
    /**< Invalid data format. Could be used to initialize variables. */
    SYSTEM_DF_FORCE32BITS = 0xFFFFFFFF
    /**< This should be the last value after the max enumeration value.
    *   This is to make sure enum size defaults to 32 bits always regardless
    *   of compiler.
    */
}System_VideoDataFormat;

#else

// Added for TDA3x 3D SRV Calibration
#define NUM_MAX_VIEWS (6)

#endif // PC_VERSION

#endif //_GLOBAL_DEFS_INCLUDED_

