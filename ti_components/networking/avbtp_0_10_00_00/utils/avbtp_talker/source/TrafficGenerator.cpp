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
#include <algorithm>

// Local project headers
#include "TrafficGenerator.hpp"
#include "DataSource.hpp"
#include "CODECSource.hpp"
#include "Packet.hpp"
#include "Socket.hpp"
#include "AVBTPTalker.hpp"

using namespace std;
using namespace test;

TrafficClassManager::TrafficClassManager(string dev, bool verbose, uint32_t defaultClass)
    : dev(std::move(dev)), verbose(verbose), defaultClass(defaultClass)
{
    rootHandle = "1:";
    reset();
}

TrafficClassManager::~TrafficClassManager()
{
    if (verbose)
    {
        std::string cmd = "tc -s class show dev eth0";
        if (::system(cmd.c_str()) < 0)
        {
            cout << "warning: 'tc -s class show dev eth0' failed" << endl;
        }
    }
    deleteRoot();
}

void TrafficClassManager::reset()
{
    deleteRoot();
    addRoot();
}

void TrafficClassManager::setClass(std::string classid, std::string rate, std::string prio)
{
    std::string cmd = "tc class replace dev " + dev + " parent " + rootHandle + " classid "+ classid + " htb rate " + rate;
    if (!prio.empty())
    {
        cmd += " prio "+ prio;
    }

    if (verbose)
    {
        cout << "Executing command: " << cmd << endl;
    }
    if (::system(cmd.c_str()) < 0)
    {
        cout << "warning: 'tc class add' failed" << endl;
    }
}

void TrafficClassManager::deleteClass(std::string classid)
{
    std::string cmd = "tc class del dev " + dev + " parent " + rootHandle + " classid "+ classid;

    if (verbose)
    {
        cout << "Executing command: " << cmd << endl;
    }
    if (::system(cmd.c_str()) < 0)
    {
        cout << "warning: 'tc class del' failed" << endl;
    }
}

void TrafficClassManager::setFilter(std::string protocol, std::string filter, std::string classid)
{
    std::string cmd = "tc filter replace dev " + dev + " protocol " + protocol + " parent " + rootHandle + " prio 1 " + filter + " flowid " + classid;
    if (verbose)
    {
        cout << "Executing command: " << cmd << endl;
    }
    if (::system(cmd.c_str()) < 0)
    {
        cout << "warning: 'tc filter add' failed" << endl;
    }
}

void TrafficClassManager::deleteRoot()
{
    int retVal;
    std::string cmd = "tc qdisc del dev " + dev + " root > /dev/null 2>&1";
    if (verbose)
    {
        cout << "Executing command: " << cmd << endl;
    }
    retVal = ::system(cmd.c_str());
    if (retVal < 0)
    {
        cout << "warning: executing 'tc qdisc del' failed" << endl;
    }
}

void TrafficClassManager::addRoot()
{
    int retVal;
    std::string cmd = "tc qdisc add dev " + dev + " root handle " + rootHandle + " htb default " + to_string(defaultClass);
    if (verbose)
    {
        cout << "Executing command: " << cmd << endl;
    }
    retVal = ::system(cmd.c_str());
    if (retVal != 0)
    {
        cout << "warning: executing 'tc qdisc add' failed" << endl;
    }
}


// TrafficGenThread implementation
TrafficGenThread::TrafficGenThread(TrafficGenerator& gen)
    : gen(gen)
{
}

TrafficGenThread::~TrafficGenThread()
{
    stop();
}

void TrafficGenThread::start()
{
    gen.reset();
    t = thread(&TrafficGenerator::run, &gen);
}

void TrafficGenThread::stop()
{
    gen.stop();
    if (t.joinable()) t.join();
}


// TrafficGenerator implementation
TrafficGenerator::TrafficGenerator()
    : packetsSentCount(0), shutDown(false)
{
}

TrafficGenerator::TrafficGenerator(uint32_t packetSize, uint32_t mbitRate)
    : packetSize(packetSize), mbitRate(mbitRate), packetsSentCount(0), shutDown(false)
{
}

TrafficGenerator::~TrafficGenerator() = default;

void TrafficGenerator::stop()
{
    shutDown = true;
}

void TrafficGenerator::run()
{
    shutDown = false;
    packetsSentCount = generate(shutDown);
}

