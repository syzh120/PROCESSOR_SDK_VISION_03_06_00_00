 /*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#include <pcap.h>
#include <sched.h>
#include "avbtp_listener_priv.h"

//#define MJPEG_CODEC
#define INTERACTIVE 1
#define LAUNCH_FFPLAY 1

NetworkAvbRx_Obj gNetworkAVBRx_obj;

void ShowUsage()
{
    printf(" \n");
    printf("# \n");
    printf("# network_avbrx.exe --srcMac <sender mac addr 11:22:33:44:55:66> \n");
    printf("# \n");
    printf("# (c) Texas Instruments 2017\n");
    printf("# \n");
    exit(0);
}

int OpenDataFile(int numChannel,int codec)
{
    int i,status = -1;

    if(numChannel < MAX_CH)
    {
        for (i = 0 ; i < numChannel ; i++)
        {
            if(gNetworkAVBRx_obj.fd[i] == NULL )
            {
#ifdef MJPEG_CODEC
                memcpy(&gNetworkAVBRx_obj.fileName[i],"Received.mjpeg",15);
#else
                memcpy(&gNetworkAVBRx_obj.fileName[i],"Received.h264",15);
#endif
                gNetworkAVBRx_obj.frameCount[i] = 0;
                system("rm -rf Received.h264");
                gNetworkAVBRx_obj.fd[i] = fopen(gNetworkAVBRx_obj.fileName[i],  "wb");
                if(gNetworkAVBRx_obj.fd[i] == NULL)
                {
                    printf("# ERROR: Unable to open file [%s]\n", gNetworkAVBRx_obj.fileName[i]);
                }
                else
                {
                    status = 0;
                }
            }
        }
    }
    return status;
}

int CloseDataFile(int numChannel)
{
    int i,status = -1;

    if(numChannel < MAX_CH)
    {
        for (i = 0 ; i < numChannel ; i++)
        {
            if(gNetworkAVBRx_obj.fd[i] == NULL )
            {
                fclose(gNetworkAVBRx_obj.fd[i]);
                gNetworkAVBRx_obj.fd[i] = NULL;
            }
        }
    }
    return status;
}

int WriteBytes(int chNum,int dataSize)
{
    fwrite(gNetworkAVBRx_obj.dataBuf[chNum], 1, dataSize, gNetworkAVBRx_obj.fd[chNum]);
    fflush(gNetworkAVBRx_obj.fd[chNum]);
    return 0;
}

int frameSize[4] = {0,0,0,0};

void ProcessBytes(const u_char *pktAddr,int size)
{
    int chNum,frameStartBit;
     /* chNum = pktAddr[CHANNEL_NUM_BITS + gNetworkAVBRx_obj.vlanSkipCnt]; */
    chNum = 0;
    frameStartBit = FRAME_START_BITS + gNetworkAVBRx_obj.vlanSkipCnt;

#ifdef MJPEG_CODEC
    if(((pktAddr[frameStartBit] == 0xff) &&
        (pktAddr[frameStartBit+1] == 0xd8)) &&
        (frameSize[chNum] != 0))
    {
        WriteBytes(chNum,frameSize[chNum]);
        frameSize[chNum] = 0;
    }
#else
    if(((pktAddr[frameStartBit] == 0x00) &&
        (pktAddr[frameStartBit +1 ] == 0x00) &&
        (pktAddr[frameStartBit +2 ] == 0x00) &&
        (pktAddr[frameStartBit +3 ] == 0x01)) &&
        (frameSize[chNum] != 0))
    {
        WriteBytes(chNum,frameSize[chNum]);
        frameSize[chNum] = 0;
    }
#endif

    memcpy((gNetworkAVBRx_obj.dataBuf[chNum] + frameSize[chNum]),
           (pktAddr + frameStartBit),
           (size - frameStartBit));
    frameSize[chNum] += (size - frameStartBit);

}

void Init(int numCh)
{
    int i;

    for(i=0 ; i < numCh; i++)
    {
        gNetworkAVBRx_obj.dataBuf[i] = malloc(MAX_BUF_SIZE);
        if(gNetworkAVBRx_obj.dataBuf[i] == NULL)
        {
            printf("# ERROR: Unable to allocate memory for buffer !!! \n");
            exit(0);
        }
    }
}

void DeInit(int numCh)
{
    int i;

    for(i=0 ; i < numCh; i++)
    {
        free(gNetworkAVBRx_obj.dataBuf[i]);
        gNetworkAVBRx_obj.dataBuf[i] = NULL;
    }
    CloseDataFile(numCh);
}

