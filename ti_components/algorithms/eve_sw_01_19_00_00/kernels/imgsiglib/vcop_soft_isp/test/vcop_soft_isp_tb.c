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


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vcop.h"
#include "eve_profile.h"
#include "configparser.h"
#include "vcop_soft_isp_config.h"

/* ------------------------------------------------------------------------ */
/*  Include prototype for the "C" implementation of SOFT ISP functions      */
/* ------------------------------------------------------------------------ */
#include "vcop_soft_isp_cn.h"

#if VCOP_HOST_EMULATION
  #include "..\src_kernelC\vcop_soft_isp_kernel.k" // kernel source
#else
  #include "vcop_soft_isp_kernel.h"
#endif

//#define __DEBUG

#define MAX_IMG_WIDTH  (64)
#define MAX_IMG_HEIGHT (60)

#define MAX_IN_IMG_WIDTH  (MAX_IMG_WIDTH + 4)
#define MAX_IN_IMG_HEIGHT (MAX_IMG_HEIGHT + 4)

#pragma DATA_SECTION(IN_RC, "Adata");
uint16_t IN_RC[MAX_IN_IMG_HEIGHT*MAX_IN_IMG_WIDTH/2] = {0};

#pragma DATA_SECTION(IN_CC, "Bdata");
uint16_t IN_CC[MAX_IN_IMG_HEIGHT*MAX_IN_IMG_WIDTH/2] = {0};

#pragma DATA_ALIGN(TEMP_A, 32);
#pragma DATA_SECTION(TEMP_A, "Adata");
uint16_t TEMP_A[MAX_IN_IMG_HEIGHT*MAX_IN_IMG_WIDTH/2] = {0};

#pragma DATA_ALIGN(TEMP_B, 32);
#pragma DATA_SECTION(TEMP_B, "Bdata");
uint16_t TEMP_B[MAX_IN_IMG_HEIGHT*MAX_IN_IMG_WIDTH/2] = {0};

