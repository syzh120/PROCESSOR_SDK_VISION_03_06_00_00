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
 * ======== pppoe.h ========
 *
 * Basic PPPoE definitions
 *
 */


/*----------------------------------------------- */
/* PPPOE Protocol Header */

#define PPPOEHDR_SIZE   6

typedef struct {
                UINT8   VerType;
                UINT8   Code;
#define PPPOE_CODE_INITIATION   0x9
#define PPPOE_CODE_OFFER        0x7
#define PPPOE_CODE_REQUEST      0x19
#define PPPOE_CODE_CONFIRM      0x65
#define PPPOE_CODE_TERMINATE    0xa7
                UINT16  SessionId;
                UINT16  Length;
                UINT8   Data[1];
#define PPPOE_TAG_EOL           0
#define PPPOE_TAG_SNAME         0x0101
#define PPPOE_TAG_ACNAME        0x0102
#define PPPOE_TAG_HOSTUNIQUE    0x0103
#define PPPOE_TAG_ACCOOKIE      0x0104
#define PPPOE_TAG_SNAMEERROR    0x0201
#define PPPOE_TAG_ACNAMEERROR   0x0202
#define PPPOE_TAG_ERROR         0x0203
               } PPPOEHDR;


/*----------------------------------------------- */
/* Shared Functions */
extern void pppoeSI( HANDLE hSI, uint Msg, UINT32 Aux, PBM_Pkt *pPkt );

/*----------------------------------------------- */
/* PPPOE Object Structures */
/*----------------------------------------------- */

/*----------------------------------------------- */
/* Max count for service list and max name length */
#define PPPOE_NAMESIZE          32

/* Generic Instance */
typedef struct _pppoe_instance {
    HANDLE       hParent;                       /* Parent structure */
    uint         Status;                        /* Call status */
    uint         iType;                         /* Instance TYPE */
#define PPPOE_INST_SERVER       1
#define PPPOE_INST_CLIENT       2
    HANDLE       hEther;                        /* Host Ethernet */
    UINT16       SessionId;                     /* Session Index */
    HANDLE       hPPP;                          /* PPP Interface */
    UINT8        MacAddr[6];                    /* Our MAC address */
    UINT8        PeerMac[6];                    /* Client's MAC address */
    } PPPOE_INST;

/* Server */
typedef struct _pppoe_server {
    uint         Type;                          /* Set to HTYPE_PPPOE_SERVER */
    HANDLE       hTimer;                        /* Session Timer */
    HANDLE       hEther;                        /* Ether Interface */
    uint         pppFlags;                      /* PPP Flags */
    uint         SessionMax;                    /* Max active sessions */
    IPN          IPClientBase;                  /* New client base IP address */
    IPN          IPServer;                      /* Our IP address */
    IPN          IPMask;                        /* Our IP mask */
    UINT8        MacAddr[6];                    /* Our MAC address */
    INT8         ServerName[PPPOE_NAMESIZE];    /* Our Server's Name */
    INT8         ServiceName[PPPOE_NAMESIZE];   /* Name of service provided */
    PPPOE_INST   ppi[1];                        /* Array of instances */
    } PPPOE_SERVER;

/* Client */
typedef struct _pppoe_client {
    uint         Type;                          /* Set to HTYPE_PPPOE_SERVER */
    HANDLE       hTimer;                        /* Session Timer */
    uint         pppFlags;                      /* PPP Flags */
    INT8         Username[PPPOE_NAMESIZE];      /* Specified Username */
    INT8         Password[PPPOE_NAMESIZE];      /* Specifies Password */
    PPPOE_INST   ppi;                           /* Our instance */
    int          State;                         /* Current state */
    int          Timeout;                       /* Timeout for this state */
    int          Retry;                         /* Retry count for timeout */
    INT8         ServerName[PPPOE_NAMESIZE];    /* Obtained from server */
    INT8         ServiceName[PPPOE_NAMESIZE];   /* Obtained from server */
    uint         CookieSize;                    /* Obtained from server */
    UINT8        Cookie[PPPOE_NAMESIZE];        /* Obtained from server */
    } PPPOE_CLIENT;
