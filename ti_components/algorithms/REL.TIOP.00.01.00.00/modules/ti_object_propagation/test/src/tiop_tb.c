/*
*
* Copyright (c) {2018} Texas Instruments Incorporated
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


/** @file tiop_tb.c
*
*  @brief  This file contains test code for TI OP test application
*
*
*  @date   July 2018
*
*/
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "xdais_types.h"
#include "iop_ti.h"
#include "tiop_config.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"
#if HOST_EMULATION
#define Cache_WbInvAll()
#define _TSC_enable() 
#else
#include "cache.h"
#include "profile.h"
#define ENABLE_TRACE_PROFILE  (0)
#endif
#include "buffermanager.h"

void _TSC_enable();  
long long _TSC_read();
uint64_t tsc_start1, tsc_cycles;
uint64_t tsc_start, tsc_end;
uint64_t tsc_cycles1, tsc_cycles2, tsc_cycles3;
uint64_t tsc_cycles4, tsc_cycles5, tsc_cycles6;
uint64_t tsc_endLK;
uint64_t tsc_startLK;
uint64_t tsc_cyclesLK1, tsc_cyclesLK2, tsc_cyclesLK3;
uint64_t tsc_endHC;
uint64_t tsc_startHC;
uint64_t tsc_cyclesHC1, tsc_cyclesHC2, tsc_cyclesHC3, tsc_cyclesHC4;

#if (CORE_DSP) && (!HOST_EMULATION)  

