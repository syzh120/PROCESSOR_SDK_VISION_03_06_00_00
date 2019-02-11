/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      edma3_lld_helper.h                                                      */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file wrapper function to create  edma3 lld handle                   */
/*                                                                          */
/*==========================================================================*/

#ifndef EDMA3_LLD_HELPER_H_
#define EDMA3_LLD_HELPER_H_

#if (!HOST_EMULATION)
#include "edma3_rm.h"
#else
#include "stdint.h"
#include "edma3lld_support.h"
typedef int32_t             EDMA3_RM_GblConfigParams;
typedef int32_t             EDMA3_RM_InstanceInitConfig;

/** EDMA3_RM Result - return value of a function  */
typedef int32_t             EDMA3_RM_Result;

/** EDMA3_DRV Result - return value of a function  */
typedef int32_t             EDMA3_DRV_Result;

/**
 * OS specific Semaphore Handle.
 * Used to acquire/free the semaphore, used for sharing of resources
 * among multiple users.
 */
typedef void    *EDMA3_OS_Sem_Handle;

/** EDMA3 Resource Manager Result OK */
#define EDMA3_RM_SOK             (0)
/** EDMA3 Driver Result OK */
#define EDMA3_DRV_SOK            (0)

/** Define for NULL values*/
#ifndef NULL
  #define NULL 0u
#endif

#endif

EDMA3_RM_Handle  EDMA3_LLD_HELPER_init(
                        unsigned int                  edma3Id,
                        EDMA3_RM_GblConfigParams    * rmConfigParams,
                        EDMA3_RM_InstanceInitConfig * rmInstanceInitConfig,
                        EDMA3_RM_Result             * errorCode);

EDMA3_RM_Result EDMA3_LLD_HELPER_deinit (unsigned int edma3Id, EDMA3_RM_Handle hEdmaResMgr);


/**
 * \brief   EDMA3 OS Semaphore Give
 *
 *      This function gives or relinquishes an already
 *      acquired semaphore token
 * \param   hSem [IN] is the handle of the specified semaphore
 * \return  EDMA3_DRV_Result if successful else a suitable error code
 */
EDMA3_DRV_Result edma3OsSemTake(EDMA3_OS_Sem_Handle hSem, int32_t mSecTimeout);


/**
 * \brief   EDMA3 OS Semaphore Give
 *
 *      This function gives or relinquishes an already
 *      acquired semaphore token
 * \param   hSem [IN] is the handle of the specified semaphore
 * \return  EDMA3_DRV_Result if successful else a suitable error code
 */
EDMA3_DRV_Result edma3OsSemGive(EDMA3_OS_Sem_Handle hSem);


void edma3OsProtectEntry (uint32_t edma3InstanceId,
                      int32_t level,
                      uint32_t *intState);

void edma3OsProtectExit (uint32_t edma3InstanceId,
                    int32_t level,
                    uint32_t intState);

#endif /* EDMA3_LLD_HELPER_H_ */
