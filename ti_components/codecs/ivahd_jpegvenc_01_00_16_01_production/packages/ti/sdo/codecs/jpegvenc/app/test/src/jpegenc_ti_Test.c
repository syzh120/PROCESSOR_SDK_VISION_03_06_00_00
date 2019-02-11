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
* @file      jpegenc_ti_Test.c
*
* @brief     This is the top level client file that drives the JPEG
*            Encoder Call using XDM v1.0 Interface. This is the Application file
*            which user is allowed to change so as to give various kind of 
*            inputs and check the behaviour of the codec.
*            Algorithm Instance creation happens here , once this is done we 
*            call the Resource Manager to assign the resources , then depending
*            on the chroma format we ask for the memory requirement to 
*            GETBUFINFO and then allocate it for input and output and use it 
*            accordingly. Process call happens after these things happened 
*            successfully.
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Feb 2010) : Review & Clean up [vasudev]
*
* @version 0.2 (Aug 2010) : Debug Trace Feature Added[Vasudev]
*
* @version 0.3 (Sep 2010) : Added tiler.lib support[Vasudev]
*
* @version 0.4 (Nov 2010) : Increased the size of luma tiler space passed to 
*                           tiler_init API. Also, modified the datatype of
*                           variable holding the return value of tiler_init 
*                           to XDAS_Int32. [Pavan] 
*
* @version 0.5 (Dec 2010) : Added macros for Netra and OMPA4 Simulators[Naidu]
*
* @version 0.6 (Sep 2012) : Added support for Rate Control and Privacy Masking
*                           [Mahantesh]
* @version 0.7 (June 2014) : Added support for cropping in Tiler memory mode
*                           [Naidu]
*******************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/

/**
*  Set the VDMA View based on the Host Type
*/
#if defined(HOSTARM968_FPGA)
#define VDMAVIEW_EXTMEM      (0x07FFFFFF)
#elif defined(HOSTCORTEXM3_OMAP4) || defined(HOSTCORTEXM3_OMAP4SIMULATOR)
#define VDMAVIEW_EXTMEM      (0xFFFFFFFF) 
#elif defined(HOSTCORTEXM3_NETRA) || defined(HOSTCORTEXM3_NETRASIMULATOR)
#define VDMAVIEW_EXTMEM      (0xFFFFFFFF) 
#elif defined(HOSTCORTEXM3_GAIA)
#define VDMAVIEW_EXTMEM      (0x1FFFFFFF)
#else
#define VDMAVIEW_EXTMEM      (0x07FFFFFF)
#endif
#define SOURCE_PITCH_TILER8   (16*1024)
#define SOURCE_PITCH_TILER16  (32*1024)

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ti/xdais/dm/ividenc2.h>
#include <ti/xdais/xdas.h>

/*--------------------- program files ----------------------------------------*/
#include <jpegenc_ti_Test.h>
#include <jpegenc_ti_rman_config.h>
#include <jpegenc_ti_config.h>
#include <jpegenc_ti.h>
#include <tilerBuf.h>

XDM_DataSyncHandle fGetInpDHandle;
XDM_DataSyncHandle fGetbufferHandle;
XDM_DataSyncHandle fputDataHandle;
XDM_DataSyncDesc   ip_datasyncDesc1;
XDM_DataSyncDesc   ip_datasyncDesc2;
XDM_DataSyncDesc   ip_datasyncDesc3;

XDAS_UInt32 configCount = 0;

/* Global Variable for the Data Sync */
#define NUM_INPUT_BLOCKS (16)

XDAS_UInt8* curr_ddr_addr[NUM_INPUT_BLOCKS];

/*XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS] = {
  1024,4096,2048,1024,3072,1024,1024,1024,7168,10240,12288,25600,1024,
  51200,0x25000,1024,
};*/

XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS] = {
  1024,1024,1024,1024,1024,1024,1024,1024,7168,10240,12288,25600,1024,
  51200,0x25000,1024,
};

XDAS_UInt32 blockPerDataSync[10] = {1,1,1,1,1,1,4,0,0,0};
XDAS_UInt32 GblCount = 0;
XDAS_UInt32 AccCount = 0;

  
/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
extern IRES_HDVICP2_Obj IRES_HDVICP2_handle;
FILE *fin, *fout;
JpegBPEncConfig         gConfig;

