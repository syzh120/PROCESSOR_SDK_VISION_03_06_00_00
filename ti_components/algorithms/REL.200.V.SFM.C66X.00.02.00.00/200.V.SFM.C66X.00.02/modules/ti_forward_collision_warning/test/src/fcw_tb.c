/*
* module name : Forward Collision Warning
*
* module descripton : Generates distance of objects presents in scene
*
*/
/*
 
Copyright (c) 2009-2017 Texas Instruments Incorporated
 
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
/** @file fcw_tb.c
*
*  @brief  This file contains test code for forward collision warning algorithm
*
*
*  @date   October 2015
*
*  Description
*    This file contains test code to validate the frame level algorithm TI FCW
*
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <float.h>
#include <math.h>

#include "xdais_types.h"
#include "fcw_tb.h"
#include "fcw_config.h"
#include "ifcw_ti.h"
#include "ti_mem_manager.h"
#if (!HOST_EMULATION)
//#include "edma3_lld_helper.h"
#endif

#define DISABLE_FILE_IO 0

#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
#endif

#if (!HOST_EMULATION)
#include "cache.h"
#endif

#if (!HOST_EMULATION)
void _TSC_enable();
long long _TSC_read();


void SetMAR()
{

  uint32_t i ;
  /* MAR Reg  Add         Cache able Region
  * MAR 144 (0x01848240h) 9000 0000h - 90FF FFFFh
  * MAR 160 (0x01848280)  A000 0000h - A0FF FFFFh
  */
  uint32_t* MAR = (uint32_t*)0x01848000 ;

  for(i = 144 ;i <= 160 ; i++)
  {
    MAR[i] = 0x1;
  }

  for(i = 128 ;i <= 133 ; i++)
  {
    MAR[i] = 0x1;
  }

  return ;
}

void InitCache()
{
  /*--------------------------------------------------------------------------*/
  /* 7-> full,6 -> 1024KB,5 -> 512KB,4-> 256KB,3 -> 128KB,2-> 64KB,0-->0      */
  /* IMPORTANT ::Currently 160 KB of L2 is assumed to be SRAM, hence in final */
  /* application any amount L2 can be configured as SRAM, but DMVAL will not  */
  /* use that.                                                                */
  /*--------------------------------------------------------------------------*/

  *L2CFG  = 3;

  /*-------------------------------------------------------------------------*/
  /* Full L1P is configured as 32KB of cache                                 */
  /* Nothing in L1P is assumed as SRAM, so no dependency from final applicati*/
  /* -on configuration. Only thing if full L1P is configured as cache then   */
  /* standalone and application performance numbers will match.              */
  /*-------------------------------------------------------------------------*/
  *L1PCFG = 4;

  /*--------------------------------------------------------------------------*/
  /* 1 -> 4 KB, 2-> 8KB, 3 ->16 KB, 4 -> 32KB as cache                       */
  /* Currently 16KB as cache has been allocated for L1D, Rest 16 KB is configu*/
  /* red as SRAM. Any change in cache configuration should be done in conjuca*/
  /* of linker command file modification in test application                 */
  /* IMPORTANT :: Here 16 KB of L1 D is assumed as SRAM hence there is depend*/
  /* -dency from final application configuration of L1D. If atleast 16 KB of */
  /* L1D is not configured as SRAM in final application then that will be a  */
  /* functional issue.                                                       */
  /*-------------------------------------------------------------------------*/
  *L1DCFG = 3;

  SetMAR() ;
}

#endif

#define ALIGN_T0_32(x) (((x+31)/32)*32)

#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of \
                            function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM0_SIZE (16*1024)
#define DMEM1_SIZE (154*1024)

#define DDRNONCACHE_SIZE (20*1024)
#define DDRCACHE_SIZE (20*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmem0");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM0_SIZE];
TIMemObject memObj_DMEM0;

#pragma DATA_SECTION (L2MEM_SCRATCH, ".dmem1");
uint8_t L2MEM_SCRATCH[DMEM1_SIZE];
TIMemObject memObj_DMEM1;

#pragma DATA_SECTION (DDRMEM_NONCACHE, ".ddrnoncacheSect");
uint8_t DDRMEM_NONCACHE[DDRNONCACHE_SIZE];
TIMemObject memObj_DDRMEMNC;

