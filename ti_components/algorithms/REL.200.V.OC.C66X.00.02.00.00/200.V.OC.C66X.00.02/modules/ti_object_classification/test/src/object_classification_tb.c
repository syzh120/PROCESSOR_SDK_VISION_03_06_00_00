/*
* module name       :TI Object Classification
*
* module descripton :Classification of German traffic signs using TI’s C66x DSP
*
*/
/*

Copyright (c) [2014] – [2017] Texas Instruments Incorporated

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

/** @file object_classification_tb.c
*
*  @brief  This is a test bench file for object classification module.
*          This test interface is common for PD,TSR and VD
*
*  @date   Nov 2015
*
*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "xdais_types.h"
#include "object_classification_config.h"
#include "iobjclass_ti.h"

#include "ti_mem_manager.h"
#include "ti_file_io.h"

#define DISABLE_FILE_IO 0
#define IO_PERSISTENT_DATA 0
#define DISPLAY_HEADER 0

#if (HOST_EMULATION)
#define DISABLE_FILE_IO 0
#endif

#define DUMP_DETECTED_ROI  (1)

#define INPUT_OBJ_WIDTH  (36)
#define INPUT_OBJ_HEIGHT (36)

#if (!HOST_EMULATION)

void _TSC_enable();
long long _TSC_read();

#define L1D_SRAM_ADDR (0x00F00000)

#define L2CFG()  (*(volatile uint32_t *)0x01840000)
#define L1PCFG() (*(volatile uint32_t *)0x01840020)
#define L1DCFG() (*(volatile uint32_t *)0x01840040)
#define MAR148() (*(volatile uint32_t *)0x01848250)
#define MAR149() (*(volatile uint32_t *)0x01848254)

void SetMAR()
{

  uint32_t i ;

  uint32_t* MAR = (uint32_t*)0x01848000;

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
  /*-------------------------------------------------------------------------*/
  /* 4-> full 256 KB as cache, 3-> 128KB, 2 -> 64KB, 1-> 32KB                */
  /* IMPORTANT :: Currently 0 KB of L2 is assumed to be SRAM, hence in final */
  /* application any amount L2 can be configured as SRAM, but DMVAL will not */
  /* use that. Only thing here important is that if in application full L2 is*/
  /* configured as cache then standalone and final application performance   */
  /* numbers will match. otherwise no functionality issue.                    */
  /*-------------------------------------------------------------------------*/
  L2CFG()  = 2;

  /*-------------------------------------------------------------------------*/
  /* Full L1P is configured as 32KB of cache                                 */
  /* Nothing in L1P is assumed as SRAM, so no dependency from final applicati*/
  /* -on configuration. Only thing if full L1P is configured as cache then   */
  /* standalone and application performance numbers will match.              */
  /*-------------------------------------------------------------------------*/
  L1PCFG() = 4;

 /*--------------------------------------------------------------------------*/
  /* 1 -> 4 KB, 2-> 8KB, 3 ->16 KB, 4 -> 32KB as cache                       */
  /* Currently 4KB as cache has been allocated for L1D, Rest 28 KB is configu*/
  /* red as SRAM. Any change in cache configuration should be done in conjuca*/
  /* of linker command file modification in test applciation                 */
  /* IMPORTANT :: Here 28 KB of L1 D is assumed as SRAM hence there is depend*/
  /* -dency from final applcaition configuration of L1D. If atleast 28 KB of */
  /* L1D is not configured as SRAM in final application then that will be a  */
  /* functional issue.                                                       */
  /*-------------------------------------------------------------------------*/
  L1DCFG() = 4;

  SetMAR() ;
}

#endif //!HOST_EMULATION

/**
 *  @enum   eMemrecs
 *  @brief  Memory records for Feature Plane classification applet
 *
*/
typedef enum
{
  /* Memory records for handle */
 /* Alg Handle should be first entry in this enum table
  as test app is expecting it to be first entry*/
  ALG_HANDLE_MEMREC,
  ALG_OC_INFO_MEMREC,
  ALG_INT_MEM_MEMREC,
  ALG_EXT_MEM_MEMREC,
  ALG_TS_STATE_MEMREC,
  ALG_INT_EDMA_MEMREC,
  NUM_MEMRECS

} eMemrecs;