/*----------------------------------------------------------------------------*/
/*Array of elements of type sTokenMapping for parsing and holding the tokens  */
/*from the input configuration file.                                          */
/*----------------------------------------------------------------------------*/
static sTokenMapping sTokenMap[MAX_ITEMS_TO_PARSE] =
{
  {"MaxWidth"                      , &gConfig.maxWidth                 , 0 } ,
  {"MaxHeight"                     , &gConfig.maxHeight                , 0 } ,
  {"DataEndianess"                 , &gConfig.dataEndianness           , 0 } ,
  {"InputChromaFormat"             , &gConfig.inputChromaFormat        , 0 } ,
  {"InputContentType"              , &gConfig.inputContentType         , 0 } ,
  {"OperatingMode"                 , &gConfig.operatingMode            , 0 } ,
  {"InputDataMode"                 , &gConfig.inputDataMode            , 0 } ,
  {"OutputDataMode"                , &gConfig.outputDataMode           , 0 } ,
  {"NumInputUnits"                 , &gConfig.numInputDataUnits        , 0 } ,
  {"NumOutputUnits"                , &gConfig.numOutputDataUnits       , 0 } ,
  {"FrameWidth"                    , &gConfig.frameWidth               , 0 } ,
  {"FrameHeight"                   , &gConfig.frameHeight              , 0 } ,
  {"QualityFactor"                 , &gConfig.qualityFactor            , 0 } ,
  {"CaptureWidth"                  , &gConfig.captureWidth             , 0 } ,
  {"captureHeight"                 , &gConfig.captureHeight            , 0 } ,
  {"captureTopLeftx"               , &gConfig.captureTopLeftx          , 0 } ,
  {"captureTopLefty"               , &gConfig.captureTopLefty          , 0 } ,
  {"generateHeader"                , &gConfig.generateHeader           , 0 } ,
  {"debugTraceLevel"               , &gConfig.debugTraceLevel          , 0 } ,
  {"lastNFramesToLog"              , &gConfig.lastNFramesToLog         , 0 } ,
  {"tilerEnable"                   , &gConfig.tilerEnable              , 0 } ,
  {"chromaTilerMode"               , &gConfig.chromaTilerMode          , 0 } ,
  {"NumFrames"                     , &gConfig.NumFrames                , 0 } , 
  {"Marker_position"               , &gConfig.Marker_position          , 0 } ,  

  
  {"RateControlPreset"            , &gConfig.rateControlPreset,2} ,  
  {"targetFrameRate"              , &gConfig.targetFrameRate,0} ,
  {"targetBitRate"                , &gConfig.targetBitRate,0} ,
  {"rateControlParamPreset" 
                         ,&gConfig.rateControlParams.rateControlParamsPreset,2},
  {"maxBitRate"                ,&gConfig.maxBitRate,0} , 
  {"minBitRate"                ,&gConfig.minBitRate,0} , 
  {"rcAlgo"                    ,&gConfig.rateControlParams.rcAlgo,2} , 
  {"qpMaxI"                    ,&gConfig.rateControlParams.qpMaxI,2} , 
  {"qpMinI"                    ,&gConfig.rateControlParams.qpMinI,2} , 
  {"qpI"                       , &gConfig.rateControlParams.qpI    , 2 } ,                 
  {"initialBufferLevel"
                 , &gConfig.rateControlParams.initialBufferLevel   , 0 } ,
  {"HRDBufferSize" 
                     , &gConfig.rateControlParams.HRDBufferSize    , 0 } ,
  {"discardSavedBits", &gConfig.rateControlParams.discardSavedBits, 2 }  ,  
  /*--------------------------------------------------------------------------*/
  /*                                  PM related parameters                  */
  /*--------------------------------------------------------------------------*/
  {"enablePrivacyMasking",&gConfig.enablePrivacyMasking,0},
                          
  {"noOfPrivacyMaskRegions", &gConfig.pmInputParams.noOfPrivacyMaskRegions,0},

  {"lumaValueForPM", &gConfig.pmInputParams.lumaValueForPM, 0},

  {"cbValueForPM", &gConfig.pmInputParams.cbValueForPM, 0},

  {"crValueForPM", &gConfig.pmInputParams.crValueForPM, 0},    

  /*--------------------------------------------------------------------------*/
  /*                                  PM  1                                  */
  /*--------------------------------------------------------------------------*/
  {"PM_1_Xmin",&gConfig.pmInputParams.listPM[0].topLeft.x,
                        sizeof(gConfig.pmInputParams.listPM[0].topLeft.x)},
  {"PM_1_Ymin",&gConfig.pmInputParams.listPM[0].topLeft.y,
                        sizeof(gConfig.pmInputParams.listPM[0].topLeft.y)},
  {"PM_1_Xmax",
                            &gConfig.pmInputParams.listPM[0].bottomRight.x,
                    sizeof(gConfig.pmInputParams.listPM[0].bottomRight.x)},
  {"PM_1_Ymax",
                            &gConfig.pmInputParams.listPM[0].bottomRight.y,
                    sizeof(gConfig.pmInputParams.listPM[0].bottomRight.y)},

  /*--------------------------------------------------------------------------*/
  /*                                  PM  2                                  */
  /*--------------------------------------------------------------------------*/
  {"PM_2_Xmin",&gConfig.pmInputParams.listPM[1].topLeft.x,
                        sizeof(gConfig.pmInputParams.listPM[1].topLeft.x)},
  {"PM_2_Ymin",&gConfig.pmInputParams.listPM[1].topLeft.y,
                        sizeof(gConfig.pmInputParams.listPM[1].topLeft.y)},
  {"PM_2_Xmax",
                           &gConfig.pmInputParams.listPM[1].bottomRight.x,
                    sizeof(gConfig.pmInputParams.listPM[1].bottomRight.x)},
  {"PM_2_Ymax",
                            &gConfig.pmInputParams.listPM[1].bottomRight.y,
                    sizeof(gConfig.pmInputParams.listPM[1].bottomRight.y)},
                                     
  /*--------------------------------------------------------------------------*/
  /*                                  PM  3                                  */
  /*--------------------------------------------------------------------------*/
  {"PM_3_Xmin",&gConfig.pmInputParams.listPM[2].topLeft.x,
                        sizeof(gConfig.pmInputParams.listPM[2].topLeft.x)},
  {"PM_3_Ymin",&gConfig.pmInputParams.listPM[2].topLeft.y,
                        sizeof(gConfig.pmInputParams.listPM[2].topLeft.y)},
  {"PM_3_Xmax",
                            &gConfig.pmInputParams.listPM[2].bottomRight.x,
                    sizeof(gConfig.pmInputParams.listPM[2].bottomRight.x)},
  {"PM_3_Ymax",
                            &gConfig.pmInputParams.listPM[2].bottomRight.y, 
                    sizeof(gConfig.pmInputParams.listPM[2].bottomRight.y)},

  /*--------------------------------------------------------------------------*/
  /*                                  PM  4                                  */
  /*--------------------------------------------------------------------------*/
  {"PM_4_Xmin",&gConfig.pmInputParams.listPM[3].topLeft.x,
                        sizeof(gConfig.pmInputParams.listPM[3].topLeft.x)},
  {"PM_4_Ymin",&gConfig.pmInputParams.listPM[3].topLeft.y,
                        sizeof(gConfig.pmInputParams.listPM[3].topLeft.y)},
  {"PM_4_Xmax",
                            &gConfig.pmInputParams.listPM[3].bottomRight.x,
                    sizeof(gConfig.pmInputParams.listPM[3].bottomRight.x)},
  {"PM_4_Ymax",
                            &gConfig.pmInputParams.listPM[3].bottomRight.y,
                    sizeof(gConfig.pmInputParams.listPM[3].bottomRight.y)},

/*--------------------------------------------------------------------------*/
/*                                  PM  5                                  */
/*--------------------------------------------------------------------------*/
{"PM_5_Xmin",&gConfig.pmInputParams.listPM[4].topLeft.x,
                        sizeof(gConfig.pmInputParams.listPM[4].topLeft.x)},
{"PM_5_Ymin",&gConfig.pmInputParams.listPM[4].topLeft.y,
                        sizeof(gConfig.pmInputParams.listPM[4].topLeft.y)},
{"PM_5_Xmax",&gConfig.pmInputParams.listPM[4].bottomRight.x,
                    sizeof(gConfig.pmInputParams.listPM[4].bottomRight.x)},
{"PM_5_Ymax",&gConfig.pmInputParams.listPM[4].bottomRight.y,
                    sizeof(gConfig.pmInputParams.listPM[4].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  6                                    */
/*----------------------------------------------------------------------------*/
{"PM_6_Xmin",&gConfig.pmInputParams.listPM[5].topLeft.x,
                        sizeof(gConfig.pmInputParams.listPM[5].topLeft.x)},
{"PM_6_Ymin",&gConfig.pmInputParams.listPM[5].topLeft.y,
                        sizeof(gConfig.pmInputParams.listPM[5].topLeft.y)},
{"PM_6_Xmax",&gConfig.pmInputParams.listPM[5].bottomRight.x,
                    sizeof(gConfig.pmInputParams.listPM[5].bottomRight.x)},
{"PM_6_Ymax",&gConfig.pmInputParams.listPM[5].bottomRight.y,
                    sizeof(gConfig.pmInputParams.listPM[5].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  7                                    */
/*----------------------------------------------------------------------------*/
{"PM_7_Xmin",&gConfig.pmInputParams.listPM[6].topLeft.x,
                        sizeof(gConfig.pmInputParams.listPM[6].topLeft.x)},
{"PM_7_Ymin",&gConfig.pmInputParams.listPM[6].topLeft.y,
                        sizeof(gConfig.pmInputParams.listPM[6].topLeft.y)},
{"PM_7_Xmax",&gConfig.pmInputParams.listPM[6].bottomRight.x,
                    sizeof(gConfig.pmInputParams.listPM[6].bottomRight.x)},
{"PM_7_Ymax",&gConfig.pmInputParams.listPM[6].bottomRight.y,
                    sizeof(gConfig.pmInputParams.listPM[6].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  8                                    */
/*----------------------------------------------------------------------------*/
{"PM_8_Xmin",&gConfig.pmInputParams.listPM[7].topLeft.x,
                       sizeof(gConfig.pmInputParams.listPM[7].topLeft.x)},
{"PM_8_Ymin",&gConfig.pmInputParams.listPM[7].topLeft.y,
                       sizeof(gConfig.pmInputParams.listPM[7].topLeft.y)},
{"PM_8_Xmax",&gConfig.pmInputParams.listPM[7].bottomRight.x,
                   sizeof(gConfig.pmInputParams.listPM[7].bottomRight.x)},
{"PM_8_Ymax",&gConfig.pmInputParams.listPM[7].bottomRight.y,
                   sizeof(gConfig.pmInputParams.listPM[7].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  9                                    */
/*----------------------------------------------------------------------------*/
{"PM_9_Xmin",&gConfig.pmInputParams.listPM[8].topLeft.x,
                       sizeof(gConfig.pmInputParams.listPM[8].topLeft.x)},
{"PM_9_Ymin",&gConfig.pmInputParams.listPM[8].topLeft.y,
                       sizeof(gConfig.pmInputParams.listPM[8].topLeft.y)},
{"PM_9_Xmax",&gConfig.pmInputParams.listPM[8].bottomRight.x,
                   sizeof(gConfig.pmInputParams.listPM[8].bottomRight.x)},
{"PM_9_Ymax",&gConfig.pmInputParams.listPM[8].bottomRight.y,
                   sizeof(gConfig.pmInputParams.listPM[8].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  10                                    */
/*----------------------------------------------------------------------------*/
{"PM_10_Xmin",&gConfig.pmInputParams.listPM[9].topLeft.x,
                       sizeof(gConfig.pmInputParams.listPM[9].topLeft.x)},
{"PM_10_Ymin",&gConfig.pmInputParams.listPM[9].topLeft.y,
                       sizeof(gConfig.pmInputParams.listPM[9].topLeft.y)},
{"PM_10_Xmax",&gConfig.pmInputParams.listPM[9].bottomRight.x,
                   sizeof(gConfig.pmInputParams.listPM[9].bottomRight.x)},
{"PM_10_Ymax",&gConfig.pmInputParams.listPM[9].bottomRight.y,
                   sizeof(gConfig.pmInputParams.listPM[9].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  11                                   */
/*----------------------------------------------------------------------------*/
{"PM_11_Xmin",&gConfig.pmInputParams.listPM[10].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[10].topLeft.x)},
{"PM_11_Ymin",&gConfig.pmInputParams.listPM[10].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[10].topLeft.y)},
{"PM_11_Xmax",
                           &gConfig.pmInputParams.listPM[10].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[10].bottomRight.x)},
{"PM_11_Ymax",
                           &gConfig.pmInputParams.listPM[10].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[10].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  12                                   */
/*----------------------------------------------------------------------------*/
{"PM_12_Xmin",&gConfig.pmInputParams.listPM[11].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[11].topLeft.x)},
{"PM_12_Ymin",&gConfig.pmInputParams.listPM[11].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[11].topLeft.y)},
{"PM_12_Xmax",
                          &gConfig.pmInputParams.listPM[11].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[11].bottomRight.x)},
{"PM_12_Ymax",
                         &gConfig.pmInputParams.listPM[11].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[11].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  13                                   */
/*----------------------------------------------------------------------------*/
{"PM_13_Xmin",&gConfig.pmInputParams.listPM[12].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[12].topLeft.x)},
{"PM_13_Ymin",&gConfig.pmInputParams.listPM[12].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[12].topLeft.y)},
{"PM_13_Xmax",
                          &gConfig.pmInputParams.listPM[12].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[12].bottomRight.x)},
{"PM_13_Ymax",
                          &gConfig.pmInputParams.listPM[12].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[12].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  14                                   */
/*----------------------------------------------------------------------------*/
{"PM_14_Xmin",&gConfig.pmInputParams.listPM[13].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[13].topLeft.x)},
{"PM_14_Ymin",&gConfig.pmInputParams.listPM[13].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[13].topLeft.y)},
{"PM_14_Xmax",
                          &gConfig.pmInputParams.listPM[13].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[13].bottomRight.x)},
{"PM_14_Ymax",
                          &gConfig.pmInputParams.listPM[13].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[13].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  14                                   */
/*----------------------------------------------------------------------------*/
{"PM_15_Xmin",&gConfig.pmInputParams.listPM[14].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[14].topLeft.x)},
{"PM_15_Ymin",&gConfig.pmInputParams.listPM[14].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[14].topLeft.y)},
{"PM_15_Xmax",
                          &gConfig.pmInputParams.listPM[14].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[14].bottomRight.x)},
{"PM_15_Ymax",
                          &gConfig.pmInputParams.listPM[14].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[14].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  15                                   */
/*----------------------------------------------------------------------------*/
{"PM_16_Xmin",&gConfig.pmInputParams.listPM[15].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[15].topLeft.x)},
{"PM_16_Ymin",&gConfig.pmInputParams.listPM[15].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[15].topLeft.y)},
{"PM_16_Xmax",
                          &gConfig.pmInputParams.listPM[15].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[15].bottomRight.x)},
{"PM_16_Ymax",
                          &gConfig.pmInputParams.listPM[15].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[15].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  16                                   */
/*----------------------------------------------------------------------------*/
{"PM_17_Xmin",&gConfig.pmInputParams.listPM[16].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[16].topLeft.x)},
{"PM_17_Ymin",&gConfig.pmInputParams.listPM[16].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[16].topLeft.y)},
{"PM_17_Xmax",
                          &gConfig.pmInputParams.listPM[16].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[16].bottomRight.x)},
{"PM_17_Ymax",
                         &gConfig.pmInputParams.listPM[16].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[16].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  17                                   */
/*----------------------------------------------------------------------------*/
{"PM_18_Xmin",&gConfig.pmInputParams.listPM[17].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[17].topLeft.x)},
{"PM_18_Ymin",&gConfig.pmInputParams.listPM[17].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[17].topLeft.y)},
{"PM_18_Xmax",
                          &gConfig.pmInputParams.listPM[17].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[17].bottomRight.x)},
{"PM_18_Ymax",
                          &gConfig.pmInputParams.listPM[17].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[17].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  18                                   */
/*----------------------------------------------------------------------------*/
{"PM_19_Xmin",&gConfig.pmInputParams.listPM[18].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[18].topLeft.x)},
{"PM_19_Ymin",&gConfig.pmInputParams.listPM[18].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[18].topLeft.y)},
{"PM_19_Xmax",
                    &gConfig.pmInputParams.listPM[18].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[18].bottomRight.x)},
{"PM_19_Ymax",
                         &gConfig.pmInputParams.listPM[18].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[18].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  19                                   */
/*----------------------------------------------------------------------------*/
{"PM_20_Xmin",&gConfig.pmInputParams.listPM[19].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[19].topLeft.x)},
{"PM_20_Ymin",&gConfig.pmInputParams.listPM[19].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[19].topLeft.y)},
{"PM_20_Xmax",
                          &gConfig.pmInputParams.listPM[19].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[19].bottomRight.x)},
{"PM_20_Ymax",
                          &gConfig.pmInputParams.listPM[19].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[19].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  20                                   */
/*----------------------------------------------------------------------------*/
{"PM_21_Xmin",&gConfig.pmInputParams.listPM[20].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[20].topLeft.x)},
{"PM_21_Ymin",&gConfig.pmInputParams.listPM[20].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[20].topLeft.y)},
{"PM_21_Xmax",
                   &gConfig.pmInputParams.listPM[20].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[20].bottomRight.x)},
{"PM_21_Ymax",
                   &gConfig.pmInputParams.listPM[20].bottomRight.y,
            sizeof(gConfig.pmInputParams.listPM[20].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  21                                   */
/*----------------------------------------------------------------------------*/
{"PM_22_Xmin",&gConfig.pmInputParams.listPM[21].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[21].topLeft.x)},
{"PM_22_Ymin",&gConfig.pmInputParams.listPM[21].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[21].topLeft.y)},
{"PM_22_Xmax",
                    &gConfig.pmInputParams.listPM[21].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[21].bottomRight.x)},
{"PM_22_Ymax",
                         &gConfig.pmInputParams.listPM[21].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[21].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  22                                   */
/*----------------------------------------------------------------------------*/
{"PM_23_Xmin",&gConfig.pmInputParams.listPM[22].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[22].topLeft.x)},
{"PM_23_Ymin",&gConfig.pmInputParams.listPM[22].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[22].topLeft.y)},
{"PM_23_Xmax",
                    &gConfig.pmInputParams.listPM[22].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[22].bottomRight.x)},
{"PM_23_Ymax",
                         &gConfig.pmInputParams.listPM[22].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[22].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  23                                   */
/*----------------------------------------------------------------------------*/
{"PM_24_Xmin",&gConfig.pmInputParams.listPM[23].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[23].topLeft.x)},
{"PM_24_Ymin",&gConfig.pmInputParams.listPM[23].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[23].topLeft.y)},
{"PM_24_Xmax",
                    &gConfig.pmInputParams.listPM[23].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[23].bottomRight.x)},
{"PM_24_Ymax",
                         &gConfig.pmInputParams.listPM[23].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[23].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  24                                   */
/*----------------------------------------------------------------------------*/
{"PM_25_Xmin",&gConfig.pmInputParams.listPM[24].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[24].topLeft.x)},
{"PM_25_Ymin",&gConfig.pmInputParams.listPM[24].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[24].topLeft.y)},
{"PM_25_Xmax",
                    &gConfig.pmInputParams.listPM[24].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[24].bottomRight.x)},
{"PM_25_Ymax",
                          &gConfig.pmInputParams.listPM[24].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[24].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  25                                   */
/*----------------------------------------------------------------------------*/
{"PM_26_Xmin",&gConfig.pmInputParams.listPM[25].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[25].topLeft.x)},
{"PM_26_Ymin",&gConfig.pmInputParams.listPM[25].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[25].topLeft.y)},
{"PM_26_Xmax",
                    &gConfig.pmInputParams.listPM[25].bottomRight.x,
            sizeof(gConfig.pmInputParams.listPM[25].bottomRight.x)},
{"PM_26_Ymax",
                          &gConfig.pmInputParams.listPM[25].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[25].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  26                                   */
/*----------------------------------------------------------------------------*/
{"PM_27_Xmin",&gConfig.pmInputParams.listPM[26].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[26].topLeft.x)},
{"PM_27_Ymin",&gConfig.pmInputParams.listPM[26].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[26].topLeft.y)},
{"PM_27_Xmax",
                          &gConfig.pmInputParams.listPM[26].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[26].bottomRight.x)},
{"PM_27_Ymax",
                          &gConfig.pmInputParams.listPM[26].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[26].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  27                                   */
/*----------------------------------------------------------------------------*/
{"PM_28_Xmin",&gConfig.pmInputParams.listPM[27].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[27].topLeft.x)},
{"PM_28_Ymin",&gConfig.pmInputParams.listPM[27].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[27].topLeft.y)},
{"PM_28_Xmax",
                          &gConfig.pmInputParams.listPM[27].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[27].bottomRight.x)},
{"PM_28_Ymax",
                          &gConfig.pmInputParams.listPM[27].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[27].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  28                                   */
/*----------------------------------------------------------------------------*/
{"PM_29_Xmin",&gConfig.pmInputParams.listPM[28].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[28].topLeft.x)},
{"PM_29_Ymin",&gConfig.pmInputParams.listPM[28].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[28].topLeft.y)},
{"PM_29_Xmax", 
                          &gConfig.pmInputParams.listPM[28].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[28].bottomRight.x)},
{"PM_29_Ymax",
                          &gConfig.pmInputParams.listPM[28].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[28].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  29                                   */
/*----------------------------------------------------------------------------*/
{"PM_30_Xmin",&gConfig.pmInputParams.listPM[29].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[29].topLeft.x)},
{"PM_30_Ymin",&gConfig.pmInputParams.listPM[29].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[29].topLeft.y)},
{"PM_30_Xmax",
                          &gConfig.pmInputParams.listPM[29].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[29].bottomRight.x)},
{"PM_30_Ymax",
                          &gConfig.pmInputParams.listPM[29].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[29].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  30                                   */
/*----------------------------------------------------------------------------*/
{"PM_31_Xmin",&gConfig.pmInputParams.listPM[30].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[30].topLeft.x)},
{"PM_31_Ymin",&gConfig.pmInputParams.listPM[30].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[30].topLeft.y)},
{"PM_31_Xmax",
                         &gConfig.pmInputParams.listPM[30].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[30].bottomRight.x)},
{"PM_31_Ymax",
                          &gConfig.pmInputParams.listPM[30].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[30].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  31                                   */
/*----------------------------------------------------------------------------*/
{"PM_32_Xmin",&gConfig.pmInputParams.listPM[31].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[31].topLeft.x)},
{"PM_32_Ymin",&gConfig.pmInputParams.listPM[31].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[31].topLeft.y)},
{"PM_32_Xmax",
                          &gConfig.pmInputParams.listPM[31].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[31].bottomRight.x)},
{"PM_32_Ymax",
                          &gConfig.pmInputParams.listPM[31].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[31].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  32                                   */
/*----------------------------------------------------------------------------*/
{"PM_33_Xmin",&gConfig.pmInputParams.listPM[32].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[32].topLeft.x)},
{"PM_33_Ymin",&gConfig.pmInputParams.listPM[32].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[32].topLeft.y)},
{"PM_33_Xmax",
                          &gConfig.pmInputParams.listPM[32].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[32].bottomRight.x)},
{"PM_33_Ymax",
                          &gConfig.pmInputParams.listPM[32].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[32].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  33                                   */
/*----------------------------------------------------------------------------*/
{"PM_34_Xmin",&gConfig.pmInputParams.listPM[33].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[33].topLeft.x)},
{"PM_34_Ymin",&gConfig.pmInputParams.listPM[33].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[33].topLeft.y)},
{"PM_34_Xmax",
                          &gConfig.pmInputParams.listPM[33].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[33].bottomRight.x)},
{"PM_34_Ymax",
                          &gConfig.pmInputParams.listPM[33].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[33].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  34                                   */
/*----------------------------------------------------------------------------*/
{"PM_35_Xmin",&gConfig.pmInputParams.listPM[34].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[34].topLeft.x)},
{"PM_35_Ymin",&gConfig.pmInputParams.listPM[34].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[34].topLeft.y)},
{"PM_35_Xmax",
                         &gConfig.pmInputParams.listPM[34].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[34].bottomRight.x)},
{"PM_35_Ymax",
                          &gConfig.pmInputParams.listPM[34].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[34].bottomRight.y)},

