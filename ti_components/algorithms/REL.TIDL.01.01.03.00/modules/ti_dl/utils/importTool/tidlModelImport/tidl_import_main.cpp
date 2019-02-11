/*
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the  
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>  // for function execvp()
#endif

#include "tidl_import_config.h"
#include "ti_dl.h"

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
};

void setDefaultParams(tidl_import_config * params)
{
  int i;
  params->randParams          = 0;
  params->modelType           = 0; // 0 - caffe, 1- tensorFlow
  params->quantizationStyle   = TIDL_quantStyleDynamic; 
  params->quantRoundAdd       = 50; // 0 - caffe, 1- tensorFlow
  params->numParamBits        = 8;
  params->rawSampleInData     = 0; // 0 - Encoded, 1- RAW
  params->numSampleInData     = 1;
  params->foldBnInConv2D      = 1;
  params->preProcType         = 0;
  params->inElementType       = TIDL_SignedChar;
  params->inQuantFactor       = -1;

  params->inWidth               = -1;
  params->inHeight              = -1;
  params->inNumChannels         = -1;
  for(i = 0; i < TIDL_NUM_MAX_LAYERS; i++)
  {
    params->layersGroupId[i] = 1;
    params->conv2dKernelType[i] = 0;
  }

}

void tidlQuantStatsTool(tidl_import_config * params)
{
  FILE * fp;
  char sysCommand[500];

#ifdef _WIN32
  sprintf(sysCommand, "if exist tempDir rmdir /S/Q tempDir");
  system(sysCommand);
  sprintf(sysCommand, "mkdir tempDir");
  system(sysCommand);
  fp = fopen("tempDir\\configFilesList.txt", "w+");
  
  if(fp== NULL)
  {
    printf("Could not open config  file tempDir\\configFilesList.txt  \n");
    return;
  }
  fprintf(fp, "1 .\\tempDir\\qunat_stats_config.txt \n0\n" );
  fclose(fp);

  fp = fopen("tempDir\\qunat_stats_config.txt", "w+");
  if(fp== NULL)
  {
    printf("Could not open config  file tempDir\\qunat_stats_config.txt  \n");
    return;
  }
  fprintf(fp, "rawImage    = %d\n",params->rawSampleInData);
  fprintf(fp, "numFrames   = %d\n",params->numSampleInData);
  fprintf(fp, "preProcType  = %d\n",params->preProcType);
  fprintf(fp, "inData   = %s\n",params->sampleInData);
  fprintf(fp, "traceDumpBaseName   = \".\\tempDir\\trace_dump_\"\n");
  fprintf(fp, "outData   = \".\\tempDir\\stats_tool_out.bin\"\n");
  fprintf(fp, "updateNetWithStats   = 1\n");
  fprintf(fp, "outputNetBinFile     = %s\n",params->outputNetFile);
  fprintf(fp, "paramsBinFile        = %s\n",params->outputParamsFile);
  fprintf(fp, "netBinFile   = \".\\tempDir\\temp_net.bin\"\n");
  fclose(fp);
  
  sprintf(sysCommand, "copy  %s .\\tempDir\\temp_net.bin",params->outputNetFile) ;
  system(sysCommand);
  sprintf(sysCommand, " %s .\\tempDir\\configFilesList.txt",params->tidlStatsTool);
  system(sysCommand);  
#else
  system ("rm -rf tempDir; mkdir -p ./tempDir");
  fp = fopen("tempDir/configFilesList.txt", "w+");
  if(fp== NULL)
  {
    printf("Could not open config  file tempDir/configFilesList.txt  \n");
    return;
  }
  fprintf(fp, "1 ./tempDir/qunat_stats_config.txt \n0\n" );
  fclose(fp);

  fp = fopen("tempDir/qunat_stats_config.txt", "w+");
  if(fp== NULL)
  {
    printf("Could not open config  file tempDir/qunat_stats_config.txt  \n");
    return;
  }
  fprintf(fp, "rawImage    = %d\n",params->rawSampleInData);
  fprintf(fp, "numFrames   = %d\n",params->numSampleInData);
  fprintf(fp, "preProcType  = %d\n",params->preProcType);
  fprintf(fp, "inData   = %s\n",params->sampleInData);
  fprintf(fp, "traceDumpBaseName   = \"./tempDir/trace_dump_\"\n");
  fprintf(fp, "outData   = \"./tempDir/stats_tool_out.bin\"\n");
  fprintf(fp, "updateNetWithStats   = 1\n");
  fprintf(fp, "outputNetBinFile     = %s\n",params->outputNetFile);
  fprintf(fp, "paramsBinFile        = %s\n",params->outputParamsFile);
  fprintf(fp, "netBinFile   = \"./tempDir/temp_net.bin\"\n");
  fclose(fp);
  
  sprintf(sysCommand, "cp  %s ./tempDir/temp_net.bin",params->outputNetFile) ;
  system(sysCommand);
  sprintf(sysCommand, " %s ./tempDir/configFilesList.txt",params->tidlStatsTool);
  //system(sysCommand);  
  // use execvp() instead of system() to search the executable in directories specified by env PATH
  char *args[]={(char *)params->tidlStatsTool, "./tempDir/configFilesList.txt", NULL};
  if(execvp(args[0],args)) {
    printf("Couldn't open tidlStatsTool file: %s  \n", params->tidlStatsTool);
    exit(0);
  }
#endif
  
  return;
  
}

/**
----------------------------------------------------------------------------
@ingroup    TIDL_Import
@fn         tidlValidateImportParams
@brief      Function validates input parameters related to tidl import 
            sets appropriate error in response to violation from 
            expected values.
            
@param      params : TIDL Create time parameters
@remarks    None
@return     Error related to parameter.
----------------------------------------------------------------------------
*/
int32_t tidlValidateImportParams(tidl_import_config * params)
{  

  /* randParams can be either 0 or 1*/
  if((params->randParams != 0) && (params->randParams != 1))
  {
    printf("\n Invalid randParams setting : set either 0 or 1");
    return -1;
  }
  /* modelType can be either 0 or 1*/
  else if((params->modelType != 0) && (params->modelType != 1))
  {
    printf("\n Invalid modelType parameter setting : set either 0 or 1");
    return -1;
  }   
  /* Currently quantizationStyle = 1 is supported */
  /*else if(params->quantizationStyle != 1)
  {
    printf("\n Invalid quantizationStyle parameter setting : set it to 1");
    return -1;
  }*/
  /* quantRoundAdd can be 0 to 100 */
  else if((params->quantRoundAdd < 0) || (params->quantRoundAdd > 100))
  {
    printf("\n Invalid quantRoundAdd parameter setting : set it 0 to 100");
    return -1;
  }  
  /* numParamBits can be 4 to 12 */
  else if((params->numParamBits < 4) || (params->numParamBits > 12))
  {
    printf("\n Invalid numParamBits parameter setting : set it 4 to 12");
    return -1;
  } 
  /* rawSampleInData can be either 0 or 1*/
  else if((params->rawSampleInData != 0) && (params->rawSampleInData != 1))
  {
    printf("\n Invalid rawSampleInData parameter setting : set either 0 or 1");
    return -1;
  }   
  /* numSampleInData can be >0  */
  else if(params->numSampleInData <= 0)
  {
    printf("\n Invalid numSampleInData parameter setting : set it to >0 ");
    return -1;
  }    
  /* foldBnInConv2D can be either 0 or 1*/
  else if((params->foldBnInConv2D != 0) && (params->foldBnInConv2D != 1))
  {
    printf("\n Invalid foldBnInConv2D parameter setting : set either 0 or 1");
    return -1;
  }    
  /* preProcType can be 0 to 4 */
  else if((params->preProcType < 0) || (params->preProcType > 6))
  {
    printf("\n Invalid preProcType parameter setting : set it 0 to 3");
    return -1;
  }    
  /* inElementType can be either 0 or 1*/
  else if((params->inElementType != 0) && (params->inElementType != 1))
  {
    printf("\n Invalid inElementType parameter setting : set either 0 or 1");
    return -1;
  }  
  /* inQuantFactor can be >0  */
  else if((params->inQuantFactor < -1) || (params->inQuantFactor == 0))
  {
    printf("\n Invalid inQuantFactor parameter setting : set it to >0 ");
    return -1;
  }
  /* inWidth can be >0  */
  else if((params->inWidth < -1) || (params->inWidth == 0))
  {
    printf("\n Invalid inWidth parameter setting : set it to >0 ");
    return -1;
  } 
  /* inHeight can be >0  */
  else if((params->inHeight < -1) || (params->inHeight == 0))
  {
    printf("\n Invalid inHeight parameter setting : set it to >0 ");
    return -1;
  } 
  /* inNumChannels can be 1 to 1024  */
  else if((params->inNumChannels < -1) || (params->inNumChannels == 0) || (params->inNumChannels > 1024))
  {
    printf("\n Invalid inNumChannels parameter setting : set it 1 to 1024 ");
    return -1;
  }  
  else
  {
    return 0;
  }
}

