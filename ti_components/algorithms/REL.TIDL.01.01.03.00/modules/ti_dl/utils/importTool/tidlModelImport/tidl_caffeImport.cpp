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

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/message.h>
#include <google/protobuf/text_format.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#endif
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "ti_dl.h"
#include "caffe.pb.h"
#include <cfloat>
#include "tidl_import_config.h"

using namespace std;
using namespace caffe;
using ::google::protobuf::Message;
using ::google::protobuf::io::FileInputStream;
using ::google::protobuf::io::FileOutputStream;
using ::google::protobuf::io::ZeroCopyInputStream;
using ::google::protobuf::io::CodedInputStream;
using ::google::protobuf::io::ZeroCopyOutputStream;
using ::google::protobuf::io::CodedOutputStream;
#include "tidl_import_common.h" 

int quantizationStyle;
int ssdNet;
#define QUAN_STYLE01_ROUND (0.5)

#define ENABLE_FIXED_QUANT_STYLE (1)

#ifdef PLATFORM_64BIT
void * sBuffPtrs[MAX_NUM_PTRS_TO_STORE];
uint32_t sBufPtrInd = 0;
#endif

int TIDL_flApply(float data, int fl)
{
  int out;
  if( data > 0)
  {
    out = (data* (1 << fl) + QUAN_STYLE01_ROUND);
  }
  else
  {
    out = (data* (1 << fl) - QUAN_STYLE01_ROUND);
  }
  return out;
}

#define IS_SIGNED_DATA (1)

int32_t TIDL_QuantizeP2(int8_t * params, float * data, int32_t dataSize, float min, float max)
{
  int32_t i;
  float absMax = abs(min) > abs(max) ? abs(min) : abs(max);
  float absMaxP2 = pow(2, ceil(log(absMax)/log(2)));

  float fl_range = ((1.0*(1 << (NUM_WHGT_BITS - IS_SIGNED_DATA))) / absMaxP2);
  int32_t fl = (int32_t)log(fl_range)/log(2);

  for(i = 0; i < dataSize; i++)
  {
    params[i] = TIDL_flApply(data[i], fl);
  }
  return fl;
}

int32_t TIDL_isInputEltWise(sTIDL_OrgNetwork_t  *pOrgTIDLNetStructure,
int32_t             numLayer, 
const char          *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs == 1) && 
            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_EltWiseLayer))
        {
          return 1 ;
        }
        else
        {
          return 0 ;
        }
      }
    }
  }
  return 0;
}

int32_t TIDL_isInputPermute(sTIDL_OrgNetwork_t  *pOrgTIDLNetStructure,
int32_t             numLayer, 
const char          *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs == 1) && 
            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_PermuteLayer))
        {
          return 1 ;
        }
        else
        {
          return 0 ;
        }
      }
    }
  }
  return 0;
}

int32_t TIDL_isInputReshape(sTIDL_OrgNetwork_t  *pOrgTIDLNetStructure,
int32_t             numLayer, 
const char          *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs == 1) && 
            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ReshapeLayer))
        {
          return 1 ;
        }
        else
        {
          return 0 ;
        }
      }
    }
  }
  return 0;
}

int32_t TIDL_isInputFlatten(sTIDL_OrgNetwork_t  *pOrgTIDLNetStructure,
int32_t             numLayer, 
const char          *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs == 1) && 
            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_FlattenLayer))
        {
          return 1 ;
        }
        else
        {
          return 0 ;
        }
      }
    }
  }
  return 0;
}

int32_t TIDL_isInputSoftMax(sTIDL_OrgNetwork_t  *pOrgTIDLNetStructure,
int32_t             numLayer, 
const char          *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs == 1) && 
            (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_SoftMaxLayer))
        {
          return 1 ;
        }
        else
        {
          return 0 ;
        }
      }
    }
  }
  return 0;
}

int32_t TIDL_isInputInnreProduct(sTIDL_OrgNetwork_t *pOrgTIDLNetStruct,
int32_t            numLayer, 
const char         *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStruct->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStruct->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStruct->TIDLPCLayers[i].numOutBufs == 1) && 
            (pOrgTIDLNetStruct->TIDLPCLayers[i].layerType==TIDL_InnerProductLayer))
        {
          return 1 ;
        }
        else
        {
          return 0 ;
        }
      }
    }
  }
  return 0;
}
int32_t TIDL_isInputBatchNorm(sTIDL_OrgNetwork_t *pOrgTIDLNetStruct,
int32_t            numLayer, 
const char         *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStruct->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStruct->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStruct->TIDLPCLayers[i].numOutBufs == 1) && 
            (pOrgTIDLNetStruct->TIDLPCLayers[i].layerType==TIDL_BatchNormLayer))
        {
          return 1 ;
        }
        else
        {
          return 0 ;
        }
      }
    }
  }
  return 0;
}

int32_t TIDL_inputLayerIndex(sTIDL_OrgNetwork_t *pOrgTIDLNetStructure,
int32_t            numLayer, 
const char         *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,
            (const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        return i;
      }
    }
  }
  return -1;
}

int32_t TIDL_isBottomUsedLater(const char* botName, int32_t startLayer,
NetParameter &netStructure)
{
  int32_t i,j;
  for (i = startLayer+1; i < netStructure.layer_size(); i++)
  {
    for (j = 0; j < netStructure.layer(i).bottom_size(); j++)
    {       
      if(strcmp((const char*)botName,
            (const char*)netStructure.layer(i).bottom(j).c_str()) == 0)
      {
        return true;
      }
    }
  }
  return false;
}

int TIDL_appCNNInteropCaffeFindLayerByName(const char *name, 
const NetParameter &netParams)
{
  int i;
  int layerNum = netParams.layer_size();
  for (i = 0; i < layerNum; i++) {
    if (string(name) == netParams.layer(i).name()) 
    {
      return i;
    }
  }
  return -1;
}


int TIDL_appCNNConverRawDataToData(NetParameter &netParams)
{
  int i,j,k;
  int layerNum = netParams.layer_size();
  for (i = 0; i < layerNum; i++) 
  {
    for (j = 0; j < netParams.layer(i).blobs_size(); j++) 
    {
      if(netParams.layer(i).blobs(j).has_raw_data())
      {
        Type raw_type = netParams.layer(i).blobs(j).raw_data_type();
        const ::std::string& hd = netParams.layer(i).blobs(j).raw_data();
        if (raw_type == caffe::FLOAT ) 
        {
          int data_size = hd.size() / 4;
          float *Y = (float*)(&hd.front());
          BlobProto & blob = (BlobProto&)netParams.layer(i).blobs(j);
          for(k = 0 ; k < data_size; k++)
          {
            blob.add_data(Y[k]);
          }
        }
        else
        {
          printf("Un supported raw_dat_tyep\n");
          return -1;
        }
      }
    }
  }
  return -1;
}

void TIDL_importConcatParams(sTIDL_OrgNetwork_t *pOrgTIDLNetStructure,
int32_t            i,
int32_t            *pLayerIndex,
int32_t            *pDataIndex,
NetParameter       netStructure)
{
  int32_t ii, j, status, numOuChs = 0, outWidth = 0;
  int32_t total_priorBoxSize, num_heads, k, data_offset;
  int32_t prevLayerIdx, layerIndex = *pLayerIndex;
  int32_t dataIndex  = *pDataIndex;  
  prevLayerIdx = TIDL_inputLayerIndex(pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str());
  if(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerType == TIDL_PriorBoxLayer)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].numMacs = 1;
    
    total_priorBoxSize = 1; // To store number of heads
    num_heads = 0;
    for (ii = 0; ii < netStructure.layer(i).bottom_size(); ii++) 
    {
      prevLayerIdx = TIDL_inputLayerIndex(pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(ii).c_str());
      if(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerType == TIDL_PriorBoxLayer)
      {
        total_priorBoxSize += pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBoxSize;
        num_heads++;
      }
    }

    /* calculate the size of all the priorboxes for concatination */
    float *top_data   = (float *)malloc(total_priorBoxSize*sizeof(float));
    data_offset = 1;
    top_data[0] = (float)num_heads;    
    for (ii = 0; ii < netStructure.layer(i).bottom_size(); ii++) 
    {
      prevLayerIdx = TIDL_inputLayerIndex(pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(ii).c_str());
      if(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerType == TIDL_PriorBoxLayer)
      {
        float * data      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.ptr);
        uint32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.bufSize;
        for(k = 0; k < dataSize; k++)
        {
          top_data[data_offset + k] = data[k]; 
        }
        data_offset += dataSize; 
        free(data);        
        RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.ptr);
        pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.bufSize = 0;        
      }
    } 
    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType      = 
    TIDL_PriorBoxLayer;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs     = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],
    netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = 
    dataIndex++;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBox.ptr,top_data);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBox.bufSize = data_offset; 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBoxSize = data_offset;     
    layerIndex++;    
  }
  else
  {    
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType      = 
  TIDL_ConcatLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs     = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],
  netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = 
  dataIndex++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs      = 
  netStructure.layer(i).bottom_size();
  
  if(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerType == TIDL_FlattenLayer)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.concatParams.axis = 1;
    //netStructure.layer(i).concat_param().axis();
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.concatParams.axis = 0;
  }
  
  if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.concatParams.axis)
  {
    for(j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++) 
    {
      strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j],
      netStructure.layer(i).bottom(j).c_str());
      status = TIDL_getDataID(
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j], 
      pOrgTIDLNetStructure,
      layerIndex, 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
      if(status == -1)
      {
        printf("Could not find the requested input Data : %s !!",
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
        exit(-1);
      }
      outWidth += 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].dimValues[1]*
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].dimValues[2]*
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].dimValues[3]);
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_UnsignedChar;
    for(j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++) 
    {
      /* If one of the input is signed then set out elementType to signed */
      if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].elementType == TIDL_SignedChar)
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType  = 
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].elementType;              
        break;
      }
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = outWidth;    
  }    
  else
  {
    for(j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++) 
    {
      strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j],
      netStructure.layer(i).bottom(j).c_str());
      status = TIDL_getDataID(
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j], 
      pOrgTIDLNetStructure,
      layerIndex, 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
      if(status == -1)
      {
        printf("Could not find the requested input Data : %s !!",
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
        exit(-1);
      }
      numOuChs += 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].dimValues[1];
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_UnsignedChar;
    for(j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++) 
    {
      /* If one of the input is signed then set out elementType to signed */
      if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].elementType == TIDL_SignedChar)
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType  = 
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j].elementType;              
        break;
      }
    }    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 
    numOuChs;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];    
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;
  layerIndex++;
  }
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;    
}

int32_t TIDL_isInputConv2DCaffe(
NetParameter         &netStructure,
int  netLayerIndex,
sTIDL_OrgNetwork_t   *pOrgTIDLNetStruct,
int32_t              layerIndex, 
const char           *bufName)
{
  int i, layerNum, canMerge = 1 ;

  //Make sure that the output is not used by someone else 
  if(netStructure.layer(netLayerIndex).bottom(0) != netStructure.layer(netLayerIndex).top(0))
  {
    layerNum = netStructure.layer_size();
    for (i = 0; i < layerNum; i++) {
      if (netStructure.layer(i).bottom(0) == netStructure.layer(netLayerIndex).bottom(0) && i != netLayerIndex )
      {
        if(netStructure.layer(i).bottom(0) != netStructure.layer(i).top(0))
        {
          canMerge = 0 ;
          break;
        }
      }
    }
  }
  if(canMerge)
  {
    canMerge = TIDL_isInputConv2D(pOrgTIDLNetStruct, layerIndex, bufName) ;
  }
  return canMerge ;
}

void TIDL_setConv2dKernelType(sTIDL_Network_t   *pTIDLNetStructure, int32_t tiLayerIndex)
{
  int layerIndex;
  for (layerIndex = 0; layerIndex < tiLayerIndex; layerIndex++) 
  {
    if(pTIDLNetStructure->TIDLLayers[layerIndex].layerType ==  TIDL_ConvolutionLayer)
    {
      if(gParams.conv2dKernelType[layerIndex] == 0)
      {
        pTIDLNetStructure->TIDLLayers[layerIndex].layerParams.convParams.kernelType = TIDL_sparse;
      }
      else if(gParams.conv2dKernelType[layerIndex] == 1)
      {
        if((((pTIDLNetStructure->TIDLLayers[layerIndex].layerParams.convParams.kernelW == 1 )) ||
              ((pTIDLNetStructure->TIDLLayers[layerIndex].layerParams.convParams.kernelW == 3 ) &&
                (pTIDLNetStructure->TIDLLayers[layerIndex].layerParams.convParams.kernelH == 3 ))) &&
            ((pTIDLNetStructure->TIDLLayers[layerIndex].layerParams.convParams.strideW == 1 ) &&
              (pTIDLNetStructure->TIDLLayers[layerIndex].layerParams.convParams.strideH == 1 )) )
        {             
         //if((pTIDLNetStructure->TIDLLayers[layerIndex].outData[0].dimValues[3] < 64) ||
         //    (pTIDLNetStructure->TIDLLayers[layerIndex].outData[0].dimValues[3] < 64) )
          {
            pTIDLNetStructure->TIDLLayers[layerIndex].layerParams.convParams.kernelType = TIDL_dense;
          }
        }
      }
    }
  }
}