#pragma DATA_SECTION (DDRMEM_CACHE, ".ddrcacheSect");
uint8_t DDRMEM_CACHE[DDRCACHE_SIZE];
TIMemObject memObj_DDRMEMC;

int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM1 = &memObj_DMEM1;

  TIMemHandle memHdl_DMEM0 = &memObj_DMEM0;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM1) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM1, memRec[i].size,
         memRec[i].alignment);

      if(memRec[i].base == NULL) {
        memRec[i].base = (Void *) malloc( memRec[i].size);
        memRec[i].space = IALG_EXTERNAL;
        printf("\n Internal memory could not be allocated");
      }
    }
    else if(memRec[i].space == IALG_DARAM0) {
      /*L1D SRAM space, currently alg requires 16kb SRAM and 16kb cache.
      */
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM0, memRec[i].size,
        memRec[i].alignment);

      if(memRec[i].base == NULL) {
        memRec[i].base = (Void *) malloc( memRec[i].size);
        memRec[i].space = IALG_EXTERNAL;
        printf("\n Internal memory could not be allocated");
      }

    }
    else {
      /* From heap present in external memory
      */
      memRec[i].base = (Void *) malloc( memRec[i].size);
    }
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
  }
  return IALG_EOK;
}

int32_t Inargs_memContamination(FCW_TI_InArgs   *inArgs)
{

  memset(inArgs, (int32_t) 0xFF , sizeof(FCW_TI_InArgs));
  return(0);
}

int32_t TestApp_memContamination(IALG_MemRec * memRec,int32_t numMemRec,
                                 int32_t frmIdx)
{
  int32_t i,j;
  int32_t size;
  float*  src;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].attrs == IALG_SCRATCH){

      size = memRec[i].size >> 2;
      src  = (float*)memRec[i].base;
      for(j = 0; j < size; j++)
        src[j] = FLT_MAX;
    }
    if((memRec[i].attrs == IALG_PERSIST) && (frmIdx == -1)){

      size = memRec[i].size >> 2;
      src  = (float*)memRec[i].base;
      for(j = 0; j < size; j++)
        src[j] = FLT_MAX;
    }
  }
  return(0);
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
    if(memRec[i].space == IALG_EXTERNAL){
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}


int32_t TestApp_AllocIOBuffers(IVISION_InBufs *inBufs,IVISION_OutBufs *outBufs,
                               sFCW_Config * params)
{
  TIMemHandle memHdl_EXTMEM = &memObj_DDRMEMC;
  uint32_t size;

  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->numPlanes               = 1;
  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.
                                                      topLeft.x = 0;
  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.
                                                      topLeft.y = 0;
  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].width
                                                      = sizeof(FCW_TI_OD_input);
  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].height     = 1;
  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.width
                                                      = sizeof(FCW_TI_OD_input);
  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.height
                                                      = 1;
  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].planeType  = 0;

  size = sizeof(FCW_TI_OD_input);

  /* Allocate the buffer in DDR which is non-cacheable */

  inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].buf =
                                      TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);

  if(inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].buf == NULL)
  {
    PRINT_ERRORE_MSG();
  }

  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->numPlanes               = 1;
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].frameROI.
                                                                topLeft.x  = 0;
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].frameROI.
                                                                topLeft.y  = 0;
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].width
                                                        = sizeof(FCW_TI_output);
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].height     = 1;
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].frameROI.width
                                                        = sizeof(FCW_TI_output);
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].frameROI.height
                                                        = 1;
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].planeType  = 0;

  size = sizeof(FCW_TI_output);
  /* Allocate the buffer in DDR which is non-cacheable */
  outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].buf =
                                      TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);

  if(outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].buf == NULL)
  {
    PRINT_ERRORE_MSG();
  }

  memset(outBufs->bufDesc[0]->bufPlanes[0].buf , 0,
    outBufs->bufDesc[0]->bufPlanes[0].width *
    outBufs->bufDesc[0]->bufPlanes[0].height);

  return IALG_EOK;
}

int32_t TestApp_ReadInBufs(IVISION_InBufs *inBufs,int32_t currFrameNum,
                           char * fileName)
{
  int32_t bytesRead;
  FILE * fp;
  int32_t size =
    inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].width *
    inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].height;

  fp = fopen(fileName, "rb");

  if(fp == NULL)
  {
    goto Exit;
  }

  fseek(fp, currFrameNum*size, SEEK_SET);

#if (!DISABLE_FILE_IO)
  bytesRead = fread(
    inBufs->bufDesc[FCW_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].buf,
    1, size, fp);
  if(bytesRead < size)
  {
    return (-1);
  }
#endif

  fclose(fp);

Exit:
  return (0);
}

int32_t TestApp_ReadInGrndPlaneEqPrm(float * dstgrndPlaneEq,
  int32_t currFrameNum,
  int32_t startFrameNum,
  char * fileName,
  int32_t maxFrameNum,
  int32_t size)
{
  int32_t bytesRead;
  int32_t grndPlnStartFrmNum = 1;

  if(currFrameNum < (startFrameNum + grndPlnStartFrmNum)) {
    dstgrndPlaneEq[0] = dstgrndPlaneEq[1] = dstgrndPlaneEq[2] = FLT_MAX;
    return(0);
  }

  if(currFrameNum == startFrameNum + grndPlnStartFrmNum) {
    fp_in_grndPlaneEq   = fopen(fileName, "rb");

    if(fp_in_grndPlaneEq == NULL)
      exit(0);
  }

  /**
  * In grndPlaneEq input file, first value is index of the arrary which is not
  * used in computations. That index is avoided in grndPlaneEq array.
  */
  fseek(fp_in_grndPlaneEq, (currFrameNum * (size + sizeof(float))) +
    sizeof(float), SEEK_SET);
  bytesRead = fread(dstgrndPlaneEq,1,size,fp_in_grndPlaneEq);
  if(bytesRead < size)
  {
    return (-1);
  }

  return (0);
}

int32_t TestApp_ReadInCameraPrm(float * dstExt, float * dstInt,
                                int32_t currFrameNum, int32_t startFrameNum,
                                char * fileName, int32_t maxFrameNum)
{
  int32_t i;
  char    tempStr[200];
  float   tempExtprm[4];
  int32_t extPrmSizeInRows = 4;
  int32_t intPramStartRow  = 14;
  int32_t extPramStartRow  = 28;
  int32_t ymlFileStartNo   = 0;
  int32_t modStartNo       = startFrameNum - ymlFileStartNo;

  /* Specific format for the file is assumed. If that format is not maintained
  * in the camera parameters file, then this code will fail.
  */

  if(currFrameNum == startFrameNum) {
    fp_in_cam   = fopen(fileName, "rb");

    if(fp_in_cam == NULL)
      exit(0);

#if (!DISABLE_FILE_IO)

    for(i = 0; i < intPramStartRow; i++) {
      fgets(tempStr,200,fp_in_cam);
    }
    i=0;
    do{
      i++;
    }while(tempStr[i] != '[');
    sscanf(&tempStr[i+1],"%f,%f,%f",dstInt,(dstInt+1),(dstInt +2));

    fgets(tempStr,200,fp_in_cam);
    sscanf(&tempStr[0],"%f,%f,%f",(dstInt + 3),(dstInt + 4),(dstInt + 5));

    fgets(tempStr,200,fp_in_cam);
    sscanf(&tempStr[0],"%f,%f,%f",(dstInt + 6),(dstInt + 7),(dstInt + 8));

    for(i=0; i< (extPramStartRow - intPramStartRow - 2 +
        extPrmSizeInRows * modStartNo); i++)
    {
      fgets(tempStr,200,fp_in_cam);
    }

    i=0;

    if(currFrameNum == ymlFileStartNo)
    {
      do{
        i++;
      }while(tempStr[i] != '[');
    }
#endif
  } else {
    i = -1;
    if(fgets(tempStr,200,fp_in_cam) == NULL)
    {
      return -1;
    }
  }

#if (!DISABLE_FILE_IO)

  /* First 2 bytes represents number of feature points information. Afterwards
  * ONE_FEATURE_INFO_SIZE many feature points information is placed in file.
  */
  sscanf(&tempStr[i+1],"%f,%f,%f,%f,",(dstExt + 0), (dstExt + 1),
                                      (dstExt + 2), (dstExt + 3));
  fgets(tempStr,200,fp_in_cam);
  sscanf(&tempStr[0],"%f,%f,%f,%f,",(dstExt + 4), (dstExt + 5),
                                    (dstExt + 6), (dstExt + 7));
  fgets(tempStr,200,fp_in_cam);
  sscanf(&tempStr[0],"%f,%f,%f,%f,",(dstExt + 8), (dstExt + 9),
                                    (dstExt + 10), (dstExt + 11));
  if(extPrmSizeInRows == 4){
    fgets(tempStr,200,fp_in_cam);
    sscanf(&tempStr[0],"%f,%f,%f,%f,",&tempExtprm[0], &tempExtprm[1],
                                      &tempExtprm[2], &tempExtprm[3]);
    if(tempExtprm[3] != 1.0){
      printf("\n Something wrong has happened");
      exit(0);
    }
  }

#endif

  if(currFrameNum == (maxFrameNum - 1)){
    fclose(fp_in_cam);
  }

  return (0);
}

int32_t TestApp_WriteOutBufs(IVISION_OutBufs * outBufs, int32_t currFrameNum,
                             int32_t startFrameNum, char * fileName,
                             int32_t maxFrameNum)
{
  int32_t bytesWritten;
  int32_t size =
    outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].width *
    outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].height;

  if(currFrameNum == startFrameNum) {
    fp_out   = fopen(fileName, "wb");
  }

  if(fp_out == NULL)
    exit(0);

  fseek(fp_out, currFrameNum*size, SEEK_SET);

#if (!DISABLE_FILE_IO)
  bytesWritten = fwrite(
    outBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].buf,
    1, size, fp_out);
  if(bytesWritten < size)
  {
    return (-1);
  }
#endif

  if(currFrameNum == (maxFrameNum - 1)){
    fclose(fp_out);
  }

  return (0);
}

int32_t TestApp_CompareOutBufs(IVISION_OutBufs *outputBufs,
              char * outTTCFileName, char * refTTCFileName, int32_t maxFrameNum)
{
  int32_t j, outBytesRead, refBytesRead;
  uint32_t frameIdx;
  FCW_TI_output *fcwOut;
  FCW_TI_output *fcwRef;
  FCW_TI_objectWorldInfo *outObjWorldInfo;
  FCW_TI_objectWorldInfo *refObjWorldInfo;
  FILE * fpOut;
  FILE * fpRef;
  FILE * fpCmpOut;
  char *outBuf;
  char *refBuf;

  int32_t size =
    outputBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].width *
    outputBufs->bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].height;

  outBuf = (char *) malloc(size);
  refBuf = (char *) malloc(size);

  fpOut = fopen(outTTCFileName, "rb");
  fpRef = fopen(refTTCFileName, "rb");
  fpCmpOut = fopen("..//testvecs//output//fcwcompout.txt", "w");

  if((fpOut == NULL) || (fpRef == NULL) || (fpCmpOut == NULL))
  {
    fprintf(fpCmpOut,"Error open file at TestApp_CompareOutBufs\n");
    goto Exit;
  }

  for(frameIdx = 0; frameIdx <maxFrameNum;frameIdx++)
  {
    fprintf(fpCmpOut,"\nFrame %d Info\n", frameIdx);

    fseek(fpOut, frameIdx*size, SEEK_SET);
    outBytesRead = fread(outBuf,1,size,fpOut);
    if(outBytesRead < size)
    {
      fprintf(fpCmpOut,
        "Error reading from output file at TestApp_CompareOutBufs\n");
      goto Exit;
    }

    fseek(fpRef, frameIdx*size, SEEK_SET);
    refBytesRead = fread(refBuf,1,size,fpRef);
    if(refBytesRead < size)
    {
      fprintf(fpCmpOut,
        "Error reading from reference file at TestApp_CompareOutBufs\n");
      goto Exit;
    }

    fcwOut   = (FCW_TI_output   *)outBuf;
    fcwRef   = (FCW_TI_output   *)refBuf;
    outObjWorldInfo  = &fcwOut->objWorldInfo[0];
    refObjWorldInfo  = &fcwRef->objWorldInfo[0];

    if(fcwOut->numObjects != fcwRef->numObjects)
    {
      fprintf(fpCmpOut,"ERROR numobjects mismatch Out:Ref = %d:%d\n",
                                        fcwOut->numObjects, fcwRef->numObjects);
      goto Exit;
    }

    for(j = 0; j < fcwOut->numObjects; j++)
    {
      fprintf(fpCmpOut,"ObjDist - Out:Ref\t=\t%f\t:\t%f\t\tAbsDiff = %f\n",
          outObjWorldInfo->distFrmCamera, refObjWorldInfo->distFrmCamera,
          fabs(outObjWorldInfo->distFrmCamera - refObjWorldInfo->distFrmCamera));
      fprintf(fpCmpOut,"objTag - Out:Ref\t=\t%d\t:\t%d\n", outObjWorldInfo->objTag,
                                                            refObjWorldInfo->objTag);
      if(outObjWorldInfo->objTag != refObjWorldInfo->objTag)
      {
        fprintf(fpCmpOut,"ERROR objTag mismatch\n");
        goto Exit;
      }

      outObjWorldInfo++;
      refObjWorldInfo++;
    }

  }

