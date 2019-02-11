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
 *   \defgroup MERGE_LINK_API Merge Link API
 *
 *
 *   Merge link is a connector link. What it does is taking input buffers from
 *   multiple input links and merge them to single output link. Release buffers
 *   to its previous links when the link connected to this merge link release
 *   the corresponding input buffers
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file mergeLink.h
 *
 * \brief Merge link API public header file.
 *
 * \version 0.0 (Aug 2013) : [SL] First version
 *
 *******************************************************************************
 */

#ifndef MERGE_LINK_H_
#define MERGE_LINK_H_

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
 * \brief Max input queues supported by Merge Link
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define MERGE_LINK_MAX_IN_QUE   (6U)

/* @} */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
*/


/**
 *******************************************************************************
 * \brief MERGE link configuration parameters.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 numInQue;
    /**< Number of inputs queue's */

    System_LinkInQueParams   inQueParams[MERGE_LINK_MAX_IN_QUE];
    /**< Input queue information */

    System_LinkOutQueParams   outQueParams;
    /**< Output queue information */

    UInt32  notifyNextLink;
    /**< TRUE: send command to next link notifying that new data is ready in que */

} MergeLink_CreateParams;

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */
static inline void MergeLink_CreateParams_Init(MergeLink_CreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
*******************************************************************************
*
* \brief Init function for MERGE link. This function does the following for
*   each MERGE link,
*  - Creates a task for the link
*  - Registers this link with the system
*
* \return  SYSTEM_LINK_STATUS_SOK
*
*******************************************************************************
*/
Int32 MergeLink_init(void);

/**
 *******************************************************************************
 *
 * \brief De-init function for MERGE link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 MergeLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Merge link set default parameters for create time params
 *   This function does the following
 *      - memset create params object
 *      - Sets notifyNextLink as TRUE
 * \param  pPrm  [OUT]  MergeLink Create time Params
 *
 *******************************************************************************
 */
static inline void MergeLink_CreateParams_Init(MergeLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(MergeLink_CreateParams));
    pPrm->notifyNextLink = (UInt32) TRUE;
    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
