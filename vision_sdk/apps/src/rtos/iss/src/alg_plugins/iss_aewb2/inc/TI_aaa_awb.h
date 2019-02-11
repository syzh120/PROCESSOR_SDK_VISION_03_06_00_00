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
/*******************************************************************************************
 *
 *  This is proprietary information, not to be published - TI INTERNAL DATA
 *  Copyright (C) 2009, Texas Instruments, Inc.  All Rights Reserved.
 *
 *******************************************************************************************
 *
 *  Name:           TI_aaa_awb.h
 *
 *  Author:         Buyue Zhang (DSPS R&D, Texas Instruments)
 *
 *  Description:
 *                  This is the interface header for TI AWB v2.0 library
 *                  This header is needed by the wrapper for AWB library
 *
 *  Project:        DM510, OMAP 3430
 *
 *******************************************************************************************
 *
 *  Instructions for AWB library integration:
 *
 *                  This header exposes the structures/definitions used by the AWB library.
 *                  These structures should be initiated in the wrapper or framework using
 *                  exactly the same format defined here for AWB library
 *
 *                  In case system already have some structures/definitions defined in this header:
 *                  (1) check if the structures are exactly the same, if so, comment out the definitions here
 *                  (2) if the structures are different, but share the same name, re-name the structures
 *                      in the framework. If this is not possible, AWB library needs to be re-compiled.
 *
 *******************************************************************************************
 *
 *  History:
 *
 *  Version Date        Author          Reason
 *
 *  1.0     25.10.2004    Namjin Kim         Created
 *  1.1     02.10.2008    Nevena Milanova    Changed interface of TI_AWBInit() and TI_AWB_do()
 *  2.0     March 5 2009, Buyue Zhang      Modified for TI AWB v2.0 library
 *          April 7 2009, Buyue Zhang      Manual mode support added
 *******************************************************************************************/

#ifndef __CTYPES_H__
#define __CTYPES_H__

#ifndef NULL
#define NULL    ((void *) 0)
#endif

// ---------------------------------------------------------------------------
// data types
// ---------------------------------------------------------------------------

typedef unsigned char  uint8;
typedef unsigned short         uint16;
typedef unsigned int   uint32;
typedef int                    int32;
typedef char                   int8;
typedef short                  int16;

#endif //_CTYPES_H__


#ifndef __H3A_510_H__
#define __H3A_510_H__

//------------------------------------------------------------------------------
// This structure contents the H3A AEWB
// paxel data parametters
//-------------------------------------------------------------------------------

typedef struct {
    /** Average value for red pixels in current paxel */
    unsigned short red;
    /** Average value for green pixels in current paxel */
    unsigned short green;
    /** Average value for blue pixels in current paxel */
    unsigned short blue;
    /** Flag indicating whether current paxel is valid 0:invalid, !0:valid */
    unsigned short valid;
} h3a_aewb_paxel_data_t;

#endif //__H3A_510_H__



#ifndef __ALG_AWB_DEFS_H__
#define __ALG_AWB_DEFS_H__

//--------------------------------------------------------------------------
// DEFINES
//--------------------------------------------------------------------------


#define FACE_TRACKING_OBJ_FALSE_TRESHOLD 0 // no face  if = threshold
#define ALG_CONFIG                  (1)


/********************************************************************
 * !!! Important notes: B Zhang, 3.5.09 !!!
 ********************************************************************
 *
 * The following definitions specify the maximal sizes of sensor calibration
 * data structures in awb_calc_data_t
 *
 * These values CANNOT be changed.
 *
 * Actual size of sensor calibration data structures passed in to AWB function
 * through awb_calc_data_t should NOT exceed these maximal sizes.
 * AND they should fill in the upper left corner of the data structures
 * in awb_calc_data_t
 *
 ******************************************************************/

// TI sensor calibration data
#define NUM_OF_REF_1        30  //maximal number of reference 1, actual use 17
#define NUM_OF_REF_2        15  //maximal number of reference 2, actual use 7
#define NUM_OF_GRAY          4  //maximal number of gray 2 used, actual use 4

//added by B Zhang to avoid msg_hif_params.h
#define NUM_OF_WB_MODE      20  //maximal number of white balance mode

