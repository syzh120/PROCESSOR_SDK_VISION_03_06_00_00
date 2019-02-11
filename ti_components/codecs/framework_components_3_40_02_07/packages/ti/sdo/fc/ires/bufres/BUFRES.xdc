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
 *
 */
/*!
 *  ======== BUFRES ========
 *  Bufres IRES Resman and Protocol Implementation
 */
@Template("./BUFRES.xdt")

metaonly module BUFRES {

    /*!
     *  ======== persistentAllocFxn ========
     *  Function for allocating persistent memory for BUFRES's internal objects.
     */
    config String persistentAllocFxn = "DSKT2_allocPersistent";

    /*!
     *  ======== persistentFreeFxn ========
     *  Function for freeing persistent memory used by BUFRES implementation's
     *  internal objects.
     *
     *  This is not required to be set.
     */
    config String persistentFreeFxn = "DSKT2_freePersistent";

    /*!
     *  ======== bufBase ========
     *  Base address of the buffer resource.
     */
    config Ptr bufBase = null;

    /*!
     *  ======== bufLength ========
     *  The length of the buffer resource.
     */
    config UInt bufLength = 0;


    /*  @_nodoc */
    override config Bool autoRegister = false;

    config Bool enableLog;
}
