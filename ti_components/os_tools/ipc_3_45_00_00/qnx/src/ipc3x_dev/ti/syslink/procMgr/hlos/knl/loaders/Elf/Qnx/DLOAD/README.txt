
                  TMS320C6000 C/C++ CODE GENERATION TOOLS
                    0.4 ELF Dynamic Loader Release Notes
		               August 2011
			  updated February 2013


===============================================================================
Contents
===============================================================================
1. The ELF Dynamic Loader
  1.1 Alpha Package Manifest
  1.2 Building the Dynamic Loader Tester (dlti.gen)
  1.3 User-Interaction Mode Commands

2. Getting Started
  2.1 Building a Dynamic Executable
  2.2 Building a Dynamic Library
  2.3 "Hello World" Example
  2.4 Known Issues

3. Relevant Documents


-------------------------------------------------------------------------------
1. The ELF Dynamic Loader
-------------------------------------------------------------------------------

This alpha package contains a reference implementation of an ELF dynamic
loader.  This implementation is intended to be loaded and run on a C6x/TMS470
architecture.  Once up and running, it provides a user-interaction mode
in which you can load and execute dynamic libraries that are linked
against the base image (the loader itself).

1.1 Alpha Package Manifest
--------------------------

Top Level:

   Makefile
   Makefile.gen
   lnkc60.cmd
   lnk470.cmd
   README.txt

Dynamic Loader API Specification (DLOAD_API):

   dload_api.h
   api_version_change.log

C60-Specific Relocation Processing (C60_DLOAD_REL):

   c60_reloc.c
   c60_reloc.h
   test_c60_reloc.cpp
   test_c60_reloc.h

C60-Specific Dynamic Loading Functions (C60_DLOAD_DYN):

   c60_dynamic.c
   c60_dynamic.h
   c60_elf32.h

TMS470-Specific Relocation Processing (TMS470_DLOAD_REL):

   arm_reloc.c
   arm_reloc.h
   test_arm_reloc.cpp
   test_arm_reloc.h

TMS470-Specific Dynamic Loading Functions (TMS470_DLOAD_DYN):

   arm_dynamic.c
   arm_dynamic.h
   arm_elf32.h

Symbol Table Management (DLOAD_SYM)

   symtab.c

Core Dynamic Loader (DLOAD):

   ArrayList.c
   ArrayList.h
   Queue.h
   dload.c
   dload.h
   dload_endian.c
   dload_endian.h
   elf32.c
   elf32.h
   relocate.h
   symtab.h
   util.h
   version.h
   virtual_targets.h

Dynamic Loader Tester Client-Provided Functions (DLWRAPPER):

   Stack.h
   arm_export.cmd
   c60_export.cmd
   dlmodules.c
   dlw.c
   dlw_client.c
   dlw_debug.c
   dlw_debug.h
   dlw_dsbt.c
   dlw_dsbt.h
   dlw_trgmem.c
   dlw_trgmem.h
   read_me_dlwrapper.txt
   ridl_client.c
   ridl_client.h
   Makefile.ridl

1.2 Building the Dynamic Loader Tester (dlti.gen)
-------------------------------------------------------

Included in the alpha package is a Makefile which can be used to build
the Dynamic Loader Tester (dlti.gen).  As mentioned above, this
reference implementation of the ELF dynamic loader is intended to be
loaded and run on the C6x or TMS470 as a base image executable file.The
extension of the loader is the host platform on which it is to run.

With the latest alpha C6x/TMS470 tools in your path and your C_DIR
and C6X_C_DIR/TMS470_C_DIR environment variables set up to provide
access to the RTS header files and libraries, you can then build
dlti.gen using gmake:

	%> gmake TARGET_CC=ARM

           or

	%> gmake TARGET_CC=C60

This will build an executable, dlti.gen, which you can load and
start running with a version of CCS that supports loading a C6x/ARM ELF
executable object file (or your favorite standalone simulator tool).
(Although, the dlti.gen can be built for either C6000 or TMS470,
the documentation and examples below use C6000 for illustration
purposes.)

For example, we use a tool called "kelvin" which is a standalone
C6x simulator that supports loading ELF executable object files.
We start by loading and starting the run of dlti.gen as follows:

	%> kelvin -q dlti.gen

