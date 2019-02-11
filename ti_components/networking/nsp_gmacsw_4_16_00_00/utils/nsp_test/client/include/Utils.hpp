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

#ifndef _UTILS_
#define _UTILS_

// C++ STL headers
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

namespace test
{
    class MACAddress;

    template <typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    std::vector<std::string> tokenize(const std::string& s, char delimiter);

    template <typename T> void replicateLast(std::vector<T>& v, size_t num)
    {
        if (v.size() != 0 && v.size() < num) {
            size_t numReplicate = num - v.size();
            for (size_t i = 0; i < numReplicate; i++) {
                v.push_back(v.back());
            }
        }
    }
    
    template< typename T > std::string int_to_hex( T i )
    {
        std::stringstream stream;
        stream  << std::setfill('0') << std::setw(sizeof(T)*2) 
                << std::hex << std::showbase << i;
        return stream.str();
    }

    class MACQueryError : public std::runtime_error
    {
        public:
            explicit MACQueryError(const std::string& str) : std::runtime_error(str)
            {
            }
    };

    MACAddress getTargetMAC(std::string ip, std::string devName);
}

#endif  // _UTILS_
