/*
 ===========================================================================
 * HDVICP2 Based H.264 HP Encoder
 * 
 * "HDVICP2 Based H.264 HP Encoder" is software module developed on TI's 
 * HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw 
 * video into a high/main/baseline profile bit-stream.
 *
 * Copyright (C) {2009} Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *
 ===========================================================================
*/


/**  
 *****************************************************************************
 * @file h264enc_ti_config.h                          
 *                                       
 * @brief This File contains function definitions for a standard 
 *        implementation of a test configuration file parser. 
 *        These functiosn parses the input  configuration files and 
 *        assigns user provided values to global instance structures
 *  
 *
 * @author: Rama Mohana Reddy (rama.mr@ti.com)
 *
 * @version 0.0 (Jan 2008) : Base version created
 *                           [Pramod]
 * @version 0.1 (Oct 2009) : Review and more commenting along with cleanup
 *                           [Rama Mohan]
 * @version 0.2 (April 2010) : Support of tiler buffer control [Pramod]
 * @version 0.3 (May 2010) : Support of IVAHD sub system selection[Nirmal]
 * @version 0.4 (Apr 2009) : Added start Frame support [Uday]
 * @version 0.5 (Aug 2010) : Added support of testing dynamic parameter change
 *                           at runtime [Nirmal]
 * @version 0.6 (Sep 2010) : Support of setting value to numBlocks for
 *                           DataSyncGetData from user
 * @version 0.7 (Dec 2010) : Cleanup related to platform specific macros
 * @version 0.8 (Aug 2011) : Added parameters related to GDR
 * @version 0.9 (Mar 2013) : Code modifications to fix SDOCM00099577(Encoder 
 *                           does not give refined error codes in case of 
 *                           creation fail or run time parameter set fail)
 *                           [Santosh]
 *****************************************************************************
*/

#ifndef _H264_TI_TEST_CONFIG_H_
#define _H264_TI_TEST_CONFIG_H_

#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <h264enc.h>
/** 
 *  Maximum size of the string to hold file name along with path
*/
#define FILE_NAME_SIZE 512
/** 
 *  Macro defining the maximum number of parameters to be parsed from the input
 *  configuration file
*/
#define MAX_ITEMS_TO_PARSE  1024 

/** 
 *  Macro to enable profiling
*/
#define GENERATE_PROFILE_NUMBER
/* #undef GENERATE_PROFILE_NUMBER*/

/*----------------------------------------------------------------------------*/
/* Macros to get proper address bases for differnt type of hosts              */
/*----------------------------------------------------------------------------*/
#ifdef OMAP4
  #define PROFILE_M3
  #define M3_HZ     (166000000)
  #define IVAHD_MHZ (266.0)
#endif 

#ifdef NETRA
  #define PROFILE_M3
  #define M3_HZ     (250000000)
  #define IVAHD_MHZ (533.0)
#endif

/*----------------------------------------------------------------------------*/
/* Base address in case when host is M3 and on Ducati Simulator               */
/*----------------------------------------------------------------------------*/
#if defined OMAP4
  #ifdef A9_HOST_FILE_IO
    #define MEM_BASE_IVAHD0  0xBB000000
    #define REG_BASE_IVAHD0  0xBA000000
    #define RST_CNTL_BASE_IVAHD0 0xAA306F10
  #else
    #define MEM_BASE_IVAHD0  0x5B000000
    #define REG_BASE_IVAHD0  0x5A000000
    #define RST_CNTL_BASE_IVAHD0 0x4A306F10
  #endif
#endif

#if defined NETRA

  #define MEM_BASE_IVAHD0  0x59000000
  #define REG_BASE_IVAHD0  0x58000000
  #define RST_CNTL_BASE_IVAHD0 0x48180C10

  #define MEM_BASE_IVAHD1  0x5B000000
  #define REG_BASE_IVAHD1  0x5A000000
  #define RST_CNTL_BASE_IVAHD1 0x48180D10

  #define MEM_BASE_IVAHD2  0x54000000
  #define REG_BASE_IVAHD2  0x53000000
  #define RST_CNTL_BASE_IVAHD2 0x48180E10

#endif /* #if defined NETRA */


typedef enum
{
  PROCESS_START,
  PROCESS_END,   
  HDVICP_ACQUIRE,
  HDVICP_WAIT,
  HDVICP_DONE,  
  HDVICP_RELEASE
  
} ProfileId ;

#define NO_OF_PROFILE_INSTANCES 50

