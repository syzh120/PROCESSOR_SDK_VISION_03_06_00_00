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
#include <random>
#include <exception>

// Local project headers
#include "DataSource.hpp"

using namespace std;
using namespace test;

IDataSource::~IDataSource() = default;

FileSource::FileSource(const std::string& name, bool loop)
    : fStream(name, fstream::in | fstream::binary), loop(loop)
{
}

std::size_t FileSource::read(uint8_t* data, std::size_t size)
{
    size_t readSize = fStream.readsome(reinterpret_cast<char*>(data), size);

    if (loop && readSize == 0) {
        fStream.seekg(0, fstream::beg);
        readSize = fStream.readsome(reinterpret_cast<char*>(data), size);
    }

    return readSize;
}

void FileSource::reset()
{
    fStream.seekg(0, fstream::beg);
}

RandomDataSource::RandomDataSource(size_t size, bool loop)
    : readIdx(0), data(size), loop(loop)
{
    uniform_int_distribution<uint8_t> distribution(0u, 255u);
    default_random_engine engine;
    for (auto& d : data) {
        d = distribution(engine);
    }
}

std::size_t RandomDataSource::read(uint8_t* out, std::size_t size)
{
    size_t remaining = data.size() - readIdx;
    size_t copySize = min(size, remaining);
    if (copySize > 0) {
        auto inputBegin = begin(data) + readIdx;
        std::copy(inputBegin, inputBegin + copySize, out);
        readIdx += copySize;
    }
    if (loop && readIdx == data.size()) readIdx = 0;
    return copySize;
}

void RandomDataSource::reset()
{
    readIdx = 0;
}

IncrementingDataSource::IncrementingDataSource(uint16_t startValue)
    : fillValue(startValue)
{
}

std::size_t IncrementingDataSource::read(uint8_t *out, std::size_t size)
{
    uint16_t *out16 = (uint16_t *)out;
    for (int i=0; i<(size/2); i++)
    {
        out16[i] = fillValue;
    }
    if (size & 0x1)
    {
        out[size-1] = 0xFF;
    }
    fillValue += 1;
    return size;
}

void IncrementingDataSource::reset()
{
    fillValue = 0;
}