/**
 *  @struct  TI_OC_Obj
 *  @brief   This structure is the main handle of OD algorithm
 *
 *  @param ivision           : All public function pointers
 *  @param algState          : State of algorithm to indicate
 *  @param numMemRecs        : Number of memory records
 *  @param memRec            : Array of memory records
 *  @param edma3RmLldHandle  : Pointer to EDMA3 LLD resource manager
 *  @param maxImageWidth     : Maximum width of input image
 *  @param maxImageHeight    : Maximum height of input image
 *  @param maxScales         : Maximum scales of input image
*/
typedef struct
{
  IVISION_Fxns      *ivision;
  uint8_t           algState;
  uint32_t          numMemRecs;
  IALG_MemRec       memRec[NUM_MEMRECS];
  void             *edma3RmLldHandle;
  uint16_t          maxImageWidth;
  uint16_t          maxImageHeight;
  uint16_t          maxScales;
  int32_t           firstTimeFlag;
  int32_t           frameNum;

} TI_OC_Obj;

#define PRINT_ERROR_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#define DMEM_SIZE (224 * 1024)
#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
uint8_t DMEM_SCRATCH[DMEM_SIZE];

#define MAX_IMAGE_PYRAMID_SIZE  (8 * 1024 * 1024)
#pragma DATA_SECTION(imgPyrData,".imgPyrDat");
uint8_t imgPyrData[MAX_IMAGE_PYRAMID_SIZE];

#define MAX_DETECTION_LIST_SIZE (32 * 1024)
#pragma DATA_SECTION(objListData,".objListDat");
uint8_t objListData[MAX_DETECTION_LIST_SIZE];

uint8_t cbBuf[640 * 360], crBuf[640 * 360];

TIMemObject memObj_DMEM;
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM = &memObj_DMEM;
  for (i = 0; i < numMemRec; i++)
  {
    if((memRec[i].space == IALG_DARAM1) || (memRec[i].space == IALG_DARAM0)) {
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
    if(memRec[i].space == IALG_EXTERNAL) {
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

int32_t TestApp_storePersistent(IALG_MemRec * memRec,int32_t numMemRec)
{
  char fileName[] = "C:\\Work\\C66\\ODFlow\\data\\oc_memtab_";
  FILE *fp;
  int32_t i;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].attrs == IALG_PERSIST)
    {
       char newName[512];
       char buffer[16];

       strcpy(newName, fileName);
       sprintf(buffer, "%d", i);
       strcat(newName, buffer);
       strcat(newName, ".bin");

       fp = fopen(newName, "wb");

       if(fp == NULL)
       {
          printf("Unable to store persistent data!\n");
          return IALG_EFAIL;
       }

       fwrite((void *)memRec[i].base,1, memRec[i].size,fp);

       fclose(fp);
    }
  }
  return IALG_EOK;
}

