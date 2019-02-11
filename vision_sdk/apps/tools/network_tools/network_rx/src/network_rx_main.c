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

#include "network_rx_priv.h"


NetworkRx_Obj gNetworkRx_obj;

void ShowUsage()
{
    printf(" \n");
    printf("# \n");
    printf("# network_rx --host_ip <ipaddr> --target_ip <ipaddr> [--port <server port> --usetfdtp --verbose --no_loop --delay <delay in secs> --retry_count <no of retries>] --files <CH0 file> <CH1 file> ... \n");
    printf("# Ex- ../bin/network_rx.exe --host_ip <ipaddr> --target_ip  <ipaddr> --port 29172 --usetfdtp  --files ../test_file.yuv \n");
    printf("# \n");
    printf("# (c) Texas Instruments 2014\n");
    printf("# \n");
    exit(0);
}

int OpenDataFile(NetworkRx_CmdHeader *pHeader)
{
    int chId = pHeader->chNum;


    if(pHeader->chNum >= gNetworkRx_obj.numCh)
    {
        printf("# ERROR: Incorrect Channel number [%s]\n", gNetworkRx_obj.fileName[chId]);
        return -1;
    }

    if(gNetworkRx_obj.fd[chId] == NULL )
    {
        gNetworkRx_obj.frameCount[chId] = 0;
        gNetworkRx_obj.fd[chId] = fopen(gNetworkRx_obj.fileName[chId],  "wb");
        if(gNetworkRx_obj.fd[chId] == NULL)
        {
            printf("# ERROR: Unable to open file [%s]\n", gNetworkRx_obj.fileName[chId]);
            pHeader->dataSize = 0;
            return -1;
        }
    }

    return 0;
}


int WriteBytes(NetworkRx_CmdHeader *pHeader)
{
    int chId = pHeader->chNum;
    int bytesWr;

    bytesWr = fwrite(gNetworkRx_obj.dataBuf, 1, pHeader->dataSize, gNetworkRx_obj.fd[chId]);
    if(bytesWr != pHeader->dataSize)
    {

        /* reached end of file, restart from begining */
        printf("# ERROR: CH%d: File [%s] write failed !!!\n",
            chId,
            gNetworkRx_obj.fileName[chId]);
        fclose(gNetworkRx_obj.fd[chId]);
        gNetworkRx_obj.fd[chId] = NULL;
        gNetworkRx_obj.frameCount[chId] = 0;
        return -1;
    }
    if(gNetworkRx_obj.verbose)
    {
        printf("# INFO: DATA: CH%d: Frame%d: %d bytes\n",
            pHeader->chNum,
            gNetworkRx_obj.frameCount[chId],
            pHeader->dataSize
        );
    }
    gNetworkRx_obj.frameCount[chId]++;
    gNetworkRx_obj.totalDataSize[chId] += pHeader->dataSize;

    if(gNetworkRx_obj.frameCount[chId] &&
        (gNetworkRx_obj.frameCount[chId] % 10)==0
      )
    {
        printf("# INFO: DATA: CH%d: Recevied %d frames, %10.2f MB\n",
            pHeader->chNum,
            gNetworkRx_obj.frameCount[chId],
            gNetworkRx_obj.totalDataSize[chId]/(1024.0*1024)
        );
    }

    return 0;
}

int WriteData(NetworkRx_CmdHeader *pHeader)
{
    int status = 0;

    status = OpenDataFile(pHeader);
    if(status < 0)
    {
        return status;
    }

    status = WriteBytes(pHeader);

    return status;
}

int main(int argc, char *argv[])
{
    int status = 0;
    TFDTP_CreateParams params;

    memset(&gNetworkRx_obj, 0, sizeof(gNetworkRx_obj));

    /* Set Null link Tx server port as receive port of PC */
    gNetworkRx_obj.serverPort = NETWORK_TX_SERVER_PORT;

    ParseCmdLineArgs(argc, argv);

    Init();
    while(1)
    {
        status = ConnectToServer();

        if ( (status==0) && (1U == gNetworkRx_obj.usetfdtp) )
        {
            printf ("# Using TFDTP for Receive \n");
            memset(&params, 0, sizeof(params));

            params.chId = NETWORK_TFDTP_RX_CHANNEL_NUM;
            params.udpPort = NETWORK_TFDTP_RXFILTER_UDP_PORT;
            strcpy(params.destIpAddr, gNetworkRx_obj.dstIpAddr);

            params.direction = DIR_RX;
            params.udpPort = NETWORK_TFDTP_HOST_UDP_PORT;

            params.frameSize = 1920*1080*2; //same size as MAX_BUF_SIZE=(1920*1080*2)
            params.thruput = 500;

            printf("TFDTP: Throughput = %d, frameSize = %d\n", params.thruput, params.frameSize);
            /* Open handle to TFDTP Stack */
            status = Network_tfdtpOpen(&gNetworkRx_obj.sockObj,  &params);
            if(status != 0)
            {
                printf (" TFDTP open failed \n");
                exit(1);
            }
            Network_tfdtpSendParams(&gNetworkRx_obj.sockObj, gNetworkRx_obj.srcIpAddr, gNetworkRx_obj.retryCount);
            OSA_printf("# NETWORK: Sent TFDTP channel params!!!\n");
        }

        if(status==0)
        {
            RecvData();
        }

        CloseConnection();

        printf("# INFO: Closing connection to Server \n");
    }
    DeInit();
    return 0;
}

