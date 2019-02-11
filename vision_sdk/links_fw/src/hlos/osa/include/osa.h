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


#ifndef _OSA_H_
#define _OSA_H_

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#ifndef QNX_BUILD
#ifndef ANDROID
#include <execinfo.h>
#endif
#endif
#include <osa_types.h>

#include <include/link_api/system_inter_link_api.h>
#include <include/link_api/systemLink_common.h>

#define OSA_DEBUG_FILE // enable printf's during OSA_fileXxxx
#define OSA_PRF_ENABLE // enable profiling APIs

#define OSA_SOK      0  ///< Status : OK
#define OSA_EFAIL   -1  ///< Status : Generic error

#ifndef _TI_STD_TYPES
#define _TI_STD_TYPES

/* unsigned quantities */
typedef unsigned long long Uint64;      ///< Unsigned 64-bit integer
#ifndef QNX_BUILD
typedef unsigned int Uint32;            ///< Unsigned 32-bit integer
typedef unsigned short Uint16;          ///< Unsigned 16-bit integer
typedef unsigned char Uint8;            ///< Unsigned  8-bit integer
#endif
/* signed quantities */
typedef long long Int64;               ///< Signed 64-bit integer

#ifndef QNX_BUILD
typedef unsigned int Uns;              ///< Unsigned int
#endif

typedef   void *  OSA_PTR;

#define OSA_SUSPEND     (0xFFFFFFFF)
#define OSA_NO_SUSPEND  (0)


#endif /* _TI_STD_TYPES */

#ifndef KB
#define KB ((Uint32)1024)
#endif

#ifndef MB
#define MB (KB*KB)
#endif

#define OSA_TIMEOUT_NONE        ((Uint32) 0)  // no timeout
#define OSA_TIMEOUT_FOREVER     ((Uint32)-1)  // wait forever

#define OSA_memAlloc(size)      (void*)malloc((size))
#define OSA_memFree(ptr)        free(ptr)

#define OSA_align(value, align)   ((( (value) + ( (align) - 1 ) ) / (align) ) * (align) )

#define OSA_floor(value, align)   (( (value) / (align) ) * (align) )
#define OSA_ceil(value, align)    OSA_align(value, align)

#define OSA_SNPRINTF(sbuf,...)                                               \
                                do {                                           \
                                    snprintf (sbuf, sizeof(sbuf) - 1,          \
                                              __VA_ARGS__);                    \
                                    sbuf[sizeof(sbuf) - 1] = 0;                \
                                } while (0)

#define OSA_ARRAYSIZE(array)             ((sizeof(array)/sizeof((array)[0])))

#define OSA_ARRAYINDEX(elem,array)       ((elem) - &((array)[0]))

#define OSA_ARRAYISVALIDENTRY(elem,array) ((OSA_ARRAYINDEX(elem,array) <   \
                                             OSA_ARRAYSIZE(array))           \
                                             ? TRUE                            \
                                             : FALSE)
#define OSA_DIV(num,den)                  (((den) != 0) ? ((num)/(den)) : 0)

#define OSA_ISERROR(status)               ((status < 0) ? TRUE : FALSE)
#include <osa_debug.h>

int OSA_init(void);
int OSA_deInit(void);

int OSA_globalTimerInit(void);
int OSA_globalTimerDeInit(void);

Int32 Vps_printf(const char * format, ... );

/**
 *******************************************************************************
 *
 * \brief Context information related to skipping of buffer's
 *
 *******************************************************************************
 */
typedef struct {
    Int32 inputFrameRate;
    /**< Incoming buffer frame-rate */

    Int32 outputFrameRate;
    /**< Outgoing buffer frame-rate */

    Int32 firstTime;
    /**< Flag to indicate if buffer skiplogic is being called for first frame */

    Int32 inCnt;
    /**< Current rate of incoming buffers */

    Int32 outCnt;
    /**< Current rate of outgoing buffers */

    Int32 multipleCnt;
    /**< inputFrameRate x outputFrameRate */

} OSA_BufSkipContext;

Uint32 OSA_getCurTimeInMsec(void);

void   OSA_waitMsecs(Uint32 msecs);
#ifndef QNX_BUILD
int    OSA_attachSignalHandler(int sigId, void (*handler)(int ) );
#else
int OSA_attachSignalHandler(struct sigevent *event, void (*handler)(int ));
#endif

int OSA_syncGlobalTime();

UInt64 OSA_getCurGlobalTimeInUsec(void);
UInt64 OSA_getCurGlobalTimeInMsec(void);
Void OSA_resetSkipBufContext(OSA_BufSkipContext *skipCtx,
                               UInt32 inputFrameRate,
                               UInt32 outputFrameRate);
Bool OSA_doSkipBuf(OSA_BufSkipContext *skipCtx );

int xstrtoi(char *hex);

#endif /* _OSA_H_ */



