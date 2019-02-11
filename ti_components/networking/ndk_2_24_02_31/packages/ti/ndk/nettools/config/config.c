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
 * ======== config.c ========
 *
 * Configuration Object
 *
 */

#include "config.h"

static void      _CfgAcquire( CFGMAIN *pc );
static void      _CfgRelease( CFGMAIN *pc );
static CFGENTRY *_CfgEntryScan( CFGENTRY *pe, uint Tag, uint Item,
                                       int Size, UINT8 *pData );
static int       _CfgEntryProcess( CFGMAIN *pc, uint op, CFGENTRY *pe );

/* Default configuration */
static HANDLE    hCfgDefault = 0;

/*----------------------------------------------------------------------- */
/* _CfgAcquire( CFGMAIN *pc ) */
/* Get ownership of CFG */
/*----------------------------------------------------------------------- */
static void _CfgAcquire( CFGMAIN *pc )
{
    /* The Kernel thread can access config before and after a "session" */
    if( !TaskSelf() )
        return;

    /* If the task already has the semaphore, then bump the count */
    if( pc->hOwner == TaskSelf() )
        pc->OwnCnt++;
    /* Else wait for ownership */
    else
    {
        SemPend( pc->hSem, SEM_FOREVER );
        pc->OwnCnt = 1;
        pc->hOwner = TaskSelf();
    }
}

/*----------------------------------------------------------------------- */
/* _CfgRelease( CFGMAIN *pc ) */
/* Release ownership of CFG */
/*----------------------------------------------------------------------- */
static void _CfgRelease( CFGMAIN *pc )
{
    /* The Kernel thread can access config before and after a "session" */
    if( !TaskSelf() )
        return;

    /* Make sure this task owns the semaphore */
    if( pc->hOwner != TaskSelf() )
        return;

    /* Decrement the ownership count */
    pc->OwnCnt--;

    /* Signal the semaphore if we're done */
    if( !pc->OwnCnt )
    {
        pc->hOwner = 0;
        SemPost( pc->hSem );
    }
}

/*----------------------------------------------------------------------- */
/* CfgSetDefault() */
/* Set the default configuration */
/*----------------------------------------------------------------------- */
void CfgSetDefault( HANDLE hCfg )
{
    hCfgDefault = hCfg;
}

/*----------------------------------------------------------------------- */
/* CfgGetDefault() */
/* Get the default configuration */
/*----------------------------------------------------------------------- */
HANDLE CfgGetDefault()
{
    return( hCfgDefault );
}

/*----------------------------------------------------------------------- */
/* CfgNew() */
/* Create a new configuration */
/*----------------------------------------------------------------------- */
HANDLE CfgNew()
{
    CFGMAIN *pc;
    int     tmp;

    /* If alloc fails, return NULL */
    if( !(pc = mmAlloc(sizeof(CFGMAIN))) )
        return( 0 );

    /* Init all to NULL */
    mmZeroInit( pc, sizeof(CFGMAIN) );

    /* Create the locking semaphore */
    if( !(pc->hSem = SemCreate( 1 )) )
    {
        mmFree( pc );
        return( 0 );
    }

    /* Init Open/Close Order Arrays */
    for( tmp=0; tmp<CFGTAG_MAX; tmp++ )
    {
        pc->OpenOrder[tmp]  = tmp+1;
        pc->CloseOrder[tmp] = tmp+1;
    }

    /* Set the type for debug */
    pc->Type = HTYPE_CFG;

    return( (HANDLE)pc );
}

