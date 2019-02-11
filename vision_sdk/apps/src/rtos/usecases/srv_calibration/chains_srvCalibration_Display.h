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


#ifndef CHAINS_SRVCALIBRATION_H_
#define CHAINS_SRVCALIBRATION_H_

/*******************************************************************************
    DEFINES
*******************************************************************************/
#define ISP_OUTPUT_NUM_BUFFERS                  (4U)

#define SRV_CAPT_SENSOR_AR140_WIDTH             (1280U)
#define SRV_CAPT_SENSOR_AR140_HEIGHT            (800U)
#define SRV_CAPT_SENSOR_OV10640_WIDTH           (1280U)
#define SRV_CAPT_SENSOR_OV10640_HEIGHT          (720U)

/* Maximum no of times 2D Pers Mat Update to be performed */
#define MAX_NUM_2D_PERSMAT_UPDATE               (10U)

/**< CSI2 Clock Speed */
#define CAPTURE_UB964_CSI2_CLOCK                (800U)

/**< Number of buffers to allocate per channel */
#define CAPTURE_NUM_BUF_PER_CH                  (4U)

/*******************************************************************************
    STRUCTURES
*******************************************************************************/
/**
 *******************************************************************************
 *
 *  \brief  chains_srvCalibration_DisplayAppObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_srvCalibration_issObj ucIss;
    chains_srvCalibration_vipObj ucVip;
    chains_srvCalibration_csi2CalObj ucCsi2Cal;
    chains_srvCalibration_avbObj ucAvb;
    chains_srvCalibration_csi2Cal_issRszObj ucCsi2CalIssRsz;

    UInt32  displayWidth;
    UInt32  displayHeight;
    Chains_Ctrl *chainsCfg;
    UInt32 yuvDumpCount;
    UInt32 imgSize;
    Ptr dumpFramesDmaObj;

    Chain_Common_SRV_CalibrationPrm calibrationPrm;
    Chains_CaptureIntf captureIntf;

    UInt32 grpxSrcLinkId;

    UInt32  numCsi2Ch;
    UInt32  numLanesOnPhy0Csi2; /* Valid values are 2 for 2 lanes, any other
                                    integer for 4 lanes */
    VidSensor_CreateParams sensorCreateParam;
    VidSensor_CreateStatus sensorCreateStatus;

#ifdef ISS_INCLUDE
    IssIspConfigurationParameters ispConfig;
    IssM2mSimcopLink_ConfigParams simcopConfig;
    vpsissldcConfig_t ldcCfg;
    vpsissvtnfConfig_t vtnfCfg;

    AppUtils_Obj appSensInfo;
#endif

    Bsp_PlatformSocId socId;

} chains_srvCalibration_DisplayAppObj;

#endif /* CHAINS_SRVCALIBRATION_H_ */
