/*
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
*/

/**
 *******************************************************************************
 *
 * \file encLink_h264.c Encode Link H264 private/specific API/function calls
 *
 * \brief  This file implemented the below H264 Encoder functions
 *         - Create/Delete/Control
 *         - Process call
 *         - set static/dynamic parameters
 *
 * \version 0.0 (Aug 2014) : [SS] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <src/rtos/links_ipu/iva/codec_utils/src/alg.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/xdais/dm/ividenc2.h>
#include <ti/sdo/codecs/h264enc/ih264enc.h>
#include <ti/sdo/codecs/h264enc/h264enc_ti.h>

#include "encLink_priv.h"
#include "encLink_h264_priv.h"
#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>
#include <src/rtos/links_ipu/iva/codec_utils/iresman_hdvicp2_earlyacquire.h>

#define ENCLINK_H264_SETNALU_MASK_SPS(naluMask) ((naluMask) |= (1 << IH264_NALU_TYPE_SPS_WITH_VUI))
#define ENCLINK_H264_SETNALU_MASK_PPS(naluMask) ((naluMask) |= (1 << IH264_NALU_TYPE_PPS))
#define ENCLINK_H264_SETNALU_MASK_SEI(naluMask) ((naluMask) |= (1 << IH264_NALU_TYPE_USER_DATA_UNREGD_SEI))

/*******************************************************************************
 *  Encode Link H264 Private Functions
 *******************************************************************************
 */
static IH264ENC_Handle enc_link_h264_create(const IH264ENC_Fxns * fxns,
                                            const IH264ENC_Params * prms);
static Void enc_link_h264_delete(IH264ENC_Handle handle);
static Int32 enclink_h264_control(IH264ENC_Handle handle,
                                  IH264ENC_Cmd cmd,
                                  IH264ENC_DynamicParams * params,
                                  IH264ENC_Status * status);
static Int enclink_h264_set_static_params(IH264ENC_Params * staticParams,
                                          EncLink_AlgCreateParams *
                                          algCreateParams);
static Int enclink_h264_set_algObject(EncLink_H264Obj * algObj,
                                      EncLink_AlgCreateParams * algCreateParams,
                                      EncLink_AlgDynamicParams *
                                      algDynamicParams);
static Int enclink_h264_set_dynamic_params(IH264ENC_DynamicParams *
                                           dynamicParams,
                                           EncLink_AlgDynamicParams *
                                           algDynamicParams);
static Void enclink_h264_freersrc(EncLink_H264Obj * hObj, Int rsrcMask);

static Int32 EncLink_h264EncoderReset(EncLink_H264Obj * hObj);

extern IRES_Fxns H264ENC_TI_IRES;
extern const IH264ENC_DynamicParams H264ENC_TI_DYNAMICPARAMS;

/**
 *******************************************************************************
 *
 * \brief This function create the H264 codec instance
 *        Create an H264ENC instance object(using parameters specified by prms)
 *
 * \param  fxns     [IN]  IH264VENC_Fxns - codec function pointers
 * \param  prms     [OUT] IH264VENC_Params params
 *
 * \return  H264VENC_Handle - codec handle on success
 *
 *******************************************************************************
 */
