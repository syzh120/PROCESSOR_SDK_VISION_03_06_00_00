/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 *
 * \ingroup RTI_LINK_API
 * \defgroup RTI_LINK_IMPL RTI link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file rtiLink_priv.h RTI link private API/Data structures
 *
 * \brief  This file is a private header file for RTI link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of RTI link.
 *
 * \version 0.1 (Jul 2015) : [CSG] First version
 *
 *******************************************************************************
 */

#ifndef _RTI_LINK_PRIV_H_
#define _RTI_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/rtiLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Stack size for RTI link tasks
 *
 * SUPPORTED in TDA3x
 *
 *******************************************************************************
 */
#define RTI_LINK_TSK_STACK_SIZE    (SYSTEM_DEFAULT_TSK_STACK_SIZE)

 /**
 *******************************************************************************
 *
 * \brief Priority for RTI link tasks
 *
 * SUPPORTED in TDA3x
 *
 *******************************************************************************
 */
#define RTI_LINK_TSK_PRI    (2U)

 /**
 *******************************************************************************
 *
 * \brief Maximum number of RTI link objects
 *
 * SUPPORTED in TDA3x
 *
 *******************************************************************************
 */
#define RTI_LINK_OBJ_MAX    (1)

 /**
 *******************************************************************************
 *
 * \brief Maximum number of RTI modules supported
 *
 * SUPPORTED in TDA3x
 * There are 5 instances in TDA3x
 *
 *******************************************************************************
 */
#define RTI_LINK_NUM_RTI_MODULES    (5)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Structure to hold all RTI link related information
 *
 *******************************************************************************
 */

typedef struct {
    Utils_TskHndl tsk;
    /**< Handle to RTI WWDT proces task */

    UInt32 rtiServiceEnabled;
    /**< Maintain whether RTI servicing is enabled */

    UInt32 rtiMonitorEnabled[RTI_LINK_NUM_RTI_MODULES];
    /**< Maintain whether RTI expiry mointoring is enabled */

    UInt32 state;
    /**< Link state, one of SYSTEM_LINK_STATE_xxx */

    UInt32 tskId;
    /**< Placeholder to store RTI link task id */

    BspOsal_SemHandle lock;
    /**< Link level lock, used while updating the link params */

    BspOsal_IntrHandle  rtiHwiHandle[RTI_LINK_NUM_RTI_MODULES];
    /**< HWI handles */

    UInt32  rtiExpired[RTI_LINK_NUM_RTI_MODULES];
    /**< RTI expiry status */

    UInt32  procMap[RTI_LINK_NUM_RTI_MODULES];
    /**< Mapping of RTI module to CPU */
} RtiLink_Obj;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
