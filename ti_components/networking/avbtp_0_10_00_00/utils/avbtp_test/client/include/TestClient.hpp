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
#include <chrono>

namespace test
{
    class TCPTrafficGenerator;
    class UDPTrafficGenerator;
    class AVBTrafficGenerator;
    class TrafficClassManager;
    class MACAddress;
    class Options;
    class JPEGSource;
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
            AVBTrafficGenerator *avbGen;
            TrafficClassManager *tcManager;
            std::vector<std::unique_ptr<UnitTest>> tests;
            Options *opts;
            std::vector<JPEGSource>* dataSources;
    };

    class UnitTest
    {
        public:
            UnitTest(TCPSocket& cmdSocket);
            virtual ~UnitTest();

            virtual bool execute(void) = 0;
            virtual std::string results();
            virtual std::string description() const = 0;

        protected:
            TCPSocket *cmdSocket;
    };

    class TrafficTest : public UnitTest
    {
        public:
            enum class Type
            {
                AVB_ONLY,
                AVB_PLUS_TCP,
            };
            TrafficTest(TCPSocket& cmdSocket, Type trafficType, uint32_t genTimeSecs, uint32_t wakeupRateInSecs = 0);
            virtual ~TrafficTest();
            virtual bool execute(void) = 0;

        protected:
            virtual bool beforeTraffic(void) = 0;
            virtual bool duringTraffic(void) = 0;
            virtual bool afterTraffic(void) = 0;

            Type     trafficType;
            uint32_t genTimeSecs;
            uint32_t wakeupRateInSecs;
    };

    class AVBnTCPTrafficTest : public TrafficTest
    {
        public:
            AVBnTCPTrafficTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                               AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                               uint32_t genTimeSecs, uint32_t wakeupRateInSecs);
            bool execute(void);
            std::string description() const;

        protected:
            virtual bool beforeTraffic(void);
            virtual bool duringTraffic(void);
            virtual bool afterTraffic(void);
            AVBTrafficGenerator *avbGen;
            TCPTrafficGenerator *tcpGen;
    };

    class ShutdownStressTest : public AVBnTCPTrafficTest
    {
        public:
            ShutdownStressTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                                       AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                                       uint32_t numIterations);
            std::string description() const;

        protected:
            bool duringTraffic(void);
            bool afterTraffic(void);

        private:
            uint32_t numIterations;
            uint32_t currIteration;
    };

    class AVBTimedPacketLossTest : public AVBnTCPTrafficTest
    {
        public:
            AVBTimedPacketLossTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                                   AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                                   uint32_t genTimeSecs);
            std::string description() const;
            std::string results();

        protected:
            bool beforeTraffic();
            bool afterTraffic();

        private:
            std::string resultsStr;
    };

    class AVBLoadTest : public AVBnTCPTrafficTest
    {
        public:
            struct LoadRange
            {
                float cpuLoadMax;
                float taskLoadMax;
                float hwiLoadMax;
            };
            AVBLoadTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                        AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen,
                        const LoadRange& loadRange, uint32_t numMeasures, bool verbose = false);
            std::string description() const;
            std::string results();
            void setNumMeasures(uint32_t num)
            {
                numMeasures = num;
            }
            void setRanges(const LoadRange& loadRange);

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();

        private:
            LoadRange   loadRange;
            uint32_t    numMeasures;
            float       avgCpuLoad;
            float       avgTaskLoad;
            float       avgHwiLoad;
            bool        verbose;
            std::string resultsStr;
    };

    class AVBParserErrorTest : public AVBnTCPTrafficTest
    {
        public:
            AVBParserErrorTest(TCPSocket& cmdSocket, TrafficTest::Type trafficType,
                               AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen);
            std::string description() const;
            std::string results();

        protected:
            bool beforeTraffic();
            bool duringTraffic();
            bool afterTraffic();

        private:
            std::string resultsStr;
            std::chrono::time_point<std::chrono::system_clock> start;
    };

    class OutputValidationTest : public AVBnTCPTrafficTest
    {
        public:
            OutputValidationTest(TCPSocket& cmdSocket,
                                 AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen);
            std::string description() const;
            std::string results();

        protected:
            bool beforeTraffic();
            bool afterTraffic();

        private:
            std::string resultsStr;
    };

    class EOIHandlingTest : public AVBnTCPTrafficTest
    {
        public:
            EOIHandlingTest(TCPSocket& cmdSocket, 
                            AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen);
            std::string description() const;
            std::string results();

        protected:
            bool beforeTraffic();
            bool afterTraffic();

        private:
            uint32_t expectedEOIErrors;
            std::string resultsStr;
    };
    
    class RSTHandlingTest : public AVBnTCPTrafficTest
    {
        public:
            RSTHandlingTest(TCPSocket& cmdSocket, 
                            AVBTrafficGenerator& avbGen, TCPTrafficGenerator& tcpGen);
            std::string description() const;
            std::string results();

        protected:
            bool beforeTraffic();
            bool afterTraffic();

        private:
            uint32_t expectedRSTMarkersDelta;
            std::string resultsStr;
    };
    
    class AVBTxLoadTest : public UnitTest
    {
        public:
            struct LoadRange
            {
                float cpuLoadMax;
                float avbTxLoadMax;
                float hwiLoadMax;
            };
            AVBTxLoadTest(TCPSocket& socket, const LoadRange& loadRange, uint32_t numMeasures);
            bool execute(void);
            std::string description() const;
            std::string results();
            void setNumMeasures(uint32_t num)
            {
                numMeasures = num;
            }

        private:
            LoadRange   loadRange;
            uint32_t    numMeasures;
            float       avgCpuLoad;
            float       avgHwiLoad;
            float       avgTaskLoad;
            std::string resultsStr;
    };
}

#endif  // _TEST_CLIENT_
