/*
 * Copyright (c) 2012-2015, Texas Instruments Incorporated
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
 * ======== hdlc.c ========
 *
 * Member functions for the HDLC client and server.
 *
 */

#include <stkmain.h>
#include "hdlcif.h"

/*----------------------------------------------- */
/* Static Functions used in callbacks */
static void hdlcInput( PBM_Handle hPkt );
static void hdlcTimer( HANDLE hHDLC );

/*----------------------------------------------- */
/* Shared Functions */
static void hdlcSI( HANDLE hSI, uint Msg, UINT32 Aux, PBM_Handle hPkt );

/*----------------------------------------------- */
/* HDLC Object */

/*----------------------------------------------- */
/* Max count for service list and max name length */
#define HDLC_NAMESIZE          32

/* HDLC Instance Structure */
typedef struct _hdlc_instance {
    uint         Type;                      /* Instance TYPE */
#define HDLC_INST_SERVER        0x2501
#define HDLC_INST_CLIENT        0x2502
    uint         DevSerial;                 /* Serial Device Index */
    HANDLE       hPPP;                      /* PPP Interface */
    uint         Status;                    /* Call status */
    uint         pppFlags;                  /* PPP Flags */
    UINT32       cmap_out;                  /* Sending CMAP */
    UINT32       cmap_in;                   /* Desired Rx CMAP */
    char         Username[HDLC_NAMESIZE];   /* Specified Username (client) */
    char         Password[HDLC_NAMESIZE];   /* Specified Password (client) */
    IPN          IPServer;                  /* Our IP address     (server) */
    IPN          IPMask;                    /* Our IP mask        (server) */
    IPN          IPClient;                  /* Client IP address  (server) */
    } HDLC_INSTANCE;

/*---------------------------------------------------------------------- */
/* USER FUNCTIONS */
/* The following functions must be callable from outside the kernel. */
/* They use llEnter()/llExit(). */
/*---------------------------------------------------------------------- */

/*-------------------------------------------------------------- */
/* hdlcNew()   USER FUNCTION */
/* Open HDLC in Client mode */
/*-------------------------------------------------------------- */
HANDLE hdlcNew( uint DevSerial, uint pppFlags, UINT32 ourcmap,
                char *Username, char *Password )
{
    HDLC_INSTANCE *pi = 0;

    /* Enter kernel mode */
    llEnter();

    /* Validate arguments */
    if( !DevSerial || !Username || !Password )
        goto ExitNew;

    /* If size of Username or Password > HDLC_NAMESIZE, */
    /* then abort */
    if( strlen(Username) >= HDLC_NAMESIZE
                         || strlen(Password) >= HDLC_NAMESIZE )
        goto ExitNew;

    /* Allocate space for instance */
    if( !(pi = mmAlloc(sizeof(HDLC_INSTANCE))) )
    {
        NotifyLowResource();
        goto ExitNew;
    }

    /* Initialize Instance */
    mmZeroInit( pi, sizeof(HDLC_INSTANCE) );
    pi->Type            = HDLC_INST_CLIENT;
    pi->DevSerial       = DevSerial;
    pi->pppFlags        = pppFlags;
    pi->cmap_out        = 0xFFFFFFFF;
    pi->cmap_in         = ourcmap;
    strcpy( pi->Username, Username );
    strcpy( pi->Password, Password );

    /* Open the serial device */
    if( !llSerialOpenHDLC( pi->DevSerial, (HANDLE)pi, hdlcTimer, hdlcInput ) )
        goto FatalError;

    /* Make sure the character escape map is correct */
    llSerialHDLCPeerMap( pi->DevSerial, pi->cmap_out );

    /* Start the PPP session now */
    pi->hPPP = pppNew( pi, pi->pppFlags, 1500, 0, 0, 0,
                       pi->Username, pi->Password, pi->cmap_in,
                       (void(*)(HANDLE,uint,UINT32,PBM_Pkt*))&hdlcSI );
    if( !pi->hPPP )
    {
        llSerialCloseHDLC( pi->DevSerial );
FatalError:
        pi->Type = 0;
        mmFree(pi);
        pi = 0;
    }

ExitNew:
    /* Exit kernel mode */
    llExit();

    return( (HANDLE)pi );
}