/*----------------------------------------------------------------------------*/
/*                                  PM  35                                   */
/*----------------------------------------------------------------------------*/
{"PM_36_Xmin",&gConfig.pmInputParams.listPM[35].topLeft.x,
                      sizeof(gConfig.pmInputParams.listPM[35].topLeft.x)},
{"PM_36_Ymin",&gConfig.pmInputParams.listPM[35].topLeft.y,
                      sizeof(gConfig.pmInputParams.listPM[35].topLeft.y)},
{"PM_36_Xmax",
                          &gConfig.pmInputParams.listPM[35].bottomRight.x,
                  sizeof(gConfig.pmInputParams.listPM[35].bottomRight.x)},
{"PM_36_Ymax",
                          &gConfig.pmInputParams.listPM[35].bottomRight.y,
                  sizeof(gConfig.pmInputParams.listPM[35].bottomRight.y)},

  /*--------------------------------------------------------------------------*/
  /* ALWAYS the last element in the map                                       */
  /*--------------------------------------------------------------------------*/
  {"\0"                            , NULL                               , 0}
};

/*----------------------------------------------------------------------------*/
/*  Global flag for non-blocking call.                                        */
/*----------------------------------------------------------------------------*/
volatile XDAS_Int32      unServMesgCount;
volatile XDAS_Int32      ServMesgCount;

