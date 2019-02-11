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
 *  ======== SyncSemThread.xdc ========
 */

import xdc.runtime.knl.SemThread;

/*!
 *  ======== SyncSemThread ========
 *  A ISync implementation based on a SemThread. [EXPERIMENTAL]
 *
 *  This module implements the {@link ti.sdo.utils.ISync} interface
 *  using the {@link xdc.runtime.knl.SemThread} module.
 */
@InstanceInitError      /* instance initialization can fail */
@InstanceFinalize       /* instances require finalization */
@RomConsts

module SyncSemThread inherits xdc.runtime.knl.ISync
{

internal:  /* not for client use */

    struct Instance_State {
        SemThread.Handle    semThread;
    };
}
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,0; 7-26-2016 11:46:39; /db/ztree/library/trees/xdc/xdc-B21/src/packages/
 */

