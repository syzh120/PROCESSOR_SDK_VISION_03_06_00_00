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

// Linux headers
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>

// Local project headers
#include "Socket.hpp"
#include "Packet.hpp"

using namespace std;
using namespace test;

// FDHandle Implementation
FDHandle::FDHandle() : fd(-1)
{
}

FDHandle::FDHandle(int fd) : fd(fd)
{
}

FDHandle::~FDHandle()
{
    closeit();
}

int FDHandle::get() const
{
    return fd;
}

void FDHandle::closeit()
{
    if (fd != -1) ::close(fd);
}

void FDHandle::operator=(int thefd)
{
    closeit();
    fd = thefd;
}


// AddrInfo Implementation
AddrInfo::AddrInfo(string ipString, string portString) : pAddrInfo(nullptr)
{
    struct addrinfo hints = {};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int ret =
        getaddrinfo(ipString.c_str(), portString.c_str(), &hints, &pAddrInfo);
    if (ret != 0 || pAddrInfo == nullptr) {
        string errorString(gai_strerror(ret));
        cout << "error: " << errorString;
        throw invalid_argument(errorString);
    }
}

AddrInfo::~AddrInfo()
{
    freeaddrinfo(pAddrInfo);
}


// BaseSocket Implementation
BaseSocket::BaseSocket()
{
}

BaseSocket::~BaseSocket() = default;


// TCPSocket Implementation
TCPSocket::TCPSocket(string ipString, string portString)
    : ip(std::move(ipString)), port(std::move(portString))
{
    AddrInfo addr(ip, port);

    // Note socketFd is a FDHandle object so the fd will not leak
    socketFd = ::socket(addr.ai_family(), SOCK_STREAM, 0);
    rxTimeout = 0;
    txTimeout = 0;

    if (socketFd.get() == -1)
    {
        perror("Opening TCP socket");
        throw Error("failed opening TCP socket");
    }

    // Set TCP_NODELAY option since we want to try and send data
    // on a per-packet basis, without engaging Nagle's algorithm
    {
        int flag = 0;
        int result = ::setsockopt(socketFd.get(),
                                  IPPROTO_TCP,
                                  TCP_NODELAY,
                                  (char *) &flag,
                                  sizeof(int));
        if (result < 0)
        {
            perror("Setting TCP socket option");
            throw Error("unable to set TCP_NODELAY mode option!");
        }
    }

    int ret = ::connect(socketFd.get(), addr.ai_addr(), addr.ai_addrlen());
    if (ret == -1)
    {
        perror("Connecting TCP socket");
        throw ConnectionError("socket is unable to connect!");
    }
}

TCPSocket::~TCPSocket()
{
    // Shutdown indicating that all in progress packet activity
    // can be discarded
    ::shutdown(socketFd.get(), SHUT_RDWR);
}

void TCPSocket::reconnect(void)
{
    AddrInfo addr(ip, port);

    // Note socketFd is a FDHandle object so the fd will not leak
    socketFd = ::socket(addr.ai_family(), SOCK_STREAM, 0);

    if (socketFd.get() == -1)
    {
        perror("Opening TCP socket");
        throw Error("failed opening TCP socket");
    }

    int ret = ::connect(socketFd.get(), addr.ai_addr(), addr.ai_addrlen());
    if (ret == -1)
    {
        perror("Connecting TCP socket");
        throw ConnectionError("socket is unable to connect!");
    }

    if (rxTimeout != 0)
    {
        //cout << "[TCPSocket]: Setting Rx timeout" << endl;
        setRcvTimeout(rxTimeout);
    }
    if (txTimeout != 0)
    {
        //cout << "[TCPSocket]: Setting Tx timeout" << endl;
        setSendTimeout(txTimeout);
    }
}

bool TCPSocket::send(const Packet& packet) const
{
    int ret = ::send(socketFd.get(), packet.data(), packet.size(), 0);
    if (ret == -1)
    {
        perror("sending");
        throw Error("socket unable to send data!");
    }
    return true;
}

vector<uint8_t> TCPSocket::receive(size_t size) const
{
    vector<uint8_t> buf(size);
    size_t remaining = buf.size();
    size_t idx = 0;
    while (remaining > 0)
    {
        ssize_t ret = ::recv(socketFd.get(), &buf[idx], remaining, 0);
        if (ret < 0)
        {
            perror("socket error during recv");
            throw Error("socket error on receive (only got " + std::to_string(idx) + " of " + std::to_string(size) + " bytes)!");
        }
        else if (ret == 0)
        {
            throw ConnectionError("socket was disconnected!");
        }
        else
        {
            idx += ret;
            remaining -= ret;
        }
    }

    return buf;
}

void TCPSocket::setSendTimeout(uint32_t secs)
{
    struct timeval to;

    /* Save txTimeout */
    txTimeout = secs;

    to.tv_sec = secs;
    to.tv_usec = 0;
    setsockopt(socketFd.get(), SOL_SOCKET, SO_SNDTIMEO, &to, sizeof(to));
}

