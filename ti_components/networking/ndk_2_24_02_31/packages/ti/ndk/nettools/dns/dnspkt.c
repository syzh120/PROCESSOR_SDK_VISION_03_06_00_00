/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 * ======== dnspkt.c ========
 *
 * DNS Packet routines
 *
 */

#include "dns.h"


/* Static Functions */

static void DNSWriteRecord( DNSHDR *pDNS, UINT8 *pbWrite, UINT16 NumRec,
                            DNSREC *pRec, UINT16 *pWUsed, int fReply );
static void DNSWriteName( UINT8 *pBuf, UINT8 *pbWrite, UINT16 Size,
                          UINT8 *pData, UINT16 *pWUsed, int fCompress );
static int DNSReadRecord( DNSHDR *pDNS, UINT8 *pbRead, int Count,
                          DNSREC *pRec, UINT16 *pRUsed, uint fReply );
static void DNSReadName( UINT8 *pBase, UINT8 *pbRead, UINT8 *pbWrite,
                         UINT16 size, UINT16 *pru, UINT16 *pwu );

/*-------------------------------------------------------------------- */
/* DNSGetQuery */

/* Checks the DNS query packet and returns the number of query */
/* records decoded. */

/* Returns -1 if the packet has an error, or 0 if no questions */
/*-------------------------------------------------------------------- */
int DNSGetQuery( DNSHDR *pDNS, DNSREC *pQuery )
{
    UINT8   *pbRead = pDNS->Data;
    UINT16  RecordCount;
    UINT16  readused;
    int     rc;

    /* Get the question count */
    RecordCount = htons(pDNS->NumQ);

    /* If RecordCount looks bogus, then punt */
    if( RecordCount < 1 || RecordCount > 3 )
        return(0);

    /* Read the Questions */
    rc = DNSReadRecord( pDNS, pbRead, RecordCount, pQuery, &readused, 0 );
    return( rc );
}

/*-------------------------------------------------------------------- */
/* DNSGetReply */

/* Checks the DNS reply and decodes the results into a DNSREPLY */
/* structure. */

/* Returns 1 if reply is found, else 0 */
/*-------------------------------------------------------------------- */
int DNSGetReply( DNSHDR *pDNS, UINT16 Id, int cc, DNSREPLY *pReply )
{
    UINT8   *pbRead = pDNS->Data;
    DNSREC  *pRec = 0;
    UINT16  readused;
    int     rc;

    (void)cc;

    /* Initialize the reply */
    bzero( pReply, sizeof( DNSREPLY ) );

    /* If this isn't the packet we're looking for, return now */

    /* Make sure this is a reply */
    pReply->Flags = htons( pDNS->Flags );
    if( !(pReply->Flags & FLG_DNS_QR) )
        return( 0 );

    /* Make sure it has the expected id */
    if( Id != htons( pDNS->Id ) )
        return( 0 );

    /* Read the Questions */
    /* If the question count is not 1, something is wrong - abort */
    if( htons(pDNS->NumQ) != 1 )
        return(0);

    /* If the packet is truncated, don't chance it - abort */
    if( pReply->Flags & FLG_DNS_TC )
        return(1);

    /* Allocate a question record */
    pRec = mmAlloc( sizeof(DNSREC) );
    if( !pRec )
        return(0);

    /* Read question */
    rc = DNSReadRecord( pDNS, pbRead, 1, pRec, &readused, 0 );
    pbRead += readused;

    /* We don't really need the question. We just needed to adavance */
    /* the read pointer. However, we fail if the read was bad */
    if( !rc )
        goto grleave;

    /* Read the answers */
    pReply->NumAns = htons( pDNS->NumA );
    if( pReply->NumAns )
    {
        /* Read the record(s) */
        rc = DNSReadRecord( pDNS, pbRead, pReply->NumAns, pRec, &readused, 1 );
        pbRead += readused;
        pReply->NumAns = (UINT16)rc;
        if( rc )
        {
            /* Set the head of the answer chain and clear pRec */
            pReply->pAns = pRec;
            pRec = 0;
        }
    }

    /* Read the authority */
    pReply->NumAuth = htons( pDNS->NumAuth );
    if( pReply->NumAuth )
    {
        /* We may haveto allocate another record */
        if( !pRec && !(pRec = mmAlloc(sizeof(DNSREC))) )
            goto grleave;

        /* Read the record(s) */
        rc = DNSReadRecord( pDNS, pbRead, pReply->NumAuth, pRec, &readused, 1 );
        pbRead += readused;
        pReply->NumAuth = (UINT16)rc;
        if( rc )
        {
            /* Set the head of the auth chain and clear pRec */
            pReply->pAuth = pRec;
            pRec = 0;
        }
    }

    /* Read the additional records */
    pReply->NumAux = htons( pDNS->NumA );
    if( pReply->NumAux )
    {
        /* We may haveto allocate another record */
        if( !pRec && !(pRec = mmAlloc(sizeof(DNSREC))) )
        {
            pReply->NumAux = 0;
            goto grleave;
        }

        /* Read the record(s) */
        rc = DNSReadRecord( pDNS, pbRead, pReply->NumAux, pRec, &readused, 1 );
        pbRead += readused;
        pReply->NumAux = (UINT16)rc;
        if( rc )
        {
            pReply->pAux = pRec;
            pRec = 0;
        }
    }

grleave:
    if( pRec )
        mmFree( pRec );

    return(1);
}