static IH264ENC_Handle enc_link_h264_create(const IH264ENC_Fxns * fxns,
                                            const IH264ENC_Params * prms)
{
    return ((IH264ENC_Handle) ALG_create((IALG_Fxns *) fxns,
                                         NULL, (IALG_Params *) prms));
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance handle
 *        Delete the H264ENC instance object specified by handle
 *
 * H264VENC_Handle - codec handle
 *
 * \return  Non
 *
 *******************************************************************************
 */
static Void enc_link_h264_delete(IH264ENC_Handle handle)
{
    ALG_delete((IALG_Handle) handle);
}

/**
 *******************************************************************************
 *
 * \brief This function set/get the H264 codec parameter/state
 *
 * \param  handle   [IN]  H264VENC_Handle - codec handle
 * \param  cmd      [IN]  IH264VENC_Cmd commands
 * \param  params   [IN]  IH264VENC_DynamicParams - codec dynamic parameters
 * \param  status   [OUT] IH264VENC_Status status
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int32 enclink_h264_control(IH264ENC_Handle handle,
                                  IH264ENC_Cmd cmd,
                                  IH264ENC_DynamicParams * params,
                                  IH264ENC_Status * status)
{
    int error = 0;
    IALG_Fxns *fxns = (IALG_Fxns *) handle->fxns;

    fxns->algActivate((IALG_Handle) handle);

    error = handle->fxns->ividenc.control((IVIDENC2_Handle) handle, cmd,
                                          (IVIDENC2_DynamicParams *) params,
                                          (IVIDENC2_Status *) status);
    fxns->algDeactivate((IALG_Handle) handle);

    if (error != XDM_EOK)
    {
        Vps_printf(" ENCODE: ERROR: ALGCONTROL FAILED CMD=0x%08x (status=%08x) !!!\n",
                     cmd, error);
    }
    return error;
}

/**
 *******************************************************************************
 *
 * \brief This function free-up the resouces allocated by the codec instance
 *
 * \param  inputBufDesc     [IN]  IVIDEO2_BufDesc - input buffer object
 * \param  secField         [OUT]  FVID2_Frame - second filed buffer
 *
 * \return  None
 *
 *******************************************************************************
 */
Int32 Enclink_h264CalcSecondFieldOffsets(IVIDEO2_BufDesc *inputBufDesc,
                                         FVID2_Frame *secField)
{
    Int retVal = ENC_LINK_S_SUCCESS;
    UInt32 addr, i;
    Int32 addrOffset, secondFieldOffsetHeight, secondFieldOffsetWidth;

    for (i=0; i<inputBufDesc->numPlanes; i++)
    {
        addr = (UInt32) secField->addr[0][i];

        addrOffset = addr - (UInt32)inputBufDesc->planeDesc[i].buf;


        secondFieldOffsetHeight = addrOffset/inputBufDesc->imagePitch[i];

        secondFieldOffsetWidth = addrOffset -
                       (secondFieldOffsetHeight * inputBufDesc->imagePitch[i]);

        inputBufDesc->secondFieldOffsetHeight[i] = secondFieldOffsetHeight;
        inputBufDesc->secondFieldOffsetWidth[i] = secondFieldOffsetWidth;
    }

    inputBufDesc->secondFieldOffsetHeight[2] =
                  inputBufDesc->secondFieldOffsetHeight[1];
    inputBufDesc->secondFieldOffsetWidth[2] =
                  inputBufDesc->secondFieldOffsetWidth[1];

    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief This function perform H264 Encode of an input compressed bitstream
 *
 * \param  pChObj          [IN]  EncLink_ChObj - Enc link channel Object
 * \param  pReqObj         [IN]  EncLink_ReqObj - Enc link request object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int32 Enclink_H264EncodeFrame(EncLink_ChObj * pChObj, EncLink_ReqObj * pReqObj)
{
    int error = XDM_EFAIL;
    Int32 i;
    IH264ENC_InArgs *inArgs;
    IH264ENC_OutArgs *outArgs;
    IVIDEO2_BufDesc *inputBufDesc;
    XDM2_BufDesc *outputBufDesc;
    IH264ENC_Handle handle = NULL;
    IALG_Fxns *fxns = NULL;
    System_IVideoContentType contentType;
    Int32 status = ENC_LINK_S_SUCCESS;
    System_BitstreamBuffer *outBuf = NULL;
    System_VideoFrameBuffer *inFrame = NULL;

    UTILS_assert(ENC_LINK_REQ_OBJECT_TYPE_REGULAR == pReqObj->type);

    if ((pChObj->algObj.u.h264AlgIfObj.staticParams.videnc2Params.inputContentType ==
         IVIDEO_PROGRESSIVE)
         ||
         (pChObj->expectedFid != FVID2_FID_BOTTOM))
    {
        status = EncLinkH264_algSetConfig(&pChObj->algObj);
    }
    pChObj->expectedFid ^= FVID2_FID_BOTTOM;
    status = EncLinkH264_algGetConfig(&pChObj->algObj);

    if (ENC_LINK_S_SUCCESS != status)
    {
      return XDM_EFAIL;
    }

    inArgs = &pChObj->algObj.u.h264AlgIfObj.inArgs;
    outArgs = &pChObj->algObj.u.h264AlgIfObj.outArgs;
    inputBufDesc = &pChObj->algObj.u.h264AlgIfObj.inBufs;
    outputBufDesc = &pChObj->algObj.u.h264AlgIfObj.outBufs;
    handle = pChObj->algObj.u.h264AlgIfObj.algHandle;

    UTILS_assert(handle != NULL);

    fxns = (IALG_Fxns *) handle->fxns;

    inArgs->videnc2InArgs.inputID =
            (UInt32) pReqObj->InFrameList.buffers[0];
    inFrame = (System_VideoFrameBuffer*)pReqObj->InFrameList.buffers[0]->payload;

    for (i = 0; i < inputBufDesc->numPlanes; i++)
    {
        /* Set proper buffer addresses for Frame data */
        inputBufDesc->planeDesc[i].buf = inFrame->bufAddr[i];
    }

    if (pReqObj->InFrameList.numBuf == 2)
    {
#if 0
        /* Now commenting out, This will be fixed later */
        System_VideoFrameBuffer *inFrame1 = NULL;
        inFrame1 = (System_VideoFrameBuffer*)pReqObj->InFrameList.buffers[1]->payload;

        UTILS_assert (FVID2_FID_TOP == (FVID2_Fid)pReqObj->InFrameList.frames[0]->fid);
        UTILS_assert (FVID2_FID_BOTTOM == (FVID2_Fid)pReqObj->InFrameList.frames[1]->fid);
        Enclink_h264CalcSecondFieldOffsets(inputBufDesc,
                               pReqObj->InFrameList.frames[1]);

        UTILS_assert ((UInt32) pReqObj->InFrameList.frames[0]->addr[0][0] +
                      inputBufDesc->imagePitch[0] *
                      (inputBufDesc->secondFieldOffsetHeight[0])
                      + inputBufDesc->secondFieldOffsetWidth[0] ==
                      (UInt32) pReqObj->InFrameList.frames[1]->addr[0][0]);

        UTILS_assert ((UInt32) pReqObj->InFrameList.frames[0]->addr[0][1] +
                      inputBufDesc->imagePitch[1]*
                      (inputBufDesc->secondFieldOffsetHeight[1])
                      + inputBufDesc->secondFieldOffsetWidth[1] ==
                      (UInt32) pReqObj->InFrameList.frames[1]->addr[0][1]);
#endif
    }

    outBuf = (System_BitstreamBuffer*) pReqObj->OutBuf->payload;
    outBuf->metaFillLength = 0;

    for (i = 0; i < outputBufDesc->numBufs; i++)
    {
        if(i == 0)
        {
          /* Set proper buffer addresses for bitstream data */
          /*---------------------------------------------------------------*/
            outputBufDesc->descs[i].buf = outBuf->bufAddr;
            outputBufDesc->descs[i].bufSize.bytes =outBuf->bufSize;
        }

        if(i == 1)
        {
            /*-------------------------------------------------------------------*/
                /* Set proper buffer addresses for MV & SAD data */
            /*-------------------------------------------------------------------*/
            outputBufDesc->descs[1].buf = outputBufDesc->descs[0].buf +
                                       outputBufDesc->descs[0].bufSize.bytes;
        }
    }

   fxns->algActivate((IALG_Handle) handle);
   error = ((IVIDENC2_Handle)handle)->fxns->process((IVIDENC2_Handle)handle,
                                                     inputBufDesc,outputBufDesc,
                                                     (IVIDENC2_InArgs *)inArgs,
                                                     (IVIDENC2_OutArgs *)outArgs);
   fxns->algDeactivate((IALG_Handle) handle);

   outBuf->fillLength = outArgs->videnc2OutArgs.bytesGenerated;

   outBuf->flags = System_Bitstream_Buffer_Flag_Set_Bitstream_Format
                                    (outBuf->flags,
                                    SYSTEM_BITSTREAM_CODING_TYPE_H264);

   if (pChObj->algObj.u.h264AlgIfObj.staticParams.videnc2Params.
       inputContentType == SYSTEM_IVIDEO_PROGRESSIVE)
   {
       contentType = SYSTEM_IVIDEO_PROGRESSIVE;
   }
   else
   {
       contentType = Utils_encdecMapSYSFID2XDMContentType((System_Fid)
                         System_Video_Frame_Get_Flag_Fid (inFrame->flags));
   }

   outBuf->flags = System_Bitstream_Buffer_Flag_Set_Is_Keyframe (outBuf->flags,
          Utils_encdecIsGopStart(outArgs->videnc2OutArgs.encodedFrameType,
                                 contentType));
   outBuf->width = inputBufDesc->imageRegion.bottomRight.x -
                   inputBufDesc->imageRegion.topLeft.x;
   outBuf->height = inputBufDesc->imageRegion.bottomRight.y -
                    inputBufDesc->imageRegion.topLeft.y;

   if (error != XDM_EOK)
   {
	  Vps_printf(" ENCODE: ERROR: ALGPROCESS FAILED (status=0x%08x) !!!\n",
                error);
   }

   return (error);
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate H264 Encoder static parameters
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoEncoder_002)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1273)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1261)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1451)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1453)
 *          DES_ID: DOX_DES_TAG(DES_VideoEncoder_004)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1452)
 *
 * \param  params   [IN] IH264VENC_Params - H264 static parameters
 * \param  status   [IN] EncLink_AlgCreateParams - Enc Link static parameters
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_h264_set_static_params(IH264ENC_Params * staticParams,
                                          EncLink_AlgCreateParams *
                                          algCreateParams)
{
    /* Initialize default values for static params */
    *staticParams = H264ENC_TI_PARAMS;

    /* Both width & height needs to be align with 2 bytes */
    staticParams->videnc2Params.maxHeight =
                  VpsUtils_align(algCreateParams->maxHeight, 2);

    staticParams->videnc2Params.maxWidth =
                  VpsUtils_align(algCreateParams->maxWidth, 16);

    staticParams->videnc2Params.maxInterFrameInterval =
        algCreateParams->maxInterFrameInterval;

    staticParams->videnc2Params.inputContentType =
        algCreateParams->inputContentType;

    staticParams->videnc2Params.inputChromaFormat =
        algCreateParams->inputChromaFormat;

    if (algCreateParams->format == SYSTEM_IVIDEO_H264BP)
        staticParams->videnc2Params.profile = IH264_BASELINE_PROFILE;
    else if (algCreateParams->format == SYSTEM_IVIDEO_H264MP)
        staticParams->videnc2Params.profile = IH264_MAIN_PROFILE;
    else if (algCreateParams->format == SYSTEM_IVIDEO_H264HP)
        staticParams->videnc2Params.profile = IH264_HIGH_PROFILE;

    staticParams->videnc2Params.level = IH264_LEVEL_40;

    staticParams->videnc2Params.encodingPreset = algCreateParams->encodingPreset;

    if ((staticParams->videnc2Params.encodingPreset == XDM_USER_DEFINED) &&
        (algCreateParams->enableHighSpeed == TRUE))
    {
        staticParams->interCodingParams.interCodingPreset =
            IH264_INTERCODING_HIGH_SPEED;
        staticParams->intraCodingParams.intraCodingPreset =
            IH264_INTRACODING_HIGH_SPEED;
        staticParams->transformBlockSize = IH264_TRANSFORM_8x8;
    }
    /* In case of interlaced encode, below would be used. In case of progressive
        this will be ignored. */
    staticParams->enableAnalyticinfo = algCreateParams->enableAnalyticinfo;
    staticParams->enableWatermark = algCreateParams->enableWaterMarking;
    staticParams->videnc2Params.rateControlPreset = IVIDEO_USER_DEFINED;
    staticParams->rateControlParams.rateControlParamsPreset = IH264_RATECONTROLPARAMS_USERDEFINED;
    staticParams->rateControlParams.scalingMatrixPreset
        = IH264_SCALINGMATRIX_NONE;
    staticParams->rateControlParams.rcAlgo = algCreateParams->rateControlPreset;
    staticParams->videnc2Params.maxBitRate = algCreateParams->maxBitRate;

    staticParams->videnc2Params.inputDataMode = IVIDEO_ENTIREFRAME;
    staticParams->videnc2Params.outputDataMode = IVIDEO_ENTIREFRAME;


    /* Number of temporal layeers set to 1. This is the default value  */
    /* in the codec*/
    if (0 == algCreateParams->numTemporalLayer)
    {
        staticParams->numTemporalLayer = IH264_TEMPORAL_LAYERS_1;
    }
    else
    {
        staticParams->numTemporalLayer = algCreateParams->numTemporalLayer;
    }

    /*Note: Enabling this flag adds svc enxtension header to the stream, not all decoders
          are generally able to play back such a stream. */
    /* Needs to be enabled to IH264_SVC_EXTENSION_FLAG_ENABLE for the
          svc extension headers to be present in the stream*/
    /*!!! Note: This flag needs to be enabled for the temporalId to be parsed
         out from the stream.*/
    staticParams->svcCodingParams.svcExtensionFlag =
		        algCreateParams->enableSVCExtensionFlag;

    /*Slice Coding Parameters*/
    staticParams->sliceCodingParams.sliceCodingPreset = IH264_SLICECODING_DEFAULT;
    staticParams->sliceCodingParams.sliceMode = IH264_SLICEMODE_NONE;
    staticParams->sliceCodingParams.streamFormat = IH264_STREAM_FORMAT_DEFAULT;


    /* To set IDR frame periodically instead of I Frame */
    staticParams->IDRFrameInterval = 1;
    /* Override with App settings */
    staticParams->IDRFrameInterval = algCreateParams->IDRFrameInterval;

    /*To trigger workaround inside codec, where SAME_CODEC is overridden as same
      codec type*/
    staticParams->reservedParams[1] = 0x5A3EC0DE;

    /* Enabling debug logging inside the codec. Details in appendix E in H.264
     * encoder user guide.
     */
#ifdef ENCLINK_H264_PERFORMANCE_LOGGING
     staticParams->debugTraceLevel = 1;
     staticParams->lastNFramesToLog = ENCLINK_H264_PROFILER_NUM_FRAMES;
#endif

    /* We want SPS and PPS to be set for every intra frame. Hence configure the
     * the NALU control params to force encoder to insert SPS/PPS on every
     * I frame
     */
    staticParams->nalUnitControlParams.naluControlPreset =
                                             IH264_NALU_CONTROL_USERDEFINED;
    ENCLINK_H264_SETNALU_MASK_SPS(staticParams->nalUnitControlParams.
                                                naluPresentMaskIntraPicture);
    ENCLINK_H264_SETNALU_MASK_PPS(staticParams->nalUnitControlParams.
                                                naluPresentMaskIntraPicture);
    ENCLINK_H264_SETNALU_MASK_SEI(staticParams->nalUnitControlParams.
                                                naluPresentMaskIntraPicture);

    ENCLINK_H264_SETNALU_MASK_SPS(staticParams->nalUnitControlParams.
                                                naluPresentMaskIDRPicture);
    ENCLINK_H264_SETNALU_MASK_PPS(staticParams->nalUnitControlParams.
                                                naluPresentMaskIDRPicture);
    ENCLINK_H264_SETNALU_MASK_SEI(staticParams->nalUnitControlParams.
                                                naluPresentMaskIDRPicture);

    ENCLINK_H264_SETNALU_MASK_SPS(staticParams->nalUnitControlParams.
                                                naluPresentMaskStartOfSequence);
    ENCLINK_H264_SETNALU_MASK_PPS(staticParams->nalUnitControlParams.
                                                naluPresentMaskStartOfSequence);
    ENCLINK_H264_SETNALU_MASK_SEI(staticParams->nalUnitControlParams.
                                                naluPresentMaskStartOfSequence);

    staticParams->entropyCodingMode = IH264_ENTROPYCODING_CABAC;
    if (algCreateParams->profile != IH264_HIGH_PROFILE)
    {
        memset (&staticParams->intraCodingParams, 0,
                               sizeof(IH264ENC_IntraCodingParams));
        staticParams->transformBlockSize = IH264_TRANSFORM_4x4;
        if (algCreateParams->profile == IH264_BASELINE_PROFILE)
        {
            staticParams->entropyCodingMode = IH264_ENTROPYCODING_CAVLC;
        }
    }

#if 1
    staticParams->vuiCodingParams.vuiCodingPreset = IH264_VUICODING_USERDEFINED;
    staticParams->vuiCodingParams.hrdParamsPresentFlag = 0;
    staticParams->vuiCodingParams.timingInfoPresentFlag = 0;
#endif

    /* Uncomment below settings if SEI/meta data needs to be enabled */
    /* staticParams->videnc2Params.metadataType[0] = IH264_SEI_USER_DATA_UNREGISTERED; */

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the parameters required for a processs call
 *
 * \param  algObj          [IN]  EncLink_H264Obj - codec object
 * \param  algCreateParams [IN]  EncLink_AlgCreateParams create parameters
 * \param  algDynamicParams[IN]  EncLink_AlgDynamicParams - dynamic parameters
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_h264_set_algObject(EncLink_H264Obj * algObj,
                                      EncLink_AlgCreateParams * algCreateParams,
                                      EncLink_AlgDynamicParams *
                                      algDynamicParams)
{
    IH264ENC_InArgs *inArgs;
    IH264ENC_OutArgs *outArgs;
    IVIDEO2_BufDesc *inputBufDesc;
    XDM2_BufDesc *outputBufDesc;
    IH264ENC_Status *status;
    Int i;

    inArgs = &algObj->inArgs;
    outArgs = &algObj->outArgs;
    inputBufDesc = &algObj->inBufs;
    outputBufDesc = &algObj->outBufs;
    status = &algObj->status;

     /*-----------------------------------------------------------------------*/
    /* Initialize the input ID in input arguments to the bufferid of the */
    /* buffer element returned from getfreebuffer() function.  */
     /*-----------------------------------------------------------------------*/
    /* inputID need to update before every encode process call */
    inArgs->videnc2InArgs.inputID = 0;
    inArgs->videnc2InArgs.control = IVIDENC2_CTRL_DEFAULT;

    outArgs->control = IH264ENC_CTRL_WRITE_NOREFUPDATE;
    outArgs->numStaticMBs = 0;
    outArgs->vbvBufferLevel = 0;
    outArgs->bytesGeneratedBotField = 1;
    outArgs->videnc2OutArgs.extendedError = 0;
    outArgs->videnc2OutArgs.bytesGenerated = 0;
    outArgs->videnc2OutArgs.encodedFrameType = IVIDEO_I_FRAME;
    outArgs->videnc2OutArgs.inputFrameSkip = 0;
    memset(&outArgs->videnc2OutArgs.freeBufID, 0,
           sizeof(outArgs->videnc2OutArgs.freeBufID));
    outArgs->videnc2OutArgs.reconBufs.planeDesc[0].buf = NULL;
    outArgs->videnc2OutArgs.reconBufs.planeDesc[1].buf = NULL;
    outArgs->videnc2OutArgs.reconBufs.imagePitch[0] = 0;

    /*------------------------------------------------------------------------*/
    /* Initialise output discriptors */
    /*------------------------------------------------------------------------*/
    outputBufDesc->numBufs = 0;
    for (i = 0; i < algObj->status.videnc2Status.bufInfo.minNumOutBufs; i++)
    {

        outputBufDesc->numBufs++;
        outputBufDesc->descs[i].memType = XDM_MEMTYPE_RAW;
        outputBufDesc->descs[i].bufSize.bytes =
            algObj->status.videnc2Status.bufInfo.minOutBufSize[i].bytes;

        if (i == 0)
        {
        /*-------------------------------------------------------------------*/
            /* Set proper buffer addresses for bitstream data */
        /*-------------------------------------------------------------------*/
            outputBufDesc->descs[0].buf = NULL;
        }
        else
        {

            /* Check for required size vs Memory allocated for Analytic info buffer.*/
            UTILS_assert((status->videnc2Status.bufInfo.minOutBufSize[i].bytes <
                        algCreateParams->mvDataSize));

        /*-------------------------------------------------------------------*/
            /* Set proper buffer addresses for MV & SAD data */
        /*-------------------------------------------------------------------*/
            outputBufDesc->descs[i].buf = NULL;
        }
    }

    /*------------------------------------------------------------------------*/
    /* Video buffer layout, field interleaved or field separated */
    /* Only IVIDEO_FIELD_INTERLEAVED and VCODEC_FIELD_SEPARATED are supported
     */
    /*------------------------------------------------------------------------*/
    inputBufDesc->dataLayout = algCreateParams->dataLayout;

    /*------------------------------------------------------------------------*/
    /* Flag to indicate field order in interlaced content */
    /* Supported values are */
    /* 0 - Bottom field first */
    /* 1 - Top filed first */
    /* TODO : need to find defalut parameter */
    /*------------------------------------------------------------------------*/
    inputBufDesc->topFieldFirstFlag = 1;

    /*------------------------------------------------------------------------*/
    /* Initialize the input buffer properties as required by algorithm */
    /* based on info received by preceding GETBUFINFO call.  */
    /*------------------------------------------------------------------------*/
    inputBufDesc->numPlanes = 2;/* status.videnc2Status.bufInfo.minNumInBufs; */
    inputBufDesc->numMetaPlanes = 0;
    /*------------------------------------------------------------------------*/
    /* Set entire Image region in the buffer by using config parameters */
    /*------------------------------------------------------------------------*/
    inputBufDesc->imageRegion.topLeft.x = algDynamicParams->startX;
    inputBufDesc->imageRegion.topLeft.y = algDynamicParams->startY;
    inputBufDesc->imageRegion.bottomRight.x = algDynamicParams->startX +
        algObj->dynamicParams.videnc2DynamicParams.inputWidth;
    inputBufDesc->imageRegion.bottomRight.y = algDynamicParams->startY +
        algObj->dynamicParams.videnc2DynamicParams.inputHeight;
    /*------------------------------------------------------------------------*/
    /* Set proper Image region in the buffer by using config parameters */
    /*------------------------------------------------------------------------*/
    inputBufDesc->activeFrameRegion.topLeft.x = algDynamicParams->startX;
    inputBufDesc->activeFrameRegion.topLeft.y = algDynamicParams->startY;
    inputBufDesc->activeFrameRegion.bottomRight.x = algDynamicParams->startX +
        algObj->dynamicParams.videnc2DynamicParams.inputWidth;
    inputBufDesc->activeFrameRegion.bottomRight.y = algDynamicParams->startY +
        algObj->dynamicParams.videnc2DynamicParams.inputHeight;
    /*------------------------------------------------------------------------*/
    /* Image pitch is capture width */
    /*------------------------------------------------------------------------*/

    inputBufDesc->imagePitch[0] =
            algObj->dynamicParams.videnc2DynamicParams.captureWidth;
    inputBufDesc->imagePitch[1] =
            algObj->dynamicParams.videnc2DynamicParams.captureWidth;
    /*------------------------------------------------------------------------*/
    /* Set Content type and chroma format from encoder parameters */
    /*------------------------------------------------------------------------*/
    inputBufDesc->contentType =
        algObj->staticParams.videnc2Params.inputContentType;
    inputBufDesc->chromaFormat =
        algObj->staticParams.videnc2Params.inputChromaFormat;

    /*------------------------------------------------------------------------*/
    /* Assign memory pointers adn sizes for the all the input buffers */
    /*------------------------------------------------------------------------*/
    for (i = 0; i < algObj->status.videnc2Status.bufInfo.minNumInBufs; i++)
    {
        inputBufDesc->planeDesc[i].buf = NULL;

            inputBufDesc->planeDesc[i].memType = XDM_MEMTYPE_RAW;
            inputBufDesc->planeDesc[i].bufSize.bytes =
                algObj->status.videnc2Status.bufInfo.minInBufSize[i].tileMem.
                width *
                algObj->status.videnc2Status.bufInfo.minInBufSize[i].tileMem.
                height;
    }
    /*------------------------------------------------------------------------*/
    /* Set second field offset width and height according to input data */
    /* When second field of the input data starts at 0 it represents 2 fields
     */
    /* are seperated and provided at 2 diff process calls (60 process call) */
    /*------------------------------------------------------------------------*/
    if ((inputBufDesc->dataLayout == VENC_FIELD_SEPARATED) &&
        (algCreateParams->singleBuf == FALSE) &&
        (algObj->staticParams.videnc2Params.inputContentType ==
         SYSTEM_IVIDEO_INTERLACED))
    {
        inputBufDesc->secondFieldOffsetHeight[0] = 0;
        inputBufDesc->secondFieldOffsetHeight[1] = 0;
        inputBufDesc->secondFieldOffsetHeight[2] = 0;
    }
    else
    {
        inputBufDesc->secondFieldOffsetHeight[0] =
            algObj->dynamicParams.videnc2DynamicParams.inputHeight;
        inputBufDesc->secondFieldOffsetHeight[1] =
            (algObj->dynamicParams.videnc2DynamicParams.inputHeight >> 1);
        inputBufDesc->secondFieldOffsetHeight[2] =
            (algObj->dynamicParams.videnc2DynamicParams.inputHeight >> 1);
    }
    inputBufDesc->secondFieldOffsetWidth[0] = 0;
    inputBufDesc->secondFieldOffsetWidth[1] = 0;
    inputBufDesc->secondFieldOffsetWidth[2] = 0;

    /*------------------------------------------------------------------------*/
    /* Set The address of unregistered user data in meta data plane desc */
    /*------------------------------------------------------------------------*/
    inputBufDesc->numMetaPlanes = 0;
    /*------------------------------------------------------------------------*/
    /* Provide approprate buffer addresses for both the supported meta data: */
    /* A. USer defined SEI message */
    /* B. User Defined Scaling MAtrices */
    /*------------------------------------------------------------------------*/
    if (algObj->staticParams.videnc2Params.
        metadataType[inputBufDesc->numMetaPlanes] ==
        IH264_SEI_USER_DATA_UNREGISTERED)
    {
        inputBufDesc->metadataPlaneDesc[inputBufDesc->numMetaPlanes].buf = NULL;
        inputBufDesc->metadataPlaneDesc[inputBufDesc->numMetaPlanes].bufSize.
            bytes = -1;
        inputBufDesc->numMetaPlanes++;
    }
    /*------------------------------------------------------------------------*/
    /* Set proper buffer addresses for user defined scaling matrix */
    /*------------------------------------------------------------------------*/
    if (algObj->staticParams.videnc2Params.
        metadataType[inputBufDesc->numMetaPlanes] ==
        IH264_USER_DEFINED_SCALINGMATRIX)
    {
        inputBufDesc->metadataPlaneDesc[inputBufDesc->numMetaPlanes].buf = NULL;
        inputBufDesc->metadataPlaneDesc[inputBufDesc->numMetaPlanes].bufSize.
            bytes =
            /* -1; */
            896;
        inputBufDesc->numMetaPlanes++;
    }

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Function to get a dummy buffer during codec get buff call back
 *
 * \param  dataSyncHandle [IN] XDM_DataSyncHandle
 * \param  dataSyncDesc   [IN] XDM_DataSyncDesc
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static XDAS_Int32 enclink_h264_dummy_get_buffer_fxn(XDM_DataSyncHandle dataSyncHandle,
                                                    XDM_DataSyncDesc *dataSyncDesc)
{
    Vps_printf("%d:ENCLINK:H264Enc !!WARNING!!!Unable to handle runtime output buffer request");
    return -1;
}

/**
 *******************************************************************************
 *
 * \brief This function to set/populate H264 Encoder dynamic parameters
 *
 * \param  params   [IN] IH264VENC_DynamicParams - H264 dynamic parameters
 * \param  status   [IN] EncLink_AlgDynamicParams - Enc Link dynamic parameters
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_h264_set_dynamic_params(IH264ENC_DynamicParams *
                                           dynamicParams,
                                           EncLink_AlgDynamicParams *
                                           algDynamicParams)
{
    *dynamicParams = H264ENC_TI_DYNAMICPARAMS;

    dynamicParams->videnc2DynamicParams.inputWidth =
        algDynamicParams->inputWidth;
    dynamicParams->videnc2DynamicParams.inputHeight =
        algDynamicParams->inputHeight;
    dynamicParams->videnc2DynamicParams.captureWidth =
        algDynamicParams->inputPitch;
    dynamicParams->videnc2DynamicParams.targetBitRate =
        algDynamicParams->targetBitRate;
    dynamicParams->videnc2DynamicParams.targetFrameRate =
        algDynamicParams->targetFrameRate;
    dynamicParams->videnc2DynamicParams.interFrameInterval =
        algDynamicParams->interFrameInterval;
    dynamicParams->videnc2DynamicParams.intraFrameInterval =
        algDynamicParams->intraFrameInterval;
    dynamicParams->videnc2DynamicParams.mvAccuracy =
        algDynamicParams->mvAccuracy;
    dynamicParams->rateControlParams.VBRDuration =
        algDynamicParams->vbrDuration;
    dynamicParams->rateControlParams.VBRsensitivity =
        algDynamicParams->vbrSensitivity;
    dynamicParams->videnc2DynamicParams.refFrameRate =
        algDynamicParams->refFrameRate;
    dynamicParams->videnc2DynamicParams.ignoreOutbufSizeFlag = XDAS_TRUE;
    dynamicParams->videnc2DynamicParams.getBufferFxn =
                                       enclink_h264_dummy_get_buffer_fxn;

    dynamicParams->rateControlParams.rateControlParamsPreset
        = IH264_RATECONTROLPARAMS_USERDEFINED;
    dynamicParams->rateControlParams.scalingMatrixPreset
        = IH264_SCALINGMATRIX_NONE;
    dynamicParams->rateControlParams.qpMinI = algDynamicParams->qpMinI;
    dynamicParams->rateControlParams.qpMaxI = algDynamicParams->qpMaxI;
    dynamicParams->rateControlParams.qpI    = algDynamicParams->qpInitI;
    dynamicParams->rateControlParams.qpMinP = algDynamicParams->qpMinP;
    dynamicParams->rateControlParams.qpMaxP = algDynamicParams->qpMaxP;
    dynamicParams->rateControlParams.qpP    = algDynamicParams->qpInitP;
    dynamicParams->rateControlParams.rcAlgo = algDynamicParams->rcAlg;

    dynamicParams->rateControlParams.discardSavedBits = 1;

    if(dynamicParams->rateControlParams.rcAlgo == IH264_RATECONTROL_PRC)
    {
        dynamicParams->rateControlParams.HRDBufferSize
            = 2 * algDynamicParams->targetBitRate;
    }
    else
    {
        dynamicParams->rateControlParams.HRDBufferSize
            = algDynamicParams->targetBitRate;
    }

    dynamicParams->
	  rateControlParams.removeExpensiveCoeff = FALSE;
    dynamicParams->
	  rateControlParams.HRDBufferSize = 2500000;

    dynamicParams->rateControlParams.initialBufferLevel
        = dynamicParams->rateControlParams.HRDBufferSize;

    dynamicParams->rateControlParams.frameSkipThMulQ5 = 0;
    dynamicParams->rateControlParams.vbvUseLevelThQ5 = 0;

    dynamicParams->rateControlParams.maxPicSizeRatioI = 640;
    /* override with App seeting, set to 1 for IDR or I-frame only mode */
    dynamicParams->rateControlParams.maxPicSizeRatioI =
        algDynamicParams->maxPicSizeRatioI;

    dynamicParams->rateControlParams.skipDistributionWindowLength = 5;
    dynamicParams->rateControlParams.numSkipInDistributionWindow = 2;

    return 0;
}

#define ENCLINKH264_ALGREATE_RSRC_NONE                                       (0)
#define ENCLINKH264_ALGREATE_RSRC_ALGCREATED                           (1 <<  0)
#define ENCLINKH264_ALGREATE_RSRC_IRES_ASSIGNED                        (1 <<  1)
#define ENCLINKH264_ALGREATE_RSRC_ALL (                                        \
                                       ENCLINKH264_ALGREATE_RSRC_ALGCREATED |  \
                                       ENCLINKH264_ALGREATE_RSRC_IRES_ASSIGNED \
                                      )

