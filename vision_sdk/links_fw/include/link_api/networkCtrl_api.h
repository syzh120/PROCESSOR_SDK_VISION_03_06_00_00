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
 *   \ingroup SAMPLE_MODULE_API
 *   \defgroup NETWORK_CTRL_API Network Control API
 *
 *   This API is used to enable receiving of commands from a PC based network
 *   controller application.
 *
 *   When command are received a user registered callback gets called to
 *   take action on the command.
 *
 *   The callback can read parameters for the command and send a reply
 *   (with parameters) to  the PC application
 *
 *   NOTE: This is NOT a link, NetworkCtrl_init() when called creates
 *         a thread which opens a TCP/IP socket on a predetermined port
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file networkCtrl_api.h
 *
 * \brief Network Control API
 *
 *******************************************************************************
 */


#ifndef NETWORK_CTRL_API_H_
#define NETWORK_CTRL_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <include/link_api/networkCtrl_if.h>
#include <include/link_api/system.h>

/*******************************************************************************
 *  Typedef's
 *******************************************************************************
 */

/*******************************************************************************
 *  \brief Function callback to handle command received over network
 *
 *         The Network command handler should call
 *         NetworkCtrl_readParams() to read parameters into user supplied buffer
 *         if prmSize > 0
 *
 *         The Network command handler should call
 *         NetworkCtrl_writeParams() to send ACK and parameters, if any,
 *         to the sender.
 *
 *         If there are no return parameters, if should still call
 *         NetworkCtrl_writeParams(NULL, 0, 0) to send ACK to the sender
 *
 *  \param cmd  [IN] The command that is received
 *  \param prmSize [IN] Size of the parameters for the received command
 *
 *******************************************************************************
 */
typedef Void (*NetworkCtrl_Handler)(char *cmd, UInt32 prmSize);

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

/*******************************************************************************
 *  \brief Create a thread to handle command received over network
 *
 *******************************************************************************
 */
Int32 NetworkCtrl_init(void);

/*******************************************************************************
 *  \brief Delete the thread used for handling network commands
 *
 *******************************************************************************
 */
Int32 NetworkCtrl_deInit(void);

/*******************************************************************************
 *  \brief Register a handler that gets called when the specified command
 *         is received
 *
 *         If handler is already registered on this command then error is
 *         returned
 *
 *  \param cmd  [IN] Command, specified as string of max size NETWORK_CTRL_CMD_STRLEN_MAX
 *  \param handler [IN] Handler that is invoked when a command is received
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkCtrl_registerHandler(char *cmd, NetworkCtrl_Handler handler);

/*******************************************************************************
 *  \brief UnRegister a handler for the specified command
 *
 *  \param cmd  [IN] Command, specified as string of max size NETWORK_CTRL_CMD_STRLEN_MAX
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkCtrl_unregisterHandler(char *cmd);

/*******************************************************************************
 *  \brief Read parameters for the current command that is received
 *
 *  \param pPrm [IN] User buffer into which the parameters will be read
 *  \param prmSize [IN] Size of parameters to read
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkCtrl_readParams(UInt8 *pPrm, UInt32 prmSize);

/*******************************************************************************
 *  \brief Writes parameters for the current command that is received
 *         and also send ACK to the sender
 *
 *  \param pPrm [IN] User buffer from which parameters will be sent
 *  \param prmSize [IN] Size of parameters to write
 *  \param returnStatus [IN] Return status to send to the sender
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 NetworkCtrl_writeParams(UInt8 *pPrm, UInt32 prmSize, UInt32 returnStatus);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


