/*
* Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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

/**
*  \file tfdtp_test_client.h
*
*  \brief TFDTP Test Client header file.
*/
#define MAX_CMD_LENGTH 1024

struct LoadStats
{
    uint32_t cpuLoad;
    uint32_t hwiLoad;
    uint32_t ndk2nspRxLoad;
    uint32_t ndk2nspTxLoad;
    uint32_t tfdtp2nspRxLoad;
    uint32_t tfdtp2nspTxLoad;
};

struct TestSWStats
{
    uint32_t tcpPacketCount;
    uint32_t udpPacketCount;
    uint32_t rawPacketCount;
    uint32_t cptsEventCount;
};

struct CPTSEvent
{
    uint32_t eventType;
    uint32_t messageType;
    uint32_t sequenceID;
    uint64_t timestamp;
};

struct EthernetHWErrors
{
    uint32_t RxSOFOverruns;
    uint32_t RxMOFOverruns;
    uint32_t RxDMAOverruns;
    uint32_t RxCRCErrors;
    uint32_t RxAlignCodeErrors;
    uint32_t RxOversized;
    uint32_t RxJabber;
    uint32_t RxUndersized;
    uint32_t RxFragments;
};

struct EthernetHWStats
{
    uint32_t RxGoodFrames;
    uint32_t RxBCastFrames;
    uint32_t RxMCastFrames;
    uint32_t RxPauseFrames;
    uint32_t RxOctets;
    uint32_t TxGoodFrames;
    uint32_t TxBCastFrames;
    uint32_t TxMCastFrames;
    uint32_t TxPauseFrames;
    uint32_t TxOctets;
};

/*---------------------------------------------------------------------------*\
|                         Function Declarations                        |
\*---------------------------------------------------------------------------*/
int GetMACAddress();
int tfdtp_testClient_InitServer(TFDTP_Obj *pObj, uint8_t *buf, uint32_t size);
int tfdtp_testClient_start(TFDTP_Obj *pObj, char *pSrcIpAddr);
int TFDTP_TestClient_sendCmd(TFDTP_Obj *pObj, TestCmdID cmdId, uint32_t *cmdBuf);
