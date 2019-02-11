/*
********************************************************************************
* HDVICP2.0 Based JPEG Encoder
*
* "HDVICP2.0 Based JPEG Encoder" is software module developed for
* TI's HDVICP2 based SoCs. This module is capable of encoding a raw image
* by compressing it into a JPEG bitstream compliant with ISO/IEC IS 10918-1.
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
* @file      ijpegenc.h
*
* @brief     JPEG specific interface details
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Jan 2010):Modified for Functionality requirements[Pavan,Vasudev]
*
* @version 0.2 (Feb 2010) : Review & Cleanup [Vasudev]
*
* @version 0.3 (Aug 2010):Debug Trace & error Robustness support added[Vasudev]
*
* @version 0.4 (Dec 2010) : Added support for error recovery and error 
*                           robustness in case of data sync errors[Pavan]
*
* @version 0.5 (Nov 2011) : Added support for Minimum Quality factor 1 and  
*                           Maximum Quality factor 100        [Naidu]
*
* @version 0.6 (Nov 2011) : Create and Dynamic Default structure are exposed to 
*                           Application                       [Naidu]
*
* @version 0.7 (July 2012) : Added support to change marker position JPEG header
*                            [Naidu]
*
* @version 0.8 (Sep 2012) : Added support for Rate Control and Privacy Masking
*                           [Mahantesh]
*
* @version 2.2 (Dec 2012) : Added another value to IJPEGVENC_RateControlAlgo 
*                           enum to support run-time disabling of rate control
*                           [Mahantesh]
* @version 2.3 (May 2013) : Added error check for “non-multiple of 16” 
*                           inputBufDesc->imagePitch [Naidu]
*                          
********************************************************************************
*/

/* -------------------- compilation control switches -------------------------*/
#ifndef JPEGENC_TI_IJPEGVENC_H
#define JPEGENC_TI_IJPEGVENC_H

/**
* Macro for Minimum,maximum & Default Quality Factor
**/
#define IJPEGVENC_MIN_QUALITY_FACTOR      (1)
#define IJPEGVENC_MAX_QUALITY_FACTOR      (100)
#define IJPEGVENC_DEFAULT_QUALITY_FACTOR  (50)

