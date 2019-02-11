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
 * ======== pipeif.h ========
 *
 * Pipe object include
 *
 */

#include "fdtif.h"

#ifndef _PIPEIF_INC_
#define _PIPEIF_INC_


/* Pipe Object Structure */
typedef struct _pipe {
             FILEDESC     fd;           /* File descriptor header */
             struct _pipe *pConnect;    /* Pointer to other end of pipe */
             HANDLE       hSBRx;        /* Rx Buffer */
             INT32        TxSpace;      /* Tx Space Required for "writeable" */
        } PIPE;


/* Pipe Access Functions */

/*------------------------------------------------------------------------ */
/* General Access Functions (called from upper layers) */
_extern int    PipeNew( HANDLE *phPipe1, HANDLE *phPipe2 );
_extern int    PipeClose( HANDLE hPipe );

_extern int    PipeCheck( HANDLE hPipe, int IoType );
#define  PIPE_READ       0
#define  PIPE_WRITE      1

_extern int    PipeStatus( HANDLE hPipe, int request, int *results );

_extern int    PipeRecv( HANDLE hPipe, INT8 *pBuf, INT32 size,
                        int flags, INT32 *pRetSize );
_extern int    PipeSend( HANDLE hPipe, INT8 *pBuf, INT32 size,
                        int flags, INT32 *pRetSize );

#endif