/** 
 *  Macro defining ICONT1 DTCM offset from the base address
*/
#define ICONT1_DTCM_OFFSET 0x00000000
/** 
 *  Macro defining ICONT2 DTCM offset from the base address
*/
#define ICONT2_DTCM_OFFSET 0x00010000
/** 
 *  Macro defining ICONT1 ITCM offset from the base address
*/
#define ICONT1_ITCM_OFFSET 0x00008000
/** 
 *  Macro defining ICONT2 ITCM offset from the base address
*/
#define ICONT2_ITCM_OFFSET 0x00018000


/** 
 *  Macro defining address of TIMER init module 
*/
#define ICEC_CNT_CTRL (*(volatile int*)(REG_BASE + 0x40840))
/** 
 *  Macro defining address of capture time register in ICE CRUSHER
*/
#define ICEC_CNT_VAL  (*(volatile int*)(REG_BASE + 0x40844))
/** 
 *  Macro defining address of MB loop cycles in SL2 memory for the first field
 *  In case of progressive frame this spalce contain total number of MB loop 
 *  cycles
*/
#define MB_LOOP_FIELD_0 (*(volatile int*)(MEM_BASE + 0x3FFF0))
/** 
 *  Macro defining address of MB loop cycles in SL2 memory for the second field
*/
#define MB_LOOP_FIELD_1 (*(volatile int*)(MEM_BASE + 0x3FFF4))

#ifdef PROFILE_M3
/** 
 *  Macro defining address of M3 TIMER init module 
*/
#define SYSTICKREG            (*(volatile int*)0xE000E010)
#define SYSTICKREL            (*(volatile int*)0xE000E014)
#define SYSTICKRELVAL         (0x00FFFFFF)
#define SYSTICKVAL            (*(volatile int*)0xE000E018)
#endif

 /** 
 *  Macro defines mode of the HDVICP resource used
 *  This is same as IRES_HDVICP2_Status enum.
 *  0 - represents SAMECODEC
 *  1 - represents SAMECODECTYPE
 *  2 - represents DIFFERENTCODEC
 *
 *  When SAMECODEC is enabled only part of DTCM is curruptedin both
 *  Iconts , i.e Memroy other than const and stack, persistant area in ICONT2
 *  is currupted
 *
 *  When SAMECODECTYPE is enabled only part of DTCM is curruptedin both
 *  Iconts , i.e Memroy other than const and stack, persistant area in ICONT2
 *  is currupted. Total SL2 memory is currupted.
 *
 *  When DIFFERENTCODEC is enabled entire IVAHD memory is currupted
 *  Here we contaminate full ITCM,DTCM of ICONT and SL2 memory
 *
*/
#define HDVICP_STATUS 0

/** 
 *  Macro to enable scratch contamination test
*/
#undef SCRATCH_CONTAMINATE

