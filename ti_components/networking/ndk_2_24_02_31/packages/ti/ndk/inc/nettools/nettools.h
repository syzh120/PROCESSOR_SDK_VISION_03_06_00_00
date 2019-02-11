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
 * ======== nettools.h ========
 *
 * Interface to tools available in nettool.lib
 *
 */

#ifndef _C_NETTOOLS_INC
#define _C_NETTOOLS_INC

/* Standard Service Callback */
/* Most services support a standard callback mechanism. The format */
/* of the callback is: */
/*   cbFun( HANDLE hCallback, uint NtStatus ), where */
/*      hCallback = Handle supplied to the service by the caller */
/*      NtStatus  = NetTools Service Status code */

/* Standard Calling Arguments */
/* Nettools Services support a standard calling structure where services */
/* may be invoked by interface or IP address. Note that some services */
/* are interface specific (like DHCP client) and can not support the */
/* "IP Address" mode. */
typedef struct _ntargs {
        int     CallMode;           /* Determines desired calling mode */
#define NT_MODE_IFIDX   1              /* Call by specifying IfIdx */
#define NT_MODE_IPADDR  2              /* Call by specifying IPAddr */
        int     IfIdx;              /* Physical interface index (0-n) */
        IPN     IPAddr;             /* IP Address */
        HANDLE  hCallback;          /* Handle to pass to callback function */
        void(*pCb)( HANDLE, uint ); /* Callback for status change */
        } NTARGS;

/* NetTools Status Codes */
/* Note most codes are specified by a range. Definitions within */
/* the set range are specified by the individual task. */
#define NETTOOLS_STAT_NONE              0
#define NETTOOLS_STAT_RUNNING           0x100
#define NETTOOLS_STAT_PARAMUPDATE       0x200
#define NETTOOLS_STAT_COMPLETED         0x300
#define NETTOOLS_STAT_FAULT             0x400

/* NetTools API Declarations */
#include "inc/configif.h"
#include "inc/daemonif.h"
#include "inc/dhcpif.h"
#include "inc/dhcpsif.h"
#include "inc/dnsif.h"
#include "inc/httpif.h"
#include "inc/inet.h"
#include "inc/ipaddrif.h"
#include "inc/telnetif.h"
#include "inc/tftpif.h"
#include "inc/natif.h"
#include "inc/dhcpopts.h"
#include "netcfg.h"

#endif