void TIDL_importConvParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
FILE                 *fp1,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
NetParameter         netStructure,
NetParameter         netParams)
{
  int32_t             status, id;
  int32_t             pad, stride;
  int32_t             paramSet = 0;
  int32_t             dataSize;
  int32_t             conv2DRandParams = 0;
  int32_t             prevLayerIdx = 0;  
  float min, max;
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType    =   
  TIDL_ConvolutionLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs   =   1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],
  netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = 
  dataIndex++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs    =   1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],
  netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(
  &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], 
  pOrgTIDLNetStructure,
  layerIndex, 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numInChannels  = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numOutChannels = 
  netStructure.layer(i).convolution_param().num_output();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups      = 
  netStructure.layer(i).convolution_param().group();
  if(netStructure.layer(i).convolution_param().kernel_w() == 0 || netStructure.layer(i).convolution_param().kernel_h() == 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW        = 
    netStructure.layer(i).convolution_param().kernel_size(0);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH        = 
    netStructure.layer(i).convolution_param().kernel_size(0);    
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW        = 
    netStructure.layer(i).convolution_param().kernel_w();
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH        = 
    netStructure.layer(i).convolution_param().kernel_h();        
  }

  if (netStructure.layer(i).convolution_param().pad_size() == 0) {
    pad = 0;
  }
  else {
    pad = netStructure.layer(i).convolution_param().pad(0);
  }
  if (netStructure.layer(i).convolution_param().stride_size() == 0) {
    stride = 1;
  }
  else {
    stride = netStructure.layer(i).convolution_param().stride(0);
  }

  if (netStructure.layer(i).convolution_param().dilation_size() == 0) {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH = 1;
  }
  else {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW = 
    netStructure.layer(i).convolution_param().dilation(0);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideW= 
  stride;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH= 
  stride;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padW   = 
  pad;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padH   = 
  pad;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numOutChannels;
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] + 
  (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padH*2)-  
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH-1)*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH+1))/
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH) + 1;
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3] + 
  (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padW*2)-  
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW-1)*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW + 1))/
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideW) + 1;
  
#if 0 // used a separate function(TIDL_setConv2dKernelType) to do this..
  if(gParams.conv2dKernelType[layerIndex] == 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelType = TIDL_sparse;
  }
  else if(gParams.conv2dKernelType[layerIndex] == 1)
  {
    if((((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW == 1 ) &&
            (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH == 1 )) ||
          ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW == 3 ) &&
            (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH == 3 ))) &&
        ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideW == 1 ) &&
          (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH == 1 )) )
    {       
      
     //if((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] < 64) ||
     //    (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] < 64) )
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelType = TIDL_dense;
      }
    }
  }
#endif
  
  if(quantizationStyle == TIDL_quantStyleFixed)
  {
#if ENABLE_FIXED_QUANT_STYLE
	id = TIDL_appCNNInteropCaffeFindLayerByName(
		(char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, netParams);
	if (id == -1)
	{
		printf("Could not find %s in Model file \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
	}
	else
	{
		if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType =
				TIDL_UnsignedChar;
		}
		else
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType =
				TIDL_SignedChar;
		}
		pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.inDataQ =
			netParams.layer(id).quantization_param().qparam_in(0).fracbits();
		if (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.inDataQ < 0)
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.inDataQ = 0;
		}
		pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.outDataQ =
			netParams.layer(id).quantization_param().qparam_out().fracbits();
		pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weightsQ =
			netParams.layer(id).quantization_param().qparam_w().fracbits();
	}
#endif
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = 
    TIDL_SignedChar;
  }

  id = TIDL_appCNNInteropCaffeFindLayerByName(
  (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
  paramSet = 0;
  if((id != -1) && (conv2DRandParams == 0))
  {
    if(netParams.layer(id).blobs_size() > 0)
    {
      dataSize = netParams.layer(id).blobs(0).data_size();
      if(dataSize != 
          ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
              pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW * 
              pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH * 
              pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1])/
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups))
      {
        printf("Kernel Size not matching %d !!", dataSize);
      }
      else
      {
        paramSet = 1;
        float  * data   = (float *)malloc(dataSize*sizeof(float));
        for (int idx = 0; idx < dataSize; idx++) 
        {
          data[idx] = netParams.layer(id).blobs(0).data(idx);
        }

        STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.ptr,data);
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.bufSize = dataSize;

      }
    }
  }
  if(paramSet == 0)
  {
    dataSize = 
    ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW * 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH * 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1])/
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups);
    printf("Setting RAND Kernel Params for Layer %s \n", 
    (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);


    float  * data   = (float *)malloc(dataSize*sizeof(float));
    for (int idx = 0; idx < dataSize; idx++) {
      uint8_t val = (rand() & (0X7F));
      data[idx] = ((float)((rand()&1) ? val : -val))/64;
    }      
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.ptr,data);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.bufSize = dataSize;  
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableBias = 
  netStructure.layer(i).convolution_param().bias_term();
  if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableBias)
  {
    paramSet = 0;
    if(id != -1)
    {
      if(netParams.layer(id).blobs_size() > 1)
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableBias = 1;
        dataSize = netParams.layer(id).blobs(1).data_size();
        if(dataSize != (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]))
        {
          printf("Bias Size not matching!!");

        }  
        else
        {
          paramSet = 1;
          float * data = (float *)malloc(dataSize*sizeof(float));
          for (int idx = 0; idx < dataSize; idx++) 
          {
            data[idx] = netParams.layer(id).blobs(1).data(idx);
          }
          STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.ptr,data);
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.bufSize = dataSize;
        }
      }
    }
    if(paramSet == 0)
    {
      dataSize = 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]);
      printf("Setting RAND BIAS Params for Layer %s \n", 
      (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);

      float  * data   = (float *)malloc(dataSize*sizeof(float));
      for (int idx = 0; idx < dataSize; idx++) {
        uint16_t val = (rand() & (0X7FFF));
        data[idx] = ((float)((rand()&1) ? val : -val))/256;      
      }      
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.ptr,data);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.bufSize = dataSize;  
    }
  }
  if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.inDataQ < 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.inDataQ = 0;
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
  (int64_t)(((int64_t)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW * 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH * 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]) / pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups);
}

void TIDL_importPoolingParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
int32_t              *pDataIndex,
NetParameter         netStructure,
NetParameter         netParams)
{
  int32_t     status;
  int32_t     layerIndex;
  int32_t     dataIndex;


  layerIndex = *pLayerIndex;
  dataIndex  = *pDataIndex;
  int32_t id = TIDL_appCNNInteropCaffeFindLayerByName(
	  (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, netParams);
  if (id == -1)
  {
	  printf("Could not find %s in Model file \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
  }

  if(TIDL_isInputConv2DCaffe(netStructure,i,pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str()) &&
      (netStructure.layer(i).pooling_param().kernel_size() == 2) &&
      (netStructure.layer(i).pooling_param().stride() == 2) &&
    (TIDL_isBottomUsedLater(netStructure.layer(i).bottom(0).c_str(),i,netStructure) == false))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.enablePooling = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.poolingType = netStructure.layer(i).pooling_param().pool();
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.kernelW   = 2;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.kernelH   = 2;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.strideW   = 2;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.strideH   = 2;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outDataNames[0],netStructure.layer(i).top(0).c_str());

    if(quantizationStyle == TIDL_quantStyleFixed)
    {
#if ENABLE_FIXED_QUANT_STYLE
		if (id != -1)
		{

			if (netStructure.layer(i).pooling_param().pool() == PoolingParameter_PoolMethod_AVE)
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.convParams.poolParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.convParams.poolParams.outDataQ = 1;
			}
			if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_UnsignedChar;
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_SignedChar;
			}
		}
#endif
    }
    else
    {
        // Keep [layerIndex-1].outData[0].elementType as it is
        // Folding pooling into previous layer should not change output type
    }
    
#if 1
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[2] /= 2; 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[3] /= 2;
#else
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[2] = 
      ceil(((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[2] + 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.padH*2.0) - 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.kernelH))/
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.strideH) + 1;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[3] = 
      ceil(((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[3] + 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.padW*2.0) - 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.kernelW))/
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.poolParams.strideW) + 1;
#endif  
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_PoolingLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType    = netStructure.layer(i).pooling_param().pool();
    
    if(netStructure.layer(i).pooling_param().global_pooling() == true)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW = 0;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH = 0;
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW        = netStructure.layer(i).pooling_param().kernel_size();
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH        = netStructure.layer(i).pooling_param().kernel_size();
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideW        = netStructure.layer(i).pooling_param().stride();
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideH        = netStructure.layer(i).pooling_param().stride();
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padW           = netStructure.layer(i).pooling_param().pad();
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padH           = netStructure.layer(i).pooling_param().pad();
    }
#if 0
    if(netStructure.layer(i).pooling_param().kernel_size() > netStructure.layer(i).pooling_param().stride())
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padW  = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW -1)/2;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padH  = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH -1)/2;
    }
#endif

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    if(netStructure.layer(i).pooling_param().global_pooling() == true)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]  = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2]  = 1;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]  = 1;
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]  = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = ceil(((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] + 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padH*2.0) - 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH))/
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideH) + 1;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = ceil(((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3] + 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padW*2.0) - 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW))/
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideW) + 1;
    }
     pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.numChannels =  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    if(quantizationStyle == TIDL_quantStyleFixed)
    {
#if ENABLE_FIXED_QUANT_STYLE
		if (id != -1)
		{
			if (netStructure.layer(i).pooling_param().pool() == PoolingParameter_PoolMethod_AVE)
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.inDataQ = netParams.layer(id).quantization_param().qparam_in(0).fracbits();
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.inDataQ = 1;
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.outDataQ = 1;
			}
			if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_UnsignedChar;
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar;
			}
		}
#endif
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = pOrgTIDLNetStructure->  TIDLPCLayers[layerIndex].inData[0].elementType;      
    }


    if(netStructure.layer(i).pooling_param().global_pooling() == false)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]*
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW * 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH ;
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]*
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
   }

    layerIndex++;
  }
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;
}

void TIDL_foldBNToConv2D(
float    * conv2weights,
float    * conv2dBias,
uint32_t  kernerlSize,
uint32_t  numCh,
float * mean,
float * var,
float * scale,
float * bias,
float eps
)
{
  kernerlSize /= numCh;
  uint32_t i, j;
  for(j = 0; j < numCh; j++)
  {
      float cb = conv2dBias[j];
      float m = mean[j];
      float v = var[j];
      float s = scale[j];
      float b = bias[j];
      double inv_var = pow((eps + v),-0.5);
      for(i = 0; i < kernerlSize; i++)
      {
        float w = conv2weights[j*kernerlSize + i];
        conv2weights[j*kernerlSize + i] = (w*s)*inv_var;
      }
      conv2dBias[j] = (((cb-m)*s)*inv_var) + b; 
  }
}

void TIDL_importPRelUParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
int32_t              *pDataIndex,
NetParameter         netStructure,
NetParameter         netParams)
{
  int32_t     status;
  int32_t     layerIndex;
  int32_t     dataIndex;
  int32_t     channel_shared;
  int32_t     paramSet = 0;
  int32_t     dataSize;
   int32_t    id;

  layerIndex = *pLayerIndex;
  dataIndex  = *pDataIndex;
  if(TIDL_isInputBatchNorm(pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).top(0).c_str()))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.enableRelU = 0;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.reluParams.reluType = TIDL_PRelU;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outDataNames[0],netStructure.layer(i).top(0).c_str());
    if(quantizationStyle == TIDL_quantStyleFixed)
    {
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].elementType = TIDL_SignedChar;
    }
        
    dataSize = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[1];
    if(dataSize != (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1]))
    {
      printf("PRelU Size not matching!!");
    }  
    else
    {
      paramSet = 1;
      float * data = (float *)malloc(dataSize*sizeof(float));

      channel_shared = netStructure.layer(i).prelu_param().channel_shared();
      id = TIDL_appCNNInteropCaffeFindLayerByName((char*)netStructure.layer(i).name().c_str(),netParams);
      for (int idx = 0; idx < dataSize; idx++) 
      {
        if(channel_shared)
        {
          data[idx] = netParams.layer(id).blobs(0).data(0);
        }
        else
        {
          data[idx] = netParams.layer(id).blobs(0).data(idx);                
        } 
      }
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.reluParams.slope.ptr,data);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.reluParams.slope.bufSize = dataSize;
    }
    if(paramSet == 0)
    {
      dataSize = 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1]);
      printf("Setting RAND SLOPE Params for Layer %s \n", 
      (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].name);
      float  * data   = (float *)malloc(dataSize*sizeof(float));
      for (int idx = 0; idx < dataSize; idx++) {
        uint16_t val = (rand() & (0X7FFF));
        data[idx] = ((float)((rand()&1) ? val : -val))/256;      
      }      
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.reluParams.slope.ptr,data);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.reluParams.slope.bufSize = dataSize;
    }  
  }
  else
  {
    id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
    if(id == -1)
    {
      printf("Could not find %s Params\n",(char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
    }    

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_BatchNormLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.enableRelU = 0;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.reluType = TIDL_PRelU;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }   
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType  = TIDL_SignedChar;    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

    uint32_t j, dataSize = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    float       eps = 0;
    float * mean  = (float*)malloc(dataSize*sizeof(float));
    float * var   = (float*)malloc(dataSize*sizeof(float));
    float * scale = (float*)malloc(dataSize*sizeof(float));
    float * bias  = (float*)malloc(dataSize*sizeof(float));   

     for(j = 0; j < dataSize; j++)
     {
       mean[j]  = 0;
       var[j]   = 1;
       scale[j] = 1;
       bias[j]  = 0;
     }    
     
    
    if(dataSize != pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1])
    {
      printf("Un-suported data size for BN\n");
    }
    else
    {
       float * dataBias    = (float*) malloc(dataSize*sizeof(float));
       float * dataWeigths = (float*) malloc(dataSize*sizeof(float));
       for(j = 0; j < dataSize; j++)
       {
         dataBias[j]  = 0;
         dataWeigths[j]  =  1;
       }
       STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.ptr,dataBias);
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.bufSize = dataSize;
       STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.ptr,dataWeigths);
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.bufSize = dataSize;
       
       TIDL_foldBNToConv2D(
       (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.ptr),
       (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.ptr),
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.bufSize,
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.bufSize,
       mean,var,scale,bias,eps);       
    }    

    if(dataSize != (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]))
    {
      printf("PRelU Size not matching!!");
    }  
    else
    {
      paramSet = 1;
      float * data = (float *)malloc(dataSize*sizeof(float));
      channel_shared = netStructure.layer(i).prelu_param().channel_shared();
      id = TIDL_appCNNInteropCaffeFindLayerByName((char*)netStructure.layer(i).name().c_str(),netParams);
      for (int idx = 0; idx < dataSize; idx++) 
      {
        if(channel_shared)
        {
          data[idx] = netParams.layer(id).blobs(0).data(0);
        }
        else
        {
          data[idx] = netParams.layer(id).blobs(0).data(idx);                
        } 
      }
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.slope.ptr,data);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.slope.bufSize = dataSize;
    }
    if(paramSet == 0)
    {
      dataSize = 
      (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]);
      printf("Setting RAND SLOPE Params for Layer %s \n", 
      (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
      float  * data   = (float *)malloc(dataSize*sizeof(float));
      for (int idx = 0; idx < dataSize; idx++) {
        uint16_t val = (rand() & (0X7FFF));
        data[idx] = ((float)((rand()&1) ? val : -val))/256;      
      }      
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.slope.ptr,data);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.slope.bufSize = dataSize;
    }     
    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]; 
    layerIndex++;

  }
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;
}


