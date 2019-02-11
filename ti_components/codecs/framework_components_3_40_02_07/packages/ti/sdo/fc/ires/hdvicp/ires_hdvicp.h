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
 *  @file       ti/sdo/fc/ires/hdvicp/ires_hdvicp.h
 *
 *  @brief      IRES PROTOCOL HDVICP Interface Definitions -
 *              Allows algorithms to request and receive handles representing
 *              the HDVICP resource.
 */

/**
 *  @addtogroup ti_sdo_fc_ires_hdvicp_IRES_HDVICP IRES HDVICP Protocol
 *
 *              Allows algorithms to request and receive handles representing
 *              HDVICP resources.
 */

#ifndef ti_sdo_fc_ires_hdvicp_IRES_HDVICP_
#define ti_sdo_fc_ires_hdvicp_IRES_HDVICP_

/** @ingroup    ti_sdo_fc_ires_hdvicp_IRES_HDVICP */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires_common.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_HDVICP_PROTOCOLNAME     "ti.sdo.fc.ires.hdvicp"

/**
 * @brief       Name to pass to Diags_setMask() to enable logging for HDVICP
 *              functions. For example,
 *                  Diags_setMask(HDVICP_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define HDVICP_MODNAME  "ti.sdo.fc.ires.hdvicp"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for this resource
 */
static IRES_ProtocolRevision IRES_HDVICP_PROTOCOLREVISION = {1, 0, 2};

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_HDVICP_Obj *IRES_HDVICP_Handle;

/**
 * @brief       Type of resource that can be requested.
 */
typedef enum IRES_HDVICP_RequestType {

    IRES_HDVICP_ID_0 = 0,
    IRES_HDVICP_ID_1 = 1,
    IRES_HDVICP_ID_ANY = 2
} IRES_HDVICP_RequestType;

/**
 *  @brief      HDVICP Protocol Arguments definition.
 */
typedef struct IRES_HDVICP_ProtocolArgs {

   IRES_ProtocolArgs base;
   IRES_HDVICP_RequestType id;                  /**< ID of the HDVICP resource
                                                     being requested, could be
                                                     IRES_HDVICP_ID_0,
                                                     IRES_HDVICP_ID_1 or
                                                     IRES_HDVICP_ID_ANY */
} IRES_HDVICP_ProtocolArgs;

/**
 *  @brief          IRES_HDVICP_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource.
 */
typedef struct  IRES_HDVICP_Obj {

    IRES_Obj ires;
    Void * info ;                               /**< RSVD for future use */
    Int id;                                     /**< ID of the HDVICP being ,
                                                     granted, could be
                                                     IRES_HDVICP_ID_0 or
                                                     IRES_HDVICP_ID_1 */
    Void * registerBaseAddress ;                /**< Base address of reg space*/
    Void * memoryBaseAddress;                   /**< Mem address of mem space */
    unsigned int pscRegisterSpace;              /**< Base address of the PSC
                                                     and system module register                                                      space */
} IRES_HDVICP_Obj;


/**
 * @brief           HDVICP Register Layout
 */
typedef struct IRES_HDVICP_RegisterLayer {

    int size;
} IRES_HDVICP_RegisterLayer;


/**
 * @brief       Static Resource Properties
 */
typedef struct IRES_HDVICP_Properties {

    int size;
    IRES_HDVICP_RegisterLayer *globalRegs;      /* Register layer of HDVICP */
} IRES_HDVICP_Properties;

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif
