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

// Legacy C headers
#include <cstdlib>

// Local project headers
#include "TestClient.hpp"
#include "Packet.hpp"
#include "Socket.hpp"
#include "Options.hpp"
#include "TrafficGenerator.hpp"
#include "DataSource.hpp"
#include "../../common/test_common.h"

using namespace std;
using namespace test;

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
    uint32_t null2nspRxLoad;
    uint32_t null2nspTxLoad;
};

static void sendCmd(const TCPSocket *cmdSocket, const Packet& p)
{
    cmdSocket->send(p);

    vector<uint8_t> recvBuf = cmdSocket->receive(p.size());
    if (!std::equal(begin(recvBuf), end(recvBuf), p.data())) {
        throw TCPSocket::Error("No ACK received!");
    }
}

static void sendCmd(const TCPSocket *cmdSocket, uint32_t cmdId)
{
    CommandPacket p(cmdId);
    sendCmd(cmdSocket, p);
}

#if (0)
static void sendCmd(const TCPSocket *cmdSocket, uint32_t cmdId, uint32_t param)
{
    CommandPacket p(cmdId, param);
    sendCmd(cmdSocket, p);
}
#endif

static uint32_t readNetOrder32(vector<uint8_t>::iterator& it)
{
    uint32_t val = it[0] | (it[1] << 8) | (it[2] << 16) | (it[3] << 24);
    it += sizeof(uint32_t);
    return ntohl(val);
}

static TestSWStats getSWStats(TCPSocket *cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_SW_STATS);

    TestSWStats stats;
    vector<uint8_t> recvBuf = cmdSocket->receive(sizeof(TestSWStats));

    auto it = begin(recvBuf);
    stats.tcpPacketCount = readNetOrder32(it);
    stats.udpPacketCount = readNetOrder32(it);
    stats.rawPacketCount = readNetOrder32(it);
    stats.cptsEventCount = readNetOrder32(it);

    return stats;
}

static CPTSEvent getCPTSEvent(TCPSocket *cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_CPTS_EVENT);

    CPTSEvent event;

    vector<uint8_t> recvBuf = cmdSocket->receive(5 * sizeof(uint32_t));

    auto it = begin(recvBuf);
    event.eventType = readNetOrder32(it);
    event.messageType = readNetOrder32(it);
    event.sequenceID = readNetOrder32(it);

    uint32_t timestampHi = readNetOrder32(it);
    uint32_t timestampLo = readNetOrder32(it);
    event.timestamp = (((uint64_t)timestampHi) << 32) | ((uint64_t)timestampLo);

    return event;
}

static EthernetHWErrors getHWErrors(TCPSocket *cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_HW_ERRORS);

    EthernetHWErrors errors;
    vector<uint8_t> recvBuf = cmdSocket->receive(sizeof(EthernetHWErrors));

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
    cout << "----- start of frame overruns: " << errors.RxSOFOverruns << endl;
    cout << "----- middle of frame overruns: " << errors.RxMOFOverruns << endl;
    cout << "----- DMA overruns: " << errors.RxDMAOverruns << endl;
    cout << "----- CRC errors: " << errors.RxCRCErrors << endl;
    cout << "----- aligment errors: " << errors.RxAlignCodeErrors << endl;
    cout << "----- oversized frames: " << errors.RxOversized << endl;
    cout << "----- jabber frames: " << errors.RxJabber << endl;
    cout << "----- undersized frames: " << errors.RxUndersized << endl;
    cout << "----- fragments " << errors.RxFragments << endl;
}

static EthernetHWStats getHWStats(TCPSocket *cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_HW_STATS);

    EthernetHWStats stats;
    vector<uint8_t> recvBuf = cmdSocket->receive(sizeof(EthernetHWStats));

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

static NDKIpStats getNDKIpStats(TCPSocket *cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_NDK_STATS);

    NDKIpStats stats;
    vector<uint8_t> recvBuf = cmdSocket->receive(sizeof(NDKIpStats));

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

static LoadStats getLoadStats(TCPSocket *cmdSocket)
{
    sendCmd(cmdSocket, TEST_CMD_GET_LOAD_INFO);

    LoadStats stats;
    vector<uint8_t> recvBuf = cmdSocket->receive(sizeof(LoadStats));

    auto it = begin(recvBuf);
    stats.cpuLoad           = readNetOrder32(it);
    stats.hwiLoad           = readNetOrder32(it);
    stats.ndk2nspRxLoad     = readNetOrder32(it);
    stats.ndk2nspTxLoad     = readNetOrder32(it);
    stats.null2nspRxLoad    = readNetOrder32(it);
    stats.null2nspTxLoad    = readNetOrder32(it);

    return stats;
}

static void printLoadStats(const LoadStats& stats, bool printNDKStats = false, bool printNULLStats = false)
{
    cout << "--- CPU Load    : " << setfill('0') << setw(3) << stats.cpuLoad << "%" << endl;
    cout << "  - HWI Load    : " << setfill('0') << setw(3) << stats.hwiLoad << "%" << endl;
    if (printNDKStats)
    {
        cout << "  - NDK Rx Load : " << setfill('0') << setw(3) << stats.ndk2nspRxLoad << "%" << endl;
        cout << "  - NDK Tx Load : " << setfill('0') << setw(3) << stats.ndk2nspTxLoad << "%" << endl;
    }
    if (printNULLStats)
    {
        cout << "  - NULL Rx Load: " << setfill('0') << setw(3) << stats.null2nspRxLoad << "%" << endl;
        cout << "  - NULL Tx Load: " << setfill('0') << setw(3) << stats.null2nspTxLoad << "%" << endl;
    }
}

const string TestClient::TEST_CMD_QDISC_CLASS = "1:1";
const string TestClient::TEST_CMD_QDISC_RATE  = "10mbit";
const string TestClient::TEST_CMD_QDISC_PRIO  = "1";

