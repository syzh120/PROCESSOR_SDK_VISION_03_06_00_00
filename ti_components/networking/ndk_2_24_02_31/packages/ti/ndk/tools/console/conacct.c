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
 * ======== conacct.c ========
 *
 * Basic console functions
 *  ConCmdAcct  -   Account Command
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "console.h"

static void   AcctDump();
static HANDLE AcctFind( char *User );
static char *AcctErr = "\nError in command line. Type 'acct' for help\n";

/*------------------------------------------------------------------------- */
/* ConCmdAcct() */
/* Function to print, add, and remove accounts */
/*------------------------------------------------------------------------- */
void ConCmdAcct( int ntok, char *tok1, char *tok2, char *tok3, char *tok4 )
{
    CI_ACCT CA;
    HANDLE  hAcct;
    char    c;
    int     rc;

    /* Check for 'acct print' */
    if( ntok == 1 && !stricmp( tok1, "print" ) )
        AcctDump();
    /* Check for 'acct add name pswd 1234' */
    else if( ntok == 4 && !stricmp( tok1, "add" ) )
    {
        if( strlen( tok2 ) >= CFG_ACCTSTR_MAX ||
            strlen( tok3 ) >= CFG_ACCTSTR_MAX )
        {
            ConPrintf("Name or password too long, %d character max\n\n",
                      CFG_ACCTSTR_MAX-1);
            return;
        }

        hAcct = AcctFind( tok2 );
        if( hAcct )
        {
            ConPrintf("Account exits - remove old account first\n\n");
            CfgEntryDeRef( hAcct );
            return;
        }

        strcpy( CA.Username, tok2 );
        strcpy( CA.Password, tok3 );

        CA.Flags = 0;
        while( (c = *tok4++) )
        {
            if( c < '1' || c > '4' )
            {
                ConPrintf("Permissions must use chars '1' to '4'\n\n");
                return;
            }
            c -= '1';
            CA.Flags |= CFG_ACCTFLG_CH1<<c;
        }

        /* Add it to the configuration */
        rc = CfgAddEntry( 0, CFGTAG_ACCT, CFGITEM_ACCT_SYSTEM,
                          CFG_ADDMODE_NOSAVE, sizeof(CI_ACCT),
                          (UINT8 *)&CA, 0 );
        if( rc < 0 )
            ConPrintf("Error adding account\n\n");
        else
            ConPrintf("Account added\n\n");
    }
    /* Check for 'acct delete name' */
    else if( ntok == 2 && !stricmp( tok1, "delete" ) )
    {
        hAcct = AcctFind( tok2 );
        if( !hAcct )
            ConPrintf("Account not found\n\n");
        else
        {
            CfgRemoveEntry( 0, hAcct );
            ConPrintf("Account removed\n\n");
        }
    }
    else if( ntok == 0 )
    {
        ConPrintf("\n[Acct Command]\n");
        ConPrintf("\nCalled to print, add, or delete PPP/EFS user accounts.\n\n");
        ConPrintf("acct print              - List all accounts\n");
        ConPrintf("acct add user pswd 1234 - Create account with channel permisions\n");
        ConPrintf("acct delete user        - Delete gateway route\n\n");
    }
    else
        ConPrintf(AcctErr);
}


static void AcctDump()
{
    CI_ACCT CA;
    uint    index,i;
    int     rc;

    index = 1;
    ConPrintf("\nUsername          Password          Channels (Realms)\n");
    ConPrintf("----------------  ----------------  -----------------\n");
    while(1)
    {
        rc = CfgGetImmediate( 0, CFGTAG_ACCT, CFGITEM_ACCT_SYSTEM,
                              index, sizeof(CA), (UINT8 *)&CA );
        if( !rc )
            break;
        ConPrintf("%-16s  %-16s  ",CA.Username,CA.Password);
        for( i=0; i<4; i++ )
            if( CA.Flags & (CFG_ACCTFLG_CH1<<i) )
                ConPrintf("R%d ",i+1);
        ConPrintf("\n");
        index++;
    }
    ConPrintf("\n");
}

static HANDLE AcctFind( char *User )
{
    HANDLE  hAcct;
    CI_ACCT CA;
    int     rc;
    int     size;

    rc = CfgGetEntry( 0, CFGTAG_ACCT, CFGITEM_ACCT_SYSTEM, 1, &hAcct );
    if( rc <= 0 )
        return(0);

    while(1)
    {
        size = sizeof(CA);
        rc = CfgEntryGetData( hAcct, &size, (UINT8 *)&CA );
        if( rc <= 0 )
        {
            CfgEntryDeRef( hAcct );
            return(0);
        }

        if( !strcmp( User, CA.Username ) )
            return( hAcct );

        rc = CfgGetNextEntry( 0, hAcct, &hAcct );
        if( rc <= 0 )
            return(0);
    }
}

