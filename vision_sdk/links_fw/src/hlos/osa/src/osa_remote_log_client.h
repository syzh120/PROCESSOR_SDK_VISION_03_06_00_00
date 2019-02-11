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
 * \defgroup REMOTE_LOG_CLIENT    Remote log implementation
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \file Remote log client  header file.
 *
 * \brief  Internal header file for remote log client
 *
 * \version 0.1 (Jul 2013) : [HS] First version
 *
 *******************************************************************************
 */

#ifndef _REMOTE_LOG_CLIENT_
#define _REMOTE_LOG_CLIENT_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <osa.h>
#include <osa_mem.h>
#include <osa_thr.h>
#include <osa_remote_log_if.h>

/**
 *******************************************************************************
 *
 * \brief Period for remote log client task to run
 *
 *******************************************************************************
 */
#define REMOTE_LOG_CLIENT_PERIOD_MS           (10u)



/**
 *******************************************************************************
 *
 * \brief Line buffer size for remote shared buffer
 *
 *******************************************************************************
 */
#define REMOTE_LOG_LINE_BUF_SIZE         (1024)



/**
 *******************************************************************************
 *
 *   \brief Remote log client object
 *
 *         Contains fields required for remote log client
 *
 *******************************************************************************
*/
typedef struct {

    unsigned int coreObjPhysBaseAddr;
    /**< Physical address of the memory to which all remote and
     *   local core writes for printing it on  uart on local
     *   core
     */
    unsigned char *coreObjVirtBaseAddr;
    /**< Virtual address of the above physical memory. For non
     *   Linux system this  will be same as physical address
     */
    unsigned int coreObjTotalMemSize;
    /**< Size of the the shared memory */

    volatile RemoteLog_MemInfo *pMemInfo[SYSTEM_PROC_MAX];
    /**< Remote log server memory Information for the remote cores. */

    volatile unsigned char *pServerLogBuf;
    /**< Pointer to Server Log Buf memory */

    char lineBuf[REMOTE_LOG_LINE_BUF_SIZE];
    /**< Temporary buffer for print on uart from shared buffer */

    OSA_ThrHndl thrHndl;
    /**< Log print thread */

    volatile int exitThr;
    /**< flag to exit thread */

} RemoteLog_ClientObj;


#endif /* _REMOTE_LOG_CLIENT_ */
