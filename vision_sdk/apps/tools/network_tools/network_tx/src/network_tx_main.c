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

#include "network_tx_priv.h"

NetworkTx_Obj gNetworkTx_obj;



void ShowUsage()
{
    printf(" \n");
    printf("# \n");
    printf("# network_tx --host_ip <ipaddr> --target_ip <ipaddr> [--port <server port> --usetfdtp --verbose --no_loop --delay <delay in secs> --retry_count <no of retries>] --files <CH0 file> <CH1 file> ... \n");
    printf("# Ex- ../bin/network_tx.exe --target_ip <ipaddr> --host_ip  <ipaddr> --port 6000 --usetfdtp  --files ../test_file.yuv \n");
    printf("# \n");
    printf("# (c) Texas Instruments 2014\n");
    printf("# \n");
    exit(0);
}

int OpenDataFile(NetworkRx_CmdHeader *pHeader)
{
    int chId = pHeader->chNum;

    if(gNetworkTx_obj.fd[chId] == NULL )
    {
        gNetworkTx_obj.frameCount[chId] = 0;
        gNetworkTx_obj.fd[chId] = fopen(gNetworkTx_obj.fileName[chId],  "rb");
        if(gNetworkTx_obj.fd[chId] == NULL)
        {
            printf("# ERROR: Unable to open file [%s]\n", gNetworkTx_obj.fileName[chId]);
            pHeader->dataSize = 0;
            return -1;
        }
    }
    /*
    TODO - open file only at the begining
    else
    {
        printf("# FILE Open: File descriptor not null, already opened file\n");
    }
    */

    return 0;
}

int ReadBytes(NetworkRx_CmdHeader *pHeader)
{
    int chId = pHeader->chNum;
    int bytesRead;

read_again:
    bytesRead = fread(gNetworkTx_obj.dataBuf, 1, pHeader->dataSize, gNetworkTx_obj.fd[chId]);
    if(bytesRead != pHeader->dataSize)
    {

        /* reached end of file, restart from begining */
        if(gNetworkTx_obj.verbose)
        {
            printf("# INFO: DATA: CH%d: Frames %d: Reached end of file [%s] !!!\n",
                chId,
                gNetworkTx_obj.frameCount[chId],
                gNetworkTx_obj.fileName[chId]);
        }
        if(gNetworkTx_obj.noLoop)
        {
            exit(0);
        }

        fseek(gNetworkTx_obj.fd[chId], 0, SEEK_SET);
        gNetworkTx_obj.frameCount[chId] = 0;
        goto read_again;
    }

    if(gNetworkTx_obj.verbose)
    {
        printf("# INFO: DATA: CH%d: Frame%d: %d bytes\n",
            pHeader->chNum,
            gNetworkTx_obj.frameCount[chId],
            pHeader->dataSize
        );
    }
    gNetworkTx_obj.frameCount[chId]++;

    return 0;
}

#define FOUND_NONE      (0)
#define FOUND_FF        (1)
#define FOUND_FF_D8     (2)
#define FOUND_FF_D9     (3)


int ReadJpeg(NetworkRx_CmdHeader *pHeader)
{
    int chId = pHeader->chNum;
    int bytesRead, i;
    unsigned char dataByte;
    int state, state1;

    state = FOUND_NONE;
    state1 = FOUND_NONE;
    i = 0;

    while(state!=FOUND_FF_D9)
    {
read_again:
        bytesRead = fread(&dataByte, 1, 1, gNetworkTx_obj.fd[chId]);
        if(bytesRead != 1)
        {
            /* reached end of file, restart from begining */
            if(gNetworkTx_obj.verbose)
            {
                printf("# INFO: JPEG: CH%d: Frames %d: Reached end of file [%s] !!!\n",
                    chId,
                    gNetworkTx_obj.frameCount[chId],
                    gNetworkTx_obj.fileName[chId]);
            }
            if(gNetworkTx_obj.noLoop)
            {
                exit(0);
            }

            fseek(gNetworkTx_obj.fd[chId], 0, SEEK_SET);
            gNetworkTx_obj.frameCount[chId] = 0;

            state = FOUND_NONE;
            state1 = FOUND_NONE;
            i = 0;
            goto read_again;
        }

        if(state==FOUND_NONE)
        {
            if(dataByte==0xFFu)
            {
                state = FOUND_FF;
            }
        }
        else
        if(state==FOUND_FF)
        {
            if(dataByte==0xD8u)
            {
                state = FOUND_FF_D8;
                i=0;
                gNetworkTx_obj.dataBuf[i++] = 0xFF;
                gNetworkTx_obj.dataBuf[i++] = 0xD8;
            }
            else
            if(dataByte==0xFFu)
            {
                state = FOUND_FF;
            }
            else
            {
                state = FOUND_NONE;
            }
        }
        else
        if(state==FOUND_FF_D8)
        {
            gNetworkTx_obj.dataBuf[i++] = dataByte;

            if(dataByte==0xFF)
            {
                state1 = FOUND_FF;
            }
            else
            if(dataByte==0xD9)
            {
                if(state1 == FOUND_FF)
                    state = FOUND_FF_D9;
            }
            else
            {
                state1 = FOUND_NONE;
            }
        }
    }
    pHeader->dataSize = i;
    if(gNetworkTx_obj.verbose)
    {
        printf("# INFO: JPEG: CH%d: Frame%d: %d bytes\n",
            pHeader->chNum,
            gNetworkTx_obj.frameCount[chId],
            pHeader->dataSize
           );
    }
    gNetworkTx_obj.frameCount[chId]++;

    return 0;
}

