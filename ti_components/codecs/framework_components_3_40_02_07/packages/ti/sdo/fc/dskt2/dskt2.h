/*
 * Copyright (c) 2012-2014, Texas Instruments Incorporated
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
/**
 *  @file               ti/sdo/fc/dskt2/dskt2.h
 *
 *  @brief              Provides services to support XDAIS algorithm instance
 *                      objects.
 */

/**
 *  @defgroup   ti_sdo_fc_dskt2_DSKT2 DSKT2
 *
 *              The XDAIS Socket Library provides services to support the
 *              creation, initialization, control, and deletion of XDAIS
 *              algorithm instance objects.
 */

#ifndef DSKT2_
#define DSKT2_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup ti_sdo_fc_dskt2_DSKT2 */
/*@{*/

#include <xdc/std.h>
#include <xdc/runtime/IHeap.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>
#include <stddef.h>

#define DSKT2_NUM_SCRATCH_GROUPS 20     /**< Maximum number of scratch groups
                                         *   that can be supported.
                                         */

#define DSKT2_MAX_MEM_ALLOCATION_SIZE  0xFFFF   /**< Maximum memory
                                                 *   allocation.
                                                 */

/* NOTE: DO NOT Change NUM_SHAREDHEAPS*/
#define DSKT2_NUM_SHAREDHEAPS 2

/**
 * @brief       Name to pass to Diags_setMask() to enable logging for DSKT2
 *              functions. For example,
 *                  Diags_setMask(DSKT2_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define DSKT2_MODNAME  "ti.sdo.fc.dskt2"

/**
 *  @brief      Function prototype of cache writeback function: Writes back
 *              the memory within the range of blockPtr and blockPtr + byteCnt.
 *
 *  @remarks    If @c wait is @c TRUE, wait for the writeback to complete before
 *              returning from this fuction call.
 */
typedef Void (*DSKT2_CacheWBInvFxn)(Ptr blockPtr, size_t byteCnt, Bool wait);


/**
 *    @brief    Cache writeback function pointer used by DSKT2 if not NULL
 */
extern __FAR__ DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn;

/* TODO: Should these be declared here ? User should know they can initialize
         these entries */
extern __FAR__ xdc_runtime_IHeap_Handle DSKT2_daram0Heap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_daram1Heap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_daram2Heap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_saram0Heap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_saram1Heap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_saram2Heap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_iprogHeap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_eprogHeap;
extern __FAR__  xdc_runtime_IHeap_Handle DSKT2_esdataHeap;
extern __FAR__  xdc_runtime_IHeap_Handle _DSKT2_heap;

extern __FAR__ UInt _DSKT2_ALLOW_EXTERNAL_SCRATCH;

extern __FAR__ UInt _DSKT2_DARAM_SCRATCH_SIZES[];
extern __FAR__ UInt _DSKT2_SARAM_SCRATCH_SIZES[];

/* ENDTODO */

/**
 *  @brief      Set this to TRUE to disable lazy deactivate feature in DSKT2.
 */
extern __FAR__ Bool ti_sdo_fc_dskt2_DSKT2_disableLazyDeactivate;

