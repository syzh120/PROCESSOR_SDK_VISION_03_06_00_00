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
#include <limits.h>
#define FLT_MIN __FLT_MIN__
#define FLT_MAX __FLT_MAX__

char *itoa(int i, char* s, int dummy_radix) {
    sprintf(s, "%d", i);
    return s;
}
#endif

#include <cmath>

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

#include "ti_dl.h"
#ifdef _WIN32
#include "tensorflow\core\framework\graph.pb.h"
#else
#include "tensorflow/core/framework/graph.pb.h"
#endif
#include "tidl_import_config.h"

using namespace std;
using namespace tensorflow;
using ::google::protobuf::Message;
using ::google::protobuf::io::FileInputStream;
using ::google::protobuf::io::FileOutputStream;
using ::google::protobuf::io::ZeroCopyInputStream;
using ::google::protobuf::io::CodedInputStream;
using ::google::protobuf::io::ZeroCopyOutputStream;
using ::google::protobuf::io::CodedOutputStream;

#include "tidl_import_common.h" 

#define IS_SIGNED_DATA (1)
#define QUAN_STYLE2_ROUND (0.5)
extern sTIDL_OrgNetwork_t      orgTIDLNetStructure;
extern sTIDL_Network_t         tIDLNetStructure;

#ifdef PLATFORM_64BIT
extern void * sBuffPtrs[MAX_NUM_PTRS_TO_STORE];
extern uint32_t sBufPtrInd;
#endif

#define ENABLE_BIN_PARSE_PRINT  (0)
int32_t gloab_data_format = -1;

uint32_t TIDL_kernelReshape(uint8_t * param, uint32_t w, uint32_t h, uint32_t ci, uint32_t co, uint32_t nBytes)
{
  uint32_t i0, i1, i2, i3;
  uint8_t * tPtr = (uint8_t * )malloc(w*h*ci*co*sizeof(uint8_t)*nBytes);
  
  if(nBytes == 1)
  {
	for(i0 = 0; i0 < co; i0++)
	{
	  for(i1 = 0; i1 < ci; i1++)
	  {
	    for(i2 = 0; i2 < h; i2++)
	    {
	      for(i3 = 0; i3 < w; i3++)
		  {
		    tPtr[i0*ci*h*w + i1*h*w + i2*w + i3] = param[i2*w*ci*co + i3*ci*co + i1*co + i0];
		  }
		}
	  }
	}
  }
  else //for 16-bit kernel
  {
	uint16_t *param16 = (uint16_t *)param;
	uint16_t *tPtr16 = (uint16_t *)tPtr;

	for(i0 = 0; i0 < co; i0++)
	{
	  for(i1 = 0; i1 < ci; i1++)
	  {
	    for(i2 = 0; i2 < h; i2++)
	    {
	      for(i3 = 0; i3 < w; i3++)
		  {
		    tPtr16[i0*ci*h*w + i1*h*w + i2*w + i3] = param16[i2*w*ci*co + i3*ci*co + i1*co + i0];
		  }
		}
      }
	}
  }
  memcpy(param,tPtr,w*h*ci*co*sizeof(uint8_t)*nBytes);
  free(tPtr);
  return 0;
}


uint32_t TIDL_kernelScale(float * param, float * scale, uint32_t w, uint32_t h, uint32_t ci, uint32_t co)
{
  uint32_t i0, i1, i2, i3;
  for(i0 = 0; i0 < co; i0++)
  {
    for(i1 = 0; i1 < ci; i1++)
    {
      for(i2 = 0; i2 < h; i2++)
      {
        for(i3 = 0; i3 < w; i3++)
        {
          param[i2*w*ci*co + i3*ci*co + i1*co + i0] *= scale[i0];
        }
      }
    }
  }
  return 0;
}
uint32_t TIDL_depthWiseKernelScale(float * param, float * scale, uint32_t k, uint32_t c)
{
  uint32_t i0, i1;
  for(i0 = 0; i0 < c; i0++)
  {
    for(i1 = 0; i1 < k; i1++)
    {
      param[i1*c + i0] *= scale[i0];
    }
  }
  return 0;
}
int32_t TIDL_isInputLayer(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,int32_t numLayer, const char *bufName, int32_t layerType)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,(const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs == 1) && (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == layerType))
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

int32_t TIDL_getLayerIdx(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, int32_t numLayer, const char *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,(const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        return i;
      }
    }
  }
  return (-1);
}

