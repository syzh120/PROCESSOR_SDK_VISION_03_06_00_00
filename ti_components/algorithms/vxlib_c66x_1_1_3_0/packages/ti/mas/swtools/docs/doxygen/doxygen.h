/*
 * This is a little header file which doxygen parses to generate the main
 * documentation page
 */

/**
 * @mainpage SWTOOLS USER MANUAL
 *
 * @section description Description
 *
 *  This component contains tools that are shared by other software components during the configuration and build procedures.
 *  For example, it contains:
 *  - Perl script support for cygwinxdc.bat files.
 *  - Version.xdt template file that is to be used by all packages to implement the Version interface.
 *  - JavaScript functions that automate creation of ClearCase related files.
 *  - <b>CommonBld</b> module containing common build utilities that can be shared across the packages to avoid duplication.
 *
 *  @section usage USAGE
 *
 *   - <a href="commonbld.html"> CommonBld Module </a>
 *
 *   - <a href="clearcase.html"> Clearcase Related Generation Scripts </a>
 *
 *   - <a href="relnotes.html"> Release Notes Generation </a>
 *
 *   - <a href="label.html"> Labeling Script </a>
 *
 *   - <a href="commonconf.html"> Common <b>config.bld</b> and <b>cygwinxdc.bat</b> </a>
 *
 *
 *   @page COMMONBLD CommonBld Module
 *
 *   @section desc Description
 *   This module contains common build functionality for the Package.bld.
 *   This file is created to avoid duplication of common processing in different packages.
 *
 *   @section location Location
 *    <b> ti\\mas\\swtools\\ </b>
 *
 *   @section usage Usage
 *
 *    The Usage of CommonBld Module is described through the package.bld sample files. Please
 *    follow the links in <b>package.bld</b> for more information.
 *    - <a href="packagebld.html"> Sample package.bld for package </a>
 *    - <a href="packagebldtest.html"> Sample package.bld for test package </a>
 *
 *   @page PACKAGEBLD Package.bld
 *
 *  \verbatim
 /******************************************************************************
 * FILE PURPOSE: Build description for package ti.mas.xxx
 ******************************************************************************
 * FILE NAME: package.bld
 *
 * DESCRIPTION: This file contains build attributes for package ti.mas.xxx
 *
 * TABS: NONE
 *
 * Copyright (C) 2008, Texas Instruments, Inc.
 *****************************************************************************\/
 \endverbatim
 <CODE>
 *
 *  var Package=xdc.loadCapsule('ti/mas/swtools/CommonBld.xs');
 *
 *  <a href="name.html"> Package.name </a>="xxx";
 *
 *  <a href="packagefiles.html"> Package.files</a>[..] = {
 *
 *     - <a href="base.html"> base_directory</a>: "src",
 *
 *     - <a href="srcfiles.html"> files</a>:[...],
 *
 *     - <a href="target.html"> target</a>:[ "c55s", "c55l"],
 *
 *     - <a href="cmodel.html"> cmodel</a>: true,
 *
 *     - <a href="flags.html"> compiler_flags</a>: "default-size",
 *
 *     - <a href="defs.html"> def_flags</a>: " -dTEST"
 *
 *    } <BR>
 *
 * <a href="packageargs.html">Package.args </a>[..]=
 * {
 *   - <a href="value.html"> value</a>:"SAMPLE",
 *
 *   - <a href="action.html"> action</a>: function()
 *   { <BR>
 *      /* Statement of Actions*\/<BR>
 *      ...............<BR>
 *      ...............<BR>
 *   },
 *
 *  - <a href="usage.html"> usageComment </a>: "Deliver Sample Code",
 *
 *  - <a href="type.html"> type </a>: "N"
 *
 * };<BR>
 *
 * <a href="archivefiles.html">Package.archiveFiles </a>[...]=
 * {
 *     - <a href="base.html"> base_directory</a>: "src",
 *
 *     -  <a href="filesarch.html"> files</a>:[...],
 *
 *     - <a href="target.html"> target</a>:[ "c55s", "c55l"],
 *
 *     -  <a href="deliverytype.html"> delivery_type</a>:"src",
 *
 * };<BR>
 *
 * /* Set up the target architecture *\/<BR>
 *  <a href="targets.html">Package.targets </a> = [C54, C54_far, C55,C55_large, C64, C64_big_endian, C64P, C64P_big_endian];
 *
 *  /* Set up version numbers for this package *\/ <BR>
 *  <a href="version.html"> Package.version </a> = [M,m,X,P];
 *
 *  <a href="createVersion.html"> Package.createVersion</a>();
 *
 *    /* Include custom makefile to generate doxygen documents *\/<BR>
 *  <a href="include.html">Package.includeMake</a>("Makedocs.mk");
 *
 *  /* Parse XDC Arguments *\/<BR>
 *  <a href="parse.html">Package.parseArgs</a>(arguments);
 *
 *  /* Create Library  *\/<BR>
 *  <a href="lib.html">Package.createLib</a>(Package.name);
 *
 *  /* Create Archive  *\/<BR>
 *  <a href="archive.html"> Package.createArchive</a>();
 *
 *  /* Clean Package  *\/<BR>
 *  <a href="clean.html"> Package.packageClean</a>();
 *
 *  /* nothing past this point *\/
 *   </CODE>
 *
 *   @page PACKAGEBLDTEST Package.bld for Test Package
 *
 *  \verbatim
 /******************************************************************************
 * FILE PURPOSE: Build description for package ti.mas.xxx.test
 ******************************************************************************
 * FILE NAME: package.bld
 *
 * DESCRIPTION: This file contains build attributes for package ti.mas.xxx.test
 *
 * TABS: NONE
 *
 * Copyright (C) 2008, Texas Instruments, Inc.
 *****************************************************************************\/
 \endverbatim
 * <CODE>
 *  var Package=xdc.loadCapsule('ti/mas/swtools/CommonBld.xs');
 *
 *  <a href="name.html"> Package.name </a>="xxx";
 *
 *  <a href="packagefiles.html"> Package.files</a>[..] = {
 *
 *     - <a href="base.html"> base_directory</a>: "src",
 *
 *     - <a href="srcfiles.html"> files</a>:[...],
 *
 *     - <a href="target.html"> target</a>:[ "c55s", "c55l"],
 *
 *     - <a href="cmodel.html"> cmodel</a>: true,
 *
 *     - <a href="flags.html"> compiler_flags</a>: "default-size",
 *
 *     - <a href="defs.html"> def_flags</a>: " -dTEST"
 *
 *    }; <BR>
 *
 *  <a href="exetarget.html"> Package.exeTarget</a>[..] = {
 *
 *     - <a href="baseexe.html"> base_directory</a>: "lnkr/test",
 *
 *     - <a href="nameexe.html"> name</a>:"test_rel_c5510",
 *
 *     - <a href="target.html"> target</a>:[ "c55s", "c55l"],
 *
 *     - <a href="platform.html"> platform</a>: "ti.sim.c55x",
 *
 *     - <a href="linktemplate.html"> linkTemplate</a>: "test_rel_c55x.xdt",
 *
  *
 *    }; <BR>
 *
 * <a href="packageargs.html">Package.args </a>[..]=
 * {
 *   - <a href="value.html"> value</a>:"SAMPLE",
 *
 *   - <a href="action.html"> action</a>: function()
 *   { <BR>
 *      /* Statement of Actions*\/<BR>
 *      ...............<BR>
 *      ...............<BR>
 *   },
 *
 *  - <a href="usage.html"> usageComment </a>: "Deliver Sample Code",
 *
 *  - <a href="type.html"> type </a>: "N"
 *
 * };<BR>
 *
 * <a href="archivefiles.html">Package.archiveFiles </a>[...]=
 * {
 *     - <a href="base.html"> base_directory</a>: "src",
 *
 *     -  <a href="filesarch.html"> files</a>:[...],
 *
 *     - <a href="target.html"> target</a>:[ "c55s", "c55l"],
 *
 *     -  <a href="deliverytype.html"> delivery_type</a>:"src",
 *
 * };<BR>
 *
 *
 * /* Set up the target architecture *\/<BR>
 *  <a href="targets.html">Package.targets </a> = [C54, C54_far, C55,C55_large, C64, C64_big_endian, C64P, C64P_big_endian];
 *
 *
 *    /* Include custom makefile to generate doxygen documents *\/<BR>
 *  <a href="include.html">Package.includeMake</a>("Makedocs.mk");
 *
 *  /* Parse XDC Arguments *\/<BR>
 *  <a href="parse.html">Package.parseArgs</a>(arguments);
 *
 *  /* Create Executables *\/<BR>
 *  <a href="exe.html">Package.createExe</a>();
 *
 *  /* Create Archive  *\/<BR>
 *  <a href="archive.html"> Package.createArchive</a>();
 *
 *  /* Clean Package  *\/<BR>
 *  <a href="clean.html"> Package.packageClean</a>();
 *
 *  /* nothing past this point *\/
 *   </CODE>
 *
 *
 *
 *
 *   @page CLEARCASE Clearcase Generation Scripts
 *
 *    - <a href="configspec.html"> configspec.clearcase</a>
 *
 *    - <a href="mcspec.html"> mCspec.txt </a>
 *
 *    - <a href="dcspec.html"> dcSpec.txt </a>
 *
 *    - <a href="icspec.html"> icSpec.txt </a>
 *
 *
 *
 *
 *   @page RELNOTES Release Notes Generation Script
 *
 *   @section desc Description
 *    The release note generation script generates new release notes from the header file <b> release.h </b>.
 *    The old release notes will be moved to the <b> docs/relnotes_archive </b> directory.
 *
 *   @section location Location
 *    <b> ti\\mas\\swtools\\ </b>
 *
 *   @section scriptname Script Name
 *    <b> release.js </b>
 *
 *   @section usage Usage
 *
 *   The following lines needs to be added to <b> Makedocs.mk </b> file for generating release notes:
 *<code>
 @verbatim
 RELEASE_DOC=./docs/doxygen/html/index.html

 releasenotes : $(RELEASE_DOC)

 $(RELEASE_DOC): ./docs/doxygen/release.h
    -@echo generating Release Notes ...
    if test ! -d ./docs/doxygen/html; then mkdir ./docs/doxygen/html; fi
    cp $(TI_DOXYGEN_TEMPLATES)/*.* ./docs/doxygen/html
    doxygen ../swtools/docs/doxygen/releaseDoxyfile
    @xs -f ../swtools/release.js
 @endverbatim
 *</code>

 *
 *
 *    @section requirement Requirement
 *
 *    -# The Component package should be built before executing the script.
 *    -# Clearcase permission required.
 *
 *
 *
 *   @page LABEL Labeling Script
 *
 *   @section desc Description
 *    The labeling script should be used for releasing any package. The label name is derived from the generated XML file of the package.
 *
 *   @section location Location
 *    <b> ti\\mas\\swtools\\ </b>
 *
 *   @section scriptname Script Name
 *    <b> mklabelcomp.js </b>
 *
 *   @section usage Usage
 *
 *    <b> xs -f mklabelcomp.js COMP_ROOT=\\dsps_gtmas COMPONENT=ti.mas.xxx LABEL_PREFIX= DEV/FCHK </b> <BR>
 *
 *    COMP_ROOT is the VOB name. <BR>
 *    COMPONENT should be specified as ti.mas.xxx. <BR>
 *    LABEL_PREFIX could be either DEV or CHK. <BR>
 *
 *    @section requirement Requirement
 *
 *    -# All the files should be checkin else error will be thrown.
 *    -# The package should be build before executing the labeling script.The version information of the package is derived from the generated xml file.
 *    -# The labeling will not occur if the label name is already existing.
 *
 *
 *
 *
 *   @page CONFIGSPEC Generate configspec.clearcase
 *   @section desc Description
 *    The configspec.clearcase should be generated for all packages. Stores clearcase information.
 *
 *   @section location Location
 *    <b> ti\\mas\\swtools\\ </b>
 *
 *   @section scriptname Script Name
 *    <b> Ccase.js </b>
 *
 *   @section usage Usage
 *
 *    <b> xs -f Ccase.js ti.mas.xxx </b> <BR>
 *
 *     where <b> ti.mas.xxx </b> is Component name <BR>
 *
 *    @section requirement Requirement
 *
 *    -# The Component package and the dependent packages should be built before executing the script.
 *    -# If the component has test package, it should also be built.
 *    -# Re-run the script after fixing the compatibility error.
 *
 *   @page MCSPEC Generate mCspec.txt
 *   @section desc Description
 *    The mCspec.txt( Maintainance Clearcase Config Spec) should be generated for all packages. Stores Clearcase information to create maintainainace branch.
 *
 *
 *   @section location Location
 *    <b> ti\\mas\\swtools\\ </b>
 *
 *   @section scriptname Script Name
 *    <b> mcspecGen.js </b>
 *
 *   @section usage Usage
 *
 *    <b> xs -f mcspecGen.js ti.mas.xxx </b> <BR>
 *
 *     where <b> ti.mas.xxx </b> is Component name <BR>
 *
 *    @section requirement Requirement
 *
 *    -# The Component package and the dependent packages should be built before executing the script.
 *    -# If the component has test package, it should also be built.
 *    -# <b> configspec.clearcase </b> should be generated before generating mcSpec.txt.
 *    -# Re-run the script after fixing the compatibility error.
 *
 *   @page DCSPEC Generate dcSpec.txt
 *
 *   @section desc Description
 *    The dcSpec.txt( Development Clearcase Config Spec) should be generated for all packages. Stores Clearcase information to create development branch.
 *
 *   @section location Location
 *    <b> ti\\mas\\swtools\\ </b>
 *
 *   @section scriptname Script Name
 *    <b> dcspecGen.js </b>
 *
 *   @section usage Usage
 *
 *    <b> xs -f dcspecGen.js ti.mas.xxx </b> <BR>
 *
 *     where <b> ti.mas.xxx </b> is Component name <BR>
 *
 *    @section requirement Requirement
 *
 *    -# The Component package and the dependent packages should be built before executing the script.
 *    -# If the component has test package, it should also be built.
 *    -# <b> configspec.clearcase </b> should be generated before generating dcSpec.txt.
 *    -# Re-run the script after fixing the compatibility error.
 *
 *   @page ICSPEC Generate icSpec.txt
 *
 *   @section desc Description
 *    The icSpec.txt( Integration Clearcase Config Spec) needs to be provided for the components integrator. Stores Clearcase information to create Integration branch.
 *
 *   @section location Location
 *    <b> ti\\mas\\swtools\\ </b>
 *
 *   @section scriptname Script Name
 *    <b> icspecGen.js </b>
 *
 *   @section usage Usage
 *
 *    <b> xs -f icspecGen.js ti.mas.xxx ti.mas.yyy ti.mas.zzz.... </b> <BR>
 *
 *     where <b> ti.mas.xxx ti.mas.yyy ti.mas.zzz</b> is list of component for which integartion specs needs to be generated <BR>
 *
 *    @section requirement Requirement
 *
 *    -# The Component package and the dependent packages should be built before executing the script.
 *    -# If the component has test package, it should also be built.
 *    -# <b> configspec.clearcase </b> should be generated before generating icSpec.txt.
 *    -# Re-run the script after fixing the compatibility error.
 *
 *
 *
 *   @page COMMONCONF Common config.bld and cygwinxdc.bat
 *
 *   The swtools config.bld and cygwinxdc.bat files can be shared by other packages.
 *   The cygwinxdc.bat apart from configuring the tools configures the config.bld file to be used from swtools package.
 *   If package has its own config.bld, that will have prefernce over the swtools config.bld.
 *
 *
 *   @page NAME Package Name
 *
 *   @section description Description
 *
 *   This variable needs to be assigned to package name.
 *
 *   @section example Example
 *
 *   - For package ti.mas.xxx <BR>
 *      <CODE> Package.name="xxx"; </CODE>
 *
 *   - For package ti.mas.xxx.test <BR>
 *      <CODE> Package.name="xxx_test"; </CODE>
 *
 *   - For package ti.mas.iface.xxx <BR>
 *      <CODE> Package.name="iface_xxx"; </CODE>
 *
 *   @page PACKAGEFILES Package Source Files Array
 *
 *   @section description Description
 *
 *   All the C, Assembly and Linear Assembly source files required to create the library, need to be specified here.
 *   The source files could be grouped as below (but not limited to):
 *   - Target independent and target dependent source files.
 *   - Source files that require different optimizer flags. ( Optimized for speed vs Optimized for space )
 *   - C model source files.
 *   - Optional source files to be compiled based on command line XDCARGS.
 *   - Physical location of source files.
 *   - Different Macros for source files.
 *
 *   The groups could be specified based on user defined identifier.
 *
 *   Files array has following field:
 *
 *     - <a href="base.html"> base_directory</a> (optional)
 *     - <a href="srcfiles.html"> files</a>
 *     - <a href="target.html"> target</a> (optional)
 *     - <a href="cmodel.html"> cmodel</a> (optional)
 *     - <a href="flags.html"> compiler_flags</a> (optional)
 *     - <a href="defs.html"> def_flags</a> (optional)
 *
 *   @section example Example
 *   <Code>
 *   @verbatim
    Package.files["commonCsrc"]= {

      base_directory: "src",

      files:[
             "util.c",
             "circbuf.c",
             "muatbl.c",
            ]
     }

    Package.files["commonCsrcSize"]= {
      base_directory: "src",

      files:[
             "wng.c",
             "png.c",
             "ecoXdaisXlat.c"
            ],

     compiler_flags:"default-size"
     }

    Package.files["C54AsmFiles"]= {

     base_directory: "src/c54",

     target: [ "c54n","c54f"],

     files:[
            "utildb2lin.s",
            "utillin2db.s",
            "utilnum.s",
            "muacomp.s",
            "wngnum.s",
            "cbbufcon.s",
            "pkt.c"
         ]
    }

    Package.files["C55CmodelFiles"]= {

     base_directory: "src",

     target: [ "c55s", "c55l"],

     files:[
           "utillin2db.c",
           "utildb2lin.c",
           "utilnum.c",
           "cbbufcon.c",
           "muacomp.c",
           "wngnum.c"
         ],

    cmodel: true,

    def_flags: " -dutlDotSat_Cm "


   }
   @endverbatim
 *  </CODE>
 *
 * @page BASE base_directory
 *
 * @section description Description
 *
 * This is an optional field. This needs to be specified relative to base of the component directory to reference the source files .
 *
 * If not defined all the files specified are referenced from base of the component directory.
 *
 * @section example Example
 *
 * - To reference C64x+ specific source files <BR>
 * <CODE>
 *  base_directory: "src/c64P"
 * </CODE>

 * @page BASEEXE base_directory
 *
 * @section description Description
 *
 * This is an optional field. This needs to be specified relative to base of the component directory to reference the linker template and linker command file.
 *
 * If not defined all the files specified are referenced from lnkr/<target>, where <target> is same as <a href="targetexe.html"> target </a> of the executable.
 *
 * @section example Example
 *
 * - To reference linker template and linker command file from C55x directory <BR>
 * <CODE>
 *  base_directory: "lnkr/c55x"
 * </CODE>
 *
 *
 * @page SRCFILES files
 *
 * @section description Description
 *
 * All the source files belonging to the array need to be specified here.
 *
 * @section example Example
 *
 * - To reference common c source files from \e src directory specified by \e base_directory <BR>
 * <CODE>
 *  @verbatim
    files:[
           "utillin2db.c",
           "utildb2lin.c",
           "utilnum.c",
           "cbbufcon.c",
           "muacomp.c",
           "wngnum.c"
         ],
  @endverbatim
 * </CODE>
 *
 * @page TARGET Target
 *
 * @section description Description
 *
 * Target specific source files are identified through this field. This is optional field if the source files in the array is target independent.
 *
 *
 * <TABLE align=center>
 * <TR>
 * <TD><B>Valid Values</B></TD>
 * <TD><B>Comments</B></TD>
 * </TR>
 * <TR>
 * <TD>"all"</TD>
 * <TD><B> Default Value </B>. Target Independent. Compiled for all targets</TD>
 * </TR>
 * <TR>
 * <TD>"c54n"</TD>
 * <TD>Target Dependent. Compiled for C54x Near target only</TD>
 * </TR>
 * <TR>
 * <TD>"c54f"</TD>
 * <TD>Target Dependent. Compiled for C54x Far target only</TD>
 * </TR>
 * <TR>
 * <TD>"c55l"</TD>
 * <TD>Target Dependent. Compiled for C55x Large target only</TD>
 * </TR>
 * <TR>
 * <TD>"c55s"</TD>
 * <TD>Target Dependent. Compiled for C55x Small target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64le"</TD>
 * <TD>Target Dependent. Compiled for C64x Little Endian target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64be"</TD>
 * <TD>Target Dependent. Compiled for C64x Big Endian target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64Ple"</TD>
 * <TD>Target Dependent. Compiled for C64x+ Little Endian target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64Pbe"</TD>
 * <TD>Target Dependent. Compiled for C64x+ Big Endian target only</TD>
 * </TR>
 * </TABLE>


 * @page TARGETEXE Target
 *
 * @section description Description
 *
 * This field specifies the target for which the executable specified in the Array will be created. This is mandatory field for exeTarget Array.
 *
 *
 * <TABLE align=center>
 * <TR>
 * <TD><B>Valid Values</B></TD>
 * <TD><B>Comments</B></TD>
 * </TR>
 * <TR>
 * <TD>"c54n"</TD>
 * <TD> Executable created for C54x Near target only</TD>
 * </TR>
 * <TR>
 * <TD>"c54f"</TD>
 * <TD>Executable created for C54x Far target only</TD>
 * </TR>
 * <TR>
 * <TD>"c55l"</TD>
 * <TD>Executable created for C55x Large target only</TD>
 * </TR>
 * <TR>
 * <TD>"c55s"</TD>
 * <TD>Executable created for C55x Small target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64le"</TD>
 * <TD>Executable created for C64x Little Endian target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64be"</TD>
 * <TD>Executable created for C64x Big Endian target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64Ple"</TD>
 * <TD>Executable created for C64x+ Little Endian target only</TD>
 * </TR>
 * <TR>
 * <TD>"c64Pbe"</TD>
 * <TD>Executable created for C64x+ Big Endian target only</TD>
 * </TR>
 * </TABLE>
 *
 *
 * @section example Example
 *
 * - Compile for all C54x and C55x targets <BR>
 * <CODE>
 *  target: ["c54n", "c54f", "c55l", "c55s"]
 * </CODE>
 *
 * @page CMODEL cmodel
 *
 * @section description Description
 *
 * If set to true the source files in this array will be used to create c-model library. This field is optional for non-cmodel source files.
 *
 * <TABLE align=center>
 * <TR>
 * <TD><B>Valid Values</B></TD>
 * <TD><B>Comments</B></TD>
 * </TR>
 * <TR>
 * <TD>false</TD>
 * <TD><B> Default Value. </B>  Compiled for release library</TD>
 * </TR>
 * <TR>
 * <TD>true</TD>
 * <TD> Compiled for c-model library</TD>
 * </TR>
 * </TABLE>
 *
 *
 * @section example Example
 *   - Compile for C-model library <BR>
 * <CODE>
 *  cmodel:true
 * </CODE>
 *
 * @page FLAGS compiler_flags
 *
 * @section description Description
 *
 * The files will be compiled based on the compiler flags specified by this field. There are two customized set of flags under <b>default-speed</b> and <b> default-size </b> category for all targets.
 * User can specify its own flags incase the requirement is not met with the customized set. This is optional field if the files needs to be complied for speed with <b>default-speed</b> flags.
 *
 * <TABLE align=center>
 * <TR>
 * <TD><B>Valid Values</B></TD>
 * <TD><B>Comments</B></TD>
 * </TR>
 * <TR>
 * <TD>default-speed</TD>
 * <TD><B> Default Value. </B>  Compile with customized speed flags for respective targets</TD>
 * </TR>
 * <TR>
 * <TD>default-size</TD>
 * <TD> Compile with customized speed flags for respective targets</TD>
 * </TR>
 * <TR>
 * <TD>" list of user specified flags "</TD>
 * <TD> Compile with user specified flags for respective targets</TD>
 * </TR>
 * </TABLE>
 *
 *
 * @section example Example
 *
 * - Compile with defaults size flags <BR>
 * <CODE>
 *  compiler_flags:"default-size",
 * </CODE>
 *
 * - Compile with specific c64x flags <BR>
 * <CODE>
 *   compiler_flags:" -pdsw994 -pdsw262 -pds77 -pden -pds232 --consultant -mw -os -g -as -ss -mi10000 "
 *  </CODE>
 *
 *
 * @page DEFS def_flags
 *
 * @section description Description
 *
 * Any library specific macros needs to be specified here. This is optional field if there are no macros.
 *
 * @section example Example
 *
 *  - Compile source code with following macros <BR>
 * <CODE>
 *      def_flags: "  -dV17 -dHALF_DUPLEX "
 * </CODE>
 *
 * @page ARCHIVEFILES Archive files Array
 *
 * @section description Description
 *
 * This array contains list of files to be archived. Files that doesn't belong to default list archived by <a href="archive.html">Package.createArchive() </a> need to be specified here.
 * If the default option of <a href="archive.html">Package.createArchive() </a> is not opted than all the header files and other archive file need to be specified here.
 *
 * This Array has the following fields:
 *     - <a href="base.html"> base_directory</a> (optional)
 *     - <a href="filesarch.html"> files</a>
 *     - <a href="target.html"> target</a> (optional)
 *     - <a href="deliverytype.html"> delivery_type</a> (optional)
 *
 * @section example Example
 * <CODE>
  @verbatim
  /* Archive files for object delivery *\/
  Package.archiveFiles["default"]= {
       files: [
          "src",
          "Version.xdt",
          "cpytools.pl",
          "Ccase.js",
          "iCcase.js",
          "Ccase.xdc",
          "commonBld.xdc",
          "commonBld.xs"
          ]
 }

  /* Archive files for source delivery *\/
  Package.archiveOtherFiles["src"] =
  {
    base_directory: "docs/doxygen"

    files: [
            "TYPES.chm"
           ]

    delivery_type: "src"
  }

  /* Archive files for C64x source delivery only *\/
  Package.archiveOtherFiles["c64x"] =
  {
    base_directory: "src/c64"

    target: [ "c64le", "c64be", "c64Ple", "c64Pbe" ]

    files: [
            "fndport.h"
           ]

    delivery_type: "src"
  }

  @endverbatim
   </CODE>
 *
 * @page FILESARCH files
 *
 * @section description Description
 *
 * List of files belonging to the array needs to be specified here.
 *
 * @section example Example
 *
 * - List of files to archive with \e base_directory undefined <BR>
 * <CODE>
 *  @verbatim
      files: [
          "src",
          "Version.xdt",
          "cpytools.pl",
          "Ccase.js",
          "iCcase.js",
          "Ccase.xdc",
          "commonBld.xdc",
          "commonBld.xs"
          ]
  @endverbatim
 * </CODE>
 * @page DELIVERYTYPE delivery_type
 *
 * @section description Description
 *
 * Field to differentiate the archiving of files based on \e source or \e object delivery. This field is option if the delivery type is \e object.
 *
 * <TABLE align=center>
 * <TR>
 * <TD><B>Valid Values</B></TD>
 * <TD><B>Comments</B></TD>
 * </TR>
 * <TR>
 * <TD> obj </TD>
 * <TD><B> Default Value. </B> Archive files in this array for both object and source release </TD>
 * </TR>
 * <TR>
 * <TD> src </TD>
 * <TD> Archive files in this array for source release only</TD>
 * </TR>
 * </TABLE>
 *
 * @section example Example
 *
 * - Archive files for source delivery <BR>
 * <CODE>
 *  delivery_type: "src"
 * </CODE>
 *
 *
 * @page PACKAGEARGS Package Specific Arguments Array
 *
 * @section description Description
 *
 * This array contains package specfic arguments. The contents of the array is used for displaying help usage, parsing XDCARGS and taking action if the argument is present in the list.
 *
 * This Array has the following fields:
 *     - <a href="value.html">  value</a>
 *     - <a href="action.html"> action</a>
 *     - <a href="usage.html">  usage</a>
 *     - <a href="type.html">   type</a> (optional)
 *
 * @section example Example
 * <CODE>
  @verbatim
  /* Package Specific "cycleprof" Argument*\/
    Package.args["cycleprof"]=
   {
       value:"cycleprof ",

       action: function()
       {
           files["commontestsrc"].def_flags = " -dUSE_CACHE -dPROFILE_CYCLES ";
       },

      usageComment: "Profile cycles for fract"

  }

  @endverbatim
  </CODE>
 *
 * @page VALUE Argument Value
 *
 * @section description Description
 *
 * Package Specific Argument value needs to be specified here.
 *
 * @section example Example
 *
 * - "cycleprof" Argument for profiling cycles.<BR>
 * <CODE>
 *  @verbatim
     value:"cycleprof"
  @endverbatim
 * </CODE>

 * @page ACTION Action
 *
 * @section description Description
 *
 * Specify funtion that will be called if the Argument in the Array is present in XDCARGS list.
 *
 * @section example Example
 *
 * - Add Macros if "cycleprof" is parsed <BR>
 * <CODE>
 *  @verbatim
    action: function()
       {
           files["commontestsrc"].defs = " -dUSE_CACHE -dPROFILE_CYCLES ";
       },
  @endverbatim
 * </CODE>
 *
 * @page USAGE Help Usage
 *
 * @section description Description
 *
 * Specify Help usage for the Argument in the Array.
 *
 * @section example Example
 *
 * - Add help usage for "cycleprof"  <BR>
 * <CODE>
 *  @verbatim
    usageComment: "Profile cycles for fract"
    @endverbatim
 * </CODE>

 * @page TYPE Help Type
 *
 * @section description Description
 *
 * Specify Help Type for the Argument in the Array. This is optional parameter and if not specified is defaulted to non-numeric.
 *
 * @section example Example
 *
 * - The Argument is of type Numeric <BR>
 * <CODE>
 *  @verbatim
    type:"N"
  @endverbatim
 * </CODE>

 * @page TARGETS Supported Targets
 *
 * @section description Description
 *
 * Provide the list of supported targets for this package.

 * <TABLE align=center>
 * <TR>
 * <TD><B>Valid Values</B></TD>
 * <TD><B>Comments</B></TD>
 * </TR>
 * <TR>
 * <TD>C54</TD>
 * <TD>C54x Near Memory Target Supported</TD>
 * </TR>
 * <TR>
 * <TD>C54_far</TD>
 * <TD>C54x Far Memory Target Supported</TD>
 * </TR>
 * <TR>
 * <TD>C55</TD>
 * <TD>C55x Small Memory Target Supported</TD>
 * </TR>
 * <TR>
 * <TD>C55_large</TD>
 * <TD>C55x Large Memory Target Supported</TD>
 * </TR>
 * <TR>
 * <TD>C64</TD>
 * <TD>C64x Little Endian Target Supported</TD>
 * </TR>
 * <TR>
 * <TD>C64_big_endian</TD>
 * <TD>C64x Big Endian Target Supported</TD>
 * </TR>
 * <TR>
 * <TD>C64P</TD>
 * <TD>C64x+ Little Endian Target Supported</TD>
 * </TR>
 * <TR>
 * <TD>C64P_big_endian</TD>
 * <TD>C64x+ Big Endian Target Supported</TD>
 * </TR>
 * </TABLE>
 *
 * @section example Example
 *
 * - C64x and C64x+ targets are supported <BR>
 * <CODE>
 *  @verbatim
   /* Set up the target architecture *\/
  Package.targets = [C64, C64_big_endian, C64P, C64P_big_endian];

  @endverbatim
 * </CODE>
 *
 *
 * @page VERSION Package Version
 *
 * @section description Description
 *
 * Specify Version of the package. The Package Version is of type <b> M.m.x.p.</b> Where <BR>
 *  <b> M </b> is a Major number,<BR>
 *  <b> m </b> is minor number,<BR>
 *  <b>x</b> is vertical number and <BR>
 *  <b>p</b> is a single digit patch number <BR>
 *
 * The Version needs to be specified for all packages except test packages.
 *
 * @section example Example
 *
 * - Specify Version of the Package <BR>
 * <CODE>
 *  @verbatim
    Package.version = [3,1,0,0];
  @endverbatim
 * </CODE>
 *
 * @page CREATEVERSION Create Version
 *
 * @section description Description
 *
 * This function creates <b> version.h </b> from the <b> version.xdt </b> template defined in swtools package.
 *
 * This function needs to be called for all packages except test packages.
 *
 * @section example Example
 *
 * - Create Version File <BR>
 * <CODE>
 *  @verbatim
    Package.createVersion();
  @endverbatim
 * </CODE>

 * @page INCLUDE Add GNU Makefile
 *
 * @section description Description
 *
 * This function adds the GNU makefile at the start of generated makefile. This allows one to extend the build
 * environment using any facility available to GNU make. The GNU makefile is provided to the function as argument.
 *
 * This function is generally called to include makefile for generating Doxygen for the package.
 *
 * @section example Example
 *
 * - Create Version File <BR>
 * <CODE>
 *  @verbatim
    /* Include custom makefile to generate doxygen documents *\/
    Package.includeMake("Makedocs.mk");
    @endverbatim
 * </CODE>
 *
 * @page PARSE Parse XDCARGS
 *
 * @section description Description
 *
 * This function parses XDCARGS provided during build.
 *
 * @section example Example
 *
 * - Parse XDCARGS <BR>
 * <CODE>
 *  @verbatim
    /* Parse XDC Arguments *\/
    Package.parseArgs(arguments);
    @endverbatim
 * </CODE>

 * @page LIB Generate Library
 *
 * @section description Description
 *
 * This function generates library. The library name to be generated need to be passed as argument to the function.
 * This function creates:
 *  - xxx_c.a*  Library for all C code
 *  - xxx_a.a*  Library for all target specific code.
 *  - xxx_cm.a* Library for all C-model code.
 *
 * @section example Example
 *
 * - Create Library<BR>
 * <CODE>
 *  @verbatim
   /* Create Library *\/
   Package.createLib(Package.name);
   @endverbatim
 * </CODE>

 * @page EXE Generate Executable
 *
 * @section description Description
 *
 * This function generates executable. The executable name is same as specified in name field of the executable array.
 *
 * @section example Example
 *
 * - Create Executable<BR>
 * <CODE>
 *  @verbatim
   /* Create Executable *\/
   Package.createExe();
   @endverbatim
 * </CODE>
 *
 * @page ARCHIVE Archive function
 *
 * @section description Description
 *
 * This function archives the files for both object and source release. <b> Package.archiveTypeDefault </b> controls the archive type.
 * If not defined or defined <b>true</b> default archive is created
 * The default Archive Contains:
    - The API header file for Object release.
    - All target non-specific header files and target specific header files for the source release based on the release target.
    - Clearcase Artifacts( configspec.clearcase & mCspec.txt )
    - Doxygen API document for object release and API and Source documnt for source release (if exists).
    - Release Notes.
    - XDC build files for the source delivery.
 *
 * Package.archiveTypeDefault needs to be set to false for non-default archive. In this case package developer needs to add all the files to be archived in array <a href="packageargs.html">Package.args </a>.
 *
 * @section example Example
 *
 * - Create non-Default Archive <BR>
 * <CODE>
 *  @verbatim
   Package.archiveTypeDefault= false;
   /* Create Archive *\/
   Package.createArchive();

  @endverbatim
 * </CODE>

 * @page CLEAN Package Clean
 *
 * @section description Description
 *
 * This function deletes all the generated XDC files, when <b> xdc clean </b> is called.
 *
 * @section example Example
 *
 * - Clean Package <BR>
 * <CODE>
 *  @verbatim
   /* Clean Package *\/
   Package.packageClean();

  @endverbatim
 * </CODE>

 *   @page EXETARGET Executable Target Array
 *
 *   @section description Description
 *
 *   This array list all the executables for various targets that will be created
 *
 *   Files array has following field:
 *
 *     - <a href="baseexe.html"> base_directory</a> (optional)
 *     - <a href="nameexe.html"> name</a>
 *     - <a href="targetexe.html"> target</a>
 *     - <a href="platform.html"> platform</a> (optional)
 *     - <a href="linktemplate.html"> linktemplate</a> (optional)
 *
 *   @section example Example
 *   <Code>
 *   @verbatim
     Package.exeTarget["c54n"] =
     {
        target:  "c54n",

        name:  "test_rel_c54x"

     };

   @endverbatim
 *  </CODE>

 *   @page NAMEEXE Executable Target Name
 *
 *   @section description Description
 *
 *   This field list the executable name that will be created.
 *
 *
 *   @section example Example
 *   <Code>
 *   @verbatim
        name:  "test_rel_c5510"
     @endverbatim
 *  </CODE>


 *   @page PLATFORM Platform
 *
 *   @section description Description
 *
 *   This field list the platform that will be used to run the executable.This is optional field and if not specified simulators of respective targets will be used.
 *
 *
 *
 *   @section example Example
 *   <Code>
 *   @verbatim
        platform:  "ti.platforms.dsk5510"
     @endverbatim
 *  </CODE>

 *   @page LINKTEMPLATE Link Template
 *
 *   @section description Description
 *
 *   This field is optional and is specified only if the link template name is different than <a href="nameexe.html">executable name</a>.xdt.
 *
 *
 *   @section example Example
 *   <Code>
 *   @verbatim
        linktemplate:  "test_release_debug.xdt"
     @endverbatim
 *  </CODE>



 */



