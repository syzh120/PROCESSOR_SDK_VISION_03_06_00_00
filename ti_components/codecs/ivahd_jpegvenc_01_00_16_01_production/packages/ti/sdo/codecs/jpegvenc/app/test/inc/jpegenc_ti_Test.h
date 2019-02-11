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
* @file      jpegenc_ti_Test.h
*
* @brief     This header contains declarations that are specific to
*            this implementation and which do not need to be exposed
*            in order for an application to use the JPEGVENC algorithm.
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
*******************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/
#ifndef JPEGENC_TI_TEST_H
#define JPEGENC_TI_TEST_H


/**
*  Macro defining the maximum number of parameters to be parsed from the input
*  configuration file
*/
#define MAX_ITEMS_TO_PARSE              512

/**
* File Name String Size
*/
#define STRING_SIZE                     250

#define MAX_SUPPORT_WIDTH               4320
#define MAX_SUPPORT_HEIGHT              4096
#define MAX_RESOLUTION                  (MAX_SUPPORT_WIDTH * MAX_SUPPORT_HEIGHT)


/**
* This macro defines the maximum size for
* config file data buffer
*/
#define MAX_CONFIG_FILE_BUF_SIZE        20000

#define ALIGN_16(a)                     (a + 15) & ~(0x0F);

/**
* Version Data Buffer size
*/
#define VERSION_DATA_BUF_SIZE           200
/**
* Memory for input and output buffers. This memory is allocated in heap.
* A worst case of 4096x4096 image with 444 is considered.
* A worst case compression ratio of 2:1 (50%) is considered
*/
#define MAX_IO_MEMORY                   (4320*4096*3 + 4320*2048 + 10240)

/*******************************************************************************
*   INCLUDE FILES
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
#include <jpegenc_ti_config.h>
#include <jpegenc_ti_api.h>
#include <jpegenc_ti.h>

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
/**
*******************************************************************************
*  @struct _sTokenMapping
*
*  @brief  Token Mapping structure for parsing codec specific
*          configuration file
*
*  @param  place        : Place Holder for the data
*  @param  tokenName    : String name in the configuration file
*******************************************************************************
*/
typedef struct _sTokenMapping{
  char *tokenName;
  XDAS_Void *place;
  XDAS_Int32 type;
} sTokenMapping;

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/
XDAS_Void testAppTilerInit(XDM2_BufSize *bufSizes);

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
char *GetConfigFileContent (FILE *fname);

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
XDAS_Int32 ParameterNameToMapIndex (char *s);

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
*
*@return Pass/Fail
********************************************************************************
*/
XDAS_Int32 ParseContent (char *buf, XDAS_Int32 bufsize);

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
XDAS_Int32 readparamfile(FILE * fname);

/**
********************************************************************************
*  @fn  TestApp_ReadInput_444P_YUVData(IVIDEO2_BufDesc *inputBuf,
*                                      short frmWidth, short frmHeight,
*                                      int frameCount, FILE * fin)
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
short frmWidth, short frmHeight,int frameCount, FILE * fin);

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
short frmWidth, short frmHeight,int frameCount, FILE * fin);

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
short frmWidth, short frmHeight,int frameCount, FILE * fin);

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
short frmWidth, short frmHeight,int frameCount, FILE * fin);

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
short frmWidth, short frmHeight,int frameCount, FILE * fin);

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
short frmWidth, short frmHeight,short extWidth, short extHeight,int frameCount, 
FILE * fin);

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
FILE *fout);

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
XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,XDM2_BufDesc *outputBufDesc,
JPEGVENC_OutArgs *outArgs);

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

XDAS_Void TestApp_SetInitParams(JPEGVENC_Params *params,
JpegBPEncConfig *config);

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
*  @param[in]   inputArgs     : Pointer to inArgs Structure
*
*  @return      none
********************************************************************************
*/

XDAS_Void TestApp_SetDynamicParams(JPEGVENC_DynamicParams *dynamicParams,
JpegBPEncConfig *config, IJPEGVENC_InArgs *inputArgs);

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
XDAS_Void JPEGVENC_TI_UpdateGetDataCallBack(XDM_DataSyncHandle ptr,
XDM_DataSyncDesc *dataSyncDescrRowLevel);

/**
********************************************************************************
*  @fn     JPEGVENC_TI_UpdateGetBufferCallBack(  XDM_DataSyncHandle ptr,
              XDM_DataSyncDesc *dataSyncDescrFixedLength )
*
*  @brief    This function asks the appliction for a new buffer for stream.
*
*  @param[in]  ptr  : Pointer to the IALG_Handle structure
*
*  @param[in]  dataSyncDescrFixedLength : Pointer to the data sync descriptor
*
*  @return None
********************************************************************************
*/
XDAS_Void JPEGVENC_TI_UpdateGetBufferCallBack( XDM_DataSyncHandle ptr,
XDM_DataSyncDesc* dataSyncDescrFixedLength);

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
XDM_DataSyncDesc* putDataSyncDescr);



#endif             /* JPEGVENC_TI_TEST_H */
