ARP32 C/C++ CODE GENERATION TOOLS
1.0.7 Release Notes
January 2015 

This release supports code generation for the EVE project, which includes
support for the baseline ARP32 v200 architecture as well as support for the
VCOP processor.

ISA Version Numbering Scheme:
    v200: ARP32 baseline (no VCOP support - default)
    v210: EVE            (ARP32 baseline + VCOP support)

===============================================================================
Documentation Included in this Release
===============================================================================
SPRUH24.pdf: ARP32 Optimizing C/C++ Compiler Reference Guide
SPRUH23.pdf: ARP32 Assembly Language Tools Reference Guide
SPRUHB9.pdf: VCOP Kernel-C Reference Guide

===============================================================================
Contents
===============================================================================
 1)  Installation Requirements
 2)  Major Deliverables
 3)  Usage Summary
 4)  Features
 5)  Intrinsics
 6)  Control Registers accessible via C source code
 7)  SP and GDP Global Registers accessible via C source code
 8)  Global Symbols
 9)  Dual Page Memory Map
 10) Near & Far Data Memory Model
 11) Nested Interrupt Support
 12) VCOP Kernel-C Support
 13) VCOP Compiler Aided Memory Allocation
 14) Defect Reporting

-------------------------------------------------------------------------------
1) Installation Requirements
-------------------------------------------------------------------------------

When installing the tools on Windows for use with Code Composer Studio v5.4
(CCSv5), it is recommended that you install the tools under the
"{CCSInstallRoot}\ccsv5\tools\compiler" directory.  This should happen
automatically if the tools are downloaded and installed from within CCS.
However, if the tools are not installed here, the installer will attempt to
locate your CCSv5 installation.  The installer will also warn you about
including the path of your installed tools in the CCSv5 Tools Discovery Path so
that CCSv5 can access the tools.

* If the installer is not able to locate your CCSv5 installation

If the installer is not able to locate your CCSv5 installation, then it cannot
install a necessary CCS XML file that CCSv5 needs in order to recognize ARP32 as
a valid target.  If this happens, you can manually install the XML file in
CCSv5 by copying "{YourToolsRoot}\ccsprocxml\ARP32.xml" to
"{CCSInstallRoot}\ccsv5\tools\compiler\userDevices\ARP32.xml".

* If you have installed the tools outside of the CCSv5 directory structure

If you have installed the tools outside of your CCSv5 installation, you will
need to ensure that your toolspath is added to the CCS Tools Discovery Path.
Failure to do this will prevent the CCSv5 project wizard from being able create
ARP32 projects.  To adjust the CCSv5 Tools Discovery Path please access
"Preferences->CCS->Build->Code Generation Tools".

None of these restrictions apply to the Linux installation of the tools.

-------------------------------------------------------------------------------
2) Major Deliverables
-------------------------------------------------------------------------------
This release delivers the following features related to the ARP32 architecture
evaluation tools.
 - A validated optimizing compiler toolchain supporting the ARP32 target.
 - Support for ARP32v200 specific instructions.
 - A tuned optimizer and several new optimization passes to improve
   generated code quality.
 - A branch extension mechanism to convert non-reaching branches into reaching
   branches, where possible.
 - Support for far-call trampolines for those branches and calls that still
   may not reach their destinations.
 - Support for ELF object file format by default.
    - COFF is not supported.
 - Object File compatibility checking.
 - Binary encoding support for ARP32v200 and VCOP instructions.
 - Binary ELF version of the BASE ARP32 runtime support library.
 - Support for HLA Hardware Loop Accelerator.
 - Support for VCOP Kernel-C compiler/translator for the EVE architecture
   validated with the Linux EVE Simulator, version 7.6
   - Known issues with the simulator can be found in the section
     "VCOP Kernel-C Support"
 - Support for setjmp/longjmp and exception handling
 - Support for v1.21 of the VCOP architecture specification.
 - Support for CALL with 22-bit signed offset
 - Support for LR register
 - Support for Near/Far Data Memory Model
 - Support for #pragma RETAIN and .retain assembly directive

-------------------------------------------------------------------------------
3) Basic Usage Summary
-------------------------------------------------------------------------------
The compiler options that are required to be specified for effectively using
the ARP32 compiler are:

1. -o[N]
  Activates the optimizer and turns optimizations on. N can vary from 0 to 3.
  Use -o3 for best performance.