When the dynamic loader starts running it places itself into a user-
interactive mode in which it can receive commands from the user.
Section 1.3 reviews the list of commands that are available in this
user-interactive mode.

Alternatively, you can write user-interaction mode commands into a text
file, one command per file.  This file can then used with the --script
command-line option when invoking the dynamic loader.

An example:

	dl_cmds.txt contains:

		base_image dlti.gen
		load hello.dll
		execute
		exit

	invoke dynamic loader:

		%> kelvin_elf dlti.gen --script dl_cmds.txt

The dynamic loader will be loaded and started running, then it will
process each command from the script file in the sequence that it
appears in the text file.


1.3 User-Interaction Mode Commands
----------------------------------

When dlti.gen is set running on the C6x, it enters a user-interactive
mode, displaying a prompt for the user as follows:

	RIDL>

At this point the dynamic loader is waiting for a command from the user.
The available user-interaction mode commands are as follows:

	"information"

		- Provide information about location of loader's copy of
		  printf() and exit() functions.

	"load_executable <program> [<argc> <argv[0]> <argv[1]> ...]"

		- Load an executable program into target memory with
		  optional command-line arguments.

	"core <entry point> [<argc> <argv[0]> <argv[1]> ...]"

		- Load the core image "prog.dump" into target memory,
		  setting the specified address as the entry point.
		  Can also provide an argument list to be passed into
		  the executable program.

	"execute"

		- Transfer control to the most recently loaded program.

	"unload"

		- Unload the last program that was loaded into memory.

	"base_image <program>"

		- Load the global symbols from the dynamic symbol table
		  of the specified program.  It is assumed that the
		  specified program has already been loaded into target
		  memory and is running.

	"debug"

		- Turn on internal debugging.

	"profile"

		- Turn on internal profiling.

	"exit"

		- Terminate execution of the dynamic loader executable.

	"help"

		- Display list of available user-interaction mode
		  commands.

You can also terminate execution of the dynamic loader with "control-D".


-------------------------------------------------------------------------------
2. Getting Started
-------------------------------------------------------------------------------

The dynamic loader included in this alpha release supports basic dynamic
linking functionalities.

The sample dynamic linking model described here is similar to a system where
a Real Time OS (RTOS) running on the DSP. The RTOS is assumed to be loaded by
traditional means (bootstrap) and shall be running on the DSP. The DLLs loaded
by the dynamic loader in this system is expected to call RTOS functions. Hence
the RTOS shall 'export' functions that a DLL is expected to call. Any module
(usually RTOS) that is boot loaded in a dynamic linking system and 'exports'
a set of functions to be called by dynamically loaded library is called a
base image in this document.

The dynamic loader has the flexibility of running on the DSP to load the DLLs
on the DSP or in an ARM+DSP system, the dynamic loader can run on the ARM side
and still load the DLLs on the DSP side.

In the sample dynamic linking model, the dynamic loader + some RTS functions
are built as the base image (dlti.gen). This base image is first loader on the
simulator. Then the dynamic loader in the base image can load any DLLs.

In order for the dynamic loader to resolve DLL references to the functions in
the base image, it needs to know the symbols exported from the base image and
their addresses. Hence, the dynamic loader should read the base image and load
its dynamic symbols. In the system described here, this means the dlti.gen is
reading itself.

2.1 Building a Dynamic Executable
---------------------------------

A dynamic executable is essentially a statically linked executable file
that contains extra information in the form of a dynamic segment that
can be used when a dynamic library is loaded and needs symbols that are
defined in the dynamic executable.

In the sample system described here, the reference implementation of the
dynamic loader (RIDL) is built as a base image. This base image also contains
the basic IO functions and some runtime support (RTS) function . The
base image should export these IO and RTS functions. These symbols will then
become available to a dynamic library when it is dynamically loaded and linked
against the dynamic executable.