/**
 *  @brief      Prepares a XDAIS algorithm instance object to start using its
 *              scratch memory.
 *
 *  @param[in]  scratchMutexId  scratch-group Id used to associate the instance
 *                              with a scratch group. The value must be the
 *                              same id used when creating this algorithm
 *                              instance.
 *
 *  @param[in]  alg             IALG_Handle of the algorithm instance to be
 *                              activated.
 *
 *  @retval     None
 *
 *  @pre        alg must be a valid handle for the algorithm's instance object
 *              returned by an earlier call to DSKT2_createAlg()
 *
 *  @pre        If alg uses DMA (IDMA3), dmaInit must be called before calling
 *              this method, ensuring that all of the instance's persistent
 *              memory is initialized and the object is ready to be used
 *
 *  @pre        No other algorithm method is currently being run on this
 *              instance. This method never preempts any other method on the
 *              same instance.
 *
 *  @post       All of the instance's persistent and scratch memory is
 *              initialized and the object is ready to be used.
 *
 *  @remarks    DSKT2_activateAlg() performs all scratch memory initialization
 *              for an algorithm's instance object. After a successful return
 *              from DSKT2_activateAlg(), the algorithm's instance object is
 *              ready to be used to process data.
 *
 *  @remarks    Unless the instance is already active, DSKT2_activateAlg()
 *              uses the algorithm's IALG interface function algActivate to
 *              initialize the algorithm instance's scratch buffers from
 *              persistent data memory.
 *
 *  @remarks    DSKT2_activateAlg() must be called before any processing or
 *              control methods of the algorithm instance can be called.
 *
 *  @remarks    DSKT2 maintains state information about current "active"
 *              algorithm instances at run-time, so that it does not perform
 *              unnecessary IALG "activation" calls when alg is already active.
 *              As part of this optimization it may call the algDeactivate
 *              method of the currently active algorithm instance in order to
 *              activate this  algorithm instance (alg).
 *
 *  @remarks    Caller ensures algorithms with the same @c scratchMutexId will
 *              not be activated simultaneously. Usually the scratch group id
 *              is associated to the priority of the task in which the
 *              algorithm is running.
 *
 *  @remarks    The implementation of the IALG algActivate() is optional by
 *              XDAIS standard. So, the instance activation makes sense
 *              only when the method is implemented by the algorithm.
 *              DSKT2_activateAlg() makes proper checks to ensure correct
 *              operation even if the algorithm does not implement the
 *              algActivate() method.
 *
 *  @sa         DSKT2_deactivateAlg()
 *  @sa         DMAN3_grantDmaChannels()
 *  @sa         DMAN_addAlg()
 */
extern Void DSKT2_activateAlg(Int scratchMutexId, IALG_Handle alg);


/**
 *  @brief      This is a convenience API to call a XDAIS algorithm instance's
 *              algControl function
 *
 *  @param[in]  alg             IALG_Handle of the algorithm instance.
 *  @param[in]  cmd             IALG_Cmd structure for the control operation.
 *  @param[in]  status          Pointer to IALG_Status structure for algorithm
 *                              to return status.
 *
 *  @retval     IALG_EOK        The control operation was successful
 *  @retval     otherwise       A failure occurred during the control operation
 *
 *  @pre        @c alg must be a valid handle for the algorithm's instance
 *              object returned by an earlier call to DSKT2_createAlg().
 *
 *  @pre        Algorithm specific cmd values are always less than IALG_SYSCMD.
 *
 *  @post       If the control operation is successful, the return value from
 *              this operation is equal to IALG_EOK; otherwise it is equal to
 *              either IALG_EFAIL or an algorithm-specific return value.
 *
 *  @post       If the cmd value is not recognized, the return value is not
 *              equal to IALG_EOK.
 *
 *  @remarks    DSKT2_controlAlg() must be called only when the instance is in
 *              active state.
 *
 *  @remarks    The implementation of the IALG algControl is optional by XDAIS
 *              standard.  DSKT2_controlAlg() makes proper checks to ensure
 *              correct operation even if the algorithm does not implement
 *              algControl().
 */
extern Int DSKT2_controlAlg(IALG_Handle alg, IALG_Cmd cmd,
    IALG_Status *status);