2. --silicon_version=[ISA SELECTION] (short option: -v[ISA])
  Use this option to select the isa to compile for. Currently two variants are
  supported in the toolchain. they are:
    a. --silicon_version=v200  ==> This selects base ARP32v200 ISA
    b. --silicon_version=v210  ==> This selects base v200 with EVE support

  Specifying nothing on the command line is equivalent to choosing (a) above.

3. Two binary and two virtual encoding runtime support libraries are
   available for this toolchain.
     a. Binary Encoding:
        "rtsarp32_v200.lib": V200 isa in ELF object format (with optimization)
        "rtsarp32_v200_eh.lib": ELF V200 isa with exception handling support

     b. Virtual Encoding (deprecated):
        "rtsarp32_v200_v.lib": virtual V200 isa in ELF format
        "rtsarp32_v200_v_eh.lib": ELF V200 isa with exception handling support

4. It is not necessary to specify --abi=eabi on the command line.  EABI is used
   by default.

5. Sample command lines when using the EVE toolchain are:
        a. cl-arp32 -o3 -v210 test.c -k -z -o test.out -lrtsarp32_v200.lib -llnk.cmd
            "-v210" ensures that code is built for EVE (v210)
            "-k" keeps the generated assembly file.
            "-z" invokes the linker
            "-o" (after "-z") linker option to name the output executable

6. For more options just invoke "cl-arp32" on the command line.

-------------------------------------------------------------------------------
4) Features
-------------------------------------------------------------------------------

1. Calling Convention
   With this release the ARP32 calling convention changes to now be the
   following
    a. Argument registers      : R2, R3, R4
    b. Save on Entry registers : R5, R6, R7
    c. Save on Call registers  : R0, R1, R2, R3, R4
    d. Return Value            : R0  [also R1 for 64bit return values]
    e. Return by ref           : R1

2. Hardware Loop Accelerator support
   The ARP32 architecutre has hardware support for loop execution through the
   Hardware Loop Accelerator (HLA).  This support is enabled whenever an
   advanced optimization level is given (-o2, -o3) during compilation.

3. Branch Expansion/Patching mechanism
   Branch instructions on the ARP32 ISA have a limited PC-relative offset range.

   In the case of binary encoding, branch expansion is done by the assembler
   and not by the compiler itself.  This allows us to better honor alignment
   restrictions set by the the compiler.  Non-reaching branches are not
   converted into register-indirect branches, which means that there is still
   a chance that a branch will not reach.  This will be compensated by
   trampoline generation by the linker if the branch target is located in
   another section.

4. Object File compatibility checking
   This checks to make sure that all object files being linked together are
   for the same ISA and use the same encoding mechanisms.

5. Immediate operands for branch and call instructions are right-shifted by 1.
   This provides the instructions with larger reach in memory to their
   targets.

6. --plain_char=<signed|unsigned>
   Plain chars (e.g. "char") now default to being signed.  The --plain_char
   option has been provided if you wish to change this behavior to make
   plan chars unsigned: "--plain_char=unsigned"

7. 64bit type support
   The toolchain supports "double" and "long long" as 64bit types that can
   be used in code.  But note that the toolchain does not provide optimal
   support.  All of the 64bit math routines are implemented as RTS routines.

8. Far-call Trampoline support
   Trampolines are enabled by default and are generated for far calls that
   exceed the reach of the ARP32 CALL or BRANCH instructions, which use a
   16-bit halfword offset field.  In addition, the following options are
   supported to allow user tweaking of trampoline generation and placement:

    --trampolines=[on, off]: Disable trampoline generation (on by default).

    --minimize_trampolines=[off, postorder]: Attempt to place callees before
                                             callers so that the target
                                             address is known and a trampoline
                                             is only generated if it is needed.
                                             (postorder by default).

    --trampoline_min_spacing=num: Set the minimum space between non-adjacent
                                  trampolines.  A higher value minimizes
                                  fragmentation but may yield more trampolines.

9. 64bit TSC support
   The 32-bit TSCR counter register has now been extended to 64bits with two
   registers, TSCL and TSCH.  These registers are accessible via user
   intrinsics, as described below.  _tsc_start() will reset the counter to 0.
   _tsc_gettime() will return the 64bit counter value.