/**
 *******************************************************************************
 *
 * \brief This function free-up the resouces allocated by the codec instance
 *
 * \param  hObj     [IN]  EncLink_H264Obj - codec object
 * \param  rsrcMask [IN]  resources mask
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void enclink_h264_freersrc(EncLink_H264Obj * hObj, Int rsrcMask)
{
    if (rsrcMask & ENCLINKH264_ALGREATE_RSRC_IRES_ASSIGNED)
    {
        IRES_Status iresStatus;

        IRESMAN_TiledMemoryForceDisableTileAlloc_UnRegister((IALG_Handle) hObj->algHandle);
        iresStatus =
            RMAN_freeResources((IALG_Handle) hObj->algHandle,
                               &H264ENC_TI_IRES, hObj->scratchID);
        if (iresStatus != IRES_OK)
        {
            Vps_printf(" ENCODE: ERROR: RMAN_freeResources FAILED (status=0x%08x) !!!\n",
                         iresStatus);
        }
    }
    if (rsrcMask & ENCLINKH264_ALGREATE_RSRC_ALGCREATED)
    {
        enc_link_h264_delete(hObj->algHandle);
        hObj->algHandle = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief This function to print the dynamic parameters
 *
 * \param  videnc2DynamicParams[IN] - IVIDENC2_DynamicParams - dynamic param
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_print_dynamic_params(IVIDENC2_DynamicParams *videnc2DynamicParams)
{
    Vps_printf("videnc2DynamicParams -> inputHeight             : %d\n", videnc2DynamicParams->inputHeight);
    Vps_printf("videnc2DynamicParams -> inputWidth              : %d\n", videnc2DynamicParams->inputWidth);
    Vps_printf("videnc2DynamicParams -> refFrameRate            : %d\n", videnc2DynamicParams->refFrameRate);
    Vps_printf("videnc2DynamicParams -> targetFrameRate         : %d\n", videnc2DynamicParams->targetFrameRate);
    Vps_printf("videnc2DynamicParams -> targetBitRate           : %d\n", videnc2DynamicParams->targetBitRate);
    Vps_printf("videnc2DynamicParams -> intraFrameInterval      : %d\n", videnc2DynamicParams->intraFrameInterval);
    Vps_printf("videnc2DynamicParams -> generateHeader          : %d\n", videnc2DynamicParams->generateHeader);
    Vps_printf("videnc2DynamicParams -> captureWidth            : %d\n", videnc2DynamicParams->captureWidth);
    Vps_printf("videnc2DynamicParams -> forceFrame              : %d\n", videnc2DynamicParams->forceFrame);
    Vps_printf("videnc2DynamicParams -> interFrameInterval      : %d\n", videnc2DynamicParams->interFrameInterval);
    Vps_printf("videnc2DynamicParams -> mvAccuracy              : %d\n", videnc2DynamicParams->mvAccuracy);
    Vps_printf("videnc2DynamicParams -> sampleAspectRatioHeight : %d\n", videnc2DynamicParams->sampleAspectRatioHeight);
    Vps_printf("videnc2DynamicParams -> sampleAspectRatioWidth  : %d\n", videnc2DynamicParams->sampleAspectRatioWidth);
    Vps_printf("videnc2DynamicParams -> ignoreOutbufSizeFlag    : %d\n", videnc2DynamicParams->ignoreOutbufSizeFlag);
    Vps_printf("videnc2DynamicParams -> lateAcquireArg          : %d\n", videnc2DynamicParams->lateAcquireArg);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function to print the dynamic parameters
 *
 * \param  dynamicParams[IN] - IH264ENC_DynamicParams - dynamic param
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_h264_print_dynamic_params(UInt32 chId, IH264ENC_DynamicParams *
                                           dynamicParams)
{
    Vps_printf(" \n");
    Vps_printf("--------- CH %d : H264 ENC : Dynamic Params -------\n", chId);
    Vps_printf(" \n");
    enclink_print_dynamic_params(&dynamicParams->videnc2DynamicParams);
    Vps_printf(" \n");
    Vps_printf("rateControlParams -> rateControlParamsPreset        : %d\n", dynamicParams->rateControlParams.rateControlParamsPreset);
    Vps_printf("rateControlParams -> scalingMatrixPreset            : %d\n", dynamicParams->rateControlParams.scalingMatrixPreset);
    Vps_printf("rateControlParams -> rcAlgo                         : %d\n", dynamicParams->rateControlParams.rcAlgo);
    Vps_printf("rateControlParams -> qpI                            : %d\n", dynamicParams->rateControlParams.qpI);
    Vps_printf("rateControlParams -> qpMaxI                         : %d\n", dynamicParams->rateControlParams.qpMaxI);
    Vps_printf("rateControlParams -> qpMinI                         : %d\n", dynamicParams->rateControlParams.qpMinI);
    Vps_printf("rateControlParams -> qpP                            : %d\n", dynamicParams->rateControlParams.qpP);
    Vps_printf("rateControlParams -> qpMaxP                         : %d\n", dynamicParams->rateControlParams.qpMaxP);
    Vps_printf("rateControlParams -> qpMinP                         : %d\n", dynamicParams->rateControlParams.qpMinP);
    Vps_printf("rateControlParams -> qpOffsetB                      : %d\n", dynamicParams->rateControlParams.qpOffsetB);
    Vps_printf("rateControlParams -> qpMaxB                         : %d\n", dynamicParams->rateControlParams.qpMaxB);
    Vps_printf("rateControlParams -> qpMinB                         : %d\n", dynamicParams->rateControlParams.qpMinB);
    Vps_printf("rateControlParams -> allowFrameSkip                 : %d\n", dynamicParams->rateControlParams.allowFrameSkip);
    Vps_printf("rateControlParams -> removeExpensiveCoeff           : %d\n", dynamicParams->rateControlParams.removeExpensiveCoeff);
    Vps_printf("rateControlParams -> chromaQPIndexOffset            : %d\n", dynamicParams->rateControlParams.chromaQPIndexOffset);
    Vps_printf("rateControlParams -> IPQualityFactor                : %d\n", dynamicParams->rateControlParams.IPQualityFactor);
    Vps_printf("rateControlParams -> initialBufferLevel             : %d\n", dynamicParams->rateControlParams.initialBufferLevel);
    Vps_printf("rateControlParams -> HRDBufferSize                  : %d\n", dynamicParams->rateControlParams.HRDBufferSize);
    Vps_printf("rateControlParams -> minPicSizeRatioI               : %d\n", dynamicParams->rateControlParams.minPicSizeRatioI);
    Vps_printf("rateControlParams -> maxPicSizeRatioI               : %d\n", dynamicParams->rateControlParams.maxPicSizeRatioI);
    Vps_printf("rateControlParams -> minPicSizeRatioP               : %d\n", dynamicParams->rateControlParams.minPicSizeRatioP);
    Vps_printf("rateControlParams -> maxPicSizeRatioP               : %d\n", dynamicParams->rateControlParams.maxPicSizeRatioP);
    Vps_printf("rateControlParams -> minPicSizeRatioB               : %d\n", dynamicParams->rateControlParams.minPicSizeRatioB);
    Vps_printf("rateControlParams -> maxPicSizeRatioB               : %d\n", dynamicParams->rateControlParams.maxPicSizeRatioB);
    Vps_printf("rateControlParams -> enablePRC                      : %d\n", dynamicParams->rateControlParams.enablePRC);
    Vps_printf("rateControlParams -> enablePartialFrameSkip         : %d\n", dynamicParams->rateControlParams.enablePartialFrameSkip);
    Vps_printf("rateControlParams -> discardSavedBits               : %d\n", dynamicParams->rateControlParams.discardSavedBits);
    Vps_printf("rateControlParams -> VBRDuration                    : %d\n", dynamicParams->rateControlParams.VBRDuration);
    Vps_printf("rateControlParams -> VBRsensitivity                 : %d\n", dynamicParams->rateControlParams.VBRsensitivity);
    Vps_printf("rateControlParams -> skipDistributionWindowLength   : %d\n", dynamicParams->rateControlParams.skipDistributionWindowLength);
    Vps_printf("rateControlParams -> numSkipInDistributionWindow    : %d\n", dynamicParams->rateControlParams.numSkipInDistributionWindow);
    Vps_printf("rateControlParams -> enableHRDComplianceMode        : %d\n", dynamicParams->rateControlParams.enableHRDComplianceMode);
    Vps_printf("rateControlParams -> frameSkipThMulQ5               : %d\n", dynamicParams->rateControlParams.frameSkipThMulQ5);
    Vps_printf("rateControlParams -> vbvUseLevelThQ5                : %d\n", dynamicParams->rateControlParams.vbvUseLevelThQ5);
    Vps_printf(" \n");
    Vps_printf("interCodingParams -> interCodingPreset  : %d\n", dynamicParams->interCodingParams.interCodingPreset);
    Vps_printf("interCodingParams -> searchRangeHorP    : %d\n", dynamicParams->interCodingParams.searchRangeHorP);
    Vps_printf("interCodingParams -> searchRangeVerP    : %d\n", dynamicParams->interCodingParams.searchRangeVerP);
    Vps_printf("interCodingParams -> searchRangeHorB    : %d\n", dynamicParams->interCodingParams.searchRangeHorB);
    Vps_printf("interCodingParams -> searchRangeVerB    : %d\n", dynamicParams->interCodingParams.searchRangeVerB);
    Vps_printf("interCodingParams -> interCodingBias    : %d\n", dynamicParams->interCodingParams.interCodingBias);
    Vps_printf("interCodingParams -> skipMVCodingBias   : %d\n", dynamicParams->interCodingParams.skipMVCodingBias);
    Vps_printf("interCodingParams -> minBlockSizeP      : %d\n", dynamicParams->interCodingParams.minBlockSizeP);
    Vps_printf("interCodingParams -> minBlockSizeB      : %d\n", dynamicParams->interCodingParams.minBlockSizeB);
    Vps_printf("interCodingParams -> meAlgoMode         : %d\n", dynamicParams->interCodingParams.meAlgoMode);
    Vps_printf(" \n");
    Vps_printf("intraCodingParams -> intraCodingPreset          : %d\n", dynamicParams->intraCodingParams.intraCodingPreset);
    Vps_printf("intraCodingParams -> lumaIntra4x4Enable         : %d\n", dynamicParams->intraCodingParams.lumaIntra4x4Enable);
    Vps_printf("intraCodingParams -> lumaIntra8x8Enable         : %d\n", dynamicParams->intraCodingParams.lumaIntra8x8Enable);
    Vps_printf("intraCodingParams -> lumaIntra16x16Enable       : %d\n", dynamicParams->intraCodingParams.lumaIntra16x16Enable);
    Vps_printf("intraCodingParams -> chromaIntra8x8Enable       : %d\n", dynamicParams->intraCodingParams.chromaIntra8x8Enable);
    Vps_printf("intraCodingParams -> chromaComponentEnable      : %d\n", dynamicParams->intraCodingParams.chromaComponentEnable);
    Vps_printf("intraCodingParams -> intraRefreshMethod         : %d\n", dynamicParams->intraCodingParams.intraRefreshMethod);
    Vps_printf("intraCodingParams -> intraRefreshRate           : %d\n", dynamicParams->intraCodingParams.intraRefreshRate);
    Vps_printf("intraCodingParams -> gdrOverlapRowsBtwFrames    : %d\n", dynamicParams->intraCodingParams.gdrOverlapRowsBtwFrames);
    Vps_printf("intraCodingParams -> constrainedIntraPredEnable : %d\n", dynamicParams->intraCodingParams.constrainedIntraPredEnable);
    Vps_printf("intraCodingParams -> intraCodingBias            : %d\n", dynamicParams->intraCodingParams.intraCodingBias);
    Vps_printf(" \n");
    Vps_printf("sliceCodingParams -> sliceCodingPreset  : %d\n", dynamicParams->sliceCodingParams.sliceCodingPreset);
    Vps_printf("sliceCodingParams -> sliceMode          : %d\n", dynamicParams->sliceCodingParams.sliceMode);
    Vps_printf("sliceCodingParams -> sliceUnitSize      : %d\n", dynamicParams->sliceCodingParams.sliceUnitSize);
    Vps_printf("sliceCodingParams -> sliceStartOffset   : [%d %d %d]\n",
            dynamicParams->sliceCodingParams.sliceStartOffset[0],
            dynamicParams->sliceCodingParams.sliceStartOffset[1],
            dynamicParams->sliceCodingParams.sliceStartOffset[2]
        );
    Vps_printf("sliceCodingParams -> streamFormat       : %d\n", dynamicParams->sliceCodingParams.streamFormat);
    Vps_printf(" \n");
    Vps_printf("sliceGroupChangeCycle           : %d\n", dynamicParams->sliceGroupChangeCycle);
    Vps_printf("searchCenter                    : %d\n", dynamicParams->searchCenter);
    Vps_printf("enableStaticMBCount             : %d\n", dynamicParams->enableStaticMBCount);
    Vps_printf("enableROI                       : %d\n", dynamicParams->enableROI);
    Vps_printf(" \n");
    Vps_printf(" \n");

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function do the necessary settings and create the
 *        H264 codec instance
 *
 *          DES_ID: DOX_DES_TAG(DES_VideoEncoder_003)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1454)
 *
 * \param  hObj             [IN] EncLink_H264Obj - codec object
 * \param  algCreateParams  [IN] EncLink_AlgCreateParams - create parameters
 * \param  algDynamicParams [IN] EncLink_AlgDynamicParams - dynamic parameters
 * \param  linkID           [IN] Link ID
 * \param  channelID        [IN] Channel ID
 * \param  scratchGroupID   [IN] Scratch group ID
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int EncLinkH264_algCreate(EncLink_H264Obj * hObj,
                          EncLink_AlgCreateParams * algCreateParams,
                          EncLink_AlgDynamicParams * algDynamicParams,
                          Int linkID, Int channelID, Int scratchGroupID)
{
    Int retVal = ENC_LINK_S_SUCCESS;
    Int rsrcMask = ENCLINKH264_ALGREATE_RSRC_NONE;
    Int algStatus;

    UTILS_assert(Utils_encdecIsH264(algCreateParams->format) == TRUE);
    hObj->format = (IVIDEO_Format)algCreateParams->format;
    hObj->linkID = linkID;
    hObj->channelID = channelID;
    hObj->scratchID = scratchGroupID;

    memset(&hObj->inArgs, 0, sizeof(hObj->inArgs));
    memset(&hObj->outArgs, 0, sizeof(hObj->outArgs));
    memset(&hObj->inBufs, 0, sizeof(hObj->inBufs));
    memset(&hObj->outBufs, 0, sizeof(hObj->outBufs));
    memset(&hObj->status, 0, sizeof(hObj->status));
    memset(&hObj->memUsed, 0, sizeof(hObj->memUsed));

    hObj->status.videnc2Status.size = sizeof(IH264ENC_Status);
    hObj->inArgs.videnc2InArgs.size = sizeof(IH264ENC_InArgs);
    hObj->outArgs.videnc2OutArgs.size = sizeof(IH264ENC_OutArgs);
    hObj->staticParams.videnc2Params.size = sizeof(IH264ENC_Params);
    hObj->dynamicParams.videnc2DynamicParams.size =
        sizeof(IH264ENC_DynamicParams);

    enclink_h264_set_static_params(&hObj->staticParams, algCreateParams);
    enclink_h264_set_dynamic_params(&hObj->dynamicParams, algDynamicParams);

    if(hObj->staticParams.rateControlParams.rcAlgo == IH264_RATECONTROL_PRC)
    {
        /* [IH264_RATECONTROL_PRC] Variable Bitrate*/
        hObj->staticParams.rateControlParams.HRDBufferSize
            = 2 * hObj->dynamicParams.videnc2DynamicParams.targetBitRate;
        hObj->staticParams.rateControlParams.initialBufferLevel
            =     hObj->staticParams.rateControlParams.HRDBufferSize;
    }
    else if(hObj->staticParams.rateControlParams.rcAlgo == IH264_RATECONTROL_PRC_LOW_DELAY)
    {
        hObj->staticParams.rateControlParams.HRDBufferSize
            = hObj->dynamicParams.videnc2DynamicParams.targetBitRate;
        hObj->staticParams.rateControlParams.initialBufferLevel
            = hObj->staticParams.rateControlParams.HRDBufferSize;
    }

    UTILS_MEMLOG_USED_START();
    hObj->algHandle =
        enc_link_h264_create((IH264ENC_Fxns *) & H264ENC_TI_IH264ENC,
                             &hObj->staticParams);
    UTILS_assertError((NULL != hObj->algHandle),
                      retVal, ENC_LINK_E_ALGCREATEFAILED, linkID, channelID);
    if (!UTILS_ISERROR(retVal))
    {
        IRES_Status iresStatus;

        rsrcMask |= ENCLINKH264_ALGREATE_RSRC_ALGCREATED;
        IRESMAN_TiledMemoryForceDisableTileAlloc_Register((IALG_Handle) hObj->algHandle);
        iresStatus = RMAN_assignResources((IALG_Handle) hObj->algHandle,
                                          &H264ENC_TI_IRES, scratchGroupID);
        UTILS_assertError((iresStatus == IRES_OK), retVal,
                          ENC_LINK_E_RMANRSRCASSIGNFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {

        rsrcMask |= ENCLINKH264_ALGREATE_RSRC_IRES_ASSIGNED;

        hObj->status.videnc2Status.data.buf = &(hObj->versionInfo[0]);
        hObj->status.videnc2Status.data.bufSize = sizeof(hObj->versionInfo);
        algStatus = enclink_h264_control(hObj->algHandle, XDM_GETVERSION,
                                         &(hObj->dynamicParams),
                                         &(hObj->status));
        if (algStatus == XDM_EOK)
        {
            Vps_printf( " ENCODE: CH%d: %s:%s\n", hObj->channelID,
                                  "H264EncCreated", hObj->versionInfo);
        }
        algStatus = enclink_h264_control(hObj->algHandle,
                                         XDM_SETDEFAULT,
                                         &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          ENC_LINK_E_ALGSETPARAMSFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {
        algStatus = enclink_h264_control(hObj->algHandle,
                                         XDM_SETPARAMS,
                                         &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          ENC_LINK_E_ALGSETPARAMSFAILED, linkID, channelID);
    }

    if (!UTILS_ISERROR(retVal))
    {
        enclink_h264_control(hObj->algHandle,
                             XDM_GETSTATUS,
                             &hObj->dynamicParams, &hObj->status);
    }
    if (!UTILS_ISERROR(retVal))
    {
        algStatus =
            enclink_h264_control(hObj->algHandle,
                                 XDM_GETBUFINFO,
                                 &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          ENC_LINK_E_ALGGETBUFINFOFAILED, linkID, channelID);
    }
    if (UTILS_ISERROR(retVal))
    {
        enclink_h264_freersrc(hObj, rsrcMask);
    }
    else
    {
        /* Initialize the Inarg, OutArg, InBuf & OutBuf objects */
        enclink_h264_set_algObject(hObj, algCreateParams, algDynamicParams);
    }

    UTILS_MEMLOG_USED_END(hObj->memUsed);
    UTILS_MEMLOG_PRINT("ENCLINK_H264",
                       hObj->memUsed,
                       (sizeof(hObj->memUsed) / sizeof(hObj->memUsed[0])));

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance and free-up the resources
 *
 * \param   hObj   [IN]  EncLink_H264Obj - H264 codec object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void EncLinkH264_algDelete(EncLink_H264Obj * hObj)
{
    UTILS_MEMLOG_FREE_START();
    if (hObj->algHandle)
    {
        enclink_h264_freersrc(hObj, ENCLINKH264_ALGREATE_RSRC_ALL);
    }

    if (hObj->algHandle)
    {
        enc_link_h264_delete(hObj->algHandle);
    }
    UTILS_MEMLOG_FREE_END(hObj->memUsed, 0 /* dont care */ );
}

/**
 *******************************************************************************
 *
 * \brief This function set/update various the codec dynamic parameters
 *
 * \param   hObj   [IN]  EncLink_algObj - H264 codec object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int32 EncLinkH264_algSetConfig(EncLink_algObj * algObj)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    UInt32 bitMask;
    Bool setConfigFlag = FALSE;
    UInt key;

    key = Hwi_disable();
    bitMask = algObj->setConfigBitMask;

    /* Set the modified encoder bitRate value */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_BITRATE) & 0x1)
    {

        algObj->u.h264AlgIfObj.dynamicParams.videnc2DynamicParams.
                targetBitRate = algObj->algDynamicParams.targetBitRate;
/*        Vps_printf("\n ENCLINK: new targetbitrate to set:%d \n",
                algObj->algDynamicParams.targetBitRate);*/
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_BITRATE));
        EncLink_h264EncoderReset(&algObj->u.h264AlgIfObj);
        setConfigFlag = TRUE;
    }

    /* Set the modified encoder Fps value */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_FPS) & 0x1)
    {
        algObj->u.h264AlgIfObj.dynamicParams.videnc2DynamicParams.
                targetFrameRate = algObj->algDynamicParams.targetFrameRate;
        algObj->u.h264AlgIfObj.dynamicParams.videnc2DynamicParams.
                targetBitRate = algObj->algDynamicParams.targetBitRate;
/*        Vps_printf("\n ENCLINK: new targetbitrate to set:%d \n",
                algObj->algDynamicParams.targetBitRate);
        Vps_printf("\n ENCLINK: new targetframerate to set:%d \n",
                algObj->algDynamicParams.targetFrameRate);*/
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_FPS));
        EncLink_h264EncoderReset(&algObj->u.h264AlgIfObj);
        setConfigFlag = TRUE;
    }

    /* Set the modified encoder Intra Frame Interval(GOP) value */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_INTRAI) & 0x1)
    {
        algObj->u.h264AlgIfObj.dynamicParams.videnc2DynamicParams.
                intraFrameInterval = algObj->algDynamicParams.intraFrameInterval;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf("\n ENCLINK: new intraFrameInterval to set:%d \n",
                algObj->algDynamicParams.intraFrameInterval);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_INTRAI));
        setConfigFlag = TRUE;
    }

    /* toggle Force IDR */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_FORCEI) & 0x1)
    {

        algObj->algDynamicParams.forceFrame = TRUE;
        algObj->algDynamicParams.forceFrameStatus = FALSE;

        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_FORCEI));
        setConfigFlag = TRUE;
    }
    /** to support Force IDR frame: Entry **/
    if ((algObj->algDynamicParams.forceFrame == TRUE) &&
        (algObj->algDynamicParams.forceFrameStatus == FALSE))
    {
        /** SET forceIDR **/
        algObj->u.h264AlgIfObj.dynamicParams.videnc2DynamicParams.forceFrame =
                IVIDEO_IDR_FRAME;
        algObj->algDynamicParams.forceFrameStatus = TRUE;
    }
    else if((algObj->algDynamicParams.forceFrame == TRUE) &&
            (algObj->algDynamicParams.forceFrameStatus == TRUE))
    {
        /** UNSET forceIDR **/
        algObj->u.h264AlgIfObj.dynamicParams.videnc2DynamicParams.forceFrame =
                IVIDEO_NA_FRAME;
        algObj->algDynamicParams.forceFrame = FALSE;

        setConfigFlag = TRUE;
    }
    /** to support Force IDR frame: Exit **/

    /* Set the modified encoder RC Alg values*/
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_RCALGO) & 0x1)
    {
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.rateControlParamsPreset
            = IH264_RATECONTROLPARAMS_USERDEFINED;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.rcAlgo
            = algObj->algDynamicParams.rcAlg;

        if(algObj->algDynamicParams.rcAlg == IH264_RATECONTROL_PRC)
        {
            algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.HRDBufferSize
                = 2 * algObj->algDynamicParams.targetBitRate;
            algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.initialBufferLevel
                = algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.HRDBufferSize;
        }
        else if(algObj->algDynamicParams.rcAlg == IH264_RATECONTROL_PRC_LOW_DELAY)
        {
            algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.HRDBufferSize
                = algObj->algDynamicParams.targetBitRate;
            algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.initialBufferLevel
                = algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.HRDBufferSize;
        }

        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf("\n ENCLINK: new RcAlg Param to set:%d\n",
                algObj->algDynamicParams.rcAlg);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_RCALGO));
        setConfigFlag = TRUE;
    }

    /* Set the modified encoder QP range values for Intra Frame */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_QPI) & 0x1)
    {
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.rateControlParamsPreset = IH264_RATECONTROLPARAMS_USERDEFINED;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMinI   = algObj->algDynamicParams.qpMinI;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMaxI   = algObj->algDynamicParams.qpMaxI;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpI      = algObj->algDynamicParams.qpInitI;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf("\n ENCLINK: new QP I Param to set:%d %d %d\n",
                algObj->algDynamicParams.qpMinI, algObj->algDynamicParams.qpMaxI, algObj->algDynamicParams.qpInitI);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_QPI));
        setConfigFlag = TRUE;
    }

    /* Set the modified encoder QP range values for Inter Frame */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_QPP) & 0x1)
    {
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.rateControlParamsPreset = IH264_RATECONTROLPARAMS_USERDEFINED;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMinP   = algObj->algDynamicParams.qpMinP;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMaxP   = algObj->algDynamicParams.qpMaxP;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpP      = algObj->algDynamicParams.qpInitP;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf("\n ENCLINK: new QP P Param to set:%d %d %d\n",
                algObj->algDynamicParams.qpMinP, algObj->algDynamicParams.qpMaxP, algObj->algDynamicParams.qpInitP);
        #endif

        /* This is a workaround for the codec bug of SDOCM00087325*/
        {
            algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpOffsetB = 0;
            algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMaxB = algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMaxP;
            algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMinB = algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.qpMaxB;
        }

        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_QPP));
        setConfigFlag = TRUE;
    }
    /* Set the modified encoder VBRDuration value for CVBR */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_VBRD) & 0x1)
    {
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.rateControlParamsPreset = IH264_RATECONTROLPARAMS_USERDEFINED;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.VBRDuration = algObj->algDynamicParams.vbrDuration;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf("\n ENCLINK: new VBR Duration Param to set:%d\n",
                   algObj->algDynamicParams.vbrDuration);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_VBRD));
        setConfigFlag = TRUE;
    }
    /* Set the modified encoder VBRsensitivity value for CVBR */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_VBRS) & 0x1)
    {
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.rateControlParamsPreset = IH264_RATECONTROLPARAMS_USERDEFINED;
        algObj->u.h264AlgIfObj.dynamicParams.rateControlParams.VBRsensitivity = algObj->algDynamicParams.vbrSensitivity;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf("\n ENCLINK: new VBR Sensitivity Param to set:%d\n",
                   algObj->algDynamicParams.vbrSensitivity);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_VBRS));
        setConfigFlag = TRUE;
    }

    /* Set the toggle for privacy mask ROI setting */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_ROI) & 0x1)
    {
        int i = 0;
        algObj->u.h264AlgIfObj.dynamicParams.enableROI =
            algObj->algDynamicParams.roiParams.roiNumOfRegion;
        IH264ENC_InArgs *inArgs = &algObj->u.h264AlgIfObj.inArgs;

        inArgs->roiInputParams.numOfROI =
            algObj->u.h264AlgIfObj.dynamicParams.enableROI;

        for (i = 0; i < inArgs->roiInputParams.numOfROI; i++)
        {
            inArgs->roiInputParams.listROI[i].topLeft.x =
                algObj->algDynamicParams.roiParams.roiStartX[i];
            inArgs->roiInputParams.listROI[i].topLeft.y =
                algObj->algDynamicParams.roiParams.roiStartY[i];
            inArgs->roiInputParams.listROI[i].bottomRight.x =
                algObj->algDynamicParams.roiParams.roiStartX[i] +
                algObj->algDynamicParams.roiParams.roiWidth[i];
            inArgs->roiInputParams.listROI[i].bottomRight.y =
                algObj->algDynamicParams.roiParams.roiStartY[i] +
                algObj->algDynamicParams.roiParams.roiHeight[i];
            inArgs->roiInputParams.roiType[i] = algObj->algDynamicParams.roiParams.roiType[i];
            inArgs->roiInputParams.roiPriority[i] = algObj->algDynamicParams.roiParams.roiPriority[i];
        }

        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_ROI));
        setConfigFlag = TRUE;
    }

    Hwi_restore(key);

    if (setConfigFlag)
    {
        status = enclink_h264_control(algObj->u.h264AlgIfObj.algHandle,
                                         XDM_SETPARAMS,
                                         &algObj->u.h264AlgIfObj.dynamicParams,
                                         &algObj->u.h264AlgIfObj.status);
        if (UTILS_ISERROR(status))
        {
            Vps_printf(" ENCLINK: ERROR in Run time parameters changes, "
                        "Extended Error code: %d \n",
                        algObj->u.h264AlgIfObj.status.videnc2Status.extendedError);
        }
        else
        {
            #ifdef SYSTEM_VERBOSE_PRINTS
            Vps_printf(" ENCLINK: Run time parameters changed %d\n",
                       algObj->u.h264AlgIfObj.status.videnc2Status.
                       extendedError);
            #endif
        }
     }

    return (status);
}

