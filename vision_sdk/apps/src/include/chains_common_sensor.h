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
 *
 * \ingroup DEVICE_API
 * \defgroup CHAINS_SENSOR APIs for selecting the Sensor source for chain.
 *
 * \brief  APIs for selecting the required sensor source for chain.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file chains_common_sensor.h
 *
 * \brief APIs for selecting the required usecase chain.
 *
 * \version 0.0 (Jul 2017) : [CM] First version
 *
 *******************************************************************************
 */

#ifndef CHAINS_COMMON_SENSOR_H
#define CHAINS_COMMON_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
 typedef enum {
     CHAINS_CAPTURE_SRC_OV10635 = 0,
     /**< Capture source is OV 10635
      *   SUPPORTED on TDA2x EVM, TDA3x EVM
      */
     CHAINS_CAPTURE_SRC_HDMI_720P,
     /**< Capture source is HDMI in 720P resolution
      *   SUPPORTED on TDA2x EVM
      */
     CHAINS_CAPTURE_SRC_HDMI_1080P,
     /**< Capture source is HDMI in 1080P resolution
      *   SUPPORTED on TDA2x EVM
      */
     CHAINS_CAPTURE_SRC_AR0132RCCC,
     /**< Capture source is Aptina AR0132 RCCC sensor
      *   SUPPORTED on TDA2x MonsterCam Board
      */
     CHAINS_CAPTURE_SRC_AR0132ISP,
     /**< Capture source is Aptina AR0132 BAYER + External ISP sensor
      *   SUPPORTED on TDA2x MonsterCam Board
      */
     CHAINS_CAPTURE_SRC_OV10640_CSI2,
     /**< OV10640 sensor with CSI2 interface
      *   SUPPORTED on TDA3x EVM
      */
     CHAINS_CAPTURE_SRC_OV10640_PARALLEL,
     /**< OV10640 sensor with parallel interface
      *   SUPPORTED on TDA3x EVM
      */
     CHAINS_CAPTURE_SRC_AR0132BAYER_PARALLEL,
     /**< Capture source is Aptina AR0132 BAYER Parallel interface
      *   SUPPORTED on TDA3x EVM ONLY via Aptina Connector
      *   Only works with ISS related use-cases
      */

     CHAINS_CAPTURE_SRC_AR0132MONOCHROME_PARALLEL,
     /**< Capture source is Aptina AR0132 Monochrome Parallel interface
      *   SUPPORTED on TDA3x EVM ONLY via Aptina Connector
      *   Only works with ISS related use-cases
      */

     CHAINS_CAPTURE_SRC_AR0140BAYER_PARALLEL,
     /**< Capture source is Aptina AR0140 BAYER Parallel interface
      *   SUPPORTED on TDA3x EVM ONLY via Aptina Connector
      *   Only works with ISS related use-cases
      */
     CHAINS_CAPTURE_SRC_IMX224_CSI2,
     /**< Capture source is Sony IMX224 CSI interface
      *   SUPPORTED on TDA3x EVM ONLY LI module
      *   Only works with ISS related use-cases
      */

     CHAINS_CAPTURE_SRC_DM388,
     /**< Capture source is external DM388 chip giving out put on vout
      *   This is for TDA2x MonsterCam Board
      */

     CHAINS_CAPTURE_SRC_UB960_TIDA00262,
     /**< Capture source is UB960 aggregator, to which 1 or more (4) TIDA00262
      *     could be connected.
      *     Each TIDA00262 module, has AR0140AT video sensor
      */
     CHAINS_CAPTURE_SRC_OV10635_LVDS,
     /**< OV10635 using LVDS
      */
     CHAINS_CAPTURE_SRC_UB960_IMI,
     /**< Capture source is UB960 aggregator, to which 1 or more (4) IMI
      *     could be connected.
      *     Each IMI module, has OV10640 video sensor
      */

     CHAINS_CAPTURE_SRC_UB964_OV1063X,
     /**< Capture source is UB964 aggregator, to which 1 or more (4) SAT0088 &
      *     OV1063X / IMI could be connected.
      */
     CHAINS_CAPTURE_SRC_VIDDEC_TVP5158,
     /**< Capture source is Video Decoder TVP 5158
      *   SUPPORTED on TDA2x EVM
      */
     CHAINS_CAPTURE_SRC_OV2775_CSI2,
     /**< OV2775 sensor with CSI2 interface
      *   SUPPORTED on TDA3x EVM
      */
     CHAINS_CAPTURE_SRC_UB960_MARS_AR0143,
     /**< AR0143 sensor with UB913 MARS Module
      *   SUPPORTED on TDA3x EVM
      */
     CHAINS_CAPTURE_SRC_IMX290ISP,
     /**< Capture source is IMX290 + External ISP sensor */

     CHAINS_CAPTURE_SRC_TRULY_AVB_CAM,
     /**< Capture source is AVB Camera on TDA2Ex ETH SRV Board */

     CHAINS_CAPTURE_SRC_OV490,
     /**< Capture source is OV490 */


     CHAINS_CAPTURE_SRC_UB960_MARS_AR0233,
     /**< AR0233 sensor with UB953 MARS Module
      *   SUPPORTED on TDA3x RVP and TDA2Px EVM
      */
     CHAINS_CAPTURE_SRC_MAX
     /**< Max number of capture source's */

 } Chains_CaptureSrc;


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

/* @} */

/**
 *******************************************************************************
 *
 *   \defgroup CHAINS_SENSOR Sensor config implementation
 *
 *******************************************************************************
 */
