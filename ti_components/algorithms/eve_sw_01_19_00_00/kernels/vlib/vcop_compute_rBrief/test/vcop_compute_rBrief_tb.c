/*
*
* Copyright (c) 2002-2017 Texas Instruments Incorporated
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


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <vcop.h>
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_compute_rBrief_config.h"
#include "../inc/vcop_compute_rBrief_c.h"


#if VCOP_HOST_EMULATION
#include "../src_kernelC/vcop_compute_rBrief_kernel.k"    // kernel source
#else
#include "vcop_compute_rBrief_kernel.h"    
#endif

// #define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")
#define COMPARE_REFERENCE    1

/* ------------------------------------------------------------- */
/* Source image dimensions                                       */
/* ------------------------------------------------------------- */
// The minimum size of patch can be calculated as (sqrt(2) * 13)*2 +1
// This provides a patch of 39x39. We need a border of 2 in each of the
// four edges, so a patch of 43x43 is the Minimum requirement.
// The patch is extended to 48x48 to make it a multiple of 8, though true
// patch size is 47x47 (Since patch size needs to be odd).

#define MOMENTS_PATCH_SIZE (32)
#define MOMENTS_OFFSET     (MOMENTS_PATCH_SIZE  + 4)

#define PATCH_SIZE (48)
#define PATCH_SIZE_P2 (PATCH_SIZE + 2)
#define PATCH_SIZE_P5 (PATCH_SIZE + 5)

#define BYTE_OFFSET (PATCH_SIZE_P2 * 2)

#define N2         (PATCH_SIZE_P5 * PATCH_SIZE)
#define N1         (PATCH_SIZE_P5 * PATCH_SIZE_P2)
#define N3         (PATCH_SIZE    * PATCH_SIZE)

#define NUM_ITER (1)

#pragma DATA_ALIGN(moments_col_mask,32);
#pragma DATA_SECTION(moments_col_mask, "WBUF");
char moments_col_mask[MOMENTS_PATCH_SIZE*MOMENTS_PATCH_SIZE] =
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

#pragma DATA_ALIGN(moments_row_mask,32);
#pragma DATA_SECTION(moments_row_mask, "WBUF");
char moments_row_mask[MOMENTS_PATCH_SIZE*MOMENTS_PATCH_SIZE] =
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

#pragma DATA_ALIGN(moments_col_sum,32);
#pragma DATA_SECTION(moments_col_sum, "IBUFHA");
int16_t moments_col_sum[MOMENTS_PATCH_SIZE];

#pragma DATA_ALIGN(moments_row_sum,32);
//#pragma DATA_SECTION(moments_row_sum, "WBUF");
#pragma DATA_SECTION(moments_row_sum, "IBUFLA");
int16_t moments_row_sum[MOMENTS_PATCH_SIZE];

#pragma DATA_ALIGN(moments_m10,32);
//#pragma DATA_SECTION(moments_m10, "IBUFHA");
#pragma DATA_SECTION(moments_m10, "IBUFLA");
int16_t moments_m10[1];

#pragma DATA_ALIGN(moments_m01,32);
//#pragma DATA_SECTION(moments_m01, "IBUFHA");
#pragma DATA_SECTION(moments_m01, "WBUF");
int16_t moments_m01[1];

#pragma DATA_ALIGN(arctan_xthr,32);
//#pragma DATA_SECTION(arctan_xthr, "WBUF");
#pragma DATA_SECTION(arctan_xthr, "IBUFHA");
uint16_t arctan_xthr[8] = {0, 54, 114, 186, 284, 443, 788, 2436};

#pragma DATA_ALIGN(arctan_pack_decision,32);
//#pragma DATA_SECTION(arctan_pack_decision, "IBUFLA");
#pragma DATA_SECTION(arctan_pack_decision, "IBUFHA");
uint8_t arctan_pack_decision[8];

#pragma DATA_ALIGN    (brief_descriptor_external,32)
#pragma DATA_SECTION  (brief_descriptor_external, "DST_MEM")
uint8_t brief_descriptor_external[64];

