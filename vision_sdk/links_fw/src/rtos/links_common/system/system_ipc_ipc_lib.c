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
 * \file system_ipc_safe_ipclib.c
 *
 * \brief  This file implements usage of safe ipc library
 *
 * \version 0.0 (Aug 2016) : [YM] first version implemented
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "system_priv_ipc.h"
#include <ti/drv/ipc_lite/ipclib_interrupt.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
Void System_safeIpcHandler(UInt32 remoteProcId,
                           UInt32 eventId,
                           UInt32 payload,
                           Void *arg,
                           Int32 status);



/**
 *******************************************************************************
 *
 * \brief System wide notify handler function.
 *
 *        This function gets registered with the ipc_notifyhandler. Based on
 *        payload linkId is derived. From linkID callback of the specific
 *        link gets invoked.
 * \param   procId      [IN] processorId which invoked notify
 * \param   lineId      [IN] LineId of the notify
 * \param   eventId     [IN] Notify eventId
 * \param   arg         [IN] not used
 * \param   payload     [IN] 4-byte notify payload. From this procId and
 *                           linkId is derived to invoke link specific
 *                           callback function
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Void System_safeIpcHandler(UInt32 remoteProcId,
                           UInt32 eventId,
                           UInt32 payload,
                           Void *arg,
                           Int32 status)
{
    if (status == IPCLIB_SOK)
    {
#ifdef A15_TARGET_OS_LINUX
        #if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
        if(SYSTEM_LINK_ID_TEST_ROUTE_BIT_TRUE(payload))
        {
            SYSTEM_LINK_ID_CLEAR_ROUTE_BIT(payload);
            System_rpmsgSendNotify(payload);
            return;
        }
        #endif
#endif
        System_ipcHandler(payload);
    }
    else
    {
        Vps_printf(" SYSTEM: SAFE IPC: System_safeIpcHandler failed - "
                   " incomplete message received\n");
    }
}

/**
 *******************************************************************************
 *
 * \brief Utility function to invoke the notify to remote processor.
 *
 *        This function generates the notify event. It takes linkId as input
 *        maps linkId with procId and generates notify event on that processor
 *
 * \param   linkId      [IN] Link Id to which notify needs to be generated.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifySendEvent(UInt32 linkId)
{
    Int32 status;
    UInt32 procId = SYSTEM_GET_PROC_ID(linkId), ipcLibProcId;

    UTILS_assert(procId < SYSTEM_PROC_MAX);

#ifdef SYSTEM_IPC_MSGQ_DEBUG
    Vps_printf(" SYSTEM: NOTIFY: Sending Notify to [%s] !!!\n",
                 System_getProcName(procId));
#endif

#ifdef A15_TARGET_OS_LINUX
    /* IPU and DSPs should never call this function directly
     * They must use System_ipcSendNotify()
     */
    #ifdef BUILD_ARP32
    if(procId == SYSTEM_PROC_A15_0)
    {
        /* Set route bit and send it to IPU1 */
        SYSTEM_LINK_ID_SET_ROUTE_BIT(linkId);

        status =
        IpcLib_interruptSendEvent(
                            System_getIpcLibProcId(SYSTEM_IPU_PROC_PRIMARY),
                            SYSTEM_IPC_NOTIFY_EVENT_ID,
                            linkId,
                            TRUE);

        if (status != IPCLIB_SOK)
        {
            Vps_printf
                (" SYSTEM: IPCLIB: Send Event to [%s][%d] failed !!! (status = %d)\n",
                 System_getProcName(SYSTEM_GET_PROC_ID(linkId)),
                 SYSTEM_GET_LINK_ID(linkId), status);

            UTILS_assert(status == Notify_S_SUCCESS);
        }

        return SYSTEM_LINK_STATUS_SOK;
    }
    #endif
