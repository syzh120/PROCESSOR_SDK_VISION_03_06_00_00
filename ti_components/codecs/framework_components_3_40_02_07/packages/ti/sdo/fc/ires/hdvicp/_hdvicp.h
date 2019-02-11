/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _HDVICP_H
#define _HDVICP_H

/* Size of PSC address space */
#define _HDVICP_PSCSIZE 0x2000

/* Base address of PSC address space */
#define _HDVICP_PSCBASE 0x1C40000

#ifdef xdc_target__os_Linux

/* Id offset from _HDVICP_ipcKeyBase to shared memory containing HDVICP object */
#define _HDVICP_SHMID (_HDVICP_ipcKeyBase)

/* Id offset from _HDVICP_ipcKeyBase to semaphore used for critical sections */
#define _HDVICP_CSID (_HDVICP_ipcKeyBase + 1)

/* Id offset from _HDVICP_ipcKeyBase to lock used for protecting HDVICP object */
#define _HDVICP_LOCKID (_HDVICP_ipcKeyBase + 2)

/* Id offset from _HDVICP_ipcKeyBase to semaphore used for managing scratch
   HDVICP memory resources */
#define _HDVICP_MEMID (_HDVICP_ipcKeyBase + 3)

extern UInt32 _HDVICP_ipcKeyBase;

#endif

#endif /* _HDVICP_H */
