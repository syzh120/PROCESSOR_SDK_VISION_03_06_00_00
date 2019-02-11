/**
 *  @file   Gate.h
 *
 *  @brief      Critical section support.
 *
 *  Gates are used by clients to protect concurrent access to critical
 *  data structures.  Critical data structures are those that must be
 *  updated by at most one thread at a time.  All code that needs access
 *  to a critical data structure "enters" a gate (that's associated with the
 *  data structure) prior to accessing the data, modifies the data structure,
 *  then "leaves" the gate.
 *
 *  A gate is responsible for ensuring that at most one thread at a time
 *  can enter and execute "inside" the gate.  There are several
 *  implementations of gates, with different system executation times and
 *  latency tradoffs.  In addition, some gates must not be entered by certain
 *  thread types; e.g., a gate that is implemented via a "blocking" semaphore
 *  must not be called by an interrupt service routine (ISR).
 *
 *  A module can be declared "gated" by adding the `@Gated` attribute to the
 *  module's XDC spec file.  A "gated" module is assigned a module-level gate
 *  at the configuration time, and that gate is then used to protect critical
 *  sections in the module's target code. A module-level gate is an instance of
 *  a module implementing `{@link IGateProvider}` interface. However, gated
 *  modules do not access their module-level gates directly. They use this
 *  module to access transparently their module-level gate.
 *
 *  Application code that is not a part of any module also has a
 *  module-level gate, configured through the module `{@link Main}`.
 *
 *  Each gated module can optionally create gates on an adhoc basis at
 *  runtime using the same gate module that was used to create the module
 *  level gate.
 *
 *  Gates that work by disabling all preemption while inside a gate can be
 *  used to protect data structures accessed by ISRs and other
 *  threads.  But, if the time required to update the data structure is not
 *  a small constant, this type of gate may violate a system's real-time
 *  requirements.
 *
 *  Gates have two orthogonal attributes: "blocking" and "preemptible".
 *  In general, gates that are "blocking" can not be use by code that is
 *  called by ISRs and gates that are not "preemptible" should only be used to
 *  to protect data manipulated by code that has small constant execution
 *  time.
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


#ifndef GATE_H_0xAF6F
#define GATE_H_0xAF6F

#include <ti/syslink/utils/IGateProvider.h>

#if defined (__cplusplus)
extern "C" {
#endif

extern IGateProvider_Handle Gate_systemHandle;

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to enter a Gate */
IArg  Gate_enterSystem (void);

/* Function to leave a Gate */
Void Gate_leaveSystem (IArg key);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* GATE_H_0xAF6F */