/**
 *  @brief      Creates and initializes a XDAIS algorithm instance object.
 *
 *  @param[in]  scratchMutexId  Scratch-group Id for determining the shared
 *                              scratch memory buffer. Value -1 is used to
 *                              disable scratch sharing for this algorithm
 *                              instance. A value between 0 and
 *                              (DSKT2_NUM_SCRATCH_GROUPS-1) indicates a valid
 *                              scratch group
 *  @param[in]  fxns            Pointer to the algorithm's IALG_Fxns table.
 *  @param[in]  parent          Handle of parent algorithm (optional).
 *  @param[in]  params          Pointer to an IALG_Params structure.
 *
 *  @retval     non-NULL        IALG_Handle for the new instance object.
 *  @retval     NULL            Failure.
 *
 *  @pre        fxns is a valid pointer to an IALG_Fxns structure
 *              (containing the vtable for a XDAIS compliant algorithm)
 *
 *  @post       If scratchMutexId is -1, all instance scratch memory is
 *              allocated as persistent (i.e. not shared) and instance
 *              operation does not require mutual exclusion
 *
 *  @post       With the exception of any initialization performed by
 *              algActivate and (IDMA2) dmaInit all of the instance's
 *              persistent memory is initialized and the object is ready to be
 *              used
 *
 *  @remarks    It uses the algorithm's IALG interface functions to query the
 *              algorithm for its memory needs then allocates the memory for
 *              the algorithm and calls the algorithm's algInit function to
 *              let the new algorithm instance object initialize itself using
 *              the allocated memory.
 *
 *  @remarks    DSKT2_createAlg() performs initialization necessary to complete
 *              the run-time creation of an algorithm's instance object. After
 *              a successful return from DSKT2_createAlg(), the algorithm's
 *              instance object can be activated via a DSKT2_activateAlg()
 *              before it can be used to process data.
 *
 *  @remarks    DSKT2_createAlg() tries to dynamically allocate instance memory
 *              based on the IALG_MemSpace attribute of the requested memory.
 *              Global DSKT2 configuration settings allow OEM to designate a
 *              memory heap for each IALG_MemSpace. DSKT2_createAlg() attempts
 *              to allocate memory in the requested space, but may search for
 *              alternative heaps when preferred heap is not large enough.
 *
 *  @remarks    The parent argument is a handle to another algorithm instance
 *              object. This parameter is often NULL, indicating that no parent
 *              object exists.  This parameter allows clients to create a
 *              shared algorithm instance object and pass it to other algorithm
 *              instances. For example, a parent instance object might contain
 *              global read-only tables that are used by several instances of a
 *              vocoder.
 *
 *  @remarks    Caller need to ensure algorithms created with the same
 *              "scratchMutexId" will not execute simultaneously
 *
 *  @remarks    On failure all memory allocated during the call (used for
 *              algorithm query, and portions of algorithm memory that were
 *              successfully allocated during the function) has been freed
 *              before DSKT2_createAlg() returns
 *
 *  @remarks    The params argument is a pointer to algorithm-specific
 *              parameters that are necessary for the creation and
 *              initialization of the instance object. This pointer points to
 *              the same parameters passed to the algorithm's IALG algAlloc
 *              function. However, this pointer may be NULL. In this case,
 *              algorithm's IALG function algInit, must assume default creation
 *              parameters.
 *
 *  @remarks    Mutual exclusion needs to be enforced by the application
 *              framework when executing this function.
 *              This function assumes that the create phase of XDAIS algorithms
 *              in the same scratch group will not be scheduled concurrently.
 *
 **
 *  @sa         DSKT2_activateAlg(), DSKT2_deactivateAlg(), DSKT2_freeAlg()
 */
extern IALG_Handle DSKT2_createAlg(Int scratchMutexId, IALG_Fxns * fxns,
    IALG_Handle parent, IALG_Params * params);