/*-------------------------------------------------------------------- */
/* DNSBuildRequest */

/* Builds up a DNS request packet with the given question and type */

/* Returns the size of the request packet */
/*-------------------------------------------------------------------- */
int DNSBuildRequest( DNSHDR *pDNS, UINT16 Id, DNSREC *pQuery )
{
    UINT8      *pbWrite = pDNS->Data;
    UINT16     writeused;

    /* Build the packet header */
    pDNS->Id      = htons( Id );
    pDNS->Flags   = htons( FLG_DNS_RD );
    pDNS->NumQ    = htons( 1 );
    pDNS->NumA    = 0;
    pDNS->NumAuth = 0;
    pDNS->NumAux  = 0;

    /* Encode the question */
    DNSWriteRecord( pDNS, pbWrite, 1, pQuery, &writeused, 0 );
    pbWrite += writeused;

    /* Return the final packet count */
    return( (int)(pbWrite - (UINT8 *)pDNS) );
}

/*-------------------------------------------------------------------- */
/* DNSBuildReply */

/* Builds up a DNS reply packet. Only gross size checks are performed, */
/* so this function should be called with a buffer significantly larger */
/* that a max packet (2x is ideal). */

/* This is safe because: */
/*  1. The stack will not generate anything but single entry replies. */
/*  2. Any outside reply must have originated in a UDP sized packet. */

/* Returns the size of the reply packet */
/*-------------------------------------------------------------------- */
int DNSBuildReply( DNSHDR *pDNS, UINT16 Id, DNSREC *pQ, DNSREPLY *pA )
{
    UINT8      *pbWrite = pDNS->Data;
    UINT16     writeused;

    /* Build the packet header */
    pDNS->Id      = htons( Id );
    pDNS->NumQ    = htons( 1 );
    pDNS->NumA    = htons( pA->NumAns );
    pDNS->NumAuth = htons( pA->NumAuth );
    pDNS->NumAux  = htons( pA->NumAux );

    /* Encode the question */
    DNSWriteRecord( pDNS, pbWrite, 1, pQ, &writeused, 0 );
    pbWrite += writeused;

    /* Encode Answers */
    DNSWriteRecord( pDNS, pbWrite, pA->NumAns, pA->pAns, &writeused, 1 );
    pbWrite += writeused;

    /* Gross size check */
    if( (pbWrite - (UINT8 *)pDNS) > DNS_PACKET_MAX )
        goto size_error;

    /* Encode Authorities */
    DNSWriteRecord( pDNS, pbWrite, pA->NumAuth, pA->pAuth, &writeused, 1 );
    pbWrite += writeused;

    /* Gross size check */
    if( (pbWrite - (UINT8 *)pDNS) > DNS_PACKET_MAX )
        goto size_error;

    /* Encode Aux */
    DNSWriteRecord( pDNS, pbWrite, pA->NumAux, pA->pAux, &writeused, 1 );
    pbWrite += writeused;

    /* Final size check */
    if( (pbWrite - (UINT8 *)pDNS) > DNS_PACKET_MAX )
        goto size_error;

    /* No size error, so set the flags */
    pDNS->Flags = htons( pA->Flags );

    /* Return the final packet count */
    return( (int)(pbWrite - (UINT8 *)pDNS) );

size_error:
    /* Truncated packet */
    pA->Flags |= FLG_DNS_TC;
    pDNS->Flags = htons( pA->Flags );
    return( DNS_PACKET_MAX );
}

/*-------------------------------------------------------------------- */
/* DNSWriteRecord() */

