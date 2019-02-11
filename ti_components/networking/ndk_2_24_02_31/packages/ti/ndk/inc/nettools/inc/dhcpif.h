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
 * ======== dhcpif.h ========
 *
 */


#ifndef _DHCPIF_H_
#define _DHCPIF_H_

/* DCHP CLIENT SERVICE */

/* Running Codes (State codes are all less than 0x10) */
#define DHCPCODE_IPADD          0x11    /* Client has added an address */
#define DHCPCODE_IPREMOVE       0x12    /* IP address removed and CFG erased */
#define DHCPCODE_IPRENEW        0x13    /* IP renewed, DHCP config space reset */

/* DCHP Parameter Structure */
#define DHCP_MAX_OPTIONS        64  /* Max number allowed options */
typedef struct _ntparam_dhcp {
    UINT8   *pOptions;  /* options to request */
    int     len;        /* length of options list */
} NTPARAM_DHCP;

/* DHCPOpen */
/* This function is called to initiate DHCP control of the IP */
/* address binding on the interface specified by hIF */
/* Compatible with NT_MODE_IFIDX only. */
/* Returns a HANDLE to the DHCP instance */
_extern HANDLE DHCPOpen( NTARGS *pNTA, NTPARAM_DHCP *pNTP );

/* DHCPClose */
/* This function terminates DHCP control and free the supplied */
/* instance handle. */
_extern void  DHCPClose( HANDLE hDHCP );

#endif

