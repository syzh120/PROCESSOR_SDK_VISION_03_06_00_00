/*
********************************************************************************  
* HDVICP2.0 Based JPEG Decoder
*
* "HDVICP2.0 Based JPEG Decoder" is software module developed on
* TI's HDVICP2 based SOCs. This module is capable of generating a raw image 
* by de-compressing/decoding a jpeg bit-stream based on ISO/IEC IS 10918-1. 
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
* ALL RIGHTS RESERVED 
********************************************************************************
*/

/**  
********************************************************************************
* @file      jpegvdec_ti_hosttestapp.h                        
*
* @brief     This is the top level client file that drives the JPEG
*            Decoder Call using XDM v1.0 Interface.This is the Application file
*            where user is allowed to change so as to give various kind of 
*            inputs and check the behaviour of the codec.
*            Ex : 1. Thumbnail is proper or not can be checked by enabling the 
*                    dynamic parameter specified in this file.
*                 2. Downsample / Tiler can be verified 
*            Algorithm Instance creation happens here , once this is done we 
*            call the Resource Manager to assign the resources , then depending
*            on the chroma format we ask for the memory requirement to 
*            GETBUFINFO and then allocate it for input and output and use it 
*            accordingly. Process call happens after these things happened 
*            properly.
*
* @author    Odanaka
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
*
* @version 0.1 (Dec 2009) : Updated Macros[Chetan]
*
* @version 0.2 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan] 
*
* @version 0.3 (July 2010) : Added support for Data Sync[pavan]
*
* @version 0.4 (July 2010) : Added Tiler.lib support and Non-Interleaved 
*                           [Chetan]
*
*******************************************************************************
*/

/* ---------------------compilation control switches -------------------------*/
#ifndef __JPEG_TESTAPP_H__
#define __JPEG_TESTAPP_H__

#undef  TST_FRAME_MODE

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>
#include <ti/xdais/dm/ividdec3.h>


/*----------------------program files ----------------------------------------*/
#include "ijpegvdec.h"

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/* ------------------------------ macros ------------------------------------ */

/**
* Maximum width in pixels supported for HD standard is 1920                  
*/
#define IMAGE_WIDTH            (4096)
/**
* Maximum height in pixels supported for HD standard standard is 1088       
*/
#define IMAGE_HEIGHT           (4096)
/**
* this is the value needed to initialize framerate in setparams . this is not 
* needed as our application is JPEG      
*/
#define MAX_FRAME_RATE           (300000) 
/**
* this is the value needed to initialize bitrate in setparams . this is not
* needed as our application is JPEG      
*/
#define MAX_BIT_RATE           (10000000)   
/**
* This Macro defines whether the function has passed succesfully or not
*/
#define PASS                                 (1)
/*----------------------------------------------------------------------------*/
/* Buffer size required for CB and CR for 4:2:0 formate is half               */
/* of picture size in pixels                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* If the Input is 444 ( worst case is this beacuse it has no subsampling) .  */
/* To support 4096x4096 in this case , We require  4096*4096*3 Output Buffer ,*/
/* and assuming 50% compression , we will allocate 4096*2048 for Input Buffer */
/* So we require the memory space = 4096*4096*3 + 4096*2048                   */
/*----------------------------------------------------------------------------*/
#define LUMA_BUFFER_SIZE       (IMAGE_WIDTH*IMAGE_HEIGHT)
#define CHROMA_BUFFER_SIZE     (LUMA_BUFFER_SIZE )

/**
* The number of characters that can be parsed by the config file parser.     
*/
#define STRING_SIZE            (256)

#define MAX_READ        0x007FFF80
#define FILENUMLENMAX   256
#define DDRBASE         0xD0000000

/**
* Processer running frequency                                              
*/
#define     CLOCK_SEC               (180000000)

#define ENABLE                              (1)

#define DISABLE                             (0)  

