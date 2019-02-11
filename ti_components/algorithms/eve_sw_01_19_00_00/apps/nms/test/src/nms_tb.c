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


/** @file nms_tb.c
*
*  @brief  This file contains test code for NMS applet
*
*
*  @date   July 2014
*
*  Description
*    This file contains test code to validate the frame level applet NMS.
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
#include "nms_config.h"
#include "xdais_types.h"
#include "inms_ti.h"
#include "ti_file_io.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "vcop_nonMaxSuppress_mxn_16s_c.h"
#include "vcop_bin_image_to_list_cn.h"

#define ENABLE_OUTPUT_DUMP 0
#define ENABLE_TRACES 0
#define ENABLE_PROFILE 1

#define ALIGN_T0_32(x) (((x+31)/32)*32)

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")


#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (14*1024)


extern uint64_t gTest_TI_profileSctm[2], gTest_TI_profileTsc;

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];


TIMemObject memObj_DMEM;

int32_t TestApp_Nms16sReference
(
    NMS_TI_CreateParams   * createParams,
    NMS_TI_InArgs             * inArgs,
    IVISION_InBufs *inBufs,
    uint32_t       *outputListXy,
    uint32_t       *numListElems
)
{
  int32_t status = 0;
  uint8_t * nmsBinPackOutBuf = NULL;

  int16_t   *inImgBuf;
  uint8_t   elemSize;
  uint16_t  inImgWidth;
  uint16_t  inImgHeight;
  uint16_t  inImgStride;

  uint16_t  outImgWidth;
  uint16_t  outImgHeight;
  uint16_t  outImgStride;

  uint32_t  upperLeftXy = 0;

  elemSize = createParams->inputByteDepth;

  inImgBuf = (short *) inBufs->bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf;

  inImgWidth  = inBufs->bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width / elemSize;
  inImgHeight = inBufs->bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height;
  inImgStride = inBufs->bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width / elemSize;

  outImgWidth   = (inImgWidth - (inArgs->windowWidth - 1));
  outImgHeight  = inImgHeight - (inArgs->windowHeight - 1);
  outImgStride  = outImgWidth;

  nmsBinPackOutBuf = (uint8_t *) malloc (outImgWidth * outImgHeight / 8);
  if ( nmsBinPackOutBuf == NULL)
  {
    status = -1;
    PRINT_ERRORE_MSG();
    goto EXIT;
  }

  vcop_nonMaxSuppress_mxn_16sbitPack_cn(inImgBuf,
                        nmsBinPackOutBuf,
                        inImgWidth,
                        inImgHeight,
                        inImgStride,
                        outImgStride / 8,
                        inArgs->windowWidth,
                        inArgs->windowHeight,
                        inArgs->nmsThreshold);

  vcop_bin_image_to_list_cn(nmsBinPackOutBuf,
                        &upperLeftXy,
                        outputListXy,
                        numListElems,
                        outImgWidth,
                        outImgHeight,
                        outImgStride,
                        0,
                        1);


EXIT:
  if (nmsBinPackOutBuf)
  {
    free(nmsBinPackOutBuf);
  }
  return status;
}



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

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

int32_t TestApp_AllocateBufs(IVISION_InBufs * inBufs,
                                 IVISION_InBufs * outBufs)
{
  uint32_t i, j;
  int32_t status = 0;
  for ( i  = 0 ; i < inBufs->numBufs ; i++)
  {
    for ( j  = 0 ; j < inBufs->bufDesc[i]->numPlanes ; j++)
    {
      inBufs->bufDesc[i]->bufPlanes[j].buf = malloc(inBufs->bufDesc[i]->bufPlanes[j].width *
                                                         inBufs->bufDesc[i]->bufPlanes[j].height);
      if ( inBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
      {
        TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return -1;
      }
    }
  }

  for ( i  = 0 ; i < outBufs->numBufs ; i++)
  {
    for ( j  = 0 ; j < outBufs->bufDesc[i]->numPlanes ; j++)
    {
      outBufs->bufDesc[i]->bufPlanes[j].buf = malloc(outBufs->bufDesc[i]->bufPlanes[j].width *
                                                         outBufs->bufDesc[i]->bufPlanes[j].height);
      if ( outBufs->bufDesc[i]->bufPlanes[j].buf == NULL )
      {
        TEST_PRINTF("Malloc failed Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
        return -1;
      }
    }
  }

  return status;
}

int32_t TestApp_FreeBufs(IVISION_InBufs * inBufs,
                                 IVISION_InBufs * outBufs)
{
  uint32_t i, j;
  int32_t status = 0;
  for ( i  = 0 ; i < inBufs->numBufs ; i++)
  {
    for ( j  = 0 ; j < inBufs->bufDesc[i]->numPlanes ; j++)
    {
      if (inBufs->bufDesc[i]->bufPlanes[j].buf != NULL)
      {
        free(inBufs->bufDesc[i]->bufPlanes[j].buf);
        inBufs->bufDesc[i]->bufPlanes[j].buf = NULL;
      }
    }
  }

  for ( i  = 0 ; i < outBufs->numBufs ; i++)
  {
    for ( j  = 0 ; j < outBufs->bufDesc[i]->numPlanes ; j++)
    {
      if (outBufs->bufDesc[i]->bufPlanes[j].buf != NULL)
      {
        free(outBufs->bufDesc[i]->bufPlanes[j].buf);
        outBufs->bufDesc[i]->bufPlanes[j].buf = NULL;
      }
    }
  }

  return status;
}

int32_t nmsTest(sNms_Config * testcaseParams)
{
  uint32_t i, idx;
#if (ENABLE_PROFILE)
  uint64_t     profile_tsc, profile_sctm, profile_create_tsc;
#endif
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;
  uint32_t seed;
  uint32_t frameNum;
  char  *statusStr = NULL;
  int32_t fail;
  TI_FILE *fp_in = NULL;
#if ENABLE_OUTPUT_DUMP
  TI_FILE * fp_out = NULL;
#endif

  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  NMS_TI_CreateParams   createParams;

  NMS_TI_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc[NMS_TI_BUFDESC_IN_TOTAL];
  IVISION_BufDesc   *inBufDescList[NMS_TI_BUFDESC_IN_TOTAL];

  NMS_TI_OutArgs   outArgs;
  IVISION_OutBufs     outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc[NMS_TI_BUFDESC_OUT_TOTAL];
  IVISION_BufDesc   *outBufDescList[NMS_TI_BUFDESC_OUT_TOTAL];

  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;
  uint8_t     elemSize;

  uint32_t *outputListXyRef = NULL;
  uint32_t numListElemRef;

  NMS_TI_ControlInArgs  ctrlInArgs;
  NMS_TI_ControlOutArgs ctrlOutArgs;


  outArgs.iVisionOutArgs.size = sizeof(NMS_TI_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(NMS_TI_InArgs);

  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);


#if (ENABLE_PROFILE)
    profiler_init();
#endif

  /*-----------------------------------------------------------------
      Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs   = NMS_TI_BUFDESC_IN_TOTAL;
  outBufs.numBufs  = NMS_TI_BUFDESC_OUT_TOTAL;

  for(i = 0 ; i < NMS_TI_BUFDESC_IN_TOTAL ;i++)
  {
    inBufDescList[i]     = &inBufDesc[i];
  }

  for(i = 0 ; i < NMS_TI_BUFDESC_OUT_TOTAL ;i++)
  {
    outBufDescList[i]     = &outBufDesc[i];
  }

  /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
  /*-----------------------------------------------------------------
  Query alogorithm memory requirement using standard IALG interface
  -----------------------------------------------------------------*/



  createParams.inputByteDepth = testcaseParams->inputByteDepth;