/** 
  Maximum number of PMs supported inside the frame.
*/
#define IJPEGVENC_MAX_PM 36
/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividenc2.h>
#include <ti/xdais/xdas.h>
/*--------------------- program files ----------------------------------------*/

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
/**
********************************************************************************
*  @struct IJPEGVENC_PrivacyMaskingInput  
*
*  @brief  This structure defines the PM input parameters required by Encoder.
*
*  @param  listPM : List of regions to be privacy masked with their x and y 
*                   co-ordinates
*                    
*  @param  noOfPrivacyMaskRegions: Number of PMs passed to codec
*
*  @param  lumaValueForPM : Y pixel value for privacy mask region
*
*  @param  cbValueForPM   : Cb pixel value for privacy mask region
*
*  @param  crValueForPM   : Cr pixel value for privacy mask region
********************************************************************************
*/
typedef struct IJPEGVENC_PrivacyMaskingInput{
  XDM_Rect    listPM[IJPEGVENC_MAX_PM];   
  XDAS_Int32  noOfPrivacyMaskRegions;
  XDAS_UInt8  lumaValueForPM;
  XDAS_UInt8  cbValueForPM;
  XDAS_UInt8  crValueForPM;
  XDAS_UInt8  dummy;         
}IJPEGVENC_PrivacyMaskingInput;
/**
********************************************************************************
*  @struct     IJPEGVENC_Obj
*
*  @brief       This structure must be the first field of all JPEGVENC
*               instance objects
*
*  @param  fxns : Pointer to Functions which performs all the operations on
*                 IJPEGVENC objects.
********************************************************************************
*/
typedef struct IJPEGVENC_Obj {
  struct IJPEGVENC_Fxns *fxns;
} IJPEGVENC_Obj;
/**
******************************************************************************** 
*  @struct IJPEGVENC_RateControlParams
*  @brief  This structure contains all the parameters which controls Rate 
          Control behavior

*  @param  rateControlParamsPreset : 
          regarded @ IJPEGENC_DynamicParams::rateControlParams
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IJPEGVENC_RATECONTROLPARAMS_DEFAULT
*  @param  scalingMatrixPreset  : 
          ignored @ IJPEGENC_DynamicParams::rateControlParams
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IJPEG_SCALINGMATRIX_DEFAULT
          
*  @param  rcAlgo  : ignored @ IJPEGENC_DynamicParams::rateControlParams
          This defines the rate control algorithm to be used. Only useful 
          if IVIDENC2::rateControlPreset is set as IVIDEO_USER_DEFINED

*  @param  qpI  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Initial Quantization Parameter for I/IDR frames. 
          Valid Range is [-1, 51]
          -1 : Auto Initialization else other wise Initial QP.
          when rateControlPreset = IVIDEO_NONE, this quantization parameter is 
          used by the whole video frame/field 

*  @param  qpMaxI  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Maximum Quantization Parameter for I/IDR frame(s). Range [0 , 51]. 
          Useful to control a minimum quality level

*  @param  qpMinI  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Minimum Quantization Parameter for I/IDR frame(s). Range [0 , 51]. 
          Useful to control a maximum bit-rate level

*  @param  qpP  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Initial Quantization Parameter for P frames. Valid Range is [-1, 51]
          -1 : Auto Initialization else other wise Initial QP.
          when rateControlPreset = IVIDEO_NONE, this quantization parameter is 
          used by the whole video frame/field 

*  @param  qpMaxP  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Maximum Quantization Parameter for inter frame(s). Range [0 , 51]. 
          Useful to control a minimum quality level

*  @param  qpMinP  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Minimum Quantization Parameter for inter frame(s). Range [0 , 51]. 
          Useful to control a maximum bit-rate level

*  @param  qpOffsetB  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Offset of B frames Quantization Parameter from P frames. 
          Valid Range is [-1, 51]
          -1 : Auto Initialization else other wise user provided offset
      if after adding the qpOffsetB into qp of P frame it exceeds 51 then
      it is clipped to 51
          when rateControlPreset = IVIDEO_NONE, this offset parameter is 
          used by the whole video frame/field 

*  @param  qpMaxB  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Maximum Quantization Parameter for B frame(s). Range [0 , 51]. 
          Useful to control a minimum quality level

*  @param  qpMinB  : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Minimum Quantization Parameter for B frame(s). Range [0 , 51]. 
          Useful to control a maximum bit-rate level

*  @param  allowFrameSkip: regarded @ IJPEGENC_DynamicParams::rateControlParams
          Controls Frame Skip. 
          non-zero means frames can be skipped to  achieve target bit-rate 
          zero means frame can never be skipped

*  @param  removeExpensiveCoeff : 
          regarded @ IJPEGENC_DynamicParams::rateControlParams
          Flag to Remove high frequency expensive coeffecients 

*  @param  chromaQPIndexOffset  : 
          ignored @ IJPEGENC_DynamicParams::rateControlParams
          Specifies offset to be added to luma QP for addressing QPC values 
          table for chroma components. 
          Valid value is between -12 and 12, (inclusive)

*  @param  IPQualityFactor: ignored @ IJPEGENC_DynamicParams::rateControlParams
          This provides configurality to control I frame Quality wrt to P frame. 
          Higher Quality factor means I frame quality is given higher 
          improtance compared to P frame. 
          Refer IJPEGENC_FrameQualityFactor for possible values

*  @param  initialBufferLevel  : 
          ignored @ IJPEGENC_DynamicParams::rateControlParams
          Initial Buffer level for HRD compliance. It informs that Hypothtical 
          decoder can start after how much time. The value taken is the 
          obsolute value of the HRD buffer size  For example if user want 
          Hypothtical decoder to start taking out data from HRD buffer after 
          half second then it should set initialBufferLevel = half of the 
          HRD buffer size that is programmed. 
          
*  @param  HRDBufferSize : regarded @ IJPEGENC_DynamicParams::rateControlParams
          Hypothetical Reference Decoder Buffer Size. This size controls the 
          frame skip  logic of the encoder. for low delay applications this 
          size should be small. Unit of this variable is bits

*  @param  minPicSizeRatio:regarded @ IJPEGENC_DynamicParams::rateControlParams
                            This ratio is used to compute minimum picture size 
                            in the following manner, 
                            minPicSize = averagePicSize >> minPicSizeRatio
                            allowed values 1 to 4, Setting this to 0 will enable 
                            encoder chosen ratio.  
                            Note that this is guided value to rate control to 
                            determine min picture size and encoder may not 
                            strictly follow this
*  @param  maxPicSizeRatio:regarded @ IJPEGENC_DynamicParams::rateControlParams
                            To determines ratio for max picture size
                            This ratio is used to compute maximum picture size 
                            in the following manner, 
                            maxPicSize = averagePicSize * maxPicSizeRatio
                            allowed values 2 to 30.Setting this to 0 and 1 
                            will enable encoder chosen ratio.  
                            Note that this is guided value to rate control 
                            to determine max picture size and encoder may not 
                            strictly follow this.

*  @param  enablePRC     : regarded @ IJPEGENC_DynamicParams::rateControlParams
                            This flag is used to control allowing PRC in the 
                            frame

*  @param  enablePartialFrameSkip : regarded @ IJPEGENC_DynamicParams::
                                 rateControlParams
                            This flag is used to control allowing partial frame  
                            skip in the frame
*  @param  reserved : 16 bit word, kept to not change the foot print
*  @param  VBRDuration : During over which statistics during interval are  
                        collected to switch bit-rate states.Increasing this  
                        value will make VBR wait for longer time before 
                        switching bit-rate state
*  @param  VBRsensitivity : Specifies the target bitrate used by rate control in 
                           high complexity state. 
*  @param  skipDistributionWindowLength : Number of frames over which the skip  
                                         frames can be distributed  
*  @param  numSkipInDistributionWindow : Number of skips allowed within the 
                                         distribution window 
*  @param  reservedRC
          Some part is kept reserved to add parameters later without 
          changing the foot print of  interface memory

*  @todo  More parameters to be added : delay (VBV), PRC related etc..
********************************************************************************  
*/