/*-------------------------------------------------------------- */
/* hdlcFree()  USER FUNCTIION */
/* Close HDLC Client */
/*-------------------------------------------------------------- */
void hdlcFree( HANDLE hHDLC )
{
    HDLC_INSTANCE *pi = (HDLC_INSTANCE *)hHDLC;

    /* Enter kernel mode */
    llEnter();

    if( pi && (pi->Type==HDLC_INST_CLIENT || pi->Type==HDLC_INST_SERVER)  )
    {
        /* This message will close PPP */
        hdlcSI( hHDLC, SI_MSG_CALLSTATUS, SI_CSTATUS_DISCONNECT, 0 );

        /* Zap the type */
        pi->Type = 0;

        /* Close the serial driver */
        llSerialCloseHDLC( pi->DevSerial );

        /* Free the instance */
        mmFree( pi );
    }

    /* Exit kernel mode */
    llExit();
}

/*-------------------------------------------------------------- */
/* hdlcGetStatus()     USER FUNCTION */
/* Get the status of the HDLC Client */
/*-------------------------------------------------------------- */
uint hdlcGetStatus( HANDLE hHDLC )
{
    HDLC_INSTANCE *pi = (HDLC_INSTANCE *)hHDLC;
    uint status       = 0;

    /* Enter kernel mode */
    llEnter();

    /* Get Status */
    if( pi && (pi->Type==HDLC_INST_CLIENT || pi->Type==HDLC_INST_SERVER)  )
        status = pi->Status;

    /* Exit kernel mode */
    llExit();

    return( status );
}

/*-------------------------------------------------------------- */
/* hdlcsNew()  USER FUNCTION */
/* Open HDLC Server */
/*-------------------------------------------------------------- */
HANDLE hdlcsNew( uint DevSerial, uint pppFlags, UINT32 ourcmap,
                 IPN IPServer, IPN IPMask, IPN IPClient )
{
    HDLC_INSTANCE *pi = 0;

    /* Enter kernel mode */
    llEnter();

    /* Validate arguments */
    if( !DevSerial || !IPClient || !IPServer || !IPMask )
        goto ExitSNew;

    /* Allocate space for instance */
    if( !(pi = mmAlloc(sizeof(HDLC_INSTANCE))) )
    {
        NotifyLowResource();
        goto ExitSNew;
    }

    /* Initialize Instance */
    mmZeroInit( pi, sizeof(HDLC_INSTANCE) );
    pi->Type            = HDLC_INST_SERVER;
    pi->DevSerial       = DevSerial;
    pi->pppFlags        = pppFlags;
    pi->cmap_out        = 0xFFFFFFFF;
    pi->cmap_in         = ourcmap;
    pi->IPServer        = IPServer;
    pi->IPMask          = IPMask;
    pi->IPClient        = IPClient;

    /* Open the serial device */
    if( !llSerialOpenHDLC( pi->DevSerial, (HANDLE)pi, hdlcTimer, hdlcInput ) )
        goto FatalErrorS;

    /* Make sure the character escape map is correct */
    llSerialHDLCPeerMap( pi->DevSerial, pi->cmap_out );

    /* Start the PPP session now */
    pi->hPPP = pppNew( pi, pi->pppFlags, 1500,
                       pi->IPServer, pi->IPMask, pi->IPClient,
                       0, 0, pi->cmap_in,
                       (void(*)(HANDLE,uint,UINT32,PBM_Pkt*))&hdlcSI );

    if( !pi->hPPP )
    {
        llSerialCloseHDLC( pi->DevSerial );
FatalErrorS:
        pi->Type = 0;
        mmFree(pi);
        pi = 0;
    }

ExitSNew:
    /* Exit kernel mode */
    llExit();

    return( (HANDLE)pi );
}

/*---------------------------------------------------------------------- */
/* STACK FUNCTIONS */
/* The following functions are Kernel Mode stack functions. */
/*---------------------------------------------------------------------- */

/*-------------------------------------------------------------- */
/* hdlcTimer() */
/* Dispatches timer ticks to the stack's PPP module */
/*-------------------------------------------------------------- */
static void hdlcTimer( HANDLE hHDLC )
{
    HDLC_INSTANCE *pi = (HDLC_INSTANCE *)hHDLC;

    if( pi && (pi->Type==HDLC_INST_CLIENT ||
        pi->Type==HDLC_INST_SERVER) && pi->hPPP )
        pppTimer( pi->hPPP );
}

