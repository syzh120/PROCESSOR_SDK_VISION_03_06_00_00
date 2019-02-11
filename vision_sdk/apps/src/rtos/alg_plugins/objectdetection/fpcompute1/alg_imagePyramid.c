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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "featurePlaneCompLink_priv.h"

#define Q_FORMATE_SCALE_RATIO                   (12)

void Alg_imagePyramidCalcScaleParams(scalePrams_t *scaleParams,
                uint16_t width,
                uint16_t height,
                uint8_t numScales,
                uint8_t scaleSteps,
                uint16_t * scaleRatiosQ12,
                uint16_t RoiCenterX,
                uint16_t RoiCenterY,
                uint16_t RoiWidth,
                uint16_t RoiHeight,
                uint8_t sreachStep)
{
  uint8_t i;

  scaleParams[0].orgWidth  = width;
  scaleParams[0].orgHeight = height;

  for(i = 1; i < numScales; i++)
  {
    scaleParams[i].orgWidth  = ((scaleParams[((i-1)/scaleSteps)*scaleSteps].orgWidth *(1 << Q_FORMATE_SCALE_RATIO))/ scaleRatiosQ12[i%scaleSteps])&(~1);
    scaleParams[i].orgHeight = ((scaleParams[((i-1)/scaleSteps)*scaleSteps].orgHeight*(1 << Q_FORMATE_SCALE_RATIO))/ scaleRatiosQ12[i%scaleSteps])&(~1);
  }

  for( i = 0; i < numScales; i++)
  {
      uint32_t xNum  = ((RoiCenterX >> (i/scaleSteps)) * (1 << Q_FORMATE_SCALE_RATIO));
      uint32_t yNum  = ((RoiCenterY >> (i/scaleSteps)) * (1 << Q_FORMATE_SCALE_RATIO));
      uint32_t xDen  = (scaleRatiosQ12[i%scaleSteps]);
      uint32_t imWidth  = scaleParams[i].orgWidth ;
      uint32_t imHidth  = scaleParams[i].orgHeight;
      if(i%scaleSteps)
      {
        xNum = (xNum/xDen);
        yNum = (yNum/xDen);
      }
      else
      {
        xNum = (xNum/(1 << Q_FORMATE_SCALE_RATIO));
        yNum = (yNum/(1 << Q_FORMATE_SCALE_RATIO));
      }

      if(RoiWidth >= imWidth)
      {
        scaleParams[i].x = 0;
        scaleParams[i].width = imWidth;
      }
      else
      {
        scaleParams[i].width = RoiWidth;
        scaleParams[i].x = ((int)xNum-(int)scaleParams[i].width/2) < 0 ? 0 : (xNum-scaleParams[i].width/2);
        scaleParams[i].x = (scaleParams[i].x + RoiWidth) > imWidth ? imWidth - scaleParams[i].width : scaleParams[i].x;
      }

      if(RoiHeight >= imHidth)
      {
        scaleParams[i].y = 0;
        scaleParams[i].height = imHidth;
      }
      else
      {
        scaleParams[i].height = RoiHeight;
        scaleParams[i].y =((int)yNum-(int)scaleParams[i].height/2) < 0 ? 0 :(yNum-scaleParams[i].height/2) ;
        scaleParams[i].y = (scaleParams[i].y + RoiHeight) > imHidth ? imHidth - scaleParams[i].height : scaleParams[i].y;
      }

      scaleParams[i].x      = (scaleParams[i].x / sreachStep)*sreachStep;
      scaleParams[i].y      = (scaleParams[i].y / sreachStep)*sreachStep;
      scaleParams[i].width  = (scaleParams[i].width / sreachStep)*sreachStep;
      scaleParams[i].height = (scaleParams[i].height / sreachStep)*sreachStep;
  }

  #if 1
  for(i = 0; i < numScales; i++)
  {
        Vps_printf(" ALG_IMAGEPYRAMID: ScalePrms #%d: %d,%d %dx%d (org = %d x %d)",
            i,
            scaleParams[i].x,
            scaleParams[i].y,
            scaleParams[i].width,
            scaleParams[i].height,
            scaleParams[i].orgWidth,
            scaleParams[i].orgHeight
            );
  }
  #endif
}

