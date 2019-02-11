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
 * \ingroup FRAMEWORK_MODULE_API
 * \defgroup SYSTEM_LINK_API System Link API
 *
 *
 * @{
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file   system.h
 *
 * \brief  System Link API
 *
 *   The APIs defined in this module are used to create links and connect
 *   them to each other to form a chain
 *
 *   A unique 32-bit link ID is used to send commands to specific links.
 *
 *******************************************************************************
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */


#if defined(LINUX_BUILD) || defined(QNX_BUILD)
#include <links_fw/src/hlos/osa/include/osa_types.h>
#endif

#if defined(BIOS_BUILD)
#include <xdc/std.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <include/link_api/system_trace.h>
#endif

#include <include/link_api/system_debug.h>
#include <include/link_api/system_linkId.h>
#include <include/link_api/system_const.h>
#include <include/link_api/system_const_vip.h>
#include <include/link_api/system_const_displayCtrl.h>
#include <include/link_api/system_link_info.h>
#include <include/link_api/system_if.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* None */


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Specifies memory alloc information that a link should use.
 *
 *        This is used to allow user to pass memory allocation pointer rather
 *        than having a link alloc the memory using dynamic memory allocation.
 *
 *        This allows users to alloc memory statically and then pass the
 *        pointers to the link.
 *
 *        If size of memory passed is less than required size then the link
 *        will assert with error log. In this case user is supposed to
 *        increase the memory allocation and try again.
 *
 *        It is recommended that the memory region address and memory region
 *        size be aligned to worst case cache line size of all CPUs present
 *        in the system. This is because the buffers can be passed to different
 *        CPUs in the system which may use this memory in cache mode. If memory
 *        is not cache line aligned, then cache operation like Writeback can
 *        corrupt memory not associated with this region and therefore causes
 *        unexpected side-effects.
 *
 *        Ex, 128B alignment is safe alignment to use in TDAxxx SoCs
 *
 *        When 'memAddr' and 'memSize' is set to 0, a link
 *        will use dynamic memory alloc
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 memAddr;
    /**< Start address of memory region, MUST physical memory address
     *   MUST be set by user when user wants link to
     *   use user provided memory allocation
     */

    UInt32 memSize;
    /**< size of memory region in units of bytes
     *   MUST be set by user when user wants link to
     *   use user provided memory allocation
     */

    UInt32 memAllocOffset;
    /**< Should be ignored by user, used internally
     */

} System_LinkMemAllocInfo;

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */
static inline void System_LinkInQueParams_Init(System_LinkInQueParams *pPrm);
static inline UInt32 SystemUtils_align(UInt32 val, UInt32 align);
static inline UInt32 SystemUtils_floor(UInt32 val, UInt32 align);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

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
Int32 System_init(void);

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
Int32 System_deInit(UInt32 shutdownRemoteProcs);

/**
 *******************************************************************************
 *
 *  \brief Create a link
 *
 *   Note, links of a chain should be created in
 *   start (source) to end (sink) order.
 *
 *   Example, in a capture + display chain.
 *
 *   The capture link is the source and should be created
 *   before the display link which is the sink for the source data.
 *
 *   Create only create the link, driver, buffer memory
 *   and other related resources.
 *
 *   Actual data transfer is not started when create is done.
 *
 * \param linkId       [IN] ID of the link which is to be created.
 * \param createArgs   [IN] Create time link specific arguments
 * \param argsSize     [IN] Size of argument
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkCreate(UInt32 linkId, Ptr createArgs, UInt32 argsSize);

/**
 *******************************************************************************
 *
 * \brief Start the link
 *
 *   The makes the link start generating or consuming data.
 *
 *   Note, the order of starting links of a chain depend on
 *   specific link implementation.
 *
 * \param linkId       [IN] link ID to be started
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkStart(UInt32 linkId);

/**
 *******************************************************************************
 *
 * \brief Stop the link
 *
 *   The makes the link stop generating or consuming data.
 *
 *   Note, the order of starting links of a chain depend on
 *   specific link implementation.
 *
 * \param linkId       [IN] link ID to be stopped
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkStop(UInt32 linkId);

/**
 *******************************************************************************
 *
 * \brief Delete the link
 *
 *   A link must be in stop state before it is deleted.
 *
 *   The links of a chain can be deleted in any order.
 *
 * \param linkId       [IN] link ID to be deleted
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkDelete(UInt32 linkId);

/**
 *******************************************************************************
 *
 * \brief Print link statistics
 *
 * \param linkId       [IN] link ID
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkPrintStatistics(UInt32 linkId);

/**
 *******************************************************************************
 *
 * \brief Print Display Error Stats
 *
 *******************************************************************************
 */
