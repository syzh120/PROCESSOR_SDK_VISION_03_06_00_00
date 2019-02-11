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
 * ======== config.h ========
 *
 * Configuration Manager Private Defines
 *
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#include <netmain.h>
#include <_oskern.h>

/*--------------------------------------------------------------------------- */
/* Private Declarations */

/* Private Config Entry Structure */
typedef struct _cfgentry {
        uint               Type;        /* Handle Type (HTYPE_CFGENTRY) */
        uint               RefCount;    /* Reference Count */
        struct _cfgentry   *pNext;      /* Pointer to next in the chain */
        uint               Active;      /* Entry is active */
        uint               NoSave;      /* Entry is not saved */
        HANDLE             hCfg;        /* Handle to configuration */
        uint               Tag;         /* Configuration Tag */
        uint               Item;        /* Configuration Item */
        int                DataSize;    /* User data size */
        UINT8              UserData[1]; /* User data */
        } CFGENTRY;

/* Private Config Structure */
typedef struct _cfgmain {
        uint    Type;                       /* Handle Type (HTYPE_CFG) */
        uint    Active;                     /* Active config flag */
        HANDLE  hOwner;                     /* Owning task when locked */
        HANDLE  hSem;                       /* Onwer's Semaphore */
        uint    OwnCnt;                     /* Owner's count */
        uint    OpenOrder[CFGTAG_MAX];      /* List of Open Order for Tags */
        uint    CloseOrder[CFGTAG_MAX];     /* List of Close Order for Tags */
        /* List of entry chains by tag */
        struct _cfgentry *pCfgEntry[CFGTAG_MAX];
        /* List of service providers */
        int (*pCbService[CFGTAG_MAX]) (HANDLE,uint,uint,uint,HANDLE);
        } CFGMAIN;

/* Saved Config Entry Structure (simplified for space) */
typedef struct _cfgentrysave {
        uint               Record;      /* Record number */
        uint               RecordSize;  /* Total Record Size */
        uint               Tag;         /* Configuration Tag */
        uint               Item;        /* Configuration Item */
        int                DataSize;    /* User data size */
        UINT8              UserData[1]; /* User data */
        } CFGENTRYSAVE;

#endif