/* This function writes a record to a DNS packet. If the fReply flag */
/* is set, the record is a reply - else its a question */
/*-------------------------------------------------------------------- */
static void DNSWriteRecord( DNSHDR *pDNS, UINT8 *pbWrite, UINT16 NumRec,
                            DNSREC *pRec, UINT16 *pWUsed, int fReply )
{
    UINT16 writeused;
    UINT8  *pbWriteOrig = pbWrite;

    while( NumRec-- )
    {
        /* Encode the record */
        DNSWriteName( (UINT8 *)pDNS, pbWrite,
                      (UINT16)strlen((char *)(pRec->Name)),
                      pRec->Name, &writeused, fReply );
        pbWrite += writeused;

        /* Write Type and Class */
        DNSWRITE16( pRec->Type, pbWrite );
        DNSWRITE16( pRec->Class, pbWrite );

        if( fReply )
        {
            /* Write TTL and Resource */
            DNSWRITE32( pRec->Ttl, pbWrite );

            if( pRec->Type == T_A 
#ifdef _INCLUDE_IPv6_CODE
                || pRec->Type == T_AAAA 
#endif
                )
            {
                /* On IP Address, just copy the data */
                DNSWRITE16( pRec->DataLength, pbWrite );
                mmCopy( pbWrite, pRec->Data, pRec->DataLength );
                pbWrite += pRec->DataLength;
            }
            else
            {
                /* Encode the data (leave room for size) */
                DNSWriteName( (UINT8 *)pDNS, pbWrite+2, pRec->DataLength,
                              pRec->Data, &writeused, fReply );

                /* Write the encoded size */
                DNSWRITE16( writeused, pbWrite );
                pbWrite += writeused;
            }
        }

        pRec = pRec->pNext;
    }

    /* Return the total space we used */
    *pWUsed = (UINT16)(pbWrite - pbWriteOrig);
}

/*-------------------------------------------------------------------- */
/* DNSWriteName() */

/* Routine to write encoded name to buffer. If the fCompress flag is */
/* not set, then compression is not required. */
/*-------------------------------------------------------------------- */
static void DNSWriteName( UINT8 *pBuf, UINT8 *pbWrite, UINT16 Size,
                          UINT8 *pData, UINT16 *pWUsed, int fCompress )
{
    UINT8  *pbWriteOrig = pbWrite;
    UINT8  *pbComp;
    UINT8  *pbMatch;
    UINT16 AltPtr;
    UINT16 matchsize,i;

    /* First encode the entry without compression */
    while( Size )
    {
        /* Ignore last (or leading) dot */
        if( *pData == '.' )
        {
            pData++;
            Size--;
        }
        else
        {
            /* Find the next dot */
            for( i=0; i<Size && *(pData+i)!='.'; i++ );

            /* Quit if we're done */
            if( !i )
                break;

            /* Make the count "safe" */
            i &= ~RR_PTR;

            /* Encode the entry */
            *pbWrite++ = (UINT8)i;
            Size -= i;
            while( i-- )
                *pbWrite++ = *pData++;
        }
    }
    *pbWrite++ = 0;

    if( !fCompress )
        goto enc_done;

    /* Get the entry size */
    matchsize = (UINT16)(pbWrite - pbWriteOrig);
    pbComp    = pbWriteOrig;

    while( matchsize > 1 )
    {
        /* Try and find a matching string */
        for( pbMatch = pBuf; pbMatch < pbComp; pbMatch++ )
        {
            for( i=0; i<matchsize; i++ )
            {
                if( *(pbComp+i) != *(pbMatch+i) )
                    break;
            }

            if( i == matchsize )
            {
                /* Found an identical entry at pbMatch */
                AltPtr = ((UINT16)(pbMatch-pBuf))|(RR_PTR << 8);
                pbWrite = pbComp;
                DNSWRITE16( AltPtr, pbWrite );
                goto enc_done;
            }
        }

        /* Try shortening matchsize */
        i = (UINT16) *pbComp++;
        pbComp += i;
        matchsize -= (i+1);
    }

enc_done:
    /* Return the total space we used */
    *pWUsed = (UINT16)(pbWrite - pbWriteOrig);
}

/*-------------------------------------------------------------------- */
/* DNSReadRecord() */