Void System_printDisplayErrorStats(void);


/**
 *******************************************************************************
 *
 * \brief Print link buffer related statistics
 *
 * \param linkId       [IN] link ID
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkPrintBufferStatistics(UInt32 linkId);

/**
 *******************************************************************************
 *
 * \brief Send a control command to a link
 *
 *   The link must be created before a control command could be sent.
 *   It need not be in start state for it to be able to received
 *   a control command
 *
 * \param linkId       [IN] link ID for which control command is intended
 * \param cmd          [IN] Link specific command ID
 * \param pPrm         [IN] Link specific command parameters
 * \param prmSize      [IN] Size of the parameter
 * \param waitAck      [IN] TRUE: wait until link ACKs the sent command,
 *                          FALSE: return after sending command
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkControl(UInt32 linkId,
                         UInt32 cmd,
                         Void *pPrm,
                         UInt32 prmSize,
                         Bool waitAck);

/**
 *******************************************************************************
 *
 * \brief Send a control command to a link
 *
 *   The link must be created before a control command could be sent.
 *   It need not be in start state for it to be able to received
 *   a control command
 *
 * \param linkId       [IN] link ID for which control command is intended
 * \param cmd          [IN] Link specific command ID
 * \param pPrm         [IN] Link specific command parameters
 * \param prmSize      [IN] Size of the parameter
 * \param waitAck      [IN] TRUE: wait until link ACKs the sent command,
 *                          FALSE: return after sending command
 * \param timeout      [IN] Waiting time, how long function should wait to get
 *                          ACK from recipient link.
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkControlWithTimeout(UInt32 linkId,
                                    UInt32 cmd,
                                    Void *pPrm,
                                    UInt32 prmSize,
                                    Bool waitAck,
                                    UInt32 timeout);

/**
 *******************************************************************************
 *
 * \brief Get information about a link
 *
 *  The link must have been created.
 *  Usually used in the succeeding link in the chain to query the queue
 *  information
 *
 * \param linkId        [IN]   Get the information for the Link ID
 * \param info          [OUT]  Information about the link.
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_linkGetInfo(UInt32 linkId, System_LinkInfo *info);

/**
 *******************************************************************************
 *
 * \brief Export System buffer as DMABuff
 *
 *  The Api is used only in linux .
 *  Linux 4.4 kernel needs buff fd instead of phy/vert addr
 *
 *
 * \param vAddr         [IN] Address of the buffer
 * \param size          [IN] Size of the buffer.
 * \param fdBuf         [IN] buffFd to which created fd is to be assigned.
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_exportDmaBuf(void * vAddr, UInt32 size, UInt32 *fdBuf);

/**
 *******************************************************************************
 *
 * \brief Initialize In queue parameters of a link
 *
 * \param pPrm       [IN]     In Queue parameters
 *
 * \return SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void System_LinkInQueParams_Init(System_LinkInQueParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    pPrm->prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->prevLinkQueId = 0U;
}


/**
 *******************************************************************************
 *
 * \brief Initialize In queue parameters of a link
 *
 * \param val         [IN]   Value to be rounded off
 *
 * \param align       [IN]   Value to which val to be rounded
 *
 * \return aligned value of val
 *
 *******************************************************************************
 */
static inline UInt32 SystemUtils_align(UInt32 val, UInt32 align)
{
    UInt32 retVal;
    retVal = SystemUtils_floor(((val) + ((align)- 1U)), (align));

    return retVal;
}

/**
 *******************************************************************************
 *
 * \brief Initialize In queue parameters of a link
 *
 * \param val         [IN]   Value to be rounded off
 *
 * \param align       [IN]   Value to which val to be rounded
 *
 * \return aligned value of val
 *
 *******************************************************************************
 */
static inline UInt32 SystemUtils_floor(UInt32 val, UInt32 align)
{
    return (((val) / (align)) * (align));
}


/**
 *******************************************************************************
 *
 * \brief Return if a processor is enabled in this system
 *
 * \param procId    [IN] processor ID SYSTEM_PROC_xxx
 *
 * \return TRUE, processor is enabled in this system, else FALSE
 *
 *******************************************************************************
 */
Bool System_isProcEnabled(UInt32 procId);

/**
 *******************************************************************************
 *
 * \brief Returns the processor name given a valid LCFW processor ID.
 *
 * \param   procId     [IN] Processor ID for which the processor name is needed
 *
 * \return  Name of the processor if valid processor ID is given
 *          else SYSTEM_IPC_PROC_NAME_INVALID
 *
 *******************************************************************************
 */
