/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
 *
 */

/*!
 *  ======== DSKT2 ========
 *  XDAIS algorithm management library.
 */
@Template("./DSKT2.xdt")

metaonly module DSKT2 {

    /*!
     *  ======== DARAM0 ========
     *  IALG memory space mapping of IALG_DARAM0.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String DARAM0;

    /*!
     *  ======== DARAM1 ========
     *  IALG memory space mapping of IALG_DARAM1.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String DARAM1;

    /*!
     *  ======== DARAM2 ========
     *  IALG memory space mapping of IALG_DARAM2.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String DARAM2;

    /*!
     *  ======== SARAM0 ========
     *  IALG memory space mapping of IALG_SARAM0.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String SARAM0;

    /*!
     *  ======== SARAM1 ========
     *  IALG memory space mapping of IALG_SARAM1.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String SARAM1;

    /*!
     *  ======== SARAM2 ========
     *  IALG memory space mapping of IALG_SARAM2.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String SARAM2;

    /*!
     *  ======== ESDATA ========
     *  IALG memory space mapping of IALG_ESDATA.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String ESDATA;

    /*!
     *  ======== IPROG ========
     *  IALG memory space mapping of IALG_IPROG.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String IPROG;

    /*!
     *  ======== EPROG ========
     *  IALG memory space mapping of IALG_EPROG.
     *
     *  This must be assigned the name of an instance of a module that
     *  implements IHeap.
     */
    config String EPROG;

    /*!
     *  ======== DSKT2_HEAP ========
     *  Heap for allocating internal DSKT2 data structures.
     *
     *  Objects internal to the DSKT2 module will be allocated from this heap.
     */
    config String DSKT2_HEAP;

    /*!
     *  ======== ALLOW_EXTERNAL_SCRATCH ========
     *  Allow external memory to be used for algorithm scratch memory requests.
     *
     *  If an algorithm requests scratch memory, and insufficient scratch
     *  memory is available, scratch buffers will be allocated in external
     *  memory if property is 'true'.
     */
    config bool   ALLOW_EXTERNAL_SCRATCH = true;

    /*!
     *  ======== DARAM_SCRATCH_SIZES ========
     *  Shared IALG_DARAM0 scratch group sizes.
     */
    config UInt   DARAM_SCRATCH_SIZES[] =
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

    /*!
     *  ======== SARAM_SCRATCH_SIZES ========
     *  Shared IALG_SARAM0 scratch group sizes.
     */
    config UInt   SARAM_SCRATCH_SIZES[] =
                  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];


    /*!
     *  ======== cacheWritebackInvalidateFxn ========
     *  Name of function implementing cache writeback invalidate.
     *
     *  This function must have the following signature:
     *  @p(code)
     *  (*DSKT2_CacheWBInvFxn)(Ptr blockPtr, size_t byteCnt, bool wait)
     *  @p
     *
     *  For C6000 platforms DSKT2 calls this function to ensure that the
     *  algorithm instance memory is not resident in cache when it is
     *  instantiated. This is necessary for compliance with XDAIS C6000 DMA
     *  Rules and Guidelines.
     */
    config String cacheWritebackInvalidateFxn = "DSKT2_cacheWBInv";

    /*!
     *  ======== disableLazyDeactivate =======
     *
     *  Set this to TRUE to disable lazy deactivate feature in DSKT2.
     *  This could affect performance of your algorithm, and should be used
     *  mostly for diagnostic purposes.
     */
    config Bool disableLazyDeactivate;

    /*!
     *  ======== ipcKeyBase ========
     *  Base value of keys of multi-process objects used by DSKT2.
     *
     *  Linux only. The MP objects created by DSKT2 will use keys starting at
     *  this value, and incrementing with each new object. There is currently
     *  a DSKT2 lock and semaphores for each scratch group, that use a key.
     *  So the keys used by DSKT2 will range from ipcKeyBase to ipcKeyBase +
     *  DSKT2_NUM_SCRATCH_GROUPS.
     *  The default value of ipcKeyBase is ascii code for "DSKT".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another key in the system that cannot be changed. If this value
     *  is changed, all programs using DSKT2 that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *
     *  TODO:H, do we need this since we only support BIOS?
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x44534B54;

}
