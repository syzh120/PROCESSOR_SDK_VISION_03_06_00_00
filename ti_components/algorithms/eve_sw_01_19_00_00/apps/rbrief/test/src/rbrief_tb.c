/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/** @file rbrief_tb.c
*
*  @brief  This file contains test code for rbrief applet
*
*
*  @date   Dec 2013
*
*  Description
*    This file contains test code to validate the frame level applet rbrief Applet.
*    It also checks the output against c reference outputs and profiles the performance
*    and computes the system overheads.
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vcop.h>


#include "evestarterware.h"
#include "alg_osal.h"
#include "rbrief_config.h"
#include "xdais_types.h"
#include "irbrief_ti.h"


#include "vcop_compute_rBrief_c.h"
#include "rbrief_config.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "ti_file_io.h"

#define ENABLE_TRACES 0
#define ENABLE_PROFILE 1
#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")
#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define MOMENTS_PATCH_SIZE_INT 32
#define PATCH_SIZE (48)
#define PATCH_SIZE_P2 (PATCH_SIZE + 2) /* 50 */
#define PATCH_SIZE_P5 (PATCH_SIZE + 5) /* 53 */

#define BYTE_OFFSET (PATCH_SIZE_P2 * 2) /* 100 */

#define N2         (PATCH_SIZE_P5 * PATCH_SIZE)/* (53 * 48) */
#define N1         (PATCH_SIZE_P5 * PATCH_SIZE_P2) /* (53 * 50) */
#define N3         (PATCH_SIZE    * PATCH_SIZE) /* (48 * 48) */

extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;

const int8_t RBRIEF_TB_TI_MOMENTS_COL_MASK[MOMENTS_PATCH_SIZE_INT*MOMENTS_PATCH_SIZE_INT] =
 {     0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,-3,-2,-1, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,  0,  0,  0,  0, 0,
       0,  0,  0,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,  0,  0,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
     -15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,  0,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  0,  0, 0,
       0,  0,  0,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,  0,  0,  0, 0,
       0,  0,  0,  0,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0,-9,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0,-8,-7,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0,-6,-5,-4,-3,-2,-1, 0, 1, 2, 3, 4, 5, 6, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0,-3,-2,-1, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0,
       0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0, 0
 };


 const int8_t RBRIEF_TB_TI_MOMENTS_ROW_MASK[MOMENTS_PATCH_SIZE_INT*MOMENTS_PATCH_SIZE_INT] =
 {     0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,-15,-15,-15,-15,-15,-15,-15,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,-12,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10, 0, 0, 0, 0, 0,
       0, 0, 0,-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9,-9, 0, 0, 0, 0,
       0, 0,-8,-8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8, -8,-8,-8, 0, 0, 0,
       0, 0,-7,-7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7, -7,-7,-7, 0, 0, 0,
       0,-6,-6,-6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6, -6,-6,-6,-6, 0, 0,
       0,-5,-5,-5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5,-5,-5,-5, 0, 0,
       0,-4,-4,-4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4, -4,-4,-4,-4, 0, 0,
      -3,-3,-3,-3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3, -3,-3,-3,-3,-3, 0,
      -2,-2,-2,-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,-2,-2,-2,-2, 0,
      -1,-1,-1,-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1,-1,-1,-1, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 1, 1, 1, 1, 0,
       2, 2, 2, 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 2, 2, 2, 2, 0,
       3, 3, 3, 3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 3, 3, 3, 3, 0,
       0, 4, 4, 4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4, 4, 4, 4, 0, 0,
       0, 5, 5, 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 5, 5, 5, 0, 0,
       0, 6, 6, 6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, 6, 6, 6, 0, 0,
       0, 0, 7, 7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 7, 7, 0, 0, 0,
       0, 0, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8, 8, 8, 0, 0, 0,
       0, 0, 0, 9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9,  9, 9, 0, 0, 0, 0,
       0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15, 15, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0,
       0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0
 };

 const int16_t  RBRIEF_TB_TI_SINQ14_2[33]  = {0,
     0   ,  3406,  6663,  9630, 12175, 14188, 15582, 16294,
     3406,  6663,  9630, 12175, 14188, 15582, 16294, 16294,
     0   , -3407, -6664, -9631,-12176,-14189,-15583,-16295,
     -3407, -6664, -9631,-12176,-14189,-15583,-16295,-16295
 };

 const int16_t  RBRIEF_TB_TI_COSQ14_2[33]  = {0,
     16384, 16025, 14967, 13254, 10963,  8192,  5062,  1712,
     -16025,-14967,-13254,-10963, -8192, -5062, -1712,  1712,
     -16384,-16025,-14967,-13254,-10963, -8192, -5062, -1712,
     16025, 14967, 13254, 10963,  8192,  5062,  1712, -1712
 };

 const uint16_t RBRIEF_TB_TI_ARCTAN_XTHR[8] = {0, 54, 114,186,284,443,788,2436};

 const uint16_t  RBRIEF_TB_TI_TRAN_OFFSET[8] = {0,1*BYTE_OFFSET,2*BYTE_OFFSET,3*BYTE_OFFSET,
                                         4*BYTE_OFFSET,5*BYTE_OFFSET,6*BYTE_OFFSET,7*BYTE_OFFSET};