TestClient::TestClient(Options& opts)
    : opts(&opts)
{
    int numLoadMeasures     = opts.getInt("num-load-measures");
    int numShutdowns        = opts.getInt("num-shutdowns");

    // Create the command TCP socket
    cmdSocket = new TCPSocket(opts.get("ip"), to_string(TEST_CMD_PORT));
    cmdSocket->setRcvTimeout(5);

    // Lookup MAC address from the IP address (now that command socket exists)
    MACAddress dstMac = getTargetMAC(opts.get("ip"), opts.get("dev"));

    // Setup qdisc traffic management
    vector<string> tokens = tokenize(RawTrafficGenerator::TEST_RAW_QDISC_CLASS, ':');
    auto subClassNum = stoi(tokens.at(1));

    tcManager = new TrafficClassManager(opts.get("dev"), opts.getBool("verbose"), subClassNum);

    tcManager->setClass(
        TestClient::TEST_CMD_QDISC_CLASS,
        TestClient::TEST_CMD_QDISC_RATE,
        TestClient::TEST_CMD_QDISC_PRIO);
    tcManager->setClass(TCPTrafficGenerator::TEST_TCP_QDISC_CLASS, "10mbit", to_string(2));
    tcManager->setClass(UDPTrafficGenerator::TEST_UDP_QDISC_CLASS, "10mbit", to_string(3));
    tcManager->setClass(RawTrafficGenerator::TEST_RAW_QDISC_CLASS, "10mbit", to_string(4));

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

    // We don't set a filter for RawTrafficGenerator::TEST_RAW_QDISC_CLASS
    // since it will be used as the default class. Ideally we would set a filter
    // to classify off of the Ethertype, or VLAN tags, but that has proven to be
    // difficult to work out how to do with the tc command.
#if (0)
    filter = "u32 match u16 " + int_to_hex(RawPacket::ETHER_TYPE_EXPERIMENTAL) + " 0xffff at -2 " +
             "match u16 0x8100 0xffff at -6";
    tcManager->setFilter(
        "ip",
        filter,
        RawTrafficGenerator::TEST_RAW_QDISC_CLASS);
#endif

    // Create the TCP/IP traffic generator
    tcpGen = new TCPTrafficGenerator(opts.get("ip"), opts.get("tcp-port"), *tcManager, opts.getBool("verbose"));

    // Create the UDP traffic generator
    udpGen = new UDPTrafficGenerator(opts.get("ip"), opts.get("udp-port"), *tcManager, opts.getBool("verbose"));

    // Create the raw traffic generator
    rawGen = new RawTrafficGenerator(opts.get("dev"), dstMac, *tcManager, opts.getBool("verbose"));

    // Register all tests

    // Register CPTS Frequency Check Unit Test (always run)
    unique_ptr<UnitTest> cptsFreqTest =
        make_unique<CPTSFreqCheckTest>(cmdSocket);
    tests.push_back(std::move(cptsFreqTest));

    // Register the CPTS Rx Ethernet Event Unit Test (always run)
    unique_ptr<UnitTest> cptsRxEventTest =
        make_unique<CPTSRxEthernetEventTest>(cmdSocket, opts.get("dev"), dstMac);
    tests.push_back(std::move(cptsRxEventTest));

    // Register the CPTS Tx Ethernet Event Unit Test (always run)
    unique_ptr<UnitTest> cptsTxEventTest =
        make_unique<CPTSTxEthernetEventTest>(cmdSocket, opts.get("dev"), dstMac);
    tests.push_back(std::move(cptsTxEventTest));

    // Performance tests
    if (opts.getBool("run-perf-tests"))
    {
        std::vector<uint32_t> bitrates      = {1,20};
        std::vector<uint32_t> packetSizes   = {750};

#if (0)
        // TCP Non-Echo Performance Tests
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> tcpPerformanceTest =
                    make_unique<TCPPerformanceTest>(cmdSocket, *tcpGen, bitrate, packetSize);
                tests.push_back(std::move(tcpPerformanceTest));
            }
        }

        bitrates      = {2,40};
        packetSizes   = {1500};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> tcpPerformanceTest =
                    make_unique<TCPPerformanceTest>(cmdSocket, *tcpGen, bitrate, packetSize);
                tests.push_back(std::move(tcpPerformanceTest));
            }
        }
#endif

        // TCP Echo Performance Tests
        bitrates        = {5,10};
        packetSizes     = {1500};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> tcpPerformanceTest =
                    make_unique<TCPPerformanceTest>(cmdSocket, *tcpGen, bitrate, packetSize, true);
                tests.push_back(std::move(tcpPerformanceTest));
            }
        }

        // UDP Non-Echo Performance Tests
        bitrates        = {5,15,30};
        packetSizes     = {750};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> udpPerformanceTest =
                    make_unique<UDPPerformanceTest>(cmdSocket, *udpGen, bitrate, packetSize);
                tests.push_back(std::move(udpPerformanceTest));
            }
        }

        bitrates        = {10,30,60};
        packetSizes     = {1500};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> udpPerformanceTest =
                    make_unique<UDPPerformanceTest>(cmdSocket, *udpGen, bitrate, packetSize);
                tests.push_back(std::move(udpPerformanceTest));
            }
        }

        // UDP Echo Performance Tests
        bitrates        = {5,15,20};
        packetSizes     = {1500};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> udpPerformanceTest =
                    make_unique<UDPPerformanceTest>(cmdSocket, *udpGen, bitrate, packetSize, true);
                tests.push_back(std::move(udpPerformanceTest));
            }
        }

        // Raw via NDK Sockets Performance Test
        bitrates        = {5,25,50};
        packetSizes     = {750};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> rawPerformanceTest =
                    make_unique<RawPerformanceTest>(cmdSocket, *rawGen, bitrate, packetSize, false);
                tests.push_back(std::move(rawPerformanceTest));
            }
        }

        bitrates        = {10,50,100};
        packetSizes     = {1500};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> rawPerformanceTest =
                    make_unique<RawPerformanceTest>(cmdSocket, *rawGen, bitrate, packetSize, false);
                tests.push_back(std::move(rawPerformanceTest));
            }
        }


        // RAW via NULL stack Performance Test
        bitrates        = {250,300,350,400,450};
        packetSizes     = {750};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> rawPerformanceTest =
                    make_unique<RawPerformanceTest>(cmdSocket, *rawGen, bitrate, packetSize, true);
                tests.push_back(std::move(rawPerformanceTest));
            }
        }

        bitrates        = {500,600,700,800,900};
        packetSizes     = {1500};
        for (auto bitrate : bitrates)
        {
            for (auto packetSize : packetSizes)
            {
                unique_ptr<UnitTest> rawPerformanceTest =
                    make_unique<RawPerformanceTest>(cmdSocket, *rawGen, bitrate, packetSize, true);
                tests.push_back(std::move(rawPerformanceTest));
            }
        }
    }


    // Load tests
    if (numLoadMeasures > 0)
    {
        //Maps core name to expected RX loads (TCP Rx only load numbers)
        map<string, TCPLoadTest::LoadRange> tcpRxLoadRangeMap
        {
            {"vayu-ipu1",       {12.0,  2.0, 10.0}},
            {"tda3xx-ipu1",      {12.0,  2.0, 10.0}},
            {"vayu-mpu",        {50.0, 10.0, 40.0}},
            {"j5eco-mc",        {12.0,  2.0, 10.0}},
            {"j5eco-mpu",       { 4.0,  1.0,  3.0}},
            {"centaurus-mc",    {12.0,  2.0, 10.0}},
            {"centaurus-mpu",   { 4.0,  1.0,  3.0}}
        };

        auto tcpRxLoadEntry = tcpRxLoadRangeMap.find(opts.get("core-name"));

        if (tcpRxLoadEntry == tcpRxLoadRangeMap.end())
        {
            throw runtime_error("invalid core name!");
        }

        unique_ptr<UnitTest> tcpRxLoadTest =
            make_unique<TCPLoadTest>(cmdSocket, *tcpGen, tcpRxLoadEntry->second, numLoadMeasures);
        tests.push_back(std::move(tcpRxLoadTest));

        //Maps core name to expected RX loads (TCP Rx+Tx only load numbers)
        map<string, TCPLoadTest::LoadRange> tcpRxTxLoadRangeMap
        {
            {"vayu-ipu1",       {28.0,  2.0, 10.0}},
            {"tda3xx-ipu1",       {28.0,  2.0, 10.0}},
            {"vayu-mpu",        {60.0, 10.0, 50.0}},
            {"j5eco-mc",        {28.0,  2.0, 10.0}},
            {"j5eco-mpu",       {10.0,  1.0,  5.0}},
            {"centaurus-mc",    {28.0,  2.0, 10.0}},
            {"centaurus-mpu",   {10.0,  1.0,  5.0}}
        };

        auto tcpRxTxLoadEntry = tcpRxTxLoadRangeMap.find(opts.get("core-name"));

        if (tcpRxTxLoadEntry == tcpRxTxLoadRangeMap.end())
        {
            throw runtime_error("invalid core name!");
        }

        unique_ptr<UnitTest> tcpRxTxLoadTest =
            make_unique<TCPLoadTest>(cmdSocket, *tcpGen, tcpRxTxLoadEntry->second, numLoadMeasures, true);
        tests.push_back(std::move(tcpRxTxLoadTest));

        //Maps core name to expected RX loads (TCP Rx only load numbers)
        map<string, UDPLoadTest::LoadRange> udpRxLoadRangeMap
        {
            {"vayu-ipu1",       {20.0,  2.0, 18.0}},
            {"tda3xx-ipu1",       {22.0, 2.0, 18.0}},
            {"vayu-mpu",        {20.0, 10.0, 40.0}},
            {"j5eco-mc",        {20.0,  2.0, 18.0}},
            {"j5eco-mpu",       { 6.0,  1.0,  3.0}},
            {"centaurus-mc",    {20.0,  2.0, 18.0}},
            {"centaurus-mpu",   { 6.0,  1.0,  3.0}}
        };

        auto udpRxLoadEntry = udpRxLoadRangeMap.find(opts.get("core-name"));

        if (udpRxLoadEntry == udpRxLoadRangeMap.end())
        {
            throw runtime_error("invalid core name!");
        }

        unique_ptr<UnitTest> udpRxLoadTest =
            make_unique<UDPLoadTest>(cmdSocket, *udpGen, udpRxLoadEntry->second, numLoadMeasures);
        tests.push_back(std::move(udpRxLoadTest));

        //Maps core name to expected RX loads (TCP Rx+Tx only load numbers)
        map<string, UDPLoadTest::LoadRange> udpRxTxLoadRangeMap
        {
            {"vayu-ipu1",       {45.0,  4.0, 41.0}},
            {"tda3xx-ipu1",      {50.0,  4.0, 41.0}},
            {"vayu-mpu",        {10.0, 10.0, 50.0}},
            {"j5eco-mc",        {45.0,  4.0, 41.0}},
            {"j5eco-mpu",       {10.0,  1.0,  3.0}},
            {"centaurus-mc",    {45.0,  4.0, 41.0}},
            {"centaurus-mpu",   {10.0,  1.0,  3.0}}
        };

        auto udpRxTxLoadEntry = udpRxTxLoadRangeMap.find(opts.get("core-name"));

        if (udpRxTxLoadEntry == udpRxTxLoadRangeMap.end())
        {
            throw runtime_error("invalid core name!");
        }

        unique_ptr<UnitTest> udpRxTxLoadTest =
            make_unique<UDPLoadTest>(cmdSocket, *udpGen, udpRxTxLoadEntry->second, numLoadMeasures, true);
        tests.push_back(std::move(udpRxTxLoadTest));
    }


    // Shutdown/Restart tests
    if (numShutdowns > 0)
    {
        // Register Driver shutdown test
        unique_ptr<UnitTest> stressTest =
            make_unique<ShutdownStressTest>(cmdSocket, numShutdowns);
        tests.push_back(std::move(stressTest));

        // Stack Register/Unregister Unit Test
        unique_ptr<UnitTest> stackRegistrationTest =
            make_unique<StackShutdownStressTest>(cmdSocket, numShutdowns);
        tests.push_back(std::move(stackRegistrationTest));

        // Register CPTS Register/Unregister Unit Test
        unique_ptr<UnitTest> cptsRegistrationTest =
            make_unique<CPTSShutdownStressTest>(cmdSocket, numShutdowns);
        tests.push_back(std::move(cptsRegistrationTest));
    }

}

