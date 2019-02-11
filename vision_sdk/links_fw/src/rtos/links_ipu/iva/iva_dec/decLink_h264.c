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
 * \file decLink_h264.c Decode Link H264 private/specific API/function calls
 *
 * \brief  This file implemented the below H264 decoder functions
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
#include <ti/sdo/codecs/h264vdec/ih264vdec.h>
#include <ti/sdo/codecs/h264vdec/h264vdec_ti.h>

#include "decLink_priv.h"
#include "decLink_err.h"
#include "decLink_h264_priv.h"

#include <src/rtos/links_ipu/iva/codec_utils/utils_encdec.h>
#include <src/rtos/links_ipu/iva/codec_utils/iresman_hdvicp2_earlyacquire.h>

/*******************************************************************************
 *  Decode Link H264 Private Functions
 *******************************************************************************
 */
static IH264VDEC_Handle dec_link_h264_create(const IH264VDEC_Fxns * fxns,
                                             const IH264VDEC_Params * prms);
static Void dec_link_h264_delete(IH264VDEC_Handle handle);
static Int32 decLink_h264_control(IH264VDEC_Handle handle,
                                  IH264VDEC_Cmd cmd,
                                  IH264VDEC_DynamicParams * params,
                                  IH264VDEC_Status * status);
static Int decLink_h264_set_static_params(IH264VDEC_Params * staticParams,
                                          DecLink_AlgCreateParams *
                                          algCreateParams);
static Int decLink_h264_set_algObject(DecLink_H264Obj * algObj,
                                      DecLink_AlgCreateParams * algCreateParams,
                                      DecLink_AlgDynamicParams *
                                      algDynamicParams);
static Int decLink_h264_set_dynamic_params(IH264VDEC_DynamicParams *
                                           dynamicParams,
                                           DecLink_AlgDynamicParams *
                                           algDynamicParams);
static Void decLink_h264_freersrc(DecLink_H264Obj * hObj, Int rsrcMask);

static Int32 DecLink_h264DecoderFlush(DecLink_H264Obj * hObj, Bool hardFlush);
static Int32 DecLink_h264DecoderReset(DecLink_H264Obj * hObj);
static Int32 DecLink_h264DecoderFlushCheck(Int32);
static Int32 DecLink_h264DecoderResetCheck(Int32);
static Int32 DecLink_h264Decoder_checkErr(Int32, Int32);

extern IRES_Fxns H264VDEC_TI_IRES;


/**
 *******************************************************************************
 *
 * \brief This function create the H264 codec instance
 *        Create an H264VDEC instance object(using parameters specified by prms)
 *
 * \param  fxns     [IN]  IH264VDEC_Fxns - codec function pointers
 * \param  prms     [OUT] IH264VDEC_Params params
 *
 * \return  IH264VDEC_Handle - codec handle on success
 *
 *******************************************************************************
 */
