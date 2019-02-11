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
 * ======== tcp6.c ========
 *
 * The file has generic functions used by the TCP6 Module.
 *
 */


#include <stkmain.h>
#include "tcp6.h"

#ifdef _INCLUDE_IPv6_CODE

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/* This is the linked list which keeps track of all TCP6 Protocol Information
 * Blocks in the System for Timer Management. */
TCPPROT* pt6TimeFirst = NULL;

/* TCP6 Initial Send Sequence. */
UINT32   tcp6_iss     = 0x7F000000; 

/**********************************************************************
 ***************************** TCP6 Functions *************************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function adds the TCP6 Protocol object to the timeout list
 *
 *  @param[in]   pt
 *      The TCP Protocl object to be added to the timeout list.
 *
 *  @retval
 *      Not Applicable.
 */
void TCP6TimeoutAdd (TCPPROT *pt)
{
    /* Add the TCP protocol object to the head of the list. */ 
    pt->pPrev = 0;
    pt->pNext = pt6TimeFirst;
    if( pt6TimeFirst )
        pt6TimeFirst->pPrev = pt;
    pt6TimeFirst = pt;
}

/** 
 *  @b Description
 *  @n  
 *      The function removes the TCP6 Protocol object to the timeout list
 *
 *  @param[in]   pt
 *      The TCP Protocl object to be removed from the timeout list.
 *
 *  @retval
 *      Not Applicable.
 */
void TCP6TimeoutRemove( TCPPROT *pt )
{
    /* Patch preceeding entry */
    if( !pt->pPrev )
        pt6TimeFirst = pt->pNext;
    else
        pt->pPrev->pNext = pt->pNext;

    /* Patch following entry */
    if( pt->pNext )
       pt->pNext->pPrev = pt->pPrev;
}

/** 
 *  @b Description
 *  @n  
 *      The function scan the timeout list for TCP timeouts
 *
 *  @retval
 *      Not Applicable.
 */
void TCP6TimeoutCheck()
{
    TCPPROT *pt;
    TCPPROT **ppt;
    UINT32  TimeWaitCnt = 0;
    UINT32  TicksTWLow  = 0xFFFFFFFF;
    UINT32  TicksTWHigh = 0;;

    ppt = &pt6TimeFirst;

    while( *ppt )
    {
        pt = *ppt;

        /* Check all timers. If pt goes away by calling the timeout */
        /* function, then move on to the next one. */
        if( pt->TicksRexmt && !--pt->TicksRexmt )
        {
            TCP6TimeoutRexmt( pt );
            if( *ppt != pt )
                continue;
        }


        /* RFC 2018 - SACK */
        if( pt->TicksSackRexmt && !--pt->TicksSackRexmt )
        {
            TCP6TimeoutSackRexmt( pt );
            if( *ppt != pt )
                continue;
        }

        if( pt->TicksPersist && !--pt->TicksPersist )
        {
            TCP6TimeoutPersist( pt );
            if( *ppt != pt )
                continue;
        }

        if( pt->TicksKeep && !--pt->TicksKeep )
        {
            TCP6TimeoutKeep( pt );
            if( *ppt != pt )
                continue;
        }

        if( pt->TicksWait2 )
        {
            if( !--pt->TicksWait2 )
            {
                TCP6TimeoutWait2( pt );
                if( *ppt != pt )
                    continue;
            }
            else if( pt->t_state == TSTATE_TIMEWAIT )
            {
                TimeWaitCnt++;
                if( pt->TicksWait2 < TicksTWLow )
                    TicksTWLow = pt->TicksWait2;
                if( pt->TicksWait2 > TicksTWHigh )
                    TicksTWHigh = pt->TicksWait2;
            }
        }

        /* Perform any delayed ACK */
        if( pt->t_flags & TF_DELACK )
        {
            pt->t_flags &= ~TF_DELACK;
            pt->t_flags |= TF_ACKNOW;
            tcps.DelAck++;
            TCP6Output(pt);
        }
        else if( pt->t_flags & TF_NEEDOUTPUT )
            TCP6Output(pt);

        /* Bump Idle time */
        pt->t_tidle++;

        /* Bump RTT counter if active */
        if( pt->t_trtt )
            pt->t_trtt++;

        /* Move on to next block */
        ppt = &pt->pNext;
    }

    /* Bump TCP start sequence */
    tcp6_iss += TCP_ISSINCR/2;

    /* Fix any socket glut in TIMEWAIT */
    if( TimeWaitCnt >= 20 )
    {
        /* Set a cutoff half way in the range */
        TicksTWLow = (TicksTWLow+TicksTWHigh)/2;

        ppt = &pt6TimeFirst;

        while( *ppt )
        {
            pt = *ppt;

            /* Accelerate TIMEWAIT timeouts that fall in the */
            /* cutoff range. */
            if( pt->TicksWait2 && pt->t_state == TSTATE_TIMEWAIT )
            {
                if( pt->TicksWait2 <= TicksTWLow )
                {
                    pt->TicksWait2 = 0;
                    TCP6TimeoutWait2( pt );
                    if( *ppt != pt )
                        continue;
                }
            }

            /* Move on to next block */
            ppt = &pt->pNext;
        }
    }
}

#endif /* _INCLUDE_IPv6_CODE */

