/*
 * Copyright (c) 2012-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== _lad.h ========
 */

#ifndef _lad_
#define _lad_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/ipc/MessageQ.h>
#include <_MessageQ.h>
#include <ti/ipc/NameServer.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>
#include <stdio.h>
#include <ti/ipc/GateMP.h>
#include <_GateMP.h>
#include <_Ipc.h>
#include <GateHWSpinlock.h>
#include <sys/time.h>
#include <ti/ipc/namesrv/_NameServerRemoteRpmsg.h>

extern Bool logFile;
extern FILE *logPtr;
extern struct timeval start_tv;

/*
 * Macros for writing to log file.
 *
 * For the timestamp prefix, subtract the start time (which is established
 * when the logFile is opened) so that the massive "since the epoch" value
 * is not displayed.  For this, subtract only the timeval.tv_sec (seconds)
 * value so we don't have to worry about the "borrow" that results when
 * start_tv.tv_usec > tv.tv_usec.
 */
#define LOG0(a)  \
    if (logFile == TRUE) { \
        struct timeval tv; \
        gettimeofday(&tv, NULL); \
        fprintf(logPtr, "[%d.%06d] " a, \
                (unsigned int)(tv.tv_sec - start_tv.tv_sec), \
                (unsigned int)tv.tv_usec); \
        fflush(logPtr); \
    }

#define LOG1(a, b)  \
    if (logFile == TRUE) { \
        struct timeval tv; \
        gettimeofday(&tv, NULL); \
        fprintf(logPtr, "[%d.%06d] " a, \
                (unsigned int)(tv.tv_sec - start_tv.tv_sec), \
                (unsigned int)tv.tv_usec, b); \
        fflush(logPtr); \
    }

#define LOG2(a, b, c)  \
    if (logFile == TRUE) { \
        struct timeval tv; \
        gettimeofday(&tv, NULL); \
        fprintf(logPtr, "[%d.%06d] " a, \
                (unsigned int)(tv.tv_sec - start_tv.tv_sec), \
                (unsigned int)tv.tv_usec, b, c); \
        fflush(logPtr); \
    }

#define LOG3(a, b, c, d)  \
    if (logFile == TRUE) { \
        struct timeval tv; \
        gettimeofday(&tv, NULL); \
        fprintf(logPtr, "[%d.%06d] " a, \
                (unsigned int)(tv.tv_sec - start_tv.tv_sec), \
                (unsigned int)tv.tv_usec, b, c, d); \
        fflush(logPtr); \
    }

#define LOG4(a, b, c, d, e)  \
    if (logFile == TRUE) { \
        struct timeval tv; \
        gettimeofday(&tv, NULL); \
        fprintf(logPtr, "[%d.%06d] " a, \
                (unsigned int)(tv.tv_sec - start_tv.tv_sec), \
                (unsigned int)tv.tv_usec, b, c, d, e); \
        fflush(logPtr); \
    }

/* macros for generating verbose output: */
#define PRINTVERBOSE0(a)  \
    if (verbose == TRUE) {  printf(a); }

#define PRINTVERBOSE1(a, b)  \
    if (verbose == TRUE) {  printf(a, b); }

#define PRINTVERBOSE2(a, b, c)  \
    if (verbose == TRUE) {  printf(a, b, c); }

#define PRINTVERBOSE3(a, b, c, d)  \
    if (verbose == TRUE) {  printf(a, b, c, d); }


/* LAD commmand FIFO strings: */
#if defined (IPC_BUILDOS_ANDROID)
#define LAD_COMMANDFIFO         "/data/lad/LAD/LADCMDS"
#define LAD_ROOTDIR             "/data/lad/"
#define LAD_WORKINGDIR          "/data/lad/LAD/"
#else
#define LAD_COMMANDFIFO         "/tmp/LAD/LADCMDS"
#define LAD_ROOTDIR             "/tmp/"
#define LAD_WORKINGDIR          "/tmp/LAD/"
#endif

#define LAD_RESPONSEFIFOPATH    LAD_WORKINGDIR
#define LAD_PROTOCOLVERSION     "03000000"    /*  MMSSRRRR */

#define LAD_MAXNUMCLIENTS  32      /* max simultaneous clients */
#define LAD_CONNECTTIMEOUT 5.0  /* LAD connect response timeout (sec) */
#define LAD_DISCONNECTTIMEOUT   5.0  /* LAD disconnect timeout (sec) */
#define LAD_MAXLENGTHFIFONAME   128  /* max length client FIFO name */
#define LAD_MAXLENGTHCOMMAND    512  /* size limit for LAD command string */
#define LAD_MAXLENGTHRESPONSE   512  /* size limit for LAD response string */
#define LAD_MAXLENGTHPROTOVERS  16   /* size limit for protocol version */
#define LAD_MAXLOGFILEPATH 256  /* size limit for LAD log file path */
#define LAD_COMMANDLENGTH       sizeof(struct LAD_CommandObj)
#define LAD_RESPONSELENGTH      sizeof(union LAD_ResponseObj)

#define LAD_MESSAGEQCREATEMAXNAMELEN 32

#define LAD_MAXENTRYNAMELEN  MAXNAMEINCHAR /* max for LAD NameServer name */
#define LAD_MAXENTRYVALUELEN 32  /* size limit for LAD NameServer value */