/* Reads one or more records to a DNSREC chain. The first element */
/* in the chain must be pre-allocated. The remainer are allocated */
/* in this routine. */
/*-------------------------------------------------------------------- */
static int DNSReadRecord( DNSHDR *pDNS, UINT8 *pbRead, int Count,
                          DNSREC *pRec, UINT16 *pRUsed, uint fReply )
{
    UINT16 readused, writeused;
    UINT8  *pbReadOrig = pbRead;
    DNSREC *pThis,*pPrev;
    int    rc;

    /* Setup "this", "prev", and the total record count */
    pThis = pRec;
    pPrev = 0;
    rc    = 0;

    while( Count-- )
    {
        /* Allocate the next record if needed */
        if( !pThis && !(pThis = mmAlloc( sizeof(DNSREC) )) )
            goto rrexit;

        /* Initialize the record */
        bzero( pThis, sizeof(DNSREC) );

        /* Read the query name */
        DNSReadName( (UINT8 *)pDNS, pbRead, pThis->Name, DNS_NAME_MAX-2,
                     &readused, &writeused );
        pbRead += readused;
        if( !writeused )
            goto rrexit;

        /* Read type and class */
        DNSREAD16( pThis->Type, pbRead );
        DNSREAD16( pThis->Class, pbRead );

        /* This this is a reply, there's more data */
        if( fReply )
        {
            /* Get the Ttl */
            DNSREAD32( pThis->Ttl, pbRead );

            /* Get the Record Size */
            DNSREAD16( pThis->DataLength, pbRead );

            /* Read the data record */
            switch( pThis->Type )
            {
            case T_A:
#ifdef _INCLUDE_IPv6_CODE
            case T_AAAA:
#endif
                /* On IPv4/v6 Address, just copy the data */
                if( pThis->DataLength > DNS_NAME_MAX )
                {
                    pbRead += pThis->DataLength;
                    goto rrskip;
                }
                mmCopy( pThis->Data, pbRead, pThis->DataLength );
                pbRead += pThis->DataLength;
                break;

            case T_PTR:
            case T_NS:
            case T_CNAME:
                /* On Domain name based records, call a function to */
                /* read the record string. */
                DNSReadName( (UINT8 *)pDNS, pbRead, pThis->Data, DNS_NAME_MAX-2,
                             &readused, &writeused );
                pbRead += pThis->DataLength;
                pThis->DataLength = writeused;
                if( !writeused )
                    goto rrexit;
                break;

            default:
                /* To be safe, we skip records that we don't directly handle */
                pbRead += pThis->DataLength;
                goto rrskip;
            }
        }

        /* Link this record onto the chain */
        if( pPrev )
            pPrev->pNext = pThis;
        pPrev = pThis;
        pThis = 0;

        /* Bump the return count */
        rc++;
rrskip:;
    }

rrexit:
    /* Free the last record if we aborted it */
    if( pThis && pPrev )
        mmFree( pThis );
    *pRUsed = (UINT16)(pbRead - pbReadOrig);
    return( rc );
}

/*-------------------------------------------------------------------- */
/* DNSReadName */

/* Routine to read an encoded name out of a DNS packet. Copies the */
/* name to the supplied buffer, and tracks the number of read and */
/* write bytes consumed. */

/*-------------------------------------------------------------------- */
static void DNSReadName
(
    UINT8    *pBase,            /* Start of DNS packet */
    UINT8    *pbRead,           /* Current Read Ptr */
    UINT8    *pbWrite,          /* Current Write Ptr in temp buffer space */
    UINT16   size,              /* Size of temp buffer space */
    UINT16   *pru,              /* Return read space used */
    UINT16   *pwu               /* Return write space used (0 on overflow) */
)
{
    UINT8   bTmp1,bTmp2;
    UINT16  wTmp;
    UINT16  ru,wu,twu;

    ru = wu = 0;

    for(;;)
    {
        /* Make sure we're not running amok */
        if( (pbRead - pBase) > DNS_PACKET_MAX )
            goto done;

        /* Check for a "pointer" instead of a count */
        if( (*pbRead & RR_PTR) == RR_PTR )
        {
            /* We have a pointer */
            DNSREAD16( wTmp, pbRead );
            ru += 2;
            wTmp &= ~(RR_PTR << 8);
            DNSReadName( pBase, pBase+wTmp, pbWrite, size, 0, &twu );

            /* All done: Add in the "write used" count to our "write used" count */
            /* If the function returned an error, then the results are unreliable */
            if( !twu )
                wu = 0;
            else
                wu += twu;
            goto done;
        }
        else
        {
            /* We have a standard byte count */
            bTmp1 = *pbRead++;
            ru++;

            /* If at end, add NULL terminator */
            if( !bTmp1 )
            {
                if( size-- > 0 )
                {
                    *pbWrite++ = 0;
                    wu++;
                }
                else
                    wu = 0;

                goto done;
            }

            /* Else, concatinate this string */
            while( bTmp1-- )
            {
                bTmp2 = *pbRead++;
                ru++;

                /* Add this character */
                if( size-- > 0 )
                {
                    *pbWrite++ = bTmp2;
                    wu++;
                }
                else
                {
                    wu = 0;
                    goto done;
                }
            }

            /* After each string, add a dot when there's more to come */
            if( *pbRead )
            {
                if( size-- > 0 )
                {
                    *pbWrite++ = '.';
                    wu++;
                }
                else
                {
                    wu = 0;
                    goto done;
                }
            }
        }
    }

done:
    if( pru )
        *pru = ru;
    if( pwu )
        *pwu = wu;
    return;
}

