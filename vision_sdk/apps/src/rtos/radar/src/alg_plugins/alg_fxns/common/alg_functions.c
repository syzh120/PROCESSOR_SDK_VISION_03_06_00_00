/******************************************************************************
Copyright (c) [2012 - 2018] Texas Instruments Incorporated

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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 *
 * \file alg_functions.c
 *
 * \brief  This file implements the registration functions which are used to
 *         get the algorithm functions.
 *
 * \version 0.0 (Sept 2016) : [PG] First version
 *
 *******************************************************************************
*/
#include <system_cfg.h>
#include <include/common/alg_functions.h>

AlgRadarProcessFxns_FxnTable *AlgRadarProcessFxns_get(char *name)
{
    AlgRadarProcessFxns_FxnTable *fxns = NULL;

    #if defined (BUILD_DSP) || defined (BUILD_M4)
    #if defined (ALG_FXN_radardraw)
    if (strcmp(name, "ti.radar.draw") == 0)
    {
        AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDraw_getFunctions(void);
        fxns = AlgorithmFxn_RadarDraw_getFunctions();
    }
    #endif
    #endif

    #if defined (BUILD_DSP) || defined (BUILD_M4)
    #if defined (ALG_FXN_radardrawfftheatmap)
    if (strcmp(name, "ti.radar.drawfftheatmap") == 0)
    {
        AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDrawFFTHeatMap_getFunctions(void);
        fxns = AlgorithmFxn_RadarDrawFFTHeatMap_getFunctions();
    }
    #endif
    #endif

    #if defined (BUILD_DSP)
    #if defined (ALG_FXN_radardspprocess)
    if (strcmp(name, "ti.radar.dspprocess") == 0)
    {
        AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDspProcess_getFunctions(void);
        fxns = AlgorithmFxn_RadarDspProcess_getFunctions();
    }
    #endif
    #endif

    #if defined (BUILD_DSP) || defined (BUILD_M4) || defined (BUILD_A15)
    #if defined (ALG_FXN_radarfft2)
    if (strcmp(name, "ti.radar.fft") == 0)
    {
        AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarFft2_getFunctions(void);
        fxns = AlgorithmFxn_RadarFft2_getFunctions();
    }
    #endif
    #if defined (ALG_FXN_radarpeakdetect)
    if (strcmp(name, "ti.radar.pkDetect") == 0)
    {
        AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarPkDetect_getFunctions(void);
        fxns = AlgorithmFxn_RadarPkDetect_getFunctions();
    }
    #endif
    #if defined (ALG_FXN_radarbeamform)
    if (strcmp(name, "ti.radar.beamForm") == 0)
    {
        AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarBeamForm_getFunctions(void);
        fxns = AlgorithmFxn_RadarBeamForm_getFunctions();
    }
    #endif
    #endif

    #if defined (ALG_FXN_radarframecopy)
    if (strcmp(name, "ti.radar.framecopy") == 0)
    {
        AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarFrameCopy_getFunctions(void);
        fxns = AlgorithmFxn_RadarFrameCopy_getFunctions();
    }
    #endif

    return fxns;
}
