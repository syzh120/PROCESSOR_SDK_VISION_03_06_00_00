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
 * ======== httppars.c ========
 *
 */
#include "http.h"

/*------------------------------------------------------------------------- */
/* httpParseRecv() */
/* This is the entrypoint for all HTTP requests. */
/* Returns: */
/*    1 Delimitor Detected */
/*    0 Terminator Detected */
/*   -1 Socket Error */
/*------------------------------------------------------------------------- */
int httpParseRecv( HTTP_MSG *pMsg )
{
    char *parsestrptr;
    char *bufptr;
    int  olength, plength;
    int  bytes = 0;
    char *endptr;
    int  canread;

    /* Move over data that has been previously consumed */
    memcpy( pMsg->request, pMsg->request+pMsg->parsed, pMsg->unparsed);

    for(;;)
    {
        if( !pMsg->flagreadall )
        {
            /* Calculate the bytes to read from the stream */
            canread = (MAXREQUEST-1) - pMsg->unparsed;

            /* Read the parse buffer with as much data as possible */
            bytes = recv( pMsg->Sock, pMsg->request+pMsg->unparsed,
                          canread, MSG_PEEK );
            if( bytes < 1 )
                return(-1);

            /* Make sure the string is terminated */
            pMsg->request[pMsg->unparsed+bytes] = '\0';

            /* Look for terminator in "request" */
            endptr = (char *) strstr(pMsg->request, pMsg->termstr);

            /* If terminator found, read up to the terminator */
            if (endptr != NULL)
            {
                /* Read up to and including terminator */
                bytes = recv( pMsg->Sock, pMsg->request + pMsg->unparsed,
                              (int)(endptr-(pMsg->request+pMsg->unparsed)) +
                              strlen(pMsg->termstr), 0);

                /* Mark that we have read all data */
                pMsg->flagreadall = 1;
            }
            else
            {
                /* Else read as much as we can */
                bytes = recv( pMsg->Sock, pMsg->request+pMsg->unparsed,
                              canread, 0);
            }

            /* If either read failed, quit */
            if (bytes < 1)
                return(-1);
        }

        pMsg->unparsed += bytes;
        parsestrptr = pMsg->parsestr;
        bufptr      = pMsg->request;
        olength     = 0;
        plength     = 0;

        /* While data left to parse, look for a delimitor */
        while( olength < pMsg->unparsed )
        {
            /* If buffer matching delimitor string, continue */
            if (*bufptr == *parsestrptr)
            {
                parsestrptr++;
                plength++;
            }
            /* Else reset delimitor */
            else
            {
                parsestrptr = pMsg->parsestr;
                plength = 0;
            }

            /* Bump consumed byte counts */
            bufptr++;
            olength++;

            /* If we matched the delimitor, break */
            if (*parsestrptr == '\0')
              break;
        }

        /* Get the length of the message without delimitor */
        pMsg->length = olength - plength;

        if (*parsestrptr == '\0')
        {
            /* Message Found */

            /* NULL terminate message */
            *(bufptr-plength) = '\0';

            /* Record message as "parsed" */
            pMsg->parsed = olength;
            pMsg->unparsed -= olength;

            return(1);
        }
        else
        {
            /* Message Not Found */

            /* We must keep looking for the message. We will do */
            /* this until one of two things happens. We either */
            /* hit the terminator or fill up our max read size. */

            /* Check terminator first */
            if( pMsg->flagreadall )
                return(0);

            /* Check for max read condition */
            if( pMsg->unparsed >= (MAXREQUEST-1) )
                return(-1);
        }
    }
}

