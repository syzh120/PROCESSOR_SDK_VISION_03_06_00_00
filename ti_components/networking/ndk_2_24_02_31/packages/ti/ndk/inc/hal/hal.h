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
 * ======== hal.h ========
 *
 * Include file for generic support layer
 *
 */

#ifndef _C_HAL_INC
#define _C_HAL_INC  /* #defined if this .h file has been included */

/* Note: All functions define here with a leading underscore '_' */
/*       must only be called from outside of kernel mode (llEnter/llExit) */

/*----------------------------------------------------------------------- */
/*---[ LLPACKET ]-------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/* Packet Driver Interface to the Operating System */
_extern uint   _llPacketInit(STKEVENT_Handle h); /* Init and enumerate */
_extern void   _llPacketShutdown();              /* System shutdown */
_extern void   _llPacketServiceCheck( uint fTimerTick ); /* Polling Function */

/* Packet Driver Interface to the Stack */
_extern uint   llPacketOpen( uint dev, HANDLE hEther );
_extern void   llPacketClose( uint dev );
_extern void   llPacketSend( uint dev, PBM_Handle hPkt );
_extern void   llPacketSetRxFilter( uint dev, uint filter );
_extern void   llPacketGetMacAddr( uint dev, UINT8 *pbData );
_extern uint   llPacketGetMCastMax( uint dev );
_extern void   llPacketSetMCast( uint dev, uint addrcnt, UINT8 *bAddr );
_extern uint   llPacketGetMCast( uint dev, uint maxaddr, UINT8 *bAddr );
_extern uint   llPacketIoctl( uint dev, uint cmd, void *arg);
_extern void   llPacketService();


/*----------------------------------------------------------------------- */
/*---[ LLSERIAL ]-------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/* Serial Driver Interface called from User Mode */
_extern uint  _llSerialInit(STKEVENT_Handle h); /* Init and enumerate */
_extern void  _llSerialShutdown();              /* System shutdown */
_extern void  _llSerialServiceCheck(uint fTimerTick); /* Polling Function */
_extern uint  _llSerialSend(uint dev, UINT8 *pBuf, uint len);

/* Serial Driver Interface called from Kernel Mode */
_extern uint  llSerialOpen(uint dev, void (*cbInput)(char c));
_extern void  llSerialClose( uint dev );

_extern uint  llSerialOpenHDLC( uint dev, HANDLE hHDLC,
                                void (*cbTimer)(HANDLE h),
                                void (*cbInput)(PBM_Handle hPkt) );
_extern void  llSerialCloseHDLC( uint dev );
_extern void  llSerialSendPkt( uint dev, PBM_Handle hPkt );
_extern void  llSerialHDLCPeerMap( uint dev, UINT32 peerMap );

_extern void  llSerialService();
_extern void  llSerialConfig( uint dev, uint baud, uint mode, uint flowctrl );

/* Mode values for llSerialConfig() */
#define HAL_SERIAL_MODE_8N1             0
#define HAL_SERIAL_MODE_7E1             1
#define HAL_SERIAL_FLOWCTRL_NONE        0
#define HAL_SERIAL_FLOWCTRL_HARDWARE    1


/*----------------------------------------------------------------------- */
/*---[ LLTIMER ]--------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/* Timer Driver Interface to the Operating System */
_extern void   _llTimerInit( STKEVENT_Handle h, UINT32 ctime );
_extern void   _llTimerShutdown();

/* Timer Driver Interface to the Stack */
_extern UINT32 llTimerGetTime( UINT32 *pMSFrac );
_extern UINT32 llTimerGetStartTime();



/*----------------------------------------------------------------------- */
/*---[ LLUSERLED ]----------------------------------------------------------- */
/*----------------------------------------------------------------------- */

/* User LED Driver Interface to the Operating System */
_extern void   _llUserLedInit();
_extern void   _llUserLedShutdown();
_extern void   LED_ON(UINT32 ledId);
_extern void   LED_OFF(UINT32 ledId);
_extern void   LED_TOGGLE(UINT32 ledId);

#define USER_LED1   1
#define USER_LED2   2
#define USER_LED3   4
#define USER_LED4   8
#define USER_LED5   16
#define USER_LED6   32
#define USER_LED7   64
#define USER_LED8   128

#endif
