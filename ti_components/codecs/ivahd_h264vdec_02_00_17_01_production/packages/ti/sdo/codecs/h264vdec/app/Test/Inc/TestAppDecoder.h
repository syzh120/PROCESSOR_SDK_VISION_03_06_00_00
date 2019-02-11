/*
*******************************************************************************
 * HDVICP2.0 Based H.264 HP Decoder
 * 
 * "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on "ISO/IEC 14496-10". 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*******************************************************************************
*/

/** @mainpage HDVICP2.0 Based H.264 HP Decoder
* @brief "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on 
 *  TI's HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on "ISO/IEC 14496-10". 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*/

/**  
*******************************************************************************
 * @file TestAppDecoder.h                        
 *                                       
 * @brief  This File contains function definitions, structures and
 *         macros that will be used for Sample Test application. 
 *
 * @author:  Ramakrishna Adireddy
 *
 * @version 0.1 (Jan 2009) : Base version Created
 * @version 0.2 (Apr 2010) : Updated function headers
 *                           [Ramakrishna Adireddy]
 * @version 0.3 (Jul 2010) : Added new function prototypes for the new testapp
 *                           [Ramakrishna Adireddy]
 ******************************************************************************
*/
#ifndef _TESTAPP_DECODER_
#define _TESTAPP_DECODER_

/******************************************************************************
*  INCLUDE FILES                                                
******************************************************************************/
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec3.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ih264vdec.h>
#include <TestApp_bufmanager.h>
#include <h264vdec.h>
#include <h264vdec_ti.h>
#include <TestApp_constants.h>
#include <TestAppFileIoApi.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <ti\sdo\fc\ires\tiledmemory\ires_tiledmemory.h>

/**
 *   Macros indicating the pass/fail status
*/
#define SUCCESS  0
#define FAILURE  1

/**
 *   Lenth of Boot code
*/
#define LENGTH_BOOT_CODE  14

/**
 *   Defining right argument type based on macro
*/
#ifdef USE_HOST_FILE_IO
  #define ARG_FILEIO_TYPE      AX_FILE_IO
#elif defined(USE_PCI)
  #define ARG_FILEIO_TYPE      PCI_FILE_IO
#else
  #define ARG_FILEIO_TYPE      RTSC_FILE_IO
#endif

/*--------------------------------------------------------------------------*/
/* Defines for N-Channel decode support                                     */
/*--------------------------------------------------------------------------*/
#define MAX_NUM_DEC_CHANNELS          (32)
#define NUM_DEC_CHANNELS_SUPPORTED    (10)

/**
 ******************************************************************************
 *  @struct tilerStruct
 *
 *  @brief  This structure contains Tiler specific parameters that need to be
 *          used during DMM initialization.
 *
 *  @param  tiler_param : Element that holds below 4 elements as a word after
 *                        packing them.
 *
 *  @param  flag_tiler_mode : Flag to indicate tiler is used or not.
 *
 *  @param  flag_tiler_interleaved : Flag to indicate whether to use tiler in 
 *                                   interleaved mode or not.
 *
 *  @param  flag_chroma_container : Flag to indicate the chroma container type.
 *                                  It is valid only when TILER mode is set.
 *
 *  @param  nb_tiled_objects : Element to indicate the maximum buffers needed
 *                             in TILER region.
 *
 *  @param  dmm_object_width : Element indicates the 2D object width that has
 *                             to be allocated in TILER region by DMM.
 *
 *  @param  dmm_object_height : Element indicates the 2D object height that has
 *                             to be allocated in TILER region by DMM.
 *
 *  @param  tiler_section_base_addr : Base adddress of TILER section.
 *
 *  @param  tiler_section_size : Size of the TILER section.
 *
 ******************************************************************************
*/
typedef struct _tilerStruct
{
  XDAS_UInt32 tiler_param;
  XDAS_UInt32 flag_tiler_mode;
  XDAS_UInt32 flag_tiler_interleaved;
  XDAS_UInt32 flag_chroma_container;
  XDAS_UInt32 nb_tiled_objects;
  XDAS_UInt32 dmm_object_width;
  XDAS_UInt32 dmm_object_height;
  XDAS_UInt32 tiler_section_base_addr;
  XDAS_UInt32 tiler_section_size;
}sTilerStruct;