#define MAX_ITEMS_TO_PARSE  1000
/**
* Maximum number of characters to be read                                    
*/
#define     MAX_CHAR_READ               (254)
/**
* This macro defines the size of the buffer which is used to call GETVERSION 
* function
*/
#define MAX_VERSION_BUF_SIZE            (200)
/**
* Number of Outbuffer for 444 chroma format
*/

#define  NUM_OUTBUF_JPEG_444                    (3)

/**
* Number of Outbuffer for 420 chroma format
*/
#define  NUM_OUTBUF_JPEG_420                    (2)

/**
* Number of Outbuffer for 422 chroma format
*/
#define  NUM_OUTBUF_JPEG_422                    (1)
/**
* Defines the output chroma format value which JPEG 444 takes
*/
#define  CHROMA_OUTBUF_JPEG_444                    (5)

/**
* Defines the output chroma format value which JPEG 420  takes
*/
#define  CHROMA_OUTBUF_JPEG_420                    (9)

/**
* Defines the output chroma format value which JPEG 422 hori  takes
*/
#define  CHROMA_OUTBUF_JPEG_422_HORI                    (3)

/** 
* Macro to round a number to nearest bigger multiple of 16 value.     
*/
#define ROUND_TO_NEXT_MULT16(value)   (((value + 15) >> 4) << 4)

/** 
* Macro to use TILER8   
*/
#define TILER8_SOURCE_PITCH              (16*1024)

/** 
* Macro to use TILED16 for Output
*/
#define TILER16_SOURCE_PITCH              (32*1024)

/**
*  Set the VDMA View based on the Host Type
*/
#if defined(HOSTARM968_FPGA)
#define VDMAVIEW_EXTMEM      (0x07FFFFFF)

#elif defined(HOSTCORTEXM3_OMAP4)
#define VDMAVIEW_EXTMEM      (0xFFFFFFFF) 

#elif defined(HOSTCORTEXM3_NETRA_IVAHD0)
#define VDMAVIEW_EXTMEM      (0xFFFFFFFF) 

#elif defined(HOSTCORTEXM3_NETRA_IVAHD1)
#define VDMAVIEW_EXTMEM      (0xFFFFFFFF)

#elif defined(HOSTCORTEXM3_NETRA_IVAHD2)
#define VDMAVIEW_EXTMEM      (0xFFFFFFFF)

#elif defined(HOSTCORTEXM3_GAIA)
#define VDMAVIEW_EXTMEM      (0x1FFFFFFF)
#else
#define VDMAVIEW_EXTMEM      (0x07FFFFFF)
#endif

/**
*******************************************************************************
*  @struct _sTokenMapping
*
*  @brief  Token Mapping structure for parsing codec specific
*          configuration file
*
*  @param  tokenName    : String name in the configuration file
*
*  @param  place        : Place Holder for the data
* 
*******************************************************************************
*/

typedef struct _sTokenMapping
{
  XDAS_Int8 *tokenName;
  XDAS_Void *place;
} sTokenMapping;

/**
*******************************************************************************
*  @struct PCIFILE
*
*  @brief  Token Mapping structure for parsing codec specific
*          configuration file
*
*  @param  fname    : String name in the configuration file
*
*  @param  pos      : Place Holder for the data
* 
*  @param  mode     : Place Holder mode for the data
*
*******************************************************************************
*/

typedef struct PCIFILE
{
  unsigned char fname[FILENUMLENMAX];
  unsigned int pos;
  unsigned char mode[1];
}PCIFILE;

/* ---------------------- function prototypes ----------------------------- */



#ifndef USE_PCI
#define FOPEN   fopen
#define FCLOSE  fclose
#define FREAD   fread
#define FWRITE  fwrite
#define FSEEK   fseek
#define FTELL   ftell
#define FFLUSH  fflush
typedef FILE MYFILE;
#else
#define FOPEN   PCIopen
#define FCLOSE  PCIclose
#define FREAD   PCIread
#define FWRITE  PCIwrite
#define FSEEK   PCIseek
#define FTELL   PCItell
#define FFLUSH  PCIflush
typedef PCIFILE MYFILE;
#endif

