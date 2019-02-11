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
#include <iostream>

// Linux headers
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

// Local project headers
#include "Utils.hpp"
#include "Mac.hpp"
#include "Socket.hpp"

using namespace std;
using namespace test;

std::vector<std::string> test::tokenize(const std::string& input, char delimiter)
{
    std::string token;
    std::istringstream ss(input);
    std::vector<std::string> tokens;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

MACAddress test::getTargetMAC(std::string ip, std::string devName)
{
    // Function assumes ARP cache has been filled (i.e. a socket to IP has been opened)

    // Open a datagram socket - we need a socket handle to query the ARP cache
    FDHandle socketFd (::socket(AF_INET, SOCK_DGRAM, 0));
    if (socketFd.get() == -1)
    {
        perror("Opening datagram socket");
        throw MACQueryError("failed opening datagram socket");
    }

    struct arpreq req = {};
    size_t len = devName.copy(&req.arp_dev[0], IFNAMSIZ - 1, 0);
    req.arp_dev[len] = '\0';

    struct sockaddr_in *sin = reinterpret_cast<struct sockaddr_in *>(&req.arp_pa);
    sin->sin_family = AF_INET;
    sin->sin_addr.s_addr = ::inet_addr(ip.c_str());

    if (::ioctl(socketFd.get(), SIOCGARP, &req) < 0)
    {
        perror("Querying MAC address");
        throw MACQueryError("unable to query target MAC Address!");
    }

    auto b = std::begin(req.arp_ha.sa_data);
    auto e = std::end(req.arp_ha.sa_data);
    MACAddress address(reinterpret_cast<uint8_t*>(b), reinterpret_cast<uint8_t*>(e));
    return address;
}
