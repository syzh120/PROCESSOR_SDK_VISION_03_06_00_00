/**
 *  @file   IGateMPSupport.h
 *
 *  @brief      Interface implemented by all multiprocessor gates.
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


#ifndef __IGATEMPSUPPORT_H__
#define __IGATEMPSUPPORT_H__


#if defined (__cplusplus)
extern "C" {
#endif


/* -----------------------------------------------------------------------------
 *  Macros
 * -----------------------------------------------------------------------------
 */
/*! Invalid Igate */
#define IGateMPSupport_NULL             (IGateProvider_Handle)0xFFFFFFFF

/*!
 *  ======== IGateProvider_Q_BLOCKING ========
 *  Blocking quality
 *
 *  Gates with this "quality" may cause the calling thread to block;
 *  i.e., suspend execution until another thread leaves the gate.
 */
#define IGateMPSupport_Q_BLOCKING 1

/*!
 *  ======== IGateProvider_Q_PREEMPTING ========
 *  Preempting quality
 *
 *  Gates with this "quality" allow other threads to preempt the thread
 *  that has already entered the gate.
 */
#define IGateMPSupport_Q_PREEMPTING 2

/*!
 *  ======== IGateMPSupport_SuperParams ========
 *  Object embedded in other Gate modules. (Inheritance)
 */
#define IGateMPSupport_SuperParams                                             \
        Bits32 resourceId;                                                         \
        Bool   openFlag;                                                           \
        UInt16 regionId;                                                           \
        Ptr    sharedAddr

/*!
 *  ======== IGateMPSupport_ParamsInitializer ========
 *  All other GateMP modules inherit this.
 */
#define IGateMPSupport_Inherit(X)                                              \
typedef enum X##_LocalProtect {                                                \
        X##_LocalProtect_NONE      = 0,                                            \
        X##_LocalProtect_INTERRUPT = 1,                                            \
        X##_LocalProtect_TASKLET   = 2,                                            \
        X##_LocalProtect_THREAD    = 3,                                            \
        X##_LocalProtect_PROCESS   = 4                                             \
} X##_LocalProtect;

/*!
 *  ======== IGateMPSupport_ParamsInitializer ========
 * Paramter initializer.
 */
#define IGateMPSupport_ParamsInitializer(x)                                    \
        (x)->resourceId = 0;                                                       \
        (x)->openFlag   = TRUE;                                                    \
        (x)->regionId   = 0;                                                       \
        (x)->sharedAddr = NULL



/* -----------------------------------------------------------------------------
 *  Structs & Enums
 * -----------------------------------------------------------------------------
 */
typedef enum IGateMPSupport_LocalProtect {
        IGateMPSupport_LocalProtect_NONE      = 0,
        IGateMPSupport_LocalProtect_INTERRUPT = 1,
        IGateMPSupport_LocalProtect_TASKLET   = 2,
        IGateMPSupport_LocalProtect_THREAD    = 3,
        IGateMPSupport_LocalProtect_PROCESS   = 4
} IGateMPSupport_LocalProtect;


typedef struct IGateMPSupport_Params {
        Bits32 resourceId;
        Bool   openFlag;
        UInt16 regionId;
        Ptr    sharedAddr;
} IGateMPSupport_Params;

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* ifndef __IGATEMPSUPPORT_H__ */