typedef enum {
    LAD_CONNECT = 0,
    LAD_DISCONNECT,
    LAD_IPC_GETCONFIG,
    LAD_NAMESERVER_SETUP,
    LAD_NAMESERVER_DESTROY,
    LAD_NAMESERVER_PARAMS_INIT,
    LAD_NAMESERVER_CREATE,
    LAD_NAMESERVER_DELETE,
    LAD_NAMESERVER_ADD,
    LAD_NAMESERVER_GET,
    LAD_NAMESERVER_ADDUINT32,
    LAD_NAMESERVER_GETUINT32,
    LAD_NAMESERVER_GETLOCAL,
    LAD_NAMESERVER_GETLOCALUINT32,
    LAD_NAMESERVER_REMOVE,
    LAD_NAMESERVER_REMOVEENTRY,
    LAD_NAMESERVER_ATTACH,
    LAD_NAMESERVER_DETACH,
    LAD_MESSAGEQ_GETCONFIG,
    LAD_MESSAGEQ_SETUP,
    LAD_MESSAGEQ_DESTROY,
    LAD_MESSAGEQ_CREATE,
    LAD_MESSAGEQ_ANNOUNCE,
    LAD_MESSAGEQ_DELETE,
    LAD_MESSAGEQ_MSGINIT,
    LAD_MULTIPROC_GETCONFIG,
    LAD_GATEMP_ATTACH,
    LAD_GATEMP_DETACH,
    LAD_GATEMP_START,
    LAD_GATEMP_GETNUMRESOURCES,
    LAD_GATEMP_GETFREERESOURCE,
    LAD_GATEMP_RELEASERESOURCE,
    LAD_GATEMP_ISSETUP,
    LAD_GATEHWSPINLOCK_GETCONFIG,
    LAD_EXIT
} _LAD_Command;

struct LAD_CommandObj {
    Int cmd;
    Int clientId;
    union {
        struct {
            Int pid;
            Char name[LAD_MAXLENGTHFIFONAME];
            Char protocol[LAD_MAXLENGTHPROTOVERS];
        } connect;
        struct {
            Int procId;
            Int rprocId;
        } rprocSetId;
        struct {
            Char name[LAD_MAXENTRYNAMELEN];
            NameServer_Params params;
        } create;
        struct {
            NameServer_Handle handle;
        } nsdelete;
        struct {
            NameServer_Handle handle;
            Char name[LAD_MAXENTRYNAMELEN];
            UInt8 buf[LAD_MAXENTRYVALUELEN];
            UInt32 len;
        } add;
        struct {
            NameServer_Handle handle;
            Char name[LAD_MAXENTRYNAMELEN];
            UInt32 len;
            UInt16 procId[MultiProc_MAXPROCESSORS];
        } get;
        struct {
            NameServer_Handle handle;
            Char name[LAD_MAXENTRYNAMELEN];
            UInt32 val;
        } addUInt32;
        struct {
            NameServer_Handle handle;
            Char name[LAD_MAXENTRYNAMELEN];
            UInt16 procId[MultiProc_MAXPROCESSORS];
        } getUInt32;
        struct {
            NameServer_Handle handle;
            Char name[LAD_MAXENTRYNAMELEN];
            UInt32 len;
        } getLocal;
        struct {
            NameServer_Handle handle;
            Char name[LAD_MAXENTRYNAMELEN];
        } getLocalUInt32;
        struct {
            NameServer_Handle handle;
            Char name[LAD_MAXENTRYNAMELEN];
        } remove;
        struct {
            NameServer_Handle handle;
            Ptr entryPtr;
        } removeEntry;
        struct {
            UInt16 procId;
        } attach;
        struct {
            UInt16 procId;
        } detach;
        struct {
            MessageQ_Config cfg;
        } messageQSetup;
        struct {
            Char name[LAD_MESSAGEQCREATEMAXNAMELEN];
            MessageQ_Params params;
        } messageQCreate;
        struct {
            Char name[LAD_MESSAGEQCREATEMAXNAMELEN];
            Void *serverHandle;
        } messageQAnnounce;
        struct {
            Void *serverHandle;
        } messageQDelete;
        struct {
            GateMP_RemoteProtect type;
        } gateMPGetNumResources;
        struct {
            GateMP_RemoteProtect type;
        } gateMPGetFreeResource;
        struct {
            GateMP_RemoteProtect type;
            Int32 id;
        } gateMPReleaseResource;
        struct {
            Bool result;
        } gateMPIsSetup;
    } args;
};

union LAD_ResponseObj {
    struct {
       Int status;
       UInt32 len;
       UInt8 buf[LAD_MAXENTRYVALUELEN];
    } get;
    struct {
       Int status;
       UInt32 val;
    } getUInt32;
    struct {
       Int status;
       Int assignedId;
    } connect;
    struct {
       Int status;
       NameServer_Handle handle;
    } nsdelete;
    struct {
       Int status;
       NameServer_Handle nameServerHandle;
    } setup;
    struct {
       Int status;
       Int queueId;
       Void *serverHandle;
    } messageQCreate;
    struct {
       Int status;
    } messageQAnnounce;
    struct {
       Int status;
    } messageQDelete;
    struct {
       Int status;
       MessageQ_MsgHeader msg;
    } msgInit;
    struct {
       Int status;
       MessageQ_Config cfg;
    } messageQGetConfig;
    struct {
       Int status;
       MultiProc_Config cfg;
    } multiprocGetConfig;
    struct {
       Int status;
       NameServer_Handle nameServerHandle;
    } gateMPStart;
    struct {
       Int status;
       Int32 value;
    } gateMPGetNumResources;
    struct {
       Int status;
       Int32 id;
    } gateMPGetFreeResource;
    struct {
       Int status;
    } gateMPReleaseResource;
    struct {
       Int status;
       Bool result;
    } gateMPIsSetup;
    struct {
       Int status;
       GateHWSpinlock_Config cfgParams;
    } gateHWSpinlockGetConfig;
    Ipc_Config ipcConfig;
    NameServer_Params params;
    NameServer_Handle handle;
    Ptr entryPtr;
    Int status;
};


#ifdef __cplusplus
}
#endif

#endif
