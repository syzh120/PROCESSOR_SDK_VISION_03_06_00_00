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
 * ======== dhcpsif.h ========
 *
 * interface to the tools available in nettool.lib
 *
 */

#ifndef _DHCPSIF_H_
#define _DHCPSIF_H_

/* DHCP SERVER SERVICE */

/* DHCPS Parameter Structure */
typedef struct _ntparam_dhcps {
        uint    Flags;          /* DHCPS Execution Flags */
#define DHCPS_FLG_LOCALDNS      0x0001  /* Report Local DNS server to clients */
#define DHCPS_FLG_LOCALDOMAIN   0x0002  /* Report Local DomainName to clients */
        IPN     PoolBase;       /* First IP address in optional pool */
        uint    PoolCount;      /* Number of addresses in optional pool */
        } NTPARAM_DHCPS;

/* DHCPSOpen() */
/* This function is called to initiate DHCPS control of a certain device. */
/* A gerneric address pool is optional. Otherwise; DHCPS will use the */
/* CLIENT list for the devcie found in the configuration. */
/* Compatible with NT_MODE_IFIDX only. */
/* Returns a HANDLE to a DHCPS instance structure which is used in */
/* calls to other DHCPS functions like DHCPSClose(). */
_extern HANDLE DHCPSOpen( NTARGS *pNTA, NTPARAM_DHCPS *pNTP );

/* DHCPSClose() */
/* This function terminates DHCPS control and free the supplied */
/* instance handle. */
_extern void DHCPSClose( HANDLE hDHCPS );

#endif

