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


#ifndef _RADAR_FFT_PRIV_H_
#define _RADAR_FFT_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include <include/alg_fxns/radarFFT_if.h>
#include <include/alg_fxns/radarFFT_work_if.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct
{
    AlgorithmFxn_RadarFftCreateParams algLinkCreateParams;
    /** fft Algo Create Params  */

    UInt8        *intermediateBuf;
    /** intermediate Buff */

    UInt32       intermediateBufSize;
    /** intermediate Buff */

    RadarFftWork_CreateInArgs *pCreateInArgs;
    RadarFftWork_CreateOutArgs *pCreateOutArgs;
    RadarFftWork_ProcessInArgs *pProcessInArgs;
    RadarFftWork_ProcessOutArgs *pProcessOutArgs;
    RadarFftWork_DeleteInArgs *pDeleteInArgs;

    UInt32 createInArgsSize;
    UInt32 createOutArgsSize;
    UInt32 processInArgsSize;
    UInt32 processOutArgsSize;
    UInt32 deleteInArgsSize;

    System_WorkObjId createWorkObjId;
    System_WorkObjId processWorkObjId;
    System_WorkObjId deleteWorkObjId;

    UInt32 workCpuId;

    UInt32 imgFrameWidth[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_NUM_PROFILE];
    /**< Width of frame which is to be output by the algorithm function */
    UInt32 imgFrameHeight[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_NUM_PROFILE];
    /**< Height of frame which is to be output by the algorithm function */

    UInt32 numPoints[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_NUM_PROFILE];
    /**< Number of points  */
    UInt32 numLines[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_NUM_PROFILE];
    /**< Enable Windowing */
    UInt32 numAntennas[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_NUM_PROFILE];
    /**< Enable Windowing */

    UInt8 numValidBits[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Number of valid bits in input data. If numValidBits is 16 then sign
     *   extension is disabled
     */

    UInt32 inBufAddrOffset[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Offset by which the input buffer address should be offsetted.
     *   Used typically when the chirp profile is enabled in the beginning of
     *   the line.
     */
    UInt32 offsetBwAntennas[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_CONFIG][RADAR_FFT_MAX_NUM_PROFILE];
    /**< Offset between antenna data. */
    UInt32 offsetBwAntennas1[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_CONFIG][RADAR_FFT_MAX_NUM_PROFILE];
    /**< Additional offset parameter by which the algorithm will understand the
    *   input data.
    */
    UInt32 irregularityFrequency[SYSTEM_MAX_CH_PER_OUT_QUE][RADAR_FFT_MAX_CONFIG][RADAR_FFT_MAX_NUM_PROFILE];
    /**< This field is to indicate after how many antenna there is an
     *   irregularity in offsetBwAntennas.
     *   A value of zero will assume a regular case where all the offset
     *   between antennas are the same.
     *   For example if the data is arranged as shown bellow
     *   A0xxxxA1xxxxA2xxxxyyyy
     *   A3xxxxA4xxxxA5xxxxyyyy
     *
     *   Here Ak represents antenna data for a particular antenna and it will
     *   have range number of samples in it. For the above example following
     *    would be the values of above parameters
     *   irregularityFrequency = 2,
     *   offsetBwAntennas  = xxxx
     *   offsetBwAntennas1 = A2 + xxxx + yyyy
     */
} AlgorithmFxn_RadarFftObj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

void * AlgorithmFxn_RadarFftCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams);

Int32 AlgorithmFxn_RadarFftProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf);

Int32 AlgorithmFxn_RadarFftControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams);

Int32 AlgorithmFxn_RadarFftDelete(void *alg_handle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
