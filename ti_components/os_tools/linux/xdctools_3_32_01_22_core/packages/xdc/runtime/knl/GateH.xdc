/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved.
 *  This program and the accompanying materials are made available under the
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== GateH.xdc ========
 */

import xdc.runtime.IGateProvider;

/*!
 *  ======== GateH ========
 *  Provides APIs to protect critical sections when an IGate.Handle is
 *  available.
 *
 *  An application can isolate itself from IGate implementations by using
 *  this module. The application must first obtain an IGate.Handle.
 *  It can get such a handle by directly calling {@link GateThread#create} or
 *  {@link GateProcess#create}. Then the application can use the generic
 *  APIs provided by this module.
 *
 *  The underlying gates are nexting in nature and users have to leave
 *  the gate as many times as they entered it.
 */
@DirectCall
@RomConsts

module GateH
{
    /*!
     *  Proxy used for optimization.
     *
     *  If ALL IGateProvider.Handles used by GateH are created using the same
     *  module (e.g GateProcess) then setting this Proxy to GateProcess and
     *  setting GateH.Proxy.abstractInstances$ = false, causes
     *  GateH APIs can have better performance.
     */
    proxy Proxy inherits IGateProvider;

    /*!
     * ======== enter ========
     * Enter a gate
     *
     * @param(hdl)    IGateProvider.Handle
     * @a(returns)    key
     */
    IArg enter(IGateProvider.Handle hdl);

    /*!
     * ======== leave ========
     * Leave a gate
     *
     * @param(hdl)    IGateProvider.Handle
     * @param(key)    key returned by enter();
     */
    Void leave(IGateProvider.Handle hdl, IArg key);
}
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-26-2016 11:46:36; /db/ztree/library/trees/xdc/xdc-B21/src/packages/
 */

