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

#ifndef _TALKER_CLIENT_
#define _TALKER_CLIENT_

// C++ STL headers
#include <string>
#include <vector>
#include <memory>
#include <chrono>

namespace test
{
    class AVBTrafficGenerator;
    class TrafficClassManager;
    class MACAddress;
    class Options;
    class CODECSource;
    class UnitTest;

    class TalkerClient
    {
        public:
            static const std::string TEST_CMD_QDISC_CLASS;
            static const std::string TEST_CMD_QDISC_RATE;
            static const std::string TEST_CMD_QDISC_PRIO;
            TalkerClient(Options& opts);
            ~TalkerClient();
            void execute();

        private:
            AVBTrafficGenerator *avbGen;
            TrafficClassManager *tcManager;
            std::vector<std::unique_ptr<UnitTest>> tests;
            Options *opts;
            std::vector<CODECSource>* dataSources;
    };

    class UnitTest
    {
        public:
            UnitTest();
            virtual ~UnitTest();

            virtual bool execute(void) = 0;
            virtual std::string description() const = 0;

        protected:
    };

    class TrafficTest : public UnitTest
    {
        public:
            TrafficTest(uint32_t genTimeSecs);
            virtual ~TrafficTest();
            virtual bool execute(void) = 0;

        protected:
            virtual bool beforeTraffic(void) = 0;
            virtual bool duringTraffic(void) = 0;
            virtual bool afterTraffic(void) = 0;

            uint32_t genTimeSecs;
    };

    class AVBTrafficTest : public TrafficTest
    {
        public:
            AVBTrafficTest(AVBTrafficGenerator& avbGen, uint32_t genTimeSecs, uint32_t dataRate);
            bool execute(void);
            std::string description() const;

        protected:
            virtual bool beforeTraffic(void);
            virtual bool duringTraffic(void);
            virtual bool afterTraffic(void);
            AVBTrafficGenerator *avbGen;
            uint32_t dataRate;
    };
}

#endif  // _TALKER_CLIENT_