static IH264VDEC_Handle dec_link_h264_create(const IH264VDEC_Fxns * fxns,
                                             const IH264VDEC_Params * prms)
{
    return ((IH264VDEC_Handle) ALG_create((IALG_Fxns *) fxns,
                                          NULL, (IALG_Params *) prms));
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance handle
 *        Delete the H264VDEC instance object specified by handle
 *
 * IH264VDEC_Handle - codec handle
 *
 * \return  Non
 *
 *******************************************************************************
 */
static Void dec_link_h264_delete(IH264VDEC_Handle handle)
{
    ALG_delete((IALG_Handle) handle);
}

/**
 *******************************************************************************
 *
 * \brief This function set/get the H264 codec parameter/state
 *
 * \param  handle   [IN]  IH264VDEC_Handle - codec handle
 * \param  cmd      [IN]  IH264VDEC_Cmd commands
 * \param  params   [IN]  IH264VDEC_DynamicParams - codec dynamic parameters
 * \param  status   [OUT] IH264VDEC_Status status
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int32 decLink_h264_control(IH264VDEC_Handle handle,
                                  IH264VDEC_Cmd cmd,
                                  IH264VDEC_DynamicParams * params,
                                  IH264VDEC_Status * status)
{
    int error = 0;
    IALG_Fxns *fxns = (IALG_Fxns *) handle->fxns;

    fxns->algActivate((IALG_Handle) handle);

    error = handle->fxns->ividdec3.control((IVIDDEC3_Handle) handle,
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

/**
 *******************************************************************************
 *
 * \brief This function used to flushes out all ouput buffers
 *        held inside the H264 decoder
 *
 * \param  pChObj         [IN]  DecLink_ChObj -  per channel handle
 * \param  inArgs         [IN]  IH264VDEC_InArgs -  codec input Args
 * \param  outArgs        [IN]  IH264VDEC_OutArgs -  codec output Args
 * \param  inputBufDesc   [IN]  XDM2_BufDesc -  input buffer descriptor
 * \param  outputBufDesc  [IN]  XDM2_BufDesc -  output buffer descriptor
 * \param  handle         [IN]  IH264VDEC_Handle -  codec handle
 * \param  freeFrameList  [IN]  System_BufferList -  free buffer list
 * \param  hardFlush      [OUT] Bool -  TURE if hard flush required
 *
 * \return  Int32 needReset
 *
 *******************************************************************************
 */
Int32 DecLinkH264_codecFlush(DecLink_ChObj *pChObj,
                             IH264VDEC_InArgs *inArgs,
                             IH264VDEC_OutArgs *outArgs,
                             XDM2_BufDesc *inputBufDesc,
                             XDM2_BufDesc *outputBufDesc,
                             IH264VDEC_Handle handle,
                             System_BufferList *freeFrameList,
                             Bool hardFlush)
{
    Int32 freeBufIdx;
    DecLink_H264Obj *hObj;
    IALG_Fxns *fxns;
    Int32 retValue=XDM_EOK;
    Int32 status = XDM_EFAIL;
    Int32 needReset = FALSE;

    hObj = &(pChObj->algObj.u.h264AlgIfObj);
    fxns = (IALG_Fxns *) handle->fxns;

    needReset =
      DecLink_h264DecoderResetCheck(outArgs->viddec3OutArgs.
                                    extendedError);
    status = DecLink_h264DecoderFlush(hObj, hardFlush);

    if (status == XDM_EOK)
    {
        do
        {

             #ifdef SYSTEM_DEBUG_DEC
             Vps_printf(" DECODE: CH%d: H264 Decoder Flushing !!!\n",
                        hObj->channelID
                        );
             #endif

             fxns->algActivate((IALG_Handle) handle);

             retValue = handle->fxns->ividdec3.process((IVIDDEC3_Handle)
                                                       handle,
                                                       inputBufDesc,
                                                       outputBufDesc,
                                                       (IVIDDEC3_InArgs *)
                                                       inArgs,
                                                       (IVIDDEC3_OutArgs *)
                                                       outArgs);

              fxns->algDeactivate((IALG_Handle) handle);

              freeBufIdx = 0;
              while (outArgs->viddec3OutArgs.freeBufID[freeBufIdx] != 0)
              {
                  freeFrameList->buffers[freeFrameList->numBuf] =
                      (System_Buffer *) outArgs->viddec3OutArgs.
                                      freeBufID[freeBufIdx];
                  freeFrameList->numBuf++;
                  pChObj->numBufsInCodec--;
                  freeBufIdx++;
              }

        } while(retValue == XDM_EOK);
    }
    if(needReset == TRUE)
    {
        DecLink_h264DecoderReset(hObj);
    }

    return (needReset);
}

/**
 *******************************************************************************
 *
 * \brief This function perform H264 decode of an input compressed bitstream
 *
 * \param  pObj            [IN]  DecLink_Obj - dec link handle
 * \param  pReqObj         [IN]  DecLink_ReqObj - dec link request object
 * \param  freeFrameList   [IN]  System_BufferList - freebuf list
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
Int32 Declink_h264DecodeFrame(DecLink_Obj * pObj,
                              DecLink_ReqObj * pReqObj,
                              System_BufferList * freeFrameList)
{
    Int32 error = XDM_EFAIL, extendedError = 0;
    Bool doDisplay = TRUE;
    Int32 i, freeBufIdx, prosIdx, chId;
    IH264VDEC_InArgs *inArgs;
    IH264VDEC_OutArgs *outArgs;
    XDM2_BufDesc *inputBufDesc;
    XDM2_BufDesc *outputBufDesc;
    IH264VDEC_Handle handle = NULL;
    IALG_Fxns *fxns = NULL;
    System_BitstreamBuffer *inBuf = NULL;
    System_VideoFrameBuffer *frame = NULL;
    System_Buffer *outFrame = NULL;
    IVIDEO2_BufDesc *displayBufs = NULL;
    UInt32 bytesConsumed;
    DecLink_ChObj *pChObj;
    Int32 needReset = FALSE;
    System_LinkChInfo *pFrameInfo;

    chId = pReqObj->InBuf->chNum;
    pChObj = &pObj->chObj[chId];

    inArgs = &pChObj->algObj.u.h264AlgIfObj.inArgs;
    outArgs = &pChObj->algObj.u.h264AlgIfObj.outArgs;
    inputBufDesc = &pChObj->algObj.u.h264AlgIfObj.inBufs;
    outputBufDesc = &pChObj->algObj.u.h264AlgIfObj.outBufs;
    handle = pChObj->algObj.u.h264AlgIfObj.algHandle;

    UTILS_assert(handle != NULL);

    fxns = (IALG_Fxns *) handle->fxns;

    bytesConsumed = 0;
    pChObj->algObj.u.h264AlgIfObj.numProcessCalls++;

    for (prosIdx = 0; prosIdx < pReqObj->OutFrameList.numBuf; prosIdx++)
    {
        /*-------------------------------------------------------------------*/
        /* Initialize the input ID in input arguments to the bufferid of */
        /* buffer element returned from getfreebuffer() function.  */
        /*-------------------------------------------------------------------*/
        /* inputID & numBytes need to update before every decode call */

        if (FALSE == outArgs->viddec3OutArgs.outBufsInUseFlag)
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
            freeFrameList->numBuf++;
            pChObj->numBufsInCodec--;
        }

        frame = (System_VideoFrameBuffer*)outFrame->payload;
        inBuf = (System_BitstreamBuffer*) pReqObj->InBuf->payload;
        inArgs->viddec3InArgs.inputID = (UInt32) outFrame;
        inArgs->viddec3InArgs.numBytes = inBuf->fillLength - bytesConsumed;

        for (i = 0; i < inputBufDesc->numBufs; i++)
        {
            /* Set proper buffer addresses for bitstreamn data */
            /*---------------------------------------------------------------*/
            inputBufDesc->descs[i].buf = (XDAS_Int8 *) inBuf->bufAddr
                                                       +  bytesConsumed;
            inputBufDesc->descs[i].bufSize.bytes = inBuf->bufSize;
        }

        for (i = 0; i < outputBufDesc->numBufs; i++)
        {
            /* Set proper buffer addresses for Frame data */
            /*---------------------------------------------------------------*/
            outputBufDesc->descs[i].buf = frame->bufAddr[i];
        }
        pChObj->numBufsInCodec++;

        fxns->algActivate((IALG_Handle) handle);
        error = handle->fxns->ividdec3.process((IVIDDEC3_Handle) handle,
                                               inputBufDesc,
                                               outputBufDesc,
                                               (IVIDDEC3_InArgs *) inArgs,
                                               (IVIDDEC3_OutArgs *) outArgs);
        fxns->algDeactivate((IALG_Handle) handle);
        bytesConsumed = outArgs->viddec3OutArgs.bytesConsumed;
        if (error != XDM_EOK)
        {
            //Vps_printf(" DECODE: ERROR: ALGPROCESS FAILED (status=0x%08x) !!!\n",
            //           error);
        }

        pChObj->algObj.prevOutFrame = outFrame;
        pReqObj->OutFrameList.buffers[prosIdx] = NULL;
        UTILS_assert(outArgs->viddec3OutArgs.displayBufsMode ==
                              IVIDDEC3_DISPLAYBUFS_EMBEDDED);
        displayBufs = &(outArgs->viddec3OutArgs.displayBufs.bufDesc[0]);
        if ((pChObj->isFirstIDRFrameFound == FALSE) &&
            ((!outArgs->viddec3OutArgs.extendedError) ||
             (!DecLink_h264Decoder_checkErr(extendedError, IH264VDEC_ERR_INVALIDPARAM_IGNORE))) &&
            ((displayBufs->frameType == IVIDEO_IDR_FRAME) ||
             (displayBufs->frameType == IVIDEO_I_FRAME)))
        {
            pChObj->isFirstIDRFrameFound = TRUE;
        }

        doDisplay = TRUE;
        bytesConsumed = outArgs->viddec3OutArgs.bytesConsumed;
        extendedError = outArgs->viddec3OutArgs.extendedError;

        if(((outArgs->viddec3OutArgs.extendedError)&&
            (!DecLink_h264Decoder_checkErr(extendedError, IH264VDEC_ERR_GAPSINFRAMENUM))&&
            (!DecLink_h264Decoder_checkErr(extendedError, IH264VDEC_ERR_INVALIDPARAM_IGNORE)))
           ||
           (pChObj->isFirstIDRFrameFound == FALSE))
        {

            #ifdef SYSTEM_DEBUG_DEC
            if (DecLink_h264Decoder_checkErr(outArgs->viddec3OutArgs.extendedError,
                                             IH264VDEC_ERR_PICSIZECHANGE))
            {
            Vps_printf(" DEC_LINK: CH%d decoder changing resolution \n",
                         chId);
            }
            else
            {
            Vps_printf(" DECODE: ERROR: ALGPROCESS FAILED (status=0x%08x) !!!\n",
                         extendedError);
            Vps_printf(" DEC_LINK: outArgs->viddec3OutArgs.extendedError for channel %d Error: 0x%x\n",
                         chId, outArgs->viddec3OutArgs.extendedError);
            Vps_printf(" DEC_LINK: Sequence called number %d\n",
                         pChObj->algObj.u.h264AlgIfObj.numProcessCalls);
            }
            #endif

            /* Workaround to fix a decode bug - WA start
               Some error cases the decoder is putting the same free
               buffer info in multiple freeBufIdx.  This bug will make
               Dec link crash. This WA to avoid such condition.
               Remove this WA once the decoder fix this issue.
            */
            for (i = 0; i < 10; i++)
            {
                freeBufIdx = i + 1;
                while (outArgs->viddec3OutArgs.freeBufID[freeBufIdx] != 0)
                {
                    if (outArgs->viddec3OutArgs.freeBufID[freeBufIdx] ==
                        outArgs->viddec3OutArgs.freeBufID[i])
                    {
                       outArgs->viddec3OutArgs.freeBufID[freeBufIdx] = 0;
                    }
                    freeBufIdx++;
                }
            }
            /* Workaround to fix a decode bug - WA End */

            doDisplay = FALSE;
            freeBufIdx = 0;

            while (outArgs->viddec3OutArgs.freeBufID[freeBufIdx] != 0)
            {
                if ((DecLink_h264Decoder_checkErr(outArgs->viddec3OutArgs.
                                                  extendedError,
                                                  IH264VDEC_ERR_PICSIZECHANGE))
                                                  && (outArgs->viddec3OutArgs.
                                                      freeBufID[freeBufIdx]
                                                      == (UInt32) outFrame))
                {
                    freeBufIdx++;
                }
                else
                {
                    freeFrameList->buffers[freeFrameList->numBuf] =
                        (System_Buffer *) outArgs->viddec3OutArgs.freeBufID[freeBufIdx];
                    freeFrameList->numBuf++;
                    pChObj->numBufsInCodec--;
                    freeBufIdx++;
                }
            }

#ifndef DEC_LINK_SUPRESS_ERROR_AND_RESET
            needReset = DecLinkH264_codecFlush(pChObj, inArgs,
                                               outArgs, inputBufDesc,
                                               outputBufDesc, handle,
                                               freeFrameList, FALSE);
            pReqObj->OutFrameList.buffers[prosIdx] = NULL;

            if (DecLink_h264Decoder_checkErr(extendedError,
                                             IH264VDEC_ERR_PICSIZECHANGE))
            {
                if(needReset != TRUE)
                {
                    inArgs->viddec3InArgs.numBytes =
                            inBuf->fillLength - bytesConsumed;
                    for (i = 0; i < inputBufDesc->numBufs; i++)
                    {
                        /* Set proper buffer addresses for bitstreamn */
                        /* data                                       */
                        /*--------------------------------------------*/
                        inputBufDesc->descs[i].buf =
                                      (XDAS_Int8 *) inBuf->bufAddr
                                       + bytesConsumed;
                        inputBufDesc->descs[i].bufSize.bytes = inBuf->bufSize;
                    }
                }

                fxns->algActivate((IALG_Handle) handle);
                error = handle->fxns->ividdec3.process((IVIDDEC3_Handle)
                                                       handle,
                                                       inputBufDesc,
                                                       outputBufDesc,
                                                       (IVIDDEC3_InArgs *)
                                                       inArgs,
                                                       (IVIDDEC3_OutArgs *)
                                                       outArgs);
                fxns->algDeactivate((IALG_Handle) handle);
                displayBufs = &(outArgs->viddec3OutArgs.displayBufs.bufDesc[0]);
                extendedError = outArgs->viddec3OutArgs.extendedError;

                if ((pChObj->isFirstIDRFrameFound == FALSE) &&
                    (!outArgs->viddec3OutArgs.extendedError) &&
                    ((displayBufs->frameType == IVIDEO_IDR_FRAME) ||
                     (displayBufs->frameType == IVIDEO_I_FRAME)))
                {
                    pChObj->isFirstIDRFrameFound = TRUE;
                }
                doDisplay = TRUE;
                if (error != XDM_EOK)
                {
                    Vps_printf(" DECODE: ERROR: ALGPROCESS FAILED (status=0x%08x) !!!\n",
                                 error);
                    Vps_printf(" DEC_LINK: outArgs->viddec3OutArgs.extendedError "
                                "for channel %d with Resolution change Error: 0x%x\n",
                                 chId, outArgs->viddec3OutArgs.extendedError);
                }
            }
#endif
        }

        if(doDisplay == TRUE)
        {
            extendedError = 0;
            pChObj->algObj.prevOutFrame = outFrame;
            pReqObj->OutFrameList.buffers[prosIdx] = NULL;
            UTILS_assert(outArgs->viddec3OutArgs.displayBufsMode ==
                         IVIDDEC3_DISPLAYBUFS_EMBEDDED);
            displayBufs = &(outArgs->viddec3OutArgs.displayBufs.bufDesc[0]);
            if ((outArgs->viddec3OutArgs.outputID[0] != 0)
                && (displayBufs->numPlanes))
            {
                XDAS_Int8 *pExpectedBuf;

                pReqObj->OutFrameList.buffers[prosIdx] =
                    (System_Buffer *) outArgs->viddec3OutArgs.outputID[0];
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
            while (outArgs->viddec3OutArgs.freeBufID[freeBufIdx] != 0)
            {
                freeFrameList->buffers[freeFrameList->numBuf] =
                    (System_Buffer *) outArgs->viddec3OutArgs.freeBufID[freeBufIdx];
                freeFrameList->numBuf++;
                pChObj->numBufsInCodec--;
                freeBufIdx++;
            }
        }

        /* Commenting out due to dec lib issue,
           gets locked-up with multiple flush commands */
#if 1
        if (pObj->createArgs.chCreateParams[chId].algCreateStatus ==
                             DEC_LINK_ALG_CREATE_STATUS_CREATE_DONE)
        {
            if (pChObj->numBufsInCodec >=
               (pObj->createArgs.chCreateParams[chId].numBufPerCh-1))
            {
                DecLinkH264_codecFlush(pChObj,
                                       &pChObj->algObj.u.h264AlgIfObj.inArgs,
                                       &pChObj->algObj.u.h264AlgIfObj.outArgs,
                                       &pChObj->algObj.u.h264AlgIfObj.inBufs,
                                       &pChObj->algObj.u.h264AlgIfObj.outBufs,
                                       pChObj->algObj.u.h264AlgIfObj.algHandle,
                                       freeFrameList, TRUE);
                Vps_printf(" DEC Link: Forced flush due to all dec ouput"
                            "buffers are locked-up inside the codec lib\n");
            }
        }
#endif
    }

    return (extendedError);
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate H264 decoder static parameters
 *
 * \param  dpbSizeInFrames   [IN] Int32 - DPB size in number of frames
 *
 * \return  h264VdecDPBSizeInFrames
 *
 *******************************************************************************
 */