//B Zhang, 4.7.09, added for manual mode support
typedef enum
{
  AWB_WB_MODE_AUTO = 0,      // 0 Auto AWB mode
  AWB_WB_MODE_MANUAL = 1     // 1 Manual AWB mode
} AWB_MODE_VALUES;

//--------------------------------------------------------------------------
// TYPES
//--------------------------------------------------------------------------

typedef enum {
    TI_AWB_ERROR_OK               = 0x0000,   // no error
    TI_AWB_ERROR_CONFIGURE        = 0x0001   // error algorithm is not configured
    //TI_AWB_ERROR_TUNE             = 0x0002    // error algorithm tuning data is not correct

} TI_AWB_ERROR_t;


//--------------------------------------------------------------------------
// This structure contains all algorithm-specific out data used in maker note.
// @see h3a_aewb_config_t, aaa_active_win_t
//--------------------------------------------------------------------------

typedef struct {
    unsigned short not_used;
} awb_alg_specific_data_t;


//--------------------------------------------------------------------------
// This structure contains some additional WB mode parameters.
// @see wb_mode_data_t
//--------------------------------------------------------------------------

typedef struct
{
    /** Contrast gain */
    unsigned char               contrastGainY;
    /** Contrast offset */
    unsigned char               contrastOffsetY;
} wb_misc_t;


//--------------------------------------------------------------------------
// This structure contains the gain values for each color channel and digital
// gain for the respective WB mode
// @see wb_mode_data_t
//--------------------------------------------------------------------------

typedef struct
{
    /** Digital gain.  Format U16Q8 */
    unsigned short          dgain;
    /** WB Gain for Gr. Format U16Q8 */
    unsigned short          gainGr;
    /** WB Gain for R.  Format U16Q8 */
    unsigned short          gainR;
    /** WB Gain for Gb. Format U16Q8 */
    unsigned short          gainGb;
    /** WB Gain for B.  Format U16Q8 */
    unsigned short          gainB;
} wb_scalers_t;


//--------------------------------------------------------------------------
// This structure contains the RGB to YUV matrixes for the respective WB mode
//@see wb_mode_data_t
//--------------------------------------------------------------------------

typedef struct
{
    /** Format U16Q8 */
    short               matrix[3][3];
    /** See register YOFST, COFST */
    short               offset[3];
} wb_rgb2yuv_t;


//--------------------------------------------------------------------------
// This structure contains the RGB2RGB matrixes for the respective WB mode
// @see wb_mode_data_t
//--------------------------------------------------------------------------

typedef struct
{
    /** Format U16Q8 */
    short               matrix[3][3];
    /** Format 2's complement integer */
    short               offset[3];
} wb_rgb2rgb_t;


//--------------------------------------------------------------------------
// This is a structure containing all parameters for a specific WB mode
// @see wb_scalers_t, wb_rgb2rgb_t, wb_rgb2yuv_t, wb_misc_t
//--------------------------------------------------------------------------

typedef struct wb_mode_data_t
{
    /** Digital gain and gains for the separate color channels */
    wb_scalers_t        wb;
    /** RGB to RGB matrixes */
    wb_rgb2rgb_t        rgb2RGB;
    /** RGB to YUV matrixes */
    wb_rgb2yuv_t        rgb2YUV;
    /** Other parameters */
    wb_misc_t           misc;
} wb_mode_data_t;


//--------------------------------------------------------------------------
// This structure contains the default AWB output parameters for all WB modes
// @see wb_mode_data_t
//--------------------------------------------------------------------------

/*typedef struct
{
    //default output parameters for AWB modes
    // +2 is because values flash and underwater are not defined any more in
    // the enum msg_hif_params. However their data is still used in application and
    // is included in this array.
    wb_mode_data_t      wbModeData[WHITE_BALANCE_MODE_VALUES_COUNT + 2 +
                        AWB_MANL_TUNED_TEMPERATURES_COUNT - 1];
} awb_data_t;*/

/********************************************************************
 * Important notes: B Zhang, 3.4.09
 ********************************************************************
 *
 * NUM_OF_WB_MODE is defined and used to avoid header msg_hif_params.h
 *
 ******************************************************************/