10. setjmp/longjmp support
   You may use the setjmp and longjmp routines as provided by the RTS
   libraries:

     int setjmp(register jmp_buf env);
     int longjmp(register jmp_buf env, register int val);

   These routines are also used to provide C++ exception handling support,
   which can be enabled using the --exceptions compiler option and by linking
   with the rtsarp32_v200_eh.lib RTS library.

11. VCOP Compiler Aided Memory Allocation (CAMA) support

-------------------------------------------------------------------------------
5) Intrinsics
-------------------------------------------------------------------------------

The supported intrinsics are documented within the "arp32.h" header file, which
is distributed as part of the RTS package.  Programs that wish to use an
intrinsic MUST include "arp32.h" in their source code, otherwise the compiler
will not generate the appropriate code.  Here is the list of supported
intrinsics:

* ARP32 Standard Intrinsics
   int          _revr (int, int);                      // REV instruction
   int          _rotr (int, int);                      // ROT instruction
   int          _rotc (int, int);                      // ROTC instruction
   int          _sadd (int, int);                      // SADD instruction
   int          _ssub (int, int);                      // SSUB instruction
   int          _norm (int);                           // LMBD 1, int, int
   int          _satn (unsigned int, int);             // SATN instruction
   int          _abs  (int);                           // ABS instruction
   int          _min  (int, int);                      // MIN instruction
   int          _max  (int, int);                      // MAX instruction
   unsigned int _minu (unsigned int, unsigned int);    // MINU instruction
   unsigned int _maxu (unsigned int, unsigned int);    // MAXU instruction
   unsigned int _lmbd (unsigned int, unsigned int);    // LMBD instruction
   long long    _itoll(unsigned int, unsigned int);    // INT to LONG LONG
   unsigned int _hill (long long);                     // HI LONG LONG to INT
   unsigned int _loll (long long);                     // LOW LONG LONG to INT
   void         _idle ();                              // IDLE instruction
   void         _swi  ();                              // SWI instruction

* ARP32 Interrupt Control Intrinsics
   unsigned int _get_inum();                           // Retrieve INUM bits
   unsigned int _get_cpunum();                         // Retrieve CPUNUM bits
   unsigned int _enable_interrupts();
   unsigned int _disable_interrupts();
   void         _restore_interrupts(unsigned int);

* ARP32 Time Stamp Counter Control Intrinsics
   void         _tsc_start();                          // Set TSCL = 0 to reset
   uns longlong _tsc_gettime();                        // Retrieve TSCL,TSCH

* ARP32 Standard Register-Based Bit Processing Intrinsics
   int          _extr (unsigned int, int);                        // EXT
   unsigned int _extur(unsigned int, int);                        // EXTU
   int          _setr (unsigned int, int);                        // SET
   int          _clrr (unsigned int, int);                        // CLR

* ARP32 Standard Immediate-Based Bit Processing Intrinsics
   int          _ext  (unsigned int, unsigned int, int);          // EXT
   unsigned int _extu (unsigned int, unsigned int, unsigned int); // EXTU
   unsigned int _set  (unsigned int, unsigned int, unsigned int); // SET
   unsigned int _clr  (unsigned int, unsigned int, unsigned int); // CLR

Please refer to the ARP32 specification proper documentation on each
instruction.

-------------------------------------------------------------------------------
6) Control Registers accessible via C source code
-------------------------------------------------------------------------------
Programmers may reference any of the following control registers in C source
code:

  ISR, ICR, IRP, NRP, IFR, IER, TSCL, TSCH, LR

Registers must be declared according to the following syntax:

  extern unsigned int cregister volatile ISR;

Note: Direct access of the CSR status register is not permitted.  Interrupt
control intrinsics are provided to provide access to the pertinent CSR bits.

-------------------------------------------------------------------------------
7) SP and GDP Global Registers accessible via C source code
-------------------------------------------------------------------------------
Programmers may access the stack pointer (SP) and global data pointer (GDP) by
including the following declarations:

  register volatile unsigned int __SP;
  register volatile unsigned int __GDP;

-------------------------------------------------------------------------------
8) Global Symbols
-------------------------------------------------------------------------------
The following global symbols are used to provide program information:

  __TI_STACK_END   - Base of the stack used to initialize the SP register.
  __TI_STACK_SIZE  - Size of the stack.
  __TI_STATIC_BASE - Base data address used to initialize the GDP register.
  __TI_SYSMEM_SIZE - Size of memory heap.