/**
 *  @brief      Creates and initializes a XDAIS algorithm instance object.
 *
 *  @param[in]  scratchMutexId  Scratch-group Id for determining the shared
 *                              scratch memory buffer. Value -1 is used to
 *                              disable scratch sharing for this algorithm
 *                              instance. A value between 0 and
 *                              (DSKT2_NUM_SCRATCH_GROUPS-1) indicates a valid
 *                              scratch group
 *  @param[in]  fxns            Pointer to the algorithm's IALG_Fxns table.
 *  @param[in]  parent          Handle of parent algorithm (optional).
 *  @param[in]  params          Pointer to an IALG_Params structure.
 *  @param[in]  extHeapId       Segment Id of memory heap to be used for all
 *                              allocations in memory space IALG_ESDATA. This
 *                              segment will be used instead of the default
 *                              external memory segment.
 *
 *  @retval     non-NULL        IALG_Handle for the new instance object.
 *  @retval     NULL            Failure.
 *
 *  @pre        fxns is a valid pointer to an IALG_Fxns structure
 *              (containing the vtable for a XDAIS compliant algorithm)
 *
 *  @pre        extHeapId >= 0
 *
 *  @post       If scratchMutexId is -1, all instance scratch memory is
 *              allocated as persistent (i.e. not shared) and instance
 *              operation does not require mutual exclusion
 *
 *  @post       With the exception of any initialization performed by
 *              algActivate and (IDMA2) dmaInit all of the instance's
 *              persistent memory is initialized and the object is ready to be
 *              used
 *
 *  @remarks    It uses the algorithm's IALG interface functions to query the
 *              algorithm for its memory needs then allocates the memory for
 *              the algorithm and calls the algorithm's algInit function to
 *              let the new algorithm instance object initialize itself using
 *              the allocated memory.
 *
 *  @remarks    DSKT2_createAlg2() performs initialization necessary to complete
 *              the run-time creation of an algorithm's instance object. After
 *              a successful return from DSKT2_createAlg2(), the algorithm's
 *              instance object can be activated via a DSKT2_activateAlg()
 *              before it can be used to process data.
 *
 *  @remarks    DSKT2_createAlg2() tries to dynamically allocate instance memory
 *              based on the IALG_MemSpace attribute of the requested memory.
 *              Global DSKT2 configuration settings allow OEM to designate a
 *              memory heap for each IALG_MemSpace. DSKT2_createAlg2() attempts
 *              to allocate memory in the requested space, but may search for
 *              alternative heaps when preferred heap is not large enough.
 *
 *  @remarks    DSKT2_createAlg2() will attempt to use the heap specified by
 *              the input parameter, extHeapId, for all allocations in the
 *              IALG_MemSpace, IALG_ESDATA. Furthermore, this holds for
 *              any IALG_MemSpace that has been configured with the same
 *              memory segment as IALG_ESDATA. e.g., if IALG_ESDATA and
 *              IALG_SARAM3 have both been configured to use the heap in the
 *              memory segment EXTMEM, then DSKT2_createAlg2() will attempt
 *              to allocate memory requested in the spaces IALG_SARAM3
 *              and IALG_ESDATA, from the heap, extHeapId.
 *
 *  @remarks    The parent argument is a handle to another algorithm instance
 *              object. This parameter is often NULL, indicating that no parent
 *              object exists.  This parameter allows clients to create a
 *              shared algorithm instance object and pass it to other algorithm
 *              instances. For example, a parent instance object might contain
 *              global read-only tables that are used by several instances of a
 *              vocoder.
 *
 *  @remarks    Mutual exclusion needs to be enforced by the application
 *              framework when executing this function.
 *              This function assumes that the create phase of XDAIS algorithms
 *              in the same scratch group will not be scheduled concurrently.
 *
 *  @remarks    Caller need to ensure algorithms created with the same
 *              "scratchMutexId" will not execute simultaneously
 *
 *  @remarks    On failure all memory allocated during the call (used for
 *              algorithm query, and portions of algorithm memory that were
 *              successfully allocated during the function) has been freed
 *              before DSKT2_createAlg() returns
 *
 *  @remarks    The params argument is a pointer to algorithm-specific
 *              parameters that are necessary for the creation and
 *              initialization of the instance object. This pointer points to
 *              the same parameters passed to the algorithm's IALG algAlloc
 *              function. However, this pointer may be NULL. In this case,
 *              algorithm's IALG function algInit, must assume default creation
 *              parameters.
 *
 *  @sa         DSKT2_activateAlg(), DSKT2_deactivateAlg(), DSKT2_freeAlg()
 */
extern IALG_Handle DSKT2_createAlg2(Int scratchMutexId, IALG_Fxns * fxns,
        IALG_Handle parent, IALG_Params * params,
        xdc_runtime_IHeap_Handle extHeapId);


