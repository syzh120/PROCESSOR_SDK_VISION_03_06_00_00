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
 *  \ingroup FRAMEWORK_MODULE_API
 *  \defgroup PROCESSOR_LINK_API Processor Link API
 *
 *   Processor Link is a link which is created on every processor to handle
 *   generic commands which do not fall into any specific pre-defined link
 *   category like capture or display. This interface allows user/developer to
 *   extend new commands in the system without having to create a new link
 *   everytime. Normally this link does not exchange frames and usually
 *   handles control commands only.
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 *   \ingroup PROCESSOR_LINK_API
 *   \defgroup SYSTEM_COMMON_LINK_API Processor Link API: Common Interfaces
 *
 *   This module defines the control commands that are applicable to
 *   all processors running in the system.
 *
 *   @{
*/

/**
 *
 *******************************************************************************
 *
 *   \file systemLink_common.h
 *   \brief Processor Link API: Common Interfaces
 *
 *******************************************************************************
*/


#ifndef SYSTEM_LINK_COMMON_H_
#define SYSTEM_LINK_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <include/link_api/system.h>
#include <include/link_api/systemLink_common_if.h>

/**
 *******************************************************************************
 *
 *  \ingroup LINK_API_CMD
 *  \addtogroup SYSTEM_COMMON_CMD Processor Link API: Common Control Commands
 *
 *   @{
*/

/**
 *******************************************************************************
 *
 *  \brief System CMD: Start CPU load computation
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_CPU_LOAD_CALC_START       (0x9000U)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Stop CPU load computation
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_CPU_LOAD_CALC_STOP       (0x9001U)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Reset CPU load computation
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_CPU_LOAD_CALC_RESET      (0x9002U)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Print CPU load information
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_CPU_LOAD_CALC_PRINT      (0x9003U)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Print CPU load, Task Load and Heap status information
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_PRINT_STATUS             (0x9004U)

/**
 *******************************************************************************
 *
 *  \brief Check's if core is active or not
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_CORE_STATUS               (0x9005U)

/**
 *******************************************************************************
 *
 *  \brief Gets Load on this core
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_GET_LOAD                  (0x9006U)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Run EDMA LLD standalone tests
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_RUN_DMA_TEST              (0x9007U)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Print Statistics standalone tests
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_PRINT_STAT_COLL              (0x9008U)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Reset Statistics standalone tests
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_RESET_STAT_COLL              (0x9009U)


/**
 *******************************************************************************
 *
 *  \brief System CMD: Get IP address of the system, if enabled
 *
 *  \param SystemCommon_IpAddr  [OUT] System IP address
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_GET_IP_ADDR                 (0x900AU)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Allocate buffer from heaps associated with System_HeapId
 *
 *  \param SystemCommon_AllocBuffer  [OUT] bufferPtr physical address
 *  \param SystemCommon_AllocBuffer  [IN]  System_heapId
 *  \param SystemCommon_AllocBuffer  [IN]  size
 *  \param SystemCommon_AllocBuffer  [IN]  align
 *
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_ALLOC_BUFFER                (0x900BU)
/**
 *******************************************************************************
 *
 *  \brief System CMD: Free buffer from heaps associated with System_HeapId
 *
 *  \param SystemCommon_FreeBuffer  [IN] bufferPtr physical address
 *  \param SystemCommon_FreeBuffer  [IN] System_heapId
 *  \param SystemCommon_FreeBuffer  [IN] size
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_FREE_BUFFER                 (0x900CU)


/**
 *******************************************************************************
 *
 *  \brief System CMD: Get proc Id where NDK is running
 *
 *  \param SystemCommon_NetProcId  [OUT] procId
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_NET_PROC_ID                  (0x900DU)

/**
 *******************************************************************************
 *
 *  \brief System CMD: Test the timers of all enabled core
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_RUN_TIMER_TEST                 (0x9010U)


/**
 *******************************************************************************
 *
 *  \brief Gets Load on SGX core
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_GET_SGX_LOAD                   (0x901AU)

/**
 *******************************************************************************
 *
 *  \brief Get Heap Stats from IPU - to be called from other cores
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_GET_HEAP_STATS                 (0x901BU)

/**
 *******************************************************************************
 *
 *  \brief Return current time in units of timer counter value
 *
 *  \param SystemCommon_GlobalTime [out] global time on this CPU in units
 *                                       of timer counter value
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_GET_GLOBAL_TIME               (0x901CU)

/**
 *******************************************************************************
 *
 *  \brief Updates rendered view of SRV
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_UPDATE_RENDER_VIEW            (0x901DU)

/**
 *******************************************************************************
 *
 *  \brief Print Display Error Stats
 *
 *  \param NONE
 *
 *******************************************************************************
*/
#define SYSTEM_COMMON_CMD_PRINT_DISPLAY_ERROR_STATS     (0x901EU)

/* @} */

/*******************************************************************************
 *  Define's
 *******************************************************************************
 */
#define SYSTEM_COMMON_MAX_CMD_HANDLERS                (8U)

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief Callback to handle user defined commands
 *
 *  \param cmd [IN] Command that needs to be handled
 *  \param pPrm [IN/OUT] Parameters for this command
 *
 *******************************************************************************
 */
typedef Void (*SystemLink_CmdHandler)(UInt32 cmd, Void *pPrm);

/**
 *******************************************************************************
 *
 *  \brief System Common: Print CPU load, Task Load and Heap Staus..
 *
 *   Defines System Common parameters that are passed when system statistics
 *   print is requested..
 *
 *******************************************************************************
*/

typedef struct {

    UInt32 printCpuLoad;
    /**< [IN] Print CPU load of each core */

    UInt32 printTskLoad;
    /**< [IN] Print CPU loading of each Task*/

    UInt32 printHeapStatus;
    /**< [IN] Print Current Heap status of core*/

} SystemCommon_PrintStatus;


/**
 *******************************************************************************
 *
 *  \brief IP address of system
 *
 *******************************************************************************
 */
typedef struct {

    char ipAddr[32U];
    /**< IP address of the system as string */
    UInt32 ifIdx;
    /**< Index specifying which interface */
} SystemCommon_IpAddr;

/**
 *******************************************************************************
 *
 *  \brief SystemCommon_AllocBuffer defines parameters used to
 *         allocates buffer from IPU managed heap
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 bufferPtr;
    /**< [OUT] pointer to allocated buffer */
    UInt32 heapId;
    /**< [IN] Heap id of the heap to allocate from */
    UInt32 size;
    /**< [IN] Size of the buffer to be allocated */
    UInt32 align;
    /**< [IN] Alignment of the allocated buffer */
} SystemCommon_AllocBuffer;

