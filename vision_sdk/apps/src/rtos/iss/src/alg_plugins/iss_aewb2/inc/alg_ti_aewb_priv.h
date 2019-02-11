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
#ifndef _ALG_TI_AEWB_PRIV_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define _ALG_TI_AEWB_PRIV_H_

#define NUM_OF_REF_1		30  //maximal number of reference 1, actual use 17                          
#define NUM_OF_REF_2       	15  //maximal number of reference 2, actual use 7
#define NUM_OF_GRAY      	 4  //maximal number of gray 2 used, actual use 4

#if 1
typedef struct
{
	// Sensor specific calibration data
	
	unsigned int	num_of_ref_1;
	unsigned int	num_of_ref_2;
	unsigned int	num_of_gray;

	unsigned int	color_temp_1[NUM_OF_REF_1];

	int	wbReferenceCb[NUM_OF_REF_1][NUM_OF_GRAY];
	int	wbReferenceCr[NUM_OF_REF_1][NUM_OF_GRAY];

	unsigned int	ref_gray_R_1[NUM_OF_REF_1][NUM_OF_GRAY];
	unsigned int	ref_gray_G_1[NUM_OF_REF_1][NUM_OF_GRAY];
	unsigned int	ref_gray_B_1[NUM_OF_REF_1][NUM_OF_GRAY];

	unsigned int	ref_index_2[NUM_OF_REF_2];
	unsigned int	color_temp_2[NUM_OF_REF_2];

	unsigned int	img_ref[NUM_OF_REF_2 * 1120];

	int	referencesCb_2[NUM_OF_REF_2][NUM_OF_GRAY];
	int	referencesCr_2[NUM_OF_REF_2][NUM_OF_GRAY];

	unsigned int	ref_gray_R_2[NUM_OF_REF_2][NUM_OF_GRAY];
	unsigned int	ref_gray_G_2[NUM_OF_REF_2][NUM_OF_GRAY];
	unsigned int	ref_gray_B_2[NUM_OF_REF_2][NUM_OF_GRAY];


	// Sensor specific tuning paramaters

	unsigned int	radius; 

	int	luma_awb_min;
	int	luma_awb_max;

	unsigned int	low_color_temp_thresh;
	
	unsigned int	apply_rgb_adjust;

	int	R_adjust;
	int	B_adjust;

	unsigned int	SB_1;
	unsigned int	SB_2;

	unsigned int	SB_low_bound;

	unsigned int	default_T_H;
	unsigned int	default_T_MH;
	unsigned int	default_T_ML;
	unsigned int	default_T_L;

	unsigned int	default_T_H_index;
	unsigned int	default_T_MH_index;
	unsigned int	default_T_ML_index;
	unsigned int	default_T_L_index;	

	unsigned int	best_gray_index_default;

} awb_calc_data_t;

#endif 

#if 0

typedef struct
{
	// Sensor specific calibration data
	
	unsigned char	num_of_ref_1;
	unsigned char	num_of_ref_2;
	unsigned char	num_of_gray;

	unsigned short	color_temp_1[NUM_OF_REF_1];

	short	wbReferenceCb[NUM_OF_REF_1][NUM_OF_GRAY];
	short	wbReferenceCr[NUM_OF_REF_1][NUM_OF_GRAY];

	unsigned short	ref_gray_R_1[NUM_OF_REF_1][NUM_OF_GRAY];
	unsigned short	ref_gray_G_1[NUM_OF_REF_1][NUM_OF_GRAY];
	unsigned short	ref_gray_B_1[NUM_OF_REF_1][NUM_OF_GRAY];

	unsigned char	ref_index_2[NUM_OF_REF_2];
	unsigned short	color_temp_2[NUM_OF_REF_2];

	unsigned short	img_ref[NUM_OF_REF_2 * 1120];

	short	referencesCb_2[NUM_OF_REF_2][NUM_OF_GRAY];
	short	referencesCr_2[NUM_OF_REF_2][NUM_OF_GRAY];

	unsigned short	ref_gray_R_2[NUM_OF_REF_2][NUM_OF_GRAY];
	unsigned short	ref_gray_G_2[NUM_OF_REF_2][NUM_OF_GRAY];
	unsigned short	ref_gray_B_2[NUM_OF_REF_2][NUM_OF_GRAY];


	// Sensor specific tuning paramaters

	unsigned short	radius; 

	int	luma_awb_min;
	int	luma_awb_max;

	unsigned short	low_color_temp_thresh;
	
	unsigned char	apply_rgb_adjust;

	short	R_adjust;
	short	B_adjust;

	unsigned short	SB_1;
	unsigned short	SB_2;

	unsigned short	SB_low_bound;

	unsigned short	default_T_H;
	unsigned short	default_T_MH;
	unsigned short	default_T_ML;
	unsigned short	default_T_L;

	unsigned char	default_T_H_index;
	unsigned char	default_T_MH_index;
	unsigned char	default_T_ML_index;
	unsigned char	default_T_L_index;	

	unsigned char	best_gray_index_default;

} awb_calc_data_t;
#endif

extern awb_calc_data_t awb_calc_data;


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

