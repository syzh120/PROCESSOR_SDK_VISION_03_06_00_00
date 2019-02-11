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
 * \file decLink_jpeg.c Decode Link MJPEG private/specific API/function calls
 *
 * \brief  This file implemented the below MJPEG decoder functions
 *         - Create/Delete/Control
 *         - Process call
 *         - set static/dynamic parameters
 *
 * \version 0.0 (Jan 2014) : [SS] First version
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
#include <ti/xdais/dm/ividdec3.h>
#include <ti/sdo/codecs/jpegvdec/ijpegvdec.h>
#include <ti/sdo/codecs/jpegvdec/jpegvdec_ti.h>

#include "decLink_priv.h"
#include "decLink_err.h"
#include "decLink_jpeg_priv.h"

#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>
#include <src/rtos/links_ipu/iva/codec_utils/iresman_hdvicp2_earlyacquire.h>

/*******************************************************************************
 *  Decode Link MJPEG Private Functions
 *******************************************************************************
 */
static IJPEGVDEC_Handle dec_link_jpeg_create(const IJPEGVDEC_Fxns * fxns,
                                             const IJPEGVDEC_Params * prms);
static Void dec_link_jpeg_delete(IJPEGVDEC_Handle handle);
static Int32 decLink_jpeg_control(IJPEGVDEC_Handle handle,
                                  IJPEGVDEC_Cmd cmd,
                                  IJPEGVDEC_DynamicParams * params,
                                  IJPEGVDEC_Status * status);
static Int decLink_jpeg_set_static_params(IJPEGVDEC_Params * staticParams,
                                          DecLink_AlgCreateParams *
                                          algCreateParams);
static Int decLink_jpeg_set_algObject(DecLink_JPEGObj * algObj,
                                      DecLink_AlgCreateParams * algCreateParams,
                                      DecLink_AlgDynamicParams *
                                      algDynamicParams);
static Int decLink_jpeg_set_dynamic_params(IJPEGVDEC_DynamicParams *
                                           dynamicParams,
                                           DecLink_AlgDynamicParams *
                                           algDynamicParams);
static Void decLink_jpeg_freersrc(DecLink_JPEGObj * hObj, Int rsrcMask);

extern IRES_Fxns JPEGVDEC_TI_IRES;


/**
 *******************************************************************************
 *
 * \brief This function create the MJPEG codec instance
 *        Create an JPEGVDEC instance object(using parameters specified by prms)
 *
 * \param  fxns     [IN]  IJPEGVDEC_Fxns - codec function pointers
 * \param  prms     [OUT] IJPEGVDEC_Params params
 *
 * \return  IJPEGVDEC_Handle - codec handle on success
 *
 *******************************************************************************
 */
