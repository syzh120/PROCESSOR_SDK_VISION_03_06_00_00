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
 *
 * \file main_eve_common.h
 *
 * \brief  This file gives interface for common code for main() and EVE_main()
 *         function for EVEs in TDA2x as per Vision SDK requirements
 *
 * \version 0.0 (Aug 2015) : [CSG] First version
 *
 *******************************************************************************
*/

#ifndef MAIN_EVE_COMMON_H_
#define MAIN_EVE_COMMON_H_

/* =============================================================================
 * INCLUDE FILES (only if necessary)
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 *******************************************************************************
 *
 * \brief This function implements the wait loop of EVE.
 *
 *        This function would get called if the EVE doesn't run the demo
 *        or application. It is not used if EVE runs the app.  Do not
 *        remove this function, required when App is moved out of EVE1
 *
 * \param  arg0 [IN]
 * \param  arg1 [IN]
 *
 * \return  void
 *
 *******************************************************************************
 */
Void Eve_main_common(UArg arg0, UArg arg1);

/**
 *******************************************************************************
 *
 * \brief This is the main() implementation of EVE1.
 *
 *        This is the first function  and entry point to EVE1, does
 *         - Set the correct/required CPU frequency
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 main_common_arp32(void);

/**
 *******************************************************************************
 *
 * \brief This function enables the ARP32_CPU_0 Timer Ticks
 *
 * \param  arg [IN]
 *
 *******************************************************************************
 */
void mainARP32_common_TimerTick(UArg arg);



#ifdef __cplusplus
}
#endif

#endif  /* MAIN_EVE_COMMON_H_ */
/* EOF */

