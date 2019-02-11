/*
*
* Copyright (c) 2012-2017 Texas Instruments Incorporated
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



/**
*  @file       eve_edma_user_interface.h
*
*  @brief      This header defines all types and constants
*              shared by implementations of the BAM EDMA user interface.
*/

#ifndef EDMA_USER_INTERFACE_H
#define EDMA_USER_INTERFACE_H

#pragma CHECK_MISRA ("none")
#include "stdint.h"
#pragma RESET_MISRA ("required")

#define MAX_NODE_CHANNELS        10U    /**< Maximum allowed number of DMA channels per node */

#define BAM_SOURCE_NODE_PORT1   0U      /**< BAM input port index 0 */
#define BAM_SINK_NODE_PORT1     0U      /**< BAM output port index 0 */

#define BAM_SOURCE_NODE_PORT2   1U      /**< BAM input port index 1 */
#define BAM_SINK_NODE_PORT2     1U      /**< BAM output port index 1 */

#define BAM_SOURCE_NODE_PORT3   2U      /**< BAM input port index 2 */
#define BAM_SINK_NODE_PORT3     2U      /**< BAM output port index 2 */

#define BAM_SOURCE_NODE_PORT4   3U      /**< BAM input port index 3 */
#define BAM_SINK_NODE_PORT4     3U      /**< BAM output port index 3 */

#define BAM_SOURCE_NODE_PORT5   4U      /**< BAM input port index 4 */
#define BAM_SINK_NODE_PORT5     4U      /**< BAM output port index 4 */

#define BAM_SOURCE_NODE_PORT6   5U      /**< BAM input port index 5 */
#define BAM_SINK_NODE_PORT6     5U      /**< BAM output port index 5 */

#define BAM_SOURCE_NODE_PORT7   6U      /**< BAM input port index 6 */
#define BAM_SINK_NODE_PORT7     6U      /**< BAM output port index 6 */

#define BAM_SOURCE_NODE_PORT8   7U      /**< BAM input port index 7 */
#define BAM_SINK_NODE_PORT8     7U      /**< BAM output port index 7 */

#define BAM_SOURCE_NODE_PORT9   8U      /**< BAM input port index 8 */
#define BAM_SINK_NODE_PORT9     8U      /**< BAM output port index 8 */

#define BAM_SOURCE_NODE_PORT10   9U      /**< BAM input port index 9 */
#define BAM_SINK_NODE_PORT10     9U      /**< BAM output port index 9 */

/**
*  @brief      Constants for defining type of EDMA transfer channel.
*
*  @remarks    These constants determine the internal EDMA auto-increment
*              settings and trigger/wait controls of each channel.
*/
typedef enum args_type
{
    EDMA_SOURCE,    /**< To be used with channels for tranfering data from DDR to internal memory */
    EDMA_SINK       /**< To be used with channels for tranfering data from internal memory to DDR */
} DMANODE_EdmaArgsType;


#endif