Int32 Alg_imagePyramidCreate(
            Alg_ImagePyramidObj *pObj,
            Alg_Filter2dObj *pFilter2dObj,
            UInt8 numScales,
            UInt8 scaleSteps,
            UInt16 roiCenterX,
            UInt16 roiCenterY,
            UInt16 roiWidth,
            UInt16 roiHeight
)
{
    uint16_t scaleRatiosQ12[ALG_IMAGE_PYRAMID_MAX_SCALE_STEPS];
    uint16_t scaleRatioQ12;
    UInt16 orgWidth, orgHeight, inWidth, inHeight, i, outWidth, outHeight, idx;
    UInt16 outStartX, outStartY, inStartX, inStartY;
    UInt32 inPitch[2];
    UInt8 *inAddr[2];

    UTILS_assert(pObj!=NULL);
    UTILS_assert(pObj->scalePrms!=NULL);
    UTILS_assert(numScales <= ALG_IMAGE_PYRAMID_MAX_SCALES);

    memset(pObj, 0, sizeof(*pObj));

    pObj->numScales = numScales;
    pObj->scaleSteps = scaleSteps;

    orgWidth = pFilter2dObj->outWidth;
    orgHeight = pFilter2dObj->outHeight;

    if(scaleSteps == 6)
    {
        scaleRatiosQ12[0] = 8192;
        scaleRatiosQ12[1] = 4597;
        scaleRatiosQ12[2] = 5160;
        scaleRatiosQ12[3] = 5792;
        scaleRatiosQ12[4] = 6501;
        scaleRatiosQ12[5] = 7298;
    }
    else
    {
        scaleRatiosQ12[0] = 8192;
        scaleRatiosQ12[1] = 4466;
        scaleRatiosQ12[2] = 4870;
        scaleRatiosQ12[3] = 5311;
        scaleRatiosQ12[4] = 5792;
        scaleRatiosQ12[5] = 6316;
        scaleRatiosQ12[6] = 6888;
        scaleRatiosQ12[7] = 7512;
    }

    pObj->sreachStep = 4;

    Alg_imagePyramidCalcScaleParams(
        pObj->scalePrms,
        orgWidth,
        orgHeight,
        numScales,
        scaleSteps,
        scaleRatiosQ12,
        roiCenterX,
        roiCenterY,
        roiWidth,
        roiHeight,
        pObj->sreachStep
        );

    for(i=1; i<numScales; i++)
    {
        pObj->prms[i].visionParams.algParams.size =
            sizeof(pObj->prms[i]);

        pObj->prms[i].visionParams.cacheWriteBack = NULL;
        pObj->prms[i].maxWidth      = orgWidth + 192;
        pObj->prms[i].maxHeight     = orgHeight + 64;
        pObj->prms[i].scaleRatioQ12 = scaleRatiosQ12[i%scaleSteps];
        pObj->prms[i].scalingMethod = 0;
        pObj->prms[i].fracQFmt      = 4;
        pObj->prms[i].outStartX     = pObj->scalePrms[i].x;
        pObj->prms[i].outStartY     = pObj->scalePrms[i].y;

        pObj->handle[i] = AlgIvision_create(
                    &YUV_SCALAR_TI_VISION_FXNS,
                    (IALG_Params*)&pObj->prms[i]
                    );
        UTILS_assert(pObj->handle[i]!=NULL);

        if(i%scaleSteps)
        {
            outWidth  = pObj->scalePrms[i].width;
            outHeight = pObj->scalePrms[i].height;
        }
        else
        {
            outWidth  = orgWidth  >> (i/scaleSteps);
            outHeight = orgHeight >> (i/scaleSteps);
        }

        outWidth  = SystemUtils_align(outWidth,384);
        outHeight = SystemUtils_align(outHeight,64);

        pObj->outBufSize[i][0] = outWidth * outHeight;
        pObj->outBufSize[i][1] = outWidth * outHeight/2;
        pObj->outPitch[i][0] = outWidth;
        pObj->outPitch[i][1] = outWidth;

        pObj->outBufAddr[i][0] =
            Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pObj->outBufSize[i][0],
                32
            );
        UTILS_assert(pObj->outBufAddr[i][0]!=NULL);
        pObj->outBufAddr[i][1] =
            Utils_memAlloc(
                UTILS_HEAPID_DDR_CACHED_SR,
                pObj->outBufSize[i][1],
                32
            );
        UTILS_assert(pObj->outBufAddr[i][1]!=NULL);
    }

    pObj->outPitch[0][0] = pFilter2dObj->outPitch[0];
    pObj->outPitch[0][1] = pFilter2dObj->outPitch[1];
    pObj->outBufAddr[0][0] = pFilter2dObj->outBufAddr[0];
    pObj->outBufAddr[0][1] = pFilter2dObj->outBufAddr[1];

    for(i=1; i<numScales; i++)
    {
        if(i <= scaleSteps)
        {
            inPitch[0] = pFilter2dObj->outPitch[0];
            inPitch[1] = pFilter2dObj->outPitch[1];
            inAddr[0] = pFilter2dObj->outBufAddr[0];
            inAddr[1] = pFilter2dObj->outBufAddr[1];
        }
        else
        {
            idx = ((i-1)/scaleSteps)*scaleSteps;

            inPitch[0] = pObj->outPitch[idx][0];
            inPitch[1] = pObj->outPitch[idx][1];
            inAddr[0]  = pObj->outBufAddr[idx][0];
            inAddr[1]  = pObj->outBufAddr[idx][1];
        }

        scaleRatioQ12  = scaleRatiosQ12[i%scaleSteps];

        inWidth   = orgWidth  >> ((i-1)/scaleSteps);
        inHeight  = orgHeight >> ((i-1)/scaleSteps);

        if(i%scaleSteps == 0)
        {
              outWidth  =  orgWidth  >> (i/scaleSteps);
              outHeight =  orgHeight >> (i/scaleSteps);
              outStartX =  0;
              outStartY =  0;
        }
        else
        {
              outWidth   =  pObj->scalePrms[i].width;
              outHeight  =  pObj->scalePrms[i].height;
              outStartX  =  pObj->scalePrms[i].x;
              outStartY  =  pObj->scalePrms[i].y;
              inStartX   = ((outStartX * scaleRatioQ12) / (1 << (Q_FORMATE_SCALE_RATIO))) ;
              inStartY   = ((outStartY * scaleRatioQ12) / (1 << (Q_FORMATE_SCALE_RATIO))) ;
              inAddr[0] += inStartY*inPitch[0] + inStartX;
              inStartX   = (((outStartX/2) * scaleRatioQ12) / (1 << (Q_FORMATE_SCALE_RATIO))) ;
              inStartY   = (((outStartY/2) * scaleRatioQ12) / (1 << (Q_FORMATE_SCALE_RATIO))) ;
              inAddr[1] += inStartY*inPitch[1] + inStartX*2;
        }

        pObj->inArgs[i].iVisionInArgs.size =
            sizeof(pObj->inArgs[i]);

        pObj->outArgs[i].iVisionOutArgs.size =
            sizeof(pObj->outArgs[i]);

        pObj->inBufs[i].size = sizeof(pObj->inBufs);
        pObj->inBufs[i].numBufs = 1;
        pObj->inBufs[i].bufDesc  = pObj->inBufDescList[i];

        pObj->outBufs[i].size = sizeof(pObj->outBufs[i]);
        pObj->outBufs[i].numBufs = 1;
        pObj->outBufs[i].bufDesc = pObj->outBufDescList[i];

        pObj->inBufDescList[i][0] = &pObj->inBufDesc[i];
        pObj->outBufDescList[i][0] = &pObj->outBufDesc[i];

        pObj->inBufDesc[i].numPlanes                          = 2;
        pObj->inBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = 0;
        pObj->inBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = 0;
        pObj->inBufDesc[i].bufPlanes[0].width                 = inPitch[0];
        pObj->inBufDesc[i].bufPlanes[0].height                = inHeight;
        pObj->inBufDesc[i].bufPlanes[0].frameROI.width        = inWidth;
        pObj->inBufDesc[i].bufPlanes[0].frameROI.height       = inHeight;
        pObj->inBufDesc[i].bufPlanes[0].planeType             = 0; //Luma Y
        pObj->inBufDesc[i].bufPlanes[0].buf                   = inAddr[0];

        pObj->inBufDesc[i].bufPlanes[1].frameROI.topLeft.x    = 0;
        pObj->inBufDesc[i].bufPlanes[1].frameROI.topLeft.y    = 0;
        pObj->inBufDesc[i].bufPlanes[1].width                 = inPitch[1];
        pObj->inBufDesc[i].bufPlanes[1].height                = inHeight/2;
        pObj->inBufDesc[i].bufPlanes[1].frameROI.width        = inWidth;
        pObj->inBufDesc[i].bufPlanes[1].frameROI.height       = inHeight/2;
        pObj->inBufDesc[i].bufPlanes[1].planeType             = 1; //C
        pObj->inBufDesc[i].bufPlanes[1].buf                   = inAddr[1];

        pObj->outBufDesc[i].numPlanes                          = 2;
        pObj->outBufDesc[i].bufPlanes[0].frameROI.topLeft.x    = 0;
        pObj->outBufDesc[i].bufPlanes[0].frameROI.topLeft.y    = 0;
        pObj->outBufDesc[i].bufPlanes[0].width                 = pObj->outPitch[i][0];
        pObj->outBufDesc[i].bufPlanes[0].height                = outHeight;
        pObj->outBufDesc[i].bufPlanes[0].frameROI.width        = outWidth;
        pObj->outBufDesc[i].bufPlanes[0].frameROI.height       = outHeight;
        pObj->outBufDesc[i].bufPlanes[0].planeType             = 0; //Luma Y
        pObj->outBufDesc[i].bufPlanes[0].buf                   = pObj->outBufAddr[i][0];

        pObj->outBufDesc[i].bufPlanes[1].frameROI.topLeft.x    = 0;
        pObj->outBufDesc[i].bufPlanes[1].frameROI.topLeft.y    = 0;
        pObj->outBufDesc[i].bufPlanes[1].width                 = pObj->outPitch[i][1];
        pObj->outBufDesc[i].bufPlanes[1].height                = outHeight/2;
        pObj->outBufDesc[i].bufPlanes[1].frameROI.width        = outWidth;
        pObj->outBufDesc[i].bufPlanes[1].frameROI.height       = outHeight/2;
        pObj->outBufDesc[i].bufPlanes[1].planeType             = 1; //Chroma UV
        pObj->outBufDesc[i].bufPlanes[1].buf                   = pObj->outBufAddr[i][1];

        #if 0
        Vps_printf(" ALG_IMAGEPYRAMID: #%d: %dx%d (pitch=%d, buf[0]=(0x%8x, %d b), buf[1]=(0x%8x, %d b)) => %dx%d (pitch=%d, buf[0]=(0x%8x, %d b), buf[1]=(0x%8x, %d b))\n",
            i,
            inWidth,
            inHeight,
            inPitch[0],
            inAddr[0],
            0,
            inAddr[1],
            0,
            outWidth,
            outHeight,
            pObj->outPitch[i][0],
            pObj->outBufAddr[i][0],
            pObj->outBufSize[i][0],
            pObj->outBufAddr[i][1],
            pObj->outBufSize[i][1]
            );
        #endif
    }

    return 0;
}

Int32 Alg_imagePyramidProcess(
            Alg_ImagePyramidObj *pObj
        )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt16 i;

    for(i=1; i<pObj->numScales; i++)
    {
        status = AlgIvision_process(
                    pObj->handle[i],
                    &pObj->inBufs[i],
                    &pObj->outBufs[i],
                    (IVISION_InArgs*)&pObj->inArgs[i],
                    (IVISION_OutArgs*)&pObj->outArgs[i]
                );
        UTILS_assert(status==0);
    }
    return status;
}

Int32 Alg_imagePyramidDelete(Alg_ImagePyramidObj *pObj)
{
    UInt16 i;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    for(i=1; i<pObj->numScales; i++)
    {
        status = AlgIvision_delete(pObj->handle[i]);
        UTILS_assert(status==0);

        status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pObj->outBufAddr[i][0],
                pObj->outBufSize[i][0]
            );
        UTILS_assert(status==0);

        status = Utils_memFree(
                UTILS_HEAPID_DDR_CACHED_SR,
                pObj->outBufAddr[i][1],
                pObj->outBufSize[i][1]
            );
        UTILS_assert(status==0);
    }

    return status;
}
