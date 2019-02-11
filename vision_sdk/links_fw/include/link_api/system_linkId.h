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
 *  \ingroup SYSTEM_LINK_API
 *  \defgroup SYSTEM_LINK_ID  System Link ID's
 *
 *  The unique 32-bit Link ID for the links present in the system are defined
 *  in this module
 *
 *  @{
*/

/**
 *******************************************************************************
 *
 *  \file system_linkId.h
 *  \brief  System Link ID's
 *
 *******************************************************************************
*/

#ifndef SYSTEM_LINK_ID_H_
#define SYSTEM_LINK_ID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <include/link_api/system_procId.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Max possible Link ID
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_MAX                  (128U)

/**
 *******************************************************************************
 *
 * \brief Invalid Link ID
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_INVALID              (0xFFFFFFFFU)

/**
 *******************************************************************************
 *
 * \brief Set the IPU primary core depends on what is set from Rules.make
 *
 *******************************************************************************
*/
#ifdef IPU_PRIMARY_CORE_IPU2
#define SYSTEM_IPU_PROC_PRIMARY (SYSTEM_PROC_IPU2)
#else
#define SYSTEM_IPU_PROC_PRIMARY (SYSTEM_PROC_IPU1_0)
#endif


#define SYSTEM_IPC_PAYLOAD_ROUTE_BIT_MASK    (0x1u)
#define SYSTEM_IPC_PAYLOAD_ROUTE_BIT_SHIFT   (31u)
#define SYSTEM_IPC_PAYLOAD_NOTIFY_TYPE_MASK  (0x7u)
#define SYSTEM_IPC_PAYLOAD_NOTIFY_TYPE_SHIFT (28u)
#define SYSTEM_IPC_PAYLOAD_DST_CPU_ID_MASK   (0xFu)
#define SYSTEM_IPC_PAYLOAD_DST_CPU_ID_SHIFT  (24u)
#define SYSTEM_IPC_PAYLOAD_LINK_ID_MASK      (0xFFFFFFu)

/**
 *******************************************************************************
 *
 * \brief Create link id which indicates the link & processor in which it
 *        resides
 *
 *******************************************************************************
*/
#if defined (IPU_PRIMARY_CORE_IPU1)
#define SYSTEM_MAKE_LINK_ID(p, x) (\
               (((UInt32)((p) & (SYSTEM_IPC_PAYLOAD_DST_CPU_ID_MASK)) << (SYSTEM_IPC_PAYLOAD_DST_CPU_ID_SHIFT))\
                   | ((x) & (SYSTEM_IPC_PAYLOAD_LINK_ID_MASK))\
               )\
           )
#endif
#if defined (IPU_PRIMARY_CORE_IPU2)
#define SYSTEM_MAKE_LINK_ID(p, x) (\
               (((UInt32)(((p == SYSTEM_PROC_IPU1_0)? SYSTEM_PROC_IPU2:p)\
                   & (SYSTEM_IPC_PAYLOAD_DST_CPU_ID_MASK)) << (SYSTEM_IPC_PAYLOAD_DST_CPU_ID_SHIFT))\
                   | ((x) & (SYSTEM_IPC_PAYLOAD_LINK_ID_MASK))\
               )\
           )
#endif

/**
 *******************************************************************************
 *
 * \brief Get the link id - strip off proc id
 *
 *******************************************************************************
*/
#define SYSTEM_GET_LINK_ID(x)     ((x) & SYSTEM_IPC_PAYLOAD_LINK_ID_MASK)

/**
 *******************************************************************************
 *
 * \brief Get the proc id - strip off link id
 *
 *******************************************************************************
*/
#define SYSTEM_GET_PROC_ID(x)     (((x) >> SYSTEM_IPC_PAYLOAD_DST_CPU_ID_SHIFT) & (SYSTEM_IPC_PAYLOAD_DST_CPU_ID_MASK))

