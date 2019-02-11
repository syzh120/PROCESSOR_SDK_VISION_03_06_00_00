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
#include "chains_saveDisFrame_priv.h"
#include <src/include/chains_common.h>
#include <src/include/chains_common_surround_view.h>
#include <src/include/chains_common_osal.h>

/*******************************************************************************
 *  STRUCTURES
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  chains_saveDisFrameAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct csc_fields{
    int index;
    int numBits;
    int bitShift;
    int val;    
}csc_fields;

void config_wb_csc()
{
    unsigned int * ptr;
    unsigned int tmp32, regVal, k, idx;
    csc_fields wb_csc[]={
       /*index  numBits  bitShift  val                                                 address */
        {0,       11,        0,   77}, // R->Y         DISPC_WB_CONV_COEF0    [10: 0]    0x58015040    
        {0,       11,       16,  150}, // G->Y         DISPC_WB_CONV_COEF0    [26:16]    0x58015040    
        {1,       11,        0,  29 }, // B->Y         DISPC_WB_CONV_COEF1    [10: 0]    0x58015044    
        {1,       11,       16,  128}, // R->Cr        DISPC_WB_CONV_COEF1    [26:16]    0x58015044    
        {2,       11,        0, -107}, // G->Cr        DISPC_WB_CONV_COEF2    [10: 0]    0x58015048    
        {2,       11,       16,  -21}, // B->Cr        DISPC_WB_CONV_COEF2    [26:16]    0x58015048    
        {3,       11,        0,  -43}, // R->Cb        DISPC_WB_CONV_COEF3    [10: 0]    0x5801504c    
        {3,       11,       16,  -85}, // G->Cb        DISPC_WB_CONV_COEF3    [26:16]    0x5801504c    
        {4,       11,        0,  128}, // B->Cb        DISPC_WB_CONV_COEF4    [10: 0]    0x58015050    
        {5,       13,        3,    0}, // Y offset     DISPC_WB_CONV_COEF5    [15: 3]    0x58015054
        {5,       13,       19, 2048}, // Cb offset    DISPC_WB_CONV_COEF5    [31:19]    0x58015054
        {6,       13,        3, 2048}, // Cr offset    DISPC_WB_CONV_COEF6    [15: 3]    0x58015058        
    };
    k = 0;
    ptr = (unsigned int *)0x58015040;
    for( idx = 0; idx <= 6 ; idx++ )
    {
        regVal = 0;
        while( (wb_csc[k].index == idx) && (k <  sizeof(wb_csc)/sizeof(csc_fields)) )
        {
            tmp32 = (unsigned int)(wb_csc[k].val&(0xffffffff>>(32-wb_csc[k].numBits)));
            tmp32 <<= wb_csc[k].bitShift;
            regVal |= tmp32;
            k++;
        }
        ptr[idx] = regVal;
        if( k == sizeof(wb_csc)/sizeof(csc_fields) )
        {
            break;
        }
    }
}  
typedef struct {

    chains_saveDisFrameObj ucObj;
    Int32 fp;

    UInt32 displayWidth;
    UInt32 displayHeight;

    /* Display write back */
    BspOsal_SemHandle disWbSync;
    Bool disWbFrame;

} chains_saveDisFrameAppObj;

/*******************************************************************************
 *  GLOBALS
 *******************************************************************************
 */
chains_saveDisFrameAppObj gSaveDisFrameAppObj;

/**
 *******************************************************************************
 *
 * \brief   Display write back frame call back
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
static Void disWbFrameCb(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg)
{
    System_Buffer *pFrameBuf = (System_Buffer*)pBuf;
    System_VideoFrameBuffer *pVidFrame = \
                                (System_VideoFrameBuffer*)pFrameBuf->payload;
    chains_saveDisFrameAppObj *pObj = (chains_saveDisFrameAppObj*)arg;

    if (TRUE == pObj->disWbFrame)
    {
        pObj->disWbFrame = FALSE;

        Vps_printf(" SAVE_DIS_FRAME: Writing Display frame to file ...\n");

        /* Dump Y plane */
        ChainsCommon_Osal_fileWrite(
                        pObj->fp,
                        (UInt8*)pVidFrame->bufAddr[0],
                        pObj->displayWidth * pObj->displayHeight);

        /* Dump UV plane */
        ChainsCommon_Osal_fileWrite(
                        pObj->fp,
                        (UInt8*)pVidFrame->bufAddr[1],
                        (pObj->displayWidth * pObj->displayHeight) >> 1);

        Vps_printf(" SAVE_DIS_FRAME: Writing Display frame to file DONE\n");

        BspOsal_semPost(pObj->disWbSync);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Set Save Display Frame Use case Link Parameters
 *
 *          It is called in Create function.
 *          In this function SwMs alg link params are set
 *          The algorithm which is to run on core is set to
 *          baseClassCreate.algId. The input whdth and height to alg are set.
 *          Number of input buffers required by alg are also set here.
 *
 *******************************************************************************
