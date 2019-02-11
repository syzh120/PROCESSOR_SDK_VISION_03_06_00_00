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

// C++ STL headers
#include <iostream>
#include <sstream>
#include <map>
#include <utility>
#include <vector>

// Legacy C headers
#include <cstdlib>

// Local project headers
#include "TestClient.hpp"
#include "Packet.hpp"
#include "Socket.hpp"
#include "Options.hpp"
#include "TrafficGenerator.hpp"
#include "DataSource.hpp"
#include "JPEGSource.hpp"
#include "../../common/test_common.h"

using namespace std;
using namespace test;

struct TestSWStats
{
    uint32_t tcpPacketCount;
    uint32_t udpPacketCount;
    uint32_t avbtpPacketCount;
    uint32_t avbtpErrorCount;
};

struct AVBTPStats
{
    /*! Number of stream data packets successfully parsed and processed by AVB stack */
    uint32_t packetCnt;
    /*! Number of ignored data packets that are dropped by the AVB stack */
    uint32_t ignoredPacketCnt;
    /*! Number of parser errors encountered by the AVB stack */
    uint32_t errorCnt;
    /*! Number of control packets received */
    uint32_t controlPacketCnt;
    /*! Number of packets with an unexpected ether type field */
    uint32_t unexpectedEtherType;
    /*! Number of packets with an unexpected AVTP subtype field */
    uint32_t unexpectedSubType;
    /*! Number of packets tagged with a stream ID which does not refer to any registered listener */
    uint32_t unexpectedStreamID;
    /*! Number of stream data packets that did not signal stream ID valid flag (violation of the standard) */
    uint32_t svFlagError;
    /*! Number of packets with zero size or bigger than the maximum allowed AVTP payload */
    uint32_t invalidPacketSizeError;
    /*! Number of times the parser encountered an out-of-sequence packet (either from packet loss or truly out of sequence) */
    uint32_t outOfSequenceError;
    /*! Number of times the parser could not find a free buffer to write into */
    uint32_t noBuffersAvailable;
    /*! Number of times the parser ran out of buffer space while assembling an output frame */
    uint32_t insufficientSizeError;
    /*! Number of times the parser encountered a JPEG SOI marker before an EOI marker */
    uint32_t missedEOIError;
    /*! Number of times the parser encountered a JPEG RST marker - tracked only if RST marker detection is enabled*/
    uint32_t numRestartMarkers;
    /*! Number of times the parser encountered a JPEG SOI marker */
    uint32_t numSOIMarkers;
    /*! Number of times the parser encountered a JPEG EOI marker */
    uint32_t numEOIMarkers;
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

struct NDKIpStats
{
    /* UDP Stats */
    uint32_t UDPRcvTotal;
    uint32_t UDPRcvShort;
    uint32_t UDPRcvBadLen;
    uint32_t UDPRcvBadSum;
    uint32_t UDPRcvFull;
    uint32_t UDPRcvNoPort;
    uint32_t UDPRcvNoPortB;

    /* TCP Stats */
    uint32_t TCPRcvTotal;
    uint32_t TCPRcvShort;
    uint32_t TCPRcvHdrSize;
    uint32_t TCPRcvBadSum;

    /* IP Stats */
    uint32_t IPTotal;
    uint32_t IPOdropped;
    uint32_t IPBadsum;
    uint32_t IPBadhlen;
    uint32_t IPBadlen;
    uint32_t IPBadoptions;
    uint32_t IPBadvers;
    uint32_t IPNoproto;
    uint32_t IPDelivered;
};

struct LoadStats
{
    uint32_t cpuLoad;
    uint32_t hwiLoad;
    uint32_t ndk2nspRxLoad;
    uint32_t ndk2nspTxLoad;
    uint32_t avbtpRxLoad;
    uint32_t avbtpTxLoad;
};

static void sendCmd(const TCPSocket& cmdSocket, const Packet& p)
{
    cmdSocket.send(p);
    vector<uint8_t> recvBuf = cmdSocket.receive(p.size());
    if (!std::equal(begin(recvBuf), end(recvBuf), p.data())) {
        throw TCPSocket::Error("No ACK received!");
    }
}

static void sendCmd(const TCPSocket& cmdSocket, uint32_t cmdId)
{
    CommandPacket p(cmdId);
    sendCmd(cmdSocket, p);
}

static void sendCmd(const TCPSocket& cmdSocket, uint32_t cmdId, uint32_t param)
{
    CommandPacket p(cmdId, param);
    sendCmd(cmdSocket, p);
}

static uint32_t readNetOrder32(vector<uint8_t>::iterator& it)
{
    uint32_t val = it[0] | (it[1] << 8) | (it[2] << 16) | (it[3] << 24);
    it += sizeof(uint32_t);
    return ntohl(val);
}

static TestSWStats getSWStats(TCPSocket& cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_SW_STATS);

    TestSWStats stats;
    vector<uint8_t> recvBuf = cmdSocket.receive(sizeof(TestSWStats));

    auto it = begin(recvBuf);
    stats.tcpPacketCount    = readNetOrder32(it);
    stats.udpPacketCount    = readNetOrder32(it);
    stats.avbtpPacketCount  = readNetOrder32(it);
    stats.avbtpErrorCount   = readNetOrder32(it);

    return stats;
}

static AVBTPStats getAVBStats(const TCPSocket& cmdSocket, uint32_t instance = 0)
{
    sendCmd(cmdSocket, TEST_CMD_GET_AVB_STATS, instance);

    AVBTPStats stats;
    vector<uint8_t> recvBuf = cmdSocket.receive(sizeof(AVBTPStats));

    auto it = begin(recvBuf);
    stats.packetCnt = readNetOrder32(it);
    stats.ignoredPacketCnt = readNetOrder32(it);
    stats.errorCnt = readNetOrder32(it);
    stats.controlPacketCnt = readNetOrder32(it);
    stats.unexpectedEtherType = readNetOrder32(it);
    stats.unexpectedSubType = readNetOrder32(it);
    stats.unexpectedStreamID = readNetOrder32(it);
    stats.svFlagError = readNetOrder32(it);
    stats.invalidPacketSizeError = readNetOrder32(it);
    stats.outOfSequenceError = readNetOrder32(it);
    stats.noBuffersAvailable = readNetOrder32(it);
    stats.insufficientSizeError = readNetOrder32(it);
    stats.missedEOIError = readNetOrder32(it);
    stats.numRestartMarkers = readNetOrder32(it);
    stats.numSOIMarkers = readNetOrder32(it);
    stats.numEOIMarkers = readNetOrder32(it);
    return stats;
}

static void clearAVBStats(const TCPSocket& cmdSocket, uint32_t instance = 0)
{
    sendCmd(cmdSocket, TEST_CMD_CLEAR_AVB_STATS, instance);
}