/**
 *******************************************************************************
 *
 * \brief Set route bit - bit 32 of LinkId is used as route bit
 *        This is used only when message needs to be routed through
 *        some other core.
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_SET_ROUTE_BIT(x)    ((x) |= (1U << SYSTEM_IPC_PAYLOAD_ROUTE_BIT_SHIFT))

/**
 *******************************************************************************
 *
 * \brief Clear route bit
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_CLEAR_ROUTE_BIT(x)  ((x) &= ~((1U) << SYSTEM_IPC_PAYLOAD_ROUTE_BIT_SHIFT))

/**
 *******************************************************************************
 *
 * \brief Test route bit
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_TEST_ROUTE_BIT_TRUE(x)  ((x) & (1U << SYSTEM_IPC_PAYLOAD_ROUTE_BIT_SHIFT))


/**
 *******************************************************************************
 *
 * \brief Type of payload used with notify payload: Payload is Link ID
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_NOTIFY_TYPE_LINK_ID         (0U)

/**
 *******************************************************************************
 *
 * \brief Type of payload used with notify payload: Payload is a message
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_NOTIFY_TYPE_MSG             (1U)

/**
 *******************************************************************************
 *
 * \brief Type of payload used with notify payload: Payload is a message ACK
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_NOTIFY_TYPE_MSG_ACK         (2U)

/**
 *******************************************************************************
 *
 * \brief Type of payload used with notify payload: Payload is a OpenVX Message
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_NOTIFY_TYPE_OPENVX          (3U)

/**
 *******************************************************************************
 *
 * \brief Type of payload used with notify payload: Payload is a Work Queue Message
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_NOTIFY_TYPE_WORK_QUEUE     (4U)

/**
 *******************************************************************************
 *
 * \brief Set route bit - bit 32 of LinkId is used as route bit
 *        This is used only when message needs to be routed through
 *        some other core.
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_MAKE_NOTIFY_TYPE(dest_p, src_p, t)       \
    ( SYSTEM_MAKE_LINK_ID((dest_p), (src_p)) | ( (UInt32)( (t) & SYSTEM_IPC_PAYLOAD_NOTIFY_TYPE_MASK ) << SYSTEM_IPC_PAYLOAD_NOTIFY_TYPE_SHIFT) )

/**
 *******************************************************************************
 *
 * \brief Test route bit
 *
 *******************************************************************************
*/
#define SYSTEM_LINK_ID_GET_NOTIFY_TYPE(x)    (((x) >> SYSTEM_IPC_PAYLOAD_NOTIFY_TYPE_SHIFT) & SYSTEM_IPC_PAYLOAD_NOTIFY_TYPE_MASK)


/* @{ */

/**
 *******************************************************************************
 *
 * \brief IPU1_0 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define IPU1_0_LINK(x)          (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_IPU1_0 , (x)))

/**
 *******************************************************************************
 *
 * \brief IPU1_1 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
*/
#define IPU1_1_LINK(x)          (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_IPU1_1 , (x)))

/**
 *******************************************************************************
 *
 * \brief IPU2 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define IPU2_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_IPU2 , (x)))

/**
 *******************************************************************************
 *
 * \brief DSP1 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define DSP1_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_DSP1   , (x)))

/**
 *******************************************************************************
 *
 * \brief DSP2 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define DSP2_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_DSP2   , (x)))

/**
 *******************************************************************************
 *
 * \brief EVE1 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define EVE1_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_EVE1   , (x)))

/**
 *******************************************************************************
 *
 * \brief EVE2 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define EVE2_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_EVE2   , (x)))

/**
 *******************************************************************************
 *
 * \brief EVE3 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define EVE3_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_EVE3   , (x)))

/**
 *******************************************************************************
 *
 * \brief EVE4 System Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define EVE4_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_EVE4   , (x)))

/**
 *******************************************************************************
 *
 * \brief A15 Link - used for non-link specific proc level communication
 *
 *******************************************************************************
*/
#define A15_0_LINK(x)            (SYSTEM_MAKE_LINK_ID(SYSTEM_PROC_A15_0 ,(x)))


/* @} */

/* @{ */

