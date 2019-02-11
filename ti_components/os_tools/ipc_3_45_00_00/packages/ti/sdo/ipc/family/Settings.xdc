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
 *  ======== Settings.xdc ========
 *
 */

/*!
 *  @_nodoc
 *  Family setting module
 */
metaonly module Settings
{
    /*! returns the family specific Interrupt module delegate */
    String getDefaultInterruptDelegate();

    /*! returns the device specific GateSpinLock settings */
    Any getGateHWSpinlockSettings();

    /*! returns the device specific GateHWSem settings */
    Any getGateHWSemSettings();

    /*! returns the module name of the HW Gate that the device supports */
    String getHWGate();

    /*! returns true when the host needs to program the mmu for the slave */
    Bool getIpcSR0Setup();

    /*! returns the MultiProc.id of the HOST if configured in MultiProc */
    UInt16 getHostProcId();

    /*! returns whether the processor is in the build device */
    Bool procInDevice(String procName);

    /*! returns array of names of processors on the build device */
    Any getDeviceProcNames();

    /*! returns the device specific NameServer Remote delegate */
    String getNameServerRemoteDelegate();

    /*! returns the device specific NotifySetup delegate */
    String getNotifySetupDelegate();

    /*! returns the MessageQ transport setup delegate */
    String getMessageQSetupDelegate();

    /*! returns whether to generate slave data for the host */
    Bool generateSlaveDataForHost();
}