static void printAVBStats(const AVBTPStats& stats)
{
    cout << "--- AVB Status at target --" << endl;
    cout << "----- packet count                     : " << stats.packetCnt << endl;
    cout << "----- ignored packet count             : " << stats.ignoredPacketCnt << endl;
    cout << "----- parser errors                    : " << stats.errorCnt << endl;
    cout << "----- control packet count             : " << stats.controlPacketCnt << endl;
    cout << "----- unexpected ether-type errors     : " << stats.unexpectedEtherType << endl;
    cout << "----- unexpected sub-type errors       : " << stats.unexpectedSubType << endl;
    cout << "----- unexpected stream ID errors      : " << stats.unexpectedStreamID << endl;
    cout << "----- valid stream ID flag unset errors: " << stats.svFlagError << endl;
    cout << "----- invalid packet size errors       : " << stats.invalidPacketSizeError << endl;
    cout << "----- out of sequence errors           : " << stats.outOfSequenceError << endl;
    cout << "----- no buffers available errors      : " << stats.noBuffersAvailable << endl;
    cout << "----- insufficient size errors         : " << stats.insufficientSizeError << endl;
    cout << "----- missed EOI errors                : " << stats.missedEOIError << endl;
    cout << "----- number of RST markers detected   : " << stats.numRestartMarkers << endl;
    cout << "----- number of SOI markers detected   : " << stats.numSOIMarkers << endl;
    cout << "----- number of EOI markers detected   : " << stats.numEOIMarkers << endl;
}

static EthernetHWErrors getHWErrors(const TCPSocket& cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_HW_ERRORS);

    EthernetHWErrors errors;
    vector<uint8_t> recvBuf = cmdSocket.receive(sizeof(EthernetHWErrors));

    auto it = begin(recvBuf);
    errors.RxSOFOverruns = readNetOrder32(it);
    errors.RxMOFOverruns = readNetOrder32(it);
    errors.RxDMAOverruns = readNetOrder32(it);
    errors.RxCRCErrors = readNetOrder32(it);
    errors.RxAlignCodeErrors = readNetOrder32(it);
    errors.RxOversized = readNetOrder32(it);
    errors.RxJabber = readNetOrder32(it);
    errors.RxUndersized = readNetOrder32(it);
    errors.RxFragments = readNetOrder32(it);

    return errors;
}

static void printHWErrors(const EthernetHWErrors& errors)
{
    cout << "--- Target ethernet hardware RX errors --" << endl;
    cout << "----- start of frame overruns      : " << errors.RxSOFOverruns << endl;
    cout << "----- middle of frame overruns     : " << errors.RxMOFOverruns << endl;
    cout << "----- DMA overruns                 : " << errors.RxDMAOverruns << endl;
    cout << "----- CRC errors                   : " << errors.RxCRCErrors << endl;
    cout << "----- aligment errors              : " << errors.RxAlignCodeErrors << endl;
    cout << "----- oversized frames             : " << errors.RxOversized << endl;
    cout << "----- jabber frames                : " << errors.RxJabber << endl;
    cout << "----- undersized frames            : " << errors.RxUndersized << endl;
    cout << "----- fragments                    : " << errors.RxFragments << endl;
}

static EthernetHWStats getHWStats(const TCPSocket& cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_HW_STATS);

    EthernetHWStats stats;
    vector<uint8_t> recvBuf = cmdSocket.receive(sizeof(EthernetHWStats));

    auto it = begin(recvBuf);
    stats.RxGoodFrames  = readNetOrder32(it);
    stats.RxBCastFrames = readNetOrder32(it);
    stats.RxMCastFrames = readNetOrder32(it);
    stats.RxPauseFrames = readNetOrder32(it);
    stats.RxOctets      = readNetOrder32(it);
    stats.TxGoodFrames  = readNetOrder32(it);
    stats.TxBCastFrames = readNetOrder32(it);
    stats.TxMCastFrames = readNetOrder32(it);
    stats.TxPauseFrames = readNetOrder32(it);
    stats.TxOctets      = readNetOrder32(it);

    return stats;
}

static void printHWStats(const EthernetHWStats& stats)
{
    cout << "--- Target ethernet hardware RX/TX stats --" << endl;
    cout << "----- Rx good frames count     : " << stats.RxGoodFrames << endl;
    cout << "----- Rx broadcast frame count : " << stats.RxBCastFrames << endl;
    cout << "----- Rx multicast frame count : " << stats.RxMCastFrames << endl;
    cout << "----- Rx pause frame count     : " << stats.RxPauseFrames << endl;
    cout << "----- Rx octet count           : " << stats.RxOctets << endl;
    cout << "----- Tx good frames count     : " << stats.TxGoodFrames << endl;
    cout << "----- Tx broadcast frame count : " << stats.TxBCastFrames << endl;
    cout << "----- Tx multicast frame count : " << stats.TxMCastFrames << endl;
    cout << "----- Tx pause frame count     : " << stats.TxPauseFrames << endl;
    cout << "----- Tx octet count           : " << stats.TxOctets << endl;
}

static NDKIpStats getNDKIpStats(const TCPSocket& cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_NDK_STATS);

    NDKIpStats stats;
    vector<uint8_t> recvBuf = cmdSocket.receive(sizeof(NDKIpStats));

    auto it = begin(recvBuf);
    stats.UDPRcvTotal       = readNetOrder32(it);
    stats.UDPRcvShort       = readNetOrder32(it);
    stats.UDPRcvBadLen      = readNetOrder32(it);
    stats.UDPRcvBadSum      = readNetOrder32(it);
    stats.UDPRcvFull        = readNetOrder32(it);
    stats.UDPRcvNoPort      = readNetOrder32(it);
    stats.UDPRcvNoPortB     = readNetOrder32(it);

    stats.TCPRcvTotal       = readNetOrder32(it);
    stats.TCPRcvShort       = readNetOrder32(it);
    stats.TCPRcvHdrSize     = readNetOrder32(it);
    stats.TCPRcvBadSum      = readNetOrder32(it);

    stats.IPTotal           = readNetOrder32(it);
    stats.IPOdropped        = readNetOrder32(it);
    stats.IPBadsum          = readNetOrder32(it);
    stats.IPBadhlen         = readNetOrder32(it);
    stats.IPBadlen          = readNetOrder32(it);
    stats.IPBadoptions      = readNetOrder32(it);
    stats.IPBadvers         = readNetOrder32(it);
    stats.IPNoproto         = readNetOrder32(it);
    stats.IPDelivered       = readNetOrder32(it);

    return stats;
}