/**
 *******************************************************************************
 *
 * \brief Link ID for the generic processor link task
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_PROCK_LINK_ID        (SYSTEM_LINK_ID_MAX-1U)

/**
 *******************************************************************************
 *
 * \brief IPU1_0 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_IPU1_0       (IPU1_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief IPU1_1 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_IPU1_1       (IPU1_1_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief IPU2 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_IPU2         (IPU2_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief DSP1 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_DSP1         (DSP1_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief DSP2 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_DSP2         (DSP2_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief EVE1 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_EVE1         (EVE1_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief EVE2 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_EVE2         (EVE2_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief EVE3 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_EVE3         (EVE3_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief EVE4 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_EVE4         (EVE4_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/**
 *******************************************************************************
 *
 * \brief A15_0 System Link - used for non-link specific proc level
 *        communication
 *
 *******************************************************************************
 */
#define SYSTEM_LINK_ID_A15_0        (A15_0_LINK(SYSTEM_LINK_ID_PROCK_LINK_ID))

/* @} */

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 *  \brief Link Id for links that can reside on any processor
 *
 *         These identifiers are not valid as-is. They need to be combined with
 *         processor Id in order to make a valid link ID.
 *
 *         The macros below can be used to create the processor specific
 *         link Id.
 *          - EVEx_LINK(common link id)
 *          - DSPx_LINK(common link id)
 *          - A15_x_LINK(common link id)
 *          - IPUx_y_LINK(common link id)
 *
 *         NOTE: Even though a link ID is listed here, for some core's
 *               the actually number of instances created will vary.
 *
 *               Ex, for EVE the number of link instances created is
 *                     IPC IN  = 1 instance
 *                     IPC OUT = 1 instance
 *                     ALG     = 1 instance
 *
 *         TO increase number of links on a given processor
 *               - Add more enum IDs for that link here
 *               - AND increase the number of link instances in file
 *               /vision_sdk/src/links_common/[link]/[link]Link_cfg.h
 *                 OR
 *               /vision_sdk/src/links_common/[link]/[link]Link_priv.h
 *
 *               - Modify "#define [link]_LINK_OBJ_MAX" to match number of enums
 *                 in this file
 *
 *         The processor specific link ID should be used with all link APIs
 *
 *******************************************************************************
 */
