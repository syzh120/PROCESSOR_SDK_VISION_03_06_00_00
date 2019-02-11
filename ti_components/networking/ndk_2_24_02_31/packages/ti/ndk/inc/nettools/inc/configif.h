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
 * ======== configif.h ========
 *
 * Configuration Manager Interface functions
 *
 */

#ifndef _CONFIGIF_H
#define _CONFIGIF_H

/*----------------------------------------------------------------------- */
/* Config API */
/*----------------------------------------------------------------------- */

/*----------------------------------------------------------------------- */
/* CfgNew() */
/* Create a new configuration */
/*----------------------------------------------------------------------- */
_extern HANDLE CfgNew();

/*----------------------------------------------------------------------- */
/* CfgFree( HANDLE hCfg ) */
/* Destroy a configuration */
/*----------------------------------------------------------------------- */
_extern void CfgFree( HANDLE hCfg );

/*----------------------------------------------------------------------- */
/* CfgSetDefault() */
/* Set the default configuration */
/*----------------------------------------------------------------------- */
_extern void CfgSetDefault( HANDLE hCfg );

/*----------------------------------------------------------------------- */
/* CfgGetDefault() */
/* Get the default configuration */
/*----------------------------------------------------------------------- */
_extern HANDLE CfgGetDefault();

/*----------------------------------------------------------------------- */
/* CfgLoad() */
/* Load a configuration from memory buffer */
/* Returns the number of bytes processed, or <0 on error */
/*----------------------------------------------------------------------- */
_extern int  CfgLoad( HANDLE hCfg, int Size, UINT8 *pData );

/*----------------------------------------------------------------------- */
/* CfgSave() */
/* Save configuration to a memory buffer */
/* *pSize is set to the size of the supplied buffer, or zero to get */
/* required size (the pointer pSize must be valid, but the value at */
/* the pointer can be zero). */
/* Returns the number of bytes written (0 on size check, <0 on error) */
/* *pSize is set to the number of bytes required. */
/*----------------------------------------------------------------------- */
_extern int  CfgSave( HANDLE hCfg, int *pSize, UINT8 *pData );

/*----------------------------------------------------------------------- */
/* CfgSetExecuteOrder() */
/* Establishes the order in which Tags are loaded and unloaded when */
/* the Execute status changes. */
/* When a configuration is first created, the order set in ascending */
/* Tag value order. */
/* The valute of Tags must be set to the EXACT number of tags in the */
/* configuration system. */
/* Returns 0 on success, or <0 on error */
/*----------------------------------------------------------------------- */
_extern int CfgSetExecuteOrder( HANDLE hCfg, uint Tags,
                        uint *pOpenOrder, uint *pCloseOrder );

/*----------------------------------------------------------------------- */
/* CfgExecute() */
/* Executes the configuration - loads all loadable entries */
/* When a configuration is first created, config changes do not */
/* alter the state of the system. Once the configuration is executed, */
/* all past settings take effect, and any new settings are immediately */
/* invoked. */
/* When fExecute is set to 0, all invoked entries are shutdown. */
/* Returns 0 on success, or <0 on error */
/*----------------------------------------------------------------------- */
_extern int  CfgExecute( HANDLE hCfg, uint fExecute );

/*----------------------------------------------------------------------- */
/* CfgSetService() */
/* Sets the service function for a particular config TAG. Service */
/* functions default to NULL, and when so, no service is performed. */
/* When invoked, the service callback function is passed back information */
/* about the affected entry. */
/*   int CbSrv( HANDLE hCfg, uint Tag, uint Item, uint Op, HANDLE hCfgEntry ) */
/*        hCfg      = HANDLE to Config */
/*        Tag       = Tag value of entry changed */
/*        Item      = Item value of entry changed */
/*        Op        = CFGCOP_ADD or CFGOP_REMOVE */
/*        hCfgEntry = Non-Ref'd HANDLE to entry added or removed */
/*    Returns 1 on success, 0 on "pass", and <0 on error. */
/* Note: The config entry handle passed to the callback is NOT Ref'd, */
/*       in that its scope expires when the callback function returns. */
/* Returns 0 on success, <0 on error. */
/*----------------------------------------------------------------------- */
_extern int  CfgSetService( HANDLE hCfg, uint Tag,
                           int (*pCb) (HANDLE, uint, uint, uint, HANDLE) );