static XDAS_Int32 decLink_h264_map_dpbsize2codecparam(Int32 dpbSizeInFrames)
{
    XDAS_Int32 h264VdecDPBSizeInFrames;

    if(DEC_LINK_DPB_SIZE_IN_FRAMES_DEFAULT == dpbSizeInFrames)
    {
        h264VdecDPBSizeInFrames = IH264VDEC_DPB_NUMFRAMES_DEFAULT;
    }
    else
    {
        if ((dpbSizeInFrames >= IH264VDEC_DPB_NUMFRAMES_0)
            &&
            (dpbSizeInFrames <= IH264VDEC_DPB_NUMFRAMES_16))
        {
            h264VdecDPBSizeInFrames =  dpbSizeInFrames;
        }
        else
        {
           Vps_printf(" DEC_LINK: Invalid param passed for DPBBufSize param [%d] "
                      "Forcing to default value [%d]",
                      dpbSizeInFrames,
                      IH264VDEC_DPB_NUMFRAMES_DEFAULT);
           h264VdecDPBSizeInFrames =  IH264VDEC_DPB_NUMFRAMES_DEFAULT;
        }
    }
    return h264VdecDPBSizeInFrames;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate H264 decoder static parameters
 *
 * \param  params   [IN] IH264VDEC_Params - H264 static parameters
 * \param  status   [IN] DecLink_AlgCreateParams - Dec Link static parameters
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int decLink_h264_set_static_params(IH264VDEC_Params * staticParams,
                                          DecLink_AlgCreateParams *
                                          algCreateParams)
{
    /* Initialize default values for static params */
    *staticParams = IH264VDEC_PARAMS;

    staticParams->viddec3Params.size = sizeof(IH264VDEC_Params);
    /* Both width & height needs to be align with 16 bytes */
    staticParams->viddec3Params.maxHeight =
                  VpsUtils_align(algCreateParams->maxHeight, 16);

    staticParams->viddec3Params.maxWidth =
                  VpsUtils_align(algCreateParams->maxWidth, 16);

    staticParams->presetProfileIdc = algCreateParams->presetProfile;

    staticParams->presetLevelIdc = algCreateParams->presetLevel;

    staticParams->processCallLevel = algCreateParams->processCallLevel;

    if (algCreateParams->processCallLevel == IH264VDEC_FRAMELEVELPROCESSCALL)
        algCreateParams->fieldMergeDecodeEnable = FALSE;

    staticParams->viddec3Params.displayDelay = algCreateParams->displayDelay;
    staticParams->dpbSizeInFrames =
        decLink_h264_map_dpbsize2codecparam(algCreateParams->dpbBufSizeInFrames);

    /* Enabling debug logging inside the codec. Details in appendix H in H.264
     * decoder user guide.
     */
    staticParams->debugTraceLevel = 0;
    staticParams->lastNFramesToLog = 31;

    staticParams->decodeFrameType = algCreateParams->decodeFrameType;

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function set/populate the parameters required for a processs call
 *
 * \param  algObj          [IN]  DecLink_H264Obj - codec object
 * \param  algCreateParams [IN]  DecLink_AlgCreateParams create parameters
 * \param  algDynamicParams[IN]  IH264VDEC_DynamicParams - dynamic parameters
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int decLink_h264_set_algObject(DecLink_H264Obj * algObj,
                                      DecLink_AlgCreateParams * algCreateParams,
                                      DecLink_AlgDynamicParams *
                                      algDynamicParams)
{
    UInt32 bufCnt;
    IH264VDEC_InArgs *inArgs;
    IH264VDEC_OutArgs *outArgs;
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
    inArgs->viddec3InArgs.inputID = 0;
    inArgs->viddec3InArgs.numBytes = 0;

    /*------------------------------------------------------------------------*/
    /* The outBufsInUseFlag tells us whether the previous input buffer given */
    /* by the application to the algorithm is still in use or not. Since */
    /* this is before the first decode call, assign this flag to 0. The */
    /* algorithm will take care to initialize this flag appropriately from */
    /* hereon for the current configuration.  */
    /*------------------------------------------------------------------------*/
    outArgs->viddec3OutArgs.outBufsInUseFlag = 0;
    outArgs->viddec3OutArgs.bytesConsumed = 0;
    outArgs->viddec3OutArgs.freeBufID[0] = 0;
    outArgs->viddec3OutArgs.outputID[0] = 0;
    outArgs->viddec3OutArgs.extendedError = 0;
    outArgs->viddec3OutArgs.displayBufsMode = IVIDDEC3_DISPLAYBUFS_EMBEDDED;
    memset(&outArgs->viddec3OutArgs.displayBufs.bufDesc, 0,
           sizeof(outArgs->viddec3OutArgs.displayBufs.bufDesc));
    outArgs->viddec3OutArgs.displayBufs.pBufDesc[0] = NULL;
    outArgs->viddec3OutArgs.decodedBufs.contentType = IVIDEO_PROGRESSIVE_FRAME;
    outArgs->viddec3OutArgs.decodedBufs.frameType = IVIDEO_I_FRAME;
    outArgs->viddec3OutArgs.decodedBufs.extendedError = 0;

    /*------------------------------------------------------------------------*/
    /* Initialize the input buffer properties as required by algorithm */
    /* based on info received by preceding GETBUFINFO call. First init the */
    /* number of input bufs.  */
    /*------------------------------------------------------------------------*/
    inputBufDesc->numBufs = algObj->status.viddec3Status.bufInfo.minNumInBufs;
    /*------------------------------------------------------------------------*/
    /* For the num of input bufs, initialize the buffer pointer addresses */
    /* and buffer sizes.  */
    /*------------------------------------------------------------------------*/
    inputBufDesc->descs[0].buf = NULL;
    inputBufDesc->descs[0].bufSize.bytes = 0;
    inputBufDesc->descs[0].memType =
        algObj->status.viddec3Status.bufInfo.inBufMemoryType[0];
    inputBufDesc->descs[0].memType = XDM_MEMTYPE_RAW;

    outputBufDesc->numBufs = algObj->status.viddec3Status.bufInfo.minNumOutBufs;
    for (bufCnt = 0; bufCnt < outputBufDesc->numBufs; bufCnt++)
    {
        outputBufDesc->descs[bufCnt].buf = NULL;
        outputBufDesc->descs[bufCnt].memType =
            algObj->status.viddec3Status.bufInfo.outBufMemoryType[bufCnt];
        outputBufDesc->descs[bufCnt].memType = XDM_MEMTYPE_RAW;

        if (outputBufDesc->descs[bufCnt].memType != XDM_MEMTYPE_RAW)
        {
            outputBufDesc->descs[bufCnt].bufSize.tileMem.width =
                algObj->status.viddec3Status.bufInfo.minOutBufSize[bufCnt].
                tileMem.width;
            outputBufDesc->descs[bufCnt].bufSize.tileMem.height =
                algObj->status.viddec3Status.bufInfo.minOutBufSize[bufCnt].
                tileMem.height;
        }
        else
        {
            outputBufDesc->descs[bufCnt].bufSize.bytes =
                (algObj->status.viddec3Status.bufInfo.minOutBufSize[bufCnt].
                tileMem.width *
                algObj->status.viddec3Status.bufInfo.minOutBufSize[bufCnt].
                tileMem.height);
        }
    }

    algObj->numProcessCalls = 0;

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief This function to set/populate H264 decoder dynamic parameters
 *
 * \param  params   [IN] IH264VDEC_DynamicParams - H264 dynamic parameters
 * \param  status   [IN] DecLink_AlgDynamicParams - Dec Link dynamic parameters
 *
 * \return  DEC_LINK_S_SUCCESS on success
 *
 *******************************************************************************
 */
static Int decLink_h264_set_dynamic_params(IH264VDEC_DynamicParams *
                                           dynamicParams,
                                           DecLink_AlgDynamicParams *
                                           algDynamicParams)
{
    *dynamicParams = IH264VDEC_TI_DYNAMICPARAMS;

    dynamicParams->viddec3DynamicParams.decodeHeader =
        algDynamicParams->decodeHeader;
    dynamicParams->viddec3DynamicParams.displayWidth =
        algDynamicParams->displayWidth;
    dynamicParams->viddec3DynamicParams.frameSkipMode =
        algDynamicParams->frameSkipMode;
    dynamicParams->viddec3DynamicParams.newFrameFlag =
        algDynamicParams->newFrameFlag;

    return DEC_LINK_S_SUCCESS;
}

#define DECLINKH264_ALGREATE_RSRC_NONE                                       (0)
#define DECLINKH264_ALGREATE_RSRC_ALGCREATED                           (1 <<  0)
#define DECLINKH264_ALGREATE_RSRC_IRES_ASSIGNED                        (1 <<  1)
#define DECLINKH264_ALGREATE_RSRC_ALL (                                        \
                                       DECLINKH264_ALGREATE_RSRC_ALGCREATED |  \
                                       DECLINKH264_ALGREATE_RSRC_IRES_ASSIGNED \
                                      )

/**
 *******************************************************************************
 *
 * \brief This function free-up the resouces allocated by the codec instance
 *
 * \param  hObj     [IN]  DecLink_H264Obj - codec object
 * \param  rsrcMask [IN]  resources mask
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void decLink_h264_freersrc(DecLink_H264Obj * hObj, Int rsrcMask)
{
    if (rsrcMask & DECLINKH264_ALGREATE_RSRC_IRES_ASSIGNED)
    {
        IRES_Status iresStatus;

        iresStatus =
            RMAN_freeResources((IALG_Handle) hObj->algHandle,
                               &H264VDEC_TI_IRES, hObj->scratchID);
        if (iresStatus != IRES_OK)
        {
            Vps_printf(" DECODE: ERROR: RMAN_freeResources FAILED (status=0x%08x) !!!\n",
                         iresStatus);
        }
    }
    if (rsrcMask & DECLINKH264_ALGREATE_RSRC_ALGCREATED)
    {
        dec_link_h264_delete(hObj->algHandle);
        hObj->algHandle = NULL;
    }
}

/**
 *******************************************************************************
 *
 * \brief This function do the necessary settings and create the
 *        H264 codec instance
 *
 * \param  hObj             [IN] DecLink_H264Obj - codec object
 * \param  algCreateParams  [IN] DecLink_AlgCreateParams - create parameters
 * \param  algDynamicParams [IN] IH264VDEC_DynamicParams - dynamic parameters
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
Int DecLinkH264_algCreate(DecLink_H264Obj * hObj,
                          DecLink_AlgCreateParams * algCreateParams,
                          DecLink_AlgDynamicParams * algDynamicParams,
                          Int linkID, Int channelID, Int scratchGroupID,
                          FVID2_Format *pFormat, UInt32 numFrames,
                          IRES_ResourceDescriptor resDesc[])
{
    Int retVal = DEC_LINK_S_SUCCESS;
    Int rsrcMask = DECLINKH264_ALGREATE_RSRC_NONE;

    UTILS_assert(Utils_encdecIsH264(algCreateParams->format) == TRUE);
    hObj->linkID = linkID;
    hObj->channelID = channelID;
    hObj->scratchID = scratchGroupID;

    memset(&hObj->inArgs, 0, sizeof(hObj->inArgs));
    memset(&hObj->outArgs, 0, sizeof(hObj->outArgs));
    memset(&hObj->inBufs, 0, sizeof(hObj->inBufs));
    memset(&hObj->outBufs, 0, sizeof(hObj->outBufs));
    memset(&hObj->status, 0, sizeof(hObj->status));
    memset(&hObj->memUsed, 0, sizeof(hObj->memUsed));

    hObj->staticParams.viddec3Params.size = sizeof(IH264VDEC_Params);
    hObj->status.viddec3Status.size = sizeof(IH264VDEC_Status);
    hObj->dynamicParams.viddec3DynamicParams.size =
        sizeof(IH264VDEC_DynamicParams);
    hObj->inArgs.viddec3InArgs.size = sizeof(IH264VDEC_InArgs);
    hObj->outArgs.viddec3OutArgs.size = sizeof(IH264VDEC_OutArgs);

    decLink_h264_set_static_params(&hObj->staticParams, algCreateParams);
    decLink_h264_set_dynamic_params(&hObj->dynamicParams, algDynamicParams);

    UTILS_MEMLOG_USED_START();
    hObj->algHandle =
        dec_link_h264_create((IH264VDEC_Fxns *) & H264VDEC_TI_IH264VDEC_MULTI,
                             &hObj->staticParams);
    UTILS_assertError((NULL != hObj->algHandle),
                      retVal, DEC_LINK_E_ALGCREATEFAILED, linkID, channelID);

    if (!UTILS_ISERROR(retVal))
    {
        Int32 status = UTILS_ENCDEC_S_SUCCESS;
        status = Utils_encdec_checkResourceAvail((IALG_Handle) hObj->algHandle,
                       &H264VDEC_TI_IRES, pFormat, numFrames, resDesc);
        UTILS_assertError((status == UTILS_ENCDEC_S_SUCCESS), retVal,
                          DEC_LINK_E_RMANRSRCASSIGNFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {
        IRES_Status iresStatus;

        rsrcMask |= DECLINKH264_ALGREATE_RSRC_ALGCREATED;
        iresStatus = RMAN_assignResources((IALG_Handle) hObj->algHandle,
                                          &H264VDEC_TI_IRES, scratchGroupID);
        UTILS_assertError((iresStatus == IRES_OK), retVal,
                          DEC_LINK_E_RMANRSRCASSIGNFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {
        Int algStatus;

        rsrcMask |= DECLINKH264_ALGREATE_RSRC_IRES_ASSIGNED;

        hObj->status.viddec3Status.data.buf = &(hObj->versionInfo[0]);
        hObj->status.viddec3Status.data.bufSize = sizeof(hObj->versionInfo);
        algStatus = decLink_h264_control(hObj->algHandle, XDM_GETVERSION,
                                         &(hObj->dynamicParams),
                                         &(hObj->status));
        if (algStatus == XDM_EOK)
        {
            #ifdef SYSTEM_DEBUG_DEC_VERBOSE
            Vps_printf(" DECODE: CH%d: %s:%s\n", hObj->channelID,
                         "H264DecCreated", hObj->versionInfo);
            #endif
        }

        algStatus = decLink_h264_control(hObj->algHandle, XDM_GETBUFINFO,
                                         &(hObj->dynamicParams),
                                         &(hObj->status));
        if (algStatus == XDM_EOK)
        {
            #ifdef SYSTEM_DEBUG_DEC_VERBOSE
            Vps_printf(" DECODE: CH%d: %s\n", hObj->channelID,
                         "XDM_GETBUFINFO done");
            #endif
        }

        algStatus = decLink_h264_control(hObj->algHandle,
                                         XDM_SETPARAMS,
                                         &hObj->dynamicParams, &hObj->status);
        UTILS_assertError((algStatus == XDM_EOK), retVal,
                          DEC_LINK_E_ALGSETPARAMSFAILED, linkID, channelID);
    }
    if (!UTILS_ISERROR(retVal))
    {
        decLink_h264_control(hObj->algHandle,
                             XDM_GETSTATUS,
                             &hObj->dynamicParams, &hObj->status);
    }
    if (UTILS_ISERROR(retVal))
    {
        decLink_h264_freersrc(hObj, rsrcMask);
    }
    else
    {
        /* Initialize the Inarg, OutArg, InBuf & OutBuf objects */
        decLink_h264_set_algObject(hObj, algCreateParams, algDynamicParams);
    }

    UTILS_MEMLOG_USED_END(hObj->memUsed);
    UTILS_MEMLOG_PRINT("DECLINK_H264",
                       hObj->memUsed,
                       (sizeof(hObj->memUsed) / sizeof(hObj->memUsed[0])));
    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief This function delete the codec instance and free-up the resources
 *
 * \param   hObj   [IN]  DecLink_H264Obj - H264 codec object
 *
 * \return  None
 *
 *******************************************************************************
 */
Void DecLinkH264_algDelete(DecLink_H264Obj * hObj)
{
    UTILS_MEMLOG_FREE_START();
    if (hObj->algHandle)
    {
        decLink_h264_freersrc(hObj, DECLINKH264_ALGREATE_RSRC_ALL);
    }

    if (hObj->algHandle)
    {
        dec_link_h264_delete(hObj->algHandle);
    }
    UTILS_MEMLOG_FREE_END(hObj->memUsed, 0 /* dont care */ );

}

/**
 *******************************************************************************
 *
 * \brief Function to check if codec Flush is required while decoding error
 *
 * \param  errorCode   [IN] codec error code
 *
 * \return  TRUE if Flush is required
 *
 *******************************************************************************
 */
#if 1
static Int32 DecLink_h264DecoderFlushCheck(Int32 errorCode)
{

  /*----------------------------------------------------------------------*/
  /* Under certain error conditions, the application need to stop decoding*/
  /* the current stream and do an XDM_FLUSH which enables the codec to    */
  /* flush (display and free up) the frames locked by it. The following   */
  /* error conditions fall in this category.                              */
  /*----------------------------------------------------------------------*/
   if((DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_STREAM_END)) ||
     (DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_PICSIZECHANGE)) ||
     (DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_UNSUPPRESOLUTION)) ||
     (DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_NUMREF_FRAMES)) ||
     (DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_DATA_SYNC)) ||
     (DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_DISPLAYWIDTH)))
   {
     return TRUE;
   }
   else
   {
     return FALSE;
   }
}
#else
static Int32 DecLink_h264DecoderFlushCheck(Int32 errorCode)
{
  /*----------------------------------------------------------------------*/
  /* Under certain error conditions, the application need to stop decoding*/
  /* the current stream and do an XDM_FLUSH which enables the codec to    */
  /* flush (display and free up) the frames locked by it. The following   */
  /* error conditions fall in this category.                              */
  /*----------------------------------------------------------------------*/
   if( (errorCode != 0)                                                                 &&
       !(DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_HDVICP2_IMPROPER_STATE)) &&
       !(DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_INVALID_MBOX_MESSAGE))   &&
       !(DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_DISPLAYWIDTH))           &&
       !(DecLink_h264Decoder_checkErr(errorCode, XDM_UNSUPPORTEDPARAM)) )
       {
              return TRUE;
       }
       else
       {
              return FALSE;
       }
}
#endif