char    GlobalMemory[MAX_IO_MEMORY];
sTilerParams             tilerParams;
char    flag = 1;
unsigned int initial_size;
FILE* ftestFile;

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/
/**
********************************************************************************
*  @fn          main(int argc, char *argv[])
*
*  @brief       Sample main program implementation which uses xDM v1.0 JPEG
*               encoder's APIs to create a encoder instance and encode multiple
*               input files. 
*               
*               Uses buffer manager for XDM v1.0 compatible buffer management 
*               and uses utility functions for reading raw data,
*               Seperating CbCr components,
*               Comparing output data with reference data &
*               Dumping raw jpeg encoded data into a file in binary format.
*
*  @param [in]  argc  :  Number of arguments
*
*  @param [in]  argv  :  Arguments
*
*  @return      XDM_EOK     : If successfully decoded all input streams/files
*               XDM_EFAIL   : If encountered error in decoding the given set of
*                             input files.
********************************************************************************
*/
int main(int argc, char *argv[])
{
  /*--------------------------------------------------------------------------*/
  /*  File I/O variables                                                      */
  /*--------------------------------------------------------------------------*/
  FILE         *fConfigFile, *finFile, *fpmInputFile;
  FILE         *fTestVecsFile;
  char         inFile[FILE_NAME_SIZE];
  char         testFile[FILE_NAME_SIZE];
  char         configFile[FILE_NAME_SIZE], testCompliance;
  char         testvecsFile[FILE_NAME_SIZE];
  char         line[FILE_NAME_SIZE];
  char         sVersion[VERSION_SIZE];
  char         pmInputFile[FILE_NAME_SIZE];
  char         *pIoBuffer = GlobalMemory;
  XDAS_UInt32 bytesFor30Frames = 0;
  /*--------------------------------------------------------------------------*/
  /*  Base Class Structures for status, input and output arguments.           */
  /*--------------------------------------------------------------------------*/
  JPEGVENC_Params            params;
  JPEGVENC_DynamicParams     dynamicParams; 
  JPEGVENC_InArgs            inArgs;
  JPEGVENC_OutArgs           outArgs;
  JPEGVENC_Status            status;

  /*--------------------------------------------------------------------------*/
  /*  Declaring Algorithm specific handle                                     */
  /*--------------------------------------------------------------------------*/
  JPEGVENC_Handle            handle;

  /*--------------------------------------------------------------------------*/
  /*  Input/Output Buffer Descriptors                                         */
  /*--------------------------------------------------------------------------*/
  IVIDEO2_BufDesc           inputBufDesc;
  XDM2_BufDesc              outputBufDesc;

  /*--------------------------------------------------------------------------*/
  /*  Other local variables                                                   */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32 retValue, extWidth, extHeight, numFramesEncoded = 0;
  XDAS_Int32 compareTestVal;
  XDAS_Int32 frmNumEncoded = 0;
  XDAS_UInt32 loopCount    = 0;
  XDAS_UInt32 offsetAdd    = 0;
  XDAS_UInt32 count        = 0;
  char  *outputAdd;
  /*--------------------------------------------------------------------------*/
  /*  Get the path of config file                                             */
  /*--------------------------------------------------------------------------*/
  strcpy(testvecsFile, 
  "..\\..\\..\\test\\testvecs\\config\\encoder_testvecs.cfg");
  
  /*--------------------------------------------------------------------------*/
  /*  Open Test Vectors File                                                  */
  /*--------------------------------------------------------------------------*/
  fTestVecsFile = fopen(testvecsFile,"r");

  /*--------------------------------------------------------------------------*/
  /*  Perform file open error check.                                          */
  /*--------------------------------------------------------------------------*/
  if (!fTestVecsFile)
  {
    printf("Couldn't open Parameter Config file %s.\n",testvecsFile);
    return XDM_EFAIL;
  }

  /*--------------------------------------------------------------------------*/
  /* Read Test Vectors parameter File until it reaches the end of file        */
  /*--------------------------------------------------------------------------*/
  while(!feof(fTestVecsFile))
  {
    AccCount = 0;
    GblCount = 0;
    numFramesEncoded = 0;
    
    /*------------------------------------------------------------------------*/
    /* Read Compliance Checking parameter                                     */
    /* when set, the frame output is compared with the reference output       */
    /*------------------------------------------------------------------------*/
    if(fgets(line,FILE_NAME_SIZE,fTestVecsFile))
    {
      sscanf(line,"%d",&testCompliance);
    }
    else
    {
      break ;
    }
    
    /*------------------------------------------------------------------------*/
    /* Read Parameters file name                                              */
    /*------------------------------------------------------------------------*/
    if(fgets(line,FILE_NAME_SIZE,fTestVecsFile))
    {
      sscanf(line,"%s",configFile);
    }
    else
    {
      break ;
    }
    
    /*------------------------------------------------------------------------*/
    /* Read Input file name                                                   */
    /*------------------------------------------------------------------------*/
    if(fgets(line,FILE_NAME_SIZE,fTestVecsFile))
    {
      sscanf(line,"%s",inFile);
    }
    else
    {
      break ;
    }

    /*------------------------------------------------------------------------*/
    /* Read Output file name                                                  */
    /*------------------------------------------------------------------------*/
    if(fgets(line,TESTVECS_FILENAME_SIZE,fTestVecsFile))
    {
      sscanf(line,"%s",testFile);
    }
    else
    {
      break ;
    }

    /*------------------------------------------------------------------------*/
    /*  Open Test Config File                                                 */
    /*------------------------------------------------------------------------*/
    fConfigFile = fopen(configFile,"r");
    
    /*------------------------------------------------------------------------*/
    /*  Perform file open error check.                                        */
    /*------------------------------------------------------------------------*/
    if (!fConfigFile)
    {
      printf("Couldn't open Parameter Config file %s.\n",configFile);
      return XDM_EFAIL;
    }

    /*------------------------------------------------------------------------*/
    /* Read Test Config Parameter File                                        */
    /*------------------------------------------------------------------------*/
    if(readparamfile(fConfigFile) != 0)
    {
      printf("Unable to read Config Parameter File %s\n", configFile);
      return(XDM_EFAIL);
    }
    
    /*------------------------------------------------------------------------*/
    /* Close Config Parameter File.                                           */
    /*------------------------------------------------------------------------*/
    fclose(fConfigFile);

    fprintf(stdout, "Testing: %s\n", inFile);
    
    /*------------------------------------------------------------------------*/
    /*  Setting the sizes of Base Class Objects                               */
    /*------------------------------------------------------------------------*/
    status.videnc2Status.size       = sizeof(IVIDENC2_Status);
    inArgs.videnc2InArgs.size       = sizeof(IVIDENC2_InArgs);
    outArgs.videnc2OutArgs.size     = sizeof(IVIDENC2_OutArgs);

    /*------------------------------------------------------------------------*/
    /*  Allocate memory for the reconstructed frames required during file     */
    /*  write.Align tbe extended width & height to 16 bit                     */
    /*------------------------------------------------------------------------*/
    extWidth                        = (gConfig.captureWidth + 15) & ~15;
    extHeight                       = (gConfig.captureHeight + 15) & ~15;

    /*------------------------------------------------------------------------*/
    /*  Initialization of static parameters is done by this function call     */
    /*------------------------------------------------------------------------*/
    TestApp_SetInitParams(&params, &gConfig);

    /*------------------------------------------------------------------------*/
    /*  Algorithm create call. This function will allocate memory for the     */
    /*  algorithm handle and for all the buffers (memtabs) required by the    */
    /*  algorithm and initialize them accordingly. The alg handle is          */
    /*  returned.                                                             */
    /*------------------------------------------------------------------------*/
    handle = JPEGVENC_create((JPEGVENC_Fxns *)&JPEGVENC_TI_IJPEGVENC, &params);

    /*------------------------------------------------------------------------*/
    /*  Check for errors in algorithm handle creation                         */
    /*------------------------------------------------------------------------*/
    if(handle == NULL)
    {
      fprintf(stdout, "Creation Failed.\n");
      fprintf(stdout, "Check the Create-time static parameter settings.\n");
      goto DELETE_INSTANCE;
    }
    
    /*------------------------------------------------------------------------*/
    /*  Print success message if handle creation is proper.                   */
    /*------------------------------------------------------------------------*/
    printf("\nAlgorithm Instance Creation Done...\n");
    
    /*------------------------------------------------------------------------*/
    /*  Call to RMAN Assign Resources (to verify the ires-rman functions.     */
    /*------------------------------------------------------------------------*/
    RMAN_AssignResources((IALG_Handle) handle);
    configCount++;
    
    if (gConfig.enablePrivacyMasking)
    {
        if(fgets(line,FILE_NAME_SIZE,fTestVecsFile))
        {
          sscanf(line,"%s",pmInputFile);
        }
        else
        {
          break ;
        }
        
      fpmInputFile = fopen(pmInputFile,"r");

    /*------------------------------------------------------------------------*/
    /*  Perform file open error check.                                        */
    /*------------------------------------------------------------------------*/
      if (!fpmInputFile)
      {
        printf("Couldn't open Parameter Config file %s.\n",pmInputFile);
        return XDM_EFAIL;
      }      
      
      if(readparamfile(fpmInputFile) != 0)
      {
        printf("Unable to read Config Parameter File %s\n", pmInputFile);
        return(XDM_EFAIL);
      }
      fclose(fpmInputFile);
    } 
    /*------------------------------------------------------------------------*/
    /*  The following function is used to initialize the dynamic params of    */
    /*  the IVIDENC2 handle.                                                  */
    /*------------------------------------------------------------------------*/
    TestApp_SetDynamicParams(&dynamicParams, &gConfig, &inArgs);    
    
    dynamicParams.rateControlParams.rateControlParamsPreset = 
                               params.rateControlParams.rateControlParamsPreset;    
    dynamicParams.rateControlParams.initialBufferLevel = 
                                   params.rateControlParams.initialBufferLevel;
    dynamicParams.rateControlParams.HRDBufferSize = 
                                   params.rateControlParams.HRDBufferSize;    
    dynamicParams.rateControlParams.qpI =     
                                   params.rateControlParams.qpI;                                   
    dynamicParams.rateControlParams.qpMaxI =     
                                   params.rateControlParams.qpMaxI;                                   
    dynamicParams.rateControlParams.qpMinI = 
                                   params.rateControlParams.qpMinI;    
    dynamicParams.rateControlParams.rcAlgo =     
                                   params.rateControlParams.rcAlgo;                                                                      
    dynamicParams.rateControlParams.VBRDuration =     
                                   params.rateControlParams.VBRDuration; 
    dynamicParams.rateControlParams.VBRsensitivity =     
                                   params.rateControlParams.VBRsensitivity; 
    dynamicParams.rateControlParams.vbvUseLevelThQ5 =     
                                   params.rateControlParams.vbvUseLevelThQ5;                                   
    /*------------------------------------------------------------------------*/
    /* Control call for Get the number of buffers and their Sizes             */
    /*------------------------------------------------------------------------*/
    status.videnc2Status.data.buf = (XDAS_Int8 *)sVersion;
    status.videnc2Status.data.bufSize = VERSION_DATA_BUF_SIZE;

    JPEGVENC_control(handle, XDM_GETVERSION,
    (JPEGVENC_DynamicParams *)&dynamicParams,
    (JPEGVENC_Status *)&status);

    printf("Version = %s\n",sVersion);
    
    /*------------------------------------------------------------------------*/
    /*  XDM_SETPARAMS is called to pass the Dynamic Parameters to the         */
    /*  codec. The Control function shall validate the parameters. If an      */
    /*  error is found then the Control function returns failure.             */
    /*------------------------------------------------------------------------*/
    retValue = JPEGVENC_control
    (
    handle,
    XDM_SETPARAMS,
    (JPEGVENC_DynamicParams *)&dynamicParams,
    (JPEGVENC_Status *)&status
    );

    /*------------------------------------------------------------------------*/
    /*  Check for errors during Control function call to XDM_SETPARAMS.       */
    /*------------------------------------------------------------------------*/
    if(retValue != IVIDENC2_EOK)
    {
      if(status.videnc2Status.extendedError & 
          (XDM_UNSUPPORTEDINPUT))
      {
        fprintf(stdout, "Error: Invalid dynamic parameters. \n");
      }
      
      /*----------------------------------------------------------------------*/
      /*  Query for the default Dynamic parameters from the codec.            */
      /*----------------------------------------------------------------------*/
      retValue = JPEGVENC_control(handle, XDM_GETDYNPARAMSDEFAULT,
      (JPEGVENC_DynamicParams *)&dynamicParams,
      (JPEGVENC_Status *)&status);
      
      /*----------------------------------------------------------------------*/
      /*  Pass the dynamic Parameters to the codec.                           */
      /*----------------------------------------------------------------------*/
      retValue = JPEGVENC_control(handle, XDM_SETPARAMS,
      (JPEGVENC_DynamicParams *)&dynamicParams,
      (JPEGVENC_Status *)&status );
    }
    
    /*------------------------------------------------------------------------*/
    /*  The GETBUFINFO call gives information for number of input and         */
    /*  output buffers. For the first call however,                           */
    /*------------------------------------------------------------------------*/
    JPEGVENC_control(handle, XDM_GETBUFINFO,
    (JPEGVENC_DynamicParams *)&dynamicParams,
    (JPEGVENC_Status *)&status);

    /*------------------------------------------------------------------------*/
    /* Open Input YUV Sequence file.                                          */
    /*------------------------------------------------------------------------*/
    finFile = fopen(inFile, "rb");
    if(finFile == NULL)
    {
      printf("\n Unable to open Input YUV Sequence File %s\n", inFile);
      return(XDM_EFAIL);
    }

    /*------------------------------------------------------------------------*/
    /* Open Output Bitstream file.                                            */
    /*------------------------------------------------------------------------*/
    if(testCompliance)
    {
      ftestFile = fopen(testFile, "rb");
      
      if(ftestFile == NULL)
      {
        printf("\n Unable to open Reference Bitstream File %s\n", testFile);
        return(XDM_EFAIL);
      }
    }
    else
    {
      ftestFile = fopen(testFile, "wb");
      
      if(ftestFile == NULL)
      {
        printf("\n Unable to open Output Bitstream File %s\n", testFile);
        return(XDM_EFAIL);
      }
    }

    /*------------------------------------------------------------------------*/
    /*        initialize the input buffer values &  pointers                  */
    /*------------------------------------------------------------------------*/
    inputBufDesc.chromaFormat = status.videnc2Status.inputChromaFormat;
    inputBufDesc.numPlanes = status.videnc2Status.bufInfo.minNumInBufs;

    inputBufDesc.imageRegion.topLeft.x = 0;
    inputBufDesc.imageRegion.topLeft.y = 0;
    inputBufDesc.imageRegion.bottomRight.x = extWidth;
    inputBufDesc.imageRegion.bottomRight.y = extHeight;

    inputBufDesc.contentType = IVIDEO_PROGRESSIVE;
    
    
    inputBufDesc.activeFrameRegion.topLeft.x =
                                             gConfig.captureTopLeftx;
     inputBufDesc.activeFrameRegion.topLeft.y =
                                             gConfig.captureTopLefty;
     inputBufDesc.activeFrameRegion.bottomRight.x =
                                            gConfig.captureTopLeftx +
                      dynamicParams.videnc2DynamicParams.inputWidth;
     inputBufDesc.activeFrameRegion.bottomRight.y =
                                            gConfig.captureTopLefty +
                     dynamicParams.videnc2DynamicParams.inputHeight;

    offsetAdd = 0;

    /*-----------------------------------------------------------------------*/
    /*  Initialize the TILER params & Get the buffers in TILER space         */
    /*-----------------------------------------------------------------------*/
    testAppTilerInit(status.videnc2Status.bufInfo.minInBufSize);

    /*------------------------------------------------------------------------*/
    /*   Initialize Input buffer descriptors for all the planes used          */
    /*------------------------------------------------------------------------*/
    if(inputBufDesc.chromaFormat == 9)
      {
      inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
      if(gConfig.captureWidth != 0)
      {
       inputBufDesc.planeDesc[0].bufSize.bytes = (extWidth * extHeight);
      }
      else
      {
        inputBufDesc.planeDesc[0].bufSize.bytes = (gConfig.frameWidth * extHeight);
      }
	  inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[0]         = extWidth;  
      
      offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      
       if(gConfig.captureWidth != 0)
      {
        inputBufDesc.planeDesc[1].bufSize.bytes = (extWidth * (extHeight >>1));
      }
      else
      {
        inputBufDesc.planeDesc[1].bufSize.bytes = (gConfig.frameWidth * (extHeight >>1));
      }
      inputBufDesc.planeDesc[1].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[1]         = extWidth; 
      inputBufDesc.planeDesc[1].memType   = XDM_MEMTYPE_RAW;
      offsetAdd += inputBufDesc.planeDesc[1].bufSize.bytes;
      }
      
      if((inputBufDesc.chromaFormat == 3)||(inputBufDesc.chromaFormat == 4))
      {
        inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
        inputBufDesc.planeDesc[0].bufSize.bytes = (2 * extWidth * extHeight);
      inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer ;
      inputBufDesc.imagePitch[0]         = 2*extWidth;
      offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      }
      
      if(inputBufDesc.chromaFormat == 5)
      {
       inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
      inputBufDesc.planeDesc[0].bufSize.bytes = (extWidth * extHeight);
                                 
      inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[0]         = extWidth;  
      
      offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      
      inputBufDesc.planeDesc[1].bufSize.bytes = (extWidth * extHeight);
      inputBufDesc.planeDesc[1].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[1]         = extWidth;  
      inputBufDesc.planeDesc[1].memType   = XDM_MEMTYPE_RAW;
      offsetAdd += inputBufDesc.planeDesc[1].bufSize.bytes;
      
      inputBufDesc.planeDesc[2].bufSize.bytes = (extWidth * extHeight);
      inputBufDesc.planeDesc[2].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[2]         = extWidth;  
      inputBufDesc.planeDesc[2].memType   = XDM_MEMTYPE_RAW;
      offsetAdd += inputBufDesc.planeDesc[2].bufSize.bytes;
      }
      
      if(inputBufDesc.chromaFormat == 7)
      {
        inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
        inputBufDesc.planeDesc[0].bufSize.bytes = (extWidth * extHeight);
      inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer ;
      inputBufDesc.imagePitch[0]         = extWidth;
      offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      }
    
    outputAdd = pIoBuffer + offsetAdd ;

    /*------------------------------------------------------------------------*/
    /*        initialize the output  pointers                                 */
    /*------------------------------------------------------------------------*/
    outputBufDesc.numBufs =status.videnc2Status.bufInfo.minNumOutBufs;

    /*------------------------------------------------------------------------*/
    /*   Initialize output buffer descriptors for all the planes used         */
    /*------------------------------------------------------------------------*/
    for(loopCount = 0; loopCount < outputBufDesc.numBufs; loopCount++)
    {
      /*----------------------------------------------------------------------*/
      /*   Initialize Output buffer pointer                                   */
      /*----------------------------------------------------------------------*/
      outputBufDesc.descs[loopCount].buf  = (XDAS_Int8 *)outputAdd + offsetAdd;
      
      /*----------------------------------------------------------------------*/
      /*   Initialize number of bytes of output data present in output buffer */
      /*----------------------------------------------------------------------*/
      outputBufDesc.descs[loopCount].bufSize.bytes = 
              status.videnc2Status.bufInfo.minOutBufSize[loopCount].bytes;
      
      /*----------------------------------------------------------------------*/
      /*   Initialize Output buffer memory type                               */
      /*----------------------------------------------------------------------*/
      outputBufDesc.descs[loopCount].memType       =
      status.videnc2Status.bufInfo.outBufMemoryType[loopCount];
      
      offsetAdd += outputBufDesc.descs[loopCount].bufSize.bytes;
    }

    /*------------------------------------------------------------------------*/
    /* Change here to test the Data Sync                                      */
    /*------------------------------------------------------------------------*/
    if (gConfig.outputDataMode == IVIDEO_SLICEMODE)
    {
      initial_size = 2048;
    }
    else
    {
      initial_size = 2048;
    }
    
    if (gConfig.outputDataMode != IVIDEO_ENTIREFRAME)
    {
      outputBufDesc.descs[0].bufSize.bytes = initial_size;
    }
    
    curr_ddr_addr[0] = (XDAS_UInt8*)outputBufDesc.descs[0].buf + initial_size;
	
    for(count = 1;count < NUM_INPUT_BLOCKS; count++)
    {
      curr_ddr_addr[count] = (XDAS_UInt8*)curr_ddr_addr[count - 1] + 
                             blockSizeArray[count -1];
    }
   
    /*------------------------------------------------------------------------*/
    /*  Initializing Thumbnail Buffer Descriptors in Inargs                   */
    /*------------------------------------------------------------------------*/
    inArgs.APPN0.buf                 = NULL;
    inArgs.APPN0.bufSize.bytes       = 0;
    inArgs.APPN0.memType             = XDM_MEMTYPE_RAW;

    /*------------------------------------------------------------------------*/
    /*  Encode Thumbnail data in APPO Marker                                  */
    /*------------------------------------------------------------------------*/
    inArgs.thumbnailIndexApp0        = 0;
    
    /*------------------------------------------------------------------------*/
    /*  Encode Thumbnail data in APPO Marker                                  */
    /*------------------------------------------------------------------------*/
    inArgs.thumbnailIndexApp1        = 0;

    /*------------------------------------------------------------------------*/
    /*  Do-While Loop for Encode Call                                         */
    /*------------------------------------------------------------------------*/
    do
    {
      /*----------------------------------------------------------------------*/
      /*Initialize the input ID in input arguments to the bufferid of         */
      /*the buffer element returned from getfreebuffer() function.            */
      /*----------------------------------------------------------------------*/
      inArgs.videnc2InArgs.inputID   = 1;

      /*----------------------------------------------------------------------*/
      /*   Initialize Input buffer descriptors for all the planes used        */
      /*----------------------------------------------------------------------*/
      offsetAdd = 0;
      
    if(inputBufDesc.chromaFormat == 9)
      {
      inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
      if(gConfig.captureWidth != 0)
      {
       inputBufDesc.planeDesc[0].bufSize.bytes = (extWidth * extHeight);
      }
      else
      {
        inputBufDesc.planeDesc[0].bufSize.bytes = (gConfig.frameWidth * extHeight);
      }
      inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd; 
      inputBufDesc.imagePitch[0]         = extWidth;
      offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      if(gConfig.captureWidth != 0)
      {
        inputBufDesc.planeDesc[1].bufSize.bytes = (extWidth * (extHeight >>1));
      }
      else
      {
        inputBufDesc.planeDesc[1].bufSize.bytes = (gConfig.frameWidth * (extHeight >>1));
      }
      inputBufDesc.planeDesc[1].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
	   inputBufDesc.imagePitch[1]         =  extWidth;
      inputBufDesc.planeDesc[1].memType   = XDM_MEMTYPE_RAW;
      offsetAdd += inputBufDesc.planeDesc[1].bufSize.bytes;
      }
      
      if((inputBufDesc.chromaFormat == 3)||(inputBufDesc.chromaFormat == 4))
      {
        inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
        inputBufDesc.planeDesc[0].bufSize.bytes = (2 * extWidth * extHeight);
        inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer ;
        inputBufDesc.imagePitch[0]         = extWidth;
        offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      }
      
      if(inputBufDesc.chromaFormat == 5)
      {
       inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
      inputBufDesc.planeDesc[0].bufSize.bytes = (extWidth * extHeight);
                                 
      inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[0]         = extWidth;  
      
      offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      
      inputBufDesc.planeDesc[1].bufSize.bytes = (extWidth * extHeight);
      inputBufDesc.planeDesc[1].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[1]         = extWidth;  
      inputBufDesc.planeDesc[1].memType   = XDM_MEMTYPE_RAW;
      offsetAdd += inputBufDesc.planeDesc[1].bufSize.bytes;
      
      inputBufDesc.planeDesc[2].bufSize.bytes = (extWidth * extHeight);
      inputBufDesc.planeDesc[2].buf      = (XDAS_Int8 *) pIoBuffer +  offsetAdd;
      inputBufDesc.imagePitch[2]         = extWidth;  
      inputBufDesc.planeDesc[2].memType   = XDM_MEMTYPE_RAW;
      offsetAdd += inputBufDesc.planeDesc[2].bufSize.bytes;
      }
      
      if(inputBufDesc.chromaFormat == 7)
      {
        inputBufDesc.planeDesc[0].memType   = XDM_MEMTYPE_RAW;
        inputBufDesc.planeDesc[0].bufSize.bytes = (extWidth * extHeight);
      inputBufDesc.planeDesc[0].buf      = (XDAS_Int8 *) pIoBuffer ;
      inputBufDesc.imagePitch[0]         = extWidth;
      offsetAdd += inputBufDesc.planeDesc[0].bufSize.bytes;
      }
      
      /*----------------------------------------------------------------------*/
      /*  Read Input YUV Sequence data.                                       */
      /*----------------------------------------------------------------------*/
      if(gConfig.captureWidth != 0)
      {
        TestApp_ReadInputYUVData(&inputBufDesc, gConfig.captureWidth,
        gConfig.captureHeight, extWidth, extHeight, 
        frmNumEncoded, finFile);
      }
      else
      {
        TestApp_ReadInputYUVData(&inputBufDesc, gConfig.frameWidth,
        gConfig.captureHeight, extWidth, extHeight, 
        frmNumEncoded, finFile);
      }

      tilerParams.tilerSpace[0]    = CONTAINER_8BITS;
      tilerParams.tilerSpace[1]    = CONTAINER_16BITS;
      if(gConfig.chromaTilerMode)
      {
        tilerParams.tilerSpace[1]  = CONTAINER_8BITS;
      }

      for(loopCount = 0;loopCount<inputBufDesc.numPlanes;loopCount++)
      {
        if(gConfig.tilerEnable)
        {
          if((inputBufDesc.chromaFormat == 9)||(inputBufDesc.chromaFormat == 5)
             || (inputBufDesc.chromaFormat == 7))
          {
            Tiler_DataMove((char *)inputBufDesc.planeDesc[loopCount].buf,
             (char *)(tilerParams.tiledBufferAddr[loopCount]),
             extWidth, 
             extHeight, 
             tilerParams.tilerSpace[loopCount] );
          }
          else
          {
            Tiler_DataMove((char *)inputBufDesc.planeDesc[loopCount].buf,
              (char *)(tilerParams.tiledBufferAddr[loopCount]),
              extWidth*2, 
              extHeight, 
              tilerParams.tilerSpace[loopCount] );
          }
          
          /*------------------------------------------------------------------*/
          /* Initialize Input buffer pointer                                  */
          /*------------------------------------------------------------------*/
          inputBufDesc.planeDesc[loopCount].buf         = 
          (XDAS_Int8 *)(tilerParams.tiledBufferAddr[loopCount]);
          inputBufDesc.planeDesc[loopCount].memType = 
          status.videnc2Status.bufInfo.inBufMemoryType[loopCount];
          inputBufDesc.planeDesc[loopCount].bufSize.tileMem.width = extWidth;
          inputBufDesc.planeDesc[loopCount].bufSize.tileMem.height = extHeight;
          inputBufDesc.imagePitch[0] = SOURCE_PITCH_TILER8;
          inputBufDesc.imagePitch[1] = SOURCE_PITCH_TILER16;
          if(gConfig.chromaTilerMode == TRUE && loopCount > 0)
          {
            inputBufDesc.planeDesc[loopCount].memType = XDM_MEMTYPE_TILED8;
            inputBufDesc.imagePitch[1] = SOURCE_PITCH_TILER8;
          }
        }
      }
      
      /*----------------------------------------------------------------------*/
      /*  Start the encode process for one frame/field by calling the         */
      /*  JPEGVENC_encodeFrame() function.                                    */
      /*----------------------------------------------------------------------*/
	  if ((gConfig.outputDataMode == IVIDEO_FIXEDLENGTH)&&(initial_size == 0))
      {
        outputBufDesc.descs[0].bufSize.bytes = 0;
        outputBufDesc.descs[0].buf = NULL;
      }
	  
      retValue  = JPEGVENC_encodeFrame(handle, &inputBufDesc,
      &outputBufDesc, &inArgs, &outArgs);
      
      /*----------------------------------------------------------------------*/
      /*  Check for failure message in the return value.                      */
      /*----------------------------------------------------------------------*/
      if(retValue != IVIDENC2_EOK)
      {
        /* Frame encoded unsuccessfully */
        fprintf(stdout, "Frame encoding failed.\n");
        fprintf(stdout,"Encoded number of bits = %d\n",
        outArgs.videnc2OutArgs.bytesGenerated * 8);
      }

      fprintf(stdout, "\nFrame #%d Bytes Generated: %d",(numFramesEncoded + 1),
      (outArgs.videnc2OutArgs.bytesGenerated));
      bytesFor30Frames += outArgs.videnc2OutArgs.bytesGenerated;
      if((numFramesEncoded + 1) % 
         (dynamicParams.videnc2DynamicParams.targetFrameRate / 1000) == 0)
      {
        float temp;
        printf("  BitsConsumedFor30Frames = %d",bytesFor30Frames*8);
        temp = ((float)bytesFor30Frames*8) / 1000000;
        printf("  Bitrate30Frames = %f\n",temp);
        bytesFor30Frames = 0;
      }
      /*----------------------------------------------------------------------*/
      /*  Write the Output Bitstream to a file.                               */
      /*----------------------------------------------------------------------*/
      if(outArgs.videnc2OutArgs.bytesGenerated)
      {
        if(testCompliance)
        {
          /*------------------------------------------------------------------*/
          /* Compare the output with the reference                            */
          /*------------------------------------------------------------------*/
          compareTestVal = TestApp_CompareOutputData(ftestFile, &outputBufDesc, 
          &outArgs);
          
          if(compareTestVal == IVIDENC2_EOK)
          {
            printf(" : Passed\n");
          }
          else
          {
            /*----------------------------------------------------------------*/
            /* Test Compliance Failed... Breaking...                          */
            /* The output is not bit exact with the reference                 */
            /*----------------------------------------------------------------*/
            printf("************Failed*************\n");
            break;
          }
        }
        else
        {
          TestApp_WriteOutputData(&outputBufDesc,
          outArgs.videnc2OutArgs.bytesGenerated,
          ftestFile);

        }
      }

      /*----------------------------------------------------------------------*/
      /*  Increment the FramesEncoded count.                                  */
      /*----------------------------------------------------------------------*/
      numFramesEncoded++;

      /*----------------------------------------------------------------------*/
      /*  Datasync variables for every frame                                  */
      /*----------------------------------------------------------------------*/
      AccCount = 0;
      GblCount = 0;
    } while(numFramesEncoded < gConfig.NumFrames);

    DELETE_INSTANCE:

    /*------------------------------------------------------------------------*/
    /*  Free the buffers allocated for through IRES-RMAN.                     */
    /*------------------------------------------------------------------------*/
    RMAN_FreeResources((IALG_Handle) handle);                                 
    
    /*------------------------------------------------------------------------*/
    /*  Delete the Encoder Instance.                                          */
    /*------------------------------------------------------------------------*/
    JPEGVENC_delete(handle);                                                  
    
    /*------------------------------------------------------------------------*/
    /*  Close all the open file pointers.                                     */
    /*------------------------------------------------------------------------*/
    fclose(finFile);
    fclose(ftestFile);
    fprintf(stdout, "\n\n");

  } /* while !feof(testvecsFile) */

  fclose(fTestVecsFile);
  printf("End of Execution.\n\n");
  return (XDM_EOK);
}

