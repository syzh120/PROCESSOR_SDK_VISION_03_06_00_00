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


/**
*  @file       orb_alg.c
*
*  @brief       This file defines the XDAIS/iVISION functions for ORB Algorithm
*  @version    0.0 (Dec 2013) : Base version.
*  @version    0.1 (April 2014) : Updated version
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#pragma RESET_MISRA ("required")

#include "orb_alg_int.h"
#include "ifast9_best_feature_to_front_ti.h"
#include "ifast9_corner_detect_ti.h"
#include "iharris_best_feature_to_front_ti.h"
#include "irbrief_ti.h"
#include "iImagePyramid_u8_ti.h"
#include "edma_utils_memcpy.h"


#define RBRIEF_APPLET_BORDER_X  24
#define RBRIEF_APPLET_BORDER_Y  24

#define MIN(a,b) ((a) < (b) ? (a) : (b)) ;
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ALIGN(addr, alignment) ((((uint32_t)addr) + alignment-1) & ~(alignment-1))

/**
* IVISION interface of the algorithm
*/
const IVISION_Fxns ORB_TI_VISION_FXNS =
{
  {
    (void *)&ORB_TI_VISION_FXNS, /* module ID */
      ORB_TI_activate,    /* activate */
      ORB_TI_alloc,       /* algAlloc */
      NULL,                          /* control (not suported) */
      ORB_TI_deactivate,  /* deactivate */
      ORB_TI_free,        /* free */
      ORB_TI_init,        /* init */
      NULL,                          /* moved (not suported) */
      ORB_TI_numAlloc     /* algNumAlloc  */
  },
  ORB_TI_process,
  ORB_TI_control
};


/**
* IRES interface of the algorithm
*/
const IRES_Fxns ORB_TI_IRES = {
  (void *)&ORB_TI_IRES,
  NULL,                                     /*getResourceDescriptors, */
  NULL,                                     /*numResourceDescriptors */
  NULL,                                     /*initResources,  */
  NULL,                                     /*reinitResources, */
  NULL,                                     /*deinitResources, */
  NULL,                                     /*activateResource,*/
  NULL,                                     /*activateAllResources, */
  NULL,                                     /*deactivateResource,   */
  NULL                                      /*deactivateAllResources */
};

/**
* Internal functions
*/


#ifdef _DEBUG
static void ORB_TI_DumpData(IVISION_OutBufs *bufList, char *routine)
{
  FILE *fp ;
  uint8_t *buf;
  uint32_t size, i,j ;
  char fileName[100];
  for(i = 0; i < bufList->numBufs ;i++)
  {
    for(j = 0 ; j < bufList->bufDesc[i]->numPlanes; j++)
    {
      buf = (uint8_t *) bufList->bufDesc[i]->bufPlanes[j].buf ;
      size = bufList->bufDesc[i]->bufPlanes[j].frameROI.width*
        bufList->bufDesc[i]->bufPlanes[j].frameROI.height;

      sprintf(fileName,"%s_buf%d_plane%d.dat",routine,i,j);
      fp = fopen(fileName,"wb");
      fwrite(buf,1,size,fp);
      fclose(fp);
    }
  }
}
#endif

static void ORB_TI_UpdateFast9CornerCreateParams(ORB_TI_CreateParams *orbCreateParams,
  FAST9_CORNER_DETECT_TI_CreateParams *fast9CornerDetectCreateParams)
{
  uint8_t level ;
  fast9CornerDetectCreateParams->visionParams = orbCreateParams->visionParams;

  for(level = 0 ; level < orbCreateParams->numLevels ; level++)
  {
    fast9CornerDetectCreateParams->imgFrameWidth[level]  = orbCreateParams->imgFrameWidth  >> level;
    fast9CornerDetectCreateParams->imgFrameHeight[level] = orbCreateParams->imgFrameHeight >> level;
  }
  fast9CornerDetectCreateParams->excludeBorderX = RBRIEF_APPLET_BORDER_X ;
  fast9CornerDetectCreateParams->excludeBorderY = RBRIEF_APPLET_BORDER_Y ;
  fast9CornerDetectCreateParams->numLevels      = orbCreateParams->numLevels ;
  return ;
}

static void ORB_TI_UpdateFast9BFFTParams(ORB_TI_CreateParams *orbCreateParams,
  FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams *fast9BFFTCreateParams)
{
  fast9BFFTCreateParams->visionParams   = orbCreateParams->visionParams  ;
  fast9BFFTCreateParams->xyInIntMem     = 0 ;
  fast9BFFTCreateParams->fast9Threshold = orbCreateParams->fast9Threshold;
  fast9BFFTCreateParams->maxFeatures = FAST9_BFFT_TI_MAXNUMFEATURES ;
  fast9BFFTCreateParams->scoreMethod = orbCreateParams->scoreMethod;
  fast9BFFTCreateParams->maxbestNFeatures = FAST9_BFFT_TI_MAXNUMFEATURES;

  return ;
}

static void ORB_TI_UpdateHarrisBFFTParams(ORB_TI_CreateParams *orbCreateParams,
  HARRIS_BEST_FEATURE_TO_FRONT_TI_CreateParams *harrisBFFTCreateParams)
{
  harrisBFFTCreateParams->visionParams     = orbCreateParams->visionParams  ;
  harrisBFFTCreateParams->bestNFeaturesOut = orbCreateParams->bestNFeaturesOut ;

  /*-----------------------------------------------------------*/
  /* Per level has 2 times final feature and total limited to  */
  /* HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMFEATURES            */
  /*-----------------------------------------------------------*/

  harrisBFFTCreateParams->maxNumFeaturesIn = 2*orbCreateParams->bestNFeaturesOut*orbCreateParams->numLevels;
  if(harrisBFFTCreateParams->maxNumFeaturesIn > HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMFEATURES)
  {
    harrisBFFTCreateParams->maxNumFeaturesIn = HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMFEATURES ;
  }
  harrisBFFTCreateParams->sensitivityParam = orbCreateParams->harrisSensitivityParam ;
  harrisBFFTCreateParams->xyListInDmem = 0 ;
  return ;
}

static void ORB_TI_UpdateRBriefParams(ORB_TI_CreateParams *orbCreateParams,
  RBRIEF_TI_CreateParams *rBriefCreateParams)
{
  rBriefCreateParams->visionParams   = orbCreateParams->visionParams  ;
  rBriefCreateParams->maxNumFeatures = orbCreateParams->bestNFeaturesOut ;
  rBriefCreateParams->orbPattern     = orbCreateParams->orbPattern    ;
  rBriefCreateParams->levelListInDmem= 0 ;
  rBriefCreateParams->xyListInDmem   = 0 ;
  return ;
}


static void ORB_TI_UpdateImagePyramidParams(ORB_TI_CreateParams *orbCreateParams,
  IMAGE_PYRAMID_U8_TI_CreateParams *imgPyramidCreateParams)
{
  imgPyramidCreateParams->imgFrameWidth  = orbCreateParams->imgFrameWidth ;
  imgPyramidCreateParams->imgFrameHeight = orbCreateParams->imgFrameHeight ;
  imgPyramidCreateParams->numLevels      = orbCreateParams->numLevels - 1;
  imgPyramidCreateParams->filterType     = IMAGE_PYRAMID_U8_TI_2x2_AVERAGE;
  return ;
}


