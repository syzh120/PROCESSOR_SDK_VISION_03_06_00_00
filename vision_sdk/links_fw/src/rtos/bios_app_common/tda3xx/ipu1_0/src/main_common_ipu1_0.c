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
 *
 * \file main_ipu1_0.c
 *
 * \brief  This file implements the IPU1_0 main()
 *
 *         This file has the IPU1_0 main(), the entry point to the core.
 *         Set the IPU1_0 clock and call System_start() & BIOS_start()
 *
 * \version 0.0 (Jun 2013) : [SS] First version
 * \version 0.1 (Jul 2013) : [SS] Updates as per code review comments
 * \version 0.2  (Jul 2013) : [HS] Added support for remote debug
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <src/rtos/utils_common/include/utils.h>
#include <include/link_api/system_common.h>
#include <src/rtos/links_common/system/system_priv_common.h>
#include <src/rtos/utils_common/include/utils_idle.h>
#include <src/rtos/utils_common/include/utils_timer_reconfig.h>
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>

#include <xdc/cfg/global.h>
#ifdef ECC_FFI_INCLUDE
#include "src/rtos/utils_common/include/utils_l3fw.h"
#endif


/*******************************************************************************
 *  Function prototypes
 *******************************************************************************
 */
Int32 System_start(Task_FuncPtr chainsMainFunc);
Int32 StartupEmulatorWaitFxn (void);
Void IPU1_0_main(UArg arg0, UArg arg1);
void mainIPU1_C0TimerTick(UArg arg);

/*******************************************************************************
 *  external reference
 *******************************************************************************
 */
extern Void Chains_main(UArg arg0, UArg arg1);


/*******************************************************************************
 *  Return Physical address for VPDMA descriptor memory
 *******************************************************************************
 */
