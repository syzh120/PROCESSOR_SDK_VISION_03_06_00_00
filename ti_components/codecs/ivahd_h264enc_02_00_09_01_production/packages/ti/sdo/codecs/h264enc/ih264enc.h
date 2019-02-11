/*
 *******************************************************************************
 *
 * HDVICP2.0 Based H.264 HP Encoder
 * 
 * "HDVICP2.0 Based H.264 HP Encoder" is software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw 
 *  video into a high/main/baseline profile bit-stream. Based on ISO/IEC      
 *  14496-10." 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *******************************************************************************
*/

/**
  ******************************************************************************
  *  @file     ih264enc.h
  *
  *  @brief    IH264ENC Interface Header
  *
  *  @author   Pramod Kumar Swami (pramods@ti.com)
  *
  *  @version  0.1 - Nov 30,2008 : Initial Version [Pramod] 
  *
  *  @version  0.2 - March 16,2009 [Pramod] 
  *    A. Name change of interface file ih264venc.h to ih264enc.h 
  *    B.Change the name of macros/enums  
  *       MAXNUMSLCGPS  --> IH264ENC_MAXNUMSLCGPS
  *      MAX_NUM_SLICE_START_OFFSET --> IH264ENC_MAX_NUM_SLICE_START_OFFSET
  *      IH264ENC_GOPSTRUCTURE_OPEN --> IH264ENC_GOPSTRUCTURE_NONUNIFORM
  *      IH264ENC_GOPSTRUCTURE_CLOSE  --> IH264ENC_GOPSTRUCTURE_UNIFORM
  *    C. Definition of IH264ENC_BufferLevel changed from buffer to time    
  *    D. mbMetaDataEnable is defined
  *    E. Following information (fields/definition) is newly added    
  *       IH264ENC_VERSION_LENGTH : For getting the encoder version via Control 
  *       method
  *       meta data support (IH264ENC_MAX_SEI_METADTA_BUFSIZE)    
  *       Support and definition of Error Codes   
  *       Enum for level 3.0 and 3.1 was missing added    
  *       Poc type 1 enum added   
  *       Support for NALU masks: no change in definition   
  *       Few more enumeration added for IH264ENC_VUICodingPreset, 
  *       IH264ENC_VideoFormat and IH264ENC_AspectRatioIdc    
  *       IH264ENC_VUICodingParams structure parameter added to creation 
  *       time parameters   
  *       New enumeration added to IH264ENC_InterlaceCodingType: MRF, SPF   
  *
  *  @version  0.3 - November 2009 [Pramod] 
  *    A. Added interface for force SKIP, it is temporarily here and will be 
  *       used from base class of IVIDENC later
  *    B. Added user defined scaling matrix bit in input meta data
  *  @version 0.4 - Feb 2010 [Deepak]
  *       Addition of error bit(IH264ENC_ErrorBit : bit 7) for max bit rate 
  *       voilation scenario in tighter RC scenario
  *  @version  0.5 - Mar 2010 [Kumar] : Added more enumerations to have all 
  *     levels supported by H264 standard to make it future proof.
  *  @version  0.6 - Apr 2010 [Kumar] : Added error bit for checking 
  *            hdvicp state IH264ENC_IMPROPER_HDVICP2_STATE
  *  @version  0.7 - Jun 2010  : [Nirmal, Pramod] Changed default value of 
  *                              BufferLevel since its is not good for
  *                              low delay applications (IR: SDOCM00071692)
  *  @version  0.8 - Apr 2010 [Uday] : Modified the definition of initial 
  *     buffer level from taking in descrete values to continuas values 
  *  @version  0.9 - May 2010 [Uday] : converted the reserve parameter for 
  *            enabling GMV in SEI to dedicated parameter 
  *  
  *  @version  0.10 - May 2010 [Uday] : Extended the outArgs to return the 
  *                                    initial buffer level 
  *  @version  0.11 -Jun 2010 [Uday] : Added interface constraint set flags
  *  @version  0.12 - Aug 2010 [Nirmal] : Added data elements for static MB
  *                                       count support
  *  @version  0.13 -Aug 2010 [Girish Murthy] : Added interface for
  *                                             RCDO profile support
  * @ version  0.14 -Sep 2010 [Kumar] : Defined a bit for 
  *                          IH264ENC_MAX_BYTES_VOILATION_IN_SLICEMODE_BYTES
  * @ version  0.15 -Sep 2010 [Kumar] : Added a new extenetd parameter for 
  *                              algorithm creation enableLongTermRefFrame
  * @version 0.16- Sept 2010[Girish]: Support for PRC and partial frame
  *                                    skip control
  * @version 0.17 Sep 2010 : Added flag to control the insertion of
  *                           HRD parameters in VUI part of bit-stream[Nirmal] 
  * @version 0.18 Sep2010 : Added error bit IH264ENC_DATASYNCH_RUN_TIME_ERROR 
  *                        multiplexed with IH264ENC_UNSUPPORTED_FMOCODINGPARAMS
  * @version 0.19 Sep2010 : Added IH264ENC_FramePackingParams structure 
  *                         required for encoding the frame packing SEI
  * @version 0.20 Sep 2010 : [Gajanan] Added IH264ENC_StereoInfoParams
  *                              Structure for Steroe Video Coding 
  *                              parameters and StereoInfoPreset enums.
  * @version 0.21 Apr 2011 : [Kumar] Added support for new long-
  *                            trem frame referencing scheme
  *                            IH264ENC_LTRP_REFERTOP_PROACTIVE
  * @version 0.22 June 2011: Inroduction of new preset
  *                          IH264_INTERCODING_MED_SPEED_HIGH_QUALITY for 
  *                           inter coding preset.
  * @version 0.23 July 2011: Added discardSavedBits in RateControl structure
  *                            SDOCM00082533
  * @version 0.24 July 2011: Added structures and enum for ROI support.[Gajanan] 
  * @version  1.0 Dec 2011: Added parameter for HRD compliance control[Girish]
  * @version  1.1 Dec 2011: Added frameSkipThMulQ5 & vbvUseLevelThQ5 in
  *                         RateControl structure for CBR quality improvement
  *                         [Karthick]
  * @version  1.2 Jan 2012: Renamed MAX_ROI macro as IH264ENC_MAX_ROI
  *                         [Harris]
  * @version  1.3 Mar 2012: Added a parameter enableErrorCheck  in 
  *                         IH264ENC_ProcessParamsList.[Santoshkumar S K]
  * @version  1.4 May 2012: Changed parameter name. Replaced 
  *                         inArgs->lateAcquireArg by inArgs->processId.
  *                         [Santoshkumar S K]
  * @version  1.5 May 2012: SDOCM00091641 : Added temporalId parameter to 
  *                         IH264ENC_OutArgs.This holds the Temporal
  *                         layer Id of current frame in H-P encoding.
  *                         (for base layer value is 0)[Santoshkumar S K]
  * @version  1.6 Aug 2012: Redundant exposure of GDR configuration 
  *                         parameters as a part of Extended Dynamic structure
  *                         are removed(SDOCM00095027)[Santoshkumar S K]
  * @version  1.7 Sep 2012: Default value of scalingmatrixPreset is changed
  *                         from NONE(0) to NORMAL(1)[Santoshkumar S K]
  * @version  1.8 Feb 2013: Fix for OMAPS00288660: Ducati returns an error 
  *                         when setting a slice size larger than 32768.
  *                         Fix : sliceUnitSize parameter's data type is changed
  *                         from XDAS_Int16 to XDAS_Int32 [Santoshkumar S K] 
  * @version  1.9 Mar 2013: a. Added IH264ENC_ExtErrBits enum structure to fix
  *                         SDOCM00099577(Encoder does not give refined error 
  *                         codes in case of creation fail or run time parameter
  *                         set fail)
  *                         b. Parameter extErrorCode[] is added in 
  *                         IH264ENC_Status and IH264ENC_OutArgs structure
  *                         [Santoshkumar S K]
 *****************************************************************************
*/

/**
 *  @defgroup   HDVICP2H264 IH264ENC_TI (V7M)
 *  @ingroup    m3
 *
 *              The IH264ENC_TI interface enables encoding in H264 format
 *
 */

#ifndef _IH264ENC_H_  /* --{                                                  */

#define _IH264ENC_H_

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividenc2.h>

/** @ingroup    HDVICP2H264 */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Definition of all the macros define by this interafce       */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** 
  Maximum number of slice groups supported by H.264 Encoder 
*/
#define IH264ENC_MAXNUMSLCGPS (2)  

/** 
  Maximum Number of slice start points
*/
#define IH264ENC_MAX_NUM_SLICE_START_OFFSET  (3) 

/** maximum size for SEI_USER_DATA_UNREGISTERED SEI message */
#define IH264ENC_MAX_SEI_METADTA_BUFSIZE (0x3FF) 

/** 
  Length of the version string. The memory to get version 
  number is owned by application
*/
#define IH264ENC_VERSION_LENGTH (64)  

/** 
  control method commands
*/
#define IH264ENC_GETSTATUS      XDM_GETSTATUS
#define IH264ENC_SETPARAMS      XDM_SETPARAMS
#define IH264ENC_RESET          XDM_RESET
#define IH264ENC_FLUSH          XDM_FLUSH
#define IH264ENC_SETDEFAULT     XDM_SETDEFAULT
#define IH264ENC_GETBUFINFO     XDM_GETBUFINFO

/** 
  Maximum number of ROIs supported inside the frame.
*/
#define IH264ENC_MAX_ROI 36 

typedef IVIDENC2_Cmd IH264ENC_Cmd;

