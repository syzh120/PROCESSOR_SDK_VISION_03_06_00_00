/*
 * webpage.c
 */

/*
 * Copyright (C) 2007-2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/_stack.h>
#include <ti/ndk/inc/tools/cgiparse.h>
#include <ti/ndk/inc/tools/cgiparsem.h>
#include <ti/ndk/inc/tools/console.h>
#include "client.h"

#include "webdata/default.h"
#include "webdata/logobar.h"
#include "webdata/dspchip.h"
#include "webdata/sample.h"

static int cgiSample( SOCKET htmlSock, int ContentLength, char *pArgs );
static int cgiSampleMulti( SOCKET htmlSock, int ContentLength, char *pArgs );
static int cgiInform( SOCKET htmlSock, int ContentLength, char *pArgs );

// This int will be our "%R%" realm file, forcing any file located
// in the same direcotry to be authenticated on realm 1. The system
// supports realms 1 to 4.
//
// Note that we're only going to protect the "protected/" subdir,
// but its also possible to protect the entire web site by putting
// a %R% file in the root. Also, you can have the root protected
// on (say) realm 1, and a subdir on (say) realm 2, allowing for
// "users" (members of realm 1) and "superusers" (members of both
// realm 1 and realm 2).
//
static int OurRealm = 1;

void AddWebFiles(void)
{
    void *pFxn;

    efs_createfile("index.html", DEFAULT_SIZE, DEFAULT);
    efs_createfile("logobar.gif", LOGOBAR_SIZE, LOGOBAR);
    efs_createfile("dspchip.gif", DSPCHIP_SIZE, DSPCHIP);
    pFxn = (void*) &cgiInform;
    efs_createfile("inform.cgi", 0, (UINT8 *) pFxn);
    efs_createfile("protected/%R%", 4, (UINT8 *)&OurRealm );
    efs_createfile("protected/sample.htm", SAMPLE_SIZE, SAMPLE );
    pFxn = (void*) &cgiSample;
    efs_createfile("protected/sample.cgi", 0, (UINT8*) pFxn);
    pFxn = (void*) &cgiSampleMulti;
    efs_createfile("protected/sample_multi.cgi", 0, (UINT8*) pFxn);
}

void RemoveWebFiles(void)
{
    efs_destroyfile("index.html");
    efs_destroyfile("logobar.gif");
    efs_destroyfile("dspchip.gif");
    efs_destroyfile("inform.cgi");
    efs_destroyfile("protected/%R%");
    efs_destroyfile("protected/sample.htm");
    efs_destroyfile("protected/sample.cgi");
    efs_destroyfile("protected/sample_multi.cgi");
}

//
// Page Creation Commonly Used Data
//
static const char *pstr_HTML_START =
       "<html><body text=#000000 bgcolor=#ffffff>\r\n";
static const char *pstr_HTML_END =
       "</body></html>\r\n";
static const char *pstr_TI_START =
       "<center><p><image src=\"logobar.gif\"></p>\r\n";
static const char *pstr_TI_END =
       "</center></body></html>\r\n";
static const char *pstr_ROW_START =
       "<tr>";
static const char *pstr_ROW_END =
       "</tr>\r\n";
static const char *pstr_DIVIDER =
       "<hr WIDTH=\"100%\"><br>\r\n";
static const char *pstr_TABLE_START =
       "<table border cellspacing=0 cellpadding=5>\r\n";
static const char *pstr_TABLE_END =
       "</table><br>\r\n";
static const char *pstr_LINK_MAIN =
       "<a href=index.html>Return to Main Page</a><br><br>\r\n";
static const char *pstr_LINK_MAIN_SUBDIR =
       "<a href=../index.html>Return to Main Page</a><br><br>\r\n";


//
// Page Creation Macro
//
#define html(str) httpSendClientStr(htmlSock, (char *)str)


// We use the following format line in cgiSample()
static const char *tablefmt = "<tr><td>%s</td><td>%s</td></tr>\r\n";
static const char *tablefmtd = "<tr><td>%s</td><td>%d</td></tr>\r\n";

//
// Sample CGI Function
//
// This function processes the sample CGI from off the main
// WEB page on the HTTP server.
//
// CGI Functions must return 1 if the socket is left open,
// and zero if the socket is closed. This example always
// returns 1.
//
static int cgiSample(SOCKET htmlSock, int ContentLength, char *pArgs )
{
    char    *name = 0, *spam = 0, *pizza = 0, *color = 0;
    char    *buffer, *key, *value;
    int     len;
    int     parseIndex;
    char    htmlbuf[MAX_RESPONSE_SIZE];

    // CGI Functions can now support URI arguments as well if the
    // pArgs pointer is not NULL, and the ContentLength were zero,
    // we could parse the arguments off of pArgs instead.

    // First, allocate a buffer for the request
    buffer = (char*) mmBulkAlloc( ContentLength + 1 );
    if ( !buffer )
        goto ERROR;

    // Now read the data from the client
    len = recv( htmlSock, buffer, ContentLength, MSG_WAITALL );
    if ( len < 1 )
        goto ERROR;

    // Setup to parse the post data
    parseIndex = 0;
    buffer[ContentLength] = '\0';

    // Process request variables until there are none left
    do
    {
        key   = cgiParseVars( buffer, &parseIndex );
        value = cgiParseVars( buffer, &parseIndex );

        if( !strcmp("name", key) )
            name = value;
        else if( !strcmp("pizza", key) )
            pizza = value;
        else if( !strcmp("spam", key) )
            spam = value;
        else if( !strcmp("color", key) )
            color = value;
    } while ( parseIndex != -1 );

    //
    // Output the data we read in...
    //

    httpSendStatusLine(htmlSock, HTTP_OK, CONTENT_TYPE_HTML);
    // CRLF before entity
    html( CRLF );

    //
    // Build our HTML response
    //
    html(pstr_HTML_START);
    html("<h1>Form Information</h1>");
    html(pstr_DIVIDER);
    html(pstr_TABLE_START);

    if( name )
    {
      sprintf( htmlbuf, tablefmt, "Name:", name );
      html( htmlbuf );
    }

    if( spam )
    {
      sprintf( htmlbuf, tablefmt, "Likes Spam:", spam );
      html( htmlbuf );
    }

    if( pizza )
    {
      sprintf( htmlbuf, tablefmt, "Favorite Pizza:", pizza );
      html( htmlbuf );
    }

    if( color )
    {
      sprintf( htmlbuf, tablefmt, "Favorite Color:", color );
      html( htmlbuf );
    }

    html(pstr_TABLE_END);
    html(pstr_DIVIDER);
    html(pstr_LINK_MAIN_SUBDIR);
    html(pstr_HTML_END);

ERROR:
    if( buffer )
        mmBulkFree( buffer );

    return( 1 );
}


//
// MultiPart Form Sample CGI  Function
//
// This function processes the sample CGI from off the main
// WEB page on the HTTP server.
//
// CGI Functions must return 1 if the socket is left open,
// and zero if the socket is closed. This example always
// returns 1.
//
static int cgiSampleMulti(SOCKET htmlSock, int ContentLength, char *pArgs )
{
    CGIPARSEREC recs[8];
    int         len,numrecs,i;
    char        *buffer;
    char        htmlbuf[MAX_RESPONSE_SIZE];

    // CGI Functions can now support URI arguments as well if the
    // pArgs pointer is not NULL, and the ContentLength were zero,
    // we could parse the arguments off of pArgs instead.

    // First, allocate a buffer for the request
    buffer = (char*) mmBulkAlloc( ContentLength );
    if ( !buffer )
        goto ERROR;

    // Now read the data from the client
    len = recv( htmlSock, buffer, ContentLength, MSG_WAITALL );
    if ( len < 1 )
        goto ERROR;

    // Parse the form data and return the record count
    numrecs = cgiParseMultiVars( buffer, len, recs, 8 );

    // Output the data we read in...
    httpSendStatusLine(htmlSock, HTTP_OK, CONTENT_TYPE_HTML);
    // CRLF before entity
    html( CRLF );

    //
    // Build our HTML response
    //
    html(pstr_HTML_START);
    html("<h1>Form Information</h1>");
    html(pstr_DIVIDER);
    html(pstr_TABLE_START);

    for( i=0; i<numrecs; i++ )
    {
        sprintf( htmlbuf, tablefmtd, "RECORD NUMBER:", i+1 );
        html( htmlbuf );

        sprintf( htmlbuf, tablefmt, "Name:", recs[i].Name );
        html( htmlbuf );

        if(recs[i].Filename)
        {
            if( !recs[i].Filename[0] )
                sprintf( htmlbuf, tablefmt, "Filename:", "<i>NULL</i>" );
            else
                sprintf( htmlbuf, tablefmt, "Filename:", recs[i].Filename );
            html( htmlbuf );
        }

        if(recs[i].Type)
        {
            sprintf( htmlbuf, tablefmt, "Content-Type:", recs[i].Type );
            html( htmlbuf );
        }

        sprintf( htmlbuf, tablefmtd, "Data Size:", recs[i].DataSize );
        html( htmlbuf );

        if( recs[i].DataSize < 32 )
        {
            if( !recs[i].Data[0] )
                sprintf( htmlbuf, tablefmt, "Data:", "<i>NULL</i>" );
            else
                sprintf( htmlbuf, tablefmt, "Data:", recs[i].Data );
            html( htmlbuf );
        }
    }

    html(pstr_TABLE_END);
    html(pstr_DIVIDER);
    html(pstr_LINK_MAIN_SUBDIR);
    html(pstr_HTML_END);

ERROR:
    if( buffer )
        mmBulkFree( buffer );

    return( 1 );
}


//
// Functions to create CGI htmlbuf
//
static void CreateIPUse(SOCKET htmlSock);
static void CreatehtmlSockets(SOCKET htmlSock);
static void CreateRoute(SOCKET htmlSock);

//
// Main CGI Function
//
int cgiInform(SOCKET htmlSock, int ContentLength, char *pArgs)
{
    char *postdata = 0;
    char *name, *value;
    int  bytes;
    int  parseIndex;

    //
    // Here, lets support either a "get" or a "post". In a
    // "get", there is no ContentLength
    //
    if( !ContentLength )
    {
        // Since we know we are in "get" mode, the "get" arguments
        // must be valid
        if( pArgs )
        {
            value = pArgs;
            goto CHECKARGS;
        }

        // We don't support a get with no arguments
        http405(htmlSock);
        goto FATAL;
    }

    // Allocate space for the CGI post data
    postdata = (char *)mmBulkAlloc(ContentLength+1);
    if( !postdata )
        goto FATAL;

    // Read in the post data from the socket
    bytes = recv(htmlSock, postdata, ContentLength, MSG_WAITALL);
    if( bytes < 1 )
        goto FATAL;

    // Setup to parse the post data
    parseIndex = 0;
    postdata[ContentLength] = '\0';

    // Read until we've read the item "ip"
    do {
        name  = cgiParseVars( postdata, &parseIndex );
        value = cgiParseVars( postdata, &parseIndex );
    } while( strcmp("ip", name ) && parseIndex != -1 );

CHECKARGS:
    // Now check the value of "ip"
    if (strcmp("ipinfo", value) == 0)
        CreateIPUse(htmlSock);
    else if (strcmp("sockets", value) == 0)
        CreatehtmlSockets(htmlSock);
    else if (strcmp("route", value) == 0)
        CreateRoute(htmlSock);
    else
        http405(htmlSock);

FATAL:
    // Free the data we've allocated
    if( postdata )
        mmBulkFree(postdata);

    // We always leave the socket open
    return( 1 );
}


void CreateIPUse(SOCKET htmlSock)
{
    IPN     myIP;
    IPN     yourIP;
    char    pszmyIP[32];
    char    pszyourIP[32];
    struct  sockaddr_in Info;
    int     InfoLength;
    char    tmpBuf[128];
    HOSTENT *dnsInfo;
    char    htmlbuf[MAX_RESPONSE_SIZE];
    int     rc;

    InfoLength = sizeof(Info);
    getsockname( htmlSock, (PSA)&Info, &InfoLength );
    myIP = Info.sin_addr.s_addr;
    NtIPN2Str( myIP, pszmyIP );

    InfoLength = sizeof(Info);
    getpeername( htmlSock, (PSA)&Info, &InfoLength );
    yourIP = Info.sin_addr.s_addr;
    NtIPN2Str( yourIP, pszyourIP );

    httpSendStatusLine(htmlSock, HTTP_OK, CONTENT_TYPE_HTML);
    // CRLF before entity
    html( CRLF );

    html(pstr_HTML_START);
    html(pstr_TI_START);
    html("<h1>IP Address Information</h1>\r\n");
    html(pstr_DIVIDER);

    html(pstr_TABLE_START);

    html(pstr_ROW_START);
    sprintf(htmlbuf,"<td>HTTP Server IP Address</td><td>%s</td>", pszmyIP);
    html(htmlbuf);
    html(pstr_ROW_END);

    html(pstr_ROW_START);
    html("<td>HTTP Server Hostname</td>");
    rc = DNSGetHostByAddr( myIP, tmpBuf, sizeof(tmpBuf) );
    if( rc )
        sprintf(htmlbuf, "<td>%s</td>", DNSErrorStr(rc) );
    else
    {
        dnsInfo = (HOSTENT*) tmpBuf;
        sprintf(htmlbuf, "<td>%s</td>", dnsInfo->h_name);
    }
    html(htmlbuf);
    html(pstr_ROW_END);

    html(pstr_ROW_START);
    sprintf(htmlbuf, "<td>Your IP Address</td><td>%s</td>", pszyourIP);
    html(htmlbuf);
    html(pstr_ROW_END);

    html(pstr_ROW_START);
    html("<td>Your Hostname</td>");
    rc = DNSGetHostByAddr( yourIP, tmpBuf, sizeof(tmpBuf) );
    if( rc )
        sprintf(htmlbuf, "<td>%s</td>", DNSErrorStr(rc) );
    else
    {
        dnsInfo = (HOSTENT*) tmpBuf;
        sprintf(htmlbuf, "<td>%s</td>", dnsInfo->h_name);
    }
    html(htmlbuf);
    html(pstr_ROW_END);

    html(pstr_TABLE_END);
    html(pstr_DIVIDER);
    html(pstr_LINK_MAIN);
    html(pstr_TI_END);
    html(pstr_HTML_END);
}

static void DumphtmlSockets( SOCKET htmlSock, uint htmlSockProt );

void CreatehtmlSockets(SOCKET htmlSock)
{
    httpSendStatusLine(htmlSock, HTTP_OK, CONTENT_TYPE_HTML);
    // CRLF before entity
    html( CRLF );

    html(pstr_HTML_START);
    html(pstr_TI_START);
    html("<h1>TCP/IP Socket State Information</h1>\r\n");

    html(pstr_DIVIDER);
    html("<h2>TCP Sockets</h2>\r\n");
    DumphtmlSockets( htmlSock, SOCKPROT_TCP );

    html(pstr_DIVIDER);
    html("<h2>UDP Sockets</h2>\r\n");
    DumphtmlSockets( htmlSock, SOCKPROT_UDP );

    html(pstr_DIVIDER);
    html(pstr_LINK_MAIN);
    html(pstr_TI_END);
    html(pstr_HTML_END);
}

static const char *States[] = { "CLOSED","LISTEN","SYNSENT","SYNRCVD",
                          "ESTABLISHED","CLOSEWAIT","FINWAIT1","CLOSING",
                          "LASTACK","FINWAIT2","TIMEWAIT" };

static void DumphtmlSockets( SOCKET htmlSock, uint htmlSockProt )
{
    UINT8   *pBuf;
    int     Entries,i;
    SOCKPCB *ppcb;
    char    str[32];
    char    htmlbuf[MAX_RESPONSE_SIZE];


    pBuf = mmBulkAlloc(2048);
    if( !pBuf )
        return;

    // Use llEnter / llExit since we're calling into the stack
    llEnter();
    Entries = SockGetPcb( htmlSockProt, 2048, pBuf );
    llExit();

    html(pstr_TABLE_START);

    html(pstr_ROW_START);
    html("<td>Local IP</td><td>LPort</td>");
    html("<td>Foreign IP</td><td>FPort</td>\r\n");
    if( htmlSockProt == SOCKPROT_TCP )
        html("<td>State</td>\r\n");
    html(pstr_ROW_END);

    for(i=0; i<Entries; i++)
    {
        ppcb = (SOCKPCB *)(pBuf+(i*sizeof(SOCKPCB)));

        html(pstr_ROW_START);
        NtIPN2Str( ppcb->IPAddrLocal, str );
        sprintf(htmlbuf, "<td>%-15s</td><td>%-5u</td>", str, htons(ppcb->PortLocal) );
        html(htmlbuf);
        NtIPN2Str( ppcb->IPAddrForeign, str );
        sprintf(htmlbuf, "<td>%-15s</td><td>%-5u</td>\r\n", str, htons(ppcb->PortForeign) );
        html(htmlbuf);
        if( htmlSockProt == SOCKPROT_TCP )
        {
            sprintf(htmlbuf,"<td>%s</td>\r\n",States[ppcb->State]);
            html(htmlbuf);
        }
        html(pstr_ROW_END);
    }

    html(pstr_TABLE_END);

    mmBulkFree( pBuf );
}

void CreateRoute(SOCKET htmlSock)
{
    HANDLE  hRt,hIF,hLLI;
    uint    wFlags,IFType,IFIdx;
    UINT32  IPAddr,IPMask;
    char    str[32];
    UINT8   MacAddr[6];
    char    htmlbuf[MAX_RESPONSE_SIZE];

    httpSendStatusLine(htmlSock, HTTP_OK, CONTENT_TYPE_HTML);
    // CRLF before entity
    html( CRLF );

    html(pstr_HTML_START);
    html(pstr_TI_START);
    html("<h1>TCP/IP Current Route Table</h1>\r\n");
    html(pstr_DIVIDER);

    // Start walking the tree
    llEnter();
    hRt = RtWalkBegin();
    llExit();

    html(pstr_TABLE_START);

    html(pstr_ROW_START);
    html("<td>Address</td><td>Subnet Mask</td>");
    html("<td>Flags</td><td>Gateway</td>\r\n");
    html(pstr_ROW_END);

    // While there are routes, print the route information
    while( hRt )
    {
        html(pstr_ROW_START);

        // Get the IP addess and IP mask and flags of the route
        llEnter();
        IPAddr = RtGetIPAddr( hRt );
        IPMask = RtGetIPMask( hRt );
        wFlags = RtGetFlags( hRt );
        hIF    = RtGetIF( hRt );
        if( hIF )
        {
            IFType = IFGetType(hIF);
            IFIdx  = IFGetIndex(hIF);
        }
        else
            IFType = IFIdx = 0;
        llExit();

        // Print address and mask
        NtIPN2Str( IPAddr, str );
        sprintf(htmlbuf, "<td>%-15s</td>", str );
        html(htmlbuf);
        NtIPN2Str( IPMask, str );
        sprintf(htmlbuf, "<td>%-15s</td>", str );
        html(htmlbuf);

        // Decode flags
        if( wFlags & FLG_RTE_UP )
            strcpy(str,"U");
        else
            strcpy(str," ");
        if( wFlags & FLG_RTE_GATEWAY )
            strcat(str,"G");
        else
            strcat(str," ");
        if( wFlags & FLG_RTE_HOST )
            strcat(str,"H");
        else
            strcat(str," ");
        if( wFlags & FLG_RTE_STATIC )
            strcat(str,"S");
        else
            strcat(str," ");
        if( wFlags & FLG_RTE_CLONING )
            strcat(str,"C");
        else
            strcat(str," ");
        if( wFlags & FLG_RTE_IFLOCAL )
            strcat(str,"L");
        else
            strcat(str," ");

        sprintf(htmlbuf, "<td>%s</td>", str );
        html(htmlbuf);

        // If the route is a gateway, print the gateway IP address as well
        if( wFlags & FLG_RTE_GATEWAY )
        {
            llEnter();
            IPAddr = RtGetGateIP( hRt );
            llExit();
            NtIPN2Str( IPAddr, str );
            sprintf(htmlbuf, "<td>%-15s</td>", str );
            html(htmlbuf);
        }
        // Else if non-local host route on Ethernet, print ARP entry
        else if( IFType == HTYPE_ETH &&
                 (wFlags&FLG_RTE_HOST) && !(wFlags&FLG_RTE_IFLOCAL) )
        {
            // The stack has a MAC address if it has an LLI (link-layer info)
            // object, and LLIGetMacAddr returns 1.
            llEnter();
            if( !(hLLI = RtGetLLI( hRt )) || !LLIGetMacAddr( hLLI, MacAddr, 6 ) )
                llExit();
            else
            {
                llExit();
                sprintf( htmlbuf,"<td>%02X:%02X:%02X:%02X:%02X:%02X</td>",
                           MacAddr[0], MacAddr[1], MacAddr[2],
                           MacAddr[3], MacAddr[4], MacAddr[5] );
                html(htmlbuf);
            }
        }
        // Else just print out the interface
        else if( IFIdx )
        {
            if( wFlags & FLG_RTE_IFLOCAL )
            {
                sprintf( htmlbuf,"<td>local (if-%d)</td>", IFIdx );
                html(htmlbuf);
            }
            else
            {
                sprintf( htmlbuf,"<td>if-%d</td>", IFIdx );
                html(htmlbuf);
            }
        }

        html(pstr_ROW_END);

        llEnter();
        hRt = RtWalkNext( hRt );
        llExit();
    }
    llEnter();
    RtWalkEnd( 0 );
    llExit();

    html(pstr_TABLE_END);
    html(pstr_DIVIDER);
    html(pstr_LINK_MAIN);
    html(pstr_TI_END);
    html(pstr_HTML_END);
}
