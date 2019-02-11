/*
* module name : Ground Plane Estimation
*
* module descripton : Generates ground plane information from sparse 3D points
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
#ifndef GPE_TB_H
#define GPE_TB_H

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "xdais_types.h"
#include "gpe_ti_config.h"
#include "igpe_ti.h"
#include "ti_mem_manager.h"

#if (!HOST_EMULATION)
//#include "edma3_lld_helper.h"
#endif

#define DISABLE_FILE_IO 0
#define FILE_NAME_SIZE  200

#if (!DISABLE_FILE_IO)
FILE * fp_in_cam;
FILE * fp_in_grndPlaneEq;
FILE * fp_out;
#endif

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec, int32_t numMemRec);
int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec, int32_t numMemRec);
int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,
                               IVISION_OutBufs * outBufs, sGPE_Config * params);
int32_t TestApp_ReadInBuf(uint16_t * dst, int32_t currFrameNum, char * fileName,
                          int32_t maxTracks);
int32_t TestApp_WriteInGrndPlaneEqPrm(float *dstGrndPlaneEq,
                                     int32_t currFrameNum,
                                     int32_t startFrameNum,
                                     char *fileName, int32_t maxFrameNum,
                                     int32_t size);

int32_t TestApp_ReadInCameraPrm(float * dstExt, float * dstInt,
                                int32_t currFrameNum, int32_t startFrameNum,
                                char * fileName, int32_t maxFrameNum);

int32_t TestApp_WriteOutBufs(IVISION_OutBufs * outBufs, int32_t currFrameNum,
                             int32_t startFrameNum, char * fileName,
                             int32_t maxFrameNum);

int32_t TestApp_CompareOutPut(char * outGpeFileName, char * refGpeFileName,
                              char * compFileName, int32_t startFrameNum,
                              int32_t maxFrameNum);

#if (!HOST_EMULATION)

void _TSC_enable();
long long _TSC_read();
void SetMAR();
void InitCache();
#define L1D_SRAM_ADDR (0x00F00000)

#define MAR148() (*(volatile uint32_t *)0x01848250)
#endif

#endif /* GPE_TB_H */