void SetMAR()
{

  uint32_t i ;
  uint32_t* MAR = (uint32_t*)0x01848000 ;

  /*0x80000000,  len = 0x03000000*/
  for(i = 128 ;i <= 130 ; i++)
  {
    MAR[i] = 0x3;
  }

  /*0x83000000,  len = 0x0D000000*/
  for(i = 131 ;i <= 143 ; i++)
  {
    MAR[i] = 0x3;
  }
  
  /* MAR Reg  Add         Cache able Region
  * MAR 144 (0x01848240h) 9000 0000h - 90FF FFFFh
  * MAR 160 (0x01848280)  A000 0000h - A0FF FFFFh
  */
  for(i = 144 ;i <= 160 ; i++)
  {
    MAR[i] = 0x3;
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
  *L1DCFG = 4;

  SetMAR() ;
}
#endif //!HOST_EMULATION

#define MAX_CONFIG_LINE_SIZE       (300)
#define MAX_FILE_NAME_SIZE         (200)
#define ENABLE_FILE_IO             (1)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y)

#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of \
                            function : %s \n",__LINE__, __FILE__,__FUNCTION__)
#pragma DATA_SECTION (createParams, ".createParams");
TIOP_CreateParams  createParams;

#define DMEM0_SIZE (8*1024)
#define DMEM1_SIZE (148*1024)

#pragma DATA_SECTION (DMEM0_SCRATCH, ".dmem0Sect");
uint8_t DMEM0_SCRATCH[DMEM0_SIZE];

#pragma DATA_SECTION (DMEM1_SCRATCH, ".dmem1Sect");
uint8_t DMEM1_SCRATCH[DMEM1_SIZE];

#define EXTMEMNONCACHEIO_SIZE (15*1024*1024)
#pragma DATA_SECTION (EXTMEMNONCACHEIO, ".iobuf");
uint8_t EXTMEMNONCACHEIO[EXTMEMNONCACHEIO_SIZE];

#define MEM_CONTAMINATION_DIS 
                  
TIMemObject memObj_DMEM0;
TIMemObject memObj_DMEM1;
TIMemObject memObj_EXTMEMNONCACHEIO;

int tiop_printf(const char *format, ...)
{
    int status;
    va_list args;
    va_start(args, format);
    status = vprintf(format, args);
    va_end(args);
    return status;
}

void setDefaultParams(tiop_config * params)
{
  /* Setting default values */  
  params->numLevels	       =	4	;									 
  params->maxItersLK	     =	10	;								
  params->nmsThresh	       =	286870912 ;    						
  params->harrisScoreScalingFactor	=	1310 ;    
  params->confScoreGoodObjs	=	0.4 ;    
  params->confScoreModObjs	=	0.12 ;    
  params->maxOverlapThresh	=	0.4 ;    
  params->maxAgeThresh	=	30 ;    
  params->lkErrThresh	  =	500 ;    
  params->numClasses	  =	21 ;    
}

void setParamsFromInputConfig(tiop_config * params)
{
  createParams.l1MemSize                     = DMEM0_SIZE;
  createParams.l2MemSize                     = DMEM1_SIZE;
  createParams.numInDetections               = params->numInDetections;
  createParams.extImagePyramidal             = params->extImagePyramidal;
  createParams.extOpticalFlow                = params->extOpticalFlow;
  createParams.inMaxWidth                    = params->inMaxWidth;
  createParams.inMaxHeight                   = params->inMaxHeight;
  createParams.harrisScoreScalingFactor      = params->harrisScoreScalingFactor;
  createParams.nmsThresh                     = params->nmsThresh;
  createParams.numLevels                     = params->numLevels;
  createParams.maxItersLK                    = params->maxItersLK;
  createParams.confScoreGoodObjs             = params->confScoreGoodObjs;
  createParams.confScoreModObjs              = params->confScoreModObjs;
  createParams.maxOverlapThresh              = params->maxOverlapThresh;
  createParams.maxAgeThresh                  = params->maxAgeThresh;
  createParams.lkErrThresh                   = params->lkErrThresh;
  createParams.numClasses                    = params->numClasses;
}

int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
#ifndef MEM_CONTAMINATION_DIS
  int32_t j;
#endif
  TIMemHandle memHdl_DMEM0 = &memObj_DMEM0;
  TIMemHandle memHdl_DMEM1 = &memObj_DMEM1;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].space == IALG_DARAM0) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM0, memRec[i].size, 
        memRec[i].alignment);
    }
    else if(memRec[i].space == IALG_DARAM1) {
      memRec[i].base = TI_GetMemoryChunk(memHdl_DMEM1, memRec[i].size, 
        memRec[i].alignment);
    }
    else {
      memRec[i].base = (Void *) calloc( memRec[i].size,1);
    }
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
#ifndef MEM_CONTAMINATION_DIS
    /*Currently in test application all memory are used as scratch across 
    process calls */       
    if(memRec[i].space != IALG_DARAM0){        
      for(j = 0; j < (memRec[i].size >> 2); j++){
        //((int32_t*)memRec[i].base)[j] = 0xDEADBEEF;
      }
    }
#endif
  }
  return IALG_EOK;
}

int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec)
{
  int32_t i;
  TIMemHandle memHdl_DMEM0 = &memObj_DMEM0;
  TIMemHandle memHdl_DMEM1 = &memObj_DMEM1;

  for (i = 0; i < numMemRec; i++)
  {
    if(memRec[i].base == NULL)
    {
      return IALG_EFAIL;
    }
    if(memRec[i].space == IALG_DARAM0) {
      TI_ResetMemoryHandle(memHdl_DMEM0);
    }
    else if(memRec[i].space == IALG_DARAM1) {
      TI_ResetMemoryHandle(memHdl_DMEM1);
    }        
    else {
      free(memRec[i].base);
    }
  }
  return IALG_EOK;
}

typedef struct IM_Fxns
{
  IVISION_Fxns * ivision;

} IM_Fxns;

char * moveToNextElement(char *in, char *LinePtr)
{
  LinePtr += strlen(in);
  while((LinePtr[0] == ' ')||(LinePtr[0] == '    '))
  {
    LinePtr++;
  }
  return(LinePtr);
}