/*-------------------------------------------------------------------------------------------*/
/* Basic idea of below 2 functions is as below                                               */
/* Different apps put their memtab requirement and to end user the total memtabs becomes     */
/* very high. so to prevent this....                                                         */
/* 1. Findout the number of highest memRecs across all applets and request user the number   */
/* of memTabs as the ALOG REQUIRED MEMTABS + MAX ACROSS APPS                                 */
/* The reason is that we need memtab memory to interact with all the apps so max across apps */
/* has to be requested additional to algo memtabs                                            */
/* Now we get memRecs to hold the information from different apps                            */
/* So we should supply this memRec area to query to apps and have 4 memrecs in algo level to */
/* sum all the memory requested from different apps                                          */
/* The category of 4 memrec is as  - EXT - SCRATCH, PERSISTENT, INT- SCRATCH, PERSISTENT     */
/* So all the persistent memory need as to be summmed up and requested by algo               */
/* All the scratch memory across applets needs to be shared by all applets so request the    */
/* max memory size across all the apps - example if app1 has 2 scratch of 1K and 2K and      */
/* app2 has 3 scratch of 0.5K, 1K and 1K.. then app1 total need is 3K, app2 totoal need is   */
/* 2.5 K - so request 3K to end user and now manage here to give same area to app1 and app2..*/
/* with this it will require activate and deactivate across app process boundary             */
/* we should try to avoid it if sum of all apps is less than 24 K for internal memory        */
/*-------------------------------------------------------------------------------------------*/

/* --------------------------------------------------------------------*/
/* Funtion to consume user given memTabs and provide to different Apps */
/* --------------------------------------------------------------------*/
static void ORB_TI_SetAlgToAppsMemRec(const IALG_MemRec *memRecBase,
                               IALG_MemRec *memRec, int32_t numRecs,
                               int32_t *pSizeConsumedIntPersist,
                               int32_t* pSizeConsumedExtPersist)
{
  int32_t i ;
  uint8_t *base, *baseAlign;
  int32_t sizeConsumedIntScratch, sizeConsumedExtScratch ;

  sizeConsumedIntScratch = sizeConsumedExtScratch = 0 ;
  for(i =0 ; i < numRecs ; i++)
  {
    if((memRec[i].attrs == IALG_SCRATCH) || (memRec[i].attrs == IVISION_SCRATCH_NOCONTEXT))
    {
      if(memRec[i].space == IALG_DARAM0)
      {
        base = ((uint8_t *) memRecBase[APPS_SCRATCH_INT].base) + sizeConsumedIntScratch ;
        baseAlign = (uint8_t*) ALIGN(base, memRec[i].alignment) ;
        memRec[i].base = baseAlign ;
        sizeConsumedIntScratch += memRec[i].size  + (baseAlign - base);
      }
      else if(memRec[i].space == IALG_EXTERNAL)
      {
        base = ((uint8_t *) memRecBase[APPS_SCRATCH_EXT].base) + sizeConsumedExtScratch ;
        baseAlign = (uint8_t*) ALIGN(base, memRec[i].alignment) ;
        memRec[i].base = baseAlign ;
        sizeConsumedExtScratch += memRec[i].size  + (baseAlign - base);
      }
    }
    else if((memRec[i].attrs == IALG_PERSIST))
    {
      if(memRec[i].space == IALG_DARAM0)
      {
        base = ((uint8_t *) memRecBase[APPS_PERSIST_INT].base) + *pSizeConsumedIntPersist ;
        baseAlign = (uint8_t*) ALIGN(base, memRec[i].alignment) ;
        memRec[i].base = baseAlign ;
        *pSizeConsumedIntPersist += memRec[i].size  + (baseAlign - base);
      }
      else if(memRec[i].space == IALG_EXTERNAL)
      {
        base = ((uint8_t *) memRecBase[APPS_PERSIST_EXT].base) + *pSizeConsumedExtPersist ;
        baseAlign = (uint8_t*) ALIGN(base, memRec[i].alignment) ;
        memRec[i].base = baseAlign ;
        *pSizeConsumedExtPersist += memRec[i].size  + (baseAlign - base);
      }
    }
  }
  return ;
}

/* --------------------------------------------------------------------*/
/* Funtion to consume apps given memTabs and provide to user           */
/* --------------------------------------------------------------------*/

static void ORB_TI_SetAppsToAlgMemRec(IALG_MemRec *memRecBase, const IALG_MemRec *memRec, int32_t numRecs )
{
  int32_t i ;
  int32_t scratchExt = 0 , scratchInt = 0 ;
  for(i =0 ; i < numRecs ; i++)
  {
    if((memRec[i].attrs == IALG_SCRATCH) || (memRec[i].attrs == IVISION_SCRATCH_NOCONTEXT))
    {
      if(memRec[i].space == IALG_DARAM0)
      {
        scratchInt += memRec[i].size + memRec[i].alignment ;
      }
      else if(memRec[i].space == IALG_EXTERNAL)
      {
        scratchExt += memRec[i].size + memRec[i].alignment ;
      }
    }
    else if((memRec[i].attrs == IALG_PERSIST))
    {
      if(memRec[i].space == IALG_DARAM0)
      {
        memRecBase[APPS_PERSIST_INT].size += memRec[i].size + memRec[i].alignment ;
      }
      else if(memRec[i].space == IALG_EXTERNAL)
      {
        memRecBase[APPS_PERSIST_EXT].size += memRec[i].size + memRec[i].alignment ;
      }
    }
  }
  memRecBase[APPS_SCRATCH_INT].size = MAX(memRecBase[APPS_SCRATCH_INT].size, scratchInt) ;
  memRecBase[APPS_SCRATCH_EXT].size = MAX(memRecBase[APPS_SCRATCH_EXT].size, scratchExt) ;

}


int32_t ORB_TI_numAlloc(void)
{
  int32_t numMemRecRBrief, numMemRecHarrisBFFT, numMemRecFast9BFFT, numMemRecFast9CornerDetect ;
  int32_t numMemRecImagePyramid ;
  int32_t numMemRecORB ;
  int32_t maxMemRecsAcrossApplets ;
  /*---------------------------------------------------------------------------------------------------------------*/
  /* Each Applet can have big list of mem rec. At alg level we should try to combine them to give a simpler view to*/
  /* End user. So to achieve that below approach is followed:                                                      */
  /* Ask all the applets on thier mem rec needs. All scratch should be combined across different applets           */
  /* At alg level have 4 mem recs to indicate                                                                      */
  /* INT_SCRATCH, EXT_SCRATCH,  - these 2 should have all applets scratch memroy need captured and share           */
  /* INT_PERSIST, EXT_PERSIST,     - these 2 should have all applets persist memroy need captured and summed       */
  /* Number of memRecs to be asked user should be max of all applets + 4 + ALG SPECIFIC                            */
  /*---------------------------------------------------------------------------------------------------------------*/
  numMemRecFast9CornerDetect = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecFast9BFFT         = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecHarrisBFFT        = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecRBrief            = RBRIEF_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecImagePyramid      = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algNumAlloc();

  maxMemRecsAcrossApplets = MAX(numMemRecFast9CornerDetect, numMemRecFast9BFFT);
  maxMemRecsAcrossApplets = MAX(maxMemRecsAcrossApplets,    numMemRecHarrisBFFT);
  maxMemRecsAcrossApplets = MAX(maxMemRecsAcrossApplets,    numMemRecRBrief);
  maxMemRecsAcrossApplets = MAX(maxMemRecsAcrossApplets,    numMemRecImagePyramid);

  numMemRecORB = NUM_MEMRECS + maxMemRecsAcrossApplets;

  return numMemRecORB;
}

