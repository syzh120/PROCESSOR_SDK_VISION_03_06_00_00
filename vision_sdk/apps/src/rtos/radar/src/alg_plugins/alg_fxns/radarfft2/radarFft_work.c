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

/**
 *******************************************************************************
 * \file    RadarFft.c
 *
 * \brief  This file contains algorithm functions for fft calculation.
 *
 * \version 0.0 (Sept 2016) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "include/alg_fxns/radarFFT_work_if.h"


static UInt32 RadarFftWork_create(
                RadarFftWork_CreateInArgs *pIn,
                RadarFftWork_CreateOutArgs *pOut
                )
{
    UInt32 numObj;
    FFT_TI_CreateParams     *pFftcreateParams;

    UTILS_assert(pIn!=NULL);
    UTILS_assert(pOut!=NULL);
    UTILS_assert(pIn->numObjs<=RADAR_FFT_MAX_CONFIG);

    for(numObj = 0; numObj < pIn->numObjs; numObj++)
    {
        pFftcreateParams = &pIn->fftcreateParams[numObj];

        /* Create alg and alloc memory reqd to alg */
        pOut->fftAlghandle[numObj] = AlgIvision_create(
                        &FFT_TI_VISION_FXNS,(IALG_Params *)(pFftcreateParams));
    }

    return 0;
}

static UInt32 RadarFftWork_delete(
                RadarFftWork_DeleteInArgs *pIn
                )
{
    UInt32 numObj;

    UTILS_assert(pIn!=NULL);
    UTILS_assert(pIn->numObjs<=RADAR_FFT_MAX_CONFIG);

    for(numObj = 0; numObj < pIn->numObjs; numObj++)
    {
        if(pIn->fftAlghandle[numObj] != NULL)
        {
            AlgIvision_delete(pIn->fftAlghandle[numObj]);
        }
    }

    return 0;
}

static UInt32 RadarFftWork_process(
                RadarFftWork_ProcessInArgs *pIn,
                RadarFftWork_ProcessOutArgs *pOut
                )
{
    UInt32 numObj;
    Int32 status = -1;
    RadarFftWork_ProcessInAlgArgs *pInAlgArgs;

    UTILS_assert(pIn!=NULL);
    UTILS_assert(pOut!=NULL);
    UTILS_assert(pIn->numObjs<=RADAR_FFT_MAX_CONFIG);

    for(numObj = 0; numObj < pIn->numObjs; numObj++)
    {
        pInAlgArgs = &pIn->inAlgArgs[numObj];

        if(numObj>0)
        {
            memcpy(
                &pInAlgArgs->inArgs.bufDescription,
                &pOut->outArgs[numObj-1].bufDescription,
                sizeof(FFT_TI_BufferDescriptor)
                );
        }

        if(pIn->fftAlghandle[numObj] != NULL)
        {
            #if 1
            status = AlgIvision_process(
                        pIn->fftAlghandle[numObj],
                        &pInAlgArgs->inBufs,
                        &pInAlgArgs->outBufs,
                        (IVISION_InArgs *)&pInAlgArgs->inArgs,
                        (IVISION_OutArgs *)&pOut->outArgs[numObj]
                        );
            #else
            status = 0;
            #endif
        }
    }

    return (UInt32)status;
}

UInt32 RadarFftWork_fxn(
                UInt16 workFxnId,
                UInt16 workCmdId,
                Void *pInArgs,
                UInt32 inArgsSize,
                Void *pOutArgs,
                UInt32 outArgsSize)
{
    UInt32 status = 0;

    if(workCmdId==RADAR_FFT_WORK_FXN_CMD_PROCESS)
    {
        status = RadarFftWork_process(pInArgs, pOutArgs);
    }
    else
    if(workCmdId==RADAR_FFT_WORK_FXN_CMD_CREATE)
    {
        status = RadarFftWork_create(pInArgs, pOutArgs);
    }
    else
    if(workCmdId==RADAR_FFT_WORK_FXN_CMD_DELETE)
    {
        status = RadarFftWork_delete(pInArgs);
    }

    return status;
}

Void RadarFftWork_registerFxns()
{
    System_workHandlerRegister(RADAR_FFT_WORK_FXN_ID, RadarFftWork_fxn);
}