/**
 * For tighter control of Rate Control Limit QPMax
*/
#define MAX_QPI_TRC 36
 /**
 *******************************************************************************
 *  @struct sTokenMapping
 *  @brief  Token Mapping structure for Error reporting
 *          This structure contains error reporting strings which are mapped to
 *          Codec errors
 *
 *  @param  errorName : Pointer to the error string
 * 
 *******************************************************************************
*/
typedef struct sErrorMapping{
  XDAS_Int8 *errorName;
}sErrorMapping;


 /**
 *******************************************************************************
 *  @struct sTokenMapping
 *  @brief Token Mapping structure for parsing codec specific configuration file
 *
 *  @param  tokenName : Name of the parameter in config file exposed to user  
 *  @param  place : Place holder for the data
 *  @param  type : Variable to specify whether the parameter is string or number
 *                 With the help of this parser function will use either memcpy
 *                 or fscanf fucntions
 * 
 *******************************************************************************
*/
typedef struct sTokenMapping{
  XDAS_Int8     *tokenName;
  XDAS_Void     *place;
  XDAS_Int32    type;
} sTokenMapping;
 /**
 *******************************************************************************
 *  @struct h264BPEncConfig_t
 *  @brief  Basic structure to hold config parameters, Which are nessesory to 
 *          run the test application
 *
 *  @param  inputFile : Place holder for the input YUV file name along with path
 *  @param  outputFile : Place holder for the output file name along with path
 *  @param  refFile : Place holder for the reference file to bitmatch with
 *          encoded bitstream
 *  @param  waterMarkInputKeyFile : Place holder for the Water mark input key 
 *                                  file along with path
 *  @param  type : flag to specify whether the parameter is string or number
 *                 With the help of this parser function will use either memcpy
 *                 or fscanf fucntions
 *  @param  numInputDataUnits : Number of frames to encode
 *
 *  @param  captureHeight : Height of the Image captured inluding cropping
 *
 *  @param  captureTopLeftx : Horizontal Top left stat position in image
 *
 *  @param  captureTopLefty : Vertical Top left stat position in image
 *
 *  @param  forceIDRPeriod : number specified by user to control encoding
 *                        This variable can be used to change the dynamic 
 *                        parameters at specified location , 
 *                        forcing IDR frame etc.
 *  @param  forceSKIPPeriod : number specified by user to control forcing of
 *                        Frame to be skip
 *  @param  gdrPeriod : number specified by user to control gdr durations 
 *  @param  gdrStartFrameNum : number specified by user to control gdr start
 *                             points 
 *  @param  LongTermRefPeriod : number specified by user to control 
 *                        Frames refering long term frames
 *  @param  LTRPFailureLocation0 : Frame Number in the capture order that needs 
 *                        to be considered as failure frame.
 *  @param  LTRPFailureLocation1 : Frame Number in the capture order that needs 
 *                        to be considered as failure frame.
 *  @param  numProcessCall : Parameter to encode in 30 process call and
 *                           60 process call mode
 *                           0 - Encode in 30 process call mode
 *                           1 - Encode in 60 process call mode
 *  @param  tilerSpace :Parameter to get tiler space for luma and chorma buffers
 *  @param  ivahdid : Parameter to get Ivahd ID
 *  @param  startFrame : Start frame number of yuv from where 
 *                       encoding need to happen
 *  @param  enableRunTimeTest : Flag to enable testing of dynamic parameter
 *                              change at run time
 *  @param  DynamicFramePos : Parameter to have frame number at which the
 *                            dynamic parameters to change
 *  @param  numBlocks:Array to hold number of blocks to be given as input during
 *                     each DataSyncGetData call
 *******************************************************************************
*/
typedef struct h264BPEncConfig_t{

  XDAS_Int8 inputFile[FILE_NAME_SIZE]            ;
  XDAS_Int8 outputFile[FILE_NAME_SIZE]           ;
  XDAS_Int8 refFile[FILE_NAME_SIZE]              ;
  XDAS_Int8 waterMarkInputKeyFile[FILE_NAME_SIZE];
  XDAS_Int32 numInputDataUnits;
  XDAS_Int32 captureHeight;
  XDAS_Int32 captureTopLeftx;
  XDAS_Int32 captureTopLefty;
  XDAS_Int32 forceIDRPeriod;
  XDAS_Int32 gdrPeriod;
  XDAS_Int32 gdrStartFrameNum;
  XDAS_Int32 forceSKIPPeriod;
  XDAS_Int32 LongTermRefPeriod;
  XDAS_Int32 LTRPFailureLocation0;
  XDAS_Int32 LTRPFailureLocation1; 
  XDAS_Int32 numProcessCall;
  XDAS_Int8  tilerSpace[2];
  XDAS_Int8  ivahdid;
  XDAS_Int32 startFrame;
  XDAS_Int8  enableRunTimeTest;
  XDAS_Int32 DynamicFramePos;
  XDAS_Int32 numBlocks[8];
  XDAS_Int8  roiinputFile[FILE_NAME_SIZE];
}h264BPEncConfig;

 /**
 *******************************************************************************
 *  @struct sLogGenerate
 *  @brief  Structure to hold log data, like frame start time instance,
 *          frame end time istance.
 *
 *  @param  uiEncodeStart : Time instance were encoding process started
 *  @param  uiEncodeEnd : Time instance were encodding process ended
 * 
 *******************************************************************************
*/
typedef struct sLogGenerate{
  XDAS_UInt32    uiEncodeStart;
  XDAS_UInt32    uiEncodeEnd;
  XDAS_UInt32    startTime_m3;
  XDAS_UInt32    endTime_m3;
  XDAS_UInt32    hostStartTime;
  XDAS_UInt32    hostEndTime;
  XDAS_UInt32    hostTime;

} sLogGenerate;

 /**
 *******************************************************************************
 *  @struct sProfileTimeStamps
 *  @brief  Structure to hold profile data at different instances during encode
 *          flow. Each element is array of size 2. 0th entry is for IVAHD cylces
 *          and 1st entry to store M3 cycles.
 *
 *  @param  processStartTimeStamp  : Time instance were encoding process started
 *  @param  hdvicpAcquireTimeStamp : Time instance were ivahd is acquired
 *  @param  hdvicpWaitTimeStamp    : Time instance were M3 enters to wait state
 *                                   just after triggering ivahd
 *  @param  hdvicpDoneTimeStamp    : Time instance where ivahd finished its 
 *                                   process
 *  @param  hdvicpReleaseTimeStamp : Time instance where M3 releases ivahd
 *  @param  processEndTimeStamp    : Time instance were encoding process ended
 * 
 *******************************************************************************
*/
typedef struct 
{
  XDAS_UInt32 processStartTimeStamp[2];
  XDAS_UInt32 hdvicpAcquireTimeStamp[2];
  XDAS_UInt32 hdvicpWaitTimeStamp[2];
  XDAS_UInt32 hdvicpDoneTimeStamp[2];
  XDAS_UInt32 hdvicpReleaseTimeStamp[2];
  XDAS_UInt32 processEndTimeStamp[2];
}sProfileTimeStamps;
 /**
 *******************************************************************************
 *  @struct sProfileCycles
 *  @brief  Structure to hold profile data mainly amount of cycles between 
 *          important probe points between process start to process end.
 *
 *  @param procStart_hdvicpAcquire : Time between process start to ivahd acquire
 *  @param hdvicpAcquire_hdvicpWait: Time between ivahd acquire till M3 enters
 *                                   to wait after triggering ivahd
 *  @param hdvicpWait_hdvicpDone   : Time between the moment M3 enters to wait
 *                                   and the moment coming to done. This cycle
 *                                   indicates actual frame processing by ivahd 
 *  @param hdvicpDone_hdvicpRelease: Time between the hdvicpDone till releasing
 *                                   the ivahd
 *  @param hdvicpRelease_procEnd   : Time between the moment ivahd is released
 *                                    till M3 reaches the process end.
 * 
 *******************************************************************************
*/
typedef struct 
{
  XDAS_UInt32 procStart_hdvicpAcquire[2];
  XDAS_UInt32 hdvicpAcquire_hdvicpWait[2];
  XDAS_UInt32 hdvicpWait_hdvicpDone[2];
  XDAS_UInt32 hdvicpDone_hdvicpRelease[2];
  XDAS_UInt32 hdvicpRelease_procEnd[2];
}sProfileCycles;
 /**
 *******************************************************************************
 *  @struct sProfileData
 *  @brief  
 *
 *  @param  contentType : 
 *  @param  profileCycles : 
 * 
 *******************************************************************************
*/
typedef struct 
{
  XDAS_UInt32 contentType;
  sProfileCycles profileCycles[2 * NO_OF_PROFILE_INSTANCES];
}sProfileData;

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Scratch_Contaminate
 *  @brief  This function will currupt scratch data in IVAHD buffers
 *          
 *          This function will currupt DTCM and other SL2 memory. This function
 *          does not contaminate const and stack area of ICONTs
 *          NOTE: Here the addresses depend on ICONT memory map, so when ever
 *          we change ICONT command file we need to change the hot 
 *          coded address
 *  
 *
 *  @return     None
