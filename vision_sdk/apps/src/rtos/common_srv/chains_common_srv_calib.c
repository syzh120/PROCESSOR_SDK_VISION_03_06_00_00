/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI�S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI�S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/chains_common_srv_calib.h>
#include <src/include/chains_common_osal.h>
#include <src/include/chains_lens.h>
#include <include/link_api/lz4CompDecomp.h>


#define NUM_VIEW_POINTS_128MB_DDR   (15U)

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
 \
/**
 *******************************************************************************
 *
 * \brief   Generate the Synthesis Blend Table
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Int32 genSynthBlendTable(
                Chain_Common_SRV_CalibrationPrm *pObj,
                AlgorithmLink_SrvCommonViewPointParams *pSrvViewPointsParam)
{
    UInt32 cnt, downScaleFactor, srvSubSample;
    AlgorithmLink_ldcSlicePrm *pCamSliceListPrm;

    pObj->blendTableGenPrm.numCameras = SRV_NUM_CAMERAS;
    pObj->blendTableGenPrm.SVOutDisplayWidth = \
                                        pSrvViewPointsParam->srvOutputWidth;
    pObj->blendTableGenPrm.SVOutDisplayHeight = \
                                        pSrvViewPointsParam->srvOutputHeight;
    pObj->blendTableGenPrm.carBoxX = pSrvViewPointsParam->carPosX;
    pObj->blendTableGenPrm.carBoxY = pSrvViewPointsParam->carPosY;
    pObj->blendTableGenPrm.viewRotationAngleRad = \
                                    pSrvViewPointsParam->viewRotationAngleRad;
    pObj->blendTableGenPrm.blendTableAddr = pSrvViewPointsParam->blendTableAddr;
    pObj->blendTableGenPrm.blendTableSize = \
        pObj->blendTableGenPrm.SVOutDisplayWidth * \
            pObj->blendTableGenPrm.SVOutDisplayHeight;

    downScaleFactor = 0;
    srvSubSample = pObj->gAlignGenLutPrm3DSrv.subsampleratio;
    for(cnt = 0U;cnt < 32;cnt++)
    {
        srvSubSample = (srvSubSample >> 1);
        if(srvSubSample == 0)
            break;
        downScaleFactor ++;
    }

    if (pObj->gAlignGenLutPrm3DSrv.SVInCamFrmWidth > pObj->blendTableGenPrm.SVOutDisplayHeight)
    {
        pObj->blendTableGenPrm.inWidth = pObj->gAlignGenLutPrm3DSrv.SVInCamFrmWidth;
    }
    else
    {
        pObj->blendTableGenPrm.inWidth = pObj->blendTableGenPrm.SVOutDisplayHeight;
    }

    pObj->blendTableGenPrm.inHeight = pObj->blendTableGenPrm.SVOutDisplayHeight;
    pObj->blendTableGenPrm.subSampleExp = downScaleFactor;
    pObj->blendTableGenPrm.pixelPad = SRV_LDC_PIXEL_PAD;
    pObj->blendTableGenPrm.ldcLutPitchBytes = SRV_LDC_MESH_TABLE_PITCH(
                                    pObj->blendTableGenPrm.inWidth,
                                    pObj->gAlignGenLutPrm3DSrv.subsampleratio);
    pObj->blendTableGenPrm.ldcMaxInBlkSize = SRV_LDC_TDA3X_MAX_INBLK_SIZE;

    for (cnt = 0;cnt < pObj->blendTableGenPrm.numCameras;cnt++)
    {
        ChainsCommon_Osal_cacheWb(
                    (UInt32)pObj->gAlignGenLutPrm3DSrv.LDCLUT3D[cnt],
                    pObj->gAlignGenLutPrm3DSrv.ldcLutSize);

        pObj->blendTableGenPrm.ldcLut[cnt] = \
                            (UInt32)pObj->gAlignGenLutPrm3DSrv.LDCLUT3D[cnt];
        pObj->blendTableGenPrm.ldcLutSize[cnt] = \
                                    pObj->gAlignGenLutPrm3DSrv.ldcLutSize;
    }

    /* LDC Block Size and max num of slices */
    pObj->blendTableGenPrm.ldcMaxNumSlices = SRV_LDC_MAX_NUM_SLICES;
    pObj->blendTableGenPrm.ldcBlkWidth[0] = SRV_LDC_BLK_WIDTH_0;
    pObj->blendTableGenPrm.ldcBlkWidth[1] = SRV_LDC_BLK_WIDTH_1;
    pObj->blendTableGenPrm.ldcBlkWidth[2] = SRV_LDC_BLK_WIDTH_2;
    pObj->blendTableGenPrm.ldcBlkHeight[0] = SRV_LDC_BLK_HEIGHT_0;
    pObj->blendTableGenPrm.ldcBlkHeight[1] = SRV_LDC_BLK_HEIGHT_1;
    pObj->blendTableGenPrm.ldcBlkHeight[2] = SRV_LDC_BLK_HEIGHT_2;


    pObj->blendTableGenPrm.boxCornerX[0] = pSrvViewPointsParam->boxCornerX[0];
    pObj->blendTableGenPrm.boxCornerY[0] = pSrvViewPointsParam->boxCornerY[0];
    pObj->blendTableGenPrm.boxCornerX[1] = pSrvViewPointsParam->boxCornerX[1];
    pObj->blendTableGenPrm.boxCornerY[1] = pSrvViewPointsParam->boxCornerY[1];
    pObj->blendTableGenPrm.boxCornerX[2] = pSrvViewPointsParam->boxCornerX[2];
    pObj->blendTableGenPrm.boxCornerY[2] = pSrvViewPointsParam->boxCornerY[2];
    pObj->blendTableGenPrm.boxCornerX[3] = pSrvViewPointsParam->boxCornerX[3];
    pObj->blendTableGenPrm.boxCornerY[3] = pSrvViewPointsParam->boxCornerY[3];

    System_linkControl(
            SYSTEM_LINK_ID_DSP1,
            TDA3X_SV_3D_GEN_BLENDTABLE,
            &pObj->blendTableGenPrm,
            sizeof(AlgorithmLink_blenTableGenPrm),
            TRUE);

    ChainsCommon_Osal_cacheWb(
                (UInt32)&pObj->blendTableGenPrm,
                sizeof(AlgorithmLink_blenTableGenPrm));

    ChainsCommon_Osal_cacheInv(
                (UInt32)pObj->blendTableGenPrm.blendTableAddr,
                pObj->blendTableGenPrm.blendTableSize);

    for (cnt = 0;cnt < SRV_NUM_CAMERAS;cnt ++)
    {
        pSrvViewPointsParam->remappedCh[cnt] = \
                                            pObj->blendTableGenPrm.chMap[cnt];
        /* Copy the LDC slice parameters */
        pCamSliceListPrm = &pObj->blendTableGenPrm.ldcSlicePrm[cnt];
        memcpy(
            &pSrvViewPointsParam->slicePrm[cnt],
            pCamSliceListPrm,
            sizeof(AlgorithmLink_ldcSlicePrm));

        pSrvViewPointsParam->quadrantStartX[cnt] = \
                                            pObj->blendTableGenPrm.quadrantStartX[cnt];
        pSrvViewPointsParam->quadrantEndX[cnt] = \
                                            pObj->blendTableGenPrm.quadrantEndX[cnt];
        pSrvViewPointsParam->quadrantStartY[cnt] = \
                                            pObj->blendTableGenPrm.quadrantStartY[cnt];
        pSrvViewPointsParam->quadrantEndY[cnt] = \
                                            pObj->blendTableGenPrm.quadrantEndY[cnt];
    }

    return 0;
}
/**
 *******************************************************************************
 *
 * \brief   Campute the LDC LUT on DSP_1
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Int32 computeLdcLut(
                Chain_Common_SRV_CalibrationPrm *pObj,
                AlgorithmLink_SrvCommonViewPointParams *pSrvViewPointParams,
                Int32 *pCalMat,
                UInt32 calMatSize,
                UInt32 v2wMeshSize,
                UInt32 ldcLutSize)
{
    UInt32 camId;

    pObj->gAlignGenLutPrm3DSrv.numCameras = SRV_NUM_CAMERAS;
    pObj->gAlignGenLutPrm3DSrv.subsampleratio = \
                                        pSrvViewPointParams->srvSubSample;
    pObj->gAlignGenLutPrm3DSrv.SVOutDisplayHeight = \
                                        pSrvViewPointParams->srvOutputHeight;
    pObj->gAlignGenLutPrm3DSrv.SVOutDisplayWidth = \
                                        pSrvViewPointParams->srvOutputWidth;
    pObj->gAlignGenLutPrm3DSrv.SVInCamFrmHeight = pObj->captureOutHeight;
    pObj->gAlignGenLutPrm3DSrv.SVInCamFrmWidth = pObj->captureOutWidth;
    pObj->gAlignGenLutPrm3DSrv.calMatSize = calMatSize;
    pObj->gAlignGenLutPrm3DSrv.v2wMeshSize = v2wMeshSize;
    pObj->gAlignGenLutPrm3DSrv.ldcLutSize = ldcLutSize;
    pObj->gAlignGenLutPrm3DSrv.carPosx = pSrvViewPointParams->carPosX;
    pObj->gAlignGenLutPrm3DSrv.carPosy = pSrvViewPointParams->carPosY;
    pObj->gAlignGenLutPrm3DSrv.view2worldmesh =                          \
                    pSrvViewPointParams->viewToWorldMeshTable;
    pObj->gAlignGenLutPrm3DSrv.calmat = pCalMat;
    pObj->gAlignGenLutPrm3DSrv.pLensPrm = (Void*)Chains_lens_getLensPrm();
    pObj->gAlignGenLutPrm3DSrv.pLensPrm2D = (Void*)Chains_lens_getLensPrm_2D();
    for (camId = 0U;camId < pObj->gAlignGenLutPrm3DSrv.numCameras;camId++)
    {
        pObj->gAlignGenLutPrm3DSrv.LDCLUT3D[camId] =                     \
                        pSrvViewPointParams->pCompBuf->metaBufAddr[camId];
        pObj->gAlignGenLutPrm3DSrv.LDC3DWidth[camId] =                  \
                        pSrvViewPointParams->ldcOutFrameWidth[camId];
        pObj->gAlignGenLutPrm3DSrv.LDC3DHeight[camId] =                 \
                        pSrvViewPointParams->ldcOutFrameHeight[camId];

        memset(
            pObj->gAlignGenLutPrm3DSrv.LDCLUT3D[camId],
            0x00,
            ldcLutSize);
    }
    System_linkControl(
            SYSTEM_LINK_ID_DSP1,
            TDA3X_SV_3D_GEN_LDCLUT,
            &pObj->gAlignGenLutPrm3DSrv,
            sizeof(AlgorithmLink_lutGenPrm_3DSRV),
            TRUE);
    ChainsCommon_Osal_cacheWb(
                    (UInt32)&pObj->gAlignGenLutPrm3DSrv,
                    sizeof(AlgorithmLink_lutGenPrm_3DSRV));

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief   Read V2W Mesh and write LDC LUT to file
 *
 *          This function reads the LUTs from the already populated
 *          Chain_Common_SRV_mediaObj buffers and the file pointers for the LUT SET files
 *          to write into them the generated Header, LDC LUTs and the BlendTable.
 *          This also creates the LUT index file as defined in the UserGuide.
 *******************************************************************************
*/
static Int32 mediaReadv2wWriteLdcLutViewPointParams(
                Chain_Common_SRV_CalibrationPrm *pChainsObj,
                Chain_Common_SRV_mediaObj *pMedia,
                AlgorithmLink_SrvCommonViewPointParams *pSrvViewPointsParam,
                System_VideoFrameCompositeBuffer *pVidCompBuf,
                UInt32 numCameras,
                UInt32 v2wMeshSize,
                UInt32 ldcLutSize,
                UInt32 carImgSize,
                Int32 *pCalMat,
                UInt32 calMatSize)
{
    Int32 retVal = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt, idx, alignedV2WMeshSize;
    UInt32 alignedLdcLutSize, alignedHeaderSize, blendTableSize, alignedBlendTableSize;
    UInt32 rawMemSize, rawMemSizeLdclut, writeSize;
    UInt32 start, end, setSize, toBeWrittenMaxSize;
    UInt8 *pToBeWritten;
    UInt8 *pTempToBeWritten;
    Int32 fpLutIdxFile;
    UInt32 offset = 0U;
    UInt32 perSetSize = 0U;
    UInt8 *readAddr;
    Uint8 *pCompressedData;
    Int32 fpSetlz4;
    UInt32 setNo = 0U;
    UInt32 idxBufPtr, chunkOffset;
    UInt32 *tempIdx;
    AlgorithmLink_SrvCommonViewPointParams *pLocalParams;

    /*the first value in the v2w idx buffer is the number of View Points*/
    UInt32 numViewPoints = *(pMedia->v2wIdxBuf);

    /* DSP will use this CAR Image, hence aliging on 128 boundary */
    blendTableSize = SRV_OUTPUT_WIDTH_TDA3X_3D_LDC * SRV_OUTPUT_HEIGHT_TDA3X_3D_LDC;
    alignedBlendTableSize = SystemUtils_align(blendTableSize, 128U);
    alignedLdcLutSize = SystemUtils_align(ldcLutSize, 128U);
    alignedV2WMeshSize = SystemUtils_align(v2wMeshSize, 128U);
    alignedHeaderSize = SystemUtils_align(SRV_MEDIA_SIZE_HEADER, 128U);

    rawMemSizeLdclut = (alignedLdcLutSize * numCameras) + alignedBlendTableSize;
    rawMemSize = rawMemSizeLdclut;
    pSrvViewPointsParam->pCompBuf = pVidCompBuf;
    fpLutIdxFile = pMedia->fpLutIdxFile;
    setSize = SRV_SET_SIZE;

    /*Allocate the buffer for index file temp storage*/
    tempIdx = (UInt32 *)ChainsCommon_Osal_memAlloc(SRV_MEDIA_SIZE_MAXIDX, 128U);
    UTILS_assert(NULL != tempIdx);

    /*Allocate a buffer for the file data that has to be compressed*/
    toBeWrittenMaxSize = setSize * (alignedHeaderSize + (alignedLdcLutSize * numCameras) + alignedBlendTableSize);
    pToBeWritten = (UInt8 *)ChainsCommon_Osal_memAlloc(toBeWrittenMaxSize, 128U);
    pTempToBeWritten = pToBeWritten;
    UTILS_assert(NULL != pToBeWritten);

    /*Allocate a buffer for the compressed data that has to be written to file*/
    pCompressedData = (UInt8 *)ChainsCommon_Osal_memAlloc(toBeWrittenMaxSize, 128U);
    UTILS_assert(NULL != pCompressedData);

    /*Allocate single super buffer*/
    pSrvViewPointsParam->baseBufAddr = ChainsCommon_Osal_memAlloc(rawMemSize, 128U);
    UTILS_assert(NULL != pSrvViewPointsParam->baseBufAddr);

    start = ChainsCommon_Osal_getCurTimeMsec();

    for(cnt = 0U;cnt < numViewPoints;cnt ++)
    {
        /*Reading the offset and size of the View Point Data from the IDX file*/
        idxBufPtr = (cnt * 2U) + (SRV_MEDIA_SIZE_METADATA >> 2U);
        chunkOffset = *(pMedia->v2wIdxBuf + idxBufPtr);

        /*Storing the previous assigned values to the structure read form the file*/
        pLocalParams = (AlgorithmLink_SrvCommonViewPointParams *)(pMedia->v2wBuf + chunkOffset);
        pLocalParams->pCompBuf = pSrvViewPointsParam->pCompBuf;
        pLocalParams->baseBufAddr = pSrvViewPointsParam->baseBufAddr;
        memcpy(pSrvViewPointsParam, pLocalParams, sizeof(AlgorithmLink_SrvCommonViewPointParams));

        UTILS_assert(NULL != pMedia->v2wBuf);
        pSrvViewPointsParam->viewToWorldMeshTable = (float*)((UInt32)pMedia->v2wBuf + \
                                                    chunkOffset + alignedHeaderSize);
        UTILS_assert(NULL != pSrvViewPointsParam->viewToWorldMeshTable);

        for(idx = 0U; idx < numCameras; idx++)
        {
            pSrvViewPointsParam->pCompBuf->metaBufAddr[idx] = (Void*)   \
                            ((UInt32)pSrvViewPointsParam->baseBufAddr + \
                            (alignedLdcLutSize * idx));
        }

        pSrvViewPointsParam->blendTableAddr = (Void*)   \
                            ((UInt32)pSrvViewPointsParam->baseBufAddr + \
                            (alignedLdcLutSize * numCameras));

        pSrvViewPointsParam->pCompBuf->numFrames = numCameras;

        Vps_printf("SRV_CALIB_UC: Generating LDC LUT for view point %d ...\n",cnt);
        retVal = computeLdcLut(pChainsObj,
                                pSrvViewPointsParam,
                                pCalMat,
                                calMatSize,
                                alignedV2WMeshSize,
                                alignedLdcLutSize);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

        retVal = genSynthBlendTable( pChainsObj, pSrvViewPointsParam);
        UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

        Vps_printf("SRV_CALIB_UC: Writing LDC LUT for view point %d ...\n",cnt);

        writeSize = alignedHeaderSize + (alignedLdcLutSize * numCameras) + \
                    alignedBlendTableSize;

        /*Write to the IDX File Buffer and later write them in one go*/
        tempIdx[(SRV_MEDIA_SIZE_METADATA >> 2U) + cnt * 2U] = offset;
        tempIdx[(SRV_MEDIA_SIZE_METADATA >> 2U) + cnt * 2U + 1U] = writeSize;
        offset += writeSize;

        memcpy(pTempToBeWritten,pSrvViewPointsParam,
                        sizeof(AlgorithmLink_SrvCommonViewPointParams));
        pTempToBeWritten += alignedHeaderSize;

        /*calculate the LUT's address and append them to the previous buffer*/
        readAddr = (UInt8*)ChainsCommon_Osal_getVirtAddr((UInt32)pSrvViewPointsParam->baseBufAddr);
        memcpy(pTempToBeWritten, readAddr,
                    (alignedLdcLutSize * numCameras) + alignedBlendTableSize);
        pTempToBeWritten += (alignedLdcLutSize * numCameras) + alignedBlendTableSize;
        perSetSize += alignedHeaderSize + (alignedLdcLutSize * numCameras) + alignedBlendTableSize;

        if((cnt == 0U) || (cnt+1U) % setSize == 0U || ((cnt + 1U) == numViewPoints))
        {
            pChainsObj->toBeCompressed.inputBufferSize = perSetSize;
            pChainsObj->toBeCompressed.inputBuffer     = pToBeWritten;
            pChainsObj->toBeCompressed.outputBuffer    = pCompressedData;
            tempIdx[SRV_MEDIA_IDX_SET_SIZE_OFFSET + setNo] = perSetSize;
            pChainsObj->toBeCompressed.operationDone   = 0U;

            ChainsCommon_Osal_cacheWb( (UInt32)(pChainsObj->toBeCompressed.inputBuffer),
                                        pChainsObj->toBeCompressed.inputBufferSize);
            /*Compress and put it as Set0*/
            System_linkControl( SYSTEM_LINK_ID_DSP1,
                                LZ4_COMPRESS_CMD,
                                &pChainsObj->toBeCompressed,
                                sizeof(lz4CompDecomp_inp),
                                TRUE);

            ChainsCommon_Osal_cacheWb( (UInt32)&pChainsObj->toBeCompressed,
                                        sizeof(lz4CompDecomp_inp));

            while(pChainsObj->toBeCompressed.operationDone == 0U);

            /*Get the new file pointer from Media structure and write the number of View Points and header*/
            fpSetlz4 = pMedia->fplutSet[setNo];

            retVal = ChainsCommon_Osal_fileWrite(fpSetlz4,
                            (UInt8*)(pChainsObj->toBeCompressed.outputBuffer),
                            pChainsObj->toBeCompressed.outputBufferSize);
            UTILS_assert(SYSTEM_LINK_STATUS_SOK == retVal);

            ChainsCommon_Osal_fileClose(fpSetlz4);
            pTempToBeWritten = pToBeWritten;
            perSetSize = 0U;
            setNo++;
        }
    }

    /*writing the Uncompressed Size, Num of Sets and size of all the sets*/
    tempIdx[0] = numViewPoints;
    tempIdx[1] = offset;
    tempIdx[2] = setNo;

    retVal = ChainsCommon_Osal_fileWrite(fpLutIdxFile,
                                        (UInt8*)tempIdx,
                                        SRV_MEDIA_SIZE_MAXIDX);
    UTILS_assert(-1 != retVal);

    end = ChainsCommon_Osal_getCurTimeMsec();
    Vps_printf("SRV_CALIB_UC: Time taken to write %d view point data = %d msec\n",
               numViewPoints, (end - start));

    /*Closing the index file*/
    ChainsCommon_Osal_fileClose(fpLutIdxFile);
    ChainsCommon_Osal_memFree( pSrvViewPointsParam->baseBufAddr, rawMemSize);
    ChainsCommon_Osal_memFree( pToBeWritten, toBeWrittenMaxSize);
    ChainsCommon_Osal_memFree( pCompressedData, toBeWrittenMaxSize);
    ChainsCommon_Osal_memFree( tempIdx, SRV_MEDIA_SIZE_MAXIDX);

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief   Write the Cal Mat into the file
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void writeCalMat(
                Chain_Common_SRV_CalibrationPrm *pObj,
                Int32 *calMatBuf,
                Int32 *persMatBuf)
{
    UInt32 cnt, numCameras, calMatSize[SRV_NUM_CAMERAS];
    Int32 fp;
    UInt8 *writeAddr;

    Vps_printf("SRV_CALIB_UC: Writing Cal Mat to the file ...\n");

    /*
     *  Write the default cal mat to the file
     */
    fp = ChainsCommon_Osal_fileOpen(SRV_CALMAT_FILE, \
                                    CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
    UTILS_assert (-1 != fp);

    /* Write the no of cameras */
    numCameras = SRV_NUM_CAMERAS;
    ChainsCommon_Osal_fileWrite(
                    fp,
                    (UInt8*)&numCameras,
                    4U);

    /* Write the size of the calMat for each camera in no of bytes */
    for (cnt = 0U;cnt < numCameras;cnt++)
    {
        calMatSize[cnt] = SRV_CALMAT_SIZE;
        ChainsCommon_Osal_fileWrite(
                        fp,
                        (UInt8*)&calMatSize[cnt],
                        4U);
    }

    /* Leave hole for the meta data */
    ChainsCommon_Osal_fileSeek(
        fp,
        SRV_MEDIA_SIZE_METADATA);       // 128 bytes including the numCameras
                                        // and (calMatSize * numCameras)

    /* Write the calMat for each camera */
    writeAddr = (UInt8*)calMatBuf;

    for (cnt = 0U;cnt < numCameras;cnt ++)
    {
        ChainsCommon_Osal_fileWrite(
                        fp,
                        writeAddr,
                        calMatSize[cnt]);
        writeAddr += calMatSize[cnt];
    }

    ChainsCommon_Osal_fileClose(fp);

    Vps_printf("SRV_CALIB_UC: Writing Cal Mat to the file DONE\n");

    /*
     *  Write the Pers mat to the file
     */

    Vps_printf("SRV_CALIB_UC: Writing Pers Mat to the file ...\n");

    fp = ChainsCommon_Osal_fileOpen(SRV_PERSMAT_FILE, \
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
    UTILS_assert (-1 != fp);

    /* Write the calMat for each camera */
    writeAddr = (UInt8*)persMatBuf;

    /* Write Pers mat to the file */
    ChainsCommon_Osal_fileWrite(
                    fp,
                    writeAddr,
                    (SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS));

    ChainsCommon_Osal_fileClose(fp);

    Vps_printf("SRV_CALIB_UC: Writing Pers Mat to the file DONE\n");
}

/**
 *******************************************************************************
 *
 * \brief   Read Cal Mat from file
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void readCalMat(
                    Chain_Common_SRV_CalibrationPrm *pObj)
{
    Int32 fp;
    UInt32 cnt, readSize, numCameras;
    UInt32 calMatSize[SRV_NUM_CAMERAS];
    UInt8 *readAddr;

    Vps_printf("SRV_CALIB_UC: => Reading Cal Mat from %s file ...\n",\
                SRV_CALMAT_FILE);

    fp = ChainsCommon_Osal_fileOpen(SRV_CALMAT_FILE, \
                                        CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
    if (-1 != fp)
    {
        ChainsCommon_Osal_fileRead(
                            fp,
                            (UInt8*)&numCameras,
                            4U,
                            &readSize);

        for (cnt = 0U;cnt < numCameras;cnt ++)
        {
            ChainsCommon_Osal_fileRead(
                                fp,
                                (UInt8*)&calMatSize[cnt],
                                4U,
                                &readSize);
        }

        ChainsCommon_Osal_fileSeek(
            fp,
            SRV_MEDIA_SIZE_METADATA);

        readAddr = (UInt8*)ChainsCommon_Osal_getVirtAddr(
                                    (UInt32)pObj->calMatGenPrm3DSrv.calMatBuf);
        for (cnt = 0U;cnt < numCameras;cnt ++)
        {
            ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)readAddr,
                        calMatSize[cnt],
                        &readSize);

            readAddr += calMatSize[cnt];
        }

        ChainsCommon_Osal_fileClose(fp);

        pObj->isCalMatGenerated = TRUE;
    }
    else
    {
        Vps_printf("SRV_CALIB_UC: => CALMAT.BIN file is NOT present ...\n");
    }
}

/**
 *******************************************************************************
 *
 * \brief   Read V2W Mesh and write LDC LUT to file for all the view points
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void Chain_Common_SRV_generateLdcLut4ViewPoints(
                    Chain_Common_SRV_CalibrationPrm *pObj)
{
    Chain_Common_SRV_mediaObj media;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 lineOffset, ldcLutSize;
#if defined(LINUX_BUILD) || defined(QNX_BUILD)

#else
    UTILS_COMPILETIME_ASSERT (SRV_MEDIA_SIZE_HEADER >= \
                                sizeof(AlgorithmLink_SrvCommonViewPointParams));
#endif

    if (TRUE == pObj->isCalMatGenerated)
    {
        lineOffset = (SRV_LDC_LUT_FRM_WIDTH/SRV_3D_LDC_SUB_SAMPLE_RATIO)+ 1U;
        lineOffset += 15;
        lineOffset &= ~0xF;
        lineOffset *= 4;

        ldcLutSize = lineOffset * ((SRV_LDC_LUT_FRM_HEIGHT/SRV_3D_LDC_SUB_SAMPLE_RATIO) + 1U);

        status = Chain_Common_SRV_Comp_mediaInit(&media, SRV_MEDIA_FILE_V2W);
        if(status != SYSTEM_LINK_STATUS_EFAIL)
        {
            mediaReadv2wWriteLdcLutViewPointParams(
                    pObj,
                    &media,
                    &pObj->algViewParams,
                    &pObj->ldcMeshTableContainer,
                    SRV_NUM_CAMERAS,
                    SRV_LDC_VIEW2WORLDMESH_MAX_SIZE,
                    ldcLutSize,
                    SRV_LDC_CARIMAGE_MAX_SIZE,
                    pObj->calMatGenPrm3DSrv.calMatBuf,
                    SRV_CALMAT_SIZE);
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Generate the GPU LUT from the Cal mat
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Int32 Chain_Common_SRV_generateGpuLut(Chain_Common_SRV_CalibrationPrm *pObj)
{
    Int32 fp, retVal;

    if (TRUE == pObj->isCalMatGenerated)
    {
        pObj->gAlignGenLutPrm3DSrv.numCameras = SRV_NUM_CAMERAS;
        pObj->gAlignGenLutPrm3DSrv.subsampleratio = SRV_3D_GPU_SUB_SAMPLE_RATIO;
        pObj->gAlignGenLutPrm3DSrv.SVOutDisplayHeight = \
                                                    SRV_OUTPUT_HEIGHT_TDA2X_3D;
        pObj->gAlignGenLutPrm3DSrv.SVOutDisplayWidth = \
                                                    SRV_OUTPUT_WIDTH_TDA2X_3D;
        pObj->gAlignGenLutPrm3DSrv.SVInCamFrmHeight = pObj->captureOutHeight;
        pObj->gAlignGenLutPrm3DSrv.SVInCamFrmWidth = pObj->captureOutWidth;
        pObj->gAlignGenLutPrm3DSrv.calmat = pObj->calMatGenPrm3DSrv.calMatBuf;
        pObj->gAlignGenLutPrm3DSrv.calMatSize = SRV_CALMAT_SIZE;
        pObj->gAlignGenLutPrm3DSrv.GPULUT3D = (UInt16*)pObj->gpuLut3DBuf;
        pObj->gAlignGenLutPrm3DSrv.gpuLutSize = pObj->gpuLutSize;
        pObj->gAlignGenLutPrm3DSrv.pLensPrm = (Void*)Chains_lens_getLensPrm();
        pObj->gAlignGenLutPrm3DSrv.pLensPrm2D = \
                                            (Void*)Chains_lens_getLensPrm_2D();
        pObj->gAlignGenLutPrm3DSrv.GPULUT3D_XYZ = (float*)pObj->gpuLut3D_XYZBuf;
        pObj->gAlignGenLutPrm3DSrv.gpuLutXYZSize = pObj->gpuLutXYZSize;
        pObj->gAlignGenLutPrm3DSrv.GPULUT3D_undist = (float*)pObj->gpuLut3D_undistBuf;
        pObj->gAlignGenLutPrm3DSrv.gpuLutundistSize = pObj->gpuLutundistSize;

        System_linkControl(
                SYSTEM_LINK_ID_DSP1,
                TDA2X_SV_3D_GEN_GPULUT,
                &pObj->gAlignGenLutPrm3DSrv,
                sizeof(AlgorithmLink_lutGenPrm_3DSRV),
                TRUE);

        ChainsCommon_Osal_cacheWb(
                            (UInt32)&pObj->gAlignGenLutPrm3DSrv,
                            sizeof(AlgorithmLink_lutGenPrm_3DSRV));

        Vps_printf("SRV_CALIB_UC: Writing GPU LUT to file ...\n");

        fp = ChainsCommon_Osal_fileOpen(SRV_FILENAME_GPULUT, \
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
        UTILS_assert (-1 != fp);

        /* Write the GPU LUT on MMC/SD card */
        ChainsCommon_Osal_fileWrite(
                fp,
                (UInt8*)ChainsCommon_Osal_getVirtAddr((UInt32)pObj->gpuLut3DBuf),
                pObj->gpuLutSize);

        ChainsCommon_Osal_fileClose(fp);

        Vps_printf("SRV_CALIB_UC: Writing GPU LUT to file DONE\n");

        retVal = 0;
    }
    else
    {
        Vps_printf("SRV_CALIB_UC: The CAL MAT is not generated\n");
        Vps_printf("SRV_CALIB_UC: Use option # 2 to generate CAL MAT\n");

        retVal = -1;
    }

    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief   Generate the GPU LUT from the Cal mat
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Int32 Chain_Common_SRV_update2DPersMat(
                    Chain_Common_SRV_CalibrationPrm *pObj)
{
    Int32 fp;
    Int32 retVal;
    UInt32 chId;

    if (TRUE == pObj->isCalMatGenerated)
    {
        Vps_printf("SRV_CALIB_UC: => Dumping YUV frames ...\n");

        for(chId = 0U;chId < pObj->numCh;chId ++)
        {
            /*
             *  Initiate the frame save and wait for completion
             */
            pObj->saveFrameChId = chId;
            pObj->saveFrame = TRUE;
            ChainsCommon_Osal_mutexWait(pObj->saveFrameSync);
        }

        pObj->update2DPersMat.imgPitch[0U] = pObj->captureOutWidth;
        pObj->update2DPersMat.imgPitch[1U] = pObj->captureOutWidth;
        pObj->update2DPersMat.result = 0;

        pObj->update2DPersMat.SVInCamFrmHeight = pObj->captureOutHeight;
        pObj->update2DPersMat.SVInCamFrmWidth = pObj->captureOutWidth;
        pObj->update2DPersMat.ldcOutFrmWidth = 0;
        pObj->update2DPersMat.ldcOutFrmHeight = 0;
        pObj->update2DPersMat.numColorChannels = 3;
        pObj->update2DPersMat.numCameras = SRV_NUM_CAMERAS;
        pObj->update2DPersMat.DMAblockSizeV = 40;
        pObj->update2DPersMat.DMAblockSizeH = 40;
        pObj->update2DPersMat.saladbowlFocalLength = 8000;
        pObj->update2DPersMat.defaultFocalLength = 455;
        pObj->update2DPersMat.downsampRatio = 2;
        pObj->update2DPersMat.carBoxHeight = SRV_CARBOX_HEIGHT;
        pObj->update2DPersMat.carBoxWidth = SRV_CARBOX_WIDTH;
        pObj->update2DPersMat.maxNumFeatures = 100;
        pObj->update2DPersMat.minMatchScore = -10;
        pObj->update2DPersMat.maxBRIEFScore = 100;
        pObj->update2DPersMat.minDistBWFeats = 10;
        pObj->update2DPersMat.outputMode = ALGORITHM_LINK_SRV_OUTPUT_2D;
        pObj->update2DPersMat.subsampleRatio = 4;
        pObj->update2DPersMat.enablePixelsPerCm = 0;
        pObj->update2DPersMat.useDefaultPixelsPerCm = 1;
        pObj->update2DPersMat.ldcDownScaleFactor = 8;
        pObj->update2DPersMat.pLensPrm2D = (Void*)Chains_lens_getLensPrm_2D();

        System_linkControl(
                SYSTEM_LINK_ID_DSP1,
                SV_2D_UPDATE_PERSMAT,
                &pObj->update2DPersMat,
                sizeof(AlgorithmLink_update2DPersMatPrm),
                TRUE);

        ChainsCommon_Osal_cacheWb(
                    (UInt32)&pObj->update2DPersMat,
                    sizeof(AlgorithmLink_update2DPersMatPrm));

        if (1 == pObj->update2DPersMat.result)
        {
            ChainsCommon_Osal_cacheInv(
                    (UInt32)pObj->update2DPersMat.persMatBuf,
                    (SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS));

            fp = ChainsCommon_Osal_fileOpen(SRV_PERSMAT_FILE, \
                                                CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
            UTILS_assert (-1 != fp);

            /* Write Pers mat to the file */
            ChainsCommon_Osal_fileWrite(
                            fp,
                            (UInt8*)pObj->update2DPersMat.persMatBuf,
                            (SRV_PERSMAT_SIZE * SRV_NUM_CAMERAS));

            ChainsCommon_Osal_fileClose(fp);

            retVal = 0;
        }
        else
        {
            retVal = -1;
        }
    }
    else
    {
        Vps_printf("SRV_CALIB_UC: The CAL MAT is not generated\n");
        Vps_printf("SRV_CALIB_UC: Use option # 2 to generate CAL MAT\n");

        retVal = -1;
    }

    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief   Generate the Calibration Matrix on DSP_1
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void Chain_Common_SRV_generateCalMat(
                    Chain_Common_SRV_CalibrationPrm *pObj,
                    SRV_CALIB_TYPE calibType)
{
    Int32 fp;
    UInt32 readSize;

    UInt32 cnt;

    pObj->isCalMatGenerated = FALSE;

    if (calibType == SRV_CALIB_TYPE_AUTO)
    {
        Vps_printf("SRV_CALIB_UC: => Dumping YUV frames ...\n");

        for(cnt = 0U;cnt < pObj->numCh;cnt ++)
        {
            /*
             *  Initiate the frame save and wait for completion
             */
            pObj->saveFrameChId = cnt;
            pObj->saveFrame = TRUE;
            ChainsCommon_Osal_mutexWait(pObj->saveFrameSync);
        }

        Vps_printf("SRV_CALIB_UC: => Reading file %s ...\n",SRV_CHARTPOS_FILE);

        fp = ChainsCommon_Osal_fileOpen(SRV_CHARTPOS_FILE, \
                                        CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
        if (-1 != fp)
        {
            ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)ChainsCommon_Osal_getVirtAddr(
                                                (UInt32)pObj->inChartPosBuf),
                        SRV_CHARTPOS_SIZE,
                        &readSize);

            ChainsCommon_Osal_fileClose(fp);

            Vps_printf("SRV_CALIB_UC: => Cal Mat Generation on DSP ...\n");

            pObj->calMatGenPrm3DSrv.numCameras = SRV_NUM_CAMERAS;
            pObj->calMatGenPrm3DSrv.imgPitch[0U] = pObj->captureOutWidth;
            pObj->calMatGenPrm3DSrv.imgPitch[1U] = pObj->captureOutWidth;
            pObj->calMatGenPrm3DSrv.imgWidth = pObj->captureOutWidth;
            pObj->calMatGenPrm3DSrv.imgHeight = pObj->captureOutHeight;
            pObj->calMatGenPrm3DSrv.inChartPosBuf = pObj->inChartPosBuf;
            pObj->calMatGenPrm3DSrv.inChartPosSize = SRV_CHARTPOS_SIZE;
            pObj->calMatGenPrm3DSrv.pLensPrm = (Void*)Chains_lens_getLensPrm();
            pObj->calMatGenPrm3DSrv.pLensPrm2D = (Void*)Chains_lens_getLensPrm_2D();
            pObj->calMatGenPrm3DSrv.binarizationMode = pObj->binarizationMode;
            pObj->calMatGenPrm3DSrv.thresholdMode = pObj->thresholdMode;
            pObj->calMatGenPrm3DSrv.windowMode = pObj->windowMode;
            pObj->calMatGenPrm3DSrv.Ransac = pObj->Ransac;
            pObj->calMatGenPrm3DSrv.PoseRansac = pObj->PoseRansac;
            pObj->calMatGenPrm3DSrv.SingleChartPose = pObj->SingleChartPose;
            pObj->calMatGenPrm3DSrv.is2mp = pObj->is2mp;

            System_linkControl(
                    SYSTEM_LINK_ID_DSP1,
                    TDA3X_SV_3D_GEN_CALMAT,
                    &pObj->calMatGenPrm3DSrv,
                    sizeof(AlgorithmLink_calMatGenPrm_3DSRV),
                    TRUE);

            ChainsCommon_Osal_cacheWb(
                        (UInt32)&pObj->calMatGenPrm3DSrv,
                        sizeof(AlgorithmLink_calMatGenPrm_3DSRV));

            if (pObj->calMatGenPrm3DSrv.retStatus == SYSTEM_LINK_STATUS_SOK)
            {
                /* Write the generated Cal Mat to the file */
                writeCalMat(
                    pObj,
                    (Int32*)ChainsCommon_Osal_getVirtAddr(
                                (UInt32)pObj->calMatGenPrm3DSrv.calMatBuf),
                    (Int32*)ChainsCommon_Osal_getVirtAddr(
                                (UInt32)pObj->calMatGenPrm3DSrv.persMatBuf));

                pObj->isCalMatGenerated = TRUE;
            }
            else
            {
                /*
                 *  The Auto Calibration has failed so if CALMAT.BIN file is
                 *  present then copy from it.
                 */
                Vps_printf("SRV_CALIB_UC: => Auto Calibration FAILED ...\n");
                readCalMat(pObj);
            }
        }
        else
        {
            Vps_printf("SRV_CALIB_UC: => CHARTPOS.BIN file is NOT present\n");
        }
    }
    else if (calibType == SRV_CALIB_TYPE_MANUAL)
    {
        readCalMat(pObj);
    }
}
/**
 *******************************************************************************
 *
 * \brief   Initialize all the files required by the calibration usecase
 *
 *          Reads the compressed LUTs and CARIMG and stores the decompressed ones
 *          to the relevant buffers from the media Object
 *******************************************************************************
*/
Int32 Chain_Common_SRV_Comp_mediaInit(Chain_Common_SRV_mediaObj *pMediaObj,
                                       SRV_MEDIA_FILE fileType)
{
    UInt32 readSize;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 numSets, currSetNo;
    char filename[SRV_FILENAME_MAX_SIZE];
    Int32 fp;
    UInt8 *compressedBuffer;
    lz4CompDecomp_inp toDecompress;

    if(fileType == SRV_MEDIA_FILE_V2W)
    {
        pMediaObj->v2wIdxBuf = NULL;
        pMediaObj->v2wBuf = NULL;
        pMediaObj->carImgIdxBuf = NULL;
        pMediaObj->carImgBuf = NULL;
        pMediaObj->ldcIdxBuf = NULL;
        pMediaObj->ldcBuf = NULL;
        pMediaObj->fpLutIdxFile = -1;

        Vps_printf("SRV MEDIA: Opening %s\n", SRV_FILENAME_V2WIDX);
        fp = ChainsCommon_Osal_fileOpen(
                                    SRV_FILENAME_V2WIDX,
                                    CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
        if (-1 == fp)
        {
            Vps_printf("SRV_MEDIA: Cannot open file (%s)\n", SRV_FILENAME_V2WIDX);
        }
        UTILS_assert(-1 != fp);

        pMediaObj->v2wIdxBuf = (UInt32 *)
                        ChainsCommon_Osal_memAlloc(SRV_MEDIA_SIZE_MAXIDX, 128U);
        UTILS_assert(NULL != pMediaObj->v2wIdxBuf);

        status = ChainsCommon_Osal_fileRead(fp,
                    (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)pMediaObj->v2wIdxBuf),
                    SRV_MEDIA_SIZE_MAXIDX,
                    &readSize);
        UTILS_assert((0U == status) && (readSize != 0U));

        ChainsCommon_Osal_fileClose(fp);

        /*Opening and reading the V2W file file*/
        pMediaObj->v2wBufSize = *(pMediaObj->v2wIdxBuf + 1U);
        Vps_printf("SRV MEDIA: Opening %s\n", SRV_FILENAME_V2W);
        fp = ChainsCommon_Osal_fileOpen( SRV_FILENAME_V2W,
                                         CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
        if (-1 == fp)
        {
            Vps_printf("SRV_MEDIA: Cannot open file (%s)\n", SRV_FILENAME_V2W);
        }
        UTILS_assert(-1 != fp);

        compressedBuffer = (UInt8 *)ChainsCommon_Osal_memAlloc(ChainsCommon_Osal_fileSize(fp), 128U);
        UTILS_assert(NULL != compressedBuffer);

        pMediaObj->v2wBuf = (UInt8 *)ChainsCommon_Osal_memAlloc(pMediaObj->v2wBufSize, 128U);
        UTILS_assert(NULL != pMediaObj->v2wBuf);

        status = ChainsCommon_Osal_fileRead(fp,
                            (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)compressedBuffer),
                            ChainsCommon_Osal_fileSize(fp),
                            &readSize);
        UTILS_assert((0U == status) && (readSize != 0U));

        toDecompress.inputBufferSize = ChainsCommon_Osal_fileSize(fp);
        UTILS_assert(toDecompress.inputBufferSize > 0U);
        toDecompress.inputBuffer = compressedBuffer;
        toDecompress.outputBuffer = pMediaObj->v2wBuf;
        toDecompress.outputBufferSize = pMediaObj->v2wBufSize;

        System_linkControl( SYSTEM_LINK_ID_LZ4_DSP,
                            LZ4_DECOMPRESS_CMD,
                            &toDecompress,
                            sizeof(lz4CompDecomp_inp),
                            TRUE);
        /*Cache wb for the compressed data*/
        ChainsCommon_Osal_cacheWb( (UInt32)toDecompress.inputBuffer,
                                    toDecompress.inputBufferSize);
        /*Cache wb for the compression/decompression structure*/
        ChainsCommon_Osal_cacheWb( (UInt32)&toDecompress,
                                    sizeof(lz4CompDecomp_inp));

        ChainsCommon_Osal_memFree(compressedBuffer, ChainsCommon_Osal_fileSize(fp));
        ChainsCommon_Osal_fileClose(fp);

        /*Opening and reading the idx file*/
        /*-----------------------------------------------------------------*/
        numSets  = *(pMediaObj->v2wIdxBuf + 2U);

        for(currSetNo = 0; currSetNo < numSets; currSetNo++)
        {
            snprintf(filename, SRV_FILENAME_MAX_SIZE, "LUT_SET%d.LZ4", currSetNo);
            /*delete the existing file*/
            ChainsCommon_Osal_fileDelete(filename);
            pMediaObj->fplutSet[currSetNo] = ChainsCommon_Osal_fileOpen( filename,
                                         CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
            if(pMediaObj->fplutSet[currSetNo] == -1)
            {
                Vps_printf("SRV MEDIA: Cannot create file:%s\n", filename);
            }
            UTILS_assert(-1 != pMediaObj->fplutSet[currSetNo]);
        }

        ChainsCommon_Osal_fileDelete(SRV_FILENAME_LUTIDX);
        pMediaObj->fpLutIdxFile = ChainsCommon_Osal_fileOpen( SRV_FILENAME_LUTIDX,
                                     CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
        if(-1 == pMediaObj->fpLutIdxFile)
        {
            Vps_printf("SRV_MEDIA: Cannot create file (%s)\n", SRV_FILENAME_LUTIDX);
        }
        UTILS_assert(-1 != pMediaObj->fpLutIdxFile);
    }
    else if(fileType == SRV_MEDIA_FILE_VIEWPOINT_ZERO)
    {
        pMediaObj->v2wIdxBuf = NULL;
        pMediaObj->v2wBuf = NULL;
        pMediaObj->carImgIdxBuf = NULL;
        pMediaObj->carImgBuf = NULL;
        pMediaObj->ldcIdxBuf = NULL;
        pMediaObj->ldcBuf = NULL;
        pMediaObj->fpLutIdxFile = -1;

        /*Reading the LUT index file*/
        fp = ChainsCommon_Osal_fileOpen( SRV_FILENAME_LUTIDX,
                                         CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
        if(-1 == fp)
        {
            Vps_printf("SRV_MEDIA: Cannot open file (%s)\n", SRV_FILENAME_LUTIDX);
        }
        UTILS_assert(-1 != fp);

        pMediaObj->ldcIdxBuf = (UInt32 *)ChainsCommon_Osal_memAlloc(SRV_MEDIA_SIZE_MAXIDX, 128U);
        UTILS_assert(NULL != pMediaObj->ldcIdxBuf);

        status = ChainsCommon_Osal_fileRead(fp,
                            (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)pMediaObj->ldcIdxBuf),
                            SRV_MEDIA_SIZE_MAXIDX,
                            &readSize);
        UTILS_assert((0U == status) && (readSize != 0U));

        ChainsCommon_Osal_fileClose(fp);

        /*Reading the CarImg index file*/
        fp = ChainsCommon_Osal_fileOpen( SRV_FILENAME_CARIMGIDX,
                                         CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
        if(-1 == fp)
        {
            Vps_printf("SRV_MEDIA: Cannot open file (%s)\n", SRV_FILENAME_CARIMGIDX);
        }
        UTILS_assert(-1 != fp);

        pMediaObj->carImgIdxBuf = (UInt32 *)ChainsCommon_Osal_memAlloc(SRV_MEDIA_SIZE_MAXIDX, 128U);
        UTILS_assert(NULL != pMediaObj->carImgIdxBuf);

        status = ChainsCommon_Osal_fileRead(fp,
                            (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)pMediaObj->carImgIdxBuf),
                            SRV_MEDIA_SIZE_MAXIDX,
                            &readSize);
        UTILS_assert((0U == status) && (readSize != 0U));

        ChainsCommon_Osal_fileClose(fp);

        /*Opening and reading the LUT file*/
        /*-----------------------------------------------------------------*/
        pMediaObj->ldcBufSize = *(pMediaObj->ldcIdxBuf + 1U);
        numSets  = *(pMediaObj->ldcIdxBuf + 2U);

        #ifdef TDA3XX_128MB_DDR
        UInt32 numViewPoints = *(pMediaObj->ldcIdxBuf);
        Vps_printf("SRV MEDIA: 128 MB build supports data with less than(or equal) %d View points. Currently : %d\n", NUM_VIEW_POINTS_128MB_DDR, numViewPoints);
        UTILS_assert(numViewPoints <= NUM_VIEW_POINTS_128MB_DDR);
        #endif

        if(status != SYSTEM_LINK_STATUS_EFAIL)
        {
            currSetNo = 0U;
            snprintf(filename, SRV_FILENAME_MAX_SIZE, "LUT_SET%d.LZ4", currSetNo);
            Vps_printf("SRV MEDIA: Opening %s\n", filename);
            fp = ChainsCommon_Osal_fileOpen(filename, CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
            if(fp == -1)
            {
                Vps_printf("SRV MEDIA: Cannot open file:%s\n", filename);
            }
            UTILS_assert(-1 != fp);

            pMediaObj->ldcBuf = (UInt8 *)ChainsCommon_Osal_memAlloc(pMediaObj->ldcBufSize, 128U);
            UTILS_assert(NULL != pMediaObj->ldcBuf);

            pMediaObj->currentldcBuf = pMediaObj->ldcBuf;
            compressedBuffer = (UInt8 *)ChainsCommon_Osal_memAlloc(ChainsCommon_Osal_fileSize(fp), 128U);
            UTILS_assert(compressedBuffer != NULL);

            status = ChainsCommon_Osal_fileRead(fp,
                                (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)compressedBuffer),
                                ChainsCommon_Osal_fileSize(fp),
                                &readSize);
            UTILS_assert((0U == status) && (readSize != 0U));

            /*Decompress the read data*/
            toDecompress.inputBufferSize = ChainsCommon_Osal_fileSize(fp);
            UTILS_assert(toDecompress.inputBufferSize > 0U);
            toDecompress.inputBuffer = compressedBuffer;
            toDecompress.outputBuffer = pMediaObj->currentldcBuf;
            toDecompress.outputBufferSize = *(pMediaObj->ldcIdxBuf + SRV_MEDIA_IDX_SET_SIZE_OFFSET + currSetNo);
            toDecompress.operationDone = 0U;
            System_linkControl( SYSTEM_LINK_ID_LZ4_DSP,
                                LZ4_DECOMPRESS_CMD,
                                &toDecompress,
                                sizeof(lz4CompDecomp_inp),
                                TRUE);

            /*Cache wb for the compressed data*/
            ChainsCommon_Osal_cacheWb( (UInt32)toDecompress.inputBuffer,
                                        toDecompress.inputBufferSize);
            /*Cache wb for the compression/decompression structure*/
            ChainsCommon_Osal_cacheWb( (UInt32)&toDecompress,
                                        sizeof(lz4CompDecomp_inp));
            pMediaObj->currentldcBuf += toDecompress.outputBufferSize;

            while(toDecompress.operationDone == 0U);

            ChainsCommon_Osal_memFree(compressedBuffer, ChainsCommon_Osal_fileSize(fp));
            ChainsCommon_Osal_fileClose(fp);

            /*Opening and reading the CARIMG file*/
            /*-----------------------------------------------------------------*/
            pMediaObj->carImgBufSize = *(pMediaObj->carImgIdxBuf + 1U);
            numSets  = *(pMediaObj->carImgIdxBuf + 2U);

            currSetNo = 0U;
            snprintf(filename, SRV_FILENAME_MAX_SIZE, "CARIMG_SET%d.LZ4", currSetNo);
            Vps_printf("SRV MEDIA: Opening %s\n", filename);
            fp = ChainsCommon_Osal_fileOpen( filename, CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
            if(fp == -1)
            {
                Vps_printf("SRV MEDIA: Cannot open file:%s\n", filename);
            }
            UTILS_assert(-1 != fp);

            pMediaObj->carImgBuf = (UInt8 *)ChainsCommon_Osal_memAlloc(pMediaObj->carImgBufSize, 128U);
            UTILS_assert(NULL != pMediaObj->carImgBuf);
            pMediaObj->currentImgBuf = pMediaObj->carImgBuf;
            compressedBuffer = (UInt8 *)ChainsCommon_Osal_memAlloc(ChainsCommon_Osal_fileSize(fp), 128U);
            UTILS_assert(NULL != compressedBuffer);
            status = ChainsCommon_Osal_fileRead(fp,
                                    (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)compressedBuffer),
                                    ChainsCommon_Osal_fileSize(fp),
                                    &readSize);
            UTILS_assert((0U == status) && (readSize != 0U));

            /*Decompress the read data*/
            toDecompress.inputBufferSize = ChainsCommon_Osal_fileSize(fp);
            UTILS_assert(toDecompress.inputBufferSize > 0U);
            toDecompress.inputBuffer = compressedBuffer;
            toDecompress.outputBuffer = pMediaObj->currentImgBuf;
            toDecompress.outputBufferSize = *(pMediaObj->carImgIdxBuf + SRV_MEDIA_IDX_SET_SIZE_OFFSET + currSetNo);
            toDecompress.operationDone = 0U;

            System_linkControl( SYSTEM_LINK_ID_LZ4_DSP,
                                LZ4_DECOMPRESS_CMD,
                                &toDecompress,
                                sizeof(lz4CompDecomp_inp),
                                TRUE);

            /*Cache wb for the compressed data*/
            ChainsCommon_Osal_cacheWb( (UInt32)toDecompress.inputBuffer,
                                        toDecompress.inputBufferSize);
            /*Cache wb for the compression/decompression structure*/
            ChainsCommon_Osal_cacheWb( (UInt32)&toDecompress, sizeof(lz4CompDecomp_inp));

            while(toDecompress.operationDone == 0U);

            pMediaObj->currentImgBuf += toDecompress.outputBufferSize;
            ChainsCommon_Osal_memFree( compressedBuffer, ChainsCommon_Osal_fileSize(fp));
            ChainsCommon_Osal_fileClose(fp);
        }
    }
    else if(fileType == SRV_MEDIA_FILE_LUT)
    {
        /*Opening and reading the LUT file*/
        numSets  = *(pMediaObj->ldcIdxBuf + 2U);
        Vps_printf("SRV MEDIA: Number of Sets:%d\n", numSets);

        for(currSetNo = 1; currSetNo < numSets; currSetNo++)
        {
            /*for the LUT file*/
            snprintf(filename, SRV_FILENAME_MAX_SIZE, "LUT_SET%d.LZ4", currSetNo);
            Vps_printf("SRV MEDIA: Opening: %s", filename);
            fp = ChainsCommon_Osal_fileOpen( filename, CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
            if(fp == -1)
            {
                Vps_printf("SRV MEDIA: Cannot open file:%s\n", filename);
            }
            UTILS_assert(-1 != fp);
            compressedBuffer = (UInt8 *)ChainsCommon_Osal_memAlloc(ChainsCommon_Osal_fileSize(fp), 128U);
            UTILS_assert(NULL != compressedBuffer);
            status = ChainsCommon_Osal_fileRead(fp,
                            (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)compressedBuffer),
                            ChainsCommon_Osal_fileSize(fp),
                            &readSize);
            UTILS_assert((0U == status) && (readSize != 0U));

            toDecompress.inputBufferSize = ChainsCommon_Osal_fileSize(fp);
            UTILS_assert(toDecompress.inputBufferSize > 0U);
            toDecompress.inputBuffer = compressedBuffer;
            toDecompress.outputBuffer = pMediaObj->currentldcBuf;
            toDecompress.outputBufferSize = *(pMediaObj->ldcIdxBuf + SRV_MEDIA_IDX_SET_SIZE_OFFSET + currSetNo);
            toDecompress.operationDone = 0U;

            System_linkControl( SYSTEM_LINK_ID_LZ4_DSP,
                                LZ4_DECOMPRESS_CMD,
                                &toDecompress,
                                sizeof(lz4CompDecomp_inp),
                                TRUE);
            /*Cache wb for the compressed data*/
            ChainsCommon_Osal_cacheWb( (UInt32)toDecompress.inputBuffer,
                                        toDecompress.inputBufferSize);
            /*Cache wb for the compression/decompression structure*/
            ChainsCommon_Osal_cacheWb( (UInt32)&toDecompress,
                                        sizeof(lz4CompDecomp_inp));

            while(toDecompress.operationDone == 0U);

            pMediaObj->currentldcBuf += toDecompress.outputBufferSize;
            ChainsCommon_Osal_memFree( compressedBuffer, ChainsCommon_Osal_fileSize(fp));
            ChainsCommon_Osal_fileClose(fp);

            /*for the CarImg File*/
            snprintf(filename, SRV_FILENAME_MAX_SIZE, "CARIMG_SET%d.LZ4", currSetNo);
            Vps_printf("SRV MEDIA: Opening: %s", filename);
            fp = ChainsCommon_Osal_fileOpen( filename, CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
            if(fp == -1)
            {
                Vps_printf("SRV MEDIA: Cannot open file:%s\n", filename);
            }
            UTILS_assert(-1 != fp);

            compressedBuffer = (UInt8 *)ChainsCommon_Osal_memAlloc(ChainsCommon_Osal_fileSize(fp), 128U);
            UTILS_assert(NULL != compressedBuffer);
            status = ChainsCommon_Osal_fileRead(fp,
                            (UInt8 *)ChainsCommon_Osal_getVirtAddr((UInt32)compressedBuffer),
                            ChainsCommon_Osal_fileSize(fp),
                            &readSize);
            UTILS_assert((0U == status) && (readSize != 0U));

            toDecompress.inputBufferSize = ChainsCommon_Osal_fileSize(fp);
            UTILS_assert(toDecompress.inputBufferSize > 0U);
            toDecompress.inputBuffer = compressedBuffer;
            toDecompress.outputBuffer = pMediaObj->currentImgBuf;
            toDecompress.outputBufferSize = *(pMediaObj->carImgIdxBuf + SRV_MEDIA_IDX_SET_SIZE_OFFSET + currSetNo);
            toDecompress.operationDone = 0U;

            System_linkControl( SYSTEM_LINK_ID_LZ4_DSP,
                                LZ4_DECOMPRESS_CMD,
                                &toDecompress,
                                sizeof(lz4CompDecomp_inp),
                                TRUE);
            /*Cache wb for the compressed data*/
            ChainsCommon_Osal_cacheWb( (UInt32)toDecompress.inputBuffer,
                                        toDecompress.inputBufferSize);
            /*Cache wb for the compression/decompression structure*/
            ChainsCommon_Osal_cacheWb( (UInt32)&toDecompress,
                                        sizeof(lz4CompDecomp_inp));

            while(toDecompress.operationDone == 0U);
            pMediaObj->currentImgBuf += toDecompress.outputBufferSize;
            ChainsCommon_Osal_memFree(compressedBuffer, ChainsCommon_Osal_fileSize(fp));
            ChainsCommon_Osal_fileClose(fp);
        }
    }
    return status;
}
