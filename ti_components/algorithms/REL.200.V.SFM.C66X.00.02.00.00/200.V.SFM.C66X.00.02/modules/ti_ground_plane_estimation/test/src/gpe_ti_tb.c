/*
* module name : Ground Plane Estimation
*
* module descripton : Generates ground plane information from sparse 3D points
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
/** @file gpe_tb.c
*
*  @brief  This file contains test code for forward collision warning algorithm
*
*
*  @date   October 2015
*
*  Description
*    This file contains test code to validate the frame level algorithm TI GPE
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
#include "gpe_ti_tb.h"
#include "gpe_ti_config.h"
#include "igpe_ti.h"
#include "ti_mem_manager.h"
#if (!HOST_EMULATION)
//#include "edma3_lld_helper.h"
#endif

#include "ti_file_io.h"
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

#include "ti_file_io.h"

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

#define DDRNONCACHE_SIZE (40*1024)
#define DDRCACHE_SIZE (220*1024)

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

#pragma DATA_SECTION (DDRMEM_CACHE, ".fileioCached");
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

int32_t Inargs_memContamination(GPE_TI_InArgs   *inArgs)
{

  memset(inArgs, (int32_t) 0xFF , sizeof(GPE_TI_InArgs));
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
                               sGPE_Config * params)
{
  TIMemHandle memHdl_EXTMEM = &memObj_DDRMEMC;
  uint32_t size;

  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->numPlanes               = 1;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.
                                                      topLeft.x = 0;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.
                                                      topLeft.y = 0;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].width
                                                      = sizeof(GPE_TI_OD_input);
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].height     = 1;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.width
                                                      = sizeof(GPE_TI_OD_input);
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].frameROI.height
                                                      = 1;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].planeType  = 0;

  size = sizeof(GPE_TI_OD_input);

  /* Allocate the buffer in DDR which is non-cacheable */

  inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].buf =
                                      TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);

  if(inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].buf == NULL)
  {
    PRINT_ERRORE_MSG();
  }


  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->numPlanes            = 1;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].frameROI.
                                                      topLeft.x = 0;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].frameROI.
                                                      topLeft.y = 0;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].width
                         = params->maxNumPointCloud * sizeof(GPE_TI_pCloudDesc);
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].height  = 1;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].frameROI.
                  width = params->maxNumPointCloud * sizeof(GPE_TI_pCloudDesc);
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].frameROI.
                                                                    height = 1;
  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].planeType
                                                                           = 0;

  size = params->maxNumPointCloud * sizeof(GPE_TI_pCloudDesc);

  /* Allocate the buffer in DDR which is non-cacheable */

  inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].buf =
                                      TI_GetMemoryChunk(memHdl_EXTMEM, size, 4);

  if(inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].buf
                                                                       == NULL)
  {
    PRINT_ERRORE_MSG();
  }

  return IALG_EOK;
}


int32_t TestApp_WriteInGrndPlaneEqPrm(float * dstgrndPlaneEq,
  int32_t currFrameNum,
  int32_t startFrameNum,
  char * fileName,
  int32_t maxFrameNum,
  int32_t size)
{
  int32_t bytesWritten;
  float curFrameNumF = currFrameNum;

  if(currFrameNum == startFrameNum) {
    fp_in_grndPlaneEq   = fopen(fileName, "wb");

    if(fp_in_grndPlaneEq == NULL)
      exit(0);
  }else{
    fp_in_grndPlaneEq   = fopen(fileName, "ab");

    if(fp_in_grndPlaneEq == NULL)
      exit(0);
  }

  /**
  * In grndPlaneEq input file, first value is index of the arrary which is not
  * used in computations. That index is avoided in grndPlaneEq array.
  */
  bytesWritten = fwrite(&curFrameNumF,1,sizeof(float),fp_in_grndPlaneEq);

  bytesWritten += fwrite(&dstgrndPlaneEq[1],1,sizeof(float),fp_in_grndPlaneEq);
  bytesWritten += fwrite(&dstgrndPlaneEq[0],1,sizeof(float),fp_in_grndPlaneEq);
  bytesWritten += fwrite(&dstgrndPlaneEq[2],1,sizeof(float),fp_in_grndPlaneEq);

  if(bytesWritten < (size + sizeof(float)))
  {
    return (-1);
  }

  fclose(fp_in_grndPlaneEq);

  return (0);
}


