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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "chains_nullSrcDisplay_priv.h"
#include <src/rtos/chains_common/chains.h>
#include <src/common/TI_logo_640_224_sp.h>

/*******************************************************************************
 *  DEFINES
 *******************************************************************************
 */
#define NULLSRC_TIME_INTERVAL           (33)
#define NULLSRC_NUM_OUTBUF              (4)
#define NULLSRC_OUT_WIDTH               (1280)
#define NULLSRC_OUT_HEIGHT              (720)
#define TILOGO_WIDTH                    (640)
#define TILOGO_HEIGHT                   (224)

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
chains_nullSrcDisplayObj gUcObj;
Chains_DisplayType gDisplayType;
UInt32 gDisplayWidth;
UInt32 gDisplayHeight;

static char useCaseRunTimeMenu[] = {
"\n "
"\n ===================="
"\n Chains Run-time Menu"
"\n ===================="
"\n "
"\n 0: Stop Chain"
"\n "
"\n p: Print Performance Statistics "
"\n "
"\n Enter Choice: "
"\n "
};

/**
 *******************************************************************************
 *
 * \brief   Null source Null use case Set Application paremeters
 *`
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void chains_nullSrcDisplay_SetAppPrms(chains_nullSrcDisplayObj *pObj, Void *appObj)
{
    System_LinkChInfo *pChInfo;
    NullSrcLink_CreateParams *pNullSrcPrm = &pObj->NullSourcePrm;

    ChainsCommon_GetDisplayWidthHeight(
                gDisplayType,
                &gDisplayWidth,
                &gDisplayHeight);

    NullSrcLink_CreateParams_Init(pNullSrcPrm);

    pNullSrcPrm->timerPeriodMilliSecs = NULLSRC_TIME_INTERVAL;
    pNullSrcPrm->outQueInfo.numCh = 1;
    pNullSrcPrm->channelParams[0].numBuffers = NULLSRC_NUM_OUTBUF;

    pChInfo = &pNullSrcPrm->outQueInfo.chInfo[0];

    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(pChInfo->flags,
                                            SYSTEM_DF_YUV420SP_UV);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(pChInfo->flags,
                                            SYSTEM_SF_PROGRESSIVE);
    pChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(pChInfo->flags,
                                            SYSTEM_BUFFER_TYPE_VIDEO_FRAME);
    pChInfo->width = NULLSRC_OUT_WIDTH;
    pChInfo->height = NULLSRC_OUT_HEIGHT;
    pChInfo->startX = 0;
    pChInfo->startY = 0;
    pChInfo->pitch[0] = SystemUtils_align(pChInfo->width, 32);
    pChInfo->pitch[1] = SystemUtils_align(pChInfo->width, 32);

    /* Alg FrameCopy parameters */
    pObj->Alg_FrameCopyPrm.baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_FRAMECOPY;
    pObj->Alg_FrameCopyPrm.maxWidth           = NULLSRC_OUT_WIDTH;
    pObj->Alg_FrameCopyPrm.maxHeight          = NULLSRC_OUT_HEIGHT;
    pObj->Alg_FrameCopyPrm.numOutputFrames    = 3;

    /* Display parameters */
    pObj->DisplayPrm.rtParams.tarWidth = gDisplayWidth;
    pObj->DisplayPrm.rtParams.tarHeight = gDisplayHeight;
    pObj->DisplayPrm.rtParams.posX = 0U;
    pObj->DisplayPrm.rtParams.posY = 0U;
    pObj->DisplayPrm.displayId = DISPLAY_LINK_INST_DSS_VID1;

    ChainsCommon_StartDisplayCtrl(
                    gDisplayType,
                    gDisplayWidth,
                    gDisplayHeight);
}

