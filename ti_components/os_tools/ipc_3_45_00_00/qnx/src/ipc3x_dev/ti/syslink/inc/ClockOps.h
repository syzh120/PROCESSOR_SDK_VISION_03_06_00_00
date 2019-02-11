/**
 *  @file   ClockOps.h
 *
 *  @brief      Generic Clock interface header
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2008-2012, Texas Instruments Incorporated
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


#ifndef ClockOps_H
#define ClockOps_H

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */

/*!
 *  @def    ClockOps_S_ALREADYSETUP
 *  @brief  The module has been already setup
 */
#define ClockOps_S_ALREADYSETUP     1

/*!
 *  @def    ClockOps_S_SUCCESS
 *  @brief  Operation is successful.
 */
#define ClockOps_S_SUCCESS          0

/*!
 *  @def    ClockOps_E_FAIL
 *  @brief  Generic failure.
 */
#define ClockOps_E_FAIL             -1

/*!
 *  @def    ClockOps_E_INVALIDARG
 *  @brief  Argument passed to function is invalid.
 */
#define ClockOps_E_INVALIDARG       -2

/*!
 *  @def    ClockOps_E_MEMORY
 *  @brief  Operation resulted in memory failure.
 */
#define ClockOps_E_MEMORY           -3


/*!
 *  @def    ClockOps_E_INVALIDSTATE
 *  @brief  Module is not initialized.
 */
#define ClockOps_E_INVALIDSTATE     -4

/*!
 *  @def    ClockOps_E_OSFAILURE
 *  @brief  A failure occurred in an OS-specific call
 */
#define ClockOps_E_OSFAILURE        -5

/*!
 *  @def    ClockOps_E_RESOURCE
 *  @brief  Specified resource is not available
 */
#define ClockOps_E_RESOURCE         -6

/*!
 *  @def    ClockOps_E_HANDLE
 *  @brief  Invalid object handle specified
 */
#define ClockOps_E_HANDLE           -7

/* =============================================================================
 *  Function pointer types
 * =============================================================================
 */

/* Function to get handle to the given Clock. */
typedef Ptr (*ClockOps_getFxn)(String clkname);
/* Function to release a Clock. */
typedef Void (*ClockOps_putFxn)(Ptr clkHandle);
/* Function to enable Clock. */
typedef Int32 (*ClockOps_enableFxn)(Ptr clkHandle);
/* Function to disable a Clock. */
typedef Void (*ClockOps_disableFxn)(Ptr clkHandle);
/* Function to get speed of a Clock. */
typedef ULong (*ClockOps_getRateFxn)(Ptr clkHandle);
/* Function to set the speed of a Clock. */
typedef Int32 (*ClockOps_setRateFxn)(Ptr clkHandle, ULong rate);

/* =============================================================================
 *  Function table interface
 * =============================================================================
 */

/*!
 *  @brief  Function table interface for Clock.
 */
typedef struct ClockOps_FxnTable_tag {

    ClockOps_getFxn        get;
    /* Function to get handle to the given Clock. */
    ClockOps_putFxn        put;
    /* Function to release a Clock. */
    ClockOps_enableFxn     enable;
    /* Function to enable Clock. */
    ClockOps_disableFxn    disable;
    /* Function to disable a Clock. */
    ClockOps_getRateFxn    getRate;
    /* Function to get speed of a Clock. */
    ClockOps_setRateFxn       setRate;
    /* Function to set the speed of a Clock. */

}ClockOps_FxnTable;

/*
 *  Generic ClockOps object. This object defines the handle type for all
 *  ClockOps operations.
 */
struct ClockOps_Object_tag {
    ClockOps_FxnTable     clkFxnTable;
    /*!< Interface function table to plug into the generic Clock. */
    Ptr                   reserved;
    /*!< reserved. */
};

/* ClockOps Object */
typedef struct ClockOps_Object_tag ClockOps_Object;

/*!
 *  @brief  Defines ClockOps object handle
 */
typedef ClockOps_Object * ClockOps_Handle;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to get handle to a clock given its name */
Ptr ClockOps_get(ClockOps_Handle handle, String clkname);
/* Function to release a Clock. */
Void ClockOps_put(ClockOps_Handle handle, Ptr clkHandle);
/* Function to enable a clock. */
Int32 ClockOps_enable(ClockOps_Handle handle, Ptr clkHandle);
/* Function to disable a clock */
Void ClockOps_disable(ClockOps_Handle handle, Ptr clkHandle);
/* Function to get clock speed */
ULong ClockOps_getRate(ClockOps_Handle handle, Ptr clkHandle);
/* Function to set clock speed */
Int32 ClockOps_setRate(ClockOps_Handle handle, Ptr clkHandle, ULong rate);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* #ifdef ClockOps_H */