/**
 ******************************************************************************
 *  @struct sAppControlParams
 *
 *  @brief  This structure contains the params that application want to control
 *          through the config file.
 *
 *  @param  seiDataMode : Indicates which mode the SEI has to be given out by
 *                        codec. 
 *
 *  @param  vuiDataMode : Indicates which mode the SEI has to be given out by
 *                        codec.
 *
 *  @param  tilerEnable     : Flag to indicate the TILER enabling status. 
 *
 *  @param  dualTilerEnable : Flag to indicate the TILER enabling status of dual
 *                            output buffer. This will be treated as 0 when 
 *                            tilerEnable is zero.
 *  @param  chromaTilerMode : Indicates the container type requested for chroma
 *                            in TILER section, valid only when TILER is used.
 *
 *  @param  bitStreamMode : Indicates the mode in which application feeds the
 *                          bit stream to codec i.e., either in Buffer moder or
 *                          in Frame mode.
 *
 *  @param  framesToDecode :The maximum number of frames decoded by the decoder. 
 *                          This param is added for debug purpose. This param 
 *                          will be useful in limitting the number of frames to
 *                          be decoded during testing.
 * 
 *  @param  dumpFrom : Indicates the frame number from which the dump of YUV
 *                     has to happen. It helps in faster debugging.
 *
 *  @param  crcNyuv : Indicates the format in which the dump to happen i.e,
 *                    either in YUV format or CRC format.
 *
 *  @param  profileEnable : Flag to enable or disable the profiling.
 *
 *  @param  parBoundCheck: Flag to enable or disable parameter boundary
 *                         checks validation.
 * 
 *  @param  parExpectedStatus: Indicates the expected staus during parameter
 *                             boundary checks validation.
 * 
 *  @param  exitLevel: Indicates the exit level, for the current test vector,
 *                     during parameter boundary checks validation.
 * 
 *  @param  xdmReset: Flag that indicates the use of XDM_RESET control to
 *                    avoid creating the instance for every new test vector. 
 * 
 *  @param  baseClassOnly: Flag that indicates the application to use
 *                         base class parameters only.
 * 
 *  @param  testCompliance: Flag to indicate the mode in which application runs
 * 
 *  @param  ddrConstLocation: Flag to indicate the use of relocatable memory
 *                            for constants of the codec Library.
 * 
 *  @param  ivahdId: In case any SoC has multiple IVAHDs, this element 
 *                   indicate to tell the ID of IVAHD to use.
 * 
 *  @param  inFile[STRING_SIZE]: Input file name
 * 
 *  @param  outFile[STRING_SIZE]: output file name
 * 
 *  @param  refFile[STRING_SIZE]: Reference file name
 * 
 *  @param  sizeFile[STRING_SIZE]: Frame size information file name
 * 
 *  @param  reserved[3]: Reserved field for future use.
 * 
 ******************************************************************************
*/
typedef struct _appControlParams
{
  XDAS_Int32  seiDataMode;
  XDAS_Int32  vuiDataMode;
  XDAS_Int32  mbInfoWriteMode;  
  XDAS_UInt32 tilerEnable;
  XDAS_UInt32 dualTilerEnable;  
  XDAS_UInt32 chromaTilerMode;
  XDAS_UInt32 bitStreamMode;
  XDAS_UInt32 framesToDecode;
  XDAS_UInt32 dumpFrom;
  XDAS_UInt32 crcNyuv;
  XDAS_UInt32 profileEnable;
  XDAS_UInt32 parBoundCheck;
  XDAS_Int32  parExpectedStatus;
  XDAS_UInt32 exitLevel;
  XDAS_UInt32 xdmReset;
  XDAS_UInt32 baseClassOnly;
  XDAS_UInt32 testCompliance;
  XDAS_UInt32 ddrConstLocation;
  XDAS_UInt32 ivahdId;
  XDAS_UInt8  inFile[STRING_SIZE];
  XDAS_UInt8  outFile[STRING_SIZE];
  XDAS_UInt8  outDualFile[STRING_SIZE];
  XDAS_UInt8  WaterMarkFile[STRING_SIZE];
  XDAS_UInt8  refFile[STRING_SIZE];
  XDAS_UInt8  sizeFile[STRING_SIZE];
  XDAS_Int32  reserved[1];
}sAppControlParams;

/**
 ******************************************************************************
 *  @struct sAppFilePointers
 *
 *  @brief  This structure contains file pointers to the files that are dealt
 *          by application through out the decoding.
 *
 *  @param  fpSizeFile : File pointer to frame size info file.
 *
 *  @param  fpRefFile : File pointer to reference file.
 *
 *  @param  fpInFile : File pointer to the input test vector
 *
 *  @param  fpOutFile : File pointer to the output YUV file
 *
 ******************************************************************************
*/
typedef struct _appFilePointers
{
  FILE    *fpRefFile;
  FILE    *fpSizeFile;
  FILE    *fpInFile; 
  FILE    *fpOutFile;
  FILE    *fpDualOutFile;
  FILE    *fpWaterMarkFile;
  
}sAppFilePointers;

/**
 ******************************************************************************
 *  @struct sTokenMapping
 *
 *  @brief  Token Mapping structure for parsing codec specific 
 *          configuration file.
 *
 *  @param  tokenName : String name in the configuration file.
 *
 *  @param  place : Place Holder for the data
 *
 *  @param  type : indicates the data type of the token
 *
 ******************************************************************************
*/
typedef struct _sTokenMapping 
{
  XDAS_Int8 *tokenName;
  XDAS_Void *place;
  XDAS_Int8  type;
} sTokenMapping;

