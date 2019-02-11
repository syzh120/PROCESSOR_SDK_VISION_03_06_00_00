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
 * \file encLink_jpeg.c Encode Link MJPEG private/specific API/function calls
 *
 * \brief  This file implemented the below MJPEG Encoder functions
 *         - Create/Delete/Control
 *         - Process call
 *         - set static/dynamic parameters
 *
 * \version 0.0 (April 2014) : [SS] First version
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
#include <ti/sdo/codecs/jpegvenc/ijpegenc.h>
#include <ti/sdo/codecs/jpegvenc/jpegenc_ti.h>

#include "encLink_priv.h"
#include "encLink_jpeg_priv.h"

#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>

/*******************************************************************************
 *  Encode Link MJPEG Private Functions
 *******************************************************************************
 */
static JPEGVENC_Handle enc_link_jpeg_create(const IJPEGVENC_Fxns * fxns,
                                            const IJPEGVENC_Params * prms);
static Void enc_link_jpeg_delete(JPEGVENC_Handle handle);
static Int32 enclink_jpeg_control(JPEGVENC_Handle handle,
                                  IJPEGVENC_Cmd cmd,
                                  IJPEGVENC_DynamicParams * params,
                                  IJPEGVENC_Status * status);
static Int enclink_jpeg_set_static_params(IJPEGVENC_Params * staticParams,
                                          EncLink_AlgCreateParams *
                                          algCreateParams);
static Int enclink_jpeg_set_algObject(EncLink_JPEGObj * algObj,
                                      EncLink_AlgCreateParams * algCreateParams,
                                      EncLink_AlgDynamicParams *
                                      algDynamicParams);
static Int enclink_jpeg_set_dynamic_params(IJPEGVENC_DynamicParams *
                                           dynamicParams,
                                           EncLink_AlgDynamicParams *
                                           algDynamicParams);
static Void enclink_jpeg_freersrc(EncLink_JPEGObj * hObj, Int rsrcMask);

extern IRES_Fxns JPEGVENC_TI_IRES;


/**
 *******************************************************************************
 *
 * \brief This function create the MJPEG codec instance
 *        Create an JPEGENC instance object(using parameters specified by prms)
 *
 * \param  fxns     [IN]  IJPEGVENC_Fxns - codec function pointers
 * \param  prms     [OUT] IJPEGVENC_Params params
 *
 * \return  JPEGVENC_Handle - codec handle on success
 *
 *******************************************************************************
 */
