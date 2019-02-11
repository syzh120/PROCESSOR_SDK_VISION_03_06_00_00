/*
*
* Copyright (c) {2015 - 2017} Texas Instruments Incorporated
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


/** @file tidl_tb.c
*
*  @brief  This file contains test code for TI DL test application
*
*
*  @date   Oct 2016
*
*/
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "xdais_types.h"
#include "itidl_ti.h"
#include "tidl_config.h"
#include "ti_mem_manager.h"
#include "ti_file_io.h"
#if (CORE_EVE) || (HOST_EMULATION)  || (VCOP_HOST_EMULATION)
#define Cache_WbInvAll() //
#define _TSC_enable() //
#else
#include "cache.h"
#include "profile.h"
#endif

#if (CORE_EVE) && (!VCOP_HOST_EMULATION)
#include "eve_profile.h"   
#endif

#define TIDL_BLOCK_WIDTH			(32U)
#define TIDL_BLOCK_HEIGHT			(32U)
#define ENABLE_FLOAT_TRACE    (0)

#if (CORE_DSP) && (!HOST_EMULATION)
  
void _TSC_enable();  
long long _TSC_read();
uint64_t tsc_start, tsc_cycles;

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
    MAR[i] = 0x0;
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

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE      (20)

#define ENABLE_FILE_IO (1)
#define TIDL_TB_CURR_CORE_ID (gParams.layersGroupId)
#define TIDL_TB_CURR_LAYERS_GROUP_ID (gParams.layersGroupId)
#define DUMP_WITH_PADING (0)
#define SAT_LO_UINT8 (0)
#define SAT_HI_UINT8 (255)  
#define SAT_LO_INT8  (-128)
#define SAT_HI_INT8  (127)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

#define Q_FORMATE_SCALE_RATIO                   (12)
#define Q_FORMATE_FRAC_WEIGHT                   (4)

#define ALIGN_SIZE(x,y) (((x + (y-1)) / y) * y)

uint8_t traceDumpBaseName[FILE_NAME_SIZE];
uint8_t traceDumpName[FILE_NAME_SIZE];

#define PRINT_ERRORE_MSG()  printf("Error at line: %5d : in file %22s, of \
                            function : %s \n",__LINE__, __FILE__,__FUNCTION__)
#pragma DATA_SECTION (createParams, ".createParams");
TIDL_CreateParams  createParams;
//#define DMEM_SIZE (19*1024)

//#pragma DATA_SECTION (DMEM_SCRATCH, ".dmemSect");
//uint8_t DMEM_SCRATCH[DMEM_SIZE];
const char * TIDL_LayerString[] = 
{
"TIDL_DataLayer           ",
"TIDL_ConvolutionLayer    ",
"TIDL_PoolingLayer        ",
"TIDL_ReLULayer           ",
"TIDL_PReLULayer          ",
"TIDL_EltWiseLayer        ",
"TIDL_InnerProductLayer   ",
"TIDL_SoftMaxLayer        ",
"TIDL_BatchNormLayer      ",
"TIDL_BiasLayer           ",
"TIDL_ScaleLayer          ",
"TIDL_Deconv2DLayer       ",
"TIDL_ConcatLayer         ",
"TIDL_SplitLayer          ",
"TIDL_SliceLayer          ",
"TIDL_CropLayer           ",
"TIDL_FlattenLayer       ",
"TIDL_DropOutLayer        ",
"TIDL_ArgMaxLayer         ",
"TIDL_DetectionOutputLayer ",
"TIDL_ReshapeLayer        ",
};
#if CORE_DSP
#define DMEM0_SIZE (8*1024)
#define DMEM1_SIZE (148*1024)
#else
#if (!HOST_EMULATION)
#define DMEM0_SIZE (20*1024)
#else
//Increase DMEM0 size to avoid writting beyond end of buffer
#define DMEM0_SIZE (20*1024 + 256)
#endif
#define DMEM1_SIZE (8*1024)
#endif
#define OCMC_SIZE  (320*1024)

#define MAX_ROI_SUPPORT   4

#pragma DATA_SECTION (DMEM0_SCRATCH, ".dmem0Sect");
uint8_t DMEM0_SCRATCH[DMEM0_SIZE];

#pragma DATA_SECTION (DMEM1_SCRATCH, ".dmem1Sect");
uint8_t DMEM1_SCRATCH[DMEM1_SIZE];

#if CORE_DSP
#define EXTMEMNONCACHEIO_SIZE (15*1024*1024*MAX_ROI_SUPPORT)
#else
#define EXTMEMNONCACHEIO_SIZE (6*1024*1024*MAX_ROI_SUPPORT)
#endif
#pragma DATA_SECTION (EXTMEMNONCACHEIO, ".iobuf");
uint8_t EXTMEMNONCACHEIO[EXTMEMNONCACHEIO_SIZE];

#pragma DATA_SECTION (tempIOBUF, ".tempiobuf");
uint8_t tempIOBUF[512*1024*MAX_ROI_SUPPORT];

#define MEM_CONTAMINATION_DIS 

int32_t readImage(uint8_t *imageFile, int8_t *ptr, int16_t roi, int16_t n, 
                  int16_t width, int16_t height, int16_t pitch, 
                  int32_t chOffset, int32_t frameCount, int32_t preProcType);
                  
TIMemObject memObj_DMEM0;
TIMemObject memObj_DMEM1;
TIMemObject memObj_EXTMEMNONCACHEIO;

int tidl_printf(const char *format, ...)
{
    int status;
    va_list args;
    va_start(args, format);
    status = vprintf(format, args);
    va_end(args);
    return status;
}

