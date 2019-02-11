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
 * ======== autoconn.h ========
 *
 * This program implements an auto-connecting mechanism for PPP.
 *
 */

#include <netmain.h>
#include <_stack.h>

typedef struct _autoconnparm {
    char    Username[32];
    char    Password[32];
    UINT32  Timeout;
    uint    Interface;
} AUTOCONNPARM;


/* Connection Status Defines */
#define AC_STATUS_CLOSED        1
#define AC_STATUS_IDLE          2
#define AC_STATUS_CONNECTING    3
#define AC_STATUS_SYSTEMFAIL    4
#define AC_STATUS_NOPPPOE       5
#define AC_STATUS_LCPFAIL       6
#define AC_STATUS_AUTHFAIL      7
#define AC_STATUS_IPCFGFAIL     8
#define AC_STATUS_CONNECTED     9


void AutoConnOpen( AUTOCONNPARM *pac );
uint AutoConnGetStatus();
void AutoConnClose();