void TrafficGenerator::setPacketSize(uint32_t packetSize)
{
    this->packetSize = packetSize;
}

void TrafficGenerator::setMBitRate(uint32_t mbitRate)
{
    this->mbitRate = mbitRate;
}

uint32_t TrafficGenerator::getPacketsSentCount(void)
{
    return packetsSentCount;
}


// TCPTrafficGenerator implementation
const string TCPTrafficGenerator::TEST_TCP_QDISC_CLASS = "1:2";
const string TCPTrafficGenerator::TEST_TCP_QDISC_PRIO = "2";

TCPTrafficGenerator::TCPTrafficGenerator(string ip, string tcpPort,
                                         TrafficClassManager& tcManager, bool verbose)
    : TrafficGenerator(DEFAULT_TCP_PACKET_SIZE,DEFAULT_TCP_MBIT_RATE),
      ip(std::move(ip)), port(std::move(tcpPort)),
      echoExpected(false), verbose(verbose), tcManager(tcManager)
{
    // Call our derived setPacketSize to adjust for headers
    setPacketSize(packetSize);
}

void TCPTrafficGenerator::reset()
{
}

void TCPTrafficGenerator::setPacketSize(uint32_t packetSize)
{
    // Adjust the packetSize to make the complete frame
    // be the specified packetSize
    this->packetSize = packetSize -
                       (Packet::ETHERNET_HEADER_SIZE +
                        Packet::IP_HEADER_SIZE +
                        Packet::TCP_HEADER_SIZE);
}

uint32_t TCPTrafficGenerator::generate(const atomic_bool& shutDown)
{
    uint32_t count = 0;

    // Call traffic class manager to set current rate
    tcManager.setClass(
        TCPTrafficGenerator::TEST_TCP_QDISC_CLASS,
        to_string(mbitRate) + "mbit",
        TCPTrafficGenerator::TEST_TCP_QDISC_PRIO);

    try
    {
        cout << "[TCPTrafficGen]: connecting to " << ip << endl;

        TCPSocket tcpSocket(ip, port);
        // Create a large random data source from which to draw data
        RandomDataSource source(1024*1024, true);
        // Create the packet drawing against the random data source
        DataPacket p(0, packetSize, source);

        unsigned long showStatusEvery=10000;
        if (verbose)
        {
            showStatusEvery = 200;
        }

        cout << "[TCPTrafficGen]: connected! Sending packets..." << endl;
        while (!shutDown)
        {
            if (!p.fill())
            {
                cout << "[TCPTrafficGen]: no more data!" << endl;
                break;
            }

            tcpSocket.send(p);
            if (verbose)
            {
                cout << "[TCPTrafficGen]: sent " << p.size() << " bytes - ";
            }

            ++count;

            if (echoExpected)
            {
                vector<uint8_t> recvBuf = tcpSocket.receive(p.size());
                if (verbose)
                {
                    cout << "[TCPTrafficGen]: received " << recvBuf.size()
                         << " bytes " << endl;
                }

                if (!std::equal(begin(recvBuf), end(recvBuf), p.data()))
                {
                    cout << "[TCPTrafficGen]: mismatch detected! " << endl;
                }

                if ((count % showStatusEvery) == 0)
                {
                    cout << "[TCPTrafficGen]: verified " << count << " buffers" << endl;
                }
            }
            else
            {
                if ((count % showStatusEvery) == 0)
                {
                    cout << "[TCPTrafficGen]: sent " << count << " buffers" << endl;
                }
            }
        }
    }
    catch (TCPSocket::Error& e)
    {
        cout << "[TCPTrafficGen]: exception - " << e.what() << endl;
    }

    cout << "[TCPTrafficGen]: stopped - sent " << count << " buffers" << endl;

    return count;
}


// UDPTrafficGenerator implementation
const string UDPTrafficGenerator::TEST_UDP_QDISC_CLASS = "1:3";
const string UDPTrafficGenerator::TEST_UDP_QDISC_PRIO = "3";

UDPTrafficGenerator::UDPTrafficGenerator(string ip, string udpPort,
                                         TrafficClassManager& tcManager, bool verbose)
    : TrafficGenerator(DEFAULT_UDP_PACKET_SIZE, DEFAULT_UDP_MBIT_RATE),
      ip(std::move(ip)), port(std::move(udpPort)),
      echoExpected(false), verbose(verbose), tcManager(tcManager)
{
}

