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


/** @file feature_plane_comp_tb.c
*
*  @brief  This file contains test code for FAST9 corner detect applet
*
*
*  @date   Dec 2013
*
*  Description
*    This file contains test code to validate the frame level applet fast9 corner detect.
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
#include "filter_2d_config.h"
#include "xdais_types.h"
#include "ifilter_2d_ti.h"

#include "ti_mem_manager.h"
#include "eve_profile.h"
#include "vcop_contrast_stretching_cn.h"
#include "ti_file_io.h"

#define ENABLE_OUTPUT_DUMP 0
#define ENABLE_TRACES 0
#define ALIGN_T0_32(x) (((x+31)/32)*32)

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

#define PRINT_ERRORE_MSG()  TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (20*1024)

#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
/* This will be used for allocation of memory in DMEM*/
uint8_t DMEM_SCRATCH[DMEM_SIZE];


TIMemObject memObj_DMEM;

#define NUM_HISTO_BINS (256)
#define SIZE_HISTO_8_COPY (NUM_HISTO_BINS * sizeof(uint32_t) * 8)
#define SIZE_HISTOGRAM    (NUM_HISTO_BINS * sizeof(uint32_t))

void vcop_yuv420_fir2d_separable_y_cn
(
    uint8_t *        inputPtr,     // input data pointer
    uint8_t *        coefPtr,    // horizontal coef data pointer
    unsigned short   blkw,         // width of input block, in elements
    unsigned short   lofst,        // offset between input lines, in elems
    unsigned short   blkh,         // height of input block
    unsigned short   numCoef,     // width of coef block, in elements
    uint8_t *        outputPtr,   // output data pointer
   unsigned short    rndBits      // bit position for rounding
)
{
  uint32_t i,j,k,l;
  uint8_t * ptr;
  uint32_t inData;
  uint32_t coefVal;
  uint32_t outData;

  for ( i = 0; i < blkh - (numCoef - 1); i++)
  {
    for ( j = 0 ; j < blkw - (numCoef - 1); j++)
    {

      ptr = &inputPtr[j + ( i * lofst)];
      outData = 0;
      for ( k = 0 ; k < numCoef ; k++)
      {
        for ( l = 0 ; l < numCoef ; l++)
        {
          inData = ptr[l + k * lofst];
          coefVal = coefPtr[l + k * numCoef];
          outData += inData * coefVal;

        }
      }
      outputPtr[j + ( i * blkw)] = ( outData + (1<< (rndBits - 1))) >> rndBits ;
    }
  }
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

int32_t TestApp_ReadInBufs(IVISION_InBufs * inBufs,int32_t currFrameNum, char * fileName)
{
  TI_FILE * fp;
  int32_t lumaSize    = inBufs->bufDesc[0]->bufPlanes[0].width * inBufs->bufDesc[0]->bufPlanes[0].height ;
  int32_t ChromaSize  = inBufs->bufDesc[0]->bufPlanes[1].width * inBufs->bufDesc[0]->bufPlanes[1].height;
  int32_t FrameSize = (lumaSize + ChromaSize);
  fp = FOPEN(fileName, "rb");
  FSEEK(fp, currFrameNum*FrameSize, SEEK_SET);
#if 1
  FREAD(inBufs->bufDesc[0]->bufPlanes[0].buf,1,lumaSize,fp);
  FREAD(inBufs->bufDesc[0]->bufPlanes[1].buf,1,ChromaSize,fp);
#endif
  FCLOSE(fp);
  return (0);
}

int32_t TestApp_compareReference(
      IVISION_OutBufs * inBufs,
      IVISION_OutBufs * outBufs,
      FILTER_2D_CreateParams * createParams,
      FILTER_2D_EffectiveDims *effDims,
      FILTER_2D_InArgs        * inArgs,
      uint32_t minVal,
      uint32_t maxVal,
      char * outFileName
      )
{
  uint8_t * yOutBufRef;
  uint32_t totalPixels;
  int32_t i,j;
  uint32_t minThrIndexVal;
  uint32_t maxThrIndexVal;
  uint32_t minValRef;
  uint32_t maxValRef;
  uint32_t minPercentileThreshold = createParams->minPercentileThreshold;
  uint32_t maxPercentileThreshold = createParams->maxPercentileThreshold;
  uint32_t scaleFactorQ16;
  uint8_t * outputImageRef = NULL;
  uint32_t * yHistogram8CopyRef = NULL;
  uint32_t * yHistogramRef = NULL;
  uint8_t * imageTobeFiltered = NULL;
  int32_t   status = 0;
  uint32_t effectiveWidth;
  uint32_t effectiveHeight;
  uint16_t imgW;
  uint16_t imgH;
  uint16_t pitch;
  uint8_t * outPtr;
  uint8_t   filterCoeffWidth;
  uint8_t * filterCoeff;
  uint8_t   dummyFilterCoeff = 1;
  uint8_t   rndBits;
  uint16_t  sumWH;
  uint8_t filterCoeffRef[MAX_FILTER_COEF_WIDTH * MAX_FILTER_COEF_HEIGHT];

  effectiveWidth  = effDims->effImageWidth;

  effectiveHeight = effDims->effImageHeight;

  yOutBufRef = (uint8_t*) malloc(effectiveWidth *
                       effectiveHeight);

  imageTobeFiltered = (uint8_t *)inBufs->bufDesc[0]->bufPlanes[0].buf;

  if( createParams->enableContrastStretching)
  {

    outputImageRef  = (uint8_t *)malloc(effectiveWidth *
                         effectiveHeight);

    yHistogram8CopyRef = (uint32_t *)malloc(SIZE_HISTO_8_COPY);

    yHistogramRef   = (uint32_t *)malloc(SIZE_HISTOGRAM);

    memset ( yHistogram8CopyRef, 0 , SIZE_HISTO_8_COPY);
    memset ( yHistogramRef, 0 , SIZE_HISTOGRAM);

    vcop_histogram_8c_word_cn((uint8_t *)inBufs->bufDesc[0]->bufPlanes[0].buf,
        effDims->activeHistImgWidth,
        effDims->activeHistImgHeight,
        inBufs->bufDesc[0]->bufPlanes[0].width,
        yHistogram8CopyRef);

    vcop_histogram_8c_word_sum_cn(yHistogram8CopyRef, yHistogramRef);


    /* Find Min and Max of histogram */
    for ( i = 1; i < 256; i++)
    {
      yHistogramRef[i] = yHistogramRef[i] + yHistogramRef[i-1];
    }
    totalPixels = yHistogramRef[255];
    minThrIndexVal = yHistogramRef[0];
    minValRef = 0;
    for(i = 0; i < 256 ; i++)
    {
      minThrIndexVal = yHistogramRef[i];
      minValRef = i;
      if( minThrIndexVal > totalPixels * minPercentileThreshold / 100)
      {
        break;
      }
    }
    maxThrIndexVal = yHistogramRef[255];
    maxValRef = 255;
    for( i = 255 ; i >= 0; i--)
    {
      maxThrIndexVal = yHistogramRef[i];
      maxValRef = i;
      if(maxThrIndexVal<totalPixels * maxPercentileThreshold / 100)
      {
        break;
      }
    }

    minValRef = ( minValRef > 64  ) ? 64  : minValRef;
    maxValRef = ( maxValRef < 128 ) ? 128 : maxValRef;

    if ( (inArgs->maxVal - inArgs->minVal ) != 0 )
    {
      scaleFactorQ16 = ( 1 << 16) / (inArgs->maxVal - inArgs->minVal );
    }
    else
    {
      scaleFactorQ16 = (1<<16);
    }



    vcop_contrast_stretching_cn(
          (uint8_t *)inBufs->bufDesc[0]->bufPlanes[0].buf,
          outputImageRef,
          effectiveWidth,
          effectiveHeight,
          inBufs->bufDesc[0]->bufPlanes[0].width,
          inBufs->bufDesc[0]->bufPlanes[0].width,
          inArgs->minVal,
          scaleFactorQ16);

    if ( minValRef != minVal  || maxValRef != maxVal)
    {
      status = -1 ;
      TEST_PRINTF(" Min and MaxVal not correct Ref (%d,%d) App (%d,%d) \n",minValRef,maxValRef,minVal,maxVal);
    }

    imageTobeFiltered = outputImageRef;
  }

  if ( createParams->enableFilter != 1)
  {
    filterCoeffWidth = 1;
    filterCoeff   = &dummyFilterCoeff;
    rndBits = 0;
  }
  else
  {
    filterCoeffWidth = createParams->filterCoefWidth;
    /* Convert separable filter to a single matrix */
    for ( j = 0; j < createParams->filterCoefHeight; j++)
    {
      for ( i = 0; i < createParams->filterCoefWidth; i++)
      {
        filterCoeffRef[i+j*createParams->filterCoefWidth] = createParams->filterCoef[j] * createParams->filterCoef[i + createParams->filterCoefWidth];
      }
    }

    filterCoeff      = filterCoeffRef;


    sumWH = 0;
    if ( createParams->separableFilter == 1 )
    {
      for ( j = 0; j < createParams->filterCoefHeight; j++)
      {
        for ( i = 0; i < createParams->filterCoefWidth; i++)
        {
          sumWH += filterCoeffRef[i+j*createParams->filterCoefWidth];
        }
      }

      /* This is under the assumption that sumWH is power of 2 */
      rndBits = 0;
      if ( sumWH !=0 )
      {
        while ( sumWH != 1 )
        {
          sumWH = sumWH >> 1;
          rndBits++;
        }
      }
    }
  }
  vcop_yuv420_fir2d_separable_y_cn(imageTobeFiltered,
                         filterCoeff,
                         effectiveWidth,
                         inBufs->bufDesc[0]->bufPlanes[0].width,
                         effectiveHeight,
                         filterCoeffWidth,
                         yOutBufRef,
                         rndBits);



  /* Compare with reference */
  imgW = inBufs->bufDesc[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.width;
  imgH = inBufs->bufDesc[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].frameROI.height;
  pitch = inBufs->bufDesc[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[0].width;

  outPtr = (uint8_t *)outBufs->bufDesc[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufPlanes[0].buf;

  for ( i = 0; i < imgH - (filterCoeffWidth - 1); i++)
  {
    for ( j = 0 ; j < imgW - (filterCoeffWidth - 1); j++)
    {
      if ( outPtr[j + (i * pitch)] != yOutBufRef[j + (i * pitch)])
      {
        TEST_PRINTF("Output Not Bit matched with reference at %d, %d \n",j,i);
        status |= -1;
        break;
      }
    }
  }

#if ENABLE_OUTPUT_DUMP
  if (strcmp(outFileName , ""))
  {
    TI_FILE * fpApp;
    uint8_t * ptr;
    fpApp = FOPEN(outFileName, "wb");

    for (i = 0; i < imgH - (filterCoeffWidth - 1); i++ )
    {
      ptr = (uint8_t *)outBufs->bufDesc[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufPlanes[0].buf;
      ptr = ptr + pitch*i;
      FWRITE(ptr,
              1,
              imgW - (filterCoeffWidth - 1),
              fpApp);


    }
    for (i = 0; i < (imgH/2) - (filterCoeffWidth - 1); i++ )
    {
      ptr = (uint8_t *)outBufs->bufDesc[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER]->bufPlanes[1].buf;
      ptr = ptr + pitch*i;
      FWRITE(ptr,
              1,
              imgW - 2 * (filterCoeffWidth - 1),
              fpApp);
    }
    FCLOSE (fpApp);
  }
#endif

  if ( yOutBufRef )
  {
    free (yOutBufRef);
  }
  if (outputImageRef)
  {
    free(outputImageRef);
  }

  if (yHistogramRef)
  {
    free(yHistogramRef);
  }

  if (yHistogram8CopyRef)
  {
    free(yHistogram8CopyRef);
  }
  return (status);
}

int32_t filter2dTest(sFilter2d_Config * testcaseParams)
{
  uint32_t tcntr0, tcntr1, overflow, profile_sctm;
  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status;

  uint32_t t0, t1, overhead, profile_tsc, profile_create_tsc;
  uint32_t testcase;
  uint8_t  levelCnt=0;
  char  *statusStr = NULL;
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/
  FILTER_2D_CreateParams   createParams;

  FILTER_2D_InArgs inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc;
  IVISION_BufDesc   *inBufDescList[FILTER_2D_TI_BUFDESC_IN_TOTAL];

  FILTER_2D_OutArgs   outArgs;
  IVISION_OutBufs     outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc;
  IVISION_BufDesc   *outBufDescList[FILTER_2D_TI_BUFDESC_OUT_TOTAL];

  FILTER_2D_EffectiveDims effDims;
  uint8_t idx;
  uint8_t fail;

  /* This is just to remove warning coming from linker command file */
  vcop_minit();

  outArgs.iVisionOutArgs.size = sizeof(FILTER_2D_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(FILTER_2D_InArgs);
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/
  uint8_t *pDmem;
  TIMemHandle memHdl_DMEM;


  pDmem = (uint8_t *)&DMEM_SCRATCH;
  memHdl_DMEM = &memObj_DMEM;
  TI_CreateMemoryHandle(memHdl_DMEM, pDmem, DMEM_SIZE);
  _tsc_start();

  t0 = _tsc_gettime();
  overhead = _tsc_gettime() - t0;

  TEST_PRINTF("\n%-20s %10s %10s %10s %10s %15s %20s %10s %10s %16s    %s\n", \
    "Algorithm", "Status", "BaseWidth", "BaseHeight","NumLevels", "MegaCycPerFr", \
    "MegaCycPerSec(30Fr)", "TotalCycPerPix", "VcopBusyCycPerPix","TimePerFr(MSec)", "Comments");

  profiler_init();
  profiler_initStack(profiler_getSP());


  /*------------------------------------------------------------*/
  /* This function actually sets Enable bit in the CT CNTL      */
  /* register of SCTM. Parameter CTM is defined in              */
  /* baseaddress.h, and is used by cred macros to compute       */
  /* baseaddress of CTM.                                        */
  /*------------------------------------------------------------*/
  EVE_SCTM_Enable(CTM);

  /*------------------------------------------------------------*/
  /* Configure Counter 0, to measure "vcop_busy" which is a     */
  /* duration signal, and enable the counter.                   */
  /*------------------------------------------------------------*/
  EVE_SCTM_CounterConfig(CTM, SCTM_Counter_0, VCOP_BUSY, SCTM_DURATION);
  EVE_SCTM_CounterTimerEnable(CTM, SCTM_Counter_0);

  for ( testcase = 0 ; testcase < filter2d_numTestCases; testcase++ )
  {

    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = FILTER_2D_TI_BUFDESC_IN_TOTAL;
    outBufs.numBufs  = FILTER_2D_TI_BUFDESC_OUT_TOTAL;

    inBufDescList[FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER]                = &inBufDesc;
    outBufDescList[FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER]    = &outBufDesc;

    /*-----------------------------------------------------------------
      Set algorithm parameters
      -----------------------------------------------------------------*/

    createParams.filterCoefWidth  =  testcaseParams[testcase].filterCoeffWidth;
    createParams.filterCoefHeight = testcaseParams[testcase].filterCoeffHeight;
    createParams.separableFilter  = 1;
    createParams.filterCoef       = testcaseParams[testcase].filterCoeffs;
    createParams.imageFormat              = testcaseParams[testcase].imageFormat;
    createParams.enableContrastStretching = testcaseParams[testcase].enableContrastStretching;
    createParams.minPercentileThreshold   = testcaseParams[testcase].minPercentileThreshold;
    createParams.maxPercentileThreshold   = testcaseParams[testcase].maxPercentileThreshold;
    createParams.enableFilter             = testcaseParams[testcase].enableFilter;
    createParams.minVal = 0;
    createParams.maxVal = 255;

     profiler_start();

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = FILTER_2D_TI_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = FILTER_2D_TI_VISION_FXNS.ialg.algAlloc(
      (IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("2D Filter Applet Create Done\n");
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
    t0 = _tsc_gettime();

    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = FILTER_2D_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
      memRec,NULL,(IALG_Params *)(&createParams));

    /* Set the end point of the timing measurement for the creation process */
    t1 = _tsc_gettime();
    profile_create_tsc = (t1 - t0 - overhead);

    profiler_end_print(0);


    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERRORE_MSG();
      goto EXIT_LOOP;
    }
#if ENABLE_TRACES
    TEST_PRINTF("2D Filter  Applet Init Done\n");
#endif

    idx = FILTER_2D_TI_BUFDESC_IN_IMAGEBUFFER;
    inBufs.bufDesc[idx]->numPlanes                          = 2;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    inBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams[testcase].srcImagePitch;
    inBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams[testcase].srcImageHeight;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams[testcase].srcImageWidth;
    inBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams[testcase].srcImageHeight;
    inBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0; //Luma Y

    inBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.x    = 0;
    inBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.y    = 0;
    inBufs.bufDesc[idx]->bufPlanes[1].width                 = testcaseParams[testcase].srcImagePitch;
    inBufs.bufDesc[idx]->bufPlanes[1].height                = testcaseParams[testcase].srcImageHeight/2;
    inBufs.bufDesc[idx]->bufPlanes[1].frameROI.width        = testcaseParams[testcase].srcImageWidth;
    inBufs.bufDesc[idx]->bufPlanes[1].frameROI.height       = testcaseParams[testcase].srcImageHeight/2;
    inBufs.bufDesc[idx]->bufPlanes[1].planeType             = 1; //C

    status = handle->ivision->algControl((IVISION_Handle)handle,FILTER_2D_CONTROL_GET_EFFECTIVE_OUTPUT_DIM,
      (IALG_Params *)(&inBufs),(IALG_Params *)(&effDims));


    inBufs.bufDesc[idx]->bufPlanes[0].buf = malloc( (effDims.effImageWidth+ (createParams.filterCoefWidth - 1)) *
                (effDims.effImageHeight+ (createParams.filterCoefHeight - 1)));


    inBufs.bufDesc[idx]->bufPlanes[1].buf = malloc( (effDims.effImageWidth + (createParams.filterCoefWidth - 1)) *
                (effDims.effImageHeight + (createParams.filterCoefHeight - 1)) / 2);

    if((inBufs.bufDesc[idx]->bufPlanes[0].buf == NULL) || (inBufs.bufDesc[idx]->bufPlanes[1].buf == NULL))
    {
      TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    }

    idx = FILTER_2D_TI_BUFDESC_OUT_IMAGE_BUFFER;
    outBufs.bufDesc[idx]->numPlanes                          = 2;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.x    = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.topLeft.y    = 0;
    outBufs.bufDesc[idx]->bufPlanes[0].width                 = testcaseParams[testcase].srcImageWidth;
    outBufs.bufDesc[idx]->bufPlanes[0].height                = testcaseParams[testcase].srcImageHeight;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.width        = testcaseParams[testcase].srcImageWidth;
    outBufs.bufDesc[idx]->bufPlanes[0].frameROI.height       = testcaseParams[testcase].srcImageHeight;
    outBufs.bufDesc[idx]->bufPlanes[0].planeType             = 0; //Luma Y

    outBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.x    = 0;
    outBufs.bufDesc[idx]->bufPlanes[1].frameROI.topLeft.y    = 0;
    outBufs.bufDesc[idx]->bufPlanes[1].width                 = testcaseParams[testcase].srcImageWidth;
    outBufs.bufDesc[idx]->bufPlanes[1].height                = testcaseParams[testcase].srcImageHeight/2;
    outBufs.bufDesc[idx]->bufPlanes[1].frameROI.width        = testcaseParams[testcase].srcImageWidth;
    outBufs.bufDesc[idx]->bufPlanes[1].frameROI.height       = testcaseParams[testcase].srcImageHeight/2;
    outBufs.bufDesc[idx]->bufPlanes[1].planeType             = 1; //Chroma UV

    outBufs.bufDesc[idx]->bufPlanes[0].buf = malloc( (effDims.effImageWidth) *
                    (effDims.effImageHeight));


    outBufs.bufDesc[idx]->bufPlanes[1].buf = malloc( (effDims.effImageWidth) *
                (effDims.effImageHeight) / 2);

    if((outBufs.bufDesc[idx]->bufPlanes[0].buf == NULL) || (outBufs.bufDesc[idx]->bufPlanes[1].buf == NULL))
    {
      TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__);
    }

    inArgs.iVisionInArgs.subFrameInfo = 0;
    inArgs.iVisionInArgs.size                  = sizeof(FILTER_2D_InArgs);
    inArgs.minVal = 25;
    inArgs.maxVal = 234;

    inBufDesc.numPlanes                          = 2;
    outBufDesc.numPlanes                         = 1;

    TestApp_ReadInBufs(&inBufs,0,(char *)testcaseParams[testcase].inImage);


#if ENABLE_TRACES
    TEST_PRINTF("Processing started for frame %d \n",0);
#endif
    tcntr0 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    t0 = _tsc_gettime();

    profiler_start();

    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);

    t1 = _tsc_gettime();
    profile_tsc = (t1 - t0 - overhead);
    tcntr1 = EVE_SCTM_CounterRead(CTM, SCTM_Counter_0);
    overflow = EVE_SCTM_OverflowCheck(CTM, SCTM_Counter_0);
    if(overflow) {
      TEST_PRINTF("Counter overflow!!!\n");
    }
    profile_sctm = ((overflow) ? (0XFFFFFFFF + tcntr1 - tcntr0) : (tcntr1 - tcntr0));

     profiler_end_print(1);
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

    fail = TestApp_compareReference(&inBufs,
                             &outBufs,
                             &createParams,
                             &effDims,
                             &inArgs,
                             outArgs.minVal,
                             outArgs.maxVal,
                             (char *)testcaseParams[testcase].outImage);


    profiler_printStatus(fail);

    statusStr = fail ? "FAILED":"PASSED";

    fflush(stdout);

TEST_PRINTF("%-20s %10s %10d %10d %10d %15.2f %20.2f %14.2f %17.2f %16.2f \
    Create graph is %2.2f Mcycles per frame but it is a one-time startup call\n",\
    "Stage 1",statusStr, testcaseParams[testcase].srcImageWidth,
    testcaseParams[testcase].srcImageHeight,\
    1, (2*profile_tsc/1000000.0), 30*(2*profile_tsc/1000000.0),\
    (profile_tsc*2.0)/(testcaseParams[testcase].srcImageWidth*testcaseParams[testcase].srcImageHeight),\
    (profile_sctm*2.0)/(testcaseParams[testcase].srcImageWidth*testcaseParams[testcase].srcImageHeight),\
    (2*profile_tsc/500000.0), (profile_create_tsc*2.0)/1000000.0);
TEST_PRINTF("Reference Matching is only for Y component\n");

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


  }

 /* Get the stack usage */
#if !(VCOP_HOST_EMULATION)
  profiler_getStackDepth();
#endif
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

  report_printAppletInfo((int8_t *)"FILTER_2D_TI_VISION");

  fp = FOPEN((const char *)configFile , "r");
  if(fp== NULL)
  {
    TEST_PRINTF("Could not open config list file : %s \n",CONFIG_LIST_FILE_NAME);
    return(status);
  }

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
      status = readparamfile(configFile, &gsTokenMap_filter2d[0]);
      if(status == -1)
      {
        TEST_PRINTF("Parser Failed");
        return -1 ;
      }

      profiler_testCaseInfo((int8_t *)gConfig_filter2d[0].testCaseName, (int8_t *)gConfig_filter2d[0].desc,
                                  gConfig_filter2d[0].performanceTestcase);
      printparams(&gsTokenMap_filter2d[0], (int32_t)MAX_ITEMS_TO_PARSE, (uint32_t)(&gsTokenMap_filter2d),
                            sizeof(sFilter2d_Config));


     /* Validate the applet */
     status = filter2dTest(gConfig_filter2d);

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