int32_t tiop_AllocNetInputMem(tiop_config *params, 
                             IVISION_BufDesc   *BufDescList)
{
  int32_t i;
  uint16_t numBuffs = 0;

  for(i = 0; i < TIOP_INPUT_TOTAL_FRAMES; i++)
  {
    /* In each input, one buffer is for input frame data and one for 
       to hold it's dectection list */
    BufDescList[numBuffs].numPlanes  = TIOP_IN_BUFDESC_TOTAL;
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.topLeft.x    = 0;
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.topLeft.y    = 0;    
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].width = params->srcImagePitch;
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].height = params->srcImageHeight;
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.width = 
                params->srcImageWidth;
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].frameROI.height = 
                params->srcImageHeight;    
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].buf = 
                (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].width * 
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].height, 4);
    memset(BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].buf, 0, 
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].width*
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].height);

    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.topLeft.x    = 0;
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.topLeft.y    = 0;    
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].width = 
                TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].height = 1;
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.width = 
                TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].frameROI.height = 1;    
    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].buf = 
                (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].width * 
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].height, 4);
    memset(BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].buf, 0, 
            BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].width*
            BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].height);

    if(params->extImagePyramidal)
    {
      int32_t j, width, height, pitch;
      width  = params->srcImageWidth >> 1;
      height = params->srcImageHeight >> 1;
      pitch  = params->srcImagePitch >> 1;
            
      for(j = 0; j < (params->numLevels-1) ; j++)
      {
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].frameROI.topLeft.x    = 0;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].frameROI.topLeft.y    = 0;    
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].width = pitch;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].height = height ;
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].frameROI.width = width;                    
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].frameROI.height = height;         
        BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].buf = 
                    (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].width * 
                    BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].height, 4);
        memset(BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].buf, 0, 
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].width*
                BufDescList[numBuffs].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].height);   
        width >>= 1 ;                
        height >>= 1 ;                        
        pitch >>= 1 ;                                        
      }                
    }
            
    BufDescList[numBuffs].bufferId = (i+1); // Should start with 1     
    numBuffs++;
  }
  return numBuffs;
}

void tiop_ReadInputFrame(TI_FILE * fp1, tiop_config *params,
                              IVISION_BufDesc   *BufDescList)
{

   FREAD(BufDescList[0].bufPlanes[0].buf, 1, (BufDescList[0].bufPlanes[0].width * 
                BufDescList[0].bufPlanes[0].height), fp1);  
  
}

void tiop_ReadInputImagePyramidal(TI_FILE * fp1, tiop_config *params,
                              IVISION_BufDesc   *BufDescList)
{
  int32_t j;
  
  for(j = 0; j < (params->numLevels-1) ; j++)
  {    
     FREAD(BufDescList[0].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].buf, 1, 
           (BufDescList[0].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].width * 
            BufDescList[0].bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + j].height), fp1);
  }
}

void tiop_ReadInputDetectList(TI_FILE * fp2, tiop_config *params,
                              IVISION_BufDesc   *BufDescList)
{  
#if 0
   FREAD(BufDescList[0].bufPlanes[1].buf, 1, params->numInDetections*sizeof(TIOP_objectDescriptor), fp2);    
#else
   int32_t bidx;
   float floatvariable;
   TIOP_objectDescriptor *inDetectList;
   inDetectList = (TIOP_objectDescriptor *)BufDescList[0].bufPlanes[1].buf;
  
    for(bidx = 0; bidx < params->numInDetections; bidx++)
    {
      FSCANF(fp2,"%f",&floatvariable);
      inDetectList->objClass = floatvariable;
      FSCANF(fp2,"%f",&floatvariable);
      inDetectList->xMin = floatvariable/params->srcImageWidth;
      FSCANF(fp2,"%f",&floatvariable);
      inDetectList->yMin = floatvariable/params->srcImageHeight;
      FSCANF(fp2,"%f",&floatvariable);
      inDetectList->xMax = floatvariable/params->srcImageWidth;
      FSCANF(fp2,"%f",&floatvariable);
      inDetectList->yMax = floatvariable/params->srcImageHeight;
      FSCANF(fp2,"%f",&floatvariable);
      inDetectList->objScore = floatvariable;
      inDetectList++;
    }
#endif  
}