/**
 ******************************************************************************
 *  @struct sProfileParams
 *
 *  @brief  Profiling specific parameters.
 *
 *  @param  startTime     : 
 *  @param  endTime       : 
 *  @param  endTimed      : 
 *  @param  startTimeM3   : 
 *  @param  endTimeM3     : 
 *  @param  endTimeM3d    : 
 *  @param  hostStartTime : 
 *  @param  hostEndTime   : 
 *  @param  hostTime      : 
 *
 ******************************************************************************
*/
typedef struct _profileParams
{
  XDAS_UInt32 processStartTime[2];
  XDAS_UInt32 processEndTime[2];
  XDAS_UInt32 hdvicpAcquireTime[2];
  XDAS_UInt32 postIvaMsgTime[2];
  XDAS_UInt32 hdvicpWaitTime[2];
  XDAS_UInt32 hdvicpDoneTime[2];
  XDAS_UInt32 hdvicpWait2Time[2];
  XDAS_UInt32 hdvicpDone2Time[2];
  XDAS_UInt32 hdvicpReleaseTime[2];
  
  XDAS_UInt32 procStart_hdvicpAcquire[2];
  XDAS_UInt32 hdvicpAcquire_postIvaMsg[2];
  XDAS_UInt32 hdvicpAcquire_hdvicpWait[2];
  XDAS_UInt32 hdvicpWait_hdvicpDone[2];
  XDAS_UInt32 hdvicpDone_hdvicpWait2[2];
  XDAS_UInt32 hdvicpWait2_hdvicpDone2[2];
  XDAS_UInt32 hdvicpDone_hdvicpRelease[2];
  XDAS_UInt32 hdvicpRelease_procEnd[2];
}sProfileParams;

/**
*******************************************************************************
 *  @struct sEnumToStringMapping
 *  @brief  Error Name Mapping to give error message.
 *          This structure contains error reporting strings which are mapped to
 *          Codec errors
 *
 *  @param  errorName : Pointer to the error string
 * 
*******************************************************************************
*/
typedef struct _sEnumToStringMapping
{
  XDAS_Int8 *errorName;
}sEnumToStringMapping;

typedef struct _channelState
{
  /*--------------------------------------------------------------------------*/
  /*  Declaring Algorithm specific handle                                     */
  /*--------------------------------------------------------------------------*/
   H264VDEC_Handle h264decHandle;
   XDAS_Int8       algCreated;
  /*--------------------------------------------------------------------------*/
  /*  Global flag for non-blocking call.                                      */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32          fatalErrorDetected;
  XDAS_Int32          nonFatalErrorDetected;
  XDAS_UInt32         frameCount;
  XDAS_Int32          picture_count;
  /*--------------------------------------------------------------------------*/
  /*  first_time: Flag used for reinitializing the buffers after the first    */
  /*              decode call. This need to be reset after buffer allocations */
  /*              are done based on the actual height,width are done.         */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32          first_time;
  XDAS_UInt32         displayCount;
  /*--------------------------------------------------------------------------*/
  /* CodecExtError, CodecExtErrorFlush : Local variable to capture errors from*/
  /*                                     decode call.                         */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32          CodecExtError;
  XDAS_Int32          CodecExtErrorFlush;
  XDAS_Int32          channelEnded;
  XDAS_Int8           process_ret_val;
  /*--------------------------------------------------------------------------*/
  /*  Input bitstream Buffer Management specific variables  like Bit stream   */
  /*  input file position for file read, variable to keep track of total bytes*/
  /*  consumed so far after every frame etc..                                 */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32 bsInFilePos;
  XDAS_Int32  validBytes;
  XDAS_Int32  bytesConsumed;
  XDAS_Int8   *bitStreamData;
  XDAS_UInt32 streamEnd;

  XDAS_UInt32 bufferFreed;
  XDAS_UInt32 bufferDisplayed;
 
  sAppControlParams appCntrlParams; 
  sAppFilePointers  appFilePtrs;
  /*--------------------------------------------------------------------------*/
  /*  Global Structure variables for static and dynamic params.               */
  /*--------------------------------------------------------------------------*/
  H264VDEC_Params          params;
  H264VDEC_DynamicParams   dynamicParams;
  /*--------------------------------------------------------------------------*/
  /*  Base Class Structures for status, input and output arguments.           */
  /*--------------------------------------------------------------------------*/
  IH264VDEC_Status           status;
  /*--------------------------------------------------------------------------*/
  /* Structure for Input/Ouput Arguments for the process call                 */
  /*--------------------------------------------------------------------------*/
  H264VDEC_InArgs    inArgs;
  H264VDEC_OutArgs   outArgs;
  /*--------------------------------------------------------------------------*/
  /*  Input/Output Buffer Descriptors                                         */
  /*--------------------------------------------------------------------------*/
  XDM2_BufDesc  inputBufDesc;
  XDM2_BufDesc  outputBufDesc;
  /*--------------------------------------------------------------------------*/  
  /*  Display Buffer descriptor can be Array type or pointer type. We use     */
  /*  below array allocation when it is configured as embedded type.          */
  /*--------------------------------------------------------------------------*/ 
  
  /*--------------------------------------------------------------------------*/ 
  /*  In case of Dual Enable Mode Codec will provide display buffers in       */
  /*  pointer type configurations.                                            */
  /*  so displayBufs->pbufdec[0] will be normal output (Tiler mode default)   */
  /*     displayBufs->pbufdec[1] wii be in Dual output(raw mode default).     */
  /*  How ever if application wants to set these mode then it can be set as   */
  /*  below:-                                                                 */
  /*  tilerenable  DualOutputEnable Dualtilerenable   buf[0]      buf[1]      */
  /*     0              0                  x         VALID(Raw)   INVALID     */
  /*     1              0                  x         VALID(Tiled) INVALID     */
  /*     0              1                  0         VALID(Raw)   VALID(Raw)  */ 
  /*     1              1                  1         VALID(Tiled) VALID(Tiled)*/
  /*     1              1                  0         VALID(Tiled) VALID(Raw)  */ 
  /*--------------------------------------------------------------------------*/
  IVIDEO2_BufDesc DisplayBuffers[2];
  IVIDEO2_BufDesc *displayBufs;
  /*--------------------------------------------------------------------------*/
  /*  Handle to a buffer element allocated by the buffer manager module       */
  /*--------------------------------------------------------------------------*/
  BUFFMGR_buffEleHandle buffEle;
  BUFFMGR_buffEle buffArray[MAX_BUFF_ELEMENTS];
  XDAS_Int32 numBuffersAllocated;
  /*--------------------------------------------------------------------------*/
  /* Scratch buffer for interleaving the data                                 */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32          fieldBuf;
  IRES_TILEDMEMORY_Obj    iresTiledMemoryObjects[NUM_TILEDMEM_OBJECTS];
  XDAS_UInt32  frameSizeOffset;
  XDAS_UInt32 decodeMode;
#ifdef TEST_SEEK_OP
/**
 * Variables needed for SEEK operation
*/
  XDAS_UInt32 seekIdxCntr, SeekOpStart, SeekBackwd;
#endif
}sChannelState;

