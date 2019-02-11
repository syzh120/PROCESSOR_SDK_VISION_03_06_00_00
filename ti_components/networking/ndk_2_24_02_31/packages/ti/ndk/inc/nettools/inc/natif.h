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
 * ======== natif.h ========
 *
 */

#ifndef _NATIF_H_
#define _NATIF_H_

/* DHCP NAT SERVICE */

/* NAT Parameter Structure */
typedef struct _ntparam_nat {
        IPN     IPVirt;         /* Virtual IP address */
        IPN     IPMask;         /* Mask of virtual subnet */
        uint    MTU;            /* NAT packet MTU (normally 1500 or 1492) */
        } NTPARAM_NAT;

/* NATOpen() */
/* This function is called to initiate NAT control of the system. The */
/* interface specified to NAT is the IF of the EXTERNAL network. */
/* Compatible with NT_MODE_IFIDX only. */
/* Returns a pseudo-HANDLE of "1" on success, or NULL on failure. The */
/* pseudo-HANDLE can used with NATClose(). */
_extern HANDLE NATOpen( NTARGS *pNTA, NTPARAM_NAT *pNTP );

/* NATClose() */
/* This function terminates NAT control */
_extern void NATClose( HANDLE hNAT );

#endif