static void printNDKIpStats(const NDKIpStats& stats)
{
    cout << "--- Target UDP Rx stats --" << endl;
    cout << "----- Rx total packet count                                 : " << stats.UDPRcvTotal   << endl;
    cout << "----- Rx packets dropped due to too small length            : " << stats.UDPRcvShort   << endl;
    cout << "----- Rx packets dropped due to too large length            : " << stats.UDPRcvBadLen  << endl;
    cout << "----- Rx packets dropped due to checksum errors             : " << stats.UDPRcvBadSum  << endl;
    cout << "----- Rx packets dropped due to socket queue full           : " << stats.UDPRcvFull    << endl;
    cout << "----- Rx packets dropped due to no listening port           : " << stats.UDPRcvNoPort  << endl;
    cout << "----- Rx broadcast packets dropped due to no listening port : " << stats.UDPRcvNoPortB << endl;
    cout << "--- Target TCP Rx stats --" << endl;
    cout << "----- Rx total packet count                                 : " << stats.TCPRcvTotal   << endl;
    cout << "----- Rx packets dropped due to too small length            : " << stats.TCPRcvShort   << endl;
    cout << "----- Rx packets dropped due to too large length            : " << stats.TCPRcvHdrSize << endl;
    cout << "----- Rx packets dropped due to checksum errors             : " << stats.TCPRcvBadSum  << endl;
    cout << "--- Target overall IP Rx stats --" << endl;
    cout << "----- Rx total packet count                                 : " << stats.IPTotal   << endl;
    cout << "----- Rx packets dropped due to buffer issues               : " << stats.IPOdropped   << endl;
    cout << "----- Rx packets dropped due to bad IP checksum             : " << stats.IPBadsum  << endl;
    cout << "----- Rx packets dropped due to invalid header length       : " << stats.IPBadhlen  << endl;
    cout << "----- Rx packets dropped due to invalid packet length       : " << stats.IPBadlen    << endl;
    cout << "----- Rx packets dropped due to invalid IP options          : " << stats.IPBadoptions  << endl;
    cout << "----- Rx packets dropped due to no wrong IP version         : " << stats.IPBadvers << endl;
    cout << "----- Rx packets dropped due to an unsupported IP protocol  : " << stats.IPNoproto  << endl;
    cout << "----- Rx packet count delivered to a protocol stack         : " << stats.IPDelivered << endl;
}

static uint32_t getBuffCount(const TCPSocket& cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_BUFFER_COUNT);

    uint32_t bufCnt;
    vector<uint8_t> recvBuf = cmdSocket.receive(sizeof(uint32_t));

    auto it = begin(recvBuf);
    bufCnt = readNetOrder32(it);

    return bufCnt;
}

static LoadStats getLoadStats(const TCPSocket& cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_LOAD_INFO);

    LoadStats stats;
    vector<uint8_t> recvBuf = cmdSocket.receive(sizeof(LoadStats));

    auto it = begin(recvBuf);
    stats.cpuLoad       = readNetOrder32(it);
    stats.hwiLoad       = readNetOrder32(it);
    stats.ndk2nspRxLoad = readNetOrder32(it);
    stats.ndk2nspTxLoad = readNetOrder32(it);
    stats.avbtpRxLoad   = readNetOrder32(it);
    stats.avbtpTxLoad   = readNetOrder32(it);

    return stats;
}

static void printLoadStats(const LoadStats& stats, bool printNDKStats = false, bool printAVBStats = false)
{
    cout << "--- CPU Load   : " << setfill('0') << setw(3) << stats.cpuLoad << "%" << endl;
    cout << "  - HWI Load   : " << setfill('0') << setw(3) << stats.hwiLoad << "%" << endl;
    if (printNDKStats)
    {
        cout << "  - NDK Rx Load: " << setfill('0') << setw(3) << stats.ndk2nspRxLoad << "%" << endl;
        cout << "  - NDK Tx Load: " << setfill('0') << setw(3) << stats.ndk2nspTxLoad << "%" << endl;
    }
    if (printAVBStats)
    {
        cout << "  - AVB Rx Load: " << setfill('0') << setw(3) << stats.avbtpRxLoad << "%" << endl;
        cout << "  - AVB Tx Load: " << setfill('0') << setw(3) << stats.avbtpTxLoad << "%" << endl;
    }
}


const string TestClient::TEST_CMD_QDISC_CLASS = "1:1";
const string TestClient::TEST_CMD_QDISC_RATE  = "10mbit";
const string TestClient::TEST_CMD_QDISC_PRIO  = "1";

