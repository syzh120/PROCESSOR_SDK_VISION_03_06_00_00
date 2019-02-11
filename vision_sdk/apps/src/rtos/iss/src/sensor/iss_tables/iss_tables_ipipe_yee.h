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
 * \ingroup EXAMPLES_API
 * \defgroup EXAMPLES_VIDEO_SENSOR_API APIs for controlling external sensors
 *
 *         Sensor APIs can be used to control external sensors.
 *         Drivers for sensors can be part of BSP or any other package.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file video_sensor.h
 *
 * \brief APIs for controlling external sensors.
 *
 * \version 0.0 (Jun 2013) : [CM] First version
 * \version 0.1 (Jul 2013) : [CM] Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef ISS_TABLES_IPIPE_YEE_H_
#define ISS_TABLES_IPIPE_YEE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define ISS_TABLE_IPIPE_YEE                             \
{                                                       \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000014,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000013,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000012,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000011,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x00000010,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000F,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000E,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000D,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000C,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000B,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x0000000A,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000009,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000008,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000007,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000006,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000005,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000004,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000003,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000002,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000001,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFEC,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFED,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEE,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFEF,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF0,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF1,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF2,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF3,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF4,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF5,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF6,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF7,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF8,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFF9,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFA,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFB,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFC,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFD,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFE,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0xFFFFFFFF,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000,                                         \
    0x00000000                                          \
}

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