void* getUserInput()
{
    u_int done;
    while(gNetworkAVBRx_obj.done != true)
    {
        sleep(1);
        scanf("%d", &done);
        if(done == 0)
        {
            gNetworkAVBRx_obj.done = true;
        }
    }
    return 0;
}

void* stopMaxFileSize()
{
    u_int size;
    sleep(10);
    while((gNetworkAVBRx_obj.done != true) && (gNetworkAVBRx_obj.maxFileSize))
    {
        sleep(1);
        size = ftell(gNetworkAVBRx_obj.fd[0]);
        // take a position of file pointer un size variable
        if((size/1048576) >= (gNetworkAVBRx_obj.maxFileSize -1))
        {
            printf("\n file size greater than %d MB ",(size/1048576));
            gNetworkAVBRx_obj.done = true;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    pcap_if_t *alldevs, *d;
    pcap_t *fp = NULL;
    u_int inum, i=0;
    char errbuf[PCAP_ERRBUF_SIZE];
    int res;
    struct pcap_pkthdr *header;
    const u_char *pkt_data;
    pthread_attr_t attr;
    struct sched_param param;

    res = ParseCmdLineArgs(argc, argv);
    if(res == 0)
    {
        gNetworkAVBRx_obj.vlanSkipCnt = 0;
        gNetworkAVBRx_obj.done = false;
        /* To support multi channel assing here */
        gNetworkAVBRx_obj.numCh = 1;
        /* To support multi codec assing here */
        gNetworkAVBRx_obj.codecType = 1;

#if (1 == INTERACTIVE)
        printf("Enter the max file write size in MB (0 for infinite )\n");
        scanf("%d", &gNetworkAVBRx_obj.maxFileSize);
#else
        gNetworkAVBRx_obj.maxFileSize =  2000;
#endif
        /* Create a thread to monitor file size and stop usecase*/
        {
            pthread_attr_init (&attr);
            pthread_attr_getschedparam (&attr, &param);
            param.sched_priority = 3;
            pthread_attr_setschedparam (&attr, &param);

            res = pthread_create(&(gNetworkAVBRx_obj.readThrId[0]), &attr, getUserInput, NULL);
            if (res != 0)
                printf("\ncan't create thread :[%s]", strerror(res));

            res = pthread_create(&(gNetworkAVBRx_obj.readThrId[1]), &attr, stopMaxFileSize, NULL);
            if (res != 0)
                printf("\ncan't create thread :[%s]", strerror(res));
        }

        if((gNetworkAVBRx_obj.numCh < MAX_CH) && (gNetworkAVBRx_obj.numCh > 0))
        {
            Init(gNetworkAVBRx_obj.numCh);

            printf("\n Select the the device list:\n");
            /* The user didn't provide a packet source: Retrieve the local device list */
            if (pcap_findalldevs(&alldevs, errbuf) == -1)
            {
                fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
                return -1;
            }

            /* Print the list */
            for(d=alldevs; d; d=d->next)
            {
                printf("%d. %s\n    ", ++i, d->name);
                if (d->description)
                    printf(" (%s)\n", d->description);
                else
                    printf(" (No description available)\n");
            }

            if (i==0)
            {
                fprintf(stderr,"No interfaces found! Exiting.\n");
                return -1;
            }
#if (1 == INTERACTIVE)
            printf("Enter the interface number (1-%d):",i);
            scanf("%d", &inum);
#else
            inum = 1;
#endif
            if (inum < 1 || inum > i)
            {
                printf("\nInterface number out of range.\n");

                /* Free the device list */
                pcap_freealldevs(alldevs);
                return -1;
            }

            /* Jump to the selected adapter */
            for (d=alldevs, i=0; i< inum-1 ;d=d->next, i++);

            /* Open the device */
            if ( (fp= pcap_open_live(d->name,
                                MAX_PACKET_SIZE /*snaplen*/,
                                1 /*flags*/ /* Capture in promiscuous mode*/,
                                20 /*read timeout*/,
                                errbuf)
                                ) == NULL)
            {
                fprintf(stderr,"\nError opening adapter\n");
                return -1;
            }
            if((gNetworkAVBRx_obj.codecType == 0) || (gNetworkAVBRx_obj.codecType == 1))
            {
                OpenDataFile(gNetworkAVBRx_obj.numCh,gNetworkAVBRx_obj.codecType);
            }
            else
            {
                printf("\n  invalid codec type \n");
                pcap_close(fp);
                return -1;
            }
        }
        printf("\n  File opened for writting \n");

        printf("\n  Enter '0' to stop \n");

        if (fp != NULL)
        {
            //system("bash run_display.sh &");
#ifdef linux
#if (1 == LAUNCH_FFPLAY)
    system("ffplay -framerate 33 -v quiet \"Received.h264\" &");
#endif
#endif
            /* Read the packets */
            while(((res = pcap_next_ex( fp, &header, &pkt_data)) >= 0) && (gNetworkAVBRx_obj.done != true))
            {
                if(res == 0)
                    continue;

                memcpy(gNetworkAVBRx_obj.ethLocalFrmHdr.dstMac, pkt_data, sizeof(gNetworkAVBRx_obj.ethLocalFrmHdr.dstMac));
                memcpy(gNetworkAVBRx_obj.ethLocalFrmHdr.srcMac, pkt_data+6, sizeof(gNetworkAVBRx_obj.ethLocalFrmHdr.srcMac));

                if(0 == memcmp(gNetworkAVBRx_obj.ethLocalFrmHdr.srcMac,gNetworkAVBRx_obj.ethRemoteFrmHdr.srcMac,6))
                {
                    /* Creaet a hdr struct and cpy the same */
                    if((pkt_data[12] == 0x81) && (pkt_data[13] == 0x00))
                    {
                        gNetworkAVBRx_obj.vlanSkipCnt = 4;
                    }
                    if((pkt_data[12 + gNetworkAVBRx_obj.vlanSkipCnt] == 0x88) && (pkt_data[13 + gNetworkAVBRx_obj.vlanSkipCnt] == 0xB5) && (pkt_data[CHANNEL_NUM_BITS+gNetworkAVBRx_obj.vlanSkipCnt] == gNetworkAVBRx_obj.channelNum))
                    {
                        ProcessBytes(pkt_data,header->caplen);
                    }
                    if((pkt_data[12 + gNetworkAVBRx_obj.vlanSkipCnt] == 0x22) && (pkt_data[13 + gNetworkAVBRx_obj.vlanSkipCnt] == 0xF0) && (pkt_data[CHANNEL_NUM_BITS+gNetworkAVBRx_obj.vlanSkipCnt] == gNetworkAVBRx_obj.channelNum))
                    {
                        ProcessBytes(pkt_data,header->caplen);
                    }
                }
            }
            if(res == -1)
            {
                fprintf(stderr, "Error reading the packets: %s\n", pcap_geterr(fp));
                return -1;
            }
            DeInit(gNetworkAVBRx_obj.numCh);
            pcap_freealldevs(alldevs);
            pcap_close(fp);

        }
    }
    return 0;
}

char atohex(char *in)
{
    char lowNib;
    char upNib;

    upNib = in[0] > '9' ? (in[0]|32) - 'a' + 10 : in[0] - '0';
    lowNib = in[1] > '9' ? (in[1]|32) - 'a' + 10 : in[1] - '0';

    return(lowNib | ((upNib << 4)));
}
int ParseCmdLineArgs(int argc, char *argv[])
{
    int i, j;
    char *varAddr;
    int macAddrSet = 0;
    int status = -1;
    for(i=0; i<argc; i++)
    {
        if(strcmp(argv[i], "--channelNum")==0)
        {
            i++;
            gNetworkAVBRx_obj.channelNum = atoi(argv[i]);
        }
        else
        if(strcmp(argv[i], "--srcMac")==0)
        {
            i++;
            varAddr = strtok(argv[i], ":");
            if(varAddr != NULL)
            {
                gNetworkAVBRx_obj.ethRemoteFrmHdr.srcMac[0] = atohex(varAddr);
                macAddrSet++;
                for(j = 1 ;j < 6; j ++)
                {
                    varAddr = strtok(NULL, ":");
                    if(varAddr != NULL)
                    {
                        gNetworkAVBRx_obj.ethRemoteFrmHdr.srcMac[j] = atohex(varAddr);
                        macAddrSet++;
                    }
                }
            }
        }
    }
    if(macAddrSet != 6)
    {
        printf("# ERROR: Src Mac addr should be specified as xx:xx:xx:xx:xx:xx\n");
        ShowUsage();
        exit(0);
    }
    else
    {
        status = 0;
    }
    return status;
}


