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
 *  ======== C64T.xdc ========
 */

/*!
 *  @_nodoc
 *  ======== C64T ========
 *  TI C64T little endian (ELF)
 */
metaonly module C64T inherits ITarget {
    override readonly config string name                 = "C64T";
    override readonly config string suffix               = "e64T";
    override readonly config string isa                  = "64T";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little",
        shortEnums: false
    };
    override readonly config xdc.bld.ITarget.Module base = ti.targets.elf.C64P;

    override config string platform     = "ti.platforms.sdp4430";

    override readonly config xdc.bld.ITarget2.Command cc = {
        cmd: "cl6x -c",
        opts: "-mv=tesla --abi=eabi"
    };

    override readonly config xdc.bld.ITarget2.Command asm = {
        cmd: "cl6x -c",
        opts: "-mv=tesla --abi=eabi"
    };

    override readonly config Int bitsPerChar =
        ti.targets.elf.C64P.bitsPerChar;
}
/*
 *  @(#) ti.targets.elf; 1, 0, 0,0; 10-21-2016 18:16:56; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