static IJPEGVDEC_Handle dec_link_jpeg_create(const IJPEGVDEC_Fxns * fxns,
                                             const IJPEGVDEC_Params * prms)
{
    return ((IJPEGVDEC_Handle) ALG_create((IALG_Fxns *) fxns,
                                          NULL, (IALG_Params *) prms));
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance handle
 *        Delete the JPEGVDEC instance object specified by handle
 *
 * IJPEGVDEC_Handle - codec handle
 *
 * \return  Non
 *
 *******************************************************************************
 */
static Void dec_link_jpeg_delete(IJPEGVDEC_Handle handle)
{
    ALG_delete((IALG_Handle) handle);
}

/**
 *******************************************************************************
 *
 * \brief This function set/get the MJPEG codec parameter/state
 *
 * \param  handle   [IN]  IJPEGVDEC_Handle - codec handle
 * \param  cmd      [IN]  IJPEGVDEC_Cmd commands
 * \param  params   [IN]  IJPEGVDEC_DynamicParams - codec dynamic parameters
 * \param  status   [OUT] IJPEGVDEC_Status status
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int32 decLink_jpeg_control(IJPEGVDEC_Handle handle,
                                  IJPEGVDEC_Cmd cmd,
                                  IJPEGVDEC_DynamicParams * params,
                                  IJPEGVDEC_Status * status)
{
    int error = 0;
    IALG_Fxns *fxns = (IALG_Fxns *) handle->fxns;

    fxns->algActivate((IALG_Handle) handle);

    error = handle->fxns->ividdec.control((IVIDDEC3_Handle) handle,
                                           (IVIDDEC3_Cmd) cmd,
                                           (IVIDDEC3_DynamicParams *) params,
                                           (IVIDDEC3_Status *) status);
    fxns->algDeactivate((IALG_Handle) handle);

    if (error != XDM_EOK)
    {
        Vps_printf(" DECODE: ERROR: ALGCONTROL FAILED CMD=0x%08x (status=%08x) !!!\n",
                     cmd, error);
    }
    return error;
}

static void decLink_jpeg_extractAppMarker(System_BitstreamBuffer *inBuf,
                System_VideoFrameBuffer *outFrame)
{
    UInt8 *pInBuf = inBuf->bufAddr;

    if(pInBuf[0]==0xFF && pInBuf[1]==0xD8)
    {
        /* valid JPEG */
        if(pInBuf[2]==0xFF && pInBuf[3]==JPEG_APP_MARKER_TAG)
        {
            /* found APP marker of interest */
            outFrame->metaFillLength =
                (((UInt16)pInBuf[4] << 8 ) + pInBuf[5]) - 2;

            if(outFrame->metaFillLength>JPEG_APP_MARKER_SIZE_MAX)
                outFrame->metaFillLength = 0;

            if(outFrame->metaFillLength)
            {
                memcpy(outFrame->metaBufAddr,
                        &pInBuf[6],
                        outFrame->metaFillLength);

                Cache_wb(
                          (Ptr)outFrame->metaBufAddr,
                          outFrame->metaBufSize,
                          Cache_Type_ALLD,
                          TRUE
                        );
            }
        }
    }

}

