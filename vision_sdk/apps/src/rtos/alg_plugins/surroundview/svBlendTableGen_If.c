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

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include "include/svSynthesisStruct.h"
#include "include/iSynthesisAlgo.h"
#include "include/alglink_api/algorithmLink_synthesis.h"
#include <math.h>

/*
 *  Seam Angle to use
 */
#define SEAM_ANGLE  (45.0f)

#define _align_4byte(A) ((Byte*)((((Word32)A+3)>>2)<<2))
#define _align_8byte(A) ((UInt8 *)((((Int32)A+7)>>3)<<3))

/*
 *  Car Box from whose edge the seam will pass through
 *      Tested only for 2D top down view
 *      May not work properly for all 3D views with different rotation angles.
 */
#define CAR_W   (0)
#define CAR_H   (0)

void svGenerate_3D_LDC_BlendTable(
                            svSynthStruct *sv,
                            float *seamAngle,
                            Word32 viewRotationAngleRad,
                            SV_Synthesis_ldcSliceListPrm *pSliceListPrm,
                            Byte *outBlendLUTPtr,
                            UInt32 inWidth,
                            UInt32 inHeight,
                            UInt32 subSampleExp,
                            UInt32 *ldcLut,
                            UInt32 ldcLutPitchBytes,
                            UInt32 pixelPad,
                            UInt32 ldcMaxInBlkSize,
                            UInt32 ldcMaxNumSlices,
                            UInt32 *ldcBlkWidth,
                            UInt32 *ldcBlkHeight);

