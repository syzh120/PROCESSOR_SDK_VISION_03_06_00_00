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
#include <src/include/chains.h>

/*******************************************************************************
 *  Globals
 *******************************************************************************
 */

char gChains_menuDualDisplayUsecases[] = {
    "\r\n "
    "\r\n Dual Display Usecases (TDA2x EVM ONLY)"
    "\r\n ----------------------------------------"
#ifdef UC_vip_single_cam_dual_display
    "\r\n 1: 1CH VIP capture + Dual Display"
#endif
#ifdef UC_lvds_vip_dual_cam_dual_display
    "\r\n 2: 2CH LVDS VIP capture + Dual Display"
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};


char gChains_menuMiscTests[] = {
    "\r\n "
    "\r\n Miscellaneous Test's"
    "\r\n --------------------"
#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) )
    "\r\n 1: File IO using MMCSD"
#endif
#ifdef UC_null_src_dec_display
    "\r\n 2: NullSrc (Encoded) + Decode + Display and Null"
#endif
#ifdef UC_null_src_display
    "\r\n 3: NullSrc (YUV) + Display and Null"
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/
Void Chains_menuDualDisplayRun()
{
    static Chains_Ctrl usecaseCfg = {0};
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Chains_statCollectorReset();

        Vps_printf(gChains_menuDualDisplayUsecases);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_vip_single_cam_dual_display
            case '1':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    usecaseCfg = gChains_usecaseCfg;
                    if( usecaseCfg.displayType != CHAINS_DISPLAY_TYPE_LCD_7_INCH &&
                        usecaseCfg.displayType != CHAINS_DISPLAY_TYPE_LCD_10_INCH)
                    {
                        Vps_printf(" ### This usecase displays on HDMI and LCD");
                        Vps_printf(" ### Please choose connected LCD type using option 's'\n");
                        break;
                    }
                    chains_vipSingleCam_DualDisplay(&gChains_usecaseCfg);
                }
                break;
            #endif
            #ifdef UC_lvds_vip_dual_cam_dual_display
            case '2':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    if(Board_isMultiDesConnected())
                    {
                        gChains_usecaseCfg.algProcId = System_getSelfProcId();
                        gChains_usecaseCfg.numLvdsCh = 2;
                        usecaseCfg = gChains_usecaseCfg;
                        if( usecaseCfg.captureSrc!= CHAINS_CAPTURE_SRC_OV10635 )
                        {
                            Vps_printf(" ### ONLY OV10635 Sensor supported for this usecase ");
                            Vps_printf(" ### Please choose OV10635 as Capture Source using option 's'\n");
                            break;
                        }
                        if( usecaseCfg.displayType != CHAINS_DISPLAY_TYPE_LCD_7_INCH &&
                            usecaseCfg.displayType != CHAINS_DISPLAY_TYPE_LCD_10_INCH)
                        {
                            Vps_printf(" ### This usecase displays on HDMI and LCD");
                            Vps_printf(" ### Please choose connected LCD type using option 's'\n");
                            break;
                        }

                        chains_lvdsVipDualCam_DualDisplay(&gChains_usecaseCfg);
                    }
                    else
                    {
                        Vps_printf(" ### Cannot run usecase. MulitDes Board Not Connected \n");
                    }
                }
                break;
            #endif
            case 'x':
            case 'X':
                done = TRUE;
                usecaseCfg = usecaseCfg; /* to avoid unused variable warning */
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }


}

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/
Void Chains_menuNetworkRxTxRun()
{
    #ifdef UC_network_rx_tx
    Chains_statCollectorReset();

    Chains_networkRxTx(&gChains_usecaseCfg);
    #endif
}

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/
Void Chains_menuMiscTestRun()
{
    char ch;
    Bool done = FALSE;

#ifdef UC_null_src_dec_display
    Chains_Ctrl chainsCfg = { 0 };
#endif

    while(!done)
    {
        Vps_printf(gChains_menuMiscTests);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            case '1':
#if ( defined(FATFS_PROC_TO_USE_IPU1_0) && defined(BUILD_M4_0) ) || \
    ( defined(FATFS_PROC_TO_USE_IPU2)   && defined(BUILD_M4_2) )
                Utils_fileTestRun();
#endif
                break;
#ifdef UC_null_src_dec_display
            case '2':
                chainsCfg = gChains_usecaseCfg;
                chainsCfg.numLvdsCh = 1;
                Chains_nullSrc_DecodeDisplay(&chainsCfg);
                break;
#endif
#ifdef UC_null_src_display
            case '3':
                Chains_nullSrc_display(&gChains_usecaseCfg);
                break;
#endif
            case 'x':
            case 'X':
                done = TRUE;
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

Int32 Chains_runDmaTest()
{
    UInt32 procId, linkId;

    for(procId=0; procId<SYSTEM_PROC_MAX; procId++)
    {
        if(System_isProcEnabled(procId)==FALSE)
            continue;

        linkId = SYSTEM_MAKE_LINK_ID(procId, SYSTEM_LINK_ID_PROCK_LINK_ID);

        System_linkControl(
            linkId,
            SYSTEM_COMMON_CMD_RUN_DMA_TEST,
            NULL,
            0,
            TRUE
        );
    }

    return SYSTEM_LINK_STATUS_SOK;
}

