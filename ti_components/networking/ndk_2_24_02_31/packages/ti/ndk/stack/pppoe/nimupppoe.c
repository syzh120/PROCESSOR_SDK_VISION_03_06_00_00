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
 * ======== nimupppoe.c ========
 *
 *  The file contains function which implements the PPPoE protocol using 
 *  the network interface objects over the Network Interface Management
 *  Architecture (NIMU). The file is based on the non NIMU version but
 *  has been modified extensivly. It was decided best to have two seperate
 *  copies which will lead to better clarity.
 *
 *
 */

#include <stkmain.h>
#include "pppoe.h"

#ifdef _INCLUDE_PPPOE_CODE

static UINT8 MacBCast[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

/* CLIENT */
static void pppoeTimer( uint Msg );
static void SendClientMsg( UINT8 Code, UINT16 SessionId, UINT8 *pMac );
static void pppoeInputC( PBM_Pkt *pPkt );
static PPPOE_CLIENT *ppc = 0;

/* SERVER */
static void pppoesTimer( uint Msg );
static void SendServerMsg( UINT8 Code, UINT16 SessionId, UINT8 *pMac,
                           uint HostData, UINT8 *pHostData );
static void pppoeInputS( PBM_Pkt *pPkt );
static PPPOE_SERVER *pps = 0;

static int header_size;
static int trailer_size;

/*----------------------------------------------- */
/* PPPOE Client State Machine States */
#define PPPOE_SM_IDLE           0
#define PPPOE_SM_INITIATING     1
#define PPPOE_SM_REQUESTING     2
#define PPPOE_SM_CONFIRMED      3

/*----------------------------------------------- */
/* PPPOE State Machine Control Function */
static void pppoeCtrlMsg( PPPOE_CLIENT *ppc, int Msg );

/*----------------------------------------------- */
/* Messages for the Control function */
#define PPPOE_MSG_QUERY     1  /* Query available services */
#define PPPOE_MSG_OPEN      2  /* Open Service Session */
#define PPPOE_MSG_CLOSE     3  /* Close Service Session */
#define PPPOE_MSG_TIMETICK  4  /* Time Tick (about 1 sec) (ctrl function only) */


/*---------------------------------------------------------------------- */
/* USER FUNCTIONS */
/* The following functions must be callable from outside the kernel. */
/* They use llEnter()/llExit(). */
/*---------------------------------------------------------------------- */

/*-------------------------------------------------------------- */
/* pppoeNew()   USER FUNCTION */
/* Open PPPOE Client */
/*-------------------------------------------------------------- */
HANDLE pppoeNew( HANDLE hEth, uint pppFlags,
                 INT8 *Username, INT8 *Password )
{
    NETIF_DEVICE* ptr_device;
        
    /* Only one instance allowed */
    if( ppc != 0 )
        return(0);

    /* Enter kernel mode */
    llEnter();

    /* Validate arguments */
    if( !hEth || !Username || !Password )
        goto ExitNew;

    /* If size of UserName or Password > PPPOE_NAMESIZE, */
    /* then abort */
    if( strlen(Username) >= PPPOE_NAMESIZE
                         || strlen(Password) >= PPPOE_NAMESIZE )
        goto ExitNew;

    /* Allocate space for instance */
    if( !(ppc = mmAlloc(sizeof(PPPOE_CLIENT))) )
    {
        NotifyLowResource();
        goto ExitNew;
    }

    /* Initialize type */
    ppc->Type = HTYPE_PPPOE_CLIENT;

    /* Save master settings */
    ppc->hTimer         = TimerNew( &pppoeTimer, 2, 0 );
    ppc->pppFlags       = pppFlags;
    strcpy( ppc->Username, Username );
    strcpy( ppc->Password, Password );

    ppc->ppi.hParent    = (HANDLE)ppc;
    ppc->ppi.iType      = PPPOE_INST_CLIENT;
    ppc->ppi.hEther     = hEth;
    ppc->ppi.SessionId  = 0;
    ppc->ppi.hPPP       = 0;

    /* Get the network interface object */
    ptr_device = (NETIF_DEVICE *)hEth;

    /* Increment the reference counter for the source interface. */
    ptr_device->RefCount++;

    /* Copy the MAC Address. */
    mmCopy (ppc->ppi.MacAddr, ptr_device->mac_address, 6);

    /* Get the current NIMU Padding: We should store these and when PPP is bought down reset
     * it to the original values. */
    NIMUGetRsvdSizeInfo (&header_size, &trailer_size);

    /* Change the padding to reflect the additional header required for the PPP + PPPoE Header */
    header_size = header_size + PPPOEHDR_SIZE + 2;

    /* Set the NIMU Padding. */
    NIMUSetRsvdSizeInfo (header_size, trailer_size);

    /* Send a PPPOE QUERY to see if there are any services */
    pppoeCtrlMsg( ppc, PPPOE_MSG_QUERY );

ExitNew:
    /* Exit kernel mode */
    llExit();

    return( (HANDLE)ppc );
}

/*-------------------------------------------------------------- */
/* pppoeFree()  USER FUNCTIION */
/* Close PPPOE Client */
/*-------------------------------------------------------------- */
void pppoeFree( HANDLE hPPPOE )
{
    NETIF_DEVICE* ptr_device;

    /* Enter kernel mode */
    llEnter();

    if( ppc && ppc == hPPPOE )
    {
        pppoeSI( &(ppc->ppi), SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT, 0 );
        if( ppc->hTimer )
            TimerFree( ppc->hTimer );

        /* Get the network interface object and decrement the reference count. */
        ptr_device = (NETIF_DEVICE *)ppc->ppi.hEther;
        ptr_device->RefCount--;

        /* Before we close we reset the NIMU Padding back to the original values. */
        NIMUSetRsvdSizeInfo (header_size, trailer_size);

        /* Clean memory. */
        mmFree( ppc );
        ppc = 0;
    }

    /* Exit kernel mode */
    llExit();
}

/*-------------------------------------------------------------- */
/* pppoeGetStatus()     USER FUNCTION */
/* Get the status of the PPPOE Client */
/*-------------------------------------------------------------- */
uint pppoeGetStatus( HANDLE hPPPOE )
{
    uint Status = 0;

    /* Enter kernel mode */
    llEnter();

    if( ppc && ppc == hPPPOE )
        Status = ppc->ppi.Status;

    /* Exit kernel mode */
    llExit();

    return( Status );
}

/*-------------------------------------------------------------- */
/* pppoesNew()  USER FUNCTION */
/* Open PPPOE Server */
/*-------------------------------------------------------------- */
HANDLE pppoesNew( HANDLE hEth, uint pppFlags, uint SessionMax,
                  IPN IPServer, IPN IPMask, IPN IPClientBase,
                  INT8 *ServerName, INT8 *ServiceName )
{
    uint          i;
    NETIF_DEVICE* ptr_device;

    /* Only one server instance allowed */
    if( pps != 0 )
        return(0);

    /* Enter kernel mode */
    llEnter();

    /* Validate arguments */
    if( !hEth || !SessionMax || !IPClientBase || !ServerName || !ServiceName )
        goto ExitSNew;

    /* If size of ServerName or ServiceName > PPPOE_NAMESIZE, */
    /* then abort */
    if( strlen(ServerName) >= PPPOE_NAMESIZE
                         || strlen(ServiceName) >= PPPOE_NAMESIZE )
        goto ExitSNew;

    /* Allocate space for server */
    i = sizeof(PPPOE_SERVER);
    if( SessionMax > 1 )
        i += sizeof(PPPOE_INST)*(SessionMax-1);

    if( !(pps = mmAlloc( i )) )
    {
        NotifyLowResource();
        goto ExitSNew;
    }

    /* Initialize type */
    pps->Type = HTYPE_PPPOE_SERVER;

    /* Save master settings */
    pps->hEther       = hEth;
    pps->hTimer       = TimerNew( &pppoesTimer, 2, 0 );
    pps->pppFlags     = pppFlags;
    pps->SessionMax   = SessionMax;
    pps->IPClientBase = IPClientBase;
    pps->IPServer     = IPServer;
    pps->IPMask       = IPMask;
    strcpy( pps->ServerName, ServerName );
    strcpy( pps->ServiceName, ServiceName );

    /* Get the network interface object */
    ptr_device = (NETIF_DEVICE *)hEth;

    /* Copy the MAC Address. */
    mmCopy (pps->MacAddr, ptr_device->mac_address, 6);

    /* Get the current NIMU Padding: We should store these and when PPP is bought down reset
     * it to the original values. */
    NIMUGetRsvdSizeInfo (&header_size, &trailer_size);

    /* Change the padding to reflect the additional header required for the PPPoE Header */
    header_size = header_size + PPPOEHDR_SIZE + 2;

    /* Set the NIMU Padding. */
    NIMUSetRsvdSizeInfo (header_size, trailer_size);

    /* Init sessions */
    for( i=0; i<SessionMax; i++ )
    {
        mmZeroInit( &(pps->ppi[i]), sizeof(PPPOE_INST) );
        pps->ppi[i].hParent    = (HANDLE)pps;
        pps->ppi[i].iType      = PPPOE_INST_SERVER;
        pps->ppi[i].hEther     = pps->hEther;
        pps->ppi[i].SessionId  = i+1;
        mmCopy(pps->ppi[i].MacAddr, pps->MacAddr, 6);
    }

ExitSNew:
    /* Exit kernel mode */
    llExit();

    return( (HANDLE)pps );
}

/*-------------------------------------------------------------- */
/* pppoesFree() */
/* Close PPPOE Server */
/*-------------------------------------------------------------- */
void pppoesFree( HANDLE hPPPOES )
{
    uint i;

    /* Enter kernel mode */
    llEnter();

    if( pps && pps == hPPPOES )
    {
        for( i=0; i<pps->SessionMax; i++ )
            if( pps->ppi[i].hPPP )
                pppoeSI( &(pps->ppi[i]), SI_MSG_CALLSTATUS,
                         SI_CSTATUS_DISCONNECT, 0 );
        if( pps->hTimer )
            TimerFree( pps->hTimer );
        mmFree( pps );
        pps = 0;
    }

    /* We need to restore the NIMU Padding back to its original value. */
    NIMUSetRsvdSizeInfo (header_size, trailer_size);

    /* Exit kernel mode */
    llExit();
}

/*---------------------------------------------------------------------- */
/* STACK FUNCTIONS */
/* The following functions are normal stack functions. */
/*---------------------------------------------------------------------- */

/*********************************************************************
 * FUNCTION NAME : pppoeSI
 *********************************************************************
 * DESCRIPTION   :
 *  The function is the registered call back routine from PPP which
 *  is used to send messages on the LINK or to terminate the state
 *  machine.
 *
 * NOTES         :
 *  This function is based on the non-NIMU version above but has been
 *  modified. The non NIMU version used to hardcode the ethernet 
 *  header inside this routine. Now with the advent of VLAN this cannot
 *  be done because the PPP might have been instantiated over a VLAN
 *  connection. We need to account for this and changes were done to 
 *  use the 'add_header' API for this. 
 *********************************************************************/
void pppoeSI( HANDLE hSI, uint Msg, UINT32 Aux, PBM_Pkt *pPkt )
{
    PPPOE_INST*     ppi = (PPPOE_INST *)hSI;
    uint            Payload;
    PPPOEHDR*       pHdr;
    HANDLE          hTmp;
    NETIF_DEVICE*   ptr_src_device;
    NETIF_DEVICE*   ptr_device;

    switch( Msg )
    {
    case SI_MSG_CALLSTATUS:
        ppi->Status = (uint)Aux;
        if( Aux >= SI_CSTATUS_DISCONNECT )
        {
            /* Close PPP */
            if( ppi->hPPP )
            {
                hTmp = ppi->hPPP;
                ppi->hPPP = 0;
                pppFree( hTmp );
            }

            /* Terminate the PPPOE session */
            if( ppi->iType == PPPOE_INST_SERVER )
            {
                /* Server Shutdown */
                SendServerMsg( PPPOE_CODE_TERMINATE,
                               ppi->SessionId, ppi->PeerMac, 0, 0 );
            }
            else
            {
                /* Client Shutdown */
                if( ppi->SessionId )
                    SendClientMsg( PPPOE_CODE_TERMINATE,
                                   ppi->SessionId, ppi->PeerMac );
                pppoeCtrlMsg( (PPPOE_CLIENT *)ppi->hParent, PPPOE_MSG_CLOSE );
                
                /* The session/channel have been cleaned up, free the PPPoE client too */
                if( ppc && (ppc == ppi->hParent) )
                {
                    if( ppc->hTimer )
                        TimerFree( ppc->hTimer );

                    /* Get the network interface object and decrement the reference count. */
                    ptr_device = (NETIF_DEVICE *)ppc->ppi.hEther;
                    ptr_device->RefCount--;

                    /* Before we close we reset the NIMU Padding back to the original values. */
                    NIMUSetRsvdSizeInfo (header_size, trailer_size);

                    /* Clean memory. */
                    mmFree( ppc );
                    ppc = 0;                
                }
            }
        }
        break;

    case SI_MSG_PEERCMAP:
        DbgPrintf( DBG_WARN, "PPPOE: Unexpected Peer CMAP" );
        break;

    case SI_MSG_SENDPACKET:
        /* Make sure packet is valid and there is enough space in the header 
         * to add the necessary PPPoE Header. */
        if( !pPkt || (pPkt->DataOffset < (PPPOEHDR_SIZE+2)) )
        {
            DbgPrintf(DBG_ERROR,"pppoeSI: Bad packet");
            PBM_free( pPkt );
            break;
        }

        /* If there is no session we dont send the packet; clean and return. */ 
        if( !ppi->SessionId )
        {
            PBM_free( pPkt );
            break;
        }

        /* Determine the length of the payload. */ 
        Payload = pPkt->ValidLen + 2;

        /* Move back the data pointer to add only the PPP and PPPoE Header. */
        pPkt->DataOffset -= (PPPOEHDR_SIZE + 2);
        pPkt->ValidLen   += (PPPOEHDR_SIZE + 2);

        /* Get the pointer to the PPPoE header */
        pHdr = (PPPOEHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

        /* Initialize the PPPoE Header. */
        pHdr->VerType   = 0x11;
        pHdr->Code      = 0;
        pHdr->SessionId = HNC16(ppi->SessionId);
        pHdr->Length    = HNC16(Payload);

        /* Add Protocol */
        *(pHdr->Data)   = (UINT8)(Aux/256);
        *(pHdr->Data+1) = (UINT8)(Aux%256);

        /* Clear any held route */
        PBM_setRoute( pPkt, 0 );

        /* Get the source device on which the PPPoE has been started */
        ptr_src_device = (NETIF_DEVICE *)ppi->hEther;

        /* Add the layer2 header. */
        if (NIMUAddHeader (ptr_src_device, (HANDLE) pPkt, ppi->PeerMac, NULL, ETHERTYPE_PPPOE_DATA) == 0)
        {
            /* Send the packet through the NIMU */
            NIMUSendPacket (ppi->hEther, pPkt);
        }
        else
        {
            /* There was an error and the header could not be added. Clean the packet
             * memory */
            PBM_free (pPkt);
        }

        break;
    }
}

/*-------------------------------------------------------------- */
/* pppoeInput() */
/* Generic packet Rx function for PPPOE */
/*-------------------------------------------------------------- */
void pppoeInput( PBM_Pkt *pPkt )
{
    if( pps && pps->hEther == pPkt->hIFRx )
        pppoeInputS( pPkt );
    else if( ppc && ppc->ppi.hEther == pPkt->hIFRx )
        pppoeInputC( pPkt );
    else
        PBM_free( pPkt );
}

/*---------------------------------------------------------------------- */
/*---------------------------------------------------------------------- */
/* PPPOE CLIENT FUNCTIONS */
/*---------------------------------------------------------------------- */
/*---------------------------------------------------------------------- */

/*-------------------------------------------------------------- */
/* pppoeTimer() */
/* Dispatches time ticks to PPP clients */
/*-------------------------------------------------------------- */
static void pppoeTimer( uint Msg )
{
    (void)Msg;

    if( ppc )
    {
        pppoeCtrlMsg( ppc, PPPOE_MSG_TIMETICK );
        if( ppc->ppi.hPPP )
            pppTimer( ppc->ppi.hPPP );
    }
}

/*-------------------------------------------------------------------- */
/* pppoeCtrlMsg */
/* This function handles the control side of a PPPOE client. */
/*-------------------------------------------------------------------- */
static void pppoeCtrlMsg( PPPOE_CLIENT *ppc, int Msg )
{
    if( !Msg || !ppc )
        return;

    switch( Msg )
    {
    case PPPOE_MSG_QUERY:       /* Query available services */
        ppc->State            = PPPOE_SM_INITIATING;
        ppc->ppi.Status       = SI_CSTATUS_WAITING;
        ppc->ppi.SessionId    = 0;
        ppc->Timeout          = 2;
        ppc->Retry            = 2;
        SendClientMsg( PPPOE_CODE_INITIATION, 0, MacBCast );
        break;

    case PPPOE_MSG_OPEN:        /* Open Service Session */
        ppc->State            = PPPOE_SM_REQUESTING;
        ppc->ppi.SessionId    = 0;
        ppc->Timeout          = 2;
        ppc->Retry            = 2;
        SendClientMsg( PPPOE_CODE_REQUEST, 0, ppc->ppi.PeerMac );
        break;

    case PPPOE_MSG_CLOSE:       /* Close Service Session */
        ppc->State            = PPPOE_SM_IDLE;
        ppc->ppi.SessionId    = 0;
        ppc->Timeout          = 0;
        break;

    case PPPOE_MSG_TIMETICK:    /* Time Increment (about 1 sec) */
        /* If we have nothing timing out, then exit quickly */
        if( !ppc->Timeout )
            break;
        /* See if somethiong timed out this call. */
        if( !--ppc->Timeout )
        {
            /* A timeout has occurred. */

            /* See if we should retry the last operation */
            if( !ppc->Retry )
            {
                /* Retries have expired */
                /* Send a failure notification */
                switch( ppc->State )
                {
                case PPPOE_SM_INITIATING:
                    /* Error in QUERY */
                    pppoeSI( &(ppc->ppi),
                             SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT, 0 );
                    break;
                case PPPOE_SM_REQUESTING:
                    /* Error in OPEN */
                    pppoeSI( &(ppc->ppi),
                             SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT, 0 );
                    break;
                default:
                    ppc->State = PPPOE_SM_IDLE;
                    break;
                }
            }

            /* Retry the operation */
            ppc->Retry--;
            switch( ppc->State )
            {
            case PPPOE_SM_INITIATING:
                ppc->Timeout = 2;
                SendClientMsg( PPPOE_CODE_INITIATION, 0, MacBCast );
                break;
            case PPPOE_SM_REQUESTING:
                ppc->Timeout = 2;
                SendClientMsg( PPPOE_CODE_REQUEST, 0, ppc->ppi.PeerMac );
                break;
            default:
                ppc->State = PPPOE_SM_IDLE;
                break;
            }
        }
        break;
    }
}

/*********************************************************************
 * FUNCTION NAME : SendClientMsg
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to send PPPoE control messages. 
 *
 * NOTES         :
 *  This function is based on the non-NIMU version above but has been
 *  modified. The non NIMU version used to hardcode the ethernet 
 *  header inside this routine. Now with the advent of VLAN this cannot
 *  be done because the PPP might have been instantiated over a VLAN
 *  connection. We need to account for this and changes were done to 
 *  use the 'add_header' API for this. 
 *********************************************************************/
static void SendClientMsg( UINT8 Code, UINT16 SessionId, UINT8 *pMac )
{
    PPPOEHDR*       pHdr;
    int             TagLength,i;
    UINT8*          pTagData;
    PBM_Pkt*        pPkt;
    NETIF_DEVICE*   ptr_src_device;

    /* Allocate memory for the PPPoE packet. */ 
    pPkt = NIMUCreatePacket (256);
    if(pPkt == NULL)
        return;

    /* Make sure there is space to add the PPPOE Header. */
    if (pPkt->DataOffset < PPPOEHDR_SIZE)
    {
        DbgPrintf(DBG_ERROR,"SendClientMsg: No space to add PPPoE Header.");
        PBM_free (pPkt);
        return;
    }

    /* Move back the offset to add the PPPoE Header. */
    pPkt->DataOffset -= PPPOEHDR_SIZE;

    /* Get the pointer to the PPPoE Header. */
    pHdr = (PPPOEHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Initialize the PPPo Header. */ 
    pHdr->VerType = 0x11;
    pHdr->Code    = Code;

    /* The session Id is used only for PPPOE_CODE_TERMINATE and CONFIRM */
    if( Code == PPPOE_CODE_TERMINATE || Code == PPPOE_CODE_CONFIRM )
        pHdr->SessionId = HNC16(SessionId);
    else
        pHdr->SessionId = 0;

    /* Add the necessary tags to the packet. */
    TagLength = 0;
    pTagData = pHdr->Data;

    /* Tags are dependent on message type */
    if( Code == PPPOE_CODE_INITIATION )
    {
        /* SNAME */
        *pTagData++ = PPPOE_TAG_SNAME/256;
        *pTagData++ = PPPOE_TAG_SNAME&255;
        *pTagData++ = 0;
        *pTagData++ = 0;
        TagLength += 4;
    }
    else if( Code == PPPOE_CODE_REQUEST )
    {
        /* SNAME */
        *pTagData++ = PPPOE_TAG_SNAME/256;
        *pTagData++ = PPPOE_TAG_SNAME&255;
        i = strlen( ppc->ServiceName );
        *pTagData++ = (UINT8)(i/256);
        *pTagData++ = (UINT8)(i&255);
        if( i )
            memcpy( pTagData, ppc->ServiceName, i );
        pTagData += i;
        TagLength += 4+i;

        /* ACCOOKIE */
        if( (i = ppc->CookieSize) != 0 )
        {
            *pTagData++ = PPPOE_TAG_ACCOOKIE/256;
            *pTagData++ = PPPOE_TAG_ACCOOKIE&255;
            *pTagData++ = (UINT8)(i/256);
            *pTagData++ = (UINT8)(i&255);
            memcpy( pTagData, ppc->Cookie, i );
            pTagData += i;
            TagLength += 4+i;
        }
    }

    /* Set TagLength in packet */
    pHdr->Length = HNC16(TagLength);

    /* Set the packet valid length */ 
    pPkt->ValidLen = PPPOEHDR_SIZE + TagLength;

    /* Get the source device on which the PPPoE has been started */
    ptr_src_device = (NETIF_DEVICE *)ppc->ppi.hEther;

    /* Add the appropriate L2 header on the packet; but use the network
     * interface object to do so. */
    if (NIMUAddHeader (ptr_src_device, (HANDLE) pPkt, pMac, NULL, ETHERTYPE_PPPOE_CTRL) == 0)
    {
        /* Send the packet through the NIMU */
        NIMUSendPacket (ppc->ppi.hEther, pPkt);
    }
    else
    {
        /* There was an error and the header could not be added. Clean the packet
         * memory */
        PBM_free (pPkt);
    }
    return;
}

/*-------------------------------------------------------------- */
/* pppoeInputC() */
/* Packet Rx function for PPPOE Client */
/*-------------------------------------------------------------- */
static void pppoeInputC( PBM_Pkt *pPkt )
{
    ETHHDR*     pEth;
    PPPOEHDR*   pHdr;
    UINT8*      pTagData;
    int         Tag,Len;
    int         TagLength;
    UINT16      SessionId;                  /* SessionId from pkt */
    INT8*       pServiceName;               /* Service string in this pkt */
    UINT8*      pCookie;                    /* Cookie in this pkt */
    int         ServiceNameSize = -1;       /* Length of service strings */
    int         CookieSize      = 0;        /* Length of cookie */
    NETIF_DEVICE* ptr_src_device;

    /* Sanity Check for packet */
    /* Note size of L2 can not be greater than 802.2 SNAP header */
    if( !pPkt || pPkt->L2HdrLen > 22 )
    {
        DbgPrintf(DBG_ERROR,"pppoeInputC: Bad Packet");
        goto RXEXIT;
    }

    /* Get a pointer to the PPPoE header */
    pHdr = (PPPOEHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get a pointer to the original Ethernet header */
    /* (we use L2HdrLen as set by EtherRxPacket) */
    pEth = (ETHHDR *)(pPkt->pDataBuffer + pPkt->DataOffset - pPkt->L2HdrLen);

    /* Get the session id from the packet */
    SessionId = HNC16(pHdr->SessionId);

    /* Any non-zero session must be valid */
    if( ppc->ppi.SessionId )
    {
        if( SessionId != ppc->ppi.SessionId )
            goto RXEXIT;
    }

    /* Setup to read tags */
    pTagData  = pHdr->Data;
    TagLength = HNC16(pHdr->Length);

    /* Make sure Tag Length is reasonable */
    if( TagLength > 1494 )
        goto RXEXIT;

    if( pPkt->EtherType == ETHERTYPE_PPPOE_DATA )
    {
        /* Rx PPP Session Packet */
        if( TagLength>0 && ppc->ppi.SessionId && ppc->ppi.hPPP )
        {
            pPkt->DataOffset += PPPOEHDR_SIZE;
            pPkt->ValidLen    = TagLength;
            pppInput( ppc->ppi.hPPP, pPkt );
            return;
        }
        goto RXEXIT;
    }

    /* Read Option tags */
    while( TagLength > 0 )
    {
        Tag =  *pTagData++ * 256;
        Tag += *pTagData++;
        Len =  *pTagData++ * 256;
        Len += *pTagData++;

        switch( Tag )
        {
        case PPPOE_TAG_EOL:
            /* EOL Tag */
            /* Setup variables to fall out of "while" loop. */
            TagLength = 4;
            Len       = 0;
            break;

        case PPPOE_TAG_SNAME:
            /* Service Name Tag */
            /* If the name isn't too long, and we have room, record the */
            /* first service name. */
            if( Len<PPPOE_NAMESIZE && ServiceNameSize<0 )
            {
                pServiceName    = (INT8 *)pTagData;
                ServiceNameSize = Len;
            }
            break;

        case PPPOE_TAG_ACCOOKIE:
            /* Cookie Tag */
            /* If the cookie isn't too long, record it */
            if( Len && Len<PPPOE_NAMESIZE )
            {
                pCookie    = pTagData;
                CookieSize = Len;
            }
            break;

        default:
            break;
        }

        pTagData  += Len;
        TagLength -= Len + 4;
    }

    /* Depending on what state we're in, we are looking for a particular */
    /* PPPOE code. */
    switch( ppc->State )
    {
    case PPPOE_SM_IDLE:
        break;

    /* During a service query... */
    case PPPOE_SM_INITIATING:
        /* Look for an OFFER */
        if( pHdr->Code != PPPOE_CODE_OFFER )
            break;

        /* Check for service */
        if( ServiceNameSize >= 0 )
        {
            /* Copy Service Name */
            if( ServiceNameSize > 0 )
                mmCopy( ppc->ServiceName, pServiceName, ServiceNameSize );
            ppc->ServiceName[ServiceNameSize] = 0;

            /* Copy cookie */
            if( CookieSize )
                memcpy( ppc->Cookie, pCookie, CookieSize );
            ppc->CookieSize = CookieSize;

            /* Copy server MAC */
            mmCopy( ppc->ppi.PeerMac, pEth->SrcMac, 6 );
        }

        /* Open the service */
        pppoeCtrlMsg( ppc, PPPOE_MSG_OPEN );
        break;

    /* Opening a session... */
    case PPPOE_SM_REQUESTING:
        /* Look for a CONFIRM */
        if( pHdr->Code != PPPOE_CODE_CONFIRM )
            break;

        /* If the SessionId is NULL, we have an error */
        if( !SessionId )
            break;

        /* Save our session Id */
        ppc->ppi.SessionId = SessionId;

        /* Before we create the PPP Connection; we compute the MRU for the PPP Connection.
         * Thus the MRU for a PPP Device is computed as follows:-
         *  MTU (Source Interface) - sizeof(PPPoE Header) - sizeof (PPP Header) 
         * i.e. 
         *  MTU (Source Interface) - 8 */
        ptr_src_device = (NETIF_DEVICE *)ppc->ppi.hEther;

        /* Open the PPP device */
        ppc->ppi.hPPP = pppNew( &(ppc->ppi), ppc->pppFlags, (ptr_src_device->mtu-8), 0, 0, 0,
                                ppc->Username, ppc->Password, 0, &pppoeSI );
        if( !ppc->ppi.hPPP )
            break;

        /* Notify the status function */
        ppc->State  = PPPOE_SM_CONFIRMED;
        break;

    /* During an established session... */
    case PPPOE_SM_CONFIRMED:
        /* Look for a TERMINATE */
        if( pHdr->Code != PPPOE_CODE_TERMINATE )
            break;

        /* The session ID must be ours */
        if( SessionId != ppc->ppi.SessionId )
            break;

        /* Close the session */
        pppoeSI( &(ppc->ppi), SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT, 0 );
        break;
    }

RXEXIT:
    /* hPkt Must be Free'd */
    if( pPkt )
        PBM_free( pPkt );
}

/*---------------------------------------------------------------------- */
/*---------------------------------------------------------------------- */
/* PPPOE SERVER */
/*---------------------------------------------------------------------- */
/*---------------------------------------------------------------------- */


/*-------------------------------------------------------------- */
/* pppoesTimer() */
/* Dispatches time ticks to PPP clients */
/*-------------------------------------------------------------- */
static void pppoesTimer( uint Msg )
{
    uint i;

    (void)Msg;

    /* Indicate timer tick to all open sessions */
    if( pps )
        for( i=0; i<pps->SessionMax; i++ )
            if( pps->ppi[i].hPPP )
                pppTimer( pps->ppi[i].hPPP );
}

/*********************************************************************
 * FUNCTION NAME : SendServerMsg
 *********************************************************************
 * DESCRIPTION   :
 *  The function is used to send PPPoE server messages. 
 *
 * NOTES         :
 *  This function is based on the non-NIMU version above but has been
 *  modified. The non NIMU version used to hardcode the ethernet 
 *  header inside this routine. Now with the advent of VLAN this cannot
 *  be done because the PPP might have been instantiated over a VLAN
 *  connection. We need to account for this and changes were done to 
 *  use the 'add_header' API for this. 
 *********************************************************************/
static void SendServerMsg( UINT8 Code, UINT16 SessionId, UINT8 *pMac,
                           uint HostData, UINT8 *pHostData )
{
    PPPOEHDR*   pHdr;
    int         TagLength,i;
    UINT8*      pTagData;
    PBM_Pkt*    pPkt;
    NETIF_DEVICE* ptr_src_device;

    /* Allocate memory for the packet. */ 
    pPkt = NIMUCreatePacket(512);
    if (pPkt == NULL)
        return;

    /* Make sure there is space to add the PPPOE Header. */
    if (pPkt->DataOffset < PPPOEHDR_SIZE)
    {
        DbgPrintf(DBG_ERROR,"SendServerMsg: No space to add PPPoE Header.");
        PBM_free (pPkt);
        return;
    }

    /* Make space to add the PPPoE Header. */
    pPkt->DataOffset = pPkt->DataOffset - PPPOEHDR_SIZE;

    /* Get the pointer to the PPPoE Header. */
    pHdr = (PPPOEHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Initialize the PPPoE header. */
    pHdr->VerType = 0x11;
    pHdr->Code    = Code;

    /* The session Id is used only for PPPOE_CODE_TERMINATE and CONFIRM */
    if( Code == PPPOE_CODE_TERMINATE || Code == PPPOE_CODE_CONFIRM )
        pHdr->SessionId = HNC16(SessionId);
    else
        pHdr->SessionId = 0;

    /* Add Tags */
    TagLength = 0;
    pTagData = pHdr->Data;

    /* Tags are dependent on message type */
    if( Code == PPPOE_CODE_OFFER || Code == PPPOE_CODE_CONFIRM )
    {
        /* SNAME */
        *pTagData++ = PPPOE_TAG_SNAME/256;
        *pTagData++ = PPPOE_TAG_SNAME&255;
        i = strlen( pps->ServiceName );
        *pTagData++ = (UINT8)(i/256);
        *pTagData++ = (UINT8)(i&255);
        if( i )
            mmCopy( pTagData, pps->ServiceName, i );
        pTagData += i;
        TagLength += 4+i;
    }

    if( Code == PPPOE_CODE_OFFER )
    {
        /* ACNAME */
        *pTagData++ = PPPOE_TAG_ACNAME/256;
        *pTagData++ = PPPOE_TAG_ACNAME&255;
        i = strlen( pps->ServerName );
        *pTagData++ = (UINT8)(i/256);
        *pTagData++ = (UINT8)(i&255);
        if( i )
            mmCopy( pTagData, pps->ServerName, i );
        pTagData += i;
        TagLength += 4+i;
    }

    if( HostData )
    {
        /* HOSTUNIQUE */
        *pTagData++ = PPPOE_TAG_HOSTUNIQUE/256;
        *pTagData++ = PPPOE_TAG_HOSTUNIQUE&255;
        *pTagData++ = (UINT8)(HostData/256);
        *pTagData++ = (UINT8)(HostData&255);
        mmCopy( pTagData, pHostData, HostData );
        pTagData += HostData;
        TagLength += 4+HostData;
    }

    /* Set TagLength in packet */
    pHdr->Length = HNC16(TagLength);

    /* Set the length of the packet to account for the PPPoE header and tags which have been added. */ 
    pPkt->ValidLen = PPPOEHDR_SIZE + TagLength;

    /* Get the source device on which the PPPoE Server has been started */
    ptr_src_device = (NETIF_DEVICE *)pps->hEther;

    /* Add the appropriate L2 header on the packet; but use the network
     * interface object to do so. */
    if (NIMUAddHeader (ptr_src_device, (HANDLE) pPkt, pMac, pps->MacAddr, ETHERTYPE_PPPOE_CTRL) == 0)
    {
        /* Send the packet through the NIMU */
        NIMUSendPacket (pps->hEther, pPkt);
    }
    else
    {
        /* There was an error and the header could not be added. Clean the packet
         * memory */
        PBM_free (pPkt);
    }
    return;
}

/*-------------------------------------------------------------- */
/* pppoeInputS() */
/* Packet Rx function for PPPOE Server */
/*-------------------------------------------------------------- */
static void pppoeInputS( PBM_Pkt *pPkt )
{
    PPPOE_INST*     ppi = 0;
    uint            i;
    ETHHDR*         pEth;
    PPPOEHDR*       pHdr;
    UINT8*          pTagData;
    int             Tag,Len;
    int             TagLength;
    UINT16          SessionId;            /* SessionId from pkt */
    INT8*           pServiceName;         /* Service string in this pkt */
    int             ServiceNameSize = -1; /* Length of service strings */
    IPN             IPClient;             /* Client IP address */
    uint            HostData=0;
    UINT8*          pHostData;
    NETIF_DEVICE*   ptr_src_device;

    /* Sanity Check for packet */
    /* Note size of L2 can not be greater than 802.2 SNAP header */
    if( !pPkt || pPkt->L2HdrLen > 22 )
    {
        DbgPrintf(DBG_ERROR,"pppoeInputC: Bad Packet");
        goto RXEXIT;
    }

    /* Get a pointer to the PPPoE header */
    pHdr = (PPPOEHDR *)(pPkt->pDataBuffer + pPkt->DataOffset);

    /* Get a pointer to the original Ethernet header */
    /* (we use AUX1 as set by EtherRxPacket) */
    pEth = (ETHHDR *)(pPkt->pDataBuffer + pPkt->DataOffset - pPkt->L2HdrLen);

    /* Get the session id from the packet */
    SessionId = HNC16(pHdr->SessionId);

    /* Get a pointer to the server session if SessionId != 0 */
    /* Any non-zero session must be valid */
    if( SessionId )
    {
        if( SessionId > pps->SessionMax )
            goto RXEXIT;
        ppi = &(pps->ppi[SessionId-1]);
        if( !ppi->hPPP )
            goto RXEXIT;
    }

    /* Setup to read tags */
    pTagData  = pHdr->Data;
    TagLength = HNC16(pHdr->Length);

    /* Make sure Tag Length is reasonable */
    if( TagLength > 1494 )
        goto RXEXIT;

    if( pPkt->EtherType == ETHERTYPE_PPPOE_DATA )
    {
        /* Rx PPP Session Packet - SessionId must be non-zero */
        /* The hPPP handle has already been validated for */
        /* non-zero SessionId values. */
        if( TagLength>0 && SessionId )
        {
            pPkt->DataOffset += PPPOEHDR_SIZE;
            pPkt->ValidLen    = TagLength;
            pppInput( ppi->hPPP, pPkt );
            return;
        }
        goto RXEXIT;
    }

    /* Read Option tags */
    while( TagLength > 0 )
    {
        Tag =  *pTagData++ * 256;
        Tag += *pTagData++;
        Len =  *pTagData++ * 256;
        Len += *pTagData++;

        switch( Tag )
        {
        case PPPOE_TAG_EOL:
            /* EOL Tag */
            /* Setup variables to fall out of "while" loop. */
            TagLength = 4;
            Len       = 0;
            break;

        case PPPOE_TAG_SNAME:
            /* Service Name Tag */
            /* If the name isn't too long, and we have room, record this */
            /* service name. */
            if( Len<PPPOE_NAMESIZE && ServiceNameSize<0 )
            {
                pServiceName    = (INT8 *)pTagData;
                ServiceNameSize = Len;
            }
            break;

        case PPPOE_TAG_HOSTUNIQUE:
            if( Len<=32 )
            {
                HostData = Len;
                pHostData = pTagData;
            }
            break;

        default:
            break;
        }

        pTagData  += Len;
        TagLength -= Len + 4;
    }

    /* Depending on what state we're in, we are looking for a particular */
    /* PPPOE code. */
    switch( pHdr->Code )
    {
    case PPPOE_CODE_INITIATION:
        /* Sender is asking for an offer */
        /* Send the offer */
        SendServerMsg( PPPOE_CODE_OFFER, 0, pEth->SrcMac, HostData, pHostData );
        break;

    case PPPOE_CODE_OFFER:
        break;

    case PPPOE_CODE_REQUEST:
        /* Sender is asking for a session */

        /* Verify the sender is requesting our serivce */
        if( ServiceNameSize > 0 )
        {
            if( (int)strlen( pps->ServiceName ) != ServiceNameSize )
                break;
            if( strncmp( pps->ServiceName, pServiceName, ServiceNameSize ) )
                break;
        }

        /* Open a new session */
        for( i=0; i<pps->SessionMax; i++ )
        {
            ppi = &(pps->ppi[i]);
            if( !ppi->hPPP )
                break;
        }

        /* If no sessions available, ignore request */
        if( i == pps->SessionMax )
            break;

        /* Get the client IP address */
        IPClient = HNC32(pps->IPClientBase) + i;
        IPClient = HNC32(IPClient);

        /* Record the Mac address of our client */
        mmCopy( ppi->PeerMac, pEth->SrcMac, 6 );

        /* Send the confirmation */
        SendServerMsg( PPPOE_CODE_CONFIRM, ppi->SessionId, ppi->PeerMac, HostData, pHostData );

        /* Before we create the PPP Connection; we compute the MRU for the PPP.
         * Thus the MRU for a PPP Device is computed as follows:-
         *  MTU (Source Interface) - sizeof(PPPoE Header) - sizeof (PPP Header) 
         * i.e. 
         *  MTU (Source Interface) - 8 */
        ptr_src_device = (NETIF_DEVICE *)pps->hEther;

        /* Open PPP - if this call fails, then the ID slot is not */
        /* allocated. However, we already send the confirmation. Thus, */
        /* we need to send a termination. This is not perfect, but clients */
        /* should get the idea. */
        ppi->hPPP = pppNew( ppi, pps->pppFlags, (ptr_src_device->mtu-8),
                            pps->IPServer, pps->IPMask, IPClient,
                            0, 0, 0, &pppoeSI );
        if( !ppi->hPPP )
            SendServerMsg( PPPOE_CODE_TERMINATE, ppi->SessionId, ppi->PeerMac, 0, 0 );

        break;

    case PPPOE_CODE_CONFIRM:
        break;

    case PPPOE_CODE_TERMINATE:
        /* Send the confirmation */
        if( ppi )
            pppoeSI( ppi, SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT, 0 );
        break;
    }

RXEXIT:
    /* hPkt Must be Free'd */
    if( pPkt )
        PBM_free( pPkt );
}


#endif /* _INCLUDE_PPPOE_CODE   */