void TIDL_importRelUParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
int32_t              *pDataIndex,
NetParameter         netStructure,
NetParameter         netParams)
{
  int32_t     status;
  int32_t     layerIndex;
  int32_t     dataIndex;
   int32_t    id;
   
  layerIndex = *pLayerIndex;
  dataIndex  = *pDataIndex;
  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, netParams);
  if (id == -1)
  {
	  printf("Could not find %s Params\n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
  }
  if(TIDL_isInputConv2DCaffe(netStructure,i,pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str()))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.enableRelU = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outDataNames[0],netStructure.layer(i).top(0).c_str());
    if(quantizationStyle == TIDL_quantStyleFixed)
    {
#if ENABLE_FIXED_QUANT_STYLE
		if (id != -1)
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.convParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
			if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_UnsignedChar;
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_SignedChar;
			}
		}
#endif
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].elementType = TIDL_UnsignedChar;
    }
      
  }
  else if(TIDL_isInputEltWise( pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).top(0).c_str()))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.eltWiseParams.enableRelU = 1;
    if(quantizationStyle == TIDL_quantStyleFixed)
    {
#if ENABLE_FIXED_QUANT_STYLE
		if (id != -1)
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.eltWiseParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
			if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_UnsignedChar;
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_SignedChar;
			}
		}
#endif
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].elementType = TIDL_UnsignedChar;
    }
  } 
  else if(TIDL_isInputInnreProduct( pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).top(0).c_str()))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.innerProductParams.enableRelU = 1;
    if(quantizationStyle == TIDL_quantStyleFixed)
    {
#if ENABLE_FIXED_QUANT_STYLE
		if (id != -1)
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.innerProductParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
			if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_UnsignedChar;
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_SignedChar;
			}
		}
#endif
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].elementType = TIDL_UnsignedChar;
    }
  }
  else if(TIDL_isInputBatchNorm(pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).top(0).c_str()))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.enableRelU = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.batchNormParams.reluParams.reluType = TIDL_RelU;
    if(quantizationStyle == TIDL_quantStyleFixed)
    {
#if ENABLE_FIXED_QUANT_STYLE
		if (id != -1)
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.batchNormParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();

			if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_UnsignedChar;
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType = TIDL_SignedChar;
			}
		}
#endif
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].elementType = TIDL_UnsignedChar;
    }
  }
  else
  {
   
    uint32_t j, dataSize;
    float       eps = 0;
     
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_BatchNormLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.enableRelU = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.reluType = TIDL_RelU;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }   
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType  = TIDL_UnsignedChar;    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

    dataSize = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    {
      float * dataBias    = (float*) malloc(dataSize*sizeof(float));
      float * dataWeigths = (float*) malloc(dataSize*sizeof(float));
      float * mean  = (float*)malloc(dataSize*sizeof(float));
      float * var   = (float*)malloc(dataSize*sizeof(float));
      float * scale = (float*)malloc(dataSize*sizeof(float));
      float * bias  = (float*)malloc(dataSize*sizeof(float));     
      for(j = 0; j < dataSize; j++)
      {
        dataBias[j]  = 0;
        dataWeigths[j]  =  1;
        mean[j]  = 0;
        var[j]   = 1;
        scale[j] = 1;
        bias[j]  = 0;
      }
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.ptr,dataBias);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.bufSize = dataSize;
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.ptr,dataWeigths);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.bufSize = dataSize;
         
      TIDL_foldBNToConv2D(
      (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.ptr),
      (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.ptr),
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.bufSize,
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.bufSize,
      mean,var,scale,bias,eps);       
    }        
    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]; 
    layerIndex++;
  }
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;
}

void TIDL_importDropoutParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
NetParameter         netStructure)
{
  int32_t     status;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_DropOutLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0];
}

void TIDL_importSoftmaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure,
NetParameter          netParams)
{
  int32_t     id, status;
  int         prevLayerIdx = 0;
  int32_t     layerIndex = *pLayerIndex; 
  int32_t     dataIndex  = *pDataIndex;
  
  if((ssdNet) && (TIDL_isInputReshape( pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str())))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerType =  TIDL_SoftMaxLayer;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].numInBufs  = 1;
    //strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[1];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[3];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[3]; 
  }  
  else
  { 
  if(netStructure.layer(i).softmax_param().axis()== 2)
  {
    printf("\n SoftMax is not suported with axis = 2");
  }
  else{
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_SoftMaxLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);

  prevLayerIdx = TIDL_inputLayerIndex(pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str());
  
  if(quantizationStyle == TIDL_quantStyleFixed)
  {
#if ENABLE_FIXED_QUANT_STYLE
    id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].name,netParams);

    
    if(id != -1)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.softMaxParams.inDataQ  = netParams.layer(id).quantization_param().qparam_in(0).fracbits();
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.softMaxParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.softMaxParams.inDataQ  = 5;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.softMaxParams.outDataQ = 5;
    }
#endif
  }

  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];
  layerIndex++;
  }
  }
  
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;  
}

void TIDL_importDeconvParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
FILE                 *fp1,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
NetParameter         netStructure,
NetParameter         netParams)
{
  int32_t             status, id;
  int32_t             pad, stride;
  int32_t             paramSet = 0;
  int32_t             dataSize;
  int32_t             conv2DRandParams = 0;
  float min, max;
 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_Deconv2DLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  if((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1] == netStructure.layer(i).convolution_param().group()) &&
  (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1] == netStructure.layer(i).convolution_param().num_output()))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numInChannels  = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numOutChannels = netStructure.layer(i).convolution_param().num_output();
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups      = netStructure.layer(i).convolution_param().group();   
  }
  else
  {
    printf("\n TIDL limitation : For Deconvolution layer, number of groups should match with number of input and output channels \n");
    exit(-1);
  }    
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW        = netStructure.layer(i).convolution_param().kernel_size(0);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH        = netStructure.layer(i).convolution_param().kernel_size(0);

  if (netStructure.layer(i).convolution_param().pad_size() == 0) {
    pad = 0;
  }
  else {
    pad = netStructure.layer(i).convolution_param().pad(0);
  }
  if (netStructure.layer(i).convolution_param().stride_size() == 0) {
    stride = 1;
  }
  else {
    stride = netStructure.layer(i).convolution_param().stride(0);
  }

  if (netStructure.layer(i).convolution_param().dilation_size() == 0) {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH = 1;
  }
  else {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH =
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW = netStructure.layer(i).convolution_param().dilation(0);
  }
  if(stride == 2) /* Only supported stride value is 2 */
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideW        = stride;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH        = stride;
  }  
  else
  {
    printf("\n TIDL limitation : For Deconvolution layer, only supported stride value is 2 \n");
    exit(-1);
  }    
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padW           = pad;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padH           = pad;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numOutChannels;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] - 1) * 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH + 
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH-1)*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH + 1) - 
  (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padH*2));
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3] - 1) * 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideW + 
  ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW-1)*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW + 1) - 
  (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padW*2));

  if(quantizationStyle == TIDL_quantStyleFixed)
  {
#if ENABLE_FIXED_QUANT_STYLE
	  if (id != -1)
	  {
		  if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
		  {
			  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_UnsignedChar;
		  }
		  else
		  {
			  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar;
		  }

		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.inDataQ = netParams.layer(id).quantization_param().qparam_in(0).fracbits();
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weightsQ = netParams.layer(id).quantization_param().qparam_w().fracbits();
	  }
#endif
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar;
  }

  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
  paramSet = 0;
  if(id != -1)
  {
    if(netParams.layer(id).blobs_size() > 0)
    {
      dataSize = netParams.layer(id).blobs(0).data_size();
      if(dataSize != ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
              pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW * 
              pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH * 
              pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1])/
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups))
      {
        printf("Kernel Size not matching!!");
      }
      else
      {
        paramSet = 1;
        float  * data   = (float *)malloc(dataSize*sizeof(float));
        for (int idx = 0; idx < dataSize; idx++) 
        {
          data[idx] = netParams.layer(id).blobs(0).data(idx);
        }
        STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.ptr,data);
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.bufSize = dataSize;
      }
    }
  }
  if(paramSet == 0)
  {
    printf("Setting RAND Kernel Params for Layer %s \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
    dataSize = ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW * 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH * 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1])/
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups);

    float  * data   = (float *)malloc(dataSize*sizeof(float));
    for (int idx = 0; idx < dataSize; idx++) {
      uint8_t val = (rand() & (0X7F));
      data[idx] = ((float)((rand()&1) ? val : -val))/64;
    }      
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.ptr,data);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.bufSize = dataSize;  
  }

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableBias = netStructure.layer(i).convolution_param().bias_term();

  if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableBias)
  {
    paramSet = 0;
    if(id != -1)
    {
      if(netParams.layer(id).blobs_size() > 1)
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableBias = 1;
        dataSize = netParams.layer(id).blobs(1).data_size();
        if(dataSize != (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]))
        {
          printf("Bias Size not matching!!");
        }     
        else
        {
          paramSet = 1;
          float * data = (float *)malloc(dataSize*sizeof(float));
          for (int idx = 0; idx < dataSize; idx++) 
          {
            data[idx] = netParams.layer(id).blobs(1).data(idx);
          }


          STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.ptr,data);             
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.bufSize = dataSize;
          
          
        }
      }

    }
    if(paramSet == 0)
    {
      printf("Setting RAND BIAS Params for Layer %s \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);

      dataSize = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]);
      float  * data   = (float *)malloc(dataSize*sizeof(float));
      for (int idx = 0; idx < dataSize; idx++) {
        uint8_t val = (rand() & (0X7F));
        data[idx] = ((float)((rand()&1) ? val : -val))/64;
      }      
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.ptr,data);             
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.bias.bufSize = dataSize;
    } 
  }


  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
  (int64_t)(((int64_t)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW * 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH * 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]) / pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups);
} 


void TIDL_importArgmaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               layerIndex,
int32_t               dataIndex,
NetParameter          netStructure)
{
  int32_t     status; 
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ArgMaxLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.argMaxParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_UnsignedChar;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
  (int64_t)((int64_t)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3])*2;
  
}


void TIDL_importBiasParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
FILE                 *fp1,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
NetParameter         netStructure,
NetParameter         netParams)
{
  int32_t             status, id;
  int32_t             paramSet = 0;
  int32_t             dataSize;
  int32_t             conv2DRandParams = 0;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_BiasLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];


  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
  paramSet = 0;
  if(id != -1)
  {
    if(netParams.layer(id).blobs_size() > 0)
    {
      dataSize = netParams.layer(id).blobs(0).data_size();
      if(dataSize != (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]))
      {
        printf("Bias Size not matching!!");
        paramSet = 0;
      }  
      else
      {
        paramSet = 1;
        int16_t * params = (int16_t *)malloc(dataSize*2);
        for (int idx = 0; idx < dataSize; idx++) {
          float data = netParams.layer(id).blobs(0).data(idx);
          params[idx] = data * (1 << (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.biasQ));
        }
        fwrite(params,2,dataSize,fp1);
        free(params);
      }
    }
  }
  if(paramSet == 0)
  {
    printf("Setting RAND BIAS Params for Layer %s \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
    dataSize = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]);
    int16_t * params = (int16_t *)malloc(dataSize*2);
    for (int idx = 0; idx < dataSize; idx++) {
      uint16_t val = (rand() & (0X7FFF));
      //params[idx] = (rand()&1) ? val : -val;
      params[idx] = -128;
    }
    fwrite(params,2,dataSize,fp1);
    free(params);
  } 

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
  (int64_t)((int64_t)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3]);
  
} 


