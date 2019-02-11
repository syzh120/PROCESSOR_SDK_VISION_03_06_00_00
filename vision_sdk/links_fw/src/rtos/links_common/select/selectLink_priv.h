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
 * \ingroup SELECT_LINK_API
 * \defgroup SELECT_LINK_IMPL Select Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file selectLink_priv.h Select Link private API/Data structures
 *
 * \brief  This file is a private header file for Select link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of Select link.
 *         Select Link is used in cases where the input buffers are selectively
 *         sent to next links.
 *
 * \version 0.0 (Nov 2013) : [CM] First version
 *
 *******************************************************************************
 */

#ifndef SELECT_LINK_PRIV_H_
#define SELECT_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/selectLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Maximum number of SELECT link objects
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SELECT_LINK_OBJ_MAX    (6U)

/**
 *******************************************************************************
 *
 * \brief Select Link channels not mapped
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SELECT_LINK_CH_NOT_MAPPED   (0xFFFFU)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief
 *
 *  Channel link info to hold the information of the perticular channel
 *
 *
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 queId;
    /**< Holds the queue Id of the channel */

    UInt32 outChNum;
    /**< Channel number of the output channel */

    Bool   rtChInfoUpdate;
    /**< Flag to indicate if the channel info has updated */

    System_LinkChInfo rtChInfo;
    /**< Link Channel Info */
} SelectLink_ChInfo;

/**
 *******************************************************************************
 *
 * \brief
 *
 * Structure to hold all Select link related information
 *
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 tskId;
    /**< Placeholder to store select link task id */

    char name[32];
    /**< Link name */

    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */

    Utils_TskHndl tsk;
    /**< Handle to select link task */

    SelectLink_CreateParams createArgs;
    /**< Create params for select link */

    System_LinkInfo inTskInfo;
    /**< Output queue information of previous link */

    System_LinkInfo info;
    /**< Output queue information of this link */

    Utils_BufHndl outFrameQue[SELECT_LINK_MAX_OUT_QUE];
    /**< Handles to the output queue */

    SelectLink_ChInfo   inChInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Input Channel info */

    SelectLink_OutQueChInfo   prevOutQueChInfo[SELECT_LINK_MAX_OUT_QUE];
    /**< Previous Channel Queue Info*/

    Utils_LinkStatistics linkStats;
    /**< Statistics related to this link */

    UInt32 getFrameCount;
    /**< Count of incoming frames */

    UInt32 putFrameCount;
    /**< Count of outgoing frames */

} SelectLink_Obj;


extern SelectLink_Obj gSelectLink_obj[SELECT_LINK_OBJ_MAX];

Void SelectLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);
Int32 SelectLink_tskCreate(UInt32 instId);
Int32 SelectLink_drvSetOutQueChInfo(SelectLink_Obj * pObj, const SelectLink_OutQueChInfo *pPrm);
Int32 SelectLink_drvGetOutQueChInfo(SelectLink_Obj * pObj, SelectLink_OutQueChInfo *pPrm);
Int32 SelectLink_drvCreate(SelectLink_Obj * pObj, const SelectLink_CreateParams * pPrm);
Int32 SelectLink_drvProcessData(SelectLink_Obj * pObj);
Int32 SelectLink_getFullBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 SelectLink_getLinkInfo(Void * ptr, System_LinkInfo * info);
Int32 SelectLink_putEmptyBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 SelectLink_drvDelete(SelectLink_Obj * pObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