static JPEGVENC_Handle enc_link_jpeg_create(const IJPEGVENC_Fxns * fxns,
                                            const IJPEGVENC_Params * prms)
{
    return ((JPEGVENC_Handle) ALG_create((IALG_Fxns *) fxns,
                                         NULL, (IALG_Params *) prms));
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance handle
 *        Delete the JPEGENC instance object specified by handle
 *
 * JPEGVENC_Handle - codec handle
 *
 * \return  Non
 *
 *******************************************************************************
 */
static Void enc_link_jpeg_delete(JPEGVENC_Handle handle)
{
    ALG_delete((IALG_Handle) handle);
}

/**
 *******************************************************************************
 *
 * \brief This function set/get the MJPEG codec parameter/state
 *
 * \param  handle   [IN]  JPEGVENC_Handle - codec handle
 * \param  cmd      [IN]  IJPEGVENC_Cmd commands
 * \param  params   [IN]  IJPEGVENC_DynamicParams - codec dynamic parameters
 * \param  status   [OUT] IJPEGVENC_Status status
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int32 enclink_jpeg_control(JPEGVENC_Handle handle,
                                  IJPEGVENC_Cmd cmd,
                                  IJPEGVENC_DynamicParams * params,
                                  IJPEGVENC_Status * status)
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
 * \brief This function perform JPEG Encode of an input compressed bitstream
 *
 * \param  pChObj          [IN]  EncLink_ChObj - Enc link channel Object
 * \param  pReqObj         [IN]  EncLink_ReqObj - Enc link request object
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int32 Enclink_jpegEncodeFrame(EncLink_ChObj * pChObj, EncLink_ReqObj * pReqObj)
{
    int error = XDM_EFAIL;
    Int32 i;
    IJPEGVENC_InArgs *inArgs;
    IJPEGVENC_OutArgs *outArgs;
    IVIDEO2_BufDesc *inputBufDesc;
    XDM2_BufDesc *outputBufDesc;
    JPEGVENC_Handle handle;
    IALG_Fxns *fxns = NULL;
    System_IVideoContentType contentType;
    System_BitstreamBuffer *outBuf = NULL;
    System_VideoFrameBuffer *inFrame = NULL;

    inArgs = &pChObj->algObj.u.jpegAlgIfObj.inArgs;
    outArgs = &pChObj->algObj.u.jpegAlgIfObj.outArgs;
    inputBufDesc = &pChObj->algObj.u.jpegAlgIfObj.inBufs;
    outputBufDesc = &pChObj->algObj.u.jpegAlgIfObj.outBufs;
    handle = pChObj->algObj.u.jpegAlgIfObj.algHandle;

    UTILS_assert(handle != NULL);

    fxns = (IALG_Fxns *) handle->fxns;

    inArgs->videnc2InArgs.inputID =
        (UInt32) pReqObj->InFrameList.buffers[0];
    inFrame = (System_VideoFrameBuffer*)pReqObj->InFrameList.buffers[0]->payload;

    for (i = 0; i < inputBufDesc->numPlanes; i++)
    {
        /* Set proper buffer addresses for Frame data */
        /*---------------------------------------------------------------*/
        inputBufDesc->planeDesc[i].buf = inFrame->bufAddr[i];
    }

    outBuf = (System_BitstreamBuffer*) pReqObj->OutBuf->payload;
    outBuf->metaFillLength = 0;

    for (i = 0; i < outputBufDesc->numBufs; i++)
    {
        /* Set proper buffer addresses for bitstream data */
      /*---------------------------------------------------------------*/
        outputBufDesc->descs[i].buf = outBuf->bufAddr;
        outputBufDesc->descs[i].bufSize.bytes = outBuf->bufSize;
    }

    fxns->algActivate((IALG_Handle) handle);
    error =
        handle->fxns->ividenc.process((IVIDENC2_Handle) handle,
                                      inputBufDesc, outputBufDesc,
                                      (IVIDENC2_InArgs *) inArgs,
                                      (IVIDENC2_OutArgs *) outArgs);
    fxns->algDeactivate((IALG_Handle) handle);

    outBuf->fillLength = outArgs->videnc2OutArgs.bytesGenerated;

    if(Utils_encdecIsJPEG(pChObj->algObj.u.jpegAlgIfObj.format) == TRUE)
        outBuf->flags = System_Bitstream_Buffer_Flag_Set_Bitstream_Format
                                        (outBuf->flags,
                                         SYSTEM_BITSTREAM_CODING_TYPE_MJPEG);

    if (pChObj->algObj.u.jpegAlgIfObj.staticParams.videnc2Params.
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
 * \brief This function set/populate MJPEG Encoder static parameters
 *
 * \param  params   [IN] IJPEGVENC_Params - JPEG static parameters
 * \param  status   [IN] EncLink_AlgCreateParams - Enc Link static parameters
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_jpeg_set_static_params(IJPEGVENC_Params * staticParams,
                                          EncLink_AlgCreateParams *
                                          algCreateParams)
{
    /* Initialize default values for static params */
    *staticParams = JPEGVENC_TI_PARAMS;

    staticParams->videnc2Params.maxHeight = algCreateParams->maxHeight;

    staticParams->videnc2Params.maxWidth = algCreateParams->maxWidth;

    staticParams->videnc2Params.maxInterFrameInterval = NULL;
    staticParams->videnc2Params.inputContentType = SYSTEM_IVIDEO_PROGRESSIVE;

    staticParams->videnc2Params.inputChromaFormat =
        algCreateParams->inputChromaFormat;

    staticParams->videnc2Params.profile = algCreateParams->profile;

    staticParams->videnc2Params.level = algCreateParams->level;

    staticParams->videnc2Params.numInputDataUnits = 1;
    staticParams->videnc2Params.numOutputDataUnits = 1;
    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the parameters required for a processs call
 *
 * \param  algObj          [IN]  EncLink_JPEGObj - codec object
 * \param  algCreateParams [IN]  EncLink_AlgCreateParams create parameters
 * \param  algDynamicParams[IN]  EncLink_AlgDynamicParams - dynamic parameters
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_jpeg_set_algObject(EncLink_JPEGObj * algObj,
                                      EncLink_AlgCreateParams * algCreateParams,
                                      EncLink_AlgDynamicParams *
                                      algDynamicParams)
{
    IJPEGVENC_InArgs *inArgs;
    IJPEGVENC_OutArgs *outArgs;
    IVIDEO2_BufDesc *inputBufDesc;
    XDM2_BufDesc *outputBufDesc;
    IJPEGVENC_Status *status;
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

    outArgs->videnc2OutArgs.extendedError = 0;
    outArgs->videnc2OutArgs.bytesGenerated = 0;
    outArgs->videnc2OutArgs.encodedFrameType = SYSTEM_IVIDEO_I_FRAME;
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
            if (status->videnc2Status.bufInfo.minOutBufSize[i].bytes
                > ANALYTICINFO_OUTPUT_BUFF_SIZE)
            {
                Vps_printf
                    (" ENCODE: Memory could not get allocated for Analytic info buffer\n");
            }
        /*-------------------------------------------------------------------*/
            /* Set proper buffer addresses for MV & SAD data */
        /*-------------------------------------------------------------------*/
            outputBufDesc->descs[i].buf = NULL;
        }
    }

    /*------------------------------------------------------------------------*/
    /* Video buffer layout, field interleaved or field separated */
    /* Only IVIDEO_FIELD_INTERLEAVED and VENC_FIELD_SEPARATED are supported
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
    inputBufDesc->numPlanes = status->videnc2Status.bufInfo.minNumInBufs;
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
            algObj->status.videnc2Status.bufInfo.minInBufSize[i].tileMem.width *
            algObj->status.videnc2Status.bufInfo.minInBufSize[i].tileMem.height;
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

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function to set/populate MJPEG Encoder dynamic parameters
 *
 * \param  params   [IN] IJPEGVENC_DynamicParams - JPEG dynamic parameters
 * \param  status   [IN] EncLink_AlgDynamicParams - Enc Link dynamic parameters
 *
 * \return  ENC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int enclink_jpeg_set_dynamic_params(IJPEGVENC_DynamicParams *
                                           dynamicParams,
                                           EncLink_AlgDynamicParams *
                                           algDynamicParams)
{
    *dynamicParams = JPEGVENC_TI_DYNAMICPARAMS;
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
    dynamicParams->videnc2DynamicParams.refFrameRate =
        algDynamicParams->refFrameRate;
    dynamicParams->videnc2DynamicParams.ignoreOutbufSizeFlag = XDAS_FALSE;

    return 0;
}

#define ENCLINKJPEG_ALGREATE_RSRC_NONE                                       (0)
#define ENCLINKJPEG_ALGREATE_RSRC_ALGCREATED                           (1 <<  0)
#define ENCLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED                        (1 <<  1)
#define ENCLINKJPEG_ALGREATE_RSRC_ALL (                                        \
                                       ENCLINKJPEG_ALGREATE_RSRC_ALGCREATED |  \
                                       ENCLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED \
                                      )

/**
 *******************************************************************************
 *
 * \brief This function free-up the resouces allocated by the codec instance
 *
 * \param  hObj     [IN]  EncLink_JPEGObj - codec object
 * \param  rsrcMask [IN]  resources mask
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void enclink_jpeg_freersrc(EncLink_JPEGObj * hObj, Int rsrcMask)
{
    if (rsrcMask & ENCLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED)
    {
        IRES_Status iresStatus;

        iresStatus =
            RMAN_freeResources((IALG_Handle) hObj->algHandle,
                               &JPEGVENC_TI_IRES, hObj->scratchID);
        if (iresStatus != IRES_OK)
        {
            Vps_printf(" ENCODE: ERROR: RMAN_freeResources FAILED (status=0x%08x) !!!\n",
                         iresStatus);
        }
    }
    if (rsrcMask & ENCLINKJPEG_ALGREATE_RSRC_ALGCREATED)
    {
        enc_link_jpeg_delete(hObj->algHandle);
        hObj->algHandle = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief This function do the necessary settings and create the
 *        MJPEG codec instance
 *
 * \param  hObj             [IN] EncLink_JPEGObj - codec object
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
Int EncLinkJPEG_algCreate(EncLink_JPEGObj * hObj,
                          EncLink_AlgCreateParams * algCreateParams,
                          EncLink_AlgDynamicParams * algDynamicParams,
                          Int linkID, Int channelID, Int scratchGroupID)
{
    Int retVal = ENC_LINK_S_SUCCESS;
    Int rsrcMask = ENCLINKJPEG_ALGREATE_RSRC_NONE;
    Int algStatus;

    UTILS_assert(Utils_encdecIsJPEG(algCreateParams->format) == TRUE);
    hObj->format = algCreateParams->format;
    hObj->linkID = linkID;
    hObj->channelID = channelID;
    hObj->scratchID = scratchGroupID;

    memset(&hObj->inArgs, 0, sizeof(hObj->inArgs));
    memset(&hObj->outArgs, 0, sizeof(hObj->outArgs));
    memset(&hObj->inBufs, 0, sizeof(hObj->inBufs));
    memset(&hObj->outBufs, 0, sizeof(hObj->outBufs));
    memset(&hObj->status, 0, sizeof(hObj->status));
    memset(&hObj->memUsed, 0, sizeof(hObj->memUsed));

    hObj->status.videnc2Status.size = sizeof(IJPEGVENC_Status);
    hObj->inArgs.videnc2InArgs.size = sizeof(IJPEGVENC_InArgs);
    hObj->outArgs.videnc2OutArgs.size = sizeof(IJPEGVENC_OutArgs);
    hObj->staticParams.videnc2Params.size = sizeof(IVIDENC2_Params);
    hObj->dynamicParams.videnc2DynamicParams.size =
        sizeof(IVIDENC2_DynamicParams);

    enclink_jpeg_set_static_params(&hObj->staticParams, algCreateParams);
    enclink_jpeg_set_dynamic_params(&hObj->dynamicParams, algDynamicParams);

    UTILS_MEMLOG_USED_START();
    hObj->algHandle =
        enc_link_jpeg_create((IJPEGVENC_Fxns *) & JPEGVENC_TI_IJPEGVENC,
                             &hObj->staticParams);
    UTILS_assertError((NULL != hObj->algHandle),
                      retVal, ENC_LINK_E_ALGCREATEFAILED, linkID, channelID);
    if (!UTILS_ISERROR(retVal))
    {
        IRES_Status iresStatus;

        rsrcMask |= ENCLINKJPEG_ALGREATE_RSRC_ALGCREATED;
        iresStatus = RMAN_assignResources((IALG_Handle) hObj->algHandle,
                                          &JPEGVENC_TI_IRES, scratchGroupID);
        UTILS_assertError((iresStatus == IRES_OK), retVal,
                          ENC_LINK_E_RMANRSRCASSIGNFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {

        rsrcMask |= ENCLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED;

        hObj->status.videnc2Status.data.buf = &(hObj->versionInfo[0]);
        hObj->status.videnc2Status.data.bufSize = sizeof(hObj->versionInfo);
        algStatus = enclink_jpeg_control(hObj->algHandle, XDM_GETVERSION,
                                         &(hObj->dynamicParams),
                                         &(hObj->status));
        if (algStatus == XDM_EOK)
        {
            Vps_printf( " ENCODE: CH%d: %s:%s\n", hObj->channelID,
                                  "JPEGDecCreated", hObj->versionInfo);
        }
        algStatus = enclink_jpeg_control(hObj->algHandle,
                                         XDM_SETDEFAULT,
                                         &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          ENC_LINK_E_ALGSETPARAMSFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {
        algStatus = enclink_jpeg_control(hObj->algHandle,
                                         XDM_SETPARAMS,
                                         &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          ENC_LINK_E_ALGSETPARAMSFAILED, linkID, channelID);
    }

    if (!UTILS_ISERROR(retVal))
    {
        enclink_jpeg_control(hObj->algHandle,
                             XDM_GETSTATUS,
                             &hObj->dynamicParams, &hObj->status);
    }
    if (!UTILS_ISERROR(retVal))
    {
        algStatus =
            enclink_jpeg_control(hObj->algHandle,
                                 XDM_GETBUFINFO,
                                 &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          ENC_LINK_E_ALGGETBUFINFOFAILED, linkID, channelID);
    }
    if (UTILS_ISERROR(retVal))
    {
        enclink_jpeg_freersrc(hObj, rsrcMask);
    }
    else
    {
        /* Initialize the Inarg, OutArg, InBuf & OutBuf objects */
        enclink_jpeg_set_algObject(hObj, algCreateParams, algDynamicParams);
    }

    UTILS_MEMLOG_USED_END(hObj->memUsed);
    UTILS_MEMLOG_PRINT("ENCLINK_JPEG",
                       hObj->memUsed,
                       (sizeof(hObj->memUsed) / sizeof(hObj->memUsed[0])));

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance and free-up the resources
 *
 * \param   hObj   [IN]  EncLink_JPEGObj - MJPEG codec object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void EncLinkJPEG_algDelete(EncLink_JPEGObj * hObj)
{
    UTILS_MEMLOG_FREE_START();
    if (hObj->algHandle)
    {
        enclink_jpeg_freersrc(hObj, ENCLINKJPEG_ALGREATE_RSRC_ALL);
    }

    if (hObj->algHandle)
    {
        enc_link_jpeg_delete(hObj->algHandle);
    }
    UTILS_MEMLOG_FREE_END(hObj->memUsed, 0 /* dont care */ );
}