/**
********************************************************************************
*  @fn          TestApp_EnableCache()
*
*  @brief       Enable cache settings for system
*
*  @return      None
********************************************************************************
*/
XDAS_Void TestApp_EnableCache(void);

/**
********************************************************************************
*  @fn          TestApp_ReadByteStream(XDAS_Int8 *inFile,
*                                      XDM2_BufDesc inputBufDesc)
*
*  @brief       Sample utility function for reading encoded bit-stream in 
*               chunks.The input file is opened every time and next 
*               "INPUT_BUFFER_SIZE - validBytes" number of bytes is read into 
*               the  input buffer. End-of-file if encountered in previous runs 
*               is remebered for given input config record.
*
*  @param [in]  inFile            :  Input file name as a null-terminated 
*                                    array of characters.
*
*  @param [in]  inputBufDesc      :  This advanced buffer uses the 
*                                    XDM2_SingleBufDesc, and is typically used 
*                                    for codecs which must reflect <i>types</i>
*                                    of memory.  For example, video/image codecs
*                                    may need to indicate whether tiled memory 
*                                    is used.
*
*  @return      TotalBytes in the input bit-stream : If successfully read.
*               -1: If encountered error in reading the input file.
********************************************************************************
*/
#ifdef TST_FRAME_MODE
XDAS_Int32 TestApp_ReadByteStream( XDAS_Int8 *inFile, XDM2_BufDesc inputBufDesc,
FILE  *fsizeFile, XDAS_Int32 frameCount );
#else
XDAS_Int32 TestApp_ReadByteStream(XDAS_Int8 *inFile,XDM2_BufDesc inputBufDesc);
#endif

/**
********************************************************************************
*  @fn          readparamfile(FILE * fname)
*
*  @brief       Parses the config parametr file and stores the value in global 
*               structure (sTokenMapping sTokenMap).
*
*  @param [in]  fname             :  Confile parameter file pointer.
*
*  @return      status            :  ( PASS/ FAIL)  
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname);


/**
********************************************************************************
*  @fn          TestApp_WriteOutputData( MYFILE             *fOutFile,
*                                        IJPEGVDEC_OutArgs *outArgs )
*
*  @brief       Sample utility function for dumping decode output. Depdending on 
*               chroma format , we will dump the yuv's. For Ex : 444 , we will
*               have to sump all 3 buffers one after the other 
*
*  @param [out]  fOutFile         :  Output file pointer
*
*  @param [in]  outArgs           :  OutArgs structure containing display 
*                                    buffer array and thier  properties like 
*                                    picture pitch, heigth and width.
*
*  @return      None.
********************************************************************************
*/
XDAS_Void TestApp_WriteOutputData
(
MYFILE             *fOutFile,
IJPEGVDEC_OutArgs *outArgs
);

/**
********************************************************************************
*  @fn          TestApp_CompareOutputData(FILE             *fOutFile,
*                                         IJPEGVDEC_OutArgs *outArgs)
*
*  @brief       This compares the output by checking with the reference output. 
*               We divide the output buffer into 3 buffers , luma , cb and cr.
*               Then depdending on the chroma format we compare the output of
*               decoded luma buffer with the reference , if it matches , then 
*               comparison is done for Cb and Cr in the same manner.
*               (Not yet tested)
*
*  @param [out]  fOutFile         :  Output file pointer
*
*  @param [in]  outArgs           :  OutArgs structure containing display 
*                                    buffer array and thier  properties like 
*                                    picture pitch, heigth and width.
*
*  @return      PASS/FAIL
********************************************************************************
*/
XDAS_Int32 TestApp_CompareOutputData
(
FILE             *fOutFile,
IJPEGVDEC_OutArgs *outArgs
);

