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

#ifndef _SOCKET_
#define _SOCKET_

// C++ STL headers
#include <string>
#include <vector>
#include <stdexcept>

// Linux headers
#include <netpacket/packet.h>
#include <sys/socket.h>
#include <netdb.h>

// Local project headers
#include "Mac.hpp"
#include "Utils.hpp"

namespace test
{
    class Packet;

    class FDHandle
    {
        public:
            explicit FDHandle();
            explicit FDHandle(int fd);
            ~FDHandle();
            void operator=(int fd);
            int get() const;

        private:
            void closeit();
            int fd;
    };

    class AddrInfo
    {
        public:
            AddrInfo(std::string ipString, std::string portString);
            ~AddrInfo();

            int ai_family() const
            {
                return pAddrInfo->ai_family;
            }
            struct sockaddr* ai_addr() const
            {
                return pAddrInfo->ai_addr;
            }
            socklen_t ai_addrlen() const
            {
                return pAddrInfo->ai_addrlen;
            }

        private:
            struct addrinfo* pAddrInfo;
    };

    class BaseSocket
    {

        public:
            BaseSocket();
            virtual ~BaseSocket();

            virtual bool send(const Packet& packet) const = 0;

        protected:
            FDHandle socketFd;
            uint32_t rxTimeout;
            uint32_t txTimeout;
    };

    class TCPSocket : public BaseSocket
    {
        public:
            class Error : public std::runtime_error
            {
                public:
                    explicit Error(const std::string& str) : std::runtime_error(str)
                    {
                    }
            };
            class ConnectionError : public Error
            {
                public:
                    explicit ConnectionError(const std::string& str) : Error(str)
                    {
                    }
            };
            TCPSocket(std::string ipString, std::string portString);
            TCPSocket(const TCPSocket& other) = delete;
            ~TCPSocket();

            bool send(const Packet& packet) const;
            void reconnect(void);
            std::vector<uint8_t> receive(size_t size) const;
            void setSendTimeout(uint32_t secs);
            void setRcvTimeout(uint32_t secs);

        private:
            std::string ip;
            std::string port;
    };

    class UDPSocket : public BaseSocket
    {
        public:
            class Error : public std::runtime_error
            {
                public:
                    explicit Error(const std::string& str) : std::runtime_error(str)
                    {
                    }
            };
            class ConnectionError : public Error
            {
                public:
                    explicit ConnectionError(const std::string& str) : Error(str)
                    {
                    }
            };
            UDPSocket(std::string ipString, std::string portString);
            UDPSocket(const UDPSocket& other) = delete;

            bool send(const Packet& packet) const;
            std::vector<uint8_t> receive(size_t size) const;
            void setSendTimeout(uint32_t secs);
            void setRcvTimeout(uint32_t secs);

        private:
            std::string ip;
            std::string port;
    };

    class RawSocket : public BaseSocket
    {
        public:
            class Error : public std::runtime_error
            {
                public:
                    explicit Error(const std::string& str) : std::runtime_error(str)
                    {
                    }
            };
            class ConnectionError : public Error
            {
                public:
                    explicit ConnectionError(const std::string& str) : Error(str)
                    {
                    }
            };
            RawSocket(const std::string& devName, const MACAddress& dstAddr);
            RawSocket(const RawSocket& that) = delete;

            bool send(const Packet& packet) const;

            MACAddress getSrcMAC() const;

        private:
            struct sockaddr_ll sockAddr;
            MACAddress srcMacAddr;
    };
}
#endif  // _SOCKET_
