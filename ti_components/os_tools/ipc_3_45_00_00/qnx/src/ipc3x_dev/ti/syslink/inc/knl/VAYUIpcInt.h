/**
 *  @file   VAYUIpcInt.h
 *
 *  @brief      Header file for VAYU DSP IPC interrupts
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




#if !defined (VAYUIPCINT_H)
#define VAYUIPCINT_H


#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */


/*!
 *  @def    VAYUIPCINT_MODULEID
 *  @brief  Module ID for Notify.
 */
#define VAYUIPCINT_MODULEID           (UInt16) 0x5f85


/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    VAYUIPCINT_STATUSCODEBASE
 *  @brief  Status code base for VAYUIPCINT module.
 */
#define VAYUIPCINT_STATUSCODEBASE    (VAYUIPCINT_MODULEID << 12u)

/*!
 *  @def    VAYUIPCINT_MAKE_FAILURE
 *  @brief  Macro to make error code.
 */
#define VAYUIPCINT_MAKE_FAILURE(x)    ((Int)(  0x80000000              \
                                    | (VAYUIPCINT_STATUSCODEBASE + (x))))

/*!
 *  @def    VAYUIPCINT_MAKE_SUCCESS
 *
 *  @brief  Macro to make success code.
 */
#define VAYUIPCINT_MAKE_SUCCESS(x)(VAYUIPCINT_STATUSCODEBASE +(x))

/*!
 *  @def    VAYUIPCINT_E_FAIL
 *  @brief  Generic failure.
 */
#define VAYUIPCINT_E_FAIL              VAYUIPCINT_MAKE_FAILURE(1)

/*!
 *  @def    VAYUIPCINT_E_INVALIDSTATE
 *  @brief  Generic failure.
 */
#define VAYUIPCINT_E_INVALIDSTATE      VAYUIPCINT_MAKE_FAILURE(2)

/*!
 *  @def    VAYUIPCINT_E_MEMORY
 *  @brief  Out of memory error.
 */
#define VAYUIPCINT_E_MEMORY            VAYUIPCINT_MAKE_FAILURE(3)
/*!
 *  @def    VAYUIPCINT_SUCCESS
 *  @brief  Generic failure.
 */
#define VAYUIPCINT_SUCCESS             VAYUIPCINT_MAKE_SUCCESS(0)
/*!
 *  @def    VAYUIPCINT_S_ALREADYSETUP
 *  @brief  Set up already called.
 */
#define VAYUIPCINT_S_ALREADYSETUP      VAYUIPCINT_MAKE_SUCCESS(1)

/*!
 *  @def    VAYUIPCINT_S_ALREADYREGISTERED
 *  @brief  ISR already registered.
 */
#define VAYUIPCINT_S_ALREADYREGISTERED VAYUIPCINT_MAKE_SUCCESS(2)
/* =============================================================================
 * Structures and enums
 * =============================================================================
 */
typedef struct VAYUIpcInt_Config_tag {
    UInt16    procId;
    /*!< Processor id of destination processor. */
    UInt32    recvIntId;
    /* recevive interrupt id */
} VAYUIpcInt_Config ;


/* =============================================================================
 * APIs
 * =============================================================================
 */
/* Function to setup interrupts for omap3530 */
Void VAYUIpcInt_setup (VAYUIpcInt_Config * cfg);

/* Function to destroy interrupt setup for omap3530 */
Void VAYUIpcInt_destroy (Void);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif  /* !defined (VAYUIPCINT_H) */
