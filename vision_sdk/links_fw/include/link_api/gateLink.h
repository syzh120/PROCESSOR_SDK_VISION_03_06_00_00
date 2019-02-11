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
 *   \defgroup GATE_LINK_API Gate Link API
 *
 *
 *   Gate link allows usecase writer to have runtime control on part of a data
 *   flow. It acts as a switch which can be turned on/off. Based on the state
 *   of the link it decides to either forward or return data.
 *
 *   This link can have many applications, some of them are as mentioned below
 *   1. Power Management - Selectively turn off and turn on cores based on their
 *      requirement for the usecase at run time.
 *   2. Boot time optimization - Usecase can be divided in to UcEarly and UcLate
 *      Basically UcEarly is created & started with gateLinks off, UcLate is
 *      created later in the course and then gateLinks can be switch on.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file gateLink.h
 *
 * \brief Gate link API public header file.
 *
 * \version 0.0 (Apr 2015) : [YM] First version
 *
 *******************************************************************************
 */

#ifndef GATE_LINK_H_
#define GATE_LINK_H_

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
 *   \brief Link CMD: Run time Command to get to switch operation mode to ON
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define GATE_LINK_CMD_SET_OPERATION_MODE_ON                       (0x8000U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Run time Command to get to switch operation mode to OFF
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define GATE_LINK_CMD_SET_OPERATION_MODE_OFF                      (0x8001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Run time Command to get to value of bufCount, application
 *                    essentially polls using this command before deleting
 *                    instance of previous or next link. When bufCount is zero
 *                    it is safe to delete the prev / next link instance
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define GATE_LINK_CMD_GET_BUFFER_FORWARD_COUNT                    (0x8002U)


/* @} */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
*/

/**
 *******************************************************************************
 * \brief GATE link configuration parameters.
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkInQueParams        inQueParams;
    /**< Input queue information */

    System_LinkOutQueParams       outQueParams;
    /**< output queue information */

    UInt32                        prevLinkIsCreated;
    /**< TRUE: no need to set 'prevLinkInfo'
        FALSE: user needs to set 'prevLinkInfo'
      */

    System_LinkInfo               prevLinkInfo;
    /**< Previous link info of the link which cab be instantiated later
         in the course of execution or can be existing at time of creation
         of the data flow */

} GateLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Init function for GATE link. This function does the following for each
 *   GATE link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 GateLink_init(void);

/**
 *******************************************************************************
 *
 * \brief De-init function for GATE link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 GateLink_deInit(void);


/**
 *******************************************************************************
 *
 * \brief Gate link set default parameters for create time params
 *
 * \param  pPrm  [OUT]  GateLink Create time Params
 *
 *******************************************************************************
 */
static inline void GateLink_CreateParams_Init(GateLink_CreateParams *pPrm);

static inline void GateLink_CreateParams_Init(GateLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(GateLink_CreateParams));

    pPrm->prevLinkIsCreated = (UInt32) TRUE;

    return;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/