void tiop_WriteOutputDetectList(TI_FILE * fout, IVISION_BufDesc   *BufDescList,
                                  int32_t numOutObjects)
{
#if 1  /* If number of output objects < 20, then fill with -1 */
  int32_t i; 
  TIOP_objectDescriptor *outPtr;
  outPtr = (TIOP_objectDescriptor *)BufDescList[0].bufPlanes[0].buf;
  outPtr = outPtr + numOutObjects;
  for(i = numOutObjects; i < 20; i++)
  {
    outPtr->objId = -1;
    outPtr->objClass = 0;
    outPtr->objScore = 0;
    outPtr->xMin = 0;
    outPtr->yMin = 0;
    outPtr->xMax = 0;
    outPtr->yMax = 0;
    outPtr++;
  }
  numOutObjects = 20;
#endif 
   FWRITE(BufDescList[0].bufPlanes[0].buf, 1, numOutObjects*sizeof(TIOP_objectDescriptor), fout);  
}

int32_t tiop_AllocNetOutputMem(tiop_config *params,
                              IVISION_BufDesc   *BufDescList)
{
  int32_t numBuffs = 0;
  
  BufDescList[numBuffs].numPlanes  = TIOP_OUT_BUFDESC_TOTAL;
  BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.topLeft.x    = 0;
  BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.topLeft.y    = 0;    
  BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].width = 
              TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
  BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].height = 1;
  BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.width = 
              TIOP_MAX_DETECT_OBJECTS * sizeof(TIOP_objectDescriptor);
  BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].frameROI.height = 1;    
  BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].buf = 
              (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
              BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].width * 
              BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].height, 4);
  memset(BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].buf, 0, 
          BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].width*
          BufDescList[numBuffs].bufPlanes[TIOP_OUT_BUFDESC_OBJECT_LIST].height);  
  
  return 1;
}

TI_FILE * tiop_openInputfile(char *inData)
{
  TI_FILE * fp1;
  fp1 = FOPEN(inData, "rb"); 
  if(fp1 == NULL)
  {
    printf("Could not open %s file for reading \n", inData);
  }
  return fp1;  
}

TI_FILE * tiop_openOutputfile(char *outData)
{
  TI_FILE * fp1;
  fp1 = FOPEN(outData, "wb"); 
  if(fp1 == NULL)
  {
    printf("Could not open %s file for writing \n", outData);
  }
  return fp1;  
}

IVISION_BufDesc   inBufDesc[TIOP_MAX_ALG_IN_BUFS];
IVISION_BufDesc   outBufDesc[TIOP_MAX_ALG_OUT_BUFS];
#pragma DATA_SECTION (inArgs, ".iobuf");
#pragma DATA_SECTION (outArgs, ".iobuf");
TIOP_InArgs      inArgs;
TIOP_outArgs     outArgs;