/**
********************************************************************************
*  @fn     GetConfigFileContent (FILE *fname)
*
*  @brief  Reads the configuration file content in a buffer and returns the
*          address of the buffer
*
*  @param[in]  fname : Pointer to the configuration file.
*
*  @return Pointer to memory loaction holding configuration parameters/ 0
*
********************************************************************************
*/
char *GetConfigFileContent (FILE *fname)
{
  XDAS_Int32 FileSize;
  char *bufConfig;

  /*--------------------------------------------------------------------------*/
  /*  Set the File Data Pointer to the End of the file                        */
  /*--------------------------------------------------------------------------*/
  if (0 != fseek (fname, 0, SEEK_END))
  {
    return 0;
  }

  /*--------------------------------------------------------------------------*/
  /*  Read the current Pointer location which will give the file size         */
  /*--------------------------------------------------------------------------*/
  FileSize = ftell (fname);

  /*--------------------------------------------------------------------------*/
  /*  Check if filesize is valid                                              */
  /*--------------------------------------------------------------------------*/
  if (FileSize < 0 || FileSize > MAX_CONFIG_FILE_BUF_SIZE)
  {
    return 0;
  }

  /*--------------------------------------------------------------------------*/
  /*  Set the File Data Pointer to beginning of the file                      */
  /*--------------------------------------------------------------------------*/
  if (0 != fseek (fname, 0, SEEK_SET))
  {
    return 0;
  }

  /*--------------------------------------------------------------------------*/
  /*  Allocate buffer for storing data from config file                       */
  /*--------------------------------------------------------------------------*/
  if ((bufConfig = malloc(FileSize + 1)) == NULL)
  {
    fprintf(stdout, "No Enough memory for Config Buffer");
  }

  /*--------------------------------------------------------------------------*/
  /* Note that ftell() gives us the file size as the file system sees it.     */
  /* The actual file size, as reported by fread() below will be often         */
  /* smaller due to CR/LF to CR conversion and/or control characters after    */
  /* the dos EOF marker in the file.                                          */
  /*--------------------------------------------------------------------------*/
  FileSize = fread (bufConfig, 1, FileSize, fname);
  bufConfig[FileSize] = '\0';

  fclose (fname);

  return bufConfig;
}/* GetConfigFileContent() */

