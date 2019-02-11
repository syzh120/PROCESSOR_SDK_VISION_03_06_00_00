/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
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

/*
 *******************************************************************************
 *
 *  EDMA utility functions
 *
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  edma_utils.h
 *
 * @brief    This function declares functions which can be used accross all usecases
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 *
 * @version 0.1 (Aug 2013) : First version of eve edma utils
 *
 *****************************************************************************
 */

#ifndef EDMA_UTILS_H_
#define EDMA_UTILS_H_

#include "edma3lld_support.h"
#include "dma_resource_allocator.h"
/** ======================= ============================
 *  @name   EDMA_UTILS_TRANSFER_TYPE
 *
 *  @desc   Describes the type of transfer you want to configure while configuring
 *                 auto increments
 *
 *  @field  EDMA_UTILS_TRANSFER_IN
 *             Indicates IN transfer, external memory to Internal memory
 *
 *  @field  EDMA_UTILS_TRANSFER_OUT
 *             Indicates OUT transfer, internal memory to external memory
 *
 *  @field  EDMA_UTILS_TRANSFER_INOUT
 *             Indicates that user wants to configure both IN and OUT transfer together
 *  ====================================================
 */
typedef enum
{
    EDMA_UTILS_TRANSFER_IN,
    EDMA_UTILS_TRANSFER_OUT,
    EDMA_UTILS_TRANSFER_INOUT
}EDMA_UTILS_TRANSFER_TYPE;

/* ==================================================
*  @func     EDMA_UTILS_setEdma3RmHandle
*
*  @desc   This is first function which should be called before calling any
*               utility function ane even before EDMA_UTILS_globalReset function is called.
*               This function sets the EDMA3 LLD handle which will be used for resource
*               allocation. User can pass the handle as NULL also for the cases he/she doesnt
*               want to use EDMA3 LLD.
*
*  @modif    NONE
*
*  @inputs   edma3RmHandle : Handle to the EDMA3 LLD resoruce manager instance
*                 This can take value as NULL for the cases where user doesnt want to use
*                 EDMA3 LLD
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
void  EDMA_UTILS_setEdma3RmHandle(EDMA3_RM_Handle edma3RmHandle);

/* ==================================================
*  @func     EDMA_UTILS_globalReset
*
*  @desc   This function resets the global utils state structure which contains
*          all resources allocatred for different utility usecases also it
*          releases all the resources allocated by resources mangaer so far.
*          This function should be called once before using EDMA utilities. It is
*          IMPORTANT to note that EDMA_UTILS_setEdma3RmHandle function
*          should have been called before calling this function
*
*  @modif    NONE
*
*  @inputs   NONE
*
*  @outputs NONE
*
*  @return    NONE
*
*  =======================================================
*/
void  EDMA_UTILS_globalReset(void);

#endif