sTIDL_OrgNetwork_t      orgTIDLNetStructure;
sTIDL_Network_t         tIDLNetStructure;
void caffe_import( tidl_import_config * params);
void tf_import(tidl_import_config * params);

int32_t main(int32_t argc, char *argv[])
{
  int32_t status = 0;
  int32_t runQuantStep = 0;
  FILE * fp;
  if(argc < 2)
  {
    printf("Number of input parameters are not enough \n");
    printf("Usage : \n tidl_model_import.out.exe config_file.txt\n");
    exit(-1);  
  }

                                 
  fp = fopen(argv[1], "r");
  if(fp== NULL)
  {
    printf("Could not open config  file : %s  \n",argv[1]);
    return(0);
  }
  fclose(fp);
  
  setDefaultParams(&gParams) ;
 
  status = readparamfile(argv[1], &gsTokenMap_tidl_import_config[0]) ;

  if(status == -1)
  {
    printf("Parser Failed");
    return -1 ;
  }

  status = tidlValidateImportParams(&gParams);    
  if(status == -1)
  {
    printf("\n Validation of Parameters Failed \n");
    return -1 ;
  }
  
  /*  inputNetFile && inputParamsFile */
  fp = fopen((const char *)gParams.inputNetFile, "r");
  if(fp== NULL)
  {
    printf("Couldn't open inputNetFile file: %s  \n", gParams.inputNetFile);
    return(0);
  }
  fclose(fp);

  if(gParams.modelType == 0)
  {
    fp = fopen((const char *)gParams.inputParamsFile, "r");
    if(fp== NULL)
    {
      printf("Couldn't open inputParamsFile file: %s  \n", gParams.inputParamsFile);
      return(0);
    }
    fclose(fp);
  }
  
  
  if(gParams.modelType == 0)
  {
    if(gParams.inQuantFactor == -1)
    {
      gParams.inQuantFactor = 255;
    }
    caffe_import(&gParams);
  }
  else if (gParams.modelType == 1)
  {
    if(gParams.inQuantFactor == -1)
    {
      if(gParams.inElementType == TIDL_SignedChar)
      {
        gParams.inQuantFactor = 128*255;
      }
      else /* if(gParams.inElementType == TIDL_UnsignedChar) */
      {
        gParams.inQuantFactor = 256*255;        
      }
    }
    tf_import(&gParams);
  }

  

  fp = fopen((const char *)gParams.sampleInData, "r");
  if(fp== NULL)
  {
    printf("Couldn't open sampleInData file: %s  \n", gParams.sampleInData);
    return(0);
  }
  fclose(fp);

#ifdef _WIN32
  // This is only needed in Windows as execvp() checks if this file exists in Linux.
  fp = fopen((const char *)gParams.tidlStatsTool, "r");
  if(fp== NULL)
  {
    printf("Couldn't open tidlStatsTool file: %s  \n", gParams.tidlStatsTool);
    return(0);
  }
  fclose(fp);
#endif  

  tidlQuantStatsTool(&gParams);

  
  return (0);
}