/**
********************************************************************************
*  @fn     ParameterNameToMapIndex (char *s)
*
*  @brief  Returns the index number from sTokenMap[] for a given parameter name.
*
*  @param[in]  s : parameter name string
*
*  @return The index number if the string is a valid parameter name, -1 for
*          error
********************************************************************************
*/
XDAS_Int32 ParameterNameToMapIndex (char *s)
{
  XDAS_Int32 indexNum = 0;

  while (sTokenMap[indexNum].tokenName != NULL)
  {
    if (0==strcmp (sTokenMap[indexNum].tokenName, s))
    return indexNum;
    else
    indexNum++;
  }

  return -1;
}/* ParameterNameToMapIndex() */

/**
********************************************************************************
* @fn    ParseContent (char *buf, XDAS_Int32 bufsize)
*
*@brief  Parses the character array buf and writes global variable input.This is
*        necessary to facilitate the addition of new parameters through the
*        sTokenMap[] mechanism. Need compiler-generated addresses in sTokenMap.
*
*@param[in,out]  buf     : Pointer to the buffer to be parsed
*
*@param[in]      bufsize : size of buffer
*
*@return Pass/Fail
********************************************************************************
*/
XDAS_Int32 ParseContent (char *buf, XDAS_Int32 bufsize)
{
  char *items[MAX_ITEMS_TO_PARSE];
  XDAS_Int32 MapIdx;
  XDAS_Int32 item = 0;
  XDAS_Int32 InString = 0, InItem = 0;
  char *pbuf = buf;
  char *bufend = &buf[bufsize];
  XDAS_Int32 IntContent;
  XDAS_Int32 itemNum;
  FILE *fpErr = stderr;

  /*--------------------------------------------------------------------------*/
  /*                                STAGE ONE                                 */
  /*--------------------------------------------------------------------------*/
  /* Generate an argc/argv-type list in items[], without comments and         */
  /* whitespace. This is context insensitive and could be done most easily    */
  /* with lex(1).                                                             */
  /*--------------------------------------------------------------------------*/
  while (pbuf < bufend)
  {
    switch (*pbuf)
    {
    case 13:  /* ASCII value 13 represents Carriage return                    */
      pbuf++;
      break;
    case '#':       /* Found comment                                          */
      *pbuf = '\0'; /* Replace '#' with '\0' in case of comment               */
      /* immediately following integer or string                */
      /* Skip till EOL or EOF, whichever comes first            */
      while (*pbuf != '\n' && pbuf < bufend)
      pbuf++;
      InString = 0;
      InItem = 0;
      break;
    case '\n':
      InItem = 0;
      InString = 0;
      *pbuf++='\0';
      break;
    case ' ':
    case '\t':             /* Skip whitespace, leave state unchanged          */
      if (InString)
      pbuf++;
      else
      {                    /* Terminate non-strings once whitespace is found  */
        *pbuf++ = '\0';
        InItem = 0;
      }
      break;
    case '"':              /* Begin/End of String                             */
      *pbuf++ = '\0';
      if (!InString)
      {
        items[item++] = pbuf;
        InItem = ~InItem;
      }
      else
      InItem = 0;
      InString = ~InString; /* Toggle                                         */
      break;
    default:
      if (!InItem)
      {
        items[item++] = pbuf;
        InItem = ~InItem;
      }
      pbuf++;
    }
  }

  item--;
  for (itemNum=0; itemNum<item; itemNum+= 3)
  {
    if (0 > (MapIdx = ParameterNameToMapIndex (items[itemNum])))
    {
      fprintf(fpErr, "\nParameter Name '%s' not recognized.. ", 
      items[itemNum]);
      return -1;
    }

    if (strcmp ("=", items[itemNum+1]))
    {
      fprintf(fpErr,
      "\nfile: '=' expected as the second token in each line.");
      return -1;
    }
    if(sTokenMap[MapIdx].type == 1)
    {
      strcpy(sTokenMap[MapIdx].place, items[itemNum+2]);
    }
    else if(sTokenMap[MapIdx].type == 2)
    {
      sscanf (items[itemNum+2], "%d", &IntContent);
      * ((XDAS_Int8 *) (sTokenMap[MapIdx].place)) = IntContent;
    }
    else
    {
      sscanf (items[itemNum+2], "%d", &IntContent);
      * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
    }
  }

  return 0 ;
}/* ParseContent() */

/**
********************************************************************************
*  @fn     readparamfile(FILE * fname)
*
*  @brief  Top Level function to read the parameter file.
*
*  @param[in]  fname  : Pointer to the configuration file
*
*
*  @return pass/Fail
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname)
{
  char *FileBuffer = NULL ;
  XDAS_Int32 retVal ;

  /*--------------------------------------------------------------------------*/
  /*  read the content in a buffer                                            */
  /*--------------------------------------------------------------------------*/
  FileBuffer = GetConfigFileContent(fname);

  /*--------------------------------------------------------------------------*/
  /*  Parse the content of config file                                        */
  /*--------------------------------------------------------------------------*/
  if(FileBuffer)
  {
    retVal  = ParseContent(FileBuffer,strlen(FileBuffer));
    return retVal;
  }
  else
  {
    return -1;
  }
}/* readparamfile() */

/**
********************************************************************************
*  @fn   TestApp_ReadInput_444P_YUVData(IVIDEO2_BufDesc *inputBuf, 
*                                       short frmWidth, short frmHeight,
*                                       int frameCount, FILE * fin)
* 
*
*  @brief          Read Input YUV444P Data from a File
*
*  @param[in,out]  inputBuf  : Pointer to the Input Buffer
*
*  @param[in]      frmWidth  : Frame Width
*
*  @param[in]      frmHeight : Frame Height
*
*  @param[in]      frameCount: Number of Frames
*
*  @param[in]      fin       : Input File Pointer
*
* @return          0
********************************************************************************
*/
short TestApp_ReadInput_444P_YUVData(IVIDEO2_BufDesc *inputBuf, 
short frmWidth, short frmHeight, int frameCount, FILE * fin)
{
  
  unsigned char *dst;
  unsigned int loopCnt, u32ChromaPitch, u32LumaPitch;

  u32LumaPitch = ALIGN_16(frmWidth);
  u32ChromaPitch = ALIGN_16(frmWidth);
  
  /*--------------------------------------------------------------------------*/
  /* Read Y Data                                                              */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[0].buf;
  for(loopCnt = 0;loopCnt<frmHeight;loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth), fin);
    dst += u32LumaPitch;
  }
  
  /*--------------------------------------------------------------------------*/
  /* Read U Data                                                              */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[1].buf;
  for(loopCnt= 0;loopCnt<(frmHeight);loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth), fin);
    dst += u32ChromaPitch;
  }
  
  /*--------------------------------------------------------------------------*/
  /* Read V Data                                                              */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[2].buf;
  for(loopCnt= 0;loopCnt<(frmHeight);loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth), fin);
    dst += u32ChromaPitch;
  }
  return 0;
}

/**
********************************************************************************
*  @fn   TestApp_ReadInput_422IBE_YUVData(IVIDEO2_BufDesc *inputBuf, 
*                                         short frmWidth, short frmHeight,
*                                         int frameCount, FILE * fin)
*
*  @brief  Read Input YUV422 IBE Data from a File
*
*  @param[in,out]  inputBuf  : Pointer to the Input Buffer
*
*  @param[in]      frmWidth  : Frame Width
*
*  @param[in]      frmHeight : Frame Height
*
*  @param[in]      frameCount: Number of Frames
*
*  @param[in]      fin       : Input File Pointer
*
* @return          0
********************************************************************************
*/
short TestApp_ReadInput_422IBE_YUVData(IVIDEO2_BufDesc *inputBuf, 
short frmWidth, short frmHeight,int frameCount, FILE * fin)
{

  unsigned char *dst;
  unsigned int loopCnt, u32LumaPitch;
  
  u32LumaPitch = ALIGN_16(frmWidth*2);
  
  /*--------------------------------------------------------------------------*/
  /* Read YUYV data                                                           */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[0].buf;
  for(loopCnt = 0;loopCnt<frmHeight;loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth<<1), fin);
    dst += u32LumaPitch;
  }
  return 0;
}

/**
********************************************************************************
*  @fn   TestApp_ReadInput_422ILE_YUVData(IVIDEO2_BufDesc *inputBuf, 
*                                         short frmWidth, short frmHeight,
*                                         int frameCount, FILE * fin)
*
*  @brief  Read Input YUV422 ILE Data from a File
*
*  @param[in,out]  inputBuf  : Pointer to the Input Buffer
*
*  @param[in]      frmWidth  : Frame Width
*
*  @param[in]      frmHeight : Frame Height
*
*  @param[in]      frameCount: Number of Frames
*
*  @param[in]      fin       : Input File Pointer
*
* @return          0
********************************************************************************
*/
short TestApp_ReadInput_422ILE_YUVData(IVIDEO2_BufDesc *inputBuf, 
short frmWidth, short frmHeight,int frameCount, FILE * fin)
{

  unsigned char *dst;
  unsigned int loopCnt, u32LumaPitch;
  
  u32LumaPitch = ALIGN_16(frmWidth*2);
  
  /*--------------------------------------------------------------------------*/
  /* Read YUYV data                                                           */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[0].buf;
  for(loopCnt = 0;loopCnt<frmHeight;loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth<<1), fin);
    dst += u32LumaPitch;
  }
  return 0;
}

/**
********************************************************************************
*  @fn   TestApp_ReadInput_400Gry_YUVData(IVIDEO2_BufDesc *inputBuf, 
*                                         short frmWidth, short frmHeight,
*                                         int frameCount, FILE * fin)
*
*  @brief  Read Input Gray Data from a File
*
*  @param[in,out]  inputBuf  : Pointer to the Input Buffer
*
*  @param[in]      frmWidth  : Frame Width
*
*  @param[in]      frmHeight : Frame Height
*
*  @param[in]      frameCount: Number of Frames
*
*  @param[in]      fin       : Input File Pointer
*
* @return          0
********************************************************************************
*/
short TestApp_ReadInput_400Gry_YUVData(IVIDEO2_BufDesc *inputBuf, 
short frmWidth, short frmHeight,int frameCount, FILE * fin)
{
  unsigned char *dst;
  unsigned int loopCnt, u32LumaPitch;
  
  u32LumaPitch = ALIGN_16(frmWidth);
  
  /*--------------------------------------------------------------------------*/
  /* Read Y data                                                              */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[0].buf;
  for(loopCnt = 0;loopCnt<frmHeight;loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth), fin);
    dst += u32LumaPitch;
  }
  return 0;
}

/**
********************************************************************************
*  @fn   TestApp_ReadInput_420SP_YUVData(IVIDEO2_BufDesc *inputBuf, 
*                                        short frmWidth, short frmHeight,
*                                        int frameCount, FILE * fin)
*
*  @brief  Read Input YUV420 Data from a File
*
*  @param[in,out]  inputBuf  : Pointer to the Input Buffer
*
*  @param[in]      frmWidth  : Frame Width
*
*  @param[in]      frmHeight : Frame Height
*
*  @param[in]      frameCount: Number of Frames
*
*  @param[in]      fin       : Input File Pointer
*
* @return          0
********************************************************************************
*/
short TestApp_ReadInput_420SP_YUVData(IVIDEO2_BufDesc *inputBuf,
short frmWidth, short frmHeight,int frameCount, FILE * fin)
{
  
  unsigned char *dst;
  unsigned int loopCnt, u32ChromaPitch, u32LumaPitch;
  
  u32LumaPitch = ALIGN_16(frmWidth);
  u32ChromaPitch = ALIGN_16(frmWidth);

  /*--------------------------------------------------------------------------*/
  /* Read Y data                                                              */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[0].buf;
  for(loopCnt = 0;loopCnt<frmHeight;loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth), fin);
    dst += u32LumaPitch;
  }
  /*--------------------------------------------------------------------------*/
  /* Read UV Interleaved data                                                 */
  /*--------------------------------------------------------------------------*/
  dst = (unsigned char *) inputBuf->planeDesc[1].buf;
  for(loopCnt= 0;loopCnt<(frmHeight>>1);loopCnt++)
  {
    fread(dst, sizeof(unsigned char), (frmWidth), fin);
    dst += u32ChromaPitch;
  }
  return 0;
}

