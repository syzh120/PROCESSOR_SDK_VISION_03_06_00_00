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
#include <random>
#include <exception>

// Local project headers
#include "JPEGSource.hpp"

using namespace std;
using namespace test;

std::once_flag JPEGSource::avFormatInit;

static uniform_int_distribution<uint8_t> uniformDist(0u, 7u);
static default_random_engine randEngine;

void JPEGSource::AVFormatContextDeleter::operator()(AVFormatContext* p) const
{
    avformat_close_input(&p);
}

JPEGSource::JPEGSource()
    : loop(false), readIdx(0), streamIdx(-1), maxFramesToRead(0), numFramesRead(0),
      stripEOI(false), addRSTMarkers(false)
{

}

JPEGSource::JPEGSource(const string& fileName, bool loop)
    : loop(loop), readIdx(0), streamIdx(-1), maxFramesToRead(0), numFramesRead(0),
      stripEOI(false), addRSTMarkers(false)
{
    int retVal = 0;

    std::call_once(avFormatInit, []() { av_register_all(); });

    unique_ptr<AVFormatContext, AVFormatContextDeleter> ctx(avformat_alloc_context());
    avFmtContext = std::move(ctx);

    if (avFmtContext == nullptr) {
        throw runtime_error("failed allocating avformat context");
    }

    auto avFormatCtxPtr = avFmtContext.get();
    try
    {
        retVal = avformat_open_input(&avFormatCtxPtr, fileName.c_str(), nullptr, nullptr);
        if (retVal < 0)
        {
            //cout << "avformat_open_input() called, but failed to open file:" <<  fileName.c_str() << endl;
            throw runtime_error("failed opening file");
        }
    }
    catch(std::runtime_error& e)
    {
        // This strange workaround required to actually see the thrown error message for missing files
        // This appeared as an issue with the move to GCC 4.8.2 in Ubuntu 14.04
        cout << "Runtime error - " << e.what() << endl;
        throw runtime_error(e.what());
    }
    
    if (avformat_find_stream_info(avFormatCtxPtr, nullptr) < 0)
    {
        throw runtime_error("failed populating stream information");
    }

    auto findJPEGStreamIdx = [&]() {
        for (unsigned int i = 0; i < avFmtContext->nb_streams; i++) {
            AVStream* stream = avFmtContext->streams[i];
            if (CODEC_ID_MJPEG == stream->codec->codec_id) {
                streamIdx = i;
                return true;
            }
        }
        return false;
    };

    bool foundStream = findJPEGStreamIdx();
    if (!foundStream) 
    {
        throw runtime_error("not a JPEG or MJPG file");
    }

    av_init_packet(&avPacket);
    avPacket.data = nullptr;
    avPacket.size = 0;
}

JPEGSource& JPEGSource::operator=(JPEGSource &&src)
{
    cout << "JPEGSource move assignment operator." << endl;
    if (this != &src)
    {
        loop = src.loop;
        readIdx = src.readIdx;
        avPacket = src.avPacket;
        streamIdx = src.streamIdx;
        avFmtContext = std::move(src.avFmtContext);
        maxFramesToRead = src.maxFramesToRead;
        numFramesRead = src.numFramesRead;
        stripEOI = src.stripEOI;
        addRSTMarkers = src.addRSTMarkers;
    }
    return *this;
};

JPEGSource::JPEGSource(JPEGSource &&src) :
    loop(src.loop),
    readIdx(src.readIdx),
    avPacket(src.avPacket),
    streamIdx(src.streamIdx),
    avFmtContext(std::move(src.avFmtContext)),
    maxFramesToRead(src.maxFramesToRead),
    numFramesRead(src.numFramesRead),
    stripEOI(src.stripEOI),
    addRSTMarkers(src.addRSTMarkers)
{
};

JPEGSource::~JPEGSource()
{
    if (avPacket.data != nullptr) {
        av_free_packet(&avPacket);
    }
}

void JPEGSource::enableStripEOI(bool flag)
{
    stripEOI = flag;
}

void JPEGSource::insertRSTMarkers(bool flag)
{
    addRSTMarkers = flag;
}

int JPEGSource::getJPEGSize()
{
    if (avPacket.data == nullptr || avPacket.size == 0) return 0;

    //The actual size should only include up to the JPEG EOI marker, anything after that is discarded.
    for (int i = 0; i < avPacket.size - 1; i++)
    {
        if ((avPacket.data[i] == 0xFF) && (avPacket.data[i+1] == 0xD9))
        {
            return stripEOI ? i : i+2;
        }
    }
    return avPacket.size;
}

bool JPEGSource::nextFrame()
{
    if (avPacket.data != nullptr) {
        av_free_packet(&avPacket);
        avPacket.data = nullptr;
        avPacket.size = 0;
    }

    if (maxFramesToRead > 0) {
        numFramesRead++;
        if (numFramesRead > maxFramesToRead) return false;
    }

    auto findFrame = [&]() {
        while (av_read_frame(avFmtContext.get(), &avPacket) == 0) {
            if (avPacket.stream_index == streamIdx) {
                return true;
            }
            av_free_packet(&avPacket);
        }
        return false;
    };

    bool foundFrame = findFrame();
    if (!foundFrame && loop) {
        if (av_seek_frame(avFmtContext.get(), streamIdx, 0, AVSEEK_FLAG_ANY) ==
            0) {
            foundFrame = findFrame();
        }
    }

    if (!foundFrame) {
        avPacket.data = nullptr;
        avPacket.size = 0;
    } else {
        avPacket.size = getJPEGSize();
    }

    readIdx = 0;
    return foundFrame;
}

std::size_t JPEGSource::read(uint8_t* out, std::size_t size)
{
    size_t remaining = avPacket.size - readIdx;
    if (remaining == 0) {
        if (!nextFrame()) return 0;
        remaining = avPacket.size;
    }

    size_t copySize = min(size, remaining);
    if (copySize > 0) {
        auto start = avPacket.data + readIdx;
        std::copy(start, start + copySize, out);
        if (readIdx > 0 && addRSTMarkers) {
            out[0] = 0xFF;
            //Randomize the RST marker (RST markers can range from 0xFFD0 to 0xFFD7)
            out[1] = 0xD0 | uniformDist(randEngine);
        }
        readIdx += copySize;
    }

    return copySize;
}

void JPEGSource::reset()
{
    av_seek_frame(avFmtContext.get(), streamIdx, 0, AVSEEK_FLAG_ANY);
    readIdx = 0;
    numFramesRead = 0;
}

void JPEGSource::setMaxFrames(uint32_t maxNumToRead)
{
    maxFramesToRead = maxNumToRead;
}

const uint8_t* JPEGSource::getNextFrame()
{
    nextFrame();
    return avPacket.data;
}

uint32_t JPEGSource::getFrameSize() const
{
    return avPacket.size;
}