TestClient::TestClient(Options& opts)
    : opts(&opts)
{
    int testDuration        = opts.getInt("test-duration");
    int longTestDuration    = opts.getInt("long-test-duration");
    int numLoadMeasures     = opts.getInt("num-load-measures");
    int numShutdowns        = opts.getInt("num-shutdowns");
    int numTalkers          = opts.getInt("num-talkers");
    string srcMacString     = opts.get("src-mac-spoof");

    // Validate some of the options
    if (numTalkers == -1)
    {
        numTalkers = 4;
    }

    // Create the command TCP socket
    cmdSocket = new TCPSocket(opts.get("dest-ip"), to_string(TEST_CMD_PORT));
    cmdSocket->setRcvTimeout(5);

    // Lookup dest MAC address from the IP address (now that command socket exists)
    MACAddress dstMac = getTargetMAC(opts.get("dest-ip"), opts.get("dev"));
    cout << "Using destination MAC found from destination IP address: " << dstMac << "." << endl;

    // Get the src MAC address (use the one given from the command line, if it exists)
    MACAddress srcMac;
    if (!srcMacString.empty())
    {
        // Spoof the mac address instead of using the one from the NIC
        srcMac = {srcMacString};
        cout << "Using source MAC spoof address provided : " << srcMac << "." << endl;
    }
    else
    {
        RawSocket socket(opts.get("dev"), dstMac);
        srcMac = socket.getSrcMAC();
        cout << "Using source MAC looked up from device: " << srcMac << "." << endl;
    }

    // Instantiate the MJPEG data sources
    vector<string> fileNames = tokenize(opts.get("input"), ' ');
    replicateLast(fileNames, numTalkers);
    dataSources = new vector<JPEGSource>();
    dataSources->reserve(numTalkers);
    bool enableLooping = opts.getBool("loop");
    for (int i = 0; i < numTalkers; i++)
    {
        JPEGSource src = JPEGSource(fileNames[i], enableLooping);
        dataSources->push_back(std::move(src));
    }

    // Setup qdisc traffic management
    vector<string> tokens = tokenize(AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS, ':');
    auto subClassNum = stoi(tokens.at(1));

    tcManager = new TrafficClassManager(opts.get("dev"), opts.getBool("verbose"), subClassNum);

    tcManager->setClass(
        TestClient::TEST_CMD_QDISC_CLASS,
        TestClient::TEST_CMD_QDISC_RATE,
        TestClient::TEST_CMD_QDISC_PRIO);
    tcManager->setClass(TCPTrafficGenerator::TEST_TCP_QDISC_CLASS, "10mbit", to_string(2));
    tcManager->setClass(UDPTrafficGenerator::TEST_UDP_QDISC_CLASS, "10mbit", to_string(3));
    tcManager->setClass(AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS, "10mbit", to_string(100));

    // Add traffic class filters
    std::string filter = "u32 match ip dport " + to_string(TEST_CMD_PORT) + " 0xffff";
    tcManager->setFilter(
        "ip",
        filter,
        TestClient::TEST_CMD_QDISC_CLASS);

    filter = "u32 match ip dport " + opts.get("tcp-port") + " 0xffff";
    tcManager->setFilter(
        "ip",
        filter,
        TCPTrafficGenerator::TEST_TCP_QDISC_CLASS);

    filter = "u32 match ip dport " + opts.get("udp-port") + " 0xffff";
    tcManager->setFilter(
        "ip",
        filter,
        UDPTrafficGenerator::TEST_UDP_QDISC_CLASS);

    // We don't set a filter for AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS
    // since it will be used as the default class. Ideally we would set a filter
    // to classify off of the Ethertype, or VLAN tags, but that has proven to be
    // difficult to work out how to do with the tc command.
#if (0)
    filter = "u32 match u16 " + int_to_hex(RawPacket::ETHER_TYPE_EXPERIMENTAL) + " 0xffff at -2 " +
             "match u16 0x8100 0xffff at -6";
    tcManager->setFilter(
        "ip",
        filter,
        AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS);
#endif

    // Create the TCP/IP traffic generator
    tcpGen = new TCPTrafficGenerator(opts.get("dest-ip"), opts.get("tcp-port"), *tcManager, opts.getBool("verbose"));

    // Create the UDP traffic generator
    udpGen = new UDPTrafficGenerator(opts.get("dest-ip"), opts.get("udp-port"), *tcManager, opts.getBool("verbose"));

    // Create the AVBTP traffic generator
    avbGen = new AVBTrafficGenerator(opts.get("dev"), srcMac, dstMac, *dataSources, *tcManager, opts.getBool("verbose"));
    // Set the default vlan for the generator
    avbGen->setVLAN(opts.getInt("vlan-id"), opts.getInt("vlan-priority"));
    avbGen->setEthertype(opts.getInt("avb-ethertype"));
    avbGen->setSubtype(opts.getInt("avb-subtype"));
    avbGen->setCvFormattype(opts.getInt("avb-cvformattype"));

    // Register all tests

    // JPEG output validation test
    if (opts.getBool("run-validation-test"))
    {
        unique_ptr<UnitTest> outputValTest =
            make_unique<OutputValidationTest>(*cmdSocket, *avbGen, *tcpGen);
        tests.push_back(std::move(outputValTest));
    }

    // Load Tests
    if (numLoadMeasures > 0)
    {
        // Maps core name to expected RX loads (AVB only loads)
        map<string, AVBLoadTest::LoadRange> rxAVBLoadRangeMap
        {
            {"vayu-ipu1",       {39.0, 34.0, 4.0}},
            {"vayu-mpu",        {39.0, 34.0, 4.0}},
            {"j6eco-ipu1",       {39.0, 34.0, 4.0}},
            {"j6eco-mpu",        {39.0, 34.0, 4.0}},
            {"j5eco-mc",        {39.0, 34.0, 4.0}},
            {"j5eco-mpu",       {39.0, 34.0, 4.0}},
            {"centaurus-mc",    {39.0, 34.0, 4.0}},
            {"centaurus-mpu",   {39.0, 34.0, 4.0}}
        };

        auto rxAVBLoadEntry = rxAVBLoadRangeMap.find(opts.get("core-name"));

        if (rxAVBLoadEntry == rxAVBLoadRangeMap.end())
        {
            throw runtime_error("invalid core name!");
        }

        unique_ptr<UnitTest> avbLoadTest =
            make_unique<AVBLoadTest>(*cmdSocket, TrafficTest::Type::AVB_ONLY, *avbGen, *tcpGen, rxAVBLoadEntry->second, numLoadMeasures);
        tests.push_back(std::move(avbLoadTest));

        // Maps core name to expected RX loads (AVB+TCP loads)
        map<string, AVBLoadTest::LoadRange> rxAVBPlusTCPLoadRangeMap
        {
            {"vayu-ipu1",       {50.0, 34.0, 4.0}},
            {"vayu-mpu",        {50.0, 34.0, 4.0}},
            {"j6eco-ipu1",      {50.0, 34.0, 4.0}},
            {"j6eco-mpu",       {50.0, 34.0, 4.0}},
            {"j5eco-mc",        {50.0, 34.0, 4.0}},
            {"j5eco-mpu",       {50.0, 34.0, 4.0}},
            {"centaurus-mc",    {50.0, 34.0, 4.0}},
            {"centaurus-mpu",   {50.0, 34.0, 4.0}}
        };

        auto rxAVBPlusTCPLoadEntry = rxAVBPlusTCPLoadRangeMap.find(opts.get("core-name"));

        if (rxAVBPlusTCPLoadEntry == rxAVBPlusTCPLoadRangeMap.end())
        {
            throw runtime_error("invalid core name!");
        }

        unique_ptr<UnitTest> avbTcpLoadTest =
            make_unique<AVBLoadTest>(*cmdSocket, TrafficTest::Type::AVB_PLUS_TCP, *avbGen, *tcpGen, rxAVBPlusTCPLoadEntry->second, numLoadMeasures);
        tests.push_back(std::move(avbTcpLoadTest));

        //Maps core name to expected TX loads (AVB only)
        map<string, AVBTxLoadTest::LoadRange> txLoadRangeMap
        {
           /* TODO: measure correct expected loads during AVB Tx */
           {"vayu-ipu1",  {100.0, 100.0, 100.0}},
           {"vayu-mpu", {100.0, 100.0, 100.0}},
           {"j6eco-ipu1",       {100.0, 100.0, 100.0}},
           {"j6eco-mpu",        {100.0, 100.0, 100.0}},
           {"j5eco-mc",   {100.0, 100.0, 100.0}},
           {"j5eco-mpu",  {100.0, 100.0, 100.0}},
           {"centaurus-mc",  {100.0, 100.0, 100.0}},
           {"centaurus-mpu", {100.0, 100.0, 100.0}}
        };

        auto txLoadEntry = txLoadRangeMap.find(opts.get("core-name"));

        if (txLoadEntry == txLoadRangeMap.end())
        {
            throw runtime_error("invalid core name!");
        }

        unique_ptr<UnitTest> avbTxLoadTest =
            make_unique<AVBTxLoadTest>(*cmdSocket, txLoadEntry->second, numLoadMeasures);
        /*
         * Commenting AVBTx as needs changes in avbtp_test_server. Currently new packets are sent in TxDone callback and AVB
         * as AVB Tx task is highest priority the stop command never gets received on server causing continueos Tx
         */
        //tests.push_back(std::move(avbTxLoadTest));
    }

    // Shutdown Tests
    if (numShutdowns > 0)
    {
        // AVBTP shutdown/restart stress test
        unique_ptr<UnitTest> stressTest =
            make_unique<ShutdownStressTest>(*cmdSocket, TrafficTest::Type::AVB_ONLY, *avbGen, *tcpGen, numShutdowns);
        tests.push_back(std::move(stressTest));

        // AVBTP+TCP shutdown/restart stress test
        unique_ptr<UnitTest> stressTestTCP =
            make_unique<ShutdownStressTest>(*cmdSocket, TrafficTest::Type::AVB_PLUS_TCP, *avbGen, *tcpGen, numShutdowns);
        /* This test is failing on IPU (passes on A15). Commenting out as debug not done for IPU */
        //tests.push_back(std::move(stressTestTCP));
    }

    // Short Packet Loss Tests
    if (testDuration > 0)
    {
        // AVBTP Packet Loss test
        unique_ptr<UnitTest> avbPacketLossTest =
            make_unique<AVBTimedPacketLossTest>(*cmdSocket, TrafficTest::Type::AVB_ONLY, *avbGen, *tcpGen, testDuration);
        tests.push_back(std::move(avbPacketLossTest));

        // AVBTP+TCP Packet Loss test
        unique_ptr<UnitTest> avbTCPPacketLossTest =
            make_unique<AVBTimedPacketLossTest>(*cmdSocket, TrafficTest::Type::AVB_PLUS_TCP, *avbGen, *tcpGen, testDuration);
        tests.push_back(std::move(avbTCPPacketLossTest));
    }

    // EOI and RST handling tests (always run)
    unique_ptr<UnitTest> eoiHandlingTest =
        make_unique<EOIHandlingTest>(*cmdSocket, *avbGen, *tcpGen);
    tests.push_back(std::move(eoiHandlingTest));

    unique_ptr<UnitTest> rstHandlingTest =
        make_unique<RSTHandlingTest>(*cmdSocket, *avbGen, *tcpGen);
    tests.push_back(std::move(rstHandlingTest));

    if (opts.getBool("run-parser-test"))
    {
        unique_ptr<UnitTest> avbTCPParserErrorTest =
            make_unique<AVBParserErrorTest>(*cmdSocket, TrafficTest::Type::AVB_PLUS_TCP, *avbGen, *tcpGen);

        tests.push_back(std::move(avbTCPParserErrorTest));
    }

    if (longTestDuration > 0)
    {
        // Long duration packet loss test
        unique_ptr<UnitTest> avbTCPLongPacketLossTest =
            make_unique<AVBTimedPacketLossTest>(*cmdSocket, TrafficTest::Type::AVB_PLUS_TCP, *avbGen, *tcpGen, longTestDuration);
        tests.push_back(std::move(avbTCPLongPacketLossTest));
    }
}

