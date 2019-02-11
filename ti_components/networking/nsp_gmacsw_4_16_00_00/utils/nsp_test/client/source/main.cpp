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
#include <iostream>
#include <cstdlib>

// Local project headers
#include "Options.hpp"
#include "TestClient.hpp"
#include "../../common/test_common.h"

using namespace std;
using namespace test;

namespace test
{
    static void usage(const Options& opts, char *execName)
    {
        auto printOpt = [&](bool required) {
            for (auto& opt : opts.data()) {
                if (required == (opt.second.req == OptVal::required)) {
                    cout << "    --" << opt.first;
                    if (opt.second.type == OptVal::boolean) {
                        cout << " [false] ";
                    } else {
                        cout << " <value> ";
                    }
                    cout << endl;
                }
            }
            cout << endl;
        };

        cout << "Usage: " << execName << " [ OPTIONS ] REQUIRED" << endl << endl;
        cout << "REQUIRED" << endl;
        printOpt(true);
        cout << "OPTIONS" << endl;
        printOpt(false);
    }
}

int main(int argc, char* argv[])
{
    map<string, OptVal> optDefaults
    {
        {"dev", {"eth0"}},
        {"ip", {"192.168.1.200"}},
        {"tcp-port", {to_string(TEST_TCP_PORT)}},
        {"udp-port", {to_string(TEST_UDP_PORT)}},
        {"verbose", {"false", OptVal::boolean}},
        {"run-perf-tests", {"false", OptVal::boolean}},
        {"test-duration", {"60"}},     // in seconds
        {"num-load-measures", {"30"}},
        {"num-shutdowns", {"50"}},
        {"core-name", {"vayu-ipu1"}}
    };

    // Parse command line options
    Options opts(optDefaults);
    if (!opts.parseCmdLine(argc, argv))
    {
        // Parsing failed, print usage
        usage(opts, argv[0]);
        return 1;
    }

    // Print selected options
    cout << opts << endl;

    // Try executing all tests associated with the TestClient object
    try
    {
        TestClient client(opts);
        client.executeAllTests();
    }
    catch (std::exception& e)
    {
        cout << "Unit test: exception - " << e.what() << endl;
    }

    return 0;
}