void TIDL_importEltwiseParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               layerIndex,
int32_t               dataIndex,
NetParameter          netStructure,
NetParameter          netParams)
{
  int32_t     status; 
  int32_t id = TIDL_appCNNInteropCaffeFindLayerByName(
	  (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, netParams);
  if (id == -1)
  {
	  printf("Could not find %s in Model file \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
  }

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_EltWiseLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = netStructure.layer(i).bottom_size();
  for (int32_t j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++) 
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j],netStructure.layer(i).bottom(j).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.eltWiseParams.eltWiseType        = netStructure.layer(i).eltwise_param().operation();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.eltWiseParams.numInData          = netStructure.layer(i).bottom_size();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar; 
  if(quantizationStyle == TIDL_quantStyleFixed)
  {
#if ENABLE_FIXED_QUANT_STYLE
	  if (id != -1)
	  {
		  if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
		  {
			  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_UnsignedChar;
		  }
		  else
		  {
			  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar;
		  }
		  for (int32_t j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.eltWiseParams.numInData; j++)
		  {
			  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.eltWiseParams.inDataQ[j] = netParams.layer(id).quantization_param().qparam_in(j).fracbits();
		  }

		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.eltWiseParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
	  }
#endif
  }
  
  if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.eltWiseParams.numInData > 2)
  {
    printf("\n TIDL limitation : Eltwise layer, only supported for two inputs \n");
    exit(-1);        
  }
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.eltWiseParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];
  
}

  
void TIDL_foldScaleToConv2D(
float    * conv2weights,
float    * conv2dBias,
uint32_t  kernerlSize,
uint32_t  numCh,
float * scale,
float * bias
)
{
  kernerlSize /= numCh;
  uint32_t i, j;
  for(j = 0; j < numCh; j++)
  {
      float cb = conv2dBias[j];
      float s = scale[j];
      float b = bias[j];
      for(i = 0; i < kernerlSize; i++)
      {
        float w = conv2weights[j*kernerlSize + i];
        conv2weights[j*kernerlSize + i] = (w*s);
      }
      conv2dBias[j] = (cb*s) + b; 
  }
}
void TIDL_importScaleParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure,
NetParameter         netParams)
{
  int32_t     status; 
  int32_t id;
  int32_t layerIndex = *pLayerIndex;
  int32_t dataIndex  = *pDataIndex;
  int32_t j;

 
  
  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
  if(id == -1)
  {
    printf("Could not find %s Params\n",(char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
    exit(0);
  }
  uint32_t dataSize = netParams.layer(id).blobs(0).data_size();

  float * scale = (float*)malloc(dataSize*sizeof(float));
  float * bias  = (float*)malloc(dataSize*sizeof(float));
  if(netParams.layer(id).blobs_size() == 2)
  {
       for(j = 0; j < dataSize; j++)
       {
         scale[j]  = netParams.layer(id).blobs(0).data(j);
         bias[j]   = netParams.layer(id).blobs(1).data(j);
       }
  }
  else
  {
    printf("Un-suported number of blobs for Scale\n");
  }

  if(TIDL_isInputConv2DCaffe(netStructure,i,pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str()))
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outDataNames[0],netStructure.layer(i).top(0).c_str());
    if(dataSize != pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1])
    {
      printf("Un-suported data size for Scale\n");
    }
    if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.enableBias == 0)
    {
       float * data = (float*) malloc(dataSize*sizeof(float));
       for(j = 0; j < dataSize; j++)
       {
         data[j]  = 0;
       }
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.enableBias = 1;
     }
     
     TIDL_foldScaleToConv2D(
     (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.weights.ptr),
     (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.bias.ptr),
     pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.weights.bufSize,
     dataSize,
     scale,bias);
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ScaleLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }   
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]; 
    layerIndex++;
  }
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;

  
} 

void TIDL_importPriorBoxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure,
NetParameter         netParams)
{
  int32_t     status; 
  int32_t id;
  int32_t layerIndex = *pLayerIndex;
  int32_t dataIndex  = *pDataIndex;
  int32_t j, img_height, img_width, num_priors;
  int32_t layer_height, layer_width;
  float step_h, step_w;
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType    =  TIDL_PriorBoxLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs   =   1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0], netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs    =   1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  
  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
  if(id == -1)
  {
    printf("Could not find %s Params\n",(char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
  }
  
  int32_t aspect_ratios_size = netStructure.layer(i).prior_box_param().aspect_ratio_size();
  float  * aspect_ratios   = (float *)malloc((aspect_ratios_size*3)*sizeof(float));
  bool flip = netStructure.layer(i).prior_box_param().flip();
  int ptr_offset = 0;
  aspect_ratios[ptr_offset++] = 1.0;
  for (int idx = 0; idx < aspect_ratios_size; idx++) 
  {
   float ar = netStructure.layer(i).prior_box_param().aspect_ratio(idx);
     bool already_exist = false;
     for (int j = 0; j < ptr_offset; ++j) 
   {
       if (fabs(ar - aspect_ratios[j]) < 1e-6) 
     {
         already_exist = true;
         break;
       }
     }
     if (!already_exist) 
   {
       aspect_ratios[ptr_offset++] = ar;
       if (flip) 
     {
         aspect_ratios[ptr_offset++] = (1./ar);
       }
     }
  }    
  aspect_ratios_size = ptr_offset;
  
  int32_t min_sizes_size = netStructure.layer(i).prior_box_param().min_size_size();
  float  * min_sizes   = (float *)malloc(min_sizes_size*sizeof(float));
  for (int idx = 0; idx < min_sizes_size; idx++) 
  {
     min_sizes[idx] = netStructure.layer(i).prior_box_param().min_size(idx);
  }  

  int32_t max_sizes_size = netStructure.layer(i).prior_box_param().max_size_size();
  float  * max_sizes   = (float *)malloc(max_sizes_size*sizeof(float));
  num_priors = aspect_ratios_size * min_sizes_size;
  for (int idx = 0; idx < max_sizes_size; idx++) 
  {
     max_sizes[idx] = netStructure.layer(i).prior_box_param().max_size(idx);
   num_priors += 1;
  }
  float offset = netStructure.layer(i).prior_box_param().offset();
  bool  clip = netStructure.layer(i).prior_box_param().clip();  

  /* First input points to Conv layer output data */  
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0], netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  layer_height = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];   
  layer_width  = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
  
  if (netStructure.layer(i).prior_box_param().has_img_h() || netStructure.layer(i).prior_box_param().has_img_w()) 
  {
    img_height = netStructure.layer(i).prior_box_param().img_h();
    img_width = netStructure.layer(i).prior_box_param().img_w();
  } 
  else if (netStructure.layer(i).prior_box_param().has_img_size()) 
  {
    int32_t img_size = netStructure.layer(i).prior_box_param().img_size();
    img_height = img_size;
    img_width = img_size;
  } 
  else 
  {
  /* Second input points to input data */  
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[1], netStructure.layer(i).bottom(1).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[1], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[1]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }
    img_height = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[1].dimValues[2];   
    img_width  = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[1].dimValues[3];
  }

  if (netStructure.layer(i).prior_box_param().has_step_h() || netStructure.layer(i).prior_box_param().has_step_w()) 
  {
    step_h = netStructure.layer(i).prior_box_param().step_h();
    step_w = netStructure.layer(i).prior_box_param().step_w();
  } 
  else if (netStructure.layer(i).prior_box_param().has_step()) 
  {
    float step = netStructure.layer(i).prior_box_param().step();
    step_h = step;
    step_w = step;
  }
  else // Step Not found in the net structure decoding from base size
  {
    step_h = ((float)img_height)/layer_height;
    step_w = ((float)img_width)/layer_width;
  }

  int32_t variance_size = netStructure.layer(i).prior_box_param().variance_size();
  float  * variance   = (float *)malloc((variance_size+1)*sizeof(float));
  if(variance_size)
  {
    for (int idx = 0; idx < variance_size; idx++) 
    {
       variance[idx] = netStructure.layer(i).prior_box_param().variance(idx);
    }
  }
  else
  {
    // Set default to 0.1.
  variance_size = 1;
    variance[0] = 0.1;    
  }
    
  int dim = 12 + (num_priors * 2);
  float *top_data   = (float *)malloc(dim*sizeof(float));
  // set the variance.
  int indx = 0;
  top_data[indx++] = num_priors; 
  top_data[indx++] = layer_width; 
  top_data[indx++] = layer_height; 
  top_data[indx++] = img_width; 
  top_data[indx++] = img_height; 
  top_data[indx++] = step_w; 
  top_data[indx++] = step_h; 
  top_data[indx++] = offset; 
  for (int j = 0; j < 4; ++j) 
  {
    if (variance_size == 1) 
    {
          top_data[indx++] = variance[0];         
    }
    else
    {
          top_data[indx++] = variance[j];        
    }
  }  
  //int indx = 4;
  //for (int h = 0; h < layer_height; ++h) 
  {
  //  for (int w = 0; w < layer_width; ++w) 
  {
      //float center_x = (w + offset) * step_w;
      //float center_y = (h + offset) * step_h;
      float box_width, box_height;
    for (int s = 0; s < min_sizes_size; ++s) 
    {
        int min_size = min_sizes[s];
        // first prior: aspect_ratio = 1, size = min_size
        box_width = box_height = min_size;
        // xmin
        top_data[indx++] = box_width; //(center_x - box_width / 2.) / img_width;
        // ymin
        top_data[indx++] = box_height; //(center_y - box_height / 2.) / img_height;
        // xmax
        //top_data[indx++] = (center_x + box_width / 2.) / img_width;
        // ymax
        //top_data[indx++] = (center_y + box_height / 2.) / img_height;

        if (max_sizes_size > 0) 
        {
          //CHECK_EQ(min_sizes_.size(), max_sizes_.size());
          int max_size = max_sizes[s];
          float size  = min_size * max_size;
          // second prior: aspect_ratio = 1, size = sqrt(min_size * max_size)
          box_width = box_height = sqrt(size);
          // xmin
          top_data[indx++] = box_width ; //(center_x - box_width / 2.) / img_width;
          // ymin
          top_data[indx++] = box_height ; //(center_y - box_height / 2.) / img_height;
          // xmax
          //top_data[indx++] = (center_x + box_width / 2.) / img_width;
          // ymax
          //top_data[indx++] = (center_y + box_height / 2.) / img_height;
        }

        // rest of priors
        for (int r = 0; r < aspect_ratios_size; ++r) 
        {
          float ar = aspect_ratios[r];
          if (fabs(ar - 1.) < 1e-6) 
          {
            continue;
          }
          box_width = min_size * sqrt(ar); 
          box_height = min_size / sqrt(ar);
          // xmin
          top_data[indx++] = box_width; //(center_x - box_width / 2.) / img_width;
          // ymin
          top_data[indx++] = box_height; //(center_y - box_height / 2.) / img_height;
          // xmax
          //top_data[indx++] = (center_x + box_width / 2.) / img_width;
          // ymax
          //top_data[indx++] = (center_y + box_height / 2.) / img_height;

        }
      }
    }
  }

  STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBox.ptr,top_data);
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBox.bufSize = indx; 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBoxSize = indx; 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 4*indx;  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;  
  layerIndex++;
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;
}
  