void setDefaultParams(tidl_conv2d_config * params)
{
  params->updateNetWithStats     = 0;
  params->rawImage               = 1;
  params->noZeroCoeffsPercentage = 100;
  params->randInput              = 0;
  params->writeOutput            = 1;
  params->preProcType            = 0;
  params->writeQ                 = 0;
  params->readQ                  = 0;
  params->layersGroupId          = 1;
#ifdef RUN_REF_FOR_STATS
  params->runFullNet             = 1;
#else
  params->runFullNet             = 0;
#endif
  
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
/* A utility function to reverse a string  */
void tidl_reverse(char str[], int32_t length)
{
  int32_t start = 0;
  int32_t end = length -1;
  int8_t temp;
  while (start < end)
  {
    temp = *(str+end);
    *(str+end) = *(str+start);
    *(str+start) = temp;
    start++;
    end--;
  }
}

// Implementation of itoa()
char* tidl_itoa(int32_t num, char* str, int32_t base)
{
  int32_t i = 0;
  int32_t isNegative = 0;

  /* Handle 0 explicitely, otherwise empty string is printed for 0 */
  if (num == 0)
  {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // In standard itoa(), negative numbers are handled only with 
  // base 10. Otherwise numbers are considered unsigned.
  if (num < 0 && base == 10)
  {
    isNegative = 1;
    num = -num;
  }

  // Process individual digits
  while (num != 0)
  {
    int32_t rem = num % base;
    str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
    num = num/base;
  }

  // If number is negative, append '-'
  if (isNegative)
    str[i++] = '-';

  str[i] = '\0'; // Append string terminator

  // Reverse the string
  tidl_reverse(str, i);

  return str;
}

static void createRandPatternS16(int16_t *ptr, int16_t n, int16_t width, 
                                 int16_t height, int16_t pitch, int32_t chOffset)
{
  short val;
  int32_t   i0, i1, i2;
  for(i0 = 0; i0 < n; i0++)
  {
    for(i1 = 0; i1 < height; i1++)
    {
      for(i2 = 0; i2 < width; i2++)
      {
        val = rand() & 0x7FFF;
        ptr[i0*chOffset + i1*pitch +i2] = (rand()&1) ? val : -val;
      }
    }
  }
}

static void createRandPatternS8(int8_t *ptr, int16_t roi, int16_t n, 
                                int16_t width, int16_t height, int16_t pitch, 
                                int32_t chOffset)
{
  int16_t val;
  int32_t   i0, i1, i2, i3;
  for(i3 = 0; i3 < roi; i3++)
  {
    for(i0 = 0; i0 < n; i0++)
    {
      for(i1 = 0; i1 < height; i1++)
      {
        for(i2 = 0; i2 < width; i2++)
        {
          val = rand() & 0x7F;
          ptr[i3*n*chOffset + i0*chOffset + i1*pitch +i2] = 
            (rand()&1) ? val : -val;
        }
      }
    }
  }
}

static void createRandPatternU8(uint8_t *ptr, int16_t roi, int16_t n, 
                                int16_t width, int16_t height, int16_t pitch, 
                                int32_t chOffset)
{
  uint16_t val;
  int32_t   i0, i1, i2, i3;
  for(i3 = 0; i3 < roi; i3++)
  {
    for(i0 = 0; i0 < n; i0++)
    {
      for(i1 = 0; i1 < height; i1++)
      {
        for(i2 = 0; i2 < width; i2++)
        {
          val = rand() & 0xFF;
          ptr[i3*n*chOffset + i0*chOffset + i1*pitch +i2] = 
            (rand()&1) ? val : -val;
        }
      }
    }
  }
}
static int32_t writeDataS8(TI_FILE *fptr, int8_t *ptr, int32_t n, int32_t width,
                           int32_t height, int32_t pitch, int32_t chOffset)
{
  int32_t   i0, i1;

  int8_t *writePtr = (int8_t *)malloc(n*width*height);
  if(writePtr)
  {
    for(i0 = 0; i0 < n; i0++)
    {
      for(i1 = 0; i1 < height; i1++)
      {
        memcpy(&writePtr[i0*width*height+ i1*width], 
               &ptr[i0*chOffset + i1*pitch],width);
      }
    }
    FWRITE(writePtr,1,width*height*n, fptr);
    free(writePtr);
    return 1;
  }
  else
  {
    return 0;
  }
}


static int32_t readDataS8(TI_FILE *fptr, int8_t *ptr, int32_t roi, int32_t n, 
                          int32_t width, int32_t height, int32_t pitch, 
                          int32_t chOffset)
{
  int32_t   i0, i1, i2, i3;

  int8_t *readPtr = (int8_t *)tempIOBUF;
  if(readPtr)
  {
    FREAD(readPtr,1,width*height*n*roi, fptr);
    for(i2 = 0; i2 < roi; i2++)
    {
      for(i0 = 0; i0 < n; i0++)
      {
        for(i1 = 0; i1 < height; i1++)
        {
          for(i3 = 0; i3 < width; i3++)
          {
           ptr[i2*n*chOffset + i0*chOffset + i1*pitch + i3] = readPtr[i2*n*width*height + i0*width*height+ i1*width + i3];
          }
        }
      }
    }
    return 1;
  }
  else
  {
    return 0;
  }
}

static void sparseConv2dCoffesS8(int8_t *ptr, int32_t n, uint8_t thr , int32_t zeroWeightValue)
{
  int32_t   i0;
  for(i0 = 0; i0 < n; i0++)
  {
    if(((uint8_t)(rand() & 0xFF)) > thr)
    {
      ptr[i0] =  zeroWeightValue;
    }
  }
}

static void sparseConv2dCoffesS16(int16_t *ptr, int32_t n, uint8_t thr , int32_t zeroWeightValue)
{
  int32_t   i0;
  for(i0 = 0; i0 < n; i0++)
  {
    if(((uint8_t)(rand() & 0xFF)) > thr)
    {
      ptr[i0] =  zeroWeightValue;
    }
  }
}

int32_t tidl_readNet(sTIDL_Network_t * net, uint8_t * fileString)
{
  TI_FILE * fptr;
  fptr = FOPEN((const char *)fileString, "rb");
  if(fptr)
  {
    //FREAD(net,1,(6*sizeof(sTIDL_Layer_t) + 64), fptr);
    FREAD(net,1,(sizeof(sTIDL_Network_t)), fptr);

    FCLOSE(fptr);
    return 0;
  }
  else
  {
    printf("Could Not Open Files %s\n",fileString);
    return -1;
  }

}

int32_t tidl_writeNet(sTIDL_Network_t * net, uint8_t * fileString)
{
  TI_FILE * fptr;
  fptr = FOPEN((const char *)fileString, "wb+");
  if(fptr)
  {
    FWRITE(net,1,(sizeof(sTIDL_Network_t)), fptr);
    FCLOSE(fptr);
    return 0;
  }
  else
  {
    printf("Could Not Open Files %s\n",fileString);
    return -1;
  }
}

int32_t tidl_updateNet(sTIDL_Network_t * net, tidl_conv2d_config * params)
{
  TI_FILE * fptr;
  int32_t i, j;
  int32_t min;
  int32_t max;
  strcpy((char *)traceDumpName,(char *)traceDumpBaseName);
  strcat((char *)traceDumpName,"LayersMinMax.bin");
  fptr = FOPEN((const char *)traceDumpName, "rb");
  if(!fptr)
  {
    printf("Could Not Open Files %s\n",traceDumpName);
    return -1;
  }

  for(i = 0; i < net->numLayers; i++)
  {
    sTIDL_Layer_t *TIDLLayer = &net->TIDLLayers[i];
    if((TIDLLayer->layersGroupId == TIDL_TB_CURR_LAYERS_GROUP_ID) || ((params->runFullNet) && (TIDLLayer->layerType != TIDL_DataLayer)))
    {
      for(j = 0; j < TIDLLayer->numOutBufs; j++)
      {
        FREAD(&min,1,sizeof(int32_t), fptr);
        FREAD(&max,1,sizeof(int32_t), fptr);
        TIDLLayer->outData[j].minValue = min;
        TIDLLayer->outData[j].maxValue = max;
      }
    }
  }

  FCLOSE(fptr);
  return 0;
}

void tidl_UpdateLayersGroup(sTIDL_Network_t * net)
{
  int32_t i;
  for (i = 0; i < net->numLayers; i++)
  {
    if (net->TIDLLayers[i].layerType != TIDL_DataLayer)
    {
      net->TIDLLayers[i].layersGroupId = TIDL_TB_CURR_LAYERS_GROUP_ID;
    }
  }
}

int32_t tidl_writeNetWithStats(tidl_conv2d_config * params)
{
  tidl_readNet(&createParams.net,params->netBinFile);
  tidl_updateNet(&createParams.net, params);
  tidl_writeNet(&createParams.net,params->outputNetBinFile);
  return 0;
}

 
int32_t tidl_allocNetParamsMem(sTIDL_Network_t * net)
{
  int32_t i;
  for(i = 0; i < net->numLayers; i++)
  {
    if((net->TIDLLayers[i].layerType == TIDL_ConvolutionLayer) || 
       (net->TIDLLayers[i].layerType   == TIDL_Deconv2DLayer))
    {
      sTIDL_ConvParams_t *conv2dPrms =&net->TIDLLayers[i].layerParams.convParams;
      conv2dPrms->weights.bufSize =  net->weightsElementSize *
            (conv2dPrms->kernelW * conv2dPrms->kernelH * 
             conv2dPrms->numInChannels * conv2dPrms->numOutChannels)
             /conv2dPrms->numGroups;
             
      conv2dPrms->weights.ptr = 
                (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                conv2dPrms->weights.bufSize, 4);

      conv2dPrms->bias.bufSize= net->biasElementSize*conv2dPrms->numOutChannels;
      conv2dPrms->bias.ptr= (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                                                    conv2dPrms->bias.bufSize,4);
    }
    else if(net->TIDLLayers[i].layerType   == TIDL_BiasLayer)
    {
      sTIDL_BiasParams_t *biasPrms =&net->TIDLLayers[i].layerParams.biasParams;
      biasPrms->bias.bufSize =  net->biasElementSize * biasPrms->numChannels;
      biasPrms->bias.ptr = (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                                                     biasPrms->bias.bufSize, 4);
    }
    else if(net->TIDLLayers[i].layerType   == TIDL_BatchNormLayer)
    {
      sTIDL_BatchNormParams_t *batchNormPrms = 
                 &net->TIDLLayers[i].layerParams.batchNormParams;
      batchNormPrms->weights.bufSize =  
                 net->weightsElementSize * batchNormPrms->numChannels;       
      batchNormPrms->weights.ptr = 
                (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                batchNormPrms->weights.bufSize, 4);
      batchNormPrms->bias.bufSize =  
                net->biasElementSize * batchNormPrms->numChannels;
      batchNormPrms->bias.ptr = 
                (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                batchNormPrms->bias.bufSize, 4);
      batchNormPrms->reluParams.slope.bufSize =  
                 net->slopeElementSize * batchNormPrms->numChannels;   
      if(batchNormPrms->reluParams.reluType == TIDL_PRelU)
      {

        batchNormPrms->reluParams.slope.ptr = 
          (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
          batchNormPrms->reluParams.slope.bufSize, 4);
      }
    }    
    else if(net->TIDLLayers[i].layerType   == TIDL_InnerProductLayer)
    {
      sTIDL_InnerProductParams_t *ipPrms = 
                            &net->TIDLLayers[i].layerParams.innerProductParams;      
      ipPrms->bias.bufSize =  net->biasElementSize * ipPrms->numOutNodes;
      ipPrms->bias.ptr = (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                                        ALIGN_SIZE(ipPrms->bias.bufSize,128),4);
      ipPrms->weights.bufSize =  net->weightsElementSize* ipPrms->numInNodes * 
                                 ipPrms->numOutNodes; //ipPrms->numChannels;
      ipPrms->weights.ptr = (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                                     ALIGN_SIZE((ipPrms->weights.bufSize + 16*net->TIDLLayers[i].layerParams.innerProductParams.numInNodes), 1024),4);
    }
    else if(net->TIDLLayers[i].layerType   == TIDL_DetectionOutputLayer)
    {
      sTIDL_DetectOutputParams_t *detectPrms =&net->TIDLLayers[i].layerParams.detectOutParams;
      detectPrms->priorBox.bufSize =  detectPrms->priorBoxSize * sizeof(float);
      detectPrms->priorBox.ptr = (float *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                                                     detectPrms->priorBox.bufSize, 4);
    }    
  }
  return 0;
}

sTIDL_DataParams_t *tidl_getDataBufDims(sTIDL_Network_t *net, int32_t dataBuffId)
{
  int32_t i,j;
  for (i = 0 ; i < net->numLayers; i++)
  {
    for (j = 0; j < net->TIDLLayers[i].numOutBufs; j++)
    {       
      if( (net->TIDLLayers[i].outData[j].dataId == dataBuffId))
      {

        return &net->TIDLLayers[i].outData[j];
      }
    }
  }
  return NULL;
}

int32_t tidl_writeTraceDataBuf(int8_t * ptr, sTIDL_Network_t * net, int32_t dataBuffId)
{
  TI_FILE * fptr;
#if ENABLE_FLOAT_TRACE
  TI_FILE * fptr2;
#endif
  char DataIDString[10];
  sTIDL_DataParams_t * dataBuffParam;
  dataBuffParam = tidl_getDataBufDims(net,dataBuffId);
#if DUMP_WITH_PADING
  int32_t dataSize = dataBuffParam->dimValues[1]*
                  (dataBuffParam->dimValues[2]+2*TIDL_MAX_PAD_SIZE)*
                  (dataBuffParam->dimValues[3]+2*TIDL_MAX_PAD_SIZE);
  if(dataBuffParam)
  {
    tidl_itoa(dataBuffId,(char *)DataIDString,10);
    strcpy((char *)traceDumpName,(char *)traceDumpBaseName);
    strcat((char *)traceDumpName,(char *)DataIDString);
    strcat((char *)traceDumpName,".bin");
    fptr = FOPEN((const char *)traceDumpName, "wb+");
    if(fptr)
    {
      FWRITE(ptr,1,dataSize, fptr);
      FCLOSE(fptr);
      return 0;
    }
    else
    {
      printf("Could Not Open Files %s\n",traceDumpName);
      return -1;
    }
  }
#else
  if(dataBuffParam)
  {
    int32_t dataSize = dataBuffParam->dimValues[1]*dataBuffParam->dimValues[2] *
                       dataBuffParam->dimValues[3];
    int32_t linePitch = dataBuffParam->pitch[TIDL_LINE_PITCH];
    int32_t chPitch   = dataBuffParam->pitch[TIDL_CHANNEL_PITCH];
    int8_t * outPtr   = (int8_t * )malloc(dataSize);
    float  * floatPtr = (float  *)malloc(sizeof(float)*dataSize);
    int32_t i, j;
    if((outPtr == NULL) || (floatPtr == NULL))
    {
      PRINT_ERRORE_MSG();
      return -1;
    }
    for (j = 0; j < dataBuffParam->dimValues[1]; j++)
    {
      for (i = 0; i < dataBuffParam->dimValues[2]; i++)
      {
        int32_t offset = j*dataBuffParam->dimValues[2] * dataBuffParam->dimValues[3] + i*dataBuffParam->dimValues[3];
        if (dataBuffParam->elementType == 0)
        {
          uint8_t * src, *dst;
          int32_t k;
          src = (uint8_t *)(ptr + j*chPitch + i*linePitch + TIDL_MAX_PAD_SIZE*linePitch + TIDL_MAX_PAD_SIZE);
          dst = (uint8_t *)(outPtr + offset);
          for (k = 0; k < dataBuffParam->dimValues[3]; k++)
          {
            dst[k]     = src[k];
            floatPtr[offset+k] = ((float)src[k]) / (dataBuffParam->dataQ/256.0);
          }
        }
        else
        {
          int8_t * src, *dst;
          int32_t k;
          src = (ptr + j*chPitch + i*linePitch + TIDL_MAX_PAD_SIZE*linePitch + TIDL_MAX_PAD_SIZE);
          dst = (outPtr + offset);
          for (k = 0; k < dataBuffParam->dimValues[3]; k++)
          {
            floatPtr[k+ offset] = ((float)src[k]) / (dataBuffParam->dataQ / 256.0);
            dst[k] = src[k] + 128;
          }
        }

      }
    }

    tidl_itoa(dataBuffId,(char *)DataIDString,10);
    strcpy((char *)traceDumpName,(char *)traceDumpBaseName);
    strcat((char *)traceDumpName,(char *)DataIDString);
    strcat((char *)traceDumpName,"_");
    tidl_itoa(dataBuffParam->dimValues[3],(char *)DataIDString,10);
    strcat((char *)traceDumpName,(char *)DataIDString);
    strcat((char *)traceDumpName,"x");
    tidl_itoa(dataBuffParam->dimValues[2],(char *)DataIDString,10);
    strcat((char *)traceDumpName,(char *)DataIDString);
    strcat((char *)traceDumpName,".y");
    fptr = FOPEN((const char *)traceDumpName, "wb+");
#if ENABLE_FLOAT_TRACE
    strcat((char *)traceDumpName, "_float.bin");
    fptr2 = FOPEN((const char *)traceDumpName, "wb+");
#endif
    if(fptr
#if ENABLE_FLOAT_TRACE
      && fptr2)
#else
      )
#endif
    {
      FWRITE(outPtr,1,dataSize, fptr);
      FCLOSE(fptr);
#if ENABLE_FLOAT_TRACE
      FWRITE(floatPtr, 1, dataSize*sizeof(float), fptr2);
      FCLOSE(fptr2);
#endif
      free(floatPtr);
      free(outPtr);
      return 0;
    }
    else
    {
      printf("Could Not Open Files %s\n",traceDumpName);
      free(floatPtr);
      free(outPtr);
      return -1;
    }
  }
#endif
  return 0;
}

int32_t tidl_writeLayerMinMax(sTIDL_Network_t * net)
{
  int32_t i, j;
  TI_FILE * fptr;
  strcpy((char *)traceDumpName,(char *)traceDumpBaseName);
  strcat((char *)traceDumpName,"LayersMinMax.bin");
  fptr = FOPEN((const char *)traceDumpName, "wb+");
  if(!fptr)
  {
    printf("Could Not Open Files %s\n",traceDumpName);
    return -1;
  }
  for(i = 0; i < net->numLayers; i++)
  {
    sTIDL_Layer_t *TIDLLayer = &net->TIDLLayers[i];
    if(TIDLLayer->layersGroupId == TIDL_TB_CURR_LAYERS_GROUP_ID)
    {
      for(j = 0; j < TIDLLayer->numOutBufs; j++)
      {
        FWRITE(&TIDLLayer->outData[j].minValue,1,sizeof(int32_t), fptr);
        FWRITE(&TIDLLayer->outData[j].maxValue,1,sizeof(int32_t), fptr);
      }    
    }
  }
  FCLOSE(fptr);
  return 0;
}

int32_t tidl_freeNetParamsMem(sTIDL_Network_t * net)
{
  int32_t i;
  for(i = 0; i < net->numLayers; i++)
  {
    if((net->TIDLLayers[i].layerType   == TIDL_ConvolutionLayer) || 
       (net->TIDLLayers[i].layerType   == TIDL_Deconv2DLayer))
    {
      free(net->TIDLLayers[i].layerParams.convParams.weights.ptr);
      free(net->TIDLLayers[i].layerParams.convParams.bias.ptr);
    }
  }
  return 0;
}

int32_t tidl_fillNetParamsMem(sTIDL_Network_t *net, tidl_conv2d_config *params)
{
  int32_t i;
  TI_FILE * fp1 = FOPEN((const char *)params->paramsBinFile, "rb+");
  uint32_t dataSize ;
  if(fp1 == NULL)
  {
    printf("Could not open %s file for reading \n",params->paramsBinFile);
  }

  for(i = 0; i < net->numLayers; i++)
  {
    if((net->TIDLLayers[i].layerType   == TIDL_ConvolutionLayer) || 
       (net->TIDLLayers[i].layerType   == TIDL_Deconv2DLayer))
    {
      sTIDL_ConvParams_t *conv2dPrms =&net->TIDLLayers[i].layerParams.convParams;
#if 1
      if(params->randInput)
      {
        createRandPatternS8((int8_t *)conv2dPrms->weights.ptr, 1, 
          conv2dPrms->numInChannels/conv2dPrms->numGroups, 
          conv2dPrms->numOutChannels, 
          conv2dPrms->kernelW*conv2dPrms->kernelH, 
          conv2dPrms->numOutChannels, 
          conv2dPrms->kernelW*conv2dPrms->kernelW*conv2dPrms->numOutChannels);
          
        if(params->noZeroCoeffsPercentage < 100)
        {
          sparseConv2dCoffesS8((int8_t *)conv2dPrms->weights.ptr, 
                               conv2dPrms->weights.bufSize, 
                               params->noZeroCoeffsPercentage*2.55, conv2dPrms->zeroWeightValue);
        }
        if(net->TIDLLayers[i].layerParams.convParams.enableBias)
        {
          dataSize = conv2dPrms->numOutChannels;
          createRandPatternS16((int16_t *)conv2dPrms->bias.ptr,1,dataSize,1,1,1);
        }
        else
        {
          memset((int8_t *)conv2dPrms->bias.ptr,0,conv2dPrms->numOutChannels*net->biasElementSize);
        }
      }
      else
#endif
      {
        dataSize = (conv2dPrms->numInChannels* conv2dPrms->numOutChannels* 
                conv2dPrms->kernelW*conv2dPrms->kernelH)/conv2dPrms->numGroups;

        //Read weights based on its size
        if(net->weightsElementSize == 2)
          FREAD((int8_t *)conv2dPrms->weights.ptr,1,2*dataSize, fp1);
        else
          FREAD((int8_t *)conv2dPrms->weights.ptr,1,dataSize, fp1);
          
        if(params->noZeroCoeffsPercentage < 100)
        {
          if(net->weightsElementSize == 2)
          {
            sparseConv2dCoffesS16((int16_t *)conv2dPrms->weights.ptr, 
              conv2dPrms->weights.bufSize, params->noZeroCoeffsPercentage*2.55,conv2dPrms->zeroWeightValue);
          }
          else
          {
            sparseConv2dCoffesS8((int8_t *)conv2dPrms->weights.ptr, 
              conv2dPrms->weights.bufSize, params->noZeroCoeffsPercentage*2.55,conv2dPrms->zeroWeightValue);
          }
        }

        if(conv2dPrms->enableBias)
        {
          dataSize = conv2dPrms->numOutChannels;
          FREAD((int8_t *)conv2dPrms->bias.ptr,1,dataSize*net->biasElementSize, fp1);
        }
        else
        {
          memset((int8_t *)conv2dPrms->bias.ptr,0,conv2dPrms->numOutChannels*net->biasElementSize);
        }
      }
    }
    else if(net->TIDLLayers[i].layerType == TIDL_BiasLayer)
    {
      sTIDL_BiasParams_t *biasPrms =&net->TIDLLayers[i].layerParams.biasParams;
      dataSize = biasPrms->numChannels;      
      if(params->randInput)
      {
        createRandPatternS16((int16_t *)biasPrms->bias.ptr, 1,dataSize,1,1, 1);
      }
      else
      {
        FREAD((int8_t *)biasPrms->bias.ptr,1,dataSize*net->biasElementSize, fp1);
      }
    } 
    else if(net->TIDLLayers[i].layerType == TIDL_BatchNormLayer)
    {
      sTIDL_BatchNormParams_t *bNPrms =&net->TIDLLayers[i].layerParams.batchNormParams;
      dataSize = bNPrms->numChannels;  
      if(params->randInput)
      {
        createRandPatternS16((int16_t *)bNPrms->weights.ptr, 1, dataSize, 1,1,1);
      }
      else
      {
        if(net->weightsElementSize == 2)
		{
          FREAD((int8_t *)bNPrms->weights.ptr,1,2*dataSize, fp1);
		}
		else
		{
          FREAD((int8_t *)bNPrms->weights.ptr,1,dataSize, fp1);
		}
      }
      if(params->randInput)
      {
        createRandPatternS16((int16_t *)bNPrms->bias.ptr, 1,dataSize,1,1, 1);
      }
      else
      {
        FREAD((int8_t *)bNPrms->bias.ptr,1,dataSize*net->biasElementSize, fp1);
      }
      if(bNPrms->reluParams.reluType == TIDL_PRelU)
      {
        if(params->randInput)
        {
          createRandPatternS16((int16_t *)bNPrms->reluParams.slope.ptr, 1, dataSize, 1,1,1);
        }
        else
        {
          if(net->slopeElementSize == 2)
		  {
            FREAD((int8_t *)bNPrms->reluParams.slope.ptr,1,2*dataSize, fp1);
		  }
		  else
		  {
            FREAD((int8_t *)bNPrms->reluParams.slope.ptr,1,dataSize, fp1);
		  }
        }
      }
    }    
    else if(net->TIDLLayers[i].layerType == TIDL_InnerProductLayer)
    {
      sTIDL_InnerProductParams_t *ipPrms = 
                             &net->TIDLLayers[i].layerParams.innerProductParams;      
      dataSize = ipPrms->numInNodes * ipPrms->numOutNodes;      
      if(params->randInput)
      {
        createRandPatternS16((int16_t *)ipPrms->weights.ptr, 1, dataSize, 1,1,1);
      }
      else
      {
        //Read weights based on its size
        if(net->weightsElementSize == 2)
		  FREAD((int8_t *)ipPrms->weights.ptr,1,2*dataSize, fp1);
		else
          FREAD((int8_t *)ipPrms->weights.ptr,1,dataSize, fp1);
      }      
      dataSize = ipPrms->numOutNodes;      
      if(params->randInput)
      {
        createRandPatternS16((int16_t *)ipPrms->bias.ptr, 1, dataSize, 1, 1, 1);
      }
      else
      {
        FREAD((int8_t *)ipPrms->bias.ptr,1,dataSize*net->biasElementSize, fp1);
      }
    }
    else if(net->TIDLLayers[i].layerType == TIDL_DetectionOutputLayer)
    {
      sTIDL_DetectOutputParams_t *detectPrms =
                    &net->TIDLLayers[i].layerParams.detectOutParams;                    
      dataSize = detectPrms->priorBoxSize;     
      if(params->randInput)
      {
        createRandPatternS16((int16_t *)detectPrms->priorBox.ptr, 1, dataSize*2, 1,1,1);
      }
      else
      {
		    FREAD((float*)detectPrms->priorBox.ptr, sizeof(float), dataSize, fp1);
      }
    }      
  }
  return 0;
}


int32_t tidltb_isOutDataBuff(sTIDL_Network_t *pTIDLNetStructure, int32_t dataId,
                             int32_t layersGroupId)
{
  int32_t i,j;
  for (i = 0 ; i < pTIDLNetStructure->numLayers; i++)
  {
    for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++)
    {       
      if((pTIDLNetStructure->TIDLLayers[i].layersGroupId != layersGroupId) && 
         (pTIDLNetStructure->TIDLLayers[i].inData[j].dataId == dataId))
      {
        return 1;
      }
    }
  }
  return 0;
}