typedef struct IJPEGVENC_RateControlParams {
  XDAS_Int8  rateControlParamsPreset ;
  XDAS_Int8  scalingMatrixPreset     ;
  XDAS_Int8  rcAlgo                  ;
  XDAS_Int8  qpI                     ;
  XDAS_Int8  qpMaxI                  ;
  XDAS_Int8  qpMinI                  ;
  XDAS_Int8  qpP                     ;
  XDAS_Int8  qpMaxP                  ;
  XDAS_Int8  qpMinP                  ;
  XDAS_Int8  qpOffsetB               ;
  XDAS_Int8  qpMaxB                  ;
  XDAS_Int8  qpMinB                  ;
  XDAS_Int8  allowFrameSkip          ;
  XDAS_Int8  removeExpensiveCoeff    ;
  XDAS_Int8  chromaQPIndexOffset     ;
  XDAS_Int8  IPQualityFactor         ;
  XDAS_Int32 initialBufferLevel      ;
  XDAS_Int32 HRDBufferSize           ;
  XDAS_Int16 minPicSizeRatioI        ; 
  XDAS_Int16 maxPicSizeRatioI        ; 
  XDAS_Int16 minPicSizeRatioP        ; 
  XDAS_Int16 maxPicSizeRatioP        ; 
  XDAS_Int16 minPicSizeRatioB        ; 
  XDAS_Int16 maxPicSizeRatioB        ; 
  XDAS_Int8  enablePRC               ;
  XDAS_Int8  enablePartialFrameSkip  ;
  XDAS_Int8  discardSavedBits        ;
  XDAS_Int8  reserved                ;
  XDAS_Int32 VBRDuration            ;
  XDAS_Int8  VBRsensitivity          ;
  XDAS_Int16 skipDistributionWindowLength;
  XDAS_Int16 numSkipInDistributionWindow;
  XDAS_Int8  enableHRDComplianceMode ;
  XDAS_Int32 frameSkipThMulQ5        ;
  XDAS_Int32 vbvUseLevelThQ5         ;
  XDAS_Int32 reservedRC[3]           ; 

} IJPEGVENC_RateControlParams ;