typedef struct
{
    wb_mode_data_t      wbModeData[NUM_OF_WB_MODE]; //bzbz// wbModeData[WHITE_BALANCE_MODE_VALUES_COUNT + 2 + AWB_MANL_TUNED_TEMPERATURES_COUNT - 1];
} awb_data_t;


//--------------------------------------------------------------------------
// Sensor and algorithm specific data for AWB calculation
//--------------------------------------------------------------------------
typedef struct
{
    // Sensor specific calibration data

    unsigned int    num_of_ref_1;
    unsigned int    num_of_ref_2;
    unsigned int    num_of_gray;

    unsigned int    color_temp_1[NUM_OF_REF_1];

    int wbReferenceCb[NUM_OF_REF_1][NUM_OF_GRAY];
    int wbReferenceCr[NUM_OF_REF_1][NUM_OF_GRAY];

    unsigned int    ref_gray_R_1[NUM_OF_REF_1][NUM_OF_GRAY];
    unsigned int    ref_gray_G_1[NUM_OF_REF_1][NUM_OF_GRAY];
    unsigned int    ref_gray_B_1[NUM_OF_REF_1][NUM_OF_GRAY];

    unsigned int    ref_index_2[NUM_OF_REF_2];
    unsigned int    color_temp_2[NUM_OF_REF_2];

    unsigned int    img_ref[NUM_OF_REF_2 * 1120];

    int referencesCb_2[NUM_OF_REF_2][NUM_OF_GRAY];
    int referencesCr_2[NUM_OF_REF_2][NUM_OF_GRAY];

    unsigned int    ref_gray_R_2[NUM_OF_REF_2][NUM_OF_GRAY];
    unsigned int    ref_gray_G_2[NUM_OF_REF_2][NUM_OF_GRAY];
    unsigned int    ref_gray_B_2[NUM_OF_REF_2][NUM_OF_GRAY];


    // Sensor specific tuning paramaters

    unsigned int    radius;

    int luma_awb_min;
    int luma_awb_max;

    unsigned int    low_color_temp_thresh;

    unsigned int    apply_rgb_adjust;

    int R_adjust;
    int B_adjust;

    unsigned int    SB_1;
    unsigned int    SB_2;

    unsigned int    SB_low_bound;

    unsigned int    default_T_H;
    unsigned int    default_T_MH;
    unsigned int    default_T_ML;
    unsigned int    default_T_L;

    unsigned int    default_T_H_index;
    unsigned int    default_T_MH_index;
    unsigned int    default_T_ML_index;
    unsigned int    default_T_L_index;

    unsigned int    best_gray_index_default;

} awb_calc_data_t;


//--------------------------------------------------------------------------
// This structure contains all sensor-specific configuration parameters.
// @see awb_data_t, awb_calc_data_t
//--------------------------------------------------------------------------

typedef struct {
    /** pointer to sensor and algorithm specific AWD calculation data */
    const awb_calc_data_t *awb_calc_data;
    /** pointer to default output parameters for all WB modes */
    //const awb_data_t   *awb_data;
} awb_sen_data_t;

//--------------------------------------------------------------------------
// This structure contains all algorithm-specific configuration parameters.
// @see h3a_aewb_config_t, aaa_active_win_t
//--------------------------------------------------------------------------

typedef struct {
    unsigned short not_used;
} awb_alg_cfg_data_t;


//--------------------------------------------------------------------------
// This structure contains data from h3a engine.
//--------------------------------------------------------------------------

typedef struct {
    /** */
    unsigned short              pix_in_pax;
    /** poiter to input data for AWB */
    h3a_aewb_paxel_data_t *h3a_res;
    /** X size of H3A data, blocks(paxels) */
    unsigned short              h3a_data_x;
    /** Y size of H3A data, blocks(paxels) */
    unsigned short              h3a_data_y;
} awb_frame_data_t;


//--------------------------------------------------------------------------
// Containes algorithm specific data, other then the frame data
// Not used by this algorithm
//@see awb_data_in_t
//--------------------------------------------------------------------------

typedef struct {
    /** This algorithm does not need specific data */
    //unsigned short not_used;

    /** Array with face-tracking information (0 means no face; 1 means face) */
    unsigned char   *faces;

} awb_alg_data_in_t;

