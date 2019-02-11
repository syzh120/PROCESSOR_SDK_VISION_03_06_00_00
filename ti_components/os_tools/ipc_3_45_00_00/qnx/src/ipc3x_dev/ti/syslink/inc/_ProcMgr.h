/**
 *  @file   _ProcMgr.h
 *
 *  @brief      Processor Manager
 *
 *              Defines internal functions to be called by system integrators.
 *
 *
 */
/*
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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



#ifndef _ProcMgr_H_0xf2ba
#define _ProcMgr_H_0xf2ba


/* Module headers */
#include <ti/syslink/SysLink.h>
#include <ti/syslink/ProcMgr.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @def    ProcMgr_MODULEID
 *  @brief  Module ID for ProcMgr.
 */
#define ProcMgr_MODULEID           (UInt16) 0xf2ba

/*!
 *  @brief  Maximum name length for ProcMgr module strings.
 */
#define ProcMgr_MAX_STRLEN 32u


/*!
 *  @brief  Module configuration structure.
 */
typedef struct ProcMgr_Config {
    Ipc_MemoryMap * sysMemMap;
    /*!< Ipc memory map. */
} ProcMgr_Config;

/*!
 *  @brief  Configuration parameters specific to the slave ProcMgr instance.
 */
typedef struct ProcMgr_Params_tag {
    Ptr    procHandle;
    /*!< Handle to the Processor object associated with this ProcMgr. */
    Ptr    loaderHandle;
    /*!< Handle to the Loader object associated with this ProcMgr. */
    Ptr    pwrHandle;
    /*!< Handle to the PwrMgr object associated with this ProcMgr. */
    Char   rstVectorSectionName [ProcMgr_MAX_STRLEN];
    /*!< Reset vector section name */
} ProcMgr_Params ;


/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Function to get the default configuration for the ProcMgr module. */
Void ProcMgr_getConfig (ProcMgr_Config * cfg);

/* Function to setup the ProcMgr module. */
Int ProcMgr_setup (ProcMgr_Config * cfg);

/* Function to destroy the ProcMgr module. */
Int ProcMgr_destroy (Void);

/* Function to initialize the parameters for the ProcMgr instance. */
Void ProcMgr_Params_init (ProcMgr_Handle handle, ProcMgr_Params * params);

/* Function to create a ProcMgr object for a specific slave processor. */
ProcMgr_Handle ProcMgr_create (UInt16 procId, const ProcMgr_Params * params);

/* Function to delete a ProcMgr object for a specific slave processor. */
Int ProcMgr_delete (ProcMgr_Handle * handlePtr);

/* Function to translate between two types of address spaces. (does not take
 * lock internally) */
Int _ProcMgr_translateAddr (ProcMgr_Handle   handle,
                            Ptr *            dstAddr,
                            ProcMgr_AddrType dstAddrType,
                            Ptr              srcAddr,
                            ProcMgr_AddrType srcAddrType);

/* Function that maps the specified slave address to master address space.
 * (does not take lock internally) */
Int _ProcMgr_map (ProcMgr_Handle     handle,
                  ProcMgr_MapMask    mapMask,
                  ProcMgr_AddrInfo * addrInfo,
                  ProcMgr_AddrType   srcAddrType);

/* Function that unmaps the specified slave address from master address space.
 * (does not take lock internally) */
Int _ProcMgr_unmap (ProcMgr_Handle     handle,
                    ProcMgr_MapMask    mapMask,
                    ProcMgr_AddrInfo * addrInfo,
                    ProcMgr_AddrType   srcAddrType);

/* Function to copy system memory map */
Void _ProcMgr_configSysMap (ProcMgr_Config * cfg);

/* Function to copy instance params overrides */
Void _ProcMgr_saveParams (String params, Int len);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* _ProcMgr_H_0xf2ba */
