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
 * \ingroup UTILS_API
 * \defgroup UTILS_REMOTE_LOG_IF_API Remote Log Interface
 *
 *         Remote log allows debugging a core by exporting it's logs to
 *         any other core dynamically.
 *
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \file remote_log_if.h
 *
 * \brief  Remote Log Interface
 *
 *******************************************************************************
 */

#ifndef _REMOTE_LOG_IF_
#define _REMOTE_LOG_IF_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Max allowed parameter buffer size
 *
 *******************************************************************************
*/
#define REMOTE_LOG_PARAM_BUF_SIZE   (1024U)

/**
 *******************************************************************************
 *
 * \brief Size of log buffer
 *
 *******************************************************************************
*/
#define REMOTE_LOG_LOG_BUF_SIZE     (158U*1024U)

/**
 *******************************************************************************
 *
 * \brief Tag used to identify remote log object
 *        Used to check log object is valid or not
 *
 *******************************************************************************
*/
#define REMOTE_LOG_HEADER_TAG       (0U)

/**
 *******************************************************************************
 *
 * \brief Flag to indicate a character is requested or returned
 *
 *******************************************************************************
*/
#define REMOTE_LOG_FLAG_TYPE_CHAR    (0x01000000U)

/**
 *******************************************************************************
 *
 * \brief Flag to indicate a string is requested or returned
 *
 *******************************************************************************
*/
#define REMOTE_LOG_FLAG_TYPE_STRING  (0x10000000U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 ********************************************************************************
 *
 *  \brief  Enumerations for the core's initialization states
 *          Deliberately starting with a non-zero enum value as this state is a
 *          value of shared memory variable, it can 0 at initialization time.
 *
 ********************************************************************************
*/
typedef enum
{
    CORE_APP_INITSTATUS_DO_EXIT = 3,
    /**< Trigger from host to exit app */
    CORE_APP_INITSTATUS_EXIT_DONE = 4,
    /**< State to indicate app exit is complete */
    CORE_APP_INITSTATUS_INIT_DONE = 5,
    /**< State to indicate core has come up */
    CORE_APP_INITSTATUS_TEST_INIT_DONE = 6,
    /**< State to indicate core has initialized */
    CORE_APP_INITSTATUS_CONFIRM_INIT_DONE = 7
    /**< State to indicate transition to init state is successful */

} CoreApp_InitializationState;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 *  \brief  Structure for remote log object.
 *
 *          This structure is used by a remote core to store information about
 *          log buffer. This log buffer is a shared memory, through which other
 *          cores can see logs of this core
 *******************************************************************************
*/

typedef struct
{
    volatile unsigned int headerTag;
    /**< Tag used to identify remote log object
     *    Used to check log object is valid or not */
    volatile unsigned int serverIdx;
    /**< Write pointer. As the core logs this keeps incrementing */
    volatile unsigned int clientIdx;
    /**< Read pointer. As other core reads the log this keeps incrementing */
    volatile unsigned int appInitState;
    /** < Flag indicating application initialization status */
} RemoteLog_MemInfo;

typedef struct
{
    RemoteLog_MemInfo memInfo[SYSTEM_PROC_MAX];
    /**< Shared memory information for each core */
    volatile unsigned char serverLogBuf[REMOTE_LOG_LOG_BUF_SIZE];
    /** < log buffer into which all logs from the core go into */
} RemoteLog_CoreObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure stores start index and size information.
 *
 *          The number of link stats objects and performance stats objects
 *          are different for each core. There is a big array of
 *          link stats and performance objects allocated in
 *          #System_LinkStatsCoreObj. This structure is used to get
 *          start index and number of instances into this big array
 *          for each core.
 *******************************************************************************
*/
typedef struct
{
    UInt32 startIdx;
    /**< Start Index */
    UInt32 size;
    /**< Number of instances */
} RemoteLog_ServerIndexInfo;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Initializes remote log client.
 *
 * Creates periodic task for printing the logs from remote server.
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
Int32 OSA_remoteLogClientInit(void);

/**
 *******************************************************************************
 *
 * \brief de-Initializes remote log client.
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
Int32 OSA_remoteLogClientDeInit(void);

/**
 *******************************************************************************
 *
 * \brief This function is used for initiating remote log server.
 *
 * \param  coreId   [IN] Id of the core to log
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
int RemoteLog_init(void);

/**
 *******************************************************************************
 *
 * \brief Return the application initialization state of the
 *        specified core
 *
 * \param pState    [OUT] Application initialization state
 * \param coreId    [IN]  Id of the core
 *
 * \return returns 0 on success
 *
 *******************************************************************************
 */
int RemoteLog_getAppInitState(int coreId, unsigned int *pState);

/**
 *******************************************************************************
 *
 * \brief Set the application initialization state of the
 *        specified core
 *
 * \param coreId    [IN] Core ID of the core to send the char
 * \param state     [IN] Value of the application intialization state to set
 *
 * \return returns 0 on success
 *
 *******************************************************************************
 */
int RemoteLog_setAppInitState(int coreId, unsigned int state);

/**
 *******************************************************************************
 *
 * \brief Return Index information for the given core
 *
 * \param coreId    [IN]  Id of the core
 *
 * \return returns 0 on success
 *
 *******************************************************************************
 */
RemoteLog_ServerIndexInfo *RemoteLog_getCoreIdxInfo(int coreId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