void TIDL_importDetectionOutputParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure,
NetParameter          netParams)
{
  int32_t  status; 
  int32_t  id, prevLayerIdx;
  int32_t  layerIndex = *pLayerIndex;
  int32_t  dataIndex  = *pDataIndex;
  int32_t  j, num_classes, num_priors;
  int32_t  num_loc_classes;
  int32_t  background_label_id;
  int32_t  code_type;
  float    confidence_threshold;
  float    nms_threshold, eta;
  int32_t  top_k, keep_top_k;
  bool     share_location, clip_bbox;
  bool     variance_encoded_in_target;  
  
  if((ssdNet) && (TIDL_isInputFlatten( pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str())))
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inDataNames[1],netStructure.layer(i).bottom(1).c_str());
    layerIndex--;
    dataIndex--;
  }
  else if((ssdNet) && (TIDL_isInputFlatten( pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(1).c_str())))
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inDataNames[1],(char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inDataNames[0]);
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    layerIndex--;
    dataIndex--;
  }    
  else
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],
    netStructure.layer(i).bottom(0).c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[1],
    netStructure.layer(i).bottom(1).c_str());    
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType    =  TIDL_DetectionOutputLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs   =   1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0], netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs      = 
  netStructure.layer(i).bottom_size(); 
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, netStructure.layer(i).name().c_str());   
  /* Don't read prior box layer input and data from prototext */
  /* Assuming min  3 inputs loc, conf and prior box. And reading only first 2 here*/
  if (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs < 2)
  {
    printf("Minimum three inputs expected for  DetectionOutput layer \n Exiting !!!!");
    exit(-1);
  }
  else
  {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs = 2;
  }

  for(j = 0; j < 2; j++) 
  {
    //strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j],
    //netStructure.layer(i).bottom(j).c_str());
    status = TIDL_getDataID(
    &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j], 
    pOrgTIDLNetStructure,
    layerIndex, 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
      exit(-1);
    }
  }
  
  prevLayerIdx = TIDL_inputLayerIndex(pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(2).c_str());
  if(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerType == TIDL_PriorBoxLayer)
  {
      float * data      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.ptr);
      uint32_t k, dataSize = pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.bufSize;
      float *top_data   = (float *)malloc(dataSize*sizeof(float));
      for(k = 0; k < dataSize; k++)
      {
        top_data[k] = data[k]; 
      }
      free(data);        
      RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.ptr);
      pOrgTIDLNetStructure->TIDLPCLayers[prevLayerIdx].layerParams.detectOutParams.priorBox.bufSize = 0;        
    
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBox.ptr,top_data);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.priorBox.bufSize = dataSize;    
  }
    
  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
  if(id == -1)
  {
    printf("Could not find %s Params\n",(char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
  }
  
  num_classes = netStructure.layer(i).detection_output_param().num_classes();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.numClasses = num_classes;
  
  share_location = netStructure.layer(i).detection_output_param().share_location();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.shareLocation = share_location;
  
  background_label_id = netStructure.layer(i).detection_output_param().background_label_id();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.backgroundLabelId = background_label_id;
  
  code_type = netStructure.layer(i).detection_output_param().code_type();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.codeType = code_type;

  variance_encoded_in_target =
      netStructure.layer(i).detection_output_param().variance_encoded_in_target();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.varianceEncoded = variance_encoded_in_target;

  keep_top_k = netStructure.layer(i).detection_output_param().keep_top_k();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.keepTopK = keep_top_k;

  confidence_threshold = netStructure.layer(i).detection_output_param().has_confidence_threshold() ?
      netStructure.layer(i).detection_output_param().confidence_threshold() : -FLT_MAX;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.confThreshold = confidence_threshold;

  // Parameters used in nms.
  nms_threshold = netStructure.layer(i).detection_output_param().nms_param().nms_threshold();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.nmsThreshold = nms_threshold;

  eta = netStructure.layer(i).detection_output_param().nms_param().eta();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.eta = eta;

  top_k = -1;
  if (netStructure.layer(i).detection_output_param().nms_param().has_top_k()) 
  {
    top_k = netStructure.layer(i).detection_output_param().nms_param().top_k();
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.detectOutParams.topK = top_k;
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = keep_top_k*7*4; // 7 float values for each detecetd box
  // Need to update numMacs after discussion with Kumar  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;  
  
  layerIndex++;
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;
}

void TIDL_importBatchNormParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure,
NetParameter         netParams,
int32_t              layerType)
{
  int32_t     status; 
  int32_t id;
  int32_t layerIndex = *pLayerIndex;
  int32_t dataIndex  = *pDataIndex;
  int32_t j;
  float eps = 0;
  uint32_t dataSize;
  
  
  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,netParams);
  if(id == -1)
  {
    printf("Could not find %s Params\n",(char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
    dataSize = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1];
  }
  else
  { 
    dataSize = netParams.layer(id).blobs(0).data_size();
  }

  float * mean  = (float*)malloc(dataSize*sizeof(float));
  float * var   = (float*)malloc(dataSize*sizeof(float));
  float * scale = (float*)malloc(dataSize*sizeof(float));
  float * bias  = (float*)malloc(dataSize*sizeof(float));
  if(id == -1)
  {
       for(j = 0; j < dataSize; j++)
       {
         mean[j]  = 0;
         var[j]   = 1;
         scale[j] = 1;
         bias[j]  = 0;
       }
  }
  else
  {
    if(layerType == 0)
    {
      eps = netParams.layer(id).batch_norm_param().eps();
      if(netParams.layer(id).blobs_size() == 5)
      {
        
        // old format: 0 - scale , 1 - bias,  2 - mean , 3 - var, 4 - reserved
        // new format: 0 - mean  , 1 - var,  2 - reserved , 3- scale, 4 - bias
        if(netParams.layer(id).blobs(4).data_size() == 1)
        {
           for(j = 0; j < dataSize; j++)
           {
             mean[j]  = netParams.layer(id).blobs(2).data(j);
             var[j]   = netParams.layer(id).blobs(3).data(j);
             scale[j] = netParams.layer(id).blobs(0).data(j);
             bias[j]  = netParams.layer(id).blobs(1).data(j);
           }
        }
        else
        {
           for(j = 0; j < dataSize; j++)
           {
             mean[j]  = netParams.layer(id).blobs(0).data(j);
             var[j]   = netParams.layer(id).blobs(1).data(j);
             scale[j] = netParams.layer(id).blobs(3).data(j);
             bias[j]  = netParams.layer(id).blobs(4).data(j);
           }
        }
      }
      else if(netParams.layer(id).blobs_size() == 3)
      {
           for(j = 0; j < dataSize; j++)
           {
             mean[j]  = netParams.layer(id).blobs(0).data(j);
             var[j]   = netParams.layer(id).blobs(1).data(j);
             scale[j] = 1;
             bias[j]  = 0;
           }
      }
      else
      {
        printf("Un-suported number of blobs for BN\n");
      }
    }
    else if(layerType == 1)
    {
         for(j = 0; j < dataSize; j++)
         {
           mean[j]  = 0;
           var[j]   = 1;
           scale[j] = 1;
           bias[j]  = netParams.layer(id).blobs(0).data(j);
         }
    }
    else if(layerType == 2)
    {
         for(j = 0; j < dataSize; j++)
         {
           mean[j]  = 0;
           var[j]   = 1;
           scale[j] = netParams.layer(id).blobs(0).data(j);
           if(netParams.layer(id).blobs_size() == 2)
           {
             bias[j]  = netParams.layer(id).blobs(1).data(j);
           }
           else
           {
             bias[j]  = 0;
           }
         }
    }
  }

  
  if((gParams.foldBnInConv2D == 1) && (TIDL_isInputConv2DCaffe(netStructure,i,pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str())))
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outDataNames[0],netStructure.layer(i).top(0).c_str());
    if(id == -1)
    {
      dataSize = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1];
    }
    if(dataSize != pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1])
    {
      printf("Un-suported data size for BN\n");
    }
    if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.enableBias == 0)
    {
       float * data = (float*) malloc(dataSize*sizeof(float));
       for(j = 0; j < dataSize; j++)
       {
         data[j]  = 0;
       }
       STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.bias.ptr,data);
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.bias.bufSize = dataSize;
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.enableBias = 1;
     }
     pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.reluParams.reluType = TIDL_RelU;
     TIDL_foldBNToConv2D(
     (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.weights.ptr),
     (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.bias.ptr),
     pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerParams.convParams.weights.bufSize,
     dataSize,
     mean,var,scale,bias,eps);
	 
	 if (quantizationStyle == TIDL_quantStyleFixed)
	 {
#if ENABLE_FIXED_QUANT_STYLE
		 if (id != -1)
		 {
			 if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			 {
				 pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType =
					 TIDL_UnsignedChar;
			 }
			 else
			 {
				 pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].outData[0].elementType =
					 TIDL_SignedChar;
			 }
			 pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.convParams.outDataQ =
				 netParams.layer(id).quantization_param().qparam_out().fracbits();
			 pOrgTIDLNetStructure->TIDLPCLayers[layerIndex - 1].layerParams.convParams.weightsQ +=
				 netParams.layer(id).quantization_param().qparam_w().fracbits();
		 }
#endif
	 }
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_BatchNormLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }   
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.reluType = TIDL_RelU;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType  = TIDL_SignedChar;    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

    if(id == -1)
    {
      dataSize = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1];
    }
    if(dataSize != pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1])
    {
      printf("Un-suported data size for BN\n");
    }
    else
    {
       float * dataBias    = (float*) malloc(dataSize*sizeof(float));
       float * dataWeigths = (float*) malloc(dataSize*sizeof(float));
       for(j = 0; j < dataSize; j++)
       {
         dataBias[j]  = 0;
         dataWeigths[j]  =  1;
       }
       STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.ptr,dataBias);
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.bufSize = dataSize;
       STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.ptr,dataWeigths);
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.bufSize = dataSize;
       
       TIDL_foldBNToConv2D(
       (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.ptr),
       (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.ptr),
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.bufSize,
       pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.bufSize,
       mean,var,scale,bias,eps);       
    }    

	
	if (quantizationStyle == TIDL_quantStyleFixed)
	{
		if ((id != -1) && netParams.layer(id).has_quantization_param())
		{
#if ENABLE_FIXED_QUANT_STYLE
			if (netParams.layer(id).quantization_param().qparam_out().unsigned_data())
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType =
					TIDL_UnsignedChar;
			}
			else
			{
				pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType =
					TIDL_SignedChar;
			}
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.inDataQ =
				netParams.layer(id).quantization_param().qparam_in(0).fracbits();
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.outDataQ =
				netParams.layer(id).quantization_param().qparam_out().fracbits();
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weightsQ +=
				netParams.layer(id).quantization_param().qparam_w().fracbits();
		}
		else
		{
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.inDataQ  = 0;
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.outDataQ = 0;
			pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weightsQ = 0;
		}
#endif
	}
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]; 
    layerIndex++;
  }
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;
} 


void TIDL_importInnerProductParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
FILE                 *fp1,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
NetParameter         netStructure,
NetParameter         netParams)
{
  int32_t             status, id;
  int32_t             paramSet = 0;
  int32_t             dataSize;
  float min, max;
  id = TIDL_appCNNInteropCaffeFindLayerByName((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name, netParams);

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_InnerProductLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType  = TIDL_SignedChar;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = netStructure.layer(i).inner_product_param().num_output();

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.numInNodes = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.numOutNodes = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];

  if(quantizationStyle == TIDL_quantStyleFixed)
  {
 #if ENABLE_FIXED_QUANT_STYLE
	  if (id != -1)
	  {
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.inDataQ = netParams.layer(id).quantization_param().qparam_in(0).fracbits();
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.outDataQ = netParams.layer(id).quantization_param().qparam_out().fracbits();
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.weightsQ = netParams.layer(id).quantization_param().qparam_w().fracbits();
	  }
#endif
  }


  paramSet = 0;
  if(id != -1)
  {
    if(netParams.layer(id).blobs_size() > 0)
    {
      dataSize = netParams.layer(id).blobs(0).data_size();       
      {
        paramSet = 1;
        float  * data   = (float *)malloc(dataSize*sizeof(float));
        for (int idx = 0; idx < dataSize; idx++) 
        {
          data[idx] = netParams.layer(id).blobs(0).data(idx);
        }

        STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.weights.ptr,data);
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.weights.bufSize = dataSize;

      }
    }
  }
  if(paramSet == 0)
  {
    printf("Setting RAND Kernel Params for Layer %s \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);
    dataSize = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.numInNodes*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.numOutNodes );

    float  * data   = (float *)malloc(dataSize*sizeof(float));
    for (int idx = 0; idx < dataSize; idx++) {
      uint8_t val = (rand() & (0X7F));
      data[idx] = ((float)((rand()&1) ? val : -val))/64;      
    }      
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.weights.ptr,data);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.weights.bufSize = dataSize;  
  }

  //pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.enableBias = 
  //netStructure.layer(i).inner_product_param().bias_term();

  if(netStructure.layer(i).inner_product_param().bias_term())
  {
    paramSet = 0;
    if(id != -1)
    {
      if(netParams.layer(id).blobs_size() > 1)
      {
        dataSize = netParams.layer(id).blobs(1).data_size();
        if(dataSize != (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]))
        {
          printf("Bias Size not matching!!");
        } 
        else        
        {
          paramSet = 1;
          float * data = (float *)malloc(dataSize*sizeof(float));
          for (int idx = 0; idx < dataSize; idx++) 
          {
            data[idx] = netParams.layer(id).blobs(1).data(idx);
          }
          STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.bias.ptr,data);
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.bias.bufSize = dataSize;
        }
      }
    }

    if(paramSet == 0)
    {
      printf("Setting RAND BIAS Params for Layer %s \n", (char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name);

      dataSize = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]);

      float  * data   = (float *)malloc(dataSize*sizeof(float));
      for (int idx = 0; idx < dataSize; idx++) {
        uint16_t val = (rand() & (0X7FFF));
        data[idx] = ((float)((rand()&1) ? val : -val))/256;      
      }      
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.bias.ptr,data);
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.bias.bufSize = dataSize;  
    }
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
} 


void TIDL_importSplitParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               layerIndex,
NetParameter          netStructure)
{
  int32_t     status; 
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_SplitLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = netStructure.layer(i).top_size();


  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }


  for (int32_t j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; j++) 
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],netStructure.layer(i).top(j).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0];
  }   
} 

void TIDL_importCopyLayerParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               layerIndex,
int32_t               *dataIndex,
NetParameter          netStructure)
{
  int32_t     status; 
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_UnSuportedLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = netStructure.layer(i).top_size();


  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }


  for (int32_t j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; j++) 
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],netStructure.layer(i).top(j).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0];

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dataId = *dataIndex;
    *dataIndex++;
  }   
}

void TIDL_importSliceParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure)
{
  int32_t     j, status; 
  int32_t numOuChs = 0;
  char numChar[10];
  int32_t     NumSlices, NumOutchannels; 
  int32_t     layerIndex = *pLayerIndex;
  int32_t     dataIndex  = *pDataIndex;
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_SliceLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = netStructure.layer(i).top_size();

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }

  if(netStructure.layer(i).slice_param().axis()!= 1)
  {
    printf("\n Unsuported slice parameters");
  }
  else
  {
    NumSlices = netStructure.layer(i).slice_param().slice_point_size(); 
    if(!NumSlices)
    {
      NumOutchannels = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1])/pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs;      
      for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; j++) 
      {
        strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],netStructure.layer(i).top(j).c_str());
        
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].numDim       = 
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
          
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[0] = 
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
          
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[2] = 
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[3] = 
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[1] = 
          NumOutchannels;  
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dataId = dataIndex++;  
      }
    }
    else
    {
      if((NumSlices+1) != pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs)
      {
        printf("\n Num slices are not matching!!");
      }
      else
      {
        NumOutchannels = 0;
        for (j = 0; j < NumSlices; j++) 
        {
          
          strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],netStructure.layer(i).top(j).c_str());
         
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].numDim       = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
            
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[0] = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
            
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[2] = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[3] = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dataId = dataIndex++;  
            
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[1] = 
          (netStructure.layer(i).slice_param().slice_point(j) - NumOutchannels);
          NumOutchannels += pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[1];          
        }
        
        //j = NumSlices;    
        {
          
          strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],netStructure.layer(i).top(j).c_str());
          
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].numDim       = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
            
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[0] = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
            
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[2] = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[3] = 
            pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dataId = dataIndex++;  
            
          pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[1] = 
          (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1] - NumOutchannels);                  
        }        
      }
    }
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;
  layerIndex++;
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;  
  
} 