int32_t tidltb_isInDataBuff(sTIDL_Network_t * pTIDLNetStructure, int32_t dataId, 
                            int32_t layersGroupId)
{
  int32_t i,j;
  for (i = 0 ; i < pTIDLNetStructure->numLayers; i++)
  {
    for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++)
    {       
      if((pTIDLNetStructure->TIDLLayers[i].layersGroupId == layersGroupId) && 
         (pTIDLNetStructure->TIDLLayers[i].inData[j].dataId == dataId))
      {
        return 1;
      }
    }
  }
  return 0;
}

int32_t tidl_AllocNetInputMem(sTIDL_Network_t * net, tidl_conv2d_config *params,
                              IVISION_BufDesc   *BufDescList)
{
  int32_t i,j;
  uint16_t tidlMaxPad     = TIDL_MAX_PAD_SIZE;
  uint16_t numBuffs = 0;

  for(i = 0; i < net->numLayers; i++)
  {
    if(net->TIDLLayers[i].layersGroupId !=TIDL_TB_CURR_LAYERS_GROUP_ID)
    {
      for(j = 0; j < net->TIDLLayers[i].numOutBufs; j++ )
      {
        if(tidltb_isInDataBuff(net,net->TIDLLayers[i].outData[j].dataId,
           TIDL_TB_CURR_LAYERS_GROUP_ID))
        {
          BufDescList[numBuffs].numPlanes                          = 1;
          BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.x    = 0;
          BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.y    = 0;

          BufDescList[numBuffs].bufPlanes[0].width                 = 
                    net->TIDLLayers[i].outData[j].dimValues[3] + 2*tidlMaxPad;
                    
          BufDescList[numBuffs].bufPlanes[0].height                =
                    net->TIDLLayers[i].outData[j].dimValues[0]*
                    net->TIDLLayers[i].outData[j].dimValues[1]*
                    (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad);
                    
          BufDescList[numBuffs].bufPlanes[0].frameROI.width        = 
                    net->TIDLLayers[i].outData[j].dimValues[3];
                    
          BufDescList[numBuffs].bufPlanes[0].frameROI.height       = 
                    net->TIDLLayers[i].outData[j].dimValues[2];

          BufDescList[numBuffs].bufPlanes[0].buf = 
                      (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                      BufDescList[numBuffs].bufPlanes[0].width * 
                      BufDescList[numBuffs].bufPlanes[0].height, 4);
          BufDescList[numBuffs].reserved[0]     = 
                                        net->TIDLLayers[i].outData[j].dataId;
          
          memset(BufDescList[numBuffs].bufPlanes[0].buf,0, 
                  BufDescList[numBuffs].bufPlanes[0].width*
                  BufDescList[numBuffs].bufPlanes[0].height);
          BufDescList[numBuffs].bufferId = net->TIDLLayers[i].outData[j].dataId;

              
          numBuffs++;
        }
      }
    }
  }
  return numBuffs;
}