int32_t TIDL_isInputInnerProduct(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,int32_t numLayer, const char *bufName)
{
  int32_t i,j;
  for (i = (numLayer-1); i >= 0; i--)
  {
    for (j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs; j++)
    {       
      if(strcmp((const char*)bufName,(const char*)pOrgTIDLNetStructure->TIDLPCLayers[i].outDataNames[j]) == 0)
      {
        if((pOrgTIDLNetStructure->TIDLPCLayers[i].numOutBufs == 1) && (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer))
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
int TIDL_fl_apply(float data, int fl)
{
  int out;
  if( data > 0)
  {
    out = (data* (1 << fl) + 0.5);
  }
  else
  {
    out = (data* (1 << fl) - 0.5);
  }
  return out;
}


TensorProto TIDL_getConstTensor(GraphDef& tfGraphDef, const string name)
{
  int i;

  for (i = 0; i < tfGraphDef.node_size(); i++) 
  {
    if((strcmp(tfGraphDef.node(i).name().c_str(),name.c_str()) == 0))
    {
      if((strcmp(tfGraphDef.node(i).op().c_str(),"Const") == 0))
      {
        if(tfGraphDef.node(i).attr().at(std::string("value")).has_tensor())
        {
          auto & tensor = tfGraphDef.node(i).attr().at(std::string("value")).tensor();
          return(tensor);
        }
      }
      else if((strcmp(tfGraphDef.node(i).op().c_str(),"Identity") == 0))
      {
        return(TIDL_getConstTensor(tfGraphDef, tfGraphDef.node(i).input(0)));
      }
    }
  }
  return (tensorflow::TensorProto::default_instance());
}

int32_t TIDL_isInputConstTensor(GraphDef& tfGraphDef, const string name)
{
  int i;

  for (i = 0; i < tfGraphDef.node_size(); i++) 
  {
    if((strcmp(tfGraphDef.node(i).name().c_str(),name.c_str()) == 0))
    {
      if((strcmp(tfGraphDef.node(i).op().c_str(),"Const") == 0))
      {
        if(tfGraphDef.node(i).attr().at(std::string("value")).has_tensor())
        {
          return(1);
        }
      }
      else if((strcmp(tfGraphDef.node(i).op().c_str(),"Identity") == 0))
      {
        return(TIDL_isInputConstTensor(tfGraphDef, tfGraphDef.node(i).input(0)));
      }
    }
  }
  return (0);
}
int32_t TIDL_hasAttr(const NodeDef& node, const char * name)
{
#ifdef _WIN32
  for (auto& it = node.attr().begin(); it != node.attr().end();) 
#else
  for (google::protobuf::Map<std::string, tensorflow::AttrValue>::const_iterator it = node.attr().begin(); it != node.attr().end();) 
#endif
  {
    auto& map = it->first;
    if(strcmp(map.c_str(),name) == 0)
    {
      return (1);
    }
    it++;
  }
  return (0);
}

int32_t TIDL_getAttr_type(const NodeDef& node, char const * name, int32_t * type)
{
  if(TIDL_hasAttr(node, (char *)name))
  {
    auto& value = node.attr().at(std::string(name));
    if(value.type() == DT_UINT8)
    {
      *type = TIDL_UnsignedChar;
    }
    else if(value.type() == DT_INT8)
    { 
      *type = TIDL_SignedChar;
    }
    *type = TIDL_UnsignedChar;
    return (1);
  }
  return (0);
}

int32_t TIDL_getAttr_padding(const NodeDef& node, const char * name, int32_t * padType)
{
  if(TIDL_hasAttr(node, (char *)name))
  {
    auto& value = node.attr().at(std::string(name));
    if(strcmp(value.s().c_str(),"SAME") == 0)
    {
      *padType = 0;
    }
    else if(strcmp(value.s().c_str(),"VALID") == 0)
    {
      *padType = 1;
    }
    else
    {
      *padType = -1;
      printf("\nUn suported Padding type \n");
    }
    return (1);
  }
  return (0);
}
int32_t TIDL_getAttr_data_format(const NodeDef& node, const char * name)
{
  if(TIDL_hasAttr(node, (char *)name))
  {
    auto& value = node.attr().at(std::string(name));
    if(strcmp(value.s().c_str(),"NHWC") == 0)
    {
      if(gloab_data_format == -1)
      {
        gloab_data_format = 0;
      }
      else if(gloab_data_format != 0)
      {
        printf("\ndata_format is not common accross all the layers \n");
      }
    }
    else if(strcmp(value.s().c_str(),"NCHW") == 0)
    {
      if(gloab_data_format == -1)
      {
        gloab_data_format = 1;
      }
      else if(gloab_data_format != 1)
      {
        printf("\ndata_format is not common accross all the layers \n");
      }
    }
    else
    {
      printf("\nUn suported data_format \n");
    }        
    return (1);
  }
  return (0);
}
int32_t TIDL_getAttr_value(const NodeDef& node, const char * name, int32_t * valuePtr, int32_t idx)
{
  if(TIDL_hasAttr(node, (char *)name))
  {
    auto& value = node.attr().at(std::string(name));
    *valuePtr  = (int32_t)value.list().i(idx);

    return (1);
  }
  return (0);
}

void TIDL_importConvParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
GraphDef&             tfGraphDef)
{
  int32_t status;  
  int32_t padType;
  int32_t idx1, idx2;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConvolutionLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(1));
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numInChannels  = tensor.tensor_shape().dim(2).size();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numOutChannels = tensor.tensor_shape().dim(3).size();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW        = tensor.tensor_shape().dim(0).size();
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH        = tensor.tensor_shape().dim(1).size();
  if(strcmp(tfGraphDef.node(i).op().c_str(),"DepthwiseConv2dNative") == 0)  
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numOutChannels = 
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numInChannels;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups      = 
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numInChannels;
  }
  else
  {
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups      = 1;
  }
  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW    = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH    = 1;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideW        = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH        = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padW           = 0;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padH           = 0;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableBias     = 0;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enableRelU     = 0;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.enablePooling  = 0;

  TIDL_getAttr_type(tfGraphDef.node(i),"T",&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType);

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar;

  TIDL_getAttr_padding(tfGraphDef.node(i),"padding",&padType);
  if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str(),TIDL_UnSuportedLayer))
  {
    padType = 0;
  }
  if(padType == 0)
  {
    int32_t pad = ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW-1)*
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW)/2;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padW = pad;
    pad = ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH-1)*
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH)/2;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padH = pad;
  }
  else if(padType == 1)
  {
  }
  TIDL_getAttr_data_format(tfGraphDef.node(i),"data_format");
  if(gloab_data_format == 1)
  {
    idx1 = 3;
    idx2 = 2;
  }
  else
  {
    idx1 = 2;
    idx2 = 1;
  }
  TIDL_getAttr_value(tfGraphDef.node(i),"strides",
    &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideW,
    idx1);
  TIDL_getAttr_value(tfGraphDef.node(i),"strides",
    &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH,
    idx2);
  TIDL_getAttr_value(tfGraphDef.node(i),"dilation_rate",
    &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationW,
    idx1);
  TIDL_getAttr_value(tfGraphDef.node(i),"dilation_rate",
    &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH,
    idx2);

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numOutChannels;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
    ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] + 
    (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padH*2) -  
    ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH-1)*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.dilationH + 1))/
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.strideH) + 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
    ((pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3] + 
    (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.padW*2) -  
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
    
  if(tensor.dtype() == 1) //DT_FLOAT
  {
    float * tPtr = (float *)tensor.tensor_content().c_str();
    int32_t dataSize = tensor.tensor_content().size()/sizeof(float);
    float * params = (float *)malloc(dataSize*sizeof(float));
    memcpy(params,tPtr,sizeof(float)*dataSize);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.bufSize = dataSize;
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.weights.ptr, (void*)params);
  }
  else
  {
    printf("\nOnly float Conv2D kernel tensor is suported \n");
  }

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    (int64_t)(((int64_t)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelW * 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.kernelH * 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]) / pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.numGroups);
}

void TIDL_importBiasParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
GraphDef&             tfGraphDef)
{
 
  float * tPtr     ;
  int32_t dataSize ;
  float * params   ;
  int32_t inLayerId = 0;
  float biasVal;
  int32_t oneValue = 0;
  int32_t     layerIndex;
  layerIndex = *pLayerIndex;
  if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(1).c_str(),TIDL_ConstDataLayer))
  {
    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(1).c_str());
    params    = (float *)LOAD_PTR(orgTIDLNetStructure.TIDLPCLayers[inLayerId].layerParams.biasParams.bias.ptr);
    dataSize = 
          (pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3]);
    
  }
  else if(TIDL_isInputConstTensor(tfGraphDef,tfGraphDef.node(i).input(1)))
  {
    TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(1));
    if(tensor.tensor_content().size())
    {
      tPtr     = (float *)tensor.tensor_content().c_str();
      dataSize = tensor.tensor_content().size()/sizeof(float);
      params   = (float *)malloc(dataSize*sizeof(float));
      if(tensor.dtype() == 1) //DT_FLOAT
      {
        memcpy(params,tPtr,sizeof(float)*dataSize);
      }
      else
      {
        printf("\nOnly float Conv2D Bias tensor is suported \n");
      }
    }
    else
    {
      oneValue = 1;
      auto values = tensor.float_val();
      biasVal = values.Get(0);
    }
  }
  else
  {
    printf("\nCould not find %s input \n", tfGraphDef.node(i).input(1).c_str());
  }
  if(TIDL_isInputConv2D( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str()))
  {
    inLayerId = TIDL_getLayerIdx ( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outDataNames[0], tfGraphDef.node(i).name().c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.enableBias     = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.bias.bufSize = dataSize;
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.bias.ptr, (void*)params);
  }
  else if (TIDL_isInputInnerProduct( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str()))
  {
    inLayerId = TIDL_getLayerIdx ( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outDataNames[0], tfGraphDef.node(i).name().c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.innerProductParams.bias.bufSize = dataSize;
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.innerProductParams.bias.ptr, (void*)params);
  }
  else if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str(),TIDL_ConstDataLayer))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConstDataLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());

    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    if((oneValue == 0) && (pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3]) != dataSize)
    {
      printf("\n Two const input size of Add Layer is not matching\n");
    }
    else
    {
      dataSize = pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3];
      float * ptr = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.biasParams.bias.ptr);
      float * outPtr   = (float *)malloc(dataSize*sizeof(float));
      for (int idx = 0; idx < dataSize; idx++) 
      {
        if(oneValue)
        {
          outPtr[idx] = ptr[idx] + biasVal; 
        }
        else
        {
          outPtr[idx] = ptr[idx] + params[idx]; 
        }
      }
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.bias.ptr, (void*)outPtr);
      for (int idx = 0; idx < TIDL_DIM_MAX; idx++) 
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[idx] = pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[idx];
      }
    }          
    layerIndex++;
  }
  *pLayerIndex = layerIndex;  
}

