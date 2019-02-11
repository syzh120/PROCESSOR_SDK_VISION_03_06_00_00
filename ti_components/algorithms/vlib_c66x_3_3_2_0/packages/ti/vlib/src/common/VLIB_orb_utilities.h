/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_ORB_UTILITIES_H

#define VLIB_ORB_UTILITIES_H 1

#include "VLIB_orb.h"
#include <math.h> /* atan2 math func is used */

typedef struct {
    double val[2][2]; /* This gives different results from the PC version if this is 32-bit float */
}RotationMatrix;

#ifndef SQRT2
#define SQRT2 0.707106781186548f
#endif

#ifndef PI_FLOAT
#define PI_FLOAT  3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f
#endif

#ifndef PI_DOUBLE
#define PI_DOUBLE 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#endif

#ifndef RADIAN2DEGREE_FLOAT
#define RADIAN2DEGREE_FLOAT(r) ((r) * (180.0f / PI_FLOAT))
#endif

#ifndef RADIAN2DEGREE_DOUBLE
#define RADIAN2DEGREE_DOUBLE(r) ((r) * (180.0 / PI_DOUBLE))
#endif

#ifndef ROUND_FLOAT
#define ROUND_FLOAT(val) ((int) ((val) + ((val) >= 0.0f ? 0.5f : -0.5f)))
#endif

#ifndef ROUND_DOUBLE
#define ROUND_DOUBLE(val) ((int) ((val) + ((val) >= 0.0 ? 0.5 : -0.5)))
#endif

/* Helper function to initialize the CORBParameters struct. */
/* For example, CORBParameters parameters = getCORBParameters(640, 480, 10, 20, 500); */
CORBParameters getCORBParameters(int width,
                                 int height,
                                 int marginPixels,
                                 unsigned char fastDifferenceThreshold,
                                 int n_features_desired);

int getRequiredScratchSize(const CORBParameters *parameters,
                           CORB_Bool harris,
                           CORB_Bool integralImage);

void initOrientationOffsets(const int width, CORBInput *input);

RotationMatrix getRotationMatrix(int orientationIndex);

void generateRotatedPatterns(CORBPatterns *patterns, const signed char *orbPattern31);

void generateRelativePattern(CORBPatterns *patterns);

void initPatterns(const int width, CORBPatterns *patterns, const signed char *orbPattern31);

CORBResult cORB_init(const CORBParameters *parameters, CORBInput *input);

#endif /* define VLIB_ORB_UTILITIES_H */

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

