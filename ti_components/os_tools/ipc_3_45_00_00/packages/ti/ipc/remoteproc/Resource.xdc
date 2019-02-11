/*
 * Copyright (c) 2011-2013, Texas Instruments Incorporated
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
 *  ======== Resource.xdc ========
 */

/*!
 *  ======== Resource ========
 *  Resource Module
 */

@Template("./Resource.xdt")
@ModuleStartup
module Resource {

    /*!
     *  @def    Resource_loadAddr
     *  @brief  Default load address for the Resource table
     */
    metaonly config UInt loadAddr = 0x3000;

    /*!
     *  @def    Resource_loadSegment
     *  @brief  If loadSegment is defined, loadAddr is overridden with the base
     *          address of the loadSegment
     */
    metaonly config String loadSegment;

    /*!
     *  @def    Resource_traceOnly
     *  @brief  Set traceOnly to true in order to get an image with trace
     *          resources only, and without VRINGs.
     *          Implemented only for the Keystone II (TCI6638) platform.
     */
    metaonly config Bool traceOnly = false;

    /*!
     *  Flag to indicate the user will provide a custom resource table
     *
     *  If false (the default), a default resource table will be
     *  created during configuration.
     *
     *  If true, the user must supply their own resource table.
     *  Fundamentally, this amounts to providing a well-formed
     *  resource_table structure named 'ti_ipc_remoteproc_ResourceTable'.
     */
    metaonly config Bool customTable = false;

    /*!
     *  @def    Resource_S_SUCCESS
     *  @brief  Operation is successful.
     */
    const Int S_SUCCESS  = 0;

    /*!
     *  @def    Resource_E_NOTFOUND
     *  @brief  Element was not found in table
     */
    const Int E_NOTFOUND = -1;

    /*!
     *  @def       Resource_RscTable
     *
     *  @brief     An open-ended type-length-value based resource table
     */
    struct RscTable {
        UInt32 ver;
        UInt32 num;
        UInt32 reserved[2];
        UInt32 offset[1];
    };

    /*!
     *  @def       Resource_MemEntry
     *
     *  @brief     A Resource Table memory type record
     */
    struct MemEntry {
        UInt32 type;
        UInt32 da;       /* Device Virtual Address */
        UInt32 pa;       /* Physical Address */
        UInt32 len;
        UInt32 flags;
        UInt32 reserved;
        Char   name[32];
    };

    /*!
     *  @brief      Virtual to Physical address translation function
     *
     *  @sa         Resource_physToVirt
     */
    @DirectCall
    Int virtToPhys(UInt32 da, UInt32 *pa);

    /*!
     *  @brief      Physical to Virtual address translation function
     *
     *  @sa         Resource_virtToPhys
     */
    @DirectCall
    Int physToVirt(UInt32 pa, UInt32 *da);

    /*!
     *  @brief      Get the Trace Buffer address from resource table.
     *
     *  @return     Pointer to trace buffer, or NULL if not found.
     */
    @DirectCall
    Ptr getTraceBufPtr();

    /*!
     *  @brief      Get the status field of the VDEV, given the fw_rsc_vdev id.
     *
     *  @return     status value which is set by Virtio device on HLOS.
     */
    @DirectCall
    Char getVdevStatus(UInt32 id);

    /*!
     *  @brief      Get the nth (vqId) vring address from the VDEV struct.
     *
     *  @return     NULL if no VDEV found, or vqId is not found.
     */
    @DirectCall
    Ptr getVringDA(UInt32 vqId);

internal:   /* not for client use */

    /*!
     *  @brief      Use resource and resourceLen so table could be properly
     *              allocated
     *
     */
    Void init();

    /*!
     *  @brief      Return the i-th entry in the resource table if the entry
     *              is of type CARVEOUT or DEVMEM, or NULL otherwise.
     *
     */
    MemEntry *getMemEntry(UInt index);

    struct Module_State {
        RscTable    *pTable;  /* Resource Resource Table pointer */
    };
}
