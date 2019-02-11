/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <vcop.h>

#include "ti_file_io.h"

#include "evestarterware.h"
#include "alg_osal.h"

#include "xdais_types.h"

#include "iremap_merge_ti.h"

#include "convert_map.h"
#include "remap_common.h"
#include "stereoVision_config.h"
#include "rectify.h"
#include "eve_profile.h"

void remapNatc(uint8_t *srcY, uint8_t *srcUV, uint8_t *dstY, uint8_t *dstUV, RemapParms *params);
void stereovision_getLeftBlockMap(unsigned char **pSrcBlkMapLeft, unsigned int *blockMap_LEN, sConvertMap *mapStruct);
void stereovision_getRightBlockMap(unsigned char **pSrcBlkMapRight, unsigned int *blockMap_LEN, sConvertMap *mapStruct);

#define PRINT_ERRORE_MSG() TEST_PRINTF("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

/* Defined in stereoVision_tb.c */
int32_t TestApp_AllocMemRecords(IALG_MemRec * memRec,int32_t numMemRec);
int32_t TestApp_FreeMemRecords(IALG_MemRec * memRec,int32_t numMemRec);

typedef struct IM_Fxns
{
    IVISION_Fxns * ivision;

} IM_Fxns;

int32_t rectify(sstereoVision_Config * gConfig_stereoVision, uint8_t *leftSrc, uint8_t*rightSrc, uint8_t *leftDst, uint8_t *rightDst) {
    RemapParms     *leftParams;
    RemapParms     *rightParams;
    RemapStat       stat;
    uint32_t *coordMapLeft, *coordMapRight;
    uint32_t lengthOfConvertedMap;
    uint8_t *convertedMapLeft, *convertedMapRight;
    char filepath[256];
    char filepath2[256];
    TI_FILE *fid;
    IM_Fxns          *leftHandle;
    IM_Fxns          *rightHandle;
    REMAP_MERGE_TI_CreateParams   leftCreateParams;
    REMAP_MERGE_TI_CreateParams   rightCreateParams;
    IVISION_InArgs    inArgs;
    IVISION_InBufs    inBufs;
    IVISION_OutArgs   outArgs;
    IVISION_OutBufs   outBufs;
    /*-----------------------------------------------------------------
	  For test purpose it is allocated in stack. Application may get
	  this descriptors from its buffer manager
	-----------------------------------------------------------------*/
    IVISION_BufDesc   inputBlkBufDesc, lutBlkBufDesc;
    IVISION_BufDesc  *inBufDescList[4]; /* Can be set to 2 as we are not doing any merging */
    IVISION_BufDesc   outputBlkBufDesc;
    IVISION_BufDesc  *outBufDescList[1];

    uint32_t        srcStride, roiWidth, roiHeight, dstStride, srcHeight;

    /*--------------------------------------------------------------------------*/
    /*Create memory handle for ARP32 DMEM.                                      */
    /*--------------------------------------------------------------------------*/
    uint32_t         blockMap_LEN, numMemRec;
    IALG_MemRec    *leftMemRec;
    IALG_MemRec    *rightMemRec;
    uint8_t *srcBlkMapLeft, *srcBlkMapRight;
    int32_t i;

    int32_t status= IALG_EOK;

    leftMemRec  = NULL;
    rightMemRec  = NULL;
    coordMapLeft= NULL;
    coordMapRight= NULL;
    srcBlkMapLeft= NULL;
    srcBlkMapRight= NULL;
    convertedMapLeft=  NULL;
    convertedMapRight= NULL;

    srcStride                           = gConfig_stereoVision->remapWidth;
    srcHeight                           = gConfig_stereoVision->remapHeight;
    dstStride                           = gConfig_stereoVision->remapWidth;
    roiWidth                            = gConfig_stereoVision->remapWidth;
    roiHeight                           = gConfig_stereoVision->remapHeight;

    rightParams                         = &rightCreateParams.remapParams;
    leftParams                          = &leftCreateParams.remapParams;

    rightParams->maps.isSrcMapFloat          = 0;
    rightParams->maps.srcFormat              = U8BIT;
    rightParams->maps.qShift                 = 2;
    rightParams->interpolationLuma           = BILINEAR;
    rightParams->interpolationChroma         = BILINEAR;
    rightParams->rightShift                  = 0;
    rightParams->sat_high                    = 255;
    rightParams->sat_high_set                = 255;
    rightParams->sat_low                     = 0;
    rightParams->sat_low_set                 = 0;
    rightCreateParams.dstFormat              = U8BIT;
    rightCreateParams.enableMerge            = 0;

    rightParams->maps.srcImageDim.width      = srcStride;
    rightParams->maps.srcImageDim.height     = srcHeight;
    rightParams->maps.mapDim.width           = roiWidth;
    rightParams->maps.mapDim.height          = roiHeight;

    rightParams->maps.outputBlockDim.width   = 128;
    rightParams->maps.outputBlockDim.height  = 8;

    memcpy(&leftCreateParams, &rightCreateParams, sizeof(rightCreateParams));

    if (gConfig_stereoVision->isRectifyMapInEveFormat== 1) {
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision->remapLeft);
        if ((fid= FOPEN(filepath,"rb"))== NULL) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }

        FREAD((void*)&lengthOfConvertedMap, 4,  1, fid);

        if ( (convertedMapLeft = (uint8_t*)malloc(lengthOfConvertedMap)) == NULL){
            status= IALG_EFAIL;
            goto EXIT;
        }

        FREAD((void*)convertedMapLeft, 1,  lengthOfConvertedMap, fid);
        FCLOSE(fid);

        rectify_getBlockMap(&srcBlkMapLeft, &blockMap_LEN, &leftParams->maps, convertedMapLeft);

        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision->remapRight);
        if ((fid= FOPEN(filepath,"rb"))== NULL) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }

        FREAD((void*)&lengthOfConvertedMap, 4,  1, fid);

        if ((convertedMapRight = (uint8_t*)malloc(lengthOfConvertedMap)) == NULL){
            status= IALG_EFAIL;
            goto EXIT;
        }

        FREAD((void*)convertedMapRight, 1,  lengthOfConvertedMap, fid);
        FCLOSE(fid);

        rectify_getBlockMap(&srcBlkMapRight, &blockMap_LEN, &rightParams->maps, convertedMapRight);

    }
    if (gConfig_stereoVision->isRectifyMapInEveFormat== 2) {
        stereovision_getLeftBlockMap(&srcBlkMapLeft, &blockMap_LEN, &leftParams->maps);
        stereovision_getRightBlockMap(&srcBlkMapRight, &blockMap_LEN, &rightParams->maps);
    }
    else {
        blockMap_LEN = convertMap_bbApproach_getMemorysizeBlockMap(&leftParams->maps);

        if ( ((int32_t)blockMap_LEN == -1) || (srcBlkMapLeft = (uint8_t*)malloc(blockMap_LEN)) == NULL || (srcBlkMapRight = (uint8_t*)malloc(blockMap_LEN)) == NULL){
            status= IALG_EFAIL;
            goto EXIT;
        }

        /*********  LUT generation for Left ************/
        /* Below is executed in case the TLU passed is in (X,Y) format, which require calling convertMap_bbApproach() */
        coordMapLeft= (uint32_t*)malloc(sizeof(uint32_t)*2*srcStride*srcHeight);
        assert(coordMapLeft!= NULL);

        leftParams->maps.srcMap = (void*)coordMapLeft;

#ifdef _IDENTITY_MAP
        {
            uint32_t r,c;
            for (r=0; r<srcHeight;r++) {
                for(c=0;c<srcStride;c++){
                    *((uint32_t*)params->maps.srcMap + 2*c + 2*r*srcStride) = c << params->maps.qShift;
                    *((uint32_t*)params->maps.srcMap + 2*c + 1 + 2*r*srcStride) = r << params->maps.qShift;
                }
            }
        }
#else
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision->remapLeft);
        if ((fid= FOPEN(filepath,"rb"))== NULL) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }
        FREAD((void*)leftParams->maps.srcMap, 4,  2*srcStride*srcHeight, fid);
        FCLOSE(fid);