/**
********************************************************************************
*  @struct     IJPEGVENC_Status
*
*  @brief       Status structure defines the parameters that can be changed or
*               read during real-time operation of the alogrithm.
*
*  @param videnc2Status : This structure holds all the status parameters for
*                         IVIDENC2 Objects
********************************************************************************
*/
typedef struct IJPEGVENC_Status {
  /*--------------------------------------------------------------------------*/
  /* Base Class                                                               */
  /*--------------------------------------------------------------------------*/
  IVIDENC2_Status videnc2Status;

  /*--------------------------------------------------------------------------*/
  /*Debug trace Level : Possible values are 0,1,2,3,4                         */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32 debugTraceLevel;

  /*--------------------------------------------------------------------------*/
  /* Number of last frames to log the debug info                              */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32 lastNFramesToLog;

  /*--------------------------------------------------------------------------*/
  /* base address of the trace buffer in external memory                      */
  /*--------------------------------------------------------------------------*/  
  XDAS_UInt32 * extMemoryDebugTraceAddr;
  
  /*--------------------------------------------------------------------------*/
  /* Size of the trace buffer                                                 */
  /*--------------------------------------------------------------------------*/    
  XDAS_UInt32 extMemoryDebugTraceSize;

  /*--------------------------------------------------------------------------*/
  /* Extended Error Code0 returned by encoder                                 */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32 extendedErrorCode0;
  
  /*--------------------------------------------------------------------------*/
  /* Extended Error Code1 returned by encoder                                 */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32 extendedErrorCode1;
  
  /*--------------------------------------------------------------------------*/
  /* Extended Error Code2 returned by encoder                                 */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32 extendedErrorCode2;
  
  /*--------------------------------------------------------------------------*/
  /* Extended Error Code3 returned by encoder                                 */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32 extendedErrorCode3;  
  /*--------------------------------------------------------------------------*/
  /* Rate control param structure                                             */
  /*--------------------------------------------------------------------------*/
  IJPEGVENC_RateControlParams rateControlParams;
  /*--------------------------------------------------------------------------*/
  /* Flag to enable Privacy Masking                                           */
  /*--------------------------------------------------------------------------*/  
  XDAS_Int32  enablePrivacyMasking;

} IJPEGVENC_Status;

/**
********************************************************************************
*  @struct     IJPEGVENC_Params
*
*  @brief       This structure defines the creation parameters for
*               all JPEGVENC objects
*
*  @param  videnc2Params :Create time Parameter structure
*
*  @param  maxThumbnailHSizeApp0:Max Horizontal resolution for APP0
*                                   thumbnail
*  @param  maxThumbnailVSizeApp0 :Max Vertical resolution for APP0
*                                    thumbnail
*  @param  maxThumbnailHSizeApp1:Max Horizontal resolution for APP1
*                                   thumbnail
*  @param  maxThumbnailVSizeApp1 :Max Vertical resolution for APP1
*                                    thumbnail
*  @param  chm_dc_vlc[12] :Chroma AC codes
********************************************************************************
*/
typedef struct IJPEGVENC_Params {
  /*--------------------------------------------------------------------------*/
  /* Base Class                                                               */
  /*--------------------------------------------------------------------------*/
  IVIDENC2_Params videnc2Params;
  
  /*--------------------------------------------------------------------------*/
  /* Max Horizontal resolution for APP0 thumbnail                             */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16     maxThumbnailHSizeApp0;

  /*--------------------------------------------------------------------------*/
  /* Max Vertical resolution for APP0 thumbnail                               */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16     maxThumbnailVSizeApp0;
  
  /*--------------------------------------------------------------------------*/
  /* Max Horizontal resolution for APP1 thumbnail                             */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16     maxThumbnailHSizeApp1;

  /*--------------------------------------------------------------------------*/
  /* Max Vertical resolution for APP0 thumbnail                               */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16     maxThumbnailVSizeApp1;

  /*--------------------------------------------------------------------------*/
  /*Debug trace Level                                                         */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32   debugTraceLevel;

  /*--------------------------------------------------------------------------*/
  /*History of last N frames                                                  */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32   lastNFramesToLog;  
  /*--------------------------------------------------------------------------*/
  /*Marker positions modification                                             */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32   Markerposition;
  /*--------------------------------------------------------------------------*/
  /* Rate control param structure                                             */
  /*--------------------------------------------------------------------------*/
  IJPEGVENC_RateControlParams rateControlParams;
  
} IJPEGVENC_Params;

