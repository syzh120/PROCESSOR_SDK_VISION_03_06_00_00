/*
 * Copyright (c) 2012-2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== ListMP.xdc ========
 *
 */

import xdc.runtime.Error;
import ti.sdo.utils.NameServer;

/*!
 *  ======== ListMP ========
 *  Shared memory linked list
 *
 *  @p(html)
 *  This module has a common header that can be found in the {@link ti.ipc}
 *  package.  Application code should include the common header file (not the
 *  RTSC-generated one):
 *
 *  <PRE>#include &lt;ti/ipc/ListMP.h&gt;</PRE>
 *
 *  The RTSC module must be used in the application's RTSC configuration file
 *  (.cfg):
 *
 *  <PRE>ListMP = xdc.useModule('ti.sdo.ipc.ListMP');</PRE>
 *
 *  Documentation for all runtime APIs, instance configuration parameters,
 *  error codes macros and type definitions available to the application
 *  integrator can be found in the
 *  <A HREF="../../../../doxygen/html/files.html">Doxygen documenation</A>
 *  for the IPC product.  However, the documentation presented on this page
 *  should be referred to for information specific to the RTSC module, such as
 *  module configuration, Errors, and Asserts.
 *  @p
 */
@InstanceInitError /* Initialization may throw errors */
@InstanceFinalize

module ListMP
{
    /*!
     *  ======== BasicView ========
     *  @_nodoc
     *  ROV view structure representing a ListMP instance.
     */
    metaonly struct BasicView {
        String      label;
        String      type;
        String      gate;
    }

    /*!
     *  ======== ElemView ========
     *  @_nodoc
     *  ROV view structure representing a single list element.
     */
    metaonly struct ElemView {
        Int        index;
        String     srPtr;
        String     addr;
    }

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo =
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Basic',
                    {
                        type: xdc.rov.ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitBasic',
                        structName: 'BasicView'
                    }
                ],
                ['Lists',
                    {
                        type: xdc.rov.ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitLists',
                        structName: 'ElemView'
                    }
                ],
            ]
        });

    /*!
     *  ======== maxRuntimeEntries ========
     *  Maximum number of ListMP's that can be dynamically created
     *  and added to the NameServer.
     */
    metaonly config UInt maxRuntimeEntries = NameServer.ALLOWGROWTH;

    /*!
     *  ======== maxNameLen ========
     *  Maximum length for names.
     */
    metaonly config UInt maxNameLen = 32;

    /*!
     *  ======== tableSection ========
     *  Section name is used to place the names table
     */
    metaonly config String tableSection = null;


instance:

    /*!
     *  ======== gate ========
     *  GateMP used for critical region management of the shared memory
     *
     *  Using the default value of NULL will result in the default GateMP
     *  being used for context protection.
     */
    config GateMP.Handle gate = null;

    /*! @_nodoc
     *  ======== openFlag ========
     *  Set to 'true' by the {@link #open}.
     */
    config Bool openFlag = false;

    /*! @_nodoc
     *  ======== sharedAddr ========
     *  Physical address of the shared memory
     *
     *  The shared memory that will be used for maintaining shared state
     *  information.  This is an optional parameter to create.  If value
     *  is null, then the shared memory for the new instance will be
     *  allocated from the heap in {@link #regionId}.
     */
    config Ptr sharedAddr = null;

    /*!
     *  ======== name ========
     *  Name of the instance
     *
     *  The name must be unique among all ListMP instances in the sytem.
     *  When using {@link #regionId} to create a new instance, the name must
     *  not be null.
     */
    config String name = null;

    /*!
     *  ======== regionId ========
     *  SharedRegion ID.
     *
     *  The ID corresponding to the index of the shared region in which this
     *  shared instance is to be placed.  This is used in create() only when
     *  {@link #name} is not null.
     */
    config UInt16 regionId = 0;

    /*! @_nodoc
     *  ======== metaListMP ========
     *  Used to store elem before the object is initialized.
     */
    metaonly config any metaListMP[];


internal:    /* not for client use */

    const UInt32 CREATED = 0x12181964;

    /*!
     *  ======== Elem ========
     *  Opaque ListMP element
     *
     *  A field of this type must be placed at the head of client structs.
     */
    @Opaque struct Elem {
        volatile SharedRegion.SRPtr next;       /* volatile for whole_program */
        volatile SharedRegion.SRPtr prev;       /* volatile for whole_program */
    };


    /*!
     *  ======== nameSrvPrms ========
     *  This Params object is used for temporary storage of the
     *  module wide parameters that are for setting the NameServer instance.
     */
    metaonly config NameServer.Params nameSrvPrms;

    /*!
     *  ======== elemClear ========
     *  Clears a ListMP element's pointers
     *
     *  This API is not for removing elements from a ListMP, and
     *  should never be called on an element in a ListMP--only on deListed
     *  elements.
     *
     *  @param(elem)    element to be cleared
     */
    Void elemClear(Elem *elem);

    /* Initialize shared memory */
    Void postInit(Object *obj, Error.Block *eb);

    /*! Structure of attributes in shared memory */
    struct Attrs {
        Bits32              status;     /* Created stamp                 */
        SharedRegion.SRPtr  gateMPAddr; /* GateMP SRPtr (shm safe)       */
        Elem                head;       /* head of list                  */
    };

    /* instance object */
    struct Instance_State {
        Attrs           *attrs;         /* local pointer to attrs        */
        Ptr             nsKey;          /* for removing NS entry         */
        Ipc.ObjType     objType;        /* Static/Dynamic? open/creator? */
        GateMP.Handle   gate;           /* Gate for critical regions     */
        SizeT           allocSize;      /* Shared memory allocated       */
        UInt16          regionId;       /* SharedRegion ID               */
        Bool            cacheEnabled;   /* Whether to do cache calls     */
        SizeT           cacheLineSize;  /* The region cache line size    */
    };

    /* module object */
    struct Module_State {
        NameServer.Handle nameServer;
    };
}
