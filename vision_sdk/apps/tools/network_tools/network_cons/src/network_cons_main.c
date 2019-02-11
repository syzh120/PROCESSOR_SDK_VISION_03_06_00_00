/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include "stdio.h"
#include "network_cons_priv.h"

NetworkCons_Obj gNetworkCons_obj;


void NetworkConsRx_main()
{
    int status;
    int isConnected = 0;

    while(1)
    {
        if(!isConnected)
        {
            printf("### RX: Connecting to server %s:%d ...\n",
                        gNetworkCons_obj.ipAddr, gNetworkCons_obj.rxPort);

            status = Network_connect(
                    &gNetworkCons_obj.sockObjRx,
                    gNetworkCons_obj.ipAddr,
                    gNetworkCons_obj.rxPort
                    );
            if(status < 0)
            {
                SleepThread(2000);
            }
            else
            {
                isConnected = 1;
            }
        }
        if(isConnected)
        {
            status = Network_readString(&gNetworkCons_obj.sockObjRx,
                        (UInt8 *)gNetworkCons_obj.rxData,
                        NETWORK_CONS_RX_BUF_SIZE
                        );
            if(status < 0)
            {
                isConnected = 0;
                printf("ERROR: Connection closed!\n");
                Network_close(&gNetworkCons_obj.sockObjRx);
            }
            else
            {
                printf((char*)gNetworkCons_obj.rxData);
            }
        }
    }
}

void NetworkConsTx_main()
{
    int status;
    int isConnected = 0;
    char ch[2];

    while(1)
    {
        if(!isConnected)
        {
            printf("### TX: Connecting to server %s:%d ...\n",
                        gNetworkCons_obj.ipAddr, gNetworkCons_obj.txPort);

            status = Network_connect(
                    &gNetworkCons_obj.sockObjTx,
                    gNetworkCons_obj.ipAddr,
                    gNetworkCons_obj.txPort
                    );
            if(status < 0)
            {
                SleepThread(2000);
            }
            else
            {
                isConnected = 1;
            }
        }
        if(isConnected)
        {
            ch[0] = getchar();
            ch[1] = 0;

            status = Network_write(&gNetworkCons_obj.sockObjTx,
                        (UInt8 *)ch,
                        1
                        );
            if(status < 0)
            {
                isConnected = 0;
                Network_close(&gNetworkCons_obj.sockObjTx);
            }
        }
    }
}

void ShowUsage()
{
    printf(" \n");
    printf("# \n");
    printf("# network_cons --ipaddr <ipaddr> [--port <tx port> <rx port>]\n");
    printf("# \n");
    printf("# (c) Texas Instruments 2016\n");
    printf("# \n");
    exit(0);
}

void ParseCmdLineArgs(int argc, char *argv[])
{
    int i;

    gNetworkCons_obj.txPort = NETWORK_CONS_TX_PORT;
    gNetworkCons_obj.rxPort = NETWORK_CONS_RX_PORT;

    for(i=0; i<argc; i++)
    {
        if(strcmp(argv[i], "--ipaddr")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            strcpy(gNetworkCons_obj.ipAddr, argv[i]);
        }
        else
        if(strcmp(argv[i], "--port")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkCons_obj.txPort = atoi(argv[i]);
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkCons_obj.rxPort = atoi(argv[i]);
        }
    }

    if(gNetworkCons_obj.ipAddr[0]==0)
    {
        if(gNetworkCons_obj.ipAddr[0]==0)
        {
            printf("# ERROR: IP Address of server MUST be specified\n");
        }
        ShowUsage();
    }
}

int main(int argc, char *argv[])
{
    ParseCmdLineArgs(argc, argv);

    Network_init();

    RunThreads();

    Network_deInit();

    return 0;
}
