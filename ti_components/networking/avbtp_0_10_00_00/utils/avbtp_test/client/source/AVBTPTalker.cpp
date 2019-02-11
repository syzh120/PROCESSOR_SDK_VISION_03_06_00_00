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
#include "Packet.hpp"
#include "Socket.hpp"
#include "AVBTPTalker.hpp"



using namespace test;

AVBTPTalker::AVBTPTalker(const MACAddress& srcMAC, const MACAddress& dstMAC,
                         uint16_t id, IDataSource& source, const RawSocket& socket)
    : packet(srcMAC, dstMAC, id, source), pSocket(&socket)
{
}

bool AVBTPTalker::send()
{
    if (packet.fill())
    {
        return pSocket->send(packet);
    }
    return false;
}

void AVBTPTalker::setEthertype(uint16_t ethertype)
{
    packet.setEthertype(ethertype);
}

void AVBTPTalker::setVLAN(uint16_t vlanId, uint8_t vlanPriority)
{
    packet.setVLAN(vlanId, vlanPriority);
}

void AVBTPTalker::setSubtype(uint8_t subtype)
{
    packet.setSubtype(subtype);
}

void AVBTPTalker::setCvFormattype(uint8_t cvformattype)
{
    packet.setCvFormattype(cvformattype);
}

void AVBTPTalker::setCvFormatSubtype(uint8_t *codectype, uint8_t talkernum)
{
    packet.setCvFormatSubtype(codectype[talkernum]);
}

void AVBTPTalker::reset()
{
    packet.reset();
}

