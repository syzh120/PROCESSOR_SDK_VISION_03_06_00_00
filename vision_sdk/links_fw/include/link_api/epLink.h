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
 * \ingroup SAMPLE_LINUX_MODULE_API
 * \defgroup EP_LINK_API Endpoint Link API for InfoADAS
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file epLink.h
 *
 * \brief Endpoint Link API
 *
 * \version 0.0 (May 2015) : [SM] First version
 *
 *******************************************************************************
 */

#ifndef _EP_LINK_H_
#define _EP_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/**
 *******************************************************************************
 *
 * \brief Endpoint Link specific defines
 *
 *******************************************************************************
 */
#define VIVI_MAX_NAME (100)

/**
 *******************************************************************************
 *
 * \brief Endpoint Link specific commands
 *
 *******************************************************************************
 */

/**
 * Meant for the source eplink
 * TODO define parameters
 */
#define EP_CMD_PUT_BUF              ((SYSTEM_LINK_ID_EP_0<<4) + 1)

/**
 * This is to create a thread specific handle for the buffer que
 *
 * \param struct ep_buf_que: to let the link know about the que name and the
 *                           function pointer to invoke for posting buffers into
 *                           the queue.
 *
 * \return SYSTEM_STATUS_SOK: on success
 */
#define EP_CMD_CREATE_QUE_HANDLE    ((SYSTEM_LINK_ID_EP_0<<4) + 2)

/**
 * Meant for the source eplink
 * TODO define parameters
 */
#define EP_CMD_CONFIG_SOURCE        ((SYSTEM_LINK_ID_EP_0<<4) + 3)

/**
 *******************************************************************************
 *
 * \brief Endpoint Link create parameters
 *
 *******************************************************************************
 */
typedef struct {
    System_LinkQueInfo  queInfo;
    /**< Input queue information provided by the vivi framework
     */
} EpLink_ConfigSource;

typedef struct {
    System_LinkInQueParams   inQueParams;
    /**< Input queue information
     */

    System_LinkOutQueParams  outQueParams;
    /**< Output queue information
     */

    UInt32 chainId;
    /**< Chain id, it belongs to
     */

    char plugName[VIVI_MAX_NAME];
    /**< Plugin it belongs to
     */

    UInt16 epType;
    /**< Type of endpoint - source or sink
     */

    EpLink_ConfigSource srcConfig;
    /**< Configuration required when acting as source
     */

} EpLink_CreateParams;

/**
 *******************************************************************************
 *
 *   \brief Endpoint link register and init function
 *
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 EpLink_init(void);
Int32 EpLink_deInit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