char *System_getProcName(UInt32 procId);

/**
 *******************************************************************************
 *
 * \brief Return if user provide memory alloc info should be used
 *
 * \param info          [IN] User memory alloc info
 *
 * \return TRUE, System_LinkMemAllocInfo should be used by the link, else FALSE
 *
 *******************************************************************************
 */
UInt32 System_useLinkMemAllocInfo(const System_LinkMemAllocInfo *info);


/**
 *******************************************************************************
 *
 * \brief Assert if user provided memory region size does not meet link memory
 *        requirements
 *
 * \param info          [IN] User memory alloc info
 * \param linkName      [IN] Link name, MUST not be NULL
 *
 *******************************************************************************
 */
Void System_assertLinkMemAllocOutOfMem(
                    System_LinkMemAllocInfo *info,
                    char *linkName);

/**
 *******************************************************************************
 *
 * \brief Reset internal state of user memory alloc info
 *
 * \param info          [IN] User memory alloc info
 *
 *******************************************************************************
 */
Void System_resetLinkMemAllocInfo(System_LinkMemAllocInfo *info);

/**
 *******************************************************************************
 *
 * \brief Get address of memory from user memory alloc info based on
 *        memory allocation done so far
 *
 * \param info          [IN] User memory alloc info
 * \param size          [IN] Amount of memory requested
 * \param align         [IN] Alignment required
 *
 *******************************************************************************
 */
Ptr System_allocLinkMemAllocInfo(System_LinkMemAllocInfo *info,
                UInt32 size,
                UInt32 align);


Bool System_isFastBootEnabled(void);
Bool System_isSrvFastBootEnabled(void);
Bool System_isHLOSFastBootEnabled(void);

#ifdef  __cplusplus
}
#endif

#endif

/*@}*/


/*
 *******************************************************************************
 *
 *   \defgroup LINK_API_CMD Link API Control Commands
 *
 *   This module lists all commands that can be sent using the link API.
 *   Each command can be related to a different link like capture, display etc.
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \mainpage VISION SDK
 *
 * \par IMPORTANT NOTE
 *
 *    <b>
 *    The interfaces defined in this package are bound to change.
 *    Kindly treat the interfaces as work in progress.
 *    Release notes/user guide list the additional limitation/restriction
 *    of this module/interfaces.
 *   </b> \n
 *    See also \ref TI_DISCLAIMER.
 *
 * \par Introduction
 *
 *   VISION SDK is a multi processor software development platform for TI family
 *   of ADAS SoCs. The software framework allows users to create different ADAS
 *   application data flows involving video capture, video pre-processing,
 *   video analytics algorithms, and video display.
 *
 *   The framework has sample ADAS data flows which exercises different CPUs
 *  and HW accelerators in the ADAS SoC and shows customer how to effectively
 *   use different sub-systems in the SoC.
 *
 *   The VISION SDK is currently targeted for the below ADAS SoCs
 *   - TDA2xx family of ADAS SoCs
 *   - TDA3xx family of ADAS SoCs
 *   - TDA2Ex family of ADAS SoCs
 *
 *   See the following documents for more details or release specific details.
 *   - Release Notes
 *   - User Guide
 *
 *   VISION SDK is based on a framework called "Links and Chains". A link is
 *   the basic processing step in a video data flow. A link consists of a OS
 *   thread coupled with a message box (implemented using OS semaphores).
 *   Since each link runs as a separate thread, links can run in parallel to
 *   each other.
 *   The message box associated with a link allows user application as well
 *   as other links to talk to that link. The link implements a specific
 *   interface which allows other links to exchange video frames and/or
 *   bit streams with the link.
 *
 *   Link API allows user to create, control and connect the links. Link API can
 *   be talk to control links on different processors. User of Link API need not
 *   worry about the lower level inter processor communication details
 *
 *   A connection of links is called a chain.
 *   A chain is created on a processor designated as HOST CPU
 *   (IPU1-M4-0 in case of TDA2xx, TDA3xx family of ADAS SoCs)
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \page  TI_DISCLAIMER  TI Disclaimer
 *
 * \htmlinclude ti_disclaim.htm
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \defgroup  ALGORITHM_LINK_PLUGIN  Algorithm Plugin's
 *
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \defgroup  SAMPLE_MODULE_API  Sample Module's
 *
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \defgroup  FRAMEWORK_MODULE_API  Framework Module's
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \defgroup  SAMPLE_LINUX_MODULE_API Vision SDK Linux Module's
 *
 *******************************************************************************
 */

