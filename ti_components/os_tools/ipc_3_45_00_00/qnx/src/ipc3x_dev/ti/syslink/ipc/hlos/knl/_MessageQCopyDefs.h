/*
 * Copyright (c) 2011-2015 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name Texas Instruments nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined (_MESSAGEQCOPYDEFS_H_0x5f84)
#define _MESSAGEQCOPYDEFS_H_0x5f84

/* Module headers */
#include <VirtQueue.h>
#include "virtio_ring.h"
#include <rpmsg.h>

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
 /*!
 *  @def    MessageQCopy_BUFSIZE
 *  @brief  Size of each MessageQCopy message.
 */
#define MessageQCopy_BUFSIZE RPMSG_BUF_SIZE

/*!
 *  @def    MessageQCopy_ADDRANY
 *  @brief  Address used to specify any address.
 */
#define MessageQCopy_ADDRANY RPMSG_ADDR_ANY

/*!
 *  @def    MessageQCopy_MAXMQS
 *  @brief  Maximum number of MQ handles (endpoints) per transport supported.
 */
#define MessageQCopy_MAXMQS 1280u

/*!
 *  @def    MessageQCopy_NUMVIRTQS
 *  @brief  Number of VirtQueues per processor.
 */
#define MessageQCopy_NUMVIRTQS 2u

/* Predefined endpoint addresses */
/*!
 *  @def    MessageQCopy_NS_PORT
 *  @brief  Name Service endpoint address.
 */
#define MessageQCopy_NS_PORT (53)


#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1) / (d))

/*!
 *  @def    MessageQCopy_NUMBUFS
 *  @brief  Number of buffers per VirtQueue.
 */
#define MessageQCopy_NUMBUFS     (256)

/*!
 *  @def    MessageQCopy_BUFSPACE
 *  @brief  Space used by buffers per remote proc.
 */
#define MessageQCopy_BUFSPACE   (MessageQCopy_NUMBUFS * RPMSG_BUF_SIZE *\
                                 MessageQCopy_NUMVIRTQS)

/*!
 *  @def    PAGE_SIZE
 *  @brief  Page size.
 */
#define PAGE_SIZE           (4096)

/*!
 *  @def    MessageQCopy_MAXRESERVEDEPT
 *  @brief  Maximum Value for System Reserved Endpoints.
 */
#define MessageQCopy_MAXRESERVEDEPT    1024

/*
 * The alignment to use between consumer and producer parts of vring.
 * Note: this is part of the "wire" protocol. If you change this, you need
 * to update your BIOS image as well
 */
#define MessageQCopy_VRINGALIGN  (4096)

/*!
 *  @def    MessageQCopy_RINGSIZE
 *  @brief  Size of the vring.  With 256 buffers, our vring will occupy 3 pages.
 */
#define MessageQCopy_RINGSIZE  ((DIV_ROUND_UP(vring_size(MessageQCopy_NUMBUFS, \
                              MessageQCopy_VRINGALIGN), PAGE_SIZE)) * PAGE_SIZE)

/*!
 *  @def    MessageQCopy_IPCMEM
 *  @brief  The total IPC space needed to communicate with a remote processor.
 */
#define MessageQCopy_IPCMEM   (MessageQCopy_BUFSPACE + MessageQCopy_NUMVIRTQS *\
                               MessageQCopy_RINGSIZE)


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif  /* !defined (_MESSAGEQCOPY_H_0x5f84) */