#pragma DATA_ALIGN(SUM_C1, 32);
#pragma DATA_SECTION(SUM_C1, "Cdata");
uint16_t SUM_C1[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(SUM_C2, 32);
#pragma DATA_SECTION(SUM_C2, "Cdata");
uint16_t SUM_C2[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(MED, 32);
#pragma DATA_SECTION(MED, "Cdata");
uint16_t MED[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(LOW, 32);
#pragma DATA_SECTION(LOW, "Cdata");
uint16_t LOW[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(HIGH, 32);
#pragma DATA_SECTION(HIGH, "Adata");
uint16_t HIGH[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(EDGE_FLAG, 32);
#pragma DATA_SECTION(EDGE_FLAG, "Bdata");
uint8_t EDGE_FLAG[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(STRIP_FLAG, 32);
#pragma DATA_SECTION(STRIP_FLAG, "Bdata");
uint8_t STRIP_FLAG[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(C1_FLAG, 32);
#pragma DATA_SECTION(C1_FLAG, "Bdata");
uint8_t C1_FLAG[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(C2_FLAG, 32);
#pragma DATA_SECTION(C2_FLAG, "Bdata");
uint8_t C2_FLAG[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(OV, 32);
#pragma DATA_SECTION(OV, "Cdata");
uint16_t OV[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(OH, 32);
#pragma DATA_SECTION(OH, "Cdata");
uint16_t OH[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(FLAG_VERT, 32);
#pragma DATA_SECTION(FLAG_VERT, "Cdata");
uint8_t FLAG_VERT[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(FLAG_HORZ, 32);
#pragma DATA_SECTION(FLAG_HORZ, "Adata");
uint8_t FLAG_HORZ[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(GBCE_TONE_CURVE, 32);
#pragma DATA_SECTION(GBCE_TONE_CURVE, "Cdata");
uint8_t GBCE_TONE_CURVE[4096*4] = {0};

#pragma DATA_ALIGN(GBCE_TONE_CURVE_DDR, 32);
#pragma DATA_SECTION(GBCE_TONE_CURVE_DDR, "Eoutdata");
uint8_t GBCE_TONE_CURVE_DDR[4096] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 38, 38, 38, 38, 39, 39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 41, 42, 42, 42, 42, 43, 43, 43, 43, 44, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 57, 57, 58, 58, 58, 58, 59, 59, 59, 59, 60, 60, 60, 60, 61, 61, 61, 61, 61, 62, 62, 62, 62, 63, 63, 63, 63, 64, 64, 64, 64, 65, 65, 65, 65, 65, 66, 66, 66, 66, 67, 67, 67, 67, 68, 68, 68, 68, 68, 69, 69, 69, 69, 70, 70, 70, 70, 71, 71, 71, 71, 71, 72, 72, 72, 72, 73, 73, 73, 73, 73, 74, 74, 74, 74, 75, 75, 75, 75, 76, 76, 76, 76, 76, 77, 77, 77, 77, 78, 78, 78, 78, 78, 79, 79, 79, 79, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 82, 82, 82, 82, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 87, 87, 87, 87, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 100, 100, 100, 100, 101, 101, 101, 101, 101, 102, 102, 102, 102, 102, 103, 103, 103, 103, 104, 104, 104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 106, 106, 107, 107, 107, 107, 108, 108, 108, 108, 108, 109, 109, 109, 109, 110, 110, 110, 110, 110, 111, 111, 111, 111, 112, 112, 112, 112, 113, 113, 113, 113, 113, 114, 114, 114, 114, 115, 115, 115, 115, 116, 116, 116, 116, 116, 117, 117, 117, 117, 118, 118, 118, 118, 119, 119, 119, 119, 119, 120, 120, 120, 120, 121, 121, 121, 121, 122, 122, 122, 122, 123, 123, 123, 123, 124, 124, 124, 124, 124, 125, 125, 125, 125, 126, 126, 126, 126, 127, 127, 127, 127, 128, 128, 128, 128, 129, 129, 129, 129, 129, 130, 130, 130, 130, 131, 131, 131, 131, 132, 132, 132, 132, 133, 133, 133, 133, 134, 134, 134, 134, 135, 135, 135, 135, 135, 136, 136, 136, 136, 137, 137, 137, 137, 138, 138, 138, 138, 139, 139, 139, 139, 140, 140, 140, 140, 140, 141, 141, 141, 141, 142, 142, 142, 142, 143, 143, 143, 143, 144, 144, 144, 144, 144, 145, 145, 145, 145, 146, 146, 146, 146, 147, 147, 147, 147, 148, 148, 148, 148, 148, 149, 149, 149, 149, 150, 150, 150, 150, 151, 151, 151, 151, 151, 152, 152, 152, 152, 153, 153, 153, 153, 153, 154, 154, 154, 154, 155, 155, 155, 155, 156, 156, 156, 156, 156, 157, 157, 157, 157, 158, 158, 158, 158, 158, 159, 159, 159, 159, 159, 160, 160, 160, 160, 161, 161, 161, 161, 161, 162, 162, 162, 162, 162, 163, 163, 163, 163, 164, 164, 164, 164, 164, 165, 165, 165, 165, 165, 166, 166, 166, 166, 166, 167, 167, 167, 167, 167, 168, 168, 168, 168, 168, 169, 169, 169, 169, 169, 170, 170, 170, 170, 170, 171, 171, 171, 171, 171, 172, 172, 172, 172, 172, 172, 173, 173, 173, 173, 173, 174, 174, 174, 174, 174, 175, 175, 175, 175, 175, 175, 176, 176, 176, 176, 176, 176, 177, 177, 177, 177, 177, 177, 178, 178, 178, 178, 178, 179, 179, 179, 179, 179, 179, 179, 180, 180, 180, 180, 180, 180, 181, 181, 181, 181, 181, 181, 182, 182, 182, 182, 182, 182, 182, 183, 183, 183, 183, 183, 183, 183, 184, 184, 184, 184, 184, 184, 184, 185, 185, 185, 185, 185, 185, 185, 186, 186, 186, 186, 186, 186, 186, 186, 187, 187, 187, 187, 187, 187, 187, 187, 188, 188, 188, 188, 188, 188, 188, 188, 188, 189, 189, 189, 189, 189, 189, 189, 189, 189, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242,
242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254};

#pragma DATA_ALIGN(GBCE_OUT_RC, 32);
#pragma DATA_SECTION(GBCE_OUT_RC, "Bdata");
uint8_t GBCE_OUT_RC[MAX_IMG_HEIGHT*MAX_IMG_WIDTH/2] = {0};

#pragma DATA_ALIGN(GBCE_OUT_CC, 32);
#pragma DATA_SECTION(GBCE_OUT_CC, "Adata");
uint8_t GBCE_OUT_CC[MAX_IMG_HEIGHT*MAX_IMG_WIDTH/2] = {0};

#pragma DATA_ALIGN(OUT_R, 32);
#pragma DATA_SECTION(OUT_R, "Bdata");
uint8_t OUT_R[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_ALIGN(STATS_SUM_PIX, 32);
#pragma DATA_SECTION(STATS_SUM_PIX, "Adata");
uint32_t STATS_SUM_PIX[8] = {0};

#pragma DATA_ALIGN(STATS_UNSAT_PIX_CNT, 32);
#pragma DATA_SECTION(STATS_UNSAT_PIX_CNT, "Bdata");
uint16_t STATS_UNSAT_PIX_CNT[8] = {0};

#pragma DATA_ALIGN(STATS_SCRATCH_C, 32);
#pragma DATA_SECTION(STATS_SCRATCH_C, "Cdata");
uint32_t STATS_SCRATCH_C[9*8] = {0};

#pragma DATA_SECTION(REF_OUT_RC, "Eoutdata");
uint16_t REF_OUT_RC[MAX_IN_IMG_HEIGHT*MAX_IN_IMG_WIDTH/2] = {0};

#pragma DATA_SECTION(REF_OUT_CC, "Eoutdata");
uint16_t REF_OUT_CC[MAX_IN_IMG_HEIGHT*MAX_IN_IMG_WIDTH/2] = {0};

#pragma DATA_SECTION(REF_GBCE_OUT_RC, "Eoutdata");
uint8_t REF_GBCE_OUT_RC[MAX_IMG_HEIGHT*MAX_IMG_WIDTH/2] = {0};

#pragma DATA_SECTION(REF_GBCE_OUT_CC, "Eoutdata");
uint8_t REF_GBCE_OUT_CC[MAX_IMG_HEIGHT*MAX_IMG_WIDTH/2] = {0};

#pragma DATA_SECTION(REF_OUT_R, "Eoutdata");
uint8_t REF_OUT_R[(MAX_IMG_HEIGHT/2)*(MAX_IMG_WIDTH/2)] = {0};

#pragma DATA_SECTION(REF_STATS, "Eoutdata");
uint8_t REF_STATS[34] = {0};

void print_2d_buf_u16(uint16_t   *buf_rc,
                      uint16_t   *buf_cc,
                      uint16_t    buf_height,
                      uint16_t    buf_width,
                      uint16_t    buf_pitch,
                      const char *str)
{
#ifdef __DEBUG
    int32_t i, j;

    printf("\n%s:\n", str);
    for(i = 0; i < buf_height/2; i++) {
        for(j = 0; j < buf_width; j++) {
            printf("%6d, ", buf_rc[i*buf_pitch + j]);
        }
        printf("\n");
        for(j = 0; j < buf_width; j++) {
            printf("%6d, ", buf_cc[i*buf_pitch + j]);
        }
        printf("\n");
    }
#endif
}


void print_2d_buf_u8(uint8_t    *buf_rc,
                     uint8_t    *buf_cc,
                     uint16_t    buf_height,
                     uint16_t    buf_width,
                     uint16_t    buf_pitch,
                     const char *str)
{
#ifdef __DEBUG
    int32_t i, j;

    printf("\n%s:\n", str);
    for(i = 0; i < buf_height/2; i++) {
        for(j = 0; j < buf_width; j++) {
            printf("%6d, ", buf_rc[i*buf_pitch + j]);
        }
        printf("\n");
        for(j = 0; j < buf_width; j++) {
            printf("%6d, ", buf_cc[i*buf_pitch + j]);
        }
        printf("\n");
    }
#endif
}


void createRndPattern(uint16_t *img_rc,
                      uint16_t *img_cc,
                      uint32_t height,
                      uint32_t width,
                      uint16_t max_val)
{
  int32_t i, j;

  for(i = 0; i < height/2; i++) {
    for(j = 0; j < width; j++) {
      img_rc[i*width + j] = rand() % (max_val + 1);
      img_cc[i*width + j] = rand() % (max_val + 1);
    }
  }
}


void fillDefaultConfig(sSoftISP_Config * params)
{
  strcpy(params->inImg, "");
#if VCOP_HOST_EMULATION
  strcpy(params->gbceToneCurve, "testvecs/input/gbceToneCurve.bin");
#else
  strcpy(params->gbceToneCurve, "../testvecs/input/gbceToneCurve.bin");
#endif
  strcpy(params->outDecompandImg, "");
  strcpy(params->outBalancedImg, "");
  strcpy(params->outRImg, "");
  strcpy(params->outCFAImg, "");
  strcpy(params->outImg, "");
  strcpy(params->outStats, "");

  params->imageWidth  = MAX_IMG_WIDTH;
  params->imageHeight = MAX_IMG_HEIGHT;
  params->imagePitch  = MAX_IMG_WIDTH;
  params->sensorBitDepth = 12;
  params->maxPixValue = 3712;

  params->enableDecompand = 1;
  params->p1 = 2048;
  params->pk = 2944;
  params->r1 = 16;
  params->r1r2 = 16;
  params->decompandShift = 0;

  params->blackClamp[0] = 0;
  params->cBalanceGain[0] = 1;

  params->blackClamp[1] = 0;
  params->cBalanceGain[1] = 1;

  params->blackClamp[2] = 0;
  params->cBalanceGain[2] = 1;

  params->blackClamp[3] = 0;
  params->cBalanceGain[3] = 1;

  params->cBalanceShift = 0;

  params->enableStats     = 0;
  params->saturationLimit = 3500;

  params->gbceMethod     = 0;

  params->randSeed    = 0;
  params->numIter     = 1;
}


int32_t main(int32_t argc, char *argv[])
{
  int32_t iter, fail, status = 0;
  uint32_t i, seed;
  FILE *fp_in = NULL, *fp_out = NULL, *fp_gbce_tc = NULL;
  char configFile[FILE_NAME_SIZE];
  uint16_t *pDecompandOut_rc, *pDecompandOut_cc;
  uint16_t *pBlackClampOut_rc, *pBlackClampOut_cc;
  uint8_t  *pScratchOut_rc, *pScratchOut_cc;
  uint16_t outStride, bufStride;
  uint8_t bitShift;
  uint32_t p2;

#ifdef __DEBUG
  uint32_t j;
#endif

  if (argc > 1)
  {
    strcpy(configFile, argv[1]);
  }
  else
  {
#if VCOP_HOST_EMULATION
    strcpy(configFile,"testvecs/config/soft_isp.cfg");
#else
    strcpy(configFile,"../testvecs/config/soft_isp.cfg");
#endif
  }

  fillDefaultConfig(&gConfig_soft_isp);
  status = readparamfile(configFile, &gsTokenMap_soft_isp[0]);
  if(status == -1)
  {
    printf("Parser Failed. Continuing with default configuration ...\n\n");
    status = 0;
  }

  /* Read the GBCE tone curve if provided */
  fp_gbce_tc = fopen((const char *)gConfig_soft_isp.gbceToneCurve, "r");
  if(fp_gbce_tc != NULL) {
    fread(GBCE_TONE_CURVE_DDR, 1, 4096, fp_gbce_tc);
  }
  else {
    printf("Using default GBCE tone curve.\n");
  }

  /* Replicate to 4 Table LUT format */
  for(i = 0; i < 4096; i++) {
    GBCE_TONE_CURVE[32*(i/8) + (i%8)] = GBCE_TONE_CURVE_DDR[i];
    GBCE_TONE_CURVE[32*(i/8) + (i%8) + 8] = GBCE_TONE_CURVE_DDR[i];
    GBCE_TONE_CURVE[32*(i/8) + (i%8) + 16] = GBCE_TONE_CURVE_DDR[i];
    GBCE_TONE_CURVE[32*(i/8) + (i%8) + 24] = GBCE_TONE_CURVE_DDR[i];
  }

  fclose(fp_gbce_tc);

  profiler_init();

  printf("Testing Software ISP kernels:\n");

  for (iter = 0; iter < gConfig_soft_isp.numIter; iter++)
  {
    printf("Iteration %d\n", iter);

    if(strcmp(gConfig_soft_isp.inImg, "")) {
      fp_in = fopen((const char *)gConfig_soft_isp.inImg, "r");
      if(fp_in == NULL) {
        printf("Failed to open input file: %s.\n", gConfig_soft_isp.inImg);
        return -1;
      }

      for(i = 0; i < gConfig_soft_isp.imageHeight/2; i++) {
        fread(IN_RC + i*gConfig_soft_isp.imagePitch, sizeof(uint16_t),
            gConfig_soft_isp.imagePitch, fp_in);
        fread(IN_CC + i*gConfig_soft_isp.imagePitch, sizeof(uint16_t),
            gConfig_soft_isp.imagePitch, fp_in);
      }
      fclose(fp_in);
    }
    else {
      seed = (gConfig_soft_isp.randSeed == 0) ? _tsc_gettime() : gConfig_soft_isp.randSeed;
      srand(seed);
      printf("Pattern Generation Seed = %d\n", seed);
      createRndPattern(IN_RC, IN_CC, gConfig_soft_isp.imageHeight,
          gConfig_soft_isp.imagePitch, gConfig_soft_isp.maxPixValue);
    }

    print_2d_buf_u16(IN_RC, IN_CC, gConfig_soft_isp.imageHeight,
        gConfig_soft_isp.imageWidth, gConfig_soft_isp.imagePitch,
        "Input image");

    outStride = 16*((gConfig_soft_isp.imageWidth + 15)/16);

    /*---------------------------------------------------------------------*/
    /* Decompanding                                                        */
    /*---------------------------------------------------------------------*/
    fail = 0;

    if(gConfig_soft_isp.enableDecompand == 1) {
      pDecompandOut_rc  = TEMP_A;
      pDecompandOut_cc  = TEMP_B;
      pBlackClampOut_rc = IN_RC;
      pBlackClampOut_cc = IN_CC;
      pScratchOut_rc    = (uint8_t *)TEMP_B;
      pScratchOut_cc    = (uint8_t *)TEMP_A;
      bufStride         = outStride;

      p2 = gConfig_soft_isp.p1 + (gConfig_soft_isp.pk - gConfig_soft_isp.p1)*gConfig_soft_isp.r1;

      profiler_start();
      vcop_decompand_piecewise_linear(IN_RC, IN_CC, pDecompandOut_rc, pDecompandOut_cc,
          gConfig_soft_isp.imageWidth, gConfig_soft_isp.imageHeight,
          gConfig_soft_isp.imagePitch, outStride, gConfig_soft_isp.p1,
          p2, gConfig_soft_isp.pk, gConfig_soft_isp.r1, gConfig_soft_isp.r1r2,
          gConfig_soft_isp.decompandShift);
      profiler_end();

      /* Compare against reference */
      vcop_decompand_piecewise_linear_cn(IN_RC, IN_CC, REF_OUT_RC, REF_OUT_CC,
          gConfig_soft_isp.imageWidth, gConfig_soft_isp.imageHeight,
          gConfig_soft_isp.imagePitch, outStride, gConfig_soft_isp.p1,
          p2, gConfig_soft_isp.pk, gConfig_soft_isp.r1, gConfig_soft_isp.r1r2,
          gConfig_soft_isp.decompandShift);

      print_2d_buf_u16(pDecompandOut_rc, pDecompandOut_cc,
          gConfig_soft_isp.imageHeight, gConfig_soft_isp.imageWidth, outStride,
          "Decompanded output");

      fp_out = fopen((const char*)gConfig_soft_isp.outDecompandImg, "w");

      for(i = 0; i < gConfig_soft_isp.imageHeight/2; i++) {
        fail |= memcmp(pDecompandOut_rc + i*outStride, REF_OUT_RC + i*outStride,
                       gConfig_soft_isp.imageWidth*sizeof(uint16_t));
        fail |= memcmp(pDecompandOut_cc + i*outStride, REF_OUT_CC + i*outStride,
                       gConfig_soft_isp.imageWidth*sizeof(uint16_t));
        if(fp_out != NULL) {
          fwrite(pDecompandOut_rc + i*outStride, sizeof(uint16_t),
              gConfig_soft_isp.imageWidth, fp_out);
          fwrite(pDecompandOut_cc + i*outStride, sizeof(uint16_t),
              gConfig_soft_isp.imageWidth, fp_out);
        }
      }
      fclose(fp_out);
      printf(fail ? "Decompanding: FAIL\n":"Decompanding: PASS\n");
      status |= fail;
    }
    else {
      pDecompandOut_rc  = IN_RC;
      pDecompandOut_cc  = IN_CC;
      pBlackClampOut_rc = TEMP_A;
      pBlackClampOut_cc = TEMP_B;
      pScratchOut_rc    = (uint8_t *)IN_CC;
      pScratchOut_cc    = (uint8_t *)IN_RC;
      bufStride         = gConfig_soft_isp.imageWidth;
    }

    /*---------------------------------------------------------------------*/
    /* Black clamp and C imbalance correction.                             */
    /*---------------------------------------------------------------------*/
    fail = 0;

    profiler_start();
    vcop_black_clamp_c_balance(pDecompandOut_rc, pDecompandOut_cc, pBlackClampOut_rc,
        pBlackClampOut_cc, gConfig_soft_isp.imageWidth, gConfig_soft_isp.imageHeight,
        bufStride, outStride, gConfig_soft_isp.blackClamp,
        gConfig_soft_isp.cBalanceGain, gConfig_soft_isp.cBalanceShift);
    profiler_end();

    /* Compare against reference */
    vcop_black_clamp_c_balance_cn(pDecompandOut_rc, pDecompandOut_cc, REF_OUT_RC,
        REF_OUT_CC, gConfig_soft_isp.imageWidth, gConfig_soft_isp.imageHeight,
        bufStride, outStride, gConfig_soft_isp.blackClamp,
        gConfig_soft_isp.cBalanceGain, gConfig_soft_isp.cBalanceShift);

    print_2d_buf_u16(pBlackClampOut_rc, pBlackClampOut_cc,
        gConfig_soft_isp.imageHeight, gConfig_soft_isp.imageWidth, outStride,
        "Black Clamp & C Balance output");

    fp_out = fopen((const char*)gConfig_soft_isp.outBalancedImg, "w");

    for(i = 0; i < gConfig_soft_isp.imageHeight/2; i++) {
      fail |= memcmp(pBlackClampOut_rc + i*outStride, REF_OUT_RC + i*outStride,
                  gConfig_soft_isp.imageWidth*sizeof(uint16_t));
      fail |= memcmp(pBlackClampOut_cc + i*outStride, REF_OUT_CC + i*outStride,
                  gConfig_soft_isp.imageWidth*sizeof(uint16_t));
      if(fp_out != NULL) {
        fwrite(pBlackClampOut_rc + i*outStride, sizeof(uint16_t),
            gConfig_soft_isp.imageWidth, fp_out);
        fwrite(pBlackClampOut_cc + i*outStride, sizeof(uint16_t),
            gConfig_soft_isp.imageWidth, fp_out);
      }
    }
    fclose(fp_out);
    printf(fail ? "C Balance: FAIL\n":"C Balance: PASS\n");
    status |= fail;

    /*---------------------------------------------------------------------*/
    /* Extract R pixels.                                                   */
    /*---------------------------------------------------------------------*/
    fail = 0;

    if(gConfig_soft_isp.enableDecompand == 0) {
      bitShift = 8;
    }
    else {
      bitShift = gConfig_soft_isp.sensorBitDepth - 8;
    }

    profiler_start();
    vcop_soft_isp_extract_r(pDecompandOut_rc + outStride + 2, OUT_R,
        gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageHeight - 4, outStride, bitShift);
    profiler_end();

    /* Compare against reference */
    vcop_soft_isp_extract_r_cn(pDecompandOut_rc + outStride + 2, REF_OUT_R,
        gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageHeight - 4, outStride, bitShift);

#ifdef __DEBUG
    printf("\nR pixel output:\n");
    for(i = 0; i < gConfig_soft_isp.imageHeight/2; i++) {
      for(j = 0; j < gConfig_soft_isp.imageWidth/2; j++) {
        printf("%8d, ", OUT_R[i*(gConfig_soft_isp.imageWidth/2) + j]);
      }
      printf("\n");
    }
#endif

    fp_out = fopen((const char*)gConfig_soft_isp.outRImg, "w");

    fail |= memcmp(OUT_R, REF_OUT_R, (gConfig_soft_isp.imageWidth - 4)*
                (gConfig_soft_isp.imageHeight - 4)*sizeof(uint8_t)/4);

    if(fp_out != NULL) {
      fwrite(OUT_R, sizeof(uint8_t), (gConfig_soft_isp.imageWidth - 4)*
                (gConfig_soft_isp.imageHeight - 4)/4, fp_out);
    }
    fclose(fp_out);
    printf(fail ? "Extract R Pixels: FAIL\n":"Extract R Pixels: PASS\n");
    status |= fail;

    if(gConfig_soft_isp.enableStats == 1) {
      /*---------------------------------------------------------------------*/
      /* Statistics Collector                                                */
      /*---------------------------------------------------------------------*/
      fail = 0;

      if(((gConfig_soft_isp.imageWidth - 4) % 16) != 0) {
        printf("Statistics Collector: Stats Width %d is not a multiple of 16.\n",
          gConfig_soft_isp.imageWidth - 4);
      }
      profiler_start();
      vcop_stats_collector_dense(pBlackClampOut_rc + outStride + 2,
          pBlackClampOut_cc + outStride + 2, STATS_SCRATCH_C, STATS_SUM_PIX, STATS_UNSAT_PIX_CNT,
          gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageHeight - 4,
          outStride, 0, gConfig_soft_isp.saturationLimit);
      profiler_end();

      vcop_stats_collector_dense_cn(pBlackClampOut_rc + outStride + 2,
          pBlackClampOut_cc + outStride + 2, REF_STATS,
          gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageHeight - 4,
          outStride, 1, gConfig_soft_isp.imageWidth - 4,
          gConfig_soft_isp.imageHeight - 4, gConfig_soft_isp.saturationLimit);

#ifdef __DEBUG
      printf("\nStatistics Collector \nSum of pixels statistics:\n");
      for(i = 0; i < 8; i++) {
          printf("%8d, ", STATS_SUM_PIX[i]);
      }
      printf("\n\nNumber of unsaturated pixels = %8d\n",
          STATS_UNSAT_PIX_CNT[0]);
#endif

      fp_out = fopen((const char*)gConfig_soft_isp.outStats, "w");

      fail |= memcmp(STATS_SUM_PIX, (uint32_t *)REF_STATS, 8*sizeof(uint32_t));
      fail |= memcmp(STATS_UNSAT_PIX_CNT, (uint16_t *)(REF_STATS + 32), sizeof(uint16_t));

      if(fp_out != NULL) {
        fwrite(STATS_SUM_PIX, sizeof(uint32_t), 8, fp_out);
        fwrite(STATS_UNSAT_PIX_CNT, sizeof(uint16_t), 1, fp_out);
      }
      fclose(fp_out);
      printf(fail ? "Statistics Collector: FAIL\n":"Statistics Collector: PASS\n");
      status |= fail;
    }

    /*---------------------------------------------------------------------*/
    /* CFA Interpolation - RCCC to CCCC conversion.                        */
    /*---------------------------------------------------------------------*/
    fail = 0;

    profiler_start();
    vcop_rccc_to_cccc(pBlackClampOut_rc, pBlackClampOut_cc,
        gConfig_soft_isp.imageWidth, gConfig_soft_isp.imageHeight, outStride,
        SUM_C1, SUM_C2, MED, LOW, HIGH, EDGE_FLAG, STRIP_FLAG,
        C1_FLAG, C2_FLAG, OV, OH, FLAG_VERT, FLAG_HORZ, 2, 0);
    profiler_end();

    vcop_rccc_to_cccc_cn(REF_OUT_RC, REF_OUT_CC, gConfig_soft_isp.imageWidth,
        gConfig_soft_isp.imageHeight, outStride, 1);

    print_2d_buf_u16(pBlackClampOut_rc, pBlackClampOut_cc,
        gConfig_soft_isp.imageHeight, gConfig_soft_isp.imageWidth, outStride,
        "CFA Interpolated output");

    //printf("CFA Interpolated output:\n");
    //for(i = 1; i < gConfig_soft_isp.imageHeight/2 - 1; i++) {
    //  for(j = 0; j < gConfig_soft_isp.imageWidth/2 - 2; j++) {
    //    printf("%6d, ", pBlackClampOut_rc[i*outStride + 2*j + 2]);
    //  }
    //  printf("\n");
    //}
    //printf("CFA Interpolated output (reference):\n");
    //for(i = 1; i < gConfig_soft_isp.imageHeight/2 - 1; i++) {
    //  for(j = 0; j < gConfig_soft_isp.imageWidth/2 - 2; j++) {
    //    printf("%6d, ", REF_OUT_RC[i*outStride + 2*j + 2]);
    //  }
    //  printf("\n");
    //}

    fp_out = fopen((const char*)gConfig_soft_isp.outCFAImg, "w");

    for(i = 1; i < gConfig_soft_isp.imageHeight/2 - 1; i++) {
      fail |= memcmp(pBlackClampOut_rc + i*outStride + 2,
                  REF_OUT_RC + i*outStride + 2,
                  (gConfig_soft_isp.imageWidth - 4)*sizeof(uint16_t));
      fail |= memcmp(pBlackClampOut_cc + i*outStride + 2,
                  REF_OUT_CC + i*outStride + 2,
                  (gConfig_soft_isp.imageWidth - 4)*sizeof(uint16_t));
      if(fp_out != NULL) {
        fwrite(pBlackClampOut_rc + i*outStride, sizeof(uint16_t),
            gConfig_soft_isp.imageWidth, fp_out);
        fwrite(pBlackClampOut_cc + i*outStride, sizeof(uint16_t),
            gConfig_soft_isp.imageWidth, fp_out);
      }
    }
    fclose(fp_out);
    printf(fail ? "CFA Interpolation: FAIL\n":"CFA Interpolation: PASS\n");
    status |= fail;

    /*---------------------------------------------------------------------*/
    /* Global Brightness and Contrast Enhancement (GBCE).                  */
    /*---------------------------------------------------------------------*/
    fail = 0;

    if(gConfig_soft_isp.enableDecompand == 1) {
      bitShift = 4;
    }
    else {
      bitShift = (gConfig_soft_isp.sensorBitDepth > 12) ? (gConfig_soft_isp.sensorBitDepth - 12): 0;
    }
    if(gConfig_soft_isp.sensorBitDepth > 16) {
      printf("Unsupported sensor Bitdepth (%d).\n",
          gConfig_soft_isp.sensorBitDepth);
      fail = 1;
      goto EXIT;
    }

    if(gConfig_soft_isp.gbceMethod == GBCE_SIMPLE) {
      profiler_start();
      vcop_gbce_simple(pBlackClampOut_rc + outStride + 2,
          pBlackClampOut_cc + outStride + 2, GBCE_OUT_RC, GBCE_OUT_CC,
          gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageHeight - 4,
          outStride, bitShift, GBCE_TONE_CURVE);
      profiler_end();

      vcop_gbce_simple_cn(pBlackClampOut_rc + outStride + 2,
          pBlackClampOut_cc + outStride + 2, REF_GBCE_OUT_RC, REF_GBCE_OUT_CC,
          gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageHeight - 4,
          outStride, bitShift, GBCE_TONE_CURVE);
    }
    else {
      profiler_start();
      vcop_gbce_interp(pBlackClampOut_rc + outStride + 2,
          pBlackClampOut_cc + outStride + 2, pScratchOut_rc, pScratchOut_cc,
          GBCE_OUT_RC, GBCE_OUT_CC, gConfig_soft_isp.imageWidth - 4,
          gConfig_soft_isp.imageHeight - 4, outStride, bitShift,
          ((1 << bitShift) - 1), GBCE_TONE_CURVE);
      profiler_end();

      vcop_gbce_interp_cn(pBlackClampOut_rc + outStride + 2,
          pBlackClampOut_cc + outStride + 2, REF_GBCE_OUT_RC, REF_GBCE_OUT_CC,
          gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageHeight - 4,
          outStride, bitShift, ((1 << bitShift) - 1), GBCE_TONE_CURVE);
    }

    print_2d_buf_u8(GBCE_OUT_RC, GBCE_OUT_CC, gConfig_soft_isp.imageHeight - 4,
        gConfig_soft_isp.imageWidth - 4, gConfig_soft_isp.imageWidth - 4,
        "GBCE output");

    fp_out = fopen((const char*)gConfig_soft_isp.outImg, "w");

    for(i = 0; i < gConfig_soft_isp.imageHeight/2 - 2; i++) {
      fail |= memcmp(GBCE_OUT_RC + i*(gConfig_soft_isp.imageWidth - 4),
                  REF_GBCE_OUT_RC + i*(gConfig_soft_isp.imageWidth - 4),
                  gConfig_soft_isp.imageWidth - 4);
      fail |= memcmp(GBCE_OUT_CC + i*(gConfig_soft_isp.imageWidth - 4),
                  REF_GBCE_OUT_CC + i*(gConfig_soft_isp.imageWidth - 4),
                  gConfig_soft_isp.imageWidth - 4);
      if(fp_out != NULL) {
        fwrite(GBCE_OUT_RC + i*(gConfig_soft_isp.imageWidth - 4), 1,
            gConfig_soft_isp.imageWidth - 4, fp_out);
        fwrite(GBCE_OUT_CC + i*(gConfig_soft_isp.imageWidth - 4), 1,
            gConfig_soft_isp.imageWidth - 4, fp_out);
      }
    }
    fclose(fp_out);
    printf(fail ? "GBCE (Method %d): FAIL\n":"GBCE (Method %d): PASS\n",
        gConfig_soft_isp.gbceMethod);
    status |= fail;

EXIT:
    status |= fail;
  }

  printf(status ? "\nFAIL\n" : "\nPASS\n");

  return (status);
}