void TIDL_importMulParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
GraphDef&             tfGraphDef)
{     
  float * tPtr     ;
  int32_t dataSize ;
  float * params   ;
  int32_t inLayerId = 0;  
  int32_t     layerIndex;
  layerIndex = *pLayerIndex;
  if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(1).c_str(),TIDL_ConstDataLayer))
  {
    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(1).c_str());
    params    = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.biasParams.bias.ptr);
    dataSize = 
          (pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3]);
    
  }
  else if(TIDL_isInputConstTensor(tfGraphDef,tfGraphDef.node(i).input(1)))
  {
    TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(1));
    tPtr     = (float *)tensor.tensor_content().c_str();
    dataSize = tensor.tensor_content().size()/sizeof(float);
    params   = (float *)malloc(dataSize*sizeof(float));
    if(tensor.dtype() == 1) //DT_FLOAT
    {
      memcpy(params,tPtr,sizeof(float)*dataSize);
    }
    else
    {
      printf("\nOnly float Mul tensor is suported \n");
    }
  }
  else
  {
    printf("\nCould not find %s input \n", tfGraphDef.node(i).input(1).c_str());
  }

  if(TIDL_isInputConv2D( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str()))
  {
    inLayerId = TIDL_getLayerIdx ( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outDataNames[0], tfGraphDef.node(i).name().c_str());
    
    float *  data      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.weights.ptr);
    
      if(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.numGroups != 
      pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1])
      {
    TIDL_kernelScale(data,params,
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.kernelW,
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.kernelH,
        (pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].inData[0].dimValues[1]/
        pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.numGroups),
        pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1]);
      }
      else
      {
        TIDL_depthWiseKernelScale(data,params,
        (pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.kernelW*
        pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.kernelW),
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1]);
  }
  }
  else if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str(),TIDL_ConstDataLayer))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConstDataLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());

    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    if((pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3]) != dataSize)
    {
      printf("\n Two const input size of Mul Layer is not matching\n");
    }
    else
    {
      float * ptr      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.biasParams.bias.ptr);
      float * outPtr   = (float *)malloc(dataSize*sizeof(float));
     
      for (int idx = 0; idx < dataSize; idx++) 
      {
        outPtr[idx] = ptr[idx] * params[idx]; 
      }
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.bias.ptr, (void*)outPtr);
      for (int idx = 0; idx < TIDL_DIM_MAX; idx++) 
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[idx] = pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[idx];
      }
    }          
    layerIndex++;
  }
  *pLayerIndex = layerIndex;  
}

void TIDL_importPrelUParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
  int32_t              i,
  int32_t              *pLayerIndex,
  int32_t              *pDataIndex,
  GraphDef&             tfGraphDef)
{
  float * tPtr;
  int32_t dataSize;
  float * params;
  int32_t inLayerId = 0;
  int32_t     layerIndex;
  int32_t dataIndex = *pDataIndex;
  int32_t status;
  layerIndex = *pLayerIndex;

  TensorProto tensor = TIDL_getConstTensor(tfGraphDef, tfGraphDef.node(i).name());
  if ((tensor.tensor_shape().dim(0).size() != 1) || (tensor.tensor_shape().dim(1).size() != 1))
  {
    printf("\nOnly Shared Prelu Parameters are suported for W and H \n");
  }

  tPtr = (float *)tensor.tensor_content().c_str();

  dataSize = tensor.tensor_content().size() / sizeof(float);
  params = (float *)malloc(dataSize*sizeof(float));
  if (tensor.dtype() == 1) //DT_FLOAT
  {
    memcpy(params, tPtr, sizeof(float)*dataSize);
  }
  else
  {
    printf("\nOnly float Prelu is suported \n");
  }

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType = TIDL_BatchNormLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0], tfGraphDef.node(i + 6).name().c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.enableRelU = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.reluType = TIDL_PRelU;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0], tfGraphDef.node(i+1).input(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if (status == -1)
  {
    printf("Could not find the requested input Data : %s !!", pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.numChannels = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_SignedChar;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];

  if (dataSize != pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1])
  {
    printf("Un-suported data size for PrelU\n");
  }
  else
  {
    float * dataBias = (float*)malloc(dataSize*sizeof(float));
    float * dataWeigths = (float*)malloc(dataSize*sizeof(float));
    
    for (int32_t j = 0; j < dataSize; j++)
    {
      dataBias[j] = 0;
      dataWeigths[j] = 1;
    }
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.ptr, dataBias);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.bias.bufSize = dataSize;
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.ptr, dataWeigths);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.weights.bufSize = dataSize;

    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.slope.ptr, params);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.batchNormParams.reluParams.slope.bufSize = dataSize;
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs =
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] *
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];


  layerIndex++;
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex;
  
}



void TIDL_importSubParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
GraphDef&             tfGraphDef)  
{
  float * tPtr     ;
  int32_t dataSize ;
  float * params   ;
  int32_t inLayerId = 0;
  int32_t     layerIndex;
  layerIndex = *pLayerIndex;
  
  if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(1).c_str(),TIDL_ConstDataLayer))
  {
    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(1).c_str());
    params    = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.biasParams.bias.ptr);
    dataSize = 
          (pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3]);
    
  }
  else if(TIDL_isInputConstTensor(tfGraphDef,tfGraphDef.node(i).input(1)))
  {
    TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(1));
    tPtr     = (float *)tensor.tensor_content().c_str();
    dataSize = tensor.tensor_content().size()/sizeof(float);
    params   = (float *)malloc(dataSize*sizeof(float));
    if(tensor.dtype() == 1) //DT_FLOAT
    {
      memcpy(params,tPtr,sizeof(float)*dataSize);
    }
    else
    {
      printf("\nOnly float Mul tensor is suported \n");
    }
  }
  else
  {
    printf("\nCould not find %s input \n", tfGraphDef.node(i).input(1).c_str());
  }

  if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str(),TIDL_ConstDataLayer))
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConstDataLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());

    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    if((pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
          pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3]) != dataSize)
    {
      printf("\n Two const input size of Mul Layer is not matching\n");
    }
    else
    {
      float * ptr = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.biasParams.bias.ptr);
      float * outPtr   = (float *)malloc(dataSize*sizeof(float));
      for (int idx = 0; idx < dataSize; idx++) 
      {
        outPtr[idx] = ptr[idx] - params[idx]; 
      }
      STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.bias.ptr, (void*)outPtr);
      for (int idx = 0; idx < TIDL_DIM_MAX; idx++) 
      {
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[idx] = pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[idx];
      }        
    }          
    layerIndex++;
  }
  else if(TIDL_isInputConstTensor(tfGraphDef,tfGraphDef.node(i).input(0)))
  {
    TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(0));
    float * ptr;
    tPtr     = (float *)tensor.tensor_content().c_str();
    dataSize = tensor.tensor_content().size()/sizeof(float);
    ptr   = (float *)malloc(dataSize*sizeof(float));
    if(tensor.dtype() == 1) //DT_FLOAT
    {
      memcpy(ptr,tPtr,sizeof(float)*dataSize);
    }
    else
    {
      printf("\nOnly float Sub tensor is suported \n");
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConstDataLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());

    for (int idx = 0; idx < dataSize; idx++) 
    {
      ptr[idx] -= params[idx]; 
    }
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.bias.ptr, (void*)ptr);
    for (int idx = 0; idx < TIDL_DIM_MAX; idx++) 
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[idx] = pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[idx];
    }
    layerIndex++;
  }          
  else
  {
    printf("\nCould not find %s input \n", tfGraphDef.node(i).input(0).c_str());
  }
  *pLayerIndex = layerIndex;    
}
 
void TIDL_importRsqrtParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
GraphDef&             tfGraphDef)  
{      
  float * tPtr     ;
  int32_t dataSize ;
  float * params   ;
  int32_t inLayerId = 0;
  int32_t     layerIndex;
  layerIndex = *pLayerIndex;
  if(TIDL_isInputLayer(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str(),TIDL_ConstDataLayer))
  {
    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConstDataLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());

    inLayerId = TIDL_getLayerIdx(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    dataSize = (pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[0] *
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[1] *
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[2] *
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[3]);

    float * ptr = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.biasParams.bias.ptr);
    float * outPtr   = (float *)malloc(dataSize*sizeof(float));
    for (int idx = 0; idx < dataSize; idx++) 
    {
      if(sqrt(ptr[idx]))
      {
        outPtr[idx] = 1/sqrt(ptr[idx]); 
      }
      else
      {
        outPtr[idx] = 0; 
      }
    }
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.bias.ptr, (void*)outPtr);
    for (int idx = 0; idx < TIDL_DIM_MAX; idx++) 
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[idx] = pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].dimValues[idx];
    }
    layerIndex++;
  }
  else 
  {
    printf("\nRsqrt Only suported on const data");
  }
  *pLayerIndex = layerIndex;   
}
 