//--------------------------------------------------------------------------
// Contains input data for TI_AWBInit() routine.
// @see awb_frame_data_t
//--------------------------------------------------------------------------

typedef struct
{
    unsigned char             flash_used;
    awb_frame_data_t  frame_data;
    unsigned char             preview_mode;
//    unsigned short            exposure_AEvalue;
//    unsigned short            gain_AEvalue;
    awb_alg_data_in_t is_face;
} ti_awb_data_in_t;

#endif // __ALG_AWB_DEFS_H__




#ifndef __AAA_AWB_DEFS_H__
#define __AAA_AWB_DEFS_H__

//--------------------------------------------------------------------------------
// AWB calculations type
// @see ae_data_in_t
//---------------------------------------------------------------------------------

typedef enum {
    /** AWB calculation for preview */
    AWB_CALC_PREVIEW,        //0
    /** AWB calculation for preview */
    AWB_CALC_PREVIEW_FAST,   //1
    /** AWB calculation for capture */
    AWB_CALC_CAPTURE,        //2
    /** AWB calculation for fast capture EXTERNAL AWB*/
    AWB_CALC_CAPTURE_FAST,   //3
    /** AWB calculation for capture with flash used */
    AWB_CALC_CAPTURE_FLASH   //4
} awb_calc_t;


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// This is the input data structure for AWB function TI_AWB_do(),
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

typedef struct
{
    unsigned short  mode;
    unsigned short  manl_tmpr;  // manual white balance : color temperature
    unsigned short  control;

    ti_awb_data_in_t ti_awb_data_in; //H3A data
    awb_calc_data_t *sen_awb_calc_data; //sensor calibration datat
    //awb_data_t  *awb_data; //RGB2RGB matrices

    unsigned char   buf_len;
    unsigned int  total_exp;

    unsigned short  *h3a_window_reference;

    unsigned char   *histogram;

    char    awb_count;
    unsigned short  temp_Rgain;
    unsigned short  temp_Ggain;
    unsigned short  temp_Bgain;
    unsigned char   RGB2RGBIndex;
    unsigned char   *history_index;

    unsigned int  *v_img_ref;

    /** Flag for checking algorithm config before applying **/
    unsigned int  alg_config;

    unsigned char   *AWB_ScratchMemory;

} awbprm_t;


//-----------------------------------------------------------------------
// This structure contains WB-related parameters received from the host
// @see awb_config_data_in_t
//-----------------------------------------------------------------------

typedef struct {
    /** The selected WB mode */
    unsigned short mode;
    /** Manual white balance */
    unsigned short color_temperature;
    /** The control mode */
    unsigned short control;
    /** Parameter related to the region of interest */
    unsigned char  manual_spot_weighting;
} awb_ctrl_cfg_data_t;


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
// This is the output structure of the AWB function: TI_AWB_do()
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------

typedef struct {
    /** Digital gain.  Format U16Q8 */
    unsigned short              dgain;
    /** WB Gain for Gr. Format U16Q8 */
    unsigned short              gain_Gr;
    /** WB Gain for R.  Format U16Q8 */
    unsigned short              gain_R;
    /** WB Gain for Gb. Format U16Q8 */
    unsigned short              gain_Gb;
    /** WB Gain for B.  Format U16Q8 */
    unsigned short              gain_B;
    /** Format S16Q8 */
    short               rgb2rgb_matrix[3][3];
    /** Format 2's complement integer */
    short               rgb2rgb_offset[3];
    /** Format S16Q8 */
    short               rgb2yuv_matrix[3][3];
    /** See register YOFST, COFST */
    short               rgb2yuv_offset[3];
    /** Contrast Gain Y */
    unsigned char               contrast_gain_Y;
    /** Contrast Offset Y */
    unsigned char               contrast_offset_Y;
    /** AWB index : awb_mode-1(DL.FLOUR,etc) */
    unsigned char               awb_idx;
    /** 1:the WB vars remain the same, 0:they are changed and should be applied */
    unsigned short              not_changed;
    /** 1: WB succeeded, 0: failed */
    unsigned short              converged;
    /** algorithm specific data : info */
    awb_alg_specific_data_t awb_alg_specific_data;
    /** color temperature estimation */
    unsigned int              color_temperature_estim;
    /** number of SB counted        */
    unsigned short              SB_count;
    /*  total internal Scratch Memory used    */
    unsigned int              internalScratchMemorySize;
    /*  total internal Persistent Memory used */
    unsigned int              internalPersistentMemorySize;

} awb_data_out_t;


