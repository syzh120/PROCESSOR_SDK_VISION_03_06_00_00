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
 * ======== llpktstb.c ========
 *
 * STUB Packet Driver for Serial Applications
 *
 */

#include <stkmain.h>

/*-------------------------------------------------------------------- */
/* PUBLIC FUNCTIONS USED BY NETCTRL */
/*-------------------------------------------------------------------- */

/*-------------------------------------------------------------------- */
/* _llPacketInit() */
/* Opens the packet driver environment and enumerates devices */
/*-------------------------------------------------------------------- */
uint _llPacketInit(STKEVENT_Handle hEvent)
{
    (void)hEvent;
    return(0);
}

/*-------------------------------------------------------------------- */
/* _llPacketShutdown() */
/* Called to shutdown packet driver environment */
/*-------------------------------------------------------------------- */
void _llPacketShutdown()
{
}

/*-------------------------------------------------------------------- */
/* _llPacketServiceCheck() */
/* Called to check for packet activity */
/*-------------------------------------------------------------------- */
void _llPacketServiceCheck( uint fTimerTick )
{
    (void)fTimerTick;
}

/*-------------------------------------------------------------------- */
/* PUBLIC FUNCTIONS USED BY THE STACK */
/*-------------------------------------------------------------------- */

/*-------------------------------------------------------------------- */
/* llPacketOpen() */
/* Opens the packet driver, and request packets of our desired type. */
/*-------------------------------------------------------------------- */
uint llPacketOpen( uint dev, HANDLE hEther )
{
    (void)dev;
    (void)hEther;
    return(0);
}

/*-------------------------------------------------------------------- */
/* PacketClose() */
/* Called to shutdown packet driver. */
/*-------------------------------------------------------------------- */
void llPacketClose( uint dev )
{
    (void)dev;
}

/*-------------------------------------------------------------------- */
/* llPacketSend() */
/* Called to send data to a device. */
/*-------------------------------------------------------------------- */
void llPacketSend( uint dev, PBM_Handle hPkt )
{
    (void)dev;
    PBM_free( hPkt );
}

/*-------------------------------------------------------------------- */
/* llPacketGetMacAddr() */
/* Called to the MAC address of the specified device. */
/*-------------------------------------------------------------------- */
void llPacketGetMacAddr( uint dev, UINT8 *pbData )
{
    (void)dev;
    (void)pbData;
}

/*-------------------------------------------------------------------- */
/* llPacketGetMCastMax() */
/* Called to the maxumim multicast addresses that the device can hold. */
/*-------------------------------------------------------------------- */
uint llPacketGetMCastMax( uint dev )
{
    (void)dev;
    return( 0 );
}

/*-------------------------------------------------------------------- */
/* llPacketSetRxFilter() */
/* Called to set the Rx Filter mode of the device. The legal modes */
/* are defined in ETHER.H */
/*-------------------------------------------------------------------- */
void llPacketSetRxFilter( uint dev, uint Filter )
{
    (void)dev;
    (void)Filter;
}

/*-------------------------------------------------------------------- */
/* llPacketSetMCast() */
/* Called to set the Multicast list for the device. */
/*-------------------------------------------------------------------- */
void llPacketSetMCast( uint dev, uint addrcnt, UINT8 *bAddr )
{
    (void)dev;
    (void)addrcnt;
    (void)bAddr;
}

/*-------------------------------------------------------------------- */
/* llPacketGetMCast() */
/* Called to get the Multicast list for the device. */
/*-------------------------------------------------------------------- */
uint llPacketGetMCast( uint dev, uint max, UINT8 *bAddr )
{
    (void)dev;
    (void)max;
    (void)bAddr;
    return(0);
}

/*-------------------------------------------------------------------- */
/* llPacketService() */
/* Called to service packet activity. */
/*-------------------------------------------------------------------- */
void llPacketService()
{
}

/*-------------------------------------------------------------------- */
/* llPacketIoctl() */
/* Execute device specific IOCTL command. */
/*-------------------------------------------------------------------- */
/* ARGSUSED */
uint llPacketIoctl( uint dev, uint cmd, void *arg)
{
    return(1);
}