#endif
        status =  convertMap_bbApproach(&leftParams->maps, &stat, srcBlkMapLeft);
        if (status == -1) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }

        if (gConfig_stereoVision->saveRectifyMapInEveFormat== 1) {
            /* First save the binary version for left map */
            i = strlen((const char *)gConfig_stereoVision->remapLeft);
            memcpy(filepath2, gConfig_stereoVision->remapLeft, i - 4);
            filepath2[i - 4] = 0;
            sprintf(filepath, "../testvecs/%s_converted.bin", filepath2);

            if ((fid= FOPEN(filepath,"wb"))== NULL) {
                PRINT_ERRORE_MSG();
                goto EXIT;
            }

            lengthOfConvertedMap= sizeof(leftParams->maps) + sizeof(blockMap_LEN) + blockMap_LEN;
            FWRITE(&lengthOfConvertedMap, 1,  sizeof(lengthOfConvertedMap), fid);
            FWRITE((void*)&leftParams->maps, 1,  sizeof(leftParams->maps), fid);
            FWRITE((void*)&blockMap_LEN, 1,  sizeof(blockMap_LEN), fid);
            FWRITE((void*)srcBlkMapLeft, 1,  blockMap_LEN, fid);
            FCLOSE(fid);

            /* Then save the *.c version */
            i = strlen(filepath);
            filepath[i-3] = 'c';
            filepath[i-2] = 0;

            if ((fid= FOPEN(filepath,"wt"))== NULL) {
                PRINT_ERRORE_MSG();
                goto EXIT;
            }

            FPRINTF(fid,"#include \"remap_common.h\"\n\n");
            FPRINTF(fid,"far unsigned char srcBlkMapLeft[%d]={\n", blockMap_LEN);
            for (i=0; i<blockMap_LEN-1; i++) {
                FPRINTF(fid, "%d,\n", srcBlkMapLeft[i]);
            }
            FPRINTF(fid, "%d };\n\n", srcBlkMapLeft[blockMap_LEN-1]);

            FPRINTF(fid,"void stereovision_getLeftBlockMap(unsigned char **pSrcBlkMapLeft, unsigned int *blockMap_LEN, sConvertMap *mapStruct){\n\n");
            FPRINTF(fid,"  *pSrcBlkMapLeft= (unsigned char*)&srcBlkMapLeft[0];\n");
            FPRINTF(fid,"  *blockMap_LEN= %d;\n", blockMap_LEN);
            FPRINTF(fid,"  mapStruct->outputBlockDim.width= %d;\n", leftParams->maps.outputBlockDim.width);
            FPRINTF(fid,"  mapStruct->outputBlockDim.height= %d;\n", leftParams->maps.outputBlockDim.height);
            FPRINTF(fid,"  mapStruct->maxInputBlockDim.width= %d;\n", leftParams->maps.maxInputBlockDim.width);
            FPRINTF(fid,"  mapStruct->maxInputBlockDim.height= %d;\n", leftParams->maps.maxInputBlockDim.height);
            FPRINTF(fid,"  mapStruct->maxInputBlockSize= %d;\n", leftParams->maps.maxInputBlockSize);
            FPRINTF(fid,"  mapStruct->maxNumPixelsinTile= %d;\n", leftParams->maps.maxNumPixelsinTile);
            FPRINTF(fid,"  mapStruct->qShift= %d;\n", leftParams->maps.qShift);
            FPRINTF(fid,"  return;\n}\n");

            FCLOSE(fid);
        }


        /*********  LUT generation for Right ************/
        coordMapRight= (uint32_t*)malloc(sizeof(uint32_t)*2*srcStride*srcHeight);
        assert(coordMapRight!= NULL);

        rightParams->maps.srcMap = (void*)coordMapRight;