TI_FILE * tidl_openNetInput(tidl_conv2d_config *params)
{
  TI_FILE * fp1;
  if(params->randInput)
  {    
    if(params->writeInput)
    {
      fp1 = FOPEN((const char *)params->inData, "wb+");
      if(fp1 == NULL)
      {
        printf("Could not open %s file for writing \n",params->inData);
      }
    }
  }
  else
  {
    fp1 = FOPEN((const char *)params->inData, "rb+");
    if(fp1 == NULL)
    {
      printf("Could not open %s file for reading \n",params->inData);
    }
  }
  return fp1;  
}


int32_t tidl_ReadNetInput(TI_FILE * fp1, sTIDL_Network_t * net, tidl_conv2d_config *params,
                              IVISION_BufDesc   *BufDescList, int32_t frameCount, int32_t * dataQ)
{
  int32_t i,j;
  uint16_t tidlMaxPad     = TIDL_MAX_PAD_SIZE;
  uint16_t numBuffs = 0;
  for(i = 0; i < net->numLayers; i++)
  {
    if(net->TIDLLayers[i].layersGroupId !=TIDL_TB_CURR_LAYERS_GROUP_ID)
    {
      for(j = 0; j < net->TIDLLayers[i].numOutBufs; j++ )
      {
        if(tidltb_isInDataBuff(net,net->TIDLLayers[i].outData[j].dataId,
           TIDL_TB_CURR_LAYERS_GROUP_ID))
        {

          if(params->randInput)
          {
            int32_t  inElementType =  net->TIDLLayers[i].inData[0].elementType;
            if(inElementType == TIDL_SignedChar)
            {
              createRandPatternS8(
                        ((int8_t *)BufDescList[numBuffs].bufPlanes[0].buf + 
                        BufDescList[numBuffs].bufPlanes[0].width*tidlMaxPad +
                        tidlMaxPad),net->TIDLLayers[i].outData[j].dimValues[0],
                        net->TIDLLayers[i].outData[j].dimValues[1],
                        net->TIDLLayers[i].outData[j].dimValues[3],
                        net->TIDLLayers[i].outData[j].dimValues[2],
                        BufDescList[numBuffs].bufPlanes[0].width,
                        BufDescList[numBuffs].bufPlanes[0].width*
                   (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad));
                   
              if(params->writeInput)
              {
                writeDataS8(fp1,
                      ((int8_t *)BufDescList[numBuffs].bufPlanes[0].buf + 
                      BufDescList[numBuffs].bufPlanes[0].width*tidlMaxPad + 
                      tidlMaxPad), net->TIDLLayers[i].outData[j].dimValues[1], 
                      net->TIDLLayers[i].outData[j].dimValues[3], 
                      net->TIDLLayers[i].outData[j].dimValues[2], 
                      BufDescList[numBuffs].bufPlanes[0].width, 
                      BufDescList[numBuffs].bufPlanes[0].width*
                   (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad));
              }                          
            }
            else if(inElementType == TIDL_UnsignedChar)
            {
              createRandPatternU8(
                  ((uint8_t *)BufDescList[numBuffs].bufPlanes[0].buf + 
                  BufDescList[numBuffs].bufPlanes[0].width*tidlMaxPad + 
                  tidlMaxPad),net->TIDLLayers[i].outData[j].dimValues[0],
                  net->TIDLLayers[i].outData[j].dimValues[1],
                  net->TIDLLayers[i].outData[j].dimValues[3],
                  net->TIDLLayers[i].outData[j].dimValues[2],
                  BufDescList[numBuffs].bufPlanes[0].width,
                  BufDescList[numBuffs].bufPlanes[0].width*
                  (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad));
                  
              if(params->writeInput)
              {
                writeDataS8(fp1,
                  ((int8_t *)BufDescList[numBuffs].bufPlanes[0].buf + 
                  BufDescList[numBuffs].bufPlanes[0].width*tidlMaxPad + 
                  tidlMaxPad),net->TIDLLayers[i].outData[j].dimValues[1], 
                  net->TIDLLayers[i].outData[j].dimValues[3],
                  net->TIDLLayers[i].outData[j].dimValues[2],
                  BufDescList[numBuffs].bufPlanes[0].width,
                  BufDescList[numBuffs].bufPlanes[0].width*
                  (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad));
              }                          
            }
          }
          else
          {
            if(params->rawImage == 1)
            {
            readDataS8(fp1,((int8_t *)BufDescList[numBuffs].bufPlanes[0].buf +
                      BufDescList[numBuffs].bufPlanes[0].width*tidlMaxPad + 
                      tidlMaxPad), net->TIDLLayers[i].outData[j].dimValues[0],
                      net->TIDLLayers[i].outData[j].dimValues[1],    
                      net->TIDLLayers[i].outData[j].dimValues[3],
                      net->TIDLLayers[i].outData[j].dimValues[2], 
                      BufDescList[numBuffs].bufPlanes[0].width, 
                      BufDescList[numBuffs].bufPlanes[0].width* 
                  (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad));
            }
            else
            {
            readImage(params->inData,((int8_t *)BufDescList[numBuffs].bufPlanes[0].buf +
                      BufDescList[numBuffs].bufPlanes[0].width*tidlMaxPad + 
                      tidlMaxPad), net->TIDLLayers[i].outData[j].dimValues[0],
                      net->TIDLLayers[i].outData[j].dimValues[1],    
                      net->TIDLLayers[i].outData[j].dimValues[3],
                      net->TIDLLayers[i].outData[j].dimValues[2], 
                      BufDescList[numBuffs].bufPlanes[0].width, 
                      BufDescList[numBuffs].bufPlanes[0].width* 
                  (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad),
                  frameCount, params->preProcType);
            }
              
          }
          numBuffs++;
        }
      }
    }
  }
  if (params->readQ)
  {
    FREAD((int8_t *)dataQ, 1, numBuffs*sizeof(int), fp1);
  }
  return 0;
}