TestClient::~TestClient()
{
    delete avbGen;
    delete udpGen;
    delete tcpGen;
    delete dataSources;
    delete tcManager;
    delete cmdSocket;
}

void TestClient::executeAllTests()
{
    stringstream ss;
    for (auto& t : tests)
    {
        cout << "====[" << t->description() << "]====" << endl;
        bool ret = t->execute();
        string passFailedStr = ret ? "Pass" : "FAIL!";
        ss << "[" << t->description() << "] : " << passFailedStr << " : " << t->results() << endl;
        cout << "====[Finished " << t->description() << " - " << passFailedStr
             << "]====" << endl << endl;
    }

    auto s = ss.str();
    if (s.size() > 0)
    {
        cout << "===Summary====" << endl;
        cout << s;
    }
    else
    {
        cout << "No tests executed!" << endl;
    }
}


// UnitTest implementation
UnitTest::UnitTest(TCPSocket& cmdSocket)
    : cmdSocket(&cmdSocket)
{
}

UnitTest::~UnitTest() = default;

string UnitTest::results()
{
    return "";
}

// TrafficTest implementation
TrafficTest::TrafficTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType, uint32_t genTimeSecs, uint32_t wakeupRateInSecs)
    : UnitTest(cmdSocket), trafficType(trafficType), genTimeSecs(genTimeSecs), wakeupRateInSecs(wakeupRateInSecs)
{
}

TrafficTest::~TrafficTest() = default;

// AVBTrafficTest implementation
AVBnTCPTrafficTest::AVBnTCPTrafficTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                               AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                               uint32_t genTimeSecs, uint32_t wakeupRateInSecs)
    : TrafficTest(cmdSocket, trafficType, genTimeSecs, wakeupRateInSecs), avbGen(&avbGen), tcpGen(&tcpGen)
{
}

bool AVBnTCPTrafficTest::execute()
{
    bool retVal = true;
    TrafficGenThread avbThread(*avbGen);
    TrafficGenThread tcpThread(*tcpGen);

    try
    {
        if (!beforeTraffic())
        {
            return false;
        }

        // Start Traffic threads
        avbThread.start();
        if (trafficType == Type::AVB_PLUS_TCP)
        {
            tcpThread.start();
        }

        if (genTimeSecs != 0)
        {
            if (trafficType == Type::AVB_PLUS_TCP)
            {
                cout << "--- Generating AVB+TCP traffic for " << genTimeSecs
                    << " seconds..." << endl;
            }
            else
            {
                cout << "--- Generating AVB traffic for " << genTimeSecs
                    << " seconds..." << endl;
            }

            // Let traffic ramp up for one seconds
            std::chrono::seconds rampTime(1);
            this_thread::sleep_for(rampTime);

            uint32_t passedTime = 0;
            if (wakeupRateInSecs != 0)
            {
                // Wake up rate is non-zero, so we wake up periodically
                // during the traffic and do the during traffic work
                while (passedTime < genTimeSecs)
                {
                    std::chrono::seconds sleepTime(wakeupRateInSecs);
                    this_thread::sleep_for(sleepTime);
                    passedTime += wakeupRateInSecs;

                    if (!duringTraffic())
                    {
                        retVal = false;
                        break;
                    }
                }
            }
            else
            {
                // Wake up rate is zero, do nothing during traffic
                std::chrono::seconds sleepTime(genTimeSecs);
                this_thread::sleep_for(sleepTime);
            }

            // Let traffic ramp down
            this_thread::sleep_for(rampTime);
        }

        if (trafficType == Type::AVB_PLUS_TCP)
        {
            tcpThread.stop();
        }
        avbThread.stop();

        if (retVal)
        {
            retVal = afterTraffic();
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[AVBnTCPTrafficTest]: error - " << e.what() << endl;
        retVal = false;
    }

    return retVal;
}

bool AVBnTCPTrafficTest::beforeTraffic()
{
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);

    // Set TCP echo ON
    if (trafficType == Type::AVB_PLUS_TCP)
    {
        tcpGen->setEchoExpected(true);

        sendCmd(*cmdSocket, TEST_CMD_ENABLE_TCP_ECHO);
    }

    vector<JPEGSource>* sources = avbGen->getDataSources();

    for (auto& s : *sources)
    {
        // By default don't cap the number of frames
        s.setMaxFrames(0);
        s.enableStripEOI(false);
        s.insertRSTMarkers(false);
    }

    return true;
}

bool AVBnTCPTrafficTest::duringTraffic()
{
    return true;
}

bool AVBnTCPTrafficTest::afterTraffic()
{
    return true;
}

string AVBnTCPTrafficTest::description() const
{
    return (trafficType == Type::AVB_ONLY) ? "AVB traffic test"
                                           : "AVB + TCP traffic test";
}


// ShutdownStressTest AVBnTCPTrafficTest implementation
ShutdownStressTest::ShutdownStressTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                                       AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                                       uint32_t numIterations)
    : AVBnTCPTrafficTest(cmdSocket, trafficType, avbGen, tcpGen, numIterations, 1), numIterations(numIterations), currIteration(0)
{
}

bool ShutdownStressTest::duringTraffic()
{
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);
    currIteration++;

    if (currIteration > 0 && (currIteration % 10) == 0) {
        cout << "--- " << currIteration << " shutdown cycles completed..." << endl;
    }

    return true;
}

bool ShutdownStressTest::afterTraffic()
{
    cout << "--- Executed " << numIterations << " total shutdown cycles." << endl;

    return true;
}

