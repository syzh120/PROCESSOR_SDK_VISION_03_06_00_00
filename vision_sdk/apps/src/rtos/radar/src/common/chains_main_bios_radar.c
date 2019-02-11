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
#include <include/common/chains_radar.h>

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */
Void Chains_showMainMenu(char *main_menu);
Void Chains_showSystemSettingsMenu();

Chains_Ctrl gChains_usecaseCfg;

/**
 *******************************************************************************
 * \brief Menu setting display string.
 *******************************************************************************
 */
char gChains_menuUseCases[] = {
    "\r\n "
    "\r\n Vision SDK Usecases,"
    "\r\n -------------------- "
    "\r\n "
    "\r\n 1: RADAR Usecases"
    "\r\n 2: MISC Tests"
    "\r\n "
    "\r\n s: System Settings "
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};


/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChains_runTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

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
    ChainsCommon_Init();
    Chains_Ctrl_Init(&gChains_usecaseCfg);

    {
        #if 0
        Chains_radarcaptureonly(&gChains_usecaseCfg);
        #endif
        {
            char ch;
            Bool done;

            done = FALSE;

            while(!done)
            {
                Chains_showMainMenu(gChains_menuUseCases);

                ch = Chains_readChar();

                Vps_printf(" \r\n");

                switch(ch)
                {
                    case '1':
                        {
                            Void Chains_radarMain(Chains_Ctrl *chainsCfg);

                            Chains_radarMain(&gChains_usecaseCfg);
                        }
                        break;

                    case '2':
                    {
                        Void System_workQueueTestRun();

                        System_workQueueTestRun();
                    }
                        break;

                    case 's':
                    case 'S':
                        Chains_showSystemSettingsMenu();
                        break;

                    case 'x':
                    case 'X':
                        done = TRUE;
                        break;
                }
            }
        }
    }

    ChainsCommon_DeInit();
}