int32_t TestApp_ReadInBufs(IVISION_InBufs *inBufs,
                           int32_t currFrameNum,
                           char * fileName,
                           char * pointCloudFileName,
                           uint16_t *numPointCloud)
{
  int32_t bytesRead, totalbytesRead;
  char temp[150];
  TI_FILE* fp;
  int32_t size =
    inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].width *
    inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].height;

  fp = FOPEN(fileName, "rb");

  if(fp == NULL)
  {
    goto Exit;
  }

  FSEEK(fp, currFrameNum*size, SEEK_SET);

#if (!DISABLE_FILE_IO)
  bytesRead = FREAD(inBufs->bufDesc[GPE_TI_IN_BUFDESC_OBJECT_PLANE]->bufPlanes[0].buf,1, size, fp);
  if(bytesRead < size)
  {
    printf("TestApp: Object Descriptors: size- %d\tbytesRead = %d\n",size, bytesRead);
    return (-1);
  }
#endif

  FCLOSE(fp);

  /*------------------------------------------------------------------------*/
  /* GPE Input File Read                                                    */
  /*------------------------------------------------------------------------*/
  size =
    inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].width *
    inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].height;

  sprintf(temp, "%04d", currFrameNum);
  strcat((char *)pointCloudFileName, temp);
  strcat((char *)pointCloudFileName, ".bin");
  //printf("Reading Point Cloud File : %s\n",pointCloudFileName);
  fp = FOPEN(pointCloudFileName, "rb");
  if(fp == NULL)
  {
    goto Exit;
  }

  //fseek(fp, currFrameNum*size, SEEK_SET);
  bytesRead = 0;
  totalbytesRead = 0;

#if (!DISABLE_FILE_IO)
  
   bytesRead = FREAD(inBufs->bufDesc[GPE_TI_IN_BUFDESC_POINTCLOUD_PLANE]->bufPlanes[0].buf, 1, size, fp );
   totalbytesRead += bytesRead;
   *numPointCloud = totalbytesRead/sizeof(GPE_TI_pCloudDesc);

#endif

  FCLOSE(fp);


Exit:
  return (0);
}


int32_t TestApp_CompareOutPut(char * outGpeFileName, char * refGpeFileName,
                              char * compFileName, int32_t startFrameNum,
                              int32_t maxFrameNum)
{
  FILE* outGpeFile = fopen(outGpeFileName,"rb");
  FILE* refGpeFile = fopen(refGpeFileName,"rb");
  FILE* compGpeFile = fopen(compFileName,"w");
  int32_t numBytesRead;

  int32_t i;
  float curGpe[4];
  float refGpe[4];

  if((outGpeFile == NULL) || (refGpeFile == NULL) || (compGpeFile == NULL)){
    return(0);
  }else{

    fprintf(compGpeFile,"          FrmNum,     Roll,     Pitch,      Dist \n");
    for(i = startFrameNum; i < maxFrameNum; i++){
      numBytesRead = fread(curGpe,1,4*sizeof(float),outGpeFile);

      if(numBytesRead == 0)
        break;

      numBytesRead = fread(refGpe,sizeof(float),4,refGpeFile);
      if(numBytesRead == 0)
        break;

      if(curGpe[0] != refGpe[0]){
        continue;
      }
      else{
        fprintf(compGpeFile,"Platform :: %04d,%6.4f,%6.4f,%6.4f\n",(int)(curGpe[0]),curGpe[1],curGpe[2],curGpe[3]);
        fprintf(compGpeFile,"Reference:: %04d,%6.4f,%6.4f,%6.4f\n",(int)(refGpe[0]),refGpe[1],refGpe[2],refGpe[3]);
#if (HOST_EMULATION)
        fprintf(compGpeFile,"Diff     ::      %6.4f,%6.4f,%6.4f\n\n",abs(refGpe[1]-curGpe[1]),abs(refGpe[2]-curGpe[2]),abs(refGpe[3]-curGpe[3]));
#else
        fprintf(compGpeFile,"Diff     ::      %6.4f,%6.4f,%6.4f\n\n",_fabs(refGpe[1]-curGpe[1]),_fabs(refGpe[2]-curGpe[2]),_fabs(refGpe[3]-curGpe[3]));

#endif
     }
    }
  }

  fclose(outGpeFile);
  fclose(refGpeFile);
  fclose(compGpeFile);

  return 0;
}

