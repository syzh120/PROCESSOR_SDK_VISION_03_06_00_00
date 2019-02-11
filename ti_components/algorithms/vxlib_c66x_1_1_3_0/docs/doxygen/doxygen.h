/* ======================================================================== *
 * VXLIB -- TI Vision Library                                               *
 *                                                                          *
 *   Doxygen generation header file                                         *
 *                                                                          *
 * Copyright (C) 2016- 2017 Texas Instruments Incorporated                  *
 *                          http://www.ti.com/                              *
 *                                                                          *
 *                                                                          *
 *  Redistribution and use in source and binary forms, with or without      *
 *  modification, are permitted provided that the following conditions      *
 *  are met:                                                                *
 *                                                                          *
 *    Redistributions of source code must retain the above copyright        *
 *    notice, this list of conditions and the following disclaimer.         *
 *                                                                          *
 *    Redistributions in binary form must reproduce the above copyright     *
 *    notice, this list of conditions and the following disclaimer in the   *
 *    documentation and/or other materials provided with the                *
 *    distribution.                                                         *
 *                                                                          *
 *    Neither the name of Texas Instruments Incorporated nor the names of   *
 *    its contributors may be used to endorse or promote products derived   *
 *    from this software without specific prior written permission.         *
 *                                                                          *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 * ======================================================================== */

/**
 * @mainpage  @PACKAGE User's Manual (@TARGETN)
 *
 *  @HLINE
 *
 *  <div>
 *    <p>&nbsp;</p>
 *    @section start Getting Started
 *    <table @TSTYLE>
 *      <tr>
 *        <td><a @ASTYLE href="intro.html">Introduction</a></td>
 *        <td>@PACKAGE features and advantages</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE href="install.html">Package Contents</a></td>
 *        <td>What the installation provides and where</td>
 *      </tr>
 * @if src
 *      <tr>
 *        <td><a @ASTYLE href="building.html">Building</a></td>
 *        <td>How to build @PACKAGE using CCS Projects or GNU make</td>
 *      </tr>
 * @endif
 *      <tr>
 *        <td><a @ASTYLE href="integrate.html">Integration</a></td>
 *        <td>How to integrate @PACKAGE into your code</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE href="examples.html">Examples</a></td>
 *        <td>Example projects provided with @PACKAGE </td>
 *      </tr>
 *      <tr>
 *        <td @CSTYLE><a @ASTYLE target="_blank" href="@PKGMANLINK">API Reference</a></td>
 *        <td>Detailed usage for all @PACKAGE kernels</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE href="bamplugins.html">BAM Plugin Support</a></td>
 *        <td>List of kernels which have BAM plugins supported</td>
 *      </tr>
 *    </table>
 *  </div>
 *
 *
 *  <div>
 *    <p>&nbsp;</p>
 *    @section dox Additional Documents
 *    <table @TSTYLE>
 *      <tr>
 *        <td @CSTYLE><a @ASTYLE @BLANK href="../../../@PKGRELNOTES">Release Notes</a></td>
 *        <td>New features, device support, known issues, etc.</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE @BLANK href="../../@PKGSWMFEST">Software Manifest</a></td>
 *        <td>Link to manifests for all packages in delivery</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE @BLANK href="../../@PKGTESTREP">Cycle Benchmarks</a></td>
 *        <td>Cycle and memory benchmarking</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE @BLANK href="../../@PKGCOMPREP">Standard Compliance</a></td>
 *        <td>MISRA-C Compliance</td>
 *      </tr>
 *    </table>
 *  </div>
 *
 *
 *  <div>
 *    <p>&nbsp;</p>
 *    @section linx Helpful Links
 *    <table @TSTYLE>
 *      <tr>
 *        <td @CSTYLE><a @ASTYLE @BLANK href="https://www-a.ti.com/downloads/sds_support/TICodegenerationTools/download.htm">Code Gen Tools</a></td>
 *        <td>Download site for TI DSP code generation tools</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE @BLANK href="http://processors.wiki.ti.com/index.php/Download_CCS">Code Composer Studio</a></td>
 *        <td>Download site for Code Composer Studio IDE</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE @BLANK href="https://e2e.ti.com/support/arm/automotive_processors/f/1021">TI E2E Support Forum</a></td>
 *        <td>Forum for @PACKAGE questions or remarks</td>
 *      </tr>
 *      <tr>
 *        <td><a @ASTYLE @BLANK href="http://processors.wiki.ti.com/index.php/Software_libraries">Library Wiki</a></td>
 *        <td>Find and download the latest @PACKAGE release</td>
 *      </tr>
 *    </table>
 *  </div>
 *
 *  @SPACER
 */


/**
 * @page intro  Introduction
 *
 * <a @NSTYLE href="index.html">Back</a>
 *
 * @SPACER
 *
 * The Texas Instruments @PACKAGE is an optimized Vision Processing
 * Functions Library for C programmers using @TARGETX devices.
 * It includes many C-callable, assembly-optimized, general-purpose vision
 * processing routines. These routines are typically used in computationally
 * intensive real-time applications where optimal execution speed is critical.
 *
 * Using these routines assures execution speeds considerably faster than
 * equivalent code written in standard ANSI C language. In addition, by
 * providing ready-to-use DSP functions, TI @PACKAGE can significantly shorten
 * vision processing application development time.
 *
 * @SPACER
 *
 * @section features  Features and Benefits
 *  @SECSTART
 *  The TI @TARGETN @PACKAGE is a software library of more than 100 royalty-free kernels
 *  from Texas Instruments that accelerates common vision processing operations. @PACKAGE 
 *  is an extensible library that is optimized for the C66 DSP core and is available 
 *  royalty-free.  This collection of 100+ kernels provide the ability to perform:
 *
 *  - Image filtering
 *  - Statistics extraction
 *  - Feature Detection
 *  - Tracking & Recognition
 *  - Low-level Pixel Processing
 *
 *   VXLIB provides an extensible foundation for the following applications:
 *
 *  - Video Analytics
 *  - Video Surveillance
 *  - Automotive Vision
 *  - Embedded Vision
 *  - Game Vision
 *  - Machine Vision
 *  - Consumer Electronics
 *  - Augmented Reality
 *  @SECEND
 *
 *
 */


