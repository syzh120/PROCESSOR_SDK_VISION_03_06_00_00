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
 * \file utils_l3_emif_bw.c
 *
 * \brief This file has the implementation of the APIs to config bandwdith
 *        related controls at L3 and EMIF
 *
 * \version 0.0 (Dec 2013) : [KC] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_l3_emif_bw.h>

#define DISPC_GLOBAL_MFLAG_ATTRIBUTE   ((volatile UInt32*)0x58010040U)
#define DISPC_GFX_MFLAG_THRESHOLD      ((volatile UInt32*)0x58011024U)
#define DISPC_VID1_MFLAG_THRESHOLD     ((volatile UInt32*)0x58017208U)
#define DISPC_VID2_MFLAG_THRESHOLD     ((volatile UInt32*)0x58018208U)

Int32 Utils_setDssMflagMode(Utils_DssMflagMode mode)
{
    *(DISPC_GLOBAL_MFLAG_ATTRIBUTE)
        =  (UInt32)(((UInt32)mode & (UInt32)0x3U) /* MFLAG_CTRL */
          |
           ((UInt32)1U << (UInt32)2U)) /* MFLAG_START
                     * 0x1: Even at the beginning of the frame when the DMA
                     *      buffer is empty, MFLAG_CTRL bitfield is used to
                     *      determine how MFLAG signal for each pipeline shall be
                     *      driven.
                     */
           ;
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_setDssMflagThreshold(System_DssDispcPipes displayPipeId,
                        UInt32 thresHigh,
                        UInt32 thresLow)
{
    UInt32 value;
    Int32 status=SYSTEM_LINK_STATUS_SOK;
    volatile UInt32 *pReg;

    value = (thresLow & (UInt32)0xFFFFU) | ((thresHigh & (UInt32)0xFFFFU) << (UInt32)16U);

    switch(displayPipeId)
    {
        case SYSTEM_DSS_DISPC_PIPE_VID1:
            pReg = DISPC_VID1_MFLAG_THRESHOLD;
            break;
        case SYSTEM_DSS_DISPC_PIPE_VID2:
            pReg = DISPC_VID2_MFLAG_THRESHOLD;
            break;
        case SYSTEM_DSS_DISPC_PIPE_GFX1:
            pReg = DISPC_GFX_MFLAG_THRESHOLD;
            break;
        default:
            status = SYSTEM_LINK_STATUS_EFAIL;
            break;
    }

    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        *pReg = value;
    }

    return status;
}

Int32 Utils_setDmmPri(Utils_DmmInitiatorId initiatorId, UInt32 priValue)
{
    Vps_printf(" UTILS: DMM: API NOT supported in TDA3xx !!! \n");
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_setDmmMflagEmergencyEnable(Bool enable)
{
    Vps_printf(" UTILS: DMM: API NOT supported in TDA3xx !!! \n");
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_setEmifPri(Utils_EmifInitiatorId initiatorId, UInt32 priValue)
{
    Vps_printf(" UTILS: EMIF: API NOT supported in TDA3xx !!! \n");
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_setBWLimiter(Utils_DmmInitiatorId initiatorId, UInt32 BW_valueInMBps)
{
    Vps_printf(" UTILS: SGX: API NOT supported in TDA3xx !!! \n");
    return SYSTEM_LINK_STATUS_SOK;
}
