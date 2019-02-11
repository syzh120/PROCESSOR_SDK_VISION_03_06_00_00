/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 *  ======== lad.c ========
 */

#include <ti/ipc/Std.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>

#include <ti/ipc/MessageQ.h>
#include <_MessageQ.h>
#include <ti/ipc/NameServer.h>
#include <_NameServer.h>
#include <ti/ipc/GateMP.h>
#include <_GateMP_daemon.h>
#include <_MultiProc.h>

#include <GateHWSpinlock.h>

#include <ladclient.h>
#include <_lad.h>

#ifndef DAEMON
#define DAEMON        1           /* 1 = run as a daemon; 0 = run as app */
#endif

#define READ_BUF_SIZE 50

Bool logFile = FALSE;
FILE *logPtr = NULL;
struct timeval start_tv;

static String commandFIFOFile = LAD_COMMANDFIFO;
static FILE *commandFIFOFilePtr = NULL;

#if defined(GATEMP_SUPPORT)
static Bool gatempEnabled = FALSE;
#endif

/* LAD client info arrays */
static Bool clientConnected[LAD_MAXNUMCLIENTS];
static UInt clientPID[LAD_MAXNUMCLIENTS];
static Char clientFIFOName[LAD_MAXNUMCLIENTS][LAD_MAXLENGTHFIFONAME];
static FILE * responseFIFOFilePtr[LAD_MAXNUMCLIENTS];

/* local internal routines */
static Bool isDaemonRunning(Char *pidName);
static LAD_ClientHandle assignClientId(Void);
static Void cleanupFifos(Void);
static Void cleanupDepartedClients(Void);
static Int connectToLAD(String clientName, Int pid, String clientProto, Int *clientIdPtr);
static Void disconnectFromLAD(Int clientId);
static Void doDisconnect(Int clientId);

struct LAD_CommandObj cmd;
union LAD_ResponseObj rsp;

#define LAD_USAGE "\
Usage:\n\
    lad_<platform> [options] \n\
\n\
Options:\n\
    h            : print this help message\n\
    g            : enable GateMP support \n\
    l <logfile>  : name of logfile for LAD\n\
    n <nprocs>   : total number of processors in the system\n\
    p <oct value>: set LAD's directory permissions\n\
    r <nreserve> : number of reserved queues\n\
    s <synctype> : type of Ipc_ProcSync (ALL|PAIR|NONE)\n\
    b <value>    : Processor's base cluster id \n\
\n\
Examples:\n\
    lad_<platform> -h\n\
    lad_<platform> -l log.txt\n\
    lad_<platform> -l log.txt -p 777\n\
    lad_<platform> -g -l log.txt\n\
    lad_<platform> -l log.txt -b 10\n\
\n"

/*
 *  ======== main ========
 */