TestClient::~TestClient()
{
    delete rawGen;
    delete udpGen;
    delete tcpGen;
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
UnitTest::UnitTest(TCPSocket *cmdSocket)
    : cmdSocket(cmdSocket)
{
}

UnitTest::~UnitTest() = default;

string UnitTest::results()
{
    return "";
}


// TrafficTest implementation
TrafficTest::TrafficTest(TCPSocket *cmdSocket, uint32_t genTimeSecs, uint32_t wakeupRateInSecs)
    : UnitTest(cmdSocket), genTimeSecs(genTimeSecs), wakeupRateInSecs(wakeupRateInSecs)
{
}

TrafficTest::~TrafficTest() = default;


// TCPTrafficTest implementation
TCPTrafficTest::TCPTrafficTest(TCPSocket *cmdSocket, TCPTrafficGenerator& tcpGen, uint32_t genTimeSecs, uint32_t wakeupRateInSecs)
    : TrafficTest(cmdSocket, genTimeSecs, wakeupRateInSecs), tcpGen(&tcpGen)
{
}

bool TCPTrafficTest::execute()
{
    try
    {
        if (!beforeTraffic()) return false;

        TrafficGenThread tcpThread(*tcpGen);

        tcpThread.start();

        if (genTimeSecs != 0)
        {
            cout << "--- Generating TCP traffic for " << genTimeSecs
                 << " seconds..." << endl;

            // Let traffic ramp up for three seconds
            std::chrono::seconds threeSecs(3);
            this_thread::sleep_for(threeSecs);

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

                    if (!duringTraffic()) return false;
                }
            }
            else
            {
                // Wake up rate is zero, do nothing during traffic
                std::chrono::seconds sleepTime(genTimeSecs);
                this_thread::sleep_for(sleepTime);
            }

            // Let traffic ramp down for three seconds
            this_thread::sleep_for(threeSecs);
        }

        tcpThread.stop();

        return afterTraffic();
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[TCPTrafficTest]: error - " << e.what() << endl;
    }
    return false;
}

bool TCPTrafficTest::beforeTraffic()
{
    tcpGen->setEchoExpected(true);

    return true;
}

bool TCPTrafficTest::duringTraffic()
{
    return true;
}

bool TCPTrafficTest::afterTraffic()
{
    return true;
}


// UDPTrafficTest implementation
UDPTrafficTest::UDPTrafficTest(TCPSocket *cmdSocket, UDPTrafficGenerator& udpGen, uint32_t genTimeSecs, uint32_t wakeupRateInSecs)
    : TrafficTest(cmdSocket, genTimeSecs, wakeupRateInSecs), udpGen(&udpGen)
{
}

bool UDPTrafficTest::execute()
{
    try
    {
        if (!beforeTraffic()) return false;

        TrafficGenThread udpThread(*udpGen);

        udpThread.start();

        if (genTimeSecs != 0)
        {
            cout << "--- Generating UDP traffic for " << genTimeSecs
                 << " seconds..." << endl;

            // Let traffic ramp up for three seconds
            std::chrono::seconds threeSecs(3);
            this_thread::sleep_for(threeSecs);

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

                    if (!duringTraffic()) return false;
                }
            }
            else
            {
                // Wake up rate is zero, do nothing during traffic
                std::chrono::seconds sleepTime(genTimeSecs);
                this_thread::sleep_for(sleepTime);
            }

            // Let traffic ramp down for three seconds
            this_thread::sleep_for(threeSecs);
        }

        udpThread.stop();

        return afterTraffic();
    }
    catch (UDPSocket::Error& e)
    {
        cout << "[UDPTrafficTest]: error - " << e.what() << endl;
    }
    return false;
}

bool UDPTrafficTest::beforeTraffic()
{
    udpGen->setEchoExpected(true);

    return true;
}

bool UDPTrafficTest::duringTraffic()
{
    return true;
}