-------------------------------------------------------------------------------
9) Dual Page Memory Map
-------------------------------------------------------------------------------
When building an ARP32 project according to a dual page memory map, PAGE 0 is
always dedicated to CODE, and PAGE 1 is always dedicated to DATA.  Section
placement must be configured via a linker command file.  Please refer to the
includined sample linker command file "lnkdp.cmd" for an example.

* Considerations:
  - Data sections must be explicitly placed on PAGE 1. If a data section is not
    mentioned in the linker command file, the linker will attempt to place the
    section in whatever region or page has available space for it. If a data
    section ends up being placed on PAGE 0 (CODE), this will result in runtime
    failure.

  - Data regions in the memory map for PAGE 1 shouldn't begin at address 0x0.
    A program should not ordinarily expect data placed at address 0x0 to be
    valid since pointers to this location are commonly understood to be NULL
    pointers.  Therefore, it is common for programs to expect that a pointer to
    location 0x0 is a NULL pointer and isn't valid.

Example memory map:
    MEMORY
    {
        PAGE 0:
            INTVECS   :   origin = 00000000h   length = 00000030h
            EXITSECT  :   origin = 00000100h   length = 00000100h
            RESET     :   origin = 00000200h   length = 000002c0h
            ON_CHIP   :   origin = 00000500h   length = 0023FAFFh

        PAGE 1:
            DATASECT  :   origin = 00000004h   length = 0001FFFFh
            STACKSECT :   origin = 00030000h   length = 0003FFFFh
            SL2       :   origin = 00400000h   length = 00080000h
    }

-------------------------------------------------------------------------------
10) Near and Far Data Memory Model
-------------------------------------------------------------------------------

* Usage:

The ARP32 toolchain implements a near and far data memory model.  By default,
all aggregate data is considered 'far' and is accessed indirectly via an
absolute address.  All scalar and constant data values are considered 'near'
and are placed within reach of the GDP global data pointer register.
Programmers can change the default data memory model using the following
option:

  --mem_model:data={near,far,far_aggregates} ("far_aggregates" is default)

In addition, the compiler supports 'near' and 'far' keyword qualifiers that
will allow programmers to specifically designate certain data as 'near'
(i.e. reachable from GDP offset) or 'far' (i.e. not reachable from GDP offset)
given programmer knowledge about the memory map. This will allow programmers to
achieve the best possible performance given existing memory map constraints.

The 'near' and 'far' qualifiers can also be applied to data pointers in order
to affect how the corresponding data is accessed, regardless of how or where
that data is placed in the memory space.

* Section Placement:

The compiler relies on six data sections to control data placement:

      | .bss     (uninitialized data)
NEAR -| .data    (initialized data)
      | .rodata  (initialized constant data)


      | .far     (uninitialized data)
FAR --| .fardata (initialized data)
      | .const   (initialized constant data)

Because the NEAR data sections are all expected to be accessable within range
of the address stored in the GDP register, the linker will automatically group
them together in the memory map.   Programmers can control this via the linker
command file to ensure they are grouped and placed within an appropriate data
region on the memory map, including PAGE # for a dual-page memory map:

    GROUP
    {
        .bss            /* This order facilitates a single segment for */
        .data           /* GDP-relative addressing                     */
        .rodata
    } > DATAREGION PAGE 1

The FAR data sections can be located anywhere on the memory map since the data
within them are always access using an absolute address.  It is a good idea for
programmers to also place them explicitly using the linker command file. The
reason for this is that if they are not explicitly placed via the linker
command file, the linker will find space for them in any of the other memory
regions.  This can become a problem with the dual-page memory model since the
linker may attempt to place them on a memory page reserved for code, and this
will likely result in an execution failure. For ARP32, this means they should
be placed on PAGE 1, which is reserved for data:

    .far        >   DATAREGION PAGE 1
    .fardata    >   DATAREGION PAGE 1
    .const      >   DATAREGION PAGE 1

Please refer to the following included sample linker command files for example:
    lnk.cmd   - Single Page Memory Map
    lnkdp.cmd - Dual Page Memory Map

