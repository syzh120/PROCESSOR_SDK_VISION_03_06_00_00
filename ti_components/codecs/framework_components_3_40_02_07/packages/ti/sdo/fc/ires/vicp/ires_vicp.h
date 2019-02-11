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
 *  @file       ti/sdo/fc/ires/vicp/ires_vicp.h
 *
 *  @brief      IRES PROTOCOL VICP Interface Definitions -
 *              Allows algorithms to request and receive handles representing
 *              the VICP resource
 */

/**
 *  @addtogroup ti_sdo_fc_ires_vicp_IRES_VICP IRES VICP Protocol
 *
 *              Allows algorithms to request and receive handles representing
 *              VICP resources.
 */

#ifndef ti_sdo_fc_ires_vicp_IRES_VICP_
#define ti_sdo_fc_ires_vicp_IRES_VICP_

/** @ingroup    ti_sdo_fc_ires_vicp_IRES_VICP */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires_common.h>

/*
 * @brief  Maximum number of VICP resources(components) to be managed
 */
#define IRES_VICP_MAXRESOURCES  1

/**
 * @brief Name used to describe this protocol
 */
#define IRES_VICP_PROTOCOLNAME     "ti.sdo.fc.ires.vicp"

/**
 * @brief       Name to pass to Diags_setMask() to enable logging for VICP
 *              functions. For example,
 *                  Diags_setMask(VICP_MODNAME"+EX1234567");
 *              turns on all Log statements in this module.
 *              Diags_setMask() must be called after initialization to take
 *              effect.
 */
#define VICP_MODNAME  "ti.sdo.fc.ires.vicp"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for this resource
 */
static IRES_ProtocolRevision IRES_VICP_PROTOCOLREVISION = {1, 0, 0};

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_VICP_Obj *IRES_VICP_Handle;

/**
 *  @brief      VICP Protocol Arguments definition.
 */
typedef struct IRES_VICP_ProtocolArgs {

    int size;                   /**< Size of this structure. */
    IRES_RequestMode mode;      /* persistent or scratch resource requested */
    short requestIMX;           /* value of 1 to indicate resource requested,
                                   0 otherwise */
    short requestVLCD;
    short requestSEQ;

} IRES_VICP_ProtocolArgs;

/**
 *  @brief          IRES_VICP_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource
 */
typedef struct  IRES_VICP_Obj {

    IRES_Obj ires;
    short assignedIMX;
    short assignedVLCD;
    short assignedSEQ;

} IRES_VICP_Obj;


/*
 * @brief           VICP Register Layout
 */
typedef struct IRES_VICP_Registers {

    int size;   /**< Size of this structure. */

    unsigned char *vicp_umap1_base;
    unsigned char *vicp_cfg_base;

    unsigned char *imgBuf_base;
    unsigned char *imgBufA_base;
    unsigned char *imgBufB_base;
    unsigned char *imxCoeffBuff_base;
    unsigned char *imxCmdBuf_base;
    unsigned char *vlcdDataBuf_base;
    unsigned char *qiqBuf_base;
    unsigned char *vlcdBuf_base;
    unsigned char *seqProgMem_base;
    unsigned char *seqDataMem_base;

    unsigned int imgBuf_length;
    unsigned int imgBufA_length;
    unsigned int imgBufB_length;
    unsigned int imxCoeffBuff_length;
    unsigned int imxCmdBuf_length;
    unsigned int vlcdDataBuf_length;
    unsigned int qiqBuf_length;
    unsigned int vlcdBuf_length;
    unsigned int seqProgMem_length;
    unsigned int seqDataMem_length;

    /* . . . */

} IRES_VICP_Registers;


/*
 * @brief       Static Resource Properties
 */
typedef struct IRES_VICP_Properties {

    int size;

    IRES_VICP_Registers *globalRegs;

} IRES_VICP_Properties;


#ifdef __cplusplus
}
#endif /* extern "C" */


/*@}*/

#endif