void TIDL_importReluParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
GraphDef&             tfGraphDef)
{ 
  int32_t inLayerId = 0;      
  if(TIDL_isInputConv2D(pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str()))
  {
    inLayerId = TIDL_getLayerIdx ( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());

    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outDataNames[0], tfGraphDef.node(i).name().c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.enableRelU = 1;

    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].elementType = TIDL_UnsignedChar;

    TIDL_getAttr_type(tfGraphDef.node(i),"T",&pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].elementType);
    if((strcmp(tfGraphDef.node(i).op().c_str(),"Relu6") == 0))
    {
      pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.reluParams.reluType = TIDL_RelU6;
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.reluParams.reluType = TIDL_RelU;  
    }
  }
  else if(TIDL_isInputInnerProduct( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str()))
  {
    inLayerId = TIDL_getLayerIdx ( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outDataNames[0], tfGraphDef.node(i).name().c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.innerProductParams.activationType = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.innerProductParams.enableRelU = 1;
    

    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].elementType = TIDL_UnsignedChar;
    TIDL_getAttr_type(tfGraphDef.node(i),"T",&pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].elementType);
    if((strcmp(tfGraphDef.node(i).op().c_str(),"Relu6") == 0))
    {
      pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.innerProductParams.reluParams.reluType = TIDL_RelU6;
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.innerProductParams.reluParams.reluType = TIDL_RelU;  
    }
  }
}


void TIDL_importPoolingParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
int32_t              *pDataIndex,
GraphDef&             tfGraphDef)
{  
  int32_t padType, status;
  int32_t idx1, idx2;
  int32_t     layerIndex;
  int32_t     dataIndex; 
  int32_t inLayerId = 0;  
  layerIndex = *pLayerIndex;
  dataIndex  = *pDataIndex;  
  if(TIDL_isInputConv2D( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str()) &&
    (tfGraphDef.node(i).attr().at(std::string("ksize")).list().i(1) == 2) &&
#ifdef _WIN32
    (tfGraphDef.node(i).attr().at(std::string("ksize")).list().i(2) == 2))
#else
    (tfGraphDef.node(i).attr().at(std::string("ksize")).list().i(2) == 2) &&
    (tfGraphDef.node(i).attr().at(std::string("strides")).list().i(1) == 2) &&
	(tfGraphDef.node(i).attr().at(std::string("strides")).list().i(2) == 2))
#endif
  {
    inLayerId = TIDL_getLayerIdx ( pOrgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outDataNames[0], tfGraphDef.node(i).name().c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].layerParams.convParams.enablePooling = 1;
    pOrgTIDLNetStructure->TIDLPCLayers[inLayerId].outData[0].elementType = TIDL_UnsignedChar;

    layerIndex--;
    if(strcmp(tfGraphDef.node(i).op().c_str(),"MaxPool") == 0)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.poolingType    = 0;
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.poolingType    = 1;
    }

    TIDL_getAttr_type(tfGraphDef.node(i),"T",&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType);
    TIDL_getAttr_data_format(tfGraphDef.node(i),"data_format");
    if(gloab_data_format == 1)
    {
      idx1 = 3;
      idx2 = 2;
    }
    else
    {
      idx1 = 2;
      idx2 = 1;
    }
    TIDL_getAttr_value(tfGraphDef.node(i),"strides",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.strideW,
      idx1);
    TIDL_getAttr_value(tfGraphDef.node(i),"strides",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.strideH,
      idx2);
    TIDL_getAttr_value(tfGraphDef.node(i),"ksize",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.kernelW,
      idx1);
    TIDL_getAttr_value(tfGraphDef.node(i),"ksize",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.kernelH,
      idx2);
    TIDL_getAttr_padding(tfGraphDef.node(i),"padding",&padType);
    if(padType == 0)
    {
      int32_t pad = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.kernelW-1)/2;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.padW = pad;
      pad = (pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.kernelH-1)/2;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.padH = pad;
    }
    else if(padType == 1)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.padW = 0;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.convParams.poolParams.padH = 0;
    }


    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] /= 2; 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] /= 2; 
    layerIndex++;
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_PoolingLayer;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }
    if(strcmp(tfGraphDef.node(i).op().c_str(),"MaxPool") == 0)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType    = 0;
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType    = 1;
    }

    TIDL_getAttr_type(tfGraphDef.node(i),"T",&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].elementType;
      
    TIDL_getAttr_data_format(tfGraphDef.node(i),"data_format");
    if(gloab_data_format == 1)
    {
      idx1 = 3;
      idx2 = 2;
    }
    else
    {
      idx1 = 2;
      idx2 = 1;
    }
    TIDL_getAttr_value(tfGraphDef.node(i),"strides",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideW,
      idx1);
    TIDL_getAttr_value(tfGraphDef.node(i),"strides",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideH,
      idx2);
    TIDL_getAttr_value(tfGraphDef.node(i),"ksize",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW,
      idx1);
    TIDL_getAttr_value(tfGraphDef.node(i),"ksize",
      &pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH,
      idx2);
    //Temprory code for Global Pooling
    if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType == 1)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    }

    TIDL_getAttr_padding(tfGraphDef.node(i),"padding",&padType);
    /* Fix for TIDL-292 issue */
    if(padType == 0)  
    {
      int stride, kernel, in_size, out_size;
      kernel = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH;
      stride = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideH;
      in_size = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = out_size = 
      (in_size + stride - 1) / stride;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padH = 
      ((out_size - 1) * stride + ((kernel - 1) + 1) - in_size)/2;

      kernel = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW;
      stride = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideW;
      in_size = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = out_size = 
      (in_size + stride - 1) / stride;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padW = 
      ((out_size - 1) * stride + ((kernel - 1) + 1) - in_size)/2;      
    }
    else if(padType == 1)
    {
      int stride, in_size, kernel;
      kernel = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH;
      stride = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideH;
      in_size = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
      //(in_size + ((kernel - 1) + 1) + stride) / stride;
      (in_size - (kernel - 1) + (stride - 1)) / stride;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padH = 0;
      
      kernel = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW;
      stride = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideW;
      in_size = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
        //(in_size + ((kernel - 1) + 1) + stride) / stride;
        (in_size - (kernel - 1) + (stride - 1)) / stride;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.padW = 0;
    }

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]  = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];    
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.numChannels =  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1];

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]*
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW * 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH ;

    //Temprory code for Global Pooling
    if(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType == 1)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW = 0;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH = 0;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideW = 1;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.strideH = 1;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]  = 1;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2]  = 1;
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]  = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
    }
    layerIndex++;
  }
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;  
}

void TIDL_importMeanParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
GraphDef&             tfGraphDef)
{  
  int32_t padType, status;
  int32_t idx1, idx2;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_PoolingLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.poolingType    = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].elementType;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]  = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2]  = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]  =  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.numChannels =  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];
    
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW * 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH ; // does this have any effect?
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelW = 0;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.poolParams.kernelH = 0;
  layerIndex++;
}    

void TIDL_importConcatV2Params(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
GraphDef&             tfGraphDef)
{ 
  int32_t  j, status;    
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConcatLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  if(TIDL_hasAttr(tfGraphDef.node(i),"N"))
  {
    auto& value = tfGraphDef.node(i).attr().at(std::string("N"));
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs = value.i();
  }
  else
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 2;
  }
  TIDL_getAttr_type(tfGraphDef.node(i),"T",&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].elementType);

  TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs));
  auto& axis = tensor.int_val();
  if(gloab_data_format == 0)
  {
    if(axis.Get(0) != 3)
    {
      printf("Concat is Only suported accorss channels\n");
      exit(-1);
    }

  }
  else
  {
    if(axis.Get(0) != 1)
    {
      printf("Concat is Only suported accorss channels\n");
      exit(-1);
    }

  }
  int32_t numOuChs = 0;

  for(j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs; j++) 
  {
    strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[j],
      tfGraphDef.node(i).input(j).c_str());
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
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];

  layerIndex++;
}    

void TIDL_importSliceParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              *pLayerIndex,
int32_t              *pDataIndex,
GraphDef&             tfGraphDef)
{  
  int32_t j, status, layerIndex = *pLayerIndex;
  int32_t dataIndex  = *pDataIndex;    
  int32_t sliceNumChs[TIDL_NUM_OUT_BUFS];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_SliceLayer;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
   pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(1).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
       
  TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(0));
  auto& axis = tensor.int_val();
  if(gloab_data_format == 0)
  {
    if(axis.Get(0) != 3)
    {
      printf("Silce is Only suported accorss channels\n");
      exit(-1);
    }

  }
  else
  {
    if(axis.Get(0) != 1)
    {
      printf("Silce is Only suported accorss channels\n");
      exit(-1);
    }

  }

  if(TIDL_hasAttr(tfGraphDef.node(i),"num_slice"))
  {
    auto& value = tfGraphDef.node(i).attr().at(std::string("num_slice"));

    if(value.has_list())
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = value.list().i_size();
      for(j = 0; j < value.list().i_size(); j++)
      {
        sliceNumChs[j] = value.list().i(j);
      }
    }
    else
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = value.i();
      for(j = 0; j < value.i(); j++)
      {
        sliceNumChs[j] = 
        pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]/value.i();;
      }
    }      
  }



  int32_t numOuChs = 0;
  char numChar[10];
  for(j = 0; j < pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs; j++) 
  {
     strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],tfGraphDef.node(i).name().c_str());
     if(j)
     {
      strcat((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],":");
      strcat((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[j],itoa(j,numChar,10));
     }

    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].numDim       = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
      
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[0] = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
      
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[2] = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[3] = 
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
   
   pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dimValues[1] = 
      sliceNumChs[j];
  
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[j].dataId = dataIndex++;
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 0;
  layerIndex++;
  *pLayerIndex = layerIndex;
  *pDataIndex = dataIndex ;    
}    

void TIDL_importReshapeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
GraphDef&             tfGraphDef)
{  
  int32_t status;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_UnSuportedLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
  
  if(TIDL_isInputConstTensor(tfGraphDef,tfGraphDef.node(i).input(0)))
  {
    TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(0));
    float * tPtr = (float *)tensor.tensor_content().c_str();
    int32_t tensor_size = (tensor.tensor_content().size()/(sizeof(float)));
    float * ptr;

    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.bias.ptr, (void*)malloc(tensor_size*sizeof(float)));
    ptr = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.biasParams.bias.ptr);

    for (int idx = 0; idx < tensor_size; idx++) 
    {
      ptr[idx] = tPtr[idx]; 
    }
    if(tensor.dtype() != 1) //DT_FLOAT
    {
      printf("\nOnly DT_FLOAT tensor is suported for reshape input\n");
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = -1;
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_ConstDataLayer;

  }
  else
  {  
    status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    if(status == -1)
    {
      printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
      exit(-1);
    }
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dataId;
  }
  TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(1));
  for (int idx = 0; idx < TIDL_DIM_MAX; idx++) 
  {
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[idx] = 1; 
  }
  int32_t * tPtr = (int32_t *)tensor.tensor_content().c_str();
  int32_t reshape_dim_size = (tensor.tensor_content().size()/(sizeof(int32_t)));
  for (int idx = 0; idx < reshape_dim_size; idx++) 
  {
    if(tPtr[idx] != -1)
    {
      pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[TIDL_DIM_MAX - reshape_dim_size + idx] = tPtr[idx]; 
    }
  }

  if(tensor.dtype() != 3) //DT_INT32
  {
    printf("\nOnly DT_INT32 Reshap tensor is suported \n");
  }
  layerIndex++;
}

void TIDL_importSqueezeParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
GraphDef&             tfGraphDef)
{
  int32_t status;  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_UnSuportedLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0];

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];

  layerIndex++;
}

void TIDL_importPadParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
GraphDef&             tfGraphDef)
{ 
  int32_t status; 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_UnSuportedLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0];
  layerIndex++;
}

void TIDL_importSoftmaxParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
GraphDef&             tfGraphDef)
{ 
  int32_t status;      
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_SoftMaxLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].numDim       = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].numDim;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3];

  layerIndex++;
}

void TIDL_importMatMulParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
int32_t              i,
int32_t              layerIndex,
int32_t              dataIndex,
GraphDef&             tfGraphDef)
{
  int32_t status;  
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerType =  TIDL_InnerProductLayer;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numOutBufs = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numInBufs  = 1;
  strcpy((char*)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
  status = TIDL_getDataID(&pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0], pOrgTIDLNetStructure, layerIndex, pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
  if(status == -1)
  {
    printf("Could not find the requested input Data : %s !!",pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inDataNames[0]);
    exit(-1);
  }
  TensorProto tensor = TIDL_getConstTensor(tfGraphDef,tfGraphDef.node(i).input(1));

  //pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0] = pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0]; 
  
  if(tensor.dtype() == 1) //DT_FLOAT
  {
    float * tPtr = (float *)tensor.tensor_content().c_str();
    int32_t dataSize = tensor.tensor_content().size()/sizeof(float);
    float * params = (float *)malloc(dataSize*sizeof(float));
    memcpy(params,tPtr,sizeof(float)*dataSize);
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.weights.bufSize = dataSize;
    STORE_PTR(pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.weights.ptr, (void*)params);
  }
  else
  {
    printf("\nOnly float Conv2D kernel tensor is suported \n");
  }
  
  /* Bug fix for TIDL - 314 */
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 1;
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[TIDL_DIM_MAX-1] = tensor.tensor_shape().dim(1).size(); 

  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].numMacs = 
    (int64_t)((int64_t)pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].outData[0].dimValues[3]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[0] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[1]*
    pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[2] * pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].inData[0].dimValues[3]);
 
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.numInNodes = 
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dimValues[3] *
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dimValues[2] *
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dimValues[1];
  pOrgTIDLNetStructure->TIDLPCLayers[layerIndex].layerParams.innerProductParams.numOutNodes = 
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3] *
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] *
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[1];
  layerIndex++;
}