int32_t TestApp_restorePersistent(IALG_MemRec * memRec,int32_t numMemRec)
{
  char fileName[] = "C:\\Work\\C66\\ODFlow\\data\\oc_memtab_";
  FILE *fp;
  int32_t i;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].attrs == IALG_PERSIST)
    {
       char newName[512];
       char buffer[16];

       strcpy(newName, fileName);
       sprintf(buffer, "%d", i);
       strcat(newName, buffer);
       strcat(newName, ".bin");

       fp = fopen(newName, "rb");

       if(fp == NULL)
       {
          printf("Unable to restore persistent file!\n");
          return IALG_EFAIL;
       }

       fread((void *)memRec[i].base,1, memRec[i].size,fp);

       fclose(fp);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

int32_t TestApp_AllocIOBuffers(IVISION_InBufs * inBufs,IVISION_OutBufs * outBufs)
{
  inBufs->bufDesc[0]->numPlanes                          = 1;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[0]->bufPlanes[0].width                 = MAX_IMAGE_PYRAMID_SIZE;
  inBufs->bufDesc[0]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[0]->bufPlanes[0].width;
  inBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = inBufs->bufDesc[0]->bufPlanes[0].frameROI.height;
  inBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;
  inBufs->bufDesc[0]->bufPlanes[0].buf                   = &imgPyrData[0];

  inBufs->bufDesc[1]->numPlanes                          = 1;
  inBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.x    = 0;
  inBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.y    = 0;
  inBufs->bufDesc[1]->bufPlanes[0].width                 = TI_OC_INPUT_LIST_SIZE;
  inBufs->bufDesc[1]->bufPlanes[0].height                = 1;
  inBufs->bufDesc[1]->bufPlanes[0].frameROI.width        = inBufs->bufDesc[0]->bufPlanes[0].width;
  inBufs->bufDesc[1]->bufPlanes[0].frameROI.height       = inBufs->bufDesc[0]->bufPlanes[0].frameROI.height;
  inBufs->bufDesc[1]->bufPlanes[0].planeType             = 0;
  inBufs->bufDesc[1]->bufPlanes[0].buf                   = &objListData[0];

  outBufs->bufDesc[0]->numPlanes                          = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs->bufDesc[0]->bufPlanes[0].width                 = TI_OC_OUTPUT_LIST_SIZE;
  outBufs->bufDesc[0]->bufPlanes[0].height                = 1;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.width        = TI_OC_OUTPUT_LIST_SIZE;
  outBufs->bufDesc[0]->bufPlanes[0].frameROI.height       = 1;
  outBufs->bufDesc[0]->bufPlanes[0].planeType             = 0;

  outBufs->bufDesc[0]->bufPlanes[0].buf = malloc(outBufs->bufDesc[0]->bufPlanes[0].width * outBufs->bufDesc[0]->bufPlanes[0].height);
  if((outBufs->bufDesc[0]->bufPlanes[0].buf == NULL))
  {
    PRINT_ERROR_MSG();
  }
  memset(outBufs->bufDesc[0]->bufPlanes[0].buf ,0,outBufs->bufDesc[0]->bufPlanes[0].width * outBufs->bufDesc[0]->bufPlanes[0].height);

#if DUMP_DETECTED_ROI
  outBufs->bufDesc[1]->numPlanes                          = 1;
  outBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.x    = 0;
  outBufs->bufDesc[1]->bufPlanes[0].frameROI.topLeft.y    = 0;
  outBufs->bufDesc[1]->bufPlanes[0].width                 = INPUT_OBJ_WIDTH;
  outBufs->bufDesc[1]->bufPlanes[0].height                = INPUT_OBJ_HEIGHT * 3;
  outBufs->bufDesc[1]->bufPlanes[0].frameROI.width        = INPUT_OBJ_WIDTH;
  outBufs->bufDesc[1]->bufPlanes[0].frameROI.height       = INPUT_OBJ_HEIGHT;
  outBufs->bufDesc[1]->bufPlanes[0].planeType             = 0;

  outBufs->bufDesc[1]->bufPlanes[0].buf = malloc(outBufs->bufDesc[1]->bufPlanes[0].width * outBufs->bufDesc[1]->bufPlanes[0].height * TI_OC_MAX_NUM_OBJECTS);
  if((outBufs->bufDesc[1]->bufPlanes[0].buf == NULL))
  {
     PRINT_ERROR_MSG();
  }
  memset(outBufs->bufDesc[1]->bufPlanes[0].buf ,0,outBufs->bufDesc[1]->bufPlanes[0].width * outBufs->bufDesc[1]->bufPlanes[0].height * TI_OC_MAX_NUM_OBJECTS);
#endif

  return IALG_EOK;
}


int32_t TestApp_ReadInBufs(IVISION_InBufs *inBufs, int32_t currFrameNum, char *fileName, int32_t numScales)
{
  IVISION_BufDesc *imgPyrData;
  int32_t metaDataSize;
  int32_t imgPyrSize;
  uint8_t *pPyrBase;
  int32_t i;

#ifdef USE_HOST_FILE_IO
  HOSTFILE * fp;
#else
  FILE * fp;
#endif

  fp = FOPEN(fileName, "rb");

  metaDataSize = sizeof(IVISION_BufDesc) * TI_OC_MAX_TOTAL_SCALES;
  FREAD(inBufs->bufDesc[0]->bufPlanes[0].buf, 1, metaDataSize, fp);
  imgPyrData = (IVISION_BufDesc *)inBufs->bufDesc[0]->bufPlanes[0].buf;

  imgPyrSize = 0;
  for(i = 0; i < numScales; i++)
  {
     imgPyrSize += imgPyrData[i].bufPlanes[0].width * imgPyrData[i].bufPlanes[0].height;
     imgPyrSize += imgPyrData[i].bufPlanes[1].width * imgPyrData[i].bufPlanes[1].height;
  }

  FSEEK(fp, (currFrameNum * (imgPyrSize + metaDataSize) + metaDataSize), SEEK_SET);

  pPyrBase = (uint8_t *)inBufs->bufDesc[0]->bufPlanes[0].buf + metaDataSize;

#if (!DISABLE_FILE_IO)
#ifdef USE_HOST_FILE_IO
{
    int32_t nChunks, reminder, ctr;
    int32_t ONE_MEGA_BYTE = 0x100000;

    nChunks  = imgPyrSize / ONE_MEGA_BYTE;
    reminder = imgPyrSize % ONE_MEGA_BYTE;
    ctr = 0;
    for(ctr = 0; ctr < nChunks; ctr++)
       FREAD((void *)(pPyrBase + (ctr * ONE_MEGA_BYTE)),1,ONE_MEGA_BYTE,fp);

    if(reminder)
       FREAD((void *)(pPyrBase + (ctr * ONE_MEGA_BYTE)),1,reminder,fp);
}
#else
  FREAD((void *)pPyrBase,1,imgPyrSize,fp);
#endif
#endif

  for(i = 0; i < numScales; i++)
  {
     imgPyrData[i].bufPlanes[0].buf = pPyrBase;
     pPyrBase = (uint8_t *)pPyrBase + (imgPyrData[i].bufPlanes[0].width * imgPyrData[i].bufPlanes[0].height);
     imgPyrData[i].bufPlanes[1].buf = pPyrBase;
     pPyrBase = (uint8_t *)pPyrBase + (imgPyrData[i].bufPlanes[1].width * imgPyrData[i].bufPlanes[1].height);
  }

  FCLOSE(fp);

  return (0);
}

int32_t TestApp_ReadDetections(IVISION_InBufs *inBufs, int32_t currFrameNum, char *fileName)
{
  FILE * fp;
  int32_t listSize;

  fp = fopen(fileName, "rb");

  listSize = sizeof(TI_OC_inputList);

  fseek(fp, (currFrameNum * listSize), SEEK_SET);
  fread((void *)((uint8_t *)inBufs->bufDesc[1]->bufPlanes[0].buf),1,listSize,fp);
  fclose(fp);

  return (0);
}

int32_t TestApp_WriteOutScales(IVISION_InBufs * inBufs, int32_t curFrame, char * fileName, int32_t numScales)
{
  IVISION_BufDesc *imgPyrData;
  uint8_t *pSrc;
  int32_t metaDataSize, lumaSize, chromaSize, ctr;
  int32_t bufOffset;

#ifdef USE_HOST_FILE_IO
  HOSTFILE * fp;
#else
  FILE * fp;
#endif

   metaDataSize = sizeof(IVISION_BufDesc) * TI_OC_MAX_TOTAL_SCALES;
   imgPyrData = (IVISION_BufDesc *)inBufs->bufDesc[0]->bufPlanes[0].buf;

  bufOffset = metaDataSize;
  for(ctr = 0; ctr < numScales; ctr++)
  {
        char newName[512];
        char buffer[16];

        strcpy(newName, fileName);
        strcat(newName, "_fr_");
        sprintf(buffer, "%d", curFrame);
        strcat(newName, buffer);
        strcat(newName, "_scale_");
        sprintf(buffer, "%d", ctr);
        strcat(newName, buffer);
        strcat(newName, "_");
        sprintf(buffer, "%d", imgPyrData[ctr].bufPlanes[0].width);
        strcat(newName, buffer);
        strcat(newName, "x");
        sprintf(buffer, "%d", imgPyrData[ctr].bufPlanes[0].height);
        strcat(newName, buffer);
        strcat(newName, ".yuv");

        fp = FOPEN(newName, "wb+");

        if(fp == NULL)
        {
            printf("Unable to open Output file!\n");
            return (-1);
        }

        pSrc = (uint8_t *)inBufs->bufDesc[0]->bufPlanes[0].buf + bufOffset;

        lumaSize = imgPyrData[ctr].bufPlanes[0].width * imgPyrData[ctr].bufPlanes[0].height;
        chromaSize = imgPyrData[ctr].bufPlanes[1].width * imgPyrData[ctr].bufPlanes[1].height;


        FWRITE((void *)pSrc,1, (lumaSize + chromaSize),fp);
        bufOffset += (lumaSize + chromaSize);
        FCLOSE(fp);
  }

  return (0);
}
#if DUMP_DETECTED_ROI
int32_t TestApp_WriteOutBufs(IVISION_OutBufs * outBufs, char * fileName, int32_t curFrame, int32_t numObjects)
{
  int32_t size;

  FILE * fp;

  char newName[512];
  char buffer[16];

  strcpy(newName, fileName);
  strcat(newName, "_36x36_fr_");
  sprintf(buffer, "%d", curFrame);
  strcat(newName, buffer);
  strcat(newName, "_objs_");
  sprintf(buffer, "%d", numObjects);
  strcat(newName, buffer);
  strcat(newName, ".rgb");

  fp = fopen(newName, "wb+");

  if(fp == NULL)
  {
      printf("Unable to open Output file!\n");
      return (-1);
  }

  size = outBufs->bufDesc[1]->bufPlanes[0].width * outBufs->bufDesc[1]->bufPlanes[0].height * numObjects;

  fwrite((void *)((uint32_t)outBufs->bufDesc[1]->bufPlanes[0].buf),1,size,fp);

  fclose(fp);

  return (0);
}
#endif

int32_t objectClassificationTest(sObjectClassification_Config * testcaseParams)
{
  IALG_MemRec *memRec;
  FILE *fpOut ;
  int32_t numMemRec;
  int32_t status;
  uint32_t testcase;
  uint8_t  levelCnt=0;
  int32_t j;
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
  TI_OC_CreateParams   createParams;

  TI_OC_InArgs      inArgs;
  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   inBufDesc1;
  IVISION_BufDesc   inBufDesc2;
  IVISION_BufDesc   *inBufDescList[TI_OC_IN_BUFDESC_TOTAL];

  TI_OC_OutArgs     outArgs;
  IVISION_OutBufs   outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   outBufDesc1;
#if DUMP_DETECTED_ROI
  IVISION_BufDesc   outBufDesc2;
#endif
  IVISION_BufDesc   *outBufDescList[TI_OC_OUT_BUFDESC_TOTAL];

  outArgs.iVisionOutArgs.size = sizeof(TI_OC_OutArgs);
  inArgs.iVisionInArgs.size   = sizeof(TI_OC_InArgs);

  TI_OC_objectDescriptor *pObjDesc;
  TI_OC_outputList *pOutList;
  uint32_t frameIdx;

  objectClassification_numTestCases  = 1;

  for (testcase = 0 ; testcase < objectClassification_numTestCases; testcase++)
  {

    /*-----------------------------------------------------------------
    Set buffer descriptor pointers array base
    -----------------------------------------------------------------*/
    inBufs.bufDesc  = inBufDescList;
    outBufs.bufDesc = outBufDescList;

    inBufs.numBufs   = TI_OC_IN_BUFDESC_TOTAL;
    outBufs.numBufs  = TI_OC_OUT_BUFDESC_TOTAL;

    inBufDescList[TI_OC_IN_BUFDESC_IMAGE_PYRAMID]  = &inBufDesc1;
    inBufDescList[TI_OC_IN_BUFDESC_DETECTION_LIST] = &inBufDesc2;

    outBufDescList[TI_OC_OUT_BUFDESC_OBJECT_LIST]  = &outBufDesc1;
#if DUMP_DETECTED_ROI
    outBufDescList[TI_OC_OUT_BUFDESC_IMAGE_LIST]   = &outBufDesc2;
#else
    outBufDescList[TI_OC_OUT_BUFDESC_IMAGE_LIST]   = NULL;
#endif
    createParams.maxImageWidth  = testcaseParams[testcase].maxImageWidth;
    createParams.maxImageHeight = testcaseParams[testcase].maxImageHeight;
    createParams.maxScales      = testcaseParams[testcase].maxScales;

    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
    createParams.edma3RmLldHandle   = NULL;

    /*-----------------------------------------------------------------
    Create DMEM Handle
    -----------------------------------------------------------------*/
    TI_CreateMemoryHandle(&memObj_DMEM, DMEM_SCRATCH, DMEM_SIZE);

    /*-----------------------------------------------------------------
    Query alogorithm memory requirement using standard IALG interface
    -----------------------------------------------------------------*/
    numMemRec = TI_OC_VISION_FXNS.ialg.algNumAlloc();
    memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

    status = TI_OC_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&createParams), NULL, memRec);

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    /*-----------------------------------------------------------------
    Allocate memory for all the mem records
    Application has to implement the below function
    Refer the example implementation below in this file
    -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(memRec,numMemRec);
    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }
#if IO_PERSISTENT_DATA
    status = TestApp_restorePersistent(memRec,numMemRec);
#endif
    /*-----------------------------------------------------------------
    Intialize the algorithm instance with the alocated memory
    and user create parameters
    -----------------------------------------------------------------*/
    status = TI_OC_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle), memRec,NULL,(IALG_Params *)(&createParams));


    handle = (IM_Fxns *) memRec[0].base;

    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
      goto EXIT_LOOP;
    }

    inArgs.iVisionInArgs.subFrameInfo       = 0;
    inArgs.iVisionInArgs.size               = sizeof(TI_OC_InArgs);

    inBufDesc1.numPlanes                    = 1;
    inBufDesc2.numPlanes                    = 1;
    outBufDesc1.numPlanes                   = 1;

    TestApp_AllocIOBuffers(&inBufs,&outBufs);

    fpOut = fopen((char *)testcaseParams[testcase].outFileName,"w+");
    if(fpOut == NULL)
    {
      printf("Unable to open output file\n");
      goto EXIT_LOOP;
    }

    for(frameIdx = 0; frameIdx < testcaseParams[testcase].maxFrames;frameIdx++)
    {

      TI_OC_Obj *objPtr = (TI_OC_Obj *)memRec[0].base;
      printf("Frame %d : ",objPtr->frameNum);
      fprintf(fpOut,"Frame %d detections \n", objPtr->frameNum);

      inArgs.inputMode         = testcaseParams[testcase].inputMode;
      inArgs.classifierType    = testcaseParams[testcase].classifierType;

      //Set reserved params to 0 for normal operation
      inArgs.reserved0  = 0;
      inArgs.reserved1  = 0;
      inArgs.reserved2  = 0;
      inArgs.reserved3  = 0;

      TestApp_ReadInBufs(&inBufs, frameIdx, (char *)testcaseParams[testcase].inFileName1, createParams.maxScales);
      TestApp_ReadDetections(&inBufs, frameIdx, (char *)testcaseParams[testcase].inFileName2);
      //TestApp_WriteOutScales(&inBufs, frameIdx, (char *)testcaseParams[testcase].imgFileName, createParams.maxScales);

#if (!HOST_EMULATION)
      t0 = _TSC_read();
#endif

      status = handle->ivision->algProcess((IVISION_Handle)handle,
                                            &inBufs,
                                            &outBufs,
                                           (IVISION_InArgs  *)&inArgs,
                                           (IVISION_OutArgs *)&outArgs);

#if (!HOST_EMULATION)
      t1 = _TSC_read();
#endif

      if(status != IALG_EOK)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }
#if IO_PERSISTENT_DATA
      status = TestApp_storePersistent(memRec,numMemRec);
      if(status != IALG_EOK)
      {
         PRINT_ERROR_MSG();
         goto EXIT_LOOP;
      }
#endif
      status = TI_OC_Report_Error(outArgs.errorCode);

      if(status != IALG_EOK)
      {
        PRINT_ERROR_MSG();
        goto EXIT_LOOP;
      }

      pOutList  = (TI_OC_outputList *)outBufs.bufDesc[0]->bufPlanes[0].buf;
      pObjDesc  = &pOutList->objDesc[0];

      for(j = 0; j < pOutList->numObjects; j++)
      {
        if(pObjDesc->objType == TI_OC_PEDESTRIAN)
            fprintf(fpOut,"PD at %4d,%4d,%4d,%4d ID = %4d",pObjDesc->xPos, pObjDesc->yPos, pObjDesc->objWidth, pObjDesc->objHeight, pObjDesc->objSubType);


        if(pObjDesc->objType == TI_OC_TRAFFIC_SIGN)
            fprintf(fpOut,"TSR at %4d,%4d,%4d,%4d ID = %4d",pObjDesc->xPos, pObjDesc->yPos, pObjDesc->objWidth, pObjDesc->objHeight, pObjDesc->objSubType);


        if(pObjDesc->objType == TI_OC_VEHICLE)
            fprintf(fpOut,"VD at %4d,%4d,%4d,%4d ID = %4d",pObjDesc->xPos, pObjDesc->yPos, pObjDesc->objWidth, pObjDesc->objHeight, pObjDesc->objSubType);

        fprintf(fpOut,"\n");
        pObjDesc++;
      }