int32_t gpeTest(sGPE_Config * testcaseParams)
{
  int32_t numMemRec, readStatus, i, writeStatus;
  IALG_MemRec *memRec;
  int32_t status, startFrame, endFrame;
  int32_t grndPlaneSize;
  uint32_t testcase;
  uint16_t numPointCloud;
  FILE *fpOut = NULL;
  char *file = NULL;
  long long  t0, t1;
  char inPointCloudFileName[FILE_NAME_SIZE];
  char grndPlnPrmFileName[FILE_NAME_SIZE];


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
  GPE_TI_CreateParams  createParams;
  GPE_TI_InArgs        inArgs;
  IVISION_InBufs       inBufs;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[GPE_TI_IN_BUFDESC_TOTAL];
  IVISION_BufDesc   *inBufDescList[GPE_TI_IN_BUFDESC_TOTAL];

  GPE_TI_OutArgs    outArgs;
  IVISION_OutBufs   outBufs;

  outArgs.iVisionOutArgs.size = sizeof(GPE_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(GPE_TI_InArgs);

  grndPlaneSize = sizeof(outArgs.grndPlaneEq);
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

  for ( testcase = 0 ; testcase < gpe_numTestCases; testcase++ )
  {
    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;

    inBufs.numBufs  = GPE_TI_IN_BUFDESC_TOTAL;

    for(i = 0 ; i < GPE_TI_IN_BUFDESC_TOTAL ;i++)
    {
        inBufDescList[i]     = &inBufDesc[i];
        inBufDesc[i].numPlanes  = 1;
    }

    /*-----------------------------------------------------------------
    Set algorithm create time parameters
    -----------------------------------------------------------------*/
    createParams.maxNumPointCloud   = testcaseParams[testcase].maxNumPointCloud;
    createParams.maxNumObjects      = testcaseParams[testcase].maxNumObjects;

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = GPE_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = GPE_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams),
                                                                  NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    printf("GPE algorithm Create Done\n");

    /*-----------------------------------------------------------------
    Allocate memory for all the mem records
    Application has to implement the below function
    Refer the example implementation below in this file
    -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);
    //TestApp_memContamination(memRec,numMemRec,-1);
    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    startFrame = testcaseParams[testcase].startFrame;
    endFrame   = startFrame + testcaseParams[testcase].maxFrames;

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = GPE_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle), memRec,
                                          NULL, (IALG_Params *)(&createParams));

    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }

    printf("GPE algorithm Init Done\n");

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size         = sizeof(GPE_TI_InArgs);

    TestApp_AllocIOBuffers(&inBufs,&outBufs,&testcaseParams[testcase]);


    for(frameIdx = 0; frameIdx < testcaseParams[testcase].maxFrames;frameIdx++)
    {

      printf("Frame :: %d\n",frameIdx);

      Inargs_memContamination(&inArgs);

      /*-----------------------------------------------------------------
      Read object parameters from odoutput file which was dumped by
      object detection module. Parameters are read to inBufs.
      -----------------------------------------------------------------*/
      strcpy(grndPlnPrmFileName, (char *)testcaseParams[testcase].outGpeFileName);
      strcpy(inPointCloudFileName, (char *)testcaseParams[testcase].inPointCloudFileName);

      readStatus = TestApp_ReadInBufs(&inBufs, frameIdx,
                                (char *)testcaseParams[testcase].inObjFileName,
                                 inPointCloudFileName,
                                 &numPointCloud);
      if(readStatus < 0)
      {
        printf("object parameters read error\n");
        break;
      }

    inArgs.fps                        = testcaseParams[testcase].fps;
    inArgs.imgHeight                  = testcaseParams[testcase].imgHeight;
    inArgs.imgWidth                   = testcaseParams[testcase].imgWidth;
    inArgs.numPointCloud              = numPointCloud;

    memcpy(&inArgs.gpeParams, &testcaseParams[testcase].gpePrms, sizeof(GPE_TI_configParams));
    inArgs.gpeParams.rsvd1 = 0x0;

    outArgs.grndPlaneEq[0] = 0;
    outArgs.grndPlaneEq[1] = 0;
    outArgs.grndPlaneEq[2] = 0;

#if (!HOST_EMULATION)

      t0 = _TSC_read();
#endif
      
      printf("Process call started \n");
      if(readStatus >= 0)
      {
      GPE_TI_VISION_FXNS.ialg.algActivate((IALG_Handle) handle);
      status = handle->ivision->algProcess((IVISION_Handle)handle, &inBufs,
           &outBufs, (IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

      GPE_TI_VISION_FXNS.ialg.algDeactivate((IALG_Handle) handle);
      }
      else
      {
        status = IALG_EOK;
      }

      printf("Process call finished \n");

#if (!HOST_EMULATION)
      t1 = _TSC_read();
      printf("Cycles Consumed : %ld \n", t1-t0);
      /* Write back Invalidate cache */
      /*Invalidate cache */
    /* frame to frame no dependency in GPE process call, only random number
       gnerator seed is to be maintained across frames, hence so writeback is
       required below.
     */
    *L1DWBINV = 1;
    *L2WBINV = 1; 
#endif

      if(status != IALG_EOK)
      {
        printf("Process Failure\n");
        PRINT_ERRORE_MSG();
        goto EXIT_LOOP;
      }
      printf("NumberOf Iteration = %d\n",outArgs.gpeStats.numValidRansacItr);
      printf("grndPlaneEq [Roll : Pitch : Dist] = [%10.8f : %10.8f% : %10.8f]\n\n",
      outArgs.gpeStats.outRoll, outArgs.gpeStats.outPitch, outArgs.gpeStats.outDistFromPlane);

#ifdef ENABLE_PROFILE
      printf("Cycles - selectRansacPoints      = %ld\n",outArgs.gpeStats.rsvd[0]);
      printf("Cycles - populateCloudRansacIp   = %ld\n",outArgs.gpeStats.rsvd[1]);
      printf("Cycles - IsPointInTrpzd cost calculation   = %ld\n",outArgs.gpeStats.rsvd[2]);
      printf("Cycles - ransacCore              = %ld\n",outArgs.gpeStats.rsvd[3]);
      printf("Cycles - computeScale & Filtering= %ld\n",outArgs.gpeStats.rsvd[4]);
      printf("Cycles - affineFit               = %ld\n",outArgs.gpeStats.rsvd[5]);
#endif


      writeStatus = TestApp_WriteInGrndPlaneEqPrm((float*)&outArgs.gpeStats.outPitch,
                    frameIdx, startFrame,
                    (char *)grndPlnPrmFileName,
                    endFrame, grndPlaneSize);
                    
      if(writeStatus){
        printf("Ground plane information is written \n");
      }

    }

    TestApp_CompareOutPut((char *)testcaseParams[testcase].outGpeFileName,
                          (char *)testcaseParams[testcase].refGpeFileName,
                          (char *)testcaseParams[testcase].compFileName,
                          startFrame,
                          endFrame);

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
  char configFile[GPE_FILE_NAME_SIZE]={0};
#if (!HOST_EMULATION)
  InitCache();
#endif
  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/gpe.cfg");
  }

#ifdef USE_HOST_FILE_IO
  ti_fileio_init();
#endif

  memcpy(&gConfig_GPE[0].gpePrms,&gpePrmsDefault,sizeof(GPE_TI_configParams));

  status = readparamfile(configFile, &gsTokenMap_GPE[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  /* Validate the algorithm */
  status = gpeTest(gConfig_GPE);

  return status;
}



