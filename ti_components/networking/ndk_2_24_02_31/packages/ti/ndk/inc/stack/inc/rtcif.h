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
 * ======== rtcif.h ========
 *
 *
 */


#ifndef _C_RTCIF_INC
#define _C_RTCIF_INC  /* #defined if this .h file has been included */

/*----------------------------------------------------------------------- */
/* Global Task Information */

/* Defined Messages */
#define MSG_RTC_TIMER                (ID_RTC*MSG_BLOCK + 0)

/* Route Report Messages */
#define MSG_RTC_UP                   (ID_RTC*MSG_BLOCK + 1)
#define MSG_RTC_DOWN                 (ID_RTC*MSG_BLOCK + 2)
#define MSG_RTC_MISS                 (ID_RTC*MSG_BLOCK + 3)
#define MSG_RTC_NEW                  (ID_RTC*MSG_BLOCK + 4)
#define MSG_RTC_EXPIRED              (ID_RTC*MSG_BLOCK + 5)
#define MSG_RTC_REMOVED              (ID_RTC*MSG_BLOCK + 6)
#define MSG_RTC_MODIFIED             (ID_RTC*MSG_BLOCK + 7)
#define MSG_RTC_REDIRECT             (ID_RTC*MSG_BLOCK + 8)
#define MSG_RTC_REDIRECT_NET         (ID_RTC*MSG_BLOCK + 9)
#define MSG_RTC_DUPIP                (ID_RTC*MSG_BLOCK + 10)

/*  RTC Route Report Messages */
/*  ------------------------- */
/*  MSG_RTC_UP               - Route is valid/pending */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */
/*  MSG_RTC_DOWN             - Route is down */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */
/*  MSG_RTC_MISS             - Route find "missed" on route */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */
/*  MSG_RTC_NEW              - New route entered in table */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */
/*  MSG_RTC_EXPIRED          - Route expired as was invalidated */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */
/*  MSG_RTC_REMOVED          - Route was manually removed */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */
/*  MSG_RTC_MODIFIED         - Route has been modified */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */
/*  MSG_RTC_REDIRECT         - Route has been redirected */
/*      Param1 = Route IP (host) */
/*      Param2 = New IP Gate (new gateway for route) */
/*  MSG_RTC_DUPIP            - Route was manually removed */
/*      Param1 = Route IP */
/*      Param2 = Route IP Mask (all ones for host route) */

_extern void   RTCReport( uint Msg, UINT32 dwParam1, UINT32 dwParam2 );

typedef void (*RTCHOOK)(uint, UINT32, UINT32);

_extern uint RTCAddHook( void (*pfn)( uint, UINT32, UINT32 ) );
_extern void RTCRemoveHook( void (*pfn)( uint, UINT32, UINT32 ) );

#endif

