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
#include "TalkerClient.hpp"
#include "Packet.hpp"
#include "Socket.hpp"
#include "Options.hpp"
#include "TrafficGenerator.hpp"
#include "DataSource.hpp"
#include "CODECSource.hpp"

using namespace std;
using namespace test;

const string TalkerClient::TEST_CMD_QDISC_CLASS = "1:1";
const string TalkerClient::TEST_CMD_QDISC_RATE  = "10mbit";
const string TalkerClient::TEST_CMD_QDISC_PRIO  = "1";

TalkerClient::TalkerClient(Options& opts)
    : opts(&opts)
{
    int testDuration        = opts.getInt("test-duration");
    int numTalkers          = opts.getInt("num-talkers");
    string srcMacString     = opts.get("src-mac-spoof");
    string destIPAddr       = opts.get("dest-ip");

    int dataRate            = opts.getInt("data-rate");

    MACAddress dstMac;
    if (!destIPAddr.empty())
    {
        // Lookup dest MAC address from the provided IP address
        dstMac = getTargetMAC(destIPAddr, opts.get("dev"));
        cout << "Using destination MAC found from destination IP address: " << dstMac << "." << endl;
    }
    else
    {
        // Use the MAC address provided (if one not provided we broadcast instead)
        string dstMacString = opts.get("dest-mac");
        if (!dstMacString.empty())
        {
            dstMac = {dstMacString};
            cout << "Using destination MAC provided: " << dstMac << "." << endl;
        }
        else
        {
            dstMac = {"FF:FF:FF:FF:FF:FF"};
            cout << "No destination MAC provided, using broadcast: " << dstMac << "." << endl;
        }
    }

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


    // Figure out how many talkers we are simulating
    vector<string> fileNames = tokenize(opts.get("input"), ' ');
    int numInputs = (int) fileNames.size();
    if ((numTalkers == -1) || (numTalkers < numInputs))
    {
        numTalkers = numInputs;
        cout << "Making numTalkers be " << numTalkers << " to match the input count." << endl;
    }
    else if (numTalkers > numInputs)
    {
        replicateLast(fileNames, numTalkers);
        cout << "Extending the input count by reusing the last input an additional " << (numTalkers - numInputs) << " time(s)." << endl;
    }

    // Instantiate the CODEC data sources
    dataSources = new vector<CODECSource>();

    dataSources->reserve(numTalkers);
    bool enableLooping = opts.getBool("loop");
    int codecType[numTalkers];
    for (int i = 0; i < numTalkers; i++)
    {
        CODECSource src = CODECSource(fileNames[i], enableLooping);
        codecType[i] = src.getCODECType();
        dataSources->push_back(std::move(src));
/*         if(i > 0)
        {
            if(codecType[i] != codecType[i-1])
            {
                exit(0);
            }
        }
 */
    }

    // Setup qdisc traffic management
    vector<string> tokens = tokenize(AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS, ':');
    auto subClassNum = stoi(tokens.at(1));

    tcManager = new TrafficClassManager(opts.get("dev"), opts.getBool("verbose"), subClassNum);

    tcManager->setClass(
        TalkerClient::TEST_CMD_QDISC_CLASS,
        TalkerClient::TEST_CMD_QDISC_RATE,
        TalkerClient::TEST_CMD_QDISC_PRIO);
    tcManager->setClass(AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS, "10mbit", to_string(100));

    // Add traffic class filters
    std::string filter = "u32 match ip dport 19200 0xffff";
    tcManager->setFilter(
        "ip",
        filter,
        TalkerClient::TEST_CMD_QDISC_CLASS);

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

    // Create the AVBTP traffic generator
    avbGen = new AVBTrafficGenerator(opts.get("dev"), srcMac, dstMac, *dataSources, *tcManager, opts.getBool("verbose"));
    // Set the default vlan for the generator
    avbGen->setVLAN(opts.getInt("vlan-id"), opts.getInt("vlan-priority"));
    avbGen->setEthertype(opts.getInt("avb-ethertype"));
    avbGen->setSubtype(opts.getInt("avb-subtype"));
    avbGen->setCvFormattype(opts.getInt("avb-cvformattype"));
    for (int i = 0; i < numTalkers; i++)
    {
        if(codecType[i] != -1)
        {
            avbGen->setCvFormatSubtype(codecType[i], i);
        }
    }
    // Set default dataRate to numTalkers*100
    if (dataRate == -1)
    {
        dataRate = numTalkers * 100;
    }

    // Register all tests
    if (testDuration > 0)
    {
        // AVBTP Packet Loss test
        unique_ptr<UnitTest> avbPacketLossTest =
            make_unique<AVBTrafficTest>(*avbGen, testDuration, dataRate);
        tests.push_back(std::move(avbPacketLossTest));
    }
}

TalkerClient::~TalkerClient()
{
    delete avbGen;
    delete dataSources;
    delete tcManager;
}

void TalkerClient::execute()
{
    stringstream ss;
    for (auto& t : tests)
    {
        cout << "====[" << t->description() << "]====" << endl;
        bool ret = t->execute();
        string passFailedStr = ret ? "Pass" : "FAIL!";
        ss << "[" << t->description() << "] : " << passFailedStr << endl;
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
UnitTest::UnitTest()
{
}

UnitTest::~UnitTest() = default;


// TrafficTest implementation
TrafficTest::TrafficTest(uint32_t genTimeSecs)
    : genTimeSecs(genTimeSecs)
{
}

TrafficTest::~TrafficTest() = default;

// AVBTrafficTest implementation
AVBTrafficTest::AVBTrafficTest(AVBTrafficGenerator& avbGen, uint32_t genTimeSecs, uint32_t dataRate)
    : TrafficTest(genTimeSecs), avbGen(&avbGen), dataRate(dataRate)
{
}

bool AVBTrafficTest::execute()
{
    bool retVal = true;
    TrafficGenThread avbThread(*avbGen);

    try
    {
        if (!beforeTraffic())
        {
            return false;
        }

        // Start Traffic threads
        avbThread.start();

        if (genTimeSecs != 0)
        {
            cout << "--- Generating AVB traffic for " << genTimeSecs
                 << " seconds..." << endl;

            // Let traffic ramp up for one seconds
            std::chrono::seconds rampTime(1);
            this_thread::sleep_for(rampTime);

            std::chrono::seconds sleepTime(genTimeSecs);
            this_thread::sleep_for(sleepTime);

            // Let traffic ramp down
            this_thread::sleep_for(rampTime);
        }

        avbThread.stop();

        if (retVal)
        {
            retVal = afterTraffic();
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[AVBTrafficTest]: error - " << e.what() << endl;
        retVal = false;
    }

    return retVal;
}

bool AVBTrafficTest::beforeTraffic()
{
    vector<CODECSource>* sources = avbGen->getDataSources();

    for (auto& s : *sources)
    {
        // By default don't cap the number of frames
        s.setMaxFrames(0);
        s.enableStripEOI(false);
        s.insertRSTMarkers(false);
    }

    // Set dataRate in the generator
    avbGen->setMBitRate(dataRate);

    return true;
}

bool AVBTrafficTest::duringTraffic()
{
    return true;
}

bool AVBTrafficTest::afterTraffic()
{
    return true;
}

string AVBTrafficTest::description() const
{
    return "AVB traffic test";
}