UInt32 System_getVpdmaPhysAddr(void)
{
    return XDC_CFG_VPDMA_DESC_PHYS_ADDR;
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Physical address for SR1_FRAME_BUFFER
 *******************************************************************************
 */
UInt8* System_getSr1FrameBufferAddr(void)
{
    return ((UInt8*)XDC_SR1_FRAME_BUFFER_ADDR);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Size for SR1_FRAME_BUFFER
 *******************************************************************************
 */
UInt32 System_getSr1FrameBufferSize(void)
{
    return (XDC_SR1_FRAME_BUFFER_SIZE);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Physical address for SR1_BUFF_ECC_ASIL
 *******************************************************************************
 */
UInt8* System_getSr1BuffEccAsilAddr(void)
{
    return ((UInt8*)XDC_SR1_BUFF_ECC_ASIL_ADDR);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Size for SR1_BUFF_ECC_ASIL
 *******************************************************************************
 */
UInt32 System_getSr1BuffEccAsilSize(void)
{
    return (XDC_SR1_BUFF_ECC_ASIL_SIZE);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Physical address for SR1_BUFF_ECC_QM
 *******************************************************************************
 */
UInt8* System_getSr1BuffEccQmAddr(void)
{
    return ((UInt8*)XDC_SR1_BUFF_ECC_QM_ADDR);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Size for SR1_BUFF_ECC_QM
 *******************************************************************************
 */
UInt32 System_getSr1BuffEccQmSize(void)
{
    return (XDC_SR1_BUFF_ECC_QM_SIZE);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Physical address for SR1_BUFF_NON_ECC_ASIL
 *******************************************************************************
 */
UInt8* System_getSr1BuffNonEccAsilAddr(void)
{
    return ((UInt8*)XDC_SR1_BUFF_NON_ECC_ASIL_ADDR);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/*******************************************************************************
 *  Return Size for SR1_BUFF_NON_ECC_ASIL
 *******************************************************************************
 */
UInt32 System_getSr1BuffNonEccAsilSize(void)
{
    return (XDC_SR1_BUFF_NON_ECC_ASIL_SIZE);
    /*  MISRA.LITERAL.UNSIGNED.SUFFIX, Rule 10.6:
     *  MISRA reports error as Unsigned integer literal without 'U' suffix,
     *  this is a labels picked from the .xs file of memory map and are not
     *  #define. Lets ignore this as this will not impact the code quality
     */
}

/**
 *******************************************************************************
 *
 * \brief This function implements the wait loop of IPU1_0.
 *
 *        This function would get called if the IPU1_0 doesn't run the demo
 *        or application. It is not used if IPU1_0 runs the app.  Do not
 *        remove this function, required when App is moved out of IPU1_0
 *
 * \param  arg0 [IN]
 * \param  arg1 [IN]
 *
 * \return  void
 *
 *******************************************************************************
 */
Void IPU1_0_main(UArg arg0, UArg arg1)
{
    UInt32 state;
    UInt32 coreId = System_getSelfProcId();

    while (1)
    {
        BspOsal_sleep(100U);
        Utils_getAppInitState(coreId, &state);
        if (state == CORE_APP_INITSTATUS_DO_EXIT)
        {
            break;
        }
    }
}



/**
 *******************************************************************************
 *
 * \brief This is the main() implementation of IPU1_0.
 *
 *        This is the first function  and entry point to IPU1_0, does
 *         - Set the correct/required CPU frequency
 *         - Call the System_start with either Chain_main() or IPU1_0_main()
 *         - Call Chain_main() if App/Chain App is runs on local core
 *         - Call IPU1_0_main() instead of Chain_main if App/Chain is
 *           implemented on any other remote code
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 main_common(void)
{
    /* This is for debug purpose- see the description of function header */
    StartupEmulatorWaitFxn();

    /* This should the first call for initializing the remote debug server
     */
    RemoteLog_init();
    Utils_remoteLogClientInit();

    Vps_printf(" ***** IPU1_0 Firmware build time %s %s\n",
               __TIME__,__DATE__);



#ifdef ECC_FFI_INCLUDE
    /* Reset Firewall configuration to clear older state when returning from
     * warm resets
     */
    Utils_l3FwReset();
    Utils_l3FwSetDsp1DataSectInfo(gXdcDsp1DataAddr, gXdcDsp1DataSize);
    Utils_l3FwSetDsp2DataSectInfo(gXdcDsp2DataAddr, gXdcDsp2DataSize);
    Utils_l3FwSetEve1DataSectInfo(gXdcEve1DataAddr, gXdcEve1DataSize);
    Utils_l3FwSetLinkStatSectInfo(gXdcLinkStatsAddr, gXdcLinkStatsSize);
#endif

    {
        UInt32 clkHz;

        clkHz = Utils_getClkHz(UTILS_CLK_ID_IPU);

        if(clkHz==0U)
        {
            clkHz = SYSTEM_IPU_FREQ;
        }

        Utils_setCpuFrequency(clkHz);
    }

    Utils_idlePrepare();

#ifdef IPU1_SMP_BIOS_INCLUDE
    /* The load module does not update the total elapsed time for the idle
     * function on Core1 if no task switches happen. So, If Core1 is lightly loaded
     * and there are no task switches during the sampling window, the idle task
     * load on Core 1 will get artificially inflated. This is a Bug in Bios, will
     * get fixed in 6.42.01.
     * In the mean time, use the below workaround,
     * Every clock tick send an SEV to wakeup IPU C1 and set the SEVONPEND to
     * allow waking up.
     */
    Utils_idleSetupSEVONPEND(0x1);
#endif

    System_start(Chains_main);
    BIOS_start();

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function enables the IPU1_0 debug option
 *
 *        This function enables the IPU1_0 debug option from main() onwards
 *         - Set the volatile variable enableDebug = 1 to enable debug
 *         - rebuild the code with enableDebug = 1
 *         - Once enableDebug is set to 1, the control waits in this
 *           function even after the free-run
 *         - Can connect to core IPU1_0 via CCS and J-Tag to debug
 *         - Once CCS is connected, reset enableDebug = 0 to come out of
 *           this function and proceeds with further debug
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 StartupEmulatorWaitFxn (void)
{
    volatile Int32 enableDebug = 0;
    do
    {
    }while (enableDebug);
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function enables the IPU_CPU_0 Timer Ticks
 *
 * \param  arg [IN]
 *
 *******************************************************************************
 */
void mainIPU1_C0TimerTick(UArg arg)
{
#ifdef IPU1_SMP_BIOS_INCLUDE
    Utils_idleSev();
#endif
    Clock_tick();
}

/* Nothing beyond this point */