typedef IVIDENC2_Cmd IJPEGVENC_Cmd;

/**
********************************************************************************
*  @struct     IJPEGVENC_CustomQuantTables
*
*  @brief      JPEG Encoder Custom Quantization Tables - This structure defines
*              the custom quantization tables for both Luma & Chroma that need
*              to be passed to the JPEG Encoder. This will be used in the
*              Quantization Module.The format is as specified in RFC 2035
*              (RTP Payload Format for JPEG-compressed Video) and also in
*              Table K.1 & K.2 of JPEG Spec.
*
*              NOTE: The "IJPEGVENC_DynamicParams" structure defined below
*              contains a pointer to this structure of type
*              "IJPEGVENC_CustomQuantTables" -
*              "IJPEGVENC_CustomQuantTables *quantTable".
*              This field is used to pass custom Quantization tables to the
*              JPEG Encoder.The application just needs to initialize this field
*              appropriately.However, if the application wishes to use the
*              Standard Quantization Tables,then there are 2 ways of informing
*              this to the JPEG Encoder -
*             (a) by using the base class only "IJPEGVENC_DynamicParams" and not
*                 the extended class "IJPEGVENC_DynamicParams", in which case
*                 the size field in the DynamicParams structure should be set to
*                 the size of "IJPEGVENC_DynamicParams".
*             (b) by using the extended class "IJPEGVENC_DynamicParams", but by
*                 setting the field "IJPEGVENC_CustomQuantTables *quantTable" to
*                 NULL.
*
*  @param  lumQuantTab :This defines the quantization table for the luma
*                       component.
*  @param  chmQuantTab :This defines the quantization table for the chroma
*                       component.
********************************************************************************
*/
typedef struct IJPEGVENC_CustomQuantTables
{
  /*--------------------------------------------------------------------------*/
  /* The array "lumQuantTab" defines the quantization table for the luma      */
  /*  component.                                                              */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16 lumQuantTab[64];

  /*--------------------------------------------------------------------------*/
  /* The array "chmQuantTab" defines the quantization table for the chroma    */
  /* component.                                                               */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16 chmQuantTab[64];

} IJPEGVENC_CustomQuantTables;

