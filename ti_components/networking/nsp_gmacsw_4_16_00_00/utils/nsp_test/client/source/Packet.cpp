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
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>

// Linux headers
#include <netinet/in.h>

// Local project headers
#include "Packet.hpp"
#include "DataSource.hpp"
#include "Mac.hpp"


using namespace std;
using namespace test;

static void writeNetOrder8(vector<uint8_t>::iterator it, uint8_t val);
static void writeNetOrder16(vector<uint8_t>::iterator it, uint16_t val);
static void writeNetOrder32(vector<uint8_t>::iterator it, uint32_t val);

Packet::Packet(size_t size) : _size(size), _data(size)
{
}

Packet::~Packet() = default;

size_t Packet::size() const
{
    return _size;
}

const uint8_t* Packet::data() const
{
    return _data.data();
}

CommandPacket::CommandPacket() : Packet(4)
{
}

CommandPacket::CommandPacket(uint32_t id) : Packet(4)
{
    setCommand(id);
}

CommandPacket::CommandPacket(uint32_t id, uint32_t param) : Packet(8)
{
    setCommand(id);
    writeNetOrder32(begin(_data) + 4, param);
}

void CommandPacket::setCommand(uint32_t id)
{
    writeNetOrder32(begin(_data), id);
}

DataPacket::DataPacket(size_t headerLen, size_t payloadSize,
                       IDataSource& source)
    : Packet(headerLen + payloadSize), headerLen(headerLen),
      payloadSize(payloadSize), source(&source), randomizeLen(false),
      distribution(1, payloadSize)
{
}

DataPacket::~DataPacket() = default;

bool DataPacket::fill()
{
    if (randomizeLen) 
    {
        payloadSize = distribution(engine);
    }
    size_t readSize = source->read(&_data[headerLen], payloadSize);
    _size = readSize + headerLen;
    return readSize != 0;
}

void DataPacket::reset()
{
    source->reset();
}

void DataPacket::print(ostream& stream) const
{
    stringstream ss;
    ss << "size: " << _size << endl;
    if (headerLen > 0) {
        ss << "--header-- " << endl;
        for (size_t i = 0; i < headerLen; i++) {
            ss << uppercase << hex << setw(2) << setfill('0')
               << static_cast<int>(_data[i]);
            if (i < headerLen - 1) ss << " ";
            if (((i + 1) % 6) == 0) ss << endl;
        }
        ss << "--end-- " << endl;
    }
    if (payloadSize > 0) {
        ss << "--payload-- " << endl;
        for (size_t i = 0; i < min((size_t)18u, payloadSize); i++) {
            ss << uppercase << hex << setw(2) << setfill('0')
               << static_cast<int>(_data[i + headerLen]);
            if (i < payloadSize - 1) ss << " ";
            if (((i + 1) % 6) == 0) ss << endl;
        }
        ss << "--end-- " << endl;
    }
    stream << ss.str();
}

RawPacket::RawPacket(const MACAddress& srcMac, const MACAddress& dstMac,
                     size_t size, IDataSource& source)
    : DataPacket(RawPacket::HEADER_SIZE, size - RawPacket::HEADER_SIZE, source), seqNum(0)
{
    // Common RawPacket stream header
    //  6 bytes - dst MAC address
    //  6 bytes - src MAC address
    //  4 bytes - 802.1Q VLAN tag
    //  2 bytes - ether type
    //  2 bytes - payload length  (for tracking purposes)
    //  4 bytes - sequence number (for tracking purposes)
    auto start = begin(_data);

    // Insert dest and source MAC addresses
    std::copy(begin(dstMac), end(dstMac), start);
    std::copy(begin(srcMac), end(srcMac), start + 6);

    // Set VLAN tag and EtherType
    writeNetOrder16(start + 12, RawPacket::VLAN_TPID);
    writeNetOrder16(start + 14, (RawPacket::VLAN_DEFAULT_PRIORITY << 13) | RawPacket::VLAN_DEFAULT_ID);
    writeNetOrder16(start + 16, RawPacket::ETHER_TYPE_EXPERIMENTAL);
    
}

void RawPacket::writePayloadLen()
{
    writeNetOrder16(begin(_data) + 18, _size - headerLen);
}

void RawPacket::writeSeqNum()
{
    writeNetOrder32(begin(_data) + 20, seqNum);
    seqNum++;
}

bool RawPacket::fill()
{
    bool filled = DataPacket::fill();
    if (filled) 
    {
        writeSeqNum();
        writePayloadLen();
    }
    return filled;
}