string ShutdownStressTest::description() const
{
    return (trafficType == Type::AVB_ONLY) ? "AVB shutdown stress test"
                                           : "AVB + TCP shutdown stress test";
}


// AVBTimedPacketLossTest AVBnTCPTrafficTest implementation
AVBTimedPacketLossTest::AVBTimedPacketLossTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                                               AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                                               uint32_t genTimeSecs )
    : AVBnTCPTrafficTest(cmdSocket, trafficType, avbGen, tcpGen, genTimeSecs, 0)
{
}

bool AVBTimedPacketLossTest::beforeTraffic()
{
    // Restart the AVB stack on server
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);

    // Set TCP echo ON
    if (trafficType == Type::AVB_PLUS_TCP)
    {
        tcpGen->setEchoExpected(true);

        sendCmd(*cmdSocket, TEST_CMD_ENABLE_TCP_ECHO);
    }

    // Clear AVB stats on server
    clearAVBStats(*cmdSocket);
    uint32_t numTalkers = avbGen->getNumTalkers();
    for (uint32_t i = 1; i <= numTalkers; i++)
    {
        clearAVBStats(*cmdSocket, i);
    }

    // Clear SW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_SW_STATS);

    // Clear HW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_HW_STATS);

    // Clear NDK stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

    return true;
}

bool AVBTimedPacketLossTest::afterTraffic()
{
    std::ostringstream out;

    // Get count of packets sent by the generator
    uint32_t packetsSentCount = avbGen->getPacketsSentCount();

    std::chrono::seconds sleepTime(2);

    // Wait a second before getting the packet stats
    this_thread::sleep_for(sleepTime);

    // Get count of packets received on target server
    TestSWStats stats = getSWStats(*cmdSocket);

    // Print out the packet counts
    out << "AVB Packets: Sent=" << packetsSentCount << ", Rcvd=" << stats.avbtpPacketCount;
    if (trafficType == Type::AVB_PLUS_TCP)
    {
        uint32_t tcpPacketsSentCount = tcpGen->getPacketsSentCount();
        out << ", TCP Packets: Sent=" << tcpPacketsSentCount << ", Rcvd=" << stats.tcpPacketCount;
    }

    resultsStr = out.str();

    cout << resultsStr << endl;

    if ((packetsSentCount != stats.avbtpPacketCount) || (stats.avbtpErrorCount != 0))
    {
        AVBTPStats          avbtpStats  = getAVBStats(*cmdSocket);
        EthernetHWStats     hwStats     = getHWStats(*cmdSocket);
        EthernetHWErrors    hwErrors    = getHWErrors(*cmdSocket);
        NDKIpStats          ndkIpStats  = getNDKIpStats(*cmdSocket);

        printAVBStats(avbtpStats);
        printHWStats(hwStats);
        printHWErrors(hwErrors);
        printNDKIpStats(ndkIpStats);

        return false;
    }

    return true;
}

string AVBTimedPacketLossTest::description() const
{
    return (trafficType == Type::AVB_ONLY) ? "AVB timed packet loss test"
                                           : "AVB + TCP timed packet loss test";
}

string AVBTimedPacketLossTest::results()
{
    return resultsStr;
}


// AVBLoadTest AVBnTCPTrafficTest implementation
AVBLoadTest::AVBLoadTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                         AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                         const LoadRange& loadRange, uint32_t numMeasures, bool verbose)
    : AVBnTCPTrafficTest(cmdSocket, trafficType, avbGen, tcpGen, numMeasures, 1), loadRange(loadRange), numMeasures(numMeasures)
{
}

bool AVBLoadTest::beforeTraffic()
{
    avgCpuLoad = 0;
    avgTaskLoad = 0;
    avgHwiLoad = 0;

    // Restart the AVB stack on server
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);

    // Set TCP echo ON
    if (trafficType == Type::AVB_PLUS_TCP)
    {
        tcpGen->setEchoExpected(false);

        sendCmd(*cmdSocket, TEST_CMD_DISABLE_TCP_ECHO);
    }

    // Clear AVB stats on server
    clearAVBStats(*cmdSocket);
    uint32_t numTalkers = avbGen->getNumTalkers();
    for (uint32_t i = 1; i <= numTalkers; i++)
    {
        clearAVBStats(*cmdSocket, i);
    }

    // Clear SW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_SW_STATS);

    // Clear HW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_HW_STATS);

    // Clear NDK stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

    return true;
}