/*----------------------------------------------------------------------- */
/* CfgFree( HANDLE hCfg ) */
/* Destroy a configuration */
/*----------------------------------------------------------------------- */
void CfgFree( HANDLE hCfg )
{
    CFGMAIN *pc;
    int      i;

    pc = (CFGMAIN *)hCfg;

    if( !pc || pc->Type != HTYPE_CFG )
        return;

    /* First we need ownership of the CFG */
    _CfgAcquire( pc );

    /* If removing the default config, clear default */
    if( hCfg == hCfgDefault )
        hCfgDefault = 0;

    /* In order to free a configuration, we must first deactivate it */
    if( pc->Active )
        CfgExecute( hCfg, 0 );

    /* Now free all configuration entries */
    for( i=0; i<CFGTAG_MAX; i++ )
        while( pc->pCfgEntry[i] )
        {
            CfgEntryRef( pc->pCfgEntry[i] );
            CfgRemoveEntry( hCfg, pc->pCfgEntry[i] );
        }

    /* Now we can free the configuration itself */

    /* Clear the type */
    pc->Type = 0;

    /* Delete the semaphore */
    SemDelete( pc->hSem );

    /* Free the memory */
    mmFree( pc );
}

/*----------------------------------------------------------------------- */
/* CfgLoad() */
/* Load a configuration from memory buffer */
/* Returns the number of bytes processed, or <0 on error */
/*----------------------------------------------------------------------- */
int  CfgLoad( HANDLE hCfg, int Size, UINT8 *pData )
{
    CFGMAIN      *pc;
    CFGENTRYSAVE *pes;
    int          totalsize=0;
    uint         rec=0;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Size and pData must be valid */
    if( !Size || !pData )
        return( CFGERROR_BADPARAM );

    /* First we need ownership of the CFG */
    _CfgAcquire( pc );

    /* Enumerate all entries for size */
    while( Size > 0 )
    {
        /* Add Next Record */

        /* Get next record */
        pes = (CFGENTRYSAVE *)pData;

        /* If record doesn't match, return */
        if( pes->Record != ++rec )
            goto load_done;

        /* Add record */
        if( CfgAddEntry( hCfg, pes->Tag, pes->Item, CFG_ADDMODE_DUPLICATE,
                         pes->DataSize, pes->UserData, 0 ) < 0 )
            goto load_done;

        /* Track bytes */
        totalsize += pes->RecordSize;

        Size -= pes->RecordSize;

        /* Bump the read location */
        pData += pes->RecordSize;
    }

load_done:
    /* Release the CFG */
    _CfgRelease( pc );

    /* Report the number of bytes we processed */
    return( totalsize );
}

/*----------------------------------------------------------------------- */
/* CfgSave() */
/* Save configuration to a memory buffer */

/* *pSize is set to the size of the supplied buffer, or zero to get */
/* required size (the pointer pSize must be valid, but the value at */
/* the pointer can be zero). */

/* Returns the number of bytes written (0 on size check, <0 on error) */
/* *pSize is set to the number of bytes required. */
/*----------------------------------------------------------------------- */
int  CfgSave( HANDLE hCfg, int *pSize, UINT8 *pData )
{
    CFGMAIN      *pc;
    CFGENTRY     *pe;
    CFGENTRYSAVE *pes;
    int          i,rec=0,totalsize=0;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* pSize must be valid, if *pSize is not zero, pData must be valid */
    if( !pSize || (*pSize && !pData) )
        return( CFGERROR_BADPARAM );

    /* First we need ownership of the CFG */
    _CfgAcquire( pc );

    /* Enumerate all entries for size */
    for( i=0; i<CFGTAG_MAX; i++ )
    {
        pe = pc->pCfgEntry[i];

        while(pe)
        {
            /* New Record - Add in the size */
            if( !pe->NoSave )
                totalsize += ((sizeof(CFGENTRYSAVE)+pe->DataSize+3)>>2)<<2;
            pe = pe->pNext;
        }
    }

    /* If this is a size check, or there isn't enough space return */
    if( *pSize < totalsize )
    {
        /* Return the required size */
        *pSize = totalsize;

        /* Release the CFG */
        _CfgRelease( pc );

        /* Report we saved ZERO bytes */
        return(0);
    }

    /* Enumerate all entries for saving */
    for( i=0; i<CFGTAG_MAX; i++ )
    {
        pe = pc->pCfgEntry[i];
        while(pe)
        {
            /* New Record - Add it */
            if( !pe->NoSave )
            {
                /* Save to current data buffer */
                pes = (CFGENTRYSAVE *)pData;

                /* Copy all the fields */
                pes->Record     = ++rec;
                pes->RecordSize = ((sizeof(CFGENTRYSAVE)+pe->DataSize+3)>>2)<<2;
                pes->Tag        = pe->Tag;
                pes->Item       = pe->Item;
                pes->DataSize   = pe->DataSize;
                mmCopy( pes->UserData, pe->UserData, pe->DataSize );

                /* Bump the save location */
                pData += pes->RecordSize;
            }

            /* Go to next entry */
            pe = pe->pNext;
        }
    }

    /* Release the CFG */
    _CfgRelease( pc );

    /* Report the number of bytes we saved */
    return( totalsize );
}

