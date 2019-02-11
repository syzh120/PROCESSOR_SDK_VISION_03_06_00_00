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
 * \defgroup LINK_STATS_COLLECT    Link Statistics Collector
 *
 * \brief Keeps all links statistics information in shared memory
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \file utils_link_stats_collector.h Link Statistics information collector
 *
 * \brief  Internal header file for Link statistics, included by each link
 *
 * \version 0.1 (Mar 2015) : First version
 *
 *******************************************************************************
 */

#ifndef LINK_STATS_COLLECTOR_
#define LINK_STATS_COLLECTOR_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>


#define UTILS_LINK_STATS_IPU1_0_INST_START   (0U)
#ifdef IPU_PRIMARY_CORE_IPU1
#define UTILS_LINK_STATS_IPU1_0_INST_NUM     (30U)
#else
#define UTILS_LINK_STATS_IPU1_0_INST_NUM     (10U)
#endif
#define UTILS_LINK_STATS_IPU1_0_INST_END     (UTILS_LINK_STATS_IPU1_0_INST_START +\
                                              UTILS_LINK_STATS_IPU1_0_INST_NUM)

#define UTILS_LINK_STATS_IPU1_1_INST_START   (UTILS_LINK_STATS_IPU1_0_INST_END)
#define UTILS_LINK_STATS_IPU1_1_INST_NUM     (15U)
#define UTILS_LINK_STATS_IPU1_1_INST_END     (UTILS_LINK_STATS_IPU1_1_INST_START +\
                                              UTILS_LINK_STATS_IPU1_1_INST_NUM)

#define UTILS_LINK_STATS_A15_0_INST_START    (UTILS_LINK_STATS_IPU1_1_INST_END)
#define UTILS_LINK_STATS_A15_0_INST_NUM      (20U)
#define UTILS_LINK_STATS_A15_0_INST_END      (UTILS_LINK_STATS_A15_0_INST_START +\
                                              UTILS_LINK_STATS_A15_0_INST_NUM)

#define UTILS_LINK_STATS_DSP1_INST_START     (UTILS_LINK_STATS_A15_0_INST_END)
#define UTILS_LINK_STATS_DSP1_INST_NUM       (15U)
#define UTILS_LINK_STATS_DSP1_INST_END       (UTILS_LINK_STATS_DSP1_INST_START +\
                                              UTILS_LINK_STATS_DSP1_INST_NUM)

#define UTILS_LINK_STATS_DSP2_INST_START     (UTILS_LINK_STATS_DSP1_INST_END)
#define UTILS_LINK_STATS_DSP2_INST_NUM       (20U)
#define UTILS_LINK_STATS_DSP2_INST_END       (UTILS_LINK_STATS_DSP2_INST_START +\
                                              UTILS_LINK_STATS_DSP2_INST_NUM)

#define UTILS_LINK_STATS_EVE1_INST_START     (UTILS_LINK_STATS_DSP2_INST_END)
#define UTILS_LINK_STATS_EVE1_INST_NUM       (10U)
#define UTILS_LINK_STATS_EVE1_INST_END       (UTILS_LINK_STATS_EVE1_INST_START +\
                                              UTILS_LINK_STATS_EVE1_INST_NUM)

#define UTILS_LINK_STATS_EVE2_INST_START     (UTILS_LINK_STATS_EVE1_INST_END)
#define UTILS_LINK_STATS_EVE2_INST_NUM       (10U)
#define UTILS_LINK_STATS_EVE2_INST_END       (UTILS_LINK_STATS_EVE2_INST_START +\
                                              UTILS_LINK_STATS_EVE2_INST_NUM)

#define UTILS_LINK_STATS_EVE3_INST_START     (UTILS_LINK_STATS_EVE2_INST_END)
#define UTILS_LINK_STATS_EVE3_INST_NUM       (5U)
#define UTILS_LINK_STATS_EVE3_INST_END       (UTILS_LINK_STATS_EVE3_INST_START +\
                                              UTILS_LINK_STATS_EVE3_INST_NUM)

#define UTILS_LINK_STATS_EVE4_INST_START     (UTILS_LINK_STATS_EVE3_INST_END)
#define UTILS_LINK_STATS_EVE4_INST_NUM       (10U)
#define UTILS_LINK_STATS_EVE4_INST_END       (UTILS_LINK_STATS_EVE4_INST_START +\
                                              UTILS_LINK_STATS_EVE4_INST_NUM)

#define UTILS_LINK_STATS_IPU2_INST_START     (UTILS_LINK_STATS_EVE4_INST_END)
#ifdef IPU_PRIMARY_CORE_IPU1
#define UTILS_LINK_STATS_IPU2_INST_NUM       (10U)
#else
#define UTILS_LINK_STATS_IPU2_INST_NUM       (30U)
#endif
#define UTILS_LINK_STATS_IPU2_INST_END       (UTILS_LINK_STATS_IPU2_INST_START +\
                                              UTILS_LINK_STATS_IPU2_INST_NUM)

/** \brief Guard macro */
#if (UTILS_LINK_STATS_IPU2_INST_END > LINK_STATS_MAX_STATS_INST)
    #error "Increase LINK_STATS_MAX_STATS_INST in file utils_link_stats_if.h"
#endif

#define UTILS_LINK_STATS_PRF_IPU1_0_INST_START   (0U)
#ifdef IPU_PRIMARY_CORE_IPU1
#define UTILS_LINK_STATS_PRF_IPU1_0_INST_NUM     (96U)
#else
#define UTILS_LINK_STATS_PRF_IPU1_0_INST_NUM     (50U)
#endif
#define UTILS_LINK_STATS_PRF_IPU1_0_INST_END     (UTILS_LINK_STATS_PRF_IPU1_0_INST_START +\
                                                  UTILS_LINK_STATS_PRF_IPU1_0_INST_NUM)

