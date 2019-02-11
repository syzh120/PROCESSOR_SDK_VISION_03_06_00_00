/*
* module name : Structure From Motion
*
* module descripton : Generates sparse 3D points from optical flow information in camera captured images
*
*/
/*
 
Copyright (c) {YEAR} Texas Instruments Incorporated
 
All rights reserved not granted herein.
 
Limited License.  
 
Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI (“TI Devices”).  No hardware patent is licensed hereunder.
 
Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution
 
Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:
 
*       No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.
 
*       any redistribution and use are licensed by TI for use only with TI Devices.
 
*       Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.
 
If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:
 
*       any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.
 
*       any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.
 
Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.
 
DISCLAIMER.
 
THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
*/
#ifndef SFM_TB_H
#define SFM_TB_H

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "math.h"
#include "xdais_types.h"


#include "xdais_types.h"
#include "sfm_ti_config.h"
#include "isfm_ti.h"

#include "ti_mem_manager.h"
#include "ti_file_io.h"
#ifdef ENABLE_PROFILE
#include "sfm_ti_alg_int.h"
#endif
#if (!HOST_EMULATION)
#include "cache.h"
#endif

#define ENABLE_TRACES 0

#define DISABLE_FILE_IO 0


#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
#endif

#ifndef __mmax
#define __mmax(x,y) (x>y)?x:y
#endif

#ifndef __mmin
#define __mmin(x,y) (x>y)?y:x
#endif


#define MAX_NUM_IN_POINTS            (20000)

#define VLIB_TRIANG_MAX_POINTS_IN_TRACK               (6)

#define FRAME_DEPTH_3D_POINT_CLOUD (1)
/*
* Maximum number of output points
*/
#define MAX_NUM_OUT_POINTS           (MAX_NUM_IN_POINTS * FRAME_DEPTH_3D_POINT_CLOUD)

#define PRINT_ERROR_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

/* Out of total 288 KB of SRAM, 128 KB is configured as cache,
6 KB as stack, hence remaining 288 - 128 - 6 = 154 is
configured as SRAM to be used by SFM algorithm
*/
#define DMEM1_SIZE (154 * 1024)

/* 16KB of L1D is configured as SRAM
*/
#define DMEM0_SIZE (16 * 1024)

#pragma DATA_SECTION (DMEM1_SCRATCH, ".dmem1");
/* This will be used for allocation of memory in DMEM1 --> L2*/
uint8_t DMEM1_SCRATCH[DMEM1_SIZE];

#pragma DATA_SECTION (DMEM0_SCRATCH, ".dmem0");
/* This will be used for allocation of memory in DMEM0 --> L1D*/
uint8_t DMEM0_SCRATCH[DMEM0_SIZE];

TIMemObject memObj_DMEM1;

TIMemObject memObj_DMEM0;

#define MAX_INPUT_BUF_SIZE (MAX_NUM_IN_POINTS*sizeof(SFM_TI_trackInfo))
#define MAX_OUTPUT_BUF_SIZE (MAX_NUM_IN_POINTS*sizeof(SFM_TI_output))
#define MAX_IMG_BUF_SIZE ((1920*1088*3)>>1)

#pragma DATA_SECTION (IN_BUF, ".fileioCached");
uint8_t IN_BUF[MAX_INPUT_BUF_SIZE];

#pragma DATA_SECTION (OUT_BUF, ".fileioCached");
uint8_t OUT_BUF[MAX_OUTPUT_BUF_SIZE];

#pragma DATA_SECTION (IMG_BUF, ".fileioCached");
uint8_t IMG_BUF[MAX_IMG_BUF_SIZE];


#define HOST_MALLOC_PACKET_SIZE (128)
#define HOST_MALLOC_TOT_PACKET  (100)

#pragma DATA_SECTION (SCRATCH_NON_CACHED, ".hostdata");
uint8_t SCRATCH_NON_CACHED[HOST_MALLOC_TOT_PACKET][HOST_MALLOC_PACKET_SIZE];

#pragma DATA_SECTION (SCRATCH_NON_CACHED, ".hostdata");
uint8_t SCRATCH_PACKET_VALIDITY[HOST_MALLOC_TOT_PACKET];

#define TRACK_DATA_FORMAT (1) // 1 binary, 0 in .txt format

#if (!DISABLE_FILE_IO)

#if (!TRACK_DATA_FORMAT)
FILE* fp_in_feat;
#else
TI_FILE * fp_in_feat;
#endif

FILE * fp_in_cam;
FILE * fp_out;
TI_FILE* fp_in1;
TI_FILE* fp_out1;
float* dist;
uint8_t* imgPtr;
#endif

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;


int32_t sfmTest(ssfm_Config * testcaseParams);
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec);
int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec);
int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs, uint16_t inNumTracks);
int32_t TestApp_ReadInBuf(uint16_t * dst,int32_t currFrameNum, char * fileName, int32_t maxTracks);

int32_t TestApp_ReadInCameraPrm(float * dstExt,
                                float * dstInt,
                                int32_t currFrameNum,
                                int32_t startFrameNum,
                                char * fileName,
                                int32_t maxFrameNum);

int32_t TestApp_WriteOutBuf(SFM_TI_output * src,int32_t currFrameNum,
                            int32_t startFrameNum,
                            char * featFileName,char* InImgFileName,
                            char* outImgFileName,int32_t maxFrameNum,
                            int32_t imgWidth, int32_t imgHeight,
                            int32_t outNumPoints);

void TestApp_WritePlyHeader(FILE* fp_out, int32_t outNumPoints);
int32_t sfmCompare(ssfm_Config * testcaseParams);
int32_t TestApp_memContamination(IALG_MemRec * memRec,int32_t numMemRec, int32_t frmIdx);
#if (!HOST_EMULATION)

void _TSC_enable();
long long _TSC_read();
void SetMAR();
void InitCache();
#define L1D_SRAM_ADDR (0x00F00000)

#define MAR148() (*(volatile uint32_t *)0x01848250)
#endif

#endif