To accomplish exporting of symbols, there are two methods available:

	1. Declare exported symbols explicitly in the source of the
	   dynamic executable using "__declspec(dllexport)".

	   For example, if I want to export "exp_func" from the dynamic
	   executable, I can declare it in my source as follows;

	   __declspec(dllexport) int exp_func();

	2. Use --export option at link time.  You can specify one or
	   more symbols to be exported with "--export=<symbol" on the
	   linker command line or in a linker command file.

	   For example, you could export exp_func() at link time
	   with:

	   %> cl6x --abi=elfabi ... -z --dynamic=exe --export=exp_func ...

In general, to build a dynamic executable, you must specify
--dynamic=exe or --dynamic on the linker command line or in a
linker_command file.

Consider the build of the dlti.gen file described above as an
example of how to build a dynamic executable or "base image":

	%> cl6x --abi=elfabi ... -z *.obj ... --dynamic --export=printf ...



2.2 Building a Dynamic Library
------------------------------

A dynamic library is a shared object that contains dynamic information
in the form of a dynamic segment.  It is relocatable and can import
symbols from other ELF dynamic objects that it links against and it can
export symbols that it defines itself.

Importing and exporting of symbols can be accomplished in two ways,
similarly to how it can be done in dynamic executables:

	1. Declare exported and/or imported symbols explicitly in
	   the source code of the dynamic library using
	   "__declspec(dllexport)" for exported symbols and
	   "__declspec(dllimport)" for imported symbols.

	   For example, if I want to export a function, red_fish(),
	   and import another function, blue_fish(), I could specify
	   this in a source file as follows:

	   __declspec(dllexport) long red_fish();
	   __declspec(dllimport) int blue_fish();

	2. You can also specify symbols to be imported or exported on
	   the linker command line (or in a linker command file) using
	   "--import=<symbol>" or "--export=<symbol>".

	   So at link time, you might say:

	   %> cl6x --abi=elfabi ... -z --dynamic=lib --export=red_fish --import=blue_fish blue.dll -o red.dll

	   This informs the linker that the definition of red_fish()
	   will be in the red.dll dynamic library and that we can find
	   and use the definition of blue_fish() in blue.dll.

In general, to build a dynamic library, you must specify --dynamic=lib
on the linker command line or in a linker_command file.  In addition,
if any symbols are imported from other dynamic objects, then those
dynamic objects must be specified on the linker command line when the
dynamic library is built.  This is sometimes referred to as static
binding.


2.3 "Hello World" Example
-------------------------

First compile this simple "Hello World" source (hello.c):

   #include <stdio.h>
   __declspec(dllexport) int start();
   int start()
   {
      printf("Hello World\n");
      return 0;
   }

Then build a dynamic library called "hello.dll":

   %> cl6x -mv6400+ --abi=elfabi hello.c -z --import=printf --dynamic=lib -o hello.dll dlti.gen -e start

Now, load the dynamic loader using a loader that supports C6x ELF
executable object files.  Then start the dynamic loader running.
You will see the "RIDL" prompt come up and then you need to issue
the following commands:

	RIDL> base_image dlti.gen
	RIDL> load hello.dll
	RIDL> execute

You should see the "Hello World" message displayed and then control
will return to the "RIDL" prompt.


2.4 Known Issues
----------------

- By default, the linker will use the output file name as the DT_SONAME
  in the dynamic segment, but the linker supports a --soname option
  that allows you to specify a custom name for a dynamic object.  The
  CORE dynamic loader asks the client to find the physical file that
  matches the SONAME and load it. However the RIDL client code does not
  implement any mechanism to find the physical file. It simply tries to
  open a file with the SONAME in the current directory. Hence the dependent
  library loading in the RIDL client code will work only if the SONAME
  is the same as the dynamic library name and also the file is in the
  current directory.

  A system shall implement a proper mechanism (registry for example) to
  find the file given the SONAME.

  We do not plan to add such support in this reference implementation.

-------------------------------------------------------------------------------
3. Relevant Documents
-------------------------------------------------------------------------------

Please see the Texas Instruments Embedded Porcessor Wiki for more information
about the architecture, specifications, and use cases for the dynamic loader.
The specific URL is:

http://processors.wiki.ti.com/index.php/C6000_EABI:Dynamic_Loader


Also refer to the C6000 Embedded Application binary Interface (EABI)
specification, available from:

http://www.ti.com/lit/an/sprab89/sprab89.pdf

(The above links are current as of Feb 2013.)