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
 *  ======== ViewInfo ========
 */
package xdc.rov

/*!
 *  ======== ViewInfo ========
 *  Describes the ROV views supported by a particular module.
 */
@Facet metaonly module ViewInfo {
    /*!
     *  ======== ViewType ========
     *  ROV view type
     *
     *  @p(dlist)
     *      - INSTANCE
     *          basic instance information (one row per instance).  The view
     *          init function is passed two arguments: (1) an instance of the
     *          view structure, and (2) the instance state structure of the
     *          instance to view.
     *
     *      - INSTANCE_DATA
     *          instance-specific data tables (many rows per instance).  The
     *          view init function is passed two arguments:(1) an instance of
     *          the xdc.rov.Program.InstDataView structure, and (2) an instance
     *          state structure for the instance to view.
     *
     *      - MODULE
     *          basic module information (one row per module).  The view
     *          init function is passed two arguments: (1) an instance of the
     *          view structure, and (2) the module state structure of the
     *          module to view.
     *
     *      - MODULE_DATA
     *          module-specific data tables (many rows per module).  The
     *          view init function is passed one argument: a
     *          Program.ModDataView structure.
     *
     *      - RAW
     *         This is a reserved view type used by ROV to display raw data.
     *
     *      - TREE_TABLE
     *         The view init function is passed no arguments and is expected
     *         to return a new initialized xdc.rov.Program.TreeNode structure
     *         or `null` in the event that there is nothing to display.
     *
     *      - TREE
     *         The view init function is passed no arguments and is expected
     *         to return a new initialized JavaScript hash table or `null`
     *         in the event that there is nothing to display.
     *  @p
     */
    metaonly enum ViewType {
        INSTANCE,
        MODULE,
        INSTANCE_DATA,
        MODULE_DATA,
        RAW,
        TREE_TABLE,
        TREE
    }
    
    /*!
     *  ======== View ========
     *  ROV View descriptor
     *
     *  @field(type)          the view type which control the type of arguments
     *                        passed to the `viewInitFxn`
     *  @field(viewInitFxn)   the name of a function that converts raw target
     *                        data into a human readable "view structure".
     *                        This name is the name of a metaonly function
     *                        defined in the module's `.xs` file.
     *  @field(structName)    the name of the view structure populated by
     *                        the `viewInitFxn`.  This name is a name defined
     *                        the module's `.xdc` file.
     */
    metaonly struct View {
        ViewType type;
        String   viewInitFxn;
        String   structName;
    }
    
instance:
    
    /*!
     *  ======== viewMap ========
     *  Specifies all of the ROV views for the module
     *
     *  Maps module-specific view names to an appropriate View descriptor.
     */
    metaonly config View viewMap[string];

    /*!
     *  ======== showRawTab ========
     *  Control whether the "raw view" is available
     */
    metaonly config Bool showRawTab = true;

}
/*
 *  @(#) xdc.rov; 1, 0, 1,0; 7-26-2016 11:45:47; /db/ztree/library/trees/xdc/xdc-B21/src/packages/
 */