bool UDPTrafficTest::afterTraffic()
{
    return true;
}


// ShutdownStressTest UnitTest implementation
ShutdownStressTest::ShutdownStressTest(TCPSocket *cmdSocket, uint32_t numIterations)
    : UnitTest(cmdSocket), numIterations(numIterations)
{
}

bool ShutdownStressTest::execute()
{
    std::chrono::seconds sleepTime(1);
    for (uint32_t i = 0; i < numIterations; i++)
    {
        // The RESTART_NSP command shuts down the stack on the target side,
        // so this host will get disconnected.
        // We attempt to reconnect at every iteration
        try
        {
            cout << "[ShutdownStressTest] restarting NSP..." << endl;
            sendCmd(cmdSocket, TEST_CMD_RESTART_NSP);

            // Wait a little before attempting reconnect
            this_thread::sleep_for(sleepTime);

            // Attempt reconnect during the TCPSocket timeout period
            cmdSocket->reconnect();

            if (i > 0 && (i % 10) == 0)
            {
                cout << "--- " << i << " shutdown cycles completed..." << endl;
            }
        }
        catch (TCPSocket::Error& e)
        {
            // Fail the test under any connection/socket errors.
            cout << "[ShutdownStressTest] error - " << e.what() << endl;
            return false;
        }
    }
    cout << "--- Executed " << numIterations << " total shutdown cycles." << endl;
    return true;
}

string ShutdownStressTest::description() const
{
    return "NSP driver shutdown stress test";
}


// StackShutdownStressTest UnitTest implementation
StackShutdownStressTest::StackShutdownStressTest(TCPSocket *cmdSocket, uint32_t numIterations)
    : UnitTest(cmdSocket), numIterations(numIterations)
{
}

bool StackShutdownStressTest::execute()
{
    std::chrono::seconds sleepTime(1);
    for (uint32_t i = 0; i < numIterations; i++)
    {
        try
        {
            cout << "[StackShutdownStressTest] starting NULL stack on top of NSP..." << endl;
            sendCmd(cmdSocket, TEST_CMD_START_NULL_STACK);

            // Wait a little before attempting reconnect
            this_thread::sleep_for(sleepTime);

            // ToDo: Send and verify traffic


            cout << "[StackShutdownStressTest] stopping NULL stack on top of NSP..." << endl;
            sendCmd(cmdSocket, TEST_CMD_STOP_NULL_STACK);


            if (i > 0 && (i % 10) == 0)
            {
                cout << "--- " << i << " start/stop cycles completed..." << endl;
            }
        }
        catch (TCPSocket::Error& e)
        {
            // Fail the test under any connection/socket errors.
            cout << "[StackShutdownStressTest] error - " << e.what() << endl;
            return false;
        }
    }
    cout << "--- Executed " << numIterations << " total start/stop cycles." << endl;
    return true;
}

string StackShutdownStressTest::description() const
{
    return "NULL stack start/stop stress test";
}


// CPTSShutdownStressTest UnitTest implementation
CPTSShutdownStressTest::CPTSShutdownStressTest(TCPSocket *cmdSocket, uint32_t numIterations)
    : UnitTest(cmdSocket), numIterations(numIterations)
{
}

bool CPTSShutdownStressTest::execute()
{
    std::chrono::seconds sleepTime(1);
    for (uint32_t i = 0; i < numIterations; i++)
    {
        try
        {
            cout << "[CPTSShutdownStressTest] registering CPTS handler..." << endl;
            sendCmd(cmdSocket, TEST_CMD_CPTS_REGISTER);

            // Wait a little before attempting reconnect
            this_thread::sleep_for(sleepTime);

            cout << "[CPTSShutdownStressTest] unregistering CPTS handler..." << endl;
            sendCmd(cmdSocket, TEST_CMD_CPTS_UNREGISTER);

            if (i > 0 && (i % 10) == 0)
            {
                cout << "--- " << i << " register/unregister cycles completed..." << endl;
            }
        }
        catch (TCPSocket::Error& e)
        {
            // Fail the test under any connection/socket errors.
            cout << "[CPTSShutdownStressTest] error - " << e.what() << endl;
            return false;
        }
    }
    cout << "--- Executed " << numIterations << " total register/unregister cycles." << endl;
    return true;
}

string CPTSShutdownStressTest::description() const
{
    return "CPTS register/unregister stress test";
}


// CPTSFreqCheckTest UnitTest implementation
CPTSFreqCheckTest::CPTSFreqCheckTest(TCPSocket *cmdSocket)
    : UnitTest(cmdSocket)
{
}

bool CPTSFreqCheckTest::execute()
{
    bool ret = true;
    std::chrono::seconds sleepTime(1);

    try
    {
        cout << "[CPTSFreqCheckTest] registering CPTS handler..." << endl;
        sendCmd(cmdSocket, TEST_CMD_CPTS_REGISTER);

        // Wait a little before attempting to check frequency
        this_thread::sleep_for(sleepTime);

        sendCmd(cmdSocket, TEST_CMD_CPTS_FREQ_CHECK);

        vector<uint8_t> recvBuf;
        recvBuf = cmdSocket->receive(2 * sizeof(uint32_t));

        auto start = begin(recvBuf);
        uint32_t measuredFreq = readNetOrder32(start);
        uint32_t reportedFreq = readNetOrder32(start);

        cout << "measured frequency = " << measuredFreq << endl;
        cout << "reported frequency = " << reportedFreq << endl;

        if ( ((measuredFreq *1.0F) > (0.98F * reportedFreq)) &&
             ((measuredFreq *1.0F) <= (1.02F * reportedFreq)) )
        {
            ret = true;
        }
        else
        {
            cout << "[CPTSFreqCheckTest] frequency mismatch..." << endl;

            ret = false;
        }

        cout << "[CPTSFreqCheckTest] unregistering CPTS handler..." << endl;
        sendCmd(cmdSocket, TEST_CMD_CPTS_UNREGISTER);
    }
    catch (TCPSocket::Error& e)
    {
        // Fail the test under any connection/socket errors.
        cout << "[CPTSFreqCheckTest] error - " << e.what() << endl;
        return false;
    }

    return ret;
}

string CPTSFreqCheckTest::description() const
{
    return "CPTS Frequency Check test";
}


// CPTSRxEthernetEventTest UnitTest implementation
CPTSRxEthernetEventTest::CPTSRxEthernetEventTest(TCPSocket *cmdSocket, std::string dev, MACAddress& dstMac)
    : UnitTest(cmdSocket), dev(std::move(dev)), dstMac(dstMac)
{
}

