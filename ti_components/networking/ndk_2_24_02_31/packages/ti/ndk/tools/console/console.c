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
 * ======== console.c ========
 *
 * Example router console
 *
 */

#include <netmain.h>
#include <_stack.h>
#include <_oskern.h>
#include "console.h"

extern char *VerStr;

static void console( HANDLE hCon, PSA pClient );
static char *StrBusy  = "\nConsole is busy\n\n";
static char *StrError = "\nCould not spawn console\n\n";
static char Password[32] = {0};

/*------------------------------------------------------------------------- */
/* Console IO */
/* The following routines form a basic standard IO for console functions */
/*------------------------------------------------------------------------- */
#define         INMAX  32
static char     InBuf[INMAX];
static int      InIdx = 0;
static int      InCnt = 0;
static SOCKET   scon  = INVALID_SOCKET;
static HANDLE   hConsole = 0;

/* PPPOE Function is only available when working with a stack build that */
/* includes PPPOE */
#ifdef _INCLUDE_PPPOE_CODE
static void     ConCmdPPPOE( int ntok, char *tok1, char *tok2, char *tok3 );
static HANDLE   hPPPOE   = 0;

static void ConCmdPPPOEServer( int ntok, char *tok1, char *tok2, char *tok3, char* tok4 ); 
static HANDLE   hPPPOEServer =0 ;
#endif

/*-------------------------------------------------------------- */
/* ConPrintf() */
/* Formatted print to console output */
/*-------------------------------------------------------------- */
int ConPrintf(const char *format, ...)
{
   va_list ap;
   char    buffer[128];
   int     size;

   va_start(ap, format);
   size = NDK_vsprintf(buffer, (char *)format, ap);
   va_end(ap);

   send( scon, buffer, size, 0 );
   return( size );
}

/*-------------------------------------------------------------- */
/* ConPrintIPN */
/* Quick routine to print out an IPN addr */
/*-------------------------------------------------------------- */
void ConPrintIPN( IPN IPAddr )
{
    IPAddr = htonl( IPAddr );
    ConPrintf( "%d.%d.%d.%d",
               (UINT8)((IPAddr>>24)&0xFF), (UINT8)((IPAddr>>16)&0xFF),
               (UINT8)((IPAddr>>8)&0xFF), (UINT8)(IPAddr&0xFF) );
}

/*-------------------------------------------------------------- */
/* ConGetCh() */
/* Read a character from console input */
/*-------------------------------------------------------------- */
char ConGetCh()
{
    char   c;
    struct timeval timeout;

    /* Configure our console timeout to be 5 minutes */
    timeout.tv_sec  = 5 * 60;
    timeout.tv_usec = 0;

    while( 1 )
    {
        while( !InCnt )
        {
            fd_set ibits;
            int    cnt;

            FD_ZERO(&ibits);
            FD_SET(scon, &ibits);

            /* Wait for io */
            cnt = fdSelect( (int)scon, &ibits, 0, 0, &timeout );
            if( cnt <= 0 )
                goto abort_console;

            /* Check for input data */
            if( FD_ISSET(scon, &ibits) )
            {
                /* We have characters to input */
                cnt = (int)recv( scon, InBuf, INMAX, 0 );
                if( cnt > 0 )
                {
                    InIdx = 0;
                    InCnt = cnt;
                }
                /* If the socket was closed or error, major abort */
                if( !cnt || (cnt<0 && fdError()!=EWOULDBLOCK) )
                    goto abort_console;
            }
        }

        InCnt--;
        c = InBuf[InIdx++];

        if( c != '\n' )
            return( c );
    }

abort_console:
    ConsoleClose();

    fdClose( scon );
    TaskExit();

    return(0);
}

/*-------------------------------------------------------------- */
/* ConGetString() */
/* Read a string from console input (with various echo options) */
/*-------------------------------------------------------------- */
int ConGetString( char *buf, int max, int echo )
{
    int idx=0, eat=0;
    char c;

    while( idx < (max-1) )
    {
        c = ConGetCh();

        /* Eat char if we're eating */
        if( eat )
        {
            if( eat == 27 && c == 79 )
                eat = 1;
            else
                eat = 0;
            continue;
        }

        /* Start eating if this is an extended char */
        if( !c )
        {
            eat = 255;
            continue;
        }

        /* Start eating if this is an escape code */
        if( c == 27 )
        {
            eat = 27;
            continue;
        }

        /* Back up on backspace */
        if( c == 8 )
        {
            if( idx )
            {
                idx--;
                ConPrintf("%c %c",8,8);
            }
            continue;
        }

        /* Return on CR */
        if( c == '\r' )
            break;

        buf[idx++] = c;
        if( echo == CGSECHO_INPUT )
           ConPrintf("%c",c);
        else if( echo == CGSECHO_PASSWORD )
           ConPrintf("*");
    }

    buf[idx] = 0;
    return( idx );
}

/*-------------------------------------------------------------- */
/* ConGetIP() */
/* Prompt for and read an IP adress from console input */
/*-------------------------------------------------------------- */
IPN ConGetIP()
{
    int    haveit = 0;
    char   c,str[32];
    IPN    IPTmp;

    while( !haveit )
    {
        ConPrintf("Enter IP as x.x.x.x : ");
        ConGetString( str, 20, CGSECHO_INPUT );
        IPTmp = inet_addr( str );
        ConPrintf("\nYou Entered ");
        ConPrintIPN( IPTmp );
        ConPrintf("\nIs this correct (y/n)\n");

        do { c=ConGetCh(); }
            while( c != 'y' && c !='Y' && c != 'N' && c != 'n' );

        if( c=='Y' || c=='y' )
            haveit = 1;
    }
    return( IPTmp );
}

/*--------------------------------------------------------------------- */
/* ConsoleOpen() */
/* Launch a console connection to the speicified client */
/* Returns local socket, or INVALID_SOCKET on error */
/*--------------------------------------------------------------------- */
SOCKET ConsoleOpen( PSA pClient )
{
    HANDLE fd1, fd2;

    // Create the local pipe - abort on error
    if( pipe( &fd1, &fd2 ) != 0 )
        return( INVALID_SOCKET );

    /* If an instance is already running, abort */
    if( hConsole )
    {
        /* If the console is already running, return a quick message and */
        /* close the pipe. */
        send( fd2, StrBusy, strlen(StrBusy), 0 );
        fdClose( fd2 );
    }
    else
    {
        /* Create the console thread */
        hConsole = TaskCreate( console, "Console", OS_TASKPRINORM, 0x1000,
                               (UINT32)fd2, (UINT32)pClient, 0 );

        /* Close the pipe and abort on an error */
        if( !hConsole )
        {
            send( fd2, StrError, strlen(StrError), 0 );
            fdClose( fd2 );
        }
    }

    /* Return the local fd */
    return( fd1 );
}

/*--------------------------------------------------------------------- */
/* ConsoleClose() */
/* Close the console task when active */
/*--------------------------------------------------------------------- */
void ConsoleClose()
{
    HANDLE hTmp;

    if( hConsole )
    {
        hTmp = hConsole;
        hConsole = 0;

#ifdef _INCLUDE_PPPOE_CODE
        /* If PPPOE is running, kill it */
        if( hPPPOE )
        {
            pppoeFree( hPPPOE );
            hPPPOE = 0;
        }
#endif

        /* Close the console socket session. This will cause */
        /* the console app thread to terminate with socket */
        /* error. */
        fdCloseSession( hTmp );
    }
}