#if (ENABLE_PROFILE)
    profiler_initStack(profiler_getSP());
#endif

  elemSize = createParams.inputByteDepth;

  numMemRec = NMS_TI_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = NMS_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("NMS Applet Create Done\n");
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

#if (ENABLE_PROFILE)
  profiler_start();
#endif


  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the alocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  status = NMS_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));


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
  TEST_PRINTF("NMS  Applet Init Done\n");
#endif


  idx = NMS_TI_BUFDESC_IN_IMAGEBUFFER;
  inBufs.bufDesc[idx]->numPlanes                          = 1;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams->imgStride * elemSize;
  inBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams->imgHeight;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams->imgWidth * elemSize;
  inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams->imgHeight;
  inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
  inBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

  ctrlInArgs.imageBuf = &inBufs;
  ctrlInArgs.windowWidth = testcaseParams->windowWidth;
  ctrlInArgs.windowHeight = testcaseParams->windowHeight;

  /* Control call need to be called repeatively only when image dimensions are changed otherwise it should be called once */
  status = handle->ivision->algControl((IVISION_Handle)handle, 0,(IALG_Params *) &ctrlInArgs ,(IALG_Params *) &ctrlOutArgs );
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }


  inBufs.bufDesc[idx]->bufPlanes[0].buf = malloc( (ctrlOutArgs.effectiveImageWidth + (testcaseParams->windowWidth - 1)) *
                    (ctrlOutArgs.effectiveImageHeight + (testcaseParams->windowHeight - 1)) * elemSize);

  if ( inBufs.bufDesc[idx]->bufPlanes[0].buf  == NULL )
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }


  idx = NMS_TI_BUFDESC_OUT_LIST_XY;
  outBufs.bufDesc[idx]->numPlanes                          = 1;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams->imgWidth * testcaseParams->imgHeight *
                                                              sizeof(uint32_t) / (testcaseParams->windowWidth * testcaseParams->windowHeight);
                                                              ;
  outBufs.bufDesc[idx]->bufPlanes[0].height                = 1;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = outBufs.bufDesc[idx]->bufPlanes[0].width;
  outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = 1;
  outBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0;
  outBufs.bufDesc[idx]->bufPlanes[0].buf                   = NULL;

  outBufs.bufDesc[idx]->bufPlanes[0].buf = malloc(outBufs.bufDesc[idx]->bufPlanes[0].width *  outBufs.bufDesc[idx]->bufPlanes[0].height);

  if ( outBufs.bufDesc[idx]->bufPlanes[0].buf == NULL )
  {
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }

  outputListXyRef = (uint32_t *) malloc (outBufs.bufDesc[idx]->bufPlanes[0].width * outBufs.bufDesc[idx]->bufPlanes[0].height);

  if ( outputListXyRef == NULL)
   {
     PRINT_ERRORE_MSG();
     goto EXIT_LOOP;
   }


  inArgs.iVisionInArgs.subFrameInfo = 0;
  inArgs.iVisionInArgs.size                  = sizeof(NMS_TI_InArgs);
  inArgs.windowWidth    = testcaseParams->windowWidth;
  inArgs.windowHeight   = testcaseParams->windowHeight;
  inArgs.nmsThreshold   = testcaseParams->nmsThreshold;

  for ( frameNum = 0 ; frameNum < testcaseParams->numFrames ; frameNum++ )
  {

    if ( strcmp((const char *)testcaseParams->inputImage, ""))
    {
      uint32_t frameSize;
      fp_in = FOPEN((const char *)testcaseParams->inputImage, "rb");

      if(fp_in == NULL)
      {
          TEST_PRINTF("Failed to open input file: %s.\n", testcaseParams->inputImage);
          return -1;
      }
      frameSize = inBufs.bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width *
              inBufs.bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].height * elemSize;

      FSEEK(fp_in, frameNum * frameSize, SEEK_SET);
      FREAD(inBufs.bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf,
                    frameSize, 1, fp_in);

      FCLOSE(fp_in);
    }
    else
    {
      uint8_t  * ptr  = (uint8_t *) inBufs.bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].buf;
      int16_t  * iptr16;
      int32_t  * iptr32;
      int32_t   j;
      seed = (testcaseParams->randSeed == 0) ? _tsc_gettime() : testcaseParams->randSeed;
      srand(seed);

      for ( i = 0; i < testcaseParams->imgHeight; i++ )
      {
        for ( j = 0 ; j < testcaseParams->imgWidth; j++)
        {
          if ( createParams.inputByteDepth == NMS_TI_INPUT_BYTE_DEPTH_16BIT )
          {
            iptr16 = (int16_t *)ptr;
            iptr16[j+ (i * testcaseParams->imgStride)] = rand() % 0xFFFFU;
          }
          else
          {
            iptr32 = (int32_t *)ptr;
            iptr32[j+ (i * testcaseParams->imgStride)] = rand() % 0xFFFFFFFFU;
          }
        }
      }
    }