********************************************************************************
*/

void H264ENC_TI_Scratch_Contaminate(XDAS_Int32 hdvicp_status);

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Init_Log
 *  @brief  This function will initialize status printing module
 *          
 *          This function, this prints log like number of frames encoded,
 *          bits consumed, cycles consumed etc
 *
 *  @param[in]  fTrace_file : File pointer to the trace log file
 *
 *  @return     XDM_EOK -  when there is no fatal error
 *              XDM_EFAIL - when it is fatal error
********************************************************************************
*/

XDAS_Int32 H264ENC_TI_Init_Log(FILE * fTrace_file);

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Capture_time
 *  @brief  This function will capture time instance 
 *          
 *          This function captures time and updates start or end time in log
 *          instance,
 *
 *  @param[in]  uiCapturePoint : tells start time or end time
 *                               0 - start time
 *                               1 - end time
 *
 *  @return     none
********************************************************************************
*/

void H264ENC_TI_Capture_time(XDAS_Int32 uiCapturePoint);

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Print_Log
 *  @brief  This function will print log encoding of the frame
 *          It will print frame type, number of frames encoded, number of bytes
 *          bytes generated for each field, and cycles consumed for each file
  
 *  @param[in]  fTrace_file : File pointer to the trace log file
 *
 *  @return     XDM_EOK -  when there is no fatal error
 *              XDM_EFAIL - when it is fatal error