-------------------------------------------------------------------------------
11) Nested Interrupt Support
-------------------------------------------------------------------------------
The ARP32 compiler has the capability of generating save and restore operations
for maskable and non-maskable interrupt handlers.  This will facilitate
single-level (using NMI) or multiple-level nested interrupts.  This capability
is provided with the --saveregs={nested_nmi,nested_std,nested_full} command
line option.  Modes include:

  --savereg=nested_nmi
            facilitates single-level nested interrupts by generating
            save and restore operations for non-maskable interrupt
            handlers.

  --savereg=nested_std
            facilitates multi-level nested interrupts by generating save
            and restore operations for non-maskable interrupt handlers
            and maskable interrupt handlers.

  --savereg=nested_full
            facilitates full multi-level nested interrupts by generating
            save and restore operations for non-maskable interrupt
            handlers and maskable interrupt handlers, including the stack
            pointer register and interrupt enable register."

If a function is designated as an interrupt handler, the compiler will ensure
that it is always included in the final link of a program.

-------------------------------------------------------------------------------
12) VCOP Kernel-C Support
-------------------------------------------------------------------------------
This release package includes the VCOP Kernel-C translator for kernels in the
EVE architecture. This tool should be run by invoking the shell (cl-arp32) and
passing the kernel file, along with any relevant files, as arguments. The
execution of the translator requires the file vcop.h, which is located in the
directory 'vcop' in the ARP32 include path. Should the user wish to not use
the base include directory that comes with installation, the 'vcop' directory
must be present in the custom library for VCOP kernels to compile correctly.

To invoke:
> cl-arp32 --silicon_version=v210 [options] kernel.k runner.c

Here are a list of options that will effect the execution of the vcop-c
compiler:

1) --vcc_extension, -ek=.ext
   Change the extension that is associated with VCOP Kernel-C files. The
   default extension is .k
2) --keep_vccfile, -kv
   Retain the translated VCOP Kernel-C file created after invocation of the
   translator. Its default name is <kernel_file>.c
3) --no_warnings, -pdw
   Removes warning messages emitted by the VCOP Kernel-C translator
4) --define, -D
   Predefine a name to a value, or 1 by default
5) --undefine, -U
   Undefine a name
6) --include_path, -I
   Add a path to #include searches, note that files included in a kernel file
   will be translated by vcc and therefore must conform to the languages
   rules.
7) --cpp_out, -fg
   Outputs C++ style pragmas and functions that can then be compiled as C++
   code.
8) --output_kernel_headers, -kh
   Tool will output a header file detailing each function provided. Includes
   parameter register count, initialization, loop, and basic runner functions.
   See the internal wiki or the VCOP Programmer's guide on information about
   this output file.
9) --vcop_unconditional_loads, -lu
   By default, the VCOP Kernel-C translator will pessimistically determine that
   any vector load whose address increments are unknown may be conditional, and
   thus preserves the register to which it loads.

   This option is provided to change the default behavior so that these loads
   are considered unconditional. This will allow the register to be reused,
   thus easing register pressure at the cost of possibly assuming that
   a register's value will be updated during each loop iteration when it might
   not be.

In addition, there are intrinsics and macros that help work with the EVE
architecture. The vcop.h header file must be included to use these functions:

_vcop_vloop_done()
   Force the scalar core to wait for the vector core to run to completion.

_vcop_vloop_ready()
   Force the scalar core to wait for the vector core to be ready to accept
   additional vector instructions.

VCOP_BUF_SWITCH_SET(w, hb, lb, ha, la)
   Sets each of the VCOP memory buffers separately. Use the macros defined in
   vcop.h of the form <buffer>_<SYST | VCOP> for readability.
   Ex: VCOP_BUF_SWITCH_SET(WBUF_VCOP, IBUFHB_SYST, IBUFLB_VCOP, IBUFHA_SYST,
                           IBUFLA_VCOP);

VCOP_WRITE_BUF_SWITCH(k)
   Writes a single 20-bit value directly into the memory buffer MMR. Refer to
   the VCOP documentation for the accepted values.

VCOP_BUF_SWITCH_TOGGLE(BUF_PING | BUF_PONG)
   Switches between two common memory buffer setups to more easily simulate
   the ping-pong buffer model detailed in the VCOP specification.

VCOP_READ_BUF_SWITCH()
   Returns the 20-bit value currently written to the VCOP memory buffer MMR

VCOP_SET_MEM_VIEW(FLAT_MEM_VIEW | ALIAS_128K_VIEW)
   Switch between the flat and aliased memory views. Refer to the VCOP
   specification for more information.