void TIDL_importCropParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               layerIndex,
int32_t               dataIndex,
NetParameter          netStructure)
{
  int32_t     status; 
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_CropLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = netStructure.layer(i).bottom_size();
  for (int32_t j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++) 
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j],netStructure.layer(i).bottom(j).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[j], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }
  }
  
  if(netStructure.layer(i).crop_param().axis()!= 2)
  {
    printf("\n Unsuported crop parameters");
  }
  else
  {
    /* Fix for JIRA issue TIDL - 297 */
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.cropParams.offsetH = netStructure.layer(i).crop_param().offset(0);
    if (netStructure.layer(i).crop_param().offset_size() > 1)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.cropParams.offsetW = netStructure.layer(i).crop_param().offset(1);      
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.cropParams.offsetW = netStructure.layer(i).crop_param().offset(0);            
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.cropParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    /* Second Input has cropped output sizes */
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[1].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[1].dimValues[3];
    
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;
  
} 

void TIDL_importFlattenParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure)
{
  int32_t     status; 
  int32_t layerIndex = *pLayerIndex; 
  int32_t dataIndex  = *pDataIndex;
  
  if((ssdNet) && ((TIDL_isInputPermute( pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str())) ||
              (TIDL_isInputSoftMax( pOrgTIDLNetStructure, layerIndex, netStructure.layer(i).bottom(0).c_str()))))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].layerType =  TIDL_FlattenLayer;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].numInBufs  = 1;
    //strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].elementType  = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].elementType;     
	  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].numDim       = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].numDim;
	  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[0] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[0];
	  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[1] = 1;
	  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[2] = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].outData[0].dimValues[3] = 
	  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[1]*
	  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[2]*
	  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex-1].inData[0].dimValues[3];    
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_FlattenLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }

	  if(netStructure.layer(i).flatten_param().axis()!= 1)
	  {
	 	  printf("\n Unsuported flatten parameters");
	  }
	  else
	  {
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = 1;
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType  = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].elementType;
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 1;
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 1;
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]*
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2]*
		  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
	  }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;	
    layerIndex++;    
  }    
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;
}
void TIDL_importReshapeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               *pLayerIndex,
int32_t               *pDataIndex,
NetParameter          netStructure)
{
  int32_t     status; 
  int32_t     prevLayerIdx = 0;  
  int32_t     layerIdx = 0;
  int32_t     totDim = 0;  
  int32_t     layerIndex = *pLayerIndex;
  int32_t     dataIndex  = *pDataIndex;  
  
  layerIdx = layerIndex; 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ReshapeLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  } 
  totDim += pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[2]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[3];    
  layerIndex++;    

  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].elementType  = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].elementType;      
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].numDim       = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[0] = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[0];  
  
  
  if(netStructure.layer(i).reshape_param().shape().dim(0) == 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[1] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[1];  
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[1] = 
    netStructure.layer(i).reshape_param().shape().dim(0);        
  }
  
  if(netStructure.layer(i).reshape_param().shape().dim(1) == 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[2] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[2];  
  }
  else if(netStructure.layer(i).reshape_param().shape().dim(1) > 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[2] = 
    netStructure.layer(i).reshape_param().shape().dim(1);        
  }
  else  //if(netStructure.layer(i).reshape_param().dim(1) == -1)
  {
    if(netStructure.layer(i).reshape_param().shape().dim(2) == 0)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[3] = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[3];  
    }
    else if(netStructure.layer(i).reshape_param().shape().dim(2) > 0)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[3] = 
      netStructure.layer(i).reshape_param().shape().dim(2);        
    }
     
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[2] = 
    ((totDim)/(pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[3]));
  }      
  
  if(netStructure.layer(i).reshape_param().shape().dim(2) == 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[3] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].inData[0].dimValues[3];  
  }
  else if(netStructure.layer(i).reshape_param().shape().dim(2) > 0)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[3] = 
    netStructure.layer(i).reshape_param().shape().dim(2);        
  }
  else  //if(netStructure.layer(i).reshape_param().dim(2) == -1)
  {       
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[3] = 
    ((totDim)/(pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[2]));
  }    
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].numMacs = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[1]*
  pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIdx].outData[0].dimValues[3];
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;  
}

void TIDL_importPermuteParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t               i,
int32_t               layerIndex,
int32_t               dataIndex,
NetParameter          netStructure)
{
  int32_t     status; 
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_PermuteLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],netStructure.layer(i).top(0).c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],netStructure.layer(i).bottom(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  if(netStructure.layer(i).permute_param().order_size() == 4)
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[netStructure.layer(i).permute_param().order(0)];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[netStructure.layer(i).permute_param().order(1)];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[netStructure.layer(i).permute_param().order(2)];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[netStructure.layer(i).permute_param().order(3)];  
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 1;  
}

void TIDL_UpdateOutDataBuff(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, uint32_t numLayers, sTIDL_DataParams_t dataBuf)
{
    uint32_t i,j;
    for (i = 0; i < numLayers; i++) 
    {
        for(j = 0; (j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs) && (pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs > 0 ); j++)
        {
          if(pOrgTIDLNetStructure->TIDLPCLayers[i].outData[j].dataId == dataBuf.dataId)
          {
              pOrgTIDLNetStructure->TIDLPCLayers[i].outData[j] = dataBuf;
          }
        }

    }

    return;
}

extern sTIDL_OrgNetwork_t      orgTIDLNetStructure;
extern sTIDL_Network_t         tIDLNetStructure;
void caffe_import( tidl_import_config * params)
{
  int32_t         i, j, layerNum;
  int32_t         layerIndex, tiLayerIndex;
  int32_t         dataIndex;
  int64_t         totalMacs = 0;
  const uint8_t   *name;
  NetParameter    netStructure;
  NetParameter    netParams;
  FILE            *fp1;
  int             paramSet = 0;
  int             conv2DRandParams = 0;
  int32_t weightsElementSizeInBits;
  int overWritefirstNode = 1 ;
  int32_t total_priorBoxSize = 0;
  int32_t   num_heads;
  
  if((params->inWidth == -1) || (params->inHeight == -1) || (params->inNumChannels == -1))
  {
    overWritefirstNode = 0;
  }  


  printf("Caffe Network File : %s  \n",(const char *)params->inputNetFile);
  printf("Caffe Model File   : %s  \n",(const char *)params->inputParamsFile);
  printf("TIDL Network File  : %s  \n",(const char *)params->outputNetFile);
  printf("TIDL Model File    : %s  \n",(const char *)params->outputParamsFile);


  quantizationStyle = params->quantizationStyle;
#if (!ENABLE_FIXED_QUANT_STYLE)
  if(quantizationStyle == TIDL_quantStyleFixed)
  {
    printf("Un Supported quantizationStyle : TIDL_quantStyleFixed\n");
    return ;
  }
    
#endif

  
  TIDL_readProtoFromTextFile((const char *)params->inputNetFile, &netStructure);
  TIDL_readProtoFromBinaryFile((const char *)params->inputParamsFile, &netParams);
  TIDL_appCNNConverRawDataToData(netParams);

  fp1 = fopen((const char *)params->outputParamsFile, "wb+");
  if(fp1 == NULL)
  {
    printf("Could not open %s file for writing \n",(const char *)params->outputParamsFile);
    exit(-1);
  }
  
  layerNum = netStructure.layer_size();
  name     = (uint8_t*)netStructure.name().c_str();
  if(netStructure.has_name())
  {
    printf("Name of the Network : %15s \n", netStructure.name().c_str());
  }
  printf("Num Inputs : %15d \n", netStructure.input_size());

  layerIndex = 0;
  dataIndex  = 0;
  if(netStructure.input_size())
  {
    for (i = 0; i < netStructure.input_size(); i++) 
    {
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].layerType  = TIDL_DataLayer;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs  = -1;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = 1;
      
      strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].name, 
      netStructure.input(i).c_str());
      strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].outDataNames[0],
      netStructure.input(i).c_str());
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataId = 
      dataIndex++;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].numDim = 
      netStructure.input_shape(i).dim_size();
      for (j = 0; j < netStructure.input_shape(i).dim_size(); j++) 
      {
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[j] = 
        netStructure.input_shape(i).dim(j);
      }
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].elementType = 
      gParams.inElementType;
      // Jacinto-net and Sqeeze net
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataQ = gParams.inQuantFactor;
      // Mobile Net
      //orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataQ = 30*255;
      
      layerIndex++;
    }
  }
  else
  {
    printf("Input layer(s) not Available.. Assuming below one Input Layer !!");
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].layerType  = TIDL_DataLayer;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs  = -1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = 1;
    
    strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].name,"indata");
    strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].outDataNames[0],
    "indata");
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].numDim = 4;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataId = 
    dataIndex++;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 1;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 3;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 224;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 224;
    orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].elementType  = 
    TIDL_UnsignedChar;
    layerIndex++;
  }
  
  if(overWritefirstNode)
  {
      for (i = layerIndex-1; i >= 0; i--) 
      {
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[1] = params->inNumChannels;
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[2] = params->inHeight;
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[3] = params->inWidth;
      }
  }
 
  /* check is this SSD net */
  ssdNet = 0;
  for (i = 0; i < layerNum; i++) 
  {
    if (netStructure.layer(i).type() == "DetectionOutput") 
    {
      ssdNet = 1;
      break;
    }
  }    
  
  for (i = 0; i < layerNum; i++) 
  {
    strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].name,
    netStructure.layer(i).name().c_str());

  //Set the weights size in bits
  orgTIDLNetStructure.TIDLPCLayers[layerIndex].weightsElementSizeInBits = NUM_WHGT_BITS;

    if (netStructure.layer(i).type() == "Concat") 
    {
      TIDL_importConcatParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure);
    }
    else if(netStructure.layer(i).type() == "Convolution")
    {
      TIDL_importConvParams(&orgTIDLNetStructure, fp1, i, layerIndex, dataIndex, 
      netStructure, netParams);
      layerIndex++;
      dataIndex++;
    }  
    else if(netStructure.layer(i).type() == "Pooling")
    {
      TIDL_importPoolingParams(&orgTIDLNetStructure, i, &layerIndex,  
      &dataIndex, netStructure, netParams);
    }
    else if ((netStructure.layer(i).type() == "ReLU") || 
        (netStructure.layer(i).type() == "LRN"))
    {
      TIDL_importRelUParams(&orgTIDLNetStructure, i, &layerIndex,  
      &dataIndex, netStructure, netParams);
    }    
    else if (netStructure.layer(i).type() == "PReLU") 
    {
      TIDL_importPRelUParams(&orgTIDLNetStructure, i, &layerIndex,  
      &dataIndex, netStructure, netParams);
    }    
    else if (netStructure.layer(i).type() == "Dropout")
    {
      TIDL_importDropoutParams(&orgTIDLNetStructure, i, layerIndex, dataIndex, 
      netStructure);
      layerIndex++;
      dataIndex++;
    }        
    else if ((netStructure.layer(i).type() == "Softmax") || 
        (netStructure.layer(i).type() == "softmax"))
    {
      TIDL_importSoftmaxParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure, netParams);
    }        
    else if (netStructure.layer(i).type() == "Deconvolution")
    {
      TIDL_importDeconvParams(&orgTIDLNetStructure, fp1, i, layerIndex, 
      dataIndex, netStructure, netParams);
      layerIndex++;
      dataIndex++;
    }
    else if ((netStructure.layer(i).type() == "Argmax") || 
        (netStructure.layer(i).type() == "ArgMax"))
    {
      TIDL_importArgmaxParams(&orgTIDLNetStructure, i, layerIndex, dataIndex, 
      netStructure);
      layerIndex++;
      dataIndex++;
    }
    else if (netStructure.layer(i).type() == "Bias")
    {
#if 0      
      TIDL_importBiasParams(&orgTIDLNetStructure, fp1, i, layerIndex, dataIndex, 
      netStructure, netParams);
      layerIndex++;
      dataIndex++;      
#else 
      TIDL_importBatchNormParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure,netParams,1);      
#endif
    }
    else if(netStructure.layer(i).type() == "Eltwise")
    {
      TIDL_importEltwiseParams(&orgTIDLNetStructure, i, layerIndex, dataIndex, 
      netStructure, netParams);
      layerIndex++;
      dataIndex++;    
    }   
    else if (netStructure.layer(i).type() == "BatchNorm")
    {
      TIDL_importBatchNormParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure,netParams,0);
    }    
    else if (netStructure.layer(i).type() == "Scale")
    {
#if 0      
      TIDL_importScaleParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure,netParams);
#else 
      TIDL_importBatchNormParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure,netParams,2);      