********************************************************************************
*/

XDAS_Int32 H264ENC_TI_Print_Log(FILE * fTrace_file,XDAS_Int32 siFrameType,
                                XDAS_Int32 siContentType,
                                XDAS_Int32 siBytesGenerated,
                                XDAS_Int32 siBytesGeneratedBotField,
                                XDAS_Int32 siNumFramesEncoded);

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Report_Error
 *  @brief  This function will print error messages
 *          
 *          This function will check for codec errors which are mapped to 
 *          extended errors in videnc2status structure and prints them in cosole
 *          Returns XDM_EFAIL in case of fatal error
 *
 *  @param[in]  uiErrorMsg  : Extended error message
 *
 *  @param[in]  fTrace_file : File pointer to the trace log file
 *
 *  @return     XDM_EOK -  when there is no fatal error
 *              XDM_EFAIL - when it is fatal error
********************************************************************************
*/

XDAS_Int32 H264ENC_TI_Report_Error(FILE * fTrace_file,XDAS_Int32 uiErrorMsg);

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Report_ExtError
 *  @brief  This function will print sub extended error messages
 *          
 *          This function will check for codec errors which are mapped to 
 *          sub-extended errors in IH264ENC_Status structure and 
 *          IH264ENC_OutArgs structure and prints them on console
 *
 *  @param[in]  uiErrorMsg  : Extended error message
 *
 *  @param[in]  errorWord   : pointer to error word
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void H264ENC_TI_Report_ExtError(FILE * fTrace_file,
                                                    XDAS_UInt32 * errorWord) ;

/** 
********************************************************************************
 *  @fn     readparamfile
 *  @brief  Reads the entire param file contents into a global buffer,which is
 *          used for parsing and updates the params to given addresses.
 *          
 *  @param[in]  file name : Name of the configuration file with path
 *
 *  @return     0 - if successfully parsed all the elements in param file and 
 *                  their  values read into the memory addresses given in 
 *                  token mappign array.
 *             XDM_EFAIL - For any file read operation related errors or if 
 *                  unknown parameter names are entered or if the parameter 
 *                  file syntax is not in compliance with the below 
 *                  implementation.
********************************************************************************
*/

XDAS_Int32 readparamfile(XDAS_Int8 *configFile);

/** 
********************************************************************************
 *  @fn     TestApp_SetInitParams
 *  @brief  Function to set default parameters
 *          This function will set default params for params function and
 *          dynamicparams function. This must be called before parsing config
 *          file so that default values are set when config file does not 
 *          specify any value
 *          
 *  @param[in] params : pointer to the XDM params interface structure
 *
 *  @param[in] dynamicParams : Pointer to t he XDM dynamicparams structure
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void TestApp_SetInitParams(H264ENC_Params *params, 
                                          H264ENC_DynamicParams *dynamicParams);
                                        
/** 
********************************************************************************
 *  @fn     H264ENC_TI_InitDynamicParams
 *  @brief  Function to init dynamic params with Encode params
 *
 *          This fucntion will update the extended dynamic params with the     
 *          extended params in encode params structure.
 *          This function should be called as soon as cofig params are parsed 
 *          and read from the file. This is due to all the extended params will
 *          be updated in Encode params structure
 *          
 *  @param[in] params : pointer to the XDM params interface structure
 *
 *  @param[in] dynamicParams : Pointer to t he XDM dynamicparams structure
 *
 *  @return    None
********************************************************************************
*/

XDAS_Void H264ENC_TI_InitDynamicParams(H264ENC_Params *params, 
                                          H264ENC_DynamicParams *dynamicParams);

/** 
********************************************************************************
 *  @fn     H264ETest_DataSyncPutDataFxn
 *  @brief  Funtion to initialize the data sync module
 *
 *  @param[in] dataSyncHandle : pointer to the datasync handle
 *  
 *  @param[in] dataSyncDesc : pointer to the datasync discriptors
 *
 *  @return     0 : when no error
 *             -1 : in case of errors
 *
********************************************************************************
*/

Void H264ETest_DataSyncPutDataFxn(XDM_DataSyncHandle dataSyncHandle, 
        XDM_DataSyncDesc *dataSyncDesc);

#endif /*_H264_TI_TEST_CONFIG_H_*/