#endif

    if(System_isProcEnabled(procId)==FALSE)
    {
        Vps_printf(
            " SYSTEM: NOTIFY: [%s] is NOT ENABLED in this build !!!\n",
            System_getProcName(procId)
            );
        UTILS_assert((Bool)FALSE);
    }

    ipcLibProcId = System_getIpcLibProcId(procId);

    do
    {
        if(System_getCoreState(procId) != SYSTEM_CORE_STATE_ACTIVE)
        {
            Vps_printf(" SYSTEM: NOTIFY: Core is dead, skipping message\n");
            status = SYSTEM_LINK_STATUS_EFAIL;
            break;
        }

        status = IpcLib_interruptSendEvent(ipcLibProcId,
                                           SYSTEM_IPC_NOTIFY_EVENT_ID,
                                           linkId,
                                           (UInt32)TRUE);

        if (status != IPCLIB_SOK)
        {
            Vps_printf
                (" SYSTEM: NOTIFY: Send Event to [%s][%d] failed !!! (status = %d)\n",
                 System_getProcName(SYSTEM_GET_PROC_ID(linkId)),
                 SYSTEM_GET_LINK_ID(linkId), status);
            UTILS_assert((Bool)FALSE);
        }

        /* Loop and try sending message again in case no Notify_S_SUCCESS but
         * after a short sleep to allow other tasks to run
         */
        if(status != IPCLIB_SOK)
        {
            Task_sleep(5U);
        }
    }
    while(status != IPCLIB_SOK);

    if(status == IPCLIB_SOK)
    {
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Utility to initialize notify sub-system for links and chains
 *        work.
 *
 *        Initialize the notify event for local processor. It also registers
 *        callback with notify sub-system to get notify events from remote
 *        processor.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyRegister(void)
{
    UInt32 procId, i, ipcLibProcId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 errorProcId = SYSTEM_PROC_INVALID;
    volatile Int32 j = 1;

    i = 0;
    while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
    {
        procId = gSystem_ipcEnableProcId[i];
        if ((procId != System_getSelfProcId()) &&
            (procId != SYSTEM_PROC_INVALID))
        {
            Vps_printf
                (" SYSTEM: IPCLIB: register to [%s] event %d... \n",
                 System_getProcName(procId),
                 SYSTEM_IPC_NOTIFY_EVENT_ID);

            ipcLibProcId = System_getIpcLibProcId(procId);

            if(status == SYSTEM_LINK_STATUS_SOK)
            {
                status = IpcLib_interruptRegisterEvent(
                                ipcLibProcId,
                                SYSTEM_IPC_NOTIFY_EVENT_ID,
                                (IpcLib_InterruptCallback) (&System_safeIpcHandler),
                                NULL);
                /*
                * MISRA.CAST.PTR_TO_INT
                * MISRAC_2004_Rule_11.3: Cast between a pointer and an integral type
                * KW State: Defer -> Waiver -> Case by case
                *
                */
                /*
                * MISRA.CAST.PTR
                * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                * and a different pointer to object type
                * KW State: Defer -> Waiver -> Case by case
                */
                if(status != IPCLIB_SOK)
                {
                    /* Removed UTILS_assert() to avoid Task_sleep */
                    errorProcId = procId;
                    status = SYSTEM_LINK_STATUS_EFAIL;
                }
            }
            if(status != SYSTEM_LINK_STATUS_SOK)
            {
                break;
            }
        }
        i++;
    }
    if(errorProcId != SYSTEM_PROC_INVALID)
    {
        Vps_printf(" SYSTEM: System_ipcNotifyRegister failed for proc %s\n",
                     System_getProcName(errorProcId));
        do
        {
        }while(j);
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Utility to un-initialize notify sub-system for links and chains
 *        work.
 *
 *        Unregisters event
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyUnregister(void)
{
    UInt32 procId, ipcLibProcId;
    UInt32 i = 0U;
    Int32 status = SYSTEM_LINK_STATUS_SOK;


    while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
    {
        procId = gSystem_ipcEnableProcId[i];
        if ((procId != System_getSelfProcId()) &&
            (procId != SYSTEM_PROC_INVALID))
        {
            ipcLibProcId = System_getIpcLibProcId(procId);
            status = IpcLib_interruptUnregisterEvent(ipcLibProcId,
                                                     SYSTEM_IPC_NOTIFY_EVENT_ID);

            /*
            * MISRA.CAST.PTR_TO_INT
            * MISRAC_2004_Rule_11.3: Cast between a pointer and an integral type
            * KW State: Defer -> Waiver -> Case by case
            *
            */
            UTILS_assert(status == IPCLIB_SOK);
        }
        i++;
    }

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Function to enable mailboxes forcefully. This is used when
 *        booting sequence is unconventional.
 *
 *
 * \return  None.
 *
 *******************************************************************************
 */
Void System_ipcNotifyReset(UInt32 procId)
{
    UInt32 ipcLibProcId;
    ipcLibProcId = System_getIpcLibProcId(procId);
    IpcLib_interruptEnable(ipcLibProcId);
}

/**
 *******************************************************************************
 *
 * \brief Function to setup safe ipc
 *
 * \return  None.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyInit(void)
{
    memset(gSystem_ipcObj.notifyCb, 0, sizeof(gSystem_ipcObj.notifyCb));

    Vps_printf(" SYSTEM: IPCLIB init in progress !!!\n");

    System_ipcInitConfig();
    System_ipcNotifyRegister();

    Vps_printf(" SYSTEM: IPCLIB init DONE !!!\n");
    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Utility to de-initialize notify sub-system for links and chains
 *        work.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success.
 *
 *******************************************************************************
 */
Int32 System_ipcNotifyDeInit(void)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    Vps_printf(" SYSTEM: IPCLIB de-init in progress !!!\n");

    status = System_ipcNotifyUnregister();
    System_ipcDeInitConfig();

    Vps_printf(" SYSTEM: IPCLIB Notify de-init DONE !!!\n");

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Utility to get ipclib procId
 *
 * \return  procId on success.
 *
 *******************************************************************************
 */

UInt32 System_getIpcLibProcId(UInt32 procId)
{
    UInt32  retVal;

    switch(procId)
    {
    #if defined (TDA2XX_BUILD)
        case SYSTEM_PROC_DSP1:
            retVal = (UInt32)IPCLIB_DSP1_ID;
        break;
        case SYSTEM_PROC_DSP2:
            retVal = (UInt32)IPCLIB_DSP2_ID;
        break;
        case SYSTEM_PROC_EVE1:
            retVal = (UInt32)IPCLIB_EVE1_ID;
        break;
        case SYSTEM_PROC_EVE2:
            retVal = (UInt32)IPCLIB_EVE2_ID;
        break;
        case SYSTEM_PROC_EVE3:
            retVal = (UInt32)IPCLIB_EVE3_ID;
        break;
        case SYSTEM_PROC_EVE4:
            retVal = (UInt32)IPCLIB_EVE4_ID;
        break;
        case SYSTEM_PROC_IPU1_0:
            retVal = (UInt32)IPCLIB_IPU1_0_ID;
        break;
        case SYSTEM_PROC_IPU1_1:
            retVal = (UInt32)IPCLIB_IPU1_1_ID;
        break;
        case SYSTEM_PROC_IPU2:
            retVal = (UInt32)IPCLIB_IPU2_0_ID;
        break;
        case SYSTEM_PROC_A15_0:
            retVal = (UInt32)IPCLIB_A15_0_ID;
        break;
    #elif defined (TDA3XX_BUILD)
        case SYSTEM_PROC_DSP1:
            retVal = (UInt32)IPCLIB_DSP1_ID;
        break;
        case SYSTEM_PROC_DSP2:
            retVal = (UInt32)IPCLIB_DSP2_ID;
        break;
        case SYSTEM_PROC_EVE1:
            retVal = (UInt32)IPCLIB_EVE1_ID;
        break;
        case SYSTEM_PROC_IPU1_0:
            retVal = (UInt32)IPCLIB_IPU1_0_ID;
        break;
        case SYSTEM_PROC_IPU1_1:
            retVal = (UInt32)IPCLIB_IPU1_1_ID;
        break;
    #elif defined (TDA2EX_BUILD)
        case SYSTEM_PROC_DSP1:
            retVal = (UInt32)IPCLIB_DSP1_ID;
        break;
        case SYSTEM_PROC_IPU1_0:
            retVal = (UInt32)IPCLIB_IPU1_0_ID;
        break;
        case SYSTEM_PROC_IPU1_1:
            retVal = (UInt32)IPCLIB_IPU1_1_ID;
        break;
        case SYSTEM_PROC_IPU2:
            retVal = (UInt32)IPCLIB_IPU2_0_ID;
        break;
        case SYSTEM_PROC_A15_0:
            retVal = (UInt32)IPCLIB_A15_0_ID;
        break;
    #elif defined (TDA2PX_BUILD)
        case SYSTEM_PROC_DSP1:
            retVal = (UInt32)IPCLIB_DSP1_ID;
        break;
        case SYSTEM_PROC_DSP2:
            retVal = (UInt32)IPCLIB_DSP2_ID;
        break;
        case SYSTEM_PROC_EVE1:
            retVal = (UInt32)IPCLIB_EVE1_ID;
        break;
        case SYSTEM_PROC_EVE2:
            retVal = (UInt32)IPCLIB_EVE2_ID;
        break;
        case SYSTEM_PROC_IPU1_0:
            retVal = (UInt32)IPCLIB_IPU1_0_ID;
        break;
        case SYSTEM_PROC_IPU1_1:
            retVal = (UInt32)IPCLIB_IPU1_1_ID;
        break;
        case SYSTEM_PROC_IPU2:
            retVal = (UInt32)IPCLIB_IPU2_0_ID;
        break;
        case SYSTEM_PROC_A15_0:
            retVal = (UInt32)IPCLIB_A15_0_ID;
        break;
    #endif
        default:
            retVal = (UInt32)IPCLIB_MAX_PROC;
        break;
    }

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief Configures IpcLib is IPC_LIB_INCLUDE if yes
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_ipcInitConfig(void)
{
    Int32 status = IPCLIB_SOK;
    UInt32 numprocs = 0U;

    IpcLib_InterruptInitPrms initPrm;
    IpcLib_interruptSetDefaultInitPrm(&initPrm);

    #if defined (TDA2XX_BUILD)
        #if defined (PROC_A15_0_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_A15_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_DSP1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_DSP1_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_0_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU2_INCLUDE) || (defined(AUTOSAR_APP) && defined( BUILD_M4_0))
            initPrm.validProcIds[numprocs] = IPCLIB_IPU2_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_DSP2_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_DSP2_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_1_ID;
            numprocs++;
        #endif
        #if defined (PROC_EVE1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_EVE1_ID;
            numprocs++;
        #endif
        #if defined (PROC_EVE2_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_EVE2_ID;
            numprocs++;
        #endif
        #if defined (PROC_EVE3_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_EVE3_ID;
            numprocs++;
        #endif
        #if defined (PROC_EVE4_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_EVE4_ID;
            numprocs++;
        #endif
    #elif defined (TDA3XX_BUILD)
        #if defined (PROC_DSP1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_DSP1_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_0_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_DSP2_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_DSP2_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_1_ID;
            numprocs++;
        #endif
        #if defined (PROC_EVE1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_EVE1_ID;
            numprocs++;
        #endif
    #elif defined (TDA2EX_BUILD)
        #if defined (PROC_A15_0_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_A15_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_DSP1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_DSP1_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_0_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_1_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU2_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU2_0_ID;
            numprocs++;
        #endif
    #elif defined (TDA2PX_BUILD)
        #if defined (PROC_A15_0_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_A15_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_DSP1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_DSP1_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_0_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU2_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU2_0_ID;
            numprocs++;
        #endif
        #if defined (PROC_DSP2_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_DSP2_ID;
            numprocs++;
        #endif
        #if defined (PROC_IPU1_1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_IPU1_1_ID;
            numprocs++;
        #endif
        #if defined (PROC_EVE1_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_EVE1_ID;
            numprocs++;
        #endif
        #if defined (PROC_EVE2_INCLUDE)
            initPrm.validProcIds[numprocs] = IPCLIB_EVE2_ID;
            numprocs++;
        #endif
    #endif
    initPrm.numValidProcs   = numprocs;
    initPrm.msgTimeOut      = 0xFFFF;

    status = IpcLib_interruptInit(&initPrm);
    UTILS_assert(status == IPCLIB_SOK);
}

/**
 *******************************************************************************
 *
 * \brief De-initializes IpcLib is IPC_LIB_INCLUDE if yes
 *
 * \return none
 *
 *******************************************************************************
 */
Void System_ipcDeInitConfig(void)
{
    IpcLib_interruptDeInit();
}


/**
 *******************************************************************************
 *
 * \brief Wrapper around Ipc_start function of IPC component.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcStart(void)
{
    /* Nothing to be done for IpcLib */
}

/**
 *******************************************************************************
 *
 * \brief Wrapper around Ipc_stop function of IPC component.
 *
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcStop(void)
{
    /* Nothing to be done for IpcLib */
}

/**
 *******************************************************************************
 *
 * \brief Attach local core to all cores for further IPC communication between
 *        cores
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcAttach(void)
{
    /* Nothing to be done for IpcLib */
}
/**
 *******************************************************************************
 *
 * \brief Detach local core to all cores for further IPC communication between
 *        cores
 *
 * \return  None
 *
 *******************************************************************************
 */
Void System_ipcDetach(void)
{
    /* Nothing to be done for IpcLib */
}

/**
 *******************************************************************************
 *
 * \brief Returns processor ID on which function is called.
 *
 *        Returns the processor id on which this function is getting called.
 *        Suppose code on DSP calls this function it returns processor id as
 *        DSP
 *
 * \return  ProcessorId for valid processor else SYSTEM_PROC_INVALID
 *
 *******************************************************************************
 */
UInt32 System_getSelfProcId(void)
{

    static UInt32 selfProcId = SYSTEM_PROC_INVALID;

    if(selfProcId!=SYSTEM_PROC_INVALID)
    {
        /*  find self proc ID only once, since it never changes run-time
        *  Doing this optimization since, this API is called for every
        *  System_linkXxxx API
        */
    }
    else
    {
        /* Doesn't use IpcLib to avoid proc name confilcts */

        #if defined (BUILD_A15)
             selfProcId = SYSTEM_PROC_A15_0;
        #endif
        #if defined (BUILD_DSP_1)
             selfProcId = SYSTEM_PROC_DSP1;
        #endif
        #if defined (BUILD_M4_0)
             selfProcId = SYSTEM_PROC_IPU1_0;
        #endif
        #if defined (BUILD_M4_2)
             selfProcId = SYSTEM_PROC_IPU2;
        #endif
        #if defined (BUILD_DSP_2)
             selfProcId = SYSTEM_PROC_DSP2;
        #endif
        #if defined (BUILD_M4_1)
             selfProcId = SYSTEM_PROC_IPU1_1;
        #endif
        #if defined (BUILD_ARP32_1)
             selfProcId = SYSTEM_PROC_EVE1;
        #endif
        #if defined (BUILD_ARP32_2)
             selfProcId = SYSTEM_PROC_EVE2;
        #endif
        #if defined (BUILD_ARP32_3)
             selfProcId = SYSTEM_PROC_EVE3;
        #endif
        #if defined (BUILD_ARP32_4)
             selfProcId = SYSTEM_PROC_EVE4;
        #endif
    }
    return selfProcId;
}

