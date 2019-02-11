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
 * ========  ========
 *
 * Telnet server utility
 *
 */

#ifndef _TELNET_H_
#define _TELNET_H_

#include <netmain.h>
#include <_stack.h>

/* TELNET Commands */
#define CMD_SE      240         /* End of sub-negotiation parameters */

#define CMD_NOP     241         /* No operation */
#define CMD_DM      242         /* The stream data portion of a Synch. */
                                /* This should awlays be accompanied */
                                /* by a TCP Urgent notification */
#define CMD_BREAK   243         /* NVT character BRK */
#define CMD_IP      244         /* The Interrupt process function */
#define CMD_AO      245         /* The Abort Output function */
#define CMD_AYT     246         /* The Are You There function */
#define CMD_EC      247         /* The Erase Character function */
#define CMD_EL      248         /* The Erase Line function */
#define CMD_GA      249         /* The Go Ahead signal */
#define CMD_SB      250         /* Indicates that subnegotiation follows */
#define CMD_WILL    251         /* Desire for us to begin option */
#define CMD_WONT    252         /* Desire for us to cease option */
#define CMD_DO      253         /* Desire for them to begin option */
#define CMD_DONT    254         /* Desire for them to cease option */
#define CMD_IAC     255         /* Interpret As Command (also data byte 255) */

/* Options for will, wont, do, dont, sb, se */
#define OPT_BINARY   0          /* Transmit binary */
#define OPT_ECHO     1          /* Echo characters received over connection */
#define OPT_SGA      3          /* Suppress Go Ahead */
#define OPT_STATUS   5          /* Give Status */
#define OPT_TM       6          /* Timing Mark (data synchronization) */
#define OPT_EXOPL    255        /* Extended Options List */

/* Local Option Status Decoding */
/* bit 0 :  0 = WONT   1 = WILL */
/* bit 1 :  0 = DONT   1 = DO */
/* bit 2 :  1 = Not Used */
/* bit 3 :  1 = Referenced (flags first peer negotiation) */
#define OS_WONT                 0x0
#define OS_WILL                 0x1
#define OS_DONT                 0x0
#define OS_DO                   0x2

#endif