#define UTILS_LINK_STATS_PRF_IPU1_1_INST_START   (UTILS_LINK_STATS_PRF_IPU1_0_INST_END)
#define UTILS_LINK_STATS_PRF_IPU1_1_INST_NUM     (50U)
#define UTILS_LINK_STATS_PRF_IPU1_1_INST_END     (UTILS_LINK_STATS_PRF_IPU1_1_INST_START +\
                                                  UTILS_LINK_STATS_PRF_IPU1_1_INST_NUM)

#define UTILS_LINK_STATS_PRF_A15_0_INST_START    (UTILS_LINK_STATS_PRF_IPU1_1_INST_END)
#define UTILS_LINK_STATS_PRF_A15_0_INST_NUM      (50U)
#define UTILS_LINK_STATS_PRF_A15_0_INST_END      (UTILS_LINK_STATS_PRF_A15_0_INST_START +\
                                                  UTILS_LINK_STATS_PRF_A15_0_INST_NUM)

#define UTILS_LINK_STATS_PRF_DSP1_INST_START     (UTILS_LINK_STATS_PRF_A15_0_INST_END)
#define UTILS_LINK_STATS_PRF_DSP1_INST_NUM       (16U)
#define UTILS_LINK_STATS_PRF_DSP1_INST_END       (UTILS_LINK_STATS_PRF_DSP1_INST_START +\
                                                  UTILS_LINK_STATS_PRF_DSP1_INST_NUM)

#define UTILS_LINK_STATS_PRF_DSP2_INST_START     (UTILS_LINK_STATS_PRF_DSP1_INST_END)
#define UTILS_LINK_STATS_PRF_DSP2_INST_NUM       (16U)
#define UTILS_LINK_STATS_PRF_DSP2_INST_END       (UTILS_LINK_STATS_PRF_DSP2_INST_START +\
                                                  UTILS_LINK_STATS_PRF_DSP2_INST_NUM)

#define UTILS_LINK_STATS_PRF_EVE1_INST_START     (UTILS_LINK_STATS_PRF_DSP2_INST_END)
#define UTILS_LINK_STATS_PRF_EVE1_INST_NUM       (16U)
#define UTILS_LINK_STATS_PRF_EVE1_INST_END       (UTILS_LINK_STATS_PRF_EVE1_INST_START +\
                                                  UTILS_LINK_STATS_PRF_EVE1_INST_NUM)

#define UTILS_LINK_STATS_PRF_EVE2_INST_START     (UTILS_LINK_STATS_PRF_EVE1_INST_END)
#define UTILS_LINK_STATS_PRF_EVE2_INST_NUM       (16U)
#define UTILS_LINK_STATS_PRF_EVE2_INST_END       (UTILS_LINK_STATS_PRF_EVE2_INST_START +\
                                                  UTILS_LINK_STATS_PRF_EVE2_INST_NUM)

#define UTILS_LINK_STATS_PRF_EVE3_INST_START     (UTILS_LINK_STATS_PRF_EVE2_INST_END)
#define UTILS_LINK_STATS_PRF_EVE3_INST_NUM       (16U)
#define UTILS_LINK_STATS_PRF_EVE3_INST_END       (UTILS_LINK_STATS_PRF_EVE3_INST_START +\
                                                  UTILS_LINK_STATS_PRF_EVE3_INST_NUM)

#define UTILS_LINK_STATS_PRF_EVE4_INST_START     (UTILS_LINK_STATS_PRF_EVE3_INST_END)
#define UTILS_LINK_STATS_PRF_EVE4_INST_NUM       (16U)
#define UTILS_LINK_STATS_PRF_EVE4_INST_END       (UTILS_LINK_STATS_PRF_EVE4_INST_START +\
                                                  UTILS_LINK_STATS_PRF_EVE4_INST_NUM)

#define UTILS_LINK_STATS_PRF_IPU2_INST_START     (UTILS_LINK_STATS_PRF_EVE4_INST_END)
#ifdef IPU_PRIMARY_CORE_IPU1
#define UTILS_LINK_STATS_PRF_IPU2_INST_NUM       (50U)
#else
#define UTILS_LINK_STATS_PRF_IPU2_INST_NUM       (96U)
#endif
#define UTILS_LINK_STATS_PRF_IPU2_INST_END       (UTILS_LINK_STATS_PRF_IPU2_INST_START +\
                                                  UTILS_LINK_STATS_PRF_IPU2_INST_NUM)

/** \brief Guard macro */
#if (UTILS_LINK_STATS_PRF_IPU2_INST_END > LINK_STATS_PRF_MAX_TSK)
    #error "Increase LINK_STATS_PRF_MAX_TSK in file utils_link_stats_if.h"
#endif


/**
 *******************************************************************************
 *
 *  \brief  Function to initialize link stats collector.
 *
 *          This api initializes Link stats collector, it resets the flags,
 *          counter for each core.
 *          This API must be called only from one core
 *
 *  \returns    0: Collector is initialized and ready to be used
 *              any other number: collector is not initialized and
 *                                return the error
 *******************************************************************************
 */
Int32 Utils_linkStatsCollectorInit(void);

/**
 *******************************************************************************
 *
 *  \brief  Function to Deinitialize collector.
 *          checks if all link stats objects are de-allocated or not,
 *          Asserts if this is not the case.
 *          This API should be called after deinit of all links
 *          This API must be called only from one core
 *
 *******************************************************************************
 */
Void Utils_linkStatsCollectorDeInit(void);

#endif /* LINK_STATS_COLLECTOR_ */

/*@}*/
