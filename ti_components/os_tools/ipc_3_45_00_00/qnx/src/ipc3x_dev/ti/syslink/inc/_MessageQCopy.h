/**
 *  @file   _MessageQCopy.h
 *
 *  @brief      Defines MessageQCopy module.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2011-2012, Texas Instruments Incorporated
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


#ifndef MESSAGEQCOPY_H_0xded2
#define MESSAGEQCOPY_H_0xded2

/* Standard headers */
#include <_MultiProc.h>

#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    MessageQCopy_MODULEID
 *  @brief  Unique module ID.
 */
#define MessageQCopy_MODULEID               (0xded2)

/*! Version setting */
#define MessageQCopy_HEADERVERSION   (UInt) 0x2000

/*!
 *  @brief  Structure defining config parameters for the MessageQCopy module.
 */
typedef struct MessageQCopy_Config_tag {
    UInt32 intId[MultiProc_MAXPROCESSORS];
    /*!< Mailbox interrupt ID */
} MessageQCopy_Config;

/* =============================================================================
 *  APIs
 * =============================================================================
 */
/*!
 *  @brief      Function to get the default configuration for the MessageQCopy
 *              module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to MessageQCopy_setup filled in by the
 *              MessageQCopy module with the default parameters. If the user
 *              does not wish to make any change in the default parameters, this
 *              API is not required to be called.
 *
 *  @param      cfg     Pointer to the MessageQCopy module configuration
 *                      structure in which the default config is to be returned.
 *
 *  @sa         MessageQCopy_setup
 */
Void MessageQCopy_getConfig (MessageQCopy_Config * cfg);

/*!
 *  @brief      Function to setup the MessageQCopy module.
 *
 *              This function sets up the MessageQCopy module. This function
 *              must be called before any other instance-level APIs can be
 *              invoked. Module-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then MessageQCopy_getConfig can be called to get the
 *              configuration filled with the default values. After this, only
 *              the required configuration values can be changed. If the user
 *              does not wish to make any change in the default parameters, the
 *              application can simply call MessageQCopy with NULL parameters.
 *              The default parameters would get automatically used.
 *
 *  @param      cfg   Optional MessageQCopy module configuration. If provided as
 *                    NULL, default configuration is used.
 *
 *  @sa         MessageQCopy_destroy
 *              GateSpinlock_create
 *              Memory_alloc
 */
Int MessageQCopy_setup (const MessageQCopy_Config * cfg);

/* Function to destroy the MessageQCopy module. */
Int MessageQCopy_destroy (void);

/* Calls the SetupProxy to setup the MessageQ transports. */
Int
MessageQCopy_attach (UInt16 remoteProcId, Ptr sharedAddr, UInt16 startId);

/* Calls the SetupProxy to detach the MessageQ transports. */
Int
MessageQCopy_detach (UInt16 remoteProcId);

/* Function to run the MessageQCopy test. */
Int MessageQCopy_runtest (UInt32 testNo);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


#endif /* MESSAGEQCOPY_H_0xded2 */
