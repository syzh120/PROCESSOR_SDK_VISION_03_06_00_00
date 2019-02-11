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
 * \file decLink_err.h Defines the Decode Link error types
 *
 * \brief  Defines the Decode Link error types
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _DEC_LINK_ERR_H_
#define _DEC_LINK_ERR_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/decLink.h>

/* =============================================================================
 * All success and failure codes for the Dec link module
 * ========================================================================== */

/** @brief Operation successful. */
#define DEC_LINK_S_SUCCESS                   (0)

/** @brief General Failure */
#define DEC_LINK_E_FAIL                      (-1)

/** @brief Argument passed to function is invalid. */
#define DEC_LINK_E_INVALIDARG                (-2)

/** @brief Decoder algorithm create failed */
#define DEC_LINK_E_ALGCREATEFAILED           (-3)

/** @brief RMAN assign resource failed */
#define DEC_LINK_E_RMANRSRCASSIGNFAILED      (-4)

/** @brief XDM_SETPARAM failed */
#define DEC_LINK_E_ALGSETPARAMSFAILED        (-5)

/** @brief Unknown codec type failed */
#define DEC_LINK_E_UNSUPPORTEDCODEC          (-6)

/** @brief Creation of task failed */
#define DEC_LINK_E_TSKCREATEFAILED           (-7)

/** @brief Invalid control cmd */
#define DEC_LINK_E_INVALIDCMD                (-8)

/** @brief Creationg of dup object failed */
#define DEC_LINK_E_DUPOBJ_CREATE_FAILED      (-9)

/** @brief Deletion of dup object failed */
#define DEC_LINK_E_DUPOBJ_DELETE_FAILED      (-10)

#endif


/* Nothing beyond this point */
