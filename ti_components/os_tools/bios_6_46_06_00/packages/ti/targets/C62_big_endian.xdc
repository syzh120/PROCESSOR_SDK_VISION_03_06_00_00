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
 *  ======== C62_big_endian.xdc ========
 *
 */

/*!
 *  ======== C62_big_endian ========
 *  @_nodoc
 *
 *  TI C62 big endian
 */
metaonly module C62_big_endian inherits ti.targets.ITarget {
    override readonly config string name            = "C62_big_endian";
    override readonly config string suffix          = "62e";
    override readonly config string isa             = "62";     
    override readonly config xdc.bld.ITarget.Model model = {endian: "big"};
    override readonly config xdc.bld.ITarget.Module base = ti.targets.C62;

    override readonly config string rts = "ti.targets.rts6000";
    override config string platform     = "ti.platforms.sim6xxx:TMS320C6211";

    override readonly config xdc.bld.ITarget2.Command ar = {
        cmd: "ar6x",
        opts: "rq"
    };

    override readonly config xdc.bld.ITarget2.Command cc = {
        cmd: "cl6x -c",
        opts: "-me"
    };

        override readonly config xdc.bld.ITarget2.Command vers = {
        cmd: "cl6x",
        opts: "--compiler_revision"
    };

    override readonly config xdc.bld.ITarget2.Command asm = {
        cmd: "cl6x -c",
        opts: "-me"
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
        ti.targets.C62.sectMap;

    final override readonly config Bool splitMap[string] =
        ti.targets.C62.splitMap;

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = C62.stdTypes;

    override readonly config Int bitsPerChar = C62.bitsPerChar;
};
/*
 *  @(#) ti.targets; 1, 0, 3,0; 10-21-2016 18:16:52; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