/*--------------------------------------------------------------------- */
/* console() */
/* This is the main console task. */
/* Arg1 = IP Addr, Arg2 = UDP Foreign Port */
/*--------------------------------------------------------------------- */
static void console( SOCKET sCon, PSA pClient )
{
    uint   tmp;
    char   tstr[80];
    char   *tok[10];
    int    i,logon=0;

    fdOpenSession( TaskSelf() );

    /* Get our socket */
    scon = sCon;

#ifndef _INCLUDE_IPv6_CODE
    /* New console connection */
    {
        PSA_IN pClient_in = (PSA_IN)pClient;
        
        ConPrintf( VerStr );
        ConPrintf("Welcome connection : ");
        ConPrintIPN( pClient_in->sin_addr.s_addr );
        ConPrintf(":%d\n", htons( pClient_in->sin_port ) );
    }
#else
    {        
        PSA_IN6 pClient_in = (PSA_IN6)pClient;

        /* Print the banner */
        ConPrintf( VerStr );
        ConPrintf("Welcome connection : ");

        /* Check if the peer is V4 or V6? */
        if (pClient_in->sin6_family == AF_INET)
        {            
            PSA_IN pClient4_in = (PSA_IN)pClient;

            /* Print the V4 Peer Information. */
            ConPrintIPN( pClient4_in->sin_addr.s_addr );
            ConPrintf(":%d\n", htons( pClient4_in->sin_port ) );
        }
        else
        {
            char    strIPAddress[40];
            IP6N    clientIPAddress;

            /* Get the pointer to the V6 socket information and convert the V6 address to 
             * a printable format. */
            memcpy ((void *)&clientIPAddress, (void *)&pClient_in->sin6_addr, sizeof(IP6N));
            IPv6IPAddressToString (clientIPAddress, &strIPAddress[0]);

            /* Display the client information. */
            ConPrintf("%s:%d\n", strIPAddress, htons(pClient_in->sin6_port));
        }
    }
#endif /* _INCLUDE_IPv6_CODE */

    /* Just for fun, ask for a password */
    for( tmp=0; tmp<3; tmp++ )
    {
        if( !strlen(Password) )
            break;
        ConPrintf("\nPassword: ");
        ConGetString( tstr, 32, CGSECHO_PASSWORD );
        if( !strcmp(tstr, Password) )
            break;
        ConPrintf("\nInvalid login\n");
    }
    if( tmp >= 3 )
        logon = 0;
    else
    {
        ConPrintf("\n\nWelcome to the console program.\n");
        ConPrintf("Enter '?' or 'help' for a list of commands.\n\n");
        logon = 1;
    }

    /* Start the console command loop */
    while( logon )
    {
        /* Get a command string */
        ConPrintf(">");
        ConGetString( tstr, 80, CGSECHO_INPUT );
        ConPrintf("\n");

        /* Break the string down into tokens */
        tmp = 0;
        i = 0;
        tok[0] = tstr;
        while( tstr[i] && tmp < 10 )
        {
            if( tstr[i] == ' ' )
            {
                tstr[i] = 0;
                if( ++tmp < 10 )
                    tok[tmp] = tstr+i+1;
            }
            i++;
        }
        /* We terminated due to a NULL, then we have one more token */
        if( tmp < 10 )
            tmp++;

        /* Process the command */
        if( i )
        {
            if( *tok[0] == '?' || !stricmp( tok[0], "help" ) )
            {
                ConPrintf( VerStr );
                ConPrintf("\n[Help Command]\n\nThe basic commands are:\n");
                ConPrintf("  acct     - Manage PPP user accounts\n");
                ConPrintf("  bye      - Logoff the console\n");
                ConPrintf("  echo     - Perform echo test\n");
                ConPrintf("  help     - Displays this message\n");
                ConPrintf("  mem      - Display memory status\n");
                ConPrintf("  nslookup - Lookup hostname or IP address\n");
#ifdef _INCLUDE_PPPOE_CODE
                ConPrintf("  pppoe      - Invoke PPPOE client logon\n");
                ConPrintf("  pppoeserver- Start the PPPoE Server\n");
#endif
                ConPrintf("  pswd     - Change console password\n");
                ConPrintf("  ping     - Test echo request\n");
                ConPrintf("  quit     - Logoff the console\n");
                ConPrintf("  reboot   - Reboot system (terminates session)\n");
                ConPrintf("  route    - Maintain route table\n");
                ConPrintf("  shutdown - Shutdown stack (terminates session)\n");
                ConPrintf("  socket   - Print socket table\n");
                ConPrintf("  stat     - Print internal stack statistics\n");
                ConPrintf("  tftp     - Test TFTP file transfer\n");
                ConPrintf("  lli      - Test Static LLI (ARP) Configuration\n");
                ConPrintf("  vlan     - Add/Delete VLAN devices\n");
                ConPrintf("  ipaddr   - Configuration of IPAddress\n");
#ifdef _INCLUDE_IPv6_CODE
                ConPrintf("  ipv6     - IPv6 Configuration.\n");
                ConPrintf("  ping6    - Test echo request over IPv6\n");
                ConPrintf("  v6nslookup - Lookup hostname or IPv6 address\n");
#endif
                ConPrintf("\nSome commands have additional help information. For example\n");
                ConPrintf("entering 'route' gives more information on the route command.\n\n");
            }
            else if( !stricmp( tok[0], "bye" ) || !stricmp( tok[0], "quit" ) )
                logon = 0;
            else if( !stricmp( tok[0], "route" ) )
                ConCmdRoute( tmp-1, tok[1], tok[2], tok[3], tok[4] );
            else if( !stricmp( tok[0], "acct" ) )
                ConCmdAcct( tmp-1, tok[1], tok[2], tok[3], tok[4] );
            else if( !stricmp( tok[0], "stat" ) )
                ConCmdStat( tmp-1, tok[1] );
            else if( !stricmp( tok[0], "nslookup" ) )
                ConCmdLookup( tmp-1, tok[1] );
#ifdef _INCLUDE_IPv6_CODE
            else if( !stricmp( tok[0], "v6nslookup" ) )
                ConCmdLookupIPv6( tmp-1, tok[1] );
#endif
            else if( !stricmp( tok[0], "ping" ) )
                ConCmdPing( tmp-1, tok[1], tok[2] );
            else if( !stricmp( tok[0], "echo" ) )
                ConCmdEcho( tmp-1, tok[1], tok[2] );
            else if( !stricmp( tok[0], "socket" ) )
                ConCmdSocket( tmp-1, tok[1] );
            else if( !stricmp( tok[0], "tftp" ) )
                ConCmdTFTP( tmp-1, tok[1], tok[2] );
            else if( !stricmp( tok[0], "lli" ) )
                ConCmdLLI ( tmp-1, tok[1], tok[2], tok[3] );
            else if( !stricmp( tok[0], "test" ) )
                ConCmdTest( tmp-1, tok[1], tok[2] );
#ifdef _INCLUDE_PPPOE_CODE
            else if( !stricmp( tok[0], "pppoe" ) )
                ConCmdPPPOE( tmp-1, tok[1], tok[2], tok[3] );
            else if( !stricmp( tok[0], "pppoeserver" ) )
                ConCmdPPPOEServer( tmp-1, tok[1], tok[2], tok[3], tok[4] );
#endif
            else if( !stricmp( tok[0], "vlan" ) )
                ConCmdVLAN( tmp-1, tok[1], tok[2], tok[3], tok[4] );
            else if( !stricmp( tok[0], "ipaddr" ) )
                ConCmdIPAddr ( tmp-1, tok[1], tok[2], tok[3], tok[4] );
#ifdef _INCLUDE_IPv6_CODE
            else if( !stricmp( tok[0], "ipv6" ) )
                ConCmdIPv6 ( tmp-1, tok[1], tok[2], tok[3], tok[4], tok[5], tok[6], tok[7] );
            else if( !stricmp( tok[0], "ping6" ) )
                ConCmdPing6( tmp-1, tok[1], tok[2] );            
#endif
            else if( !stricmp( tok[0], "reboot" ) )
                NC_NetStop(1);
            else if( !stricmp( tok[0], "shutdown" ) )
                NC_NetStop(0);
            else if( !stricmp( tok[0], "mem" ) )
                _mmCheck( MMCHECK_MAP, &ConPrintf );
            else if( !stricmp( tok[0], "pswd" ) )
            {
                if( tmp<2 || strlen(tok[1]) > 31 )
                    ConPrintf("Usage: pswd newpassword\n\n");
                else
                {
                    strcpy(Password,tok[1]);
                    ConPrintf("Console password is now '%s'\n\n",Password);
                }
            }
            else
                ConPrintf("Invalid command - Enter '?' or 'help' for a list of commands.\n");
        }
    }

    /* Close the console */
    ConPrintf("\nGoodbye\n");

    /* Close console thread */
    ConsoleClose();

    fdClose( scon );
    TaskExit();
}