/*---------------------------------------------------------------*/
/* Function to supply memory requirement to user                 */
/* refer algAlloc function for details in XADIS (ialg.h file)    */
/*---------------------------------------------------------------*/
int32_t ORB_TI_alloc(const IALG_Params *params,
                        struct IALG_Fxns **parentFxns,
                        IALG_MemRec *memRec)
{
  int32_t status = IALG_EOK;
  int32_t numMemRecRBrief, numMemRecHarrisBFFT, numMemRecFast9BFFT, numMemRecFast9CornerDetect ;
  IALG_MemRec *memRecBase ;
  int32_t maxMemRecsAcrossApplets, numMemRecImagePyramid ;
  int32_t i ;

  ORB_TI_CreateParams * createParams =
    (ORB_TI_CreateParams*)params;

  FAST9_CORNER_DETECT_TI_CreateParams fast9CornerDetectCreateParams ;
  FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams fast9BFFTCreateParams ;
  HARRIS_BEST_FEATURE_TO_FRONT_TI_CreateParams harrisBFFTCreateParams ;
  RBRIEF_TI_CreateParams rBriefCreateParams ;
  IMAGE_PYRAMID_U8_TI_CreateParams imgPyramidCreateParams ;


  /*---------------------------------------------------------------------*/
  /* Error checks                                                        */
  /*---------------------------------------------------------------------*/
  if(createParams->bestNFeaturesOut > ORB_TI_MAXNUMFEATURES)
  {
    status = IORB_ERRORTYPE_MAXNUMFEATURES_EXCEEDED ;
    goto EXIT_FUNC_TI_ALLOC;
  }
  if(createParams->numLevels > ORB_TI_MAXLEVELS)
  {
    status = IORB_ERRORTYPE_MAXLEVELS_EXCEEDED ;
    goto EXIT_FUNC_TI_ALLOC;
  }

  if(createParams->startX > createParams->imgFramePitch ||
    createParams->startY  > createParams->imgFrameHeight)
  {
    status = IORB_ERRORTYPE_INVALID_START_XY ;
    goto EXIT_FUNC_TI_ALLOC;
  }

  if(createParams->imgFrameWidth > ORB_TI_MAXWIDTH ||
    createParams->imgFrameHeight > ORB_TI_MAXHEIGHT)
  {
    status = IORB_ERRORTYPE_INVALID_IMAGE_DIMS ;
    goto EXIT_FUNC_TI_ALLOC;
  }

  if(createParams->orbPattern == NULL)
  {
    status = IORB_ERRORTYPE_NULL_ORBPATTERN ;
    goto EXIT_FUNC_TI_ALLOC;
  }

  /*---------------------------------------------------------------------*/
  memRecBase = memRec ;

  memRec[ALG_HANDLE_MEMREC].size          = sizeof(ORB_TI_Obj);
  memRec[ALG_HANDLE_MEMREC].space         = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[ALG_HANDLE_MEMREC].attrs         = IALG_PERSIST;
  memRec[ALG_HANDLE_MEMREC].alignment     = 4;

  memRec[ALG_HANDLE_INT_MEMREC].size      = sizeof(ORB_TI_Obj);
  memRec[ALG_HANDLE_INT_MEMREC].space     = (IALG_MemSpace)IALG_DARAM0;
  memRec[ALG_HANDLE_INT_MEMREC].attrs     = IALG_SCRATCH;
  memRec[ALG_HANDLE_INT_MEMREC].alignment = 4;

  memRec[XY_LIST_MEMREC].size             =
    4 * createParams->imgFrameWidth*createParams->imgFrameHeight ;
  memRec[XY_LIST_MEMREC].space            = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[XY_LIST_MEMREC].attrs            = IALG_SCRATCH;
  memRec[XY_LIST_MEMREC].alignment        = 4;

  /* Initialize all APPS records to be having size 0 */
  memRec[APPS_SCRATCH_INT].size             = 0 ;
  memRec[APPS_SCRATCH_INT].space            = (IALG_MemSpace)IALG_DARAM0;
  memRec[APPS_SCRATCH_INT].attrs            = IALG_SCRATCH;
  memRec[APPS_SCRATCH_INT].alignment        = 4;

  memRec[APPS_SCRATCH_EXT].size             = 0 ;
  memRec[APPS_SCRATCH_EXT].space            = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[APPS_SCRATCH_EXT].attrs            = IALG_SCRATCH;
  memRec[APPS_SCRATCH_EXT].alignment        = 4;

  memRec[APPS_PERSIST_INT].size             = 0 ;
  memRec[APPS_PERSIST_INT].space            = (IALG_MemSpace)IALG_DARAM0;
  memRec[APPS_PERSIST_INT].attrs            = IALG_PERSIST;
  memRec[APPS_PERSIST_INT].alignment        = 4;

  memRec[APPS_PERSIST_EXT].size             = 0 ;
  memRec[APPS_PERSIST_EXT].space            = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[APPS_PERSIST_EXT].attrs            = IALG_PERSIST;
  memRec[APPS_PERSIST_EXT].alignment        = 4;

  maxMemRecsAcrossApplets = ORB_TI_numAlloc() ;
  maxMemRecsAcrossApplets = maxMemRecsAcrossApplets - NUM_MEMRECS ;

  memRec[DUMMY_MEMREC_INFO].size            = maxMemRecsAcrossApplets * sizeof(IALG_MemRec);
  memRec[DUMMY_MEMREC_INFO].space           = (IALG_MemSpace)IALG_EXTERNAL;
  memRec[DUMMY_MEMREC_INFO].attrs           = IALG_PERSIST;
  memRec[DUMMY_MEMREC_INFO].alignment       = 4;

  memRec += NUM_MEMRECS ;

  /*--------------------------------------------------------------------------*/
  /* Take the create time parameters from ORB and populate individual applets */
  /*--------------------------------------------------------------------------*/
  ORB_TI_UpdateFast9CornerCreateParams(createParams, &fast9CornerDetectCreateParams);
  ORB_TI_UpdateFast9BFFTParams(createParams, &fast9BFFTCreateParams);
  ORB_TI_UpdateHarrisBFFTParams(createParams, &harrisBFFTCreateParams);
  ORB_TI_UpdateRBriefParams(createParams, &rBriefCreateParams);
  ORB_TI_UpdateImagePyramidParams(createParams, &imgPyramidCreateParams);

  /*---------------------------------------------------------------*/
  /* Do algAlloc  of all the applets                               */
  /*---------------------------------------------------------------*/
  numMemRecImagePyramid = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algNumAlloc();
  status = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&imgPyramidCreateParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_IMGPYRAMID_CREATE_FAIL ;
    goto EXIT_FUNC_TI_ALLOC;
  }

  ORB_TI_SetAppsToAlgMemRec(memRecBase, memRec, numMemRecImagePyramid);


  numMemRecFast9CornerDetect = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algNumAlloc();
  status = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&fast9CornerDetectCreateParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_FAST9_CORNER_CREATE_FAIL ;
    goto EXIT_FUNC_TI_ALLOC;
  }

  ORB_TI_SetAppsToAlgMemRec(memRecBase, memRec, numMemRecFast9CornerDetect);

  numMemRecFast9BFFT         = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
  status = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&fast9BFFTCreateParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_FAST9_BFFT_CREATE_FAIL ;
    goto EXIT_FUNC_TI_ALLOC;
  }
  ORB_TI_SetAppsToAlgMemRec(memRecBase, memRec, numMemRecFast9BFFT);

  numMemRecHarrisBFFT        = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
  status = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&harrisBFFTCreateParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_HARRIS_BFFT_CREATE_FAIL;
    goto EXIT_FUNC_TI_ALLOC;
  }
  ORB_TI_SetAppsToAlgMemRec(memRecBase, memRec, numMemRecHarrisBFFT);

  numMemRecRBrief            = RBRIEF_TI_VISION_FXNS.ialg.algNumAlloc();
  status = RBRIEF_TI_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&rBriefCreateParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_RBRIEF_CREATE_FAIL;
    goto EXIT_FUNC_TI_ALLOC;
  }
  ORB_TI_SetAppsToAlgMemRec(memRecBase, memRec, numMemRecRBrief);

  /* If any one of the memory is still having size as 0 - put some minimum value to avoid mis behavior on user side */

  if(memRecBase[APPS_SCRATCH_INT].size == 0)  memRecBase[APPS_SCRATCH_INT].size = 4 ;
  if(memRecBase[APPS_SCRATCH_EXT].size == 0)  memRecBase[APPS_SCRATCH_EXT].size = 4 ;
  if(memRecBase[APPS_PERSIST_INT].size == 0)  memRecBase[APPS_PERSIST_INT].size = 4 ;
  if(memRecBase[APPS_PERSIST_EXT].size == 0)  memRecBase[APPS_PERSIST_EXT].size = 4 ;

  /*--------------------------------------------------------------------------------------*/
  /* Need to set rest all memtab as dummy because algo is taking care of all memory needs */
  /* of apps as part of its own memtabs.                                                  */
  /*--------------------------------------------------------------------------------------*/
  for(i = 0 ; i < maxMemRecsAcrossApplets ; i++)
  {
    memRec[i].size      = 16;
    memRec[i].attrs     = IALG_SCRATCH;
    memRec[i].space     = (IALG_MemSpace)IALG_EXTERNAL;
    memRec[i].alignment = 4;
  }