const int8_t orbPattern[]  = {
/* X Position of SRC */
-13,    -2,    1,    2,    7,    -11,    4,    8,    -9,    -13,    -4,    7,    -11,    -13,    10,    -13,
-8,    3,    5,    4,    11,    -6,    -3,    12,    1,    5,    5,    -10,    -4,    -7,    -13,    -2,
-13,    0,    4,    -8,    -4,    2,    4,    9,    -6,    10,    -13,    7,    0,    8,    -6,    -3,
2,    3,    -1,    5,    3,    -13,    -13,    10,    -12,    -2,    -9,    6,    -7,    -13,    -13,    -13,
-4,    5,    -1,    -11,    2,    -3,    -7,    3,    -7,    7,    -4,    -7,    7,    10,    -12,    -9,
-1,    -4,    2,    1,    -13,    7,    -3,    -13,    6,    12,    7,    -13,    -1,    9,    1,    7,
1,    -11,    -8,    9,    2,    3,    2,    5,    -5,    -10,    -11,    7,    3,    6,    2,    6,
7,    -5,    -2,    4,    -10,    4,    8,    -10,    11,    -2,    7,    1,    -9,    8,    -5,    -9,
5,    -1,    0,    -9,    0,    5,    3,    -12,    1,    -13,    -7,    6,    -4,    -5,    -13,    3,
7,    -3,    -6,    4,    -2,    2,    -2,    4,    2,    -13,    -8,    -7,    7,    7,    -13,    4,
5,    -11,    -12,    -11,    2,    8,    -6,    10,    -4,    -9,    2,    -3,    -10,    -13,    -1,    -2,
-4,    -1,    7,    11,    -13,    6,    -6,    -4,    1,    1,    -13,    -5,    -8,    -7,    -13,    -7,
2,    8,    -13,    -1,    -9,    -1,    5,    9,    4,    5,    -4,    3,    4,    -10,    -10,    7,
2,    -8,    8,    -10,    3,    -12,    0,    -9,    4,    -8,    -3,    -1,    -3,    -7,    6,    10,
-10,    2,    4,    -3,    11,    3,    6,    2,    5,    -13,    -9,    -13,    0,    6,    -13,    -13,
-13,    3,    -1,    3,    11,    9,    -1,    2,    -1,    7,    9,    7,    -10,    7,    8,    5,

/* X Position of DST */

-11,    -2,    1,    2,    12,    -8,    7,    9,    -7,    -12,    -3,    12,    -9,    -8,    11,    -12,
-6,    6,    10,    5,    12,    -4,    -2,    12,    4,    7,    6,    -6,    -3,    -5,    -8,    -1,
-8,    1,    9,    -7,    -2,    4,    4,    11,    -6,    12,    -11,    11,    1,    10,    -4,    -2,
3,    5,    1,    10,    7,    -8,    -8,    12,    -7,    0,    -7,    12,    -4,    -11,    -12,    -13,
-4,    5,    0,    -5,    5,    -1,    -4,    8,    -5,    12,    -3,    -6,    12,    12,    -8,    -9,
1,    -2,    3,    12,    -11,    12,    -2,    -12,    7,    12,    10,    -10,    -1,    12,    3,    8,
2,    -4,    -7,    10,    12,    4,    2,    6,    -3,    -5,    -6,    9,    8,    11,    3,    7,
10,    -5,    -2,    6,    -8,    6,    12,    -9,    12,    -1,    9,    1,    -9,    9,    -5,    -8,
7,    1,    2,    -5,    2,    10,    7,    -6,    3,    -5,    -6,    8,    -3,    -3,    -8,    6,
12,    -1,    -3,    9,    0,    12,    2,    8,    3,    -12,    -7,    -7,    7,    8,    -9,    5,
11,    -10,    -7,    -10,    2,    9,    -6,    12,    -3,    -4,    3,    -2,    -10,    -12,    0,    -1,
-3,    0,    12,    12,    -5,    6,    -4,    -2,    10,    5,    -8,    -4,    -6,    -6,    -8,    -6,
3,    10,    -8,    1,    -6,    1,    10,    10,    5,    10,    -3,    8,    8,    -8,    -5,    12,
3,    -6,    12,    -10,    4,    -6,    3,    -4,    12,    -8,    -3,    -1,    -3,    -6,    8,    11,
-8,    2,    4,    -3,    12,    7,    11,    3,    8,    -8,    -6,    -9,    1,    11,    -11,    -11,
-10,    4,    0,    3,    12,    11,    -1,    3,    0,    12,    10,    12,    -10,    8,    9,    12,

/* Y Position of SRC */

-13,    -10,    -7,    -13,    -12,    9,    2,    -3,    0,    2,    -5,    7,    7,    -8,    4,    -3,
-7,    -7,    -3,    7,    -13,    -13,    6,    -6,    0,    -6,    -12,    -12,    2,    3,    12,    11,
-2,    -8,    11,    -5,    -12,    -1,    7,    11,    -3,    7,    -6,    -5,    9,    12,    9,    -2,
-4,    -10,    7,    7,    3,    0,    8,    -9,    5,    -5,    -1,    -10,    12,    3,    -7,    0,
-13,    -3,    6,    -13,    9,    -2,    -7,    -10,    6,    -1,    9,    -13,    12,    2,    -10,    -6,
-13,    3,    -6,    -3,    -7,    -8,    7,    11,    3,    -5,    7,    -13,    -9,    1,    -1,    1,
12,    12,    4,    -12,    6,    8,    -12,    -13,    -8,    11,    -5,    8,    -3,    3,    3,    -9,
-6,    -8,    0,    -2,    12,    -6,    -1,    5,    -6,    1,    -4,    -8,    -11,    -8,    -13,    -13,
11,    2,    7,    12,    -4,    5,    7,    -9,    -10,    6,    6,    5,    -7,    9,    -4,    5,
5,    -13,    -10,    1,    -13,    -12,    -2,    1,    4,    6,    11,    -4,    -8,    1,    9,    -2,
-3,    0,    -13,    -2,    -12,    -3,    -5,    -5,    6,    -13,    -3,    9,    -2,    -11,    -8,    -13,
-8,    12,    -5,    11,    11,    -3,    -11,    12,    0,    5,    7,    -1,    5,    -2,    -12,    1,
-13,    -11,    1,    -10,    -3,    11,    -8,    12,    -13,    -13,    2,    12,    -6,    -8,    -10,    -13,
2,    -12,    -13,    -10,    2,    1,    3,    9,    2,    -2,    -7,    -13,    -9,    10,    8,    6,
-6,    -4,    -11,    0,    -1,    -1,    -9,    -5,    -9,    -6,    8,    3,    -1,    0,    12,    7,
0,    -6,    4,    0,    -3,    5,    -6,    7,    -6,    0,    -7,    3,    4,    -4,    9,    8,

/* Y Position of DST */
-8,    -4,    6,    12,    -13,    2,    -12,    5,    5,    -3,    0,    6,    12,    -9,    9,    -9,
-2,    12,    -3,    1,    -8,    -8,    12,    -1,    -5,    -1,    -7,    11,    7,    -3,    10,    -10,
2,    -13,    12,    -10,    7,    4,    12,    -13,    12,    1,    0,    -10,    3,    7,    -9,    3,
-10,    6,    -12,    -7,    8,    -4,    -12,    -4,    5,    12,    -6,    8,    7,    8,    12,    5,
12,    2,    -1,    -13,    -11,    -7,    5,    -13,    1,    2,    4,    5,    12,    -3,    -4,    6,
9,    -13,    0,    12,    -12,    -7,    -6,    5,    11,    9,    12,    5,    3,    6,    12,    -6,
-8,    -6,    9,    3,    -13,    -6,    3,    10,    12,    10,    -4,    3,    -8,    0,    -2,    -4,
12,    2,    12,    7,    7,    -11,    -6,    0,    -11,    -4,    1,    -2,    0,    -13,    -2,    -8,
-9,    7,    12,    -13,    8,    8,    12,    4,    10,    -2,    12,    0,    -12,    -3,    9,    -8,
-11,    1,    -5,    3,    -6,    12,    -13,    -4,    9,    -8,    -8,    1,    6,    6,    -5,    -7,
8,    -5,    -9,    3,    8,    -8,    7,    3,    -10,    0,    2,    -13,    11,    -5,    9,    12,
-2,    7,    -2,    6,    5,    11,    9,    -7,    -13,    -13,    10,    5,    -9,    -8,    -13,    7,
-6,    -6,    -10,    12,    2,    -13,    -9,    -1,    -1,    -12,    -3,    -13,    5,    -13,    -7,    -9,
7,    -5,    12,    9,    -8,    1,    -9,    3,    12,    3,    4,    5,    9,    5,    -12,    -8,
1,    1,    12,    6,    4,    12,    -13,    11,    10,    -2,    -3,    -2,    4,    -13,    -13,    1,
5,    5,    10,    5,    -8,    -2,    -1,    -9,    -11,    -2,    -2,    4,    9,    -12,    -6,    11,
0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0
} ;