#ifdef _IDENTITY_MAP
        {
            uint32_t r,c;
            for (r=0; r<srcHeight;r++) {
                for(c=0;c<srcStride;c++){
                    *((uint32_t*)params->maps.srcMap + 2*c + 2*r*srcStride) = c << params->maps.qShift;
                    *((uint32_t*)params->maps.srcMap + 2*c + 1 + 2*r*srcStride) = r << params->maps.qShift;
                }
            }
        }
#else
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision->remapRight);
        if ((fid= FOPEN(filepath,"rb"))== NULL) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }
        FREAD((void*)rightParams->maps.srcMap, 4,  2*srcStride*srcHeight, fid);
        FCLOSE(fid);
#endif
        status =  convertMap_bbApproach(&rightParams->maps, &stat, srcBlkMapRight);
        if (status == -1) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }

        if (gConfig_stereoVision->saveRectifyMapInEveFormat== 1) {
            /* First save the binary version for right map */
            i = strlen((const char *)gConfig_stereoVision->remapRight);
            memcpy(filepath2, gConfig_stereoVision->remapRight, i - 4);
            filepath2[i - 4] = 0;
            sprintf(filepath, "../testvecs/%s_converted.bin", filepath2);

            if ((fid= FOPEN(filepath,"wb"))== NULL) {
                PRINT_ERRORE_MSG();
                goto EXIT;
            }

            lengthOfConvertedMap= sizeof(rightParams->maps) + sizeof(blockMap_LEN) + blockMap_LEN;
            FWRITE(&lengthOfConvertedMap, 1,  sizeof(lengthOfConvertedMap), fid);
            FWRITE((void*)&rightParams->maps, 1,  sizeof(rightParams->maps), fid);
            FWRITE((void*)&blockMap_LEN, 1,  sizeof(blockMap_LEN), fid);
            FWRITE((void*)srcBlkMapRight, 1,  blockMap_LEN, fid);
            FCLOSE(fid);

            /* Then save the *.c version */
            i = strlen(filepath);
            filepath[i-3] = 'c';
            filepath[i-2] = 0;

            if ((fid= FOPEN(filepath,"wt"))== NULL) {
                PRINT_ERRORE_MSG();
                goto EXIT;
            }

            FPRINTF(fid,"#include \"remap_common.h\"\n\n");

            FPRINTF(fid,"far unsigned char srcBlkMapRight[%d]={\n", blockMap_LEN);
            for (i=0; i<blockMap_LEN-1; i++) {
                FPRINTF(fid, "%d,\n", srcBlkMapRight[i]);
            }
            FPRINTF(fid, "%d };\n\n", srcBlkMapRight[blockMap_LEN-1]);

            FPRINTF(fid,"void stereovision_getRightBlockMap(unsigned char **pSrcBlkMapRight, unsigned int *blockMap_LEN, sConvertMap *mapStruct){\n\n");
            FPRINTF(fid,"  *pSrcBlkMapRight= (unsigned char*)&srcBlkMapRight[0];\n");
            FPRINTF(fid,"  *blockMap_LEN= %d;\n", blockMap_LEN);
            FPRINTF(fid,"  mapStruct->outputBlockDim.width= %d;\n", rightParams->maps.outputBlockDim.width);
            FPRINTF(fid,"  mapStruct->outputBlockDim.height= %d;\n", rightParams->maps.outputBlockDim.height);
            FPRINTF(fid,"  mapStruct->maxInputBlockDim.width= %d;\n", rightParams->maps.maxInputBlockDim.width);
            FPRINTF(fid,"  mapStruct->maxInputBlockDim.height= %d;\n", rightParams->maps.maxInputBlockDim.height);
            FPRINTF(fid,"  mapStruct->maxInputBlockSize= %d;\n", rightParams->maps.maxInputBlockSize);
            FPRINTF(fid,"  mapStruct->maxNumPixelsinTile= %d;\n", rightParams->maps.maxNumPixelsinTile);
            FPRINTF(fid,"  mapStruct->qShift= %d;\n", rightParams->maps.qShift);
            FPRINTF(fid,"  return;\n}\n");

            FCLOSE(fid);
        }
    }

    /*-----------------------------------------------------------------
          Query alogorithm memory requirement using standard IALG interface
      -----------------------------------------------------------------*/
    numMemRec   = REMAP_MERGE_TI_VISION_FXNS.ialg.algNumAlloc();
    leftMemRec  = (IALG_MemRec *)malloc(numMemRec * sizeof(IALG_MemRec));
    rightMemRec = (IALG_MemRec *)malloc(numMemRec * sizeof(IALG_MemRec));

    status    = REMAP_MERGE_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&leftCreateParams), NULL, leftMemRec);
    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    status    = REMAP_MERGE_TI_VISION_FXNS.ialg.algAlloc((IALG_Params *)(&rightCreateParams), NULL, rightMemRec);
    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    /*-----------------------------------------------------------------
          Allocate memory for all the mem records
          Application has to implement the below function
          Refer the example implementation below in this file
     -----------------------------------------------------------------*/
    status = TestApp_AllocMemRecords(leftMemRec, numMemRec);
    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    status = TestApp_AllocMemRecords(rightMemRec, numMemRec);
    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    /*-----------------------------------------------------------------
          Intialize the algorithm instance with the alocated memory
          and user create parameters
     -----------------------------------------------------------------*/
    status = REMAP_MERGE_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&leftHandle),
            leftMemRec, NULL, (IALG_Params *)(&leftCreateParams));


    leftHandle = (IM_Fxns *)leftMemRec[0].base;

    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    status = REMAP_MERGE_TI_VISION_FXNS.ialg.algInit((IALG_Handle)(&rightHandle),
            rightMemRec, NULL, (IALG_Params *)(&leftCreateParams));


    rightHandle = (IM_Fxns *)rightMemRec[0].base;

    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    /*-----------------------------------------------------------------
           Set buffer descriptor pointers array base
      -----------------------------------------------------------------*/
    inArgs.subFrameInfo = 0;
    inArgs.size         = sizeof(IVISION_InArgs);
    outArgs.size        = sizeof(IVISION_OutArgs);

    inBufs.bufDesc      = inBufDescList;
    outBufs.bufDesc     = outBufDescList;

    inBufs.numBufs      = 2;
    outBufs.numBufs     = 1;

    inBufDescList[0]    = &inputBlkBufDesc;
    inBufDescList[1]    = &lutBlkBufDesc;
    outBufDescList[0]   = &outputBlkBufDesc;

    inputBlkBufDesc.numPlanes                          = 1;
    inputBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)leftSrc;
    inputBlkBufDesc.bufPlanes[0].width                 = srcStride;
    inputBlkBufDesc.bufPlanes[0].height                = srcHeight;
    inputBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
    inputBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
    inputBlkBufDesc.bufPlanes[0].frameROI.width        = srcStride;
    inputBlkBufDesc.bufPlanes[0].frameROI.height       = srcHeight;

    lutBlkBufDesc.numPlanes                          = 1;
    lutBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)srcBlkMapLeft;
    lutBlkBufDesc.bufPlanes[0].width                 = blockMap_LEN;
    lutBlkBufDesc.bufPlanes[0].height                = 1;
    lutBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
    lutBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
    lutBlkBufDesc.bufPlanes[0].frameROI.width        = blockMap_LEN;
    lutBlkBufDesc.bufPlanes[0].frameROI.height       = 1;

    outputBlkBufDesc.numPlanes                          = 1;
    outputBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)leftDst;
    outputBlkBufDesc.bufPlanes[0].width                 = dstStride;
    outputBlkBufDesc.bufPlanes[0].height                = roiHeight;
    outputBlkBufDesc.bufPlanes[0].frameROI.topLeft.x    = 0;
    outputBlkBufDesc.bufPlanes[0].frameROI.topLeft.y    = 0;
    outputBlkBufDesc.bufPlanes[0].frameROI.width        = roiWidth;
    outputBlkBufDesc.bufPlanes[0].frameROI.height       = roiHeight;