/**
 * @page install  Package Contents
 *
 * <a @NSTYLE href="index.html">Back</a>
 *
 * @SPACER
 *
 *  Unless otherwise specified, the @PACKAGE package installs under
 *  <tt>C:\\ti\\</tt> in directory <tt> @PKGDIR</tt>.
 *  The files that comprise the @PACKAGE installation can be categorized into the
 *  following categories.
 *
 *    -# Documentation
 *    -# Component Repository
 *    -# Kernel Directories
 *    -# Library Directory
 *    -# Eclipse Support
 *    -# Internal Meta Data
 *
 *  The sections that follow provide details for each category.
 *
 * @SPACER
 *
 * @section documents Documentation
 *  @SECSTART
 *  Installation places all @PACKAGE documentation in a @c @b Docs directory in the
 *  @PACKAGE root.  The following documentation comes with the delivery:
 *
 *  - @PKGMANHTML (this document)
 *  - <a @BLANK href="../../../@PKGRELNOTES">Release Notes</a>
 *  - <a @BLANK href="../../@PKGSWMFEST">Software Manifest</a></td>
 *  - <a @BLANK href="../../@PKGTESTREP">Cycle Benchmarks</a>
 *  @SECEND
 *
 * @section repository  Component Repository
 *  @SECSTART
 *  The installation creates a @c @b Components directory in the @PACKAGE root
 *  folder.  This directory serves as a repository for all packages included
 *  in the @PACKAGE installation.  Each package in this repository is compressed.
 *  @SECEND
 *
 * @section kerneldir  Kernel Directories
 *  @SECSTART
 *  The installation also creates a @c @b Packages directory in the @PACKAGE root
 *  folder.  This directory holds all kernels contained within the @PACKAGE
 *  library.  This directory follows the standard TI directory structure.  As an
 *  example, the files that comprise the @PACKAGE kernel @c @b @KERNELEX will be
 *  located, relative to the @PACKAGE root installation directory, at
 *  <tt>packages/ti/@package/src/vx/@KERNELEX/</tt>.
 *
 *  Each Kernel is delivered with a pre-compiled CCS project that illustrates
 *  the kernel API and performs several validation tests.  Each project provides
 *  an estimate of kernel cycle and program memory requirements.
 *
 *  Some selected kernels also contain a bam_plugin folder which contains the 
 *  files necessary to plugin the respective kernel into the BAM block based processing
 *  framework.
 *
 *  Follow @ref ccs_compile_knl for building & testing kernel projects.
 *  @SECEND
 *
 * @section libdir  Library Directory
 *  @SECSTART
 *  The installation also creates a @c @b lib directory in the <tt>packages/ti/@package</tt>
 *  folder.  This directory holds:
 *   - @c @b vxlib.lib : Main optimized @package library
 *   - @c @b vxlib_cn.lib : C Natural Implementation of @package library
 *   - @c @b vxlib_bamplugin.lib : Library of bam plugin interfaces to the VXLIB functions.
 *   - @c @b common.lib : Common functions required for testing kernels.
 * @if src 
 *   - @c @b vxlib.a86 : Host(x86) Intrinsic library
 *   - @c @b vxlib_cn.a86 : C Natural Host(x86) library
 *   - @c @b vxlib_bamplugin.a86 : Host(x86) Library of bam plugin interfaces to the VXLIB functions.
 *   - @c @b common.a86 : Common functions Host(x86) library.
 *
 *   - @c @b vxlib.a86_64W : Host(x86_64) Intrinsic library
 *   - @c @b vxlib_cn.a86_64W : C Natural Host(x86_64) library
 *   - @c @b vxlib_bamplugin.a86_64W : Host(x86_64) Library of bam plugin interfaces to the VXLIB functions.
 *   - @c @b common.a86_64W : Common functions Host(x86_64) library.
 * @endif
 *  The *.lib files are actually "library information archives" (build from using libinfo6x command)
 *  which internally point to the *.ae66 library files.  This is done so that you can always link using 
 *  the *.lib files even if we add new variants of libraries with different extensions to the package. You
 *  can read more about Library Information Archiver tool in <a @ASTYLE @BLANK href="http://www.ti.com/lit/pdf/spru186">spru186</a>
 *
 * @section eclipsedir  Eclipse Support
 *  @SECSTART
 *  The @c @b Eclipse directory contains all files required for @PACKAGE to be
 *  recognized by Eclipse (CCS) as a plug-in.  This is a support directory and
 *  can be safely ignored.
 *  @SECEND
 *
 * @section metadata  Internal Meta Data
 *  @SECSTART
 *  The @PACKAGE installation creates a @c @b Package directory.  This directory
 *  contains meta information required by the TI packaging tools.  This is a
 *  support directory and can be safely ignored.
 *  @SECEND
 *
 */