void UDPTrafficGenerator::reset()
{
}

void UDPTrafficGenerator::setPacketSize(uint32_t packetSize)
{
    // Adjust the packetSize to make the complete frame
    // be the specified packetSize
    this->packetSize = packetSize -
                       (Packet::ETHERNET_HEADER_SIZE +
                        Packet::IP_HEADER_SIZE +
                        Packet::UDP_HEADER_SIZE);
}

uint32_t UDPTrafficGenerator::generate(const atomic_bool& shutDown)
{
    uint32_t count = 0;

    // Call traffic class manager to set current rate
    tcManager.setClass(
        UDPTrafficGenerator::TEST_UDP_QDISC_CLASS,
        to_string(mbitRate) + "mbit",
        UDPTrafficGenerator::TEST_UDP_QDISC_PRIO);

    try
    {
        cout << "[UDPTrafficGen]: connecting to " << ip << endl;

        UDPSocket udpSocket(ip, port);
        RandomDataSource source(1024*1024, true);
        DataPacket p(0, packetSize, source);

        if (echoExpected)
        {
            udpSocket.setRcvTimeout(3);
        }

        unsigned long showStatusEvery=10000;
        if (verbose)
        {
            showStatusEvery = 200;
        }

        cout << "[UDPTrafficGen]: connected! Sending packets..." << endl;
        while (!shutDown)
        {
            if (!p.fill())
            {
                cout << "[UDPTrafficGen]: no more data!" << endl;
                break;
            }

            udpSocket.send(p);
            if (verbose)
            {
                cout << "[UDPTrafficGen]: sent " << p.size() << " bytes - ";
            }

            ++count;

            if (echoExpected)
            {
                vector<uint8_t> recvBuf = udpSocket.receive(p.size());
                if (verbose)
                {
                    cout << "[UDPTrafficGen]: received " << recvBuf.size()
                         << " bytes " << endl;
                }

                if (!std::equal(begin(recvBuf), end(recvBuf), p.data()))
                {
                    cout << "[UDPTrafficGen]: mismatch detected! " << endl;
                }

                if ((count % showStatusEvery) == 0)
                {
                    cout << "[UDPTrafficGen]: verified " << count << " packets" << endl;
                }
            }
            else
            {
                if ((count % showStatusEvery) == 0)
                {
                    cout << "[UDPTrafficGen]: sent " << count << " packets" << endl;
                }
            }
        }
    }
    catch (UDPSocket::Error& e)
    {
        cout << "[UDPTrafficGen]: exception - " << e.what() << endl;
    }

    cout << "[UDPTrafficGen]: stopped - sent " << count << " packets" << endl;

    return count;
}



// AVBTrafficGenerator implementation
const string AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS = "1:4";
const string AVBTrafficGenerator::TEST_AVBTP_QDISC_PRIO = "4";

AVBTrafficGenerator::AVBTrafficGenerator(std::string dev, MACAddress& srcMac, MACAddress& dstMac,
                                         vector<CODECSource>& dataSources, TrafficClassManager& tcManager, bool verbose)
    : TrafficGenerator(DEFAULT_AVBTP_PACKET_SIZE,DEFAULT_AVBTP_MBIT_RATE),
      dev(std::move(dev)), srcMac(srcMac), dstMac(dstMac),
      dataSources(&dataSources), verbose(verbose), tcManager(tcManager)
{
    numTalkers = dataSources.size();

    setVLAN(AVBTPStreamPacket::VLAN_DEFAULT_ID, AVBTPStreamPacket::VLAN_DEFAULT_PRIORITY);
    setEthertype(AVBTPStreamPacket::ETHER_TYPE_EXPERIMENTAL);
    setSubtype(AVBTPStreamPacket::SUBTYPE_RESERVED);
}

void AVBTrafficGenerator::reset()
{
    for (auto& s : *dataSources)
    {
        s.reset();
    }
}

void AVBTrafficGenerator::setEthertype(uint16_t ethertype)
{
    this->ethertype = ethertype;
}

void AVBTrafficGenerator::setVLAN(uint16_t vlanId, uint8_t vlanPriority)
{
    this->vlanId = vlanId;
    this->vlanPrio = vlanPriority;
}

void AVBTrafficGenerator::setSubtype(uint8_t subtype)
{
    this->subtype = subtype;
}

void AVBTrafficGenerator::setCvFormattype(uint8_t cvformattype)
{
    this->cvformattype = cvformattype;
}

