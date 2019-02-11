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
 * ======== rawethsockprot.c ========
 *
 * The file implements the SOCKET_RAWETH Family. 
 *
 */


#include <stkmain.h>

/** 
 *  @b Description
 *  @n  
 *      The function attaches the socket to the appropriate global family list.
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
int RawEthSockPrAttach (SOCKRAWETH *ps)
{
    /* Attach the socket to the protocol family list. */
    return RawEthSockPcbAttach (ps);
}

/** 
 *  @b Description
 *  @n  
 *      The function detaches the socket from the appropriate global family list.
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
int RawEthSockPrDetach (SOCKRAWETH *ps)
{
    /* Detach the socket from the global family list. */
    return RawEthSockPcbDetach(ps);
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
void RawEthSockPrCtlError( SOCKRAWETH *ps, uint Code )
{
    if (!ps->ErrorPending)
        ps->ErrorPending = Code;
    return;
}

