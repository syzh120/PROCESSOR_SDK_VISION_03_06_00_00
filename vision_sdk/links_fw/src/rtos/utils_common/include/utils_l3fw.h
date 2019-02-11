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
 * \ingroup UTILS_API
 * \defgroup UTILS_L3FW_API L3 Firewall related utilities
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_l3fw.h
 *
 * \brief  This file has the interface for utility functions for using
 *         firewalls on TDA2x and TDA3x
 *
 * \version 0.0 (Dec 2015) : [CSG] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_L3FW_H
#define UTILS_L3FW_H

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*
 * \brief Setup L3FW and register error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_l3FwSetup(void);

/*
 * \brief Reset all L3FW configuration and de-register error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_l3FwReset(void);

/*
 * \brief  Switch background region to READ-ONLY or READ-WRITE for EVE
 *
 * \param  safetyMode - BSP_SAFETY_OSAL_MODE_ASIL/BSP_SAFETY_OSAL_MODE_QM
 *
 * \return None
 */
void Utils_l3FwSwitchSafetyMode(UInt32 safetyMode);

#ifdef BUILD_ARP32
/* Interface to identify current safetyMode in EVE.
 */
UInt32 Utils_l3FwGetSafetyMode(Void);
#endif

#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
/* Interface to provide DSP1/DSP2/EVE1 data section size in
 * to allow FFI between EDMA and CPU
 */
void Utils_l3FwSetDsp1DataSectInfo(UInt32 addr, UInt32 size);
#ifndef TDA2EX_BUILD
void Utils_l3FwSetDsp2DataSectInfo(UInt32 addr, UInt32 size);
void Utils_l3FwSetEve1DataSectInfo(UInt32 addr, UInt32 size);
#endif
void Utils_l3FwSetLinkStatSectInfo(UInt32 addr, UInt32 size);
#endif


#ifdef __cplusplus
}
#endif

#endif

/* @} */