int ReadData(NetworkRx_CmdHeader *pHeader)
{
    int status = 0;

    status = OpenDataFile(pHeader);
    if(status < 0)
        return status;

    if(pHeader->payloadType==NETWORK_RX_TYPE_BITSTREAM_MJPEG)
    {
        ReadJpeg(pHeader);
    }
    else
    {
        ReadBytes(pHeader);
    }

    return status;
}

int main(int argc, char *argv[])
{
    int status = 0;
    TFDTP_CreateParams params;

    memset(&gNetworkTx_obj, 0, sizeof(gNetworkTx_obj));

    /* Set Null source links Rx server port as trasnmit port of PC */
    gNetworkTx_obj.serverPort = NETWORK_RX_SERVER_PORT;

    gNetworkTx_obj.thruput    = TFDTP_DEFAULT_RX_THRUPUT;

    ParseCmdLineArgs(argc, argv);

    Init();

    while(1)
    {
#if (0 == TFDTP_TX_STREAMING_MODE)
        status = ConnectToServer();
#endif
        if ( (status==0) && (1U == gNetworkTx_obj.usetfdtp) )
        {
            printf ("# Using TFDTP for Transmit \n");
            memset(&params, 0, sizeof(params));

            params.chId = NETWORK_TFDTP_TX_CHANNEL_NUM;
            params.udpPort = NETWORK_TFDTP_RXFILTER_UDP_PORT;
            params.thruput = gNetworkTx_obj.thruput;
            strcpy(params.destIpAddr, gNetworkTx_obj.dstIpAddr);

            params.direction = DIR_TX;
#if (1 == TFDTP_TX_STREAMING_MODE)
            printf (" TFDTP: Using Tx streaming mode for TFDTP_rx link \n");
            #if (1 == SYSTEM_DF_YUV420SP_UV)
                printf (" TFDTP: Data format for input stream SYSTEM_DF_YUV420SP_UV \n");
                params.frameSize = (TFDTP_CH_MAX_FRAME_WIDTH * TFDTP_CH_MAX_FRAME_HEIGHT) + ((TFDTP_CH_MAX_FRAME_WIDTH * TFDTP_CH_MAX_FRAME_HEIGHT) / 2U);
            #elif  (1 == SYSTEM_DF_YUV422I_YUYV)
                printf (" TFDTP: Data format for input stream SYSTEM_DF_YUV422I_YUYV \n");
                params.frameSize = (TFDTP_CH_MAX_FRAME_WIDTH * TFDTP_CH_MAX_FRAME_HEIGHT) * 2;
            #endif
#else
            params.frameSize = MAX_BUF_SIZE;
            if (gNetworkTx_obj.thruput == 0)
            {
                /*
                 * For linux thruput should be set otherwise it pumps data at max possible
                 * rate causing frame drop at Null Source
                 */
                params.thruput = 320;
            }
#endif
            /* Open handle to TFDTP Stack */
            status = Network_tfdtpOpen(&gNetworkTx_obj.sockObj,  &params);
            if(status != 0)
            {
                printf ("ERROR: TFDTP open failed, exiting... \n");
                exit(1);
            }
#if (0 == TFDTP_TX_STREAMING_MODE)
            Network_tfdtpSendParams(&gNetworkTx_obj.sockObj, gNetworkTx_obj.srcIpAddr, gNetworkTx_obj.retryCount);
            OSA_printf("# NETWORK: Sent TFDTP channel params!!!\n");
#endif
        }

        if(status==0)
        {
            SendData();
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

    gNetworkTx_obj.dataBuf = malloc(MAX_BUF_SIZE);
    if(gNetworkTx_obj.dataBuf==NULL)
    {
        printf("# ERROR: Unable to allocate memory for buffer !!! \n");
        exit(0);
    }
}

void DeInit()
{
    Network_deInit();

    free(gNetworkTx_obj.dataBuf);
}

void SetTfdtpCmdHeader(NetworkRx_CmdHeader *pHeader)
{
    pHeader->chNum = 0;

    pHeader->width = TFDTP_CH_MAX_FRAME_WIDTH;
    pHeader->height = TFDTP_CH_MAX_FRAME_HEIGHT;

#if (1 == SYSTEM_DF_YUV420SP_UV)
    {
        pHeader->pitch[0U] = pHeader->width;
        pHeader->pitch[1U] = pHeader->width;

        pHeader->dataSize = (pHeader->pitch[0] * pHeader->height) +
                             ((pHeader->pitch[1]* pHeader->height) / 2U);

        pHeader->payloadType = NETWORK_RX_TYPE_VIDEO_FRAME_YUV420SP_UV;

    }
#elif  (1 == SYSTEM_DF_YUV422I_YUYV)
    {
        pHeader->pitch[0U] = pHeader->width *2;
        pHeader->pitch[1U] = pHeader->width *2;
        pHeader->dataSize =  pHeader->pitch[0] * pHeader->height;
        pHeader->payloadType =  NETWORK_RX_TYPE_VIDEO_FRAME_YUV422I_YUYV;
    }
#else
    printf("# ERROR: Data format not set correctly for TFDTP...\n");
    exit(1);
#endif
}

int ReadCmdHeader(NetworkRx_CmdHeader *pHeader)
{
    UInt32 dataSize;
    Int32 status;

    dataSize = sizeof(*pHeader);

    status = Network_read(&gNetworkTx_obj.sockObj, (UInt8*)pHeader, &dataSize);

    if(status!=0)
    {
        printf("# ERROR: Network read for cmd header failed \n");
        return NETWORK_ERROR;
    }

    if(pHeader->header!=NETWORK_RX_HEADER
        ||
       pHeader->chNum >= gNetworkTx_obj.numCh
        ||
       pHeader->dataSize > MAX_BUF_SIZE
        )
    {
        pHeader->dataSize = 0;
        pHeader->width = 0;
        pHeader->height = 0;
        pHeader->pitch[0] = pHeader->pitch[1] = 0;

        if(pHeader->header!=NETWORK_RX_HEADER)
        {
            printf("# ERROR: Command header not matching\n");
        }
        else if (pHeader->chNum >= gNetworkTx_obj.numCh)
        {
            printf("# ERROR: No. of channels in header not matching user input\n");
        }
        else if (pHeader->dataSize > MAX_BUF_SIZE)
        {
            printf("# ERROR: Buffer size in command header too big (>MAX_BUF_SIZE)\n");
        }
        return NETWORK_INVALID_HEADER;
    }

    return 0;
}

int WriteCmdHeader(NetworkRx_CmdHeader *pHeader)
{
    UInt32 dataSize;
    Int32 status;

    pHeader->header = NETWORK_RX_HEADER;

    dataSize = sizeof(*pHeader);

    status = Network_write(&gNetworkTx_obj.sockObj, (UInt8*)pHeader, dataSize);
    if(status!=0)
        return NETWORK_ERROR;

    return 0;
}

int WriteData_TFDTP(NetworkRx_CmdHeader *pHeader)
{
    Int32 status;
    UInt32 ack;
    Int32 retry;

    if(pHeader->dataSize==0)
        return 0;

    if (gNetworkTx_obj.retryCount)
    {
        retry = gNetworkTx_obj.retryCount;
        do
        {
            status = Network_tfdtpWrite(&gNetworkTx_obj.sockObj, gNetworkTx_obj.dataBuf, pHeader->dataSize);
            ack = Network_tfdtpWaitAck(&gNetworkTx_obj.sockObj);
        }
        while((retry >= 0) && (ack != TFDTP_TRANSMIT_OK));

        if(ack != TFDTP_TRANSMIT_OK)
        {
            status = -1;
            printf("# ERROR: Network_tfdtpWrite Failed!!");
        }
    }
    else
    {
        status = Network_tfdtpWrite(&gNetworkTx_obj.sockObj, gNetworkTx_obj.dataBuf, pHeader->dataSize);
    }
    if(status!=0)
        return NETWORK_ERROR;

    return 0;
}
int WriteData(NetworkRx_CmdHeader *pHeader)
{
    Int32 status;

    if(pHeader->dataSize==0)
        return 0;

    status = Network_write(&gNetworkTx_obj.sockObj, gNetworkTx_obj.dataBuf, pHeader->dataSize);
    if(status!=0)
        return NETWORK_ERROR;

    return 0;
}

void SendData()
{
    Int32 status = 0;
    NetworkRx_CmdHeader cmdHeader;

#if (1 == TFDTP_TX_STREAMING_MODE)
    /* In streaming mode server/EVM will not send command header */
    SetTfdtpCmdHeader(&cmdHeader);
#endif

    while(1)
    {
#if (0 == TFDTP_TX_STREAMING_MODE)
        status = ReadCmdHeader(&cmdHeader);
        if(status==NETWORK_ERROR)
            break;
#endif
        if(status == 0)
        {
            ReadData(&cmdHeader);
        }

        if (1U == gNetworkTx_obj.usetfdtp)
        {
            status = WriteData_TFDTP(&cmdHeader);
            if(status==NETWORK_ERROR)
                break;
        }
        else
        {
            status = WriteCmdHeader(&cmdHeader);
            if(status==NETWORK_ERROR)
                break;
            status = WriteData(&cmdHeader);
            if(status==NETWORK_ERROR)
                break;
        }

        if(gNetworkTx_obj.delay)
        {
            if(gNetworkTx_obj.delay==-1)
            {
                printf("# Waiting for input. Press any key to continue...\n");
                getchar();
            }
            else
            {
                sleep(gNetworkTx_obj.delay);
            }
        }

    }
}

int ConnectToServer()
{
    int status;

    printf("# Network Tx: Connecting to server %s:%d ...\n", gNetworkTx_obj.dstIpAddr, gNetworkTx_obj.serverPort);
    status = Network_connect(&gNetworkTx_obj.sockObj, gNetworkTx_obj.dstIpAddr, gNetworkTx_obj.serverPort);
    return status;
}

void CloseConnection()
{
    Network_close(&gNetworkTx_obj.sockObj);
}

void ParseCmdLineArgs(int argc, char *argv[])
{
    int i, p;
    struct stat fileStat;
    int status;

    gNetworkTx_obj.retryCount = -1;
    memset(gNetworkTx_obj.fileName, 0, sizeof(gNetworkTx_obj.fileName));

    for(i=0; i<argc; i++)
    {
        if(strcmp(argv[i], "--target_ip")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            strcpy(gNetworkTx_obj.dstIpAddr, argv[i]);
        }
        if(strcmp(argv[i], "--host_ip")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            strcpy(gNetworkTx_obj.srcIpAddr, argv[i]);
        }
        else
        if(strcmp(argv[i], "--port")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkTx_obj.serverPort = atoi(argv[i]);
        }
        else
        if(strcmp(argv[i], "--usetfdtp")==0)
        {
            gNetworkTx_obj.usetfdtp = 1;
        }
        else
        if(strcmp(argv[i], "--data-rate")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkTx_obj.thruput = atoi(argv[i]);
        }
        else
        if(strcmp(argv[i], "--no_loop")==0)
        {
            gNetworkTx_obj.noLoop = 1;
        }
        else
        if(strcmp(argv[i], "--verbose")==0)
        {
            gNetworkTx_obj.verbose = 1;
        }
        else
        if(strcmp(argv[i], "--delay")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkTx_obj.delay = atoi(argv[i]);
        }
        else
        if(strcmp(argv[i], "--retry_count")==0)
        {
            i++;
            if(i>=argc)
            {
                ShowUsage();
            }
            gNetworkTx_obj.retryCount = atoi(argv[i]);
        }
        else
        if(strcmp(argv[i], "--files")==0)
        {
            i++;
            p=0;
            for( ;i<argc;i++)
            {
                strcpy(gNetworkTx_obj.fileName[p], argv[i]);
                p++;
            }

            gNetworkTx_obj.numCh = p;
        }
    }

    if(gNetworkTx_obj.dstIpAddr[0]==0
        ||
       gNetworkTx_obj.numCh==0
        )
    {

        if(gNetworkTx_obj.dstIpAddr[0]==0)
        {
            printf("# ERROR: IP Address of server MUST be specified\n");
        }
        if(gNetworkTx_obj.numCh==0)
        {
            printf("# ERROR: Atleast one input file MUST be specified\n");
        }

        ShowUsage();
        exit(0);
    }

    for(p=0; p<gNetworkTx_obj.numCh; p++)
    {
        status = stat(gNetworkTx_obj.fileName[p], &fileStat);
        if(status<0)
        {
            printf("# ERROR: [%s] input file NOT found !!!\n", gNetworkTx_obj.fileName[p]);
            ShowUsage();
            exit(0);
        }
        gNetworkTx_obj.fd[p] = NULL;
    }

    if(gNetworkTx_obj.retryCount == -1)
    {
        gNetworkTx_obj.retryCount = NETWORK_TFDTP_RETRANSMIT_COUNT;
    }
}
