//To include system type def header
#ifndef _SV_PECOMMONDEFS_H_
#define _SV_PECOMMONDEFS_H_


#define LIN_ALG_FLOUBLE_TYPE 1 /* 0 = float, 1 = double */
/*#ifdef AUTOCALIB_USE_FLOAT
typedef float Flouble;
#else
typedef double Flouble;
#endif*/


#ifndef PC_VERSION
#include <include/link_api/system.h>
#endif
#ifdef PC_VERSION
#include "../algorithmSrc/include/globalDefs.h"
#endif

#include <math.h>

#include "../../commonutils/linAlg/linAlg2DTypes.h"
#include "../../commonutils/linAlg/linAlg3DTypes.h"

#include "calmatDefs.h"

#if LIN_ALG_FLOUBLE_TYPE == 0
#define AUTOCALIB_USE_FLOAT
#elif LIN_ALG_FLOUBLE_TYPE == 1
#else
#error("Unknown value for LIN_ALG_FLOUBLE_TYPE");
#endif

/*#ifdef AUTOCALIB_USE_FLOAT
    #define SQRT(x) sqrtf((x))
    #define COS(x)   cosf((x))
    #define SIN(x)   sinf((x))
    #define TAN(x)   tanf((x))
    #define ACOS(x)  acosf((x))
    #define ASIN(x)  asinf((x))
    #define ATAN(x)  atanf((x))
    #define EXP(x)   expf((x))
    #define POW(x,p) powf((x),(p))
    #define FABS(x)  fabsf((x))
    #define FLOUBLE_MAX FLT_MAX
    #define FLOUBLE_MIN FLT_MIN
    #define FLOUBLE_EPSILON FLT_EPSILON
#else
    #define SQRT(x)  sqrt((x))
    #define COS(x)   cos((x))
    #define SIN(x)   sin((x))
    #define TAN(x)   tan((x))
    #define ACOS(x)  acos((x))
    #define ASIN(x)  asin((x))
    #define ATAN(x)  atan((x))
    #define EXP(x)   exp((x))
    #define POW(x,p) pow((x),(p))
    #define FABS(x)  fabs((x))
    #define FLOUBLE_MAX DBL_MAX
    #define FLOUBLE_MIN DBL_MIN
    #define FLOUBLE_EPSILON DBL_EPSILON
#endif*/

#define SVD_2D 0

#define A_NROWS 16
#define A_NCOLS 9
#define A_SIZE  A_NROWS*A_NCOLS
#define U_SIZE  A_NROWS*A_NROWS
#define V_SIZE  A_NROWS*A_NROWS //A_NCOLS*A_NCOLS


typedef struct {
    UInt16 distCenterX;
    UInt16 distCenterY;
    UInt16 distFocalLength;
    Matrix3D_f K;
    Matrix3D_f invK;
} CameraIntrinsicParams;


typedef enum
{
    ESTIMATE_RT_DLT,
    ESTIMATE_RT_RANSAC
} rtEstimateMethod;


/*****************************************/
/* For 2D perpective matrix              */
/*****************************************/
typedef struct{
    UInt16 CarBoxCenter_x;  //x coordinate of car box in output frame
    UInt16 CarBoxCenter_y;  //y coordinate of car box in output frame
    UInt16 CarBox_height;   //height of car box
    UInt16 CarBox_width;    //width of car box
} carBoxParamsStruct;  //structure to hold car box parameters
/******************************************/

#endif