bool CPTSRxEthernetEventTest::execute()
{
    bool ret = true;
    std::chrono::seconds sleepTime(1);
    std::chrono::milliseconds interPacketTime(10);

    try
    {
        RawSocket rawSocket(dev, dstMac);
        MACAddress srcMac = rawSocket.getSrcMAC();
        CPTSPacket packet(srcMac, dstMac);

        cout << "[CPTSRxEthernetEventTest] registering CPTS handler..." << endl;
        sendCmd(cmdSocket, TEST_CMD_CPTS_REGISTER);

        // Clear all stats
        sendCmd(cmdSocket, TEST_CMD_CLEAR_SW_STATS);

        vector<uint8_t> messageTypes =
        {
            CPTSPacket::CPTS_MESSAGE_SYNC,
            CPTSPacket::CPTS_MESSAGE_SYNC,
            CPTSPacket::CPTS_MESSAGE_DELAY_REQ,
            CPTSPacket::CPTS_MESSAGE_PDELAY_REQ,
            CPTSPacket::CPTS_MESSAGE_PDELAY_RESP,
            CPTSPacket::CPTS_MESSAGE_FOLLOW_UP,
            CPTSPacket::CPTS_MESSAGE_DELAY_RESP,
            CPTSPacket::CPTS_MESSAGE_PDELAY_RESP_FOLLOW_UP,
            CPTSPacket::CPTS_MESSAGE_ANNOUNCE,
            CPTSPacket::CPTS_MESSAGE_SIGNALING,
            CPTSPacket::CPTS_MESSAGE_MANAGEMENT
        };

        // Wait a little before sending CPTS packets to generate CPTS events
        this_thread::sleep_for(sleepTime);

        for (auto messageType : messageTypes)
        {
            packet.setMessageType(messageType);
            packet.fill();
            rawSocket.send(packet);
            this_thread::sleep_for(interPacketTime);
        }

        // Wait a little before checking on the CPTS events
        this_thread::sleep_for(sleepTime);

        cout << "[CPTSRxEthernetEventTest]: sent Layer 2 CPTS/PTP frames" << endl;

        // Get count of CPTS event packets received on target server
        TestSWStats stats = getSWStats(cmdSocket);

        if (stats.cptsEventCount != messageTypes.size())
        {
            cout << "[CPTSRxEthernetEventTest]: Wrong number of CPTS events observed!" << endl;
            cout << "cptsEventCount = " << stats.cptsEventCount << endl;
            ret = false;
        }
        else
        {
            // Verify all events
            for(uint32_t i = 0; i < messageTypes.size(); i++)
            {
                CPTSEvent event = getCPTSEvent(cmdSocket);

                if ( (event.messageType != messageTypes[i]) ||
                     (event.sequenceID != i) ||
                     (event.eventType != 4U) )
                {
                    ret = false;
                    break;
                }
            }
        }

        sendCmd(cmdSocket, TEST_CMD_CPTS_UNREGISTER);
        cout << "[CPTSRxEthernetEventTest] unregistering CPTS handler..." << endl;
    }
    catch (TCPSocket::Error& e)
    {
        // Fail the test under any connection/socket errors.
        cout << "[CPTSRxEthernetEventTest] error - " << e.what() << endl;
        return false;
    }

    return ret;
}

string CPTSRxEthernetEventTest::description() const
{
    return "CPTS Rx Ethernet Event test";
}


// CPTSRxEthernetEventTest UnitTest implementation
CPTSTxEthernetEventTest::CPTSTxEthernetEventTest(TCPSocket *cmdSocket, std::string dev, MACAddress& dstMac)
    : UnitTest(cmdSocket), dev(std::move(dev)), dstMac(dstMac)
{

}

bool CPTSTxEthernetEventTest::execute()
{
    bool ret = true;
    std::chrono::seconds sleepTime(1);
    std::chrono::milliseconds interPacketTime(10);

    try
    {
        RawSocket rawSocket(dev, dstMac);
        MACAddress srcMac = rawSocket.getSrcMAC();
        CPTSPacket packet(srcMac, dstMac);

        vector<uint8_t> messageTypes =
        {
            CPTSPacket::CPTS_MESSAGE_SYNC,
            CPTSPacket::CPTS_MESSAGE_SYNC,
            CPTSPacket::CPTS_MESSAGE_DELAY_REQ,
            CPTSPacket::CPTS_MESSAGE_PDELAY_REQ,
            CPTSPacket::CPTS_MESSAGE_PDELAY_RESP,
            CPTSPacket::CPTS_MESSAGE_FOLLOW_UP,
            CPTSPacket::CPTS_MESSAGE_DELAY_RESP,
            CPTSPacket::CPTS_MESSAGE_PDELAY_RESP_FOLLOW_UP,
            CPTSPacket::CPTS_MESSAGE_ANNOUNCE,
            CPTSPacket::CPTS_MESSAGE_SIGNALING,
            CPTSPacket::CPTS_MESSAGE_MANAGEMENT
        };

        cout << "[CPTSTxEthernetEventTest] registering CPTS handler..." << endl;
        sendCmd(cmdSocket, TEST_CMD_CPTS_REGISTER);

        // Clear all stats
        sendCmd(cmdSocket, TEST_CMD_CLEAR_SW_STATS);

        // Wait a little before sending CPTS packets to generate CPTS events
        this_thread::sleep_for(sleepTime);

        // Send command to kick off test cycle
        sendCmd(cmdSocket, TEST_CMD_CPTS_SEND_ETH_TX);

        // Sleep and let the server set up the raw socket to receive the CPTS message
        this_thread::sleep_for(sleepTime);

        // Send one CPTS message to tell server we are ready
        packet.setMessageType(CPTSPacket::CPTS_MESSAGE_SYNC);
        packet.fill();
        rawSocket.send(packet);

        cout << "[CPTSTxEthernetEventTest]: sent one Layer 2 CPTS/PTP frames" << endl;

        // Sleep and let the server send CPTS frames to create CPTS Tx Ethernet Events
        this_thread::sleep_for(sleepTime);

        // Get count of CPTS event packets received on target server
        TestSWStats stats = getSWStats(cmdSocket);

        if (stats.cptsEventCount != messageTypes.size())
        {
            cout << "[CPTSTxEthernetEventTest]: Wrong number of CPTS events observed!" << endl;
            cout << "cptsEventCount = " << stats.cptsEventCount << endl;
            ret = false;
        }
        else
        {
            // Get the Event from the packet we sent
            CPTSEvent event = getCPTSEvent(cmdSocket);

            if ( (event.messageType != messageTypes[0]) ||
                 (event.sequenceID != 0U) ||
                 (event.eventType != 4U) )
            {
                cout << "[CPTSTxEthernetEventTest]: First CPTS event was incorrect!" << endl;
                cout << "eventType      = " << event.eventType    << endl
                     << "messageType    = " << event.messageType  << endl
                     << "sequenceID     = " << event.sequenceID   << endl
                     << "timestamp      = " << event.timestamp    << endl;
                ret = false;
            }
            else
            {
                // Get the Tx Event from the packet the server sent
                for(uint32_t i = 1; i < messageTypes.size(); i++)
                {
                    event = getCPTSEvent(cmdSocket);

                    if ( (event.messageType != messageTypes[i]) ||
                         (event.sequenceID != (i-1)) ||
                         (event.eventType != 5U) )
                    {
                        cout << "[CPTSTxEthernetEventTest]: CPTS Tx event " << i << " was incorrect!" << endl;
                        cout << "eventType      = " << event.eventType    << endl
                             << "messageType    = " << event.messageType  << endl
                             << "sequenceID     = " << event.sequenceID   << endl
                             << "timestamp      = " << event.timestamp    << endl;

                        ret = false;
                        break;
                    }
                }
            }
        }

        sendCmd(cmdSocket, TEST_CMD_CPTS_UNREGISTER);
        cout << "[CPTSTxEthernetEventTest] unregistering CPTS handler..." << endl;
    }
    catch (TCPSocket::Error& e)
    {
        // Fail the test under any connection/socket errors.
        cout << "[CPTSTxEthernetEventTest] error - " << e.what() << endl;
        return false;
    }

    return ret;
}

string CPTSTxEthernetEventTest::description() const
{
    return "CPTS Tx Ethernet Event test";
}


