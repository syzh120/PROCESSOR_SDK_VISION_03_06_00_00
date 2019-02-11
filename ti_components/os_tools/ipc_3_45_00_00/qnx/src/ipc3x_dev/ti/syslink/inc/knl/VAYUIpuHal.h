/**
 *  @file   VAYUIpuHal.h
 *
 *  @brief      Top-level header file for VAYUIPU COREX Hardware Abstraction Layer.
 *
 *              This module is responsible for handling device-specific
 *              operations.
 *              The implementation is specific to VAYUIPU COREX.
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2013, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */


#ifndef VAYUIPUHAL_H_0xbbed
#define VAYUIPUHAL_H_0xbbed


/* Module level headers */
#include <_ProcDefs.h>
#include <VAYUIpuHalMmu.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 *  See _ProcDefs.h
 * =============================================================================
 */

/*!
 *  @brief  Hardware Abstraction object.
 */
typedef struct VAYUIPU_HalObject_tag {
    UInt32                    cmBase;
    /*!< Virtual base address of the General Control module. */
    UInt32                    prmBase;
    /*!< Virtual base address of the General Control module. */
    UInt32                    mmuBase;
    /*!< Base address of the MMU module. */
    UInt32                    ctrlModBase;
    /*!< Base address of the control module. */
    UInt32                    procId;
    /*!< Processor ID. */
    VAYUIPU_HalMmuObject mmuObj;
    /*!< MMU abstraction. */
} VAYUIPU_HalObject;

/*!
 *  @brief  Hardware Abstraction object.
 */
typedef struct VAYUIPU_HalParams_tag {
    UInt16                    procId;
    /*!< ProcId of the IPU being created. */
} VAYUIPU_HalParams;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to initialize the HAL object */
Int VAYUIPU_halInit (Ptr * halObj, Ptr params);

/* Function to finalize the HAL object */
Int VAYUIPU_halExit (Ptr halObj);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* VAYUIpuHal_H_0xbbec */