typedef enum
{
    SYSTEM_LINK_ID_IPC_OUT_0 = 0,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_1 = 1,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_2 = 2,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_3 = 3,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_4 = 4,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_5 = 5,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_6 = 6,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_7 = 7,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_8 = 8,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_OUT_9 = 9,
    /**< IPC Output Link Id  - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_0 = 10,
    /**< IPC Input Link Id - used to xfr data across
      *  processors */

    SYSTEM_LINK_ID_IPC_IN_1 = 11,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_2 = 12,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_3 = 13,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_4 = 14,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_5 = 15,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_6 = 16,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_7 = 17,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_8 = 18,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_IPC_IN_9 = 19,
    /**< IPC Input Link Id - used to xfr data across
     *   processors */

    SYSTEM_LINK_ID_NULL_0 = 20,
    /**< Null Link - Can be used as a tap point to verify various
     *   sub-chains. Doesnt do any processing : 4*/

    SYSTEM_LINK_ID_NULL_1 = 21,
    /**< Null Link - Can be used as a tap point to verify various
     *   sub-chains. Doesnt do any processing : 5*/

    SYSTEM_LINK_ID_NULL_2 = 22,
    /**< Null Link - Can be used as a tap point to verify various
     *   sub-chains. Doesnt do any processing : 5*/

    SYSTEM_LINK_ID_GRPX_SRC_0 = 23,
    /**< Null source link - can be used as a source link providing
     *   dummy data */

    SYSTEM_LINK_ID_GRPX_SRC_1 = 24,
    /**< Null source link - can be used as a source link providing
     *   dummy data */

    SYSTEM_LINK_ID_DUP_0 = 25,
    /**< Dup Link - Duplicate frames and provides multiple outputs */

    SYSTEM_LINK_ID_DUP_1 = 26,
    /**< Dup Link - Duplicate frames and provides multiple outputs */

    SYSTEM_LINK_ID_DUP_2 = 27,
    /**< Dup Link - Duplicate frames and provides multiple outputs */

    SYSTEM_LINK_ID_DUP_3 = 28,
    /**< Dup Link - Duplicate frames and provides multiple outputs */

    SYSTEM_LINK_ID_DUP_4 = 29,
    /**< Dup Link - Duplicate frames and provides multiple outputs */

    SYSTEM_LINK_ID_GATE_0 = 30,
    /**< Gate Link - Acts a on/off switch and allows partial data
         flow to exist */

    SYSTEM_LINK_ID_GATE_1 = 31,
    /**< Gate Link - Acts a on/off switch and allows partial data
         flow to exist */

    SYSTEM_LINK_ID_GATE_2 = 32,
    /**< Gate Link - Acts a on/off switch and allows partial data
         flow to exist */

    SYSTEM_LINK_ID_GATE_3 = 33,
    /**< Gate Link - Acts a on/off switch and allows partial data
         flow to exist */

    SYSTEM_LINK_ID_SYNC_0 = 34,
    /**< Sync Link - creates a composite frame by composing multiple incoming
         Frames */

    SYSTEM_LINK_ID_SYNC_1 = 35,
    /**< Sync Link - creates a composite frame by composing multiple incoming
         Frames */

    SYSTEM_LINK_ID_SYNC_2 = 36,
    /**< Sync Link - creates a composite frame by composing multiple incoming
         Frames */

    SYSTEM_LINK_ID_SYNC_3 = 37,
    /**< Sync Link - creates a composite frame by composing multiple incoming
         Frames */

    SYSTEM_LINK_ID_MERGE_0 = 38,
    /**< Merge Link - Merge different input queue frames & provide them as
     *   single output source. Channel numbering is sequential wrt to
     *   input queues */

    SYSTEM_LINK_ID_MERGE_1 = 39,
    /**< Merge Link - Merge different input queue frames & provide them as
     *   single output source. Channel numbering is sequential wrt to
     *   input queues */

    SYSTEM_LINK_ID_MERGE_2 = 40,
    /**< Merge Link - Merge different input queue frames & provide them as
     *   single output source. Channel numbering is sequential wrt to
     *   input queues */

    SYSTEM_LINK_ID_MERGE_3 = 41,
    /**< Merge Link - Merge different input queue frames & provide them as
     *   single output source. Channel numbering is sequential wrt to
     *   input queues */

    SYSTEM_LINK_ID_MERGE_4 = 42,
    /**< Merge Link - Merge different input queue frames & provide them as
     *   single output source. Channel numbering is sequential wrt to
     *   input queues */


    SYSTEM_LINK_ID_SELECT_0 = 43,
    /**< Select Link enables configurable mapping of specific channels
     *   to be sent out in multiple queues */

    SYSTEM_LINK_ID_SELECT_1 = 44,
    /**< Select Link enables configurable mapping of specific channels
     *   to be sent out in multiple queues */

    SYSTEM_LINK_ID_SELECT_2 = 45,
    /**< Select Link enables configurable mapping of specific channels
     *   to be sent out in multiple queues */

    SYSTEM_LINK_ID_SELECT_3 = 46,
    /**< Select Link enables configurable mapping of specific channels
     *   to be sent out in multiple queues */

    SYSTEM_LINK_ID_SELECT_4 = 47,
    /**< Select Link enables configurable mapping of specific channels
     *   to be sent out in multiple queues */

    SYSTEM_LINK_ID_SELECT_5 = 48,
    /**< Select Link enables configurable mapping of specific channels
     *   to be sent out in multiple queues */

    SYSTEM_LINK_ID_ALG_0 = 49,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_ALG_1 = 50,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_ALG_2 = 51,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_ALG_3 = 52,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_ALG_4 = 53,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_ALG_5 = 54,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_ALG_6 = 55,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_ALG_7 = 56,
    /**< Algorithm link Id */

    SYSTEM_LINK_ID_NULL_SRC_0 = 57,
    /**< Null source link - can be used as a source link providing
     *   dummy data */

    SYSTEM_LINK_ID_AVB_RX = 58,
    /**< AvbRx link Id - can be used for supported CPUs only.
     *
     *   Supported CPUs: ipu1_0, ipu1_1, a15_0 in TDA2xx
     *   Supported CPUs: ipu1_0, ipu1_1        in TDA3xx
     */

    SYSTEM_LINK_ID_RTI_0 = 59,
    /* RTI link - only on TDA3x, on all cores except EVE/M4_1 */

    SYSTEM_LINK_ID_TFDTP_RX = 60,
    /**< TFDTP Rx link Id - can be used for supported CPUs only.
     *
     *   Supported CPUs: ipu1_0, ipu1_1, a15_0 in TDA2xx
     *   Supported CPUs: ipu1_0, ipu1_1        in TDA3xx
     */

    SYSTEM_LINK_ID_LIDAR_GPC = 61,
    /* Lidar Ground Point Classification algorithm, runs on dsp1, dsp2, ipu1_0, ipu1_1, and a15_0 */

    SYSTEM_LINK_ID_AVB_TX_0 = 62,
    /**< AvbTx link Id - can be used for supported CPUs only.
     *
     *   Supported CPUs: ipu1_0, ipu1_1, a15_0 in TDA2xx
     *   Supported CPUs: ipu1_0, ipu1_1        in TDA3xx
     */

    SYSTEM_LINK_ID_NETWORK_TX_0 = 63,
    /**< Network Tx link Id - can be used for supported CPUs only.
     *
     *   Supported CPUs: ipu1_0, ipu1_1, a15_0 in TDA2xx
     *   Supported CPUs: ipu1_0, ipu1_1        in TDA3xx
     */

    SYSTEM_LINK_ID_NETWORK_TX_1 = 64,
    /**< Network Tx link Id - can be used for supported CPUs only.
     *
     *   Supported CPUs: ipu1_0, ipu1_1, a15_0 in TDA2xx
     *   Supported CPUs: ipu1_0, ipu1_1        in TDA3xx
     */

    SYSTEM_LINK_ID_NETWORK_TX_2 = 65,
    /**< Network Tx link Id - can be used for supported CPUs only.
     *
     *   Supported CPUs: ipu1_0, ipu1_1, a15_0 in TDA2xx
     *   Supported CPUs: ipu1_0, ipu1_1        in TDA3xx
     */

    SYSTEM_LINK_ID_NETWORK_RX_0 = 66,
    /**< Network Rx link Id - can be used for supported CPUs only.
     *
     *   Supported CPUs: ipu1_0, ipu1_1, a15_0 in TDA2xx
     *   Supported CPUs: ipu1_0, ipu1_1        in TDA3xx
     */

     SYSTEM_LINK_ID_AUTOSAR_IPC_IN_0 = 67,
     /**< Autosar IPC Input Link Id  - used to xfr data across
      *   processors */

     SYSTEM_LINK_ID_AUTOSAR_IPC_OUT_0 = 68,
     /**< Autosar IPC Output Link Id  - used to xfr data across
      *   processors */

     SYSTEM_LINK_COMMON_LINKS_MAX_ID = 69
    /**< Common Links - Max Id */

} SYSTEM_LINK_IDS_COMMON;

