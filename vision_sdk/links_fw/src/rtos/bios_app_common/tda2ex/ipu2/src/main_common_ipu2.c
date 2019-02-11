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
 * \file main_ipu2.c
 *
 * \brief  This file implements the IPU2 main()
 *
 *         This file has the IPU2 main(), the entry point to the core.
 *         Set the IPU2 clock and call System_start() & BIOS_start()
 *
 * \version 0.0 (Aug 2013) : [SS] First version
 *
 *******************************************************************************
*/

#ifdef A15_TARGET_OS_LINUX
/* This define must precede inclusion of any xdc header file */
#define Registry_CURDESC Test__Desc
#define MODULE_NAME "Server"
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_idle.h>
#include <src/rtos/utils_common/include/utils_timer_reconfig.h>
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>

#ifdef A15_TARGET_OS_LINUX
/* xdctools header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Registry.h>

#include <src/rtos/links_common/system/system_priv_common.h>
#include <src/rtos/links_common/system/system_rsc_table_ipu.h>
/* private data */
Registry_Desc               Registry_CURDESC;
#endif

/*******************************************************************************
 *  Function prototypes
 *******************************************************************************
 */
Int32 System_start(Task_FuncPtr chainsMainFunc);
Int32 StartupEmulatorWaitFxn (void);
Void IPU2_main(UArg arg0, UArg arg1);
void mainIPU2_TimerTick(UArg arg);

/*******************************************************************************
 *  external reference
 *******************************************************************************
 */
extern Void Chains_main(UArg arg0, UArg arg1);

/**
 *******************************************************************************
 *
 * \brief This function implements the wait loop of IPU2.
 *
 *        This function would get called if the IPU2 doesn't run the demo
 *        or application. It is not used if IPU2 runs the app.  Do not
 *        remove this function, required when App is moved out of IPU2
 *
 * \param  arg0 [IN]
 * \param  arg1 [IN]
 *
 * \return  void
 *
 *******************************************************************************
 */
Void IPU2_main(UArg arg0, UArg arg1)
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
 * \brief This is the main() implementation of IPU2.
 *
 *        This is the first function  and entry point to IPU2, does
 *         - Set the correct/required CPU frequency
 *         - Call the System_start with either Chain_main() or IPU2_main()
 *         - Call Chain_main() if App/Chain App is runs on local core
 *         - Call IPU2_main() instead of Chain_main if App/Chain is
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

#ifdef A15_TARGET_OS_LINUX
    Registry_Result result;

    /* register with xdc.runtime to get a diags mask */
    result = Registry_addModule(&Registry_CURDESC, MODULE_NAME);
    Assert_isTrue(result == Registry_SUCCESS, (Assert_Id)NULL);

    /* enable some log events */
    Diags_setMask(MODULE_NAME"+EXF");
#endif

    /* This should the first call for initializing the remote debug server
     */
    RemoteLog_init();

#ifdef IPU_PRIMARY_CORE_IPU2
       IPU_primary_core_init();
#endif

    Vps_printf(" ***** IPU2 Firmware build time %s %s\n",
               __TIME__,__DATE__);

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

#ifdef IPU_PRIMARY_CORE_IPU2
    System_start(Chains_main);
#else
    System_start(IPU2_main);
#endif
    BIOS_start();

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief This function enables the IPU2 debug option
 *
 *        This function enables the IPU2 debug option from main() onwards
 *         - Set the volatile variable enableDebug = 1 to enable debug
 *         - rebuild the code with enableDebug = 1
 *         - Once enableDebug is set to 1, the control waits in this
 *           function even after the free-run
 *         - Can connect to core IPU2 via CCS and J-Tag to debug
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
 * \brief This function enables the M4Cpu0 Timer Ticks
 *
 * \param  arg [IN]
 *
 *******************************************************************************
 */
void mainIPU2_TimerTick(UArg arg)
{
    Utils_idleSev();
    Clock_tick();
}

/* Nothing beyond this point */

