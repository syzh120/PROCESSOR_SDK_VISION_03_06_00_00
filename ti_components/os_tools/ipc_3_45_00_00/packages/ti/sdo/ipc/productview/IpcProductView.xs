/*
 * Copyright (c) 2012), Texas Instruments Incorporated
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
 *  ======== IpcProductView.xs ========
 */

/* Scheduling elements */

var ProdQuery;
function module$meta$init()
{

/* Modules */

/* Heaps Sub Group Modules */

    this.ti_sdo_ipc_heaps_HeapMemMP.elemName = "HeapMemMP";
    this.ti_sdo_ipc_heaps_HeapMemMP.moduleName = "ti.sdo.ipc.heaps.HeapMemMP";
    this.ti_sdo_ipc_heaps_HeapMemMP.iconFileName = "icons/mem.ico";

    this.ti_sdo_ipc_heaps_HeapBufMP.elemName = "HeapBufMP";
    this.ti_sdo_ipc_heaps_HeapBufMP.moduleName = "ti.sdo.ipc.heaps.HeapBufMP";
    this.ti_sdo_ipc_heaps_HeapBufMP.iconFileName = "icons/mem.ico";

    this.ti_sdo_ipc_heaps_HeapMultiBufMP.elemName = "HeapMultiBufMP";
    this.ti_sdo_ipc_heaps_HeapMultiBufMP.moduleName =
        "ti.sdo.ipc.heaps.HeapMultiBufMP";
    this.ti_sdo_ipc_heaps_HeapMultiBufMP.iconFileName = "icons/mem.ico";

/* Communication Group Modules */

    this.ti_sdo_ipc_MessageQ.elemName = "MessageQ";
    this.ti_sdo_ipc_MessageQ.moduleName = "ti.sdo.ipc.MessageQ";
    this.ti_sdo_ipc_MessageQ.iconFileName = "icons/mbx.ico";

    this.ti_sdo_ipc_Notify.elemName = "Notify";
    this.ti_sdo_ipc_Notify.moduleName = "ti.sdo.ipc.Notify";
    this.ti_sdo_ipc_Notify.iconFileName = "icons/mbx.ico";

    this.ti_sdo_ipc_Ipc.elemName = "Ipc Types";
    this.ti_sdo_ipc_Ipc.moduleName = "ti.sdo.ipc.Ipc";
    this.ti_sdo_ipc_Ipc.iconFileName = "icons/sys.ico";

    this.ti_sdo_ipc_SharedRegion.elemName = "SharedRegion";
    this.ti_sdo_ipc_SharedRegion.moduleName = "ti.sdo.ipc.SharedRegion";
    this.ti_sdo_ipc_SharedRegion.iconFileName = "icons/mem.ico";

    this.ti_sdo_ipc_GateMP.elemName = "GateMP";
    this.ti_sdo_ipc_GateMP.moduleName = "ti.sdo.ipc.GateMP";
    this.ti_sdo_ipc_GateMP.iconFileName = "icons/lck.ico";

    this.ti_sdo_ipc_ListMP.elemName = "ListMP";
    this.ti_sdo_ipc_ListMP.moduleName = "ti.sdo.ipc.ListMP";
    this.ti_sdo_ipc_ListMP.iconFileName = "icons/que.ico";

/* Utilities Group Modules */

    this.ti_sdo_utils_List.elemName = "List";
    this.ti_sdo_utils_List.moduleName = "ti.sdo.utils.List";
    this.ti_sdo_utils_List.iconFileName = "icons/que.ico";

    this.ti_sdo_utils_NameServer.elemName = "NameServer";
    this.ti_sdo_utils_NameServer.moduleName = "ti.sdo.utils.NameServer";
    this.ti_sdo_utils_NameServer.iconFileName = "icons/que.ico";

    this.ti_sdo_utils_MultiProc.elemName = "MultiProc";
    this.ti_sdo_utils_MultiProc.moduleName = "ti.sdo.utils.MultiProc";
    this.ti_sdo_utils_MultiProc.iconFileName = "icons/que.ico";

/* Sub Groups */

    this.heapsGroup.elemName = "Heaps";
    this.heapsGroup.moduleName = null;
    this.heapsGroup.iconFileName = "icons/mem_fldr.ico";
    this.heapsGroup.elemArray = [
        this.ti_sdo_ipc_heaps_HeapMemMP,
        this.ti_sdo_ipc_heaps_HeapBufMP,
        this.ti_sdo_ipc_heaps_HeapMultiBufMP
    ];

/* Groups */
    this.multicoreGroup.elemName = "Multicore Modules";
    this.multicoreGroup.moduleName = null;
    this.multicoreGroup.iconFileName = "icons/hst_fldr.ico";
    this.multicoreGroup.elemArray = [
        this.ti_sdo_ipc_Ipc,
        this.ti_sdo_ipc_ListMP,
        this.ti_sdo_ipc_MessageQ,
        this.ti_sdo_utils_MultiProc,
        this.ti_sdo_ipc_Notify,
        this.ti_sdo_ipc_SharedRegion,
        this.heapsGroup,
    ];

    this.utilsGroup.elemName = "Utilities";
    this.utilsGroup.moduleName = null;
    this.utilsGroup.iconFileName = "icons/rtdx.ico";
    this.utilsGroup.elemArray = [
        this.ti_sdo_utils_List,
        this.ti_sdo_utils_NameServer,
    ];

/* product */

    this.ipcProduct.elemName = "IPC (Multicore)";
    this.ipcProduct.moduleName = null;
    this.ipcProduct.iconFileName = "icons/bios.gif";
    this.ipcProduct.elemArray = [
        this.multicoreGroup,
        this.utilsGroup
    ];
}

/*
 *  ======== getProductDescriptor ========
 */
function getProductDescriptor()
{
    return this.ipcProduct;
}