/**
 *  @brief      Creates and initializes a XDAIS algorithm instance object,
 *              allocating all algorithm memory in external memory.
 *
 *  @param[in]  scratchId       Scratch-group Id for determining the shared
 *                              scratch memory buffer. Value -1 is used to
 *                              disable scratch sharing for this algorithm
 *                              instance. A value between 0 and
 *                              (DSKT2_NUM_SCRATCH_GROUPS-1) indicates a valid
 *                              scratch group
 *  @param[in]  fxns            Pointer to the algorithm's IALG_Fxns table.
 *  @param[in]  parent          Handle of parent algorithm (optional).
 *  @param[in]  params          Pointer to an IALG_Params structure.
 *
 *  @retval     non-NULL        IALG_Handle for the new instance object.
 *  @retval     NULL            Failure.
 *
 *  @pre        fxns is a valid pointer to an IALG_Fxns structure
 *              (containing the vtable for a XDAIS compliant algorithm)
 *
 *  @post       If scratchMutexId is -1, all instance scratch memory is
 *              allocated as persistent (i.e. not shared) and instance
 *              operation does not require mutual exclusion
 *
 *  @post       With the exception of any initialization performed by
 *              algActivate and (IDMA2 or IDMA3) dmaInit all of the instance's
 *              persistent memory is initialized and the object is ready to be
 *              used
 *
 *  @remarks    This API is very similar to DSKT2_createAlg(), in that
 *              it uses the algorithm's IALG interface functions to query the
 *              algorithm for its memory needs, allocates the memory for
 *              the algorithm and calls the algorithm's algInit function to
 *              let the new algorithm instance object initialize itself using
 *              the allocated memory. Unlike DSKT2_createAlg(), however,
 *              DSKT2_createAlgExt() will ignore the @c space field of the
 *              @c IALG_MemRec table entries filled in by the algorithm's
 *              algAlloc() function, and allocate all of the memory in the
 *              memory segment that is mapped to DSKT2.ESDATA.
 *
 *  @remarks    After a successful return from DSKT2_createAlgExt(), the
 *              algorithm's instance object can be activated via a
 *              DSKT2_activateAlg() before it can be used to process data.
 *
 *  @remarks    The parent argument is a handle to another algorithm instance
 *              object. This parameter is often NULL, indicating that no parent
 *              object exists.  This parameter allows clients to create a
 *              shared algorithm instance object and pass it to other algorithm
 *              instances. For example, a parent instance object might contain
 *              global read-only tables that are used by several instances of a
 *              vocoder.
 *
 *  @remarks    Mutual exclusion needs to be enforced by the application
 *              framework when executing this function.
 *              This function assumes that the create phase of XDAIS algorithms
 *              in the same scratch group will not be scheduled concurrently.
 *
 *  @remarks    Caller need to ensure algorithms created with the same
 *              "scratchMutexId" will not execute simultaneously
 *
 *  @remarks    On failure all memory allocated during the call (used for
 *              algorithm query, and portions of algorithm memory that were
 *              successfully allocated during the function) has been freed
 *              before DSKT2_createAlg() returns
 *
 *  @remarks    The params argument is a pointer to algorithm-specific
 *              parameters that are necessary for the creation and
 *              initialization of the instance object. This pointer points to
 *              the same parameters passed to the algorithm's IALG algAlloc
 *              function. However, this pointer may be NULL. In this case,
 *              algorithm's IALG function algInit, must assume default creation
 *              parameters.
 *
 *  @sa         DSKT2_activateAlg(), DSKT2_deactivateAlg(), DSKT2_freeAlg()
 */
IALG_Handle DSKT2_createAlgExt(Int scratchId, IALG_Fxns * fxns,
        IALG_Handle parent, IALG_Params * params);