#pragma DATA_ALIGN    (tran_offset,32)
#pragma DATA_SECTION(tran_offset,"WBUF");
uint16_t  tran_offset[8] = {0,1*BYTE_OFFSET,2*BYTE_OFFSET,3*BYTE_OFFSET,4*BYTE_OFFSET,5*BYTE_OFFSET,6*BYTE_OFFSET,7*BYTE_OFFSET};


#pragma DATA_ALIGN  (sinQ14_2,32)
#pragma DATA_SECTION(sinQ14_2,"WBUF");
int16_t  sinQ14_2[33]  = {0,
    0   ,  3406,  6663,  9630, 12175, 14188, 15582, 16294,
    3406,  6663,  9630, 12175, 14188, 15582, 16294, 16294,
    0   , -3407, -6664, -9631,-12176,-14189,-15583,-16295,
    -3407, -6664, -9631,-12176,-14189,-15583,-16295,-16295
};

#pragma DATA_ALIGN  (cosQ14_2,32)
//#pragma DATA_SECTION(cosQ14_2,"WBUF");
#pragma DATA_SECTION(cosQ14_2,"IBUFLA");
int16_t  cosQ14_2[33]  = {0,
    16384, 16025, 14967, 13254, 10963,  8192,  5062,  1712,
    -16025,-14967,-13254,-10963, -8192, -5062, -1712,  1712,
    -16384,-16025,-14967,-13254,-10963, -8192, -5062, -1712,
    16025, 14967, 13254, 10963,  8192,  5062,  1712, -1712
};


/* The below are for storing the selected sin/cos */
#pragma DATA_ALIGN  (sin_pt,32)
#pragma DATA_SECTION(sin_pt,"IBUFLA");
int16_t  sin_pt[32];

#pragma DATA_ALIGN  (cos_pt,32)
#pragma DATA_SECTION(cos_pt,"WBUF");
int16_t  cos_pt[32];


#pragma DATA_ALIGN   (input_image_blk_ping, 32);
#pragma DATA_SECTION (input_image_blk_ping, "IBUFLA");
uint8_t input_image_blk_ping[N2] ;

#pragma DATA_ALIGN   (input_image_blk_pong, 32);
#pragma DATA_SECTION (input_image_blk_pong, "IBUFLB");
uint8_t input_image_blk_pong[N2] ;

#pragma DATA_ALIGN  (col_sum, 32);
#pragma DATA_SECTION(col_sum, "IBUFHA");
int16_t col_sum[N1];

#pragma DATA_ALIGN(row_col_sum,32);
#pragma DATA_SECTION(row_col_sum, "WBUF");
int16_t row_col_sum[N3*2]; // For 2 copy of tables


// x,y src and dst pairs (256 pairs)
#pragma DATA_ALIGN  (zero_src_dst_x,32);
#pragma DATA_SECTION(zero_src_dst_x,"IBUFHA");
char zero_src_dst_x[512];
char zero_src_dst_x_i[512];

#pragma DATA_ALIGN  (zero_src_dst_y,32);
#pragma DATA_SECTION(zero_src_dst_y, "IBUFHA");
char zero_src_dst_y[512];
char zero_src_dst_y_i[512];

