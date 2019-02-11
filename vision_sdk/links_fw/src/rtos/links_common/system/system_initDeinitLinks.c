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
 * \file system_initDeinitLinks.c
 *
 * \brief   Initialize and deinitialize links for all the cores.
 *
 *          This file deals with system level initialization of links and
 *          chains framework. It creates a system tasks for handling all system
 *          wide functions. Initializes the system wide resources like
 *          and components performance counters, mail boxes, IPC, memory
 *          allocators. It also initializes all links in the system such that
 *          links are ready to take commands from application.
 *
 * \version 0.0 (Jun 2013) : [KC] First version taken from DVR RDK and
 *                            cleaned up for Vision_sdk
 * \version 0.1 (Jul 2013) : [HS] Commenting style update as per defined
 *                                format.
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "system_priv_common.h"
#include <include/link_api/dupLink.h>
#include <include/link_api/gateLink.h>
#include <include/link_api/ipcLink.h>
#include <include/link_api/mergeLink.h>
#include <include/link_api/nullLink.h>
#include <include/link_api/nullSrcLink.h>
#include <include/link_api/networkTxLink.h>
#include <include/link_api/networkRxLink.h>
#include <include/link_api/selectLink.h>
#include <include/link_api/syncLink.h>
#include <include/link_api/tfdtpRxLink.h>
#include <include/link_api/displayLink.h>
#include <include/link_api/displayCtrlLink.h>
#include <include/link_api/issCaptureLink.h>
#include <include/link_api/issM2mIspLink.h>
#include <include/link_api/issM2mSimcopLink.h>
#include <include/link_api/captureLink.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/dssM2mWbLink.h>

#ifdef BUILD_M4_0
    #include <linksInclude_ipu1_0.h>
#endif

#ifdef BUILD_M4_1
    #include <linksInclude_ipu1_1.h>
#endif

#ifdef BUILD_M4_2
    #include <linksInclude_ipu2.h>
#endif

#ifdef BUILD_A15
    #include <linksInclude_a15_0.h>
#endif

#ifdef BUILD_DSP_1
    #include <linksInclude_c66xdsp_1.h>
#endif

#ifdef BUILD_DSP_2
    #include <linksInclude_c66xdsp_2.h>
#endif

#ifdef BUILD_ARP32_1
    #include <linksInclude_arp32_1.h>
#endif

#ifdef BUILD_ARP32_2
    #include <linksInclude_arp32_2.h>
#endif

#ifdef BUILD_ARP32_3
    #include <linksInclude_arp32_3.h>
#endif

#ifdef BUILD_ARP32_4
    #include <linksInclude_arp32_4.h>
#endif
#ifdef links_common_avb_rx
#include <include/link_api/avbRxLink.h>
#endif
#ifdef links_common_avb_tx
#include <include/link_api/avbTxLink.h>
#endif
#ifdef links_ipu_iva
#include <include/link_api/encLink.h>
#include <include/link_api/decLink.h>
#endif
#ifdef links_ipu_vpe
#include <include/link_api/vpeLink.h>
#endif
#ifdef links_ipu_iss_m2mresizer
#include <include/link_api/issM2mResizerLink.h>
#endif


