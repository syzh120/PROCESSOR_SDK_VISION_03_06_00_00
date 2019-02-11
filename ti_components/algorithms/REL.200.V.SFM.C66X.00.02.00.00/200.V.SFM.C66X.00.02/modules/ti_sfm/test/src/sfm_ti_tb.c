/*
* module name : Structure From Motion
*
* module descripton : Generates sparse 3D points from optical flow information in camera captured images
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
/** @file SFM_tb.c
*
*  @brief  This is a test bench file for Structure From Motion (SFM) module.
*          This test interface is common for PD and TSR.
*
*  @date   October 2014
*
*/

#pragma CHECK_MISRA ("none")

#include "sfm_ti_tb.h"
#include "float.h"

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  char configFile[FILE_NAME_SIZE]={0};
#if (!HOST_EMULATION)
  /*---------------------------------------------------------------------------
  Initialization of cache. Currently 128KB of L2 , 16 KB
  of L1, and full L1P is configured as cache.
  ----------------------------------------------------------------------------*/
  InitCache();
#endif

#if (!HOST_EMULATION)
  _TSC_enable();
#endif

  if (argc > 1)
  {
    strcpy(configFile, argv[1]) ;
  }
  else
  {
    strcpy(configFile,"../testvecs/config/sfm.cfg");
  }

  /*---------------------------------------------------------------------------
  Setting the default value of the current test case.
  ----------------------------------------------------------------------------*/
  gConfig_sfm[0].maxFrames         = 1;
  gConfig_sfm[0].maxRansacItr      = 90;
  gConfig_sfm[0].maxTriangItr      = 10;
  gConfig_sfm[0].curPrev3DPtFlag   = SFM_TI_OUT_CUR_PREV_3D_POINTS_DEFAULT;
  gConfig_sfm[0].maxNumTracks      = MAX_NUM_IN_POINTS;
  gConfig_sfm[0].profileEn         = 0;
  gConfig_sfm[0].compareEn         = 0;
  gConfig_sfm[0].sfmEn             = 0;
  gConfig_sfm[0].fMatrixPrunEn     = 1;
  gConfig_sfm[0].fMatrixInTh       = 2;
  gConfig_sfm[0].camExtPrmNormType = SFM_TI_CAM_EXT_PRM_NORM_DEFAULT;
  gConfig_sfm[0].pointPruneAngle   = 0.0;
  gConfig_sfm[0].fMatrixCalcMethod = SFM_TI_FMAT_EXT_PRM_NORM_DEFAULT;

  sprintf((char*)&gConfig_sfm[0].compareRsultPath[0], "../testvecs/output/");

  /*---------------------------------------------------------------------------
  Read the config file parameters set value
  ----------------------------------------------------------------------------*/
  status = readparamfile(configFile, &gsTokenMap_sfm[0]) ;

  if(status == -1)
  {
    printf("Parser Failed \n");
    return -1 ;
  }
#ifdef USE_HOST_FILE_IO
  ti_fileio_init();
#endif
  /*---------------------------------------------------------------------------
  Validate the applet
  ----------------------------------------------------------------------------*/
  if(gConfig_sfm[0].sfmEn){
    status = sfmTest(gConfig_sfm);
  }

  /*---------------------------------------------------------------------------
  Do the compression of .ply file with reference .ply file
  ----------------------------------------------------------------------------*/
  if(gConfig_sfm[0].compareEn){
    //status = sfmCompare(gConfig_sfm);
  }

  return status;
}

