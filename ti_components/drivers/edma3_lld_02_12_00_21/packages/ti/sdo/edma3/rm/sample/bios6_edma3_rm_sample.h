/*
 * bios6_edma3_rm_sample.h
 *
 * Header file for the Demo application for the EDMA3 Resource Manager.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef BIOS6_EDMA3_RM_SAMPLE_H_
#define BIOS6_EDMA3_RM_SAMPLE_H_

#include <ti/sysbios/knl/Semaphore.h>

#include <ti/sdo/edma3/rm/edma3_rm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* To enable debug traces in the EDMA3 sample app */
/* Nowhere this macro is used, undefined to remove Misra C warning */

/* #define EDMA3_DEBUG_PRINT  */

#ifdef EDMA3_DEBUG_PRINT
#include <stdio.h>
#define EDMA3_DEBUG_PRINTF printf
#endif /* EDMA3_DEBUG_PRINT */

/**
 * Cache line size on the underlying SoC. It needs to be modified
 * for different cache line sizes, if the Cache is Enabled.
 */
#define EDMA3_CACHE_LINE_SIZE_IN_BYTES      (128u)

/* Error returned in case of buffers are not aligned on the cache boundary */
#define EDMA3_NON_ALIGNED_BUFFERS_ERROR     (-1)

/* Error returned in case of data mismatch */
#define EDMA3_DATA_MISMATCH_ERROR           (-2)

/**
 * \brief   EDMA3 Initialization
 *
 * This function initializes the EDMA3 Resource Manager for the given EDMA3 controller
 * and opens a EDMA3 RM instance. It internally calls EDMA3_RM_create() and
 * EDMA3_RM_open(), in that order.
 *
 * It also registers interrupt handlers for various EDMA3 interrupts like 
 * transfer completion or error interrupts.
 *
 *  \param  edma3Id 	[IN]		EDMA3 Controller Instance Id (Hardware
 *									instance id, starting from 0)
 *  \param  errorCode 	[IN/OUT]	Error code while opening RM instance
 *  \return EDMA3_RM_Handle: If successfully opened, the API will return the
 *                            associated RM's instance handle.
 */
EDMA3_RM_Handle edma3init (uint32_t edma3Id, EDMA3_RM_Result *errorCode);

/**
 * \brief   EDMA3 De-initialization
 *
 * This function de-initializes the EDMA3 RM for the given EDMA3 controller
 * and closes the previously opened EDMA3 RM instance. It internally calls 
 * EDMA3_RM_close and EDMA3_RM_delete(), in that order.
 *
 * It also un-registers the previously registered interrupt handlers for various 
 * EDMA3 interrupts.
 *
 *  \param  edma3Id 	[IN]		EDMA3 Controller Instance Id (Hardware
 *									instance id, starting from 0)
 *  \param  hEdma		[IN]		EDMA3 RM handle, returned while using
 *									edma3init().
 *  \return  EDMA3_RM_SOK if success, else error code
 */
EDMA3_RM_Result edma3deinit (uint32_t edma3Id, EDMA3_RM_Handle hEdma);

/**
 * Counting Semaphore related functions (OS dependent) should be
 * called/implemented by the application. A handle to the semaphore
 * is required while opening the driver/resource manager instance.
 */

/**
 * \brief   EDMA3 OS Semaphore Create
 *
 *      This function creates a counting semaphore with specified
 *      attributes and initial value. It should be used to create a semaphore
 *      with initial value as '1'. The semaphore is then passed by the user
 *      to the EDMA3 RM for proper sharing of resources.
 * \param   initVal [IN] is initial value for semaphore
 * \param   attrs [IN] is the semaphore attributes ex: Fifo type
 * \param   hSem [OUT] is location to recieve the handle to just created
 *      semaphore
 * \return  EDMA3_RM_SOK if succesful, else a suitable error code.
 */
EDMA3_RM_Result edma3OsSemCreate(int32_t initVal,
							const Semaphore_Params *semParams,
                           	EDMA3_OS_Sem_Handle *hSem);

/**
 * \brief   EDMA3 OS Semaphore Delete
 *
 *      This function deletes or removes the specified semaphore
 *      from the system. Associated dynamically allocated memory
 *      if any is also freed up.
 * \warning OsSEM services run in client context and not in a thread
 *      of their own. If there exist threads pended on a semaphore
 *      that is being deleted, results are undefined.
 * \param   hSem [IN] handle to the semaphore to be deleted
 * \return  EDMA3_RM_SOK if succesful else a suitable error code
 */
EDMA3_RM_Result edma3OsSemDelete(EDMA3_OS_Sem_Handle hSem);

/**
 * \brief   enableXferCompInterrupt
 *
 * This function enables the tranfer completion interrupt of EDMA3.
 *
 */
void enableXferCompInterrupt(uint32_t edma3Id);

/**
 * \brief   disableXferCompInterrupt
 *
 * This function disables the tranfer completion interrupt of EDMA3.
 *
 */
void disableXferCompInterrupt(uint32_t edma3Id);

/**
 * \brief   enableErrorInterrupt
 *
 * This function enables the error interrupt of EDMA3.
 *
 */
void enableErrorInterrupt(uint32_t edma3Id);

/**
 * \brief   disableErrorInterrupt
 *
 * This function disables the error interrupt of EDMA3.
 *
 */
void disableErrorInterrupt(uint32_t edma3Id);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif

