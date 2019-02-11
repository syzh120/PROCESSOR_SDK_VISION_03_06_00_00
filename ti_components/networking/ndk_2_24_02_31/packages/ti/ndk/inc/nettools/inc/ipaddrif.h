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
 * ======== ipaddrif.h ========
 *
 *
 */

#ifndef _IPADDRIF_H_
#define _IPADDRIF_H_

/* IP Addr */
/* IP Address Maintenance Functions */
_extern HANDLE NtAddNetwork( HANDLE hIF, IPN dwIP, IPN dwIPMask );
_extern void   NtRemoveNetwork( HANDLE hBind );
_extern HANDLE NtAddStaticGateway( IPN IPTgtAddr, IPN IPTgtMask, IPN IPGateway );
_extern int    NtRemoveStaticGateway( IPN IPTarget );

/* Get IP Address from Physical If Index */
_extern int    NtIfIdx2Ip( uint IfIdx, IPN *pIPAddr );

/* Get Public Host Information */
_extern int    NtGetPublicHost( IPN *pIPAddr, uint MaxSize, UINT8 *pDomain );

/* Convert network format IP address to string */
_extern void   NtIPN2Str( IPN IPAddr, char *str );

#endif

