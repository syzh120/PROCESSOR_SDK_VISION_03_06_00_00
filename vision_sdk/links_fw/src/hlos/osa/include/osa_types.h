/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if !defined(STD_H)
#define STD_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#if defined (__cplusplus)
extern "C" {
#endif

typedef char              Char;
#ifndef ANDROID
typedef unsigned char     UChar;
#endif
typedef short             Short;
typedef unsigned short    UShort;
typedef int               Int;
typedef unsigned int      UInt;
typedef long              Long;
typedef unsigned long     ULong;
typedef float             Float;
typedef double            Double;
typedef long double       LDouble;
typedef void              Void;


typedef unsigned short    Bool;
typedef void            * Ptr;       /* data pointer */
typedef char            * String;    /* null terminated string */


typedef int            *  IArg;
typedef unsigned int   *  UArg;
typedef char              Int8;
typedef short             Int16;
typedef int               Int32;

typedef unsigned char     Uint8;
typedef unsigned short    Uint16;
typedef unsigned int      Uint32;

typedef unsigned int      Uns;

typedef unsigned char     UInt8;
typedef unsigned short    UInt16;
typedef unsigned int      UInt32;
typedef unsigned int      SizeT;
typedef unsigned char     Bits8;
typedef unsigned short    Bits16;
typedef UInt32            Bits32;
typedef unsigned long long UInt64;
#ifndef TRUE
#define TRUE              1
#endif

#ifndef FALSE
#define FALSE             0
#endif

/*! Data type for errors */
typedef UInt32            Error_Block;

/*! Initialize error block */
#define Error_init(eb) *eb = 0

#include <osa_debug.h>

#define Task_sleep(x)  usleep(x)

#if defined (__cplusplus)
}
#endif

#endif