#ifdef TEST_SEEK_OP
/**
 * Indicates the frame numbers where all the application want to flush for
 * triggering the SEEK operation
*/
static XDAS_UInt32 frameNumsToStop[12] = {3,30, 140, 200, 240, 613,
                                     756, 843, 933, 1010, 1200, 1375 };                                    
/**
 * Indicates the frame numbers from which application wants to resume the 
 * decoding.
*/
static  XDAS_UInt32 frameNumsToSeek[12] = {7, 40, 170, 120, 250, 452, 543, 620,
                                     760, 899, 935, 1044};  

#endif /* TEST_SEEK_OP */

/** 
********************************************************************************
 *  @fn     TestApp_ReadByteStream
 *  @brief  The function is an Application function to read bitstream
 *
 *  @param[in] finFile  : Pointer to the Input bit-stream file to be read.
 *  @param[in] fsizeFile : Pointer to the frame size file.
 *  @param[in] bytesConsumed : The toal bytes consumbed by the codec till the
 *                             point of this function call.
 *  @return [out] BytesRead  : The number of Bytes that read from file & to be
 *                             supplied to the codec.
********************************************************************************
*/
XDAS_Int32  TestApp_ReadByteStream( FILE   *finFile, 
                                    FILE   *fsizeFile, 
                                    XDAS_UInt32 bytes,
                                    XDAS_Int8   chnlNum
                                  );