*/
Void chains_saveDisFrame_SetAppPrms(
                                chains_saveDisFrameObj *pUcObj, Void *appObj)
{
    chains_saveDisFrameAppObj *pObj = (chains_saveDisFrameAppObj*)appObj;

    /* Capture DSS WB params */
    pUcObj->Capture_dsswbPrm.numVipInst = 0;
    pUcObj->Capture_dsswbPrm.numDssWbInst = 1;

    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInstId = VPS_CAPT_INST_DSS_WB1;
    System_VideoScanFormat scanFormat = SYSTEM_SF_PROGRESSIVE;

    if (Bsp_platformIsTda3xxFamilyBuild())
    {
        pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.inNode = \
                                                        SYSTEM_WB_IN_NODE_LCD1;
    }
    else
    {
        pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.inNode = \
                                                        SYSTEM_WB_IN_NODE_TV;
    }
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbInSourceWidth = \
                                                            pObj->displayWidth;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbInSourceHeight = \
                                                            pObj->displayHeight;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbInWidth = \
                                                            pObj->displayWidth;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbInHeight = \
                                                            pObj->displayHeight;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbPosx = 0;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbPosy = 0;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbInSourceDataFmt = \
                                                            SYSTEM_DF_BGR24_888;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbInputPrms.wbScanFormat = \
                                                                    scanFormat;

    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbOutputPrms.wbWidth = \
                                                            pObj->displayWidth;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbOutputPrms.wbHeight = \
                                                            pObj->displayHeight;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbOutputPrms.wbDataFmt = \
                                                        SYSTEM_DF_YUV420SP_UV;
    pUcObj->Capture_dsswbPrm.dssWbInst[0].dssWbOutputPrms.wbScanFormat = \
                                                                scanFormat;

    pUcObj->Capture_dsswbPrm.dssWbInst[0].numBufs = 4U;

    /* Null Params */
    pUcObj->Null_disWbPrm.appCb = disWbFrameCb;
    pUcObj->Null_disWbPrm.appCbArg = pObj;

    pUcObj->Capture_dsswbLinkID = SYSTEM_LINK_ID_CAPTURE_1;
    pUcObj->Null_disWbLinkID = IPU1_0_LINK (SYSTEM_LINK_ID_NULL_1);
}

/**
 *******************************************************************************
 *
 * \brief   Save Display Frame API
 *
 *          This function configure, creates, link various links to establish
 *          usecase.
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
Void chains_saveDisFrame(
                    char *fileName,
                    UInt32 numSaveFrames,
                    UInt32 displayWidth,
                    UInt32 displayHeight)
{
    UInt32 cnt;
    chains_saveDisFrameAppObj *pObj = \
                            (chains_saveDisFrameAppObj*)&gSaveDisFrameAppObj;
    chains_saveDisFrameObj *pUcObj = &pObj->ucObj;

    pObj->fp = ChainsCommon_Osal_fileOpen(fileName, \
                                        CHAINSCOMMON_OSAL_FILEMODE_WRITE_BIN);
    if (0 <= pObj->fp)
    {
        pObj->displayWidth = displayWidth;
        pObj->displayHeight = displayHeight;
        pObj->disWbFrame = FALSE;

        pObj->disWbSync = BspOsal_semCreate(0, (Bool) TRUE);
        UTILS_assert(NULL != pObj->disWbSync);

        /* Create Use Case */
        chains_saveDisFrame_Create(pUcObj, pObj);
        config_wb_csc();
        chains_saveDisFrame_Start(pUcObj);

        for (cnt = 0U;cnt < numSaveFrames;cnt ++)
        {
            pObj->disWbFrame = TRUE;
            BspOsal_semWait(pObj->disWbSync, BSP_OSAL_WAIT_FOREVER);
        }

        /* Delete Use Case */
        chains_saveDisFrame_Stop(pUcObj);
        chains_saveDisFrame_Delete(pUcObj);

        BspOsal_semDelete(&pObj->disWbSync);

        ChainsCommon_Osal_fileClose(pObj->fp);
    }
}