/**
 *******************************************************************************
 *
 * \brief   Fill the source buffers with known pattern
 *`
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
static Void fillSrcBuf(chains_nullSrcDisplayObj *pObj)
{
    Int32 status;
    UInt32 ht, bufCnt, logoStartX, logoStartY, offset;
    UInt8 *srcAddr, *dstAddr;
    NullSrcLink_GetBufInfoParams getBufInfoPrm;
    System_Buffer *pBuffer;
    System_VideoFrameBuffer *pVideoFrame;

    /**
     *  Get the Null source buffer info
     */
    getBufInfoPrm.chId = 0U;
    status = System_linkControl(
                    pObj->NullSourceLinkID,
                    NULL_SRC_LINK_CMD_GET_BUF_INFO,
                    &getBufInfoPrm,
                    sizeof(NullSrcLink_GetBufInfoParams),
                    TRUE);
    UTILS_assert (SYSTEM_LINK_STATUS_SOK == status);

    for (bufCnt = 0;bufCnt < getBufInfoPrm.numBuf;bufCnt ++)
    {
        pBuffer = &getBufInfoPrm.buffer[bufCnt];
        pVideoFrame = pBuffer->payload;

        memset(
            pVideoFrame->bufAddr[0],
            0xFF,
            (NULLSRC_OUT_WIDTH * NULLSRC_OUT_HEIGHT));

        memset(
            pVideoFrame->bufAddr[1],
            0x80,
            (NULLSRC_OUT_WIDTH * NULLSRC_OUT_HEIGHT/2));

        /* copy TI logo */
        logoStartX = (NULLSRC_OUT_WIDTH - TILOGO_WIDTH)/2;
        logoStartY = (NULLSRC_OUT_HEIGHT - TILOGO_HEIGHT)/2;
        offset = (logoStartY * NULLSRC_OUT_WIDTH) + logoStartX;
        dstAddr = (UInt8*)((UInt32)pVideoFrame->bufAddr[0] + offset);
        srcAddr = tiLogo_640_224;
        for(ht = 0;ht < TILOGO_HEIGHT;ht++)
        {
            memcpy(dstAddr, srcAddr, TILOGO_WIDTH);
            dstAddr += NULLSRC_OUT_WIDTH;
            srcAddr += TILOGO_WIDTH;
        }

        offset = ((logoStartY/2) * NULLSRC_OUT_WIDTH) + logoStartX;
        dstAddr = (UInt8*)((UInt32)pVideoFrame->bufAddr[1] + offset);
        srcAddr = (UInt8*)((UInt32)tiLogo_640_224 + \
                                            (TILOGO_WIDTH * TILOGO_HEIGHT));
        for(ht = 0;ht < TILOGO_HEIGHT/2;ht++)
        {
            memcpy(dstAddr, srcAddr, TILOGO_WIDTH);
            dstAddr += NULLSRC_OUT_WIDTH;
            srcAddr += TILOGO_WIDTH;
        }

        Cache_wb(
            pVideoFrame->bufAddr[0],
            (NULLSRC_OUT_WIDTH * NULLSRC_OUT_HEIGHT),
            Cache_Type_ALLD,
            TRUE);

        Cache_wb(
            pVideoFrame->bufAddr[1],
            (NULLSRC_OUT_WIDTH * NULLSRC_OUT_HEIGHT/2),
            Cache_Type_ALLD,
            TRUE);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Null source Null use case
 *`
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_nullSrc_display()
{
    char ch;
    UInt32 done = FALSE;

    gDisplayType = CHAINS_DISPLAY_TYPE_HDMI_1080P;

    Vps_printf(" #### ENTERING SAMPLE_APP:NULL SOURCE -> DISPLAY USE CASE ####");

    chains_nullSrcDisplay_Create(&gUcObj,NULL);

    Chains_memPrintHeapStatus();

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);

    /* Fill the source buffers */
    fillSrcBuf(&gUcObj);

    chains_nullSrcDisplay_Start(&gUcObj);

    done = FALSE;
    while(!done)
    {
        Vps_printf(useCaseRunTimeMenu);
        ch = ChainsCommon_readChar();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
                chains_nullSrcDisplay_printStatistics(&gUcObj);
                ChainsCommon_PrintStatistics();
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n",
                            ch);
                break;
        }
    }

    chains_nullSrcDisplay_Stop(&gUcObj);
    chains_nullSrcDisplay_Delete(&gUcObj);

    ChainsCommon_StopDisplayCtrl();

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
    Vps_printf(" #### EXITING SAMPLE_APP:NULL SOURCE -> DISPLAY USE CASE ####");
}