/**
 * @page examples  Examples
 *
 * <a @NSTYLE href="index.html">Back</a>
 *
 * @SPACER
 *
 * @section kernelexamples  Stand-alone kernel examples/tests
 *  @SECSTART
 *  Each kernel directory has a stand-alone CCS project that can be compiled and run 
 *  on a bare-metal DSP (no OS or drivers).  The main test file is the *_d.c file.
 *  This file follows a common format for each kernel:
 *  - Load all the test vectors from the *_idat.c file of the same directory.
 *  - For each test case:
 *    - Allocate memory for each buffer based on the parameters specified from the test vector
 *    - Initialize buffers with data as specified from the test vector (random, static, etc.)
 *    - Initialize function parameters
 *    - Call the optimized version of the kernel from the c66 folder of the same directory
 *    - Call the natural c version of the kernel from the *_cn.c file of the same directory
 *    - Compare the results of these two versions to make sure they match
 *    - Optionally compare the results against a static expected output_iterator
 *    - Print test results, including performance
 *    - Free buffers
 *  - When all the test vectors are completed, print summary of performance and memory usage.
 *  @SECEND
 *
 * @section regressionexample  Full regression test
 *  @SECSTART
 *  The examples folder contains 
 *    - Regression CCS Project (Calls each of the kernel tests one after the other in a single executable)
 * @if src
 *    - Regression Host(x86 or x86_64) makefile project
 * @endif
 *  @SECEND
 *
 */


/**
 * @page integrate  Integration
 *
 * <a @NSTYLE href="index.html">Back</a>
 *
 * @SPACER
 *
 *  Since @PACKAGE is a collection of individual kernels, any combination of the
 *  kernels that comprise @PACKAGE may be integrated into a system individually.
 *  Integration, for single or multiple kernels, requires simple steps below:
 *
 *    -# @ref compile 
 *    -# @ref kernelcalls
 *    -# @ref syscompile
 *    -# @ref linking
 *
 *  The sections that follow provide details regarding the above steps.
 *
 * @SPACER
 *
 *  @if src
 *  @section compile  Compile @PACKAGE 
 *  @SECSTART
 *  On installation, the @PACKAGE libraries are built and ready to link.  Therefore,
 *  this step is only required when the original kernel source code has been refined
 *  or contributions have been added.  In the case of Building for PC target (x86 or x86l) executions,
 *  it may also be required to rebuild the source against the compiler version you are
 *  using in the larger executable.  See @ref building for details regarding building @PACKAGE.
 *  @SECEND
 *  @endif  
 *
 *  @section kernelcalls  Add @PACKAGE API Calls
 *  @SECSTART
 *  Add calls to @PACKAGE kernels within the system source code as necessary.
 *  Any system source file that contains calls to an @PACKAGE kernel will require
 *  that the @PACKAGE header file <tt> @PKGHEADER </tt> is included.  See the
 *  <a href="@PKGMANLINK">@PACKAGE Function Reference</a> for details on individual
 *  kernel APIs.
 *  @SECEND
 *
 *  @section syscompile  System Compilation
 *  @SECSTART
 *  @par Include Paths
 *  To compile the system code with VXLIB integrated, the following two paths should be added to the
 *  compiler's include path search list:
 *  - The path to <tt> @PKGHEADER </tt>: <tt>\<@PACKAGE root\>\\packages\\ti\\vxlib</tt> directory
 *  - The path to the <tt>\<@PACKAGE root\>\\packages</tt> directory.
 *
 *  These paths will depend on the @PACKAGE root installation directory.  This allows the main
 *  @PACKAGE header file to be moved from within the installation directory and
 *  still recognize the individual kernel headers.
 *  @par Preprocessor Defines
 *  (Optional) When compiling the final executable as a PC target (x86 or x86l), the
 *  following preprocessor definitions should be added to the compiler's preprocessor defines
 *  list:
 *  - _HOST_BUILD
 *  - _TMS320C6600
 *  - TMS320C66X
 *  - CORE_DSP
 *  - HOST_EMULATION
 *  @SECEND
 *
 *  @section linking  Linking @PACKAGE
 *  @SECSTART
 *  The path to the @PACKAGE required libraries must be provided to the linker.
 *  @note When compiling for PC target (x86 or x86l), the common library also needs to be linked along with the vxlib library due to dependencies on emulated intrinsic that are
 *  part of the common library.
 *  @SECEND
 *
 */