void TCPSocket::setRcvTimeout(uint32_t secs)
{
    struct timeval to;

    /* Save rxTimeout */
    rxTimeout = secs;

    to.tv_sec = secs;
    to.tv_usec = 0;
    setsockopt(socketFd.get(), SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to));
}


// UDPSocket Implementation
UDPSocket::UDPSocket(string ipString, string portString)
    : ip(std::move(ipString)), port(std::move(portString))
{
    AddrInfo addr(ip, port);

    // Note socketFd is a FDHandle object so the fd will not leak
    socketFd = ::socket(addr.ai_family(), SOCK_DGRAM, 0);

    rxTimeout = 0;
    txTimeout = 0;

    if (socketFd.get() == -1)
    {
        perror("Opening UDP socket");
        throw Error("failed opening UDP socket");
    }

    int ret = ::connect(socketFd.get(), addr.ai_addr(), addr.ai_addrlen());
    if (ret == -1)
    {
        perror("Connecting TCP socket");
        throw ConnectionError("socket is unable to connect!");
    }
}

bool UDPSocket::send(const Packet& packet) const
{
    int ret = ::send(socketFd.get(), packet.data(), packet.size(), 0);
    if (ret == -1)
    {
        perror("sending");
        throw Error("socket unable to send data!");
    }
    return true;
}

vector<uint8_t> UDPSocket::receive(size_t size) const
{
    vector<uint8_t> buf(size);
    size_t remaining = buf.size();
    size_t idx = 0;
    while (remaining > 0)
    {
        ssize_t ret = ::recv(socketFd.get(), &buf[idx], remaining, 0);
        if (ret < 0)
        {
            perror("socket error during recv");
            throw Error("socket error on receive (only got " + std::to_string(idx) + " of " + std::to_string(size) + " bytes)!");
        }
        else if (ret == 0)
        {
            throw ConnectionError("socket was disconnected!");
        }
        else
        {
            idx += ret;
            remaining -= ret;
        }
    }

    return buf;
}

void UDPSocket::setSendTimeout(uint32_t secs)
{
    struct timeval to;

    /* Save txTimeout */
    txTimeout = secs;

    to.tv_sec = secs;
    to.tv_usec = 0;
    setsockopt(socketFd.get(), SOL_SOCKET, SO_SNDTIMEO, &to, sizeof(to));
}

void UDPSocket::setRcvTimeout(uint32_t secs)
{
    struct timeval to;

    /* Save rxTimeout */
    rxTimeout = secs;

    to.tv_sec = secs;
    to.tv_usec = 0;
    setsockopt(socketFd.get(), SOL_SOCKET, SO_RCVTIMEO, &to, sizeof(to));
}


// RawSocket Implementation
RawSocket::RawSocket(const std::string& devName, const MACAddress& dstAddr)
    : sockAddr{}
{
    sockAddr.sll_family = AF_PACKET;
    sockAddr.sll_halen  = ETHER_ADDR_LEN;
    std::copy(begin(dstAddr), end(dstAddr), begin(sockAddr.sll_addr));

    socketFd = ::socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (socketFd.get() == -1)
    {
        perror("Opening packet socket");
        throw runtime_error("failed to open packet socket");
    }

    struct ifreq ifReq;

    auto ioctlReq = [&](int ioctNum)
    {
        ifReq = {};
        size_t len = devName.copy(&ifReq.ifr_name[0], IFNAMSIZ - 1, 0);
        ifReq.ifr_name[len] = '\0';
        return ::ioctl(socketFd.get(), ioctNum, &ifReq);
    };

    int ret = ioctlReq(SIOCGIFINDEX);
    if (ret == -1) {
        perror("Getting interface index");
        throw runtime_error("failed requesting interface index");
    }

    sockAddr.sll_ifindex = ifReq.ifr_ifindex;

    ret = ioctlReq(SIOCGIFHWADDR);
    if (ret == -1) {
        perror("Getting src mac address");
        throw runtime_error("failed requesting interface MAC address");
    }

    auto b = begin(ifReq.ifr_hwaddr.sa_data);
    auto e = end(ifReq.ifr_hwaddr.sa_data);

    srcMacAddr = {reinterpret_cast<uint8_t*>(b), reinterpret_cast<uint8_t*>(e)};
}

bool RawSocket::send(const Packet& packet) const
{
    int ret = ::sendto(socketFd.get(), packet.data(), packet.size(), 0,
                       reinterpret_cast<const struct sockaddr*>(&sockAddr),
                       sizeof(sockAddr));
    if (ret == -1)
    {
        perror("sending");
        throw Error("socket unable to send data!");
    }
    return true;
}

MACAddress RawSocket::getSrcMAC() const
{
    return srcMacAddr;
}