// TCPLoadTest TCPTrafficTest implementation
TCPLoadTest::TCPLoadTest(TCPSocket *cmdSocket, TCPTrafficGenerator& tcpGen, const LoadRange& loadRange,
                         uint32_t numMeasures, bool echoEnabled = false, bool verbose = false)
    : TCPTrafficTest(cmdSocket,tcpGen,numMeasures,1), loadRange(loadRange), numMeasures(numMeasures), echoEnabled(echoEnabled), verbose(verbose)
{
}

bool TCPLoadTest::beforeTraffic()
{
    // Init average load values
    avgCpuLoad      = 0;
    avgHwiLoad      = 0;
    avgRxTaskLoad   = 0;
    avgTxTaskLoad   = 0;

    try
    {
        if (echoEnabled)
        {
            sendCmd(cmdSocket, TEST_CMD_ENABLE_TCP_ECHO);
        }
        else
        {
            sendCmd(cmdSocket, TEST_CMD_DISABLE_TCP_ECHO);
        }

        // Clear SW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_SW_STATS);

        // Clear HW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_HW_STATS);

        // Clear NDK stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

        // Tell the traffic generator whether to expect echo traffic or not
        tcpGen->setEchoExpected(echoEnabled);

        // set packetSize and bit rate of the traffic generator
        tcpGen->setPacketSize(TCPTrafficGenerator::DEFAULT_TCP_PACKET_SIZE);
        tcpGen->setMBitRate(TCPTrafficGenerator::DEFAULT_TCP_MBIT_RATE);
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[TCPLoadTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool TCPLoadTest::duringTraffic()
{
    try
    {
        LoadStats stats = getLoadStats(cmdSocket);

        avgCpuLoad      += stats.cpuLoad;
        avgHwiLoad      += stats.hwiLoad;
        avgRxTaskLoad   += stats.ndk2nspRxLoad;
        if (echoEnabled)
        {
            avgTxTaskLoad   += stats.ndk2nspTxLoad;
        }
        if (verbose)
        {
            printLoadStats(stats, true);
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[TCPLoadTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool TCPLoadTest::afterTraffic()
{
    std::ostringstream out;

    // Create and save results string
    avgCpuLoad    = (avgCpuLoad * wakeupRateInSecs) / genTimeSecs;
    avgHwiLoad    = (avgHwiLoad * wakeupRateInSecs) / genTimeSecs;
    avgRxTaskLoad = (avgRxTaskLoad * wakeupRateInSecs) / genTimeSecs;
    avgTxTaskLoad = (avgTxTaskLoad * wakeupRateInSecs) / genTimeSecs;

    cout << "--- Expected CPU load max    : " << loadRange.cpuLoadMax << endl;
    cout << "--- Expected Hwi load max    : " << loadRange.hwiLoadMax << endl;
    cout << "--- Expected Rx Task load max: " << loadRange.taskLoadMax << endl;

    cout << "--- Average CPU Load     : " << avgCpuLoad  << endl;
    cout << "--- Average HWI Load     : " << avgHwiLoad  << endl;
    cout << "--- Average Rx Task Load : " << avgRxTaskLoad << endl;
    cout << "--- Average Tx Task Load : " << avgTxTaskLoad << endl;

    out << "CPU Load = " << avgCpuLoad << "%"
        << ", HWI Load = " << avgHwiLoad << "%"
        << ", Rx Task Load = " << avgRxTaskLoad << "%";
    if (echoEnabled)
    {
        out << ", Tx Task Load = " << avgTxTaskLoad << "%";
    }
    resultsStr = out.str();

    cout << resultsStr << endl;

    return (avgCpuLoad <= loadRange.cpuLoadMax) &&
           (avgHwiLoad <= loadRange.hwiLoadMax) &&
           (avgRxTaskLoad <= loadRange.taskLoadMax);
}

string TCPLoadTest::description() const
{
    return (echoEnabled) ? "TCP Rx/Tx load test" : "TCP Rx load test";
}

string TCPLoadTest::results()
{
    return resultsStr;
}


// TCPPerformanceTest TCPTrafficTest implementation
TCPPerformanceTest::TCPPerformanceTest(TCPSocket *cmdSocket, TCPTrafficGenerator& tcpGen, uint32_t mbitRate, uint32_t packetSize, bool echoEnabled = false)
    : TCPTrafficTest(cmdSocket, tcpGen, TCPPerformanceTest::DEFAULT_TEST_DURATION, TCPPerformanceTest::DEFAULT_LOAD_CHECK_INTERVAL),
      mbitRate(mbitRate), packetSize(packetSize), echoEnabled(echoEnabled)
{
}

bool TCPPerformanceTest::beforeTraffic()
{
    // Init average load values
    avgCpuLoad      = 0;
    avgHwiLoad      = 0;
    avgRxTaskLoad   = 0;
    avgTxTaskLoad   = 0;

    try
    {
        // Tell TCP daemon on server to not send echoes
        if (echoEnabled)
        {
            sendCmd(cmdSocket, TEST_CMD_ENABLE_TCP_ECHO);
        }
        else
        {
            sendCmd(cmdSocket, TEST_CMD_DISABLE_TCP_ECHO);
        }

        // Clear SW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_SW_STATS);

        // Clear HW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_HW_STATS);

        // Clear NDK stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

        // Tell the traffic generator whether to expect echo traffic or not
        tcpGen->setEchoExpected(echoEnabled);

        // set packetSize and bit rate of the traffic generator
        tcpGen->setPacketSize(packetSize);
        tcpGen->setMBitRate(mbitRate);
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[TCPPerformanceTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool TCPPerformanceTest::duringTraffic()
{
    try
    {
        LoadStats stats = getLoadStats(cmdSocket);

        avgCpuLoad      += stats.cpuLoad;
        avgHwiLoad      += stats.hwiLoad;
        avgRxTaskLoad   += stats.ndk2nspRxLoad;
        if (echoEnabled)
        {
            avgTxTaskLoad += stats.ndk2nspTxLoad;
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[TCPPerformanceTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool TCPPerformanceTest::afterTraffic()
{
    std::ostringstream out;

    // Create and save results string
    avgCpuLoad    = (avgCpuLoad * wakeupRateInSecs) / genTimeSecs;
    avgHwiLoad    = (avgHwiLoad * wakeupRateInSecs) / genTimeSecs;
    avgRxTaskLoad = (avgRxTaskLoad * wakeupRateInSecs) / genTimeSecs;
    avgTxTaskLoad = (avgTxTaskLoad * wakeupRateInSecs) / genTimeSecs;

    // Get count of packets sent by the generator
    uint32_t packetsSentCount = tcpGen->getPacketsSentCount();

    std::chrono::seconds sleepTime(1);

    // Wait a second before getting the packet stats
    this_thread::sleep_for(sleepTime);

    // Get count of packets received on target server
    TestSWStats stats = getSWStats(cmdSocket);

    // Print out the packet counts
    if (packetsSentCount != stats.tcpPacketCount)
    {
        out << "Packets Sent = " << packetsSentCount
            << ", Packets Received = " << stats.tcpPacketCount;
    }
    else
    {
        out << "CPU Load = " << avgCpuLoad << "%"
            << ", HWI Load = " << avgHwiLoad << "%"
            << ", Rx Task Load = " << avgRxTaskLoad << "%";
        if (echoEnabled)
        {
            out << ", Tx Task Load = " << avgTxTaskLoad << "%";
        }
    }

    resultsStr = out.str();

    cout << resultsStr << endl;

    if (packetsSentCount != stats.tcpPacketCount)
    {
        EthernetHWStats     hwStats     = getHWStats(cmdSocket);
        EthernetHWErrors    hwErrors    = getHWErrors(cmdSocket);
        NDKIpStats          ndkIpStats  = getNDKIpStats(cmdSocket);

        printHWStats(hwStats);
        printHWErrors(hwErrors);
        printNDKIpStats(ndkIpStats);

        return false;
    }

    return true;
}

string TCPPerformanceTest::description() const
{
    std::ostringstream out;

    out << "NSP TCP Traffic Performance Test "
        << "(packetSize = " << std::to_string(packetSize)
        << ", bitrate = " << std::to_string(mbitRate) << "Mbps"
        << ", echo " << (echoEnabled ? "on" : "off") << ")";

    return out.str();
}

string TCPPerformanceTest::results()
{
    return resultsStr;
}


// UDPLoadTest UDPTrafficTest implementation
UDPLoadTest::UDPLoadTest(TCPSocket *cmdSocket, UDPTrafficGenerator& udpGen, const LoadRange& loadRange,
                         uint32_t numMeasures, bool echoEnabled = false, bool verbose = false)
    : UDPTrafficTest(cmdSocket,udpGen,numMeasures,1), loadRange(loadRange), numMeasures(numMeasures), echoEnabled(echoEnabled), verbose(verbose)
{
}

bool UDPLoadTest::beforeTraffic()
{
    // Init average load values
    avgCpuLoad      = 0;
    avgHwiLoad      = 0;
    avgRxTaskLoad   = 0;
    avgTxTaskLoad   = 0;

    try
    {
        if (echoEnabled)
        {
            sendCmd(cmdSocket, TEST_CMD_ENABLE_UDP_ECHO);
        }
        else
        {
            sendCmd(cmdSocket, TEST_CMD_DISABLE_UDP_ECHO);
        }

        // Clear SW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_SW_STATS);

        // Clear HW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_HW_STATS);

        // Clear NDK stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

        // Tell the traffic generator whether to expect echo traffic or not
        udpGen->setEchoExpected(echoEnabled);

        // set packetSize and bit rate of the traffic generator
        udpGen->setPacketSize(UDPTrafficGenerator::DEFAULT_UDP_PACKET_SIZE);
        udpGen->setMBitRate(UDPTrafficGenerator::DEFAULT_UDP_MBIT_RATE);
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[UDPLoadTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool UDPLoadTest::duringTraffic()
{
    try
    {
        LoadStats stats = getLoadStats(cmdSocket);

        avgCpuLoad      += stats.cpuLoad;
        avgHwiLoad      += stats.hwiLoad;
        avgRxTaskLoad   += stats.ndk2nspRxLoad;
        if (echoEnabled)
        {
            avgTxTaskLoad += stats.ndk2nspTxLoad;
        }
        if (verbose)
        {
            printLoadStats(stats, true);
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[UDPLoadTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool UDPLoadTest::afterTraffic()
{
    std::ostringstream out;

    // Create and save results string
    avgCpuLoad    = (avgCpuLoad * wakeupRateInSecs) / genTimeSecs;
    avgHwiLoad    = (avgHwiLoad * wakeupRateInSecs) / genTimeSecs;
    avgRxTaskLoad = (avgRxTaskLoad * wakeupRateInSecs) / genTimeSecs;
    avgTxTaskLoad = (avgTxTaskLoad * wakeupRateInSecs) / genTimeSecs;

    cout << "--- Expected CPU load max    : " << loadRange.cpuLoadMax << endl;
    cout << "--- Expected Hwi load max    : " << loadRange.hwiLoadMax << endl;
    cout << "--- Expected Rx Task load max: " << loadRange.taskLoadMax << endl;

    cout << "--- Average CPU Load     : " << avgCpuLoad  << endl;
    cout << "--- Average HWI Load     : " << avgHwiLoad  << endl;
    cout << "--- Average Rx Task Load : " << avgRxTaskLoad << endl;
    cout << "--- Average Tx Task Load : " << avgTxTaskLoad << endl;

    out << "CPU Load = " << avgCpuLoad << "%"
        << ", HWI Load = " << avgHwiLoad << "%"
        << ", Rx Task Load = " << avgRxTaskLoad << "%";
    if (echoEnabled)
    {
        out << ", Tx Task Load = " << avgTxTaskLoad << "%";
    }
    resultsStr = out.str();

    cout << resultsStr << endl;

    return (avgCpuLoad <= loadRange.cpuLoadMax) &&
           (avgHwiLoad <= loadRange.hwiLoadMax) &&
           (avgRxTaskLoad <= loadRange.taskLoadMax);
}

string UDPLoadTest::description() const
{
    return (echoEnabled) ? "UDP Rx/Tx load test" : "UDP Rx load test";
}

string UDPLoadTest::results()
{
    return resultsStr;
}


// UDPPerformanceTest UDPTrafficTest implementation
UDPPerformanceTest::UDPPerformanceTest(TCPSocket *cmdSocket, UDPTrafficGenerator& udpGen, uint32_t mbitRate,
                                       uint32_t packetSize, bool echoEnabled = false)
    : UDPTrafficTest(cmdSocket, udpGen, UDPPerformanceTest::DEFAULT_TEST_DURATION, UDPPerformanceTest::DEFAULT_LOAD_CHECK_INTERVAL),
      mbitRate(mbitRate), packetSize(packetSize), echoEnabled(echoEnabled)
{
}

bool UDPPerformanceTest::beforeTraffic()
{
    // Init average load values
    avgCpuLoad      = 0;
    avgHwiLoad      = 0;
    avgRxTaskLoad   = 0;
    avgTxTaskLoad   = 0;

    try
    {
        // Tell UDP daemon on server to not send echoes
        if (echoEnabled)
        {
            sendCmd(cmdSocket, TEST_CMD_ENABLE_UDP_ECHO);
        }
        else
        {
            sendCmd(cmdSocket, TEST_CMD_DISABLE_UDP_ECHO);
        }

        // Clear SW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_SW_STATS);

        // Clear HW stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_HW_STATS);

        // Clear NDK stats on server
        sendCmd(cmdSocket, TEST_CMD_CLEAR_NDK_STATS);

        // Tell the traffic generator whether to expect echo traffic or not
        udpGen->setEchoExpected(echoEnabled);

        // set packetSize and bit rate of the traffic generator
        udpGen->setPacketSize(packetSize);
        udpGen->setMBitRate(mbitRate);
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[UDPPerformanceTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool UDPPerformanceTest::duringTraffic()
{
    try
    {
        LoadStats stats = getLoadStats(cmdSocket);

        avgCpuLoad      += stats.cpuLoad;
        avgHwiLoad      += stats.hwiLoad;
        avgRxTaskLoad   += stats.ndk2nspRxLoad;
        if (echoEnabled)
        {
            avgTxTaskLoad += stats.ndk2nspTxLoad;
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[UDPPerformanceTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool UDPPerformanceTest::afterTraffic()
{
    std::ostringstream out;

    // Create and save results string
    avgCpuLoad    = (avgCpuLoad * wakeupRateInSecs) / genTimeSecs;
    avgHwiLoad    = (avgHwiLoad * wakeupRateInSecs) / genTimeSecs;
    avgRxTaskLoad = (avgRxTaskLoad * wakeupRateInSecs) / genTimeSecs;
    avgTxTaskLoad = (avgTxTaskLoad * wakeupRateInSecs) / genTimeSecs;

    // Get count of packets sent by the generator
    uint32_t packetsSentCount = udpGen->getPacketsSentCount();

    std::chrono::seconds sleepTime(1);

    // Wait a second before getting the packet stats
    this_thread::sleep_for(sleepTime);

    // Get count of packets received on target server
    TestSWStats stats = getSWStats(cmdSocket);

    // Print out the packet counts
    if (packetsSentCount != stats.udpPacketCount)
    {
        out << "Packets Sent = " << packetsSentCount
            << ", Packets Received = " << stats.udpPacketCount;
    }
    else
    {
        out << "CPU Load = " << avgCpuLoad << "%"
            << ", HWI Load = " << avgHwiLoad << "%"
            << ", Rx Task Load = " << avgRxTaskLoad << "%";
        if (echoEnabled)
        {
            out << ", Tx Task Load = " << avgTxTaskLoad << "%";
        }
    }

    resultsStr = out.str();

    cout << resultsStr << endl;

    if (packetsSentCount != stats.udpPacketCount)
    {
        EthernetHWStats     hwStats     = getHWStats(cmdSocket);
        EthernetHWErrors    hwErrors    = getHWErrors(cmdSocket);
        NDKIpStats          ndkIpStats  = getNDKIpStats(cmdSocket);

        printHWStats(hwStats);
        printHWErrors(hwErrors);
        printNDKIpStats(ndkIpStats);

        return false;
    }

    return true;
}

string UDPPerformanceTest::description() const
{
    std::ostringstream out;

    out << "NSP UDP Traffic Performance Test "
        << "(packetSize = " << std::to_string(packetSize)
        << ", bitrate = " << std::to_string(mbitRate) << "Mbps"
        << ", echo " << (echoEnabled ? "on" : "off") << ")";

    return out.str();
}

string UDPPerformanceTest::results()
{
    return resultsStr;
}


// RawPerformanceTest implementation
RawPerformanceTest::RawPerformanceTest(TCPSocket *cmdSocket, RawTrafficGenerator& rawGen, uint32_t mbitRate, uint32_t packetSize, bool vlanEnabled)
    : TrafficTest(cmdSocket, RawPerformanceTest::DEFAULT_TEST_DURATION, RawPerformanceTest::DEFAULT_LOAD_CHECK_INTERVAL),
      rawGen(&rawGen), mbitRate(mbitRate), packetSize(packetSize), vlanEnabled(vlanEnabled)
{
}

bool RawPerformanceTest::execute()
{
    try
    {
        if (!beforeTraffic()) return false;

        TrafficGenThread rawThread(*rawGen);

        rawThread.start();

        if (genTimeSecs != 0)
        {
            cout << "--- Generating RAW traffic for " << genTimeSecs
                 << " seconds..." << endl;

#if (0)
            // Let traffic ramp up for three seconds
            std::chrono::seconds threeSecs(3);
            this_thread::sleep_for(threeSecs);
#endif
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

                    if (!duringTraffic()) return false;
                }
            }
            else
            {
                // Wake up rate is zero, do nothing during traffic
                std::chrono::seconds sleepTime(genTimeSecs);
                this_thread::sleep_for(sleepTime);
            }

#if (0)
            // Let traffic ramp down for three seconds
            this_thread::sleep_for(threeSecs);
#endif
        }

        rawThread.stop();

        return afterTraffic();
    }
    catch (RawSocket::Error& e)
    {
        cout << "[RawPerformanceTest]: error - " << e.what() << endl;
    }
    return false;
}

bool RawPerformanceTest::beforeTraffic()
{
    // Init average load values
    avgCpuLoad      = 0;
    avgRxTaskLoad   = 0;
    avgHwiLoad      = 0;

    // set packetSize and bit rate of the traffic generator
    rawGen->setPacketSize(packetSize);
    rawGen->setMBitRate(mbitRate);
    rawGen->setVLAN(vlanEnabled);

    // Clear SW stats on server
    sendCmd(cmdSocket, TEST_CMD_CLEAR_SW_STATS);

    // Clear HW stats on server
    sendCmd(cmdSocket, TEST_CMD_CLEAR_HW_STATS);

    if (vlanEnabled)
    {
        std::chrono::seconds sleepTime(1);

        sendCmd(cmdSocket, TEST_CMD_START_NULL_STACK);

        // Wait a second before starting traffic for NULL stack
        this_thread::sleep_for(sleepTime);
    }

    return true;
}

bool RawPerformanceTest::duringTraffic()
{
    try
    {
        LoadStats stats = getLoadStats(cmdSocket);

        avgCpuLoad      += stats.cpuLoad;
        avgHwiLoad      += stats.hwiLoad;

        if (vlanEnabled)
        {
            avgRxTaskLoad   += stats.null2nspRxLoad;
        }
        else
        {
            avgRxTaskLoad   += stats.ndk2nspRxLoad;
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[RawPerformanceTest] error " << e.what() << endl;
        return false;
    }

    return true;
}

bool RawPerformanceTest::afterTraffic()
{
    std::ostringstream out;

    // Create and save results string
    avgCpuLoad      = (avgCpuLoad * wakeupRateInSecs) / genTimeSecs;
    avgRxTaskLoad   = (avgRxTaskLoad * wakeupRateInSecs) / genTimeSecs;
    avgHwiLoad      = (avgHwiLoad * wakeupRateInSecs) / genTimeSecs;

    // Get count of packets sent by the generator
    uint32_t packetsSentCount = rawGen->getPacketsSentCount();

    // Wait a little time before getting stats and stopping NULL stack
    std::chrono::seconds sleepTime(2);
    this_thread::sleep_for(sleepTime);

    // Get count of packets received on target server
    TestSWStats stats = getSWStats(cmdSocket);

    // Shutdown NULL stack if needed
    if (vlanEnabled)
    {
        sendCmd(cmdSocket, TEST_CMD_STOP_NULL_STACK);
    }

    // Print out the packet counts
    if (packetsSentCount != stats.rawPacketCount)
    {
        out << "Packets Sent = " << packetsSentCount
            << ", Packets Received = " << stats.rawPacketCount;
    }
    else
    {
        out << "CPU Load = " << avgCpuLoad << "%"
            << ", HWI Load = " << avgHwiLoad << "%"
            << ", Rx Task Load = " << avgRxTaskLoad << "%";
    }

    resultsStr = out.str();

    cout << resultsStr << endl;

    if (packetsSentCount != stats.rawPacketCount)
    {
        EthernetHWStats     hwStats     = getHWStats(cmdSocket);
        EthernetHWErrors    hwErrors    = getHWErrors(cmdSocket);

        printHWStats(hwStats);
        printHWErrors(hwErrors);

        return false;
    }

    return true;
}

string RawPerformanceTest::results()
{
    return resultsStr;
}

string RawPerformanceTest::description() const
{
    std::ostringstream out;

    out << "NSP Raw Traffic Performance Test "
        << "(packetSize = " << std::to_string(packetSize)
        << ", bitrate = " << std::to_string(mbitRate) << "Mbps"
        << ", " << (vlanEnabled ? "processed by NULL stack" : "processed by NDK Raw Sockets") << ")";

    return out.str();
}