/**
 *******************************************************************************
 *
 * \brief This function perform JPEG decode of an input compressed bitstream
 *
 * \param  pObj            [IN]  DecLink_Obj - dec link handle
 * \param  pReqObj         [IN]  DecLink_ReqObj - dec link request object
 * \param  freeFrameList   [IN]  System_BufferList - freebuf list
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int32 Declink_jpegDecodeFrame(DecLink_Obj * pObj,
                              DecLink_ReqObj * pReqObj,
                              System_BufferList * freeFrameList)
{
    Int32 error = XDM_EFAIL, chId;
    Int32 i, freeBufIdx, prosIdx;
    IJPEGVDEC_InArgs *inArgs;
    IJPEGVDEC_OutArgs *outArgs;
    XDM2_BufDesc *inputBufDesc;
    XDM2_BufDesc *outputBufDesc;
    IJPEGVDEC_Handle handle;
    IALG_Fxns *fxns = NULL;
    System_BitstreamBuffer *inBuf = NULL;
    System_VideoFrameBuffer *frame = NULL;
    System_Buffer *outFrame = NULL;
    IVIDEO2_BufDesc *displayBufs = NULL;
    UInt32 bytesConsumed;
    DecLink_ChObj *pChObj;
    System_LinkChInfo *pFrameInfo;

    chId = pReqObj->InBuf->chNum;
    pChObj = &pObj->chObj[chId];

    inArgs = &pChObj->algObj.u.jpegAlgIfObj.inArgs;
    outArgs = &pChObj->algObj.u.jpegAlgIfObj.outArgs;
    inputBufDesc = &pChObj->algObj.u.jpegAlgIfObj.inBufs;
    outputBufDesc = &pChObj->algObj.u.jpegAlgIfObj.outBufs;
    handle = pChObj->algObj.u.jpegAlgIfObj.algHandle;

    UTILS_assert(handle != NULL);

    fxns = (IALG_Fxns *) handle->fxns;

    bytesConsumed = 0;

    for (prosIdx=0; prosIdx< pReqObj->OutFrameList.numBuf; prosIdx++)
    {
        /*----------------------------------------------------------------*/
        /* Initialize the input ID in input arguments to the bufferid of  */
        /* buffer element returned from getfreebuffer() function.         */
        /*----------------------------------------------------------------*/
        /* inputID & numBytes need to update before every decode call */

        if (FALSE == outArgs->viddecOutArgs.outBufsInUseFlag)
        {
            outFrame = pReqObj->OutFrameList.buffers[prosIdx];
        }
        else
        {
            UTILS_assert(NULL != pChObj->algObj.prevOutFrame);
            /* Previous buffer was in use. Free the current outBuf */
            outFrame = pChObj->algObj.prevOutFrame;
            freeFrameList->buffers[freeFrameList->numBuf] =
                            pReqObj->OutFrameList.buffers[prosIdx];
            pChObj->numBufsInCodec--;
            freeFrameList->numBuf++;
        }

        frame = (System_VideoFrameBuffer*)outFrame->payload;
        inBuf = (System_BitstreamBuffer*) pReqObj->InBuf->payload;
        inArgs->viddecInArgs.inputID = (UInt32) outFrame;
        inArgs->viddecInArgs.numBytes = inBuf->fillLength - bytesConsumed;

        for (i = 0; i < inputBufDesc->numBufs; i++)
        {
            /* Set proper buffer addresses for bitstreamn data */
            /*------------------------------------------------------------*/
            inputBufDesc->descs[i].buf = (XDAS_Int8 *) inBuf->bufAddr
                                                       +  bytesConsumed;
            inputBufDesc->descs[i].bufSize.bytes = inBuf->bufSize;
        }

        if(frame->metaBufAddr!=NULL)
        {
            /* extarct APP marker data from JPEG bitstream */
            decLink_jpeg_extractAppMarker(inBuf, frame);
        }

        for (i = 0; i < outputBufDesc->numBufs; i++)
        {
            /* Set proper buffer addresses for Frame data */
            /*------------------------------------------------------------*/
            outputBufDesc->descs[i].buf = frame->bufAddr[i];
        }
        pChObj->numBufsInCodec++;

        fxns->algActivate((IALG_Handle) handle);
        error = handle->fxns->ividdec.process((IVIDDEC3_Handle) handle,
                                              inputBufDesc,
                                              outputBufDesc,
                                              (IVIDDEC3_InArgs *) inArgs,
                                              (IVIDDEC3_OutArgs *) outArgs);
        fxns->algDeactivate((IALG_Handle) handle);
        bytesConsumed = outArgs->viddecOutArgs.bytesConsumed;
        if (error != XDM_EOK)
        {
            Vps_printf(" DECODE: ERROR: ALGPROCESS FAILED (status=0x%08x) !!!\n",
                       error);
        }
        pChObj->algObj.prevOutFrame = outFrame;
        pReqObj->OutFrameList.buffers[prosIdx] = NULL;
        UTILS_assert(outArgs->viddecOutArgs.displayBufsMode ==
                     IVIDDEC3_DISPLAYBUFS_EMBEDDED);
        displayBufs = &(outArgs->viddecOutArgs.displayBufs.bufDesc[0]);
        if ((outArgs->viddecOutArgs.outputID[0] != 0)
            && (displayBufs->numPlanes))
        {
            XDAS_Int8 *pExpectedBuf;

            pReqObj->OutFrameList.buffers[prosIdx] =
              (System_Buffer *) outArgs->viddecOutArgs.outputID[0];
            frame = (System_VideoFrameBuffer*)
                       (pReqObj->OutFrameList.buffers[prosIdx])->payload;
            pExpectedBuf = frame->bufAddr[0];
            UTILS_assert(displayBufs->planeDesc[0].buf == pExpectedBuf);
            /* Enable this code once SysTemFrameInfo is updated with support
             * for storing frame resolution info */
            pFrameInfo = (System_LinkChInfo *) &frame->chInfo;
            {
                UTILS_assert(pFrameInfo != NULL);
                pFrameInfo->width =
                    displayBufs->activeFrameRegion.bottomRight.x -
                    displayBufs->activeFrameRegion.topLeft.x;
                pFrameInfo->height =
                    displayBufs->activeFrameRegion.bottomRight.y -
                    displayBufs->activeFrameRegion.topLeft.y;
                pFrameInfo->pitch[0] = displayBufs->imagePitch[0];
                pFrameInfo->pitch[1] = displayBufs->imagePitch[1];
                pFrameInfo->startX =
                    displayBufs->activeFrameRegion.topLeft.x;
                pFrameInfo->startY =
                    displayBufs->activeFrameRegion.topLeft.y;
                pFrameInfo->flags = System_Link_Ch_Info_Set_Flag_Mem_Type(
                    pFrameInfo->flags, SYSTEM_MT_NONTILEDMEM);
                pFrameInfo->flags = System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update(
                    pFrameInfo->flags, TRUE);
            }
            frame->flags = System_Video_Frame_Set_Flag_Fid(frame->flags,
                Utils_encdecMapXDMContentType2SYSFID(displayBufs->
                                                     contentType));
        }
        freeBufIdx = 0;
        while (outArgs->viddecOutArgs.freeBufID[freeBufIdx] != 0)
        {
            freeFrameList->buffers[freeFrameList->numBuf] =
              (System_Buffer *) outArgs->viddecOutArgs.freeBufID[freeBufIdx];
            freeFrameList->numBuf++;
            pChObj->numBufsInCodec--;
            freeBufIdx++;
        }
    }

    return (error);
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate MJPEG decoder static parameters
 *
 * \param  params   [IN] IJPEGVDEC_Params - JPEG static parameters
 * \param  status   [IN] DecLink_AlgCreateParams - Dec Link static parameters
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int decLink_jpeg_set_static_params(IJPEGVDEC_Params * staticParams,
                                          DecLink_AlgCreateParams *
                                          algCreateParams)
{
    /* Initialize default values for static params */
    *staticParams = JPEGVDEC_TI_Static_Params;

    staticParams->viddecParams.maxHeight = algCreateParams->maxHeight;

    staticParams->viddecParams.maxWidth = algCreateParams->maxWidth;

    staticParams->viddecParams.displayDelay = algCreateParams->displayDelay;
    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the parameters required for a processs call
 *
 * \param  algObj          [IN]  DecLink_JPEGObj - codec object
 * \param  algCreateParams [IN]  DecLink_AlgCreateParams create parameters
 * \param  algDynamicParams[IN]  IJPEGVDEC_DynamicParams - dynamic parameters
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int decLink_jpeg_set_algObject(DecLink_JPEGObj * algObj,
                                      DecLink_AlgCreateParams * algCreateParams,
                                      DecLink_AlgDynamicParams *
                                      algDynamicParams)
{
    UInt32 bufCnt;
    IJPEGVDEC_InArgs *inArgs;
    IJPEGVDEC_OutArgs *outArgs;
    XDM2_BufDesc *inputBufDesc;
    XDM2_BufDesc *outputBufDesc;

    inArgs = &algObj->inArgs;
    outArgs = &algObj->outArgs;
    inputBufDesc = &algObj->inBufs;
    outputBufDesc = &algObj->outBufs;

     /*-----------------------------------------------------------------------*/
    /* Initialize the input ID in input arguments to the bufferid of */
    /* buffer element returned from getfreebuffer() function.  */
     /*-----------------------------------------------------------------------*/
    /* inputID & numBytes need to update before every decode process call */
    inArgs->viddecInArgs.inputID = 0;
    inArgs->viddecInArgs.numBytes = 0;

    /*------------------------------------------------------------------------*/
    /* The outBufsInUseFlag tells us whether the previous input buffer given */
    /* by the application to the algorithm is still in use or not. Since */
    /* this is before the first decode call, assign this flag to 0. The */
    /* algorithm will take care to initialize this flag appropriately from */
    /* hereon for the current configuration.  */
    /*------------------------------------------------------------------------*/
    outArgs->viddecOutArgs.outBufsInUseFlag = 0;
    outArgs->viddecOutArgs.bytesConsumed = 0;
    outArgs->viddecOutArgs.freeBufID[0] = 0;
    outArgs->viddecOutArgs.outputID[0] = 0;
    outArgs->viddecOutArgs.extendedError = 0;
    outArgs->viddecOutArgs.displayBufsMode = IVIDDEC3_DISPLAYBUFS_EMBEDDED;
    memset(&outArgs->viddecOutArgs.displayBufs.bufDesc, 0,
           sizeof(outArgs->viddecOutArgs.displayBufs.bufDesc));
    outArgs->viddecOutArgs.displayBufs.pBufDesc[0] = NULL;
    outArgs->viddecOutArgs.decodedBufs.contentType = SYSTEM_IVIDEO_PROGRESSIVE_FRAME;
    outArgs->viddecOutArgs.decodedBufs.frameType = SYSTEM_IVIDEO_I_FRAME;
    outArgs->viddecOutArgs.decodedBufs.extendedError = 0;

    /*------------------------------------------------------------------------*/
    /* Initialize the input buffer properties as required by algorithm */
    /* based on info received by preceding GETBUFINFO call. First init the */
    /* number of input bufs.  */
    /*------------------------------------------------------------------------*/
    inputBufDesc->numBufs = algObj->status.viddecStatus.bufInfo.minNumInBufs;
    /*------------------------------------------------------------------------*/
    /* For the num of input bufs, initialize the buffer pointer addresses */
    /* and buffer sizes.  */
    /*------------------------------------------------------------------------*/
    inputBufDesc->descs[0].buf = NULL;
    inputBufDesc->descs[0].bufSize.bytes = 0;
    inputBufDesc->descs[0].memType =
        algObj->status.viddecStatus.bufInfo.inBufMemoryType[0];
    inputBufDesc->descs[0].memType = XDM_MEMTYPE_RAW;

    outputBufDesc->numBufs = algObj->status.viddecStatus.bufInfo.minNumOutBufs;
    for (bufCnt = 0; bufCnt < outputBufDesc->numBufs; bufCnt++)
    {
        outputBufDesc->descs[bufCnt].buf = NULL;
        outputBufDesc->descs[bufCnt].memType =
            algObj->status.viddecStatus.bufInfo.outBufMemoryType[bufCnt];
        outputBufDesc->descs[bufCnt].memType = XDM_MEMTYPE_RAW;

        if (outputBufDesc->descs[bufCnt].memType != XDM_MEMTYPE_RAW)
        {
            outputBufDesc->descs[bufCnt].bufSize.tileMem.width =
                algObj->status.viddecStatus.bufInfo.minOutBufSize[bufCnt].
                tileMem.width;
            outputBufDesc->descs[bufCnt].bufSize.tileMem.height =
                algObj->status.viddecStatus.bufInfo.minOutBufSize[bufCnt].
                tileMem.height;
        }
        else
        {
            outputBufDesc->descs[bufCnt].bufSize.bytes =
                (algObj->status.viddecStatus.bufInfo.minOutBufSize[bufCnt].
                tileMem.width *
                algObj->status.viddecStatus.bufInfo.minOutBufSize[bufCnt].
                tileMem.height);
        }
    }

    return DEC_LINK_S_SUCCESS;
}

/**
 *******************************************************************************
 *
 * \brief This function to set/populate MJPEG decoder dynamic parameters
 *
 * \param  params   [IN] IJPEGVDEC_DynamicParams - JPEG dynamic parameters
 * \param  status   [IN] DecLink_AlgDynamicParams - Dec Link dynamic parameters
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int decLink_jpeg_set_dynamic_params(IJPEGVDEC_DynamicParams *
                                           dynamicParams,
                                           DecLink_AlgDynamicParams *
                                           algDynamicParams)
{
    *dynamicParams = JPEGVDEC_TI_DynamicParams;

    dynamicParams->viddecDynamicParams.decodeHeader =
        algDynamicParams->decodeHeader;
    dynamicParams->viddecDynamicParams.displayWidth =
        algDynamicParams->displayWidth;
    dynamicParams->viddecDynamicParams.frameSkipMode =
        algDynamicParams->frameSkipMode;
    dynamicParams->viddecDynamicParams.newFrameFlag =
        algDynamicParams->newFrameFlag;

    return DEC_LINK_S_SUCCESS;
}

/**< Define various states of the codec create process */
#define DECLINKJPEG_ALGREATE_RSRC_NONE                                       (0)
#define DECLINKJPEG_ALGREATE_RSRC_ALGCREATED                           (1 <<  0)
#define DECLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED                        (1 <<  1)
#define DECLINKJPEG_ALGREATE_RSRC_ALL (                                        \
                                       DECLINKJPEG_ALGREATE_RSRC_ALGCREATED |  \
                                       DECLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED \
                                      )

