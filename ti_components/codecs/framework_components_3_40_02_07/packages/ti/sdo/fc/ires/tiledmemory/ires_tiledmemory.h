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
/**
 *  @file       ti/sdo/fc/ires/tiledmemory/ires_tiledmemory.h
 *
 *  @brief      IRES PROTOCOL TILEDMEMORY Interface Definitions (Beta) -
 *              Allows algorithms to request and receive handles representing
 *              the TILEDMEMORY resource.
 */

/**
 *  @addtogroup ti_sdo_fc_ires_tiledmemory_IRES_TILEDMEMORY IRES TILEDMEMORY Protocol (Beta)
 *
 *              Allows algorithms to request and receive handles representing
 *              TILEDMEMORY resources.
 */

#ifndef ti_sdo_fc_ires_tiledmemory_IRES_TILEDMEMORY_
#define ti_sdo_fc_ires_tiledmemory_IRES_TILEDMEMORY_

/** @ingroup    ti_sdo_fc_ires_tiledmemory_IRES_TILEDMEMORY */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/xdas.h>
#include <ti/xdais/ires_common.h>
#include <ti/xdais/ires.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_TILEDMEMORY_PROTOCOLNAME       "ti.sdo.fc.ires.tiledmemory"

/**
 * @brief       Name to pass to Diags_setMask() to enable logging for
 *              TILEDMEMORY functions. For example,
 *                  Diags_setMask(TILEDMEMORY_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define TILEDMEMORY_MODNAME  "ti.sdo.fc.ires.tiledmemory"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for this resource
 */
static IRES_ProtocolRevision IRES_TILEDMEMORY_PROTOCOLREVISION = {1, 0, 0};

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_TILEDMEMORY_Obj *IRES_TILEDMEMORY_Handle;

/**
 *  @brief     Indicates whether requested/granted memory is of type 1D or 2D
 *
 *  @enumWarning
 */
typedef enum IRES_TILEDMEMORY_AccessDimension {
    IRES_TILEDMEMORY_1D = 0,
    IRES_TILEDMEMORY_2D = 1
} IRES_TILEDMEMORY_AccessDimension;


/**
 *  @brief     Indicates the size of the Tiler elements requested by the codec
 *
 *  @enumWarning
 */
typedef enum IRES_TILEDMEMORY_AccessUnit {

    IRES_TILEDMEMORY_RAW = 0,                   /**< Contiguously allocated
                                                     non-TILED memory */
    IRES_TILEDMEMORY_PAGE = 1,                  /**< PAGE TILED memory */
    IRES_TILEDMEMORY_8BIT = 2,                  /**< 8BIT TILED memory */
    IRES_TILEDMEMORY_16BIT = 3,                 /**< 16BIT TILED memory */
    IRES_TILEDMEMORY_32BIT = 4                  /**< 32BIT TILED memory */

} IRES_TILEDMEMORY_AccessUnit;

/**
 *  @brief      TILEDMEMORY Protocol Arguments definition.
 */
typedef struct IRES_TILEDMEMORY_ProtocolArgs {

    IRES_ProtocolArgs base;

    XDAS_UInt32 accessDimension;        /**<  Access dimension of requested
                                              memory.
                                              @sa IRES_TILEDMEMORY_AccessDimension */
    XDAS_UInt32 accessUnit;             /**< Access Unit for memory requested.
                                            @sa IRES_TILEDMEMORY_AccessUnit */

    /** size of 1st Dimension (width) in number of bytes */
    int sizeDim0;

    /** size of 2nd Dimension (height) in number of bytes when 2D access type */
    int sizeDim1;

    /** alignment in bytes for the memory base address to be allocated */
    int alignment;

} IRES_TILEDMEMORY_ProtocolArgs;

/**
 *  @brief          IRES_TILEDMEMORY_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource.
 */
typedef struct IRES_TILEDMEMORY_Obj {

    IRES_Obj ires;
    XDAS_Void * info ;                  /**< RSVD for future use */
    XDAS_Void * memoryBaseAddress;      /**< Process-specific virtual base
                                         *   address of Tiler memory
                                         *   allocated.
                                         */
    XDAS_UInt32 isTiledMemory;          /**< Boolean value that identifies
                                         *   if returned memory is
                                         *   of type TILED memory or not.
                                         *
                                         *   Valid values for this field are
                                         *   XDAS_TRUE and XDAS_FALSE.
                                         *
                                         *   If XDAS_TRUE, accessUnit will
                                         *   describe the kind of TILED memory
                                         *   allocated.
                                         */
    XDAS_UInt32 accessUnit;             /**< Describes the kind of memory
                                         *   actually allocated in the TILER
                                         *   space of type,
                                         *
                                         *   @remarks   Requestor MUST check
                                         *              the type of returned
                                         *              memory to ensure it
                                         *              is suitable for its
                                         *              purpose.
                                         *   @sa IRES_TILEDMEMORY_AccessUnit
                                         */
    XDAS_Void * tilerBaseAddress;       /**< Base address of TILER on SOC */
    XDAS_Void * systemSpaceBaseAddress; /**< Tiler space base address of
                                         *    memory allocated
                                         */

} IRES_TILEDMEMORY_Obj;

/**
 * @brief           TILEDMEMORY Register Layout
 */
typedef struct IRES_TILEDMEMORY_RegisterLayer {

    int size;
    /* TBD */
} IRES_TILEDMEMORY_RegisterLayer;

/**
 * @brief       Static Resource Properties
 */
typedef struct IRES_TILEDMEMORY_Properties {

    int size;
} IRES_TILEDMEMORY_Properties;

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif
