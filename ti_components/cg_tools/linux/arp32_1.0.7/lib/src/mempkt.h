/*****************************************************************************/
/*  MEMPKT.H v1.0.7 - Common declarations for ARP32/VCOP memory allocation   */
/*                                                                           */
/* Copyright (c) 2011-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#ifndef _MEMPKT_H
#define _MEMPKT_H

#include <stdint.h>  /* For PTRDIFF_MAX */

/*----------------------------------------------------------------------------
* "PACKET" is the template for a memory data packet. "packet_size" is the
* number of words allocated for the user, excluding the size "OVERHEAD"
* required for management of the packet. When a packet is on the free list, the
* field "next_free" is a pointer to the next member of the freelist; when the
* packet is in use (allocated), this field is invalid, overwritten by user data
* (the address of this field is the address returned by malloc). A negative
* size indicates a free packet.
*---------------------------------------------------------------------------*/
typedef ptrdiff_t memsz_t;
#define MEMSZ_MAX (PTRDIFF_MAX)

typedef struct fpack
{
    memsz_t packet_size; /* in words */
#ifdef DEBUG
    int guard;
#endif
    struct fpack *next_free;
} PACKET;

/*----------------------------------------------------------------------------
* LIMIT is used to initialize the initial "next_free" pointer
*---------------------------------------------------------------------------*/
#define LIMIT	((PACKET *) -1)

/*----------------------------------------------------------------------------
* OVERHEAD is the space in the packet required to store the packet size. This
* macro is used for two purposes: to compute the size of the allocation, and
* to ensure that the packet is properly aligned.
*---------------------------------------------------------------------------*/
#define OVERHEAD offsetof(PACKET, next_free)

/*----------------------------------------------------------------------------
* Utility macro to round up the value to be a multiple of aln.
*---------------------------------------------------------------------------*/
#define RNDUP(val,aln) (((val) + (aln-1)) & ~(aln-1))

#ifdef DEBUG
#define GUARDDWORD 0xDEAD
#endif

/*----------------------------------------------------------------------------
* Generic memory allocation / free prototypes
*---------------------------------------------------------------------------*/
void *mem_alloc(PACKET **free_mem, size_t allocsize);
void  mem_free(PACKET **free_mem, void *userptr);

#endif /* _MEMPKT_H */
