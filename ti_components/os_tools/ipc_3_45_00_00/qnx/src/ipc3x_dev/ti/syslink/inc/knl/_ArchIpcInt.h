/**
 *  @file   _ArchIpcInt.h
 *
 *  @brief      Defines for for Interrupt based architecture interface
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2009, Texas Instruments Incorporated
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


#if !defined (ARCHIPCINTDEFS_INTERRUPT_H)
#define ARCHIPCINTDEFS_INTERRUPT_H

/* OSAL headers */
#include <OsalIsr.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Function pointer types
 * =============================================================================
 */

/*!
 *  @brief  Callback function type. Returns whether interrupt has been handled.
 */
typedef Bool (*ArchIpcInt_CallbackFxn) (UInt32 msg, Ptr fxnArgs);


/*!
 *  @brief  This type registers the interrupt service routine
 *
 */
typedef Int32   (*ArchIpcInt_InterruptRegister)(UInt16                 procId,
                                                UInt32                 intId,
                                                ArchIpcInt_CallbackFxn fxn,
                                                Ptr                    fxnArgs);


/*!
 *  @brief  This type unregisters the interrupt service routine
 *
 */
typedef Int32   (*ArchIpcInt_InterruptUnregister)(UInt16 procId);


/*!
 *  @brief  This type defines the function to enable interrupt
 *
 */
typedef Void   (*ArchIpcInt_InterruptEnable)    (UInt16 procId, UInt32 intId);

/*!
 *  @brief  This type defines the function to disable interrupt
 *
 */
typedef Void   (*ArchIpcInt_InterruptDisable)   (UInt16 procId, UInt32 intId);

/*!
 *  @brief  This type defines the function to wait till interrupt is cleared
 *
 */
typedef Int32  (*ArchIpcInt_WaitClearInterrupt) (UInt16 procId, UInt32 intId);

/*!
 *  @brief  This type defines the function to send interrupt
 *
 */
typedef Int32  (*ArchIpcInt_SendInterrupt)      (UInt16 procId,
                                                 UInt32 intId,
                                                 UInt32 value);
/*!
 *  @brief  This type defines the function to clear interrupt
 *
 */
typedef UInt32 (*ArchIpcInt_ClearInterrupt)     (UInt16 procId, UInt16 mboxNum);


/* =============================================================================
 *  Function table interface
 * =============================================================================
 */
/*!
 *  @brief  This type defines the function to clear interrupt
 *
 */
typedef struct ArchIpcInt_FxnTable_tag {
    ArchIpcInt_InterruptRegister    interruptRegister;
    /*!< interface function InterruptRegister  */
    ArchIpcInt_InterruptUnregister  interruptUnregister;
    /*!< interface function InterruptUnregister*/
    ArchIpcInt_InterruptEnable      interruptEnable;
    /*!< interface function InterruptEnable    */
    ArchIpcInt_InterruptDisable     interruptDisable;
    /*!< interface function InterruptDisable   */
    ArchIpcInt_WaitClearInterrupt   waitClearInterrupt;
    /*!< interface function WaitClearInterrupt */
    ArchIpcInt_SendInterrupt        sendInterrupt;
    /*!< interface function SendInterrupt      */
    ArchIpcInt_ClearInterrupt       clearInterrupt;
    /*!< interface function ClearInterrupt     */
} ArchIpcInt_FxnTable;


/* =============================================================================
 * ArchIpcInt structure
 * =============================================================================
 */
/*!
 *  @brief  Device specific object
 */
typedef struct ArchIpcInt_Object_tag {
    Bool                  isSetup;
    /*!< Indicates devices specific setup state. */
    ArchIpcInt_FxnTable * fxnTable;
    /*!< Function table for device specific APIs. */
    Ptr                   obj;
    /* Internal object */
} ArchIpcInt_Object ;


/*
 *  @brief  Extern declaration device specific object
 */
extern ArchIpcInt_Object ArchIpcInt_object;

#if defined (__cplusplus)
}
#endif


#endif  /* !defined (ARCHIPCINTDEFS_INTERRUPT_H) */
