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
#include "VLIB_normalFlow_16_idat.h"

/* Input Arrays */
/* Image difference array */
static int16_t    imDiff[] =
{
    -22,    -29,    -30,    -24,    -24,    -29,    -38,    -32,
    117,    119,    121,    127,    128,    128,    130,    138,
    114,     65,     94,    110,     95,    100,     95,     98,
    -39,    -22,      0,      0,    -22,      0,      0,    -24,
    0,     36,     36,      0,      0,      0,      0,      0,
    0,      0,      0,      0,      0,      0,      0,      0,
    0,      0,      0,    -28,      0,      0,      0,      0,
    0,      0,      0,    -29,      0,    -21,      0,      0
};

/* Gradient magnitude array */
static int16_t    Emag[] =
{
    101,    105,    110,    114,    116,    124,    132,    133,
    181,    174,    187,    196,    195,    202,    210,    201,
    38,     15,     60,     50,     50,     53,     48,     35,
    38,     10,     59,      3,      6,     12,      9,     21,
    62,     43,     42,     13,     10,      7,      6,     19,
    19,     29,     15,     42,     17,      3,      5,      5,
    6,     33,     43,     54,     48,     18,     20,     15,
    6,     26,     50,     21,     45,      9,      5,      9
};

/* X-direction gradient array */
static int16_t    Ex[] =
{
    2,      2,     -4,     -5,      0,     10,     -1,    -13,
    8,     -1,    -19,     -3,     -2,     -3,     -5,     -3,
    28,     -6,    -46,      0,     -2,    -12,      2,     17,
    38,     -9,    -59,     -2,     -3,    -12,      9,     21,
    32,      6,    -42,    -12,     -1,     -6,      3,      8,
    16,     25,     -3,    -26,    -10,      0,     -2,      0,
    5,     33,     37,    -31,    -35,      5,     -2,     -4,
    6,     26,     50,    -19,    -45,      5,     -5,     -9
};

/* Y-direction gradient array */
static int16_t    Ey[] =
{
    -101,   -105,   -110,   -114,   -116,   -124,   -132,   -133,
    -181,   -174,   -187,   -196,   -195,   -202,   -210,   -201,
    -23,    -15,    -35,    -50,    -50,    -53,    -48,    -30,
    -6,     -5,     -1,     -2,     -6,     -3,     -1,     -7,
    -51,    -43,    -15,     -6,    -10,     -4,     -5,    -18,
    -10,    -14,     15,     31,     13,      3,      5,      5,
    3,      3,     21,     41,     29,     18,     20,     15,
    2,     -4,    -15,     -9,      5,      7,      2,     -1
};

/* Look-Up Table for values in Emag array */
static int16_t    LUT[] =
{
    0, 32767, 16383, 10922, 8191, 6553, 5461, 4681, 4095, 3640, 3276, 2978,
    2730, 2520, 2340, 2184, 2047, 1927, 1820, 1724, 1638, 1560, 1489,
    1424, 1365, 1310, 1260, 1213, 1170, 1129, 1092, 1057, 1023, 992, 963,
    936, 910, 885, 862, 840, 819, 799, 780, 762, 744, 728, 712, 697,
    682, 668, 655, 642, 630, 618, 606, 595, 585, 574, 564, 555, 546, 537,
    528, 520, 511, 504, 496, 489, 481, 474, 468, 461, 455, 448, 442,
    436, 431, 425, 420, 414, 409, 404, 399, 394, 390, 385, 381, 376, 372,
    368, 364, 360, 356, 352, 348, 344, 341, 337, 334, 330, 327, 324,
    321, 318, 315, 312, 309, 306, 303, 300, 297, 295, 292, 289, 287, 284,
    282, 280, 277, 275, 273, 270, 268, 266, 264, 262, 260, 258, 255,
    254, 252, 250, 248, 246, 244, 242, 240, 239, 237, 235, 234, 232, 230,
    229, 227, 225, 224, 222, 221, 219, 218, 217, 215, 214, 212, 211,
    210, 208, 207, 206, 204, 203, 202, 201, 199, 198, 197, 196, 195, 193,
    192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180,
    179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 168, 167,
    166, 165, 164, 163, 163, 162, 161, 160, 159, 159, 158, 157, 156,
    156, 155, 154, 153, 153, 152, 151, 151, 150, 149, 148, 148, 147, 146,
    146, 145, 144, 144, 143, 143, 142, 141, 141, 140, 140, 139, 138
};

static normalFlow_16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticImDiff, *staticEmag, *staticEx, *staticEy, *staticLUT,
           *staticOutU, *staticOutV,
           T, width, height
        },
    *********************************************/
    {
        STATIC,
        imDiff, Emag, Ex, Ey, LUT,
        NULL, NULL,
        10, 8, 8
    },
    {
        SEQUENTIAL,
        NULL, NULL, NULL, NULL, NULL,
        NULL, NULL,
        2, 32, 24
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        NULL, NULL,
        4, 40, 26
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        NULL, NULL,
        63, 96, 52
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        NULL, NULL,
        19, 128, 64
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, NULL,
        NULL, NULL,
        200, 160, 120
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void normalFlow_16_getTestParams(normalFlow_16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(normalFlow_16_testParams_t);
}