/**
 *******************************************************************************
 *
 * \brief Initialize the core system links
 *
 *******************************************************************************
*/
Void System_initLinks(void)
{

    Vps_printf(" SYSTEM: Initializing Links !!! \r\n");

    /*  Links init based on the links which are part of the build
     */
    #ifdef links_common_avb_rx
        AvbRxLink_init();
    #endif
    #ifdef links_common_avb_tx
        AvbTxLink_init();
    #endif
    #ifdef links_common_dup
        DupLink_init();
    #endif
    #ifdef links_common_gate
        GateLink_init();
    #endif
    #ifdef links_common_ipcIn
        IpcInLink_init();
    #endif
    #ifdef links_common_ipcOut
        IpcOutLink_init();
    #endif
    #ifdef links_common_merge
        MergeLink_init();
    #endif
    #ifdef links_common_network_tx
        NetworkTxLink_init();
    #endif
    #ifdef links_common_network_rx
        NetworkRxLink_init();
    #endif
    #ifdef links_common_null
        NullLink_init();
    #endif
    #ifdef links_common_nullSrc
        NullSrcLink_init();
    #endif
    #ifdef links_common_select
        SelectLink_init();
    #endif
    #ifdef links_common_sync
        SyncLink_init();
    #endif
    #ifdef links_common_tfdtp_rx
        TfdtpRxLink_init();
    #endif
    #ifdef links_ipu_display
        DisplayLink_init();
    #endif
    #ifdef links_ipu_display_ctrl
        DisplayCtrlLink_init();
    #endif
    #ifdef links_ipu_iss_capture
        IssCaptureLink_init();
    #endif
    #ifdef links_ipu_iss_m2misp
        IssM2mIspLink_init();
    #endif
    #ifdef links_ipu_iss_m2mresizer
        IssRszLink_init();
    #endif
    #ifdef links_ipu_iss_m2msimcop
        IssM2mSimcopLink_init();
    #endif
    #ifdef links_ipu_iva
        EncLink_init();
        DecLink_init();
    #endif
    #ifdef links_ipu_vip_capture
        CaptureLink_init();
    #endif
    #ifdef links_ipu_vpe
        VpeLink_init();
    #endif
    #ifdef links_common_algorithm
        AlgorithmLink_init();
    #endif
    #ifdef links_ipu_dssM2mWb
        DssM2mWbLink_init();
    #endif

    Vps_printf(" SYSTEM: Initializing Links ... DONE !!! \r\n");
}

/**
 *******************************************************************************
 *
 * \brief De-initialize the previously initialized core link
 *
 *******************************************************************************
*/
Void System_deInitLinks(void)
{
    Vps_printf(" SYSTEM: De-Initializing Links !!! \r\n");

    /*  Links de init based on the links which are part of the build
     */
    #ifdef links_common_avb_rx
        AvbRxLink_deInit();
    #endif
    #ifdef links_common_avb_tx
        AvbTxLink_deInit();
    #endif
    #ifdef links_common_dup
        DupLink_deInit();
    #endif
    #ifdef links_common_gate
        GateLink_deInit();
    #endif
    #ifdef links_common_ipcIn
        IpcInLink_deInit();
    #endif
    #ifdef links_common_ipcOut
        IpcOutLink_deInit();
    #endif
    #ifdef links_common_merge
        MergeLink_deInit();
    #endif
    #ifdef links_common_network_tx
        NetworkTxLink_deInit();
    #endif
    #ifdef links_common_network_rx
        NetworkRxLink_deInit();
    #endif
    #ifdef links_common_null
        NullLink_deInit();
    #endif
    #ifdef links_common_nullSrc
        NullSrcLink_deInit();
    #endif
    #ifdef links_common_select
        SelectLink_deInit();
    #endif
    #ifdef links_common_sync
        SyncLink_deInit();
    #endif
    #ifdef links_common_tfdtp_rx
        TfdtpRxLink_deInit();
    #endif
    #ifdef links_ipu_display
        DisplayLink_deInit();
    #endif
    #ifdef links_ipu_display_ctrl
        DisplayCtrlLink_deInit();
    #endif
    #ifdef links_ipu_iss_capture
        IssCaptureLink_deInit();
    #endif
    #ifdef links_ipu_iss_m2misp
        IssM2mIspLink_deInit();
    #endif
    #ifdef links_ipu_iss_m2mresizer
        IssRszLink_deInit();
    #endif
    #ifdef links_ipu_iss_m2msimcop
        IssM2mSimcopLink_deInit();
    #endif
    #ifdef links_ipu_iva
        EncLink_deInit();
        DecLink_deInit();
    #endif
    #ifdef links_ipu_vip_capture
        CaptureLink_deInit();
    #endif
    #ifdef links_ipu_vpe
        VpeLink_deInit();
    #endif
    #ifdef links_common_algorithm
        AlgorithmLink_deInit();
    #endif
    #ifdef links_ipu_dssM2mWb
        DssM2mWbLink_deInit();
    #endif

    Vps_printf(" SYSTEM: De-Initializing Links ... DONE !!! \r\n");
}
