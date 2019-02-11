/* 
 *  Copyright (c) 2008-2015 Texas Instruments Incorporated
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

/*
 *  ======== C64.xdc ========
 */

/*!
 *  @_nodoc
 *  ======== C64 ========
 *  TI C64 default runtime model (little endian)
 */
metaonly module C64 inherits ti.targets.ITarget {
    override readonly config string name                 = "C64";
    override readonly config string suffix               = "64";
    override readonly config string isa                  = "64";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little"
    };
    override readonly config xdc.bld.ITarget.Module base = ti.targets.C64P;

    override readonly config string rts = "ti.targets.rts6000";
    override config string platform     = "ti.platforms.sim6xxx:TMS320C6416";

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["62"];

    override readonly config xdc.bld.ITarget2.Command ar = {
        cmd: "ar6x",
        opts: "rq"
    };

    override readonly config xdc.bld.ITarget2.Command cc = {
        cmd: "cl6x -c",
        opts: "-mv6400"
    };

    override readonly config xdc.bld.ITarget2.Command vers = {
        cmd: "cl6x",
        opts: "--compiler_revision"
    };

    override readonly config xdc.bld.ITarget2.Command asm = {
        cmd: "cl6x -c",
        opts: "-mv6400"
    };

    override readonly config xdc.bld.ITarget2.Command lnk = {
        cmd: "cl6x",
        opts: "-z"
    };

    /*!
     *  ======== asmOpts ========
     *  User configurable assembler options.
     *
     *  Defaults:
     *  @p(dlist)
     *      -`-qq`
     *          super quiet mode
     */
    override config xdc.bld.ITarget2.Options asmOpts = {
        prefix: "-qq",
        suffix: ""
    };

    /*!
     *  ======== ccOpts ========
     *  User configurable compiler options.
     *
     *  Defaults:
     *  @p(dlist)
     *      -`-qq`
     *          super quiet mode
     *      -`-pdsw225`
     *          generate a warning for implicitly declared functions; i.e.,
     *          functions without prototypes
     */
    override config xdc.bld.ITarget2.Options ccOpts = {
        prefix: "-qq -pdsw225",
        suffix: ""
    };

    override config string includeOpts = "-I$(rootDir)/include";

    final override readonly config string sectMap[string] =
        ti.targets.C64P.sectMap;

    final override readonly config Bool splitMap[string] =
        ti.targets.C64P.splitMap;

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = C64P.stdTypes;

    override readonly config Int bitsPerChar = C64P.bitsPerChar;
};
/*
 *  @(#) ti.targets; 1, 0, 3,0; 10-21-2016 18:16:52; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

