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
 *   \defgroup NETWORK_TX_LINK_API NetworkTx Link API
 *
 *   NetworkTx Link can be used to take input from a link and then sending it to
 *   network using TCP/UDP/TFDTP.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file networkTxLink.h
 *
 * \brief NetworkTx link API public header file.
 *
 * \version 0.0 (Dec 2017) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef NETWORK_TX_LINK_H_
#define NETWORK_TX_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/networkCtrl_if.h>
#include <include/link_api/system.h>
/* @{ */

/**

*******************************************************************************
 *
 * \brief Max output queues supported by NetworkTx Link
 *
 * SUPPORTED in ALL platforms
 *

*******************************************************************************
*/
#define NETWORK_TX_LINK_MAX_IN_QUE        (4U)

/* @} */

/**
 ******************************************************************************
 * \brief NetworkTx link data Copy types.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef enum {
    NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP = 0U,
    /**< For dumping buffer data, frames/bitstream/meta data over network */
    NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP = 1U,
    /**< For dumping buffer data, frames/bitstream/meta data over TFDTP */
    NETWORK_TX_LINK_TRANSMIT_TYPE_FORCE32BITS = 0x7FFFFFFFU
    /**< To make sure enum is 32 bits */
}NetworkTxLink_TransferType;

/******************************************************************************
 *
 *  Data structures
 *
*******************************************************************************
*/

/**
 ******************************************************************************
 * \brief NetworkTx link configuration parameters.
 *
 * SUPPORTED in ALL platforms
 *
*******************************************************************************
*/
typedef struct
{
    UInt32  numInQue;
    /**< Number of input queues */

    System_LinkInQueParams   inQueParams[NETWORK_TX_LINK_MAX_IN_QUE];
    /**< Input queue information */

    NetworkTxLink_TransferType  transmitDataType;
    /**< Transmit frames captured by networkTx link to network. */

    UInt32 networkServerPort;
    /**< Server port to use when dumpDataType is
     *   NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP
     */
    Void (*appCb)(System_LinkChInfo *pChInfo, Void *pBuf, Void *arg);
    /**< Application call back function which returns the full buffer */

    Void *appCbArg;
    /**< Application call back argument */

    Int32 retryCount;
    /**< Number of times to retry transmission. */

} NetworkTxLink_CreateParams;

/******************************************************************************
*  Functions Prototypes
*******************************************************************************
*/
static inline void NetworkTxLink_CreateParams_Init(NetworkTxLink_CreateParams *pPrm);

/******************************************************************************
*
*  Functions
*
*******************************************************************************
*/

/**
*******************************************************************************
 *
 * \brief NetworkTx link register and init
 *
 *    - Creates link task
 *    - Registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 NetworkTxLink_init(void);


/**
*******************************************************************************
 *
 * \brief NetworkTx link de-register and de-init
 *
 *    - Deletes link task
 *    - De-registers as a link with the system API
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 NetworkTxLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief NetworkTx link set default parameters for create time params
 *   This function does the following
 *      - memset create params object
 * \param  pPrm  [OUT]  NetworkTxLink Create time Params
 *
 *******************************************************************************
 */
static inline void NetworkTxLink_CreateParams_Init(NetworkTxLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(NetworkTxLink_CreateParams));

    pPrm->numInQue = 1U;
    pPrm->networkServerPort = NETWORK_TX_SERVER_PORT;
    pPrm->appCb = NULL;
    pPrm->appCbArg = NULL;

    return;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
