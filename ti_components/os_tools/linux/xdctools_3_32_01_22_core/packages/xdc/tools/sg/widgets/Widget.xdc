/* 
 *Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
metaonly interface Widget {
instance:
    create(Any parent);
    void dispose();

    Bool isValid();

    readonly config Any control;
};
/*
 *  @(#) xdc.tools.sg.widgets; 1,0,0,294; 7-13-2016 10:52:16; /db/ztree/library/trees/xdctools/xdctools-g12x/src/
 */