char orig_src_dst[1024] =
{
    8,-3, 9,5,
    4,2, 7,-12,
    -11,9, -8,2,
    7,-12, 12,-13,
    2,-13, 2,12,
    1,-7, 1,6,
    -2,-10, -2,-4,
    -13,-13, -11,-8,
    -13,-3, -12,-9,
    10,4, 11,9,
    -13,-8, -8,-9,
    -11,7, -9,12,
    7,7, 12,6,
    -4,-5, -3,0,
    -13,2, -12,-3,
    -9,0, -7,5,
    12,-6, 12,-1,
    -3,6, -2,12,
    -6,-13, -4,-8,
    11,-13, 12,-8,
    4,7, 5,1,
    5,-3, 10,-3,
    3,-7, 6,12,
    -8,-7, -6,-2,
    -2,11, -1,-10,
    -13,12, -8,10,
    -7,3, -5,-3,
    -4,2, -3,7,
    -10,-12, -6,11,
    5,-12, 6,-7,
    5,-6, 7,-1,
    1,0, 4,-5,
    9,11, 11,-13,
    4,7, 4,12,
    2,-1, 4,4,
    -4,-12, -2,7,
    -8,-5, -7,-10,
    4,11, 9,12,
    0,-8, 1,-13,
    -13,-2, -8,2,
    -3,-2, -2,3,
    -6,9, -4,-9,
    8,12, 10,7,
    0,9, 1,3,
    7,-5, 11,-10,
    -13,-6, -11,0,
    10,7, 12,1,
    -6,-3, -6,12,
    10,-9, 12,-4,
    -13,8, -8,-12,
    -13,0, -8,-4,
    3,3, 7,8,
    5,7, 10,-7,
    -1,7, 1,-12,
    3,-10, 5,6,
    2,-4, 3,-10,
    -13,0, -13,5,
    -13,-7, -12,12,
    -13,3, -11,8,
    -7,12, -4,7,
    6,-10, 12,8,
    -9,-1, -7,-6,
    -2,-5, 0,12,
    -12,5, -7,5,
    3,-10, 8,-13,
    -7,-7, -4,5,
    -3,-2, -1,-7,
    2,9, 5,-11,
    -11,-13, -5,-13,
    -1,6, 0,-1,
    5,-3, 5,2,
    -4,-13, -4,12,
    -9,-6, -9,6,
    -12,-10, -8,-4,
    10,2, 12,-3,
    7,12, 12,12,
    -7,-13, -6,5,
    -4,9, -3,4,
    7,-1, 12,2,
    -7,6, -5,1,
    -13,11, -12,5,
    -3,7, -2,-6,
    7,-8, 12,-7,
    -13,-7, -11,-12,
    1,-3, 12,12,
    2,-6, 3,0,
    -4,3, -2,-13,
    -1,-13, 1,9,
    7,1, 8,-6,
    1,-1, 3,12,
    9,1, 12,6,
    -1,-9, -1,3,
    -13,-13, -10,5,
    7,7, 10,12,
    12,-5, 12,9,
    6,3, 7,11,
    5,-13, 6,10,
    2,-12, 2,3,
    3,8, 4,-6,
    2,6, 12,-13,
    9,-12, 10,3,
    -8,4, -7,9,
    -11,12, -4,-6,
    1,12, 2,-8,
    6,-9, 7,-4,
    2,3, 3,-2,
    6,3, 11,0,
    3,-3, 8,-8,
    7,8, 9,3,
    -11,-5, -6,-4,
    -10,11, -5,10,
    -5,-8, -3,12,
    -10,5, -9,0,
    8,-1, 12,-6,
    4,-6, 6,-11,
    -10,12, -8,7,
    4,-2, 6,7,
    -2,0, -2,12,
    -5,-8, -5,2,
    7,-6, 10,12,
    -9,-13, -8,-8,
    -5,-13, -5,-2,
    8,-8, 9,-13,
    -9,-11, -9,0,
    1,-8, 1,-2,
    7,-4, 9,1,
    -2,1, -1,-4,
    11,-6, 12,-11,
    -12,-9, -6,4,
    3,7, 7,12,
    5,5, 10,8,
    0,-4, 2,8,
    -9,12, -5,-13,
    0,7, 2,12,
    -1,2, 1,7,
    5,11, 7,-9,
    3,5, 6,-8,
    -13,-4, -8,9,
    -5,9, -3,-3,
    -4,-7, -3,-12,
    6,5, 8,0,
    -7,6, -6,12,
    -13,6, -5,-2,
    1,-10, 3,10,
    4,1, 8,-4,
    -2,-2, 2,-13,
    2,-12, 12,12,
    -2,-13, 0,-6,
    4,1, 9,3,
    -6,-10, -3,-5,
    -3,-13, -1,1,
    7,5, 12,-11,
    4,-2, 5,-7,
    -13,9, -9,-5,
    7,1, 8,6,
    7,-8, 7,6,
    -7,-4, -7,1,
    -8,11, -7,-8,
    -13,6, -12,-8,
    2,4, 3,9,
    10,-5, 12,3,
    -6,-5, -6,7,
    8,-3, 9,-8,
    2,-12, 2,8,
    -11,-2, -10,3,
    -12,-13, -7,-9,
    -11,0, -10,-5,
    5,-3, 11,8,
    -2,-13, -1,12,
    -1,-8, 0,9,
    -13,-11, -12,-5,
    -10,-2, -10,11,
    -3,9, -2,-13,
    2,-3, 3,2,
    -9,-13, -4,0,
    -4,6, -3,-10,
    -4,12, -2,-7,
    -6,-11, -4,9,
    6,-3, 6,11,
    -13,11, -5,5,
    11,11, 12,6,
    7,-5, 12,-2,
    -1,12, 0,7,
    -4,-8, -3,-2,
    -7,1, -6,7,
    -13,-12, -8,-13,
    -7,-2, -6,-8,
    -8,5, -6,-9,
    -5,-1, -4,5,
    -13,7, -8,10,
    1,5, 5,-13,
    1,0, 10,-13,
    9,12, 10,-1,
    5,-8, 10,-9,
    -1,11, 1,-13,
    -9,-3, -6,2,
    -1,-10, 1,12,
    -13,1, -8,-10,
    8,-11, 10,-6,
    2,-13, 3,-6,
    7,-13, 12,-9,
    -10,-10, -5,-7,
    -10,-8, -8,-13,
    4,-6, 8,5,
    3,12, 8,-13,
    -4,2, -3,-3,
    5,-13, 10,-12,
    4,-13, 5,-1,
    -9,9, -4,3,
    0,3, 3,-9,
    -12,1, -6,1,
    3,2, 4,-8,
    -10,-10, -10,9,
    8,-13, 12,12,
    -8,-12, -6,-5,
    2,2, 3,7,
    10,6, 11,-8,
    6,8, 8,-12,
    -7,10, -6,5,
    -3,-9, -3,9,
    -1,-13, -1,5,
    -3,-7, -3,4,
    -8,-2, -8,3,
    4,2, 12,12,
    2,-5, 3,11,
    6,-9, 11,-13,
    3,-1, 7,12,
    11,-1, 12,4,
    -3,0, -3,6,
    4,-11, 4,12,
    2,-4, 2,1,
    -10,-6, -8,1,
    -13,7, -11,1,
    -13,12, -11,-13,
    6,0, 11,-13,
    0,-1, 1,4,
    -13,3, -9,-2,
    -9,8, -6,-3,
    -13,-6, -8,-2,
    5,-9, 8,10,
    2,7, 3,-9,
    -1,-6, -1,-1,
    9,5, 11,-2,
    11,-3, 12,-8,
    3,0, 3,5,
    -1,4, 0,10,
    3,-6, 4,5,
    -13,0, -10,5,
    5,8, 12,11,
    8,9, 9,-6,
    7,-4, 8,-12,
    -10,4, -10,9,
    7,3, 12,4,
    9,-7, 10,-2,
    7,0, 12,-2,
    -1,-6, 0,-11
};


