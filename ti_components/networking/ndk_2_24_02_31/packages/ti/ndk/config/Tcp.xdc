/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 *  ======== Tcp.xdc ========
 *
 *  Tcp module definition file and initial values.
 */

/*!
 *  ======== Tcp ========
 *  NDK Transmission Control Protocol (TCP) settings and configuration.
 *
 *  The Tcp module is used to configure settings for TCP, including:
 *
 *  @p(blist)
 *      - Buffer sizes
 *      - Maximum number of reassembly packets
 *      - Idle time
 *      - KEEP probe settings
 *  @p
 */

@Template("./Tcp.xdt")

metaonly module Tcp {

    /*
     * Default values
     *  @_nodoc
     */
    const Int defaultMaxReasmPkts  = 2;
    const Int defaultTxBufSize     = 8192;
    const Int defaultRxBufSize     = 8192;
    const Int defaultRxBufLimit    = 8192;
    const Int defaultKeepIdleTime  = 72000;
    const Int defaultKpProbIntv    = 750;
    const Int defaultKpProbTimeout = 6000;

    /*!
     *  Specifies the maximum number of reassembly packets allowed per
     *  TCP socket.
     */
    config Int maxNumReasmPkts = defaultMaxReasmPkts;

    /*!
     *  Sets the size of the TCP send buffer.
     */
    config Int transmitBufSize = defaultTxBufSize;

    /*!
     *  Sets the size of the TCP receive buffer (copy mode).
     */
    config Int receiveBufSize = defaultRxBufSize;

    /*!
     *  Sets the max number of cumulative bytes in packet buffers that can be
     *  queued up at any given TCP based socket (non-copy mode).
     */
    config Int receiveBufLimit = defaultRxBufLimit;

    /*!
     *  Amount of time to allow socket to idle. Only affects sockets
     *  specified with SO_KEEPALIVE value.
     *
     *  Time units for this value are in 0.1 seconds.
     */
    config Int keepIdleTime = defaultKeepIdleTime;

    /*!
     *  Time interval specifying the amount of time in between TCP KEEP probes
     *  Only affects sockets specified with SO_KEEPALIVE value.
     *
     *  Used to determine if socket should be kept open. Time units for this
     *  value are in 0.1 seconds.
     */
    config Int keepProbeInterval = defaultKpProbIntv;

    /*!
     *  Time TCP will continue to send unanswered KEEP probes before timing out
     *  the connection.
     *
     *  Time units for this value are in 0.1 seconds.
     */
    config Int keepProbeTimeout = defaultKpProbTimeout;

}