/**
 *******************************************************************************
 *
 *  \brief Links Ids specific to IPU1_0.
 *
 *         These are valid Link Ids available in IPU1_0.
 *         Few of the links create multiple instances with unique
 *         identifier - like xxx_0, xxx_1
 *
 *******************************************************************************
 */
typedef  enum
{
    SYSTEM_LINK_ID_CAPTURE_0           =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+1U),
    /**< Capture link. Present in IPU1_0 */

    SYSTEM_LINK_ID_CAPTURE_1           =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+2U),
    /**< Capture link. Present in IPU1_0 */

    SYSTEM_LINK_ID_CAPTURE             = SYSTEM_LINK_ID_CAPTURE_0,
    /**< Capture link ID to keep the name backward compatible */

    SYSTEM_LINK_ID_DISPLAYCTRL      =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+3U),
    /**< Display link Control - enables configurations of Vencs.
         Present in IPU1_0 */

    SYSTEM_LINK_ID_DISPLAY_0         =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+4U),
    /**< Display link - enables one of the outputs like HDTV, SDTV etc.
         Present in IPU1_0 */

    SYSTEM_LINK_ID_DISPLAY_1         =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+5U),
    /**< Display link - enables one of the outputs like HDTV, SDTV etc.
         Present in IPU1_0 */

    SYSTEM_LINK_ID_DISPLAY_2         =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+6U),

    /**< Display link - enables one of the outputs like HDTV, SDTV etc.
         Present in IPU1_0 */

    SYSTEM_LINK_ID_DISPLAY_3        =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+7U),
    /**< Display link - enables one of the outputs like HDTV, SDTV etc.
         Present in IPU1_0 */

    SYSTEM_LINK_ID_VPE_0            =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+8U),
    /**< VPE Link Id */

    SYSTEM_LINK_ID_VPE_1            =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+9U),
    /**< VPE Link Id */

    SYSTEM_LINK_ID_VPE_2            =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+10U),
    /**< VPE Link Id */

    SYSTEM_LINK_ID_VPE_3            =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+11U),
    /**< VPE Link Id */

    SYSTEM_LINK_ID_VENC_0           =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+12U),
    /**< Video encode link Id */

    SYSTEM_LINK_ID_VDEC_0           =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+13U),
    /**< Video decode link Id */

    SYSTEM_LINK_ID_ISSCAPTURE_0     =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+14U),
    /**< Iss Capture link 0. Present in IPU1_0 */

    SYSTEM_LINK_ID_ISSM2MISP_0     =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+15U),
    /**< Iss Capture link 0. Present in IPU1_0 */

    SYSTEM_LINK_ID_ISSM2MSIMCOP_0 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+16U),
    /**< Simcop link Id */

    SYSTEM_LINK_ID_ISSM2MSIMCOP_1 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+17U),
    /**< Simcop link Id */

    SYSTEM_LINK_ID_ISSM2MSIMCOP_2 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+18U),
    /**< Simcop link Id */

    SYSTEM_LINK_ID_ISSM2MSIMCOP_3 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+19U),
    /**< Simcop link Id */

    SYSTEM_LINK_ID_ISSM2MSIMCOP_4 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+20U),
    /**< Simcop link Id */

    SYSTEM_LINK_ID_APP_CTRL         =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+21U),
    /**< Application specific control link Id */

    SYSTEM_LINK_ID_ULTRASONIC_CAPTURE =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+22U),
    /**< Ultrasonic capture link */

    SYSTEM_LINK_ID_HCF_0 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+23U),
    /**< HCF link */

    SYSTEM_LINK_ID_SPLIT_0 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+24U),
    /**< Split Link - Split frames into different queues */

    SYSTEM_LINK_ID_RADAR_CAPTURE =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+25U),
    /**< Radar Capture Link */

    SYSTEM_LINK_ID_DISPLAY_MULTI_PIPE_0         =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+26U),
    /**< Display link - enables one of the outputs like HDTV, SDTV etc.
         Present in IPU1_0 */

    SYSTEM_LINK_ID_DISPLAY_MULTI_PIPE_1         =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+27U),
    /**< Display link - enables one of the outputs like HDTV, SDTV etc.
         Present in IPU1_0 */

    SYSTEM_LINK_ID_DSSM2MWB_0 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+28U),
    /**< DSS M2M Write Back link */

    SYSTEM_LINK_ID_ISS_RESIZER_0 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+29U),
    /**< ISS Resizer link */

    SYSTEM_LINK_ID_ISS_RESIZER_1 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+30U),
    /**< ISS Resizer link */

    SYSTEM_LINK_ID_ISS_RESIZER_2 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+31U),
    /**< ISS Resizer link */

    SYSTEM_LINK_ID_ISS_RESIZER_3 =
                    IPU1_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+32U),
    /**< ISS Resizer link */

    SYSTEM_IPU1_0_LINK_ID_MAX = 0x3FFFFFFFU
    /**< Max link ID for IPU1-0 specfic links */

} SYSTEM_IPU1_0_LINK_IDS;