void TIDL_importQuantLayerParams(sTIDL_OrgNetwork_t   *pOrgTIDLNetStructure,
                                 int32_t              i,
                                 FILE                 *fp1
                                 )
{      
  int32_t zeroWeightValue;
  if ((pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer) ||
    (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer) ||
    (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer))
  {
    float min = FLT_MAX;
    float max = FLT_MIN;
    int32_t weightsElementSizeInBits = pOrgTIDLNetStructure->TIDLPCLayers[i].weightsElementSizeInBits;
    if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer)
    {
      float *  data      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.weights.ptr);
      uint32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.weights.bufSize;
      uint8_t * params = (uint8_t *)malloc(dataSize * ((weightsElementSizeInBits-1)/8 + 1));
      TIDL_findRange(data, dataSize, &min , &max, 1.0);

      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.weightsQ = 
        TIDL_QuantizeUnsignedMax((uint8_t *)params, data,dataSize, min , max,  NUM_WHGT_BITS, weightsElementSizeInBits, &zeroWeightValue);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.zeroWeightValue = zeroWeightValue;

      //if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numGroups != 
      //pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].dimValues[1])
      {
        TIDL_kernelReshape(params,
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.kernelW,
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.kernelH,
        (pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].dimValues[1]/
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.numGroups),
        pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].dimValues[1], ((weightsElementSizeInBits-1)/8 + 1));
      }
      
      if(weightsElementSizeInBits > 8)
        fwrite(params,2,dataSize,fp1);
	  else
      fwrite(params,1,dataSize,fp1);
        
      free(params);
      free(data);
      RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.weights.ptr);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.weights.bufSize = 0;

      if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.enableBias)
      {

        min = FLT_MAX;
        max = FLT_MIN;
        {
          float * biasData = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.bias.ptr);
          uint32_t biasDataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.bias.bufSize;
          TIDL_findRange(biasData, biasDataSize, &min, &max, 1.0);
        }

        data      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.bias.ptr);
        dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.bias.bufSize;
        max = abs(min) >  abs(max) ? abs(min) : abs(max);
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.biasQ =
          TIDL_QuantizeUnsignedMax(0, 0, 0, 0, max, NUM_BIAS_BITS, (NUM_BIAS_BYTES * 8), &zeroWeightValue);


        int16_t * params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
        for (int idx = 0; idx < dataSize; idx++) 
        {
          int32_t biasParam = TIDL_normalize(data[idx], 0 , max);
          params[idx] = (int16_t)TIDL_roundSat(biasParam,0,SHRT_MIN,SHRT_MAX);
        }
        fwrite(params, NUM_BIAS_BYTES,dataSize,fp1);
        free(params);
        free(data);
        RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.bias.ptr);
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.bias.bufSize = 0;
      }
      if (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.biasQ == 0)
      {
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.biasQ = 1;
      }
    }
    else if(pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_InnerProductLayer)
    {
      float *  data      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.weights.ptr);
      uint32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.weights.bufSize;
      uint8_t * params = (uint8_t *)malloc(dataSize * ((weightsElementSizeInBits-1)/8 + 1));
      TIDL_findRange(data, dataSize, &min , &max, 1.0);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.weightsQ = 
        TIDL_QuantizeUnsignedMax((uint8_t *)params, data,dataSize, min , max,  NUM_WHGT_BITS, weightsElementSizeInBits, &zeroWeightValue);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.zeroWeightValue = zeroWeightValue;

      TIDL_kernelReshape(params,
      1,
      1,
      pOrgTIDLNetStructure->TIDLPCLayers[i].inData[0].dimValues[3],
      pOrgTIDLNetStructure->TIDLPCLayers[i].outData[0].dimValues[3], ((weightsElementSizeInBits-1)/8 + 1));


      if(weightsElementSizeInBits > 8)
        fwrite(params,2,dataSize,fp1);
	  else
      fwrite(params,1,dataSize,fp1);
        
      free(params);
      free(data);
      RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.weights.ptr);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.weights.bufSize = 0;
 
      min = FLT_MAX;
      max = FLT_MIN;
      //if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.convParams.enableBias)
      {
        float * biasData = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
        uint32_t biasDataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize;
        TIDL_findRange(biasData, biasDataSize, &min, &max, 1.0 );
      }
      
      max = abs(min) >  abs(max) ? abs(min) : abs(max);
      orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.biasQ =
        TIDL_QuantizeUnsignedMax(0, 0, 0, 0, max, NUM_BIAS_BITS, (NUM_BIAS_BYTES * 8), &zeroWeightValue);


      data      = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
      dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize;
      {
        int16_t *params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
        for (int idx = 0; idx < dataSize; idx++) 
        {
          int32_t biasParam = TIDL_normalize(data[idx], 0 , max);
          params[idx] = (int16_t)TIDL_roundSat(biasParam,0,SHRT_MIN,SHRT_MAX);
        }
        fwrite(params, NUM_BIAS_BYTES,dataSize,fp1);
        free(params);
      }
      free(data);
      RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.bias.ptr);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.innerProductParams.bias.bufSize = 0;

      if (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.biasQ == 0)
      {
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.biasQ = 1;
      }
    }
    else if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerType == TIDL_BatchNormLayer)
    {
      float *  data = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.weights.ptr);
      uint32_t dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.weights.bufSize;
      uint8_t * params = (uint8_t *)malloc(dataSize * ((weightsElementSizeInBits - 1) / 8 + 1));
      TIDL_findRange(data, dataSize, &min, &max, 1.0);

      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.weightsQ =
        TIDL_QuantizeUnsignedMax((uint8_t *)params, data, dataSize, min, max, NUM_WHGT_BITS, weightsElementSizeInBits, &zeroWeightValue);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.zeroWeightValue = zeroWeightValue;

      if (weightsElementSizeInBits > 8)
        fwrite(params, 2, dataSize, fp1);
      else
        fwrite(params, 1, dataSize, fp1);

      free(params);
      free(data);
      RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.weights.ptr);
      pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.weights.bufSize = 0;

      {
        min = FLT_MAX;
        max = FLT_MIN;
        {
          float * biasData = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.bias.ptr);
          uint32_t biasDataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.bias.bufSize;
          TIDL_findRange(biasData, biasDataSize, &min, &max, 1.0);
        }

        data = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.bias.ptr);
        dataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.bias.bufSize;
        max = abs(min) > abs(max) ? abs(min) : abs(max);
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.biasQ =
          TIDL_QuantizeUnsignedMax(0, 0, 0, 0, max, NUM_BIAS_BITS, (NUM_BIAS_BYTES * 8), &zeroWeightValue);


        int16_t * params = (int16_t *)malloc(dataSize*NUM_BIAS_BYTES);
        for (int idx = 0; idx < dataSize; idx++)
        {
          int32_t biasParam = TIDL_normalize(data[idx], 0, max);
          params[idx] = (int16_t)TIDL_roundSat(biasParam, 0, SHRT_MIN, SHRT_MAX);
        }
        fwrite(params, NUM_BIAS_BYTES, dataSize, fp1);
        free(params);
        free(data);
        if (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.biasQ == 0)
        {
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.biasQ = 1;
        }
        RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.bias.ptr);
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.bias.bufSize = 0;
      }
      if (pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.reluType == TIDL_PRelU)
      {
        float * slopeData = (float *)LOAD_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.ptr);
        uint32_t slopeDataSize = pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.bufSize;
        uint8_t * params = (uint8_t *)malloc(slopeDataSize * ((weightsElementSizeInBits - 1) / 8 + 1));
        float min = FLT_MAX;
        float max = FLT_MIN;
        TIDL_findRange(slopeData, slopeDataSize, &min, &max, (1.0));
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slopeQ =
          TIDL_QuantizeUnsignedMax((uint8_t *)params, slopeData, slopeDataSize, min, max, NUM_WHGT_BITS, weightsElementSizeInBits, &zeroWeightValue);
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slopeQ /= 256;
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.zeroSlopeValue = zeroWeightValue;

        if (weightsElementSizeInBits > 8)
        {
          fwrite(params, 2, slopeDataSize, fp1);
        }
        else
        {
          fwrite(params, 1, slopeDataSize, fp1);
        }
        free(params);
        free(slopeData);
        RESET_PTR(pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.ptr);
        pOrgTIDLNetStructure->TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slope.bufSize = 0;
        if (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slopeQ == 0)
        {
          orgTIDLNetStructure.TIDLPCLayers[i].layerParams.batchNormParams.reluParams.slopeQ = 1;
        }
      }
    }
  }
}



TIDL_TFLayerMapping_t TIDL_TFLayerMap[] =
{
  { (char*)"TIDL_TFKerasPrelU",         (char*)"ConstReluNegNegReluMulAdd"   , 7 },
  { (char*)"TIDL_TFSlimBatchNorm",      (char*)"MulConstSub"                 , 10 },
  { (char*)"TIDL_TFKerasFlatten",       (char*)"ResahpeSqueeze"              , 10 }
};

int32_t tf_getLayreTypeMapIdx(char* layerName)
{
  int32_t idx;
  for (idx = 0; idx < (sizeof(TIDL_TFLayerMap) / sizeof(TIDL_TFLayerMapping_t)); idx++)
  {
    if(strcmp(layerName, TIDL_TFLayerMap[idx].layerName) == 0)
    {
      return (idx);
    }
  }
  return -1;
}

int32_t tf_isLayerType(const char* layerName, int32_t  startNode, GraphDef &tfGraphDef)
{
  int32_t i, numOps;
  int32_t mapIdx = tf_getLayreTypeMapIdx((char *)layerName);
  if (mapIdx != -1)
  {
    char layerOpsString[300] = "";
    numOps = TIDL_TFLayerMap[mapIdx].NumOps;
    for (i = 0; ((i < numOps) && ((startNode + i) < tfGraphDef.node_size())); i++)
    {
      strcat(layerOpsString, tfGraphDef.node(startNode + i).op().c_str());
    }
    if (strcmp(layerOpsString, TIDL_TFLayerMap[mapIdx].layerOpsString) == 0)
    {
      return (1);
    }
  }
  return (0);
}


