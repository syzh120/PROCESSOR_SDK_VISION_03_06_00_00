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
 * ======== cgiparsem.c ========
 *
 * Multipart CGI parsing for "multipart/from-data" forms.
 *
 */

#include <netmain.h>
#include <_stack.h>
#include "cgiparsem.h"

/*
 * myscan()
 *
 * Simple scan function. Returns the index of the start of
 * the terminator from the beginning of the buffer.
 */
static int myscan( char *buffer, char *terminator, int buflen )
{
    int i,len;

    len = strlen( terminator );

    buflen -= len;

    for( i=0; buflen>=0; i++, buflen-- )
    {
        if( !strncmp( buffer+i, terminator, len ) )
            return(i);
    }

    return(-1);
}

static char *CGI_CRLF = "\r\n";

/* 
 * cgiParseMultiVars()
 *
 * This function is used to parse CGI data sent in the "multipart/form-data"
 * format. The caller must pass in the entire CGI payload as a single buffer.
 * The buffer will altered to add NULL termination to all names, types, and
 * data fields.
 *
 * Returns the number of validated records, or -1 on parsing error.
 */
int cgiParseMultiVars( char *buffer, int buflen, CGIPARSEREC *recs, int maxrecs )
{
    char *divider;
    int  i,numrecs,fname;
    char *tstr,*tmark,*tmarkv;
    int  tlen,divlen;
    char c;


    /* Clear out the entire recs[] array */
    mmZeroInit( recs, sizeof(CGIPARSEREC) * maxrecs );

    /* First, read in our divider. The buffer must start with "--". */
    if( *buffer!='-' || *(buffer+1)!='-' )
        return(-1);

    /* Scan for "\r\n" and put in "divider" */
    i = myscan( buffer, CGI_CRLF, buflen );
    if( i < 3 )         /* Minimum divider is "--?" */
        return(-1);
    divider = buffer;
    divlen  = i;
    *(divider+i) = 0;   /* Null terminate the string */
    buffer += i+2;     /* Step past the "/r/n" */
    buflen -= i+2;

    numrecs = 0;
    fname = 0;
    for( ;; )
    {
        /* Scan in the next token */
        i = myscan( buffer, CGI_CRLF, buflen );
        if( i < 0 )
            return(-1);

        /* If i==0, then we hit a "/r/n/r/n", in which case the */
        /* next field should be the data. */
        if( !i )
        {
            buffer += 2;     /* Step past the "/r/n" */
            buflen -= 2;

            /* We must have read a name by now or we have an error */
            if( !fname )
                return(-1);

            /* Scan for the divider */
            i = myscan( buffer, divider, buflen );
            if( i < 2 )         /* Minimum is "/r/nDivider" */
                return(-1);

            /* Two chars before divider must be "/r/n" */
            if( *(buffer+i-2)!='\r' || *(buffer+i-1)!='\n' )
                return(-1);

            /* Null terminate and record info */
            *(buffer+i-2) = 0;
            (recs+numrecs)->Data = buffer;
            (recs+numrecs)->DataSize = i-2;

            /* We're done with this record */
            if( ++numrecs == maxrecs )
                return( numrecs );

            /* Step past the data and the divider */
            buffer += i+divlen;
            buflen -= i+divlen;

            /* This scan must be either "2" or Zero */
            i = myscan( buffer, CGI_CRLF, buflen );

            if( i==2 )
            {
                /* This may be the real terminator. At the end of */
                /* the buffer, the data should be "--/r/n", so... */
                if( *buffer=='-' && *(buffer+1)=='-' )
                    return( numrecs );
                else
                    return( -1 );

            }

            if( i!=0 )
                return( -1 );

            /* Setup for next record */
            fname = 0;
            buffer += 2;
            buflen  -= 2;

            continue;
        }

        /* Here we have a tag that precedes the data. The tag starts */
        /* at [buffer], and is [i] characters in length. */

        /* See if the tag is "Content-Disposition:" */
        if( !strncmp( buffer, "Content-Disposition:", 20 ) )
        {
            /* We now do a sub-parsing on this string */
            tstr = buffer+20;
            tlen = i-20;

            /* Step the main status beyond this tag */
            buffer += i+2;     /* Step past the "/r/n" */
            buflen -= i+2;

            /* Sub-parse the tag */
            tmark = tstr;
            while( tlen > 0 )
            {
                c = *tstr++;
                tlen--;

                if( c==' ' || c==';' )
                    tmark = tstr;

                if( c=='=' )
                {
                    /* Null terminate the field name */
                    *(tstr-1) = 0;

                    /* Find the quotes */
                    tmarkv = 0;
                    i = 0;
                    while( tlen > 0 )
                    {
                        c = *tstr++;
                        tlen--;

                        if( c=='"' )
                        {
                            if( ++i == 1 )
                                tmarkv = tstr;
                            else
                                break;
                        }
                    }

                    /* If we didn't get two quotes, we have an error */
                    if( i != 2 )
                        return(-1);

                    /* Null terminate the field value */
                    *(tstr-1) = 0;

                    /* We look for "name" and "filename" strings */
                    if( !strcmp( tmark, "name" ) )
                    {
                        (recs+numrecs)->Name = tmarkv;
                        fname = 1;
                    }

                    if( !strcmp( tmark, "filename" ) )
                        (recs+numrecs)->Filename = tmarkv;
                }
            }

            continue;
        }


        /* See if the tag is "Content-Type:" */
        if( !strncmp( buffer, "Content-Type:", 13 ) )
        {
            /* We now do a sub-parsing on this string */
            tstr = buffer+13;
            tlen = i-13;

            /* Step the main status beyond this tag */
            buffer += i+2;     /* Step past the "/r/n" */
            buflen -= i+2;

            /* Here we'll just remove any leading spaces */
            while( *tstr == ' ' )
            {
                tstr++;
                tlen--;
            }

            /* Null terminate the string */
            *(buffer-2) = 0;

            /* Record it */
            (recs+numrecs)->Type = tstr;

            continue;
        }

        /* This is a tag we don't care about - just step past it */
        buffer += i+2;     /* Step past the "/r/n" */
        buflen -= i+2;
    }
}

