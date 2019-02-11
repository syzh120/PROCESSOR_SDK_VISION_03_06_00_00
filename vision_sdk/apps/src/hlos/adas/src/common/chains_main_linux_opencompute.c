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

/****************** *************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <system_cfg.h>
#include <src/hlos/adas/include/chains.h>

/**
 *******************************************************************************
 * \brief OpenCompute UC Menu
 *******************************************************************************
 */

char gChains_menuOpenComputeUsecases[] = {
    "\r\n "
    "\r\n OpenCompute Usecases"
    "\r\n ----------------------------"
#ifdef OPENVX_INCLUDE
    "\r\n 1: OpenVX USecases"
#endif
#ifdef ENABLE_OPENCV
    "\r\n 2: OpenCV Usecases"
#endif
#ifdef OPENCL_INCLUDE
    "\r\n 3: OpenCL Usecases"
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief OpenVx UC Menu
 *******************************************************************************
 */

char gChains_menuOpenVXUsecases[] = {
    "\r\n "
    "\r\n OPENVX Usecases"
    "\r\n ----------------------------"
    "\r\n 1: OpenVX v1.1 Conformance Test"
    "\r\n 2: OpenVX Tutorials"
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief OpenCV UC Menu
 *******************************************************************************
 */

char gChains_menuOpenCVUsecases[] = {
    "\r\n "
    "\r\n OpenCV Usecases"
    "\r\n ----------------------------"
#ifdef UC_vip_single_cam_opencvcanny_sgx_display
    "\r\n 1: 1CH VIP capture + OpenCV Canny (A15) + SGX Copy + DISPLAY"
#endif
#ifdef UC_vip_single_cam_opencvopencldilation_sgx_display
    "\r\n 2: 1CH VIP capture + OpenCV OpenCL Dilation (A15 + DSP) + SGX Copy + DISPLAY"
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 * \brief OpenCL UC Menu
 *******************************************************************************
 */

char gChains_menuOpenCLUsecases[] = {
    "\r\n "
    "\r\n OpenCL Usecases"
    "\r\n ----------------------------"
#ifdef UC_vip_single_cam_openclframe_copy
    "\r\n 1: 1CH VIP capture + OpenCL Copy (A15->DSP) + SGX Copy + DISPLAY"
#endif
    "\r\n "
    "\r\n x: Exit "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/

Void Chains_menuOpenVXRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuOpenVXUsecases);
        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef OPENVX_INCLUDE
            case '1':
                TestModuleRegister();
                vx_conformance_test_main(0U, NULL);
                TestModuleUnRegister();
                break;
            case '2':
                vx_tutorial_run_interactive();
                break;
            #endif
            case 'x':
            case 'X':
                done = TRUE;
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/

Void Chains_menuOpenCVRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuOpenCVUsecases);
        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_vip_single_cam_opencvcanny_sgx_display
            case '1':
                chains_vipSingleCamOpenCVCannySgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            #ifdef UC_vip_single_cam_opencvopencldilation_sgx_display
            case '2':
                chains_vipSingleCamOpenCVOpenCLDilationSgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            case 'x':
            case 'X':
                done = TRUE;
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/

Void Chains_menuOpenCLRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuOpenCLUsecases);
        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef UC_vip_single_cam_openclframe_copy
            case '1':
                chains_vipSingleCamOpenCLFrameCopySgxDisplay(&gChains_usecaseCfg);
                break;
            #endif
            case 'x':
            case 'X':
                done = TRUE;
                break;

            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   Function to select demo depending on user input
 *          Accepts user input as ch and switches to corrosponding usecase
 *
 * \param   ch        [IN]  Input choise for user
 *
 *******************************************************************************
*/

Void Chains_menuOpenComputeRun()
{
    char ch;
    Bool done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_menuOpenComputeUsecases);
        ch = Chains_readChar();
        Vps_printf(" \r\n");

        switch(ch)
        {
            #ifdef OPENVX_INCLUDE
            case '1':
                Chains_menuOpenVXRun();
                done = TRUE;
                break;
            #endif
            #ifdef ENABLE_OPENCV
            case '2':
                Chains_menuOpenCVRun();
                done = TRUE;
                break;
            #endif
            #ifdef OPENCL_INCLUDE
            case '3':
                Chains_menuOpenCLRun();
                done = TRUE;
                break;
            #endif
            case 'x':
            case 'X':
                done = TRUE;
                break;
            default:
                Vps_printf(" Unsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}


