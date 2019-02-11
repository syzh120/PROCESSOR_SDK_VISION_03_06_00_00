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

// Local project headers
#include "Options.hpp"

using namespace std;
using namespace test;

Options::Options(const map<string, OptVal>& defaults) : opts(defaults)
{
}

bool Options::parseCmdLine(int argc, char* argv[])
{
    int nargs = argc - 1;
    int i = 0;

    auto nextArg = [&]() {
        ++i;
        --nargs;
        return argv[i];
    };

    string option;
    auto findOption = [&]() {
        while (nargs > 0) {
            string arg(nextArg());
            if (arg.find("--") == 0) {
                option = arg.substr(2);
                return true;
            }
        }
        return false;
    };

    auto getArgs = [&]() {
        string result;
        while (nargs > 0) {
            string arg(nextArg());
            if (arg.find("--") == 0) {
                // rewind
                --i;
                ++nargs;
                return result;
            }
            if (!result.empty())
                result.append(" ");
            result.append(arg);
        }
        return result;
    };

    while (findOption()) {
        if (option.find("help") == 0) return false;

        // Encountered an option specifier in the command line,
        // let's check if it's in our list of supported options
        auto entry = opts.find(option);
        if (entry == opts.end()) continue;

        // OK, it is a supported option - let's check if its
        // boolean in which case we don't need an argument
        // but the argument could be used to turn the boolean option off
        auto& optVal = (*entry).second;
        string value = getArgs();
        if (optVal.type == OptVal::boolean) {
            optVal.value = "true";
            if (value.find("false") == 0) optVal.value = "false";
        } else {

            if (!value.empty()) optVal.value = value;
        }
    }
    return hasRequired();
}

bool Options::hasRequired() const
{
    for (auto& opt : opts) {
        if (opt.second.req == OptVal::required && opt.second.value.empty()) {
            return false;
        }
    }
    return true;
}

string Options::get(const string& name) const
{
    string option;
    auto entry = opts.find(name);
    if (entry != opts.end()) option = entry->second.value;
    return option;
}

bool Options::getBool(const string& name) const
{
    string option = get(name);
    if (!option.empty()) return option.find("true") == 0;
    return false;
}

int Options::getInt(const string& name) const
{
    string option = get(name);
    if (!option.empty()) return stoi(option);
    return -1;
}

void Options::print(ostream& stream) const
{
    for (auto& opt : opts) {
        stream << opt.first << ": " << opt.second.value << endl;
    }
}

ostream& operator<<(ostream& os, const Options& opt)
{
    opt.print(os);
    return os;
}
