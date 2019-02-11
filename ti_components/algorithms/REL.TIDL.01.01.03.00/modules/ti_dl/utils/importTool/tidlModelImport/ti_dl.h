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


/**
----------------------------------------------------------------------------
@file    ti_dl.h
@brief     This file defines the ivision interface for TI deep learning libary
@version 0.1 (Oct 2016) : Initial Code [ADK]
@version 0.5 (Jan 2017) : Cleaned up [ADK]
----------------------------------------------------------------------------
*/

#ifndef TIDL_H_
#define TIDL_H_ 1

#include "itidl_ti.h"

typedef enum
{
  TIDL_ConstDataLayer       = TIDL_UnSuportedLayer+1,
  TIDL_PriorBoxLayer         ,
  TIDL_PermuteLayer          ,
  TIDL_ReshapeLayer          ,  
}eTIDL_PCLayerType;

extern const char * TIDL_LayerString[];
#define TIDL_NUM_MAX_PC_LAYERS (1024)

typedef struct {
    sTIDL_LayerParams_t layerParams;
    int32_t layerType;
    int32_t numInBufs;
    int32_t numOutBufs;
    int64_t numMacs;
    int8_t  name[TIDL_STRING_SIZE];
    int8_t  inDataNames[TIDL_NUM_IN_BUFS][TIDL_STRING_SIZE];   
    int8_t  outDataNames[TIDL_NUM_OUT_BUFS][TIDL_STRING_SIZE];
    sTIDL_DataParams_t inData[TIDL_NUM_IN_BUFS];  
    sTIDL_DataParams_t outData[TIDL_NUM_OUT_BUFS]; 
    
    int32_t weightsElementSizeInBits;  //kernel weights in bits
    
}sTIDL_LayerPC_t;

typedef struct {
    sTIDL_LayerPC_t TIDLPCLayers[TIDL_NUM_MAX_PC_LAYERS];
    int32_t numLayers;

}sTIDL_OrgNetwork_t;


#endif  /* TI_DL_H_ */

/* =========================================================================*/
/*  End of file:  ti_od_cnn.h                                               */
/* =========================================================================*/