#if (!HOST_EMULATION)
{
    int32_t divFactor;

    if(pOutList->numObjects == 0)
       divFactor = 1;
    else
       divFactor = pOutList->numObjects;
    printf("Total Cycles: %8lld, NUM Detections: %4d, Avg cycles per Detection: %8lld ", (t1-t0), pOutList->numObjects, (t1-t0) / divFactor);
}
#endif
    printf("\n");
#if DUMP_DETECTED_ROI
    TestApp_WriteOutBufs(&outBufs, (char *)testcaseParams[testcase].imgFileName, frameIdx, pOutList->numObjects);
#endif
    }
    fprintf(fpOut,"\n");

EXIT_LOOP:
    if(fpOut)
    {
        fflush(fpOut);
        fclose(fpOut);
    }

#if (!IO_PERSISTENT_DATA)
    status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
    if(status != IALG_EOK)
    {
      PRINT_ERROR_MSG();
    }
#endif

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

    for ( levelCnt = 0 ; levelCnt < inBufDesc1.numPlanes ; levelCnt++)
    {
      if ( inBufDesc1.bufPlanes[levelCnt].buf != NULL )
      {
        //free(inBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < inBufDesc2.numPlanes ; levelCnt++)
    {
      if ( inBufDesc2.bufPlanes[levelCnt].buf != NULL )
      {
        //free(inBufDesc.bufPlanes[levelCnt].buf);
      }
    }

    for ( levelCnt = 0 ; levelCnt < outBufDesc1.numPlanes ; levelCnt++)
    {
      if ( outBufDesc1.bufPlanes[levelCnt].buf != NULL )
      {
        free(outBufDesc1.bufPlanes[levelCnt].buf);
      }
    }
#if DUMP_DETECTED_ROI
    for ( levelCnt = 0 ; levelCnt < outBufDesc2.numPlanes ; levelCnt++)
    {
      if ( outBufDesc2.bufPlanes[levelCnt].buf != NULL )
      {
        free(outBufDesc2.bufPlanes[levelCnt].buf);
      }
    }
#endif
  }
  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  char configFile[FILE_NAME_SIZE]={0};

#if (!HOST_EMULATION)
  InitCache();
#endif

#ifdef USE_HOST_FILE_IO
    ti_fileio_init();
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
#if IO_PERSISTENT_DATA
    strcpy(configFile,"C:\\Work\\C66\\ODFlow\\oc\\object_classification.cfg");
#else
    strcpy(configFile,"../testvecs/config/object_classification.cfg");
#endif
  }

  status = readparamfile(configFile, &gsTokenMap_objectClassification[0]) ;
  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  status = objectClassificationTest(gConfig_objectClassification);

  return status;
}