//-----------------------------------------------------------------------------
// This structure contains all configuration parameters for WB
// @see ctrl_cfg_data, wb_data_out, sen_cfg_data, alg_cfg_data
//-----------------------------------------------------------------------------

typedef struct {
    /** This structure contains WB-related parameters received from the host */
    awb_ctrl_cfg_data_t  ctrl_cfg_data;
    /** Output structure for WB algorithm */
    awb_data_out_t*  wb_data_out;
    /** Sensor-related parameters */
    awb_sen_data_t   sen_awb_data;
    /** Algorithm-specific parameters */
    awb_alg_cfg_data_t  alg_cfg_data;
    /** pointer to work buffer of size AWB_WORK_BUFF_SIZE bytes */
    void*            work_buff;
} awb_config_data_in_t;


//-----------------------------------------------------------------------------
// This is the output structure for the configuration routine.
// @see awb_config_data_in_t
//-----------------------------------------------------------------------------

typedef struct
{
    /** not used */
    short               not_used;
} awb_config_data_out_t;


//--------------------------------------------------------------------------
// Contains input data for awb_do() routine
// -- awb_do() is the wrapper function that calls the AWB function TI_awb_do()
//-----------------------------------------------------------------------------

typedef struct {
    /** AWB calculations type :  preview,capture or flash*/
    awb_calc_t        calc_type;
    /** frame descriptor */
    awb_frame_data_t  frame_data;
    /** other algorithm specific data */
    awb_alg_data_in_t alg_in_data;
} awb_data_in_t;

#endif // __AAA_AWB_DEFS_H__






//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
// The following section contains declaration of functions inside TI_aaa_awb.c
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------


#ifndef __TI_AAA_AWB_H__
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define __TI_AAA_AWB_H__

// ===========================================================================
// void TI_AWBInit(awbprm_t *awb_param, awb_data_out_t  *data_out, unsigned short load_defs)
// INPUT:
//      awb_param: pointer to input data
//      load_defs : loads the defaults of the AWB controlled variables. This is
//          necessary if the current values are not relyable (after power-up)
// NOTE:
//   initialize the AWB alorithm,
//   calculates the settings to configures the AWB hardware
//   returns the initial values for AWB controlled variables
// ===========================================================================
/* ===================================================================
 *  @func     TI_AWBInit
 *
 *  @desc     Function does the following
 *
 *  @modif    This function modifies the following structures
 *
 *  @inputs   This function takes the following inputs
 *            <argument name>
 *            Description of usage
 *            <argument name>
 *            Description of usage
 *
 *  @outputs  <argument name>
 *            Description of usage
 *
 *  @return   Return value of this function if any
 *  ==================================================================
 */
TI_AWB_ERROR_t TI_AWBInit(awbprm_t *awb_param, awb_data_out_t  *data_out, unsigned short load_defs);



// ===========================================================================
// void TI_AWB_do (awbprm_t *awb_param, awb_data_out_t  *data_out)
// INPUT:
//      awbprm_t, ti_awb_data_in_t  : input parameters to AWB
// OUTPUT:
//      awb_data_out_t : AWB output data structure
//                      int the location set in AWBInit() - awb_param->data_out
// NOTE:
//     executes 1 iteration of the AWB algorithm
// ===========================================================================
TI_AWB_ERROR_t TI_AWB_do (awbprm_t *awb_param, awb_data_out_t  *data_out);



// ===========================================================================
// void TI_AWB_stab (awbprm_t *awb_param, awb_data_out_t  *data_out)
// INPUT:
//      awbprm_t, ti_awb_data_in_t  : input parameters
// OUTPUT:
//      awb_data_out_t : update AWB output data structure
//                      int the location set in AWBInit() - awb_param->data_out
// NOTE:
//     executes 1 iteration of the AWB algorithm
// ===========================================================================
void TI_AWB_stab (awbprm_t *awb_param, awb_data_out_t  *data_out);




#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __TI_AAA_AWB_H__