int32_t sfmTest(ssfm_Config * testcaseParams)
{
  int32_t         numMemRec;
  IALG_MemRec*    memRec;
  int32_t         status;
  uint32_t        testcase;
  long long       t0, t1;
  uint8_t*        pDmem1;
  uint8_t*        pDmem0;
  TIMemHandle     memHdl_DMEM1,memHdl_DMEM0;
  SFM_TI_output*  outputSfm;
  uint32_t        frameIdx;
  char            tempStr[200];
  int32_t         numFeat,startFrame,endFrame,validNumFeat,i;
  SFM_TI_trackInfo* baseTrackInfo;

#if (!HOST_EMULATION)
  _TSC_enable();
#endif
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *             handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  SFM_TI_CreateParams   createParams;

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc       inBufDesc;
  IVISION_BufDesc*      inBufDescList[SFM_TI_IN_BUFDESC_TOTAL];

  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc       outBufDesc;
  IVISION_BufDesc*      outBufDescList[SFM_TI_OUT_BUFDESC_TOTAL];

  /*-----------------------------------------------------------------
  InArgs and InBufs declaration required in SFM process call
  ----------------------------------------------------------------*/

  SFM_TI_InArgs         inArgs;
  IVISION_InBufs        inBufs;

  /*-----------------------------------------------------------------
  InArgs and InBufs declaration required in SFM process call
  ----------------------------------------------------------------*/
  SFM_TI_OutArgs        outArgs;
  IVISION_OutBufs       outBufs;
#ifdef ENABLE_PROFILE
  TI_DSP_PrfInfo*       prfInfo;
  sSfm_TI_L1DMem*       sfmL1Prm = (sSfm_TI_L1DMem*)(0x00F00000);
#endif
  outArgs.iVisionOutArgs.size = sizeof(SFM_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(SFM_TI_InArgs);

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for L2 SRAM of DSP.                                  */
  /*--------------------------------------------------------------------------*/
  pDmem1 = (uint8_t *)&DMEM1_SCRATCH;
  pDmem0 = (uint8_t *)&DMEM0_SCRATCH;

  memHdl_DMEM1 = &memObj_DMEM1;
  memHdl_DMEM0 = &memObj_DMEM0;

  TI_CreateMemoryHandle(memHdl_DMEM1, pDmem1, DMEM1_SIZE);
  TI_CreateMemoryHandle(memHdl_DMEM0, pDmem0, DMEM0_SIZE);

  /*--------------------------------------------------------------------------
  Currently Only test case running is supported in single run.
  -------------------------------------------------------------------------*/
  sfm_numTestCases  = (testcaseParams[0].sfmEn == 1) ? 1: 0;

  printf("\n**************************************************************");
  printf("\n********~~~~~~~~~TI-Structure From Motion~~~~~~~~~~~~~~******");
  printf("\n**************************************************************\n");

  for ( testcase = 0 ; testcase < sfm_numTestCases; testcase++ )
  {

    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc       = inBufDescList;
    outBufs.bufDesc      = outBufDescList;

    inBufs.numBufs       = SFM_TI_IN_BUFDESC_TOTAL;
    outBufs.numBufs      = SFM_TI_OUT_BUFDESC_TOTAL;

    inBufDescList[SFM_TI_IN_BUFDESC_FEATURE_PLANE]    = &inBufDesc;
    outBufDescList[SFM_TI_OUT_BUFDESC_FEATURE_PLANES] = &outBufDesc;

    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
    createParams.maxNumTracks  = testcaseParams[testcase].maxNumTracks;
    createParams.rsvd1         = testcaseParams[testcase].profileEn;
    createParams.camExtPrmNormType = testcaseParams[testcase].camExtPrmNormType;

    /*-----------------------------------------------------------------
    Query algorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = SFM_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = SFM_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("Structure from motion Applet Create Done\n");
#endif
    /*-----------------------------------------------------------------
    Allocate memory for all the mem records
    Application has to implement the below function
    Refer the example implementation below in this file
    -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);

    //TestApp_memContamination(memRec,numMemRec,-1);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    startFrame = testcaseParams[testcase].startFrame;
    endFrame   = startFrame + testcaseParams[testcase].maxFrames;

    TestApp_ReadInCameraPrm((float*)&inArgs.camExtPrm,
      (float*)&createParams.camIntPrm,
      startFrame,startFrame,
      (char *)testcaseParams[testcase].inCamPrmFileName,
      startFrame);

    /*-----------------------------------------------------------------
    Initialize the algorithm instance with the allocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = SFM_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));


    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    printf("SFM Application Init Done\n");
#endif

    inArgs.iVisionInArgs.subFrameInfo       = 0;
    inArgs.iVisionInArgs.size               = sizeof(SFM_TI_InArgs);
    inBufDesc.numPlanes                     = 1;
    outBufDesc.numPlanes                    = 1;

    TestApp_AllocIOBuffers(&inBufs,&outBufs,testcaseParams[testcase].maxNumTracks);

    for(frameIdx = startFrame; frameIdx < endFrame; frameIdx++)
    {
      //TestApp_memContamination(memRec,numMemRec,frameIdx);

      /*-----------------------------------------------------------------------
      Read the Intrinsic and extrinsic Parameter of camera corresponding to
      current frame
      -----------------------------------------------------------------------*/

      TestApp_ReadInCameraPrm((float*)&inArgs.camExtPrm,
        (float*)&createParams.camIntPrm,
        frameIdx,startFrame,
        (char *)testcaseParams[testcase].inCamPrmFileName,
        endFrame);

#if (TRACK_DATA_FORMAT)
      sprintf(tempStr,"%s%d.bin",testcaseParams[testcase].inFeatFileName, (frameIdx ));
#else
      sprintf(tempStr,"%s%d.txt",testcaseParams[testcase].inFeatFileName, (frameIdx ));
#endif

      numFeat=
        TestApp_ReadInBuf((uint16_t*)inBufs.bufDesc[0]->bufPlanes[0].buf,frameIdx,
        (char *)tempStr,testcaseParams[testcase].maxNumTracks);

      inBufs.bufDesc[SFM_TI_IN_BUFDESC_FEATURE_PLANE]->bufferId    = frameIdx;
      outBufs.bufDesc[SFM_TI_OUT_BUFDESC_FEATURE_PLANES]->bufferId = frameIdx;

      /*-----------------------------------------------------------------------
      Population of inArgs parameters
      ---------------------------------------------------------------------*/
      inArgs.trackPtQfmt      = 4;
      validNumFeat            = 0;
      baseTrackInfo           = (SFM_TI_trackInfo*)(inBufs.bufDesc[0]->bufPlanes[0].buf);
      for(i = 0; i < numFeat; i++){
        if(baseTrackInfo->age != 0x0)
          validNumFeat = i;
        baseTrackInfo++;
      }

      inArgs.numTracks         = (validNumFeat + 1);

      inArgs.maxRansacItr      = testcaseParams[testcase].maxRansacItr;
      inArgs.maxTriangItr      = testcaseParams[testcase].maxTriangItr;
      inArgs.curPrev3DPtFlag   = testcaseParams[testcase].curPrev3DPtFlag;
      inArgs.fMatrixPrunEn     = testcaseParams[testcase].fMatrixPrunEn;
      inArgs.fMatrixInTh       = testcaseParams[testcase].fMatrixInTh;
      inArgs.pointPruneAngle   = testcaseParams[testcase].pointPruneAngle;
      inArgs.fMatrixCalcMethod = testcaseParams[testcase].fMatrixCalcMethod;
      inArgs.reserved0         = 0x0;
      
      printf("Frame#%5d\n",frameIdx);
      printf("  In Tracks            = %15d\n",inArgs.numTracks);

#if (!HOST_EMULATION)
      Cache_WbInvAll();
#endif

#if (!HOST_EMULATION)
      t0 = _TSC_read();
#endif
      /*-----------------------------------------------------------------------
      SFM Algorithm process call
      ---------------------------------------------------------------------*/
      status = handle->ivision->algProcess((IVISION_Handle)handle,
        &inBufs,
        &outBufs,
        (IVISION_InArgs  *)&inArgs,
        (IVISION_OutArgs *)&outArgs);

#if (!HOST_EMULATION)
      t1 = _TSC_read();
#endif
      if(outArgs.iVisionOutArgs.inFreeBufIDs[0] != frameIdx)
        printf("\n Problem in in free Id");

      if(outArgs.iVisionOutArgs.outFreeBufIDs[0] != frameIdx)
        printf("\n Problem in out free Id");



      printf("  Out 3D Point         = %15d\n",outArgs.outNumPoints);
      printf("  numIterFMat          = %15d\n",outArgs.sfmStats.numIterFMat);
      printf("  numInlierFmat        = %15d\n",outArgs.sfmStats.numInlierFmat);
      printf("  numCur3DPnts         = %15d\n",outArgs.sfmStats.numCur3DPnts);
      printf("  isStatic             = %15d\n",outArgs.sfmStats.isStatic);

#if (!HOST_EMULATION)
      long long totOverHead = 0;
      long long prfCycSum = 0;
#ifdef ENABLE_PROFILE
      /*-----------------------------------------------------------------------
      createParams :: rsvd1 is used for enabling the profiling of internals
      of SFM algorithm
      -----------------------------------------------------------------------*/
      if(createParams.rsvd1 != 0x0){

        prfInfo = (TI_DSP_PrfInfo*)outArgs.sfmStats.rsvd1;

        printf("  Sub-Modules Profile Info\n");

        for(md = 0; md < TI_DSP_PROFILE_MAX; md ++){
          if((prfInfo->prfData[md].moduleId != -1))
            printf("    MODULE%3d TotalCycle = %10lld TotalCount = %10d avgCycle = %5lld\n",\
            prfInfo->prfData[md].moduleId,
            prfInfo->prfData[md].totalTime,
            prfInfo->prfData[md].count,
            (prfInfo->prfData[md].totalTime/prfInfo->prfData[md].count));
            prfCycSum += prfInfo->prfData[md].totalTime;
        }
        totOverHead = prfInfo->totalOvehead;
      }
      if(sfmL1Prm->rsvd2 > 0)
        printf("  AvgCycle Module      = %15d, %d, %d\n",sfmL1Prm->rsvd1/sfmL1Prm->rsvd2,sfmL1Prm->rsvd1,sfmL1Prm->rsvd2);

#endif
      printf("  Total Cycle          = %15lld, %15lld\n",(t1 - t0 - totOverHead),prfCycSum);
      

#endif

      if(status != IALG_EOK)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

#if ENABLE_TRACES
      printf("Processing Completed for frame %d \n",frameIdx);
#endif
      outputSfm  = (SFM_TI_output *)outBufs.bufDesc[0]->bufPlanes[0].buf;

      /*-----------------------------------------------------------------------
      Write out the 3D points location in .txt  file and also on YUV file
      -----------------------------------------------------------------------*/
#if 1
      TestApp_WriteOutBuf(outputSfm,frameIdx,startFrame,
        (char *)testcaseParams[testcase].outFeatFileName,
        (char *)testcaseParams[testcase].inImgFileName,
        (char *)testcaseParams[testcase].outImgFileName,
        endFrame,
        testcaseParams[testcase].imageWidth,
        testcaseParams[testcase].imageHeight,
        outArgs.outNumPoints);
#endif
    }


EXIT_LOOP:

    status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
    }

    /* Here Free memory for all the mem records */
    status = TestApp_FreeMemRecords(memRec,numMemRec);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
    }

    if ( memRec != NULL )
    {
      free(memRec);
    }

