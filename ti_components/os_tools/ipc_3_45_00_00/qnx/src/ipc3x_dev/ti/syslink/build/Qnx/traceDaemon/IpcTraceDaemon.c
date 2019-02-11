/*
 *  @file  IpcTraceDaemon.c
 *
 *  @brief  Daemon for remote core IPC traces
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2010-2014, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

/* OS-specific headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/procmgr.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ti/syslink/Std.h>
#include <_MultiProc.h>
#include <limits.h>
#include <ti/ipc/MultiProc.h>

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

#define TRACE_BUFFER_SIZE               0x8000

/* Default polling interval */
#define TIMEOUT_USECS                   500000

static char traceBuffer[TRACE_BUFFER_SIZE];
static useconds_t timeout = TIMEOUT_USECS;

static FILE *log;
sem_t        semPrint; /* Semaphore to allow only one thread to print at once */

/* pull char from queue */
void printTraces (void *arg)
{
    int32_t           index = (int32_t)arg;
    int32_t           numOfBytesInBuffer  = 0;
    uint32_t          readPointer         = 0;
    int               fd                  = -1;
    char              path[_POSIX_PATH_MAX];

    fprintf (log, "\nSpawning procId %d trace thread\n ", index);

    /* Initialize read indexes to zero */
    snprintf (path, _POSIX_PATH_MAX, "/dev/ipc-trace/%s", MultiProc_getName(index));
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Unable to open ipc-trace");
        goto EXIT;
    }
    do {
        sem_wait(&semPrint);    /* Acquire exclusive access to printing */
        while ((numOfBytesInBuffer = read(fd, traceBuffer, TRACE_BUFFER_SIZE)) > 0) {
            readPointer = 0;
            fprintf (log, "\n[ProcId %d]: ", index);
            while ( numOfBytesInBuffer-- ) {
                fprintf (log, "%c", traceBuffer[readPointer]);
                if (traceBuffer[readPointer] == '\n') {
                    fprintf (log, "[ProcId %d]: ", index);
                }

                readPointer++;
            }
        }
        fflush (log);
        sem_post(&semPrint);    /* Release exclusive access to printing */
        if (numOfBytesInBuffer < 0) {
            perror ("\nError reading from ipc-trace");
            break;
        }
        usleep(timeout);
    } while(1);

    close(fd);
EXIT:
    fprintf (log, "Leaving printTraces thread function for ProcId %d\n", index);
    return;
}


/** print usage and exit */
static void printUsageExit (char * app)
{
    printf ("%s: [-h] [-l logfile] [-f] [-t interval]\n", app);
    printf ("  -h   show this help message\n");
    printf ("  -l   select file to log to (default stdout)\n");
    printf ("  -f   run in foreground (do not fork daemon process)\n");
    printf ("  -t   polling interval in microseconds (default %d)\n",
        TIMEOUT_USECS);

    exit (EXIT_SUCCESS);
}

int main (int argc, char * argv [])
{
    pthread_t   threads[MultiProc_MAXPROCESSORS]; /* server thread object */
    char      * log_file    = NULL;
    bool        daemon      = true;
    int         i;
    struct stat sbuf;
    char        names[MultiProc_MAXPROCESSORS][_POSIX_PATH_MAX];
    int         c;

    /* parse cmd-line args */
    while (1) {
        c = getopt(argc, argv, "l:fht:");
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'l':
                log_file = optarg;
                break;

            case 'f':
                daemon = false;
                break;

            case 'h':
                printUsageExit (argv[0]);
                break;

            case 't':
                timeout = atoi(optarg);
                printf("Using polling interval of %d us\n", timeout);
                break;

            default:
                fprintf (stderr, "Unrecognized argument\n");
        }
    }

    if (!log_file) {
        log = stdout;
    }
    else {
        log = fopen (log_file, "a+");
        if (log == NULL) {
            printf("Bad filename specified for log file\n");
            printUsageExit(argv[0]);
        }
    }

    printf ("Spawning IPC Trace daemon...\n");

    /* background the process, if requested */
    if (daemon) {
        procmgr_daemon(0, PROCMGR_DAEMON_NOCLOSE|PROCMGR_DAEMON_NODEVNULL);
    }

    sem_init(&semPrint, 0, 1);
    for (i = 0; i < MultiProc_getNumProcessors(); i++) {
        snprintf (names[i], _POSIX_PATH_MAX, "/dev/ipc-trace/%s", MultiProc_getName(i));
        if (-1 != stat(names[i], &sbuf)) {
            pthread_create (&threads[i], NULL, (void *)&printTraces, (void *)i);
        }
        else
            threads[i] = NULL;
    }

    for (i = 0; i < MultiProc_MAXPROCESSORS; i++) {
        if (threads[i])
            pthread_join(threads[i], NULL);
    }

    sem_destroy(&semPrint);

    return 0;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