/**
 * @if src
 * @page building  @PACKAGE Build Process
 *
 * <a @NSTYLE href="index.html">Back</a>
 *
 * @SPACER
 *
 *  @PACKAGE is provided with two methods for compilation/link (build).  For those
 *  familiar with TI's Code Composer Studio (Eclipse-based) IDE, we provide projects
 *  for each kernel to get up and running with relative ease.  Likewise, many
 *  developers are more comfortable with the GNU Make utility.  As such, we also
 *  provide Makefiles to build the @PACKAGE library.
 *
 *  This table compares the out-of-box build support for CCS vs GNU Makefile.
 *
 *	- <b>Build libraries</b> : build vxlib, vxlib_cn, vxlib_bamplugin, and common libraries.
 *	- <b>Build Individual Kernel Examples</b> : Separate executable for each kernel.
 *	- <b>Build Full Kernel Regression</b> : Single executable which includes all kernel examples run back to back.
 *
 *  <table>
 *    <tr bgcolor="darkgrey">
 *      <th> Feature </th>
 *      <th> CCS </th>
 *      <th> Makefile </th>
 *    </tr>
 *    <tr bgcolor="lightgrey">
 *      <th align="left"> C66 DSP Binaries (Building on Windows or Linux) </th>
 *      <th>  </th>
 *      <th>  </th>
 *    </tr>
 *    <tr>
 *      <td> Build Libraries </td>
 *      <td align="center"> YES </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> Build Individual Kernel Examples </td>
 *      <td align="center"> YES </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> Build Full Kernel Regression </td>
 *      <td align="center"> YES </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr bgcolor="lightgrey">
 *      <th align="left"> X86 Windows Binaries (Building on Windows) </th>
 *      <th>  </th>
 *      <th>  </th>
 *    </tr>
 *    <tr>
 *      <td> Build Libraries </td>
 *      <td align="center">  </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> Build Individual Kernel Examples </td>
 *      <td align="center">  </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> Build Full Kernel Regression </td>
 *      <td align="center">  </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr bgcolor="lightgrey">
 *      <th align="left"> X86 Linux Binaries (Building on Linux) </th>
 *      <th>  </th>
 *      <th>  </th>
 *    </tr>
 *    <tr>
 *      <td> Build Libraries </td>
 *      <td align="center">  </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> Build Individual Kernel Examples </td>
 *      <td align="center">  </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> Build Full Kernel Regression </td>
 *      <td align="center">  </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *  </table>
 *
 * @SPACER
 *
 * @section ccs_howto  Code Composer Studio
 *  @SECSTART
 *  This release of @PACKAGE provides Code Composer Studio (CCS) projects
 *  to build and test each DSP kernel within.  Each project is provided within the
 *  specific kernel directory.  Once loaded, each project provides the ability
 *  to build and test the code.
 *
 *  There is also a CCS project to build and test the full DSP kernel regression, as well
 *  as a project which simiply calls the GNU Makefile for building the DSP libraries
 *  from within CCS.
 *
 *  Follow the instructions at @ref ccs_build for more details.
 *  @SECEND
 *
 * @section gnu_howto  GNU Makefile
 *  @SECSTART
 *  A GNU @b makefile is provided for rebuilding @PACKAGE libraries via the GNU make utility.
 *  This file is located in the @b packages/ti/@package folder. The makefile provides
 *  a list of all tools, common build utilities and build rules required for generating
 *  @PACKAGE libraries.
 *
 *  There is also a second makefile for rebuilding the full kernel regression executable.
 *  This file is located in the @b examples folder. The makefile provides
 *  a list of all tools, common build utilities and build rules required for generating
 *  @PACKAGE regression executable.
 *
 *  Follow the instructions at @ref gnu_build for more details.
 *  @SECEND
 * @endif 
 */

