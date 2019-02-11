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
******************************************************************************/

/**
 *******************************************************************************
 * \file chains_main_robust_rvc.c
 *
 * \brief  APIs for selecting the Robust RVC usecase chain.
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/include/chains.h>
#include <src/include/chains_common.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>
#include <src/include/link_stats_monitor.h>
#include <src/rtos/alg_plugins/rvcDiags/rvcDiagnostic_algLink_priv.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

Chains_Ctrl gChains_usecaseCfg;

/**
 *******************************************************************************
 *
 * \brief   Function to handle RVC startup diagnostic where certain registers
 *          can be checked against the default reference before starting.
 *          When discrepancies detected, perform auto update with the default
 *          reference.
 *
 *******************************************************************************
*/
int RVC_StartupDiagnostics()
{
    unsigned int StartRegFieldValue[MAX_S_DIAG_REGFIELDS];
    unsigned int i;

    Vps_printf("\n Performing RVC_StartupDiagnostics \n");

    for (i=0;i<MAX_S_DIAG_REGFIELDS;i++)
    {
        StartRegFieldValue[i] =
            HW_RD_FIELD32_RAW(startupDiagnosticsRegField[i].base+startupDiagnosticsRegField[i].offset, \
            startupDiagnosticsRegField[i].mask, startupDiagnosticsRegField[i].shift);
        Vps_printf("StartRegFieldValue[%d] address 0x%x : 0x%x\n", i, startupDiagnosticsRegField[i].base+startupDiagnosticsRegField[i].offset, StartRegFieldValue[i]);
    }

    // Compare it with the reference register value
    for (i=0; i<MAX_S_DIAG_REGFIELDS;i++)
    {
        if(StartRegFieldValue[i] != startupDiagnosticsRegField[i].reference)
        {
            Vps_printf("\n StartRegField %d ERROR is: %x should be %x \n", i, StartRegFieldValue[i], startupDiagnosticsRegField[i].reference);
            Vps_printf("\n Performing AutoUpdate \n");
            HW_WR_FIELD32_RAW(startupDiagnosticsRegField[i].base + startupDiagnosticsRegField[i].offset,
                startupDiagnosticsRegField[i].mask, startupDiagnosticsRegField[i].shift, startupDiagnosticsRegField[i].reference);
            // Perform check after writing into it.
            StartRegFieldValue[i] =
                HW_RD_FIELD32_RAW(startupDiagnosticsRegField[i].base + startupDiagnosticsRegField[i].offset, \
                    startupDiagnosticsRegField[i].mask, startupDiagnosticsRegField[i].shift);

            Vps_printf("\n Performing AutoUpdate on StartRegField %d is now %x COMPLETED \n", i, StartRegFieldValue[i]);
        }
    }

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 *******************************************************************************
*/
Void Chains_menuSingleCameraRun()
{
    Bool done = FALSE;

    Chains_statCollectorReset();

    RVC_StartupDiagnostics();

    while(!done)
    {
        /* VIP Single RVC Cam - CRC on DSP2 */
        chains_vipSingleRvcCamCrc_Display(&gChains_usecaseCfg);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Do common system init
 *
 *******************************************************************************
*/
Void Rvc_ChainsCommon_Init()
{
    Board_init();

    Lcd_init();

    Utils_prcmClockRateInit();

    GrpxSrcLink_init();

    Chains_linkStatsMonitorInit();
}

/**
 *******************************************************************************
 *
 * \brief   Do common system deinit
 *
 *******************************************************************************
*/
Void Rvc_ChainsCommon_DeInit()
{
    Chains_linkStatsMonitorDeInit();

    GrpxSrcLink_deInit();

    Lcd_deInit();

    Board_deInit();
}


/**
 *******************************************************************************
 *
 * \brief   Main call for usecase selection and configuration
 *
 *          Chains_main is called form the main of main_ipu1_0.c .
 *          This is the entry point for usecase selection.
 *          Board, UART LCD initializations and demo selections are performed.
 *          It waits in a while loop till the end of demo/usecase is triggred
 *
 * \param   arg0    [IN]  default args
 *
 * \param   arg1    [IN]  default args
 *
 *******************************************************************************
*/
Void Chains_main(UArg arg0, UArg arg1)
{
    Rvc_ChainsCommon_Init();

    Chains_Ctrl_Init(&gChains_usecaseCfg);
    gChains_usecaseCfg.displayType = CHAINS_DISPLAY_TYPE_LCD_10_INCH;
    gChains_usecaseCfg.captureSrc = CHAINS_CAPTURE_SRC_VIDDEC_TVP5158;

    Chains_menuSingleCameraRun();

    Rvc_ChainsCommon_DeInit();
}