/*----------------------------------------------------------------------- */
/* CfgSetExecuteOrder() */

/* Establishes the order in which Tags are loaded and unloaded when */
/* the Execute status changes. */

/* When a configuration is first created, the order set in ascending */
/* Tag value order. */

/* The value of Tags must be set to the EXACT number of tags in the */
/* configuration system. */

/* Returns 0 on success, or <0 on error */
/*----------------------------------------------------------------------- */
int CfgSetExecuteOrder( HANDLE hCfg, uint Tags,
                        uint *pOpenOrder, uint *pCloseOrder )
{
    CFGMAIN      *pc;
    int          tmp;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Do basic parameter validation */
    if( Tags!=CFGTAG_MAX || !pOpenOrder || !pCloseOrder )
        return( CFGERROR_BADPARAM );

    /* First we need ownership of the CFG */
    _CfgAcquire( pc );

    /* Copy the supplied order arrays to our local arrays */
    for( tmp=0; tmp<CFGTAG_MAX; tmp++ )
    {
        pc->OpenOrder[tmp]  = *pOpenOrder++;
        pc->CloseOrder[tmp] = *pCloseOrder++;
    }

    _CfgRelease( pc );

    return(0);
}


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
int  CfgExecute( HANDLE hCfg, uint fExecute )
{
    CFGMAIN      *pc;
    CFGENTRY     *pe;
    uint         *pOrder;
    int          returncode = 0;
    int          i,op;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* First we need ownership of the CFG */
    _CfgAcquire( pc );

    /* Set op according to execute, and abort trivial case */
    if( !fExecute )
    {
        if( !pc->Active )
        {
            returncode = CFGERROR_ALREADY;
            goto execute_done;
        }
        op = CFGOP_REMOVE;
        pOrder = pc->CloseOrder;
        pc->Active = 0;
    }
    else
    {
        if( pc->Active )
        {
            returncode = CFGERROR_ALREADY;
            goto execute_done;
        }
        op = CFGOP_ADD;
        pOrder = pc->OpenOrder;
        pc->Active = 1;
    }

    /* Now we need to enumerate every item and process it */
    for( i=0; i<CFGTAG_MAX; i++ )
    {
        uint Tag = *(pOrder+i);

        /* If Tag value is invalid, the Open/Close is implicitly */
        /* disabled */
        if( Tag>0 && Tag<=CFGTAG_MAX )
        {
            /* Start with the first entry for this tag */
            pe = (CFGENTRY *)pc->pCfgEntry[Tag-1];

            /* Process the entry */
            while( pe )
            {
                if( pe->Active != pc->Active )
                {
                    pe->Active = pc->Active;
                    _CfgEntryProcess( pc, op, pe );
                }
                pe = pe->pNext;
            }
        }
    }

execute_done:
    /* Release the CFG */
    _CfgRelease( pc );

    return( returncode );
}

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
int  CfgSetService( HANDLE hCfg, uint Tag,
                    int (*pCb) (HANDLE, uint, uint, uint, HANDLE) )
{
    CFGMAIN      *pc;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Do basic parameter validation */
    if( Tag < 1 || Tag > CFGTAG_MAX )
        return( CFGERROR_BADPARAM );

    /* Install the serive */
    pc->pCbService[Tag-1] = pCb;

    return(0);
}

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
int  CfgAddEntry( HANDLE hCfg, uint Tag, uint Item, uint Mode,
                  int Size, UINT8 *pData, HANDLE *phCfgEntry )
{
    CFGMAIN      *pc;
    CFGENTRY     *pe,*peTmp;
    int          EntrySize;
    int          returncode = 0;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Do basic parameter validation */
    if( Tag < 1 || Tag > CFGTAG_MAX )
        return( CFGERROR_BADPARAM );

    /* Now acquire ownership of the CFG */
    _CfgAcquire( pc );

    /* Count the number of current instances */
    returncode = CfgGetEntryCnt( hCfg, Tag, Item );
    if( returncode < 0 )
        goto add_done;

    /* If we want to replace all previous instances, unload any instances */
    /* we currently have */
    if( (Mode & CFG_ADDMODE_UNIQUE) && returncode > 0 )
    {
        while( CfgGetEntry( hCfg, Tag, Item, 1, (HANDLE *)&pe ) == 1 )
            CfgRemoveEntry( hCfg, (HANDLE)pe );
    }
    /* Else if we don't want to allow a duplicate, return if we have one */
    else if( !(Mode & CFG_ADDMODE_DUPLICATE) && returncode > 0 )
    {
        pe = _CfgEntryScan( pc->pCfgEntry[Tag-1], Tag, Item, Size, pData );
        if( pe )
        {
            returncode = 0;
            goto add_have_entry;
        }
    }

    /* Allocate the config entry structure */
    EntrySize = sizeof(CFGENTRY) + Size - 1;

    /* If alloc fails, return error */
    if( !(pe = mmAlloc( EntrySize )) )
    {
        returncode = CFGERROR_RESOURCES;
        goto add_done;
    }

    /* Init our entry fields to NULL */
    mmZeroInit( pe, sizeof(CFGENTRY)-1 );

    /* Initialize entry */
    pe->Type     = HTYPE_CFGENTRY;
    pe->RefCount = 1;
    pe->hCfg     = hCfg;
    pe->Tag      = Tag;
    pe->Item     = Item;
    pe->DataSize = Size;
    mmCopy( pe->UserData, pData, Size );

    /* Set the NoSave flag if needed */
    if( Mode & CFG_ADDMODE_NOSAVE )
        pe->NoSave = 1;

    /* Add it to the configuration */
    peTmp=pc->pCfgEntry[Tag-1];
    if( !peTmp )
        pc->pCfgEntry[Tag-1] = pe;
    else
    {
        while( peTmp->pNext )
            peTmp = peTmp->pNext;
        peTmp->pNext = pe;
    }

    /* If the configuration is active, we process the entry */
    pe->Active = pc->Active;
    if( pe->Active )
        returncode = _CfgEntryProcess( pc, CFGOP_ADD, pe );
    else
        returncode = 0;

add_have_entry:
    /* If the user wants the handle, reference it and return it */
    if( phCfgEntry )
    {
        CfgEntryRef( pe );
        *phCfgEntry = pe;
    }

add_done:
    /* Release the CFG */
    _CfgRelease( pc );

    return( returncode );
}

