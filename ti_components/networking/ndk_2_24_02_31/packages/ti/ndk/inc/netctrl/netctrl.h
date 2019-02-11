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
 * ======== netctrl.h ========
 *
 * Shell functions for simplified net startup and shutdown
 *
 * The idea behind this API is to hide the user callable HAL/STACK functions
 *
 */

#ifndef _C_NETCTRL_INC
#define _C_NETCTRL_INC

/* NETCTRL is used to initialize the stack and maintain services. To */
/* accomplish this, it makes use of the configuration manager provided */
/* in the NETTOOLS library. Note that the configuration definitions and */
/* structures defined here are specific to NETCTRL, not CONFIG. */

/* NETCTRL Access Functions */

/* Initialize the run-time environment */
_extern int  NC_SystemOpen( int Priority, int OpMode );

#define NC_PRIORITY_LOW             OS_SCHEDULER_LOWPRI
#define NC_PRIORITY_HIGH            OS_SCHEDULER_HIGHPRI

#define NC_OPMODE_POLLING           1
#define NC_OPMODE_INTERRUPT         2

#define NC_OPEN_SUCCESS             0
#define NC_OPEN_ILLEGAL_PRIORITY    -1
#define NC_OPEN_ILLEGAL_OPMODE      -2
#define NC_OPEN_MEMINIT_FAILED      -3
#define NC_OPEN_EVENTINIT_FAILED    -4


/* Close down the run-time environment */
_extern void NC_SystemClose();

/* Start the network using the supplied configuration */
_extern int NC_NetStart( HANDLE hCfg, void (*NetStart)(),
                        void (*NetStop)(), void (*NetIP)(IPN,uint,uint) );

/* Stop the network */
_extern void NC_NetStop( int rc );

/* Called when Boot thread has completed */
_extern void NC_BootComplete();

/* Called when IP address is added or removed */
_extern void NC_IPUpdate( IPN IPAddr, uint IfIdx, uint fAdd );

/* Called to set the user function that's called when link goes up/down */
_extern void NC_setLinkHook( void (*LinkHook)(int) );

#endif