/**
 *  @brief      Prepares a XDAIS algorithm instance object to give up using
 *              its scratch memory
 *
 *  @param[in]  scratchMutexId  scratch-group Id used for determining the
 *                              shared scratch memory.
 *  @param[in]  alg             IALG_Handle of the algorithm instance to be
 *                              deactivated.
 *
 *  @retval     None
 *
 *  @pre        alg must be a valid handle for the algorithm's instance object
 *              returned by an earlier call to DSKT2_createAlg()
 *
 *  @pre        No other algorithm method is currently being run on this
 *              instance. This method never preempts any other method on the
 *              same instance.
 *
 *  @pre        DSKT2_activateAlg() must be called before calling this method
 *
 *  @remarks    DSKT2_deactivateAlg() marks an algorithm's shared scratch
 *              memory as available to other instances activation. After a
 *              successful return from DSKT2_deactivateAlg(), the algorithm's
 *              processing or control functions cannot be called to process
 *              data.
 *
 *  @remarks    Object's deactivation logic involves calling the algorithm's
 *              IALG interface function algDeactivate to save necessary data
 *              from the algorithm instance's scratch buffers to its persistent
 *              data memory.
 *
 *  @remarks    DSKT2_deactivateAlg() must be called after the last processing
 *              or control methods of the algorithm instance.
 *
 *  @remarks    DSKT2 maintains state information about current "active"
 *              algorithm instances at run-time, so that it does not perform
 *              unnecessary IALG "deactivation" calls. As part of this
 *              optimization it may defer the deactivation of this algorithm
 *              instance (alg) to a later stage, i.e. when DSKT2_activateAlg()
 *              is called to activate another algorithm instance.
 *
 *  @remarks    The implementation of the IALG algDeactivate is optional by
 *              XDAIS standard. So, the instance deactivation makes sense only
 *              when the method is implemented by the algorithm.
 *              DSKT2_deactivateAlg() makes proper checks to ensure correct
 *              operation even if the algorithm does not implement the
 *              algDeactivate methods.
 *
 *  @sa         DSKT2_activateAlg()
 *
 */
extern Void DSKT2_deactivateAlg(Int scratchMutexId, IALG_Handle alg);

/**
 *  @brief      All algorithms that have been deactivated lazily are now
 *              really deactivate. Any algorithms that are still currently
 *              active will be left as is. The number of algorithms that are
 *              still active will be returned from this call.
 *
 *  @retval     >=0   The number of currently active algorithms
 *
 *  @pre        Must be called with the TSK and SWI schedulers disabled.
 *
 */
extern Int DSKT2_deactivateAll();

/**
 *  @brief      Deletes a XDAIS algorithm instance object and frees all
 *              persistent memory allocated for the instance object
 *
 *  @param[in]  scratchMutexId  scratch-group Id used for determining the
 *                              shared scratch memory. Must be the same Id
 *                              used when algorithm instance is created
 *  @param[in]  alg             IALG_Handle of the algorithm instance to be
 *                              deleted
 *
 *  @retval     TRUE            Success
 *  @retval     FALSE           Failure
 *
 *  @pre        alg must be a valid handle for the algorithm's instance object
 *              returned by an earlier call to DSKT2_createAlg()
 *
 *  @remarks    A reference counting mechanism is implemented to free up
 *              instance scratch memory so that when the last instance within a
 *              scratch group is deleted all shared scratch memory allocated
 *              for the group is reclaimed.
 *
 *  @remarks    DSKT2 maintains allocation information about all algorithm
 *              instances created by DSKT2_createAlg(), so it does not call the
 *              instance algFree method before free'ing instance memory.
 *
 *  @remarks    Mutual exclusion needs to be enforced by the application
 *              framework when executing this function.
 *              This function assumes that the delete phase of XDAIS algorithms
 *              in the same scratch group will not be scheduled concurrently.
 *
 *  @sa         DSKT2_createAlg()
 */
extern Bool DSKT2_freeAlg(Int scratchMutexId, IALG_Handle alg);

/**
 *  @brief      Alocates memory from a DSKT2 shared scratch group buffer.
 *
 *  @param[in]  alg             IALG_Handle of the algorithm instance to be
 *                              granted shared scratch memory. Could be NULL.
 *  @param[in]  mutexId         scratch-group Id used for determining the
 *                              shared scratch memory. Must be the same Id
 *                              used when algorithm instance is created
 *  @param[in]  memTab          Array of IALG_MemRec structures describing the
 *                              memory required by the algorithm
 *  @param[in]  numRecs         Number of IALG_MemRec structures
 *
 *  @retval     TRUE            Success
 *  @retval     FALSE           Failure
 *
 *  @pre        If @c alg is not NULL, then it must be a valid handle for
 *              an algorithm instance returned by an earlier call to
 *              DSKT2_createAlg().
 *
 *  @remarks    If a valid IALG_Handle is passed to this call, allocation is
 *              done from the shared buffer in a non-overlapping manner from
 *              memory already assigned to the algorithm.
 *
 *  @remarks    DSKT2 maintains allocation information about all algorithm
 *              instances created by DSKT2_createAlg(), so it does not call the
 *              instance algFree() method before free'ing instance memory.
 *
 *  @sa         DSKT2_freeScratch()
 */