EXIT_FUNC_TI_ALLOC:

  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept memory pointers from user and initialize algorithm */
/* Refer algInit function for details in XADIS (ialg.h file)             */
/*-----------------------------------------------------------------------*/
int32_t ORB_TI_init(IALG_Handle handle,
                      const IALG_MemRec *memRec,
                      IALG_Handle parent,
                      const IALG_Params * params)
{
  int32_t status = IALG_EOK;
  uint8_t memRecBaseId = 0 ;
  uint32_t frameBufSize, i, xyListSizePerLevel, totalBestNFeaturesOutFast9BFTF  ;
  IVISION_Handle handleApp ;
  int32_t dummyMemRecs ;
  int32_t numMemRecRBrief, numMemRecHarrisBFFT, numMemRecFast9BFFT, numMemRecFast9CornerDetect ;
  int32_t numMemRecImgPyramid ;

  int32_t sizeConsumedIntPersist, sizeConsumedExtPersist  ;

  FAST9_CORNER_DETECT_TI_CreateParams fast9CornerDetectCreateParams ;
  FAST9_BEST_FEATURE_TO_FRONT_TI_CreateParams fast9BFFTCreateParams ;
  HARRIS_BEST_FEATURE_TO_FRONT_TI_CreateParams harrisBFFTCreateParams ;
  RBRIEF_TI_CreateParams rBriefCreateParams ;
  IMAGE_PYRAMID_U8_TI_CreateParams  imgPyramidCreateParams ;

  ORB_TI_CreateParams * createParams =
    (ORB_TI_CreateParams*)params;

  ORB_TI_Handle algHandle =
    (ORB_TI_Handle)memRec[ALG_HANDLE_MEMREC].base;


  /*--------------------------------------------------------------------------*/
  /* Take the create time parameters from ORB and populate individual applets */
  /*--------------------------------------------------------------------------*/
  ORB_TI_UpdateFast9CornerCreateParams(createParams, &fast9CornerDetectCreateParams);
  ORB_TI_UpdateFast9BFFTParams(createParams, &fast9BFFTCreateParams);
  ORB_TI_UpdateHarrisBFFTParams(createParams, &harrisBFFTCreateParams);
  ORB_TI_UpdateRBriefParams(createParams, &rBriefCreateParams);
  ORB_TI_UpdateImagePyramidParams(createParams, &imgPyramidCreateParams);



  numMemRecFast9CornerDetect = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecFast9BFFT         = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecHarrisBFFT        = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecRBrief            = RBRIEF_TI_VISION_FXNS.ialg.algNumAlloc();
  numMemRecImgPyramid        = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algNumAlloc();

  algHandle->numLevels       = createParams->numLevels ;
  algHandle->fast9Threshold  = createParams->fast9Threshold;
  algHandle->bestNFeaturesOut= createParams->bestNFeaturesOut ;

  /*--------------------------------------------------------------------------*/
  /* Check total Features to be feeded to Harris BFTF - if it exceed the      */
  /* capability of Harris BFTF then We need to make sure that Fast9 BFTF      */
  /* doesn't produce high value. By default 2*totalBest is produced by Fast9  */
  /* BFTF but if total is high then divide in ratio of total pixels           */
  /*--------------------------------------------------------------------------*/

  totalBestNFeaturesOutFast9BFTF = createParams->numLevels * createParams->bestNFeaturesOut * 2;
  if(totalBestNFeaturesOutFast9BFTF > HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMFEATURES)
  {
    uint8_t ratioHighest, totalParts ;
    ratioHighest = 1 << (createParams->numLevels - 1) ;
    totalParts   = (1 << createParams->numLevels) - 1;
    totalBestNFeaturesOutFast9BFTF  = HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMFEATURES ;
    for(i= 0; i < createParams->numLevels ; i++)
    {
      algHandle->bestNFeaturesOutFast9BFTF[i] =
        (totalBestNFeaturesOutFast9BFTF * ratioHighest)/totalParts;
      ratioHighest >>= 1 ;
    }
  }
  else
  {
    for(i= 0; i < createParams->numLevels ; i++)
    {
      algHandle->bestNFeaturesOutFast9BFTF[i] = createParams->bestNFeaturesOut * 2;
    }
  }

  frameBufSize = createParams->imgFrameWidth * createParams->imgFrameHeight ;

  /*-------------------------------------------------------------------------------------------------------------*/
  /* Mmeory b/w image Pyramids and XY list is shared                                                             */
  /* XY list needs 4 x maxWidth x maxHeight memory (worst case)                                                  */
  /*  image Pyramids needs 2x maxWidth x max Height for all levels excluding base level (1/2 + 1/4 + 1/8 ....)   */
  /* XY list memory required by key point detction is only maxWidth x maxHeight after base level                 */
  /* so if we do image pyramid generation after key point selection on base level total memory need is           */
  /* 3 x maxWidth x maxHeight....                                                                                */
  /* Now assume that we can limit the total points sleected as 1/4 of image size for base level... all together  */
  /* everything can fit in 4x maxWidth x maxHeight memory...                                                     */
  /* We have limit on kepy points as 2K - may be 4K for future so it needs 4K*4 = 16 K memory. which means that  */
  /* base resolution alllowed is something which satisfy the propery as width x height > 16 K... -- 128x128      */
  /* so we need to put limit on mimimum width and height if there are more than 1 level                          */
  /*-------------------------------------------------------------------------------------------------------------*/
  xyListSizePerLevel = (memRec[XY_LIST_MEMREC].size / 2)/createParams->numLevels ;
  algHandle->bufPtrsAlg[IMG_BUF][0] = NULL ; /* It will be updated during process time */
  algHandle->bufPtrsAlg[IMG_BUF][1] = (uint8_t*)memRec[XY_LIST_MEMREC].base + (memRec[XY_LIST_MEMREC].size / 2) ;
  algHandle->bufPtrsAlg[XY_ALG_BUF][0]  = (uint8_t*)memRec[XY_LIST_MEMREC].base ;
  algHandle->bufPtrsAlg[XY_ALG_BUF][1]  = algHandle->bufPtrsAlg[XY_ALG_BUF][0] + xyListSizePerLevel ;

  for(i= 2; i < createParams->numLevels ; i++)
  {
    algHandle->bufPtrsAlg[IMG_BUF][i] =
      algHandle->bufPtrsAlg[IMG_BUF][i-1] + (frameBufSize)/ ((1<< (i-1)) * (1<< (i-1))) ;
    algHandle->bufPtrsAlg[XY_ALG_BUF][i]  =
      algHandle->bufPtrsAlg[XY_ALG_BUF][i-1] + xyListSizePerLevel ;
  }

  algHandle->bufDesc[IMG_ALG_BUFDESC].numPlanes         = createParams->numLevels ;
  algHandle->bufDesc[XY_ALG_BUFDESC].numPlanes          = createParams->numLevels ;
  algHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC].numPlanes = createParams->numLevels - 1;
  for(i= 0; i < createParams->numLevels ; i++)
  {
    if(i !=0) /* for first the buffers are provided during process */
    {
      algHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[i].buf = algHandle->bufPtrsAlg[IMG_BUF][i];
      algHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[i].width = createParams->imgFrameWidth >> i ;
      algHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[i].frameROI.topLeft.x = 0 ;
      algHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[i].frameROI.topLeft.y = 0 ;
      algHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[i].frameROI.width  = createParams->imgFrameWidth >> i ;
      algHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[i].frameROI.height = createParams->imgFrameWidth >> i ;

      algHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC].bufPlanes[i-1].buf = algHandle->bufPtrsAlg[IMG_BUF][i];
      algHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC].bufPlanes[i-1].width = createParams->imgFrameWidth >> i ;
      algHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC].bufPlanes[i-1].frameROI.topLeft.x = 0 ;
      algHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC].bufPlanes[i-1].frameROI.topLeft.y = 0 ;
      algHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC].bufPlanes[i-1].frameROI.width  = createParams->imgFrameWidth >> i ;
      algHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC].bufPlanes[i-1].frameROI.height = createParams->imgFrameWidth >> i ;
    }

    algHandle->bufDesc[XY_ALG_BUFDESC].bufPlanes[i].buf = algHandle->bufPtrsAlg[XY_ALG_BUF][i];
    algHandle->bufDesc[XY_ALG_BUFDESC].bufPlanes[i].width = FAST9_BFFT_TI_MAXNUMFEATURES*sizeof(int32_t) ;
    algHandle->bufDesc[XY_ALG_BUFDESC].bufPlanes[i].height = 1;
    algHandle->bufDesc[XY_ALG_BUFDESC].bufPlanes[i].frameROI.topLeft.x = 0 ;
    algHandle->bufDesc[XY_ALG_BUFDESC].bufPlanes[i].frameROI.topLeft.y = 0 ;
    algHandle->bufDesc[XY_ALG_BUFDESC].bufPlanes[i].frameROI.width  = FAST9_BFFT_TI_MAXNUMFEATURES ; ;
    algHandle->bufDesc[XY_ALG_BUFDESC].bufPlanes[i].frameROI.height = 4 ;

  }

  {
    /*--------------------------------------------------------------------------------------------*/
    /* This variable is intentionally created seperately in the brace as the scope should be very */
    /* limited - one should not use intAlgHandle for any access in this function as it will       */
    /* touch EVE internal memory during create time which we should not do                        */
    /*--------------------------------------------------------------------------------------------*/
    ORB_TI_Handle intAlgHandle;
    intAlgHandle = (ORB_TI_Handle)memRec[ALG_HANDLE_INT_MEMREC].base;
    algHandle->pBufDescList[IMG_ALG_BUFDESC]         = &intAlgHandle->bufDesc[IMG_ALG_BUFDESC];
    algHandle->pBufDescList[IMG_PYRAMID_ALG_BUFDESC] = &intAlgHandle->bufDesc[IMG_PYRAMID_ALG_BUFDESC];
    algHandle->pBufDescList[XY_ALG_BUFDESC]          = &intAlgHandle->bufDesc[XY_ALG_BUFDESC];
    algHandle->pBufDescList[IMG_ALG_BUFDESC1]        = &intAlgHandle->bufDesc[IMG_ALG_BUFDESC];
  }


  /*--------------------------------------------------------*/

  memRecBaseId += NUM_MEMRECS ;

  /* copy rest all memrec given by application to one of the ALG memrec. it will be used during free */
  dummyMemRecs = ORB_TI_numAlloc() ;
  dummyMemRecs = dummyMemRecs - NUM_MEMRECS ;
  memcpy(memRec[DUMMY_MEMREC_INFO].base,memRec + NUM_MEMRECS, sizeof(IALG_MemRec)*dummyMemRecs);

  sizeConsumedIntPersist =  sizeConsumedExtPersist  = 0 ;
  /*-----------------------------------------------------------------*/
  /* Intialize the algorithm instance with the allocated memory                            */
  /* and user create parameters                                                                       */
  /*----------------------------------------------------------------*/
  FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algAlloc(
    (const IALG_Params *)(&fast9BFFTCreateParams), NULL, (IALG_MemRec*)memRec + memRecBaseId);
  ORB_TI_SetAlgToAppsMemRec(memRec, (IALG_MemRec*)memRec + memRecBaseId, numMemRecFast9BFFT,
    &sizeConsumedIntPersist, &sizeConsumedExtPersist  );

  handleApp = (IVISION_Handle) memRec[memRecBaseId].base;
  status = FAST9_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handleApp),
    memRec + memRecBaseId, NULL,(IALG_Params *)(&fast9BFFTCreateParams));
  algHandle->fast9BFFTHandle       = handleApp;
  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_FAST9_BFFT_CREATE_FAIL ;
    goto EXIT_FUNC_TI_INIT;
  }
  /*----------------------------------------------------------------*/
  HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algAlloc(
    (const IALG_Params *)(&harrisBFFTCreateParams), NULL, (IALG_MemRec*)memRec + memRecBaseId);
  ORB_TI_SetAlgToAppsMemRec(memRec, (IALG_MemRec*)memRec + memRecBaseId, numMemRecHarrisBFFT,
    &sizeConsumedIntPersist, &sizeConsumedExtPersist  );

  handleApp = (IVISION_Handle) memRec[memRecBaseId].base;
  status = HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handleApp),
    memRec + memRecBaseId, NULL,(IALG_Params *)(&harrisBFFTCreateParams));
  algHandle->harrisBFFTHandle      = handleApp;
  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_HARRIS_BFFT_CREATE_FAIL ;
    goto EXIT_FUNC_TI_INIT;
  }
  /*----------------------------------------------------------------*/
  FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algAlloc(
    (const IALG_Params *)(&fast9CornerDetectCreateParams), NULL, (IALG_MemRec*)memRec + memRecBaseId);
  ORB_TI_SetAlgToAppsMemRec(memRec, (IALG_MemRec*)memRec + memRecBaseId, numMemRecFast9CornerDetect,
    &sizeConsumedIntPersist, &sizeConsumedExtPersist  );

  handleApp = (IVISION_Handle) memRec[memRecBaseId].base;
  status = FAST9_CORNER_DETECT_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handleApp),
    memRec + memRecBaseId, NULL,(IALG_Params *)(&fast9CornerDetectCreateParams));
  algHandle->fast9CornerDetectHandle  = handleApp;
  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_FAST9_CORNER_CREATE_FAIL ;
    goto EXIT_FUNC_TI_INIT;
  }
  /*----------------------------------------------------------------*/
  RBRIEF_TI_VISION_FXNS.ialg.algAlloc(
    (const IALG_Params *)(&rBriefCreateParams), NULL, (IALG_MemRec*)memRec + memRecBaseId);
  ORB_TI_SetAlgToAppsMemRec(memRec, (IALG_MemRec*)memRec + memRecBaseId, numMemRecRBrief,
    &sizeConsumedIntPersist, &sizeConsumedExtPersist  );

  handleApp = (IVISION_Handle) memRec[memRecBaseId].base;
  status = RBRIEF_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handleApp),
    memRec + memRecBaseId, NULL,(IALG_Params *)(&rBriefCreateParams));
  algHandle->rBriefHandle     = handleApp;
  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_RBRIEF_CREATE_FAIL ;
    goto EXIT_FUNC_TI_INIT;
  }
  /*----------------------------------------------------------------*/
  IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algAlloc(
    (const IALG_Params *)(&imgPyramidCreateParams), NULL, (IALG_MemRec*)memRec + memRecBaseId);
  ORB_TI_SetAlgToAppsMemRec(memRec, (IALG_MemRec*)memRec + memRecBaseId, numMemRecImgPyramid,
    &sizeConsumedIntPersist, &sizeConsumedExtPersist  );

  handleApp = (IVISION_Handle) memRec[memRecBaseId].base;

  if(createParams->numLevels > 1)
  {
      status = IMAGE_PYRAMID_U8_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&handleApp),
          memRec + memRecBaseId, NULL,(IALG_Params *)(&imgPyramidCreateParams));
      algHandle->imgPyramidHandle  = handleApp;
  }

  if(status != IALG_EOK)
  {
    status = IORB_ERRORTYPE_IMGPYRAMID_CREATE_FAIL ;
    goto EXIT_FUNC_TI_INIT;
  }

  algHandle->numMemRecs  = NUM_MEMRECS;
  memcpy(algHandle->memRec,memRec, sizeof(IALG_MemRec)*NUM_MEMRECS);

  algHandle->ivision = (IVISION_Fxns *)&ORB_TI_VISION_FXNS;

  /*-----------------------------------------------------------------------*/
  /* State to indicate that internal context of algorithm is not active    */
  /*-----------------------------------------------------------------------*/
  algHandle->algState = ALG_NOT_ACTIVE;


