/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
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
 */
/*
 *  ======== NotifySetup.xdc ========
 *
 */

/*!
 *  ======== NotifySetup ========
 *  Manages setup of the default Notify driver handles
 *
 *  Creates the default notify drivers for each pair of processors.
 */
module NotifySetup inherits ti.sdo.ipc.interfaces.INotifySetup
{
    /*! Possible incoming interrupt IDs for DaVinci/DSP */
    enum DSP_INT {
        DSP_INT0 = 16,
        DSP_INT1 = 17,
        DSP_INT2 = 18,
        DSP_INT3 = 19
    }

    /*! Possible incoming interrupt IDs for DaVinci/ARM */
    enum ARM_INT {
        ARM_INT0 = 46,
        ARM_INT1 = 47
    }

    /*!
     *  Incoming interrupt ID for line #0 line on DSP
     *
     *  See {@link #DSP_INT} for possible values.
     */
    config UInt dspRecvIntId0 = DSP_INT0;

    /*! Vector ID to use on DSP for line #0 */
    config UInt dspIntVectId0 = 5;

    /*!
     *  Incoming interrupt ID for line #0 line on ARM
     *
     *  See {@link #ARM_INT} for possible values.
     */
    config UInt armRecvIntId0 = ARM_INT0;

    /*! Enable the second interrupt line on DaVinci */
    config Bool useSecondLine = false;

    /*!
     *  Incoming interrupt ID for line #1 line on DSP
     *
     *  See {@link #DSP_INT} for possible values.
     */
    config UInt dspRecvIntId1 = DSP_INT1;

    /*! Vector ID to use on DSP for line #1 */
    config UInt dspIntVectId1 = 6;

    /*!
     *  Incoming interrupt ID for line #1 line on ARM
     *
     *  See {@link #ARM_INT} for possible values.
     */
    config UInt armRecvIntId1 = ARM_INT1;

internal:

}