/**
********************************************************************************
*  @fn   TestApp_ReadInputYUVData(IVIDEO2_BufDesc *inputBuf, 
*                                 short frmWidth, short frmHeight,
*                                 short extWidth, short extHeight, 
*                                 int frameCount, FILE * fin)
*
*  @brief  Read Input YUV Data from a File
*
*  @param[in,out]  inputBuf  : Pointer to the Input Buffer
*
*  @param[in]      frmWidth  : Frame Width
*
*  @param[in]      frmHeight : Frame Height
*  
*  @param[in]      extWidth  : Extended Width
*  
*  @param[in]      extHeight : Extended Height
*
*  @param[in]      frameCount: Number of Frames
*
*  @param[in]      fin       : Input File Pointer
*
* @return          0
********************************************************************************
*/
short TestApp_ReadInputYUVData(IVIDEO2_BufDesc *inputBuf, 
short frmWidth, short frmHeight, short extWidth, short extHeight, 
int frameCount, FILE * fin)
{
  /*--------------------------------------------------------------------------*/
  /* Call Functions to read YUV Data depending on input Chroma format         */
  /*--------------------------------------------------------------------------*/
  switch(inputBuf->chromaFormat)
  {
  case XDM_YUV_422IBE :   TestApp_ReadInput_422IBE_YUVData(inputBuf, 
    frmWidth, frmHeight, frameCount, fin);
    break;
	
  case XDM_YUV_422ILE :   TestApp_ReadInput_422ILE_YUVData(inputBuf, 
    frmWidth, frmHeight, frameCount, fin);
    break;
    
  case XDM_GRAY       :   TestApp_ReadInput_400Gry_YUVData(inputBuf, 
    frmWidth, frmHeight, frameCount, fin);
    break;
    
  case XDM_YUV_420SP  :   TestApp_ReadInput_420SP_YUVData(inputBuf, 
    frmWidth, frmHeight, frameCount, fin);
    break;
    
  case XDM_YUV_444P   :   TestApp_ReadInput_444P_YUVData(inputBuf, 
    frmWidth, frmHeight, frameCount, fin);
    break;
    
    default             :   break;
  }
  return 0;
}


/**
********************************************************************************
*  @fn   TestApp_WriteOutputData(XDM2_BufDesc *outputBuf,
*                                    int bytesGenerated,
*                                      FILE *fout)
*
*  @brief  Write Bitstream Data to a File
*
*  @param[in]      outputBuf      : Pointer to the Output Buffer
*
*  @param[in]      bytesGenerated : Number of Bytes Generated
*
*  @param[in,out]  fout           : Output File Pointer
*
* @return          0
********************************************************************************
*/
short TestApp_WriteOutputData(XDM2_BufDesc *outputBuf,int bytesGenerated, 
FILE *fout)
{
  /*--------------------------------------------------------------------------*/
  /*Get the Pointer to encoded data in external memory                        */
  /*--------------------------------------------------------------------------*/
  char *src = (char*)outputBuf->descs[0].buf;
  
  /*--------------------------------------------------------------------------*/
  /* Write Encoded data into output file                                      */
  /*--------------------------------------------------------------------------*/
  if (gConfig.outputDataMode == IVIDEO_ENTIREFRAME)
  {
    fwrite(src, bytesGenerated, 1, fout);
  }

  return 0;
}

/**
********************************************************************************
*  @fn   TestApp_CompareOutputData(FILE *fRefFile, XDM2_BufDesc *outputBufDesc,
*                                  JPEGVENC_OutArgs *outArgs)
*
*  @brief  Comparing Output Data with Reference File data
*
*  @param[in]  fRefFile        : Reference file pointer
*
*  @param[in]  outputBufDesc   : Pointer to Output Buffer Descriptors
*
*  @param[in]  outArgs         : Pointer to Outargs
*
*  @return  pass/fail
********************************************************************************
*/
XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,
XDM2_BufDesc *outputBufDesc, JPEGVENC_OutArgs *outArgs)
{
  XDAS_Int32 bufNum, retVal;
  XDAS_UInt8 *refData;

  retVal = IVIDENC2_EOK;

  refData = malloc(outArgs->videnc2OutArgs.bytesGenerated);
  
  /*--------------------------------------------------------------------------*/
  /* Compare all the output Buffers with the ref File                         */
  /*--------------------------------------------------------------------------*/
  for(bufNum=0; bufNum < outputBufDesc->numBufs ; bufNum++)
  {
    /*------------------------------------------------------------------------*/
    /* Read Reference data from reference file to reference data buffer       */
    /*------------------------------------------------------------------------*/
    fread(refData, 1, outArgs->videnc2OutArgs.bytesGenerated, fRefFile);

    /*------------------------------------------------------------------------*/
    /* Compare reference data & output data generated.                        */
    /* Number of bytes compared is number of bytes generated by encoder       */
    /*------------------------------------------------------------------------*/
    if(memcmp(refData, outputBufDesc->descs[bufNum].buf,
          outArgs->videnc2OutArgs.bytesGenerated))
    {
      retVal = IVIDENC2_EFAIL;
    }
    break ;
  }
  free(refData);
  return retVal;
}

/**
********************************************************************************
*  @fn   TestApp_SetInitParams(JPEGVENC_Params *params,
*                              JpegBPEncConfig *config)
*
*  @brief  Set create time Parameters
*
*  @param[out]  params        : Pointer to Create time Parameters
*
*  @param[in]   config        : Pointer to config Structure
*
*  @return      none
********************************************************************************
*/

XDAS_Void TestApp_SetInitParams(JPEGVENC_Params *params,JpegBPEncConfig *config)
{
  /*--------------------------------------------------------------------------*/
  /*  Set IVIDENC2 parameters                                                 */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /*  Size: sizeof(IVIDENC2_Params)                                           */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.size                = sizeof(IJPEGVENC_Params);            
  
  /*--------------------------------------------------------------------------*/
  /*  maxHeight: HD Height (4096)                                             */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.maxHeight           = config->maxHeight; 
  
  /*--------------------------------------------------------------------------*/
  /*  maxWidth: HD Width   (4096)                                             */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.maxWidth            = config->maxWidth;  
  
  /*--------------------------------------------------------------------------*/
  /*  Data Endianness : XDM_BYTE. (Big endian stream)                         */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.dataEndianness      = config->dataEndianness;      
  
  /*--------------------------------------------------------------------------*/
  /*  inputChromaFormat :  Chroma format for the input buffer.                */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.inputChromaFormat   = config->inputChromaFormat;

  /*--------------------------------------------------------------------------*/
  /*  inputContentType :  Progressive or Interlaced format of the buffer      */
  /*                        being encoded.                                    */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.inputContentType    = config->inputContentType;

  /*--------------------------------------------------------------------------*/
  /*  operatingMode :  Video Coding Mode of operation (encode/decode/         */
  /*  transcode/transrate).                                                   */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.operatingMode       = config->operatingMode;

  /*--------------------------------------------------------------------------*/
  /*  inputDataMode :  Video input data mode                                  */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.inputDataMode       = config->inputDataMode;

  /*--------------------------------------------------------------------------*/
  /*  outputDataMode :  Video output data mode                                */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.outputDataMode      = config->outputDataMode;

  /*--------------------------------------------------------------------------*/
  /*  numInputDataUnits :  Number of input rows                               */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.numInputDataUnits   = config->numInputDataUnits;

  /*--------------------------------------------------------------------------*/
  /*  numOutputDataUnits :  Number of output slices                           */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.numOutputDataUnits  = config->numOutputDataUnits;

  /*--------------------------------------------------------------------------*/
  /*  Set Extended Parameters in IJpegVENC parameters                         */
  /*--------------------------------------------------------------------------*/
  params->maxThumbnailHSizeApp0 = 4096;
  params->maxThumbnailHSizeApp1 = 4096;
  params->maxThumbnailVSizeApp0 = 4096;
  params->maxThumbnailVSizeApp1 = 4096;
  params->debugTraceLevel = config->debugTraceLevel;

  params->lastNFramesToLog = config->lastNFramesToLog;
  params->Markerposition   = config->Marker_position;
  
  params->rateControlParams.VBRDuration     = 8;
  params->rateControlParams.VBRsensitivity  = 0;
  params->rateControlParams.vbvUseLevelThQ5 = 0;
  
  params->videnc2Params.rateControlPreset = config->rateControlPreset;
  params->videnc2Params.maxBitRate = config->maxBitRate;
  params->videnc2Params.minBitRate = config->minBitRate;
  
  params->rateControlParams.rateControlParamsPreset = 
                              config->rateControlParams.rateControlParamsPreset;
  params->rateControlParams.rcAlgo = 
                              config->rateControlParams.rcAlgo;
  params->rateControlParams.qpMaxI = 
                              config->rateControlParams.qpMaxI;
  params->rateControlParams.qpMinI = 
                              config->rateControlParams.qpMinI;
  params->rateControlParams.qpI = 
                              config->rateControlParams.qpI;
  params->rateControlParams.initialBufferLevel = 
                              config->rateControlParams.initialBufferLevel;
  params->rateControlParams.HRDBufferSize = 
                              config->rateControlParams.HRDBufferSize;
  params->rateControlParams.discardSavedBits = 
                              config->rateControlParams.discardSavedBits;
  return;
}

/**
********************************************************************************
*  @fn   TestApp_SetDynamicParams(JPEGVENC_DynamicParams *dynamicParams,
*                                 JpegBPEncConfig *config)
*
*  @brief  Set Dynamic Parameters
*
*  @param[out]  dynamicParams : Pointer to dynamic Parameters
*
*  @param[in]   config        : Pointer to config Structure
*
*  @return      none
********************************************************************************
*/
XDAS_Void TestApp_SetDynamicParams(JPEGVENC_DynamicParams *dynamicParams,
JpegBPEncConfig *config, IJPEGVENC_InArgs *inArgs)
{
  int i;   
  /*--------------------------------------------------------------------------*/
  /*  Set IVIDENC2 Dynamic parameters                                         */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /*  Size: sizeof(JPEGVENC_DynamicParams)   incase of extended class         */
  /*  of paramaters.                                                          */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.size  = sizeof(JPEGVENC_DynamicParams);

  /*--------------------------------------------------------------------------*/
  /*  Input Height                                                            */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.inputHeight    = config->frameHeight;

  /*--------------------------------------------------------------------------*/
  /*  Input Width                                                             */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.inputWidth     = config->frameWidth;

  /*--------------------------------------------------------------------------*/
  /*  Capture Width                                                           */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.captureWidth   = config->captureWidth;

  /*--------------------------------------------------------------------------*/
  /*  generateHeader :  Encode Header only                                    */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.generateHeader = config->generateHeader;

  /*--------------------------------------------------------------------------*/
  /*  Set Extended Parameters in IJpegVENC parameters                         */
  /*--------------------------------------------------------------------------*/
  if (gConfig.outputDataMode == IVIDEO_SLICEMODE)
  {
    dynamicParams->restartInterval                     = 7;
  }
  else
  {
    dynamicParams->restartInterval                     = 0;
  }

  /*--------------------------------------------------------------------------*/
  /*  Initalize the Quality factor                                            */
  /*--------------------------------------------------------------------------*/
  dynamicParams->qualityFactor                       = config->qualityFactor;

  /*--------------------------------------------------------------------------*/
  /*  Initalize the Quantization Table                                        */
  /*--------------------------------------------------------------------------*/
  dynamicParams->quantTable                          = NULL;

  /*--------------------------------------------------------------------------*/
  /*    assign dataSync  callBack function pointers to encoder dynamicParams  */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /*    INPUT DATA SYNC Function Pointer                                      */
  /*--------------------------------------------------------------------------*/
    /*--------------------------------------------------------------------------*/
  /* Set "getDataFxn" pointer to the call back function in application        */
  /*--------------------------------------------------------------------------*/
  fGetInpDHandle = (XDM_DataSyncHandle)&ip_datasyncDesc1;
  fGetbufferHandle = (XDM_DataSyncHandle)&ip_datasyncDesc2;
  fputDataHandle  = (XDM_DataSyncHandle)&ip_datasyncDesc3;
  dynamicParams->videnc2DynamicParams.getDataFxn =
  (XDM_DataSyncGetFxn)JPEGVENC_TI_UpdateGetDataCallBack;

  dynamicParams->videnc2DynamicParams.getDataHandle = fGetInpDHandle;
  

  /*--------------------------------------------------------------------------*/
  /* OUTPUT DATA SYNC Function Pointer                                        */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.getBufferFxn =
  (XDM_DataSyncGetBufferFxn)JPEGVENC_TI_UpdateGetBufferCallBack;

  dynamicParams->videnc2DynamicParams.getBufferHandle = fGetbufferHandle;
  
  /*--------------------------------------------------------------------------*/
  /* PUTDATA DATA SYNC Function Pointer                                       */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.putDataFxn =
  (XDM_DataSyncPutFxn)JPEGVENC_TI_PutDataCallBack;

  dynamicParams->videnc2DynamicParams.putDataHandle = fputDataHandle;
  
  dynamicParams->videnc2DynamicParams.targetFrameRate = config->targetFrameRate;
  dynamicParams->videnc2DynamicParams.targetBitRate = config->targetBitRate;
  
  if(inArgs->videnc2InArgs.size == sizeof(IVIDENC2_InArgs))
  {
    config->enablePrivacyMasking = 0;  
  }
  dynamicParams->enablePrivacyMasking = config->enablePrivacyMasking;
  
  if(dynamicParams->enablePrivacyMasking == 1)
  {
  
  inArgs->pmInputParams.noOfPrivacyMaskRegions = 
                                   config->pmInputParams.noOfPrivacyMaskRegions;
  inArgs->pmInputParams.lumaValueForPM = config->pmInputParams.lumaValueForPM;
  inArgs->pmInputParams.cbValueForPM = config->pmInputParams.cbValueForPM;
  inArgs->pmInputParams.crValueForPM = config->pmInputParams.crValueForPM;
  
  for(i = 0; i < inArgs->pmInputParams.noOfPrivacyMaskRegions; i++)
  {
    inArgs->pmInputParams.listPM[i].topLeft.x = 
                                  config->pmInputParams.listPM[i].topLeft.x;
    inArgs->pmInputParams.listPM[i].bottomRight.x = 
                                  config->pmInputParams.listPM[i].bottomRight.x;
    inArgs->pmInputParams.listPM[i].topLeft.y = 
                                  config->pmInputParams.listPM[i].topLeft.y;
    inArgs->pmInputParams.listPM[i].bottomRight.y = 
                                  config->pmInputParams.listPM[i].bottomRight.y;    
  }
  }
  return;
}