#if !(VCOP_HOST_EMULATION)
    /*-----------------------------------------------------------------
           Initiate frame processing for left frame
     -----------------------------------------------------------------*/
    status = leftHandle->ivision->algProcess((IVISION_Handle)leftHandle, &inBufs, &outBufs, &inArgs, &outArgs);

    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }

    inputBlkBufDesc.bufPlanes[0].buf                   = (uint8_t *)rightSrc;
    lutBlkBufDesc.bufPlanes[0].buf                     = (uint8_t *)srcBlkMapRight;
    outputBlkBufDesc.bufPlanes[0].buf                  = (uint8_t *)rightDst;
    /*-----------------------------------------------------------------
                Initiate frame processing for right frame
          -----------------------------------------------------------------*/
    status = rightHandle->ivision->algProcess((IVISION_Handle)rightHandle, &inBufs, &outBufs, &inArgs, &outArgs);

    if(status != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
        goto EXIT;
    }
#else

    /* In case we haven't read yet the table earlier, we need to read directly from the files */
    if (gConfig_stereoVision->isRectifyMapInEveFormat!= 0) {

        /*********  LUT loading for Left ************/
        coordMapLeft= (uint32_t*)malloc(sizeof(uint32_t)*2*srcStride*srcHeight);
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision->remapLeft);
        if ((fid= FOPEN(filepath,"rb"))== NULL) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }
        FREAD((void*)coordMapLeft, 4,  2*srcStride*srcHeight, fid);
        FCLOSE(fid);
        /*********  LUT loading for Right  ************/
        coordMapRight= (uint32_t*)malloc(sizeof(uint32_t)*2*srcStride*srcHeight);
        sprintf(filepath, "../testvecs/%s", gConfig_stereoVision->remapRight);
        if ((fid= FOPEN(filepath,"rb"))== NULL) {
            PRINT_ERRORE_MSG();
            goto EXIT;
        }
        FREAD((void*)coordMapRight, 4,  2*srcStride*srcHeight, fid);
        FCLOSE(fid);
    }

    leftParams->maps.srcMap = (void*)coordMapLeft;
    remapNatc(leftSrc, NULL, leftDst, NULL, leftParams);

    rightParams->maps.srcMap = (void*)coordMapRight;
    remapNatc(rightSrc, NULL, rightDst, NULL, rightParams);