#if 0 // in and out buffers are statically allocated , not through malloc
    for ( levelCnt = 0 ; levelCnt < inBufDesc.numPlanes ; levelCnt++)
    {
      if ( inBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        free(inBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < outBufDesc.numPlanes ; levelCnt++)
    {
      if ( outBufDesc.bufPlanes[levelCnt].buf != NULL )
      {
        free(outBufDesc.bufPlanes[levelCnt].buf);
      }
    }
#endif

  }
  return status;
}


int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM1 = &memObj_DMEM1;

  TIMemHandle memHdl_DMEM0 = &memObj_DMEM0;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM1) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM1, memRec[i].size, memRec[i].alignment);
      if(memRec[i].base == NULL) {
        memRec[i].base = (Void *) malloc( memRec[i].size);
        memRec[i].space = IALG_EXTERNAL;
        printf("\n Internal memory could not be allocated");
      }
    }
    else if(memRec[i].space == IALG_DARAM0) {
      /*L1D SRAM space, currently alg requires 16kb SRAM and 16kb cache.
      */
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM0, memRec[i].size, memRec[i].alignment);
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
int32_t TestApp_memContamination(IALG_MemRec * memRec,int32_t numMemRec, int32_t frmIdx){

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
    if(memRec[i].space == IALG_EXTERNAL) {
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs, uint16_t inNumTracks)
{
  /*int32_t size;*/

  inBufs->bufDesc[0]->numPlanes                          = 1;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[0]->bufPlanes[0].width                 = inNumTracks;
  inBufs->bufDesc[0]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[0]->bufPlanes[0].width;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = 1;
  inBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;

  /*size = sizeof(SFM_TI_trackInfo) * inNumTracks;*/

  inBufs->bufDesc[0]->bufPlanes[0].buf = IN_BUF;

  if((inBufs->bufDesc[0]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERROR_MSG();
  }

  outBufs->bufDesc[0]->numPlanes                          = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].width                 = inNumTracks * FRAME_DEPTH_3D_POINT_CLOUD;
  outBufs->bufDesc[0]->bufPlanes[0].height                = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = outBufs->bufDesc[0]->bufPlanes[0].width;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = 1;
  outBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;

  /*size = outBufs->bufDesc[0]->bufPlanes[0].width  *
  outBufs->bufDesc[0]->bufPlanes[0].height *
  sizeof(SFM_TI_output);*/

  outBufs->bufDesc[0]->bufPlanes[0].buf = OUT_BUF;

  if((outBufs->bufDesc[0]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERROR_MSG();
  }
  return IALG_EOK;
}

int32_t TestApp_ReadInBuf(uint16_t * dst,int32_t currFrameNum, char * fileName, int32_t maxTracks)
{
#if (!TRACK_DATA_FORMAT)
  char     tempStr[200];
  char*    runStrPtr;
  int32_t  numTracks;
  uint16_t trackAge;
  int16_t  feat_x[16];
  int16_t  feat_y[16];
  int16_t  prevTrackIdx;
  SFM_TI_trackInfo* curTrackInfo;
  int32_t k,tempx,tempy,j;
#endif

  int16_t  trackIdx = -1;

#if (!TRACK_DATA_FORMAT)
  fp_in_feat   = fopen(fileName, "r");
#else
  fp_in_feat   = FOPEN(fileName, "rb");
#endif

  if(fp_in_feat == NULL){
    return (trackIdx + 1); 
  }

#if (!DISABLE_FILE_IO)


  /* First 2 bytes represents number of feature points information. After wards
  ONE_FEATURE_INFO_SIZE many feature points information is placed in file.
  */
#if (!TRACK_DATA_FORMAT)
  {
    numTracks = 0;

    prevTrackIdx = 0;
    /*
    * Dummy read to avoid header data parsing.
    */
    fgets(tempStr,200,fp_in_feat);

    while(!feof(fp_in_feat))
      //for(i=0;i<400;i++)
    {

      fgets(tempStr,200,fp_in_feat);

      runStrPtr = tempStr;

      sscanf(runStrPtr,"%hu;%hu;",
        &trackIdx,
        &trackAge);

      if(trackIdx >= MAX_NUM_IN_POINTS)
        break;

      if(trackIdx < 0) {

        printf("\n Seems to be some problem in track data");
        trackAge = __mmin(trackAge,currFrameNum);
      }


      for(k=0;k<trackAge;k++){

        do{
          runStrPtr++;
        }while(runStrPtr[0] != '(');

        sscanf(runStrPtr,"(%d,%d);",
          &tempx,
          &tempy);

        feat_x[k] = tempx;
        feat_y[k] = tempy;

      }

      for(j = prevTrackIdx + 1; j < trackIdx; j++){

        curTrackInfo = (SFM_TI_trackInfo*)dst;
        curTrackInfo += j;
        curTrackInfo->age = 0;

      }

      if(trackAge > 0)  {

        curTrackInfo = (SFM_TI_trackInfo*)dst;
        curTrackInfo += trackIdx;
        curTrackInfo->age = __mmin((trackAge - 1),5);

        curTrackInfo->x[0] = (int16_t)(feat_x[0]  * 1);
        curTrackInfo->x[1] = (int16_t)(feat_x[1]  * 1);
        curTrackInfo->x[2] = (int16_t)(feat_x[2]  * 1);
        curTrackInfo->x[3] = (int16_t)(feat_x[3]  * 1);
        curTrackInfo->x[4] = (int16_t)(feat_x[4]  * 1);
        curTrackInfo->x[5] = (int16_t)(feat_x[5]  * 1);

        curTrackInfo->y[0] = (int16_t)(feat_y[0]  * 1);
        curTrackInfo->y[1] = (int16_t)(feat_y[1]  * 1);
        curTrackInfo->y[2] = (int16_t)(feat_y[2]  * 1);
        curTrackInfo->y[3] = (int16_t)(feat_y[3]  * 1);
        curTrackInfo->y[4] = (int16_t)(feat_y[4]  * 1);
        curTrackInfo->y[5] = (int16_t)(feat_y[5]  * 1);
      }
      else{
        printf("\nSome problem in file io \n");
      }
      prevTrackIdx = trackIdx;
      numTracks++;
    }
  }
  fclose(fp_in_feat);
#else
  FREAD(dst,1,maxTracks*sizeof(SFM_TI_trackInfo),fp_in_feat);
  //FREAD(dst,sizeof(SFM_TI_trackInfo),300,fp_in_feat);
  trackIdx = maxTracks - 1;
  FCLOSE(fp_in_feat);
#endif

#endif


  return (trackIdx + 1);
}

int32_t TestApp_ReadInCameraPrm(float * dstExt,
                                float * dstInt,
                                int32_t currFrameNum,
                                int32_t startFrameNum,
                                char * fileName,
                                int32_t maxFrameNum)
{
  int32_t i;
  char    tempStr[200];
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
    sscanf(&tempStr[i+1],"%f,%f,%f",&dstInt[0],&dstInt[1],&dstInt[2]);

    fgets(tempStr,200,fp_in_cam);
    sscanf(&tempStr[0],"%f,%f,%f",&dstInt[3],&dstInt[4],&dstInt[5]);

    fgets(tempStr,200,fp_in_cam);
    sscanf(&tempStr[0],"%f,%f,%f",&dstInt[6],&dstInt[7],&dstInt[8]);

    for(i=0;i< (extPramStartRow - intPramStartRow - 2 + extPrmSizeInRows * modStartNo);i++) {
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
    fgets(tempStr,200,fp_in_cam);
  }

#if (!DISABLE_FILE_IO)

  /* First 2 bytes represents number of feature points information. After wards
  * ONE_FEATURE_INFO_SIZE many feature points information is placed in file.
  */
  sscanf(&tempStr[i+1],"%f,%f,%f,%f,",&dstExt[0],&dstExt[1],&dstExt[2], &dstExt[3]);
  fgets(tempStr,200,fp_in_cam);
  sscanf(&tempStr[0],"%f,%f,%f,%f,",&dstExt[4],&dstExt[5],&dstExt[6], &dstExt[7]);
  fgets(tempStr,200,fp_in_cam);
  sscanf(&tempStr[0],"%f,%f,%f,%f,",&dstExt[8],&dstExt[9],&dstExt[10], &dstExt[11]);
  if(extPrmSizeInRows == 4){
    fgets(tempStr,200,fp_in_cam);
    sscanf(&tempStr[0],"%f,%f,%f,%f,",&dstExt[12],&dstExt[13],&dstExt[14], &dstExt[15]);
    if(dstExt[15] != 1.0){
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
//#define ENABLE_YUV_WRITE
//#define ENABLE_PLY_WRITE
#define ENABLE_PLY_BIN_WRITE

int32_t TestApp_WriteOutBuf(SFM_TI_output * src,int32_t currFrameNum,
                            int32_t startFrameNum,
                            char * featFileName,char* InImgFileName,
                            char* outImgFileName,int32_t maxFrameNum,
                            int32_t imgWidth, int32_t imgHeight,
                            int32_t outNumPoints)
{
  int32_t  i;
  float    curX,curY,curZ;
  float    curImgx, curImgy;
  int32_t  int_x, int_y;
  float    dmean, dmean2, curDist;
  float    dStdDev,dMin,dMax;
  int32_t  colorMax = 64;
  int32_t  colorMaxToUse = colorMax * 3 / 4;
  int32_t  colorIndex,r,g,b;
  //uint32_t imgSize = (imgWidth*imgHeight*3)/2;
  //uint32_t index;
  char     localString[200];
  SFM_TI_output* localOutPtr;
  TI_FILE* fp_out_bin;
  int32_t  NUM_STEPS = 10;
  float    maxZ4Visulization = 100.0;
#ifdef ENABLE_YUV_WRITE
  if(currFrameNum == startFrameNum) {
    fp_in1   = FOPEN(InImgFileName, "rb");
    fp_out1  = FOPEN(outImgFileName, "wb");
    //imgPtr   = (uint8_t*)malloc(imgSize);

    if(imgSize > MAX_IMG_BUF_SIZE)
      printf("\n Insufficient memory");

    imgPtr   = IMG_BUF;

    if(fp_in1 == NULL){
      printf("\n Could not open the input YUV file");
      exit(0);
    }
    /*FSEEK is not working properly in fast file i/o hence using
    multiple fread.
    */
    FSEEK(fp_in1, (currFrameNum * imgSize), SEEK_SET);

  }
#endif
#ifdef ENABLE_PLY_WRITE
  sprintf(localString,"%s%010d.png.ply",featFileName,(currFrameNum));

  fp_out   = fopen(localString, "w");

  if(fp_out == NULL){
    printf("\n Could not open the output file");
    exit(0);
  }
#endif

#ifdef ENABLE_PLY_BIN_WRITE
  sprintf(localString,"%s%04d.bin",featFileName,(currFrameNum));
  fp_out_bin   = FOPEN(localString, "wb");

  if(fp_out_bin == NULL){
    printf("\n Could not open the output file");
    exit(0);
  }
#endif

  if(outNumPoints)
    dist     = (float*)malloc(outNumPoints * sizeof(float));

  dmean       = 0;
  dmean2      = 0;
  localOutPtr = src;

  for(i=0;i<outNumPoints;i++) {

    curX = localOutPtr->point3dX;
    curY = localOutPtr->point3dY;
    curZ = localOutPtr->point3dZ;

    curDist = curX*curX + curY*curY + curZ*curZ;
    dmean2 += curDist;
#ifdef DSP_INTRINSICS
    curDist = (curDist* _rsqrsp(curDist));
#else
    curDist = sqrtf(curDist);
#endif
    dist[i] = curDist;
    dmean  += curDist;

    localOutPtr ++;
  }

  dmean   = outNumPoints? dmean / outNumPoints : 0;
  dmean2  = outNumPoints? dmean2 / outNumPoints : 0;

  dStdDev = dmean2 - dmean*dmean;
#ifdef DSP_INTRINSICS
  dStdDev = (dStdDev * _rsqrsp (dStdDev));
#else
  dStdDev = sqrtf(dStdDev);
#endif

  dMin    = dmean - 3*dStdDev;
  dMax    = dmean + 3*dStdDev;
  dMax    = (dMin == dMax)? dMin + 1 : dMax;

  //clip range of depth into a certain range for color display.
  dMax = (dMax < 150.0f) ? dMax : 150.0f; //150 meters max
  dMin = (dMin > 0.0f) ? dMin : 0.0f;   //0 meters min

  dMin = 0.0;
  dMax = 192.0;

#if (!DISABLE_FILE_IO)

#ifdef ENABLE_YUV_WRITE
#if (!HOST_EMULATION)
  Cache_WbInvAll();
#endif
  FREAD(imgPtr,1,imgSize,fp_in1);
#endif

#ifdef ENABLE_PLY_WRITE
  TestApp_WritePlyHeader(fp_out,outNumPoints);
#endif

  localOutPtr = src;

  for(i=0;i< outNumPoints; i++) {
    
    if(0){  
      curDist = dist[i];
      curDist = __mmin(curDist,maxZ4Visulization);
      colorIndex = (curDist * NUM_STEPS / maxZ4Visulization);
      colorIndex = (colorIndex * colorMaxToUse) / NUM_STEPS;
    }else{
      //curDist = localOutPtr->point3dZ;
      curDist = dist[i];
      colorIndex = (curDist - dMin) * colorMaxToUse / (maxZ4Visulization - dMin);
    }
    

    colorIndex = (colorIndex > 0) ? colorIndex : 0;
    colorIndex = (colorIndex < colorMaxToUse) ?  colorIndex : colorIndex;

    //colorIndex = 63;
    //select the color
    r = HSV_COLOR_MAP[colorIndex][0]*UCHAR_MAX;
    g = HSV_COLOR_MAP[colorIndex][1]*UCHAR_MAX;
    b = HSV_COLOR_MAP[colorIndex][2]*UCHAR_MAX;

    //y  = (( (66 * r)  + (129 * g) + (25 * b)  + 128) >> 8) + 16;
    //cb = ((-(38 * r)  - (74 * g)  + (112 * b) + 128) >> 8) + 128;
    //cr = (( (112 * r) - (94 * g)  - (18 * b)  + 128) >> 8) + 128;

    curX = localOutPtr->point3dX;
    curY = localOutPtr->point3dY;
    curZ = localOutPtr->point3dZ;

    curImgx = localOutPtr->point2dX;
    curImgy = localOutPtr->point2dY;

    int_x = curImgx;
    int_y = curImgy;

    int_x &= 0x7FFFFFFE;
    int_y &= 0x7FFFFFFE;

#ifdef ENABLE_PLY_WRITE
    // format is X Y Z R G B x y frmid trackID
    fprintf(fp_out,"%8.2f %8.2f %8.2f %6d %6d %6d %8.2f %8.2f %6d %6d\n",
      curX,
      curY,
      curZ,
      0x0,
      0x0,
      0x0,
      curImgx,
      curImgy,
      localOutPtr->frmId,
      localOutPtr->trackId
      );
#endif

#ifdef ENABLE_YUV_WRITE
    if((int_x > 0) && (int_y >0) &&
      (int_x < (imgWidth -1))   &&
      (int_y < (imgHeight-1))   &&
      (curDist>dMin)           &&
      (curDist<dMax)){

        index = int_y*imgWidth + int_x;

        imgPtr[index    ] = y;
        imgPtr[index + 1] = y;
        imgPtr[index + imgWidth  ] = y;
        imgPtr[index + imgWidth + 1] = y;

        index = (imgWidth*imgHeight) + ((int_y*imgWidth) >> 2) + (int_x >> 1);

        imgPtr[index] = cb;

        index = (imgWidth*imgHeight) + ((imgWidth*imgHeight)>>2) + ((int_y*imgWidth) >> 2) + (int_x >> 1);

        imgPtr[index] = cr;

    }
#endif
    localOutPtr++;
  }
#ifdef ENABLE_YUV_WRITE

#if (!HOST_EMULATION)
  Cache_WbInvAll();
#endif

  FWRITE(imgPtr,1,imgSize,fp_out1);
#endif

#ifdef ENABLE_PLY_BIN_WRITE

#if (!HOST_EMULATION)
  Cache_WbInvAll();
#endif

  FWRITE(src,1,sizeof(SFM_TI_output)*outNumPoints,fp_out_bin);
#endif

#endif

  if(outNumPoints)
    free(dist);

#ifdef ENABLE_PLY_WRITE
  fclose(fp_out);
#endif

#ifdef ENABLE_PLY_BIN_WRITE
  FCLOSE(fp_out_bin);
#endif

  if(currFrameNum == (maxFrameNum - 1)){
#ifdef ENABLE_YUV_WRITE
    FCLOSE(fp_out1);
    FCLOSE(fp_in1);
#endif
  }

  return (0);
}

#if (!HOST_EMULATION)
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
#endif //!HOST_EMULATION
void TestApp_WritePlyHeader(FILE* fp_out, int32_t outNumPoints)
{
  fprintf(fp_out,"ply\n");
  fprintf(fp_out,"format ascii 1.0\n");
  fprintf(fp_out,"comment PCL generated by ticv using rply\n");
  fprintf(fp_out,"element vertex %d\n",outNumPoints);
  fprintf(fp_out,"property float x\n");
  fprintf(fp_out,"property float y\n");
  fprintf(fp_out,"property float z\n");
  fprintf(fp_out,"property uchar red\n");
  fprintf(fp_out,"property uchar green\n");
  fprintf(fp_out,"property uchar blue\n");
  fprintf(fp_out,"property float x2D\n");
  fprintf(fp_out,"property float y2D\n");
  fprintf(fp_out,"property int frame\n");
  fprintf(fp_out,"property int track\n");
  fprintf(fp_out,"element camera 1\n");
  fprintf(fp_out,"property float view_px\n");
  fprintf(fp_out,"property float view_py\n");
  fprintf(fp_out,"property float view_pz\n");
  fprintf(fp_out,"property float x_axisx\n");
  fprintf(fp_out,"property float x_axisy\n");
  fprintf(fp_out,"property float x_axisz\n");
  fprintf(fp_out,"property float y_axisx\n");
  fprintf(fp_out,"property float y_axisy\n");
  fprintf(fp_out,"property float y_axisz\n");
  fprintf(fp_out,"property float z_axisx\n");
  fprintf(fp_out,"property float z_axisy\n");
  fprintf(fp_out,"property float z_axisz\n");
  fprintf(fp_out,"property float focal\n");
  fprintf(fp_out,"property float scalex\n");
  fprintf(fp_out,"property float scaley\n");
  fprintf(fp_out,"property float centerx\n");
  fprintf(fp_out,"property float centery\n");
  fprintf(fp_out,"property int viewportx\n");
  fprintf(fp_out,"property int viewporty\n");
  fprintf(fp_out,"property float k1\n");
  fprintf(fp_out,"property float k2\n");
  fprintf(fp_out,"end_header\n");

}
#if 0
int32_t sfmCompare(ssfm_Config * testcaseParams) {

  SFM_TI_output* refInfo;
  SFM_TI_output* testInfo;
  SFM_TI_output* curInfo;
  SFM_TI_output* curInfo_2;

  uint8_t refFileName[FILE_NAME_SIZE];
  uint8_t testFileName[FILE_NAME_SIZE];
  uint8_t reportFileName[FILE_NAME_SIZE];

  FILE*   fp_ref;
  FILE*   fp_test;
  FILE*   fp_report;

  int32_t startFrame   = testcaseParams[0].startFrame;
  int32_t endFrame     = startFrame + testcaseParams[0].maxFrames;
  int32_t frameIdx;

  int32_t refTotalFeat;
  int32_t testTotalFeat, matchTotalFeat;;
  int32_t tempR,tempG,tempB;

  uint8_t curString[200];
  int32_t numInliers5, numInliers10, numInliers15,testOrphans, refOrphans;
  int32_t prevTrackId, prevFrmId,i,j,holeTracks;

  float maxDiff, point3dX, point3dY, point3dZ, point2dX, point2dY;
  int32_t frmId, trackId;
  int16_t refFrmId, refTrackId, testFrmId, testTrackId;
  int32_t curTotalPts;
  float dist1, dist2;

  refInfo  = (SFM_TI_output*)malloc(sizeof(SFM_TI_output)*MAX_NUM_OUT_POINTS);
  testInfo = (SFM_TI_output*)malloc(sizeof(SFM_TI_output)*MAX_NUM_OUT_POINTS);

  sprintf((char*)&reportFileName[0],"%s\compareResult.txt",testcaseParams[0].compareRsultPath);

  fp_report = fopen((const char*)&reportFileName[0],"w");

  if(fp_report == NULL)
    exit(0);

  fprintf(fp_report,"frameIdx          testTotalPts        refTotalPts         inlier(+/- 0.5)     inlier(+/- 1.0)     inlier(+/- 1.5)     %testOrphans        %refOrphans\n");

  // Read the data from file and put into memory
  for(frameIdx = startFrame;frameIdx <  (endFrame - VLIB_TRIANG_MAX_POINTS_IN_TRACK); frameIdx++){

    sprintf((char*)&refFileName[0],"%s(%d).ply",testcaseParams[0].refFeatFileName, (frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK -1));
    fp_ref = fopen((const char*)&refFileName[0],"r");

    if(fp_ref == NULL)
      exit(0);

    sprintf((char*)testFileName,"%s%010d.png.ply",testcaseParams[0].outFeatFileName, (frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK -1));
    fp_test = fopen((const char*)&testFileName[0],"r");

    if(fp_test == NULL)
      exit(0);

    fgets((char*)curString,200,fp_ref);
    fgets((char*)curString,200,fp_ref);
    fgets((char*)curString,200,fp_ref);
    fgets((char*)curString,200,fp_ref);

    sscanf((char*)&curString[15],"%d",&refTotalFeat);



    fgets((char*)curString,200,fp_test);
    fgets((char*)curString,200,fp_test);
    fgets((char*)curString,200,fp_test);
    fgets((char*)curString,200,fp_test);

    sscanf((char*)&curString[15],"%d",&testTotalFeat);

    if(refTotalFeat == 0){
      fprintf(fp_report,"%3d          %10d          %10d Reference Triangulation Failed\n",
        (frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK - 1), testTotalFeat, refTotalFeat);
      continue;
    }

    if(testTotalFeat == 0){
      fprintf(fp_report,"%3d          %10d          %10d Test Triangulation Failed\n",
        (frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK - 1), testTotalFeat, refTotalFeat);
      continue;
    }

    numInliers5    = 0;
    numInliers10    = 0;
    numInliers15   = 0;
    testOrphans    = 0;
    refOrphans     = 0;
    matchTotalFeat = 0;

    for(i =0 ;i < 37- 4 -1; i++){
      fgets((char*)curString,200,fp_ref);
      fgets((char*)curString,200,fp_test);
    }

    curInfo      = refInfo;
    curInfo_2    = testInfo;

    for(i = 0; i < MAX_NUM_OUT_POINTS; i++){
      curInfo->frmId   = -1;
      curInfo_2->frmId = -1;
      curInfo++;
      curInfo_2++;
    }

    curInfo      = refInfo;
    prevTrackId  = -1;
    curTotalPts  = 0;
    prevFrmId    = frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK -1;
    fgets((char*)curString,200,fp_ref);

    for(i = 0;i < refTotalFeat; i++) {

      fgets((char*)curString,200,fp_ref);

      sscanf((char*)&curString[0],"%f %f %f %d %d %d %f %f %d %d\n",
        &point3dX,
        &point3dY,
        &point3dZ,
        &tempR,
        &tempG,
        &tempB,
        &point2dX,
        &point2dY,
        &frmId,
        &trackId
        );

      if((frmId > (frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK - 1)) || (frmId < (frameIdx + 1)))
        break;

      holeTracks = (prevFrmId - frmId)*MAX_NUM_IN_POINTS + (trackId - prevTrackId - 1);

      if(holeTracks > MAX_NUM_IN_POINTS)
        printf("\n something went wrong");

      for(j = 0; j < holeTracks; j++) {
        curInfo->frmId = -1;
        curInfo++;
        curTotalPts++;
      }

      curInfo->point3dX  = point3dX;
      curInfo->point3dY  = point3dY;
      curInfo->point3dZ  = point3dZ;

      curInfo->point2dX  = point2dX;
      curInfo->point2dY  = point2dY;

      curInfo->frmId     = frmId;
      curInfo->trackId   = trackId;

      prevTrackId        = trackId;
      prevFrmId          = frmId;
      curInfo++;
      curTotalPts++;
      if(curTotalPts == MAX_NUM_OUT_POINTS)
        break;
    }

    curInfo      = testInfo;
    prevTrackId  = -1;
    curTotalPts  = 0;

    prevFrmId    = frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK - 1;

    fgets((char*)curString,200,fp_test);

    for(i = 0;i < testTotalFeat; i++) {
      fgets((char*)curString,200,fp_test);

      sscanf((char*)&curString[0],"%f %f %f %d %d %d %f %f %d %d\n",
        &point3dX,
        &point3dY,
        &point3dZ,
        &tempR,
        &tempG,
        &tempB,
        &point2dX,
        &point2dY,
        &frmId,
        &trackId
        );

      if((frmId > (frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK - 1)) || (frmId < (frameIdx + 1)))
        break;

      holeTracks = (prevFrmId - frmId)*MAX_NUM_IN_POINTS + (trackId - prevTrackId - 1);

      if(holeTracks > MAX_NUM_IN_POINTS)
        printf("\n something went wrong");

      for(j = 0; j < holeTracks; j++) {
        curInfo->frmId = -1;
        curInfo++;
        curTotalPts++;
      }

      curInfo->point3dX  = point3dX;
      curInfo->point3dY  = point3dY;
      curInfo->point3dZ  = point3dZ;

      curInfo->point2dX  = point2dX;
      curInfo->point2dY  = point2dY;

      curInfo->frmId     = frmId;
      curInfo->trackId   = trackId;

      prevTrackId        = trackId;
      prevFrmId          = frmId;
      curInfo++;
      curTotalPts++;
      if(curTotalPts == MAX_NUM_OUT_POINTS)
        break;
    }

    curInfo   = refInfo;
    curInfo_2 = testInfo;

    for(i = 0; i < MAX_NUM_OUT_POINTS; i++){

      refFrmId      = curInfo->frmId;
      refTrackId    = curInfo->trackId;

      testFrmId     = curInfo_2->frmId;
      testTrackId   = curInfo_2->trackId;


      if((refFrmId != -1) && (testFrmId != -1))
      {
        // test and ref both has generated a 3D point from this track

        /* 3D points comparison
        */
        dist1  = ((curInfo->point3dX - curInfo_2->point3dX)*(curInfo->point3dX - curInfo_2->point3dX)) +
          ((curInfo->point3dY - curInfo_2->point3dY)*(curInfo->point3dY - curInfo_2->point3dY)) +
          ((curInfo->point3dZ - curInfo_2->point3dZ)*(curInfo->point3dZ - curInfo_2->point3dZ));

        dist1  = sqrtf(dist1);

        dist2  = ((curInfo->point2dX - curInfo_2->point2dX)*(curInfo->point2dX - curInfo_2->point2dX)) +
          ((curInfo->point2dY - curInfo_2->point2dY)*(curInfo->point2dY - curInfo_2->point2dY)) ;

        dist2  = sqrtf(dist2);


        if((dist1 < .5) && (dist2 < .5))
          numInliers5++;

        if((dist1 < 1.0) && (dist2 < 1.0))
          numInliers10++;

        if((dist1 < 1.5) && (dist2 < 1.5))
          numInliers15++;

        matchTotalFeat++;

      }else if(refFrmId != -1) {
        refOrphans++;
      }else if(testFrmId != -1){
        testOrphans++;
      } else {
        // feature dropped by ref and test both.
      }

      curInfo++;
      curInfo_2++;
    }

    fprintf(fp_report,"%3d          %10d          %10d          %10.2f          %10.2f          %10.2f          %10d          %10d\n",
      (frameIdx + VLIB_TRIANG_MAX_POINTS_IN_TRACK - 1), testTotalFeat, refTotalFeat,
      ((numInliers5*100.0)/matchTotalFeat),
      ((numInliers10*100.0)/matchTotalFeat),
      ((numInliers15*100.0)/matchTotalFeat),
      testOrphans,
      refOrphans
      );

    fclose(fp_ref);
    fclose(fp_test);
  }
  fclose(fp_report);
  //fclose(refInfo);
  //fclose(testInfo);
  return(0);
}

void host_file_io_ti_init(){
  int32_t i;
  /* making all packets as available
  */
  for(i = 0; i < HOST_MALLOC_TOT_PACKET; i++){
    SCRATCH_PACKET_VALIDITY[i] = 0x0;
  }
}

void* host_file_io_ti_malloc(int32_t size){

  int32_t  contSize   = 0;
  int32_t  numPackets = 0;
  int32_t  baseIndx   = 0;
  void*    baseAddr;
  int32_t i;

  baseAddr   = &SCRATCH_NON_CACHED[baseIndx][0];

  for(i = 0; i < HOST_MALLOC_TOT_PACKET; i++){

    if(SCRATCH_PACKET_VALIDITY[i] == 0x0){

      contSize += HOST_MALLOC_PACKET_SIZE;
      numPackets++;
    }else{

      contSize   = 0;
      numPackets = 0;
      baseIndx   = i + 1;
      baseAddr   = &SCRATCH_NON_CACHED[baseIndx][0];
    }

    if(contSize >= size)
      break;

  }

  if(i == HOST_MALLOC_TOT_PACKET){
    printf("\n Could not allocate memory for host file i/o \n");
    return(0x0);
  }


  for(i = baseIndx; i < baseIndx + numPackets; i++)
    SCRATCH_PACKET_VALIDITY[i] = 1;

  /* Indication for freeing up the packets. At the time of freeing
  * total number of packets to be freed to be known.
  */
  SCRATCH_PACKET_VALIDITY[baseIndx] = numPackets;

  return(baseAddr);
}

void host_file_io_ti_free(void* ptr){

  int32_t numPackets;
  int32_t baseIndx;
  int32_t i;

  for(i = 0; i < HOST_MALLOC_TOT_PACKET; i++){
    if(ptr == &SCRATCH_NON_CACHED[i][0])
      break;
  }

  baseIndx = i;

  if( i >= HOST_MALLOC_TOT_PACKET)
    printf("\n Error");

  numPackets = SCRATCH_PACKET_VALIDITY[baseIndx];

  for(i = baseIndx; i < baseIndx + numPackets; i++){
    SCRATCH_PACKET_VALIDITY[i] = 0x0;
  }

  if( i >= HOST_MALLOC_TOT_PACKET)
    printf("\n Error");
}
#endif