#if ENABLE_TRACES
    TEST_PRINTF("Processing started for frame %d \n",0);
#endif

#if (ENABLE_PROFILE)
      profiler_start();
#endif

    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

#if (ENABLE_PROFILE)
      profiler_end_print(1);

      profile_tsc  = gTest_TI_profileTsc;
      profile_sctm = gTest_TI_profileSctm[0];
#endif

#if ENABLE_TRACES
    TEST_PRINTF("TSC Cycles : SCTM %12d :% 12d\n", profile_tsc,profile_sctm);
#endif

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
  }
#if ENABLE_TRACES
    TEST_PRINTF("Processing Completed for frame %d \n",0);
#endif

    TestApp_Nms16sReference(
      &createParams,
      &inArgs,
      &inBufs,
      outputListXyRef,
      &numListElemRef
    );

    fail = 0;

    if ( numListElemRef == outArgs.numListPoints )
    {
      fail = memcmp(outputListXyRef, outBufs.bufDesc[0]->bufPlanes[0].buf,numListElemRef * sizeof(uint32_t) );

    }
    else
    {
      fail = -1;
    }

    statusStr = fail ? "FAILED":"PASSED";


    profiler_printStatus(fail);

#if (ENABLE_PROFILE)
TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
  "Algorithm", "Status", "BaseWidth", "BaseHeight","NumLevels", "MegaCycPerFr", \
  "MegaCycPerSec(30Fr)", "TotalCycPerPix", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");