/*-------------------------------------------------------------- */
/* hdlcInput() */
/* Dispatches packets to the stack's PPP module */
/*-------------------------------------------------------------- */
void hdlcInput( PBM_Handle hPkt )
{
    HDLC_INSTANCE *pi = 0;
    uint          Size;

    /* If we were given a packet, our handle is the RX interface */
    if( hPkt )
        pi = (HDLC_INSTANCE *)PBM_getIFRx(hPkt);

    /* Verify what we were given */
    if( !pi || (pi->Type!=HDLC_INST_CLIENT && pi->Type!=HDLC_INST_SERVER)  )
    {
        DbgPrintf(DBG_ERROR,"hdlcInput: Invalid Handle");
        goto ReturnPacket;
    }

    /* Do a sanity check on the size */
    Size = PBM_getValidLen(hPkt);
    if( Size < 7 )
    {
        DbgPrintf(DBG_ERROR,"hdlcInput: Bad Packet");
        goto ReturnPacket;
    }

    /* Packet comes in as FF03(2), PROT(2), DATA(n), CHECKSUM(2) */
    /* We need to remove the FF03 and two byte checksum */
    Size -= 4;
    PBM_setValidLen(hPkt,Size);
    PBM_setDataOffset(hPkt,PBM_getDataOffset(hPkt)+2);

    /* When closing, when can get here with a null PPP handle. (This */
    /* is because PPP must switch out of kernel mode to clean up any */
    /* installed routes.) Thus we make sure to only give the packet to */
    /* PPP when the PPP handle is valid. */
    if( pi->hPPP )
    {
        pppInput( pi->hPPP, hPkt );
        return;
    }

ReturnPacket:
    if( hPkt )
         PBM_free(hPkt);
    return;
}

/*-------------------------------------------------------------------- */
/* SI Control Function */
/*-------------------------------------------------------------------- */
void hdlcSI( HANDLE hSI, uint Msg, UINT32 Aux, PBM_Handle hPkt )
{
    HDLC_INSTANCE       *pi = (HDLC_INSTANCE *)hSI;
    HANDLE              hTmp;
    uint                Offset,Size;
    UINT8               *pBuf;

    switch( Msg )
    {
    case SI_MSG_CALLSTATUS:
        /* Update Connection Status */
        pi->Status = (uint)Aux;
        if( Aux >= SI_CSTATUS_DISCONNECT )
        {
            /* Close PPP - we clear the handle to make sure we */
            /* only call pppFree() once. (We may get multiple */
            /* disconnect messages - one from each protocol.) */
            if( pi->hPPP )
            {
                hTmp = pi->hPPP;
                pi->hPPP = 0;
                pppFree( hTmp );
            }
        }
        break;

    case SI_MSG_PEERCMAP:
        /* Update Out CMAP for Transmit */
        pi->cmap_out = Aux;
        llSerialHDLCPeerMap( pi->DevSerial, Aux );
        break;

    case SI_MSG_SENDPACKET:
        if( !hPkt )
        {
            DbgPrintf(DBG_ERROR,"hdlcSI: No packet");
            break;
        }

        Offset = PBM_getDataOffset(hPkt);
        Size = PBM_getValidLen(hPkt);

        /* Make sure packet is valid, room for protocol, room for checksum */
        if( (Offset<4) || ((Offset+Size+2)>PBM_getBufferLen(hPkt)) )
        {
            DbgPrintf(DBG_ERROR,"hdlcSI: Bad packet");
            PBM_free( hPkt );
            break;
        }

        /* Add in 2 byte Protocol and 2 byte header. Also add in size for */
        /* 2 byte checksum. Note that the outgoing checksum is corrected */
        /* (calculated) by the serial driver. */
        Offset -= 4;
        Size += 6;
        PBM_setDataOffset(hPkt, Offset );
        PBM_setValidLen(hPkt, Size );
        pBuf = PBM_getDataBuffer(hPkt)+Offset;
        *pBuf++ = 0xFF;
        *pBuf++ = 0x03;
        *pBuf++ = (UINT8)(Aux/256);
        *pBuf++ = (UINT8)(Aux%256);

        /* Send the buffer to the serial driver */
        /* If LCP and the command is <= 7, then make sure we */
        /* use the default CMAP */
        if( Aux == 0xc021 && *pBuf <= 7 )
        {
            llSerialHDLCPeerMap( pi->DevSerial, 0xFFFFFFFF );
            llSerialSendPkt( pi->DevSerial, hPkt );
            llSerialHDLCPeerMap( pi->DevSerial, pi->cmap_out );
        }
        else
            llSerialSendPkt( pi->DevSerial, hPkt );

        break;
    }
}