#define DMEM_SIZE (15*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];

TIMemObject memObj_DMEM;
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM, memRec[i].size, memRec[i].alignment);
    }
    else {
      memRec[i].base = (Void *) malloc( memRec[i].size);
    }
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
  }
  return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if(memRec[i].space != IALG_DARAM0) {
        free(memRec[i].base);
    }
  }
  return IALG_EOK;
}
#define MAX_INPUT_LINE_SIZE 255

int32_t TestApp_readXyLevelList(const char * fileName, uint32_t *pXYList, uint8_t *pLevelList,
                                          uint16_t maxNumFeatures, uint16_t * totalFeatureCnt)
{
  uint32_t X, Y;
  uint32_t level;
  uint16_t totalFeatures = 0 ;
  int32_t status = 0;
  char inputLine[MAX_INPUT_LINE_SIZE];
  char * LinePtr;

  TI_FILE *fp = FOPEN(fileName, "r");
  if ( fp == NULL )
  {
    PRINT_ERRORE_MSG();
    status = -1;
    goto EXIT;
  }
  memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
  while (!status)
  {
    status = (int32_t)FGETS(inputLine,MAX_INPUT_LINE_SIZE,fp);
    LinePtr = inputLine;

    sscanf(LinePtr, "%d",&X);
    sscanf(LinePtr, "%d",&Y);
    sscanf(LinePtr, "%d",&level);

    pXYList[totalFeatures] = ((X << 16) | Y) ;
    pLevelList[totalFeatures] = level;
    totalFeatures++ ;
    if ( totalFeatures == maxNumFeatures)
    {
      TEST_PRINTF("Warning : total number of features is equal or greater than maxNumFeatures \
                   using maxNumFeatures as totalFeature\n");
      break;
    }
  }

  for ( X = 0 ; X < 3; X++ )
  {
    pXYList[X] = 0x00C800ae;
    pLevelList[X] = 0;
  }
  totalFeatures = X;

  FCLOSE(fp);
  *totalFeatureCnt = totalFeatures;
EXIT:
  return 0 ;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

int ComputeRBriefDesc(
    unsigned char **src,
    unsigned int   * cornerListXYIn,
    unsigned char  * cornerListLevelIn,
    char* in_src_dst_x,
    char* in_src_dst_y,
    unsigned short srcBufferPitch,
    unsigned char *orbDescOut,
    unsigned int numPoints
)
{
 unsigned int i, X, Y, XY, srcPitch, k, level;
 unsigned char *srcPtr ;
 unsigned char Patch[(PATCH_SIZE + 5)][PATCH_SIZE] ;

 for (i= 0; i < numPoints ; i++)
 {
   level = cornerListLevelIn[i];
   XY    = cornerListXYIn[i];
   X = XY >> 16 ;
   Y = XY & 0xFFFF ;

   srcPtr   = src[level] ;
   srcPitch = srcBufferPitch >> level ;
   srcPtr += (Y-23)*srcPitch + (X - 23) ;
   for(k = 0 ; k < PATCH_SIZE ; k++)
   {
     memcpy(&Patch[5+k][0], srcPtr + k*srcPitch, PATCH_SIZE);
   }

   compute_Orb((unsigned char *)Patch,
     (char *)RBRIEF_TB_TI_MOMENTS_COL_MASK, //
     (char *)RBRIEF_TB_TI_MOMENTS_ROW_MASK, //
     in_src_dst_x,
     in_src_dst_y,
     (short *)RBRIEF_TB_TI_COSQ14_2,
     (short *)RBRIEF_TB_TI_SINQ14_2,
     (unsigned short *)RBRIEF_TB_TI_ARCTAN_XTHR,
     orbDescOut + i*(256/8));

 }
  return 0;
}

int32_t rbriefTest(sRbrief_Config * testcaseParams)
{

  uint8_t *wbufToZero;
  int32_t numMemRec;
  int32_t i,j;
  IALG_MemRec *memRec;
  int32_t status;
  int32_t fail = 0;

  uint8_t *output;
  uint8_t *refOutput;

#if (ENABLE_PROFILE)
  uint64_t     profile_tsc, profile_sctm, profile_create_tsc;
#endif

  uint8_t *inputPtr;
  uint32_t sizeInput;
  uint32_t sizeOutput;
  uint32_t numBytes;
  uint32_t testcase;
  uint32_t  levelCnt;
  uint16_t  totalFeatureCnt;
  char  filepath[256];
  TI_FILE *fid;
  char  *statusStr = NULL;

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  RBRIEF_TI_CreateParams   createParams;

  IVISION_InArgs    inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   xyListBufDesc;
  IVISION_BufDesc   levelIdBufDesc;
  IVISION_BufDesc   *inBufDescList[RBRIEF_TI_BUFDESC_IN_TOTAL];

  RBRIEF_TI_OutArgs   outArgs;
  IVISION_OutBufs                  outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[RBRIEF_TI_BUFDESC_OUT_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(RBRIEF_TI_OutArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;


  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);

#if (ENABLE_PROFILE)
      profiler_init();
#endif

  for ( testcase = 0 ; testcase < rbrief_numTestCases; testcase++ )
  {

#if (ENABLE_PROFILE)
    profiler_initStack(profiler_getSP());
#endif

    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = RBRIEF_TI_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = RBRIEF_TI_BUFDESC_OUT_TOTAL;

    inBufDescList[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]   = &inBufDesc;
    inBufDescList[RBRIEF_TI_BUFDESC_IN_XY_LIST]       = &xyListBufDesc;
    inBufDescList[RBRIEF_TI_BUFDESC_IN_LEVEL_ID]      = &levelIdBufDesc;

    outBufDescList[RBRIEF_TI_BUFDESC_OUT_RBRIEF_DESC]    = &outBufDesc;
    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/

    createParams.visionParams.algParams.size   = sizeof(RBRIEF_TI_CreateParams);
    createParams.visionParams.cacheWriteBack   = NULL;
    createParams.maxNumFeatures                = testcaseParams[testcase].maxNumFeatures;
    createParams.orbPattern                    = orbPattern;
    createParams.xyListInDmem                  = 0;
    createParams.levelListInDmem               = 0;

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = RBRIEF_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = RBRIEF_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("rbrief Applet Create Done\n");
#endif
    /*-----------------------------------------------------------------
    Allocate memory for all the mem records
    Application has to implement the below function
    Refer the example implementation below in this file
    -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    /* Start measuring execution time for creation process */
#if (ENABLE_PROFILE)
      profiler_start();
#endif


    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = RBRIEF_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));


    /* Set the end point of the timing measurement for the creation process */
#if (ENABLE_PROFILE)
    profiler_end_print(0);
    profile_create_tsc = gTest_TI_profileTsc;
#endif


    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("rbrief Applet Init Done\n");
#endif

    inArgs.subFrameInfo = 0;
    inArgs.size                  = sizeof(IVISION_InArgs);

    inBufDesc.numPlanes                          = testcaseParams[testcase].numLevels;
    if ( testcaseParams[testcase].numLevels > 4 )
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
    for ( levelCnt = 0; levelCnt < inBufDesc.numPlanes ; levelCnt++)
    {
      inBufDesc.bufPlanes[levelCnt].frameROI.topLeft.x    = 0;
      inBufDesc.bufPlanes[levelCnt].frameROI.topLeft.y    = 0;
      inBufDesc.bufPlanes[levelCnt].width                 = testcaseParams[testcase].srcImagePitch[levelCnt];
      inBufDesc.bufPlanes[levelCnt].height                = testcaseParams[testcase].srcImageHeight[levelCnt];
      inBufDesc.bufPlanes[levelCnt].frameROI.width        = testcaseParams[testcase].srcImageWidth[levelCnt];
      inBufDesc.bufPlanes[levelCnt].frameROI.height       = testcaseParams[testcase].srcImageHeight[levelCnt];
      inBufDesc.bufPlanes[levelCnt].buf = (uint8_t *)malloc(inBufDesc.bufPlanes[levelCnt].width *
                                                      inBufDesc.bufPlanes[levelCnt].height);
      if(inBufDesc.bufPlanes[levelCnt].buf == NULL)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }

      if ( testcaseParams[testcase].fileBased == 1 )
      {

        sprintf(filepath, "../testvecs/input/%s", testcaseParams[testcase].inImage[levelCnt]);

        fid = FOPEN(filepath,"rb");
        if (fid == NULL) {
          PRINT_ERRORE_MSG();
          TEST_PRINTF("Error, unable to open file %s \n", filepath);
          goto EXIT_LOOP;
        }
        inputPtr = (uint8_t * )inBufDesc.bufPlanes[levelCnt].buf;
        sizeInput = inBufDesc.bufPlanes[levelCnt].frameROI.width *
                      inBufDesc.bufPlanes[levelCnt].frameROI.height;

        numBytes = FREAD(inputPtr, 1, sizeInput, fid);
        assert(numBytes== sizeInput);
        FCLOSE(fid);
      }
      else
      {
        inputPtr = (uint8_t * )inBufDesc.bufPlanes[levelCnt].buf;
        /* Create Random input data */
        for ( i = 0 ; i < testcaseParams[testcase].srcImageHeight[levelCnt]; i++)
        {
          for ( j = 0; j < testcaseParams[testcase].srcImageWidth[levelCnt]; j++)
          {
            inputPtr[j + (i*testcaseParams[testcase].srcImagePitch[levelCnt])] = rand();
          }
        }
      }
    }

    xyListBufDesc.bufPlanes[0].buf = (uint8_t *)malloc(testcaseParams[testcase].maxNumFeatures * sizeof(uint32_t));
    if(xyListBufDesc.bufPlanes[0].buf == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    levelIdBufDesc.bufPlanes[0].buf = (uint8_t *)malloc(testcaseParams[testcase].maxNumFeatures * sizeof(uint8_t));

    if(levelIdBufDesc.bufPlanes[0].buf == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    sprintf(filepath, "../testvecs/input/%s", testcaseParams[testcase].xyLevelListFile);

    status = TestApp_readXyLevelList(filepath,
                            (uint32_t *)xyListBufDesc.bufPlanes[0].buf,
                            (uint8_t *) levelIdBufDesc.bufPlanes[0].buf,
                            testcaseParams[testcase].maxNumFeatures, &totalFeatureCnt);

    if ( status != 0 )
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    xyListBufDesc.numPlanes                          = 1;
    xyListBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
    xyListBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
    xyListBufDesc.bufPlanes[0].width                 = totalFeatureCnt * sizeof(uint32_t);
    xyListBufDesc.bufPlanes[0].height                = 1;
    xyListBufDesc.bufPlanes[0].frameROI.width        = xyListBufDesc.bufPlanes[0].width;
    xyListBufDesc.bufPlanes[0].frameROI.height       = xyListBufDesc.bufPlanes[0].height;

    levelIdBufDesc.numPlanes                          = 1;
    levelIdBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
    levelIdBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
    levelIdBufDesc.bufPlanes[0].width                 = totalFeatureCnt * sizeof(uint8_t);
    levelIdBufDesc.bufPlanes[0].height                = 1;
    levelIdBufDesc.bufPlanes[0].frameROI.width        = levelIdBufDesc.bufPlanes[0].width;
    levelIdBufDesc.bufPlanes[0].frameROI.height       = levelIdBufDesc.bufPlanes[0].height;


    outBufDesc.numPlanes                          = 1;
    outBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
    outBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
    outBufDesc.bufPlanes[0].width                 = totalFeatureCnt * RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE *
                                                    sizeof(uint8_t);
    outBufDesc.bufPlanes[0].height                = 1;
    outBufDesc.bufPlanes[0].frameROI.width        = outBufDesc.bufPlanes[0].width;
    outBufDesc.bufPlanes[0].frameROI.height       = outBufDesc.bufPlanes[0].height;

    output = (uint8_t * )malloc(outBufDesc.bufPlanes[0].width * outBufDesc.bufPlanes[0].height);
    sizeOutput = outBufDesc.bufPlanes[0].width * outBufDesc.bufPlanes[0].height;
    outBufDesc.bufPlanes[0].buf = (uint8_t * )output;

    if(outBufDesc.bufPlanes[0].buf == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    memset(output, 0, sizeOutput);
    vcop_minit();
    wbufToZero= (uint8_t*)vcop_malloc(VCOP_WMEM, 31*1024);
    memset(wbufToZero, 0xcd, 31*1024);
    vcop_free(wbufToZero);

#if ENABLE_TRACES
    TEST_PRINTF("Processing start \n");
#endif
#if (ENABLE_PROFILE)
     profiler_start();
#endif


    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,&inArgs,(IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
    profiler_end_print(1);

    profile_tsc  = gTest_TI_profileTsc;
    profile_sctm = gTest_TI_profileSctm[0];
#endif



    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("Processing End\n");
#endif

    if (testcaseParams[testcase].fileBased == 1)
    {
      /* Write output files */
      sprintf(filepath, "../testvecs/output/%s", testcaseParams[testcase].outImage);
      fid= FOPEN(filepath,"wb");
      if ( fid == NULL)
      {
        TEST_PRINTF("Error, unable to open file %s \n", filepath);
        goto EXIT_LOOP;
      }
      output = (uint8_t * )outBufDesc.bufPlanes[0].buf;
      numBytes = FWRITE(output, 1, totalFeatureCnt * RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE *sizeof(uint8_t), fid);

      assert(numBytes == totalFeatureCnt * RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE *sizeof(uint8_t));
      FCLOSE(fid);
    }

    refOutput =  (uint8_t * )malloc(outBufDesc.bufPlanes[0].width * outBufDesc.bufPlanes[0].height);

    if(refOutput == NULL)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
    /* Reference C Matching */
    {

      int i;
      uint8_t *src[RBRIEF_TI_MAXLEVELS];
      uint32_t   * cornerListXYIn ;
      uint8_t  * cornerListLevelIn ;
      int8_t* in_src_dst_x ;
      int8_t* in_src_dst_y ;
      uint16_t srcBufferPitch ;
      uint8_t *orbDescOut ;
      uint32_t numPoints  ;
      int32_t topLeftX, topLeftY;
      srcBufferPitch = inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width ;

      for(i = 0 ; i < inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->numPlanes; i++)
      {
        src[i] = (uint8_t *) inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[i].buf ;
        topLeftX = inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[i].frameROI.topLeft.x ;
        topLeftY = inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[i].frameROI.topLeft.y ;
        src[i] = src[i] + topLeftX + topLeftY*srcBufferPitch ;
      }

      cornerListXYIn    = (uint32_t *)inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_XY_LIST]->bufPlanes[0].buf ;
      cornerListLevelIn = (uint8_t *)inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_LEVEL_ID]->bufPlanes[0].buf ;
      in_src_dst_x = (int8_t *)orbPattern ;
      in_src_dst_y = (int8_t *)orbPattern + 512 ;
      orbDescOut   = (uint8_t *)refOutput;
      numPoints    = inBufs.bufDesc[RBRIEF_TI_BUFDESC_IN_LEVEL_ID]->bufPlanes[0].frameROI.width ;

      ComputeRBriefDesc(
         src,
         cornerListXYIn,
         cornerListLevelIn,
         (char*)in_src_dst_x,
         (char*)in_src_dst_y,
         srcBufferPitch,
         orbDescOut,
         numPoints);
    }
    fail = 0 ;
    fail =  memcmp(refOutput, outBufDesc.bufPlanes[0].buf, totalFeatureCnt * RBRIEF_TI_FEATURE_DESCRIPTOR_SIZE);
    statusStr = fail?"FAILED":"PASSED";
    profiler_printStatus(fail);

#if (ENABLE_PROFILE)
    TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
      "Algorithm", "Status", "Width", "Height", "NumFeatures", "MegaCycPerFr", \
      "MegaCycPerSec(30Fr)", "TotalCycPerFeature", "VcopBusyCycPerFeature","TimePerFr(MSec)", "Comments");


#if (VCOP_HOST_EMULATION)
      profile_sctm = 1;
      profile_tsc = 1;
#endif

    TEST_PRINTF("%-20s %10s %10d %10d %10d %15.2f %20.2f %14.2f %17.2f %16.2f \
        Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
        "RBRIEF",statusStr,testcaseParams[testcase].srcImageWidth[0],testcaseParams[testcase].srcImageHeight[0],\
        totalFeatureCnt,(profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
        (profile_tsc)/(float)totalFeatureCnt,\
        (profile_sctm)/(float)totalFeatureCnt,\
        (profile_tsc/500000.0), (profile_create_tsc)/1000000.0);
#endif
    fflush(stdout);
EXIT_LOOP:
    status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
    }
    /* Here Free memory for all the mem records */
    status = TestApp_FreeMemRecords(memRec,numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
    }

    if ( memRec != NULL )
    {
      free(memRec);
    }

    for (levelCnt = 0 ; levelCnt < inBufDesc.numPlanes ; levelCnt++)
    {
      if ( inBufDesc.bufPlanes[levelCnt].buf  != NULL )
      {
        free(inBufDesc.bufPlanes[levelCnt].buf);
      }
    }
    if ( outBufDesc.bufPlanes[0].buf != NULL )
    {
      free(outBufDesc.bufPlanes[0].buf);
    }

    if ( xyListBufDesc.bufPlanes[0].buf  != NULL)
    {
      free(xyListBufDesc.bufPlanes[0].buf);
    }

    if ( levelIdBufDesc.bufPlanes[0].buf  != NULL)
    {
      free(levelIdBufDesc.bufPlanes[0].buf);
    }

    if ( refOutput != NULL )
    {
      free(refOutput);
    }

#if !(VCOP_HOST_EMULATION)
      profiler_getStackDepth();
#endif
  }
  return status;
}
char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '	')||(LinePtr[0] == ','))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int main(int argc, char *argv[])
{
  int status = 0;
  char configFile[FILE_NAME_SIZE]={0};
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  int8_t         *LinePtr;
  TI_FILE * fp;
  int32_t         lineNum = -1;
  int32_t         config_cmd;

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,CONFIG_LIST_FILE_NAME);
  }

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

  report_printAppletInfo((int8_t *)"RBRIEF_TI_VISION");

  while ( 1 )
  {
    memset(configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int)FGETS(configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (int8_t *)configLine;
    if ((status == EOF) || (status == 0))
    {
      break;
    }
    status = 0;
    lineNum++;
    sscanf((const char *)LinePtr, "%d",&config_cmd);
    sscanf((const char *)LinePtr, "%s",configParam);

    if(config_cmd == 0)
    {
      TEST_PRINTF("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = (int8_t *)moveToNextElement(configParam,(char *)LinePtr);
      status  = sscanf((const char *)LinePtr, "%s",configFile);
      TEST_PRINTF("\n Processing config file %s !\n", configFile);
/*      fillDefaultConfig(&gConfig_nms);*/
      status = readparamfile(configFile, &gsTokenMap_rbrief[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)gConfig_rbrief[0].testCaseName, (int8_t *)gConfig_rbrief[0].desc,
                            gConfig_rbrief[0].performanceTestcase);
      printparams(&gsTokenMap_rbrief[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_rbrief[0]),
                            sizeof(sRbrief_Config));

  /* Validate the applet */
  status = rbriefTest(gConfig_rbrief);
      if(status == -1)
      {
        return status;
      }
    }
    else
    {
      TEST_PRINTF(" Unsupported config list command parameter at line num : %4d !\n", lineNum);
    }

  }

  FCLOSE(fp);

  return status;
}



