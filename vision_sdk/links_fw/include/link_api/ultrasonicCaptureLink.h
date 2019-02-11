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
*/

/**
 *******************************************************************************
 *
 *   \ingroup SAMPLE_MODULE_API
 *   \defgroup ULTRASONIC_CAPTURE_LINK_API UltrasonicCapture Link API
 *
 *             Capture data from ultrasonic sensors connected via UART
 *             Sends measurement info to next link
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file ultrasonicCaptureLink.h
 *
 * \brief UltrasonicCapture link API public header file.
 *
 * \version 0.0 (Jul 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ULTRASONIC_CAPTURE_LINK_H_
#define ULTRASONIC_CAPTURE_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /* @{ */

/**
 *******************************************************************************
 * \brief Maximum number of possible devices that can be connected
 *******************************************************************************
 */
#define ULTRASONIC_CAPTURE_MAX_DEVICES                  (16)

/**
 *******************************************************************************
 * \brief Measurement mode is short distance
 *******************************************************************************
 */
#define ULTRASONIC_CAPTURE_MEASUREMENT_MODE_SHORT       (1)

/**
 *******************************************************************************
 * \brief Measurement mode is long distance
 *******************************************************************************
 */
#define ULTRASONIC_CAPTURE_MEASUREMENT_MODE_LONG        (2)

typedef enum _USM_id_e {

    /*! \brief USM ID for PGA450 */
    USM_ID_PGA450 = 0,

    /*! \brief USM ID for PGA460 */
    USM_ID_PGA460 = 1,

    /*! \brief Invalid CPU ID */
    USM_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

} USM_id_e;

/* @} */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
*/

/**
 *******************************************************************************
 * \brief Device measurement info
 *******************************************************************************
 */
typedef struct {

    UInt32 deviceId;
    /**< ID of device for which this measurement is done */

    UInt32 distanceLong;
    /**< Detected object distance in cm */

    UInt32 distanceShort;
    /**< Detected object distance in cm */

} UltrasonicCapture_DeviceMeasurementInfo;

/**
 *******************************************************************************
 * \brief Structure of data included in the buffer that is passed to next link
 *******************************************************************************
 */
typedef struct
{
    UInt32 numSensors;
    /**< Number of sensors for which data is measured */

    UltrasonicCapture_DeviceMeasurementInfo deviceInfo
        [ULTRASONIC_CAPTURE_MAX_DEVICES];
    /**< Measurement information of individual device's */

} UltrasonicCapture_MeasurementInfo;



/**
 *******************************************************************************
 * \brief Ultrasonic capture link configuration parameters.
 *******************************************************************************
*/
typedef struct
{
    UInt32  uartInstId;
    /**< 0..9, UART instance to use for ultrasonic sensor   */

    UInt32  numSensorsConnected;
    /**< Gives number of sensors connected to device   */

    System_LinkOutQueParams   outQueParams;
    /**< output queue information */

} UltrasonicCaptureLink_CreateParams;

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */
static inline void UltrasonicCaptureLink_CreateParams_Init(
                                    UltrasonicCaptureLink_CreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Init function for Ultrasonic capture link.
 *
 *        This function does the following
 *          - Creates a task for the link
 *          - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 UltrasonicCaptureLink_init(int usm_id);

/**
 *******************************************************************************
 *
 * \brief De-init function for Ultrasonic capture link.
 *
 *        This function de-registers this link from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 UltrasonicCaptureLink_deInit(int usm_id);

/**
 *******************************************************************************
 *
 * \brief UltrasonicCapture link set default parameters for create time params
 *
 * \param  pPrm  [OUT]  UltrasonicCaptureLink Create time Params
 *
 *******************************************************************************
 */
static inline void UltrasonicCaptureLink_CreateParams_Init(UltrasonicCaptureLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(UltrasonicCaptureLink_CreateParams));

    /* value of 9 corresponds to UART instance 10 as specified in TRM */
    pPrm->uartInstId = 9U;

    return;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/

