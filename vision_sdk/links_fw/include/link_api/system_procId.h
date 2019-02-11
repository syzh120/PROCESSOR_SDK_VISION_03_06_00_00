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
 *  \ingroup SYSTEM_LINK_API
 *  \defgroup SYSTEM_LINK_ID  System Link ID's
 *
 *  The unique 32-bit Link ID for the links present in the system are defined
 *  in this module
 *
 *  @{
*/

/**
 *******************************************************************************
 *
 *  \file system_procId.h
 *  \brief  System Proc ID's
 *
 *******************************************************************************
*/

#ifndef SYSTEM_PROC_ID_H_
#define SYSTEM_PROC_ID_H_

#ifdef __cplusplus
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
 * \brief IPU1 Core 0 Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_IPU1_0      (0U)

/**
 *******************************************************************************
 *
 * \brief IPU Core 1 Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_IPU1_1      (1U)

/**
 *******************************************************************************
 *
 * \brief MPU Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_A15_0       (2U)

/**
 *******************************************************************************
 *
 * \brief DSP Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_DSP1        (3U)
/**
 *******************************************************************************
 *
 * \brief DSP Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_DSP2        (4U)

/**
 *******************************************************************************
 *
 * \brief EVE Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_EVE1        (5U)

/**
 *******************************************************************************
 *
 * \brief EVE Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_EVE2        (6U)

/**
 *******************************************************************************
 *
 * \brief EVE Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_EVE3        (7U)

/**
 *******************************************************************************
 *
 * \brief EVE Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_EVE4        (8U)

/**
 *******************************************************************************
 *
 * \brief IPU Core 1 Proc ID
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_IPU2        (9U)

/**
 *******************************************************************************
 *
 * \brief Max supported processors
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_MAX         (10U)

/**
 *******************************************************************************
 *
 * \brief Invalid proc Id, if received indicates some corruption
 *
 *******************************************************************************
*/
#define SYSTEM_PROC_INVALID     (0xFFFFU)

/* @} */


#ifdef  __cplusplus
}
#endif

#endif

/*@}*/