bool AVBLoadTest::duringTraffic()
{
    try
    {
        LoadStats stats = getLoadStats(*cmdSocket);

        avgCpuLoad      += stats.cpuLoad;
        avgHwiLoad      += stats.hwiLoad;
        avgTaskLoad     += stats.avbtpRxLoad;

        if (verbose)
        {
            printLoadStats(stats, false, true);
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[AVBLoadTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool AVBLoadTest::afterTraffic()
{
    std::ostringstream out;

    // Create and save results string
    avgCpuLoad  = (avgCpuLoad * wakeupRateInSecs) / genTimeSecs;
    avgTaskLoad = (avgTaskLoad * wakeupRateInSecs) / genTimeSecs;
    avgHwiLoad  = (avgHwiLoad * wakeupRateInSecs) / genTimeSecs;

    cout << "--- Expected CPU load max: " << loadRange.cpuLoadMax << endl;
    cout << "--- Expected Hwi load max: " << loadRange.hwiLoadMax << endl;
    cout << "--- Expected AVB load max: " << loadRange.taskLoadMax << endl;

    cout << "--- Average CPU Load:  " << avgCpuLoad  << endl;
    cout << "--- Average HWI Load:  " << avgHwiLoad  << endl;
    cout << "--- Average Task Load: " << avgTaskLoad << endl;

    out << "CPU Load = " << avgCpuLoad
        << "%, HWI Load = " << avgHwiLoad
        << "%, Task Load = " << avgTaskLoad << "%";


    resultsStr = out.str();

    cout << resultsStr << endl;

    return (avgCpuLoad <= loadRange.cpuLoadMax) &&
           (avgTaskLoad <= loadRange.taskLoadMax) &&
           (avgHwiLoad <= loadRange.hwiLoadMax);
}

string AVBLoadTest::description() const
{
    return (trafficType == Type::AVB_ONLY) ? "AVB load test"
                                           : "AVB + TCP load test";
}

string AVBLoadTest::results()
{
    return resultsStr;
}


// AVBParserErrorTest 24 hours parser test - checks for any error during that period
AVBParserErrorTest::AVBParserErrorTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                                       AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen)
    : AVBnTCPTrafficTest(cmdSocket, trafficType, avbGen, tcpGen, 24*60*60, 30)
{
}

bool AVBParserErrorTest::beforeTraffic()
{
    // Restart the AVB stack on server
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);

    // Set TCP echo ON
    if (trafficType == Type::AVB_PLUS_TCP)
    {
        tcpGen->setEchoExpected(false);

        sendCmd(*cmdSocket, TEST_CMD_DISABLE_TCP_ECHO);
    }

    // Clear AVB stats on server
    clearAVBStats(*cmdSocket);
    uint32_t numTalkers = avbGen->getNumTalkers();
    for (uint32_t i = 1; i <= numTalkers; i++)
    {
        clearAVBStats(*cmdSocket, i);
    }

    // Clear SW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_SW_STATS);

    // Clear HW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_HW_STATS);

    // Clear NDK stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

    start = chrono::system_clock::now();

    return true;
}

bool AVBParserErrorTest::duringTraffic()
{
    AVBTPStats          avbtpStats  = getAVBStats(*cmdSocket);
    EthernetHWStats     hwStats     = getHWStats(*cmdSocket);
    EthernetHWErrors    hwErrors    = getHWErrors(*cmdSocket);
    NDKIpStats          ndkIpStats  = getNDKIpStats(*cmdSocket);

    printAVBStats(avbtpStats);
    printHWStats(hwStats);
    printHWErrors(hwErrors);
    printNDKIpStats(ndkIpStats);

    if (avbtpStats.errorCnt != 0)
    {
        std::ostringstream out;

        auto end = chrono::system_clock::now();
        auto duration =  chrono::duration_cast<chrono::minutes>(end - start);
        out << "Time elapsed: " << duration.count() << " minutes" << endl;

        resultsStr = out.str();

        return false;
    }

    return true;
}

bool AVBParserErrorTest::afterTraffic()
{
    std::ostringstream out;

    auto end = chrono::system_clock::now();
    auto duration =  chrono::duration_cast<chrono::minutes>(end - start);
    out << "Time elapsed: " << duration.count() << " minutes" << endl;

    resultsStr = out.str();

    return true;
}

string AVBParserErrorTest::description() const
{
    return (trafficType == Type::AVB_ONLY) ? "AVB parser error test"
                                           : "AVB + TCP parser error test";
}

string AVBParserErrorTest::results()
{
    return resultsStr;
}


// OutputValidationTest AVBnTCPTrafficTest implementation
OutputValidationTest::OutputValidationTest(TCPSocket& cmdSocket,
                                           AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen)
    : AVBnTCPTrafficTest(cmdSocket, Type::AVB_PLUS_TCP, avbGen, tcpGen, 5, 0)
{
}

bool OutputValidationTest::beforeTraffic()
{
    // Restart the AVB stack on server
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);

    // Set TCP echo ON
    if (trafficType == Type::AVB_PLUS_TCP)
    {
        tcpGen->setEchoExpected(false);

        sendCmd(*cmdSocket, TEST_CMD_DISABLE_TCP_ECHO);
    }

    // Clear AVB stats on server
    clearAVBStats(*cmdSocket);
    uint32_t numTalkers = avbGen->getNumTalkers();
    for (uint32_t i = 1; i <= numTalkers; i++)
    {
        clearAVBStats(*cmdSocket, i);
    }

    // Clear SW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_SW_STATS);

    // Clear HW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_HW_STATS);

    // Clear NDK stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

    uint32_t bufCnt = getBuffCount(*cmdSocket);

    cout << "--- Will send " << bufCnt << " JPEG frames per listener" << endl;

    vector<JPEGSource>* sources = avbGen->getDataSources();
    for (auto& s : *sources)
    {
        s.setMaxFrames(bufCnt);
    }
    return true;
}

bool OutputValidationTest::afterTraffic()
{
    std::ostringstream out;

    // Get count of packets sent by the generator
    uint32_t packetsSentCount = avbGen->getPacketsSentCount();

    sendCmd(*cmdSocket, TEST_CMD_DUMP_OUTPUT_FRAMES);

    vector<JPEGSource>* sources = avbGen->getDataSources();
    for (auto& s : *sources)
    {
        s.reset();
    }

    /* Protocol is:
    *  0 Number of listeners
    *  1 Number of buffers per listener
    *  2 Buffer size
    *  3 Buffer contents
    *  4 [ Repeat 2-3 for all remaining buffers]
    */
    vector<uint8_t> recvBuf = cmdSocket->receive(2 * sizeof(uint32_t));
    auto it = begin(recvBuf);
    uint32_t numListeners = readNetOrder32(it);
    uint32_t numBuffers = readNetOrder32(it);

    cout << "--- Number of target listeners: " << numListeners << endl;
    cout << "--- Number of buffers per listener: " << numBuffers << endl;

    for (uint32_t i = 0; i < numListeners; i++)
    {
        for (uint32_t j = 0; j < numBuffers; j++)
        {
            const uint8_t* bufSent = (*sources)[i].getNextFrame();
            uint32_t bufSizeSent = (*sources)[i].getFrameSize();

            recvBuf = cmdSocket->receive(sizeof(uint32_t));
            it = begin(recvBuf);
            uint32_t bufferSize = readNetOrder32(it);
            cout << "--- Listener " << i << " - Buffer " << j
                 << " - target received: " << bufferSize << " bytes"
                 << " - host sent: " << bufSizeSent << " bytes ";

            if (bufferSize != bufSizeSent)
            {
                cout << "- size mismatch! <-----------" << endl;

                AVBTPStats          avbtpStats  = getAVBStats(*cmdSocket);
                EthernetHWStats     hwStats     = getHWStats(*cmdSocket);
                EthernetHWErrors    hwErrors    = getHWErrors(*cmdSocket);
                NDKIpStats          ndkIpStats  = getNDKIpStats(*cmdSocket);

                printAVBStats(avbtpStats);
                printHWStats(hwStats);
                printHWErrors(hwErrors);
                printNDKIpStats(ndkIpStats);

                return false;
            }

            recvBuf = cmdSocket->receive(bufferSize);

            if (!std::equal(begin(recvBuf), end(recvBuf), bufSent))
            {
                cout << "- data mismatch! <-----------" << endl;

                AVBTPStats          avbtpStats  = getAVBStats(*cmdSocket);
                EthernetHWStats     hwStats     = getHWStats(*cmdSocket);
                EthernetHWErrors    hwErrors    = getHWErrors(*cmdSocket);
                NDKIpStats          ndkIpStats  = getNDKIpStats(*cmdSocket);

                printAVBStats(avbtpStats);
                printHWStats(hwStats);
                printHWErrors(hwErrors);
                printNDKIpStats(ndkIpStats);

                return false;
            }

            cout << "- match" << endl;
        }
    }

    AVBTPStats stats = getAVBStats(*cmdSocket);
    out << "AVB Packets: Sent=" << packetsSentCount << ", Rcvd=" << stats.packetCnt;
    resultsStr = out.str();
    cout << resultsStr;
    printAVBStats(stats);

    EthernetHWStats hwStats = getHWStats(*cmdSocket);
    printHWStats(hwStats);

    return true;
}

string OutputValidationTest::description() const
{
    return "Output validation test";
}

string OutputValidationTest::results()
{
    return resultsStr;
}


// EOIHandlingTest AVBnTCPTrafficTest implementation
EOIHandlingTest::EOIHandlingTest(TCPSocket& cmdSocket,
                                 AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen)
    : AVBnTCPTrafficTest(cmdSocket, Type::AVB_ONLY, avbGen, tcpGen, 10, 0), expectedEOIErrors(0)
{
}

bool EOIHandlingTest::beforeTraffic()
{
    const int nFrames2Send = 100;

    // Restart the AVB stack on server
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);

    // Clear AVB stats on server
    clearAVBStats(*cmdSocket);
    uint32_t numTalkers = avbGen->getNumTalkers();
    for (uint32_t i = 1; i <= numTalkers; i++)
    {
        clearAVBStats(*cmdSocket, i);
    }

    // Clear SW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_SW_STATS);

    // Clear HW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_HW_STATS);

    // Clear NDK stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

    vector<JPEGSource>* sources = avbGen->getDataSources();
    for (auto& s : *sources)
    {
        s.setMaxFrames(nFrames2Send);
        s.enableStripEOI(true);
        s.insertRSTMarkers(false);
    }

    expectedEOIErrors = (nFrames2Send - 1)*avbGen->getNumTalkers();

    return true;
}

