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

#ifndef TIDL_IMPORT_COMMONH_
#define TIDL_IMPORT_COMMONH_ 1


int32_t TIDL_QuantizeUnsignedMax(uint8_t * params, float * data, int32_t dataSize, float min, float max, int32_t numBits, int32_t weightsElementSizeInBits, int32_t * zeroWeightValue);

int32_t TIDL_normalize(float data, float min, float max);

bool TIDL_readProtoFromTextFile(const char* fileName, Message* proto);

bool TIDL_readProtoFromBinaryFile(const char* fileName, Message* proto);

int32_t TIDL_getDataID(sTIDL_DataParams_t *data, 
sTIDL_OrgNetwork_t * pOrgTIDLNetStructure,
int32_t            numLayer, 
int8_t             *bufName);

int32_t TIDL_isDataBufUsed(int32_t           dataId, 
sTIDL_Network_t   *pTIDLNetStructure,
int32_t           numLayer);
int32_t TIDL_isInputConv2D(sTIDL_OrgNetwork_t   *pOrgTIDLNetStruct,
int32_t              numLayer, 
const char           *bufName);
void TIDL_UpdateInDataBuff(sTIDL_OrgNetwork_t * pOrgTIDLNetStructure, 
uint32_t numLayers, sTIDL_DataParams_t dataBuf);

void TIDL_findRange(float * data, int32_t dataSize, float * minOut, float * maxOut, float scale);
int64_t TIDL_roundSat(int64_t val, uint8_t bits, int64_t min, int64_t max);
int32_t TIDL_findSymQ(float  min, float max);
void TIDL_setConv2dKernelType(sTIDL_Network_t   *pTIDLNetStructure, int32_t tiLayerIndex);
#define NUM_WHGT_BITS   (gParams.numParamBits)
#define NUM_BIAS_BITS   (15U)
#define NUM_BIAS_BYTES   (((NUM_BIAS_BITS + 15U) >> 4) << 1)

typedef struct {
  char           *layerName;
  char           *layerOpsString;
  uint32_t       NumOps;
} TIDL_TFLayerMapping_t;


#ifdef PLATFORM_64BIT
#define MAX_NUM_PTRS_TO_STORE (TIDL_NUM_MAX_LAYERS*10)

#define STORE_PTR(dst, src) \
    sBufPtrInd++; \
    if(sBufPtrInd == (MAX_NUM_PTRS_TO_STORE)) { \
        printf("Out of memory for storing pointers! Increase MAX_NUM_PTRS_TO_STORE.\n"); \
            exit(-1); \
    } \
    sBuffPtrs[sBufPtrInd] = src; \
    dst = sBufPtrInd;  

#define LOAD_PTR(ptr) sBuffPtrs[ptr] 
#define RESET_PTR(ptr) ptr = 0
#else
#define STORE_PTR(dst, src)  dst = src
#define LOAD_PTR(ptr) ptr 
#define RESET_PTR(ptr) ptr = NULL
#endif

#endif /*TIDL_IMPORT_COMMONH_ */