#endif
    } 
    else if (netStructure.layer(i).type() == "InnerProduct")
    {
      TIDL_importInnerProductParams(&orgTIDLNetStructure, fp1, i, layerIndex, 
      dataIndex, netStructure, netParams);
      layerIndex++;
      dataIndex++;         
    }       
    else if(netStructure.layer(i).type() == "Split")
    {
      TIDL_importSplitParams(&orgTIDLNetStructure, i, layerIndex, 
      netStructure);
      layerIndex++;
    }
    else if(netStructure.layer(i).type() == "Slice")
    {
      TIDL_importSliceParams(&orgTIDLNetStructure, i, &layerIndex,  
      &dataIndex, netStructure);
    }
    else if(netStructure.layer(i).type() == "Crop")
    {
      TIDL_importCropParams(&orgTIDLNetStructure, i, layerIndex, 
      dataIndex, netStructure);
      layerIndex++;
      dataIndex++;      
    }
    else if(netStructure.layer(i).type() == "Flatten")
    {
      TIDL_importFlattenParams(&orgTIDLNetStructure, i, &layerIndex, 
      &dataIndex, netStructure);
    } 
    else if(netStructure.layer(i).type() == "Permute")
    {
      TIDL_importPermuteParams(&orgTIDLNetStructure, i, layerIndex, 
      dataIndex, netStructure);
      layerIndex++;
      dataIndex++;
    }
    else if (netStructure.layer(i).type() == "PriorBox")
    {
      TIDL_importPriorBoxParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure,netParams);
    }  
    else if (netStructure.layer(i).type() == "Reshape")
    {
      TIDL_importReshapeParams(&orgTIDLNetStructure, i, &layerIndex, 
      &dataIndex, netStructure);
    }  
    else if (netStructure.layer(i).type() == "DetectionOutput")
    {
      TIDL_importDetectionOutputParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex, 
      netStructure,netParams);
    }  
    else
    {
      printf("Unsuported Layer Type : %s !!!! assuming it as pass through layer\n", 
      netStructure.layer(i).type().c_str());
      TIDL_importCopyLayerParams(&orgTIDLNetStructure, i, layerIndex, 
      &dataIndex, netStructure);
      layerIndex++;
    }
  }
  
    for (i = 0; i < layerIndex; i++) 
    {
      /* Find Inner Product layers */
      if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer)
      {
        if((orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[2] == 1) &&
          (orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[3] == 1) &&
          (orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[2] == 1) &&
          (orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[3] == 1) &&
          (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.kernelW == 1) &&
          (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.kernelH == 1) &&
          ((orgTIDLNetStructure.TIDLPCLayers[i+1].layerType == TIDL_InnerProductLayer) ||
          (orgTIDLNetStructure.TIDLPCLayers[i+1].layerType == TIDL_SoftMaxLayer))
          /* if next layer is inner product or softMax layer */
          )
        {
          orgTIDLNetStructure.TIDLPCLayers[i].layerType = TIDL_InnerProductLayer;
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.enableRelU = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.enableRelU;

          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.ptr = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr;
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.bufSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize;

          if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.enableBias)
          {
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr;
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize;
          }
          else
          {
            printf("TIDL_InnerProductLayer without Bias is not supported \n");
          }

          //orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr = NULL;
          //orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize = 0;
          //orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr = NULL;
          //orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize = 0;
        }
      }
    }
    
    for (i = 0; i < layerIndex; i++) 
    {
      /* Find Convolution Layer iwht Just one input channel
      The minimum number of input channel required for TIDL convolution layer is 2
      So making it to 2 input channel and ans setting all the kernel co-efficents for 
      second input channel as zero*/
      if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer)
      {
        if(orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[1] == 1)
        {        
          orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[1] = 2;
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.numInChannels = 2;
          {
          uint32_t k = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.kernelW *
                       orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.kernelH;
          uint32_t numOutCh = orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[1];
          
          float *data       = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr);
          uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize;
 
          float *outData       = (float *)malloc(dataSize*2*sizeof(float));
          
            for (int idx = 0; idx < numOutCh; idx++) 
            {
              for (int idx2 = 0; idx2 < k; idx2++) 
              {
                outData[2*idx*k + idx2] = data[idx*k + idx2];
                outData[2*idx*k + k + idx2] = 0;
              }
            }
            free(data);
            STORE_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr,outData);
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize = dataSize*2;
        }
        TIDL_UpdateOutDataBuff(&orgTIDLNetStructure,i,orgTIDLNetStructure.TIDLPCLayers[i].inData[0]);

        
       }
     }
    }
    
#if 0    
    /* calculate the size of all the priorboxes for concatination */
    total_priorBoxSize = 1; // To store number of heads
    num_heads = 0;
    for (i = 0; i < layerIndex; i++) 
    {
      if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_PriorBoxLayer)
      {
        total_priorBoxSize += orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBoxSize;
        num_heads++;
      }
    }      
    
    /* calculate the size of all the priorboxes for concatination */
    float *top_data   = (float *)malloc(total_priorBoxSize*sizeof(float));
    int   k, data_offset = 1;
    top_data[0] = (float)num_heads;    
    for (i = 0; i < layerIndex; i++) 
    {
      if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_PriorBoxLayer)
      {
        float * data      = (float *)orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.ptr;
        uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.bufSize;
        for(k = 0; k < dataSize; k++)
        {
          top_data[data_offset + k] = data[k]; 
        }
        data_offset += dataSize; 
        free(data);        
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.ptr = NULL;
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.bufSize = 0;        
      }
    } 
