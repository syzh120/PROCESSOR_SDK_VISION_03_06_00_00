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
 * \ingroup UTILS_MEM_API
 * \defgroup UTILS_MEM_CFG_API Memory heap configuration parameters
 *
 * \brief  Parameters to enable / disable L2 heap and set size of L2 heap
 *
 * @{
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file utils_mem_cfg.h
 *
 * \brief Memory heap configuration parameters
 *
 * \version 0.0 First version
 *
 *******************************************************************************
*/

#ifndef UTILS_MEM_CFG_H_
#define UTILS_MEM_CFG_H_

/* The L2 RAM size for DSP is visible to all cores for save and restore functionality
 * while trying to disable and re-enable DSP during power off and power on.
 */
#define UTILS_MEM_L2RAM_SIZE    (224U * 1024U)

#ifdef BUILD_DSP
    #define ENABLE_HEAP_L2
    /* 0x800 is used by stack, remaining is for HEAP, 0x40 is used for PMLIBDoWfi */
    #define UTILS_MEM_HEAP_L2_SIZE  (UTILS_MEM_L2RAM_SIZE - 0x840U)
#endif

#ifdef BUILD_ARP32
    #define ENABLE_HEAP_L2
    #define UTILS_MEM_HEAP_L2_SIZE  (22*1024)
#endif

#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
#ifndef IPC_LIB_INCLUDE
	#define ENABLE_HEAP_SR0
#endif
#endif /* #ifdef BUILD_M4_0 */

#endif /* UTILS_MEM_CFG_H_ */

/* @} */