/**
********************************************************************************
*  @struct     IJPEGVENC_DynamicParams
*
*  @brief       This structure defines the dynamic parameters for
*               all JPEGVENC objects
*
*  @param videnc2DynamicParams: IVIDENC2_Dynamic Params
*  @param restartInterval     : Restart Interval
*  @param qualityFactor       : Quality factor
*  @param quantTable          : User Defined Quant Table
*  @param rateControlParams   : Rate Control Params
*  @param enablePrivacyMasking: Flag to enable Privacy Masking
********************************************************************************
*/
typedef struct IJPEGVENC_DynamicParams {
  /*--------------------------------------------------------------------------*/
  /* Base Class                                                               */
  /*--------------------------------------------------------------------------*/
  IVIDENC2_DynamicParams videnc2DynamicParams;
  
  /*--------------------------------------------------------------------------*/
  /* restartInterval : Specifies the number of MCUs between RST markers       */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32             restartInterval;

  /*--------------------------------------------------------------------------*/
  /* qualityFactor : Specifies the quality setting to use for encoding        */
  /*                 Supported values are from 0 (lowest quality)             */
  /*                 to 97 (highest quality)                                  */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32             qualityFactor;

  /*--------------------------------------------------------------------------*/
  /* quantTable : Application should populate the custom quant table in a     */
  /*              structure of type IJPEGVENC_CustomQuantTables and pass the  */
  /*              pointer to it here. Set it to NULL if custom quant tables   */
  /*              are not to be used.                                         */
  /*--------------------------------------------------------------------------*/
  IJPEGVENC_CustomQuantTables *quantTable;
  /*--------------------------------------------------------------------------*/
  /* Rate control param structure                                             */
  /*--------------------------------------------------------------------------*/
  IJPEGVENC_RateControlParams rateControlParams;
  /*--------------------------------------------------------------------------*/
  /* Flag to enable Privacy Masking                                           */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32             enablePrivacyMasking;
  
} IJPEGVENC_DynamicParams;

/**
********************************************************************************
*  @struct     IJPEGVENC_InArgs
*
*  @brief       This structure defines the runtime input arguments
*               for IJPEGVENC::process
*
*  @param videnc2InArgs            : IVIDENC2_InArgs
*  @param APPN0                    : APP0 thumbnail Buffer
*  @param thumbnailIndexApp0       : JFIF Thumbnail Enable
*  @param APPN1                    : APP1 thumbnail Buffer
*  @param thumbnailIndexApp1       : EXIF Thumbnail Enable
*  @param Comment                  : Comment Data
*  @param pmInputParams            : Privacy Masking Params
********************************************************************************
*/

typedef struct IJPEGVENC_InArgs {
  /*--------------------------------------------------------------------------*/
  /* Base Class                                                               */
  /*--------------------------------------------------------------------------*/
  IVIDENC2_InArgs videnc2InArgs;
  
  /*--------------------------------------------------------------------------*/
  /* APPN0 : buffer holding the data for APP-0 Marker                         */
  /*--------------------------------------------------------------------------*/
  XDM2_SingleBufDesc  APPN0;

  /*--------------------------------------------------------------------------*/
  /* thumbnailIndexApp0 :                                                     */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16    thumbnailIndexApp0;

  /*--------------------------------------------------------------------------*/
  /* APPN1 : buffer holding the data for APP-1 Marker                         */
  /*--------------------------------------------------------------------------*/
  XDM2_SingleBufDesc  APPN1;

  /*--------------------------------------------------------------------------*/
  /* Thumbnail_Index_App0 :                                                   */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt16    thumbnailIndexApp1;

  /*--------------------------------------------------------------------------*/
  /* Comment : buffer holding the data for comment Marker                     */
  /*--------------------------------------------------------------------------*/
  XDM2_SingleBufDesc  Comment;
  
  /*--------------------------------------------------------------------------*/
  /* Privacy Masking Params                                                   */
  /*--------------------------------------------------------------------------*/
  IJPEGVENC_PrivacyMaskingInput pmInputParams;

} IJPEGVENC_InArgs;

/**
********************************************************************************
*  @struct     IJPEGVENC_OutArgs
*
*  @brief  This structure defines the runtime output arguments
*          for IJPEGVENC::process
*
*  @param  videnc2OutArgs : This structure contains run time output arguments 
*                           for all IVIDENC2 instance objects
*  @param  vbvBufferLevel : This varible tells the buffer level at the end
*                           of every picture from decoder perspective.
********************************************************************************
*/

typedef struct IJPEGVENC_OutArgs {
  IVIDENC2_OutArgs videnc2OutArgs;
  XDAS_Int32 vbvBufferLevel;
} IJPEGVENC_OutArgs;

