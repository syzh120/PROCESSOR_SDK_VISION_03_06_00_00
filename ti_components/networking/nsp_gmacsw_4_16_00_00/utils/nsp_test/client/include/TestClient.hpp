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

#ifndef _TEST_CLIENT_
#define _TEST_CLIENT_

// C++ STL headers
#include <string>
#include <vector>
#include <memory>

#include "Mac.hpp"

namespace test
{
    class TCPTrafficGenerator;
    class UDPTrafficGenerator;
    class RawTrafficGenerator;
    class TrafficClassManager;
    class Options;
    class UnitTest;
    class TCPSocket;

    class TestClient
    {
        public:
            static const std::string TEST_CMD_QDISC_CLASS;
            static const std::string TEST_CMD_QDISC_RATE;
            static const std::string TEST_CMD_QDISC_PRIO;
            TestClient(Options& opts);
            ~TestClient();
            void executeAllTests();

        private:
            TCPSocket *cmdSocket;
            TCPTrafficGenerator *tcpGen;
            UDPTrafficGenerator *udpGen;
            RawTrafficGenerator *rawGen;
            TrafficClassManager *tcManager;
            std::vector<std::unique_ptr<UnitTest>> tests;
            Options *opts;
    };

    class UnitTest
    {
        public:
            UnitTest(TCPSocket *cmdSocket);
            virtual ~UnitTest();

            virtual bool execute(void) = 0;
            virtual std::string results();
            virtual std::string description() const = 0;

        protected:
            TCPSocket *cmdSocket;
    };

    class ShutdownStressTest : public UnitTest
    {
        public:
            ShutdownStressTest(TCPSocket *cmdSocket, uint32_t numIterations);
            bool execute(void);
            std::string description() const;

        private:
            uint32_t numIterations;
    };

    class StackShutdownStressTest : public UnitTest
    {
        public:
            StackShutdownStressTest(TCPSocket *cmdSocket, uint32_t numIterations);
            bool execute(void);
            std::string description() const;

        private:
            uint32_t numIterations;
    };

    class CPTSShutdownStressTest : public UnitTest
    {
        public:
            CPTSShutdownStressTest(TCPSocket *cmdSocket, uint32_t numIterations);
            bool execute(void);
            std::string description() const;

        private:
            uint32_t numIterations;
    };

    class CPTSFreqCheckTest : public UnitTest
    {
        public:
            CPTSFreqCheckTest(TCPSocket *cmdSocket);
            bool execute(void);
            std::string description() const;
    };

    class CPTSRxEthernetEventTest : public UnitTest
    {
        public:
            CPTSRxEthernetEventTest(TCPSocket *cmdSocket, std::string dev, MACAddress& dstMac);
            bool execute(void);
            std::string description() const;
    
        private:
            std::string dev;
            MACAddress  dstMac;
    };
    
    class CPTSTxEthernetEventTest : public UnitTest
    {
        public:
            CPTSTxEthernetEventTest(TCPSocket *cmdSocket, std::string dev, MACAddress& dstMac);
            bool execute(void);
            std::string description() const;
    
        private:
            std::string dev;
            MACAddress  dstMac;
    };
    
    class TrafficTest : public UnitTest
    {
        public:
            TrafficTest(TCPSocket *cmdSocket, uint32_t genTimeSecs, uint32_t wakeupRateInSecs);
            virtual ~TrafficTest();
            virtual bool execute(void) = 0;

        protected:
            virtual bool beforeTraffic() = 0;
            virtual bool duringTraffic() = 0;
            virtual bool afterTraffic() = 0;

            uint32_t genTimeSecs;
            uint32_t wakeupRateInSecs;

    };

    class TCPTrafficTest : public TrafficTest
    {
        public:
            TCPTrafficTest(TCPSocket *cmdSocket, TCPTrafficGenerator& tcpGen, uint32_t genTimeSecs = 0, uint32_t wakeupRateInSecs = 0);
            bool execute(void);

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();
            TCPTrafficGenerator *tcpGen;
    };

    class UDPTrafficTest : public TrafficTest
    {
        public:
            UDPTrafficTest(TCPSocket *cmdSocket, UDPTrafficGenerator& udpGen, uint32_t genTimeSecs = 0, uint32_t wakeupRateInSecs = 0);
            bool execute(void);

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();
            UDPTrafficGenerator *udpGen;
    };