/**
 * @if src
 * @page ccs_build  CCS Build Process
 *
 * <a @NSTYLE href="building.html">Back</a>
 *
 * @SPACER
 *
 *  To build any specific kernel for test, benchmarking or to pull in source code changes -
 *  just locate the associated project file, load it and run within the CCS environment.
 *  The sections below provide all necessary details to get started.
 *
 *    -# @ref ccs_projects
 *    -# @ref ccs_tools
 *    -# @ref ccs_compile_lib
 *    -# @ref ccs_compile_test
 *    -# @ref ccs_compile_regression
 *
 * @SPACER
 *
 * @section ccs_projects  Available CCS Projects
 *  @SECSTART
 *  @PACKAGE provides three types of CCS projects which build for C66 DSP:
 *  -# <b>Library Makefile Project (VXLIB_LIB_GEN)</b>: Located in @b <tt>packages/ti/@package/lib</tt> folder.  This makefile project builds
 *     vxlib, vxlib_cn, vlib_bamplugin, and common libraries by default (uses (g)make <b>.libraries,e66</b> command).  This default can be changed 
 *     in the Properties->Build window of the project.  The follwoing build targets are alternative options to the default.
 *    - <b>all,e66</b> : All C66 DSP libraries (same as .libraries,e66 since this makefile only creates libraries)
 *      - @b lib/vxlib.ae66 : C66 DSP vxlib optimized library
 *      - @b lib/vxlib_cn.ae66 : C66 DSP vxlib natural c library
 *      - @b lib/vxlib_bamplugin.ae66 : C66 DSP vxlib bamplugin library (depends on ALGFRAMEWORK and DMAUTILS packages)
 *      - @b lib/common.ae66 : C66 DSP common test utilities library
 *    - @b clean : All libraries
 *  -# <b>Kernel Test Projects (VXLIB_<kernel name>_66_LE_ELF)</b>: Located in each kernel <b><tt>packages/ti/vxlib/src/vx/\<kernel\></tt></b> folder.
 *     These projects build the test code for the kernel, and is dependent on (links against)
 *     vxlib, vxlib_cn, and common libraries from the <b>Library Makefile Project</b>
 *  -# <b>Kernel Regression Project (RegressionTest_66_LE_ELF)</b>: Located in @b <tt>examples/Regression</tt> folder.  This project builds the full kernel regression executable.  It is dependent
 *     on (links against) vxlib, vxlib_cn, and common libraries from <b>Library Makefile Project</b>.  It also build a library of each kernel's test functions
 *     (*_idat.c, *_d.c), and then build the main.c and link it all together for the executable.
 * 
 *  @SECEND
 *
 * @section ccs_tools  Required Tools
 *  @SECSTART
 *  The following tools are required to build @PACKAGE using CCS (links provided).
 *  Download and install all tools to a single local (@c @b C:) directory,
 *  for example, <tt><b>c:\\ti</b></tt>.
 *
 *  - <a target=_blank href="https://www-a.ti.com/downloads/sds_support/TICodegenerationTools/download.htm">Code Generation Tools Version 7.4.2</a>
 *  - <a target=_blank href="http://processors.wiki.ti.com/index.php?title=Category:Code_Composer_Studio_v5">CCS Versions 5.4 or higher</a>
 *
 *  @note  A "My.TI" account is required for download and can be registered at <a target=_blank href="http://my.ti.com">my.ti.com</a>
 *  @SECEND
 *
 * @section ccs_compile_lib  @PACKAGE Libraries Build Procedure
 *  @SECSTART
 *  The @PACKAGE libraries (vxlib, vxlib_cn, vxlib_bamplugin, & common) may be compiled with CCS following the procedure below.
 *
 *   -# Open CCS Version 5.4 or later
 *   -# Import the @PACKAGE @b makefile based project
 *     - Open the @b Project menu
 *     - Select <b>Import Existing Eclipse Project</b>
 *     - Import VXLIB_LIB_GEN project from the @PACKAGE @b <tt>/packages/ti/@package/lib</tt> directory
 *   -# Make modifications to the project (optional)
 *     - By default, the @b release build configuration is enabled, and the <b>all,e66</b> target is chosen.
 *     - To change the build configuration or target of makefile:
 *       - Select <b>Properties</b> from @b Project menu
 *       - Select @b Build on the left panel
 *         - To change build configuration to @b debug, click on the @b Variables tab and add a new variable: <b>DEBUG = yes</b>
 *         - To change the target of the makefile, click on the @b Behaviour tab and modify the target in the <b>Make build target</b> fields
 *           to match one of the makefile targets in @ref ccs_projects.
 *     - After making change, close the window by clicking @b OK
 *   -# Build the project
 *     - Select <b>Rebuild Active Project</b> from @b Project menu
 *     - @note This procedure uses a makefile project using the same makefile mentioned at @ref gnu_makefiles.  It therefore uses the settings
 *       from this makefile instead of the CCS project settings.
 *
 *  @SECEND
 * @endif
 *
 * @section ccs_compile_test  @PACKAGE Individual Kernel Test Build Procedure
 *  @SECSTART
 *  Any individual kernel within @PACKAGE may be compiled and tested via CCS following
 *  the procedure below:
 *
 *   -# Open CCS
 *   -# Import the @PACKAGE kernel project
 *     - Open the @b Project menu
 *     - Select <b>Import Existing Eclipse Project</b>
 *     - Import from the @PACKAGE @b <tt>/packages/ti/@package/src/vx/\<kernel\></tt> directory
 *   -# Use the @b Debug/Release profile for debugging/modifing/optimizing kernels
 *     - Open the @b Project menu
 *     - Select <b>Active Build Configuration</b> and set to @b Debug/Release
 *   -# Build and test the project
 *     - Select <b>Rebuild Active Project</b> from @b Project menu
 *     - Test using the proper target configuration
 *
 *  @SECEND
 * @endif
 *
 * @section ccs_compile_regression  @PACKAGE Full Kernel Test Regression Build Procedure
 *  @SECSTART
 *  The @PACKAGE full kernel test regression may be compiled with CCS following the procedure below.
 *
 *   -# Open CCS
 *   -# Import the @PACKAGE test regression project
 *     - Open the @b Project menu
 *     - Select <b>Import Existing Eclipse Project</b>
 *     - Import from the @PACKAGE @b <tt>/examples/Regression</tt> directory
 *   -# Use the @b Debug/Release profile for debugging/modifing/optimizing kernels
 *     - Open the @b Project menu
 *     - Select <b>Active Build Configuration</b> and set to @b Debug/Release
 *   -# Build and test the project
 *     - Select <b>Rebuild Active Project</b> from @b Project menu
 *     - Test using the proper target configuration
 *
 *  @SECEND
 * @endif
 */
 
 /**
 * @page ccs_compile_knl Individual Kernel Build Procedure
 * 
 * <a @NSTYLE href="install.html">Back</a>
 *
 * @SPACER
 *  Any individual kernel within @PACKAGE may be compiled and tested via CCS following
 *  the procedure below:
 *
 *   -# Open CCS
 *   -# Import the @PACKAGE kernel project
 *     - Open the @b Project menu
 *     - Select <b>Import Existing Eclipse Project</b>
 *     - Import from the @PACKAGE @b <tt>/packages/ti/@package/src/vx/\<kernel\></tt> directory
 *   -# Use the @b Debug/Release profile for debugging/modifing/optimizing kernels
 *     - Open the @b Project menu
 *     - Select <b>Active Build Configuration</b> and set to @b Debug/Release
 *   -# Build and test the project
 *     - Select <b>Rebuild Active Project</b> from @b Project menu
 *     - Test using the proper target configuration
 *
 * @SPACER
 */


