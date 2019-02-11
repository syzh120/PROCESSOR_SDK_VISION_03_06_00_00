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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <system_cfg.h>
#include <src/hlos/adas/include/chains.h>
#include <include/link_api/networkCtrl_api.h>
#include <include/link_api/dataCollectLink.h>

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

Void Chains_showSystemSettingsMenu();
Void Chains_menuSingleCameraRun();
Void Chains_menuMultiCameraLvdsRun();
Void Chains_menuOpenComputeRun();
Void Chains_menuAvbRxRun();
Void Chains_menuIssRun();
Void Chains_menuRadarRun();

Chains_Ctrl gChains_usecaseCfg;

/**
 *******************************************************************************
 * \brief Run Time Test Menu string.
 *******************************************************************************
 */
char gChains_testMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Vision SDK Usecases"
    "\r\n ===================="
    "\r\n 1: Single Camera Usecases"
    "\r\n 2: Multi-Camera LVDS Usecases"
    "\r\n 3: Open-Compute Usecases"
#ifdef AVB_INCLUDE
    "\r\n 4: AVB RX Usecases, (TDA2x & TDA2Ex ONLY)"
#endif
#ifdef ISS_INCLUDE
    "\r\n 5: ISS Usecases, (TDA2Px ONLY)"
#endif
    "\r\n 6: Radar Usecases"
    "\r\n "
    "\r\n p: CPU Status"
    "\r\n i: Show IP Addr (IPU + NDK + AVB) "
    "\r\n "
    "\r\n s: System Settings "
    "\r\n "
    "\r\n x: Exit "
    "\r\n z: Exit - AND SHUTDOWN Remote CPUs"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

#ifdef EARLY_USECASE_ENABLE
/* Since the chain resides on M4, there isn't an interactive menu available
 to manipulate the behavior of the chain. The only option available is to
 exit the use-case, which will in-turn de-init the links.*/
Void Chains_mainEarlyUsecase(char *e)
{
    /*Loop till task is exited*/
    char ch;
    while(1)
    {
      Vps_printf("Enter 'e' to exit\n");
      ch = getchar();
      if(ch == 'e')
      {
          break;
      }
    }
}
#endif

/**
 *******************************************************************************
 *
 * \brief   Application's main - entry function
 *
 *******************************************************************************
*/
Int32 main (Int32 argc, Char ** argv)
{
    char ch;
    Int32 status;
    Bool shutdownRemoteCores = FALSE;

    System_init();
#ifndef QNX_BUILD
    NetworkCtrl_init();
    DataCollectLink_init();
#endif
    ChainsCommon_appCtrlCommonInit();
    status = System_linkControl(SYSTEM_LINK_ID_APP_CTRL,
                                APP_CTRL_LINK_CMD_LINUX_INIT_COMPLETE,
                                NULL,
                                0,
                                TRUE);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
#ifdef EARLY_USECASE_ENABLE
    Chains_mainEarlyUsecase(&ch);
    shutdownRemoteCores = TRUE;
#else
    
    Chains_Ctrl_Init(&gChains_usecaseCfg);

    /* allow remote prints to complete, before showing main menu */
    OSA_waitMsecs(500);

    static UInt8 autoBoot = 0;
    gChains_usecaseCfg.ispOpMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
    strncpy(gChains_usecaseCfg.sensorName, SENSOR_OMNIVISION_OV10640_IMI,
        ISS_SENSORS_MAX_NAME);

    while(1)
    {
        Vps_printf(gChains_testMenu);
        if (autoBoot == 0)
        {
            ch = getchar();
        }
        else
        {
            ch = 'b';
            autoBoot = 0;
        }


        if((ch=='x') || (ch=='X'))
            break;

        if((ch=='z') || (ch=='Z'))
        {
            shutdownRemoteCores = TRUE;
            break;
        }

        switch(ch)
        {
            case '1':
                Chains_menuSingleCameraRun();
                break;
            case '2':
                Chains_menuMultiCameraLvdsRun();
                break;
            case '3':
                Chains_menuOpenComputeRun();
                break;
            #ifdef AVB_INCLUDE
            case '4':
                Chains_menuAvbRxRun();
                break;
            #endif
            #ifdef ISS_INCLUDE
            case '5':
                Chains_menuIssRun();
                break;
            #endif
            case '6':
                Chains_menuRadarRun();
                break;
            case 'p':
            case 'P':
                ChainsCommon_printCpuStatus();
                break;
            case 'i':
            case 'I':
                if(System_isProcEnabled(SYSTEM_IPU_PROC_PRIMARY))
                {
                    SystemCommon_IpAddr ipuIpAddr;
                    System_linkControl(
                        SYSTEM_LINK_ID_IPU1_0,
                        SYSTEM_COMMON_CMD_GET_IP_ADDR,
                        &ipuIpAddr,
                        sizeof(SystemCommon_IpAddr),
                        TRUE
                    );
                    Vps_printf(" Network IP address : %s\n", ipuIpAddr.ipAddr);
                }
                break;
            case 's':
            case 'S':
                Chains_showSystemSettingsMenu();
                break;
        }
    }
    ChainsCommon_appCtrlCommonDeInit();
#ifndef QNX_BUILD
    NetworkCtrl_deInit();
    DataCollectLink_deInit();
#endif
#endif /*EARLY_USECASE_ENABLE*/

    System_deInit(shutdownRemoteCores);

    return 0;
}