static Word32 initSynthesisRunScratchMem(
                            svSynthStruct *sv,
                            void *MemTabBasePtr)
{
    Word32 usedMemSize;
    Byte*  p_newMem;
    Byte* tempMemory;

    tempMemory = (Byte *)MemTabBasePtr;

    /* Be careful about byte alignment. */
    p_newMem = _align_4byte(tempMemory);

   /*
    *   --------------------------------------------------------------
    *   1st time call: estimate size of memory
    *   2nd time call: assign memory
    *   Assign memory for 4 bytes first, then 2 bytes, then 1 bytes etc
    *   To do: Call p_newMem = _align_4byte(tempMemory) after each section is completed!!
    *   --------------------------------------------------------------
    */

    /* itialize */
    /* Calculate used memory size */
    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

static Word32 initSynthesisRunPersistentMem(
                                svSynthStruct *sv,
                                void *MemTabBasePtr)
{
    Word32 usedMemSize, tmp, i;
    Byte*  p_newMem;
    Byte* tempMemory;

    /* Be careful about byte alignment. */
    tempMemory = (Byte *)MemTabBasePtr;

    p_newMem = _align_4byte(tempMemory);

   /*
    *   --------------------------------------------------------------
    *   1st time call: estimate size of memory
    *   2nd time call: assign memory
    *   Assign memory for 4 bytes first, then 2 bytes, then 1 bytes etc
    *   To do: Call p_newMem = _align_4byte(tempMemory) after each section is completed!!
    *   --------------------------------------------------------------
    */

    /* Word32        PAlignGain_RGB[NUM_INPUT_CAMERAS][NUM_COLOR_CHANNELS]; */
    tmp = sv->numCameras;
    if(tempMemory) sv->PAlignGain_RGB = (Word32**)p_newMem;
    p_newMem += sizeof(Word32*)*tmp;
    for(i=0; i<sv->numCameras; i++){
        tmp = sv->numColorChannels;
        if(tempMemory) sv->PAlignGain_RGB[i] = (Word32*)p_newMem;
        p_newMem += sizeof(Word32)*tmp;
    }

    p_newMem = _align_4byte(p_newMem);

    /* uWord16       *overlapRegMarkPts; //16 element */
    if(tempMemory) sv->overlapRegMarkPts = (uWord16 *)p_newMem;
    tmp = MAX_INPUT_CAMERAS*4; /* maximal size for both RGB and YUV format */
    p_newMem += sizeof(uWord16)*tmp;

    /* uWord16       *seamMarkPts; //8 element */
    if(tempMemory) sv->seamMarkPts = (uWord16 *)p_newMem;
    tmp = MAX_INPUT_CAMERAS*2; /* maximal size for both RGB and YUV format */
    p_newMem += sizeof(uWord16)*tmp;

    /* Calculate used memory size */
    usedMemSize = (Word32) (p_newMem-tempMemory);

    return usedMemSize;
}

void Utils_sv3dGenBlendTable(void *pPrm)
{
    UInt32 memSize, cnt, sliceIdx;
    svSynthStruct svSynthObj;
    AlgorithmLink_blenTableGenPrm *pSynthBlendTableGenPrm =
                                    (AlgorithmLink_blenTableGenPrm*)pPrm;
    SV_Synthesis_ldcSliceListPrm sliceListPrm[ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS];
    float seamAngle[4];

    UTILS_assert (NULL != pSynthBlendTableGenPrm);
    UTILS_assert (NULL != pSynthBlendTableGenPrm->blendTableAddr);

    memset(&svSynthObj, 0x00, sizeof(svSynthStruct));

    Cache_inv(
        pSynthBlendTableGenPrm,
        sizeof(AlgorithmLink_blenTableGenPrm),
        Cache_Type_ALLD,
        TRUE);

    for (cnt = 0;cnt < pSynthBlendTableGenPrm->numCameras;cnt++)
    {
        UTILS_assert (NULL != pSynthBlendTableGenPrm->ldcLut[cnt]);

        Cache_inv(
            (Ptr)pSynthBlendTableGenPrm->ldcLut[cnt],
            pSynthBlendTableGenPrm->ldcLutSize[cnt],
            Cache_Type_ALLD,
            TRUE);
    }

    svSynthObj.blendlen = 30;
    svSynthObj.numCameras = pSynthBlendTableGenPrm->numCameras;
    svSynthObj.SVOutDisplayWidth = pSynthBlendTableGenPrm->SVOutDisplayWidth;
    svSynthObj.SVOutDisplayHeight = pSynthBlendTableGenPrm->SVOutDisplayHeight;
    svSynthObj.svCarBoxParams.CarBoxCenter_x = pSynthBlendTableGenPrm->carBoxX;
    svSynthObj.svCarBoxParams.CarBoxCenter_y = pSynthBlendTableGenPrm->carBoxY;

    memSize = initSynthesisRunPersistentMem(
                        &svSynthObj,
                        pSynthBlendTableGenPrm->persistentBaseAddr);
    UTILS_assert (memSize <= pSynthBlendTableGenPrm->persistentMemSize);

    memSize = initSynthesisRunScratchMem(
                        &svSynthObj,
                        pSynthBlendTableGenPrm->scratchBaseAddr);
    UTILS_assert (memSize <= pSynthBlendTableGenPrm->srcatchMemSize);

    Vps_printf("BLEND_TABLE: Generating Blend table ...");

    memset(&sliceListPrm[0],0x00, sizeof(SV_Synthesis_ldcSliceListPrm) * ALGORITHM_LINK_SRV_SYNTHESIS_MAX_VIEWS);

    /*
     *  The seam angle is fixed at 45 degree
     *  This can be changed as per requirement
     */
#if 0
    seamAngle[0] = 45.0;
    seamAngle[1] = 45.0;
    seamAngle[2] = 45.0;
    seamAngle[3] = 45.0;
#else
    seamAngle[0] = seamAngle[1] = seamAngle[2] = seamAngle[3] = \
    (atanf((float)svSynthObj.SVOutDisplayHeight/(float)svSynthObj.SVOutDisplayWidth) * \
        180.0f)/M_PI;
#endif

    /*
        Car Box co-ordinates:
            The seams are adjusted to pass through the below car box corner points
    */
    svSynthObj.carBoxX[0] = pSynthBlendTableGenPrm->boxCornerX[0];
    svSynthObj.carBoxY[0] = pSynthBlendTableGenPrm->boxCornerY[0];
    svSynthObj.carBoxX[1] = pSynthBlendTableGenPrm->boxCornerX[1];
    svSynthObj.carBoxY[1] = pSynthBlendTableGenPrm->boxCornerY[1];
    svSynthObj.carBoxX[2] = pSynthBlendTableGenPrm->boxCornerX[2];
    svSynthObj.carBoxY[2] = pSynthBlendTableGenPrm->boxCornerY[2];
    svSynthObj.carBoxX[3] = pSynthBlendTableGenPrm->boxCornerX[3];
    svSynthObj.carBoxY[3] = pSynthBlendTableGenPrm->boxCornerY[3];

    Vps_printf("BLEND_TABLE: Corner[0]: X= %d, Y=%d", svSynthObj.carBoxX[0], svSynthObj.carBoxY[0]);
    Vps_printf("BLEND_TABLE: Corner[1]: X= %d, Y=%d", svSynthObj.carBoxX[1], svSynthObj.carBoxY[1]);
    Vps_printf("BLEND_TABLE: Corner[2]: X= %d, Y=%d", svSynthObj.carBoxX[2], svSynthObj.carBoxY[2]);
    Vps_printf("BLEND_TABLE: Corner[3]: X= %d, Y=%d", svSynthObj.carBoxX[3], svSynthObj.carBoxY[3]);

    svGenerate_3D_LDC_BlendTable(
                    &svSynthObj,
                    &seamAngle[0],
                    pSynthBlendTableGenPrm->viewRotationAngleRad,
                    &sliceListPrm[0],
                    (Byte*)pSynthBlendTableGenPrm->blendTableAddr,
                    pSynthBlendTableGenPrm->inWidth,
                    pSynthBlendTableGenPrm->inHeight,
                    pSynthBlendTableGenPrm->subSampleExp,
                    pSynthBlendTableGenPrm->ldcLut,
                    pSynthBlendTableGenPrm->ldcLutPitchBytes,
                    pSynthBlendTableGenPrm->pixelPad,
                    pSynthBlendTableGenPrm->ldcMaxInBlkSize,
                    pSynthBlendTableGenPrm->ldcMaxNumSlices,
                    pSynthBlendTableGenPrm->ldcBlkWidth,
                    pSynthBlendTableGenPrm->ldcBlkHeight);

    Cache_wb(
        pSynthBlendTableGenPrm->blendTableAddr,
        pSynthBlendTableGenPrm->blendTableSize,
        Cache_Type_ALLD,
        TRUE);

    for (cnt = 0;cnt < svSynthObj.numCameras;cnt++)
    {
        pSynthBlendTableGenPrm->chMap[cnt] = svSynthObj.chMap[cnt];

        pSynthBlendTableGenPrm->ldcSlicePrm[cnt].numSlices = \
                                                sliceListPrm[cnt].numSlices;
        for (sliceIdx = 0;sliceIdx < sliceListPrm[cnt].numSlices;sliceIdx++)
        {
            pSynthBlendTableGenPrm->ldcSlicePrm[cnt].slice[sliceIdx].slicePrmType = \
                ALGLINK_SRV_LDC_SLICE_PRMTYPE_ABS;
            pSynthBlendTableGenPrm->ldcSlicePrm[cnt].slice[sliceIdx].blockWidth = \
                sliceListPrm[cnt].slice[sliceIdx].blockWidth;
            pSynthBlendTableGenPrm->ldcSlicePrm[cnt].slice[sliceIdx].blockHeight = \
                sliceListPrm[cnt].slice[sliceIdx].blockHeight;
            pSynthBlendTableGenPrm->ldcSlicePrm[cnt].slice[sliceIdx].sliceX = \
                sliceListPrm[cnt].slice[sliceIdx].sliceX;
            pSynthBlendTableGenPrm->ldcSlicePrm[cnt].slice[sliceIdx].sliceY = \
                sliceListPrm[cnt].slice[sliceIdx].sliceY;
            pSynthBlendTableGenPrm->ldcSlicePrm[cnt].slice[sliceIdx].sliceW = \
                sliceListPrm[cnt].slice[sliceIdx].sliceW;
            pSynthBlendTableGenPrm->ldcSlicePrm[cnt].slice[sliceIdx].sliceH = \
                sliceListPrm[cnt].slice[sliceIdx].sliceH;
        }

        /* Quadrant co-ordinates */
        pSynthBlendTableGenPrm->quadrantStartX[cnt] = svSynthObj.quadrantStartX[cnt];
        pSynthBlendTableGenPrm->quadrantEndX[cnt] = svSynthObj.quadrantEndX[cnt];
        pSynthBlendTableGenPrm->quadrantStartY[cnt] = svSynthObj.quadrantStartY[cnt];
        pSynthBlendTableGenPrm->quadrantEndY[cnt] = svSynthObj.quadrantEndY[cnt];
    }

    Cache_wb(
        pSynthBlendTableGenPrm,
        sizeof(AlgorithmLink_blenTableGenPrm),
        Cache_Type_ALLD,
        TRUE);

    Vps_printf("BLEND_TABLE: Generating Blend Table DONE");
}
