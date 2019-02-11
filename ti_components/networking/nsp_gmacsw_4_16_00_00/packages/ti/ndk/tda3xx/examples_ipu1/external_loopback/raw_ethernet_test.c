/*
 * raw_ethernet_test.c
 */

/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Timer.h>

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>
#include <ti/ndk/inc/stack/stack.h>

/* Project dependency headers */

/* This module's header */


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/

extern Task_Handle recvTask;


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define PACKET_SIZE         (1514u)
#define PACKET_ETHERTYPE    (0x88B5U)

#define TOTAL_PACKET_CNT    (1024u)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

static SOCKET s = INVALID_SOCKET;

static Semaphore_Handle packetSem;

static uint8_t sendPacket[PACKET_SIZE];


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

void recvTaskFxn(UArg arg0, UArg arg1)
{
    HANDLE pBufHandle = NULL;
    uint8_t *pRecvPacket = NULL;
    int32_t packetCnt = 0;
    int32_t packetVerifiedCnt = 0;
    int32_t packetSize = 0;
    int32_t rxError = 0;

    printf("Begin receive task.\n");

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    while(packetCnt < TOTAL_PACKET_CNT)
    {
        /* Attempt to recv a packet */
        packetSize = recvnc(s, (void **)&pRecvPacket, 0x0, &pBufHandle);
        if (PACKET_SIZE != packetSize)
        {
            if (-1 == packetSize)
            {
                rxError = fdError();
                printf("Packet %d: Raw socket receive failed with some error.\n", packetCnt);

                if (EBADF == rxError)
                {
                    printf("EBADF: The file descriptor (socket) is invalid.\n");
                }
                else if (EINVAL == rxError)
                {
                    printf("EINVAL: Attempt to read (or calling arguments) invalid for this socket.\n");
                }
                else if (ENOTSOCK == rxError)
                {
                    printf("ENOTSOCK: The file descriptor does not reference a socket.\n");
                }
                else if (EWOULDBLOCK == rxError)
                {
                    printf("EWOULDBLOCK: The receive timeout configured on the socket has expired.\n");
                }
                else if (ENXIO == rxError)
                {
                    printf("ENXIO: No egress interface specified for this socket to receive from.\n");
                }
                else
                {
                    printf("Unknown Error = 0x%08X.\n",rxError);
                }
            }
            else
            {
                printf("Packet %d: PacketSize of receive packet equals %d, but not 1500.\n", packetCnt, packetSize);
            }
        }
        else
        {
            /* If packet size is correct, verify the packet payload contents (including ethertype)*/
            if (memcmp((const void *)&sendPacket[12], (const void *)&pRecvPacket[12], packetSize - 12))
            {
                int i= 0;
                uint32_t errorCnt = 0;

                printf("Packet %d: Data did not verify properly.\n",packetCnt);

                for (i=12; i<packetSize; i++)
                {
                    if (pRecvPacket[i] != sendPacket[i])
                    {
                        printf("\tByte %d: Sent 0x%02X, Received 0x%02X\n",i, sendPacket[i], pRecvPacket[i]);
                        errorCnt++;
                    }
                }
                if (errorCnt == 0)
                {
                    printf("ERROR: memcmp failed, but second check passed!?!");
                }
            }
            else
            {
                packetVerifiedCnt++;
            }
            packetCnt++;

            /* Tell send thread that we received the packet */
            Semaphore_post(packetSem);
        }

        /* Tell the stack to free the buffer */
        recvncfree(pBufHandle);
    }

    if (TOTAL_PACKET_CNT == packetVerifiedCnt)
    {
        printf("All packets were received and verified.\n");
    }
    else
    {
        printf("Packet verification failed.\n");
    }

    fdCloseSession (TaskSelf());
}

