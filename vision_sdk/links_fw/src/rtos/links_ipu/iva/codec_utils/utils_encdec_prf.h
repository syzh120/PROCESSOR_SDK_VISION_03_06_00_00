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
 * \file utils_encdec_prf.h
 *
 * \brief  HDVICP frofile functions are defined
 *
 * \version 0.0 (Jan 2014) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef _UTILS_ENCDEC_PRF_H_
#define _UTILS_ENCDEC_PRF_H_

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <string.h>
#include <xdc/std.h>
#include <xdc/runtime/Timestamp.h>
#include <include/link_api/system_trace.h>

/*******************************************************************************
 *  \brief Flag to enable/disable HDVICP profiling option
 *******************************************************************************
 */
#if 1
#define UTILS_ENCDEC_HDVICP_PROFILE
#endif

/*******************************************************************************
 *  \brief Max number of HDVICP resources available in the decvice
 *******************************************************************************
 */
#define UTILS_ENCDEC_MAXNUMOFHDVICP2_RESOUCES                               (1)
/*
 *          DES_ID: DOX_DES_TAG(DES_VideoDecoder_004)
 *          REQ_ID: DOX_REQ_TAG(ADASVISION-1339)
*/
typedef struct HDVICP_logTbl {
    UInt32 totalAcquire2wait;
    UInt32 totalWait2Isr;
    UInt32 totalIsr2Done;
    UInt32 totalWait2Done;
    UInt32 totalDone2Release;
    UInt32 totalAcquire2Release;
    UInt32 totalAcq2acqDelay;
    UInt32 tempPrevTime;
    UInt32 tempAcquireTime;
    UInt32 tempWaitTime;
    UInt32 startTime;
    UInt32 endTime;
    UInt32 numAccessCnt;
    UInt32 totalIVAHDActivateTime;
} HDVICP_logTbl;

extern HDVICP_logTbl g_HDVICP_logTbl[UTILS_ENCDEC_MAXNUMOFHDVICP2_RESOUCES];


static inline UInt32 Utils_encdecGetTime(Void)
{
    return (Utils_getCurGlobalTimeInMsec());
}

static Void Utils_encdecHdvicpPrfInit(Void)
{
    memset(&g_HDVICP_logTbl, 0, sizeof(g_HDVICP_logTbl));
    return;
}

static Void Utils_encdecHdvicpPrfPrint(void)
{
#ifndef IPUMM_INCLUDE
    int ivaId;
    UInt32 totalElapsedTime = 0, perCentTotalWait2Isr = 0;
#endif

#ifdef UTILS_ENCDEC_HDVICP_PROFILE
    for (ivaId = 0; ivaId < UTILS_ENCDEC_MAXNUMOFHDVICP2_RESOUCES; ivaId++)
    {

        Vps_printf(" HDVICP-ID: %d\n", ivaId);

        totalElapsedTime = (g_HDVICP_logTbl[ivaId].endTime -
                            g_HDVICP_logTbl[ivaId].startTime);
        if(totalElapsedTime)
        {
            perCentTotalWait2Isr = (g_HDVICP_logTbl[ivaId].totalWait2Isr * 100) /
                                    totalElapsedTime;
            Vps_printf ("All percentage figures are based of totalElapsedTime\n");
            Vps_printf("\n\t\t totalAcquire2Wait :%d %%"
                       "\n\t\t totalWait2Isr :%d %%"
                       "\n\t\t totalIsr2Done :%d %%"
                       "\n\t\t totalWait2Done :%d %%"
                       "\n\t\t totalDone2Release :%d %%"
                       "\n\t\t totalAcquire2Release :%d %%"
                       "\n\t\t totalRelease2AcquireDelay :%d %%"
                       "\n\t\t totalElapsedTime in msec :%8d"
                       "\n\t\t numAccessCnt:%8d\n",
                       (g_HDVICP_logTbl[ivaId].totalAcquire2wait * 100) / totalElapsedTime ,
                       (g_HDVICP_logTbl[ivaId].totalWait2Isr * 100) / totalElapsedTime,
                       (g_HDVICP_logTbl[ivaId].totalIsr2Done * 100) / totalElapsedTime,
                       (g_HDVICP_logTbl[ivaId].totalWait2Done * 100) / totalElapsedTime,
                       (g_HDVICP_logTbl[ivaId].totalDone2Release * 100) / totalElapsedTime,
                       (g_HDVICP_logTbl[ivaId].totalAcquire2Release * 100 ) / totalElapsedTime,
                       (g_HDVICP_logTbl[ivaId].totalAcq2acqDelay * 100) / totalElapsedTime,
                       totalElapsedTime, g_HDVICP_logTbl[ivaId].numAccessCnt
                       );

            Vps_printf(" IVA-FPS :%8d\n",
                   ((g_HDVICP_logTbl[ivaId].numAccessCnt) /
                    (totalElapsedTime/1000)));

        }

        if(g_HDVICP_logTbl[ivaId].numAccessCnt)
        {
            Vps_printf(" Average time spent per frame in microsec:%8d\n",
                   ((totalElapsedTime * 1000/ g_HDVICP_logTbl[ivaId].numAccessCnt) * perCentTotalWait2Isr)/ 100);
        }
        Vps_printf(" \n");
    }
#endif
    return;
}

#endif

/* Nothing beyond this point */


