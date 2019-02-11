/******************************************************************************
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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/common/chains_radar.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include <src/include/link_stats_monitor.h>

/**
 *******************************************************************************
 *
 * \brief   Do common system init
 *
 *******************************************************************************
*/
Void ChainsCommon_Init()
{

    Board_init();
    #if defined(FATFS_PROC_TO_USE_IPU1_0)
    File_init();
    #endif

#ifdef ENABLE_UART_LOG
    System_uartInit();

    /* let the pending prints from other processor's finish */
    if(!System_isFastBootEnabled() &&
       !System_isSrvFastBootEnabled())
    {
        Task_sleep(1000);
    }
#endif
    Utils_prcmClockRateInit();
    Utils_prcmPrintPowerConsumptionInit();

    System_qspiInit();

    GrpxSrcLink_init();
    ChainsCommon_SetSystemL3DmmPri();
    Utils_statCollectorInit(); /* Initializing the statCollector */
    Chains_linkStatsMonitorInit();
}

/**
 *******************************************************************************
 *
 * \brief   Do common system init
 *
 *******************************************************************************
*/
Void ChainsCommon_DeInit()
{
    GrpxSrcLink_deInit();

    #if defined(FATFS_PROC_TO_USE_IPU1_0)
    File_deInit();
    #endif
    Board_deInit();

    Utils_statCollectorDeInit();
    Chains_linkStatsMonitorDeInit();
}

Void ChainsCommon_InitCaptureDevice(Chains_CaptureSrc captureSrc)
{
    return;
}

/**
 *******************************************************************************
 *
 * \brief   Configure and start single channel capture device
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StartCaptureDevice(Chains_CaptureSrc captureSrc,
                        UInt32 captureOutWidth,
                        UInt32 captureOutHeight
                        )
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    return status;
}


/**
 *******************************************************************************
 *
 * \brief   Stop capture device
 *
 *******************************************************************************
*/
Int32 ChainsCommon_StopCaptureDevice(Chains_CaptureSrc captureSrc)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    return status;
}