/*--------------------------------------------------------------------- */
/* PPPOE Client Command */
/*--------------------------------------------------------------------- */
#ifdef _INCLUDE_PPPOE_CODE
static void     ConCmdPPPOE( int ntok, char *tok1, char *tok2, char *tok3 );
static char *callerr[] = { "Dropped", "LCP Failed", "Authorization Failed",
                           "IP Config Failed" };
static void ConCmdPPPOE( int ntok, char *tok1, char *tok2, char *tok3 )
{
    uint tmp;

    /* Check for 'acct 1 userid password' */
    if( ntok == 3 )
    {
        tmp = *tok1 - '0';
        if( tmp<1 || tmp>9 )
            goto ERROR;

        {
            NIMU_IF_REQ ifreq;
            HANDLE      hIf;

            /* Initialize the NIMU Interface Object. */
            mmZeroInit (&ifreq, sizeof(NIMU_IF_REQ));

            /*
             *  We are interested in receiving the handle associated with
             *  'index' Item
             */
            ifreq.index = tmp;
            if (NIMUIoctl(NIMU_GET_DEVICE_HANDLE, &ifreq, (void *)&hIf,
                    sizeof(HANDLE)) < 0)
                return;

            /* Initiate the call. */
            hPPPOE = pppoeNew(hIf, PPPFLG_CLIENT | PPPFLG_OPT_USE_MSE, tok2,
                    tok3 );
        }

        if( !hPPPOE )
            ConPrintf("PPPOE Open failed\n");
        else while(1)
        {
            /* Get status of call */
            tmp = pppoeGetStatus( hPPPOE );

            /* If disconnected, print message and close */
            if( tmp >= SI_CSTATUS_DISCONNECT )
            {
                ConPrintf("Disconnected - '%s'\n", callerr[tmp-SI_CSTATUS_DISCONNECT]);
                goto DISCONNECT;
            }

            /* If connected, print message and break */
            if( tmp == SI_CSTATUS_CONNECTED )
            {
                ConPrintf("Connected\n");
                break;
            }

            /* Else wait half a second and try again */
            TaskSleep( 500 );
        }
    }
    /* Check for 'close' */
    else if( ntok == 1 && !stricmp( tok1, "close" ) )
    {
        if( !hPPPOE )
            ConPrintf("\nPPPOE not connected\n\n");
        else
        {
DISCONNECT:
            pppoeFree( hPPPOE );
            hPPPOE = 0;
            ConPrintf("\nPPPOE closed\n\n");
        }
    }
    else if( ntok == 0 )
    {
        ConPrintf("\n[PPPOE Command]\n");
        ConPrintf("\nCalled to invoke a PPPOE client session.\n\n");
        ConPrintf("pppoe 1 userid password - Connect on Ethernet If-1\n");
        ConPrintf("pppoe close             - Close PPPOE session\n\n");
    }
    else
    {
ERROR:
        ConPrintf("\nError in command. Type 'PPPOE' for usage.\n\n");
    }
}

