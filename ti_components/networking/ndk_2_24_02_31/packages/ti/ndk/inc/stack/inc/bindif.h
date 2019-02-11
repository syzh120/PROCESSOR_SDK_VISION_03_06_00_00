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
 * ======== bindif.h ========
 *
 * IPv4 Binding table access functions and definitions
 *
 */


#ifndef _C_BINDIF_INC
#define _C_BINDIF_INC  /* #defined if this .h file has been included */

/* Bind Create Functions */
_extern HANDLE  BindNew( HANDLE hIF, IPN IPHost, IPN IPMask );
_extern void    BindFree( HANDLE h );

/* Bind Access Functions */
_extern HANDLE  BindGetFirst();
_extern HANDLE  BindGetNext( HANDLE );
_extern HANDLE  BindGetIF( HANDLE );
_extern HANDLE  BindGetIFByDBCast( IPN IPHost );
_extern void    BindGetIP(HANDLE,IPN *pIPHost,IPN *pIPNet,IPN *pIPMask);

/* Bind Search Functions */
_extern HANDLE  BindFindByIF( HANDLE hIF );
_extern HANDLE  BindFindByNet( HANDLE hIF, IPN IP );
_extern HANDLE  BindFindByHost( HANDLE hIF, IPN IP );

/* IF to IP Matching Functions */
_extern IPN     BindIFNet2IPHost( HANDLE hIF, IPN IP );
_extern IPN     BindIF2IPHost( HANDLE hIF );
_extern HANDLE  BindIPHost2IF( IPN IP );
_extern HANDLE  BindIPNet2IF( IPN IP );

#endif
