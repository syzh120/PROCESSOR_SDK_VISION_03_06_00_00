 /*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _NETWORK_RX_PRIV_H_
#define _NETWORK_RX_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

#define MAX_CH  (8)
#define MAX_BUFF  (2)

#define NETWORK_ERROR   (-1)
#define NETWORK_INVALID_HEADER  (-2)
#define STOP_ON_ERROR   (0)
#define MAX_BUF_SIZE    (1920*1080*2)
#define PCAP_SRC_IF_STRING "rpcap://"

#if 0
#define ETHTYPE_0 0x88
#define ETHTYPE_1 0xB5
#else
#define ETHTYPE_0 0x22
#define ETHTYPE_1 0xF0
#endif
#define MAX_PACKET_SIZE (1600)
#define FRAME_START_BITS (38)
#define CHANNEL_NUM_BITS (25)
#define ETH_TYPE_BITS    (12)



struct vlan_af
{
    uint16_t tpid;
    uint16_t tci;
};

/* IP header */
typedef struct ether_frame_header
{
    /*! Destination MAC address */
    char dstMac[6];
    /*! Source MAC address */
    char srcMac[6];
    /*! VLAN tag */
    struct vlan_af vlanaf;
    /*! The frame type */
    uint16_t etherType;
} ether_frame_header_t;

typedef struct {

    int numCh;

    char fileName[MAX_CH][1024];

    unsigned int codecType;

    u_char *dataBuf[MAX_CH];

    FILE *fd[MAX_CH];

    int frameCount[MAX_CH];

    unsigned long long totalDataSize[MAX_CH];

    int maxFileSize;
    int channelNum;
    int vlanSkipCnt;
    bool done;
    ether_frame_header_t ethLocalFrmHdr;
    ether_frame_header_t ethRemoteFrmHdr;
    pthread_t readThrId[2];

} NetworkAvbRx_Obj;



extern NetworkAvbRx_Obj gNetworkAVBRx_obj;

void ShowUsage();
int ParseCmdLineArgs(int argc, char *argv[]);
int  ConnectToServer();
void CloseConnection();
void Init();
void DeInit();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


