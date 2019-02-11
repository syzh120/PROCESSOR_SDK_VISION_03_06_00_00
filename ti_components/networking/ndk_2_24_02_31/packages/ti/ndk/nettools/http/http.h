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
 * ======== http.h ========
 *
 * HTTP server includes
 *
 */

#ifndef _HTTP_H
#define _HTTP_H

#include <netmain.h>
#include <_stack.h>

#define MAX_HTTP_CONNECTS       4

typedef struct _httpinst {
        HANDLE  hCb;                    /* Callback Handle */
        void (*pCb)(HANDLE,uint);       /* Status callback */
        IPN     IPAddr;                 /* Local IP address */
        HANDLE  hSemConnect;            /* Connection semaphore */
        HANDLE  hTask;                  /* HANDLE to task */
        } HTTPINST;

#define MAXREQUEST      512             /* Max bytes in request[] */

/* Structure for parsing HTTP messages */
typedef struct _http_msg
{
    SOCKET Sock;                        /* Socket */
    int    flagreadall;                 /* Set if entire record read */
    int    length;                      /* Length of the parsed string */
    int    parsed;                      /* Bytes of request[] parsed (consumed) */
    int    unparsed;                    /* Bytes of request[] remaining */
    char   termstr[16];                 /* Read terminator */
    char   parsestr[16];                /* Parse delimitor */
    char   username[32];                /* Username (when AUTH tag present) */
    char   password[32];                /* Password (when AUTH tag present) */
    char   request[MAXREQUEST];         /* Request buffer */
    int    PostContentLength;
    char   URI[MAXREQUEST];             /* URI (never larger than request[]) */
    char   RequestedFile[MAXREQUEST+16];/* File (we must be able to append */
                                        /* 'index.html' to max file length) */
    char  *URIArgs;                     /* '?' arguments on URI */
} HTTP_MSG;


/* Our private global functions */
int  httpParseRecv( HTTP_MSG *pMsg );
void httpAuthenticationReq( SOCKET Sock, int realmIdx );

#endif