/**
********************************************************************************
*  @fn          TestApp_WriteOutputDataTiled16(MYFILE           *fOutFile,
*                                       IJPEGVDEC_OutArgs *outArgs)
*
*  @brief       Sample utility function for dumping decode output. Depdending on 
*               chroma format , we will dump the yuv's. For Ex : 444 , we will
*               have to dump all 3 buffers one after the other 
*
*  @param [out]  fOutFile         :  Output file pointer
*
*  @param [in]  outArgs           :  OutArgs structure containing display 
*                                    buffer array and thier  properties like 
*
*  @return      None.
********************************************************************************
*/
XDAS_Void TestApp_WriteOutputDataTiled16
(
MYFILE           *fOutFile,
IJPEGVDEC_OutArgs *outArgs
);


/**
********************************************************************************
*  @fn          TestApp_SetInitParams(IVIDDEC3_Params *Params)
*
*  @brief       Initalizes the init parameter structure with proper values
*
*  @param [out]   params             :  Init parameter structure.
*
*  @return      None
********************************************************************************
*/
XDAS_Void TestApp_SetInitParams(IVIDDEC3_Params *Params);

/**
********************************************************************************
*  @fn          TestApp_SetDynamicParams(IJPEGVDEC_DynamicParams *DynamicParams)
*
*  @brief       Initalizes the Dynamic parameter structure with proper values
*
*  @param[out]   dynamicParams     :  Init Dynamic parameter structure.
*
*  @return      None
********************************************************************************
*/
XDAS_Void TestApp_SetDynamicParams(IJPEGVDEC_DynamicParams *DynamicParams);

/****************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------data declarations -----------------------------------*/

/**
********************************************************************************
*  @fn     JPEGVDEC_TI_PutDataCallBack(  XDM_DataSyncHandle ptr,
*                                       XDM_DataSyncDesc *dataSyncDescrRowLevel)
*
*  @brief    This function is call back function. This function copies the YUV 
*            data to a temporary buffer. Later temporary buffer will be copied 
*            into an output file once all the ROWs has been decoded.
*
*  @param[in]  ptr  : Pointer to the IALG_Handle structure
*
*  @param[in]  dataSyncDescrRowLevel : Pointer to the data sync descriptor
*
*  @return None
********************************************************************************
*/
XDAS_Void JPEGVDEC_TI_PutDataCallBack(XDM_DataSyncHandle ptr,
XDM_DataSyncDesc *dataSyncDescrRowLevel);

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
void SetPATViewMapBase();

/** 
********************************************************************************
*  @fn     testAppTilerInit(XDM2_BufSize *bufSizes)
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
XDAS_Void testAppTilerInit(XDM2_BufSize *bufSizes);

/**
********************************************************************************
*  @fn     JPEGVDEC_TI_GetDataCallBack(  XDM_DataSyncHandle ptr,
*                                    XDM_DataSyncDesc *dataSyncDescrFixedLength)
*
*  @brief    This function is call back function. This function is called  
*            when IVAHD is in need of stream.
*
*  @param[in]  ptr  : Pointer to the IALG_Handle structure
*
*  @param[in]  dataSyncDescrFixedLength : Pointer to the data sync descriptor
*
*  @return None
********************************************************************************
*/
XDAS_Void JPEGVDEC_TI_GetDataCallBack( XDM_DataSyncHandle ptr,
XDM_DataSyncDesc* dataSyncDescrFixedLength);
/**
********************************************************************************
*  @fn     JPEGVDEC_PutBuffer(  XDM_DataSyncHandle putDataHandle,
*                                    XDM_DataSyncDesc *dataSyncParams)
*
*  @brief    This function is call back function. This function is called  
*            when IVAHD is in need of stream.
*
*  @param[in]  putDataHandle  : Pointer to the IALG_Handle structure
*
*  @param[in]  dataSyncParams : Pointer to the data sync descriptor
*
*  @return None
********************************************************************************
*/

XDAS_Void JPEGVDEC_PutBuffer(XDM_DataSyncHandle putDataHandle, 
                            XDM_DataSyncDesc *dataSyncParams);

#endif /* #ifndef __JPEG_TESTAPP_H__ */
