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
#include <src/include/chains.h>
#include <src/rtos/utils_common/include/utils_prcm_stats.h>

/*******************************************************************************
 *  Global's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Menu for system settings.
 *******************************************************************************
 */
 char gChains_menuSystemSettings[] = {
    "\r\n "
    "\r\n ==============="
    "\r\n System Settings"
    "\r\n ==============="
    "\r\n "
    "\r\n 1: Print PRCM Statistics"
    "\r\n 2: Show Memory/CPU/DDR BW usage"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief Interface IP address.
 * \note  This is needed for Radar ALPS board without UART console. Users can
 *        connect to IPU1_0 via CCS and after loading symbols can look at value
 *        of this global variable to know the board IP address.
 *******************************************************************************
 */
char gDeviceIpAddr1[20];
char gDeviceIpAddr2[20];

extern char *gChain_displayTypeName[];
Void Chains_showDisplaySettingsMenu();
Void Chains_showPMStatistics();

/**
 *******************************************************************************
 *
 * \brief   Function to display select options using uart print message
 *
 *******************************************************************************
*/
Void Chains_showMainMenu(char *main_menu)
{

    /*Obtain the IP Addresses for both the interfaces*/
    Utils_netGetIpAddrStr(gDeviceIpAddr1, 1);
    Utils_netGetIpAddrStr(gDeviceIpAddr2, 2);

    Vps_printf(" \n");
    Vps_printf(" Current System Settings,\n");
    Vps_printf(" ========================\n");
    Vps_printf(" Display Type   : %s \n",
            gChain_displayTypeName[gChains_usecaseCfg.displayType]);
    Vps_printf(" My IP address for interface 1 : %s \n",
            gDeviceIpAddr1 );
    Vps_printf(" My IP address for interface 2 : %s \n",
            gDeviceIpAddr2 );
    Vps_printf(" \n");
    Vps_printf(" ============\r\n");
    Vps_printf(" Usecase Menu\r\n");
    Vps_printf(" ============\r\n");

    Vps_printf(main_menu);
}

/**
 *******************************************************************************
 *
 * \brief   Function to select systems settings option.
 *
 *******************************************************************************
*/
Void Chains_showSystemSettingsMenu()
{
    char ch;
    Bool done;
    done = FALSE;

    do
    {
        Vps_printf(gChains_menuSystemSettings);
        Vps_printf(" \r\n");
        ch = Chains_readChar();

        switch(ch)
        {
           case '1':
                Chains_showPMStatistics();
                done = TRUE;
                break;
           case '2':
                Utils_prcmPrintAllVDTempValues();
                Chains_memPrintHeapStatus();
                Chains_statCollectorPrint();
                Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
                Vps_printf(" CHAINS: Waiting for CPU load calculation to Complete !!!!\n");
                Task_sleep(2000);
                Vps_printf(" CHAINS: CPU load calculation to Complete !!!!\n");
                Chains_prfLoadCalcEnable(FALSE, TRUE, TRUE);
                done = TRUE;
                break;
            case 'x':
            case 'X':
                done = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }while(!done);
}
