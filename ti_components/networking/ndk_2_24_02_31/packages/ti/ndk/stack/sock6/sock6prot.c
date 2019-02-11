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
 * ======== sock6prot.c ========
 *
 * The file implements the SOCKET6 Family. 
 *
 */


#include <stkmain.h>
#include "sock6.h"

#ifdef _INCLUDE_IPv6_CODE

/** 
 *  @b Description
 *  @n  
 *      The function attaches the SOCKET to the appropriate global family list.
 *
 *  @param[in]  ps
 *      The pointer to the socket which we will attach to the corresponding
 *      list.
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   Non Zero
 */
int Sock6PrAttach (SOCK6 *ps)
{
    /* Check if the protocol is TCP or UDP? */ 
    if (ps->SockProt == SOCKPROT_TCP)
        return (TCP6PrAttach((HANDLE)ps, &ps->hTP));

    /* Attach the socket to the protocol family list. */
    return Sock6PcbAttach (ps);
}

/** 
 *  @b Description
 *  @n  
 *      The function detaches the SOCKET from the appropriate global family list.
 *
 *  @param[in]  ps
 *      The pointer to the socket which we will detach from the corresponding
 *      list.
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   Non Zero
 */
int Sock6PrDetach (SOCK6 *ps)
{
    /* Should only be TCP, but make sure */
    if( ps->SockProt == SOCKPROT_TCP )
    {
        /* If we've already started the closing process, then this */
        /* is a hard drop - tell TCP to just free it and return. */
        /* Otherwise, TCP will try and tell the peer that we've */
        /* dropped the socket */
        if( ps->StateFlags & SS_CLOSING )
            return TCP6PrDetach((HANDLE)ps, &ps->hTP, 1);
        else
            return TCP6PrDetach((HANDLE)ps, &ps->hTP, 0);
    }

    /* Detach the socket from the global family list. */
    return Sock6PcbDetach(ps);
}

/** 
 *  @b Description
 *  @n  
 *      The function notifies the socket of a problem. Sets the 
 *      appropriate error code on the socket.
 *
 *  @param[in]  ps
 *      The pointer to the socket to which the error needs to
 *      be notified.
 *
 *  @param[in]  Code
 *      Error code indicating the problem.
 *
 *  @retval
 *      None
 */
void Sock6PrCtlError( SOCK6 *ps, uint Code )
{
    if (ps->SockProt == SOCKPROT_TCP)
    {
        TCP6PrCtlError( ps, ps->hTP, Code, 0);
    }
    else if (ps->SockProt == SOCKPROT_UDP)
    {
        /* UDP is easy, just set the socket error */
        if (!ps->ErrorPending)
            ps->ErrorPending = Code;
    }
    return;
}

#endif /* _INCLUDE_IPv6_CODE */

