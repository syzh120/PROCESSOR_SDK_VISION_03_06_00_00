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


/****************************************************************************/
/*  bam_mempkt.h v1.0.2 - Common declarations for ARP32/VCOP memory         */
/*                        allocation                                        */
/****************************************************************************/

#ifndef _BAM_MEMPKT_H
#define _BAM_MEMPKT_H
#include <stddef.h>
#include "bam_common.h"

/* DEBUG_BAM_MALLOC only works when HOST emulation is turned off */

#if defined(HOST_EMULATION) || defined(CORE_DSP) 
typedef enum memview
{
    VCOP_MEMFLAT = 0,
    VCOP_MEMALIASED
} VCOP_MEMVIEW;
#endif

/* Guard value that is added to the number of available memory packets to ensure that the pool of memory packets is big enough
 * has the maximum number of memory records in each memory heap. */
#define BAM_NUM_GUARD_PACKETS 0

/*----------------------------------------------------------------------------
 * "BAM_Packet" is the template for a memory data packet. "packet_size" is the
 * number of words allocated for the user, excluding the size "OVERHEAD"
 * required for management of the packet. When a packet is on the free list, the
 * field "next_free" is a pointer to the next member of the freelist; when the
 * packet is in use (allocated), this field is invalid, overwritten by user data
 * (the address of this field is the address returned by malloc). A negative
 * size indicates a free packet.
 *---------------------------------------------------------------------------*/
typedef ptrdiff_t memsz_t;
typedef struct fpack
{
    memsz_t packet_size; /* in words */
    struct fpack *next_free;
    struct fpack *apacket; /* alias packet */
    void *uaptr; /* unaligned ptr */
    void *ptr;   /* aligned ptr */
    int32_t heap; /* 0: free packet, other value correspond to the heap it belongs to */ 
} BAM_Packet;

/*----------------------------------------------------------------------------
 * LIMIT is used to initialize the initial "next_free" pointer
 *---------------------------------------------------------------------------*/
#define LIMIT   ((BAM_Packet *) (void*)0xFFFFFFFFU)

/*----------------------------------------------------------------------------
 * OVERHEAD is the space in the packet required to store the packet size. This
 * macro is used for two purposes: to compute the size of the allocation, and
 * to ensure that the packet is properly aligned.
 *---------------------------------------------------------------------------*/
#define OVERHEAD (offsetof(BAM_Packet, next_free))

/*----------------------------------------------------------------------------
 * Utility macro to round up the value to be a multiple of aln.
 *---------------------------------------------------------------------------*/
 
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* This macro has to accept 2 arguments */
#define RNDUP(val,aln) ((uint32_t)((val) + ((uint32_t)(aln)-1U)) & ~((uint32_t)(aln)-1U))
/* RESET_MISRA("19.7")  -> Reset rule 19.7 */

/*----------------------------------------------------------------------------
 * Generic memory allocation / free prototypes
 *---------------------------------------------------------------------------*/
void bam_setview(VCOP_MEMVIEW view);
int32_t bam_minit(BAM_Packet *packet_pool, int32_t num_packets,BAM_InternalMemParams * intMemParams);
int32_t bam_mcheck(void);
BAM_Packet *bam_getMemPacket(VCOP_MEMHEAP heap, int32_t alignment, size_t size);
BAM_Packet *bam_get_packet(int32_t heap);
BAM_Packet *bam_mem_alloc(BAM_Packet **free_mem, size_t allocsize, int32_t alignment, int32_t heap);
void bam_releaseMemPacket(BAM_Packet *packet);
void bam_mem_free(BAM_Packet **free_mem, BAM_Packet *packet);
BAM_Packet *bam_get_packet(int32_t heap);
int32_t bam_put_packet(BAM_Packet *packet);

#endif /* _MEMPKT_H */
