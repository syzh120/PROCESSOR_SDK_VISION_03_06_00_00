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
 *  @file       ti/xdais/dm/iaewb.h
 *
 *  @brief      This header defines all types, constants, and functions
 *              shared by all implementations of the auto exposure and auto 
 *              white balance algorithms.
 */
/**
 *  @defgroup   ti_xdais_dm_IAEWB   xDM 1.0 extention Auto Exposure & 
 *                                  Auto White Balance Interface
 *
 *  This is the xDM 1.0 extention Auto Exposure & Auto White Balance Interface.
 */

#ifndef ti_xdais_dm_IAEWB_
#define ti_xdais_dm_IAEWB_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_xdais_dm_IAEWB */
/*@{*/

/**
 *  @brief typedef for RGB count: 16-bit for HW 3A, 32-bit otherwise 
 */

#ifdef H3A
typedef XDAS_UInt16 IAEWB_RGB_COUNT;  /**< H3A available: 16-bit unsigned */
#else
typedef XDAS_UInt32 IAEWB_RGB_COUNT; /**< SW Implementation: 32-bit unsigned */
#endif

/**
 *  @brief structure for non-saturated RGB counter values for each sub-window
 */
typedef struct IAEWB_Rgb{
    IAEWB_RGB_COUNT r; /**< Red value 16 bit */
    IAEWB_RGB_COUNT g; /**< Green value 16 bit */
    IAEWB_RGB_COUNT b; /**< Blue value 16 bit */
} IAEWB_Rgb;

/**
 *  @brief structure for statistics matrix
 */

typedef struct IAEWB_StatMat{
	    XDAS_Int32 winCtHorz; /**< number of windows in horizontal direction */
	    XDAS_Int32 winCtVert; /**< number of windows in vertical direction */
	    XDAS_Int32 pixCtWin; /**< number pixels per window */
	} IAEWB_StatMat;

/**
 *  @brief structure for Auto Exposure Setting
 */
typedef struct {
  XDAS_Int32 exposureTime;  /**< exposure Time  */
  XDAS_Int32 apertureLevel; /**< aperture Level */
  XDAS_Int32 sensorGain;    /**< sensor gain, Q10 */
  XDAS_Int32 ipipeGain;     /**< IPIPE gain, Q10  
                             *   e.g. 1.0 is 1024, 2.0 is 2048 and 0.5 is 512
			     */
} IAEWB_Ae;

/**
  \brief structure for Auto Whilte Balance Setting
*/
typedef struct IAEWB_Wb{
  XDAS_UInt32 rGain; /**< Red Gain, Q10, 
                      *   e.g. 1.0 is 1024, 2.0 is 2048 and 0.5 is 512
		      */
  XDAS_UInt32 gGain; /**< Green Gain, Q10, 
                      *   e.g. 1.0 is 1024, 2.0 is 2048 and 0.5 is 512
		      */
  XDAS_UInt32 bGain; /**< Blue Gain, Q10, 
                       *  e.g. 1.0 is 1024, 2.0 is 2048 and 0.5 is 512
		       */
  XDAS_UInt32 colorTemp; /**< color Temperature, 
                          *   unit is not yet decided (tentative)
			  */
} IAEWB_Wb;



/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif


#endif  /* ti_xdais_dm_IAEWB_ */