void Init()
{
    Network_init();

    gNetworkRx_obj.dataBuf = malloc(MAX_BUF_SIZE);
    if(gNetworkRx_obj.dataBuf==NULL)
    {
        printf("# ERROR: Unable to allocate memory for buffer !!! \n");
        exit(0);
    }
}

void DeInit()
{
    Network_deInit();

    free(gNetworkRx_obj.dataBuf);
}

int ReadCmdHeader(NetworkRx_CmdHeader *pHeader)
{
    UInt32 dataSize;
    Int32 status;
    UInt32 ack = TFDTP_TRANSMIT_OK;

    dataSize = sizeof(*pHeader);

    status = Network_read(&gNetworkRx_obj.sockObj, (UInt8*)pHeader, &dataSize);

    if(status!=0)
    {
        status = NETWORK_ERROR;
        ack = TFDTP_TRANSMIT_FAIL;
        printf("# ERROR: Network read for cmd header failed \n");
    }
    else if ( pHeader->header!=NETWORK_TX_HEADER)
    {
        status = NETWORK_INVALID_HEADER;
        ack = TFDTP_TRANSMIT_INVALID;
        printf("# ERROR: Command header not matching\n");

    }
    else if ( pHeader->dataSize > MAX_BUF_SIZE )
    {
        status = NETWORK_INVALID_HEADER;
        ack = TFDTP_TRANSMIT_INVALID;
        printf("# ERROR: Buffer size in command header too big (>MAX_BUF_SIZE)\n");
    }
    if (1U == gNetworkRx_obj.usetfdtp)
    {
        Network_tfdtpSendAck(&gNetworkRx_obj.sockObj, ack);
    }

    return status;
}

void print_tfdtpStats(TFDTP_Obj *pAppObj)
{
    struct tfdtp_stats stats;

    printf("Target Load Info\n");
    /* Send get load command */
    printf("TFDTP Target statistics\n");
    printf("\tFrame Errors                 :  %u\n", stats.errorCnt);
    printf("\tTotal Packets                :  %u\n", stats.packetCount);
    printf("\tIgnored packets              :  %u\n", stats.ignoredPacketCnt);
    printf("\tInvalidPacketSizeError       :  %u\n", stats.invalidPacketSizeError);
    printf("\tOutOfSequenceError           :  %u\n", stats.outOfSequenceError);
    printf("\tBuffer Underflow             :  %u\n", stats.noBuffersAvailable);
    printf("\tInsufficientSizeError        :  %u\n", stats.insufficientSizeError);

}

int ReadData(NetworkRx_CmdHeader *pHeader)
{
    Int32 status = 0;
    UInt32 readDataSize;
    Int32 i,numBuf = pHeader->numBuf;
    UInt8 *buf;
    UInt32 ack;
    Int32 retry;

    if(pHeader->dataSize==0)
    {
        printf("# Network Read ERROR: Read data of size 0 requested, returning\n");
        return 0;
    }

    readDataSize = pHeader->dataSize;

    if (1U == gNetworkRx_obj.usetfdtp)
    {
        buf = gNetworkRx_obj.dataBuf;
        for (i=0; i<numBuf; i++)
        {
            if (gNetworkRx_obj.retryCount > 0)
            {
                retry = gNetworkRx_obj.retryCount;
                do
                {
                    status = Network_tfdtpRead(&gNetworkRx_obj.sockObj, buf, &readDataSize);
                    if (status != 0)
                    {
                        ack = TFDTP_TRANSMIT_FAIL;
                    }
                    else
                    {
                        ack = TFDTP_TRANSMIT_OK;
                    }
                    Network_tfdtpSendAck(&gNetworkRx_obj.sockObj, ack);
                    retry--;
                }
                while((retry >= 0) && (ack != TFDTP_TRANSMIT_OK));
                if (retry < 0)
                {
                    printf("# Network Rx ERROR: TFDTP read failed after retry\n");
                }
            }
            else
            {
                status = Network_tfdtpRead(&gNetworkRx_obj.sockObj, buf, &readDataSize);
            }
            buf +=  pHeader->dataSize;
        }
    }
    else
    {
        status = Network_read(&gNetworkRx_obj.sockObj, gNetworkRx_obj.dataBuf, &readDataSize);
    }

    if(status!=0)
    {
        printf("ERROR : Network read error \n");
#if (1 == STOP_ON_ERROR)
        return NETWORK_ERROR;
#endif
    }

    pHeader->dataSize = readDataSize * pHeader->numBuf;


    return 0;
}