The VCOP Kernel-C Functional Specification includes additional information and
advice to avoid common pitfalls.

This release has been validated on Linux with version 7.6 of the EVE
simulator. There are two issues with this version:
   - Using pack() with values greater than 33 bits could result in calculation
     errors. 
   - Circular buffers in conjunction with the ds2() distribution may store
     values into the wrong memory location.

-------------------------------------------------------------------------------
13) VCOP Compiler Aided Memory Allocation
-------------------------------------------------------------------------------
The release supports a VCOP aware heap allocator that will allow users to use
the following APIs to manage VCOP heap memory (you must include vcop.h):

void *vcop_malloc(VCOP_MEMHEAP heap, int size)
      - Allocate 'size' bytes from a VCOP heap, using heap id:
        VCOP_IBUFLA, VCOP_IBUFHA, VCOP_IBUFLB, VCOP_IBUFHB, VCOP_WMEM

void  vcop_free(void *userptr)
      - Free memory indicated by pointer.  Allocator will automatically
        determine the corresponding heap

void  vcop_setview(VCOP_MEMVIEW view)
      - Set allocator according to VCOP_MEMFLAT or VCOP_MEMALIASED view.
        Under aliased view, allocator will also manage memory for aliased
        heaps when memory is allocated from IBUFLA or IBUFHA.
        views: VCOP_MEMFLAT (default) or VCOP_MEMALIASED

void  vcop_minit()
      - Reset the state of the VCOP memory allocator.  This call is done
        automatically the first time vcop_malloc() is invoked.  
        Note: It does NOT free previously allocated memory.

The routines are implemented within the provided RTS library.

In order to use these APIs, you must define the following symbols and cfg in
the linker command file (see included link.vcop.cmd for an example):

/*----------------------------------------------------------------------------
* Define VCOP memory regions
*---------------------------------------------------------------------------*/
MEMORY
{
  PAGE 1:
    WMEM:        origin = 0x40040000, length = 0x7E00
    IMEMLA:      origin = 0x40050000, length = 0x4000
    IMEMHA:      origin = 0x40054000, length = 0x4000
    IMEMLB:      origin = 0x40070000, length = 0x4000
    IMEMHB:      origin = 0x40074000, length = 0x4000
}

/*----------------------------------------------------------------------------
* Define VCOP heap sizes. These can be smaller than the actual memory region
*---------------------------------------------------------------------------*/
IMEML_SIZE = 0x4000;
IMEMH_SIZE = 0x4000;
WMEM_SIZE  = 0x4000;

/*----------------------------------------------------------------------------
* Define VCOP heap locations and ensure heaps span the appropriate size
*---------------------------------------------------------------------------*/
SECTIONS
{
  .imemla: { *(.imemla) . += (IMEML_SIZE - 8); } > IMEMLA PAGE 1
  .imemha: { *(.imemha) . += (IMEMH_SIZE - 8); } > IMEMHA PAGE 1
  .imemlb: { *(.imemlb) . += (IMEML_SIZE - 8); } > IMEMLB PAGE 1
  .imemhb: { *(.imemhb) . += (IMEMH_SIZE - 8); } > IMEMHB PAGE 1
  .wmem  : { *(.wmem)   . += (WMEM_SIZE  - 8); } > WMEM   PAGE 1
}

If you would like to use some of the space in one of these memory regions, you
can adjust the size of the size symbols appropriately. However, if IMEML_SIZE,
IMEMH_SIZE, and WMEM_SIZE are not defined in the linker command file, and
you are attempting to use vcop_allocate() or vcop_free(), the executable will
not be able to link and you will see an error, e.g.:

 undefined  first referenced
  symbol        in file
 ---------  ----------------
 IMEMH_SIZE rtsarp32_v200.lib<vcop_memory.obj>
 IMEML_SIZE rtsarp32_v200.lib<vcop_memory.obj>
 WMEM_SIZE  rtsarp32_v200.lib<vcop_memory.obj>

-------------------------------------------------------------------------------
14) Defect Reporting
-------------------------------------------------------------------------------
All EVE (ARP32+VCOP) compiler defects reports should be submitted using the SDO
ClearQuest database (http://cqweb.itg.ti.com/SDO).  Enter 'ARP32 Code
Generation Tools' in the "Product" section, and "CodeGenGroup" as the Assignee.