/** 
  Macro to set particular NAL bit in the nal unit mask
*/
#define IH264ENC_SET_NALU(naluPresentMask, NALU) \
{ \
  naluPresentMask = ((naluPresentMask) | (1 << IH264_NALU_TYPE_##NALU)) ;\
}

/** 
  Macro to clear particular NAL bit in the nal unit mask
*/
#define IH264ENC_CLEAR_NALU(naluPresentMask, NALU) \
{ \
  naluPresentMask = ((naluPresentMask) & (~(1 << IH264_NALU_TYPE_##NALU))) ;\
}

/** 
  Macro to get particular NAL bit in the nal unit mask
*/
#define IH264ENC_GET_NALU(naluPresentMask, NALU)\
  ((naluPresentMask) & (1    << IH264_NALU_TYPE_##NALU))



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Definition of all the Enumeration define by this interafce  */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 *  @enum       IH264ENC_ErrorBit
 *  @brief      error informations of IVAHD H264 encoder implementation by TI.
 *
 *  @remarks    When an internal error occurs, the algorithm will return
 *              an error return value (e.g. EFAIL, EUNSUPPORTED)
 *
 *  @remarks    The value of each enum is the bit which is set.
 *
 *  @remarks    Bits 8-15 are defined by XDM and hence not used by codec 
 *              implementation.
 *              rest all bits are used. XDM defined error bits are also active.
 *
 *  @remarks    The algorithm can set multiple bits to 1 based on conditions.
 *              e.g. it will set bits #XDM_FATALERROR (fatal) and
 *              #XDM_UNSUPPORTEDPARAM (unsupported params) in case
 *              of unsupported run time parameters.
 *
 */

typedef enum {
  IH264ENC_LEVEL_INCOMPLAINT_PARAMETER = 0, 
          /**< Bit 0 - level incomplaint parameters.
          *   @remarks  This error is applicable when some parameters are set 
          *   which are not meeting the limit defined by H.264 standard 
          *   Table A-1 – Level limits. It can be categorized under 
          *   following category : 
          *   IH264ENC_LEVEL_INCOMPLAINT_RESOLUTION : Invalid width/height
          *   IH264ENC_LEVEL_INCOMPLAINT_HRDBUFSZIE : Invalid HrdBufferSize
          *   IH264ENC_LEVEL_INCOMPLAINT_BITRATE    : Invalid Bit Rate         
          *   IH264ENC_LEVEL_INCOMPLAINT_MBSPERSECOND : Invalid FrameRate/
          *                                             resolution
          *   IH264ENC_LEVEL_INCOMPLAINT_DPBSIZE      : Invalid DPB size
          *   For above 5 situations, only a signle bit (bit-0) is set as true
          */

  IH264ENC_PROFILE_INCOMPLAINT_CONTENTTYPE = 1, 
         /**< Bit 1 - Profile incomplaint content type.
          *   @remarks  This error is applicable when 
          *   IVIDENC2_Params::inputContentType is not set as 
          *   IVIDEO_PROGRESSIVE but IVIDENC2_Params::profile is set 
          *   as IH264_BASELINE_PROFILE
          */

  IH264ENC_PROFILE_INCOMPLAINT_FMO_SETTING = 2, 
          /**< Bit 2 - Profile incomplaint FMO setting.
          *   @remarks  This error is applicable when FMO is enabled but 
          *   IVIDENC2_Params::profile is not set as IH264_BASELINE_PROFILE
          */
          
  IH264ENC_PROFILE_INCOMPLAINT_TRANSFORMBLOCKSIZE = 3 , 
          /**< Bit 3 - Profile incomplaint transform block size.
          *   @remarks  This error is set when 
          *   IH264ENC_Params::transformBlockSize != IH264_TRANSFORM_4x4 &&
          *   IVIDENC2_Params::profile != IH264_HIGH_PROFILE
          */
  
  IH264ENC_PROFILE_INCOMPLAINT_INTERFRAMEINTERVAL = 4 ,
          /**< Bit 4 - Profile incomplaint interframeInterval.
          *   @remarks  This error is set when B frames are used with
          *   IH264_BASELINE_PROFILE
          */

  IH264ENC_PROFILE_INCOMPLAINT_SCALINGMATRIXPRESET = 5,
          /**< Bit 5 - Profile incomplaint scaling matrix setting.
          *   @remarks  This error is set when scaling matrix is used
          *   without IH264_HIGH_PROFILE
          */

  IH264ENC_PROFILE_INCOMPLAINT_ENTROPYCODINGMODE = 6,
          /**< Bit 6 - Profile incomplaint entropy coding mode setting.
          *   @remarks  This error is set when cabac is used 
          *   without IH264_HIGH_PROFILE/MAIN profile
          */

  IH264ENC_MAX_BYTES_VOILATION_IN_SLICEMODE_BYTES = 6,
          /**< Bit 6 - If number of bytes encoded in any of the 
          *  slice in the currently encoded picture is crossing
          *  maximum unbit size then this bit will be set
          *   @remarks  This error bit is shared between the 
          *   create time parameter entropy coding mode
          *   
          */

  IH264ENC_MAX_BIT_RATE_VOILATION = 7,
          /**< Bit 7 - Max bits for one Unit Voilation
           * @remarks When max bit rate is enabled by user,
           * than it is possible that codec might not be able
           * honor max bit rate. This bit is set when bits consumed
           * in one unit ( 1 sec) is more than the allocated as per the
           * given max bit rate. If the frame rate is N , and if the
           * max bit rate is voilated in M th frame than this bit will
           * get set for frame M to N.
           */
  IH264ENC_IMPROPER_HDVICP2_STATE = 16, 
          /**< Bit 16 - Device is not proper state to use.
          */
          
  IH264ENC_IMPROPER_STREAMFORMAT = 17, 
          /**< Bit 17 - stream format is not proper
          *   @remarks  This error is set when streamFormat is set as
          *   IH264_NALU_STREAM but data synch is not enabled for putdata
          */

  IH264ENC_IMPROPER_POCTYPE = 18,
          /**< Bit 18 - poc type is not proper
          *   @remarks  This error is set when poc type 2 is used in 
          *   presense of non reference frames 
          */

  IH264ENC_IMPROPER_DATASYNC_SETTING = 19, 
          /**< Bit 19 - data synch settings are not proper
          *   @remarks  This error is set when encoder is asked to operate
          *   at sub frame level but the call back function pointer is NULL
          */

  IH264ENC_UNSUPPORTED_VIDENC2PARAMS = 20, 
          /**< Bit 20 - Invalid videnc2 parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IVIDENC2_Params is not in allowed range
          */

  IH264ENC_UNSUPPORTED_RATECONTROLPARAMS = 21,
          /**< Bit 21 - Invalid rate control parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_RateControlParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_INTERCODINGPARAMS = 22,
          /**< Bit 22 - Invalid inter coding parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_InterCodingParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_INTRACODINGPARAMS = 23,
          /**< Bit 23 - Invalid Intra coding parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_IntraCodingParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_NALUNITCONTROLPARAMS = 24,
          /**< Bit 24 - Invalid nal unit coding parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_NALUControlParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_SLICECODINGPARAMS = 25,
          /**< Bit 25 - Invalid slice coding parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_SliceCodingParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_LOOPFILTERPARAMS = 26,
          /**< Bit 26 - Invalid loop filter related parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_LoopFilterParams is not in allowed range
          */
  IH264ENC_DATASYNCH_RUN_TIME_ERROR = 27,
          /**< Bit 27 is muxed with incorrect FMO paramters setting.
          *  This will be set when codec inside IVAHD encounters 
          *  erroneous situation, like 
          *  a) when number of NALs in 1Kb of data is more than 8
          *  b) when the blocks provided through getBuf call is not
          *     sufficient for all the NALs in one oage of SL2 stream.
          */
  IH264ENC_UNSUPPORTED_N_FRAME_PROCESSCALL_PARAMS = 27,
          /**< Bit 27 is also muxed with incorrect paramters setting in 
           * N frame process call scenario
          */
  IH264ENC_UNSUPPORTED_FMOCODINGPARAMS = 27,
          /**< Bit 27 - Invalid fmo parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_FMOCodingParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_VUICODINGPARAMS = 28,
          /**< Bit 28 - Invalid vui coding parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_VUICodingParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_H264ENCPARAMS = 29,
          /**< Bit 29 - Invalid Create time extended parameters 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_Params is not in allowed range
          */

  IH264ENC_UNSUPPORTED_VIDENC2DYNAMICPARAMS = 30,
          /**< Bit 30 - Invalid base class dyanmic paaremeters during control 
          *   @remarks  This error is set when any parameter of struct 
          *   IVIDENC2_DynamicParams is not in allowed range
          */

  IH264ENC_UNSUPPORTED_H264ENCDYNAMICPARAMS = 31
          /**< Bit 31 - Invalid exteded class dyanmic paaremeters during control 
          *   @remarks  This error is set when any parameter of struct 
          *   IH264ENC_DynamicParams (excluding embedded structures) is not in 
          *    allowed range
          */

} IH264ENC_ErrorBit ;

/**
 *  @enum       IH264ENC_ExtErrBits
 *  @brief      Sub extended error informations of IVAHD H264 encoder  
 *              implementation by TI.
 *
 *  @remarks    When an internal error occurs, the algorithm will return
 *              an error return value (e.g. EFAIL, EUNSUPPORTED). Apart from 
 *              this information, encoder returns extended error codes which 
 *              helps to get  refined error. For eg Error 
 *              IH264ENC_UNSUPPORTED_VIDENC2DYNAMICPARAMS can be returned by  
 *              many sub conditions which is not enough for the user
 *              to trace his parameter settings. But the sub extended error
 *              codecs as mentioned in the below enum gives finer and refined
 *              error information.These error bits are unique for each fail in
 *              param settings. The algorithm can set multiple bits based on 
 *              conditions.e.g. it will set bits #
 *              IH264ENC_EXTERROR_CREATE_INTERLACE_TYPE (for  wrong interlace 
 *              coding type) and #IH264ENC_EXTERROR_CREATE_LTRP (for wrong 
 *              LTRP settings) & etc.
 *              These bits are set in structure IH264ENC_Status::extErrorCode[] 
 *              and/or  structure IH264ENC_OutArgs::extErrorCode[]
 */
typedef enum {
  IH264ENC_EXTERROR_ACTIVEREGION                            = 0 ,
  /** Bit 0 – Active frame region dimensions are not matching with the 
   *  encoding frame dimensions 
   */     
  IH264ENC_EXTERROR_ANALYTICINFO_BUFFERSIZE                 = 1 ,
  /** Bit 1 – Analytic Info buffer size provided is less than that of 
   *  requested
   */     
  IH264ENC_EXTERROR_BITRATE                                 = 2 ,
  /* Bit 2 – target bit rate set is more than max bit rate  */     
  IH264ENC_EXTERROR_BITSTREAM_BUFFERSIZE                    = 3 ,
  /** Bit 3 – Output bitstream buffer size provided is less than that of 
   *  requested. And this validation is done only if 
   *  IVIDENC2_DynamicParams::ignoreOutbufSizeFlag is 0. Application has a 
   *  flexibility of the not honoring this size by setting ignoreOutbufSizeFlag
   *  to 1  
   */     
  IH264ENC_EXTERROR_CAPTUREWIDTH_FORCEFRAME_LTRP_QPEL       = 4 ,
  /** Bit 4 – This bit is set if any of the below conditions is set
   *  a. The size of dynamic params structure set is not of base class and
   *     nor even extended class
   *  b. Encoding dimensions are out of range
   *  c. Target bit rate less than minimum bt rate or frame rate is less than 0
   *  d. Generate header mode other than XDM_ENCODE_AU and XDM_GENERATE_HEADER
   *  e. User forced frame other than IDR/NA frame
   *  f. Wrong settings in interframe or intraFrame intervals
   *  g. Incorrect settings in motion vector accuracy settings
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_RESOLUTION_BITRATE_
   *  FRMINTERVAL_GENHEADER is also set  
   */     
  IH264ENC_EXTERROR_CONTROLCALL_CMD                         = 5 ,
  /** Bit 5 – Encoder control call is made with an incorrect command option  
   */     
  IH264ENC_EXTERROR_CREATE_ENTROPY_PROFILE                  = 6 ,
  /** Bit 6 – Entropy coding mode set is CABAC for Base line profile which is
   *  not supported  
   */     
  IH264ENC_EXTERROR_CREATE_GOPSTRUCT_LOG2MAX_INTRAINTERVAL  = 7 ,
  /** Bit 7 – This bit is set when
   * a. Parameters transformBlockSize, entropyCodingMode, log2MaxFNumMinus4,
   *    maxIntraFrameInterval, IDRFrameInterval, gopStructure are out of range.
   * b. LTRP is enabled for interlaced coding type
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_CREATE_TXBLKSIZE_
   *  ENTROPY_POC_LTRP is also set  
   */     
  IH264ENC_EXTERROR_CREATE_HPLAYERS                         = 8 ,
  /** Bit 8 – Hierarchal layers set is out of range i.e., numTemporalLayer 
   *  set is less tha 0 or more than 4  
   */     
  IH264ENC_EXTERROR_CREATE_HPLAYERS_BFRAME                  = 9 ,
  /** Bit 9 – Hierarchal coding is enabled for 'B’ Frames which is not supported
   */     
  IH264ENC_EXTERROR_CREATE_HPLAYERS_POC                     = 10 ,
  /** Bit 10 – Picture Order Count(POC) type 1 is enabled for Hierarchal layer 
   *  coding which is not supported  
   */     
  IH264ENC_EXTERROR_CREATE_HPLAYERS_REFPICMRKING            = 11 ,
  /** Bit 11 - Longterm Referencing (MMCO commands) is not enabled for 
   *  Hierarchal layer coding i.e., referencePicMarking is other than 
   *  IH264_LONG_TERM_PICTURE for Hierarchal layer coding which is 
   *  not supported  
   */     
  IH264ENC_EXTERROR_CREATE_INTERLACE_TYPE                   = 12 ,
  /** Bit 12 – In interlaced encoding, interlace coding type set is out
   *  of supported values  
   */     
  IH264ENC_EXTERROR_CREATE_LTRP                             = 13 ,
  /** Bit 13 – LTRP option (enableLongTermRefFrame) set is out of allowed ranges
   */     
  IH264ENC_EXTERROR_CREATE_LTRP_HP                          = 14 ,
  /** Bit 14 – LTRP option IH264ENC_LTRP_REFERTOP_PROACTIVE is enabled for
   *  Hierarchal layer coding which is not supported  
   */     
  IH264ENC_EXTERROR_CREATE_LTRP_PERIOD                      = 15 ,
  /** Bit 15 - When LTRP is enabled for Hierarchal layer coding (H-P) then 
   *  LTRPPeriod set should be multiple of subGop length  
   */     
  IH264ENC_EXTERROR_CREATE_LVL_DPBSIZE                      = 16 ,
  /** Bit 16 – Current DPB size set is more than the max DPB size allowed 
   *  in this level. Current DPB size is calculated using formaula 
   *  (maxWidth * maxHeight * 1.5 * max_num_ref_frames)  
   */     
  IH264ENC_EXTERROR_CREATE_POC_BFRAME                       = 17 ,
  /** Bit 17 – Picture Order Count(POC) type 2 is set for ‘B’ frames which
   * is not supported  
   */     
  IH264ENC_EXTERROR_CREATE_RCDO_PROFILE                     = 18 ,
  /** Bit 18 – RCDO is allowed only for Baseline profile. 
   */     
  IH264ENC_EXTERROR_CREATE_TXBLKSIZE_ENTROPY_POC_LTRP       = 19 ,
  /** Bit 19 – This bit is set when
   * a. Parameters transformBlockSize, entropyCodingMode, log2MaxFNumMinus4,
   *    maxIntraFrameInterval, IDRFrameInterval, gopStructure are out of range.
   * b. LTRP is enabled for interlaced coding type
   * If this bit is set, correspondingly IH264ENC_EXTERROR_CREATE_GOPSTRUCT
   * _LOG2MAX_INTRAINTERVAL is also set  
   */     
  IH264ENC_EXTERROR_CREATE_TXBLKSIZE_PROFILE                = 20 ,
  /** Bit 20 – Transform Block size IH264_TRANSFORM_8x8 is allowed only in
   *  High profile.
   */     
  IH264ENC_EXTERROR_DATASYNC_GETFN_PTRNULL                  = 21 ,
  /** Bit 21 – getBufferFxn is a function pointer used to get buffer. This 
   *  function gets called in Data synch flow. This error bit is set if 
   *  this function pointer is NULL  
   */     
  IH264ENC_EXTERROR_DATASYNC_MBUNIT_SLICESIZE               = 22 ,
  /** Bit 22 – This bit is set if
   *  a. User has enabled call back notification at slice level and
   *  b. Encoder slice mode selected is IH264_SLICEMODE_MBUNIT and
   *  c. Slice Unit size(number of MBs per slice) set is less than 
   *     minimum MBs per slices. Minimum MBs per slice is (TotalMbsInPic/63)
   */     
  IH264ENC_EXTERROR_DATASYNC_MODE_BFRAME                    = 23 ,
  /** Bit 23 – Data sync, inputDataMode is not set to IVIDEO_ENTIREFRAME in 
   *  presence of ‘B’ frames. In ‘B’ cases we allow processing entire frames
   *  and not any mode  
   */     
  IH264ENC_EXTERROR_DATASYNC_MODE_FNPTRNULL                 = 24 ,
  /** Bit 24 – This bit is set if
   *  a. Data sync, outputDataMode is IVIDEO_FIXEDLENGTH or IVIDEO_SLICEMODE
   *     and putDataFxn is NULL
   *  OR
   *  b. Data sync, inputDataMode is IVIDEO_NUMROWS and getDataFxn is NULL  
   */     
  IH264ENC_EXTERROR_DATASYNC_MODE_H241_FNPTRNULL            = 25 ,
  /** Bit 25 – In H241 flow, if user is interested in call back notification
   *  at slice level then he has to provide function address in getBufferFxn
   *  function pointer else this bit is set  
   */     
  IH264ENC_EXTERROR_DATASYNC_MODE_MINBITRATE                = 26 ,
  /** Bit 26 – minBitRate should be 0 if data sync, outputDataMode is 
   *  VIDEO_FIXEDLENGTH or IVIDEO_SLICEMODE  
   */     
  IH264ENC_EXTERROR_DATASYNC_OUTPUTDATAEXCEED               = 27 ,
  /** Bit 27 – Encoded output data size has exceeded the available buffer 
   *  size  
   */     
  IH264ENC_EXTERROR_DATASYNC_UNITS                          = 28 ,
  /** Bit 28 – Data sync, numOutputDataUnits are out of allowed ranges in
   *  case of outputDataMode not equal to IVIDEO_ENTIREFRAME  
   */     
  IH264ENC_EXTERROR_DYNAMIC_SRCHCENTRE                      = 29 ,
  /** Bit 29 – GMV, search centre x/y are out of allowed range  
   */     
  IH264ENC_EXTERROR_DYNAMICPARAMS_PTRNULL                   = 30 ,
  /** Bit 30 – In encoder control call with command option XDM_SETPARAMS,
   *  IVIDENC2_DynamicParams structure pointer is NULL  
   */     
  IH264ENC_EXTERROR_EARLYEXIT                               = 31 ,
  /** Bit 31 – Early exit called because Frame processing is not completed
   *  at IVAHD side  
   */     
  IH264ENC_EXTERROR_FIFO_EMPTY_NOPROCESS                    = 32 ,
  /** Bit 32 – In Flush process calls, no more buffers are locked and 
   *  hence process call cannot be made further this point  
   */     
  IH264ENC_EXTERROR_FILLERBYTES_NEGATIVE                    = 33 ,
  /** Bit 33 – This bit set indicates that the filler bytes size to be put 
   *  in bitstream to meet bit stream constraint is negative. Filler data 
   *  negative indiactes that bits consumed in current unit till now has 
   *  crossed the maximum limit.So inform to the user by seeting appropirate bit  
   */     
  IH264ENC_EXTERROR_FMO_PRESET                              = 34 ,
  /** Bit 34 – FMO coding preset is other than default. 
   *  FMO is not supported in this release
   */     
  IH264ENC_EXTERROR_FRMPACKING_PRESET                       = 35 ,
  /** Bit 35 – Frame packing preset is not in allowed range  
   */     
  IH264ENC_EXTERROR_FRMPACKING_TYPE_INPCONTENT              = 36 ,
  /** Bit 36 – This bit is set if
   *  a.Frame packing is enabled for interlaced cases
   *  b.Frame packing preset is user defined and frame packing type is more
   *    than 4 (IH264_FRAMEPACK_TOP_BOTTOM)  
   */     
  IH264ENC_EXTERROR_FRMRATE_NUMUNITSINTICKS                 = 37 ,
  /** Bit 37 – Level incompliant MBs per second
   */     
  IH264ENC_EXTERROR_GENHEADER_BITSTREAM_BUFFERSIZE          = 38 ,
  /** Bit 38 – In process call with XDM_GENERATE_HEADER mode, output 
   *  buffer size provided should be minimum of 0x100 bytes 
   *  (to hold SPS and PPS)
   */     
  IH264ENC_EXTERROR_HANDLE_BUFDESCRIPTORS_PTRNULL           = 39 ,
  /** Bit 39 – Pointer of handle or inBufs or outBufs structure may be NULL
   */     
  IH264ENC_EXTERROR_HIGHSPEED_BFARME                        = 40 ,
  /** Bit 40 – High speed encoding feature is not supported for ‘B’ frames.
   */     
  IH264ENC_EXTERROR_HIGHSPEED_MEALGO_TXBLKSIZE_PROFILE      = 41 ,
  /** Bit 41 – This bit is set if, in High speed encoding mode
   *  a. Transform block size is 4x4 for High profile case
   *  OR
   *  b. Transform block size is 8x8 and non High profile cases
   */     
  IH264ENC_EXTERROR_HIGHSPEED_PARTIALSKIP_INTRAREFRESHMETHOD= 42 ,
  /** Bit 42 – This bit is set if, in High speed encoding mode
   *  a. Transform block size is 4x4 for High profile case
   *  OR
   *  b. Transform block size is 8x8 and non High profile cases
   *  OR
   *  c. Partial Frame skip is enabled
   *  OR
   *  d. Intra refresh method is other than default
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_HIGHSPEED_
   *  TXBLKSIZE_PROFILE is also set
   */     
  IH264ENC_EXTERROR_HIGHSPEED_TXBLKSIZE_PROFILE             = 43 ,
  /** Bit 43 – This bit is set if, in High speed encoding mode
   *  a. Transform block size is 4x4 for High profile case
   *  OR
   *  b. Transform block size is 8x8 and non High profile cases
   *  OR
   *  c. Partial Frame skip is enabled
   *  OR
   *  d. Intra refresh method is other than default
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_HIGHSPEED_
   *  PARTIALSKIP_INTRAREFRESHMETHOD is also set  
   */     
  IH264ENC_EXTERROR_INARGS_BASECLASS_WATERMARKENABLE        = 44 ,
  /** Bit 44 – Water Marking feature of the encoder is enabled and inArgs
   *  structure is base class. If inArgs structure is base class we cannot
   *  access the input key that has to used in water marking algo. 
   *  So please use extended class of inArgs and pass the input key  
   */     
  IH264ENC_EXTERROR_INARGS_CONTROL                          = 45 ,
  /** Bit 45 – The control parameter passed as part of inArgs structure is
   *  out of allowed range  
   */     
  IH264ENC_EXTERROR_INARGS_OUTARGS_SIZE                     = 46 ,
  /** Bit 46 – The size parameter as part of inArgs or outArgs structure does
   *  not match base class not even extended class  
   */     
  IH264ENC_EXTERROR_INARGS_PTRNULL                          = 47 ,
  /** Bit 47 – inArgs structure pointer passed in the process call is NULL
   */     
  IH264ENC_EXTERROR_INPCONTENT_TYPE                         = 48 ,
  /** Bit 48 – Input data content type value is wrong or input data chroma
   *  format is not YUV420
   */     
  IH264ENC_EXTERROR_INPUT_BUFFERID                          = 49 ,
  /** Bit 49 – inputId as part of inArgs structure is 0
   */     
  IH264ENC_EXTERROR_INPUTBUF_MEMTYPE                        = 50 ,
  /** Bit 50 – memType value set in the plane descriptors of inBufs structure
   *  is falling out of allowed values
   */     
  IH264ENC_EXTERROR_INPUTBUF_PTR_SIZE_NULL                  = 51 ,
  /** Bit 51 - buf value(buffer pointer) or bufSize.bytes set in the plane
   *  descriptors of inBufs structure is NULL
   */     
  IH264ENC_EXTERROR_INTER_HIGHSPEED_MVPERMB                 = 52 ,
  /** Bit 52 – This bit is set if, in High speed encoding mode
   *  a. ‘B’ frames are enabled
   *  OR
   *  b. Motion vector accuracy is not a Quarter pel (mvAccuracy != 
   *     IVIDENC2_MOTIONVECTOR_QUARTERPEL)
   *  OR
   *  c. Motion vectors per macroblock is not 1 
   *     (minBlockSizeP != IH264_BLOCKSIZE_16x16)
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_INTER_HIGHSPEED
   *  _QPEL_FRAMEINTERVAL is also set
   */     
  IH264ENC_EXTERROR_INTER_HIGHSPEED_QPEL_FRAMEINTERVAL      = 53 ,
  /** Bit 53 – This bit is set if, in High speed encoding mode
   *  a. ‘B’ frames are enabled
   *  OR
   *  b. Motion vector accuracy is not a Quarter pel (mvAccuracy != 
   *     IVIDENC2_MOTIONVECTOR_QUARTERPEL)
   *  OR
   *  c. Motion vectors per macroblock is not 1 
   *     (minBlockSizeP != IH264_BLOCKSIZE_16x16)
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_INTER_HIGHSPEED
   *  _MVPERMB is also set
   */     
  IH264ENC_EXTERROR_INTER_MVPERMB                           = 54 ,
  /** Bit 54 – Motion vectors per MB set is not in allowed range. 
   *  minBlockSizeP/B is not equal to IH264_BLOCKSIZE_16x16 and not even 
   *  IH264_BLOCKSIZE_8x8
   */     
  IH264ENC_EXTERROR_INTER_PRESET                            = 55 ,
  /** Bit 55 – interCoding preset value is out of allowed range
   */     
  IH264ENC_EXTERROR_INTER_SRCHRGN_SKIPMVBIAS                = 56 ,
  /** Bit 56 – searchRangeHorP/B or searchRangeVerP/B or skipMVCodingBias 
   *  values are out of allowed range
   */     
  IH264ENC_EXTERROR_INTERLACE_DATALAYOUT                    = 57 ,
  /** Bit 57 – In interlaced encoding cases, dataLayout value set as part
   *  of inBufs structure is not IVIDEO_FIELD_INTERLEAVED and not even 
   *  IVIDEO_FIELD_SEPARATED
   */     
  IH264ENC_EXTERROR_INTRA_CBCR8X8                           = 58 ,
  /** Bit 58 – This bit is set if,
   *  a. intraCodingPreset is not a default
   *  AND
   *  b. chromaIntra8x8Enable is enabled
   *  AND
   *  c. chromaComponentEnable value is falling out of allowed range
   *  Please refer IH264ENC_ChormaComponent for more details
   */     
  IH264ENC_EXTERROR_INTRA_GDR_BFRAME_INPCONTENT_RATE        = 59 ,
  /** Bit 59 – This bit is set if, in GDR enabled cases
   *  a. Interlaced encoding is enabled
   *  b. ‘B’ frames are enabled
   *  c. GDR overlap rows is less than 0 or more than intraRefresh rate
   */     
  IH264ENC_EXTERROR_INTRA_GDR_REFRESHRATE                   = 60 ,
  /** Bit 60 – gdrOverlapRowsBtwFrames is more than intraRefreshRate
   */     
  IH264ENC_EXTERROR_INTRA_INTER_FRMINTERVAL                 = 61 ,
  /** Bit 61 – intraFrame interval is not a multiple of interFrame interval
   */     
  IH264ENC_EXTERROR_INTRA_LEVEL_MODE                        = 62 ,
  /** Bit 62 - lumaIntra8x8Enable is enabled for profile other than 
   *  IH264_HIGH_PROFILE
   */     
  IH264ENC_EXTERROR_INTRA_PRESET                            = 63 ,
  /** Bit 63 – intraCoding preset is out of allowed range
   */     
  IH264ENC_EXTERROR_INTRA_REFRESHMETHOD                     = 64 ,
  /** Bit 64 – intraRefreshMethod value is out of allowed range
   */     
  IH264ENC_EXTERROR_INTRA_REFRESHMETHOD_RATE                = 65 ,
  /** Bit 65 – intraRefreshRate is less than or equal to 0 for 
   *  intraRefreshMethod value other than default
   */     
  IH264ENC_EXTERROR_INTRA_REFRESHRATE                       = 66 ,
  /** Bit 66 - intraRefreshRate is less than 0 for GDR enabled cases
   */     
  IH264ENC_EXTERROR_IVAHD_BADRESET                          = 67 ,
  /** Bit 67 – HDVICP reset is not proper
   */     
  IH264ENC_EXTERROR_IVAHD_BADSTATE                          = 68 ,
  /** Bit 68 – HDVICP is not in standby state
   */     
  IH264ENC_EXTERROR_IVAHD_RELEASE                           = 69 ,
  /** Bit 69 – HDVICP release fail. This occurs if HDVICP is not in 
   *  standby state during release time
   */     
  IH264ENC_EXTERROR_LEVEL_INPCONTENT                        = 70 ,
  /** Bit 70 – level less than or equal to IH264_LEVEL_20 for interlaced 
   *  encoding
   */     
  IH264ENC_EXTERROR_LEVELLIMIT_RESOLUTION                   = 71 ,
  /** Bit 71 – encoding resolutions/frame_dimensions are more than that 
   *  of level allowed range
   */     
  IH264ENC_EXTERROR_LOOPFILTER_OFFST_LFIDC                  = 72 ,
  /** Bit 72 – loop filter preset is not a default and loopfilterDisableIDC, 
   *  filterOffsetA/B is/are out of allowed range or filterOffsetA/B is odd 
   *  value
   */     
  IH264ENC_EXTERROR_LOOPFILTER_PRESET                       = 73 ,
  /* Bit 73 – loop filter preset is out of allowed range
  */     
  IH264ENC_EXTERROR_LUMA_INPUTBUF_MEMTYPE                   = 74 ,
  /** Bit 74 – memType value set in the plane descriptors of inBufs 
   *  structure corresponding to Luma data is XDM_MEMTYPE_TILED32 or 
   *  XDM_MEMTYPE_TILED16. Allowed value is only XDM_MEMTYPE_TILED8 for 
   *  Luma container
   */     
  IH264ENC_EXTERROR_METADATA_NUMBUFFERS                     = 75 ,
  /** Bit 75 – Number of meta data planes (corresponding to 
   *  IH264_USER_DEFINED_SCALINGMATRIX and IH264_SEI_USER_DATA_UNREGISTERED)
   *  provided is not equal to inBufs->numMetaPlanes
   */     
  IH264ENC_EXTERROR_METADATABUF_MEMTYPE                     = 76 ,
  /** Bit 76 - memType value set in the meta data plane descriptors of 
   *  inBufs structure is not equal to XDM_MEMTYPE_ROW or XDM_MEMTYPE_TILEDPAGE
   */     
  IH264ENC_EXTERROR_METADATAPLANE_WGTTABLESIZE              = 77 ,
  /** Bit 77 – In case of user defined scaling matrix, payload_size
   *  (bufSize.bytes) provided as part of meta data plane descriptors of inBufs
   *  structure is less the size of weightTable 
   *  (inBufs->metadataPlaneDesc[index].bufSize.bytes) < 
   *                                                 (sizeof(sH264WgtTables_t))
   */     
  IH264ENC_EXTERROR_METADATATYPES                           = 78 ,
  /** Bit 78 – metadataType[] are other than the supported values
   */     
  IH264ENC_EXTERROR_MULITCHNL_BFRAME_NOTSUPPORTED           = 79 ,
  /** Bit 79 – This bit is set if ‘B’ frames are enabled in multi Frame
   *  process call
   */     
  IH264ENC_EXTERROR_MULITCHNL_CHNLNUMEXCEEDED               = 80 ,
  /** Bit 80 – This bit is set if number of channels to be processed are 
   *  more that of maximum supported in multi Frame process call
   */     
  IH264ENC_EXTERROR_MULITCHNL_DATASYNC                      = 81 ,
  /** Bit 81 – This bit is set if data sync is enabled in multi Frame process
   *  call
   */     
  IH264ENC_EXTERROR_MULITCHNL_FRMPCK_STEREOIINFO            = 82 ,
  /** Bit 82 - This bit is set if framePackingPreset or stereoInfoPreset is 
   *  enabled in multi Frame process call
   */     
  IH264ENC_EXTERROR_MULITCHNL_GENHEADER_NOTSUPPORTED        = 83 ,
  /** Bit 83 - This bit is set if frame process mode is XDM_GENERATE_HEADER
   *  in multi Frame process call
   */     
  IH264ENC_EXTERROR_MULITCHNL_MINBITRATE_NOTSUPPORTED       = 84 ,
  /** Bit 84 - This bit is set if minBitRate value is more than 0 in multi 
   *  Frame process call
   */     
  IH264ENC_EXTERROR_MULITCHNL_MVPERMB                       = 85 ,
  /** Bit 85 – This bit is set if motion vectors per MB (minBlockSizeP) 
   *  is not same for all the channels submitted in multi Frame process call
   */     
  IH264ENC_EXTERROR_NALU_GOLDENSPS                          = 86 ,
  /** Bit 86 – In all NALU preset masks, SPS_WITH_VUI bit is to be set or
   *  has to be reset. Setting of this bit in few masks and resetting in others
   *  is not allowed
   */     
  IH264ENC_EXTERROR_NALU_PRESET                             = 87 ,
  /** Bit 87 – NALU control preset is out of allowed range
   */     
  IH264ENC_EXTERROR_NALU_SPS_VUI                            = 88 ,
  /** Bit 88 – SEI NALU bit is set in a mask and SPS_WITH_VUI is not 
   *  set in that particular mask
   */     
  IH264ENC_EXTERROR_NOCLEANEXIT                             = 89 ,
  /** Bit 89 – Early return because M3 has done early abort
   */     
  IH264ENC_EXTERROR_NUM_INPUT_OUTPUT_BUFS                   = 90 ,
  /** Bit 90 – There has to atleast 2 input buffers (inBufs->numPlanes :
   *  1 Luma and 1 CbCr) and 1 output buffer (outBufs->numBufs : bit stream).
   *  This bit is set if this condition is not satisfied
   */     
  IH264ENC_EXTERROR_OUTPUTBUF_MEMTYPE                       = 91 ,
  /** Bit 91 – This bit is set if
   *  a. output bitstream buffer’s memory type is not XDM_MEMTYPE_ROW or 
   *     not XDM_MEMTYPE_TILEDPAGE
   *  OR
   *  b. output buffer’s memory type is out of allowed range
   */     
  IH264ENC_EXTERROR_OUTPUTBUF_PTR_SIZE_NULL                 = 92 ,
  /** Bit 92 – This bit is set if output data sync is not enabled and 
   *  bitstream buffer pointer is NULL or buffer.bytes is 0
   */     
  IH264ENC_EXTERROR_OUTPUTDATASIZE_EXCEEDED                 = 93 ,
  /** Bit 93 - Encoded output data size has exceeded the available buffer size
   */     
  IH264ENC_EXTERROR_PRESET_ENC_RATECTRL_LVL                 = 94 ,
  /** Bit 94 – This bit is set if
   *  a. encodingPreset is out of allowed range
   *  b. rateControlPreset is out of allowed range
   *  c. profile and level out of allowed range
   *  d. data sync mode out of allowed range
   *  e. inputChromaFormat, inputContentType,operatingMode, 
   *     maxInterFrameInterval, maxHeight, maxWidth and dataEndianness are
   *     out of allowed range
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_PROFILE_DATASYNC
   *  _INPCONTENT_RES is also set
   */     
  IH264ENC_EXTERROR_PROFILE_BFRAME                          = 95 ,
  /** Bit 95 – ‘B’ frames are enabled for baseline profile
   */     
  IH264ENC_EXTERROR_PROFILE_DATASYNC_INPCONTENT_RES         = 96 ,
  /** Bit 96 – This bit is set if
   *  a. encodingPreset is out of allowed range
   *  b. rateControlPreset is out of allowed range
   *  c. profile and level out of allowed range
   *  d. data sync mode out of allowed range
   *  e. inputChromaFormat, inputContentType,operatingMode, 
   *     maxInterFrameInterval, maxHeight, maxWidth and dataEndianness are
   *     out of allowed range
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_PRESET_ENC_RATECTRL
   *  _LVL is also set
   */     
  IH264ENC_EXTERROR_PROFILE_INPCONTENT                      = 97 ,
  /** Bit 97 – interlaced encoding is enabled for baseline profile
   */     
  IH264ENC_EXTERROR_RATECTRL_BFRAMEPICSIZE                  = 98 ,
  /** Bit 98 – rate control, minPicSizeRatioB value is out of allowed range
   */     
  IH264ENC_EXTERROR_RATECTRL_CBCRQPINDEX_INITBUFLVL         = 99 ,
  /** Bit 99 – rate control,chromaQPIndexOffset initialBufferLevel are out
   *  of allowed range
   */     
  IH264ENC_EXTERROR_RATECTRL_HRDBUFFER_LVLEXCEED            = 100 ,
  /** Bit 100 – rate control, HRDBufferSize is falling out of level decided 
   *  minimum and maximum limit
   */     
  IH264ENC_EXTERROR_RATECTRL_IFRAME_QP                      = 101 ,
  /** Bit 101 – rate control, qpI is not falling in the range [qpMinI, qpMaxI]
   */     
  IH264ENC_EXTERROR_RATECTRL_IFRAMEPICSIZE                  = 102 ,
  /** Bit 102 – rate control, minPicSizeRatioI value is out of allowed range
   */     
  IH264ENC_EXTERROR_RATECTRL_IPBFRAME_QP                    = 103 ,
  /** Bit 103 – rate control, Qp values set for ‘I’, ‘P’ and ‘B’ frames are
   *  falling out allowed values
   */     
  IH264ENC_EXTERROR_SCLMATRIX_METADATA                      = 104 ,
  /** Bit 104 – Scaling matrix preset is user defined 
   *  (IH264_SCALINGMATRIX_USERDEFINED_SPSLEVEL or IH264_SCALINGMATRIX_
   *  USERDEFINED_PPSLEVEL) and meta data is not enabled for user defined
   *  scaling matrix  
   */     
  IH264ENC_EXTERROR_RATECTRL_PARAMSPRESET                   = 105 ,
  /** Bit 105 – rate control, rateControlParamsPreset is out of allowed range
   */     
  IH264ENC_EXTERROR_RATECTRL_PBFRAME_QP                     = 106 ,
  /** Bit 106 – rate control, Qp values for ‘P’ or ‘B’ frames are out of 
   *  range[minQp, maxQp]
   */     
  IH264ENC_EXTERROR_RATECTRL_PFRAMEPICSIZE                  = 107 ,
  /** Bit 107 – rate control, minPicSizeRatioP value is out of allowed range
   */     
  IH264ENC_EXTERROR_RATECTRL_PRESET_BFRAME_INPCONTENT       = 108 ,
  /** Bit 108 - IVIDEO_LOW_DELAY rateControlPreset is not supported for 
   *  interlaced encoding and for ‘B’ frame cases
   */     
  IH264ENC_EXTERROR_RATECTRL_PROFILE_SCALINGMTRX            = 109 ,
  /** Bit 109 – scaling matrix preset is out of range or scaling matrix preset
   *  is other than user defined for profile not equal to IH264_HIGH_PROFILE
   */     
  IH264ENC_EXTERROR_RATECTRL_RCALGO                         = 110 ,
  /** Bit 110 – rate control, rcAlgo is out of allowed range
   */     
  IH264ENC_EXTERROR_RATECTRL_RCALGO_INTERLACE_OR_BFRAME     = 111 ,
  /** Bit 111 - RATECONTROL_PRC_LOW_DELAY rcAlgo is not supported for 
   *  interlaced encoding and for ‘B’ frame cases
   */     
  IH264ENC_EXTERROR_RATECTRL_SKIPDISTWNDW                   = 112 ,
  /** Bit 112 – This bit is set if
   *  a. rcAlgo is RATECONTROL_PRC_LOW_DELAY
   *  AND
   *  b. skip distribution window length (skipDistributionWindowLength) or
   *     number of skip frames in distribution window specified are out of
   *     allowed range
   */     
  IH264ENC_EXTERROR_RATECTRL_VBR                            = 113 ,
  /** Bit 113 – rate control, with CVBR settings, VBR duration (VBRDuration)
   *  or VBR sensitivity (VBRsensitivity) are out of allowed range
   */     
  IH264ENC_EXTERROR_RESOLUTION_BITRATE_FRMINTERVAL_GENHEADER= 114 ,
  /** Bit 114 – This bit is set if any of the below conditions is set
   *  a. The size of dynamic params structure set is not of base class and
   *     nor even extended class
   *  b. Encoding dimensions are out of range
   *  c. Target bit rate less than minimum bt rate or frame rate is less than 0
   *  d. Generate header mode other than XDM_ENCODE_AU and XDM_GENERATE_HEADER
   *  e. User forced frame other than IDR/NA frame
   *  f. Wrong settings in interframe or intraFrame intervals
   *  g. Incorrect settings in motion vector accuracy settings
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_CAPTUREWIDTH_
   *  FORCEFRAME_LTRP_QPEL is also set
   */     
  IH264ENC_EXTERROR_ROI_COORDINATES                         = 115 ,
  /** Bit 115 – ROI co-ordinates provided are not proper. x/y may be less 
   *  than 0 or more than frame dimensions. Also please see that Top.x 
   *  should be less than Bottom.x and Top.y should be less than bottom.y
   *  for all co-ordinates
   */     
  IH264ENC_EXTERROR_ROI_NUMBERROIS                          = 116 ,
  /** Bit 116 – Number of ROI regions set are out of allowed range
   */     
  IH264ENC_EXTERROR_ROI_PRIORITY                            = 117 ,
  /** Bit 117 – ROI priority (roiPriority) provided are out of allowed range.
   *  This check is done with rate control enabled cases
   */     
  IH264ENC_EXTERROR_ROI_QP                                  = 118 ,
  /** Bit 118 - ROI priority (roiPriority) provided are out of allowed range.
   *  This check is done with rate control disabled cases. 
   *  Here roiPriority holds the Qp values of the ROI regions
   */     
  IH264ENC_EXTERROR_ROI_TYPE                                = 119 ,
  /** Bit 119 – ROI types (roiType) provided are out of allowed range
   */     
  IH264ENC_EXTERROR_SLICE_NONE_DATASYNC                     = 120 ,
  /** Bit 120 – data sync call back notification is enabled for every 
   *  slice (outputDataMode == IVIDEO_SLICEMODE)and slice level encoding
   *  is disabled (sliceMode == IH264_SLICEMODE_NONE)
   */     
  IH264ENC_EXTERROR_SLICE_H241_ENTROPY_INTERFRAME_INTERLACE = 121 ,
  /** Bit 121 – This bit is set if H241 is enabled and
   *  a. Width provided is less than that being supported in H241 cases
   *  OR
   *  b. Interlaced encoding is enabled
   *  OR
   *  c. Entropy coding mode is CABAC
   *  OR
   *  d. ‘B’ frames are enabled
   *  OR
   *  e. Slice unit size in bytes (sliceUnitSize) provided is loess that being
   *     supported
   *  If this bit is set, correspondingly IH264ENC_EXTERROR_SLICE_H241_
   *  WIDTH_SLICESIZE is also set
   */     
  IH264ENC_EXTERROR_SLICE_STRMFORMAT_DATASYNC               = 122 ,
  /** Bit 122 – stream format IH264_NALU_STREAM is supported only with default
   *  slice mode and datasync option as IVIDEO_SLICEMODE
   */     
  IH264ENC_EXTERROR_SLICE_H241_WIDTH_SLICESIZE              = 123 ,
  /** Bit 123 – This bit is set if H241 is enabled and
   *  a. Width provided is less than that being supported in H241 cases
   *  OR
   *  b. Interlaced encoding is enabled
   *  OR
   *  c. Entropy coding mode is CABAC
   *  OR
   *  d. ‘B’ frames are enabled
   *  OR
   *  e. Slice unit size in bytes (sliceUnitSize) provided is loess that being
   *     supported
   */     
  IH264ENC_EXTERROR_SLICE_MODE_SIZE                         = 124 ,
  /** Bit 124 – This bit is set if
   *  a. Slice mode is SLICEMODE_MBUNIT and slice size provided is more than 
   *     size of the frame or slice size is less than 6
   *  OR
   *  b. Slice mode is SLICEMODE_OFFSET and sliceOffset0 is more than 
   *     sliceOffset1 or sliceOffset1 is more than sliceoffset2
   */     
  IH264ENC_EXTERROR_SLICE_PRESET                            = 125 ,
  /** Bit 125 – slice coding preset is out of allowed range
   */     
  IH264ENC_EXTERROR_SLICE_STRMFORMAT                        = 126 ,
  /** Bit 126 – stream format provided is out of allowed range
   */     
  IH264ENC_EXTERROR_STATUS_PTRNULL                          = 127 ,
  /** Bit 127 – status structure pointer passed in the encoder control call is
   *  NULL
   */     
  IH264ENC_EXTERROR_STATUS_SIZE                             = 128 ,
  /** Bit 128 - The size of status params structure set is not of base class 
   *  and nor even extended class
   */     
  IH264ENC_EXTERROR_STEREO_INPCONTENT                       = 129 ,
  /** Bit 129 – stereo info preset is enabled for progressive encoding which
   *  is not supported in this version of encoder
   */     
  IH264ENC_EXTERROR_STEREO_PRESET                           = 130 ,
  /** Bit 130 – stereo info preset set is out of allowed range
   */     
  IH264ENC_EXTERROR_VERSION_BUFFER_NULL_OR_SIZE             = 131 ,
  /** Bit 131 – data buffer pointer as part of status structure is NULL. 
   *  This buffer is used to place the version number of encoder. 
   *  OR 
   *  The data size as part of status structure is less than the size
   *  required to place an version number
   */  
  IH264ENC_EXTERROR_VUI_NUMUNITSINTICKS                     = 132 ,
  /** Bit 132 – VUI coding preset is user defined and the parameter 
   *  numUnitsInTicks as part of vuiCodingParams is less than 0
   */     
  IH264ENC_EXTERROR_VUI_PRESET                              = 133 ,
  /** Bit 133 – VUI coding preset set is out of allowed range
   */     
  IH264ENC_NUM_OUTPUT_BUFS_ANALYTICINFO                     = 134 ,
  /** Bit 134 – Analytic info is enabled and the buffer to store analytic
   *  info is not provided i.e., (outBufs->numBufs < 2 AND enableAnalyticinfo)
   */     
  IH264ENC_EXTERROR_NUM_MAXBITS ,
  /** Maximum number of sub extended error bits
   */     
  IH264ENC_EXTERROR_NUM_MAXWORDS = ((IH264ENC_EXTERROR_NUM_MAXBITS + 31) / 32)
  /** Each word can hold 32 error bits, so max words are calculated as above
   */     
}IH264ENC_ExtErrBits ;

/**
 *  @enum       IH264ENC_Level
 *  @brief      Level Identifier for H.264 Encoder
*/
typedef enum
{
  IH264_LEVEL_10 = 10,  /**<  Level 1.0  */
  IH264_LEVEL_1b =  9,  /**<  Level 1.b  */
  IH264_LEVEL_11 = 11,  /**<  Level 1.1  */
  IH264_LEVEL_12 = 12,  /**<  Level 1.2  */
  IH264_LEVEL_13 = 13,  /**<  Level 1.3  */
  IH264_LEVEL_20 = 20,  /**<  Level 2.0  */
  IH264_LEVEL_21 = 21,  /**<  Level 2.1  */
  IH264_LEVEL_22 = 22,  /**<  Level 2.2  */
  IH264_LEVEL_30 = 30,  /**<  Level 3.0  */
  IH264_LEVEL_31 = 31,  /**<  Level 3.1  */
  IH264_LEVEL_32 = 32,  /**<  Level 3.2  */
  IH264_LEVEL_40 = 40,  /**<  Level 4.0  */
  IH264_LEVEL_41 = 41,  /**<  Level 4.1  */
  IH264_LEVEL_42 = 42,  /**<  Level 4.2  */
  IH264_LEVEL_50 = 50,  /**<  Level 5.0  */
  IH264_LEVEL_51 = 51   /**<  Level 5.1  */

} IH264ENC_Level ;


/**
 *  @enum       IH264ENC_Profile
 *  @brief      Profile Identifier for H.264 Encoder
*/
typedef enum
{
  IH264_BASELINE_PROFILE = 66,                  /**< BaseLine Profile   */
  IH264_MAIN_PROFILE     = 77,                  /**< Main Profile       */
  IH264_EXTENDED_PROFILE = 88,                  /**< Extended Profile   */
  IH264_HIGH_PROFILE     = 100,                 /**< High Profile       */
  IH264_DEFAULT_PROFILE  = IH264_HIGH_PROFILE,  /**< Default Profile    */
  IH264_HIGH10_PROFILE   = 110,                 /**< High 10 Profile    */
  IH264_HIGH422_PROFILE  = 122,                 /**< High 4:2:2 Profile */
  IH264SVC_BASELINE_PROFILE = 83,               /**< SVC Baseline Profile */
  IH264SVC_HIGH_PROFILE     = 86                /**< SVC High Profile */
} IH264ENC_Profile ;

/**
 *  @enum       IH264ENC_MetadataType
 *  @brief      Meta Data for H.264 encoder
 
   The way to pass meta data to encode is via inBufs to the encoder during 
   process call. 
   The way to get meta data from encode is via outBufs of the encoder during 
   process call. 
 
   When application request the buffer infos via control call with 
   XDM_GETBUFINFO, encoder should count a buffer to have meta data at 
   input/output level for this purpose. If for some metadata size is not known 
   by encoder then it should return size =-1 so that application can 
   allocate as per its knowledge. Same way for some meta-data application 
   might not provide the size to codec via XDM2_SingleBufDesc.bufSize.bytes, 
   in that case application can set it to -1. The meta data which has size 
   field in its format, uses size of buffer from that field only.
   Example: User want to insert SEI_USER_DATA_UNREGISTERED meta data at each 
   IDR picture, the following steps should be followed
 
 1. Create the encoder object with IVIDENC2_Params::metadataType[0] = 
   IH264_SEI_USER_DATA_UNREGISTERED and metadataType[1] and metadataType[2]
   = IVIDEO_METADATAPLANE_NONE
   
    Also have IH264ENC_SET_NALU(naluPresentMaskIDRPicture, SEI)
 2. Call Control function with XDM_GETBUFINFO. Encoder should return one 
    additional input buffer as required. size of the buffer will be -1 as 
    encoder doesn't know the size
 3. Application should have a memory allocated for this meta data and pass on 
    to the encoder via IVIDEO2_BufDesc *inBufs->numMetaPlanes = 1        
                                                          +----------------+
    inBufs->metadataPlaneDesc[index].buf = pBuffer ; ---> | size | payLoad |
    inBufs->metadataPlaneDesc[index].bufSize.bytes = -1 ; +----------------+
    since the meta-data format includes size field, encoder will read size from 
    there and utilize it.

    index of metadataPlaneDesc is the index of metaDataType which is holding
    the particular meta data type. In this example metadataType[0] is holding
    IH264_SEI_USER_DATA_UNREGISTERED so index = 0 of metadataPlaneDesc points 
    to IH264_SEI_USER_DATA_UNREGISTERED specific meta data
*/

typedef enum {
  IH264_SEI_USER_DATA_UNREGISTERED = XDM_CUSTOMENUMBASE,
  /**< H.264 allows inserting SEI message for any user data. refer section 
  *    D.1.6 of H.264 standard.
  *    By setting this value to any if IVIDENC2_Params::metadataType[i] 
  *    user can provide its user data SEI to be inserted 
  *    in H.264 bit-stream
  *    The format of user data is as below
  *    typedef struct {
  *       U32 size;       only lower 10-bits are considered                
  *       U08 payload[];  number of bytes for payload is indicated by first 
  *                       32 bit field size                                
  *    }
  * The picture which uses this metadata will be decided by naluPresentMask::SEI
  * bit. Example
  * if SEI bit of only naluPresentMaskStartOfSequence is set to 1 then this meta 
  * data will be used  only during start of sequence
  * Encoder can accept maximum size of this meta data as 1023 bytes < 1K. 
  * Only lower 10-bits of size field is used by encoder
  */
  
  IH264_REGION_OF_INTEREST,
  /**< Not defined yet the format but this field is to control the encoder to 
  *  accept ROI data as input 
  */
  
  IH264_USER_DEFINED_SCALINGMATRIX
  /**< H.264 allows inserting user defined scaling matrices.
  *  By setting this value to any if IVIDENC2_Params::metadataType[i]
  *  user can provide its user data SEI to be inserted in H.264 bit-stream
  * The format of user data is as below
  * typedef struct {
  *   U32 size;        only lower 10-bits are considered                    
  *   U08 payload[];   number of bytes for payload is indicated by first    
  *                    32 bit field size                                    
  *  }
  * format of payload is for scaling matrix is defined in User GUide
  */
  } IH264ENC_MetadataType;

/**
 *  @enum       IH264ENC_Control
 *  @brief      Diffrent types of controls for encoding frame 
 *              Eg: refere long term reference frame
 */

typedef enum {
  IH264ENC_CTRL_REFER_LONG_TERM_FRAME = XDM_CUSTOMENUMBASE,
          /**< Refere long term reference frame (I/IDR frames) when
           * IH264ENC_LTRPScheme is IH264ENC_LTRP_REFERTOIDR
           */
  IH264ENC_CTRL_NOWRITE_NOREFUPDATE,
          /**< Current frame is a non-referencing P frame and do
           * not update the reference frame for this frame. Applicable
           * when IH264ENC_LTRPScheme is IH264ENC_LTRP_REFERTOP_PROACTIVE
           */
  IH264ENC_CTRL_WRITE_NOREFUPDATE,
          /**< Current frame is a referencing P frame and do
           * not update the reference frame for this frame. Applicable
           * when IH264ENC_LTRPScheme is IH264ENC_LTRP_REFERTOP_PROACTIVE
           */
  IH264ENC_CTRL_NOWRITE_REFUPDATE,
          /**< Current frame is a non-referencing P frame and
           * update the reference frame for this frame. Applicable
           * when IH264ENC_LTRPScheme is IH264ENC_LTRP_REFERTOP_PROACTIVE
           */
  IH264ENC_CTRL_WRITE_REFUPDATE,
          /**< Current frame is a referencing P frame and 
           * update the reference frame for this frame. Applicable
           * when IH264ENC_LTRPScheme is IH264ENC_LTRP_REFERTOP_PROACTIVE
           */
  IH264ENC_CTRL_START_GDR
          /**< Current frame is a choosen to start the GDR activity. Applicable
           * when intraRefreshMethod is IH264_INTRAREFRESH_GDR
           */
} IH264ENC_Control;

/**
 *  @enum       IH264ENC_LTRPScheme
 *  @brief      Diffrent types of long term-frame referencing scheme
 *              Eg: Mark all the I frames as long term-reference frame
 */typedef enum {
  IH264ENC_LTRP_NONE = 0,
          /**< No longterm refernce frame in the sequnce
           */
  IH264ENC_LTRP_REFERTO_PERIODICLTRP = 1,
          /**< Mark frames as long-term reference frame with the period given
           * by LTRPPeriod of IH264ENC_Params and 
           * based on the frame control IH264ENC_Control, refer to
           * the long-term reference frame .
           */
  IH264ENC_LTRP_REFERTOP_PROACTIVE =2,
          /**< Two long term frames are supported in this schme and
           * long-term index marking and refernce frame update is done based
           * the IH264ENC_Control values
           */
  IH264ENC_LTRP_REFERTOP_REACTIVE = 3
          /**< Mark frames as long-term reference frame with the period given
           * by LTRPPeriod of IH264ENC_Params.
           * At any point of time there will be 2 long-term frames and 
           * based on the frame control IH264ENC_Control, refer to
           * the last long-term reference frame .
           */
}IH264ENC_LTRPScheme;

/**
 *  @enum       IH264ENC_PicOrderCountType
 *  @brief      Picture Order Count Type Identifier for H.264 Encoder
*/
typedef enum
{
  IH264_POC_TYPE_0 = 0,                       /**< POC type 0   */
  IH264_POC_TYPE_DEFAULT = IH264_POC_TYPE_0,  /**< Default poc type */
  IH264_POC_TYPE_1 = 1,                       /**< POC type 1   */
  IH264_POC_TYPE_2 = 2,                       /**< POC type 2   */
  IH264_POC_TYPE_MAX

} IH264ENC_PicOrderCountType ;


/**
  
  @enum   IH264ENC_ScalingMatPreset
  @brief  These enumerations control the type of scaling matrix picked up
          by encoder
  
*/
typedef enum
{
  IH264_SCALINGMATRIX_NONE        = 0 ,
      /**< Default Scaling matrix (No scaling) */
  IH264_SCALINGMATRIX_NORMAL      = 1 , 
      /**< Flat Scaling matrix: part of standard (NO Scaling Matrix) */
  IH264_SCALINGMATRIX_DEFAULT     = IH264_SCALINGMATRIX_NORMAL, 
      /**< For normal contents */
  IH264_SCALINGMATRIX_NOISY       = 2 , 
      /**< For noisy contents  */
  IH264_SCALINGMATRIX_STD_DEFAULT = 3 , 
  /**< Default Scaling Matrix provided by H.264 standard */
  IH264_SCALINGMATRIX_USERDEFINED_SPSLEVEL = 4 , 
  /**< User defined SM at SPS level*/
  IH264_SCALINGMATRIX_USERDEFINED_PPSLEVEL = 5 ,
  /**< User defined SM at PPS level*/
  IH264_SCALINGMATRIX_MAX  

} IH264ENC_ScalingMatPreset;


/**
  
  @enum   IH264ENC_RateControlAlgo
  @brief  These enumerations control the type of rateControl algo to be picked
          up by encoder. Only useful if IVIDENC2::rateControlPreset is set as 
          IVIDEO_USER_DEFINED
  
*/
typedef enum
{
  IH264_RATECONTROL_PRC               = 0 ,        /**< Perceptual Rate Control, 
                                                   * controls the QP @ MB level 
                                                   */
  IH264_RATECONTROL_PRC_LOW_DELAY     = 1,         /** Low Delay Rate Control */
  IH264_RATECONTROL_DEFAULT = IH264_RATECONTROL_PRC/** Default rcAlgo is PRC  */

} IH264ENC_RateControlAlgo;


/**
  
  @enum   IH264ENC_FrameQualityFactor
  @brief  These enumerations control the quality factor b/w two types of frames
          For example if user want I frame Quality to be given more importance
          than P frame, one can define it to be higher quality factor
  
*/
typedef enum
{
  IH264_QUALITY_FACTOR_1  = 0 ,   /**< Same Quality factor 
                                  * b/w two types of frame
                                  */
  IH264_QUALITY_FACTOR_DEFAULT  = IH264_QUALITY_FACTOR_1, 
                                  /**< Default Quality factor 
                                  * to be used by encoder
                                  */
  IH264_QUALITY_FACTOR_2  = 1 ,   /**< High Quality factor to 
                                  * one frame type b/w two types 
                                  of frame
                                  */
  IH264_QUALITY_FACTOR_3  = 2 ,   /**< Higher Quality factor to 
                                  one frame type b/w two types of frame
                                  */
  IH264_QUALITY_FACTOR_MAX

} IH264ENC_FrameQualityFactor ;



/**
  
  @enum   IH264ENC_RateControlParamsPreset
  @brief  These enumerations control the RateControl Params
  
*/

typedef enum
{
  IH264_RATECONTROLPARAMS_DEFAULT     = 0 , 
      /**< Default Rate Control params */
  IH264_RATECONTROLPARAMS_USERDEFINED = 1 , 
      /**< User defined Rate Control params */
  IH264_RATECONTROLPARAMS_EXISTING    = 2 , 
      /**< Keep the Rate Control params as existing. This is 
      * useful because during control call if user don't want 
      * to chnage the Rate Control Params
      */
  IH264_RATECONTROLPARAMS_MAX

} IH264ENC_RateControlParamsPreset;

/**
  
  @enum   IH264ENC_InterCodingPreset
  @brief  These enumerations control the type of inter coding 
  
*/

typedef enum
{
  IH264_INTERCODING_DEFAULT     = 0 , /**< Default Inter coding params      */
  IH264_INTERCODING_USERDEFINED = 1 , /**< User defined inter coding params */
  IH264_INTERCODING_EXISTING    = 2 , /**< Keep the inter coding params as
                                       *  existing. This is useful because
                                       *  during control call if user don't
                                       *  want to chnage the inter coding Params
                                       */
  IH264_INTERCODING_MED_SPEED_HIGH_QUALITY   = 3 , /**< Med Speed High Quality*/
  IH264_INTERCODING_HIGH_SPEED               = 4, /**< High Speed Preset*/
  IH264_INTERCODING_MAX

} IH264ENC_InterCodingPreset;

/**

  @enum   IH264ENC_MeAlgoMode
  @brief  These enumerations control the mealgo selected

*/

typedef enum
{
  IH264ENC_MOTIONESTMODE_NORMAL     = 0 ,          /**< Normal meAlgo         */
  IH264ENC_MOTIONESTMODE_HIGH_SPEED  = 1 ,         /**< meAlgo for HIGH SPEED */
  IH264ENC_MOTIONESTMODE_DEFAULT    = IH264ENC_MOTIONESTMODE_NORMAL , 
                                                   /**< Default meAlgo        */
  IH264ENC_MOTIONESTMODE_MAX
  
} IH264ENC_MeAlgoMode;

/**

  @enum   IH264ENC_IntraCodingBias
  @brief  These enumerations control the number of intra Mbs to be encoded

*/

typedef enum
{
  IH264ENC_INTRACODINGBIAS_NORMAL      = 0 , 
                                     /**< Normal number of intra Mbs          */
  IH264ENC_INTRACODINGBIAS_HIGH_SPEED  = 12 , 
                                     /**< intra Mbs restricted for HIGH SPEED */
  IH264ENC_INTRACODINGBIAS_DEFAULT     = IH264ENC_INTRACODINGBIAS_NORMAL ,
                                     /**< Default intra codign bias           */
  IH264ENC_INTRACODINGBIAS_MAX
  
} IH264ENC_IntraCodingBias;

/**

  @enum   IH264ENC_InterBlockSize
  @brief  These enumerations are defined for minimum Inter block size
  
*/

typedef enum
{
  IH264_BLOCKSIZE_16x16     = 0 ,                    /**< 16x16 Block size    */
  IH264_BLOCKSIZE_DEFAULT   = IH264_BLOCKSIZE_16x16, /**< Default block size  */
  IH264_BLOCKSIZE_8x8       = 1 ,                    /**< 8x8 Block size      */
  IH264_BLOCKSIZE_4x4       = 2 ,                    /**< 4x4 Block size      */
  IH264_BLOCKSIZE_MAX

} IH264ENC_InterBlockSize;

/**
  
  @enum   IH264ENC_BiasFactor
  @brief  Encoder uses bias b/w two possible chices for lot of decisions. 
  It is to control the mild/strong ness of the biasing
  
*/
typedef enum 
{
  IH264_BIASFACTOR_LOW      = 0 ,                       
                                  /**< Low biasing                */
  IH264_BIASFACTOR_MEDIUM   = 1 ,                       
                                  /**< Normal/Med biasing         */
  IH264_BIASFACTOR_NORMAL   = IH264_BIASFACTOR_MEDIUM,  
                                  /**< Normal/Med biasing         */
  IH264_BIASFACTOR_DEFAULT  = IH264_BIASFACTOR_MEDIUM,  
                                  /**< Default :Normal/Med biasing*/
  IH264_BIASFACTOR_HIGH     = 2 ,                       
                                  /**< High biasing               */
  IH264_BIASFACTOR_MILD       = 4 , /**< Mild biasing             */
  IH264_BIASFACTOR_ADAPTIVE       = 5 , /**< Adaptive biasing     */
  IH264_BIASFACTOR_MAX
} IH264ENC_BiasFactor ;


/**
  
  @enum   IH264ENC_IntraRefreshMethods
  @brief  Refresh method Type Identifier for H.264 Encoder
  
*/

typedef enum
{
  IH264_INTRAREFRESH_NONE       = 0 ,  /**< Doesn't insert forcefully intra 
                                            macro blocks */
  IH264_INTRAREFRESH_DEFAULT    = IH264_INTRAREFRESH_NONE, 
                                       /**< Default intra refresh is OFF */
  IH264_INTRAREFRESH_CYCLIC_MBS     ,  /**< Insters intra macro blocks in a 
                                       * cyclic fashion cyclic interval is 
                                       * equal to intraRefreshRate
                                       */
  IH264_INTRAREFRESH_CYCLIC_SLICES  ,  /**< Insters Intra Slices(Row based) in 
                                       * a cyclic fashion: 
                                       * cyclic interval is equal to 
                                       * intraRefreshRate
                                       */
  IH264_INTRAREFRESH_RDOPT_MBS      ,  /**< position of intra macro blocks is 
                                       * intelligently  chosen by encoder, 
                                       * but the number of forcely coded 
                                       * intra macro blocks in a frame is 
                                       * gaurnteed to be equal to 
                                       * totalMbsInFrame/intraRefreshRate 
                                       */
  IH264_INTRAREFRESH_GDR            ,  /**< Instead of a sudden Intra Refresh
                                       * of entire frame, the frame is refreshed
                                       * Gradualy over a duration (which is con-
                                       * figerable) of frames with refresh 
                                       * happening by Intra coded rows scanning 
                                       *from top to bottom of the scene/picture.
                                       */
  IH264_INTRAREFRESH_MAX

} IH264ENC_IntraRefreshMethods ;

/**
  
  @enum   IH264ENC_ChormaComponent
  @brief  These enumerations control the selction of chroma component to perfom 
          chroma intra estimation 
  
*/
typedef enum
{
  IH264_CHROMA_COMPONENT_CB_CR_BOTH  = 0 , /**< BOth Cb and Cr component */
  IH264_CHROMA_COMPONENT_CR_ONLY     = 1 , /**< Only Cr Component        */
  IH264_CHROMA_COMPONENT_DEFAULT     = IH264_CHROMA_COMPONENT_CR_ONLY, 
      /**< Default is Only Cr Component */
  IH264_CHROMA_COMPONENT_MAX

} IH264ENC_ChormaComponent;


/**
  
  @enum   IH264ENC_IntraCodingPreset
  @brief  These enumerations control the type of intra coding 
  
*/

typedef enum
{
  IH264_INTRACODING_DEFAULT     = 0 , /**< Default intra coding params      */
  IH264_INTRACODING_USERDEFINED = 1 , /**< User defined intra coding params */
  IH264_INTRACODING_EXISTING    = 2 , 
  IH264_INTRACODING_HIGH_SPEED  = 3 , /**< High Speed intra Coding Preset   */
  IH264_INTRACODING_MAX

} IH264ENC_IntraCodingPreset;

/**
  
  @enum   IH264ENC_NALUnitType
  @brief  These enumerations define the NALU type supported by H.264
  
*/
typedef enum
{
  IH264_NALU_TYPE_UNSPECIFIED          =  0 , 
    /**< Unspecified Slice Type               */
  IH264_NALU_TYPE_SLICE                =  1 , 
    /**< slice of a non-IDR picture           */
  IH264_NALU_TYPE_SLICE_DP_A           =  2 , 
    /**< Coded slice data partition A         */
  IH264_NALU_TYPE_SLICE_DP_B           =  3 , 
    /**< Coded slice data partition B         */
  IH264_NALU_TYPE_SLICE_DP_C           =  4 , 
    /**< Coded slice data partition C         */
  IH264_NALU_TYPE_IDR_SLICE            =  5 , 
    /**< slice of an IDR picture              */
  IH264_NALU_TYPE_SEI                  =  6 , 
    /**< Supplemental enhancement information */
  IH264_NALU_TYPE_SPS                  =  7 , 
    /**< Sequence parameter set               */
  IH264_NALU_TYPE_PPS                  =  8 , 
    /**< Picture parameter set                */
  IH264_NALU_TYPE_AUD                  =  9 , 
    /**< Access unit delimiter                */
  IH264_NALU_TYPE_EOSEQ                = 10 , 
    /**< End of sequence                      */
  IH264_NALU_TYPE_EOSTREAM             = 11 , 
    /**< End of stream                        */
  IH264_NALU_TYPE_FILLER               = 12 , 
    /**< Filler data                          */
  IH264_NALU_TYPE_SPS_WITH_VUI         = 13,  
    /**< Sequence parameter set with VUI      */
  IH264_NALU_TYPE_USER_DATA_UNREGD_SEI = 14,   
    /**< User Data unregsitered SEI           */
  IH264_NALU_TYPE_SSPS                 = 15,   
    /**< Sub-Sequence Parameter Set for SVC   */
  IH264_NALU_TYPE_CODED_SLICE_IN_SCALABLE_EXTN = 20   
    /**< Coded Slice in Scalable Extn for SVC   */

} IH264ENC_NALUnitType;


/**
  
  @enum   IH264ENC_NALUControlPreset
  @brief  These enumerations define the control mechanism for insertion of 
          different NALU types at different point in video sequence
  
*/

typedef enum
{
  IH264_NALU_CONTROL_DEFAULT     = 0 , /**< Default NALU insertion      */
  IH264_NALU_CONTROL_USERDEFINED = 1 , /**< User defined NALU insertion */
  IH264_NALU_CONTROL_MAX

} IH264ENC_NALUControlPreset;

/**
  
  @enum   IH264ENC_SliceCodingPreset
  @brief  These enumerations control the type of slice coding 
  
*/

typedef enum
{
  IH264_SLICECODING_DEFAULT     = 0 , 
    /**< Default slice coding params                        */
  IH264_SLICECODING_USERDEFINED = 1 , 
    /**< User defined slicecoding params                    */
  IH264_SLICECODING_EXISTING    = 2 , 
    /**< Keep the slice coding params as existing           */
    /**< This is useful because during control call         */
    /**< if user don't want to chnage the sliceCodingParams */
  IH264_SLICECODING_MAX

} IH264ENC_SliceCodingPreset;

/**
  
  @enum   IH264ENC_SliceMode
  @brief  These enumerations control the type of slice coding 
  
*/

typedef enum
{
  IH264_SLICEMODE_NONE    = 0 ,
  IH264_SLICEMODE_DEFAULT = IH264_SLICEMODE_NONE , 
    /**< Default slice coding mode is MB based */
  IH264_SLICEMODE_MBUNIT  = 1 , 
    /**< Slices are controlled based upon number of Macroblocks   */
  IH264_SLICEMODE_BYTES   = 2 , 
    /**< Slices are controlled based upon number of bytes         */
  IH264_SLICEMODE_OFFSET  = 3 , 
    /**< Slices are controlled based upon user defined offset in 
    * unit of Rows
    */
  IH264_SLICEMODE_MAX

} IH264ENC_SliceMode;

/**
  
  @enum   IH264ENC_StreamFormat
  @brief  These enumerations control the type stream format
  
*/
typedef enum
{
  IH264_BYTE_STREAM = 0,                            
    /**< bit-stream contains the start code identifier*/
  IH264_STREAM_FORMAT_DEFAULT = IH264_BYTE_STREAM , 
    /**< Default slice coding mode is byte-stream     */
  IH264_NALU_STREAM = 1,                            
  /**< bit-stream doesn't contain the start code identifier */
  IH264_STREAM_FORMAT_MAX
}IH264ENC_StreamFormat;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @enum   IH264ENC_LoopFilterPreset
 * @brief  These enumerations control the type of slice coding 
*/

typedef enum
{
  IH264_LOOPFILTER_DEFAULT     = 0 , /**< Default loop-filtering params      */
  IH264_LOOPFILTER_USERDEFINED = 1 , /**< User defined loop-filtering params */
  IH264_LOOPFILTER_MAX
} IH264ENC_LoopFilterPreset;

/**
  
  @enum   IH264ENC_LoopFilterDisableIDC
  @brief  Control Parameter to disable loop filter at different places
  
*/
typedef enum 
{
  IH264_DISABLE_FILTER_NONE = 0,                              
    /**< Enable filtering of all the edges */
  IH264_DISABLE_FILTER_DEFAULT   = IH264_DISABLE_FILTER_NONE, 
    /**< Default is Loop filter enabled    */
  IH264_DISABLE_FILTER_ALL_EDGES,                             
    /**< Disable filtering of all the edge */
  IH264_DISABLE_FILTER_SLICE_EDGES,                           
    /**< Disable filtering of slice edges  */
  IH264_DISABLE_FILTER_MAX
} IH264ENC_LoopFilterDisableIDC ;

/**
  
  @enum   IH264ENC_SliceGroupMapType
  @brief  Slice group map type defined by H.264 standard
  
*/

typedef enum
{
  IH264_INTERLEAVED_SLICE_GRP             = 0 , 
    /**< 0 : Interleaved Slice Group    */
  IH264_DISPERSED_SLICE_GRP               = 1 , 
    /**< 1 : Dispersed Slice Group      */
  IH264_FOREGRND_WITH_LEFTOVER_SLICE_GRP  = 2 , 
    /**< 2 : ForeGround with Left Over  */
  IH264_BOX_OUT_SLICE_GRP                 = 3 , 
    /**< 3 : Box Out                    */
  IH264_RASTER_SCAN_SLICE_GRP             = 4 , 
    /**< 4 : Raster Scan                */
  IH264_SLICE_GRP_MAP_DEFAULT             = IH264_RASTER_SCAN_SLICE_GRP,
    /**< Default*/
  IH264_WIPE_SLICE_GRP                    = 5 , 
    /**< 5 : Wipe slice group           */
  IH264_EXPLICIT_SLICE_GRP                = 6   
    /**< 6 : Explicit Slice gropup map  */
} IH264ENC_SliceGroupMapType ; 

/**
  
  @enum   IH264ENC_SliceGroupChangeDirection
  @brief  Different Scan /rotation oreder
  
*/

typedef enum
{
  IH264_RASTER_SCAN             = 0 , 
    /**< 0 : Raster scan order                      */
  IH264_CLOCKWISE               = 0 , 
    /**< 0 : Clockwise (used for BOX OUT FMO Params)*/
  IH264_RIGHT                   = 0 , 
    /**< 0 : RIGHT (Used for Wipe FMO type)         */
  IH264ENC_SLICEGROUP_CHANGE_DIRECTION_DEFAULT = IH264_RASTER_SCAN, 
    /**< Default      */                  
  IH264_REVERSE_RASTER_SCAN     = 1 , 
    /**< 1 : Reverse Raster Scan Order              */
  IH264_COUNTER_CLOCKWISE       = 1 , 
    /**< 1 : Counter Clockwise (used for BOX OUT 
    * FMO Params)
    */
  IH264_LEFT                    = 1  
    /**< 1 : LEFT (Used for Wipe FMO type)           */
} IH264ENC_SliceGroupChangeDirection ;

/**
  
  @enum   IH264ENC_FMOCodingPreset
  @brief  Preset to define FMO coding type
  
*/

typedef enum
{
  IH264_FMOCODING_NONE             = 0 ,                    /**< 0 : NO FMO */
  IH264_FMOCODING_DEFAULT          = IH264_FMOCODING_NONE,  /**< 0 : NO FMO */
  IH264_FMOCODING_USERDEFINED      = 1 /**< 1 : User defined FMO parameters */

} IH264ENC_FMOCodingPreset ;


/**
  
  @enum   IH264ENC_VUICodingPreset
  @brief  Defines the Preset for VUI coding
  
*/

typedef enum
{
  IH264_VUICODING_DEFAULT          = 0,   /**< Default VUI Parameters. Note that 
                                          * Enable/Disable of VUI is via 
                                          * nalUnitControlParams 
                                          */
  IH264_VUICODING_USERDEFINED      = 1,   /**< 1 : User defined VUI parameters*/
  IH264_VUICODING_MAX                     /**< Max VUI Coding enum            */

} IH264ENC_VUICodingPreset ;


/**
  
  @enum   IH264ENC_VideoFormat
  @brief  Defines different video formats 
  
*/
typedef enum 
{
  IH264ENC_VIDEOFORMAT_COMPONENT,  /**< component video format  */
  IH264ENC_VIDEOFORMAT_PAL,        /**< PAL video format        */
  IH264ENC_VIDEOFORMAT_NTSC,       /**< NTSC video format       */
  IH264ENC_VIDEOFORMAT_SECAM,      /**< SECAM video format      */
  IH264ENC_VIDEOFORMAT_MAC,        /**< MAC video format        */
  IH264ENC_VIDEOFORMAT_UNSPECIFIED /**< Unspecified video format*/
} IH264ENC_VideoFormat ;

/**
  
  @enum   IH264ENC_StereoInfoPreset
  @brief  Defines the Preset for Stereo Video Info coding*/
  
typedef enum
{
  IH264_STEREOINFO_DISABLE            = 0,   /* StereoVideoCoding is disable */
  IH264_STEREOINFO_ENABLE_DEFAULT     = 1,   /* Default Stereo Video Info 
                                                Parameters enabled.       */
  IH264_STEREOINFO_ENABLE_USERDEFINED = 2,   /* User defined Stereo Video Info
                                                parameters enabled           */    
  IH264_STEREOINFO_MAX                       /* Max Stereo Video Info enum   */

} IH264ENC_StereoInfoPreset ;

/**
  
  @enum   IH264ENC_FramePackingPreset
  @brief  Defines the Preset for Frame packing SEI coding*/
  
typedef enum
{
  IH264_FRAMEPACK_SEI_DISABLE         = 0, /* Frame packing SEI is disable */
  IH264_FRAMEPACK_SEI_ENABLE_DEFAULT  = 1, /* Default Frame packing SEI 
                                            Parameters enabled.       */
  IH264_FRAMEPACK_SEI_USERDEFINED     = 2, /* User defined SFrame packing 
                                                SEIparameters enabled        */    
  IH264_FRAMEPACK_SEI_MAX                  /* Max Stereo Video Info enum   */

} IH264ENC_FramePackingPreset ;

/**
  
  @enum   IH264ENC_FramePackingType
  @brief  Defines the type of packing arrangement for
          Frame packing SEI coding
*/
  
typedef enum
{
  IH264_FRAMEPACK_CHECKERBOARD        = 0,
  IH264_FRAMEPACK_COLUMN_INTERLEAVING = 1,
  IH264_FRAMEPACK_ROW_INTERLEAVING    = 2,
  IH264_FRAMEPACK_SIDE_BY_SIDE        = 3,
  IH264_FRAMEPACK_TOP_BOTTOM          = 4,
  IH264_FRAMEPACK_TYPE_DEFAULT        = IH264_FRAMEPACK_SIDE_BY_SIDE, 
  IH264_FRAMEPACK_TYPE_MAX                 

} IH264ENC_FramePackingType ;

/**
  
  @enum   IH264ENC_AspectRatioIdc
  @brief  Defines aspect ratio IDs
  
*/
typedef enum
{
  IH264ENC_ASPECTRATIO_UNSPECIFIED,    /**< Unspecified aspect ratio  */
  IH264ENC_ASPECTRATIO_SQUARE ,        /**< 1:1 (square) aspect ratio */
  IH264ENC_ASPECTRATIO_12_11  ,        /**<  12:11  aspect ratio      */
  IH264ENC_ASPECTRATIO_10_11  ,        /**<  10:11  aspect ratio      */
  IH264ENC_ASPECTRATIO_16_11  ,        /**<  16:11  aspect ratio      */
  IH264ENC_ASPECTRATIO_40_33  ,        /**<  40:33  aspect ratio      */
  IH264ENC_ASPECTRATIO_24_11  ,        /**<  24:11  aspect ratio      */
  IH264ENC_ASPECTRATIO_20_11  ,        /**<  20:11  aspect ratio      */
  IH264ENC_ASPECTRATIO_32_11  ,        /**<  32:11  aspect ratio      */
  IH264ENC_ASPECTRATIO_80_33  ,        /**<  80:33  aspect ratio      */
  IH264ENC_ASPECTRATIO_18_11  ,        /**<  18:11  aspect ratio      */
  IH264ENC_ASPECTRATIO_15_15  ,        /**<  15:15  aspect ratio      */
  IH264ENC_ASPECTRATIO_64_33  ,        /**<  64:33  aspect ratio      */
  IH264ENC_ASPECTRATIO_160_99 ,        /**<  160:99 aspect ratio      */
  IH264ENC_ASPECTRATIO_4_3    ,        /**<  4:3    aspect ratio      */
  IH264ENC_ASPECTRATIO_3_2    ,        /**<  3:2    aspect ratio      */
  IH264ENC_ASPECTRATIO_2_1    ,        /**<  2:1    aspect ratio      */  
  IH264ENC_ASPECTRATIO_EXTENDED = 255  /**<  Extended aspect ratio    */

} IH264ENC_AspectRatioIdc ;

/**
  
  @enum   IH264ENC_EntropyCodingMode
  @brief  Defines the different entropy code mode
  
*/
typedef enum 
{
  IH264_ENTROPYCODING_CAVLC = 0 ,                           /**< CAVLC coding 
                                                              type            
                                                             */
  IH264_ENTROPYCODING_DEFAULT = IH264_ENTROPYCODING_CAVLC , /**< Default is 
                                                            CAVLC coding type 
                                                            */
  IH264_ENTROPYCODING_CABAC = 1 ,                           /**< CABAC coding 
                                                            type            
                                                            */
  IH264_ENTROPYCODING_MAX        
} IH264ENC_EntropyCodingMode ;

/**
  
  @enum   IH264ENC_TransformBlockSize
  In H264 Intra macro block's transform size depends upon the Intra mode,
  so this applies to inter macroblocks only
  
*/
typedef enum 
{
  IH264_TRANSFORM_4x4      = 0 ,                        /**< Transform blocks 
                                                             size is 4x4 */
  IH264_TRANSFORM_8x8      = 1 ,                        /**< Transform blocks 
                                                        *    size is 8x8 : 
                                                        *    Valid for only 
                                                        *    High Profile
                                                        */
  IH264_TRANSFORM_ADAPTIVE = 2 ,                        /**< Adaptive transform 
                                                        *    block size : 
                                                        *    encoder decides 
                                                        *    as per content
                                                        */
  IH264_TRANSFORM_DEFAULT  = IH264_TRANSFORM_ADAPTIVE  ,/**< Default is adaptive 
                                                        *  based upon content
                                                        */
  IH264_TRANSFORM_MAX  

} IH264ENC_TransformBlockSize ;



/**
  
  @enum   IH264ENC_GOPStructure
  @brief 
  When B frames are used (InterFrameInterval > 1) then the arrangement of 
  frames can be different
  
  GOP structure in display order as indicated below
  If contentType = Frame
  IH264ENC_GOPSTRUCTURE_NONUNIFORM : IBBPBBP. . 
  IH264ENC_GOPSTRUCTURE_UNIFORM : BBIBBPBB. .
  If contentType = Field
  IH264ENC_GOPSTRUCTURE_NONUNIFORM : IPBBBBPBBBB
  IH264ENC_GOPSTRUCTURE_UNIFORM : BBBBIPBBBBPPBBBB
  
*/

typedef enum 
{
  IH264ENC_GOPSTRUCTURE_NONUNIFORM  = 0 ,                              
    /**< Open Gop structure  : IBBPBBP */
  IH264ENC_GOPSTRUCTURE_DEFAULT  = IH264ENC_GOPSTRUCTURE_NONUNIFORM  , 
    /**< Default is open gop structure */
  IH264ENC_GOPSTRUCTURE_UNIFORM = 1 ,                                  
    /**< Close Gop structure : BBIBBPBB*/
  IH264ENC_GOPSTRUCTURE_MAX  

} IH264ENC_GOPStructure ;


/**
  
  @enum   IH264ENC_BiasFactor
  @brief  Encoder uses bias b/w two possible chices for lot of decisions. 
          It is to control the mild/strong ness of the biasing
  
*/
typedef enum 
{
  IH264_INTERLACE_PICAFF                = 0 ,                           
    /**< PicAFF type of interlace coding    */
  IH264_INTERLACE_MBAFF                 = 1 ,                           
    /**< MBAFF type of interlace coding     */
  IH264_INTERLACE_FIELDONLY             = 2 ,                           
    /**< Field only coding with fixed partiy scheme  */
  IH264_INTERLACE_FIELDONLY_MRF         = IH264_INTERLACE_FIELDONLY ,   
    /**< Use Most recent field for refernece*/
  IH264_INTERLACE_FIELDONLY_ARF         = 3 , 
    /**< Field only coding where codec decides the partiy of of the field to 
    *    be used based upon content (adaptive) */
  IH264_INTERLACE_DEFAULT               = IH264_INTERLACE_FIELDONLY_ARF , 
    /**< Default : adaptive partiy for reference*/
  IH264_INTERLACE_FIELDONLY_SPF         = 4,                              
    /**< Use same parity field for refernece    */

  IH264_INTERLACE_MAX         
} IH264ENC_InterlaceCodingType ;
/**
  @enum   IH264ENC_NumTemporalLayer
  @brief  Define different Temporal Layers
*/
typedef enum 
{
  /* Only Base Layer  */
  IH264_TEMPORAL_LAYERS_1                = 1 ,                           

  /* Base Layer + Temporal Layer     */
  IH264_TEMPORAL_LAYERS_2                = 2 ,                           

  /* Base Layer + 2Temporal Layers   */
  IH264_TEMPORAL_LAYERS_3                = 3 ,                           

  /* Base Layer + 3Temporal Layers   */
  IH264_TEMPORAL_LAYERS_4                = 4 ,                           

  /* Maximum Temporal Layer Supported*/
  IH264_TEMPORAL_LAYERS_MAX              = IH264_TEMPORAL_LAYERS_4

} IH264ENC_NumTemporalLayer ;

/**
  @enum  IH264ENC_RoiType  
  @brief Defines the different ROI types
*/
typedef enum {
  IH264_FACE_OBJECT       = 0,
    /**< Face type of ROI object               */
  IH264_BACKGROUND_OBJECT = 1,
    /**< Background type of ROI object         */
  IH264_FOREGROUND_OBJECT = 2,
    /**< Foreground type of ROI object         */
  IH264_DEFAULT_OBJECT    = 3,
    /**< Default type of ROI object            */
  IH264_PRIVACY_MASK      = 4
    /**< Privacy mask type of ROI object       */
} IH264ENC_RoiType;

/**
  @enum   IH264ENC_SvcExtensionFlag
  @brief  Define SVC Extension Flag
*/
typedef enum 
{
 /*Svc Extension Flag Disabled*/
  IH264_SVC_EXTENSION_FLAG_DISABLE               = 0 ,                           
  /*Svc Extension Flag Enabled*/
  IH264_SVC_EXTENSION_FLAG_ENABLE                = 1 ,    
  /*Svc Extension Flag Enabled with EC Flexibility*/
  IH264_SVC_EXTENSION_FLAG_ENABLE_WITH_EC_FLEXIBILITY = 2

} IH264ENC_SvcExtensionFlag ;

/**
  @enum   IH264ENC_ReferencePicMarking
  @brief  Define Reference Picture Marking
*/
typedef enum 
{
 /* ReferencePicMarking is Short-term picutre(Sliding Window) */
  IH264_SHORT_TERM_PICTURE               = 0 ,                           
 /* ReferencePicMarking is Long-term picutre(MMCO Commands) */
  IH264_LONG_TERM_PICTURE                = 1                           

} IH264ENC_ReferencePicMarking ;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Definition of all the structures define by this interafce   */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
  
  @struct IH264ENC_RateControlParams
  @brief  This structure contains all the parameters which controls Rate 
          Control behavior

  @param  rateControlParamsPreset : 
          regarded @ IH264ENC_DynamicParams::rateControlParams
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_RATECONTROLPARAMS_DEFAULT
  @param  scalingMatrixPreset  : 
          ignored @ IH264ENC_DynamicParams::rateControlParams
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_SCALINGMATRIX_DEFAULT
          
  @param  rcAlgo  : ignored @ IH264ENC_DynamicParams::rateControlParams
          This defines the rate control algorithm to be used. Only useful 
          if IVIDENC2::rateControlPreset is set as IVIDEO_USER_DEFINED

  @param  qpI  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Initial Quantization Parameter for I/IDR frames. 
          Valid Range is [-1, 51]
          -1 : Auto Initialization else other wise Initial QP.
          when rateControlPreset = IVIDEO_NONE, this quantization parameter is 
          used by the whole video frame/field 

  @param  qpMaxI  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Maximum Quantization Parameter for I/IDR frame(s). Range [0 , 51]. 
          Useful to control a minimum quality level

  @param  qpMinI  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Minimum Quantization Parameter for I/IDR frame(s). Range [0 , 51]. 
          Useful to control a maximum bit-rate level

  @param  qpP  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Initial Quantization Parameter for P frames. Valid Range is [-1, 51]
          -1 : Auto Initialization else other wise Initial QP.
          when rateControlPreset = IVIDEO_NONE, this quantization parameter is 
          used by the whole video frame/field 

  @param  qpMaxP  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Maximum Quantization Parameter for inter frame(s). Range [0 , 51]. 
          Useful to control a minimum quality level

  @param  qpMinP  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Minimum Quantization Parameter for inter frame(s). Range [0 , 51]. 
          Useful to control a maximum bit-rate level

  @param  qpOffsetB  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Offset of B frames Quantization Parameter from P frames. 
          Valid Range is [-1, 51]
          -1 : Auto Initialization else other wise user provided offset
      if after adding the qpOffsetB into qp of P frame it exceeds 51 then
      it is clipped to 51
          when rateControlPreset = IVIDEO_NONE, this offset parameter is 
          used by the whole video frame/field 

  @param  qpMaxB  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Maximum Quantization Parameter for B frame(s). Range [0 , 51]. 
          Useful to control a minimum quality level

  @param  qpMinB  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Minimum Quantization Parameter for B frame(s). Range [0 , 51]. 
          Useful to control a maximum bit-rate level

  @param  allowFrameSkip  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Controls Frame Skip. 
          non-zero means frames can be skipped to  achieve target bit-rate 
          zero means frame can never be skipped

  @param  removeExpensiveCoeff : 
          regarded @ IH264ENC_DynamicParams::rateControlParams
          Flag to Remove high frequency expensive coeffecients 

  @param  chromaQPIndexOffset  : 
          ignored @ IH264ENC_DynamicParams::rateControlParams
          Specifies offset to be added to luma QP for addressing QPC values 
          table for chroma components. 
          Valid value is between -12 and 12, (inclusive)

  @param  IPQualityFactor  : ignored @ IH264ENC_DynamicParams::rateControlParams
          This provides configurality to control I frame Quality wrt to P frame. 
          Higher Quality factor means I frame quality is given higher 
          improtance compared to P frame. 
          Refer IH264ENC_FrameQualityFactor for possible values

  @param  initialBufferLevel  : 
          ignored @ IH264ENC_DynamicParams::rateControlParams
          Initial Buffer level for HRD compliance. It informs that Hypothtical 
          decoder can start after how much time. The value taken is the 
          obsolute value of the HRD buffer size  For example if user want 
          Hypothtical decoder to start taking out data from HRD buffer after 
          half second then it should set initialBufferLevel = half of the 
          HRD buffer size that is programmed. 
          
  @param  HRDBufferSize  : regarded @ IH264ENC_DynamicParams::rateControlParams
          Hypothetical Reference Decoder Buffer Size. This size controls the 
          frame skip  logic of the encoder. for low delay applications this 
          size should be small. Unit of this variable is bits

  @param  minPicSizeRatio : regarded @ IH264ENC_DynamicParams::rateControlParams
                            This ratio is used to compute minimum picture size 
                            in the following manner, 
                            minPicSize = averagePicSize >> minPicSizeRatio
                            allowed values 1 to 4, Setting this to 0 will enable 
                            encoder chosen ratio.  
                            Note that this is guided value to rate control to 
                            determine min picture size and encoder may not 
                            strictly follow this
  @param  maxPicSizeRatio : regarded @ IH264ENC_DynamicParams::rateControlParams
                            To determines ratio for max picture size
                            This ratio is used to compute maximum picture size 
                            in the following manner, 
                            maxPicSize = averagePicSize * maxPicSizeRatio
                            allowed values 2 to 30.Setting this to 0 and 1 
                            will enable encoder chosen ratio.  
                            Note that this is guided value to rate control 
                            to determine max picture size and encoder may not 
                            strictly follow this.

  @param  enablePRC       : regarded @ IH264ENC_DynamicParams::rateControlParams
                            This flag is used to control allowing PRC in the 
                            frame

  @param  enablePartialFrameSkip : regarded @ IH264ENC_DynamicParams::
                                 rateControlParams
                            This flag is used to control allowing partial frame  
                            skip in the frame
  @param  reserved : 16 bit word, kept to not change the foot print
  @param  VBRDuration : During over which statistics during interval are  
                        collected to switch bit-rate states.Increasing this  
                        value will make VBR wait for longer time before 
                        switching bit-rate state
  @param  VBRsensitivity : Specifies the target bitrate used by rate control in 
                           high complexity state. 
  @param  skipDistributionWindowLength : Number of frames over which the skip  
                                         frames can be distributed  
  @param  numSkipInDistributionWindow : Number of skips allowed within the 
                                         distribution window 
  @param  reservedRC
          Some part is kept reserved to add parameters later without 
          changing the foot print of  interface memory

  @todo  More parameters to be added : delay (VBV), PRC related etc..
  

*/

typedef struct IH264ENC_RateControlParams {
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

} IH264ENC_RateControlParams ;

/**
  @struct   ROI_Interface  
  @brief    This structure defines the ROI input parameters required by Encoder.
  @param  listROI:
                  List of ROIs with their x and y co-ordinates
  @param  roiType:
                  Type of each ROI 
  @param  numOfROI:
                  Number of ROIs passed to codec
  @param roiPriority:
                  Priority of each ROI
*/
typedef struct IH264ENC_RoiInput{
  XDM_Rect   listROI[IH264ENC_MAX_ROI];
  XDAS_Int8  roiType[IH264ENC_MAX_ROI];
  XDAS_Int8  numOfROI;
  XDAS_Int32 roiPriority[IH264ENC_MAX_ROI];
}IH264ENC_RoiInput;

/**
  
  @struct IH264ENC_InterCodingParams
  @brief  This structure contains all the parameters which controls Inter MBs 
          coding behavior
  @param  interCodingPreset  
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_INTERCODING_DEFAULT
  @param  searchRangeHorP :regarded @ IH264ENC_DynamicParams::interCodingParams
          Horizontal Search Range for P frames
  @param  searchRangeVerP :regarded @ IH264ENC_DynamicParams::interCodingParams
          Vertical Search Range for P frames 
  @param  searchRangeHorB :regarded @ IH264ENC_DynamicParams::interCodingParams
          Horizontal Search Range for B frames
  @param  searchRangeVerB :regarded @ IH264ENC_DynamicParams::interCodingParams
          Vertical Search Range for B frames 
  @param  interCodingBias :regarded @ IH264ENC_DynamicParams::interCodingParams      
          Bias Control for having a macro block coded as inter vs Intra
          Refer IH264ENC_BiasFactor for possible values
  @param  skipMVCodingBias :regarded @ IH264ENC_DynamicParams::interCodingParams     
          Bias Control for having a macro block use skip MV vs regular MV
          refer IH264ENC_BiasFactor for possible values
  @param  minBlockSizeP  : regarded @ IH264ENC_DynamicParams::interCodingParams
          minimum block size for P frames. Refer IH264ENC_InterBlockSize 
          enumeration to see the valid values
  @param  minBlockSizeB  : regarded @ IH264ENC_DynamicParams::interCodingParams
          minimum block size for B frames. Refer IH264ENC_InterBlockSize 
          enumeration to see the valid values
  
*/

typedef struct IH264ENC_InterCodingParams {
  XDAS_Int8                  interCodingPreset     ; 
  XDAS_Int16                 searchRangeHorP       ;
  XDAS_Int16                 searchRangeVerP       ;
  XDAS_Int16                 searchRangeHorB       ;
  XDAS_Int16                 searchRangeVerB       ;
  XDAS_Int8                  interCodingBias       ;
  XDAS_Int8                  skipMVCodingBias      ;
  XDAS_Int8                  minBlockSizeP         ; 
  XDAS_Int8                  minBlockSizeB         ; 
  XDAS_Int8                  meAlgoMode            ;

} IH264ENC_InterCodingParams ;

/**
  
  @struct IH264ENC_IntraCodingParams
  @brief  This structure contains all the parameters which controls Intra 
          encoding

  @param  intraCodingPreset  
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          INTRA_CODING_DEFAULT other wise INTRA_CODING_USER_DEFINED
  @param  lumaIntra4x4Enable 
          This parameter controls the Luma Intra4x4 encoding in video encoder. A
          bit-field is given for each Luma intra4x4 mode as shown below. This
          field is H.264 specific HOR_UP|VERT_LEFT|HOR_DOWN|
          VERT_RIGHT|DIAG_DOWN_RIGHT|DIAG_DOWN_LEFT|DC|HOR|VER
          Set/ reset particular bit to enable/disable that mode 
          (0=disable, 1=enable). DC (bit-2)is don't care
  @param  lumaIntra8x8Enable 
          This parameter controls the Luma Intra8x8 encoding in video encoder. A
          bit-field is given for each Luma intra8x8 mode as shown below. 
          HOR_UP|VERT_LEFT|HOR_DOWN|VERT_RIGHT|DIAG_DOWN_RIGHT|DIAG_DOWN_LEFT|
          DC|HOR|VER Set/ reset particular bit to enable/disable that 
          mode (0=disable, 1=enable) DC (bit-2)is don't care
          Example : 139(decimal) ==> 0x8B =>> 010001011 (bits) ==> 
          HOR, VER, VERT_LEFT
          are enabled and DC is always enabled
  @param  lumaIntra16x16Enable 
          This parameter controls the Luma Intra16x16 encoding in video encoder.
          A bit-field is given for each Luma intra16x16 mode as shown below. 
          PLANE|DC|HOR|VER
          Set/ reset particular bit to enable/disable that 
          mode (0=disable, 1=enable). DC (bit-2)is don't care
  @param  chromaIntra8x8Enable 
          This parameter controls the chroma Intra8x8 encoding in video encoder.
          A bit-field is given for each chroma intra8x8 mode as shown below. 
          PLANE|VER|HOR|DC
          Set/ reset particular bit to enable/disable 
          that mode (0=disable, 1=enable) DC (bit-0)is don't care
  @param  chromaComponentEnable
          This parameter controls the chroma Intra prediction search. User 
          can choose to perfom chroma intra estimation for both Cb and Cr 
          samples or only on Cr samples. For more details 
          refer IH264ENC_ChormaComponent
  @param  intraRefreshMethod
          Mechanism to do intra Refresh, see IH264ENC_IntraRefreshMethods 
          for valid values
  @param  intraRefreshRate
          Rate at which intra Refresh is done, This rate is specified as 
          One IntraMB per # MBs. For example if rate is 20 it means that 
          there has to be  one intra MB(s) per 20 Mbs.
          When intraRefreshMethod == IH264_INTRAREFRESH_GDR, this parameter
          is treated/interpreted number of rows to be intra refreshed per
          frame.

  @param  gdrOverlapRowsBtwFrames
          Defines the Overlap of the Intra Refresh Region between successive
          frame in case the intraRefreshMethod == IH264_INTRAREFRESH_GDR or
          else treated to be don't care.
          Again gdrOverlapRowsBtwFrames should be less than intraRefreshRate.
      
  @param  constrainedIntraPredEnable
          Controls the intra macroblock coding in P slices. 
          Valid values are [0,non-zero]
  
*/

typedef struct IH264ENC_IntraCodingParams {
  XDAS_Int8                    intraCodingPreset          ; 
  XDAS_Int16                   lumaIntra4x4Enable         ; 
  XDAS_Int16                   lumaIntra8x8Enable         ; 
  XDAS_Int8                    lumaIntra16x16Enable       ; 
  XDAS_Int8                    chromaIntra8x8Enable       ;
  XDAS_Int8                    chromaComponentEnable      ;
  XDAS_Int8                    intraRefreshMethod         ; 
  XDAS_Int16                   intraRefreshRate           ; 
  XDAS_Int16                    gdrOverlapRowsBtwFrames    ;
  XDAS_Int16                   constrainedIntraPredEnable ;
  XDAS_Int8                    intraCodingBias            ;
} IH264ENC_IntraCodingParams ;


/**
  
  @struct IH264ENC_NALUControlParams
  @brief  This structure contains all the parameters which define the 
          control mechanism for insertion of different NALU types at 
          different point in video sequence

  @param  naluControlPreset  
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_NALU_CONTROL_DEFAULT other wise IH264_NALU_CONTROL_USERDEFINED
  @param  naluPresentMaskStartOfSequence 
          This parameter controls the insertion of different NALU at Start of 
          Sequence
          A bit-field is given for each NALU type as shown below. This field is
\n ---------------------------------------------------------------------\n
\n   7|  6|        5|         4|         3|         2|    1|          0 \n
\n SPS|SEI|IDR_SLICE|SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED \n
\n ---------------------------------------------------------------------\n
\n----------------------------------------------
\n     14|     13|    12|      11|   10|  9|  8|
\n UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|
\n----------------------------------------------
          Set/ reset particular bit to enable/disable that insertion of that 
          NALU (0=disable, 1=enable)
          UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3), 
          SLICE_DP_C(bit-4), IDR_SLICE(bit-5), EOSEQ (bit-10) and 
          EOSTREAM (bit-11) are don't care and assumed to be <b> zero </b>.
          SPS (bit-7), PPS(bit-8) are don't care and assumed to be <b> one </b>.
  @param  naluPresentMaskIDRPicture 
          This parameter controls the insertion of different NALU at IDR picture
          A bit-field is given for each NALU type as shown below. This field is
\n ---------------------------------------------------------------------\n
\n   7|  6|        5|         4|         3|         2|    1|          0 \n
\n SPS|SEI|IDR_SLICE|SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED \n
\n ---------------------------------------------------------------------\n
\n----------------------------------------------
\n     14|     13|    12|      11|   10|  9|  8|
\n UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|
\n----------------------------------------------
          Set/ reset particular bit to enable/disable that insertion of that 
          NALU (0=disable, 1=enable)
          UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3), 
          SLICE_DP_C(bit-4), IDR_SLICE(bit-5), EOSEQ (bit-10) and 
          EOSTREAM (bit-11) are don't care and assumed to be <b> zero </b>.
  @param  naluPresentMaskIntraPicture 
          This parameter controls the insertion of different NALU at I picture
          A bit-field is given for each NALU type as shown below. This field is
\n ---------------------------------------------------------------------\n
\n   7|  6|        5|         4|         3|         2|    1|          0 \n
\n SPS|SEI|IDR_SLICE|SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED \n
\n ---------------------------------------------------------------------\n
\n----------------------------------------------
\n     14|     13|    12|      11|   10|  9|  8|
\n UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|
\n----------------------------------------------
          Set/ reset particular bit to enable/disable that insertion of that 
          NALU (0=disable, 1=enable)
          UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3), 
          SLICE_DP_C(bit-4), IDR_SLICE(bit-5), EOSEQ (bit-10) and 
          EOSTREAM (bit-11) are don't care and assumed to be <b> zero </b>.
  @param  naluPresentMaskNonIntraPicture 
          This parameter controls the insertion of different 
          NALU at NON intra picture
          A bit-field is given for each NALU type as shown below. This field is
\n ---------------------------------------------------------------------\n
\n   7|  6|        5|         4|         3|         2|    1|          0 \n
\n SPS|SEI|IDR_SLICE|SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED \n
\n ---------------------------------------------------------------------\n
\n----------------------------------------------
\n     14|     13|    12|      11|   10|  9|  8|
\n UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|
\n----------------------------------------------
          Set/ reset particular bit to enable/disable that insertion of that 
          NALU (0=disable, 1=enable)
          UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3), 
          SLICE_DP_C(bit-4), IDR_SLICE(bit-5), EOSEQ (bit-10) and 
          EOSTREAM (bit-11) are don't care and assumed to be <b> zero </b>.
  @param  naluPresentMaskEndOfSequence 
          This parameter controls the insertion of different NALU at End of Seq
          A bit-field is given for each NALU type as shown below. This field is
\n ---------------------------------------------------------------------\n
\n   7|  6|        5|         4|         3|         2|    1|          0 \n
\n SPS|SEI|IDR_SLICE|SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED \n
\n ---------------------------------------------------------------------\n
\n----------------------------------------------
\n     14|     13|    12|      11|   10|  9|  8|
\n UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|
\n----------------------------------------------
          Set/ reset particular bit to enable/disable that insertion of that 
          NALU (0=disable, 1=enable)
          UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3), 
          SLICE_DP_C(bit-4), SPS_VUI (bit-13), FILLER (bit-12), AUD(bit-9), 
          PPS(bit-8), SPS(bit-7), SEI(bit-6), IDR_SLICE(bit-5), SLICE (bit-1) 
          are don't care and assumed to be <b> zero </b>.
  
*/

typedef struct IH264ENC_NALUControlParams {
  XDAS_Int16                   naluControlPreset              ; 
  XDAS_Int16                   naluPresentMaskStartOfSequence ;
  XDAS_Int16                   naluPresentMaskIDRPicture      ;
  XDAS_Int16                   naluPresentMaskIntraPicture    ;
  XDAS_Int16                   naluPresentMaskNonIntraPicture ;
  XDAS_Int16                   naluPresentMaskEndOfSequence ;

} IH264ENC_NALUControlParams ;

/**
  
  @struct IH264ENC_SliceCodingParams
  @brief  This structure contains all the parameters which controls Slice 
          encoding

  @param  sliceCodingPreset  
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_SLICECODING_DEFAULT

  @param  sliceMode  : regarded @ IH264ENC_DynamicParams::sliceCodingParams
          This defines the control mechanism to split a picture in slices. 
          It can be either MB based or bytes based

  @param  sliceUnitSize  : regarded @ IH264ENC_DynamicParams::sliceCodingParams  
          The meaning of this parameter depends upon sliceMode. 
          sliceMode == IH264_SLICEMODE_MBUNIT then this 
          parameter informs the number of Macroblocks in one slice
          sliceMode == IH264_SLICEMODE_BYTES then this 
          parameter informs the number of bytes in one slice
          sliceMode == IH264_SLICEMODE_OFFSET then this 
          parameter informs the number of offset information provided by user.
          Actual offset are provided with sliceStartOffset

  @param  sliceStartOffset[IH264ENC_MAX_NUM_SLICE_START_OFFSET]  : regarded @ 
          IH264ENC_DynamicParams::sliceCodingParams row numbering is assumed to
           start from 0. Enteris in this array must have numbers in ascending 
           order. first slice of the picture is always starting from 0th row 
           of the picture so  0th entry is the offset of second slice in picture
          Ex 1 : sliceStartRowNum[0] = 25 , 
                 sliceStartRowNum[1] = 30, sliceStartRowNum[2] = 40 
                 will result into 4 slices starting from row# 0, 25, 30 and 40
          Ex 2 : sliceStartRowNum[0] = 25 , sliceStartRowNum[1] = 70, 
                 sliceStartRowNum[2] = 60  is invalid
          Ex 3 : sliceStartRowNum[0] = 25 , sliceStartRowNum[1] = 50, 
                 sliceStartRowNum[2] = 100 
                 will result into 3 slices starting from row# 0, 25 and 50 
                 {if number of rows in picture < (100 + 1) } 
  

  @param  streamFormat  : ignored @ IH264ENC_DynamicParams::sliceCodingParams  
          Controls the type of stream : byte stream format or NALU format
          refer IH264ENC_StreamFormat for possible values
  
*/

typedef struct IH264ENC_SliceCodingParams {
  XDAS_Int8            sliceCodingPreset     ; 
  XDAS_Int16           sliceMode             ; 
  XDAS_Int32           sliceUnitSize         ;
  XDAS_Int8            sliceStartOffset[IH264ENC_MAX_NUM_SLICE_START_OFFSET] ;
  XDAS_Int8            streamFormat          ;

} IH264ENC_SliceCodingParams ;


/**
  
  @struct IH264ENC_LoopFilterParams
  @brief  This structure contains all the parameters which controls loop 
          filtering operations

  @param  loopfilterPreset  
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_SLICECODING_DEFAULT
  @param  loopfilterDisableIDC
          Controls H.264 loop filter disabling options
  @param  filterOffsetA  
          alpha offset for loop filter [-12, 12] even number
  @param  filterOffsetB 
          beta offset for loop filter [-12, 12] even number

  
*/
typedef struct IH264ENC_LoopFilterParams {
  XDAS_Int8  loopfilterPreset      ; 
  XDAS_Int8  loopfilterDisableIDC  ; 
  XDAS_Int8  filterOffsetA         ; 
  XDAS_Int8  filterOffsetB         ; 

} IH264ENC_LoopFilterParams ;

/**
  
  @struct IH264ENC_FMOCodingParams
  @brief  This structure contains all the parameters which controls FMO behavior 

  @param  fmoCodingPreset  
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_FMOCODING_DEFAULT
  @param  numSliceGroups
          Total Number of slice groups, valid enteries are [0,8]
  @param  sliceGroupMapType  
          For Valid enteries see IH264ENC_SliceGroupMapType
  @param  sliceGroupChangeDirectionFlag 
          Only valid when sliceGroupMapType is equal to 
          IH264_RASTER_SCAN_SLICE_GRP,
          IH264_WIPE_SLICE_GRP or IH264_WIPE_SLICE_GRP. 
          For valid values refer IH264ENC_SliceGroupChangeDirection
  @param  sliceGroupChangeRate 
          Only valid when sliceGroupMapType is equal to 
          IH264_RASTER_SCAN_SLICE_GRP,
          IH264_WIPE_SLICE_GRP or IH264_WIPE_SLICE_GRP
          valid values are : [0, factor of number of Mbs in a row]
  @param  sliceGroupChangeCycle 
          Only valid when sliceGroupMapType is equal to 
          IH264_RASTER_SCAN_SLICE_GRP,
          IH264_WIPE_SLICE_GRP or IH264_WIPE_SLICE_GRP
          Valid values can be 0 to numMbsRowsInPicture, also constrained by 
          sliceGroupChangeRate*sliceGroupChangeCycle < totalMbsInFrameOnly valid 
          when sliceGroupMapType is equal to IH264_RASTER_SCAN_SLICE_GRP. 
          valid values are : [0, factor of number of Mbs in a row]
  @param  sliceGroupParams[IH264ENC_MAXNUMSLCGPS]
          This field is useful in case of sliceGroupMapType equal to either  
          IH264_INTERLEAVED_SLICE_GRP or IH264_FOREGRND_WITH_LEFTOVER_SLICE_GRP
          In both cases it has different meaning:
          In case of IH264_INTERLEAVED_SLICE_GRP:
          The i-th entery in this array is used to specify the number of 
          consecutive  slice group macroblocks to be assigned to the i-th slice 
          group in raster scan order of slice group macroblock units.
          Valid values are 0 to totalMbsInFrame again constrained by sum of 
          all the elements shouldn't exceed totalMbsInFrame
          In case of IH264_FOREGRND_WITH_LEFTOVER_SLICE_GRP:
          First entry in the array specify the start position of foreground 
          region in terms of macroblock number, valid values are 
          [0, totalMbsInFrame-1]
          Second entry in the array specify the end position of foreground 
          region in terms  of macroblock number, valid values are 
          [0, totalMbsInFrame-1] with following constrains:
          endPos > startPos && endPos%mbsInOneRow > startPos%mbsInOneRow

  @todo   Review this structure and see all the fields are sufficient enough

  
*/

typedef struct IH264ENC_FMOCodingParams {
  XDAS_Int8                  fmoCodingPreset                ; 
  XDAS_Int8                  numSliceGroups                 ;
  XDAS_Int8                  sliceGroupMapType              ; 
  XDAS_Int8                  sliceGroupChangeDirectionFlag  ; 
  XDAS_Int8                  sliceGroupChangeRate           ; 
  XDAS_Int16                 sliceGroupChangeCycle          ; 
  XDAS_Int16                 sliceGroupParams[IH264ENC_MAXNUMSLCGPS] ; 
} IH264ENC_FMOCodingParams ;


/**
  
  @struct IH264ENC_VUICodingParams
  @brief  This structure contains all the parameters which controls VUI 
          parameters. Refer Annex E of the H.264 standard for more details 
          of VUI and parameters
  @param  vuiCodingPreset  
          This Preset controls the USER_DEFINED vs DEFAULT mode. if User is 
          not aware about following fields, it should be set as 
          IH264_VUICODING_DEFAULT
  @param aspectRatioInfoPresentFlag 
          This controls the insertion of aspect ratio information in VUI part 
          of bit-stream
      zero : No aspect ratio related information is transmitted
      non-zero : aspect ratio related information is transmitted
  @param aspectRatioIdc
          Encoder inserts aspectRatioIdc as it is in the bit-stream. It is 
          user's responsibility to feed appropriate value of this. 
          Refer Table E-1 of H264 standard  (or enum IH264ENC_AspectRatioIdc) 
          for valid values of this.
          when aspectRatioIdc == IH264ENC_ASPECTRATIO_EXTENDED(255), encoder 
          will look at IVIDENC2_DynamicParams::sampleAspectRatioHeightand 
          IVIDENC2_DynamicParams::sampleAspectRatioWidth and use them as 
          sar_height and sar_width respectively. aspectRatioIdc is left to 
          user to provide correct value.
      <b> if aspectRatioInfoPresentFlag ==0 then encoder ignores 
          this parameter </b>
  @param videoSignalTypePresentFlag
          This controls the insertion of video signal type in VUI part of 
          bit-stream
      zero : No video signal related information is transmitted
      non-zero : video signal related information is transmitted
  @param videoFormat               
          Encoder inserts videoFormat(lower 3 bits) as it is in the bit-stream. 
          It is user's responsibility to feed appropriate value of this. 
          Refer Table E-2 H264 standard (or enum IH264ENC_VideoFormat)
          for valid values of this.
  @param videoFullRangeFlag
         zero: video range is not full{0, 255} ; non-zero: video range is full
  @param timingInfoPresentFlag     
          This controls the insertion of timing info related parameters in 
          VUI part of bit-stream
  @param hrdParamsPresentFlag
          This controls the insertion of HRD parameters in 
          VUI part of bit-stream  
  @param numUnitsInTicks     
          This controls the insertion of numUnitsInTicks parameter in 
          VUI part of bit-stream. 
          Valid values are [1, targetFrameRate]
          If this parameter is set by user then the targetFrameRate 
          has multiplication factor of numUnitInTicks instead of 1000
*/

typedef struct IH264ENC_VUICodingParams {
  XDAS_Int8                  vuiCodingPreset            ; 
  XDAS_UInt8                 aspectRatioInfoPresentFlag ;
  XDAS_UInt8                 aspectRatioIdc             ;
  XDAS_UInt8                 videoSignalTypePresentFlag ;
  XDAS_UInt8                 videoFormat                ;
  XDAS_UInt8                 videoFullRangeFlag         ;
  XDAS_UInt8                 timingInfoPresentFlag      ;
  XDAS_UInt8                 hrdParamsPresentFlag       ;
  XDAS_UInt32                numUnitsInTicks            ;


} IH264ENC_VUICodingParams ;

/**
  
  @struct IH264ENC_StereoInfoParams
  @brief  This structure contains all the parameters which have Stereo  
          Video info for SEI message. 
  @param stereoInfoPreset 
          This Preset controls the Enable/Disable of stereo video coding &
          if its enable then controls the USER_DEFINED vs DEFAULT mode. 
          If User is not aware about following fields, it should be set 
          as IH264_STEREOINFO_ENABLE_DEFAULT.
          0  :Stereo Video Coding is Disabled.
          1  :Default stereo video information parameters .
          2  :User defined steroe video information pamameters.
      @remarks - When stereo video coding is enabled then input content type 
                    (coding type) should be Interlaced coding.
  @param topFieldIsLeftViewFlag
          This indicates the top & bottom field in video coded sequence
          as a left view or right view
    non-zero :top fields in the coded video sequence represent a left view & the
               bottom fields in the coded video sequence represent a right view.
        zero :vice-versa.
  @param viewSelfContainedFlag
          This controls the Left/Right view should Refer/NotRefer to
          Left/Right view.
     zero :Leftview can refer to Rightview or Leftview & Rightview can refer to
           Leftview or Rightview.
           i.e.Possible values for left_view_self_contained_flag = 0 &&
               right_view_self_contained_flag = 0 in  bit-stream.
  non-zero:Leftview cannot refer to Rightview & Rightview cannot refer to 
           Leftview.
           i.e Possible values for left_view_self_contained_flag = 1 &&
           right_view_self_contained_flag = 1 in  bit-stream.
     @remarks - This viewSelfContainedFlag overrides the interlaceCodingType.
          viewSelfContainedFlag == 0 forces interlaceCodingType = ARF 
          viewSelfContainedFlag == 1 forces interlaceCodingType = SPF 
*/
typedef struct IH264ENC_StereoInfoParams {
  XDAS_UInt8         stereoInfoPreset;
  XDAS_UInt8         topFieldIsLeftViewFlag ;
  XDAS_UInt8         viewSelfContainedFlag ;
}IH264ENC_StereoInfoParams ;

/**
  
  @struct IH264ENC_FramePackingSEIParams
  @brief  This structure contains all the parameters for Frame packing
           SEI message. 
  @param framePackingPreset 
          This Preset controls the Enable/Disable of Frame packing
          SEI message encoding.If its enable then controls 
          the USER_DEFINED vs DEFAULT mode. 
          If User is not aware about following fields, it should be set 
          as IH264_FRAMEPACK_SEI_ENABLE_DEFAULT.
          0  :Frame packing SEI is Disabled.
          1  :Default Frame packing SEI parameters .
          2  :User defined Frame packing SEI information pamameters.
      @remarks - When Frame packing SEI coding is enabled then input content
                     type (coding type) should be Progressive coding.
  @param framePackingType
          indicates the type of packing arrangement of the frames as 
          specified standard. Refer IH264ENC_FramePackingType
  @param frame0PositionX
          location of the upper left sample of frame 0 (Left view) in
          horizontal direction. Allowed values are [0,15]. Only lower
          4 bits of this parameter are significant.
  @param frame0PositionY
          location of the upper left sample of frame 0 (Left view) in
          vertical direction. Allowed values are [0,15]. Only lower
          4 bits of this parameter are significant.
  @param frame1PositionX
          location of the upper left sample of frame 1 (Right view) in
          horizontal direction. Allowed values are [0,15]. Only lower
          4 bits of this parameter are significant.
  @param frame1PositionY
          location of the upper left sample of frame 1 (Right view) in
          vertical direction. Allowed values are [0,15]. Only lower
          4 bits of this parameter are significant.
  @param reservedByte
          reserved byte that needs to be encoded as part of SEI message
          "frame_packing_arrangement_reserved_byte"
          User should set it to 0 as current standard (March 2010) allows 
          only 0 of this value. This is kept for future provisions.

*/
typedef struct IH264ENC_FramePackingSEIParams {
  XDAS_UInt8         framePackingPreset;
  XDAS_UInt8         framePackingType ;
  XDAS_UInt8         frame0PositionX ;
  XDAS_UInt8         frame0PositionY ;
  XDAS_UInt8         frame1PositionX ;
  XDAS_UInt8         frame1PositionY ;
  XDAS_UInt8         reservedByte ;
}IH264ENC_FramePackingSEIParams ;

/**
  
  @struct IH264ENC_SVCCodingParams
  @brief  This structure contains all the parameters which controls SVC 
          parameters. Refer Annex G of the H.264 standard for more details 
          of SVC and parameters
          
  @param  svcExtensionFlag
          This parameter configures the codec put SVC extensions in the 
          bit-stream. For normal H.264 operation this Flag needs to be ZERO
          (default value). For Encoder instance to encode SSPS, Prefix-NALU,
           Coded Slice in the bit-stream, this flag needs to be set.
        
      Allowed Values are [0,1,2]
      
      0 - Disables all SVC features/syntaxes and rest of the structure 
          is not read/respected.
      1 - Encodes the required SVC related syntaxes of the layer for 
          which H.264 Codec has been instantiated.
      2 - Encoder the required SVC related syntaxes of the layer for 
          which H.264 Codec has been instantiated 
        Only in this mode, the JSVM error concealment will work on 
        encoded bitstreams as in this mode even Spatial/CGS is also 
        coded the MGS way (i.e. by setting 
        adaptive_xxx_prediction_flag and 
        default_xxxx_prediction_flag to zero).

  @param  dependencyID
          This parameter tell whether the current instance is for Base layer 
          or for enhancement layer and also conveys Layer ID Info. This field 
          is respected only when svcExtensionFlag is set. For configuring the
          encoder instance for BL then this parameter should be ZERO. For 
          configuring the encoder instance for EL, this parameter should hold
          the value of the layer ID. 

  @param  qualityID
          This parameter tells Quality ID of the layer that the current instance
          of encoder is going to encode. 
          This field is respected only when svcExtensionFlag is set. For 
          configuring the encoder instance for BL then this parameter should be 
          ZERO.
          
  @param  enhancementProfileID
          This parameter conveys the enhancement encoder instance like what 
          should be the profile ID to be encoded in the Sub-Sequence Parameter 
          Set (SSPS).This parameter is dont care when, the svcExtensionFlag is 
          not set.Possible values are IH264SVC_BASELINE_PROFILE (83) or 
          IH264SVC_HIGH_PROFILE (86)       
  @param  layerIndex
          This parameter conveys the enhancement encoder instance like what  
          should be the pic_parameter_set_id and seq_parameter_set_id to be  
          encoded in the Picture Parameter Set (PPS) and Sub-Sequence Parameter 
          Set (SSPS). layerIndex is don’t care or treated to be ZERO when  
          svcExtensionFlag is not enabled.
  @param  refLayerDQId
          This parameter conveys the the DQ Id of the ReferenceLayer.

*/

typedef struct IH264ENC_SVCCodingParams {
  XDAS_UInt8                   svcExtensionFlag;
  XDAS_UInt8                   dependencyID;
  XDAS_UInt8                   qualityID;
  XDAS_UInt8                   enhancementProfileID;
  XDAS_UInt8                   layerIndex;
  XDAS_Int8                    refLayerDQId;

} IH264ENC_SVCCodingParams ;

/**<
  
  @struct IH264ENC_Params
  @brief This structure defines the Create time parameters for all 
         H264ENC objects

  @param  videnc2Params        must be followed for all video encoders. 
                               Base class create params
  @param  rateControlParams    Controls all Rate Control related parameters 
  @param  interCodingParams    Controls all Inter coding related parameters 
  @param  intraCodingParams    Controls all Intra coding related parameters 

  @param  nalUnitControlParams Controls the insertion of different NALUs at 
                               different access points in video sequence
  @param  sliceCodingParams    Controls all Slice coding related parameters 
  @param  loopFilterParams     Controls the in-loop filtering process
  @param  fmoCodingParams      Controls the FMO behavior
  @param  vuiCodingParams      Controls the VUI (Video Usability Information) 
                               parameters. Refer Annex E for more details of 
  @param  stereoInfoParams     Controls the Stereo Video Information for SEI
                               NAL Unit.
  @param  framePackingSEIParams This structure contains all the parameters 
                                for Frame packing SEI message.
  @param  svcCodingParams      Controls the SVC coding parameters

  @param  interlaceCodingType  Controls the type of interlaced coding, refer 
                               IH264ENC_InterlaceCodingType for more details
  @param  bottomFieldIntra     This field is valid only for interlaced sequences
          0        = Bottom field of the first I frame in the GOP encoded as 
                     P field.
          non-zero = Bottom field of the first I frame in the GOP encoded as I 
                     field.

  @param  IDRFrameInterval     Interval b/w two IDR frames, unit of this 
                                parameter is intraFrameInterval
  Ex: 0 : Only first I frame as IDR
      1 : All I frames are IDR.
      2 : 1 out of 2 I frames are IDR starting from first I frame
      -ve values are not allowed.

  @param  gopStructure         Defines the gop structure type: 
                               uniform/non-uniform. For more information refer 
                               IH264ENC_GOPStructure
  @param  entropyCodingMode    Controls the entropy coding type, see 
                               IH264ENC_EntropyCodingMode for allowed values
  @param  transformBlockSize   Tranform Block size. Refer 
                               IH264ENC_TransformBlockSize

  @param  log2MaxFNumMinus4    Limits the maximum frame number in the bit-stream
                               to (1<< (log2MaxFNumMinus4 + 4)) Range[0,12]
  @param  picOrderCountType    Picture Order count type Valid values refer 
                               IH264ENC_PicOrderCountType
  @param  enableWatermark      This Parameter Enables or disables Water Mark
                               SEI message in the bit stream
                               0 – Disable, Non-Zero - Enable 
  @param  pConstantMemory
          This pointer points to the the memory area where constants are 
          located. It has to be in DDR addressable space by vDMA. This is 
          use ful to allow relocatable constants for the applications which 
          doesn't use M3 as host. Actual memory controller/allocator
          is on another master processor. If this is set to NULL then 
          encoder assumes that all constants are pointed by symbol 
          H264ENC_TI_ConstData
         

  @param  maxIntraFrameInterval
          This parameter contains the maximum Intra Frame interval. It is used
          to reduce the memory requirement of refernce Buffers. Because for all
          I frame/field configuration the reference frame buffers are not 
          required
          @remarks  For example, this field will be:
         - 0 - Only first frame to be intra
           coded.  e.g. IPPPPPP...
         - 1 - No inter frames (all intra
           frames).
         - 2 - Consecutive IPIPIP... sequence (if
           no B frames).
         - 3 - IPPIPP... or IPBIPBI... and so on.

  @param  debugTraceLevel
          This parameter configures the codec to dump a debug trace log

  @param  lastNFramesToLog
          This parameter configures the codec to maintain a history of last 
          N frames/pictures

  @param  enableAnalyticinfo
          This parameter configures the codec to expose analytic info like
          MVs and SAD parameters
  @param  enableGMVSei
          This Parameter Enable or disable the TI specific GMV SEI message 
          in the bit stream
          0 – Disable, Non-Zero - Enable 

  @param  constraintSetFlags    
          Used to modify the values of constraint set flags that 
          are coded in te bit stream. The syntax of of this 
          flag is as follows
           RESVD|RESVD|RESVD|PRESET|CST_0|CST_1|CST_2|CST_3
          if preset is set to zero then, CST flags are set by the 
          encoder internally. if preset is 1 then encoder takes the 
          preset values given by the user and encodes themin the 
          bit stream. Note that there are no error checks are placed 
          on the user defined values. 
  @param  enableRCDO
          This paramter is used to enable encoding a bit stream compliant to
          Reduced Complexity Decoding Operations (RCDO) profile

  @param  enableLongTermRefFrame
          This paramter is used to enable support of long term reference frame.
          Enabling this bit will instruct encoder to keep the recently marked
          long-term frame in its refernce buffer list. So it increases the DDR
          foot print by one or two frame buffers depends on the LTRPScheme used.

  @param  LTRPPeriod
          This parameter is used to specify the long-term reference frame
          marking interval. This parameter is in use when
          enableLongTermRefFrame = IH264ENC_LTRP_REFERTOP_REACTIVE or
          IH264ENC_LTRP_REFERTO_PERIODICLTRP.
           
  @param  numTemporalLayer
          This parameter controls the temporal Levels in bit-stream.
           1 - Only Base Layer available in bit-stream.
           2 - Maximum Temporal Level 1 in bit-stream
           3 - Maximum Temporal Level 2 in bit-stream 
           4 - Maximum Temporal Level 3 in bit-stream
       @remarks - numTemporalLayer = 0 is not supported & its erroneous case.
    
  @param  referencePicMarking
          This parameter used to control the Reference Picture Marking 
          For any non-zero value means Long-term Picture (MMCO Commands)
            0 - Short-term Picture (Sliding Window)         
            1 - Long-term Picture (  MMCO Commands)
  @param  reservedParams
          Some part is kept reserved to add parameters later without 
          changing the foot print of interface object memory

  @todo  
  More parameters need to be added for Hieririchal frames, 
  error resilience options, SEI/VUI parameter options, Analytic exposure 
  from encoder like MVs and SAD parameters
  
  
*/

typedef struct
{
  IVIDENC2_Params                  videnc2Params      ;
  IH264ENC_RateControlParams       rateControlParams  ; 
  IH264ENC_InterCodingParams       interCodingParams  ; 
  IH264ENC_IntraCodingParams       intraCodingParams  ; 
  IH264ENC_NALUControlParams       nalUnitControlParams; 
  IH264ENC_SliceCodingParams       sliceCodingParams  ; 
  IH264ENC_LoopFilterParams        loopFilterParams   ; 
  IH264ENC_FMOCodingParams         fmoCodingParams    ;
  IH264ENC_VUICodingParams         vuiCodingParams    ;
  IH264ENC_StereoInfoParams        stereoInfoParams  ;
  IH264ENC_FramePackingSEIParams   framePackingSEIParams ;
  IH264ENC_SVCCodingParams         svcCodingParams    ;
  XDAS_Int8                        interlaceCodingType;
  XDAS_Int8                        bottomFieldIntra   ; 
  XDAS_Int8                        gopStructure       ; 
  XDAS_Int8                        entropyCodingMode  ; 
  XDAS_Int8                        transformBlockSize ; 
  XDAS_Int8                        log2MaxFNumMinus4  ; 
  XDAS_Int8                        picOrderCountType  ;
/*   XDAS_Int8                        mbMetaDataEnable ;                      */
  XDAS_Int8                        enableWatermark     ;
  XDAS_Int32                       IDRFrameInterval   ; 
  XDAS_Int32                       pConstantMemory    ;
  XDAS_Int32                       maxIntraFrameInterval  ;
  XDAS_UInt32                      debugTraceLevel;
  XDAS_UInt32                      lastNFramesToLog;
  XDAS_Int8                        enableAnalyticinfo ;
  XDAS_Int8                        enableGMVSei  ;
  XDAS_Int8                        constraintSetFlags;
  XDAS_Int8                        enableRCDO;
  XDAS_Int32                       enableLongTermRefFrame  ;
  XDAS_Int32                       LTRPPeriod;
  XDAS_Int8                        numTemporalLayer  ;
  XDAS_Int8                        referencePicMarking   ;
  XDAS_Int32                       reservedParams[3]  ;
} IH264ENC_Params;


/**<
  
  @struct IH264ENC_Status
  @brief This structure informs back the status of H264 encoder and tells the 
         value of each control parameter 

  @param  videnc2Status        must be followed for all video encoders. 
                               Base class status

  @param  rateControlParams    Controls all Rate Control related parameters 
  @param  interCodingParams    Controls all Inter coding related parameters 
  @param  intraCodingParams    Controls all Intra coding related parameters 

  @param  nalUnitControlParams Controls the insertion of different NALUs at 
                               different access points in video sequence
  @param  sliceCodingParams    Controls all Slice coding related parameters 
  @param  loopFilterParams     Controls the in-loop filtering process
  @param  fmoCodingParams      Controls the FMO behavior
  @param  vuiCodingParams      Controls the VUI (Video Usability Information) 
                               parameters. Refer Annex E for more details 
                               of VUI and parameters
  @param  stereoInfoParams     Controls the Stereo Video Information for SEI
                               NAL Unit.
  @param  framePackingSEIParams This structure contains all the parameters 
                                for Frame packing SEI message.
  @param  svcCodingParams      Controls the SVC behavior
  @param  interlaceCodingType  Controls the type of interlaced coding, refer 
                               IH264ENC_InterlaceCodingType for more details
  @param  bottomFieldIntra     This field is valid only for interlaced sequences
                               0 = Bottom field of the first I frame in the GOP 
                               encoded as P field.
                               non-zero = Bottom field of the first I frame in 
                               the GOP encoded as I field.
  @param  gopStructure         Defines the gop structure type: Open/Close.
                               For more information refer IH264ENC_GOPStructure
  @param  entropyCodingMode    Controls the entropy coding type, see 
                               IH264ENC_EntropyCodingMode for allowed values
  @param  transformBlockSize   Tranform Block size. Refer 
                               IH264ENC_TransformBlockSize

  @param  log2MaxFNumMinus4    Limits the maximum frame number in the bit-stream
                                to (1<< (log2MaxFNumMinus4 + 4)) Range[0,12]
  @param  picOrderCountType    Picture Order count type Valid values refer 
                               IH264ENC_PicOrderCountType
  @param  enableWatermark      This Parameter Enables or disables Water Mark
                               SEI message in the bit stream
                               0 – Disable, Non-Zero - Enable 
  @param  IDRFrameInterval     Interval b/w two IDR frames, it should be and 
                               integer multiple of intraFrameInterval 

  @param  maxIntraFrameInterval
          This parameter contains the maximum Intra Frame interval. It is used
          to reduce the memory requirement of refernce Buffers. Because for all
          I frame/field configuration the reference frame buffers are not 
          required
          @remarks  For example, this field will be:
         - 0 - Only first frame to be intra
           coded.  e.g. IPPPPPP...
         - 1 - No inter frames (all intra
           frames).
         - 2 - Consecutive IPIPIP... sequence (if
           no B frames).
         - 3 - IPPIPP... or IPBIPBI... and so on.

  @param  debugTraceLevel
          This parameter configures the codec to dump a debug trace log

  @param  lastNFramesToLog
          This parameter configures the codec to maintain a history of last 
          N frames/pictures

  @param  enableAnalyticinfo
          This parameter configures the codec to expose analytic info like
          MVs and SAD parameters

  @param  enableGMVSei
          This Parameter Enable or disable the TI specific GMV SEI message 
          in the bit stream
          0 – Disable, Non-Zero - Enable 

  @param  constraintSetFlags    
          Used to modify the values of constraint set flags that 
          are coded in te bit stream. The syntax of of this 
          flag is as follows
           RESVD|RESVD|RESVD|PRESET|CST_0|CST_1|CST_2|CST_3
          if preset is set to zero then, CST flags are set by the 
          encoder internally. if preset is 1 then encoder takes the 
          preset values given by the user and encodes themin the 
          bit stream. Note that there are no error checks are placed 
          on the user defined values. 

  @param  enableRCDO
          This paramter is used to enable encoding a bit stream compliant to
          Reduced Complexity Decoding Operations (RCDO) profile

  @param  enableLongTermRefFrame
          This paramter is used to enable support of long term reference frame.
          Enabling this bit will instruct encoder to keep the recently marked
          long-term frame in its refernce buffer list. So it increases the DDR
          foot print by one or two frame buffers depends on the LTRPScheme used.

  @param  LTRPPeriod
          This parameter is used to specify the long-term reference frame
          marking interval. This parameter is in use when
          enableLongTermRefFrame = IH264ENC_LTRP_REFERTOP_REACTIVE or
          IH264ENC_LTRP_REFERTO_PERIODICLTRP.
                    
  @param  searchCenter         seacrh Center for motion estimation
  @param  enableStaticMBCount  Flag to indicate enable/disable Static MB count
                               support  
  @param  extMemoryDebugTraceAddr  This parameter reports the external
                               memory address (as seen by M3) where debug trace
                               information is being dumped
  @param  extMemoryDebugTraceSize  This parameter reports the external
                               memory buffer size (in bytes) where debug trace
                               information is being dumped
  @param  numTemporalLayer     This parameter controls the temporal Levels in 
                               bit-stream.  
  @param  referencePicMarking  This parameter used to control the Reference
                               Picture Marking.             
  @param  extErrorCode        This parameter carries the sub extended error bits
                              set by encoder. Application/user can look into  
                              these bits to correct his configuration.
*/

typedef struct
{
  IVIDENC2_Status      videnc2Status ;  

  IH264ENC_RateControlParams       rateControlParams    ; 
  IH264ENC_InterCodingParams       interCodingParams    ; 
  IH264ENC_IntraCodingParams       intraCodingParams    ; 
  IH264ENC_NALUControlParams       nalUnitControlParams ; 
  IH264ENC_SliceCodingParams       sliceCodingParams    ; 
  IH264ENC_LoopFilterParams        loopFilterParams     ; 
  IH264ENC_FMOCodingParams         fmoCodingParams      ;
  IH264ENC_VUICodingParams         vuiCodingParams      ;
  IH264ENC_StereoInfoParams        stereoInfoParams  ;
  IH264ENC_FramePackingSEIParams   framePackingSEIParams ;
  IH264ENC_SVCCodingParams         svcCodingParams    ;

  XDAS_Int8                        interlaceCodingType  ;
  XDAS_Int8                        bottomFieldIntra     ; 
  XDAS_Int8                        gopStructure         ; 
  XDAS_Int8                        entropyCodingMode    ; 
  XDAS_Int8                        transformBlockSize   ; 
  XDAS_Int8                        log2MaxFNumMinus4    ; 
  XDAS_Int8                        picOrderCountType    ;
  XDAS_Int8                        enableWatermark      ;
  XDAS_Int32                       IDRFrameInterval     ;  
  XDAS_Int32                       maxIntraFrameInterval  ;
  XDAS_UInt32                      debugTraceLevel;
  XDAS_UInt32                      lastNFramesToLog;
  XDAS_Int8                        enableAnalyticinfo ;
  XDAS_Int8                        enableGMVSei  ;
  XDAS_Int8                        constraintSetFlags;
  XDAS_Int8                        enableRCDO;
  XDAS_Int32                       enableLongTermRefFrame  ;
  XDAS_Int32                       LTRPPeriod  ;
  XDM_Point                        searchCenter         ;
  XDAS_Int8                        enableStaticMBCount ;
  XDAS_UInt32                    * extMemoryDebugTraceAddr;
  XDAS_Int8                        numTemporalLayer  ;
  XDAS_Int8                        referencePicMarking   ;
  XDAS_UInt32                      extMemoryDebugTraceSize;
  XDAS_Int8                        enableROI;
  XDAS_UInt32                      extErrorCode[IH264ENC_EXTERROR_NUM_MAXWORDS];
} IH264ENC_Status;

/**< This structure must be the first field of all H264ENC instance objects */
typedef struct IH264ENC_Obj
{
    struct IH264ENC_Fxns *fxns;
} IH264ENC_Obj;

/**< This handle is used to reference all H264ENC instance objects */
typedef struct IH264ENC_Obj *IH264ENC_Handle;

/**<Default parameter values for H264ENC instance objects */
extern const IH264ENC_Params H264ENC_TI_PARAMS;


/**<
  
  @struct IH264ENC_DynamicParams
  @brief This structure defines the run time parameters for all H264ENC objects
  
  @param  videnc2DynamicParams must be followed for all video encoders 
  @param  rateControlParams    Controls all Rate Control related parameters. 
                               only few are supported to be changed as 
                               part @ Control call. Refer 
                               IH264ENC_RateControlParams to find out 
  @param  interCodingParams    Controls all iner MB coding related parameters. 
                               only few are supported to be changed as 
                               part @ Control call. Refer interCodingParams to 
                               find out  
  @param  sliceCodingParams    Controls all Slice coding related parameters. 
                               only few are supported to be changed as 
                               part @ Control call.
                               Refer sliceCodingParams to find out  
  @param  sliceGroupChangeCycle 
          Only valid when sliceGroupMapType is equal to 
          IH264_RASTER_SCAN_SLICE_GRP,
          IH264_WIPE_SLICE_GRP or IH264_WIPE_SLICE_GRP
          Valid values can be 0 to numMbsRowsInPicture, also constrained by 
          sliceGroupChangeRate*sliceGroupChangeCycle < totalMbsInFrameOnly valid 
          when sliceGroupMapType is equal to IH264_RASTER_SCAN_SLICE_GRP. 
          valid values are : [0, factor of number of Mbs in a row]
  @param  searchCenter         seacrh Center for motion estimation. 
                               XDM_Point.x == 0xFFFF means ignore searchCenter

  @param  enableStaticMBCount  Flag to indicate enable/disable Static MB count
                               support  

  @param  enableROI
          Enable/Disable the ROI algorithm

  @param  reservedDynParams
          Some part is kept reserved to add parameters later without changing 
          the foot print of interface memory
  
*/

typedef struct IH264ENC_DynamicParams {
  IVIDENC2_DynamicParams       videnc2DynamicParams; 
  IH264ENC_RateControlParams   rateControlParams   ; 
  IH264ENC_InterCodingParams   interCodingParams   ; 
  IH264ENC_IntraCodingParams   intraCodingParams   ;
  IH264ENC_SliceCodingParams   sliceCodingParams   ; 
  XDAS_Int32                   sliceGroupChangeCycle  ; 
  XDM_Point                    searchCenter        ;
  XDAS_Int8                    enableStaticMBCount ;
  XDAS_Int32                   enableROI;
  XDAS_Int32                   reservedDynParams[3];
} IH264ENC_DynamicParams;

extern const IH264ENC_DynamicParams H264ENC_TI_DYNAMICPARAMS;

/**< 
  
  @struct IH264ENC_InArgs
  @brief  This structure defines the input argument being passed to 
          H.264 encoder 
  
  @params videnc2InArgs : It is instance of base class. It cntains all 
          the necessary  info required run time parameters for all H264ENC 
          objects
  @param  processId      : processId in InArgs was kept to ease the 
                           implementation of acquire time optimization 
                           in application code. In N channel case, 
                           acquire is happening for last channel and 
                           this (processId ) as argument is passed into
                           acquire call.This will make application to 
                           understand that for which process call, acquire
                           has been made. With this information application 
                           can optimize the time spent in acquire. Like, it
                           might have happened that from last call of acquire, 
                           IVAHd became unavailable to any further process 
                           call(s). In this scenario application will get to
                           know that IVAHD was not given to somebody else from 
                           last process call, and hence it can do some
                           optimization in acquire routine
  @params roiInputParams : Input parameters related to ROI algorithm
  @params inputKey       : This parameter along with the few important 
                           properties of a frame are used to generate the 
                           Encrypted key. If watermarking is enabled then this 
                           Encrypted key would be inserted in the form of user
                           data unregistered SEI message in the encoded stream.
  */
typedef struct IH264ENC_InArgs {

  IVIDENC2_InArgs  videnc2InArgs  ; 
  XDAS_Int32 processId;
  IH264ENC_RoiInput roiInputParams;
  XDAS_UInt32      inputKey       ; 
} IH264ENC_InArgs;


/**<
  
  @struct IH264ENC_MetaDataFormatUserDefinedSEI
  @brief This structure defines the format of meta data used to provide 
         information about user defined SEI

  @param  size size of the payload
  @param  payload buffer
  
*/
typedef struct IH264ENC_MetaDataFormatUserDefinedSEI
{
  XDAS_Int32   size ;
  XDAS_Int8   payload[IH264ENC_MAX_SEI_METADTA_BUFSIZE] ;
}IH264ENC_MetaDataFormatUserDefinedSEI;

/**<
  
  @struct IH264ENC_MetaDataFormatNaluInfo
  @brief This structure defines the format of meta data used to provide 
         information about slice 

  @param  naluSize size of each NAL Unit
  
*/
typedef struct IH264ENC_MetaDataFormatNaluInfo
{
  XDAS_Int32   naluSize ;
}IH264ENC_MetaDataFormatNaluInfo;

/**< 
  
  @struct IH264ENC_OutArgs
  @brief  This structure defines the output argument being generated from H.264
          encoder

  @params videnc2OutArgs : It is instance of base class. It cntains all
          the necessary info encoder should produce
  @params bytesGeneratedBotField: Number of bytes generated for bottom field 
          during the IVIDENC2_Fxns::process() call. This field is updated only
          in case of contentType = Interlaced and both the fields are provided 
          to codec in single process call
  @param  vbvBufferLevel: This varible tells the buffer level at the end of 
          every picture from decoder perspective.the value populated 
          in this variable is latest for every process call
  @param  numStaticMBs: Number of static MBs (defined by H241) in the encoded 
          picture. This field is updated only in case of 
          dynamicParams.enableStaticMBCount is set.
  @param  temporalId:Temporal ID for temporal scalability.Temporal layer Id
          of current frame in H-P encoding(for base layer value is 0).
  @param  control: Encoder control operations. Most of the times it is 
          IVIDENC2_InArgs::control. But there are certain cases when it is
          not same as IVIDENC2_InArgs::control, hence it is advisable to look
          at this output information
          @sa IVIDENC2_Control
          @sa IH264ENC_Control
  @param  extErrorCode : This parameter carries the sub extended error bits
          set by encoder. Application/user can look into these 
          bits to understand encoder's run time failure.
*/
typedef struct IH264ENC_OutArgs {

  IVIDENC2_OutArgs  videnc2OutArgs  ;
  XDAS_Int32 bytesGeneratedBotField ;
  XDAS_Int32 vbvBufferLevel         ;
  XDAS_Int32 numStaticMBs           ;
  XDAS_Int32 temporalId             ;
  XDAS_Int32 control                ;
  XDAS_UInt32 extErrorCode[IH264ENC_EXTERROR_NUM_MAXWORDS];
} IH264ENC_OutArgs;

#define IH264ENC_MAX_LENGTH_PROCESS_LIST (24)

/**<
  @struct IH264ENC_ProcessParams
  @brief  This structure defines the channel specific parameters passed in 
          a process call
  @params handle  : Handle to an algorithm instance
  @params inBufs  : pointer to detailed buffer descriptor for video buffers 
  @params outBufs : pointer to the Buffer descriptors
  @params inArgs  : pointer to the input argument being passed to H.264
                    encoder
  @params outArgs : pointer to the output argument being generated from H.264
                    encoder
  */
typedef struct
{
  IVIDENC2_Handle handle;
  IVIDEO2_BufDesc *inBufs;
  XDM2_BufDesc *outBufs;
  IVIDENC2_InArgs *inArgs;
  IVIDENC2_OutArgs *outArgs;

} IH264ENC_ProcessParams;

/**<

  @struct IH264ENC_ProcessParamsList
  @brief  This structure carries the information of all the channels to be 
          processed .
  @params numEntries        : Number of channels to be encoded in the process 
                              call.
  @params enableErrorCheck  : This parameter controls(enable/disable)
            the check of the non supported features in N channel scenario.
           Note:
           1.Effect of flag is as of now only if (processList->numEntries > 1).
           2.Suggested value for this flag is 0 to have better performance
  @params processParams     : An array holding the process parameters viz.,
             handle,InArgs,outArgs etc of the channel(s) to be processed. 
  
  */

typedef struct
{
  XDAS_Int32 numEntries ;
  XDAS_Int32 enableErrorCheck  ;
  IH264ENC_ProcessParams processParams[IH264ENC_MAX_LENGTH_PROCESS_LIST];
} IH264ENC_ProcessParamsList ;

/**<

  @struct IH264ENC_Fxns
  @brief  This structure defines of the operations on H264ENC objects

    @params IVIDENC2_Fxns : It is instance of base class. It contains all
                            function table
    @params processMulti   : pointer to the Function H264ENC_TI_encodemulti

*/
typedef struct IH264ENC_Fxns
{
    IVIDENC2_Fxns ividenc;
    XDAS_Int32 (*processMulti) (IH264ENC_ProcessParamsList *processList);

} IH264ENC_Fxns;

#ifdef __cplusplus
}
#endif

/*@}*/ /* ingroup HDVICP2H264 */

#endif  /* _IH264ENC_H_  --}                                                  */

/* ========================================================================*/
/* End of file : ih264enc.h                                                */
/*-------------------------------------------------------------------------*/
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ========================================================================*/