void RecvData()
{
    Int32 status = 0;
    NetworkRx_CmdHeader cmdHeader;
    TFDTP_Obj *pTfdtpObj;

    while(status==0)
    {
        status = ReadCmdHeader(&cmdHeader);

        if(status==0)
        {

            status = ReadData(&cmdHeader);

            if (1U == gNetworkRx_obj.usetfdtp)
            {
                pTfdtpObj = gNetworkRx_obj.sockObj.pTfdtpObj;

                if (status != 0)
                {
                    if(BUFF_PARTIAL == pTfdtpObj->curBufDes.bufState)
                    {
                        gNetworkRx_obj.tfdtpPartialFrameCnt[cmdHeader.chNum]++;
                    }
                    else
                    {
                        gNetworkRx_obj.tfdtpErrorCnt[cmdHeader.chNum]++;
                    }
                }
            }
        }
        else
        {
            printf("# ERROR: Read cmd header failed\n");
        }

        if(status == 0)
        {
            WriteData(&cmdHeader);
        }
    }
}

int ConnectToServer()
{
    int status;

    printf("# Connecting to server %s:%d ...\n", gNetworkRx_obj.dstIpAddr, gNetworkRx_obj.serverPort);
    status = Network_connect(&gNetworkRx_obj.sockObj, gNetworkRx_obj.dstIpAddr, gNetworkRx_obj.serverPort);
    return status;
}

void CloseConnection()
{
    Network_close(&gNetworkRx_obj.sockObj);
}

void ParseCmdLineArgs(int argc, char *argv[])
{
    int i, p;

    gNetworkRx_obj.numCh = 0;
    gNetworkRx_obj.retryCount = -1;

    memset(gNetworkRx_obj.fileName, 0, sizeof(gNetworkRx_obj.fileName));

    for(i=0; i<argc; i++)
    {
        if(strcmp(argv[i], "--target_ip")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            strcpy(gNetworkRx_obj.dstIpAddr, argv[i]);
        }
        else
        if(strcmp(argv[i], "--host_ip")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            strcpy(gNetworkRx_obj.srcIpAddr, argv[i]);
        }
        else
        if(strcmp(argv[i], "--port")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkRx_obj.serverPort = atoi(argv[i]);
        }
        else
        if(strcmp(argv[i], "--usetfdtp")==0)
        {
            gNetworkRx_obj.usetfdtp = 1;
        }
        else
        if(strcmp(argv[i], "--verbose")==0)
        {
            gNetworkRx_obj.verbose = 1;
        }
        else
        if(strcmp(argv[i], "--retry_count")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkRx_obj.retryCount = atoi(argv[i]);
        }
        else
        if(strcmp(argv[i], "--files")==0)
        {
            i++;
            p=0;
            for( ;i<argc;i++)
            {
                strcpy(gNetworkRx_obj.fileName[p], argv[i]);
                p++;
            }
            gNetworkRx_obj.numCh = p;
        }
    }

    if(gNetworkRx_obj.dstIpAddr[0]==0
        ||
       gNetworkRx_obj.numCh==0
        )
    {

        if(gNetworkRx_obj.dstIpAddr[0]==0)
        {
            printf("# ERROR: IP Address of server MUST be specified\n");
        }
        if(gNetworkRx_obj.numCh==0)
        {
            printf("# ERROR: Atleast one output file MUST be specified\n");
        }

        ShowUsage();
        exit(0);
    }

    for(p=0; p<gNetworkRx_obj.numCh; p++)
    {
        gNetworkRx_obj.fd[p] = NULL;
    }

    if(gNetworkRx_obj.retryCount == -1)
    {
        gNetworkRx_obj.retryCount = NETWORK_TFDTP_RETRANSMIT_COUNT;
    }
}
