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

#ifndef _MAC_
#define _MAC_

// C++ STL headers
#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>

// Legacy C headers
#include <cstdint>

namespace test
{
    class MACAddress
    {
        public:
            MACAddress() = default;
            MACAddress(std::initializer_list<uint8_t> args);
            MACAddress(const std::array<uint8_t, 6>& address);
            MACAddress(const std::string& addrString);
            MACAddress(const uint8_t* begin, const uint8_t* end);

            void print(std::ostream& os) const;
            std::array<uint8_t, 6>::const_iterator begin() const
            {
                return macAddr.begin();
            }
            std::array<uint8_t, 6>::const_iterator end() const
            {
                return macAddr.end();
            }

        private:
            std::array<uint8_t, 6> macAddr;
    };
}

std::ostream& operator<<(std::ostream& os, const test::MACAddress& mac);

#endif  // _MAC_