    class TCPLoadTest : public TCPTrafficTest
    {
        public:
            struct LoadRange
            {
                float cpuLoadMax;
                float hwiLoadMax;
                float taskLoadMax;
            };
            TCPLoadTest(TCPSocket *cmdSocket, TCPTrafficGenerator& tcpGen, const LoadRange& loadRange, 
                        uint32_t numMeasures, bool echoEnabled, bool verbose);
            std::string description() const;
            std::string results();
            void setNumMeasures(uint32_t num)
            {
                numMeasures = num;
            }

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();

        private:
            LoadRange   loadRange;
            uint32_t    numMeasures;
            bool        echoEnabled;
            bool        verbose;            
            float       avgCpuLoad;
            float       avgHwiLoad;
            float       avgRxTaskLoad;
            float       avgTxTaskLoad;
            std::string resultsStr;
    };

    class TCPPerformanceTest : public TCPTrafficTest
    {
        public:
            TCPPerformanceTest(TCPSocket *cmdSocket, TCPTrafficGenerator& tcpGen, uint32_t mbitRate, uint32_t packetSize, bool echoEnabled);
            std::string description() const;
            std::string results();

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();

        private:
            static const uint32_t DEFAULT_TEST_DURATION = 30;
            static const uint32_t DEFAULT_LOAD_CHECK_INTERVAL = 2;

            uint32_t    mbitRate;
            uint32_t    packetSize;
            bool        echoEnabled;
            float       avgCpuLoad;
            float       avgHwiLoad;
            float       avgRxTaskLoad;
            float       avgTxTaskLoad;
            std::string resultsStr;
    };
    
    class UDPLoadTest : public UDPTrafficTest
    {
        public:
            struct LoadRange
            {
                float cpuLoadMax;
                float hwiLoadMax;
                float taskLoadMax;
            };
            UDPLoadTest(TCPSocket *cmdSocket, UDPTrafficGenerator& udpGen, const LoadRange& loadRange, 
                        uint32_t numMeasures, bool echoEnabled, bool verbose);
            std::string description() const;
            std::string results();
            void setNumMeasures(uint32_t num)
            {
                numMeasures = num;
            }

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();

        private:
            LoadRange   loadRange;
            uint32_t    numMeasures;
            bool        echoEnabled;
            bool        verbose;            
            float       avgCpuLoad;
            float       avgHwiLoad;
            float       avgRxTaskLoad;
            float       avgTxTaskLoad;
            std::string resultsStr;
    };

    class UDPPerformanceTest : public UDPTrafficTest
    {
        public:
            UDPPerformanceTest(TCPSocket *cmdSocket, UDPTrafficGenerator& udpGen, uint32_t mbitRate, uint32_t packetSize, bool echoEnabled);
            std::string description() const;
            std::string results();

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();

        private:
            static const uint32_t DEFAULT_TEST_DURATION = 30;
            static const uint32_t DEFAULT_LOAD_CHECK_INTERVAL = 2;

            uint32_t    mbitRate;
            uint32_t    packetSize;
            bool        echoEnabled;
            float       avgCpuLoad;
            float       avgHwiLoad;
            float       avgRxTaskLoad;
            float       avgTxTaskLoad;
            std::string resultsStr;
    };

    class RawPerformanceTest : public TrafficTest
    {
        public:
            RawPerformanceTest(TCPSocket *cmdSocket, RawTrafficGenerator& rawGen, uint32_t mbitRate, uint32_t packetSize, bool vlanEnabled);
            std::string description() const;
            std::string results();
            bool execute(void);

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();

        private:
            static const uint32_t DEFAULT_TEST_DURATION = 30;
            static const uint32_t DEFAULT_LOAD_CHECK_INTERVAL = 2;

            RawTrafficGenerator *rawGen;
            uint32_t    mbitRate;
            uint32_t    packetSize;
            bool        vlanEnabled;
            float       avgCpuLoad;
            float       avgHwiLoad;
            float       avgRxTaskLoad;
            std::string resultsStr;
    };
}
#endif  // _TEST_CLIENT_
