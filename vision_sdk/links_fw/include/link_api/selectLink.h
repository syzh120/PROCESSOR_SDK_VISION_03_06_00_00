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
 *   \ingroup FRAMEWORK_MODULE_API
 *   \defgroup SELECT_LINK_API Select Link API
 *
 *
 *   SELECT Link can be used to select expected channel(s) data
 *   from input channels.It takes input buffers and selectively passes to the
 *   next link.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file selectLink.h
 *
 * \brief Select link API public header file.
 *
 * \version 0.0 (Nov 2013) : [CM] First version
 *
 *******************************************************************************
 */


#ifndef SELECT_LINK_H_
#define SELECT_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /* @{ */

/**
 *******************************************************************************
 *
 * \brief Max output queues to which a given SELECT link can connect
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define SELECT_LINK_MAX_OUT_QUE     (4U)

/* @} */

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup SELECT_LINK_API_CMD Select Link Control Commands
 *
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Link CMD: SELECT_LINK_CMD_SET_OUT_QUE_CH_INFO
 *
 *  Sets Information about which channels from input to be set at the output
 *
 * \param SelectLink_drvSetOutQueChInfo
 *
 *******************************************************************************
*/
#define SELECT_LINK_CMD_SET_OUT_QUE_CH_INFO         (0xB000U)

/**
 *******************************************************************************
 *
 * \brief Link CMD: SELECT_LINK_CMD_GET_OUT_QUE_CH_INFO
 *
 * Information about which channels from input are selected at the output
 *
 * \param SelectLink_drvGetOutQueChInfo
 *
 *******************************************************************************
*/
#define SELECT_LINK_CMD_GET_OUT_QUE_CH_INFO         (0xB001U)

/* @} */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 *  \brief SELECT_LINK_CMD_GET_OUT_QUE_CH_INFO command params
 *  Information about which channels from input are selected at the output
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
/**

*/
typedef struct
{
    UInt32 outQueId;
    /**< Que ID for which this is applicable
            - IGNORED when used with SelectLink_CreateParams */
    UInt32 numOutCh;
    /**< number of output channels in this output queue */

    UInt32 inChNum[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< input channel number which maps to this output queue */

} SelectLink_OutQueChInfo;

/**
 *******************************************************************************
 * \brief Select link configuration parameters.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 numOutQue;
    /**< Number of outPutQue queue's */

    System_LinkInQueParams     inQueParams;
    /**< Input queue information. */

    System_LinkOutQueParams   outQueParams[SELECT_LINK_MAX_OUT_QUE];
    /**< Output queue information */

    SelectLink_OutQueChInfo   outQueChInfo[SELECT_LINK_MAX_OUT_QUE];
    /**< Information about which channels from input are selected at the output */

    UInt32  notifyNextLink;
    /**< TRUE: send command to next link notifying that new data is ready in que
      *  Misra C: Cant be kept as Bool as this is interface file and can cause
      *           issue with different compiler if kept as Bool
      */

} SelectLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
*******************************************************************************
*
* \brief Init function for SELECT link. This function does the following for
*   each SELECT link,
*  - Creates a task for the link
*  - Registers this link with the system
*
* \return  SYSTEM_LINK_STATUS_SOK
*
*******************************************************************************
*/
Int32 SelectLink_init(void);

/**
 *******************************************************************************
 *
 * \brief De-init function for SELECT link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 SelectLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Select link set default parameters for create time params
 *   This function does the following
 *      - memset create params object
 *      - Sets notifyNextLink as TRUE
 * \param  pPrm  [OUT]  Select Link Create time Params
 *
 *******************************************************************************
 */
static inline void SelectLink_CreateParams_Init(SelectLink_CreateParams *pPrm);

static inline void SelectLink_CreateParams_Init(SelectLink_CreateParams *pPrm)
{
    UInt32 queId;

    memset((Ptr)pPrm, 0, sizeof(SelectLink_CreateParams));

    pPrm->notifyNextLink = (UInt32)TRUE;

    /* Init Out Queue ID in order as this is the most likely way of using */
    for (queId = 0U; queId < SELECT_LINK_MAX_OUT_QUE; queId++)
    {
        pPrm->outQueChInfo[queId].outQueId = queId;
    }
    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
