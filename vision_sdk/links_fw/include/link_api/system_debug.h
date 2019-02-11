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
 *  \ingroup SYSTEM_LINK_API
 *  \defgroup SYSTEM_DEBUG_API System Debug Const's
 *
 *  Modify this file to enable/disable prints from different links.
 *
 *  When SYSTEM_DEBUG_xxx_RT  is enabled a print is done for every frame.
 *  In real-time systems such prints may slow down the system and hence
 *  are intended to used only for debug purposes.
 *
 *  @{
*/

/**
 *******************************************************************************
 *
 *  \file system_debug.h
 *  \brief System Debug Const's
 *
 *******************************************************************************
*/

#ifndef SYSTEM_DEBUG_H_
#define SYSTEM_DEBUG_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of the system
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of the AVB link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_AVBTP

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of the TFDTP receive link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_TFDTP

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of the Null link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_NULL

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of the Null source link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_NULLSRC

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of the capture link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_CAPTURE

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of VPE link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_VPE

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of ISS M2M link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_ISSM2M

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of display link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_DISPLAY

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of DUP link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_DUP

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of SW Mosaic link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_SWMS
/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of IPC link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_IPC

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of merge link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_MERGE

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug encoder link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_ENC

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of decoder link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_DEC

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of select link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_SELECT

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of Algorithm link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_ALGORITHM

/**
 *******************************************************************************
 *
 * \brief Enable real time debug of links
 *
 *******************************************************************************
 */
#define SYSTEM_RT_STATS_LOG_INTERVAL        (10)

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of BSP and STW driver
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_BSPSTW

/**
 *******************************************************************************
 *
 *   \brief Define to enable debug of DSSM2MWB link
 *
 *******************************************************************************
*/
#define SYSTEM_DEBUG_DSSM2MWB

/**
 *******************************************************************************
 *
 *  \brief Enable real time logs of links at various processing time instances
 *   like input dequeuing, processing, output queueing etc
 *
 *******************************************************************************
*/
#ifdef SYSTEM_DEBUG_RT
    #define SYSTEM_DEBUG_CAPTURE_RT
    #define SYSTEM_DEBUG_VPE_RT
    #define SYSTEM_DEBUG_DISPLAY_RT
    #define SYSTEM_DEBUG_SWMS_RT
    #define SYSTEM_DEBUG_IPC_RT
    #define SYSTEM_DEBUG_ENC_RT
    #define SYSTEM_DEBUG_DEC_RT
    #define SYSTEM_DEBUG_NULLSRC_RT
    #define SYSTEM_DEBUG_NULL_RT
#endif

/*@}*/

#ifdef  __cplusplus
}
#endif

#endif /* SYSTEM_DEBUG_H_ */

/* @} */

