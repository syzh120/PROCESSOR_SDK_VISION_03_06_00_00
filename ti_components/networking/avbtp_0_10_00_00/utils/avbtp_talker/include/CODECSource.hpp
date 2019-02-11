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

#ifndef _CODEC_SOURCE_
#define _CODEC_SOURCE_

// C++ STL headers
#include <vector>
#include <fstream>
#include <memory>
#include <mutex>


/* CVF - format subtypes (also defined in avbtp.h for server) */
#define AVBTP_CVF_FORMAT_SUBTYPE_MJPEG      0x0
#define AVBTP_CVF_FORMAT_SUBTYPE_H264       0x1
#define AVBTP_CVF_FORMAT_SUBTYPE_JPEG2000   0x2

// Local project headers
#include "DataSource.hpp"

extern "C" {
#include <libavformat/avformat.h>
}

namespace test
{
    class CODECSource : public IDataSource
    {
        public:
            CODECSource();
            CODECSource(const std::string& name, bool loop = false);
            CODECSource(const CODECSource& src) = delete;
            CODECSource &operator=(CODECSource &&src);
            CODECSource(CODECSource &&src);
            ~CODECSource();

            std::size_t read(uint8_t* data, std::size_t size);
            void reset();
            void setMaxFrames(uint32_t maxNumToRead);

            int getCODECSize();
            int getCODECType();
            int getFrameCount();
            void setFrameCount();
            void enableStripEOI(bool flag);
            void insertRSTMarkers(bool flag);

            const uint8_t* getNextFrame();
            uint32_t getFrameSize() const;

        private:
            class AVFormatContextDeleter
            {
                public:
                    void operator()(AVFormatContext* p) const;
            };

            bool nextFrame();

            bool loop;
            size_t readIdx;
            AVPacket avPacket;
            int streamIdx;
            static std::once_flag avFormatInit;
            std::unique_ptr<AVFormatContext, AVFormatContextDeleter> avFmtContext;
            uint32_t maxFramesToRead;
            uint32_t numFramesRead;
            uint32_t numFrames;
            bool stripEOI;
            bool addRSTMarkers;
	    int32_t codecType = -1;
    };
}
#endif  // _CODEC_SOURCE_