void tf_import(tidl_import_config * params)
{
  int32_t                    i,j;
  int32_t                    layerNum;
  int32_t                    inputSize;
  int32_t                    pad,stride;
  int32_t                    layerIndex;
  int32_t                    tiLayerIndex;
  int32_t                    dataIndex;
  int64_t                    totalMacs = 0;
  const uint8_t             *name;
  const uint8_t             *inputName[10];
  const uint8_t             *outputName;
  GraphDef           tfGraphDef;
  int32_t status;
  int32_t                    dataSize;
  int32_t                    id;
  FILE * fp0;
  FILE * fp1;
  int paramSet  = 0;
  int conv2DRandParams = 0;
  string attrKey;
  int32_t inLayerId = 0;  
  int32_t weightsElementSizeInBits;
  int overWritefirstNode = 1 ;
  
  if((params->inWidth == -1) || (params->inHeight == -1) || (params->inNumChannels == -1))
  {
    overWritefirstNode = 0;
  }  
  string key = "value";

  printf("TF Model File : %s  \n",(const char *)params->inputNetFile);

  TIDL_readProtoFromBinaryFile((const char *)params->inputNetFile, &tfGraphDef);
  fp0 = fopen((const char *)params->outputNetFile, "wb+");
  if(fp0 == NULL)
  {
    printf("Could not open %s file for writing \n",(const char *)params->outputNetFile);
  }

  fp1 = fopen((const char *)params->outputParamsFile, "wb+");
  if(fp1 == NULL)
  {
    printf("Could not open %s file for writing \n",(const char *)params->outputParamsFile);
  }


  gloab_data_format = 0;

  layerIndex = 0;
  dataIndex  = 0;

  for (i = 0; i < tfGraphDef.node_size(); i++) 
  {
    if((strcmp(tfGraphDef.node(i).op().c_str(),"Placeholder") == 0))
    {
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].layerType = TIDL_DataLayer;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs  = -1;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = 1;
      strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
      strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());

      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex++;
      if(TIDL_hasAttr(tfGraphDef.node(i),"shape"))
      {
        auto& shape = tfGraphDef.node(i).attr().at(std::string("shape")).shape();
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].numDim = shape.dim_size();

        if(gloab_data_format == 0)
        {
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3] = shape.dim(2).size();
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] = shape.dim(1).size();
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[1] = shape.dim(3).size();
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 1; // Set 1 as default 
          if(shape.dim(0).size() > 0)
          {
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] = shape.dim(0).size();
          }            
        }
        else
        {
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3] = shape.dim(3).size();
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] = shape.dim(2).size();
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[1] = shape.dim(1).size();
          orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 1; // Set 1 as default
          if(shape.dim(0).size() > 0)
          {
            orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] = shape.dim(0).size();           
          }
        }
      }
      else
      {
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].numDim = 4;
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 224 ;
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 224 ;
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 3;
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 1;
      }
      //orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 256;
      //orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 256;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].elementType = gParams.inElementType;
      //orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].elementType = TIDL_UnsignedChar;
      //TIDL_getAttr_type(tfGraphDef.node(i),"dtype",&orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].elementType);
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataQ = gParams.inQuantFactor;
      layerIndex++;
    }
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
  
  for (i = 0; i < tfGraphDef.node_size(); i++) 
  {
    //printf("\n Parsing node %4d: %s  \n", i, tfGraphDef.node(i).name().c_str());    
    //Set the weights size in bits
    weightsElementSizeInBits = orgTIDLNetStructure.TIDLPCLayers[layerIndex].weightsElementSizeInBits = NUM_WHGT_BITS;
    if (tf_isLayerType("TIDL_TFKerasPrelU", i, tfGraphDef))
    {
      TIDL_importPrelUParams(&orgTIDLNetStructure, i, &layerIndex, &dataIndex,
        tfGraphDef);
      i += 6;
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Const") == 0) ||
       (strcmp(tfGraphDef.node(i).op().c_str(),"Placeholder") == 0) ||
       (strcmp(tfGraphDef.node(i).op().c_str(),"Identity") == 0))      
    {
      continue;
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Conv2D") == 0) || (strcmp(tfGraphDef.node(i).op().c_str(),"DepthwiseConv2dNative") == 0))
    {
      TIDL_importConvParams(&orgTIDLNetStructure, i, layerIndex, dataIndex, 
      tfGraphDef);
      layerIndex++;
      dataIndex++;           
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"BiasAdd") == 0) || 
      (strcmp(tfGraphDef.node(i).op().c_str(),"Add") == 0))
    {
      TIDL_importBiasParams(&orgTIDLNetStructure, i, &layerIndex, 
      tfGraphDef);
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Mul") == 0))
    {
      TIDL_importMulParams(&orgTIDLNetStructure, i, &layerIndex, 
      tfGraphDef);      
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Sub") == 0))
    {
      TIDL_importSubParams(&orgTIDLNetStructure, i, &layerIndex, 
      tfGraphDef); 
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Rsqrt") == 0))
    {
      TIDL_importRsqrtParams(&orgTIDLNetStructure, i, &layerIndex, 
      tfGraphDef); 
    }    
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Relu") == 0) || (strcmp(tfGraphDef.node(i).op().c_str(),"Relu6") == 0))
    {
      TIDL_importReluParams(&orgTIDLNetStructure, i, layerIndex,  
      tfGraphDef);       
    }    
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"FusedBatchNorm") == 0))
    {
      if(TIDL_isInputConv2D( &orgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str()))
      {
        inLayerId = TIDL_getLayerIdx ( &orgTIDLNetStructure, layerIndex, tfGraphDef.node(i).input(0).c_str());
        strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[inLayerId].outDataNames[0], tfGraphDef.node(i).name().c_str());
      }
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"MaxPool") == 0) || 
            (strcmp(tfGraphDef.node(i).op().c_str(),"AvgPool") == 0))
    {
      TIDL_importPoolingParams(&orgTIDLNetStructure, i, &layerIndex,  
      &dataIndex, tfGraphDef);      
    }    
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Mean") == 0))
    {
      TIDL_importMeanParams(&orgTIDLNetStructure, i, layerIndex,  
      dataIndex, tfGraphDef);  
      layerIndex++;
      dataIndex++; 
    }    
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"ConcatV2") == 0))
    {
      TIDL_importConcatV2Params(&orgTIDLNetStructure, i, layerIndex,  
      dataIndex, tfGraphDef);  
      layerIndex++;
      dataIndex++;       
    }    
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Slice") == 0))
    {
      TIDL_importSliceParams(&orgTIDLNetStructure, i, &layerIndex,  
      &dataIndex, tfGraphDef);  
    }    
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Reshape") == 0))
    {
      TIDL_importReshapeParams(&orgTIDLNetStructure, i, layerIndex,  
      dataIndex, tfGraphDef);  
      layerIndex++;       
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Squeeze") == 0))
    {
      TIDL_importSqueezeParams(&orgTIDLNetStructure, i, layerIndex,  
      tfGraphDef);  
      layerIndex++; 
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Pad") == 0))
    {
      TIDL_importPadParams(&orgTIDLNetStructure, i, layerIndex,  
      tfGraphDef);  
      layerIndex++; 
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"Softmax") == 0))
    {
      TIDL_importSoftmaxParams(&orgTIDLNetStructure, i, layerIndex,  
      dataIndex, tfGraphDef);  
      layerIndex++;
      dataIndex++;        
    }
    else if((strcmp(tfGraphDef.node(i).op().c_str(),"MatMul") == 0))
    {
      TIDL_importMatMulParams(&orgTIDLNetStructure, i, layerIndex,  
      dataIndex, tfGraphDef);  
      layerIndex++;
      dataIndex++;        
    }
    else
    {
      printf(" Op Type %s is Not suported will be By passed \n",tfGraphDef.node(i).op().c_str());
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].layerType =  TIDL_UnSuportedLayer;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numOutBufs = 1;
      strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].name,tfGraphDef.node(i).name().c_str());
      strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].outDataNames[0],tfGraphDef.node(i).name().c_str());
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dataId = dataIndex;

      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numInBufs  = 1;
      strcpy((char*)orgTIDLNetStructure.TIDLPCLayers[layerIndex].inDataNames[0],tfGraphDef.node(i).input(0).c_str());
      status = TIDL_getDataID(&orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0], &orgTIDLNetStructure, layerIndex, orgTIDLNetStructure.TIDLPCLayers[layerIndex].inDataNames[0]);
      if(status == -1)
      {
        printf("Could not find the requested input Data : %s !!",orgTIDLNetStructure.TIDLPCLayers[layerIndex].inDataNames[0]);
        exit(-1);
      }
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].numDim       = 
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].numDim;
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] = 
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dimValues[0];
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[1] = 
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dimValues[1];
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] = 
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dimValues[2];
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3] = 
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].inData[0].dimValues[3];
      orgTIDLNetStructure.TIDLPCLayers[layerIndex].numMacs = 
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[0] * orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[1]*
        orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[2] * orgTIDLNetStructure.TIDLPCLayers[layerIndex].outData[0].dimValues[3];

      layerIndex++;
    }  
  }

  for (i = 0; i < layerIndex; i++) 
  {
    if(orgTIDLNetStructure.TIDLPCLayers[i].layerType == TIDL_ConvolutionLayer)
    {
      if((orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.kernelW  == 1) &&
        (orgTIDLNetStructure.TIDLPCLayers[i].layerParams.convParams.kernelH  == 1) &&
        (orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[1] == 1) &&
        (orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[2] == 1))
      {
        orgTIDLNetStructure.TIDLPCLayers[i].layerType = TIDL_InnerProductLayer;
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[3] = orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[1];
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[1] = 1;
        orgTIDLNetStructure.TIDLPCLayers[i].outData[0].elementType = TIDL_SignedChar;
        
        TIDL_UpdateInDataBuff(&orgTIDLNetStructure,layerIndex,orgTIDLNetStructure.TIDLPCLayers[i].outData[0]);

        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.enableRelU     = 0;
        /* Bug fix for TIDL - 314 */
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.numInNodes = 
          orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[3] *
          orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[2] *
          orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[1];
        orgTIDLNetStructure.TIDLPCLayers[i].layerParams.innerProductParams.numOutNodes = 
          orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[3];
      }
    }
  }

  /* Quantize Layer Params */
  for (i = 0; i < layerIndex; i++) 
  {
    TIDL_importQuantLayerParams(&orgTIDLNetStructure, i, fp1);
  }
  printf(" Num of Layer Detected : %3d \n",layerIndex);

  tIDLNetStructure.dataElementSize    = 1;
  tIDLNetStructure.biasElementSize    = 2;
  tIDLNetStructure.weightsElementSize = ((weightsElementSizeInBits-1)/8 + 1); //1;
  tIDLNetStructure.slopeElementSize   = tIDLNetStructure.weightsElementSize;
  tIDLNetStructure.interElementSize   = 1;
  tIDLNetStructure.quantizationStyle  = TIDL_quantStyleDynamic;
  tiLayerIndex = 0;
  tIDLNetStructure.strideOffsetMethod = TIDL_strideOffsetCenter;
  
  for (i = 0; i < layerIndex; i++) 
  {
    if((orgTIDLNetStructure.TIDLPCLayers[i].layerType != TIDL_UnSuportedLayer)&&
      (orgTIDLNetStructure.TIDLPCLayers[i].layerType != TIDL_ConstDataLayer))
    {
      tIDLNetStructure.TIDLLayers[tiLayerIndex].layerType   = orgTIDLNetStructure.TIDLPCLayers[i].layerType;
      tIDLNetStructure.TIDLLayers[tiLayerIndex].layerParams = orgTIDLNetStructure.TIDLPCLayers[i].layerParams;
      tIDLNetStructure.TIDLLayers[tiLayerIndex].numInBufs   = orgTIDLNetStructure.TIDLPCLayers[i].numInBufs;
      tIDLNetStructure.TIDLLayers[tiLayerIndex].numOutBufs  = orgTIDLNetStructure.TIDLPCLayers[i].numOutBufs;
	  tIDLNetStructure.TIDLLayers[tiLayerIndex].weightsElementSizeInBits = orgTIDLNetStructure.TIDLPCLayers[i].weightsElementSizeInBits;
	  
      if(tIDLNetStructure.TIDLLayers[tiLayerIndex].layerType == TIDL_DataLayer)
      {
        tIDLNetStructure.TIDLLayers[tiLayerIndex].layersGroupId      = 0;
      }
      else
      {
        tIDLNetStructure.TIDLLayers[tiLayerIndex].coreID             = 1;
        tIDLNetStructure.TIDLLayers[tiLayerIndex].layersGroupId      = 1;
      }

      printf("%3d, %-30s",tiLayerIndex, TIDL_LayerString[orgTIDLNetStructure.TIDLPCLayers[i].layerType]);
      printf("%3d, %3d ,%3d ,",tIDLNetStructure.TIDLLayers[tiLayerIndex].layersGroupId, orgTIDLNetStructure.TIDLPCLayers[i].numInBufs,orgTIDLNetStructure.TIDLPCLayers[i].numOutBufs);

      for (j = 0; j < orgTIDLNetStructure.TIDLPCLayers[i].numInBufs; j++) 
      {
        printf("%3d ,",orgTIDLNetStructure.TIDLPCLayers[i].inData[j].dataId);
        tIDLNetStructure.TIDLLayers[tiLayerIndex].inData[j]   = orgTIDLNetStructure.TIDLPCLayers[i].inData[j];

      }
      for (j = (orgTIDLNetStructure.TIDLPCLayers[i].numInBufs > 0 ? orgTIDLNetStructure.TIDLPCLayers[i].numInBufs : 0); j < 8; j++) 
      {
        printf("  x ,");
      }
      printf("%3d ,",orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dataId);
      for (j = 0; j < orgTIDLNetStructure.TIDLPCLayers[i].numOutBufs; j++) 
      {
      tIDLNetStructure.TIDLLayers[tiLayerIndex].outData[j]   = orgTIDLNetStructure.TIDLPCLayers[i].outData[j];

      }
      for (j = 0; j < TIDL_DIM_MAX; j++) 
      {
        printf("%5d ,",orgTIDLNetStructure.TIDLPCLayers[i].inData[0].dimValues[j]);
      }

      for (j = 0; j < TIDL_DIM_MAX; j++) 
      {
        printf("%5d ,",orgTIDLNetStructure.TIDLPCLayers[i].outData[0].dimValues[j]);
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

  for (i = 0; i < tiLayerIndex; i++) 
  {
    tIDLNetStructure.TIDLLayers[tiLayerIndex].layerType   = TIDL_DataLayer;
    tIDLNetStructure.TIDLLayers[tiLayerIndex].numInBufs   = 0;
    tIDLNetStructure.TIDLLayers[tiLayerIndex].numOutBufs  = -1;
    tIDLNetStructure.TIDLLayers[tiLayerIndex].coreID      = 255;

    if(tIDLNetStructure.TIDLLayers[i].layerType != TIDL_DataLayer)
    {
      for (j = 0 ; j < tIDLNetStructure.TIDLLayers[i].numOutBufs; j++) 
      {
        if(!TIDL_isDataBufUsed(tIDLNetStructure.TIDLLayers[i].outData[j].dataId, &tIDLNetStructure, tiLayerIndex))
        {
          tIDLNetStructure.TIDLLayers[tiLayerIndex].inData[tIDLNetStructure.TIDLLayers[tiLayerIndex].numInBufs] = tIDLNetStructure.TIDLLayers[i].outData[j];
          tIDLNetStructure.TIDLLayers[tiLayerIndex].numInBufs++;
        }
      }
    }
  }
  tIDLNetStructure.numLayers = tiLayerIndex + 1;


  printf("Total Giga Macs : %4.4f\n", ((float)totalMacs/1000000000));
  if(fp1 != NULL)
  {
    fclose(fp1);
  }
  fwrite(&tIDLNetStructure,1,sizeof(tIDLNetStructure),fp0);
  if(fp0 != NULL)
  {
    fclose(fp0);
  }
}