/*----------------------------------------------------------------------- */
/* CfgRemoveEntry() */

/* Performs a single DeRef on a configuration entry, and removes it from */
/* the configuration structure. */

/* Returns 0 on success, or <0 on error */
/*----------------------------------------------------------------------- */
int  CfgRemoveEntry( HANDLE hCfg, HANDLE hCfgEntry )
{
    CFGMAIN      *pc;
    CFGENTRY     *pe    = (CFGENTRY *)hCfgEntry;
    CFGENTRY     *peTmp;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Verify Entry Handle */
    if( !pe || pe->Type != HTYPE_CFGENTRY )
        return( CFGERROR_BADHANDLE );

    /* Make sure the Cfg/Entry pair is a match */
    /* Allow an "orphaned" entry to go through for deref */
    if( pe->hCfg && pe->hCfg != hCfg )
        return( CFGERROR_BADPARAM );

    /* Now acquire ownership of the CFG */
    _CfgAcquire( pc );

    /* Only remove the entry if its in this configuration */
    if( pe->hCfg )
    {
        /* Unlink the entry from the config */
        if( (peTmp = pc->pCfgEntry[pe->Tag-1]) != 0 )
        {
            if( peTmp == pe )
                pc->pCfgEntry[pe->Tag-1] = pe->pNext;
            else while( peTmp->pNext )
            {
                if( peTmp->pNext == pe )
                {
                    peTmp->pNext = pe->pNext;
                    break;
                }
                peTmp = peTmp->pNext;
            }
        }
        pe->pNext = 0;
        pe->hCfg  = 0;

        /* If the entry is active, we process the entry removal */
        if( pe->Active )
        {
            pe->Active = 0;
            _CfgEntryProcess( pc, CFGOP_REMOVE, pe );
        }

        /* DeRef the Entry on behalf of the configuration */
        CfgEntryDeRef( pe );
    }

    /* DeRef the Entry on behalf of the caller */
    CfgEntryDeRef( pe );

    /* Release the CFG */
    _CfgRelease( pc );

    return( 0 );
}

