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

#ifndef _OSA_DEBUG_H_
#define _OSA_DEBUG_H_

#include <stdio.h>
#include "osa_types.h"

#ifdef QNX_BUILD
#include <sys/slog.h>
#include <sys/slogcodes.h>
#define _SLOGC_INFOADAS_LOCAL _SLOG_SETCODE(10101,0)
#define _SLOGC_INFOADAS_REMOTELOG _SLOG_SETCODE(10101,1)
#endif

#define OSA_DEBUG_MODE

// printf wrapper that can be turned on and off by defining/undefining
#ifdef OSA_DEBUG_MODE

#ifndef QNX_BUILD
  #define OSA_printf(...)  do { printf(" [HOST] " __VA_ARGS__); fflush(stdout); } while(0)
#else
  #define OSA_printf(...) slogf(_SLOGC_INFOADAS_LOCAL, _SLOG_INFO, "[HOST  ] " __VA_ARGS__)
  #define std_printf  printf
#endif

// #define __KLOCWORK__
#ifdef __KLOCWORK__
  #define OSA_assert(x)  \
  { \
    if( (x) == 0) { \
      fprintf(stderr, " ASSERT (%s|%s|%d)\r\n", __FILE__, __func__, __LINE__); \
      abort();\
    } \
  }
#else
  #define OSA_assert(x)  \
  { \
    if( (x) == 0) { \
      fprintf(stderr, " ASSERT (%s|%s|%d)\r\n", __FILE__, __func__, __LINE__); \
      while (getchar()!='q')  \
        ; \
    } \
  }
#endif
    #define UTILS_assert(x)   OSA_assert(x)

#define OSA_DEBUG \
  fprintf(stderr, " @ %s:%s:%d \n", __FILE__, __func__, __LINE__);


#define OSA_DEBUG_WAIT \
  OSA_DEBUG \
  fprintf(stderr, " Press Any key to continue !!!\n"); \
  getchar();

#define OSA_COMPILETIME_ASSERT(condition)                                       \
                   do {                                                         \
                       typedef char ErrorCheck[((condition) == TRUE) ? 1 : -1]; \
                   } while(0)

#else

  #define OSA_printf(...)
  #define OSA_assert(x)
  #define UTILS_assert(x)
  #define OSA_DEBUG
  #define OSA_DEBUG_WAIT
#endif

// printf wrapper that can be used to display errors. Prefixes all text with
// "ERROR" and inserts the file and line number of where in the code it was
// called
#define OSA_ERROR(...) \
  do \
  { \
  fprintf(stderr, " ERROR  (%s|%s|%d): ", __FILE__, __func__, __LINE__); \
  fprintf(stderr, __VA_ARGS__); \
  } \
  while(0);

#define OSA_assertSuccess(ret)  OSA_assert(ret==OSA_SOK)

void OSA_enableRemoteLogClient(Bool flag);
Bool OSA_isRemoteLogClientEnabled(void);

#endif  //_OSA_DEBUG_H_