int main(int argc, char * argv[])
{
    MessageQ_Handle handle;
    Ipc_Config ipcCfg;
    UInt16 *procIdPtr;
    Int statusIO;
    Int clientId;
    Int command;
    Int flags;
    Int i;
    Int n;
    Int c;
#if defined(GATEMP_SUPPORT)
    Int status;
    UInt16 procId;
#endif
    String tmpString;
#if DAEMON
    pid_t pid;
    pid_t sid;
#endif

    /* change to LAD's root directory */
    if ((chdir(LAD_ROOTDIR)) < 0) {
        /* if can't change directory assume it needs to be created, do it */
        if ((mkdir(LAD_ROOTDIR, 0666)) < 0) {
            fprintf(stderr,
                    "\nERROR: Failed to create LAD's root directory!\n");
            exit(EXIT_FAILURE);
        }
    }

#ifndef IPC_BUILDOS_ANDROID
    if (isDaemonRunning(argv[0])) {
        printf("Multiple instances of LAD are not supported!\n");
        exit(EXIT_FAILURE);
    }
#endif

    /* change to LAD's working directory */
    if ((chdir(LAD_WORKINGDIR)) < 0) {

        /* if can't change directory assume it needs to be created, do it */
        if ((mkdir(LAD_WORKINGDIR, 0666)) < 0) {
            fprintf(stderr,
                    "\nERROR: Failed to create LAD's working directory!\n");
            exit(EXIT_FAILURE);
        }
        /* now change to the new directory */
        if ((chdir(LAD_WORKINGDIR)) < 0) {
            fprintf(stderr,
                    "\nERROR: Failed to change to LAD's working directory!\n");
            exit(EXIT_FAILURE);
        }
    } else {
        cleanupFifos();
    }

    /* process command line args */
    while (1) {
        c = getopt(argc, argv, "b:ghl:n:p:r:s:");
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'g':
#if defined(GATEMP_SUPPORT)
                printf("\nGateMP support enabled on host\n");
                gatempEnabled = TRUE;
#else
                printf("\nGateMP is not supported for this device\n");
#endif
                break;
            case 'b':
                printf("\nSet LAD's base cluster id to %s\n", optarg);
                _MultiProc_cfg.id = atoi(optarg);
                _MultiProc_cfg.baseIdOfCluster = atoi(optarg);
                break;
            case 'h':
                printf("%s", LAD_USAGE);
                exit(0);
                break;
            case 'l':
                logPtr = fopen(optarg, "w");
                if (logPtr == NULL) {
                    fprintf(stderr, "\nERROR: unable to open log file %s\n",
                            optarg);
                    exit(EXIT_FAILURE);
                }
                else {
                    logFile = TRUE;
                    gettimeofday(&start_tv, NULL);
                    printf("\nOpened log file: %s\n", optarg);
                    /* close log file upon LAD termination */
                    flags = fcntl(fileno(logPtr), F_GETFD);
                    if (flags != -1) {
                        fcntl(fileno(logPtr), F_SETFD, flags | FD_CLOEXEC);
                    }
                }
                break;
            case 'n':
                printf("\nSet LAD's number of processors to %s\n", optarg);
                _MultiProc_cfg.numProcessors = atoi(optarg);
                break;
            case 'p':
                printf("\nSet LAD's directory permissions to '%s'\n", optarg);
                chmod(LAD_ROOTDIR, strtol(optarg, NULL, 8));
                chmod(LAD_WORKINGDIR, strtol(optarg, NULL, 8));
                break;
            case 'r':
                printf("\nSet LAD's number of reserved queues to %s\n", optarg);
                _MessageQ_setNumReservedEntries(atoi(optarg));
                break;
            case 's':
                printf("\nSet LAD's synchronization scheme to ProcSync_%s\n",
                       optarg);

                Ipc_getConfig(&ipcCfg);

                if (!strcmp(optarg, "ALL")) {
                    ipcCfg.procSync = Ipc_ProcSync_ALL;
                }
                else if (!strcmp(optarg, "PAIR")) {
                    ipcCfg.procSync = Ipc_ProcSync_PAIR;
                }
                else if (!strcmp(optarg, "NONE")) {
                    ipcCfg.procSync = Ipc_ProcSync_NONE;
                }
                else {
                    fprintf(stderr,
                            "Error: bad synchronization specified, must be "
                            "ALL|PAIR|NONE\n");
                    exit(EXIT_FAILURE);
                }

                Ipc_setConfig(&ipcCfg);
                break;
            default:
                fprintf (stderr, "\nUnrecognized argument\n");
                exit(EXIT_FAILURE);
        }
    }

    /* Check to ensure id and baseId are not invalid */
    printf ("\nnumProcessors = %d id = %d baseId = %d\n",
            _MultiProc_cfg.numProcessors, _MultiProc_cfg.id,
            _MultiProc_cfg.baseIdOfCluster);

    if (_MultiProc_cfg.id == 0xFFFF ||
        _MultiProc_cfg.baseIdOfCluster == 0xFFFF) {
         fprintf(stderr, "\nBase cluster id is set to an INVALID value\n");
         fprintf(stderr,
                 "Use -b option to set value or modify the MultiProcCfg file\n"
                );
         exit(EXIT_FAILURE);
    }
    if ((_MultiProc_cfg.baseIdOfCluster + _MultiProc_cfg.numProcsInCluster) >
        _MultiProc_cfg.numProcessors) {
        fprintf(stderr,
                "\nNumber of processors (%d) must be >= base cluster id + "
                "number of processors in cluster (%d + %d)\n",
                _MultiProc_cfg.numProcessors, _MultiProc_cfg.baseIdOfCluster,
                _MultiProc_cfg.numProcsInCluster);
        exit(EXIT_FAILURE);
    }


