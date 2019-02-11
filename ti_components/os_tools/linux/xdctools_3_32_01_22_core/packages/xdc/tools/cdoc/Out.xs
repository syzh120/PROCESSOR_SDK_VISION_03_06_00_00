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
 *  ======== Stream ========
 */
function Stream( fname )
{
    var file = new java.io.File(fname);
    if (file.exists()) {
        file['delete']();
    }

    this.outstr = new Packages.xdc.services.global.Out(new java.io.FileOutputStream(file));
}

/*
 *  ======== Stream.close ========
 */
Stream.prototype.close = function()
{
    this.outstr.close();
};

/*
 *  ======== Stream.print ========
 */
Stream.prototype.print = function( o )
{
    this.outstr.print(o);
};

/*
 *  ======== Stream.printf ========
 */
Stream.prototype.printf = function( fmt, o0, o1, o2, o3 )
{
    this.outstr.doPrint(fmt, o0, o1, o2, o3);
};

/*
 *  ======== Stream.println ========
 */
Stream.prototype.println = function( s )
{
    this.outstr.println(s);
};

/*
 *  @(#) xdc.tools.cdoc; 1, 0, 0,0; 7-26-2016 11:49:19; /db/ztree/library/trees/xdc/xdc-B21/src/packages/
 */