/*----------------------------------------------------------------------- */
/* CfgGetEntryCnt() */
/* Returns the number of entries on a specific tag/item, or <0 on error */
/*----------------------------------------------------------------------- */
int  CfgGetEntryCnt( HANDLE hCfg, uint Tag, uint Item )
{
    CFGMAIN      *pc;
    int          returncode = 0;
    int          cnt        = 0;
    HANDLE       hCfgEntry;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Now acquire ownership of the CFG */
    _CfgAcquire( pc );

    /* The user could enumerate using these functions as well. This is */
    /* the easiest way to do it. */
    returncode = CfgGetEntry( hCfg, Tag, Item, 1, &hCfgEntry );
    while( returncode == 1 )
    {
        cnt++;
        returncode = CfgGetNextEntry( hCfg, hCfgEntry, &hCfgEntry );
    }

    /* Release the CFG */
    _CfgRelease( pc );

    /* Return the entry count or error return */
    if( returncode >= 0 )
        return( cnt );
    else
        return( returncode );
}

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
int  CfgGetEntry( HANDLE hCfg, uint Tag, uint Item,
                               uint Index, HANDLE *phCfgEntry )
{
    CFGMAIN      *pc;
    CFGENTRY     *pe;
    int          returncode = 0;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Now acquire ownership of the CFG */
    _CfgAcquire( pc );

    /* Find the first entry. If no entries found, return */
    pe = _CfgEntryScan( pc->pCfgEntry[Tag-1], Tag, Item, 0, 0 );

    /* Now, count down the Index number and scan while Index not reached */
    while( pe && --Index )
        pe = _CfgEntryScan( pe->pNext, Tag, Item, 0, 0 );

    /* Here we either have the desired entry in "pe", or it is NULL */
    if( pe )
    {
        /* Tell the user we found it */
        returncode = 1;

        /* If the user wants the handle, reference it and return it */
        if( phCfgEntry )
        {
            CfgEntryRef( pe );
            *phCfgEntry = pe;
        }
    }

    /* Release the CFG */
    _CfgRelease( pc );

    return( returncode );
}

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
int  CfgGetNextEntry( HANDLE hCfg, HANDLE hCfgEntry, HANDLE *phCfgEntryNext )
{
    CFGMAIN      *pc;
    CFGENTRY     *pe    = (CFGENTRY *)hCfgEntry;
    int          returncode = 0;

    /* Assign and validate handle */
    if( !hCfg )
        hCfg = (HANDLE)hCfgDefault;
    pc = (CFGMAIN *)hCfg;
    if( !pc || pc->Type != HTYPE_CFG )
        return( CFGERROR_BADHANDLE );

    /* Verify Entry Handle */
    if( !pe || pe->Type != HTYPE_CFGENTRY )
        return( CFGERROR_BADHANDLE );

    /* Make sure the Cfg/Entry pair is a match */
    /* Allow an "orphaned" entry to go through for deref */
    if( pe->hCfg && pe->hCfg != hCfg )
        return( CFGERROR_BADPARAM );

    /* Now acquire ownership of the CFG */
    _CfgAcquire( pc );

    /* If the entry is not in a configuration, deref on behalf of */
    /* the caller, else get the next entry */
    if( !pe->hCfg )
        CfgEntryDeRef( pe );
    else
    {
        /* DeRef the Entry */
        CfgEntryDeRef( pe );

        /* Get the next entry (if any) */
        pe = _CfgEntryScan( pe->pNext, pe->Tag, pe->Item, 0, 0 );

        /* Here we either have the desired entry in "pe", or it is NULL */
        if( pe )
        {
            /* Tell the user we found it */
            returncode = 1;

            /* If the user wants the handle, reference it and return it */
            if( phCfgEntryNext )
            {
                CfgEntryRef( pe );
                *phCfgEntryNext = pe;
            }
        }
    }

    /* Release the CFG */
    _CfgRelease( pc );

    return( returncode );
}

