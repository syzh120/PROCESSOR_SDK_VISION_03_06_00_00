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
 *  \file system_vring_config.h  Linux <-> BIOS VRING Config
 *
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 *  \file system_vring_config.h
 *  \brief System viring addresses
 *
 *******************************************************************************
*/

#ifndef _SYSTEM_VRING_CONFIG_H_
#define _SYSTEM_VRING_CONFIG_H_

#ifdef  __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */


/*
 * Vring virtual addresses
 *
 * Vring virtual addresses are hard coded by ipc, if it is changed here it needs to be
 * changed in ipc package ipc_x_yy_zz_aa/packages/ti/ipc/family/<platform>/VirtQueue.c
 *
 * Ipc lib and bios side ipu/dsp executable needs to be re-built after the change.
 */

#define IPU_MEM_IPC_VRING       0x60000000
#define IPU_MEM_RPMSG_VRING0    0x60000000
#define IPU_MEM_RPMSG_VRING1    0x60004000
#define IPU_MEM_VRING_BUFS0     0x60040000
#define IPU_MEM_VRING_BUFS1     0x60080000

#define DSP_MEM_IPC_VRING       0xA0000000
#define DSP_MEM_RPMSG_VRING0    0xA0000000
#define DSP_MEM_RPMSG_VRING1    0xA0004000
#define DSP_MEM_VRING_BUFS0     0xA0040000
#define DSP_MEM_VRING_BUFS1     0xA0080000

/*
 * Vring physical addresses
 *
 * These are expected to be matched with beginning of cma section mentioned in
 * linux kernel linux/arch/arm/mach-omap2/remotproc.c, reserved for carveouts of
 * particular remote-core.
 *
 * If there is a change in physical address of a cma section in linux side it should be
 * manually done here. Vrings are expected to be at the beginning of cma section.
 *
 * Following addresses denote where the cma section for a particular core is physically
 * allocated / reserved by linux remoteproc module.
 *
 */

#ifdef BUILD_M4_0
#define IPU_PHYS_MEM_IPC_VRING      0x9e000000
#endif

#ifdef BUILD_DSP_1
#define DSP_PHYS_MEM_IPC_VRING      0xa1000000
#endif

#ifdef BUILD_DSP_2
#define DSP_PHYS_MEM_IPC_VRING      0xa3000000
#endif

#ifdef BUILD_M4_2
#define IPU_PHYS_MEM_IPC_VRING      0x99000000
#endif


/*@}*/

#ifdef  __cplusplus
}
#endif

#endif /* _SYSTEM_VRING_CONFIG_H_ */



