/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
} MultiProc_Config;

/* =============================================================================
 *  APIs
 * =============================================================================
 */
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
