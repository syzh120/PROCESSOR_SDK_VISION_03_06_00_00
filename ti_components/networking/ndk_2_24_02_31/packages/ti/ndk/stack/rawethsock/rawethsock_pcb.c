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
 * ======== rawethsockpcb.c ========
 *
 * Object member functions for the SOCKRAWETH object. These 
 * functions include protocol control type access to the socket 
 * object.
 *
 */

#include <stkmain.h>

/**********************************************************************
 *************************** Global Variables *************************
 **********************************************************************/

/** 
 * @brief 
 *  This structure is used to maintain the list of all the
 *  registered raw ethernet socket objects.
 *
 * @details
 */
typedef struct _RAWETHSOCK_PCB
{
    /**
     * @brief       List of Raw eth socket objects.
     */
    SOCKRAWETH*    sockets;
} RAWETHSOCK_PCB;

/* Local copy for management */
RAWETHSOCK_PCB      raweth_pcb;

/**********************************************************************
 ******************** SOCKRAWETH PCB Functions ***********************
 **********************************************************************/

/** 
 *  @b Description
 *  @n  
 *      The function attaches the SOCKET to the appropriate list.
 *
 *  @param[in]  hSock
 *      The pointer to the socket which we will attach to the corresponding
 *      list.
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   Non Zero
 */
int RawEthSockPcbAttach (HANDLE hSock)
{
    SOCKRAWETH *ps, *ptr_head;

    /* Get the pointer to the socket. */
    ps = (SOCKRAWETH *)hSock;

    /* The ethernet type specified is not a valid value 
     * or is a well known ethernet type which cannot be 
     * overriden.
     */
    switch (ps->Protocol)
    {
        case 0:
        case ETHERTYPE_IP:
        case ETHERTYPE_IPv6:
        case ETHERTYPE_VLAN:
        case ETHERTYPE_PPPOECTL:
        case ETHERTYPE_PPPOEDATA:
            return EINVAL;
    }

    /* Validate this socket entry. Check if any other socket
     * entry is already configured with the same properties.
     */
    if (RawEthSockPcbFind(ps->Protocol, ps->hIF))
    {
        /* Socket already exists with the same parameters. */
        return EADDRINUSE;
    }

    /* Add this Raw ethernet socket object to the list. */

	/* Check if the list is empty ? */
	if (raweth_pcb.sockets == NULL)
	{
		/* YES the list is empty. Initialize the links */
		ps->pNext = NULL;
        ps->pPrev = NULL;

		/* Initialize the LIST */
		raweth_pcb.sockets = ps;
	}
    else
    {
	    /* No the list was NOT empty. Add the node to the beginning of list. 
         * Get the current head of the list. 
         */
	    ptr_head = raweth_pcb.sockets;

	    /* Initialize the new head of the list. */
	    ps->pNext  = ptr_head;
        ps->pPrev = NULL;

        /* Update the old head to point to the new head */
        ptr_head->pPrev = ps;

        /* Update the pointer to the head of the list. */
	    raweth_pcb.sockets = ps;
    }
    
    return (0);
}

/** 
 *  @b Description
 *  @n  
 *      The function detaches the SOCKET from the appropriate list.
 *
 *  @param[in]  hSock
 *      The pointer to the socket which we will detach from the 
 *      corresponding list.
 *
 *  @retval
 *      Success -   0
 *  @retval      
 *      Error   -   Non Zero
 */
int RawEthSockPcbDetach( HANDLE hSock )
{
    SOCKRAWETH  *ps, *ptr_head, *ptr_node, *ptr_prev , *ptr_next;

    /* Get the pointer to the socket. */
    ps = (SOCKRAWETH *)hSock;

    /* Remove the entry from the list */
    
    /* Are there any nodes in the list? */
    if (raweth_pcb.sockets == NULL)
		return -1;

    /* Are we removing the head? */
    if (ps == raweth_pcb.sockets)
    {
	    /* Get the head of the list. */
	    ptr_node = raweth_pcb.sockets;

	    /* Move the head to the next element in the list. */
	    ptr_head = ptr_node->pNext;
	    raweth_pcb.sockets = ptr_head;

        /* Did we remove the last element?*/
        if (ptr_head != NULL)
        {
            /* No; in that case update the pointers for the new head. */
            ptr_head->pPrev = NULL;
        }

	    /* Kill the links. */
	    ptr_node->pNext = NULL;
        ptr_node->pPrev = NULL;
	}
    else
    {
        /* OK; we are trying to remove a non head element; so lets get the
         * previous and next pointer of the elements that needs to be removed. */
        ptr_prev = ps->pPrev;
        ptr_next = ps->pNext;

        /*  Kill the Links for element that is being removed. */
        ps->pPrev = NULL;
        ps->pNext = NULL;

        /* Are we removing the last element */
        if (ptr_next == NULL)
        {
            /* The last element points to nothing. */
            ptr_prev->pNext = NULL;
        }
        else
        {
            /* We are trying to remove an element in the middle of the list. */
	        ptr_prev->pNext = ptr_next;
            ptr_next->pPrev = ptr_prev;
        }
    }

	return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function finds a socket matching the criteria given.
 *
 *  @param[in]  Protocol
 *      The "Ethernet Type" / Layer 3 protocol to match.
 *  @param[in]  hIF
 *      The Ethernet device to match.
 *
 *  @retval
 *      Success -   Socket Matching the search criteria.
 *  @retval      
 *      Error   -   No socket matching the criteria is found.
 */
SOCKRAWETH *RawEthSockPcbFind( UINT32  Protocol, HANDLE hIF )
{
    SOCKRAWETH* ps;
    
   /* Traverse through our already open Raw ethernet channels to
    * check if this ethernet type is already in use.
    */
    ps = (SOCKRAWETH *)(raweth_pcb.sockets);
    while (ps != NULL)
    {
        /* Found the matching raw eth entry in our local database? */    
        if (ps->Protocol == Protocol && ps->hIF == hIF)
        {
            /* Found matching entry. Success. Return found entry. */
            return ps;
        }
        
        /* Go to the next element. */
        ps = (SOCKRAWETH *)(ps->pNext);
    }    

    /* If we reached here indicates that we didnt find any
     * socket entry configured with the same ethernet type and the ethernet device. 
     * Return NULL.
     */
    return NULL;
}

/** 
 *  @b Description
 *  @n  
 *      The function initializes the NDK core stack Raw Ethernet
 *      socket protocol control block.
 *
 *      This is for *internal* NDK Stack Usage.
 *      
 *  @param[in]  void
 *
 *  @retval
 *   0      -   Success
 *  @retval
 *   <0     -   Error
 */
int RawEthSockPcbInit (void)
{
    /* Initialize the PCB. */
    mmZeroInit ((void *)&raweth_pcb, sizeof (RAWETHSOCK_PCB));

    return 0;
}

/** 
 *  @b Description
 *  @n  
 *      The function cleans up all the Raw ethernet sockets.
 *
 *      This is for *internal* NDK Stack Usage.
 *
 *  @retval
 *   Not applicable.
 */
void RawEthSockPcbCleanup (void)
{
    SOCKRAWETH*     ps;

    /* Cycle through all the raw ethernet channel objects in the manager
     * and close them out. 
     */
    ps = (SOCKRAWETH *)(raweth_pcb.sockets);
    while (ps != NULL)
    {
        /* Close the socket and free its memory. */
        RawEthSockClose(ps);

        /* Go to the next element. */
        ps = (SOCKRAWETH *)(raweth_pcb.sockets);
    }
    return;
}