/** 
********************************************************************************
 *  @fn     TestApp_SetInitParams
 *  @brief  Function to set default parameters
 *          This function will set default params for params function.
 *          
 *  @param[in] params : pointer to the XDM params interface structure
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void TestApp_SetInitParams(H264VDEC_Params *params,
                                XDAS_Int8        chnlNum);

/** 
********************************************************************************
 *  @fn     TestApp_SetDynamicParams
 *  @brief  Function to set default parameters
 *          This function will set default params for dynamic params function.
 *          
 *  @param[in] params : pointer to the XDM params interface structure
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void TestApp_SetDynamicParams(IVIDDEC3_DynamicParams *dynamicParams,
                                   XDAS_Int8        chnlNum);

/** 
********************************************************************************
 *  @fn     ConfigureProfile
 *  @brief  Configures the entire param file contents into a global buffer,which
 *          is used for parsing and updates the params to given addresses.
 *          
 *  @param[in]  None
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void ConfigureProfile(XDAS_Int8  chnlNum);

/** 
********************************************************************************
 *  @fn     printProfileNums
 *  @brief  
 *          
 *  @param[in] chnlNum      : Decoder channel number.
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void printProfileNums(XDAS_Int8  chnlNum);

/** 
********************************************************************************
 *  @fn     H264Dec_getDataFixedSize
 *  @brief  The function is an Application function to fill input datasync 
 *          parameters for the fixed size datasync mode.
 *  @param[in] XDM_DataSyncHandle  : datasync handle
 *          
 *  @param[in] XDM_DataSyncDesc  : datasync descriptor
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void H264Dec_getDataFixedSize(XDM_DataSyncHandle none, 
                                   XDM_DataSyncDesc *dataSyncParams);

/** 
********************************************************************************
 *  @fn     H264Dec_getDataNALUnits
 *  @brief  The function is an Application function to fill the input datasync 
 *          parameters for the NAL unit datasync mode.
 *
 *  @param[in] XDM_DataSyncHandle  : datasync handle
 *          
 *  @param[in] XDM_DataSyncDesc  : datasync descriptor
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void H264Dec_getDataNALUnits(XDM_DataSyncHandle none,
                                  XDM_DataSyncDesc *dataSyncDesc);

/** 
********************************************************************************
 *  @fn     H264Dec_PutDataSync
 *  @brief  Sample call back function implementation for the putDataSync.
 *          
 *  @param[in] XDM_DataSyncHandle : datasync handle
 *  @param[in] XDM_DataSyncDesc   : pointer to datasync descriptor
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void H264Dec_PutDataSync(XDM_DataSyncHandle none, 
                         XDM_DataSyncDesc *dataSyncParams);

/** 
********************************************************************************
 *  @fn     TestApp_WriteOutputData
 *  @brief  The function is an Application function to write output data 
 *          to a file.
 *
 *  @param[in] fOutFile : Pointer to output file.
 *  @param[in] outArgs  : Pointer to outargs. These args filled in process call.
 *  @param[in] complianceMode : It is used to dump output or compare output
 *                              as provided by reference frame  
 *  @param[in] crcEnable : Enables CRC compare or CRC dump
 *  @return none
********************************************************************************
*/
XDAS_Void TestApp_WriteOutputData
(
  FILE              *fOutFile,
  H264VDEC_OutArgs  *outArgs,
  XDAS_Int8          complianceMode,
  XDAS_Int8          crcEnable,
  XDAS_Int8          chnlNum
);
/** 
********************************************************************************
 *  @fn     TestApp_Write_DualOutputData
 *  @brief  The function is an Application function to write Dual output data 
 *          to a file.
 *
 *  @param[in] fOutFile : Pointer to output file.
 *  @param[in] outArgs  : Pointer to outargs. These args filled in process call.
 *  @param[in] complianceMode : It is used to dump output or compare output
 *                              as provided by reference frame  
 *  @param[in] crcEnable : Enables CRC compare or CRC dump
 *  @return none
********************************************************************************
*/
XDAS_Void TestApp_Write_DualOutputData
(
  FILE              *fDualoutFile,
  H264VDEC_OutArgs  *outArgs,
  XDAS_Int8          complianceMode,
  XDAS_Int8          crcEnable,
  XDAS_Int8          chnlNum
);
/** 
********************************************************************************
 *  @fn     outputDisplayFrame
 *  @brief  The function is Sub function to write output data to a file
 *
 *  @param[in] outArgs  : Pointer to the Input bit-stream file to be read.
 *          
 *  @param[in] xoff : horizontal x-axis offset
 *          
 *  @param[in] yoff : vertical y-axis offset
 *          
 *  @param[in] ref_height : vertical picture size after frame pre-padding
 *          
 *  @param[in] width :  horizontal picture size
 *          
 *  @param[in] height : vertical picture size
 *
 *  @param[in] complianceMode : It is used to dump output or compare output
 *                              as provided by reference frame 
 *  @param[in] crcEnable : Enables CRC compare or CRC dump
 *          
 *  @return none
********************************************************************************
*/
XDAS_Void outputDisplayFrame
( 
  H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff,
  XDAS_Int16 yoff, XDAS_Int16 ref_height,
  XDAS_Int16 width, XDAS_Int16 height, XDAS_Int8 complianceMode,
  XDAS_Int8  crcEnable,
  FILE *fout,
  XDAS_Int8 chnlNum
);
/** 
********************************************************************************
 *  @fn     outputDisplayFrame_dual
 *  @brief  The function is Sub function to write Dual output data to a file
 *
 *  @param[in] fout  : File Pointer to dual output.
 *
 *  @param[in] outArgs  : Pointer to the Input bit-stream file to be read.
 *          
 *  @param[in] xoff : horizontal x-axis offset
 *          
 *  @param[in] yoff : vertical y-axis offset
 *          
 *  @param[in] ref_height : vertical picture size after frame pre-padding
 *          
 *  @param[in] width :  horizontal picture size
 *          
 *  @param[in] height : vertical picture size
 *
 *  @param[in] complianceMode : It is used to dump output or compare output
 *                              as provided by reference frame 
 *  @param[in] crcEnable : Enables CRC compare or CRC dump
 *          
 *  @return none
********************************************************************************
*/