int32_t tidl_WriteNetOutputMem (tidl_conv2d_config *params,
                                IVISION_BufDesc *BufDescList, uint16_t numBuffs, int32_t * dataQ)
{
  int32_t i;
  uint16_t tidlMaxPad     = TIDL_MAX_PAD_SIZE;
  uint16_t nuChs;
  static int32_t firstCall = 1;
  TI_FILE * fp1;

  if(firstCall)
  {
    fp1 = FOPEN((const char *)params->outData, "wb+");
    firstCall = 0;
  }
  else
  {
    fp1 = FOPEN((const char *)params->outData, "ab+");
  }
  if(fp1 == NULL)
  {
    printf("Could not open %s file for writing \n",params->outData);
  }
  

  for(i = 0; i < numBuffs; i++)
  {
    sTIDL_DataParams_t * dataBuffParam;
    dataBuffParam = tidl_getDataBufDims(&createParams.net,BufDescList[i].bufferId);

    nuChs = dataBuffParam->dimValues[1];
    writeDataS8(fp1,((int8_t *)BufDescList[i].bufPlanes[0].buf + 
                BufDescList[i].bufPlanes[0].width*tidlMaxPad + tidlMaxPad),
                nuChs, BufDescList[i].bufPlanes[0].frameROI.width ,
                BufDescList[i].bufPlanes[0].frameROI.height ,
                BufDescList[i].bufPlanes[0].width,
                ((BufDescList[i].bufPlanes[0].width*
                BufDescList[i].bufPlanes[0].height)/ nuChs));
  }
  if (params->writeQ)
  {
    FWRITE((void *)dataQ, 1, sizeof(int32_t)*numBuffs, fp1);
  }

  if(fp1)
  {
    FCLOSE(fp1);
  }
  return 0;
}