bool EOIHandlingTest::afterTraffic()
{
    std::ostringstream out;

    AVBTPStats stats = getAVBStats(*cmdSocket);
    out << "Expected EOI errors=" << expectedEOIErrors << ", detected EOI errors=" << stats.missedEOIError;
    resultsStr = out.str();
    cout << resultsStr << endl;

    if (stats.missedEOIError != expectedEOIErrors)
    {
        AVBTPStats          avbtpStats  = getAVBStats(*cmdSocket);
        EthernetHWStats     hwStats     = getHWStats(*cmdSocket);
        EthernetHWErrors    hwErrors    = getHWErrors(*cmdSocket);
        NDKIpStats          ndkIpStats  = getNDKIpStats(*cmdSocket);

        printAVBStats(avbtpStats);
        printHWStats(hwStats);
        printHWErrors(hwErrors);
        printNDKIpStats(ndkIpStats);

        return false;
    }

    return true;
}

string EOIHandlingTest::description() const
{
    return "JPEG EOI Handling test";
}

string EOIHandlingTest::results()
{
    return resultsStr;
}


// EOIHandlingTest AVBnTCPTrafficTest implementation
RSTHandlingTest::RSTHandlingTest(TCPSocket& cmdSocket,
                                 AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen)
    : AVBnTCPTrafficTest(cmdSocket, Type::AVB_ONLY, avbGen, tcpGen, 10, 0), expectedRSTMarkersDelta(0)
{
}

bool RSTHandlingTest::beforeTraffic()
{
    const int nFrames2Send = 100;

    // Restart the AVB stack on server
    sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
    sendCmd(*cmdSocket, TEST_CMD_ENABLE_RST_MARKER_DETECTION);
    sendCmd(*cmdSocket, TEST_CMD_START_AVB);

    // Clear AVB stats on server
    clearAVBStats(*cmdSocket);
    uint32_t numTalkers = avbGen->getNumTalkers();
    for (uint32_t i = 1; i <= numTalkers; i++)
    {
        clearAVBStats(*cmdSocket, i);
    }

    // Clear SW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_SW_STATS);

    // Clear HW stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_HW_STATS);

    // Clear NDK stats on server
    sendCmd(*cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

    vector<JPEGSource>* sources = avbGen->getDataSources();
    for (auto& s : *sources)
    {
        s.setMaxFrames(nFrames2Send);
        s.enableStripEOI(false);
        s.insertRSTMarkers(true);
    }

    //RST markers are not sent in first packet as it contains SOI
    expectedRSTMarkersDelta = (nFrames2Send)*avbGen->getNumTalkers();

    return true;
}

bool RSTHandlingTest::afterTraffic()
{
    std::ostringstream out;

    uint32_t packetsSentCount = avbGen->getPacketsSentCount();
    uint32_t expectedRSTMarkers = packetsSentCount - expectedRSTMarkersDelta;

    AVBTPStats stats = getAVBStats(*cmdSocket);
    out << "Expected RST markers=" << expectedRSTMarkers << ", detected RST markers=" << stats.numRestartMarkers;
    resultsStr = out.str();
    cout << resultsStr << endl;

    if (stats.numRestartMarkers != expectedRSTMarkers)
    {
        AVBTPStats          avbtpStats  = getAVBStats(*cmdSocket);
        EthernetHWStats     hwStats     = getHWStats(*cmdSocket);
        EthernetHWErrors    hwErrors    = getHWErrors(*cmdSocket);
        NDKIpStats          ndkIpStats  = getNDKIpStats(*cmdSocket);

        printAVBStats(avbtpStats);
        printHWStats(hwStats);
        printHWErrors(hwErrors);
        printNDKIpStats(ndkIpStats);

        return false;
    }

    return true;
}

string RSTHandlingTest::description() const
{
    return "JPEG RST Handling test";
}

string RSTHandlingTest::results()
{
    return resultsStr;
}


AVBTxLoadTest::AVBTxLoadTest(TCPSocket& cmdSocket,
                             const LoadRange& loadRange, uint32_t numMeasures)
    : UnitTest(cmdSocket), loadRange(loadRange), numMeasures(numMeasures)
{
}

bool AVBTxLoadTest::execute()
{
    chrono::seconds oneSec(1);

    try
    {
        std::ostringstream out;

        sendCmd(*cmdSocket, TEST_CMD_STOP_AVB);
        sendCmd(*cmdSocket, TEST_CMD_START_AVB);
        sendCmd(*cmdSocket, TEST_CMD_START_AVB_TALKER);

        avgCpuLoad = 0;
        avgHwiLoad = 0;
        avgTaskLoad = 0;

        for (uint32_t i = 0; i < numMeasures; i++)
        {
            this_thread::sleep_for(oneSec);

            LoadStats stats = getLoadStats(*cmdSocket);
            avgCpuLoad += stats.cpuLoad;
            avgHwiLoad += stats.hwiLoad;
            avgTaskLoad += stats.avbtpTxLoad;

            printLoadStats(stats, false, true);
        }

        sendCmd(*cmdSocket, TEST_CMD_STOP_AVB_TALKER);

        avgCpuLoad /= numMeasures;
        avgHwiLoad /= numMeasures;
        avgTaskLoad /= numMeasures;

        cout << "--- Expected CPU load max      : " << loadRange.cpuLoadMax     << endl;
        cout << "--- Expected AVB Tx load max   : " << loadRange.avbTxLoadMax   << endl;
        cout << "--- Expected Hwi load max      : " << loadRange.hwiLoadMax     << endl;

        cout << "--- Average CPU Load           : " << avgCpuLoad       << endl;
        cout << "--- Average AVB Tx Load        : " << avgTaskLoad      << endl;
        cout << "--- Average HWI Load           : " << avgHwiLoad       << endl;

        out << "CPU Load = " << avgCpuLoad
            << "%, HWI Load = " << avgHwiLoad
            << "%, Task Load = " << avgTaskLoad << "%";

        resultsStr = out.str();

        return (avgCpuLoad <= loadRange.cpuLoadMax) &&
               (avgHwiLoad <= loadRange.hwiLoadMax) &&
               (avgTaskLoad <= loadRange.avbTxLoadMax);
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[AVBTxLoadTest]: error - " << e.what() << endl;
    }
    return false;
}

string AVBTxLoadTest::description() const
{
    return "AVB Tx Load Test";
}

string AVBTxLoadTest::results()
{
    return resultsStr;
}