#if (VCOP_HOST_EMULATION)
  profile_sctm = 1;
  profile_tsc = 1;
#endif

TEST_PRINTF("%-20s %10s %10d %10d %10d %15.2f %20.2f %14.2f %17.2f %16.2f \
    Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
    "Stage 1",statusStr, testcaseParams->imgWidth,
    testcaseParams->imgHeight,\
    1, (profile_tsc/1000000.0), 30*(profile_tsc/1000000.0),\
    (profile_tsc)/(float)((testcaseParams->imgWidth - testcaseParams->windowWidth) *
              (testcaseParams->imgHeight - testcaseParams->windowHeight)),\
    (profile_sctm)/(float)((testcaseParams->imgWidth - testcaseParams->windowWidth) *
              (testcaseParams->imgHeight - testcaseParams->windowHeight)),\
    (profile_tsc/500000.0), (profile_create_tsc)/1000000.0);

#endif
    fflush(stdout);

#if ENABLE_OUTPUT_DUMP
    if(strcmp((const char *)testcaseParams->outputListXY, ""))
    {
      fp_out = FOPEN((const char*)testcaseParams->outputListXY, "wb+");


      if(fp_out != NULL)
      {

        FWRITE(outBufs.bufDesc[0]->bufPlanes[0].buf , outArgs.numListPoints * sizeof(uint32_t),
                          1, fp_out);

        FCLOSE(fp_out);
      }
      else
      {
        TEST_PRINTF("Failed to open Output file.\n");
      }
    }
#endif
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

    if ( outputListXyRef)
    {
      free(outputListXyRef);
      outputListXyRef = NULL;
    }

    TestApp_FreeBufs(&inBufs, &outBufs);

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

  report_printAppletInfo((int8_t *)"NMS_TI_VISION");

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
      status = readparamfile(configFile, &gsTokenMap_nms[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }
      profiler_testCaseInfo((int8_t *)gConfig_nms[0].testCaseName, (int8_t *)gConfig_nms[0].desc,
                            gConfig_nms[0].performanceTestcase);
      printparams(&gsTokenMap_nms[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gConfig_nms[0]),
                            sizeof(sNms_Config));

      /* Validate the applet */
      status = nmsTest(&gConfig_nms[0]);
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



