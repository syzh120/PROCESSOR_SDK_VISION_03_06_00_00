/* 
 *  Copyright (c) 2012-2016 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
var cap = xdc.loadCapsule("ITarget.xs");

function init()
{
    cap._init(this);

    var ma = this.$modules;
    var iarTargets = xdc.loadPackage('iar.targets.msp430');

    for (var i = 0; i < ma.length; i++) {
        if (ma[i] instanceof iarTargets.ITarget.Module) {
            var targ = iarTargets.ITarget.Module(ma[i]);

            /* add .s<suffix> to list of recognized extensions */
            var ext = ".s" + targ.suffix;
            targ.extensions.$putHead(ext,new xdc.om['xdc.bld.ITarget.Extension'](
                {
                    suf: ext,
                    typ: "asm"
                }
            ));
        }
    }
}
/*
 *  @(#) iar.targets.msp430; 1, 0, 0,0; 10-21-2016 18:16:51; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