/**
 *******************************************************************************
 *
 * \brief This function get/return the current codec dynamic parameters
 *
 * \param   hObj   [IN]  EncLink_algObj - H264 codec object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int32 EncLinkH264_algGetConfig(EncLink_algObj * algObj)
{
    Int retVal = ENC_LINK_S_SUCCESS, chId;
    IH264ENC_DynamicParams dynamicParams;
    IH264ENC_Status status;

    if(algObj->getConfigFlag == TRUE)
    {
        status.videnc2Status.size = sizeof(IH264ENC_Status);
        dynamicParams.videnc2DynamicParams.size = sizeof(IH264ENC_DynamicParams);

        retVal = enclink_h264_control(algObj->u.h264AlgIfObj.algHandle,
                                         XDM_GETSTATUS,
                                         &dynamicParams,
                                         &status);
        if (UTILS_ISERROR(retVal))
        {
            Vps_printf(" ENCLINK: ERROR in Run time parameters changes, "
                        "Extended Error code: %d \n",
                        status.videnc2Status.extendedError);
        }

        chId = algObj->u.h264AlgIfObj.channelID;

        enclink_h264_print_dynamic_params(chId, (IH264ENC_DynamicParams*)&status.videnc2Status.encDynamicParams);

        algObj->getConfigFlag = FALSE;

        algObj->algDynamicParams.inputWidth =
              status.videnc2Status.encDynamicParams.inputWidth;
        algObj->algDynamicParams.inputHeight =
              status.videnc2Status.encDynamicParams.inputHeight;
        algObj->algDynamicParams.targetBitRate =
              status.videnc2Status.encDynamicParams.targetBitRate;
        algObj->algDynamicParams.targetFrameRate =
              status.videnc2Status.encDynamicParams.targetFrameRate;
        algObj->algDynamicParams.intraFrameInterval =
              status.videnc2Status.encDynamicParams.intraFrameInterval;
        algObj->algDynamicParams.forceFrame =
              status.videnc2Status.encDynamicParams.forceFrame;
        algObj->algDynamicParams.refFrameRate =
              status.videnc2Status.encDynamicParams.refFrameRate;
    }

    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief Top level function to set/update various the codec dynamic parameters
 *
 * \param   hObj   [IN]  EncLink_H264Obj - H264 codec object
 * \param   algCreateParams[IN]  EncLink_AlgCreateParams - H264 create time parameters
 * \param   algDynamicParams[IN]  EncLink_AlgDynamicParams - H264 run time parameters
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int EncLinkH264_algDynamicParamUpdate(EncLink_H264Obj * hObj,
                               EncLink_AlgCreateParams * algCreateParams,
                               EncLink_AlgDynamicParams * algDynamicParams)
{
    Int retVal = ENC_LINK_S_SUCCESS;

    enclink_h264_set_dynamic_params(&hObj->dynamicParams, algDynamicParams);
    enclink_h264_set_algObject(hObj, algCreateParams, algDynamicParams);

    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief This function reset the codec instance
 *
 * \param  hObj     [IN]  EncLink_H264Obj - codec object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int32 EncLink_h264EncoderReset(EncLink_H264Obj * hObj)
{
    int error;

    IH264ENC_Handle handle;
    IALG_Fxns *fxns = NULL;

    handle = hObj->algHandle;
    fxns = (IALG_Fxns *) handle->fxns;

    fxns->algActivate((IALG_Handle) handle);
    error = enclink_h264_control(handle,
                                XDM_RESET,
                                &(hObj->dynamicParams),
                                &(hObj->status));

    fxns->algDeactivate((IALG_Handle) handle);

    return (error);
}

