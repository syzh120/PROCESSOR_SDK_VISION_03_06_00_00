/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
 * ======== netsrv.h ========
 *
 * Routines to spawn and destroy stack services
 *
 */

#ifndef _C_NETSRV_INC
#define _C_NETSRV_INC

/* The following #define's are used to determine if certain service */
/* entrypoints are linked into the executable. So if a service is not */
/* going to be used, set the corresponding #define to zero. When set */
/* to zero, the service is unavailable. */

#ifndef _NDK_EXTERN_CONFIG /* Configuration overridden by Makefiles */
#define NETSRV_ENABLE_TELNET            1
#define NETSRV_ENABLE_HTTP              1
#define NETSRV_ENABLE_NAT               0
#define NETSRV_ENABLE_DHCPCLIENT        1
#define NETSRV_ENABLE_DHCPSERVER        0
#define NETSRV_ENABLE_DNSSERVER         0
#endif

/* NETSRV Access Functions */

/* Hook function to check IP address per protocols like ACD RFC5227 */
typedef int(*NS_ValidateAddress)(IPN ipAddr);
extern void NS_setAddrHook(NS_ValidateAddress fxn);

/* PreBook Task */
_extern void NS_PreBoot();

/* Book Task */
_extern void NS_BootTask( HANDLE hCfg );

#endif