int32_t tidl_AllocNetOutputMem(sTIDL_Network_t *net, tidl_conv2d_config *params,
                               IVISION_BufDesc   *BufDescList)
{
  int32_t i,j;
  uint16_t tidlMaxPad     = TIDL_MAX_PAD_SIZE;
  uint16_t numBuffs = 0;

  for(i = 0; i < net->numLayers; i++)
  {
    if(net->TIDLLayers[i].layersGroupId == TIDL_TB_CURR_LAYERS_GROUP_ID)
    {
      for(j = 0; j < net->TIDLLayers[i].numOutBufs; j++ )
      {
        if(tidltb_isOutDataBuff(net,net->TIDLLayers[i].outData[j].dataId, 
                                TIDL_TB_CURR_LAYERS_GROUP_ID))
        {
          BufDescList[numBuffs].numPlanes                          = 1;
          BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.x    = 0;
          BufDescList[numBuffs].bufPlanes[0].frameROI.topLeft.y    = 0;

          BufDescList[numBuffs].bufPlanes[0].width                 = 
                  net->TIDLLayers[i].outData[j].dimValues[3] + (2 * tidlMaxPad);
          BufDescList[numBuffs].bufPlanes[0].height                = 
                  net->TIDLLayers[i].outData[j].dimValues[0]*
                  net->TIDLLayers[i].outData[j].dimValues[1]*
                  (net->TIDLLayers[i].outData[j].dimValues[2] + 2*tidlMaxPad);
          BufDescList[numBuffs].bufPlanes[0].frameROI.width        = 
                  net->TIDLLayers[i].outData[j].dimValues[3];
          BufDescList[numBuffs].bufPlanes[0].frameROI.height       = 
                  net->TIDLLayers[i].outData[j].dimValues[2];

          BufDescList[numBuffs].bufPlanes[0].buf = 
              (int8_t *)TI_GetMemoryChunk(&memObj_EXTMEMNONCACHEIO, 
                  net->TIDLLayers[i].outData[j].pitch[0],4);
          BufDescList[numBuffs].reserved[0]      = 
              net->TIDLLayers[i].outData[j].dataId;
          memset( BufDescList[numBuffs].bufPlanes[0].buf,0, 
              net->TIDLLayers[i].outData[j].pitch[0]);
          BufDescList[numBuffs].bufferId         = 
              net->TIDLLayers[i].outData[j].dataId;
          numBuffs++;
        }
      }
    }
  }
  return numBuffs;
}