XDAS_Void outputDisplayFrame_dual
( 
  FILE * fout,H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff,
  XDAS_Int16 yoff, XDAS_Int16 ref_height,
  XDAS_Int16 width, XDAS_Int16 height, XDAS_Int8 complianceMode,
  XDAS_Int8  crcEnable,
  XDAS_Int8 chnlNum
);

/** 
********************************************************************************
 *  @fn     outputDisplayField
 *  @brief  The function is Sub  Function to interleave 2 fields.
 *           In case of interlaced or PICAFF streams, the frame is stored as
 *           2 separate field. This function is used to interleaved the 2 fields
 *           and form the frame.The interleaving is done in fieldBuf and is then 
 *           written out.
 *
 *  @param[in] fout    : File pointer to dual output.
 *  @param[in] outArgs    : Pointer to the Input bit-stream file to be read.
 *  @param[in] xoff       : horizontal x-axis offset
 *  @param[in] yoff       : vertical y-axis offset
 *  @param[in] ref_height : vertical picture size after frame pre-padding
 *  @param[in] width      :  horizontal picture size
 *  @param[in] height     : vertical picture size
 *  @param[in] bottom_field_flag :This parameter equal to 1 specifies that the 
 *             slice is part of a coded bottom field. bottom_field_flag equal 
 *             to 0 specifies that the picture is a coded top field.
 *          
 *  @param[in] complianceMode : It is used to dump output or compare output
 *                              as provided by reference frame 
 *  @param[in] crcEnable : Enables CRC compare or CRC dump
 *          
 *  @return : None
********************************************************************************
*/
XDAS_Void outputDisplayField
(
  H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff, 
  XDAS_Int16 yoff, XDAS_Int16 ref_height, 
  XDAS_Int16 width, XDAS_Int16 height,
  XDAS_Int8 complianceMode,
  XDAS_Int8 crcEnable,
  FILE *fout,
  XDAS_Int8 chnlNum
);
/** 
********************************************************************************
 *  @fn     outputDisplayField_Dual
 *  @brief  The function is Sub  Function to interleave 2 fields for dual o/p.
 *           In case of interlaced or PICAFF streams, the frame is stored as
 *           2 separate field. This function is used to interleaved the 2 fields
 *           and form the frame.The interleaving is done in fieldBuf and is then 
 *           written out.
 *
 *  @param[in] fout       : File pointer to dual output.
 *  @param[in] outArgs    : Pointer to the Input bit-stream file to be read.
 *  @param[in] xoff       : horizontal x-axis offset
 *  @param[in] yoff       : vertical y-axis offset
 *  @param[in] ref_height : vertical picture size after frame pre-padding
 *  @param[in] width      :  horizontal picture size
 *  @param[in] height     : vertical picture size
 *  @param[in] bottom_field_flag :This parameter equal to 1 specifies that the 
 *             slice is part of a coded bottom field. bottom_field_flag equal 
 *             to 0 specifies that the picture is a coded top field.
 *          
 *  @param[in] complianceMode : It is used to dump output or compare output
 *                              as provided by reference frame 
 *  @param[in] crcEnable : Enables CRC compare or CRC dump
 *          
 *  @return : None
********************************************************************************
*/
XDAS_Void outputDisplayField_Dual
(
  FILE *fout,H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff, 
  XDAS_Int16 yoff, XDAS_Int16 ref_height, 
  XDAS_Int16 width, XDAS_Int16 height,
  XDAS_Int8 complianceMode,
  XDAS_Int8 crcEnable,
  XDAS_Int8 chnlNum
);
/** 
*******************************************************************************
 *  @fn     outputDisplayRows
 *  @brief  Sample utility function for comparing the raw decoded output with 
 *          reference output data.
 *
 *  @param[in] outArgs    : Pointer to the Input bit-stream file to be read.
 *  @param[in] xoff       : horizontal x-axis offset
 *  @param[in] yoff       : vertical y-axis offset
 *  @param[in] ref_height : vertical picture size after frame pre-padding
 *  @param[in] width      :  horizontal picture size
 *  @param[in] height     : vertical picture size
 *  @param[in] numRows    : Number of rows given for display in the DS call
 *  @param[in] rowNumber  : Row number in Display 
 *  @param[in] picType    : Indicates the picture type
 *          
 *  @return  XDM_EFAIL/XDM_EOK
*******************************************************************************
*/
XDAS_Void outputDisplayRows
( 
  H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff, XDAS_Int16 yoff,
  XDAS_Int16 ref_height, XDAS_Int16 width, XDAS_Int16 height,
  XDAS_UInt32 numRows, XDAS_UInt32 rowNumber, XDAS_Int8 picType,
  XDAS_Int8 chnlNum
);

