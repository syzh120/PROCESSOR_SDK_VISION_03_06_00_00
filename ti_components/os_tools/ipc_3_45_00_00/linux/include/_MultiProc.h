/*
 *  Copyright (c) 2008-2015 Texas Instruments Incorporated - http://www.ti.com
 *  All rights reserved.
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
 */
/** ============================================================================
 *  @file   _MultiProc.h
 *
 *  @brief  Header file for_MultiProc on HLOS side
 *  ============================================================================
 */


#ifndef _MULTIPROC_H_0XB522
#define _MULTIPROC_H_0XB522


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @brief  Max name length for a processor name.
 */
#define MultiProc_MAXNAMELENGTH 32

/*!
 *  @brief  Max number of processors supported.
 */
#define MultiProc_MAXPROCESSORS 10


/*!
 *  @brief  Configuration structure for MultiProc module
 */
typedef struct MultiProc_Config_tag {
    Int32  numProcessors;
    /*!< Max number of procs for particular system */
    Char   nameList [MultiProc_MAXPROCESSORS][MultiProc_MAXNAMELENGTH];
    /*!< Name List for processors in the system */
    Int32  rprocList[MultiProc_MAXPROCESSORS];
    /*!< Linux "remoteproc index" for processors in the system */
    UInt16 id;
    /*!< Local Proc ID. This needs to be set before calling any other APIs */
    UInt16 numProcsInCluster;
    /*!< number of processors in the cluster */
    UInt16 baseIdOfCluster;
    /*!< processor ID of first entry in cluster */
} MultiProc_Config;

/* =============================================================================
 *  APIs
 * =============================================================================
 */

/* Internal variable to enable/disable tracing throughout MultiProc */
extern Bool _MultiProc_verbose;

/*!
 *  @brief	Get the default configuration for the MultiProc module.
 *
 *		This function can be called by the application to setup and get
 *		configuration parameter for MultiProc with the default parameters.
 *
 *  @param	cfg	   Pointer to the MultiProc module configuration
 *			   structure in which the default config is to be
 *			   returned.
 */
Void MultiProc_getConfig (MultiProc_Config * cfg);

/*!
 *  @brief	Initialize the configuration for the MultiProc module.
 *
 *		This function is called to initialize the configuration for
 *              MultiProc.
 *
 *  @param	cfg	   Pointer to a populated MultiProc configuration
 *			   structure.
 */
Void _MultiProc_initCfg(MultiProc_Config * cfg);

/* This exported from daemon/MultiProcCfg_<PLATFORM>.c: */
extern MultiProc_Config _MultiProc_cfg;

#if defined (__cplusplus)
}
#endif

#endif