#endif

    EXIT:
    /*-----------------------------------------------------------------
                   Call algFree
       -----------------------------------------------------------------*/
    if (leftHandle->ivision->ialg.algFree((IALG_Handle)(leftHandle), leftMemRec) != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
    }

    if (rightHandle->ivision->ialg.algFree((IALG_Handle)(rightHandle), rightMemRec) != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
    }

    /* Here Free memory for all the mem records */
    if (TestApp_FreeMemRecords(leftMemRec, numMemRec) != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
    }

    if (TestApp_FreeMemRecords(rightMemRec, numMemRec) != IALG_EOK)
    {
        PRINT_ERRORE_MSG();
    }

    if ( leftMemRec != NULL )
    {
        free(leftMemRec);
    }

    if ( rightMemRec != NULL )
    {
        free(rightMemRec);
    }

    if (gConfig_stereoVision->isRectifyMapInEveFormat!= 2) {
        if ( srcBlkMapLeft != NULL )
        {
            free(srcBlkMapLeft);
        }

        if ( srcBlkMapRight != NULL )
        {
            free(srcBlkMapRight);
        }
    }

    if (coordMapLeft != NULL) {
        free(coordMapLeft);
    }

    if (coordMapRight != NULL) {
        free(coordMapRight);
    }

    if (convertedMapLeft != NULL) {
        free(convertedMapLeft);
    }

    if (convertedMapRight != NULL) {
        free(convertedMapRight);
    }

    return status;
}

void rectify_getBlockMap(uint8_t **srcBlkMap, uint32_t *blockMap_LEN, sConvertMap *maps, uint8_t *convertedMap) {

    uint32_t i;
    uint8_t *p;
    p= (uint8_t*)maps;

    for (i=0; i< sizeof(sConvertMap);i++)
        *p++= *convertedMap++;

    p= (uint8_t*)blockMap_LEN;
    for (i=0; i< sizeof(*blockMap_LEN);i++)
        *p++= *convertedMap++;

    *srcBlkMap= convertedMap;
}