int32_t tidltb_printNetInfo(sTIDL_Network_t * pTIDLNetStructure, 
                            int32_t layersGroupId)
{
  int32_t i,j;
  for (i = 0 ; i < pTIDLNetStructure->numLayers; i++)
  {
    printf("%3d, %-30s,",i, 
                TIDL_LayerString[pTIDLNetStructure->TIDLLayers[i].layerType]);
    printf("%3d, %3d ,%3d ,",pTIDLNetStructure->TIDLLayers[i].layersGroupId, 
                             pTIDLNetStructure->TIDLLayers[i].numInBufs,
                             pTIDLNetStructure->TIDLLayers[i].numOutBufs);
                             
    for (j = 0; j < pTIDLNetStructure->TIDLLayers[i].numInBufs; j++) 
    {
      printf("%3d ,",pTIDLNetStructure->TIDLLayers[i].inData[j].dataId);
    }
    for (j = (pTIDLNetStructure->TIDLLayers[i].numInBufs > 0 ? 
          pTIDLNetStructure->TIDLLayers[i].numInBufs : 0); j < 8; j++) 
    {
      printf("  x ,");
    }
    printf("%3d ,",pTIDLNetStructure->TIDLLayers[i].outData[0].dataId);
    for (j = 0; j < 4; j++) 
    {
      printf("%5d ,",pTIDLNetStructure->TIDLLayers[i].inData[0].dimValues[j]);
    }
    for (j = 0; j < 4; j++) 
    {
      printf("%5d ,",pTIDLNetStructure->TIDLLayers[i].outData[0].dimValues[j]);
    }
    printf("\n");
  }
  return 0;
}
IVISION_BufDesc   inBufDesc[TIDL_MAX_ALG_IN_BUFS];
IVISION_BufDesc   outBufDesc[TIDL_MAX_ALG_OUT_BUFS];
#pragma DATA_SECTION (inArgs, ".iobuf");
#pragma DATA_SECTION (outArgs, ".iobuf");
TIDL_InArgs      inArgs;
TIDL_outArgs     outArgs;