void sendTaskFxn(UArg arg0, UArg arg1)
{
    int32_t packetCnt = 0;
    int32_t txError = 0;
    int32_t bytesSent = 0;

    uint8_t macAddress[6];

    printf("Begin transmit task.\n");

    /* Allocate the file environment for this task */
    fdOpenSession( TaskSelf() );

    /* Open the raw socket which gets used for both Tx and Rx */
    s = socket(AF_RAWETH, SOCK_RAWETH, PACKET_ETHERTYPE);

    if( s == INVALID_SOCKET )
    {
        printf("Fail socket, %d\n", fdError());
        fdCloseSession (Task_self());
        return;
    }

    /* Set some socket options */
    {
        int ifVal = 1;
        int retVal = 0;

        /* Set socket option to set IF device */
        retVal = setsockopt(s, SOL_SOCKET, SO_IFDEVICE, &ifVal, sizeof(ifVal));
        if (retVal)
        {
            printf("Error in setsockopt() API.\n");
        }

        /*
         * Set max receive size to handle all possible packets that could be received at
         * once from the hardware.
         */
        ifVal = 64*1536;
        retVal = setsockopt(s, SOL_SOCKET, SO_RCVBUF, &ifVal, sizeof(ifVal));
        if (retVal)
        {
            printf("Error in setsockopt() API.\n");
        }
    }

    /* Get the interface MAC address using the NIMU ioctl()*/
    {
        int ret_code;
        uint16_t        dev_index;
        NIMU_IF_REQ     if_req;

        if_req.index = 1;
        if (NIMUIoctl (NIMU_GET_DEVICE_INDEX, &if_req, &dev_index, sizeof(dev_index)) < 0)
        {
            printf ("Error: Incorrect device index specified\n");
            exit(1);
        }

        if_req.name[0] = 0;
        if_req.index   = dev_index;

        /* Get the device MAC Address */
        ret_code = NIMUIoctl (NIMU_GET_DEVICE_MAC, &if_req, &macAddress, sizeof(macAddress));
        if (ret_code < 0)
        {
            printf ("NIMUIOCTL Failed with error code: %d\n",ret_code);
            return;
        }
    }

    /* Create packet semaphore */
    {
        Semaphore_Params semParams;

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        packetSem = Semaphore_create(0, &semParams, NULL);
    }

    /* Start higher priority receive task now that the shared socket is created and set up */
    {
        Task_Params taskParams;
        Task_Params_init(&taskParams);
        taskParams.instance->name = "Raw_Receiver";
        taskParams.stackSize = 0x1000;
        taskParams.priority = 2;
        recvTask = Task_create((Task_FuncPtr)recvTaskFxn, &taskParams,NULL);
    }

    while(packetCnt < TOTAL_PACKET_CNT)
    {
        uint8_t *payload = (uint8_t *) &sendPacket[14];
        int i;

        /* Make this a broadcast packet */
        memset(&sendPacket[0], 0xFFU, 6);

        /* Set the source MAC address */
        memcpy((void *)&sendPacket[6], (void *)macAddress, sizeof(macAddress));

        /* Set the Ethertype */
        *((uint16_t *)&sendPacket[12]) = htons(PACKET_ETHERTYPE);

        /* Fill in payload with random data*/
        for (i = 0; i < (PACKET_SIZE - 14); i++)
        {
            payload[i] = (uint8_t)((int) (255.0*rand()/(RAND_MAX+1.0)));
        }

        /* Tag packet with sequence number */
        *((uint16_t *)payload) = packetCnt;

        bytesSent = send(s, (void *)sendPacket, PACKET_SIZE, 0x0);
        if (-1 == bytesSent)
        {
            txError = fdError();
            printf("Packet %d: Raw socket send failed with some error.\n", packetCnt);

            if (ENOBUFS == txError)
            {
                printf("ENOBUFS: Memory allocation failure while attempting to send data.\n");
            }
            else if (EINVAL == txError)
            {
                printf("EINVAL: The input is invalid.\n");
            }
            else if (ENOTSOCK == txError)
            {
                printf("ENOTSOCK: The file descriptor does not reference a socket.\n");
            }
            else if (ESHUTDOWN == txError)
            {
                printf("ESHUTDOWN: The socket has been shut down for writes.\n");
            }
            else if (ENXIO == txError)
            {
                printf("ENXIO: No egress interface specified for this socket to send out data.\n");
            }
            else if (EMSGSIZE == txError)
            {
                printf("EMSGSIZE: The size of the data being sent exceeds the MTU of the interface.\n");
            }
            else
            {
                printf("Unknown Error = 0x%08X.\n",txError);
            }
        }
        packetCnt++;

        /* Wait for recv thread to indicate reception of this packet looped back */
        Semaphore_pend(packetSem, BIOS_WAIT_FOREVER);
    }

    if (TOTAL_PACKET_CNT == packetCnt)
    {
        printf("All packets were sent.\n");
    }

    fdCloseSession (TaskSelf());
}

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