void AVBTrafficGenerator::setCvFormatSubtype(uint8_t codectype, uint8_t talkernum)
{
    this->codectypearray[talkernum] = codectype;
}

vector<CODECSource>* AVBTrafficGenerator::getDataSources(void) const
{
    return dataSources;
}

uint32_t AVBTrafficGenerator::getNumTalkers(void) const
{
    return numTalkers;
}

uint32_t AVBTrafficGenerator::generate(const atomic_bool& shutDown)
{
    uint32_t count = 0;
    int maxFrameSent = 0, sendFlag = 0U;
    int frameCnt[4];
    int cnt = 0;
    // Call traffic class manager to set current rate
    tcManager.setClass(
        AVBTrafficGenerator::TEST_AVBTP_QDISC_CLASS,
        to_string(mbitRate) + "mbit",
        AVBTrafficGenerator::TEST_AVBTP_QDISC_PRIO);

    try
    {
        cout << "[AVBTrafficGen]: connecting to " << dstMac << endl;

        RawSocket rawSocket(dev, dstMac);

        // The talker uses a pull streaming model (packets are filled with data from
        // the data source).
        // Looping is provided by the data source itself.
        vector<AVBTPTalker> talkers;
        talkers.reserve(numTalkers);

        for (uint32_t i = 0; i < numTalkers; i++)
        {
            AVBTPTalker talker(srcMac, dstMac, i, dataSources->at(i), rawSocket);
            talker.setVLAN(vlanId, vlanPrio);
            talker.setSubtype(subtype);
            talker.setEthertype(ethertype);
            talker.setCvFormattype(cvformattype);
            talker.setCvFormatSubtype(codectypearray, i);
            talkers.push_back(talker);
        }

        // remove_if will iterate over the complete list, invoking the sendPacket
        // lambda on each of the talkers.
        // if a talker could not send a packet (either from running out of data or
        // an error on the socket send) then
        // remove_if will move that element to the end of the list returning the
        // iterator to that element which
        // we can now use in an erase call (Erase-remove idiom)
        auto sendPacket = [&](AVBTPTalker * talker)
        {
            bool sent = talker->send();
            if (sent)
            {
                count++;
            }
            return !sent;
        };
        cout << "[AVBTrafficGen]: sending frames..." << endl;

        // Copy List
        vector<AVBTPTalker*> tmpTalkers1(1);
        vector<AVBTPTalker*> tmpTalkers2(1);
        vector<AVBTPTalker*> tmpTalkers3(1);
        vector<AVBTPTalker*> tmpTalkers4(1);

        tmpTalkers1[0] = &talkers[0];
        tmpTalkers2[0] = &talkers[1];
        tmpTalkers3[0] = &talkers[2];
        tmpTalkers4[0] = &talkers[3];

        if (numTalkers == 4)
        {
            while (((tmpTalkers1.size() > 0) && (tmpTalkers2.size() > 0) && (tmpTalkers3.size() > 0) && (tmpTalkers4.size() > 0)) && !shutDown)
            {
                vector<CODECSource>* sources = getDataSources();
                cnt = 0;
                for (auto& s : *sources)
                {
                    frameCnt[cnt] = s.getFrameCount();
                    cnt++;
                }

                if((frameCnt[0] == frameCnt[1]) && (frameCnt[2] == frameCnt[3]) && (frameCnt[0] == frameCnt[3]))
                {
                    sendFlag = 1U;
                }
                else
                {
                    maxFrameSent = frameCnt[0];
                    for(int i=0;i<cnt;i++)
                    {
                        if(frameCnt[i]>maxFrameSent)
                        {
                            maxFrameSent = frameCnt[i];
                        }
                    }
                    sendFlag = 0U;
                }

                if(maxFrameSent > frameCnt[0] || sendFlag)
                {
                    tmpTalkers1.erase(
                    remove_if(begin(tmpTalkers1), end(tmpTalkers1), sendPacket),
                    end(tmpTalkers1));
                }
                if(maxFrameSent > frameCnt[1] || sendFlag)
                {
                    tmpTalkers2.erase(
                    remove_if(begin(tmpTalkers2), end(tmpTalkers2), sendPacket),
                    end(tmpTalkers2));
                }
                if(maxFrameSent > frameCnt[2] || sendFlag)
                {
                    tmpTalkers3.erase(
                    remove_if(begin(tmpTalkers3), end(tmpTalkers3), sendPacket),
                    end(tmpTalkers3));
                }
                if(maxFrameSent > frameCnt[3] || sendFlag)
                {
                    tmpTalkers4.erase(
                    remove_if(begin(tmpTalkers4), end(tmpTalkers4), sendPacket),
                    end(tmpTalkers4));
                }
            }
        }
        else if (numTalkers == 3)
        {
            while (((tmpTalkers1.size() > 0) && (tmpTalkers2.size() > 0) && (tmpTalkers3.size() > 0)) && !shutDown)
            {
                vector<CODECSource>* sources = getDataSources();
                cnt = 0;
                for (auto& s : *sources)
                {
                    frameCnt[cnt] = s.getFrameCount();
                    cnt++;
                }

                if((frameCnt[0] == frameCnt[1]) && (frameCnt[0] == frameCnt[2]))
                {
                    sendFlag = 1U;
                }
                else
                {
                    maxFrameSent = frameCnt[0];
                    for(int i=0;i<cnt;i++)
                    {
                        if(frameCnt[i]>maxFrameSent)
                        {
                            maxFrameSent = frameCnt[i];
                        }
                    }
                    sendFlag = 0U;
                }

                if(maxFrameSent > frameCnt[0] || sendFlag)
                {
                    tmpTalkers1.erase(
                    remove_if(begin(tmpTalkers1), end(tmpTalkers1), sendPacket),
                    end(tmpTalkers1));
                }
                if(maxFrameSent > frameCnt[1] || sendFlag)
                {
                    tmpTalkers2.erase(
                    remove_if(begin(tmpTalkers2), end(tmpTalkers2), sendPacket),
                    end(tmpTalkers2));
                }
                if(maxFrameSent > frameCnt[2] || sendFlag)
                {
                    tmpTalkers3.erase(
                    remove_if(begin(tmpTalkers3), end(tmpTalkers3), sendPacket),
                    end(tmpTalkers3));
                }
            }
        }
        else if (numTalkers == 2)
        {
            cout << "[AVBTrafficGen]: NUMTALKERS = 2" << endl;
            while (((tmpTalkers1.size() > 0) && (tmpTalkers2.size() > 0)) && !shutDown)
            {
                vector<CODECSource>* sources = getDataSources();
                cnt = 0;
                for (auto& s : *sources)
                {
                    frameCnt[cnt] = s.getFrameCount();
                    cout << "frameCount source "<< cnt << "=" << frameCnt[cnt] << endl;
                    cnt++;
                }

                if((frameCnt[0] == frameCnt[1]))
                {
                    sendFlag = 1U;
                }
                else
                {
                    maxFrameSent = frameCnt[0];
                    for(int i=0;i<cnt;i++)
                    {
                        if(frameCnt[i]>maxFrameSent)
                        {
                            maxFrameSent = frameCnt[i];
                        }
                    }
                    sendFlag = 0U;
                }

                if(maxFrameSent > frameCnt[0] || sendFlag)
                {
                    cout << "Sending talker 1" << endl;
                    tmpTalkers1.erase(
                    remove_if(begin(tmpTalkers1), end(tmpTalkers1), sendPacket),
                    end(tmpTalkers1));
                }
                if(maxFrameSent > frameCnt[1] || sendFlag)
                {
                    cout << "Sending talker 2" << endl;
                    tmpTalkers2.erase(
                    remove_if(begin(tmpTalkers2), end(tmpTalkers2), sendPacket),
                    end(tmpTalkers2));
                }

            }
        }
        else if (numTalkers == 1)
        {
            cout << "[AVBTrafficGen]: NUMTALKERS = 1" << endl;
            while (tmpTalkers1.size() > 0 && !shutDown)
            {
                tmpTalkers1.erase(
                remove_if(begin(tmpTalkers1), end(tmpTalkers1), sendPacket),
                end(tmpTalkers1));
            }
        }
        else
        {
            cout << " No. of talkers value wrong \n" << endl;
        }
        cout << "[AVBTrafficGen]: stopped" << endl;
    }
    catch (RawSocket::Error& e)
    {
        cout << "[AVBTrafficGen]: exception - " << e.what() << endl;
    }

    cout << "[AVBTrafficGen]: stopped - sent " << count << " frames" << endl;

    return count;
}
