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

#ifndef _DATA_SOURCE_
#define _DATA_SOURCE_

// C++ STL headers
#include <vector>
#include <fstream>
#include <memory>
#include <mutex>

// Legacy C headers
#include <cstddef>
#include <cstdint>

namespace test
{
    class IDataSource
    {
        public:
            virtual ~IDataSource();
            virtual std::size_t read(uint8_t* data, std::size_t size) = 0;
            virtual void reset() = 0;
    };

    class FileSource : public IDataSource
    {
        public:
            FileSource(const std::string& name, bool loop = false);

            std::size_t read(uint8_t* data, std::size_t size);
            void reset();

        private:
            std::fstream fStream;
            bool loop;
    };

    class RandomDataSource : public IDataSource
    {
        public:
            RandomDataSource(std::size_t size, bool loop = false);

            std::size_t read(uint8_t* data, std::size_t size);
            void reset();

        private:
            std::size_t readIdx;
            std::vector<uint8_t> data;
            bool loop;
    };
}
#endif  // _DATA_SOURCE_