/**
 *******************************************************************************
 *
 * \brief Function to check if codec return error decoding from error code
 *
 * \param  errMsg   [IN] codec erroe MSQ
 * \param  errVal   [IN] codec error Value
 *
 * \return  TRUE if error is occured
 *
 *******************************************************************************
 */
static Int32 DecLink_h264Decoder_checkErr(Int32 errMsg, Int32 errVal)
{
  if(errMsg & (1 << errVal))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

/**
 *******************************************************************************
 *
 * \brief Function to perform codec Flush
 *
 * \param  hObj       [IN] DecLink_H264Obj - codec handle
 * \param  hardFlush  [IN] Bool - Hard flush status
 *
 * \return  XDM_TRUE/XDM_EFAIL - Codec FLUSH status
 *
 *******************************************************************************
 */
static Int32 DecLink_h264DecoderFlush(DecLink_H264Obj * hObj, Bool hardFlush)
{
    int error = XDM_EFAIL;

    IH264VDEC_Handle handle;
    IH264VDEC_OutArgs *outArgs;
    IALG_Fxns *fxns = NULL;
    Int32 doFlush;

    outArgs = &hObj->outArgs;
    handle = hObj->algHandle;
    fxns = (IALG_Fxns *) handle->fxns;

    /* Check if XDM_FLUSH is required or not. */
    doFlush = DecLink_h264DecoderFlushCheck(outArgs->viddec3OutArgs.extendedError);

    if(doFlush || hardFlush)
    {
        #ifdef SYSTEM_DEBUG_DEC
        Vps_printf(" DECODE: CH%d: H264 Decoder flush needed (%d)!!!\n",
            hObj->channelID,
            outArgs->viddec3OutArgs.extendedError
        );
        #endif

       fxns->algActivate((IALG_Handle) handle);

       error = decLink_h264_control(handle,
                                   XDM_FLUSH,
                                   &(hObj->dynamicParams),
                                   &(hObj->status));

       fxns->algDeactivate((IALG_Handle) handle);

    }

    return (error);
}

/**
 *******************************************************************************
 *
 * \brief Function to check if codec Reset is required while decoding error
 *
 * \param  errorCode   [IN] codec error code
 *
 * \return  TRUE if Reset is required
 *
 *******************************************************************************
 */
static Int32 DecLink_h264DecoderResetCheck(Int32 errorCode)
{
   Int32 reset;
   if(DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_DATA_SYNC))
     reset = TRUE;
   else if(DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_NUMREF_FRAMES))
     reset = TRUE;
   else if(DecLink_h264Decoder_checkErr(errorCode, IH264VDEC_ERR_UNSUPPRESOLUTION))
     reset = TRUE;
   else
     reset = FALSE;

   return reset;
}

/**
 *******************************************************************************
 *
 * \brief Function to perform codec Reset
 *
 * \param  hObj  [IN] DecLink_H264Obj - codec handle
 *
 * \return  XDM_TRUE/XDM_EFAIL - Codec Reset status
 *
 *******************************************************************************
 */
static Int32 DecLink_h264DecoderReset(DecLink_H264Obj * hObj)
{
    int error;

    IH264VDEC_Handle handle;
    IALG_Fxns *fxns = NULL;

    handle = hObj->algHandle;
    fxns = (IALG_Fxns *) handle->fxns;

    fxns->algActivate((IALG_Handle) handle);
    error = decLink_h264_control(handle,
                               XDM_RESET,
                               &(hObj->dynamicParams),
                               &(hObj->status));

    fxns->algDeactivate((IALG_Handle) handle);

    return (error);
}

/* Nothing beyond this point */