/**
 * @if src
 * @page gnu_build  GNU Make Build Process
 *
 * <a @NSTYLE href="building.html">Back</a>
 *
 * @SPACER
 *
 *  The sections below provide all necessary details to get started.
 *
 *    -# @ref gnu_makefiles
 *    -# @ref gnu_tools
 *    -# @ref gnu_compile_windows
 *    -# @ref gnu_compile_Linux
 *
 * @SPACER
 *
 * @section gnu_makefiles  Available Makefiles
 *  @SECSTART
 *  @PACKAGE provides two GNU makefiles which build for C66 DSP, Windows Visual Studio, or Linux GCC targets.  Each one lists the hierarchy
 *  of make targets that can be chosen on the command line during the build procedures below.  This may be useful if you want to 
 *  save time only building what you need, or if your configuration doesn't support all targets.
 *  -# <b>Library makefile</b>: Located in @b <tt>packages/ti/@package</tt> folder.  This makefile builds
 *     vxlib, vxlib_cn, vlib_bamplugin, and common libraries.
 *    - @b all : All libraries
 *      - <b>all,e66</b> : All C66 DSP libraries
 *        - @b lib/vxlib.ae66 : C66 DSP vxlib optimized library
 *        - @b lib/vxlib_cn.ae66 : C66 DSP vxlib natural c library
 *        - @b lib/vxlib_bamplugin.ae66 : C66 DSP vxlib @ref bamplugins library (depends on ALGFRAMEWORK and DMAUTILS packages)
 *        - @b lib/common.ae66 : C66 DSP common test utilities library
 *      - <b>all,a86</b> : All 32-bit Windows Visual Studio libraries
 *        - @b lib/vxlib.a86 : 32-bit Windows Visual Studio vxlib library
 *        - @b lib/vxlib_cn.a86 : 32-bit Windows Visual Studio  vxlib natural c library
 *        - @b lib/vxlib_bamplugin.a86 : 32-bit Windows Visual Studio  vxlib @ref bamplugins library (depends on ALGFRAMEWORK and DMAUTILS packages)
 *        - @b lib/common.a86 : 32-bit Windows Visual Studio  common test utilities library
 *      - <b>all,a86l</b> : All 32-bit Linux GCC libraries
 *        - @b lib/vxlib.a86l : 32-bit Linux GCC vxlib library
 *        - @b lib/vxlib_cn.a86l : 32-bit Linux GCC vxlib natural c library
 *        - @b lib/vxlib_bamplugin.a86l : 32-bit Linux GCC vxlib @ref bamplugins library (depends on ALGFRAMEWORK and DMAUTILS packages)
 *        - @b lib/common.a86l : 32-bit Linux GCC common test utilities library
 *      - <b>all,a86_64W</b> : All 64-bit Windows Visual Studio libraries
 *        - @b lib/vxlib.a86_64W : 64-bit Windows Visual Studio common test utilities library
 *        - @b lib/vxlib_cn.a86_64W : 64-bit Windows Visual Studio vxlib natural c library
 *        - @b lib/vxlib_bamplugin.a86_64W : 64-bit Windows Visual Studio vxlib @ref bamplugins library (depends on ALGFRAMEWORK and DMAUTILS packages)
 *        - @b lib/common.a86_64W : 64-bit Windows Visual Studio common test utilities library
 *    - @b clean : All libraries
 *  -# <b>Kernel Regression makefile</b>: Located in @c @b examples folder.  This makefile builds
 *     the full kernel regression executable.  It is dependent on vxlib, vxlib_cn, and common libraries from other makefile, so if they are not built,
 *     this makefile will invoke the appropriate targets from the library makefile first.  It will then build a library of each kernel's test functions
 *     (*_idat.c, *_d.c), and then build the main.c and link it all together for the executable.
 *    - @b all : All kernel regression targets
 *      - <b>all,e66</b> : C66 DSP kernel regression 
 *      - <b>all,a86</b> : 32-bit Windows Visual Studio kernel regression
 *      - <b>all,a86l</b> : 32-bit Linux GCC kernel regression
 *      - <b>all,a86_64W</b> : 64-bit Windows Visual Studio kernel regression
 *    - @b clean : All kernel regression targets
 * 
 *  Both makefiles provide a list of all tools, common build utilities and build rules required.  
 *
 *  The sections that follow apply to both of these makefiles.
 *  @SECEND
 *
 * @section gnu_tools  Required Tools
 *  @SECSTART
 *  The following tools are required to build either makefile using GNU make (links provided).
 *  Download and install all tools to a single local (@c @b C:) directory,
 *  for example, <tt><b>c:\\ti</b></tt>.
 *
 *  - Both Windows and Linux Build Machines
 *    - <a target=_blank href="https://www-a.ti.com/downloads/sds_support/TICodegenerationTools/download.htm">C6000 DSP Code Generation Tools Version 7.4.2</a> - For building the DSP target binaries.
 *  - Windows Build Machine
 *    - <a target=_blank href="http://processors.wiki.ti.com/index.php?title=Category:Code_Composer_Studio_v5">CCS Version 5.4 or higher</a> - it contains gmake and needed cygwin utilities to emulate linux commands
 *    - Microsoft Visual Studio - Needed only if compiling Host build (validated using VS 2012, VS 2013, and VS 2017)
 *  - Linux Build Machine (validated on Ubuntu 14.04) 
 *    - GNU Make - validated using v3.81
 *    - GCC - validated using v4.6.3
 *    - GCC compiler with 32b mode support is required for using VXLIB
 *      - Make sure below linux packages are installed. This is required to use GCC in 32b mode on 64b systems.
 *        @code
 *        sudo apt-get install g++-multilib libc6 libc6-dev
 *        @endcode
 *
 *  @note  A "My.TI" account is required for download and can be registered at <a target=_blank href="http://my.ti.com">my.ti.com</a>
 *  @SECEND
 *
 *
 * @section gnu_compile_windows  Build Procedure (Windows Build Machine)
 *  @SECSTART
 *  The makefile may be compiled on a Windows machine using GNU make following the procedure below.
 *  Note that items 4-6 are followed by two options, either of which
 *  may be used to accomplish the goal.
 *
 *   -# Open a windows command prompt window in the appropriate folder where the makefile is located (see @ref gnu_makefiles)
 *   -# (Optional) If building Visual Studio targets, call the @b vcvarsall.bat script that is packaged with your version of Visual Studio 
 *       to setup the Environment variables to use the x86 configuration. 
 *     - This will enable the x86 version. If the 64 bit version will be compiled, the paths are automatically updated by the makefiles.
 *       of Visual Studio (you can use a different version or path based on your configuration).
 *      @code
 *      "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" x86  
 *      @endcode
 *   -# Add two directories to the environment PATH : @b ccsv5\\utils\\bin and @b ccsv5\\utils\\cygwin.
 *     - The @b bin folder is where the gmake utility is.
 *     - The @b cygwin folder contains various cygwin utilities utilized by the makefile.
 *      @code
 *      set PATH=C:\ti\ccsv5\utils\bin;C:\ti\ccsv5\utils\cygwin;%PATH%
 *      @endcode
 *   -# (Optional) If building C66 DSP targets, correct the @b C6x_GEN_INSTALL_DIR path in the @b makefile (two options)
 *     - Directly modify the makefile  OR
 *     - Set the @b C6x_GEN_INSTALL_DIR in the environment with the proper tools path
 *   -# (Optional) If building the @ref bamplugins library from the libraries makefile, correct the @b ALGFRAMEWORK_INSTALL_DIR and @b DMAUTILS_INSTALL_DIR in paths in
 *       the @b makefile to point to the correct folders (two options)
 *     - Directly modify the makefile  OR
 *     - Set the @b ALGFRAMEWORK_INSTALL_DIR and @b DMAUTILS_INSTALL_DIR in the environment with the proper install paths
 *   -# (Optional) If building Visual Studio targets, correct the @b MSVC_GEN_INSTALL_DIR path in the @b makefile (two options)
 *     - Directly modify the makefile  OR
 *     - Set the @b MSVC_GEN_INSTALL_DIR in the environment with the proper tools path
 *     - Use only DOS path name.
 *   -# Build the makefile using the target or target rule(s) you want (full list of targets for each makefile can be found at @ref gnu_makefiles)
 *     - Enter <b><tt>gmake all</tt></b> to build all supported versions of the the binaries.
 *     - Enter <b><tt>gmake all,e66</tt></b> to build the DSP versions of the binaries only.
 *     - Enter <b><tt>gmake all,86</tt></b> to build the 32 bit windows version of the binaries only.
 *     - Enter <b><tt>gmake all,86_64W</tt></b> to build the 64 bit windows version of the binaries only.
 *     - Enter <b><tt>gmake clean</tt></b> to clean all generated object files and artifacts.
 *     - @note  In the case of the <b>Library Makefile</b>, if you want to save time and build all libraries except for the @ref bamplugins library for a given target, 
 *       you should explicity call each gmake target option except for lib/bam_plugin option.  Otherwise, a <b><tt>gmake all</tt></b> will try to build the
 *       bam_plugin library and would show build errors if the @b ALGFRAMEWORK_INSTALL_DIR and @b DMAUTILS_INSTALL_DIR variables were not defined in the environment.
 *   -# Build Options
 *     - set DEBUG=YES for debug binary for both C66 & Host Build. (Default: Release binary is generated)
 *  @SECEND
 *
 *
 * @section gnu_compile_Linux  Build Procedure (Linux Build Machine)
 *  @SECSTART
 *  The makefile may be compiled on a Linux build machine using GNU make following the procedure below.
 *  Note that items 1-3 are followed by two options, either of which
 *  may be used to accomplish the goal.
 *
 *   -# Open a linux terminal window in the appropriate folder where the makefile is located (see @ref gnu_makefiles)
 *   -# Correct the @b C6x_GEN_INSTALL_DIR path in the @b makefile (two options)
 *     - Directly modify the makefile  OR
 *     - Set the @b C6x_GEN_INSTALL_DIR in the environment with the proper tools path
 *   -# If building the @ref bamplugins library from the libraries makefile, correct the @b ALGFRAMEWORK_INSTALL_DIR and @b DMAUTILS_INSTALL_DIR in paths in the @b makefile to point to the correct folders (two options)
 *     - Directly modify the makefile  OR
 *     - Set the @b ALGFRAMEWORK_INSTALL_DIR and @b DMAUTILS_INSTALL_DIR in the environment with the proper install paths
 *   -# Build the makefile (full list of targets for each makefile can be found at @ref gnu_makefiles)
 *     - Enter <b><tt>make all</tt></b> to build all supported versions of the the binaries.
 *     - Enter <b><tt>make all,e66</tt></b> to build the DSP versions of the binaries only.
 *     - Enter <b><tt>make all,86l</tt></b> to build the 32 bit linux gcc version of the binaries only.
 *     - Enter <b><tt>make clean</tt></b> to clean all generated object files and artifacts.
 *     - @note  In the case of the <b>Library Makefile</b>, if you want to save time and build all libraries except for the bam_plugin library for a given target, 
 *       you should explicity call each make target option except for lib/bam_plugin option.  Otherwise, a <b><tt>make all</tt></b> will try to build the
 *       bam_plugin library and would show build errors if the @b ALGFRAMEWORK_INSTALL_DIR and @b DMAUTILS_INSTALL_DIR variables were not defined in the environment.
 *   -# Build Options
 *     - export DEBUG=YES for debug binary. (Default: Release binary is generated)
 *  @SECEND
 *  @endif
 */

