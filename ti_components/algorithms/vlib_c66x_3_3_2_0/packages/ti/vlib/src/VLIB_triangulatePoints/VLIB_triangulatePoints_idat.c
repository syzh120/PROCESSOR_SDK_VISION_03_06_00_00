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
 **|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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
#include "../common/VLIB_memory.h"
#include "VLIB_triangulatePoints_idat.h"

static VLIB_F32 track_0[2*2] = {-0.4651272, -0.2504775,/*(N-1)th frame image location (x, y)*/
                                -0.4591167, -0.2480025 /*(N)th frame image location (x, y)*/}; // track Id = 15

static VLIB_F32 out3DPoint_0[3] = {120.868, /* X co-ordinate of 3D point corresponding to track "track_0"*/
                                   51.718,  /* Y co-ordinate of 3D point corresponding to track "track_0"*/
                                   29.469   /* Z co-ordinate of 3D point corresponding to track "track_0"*/};

static VLIB_F32 track_1[3*2] = {-0.71262, -0.2504775,/*(N-2)th frame image location (x, y)*/
                                -0.7120897, -0.2472954,/*(N-1)th frame image location (x, y)*/
                                -0.7097031, -0.2452624 /*(N)th frame image location (x, y)*/ }; // trackId = 2

static VLIB_F32 out3DPoint_1[3] = {49.686, /* X co-ordinate of 3D point corresponding to track "track_1"*/
                                   31.901, /* Y co-ordinate of 3D point corresponding to track "track_1"*/
                                   12.071  /* Z co-ordinate of 3D point corresponding to track "track_1"*/};

static VLIB_F32 out3DPoint_1_5[3] = {50.031, /* X co-ordinate of 3D point corresponding to track "track_1"*/
                                     32.145, /* Y co-ordinate of 3D point corresponding to track "track_1"*/
                                     12.153  /* Z co-ordinate of 3D point corresponding to track "track_1"*/};

static VLIB_F32 out3DPoint_1_3[3] = {49.811, /* X co-ordinate of 3D point corresponding to track "track_1"*/
                                     31.995, /* Y co-ordinate of 3D point corresponding to track "track_1"*/
                                     12.101  /* Z co-ordinate of 3D point corresponding to track "track_1"*/};

static VLIB_F32 track_2[4*2] = {-0.5726098, -0.247649,/*(N-3)th frame image location (x, y)*/
                                -0.5775596, -0.245616,/*(N-2)th frame image location (x, y)*/
                                -0.5763222, -0.2433178,/*(N-1)th frame image location (x, y)*/
                                -0.5696929, -0.2401358 /*(N)th frame image location (x, y)*/ }; // trackId = 137

static VLIB_F32 out3DPoint_2[3] = {129.289, /* X co-ordinate of 3D point corresponding to track "track_2"*/
                                   69.243,  /* Y co-ordinate of 3D point corresponding to track "track_2"*/
                                   30.555   /* Z co-ordinate of 3D point corresponding to track "track_2"*/};

static VLIB_F32 out3DPoint_2_5[3] = {129.409, /* X co-ordinate of 3D point corresponding to track "track_2"*/
                                     69.308, /* Y co-ordinate of 3D point corresponding to track "track_2"*/
                                     30.583  /* Z co-ordinate of 3D point corresponding to track "track_2"*/};

static VLIB_F32 out3DPoint_2_3[3] = {133.289, /* X co-ordinate of 3D point corresponding to track "track_2"*/
                                     71.433, /* Y co-ordinate of 3D point corresponding to track "track_2"*/
                                     31.494  /* Z co-ordinate of 3D point corresponding to track "track_2"*/};

static VLIB_F32 track_3[5*2] = {0.0687502, -0.2355395,/*(N-4)th frame image location (x, y)*/
                                0.06963408, -0.238368,/*(N-3)th frame image location (x, y)*/
                                0.0661869, -0.2382796,/*(N-2)th frame image location (x, y)*/
                                0.07272774, -0.2409313,/*(N-1)th frame image location (x, y)*/
                                0.08059448, -0.2436714 /*(N)th frame image location (x, y)*/ }; // trackId = 29

static VLIB_F32 out3DPoint_3[3] = {13.723, /* X co-ordinate of 3D point corresponding to track "track_3"*/
                                   -1.410, /* Y co-ordinate of 3D point corresponding to track "track_3"*/
                                   3.434  /* Z co-ordinate of 3D point corresponding to track "track_3"*/};

static VLIB_F32 out3DPoint_3_5[3] = {13.724, /* X co-ordinate of 3D point corresponding to track "track_3"*/
                                     -1.410, /* Y co-ordinate of 3D point corresponding to track "track_3"*/
                                     3.432   /* Z co-ordinate of 3D point corresponding to track "track_3"*/};

static VLIB_F32 out3DPoint_3_3[3] = {13.721, /* X co-ordinate of 3D point corresponding to track "track_3"*/
                                     -1.410, /* Y co-ordinate of 3D point corresponding to track "track_3"*/
                                     3.433  /* Z co-ordinate of 3D point corresponding to track "track_3"*/};

static VLIB_F32 track_4[6*2] = {-0.383101, -0.2405777,/*(N-5)th frame image location (x, y)*/
                                -0.3988345, -0.2426107,/*(N-4)th frame image location (x, y)*/
                                -0.4085574, -0.2434062,/*(N-3)th frame image location (x, y)*/
                                -0.4132421, -0.2419036,/*(N-2)th frame image location (x, y)*/
                                -0.4119162, -0.2397822,/*(N-1)th frame image location (x, y)*/
                                -0.4056405, -0.2372189 /*(N)th frame image location (x, y)*/ }; // trackId = 19

