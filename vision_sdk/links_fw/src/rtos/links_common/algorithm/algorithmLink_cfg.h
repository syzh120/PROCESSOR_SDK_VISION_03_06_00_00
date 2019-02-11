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
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_cfg.h Algorithm Link private API/Data structures
 *
 * \brief  This link private header file has all the definitions which
 *         are specific to the processor type / processor core
 *         Functions APIs which need to be called by the use case are listed
 *         here
 *
 * \version 0.0 (Aug 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_CFG_H_
#define ALGORITHM_LINK_CFG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/algorithmLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Maximum number of algorithm links to be used and stack sizes
 *          to be used.
 *
 *          It is defined based on the processor core, thus giving
 *          flexibility of different number of links / stack sizes for different
 *          processor cores. However for different links on the same processor
 *          core, stack size is kept same.
 *
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
/*
 *
 *    DES_ID: DOX_DES_TAG(DES_ALGLINK_001)
 *    REQ_ID: DOX_REQ_TAG(ADASVISION-1547)
 *
 */
#ifdef BUILD_DSP_1
#define ALGORITHM_LINK_OBJ_MAX        (8U)
/* stack size increased for pedstrain detect object tracking lib */
#define ALGORITHM_LINK_TSK_STACK_SIZE (1024*1024)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_DSP_ALG_MAXNUM)
#endif

#ifdef BUILD_DSP_2
#define ALGORITHM_LINK_OBJ_MAX        (8U)
#define ALGORITHM_LINK_TSK_STACK_SIZE (1024*1024)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_DSP_ALG_MAXNUM)
#endif

#ifdef BUILD_ARP32_1
#define ALGORITHM_LINK_OBJ_MAX        (8U)
#define ALGORITHM_LINK_TSK_STACK_SIZE (7*KB)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_EVE_ALG_MAXNUM)
#endif

#ifdef BUILD_ARP32_2
#define ALGORITHM_LINK_OBJ_MAX        (8U)
#define ALGORITHM_LINK_TSK_STACK_SIZE (7*KB)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_EVE_ALG_MAXNUM)
#endif

#ifdef BUILD_ARP32_3
#define ALGORITHM_LINK_OBJ_MAX        (8U)
#define ALGORITHM_LINK_TSK_STACK_SIZE (7*KB)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_EVE_ALG_MAXNUM)
#endif

#ifdef BUILD_ARP32_4
#define ALGORITHM_LINK_OBJ_MAX        (8U)
#define ALGORITHM_LINK_TSK_STACK_SIZE (7*KB)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_EVE_ALG_MAXNUM)
#endif

#ifdef BUILD_M4
#define ALGORITHM_LINK_OBJ_MAX        (8U)
#define ALGORITHM_LINK_TSK_STACK_SIZE (SYSTEM_DEFAULT_TSK_STACK_SIZE)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_IPU_ALG_MAXNUM)
#endif

#ifdef BUILD_A15
#define ALGORITHM_LINK_OBJ_MAX        (8U)
#define ALGORITHM_LINK_TSK_STACK_SIZE (SYSTEM_DEFAULT_TSK_STACK_SIZE)
#define ALGORITHM_LINK_ALG_MAXNUM     (ALGORITHM_LINK_A15_ALG_MAXNUM)
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
Int32 AlgorithmLink_initAlgPlugins(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
