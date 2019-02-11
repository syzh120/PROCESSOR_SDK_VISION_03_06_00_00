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
#include <system_cfg.h>

Void Chains_networkTxMultiCamCapture(Chains_Ctrl *chainsCfg);

static char usecase_menu[] = {
    "\r\n "
    "\r\n Select use-case,"
    "\r\n ----------------"
    "\r\n 1: Network RX + Display"
    "\r\n 2: Network RX + Decode + Display (TDA2x ONLY)"
    "\r\n 3: 1CH VIP Capture + Network TX"
    "\r\n 4: 1CH VIP Capture + Encode + Network TX (TDA2x ONLY)"
    "\r\n 5: 4CH VIP Capture + Network TX"
    #ifdef UC_tfdtprx_display
    "\r\n 6: TFDTPRx Link + Display"
    #endif
    "\r\n "
    "\r\n x: Exit"
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

Void Chains_networkRxTx(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;

    if(!Bsp_platformIsTda2xxFamilyBuild())
    {
#if !defined(NSP_TFDTP_INCLUDE)
        Vps_printf(" ### Cannot run usecase on this platform\n");
#endif
    }

    while(!done)
    {
        Vps_printf(usecase_menu);

        ch = Chains_readChar();

        switch(ch)
        {
            case 'x':
                done = TRUE;
                break;
            case '1':
                Chains_networkRxDisplay(chainsCfg);
                break;
            case '2':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    Chains_networkRxDecDisplay(chainsCfg);
                }
                else
                {
                    Vps_printf(" ### Cannot run usecase on this platform\n");
                }
                break;
            case '3':
                Chains_networkTxCapture(chainsCfg);
                break;
            case '4':
                if(Bsp_platformIsTda2xxFamilyBuild())
                {
                    Chains_networkTxEncCapture(chainsCfg);
                }
                else
                {
                    Vps_printf(" ### Cannot run usecase on this platform\n");
                }
                break;
            case '5':
                if(BSP_PLATFORM_SOC_ID_TDA2EX != Bsp_platformGetSocId())
                {
                 if(Board_isMultiDesConnected())
                 {
                     Chains_networkTxMultiCamCapture(chainsCfg);
                 }
                 else
                 {
                     Vps_printf(" ### Cannot run usecase on this platform\n");
                 }
                }
                else
                {
                     Vps_printf("Invalid option on TDA2EX, Network does not work on LVDS board\n");
                }
                break;
            #if defined (UC_tfdtprx_display) && defined(NSP_TFDTP_INCLUDE)
            case '6':
                Chains_tfdtpRx_Display(&gChains_usecaseCfg);
                break;
            #endif

            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

