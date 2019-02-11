/* 
 *  Copyright (c) 2008 Texas Instruments and others.
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
 *  ======== C67.xdc ========
 *
 */

/*!
 *  ======== C67 ========
 *  @_nodoc
 * 
 *  TI C67 default runtime model (little endian)
 */
metaonly module C67 inherits ti.targets.ITarget {
    override readonly config string name                 = "C67";
    override readonly config string suffix               = "67";
    override readonly config string isa                  = "67";        
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little"
    };
    override readonly config xdc.bld.ITarget.Module base = ti.targets.C62;

    override readonly config string rts = "ti.targets.rts6000";
    override config string platform     = "ti.platforms.sim6xxx:TMS320C6713";

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
        opts: "-mv6700"
    };

    override readonly config xdc.bld.ITarget2.Command vers = {
        cmd: "cl6x",
        opts: "--compiler_revision"
    };

    override readonly config xdc.bld.ITarget2.Command asm = {
        cmd: "cl6x -c",
        opts: "-mv6700"
    };

    override readonly config xdc.bld.ITarget2.Command lnk = {
        cmd: "lnk6x",
        opts: ""
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
}
/*
 *  @(#) ti.targets; 1, 0, 3,0; 10-21-2016 18:16:53; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

