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
 * \file system_ipu1_0.c
 *
 * \brief  This file has the implementataion of system and link init and deinit
 *
 *         This file implements system Init deinit , Link init and deinit calls,
 *         BSP driver and platform initialized from IPU1
 *
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include "system_priv_ipu1_0.h"
#include "system_bsp_init.h"
#include <src/rtos/links_common/system/system_priv_common.h>
#ifdef DCC_ESM_INCLUDE
#include <src/rtos/utils_common/include/utils_esm.h>
#endif
#ifdef ECC_FFI_INCLUDE
#include "src/rtos/utils_common/include/utils_l3fw.h"
#endif
#ifdef TDA3XX_BUILD
#include "src/rtos/utils_common/include/utils_ipu_ecc.h"
#endif

/**
 *******************************************************************************
 * \brief IPU1_0 global Object
 *******************************************************************************
 */
System_Ipu1_0_Obj gSystem_objIpu1_0;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
void App_init(void);
void App_deInit(void);
/**
 *******************************************************************************
 * \brief API to Initialize the system
 *
 *   - Initialize various links present in the core
 *   - Initialize the resources
 *
 *   Links and chains APIs allow user to connect different drivers in a
 *   logical consistent way in order to make a chain of data flow.
 *
 *   Example,
 *   Capture + NSF + DEI + SC + Display
 *   OR
 *   Capture + Display
 *
 *   A link is basically a task which exchange frames with other links and
 *   makes FVID2 driver  calls to process the frames.
 *
 *   A chain is a connection of links.
 *
 *   Links exchange frames with each other via buffer queue's.
 *
 *   Links exchange information with each other and the top level system task
 *   via mail box.
 *
 *   When a link is connected to another link, it basically means output queue
 *   of one link is connected to input que of another link.
 *
 *   All links have a common minimum interface which makes it possible for a
 *   link to exchange frames with another link without knowing the other links
 *   specific details. This allow the same link to connect to different other
 *   links in different data flow scenario's
 *
 *   Example,
 *   Capture can be connected to either display in the Capture + Display chain
 *   OR
 *   Capture can be connected to NSF in the Capture + NSF + DEI + SC + Display
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_init(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

#ifdef SYSTEM_DEBUG
    Vps_printf(" SYSTEM: System Init in progress !!!\n");
#endif

   /* BSP driver and platform initialized from IPU1 */
    System_bspInit();

    Utils_dmaInit();

#ifdef DCC_ESM_INCLUDE
    System_esmInit();
#endif

#ifdef ECC_FFI_INCLUDE
    Utils_l3FwSetup();
#endif

    Utils_emifEccInit();
#ifdef TDA3XX_BUILD
    Utils_ipuEccInit();
#endif

    System_memPrintHeapStatus();

    System_initLinks();

    /*
     *  Application specific init:
     *  This is defined in the applicaion 'main_app' code
     */
    App_init();

#ifdef ISS_INCLUDE
    Utils_ispLockCreate();
#endif

   return status;
}

/**
 *******************************************************************************
 *
 * \brief API to De-Initialize the system
 *
 *  - De-Initialize various links present in the core
 *  - De-Initialize the resources
 *
 * \param shutdownRemoteProcs   [IN] Set FALSE always for Bios only build.
 *                                   For Linux builds choose TRUE or FALSE
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_deInit(UInt32 shutdownRemoteProcs)
{
   Int32 status = SYSTEM_LINK_STATUS_SOK;

    Utils_emifEccDeInit();
#ifdef TDA3XX_BUILD
    Utils_ipuEccDeInit();
#endif

   App_deInit();

   System_deInitLinks();

   System_memPrintHeapStatus();

#ifdef ECC_FFI_INCLUDE
    Utils_l3FwReset();
#endif

#ifdef DCC_ESM_INCLUDE
    System_esmDeInit();
#endif

   Utils_dmaDeInit();

   System_bspDeInit();

#ifdef IPUMM_INCLUDE
    if (gSystem_objIpu1_0.tsk_handle_ipumm != NULL)
    {
        BspOsal_taskDelete(gSystem_objIpu1_0.tsk_handle_ipumm);
    }
#endif

#ifdef SYSTEM_DEBUG
   Vps_printf(" SYSTEM: System De-Init Done !!!\n");
#endif

   return status;
}
