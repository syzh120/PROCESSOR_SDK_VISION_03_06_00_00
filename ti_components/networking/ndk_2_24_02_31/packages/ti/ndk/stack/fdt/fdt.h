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
 * */
/*
 * ======== fdt.h ========
 *
 * File Management Includes
 *
 */

/* File Descriptor Table */
typedef struct _fdtable {
        uint             Type;          /* Set to HTYPE_FDTABLE */
        uint             RefCount;      /* Object reference count */
        HANDLE           hSem;          /* File Event semaphore */
        int              error;         /* FileOp Error Number */
        UINT8            fClosing;      /* Flag when tasks can not use sockets */
        UINT8            fEvented;      /* Flag if we were "evented" */
        UINT8            fAbortPoll;    /* Flag if fdSelectAbort() called */
      } FDTABLE;


/*-------------------------------------------------------------------- */
/* Private Functions */
extern FDTABLE  *fdint_getfdt( HANDLE hTask );
extern void fdint_freefdt( FDTABLE *pfdt );
extern void fdint_signalevent( FDTABLE *pfdt );
extern void fdint_signaltimeout( FDTABLE *pfdt );
extern int  fdint_waitevent( FDTABLE *pfdt, UINT32 timeout );

extern int  fdint_setevent( FDTABLE *pfdt, FILEDESC *pfd, UINT8 EventFlags );
extern void fdint_clearevent( FDTABLE *pfdt, FILEDESC *pfd );

extern int  fdint_lockfd( FILEDESC *pfd, uint Type );
extern void fdint_unlockfd( FILEDESC *pfd, uint error );