/**
 *******************************************************************************
 *
 *  \brief SystemCommon_AllocBuffer defines parameters used to
 *         free buffer from IPU managed heap
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 bufferPtr;
    /**< [IN] pointer to allocated buffer */
    UInt32 heapId;
    /**< [IN] Heap id of the heap to allocate from */
    UInt32 size;
    /**< [IN] Size of the buffer to be allocated */
} SystemCommon_FreeBuffer;

/**
 *******************************************************************************
 *
 *  \brief IP address of system
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 procId;
    /**< procId where NDK is running */

} SystemCommon_NetProcId;


/**
 *******************************************************************************
 *
 *  \brief 64-bit Global timer counter value
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 timeH;
    /**< 32bit high value of timer coutner */
    UInt32 timeL;
    /**< 32bit low value of timer coutner */
} SystemCommon_GlobalTime;


/*******************************************************************************
 *  Function's
 *******************************************************************************
 */




/**
 *******************************************************************************
 *  \brief Register user defined command handler in System Link
 *
 *         Multiple handler can be registered
 *         All handlers are called when a command is received
 *         Unsupported command should be ignored in handler
 *
 *  \param handler [IN] User defined handler
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 SystemLink_registerHandler(SystemLink_CmdHandler handler);

/**
 *******************************************************************************
 *  \brief Un-Register user defined command handler in System Link
 *
 *  \param handler [IN] User defined handler to unregister
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 SystemLink_unregisterHandler(SystemLink_CmdHandler handler);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/