/** 
********************************************************************************
 *  @fn     MEMUTILS_getPhysicalAddr
 *  @brief  Translates the given Virtual address to physical address
 *          
 *  @param[in]  Addr:
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void *MEMUTILS_getPhysicalAddr(Ptr Addr);

/** 
********************************************************************************
 *  @fn     TestApp_CompareOutputData
 *  @brief  Compares the decoder output data with the reference data provided
 *          by application.
 *          
 *  @param[in]  fRefFile : File pointer to the reference YUV file
 *
 *  @param[in]  outArgs : Pointer to the outArgs structure
 *
 *  @return    None
********************************************************************************
*/
XDAS_Int32 TestApp_CompareOutputData
(
   FILE             *fRefFile,
   H264VDEC_OutArgs *outArgs,
   XDAS_Int8         chnlNum
);

/** 
********************************************************************************
 *  @fn     TestApp_updateIObufDesc
 *  @brief  Updates the Input & Output buffer descriptors for every decode call.
 *          
 *  @param[in]  inputBufDesc : Pointer to the input Buffer Descriptor.
 *  @param[in]  outputBufDesc : Pointer to the output Buffer descriptor
 *  @param[in]  status : Pointer to the status structure.
 *  @param[in]  bytesConsumed : Indicates the bytesConsumed from the input
 *                              buffer till the point.
 *  @param[in]  validBytes : Indicates valid Bytes yet to be consumed by
 *                           codec & available in input buffer.
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void TestApp_updateIObufDesc
(
  XDM2_BufDesc     *inputBufDesc,
  XDM2_BufDesc     *outputBufDesc,
  IVIDDEC3_Status  *status,
  XDAS_UInt32      bytesConsumed,
  XDAS_Int32       validBytes,
  XDAS_Int8        chnlNum,
  XDAS_Int8        outBufsInUseFlag
);

/** 
********************************************************************************
 *  @fn     readparamfile
 *  @brief  Reading the parameters configuration file.
 *          
 *  @param[in]  status : File Pointer to the current config file
 *
 *  @return    None
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname);

/** 
********************************************************************************
 *  @fn     TestApp_ioFilePtrInit
 *  @brief  Sample utility function for comparing the raw decoded output with 
 *          reference output data.
 *
 *  @param[in] fRefFile : Reference file pointer.
 *  @param[in] outArgs  : outArgs structure containing displayable frame.
 *  @param[in] fieldBuf : Scratch buffer for interleaving the data
 *  @param[in] crcEnable : Indicates whether crc is enabled or not
 *  @return 
********************************************************************************
*/
XDAS_Int8 TestApp_ioFilePtrInit(FILE *fpConfig, XDAS_Int8 *testCompliance,
                                XDAS_Int8 *crcEnable,
                                XDAS_Int8  chnlNum);

/** 
********************************************************************************
 *  @fn     TestApp_captureTime
 *  @brief  Capture the time stamp at the interested position.
 *           
 *  @param[in] capLoc : Tells whether before or after the function that to be
 *                      profiled.
 *          
 *  @return None.
********************************************************************************
*/
XDAS_Void TestApp_captureTime(XDAS_UInt32 capLoc);

/** 
********************************************************************************
 *  @fn     TestApp_outputDataXfr
 *  @brief  Sample utility function for comparing the raw decoded output with 
 *          reference output data.
 *
 *  @param[in] fRefFile : Reference file pointer.
 *          
 *  @param[in] outArgs  : outArgs structure containing displayable frame.
 *          
 *  @param[in] testCompliance : Scratch buffer for interleaving the data
 *          
 *  @param[in] crcEnable : Indicates whether crc is enabled or not
 *
 *  @return 
********************************************************************************
*/
XDAS_Int8 TestApp_outputDataXfr( FILE *foutFile, FILE *frefFile,
                                 H264VDEC_OutArgs  outArgs,
                                 XDAS_Int8         testCompliance,
                                 XDAS_Int8         crcEnable,
                                 XDAS_Int8         chnlNum
                               );

/** 
********************************************************************************
 *  @fn     TestApp_checkErr
 *  @brief  Checks whether error message contains the given error value.
 *
 *  @param[in] fRefFile : Reference file pointer.
 *          
 *  @return XDAS_TRUE or XDAS_FALSE
********************************************************************************
*/
XDAS_Bool TestApp_checkErr(XDAS_Int32 errMsg, XDAS_Int32 errVal);

/** 
********************************************************************************
 *  @fn     TestApp_errorReport
 *  @brief  Printing all the errors that are set by codec
 *
 *  @param[in] errMsg : Error message.
 *          
 *  @return  None.
********************************************************************************
*/
XDAS_Void TestApp_errorReport(XDAS_Int32 errMsg);

/** 
********************************************************************************
 *  @fn     TestApp_DMMinit
 *  @brief  DMM initialization needs to be done in case of tiler is enabled.
 *          This is needed only in case running on OMPAP4 SDC.
 *
 *  @param[in]  : None
 *          
 *  @return none
********************************************************************************
*/
XDAS_Void TestApp_DMMinit();