/**
 * @page bamplugins  BAM Plugins
 *
 * <a @NSTYLE href="index.html">Back</a>
 *
 * @SPACER
 *
 *  Some selected VXLIB kernels also contain a bam_plugin folder which contains the 
 *  files necessary to plugin the respective kernel into the BAM block based processing
 *  framework.  In order to build the bam_plugin library, DMAUTILS_INSTALL_DIR should be
 *  defined in the make system due to dependent header files.  Currently, these bam plugins
 *  are utilized to provide DMA acceleration of VXLIB kernels within the TI OpenVX (TIOVX)
 *  framework.  If VXLIB is not being used in conjuction with TIOVX, then the bam_plugins
 *  can be ignored and left unused.
 *
 *  This table lists each @PACKAGE kernel and indicates if it has BAM plugin support.  The plugin files are located in the bam_plugin folder in each kernel directory.
 *
 *  <table>
 *    <tr bgcolor="lightgrey">
 *      <th> Kernel </th>
 *      <th> BAM Plugin Support </th>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_absDiff_i16s_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_absDiff_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_accumulateImage_i8u_io16s </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_accumulateSquareImage_i8u_io16s </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_accumulateWeightedImage_i8u_io8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_add_i16s_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_add_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_add_i8u_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_add_i8u_i8u_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_addSquare_i8u_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_addWeight_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_and_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_box_3x3_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_cannyNMS_i16s_i16s_i16u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelCopy_1to1_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelCombine_2to1_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelCombine_3to1_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelCombine_4to1_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelCombine_yuyv_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelExtract_1of2_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelExtract_1of3_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_channelExtract_1of4_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_IYUVtoNV12_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_IYUVtoRGB_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_IYUVtoRGBX_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_IYUVtoYUV4_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_NVXXtoIYUV_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_NVXXtoRGB_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_NVXXtoRGBX_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_NVXXtoYUV4_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBtoIYUV_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBtoNV12_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBtoRGBX_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBtoYUV4_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBXtoIYUV_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBXtoNV12_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBXtoRGB_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_RGBXtoYUV4_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_YUVXtoIYUV_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_YUVXtoNV12_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_YUVXtoRGB_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_colorConvert_YUVXtoRGBX_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convertDepth_i16s_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convertDepth_i8u_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_3x3_i8u_c16s_o16s </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_3x3_i8u_c16s_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_5x5_i8u_c16s_o16s </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_5x5_i8u_c16s_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_7x7_i8u_c16s_o16s </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_7x7_i8u_c16s_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_i8u_c16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_convolve_i8u_c16s_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_dilate_3x3_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_dilate_MxN_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_doubleThreshold_i16u_i8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_edgeTracing_i8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_equalizeHist_i8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_erode_3x3_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_erode_MxN_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_fastCorners_i8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_fastCornersDetect_i8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_fastCornersScore_i8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_fastCornersNMS_i8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_gaussian_3x3_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_gaussian_5x5_br_i8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_gaussian_5x5_i8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_halfScaleGaussian_5x5_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_halfScaleGaussian_5x5_i8u_o8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_halfScaleGaussian_5x5_br_i8u_o8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_harrisCornersDetect_i32f </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_harrisCornersNMS_i32f </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_harrisCornersScore_i16s_i16s_o32f </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_harrisCornersScore_i32s_i32s_o32f </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_histogram_i8u_o32u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_histogramCdfLut_i32u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_histogramSimple_i8u_o32u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_integralImage_i8u_o32u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_magnitude_i16s_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_meanStdDev_i8u_o32f </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_median_3x3_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_median_MxN_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_minMaxLoc_i16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_minMaxLoc_i8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_multiply_i16s_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_multiply_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_multiply_i8u_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_multiply_i8u_i8u_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_normL1_i16s_i16s_o16u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_normL2_i16s_i16s_o16u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_not_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_or_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_phase_i16s_i16s_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_remapBilinear_bc_i8u_i32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_remapNearest_bc_i8u_i32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_scaleImageBilinear_i8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_scaleImageBilinear_bc_i8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_scaleImageBilinear_br_i8u_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_scaleImageNearest_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_scharr_3x3_i8u_o16s_o16s </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_sobelX_3x3_i8u_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_sobelY_3x3_i8u_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_sobel_3x3_i8u_o16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_sobel_5x5_i8u_o16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_sobel_7x7_i8u_o16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_sobel_7x7_i8u_o32s_o32s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_subtract_i16s_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_subtract_i8u_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_subtract_i8u_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_subtract_i8u_i8u_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_tableLookup_i16s_o16s </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_tableLookup_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_thresholdBinary_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_thresholdRange_i8u_o8u </td>
 *      <td align="center"> YES </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_trackFeaturesLK_i8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpAffineBilinear_bc_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpAffineBilinear_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpAffineNearest_bc_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpAffineNearest_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpPerspectiveBilinear_bc_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpPerspectiveBilinear_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpPerspectiveNearest_bc_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_warpPerspectiveNearest_i8u_c32f_o8u </td>
 *      <td align="center">  </td>
 *    </tr>
 *    <tr>
 *      <td> VXLIB_xor_i8u_i8u_o8u
 *      <td align="center"> YES </td>
 *    </tr>
 *  </table>
 *
 */