#define CFGOP_REMOVE    0
#define CFGOP_ADD       1

/*----------------------------------------------------------------------- */
/* CfgAddEntry() */
/* Add a configuration entry to a configuration. */
/* When the pointer phCfgEntry is non-zero, this function write a */
/* referenced HANDLE to this location. */
/* When finished with a referenced entry HANDLE, an application must */
/* DeRef it by calling one of the following functions: */
/*   CfgEntryDeRef()          - Stop using the entry */
/*   CfgRemoveEntry()         - Stop using entry and remove it from cfg */
/*   CfgGetNextEntry()        - Stop using entry and get next entry */
/* Returns 1 on successful add and processing. */
/* Returns 0 on successful add with no processing. */
/* Returns <0 but > CFGERROR_SERVICE on configuration error */
/* Returns <= CFGERROR_SERVICE on successful add, but service error */
/*----------------------------------------------------------------------- */
_extern int  CfgAddEntry( HANDLE hCfg, uint Tag, uint Item, uint Mode,
                         int Size, UINT8 *pData, HANDLE *phCfgEntry );

/* Add Entry Flags */
#define CFG_ADDMODE_UNIQUE      0x0001  /* Replace all previous instances */
#define CFG_ADDMODE_DUPLICATE   0x0002  /* Allow duplicate data entry */
#define CFG_ADDMODE_NOSAVE      0x0004  /* Don't include this entry in CfgSave */

/*----------------------------------------------------------------------- */
/* CfgRemoveEntry() */
/* Performs a single DeRef on a configuration entry, and removes it from */
/* the configuration structure. */
/* Returns 0 on success, or <0 on error */
/*----------------------------------------------------------------------- */
_extern int  CfgRemoveEntry( HANDLE hCfg, HANDLE hCfgEntry );

/*----------------------------------------------------------------------- */
/* CfgGetEntryCnt() */
/* Returns the number of entries on a specific tag/item, or <0 on error */
/*----------------------------------------------------------------------- */
_extern int  CfgGetEntryCnt( HANDLE hCfg, uint Tag, uint Item );

/*----------------------------------------------------------------------- */
/* CfgGetEntry() */
/* Get a referenced HANDLE to a configuration entry */
/* Index is a relative value (the "n'th" 1-based entry in a list) */
/* DO NOT use the index value to enumerate entry entry in the list. */
/* The index is valid only at the time of the call as an item can */
/* move up and down in the list as config changes are made. To */
/* enumerate every entry for a Tag/Item pair, start with index 1 and */
/* then use GetNextEntry() to get additional entries. */
/* When finished with this entry, an application must deref it */
/* by calling one of the following functions: */
/*   CfgEntryDeRef()          - Stop using the entry */
/*   CfgRemoveEntry()         - Stop using entry and remove it from cfg */
/*   CfgGetNextEntry()        - Stop using entry and get next entry */
/* Function returns 1 on success, 0 on "not found", and <0 on error. */
/*----------------------------------------------------------------------- */
_extern int  CfgGetEntry( HANDLE hCfg, uint Tag, uint Item,
                         uint Index, HANDLE *phCfgEntry );

/*----------------------------------------------------------------------- */
/* CfgGetNextEntry() */
/* DeRef supplied entry HANDLE and get referenced HANDLE of */
/* next configuration entry in the enumerated list. */
/* When finished with this entry, an application must deref it */
/* by calling one of the following functions: */
/*   CfgEntryDeRef()          - Stop using the entry */
/*   CfgRemoveEntry()         - Stop using entry and remove it from cfg */
/*   CfgGetNextEntry()        - Stop using entry and get next entry */
/* Function returns 1 on success, 0 on "not found", and <0 on error. */
/*----------------------------------------------------------------------- */
_extern int  CfgGetNextEntry( HANDLE hCfg, HANDLE hCfgEntry,
                             HANDLE *phCfgEntryNext );

