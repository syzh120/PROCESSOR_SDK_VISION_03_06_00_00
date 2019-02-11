/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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

#include <xdc/std.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Memory.h>

#include <ti/xdais/ialg.h>

#include <ti/sysbios/heaps/HeapMem.h>

#pragma DATA_SECTION(EdmaMgr_HEAP_MEM,".far:EdmaMgr_heap");
#pragma DATA_SECTION(EdmaMgr_HEAP,".far:EdmaMgr_heap");

#define EdmaMgr_HEAP_SIZE  0x1500
uint8_t EdmaMgr_HEAP_MEM[EdmaMgr_HEAP_SIZE];

ti_sysbios_heaps_HeapMem_Handle EdmaMgr_HEAP;

/*********************************************************************************
 * FUNCTION PURPOSE: Create EdmaMgr heaps
 *********************************************************************************
  DESCRIPTION:      This function is creating the heap for EdmaMgr use.

  Parameters :      Inputs: None

                    Output: None
 *********************************************************************************/
void EdmaMgr_heap_create(void)
{
    HeapMem_Params prms;

    /* Create internal heap */
    HeapMem_Params_init(&prms);
    prms.size = EdmaMgr_HEAP_SIZE;
    prms.buf = EdmaMgr_HEAP_MEM;
    EdmaMgr_HEAP = HeapMem_create(&prms, NULL);
}

/*********************************************************************************
 * FUNCTION PURPOSE: Free heap memory
 *********************************************************************************
  DESCRIPTION:      This function frees heap memory

  Parameters :      Inputs: memTab  : memory entries
                            n       : number of memory entries
                    Output: None
 *********************************************************************************/
Void EdmaMgr_heap_free(IALG_MemRec memTab[], Int n)
{
    Int i;

    for (i = 0; i < n; i++) {
        if (memTab[i].base != NULL) {
            Memory_free((xdc_runtime_IHeap_Handle)EdmaMgr_HEAP,
                    memTab->base, memTab->size);
        }
    }
}

/*********************************************************************************
 * FUNCTION PURPOSE: Allocate heap memory
 *********************************************************************************
  DESCRIPTION:      This function allocates heap memory

  Parameters :      Inputs: memTab  : memory entries
                            n       : number of memory entries
                    Output: TRUE if allocation successful; FALSE otherwise
 *********************************************************************************/
Bool EdmaMgr_heap_alloc(IALG_MemRec memTab[], Int n)
{
    Int i;

    for (i = 0; i < n; i++) {
        memTab[i].base = Memory_calloc((xdc_runtime_IHeap_Handle)EdmaMgr_HEAP,
                memTab[i].size, memTab[i].alignment, NULL);

        if (memTab[i].base == NULL) {
            EdmaMgr_heap_free(memTab, i);
            return (FALSE);
        }
    }
    return (TRUE);
}