void RawPacket::reset()
{
    DataPacket::reset();
    seqNum = 0;
}

RawPacketNoVLAN::RawPacketNoVLAN(const MACAddress& srcMac, const MACAddress& dstMac,
                     size_t size, IDataSource& source)
    : DataPacket(RawPacketNoVLAN::HEADER_SIZE, size - RawPacketNoVLAN::HEADER_SIZE, source), seqNum(0)
{
    // Common RawPacket stream header
    //  6 bytes - dst MAC address
    //  6 bytes - src MAC address
    //  2 bytes - ether type
    //  2 bytes - payload length  (for tracking purposes)
    //  4 bytes - sequence number (for tracking purposes)
    auto start = begin(_data);

    // Insert dest and source MAC addresses
    std::copy(begin(dstMac), end(dstMac), start);
    std::copy(begin(srcMac), end(srcMac), start + 6);

    // Write EtherType
    writeNetOrder16(start + 12, RawPacketNoVLAN::ETHER_TYPE_EXPERIMENTAL);
}

void RawPacketNoVLAN::writePayloadLen()
{
    writeNetOrder16(begin(_data) + 14, _size - headerLen);
}

void RawPacketNoVLAN::writeSeqNum()
{
    writeNetOrder32(begin(_data) + 16, seqNum);
    seqNum++;
}

bool RawPacketNoVLAN::fill()
{
    bool filled = DataPacket::fill();
    if (filled) 
    {
        writeSeqNum();
        writePayloadLen();
    }
    return filled;
}

void RawPacketNoVLAN::reset()
{
    DataPacket::reset();
    seqNum = 0;
}

CPTSPacket::CPTSPacket(const MACAddress& srcMac, const MACAddress& dstMac)
    : Packet(CPTSPacket::HEADER_SIZE), seqNum(0), messageType(0)
{
    // Common CPTS Packet stream header
    //  6 bytes     - dst MAC address
    //  6 bytes     - src MAC address
    //  2 bytes     - ether type
    //  1 byte      - message type (set 0x1x, where x is messageType)
    //  1 byte      - PTP version (set 0x02 for IEEE 1588-2008 (v2))
    //  2 bytes     - payload length
    //  1 byte      - domain number
    //  1 byte      - reserved
    //  2 bytes     - flags
    //  8 bytes     - correction field
    //  4 bytes     - reserved
    //  10 bytes    - sourcePortIdentity (ClockIdentity of bytes
    //  2 bytes     - sequence ID
    //  1 byte      - control
    //  1 byte      - logMessageInterval
    
    auto start = begin(_data);

    // Insert dest and source MAC addresses
    std::copy(begin(dstMac), end(dstMac), start);
    std::copy(begin(srcMac), end(srcMac), start + 6);

    // Write EtherType
    writeNetOrder16(start + 12, CPTSPacket::ETHER_TYPE_PTP);
    // Write PTP version
    writeNetOrder8(start + 15, 0x02U);
    // Write payload length
    writeNetOrder16(start + 16, CPTSPacket::HEADER_SIZE);
   
}

void CPTSPacket::setMessageType(uint8_t messageType)
{
    this->messageType = messageType & 0x0FU;
}

void CPTSPacket::writeSeqNum()
{
    writeNetOrder16(begin(_data) + 44, seqNum);
    seqNum++;
}

void CPTSPacket::writeMessageType()
{
    writeNetOrder8(begin(_data) + 14, (0x10U | messageType));
}

bool CPTSPacket::fill()
{
    writeMessageType();
    writeSeqNum();
    
    return true;
}

void CPTSPacket::reset()
{
    seqNum = 0;
}

static void writeNetOrder8(vector<uint8_t>::iterator it, uint8_t val)
{
    it[0] = val;
}

static void writeNetOrder16(vector<uint8_t>::iterator it, uint16_t val)
{
    val = htons(val);
    it[0] = val & 0xFF;
    it[1] = val >> 8;
}

static void writeNetOrder32(vector<uint8_t>::iterator it, uint32_t val)
{
    val = htonl(val);
    it[0] = val & 0xFF;
    it[1] = (val >> 8) & 0xFF;
    it[2] = (val >> 16) & 0xFF;
    it[3] = (val >> 24) & 0xFF;
}

ostream& operator<<(ostream& os, const DataPacket& packet)
{
    packet.print(os);
    return os;
}
