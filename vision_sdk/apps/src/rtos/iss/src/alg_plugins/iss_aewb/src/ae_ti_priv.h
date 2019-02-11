/******************************************************************************
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
******************************************************************************/

/*
 *  ======== ae_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for AE
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the AE algorithm.
 */
#ifndef AE_TI_PRIV_
#define AE_TI_PRIV_

#define RY    0x4d
#define GY    0x96
#define BY    0x1d

typedef struct AE_TI_Obj {
    IALG_Obj   alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32 numRanges;
    IAE_Range exposureTimeRange[IAE_MAX_RANGES];
    XDAS_UInt32 exposureTimeStepSize;
    IAE_Range apertureLevelRange[IAE_MAX_RANGES];
    IAE_Range sensorGainRange[IAE_MAX_RANGES];
    IAE_Range ipipeGainRange[IAE_MAX_RANGES];
    IAE_Range targetBrightnessRange;
    XDAS_UInt32 targetBrightness;
    XDAS_UInt32 thrld;
    XDAS_Int32 avgY;
    XDAS_Int32 numHistory;
    XDAS_Int32 numSmoothSteps;
    XDAS_Int32 *historyBrightness;
    XDAS_UInt32 curBrightness;
    XDAS_Int32  curExposureTime;
    XDAS_Int32  curApertureLevel;
    XDAS_Int32  curSensorGain;
    XDAS_Int32  curIpipeGain;
    XDAS_Bool   locked;
    XDAS_Int32  lockCnt;
    IAEWB_Ae prevAE;
} AE_TI_Obj;

extern Int AE_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int AE_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int AE_TI_init(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 AE_TI_process(IAE_Handle h, IAE_InArgs *inArgs, IAE_OutArgs *outArgs,
    IAEWB_Rgb *rgbData, XDAS_UInt8 *weight, void *customData);

extern XDAS_Int32 AE_TI_control(IAE_Handle handle,
    IAE_Cmd id, IAE_DynamicParams *params, IAE_Status *status);

#endif

