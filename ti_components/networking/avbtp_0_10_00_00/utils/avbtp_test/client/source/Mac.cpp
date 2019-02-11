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
#include <stdexcept>

// Local project headers
#include "Mac.hpp"
#include "Utils.hpp"

using namespace std;
using namespace test;

MACAddress::MACAddress(const string& addrString)
{
    vector<string> tokens = tokenize(addrString, ':');
    if (tokens.size() != 6)
        throw invalid_argument("Bad MAC string - not enough octets");

    auto it = std::begin(macAddr);
    for (const auto& t : tokens) {
        auto x = stoi(t, nullptr, 16);
        if (x < 0 || x > 255)
            throw invalid_argument("Bad MAC Address - octet out of range");
        *it = x;
        ++it;
    }
}

MACAddress::MACAddress(std::initializer_list<uint8_t> args)
{
    if (args.size() != 6)
        throw invalid_argument("Initializer list should have 6 elements");
    std::copy(std::begin(args), std::end(args), std::begin(macAddr));
}

MACAddress::MACAddress(const std::array<uint8_t, 6>& address) : macAddr(address)
{
}

MACAddress::MACAddress(const uint8_t* b, const uint8_t* e)
{
    if ((e - b) < 6) throw invalid_argument("source does not have 6 elements");
    for (size_t i = 0; i < macAddr.size(); i++) {
        macAddr[i] = b[i];
    }
}

void MACAddress::print(ostream& stream) const
{
    stringstream ss;
    for (size_t i = 0; i < macAddr.size(); i++) {
        ss << uppercase << hex << setw(2) << setfill('0')
           << static_cast<int>(macAddr[i]);
        if (i < macAddr.size() - 1) ss << ":";
    }
    stream << ss.str();
}

ostream& operator<<(ostream& os, const MACAddress& mac)
{
    mac.print(os);
    return os;
}
