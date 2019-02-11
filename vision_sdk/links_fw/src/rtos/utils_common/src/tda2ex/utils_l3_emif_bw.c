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

#define DISPC_GLOBAL_MFLAG_ATTRIBUTE              (volatile UInt32*)(0x5800185C)
#define DISPC_GFX_MFLAG_THRESHOLD                 (volatile UInt32*)(0x58001860)
#define DISPC_VID1_MFLAG_THRESHOLD                (volatile UInt32*)(0x58001864)
#define DISPC_VID2_MFLAG_THRESHOLD                (volatile UInt32*)(0x58001868)
#define DISPC_VID3_MFLAG_THRESHOLD                (volatile UInt32*)(0x5800186C)

#define DMM_EMERGENCY                             (volatile UInt32*)(0x4E000020)
#define DMM_PEG_PRIO_0_ADDR                       (volatile UInt32*)(0x4E000620)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_ADDR  (volatile UInt32*)(0x4A002420)

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
        case SYSTEM_DSS_DISPC_PIPE_VID3:
            pReg = DISPC_VID3_MFLAG_THRESHOLD;
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
    volatile UInt32 *pPegPrioReg = DMM_PEG_PRIO_0_ADDR;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 index;
    UInt32 shift;

    index = initiatorId / (UInt32)8U;
    shift  = (initiatorId % (UInt32)8U) * (UInt32)4U;

    if(index < (UInt32)8U)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        priValue = (UInt32)0x8U | (priValue & (UInt32)0x7U);

        pPegPrioReg[index] = priValue << shift;

        Vps_printf(" DMM_PEG_PRIO_%d (0x%08x) = 0x%08x\n",
                index,
                &pPegPrioReg[index],
                pPegPrioReg[index]
            );
    }

    return status;
}

Int32 Utils_setDmmMflagEmergencyEnable(Bool enable)
{
    UInt32 value;

    value = *DMM_EMERGENCY;

    if(enable)
    {
        value |= (UInt32)0x1U;
    }
    else
    {
        value &= ~(UInt32)0x1U;
    }


    *DMM_EMERGENCY = value;

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 Utils_setEmifPri(Utils_EmifInitiatorId initiatorId, UInt32 priValue)
{
    volatile UInt32 *pEmifPrioReg = CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_ADDR;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 index;
    UInt32 shift;

    index = initiatorId / (UInt32)8U;
    shift  = (initiatorId % (UInt32)8U) * (UInt32)4U;

    if(index < (UInt32)7U)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {

        priValue = (priValue & (UInt32)0x7U);

        /* clear field */
        pEmifPrioReg[index] &= ~((UInt32)0x7U << shift);

        /* set field */
        pEmifPrioReg[index] |= (priValue << shift);

        Vps_printf(" CTRL_CORE_EMIF_INITIATOR_PRIORITY_%d (0x%08x) = 0x%08x\n",
                index + (UInt32)1U,
                &pEmifPrioReg[index],
                pEmifPrioReg[index]
            );
    }

    return status;
}

#define L3_BW_LIMITER_BANDWIDTH_FRACTIONAL_GPU_P1 (volatile UInt32*)(0x44805B08)
#define L3_BW_LIMITER_BANDWIDTH_INTEGER_GPU_P1    (volatile UInt32*)(0x44805B0C)
#define L3_BW_LIMITER_WATERMARK_0_GPU_P1          (volatile UInt32*)(0X44805B10)
#define L3_BW_LIMITER_CLEARHISTORY_GPU_P1         (volatile UInt32*)(0X44805B14)

#define L3_BW_LIMITER_BANDWIDTH_FRACTIONAL_GPU_P2 (volatile UInt32*)(0x44805C08)
#define L3_BW_LIMITER_BANDWIDTH_INTEGER_GPU_P2    (volatile UInt32*)(0x44805C0C)
#define L3_BW_LIMITER_WATERMARK_0_GPU_P2          (volatile UInt32*)(0X44805C10)
#define L3_BW_LIMITER_CLEARHISTORY_GPU_P2         (volatile UInt32*)(0X44805C14)

Int32 Utils_setBWLimiter(Utils_DmmInitiatorId initiatorId, UInt32 BW_valueInMBps)
{
   UInt32 BW;
   UInt32 BW_int;
   UInt32 BW_frac;

   BW = (UInt32) (BW_valueInMBps/(UInt32)8.3125);
   BW_int = (BW & (UInt32)0xFFFFFFE0U) >> (UInt32)5U;
   BW_frac = (BW & (UInt32)0x1FU);

   if (UTILS_DMM_INITIATOR_ID_GPU_P1 == initiatorId)
   {
       *L3_BW_LIMITER_BANDWIDTH_FRACTIONAL_GPU_P1 = BW_frac;
       *L3_BW_LIMITER_BANDWIDTH_INTEGER_GPU_P1 = BW_int;
       *L3_BW_LIMITER_WATERMARK_0_GPU_P1= (UInt32)0U;
       *L3_BW_LIMITER_CLEARHISTORY_GPU_P1 = (UInt32)1U;
   }

   if (UTILS_DMM_INITIATOR_ID_GPU_P2 == initiatorId)
   {
       *L3_BW_LIMITER_BANDWIDTH_FRACTIONAL_GPU_P2 = BW_frac;
       *L3_BW_LIMITER_BANDWIDTH_INTEGER_GPU_P2 = BW_int;
       *L3_BW_LIMITER_WATERMARK_0_GPU_P2 = (UInt32)0U;
       *L3_BW_LIMITER_CLEARHISTORY_GPU_P2 = (UInt32)1U;
   }

    return SYSTEM_LINK_STATUS_SOK;
}

#define L3_BW_REGULATOR_BANDWIDTH_IVA             (volatile UInt32*)(0x44805008)
#define L3_BW_REGULATOR_WATERMARK_IVA             (volatile UInt32*)(0x4480500C)
#define L3_BW_REGULATOR_CLEARHISTORY_IVA          (volatile UInt32*)(0x44805014)

Int32 Utils_setBWRegulator(Utils_DmmInitiatorId initiatorId, UInt32 BW_valueInMBps)
{
   UInt32 BW, WM;

   BW = (UInt32) (BW_valueInMBps/(UInt32)8.3125);
   WM = (UInt32) (BW_valueInMBps * (UInt32)1); /* 1 MicroSec window */

   if (UTILS_DMM_INITIATOR_ID_IVA == initiatorId)
   {
       *L3_BW_REGULATOR_BANDWIDTH_IVA = BW;
       *L3_BW_REGULATOR_WATERMARK_IVA = WM;
       *L3_BW_REGULATOR_CLEARHISTORY_IVA = (UInt32)1U;
   }

    return SYSTEM_LINK_STATUS_SOK;
}