/**
********************************************************************************
*  @struct     IJPEGVENC_Fxns
*
*  @brief       This structure defines all of the operations on
*               JPEGVENC objects.
*  @param ividenc : Pointer to Functions which performs all the operations on
*                   IVIDENC2 objects.
********************************************************************************
*/
typedef struct IJPEGVENC_Fxns {
  IVIDENC2_Fxns ividenc;
} IJPEGVENC_Fxns;

/**
 * The error codes correspond to the 32-bit extended error parameter passed 
 * through outargs and get sttus. The error have been categorised to the below 
 * 32 groups and the respective bit is set on error occurrence.
 */
typedef enum
{
  IJPEGVENC_ERR_UNSUPPORTED_VIDENC2PARAMS = 0,
  IJPEGVENC_ERR_UNSUPPORTED_VIDENC2DYNAMICPARAMS,            
  IJPEGVENC_ERR_UNSUPPORTED_JPEGENCDYNAMICPARAMS,              
  IJPEGVENC_ERR_IMPROPER_DATASYNC_SETTING,      
  IJPEGVENC_ERR_NOSLICE,     
  IJPEGVENC_ERR_SLICEHDR,            
  IJPEGVENC_ERR_MBDATA,            
  IJPEGVENC_ERR_UNSUPPFEATURE,     
  IJPEGVENC_ERR_STREAM_END = 16,            
  IJPEGVENC_ERR_INVALID_MBOX_MESSAGE,    
  IJPEGVENC_ERR_HDVICP_RESET,
  IJPEGVENC_ERR_HDVICP_WAIT_NOT_CLEAN_EXIT,
  IJPEGVENC_ERR_IRES_RESHANDLE,
  IJPEGVENC_ERR_STANDBY,

  /* Error Codes for Data Sync */
  IJPEGVENC_ERR_INPUT_DATASYNC,
  IJPEGVENC_ERR_OUTPUT_DATASYNC,
  
  IJPEG_ERR_PRIVACY_MASKING_PARAMS,
  IJPEG_ERR_RATECONTROLPARAMS
}IJPEGVENC_ExtendedErrorCodes;

/**
 * The enum corresponds to the 4 32-bit words used to pass the error codes to 
 * the application in the extended parameters of status stucture through the 
 * getstatus command. Each bit is set for an error which falls under one of 
 * the groups in the outargs 32 bvits.
 */
typedef enum
{
  JPEG_DYNAMIC_PARAMS_HANDLE_ERROR = 0,
  JPEG_STATUS_HANDLE_ERROR,
  JPEG_DYNAMIC_PARAMS_SIZE_ERROR,
  JPEG_ENCODE_HEADER_ERROR,
  JPEG_UNSUPPORTED_RESOLUTION,
  JPEG_CAPTURE_WIDTH_ERROR,
  JPEG_GET_DATA_FXN_NULL_POINTER,
  JPEG_GET_BUFFER_FXN_NULL_POINTER,
  JPEG_INVALID_RESTART_INTERVAL_ERROR,
  JPEG_INVALID_QUALITY_FACTOR_ERROR,
  JPEG_INVALID_INPUT_CHROMA_FORMAT_ERROR,
  JPEG_NULL_QUANT_TABLE_POINTER_ERROR,
  JPEG_NULL_INARGS_POINTER_ERROR,
  JPEG_NULL_INARGS_APP_POINTER_ERROR,
  JPEG_INARGS_SIZE_ERROR,
  JPEG_INVALID_INPUT_BYTES_ERROR,
  JPEG_INVALID_INPUT_ID_ERROR,
  JPEG_NULL_INPUT_BUF_DESC_ERROR,
  JPEG_NULL_INPUT_BUFFER_POINTER_ERROR,
  JPEG_INVALID_INPUT_BUFFER_SIZE_ERROR,
  JPEG_INVALID_NUM_OF_INPUT_BUFFERS_ERROR,
  JPEG_INVALID_INPUT_BUFFER_MEMTYPE_ERROR,
  JPEG_INVALID_OUTPUT_BUFFER_MEMTYPE_ERROR,
  JPEG_NULL_OUTARGS_POINTER_ERROR,
  JPEG_INVALID_OUTARGS_SIZE,
  JPEG_NULL_OUTPUT_BUF_DESC_ERROR,
  JPEG_NULL_OUTPUT_BUFFER_POINTER_ERROR,
  JPEG_INVALID_OUTPUT_BUFFER_SIZE_ERROR,
  JPEG_INVALID_NUM_OF_OUTPUT_BUFFERS_ERROR,
  JPEG_INSUFFICIENT_OUTPUT_BUFFER_SIZE_ERROR,
  JPEG_INVALID_JFIF_THUMBNAIL_ENABLE_ERROR,
  JPEG_INVALID_EXIF_THUMBNAIL_ENABLE_ERROR,
  JPEG_INPUT_BUFFER_POINTER_ALIGN_ERROR,
  
  /* Extended Error Codes related to Data Sync */
  JPEG_DATASYNC_GET_ROW_DATA_ERROR, /* from 33rd bit*/
  
  JPEG_DATASYNC_INVALID_RESTART_INTERVAL_ERROR,
  
  JPEG_DATASYNC_BLOCK_POINTER_ERROR,
  JPEG_DATASYNC_BLOCK_SIZE_ERROR,
  JPEG_DATASYNC_INVALID_BLOCKS_ERROR,
  JPEG_DATASYNC_NOT_VALID_COMBINATION_ERROR,
  JPEG_INVALID_IMAGEPITCH
}IjpegVENC_ErrorStatus;