extern Bool DSKT2_allocScratch(IALG_Handle alg,Int mutexId, IALG_MemRec *memTab,
        Int numRecs);

extern Int DSKT2_getScratchId(IALG_Handle alg);

/**
 *  @brief      Alocates memory from a DSKT2 shared scratch group buffer.
 *
 *  @param[in]  mutexId         scratch-group Id used for determining the
 *                              shared scratch memory. Must be the same Id
 *                              used when algorithm instance is created
 *  @param[in]  addr            Address of the memory to be freed, that was
 *                              previous allocated using DSKT2_allocScratch
 *  @param[in]  size            Size of memory to be freed.
 *
 *  @pre        Memory must have been allocated through a call
 *              to DSKT2_allocScratch
 *
 *  @remarks    If a valid IALG_Handle is passed to this call, allocation is
 *              done from teh shared buffer in a non-overlapping manner from
 *              memory already assigned to the algorithm
 *
 *  @remarks    DSKT2 maintains allocation information about all algorithm
 *              instances created by DSKT2_createAlg(), so it does not call the
 *              instance algFree method before free'ing instance memory.
 *
 *  @sa         DSKT2_allocScratch()
 */
extern Void DSKT2_freeScratch(Int mutexId, Void *addr, UInt size);

/**
 *  @brief      Alocates persistent memory to the requesting algorithm
 *
 *  @param[in]  memTab          Array of IALG_MemRec structures describing the
 *                              memory required by the algorithm
 *  @param[in]  numRecs         Number of IALG_MemRec structures
 *
 *  @retval     TRUE            Success
 *  @retval     FALSE           Failure
 *
 *  @sa         DSKT2_freePersistent()
 */
extern Bool DSKT2_allocPersistent(IALG_MemRec *memTab, Int numRecs);

/**
 *  @brief      Frees persistent memory from the requesting algorithm
 *
 *  @param[in]  memTab          Array of IALG_MemRec structures describing the
 *                              memory granted to the algorithm, to be freed.
 *  @param[in]  numRecs         Number of IALG_MemRec structures
 *
 *  @pre        Memory must have been allocated through a call
 *              to DSKT2_allocPersistent
 *
 *  @sa         DSKT2_allocPersistent()
 */
extern Void DSKT2_freePersistent(IALG_MemRec *memTab, Int numRecs);

/*
 * Functions below are friend functions that are used by RMAN and some IRES
 * implementations to cooperatively yield to higher priority algorithms.
 */
/** @cond INTERNAL */
/**
 *  @brief      Yields control to another algorithm of same or higher priority,
 *              will release the scratchgroup lock etc. Context will
 *              switch to this other algorithm. Should have valid context
 *              save/restore functions for correct execution.
 */
Void DSKT2_yield(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs);

/**
 *  @brief      Allows you to obtain the yield arguments for a particular
 *              scratch group.
 */
IRES_YieldArgs DSKT2_getYieldArgs(Int scratchId);

/**
 *  @brief      Allows you to set and then get the yield arguments for a
 *              particular scratch group.
 */
IRES_YieldArgs DSKT2_setYieldArgs(Int scratchId, Bool yieldFlag);


Void DSKT2_contextRelease(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs);

Void DSKT2_contextAcquire(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs);

/**
 *  @brief      Returns the number of algorithms created using DSKT2
 *
 *  @retval             Number of algorithms
 */
Int DSKT2_getNumAlgs();

/**
 *  @brief      Returns the complete list of algorithms created using DSKT2
 *              and their scratch ids
 *  @param[in/out]      algList     Empty table passed in, populated list of
 *                                 IALG_Handles is then reeturned.
 *
 *  @param[in/out]      scratchIds  Empty table passed in, populated list of
 *                                  scratch ids is returned.
 *  @retval             Number of algorithms
 */
Int DSKT2_getAlgList(IALG_Handle * algList, Int * scratchIds);

/** @endcond INTERNAL */

/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  /* DSKT2_ */