/** 
********************************************************************************
 *  @fn     TestAppMetaDataBuf
 *  @brief  The TestAppMetaDataBuf function is called by the test application to
 *          initialise the Meta data buffers allocation and corresponding
 *          initializations of global buffer arrays.
 *          
 *  @param[in] bufSizes  : Address of array containing the buffer sizes of the 
 *                         numbufs.
 *          
 *  @return Success(0)/failure(-1) in allocating and initialising
********************************************************************************
*/
XDAS_Int32 TestAppMetaDataBuf(XDM2_BufSize *bufSizes,XDAS_Int8  chnlNum);

/** 
********************************************************************************
 *  @fn     testAppTilerInit
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
XDAS_Void testAppTilerInit(XDM2_BufSize *bufSizes,XDAS_Int8  chnlNum);

/** 
********************************************************************************
 *  @fn     paramBoundaryCheck
 *  @brief  main function of Host TestAppDecoder
 *          
 *  @param[in] retVal       : Indicates the value returned by create call or
 *                            control call.
 *  @param[in] checkLevel   : Indicates the check & exit points during param
 *                            boundary checks validation.
 *          
 *  @return None
********************************************************************************
*/
XDAS_Int8 paramBoundaryCheck(XDAS_Int8 retVal, XDAS_Int8 checkLevel, 
                            XDAS_Int8 chnlNum);

/** 
********************************************************************************
 *  @fn     updateConfigStatusFile
 *  @brief  Function to update the log file which captures the status of each
 *          config.
 *          
 *  @param[in] status       : Indicates the PASS or FAIL status of the current
 *                            configuration.
 *          
 *  @return None
********************************************************************************
*/
XDAS_Void updateConfigStatusFile(XDAS_Int8 status);

/** 
********************************************************************************
 *  @fn     testAppFlushFrames
 *  @brief  Flush implementation 
 *          
 *  @param[in] inputBufDesc : Pointer to the input Buffer descriptor
 *  @param[in] outputBufDesc: Pointer to the output Buffer descriptor
 *  @param[in] displayBufs  : Pointer to the display Buffers descriptor
 *          
 *  @return None
********************************************************************************
*/
XDAS_Int8 testAppFlushFrames(XDM2_BufDesc *inputBufDesc, 
                              XDM2_BufDesc *outputBufDesc,
                              IVIDEO2_BufDesc *displayBufs,
                              XDAS_Int8  chnlNum);

/** 
********************************************************************************
 *  @fn     TestApp_checkErr
 *  @brief  Checks whether the errors resulted in process call force application
 *          application to initiate flush operation.
 *
 *  @param[in] errMsg : Error message returned by process call.
 *          
 *  @return XDAS_TRUE or XDAS_FALSE
********************************************************************************
*/
XDAS_Bool TestApp_flushCheck(XDAS_Int32 errMsg);

/**
********************************************************************************
 *  @func   IVAHD_Standby_power_on_uboot
 *
 *  @brief  This function puts given IVAHD in standby after power on during
 *          booting process of given SoC
 *
 *  @param  None
 *
 *  @return TRUE/FALSE
 *
 *  @note   Please make to define address as per given SoC, IVAHD# and MMU
 *          Setting
********************************************************************************
*/
XDAS_Void IVAHD_Standby_power_on_uboot();


#ifdef MEM_CORRUPTION_TEST
/** 
********************************************************************************
 *  @fn            H264DEC_ScratchMemoryCorruption
 *  @brief         This function does scratch corruption of SL2, ITCM, DTCM 
 *                 and IP Memories
 *  @param[in] void : None
 *          
 *  @return         : None
********************************************************************************
*/
XDAS_Void H264DEC_ScratchMemoryCorruption();

/** 
 *******************************************************************************
 *  @fn     TestApp_turnOffClocks
 *
 *  @brief This function turns off the clocks for all the required IPs for 
 *         decoding. Note that here we dont check whether the clock is already 
 *         disabled or not. 
 *        
 *         In ordert o completly disable the clock, we need to make sure some 
 *         of these things.
 *          -# All IPs interrupts need to be cleared. This mostly happens in 
 *             LSE IPs. So clear all the interrupts before turing off the clock 
 *          -# For ECD in error case we need to do reset. This currently we are 
 *             doing even for normal case                   
 *
 *  @param[in] : none 
 *
 *  @return : APP_EOK/APP_EFAIL
 *******************************************************************************
*/
XDAS_UInt32 TestApp_turnOffClocks();

/** 
 *******************************************************************************
 *  @fn    TestApp_turnOnClocks
 *
 *  @brief This function turns on the clocks for all the required IPs for 
 *         decoding. Note that here we dont check whether the clock is already 
 *         enabled or not. 
 *
 *  @param[in] : none 
 *
 *  @return : APP_EOK/APP_EFAIL
 *******************************************************************************
*/
XDAS_UInt32 TestApp_turnOnClocks();
#endif
#endif


