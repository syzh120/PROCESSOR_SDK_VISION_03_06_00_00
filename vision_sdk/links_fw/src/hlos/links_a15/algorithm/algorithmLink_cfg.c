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

/**
 *******************************************************************************
 * \file algorithmLink_cfg.c
 *
 * \brief  This file has some configuration of algorithm link
 *
 *         Functions in this file will be called by use case or application
 *
 * \version 0.0 (March 2016) : [SN] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include "algorithmLink_priv.h"
#include "algorithmLink_cfg.h"
#include <include/link_api/algorithmLink.h>

#ifdef ALG_framecopy
#include <include/alglink_api/algorithmLink_frameCopy.h>
#endif

/*******************************************************************************
 *  Declaring gAlgorithmLinkFuncTable for the current core
 *******************************************************************************
 */
AlgorithmLink_FuncTable gAlgorithmLinkFuncTable[ALGORITHM_LINK_ALG_MAXNUM];

/**
 *******************************************************************************
 * \brief Display Link object, stores all link related information
 *******************************************************************************
 */
AlgorithmLink_Obj gAlgorithmLink_obj[ALGORITHM_LINK_OBJ_MAX];

/**
 *******************************************************************************
 *
 * \brief Initializing alg plugins
 *
 *        This function needs to be called by the use case / application.
 *        This function will inturn call the algorithm specific init functions
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_initAlgPlugins(void)
{
    memset(gAlgorithmLinkFuncTable, 0, sizeof(gAlgorithmLinkFuncTable));

    /** For all alorithms on A15 */
#ifdef ALG_framecopy
    AlgorithmLink_FrameCopy_initPlugin();
#endif

#ifdef ALG_openclframecopy
    AlgorithmLink_OpenCLFrameCopy_initPlugin();
#endif

#ifdef ALG_opencvcanny
    AlgorithmLink_OpenCVCanny_initPlugin();
#endif

#ifdef ALG_opencvopencldilation
    AlgorithmLink_OpenCVOpenCLDilation_initPlugin();
#endif

    return SYSTEM_LINK_STATUS_SOK;
}

/* Nothing beyond this point */