/**
 * @page Revision History
 * <center> <B> Revision History </B> </center>
 *
 * <TABLE align=center>
 * <TR>
 * <TD><B>Version</B></TD>
 * <TD><B>Comments</B></TD>
 * </TR>
 * <TR>
 * <TD>1.0.0.0</TD>
 * <TD>Initial Version</TD>
 * </TR>
 * </TABLE>
 */

/**
 * @page Disclaimer
 *<center> <B>IMPORTANT NOTICE </B> </center>
 * Texas Instruments Incorporated and its subsidiaries (TI) reserve the right
 * to make corrections, modifications, enhancements, improvements, and other
 * changes to its products and services at any time and to discontinue any
 * product or service without notice. Customers should obtain the latest
 * relevant information before placing orders and should verify that such
 * information is current and complete. All products are sold subject to TIs
 * terms and conditions of sale supplied at the time of order acknowledgment.
 *
 * TI warrants performance of its hardware products to the specifications
 * applicable at the time of sale in accordance with TIs standard warranty.
 * Testing and other quality control techniques are used to the extent TI
 * deems necessary to support this warranty. Except where mandated by
 * government requirements, testing of all parameters of each product is not
 * necessarily performed.
 *
 * TI assumes no liability for applications assistance or customer product
 * design. Customers are responsible for their products and applications
 * using TI components. To minimize the risks associated with customer
 * products and applications, customers should provide adequate design and
 * operating safeguards.
 *
 * TI does not warrant or represent that any license, either express or
 * implied, is granted under any TI patent right, copyright, mask work right,
 * or other TI intellectual property right relating to any combination,
 * machine, or process in which TI products or services are used. Information
 * published by TI regarding third-party products or services does not
 * constitute a license from TI to use such products or services or a warranty
 * or endorsement thereof. Use of such information may require a license from a
 * third party under the patents or other intellectual property of the third
 * party, or a license from TI under the patents or other intellectual property
 * of TI.
 *
 * Reproduction of information in TI data books or data sheets is permissible
 * only if reproduction is without alteration and is accompanied by all
 * associated warranties, conditions, limitations, and notices. Reproduction
 * of this information with alteration is an unfair and deceptive business
 * practice. TI is not responsible or liable for such altered documentation.
 *
 * Resale of TI products or services with statements different from or beyond
 * the parameters stated by TI for that product or service voids all express
 * and any implied warranties for the associated TI product or service and is
 * an unfair and deceptive business practice. TI is not responsible or liable
 * for any such statements.
 *
 *
 *
 *
 * Mailing Address: <BR>
 * Texas Instruments <BR>
 * Post Office Box 655303 <BR>
 * Dallas, Texas 75265 <BR>
 *
 *
 *
 * Copyright  2006 Texas Instruments Incorporated.  All rights reserved.
 *
 * Information in this document is subject to change without notice.
 * Texas Instruments may have pending patent applications, trademarks,
 * copyrights, or other intellectual property rights covering matter in this
 * document.  The furnishing of this document is given for usage with Texas
 * Instruments products only and does not give you any license to the
 * intellectual property that might be contained within this document.
 * Texas Instruments makes no implied or expressed warranties in this document
 * and is not responsible for the products based from this document.
 *
 *
 */