/**
 *******************************************************************************
 *
 * \brief This function free-up the resouces allocated by the codec instance
 *
 * \param  hObj     [IN]  DecLink_JPEGObj - codec object
 * \param  rsrcMask [IN]  resources mask
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void decLink_jpeg_freersrc(DecLink_JPEGObj * hObj, Int rsrcMask)
{
    if (rsrcMask & DECLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED)
    {
        IRES_Status iresStatus;

        iresStatus =
            RMAN_freeResources((IALG_Handle) hObj->algHandle,
                               &JPEGVDEC_TI_IRES, hObj->scratchID);
        if (iresStatus != IRES_OK)
        {
            Vps_printf(" DECODE: ERROR: RMAN_freeResources FAILED (status=0x%08x) !!!\n",
                         iresStatus);
        }
    }
    if (rsrcMask & DECLINKJPEG_ALGREATE_RSRC_ALGCREATED)
    {
        dec_link_jpeg_delete(hObj->algHandle);
        hObj->algHandle = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief This function do the necessary settings and create the
 *        MJPEG codec instance
 *
 * \param  hObj             [IN] DecLink_JPEGObj - codec object
 * \param  algCreateParams  [IN] DecLink_AlgCreateParams - create parameters
 * \param  algDynamicParams [IN] IJPEGVDEC_DynamicParams - dynamic parameters
 * \param  linkID           [IN] Link ID
 * \param  channelID        [IN] Channel ID
 * \param  scratchGroupID   [IN] Scratch group ID
 * \param  pFormat          [IN] FVID2_Format - output frame resolution/details
 * \param  numFrames        [IN] number of ouput frames required
 * \param  resDesc          [IN] IRES_ResourceDescriptor RAMN resource details
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int DecLinkJPEG_algCreate(DecLink_JPEGObj * hObj,
                          DecLink_AlgCreateParams * algCreateParams,
                          DecLink_AlgDynamicParams * algDynamicParams,
                          Int linkID, Int channelID, Int scratchGroupID,
                          FVID2_Format *pFormat, UInt32 numFrames,
                          IRES_ResourceDescriptor resDesc[])
{
    Int retVal = DEC_LINK_S_SUCCESS;
    Int rsrcMask = DECLINKJPEG_ALGREATE_RSRC_NONE;

    UTILS_assert(Utils_encdecIsJPEG(algCreateParams->format) == TRUE);
    hObj->linkID = linkID;
    hObj->channelID = channelID;
    hObj->scratchID = scratchGroupID;

    memset(&hObj->inArgs, 0, sizeof(hObj->inArgs));
    memset(&hObj->outArgs, 0, sizeof(hObj->outArgs));
    memset(&hObj->inBufs, 0, sizeof(hObj->inBufs));
    memset(&hObj->outBufs, 0, sizeof(hObj->outBufs));
    memset(&hObj->status, 0, sizeof(hObj->status));
    memset(&hObj->memUsed, 0, sizeof(hObj->memUsed));

    hObj->staticParams.viddecParams.size = sizeof(IJPEGVDEC_Params);
    hObj->status.viddecStatus.size = sizeof(IJPEGVDEC_Status);
    hObj->dynamicParams.viddecDynamicParams.size =
        sizeof(IJPEGVDEC_DynamicParams);
    hObj->inArgs.viddecInArgs.size = sizeof(IJPEGVDEC_InArgs);
    hObj->outArgs.viddecOutArgs.size = sizeof(IJPEGVDEC_OutArgs);

    decLink_jpeg_set_static_params(&hObj->staticParams, algCreateParams);
    decLink_jpeg_set_dynamic_params(&hObj->dynamicParams, algDynamicParams);

    UTILS_MEMLOG_USED_START();
    hObj->algHandle =
        dec_link_jpeg_create((IJPEGVDEC_Fxns *) & JPEGVDEC_TI_IJPEGVDEC,
                             &hObj->staticParams);
    UTILS_assertError((NULL != hObj->algHandle),
                      retVal, DEC_LINK_E_ALGCREATEFAILED, linkID, channelID);

    if (!UTILS_ISERROR(retVal))
    {
        Int32 status = UTILS_ENCDEC_S_SUCCESS;
        status = Utils_encdec_checkResourceAvail((IALG_Handle) hObj->algHandle,
                       &JPEGVDEC_TI_IRES, pFormat, numFrames, resDesc);
        UTILS_assertError((status == UTILS_ENCDEC_S_SUCCESS), retVal,
                          DEC_LINK_E_RMANRSRCASSIGNFAILED, linkID, channelID);
    }

    if (!UTILS_ISERROR(retVal))
    {
        IRES_Status iresStatus;

        rsrcMask |= DECLINKJPEG_ALGREATE_RSRC_ALGCREATED;
        iresStatus = RMAN_assignResources((IALG_Handle) hObj->algHandle,
                                          &JPEGVDEC_TI_IRES, scratchGroupID);
        UTILS_assertError((iresStatus == IRES_OK), retVal,
                          DEC_LINK_E_RMANRSRCASSIGNFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {
        Int algStatus;

        rsrcMask |= DECLINKJPEG_ALGREATE_RSRC_IRES_ASSIGNED;

        hObj->status.viddecStatus.data.buf = &(hObj->versionInfo[0]);
        hObj->status.viddecStatus.data.bufSize = sizeof(hObj->versionInfo);
        algStatus = decLink_jpeg_control(hObj->algHandle, XDM_GETVERSION,
                                         &(hObj->dynamicParams),
                                         &(hObj->status));
        if (algStatus == XDM_EOK)
        {
            #ifdef SYSTEM_DEBUG_DEC_VERBOSE
            Vps_printf(" DECODE: CH%d: %s:%s\n", hObj->channelID,
                        "JPEGDecCreated", hObj->versionInfo);
            #endif
        }

        algStatus = decLink_jpeg_control(hObj->algHandle, XDM_GETBUFINFO,
                                         &(hObj->dynamicParams),
                                         &(hObj->status));
        if (algStatus == XDM_EOK)
        {
            #ifdef SYSTEM_DEBUG_DEC_VERBOSE
            Vps_printf(" DECODE: CH%d: %s\n", hObj->channelID,
                        "XDM_GETBUFINFO done");
            #endif
        }

        algStatus = decLink_jpeg_control(hObj->algHandle,
                                         XDM_SETPARAMS,
                                         &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          DEC_LINK_E_ALGSETPARAMSFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {
        decLink_jpeg_control(hObj->algHandle,
                             XDM_GETSTATUS,
                             &hObj->dynamicParams, &hObj->status);
    }
    if (UTILS_ISERROR(retVal))
    {
        decLink_jpeg_freersrc(hObj, rsrcMask);
    }
    else
    {
        /* Initialize the Inarg, OutArg, InBuf & OutBuf objects */
        decLink_jpeg_set_algObject(hObj, algCreateParams, algDynamicParams);
    }

    UTILS_MEMLOG_USED_END(hObj->memUsed);
    UTILS_MEMLOG_PRINT("DECLINK_JPEG",
                       hObj->memUsed,
                       (sizeof(hObj->memUsed) / sizeof(hObj->memUsed[0])));
    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance and free-up the resources
 *
 * \param   hObj   [IN]  DecLink_JPEGObj - MJPEG codec object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void DecLinkJPEG_algDelete(DecLink_JPEGObj * hObj)
{
    UTILS_MEMLOG_FREE_START();
    if (hObj->algHandle)
    {
        decLink_jpeg_freersrc(hObj, DECLINKJPEG_ALGREATE_RSRC_ALL);
    }

    if (hObj->algHandle)
    {
        dec_link_jpeg_delete(hObj->algHandle);
    }
    UTILS_MEMLOG_FREE_END(hObj->memUsed, 0 /* dont care */ );
}

/* Nothing beyond this point */