Exit:
  if(fpCmpOut)
  {
    fclose(fpCmpOut);
  }
  if(fpRef)
  {
    fclose(fpRef);
  }
  if(fpOut)
  {
    fclose(fpOut);
  }

  return 0;
}

int32_t fcwTest(sFCW_Config * testcaseParams)
{
  int32_t numMemRec, readStatus;
  IALG_MemRec *memRec;
  int32_t status, startFrame, endFrame;
  uint32_t testcase;
  FILE *fpOut = NULL;
  char *file = NULL;
  long long  t0, t1;

#if (!HOST_EMULATION)
  _TSC_enable();
#endif
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  FCW_TI_CreateParams  createParams;
  FCW_TI_InArgs        inArgs;
  IVISION_InBufs       inBufs;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[FCW_TI_IN_BUFDESC_TOTAL];

  FCW_TI_OutArgs    outArgs;
  IVISION_OutBufs   outBufs;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[FCW_TI_OUT_BUFDESC_TOTAL];

  FCW_TI_output *fcwOutputinfo;

  outArgs.iVisionOutArgs.size = sizeof(FCW_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(FCW_TI_InArgs);

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for L1DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for L2MEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pL2mem;
  TIMemHandle memHdl_L2MEM;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for DDR NON CACHE MEM                     */
  /*--------------------------------------------------------------------------*/
  uint8_t *pExtNCmem;
  TIMemHandle memHdl_EXTMEMNC;

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for DDR NON CACHE MEM                     */
  /*--------------------------------------------------------------------------*/
  uint8_t *pExtCmem;
  TIMemHandle memHdl_EXTMEMC;

  uint32_t frameIdx;
  int32_t grndPlaneSize = sizeof(inArgs.grndPlaneEq);

  pDmem = DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM0;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM0_SIZE);

  pL2mem = L2MEM_SCRATCH;
  memHdl_L2MEM = &memObj_DMEM1;
  TI_CreateMemoryHandle(memHdl_L2MEM, pL2mem, DMEM1_SIZE);

  pExtNCmem = DDRMEM_NONCACHE;
  memHdl_EXTMEMNC = &memObj_DDRMEMNC;
  TI_CreateMemoryHandle(memHdl_EXTMEMNC, pExtNCmem, DDRNONCACHE_SIZE);

  pExtCmem = DDRMEM_CACHE;
  memHdl_EXTMEMC = &memObj_DDRMEMC;
  TI_CreateMemoryHandle(memHdl_EXTMEMC, pExtCmem, DDRCACHE_SIZE);

  for ( testcase = 0 ; testcase < fcw_numTestCases; testcase++ )
  {
    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs  = FCW_TI_IN_BUFDESC_TOTAL;
    outBufs.numBufs = FCW_TI_OUT_BUFDESC_TOTAL;

    inBufDescList[FCW_TI_IN_BUFDESC_OBJECT_PLANE] = &inBufDesc;
    outBufDescList[FCW_TI_OUT_BUFDESC_TTC_PLANES] = &outBufDesc;


    /*-----------------------------------------------------------------
    Set algorithm create time parameters
    -----------------------------------------------------------------*/
    createParams.maxNumObjects      = testcaseParams[testcase].maxNumObjects;
    createParams.minObjDist         = testcaseParams[testcase].minObjDist  ;
    createParams.maxObjDist         = testcaseParams[testcase].maxObjDist  ;
    createParams.minObjHeight       = testcaseParams[testcase].minObjHeight;
    createParams.maxObjHeight       = testcaseParams[testcase].maxObjHeight;

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = FCW_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = FCW_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams),
                                                                  NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    printf("FCW algorithm Create Done\n");

    /*-----------------------------------------------------------------
    Allocate memory for all the mem records
    Application has to implement the below function
    Refer the example implementation below in this file
    -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);
    TestApp_memContamination(memRec,numMemRec,-1);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    startFrame = testcaseParams[testcase].startFrame;
    endFrame   = startFrame + testcaseParams[testcase].maxFrames;

    TestApp_ReadInCameraPrm((float*)&inArgs.camExtPrm,
                  (float*)&createParams.camIntPrm, startFrame, startFrame,
                  (char *)testcaseParams[testcase].camExtPrmFileName, endFrame);

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = FCW_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle), memRec,
                                          NULL, (IALG_Params *)(&createParams));

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    printf("FCW algorithm Init Done\n");

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size         = sizeof(FCW_TI_InArgs);


    inBufDesc.numPlanes               = 1;
    outBufDesc.numPlanes              = 1;

    TestApp_AllocIOBuffers(&inBufs,&outBufs,&testcaseParams[testcase]);

    for(frameIdx = 0; frameIdx < testcaseParams[testcase].maxFrames;frameIdx++)
    {

      Inargs_memContamination(&inArgs);
      /*-----------------------------------------------------------------
      Read ground plane equation parameters to inArgs.grndPlaneEq
      -----------------------------------------------------------------*/
      readStatus = TestApp_ReadInGrndPlaneEqPrm((float*)&inArgs.grndPlaneEq,
                    frameIdx, startFrame,
                    (char *)testcaseParams[testcase].grndPlnPrmFileName,
                    endFrame, grndPlaneSize);

      if(readStatus < 0)
      {
        printf("ground plane equation parameters read error\n");
        break;
      }

      /*-----------------------------------------------------------------
      Read camera extrinsic parameters to inArgs.camExtPrm
      -----------------------------------------------------------------*/
      readStatus = TestApp_ReadInCameraPrm((float*)&inArgs.camExtPrm,
                (float*)&createParams.camIntPrm, frameIdx, startFrame,
                (char *)testcaseParams[testcase].camExtPrmFileName, endFrame);

      if(readStatus < 0)
      {
        printf("camIntPrm and camExtPrm read error\n");
        break;
      }
      /*-----------------------------------------------------------------
      Read object parameters from odoutput file which was dumped by
      object detection module. Parameters are read to inBufs.
      -----------------------------------------------------------------*/
      readStatus = TestApp_ReadInBufs(&inBufs, frameIdx,
                                (char *)testcaseParams[testcase].inObjFileName);
      if(readStatus < 0)
      {
        printf("object parameters read error\n");
        break;
      }

      inArgs.fps                        = testcaseParams[testcase].fps;
      inArgs.imgHeight                  = testcaseParams[testcase].imgHeight;
      inArgs.camHeightInMeter           = 1.58;
      inArgs.camOffsetInMeter           = 1.4;
      
#if (!HOST_EMULATION)
      /* Write back Invalidate cache */
      //CacheWbInv();
      t0 = _TSC_read();
#endif

      status = handle->ivision->algProcess((IVISION_Handle)handle, &inBufs,
               &outBufs, (IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

#if (!HOST_EMULATION)
      t1 = _TSC_read();
      printf(" Cycles => per frame %ld \t--\t", t1-t0);
      fcwOutputinfo  = (FCW_TI_output *)
        outBufs.bufDesc[FCW_TI_OUT_BUFDESC_TTC_PLANES]->bufPlanes[0].buf;
      printf("per frame per object %f \n",
                                      (float)(t1-t0)/fcwOutputinfo->numObjects);
      /* Write back Invalidate cache */
      //CacheWbInv();
#endif

      if(status != IALG_EOK)
      {
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }

      printf("Processing Completed for frame %d \n\n",frameIdx);

      TestApp_WriteOutBufs(&outBufs, frameIdx, startFrame,
                     (char *)testcaseParams[testcase].outTTCFileName, endFrame);
    }

    TestApp_CompareOutBufs(&outBufs,
      (char *)testcaseParams[testcase].outTTCFileName,
      (char *)testcaseParams[testcase].refTTCFileName,endFrame);

  }

EXIT_LOOP:

  if(file != NULL)
  {
    free(file);
  }
  if(fpOut)
  {
    fclose(fpOut);
  }
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

  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  char configFile[FCW_FILE_NAME_SIZE]={0};
#if (!HOST_EMULATION)
  InitCache();
#endif
  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/fcw.cfg");
  }

  status = readparamfile(configFile, &gsTokenMap_FCW[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  /* Validate the algorithm */
  status = fcwTest(gConfig_FCW);

  return status;
}