EXIT_FUNC_TI_INIT:
  return (status);
}

/*-----------------------------------------------------------------------*/
/* Function to accept any run time updates with recreation of object     */
/* Refer algControl function for details in ivision.h file               */
/* Not implemented for this function                                     */
/*-----------------------------------------------------------------------*/
int32_t ORB_TI_control(IVISION_Handle handle,
                                       IALG_Cmd cmd,
                                       const IALG_Params *inParams,
                                       IALG_Params *outParams)
{
  int32_t status = IALG_EOK;

  return (status);
}


/*--------------------------------------------------------------------------*/
/* This is the main processing function and should be called for each frame */
/* Refer process function for details in ivision.h file                     */
/*--------------------------------------------------------------------------*/
int32_t ORB_TI_process(IVISION_Handle handle,
                                       IVISION_InBufs *inBufs,
                                       IVISION_OutBufs *outBufs,
                                       IVISION_InArgs *inArgs,
                                       IVISION_OutArgs *outArgs)
{
  ORB_TI_Handle algHandle = (ORB_TI_Handle)(handle);
  ORB_TI_Handle intAlgHandle;
  int32_t status            = IALG_EOK;
  uint8_t level, i ;
  IVISION_InBufs  inBufsORB ;
  IVISION_OutBufs outBufsORB  ;

  ORB_TI_OutArgs *orbOutArgs;
  ORB_TI_InArgs  *orbInArgs;


  FAST9_CORNER_DETECT_TI_OutArgs        fast9CornerDetectOutArgs ;
  FAST9_CORNER_DETECT_TI_InArgs         fast9CornerDetectInArgs ;
  FAST9_BEST_FEATURE_TO_FRONT_TI_InArgs fast9BFFTInArgs ;
  FAST9_BEST_FEATURE_TO_FRONT_TI_OutArgs fast9BFFTOutArgs ;
  IVISION_OutArgs                       outArgsInt;
  RBRIEF_TI_OutArgs                     rBRIEFOutArgs ;
  IMAGE_PYRAMID_U8_TI_outArgs           imgPyramidOutArgs ;

  IVISION_Handle   fast9CornerDetectHandle ;
  IVISION_Handle   fast9BFFTHandle ;
  IVISION_Handle   harrisBFFTHandle ;
  IVISION_Handle   rBriefHandle ;
  IVISION_Handle   imgPyramidHandle ;

  if( inBufs->numBufs < ORB_TI_BUFDESC_IN_TOTAL || outBufs->numBufs < ORB_TI_BUFDESC_OUT_TOTAL)
  {
    status = IVISION_ERRORTYPE_NUM_INBUF_LESS;
    goto Exit;
  }

  orbOutArgs = (ORB_TI_OutArgs *)outArgs;
  orbInArgs  = (ORB_TI_InArgs *)inArgs;

  /*-----------------------------------------------------------------------*/
  /* Activate the algorithm to make sure that now onwards internal memory  */
  /* handle can be utilized                                                */
  /*-----------------------------------------------------------------------*/
  ORB_TI_activate((IALG_Handle)handle);

  intAlgHandle            = (ORB_TI_Handle)algHandle->memRec[ALG_HANDLE_INT_MEMREC].base;
  fast9CornerDetectHandle = intAlgHandle->fast9CornerDetectHandle;
  fast9BFFTHandle         = intAlgHandle->fast9BFFTHandle        ;
  harrisBFFTHandle        = intAlgHandle->harrisBFFTHandle       ;
  rBriefHandle            = intAlgHandle->rBriefHandle           ;
  imgPyramidHandle        = intAlgHandle->imgPyramidHandle       ;

  /* Populate all the buffer descriptor required in ORB */
  intAlgHandle->pBufDescList[XY_USER_BUFDESC]     = outBufs->bufDesc[ORB_TI_BUFDESC_OUT_XY_LIST];
  intAlgHandle->pBufDescList[LEVEL_USER_BUFDESC]  = outBufs->bufDesc[ORB_TI_BUFDESC_OUT_LEVEL_ID];


  /* Populate the buffers (which are not populated during create time) of ORB */
  intAlgHandle->bufPtrsAlg[IMG_BUF][0] = (uint8_t*) inBufs->bufDesc[0]->bufPlanes[0].buf ;
  intAlgHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[0].buf                = inBufs->bufDesc[0]->bufPlanes[0].buf                ;
  intAlgHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[0].width              = inBufs->bufDesc[0]->bufPlanes[0].width              ;
  intAlgHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[0].frameROI           = inBufs->bufDesc[0]->bufPlanes[0].frameROI           ;
  intAlgHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[0].frameROI.width     = inBufs->bufDesc[0]->bufPlanes[0].frameROI.width     ;
  intAlgHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[0].frameROI.height    = inBufs->bufDesc[0]->bufPlanes[0].frameROI.height    ;
  intAlgHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[0].frameROI.topLeft.x = inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x ;
  intAlgHandle->bufDesc[IMG_ALG_BUFDESC].bufPlanes[0].frameROI.topLeft.y = inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y ;


  ((IVISION_OutArgs*)&fast9CornerDetectOutArgs)->size = sizeof(FAST9_CORNER_DETECT_TI_OutArgs);
  ((IVISION_OutArgs*)&fast9CornerDetectInArgs)->size  = sizeof(FAST9_CORNER_DETECT_TI_InArgs);
  ((IVISION_OutArgs*)&fast9BFFTInArgs)->size  = sizeof(FAST9_BEST_FEATURE_TO_FRONT_TI_InArgs);
  ((IVISION_OutArgs*)&fast9BFFTOutArgs)->size  = sizeof(FAST9_BEST_FEATURE_TO_FRONT_TI_OutArgs);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~IMAGE PYRAMID GENERATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  if(intAlgHandle->numLevels > 1)
  {
    inBufsORB.numBufs = 1 ;
    inBufsORB.bufDesc = &inBufs->bufDesc[ORB_TI_BUFDESC_IN_IMAGEBUFFER] ;

    outBufsORB.numBufs = 1 ;
    outBufsORB.bufDesc = &intAlgHandle->pBufDescList[IMG_PYRAMID_ALG_BUFDESC] ;

    imgPyramidHandle->fxns->ialg.algActivate((IALG_Handle)imgPyramidHandle);

    status = imgPyramidHandle->fxns->algProcess(
      imgPyramidHandle,
      &inBufsORB,
      &outBufsORB,
      (IVISION_InArgs *)inArgs,
      (IVISION_OutArgs *)&imgPyramidOutArgs);

    imgPyramidHandle->fxns->ialg.algDeactivate((IALG_Handle)imgPyramidHandle);
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~FAST9 CORNER DETECTION - MULTI LEVEL~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* Start all levels with same threshold */
  fast9CornerDetectHandle->fxns->ialg.algActivate((IALG_Handle)fast9CornerDetectHandle);
  for(level = 0; level < intAlgHandle->numLevels ;level++)
  {
    fast9CornerDetectInArgs.fast9Threshold[level] = intAlgHandle->fast9Threshold ;
  }
  fast9CornerDetectInArgs.levelMask = FAST9_CORNER_DETECT_TI_LEVEL_ALL ;

  inBufsORB.numBufs = 1 ;
  inBufsORB.bufDesc = &intAlgHandle->pBufDescList[IMG_ALG_BUFDESC] ;

  /*-----------------------------------------------------------------------------------------------------*/
  /* Out put buffer descriptor for FAST9 Corner Detect  - This buffer is requested during ORB create     */
  /* as scratch in ext memory                                                                            */
  /*-----------------------------------------------------------------------------------------------------*/
  outBufsORB.numBufs = 1 ;
  outBufsORB.bufDesc = &intAlgHandle->pBufDescList[XY_ALG_BUFDESC] ;


  status = fast9CornerDetectHandle->fxns->algProcess(
    fast9CornerDetectHandle,
    &inBufsORB,
    &outBufsORB,
    (IVISION_InArgs *)&fast9CornerDetectInArgs,
    (IVISION_OutArgs *)&fast9CornerDetectOutArgs);


  /*--------------------------------------------------------------------------------------------------------*/
  /* If some level is producing higher points than FAST9_BFFT_TI_MAXNUMFEATURES then increase the           */
  /* threshold and  call again  - this scheme is for demonstrate purpose and in actual the threshold should */
  /* be chosen appropriately and if the points are higjer points beyond the limit should be discarded       */
  /*--------------------------------------------------------------------------------------------------------*/
  if(orbInArgs->fast9CornerSelectMethod == ORB_FAST9_CORNERS_ITERATIVE)
  {
    do
    {
      /* Perfrom corner detection and keep increasing threshold to make sure max points are within limit */
      fast9CornerDetectInArgs.levelMask = 0  ;
      for(level = 0; level < intAlgHandle->numLevels ;level++)
      {
        if(fast9CornerDetectOutArgs.numCorners[level] > FAST9_BFFT_TI_MAXNUMFEATURES)
        {
          fast9CornerDetectInArgs.levelMask |= (1 << level) ;
          fast9CornerDetectInArgs.fast9Threshold[level]++ ;
        }
      }
      if(fast9CornerDetectInArgs.levelMask)
      {
        status = fast9CornerDetectHandle->fxns->algProcess(
          fast9CornerDetectHandle,
          &inBufsORB,
          &outBufsORB,
          (IVISION_InArgs *)&fast9CornerDetectInArgs,
          (IVISION_OutArgs *)&fast9CornerDetectOutArgs);
      }
    }while(fast9CornerDetectInArgs.levelMask);
  }

  if (outArgs->size == sizeof (ORB_TI_OutArgs) && status == IALG_EOK)
  {
    orbOutArgs->numCorners = 0 ;
    for(level = 0; level < intAlgHandle->numLevels ;level++)
    {
      orbOutArgs->activeImgWidth[level]    = fast9CornerDetectOutArgs.activeImgWidth[level];
      orbOutArgs->activeImgHeight[level]   = fast9CornerDetectOutArgs.activeImgHeight[level];
      if(fast9CornerDetectOutArgs.numCorners[level] > FAST9_BFFT_TI_MAXNUMFEATURES)
      {
         fast9CornerDetectOutArgs.numCorners[level] = FAST9_BFFT_TI_MAXNUMFEATURES ;
      }
      orbOutArgs->numCorners += fast9CornerDetectOutArgs.numCorners[level];
    }
    if(orbOutArgs->numCorners > intAlgHandle->bestNFeaturesOut)
    {
      orbOutArgs->numCorners = intAlgHandle->bestNFeaturesOut ;
    }
  }
  fast9CornerDetectHandle->fxns->ialg.algDeactivate((IALG_Handle)fast9CornerDetectHandle);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~FAST9 BEST FEATURE TO FRONT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(level = 0; level < intAlgHandle->numLevels ;level++)
  {
    /* At this point number of key points n this level is within the limit of FAST9 BFFT */
    /* Perfrom FAST9 BFFT */
    fast9BFFTInArgs.numFeaturesIn[level] = fast9CornerDetectOutArgs.numCorners[level] ;
    fast9BFFTInArgs.bestNFeatures[level] = intAlgHandle->bestNFeaturesOutFast9BFTF[level] ;
    inBufsORB.bufDesc[1]->bufPlanes[level].width = fast9CornerDetectOutArgs.numCorners[level] ;
  }
  fast9BFFTInArgs.suppressionMethod = FAST9_BFTF_TI_SUPPRESSION_4WAY;

  inBufsORB.numBufs = 2 ;
  inBufsORB.bufDesc = &intAlgHandle->pBufDescList[IMG_ALG_BUFDESC] ;

  fast9BFFTHandle->fxns->ialg.algActivate((IALG_Handle)fast9BFFTHandle);

  status   = fast9BFFTHandle->fxns->algProcess(
    fast9BFFTHandle,
    &inBufsORB,
    &outBufsORB,
    (IVISION_InArgs *) &fast9BFFTInArgs,
    (IVISION_OutArgs *)&fast9BFFTOutArgs);

#ifdef _DEBUG
  ORB_TI_DumpData(&outBufsORB, "FAST9_BFTF");
#endif

  fast9BFFTHandle->fxns->ialg.algDeactivate((IALG_Handle)fast9BFFTHandle);


  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~HARRIS BEST FEATURE TO FRONT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  harrisBFFTHandle->fxns->ialg.algActivate((IALG_Handle)harrisBFFTHandle);
  outBufsORB.numBufs = 2 ;
  outBufsORB.bufDesc = &intAlgHandle->pBufDescList[XY_USER_BUFDESC] ;
  for(level = 0; level < intAlgHandle->numLevels ;level++)
  {
    inBufsORB.bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]->bufPlanes[level].frameROI.width =
      fast9BFFTOutArgs.bestNFeaturesOut[level] ;
  }

  status = harrisBFFTHandle->fxns->algProcess(
    harrisBFFTHandle,
    &inBufsORB,
    &outBufsORB,
    (IVISION_InArgs *)inArgs,
    (IVISION_OutArgs *)&outArgsInt);

#ifdef _DEBUG
  ORB_TI_DumpData(&outBufsORB, "HARRIS_BFTF");
#endif

  harrisBFFTHandle->fxns->ialg.algDeactivate((IALG_Handle)harrisBFFTHandle);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~ RBRIEF - ORB DESCRIPTOR GENERATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  inBufsORB.numBufs = 3 ;
  inBufsORB.bufDesc = &intAlgHandle->pBufDescList[IMG_ALG_BUFDESC1] ;
  outBufsORB.numBufs = 1 ;
  outBufsORB.bufDesc = &outBufs->bufDesc[ORB_TI_BUFDESC_OUT_DESCRIPTOR] ;

  rBriefHandle->fxns->ialg.algActivate((IALG_Handle)rBriefHandle);

  status = rBriefHandle->fxns->algProcess(
    rBriefHandle,
    &inBufsORB,
    &outBufsORB,
    (IVISION_InArgs *)inArgs,
    (IVISION_OutArgs *)&rBRIEFOutArgs);

  rBriefHandle->fxns->ialg.algDeactivate((IALG_Handle)rBriefHandle);

Exit:
  /*----------------------------------*/
  /* Free the input and output buffer */
  /*----------------------------------*/
  for (i = 0 ; i < ORB_TI_BUFDESC_IN_TOTAL ; i++)
  {
    outArgs->inFreeBufIDs[0]    = inBufs->bufDesc[i]->bufferId ;
  }
  outArgs->inFreeBufIDs[i]    = 0 ;
  for (i = 0 ; i < ORB_TI_BUFDESC_OUT_TOTAL ; i++)
  {
    outArgs->outFreeBufIDs[i]   = outBufs->bufDesc[i]->bufferId ;
    outBufs->bufDesc[i]->bufPlanes[0].accessMask = IVISION_ACCESSMODE_HWA;
  }
  outArgs->outFreeBufIDs[i]   = 0 ;
  return status;

}

