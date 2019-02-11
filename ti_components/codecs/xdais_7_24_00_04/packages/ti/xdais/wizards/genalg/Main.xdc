/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
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
/*!
 * ======== Main ========
 * XDM GenAlg wizard
 *
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        '[-g] [--cgtools <dir>] [--gcccgtools <dir>] [--m3cgtools <dir>] [-f <file> | --xml <file>] [-d <destination dir>]'
    ];

instance:

    /*! Gui */
    @CommandOption("g")
    config Bool gui = false;

    /*! TI C6000 codegen tools directory */
    @CommandOption('cgtools')
    config String cgTools = null;

    /*! GCC codegen tools directory */
    @CommandOption('gcccgtools')
    config String gccCgTools = null;

    /*! m3 codegen tools directory */
    @CommandOption('m3cgtools')
    config String m3cgTools = null;

    //! XML File containing saved user input
    @CommandOption("f,xml")
    config String xmlFile = null;

    /*! package destination directory */
    @CommandOption('d')
    config String destDir = null;

}