#pragma DATA_ALIGN  (rot_src_dst_x,32);
#pragma DATA_SECTION(rot_src_dst_x, "IBUFLA");
char rot_src_dst_x[512];

#pragma DATA_ALIGN  (rot_src_dst_y,32);
#pragma DATA_SECTION(rot_src_dst_y, "WBUF");
char rot_src_dst_y[512];

#pragma DATA_ALIGN  (rot_src_lin,32);
#pragma DATA_SECTION(rot_src_lin, "IBUFLA");
uint16_t rot_src_lin[256];

#pragma DATA_ALIGN  (tlu_src,32);
#pragma DATA_SECTION(tlu_src, "IBUFHA");
int16_t tlu_src[256];

#pragma DATA_ALIGN  (rot_dst_lin,32);
#pragma DATA_SECTION(rot_dst_lin, "IBUFHA");
uint16_t rot_dst_lin[256];

#pragma DATA_ALIGN  (tlu_dst,32);
#pragma DATA_SECTION(tlu_dst,"IBUFLA");
int16_t tlu_dst[256];

#pragma DATA_ALIGN  (brief_descriptor_ping, 32);
#pragma DATA_SECTION(brief_descriptor_ping, "IBUFHA");
unsigned char brief_descriptor_ping[32];

#pragma DATA_SECTION(reference, "EOutdata");
uint8_t reference[32]  = {0x0};