/*--------------------------------------------------------------------------*/
/* This is the function to do activation of algorithm. All scratch memory   */
/* are restored in this                                                     */
/* Refer algActivate function for details in ialg.h file                    */
/*--------------------------------------------------------------------------*/
XDAS_Void  ORB_TI_activate(IALG_Handle handle)
{
  ORB_TI_Handle algHandle = (ORB_TI_Handle)(handle);
  int i;

  /*----------------------------------------------------------------*/
  /* Do Activation only if it is deactivated or just after creation */
  /*----------------------------------------------------------------*/
  if(algHandle->algState == ALG_NOT_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC))
      {

        EDMA_UTILS_memcpy2D(algHandle->memRec[i].base,
          algHandle->memRec[i-1].base,
          algHandle->memRec[i].size,
          1,
          0,
          0);
      }

    }
    algHandle->algState = ALG_ACTIVE;
  }

  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function to do de-activation of algorithm. All scratch memory*/
/* are stoed to external memory in this                                     */
/* Refer algDeactivate function for details in ialg.h file                  */
/*--------------------------------------------------------------------------*/
XDAS_Void  ORB_TI_deactivate(IALG_Handle handle)
{
  ORB_TI_Handle algHandle = (ORB_TI_Handle)(handle);
  int i;

  if(algHandle->algState != ALG_NOT_ACTIVE)
  {
    for(i= 1; i < algHandle->numMemRecs; i++)
    {
      if((i == ALG_HANDLE_INT_MEMREC))
      {
        EDMA_UTILS_memcpy2D(algHandle->memRec[i-1].base,
          algHandle->memRec[i].base,
          algHandle->memRec[i].size,
          1,
          0,
          0);
      }

    }
    algHandle->algState = ALG_NOT_ACTIVE;
  }
  return;
}

/*--------------------------------------------------------------------------*/
/* This is the function which user can call to get back the memory given to */
/* algo                                                                     */
/* Refer algFree function for details in ialg.h file                        */
/*--------------------------------------------------------------------------*/
int32_t ORB_TI_free(IALG_Handle handle, IALG_MemRec *memRec)
{
  int32_t status            = IALG_EOK;
  ORB_TI_Handle algHandle = (ORB_TI_Handle)(handle);
  int32_t dummyMemRecs ;

  dummyMemRecs = ORB_TI_numAlloc() ;
  dummyMemRecs = dummyMemRecs - NUM_MEMRECS ;

  memcpy(
    memRec,
    algHandle->memRec,
    sizeof(IALG_MemRec)*algHandle->numMemRecs);

  memcpy(
    memRec + algHandle->numMemRecs,
    algHandle->memRec[DUMMY_MEMREC_INFO].base,
    sizeof(IALG_MemRec)*dummyMemRecs);

  return status;
}