#endif
    
    int32_t zeroWeightValue;
    if(quantizationStyle == TIDL_quantStyleDynamic)
  {
    /* Dynamically Quantize Layer Params */
     uint32_t totalParamSize = 0;
    for (i = 0; i < layerIndex; i++) 
    {
      if((orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) || 
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_InnerProductLayer) || 
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer) ||
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_BatchNormLayer) ||
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_DetectionOutputLayer)
          )
      {
        float min = FLT_MAX;
        float max = FLT_MIN;

        if((orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer))
        {
          weightsElementSizeInBits = orgTIDLNetStructure.TIDLPCLayers[i].weightsElementSizeInBits;
          float *  data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr);
          uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize;
          uint8_t * params = (uint8_t *)malloc(dataSize * ((weightsElementSizeInBits-1)/8 + 1));
          TIDL_findRange(data, dataSize, &min , &max, 1.0);
          
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weightsQ = 
          TIDL_QuantizeUnsignedMax((uint8_t *)params, data,dataSize, min , max, NUM_WHGT_BITS, weightsElementSizeInBits, &zeroWeightValue);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.zeroWeightValue = zeroWeightValue;
          
          if(weightsElementSizeInBits > 8)
          {
            fwrite(params,2,dataSize,fp1);
            totalParamSize += 2*dataSize;
          }
          else
          {
            fwrite(params,1,dataSize,fp1);
            totalParamSize += dataSize;
          }
          free(params);
          free(data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize = 0;
          if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.enableBias)
          {
            min = FLT_MAX;
            max = FLT_MIN;
            if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.enableBias)
            {
                float * biasData      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr);
                uint32_t biasDataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize;
                TIDL_findRange(biasData, biasDataSize, &min , &max, 1.0);
            }
            max = abs(min) >  abs(max) ? abs(min) : abs(max);
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.biasQ = 
            TIDL_QuantizeUnsignedMax(0, 0,0, 0 , max, NUM_BIAS_BITS, (NUM_BIAS_BYTES*8), &zeroWeightValue);

            data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr);
            dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize;
            
            int16_t * params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
            for (int idx = 0; idx < dataSize; idx++) 
            {
              int32_t biasParam = TIDL_normalize(data[idx], 0 , max);
              params[idx] = (int16_t)TIDL_roundSat(biasParam,0,SHRT_MIN,SHRT_MAX);
            }
            fwrite(params,NUM_BIAS_BYTES,dataSize,fp1);
            totalParamSize += NUM_BIAS_BYTES*dataSize;
            free(params);
            free(data);
            RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr);
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize = 0;
          }
          if (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.biasQ == 0)
          {
             orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.biasQ = 1;
          }

        }
        else if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
        {
          weightsElementSizeInBits = orgTIDLNetStructure.TIDLPCLayers[i].weightsElementSizeInBits;
          float *  data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.ptr);
          uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.bufSize;
          uint8_t * params = (uint8_t *)malloc(dataSize * ((weightsElementSizeInBits-1)/8 + 1));
          TIDL_findRange(data, dataSize, &min , &max, 1.0);

          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weightsQ = 
          TIDL_QuantizeUnsignedMax((uint8_t *)params, data,dataSize, min , max, NUM_WHGT_BITS,  weightsElementSizeInBits, &zeroWeightValue);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.zeroWeightValue = zeroWeightValue;
          if(weightsElementSizeInBits > 8)
          {
            fwrite(params,2,dataSize,fp1);
            totalParamSize += 2*dataSize;
          }
          else
          {
            fwrite(params,1,dataSize,fp1);
            totalParamSize += dataSize;
          }
          free(params);
          free(data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.bufSize = 0;
          min = FLT_MAX;
          max = FLT_MIN;
          //if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.enableBias)
          {
            float * biasData      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
            uint32_t biasDataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize;
            TIDL_findRange(biasData, biasDataSize, &min , &max, 1.0);
          }
          data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
          dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize;

          max = abs(min) >  abs(max) ? abs(min) : abs(max);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.biasQ = 
          TIDL_QuantizeUnsignedMax(0, 0,0, 0 , max, NUM_BIAS_BITS, (NUM_BIAS_BYTES*8), &zeroWeightValue);

 
          //if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.enableBias)
          {
            int16_t *params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
            for (int idx = 0; idx < dataSize; idx++) 
            {
              int32_t biasParam = TIDL_normalize(data[idx], 0 , max);
              params[idx] = (int16_t)TIDL_roundSat(biasParam,0,SHRT_MIN,SHRT_MAX);
            }
            fwrite(params,NUM_BIAS_BYTES,dataSize,fp1);
            totalParamSize += NUM_BIAS_BYTES*dataSize;
            free(params);
          }
          free(data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize = 0;
          if (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.biasQ == 0)
          {
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.biasQ = 1;
          }
        }
        else if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)
        {
          weightsElementSizeInBits = orgTIDLNetStructure.TIDLPCLayers[i].weightsElementSizeInBits;
          float *  data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.ptr);
          uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.bufSize;
          uint8_t * params = (uint8_t *)malloc(dataSize * ((weightsElementSizeInBits-1)/8 + 1));
          TIDL_findRange(data, dataSize, &min , &max, 1.0);

          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weightsQ = 
          TIDL_QuantizeUnsignedMax((uint8_t *)params, data,dataSize, min , max, NUM_WHGT_BITS, weightsElementSizeInBits, &zeroWeightValue);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.zeroWeightValue = zeroWeightValue;

          if(weightsElementSizeInBits > 8)
          {
            fwrite(params,2,dataSize,fp1);
            totalParamSize += 2*dataSize;
          }
          else
          {
            fwrite(params,1,dataSize,fp1);
            totalParamSize += dataSize;
          }
          free(params);
          free(data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.bufSize = 0;
          
          min = FLT_MAX;
          max = FLT_MIN;
          //if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.enableBias)
          {
            float * biasData      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.ptr);
            uint32_t biasDataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.bufSize;
            TIDL_findRange(biasData, biasDataSize, &min , &max, 1.0);
          }
          data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.ptr);
          dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.bufSize;

          max = abs(min) >  abs(max) ? abs(min) : abs(max);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.biasQ = 
          TIDL_QuantizeUnsignedMax(0, 0,0, 0 , max, NUM_BIAS_BITS, (NUM_BIAS_BYTES*8), &zeroWeightValue);
          
          {
            int16_t *params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
            for (int idx = 0; idx < dataSize; idx++) 
            {
              int32_t biasParam = TIDL_normalize(data[idx], 0 , max);
              params[idx] = (int16_t)TIDL_roundSat(biasParam,0,SHRT_MIN,SHRT_MAX);
            }
            fwrite(params,NUM_BIAS_BYTES,dataSize,fp1);
            totalParamSize += NUM_BIAS_BYTES*dataSize;
            free(params);
          }
          free(data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.bufSize = 0;
          if (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.biasQ == 0)
          {
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.biasQ = 1;
          }
          if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.reluType == TIDL_PRelU)
          {
            float * slopeData      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.ptr);
            uint32_t slopeDataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.bufSize;
            uint8_t * params = (uint8_t *)malloc(slopeDataSize * ((weightsElementSizeInBits-1)/8 + 1));
            float min = FLT_MAX;
            float max = FLT_MIN;
            TIDL_findRange(slopeData, slopeDataSize, &min , &max, (1.0));
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slopeQ = 
            TIDL_QuantizeUnsignedMax((uint8_t *)params, slopeData,slopeDataSize, min , max, NUM_WHGT_BITS, weightsElementSizeInBits, &zeroWeightValue);
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slopeQ /= 256;
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.zeroSlopeValue = zeroWeightValue;

            if(weightsElementSizeInBits > 8)
            {
              fwrite(params,2,slopeDataSize,fp1);
              totalParamSize += 2*slopeDataSize;
            }
            else
            {
              fwrite(params,1,slopeDataSize,fp1);
              totalParamSize += slopeDataSize;
            }
            free(params);
            free(slopeData);
            RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.ptr);
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.bufSize = 0;          
          }
        }
        else if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_DetectionOutputLayer)
        {
          float * top_data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.ptr);
          uint32_t total_priorBoxSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.bufSize;
          
          fwrite(top_data, 4, total_priorBoxSize, fp1);
          totalParamSize += 4*total_priorBoxSize;
          free(top_data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBox.bufSize = 0;                  
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.detectOutParams.priorBoxSize = total_priorBoxSize;          
        }
      }
    }
  }
  else if(quantizationStyle == TIDL_quantStyleFixed)
  {
    /* Fixed Quantization of Layer Params */
     uint32_t totalParamSize = 0;
	 for (i = 0; i < layerIndex; i++)
    {
		float min = FLT_MAX;
		float max = FLT_MIN;
		weightsElementSizeInBits = orgTIDLNetStructure.TIDLPCLayers[i].weightsElementSizeInBits;
		if((orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_InnerProductLayer) || 
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer) ||
			(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)
          )
      {
        if((orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
          (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_Deconv2DLayer))
        {
          float *  data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr);
          uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize;
          int8_t * params = (int8_t *)malloc(dataSize);
		  TIDL_findRange(data, dataSize, &min, &max, 1.0);
          if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.enableBias)
          {
            float * biasData      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr);
            uint32_t biasDataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize;
			if ((NUM_BIAS_BITS - NUM_WHGT_BITS - orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.inDataQ) > 0)
			{
				TIDL_findRange(biasData, biasDataSize, &min, &max, (1.0 / (1 << (NUM_BIAS_BITS - NUM_WHGT_BITS - orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.inDataQ))));
			}
			else
			{
				TIDL_findRange(biasData, biasDataSize, &min, &max, 1.0);
			}
          }
		  orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weightsQ = TIDL_findSymQ(min, max);

		  for (int idx = 0; idx < dataSize; idx++) 
          {
            params[idx] = TIDL_flApply(data[idx], 
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weightsQ);
          }
         
          fwrite(params,1,dataSize,fp1);
          totalParamSize += dataSize;
          free(params);
          free(data);

          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weights.bufSize = 0;
          if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.enableBias)
          {
            data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr);
            dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize;
            if(NUM_BIAS_BYTES == 2)
            {
                int16_t * params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
                for (int idx = 0; idx < dataSize; idx++) 
                {
                  params[idx] = TIDL_flApply(data[idx], 
                  (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weightsQ + 
                  orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.inDataQ));
                }
            }
            else
            {
                int32_t * params = (int32_t *)malloc(dataSize*NUM_BIAS_BYTES);
                for (int idx = 0; idx < dataSize; idx++) 
                {
                  params[idx] = TIDL_flApply(data[idx], 
                  (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.weightsQ + 
                  orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.inDataQ));
                }
            }
          }
            
            fwrite(params,NUM_BIAS_BYTES,dataSize,fp1);
            totalParamSize += NUM_BIAS_BYTES*dataSize;
            free(params);
            free(data);
            RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.ptr);
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.bias.bufSize = 0;

        }
        else if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
        {
          float *  data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.ptr);
          uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.bufSize;
          int8_t * params = (int8_t *)malloc(dataSize);
		  TIDL_findRange(data, dataSize, &min, &max, 1.0);
		  {
			  float * biasData = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
			  uint32_t biasDataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize;
			  if ((NUM_BIAS_BITS - NUM_WHGT_BITS - orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.inDataQ) > 0)
			  {
				  TIDL_findRange(biasData, biasDataSize, &min, &max, (1.0 / (1 << (NUM_BIAS_BITS - NUM_WHGT_BITS - orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.inDataQ))));
			  }
			  else
			  {
				  TIDL_findRange(biasData, biasDataSize, &min, &max, 1.0);
			  }
		  }
		  orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weightsQ = TIDL_findSymQ(min, max);

          for (int idx = 0; idx < dataSize; idx++) 
          {
            params[idx] = TIDL_flApply(data[idx], 
            orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weightsQ);
          }

          fwrite(params,1,dataSize,fp1);
          totalParamSize += dataSize;
          free(params);
          free(data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weights.bufSize = 0;
          data      = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
          dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize;
          //if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.enableBias)
          {
            if(NUM_BIAS_BYTES == 2)
            {
                int16_t *params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
                
                for (int idx = 0; idx < dataSize; idx++) 
                {
                  params[idx] = TIDL_flApply(data[idx], 
                  (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weightsQ + 
                  orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.inDataQ));
                }
            }
            else
            {
                int32_t *params = (int32_t *)malloc(dataSize*NUM_BIAS_BYTES);
                
                for (int idx = 0; idx < dataSize; idx++) 
                {
                  params[idx] = TIDL_flApply(data[idx], 
                  (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.weightsQ + 
                  orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.inDataQ));
                }
            }

            fwrite(params,NUM_BIAS_BYTES,dataSize,fp1);
            totalParamSize += NUM_BIAS_BYTES*dataSize;
            free(params);
          }
          free(data);
          RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize = 0;
        }
		else if (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)
		{
			weightsElementSizeInBits = orgTIDLNetStructure.TIDLPCLayers[i].weightsElementSizeInBits;
			float *  data = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.ptr);
			uint32_t dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.bufSize;
			int8_t * params = (int8_t *)malloc(dataSize * ((weightsElementSizeInBits - 1) / 8 + 1));
			
			//TIDL_findRange(data, dataSize, &min, &max, 1.0);
			//orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weightsQ = TIDL_findSymQ(min, max);

			for (int idx = 0; idx < dataSize; idx++)
			{
				params[idx] = TIDL_flApply(data[idx],
					orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weightsQ);
			}

			fwrite(params, 1, dataSize, fp1);
			totalParamSize += dataSize;
			free(params);
			free(data);

			RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.ptr);
			orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weights.bufSize = 0;
			data = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.ptr);
			dataSize = orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.bias.bufSize;
			//if(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.enableBias)
			{
			    if(NUM_BIAS_BYTES == 2)
                {	
                    int16_t *params = (int16_t *)malloc(dataSize * NUM_BIAS_BYTES);
                    for (int idx = 0; idx < dataSize; idx++)
                    {
                        params[idx] = TIDL_flApply(data[idx],
                            (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weightsQ +
                                orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.inDataQ));
                    }
                }
                else
                {
                    int16_t *params = (int16_t *)malloc(dataSize * NUM_BIAS_BYTES);
                    for (int idx = 0; idx < dataSize; idx++)
                    {
                        params[idx] = TIDL_flApply(data[idx],
                            (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.weightsQ +
                                orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.inDataQ));
                    }
                }

				fwrite(params, NUM_BIAS_BYTES, dataSize, fp1);
				totalParamSize += NUM_BIAS_BYTES * dataSize;
				free(params);
			}
			free(data);
			RESET_PTR(orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
			orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize = 0;
		}
	  }
    }
  }
  else
  {
      printf("Unsuported quantizationStyle \n");
  }

    /* Re-shape layers */
  for (i = 0; i < layerIndex; i++) 
  {
    if(((orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_PoolingLayer) &&
      (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.poolParams.kernelW == 0 ) &&
      (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.poolParams.kernelH == 0) &&
      ((orgTIDLNetStructure.TIDLPCLayers[i+1].layerType == TIDL_InnerProductLayer) ||
       (orgTIDLNetStructure.TIDLPCLayers[i+1].layerType == TIDL_SoftMaxLayer))) 
      ||
      (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
      ||
      (orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_SoftMaxLayer))
    {
      orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[3] = 
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[1]*
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[2]*
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[3];
      orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[1] = 1;
      orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[2] = 1;
      TIDL_UpdateInDataBuff(&orgTIDLNetStructure,layerIndex,orgTIDLNetStructure.TIDLPCLayers[i].outData[0]);
      if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
      {
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.numInNodes = 
      orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[1] * orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[2]*orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[3];
      }
    }            
  }


  
  printf(" Num of Layer Detected : %3d \n",layerIndex);

  tIDLNetStructure.dataElementSize    = 1;   //Set to 1 for 8-bit data and to 2 for 16-bit data
  tIDLNetStructure.biasElementSize    = NUM_BIAS_BYTES;
  tIDLNetStructure.weightsElementSize = ((weightsElementSizeInBits-1)/8 + 1); //1;
  tIDLNetStructure.slopeElementSize   = tIDLNetStructure.weightsElementSize;
  tIDLNetStructure.interElementSize   = 4;
  tIDLNetStructure.quantizationStyle  = quantizationStyle;
  tIDLNetStructure.strideOffsetMethod = TIDL_strideOffsetTopLeft;
  
  tiLayerIndex = 0;
  for (i = 0; i < layerIndex; i++) 
  {
    if((orgTIDLNetStructure.TIDLPCLayers[i].layerType != TIDL_SplitLayer) &&
      (orgTIDLNetStructure.TIDLPCLayers[i].layerType !=TIDL_DropOutLayer) && 
      //(orgTIDLNetStructure.TIDLPCLayers[i].layerType !=TIDL_ReshapeLayer) && 
      (orgTIDLNetStructure.TIDLPCLayers[i].layerType !=TIDL_PriorBoxLayer))
    {
      tIDLNetStructure.TIDLLayers[tiLayerIndex].layerType   = 
      orgTIDLNetStructure.TIDLPCLayers[i].layerType;
      tIDLNetStructure.TIDLLayers[tiLayerIndex].layerParams = 
      orgTIDLNetStructure.TIDLPCLayers[i].layerParams;
      tIDLNetStructure.TIDLLayers[tiLayerIndex].numInBufs   = 
      orgTIDLNetStructure.TIDLPCLayers[i].numInBufs;
      tIDLNetStructure.TIDLLayers[tiLayerIndex].numOutBufs  = 
      orgTIDLNetStructure.TIDLPCLayers[i].numOutBufs;
      if(tIDLNetStructure.TIDLLayers[tiLayerIndex].layerType == TIDL_DataLayer)
      {
        tIDLNetStructure.TIDLLayers[tiLayerIndex].layersGroupId      = 0;
      }
      else
      {
          tIDLNetStructure.TIDLLayers[tiLayerIndex].coreID             = gParams.layersGroupId[tiLayerIndex];
          tIDLNetStructure.TIDLLayers[tiLayerIndex].layersGroupId      = gParams.layersGroupId[tiLayerIndex];
      }
      if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_UnSuportedLayer)
      {
        char naName[30] = "TIDL_UnSuportedLayer";
        printf("%3d, %-30s, %-40s", i, 
          naName, 
          orgTIDLNetStructure.TIDLPCLayers[i].name);
      }
      else
      {
        printf("%3d, %-30s, %-40s", i, 
          TIDL_LayerString[orgTIDLNetStructure.TIDLPCLayers[i].layerType], 
          orgTIDLNetStructure.TIDLPCLayers[i].name);
      }


      printf("%3d, %3d ,%3d , ", 
      tIDLNetStructure.TIDLLayers[tiLayerIndex].layersGroupId, 
      orgTIDLNetStructure.TIDLPCLayers[i].numInBufs,
      orgTIDLNetStructure.TIDLPCLayers[i].numOutBufs);

      for (j = 0; j < orgTIDLNetStructure.TIDLPCLayers[i].numInBufs; j++) 
      {
        printf("%3d ,",orgTIDLNetStructure.TIDLPCLayers[i].inData[j].dataId);
        tIDLNetStructure.TIDLLayers[tiLayerIndex].inData[j]   = 
        orgTIDLNetStructure.TIDLPCLayers[i].inData[j];
      }
      j = 0;
      if(orgTIDLNetStructure.TIDLPCLayers[i].numInBufs > 0)
      j = orgTIDLNetStructure.TIDLPCLayers[i].numInBufs;
      for (; j < 8; j++) 
      {
        printf("  x ,");
      }

      for (j = 0; j < orgTIDLNetStructure.TIDLPCLayers[i].numOutBufs; j++) 
      {
        printf("%3d ,",orgTIDLNetStructure.TIDLPCLayers[i].outData[j].dataId);
        tIDLNetStructure.TIDLLayers[tiLayerIndex].outData[j]   = 
        orgTIDLNetStructure.TIDLPCLayers[i].outData[j];
      }
      
      tIDLNetStructure.TIDLLayers[tiLayerIndex].outData[0].minValue = (int)(0x7FFFFFFF);
      tIDLNetStructure.TIDLLayers[tiLayerIndex].outData[0].maxValue = (int)(0x80000000);
      
      for (j = 0; j < TIDL_DIM_MAX; j++) 
      {
        printf("%8d ,",
        orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[j]);
      }

      for (j = 0; j < TIDL_DIM_MAX; j++) 
      {
        printf("%8d ,",
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[j]);
      }
#ifdef PLATFORM_64BIT
      printf("%10ld ,",orgTIDLNetStructure.TIDLPCLayers[i].numMacs);
#else
      printf("%10lld ,",orgTIDLNetStructure.TIDLPCLayers[i].numMacs);
#endif
      totalMacs += orgTIDLNetStructure.TIDLPCLayers[i].numMacs;
      printf("\n");
      tiLayerIndex++;
    }
  }

  /* Function to set Conv2dKernelType in layer params based on the "conv2dKernelType"
     parameter from import config file : TIDL - 310
  */     
  TIDL_setConv2dKernelType(&tIDLNetStructure, tiLayerIndex);

  /* Below for loop calculates the number of output layers and set them as 
     TIDL_DataLayer, so this loop checks each output is consumed by any other,
      if not that layer is set as output layer
  */         
  /* Set output layers(TIDL_DataLayer) after all the processing layers */
  layerNum = tiLayerIndex;
  for (i = 0; i < tiLayerIndex; i++) 
  {
    sTIDL_Layer_t *tidlLayer;
    tidlLayer = &tIDLNetStructure.TIDLLayers[layerNum];
    tidlLayer->layerType   = TIDL_DataLayer;
    tidlLayer->numInBufs   = 0;
    tidlLayer->numOutBufs  = -1;
    tidlLayer->coreID      = 255;

    if(tIDLNetStructure.TIDLLayers[i].layerType != TIDL_DataLayer)
    {
      for (j = 0 ; j < tIDLNetStructure.TIDLLayers[i].numOutBufs; j++) 
      {
        if(!TIDL_isDataBufUsed(tIDLNetStructure.TIDLLayers[i].outData[j].dataId, 
              &tIDLNetStructure, layerNum))
        {
          tidlLayer->inData[tidlLayer->numInBufs] = 
          tIDLNetStructure.TIDLLayers[i].outData[j];
          tidlLayer->numInBufs++;
        }
      }
      /* There can be more than one ouptut layer in a network, so
         increament layer count by 1 after each output layer */ 
      if(tidlLayer->numInBufs > 0)
      {
        layerNum++;
      }
    }
  }
  tIDLNetStructure.numLayers = layerNum;

  printf("Total Giga Macs : %4.4f\n", ((float)totalMacs/1000000000));
  if(fp1 != NULL)
  {
    fclose(fp1);
  }
  fp1 = fopen((const char *)params->outputNetFile, "wb+");
  if(fp1 == NULL)
  {
    printf("Could not open %s file for writing \n",(const char *)params->outputNetFile);
  }
  fwrite(&tIDLNetStructure,1,sizeof(tIDLNetStructure),fp1);
  if(fp1 != NULL)
  {
    fclose(fp1);
  }
}
