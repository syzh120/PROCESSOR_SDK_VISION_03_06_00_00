/*
 * Copyright (c) 2011-2013, Texas Instruments Incorporated
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
 *  ======== SysMin.xdc ========
 */

/*!
 *  ======== SysMin ========
 *
 *  Minimal implementation of `{@link ISystemSupport}`.
 *
 *  This implementation provides a fully functional implementation of
 *  all methods specified by `ISystemSupport`.
 *
 *  The module maintains an internal buffer (with a configurable size)
 *  that stores on the "output". When full, the data is over-written.  When
 *  `System_flush()` is called the characters in the internal buffer are
 *  "output" using the user configuratble `{@link #outputFxn}`.
 *
 *  As with all `ISystemSupport` modules, this module is the back-end for the
 *  `{@link System}` module; application code does not directly call these
 *  functions.
 */
@Template("./SysMin.xdt")
@ModuleStartup
module SysMin inherits xdc.runtime.ISystemSupport {

    metaonly struct ModuleView {
        Ptr outBuf;
        UInt outBufIndex;
        Bool getTime;   /* set to true for each new trace */
        Bool wrapped;    /* has the buffer wrapped */
    };

    metaonly struct BufferEntryView {
        String entry;
    }

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Module',
                    {
                        type: xdc.rov.ViewInfo.MODULE,
                        viewInitFxn: 'viewInitModule',
                        structName: 'ModuleView'
                    }
                ],
                ['OutputBuffer',
                    {
                        type: xdc.rov.ViewInfo.MODULE_DATA,
                        viewInitFxn: 'viewInitOutputBuffer',
                        structName: 'BufferEntryView'
                    }
                ]
            ]
        });

    /*!
     *  ======== LINEBUFSIZE ========
     *  Size (in MAUs) of the line buffer
     *
     *  An internal line buffer of this size is allocated. All output is stored
     *  in this internal buffer until a new line is output.
     */
    const SizeT LINEBUFSIZE = 0x100;

    /*!
     *  ======== bufSize ========
     *  Size (in MAUs) of the output.
     *
     *  An internal buffer of this size is allocated. All output is stored
     *  in this internal buffer.
     *
     *  If 0 is specified for the size, no buffer is created and ALL
     *  tracing is disabled.
     */
    config SizeT bufSize = 0x1000;

    /*!
     *  ======== sectionName ========
     *  Section where the internal character output buffer is placed
     *
     *  The default is to have no explicit placement; i.e., the linker is
     *  free to place it anywhere in the memory map.
     */
    metaonly config String sectionName = null;

    /*!
     *  ======== flushAtExit ========
     *  Flush the internal buffer during `{@link #exit}` or `{@link #abort}`.
     *
     *  If the application's target is a TI target, the internal buffer is
     *  flushed via the `HOSTwrite` function in the TI C Run Time Support
     *  (RTS) library.
     *
     *  If the application's target is not a TI target, the internal buffer
     *  is flushed to `stdout` via `fwrite(..., stdout)`.
     *
     *  Setting this parameter to `false` reduces the footprint of the
     *  application at the expense of not getting output when the application
     *  ends via a `System_exit()`, `System_abort()`, `exit()` or `abort()`.
     */
    config Bool flushAtExit = true;

    /*!
     *  ======== abort ========
     *  Backend for `{@link System#abort()}`
     *
     *  This abort function writes the string to the internal
     *  output buffer and then gives all internal output to the
     *  `{@link #outputFxn}` function if the `{@link #flushAtExit}`
     *  configuration parameter is true.
     *
     *  @param(str)  message to output just prior to aborting
     *
     *      If non-`NULL`, this string should be output just prior to
     *      terminating.
     *
     *  @see ISystemSupport#abort
     */
    override Void abort(CString str);

    /*!
     *  ======== exit ========
     *  Backend for `{@link System#exit()}`
     *
     *  This exit function gives all internal output to the
     *  `{@link #outputFxn}` function if the `{@link #flushAtExit}`
     *  configuration parameter is true.
     *
     *  @see ISystemSupport#exit
     */
    override Void exit(Int stat);

    /*!
     *  ======== flush ========
     *  Backend for `{@link System#flush()}`
     *
     *  The `flush` writes the contents of the internal character buffer
     *  via the `{@link #outputFxn}` function.
     *
     *  @a(Warning)
     *  The `{@link System}` gate is used for thread safety during the
     *  entire flush operation, so care must be taken when flushing with
     *  this `ISystemSupport` module.  Depending on the nature of the
     *  `System` gate, your application's interrupt latency
     *  may become a function of the `bufSize` parameter!
     *
     *  @see ISystemSupport#flush
     */
    override Void flush();

    /*!
     *  ======== putch ========
     *  Backend for `{@link System#printf()}` and `{@link System#putch()}`
     *
     *  Places the character into an internal buffer. The `{@link #flush}`
     *  sends the internal buffer to the `{@link #outputFxn}` function.
     *  The internal buffer is also sent to the `SysMin_outputFxn`
     *  function by `{@link #exit}` and `{@link #abort}` if the
     *  `{@link #flushAtExit}` configuration parameter is true.
     *
     *  @see ISystemSupport#putch
     */
    override Void putch(Char ch);

    /*!
     *  ======== ready ========
     *  Test if character output can proceed
     *
     *  This function returns true if the internal buffer is non-zero.
     *
     *  @see ISystemSupport#ready
     */
    override Bool ready();

internal:

    struct LineBuffer {
        UInt lineidx;              /* index within linebuf to write next Char */
        Char linebuf[LINEBUFSIZE]; /* local line buffer */
    }

    struct Module_State {
        LineBuffer  lineBuffers[];  /* internal line buffers */
        Char        outbuf[];   /* the output buffer */
        UInt        outidx;     /* index within outbuf to next Char to write */
        Bool        getTime;    /* set to true for each new trace */
        Bool        wrapped;    /* has the index (outidx) wrapped */
        UInt        writeidx[]; /* index to the last "\n" char */
        UInt        readidx[];  /* index to the last char read by external
                                 * observer */
    }
}