#if DAEMON
    /* fork off a child process */
    pid = fork();

    /* if fork of child failed then exit immediately; no child created */
    if (pid < 0) {
        fprintf(stderr, "\nERROR: Failed to fork child process!");
        exit(EXIT_FAILURE);
    }

    /* if pid > 0 this is the parent; time to die ... */
    if (pid > 0) {
        printf("\nSpawned daemon: %s\n\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    /* child continues from here (pid == 0) ... */

    /* change file mode mask */
    umask(0);

    /* create new session ID for the child */
    sid = setsid();

    /* exit with failure code if failed to get session ID... */
    if (sid < 0) {
        fprintf(stderr, "\nERROR: Failed to acquire new session ID!");
        exit(EXIT_FAILURE);
    }

    /* disassociate from the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

#endif

    LOG0("\nInitializing LAD... ")

    /* TODO:L make sure LAD is not already running? */

    /* initialize client info arrays */
    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {
        clientConnected[i] = FALSE;
        responseFIFOFilePtr[i] = NULL;
    }

    /* if command FIFO exists from previous LAD session delete it now */
    unlink(commandFIFOFile);

    /* create command FIFO */
    statusIO = mkfifo(commandFIFOFile, 0777);
    if (statusIO != 0) {
        LOG2("\nERROR: unable to create %s, errno = %x\n", commandFIFOFile,
            errno)
        return(0);
    }

    /* set FIFO permissions to read/write */
    chmod(commandFIFOFile, 0666);

    /* Setup modules relevant for GateMP if necessary */
#if defined(GATEMP_SUPPORT)
    if (gatempEnabled) {
        /* Set up NameServer for resource manager process */
        status = NameServer_setup();
        if (status < 0) {
            LOG0("\nERROR: unable to setup NameServer\n")
            return(0);
        }

        status = GateHWSpinlock_start();
        if (status < 0) {
            LOG0("\nERROR: unable to start GateHWSpinlock\n");
            return(0);
        }

        /* Set up GateMP */
        status = GateMP_setup();
        if (status < 0) {
            LOG0("\nERROR: unable to setup GateMP\n")
            NameServer_destroy();
            return(0);
        }
    }
#endif

opencommandFIFO:

    /* now open file for FIFO - will block until writer arrives... */
    LOG1("\n    opening FIFO: %s\n", commandFIFOFile)
    commandFIFOFilePtr = fopen(commandFIFOFile, "r");
    if (commandFIFOFilePtr == NULL) {
        LOG0("\nERROR: unable to open command FIFO\n")
        unlink(commandFIFOFile);
#if defined(GATEMP_SUPPORT)
        if (gatempEnabled) {
            GateMP_destroy();
            NameServer_destroy();
        }
#endif
        return(0);
    }

    /* COMMAND PROCESSING LOOP */
    while (1) {
        LOG0("Retrieving command...\n")

        /* read the next command packet */
        n = fread(&cmd, LAD_COMMANDLENGTH, 1, commandFIFOFilePtr);

        /*
         * if last client closes FIFO then it must be closed and reopened ...
         */
        if (!n) {
            LOG1("   EOF detected on FIFO, closing FIFO: %s\n", commandFIFOFile)
            fclose(commandFIFOFilePtr);

            goto opencommandFIFO;
        }

        /* cleanup for any connected/started clients that have departed */
        cleanupDepartedClients();

        command = cmd.cmd;
        clientId = cmd.clientId;

        /* process individual commands */
        switch (command) {
          /*
           * Since cmd is a union of rcv and snd structs, don't write
           * any snd elements before all rcv elements have been referenced
           * (either saved in separate variables or passed to a function).
           *
           * cmd.cmd has already been saved in 'command'
           * cmd.clientId has already been saved in 'clientId'
           */
          case LAD_CONNECT:
            connectToLAD(cmd.args.connect.name, cmd.args.connect.pid,
                         cmd.args.connect.protocol, NULL);

            break;

          case LAD_DISCONNECT:
            disconnectFromLAD(clientId);

            break;

          case LAD_IPC_GETCONFIG:
            Ipc_getConfig(&rsp.ipcConfig);
            break;

          case LAD_NAMESERVER_SETUP:
            LOG0("LAD_NAMESERVER_SETUP: calling NameServer_setup()...\n")

            rsp.status = NameServer_setup();

            LOG1("    status = %d\n", rsp.status)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_DESTROY:
            LOG0("LAD_NAMESERVER_DESTROY: calling NameServer_destroy()...\n")

            rsp.status = NameServer_destroy();

            LOG1("    status = %d\n", rsp.status)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_PARAMS_INIT:
            LOG0("LAD_NAMESERVER_PARAMS_INIT: calling NameServer_Params_init()...\n")

            NameServer_Params_init(&rsp.params);

            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_CREATE:
            LOG1("LAD_NAMESERVER_CREATE: calling NameServer_create('%s')...\n", cmd.args.create.name)

            rsp.handle = NameServer_create(cmd.args.create.name,
                                               &cmd.args.create.params);

            LOG1("    handle = %p\n", rsp.handle)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_DELETE:
            LOG1("LAD_NAMESERVER_DELETE: calling NameServer_delete(%p)...\n",
                    cmd.args.nsdelete.handle)

            rsp.nsdelete.handle = cmd.args.nsdelete.handle;
            rsp.nsdelete.status = NameServer_delete(&rsp.nsdelete.handle);

            LOG1("    status = %d\n", rsp.nsdelete.status)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_ADD:
            LOG1("LAD_NAMESERVER_ADD: calling NameServer_add(%p, ", cmd.args.add.handle)
            LOG2("'%s', %p,", cmd.args.add.name, cmd.args.add.buf)
            LOG1(" 0x%x)...\n", cmd.args.add.len)

            rsp.entryPtr = NameServer_add(
                cmd.args.add.handle,
                cmd.args.add.name,
                cmd.args.add.buf,
                cmd.args.add.len);

            LOG1("    entryPtr = %p\n", rsp.entryPtr)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_GET:
            LOG2("LAD_NAMESERVER_GET: calling NameServer_get(%p, '%s'",
                    cmd.args.get.handle, cmd.args.get.name)
            LOG0(")...\n")

            if (cmd.args.get.procId[0] == (UInt16)-1) {
                procIdPtr = NULL;
            }
            else {
                procIdPtr = cmd.args.get.procId;
            }
            rsp.get.status = NameServer_get(
                cmd.args.get.handle,
                cmd.args.get.name,
                rsp.get.buf,
                &cmd.args.get.len,
                procIdPtr);
            rsp.get.len = cmd.args.get.len;

            LOG1("    value = 0x%x\n", rsp.get.len)
            LOG1("    status = %d\n", rsp.get.status)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_ADDUINT32:
            LOG3("LAD_NAMESERVER_ADDUINT32: calling NameServer_addUInt32"
                    "(%p, '%s', 0x%x)...\n", cmd.args.addUInt32.handle,
                    cmd.args.addUInt32.name, cmd.args.addUInt32.val)

            rsp.entryPtr = NameServer_addUInt32(
                cmd.args.addUInt32.handle,
                cmd.args.addUInt32.name,
                cmd.args.addUInt32.val);

            LOG1("    entryPtr = %p\n", rsp.entryPtr)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_GETUINT32:
            LOG2("LAD_NAMESERVER_GETUINT32: calling NameServer_getUInt32"
                    "(%p, '%s')...\n", cmd.args.getUInt32.handle,
                    cmd.args.getUInt32.name)

            if (cmd.args.getUInt32.procId[0] == (UInt16)-1) {
                procIdPtr = NULL;
            }
            else {
                procIdPtr = cmd.args.getUInt32.procId;
            }
            rsp.getUInt32.status = NameServer_getUInt32(
                cmd.args.getUInt32.handle,
                cmd.args.getUInt32.name,
                &rsp.getUInt32.val,
                procIdPtr);

            LOG1("    value = 0x%x\n", rsp.getUInt32.val)
            LOG1("    status = %d\n", rsp.getUInt32.status)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_GETLOCAL:
            rsp.get.status = NameServer_getLocal(cmd.args.getLocal.handle,
                cmd.args.getLocal.name, &rsp.get.buf, &cmd.args.getLocal.len);
            rsp.get.len = cmd.args.getLocal.len;
            break;

          case LAD_NAMESERVER_GETLOCALUINT32:
            rsp.getUInt32.status = NameServer_getLocalUInt32(
                cmd.args.getLocalUInt32.handle,
                cmd.args.getLocalUInt32.name,
                &rsp.getUInt32.val);
            break;

          case LAD_NAMESERVER_REMOVE:
            LOG2("LAD_NAMESERVER_REMOVE: calling NameServer_remove(%p, '%s')...\n", cmd.args.remove.handle, cmd.args.remove.name)

            rsp.status = NameServer_remove(cmd.args.remove.handle,
                                               cmd.args.remove.name);

            LOG1("    status = %d\n", rsp.status)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_REMOVEENTRY:
            LOG2("LAD_NAMESERVER_REMOVEENTRY: calling NameServer_removeEntry(%p, %p)...\n", cmd.args.removeEntry.handle, cmd.args.removeEntry.entryPtr)

            rsp.status = NameServer_removeEntry(
                cmd.args.removeEntry.handle,
                cmd.args.removeEntry.entryPtr);

            LOG1("    status = %d\n", rsp.status)
            LOG0("DONE\n")

            break;

          case LAD_NAMESERVER_ATTACH:
            rsp.status = NameServer_attach(cmd.args.attach.procId);
            break;

          case LAD_NAMESERVER_DETACH:
            rsp.status = NameServer_detach(cmd.args.detach.procId);
            break;

          case LAD_MESSAGEQ_GETCONFIG:
            LOG0("LAD_MESSAGEQ_GETCONFIG: calling MessageQ_getConfig()...\n")

            MessageQ_getConfig(&rsp.messageQGetConfig.cfg);
            rsp.messageQGetConfig.status = 0;

            LOG1("    status = %d\n", rsp.messageQGetConfig.status)
            LOG0("DONE\n")

            break;

          case LAD_MESSAGEQ_SETUP:
            LOG0("LAD_MESSAGEQ_SETUP: calling MessageQ_setup()...\n")

            rsp.setup.status = MessageQ_setup(&cmd.args.messageQSetup.cfg);
            rsp.setup.nameServerHandle = MessageQ_getNameServerHandle();

            LOG1("    status = %d\n", rsp.setup.status)
            LOG0("DONE\n")

            break;

          case LAD_MESSAGEQ_DESTROY:
            LOG0("LAD_MESSAGEQ_DESTROY: calling MessageQ_destroy()...\n")

            rsp.status = MessageQ_destroy();

            LOG1("    status = %d\n", rsp.status)
            LOG0("DONE\n")

            break;

          case LAD_MESSAGEQ_CREATE:
            LOG2("LAD_MESSAGEQ_CREATE: calling MessageQ_create(%p, %p)...\n",
                    cmd.args.messageQCreate.name,
                    &cmd.args.messageQCreate.params);

            tmpString = (cmd.args.messageQCreate.name[0] == '\0') ? NULL :
                cmd.args.messageQCreate.name;

            handle = MessageQ_create(tmpString, &cmd.args.messageQCreate.params);
            rsp.messageQCreate.serverHandle = handle;

            if (handle) {
                rsp.messageQCreate.queueId = MessageQ_getQueueId(handle);
                MessageQ_setQueueOwner(handle, clientPID[clientId]);
                rsp.messageQCreate.status = 0;
            }
            else {
                rsp.messageQCreate.status = -1;
            }

            LOG1("    status = %d\n", rsp.messageQCreate.status)
            LOG0("DONE\n")

            break;

          case LAD_MESSAGEQ_ANNOUNCE:
            LOG2("LAD_MESSAGEQ_ANNOUNCE: calling MessageQ_announce(%p, %p)...\n",
                    cmd.args.messageQAnnounce.name,
                    cmd.args.messageQAnnounce.serverHandle);

            tmpString = (cmd.args.messageQAnnounce.name[0] == '\0') ? NULL :
                cmd.args.messageQAnnounce.name;

            rsp.messageQAnnounce.status =
                MessageQ_announce(tmpString, (MessageQ_Handle *)&cmd.args.messageQAnnounce.serverHandle);

            LOG1("    status = %d\n", rsp.messageQAnnounce.status)
            LOG0("DONE\n")

            break;
          case LAD_MESSAGEQ_DELETE:
            LOG1("LAD_MESSAGEQ_DELETE: calling MessageQ_delete(%p)...\n", cmd.args.messageQDelete.serverHandle)

            rsp.messageQDelete.status =
                MessageQ_delete((MessageQ_Handle *)&cmd.args.messageQDelete.serverHandle);

            LOG1("    status = %d\n", rsp.messageQDelete.status)
            LOG0("DONE\n")

            break;

          case LAD_MESSAGEQ_MSGINIT:
            LOG1("LAD_MESSAGEQ_MSGINIT: calling MessageQ_msgInit(%p)...\n", &rsp.msgInit.msg);

            MessageQ_msgInit(&rsp.msgInit.msg);
            rsp.msgInit.status = 0;

            LOG1("    status = %d\n", rsp.msgInit.status)
            LOG0("DONE\n")

            break;

          case LAD_MULTIPROC_GETCONFIG:
            LOG0("LAD_MULTIPROC_GETCONFIG: calling MultiProc_getConfig()...\n")

            MultiProc_getConfig(&rsp.multiprocGetConfig.cfg);
            rsp.multiprocGetConfig.status = 0;

            LOG1("    status = %d\n", rsp.multiprocGetConfig.status)
            LOG0("DONE\n")

            break;

#if defined(GATEMP_SUPPORT)
          case LAD_GATEMP_ATTACH:
            procId = cmd.args.attach.procId;
            LOG1("LAD_GATEMP_ATTACH: calling GateMP_attach(%d)...\n", procId)

            rsp.status = GateMP_attach(procId);

            LOG1("    status = %d\n", rsp.status)
            LOG0("DONE\n")

            break;

          case LAD_GATEMP_DETACH:
            procId = cmd.args.detach.procId;
            LOG1("LAD_GATEMP_DETACH: calling GateMP_detach(%d)...\n", procId)

            rsp.status = GateMP_detach(procId);

            LOG1("    status = %d\n", rsp.status)
            LOG0("DONE\n")

            break;

          case LAD_GATEMP_START:
            LOG0("LAD_GATEMP_START: calling GateMP_start()...\n")

            rsp.gateMPStart.nameServerHandle = GateMP_getNameServer();
            rsp.gateMPStart.status = GateMP_S_SUCCESS;

            LOG1("    status = %d\n", rsp.gateMPStart.status)
            LOG0("DONE\n")

            break;

          case LAD_GATEMP_GETNUMRESOURCES:
            LOG0("LAD_GATEMP_GETNUMRESOURCES: calling GateMP_getNumResources()...\n")

            rsp.gateMPGetNumResources.value = GateMP_getNumResources(
                                          cmd.args.gateMPGetNumResources.type);
            rsp.gateMPGetNumResources.status = GateMP_S_SUCCESS;;

            LOG1("    status = %d\n", rsp.gateMPGetNumResources.status)
            LOG0("DONE\n")

            break;

          case LAD_GATEMP_GETFREERESOURCE:
            LOG0("LAD_GATEMP_GETFREERESOURCE: calling GateMP_getFreeResource()...\n")

            rsp.gateMPGetFreeResource.id = GateMP_getFreeResource(
                                          cmd.args.gateMPGetFreeResource.type);
            rsp.gateMPGetFreeResource.status = GateMP_S_SUCCESS;;

            LOG1("    status = %d\n", rsp.gateMPGetFreeResource.status)
            LOG0("DONE\n")

            break;

          case LAD_GATEMP_RELEASERESOURCE:
            LOG0("LAD_GATEMP_RELEASERESOURCE: calling GateMP_releaseResource()...\n")

            rsp.gateMPReleaseResource.status = GateMP_releaseResource(
                                          cmd.args.gateMPReleaseResource.id,
                                          cmd.args.gateMPReleaseResource.type);

            LOG1("    status = %d\n", rsp.gateMPReleaseResource.status)
            LOG0("DONE\n")

            break;

          case LAD_GATEMP_ISSETUP:
            LOG0("LAD_GATEMP_ISSETUP: calling GateMP_isSetup()...\n")

            rsp.gateMPIsSetup.result = GateMP_isSetup();
            rsp.gateMPIsSetup.status = GateMP_S_SUCCESS;

            LOG1("    status = %d\n", rsp.gateMPIsSetup.status)
            LOG0("DONE\n")

            break;

          case LAD_GATEHWSPINLOCK_GETCONFIG:
            LOG0("LAD_GATEHWSPINLOCK_GETCONFIG: calling GateHWSpinlock_getConfig()...\n")

            GateHWSpinlock_getConfig(&rsp.gateHWSpinlockGetConfig.cfgParams);
            rsp.gateHWSpinlockGetConfig.status = 0;

            LOG1("    status = %d\n", rsp.gateHWSpinlockGetConfig.status)
            LOG0("DONE\n")

            break;
#endif

          case LAD_EXIT:
            goto exitNow;

            break;

          default:
            LOG1("\nUnrecognized command: 0x%x\n", command)

            break;
        }

        switch (command) {
          case LAD_CONNECT:
          case LAD_DISCONNECT:
            break;

          case LAD_IPC_GETCONFIG:
          case LAD_NAMESERVER_SETUP:
          case LAD_NAMESERVER_DESTROY:
          case LAD_NAMESERVER_PARAMS_INIT:
          case LAD_NAMESERVER_CREATE:
          case LAD_NAMESERVER_DELETE:
          case LAD_NAMESERVER_ADD:
          case LAD_NAMESERVER_GET:
          case LAD_NAMESERVER_ADDUINT32:
          case LAD_NAMESERVER_GETUINT32:
          case LAD_NAMESERVER_GETLOCAL:
          case LAD_NAMESERVER_GETLOCALUINT32:
          case LAD_NAMESERVER_REMOVE:
          case LAD_NAMESERVER_REMOVEENTRY:
          case LAD_NAMESERVER_ATTACH:
          case LAD_NAMESERVER_DETACH:
          case LAD_MESSAGEQ_GETCONFIG:
          case LAD_MESSAGEQ_SETUP:
          case LAD_MESSAGEQ_DESTROY:
          case LAD_MESSAGEQ_CREATE:
          case LAD_MESSAGEQ_ANNOUNCE:
          case LAD_MESSAGEQ_DELETE:
          case LAD_MESSAGEQ_MSGINIT:
          case LAD_MULTIPROC_GETCONFIG:
#if defined(GATEMP_SUPPORT)
          case LAD_GATEMP_ATTACH:
          case LAD_GATEMP_DETACH:
          case LAD_GATEMP_START:
          case LAD_GATEMP_GETNUMRESOURCES:
          case LAD_GATEMP_GETFREERESOURCE:
          case LAD_GATEMP_RELEASERESOURCE:
          case LAD_GATEMP_ISSETUP:
          case LAD_GATEHWSPINLOCK_GETCONFIG:
#endif

            LOG0("Sending response...\n");

            fwrite(&rsp, LAD_RESPONSELENGTH, 1, responseFIFOFilePtr[clientId]);
            fflush(responseFIFOFilePtr[clientId]);

            break;

          default:
            break;
        }
    }

exitNow:
#if defined(GATEMP_SUPPORT)
    if (gatempEnabled) {
        GateMP_destroy();
        NameServer_destroy();
    }
#endif
    if (logFile) {
        LOG0("\n\nLAD IS SELF TERMINATING...\n\n")
        fclose(logPtr);
    }
    unlink(commandFIFOFile);

    return(0);

}


/*
 *  ======== isDaemonRunning ========
 */
static Bool isDaemonRunning(Char *pidName)
{
    DIR *dir;
    pid_t pid;
    Int dirNum;
    FILE *fp;
    struct dirent * next;
    Bool isRunning = FALSE;
    Char filename [READ_BUF_SIZE];
    Char buffer [READ_BUF_SIZE];
    Char *bptr = buffer;
    Char *name;

    pid = getpid();
    dir = opendir("/proc");
    if (!dir) {
        printf("Warning: Cannot open /proc filesystem\n");
        return isRunning;
    }

    name = strrchr(pidName, '/');
    if (name) {
        pidName = (name + 1);
    }

    while ((next = readdir(dir)) != NULL) {
        /* If it isn't a number, we don't want it */
        if (!isdigit(*next->d_name)) {
            continue;
        }

        dirNum = strtol(next->d_name, NULL, 10);
        if (dirNum == pid) {
            continue;
        }

        snprintf(filename, READ_BUF_SIZE, "/proc/%s/cmdline", next->d_name);
        if (!(fp = fopen(filename, "r"))) {
            continue;
        }
        if (fgets(buffer, READ_BUF_SIZE, fp) == NULL) {
            fclose(fp);
            continue;
        }
        fclose (fp);

        name = strrchr(buffer, '/');
        if (name && (name + 1)) {
            bptr = name + 1;
        }
        else {
            bptr = buffer;
        }

        /* Buffer should contain the entire command line */
        if (strcmp(bptr, pidName) == 0) {
            isRunning = TRUE;
            break;
        }
    }
    closedir (dir);

    return isRunning;
}

/*
 *  ======== assignClientId ========
 */
static LAD_ClientHandle assignClientId(Void)
{
    Int clientId = -1;
    Int i;

    /* scan connection status flags to acquire a clientId */
    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {
        /* if slot open then provisionally select this clientId */
        if (clientConnected[i] == FALSE) {
             clientId = i;
             break;
        }
    }

    return(clientId);
}

/*
 *  ======== cleanupFifos ========
 */
static void cleanupFifos(Void)
{
    DIR *dir;
    struct dirent entry;
    struct dirent *result;
    size_t dirnamelen;
    size_t maxcopy;
    Char pathname[PATH_MAX];
    Char *namep;

    if ((dir = opendir(LAD_WORKINGDIR)) == NULL)
        return;

    dirnamelen = snprintf(pathname, sizeof(pathname), "%s/", LAD_WORKINGDIR);
    if (dirnamelen >= sizeof(pathname)) {
        closedir(dir);
        return;
    }
    namep = pathname + dirnamelen;
    maxcopy = PATH_MAX - dirnamelen;
    while (readdir_r(dir, &entry, &result) == 0 && result != NULL) {
        /* Delete old FIFOs left over */
        if ((entry.d_type == DT_FIFO) && (strlen(entry.d_name) < maxcopy)) {
            strncpy(namep, entry.d_name, maxcopy);
            unlink(pathname);
        }
    }
    closedir(dir);
}

/*
 *  ======== cleanupDepartedClients ========
 */
static Void cleanupDepartedClients(Void)
{
    Int killStat;
    Int i;

    /* scan all connections to verify client processes still exist... */
    for (i = 0; i < LAD_MAXNUMCLIENTS; i++) {

        /* if connected... */
        if (clientConnected[i] == TRUE) {

            /* check if the client process (PID) still exists */
            /*
             * NOTE - calling kill with signal value of 0 will perform
             * error checking, but not actually send a signal.  Will use this
             * error check to see if PID still exists.  An alternative was
             * to call getpgid.  This worked, but is apparently limited to
             * USE_XOPEN_EXTENDED configurations.
             */
            killStat = kill(clientPID[i], 0);
            if ((killStat == -1) && (errno == ESRCH)) {

                LOG1("\nDETECTED CONNECTED CLIENT #%d HAS DEPARTED!", i)

                /* will always need to do the disconnect... */
                LOG0("\nDoing DISCONNECT on behalf of client...")
                doDisconnect(i);

                MessageQ_cleanupOwner(clientPID[i]);
//                NameServer_cleanupOwner(clientPID[i]);

                LOG0("DONE\n")
            }
        }
    }
}


/*
 *  ======== connectToLAD ========
 */
static Int connectToLAD(String clientName, Int pid, String clientProto, Int *clientIdPtr)
{
    Int clientId = -1;
    Bool connectDenied = FALSE;
    Int status = LAD_SUCCESS;
    FILE * filePtr;
    Int statusIO;

    /*
     * TODO:L here, and everywhere parse FIFO strings: should
     * add full error checking for incomplete or corrupted
     * strings? Since LAD to ladclient comms are "closed", and
     * tested, the likelihood of problems seems very low.
     * But should still consider doing full error checking
     * and, hopefully, recovery.
     */
    LOG0("\nLAD_CONNECT: \n")
    LOG1("    client FIFO name = %s\n", clientName)
    LOG1("    client PID = %d\n", pid)

    /* first check for proper communication protocol */
    if (strcmp(clientProto, LAD_PROTOCOLVERSION) != 0) {

        /* if no match then reject the request */
        LOG0("    ERROR: mismatch in communication protocol!\n")
        LOG1("        LAD protocol = %s\n", LAD_PROTOCOLVERSION)
        LOG1("        client protocol = %s\n", clientProto)
        status = LAD_INVALIDVERSION;

        /* set flag so know to close FIFO after response */
        connectDenied = TRUE;

        /* now jump forward a bit to send response */
        goto openResponseFIFO;
    }

    /* determine this client's ID */
    clientId = assignClientId();

    /* if failed to acquire an ID then exit early */
    if (clientId == -1) {
        LOG0("    no free handle; too many connections!\n")
        status = LAD_ACCESSDENIED;

        /* set flag so know to close FIFO after response */
        connectDenied = TRUE;
    }
    else {
        LOG1("    assigned client handle = %d\n", clientId)

        /* save the client's FIFO name for when disconnect */
        strcpy(clientFIFOName[clientId], clientName);
    }

openResponseFIFO:

    /* create the dedicated response FIFO to the client */
    statusIO = mkfifo(clientName, 0777);
    if (statusIO != 0) {

        LOG2("\nERROR: unable to mkfifo %s, errno = %x\n", clientName, errno)

        status = LAD_IOFAILURE;

        /* send no response; connection request will timeout */
        goto doneconnect;
    }

    LOG1("    FIFO %s created\n", clientName)

    /* set FIFO permissions to read/write */
    chmod(clientName, 0666);

    filePtr = fopen(clientName, "w");
    if (filePtr == NULL) {
        LOG1("\nERROR: unable to open response FIFO %s\n", clientName)

        /* if failed open, still need to delete the FIFO */
        unlink(clientName);

        status = LAD_IOFAILURE;

        /* send no response; connection request will timeout */
        goto doneconnect;
    }

    LOG1("    FIFO %s opened for writing\n", clientName)

    /*
     * set "this client is connected" flag; this client ID is now "owned", and
     * is no longer provisional
     */
    if (connectDenied == FALSE) {
        responseFIFOFilePtr[clientId] = filePtr;
        clientPID[clientId] = pid;
        clientConnected[clientId] = TRUE;
    }

    rsp.connect.assignedId = clientId;
    rsp.status = status;

    /* put response to FIFO */
    fwrite(&rsp, LAD_RESPONSELENGTH, 1, filePtr);
    fflush(filePtr);

    LOG0("    sent response\n")

    /* if connection was denied, must now close FIFO */
    if (connectDenied == TRUE) {
        LOG1("    connect denied; closing FIFO %s\n", clientName)
        fclose(filePtr);
        unlink(clientName);
    }

    LOG0("DONE\n")

doneconnect:
    if (clientIdPtr != NULL) {
        *clientIdPtr = clientId;
    }

    return(status);
}


/*
 *  ======== disconnectFromLAD ========
 */
static Void disconnectFromLAD(Int clientId)
{
    LOG0("\nLAD_DISCONNECT: ")

    LOG1("\n    client handle = %x", clientId)
    doDisconnect(clientId);

    LOG0("DONE\n")

    return;
}


/*
 *  ======== doDisconnect ========
 */
static Void doDisconnect(Int clientId)
{
    /* set "this client is not connected" flag */
    clientConnected[clientId] = FALSE;

    /* close and remove the response FIFO */
    LOG2("\n    closing FIFO %s (filePtr=%p)\n",
        clientFIFOName[clientId], responseFIFOFilePtr[clientId])
    fclose(responseFIFOFilePtr[clientId]);

    LOG1("    done, unlinking %s\n", clientFIFOName[clientId]);
    unlink(clientFIFOName[clientId]);
}
