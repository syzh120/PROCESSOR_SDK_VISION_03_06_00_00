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
 **|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
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
#include "VLIB_imagePyramid16_idat.h"

static uint16_t    staticRefIn[16 * 8] =
{
    1208,  456,  928, 1360,   72, 1976, 1664, 1120, 1200,  480,  704,  616,   32,   48, 1296,   48,
    248, 1144, 1424,   24, 1080,  728,  432, 1232, 1544, 1288,  160, 1296, 1096, 1200, 1024, 1792,
    1712,  904,   72,  224,  424, 1688,  784, 1736, 1192, 1864, 1848, 1016,  920, 1624, 1416,  336,
    496, 1240,   24,  824, 1016,  128, 1080, 1048, 1688, 1264,   72,   16,  848, 1816, 1992, 2040,
    1208,  456,  928, 1360,   72, 1976, 1664, 1120, 1200,  480,  704,  616,   32,   48, 1296,   48,
    248, 1144, 1424,   24, 1080,  728,  432, 1232, 1544, 1288,  160, 1296, 1096, 1200, 1024, 1792,
    1712,  904,   72,  224,  424, 1688,  784, 1736, 1192, 1864, 1848, 1016,  920, 1624, 1416,  336,
    496, 1240,   24,  824, 1016,  128, 1080, 1048, 1688, 1264,   72,   16,  848, 1816, 1992, 2040
};

/* This was added to test values with a 1 in the most significant bit (if the addition uses unsigned, not signed) */
static uint16_t    staticRefInUpperRange[16 * 8] =
{
    22625, 40814, 48412, 28582, 24397, 34910, 22892, 46474, 30657, 13748, 29479, 31530, 26348, 41480, 36789, 31782,
    42605, 38657, 33183, 43768, 34153, 41076, 44320, 43792, 28650, 39916, 41716, 24607, 30004, 40278, 36862, 44289,
    19576, 24075, 44811, 22032, 21340, 28914, 11523, 42581, 24067, 38903, 38679, 45542, 23720, 22457, 31131, 35347,
    42999, 47925, 35164, 24567, 44459, 31793, 10202, 32390, 44402, 27685, 54552, 27836, 28394, 20710, 24373, 28314,
    32174, 27288, 28092, 43105, 25443, 34885, 36035, 31742, 36695, 50884, 26486, 51376, 20984, 56791, 37693, 35963,
    38582, 31853, 31834, 39808, 33022, 25396, 37537, 29704, 33094, 30831, 38902, 17869, 18010, 32189, 37004, 43653,
    33668, 29841, 46209, 27271, 21830, 29872, 22364, 46829, 24750, 27902, 28617, 43272, 37865, 39184, 38755, 34248,
    37055, 31856, 37382, 27123, 22559, 35003, 33897, 50453, 28006, 20561, 38394, 38914, 25606, 20851, 31972, 22098
};

/* expected output calculated off-line in Matlab */
static uint16_t    staticRefOut[8 * 4 + 4 * 2 + 2 * 1] =
{
    764,  934,  964, 1112, 1128,  694,  594, 1040,
    1088,  286,  814, 1162, 1502,  738, 1302, 1446,
    764,  934,  964, 1112, 1128,  694,  594, 1040,
    1088,  286,  814, 1162, 1502,  738, 1302, 1446,
    768, 1013, 1015, 1095,
    768, 1013, 1015, 1095,
    890, 1055
};

/* Expected interval image for constant array of 1s */
static uint16_t    staticRefOutOnes[16 * 4 + 8 * 2 + 4 * 1] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1
};

static imagePyramid16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOut,
           inCols, inRows
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefOut,
        16, 8
    },
    {
        CONSTANT,
        NULL, staticRefOutOnes,
        32, 8
    },
    {
        STATIC,
        staticRefInUpperRange, NULL,
        16, 8
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48
    },
    {
        RANDOM,
        NULL, NULL,
        104, 56
    },
    {
        RANDOM,
        NULL, NULL,
        112, 64
    },
    {
        RANDOM,
        NULL, NULL,
        320, 160
    },
    {
        RANDOM,
        NULL, NULL,
        640, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void imagePyramid16_getTestParams(imagePyramid16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(imagePyramid16_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