/**
 *******************************************************************************
 *
 * \brief This function set/update various the codec dynamic parameters
 *
 * \param   hObj   [IN]  EncLink_algObj - MJPEG codec object
 *
 * \return  None
 *
 *******************************************************************************
 */
Int32 EncLinkJPEG_algSetConfig(EncLink_algObj * algObj)
{
    Int32 status = ENC_LINK_S_SUCCESS;
    UInt32 bitMask;
    Bool setConfigFlag = FALSE;
    UInt key;

    key = Hwi_disable();
    bitMask = algObj->setConfigBitMask;

    /* Set the modified encoder bitRate value */
    if ((bitMask >> ENC_LINK_SETCONFIG_BITMASK_BITRATE) & 0x1)
    {

        algObj->u.jpegAlgIfObj.dynamicParams.videnc2DynamicParams.
            targetBitRate = algObj->algDynamicParams.targetBitRate;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf(" ENCLINK: new targetbitrate to set:%d \n",
                   algObj->algDynamicParams.targetBitRate);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                     (1 <<
                                      ENC_LINK_SETCONFIG_BITMASK_BITRATE));
        setConfigFlag = TRUE;
    }

    /* Set the modified encoder Fps value */
    if ((bitMask >> ENC_LINK_SETCONFIG_BITMASK_FPS) & 0x1)
    {
        algObj->u.jpegAlgIfObj.dynamicParams.videnc2DynamicParams.
            targetFrameRate = algObj->algDynamicParams.targetFrameRate;
        algObj->u.jpegAlgIfObj.dynamicParams.videnc2DynamicParams.
            targetBitRate = algObj->algDynamicParams.targetBitRate;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf(" ENCLINK: new targetbitrate to set:%d \n",
                   algObj->algDynamicParams.targetBitRate);
        Vps_printf(" ENCLINK: new targetframerate to set:%d \n",
                   algObj->algDynamicParams.targetFrameRate);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                     (1 << ENC_LINK_SETCONFIG_BITMASK_FPS));
        setConfigFlag = TRUE;
    }

    /* Set the modified encoder Intra Frame Interval(GOP) value */
    if ((bitMask >> ENC_LINK_SETCONFIG_BITMASK_INTRAI) & 0x1)
    {
        algObj->u.jpegAlgIfObj.dynamicParams.videnc2DynamicParams.
            intraFrameInterval = algObj->algDynamicParams.intraFrameInterval;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf(" ENCLINK: new intraFrameInterval to set:%d \n",
                   algObj->algDynamicParams.intraFrameInterval);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                     (1 << ENC_LINK_SETCONFIG_BITMASK_INTRAI));
        setConfigFlag = TRUE;
    }

    /* toggle Force IDR */
    if ((bitMask >> ENC_LINK_SETCONFIG_BITMASK_FORCEI) & 0x1)
    {

        algObj->algDynamicParams.forceFrame = TRUE;
        algObj->algDynamicParams.forceFrameStatus = FALSE;

        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                     (1 << ENC_LINK_SETCONFIG_BITMASK_FORCEI));
        setConfigFlag = TRUE;
    }

    /* Set the modified Qualityfactor value for a jpeg Frame */
    if ((bitMask >>  ENC_LINK_SETCONFIG_BITMASK_QPI) & 0x1)
    {
        algObj->u.jpegAlgIfObj.dynamicParams.qualityFactor = algObj->algDynamicParams.qpInitI;
        #ifdef SYSTEM_VERBOSE_PRINTS
        Vps_printf(" ENCLINK: new qualityFactor Param to set:%d\n",
                algObj->algDynamicParams.qpInitI);
        #endif
        algObj->setConfigBitMask &= (ENC_LINK_SETCONFIG_BITMASK_RESET_VALUE ^
                                    (1 << ENC_LINK_SETCONFIG_BITMASK_QPI));
        setConfigFlag = TRUE;
    }

    Hwi_restore(key);

    if (setConfigFlag)
    {
        status = enclink_jpeg_control(algObj->u.jpegAlgIfObj.algHandle,
                                      XDM_SETPARAMS,
                                      &algObj->u.jpegAlgIfObj.dynamicParams,
                                      &algObj->u.jpegAlgIfObj.status);
        if (UTILS_ISERROR(status))
        {
            Vps_printf(" ENCLINK: ERROR in Run time parameters changes, "
                        "Extended Error code: %d \n",
                        algObj->u.jpegAlgIfObj.status.videnc2Status.extendedError);
        }
        else
        {
            #ifdef SYSTEM_VERBOSE_PRINTS
            Vps_printf(" ENCLINK: Run time parameters changed %d\n",
                       algObj->u.jpegAlgIfObj.status.videnc2Status.
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
 * \param   hObj   [IN]  EncLink_algObj - MJPEG codec object
 *
 * \return  None
 *
 *******************************************************************************
 */
Int32 EncLinkJPEG_algGetConfig(EncLink_algObj * algObj)
{
    Int retVal = ENC_LINK_S_SUCCESS;
    IJPEGVENC_DynamicParams dynamicParams;
    IJPEGVENC_Status status;

    if(algObj->getConfigFlag == TRUE)
    {

        status.videnc2Status.size = sizeof(IJPEGVENC_Status);
        dynamicParams.videnc2DynamicParams.size = sizeof(IJPEGVENC_DynamicParams);

        retVal = enclink_jpeg_control(algObj->u.jpegAlgIfObj.algHandle,
                                      XDM_GETSTATUS, &dynamicParams, &status);
        if (UTILS_ISERROR(retVal))
        {
            Vps_printf(" ENCLINK: ERROR in Run time parameters changes, "
                        "Extended Error code: %d \n",
                        status.videnc2Status.extendedError);
        }

        algObj->getConfigFlag = FALSE;

        algObj->algDynamicParams.inputWidth =
            status.videnc2Status.encDynamicParams.inputWidth;
        algObj->algDynamicParams.inputHeight =
            status.videnc2Status.encDynamicParams.inputHeight;
    }
    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief Top level function to set/update various the codec dynamic parameters
 *
 * \param   hObj   [IN]  EncLink_JPEGObj - MJPEG codec object
 * \param   hObj   [IN]  EncLink_AlgCreateParams - MJPEG create time parameters
 * \param   hObj   [IN]  EncLink_AlgDynamicParams - MJPEG run time parameters
 *
 * \return  None
 *
 *******************************************************************************
 */
Int EncLinkJPEG_algDynamicParamUpdate(EncLink_JPEGObj * hObj,
                               EncLink_AlgCreateParams * algCreateParams,
                               EncLink_AlgDynamicParams * algDynamicParams)
{
    Int retVal = ENC_LINK_S_SUCCESS;

    enclink_jpeg_set_dynamic_params(&hObj->dynamicParams, algDynamicParams);
    enclink_jpeg_set_algObject(hObj, algCreateParams, algDynamicParams);

    return (retVal);
}

/* Nothing beyond this point */