/**
  @enum   IJPEGVENC_RateControlParamsPreset
  @brief  These enumerations control the RateControl Params  
*/

typedef enum
{
  IJPEGVENC_RATECONTROLPARAMS_DEFAULT     = 0 , 
      /**< Default Rate Control params */
  IJPEGVENC_RATECONTROLPARAMS_USERDEFINED = 1 , 
      /**< User defined Rate Control params */
  IJPEGVENC_RATECONTROLPARAMS_EXISTING    = 2 , 
      /**< Keep the Rate Control params as existing. This is 
      * useful because during control call if user don't want 
      * to change the Rate Control Params
      */
  IJPEGVENC_RATECONTROLPARAMS_MAX

} IJPEGVENC_RateControlParamsPreset;

/**
  @enum   IJPEGVENC_PrivacyMaskingInputParams
  @brief  These enumerations control the Privacy Masking Params  
*/
typedef enum
{
  IJPEGVENC_PRIVACYMASKING_DISABLE = 0,
  /**< Disable Privacy Masking */
  IJPEGVENC_PRIVACYMASKING_ENABLE
  /**< Enable Privacy Masking  */
}IJPEGVENC_PrivacyMaskingInputParams;

/**
  
  @enum   IJPEGVENC_RateControlAlgo
  @brief  These enumerations control the type of rateControl algo to be picked
          up by encoder. Only useful if IVIDENC2::rateControlPreset is set as 
          IVIDEO_USER_DEFINED
  
*/
typedef enum
{
  IJPEGVENC_RATECONTROL_VBR_STORAGE       = 0 ,        
  /** VBR - Storage Rate Control   */
  IJPEGVENC_RATECONTROL_CBR_LOW_DELAY     = 1 ,        
  /** CBR - Low Delay Rate Control */
  IJPEGVENC_RATECONTROL_DISABLE           = 2
  /** Disable Rate Control */  
} IJPEGVENC_RateControlAlgo;
/**
******************************************************************************
 *  ======== IJPEGVENC_DynamicParams ========
 *  Default Create parameter values for JPEGVENC instance objects
********************************************************************************
*/
extern const IJPEGVENC_DynamicParams JPEGVENC_TI_DYNAMICPARAMS;
/**
******************************************************************************
 *  ======== IJPEGVENC_Params ========
 *  Default DynamicParams values for JPEGVENC instance objects
********************************************************************************
*/
extern const IJPEGVENC_Params JPEGVENC_TI_PARAMS;

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

#endif /*#ifndef JPEGENC_TI_IJPEGVENC_H*/