/**
*******************************************************************************
*  @fn       MEMUTILS_getPhysicalAddr(Ptr Addr)
*  @brief      This function will give the physical address on HOST_M3
*
*  @param[in]  Addr : Pointer to the address for which physical address
*                     is required
*
*  @return     Pointer to the physical memory
*******************************************************************************
*/
void *MEMUTILS_getPhysicalAddr(Ptr Addr)
{
  return ((void *)((unsigned int)Addr & VDMAVIEW_EXTMEM));
}

/**
********************************************************************************
*  @fn     JPEGVENC_TI_UpdateGetDataCallBack(  XDM_DataSyncHandle ptr,
*                                     XDM_DataSyncDesc *dataSyncDescrRowLevel)
*  @brief  Append one or more number of input rows into the frame buffer and
*          update the numBlocks equal to the total number of rows has been
*          filled into the frame buffer.
*          codec will do a call back as soon as it completed encoding the
*          number of rows available in frame buffer.
*          Codec assumes atleast one row appended per a call back.

*
*  @param[in]  ptr  : Pointer to the IALG_Handle structure
*
*  @param[in]  dataSyncDescrRowLevel : Pointer to the data sync descriptor
*
*  @return None
********************************************************************************
*/
XDAS_Void JPEGVENC_TI_UpdateGetDataCallBack( XDM_DataSyncHandle ptr,
XDM_DataSyncDesc* dataSyncDescrRowLevel)
{
  volatile int* pNumBlocks =  &dataSyncDescrRowLevel->numBlocks;    
  
  if (gConfig.inputDataMode == IVIDEO_NUMROWS) /* NUM_ROWS */
  {
    /*------------------------------------------------------------------------*/
    /* get the input to frame buffer and update the numBlocks.                */
    /* numBlocks should be total number of input rows available               */
    /* from the start of the frame, codec internally knows the                */
    /* number of rows it has encoded already.                                 */
    /* codec assumes atleast one row appended per a call back.                */
    /*------------------------------------------------------------------------*/
    *pNumBlocks = 3;
  }

  return;
}


/**
********************************************************************************
*  @fn     JPEGVENC_TI_UpdateGetBufferCallBack(  XDM_DataSyncHandle ptr,
*                                  XDM_DataSyncDesc *dataSyncDescrFixedLength )
*                                  
*  @brief  Append one or more number of input rows into the frame buffer and
*          update the numBlocks equal to the total number of rows has been
*          filled into the frame buffer.
*          codec will do a call back as soon as it completed encoding the
*          number of rows available in frame buffer.
*          Codec assumes atleast one row appended per a call back.
*
*  @param[in]  ptr  : Pointer to the IALG_Handle structure
*
*  @param[in]  dataSyncDescrFixedLength : Pointer to the data sync descriptor
*
*  @return None
********************************************************************************
*/
XDAS_Void JPEGVENC_TI_UpdateGetBufferCallBack( XDM_DataSyncHandle ptr,
XDM_DataSyncDesc* dataSyncDescrFixedLength)
{
  if (gConfig.outputDataMode == IVIDEO_FIXEDLENGTH)
  {
    dataSyncDescrFixedLength->scatteredBlocksFlag = TRUE;
    dataSyncDescrFixedLength->varBlockSizesFlag   = TRUE;
    
    /*------------------------------------------------------------------------*/
    /* In IVIDEO_FIXEDLENGTH Mode the stream buffer may contigous or          */
    /* non-contigous Memory depending upon the Scatter Flag                   */
    /*------------------------------------------------------------------------*/
    if(dataSyncDescrFixedLength->scatteredBlocksFlag == TRUE)
    {
      dataSyncDescrFixedLength->numBlocks  = blockPerDataSync[GblCount];
      /* (1 <= numBlocks <= 4) */
      
      dataSyncDescrFixedLength->baseAddr   = 
      (XDAS_Int32*)&curr_ddr_addr[AccCount]; 
      dataSyncDescrFixedLength->blockSizes = 
      (XDAS_Int32*)&blockSizeArray[AccCount];
    }
    else
    {
      dataSyncDescrFixedLength->numBlocks  = 1; 
      dataSyncDescrFixedLength->baseAddr   = (XDAS_Int32*)curr_ddr_addr[0];
      dataSyncDescrFixedLength->blockSizes = (XDAS_Int32*)&blockSizeArray[0];
    }
    
    AccCount += blockPerDataSync[GblCount];
    GblCount++;
  }
  else if(gConfig.outputDataMode == IVIDEO_SLICEMODE)
  {
    dataSyncDescrFixedLength->scatteredBlocksFlag = FALSE;
    dataSyncDescrFixedLength->varBlockSizesFlag   = FALSE;
    
    dataSyncDescrFixedLength->numBlocks  = 1;
    dataSyncDescrFixedLength->blockSizes = (XDAS_Int32*)&blockSizeArray[0];
  }
  
  return;
}
/**
********************************************************************************
*  @fn     JPEGVENC_TI_PutDataCallBack(  XDM_DataSyncHandle ptr,
*                                     XDM_DataSyncDesc *putDataSyncDescr )
*                                      
*  @brief    Call back funtion from IVAHD to Application informing about the 
*            availability of the output stream
*
*
*  @param[in]  ptr  : Pointer to the IALG_Handle structure
*
*  @param[in]  putDataSyncDescr : Pointer to the data sync descriptor
*
*  @return     None
********************************************************************************
*/
XDAS_Void JPEGVENC_TI_PutDataCallBack( XDM_DataSyncHandle ptr,
XDM_DataSyncDesc* putDataSyncDescr)
{
  /*--------------------------------------------------------------------------*/
  /* Write Encoded data into output file                                      */
  /*--------------------------------------------------------------------------*/
  fwrite(putDataSyncDescr->baseAddr, putDataSyncDescr->blockSizes[0], 1, 
  ftestFile);
}

/** 
********************************************************************************
*  @fn     SetPATViewMapBase
*
*  @brief  This function provides the base address, i.e the physical address 
*          in external memory to be used as tiler memory.
*
*  @return None
********************************************************************************
*/
void SetPATViewMapBase()
{
/*--------------------------------------------------------------------------*/
/* The default values set in gel files is 0x8000000 which will              */
/* overlap on the .text mapped in client. Hence, to avoid corruption        */
/* of vital memory we are mapping the tiler base address to a               */
/* different value.                                                         */
/* In below piece of code, programming of Below Registers are done          */
/* DMM_PAT_VIEW_MAP                                                         */
/* DMM_PAT_VIEW_MAP_BASE                                                    */
/* DMM_PAT_IRQSTATUS_RAW                                                    */
/* DMM_PAT_STATUS                                                           */
/* DMM_PAT_AREA                                                             */
/* DMM_PAT_DATA                                                             */
/*--------------------------------------------------------------------------*/
#if defined(HOSTCORTEXM3_OMAP4) || defined(HOSTCORTEXM3_OMAP4SIMULATOR)
  /*------------------------------------------------------------------------*/ 
  /* Tiler is mapped to following physical container addresses:             */
  /* TILE8_PHY_ADDR -  0x9000 0000 -> 0x9800 0000                           */
  /* TILE16_PHY_ADDR - 0x9800 0000 -> 0xA000 0000                           */
  /* TILE32_PHY_ADDR - 0xA000 0000 -> 0xA800 0000                           */
  /* TILEPG_PHY_ADDR - 0xA000 0000 -> 0xA800 0000                           */
  /* Tiler32 & TilePG are overlayed with assumption that Tile32 is not      */ 
  /* used                                                                   */
  /*------------------------------------------------------------------------*/

      *(int *)(0x4E000440) = 0x04040302; 
      *(int *)(0x4E000444) = 0x04040302; 
      *(int *)(0x4E000448) = 0x04040302; 
      *(int *)(0x4E00044C) = 0x04040302; 

      *(int *)(0x4E000460) = 0x80000000; 

      *(int *)(0x4E000480) = 0x00000003; 
      *(int *)(0x4E0004C0) = 0x0000000B; 
      *(int *)(0x4E000504) = 0x3FFF20E0;
      *(int *)(0x4E00050C) = 0x8510F010;
#endif

#if defined(HOSTCORTEXM3_NETRA) || defined(HOSTCORTEXM3_NETRASIMULATOR)

  /*------------------------------------------------------------------------*/
  /* Tiler is mapped to following physical container addresses:             */
  /* TILE8_PHY_ADDR -  0xA000 0000 -> 0xA800 0000                           */
  /* TILE16_PHY_ADDR - 0xA800 0000 -> 0xB000 0000                           */
  /* TILE32_PHY_ADDR - 0xB000 0000 -> 0xB800 0000                           */
  /* TILEPG_PHY_ADDR - 0xB000 0000 -> 0xB800 0000                           */
  /* Tiler32 & TilePG are overlayed with assumption that Tile32 is not      */ 
  /* used                                                                   */
  /*------------------------------------------------------------------------*/
      *(int *)(0x4E000440) = 0x06060504; 
      *(int *)(0x4E000444) = 0x06060504; 
      *(int *)(0x4E000448) = 0x06060504; 
      *(int *)(0x4E00044C) = 0x06060504;

      *(int *)(0x4E000460) = 0xA0000000;

      *(int *)(0x4E000480) = 0x00000003; 
      *(int *)(0x4E0004C0) = 0x0000000B; 
      *(int *)(0x4E000504) = 0x3FFF20E0;
      *(int *)(0x4E00050C) = 0x8510F010;
#endif
}

/** 
********************************************************************************
*  @fn     XDAS_Void testAppTilerInit(XDM2_BufSize *bufSizes)
*
*  @brief  The testAppTilerInit function initializes & chunks the TILER 
*          memory into required number with required 2D block sizes.
*
*  @param[in] bufSizes  : Address of array containing the buffer sizes of the 
*                         numbufs.
*
*  @return None
********************************************************************************
*/
XDAS_Void testAppTilerInit(XDM2_BufSize *bufSizes)
{
  XDAS_Int32    ret_val;
  
  /*--------------------------------------------------------------------------*/
  /*  Get the buffers in TILER space                                          */
  /*--------------------------------------------------------------------------*/
  if(gConfig.tilerEnable)                                                     
  {                                                                           
    /*------------------------------------------------------------------------*/
    /* Get the buffers in TILER space                                         */
    /* Do the allocation for maximum supported resoultion and keep to some    */
    /* aligned boundary. Also this allocation assumes that tiled8 and         */
    /* tiled16 are mapped to same physical space                              */
    /*------------------------------------------------------------------------*/
    sTilerParams *pTilerParams     = &tilerParams;
    
    /*------------------------------------------------------------------------*/
    /* Set the base address of the tiler memory area allocated by the tiler   */
    /* library.                                                               */
    /*------------------------------------------------------------------------*/
    SetPATViewMapBase();
                            
    pTilerParams->tilerSpace[0]    = CONTAINER_8BITS;                         
    pTilerParams->tilerSpace[1]    = CONTAINER_16BITS;                        
    if(gConfig.chromaTilerMode)                                               
    {                                                                         
      pTilerParams->tilerSpace[1]  = CONTAINER_8BITS;                         
    }                                                                         
    
    pTilerParams->imageDim[0]      = bufSizes[0].tileMem.width;               
    pTilerParams->imageDim[1]      = bufSizes[0].tileMem.height;              

    /*------------------------------------------------------------------------*/
    /* Max Luma Size we will be using (4096*4096) is set to  totalSizeLuma    */
    /*------------------------------------------------------------------------*/
    pTilerParams->totalSizeLuma    = 0x6000000;                               
    
    pTilerParams->memoryOffset[0]  = 0;                                       
    pTilerParams->memoryOffset[1]  = pTilerParams->totalSizeLuma;             
    
    ret_val = tiler_init(pTilerParams);                                       
    if(ret_val == -1)                                                         
    {                                                                         
      /*----------------------------------------------------------------------*/
      /* If tiler allocation is not successful then Force both the buffer     */
      /* to be in raw region                                                  */
      /*----------------------------------------------------------------------*/
      gConfig.tilerEnable = 0 ;                                               
    }
  }
}