int32_t test_ti_dl_ivison(void)
{

  int32_t numMemRec;
  IALG_MemRec *memRec;
  int32_t status, i;
  int32_t frameIdx;

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
  IVISION_BufDesc   *inBufDescList[TIDL_MAX_ALG_IN_BUFS];

  IVISION_OutBufs          outBufs;
  /*-----------------------------------------------------------------
  For test purpose it is allocated in stack. Application may get
  this descriptors from its buffer manager
  -----------------------------------------------------------------*/
  IVISION_BufDesc   *outBufDescList[TIDL_MAX_ALG_OUT_BUFS];
  TI_FILE * fp1;
  /*--------------------------------------------------------------------------*/
  /*Create memory handle for ARP32 DMEM.                                      */
  /*--------------------------------------------------------------------------*/

  tidl_conv2d_config * params;
  params = (tidl_conv2d_config *)(&gParams);

  TI_CreateMemoryHandle(&memObj_DMEM0, DMEM0_SCRATCH, DMEM0_SIZE);
  TI_CreateMemoryHandle(&memObj_DMEM1, DMEM1_SCRATCH, DMEM1_SIZE);
  TI_CreateMemoryHandle(&memObj_EXTMEMNONCACHEIO, EXTMEMNONCACHEIO, 
                         EXTMEMNONCACHEIO_SIZE);


  /*-----------------------------------------------------------------
  Set algorithm parameters
  -----------------------------------------------------------------*/
  createParams.visionParams.algParams.size   = sizeof(TIDL_CreateParams);
  createParams.visionParams.cacheWriteBack   = NULL;
  createParams.currCoreId                    = TIDL_TB_CURR_CORE_ID;
  createParams.currLayersGroupId             = TIDL_TB_CURR_LAYERS_GROUP_ID;

  createParams.l1MemSize                     = DMEM0_SIZE;
  createParams.l2MemSize                     = DMEM1_SIZE;
  createParams.l3MemSize                     = OCMC_SIZE;
 
  createParams.quantHistoryParam1   = 20;
  createParams.quantHistoryParam2   = 5;
  createParams.quantMargin          = 0;
  createParams.optimiseExtMem       = TIDL_optimiseExtMemL1; 
  
  tidl_readNet(&createParams.net,params->netBinFile);
  createParams.net.interElementSize = 4;
  Cache_WbInvAll();
  tidl_allocNetParamsMem(&createParams.net);
  tidl_fillNetParamsMem(&createParams.net,params);
  Cache_WbInvAll();
  if(params->runFullNet)
  {
    tidl_UpdateLayersGroup(&createParams.net);
  }
  tidltb_printNetInfo(&createParams.net,createParams.currLayersGroupId );


#if (CORE_EVE) && (!VCOP_HOST_EMULATION)
  profiler_init();
  profiler_start();
#endif
  numMemRec = TIDL_VISION_FXNS.ialg.algNumAlloc();
  memRec    = (IALG_MemRec *)malloc(numMemRec*sizeof(IALG_MemRec));

  status = TIDL_VISION_FXNS.ialg.algAlloc(
    (IALG_Params *)(&createParams), NULL, memRec);

  if(status != IALG_EOK)
  {
    printf("\n TIDL returned with error code : %d, refer to interface header file for error code details \n\n", status);
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
    printf("\n TIDL returned with error while allocating memory \n\n", status);    
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
  /*-----------------------------------------------------------------
  Intialize the algorithm instance with the allocated memory
  and user create parameters
  -----------------------------------------------------------------*/
  Cache_WbInvAll();
  status = TIDL_VISION_FXNS.ialg.algInit((IALG_Handle)(&handle),
    memRec,NULL,(IALG_Params *)(&createParams));
  Cache_WbInvAll();
  handle = (IM_Fxns *) memRec[0].base;
#if (CORE_EVE) && (!VCOP_HOST_EMULATION)
  profiler_end_print(0);
#endif
  if(status != IALG_EOK)
  {
    printf("\n TIDL returned with error code : %d, refer to interface header file for error code details \n\n", status);    
    PRINT_ERRORE_MSG();
    goto EXIT_LOOP;
  }
#if ENABLE_TRACES
  TEST_PRINTF("Algorithm Init Done\n");
#endif

  inBufs.bufDesc  = inBufDescList;
  outBufs.bufDesc = outBufDescList;

  inBufs.numBufs  = tidl_AllocNetInputMem(&createParams.net,params,inBufDesc);
  outBufs.numBufs = tidl_AllocNetOutputMem(&createParams.net,params,outBufDesc);

  for(i = 0; i < inBufs.numBufs; i++)
  {
    inBufDescList[i]     = &inBufDesc[i];
  }
  for(i = 0; i < outBufs.numBufs; i++)
  {
    outBufDescList[i]     = &outBufDesc[i];
  }

  outArgs.iVisionOutArgs.size       = sizeof(TIDL_outArgs);
  inArgs.iVisionInArgs.size         = sizeof(TIDL_InArgs);
  inArgs.iVisionInArgs.subFrameInfo = 0;
  
  fp1 = tidl_openNetInput(params);
  
  for(frameIdx = 0 ; frameIdx < params->numFrames; frameIdx++)
  {
    printf("\nProcessing Frame Number : %d \n\n",frameIdx);
    tidl_ReadNetInput(fp1, &createParams.net,params,inBufDesc,frameIdx, &inArgs.dataQ[0]);
    Cache_WbInvAll();
#if (CORE_EVE) && (!VCOP_HOST_EMULATION)
    profiler_start();
#elif (CORE_DSP) && (!HOST_EMULATION)
     tsc_start = _TSC_read();
#endif
    status = handle->ivision->algProcess((IVISION_Handle)handle,
      &inBufs,&outBufs,(IVISION_InArgs *)&inArgs,(IVISION_OutArgs *)&outArgs);
#if (CORE_EVE) && (!VCOP_HOST_EMULATION)
    profiler_end_print(1);
#elif (CORE_DSP) && (!HOST_EMULATION)
     tsc_cycles  =  _TSC_read();
     if(tsc_cycles < tsc_start)
     {
         printf(" TSC Mega Cycles = %8.2f with Over Flow ", (tsc_cycles/1000000.0));
     }
     else
     {
         tsc_cycles -= tsc_start;
         printf(" TSC Mega Cycles = %8.2f ", (tsc_cycles/1000000.0));
     }
#endif
    Cache_WbInvAll();

    if(params->writeOutput)
    {
      tidl_WriteNetOutputMem(params,outBufDesc,outBufs.numBufs, &outArgs.dataQ[0]);
    }
  }
  FCLOSE(fp1);
  
  status = handle->ivision->ialg.algFree((IALG_Handle)(handle), memRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
  }
  
  if(params->updateNetWithStats)
  {
    tidl_writeNetWithStats(params);
  }
  
  /* Here Free memory for all the mem records */
  status = TestApp_FreeMemRecords(memRec,numMemRec);
  if(status != IALG_EOK)
  {
    PRINT_ERRORE_MSG();
  }

  /* Get the stack usage */
#if !(HOST_EMULATION) && (!CORE_DSP) && 0
  profiler_getStackDepth();
#endif
EXIT_LOOP:

  return status;
}

int32_t main(int32_t argc, char *argv[])
{
  FILE * fp;
  char * LinePtr;
  int32_t status;
  int32_t lineNum = -1;
  tidl_conv2d_config * params;
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
  params = (tidl_conv2d_config *)(&gParams);
  //report_printAppletInfo((int8_t *)"TIDL_VISION");

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
      status = readparamfile(configFileName, &gsTokenMap_tidl_conv2d[0]) ;
      if(status == -1)
      {
        printf("Parser Failed");
        return -1 ;
      }
      strcpy((char *)traceDumpBaseName,(char *)params->traceDumpBaseName);
      status = test_ti_dl_ivison();
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