/*----------------------------------------------------------------------- */
/* CfgGetImmediate() */
/* This function is intened for when an entry is known to most likely */
/* exist and is of a fixed size. It looks-up the entry, copies the data, */
/* and de-refs the entry all in one call. */
/* Returns the number of bytes copied. */
/*----------------------------------------------------------------------- */
_extern int CfgGetImmediate( HANDLE hCfg, uint Tag, uint Item, uint Instance,
                            int MaxSize, UINT8 *pData );

/*----------------------------------------------------------------------- */
/* CfgEntryRef() */
/* Add a reference a configuration entry handle */
/* This function is called by an application when it intends to use an */
/* entry handle beyond the scope of the function which obtained it */
/* from the configuration. */
/* When finished with this entry, an application must deref it */
/* by calling one of the following functions: */
/*   CfgEntryDeRef()          - Stop using the entry */
/*   CfgRemoveEntry()         - Stop using entry and remove it from cfg */
/*   CfgGetNextEntry()        - Stop using entry and get next entry */
/* Returns 0 on success, <0 on error. */
/*----------------------------------------------------------------------- */
_extern int  CfgEntryRef( HANDLE hCfgEntry );

/*----------------------------------------------------------------------- */
/* CfgEntryDeRef(); */
/* Dereference a configuration entry handle */
/* Returns 0 on success, <0 on error. */
/*----------------------------------------------------------------------- */
_extern int  CfgEntryDeRef( HANDLE hCfgEntry );

/*----------------------------------------------------------------------- */
/* CfgEntryGetData() */
/* Get configuration entry user data */
/* the pointer can be zero). */
/* Returns the number of bytes written. If the supplied size is ZERO or */
/* too small, the function returns 0 and *pSize is set to the number of */
/* bytes required. Returns <0 on non-size related error. */
/*----------------------------------------------------------------------- */
_extern int  CfgEntryGetData( HANDLE hCfgEntry, int *pSize, UINT8 *pData );

/*----------------------------------------------------------------------- */
/* CfgEntrySetData() */
/* Set configuration entry user data */
/* Size is set to the size of item to replace. It must be an exact */
/* match for the current entry size. Also, no processing is done on */
/* the altered data. */
/* * USE WITH CARE * */
/* Returns the number of bytes written. If the supplied size doesn't */
/* match the old size, function returns 0. */
/* Returns <0 on non-size related error. */
/*----------------------------------------------------------------------- */
_extern int  CfgEntrySetData( HANDLE hCfgEntry, int Size, UINT8 *pData );

/*----------------------------------------------------------------------- */
/* CfgEntryInfo() */
/* Get configuration entry user data info */
/* Returns configuration size and data pointer. When either size or */
/* data information is not required, the pointer arguments can be NULL. */
/* Returns ZERO on successm or <0 on error */
/*----------------------------------------------------------------------- */
_extern int  CfgEntryInfo( HANDLE hCfgEntry, int *pSize, UINT8 **ppData );

/*----------------------------------------------------------------------- */
/* Config API Error Codes */
/*----------------------------------------------------------------------- */
#define CFGERROR_BADHANDLE      -1      /* Invalid Cfg handle */
#define CFGERROR_BADPARAM       -2      /* Invalid function parameter */
#define CFGERROR_RESOURCES      -3      /* Memory allocation error */
#define CFGERROR_REFERROR       -4      /* Reference count mismatch */
#define CFGERROR_ALREADY        -5      /* Already in desired state */
#define CFGERROR_SERVICE        -100    /* First service error */

#define CFG_MAKE_CFGERROR(x)     ((x)+CFGERROR_SERVICE)
#define CFG_GET_SERVICE_ERROR(x) ((x)-CFGERROR_SERVICE)
#define CFG_IS_SERVICE_ERROR(x)  ((x)<=CFGERROR_SERVICE)

#endif