int32_t test_ti_op_ivison(void)
{

  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status, i, numFrames;
  int32_t frameIdx;
  uint32_t fileSize;
  
  /*-----------------------------------------------------------------
  Pointer to algorithm instance
  -----------------------------------------------------------------*/
  IM_Fxns *     handle;

  /*-----------------------------------------------------------------
  Algorithm parameters memory in stack
  -----------------------------------------------------------------*/

  IVISION_InBufs    inBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *inBufDescList[TIOP_MAX_ALG_IN_BUFS];

  IVISION_OutBufs          outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *outBufDescList[TIOP_MAX_ALG_OUT_BUFS];
  TI_FILE * fp1, * fp2, * fp3, * fout;
  
  /*--------------------------------------------------------------------------*/
  /* Buffer manager handle to crate and free the input buffers                */
  /*--------------------------------------------------------------------------*/
  BUFFMGR_buffEle  *buffEle;
  
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for DMEM and External memory                         */
  /*--------------------------------------------------------------------------*/
  TI_CreateMemoryHandle(&memObj_DMEM0, DMEM0_SCRATCH, DMEM0_SIZE);
  TI_CreateMemoryHandle(&memObj_DMEM1, DMEM1_SCRATCH, DMEM1_SIZE);
  TI_CreateMemoryHandle(&memObj_EXTMEMNONCACHEIO, EXTMEMNONCACHEIO, 
                         EXTMEMNONCACHEIO_SIZE);

  tiop_config *params;
  params = (tiop_config *)(&gParams);
  
  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size   = sizeof(TIOP_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  setParamsFromInputConfig(params) ;
  
  Cache_WbInvAll();

  numMemRec = TIOP_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = TIOP_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
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
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the allocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  Cache_WbInvAll();
  status = TIOP_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));
  Cache_WbInvAll();
  handle = (IM_Fxns *) memRec[0].base; 
  
  if(status != IALG_EOK)
  {
    printf("Algorithm Init failed with error number: %d\n", status);
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }

  if(params->extOpticalFlow)
  {
    printf("Algorithm Init failed with error number: %d\n", status);
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;    
  }
  
  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs  = tiop_AllocNetInputMem(params, inBufDesc);
  outBufs.numBufs = tiop_AllocNetOutputMem(params,outBufDesc);

  BUFFMGR_Init(inBufs.numBufs, inBufDesc);
  
  for(i = 0; i < inBufs.numBufs; i++)
  {
    inBufDescList[i]     = &inBufDesc[i];
  }
  for(i = 0; i < outBufs.numBufs; i++)
  {
    outBufDescList[i]     = &outBufDesc[i];
  }

  outArgs.iVisionOutArgs.size       = sizeof(TIOP_outArgs);
  inArgs.iVisionInArgs.size         = sizeof(TIOP_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;
  inArgs.numInObjects = params->numInDetections;   
   
  fp1  = tiop_openInputfile((char *)params->inDataFrame);
  fp2  = tiop_openInputfile((char *)params->inDataList);
  if(params->extImagePyramidal)
    fp3  = tiop_openInputfile((char *)params->inImagePyramidal);
  fout = tiop_openOutputfile((char *)params->outputFile);
    
  FSEEK (fp1 , 0 , SEEK_END );
  fileSize = FTELL (fp1);
  FSEEK (fp1 , 0 , SEEK_SET );
  numFrames = fileSize/(params->srcImagePitch*params->srcImageHeight); 
  
  for(frameIdx = 0 ; frameIdx < numFrames; frameIdx++)
  {
    printf("\nProcessing Frame Number : %d \n",frameIdx);
    buffEle = BUFFMGR_GetFreeBuffer();
    inBufDescList[0]->bufferId = buffEle->bufId;
    inBufDescList[0]->bufPlanes[TIOP_IN_BUFDESC_INPUT_FRAME].buf = (int8_t *) buffEle->buf[0];
    inBufDescList[0]->bufPlanes[TIOP_IN_BUFDESC_DETECTION_LIST].buf = (int8_t *) buffEle->buf[1];
    if(params->extImagePyramidal)
    {
      for(i = 0; i < (params->numLevels-1) ; i++)
      {
        inBufDescList[0]->bufPlanes[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + i].buf = 
        (int8_t *) buffEle->buf[TIOP_IN_BUFDESC_IPBUF_LEVEL1 + i];
      }
    }
    
    /* Read input to this buffer in buffEle */
    tiop_ReadInputFrame(fp1, params, inBufDesc);
    tiop_ReadInputDetectList(fp2, params, inBufDesc);
    if(params->extImagePyramidal)
      tiop_ReadInputImagePyramidal(fp3, params, inBufDesc);     
    Cache_WbInvAll();
    
#if (CORE_DSP) && (!HOST_EMULATION)
     tsc_start1 = _TSC_read();
#endif
    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
      
#if (CORE_DSP) && (!HOST_EMULATION)
     tsc_cycles  =  _TSC_read();
     if(tsc_cycles < tsc_start1)
     {
         printf(" TSC Mega Cycles = %8.6f with Over Flow \n", (tsc_cycles/1000000.0));
     }
     else
     {
         tsc_cycles -= tsc_start1;
         printf(" TSC Mega Cycles = %8.6f \n", (tsc_cycles/1000000.0));
     }
#if (ENABLE_TRACE_PROFILE)
     printf(" Image pyramid cycles = %8.6f \n", (tsc_cycles1/1000000.0));
     printf(" LK tracker  cycles   = %8.6f \n", (tsc_cycles2/1000000.0));
     printf(" Read Input  cycles   = %8.6f \n", (tsc_cycles3/1000000.0));
     printf(" Overlap NMS cycles   = %8.6f \n", (tsc_cycles4/1000000.0));
     printf(" Condition NMS cycles = %8.6f \n", (tsc_cycles5/1000000.0));
     printf(" HarriesCorner cycles = %8.6f \n", (tsc_cycles6/1000000.0));
#endif
#endif

    Cache_WbInvAll();
    
    /* These inFreeBufIDs will be set by the algorithm to indicate application to free buffers */
    BUFFMGR_ReleaseBuffer((uint32_t*)outArgs.iVisionOutArgs.inFreeBufIDs);
    
    tiop_WriteOutputDetectList(fout, outBufDesc, outArgs.numOutObjects);    
  }
  FCLOSE(fp1);
  FCLOSE(fp2);
  if(params->extImagePyramidal)
    FCLOSE(fp3);
  FCLOSE(fout);
  
  BUFFMGR_ReleaseAllBuffers();
  
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

EXIT_LOOP:

  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  FILE * fp;
  char * LinePtr;
  int32_t status;
  int32_t lineNum = -1;
  tiop_config * params;
  int32_t config_cmd;
  char configFileName[MAX_FILE_NAME_SIZE];
#if (!HOST_EMULATION) && (CORE_DSP)
  /*---------------------------------------------------------------------------
  Initialization of cache. Currently 128KB of L2 , 16 KB
  of L1, and full L1P is configured as cache.
  ----------------------------------------------------------------------------*/
  InitCache();
#endif
#ifdef USE_HOST_FILE_IO  
  ti_fileio_init();
#endif
#if (!HOST_EMULATION)
  argc = 1;
#endif
    
  _TSC_enable();
  params = (tiop_config *)(&gParams);

  if(argc == 1)
  {
    fp = fopen(CONFIG_LIST_FILE_NAME, "r");
    if(fp== NULL)
    {
      printf("Could not open config list file : %s  \n",CONFIG_LIST_FILE_NAME);
      return(0);
    }
  }
  else if(argc == 2)
  {
    fp = fopen(argv[1], "r");
    if(fp== NULL)
    {
      printf("Could not open config list file : %s  \n",argv[1]);
      return(0);
    }
  }
  
  while(1)
  {
    memset(params->configLine, 0, MAX_CONFIG_LINE_SIZE);
    status = (int32_t)fgets((char *)params->configLine,MAX_CONFIG_LINE_SIZE,fp);
    LinePtr = (char *)params->configLine;
    if ((status == EOF) || (status == 0)) 
      break;
    lineNum++;
    sscanf(LinePtr, "%d",&config_cmd);
    sscanf(LinePtr, "%s",params->configParam);
    if(config_cmd == 0)
    {
      printf("End of config list found !\n");
      break;
    }
    else if(config_cmd == 2)
    {
      continue;
    }
    else if(config_cmd == 1)
    {
      LinePtr = moveToNextElement((char *)params->configParam,LinePtr);
      status  = sscanf(LinePtr, "%s",configFileName);
      printf("\nProcessing config file %s !\n", configFileName);
      setDefaultParams(params) ;
      status = readparamfile(configFileName, &gsTokenMap_tiop[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      status = test_ti_op_ivison();
    }
    else
    {
      printf("Unsupported config list command parameter at line num : %4d !\n", 
              lineNum);
    }
  }

  fclose(fp);
  return (0);
}
