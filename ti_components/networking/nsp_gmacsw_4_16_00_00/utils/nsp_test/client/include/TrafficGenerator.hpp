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

#ifndef _TRAFFIC_GENERATOR_
#define _TRAFFIC_GENERATOR_

// C++ STL headers
#include <thread>
#include <atomic>
#include <vector>
#include <string>

#include "Mac.hpp"

namespace test
{
    class TrafficGenerator
    {
        public:
            TrafficGenerator();
            TrafficGenerator(uint32_t packetSize, uint32_t mbitRate);
            virtual ~TrafficGenerator();

            void run();
            void stop();

            virtual void reset() = 0;

            virtual void setPacketSize(uint32_t packetSize);
            virtual void setMBitRate(uint32_t mbitRate);
            virtual uint32_t getPacketsSentCount(void);

        protected:
            virtual uint32_t generate(const std::atomic_bool& shutDown) = 0;

            uint32_t            packetSize;
            uint32_t            mbitRate;

        private:
            uint32_t            packetsSentCount;
            std::atomic_bool    shutDown;
    };

    class TrafficClassManager
    {
        public:
            TrafficClassManager(std::string dev, bool verbose = false, uint32_t defaultClass = 1);
            ~TrafficClassManager();

            void reset();
            void setClass(std::string classid, std::string rate = "100mbit", std::string prio = "100");
            void deleteClass(std::string classid);
            void setFilter(std::string protocol, std::string filter, std::string classid);

        private:
            void deleteRoot();
            void addRoot();
            std::string dev;
            bool verbose;
            std::string rootHandle;
            uint32_t defaultClass;
    };

    class TrafficGenThread
    {
        public:
            TrafficGenThread(TrafficGenerator& gen);
            ~TrafficGenThread();

            void start();
            void stop();

        private:
            std::thread t;
            TrafficGenerator& gen;
    };

    class TCPTrafficGenerator : public TrafficGenerator
    {
        public:
            static const std::string TEST_TCP_QDISC_CLASS;
            static const std::string TEST_TCP_QDISC_PRIO;
            static const int DEFAULT_TCP_PACKET_SIZE    = 1500;
            static const int DEFAULT_TCP_MBIT_RATE      = 5;
            TCPTrafficGenerator(std::string ip, std::string port,
                                TrafficClassManager& tcManager, bool verbose = false);
            void reset();
            void setPacketSize(uint32_t packetSize);
            void setEchoExpected(bool echoExpected)
            {
                this->echoExpected = echoExpected;
            }

        protected:
            uint32_t generate(const std::atomic_bool& shutDown);

        private:
            std::string ip;
            std::string port;
            bool        echoExpected;
            bool        verbose;
            TrafficClassManager& tcManager;
    };

    class UDPTrafficGenerator : public TrafficGenerator
    {
        public:
            static const std::string TEST_UDP_QDISC_CLASS;
            static const std::string TEST_UDP_QDISC_PRIO;
            static const int DEFAULT_UDP_PACKET_SIZE    = 1024;
            static const int DEFAULT_UDP_MBIT_RATE      = 10;
            UDPTrafficGenerator(std::string ip, std::string port,
                               TrafficClassManager& tcManager, bool verbose);
            void reset();
            void setPacketSize(uint32_t packetSize);
            void setEchoExpected(bool echoExpected)
            {
                this->echoExpected = echoExpected;
            }

        protected:
            uint32_t generate(const std::atomic_bool& shutDown);


        private:
            std::string ip;
            std::string port;
            bool        echoExpected;
            bool        verbose;
            TrafficClassManager& tcManager;
    };

    class RawTrafficGenerator : public TrafficGenerator
    {
        public:
            static const std::string TEST_RAW_QDISC_CLASS;
            static const std::string TEST_RAW_QDISC_PRIO;
            static const int DEFAULT_RAW_PACKET_SIZE    = 1500;
            static const int DEFAULT_RAW_MBIT_RATE      = 100;
            RawTrafficGenerator(std::string dev, MACAddress& dstMac,
                                TrafficClassManager& tcManager, bool verbose);

            void reset();
            void setVLAN(bool enabled);

        protected:
            uint32_t generate(const std::atomic_bool& shutDown);

        private:
            std::string dev;
            MACAddress  dstMac;
            bool        VLANEnabled;
            bool        verbose;
            TrafficClassManager& tcManager;
    };
}

#endif  // _TRAFFIC_GENERATOR_