/*----------------------------------------------------------------------- */
/* CfgGetImmediate() */

/* This function is intended for when an entry is known to most likely */
/* exist and is of a fixed size. It looks-up the entry, copies the data, */
/* and de-refs the entry all in one call. */

/* Returns the number of bytes copied. */
/*----------------------------------------------------------------------- */
int CfgGetImmediate( HANDLE hCfg, uint Tag, uint Item, uint Instance,
                     int MaxSize, UINT8 *pData )
{
    HANDLE hCfgEntry;
    int    rc,size;

    /* Get entry */
    rc = CfgGetEntry( hCfg, Tag, Item, Instance, &hCfgEntry );
    if( rc < 1 )
        return(0);

    /* Get data */
    size = MaxSize;
    rc = CfgEntryGetData( hCfgEntry, &size, pData );

    /* Deref entry */
    CfgEntryDeRef( hCfgEntry );

    /* Return results based on GetData results */
    if( rc < 1 )
        return(0);
    else
        return(rc);
}

/*----------------------------------------------------------------------- */
/* Config Entry Functions */
/*----------------------------------------------------------------------- */

/*----------------------------------------------------------------------- */
/* _CfgEntryScan() */
/* Scans a chain of configuration entries, looking for those that */
/* match the input parameters. A parameter of NULL is treated as */
/* a wildcard. */
/*----------------------------------------------------------------------- */
static CFGENTRY *_CfgEntryScan( CFGENTRY *pe, uint Tag, uint Item,
                                int Size, UINT8 *pData )
{
    int i;

    while( pe )
    {
        /* If all supplied parameters match, return this entry */
        if( Tag && Tag != pe->Tag )
            goto scan_failed;
        if( Item && Item != pe->Item )
            goto scan_failed;
        if( Size && Size != pe->DataSize )
            goto scan_failed;
        if( pData )
            for( i=0; i<pe->DataSize; i++ )
                if( *(pData+i) != pe->UserData[i] )
                    goto scan_failed;
        return( pe );

scan_failed:
        /* Here we failed to match, so move onto next entry */
        pe = pe->pNext;
    }
    return(0);
}

/*----------------------------------------------------------------------- */
/* _CfgEntryProcess() */
/* Called to process an ADD or REMOVE operation in the configuration */
/*----------------------------------------------------------------------- */
static int _CfgEntryProcess( CFGMAIN *pc, uint op, CFGENTRY *pe )
{
    int returncode;

    /* If there's no service provider, return */
    if( !pc->pCbService[pe->Tag-1] )
        return(0);

    /* Otherwise, call the service provider */
    returncode = pc->pCbService[pe->Tag-1]( pc, pe->Tag, pe->Item, op, pe );
    if( returncode < 0 )
        return( CFG_MAKE_CFGERROR(returncode) );
    else
        return( returncode );
}

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
int  CfgEntryRef( HANDLE hCfgEntry )
{
    CFGENTRY *pe        = (CFGENTRY *)hCfgEntry;

    /* Verify Handle */
    if( pe->Type != HTYPE_CFGENTRY )
        return( CFGERROR_BADHANDLE );

    /* Ref it */
    if( pe->RefCount != 65535 )
        pe->RefCount++;

    return(0);
}

