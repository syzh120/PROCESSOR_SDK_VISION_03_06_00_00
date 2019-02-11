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

#ifndef _OPTIONS_
#define _OPTIONS_

// C++ STL headers
#include <string>
#include <map>
#include <iostream>

namespace test
{
    struct OptVal
    {
        enum class Requirement
        {
            _optional,
            _required
        };
        enum class Type
        {
            _notboolean,
            _boolean,
        };
        static const Requirement required = Requirement::_required;
        static const Requirement optional = Requirement::_optional;
        static const Type boolean = Type::_boolean;
        static const Type notboolean = Type::_notboolean;
        std::string value;
        Type type;
        Requirement req;
    };

    class Options
    {
        public:
            Options() = delete;
            Options(const std::map<std::string, OptVal>& defaults);

            bool parseCmdLine(int argc, char* argv[]);
            bool hasRequired() const;
            std::string get(const std::string& optName) const;
            bool getBool(const std::string& optName) const;
            int getInt(const std::string& optName) const;
            void print(std::ostream& stream) const;

            const std::map<std::string, OptVal>& data() const
            {
                return opts;
            }

        private:
            std::map<std::string, OptVal> opts;
    };
}

std::ostream& operator<<(std::ostream& os, const test::Options& opt);
#endif  // _OPTIONS_
