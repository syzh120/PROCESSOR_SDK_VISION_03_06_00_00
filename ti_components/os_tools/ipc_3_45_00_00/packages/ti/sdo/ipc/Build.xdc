/*
 * Copyright (c) 2013-2015 Texas Instruments Incorporated - http://www.ti.com
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
 *  ======== Build.xdc ========
 *  metaonly module to support building various package/product libraries
 *
 */

/*!
 *  ======== Build ========
 */

@Template("./Build.xdt")
metaonly module Build
{
    /*!
     *  ======== LibType ========
     *  IPC library selection options
     *
     *  This enumeration defines all the IPC library types provided
     *  by the product. You can select the library type by setting
     *  the {@link #libType Build.libType} configuration parameter.
     *
     *  @field(LibType_Instrumented) The library supplied is prebuilt
     *  with logging and assertions enabled.
     *
     *  @field(LibType_NonInstrumented) The library supplied is prebuilt
     *  with logging and assertions disabled.
     *
     *  @field(LibType_Custom) This option builds the IPC library from
     *  sources using the options specified by {@link #customCCOpts}.
     *  Only the modules and APIs that your application uses are
     *  contained in the resulting executable. Program optimization is
     *  performed to reduce the size of the executable and improve
     *  performance. Enough debug information is retained to allow you
     *  to step through the application code in CCS and locate global
     *  variables.
     *
     *  @field(LibType_Debug) This option is similar to the LibType_Custom
     *  option in that it builds the IPC library from sources and omits
     *  modules and APIs that your code does not use. However, no program
     *  optimization is performed. The resulting executable is fully
     *  debuggable, and you can step into IPC code. The tradeoff is that
     *  the executable is larger and runs slower than builds that use the
     *  LibType_Custom option.
     *
     *  @field(LibType_PkgLib) This option uses the individual libraries
     *  built by each package of the IPC product. These libraries are
     *  not shipped. You must build the product to generate the package
     *  libraries. See the IPC Install Guides (links in the Release
     *  Note) for details on building the IPC product.
     *
     *  @see #libType
     */
    enum LibType {
        LibType_Instrumented,           /*! Instrumented */
        LibType_NonInstrumented,        /*! Non-instrumented */
        LibType_Custom,                 /*! Custom (Optimized) */
        LibType_Debug,                  /*! Custom (Debug) */
        LibType_PkgLib                  /*! Use package library */
    };

    /*!
     *  ======== libType ========
     *  IPC library type
     *
     *  The IPC runtime is provided in the form of a library that is
     *  linked with your application. Several forms of this library are
     *  provided with the IPC product. In addition, there is an option
     *  to build the library from source. This configuration parameter
     *  allows you to select the form of the IPC library to use.
     *
     *  The default value of libType is taken from the BIOS.libType
     *  configuration parameter. For a complete list of options and
     *  what they offer see {@link #LibType}.
     */
    config LibType libType;

    /*!
     *  ======== customCCOpts ========
     *  Compiler options used when building a custom IPC library
     *
     *  When {@link #libType Build.libType} is set to
     *  {@link #LibType_Custom Build_LibType_Custom} or
     *  {@link #LibType_Debug Build_LibType_Debug}, this string contains
     *  the options passed to the compiler during any re-build of the
     *  IPC sources.
     *
     *  In addition to the options specified by `Build.customCCOpts`,
     *  several `-D` and `-I` options are also passed to the compiler.
     *  The options specified by `Build.customCCOpts` preceed the `-D`
     *  and `-I` options passed to the compiler on the command line.
     *
     *  To view the custom compiler options, add the following line
     *  to your config script:
     *
     *  @p(code)
     *  print("Build.customCCOpts="+Build.customCCOpts);
     *  @p
     *
     *  When {@link #libType Build.libType} is set to
     *  {@link #LibType_Custom Build_LibType_Custom}, `Build.customCCOpts`
     *  is initialized to create a highly optimized library.
     *
     *  When {@link #libType Build.libType} is set to
     *  {@link #LibType_Debug Build_LibType_Debug}, `Build.customCCOpts`
     *  is initialized to create a non-optimized library that can be
     *  used to single-step through the APIs with the CCS debugger.
     *
     *  @a(Warning)
     *  The default value of `Build.customCCOpts`, which is derived from
     *  the target specified by your configuration, includes runtime
     *  model options (such as endianess) that must be the same for all
     *  sources built and linked into your application. You must not
     *  change or add any options that can alter the runtime model
     *  specified by the default value of `Build.customCCOpts`.
     */
    config String customCCOpts;

    /*!
     *  ======== assertsEnabled ========
     *  IPC assert checking in custom library enable flag
     *
     *  When set to true, assert checking code is compiled into
     *  the custom library created when {@link #libType Build.libType}
     *  is set to {@link #LibType_Custom Build_LibType_Custom} or
     *  {@link #LibType_Debug Build_LibType_Debug}.
     *
     *  When set to false, assert checking code is removed from the
     *  custom library created when Build.libType is set to
     *  Build.LibType_Custom or Build.LibType_Debug. This option can
     *  considerably improve runtime performance as well significantly
     *  reduce the application's code size.
     *
     *  @see #libType
     */
    config Bool assertsEnabled = true;

    /*!
     *  ======== logsEnabled ========
     *  IPC log support in custom library enable flag
     *
     *  When set to true, IPC execution log code is compiled into
     *  the custom library created when {@link #libType Build.libType}
     *  is set to {@link #LibType_Custom Build_LibType_Custom} or
     *  {@link #LibType_Debug Build_LibType_Debug}.
     *
     *  When set to false, all log code is removed from the custom
     *  library created when Build.libType = Build.LibType_Custom or
     *  Build.LibType_Debug. This option can considerably improve runtime
     *  performance as well signficantly reduce the application's code
     *  size.
     *
     *  @see #libType
     */
    config Bool logsEnabled = true;

    /*!
     *  ======== libDir ========
     */
    config String libDir = null;

    /*
     *  ======== getCCOpts ========
     *  Get the compiler options necessary to build
     */
    metaonly String getCCOpts(xdc.bld.ITarget.Module target);

    /*!
     *  ======== getDefaultCustomCCOpts ========
     */
    String getDefaultCustomCCOpts();

    /*!
     *  ======== getDefs ========
     *  Get the compiler -D options necessary to build
     */
    String getDefs();

    /*!
     *  ======== getCFiles ========
     *  Get the library C source files.
     */
    String getCFiles(String target);

    /*!
     *  ======== getAsmFiles ========
     *  Get the library Asm source files.
     */
    Any getAsmFiles(String target);

    /*
     *  ======== buildLibs ========
     *  This function generates the makefile goals for the libraries
     *  produced by a ti.sysbios package.
     */
    function buildLibs(objList, relList, filter, xdcArgs);

    /*!
     *  ======== getLibs ========
     *  Common getLibs() for all ipc packages.
     */
    function getLibs(pkg);
}