/**
 *******************************************************************************
 *
 *  \brief Links Ids specific to A15 (Linux).
 *
 *         These are valid Link Ids available in A15 (Linux).
 *         Few of the links create multiple instances with unique
 *         identifier - like xxx_0, xxx_1
 *
 *******************************************************************************
 */
typedef  enum
{
    SYSTEM_LINK_ID_SGXFRMCPY_0    =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+1U),
    /**< SgxDiaply link - enables DRM display along with SGX rendering,
         Present only on A15_0 */

    SYSTEM_LINK_ID_SGX3DSRV_0     =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+2U),
    /**< Sgx3Dsrv link - For 3D SRV output creation/rendering on SGX,
         Present only on A15_0 */

    SYSTEM_LINK_ID_SGX3DSFM_0     =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+3U),
    /**< Sgx3Dsfm link - For 3D map output rendering on SGX,
         Present only on A15_0 */

    SYSTEM_LINK_ID_EP_0 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+4U),
    /**< endpoint link id - 0,
         Present only on A15 */
    SYSTEM_LINK_ID_EP_1 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+5U),
    /**< endpoint link id - 1,
         Present only on A15 */
    SYSTEM_LINK_ID_EP_2 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+6U),
    /**< endpoint link id - 2,
         Present only on A15 */
    SYSTEM_LINK_ID_EP_3 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+7U),
    /**< endpoint link id - 3,
         Present only on A15 */

    SYSTEM_LINK_ID_DATA_COLLECT_0 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+8U),
    /**< Data Collect link id ,
         Present only on A15 */

    SYSTEM_LINK_ID_LIDAR_CAPTURE =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+9U),
    /* ID of link capturing lidar data over ethernet */

    SYSTEM_LINK_ID_LIDAR_CLOUD =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+10U),
    /* ID of link for decoding lidar data into point cloud format */

    SYSTEM_LINK_ID_SGX_LINK =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+11U),
    /* ID of link for rendering data in 3D on SGX */

    SYSTEM_LINK_ID_LIDAR_XFORM =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+12U),
    /* Transformation link between reference rames */

    SYSTEM_LINK_ID_IMU =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+13U),

    SYSTEM_LINK_ID_DUMP_LINK_0 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+14U),

    SYSTEM_LINK_ID_DUMP_LINK_1 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+15U),

    SYSTEM_LINK_ID_DUMP_LINK_2 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+16U),

    SYSTEM_LINK_ID_DUMP_LINK_3 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+17U),

    SYSTEM_LINK_ID_SGXCAMPC_0 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+18U),

    SYSTEM_LINK_ID_SLAM =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+19U),

    SYSTEM_LINK_ID_UNDUMP_LINK_0 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+20U),

    SYSTEM_LINK_ID_UNDUMP_LINK_1 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+21U),

    SYSTEM_LINK_ID_UNDUMP_LINK_2 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+22U),

    SYSTEM_LINK_ID_UNDUMP_LINK_3 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+23U),

    SYSTEM_LINK_ID_OG_LINK_0 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+24U),

    SYSTEM_LINK_ID_OG_LINK_1 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+25U),

    SYSTEM_LINK_ID_DISPDISTSRC_LINK_0 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+25U),

    SYSTEM_LINK_ID_DISPDISTSRC_LINK_1 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+26U),

    SYSTEM_LINK_ID_DISPDISTSRC_LINK_2 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+27U),

    SYSTEM_LINK_ID_DISPDISTSRC_LINK_3 =
                    A15_0_LINK((uint32_t)SYSTEM_LINK_COMMON_LINKS_MAX_ID+28U)

} SYSTEM_A15_0_LINK_IDS;


#ifdef  __cplusplus
}
#endif

#endif

/*@}*/