unsigned char desc[256];

void dst_buffers_setup()
{
    memset (input_image_blk_ping, 0x0,  sizeof(input_image_blk_ping));
    memset (input_image_blk_pong, 0x0,  sizeof(input_image_blk_pong));
    memset (brief_descriptor_ping, 0x0, sizeof(brief_descriptor_ping));
}

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '    '))
  {
    LinePtr++;
  }
  return(LinePtr);
}

void fillDefaultConfig(scompute_rBrief_Config * params)
{
    strcpy(params->inputSrc, "RND_PTRN");
    params->numIter        = NUM_ITER;
    params->writeOutput = 0;
    params->seedForRND    = 0;
}


int writeOutputFile(unsigned char * output, scompute_rBrief_Config * params, char * filename)
{
    FILE * fp;
    int k;
    fp = fopen(filename, "w+");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }

    for(k=0;k<32;k++)
    {
        fprintf(fp, "0x%x ", output[k]);
    }
    fclose(fp);

    return (0);
}

int readInputFile(void * input, unsigned short n, unsigned short w, unsigned short h, unsigned short stride, char * filename, int dataType)
{
    int i, j, k;
    FILE * fp;
    char * LinePtr;
    int status;
    int value;
    char inputLine[MAX_INPUT_LINE_SIZE];
    char inputValue[MAX_INPUT_VALUE_SIZE];

    fp = fopen(filename, "r");
    if(fp== NULL)
    {
        printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return (-1);
    }
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < h; i++)
        {
            memset(inputLine, 0, MAX_INPUT_LINE_SIZE);
            status = (int)fgets(inputLine,MAX_CONFIG_LINE_SIZE,fp);
            if ((status == EOF) || (status == 0))
            {
                printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
                return(-1);
            }
            LinePtr = inputLine;
            for(j = 0; j < w; j++)
            {
                sscanf(LinePtr, "%d",&value);
                sscanf(LinePtr, "%s",inputValue);
                if(dataType == 5)
                {
                  int * ptr = (int * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 4)
                {
                  unsigned int * ptr = (unsigned int * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 3)
                {
                  short * ptr = (short * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 2)
                {
                  unsigned short * ptr = (unsigned short * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType == 1)
                {
                  char * ptr = (char * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                else if(dataType ==0)
                {
                  unsigned char * ptr = (unsigned char * )input;
                  ptr[k*stride*h+i*stride+j] = value;
                }
                LinePtr = moveToNextElement(inputValue,LinePtr);
            }
        }
    }
  fclose(fp);
  return(0);
}

static void CreateRandPatternU8(unsigned char *p, unsigned short h, unsigned short stride)
{
    int i, j;

#ifdef __DEBUG
    printf("Input Block:\n");
#endif

    for(i = 0; i < h; i++)
    {
        for(j = 0; j < stride; j++)
        {
            input_image_blk_ping[i*stride + j] = (rand() & 0xFF);
#ifdef __DEBUG
            printf("%4d, ",  input_image_blk_ping[i*stride + j]);
#endif
        }
#ifdef __DEBUG
          printf("\n");
#endif
      }
}

void test_compute_rBrief_c_reference()
{
    int i, j;

    char refFile[MAX_FILE_NAME_SIZE] = "..\\testvecs\\reference\\ref_out.txt";
    char inFile[MAX_FILE_NAME_SIZE] = "..\\testvecs\\input\\input_image.txt";

    readInputFile(input_image_blk_ping, 1, PATCH_SIZE, PATCH_SIZE_P5, PATCH_SIZE, inFile, 0);

    /* Column Sum Needs to be initialized to zero */
    // Optimize later to initialize only first 5 rows
    for (i=0; i<PATCH_SIZE_P5; i++) {
        for (j=0; j< PATCH_SIZE_P2; j ++) {
            col_sum[i*PATCH_SIZE_P2 + j] = 0;
        }
    }

    // Arrange for src and dst coordinates sequentially
    for (i=0; i<256; i++) {
        zero_src_dst_x_i [i] = orig_src_dst[4*i];
        zero_src_dst_y_i [i] = orig_src_dst[4*i +1 ];
        zero_src_dst_x_i [256 +i] = orig_src_dst[4*i + 2];
        zero_src_dst_y_i [256 +i] = orig_src_dst[4*i + 3];
    }

    /* Align the coordinates with DSP Implementation       */
    /* Each Byte Needs to be reversed so the cooresponding */
    /* Coordinates are reversed to get the same effect     */
    for (i=0; i<32; i++) {
        for (j=0; j<8; j++) {
            zero_src_dst_x [i*8 +j] = zero_src_dst_x_i[i*8 +7-j];
            zero_src_dst_y [i*8 +j] = zero_src_dst_y_i[i*8 +7-j];
            zero_src_dst_x [256 + i*8 +j] = zero_src_dst_x_i[256 + i*8 +7-j];
            zero_src_dst_y [256 + i*8 +j] = zero_src_dst_y_i[256 + i*8 +7-j];
        }; // j
    }; // i


    compute_Orb(
            input_image_blk_ping,
            moments_col_mask,
            moments_row_mask,
            zero_src_dst_x,
            zero_src_dst_y,
            cosQ14_2,
            sinQ14_2,
            arctan_xthr,
            desc);

    readInputFile(reference, 1, 32, 1, 32, refFile, 0);

    for (i = 0; i < 32; ++i)
     {
         if (reference[i] != desc[i])
         {
             printf("ERROR: \nC output[%d] = %x\nExpected output[%d] = %x\n", i, desc[i], i, reference[i]);
         }
     }

}


int test_compute_rBrief_vcop(scompute_rBrief_Config * params)
{
    int i, j, iter;
    int fail = 0;

    printf("\nvcop_compute_rBrief:\n");

    profiler_init();

    dst_buffers_setup();


    if(strcmp(params->inputSrc, "RND_PTRN") == 0)
    {
        printf("Pattern generation Seed = %d\n", params->seedForRND);
        srand(params->seedForRND);
        CreateRandPatternU8(input_image_blk_ping, PATCH_SIZE_P5, PATCH_SIZE);
    }
    else if(strcmp(params->inputSrc, "TXT_FILE") == 0)
    {
        readInputFile(input_image_blk_ping, 1, PATCH_SIZE, PATCH_SIZE_P5, PATCH_SIZE, params->inFileName, 0);
    }

    /* Column Sum Needs to be initialized to zero */
    // Optimize later to initialize only first 5 rows
    for (i=0; i<PATCH_SIZE_P5; i++) {
        for (j=0; j< PATCH_SIZE_P2; j ++) {
            col_sum[i*PATCH_SIZE_P2 + j] = 0;
        }
    }

    // Arrange for src and dst coordinates sequentially
    for (i=0; i<256; i++) {
        zero_src_dst_x_i [i] = orig_src_dst[4*i];
        zero_src_dst_y_i [i] = orig_src_dst[4*i +1 ];
        zero_src_dst_x_i [256 +i] = orig_src_dst[4*i + 2];
        zero_src_dst_y_i [256 +i] = orig_src_dst[4*i + 3];
    }

    /* Align the coordinates with DSP Implementation       */
    /* Each Byte Needs to be reversed so the cooresponding */
    /* Coordinates are reversed to get the same effect     */
    for (i=0; i<32; i++) {
        for (j=0; j<8; j++) {
            zero_src_dst_x [i*8 +j] = zero_src_dst_x_i[i*8 +7-j];
            zero_src_dst_y [i*8 +j] = zero_src_dst_y_i[i*8 +7-j];
            zero_src_dst_x [256 + i*8 +j] = zero_src_dst_x_i[256 + i*8 +7-j];
            zero_src_dst_y [256 + i*8 +j] = zero_src_dst_y_i[256 + i*8 +7-j];
        }; // j
    }; // i

    for(iter = 0; iter < params->numIter; iter++)
    {

        profiler_start();

        // call the kernel
        vcop_compute_rBrief(
                moments_col_mask,
                moments_col_sum,
                moments_row_mask,
                moments_row_sum,
                moments_m10,
                moments_m01,
                arctan_xthr,
                arctan_pack_decision,
                cosQ14_2,            // Ptr to cos matrix
                sinQ14_2,            // Ptr to sin matrix
                tran_offset,         // Ptr containing offsets (Increments of 34)
                cos_pt     ,
                sin_pt     ,
                input_image_blk_ping,                // input 1 data pointer
                col_sum,                       // col sum 5 row up shifted
                row_col_sum,
                zero_src_dst_x,
                zero_src_dst_y,
                rot_src_dst_x,        // Rotated src-dst matrix
                rot_src_dst_y,        // Rotated src-dst matrix
                rot_src_lin,          // Linearized  rotated src matrix
                rot_dst_lin,          // Linearized  rotated src matrix
                tlu_src,              // output  5x5 tlu src
                tlu_dst,              // output  5x5 tlu dst
                brief_descriptor_ping);

        profiler_end();

#ifdef COMPARE_REFERENCE

        // call the natural C version //
        compute_Orb(
                input_image_blk_ping,
                moments_col_mask,
                moments_row_mask,
                zero_src_dst_x,
                zero_src_dst_y,
                cosQ14_2,
                sinQ14_2,
                arctan_xthr,
                desc);

        for (i = 0; i < 32; ++i)
        {
            if (brief_descriptor_ping[i] != desc[i])
            {
                printf("ERROR: \nC output[%d] = %x\nkernel output[%d] = %x\n", i, desc[i], i, brief_descriptor_ping[i]);
                fail = 1;
            }
        }

        printf(fail ? "FAIL\n" : "PASS\n");
#endif
    }

    profiler_deinit();

    if(params->writeOutput)
    {
        writeOutputFile(brief_descriptor_ping, params, params->outFileName);
    }

    return 0;

}

int main()
{

    FILE * fp;
    char * LinePtr;
    int status;
    int lineNum = -1;
    scompute_rBrief_Config * params;
    int config_cmd;
    char configFileName[MAX_FILE_NAME_SIZE];

    params = (scompute_rBrief_Config *)(&gConfig_compute_rBrief);

    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
        printf("Could not open config list file : %s , Running in default mode \n",CONFIG_LIST_FILE_NAME);
        fillDefaultConfig(params);
        test_compute_rBrief_vcop(params);
        return(0);
    }

    while(1)
    {
        memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
        status = (int)fgets(params->configLine,MAX_CONFIG_LINE_SIZE,fp);
        LinePtr = params->configLine;
        if ((status == EOF) || (status == 0))
            break;
        lineNum++;
        sscanf(LinePtr, "%d",&config_cmd);
        sscanf(LinePtr, "%s",params->configParam);
        if(config_cmd == 0)
        {
            printf("End of config list found !\n");
            break;
        }
        else if(config_cmd == 2)
        {
            continue;
        }
        else if(config_cmd == 1)
        {
            LinePtr = moveToNextElement(params->configParam,LinePtr);
            status  = sscanf(LinePtr, "%s",configFileName);
            printf("Processing config file %s !\n", configFileName);
            fillDefaultConfig(params);
            status = readparamfile(configFileName, &gsTokenMap_compute_rBrief[0]) ;
            if(status == -1)
            {
                printf("Parser Failed");
                return -1 ;
            }
            test_compute_rBrief_vcop(params);
        }
        else
        {
            printf(" Unsupported config list command parameter at line number : %4d !\n", lineNum);
        }
    }
    fclose(fp);
    return (0);


}