static VLIB_F32 out3DPoint_4[3] = {108.262,    /* X co-ordinate of 3D point corresponding to track "track_4"*/
                                   40.652,     /* Y co-ordinate of 3D point corresponding to track "track_4"*/
                                   25.282      /* Z co-ordinate of 3D point corresponding to track "track_4"*/};

static VLIB_F32 out3DPoint_4_5[3] = {108.7552, /* X co-ordinate of 3D point corresponding to track "track_4"*/
                                     40.887,   /* Y co-ordinate of 3D point corresponding to track "track_4"*/
                                     25.426    /* Z co-ordinate of 3D point corresponding to track "track_4"*/};

static VLIB_F32 out3DPoint_4_3[3] = {108.546,  /* X co-ordinate of 3D point corresponding to track "track_4"*/
                                     40.762,   /* Y co-ordinate of 3D point corresponding to track "track_4"*/
                                     25.397    /* Z co-ordinate of 3D point corresponding to track "track_4"*/};

/* Last Six frame Camera extrinsic parameters
 */
static VLIB_F32 camExtPrm[6*16] = {
                   /* (N - 5)th frame extrinsic camera parameters */
                  -0.001088635,   -0.9999763,      0.006787182,    -0.316397,
                  -0.008512072,   -0.006777671,   -0.9999409,       0.7341205,
                   0.9999632,     -0.001146343,   -0.0085044930,   -1.138036,
                   0.0,            0.0,            0.0,             1.0,
                   /* (N - 4)th frame extrinsic camera parameters */
                  -0.01328138,    -0.999905,       0.003674412,    -0.318944,
                  -0.009643581,   -0.003546472,   -0.9999473,       0.745724,
                   0.9998653,     -0.01331611,    -0.009595564,    -1.446814,
                   0.0,            0.0,            0.0,             1.0,
                   /* (N - 3)th frame extrinsic camera parameters */
                  -0.01987672,    -0.9998009,      0.001729067,    -0.3194034,
                  -0.009878644,   -0.001532928,   -0.9999501,       0.7536414,
                   0.9997537,     -0.0198928,     -0.009846209,    -1.731501,
                   0.0,            0.0,            0.0,             1.0,
                   /* (N - 2)th frame extrinsic camera parameters */
                  -0.02201085,   -0.9997572,      -0.001049807,    -0.3225931,
                  -0.008563456,   0.001238561,    -0.9999626,       0.7572622,
                   0.9997211,    -0.02200103,     -0.008588639,    -2.021409,
                   0.0,            0.0,            0.0,             1.0,
                   /* (N - 1)th frame extrinsic camera parameters */
                  -0.02002354,   -0.9997959,      -0.002685567,    -0.3306924,
                  -0.006622053,   0.002818673,    -0.9999742,       0.7583499,
                   0.9997776,    -0.02000523,     -0.006677141,    -2.347819,
                   0.0,            0.0,            0.0,             1.0,
                   /* Nth frame extrinsic camera parameters */
                  -0.01377226,   -0.9998924,   -0.005051377,       -0.3449626,
                  -0.005474702,   0.005127189, -0.9999719,          0.7596228,
                   0.9998901,    -0.01374421,  -0.005544727,       -2.651081,
                   0.0,            0.0,            0.0,             1.0};

static triangulatePoints_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           numTracks,
           *ptrack[4],
           *camExtPrm,
           trackLength[4],
           maxIter,
           *outX[4],
           desc
        },
    *********************************************/
    {
        STATIC,
        16,
        {track_4,track_4,track_4,track_4},
        camExtPrm,
        {6,6,6,6},
        3,
        {out3DPoint_4_3,out3DPoint_4_3,out3DPoint_4_3,out3DPoint_4_3},
        0x0,
        "Even number of Track :: Low value of maxIter"
    },
    {
        STATIC,
        1,
        {track_0,NULL,NULL,NULL},
        camExtPrm,
        {2,0,0,0},
        10,
        {out3DPoint_0,NULL,NULL,NULL},
        0x0,
        "Odd number of Track :: Worst cycle performance"
    },
    {
        STATIC,
        1600,
        {track_0,track_1,NULL,NULL},
        camExtPrm,
        {2,3,0,0},
        10,
        {out3DPoint_0,out3DPoint_1,NULL,NULL},
        0x0,
        "Even number of Track :: Good cycle performance"
    },
    {
        STATIC,
        4,
        {track_1,track_2,track_3,track_4},
        camExtPrm,
        {3,4,5,6},
        10,
        {out3DPoint_1,out3DPoint_2,out3DPoint_3,out3DPoint_4},
        0x0,
        "Even number of Track :: High value of maxIter"
    },
    {
        STATIC,
        4,
        {track_1,track_2,track_3,track_4},
        camExtPrm,
        {3,4,5,6},
        5,
        {out3DPoint_1_5,out3DPoint_2_5,out3DPoint_3_5,out3DPoint_4_5},
        0x0,
        "Even number of Track :: Mid value of maxIter"
    },
    {
        STATIC,
        4,
        {track_1,track_2,track_3,track_4},
        camExtPrm,
        {3,4,5,6},
        3,
        {out3DPoint_1_3,out3DPoint_2_3,out3DPoint_3_3,out3DPoint_4_3},
        0x0,
        "Even number of Track :: Low value of maxIter"
    },
    {
        STATIC,
        4,
        {track_1,track_2,track_3,track_4},
        camExtPrm,
        {3,4,5,6},
        1,
        {out3DPoint_1_3,out3DPoint_2_3,out3DPoint_3_3,out3DPoint_4_3},
        0x1,
        "Even number of Track :: Low value of maxIter with high precision"
    }
};
/*
 *  Sends the test parameter structure and number of tests
 */
void triangulatePoints_getTestParams(triangulatePoints_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(triangulatePoints_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

