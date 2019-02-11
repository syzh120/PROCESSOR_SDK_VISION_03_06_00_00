/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== main_host.c ========
 *
 */

/* cstdlib header files */
#include <stdio.h>
#include <stdlib.h>

/* package header files */
#include <ti/ipc/Std.h>
#include <ti/ipc/Ipc.h>
#include <ti/ipc/MultiProc.h>
#include <ti/ipc/transports/TransportRpmsg.h>

#include <ti/cmem.h>

/* local header files */
#include "GateMPApp.h"

/* private functions */
static Int Main_main(Void);
static Int Main_parseArgs(Int argc, Char *argv[]);


#define Main_USAGE "\
Usage:\n\
    GateMPApp [options]\n\
\n\
Options:\n\
    h   : print this help message\n\
\n\
Examples:\n\
    GateMPApp\n\
    GateMPApp -h\n\
\n"


/*
 *  ======== main ========
 */
Int main(Int argc, Char* argv[])
{
    Int status;

    printf("--> main:\n");

    /* parse command line */
    status = Main_parseArgs(argc, argv);

    if (status < 0) {
        goto leave;
    }

    status = CMEM_init();
    if (status < 0) {
        printf("CMEM_init failed\n");
        goto leave;
    }
    else {
        printf("CMEM_init success\n");
    }

    /* configure the transport factory */
    Ipc_transportConfig(&TransportRpmsg_Factory);

    /* IPC initialization */
    status = Ipc_start();

    if (status >= 0) {
        /* application create, exec, delete */
        status = Main_main();

        /* Ipc finalization */
        Ipc_stop();
    }
    else {
        printf("Ipc_start failed: status = %d\n", status);
        goto leave;
    }

leave:
    printf("<-- main:\n");
    status = (status >= 0 ? 0 : status);

    return (status);
}


/*
 *  ======== Main_main ========
 */
Int Main_main(Void)
{
    Int         status = 0;

    printf("--> Main_main:\n");

    /* BEGIN application phase */

    /* application create phase */
    status = GateMPApp_create();

    if (status < 0) {
        goto leave;
    }

    /* application execute phase */
    status = GateMPApp_exec();

    if (status < 0) {
        goto leave;
    }

    /* application delete phase */
    status = GateMPApp_delete();

    if (status < 0) {
        goto leave;
    }

leave:
    printf("<-- Main_main:\n");

    status = (status >= 0 ? 0 : status);
    return (status);
}


/*
 *  ======== Main_parseArgs ========
 */
Int Main_parseArgs(Int argc, Char *argv[])
{
    Int             x, cp, opt;
    Int             status = 0;


    /* parse the command line options */
    for (opt = 1; (opt < argc) && (argv[opt][0] == '-'); opt++) {
        for (x = 0, cp = 1; argv[opt][cp] != '\0'; cp++) {
            x = (x << 8) | (int)argv[opt][cp];
        }

        switch (x) {
            case 'h': /* -h */
                printf("%s", Main_USAGE);
                exit(0);
                break;

            default:
                printf(
                    "Error: %s, line %d: invalid option, %c\n",
                    __FILE__, __LINE__, (Char)x);
                printf("%s", Main_USAGE);
                status = -1;
                goto leave;
        }
    }

    /* parse the command line arguments */
    if (opt < argc) {
        printf(
            "Error: %s, line %d: too many arguments\n",
            __FILE__, __LINE__);
        printf("%s", Main_USAGE);
        status = -1;
        goto leave;
    }

leave:
    return(status);
}
