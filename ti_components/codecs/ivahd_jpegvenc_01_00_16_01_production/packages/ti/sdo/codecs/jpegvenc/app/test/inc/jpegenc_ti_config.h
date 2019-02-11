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
* @file      jpegenc_ti_config.h
*
* @brief     Configuration parameters related header file
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
* 
* @version 0.1 (Aug 2010) : Debug Trace support added[Vasudev]
* 
* @version 0.2 (Sep 2010) : tiler.lib support added[Vasudev]
********************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/
#ifndef _JPEGENC_TI_CONFIG_H_
#define _JPEGENC_TI_CONFIG_H_
#define FILE_NAME_SIZE 255
#define VERSION_SIZE          102
#define TESTVECS_FILENAME_SIZE 254
/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
#include "ijpegenc.h"
/* -------------------- system and platform files ----------------------------*/
/*--------------------- program files ----------------------------------------*/


/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
/**
********************************************************************************
*  @struct JpegBPEncConfig_t
*  @brief  This structure contains parameters passed by the user to codec
*          through Config File
*
*  @param  inputFile         : this paramter contains location of Input File
*  @param  outputFile        : this paramter contains location of Output File
*  @param  refFile           : this paramter contains location of Reference File
*  @param  maxHeight         : Maximum Image height in pixels
*  @param  maxWidth          : Maximum Image width  in pixels
*  @param  dataEndianness    : Endianness of output data
*  @param  inputChromaFormat : Chroma format for the input buffer.
*  @param  inputContentType  : Image content type of the buffer being encoded.
*  @param  operatingMode     : Image coding mode of operation.
*  @param  inputDataMode     : Input data mode.
*  @param  outputDataMode    : Output data mode.
*  @param  numInputDataUnits : Number of input slices/rows.
*  @param  numOutputDataUnits: Number of output slices/rows.
*  @param  frameWidth        : Width of Frame in Pixels
*  @param  frameHeight       : Height  of Frame in Pixels
*  @param  qualityFactor     : Specifies the quality setting to use for encoding
*  @param  captureWidth      : Capture width of the image to be encoded
*  @param  captureHeight     : Capture Height of the image to be encoded
*  @param  captureTopLeftx   : captureTopLeftx offset of the image to be encoded
*  @param  captureTopLefty   : captureTopLefty offset of the image to be encoded
*  @param  generateHeader    : Encoder Header only
*  @param  debugTraceLevel   : Level of Debug information needed
*  @param  lastNFramesToLog  : Number of past frames of information needed
*  @param  tilerEnable       : when Tiler lib enable needed
*  @param  chromaTilerMode   : chromaTilerMode  information needed
*  @param  NumFrames         : Num frames of MJPEG encodeing information needed
*  @param  Marker_position   : MJPEG encodeing change marker position
********************************************************************************
*/
typedef struct JpegBPEncConfig_t {
  Int8 inputFile[FILE_NAME_SIZE];
  Int8 outputFile[FILE_NAME_SIZE];
  Int8 refFile[FILE_NAME_SIZE];
  int maxHeight;
  int maxWidth;
  int dataEndianness;
  int inputChromaFormat;
  int inputContentType;
  int operatingMode;
  int inputDataMode;
  int outputDataMode;
  int numInputDataUnits;
  int numOutputDataUnits;
  int frameWidth;
  int frameHeight;
  int qualityFactor;
  int captureWidth;
  int captureHeight;
  int captureTopLeftx;
  int captureTopLefty;
  int generateHeader;
  int debugTraceLevel;
  int lastNFramesToLog;
  int tilerEnable;
  int chromaTilerMode;
  int NumFrames;
  int Marker_position;
  XDAS_UInt32 rateControlPreset;
  XDAS_Int32 targetFrameRate;
  XDAS_Int32 targetBitRate;
  XDAS_Int32 maxBitRate;
  XDAS_Int32 minBitRate;  
  IJPEGVENC_RateControlParams rateControlParams;  
  XDAS_UInt32 enablePrivacyMasking;
  IJPEGVENC_PrivacyMaskingInput pmInputParams;
} JpegBPEncConfig;

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/
#endif /*#ifndef _JPEGENC_TI_CONFIG_H_*/
