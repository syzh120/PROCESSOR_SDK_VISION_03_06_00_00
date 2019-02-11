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
#include <include/common/chains_radar.h>

/**
 *******************************************************************************
 * \brief Run Time Menu string for Network mode
 *******************************************************************************
 */
static char gChains_menuRadarDataRdWrMode[] = {
    "\r\n "
    "\r\n Select Data Read/Write Mode, "
    "\r\n --------------------"
    "\r\n 1: SD CARD "
    "\r\n 2: NETWORK "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char gChains_menuRadarUsecases[] = {
    "\r\n "
    "\r\n RADAR Usecases"
    "\r\n ---------------"
    "\r\n "
#ifdef TDA3XX_AR12_ALPS
    "\r\n 1: AR12 Firmware Flash (ALPS board Only)"
#endif
#ifdef UC_radar_capture_only
    "\r\n 2: Radar (Single AWR1243) Capture + Null (TDA3xx Only)"
#endif
#ifdef UC_radar_objectdetect_display
    "\r\n 3: Radar (Single AWR1243) Capture + Radar Object Detect (EVE1) + Display (TDA3xx Only)"
#endif
#ifdef UC_radar_objectdetect_null
    "\r\n 4: Radar (Single AWR1243) Capture + Radar Object Detect (EVE1) + Null (TDA3xx Only)"
#endif
#ifdef UC_radar_capture_process
    "\r\n 5: Radar (Single AWR1243) Capture + Radar Frame Copy (DSP1) + Null (TDA3xx Only)"
#endif
#ifdef UC_radar_read_fft_write
    "\r\n 6: Null Source (SD/Network) Input + Radar FFT (EVE1) + Null (SD/Network) "
#endif
#ifdef UC_multi_radar_capture_fft_display
    "\r\n 7: Multi Radar (AWR1243) Capture + Radar FFT (EVE1) + Display (TDA3xx Only)"
#endif
#ifdef UC_radar_read_objectdetect_write
    "\r\n 8: Null Source (SD) Input + Radar Object Detect (EVE1) + Null (SD) "
#endif
#ifdef UC_cascade_radar_capture_only
    "\r\n 9: Cascade Radar (4 AWR1243) Capture + Null (TDA2xx Only)"
#endif
#ifdef UC_cascade_radar_object_detect
    "\r\n a: Cascade Radar (4 AWR1243) Capture + Radar Object Detect (DSP) + Null (TDA2xx Only)"
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

Chains_DataRdWrType Chains_getDataRdWrMode()
{
    char ch;
    UInt32 done = FALSE;
    Chains_DataRdWrType linkType;

    while(!done)
    {
        Vps_printf(gChains_menuRadarDataRdWrMode);

        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                linkType = CHAINS_RADAR_LINKTYPE_FILE;
                done = TRUE;
                break;
            case '2':
                linkType = CHAINS_RADAR_LINKTYPE_NETWORK;
                done = TRUE;
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    return linkType;
}

Void Chains_radarMain(Chains_Ctrl *chainsCfg)
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Chains_statCollectorReset();

        Vps_printf(gChains_menuRadarUsecases);

        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef TDA3XX_AR12_ALPS
            case '1':
                if((Bsp_platformIsTda3xxFamilyBuild()) && (Bsp_boardGetId() == BSP_BOARD_TDA3XX_AR12XX_ALPS))
                {
                    ChainsCommon_ar12xxFirmwareFlash();
                }
                else
                {
                    Vps_printf(" ### Cannot run usecase. Usecase not supported on this platform \n");
                }

                break;
            #endif
            #ifdef UC_radar_capture_only
            case '2':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    Chains_radarcaptureonly(chainsCfg);
                }
                else
                {
                    Vps_printf(" ### Cannot run usecase. Usecase not supported on this platform \n");
                }
                break;
            #endif
            #ifdef UC_radar_objectdetect_display
            case '3':
                chainsCfg->algProcId = SYSTEM_PROC_EVE1;
                Chains_radarobjectdetectdisplay(chainsCfg);
                break;
            #endif
            #ifdef UC_radar_objectdetect_null
            case '4':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    chainsCfg->algProcId = SYSTEM_PROC_EVE1;
                    Chains_radarobjectdetectnull(chainsCfg);
                }
                else
                {
                    Vps_printf(" ### Cannot run usecase. Usecase not supported on this platform \n");
                }
                break;
            #endif
            #ifdef UC_radar_capture_process
            case '5':
                if(Bsp_platformIsTda3xxFamilyBuild())
                {
                    Chains_radarcaptureprocess(chainsCfg);
                }
                else
                {
                    Vps_printf(" ### Cannot run usecase. Usecase not supported on this platform \n");
                }
                break;
            #endif
            #ifdef UC_radar_read_fft_write
            case '6':
                chainsCfg->algProcId = SYSTEM_PROC_EVE1;
                Chains_radarreadfftwrite(chainsCfg);
                break;
            #endif
            #ifdef UC_multi_radar_capture_fft_display
            case '7':
                chainsCfg->algProcId = SYSTEM_PROC_EVE1;
                Chains_multiradarcapturefftdisplay(chainsCfg);
                break;
            #endif
            #ifdef UC_radar_read_objectdetect_write
            case '8':
                chainsCfg->algProcId = SYSTEM_PROC_EVE1;
                Chains_radarfilereadobjdetectwrite(chainsCfg);
                break;
            #endif
            #ifdef UC_cascade_radar_capture_only
            case '9':
                Chains_cascadeRadarCapture(chainsCfg);
                break;
            #endif
            #ifdef UC_cascade_radar_object_detect
            case 'a':
                Chains_cascadeRadarOd(chainsCfg);
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