static void ConCmdPPPOEServer( int ntok, char *tok1, char *tok2, char *tok3, char* tok4 )
{
    uint tmp;
    IPN  ServerIP;
    IPN  ServerIPMask;
    IPN  ClientBase;

    /* Check for '<InterfaceHandle> <IPServer> <ServerMask> <ClientBase>' */
    if( ntok == 4 )
    {
        tmp = *tok1 - '0';
        if( tmp<1 || tmp>9 )
            goto ERROR;

        if( hPPPOEServer )
        {
            ConPrintf("\nPPPoE Server already running\n\n");
            return;
        }

        if( !ConStrToIPN( tok2, &ServerIP ) )
        {
            ConPrintf("\nInvalid Server IP Specified\n\n");
            return;            
        }

        if( !ConStrToIPN( tok3, &ServerIPMask ) )
        {
            ConPrintf("\nInvalid Server IP Mask Specified\n\n");
            return;            
        }

        if( !ConStrToIPN( tok4, &ClientBase ) )
        {
            ConPrintf("\nInvalid Client Base Specified\n\n");
            return;            
        }       

        {
            NIMU_IF_REQ ifreq;
            HANDLE      hIf;

            /* Initialize the NIMU Interface Object. */
            mmZeroInit (&ifreq, sizeof(NIMU_IF_REQ));

            /*
             *  We are interested in receiving the handle associated with
             *  'index' Item
             */
            ifreq.index = tmp;
            ifreq.index = tmp;
            if (NIMUIoctl(NIMU_GET_DEVICE_HANDLE, &ifreq, (void *)&hIf,
                    sizeof(HANDLE)) < 0)
                return;

            /* Start the PPPoE Server: We currently support at max 5 clients. */
            hPPPOEServer = pppoesNew(hIf, PPPFLG_SERVER | PPPFLG_OPT_USE_MSE, 5,
                    ServerIP, ServerIPMask, ClientBase, "NDKPPPoEServer",
                    "NDKPPPService");
        }

        if( !hPPPOEServer )
            ConPrintf("\nError: Unable to start the PPPoE Server\n\n");
        else
            ConPrintf("\nPPPoE Server has been started successfully\n\n");
    }
    /* Check for 'close' */
    else if( ntok == 1 && !stricmp( tok1, "close" ) )
    {
        if( !hPPPOEServer )
            ConPrintf("\nPPPOE Server not running\n\n");
        else
        {
            pppoesFree( hPPPOEServer );
            hPPPOEServer = 0;
            ConPrintf("\nPPPOE Server closed\n\n");
        }
    }
    else if( ntok == 0 )
    {
        ConPrintf("\n[PPPOEServer Command]\n");
        ConPrintf("\nCalled to start a PPPoE Server\n\n");
        ConPrintf("pppoeserver 1 ServerIP ServerIPMask ClientBase - Start the PPPoE Server on Interface Handle 1\n");
        ConPrintf("pppoeserver close                              - Close PPPOE Server\n\n");
    }
    else
    {
ERROR:
        ConPrintf("\nError in command. Type 'PPPOE' for usage.\n\n");
    }
}


#endif
