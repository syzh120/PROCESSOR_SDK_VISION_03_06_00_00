/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 */
/*
 *  ======== _IpcLog.h ========
 */

#ifndef _IpcLog_
#define _IpcLog_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern Bool IpcLog_logFile;
extern FILE * IpcLog_logPtr;

/* macros for writing to log file: */
#define LOG0(a)  \
    if (IpcLog_logFile == TRUE) \
        {  fprintf(IpcLog_logPtr, a); fflush(IpcLog_logPtr); }

#define LOG1(a, b)  \
    if (IpcLog_logFile == TRUE) \
        {  fprintf(IpcLog_logPtr, a, b); fflush(IpcLog_logPtr); }

#define LOG2(a, b, c)  \
    if (IpcLog_logFile == TRUE) \
        {  fprintf(IpcLog_logPtr, a, b, c); fflush(IpcLog_logPtr); }


/* macros for generating verbose output: */
#define PRINTVERBOSE0(a)  \
    if (verbose == TRUE) {  printf(a); }

#define PRINTVERBOSE1(a, b)  \
    if (verbose == TRUE) {  printf(a, b); }

#define PRINTVERBOSE2(a, b, c)  \
    if (verbose == TRUE) {  printf(a, b, c); }

#define PRINTVERBOSE3(a, b, c, d)  \
    if (verbose == TRUE) {  printf(a, b, c, d); }


#ifdef __cplusplus
}
#endif

#endif