/*----------------------------------------------------------------------- */
/* CfgEntryDeRef(); */

/* Dereference a configuration entry handle */

/* Returns 0 on success, <0 on error. */
/*----------------------------------------------------------------------- */
int  CfgEntryDeRef( HANDLE hCfgEntry )
{
    CFGENTRY *pe        = (CFGENTRY *)hCfgEntry;

    /* Verify Handle */
    if( pe->Type != HTYPE_CFGENTRY )
        return( CFGERROR_BADHANDLE );

    /* DeRef it */
    if( pe->RefCount > 1 )
        pe->RefCount--;
    else
    {
        /* It should be impossible for a completely DeRef'd entry */
        /* to still be in config, but since applications developers */
        /* sometimes make mistakes.... */
        if( pe->hCfg )
        {
            DbgPrintf( DBG_WARN, "CfgEntryDeRef: REFERROR");
            return( CFGERROR_REFERROR );
        }

        /* Otherwise; free entry */
        mmFree( pe );
    }
    return(0);
}

/*----------------------------------------------------------------------- */
/* CfgEntryGetData() */

/* Get configuration entry user data */

/* *pSize is set to the size of the supplied buffer, or zero to get */
/* required size (the pointer pSize must be valid, but the value at */
/* the pointer can be zero). */

/* Returns the number of bytes written. If the supplied size is ZERO or */
/* too small, the function returns 0 and *pSize is set to the number of */
/* bytes required. Returns <0 on non-size related error. */
/*----------------------------------------------------------------------- */
int  CfgEntryGetData( HANDLE hCfgEntry, int *pSize, UINT8 *pData )
{
    CFGENTRY *pe        = (CFGENTRY *)hCfgEntry;

    /* Verify Handle */
    if( pe->Type != HTYPE_CFGENTRY )
        return( CFGERROR_BADHANDLE );

    /* Verify size parameter */
    if( !pSize )
        return( CFGERROR_BADPARAM );

    /* If size is zero or too small, return the required size */
    if( *pSize < pe->DataSize )
    {
        *pSize = pe->DataSize;
        return( 0 );
    }

    /* Here, the user wants the data - verify pData */
    if( !pData )
        return( CFGERROR_BADPARAM );

    /* Copy the data */
    mmCopy( pData, pe->UserData, pe->DataSize );
    return( pe->DataSize );
}

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
int  CfgEntrySetData( HANDLE hCfgEntry, int Size, UINT8 *pData )
{
    CFGENTRY *pe        = (CFGENTRY *)hCfgEntry;

    /* Verify Handle */
    if( pe->Type != HTYPE_CFGENTRY )
        return( CFGERROR_BADHANDLE );

    /* Verify data parameter */
    if( !pData )
        return( CFGERROR_BADPARAM );

    /* If size different, return */
    if( Size != pe->DataSize )
        return( 0 );

    /* Copy the data */
    mmCopy( pe->UserData, pData, pe->DataSize );
    return( pe->DataSize );
}

/*----------------------------------------------------------------------- */
/* CfgEntryInfo() */

/* Get configuration entry user data info */

/* Returns configuration size and data pointer. When either size or */
/* data information is not required, the pointer arguments can be NULL. */

/* Returns ZERO on success or <0 on error */
/*----------------------------------------------------------------------- */
int  CfgEntryInfo( HANDLE hCfgEntry, int *pSize, UINT8 **ppData )
{
    CFGENTRY *pe        = (CFGENTRY *)hCfgEntry;

    /* Verify Handle */
    if( pe->Type != HTYPE_CFGENTRY )
        return( CFGERROR_BADHANDLE );

    /* Return data when pointers are valid */
    if (pSize || !ppData) {
        if (pSize) {
            *pSize  = pe->DataSize;
        }
    }
    if( ppData )
        *ppData = pe->UserData;

    return( 0 );
}
