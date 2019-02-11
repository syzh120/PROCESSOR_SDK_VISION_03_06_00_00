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
* @file      jpegvdec_ti_hosttestapp.c                         
*
* @brief     This is the top level client file that drives the JPEG
*            Decoder Call using XDM v1.0 Interface. This is the Application file
*            which the user can change so as to give various kinds of 
*            inputs and check the behaviour of the codec.
*            Ex : 1. Thumbnail is proper or not can be checked by enabling the 
*                    dynamic parameter specified in this file.
*                 2. Downsample only can be verified 
*            Algorithm Instance creation happens here , once this is done we 
*            call the Resource Manager to assign the resources , then depending
*            on the chroma format we ask for the memory requirement to 
*            GETBUFINFO and then allocate it for input and output and use it 
*            accordingly. Process call happens after these things happened 
*            properly.
*
* @author    Chetan
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
* 
* @version 0.1 (Dec 2009) : Added support for all chroma formats , rectified
*                           memory allocation for resolution of 4k x 4k
*
* @version 0.2 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan]
*
* @version 0.3 (July 2010) : Added support for Data Sync [Pavan]
*
* @version 0.4 (July 2010) : Added Tiler.lib support and Non-Interleaved 
*                           [Chetan]
* 
* @version 0.5 (Nov 2010) : Added support for Slice level decoding[Chetan] 
*
* @version 0.6 (Jan 2012) : Updated input read routene [Naidu]
*
********************************************************************************
*/

/*----------------------compilation control switches -------------------------*/

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/*--------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tilerBuf.h>

/*----------------------program files ----------------------------------------*/
#include "jpegvdec_ti.h"
#include "jpegvdec_ti_api.h"
#include "jpegvdec_ti_hosttestapp.h"
#include "jpegvdec_rman_config.h"
#define MIN_VERSION_BUF_SIZE 107
#ifdef PROFILE_HOST

#define IVA_CLOCK_FREQ       533.0
#define M3_CLOCK_FREQ        250000000

/** 
*  Macro defining address of TIMER init module 
*/
#define ICEC_CNT_CTRL     (*(volatile int*)(0x58040000 + 0x00040))

/** 
*  Macro defining address of capture time register in ICE CRUSHER
*/
#define ICEC_CNT_VAL      (*(volatile int*)(0x58040000 + 0x00044))

/** 
*  Macro defining address of M3 TIMER init module 
*/
#define SYSTICKREG        (*(volatile int*)0xE000E010)
#define SYSTICKREL        (*(volatile int*)0xE000E014)
#define SYSTICKVAL        (*(volatile int*)0xE000E018)
#define SYSTICKRELVAL     0x00FFFFFF

#endif//PROFILE_HOST
/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/
/**
* The maximum number of frames decoded by the decoder. This macro is added
* for debug purpose. This macro will be useful in limitting the number of
* frames to be decoded during testing
*/
XDAS_UInt32                 framesToDecode;
XDAS_UInt32                 i;
/**
* The frames number from which output need to be dumped. This macro is added
* for debug purpose. This macro will be useful in limitting the number of
* frames to be dumped during testing
*/
XDAS_UInt32                 dumpFrom;

/**
* Memory for input and output buffers. This memory is allocated in heap.
* A worst case of 4096x4096 image with 444 is considered.
* A worst case compression ratio of 2:1 (50%) is considered
*/
#define MAX_IO_MEMORY      (4096*4096*3) 
#define  INPUT_BUFFER_SIZE   0x780000                                                  
#pragma    DATA_SECTION(globalMemory, ".io_buffer")

/* Added for output data sync */
#pragma    DATA_SECTION(PartialOutLuma,   ".temp_buffer")
XDAS_Int8  PartialOutLuma[4096*4096*3];

#pragma     DATA_SECTION(inputData, ".input_buffer")

XDAS_Int8   inputData[INPUT_BUFFER_SIZE];                                                                       
XDAS_UInt8                 globalMemory[MAX_IO_MEMORY];
XDAS_UInt8                 *pBufferIo;

/**
* This buffer holds the seperated out Cb Cr component - useful for dumping
* the decoded output to a file stream - this array can be avoided if CbCr
* need nto be seperated before writing the the outptu file
* CHROMA_BUFFER_SIZE depends on the maximum picture size supported and is
* defined in TestAppDecoder.h
*/
#pragma    DATA_SECTION(chromaSeperate, ".chroma_buffer")
XDAS_Int8  chromaSeperate[2 * LUMA_BUFFER_SIZE];

IJPEGVDEC_Params             params;
IJPEGVDEC_DynamicParams      dynamicParams;
/**
* This global array of structure elements define the format of
* config file being used. User needs to modify this array either
* by adding new elements or by deleting existing elements in
* correspondence to the changes required in parameters configuration
* cfg file
*/
sTokenMapping sTokenMap[] =
{
  {(XDAS_Int8 *)"FramesToDecode",   &framesToDecode                         },
  {(XDAS_Int8 *)"DumpFrom",         &dumpFrom                               },
  {(XDAS_Int8 *)"ImageHeight",      &params.viddecParams.maxHeight          },
  {(XDAS_Int8 *)"ImageWidth",       &params.viddecParams.maxWidth           },
  {(XDAS_Int8 *)"ChromaFormat",     &params.viddecParams.forceChromaFormat  },
  {(XDAS_Int8 *)"rangeReduction",      &dynamicParams.rangeReduction        },
  {(XDAS_Int8 *)"sliceSwitchON",      &params.sliceSwitchON            },
  {(XDAS_Int8 *)"ErrorConcealmentON",  &params.ErrorConcealmentON  },
  {(XDAS_Int8 *)"debugTraceLevel",     &params.debugTraceLevel  },
  {(XDAS_Int8 *)"lastNFramesToLog",     &params.lastNFramesToLog  },
  {(XDAS_Int8 *)"numSwitchPerFrame",     &params.numSwitchPerFrame  },
  {(XDAS_Int8 *)"numRestartMarkerPerSwitch",&params.numRestartMarkerPerSwitch },
  {NULL,                                                            NULL}
};


XDAS_Int8 tilerEnable = 1;
XDAS_Int8 chromaTilerMode = 0;
XDAS_UInt32  frameSizeOffset =0;
/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

sTilerParams             tilerParams;

/**
* Total number of valid Bytes still left over in the input bit-stream
* buffer. This values is first initialised to the total bytes read from
* the input file and it keeps getting decremented as the data is consumed
* by every successive process call. It is also used to signal error in
* reading the input file
*/
XDAS_Int32  validBytes;

/**
* Stores the total bytes consumed by the decoder from the encoded input
* bit-stream during previous process call.
*/
XDAS_UInt32 bytesConsumed;
XDAS_UInt32 bytesConsumed_total;
/**
* Used as a boolean flag to indicate if the end-of-input-encoded bit-stream
* file has been encountered.
*/
XDAS_UInt32 reachedEndOfFile;

/**
* Offset in the input file from where next read happens
*/
XDAS_UInt32 fileOffset;
XDAS_Int32  countConfigSet;
Uint32 initialFrame;
/**
* This buffer holds the reference Luma component - useful for comparing
* with reference of the decoded output.LUMA_BUFFER_SIZE calculated depends on
* the maximum picture size supported and is defined in TestAppDecoder.h
*/
#pragma    DATA_SECTION(refBuffer, ".ref_buffer")
XDAS_Int8 refBuffer[LUMA_BUFFER_SIZE];

/*------------------------------- macros ------------------------------------ */

/*----------------------------------------------------------------------------*/
/*  Global flag for non-blocking call.                                        */
/*----------------------------------------------------------------------------*/
extern IRES_HDVICP2_Obj IRES_HDVICP2_handle;
/* For Input Data Sync*/
#define NUM_INPUT_BLOCKS (32)
unsigned int bytes_ddr, curr_ddr_bytes, OutFlag;

XDAS_Int8* curr_ddr_addr[NUM_INPUT_BLOCKS];

/*----------------------------------------------------------------------------*/
/* 'blockSizeArray' used for the input data sync which provides the block     */
/*  sizes in each data sync call.                                             */
/*----------------------------------------------------------------------------*/
/*XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS] = {
  3072,512,512,512,512,1024,2175,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

XDAS_UInt32 blockPerDataSync[10] = {3,4,0,0,0,0,0,0,0,0};*/
//XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS] = {
  //690,690,94,900,951,1110,1109,1091,1421,232,0,0,0,0,0,0,
  //1459,915,951,1110,1109,1091,1421,232,0,0,0,0,0,0,0,
 // 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  //XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS] = {
 // 8192,8192,8192,8192,8192,8192,8192,8192,8192,8192,8192,8192,3059,1529,0,0,0,0,0,0,
 // 0,0,0,0,0,0,0,0,0,0,0,0};
 
 XDAS_UInt32 blockSizeArray[32] = {8192,8192,8192,8192,8192,8192,8192,8192,8192,
                                   8192,8192,8192,8192,8192,8192,8192,
                                   8192,8192,8192,8192,8192,8192,8192,8192,8192,
                                   8192,8192,8192,8192,8192,3059,1529};
  
// XDAS_UInt32 blockSizeArray[32] = {8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,
             //                     8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,8145,3059,1529};
    
//XDAS_UInt32 blockSizeArray[32] = {7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,
//                                  7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,7145,3059,1529};
    
//XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS] = {
 // 8192,8192,8192,8192,8192,8192,8192,8192,8192,8192,8192,8192,3059,1529,0,0,0,0,0,0,
  //0,0,0,0,0,0,0,0,0,0,0,0};
//XDAS_UInt32 blockPerDataSync[20] = {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0};  
//XDAS_UInt32 blockPerDataSync[20] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0}; 
XDAS_UInt32 blockPerDataSync[32] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                   1,1,1,1,1,1,1,1,1,1};

XDAS_UInt32 GblCount = 0;

XDAS_UInt32 AccCount = 0;
XDAS_UInt32 SlcSwitchCount = 0;

XDAS_UInt32 StartBlock = 0;
/* For Output Data Sync*/
IJPEGVDEC_OutArgs   outArgs;

volatile XDAS_Int32      unServMesgCount;
volatile XDAS_Int32      ServMesgCount;
XDAS_Int32 putBufferCount;
/*----------function prototypes ----------------------------------------------*/

/**
********************************************************************************
*  @fn          main
*
*  @brief       Sample main program implementation which uses xDM v1.0 JPEG
*               decoder's APIs to create a decoder instance and decode multiple
*               input files. It supports dumping of output decoded YUV data in
*               4:2:0, 4:2:2 or 4:4:4 format or comparision fo decoded raw data
*               with reference data.Uses single instance of the decoder and 
*               uses only base params for all input classes.
*               
*              Since this is a JPEG and we have only 1 frame in it , we will 
*              not be making use of buffer manager , instead we will make use 
*              of Global memory and divide it upon the input and output buffers 
*              to allocate it and use it accordingly
*
*
*  @return      XDM_EOK     : If successfully decoded all input streams/files
*               XDM_EFAIL   : If encountered error in decoding the given set of
*                             input files.
********************************************************************************
*/

XDAS_Int32 main()
{
  /*--------------------------------------------------------------------------*/
  /* File I/O variables                                                       */
  /*--------------------------------------------------------------------------*/
  FILE *pFconfigFile = NULL, *pFparamsFile = NULL;
  MYFILE  *pFtestFile = NULL;
  XDAS_Int8 line[2*STRING_SIZE], inFile[STRING_SIZE], testFile[STRING_SIZE];
  XDAS_Int8 paramsFile[STRING_SIZE],  testCompliance;
  XDAS_UInt32 frameNum = 0;
  char sVersion[MIN_VERSION_BUF_SIZE];
  
#ifdef TST_FRAME_MODE
  XDAS_Int8 sizeFile[STRING_SIZE];
  FILE *fsizeFile;
#endif

  /*--------------------------------------------------------------------------*/
  /* Relative path for the configuration file TestVecs.cfg.                   */
  /* This file contains the configurations to test using this test application*/
  /*--------------------------------------------------------------------------*/
  XDAS_Int8 *fname = 
  (XDAS_Int8 *)"..\\..\\..\\test\\testvecs\\config\\TestVecs.cfg";

  /*--------------------------------------------------------------------------*/
  /* Base Class Structures                                                    */
  /*--------------------------------------------------------------------------*/
  IJPEGVDEC_Status             status;
  IJPEGVDEC_InArgs             inArgs;

  /*--------------------------------------------------------------------------*/
  /* Algorithm specific instance handle                                       */
  /*--------------------------------------------------------------------------*/
  IALG_Handle handle;

  /*--------------------------------------------------------------------------*/
  /* Input/Output Buffer Descriptors                                          */
  /*--------------------------------------------------------------------------*/
  XDM2_BufDesc inputBufDesc;
  XDM2_BufDesc  outputBufDesc;

  /*--------------------------------------------------------------------------*/
  /* Other variables                                                          */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32  inputBufCount, outputBufCount, frameCount;
  XDAS_Int32  testVal;
  XDAS_UInt32 BufferReq , errorVal;
  XDAS_UInt32 readIdentifier1=0, readIdentifier2=0;
#ifdef PROFILE_HOST  
  XDAS_Int32 startTime;
  XDAS_Int32 endTime;
  XDAS_Int32 AverageCycles;
  XDAS_Int32 startTimeM3;
  XDAS_Int32 endTimeM3;
  XDAS_Int32 AverageCyclesM3;
  XDAS_Int32 PeakCyclesM3;
  XDAS_Int32 FrameCyclesM3;
#endif  
#ifndef TST_FRAME_MODE
  XDAS_Int8 * inBufAddr;                                                                                                     
  /*--------------------------------------------------------------------------*/
  /* Open Test Config File                                                    */
  /*--------------------------------------------------------------------------*/
  inBufAddr = inputData; 
#endif  
  pFconfigFile = fopen((const char *)fname,"r");
  if (!pFconfigFile)
  {
    printf("Couldn't open parameter file %s",fname);
    return XDM_EFAIL;
  }
  else
  {
    /* Nothing to execute*/
  }

  countConfigSet = 0; 
  /*--------------------------------------------------------------------------*/
  /* Read the Config File until it reaches the end of file                    */
  /*--------------------------------------------------------------------------*/
  while(!feof(pFconfigFile))
  {

    AccCount = 0;
    GblCount = 0;
    countConfigSet++;
    initialFrame = 0;
    SlcSwitchCount = 0;
    /*------------------------------------------------------------------------*/
    /* initialize the IO memory pointer                                       */
    /*------------------------------------------------------------------------*/
    pBufferIo = globalMemory;

    /*------------------------------------------------------------------------*/
    /* Read Compliance Checking parameter                                     */
    /*------------------------------------------------------------------------*/
    if(fgets((char *)line,MAX_CHAR_READ,pFconfigFile))
    {
      sscanf((const char *)line,"%d",&testCompliance);
    }
    else
    {
      break ;
    }
    
    /*------------------------------------------------------------------------*/
    /* Read Parameters file name                                              */
    /*------------------------------------------------------------------------*/
    if(fgets((char *)line,MAX_CHAR_READ,pFconfigFile))
    {
      sscanf((const char *)line,"%s",paramsFile);
    }
    else
    {
      break ;
    }
    
    /*------------------------------------------------------------------------*/
    /* Read Input file name                                                   */
    /*------------------------------------------------------------------------*/
    if(fgets((char *)line,MAX_CHAR_READ,pFconfigFile))
    {
      sscanf((const char *)line,"%s",inFile);
    }
    else
    {
      break ;
    }
    
    /*------------------------------------------------------------------------*/
    /* Read Output/Reference file name                                        */
    /*------------------------------------------------------------------------*/
    if(fgets((char *)line,MAX_CHAR_READ,pFconfigFile))
    {
      sscanf((const char *)line,"%s",testFile);
    }
    else
    {
      break ;
    }
#ifdef TST_FRAME_MODE
    /*--------------------------------------------------------------------*/
    /* Read Frame size file name                                          */
    /* frameSize file contains the number of bytes to be read for each    */
    /* frame                                                              */
    /*--------------------------------------------------------------------*/
    if(fgets((char * )line,MAX_CHAR_READ,pFconfigFile))
    {
      sscanf((const char *)line,"%s",sizeFile);
      fsizeFile = fopen ((const char *)sizeFile, "rb");
      if(fsizeFile == NULL)
      {

        continue ;
      }
      else
      {
        /* Nothing to Execute */
      }
    }
    else
    {
      break ;
    }
#endif /* TST_FRAME_MODE */

    printf("*******************************************\n");
    printf("Finished reading configuration set %d\n", countConfigSet);
    printf("*******************************************\n");

    /*------------------------------------------------------------------------*/
    /* Initialization of parameters needed for Algorithm  creation            */
    /*------------------------------------------------------------------------*/
    TestApp_SetInitParams(&params.viddecParams);
    
    /*------------------------------------------------------------------------*/
    /* Open Parameters file, and read the contents of parameters              */
    /* related to the JPEG decoder codec. Close the file after completion     */
    /* of parameter read                                                      */
    /*------------------------------------------------------------------------*/
    pFparamsFile = (MYFILE *)FOPEN((const char *)paramsFile, "rb");
    if(!pFparamsFile)
    {
      printf("Couldn't open Parameters file...   %s\n", paramsFile);
      printf("Exiting for this configuration...\n");
      continue;
    }
    else
    {
      /* Nothing to execute*/
    }
    
    if(readparamfile(pFparamsFile) < 0)
    {
      printf("Syntax Error in %s\n", paramsFile);
      printf("Exiting for this configuration...\n");
      continue;
    }
    else
    {
      /* Nothing to execute*/
    }  

    FCLOSE(pFparamsFile);
    
    /*------------------------------------------------------------------------*/
    /* Print Compliance mode                                                  */
    /*------------------------------------------------------------------------*/
    if(testCompliance)
    {
      printf("Running in Compliance Mode\n");
    }
    else
    {
      printf("Running in Output Dump Mode\n");
    }

    /*------------------------------------------------------------------------*/
    /* Open output/reference file based on compliance mode                    */
    /*------------------------------------------------------------------------*/
    if(testCompliance)
    {
      pFtestFile = (MYFILE *)FOPEN ((const char *)testFile, "rb");
      if( !pFtestFile)
      {
        printf("Couldn't open Test File... %s",pFtestFile);
        printf("\n Exiting for this configuration..." );
        continue;
      }
    }
    else
    {
      pFtestFile = (MYFILE *)FOPEN ((const char *)testFile, "wb");
      if( !pFtestFile)
      {
        printf("Couldn't open Test File... %s",pFtestFile);
        printf("\n Exiting for this configuration..." );
        continue;
      }      
    }
    
    /*------------------------------------------------------------------------*/   
    /* Setting the sizes of Base Class Objects                                */
    /*------------------------------------------------------------------------*/
    params.viddecParams.size     = sizeof(IJPEGVDEC_Params);
    status.viddecStatus.size     = sizeof(IJPEGVDEC_Status);
    inArgs.viddecInArgs.size     = sizeof(IJPEGVDEC_InArgs);
    outArgs.viddecOutArgs.size   = sizeof(IJPEGVDEC_OutArgs);
    dynamicParams.viddecDynamicParams.size = sizeof(IJPEGVDEC_DynamicParams);

    /*------------------------------------------------------------------------*/
    /* Initializing one input file processing specific variables              */
    /*------------------------------------------------------------------------*/
    frameCount                   = 0;
    bytesConsumed                = 0;
  bytesConsumed_total          = 0;
    reachedEndOfFile             = 0;
    fileOffset                   = 0;
    validBytes                   = 0;
    outArgs.viddecOutArgs.bytesConsumed        = 0;

    /*------------------------------------------------------------------------*/
    /* NOTE:                                                                  */
    /* HDVICP calls enables non-blocking implementation on the host           */
    /* processor in a OS scenario with support for multi-thread/task          */
    /* creations. hdvicpObj which will be part of the decoder instance.       */
    /* All future calls to HDVICP module made by the algorithm will           */
    /* contain this as the handle.HDVICP module initialises it suitably       */
    /* to enable context identification is future calls.                      */
    /*------------------------------------------------------------------------*/
    /*------------------------------------------------------------------------*/
    /* Create the Algorithm object (instance)                                 */
    /*------------------------------------------------------------------------*/
    printf("\nCreating Algorithm Instance...");
    if ((handle =
          (IALG_Handle)jpgVDEC_create
          (
            (const IJPEGVDEC_Fxns  *)&JPEGVDEC_TI_IJPEGVDEC,
            (const IJPEGVDEC_Params *) &params)) == NULL
        )
    {
      printf("\nFailed to Create Instance Exiting this configuration");
      continue;
    }
    else
    {
      /* Nothing to execute*/
    }
    printf("\nAlgorithm Instance Creation Done...\n");

    /*------------------------------------------------------------------------*/
    /* Call to RMAN Assign Resources. This call will assign all the required  */
    /* resources to algorithm for decoding                                    */
    /*------------------------------------------------------------------------*/
    RMAN_AssignResources(handle);

    printf("Started decoding Test File %s\n",inFile);
    
    /*------------------------------------------------------------------------*/
    /* Initialization of run time dynamic parameters                          */
    /*------------------------------------------------------------------------*/
    TestApp_SetDynamicParams(&dynamicParams);

    /*------------------------------------------------------------------------*/
    /* Initialization of data buffer required for holding the version info    */
    /*------------------------------------------------------------------------*/
    status.viddecStatus.data.buf = (XDAS_Int8 *)sVersion;
    status.viddecStatus.data.bufSize = MAX_VERSION_BUF_SIZE;
    
    /*------------------------------------------------------------------------*/
    /*  The XDM_GETVERSION call gives information for about the codec         */
    /*  version...                                                            */
    /*------------------------------------------------------------------------*/
    jpgVDEC_control((IJPEGVDEC_Handle)handle,
    XDM_GETVERSION,
    (IJPEGVDEC_DynamicParams *)&dynamicParams,
    (IJPEGVDEC_Status *)&status
    );

    printf("Version = %s\n",sVersion);

    /*------------------------------------------------------------------------*/
    /*  The SETPARAMS call gives information to the algorithm about the       */
    /*  dynamic parameters that have been initialized. Currently, only        */
    /*  base params have been initialized. The algorithm will set any         */
    /*  specific context variables that it needs from these dynamic prms.     */
    /*------------------------------------------------------------------------*/
    errorVal = jpgVDEC_control((IJPEGVDEC_Handle)handle,
    XDM_SETPARAMS,
    (IJPEGVDEC_DynamicParams  *)&dynamicParams,
    (IJPEGVDEC_Status *)&status
    );
    
    if(errorVal != 0)
    {
      printf(" Set Params Not set properly \n");
      continue;
    }
    /*------------------------------------------------------------------------*/
    /* Enquire the algorithm about its IO buffer requirements. Alpgorithm will*/
    /* populate the status.bufInfo with all the memory requirements           */
    /*------------------------------------------------------------------------*/
    jpgVDEC_control((IJPEGVDEC_Handle)handle,
    XDM_GETBUFINFO,
    (IJPEGVDEC_DynamicParams *)&dynamicParams,
    (IJPEGVDEC_Status *)&status
    );

    /*-----------------------------------------------------------------------*/
    /*  Initialize the TILER params & Get the buffers in TILER space         */
    /*-----------------------------------------------------------------------*/
    testAppTilerInit(status.viddecStatus.bufInfo.minOutBufSize);
    
    /*------------------------------------------------------------------------*/
    /* Fill up the input buffer values and pointers. Please note that at      */
    /* this stage picture size is still unknown hence default picture size    */
    /* of maxWidth x maxHeight is assumed internally by the codec.            */
    /* This defaultpicture size is used initialise minimum input and          */
    /* output buffers.                                                        */
    /*------------------------------------------------------------------------*/    
    inputBufDesc.numBufs  = status.viddecStatus.bufInfo.minNumInBufs ;

    /*------------------------------------------------------------------------*/
    /* For Raw Memory input , allocate the buffer address and number of       */
    /* bytes required by the same , we will be having 1 huge memory in        */
    /* heap which will be divided among input and output buffers , so         */
    /* updation of  "pBufferIo" is required so that output buffer starts      */
    /* from the address offset of bytes consumed by inputbuffer               */
    /*------------------------------------------------------------------------*/ 
    for(inputBufCount=0;
    inputBufCount<(status.viddecStatus.bufInfo.minNumInBufs) ;
    inputBufCount++ )
    {
      inputBufDesc.descs[inputBufCount].buf  = (XDAS_Int8 *) inputData;                                 
      inputBufDesc.descs[inputBufCount].bufSize.bytes =                                                 
      inputBufDesc.descs[inputBufCount].bufSize.bytes =
      status.viddecStatus.bufInfo.minInBufSize[inputBufCount].bytes;
    }
    
    inputBufDesc.descs[0].memType   =   XDM_MEMTYPE_RAW;

    outputBufDesc.numBufs    =  status.viddecStatus.bufInfo.minNumOutBufs;
    
    if(!tilerEnable)
    {
      /*----------------------------------------------------------------------*/
      /* For Raw Memory Output ,  Fill up the output buffer values and        */
      /* pointers  , and update the "pBufferIo" after each buffer is done.    */
      /* Since next buffer (depending on the chroma format) will use the      */
      /* pointer from the updated value of "pBufferIo"                        */
      /*----------------------------------------------------------------------*/
      BufferReq = status.viddecStatus.bufInfo.minOutBufSize[0].
      tileMem.width * status.viddecStatus.bufInfo.minOutBufSize[0].
      tileMem.height;
      
      /*----------------------------------------------------------------------*/
      /* For Raw Memory , depending on the chroma format (through Number of   */
      /* output buffers requested) we will allocate the number of bytes       */
      /* required . This we have to do since "XDM2_BufSize"  is of type       */
      /* union                                                                */
      /*----------------------------------------------------------------------*/
      switch(outputBufDesc.numBufs)
      {
      case  NUM_OUTBUF_JPEG_420 :
        /*--------------------------------------------------------------------*/
        /*in case of 420 we will be having only 2 buffers , so raw memory     */
        /* allocation is done here for 2 buffers                              */
        /*--------------------------------------------------------------------*/ 
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes = BufferReq;
        outputBufDesc.descs[0].buf  = (XDAS_Int8 *) pBufferIo;
        outputBufDesc.descs[0].bufSize.bytes =
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes;
        outputBufDesc.descs[0].memType       =  XDM_MEMTYPE_RAW;
        
        pBufferIo                           += 
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes;
        status.viddecStatus.bufInfo.minOutBufSize[1].bytes = BufferReq>>1;
        outputBufDesc.descs[1].buf  = (XDAS_Int8 *) pBufferIo;
        outputBufDesc.descs[1].bufSize.bytes =
        status.viddecStatus.bufInfo.minOutBufSize[1].bytes;
        outputBufDesc.descs[1].memType       =  XDM_MEMTYPE_RAW;
        break;    
        
      case  NUM_OUTBUF_JPEG_422 : 
        /*--------------------------------------------------------------------*/
        /*in case of 422 we will be having only 1 buffer , so raw memory      */
        /* allocation is done here for 1 buffer.                              */
        /*--------------------------------------------------------------------*/
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes = BufferReq << 1;
        outputBufDesc.descs[0].buf  = (XDAS_Int8 *) pBufferIo;
        outputBufDesc.descs[0].bufSize.bytes =
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes;
        outputBufDesc.descs[0].memType       =  XDM_MEMTYPE_RAW;
        break;    
        
      case  NUM_OUTBUF_JPEG_444 :
        /*--------------------------------------------------------------------*/
        /*in case of 444 we will be having only 3 buffers , so raw memory     */
        /* allocation is done here for 3 buffers (1 each for Luma , Cb and Cr)*/
        /*--------------------------------------------------------------------*/      
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes = BufferReq;
        outputBufDesc.descs[0].buf  = (XDAS_Int8 *) pBufferIo;
        outputBufDesc.descs[0].bufSize.bytes =
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes;
        outputBufDesc.descs[0].memType       =  XDM_MEMTYPE_RAW;
        
        pBufferIo                           += 
        status.viddecStatus.bufInfo.minOutBufSize[0].bytes;
        status.viddecStatus.bufInfo.minOutBufSize[1].bytes = BufferReq;
        outputBufDesc.descs[1].buf  = (XDAS_Int8 *) pBufferIo;
        outputBufDesc.descs[1].bufSize.bytes =
        status.viddecStatus.bufInfo.minOutBufSize[1].bytes;
        outputBufDesc.descs[1].memType       =  XDM_MEMTYPE_RAW;
        
        pBufferIo                           += 
        status.viddecStatus.bufInfo.minOutBufSize[1].bytes;
        status.viddecStatus.bufInfo.minOutBufSize[2].bytes = BufferReq;
        outputBufDesc.descs[2].buf  = (XDAS_Int8 *) pBufferIo;
        outputBufDesc.descs[2].bufSize.bytes =
        status.viddecStatus.bufInfo.minOutBufSize[2].bytes;
        outputBufDesc.descs[2].memType       =  XDM_MEMTYPE_RAW;
        break;    
        
        default :
        break;
      }
    }
    else
    {
      for(outputBufCount=0; 
      outputBufCount<(status.viddecStatus.bufInfo.minNumOutBufs);
      outputBufCount++ )
      {
        outputBufDesc.descs[outputBufCount].buf    =
        (XDAS_Int8 *)tilerParams.tiledBufferAddr[outputBufCount];
        outputBufDesc.descs[outputBufCount].bufSize.tileMem.width  = 
        status.viddecStatus.bufInfo.minOutBufSize[outputBufCount].tileMem.width;
        outputBufDesc.descs[outputBufCount].bufSize.tileMem.height = 
        status.viddecStatus.bufInfo.minOutBufSize[outputBufCount].
        tileMem.height;

      } 

      tilerParams.tilerSpace[0]    = CONTAINER_8BITS;
      tilerParams.tilerSpace[1]    = CONTAINER_16BITS;
      
      if(chromaTilerMode)
      {
        tilerParams.tilerSpace[1]  = CONTAINER_8BITS;
      }
      
      if(chromaTilerMode) 
      {
        outputBufDesc.descs[1].memType  = XDM_MEMTYPE_TILED8;
        outputBufDesc.descs[0].memType  = XDM_MEMTYPE_TILED8;
      }
      else 
      {
        outputBufDesc.descs[1].memType = XDM_MEMTYPE_TILED16;
        outputBufDesc.descs[0].memType  = XDM_MEMTYPE_TILED8;
      }      

    }      

    outArgs.viddecOutArgs.outBufsInUseFlag = 0;

    do
    {
#ifdef PROFILE_HOST

      AverageCycles = 0;
      AverageCyclesM3 = 0;
      PeakCyclesM3 = 0;
      
      ICEC_CNT_CTRL = 0x40000000;
      while(!(ICEC_CNT_CTRL & (1 << 28)))  /* is owner Application */
      {
        /* claim resource */
        ICEC_CNT_CTRL = 0x40000000;
      }
      /* enable resource */
      ICEC_CNT_CTRL = 0x80000000;
      ICEC_CNT_CTRL = 0x80000000 |  (1<<19) | (1<<16);
      /* load enable counter mode1 */
      ICEC_CNT_CTRL = 0x80000000 |  (1<<19) | (1<<16) | (1<<12);
      
      startTime = ICEC_CNT_VAL;
      endTime = ICEC_CNT_VAL;

      /*----------------------------------------------------------------------*/
      /* Cortex-M3 counter register initialization.                           */
      /* This is a decrementing counter.                                      */
      /*----------------------------------------------------------------------*/
      SYSTICKREG = 0x4;
      SYSTICKREL = SYSTICKRELVAL;
      SYSTICKREG = 0x5;

#endif
      /*----------------------------------------------------------------------*/
      /* reset release buffer counter used in DataSync                        */
      /*----------------------------------------------------------------------*/     
       putBufferCount = 0;
      /*----------------------------------------------------------------------*/
      /* Setting of input ID. For JPEG decoder, the buffer management is not  */
      /* required. Thus inputID is always set to 1. Codec should release      */
      /* the buffer after process call through outputID                       */
      /*----------------------------------------------------------------------*/      
      inArgs.viddecInArgs.inputID = 1;                                              
      
      /*----------------------------------------------------------------------*/
      /* Read the bitstream in the Application Input Buffer. validBytes       */
      /* would be initialised with the actual number of bytes read from       */
      /* the input file                                                       */
      /*----------------------------------------------------------------------*/
#ifdef TST_FRAME_MODE
      validBytes = TestApp_ReadByteStream(inFile, inputBufDesc,
      fsizeFile,frameCount);
#else
      if(params.sliceSwitchON == 0)
      {
        validBytes = TestApp_ReadByteStream(inFile,inputBufDesc);          
        if(validBytes  <= 0)
        {
          reachedEndOfFile = 1;
        }  
        GblCount = 0;        
        AccCount = 0; 

      }  
      else if(params.sliceSwitchON == 1)
      {
        validBytes = TestApp_ReadByteStream(inFile,inputBufDesc); 
        if(validBytes  <= 0)
        {
          reachedEndOfFile = 1;
        }
            /*handling special case when each variable block size one slice data*/
        GblCount = 0;        
        AccCount = frameCount;
        SlcSwitchCount = frameCount;
        frameCount++;
        framesToDecode++;
      }
#endif

#ifndef TST_FRAME_MODE                                                                                                       
      inputBufDesc.descs[0].buf   = (XDAS_Int8 *)((XDAS_Int32)inBufAddr + 
      bytesConsumed);      
#endif                                                                                                 
      curr_ddr_addr[0]  = inputBufDesc.descs[0].buf;
      bytes_ddr      = validBytes;
      curr_ddr_bytes = ((validBytes > 8192) ? (8192) : (validBytes));
      OutFlag = 0;
      curr_ddr_addr[0] = curr_ddr_addr[0];
      if(params.sliceSwitchON == 1)
      {
      curr_ddr_addr[1] = curr_ddr_addr[0] + blockSizeArray[0 + AccCount];
      curr_ddr_addr[2] = curr_ddr_addr[1] + blockSizeArray[1 + AccCount];
      curr_ddr_addr[3] = curr_ddr_addr[2] + blockSizeArray[2 + AccCount];
      curr_ddr_addr[4] = curr_ddr_addr[3] + blockSizeArray[3 + AccCount];
      curr_ddr_addr[5] = curr_ddr_addr[4] + blockSizeArray[4 + AccCount];
      curr_ddr_addr[6] = curr_ddr_addr[5] + blockSizeArray[5 + AccCount];
      curr_ddr_addr[7] = curr_ddr_addr[6] + blockSizeArray[6 + AccCount];
        curr_ddr_addr[8] = curr_ddr_addr[7] + blockSizeArray[7 + AccCount];
        curr_ddr_addr[9] = curr_ddr_addr[8] + blockSizeArray[8 + AccCount];
        curr_ddr_addr[10] = curr_ddr_addr[9] + blockSizeArray[9 + AccCount];
        curr_ddr_addr[11] = curr_ddr_addr[10] + blockSizeArray[10 + AccCount];
        curr_ddr_addr[12] = curr_ddr_addr[11] + blockSizeArray[11 + AccCount];
    curr_ddr_addr[13] = curr_ddr_addr[12] + blockSizeArray[12 + AccCount];
        curr_ddr_addr[14] = curr_ddr_addr[13] + blockSizeArray[13 + AccCount];
        curr_ddr_addr[15] = curr_ddr_addr[14] + blockSizeArray[14 + AccCount];
    curr_ddr_addr[16] = curr_ddr_addr[15] + blockSizeArray[15 + AccCount];
    curr_ddr_addr[17] = curr_ddr_addr[16] + blockSizeArray[16 + AccCount];
    curr_ddr_addr[18] = curr_ddr_addr[17] + blockSizeArray[17 + AccCount];
    curr_ddr_addr[19] = curr_ddr_addr[18] + blockSizeArray[18 + AccCount];
    curr_ddr_addr[20] = curr_ddr_addr[19] + blockSizeArray[19 + AccCount];
    curr_ddr_addr[21] = curr_ddr_addr[20] + blockSizeArray[20 + AccCount];
    curr_ddr_addr[22] = curr_ddr_addr[21] + blockSizeArray[21 + AccCount];
    curr_ddr_addr[23] = curr_ddr_addr[22] + blockSizeArray[22 + AccCount];
    curr_ddr_addr[24] = curr_ddr_addr[23] + blockSizeArray[23 + AccCount];
    curr_ddr_addr[25] = curr_ddr_addr[24] + blockSizeArray[24 + AccCount];
    curr_ddr_addr[26] = curr_ddr_addr[25] + blockSizeArray[25 + AccCount];
    curr_ddr_addr[27] = curr_ddr_addr[26] + blockSizeArray[26 + AccCount];
    curr_ddr_addr[28] = curr_ddr_addr[27] + blockSizeArray[27 + AccCount];
    curr_ddr_addr[29] = curr_ddr_addr[28] + blockSizeArray[28 + AccCount];
    curr_ddr_addr[30] = curr_ddr_addr[29] + blockSizeArray[29 + AccCount];
    curr_ddr_addr[31] = curr_ddr_addr[30] + blockSizeArray[30 + AccCount];
      }
      else
      {      

      curr_ddr_addr[1] = curr_ddr_addr[0] + blockSizeArray[0];
      curr_ddr_addr[2] = curr_ddr_addr[1] + blockSizeArray[1];
      curr_ddr_addr[3] = curr_ddr_addr[2] + blockSizeArray[2];
      curr_ddr_addr[4] = curr_ddr_addr[3] + blockSizeArray[3];
      curr_ddr_addr[5] = curr_ddr_addr[4] + blockSizeArray[4];
      curr_ddr_addr[6] = curr_ddr_addr[5] + blockSizeArray[5];
      curr_ddr_addr[7] = curr_ddr_addr[6] + blockSizeArray[6];
      
      if((blockSizeArray[0]+blockSizeArray[1]+blockSizeArray[2]+
            blockSizeArray[3]+blockSizeArray[4]+blockSizeArray[5] + 
            blockSizeArray[6]+ blockSizeArray[7]) < validBytes)
      {
        blockSizeArray[7] += validBytes - (blockSizeArray[0] + 
        blockSizeArray[1] +
        blockSizeArray[2] +
        blockSizeArray[3] +
        blockSizeArray[4] +
        blockSizeArray[5] + 
        blockSizeArray[6] + 
        blockSizeArray[7]); 
      }
      }
      
      
      
      if(validBytes <= -1)                                                    
      {                                                                       
        break;                                                                
      }                                                                       
      else                                                                    
      {                                                                       
        /* Nothing to execute*/                                               
      }                                                                       
      
      /*----------------------------------------------------------------------*/
      /* Assign the number of bytes available for decoding                    */
      /*----------------------------------------------------------------------*/
      inArgs.viddecInArgs.numBytes        = validBytes;
      inputBufDesc.descs[0].bufSize.bytes = validBytes;    
      printf("inputBufDesc.descs[0].buf =%x\n",inputBufDesc.descs[0].buf);
#ifdef PROFILE_HOST
      startTime = ICEC_CNT_VAL;
      startTimeM3 = SYSTICKVAL;
#endif          
      /*----------------------------------------------------------------------*/
      /* Basic Algorithm process() call to decode a frame                     */
      /*----------------------------------------------------------------------*/
      errorVal = jpgVDEC_decode
      (
      (IJPEGVDEC_Handle)handle,
      (XDM2_BufDesc *)&inputBufDesc,
      (XDM2_BufDesc *)&outputBufDesc,
      (IJPEGVDEC_InArgs *)&inArgs,
      (IJPEGVDEC_OutArgs *)&outArgs
      );

#ifdef PROFILE_HOST
      endTimeM3  = SYSTICKVAL;
      endTime  = ICEC_CNT_VAL;
      AverageCycles += (endTime - startTime);
      if((XDAS_Int32)(startTimeM3 - endTimeM3) < 0)
      {
        startTimeM3 += SYSTICKRELVAL;
      }
      FrameCyclesM3 = (startTimeM3 - endTimeM3);
      AverageCyclesM3 += FrameCyclesM3;
      if(FrameCyclesM3 > PeakCyclesM3)
      {
        PeakCyclesM3 = FrameCyclesM3;
      }
      printf("IVA MHz per frame : %f\n", 
           (FrameCyclesM3 * IVA_CLOCK_FREQ / (M3_CLOCK_FREQ)));    
#endif
      
      if(errorVal != 0)
      {
        printf(" Process fail for frameNum = %d \n", frameNum);
        printf ( "outArgs.viddecOutArgs.extendedError = %0x\n",
        outArgs.viddecOutArgs.extendedError );
      }
      else
      {
        printf("Decoding Completed for frameNum = %d \n", frameNum);
      }    

      /*----------------------------------------------------------------------*/
      /* Check for return value of the process call. It is to check the status*/
      /* of the Picture being decoded now. As it is JPEG , there is no concept*/
      /* of previous frame , always the status structure updation will happen */
      /* for the current frame                                                */
      /*----------------------------------------------------------------------*/
      jpgVDEC_control
      (
      (IJPEGVDEC_Handle)handle,
      XDM_GETSTATUS,
      (IJPEGVDEC_DynamicParams *)&dynamicParams,
      (IJPEGVDEC_Status *)&status
      );

      if(errorVal != 0)
      {

        printf ( "status.viddecStatus.extendedError = %0x\n",
        status.viddecStatus.extendedError );
        
        printf ( "status.extendedErrorCode0 = %0x\n",
        status.extendedErrorCode0 );
        
        printf ( "status.extendedErrorCode1 = %0x\n",
        status.extendedErrorCode1 );
        
        printf ( "status.extendedErrorCode2 = %0x\n",
        status.extendedErrorCode2 );
        
        printf ( "status.extendedErrorCode3 = %0x\n",
        status.extendedErrorCode3 );                                
     
      }
      /*----------------------------------------------------------------------*/
      /*  Update the bytesConsumed by adding the bytes consumed by the algo-  */
      /*  rithm in the decode call. Similarly, reduce the valid bytes         */
      /*  remaining in the application input buffer by subtracting the        */
      /*  bytes consumed in the decode call.                                  */
      /*----------------------------------------------------------------------*/     
      bytesConsumed          = outArgs.viddecOutArgs.bytesConsumed;
      printf("bytesConsumed =%d\n",bytesConsumed);
      bytesConsumed_total   += outArgs.viddecOutArgs.bytesConsumed;
      validBytes             -= outArgs.viddecOutArgs.bytesConsumed;
      
      if((params.sliceSwitchON == 1) &&
          (outArgs.viddecOutArgs.outBufsInUseFlag))
      {

        readIdentifier1 = (*((XDAS_UInt8*)(inputBufDesc.descs[0].buf + bytesConsumed - 2)));

        readIdentifier2 = (*((XDAS_UInt8*)(inputBufDesc.descs[0].buf + bytesConsumed - 1)));

        if((readIdentifier1 == 0xFF) && ((readIdentifier2 == 0xD0) || 
              (readIdentifier2 == 0xD0) || (readIdentifier2 == 0xD1) || 
              (readIdentifier2 == 0xD2) || (readIdentifier2 == 0xD3) || 
              (readIdentifier2 == 0xD4) || (readIdentifier2 == 0xD5) || 
              (readIdentifier2 == 0xD6) || (readIdentifier2 == 0xD7)))
        {
          bytesConsumed -= 2;
          validBytes += 2;
        }
            SlcSwitchCount++;
      }
      
      /*----------------------------------------------------------------------*/
      /* Check for frame ready via display buffer pointers                    */
      /*----------------------------------------------------------------------*/
      if(outArgs.viddecOutArgs.outputID[0] != 0)
      {
        if(testCompliance)
        {
          /*------------------------------------------------------------------*/
          /* Compare the output frames with the Reference File                */
          /*------------------------------------------------------------------*/
          testVal = TestApp_CompareOutputData
          (
          pFtestFile,
          &outArgs
          );

          if(testVal == 1)
          {
            printf(" : Passed\n");
          }
          else
          {
            /*----------------------------------------------------------------*/
            /* Test Compliance Failed... Breaking...                          */
            /*----------------------------------------------------------------*/
            printf("************Failed*************\n");
            break;
          }
        } /* if(testCompliance)*/
        else
        {
          if(!outArgs.viddecOutArgs.outBufsInUseFlag)
          {
            if(frameCount >= dumpFrom)
            {
              printf("Started dumping output...\n");
              
              /*----------------------------------------------------------------*/
              /*   Write the output frames in the display order                 */
              /*----------------------------------------------------------------*/
              if(chromaTilerMode==0  && tilerEnable == 1 )
              TestApp_WriteOutputDataTiled16
              (
              pFtestFile,
              &outArgs
              );
              
              else
              /*----------------------------------------------------------------*/
              /* Write the output frames in the display order                   */
              /*----------------------------------------------------------------*/
              TestApp_WriteOutputData
              (
              pFtestFile,
              &outArgs
              );
            } /* if(frameCount >= dumpFrom)*/
          }
        }/*else */
      }
      else
      {
        /* Nothing to execute*/
      }

      if(!outArgs.viddecOutArgs.outBufsInUseFlag)
      {
        frameCount++;
      }
      else
      {
        /* Nothing to execute*/
      }
      /*----------------------------------------------------------------------*/
      /*  Since this is a JPEG decoder , we will be having only one frame ,   */
      /* hence printing all the valuable information like Chroma format of    */
      /* the image decoded                                                    */
      /*----------------------------------------------------------------------*/
      printf("Frame Number :  %d\n",frameNum);
      
#ifndef TST_FRAME_MODE

      /*----------------------------------------------------------------------*/
      /* Check for Break off condition . Since this application is for        */
      /* JPEG , we donot expect any image with less than 5 bytes.             */
      /*----------------------------------------------------------------------*/      
      if((validBytes <= 5)||(outArgs.viddecOutArgs.extendedError == 0x20000000))
      {
        printf("\n Bitstream Ended...  ");
        break; 
        /*--------------------------------------------------------------------*/
        /* Bitstream ended: Break off the while loop                          */
        /*--------------------------------------------------------------------*/
      }
      else
      {
        frameNum++;
      }

#endif
      
    }  while(frameCount < framesToDecode);  /* end of Do-While loop  */
    
    /*------------------------------------------------------------------------*/
    /* Output file close                                                      */
    /*------------------------------------------------------------------------*/
    FCLOSE(pFtestFile);
#ifdef TST_FRAME_MODE
    reachedEndOfFile = 0;
    frameSizeOffset  = 0;
#endif
    frameNum = 0;

    /*------------------------------------------------------------------------*/
    /* Call to RMAN_FreeResources. This call will free all the required  */
    /* resources to algorithm for decoding                                    */
    /*------------------------------------------------------------------------*/
    RMAN_FreeResources(handle);
    
    /*------------------------------------------------------------------------*/
    /* Delete the Algorithm instance object specified by handle               */
    /*------------------------------------------------------------------------*/
    jpgVDEC_delete((IJPEGVDEC_Handle)handle);

    if(frameCount == 0)
    {
      /*----------------------------------------------------------------------*/
      /* To avoid division with zero                                          */
      /*----------------------------------------------------------------------*/
      frameCount = 1; 
    }

    printf("\n --------------  SUMMARY --------------------\n");

    if(!testCompliance)
    {
      printf(" Decoder output dump completed\n");
    }
    /*------------------------------------------------------------------------*/
    /* Depending on the output chroma format , print the chroma format type   */
    /*------------------------------------------------------------------------*/    
    switch(outArgs.viddecOutArgs.displayBufs.bufDesc[0].chromaFormat)
    {
    case  CHROMA_OUTBUF_JPEG_420 :
      printf(" OutputChroma Format : JPEG_420 \n");
      break;    
      
    case  CHROMA_OUTBUF_JPEG_422_HORI : 
      printf(" OutputChroma Format : JPEG_422 Horizontal \n");
      break;    
      
    case  CHROMA_OUTBUF_JPEG_444 :
      printf(" OutputChroma Format : JPEG_444 planar \n");
      break;    
      
      default :
      break;
    }
    
    printf("\n --------------------------------------------\n");

    printf("\t Total number of Frames              = %d\n", 
    (XDAS_UInt32)frameCount);
    printf("\t Bit Rate at 30 frames/Sec           = %d Kbps\n", 
    (XDAS_UInt32)(((bytesConsumed_total*8*30)/frameCount)/1024));
    printf("\t Width and Height                    = %d, %d \n", 
    outArgs.viddecOutArgs.displayBufs.bufDesc[0].
    activeFrameRegion.bottomRight.x -
    outArgs.viddecOutArgs.displayBufs.bufDesc[0].
    activeFrameRegion.topLeft.x,
    outArgs.viddecOutArgs.displayBufs.bufDesc[0].
    activeFrameRegion.bottomRight.y -
    outArgs.viddecOutArgs.displayBufs.bufDesc[0].
    activeFrameRegion.topLeft.y);
    printf (" --------------    END   --------------------\n");

    
  } /* Read the Config File until it reaches the end of file             */

  printf("\nEnd of execution\n");

  /*--------------------------------------------------------------------------*/
  /* Close the config files                                                   */
  /*--------------------------------------------------------------------------*/
  FCLOSE(pFconfigFile);

  return XDM_EOK;
} /* main */


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
XDAS_Int32 TestApp_ReadByteStream
(
XDAS_Int8 *inFile,
XDM2_BufDesc inputBufDesc,
FILE      *fsizeFile,
XDAS_Int32 frameCount
)
{
  XDAS_UInt32 BytesRead;
  XDAS_UInt32 frameSizeVal    = 0;

  FILE  *finFile;

  /*------------------------------------------------------------------------*/
  /* Open input file                                                        */
  /*------------------------------------------------------------------------*/
  finFile = fopen ((const char *)inFile, "rb");
  if(!finFile)
  {
    printf("\n Couldn't open Input file...  %s  ",inFile);
    printf("\n Exiting for this configuration...");
    return -1;
  }

  if(reachedEndOfFile)
  {
    FCLOSE(finFile);
    return 0;
  }
  if(!feof(fsizeFile))
  {

    fscanf(fsizeFile,"%ld", &frameSizeVal);

    fseek (finFile, frameSizeOffset, SEEK_SET);
    
    frameSizeOffset += frameSizeVal;

    BytesRead  = fread (inputBufDesc.descs[0].buf, 1, frameSizeVal, finFile);
    fclose(finFile);
    /*----------------------------------------------------------------------*/
    /* Determine end-of-file condition                                      */
    /*----------------------------------------------------------------------*/
    if(BytesRead != frameSizeVal)
    {
      reachedEndOfFile = 1;
    }

    /*----------------------------------------------------------------------*/
    /* Return total bytes available for further decoding                    */
    /*----------------------------------------------------------------------*/
    return (BytesRead);
  }
  else
  {
    return -1;
  }  
}
#else
XDAS_Int32 TestApp_ReadByteStream(XDAS_Int8 *inFile,XDM2_BufDesc inputBufDesc)
{
  XDAS_UInt32 BytesRead, BufferSize, validBytesIndex, totBufSize;
  MYFILE  *finFile;
  XDAS_Int8 *bufPtr , *inBuf;
  bufPtr = inputBufDesc.descs[0].buf;
  inBuf = inputBufDesc.descs[0].buf;
  /*--------------------------------------------------------------------------*/
  /* If end-of-file had already been encountered for this config              */
  /* record, then just return the remainign bytes in the input                */
  /* bit-stream.                                                              */
  /*--------------------------------------------------------------------------*/
  if(reachedEndOfFile)
  {
    return validBytes;
  }

  fileOffset -= validBytes & 0xF;
  validBytes &= 0xFFFFFFF0;

  /*--------------------------------------------------------------------------*/
  /* Open input file in read mode to fill the input stream buffer             */
  /*--------------------------------------------------------------------------*/
  finFile = (MYFILE *)FOPEN ((const char *)inFile, "rb");
  if(!finFile)
  {
    printf("\n Couldn't open Input file...  %s  ",inFile);
    printf("\n Exiting for this configuration...");
    return -1;
  }

  /*--------------------------------------------------------------------------*/
  /* Seek to the exact location in the input file from where previous         */
  /* read had left over                                                       */
  /*--------------------------------------------------------------------------*/
  FSEEK(finFile, fileOffset, SEEK_SET);

  /*--------------------------------------------------------------------------*/
  /* Shift data from lower-half to upper part. The valid bytes remaining in   */
  /* the input buffer are shifted to the starting address of the buffer and   */
  /* the empty area freed at the end is refilled.                             */
  /*--------------------------------------------------------------------------*/
  for(validBytesIndex=0 ; validBytesIndex<validBytes ; validBytesIndex++)
  {
    *inBuf = *(inBuf + bytesConsumed);
    inBuf++;
  }
  bytesConsumed = 0;

  totBufSize = INPUT_BUFFER_SIZE;
  BufferSize = totBufSize - validBytes;

  /*--------------------------------------------------------------------------*/
  /* Read the "BufferSize" number of bytes in the input buffer                */
  /* The line of code is commented for the time being                         */
  /*--------------------------------------------------------------------------*/
  BytesRead  = FREAD((bufPtr + validBytes), 1, BufferSize, finFile);
  /*--------------------------------------------------------------------------*/
  /* Store the exact pointer in the input file for next read.                 */
  /* fileOffset is also used to keep track of total file size                 */
  /* processed at any given instant. Its used to calculate the                */
  /* bit-rate of the input file as well at the end of decoding                */
  /*--------------------------------------------------------------------------*/
  fileOffset = FTELL(finFile);
  FCLOSE(finFile);

  /*--------------------------------------------------------------------------*/
  /* Return total bytes available for further decoding                        */
  /*--------------------------------------------------------------------------*/
  return (validBytes + BytesRead);
} /* TestApp_ReadByteStream() */
#endif                                                                                                  
/**
********************************************************************************
*  @fn          TestApp_CompareOutputData(FILE             * fOutFile,
*                                         IJPEGVDEC_OutArgs * outArgs)
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
FILE             * fOutFile,
IJPEGVDEC_OutArgs * outArgs
)
{
  XDAS_UInt8 *pSrc = NULL, *pDst1= NULL, *pDst2= NULL;
  XDAS_Int8  *pCbCrSeperate[4]; /* Pointers to hold seperated Cb and Cr */
  XDAS_Int8  *pLumaData= NULL;
  XDAS_Int8  fail   = 0;
  XDAS_Int32 retVal = 0;
  XDAS_Int32  frameHeight,frameWidth;
  XDAS_UInt8 chromaH = 5, chromaV = 5;
  IVIDEO2_BufDesc    *displayBufs= NULL;

  XDAS_UInt8 *pLuma = NULL, *pCb = NULL, *pCr = NULL;
  XDAS_UInt8  *pLumaBuffer= NULL, *pCbBuffer= NULL, *pCrBuffer= NULL;
  XDAS_Int32  loopVar1, loopVar2, loopVar3,loopVar4;

  /*--------------------------------------------------------------------------*/
  /* If the display buffers mode is of pointers type , then return the        */
  /* pointers else return the buffer address of the bufferDescriptor of       */
  /* display buffer in outArgs                                                */
  /*--------------------------------------------------------------------------*/
  if (outArgs->viddecOutArgs.displayBufsMode == IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddecOutArgs.displayBufs.
    pBufDesc[outArgs->viddecOutArgs.outputID[0]- 1];
  }
  else if (outArgs->viddecOutArgs.displayBufsMode == 
      IVIDDEC3_DISPLAYBUFS_EMBEDDED)
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddecOutArgs.
    displayBufs.bufDesc[0];
  }

  pLumaData = displayBufs->planeDesc[0].buf;

  /*--------------------------------------------------------------------------*/
  /* FrameHeight and FrameWidth as mentioned by the application               */
  /*--------------------------------------------------------------------------*/
  frameHeight = (displayBufs->activeFrameRegion.bottomRight.y -
  displayBufs->activeFrameRegion.topLeft.y);

  frameWidth  = (displayBufs->activeFrameRegion.bottomRight.x -
  displayBufs->activeFrameRegion.topLeft.x);

  if(displayBufs->contentType == IVIDEO_PROGRESSIVE)
  {
    switch(displayBufs->chromaFormat)
    {
    case  XDM_YUV_422IBE :
      chromaH = 1;
      chromaV = 0;

      /*--------------------------------------------------------------------*/
      /* chromaSeperate is the buffer for storing intermediate output for   */
      /* writing into output file                                           */
      /*--------------------------------------------------------------------*/
      pLuma = (XDAS_UInt8 *)chromaSeperate;

      /*--------------------------------------------------------------------*/
      /* Initialise the Cb and Cr addresses so as to get the values of Cb   */
      /* and Cr respectively and output the same in the fashion Luma , Cb   */
      /* and Cr (Planar Format)                                             */
      /*--------------------------------------------------------------------*/
      pCb   = pLuma + LUMA_BUFFER_SIZE;
      pCr   = pCb  + (LUMA_BUFFER_SIZE>>chromaH);

      pLumaBuffer = pLuma;
      pCbBuffer   = pCb;
      pCrBuffer   = pCr;

      loopVar2 = loopVar3 = 0;
      /*--------------------------------------------------------------------*/
      /* Loop to de-interleave YUYV into Y separate , U (Cb) and V(Cr)      */
      /* separate buffers                                                   */
      /*--------------------------------------------------------------------*/
      for(loopVar4 = 0 ; loopVar4 < frameHeight; loopVar4++)
      {
        for(loopVar1 = 0 ; loopVar1 < (frameWidth >> chromaH) ; loopVar1++)
        {
          pLuma[loopVar2] = pLumaData[loopVar1*4];
          loopVar2++;
          pCb[loopVar3]   = pLumaData[(loopVar1*4) + 1];
          pLuma[loopVar2] = pLumaData[(loopVar1*4) + 2];
          pCr[loopVar3]   = pLumaData[(loopVar1*4) + 3];
          loopVar2++;
          loopVar3++;
        }
        pLumaData += (displayBufs->imagePitch[0]<<1);
        pLuma     += (displayBufs->imagePitch[0]);
        pCb       += (displayBufs->imagePitch[1] >> chromaH);
        pCr       += (displayBufs->imagePitch[1] >> chromaH);
        loopVar2   = loopVar3 = 0;
      }
      break;

    case  XDM_YUV_420SP :
    case  XDM_GRAY :

      chromaH = 1;
      chromaV = 1;

      /*--------------------------------------------------------------------*/
      /* Chroma_seperate is the buffer for storing intermediate output for  */
      /* writing into output file                                           */
      /*--------------------------------------------------------------------*/
      pCbCrSeperate[0] = chromaSeperate;
      pCbCrSeperate[1] = pCbCrSeperate[0] + ((frameHeight *
      displayBufs->imagePitch[1]) >> (chromaH+chromaV));
      pSrc             = (XDAS_UInt8 *)displayBufs->planeDesc[1].buf;

      /*--------------------------------------------------------------------*/
      /* Initialise the Cb and Cr addresses so as to get the values of Cb   */
      /* and Cr respectively and output the same in the fashion Luma , Cb   */
      /* and Cr (Planar Format)                                             */
      /*--------------------------------------------------------------------*/
      pDst1            = (XDAS_UInt8 *)pCbCrSeperate[0];
      pDst2            = (XDAS_UInt8 *)pCbCrSeperate[1];

      /*--------------------------------------------------------------------*/
      /* Looping to separate Cb/Cr interleaved into Cb and Cr separate      */
      /* buffers                                                            */
      /*--------------------------------------------------------------------*/
      for(loopVar2=0 ; loopVar2<(frameHeight >> chromaV) ; loopVar2++)
      {
        for(loopVar1=0 ; loopVar1<(frameWidth >> chromaH); loopVar1++)
        {
          pDst1[loopVar1] = pSrc[loopVar1*2];
          pDst2[loopVar1] = pSrc[(loopVar1*2) + 1];
        }
        pSrc  += (displayBufs->imagePitch[1]);
        pDst1 += (displayBufs->imagePitch[1]>>chromaH);
        pDst2 += (displayBufs->imagePitch[1]>>chromaH);

      }

      pLumaBuffer      = (XDAS_UInt8 *) displayBufs->planeDesc[0].buf;
      pCbBuffer        = (XDAS_UInt8 *) pCbCrSeperate[0];
      pCrBuffer        = (XDAS_UInt8 *) pCbCrSeperate[1];
      break;

    case  XDM_YUV_444P :
      chromaH = 0;
      chromaV = 0;

      pLumaBuffer      = (XDAS_UInt8 *) displayBufs->planeDesc[0].buf;
      pCbBuffer        = (XDAS_UInt8 *) displayBufs->planeDesc[1].buf;
      pCrBuffer        = (XDAS_UInt8 *) displayBufs->planeDesc[2].buf;
      break;

      default :
      break;
    }

    /*------------------------------------------------------------------------*/
    /* Comparing the output in the order , Luma , Cb and Cr respectively      */
    /*------------------------------------------------------------------------*/
    if(chromaH <= 1)
    {
      /*---------------------------------------------------------------------*/
      /*           Read Reference Luma and Compare with the output           */
      /*---------------------------------------------------------------------*/
      for(loopVar1=0 ; loopVar1<(frameHeight) ; loopVar1++)
      {
        fread(refBuffer, 1, frameWidth, fOutFile);
        fail = memcmp(pLumaBuffer, refBuffer, frameWidth);
        if(fail)
        break;
        pLumaBuffer += displayBufs->imagePitch[0];
      }

      /*---------------------------------------------------------------------*/
      /*           Read Reference CB and Compare with the output             */
      /*           Compare only if Luma is passed                            */
      /*---------------------------------------------------------------------*/
      if (fail == 0)
      {
        for(loopVar1=0 ; loopVar1<(frameHeight >> chromaV) ; loopVar1++)
        {
          fread(refBuffer, 1, (frameWidth>>chromaH),fOutFile);
          fail = memcmp(pCbBuffer, refBuffer,(frameWidth>>chromaH));
          if(fail)
          break;
          pCbBuffer += displayBufs->imagePitch[1] >> chromaH;
        }
      }

      /*---------------------------------------------------------------------*/
      /*           Read Reference CR and Compare with the output             */
      /*           Compare only if Luma  and CB are passed                   */
      /*---------------------------------------------------------------------*/
      if (fail == 0)
      {
        for(loopVar1=0 ; loopVar1<(frameHeight >> chromaV) ; loopVar1++)
        {
          fread(refBuffer, 1, (frameWidth >> chromaH),fOutFile);
          fail = memcmp(pCrBuffer, refBuffer,(frameWidth >> chromaH));
          if(fail)
          break;
          pCrBuffer += displayBufs->imagePitch[1] >> chromaH;
        }
      }

      if(fail)
      {
        printf("\nCOMPARISION FAILED- NOT MATCHING WITH REFERENCE\n");
        retVal = 0;
      }
      else
      {
        printf("\nMATCHING WITH REFERENCE\n");
        retVal = 1;
      }
    }
  }
  return (retVal);
} /* TestApp_CompareOutputData */

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
)
{
  XDAS_Int32 count = 0;
  XDAS_Int32 roundingFactor, loopVar1, loopVar2, loopVar3,loopVar4;
  XDAS_Int32 picSize;
  volatile XDAS_UInt16 *pSrc = NULL;
  
  volatile XDAS_UInt8 *pDst1 = NULL, *pDst2 = NULL;
  XDAS_UInt8 *pLuma = NULL, *pCb = NULL, *pCr = NULL;
  XDAS_Int8  *pCbCrSeperate[4]; /* Pointers to hold seperated Cb and Cr   */
  XDAS_Int8  *pLumaData = NULL;
  XDAS_UInt8  chromaH, chromaV;
  XDAS_Int32 height,frameHeight,frameWidth,frameHeightRounded;
  IVIDEO2_BufDesc           *displayBufs;

  XDAS_Int8* PartialOutChroma = PartialOutLuma + (4096*4096);
  
  /*--------------------------------------------------------------------------*/
  /* If the display buffers mode is of pointers type , then return the        */
  /* pointers else return the buffer address of the bufferDescriptor of       */
  /* display buffer in outArgs                                                */
  /*--------------------------------------------------------------------------*/
  if (outArgs->viddecOutArgs.displayBufsMode == IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddecOutArgs.displayBufs.
    pBufDesc[outArgs->viddecOutArgs.outputID[count]- 1];
  }
  else if (outArgs->viddecOutArgs.displayBufsMode == 
      IVIDDEC3_DISPLAYBUFS_EMBEDDED)
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddecOutArgs.
    displayBufs.bufDesc[0];
  }
  else
  {
    /* Nothing to execute*/
  }
  /*--------------------------------------------------------------------------*/
  /* FrameHeight and FrameWidth as mentioned by the application               */
  /*--------------------------------------------------------------------------*/
  frameHeight = (displayBufs->activeFrameRegion.bottomRight.y -                     
  displayBufs->activeFrameRegion.topLeft.y);                                        
  
  frameWidth  = (displayBufs->activeFrameRegion.bottomRight.x -                     
  displayBufs->activeFrameRegion.topLeft.x);                                        
  /*--------------------------------------------------------------------------*/
  /* Rounding off the framheight to the nearest multiple of 16 , so that      */
  /* if the frameheight is not multiple of 16 , we will discard the           */
  /* other pixels which are extra since in DDR we will be getting the         */
  /* output as multiple of 16                                                 */
  /*--------------------------------------------------------------------------*/
  if((frameHeight % 16) != 0)                                                 
  {                                                                           
    roundingFactor = (16 - (frameHeight % 16));                               
    frameHeightRounded = frameHeight + roundingFactor;                        
  }                                                                           
  else                                                                        
  {                                                                           
    frameHeightRounded = frameHeight;                                         
  }     
  
  /*------------------------------------------------------------------------*/
  /* Outpuit Buffer is in Tiler region Or in Raw region                     */
  /*------------------------------------------------------------------------*/
  if(tilerEnable)
  {
    displayBufs->imagePitch[0] = TILER8_SOURCE_PITCH;
    /*---------------------------------------------------------------------*/
    /* Chroma Buffer in Tiled 16 bit region                                */
    /*---------------------------------------------------------------------*/
    if(chromaTilerMode)
    {
      displayBufs->imagePitch[1] = TILER8_SOURCE_PITCH;
    }
    else
    {
      displayBufs->imagePitch[1] = TILER16_SOURCE_PITCH;
    }
  }
  
  /*--------------------------------------------------------------------------*/
  /* Depending on the chroma format, Horizontal sampling factor and           */
  /* vertical sampling factor is modified , since for comparison we need      */
  /* not to compare all the bytes Ex : if the input is 420 , output of        */
  /* the codec is always Cb/Cr interleaved , so to de-interleave it and       */
  /* compare separately we need these values                                  */
  /*--------------------------------------------------------------------------*/
  switch(displayBufs->chromaFormat)
  {
  case  XDM_YUV_420SP :
  case  XDM_GRAY :
    /*------------------------------------------------------------------------*/
    /* Since both Horizontal and Vertical subsample happens for 420 output    */
    /* , we make both as "1"                                                  */
    /*------------------------------------------------------------------------*/
    chromaH = 1;                                                              
    chromaV = 1;                                                              
    break;                                                                    
    
  case  XDM_YUV_422IBE :                                                      
    /*------------------------------------------------------------------------*/
    /* For 422 Horizontal , only horizontal subsample happens , so making     */
    /* only chroma hori as "1"                                                */
    /*------------------------------------------------------------------------*/
    chromaH = 1;                                                              
    chromaV = 0;                                                              
    break;                                                                    
    
  case  XDM_YUV_422P :                                                        
    /*------------------------------------------------------------------------*/
    /* For 422 Vertical , only Vertical subsample happens , so making         */
    /* only chroma vertical as "1"                                            */
    /*------------------------------------------------------------------------*/
    chromaH = 0;                                                              
    chromaV = 1;                                                              
    break;                                                                    
    
    default :                                                                 
    /*------------------------------------------------------------------------*/
    /* For 444 , Cb , Cr both are not subsampled hence both made as "0"       */
    /*------------------------------------------------------------------------*/
    chromaH = 0;
    chromaV = 0;
    break;
  }  

  if(displayBufs->contentType == IVIDEO_PROGRESSIVE)
  {
    /*------------------------------------------------------------------------*/
    /* Picture size in pixels for luma                                        */
    /*------------------------------------------------------------------------*/
    picSize = frameWidth * frameHeight;

    /*------------------------------------------------------------------------*/
    /* Base address of luma data from the output bufffer given by decoder     */
    /*------------------------------------------------------------------------*/

    if(params.viddecParams.outputDataMode == IVIDEO_NUMROWS)
    {
      pLumaData  = PartialOutLuma;
    }
    else
    {
      pLumaData  = displayBufs->planeDesc[0].buf;
    }    
    
    switch(displayBufs->chromaFormat)
    {
    case  XDM_RGB :
      FWRITE(pLumaData, 1, picSize*3, fOutFile);
      break;    
      
    case  XDM_YUV_422IBE : 
      /*----------------------------------------------------------------------*/
      /* Chroma_seperate is the buffer for storing intermediate output for    */
      /* writing into output file                                             */
      /*----------------------------------------------------------------------*/           
      pLuma = (XDAS_UInt8 *)chromaSeperate;                                   
      /*----------------------------------------------------------------------*/
      /* Initialise the Cb and Cr addresses so as to get the values of Cb     */
      /* and Cr respectively and output the same in the fashion Luma , Cb     */
      /* and Cr (Planar Format)                                               */
      /*----------------------------------------------------------------------*/
      pCb   = pLuma + LUMA_BUFFER_SIZE;                                       
      pCr   = pCb  + (LUMA_BUFFER_SIZE>>1);                                   
      
      loopVar2 = loopVar3 = 0;                                                
      /*----------------------------------------------------------------------*/
      /* Loop to de-interleave YUYV into Y separate , U (Cb) and V(Cr)        */
      /* separate buffers                                                     */
      /*----------------------------------------------------------------------*/
      for(loopVar4 = 0 ; loopVar4 < frameHeight; loopVar4++)
      {
        for(loopVar1 = 0 ; loopVar1 < (frameWidth/2) ; loopVar1++)
        {
          pLuma[loopVar2] = pLumaData[loopVar1*4];  
          loopVar2++;
          pCb[loopVar3]   = pLumaData[(loopVar1*4) + 1];
          pLuma[loopVar2] = pLumaData[(loopVar1*4) + 2];
          pCr[loopVar3]   = pLumaData[(loopVar1*4) + 3];
          loopVar2++;
          loopVar3++;
        }

        pLumaData += (displayBufs->imagePitch[0]);
        
      }
      
      /*----------------------------------------------------------------------*/
      /* Writing the output in the order , Luma , Cb and Cr respectively      */
      /*----------------------------------------------------------------------*/      
      FWRITE (pLuma, 1, frameWidth*frameHeight, fOutFile);
      FWRITE (pCb, 1, (frameWidth*frameHeight)/2, fOutFile);
      FWRITE (pCr, 1, (frameWidth*frameHeight)/2, fOutFile);    
      break;    
      
    case  XDM_YUV_420SP :
    case  XDM_GRAY :
      /*----------------------------------------------------------------------*/
      /* Loop to write the Luma data into output file                         */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<frameHeight ; height++)
      {
        FWRITE (pLumaData, 1, frameWidth, fOutFile);          
        pLumaData  += displayBufs->imagePitch[0];          
      }

      /*----------------------------------------------------------------------*/
      /* Init output yuv_buffer with global pointers                          */
      /* Chroma_seperate is the buffer for storing intermediate output for    */
      /* writing into output file                                             */
      /*----------------------------------------------------------------------*/ 
      pCbCrSeperate[0] = chromaSeperate; 
      pCbCrSeperate[1] = pCbCrSeperate[0] + 
      ((frameHeightRounded * displayBufs->imagePitch[0]) >> 
      (chromaH+chromaV));
      
      if(params.viddecParams.outputDataMode == IVIDEO_NUMROWS)
      {
        pSrc = (XDAS_UInt16 *)PartialOutChroma;
      }
      else
      {
        pSrc = (XDAS_UInt16 *)displayBufs->planeDesc[1].buf;
      }

      /*----------------------------------------------------------------------*/
      /* Initialise the Cb and Cr addresses so as to get the values of Cb     */
      /* and Cr respectively and output the same in the fashion Luma , Cb     */
      /* and Cr (Planar Format)                                               */
      /*----------------------------------------------------------------------*/     
      pDst1             = (XDAS_UInt8 *)pCbCrSeperate[0];                     
      pDst2             = (XDAS_UInt8 *)pCbCrSeperate[1];                     
      /*----------------------------------------------------------------------*/
      /* Looping to separate Cb/Cr interleaved into Cb and Cr separate        */
      /* buffers                                                              */
      /*----------------------------------------------------------------------*/
      for(loopVar2=0 ; loopVar2<(frameHeight>>1) ; loopVar2++)                
      {                                                                       
        for(loopVar1=0 ; loopVar1<(frameWidth>>1) ;                           
        loopVar1++)                                                           
        {                                                                     
          pDst1[loopVar1] = (pSrc[loopVar1] & 0x00FF);                                 
          pDst2[loopVar1] = (pSrc[loopVar1]>>8) & 0x00FF;                           
        }                                                                     
        pSrc  = (XDAS_UInt16 *)((XDAS_UInt32)pSrc + 
        ((XDAS_UInt32) displayBufs->imagePitch[1]));                                
        pDst1 += (frameWidth>>chromaH);                                       
        pDst2 += (frameWidth>>chromaH);                                       
        
      }                                                                       
      /*----------------------------------------------------------------------*/
      /* Writing the separated Cb first and then Cr into an output file       */
      /*----------------------------------------------------------------------*/
      FWRITE(pCbCrSeperate[0], 1, picSize>>(chromaH+chromaV),
      fOutFile);
      FWRITE(pCbCrSeperate[1], 1, picSize>>(chromaH+chromaV),
      fOutFile);
      break;    
      
      default :
      break;
    }
  }
  else
  {
    /* Nothing to execute*/
  }

  FFLUSH(fOutFile);

  return;
} /* TestApp_WriteOutputDataTiled16 */


/**
********************************************************************************
*  @fn          TestApp_WriteOutputData(MYFILE           *fOutFile,
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
XDAS_Void TestApp_WriteOutputData
(
MYFILE           *fOutFile,
IJPEGVDEC_OutArgs *outArgs
)
{
  XDAS_Int32 count = 0;
  XDAS_Int32 roundingFactor, loopVar1, loopVar2, loopVar3,loopVar4;
  XDAS_Int32 picSize;
  XDAS_UInt8 *pSrc = NULL,*pSrc1 = NULL,*pDst1 = NULL, *pDst2 = NULL;
  XDAS_UInt8 *pLuma = NULL, *pCb = NULL, *pCr = NULL;
  XDAS_Int8  *pCbCrSeperate[4]; /* Pointers to hold seperated Cb and Cr   */
  XDAS_Int8  *pLumaData = NULL;
  XDAS_UInt8  chromaH, chromaV;
  XDAS_Int32 height,frameHeight,frameWidth,frameHeightRounded;
  IVIDEO2_BufDesc           *displayBufs;

  XDAS_Int8* PartialOutChroma = PartialOutLuma + (4096*4096);
  
  /*--------------------------------------------------------------------------*/
  /* If the display buffers mode is of pointers type , then return the        */
  /* pointers else return the buffer address of the bufferDescriptor of       */
  /* display buffer in outArgs                                                */
  /*--------------------------------------------------------------------------*/
  if (outArgs->viddecOutArgs.displayBufsMode == IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddecOutArgs.displayBufs.
    pBufDesc[outArgs->viddecOutArgs.outputID[count]- 1];
  }
  else if (outArgs->viddecOutArgs.displayBufsMode == 
      IVIDDEC3_DISPLAYBUFS_EMBEDDED)
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddecOutArgs.
    displayBufs.bufDesc[0];
  }
  else
  {
    /* Nothing to execute*/
  }
  /*--------------------------------------------------------------------------*/
  /* FrameHeight and FrameWidth as mentioned by the application               */
  /*--------------------------------------------------------------------------*/
  frameHeight = (displayBufs->activeFrameRegion.bottomRight.y -                     
  displayBufs->activeFrameRegion.topLeft.y);                                        
  
  frameWidth  = (displayBufs->activeFrameRegion.bottomRight.x -                     
  displayBufs->activeFrameRegion.topLeft.x);                                        
  /*--------------------------------------------------------------------------*/
  /* Rounding off the framheight to the nearest multiple of 16 , so that      */
  /* if the frameheight is not multiple of 16 , we will discard the           */
  /* other pixels which are extra since in DDR we will be getting the         */
  /* output as multiple of 16                                                 */
  /*--------------------------------------------------------------------------*/
  if((frameHeight % 16) != 0)                                                 
  {                                                                           
    roundingFactor = (16 - (frameHeight % 16));                               
    frameHeightRounded = frameHeight + roundingFactor;                        
  }                                                                           
  else                                                                        
  {                                                                           
    frameHeightRounded = frameHeight;                                         
  }     
  
  /*------------------------------------------------------------------------*/
  /* Outpuit Buffer is in Tiler region Or in Raw region                     */
  /*------------------------------------------------------------------------*/
  if(tilerEnable)
  {
    displayBufs->imagePitch[0] = (16*1024);
    /*---------------------------------------------------------------------*/
    /* Chroma Buffer in Tiled 16 bit region                                */
    /*---------------------------------------------------------------------*/
    if(chromaTilerMode)
    {
      displayBufs->imagePitch[1] = (16*1024);
    }
    else
    {
      displayBufs->imagePitch[1] = 2*(16*1024);
    }
  }
  
  /*--------------------------------------------------------------------------*/
  /* Depending on the chroma format, Horizontal sampling factor and           */
  /* vertical sampling factor is modified , since for comparison we need      */
  /* not to compare all the bytes Ex : if the input is 420 , output of        */
  /* the codec is always Cb/Cr interleaved , so to de-interleave it and       */
  /* compare separately we need these values                                  */
  /*--------------------------------------------------------------------------*/
  switch(displayBufs->chromaFormat)
  {
  case  XDM_YUV_420SP :
  case  XDM_GRAY :
    /*------------------------------------------------------------------------*/
    /* Since both Horizontal and Vertical subsample happens for 420 output    */
    /* , we make both as "1"                                                  */
    /*------------------------------------------------------------------------*/
    chromaH = 1;                                                              
    chromaV = 1;                                                              
    break;                                                                    
    
  case  XDM_YUV_422IBE :                                                      
    /*------------------------------------------------------------------------*/
    /* For 422 Horizontal , only horizontal subsample happens , so making     */
    /* only chroma hori as "1"                                                */
    /*------------------------------------------------------------------------*/
    chromaH = 1;                                                              
    chromaV = 0;                                                              
    break;                                                                    
    
  case  XDM_YUV_422P :                                                        
    /*------------------------------------------------------------------------*/
    /* For 422 Vertical , only Vertical subsample happens , so making         */
    /* only chroma vertical as "1"                                            */
    /*------------------------------------------------------------------------*/
    chromaH = 0;                                                              
    chromaV = 1;                                                              
    break;                                                                    
    
    default :                                                                 
    /*------------------------------------------------------------------------*/
    /* For 444 , Cb , Cr both are not subsampled hence both made as "0"       */
    /*------------------------------------------------------------------------*/
    chromaH = 0;
    chromaV = 0;
    break;
  }  

  if(displayBufs->contentType == IVIDEO_PROGRESSIVE)
  {
    /*------------------------------------------------------------------------*/
    /* Picture size in pixels for luma                                        */
    /*------------------------------------------------------------------------*/
    picSize = frameWidth * frameHeight;

    /*------------------------------------------------------------------------*/
    /* Base address of luma data from the output bufffer given by decoder     */
    /*------------------------------------------------------------------------*/

    if(params.viddecParams.outputDataMode == IVIDEO_NUMROWS)
    {
      pLumaData  = PartialOutLuma;
    }
    else
    {
      pLumaData  = displayBufs->planeDesc[0].buf;
    }    
    
    switch(displayBufs->chromaFormat)
    {
    case  XDM_RGB :
      FWRITE(pLumaData, 1, picSize*3, fOutFile);
      break;    
      
    case  XDM_YUV_422IBE : 
      /*----------------------------------------------------------------------*/
      /* Chroma_seperate is the buffer for storing intermediate output for    */
      /* writing into output file                                             */
      /*----------------------------------------------------------------------*/           
      pLuma = (XDAS_UInt8 *)chromaSeperate;                                   
      /*----------------------------------------------------------------------*/
      /* Initialise the Cb and Cr addresses so as to get the values of Cb     */
      /* and Cr respectively and output the same in the fashion Luma , Cb     */
      /* and Cr (Planar Format)                                               */
      /*----------------------------------------------------------------------*/
      pCb   = pLuma + LUMA_BUFFER_SIZE;                                       
      pCr   = pCb  + (LUMA_BUFFER_SIZE>>1);                                   
      
      loopVar2 = loopVar3 = 0;                                                
      /*----------------------------------------------------------------------*/
      /* Loop to de-interleave YUYV into Y separate , U (Cb) and V(Cr)        */
      /* separate buffers                                                     */
      /*----------------------------------------------------------------------*/
      for(loopVar4 = 0 ; loopVar4 < frameHeight; loopVar4++)
      {
        for(loopVar1 = 0 ; loopVar1 < (frameWidth/2) ; loopVar1++)
        {
          pLuma[loopVar2] = pLumaData[loopVar1*4];  
          loopVar2++;
          pCb[loopVar3]   = pLumaData[(loopVar1*4) + 1];
          pLuma[loopVar2] = pLumaData[(loopVar1*4) + 2];
          pCr[loopVar3]   = pLumaData[(loopVar1*4) + 3];
          loopVar2++;
          loopVar3++;
        }

        pLumaData += (displayBufs->imagePitch[0]);
        
      }
      
      /*----------------------------------------------------------------------*/
      /* Writing the output in the order , Luma , Cb and Cr respectively      */
      /*----------------------------------------------------------------------*/      
      FWRITE (pLuma, 1, frameWidth*frameHeight, fOutFile);
      FWRITE (pCb, 1, (frameWidth*frameHeight)/2, fOutFile);
      FWRITE (pCr, 1, (frameWidth*frameHeight)/2, fOutFile);    
      break;    
      
    case  XDM_YUV_420SP :
    case  XDM_GRAY :
      /*----------------------------------------------------------------------*/
      /* Loop to write the Luma data into output file                         */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<frameHeight ; height++)
      {
        FWRITE (pLumaData, 1, frameWidth, fOutFile);          
        pLumaData  += displayBufs->imagePitch[0];          
      }

      /*----------------------------------------------------------------------*/
      /* Init output yuv_buffer with global pointers                          */
      /* Chroma_seperate is the buffer for storing intermediate output for    */
      /* writing into output file                                             */
      /*----------------------------------------------------------------------*/ 
      pCbCrSeperate[0] = chromaSeperate; 
      pCbCrSeperate[1] = pCbCrSeperate[0] + 
      ((frameHeightRounded * displayBufs->imagePitch[0]) >> 
      (chromaH+chromaV));
      
      if(params.viddecParams.outputDataMode == IVIDEO_NUMROWS)
      {
        pSrc = (XDAS_UInt8 *)PartialOutChroma;
      }
      else
      {
        pSrc = (XDAS_UInt8 *)displayBufs->planeDesc[1].buf;
      }

      pSrc1 = pSrc + ((frameHeightRounded/2) * displayBufs->imagePitch[1]);
      
      /*----------------------------------------------------------------------*/
      /* Initialise the Cb and Cr addresses so as to get the values of Cb     */
      /* and Cr respectively and output the same in the fashion Luma , Cb     */
      /* and Cr (Planar Format)                                               */
      /*----------------------------------------------------------------------*/     
      pDst1             = (XDAS_UInt8 *)pCbCrSeperate[0];                     
      pDst2             = (XDAS_UInt8 *)pCbCrSeperate[1];                     
      /*----------------------------------------------------------------------*/
      /* Looping to separate Cb/Cr interleaved into Cb and Cr separate        */
      /* buffers                                                              */
      /*----------------------------------------------------------------------*/
      for(loopVar2=0 ; loopVar2<(frameHeight>>1) ; loopVar2++)                
      {                                                                       
        for(loopVar1=0 ; loopVar1<(frameWidth>>1) ;                           
        loopVar1++)                                                           
        {                                                                     
          pDst1[loopVar1] = pSrc[loopVar1*2];                                 
          pDst2[loopVar1] = pSrc[(loopVar1*2) + 1];                           
        }                                                                     
        pSrc  += (displayBufs->imagePitch[1]);                                
        pDst1 += (frameWidth>>chromaH);                                       
        pDst2 += (frameWidth>>chromaH);                                       
        
      }                                                                       
      /*----------------------------------------------------------------------*/
      /* Writing the separated Cb first and then Cr into an output file       */
      /*----------------------------------------------------------------------*/
      FWRITE(pCbCrSeperate[0], 1, picSize>>(chromaH+chromaV),
      fOutFile);
      FWRITE(pCbCrSeperate[1], 1, picSize>>(chromaH+chromaV),
      fOutFile);
      break;    
      
    case  XDM_YUV_444P :
      /*----------------------------------------------------------------------*/
      /* Loop to write the Luma data into output file                         */
      /*----------------------------------------------------------------------*/ 
      for(height=0 ; height<frameHeight ; height++)
      {
        FWRITE (pLumaData, 1, frameWidth, fOutFile);          
        pLumaData  += displayBufs->imagePitch[0];          
      }

      /*----------------------------------------------------------------------*/
      /* Init output yuv_buffer with global pointers                          */
      /* Chroma_seperate is the buffer for storing intermediate output for    */
      /* writing into output file                                             */
      /*----------------------------------------------------------------------*/

      pCbCrSeperate[0] = chromaSeperate; 
      pCbCrSeperate[1] = pCbCrSeperate[0] + 
      ((frameHeightRounded * displayBufs->imagePitch[0]) >> 
      (chromaH+chromaV));

      if(params.viddecParams.outputDataMode == IVIDEO_NUMROWS)
      {
        pSrc = (XDAS_UInt8 *)PartialOutChroma;
        pSrc1 = pSrc + (4096 * 4096);
      }
      else
      {
        pSrc = (XDAS_UInt8 *)displayBufs->planeDesc[1].buf; 
        pSrc1 = (XDAS_UInt8 *)displayBufs->planeDesc[2].buf;
      }

      /*----------------------------------------------------------------------*/
      /* Initialise the Cb and Cr addresses so as to get the values of Cb     */
      /* and Cr respectively and output the same in the fashion Luma , Cb     */
      /* and Cr (Planar Format)                                               */
      /*----------------------------------------------------------------------*/     
      pDst1 = pSrc;
      pDst2 = pSrc1;
      /*----------------------------------------------------------------------*/
      /* Write the saperated out CB and CR in to YUV output file              */
      /*----------------------------------------------------------------------*/
      for(height=0 ; height<frameHeight ; height++)
      {
        FWRITE(pSrc, 1, frameWidth, fOutFile);          
        pSrc  += displayBufs->imagePitch[1];    
      }
      for(height=0 ; height<frameHeight ; height++)
      {
        FWRITE(pSrc1, 1, frameWidth, fOutFile);
        pSrc1  += displayBufs->imagePitch[2];
      } 
      break;   
      
    case XDM_YUV_420P :
      /*----------------------------------------------------------------------*/
      /* Loop to write the Luma data into output file                         */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<frameHeight ; height++)
      {
        FWRITE (pLumaData, 1, frameWidth, fOutFile);          
        pLumaData  += displayBufs->imagePitch[0];          
      }

      pSrc = (XDAS_UInt8 *)displayBufs->planeDesc[1].buf; 
      pSrc1 = (XDAS_UInt8 *)displayBufs->planeDesc[2].buf;     
      /*----------------------------------------------------------------------*/
      /* Loop to write the Cb data into output file                           */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<(frameHeight>>1) ; height++)
      {
        FWRITE (pSrc, 1, (frameWidth>>1), fOutFile);          
        pSrc  += (displayBufs->imagePitch[1]>>1);          
      }  
      /*----------------------------------------------------------------------*/
      /* Loop to write the Cr data into output file                           */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<(frameHeight>>1) ; height++)
      {
        FWRITE (pSrc1, 1, (frameWidth>>1), fOutFile);          
        pSrc1  += (displayBufs->imagePitch[2]>>1);          
      }         
      
      break;
      
    case XDM_YUV_422P :
      /*----------------------------------------------------------------------*/
      /* Loop to write the Luma data into output file                         */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<frameHeight ; height++)
      {
        FWRITE (pLumaData, 1, frameWidth, fOutFile);          
        pLumaData  += displayBufs->imagePitch[0];          
      }

      pSrc = (XDAS_UInt8 *)displayBufs->planeDesc[1].buf; 
      pSrc1 = (XDAS_UInt8 *)displayBufs->planeDesc[2].buf;     
      /*----------------------------------------------------------------------*/
      /* Loop to write the Cb data into output file                           */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<(frameHeight) ; height++)
      {
        FWRITE (pSrc, 1, (frameWidth>>1), fOutFile);          
        pSrc  += (displayBufs->imagePitch[1]);          
      }  
      /*----------------------------------------------------------------------*/
      /* Loop to write the Cr data into output file                           */
      /*----------------------------------------------------------------------*/       
      for(height=0 ; height<(frameHeight) ; height++)
      {
        FWRITE (pSrc1, 1, (frameWidth>>1), fOutFile);          
        pSrc1  += (displayBufs->imagePitch[2]);          
      }         
      
      break;
      
      default :
      break;
    }
  }
  else
  {
    /* Nothing to execute*/
  }

  FFLUSH(fOutFile);

  return;
} /* TestApp_WriteOutputData */


/**
*******************************************************************************
*  @fn         MEMUTILS_getPhysicalAddr(Ptr Addr)
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
XDM_DataSyncDesc *dataSyncDescrRowLevel)
{
  volatile int* pNumBlocks =  &dataSyncDescrRowLevel->numBlocks;
  IVIDEO2_BufDesc           *displayBufs;
  XDAS_Int8* pLumaData, *pChromaData;
  unsigned int loopVar, Lumabytes, frameWidth, frameHeight;
  XDAS_Int8* pLuma ;
  XDAS_Int8* pChroma;
  XDAS_Int32 Offset, Width;
  XDAS_Int32 LoopHeight;
  XDAS_Int8* PartialOutChroma = PartialOutLuma + (4096*4096);
  XDAS_Int32 actualStartBlock;
  XDAS_Int32 endBlock = 0; 
  
  if (OutFlag == 0)
  {
    StartBlock = 0;
    OutFlag = 1;
  }
  actualStartBlock   = StartBlock;
  endBlock    = actualStartBlock + *pNumBlocks; 
  StartBlock  = endBlock;
  
  /*--------------------------------------------------------------------------*/
  /* The MCU sizes are different of each chroma format. For all chroma format */
  /* execpt 420 one 'row' is 8 line and for 420 chroma format it is 16 lines  */
  /*--------------------------------------------------------------------------*/  
  if (outArgs.viddecOutArgs.displayBufsMode == IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs.viddecOutArgs.displayBufs.
    pBufDesc[outArgs.viddecOutArgs.outputID[0]- 1];
  }
  else if (outArgs.viddecOutArgs.displayBufsMode == 
      IVIDDEC3_DISPLAYBUFS_EMBEDDED)
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs.viddecOutArgs.
    displayBufs.bufDesc[0];
  }
  if(displayBufs->chromaFormat == XDM_YUV_422IBE )
  {
    displayBufs->activeFrameRegion.topLeft.y       = actualStartBlock * 8;
    displayBufs->activeFrameRegion.bottomRight.y   = endBlock * 8;
  }
  else if(displayBufs->chromaFormat == XDM_YUV_444P)
  {
    displayBufs->activeFrameRegion.topLeft.y       = actualStartBlock * 8;
    displayBufs->activeFrameRegion.bottomRight.y   = endBlock * 8;
  }
  else
  {
    if(outArgs.IsGrayFlag == 1 ) /* if the format is Gray scale */
    {
      displayBufs->activeFrameRegion.topLeft.y     = actualStartBlock * 8;
      displayBufs->activeFrameRegion.bottomRight.y = endBlock * 8 ;
    }
    else
    {
      displayBufs->activeFrameRegion.topLeft.y     = actualStartBlock * 16;
      displayBufs->activeFrameRegion.bottomRight.y = endBlock * 16;
    }
  }
  
  /*--------------------------------------------------------------------------*/
  /* Copy  the Output in Rows in Temporary Buffer                             */ 
  /*--------------------------------------------------------------------------*/
  
  frameWidth  = (displayBufs->activeFrameRegion.bottomRight.x -                     
  displayBufs->activeFrameRegion.topLeft.x);
  
  frameHeight = (displayBufs->activeFrameRegion.bottomRight.y -                     
  displayBufs->activeFrameRegion.topLeft.y);


  if(displayBufs->chromaFormat == XDM_YUV_422IBE ) /* Only for 422 Format */
  {                 
    Offset    = displayBufs->imagePitch[0]; 
    Lumabytes = (frameWidth << 1);              
    Width     = (displayBufs->imagePitch[0]);
  }
  else
  {
    Offset    = displayBufs->imagePitch[0];   
    Lumabytes = frameWidth;                   
    Width     = (displayBufs->imagePitch[0]);
  }  
  
  pLumaData  = displayBufs->planeDesc[0].buf + 
  (Offset * displayBufs->activeFrameRegion.topLeft.y);
  pLuma = PartialOutLuma + (Offset * displayBufs->activeFrameRegion.topLeft.y);
  
  /*--------------------------------------------------------------------------*/
  /* Copy Luma into temporary Buffer                                          */
  /*--------------------------------------------------------------------------*/ 
  for(loopVar = 0 ; loopVar < frameHeight; loopVar++)
  {
    memcpy(pLuma,   pLumaData,  Lumabytes);
    pLumaData += Offset;
    pLuma += Offset;
  }
  
  if(displayBufs->chromaFormat != XDM_YUV_422IBE)
  {
    if((displayBufs->chromaFormat == XDM_YUV_420SP)||
        (displayBufs->chromaFormat == XDM_GRAY))
    {
      Offset     = displayBufs->imagePitch[1] ; 
      Width      = (displayBufs->imagePitch[1]) ;
      LoopHeight = frameHeight >> 1;
      
      /* Copy Chroma Interleaved */
      pChromaData = displayBufs->planeDesc[1].buf + 
      (Offset * displayBufs->activeFrameRegion.topLeft.y >> 1);
      pChroma   = PartialOutChroma + 
      (Offset * displayBufs->activeFrameRegion.topLeft.y >> 1 );
      
      /*----------------------------------------------------------------------*/ 
      /* Copy Chroma into temporary Buffer                                    */
      /*----------------------------------------------------------------------*/ 
      for(loopVar = 0 ; loopVar < LoopHeight; loopVar++)
      {
        memcpy(pChroma,   pChromaData,  Width);
        pChromaData += Width;
        pChroma += Width;
      }
    }
    else /* For 444 P */
    {
      Offset     = displayBufs->imagePitch[1] ; 
      Width      = (displayBufs->imagePitch[1]) ;
      LoopHeight = frameHeight;
      
      /* Cb */
      pChromaData = displayBufs->planeDesc[1].buf + 
      (Offset * displayBufs->activeFrameRegion.topLeft.y);
      pChroma   = PartialOutChroma + 
      (Offset * displayBufs->activeFrameRegion.topLeft.y);

      /*----------------------------------------------------------------------*/ 
      /* Copy Cb into temporary Buffer                                        */
      /*----------------------------------------------------------------------*/ 
      for(loopVar = 0 ; loopVar < LoopHeight; loopVar++)
      {
        memcpy(pChroma,   pChromaData,  Width);
        pChromaData += Width;
        pChroma += Width;
      }
      
      /* Cr */
      pChromaData = displayBufs->planeDesc[2].buf + 
      (Offset * displayBufs->activeFrameRegion.topLeft.y);
      pChroma   = PartialOutChroma + 
      (Offset * displayBufs->activeFrameRegion.topLeft.y) + 
      (4096 * 4096);
      
      /*----------------------------------------------------------------------*/ 
      /* Copy Cr into temporary Buffer                                        */
      /*----------------------------------------------------------------------*/ 
      for(loopVar = 0 ; loopVar < LoopHeight; loopVar++)
      {
        memcpy(pChroma,   pChromaData,  Width);
        pChromaData += Width;
        pChroma += Width;
      }
    }
  }
  return;
}


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
XDM_DataSyncDesc* dataSyncDescrFixedLength)
{
  if(params.viddecParams.inputDataMode == IVIDEO_FIXEDLENGTH)
  {
    /*------------------------------------------------------------------------*/ 
    /* For fixed length mode the 'numBlocks' is '1' (TI's Constraint).        */
    /* then the scatteredBlocksFlag and varBlockSizesFlag will be false       */
    /*------------------------------------------------------------------------*/ 
    dataSyncDescrFixedLength->numBlocks = 1;
    
    dataSyncDescrFixedLength->scatteredBlocksFlag = XDAS_FALSE; 
    dataSyncDescrFixedLength->varBlockSizesFlag   = XDAS_FALSE;
    
    /*------------------------------------------------------------------------*/ 
    /* Provide the stream buffer pointer and its length to the Codec          */
    /*------------------------------------------------------------------------*/ 
    blockSizeArray[0]                      = curr_ddr_bytes;
    dataSyncDescrFixedLength->blockSizes   = (XDAS_Int32 *)&blockSizeArray[0];
    dataSyncDescrFixedLength->baseAddr     = (XDAS_Int32*)curr_ddr_addr[0];
    curr_ddr_addr[0]  += curr_ddr_bytes;
    bytes_ddr      -= curr_ddr_bytes;
    curr_ddr_bytes  = ((bytes_ddr >= 8192) ? (8192) : (bytes_ddr));
  }
  else if(params.viddecParams.inputDataMode == IVIDEO_SLICEMODE)
  {
    if(params.sliceSwitchON == 1)
    {
    dataSyncDescrFixedLength->numBlocks = blockPerDataSync[SlcSwitchCount];
    dataSyncDescrFixedLength->baseAddr   =
    (XDAS_Int32*)&curr_ddr_addr[GblCount];
    SlcSwitchCount++;
    }
    else
    {    
    dataSyncDescrFixedLength->numBlocks = blockPerDataSync[GblCount];
    dataSyncDescrFixedLength->baseAddr   =
    (XDAS_Int32*)&curr_ddr_addr[AccCount];
    }
    dataSyncDescrFixedLength->scatteredBlocksFlag = XDAS_TRUE; 
    dataSyncDescrFixedLength->varBlockSizesFlag   = XDAS_TRUE;

    /*------------------------------------------------------------------------*/ 
    /* Provide the stream buffer pointer and its length to the Codec          */
    /*------------------------------------------------------------------------*/
    dataSyncDescrFixedLength->blockSizes = 
    (XDAS_Int32 *)&blockSizeArray[AccCount];

    
    /*------------------------------------------------------------------------*/
    /* Updating the global variable useful in fetching the right buffers and  */
    /* sizes fpr next data sync                                               */
    /*------------------------------------------------------------------------*/
    AccCount += blockPerDataSync[GblCount];
    //printf("Datasync counts\n");
    GblCount++;
  }
  return;
}

/**
********************************************************************************
*  @fn          TestApp_SetInitParams(IVIDDEC3_Params *params)
*
*  @brief       Initalizes the init parameter structure with proper values
*
*  @param [out]   params             :  Init parameter structure.
*
*  @return      None
********************************************************************************
*/
XDAS_Void TestApp_SetInitParams(IVIDDEC3_Params *params)
{
  /*--------------------------------------------------------------------------*/
  /* Set IVIDDEC3 parameters                                                  */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /* Max Height and max width of the Image                                    */
  /*--------------------------------------------------------------------------*/
  params->maxHeight             = IMAGE_HEIGHT;                               
  params->maxWidth              = IMAGE_WIDTH;                                
  
  /*--------------------------------------------------------------------------*/
  /* Max Frame Rate: Not currently used in the algorithm                      */
  /*--------------------------------------------------------------------------*/
  params->maxFrameRate        = MAX_FRAME_RATE;                               
  
  /*--------------------------------------------------------------------------*/
  /* Max Bit Rate: Not currently used in the algorithm                        */
  /*--------------------------------------------------------------------------*/
  params->maxBitRate          = MAX_BIT_RATE;                                 
  
  /*--------------------------------------------------------------------------*/
  /* Data Endianness (1: Big) : only Big Endian supported                     */
  /*--------------------------------------------------------------------------*/
  params->dataEndianness      = XDM_BYTE;

  params->forceChromaFormat   = XDM_YUV_420SP;
  params->operatingMode       = IVIDEO_DECODE_ONLY;

  params->inputDataMode       = IVIDEO_ENTIREFRAME; /* IVIDEO_SLICEMODE */ 
  /*IVIDEO_SLICEMODE  */ 
  /*IVIDEO_FIXEDLENGTH*/
  params->outputDataMode      = IVIDEO_ENTIREFRAME;/* IVIDEO_NUMROWS */

  params->numOutputDataUnits     = 1;
  params->numInputDataUnits      = 1;
  params->errorInfoMode          = IVIDEO_ERRORINFO_OFF;
  params->displayBufsMode        = IVIDDEC3_DISPLAYBUFS_EMBEDDED;
} /* TestApp_SetInitParams */


/**
********************************************************************************
*  @fn          TestApp_SetDynamicParams(IJPEGVDEC_DynamicParams *dynamicParams)
*
*  @brief       Initalizes the Dynamic parameter structure with proper values
*
*  @param[out]   dynamicParams     :  Init Dynamic parameter structure.
*
*  @return      None
********************************************************************************
*/
XDAS_Void TestApp_SetDynamicParams(IJPEGVDEC_DynamicParams *dynamicParams)
{
  /*--------------------------------------------------------------------------*/
  /* Set IVIDDEC3 Run time parameters  (these values could be modified to     */
  /* use the decoder with different configurations)                           */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /* 1. Decode header :  Making this parameter "XDM_PARSE_HEADER" , we can    */
  /*                     verify the functionality of header only decoding     */
  /*                     support                                              */
  /* 2. DisplayWidth  :  If set to zero, use the decoded image width.         */
  /*                     Else, use given display width in pixels.             */
  /*                     Display width has to be greater than or equal to     */
  /*                     image width.                                         */
  /* 3. decodeThumbnail  :  By Enabling this parameter , we can decode the    */
  /*                        thumbnail Image present in the given input and    */
  /*                        can be given it to display                        */
  /* 4. thumbnailMode  :  Specifies which thumbnail to decode. If none of     */
  /*                      the markers (JFIF and EXIF) have thumbnail          */
  /*                      image, use IJPEGVDEC_THUMBNAIL_DOWNSAMPLE. Refer to */
  /*                      ethumbnailMode  enumeration                         */
  /* 5. downsamplingFactor  : If decodeThumbnail is enabled and               */
  /*                          thumbnailMode is set to                         */
  /*                            IJPEGVDEC_THUMBNAIL_DOWNSAMPLE                */
  /*                          downsamplingFactor is used as scaling factor    */
  /*                          for ThumNail output .If decodeThumbnail is      */
  /*                          disabled, this parameter is used as scaling     */
  /*                          factor for display buffer output. Refer to      */
  /*                          edownSamplingFactor                             */
  /* 6. streamingCompliant  :  If an Input Image is Non-Interleaved ,         */
  /*                           This parameter  has to be set to "0" (DISABLE),*/
  /*                           if it is Interleaved , value will be "1"       */
  /*                           (ENABLE). This Paramater along with            */
  /*                           ForceChromaFormat determines whether we        */
  /*                           have to give Planar Buffers from GetBufinfo.   */
  /*--------------------------------------------------------------------------*/
  dynamicParams->viddecDynamicParams.decodeHeader  = XDM_DECODE_AU;
  dynamicParams->viddecDynamicParams.displayWidth  = 0;
  dynamicParams->decodeThumbnail                   = DISABLE;
  dynamicParams->thumbnailMode                     = IJPEGVDEC_THUMBNAIL_EXIF;
  dynamicParams->downsamplingFactor                = IJPEGVDEC_NODOWNSAMPLE;
  dynamicParams->streamingCompliant                = DISABLE;
  /*--------------------------------------------------------------------------*/
  /*Not Supported                                                             */
  /*--------------------------------------------------------------------------*/
  dynamicParams->viddecDynamicParams.frameSkipMode = IVIDEO_NO_SKIP;
  dynamicParams->viddecDynamicParams.newFrameFlag  = XDAS_FALSE;
  dynamicParams->viddecDynamicParams.getDataFxn    = NULL;
  dynamicParams->viddecDynamicParams.getDataHandle = NULL;
  dynamicParams->viddecDynamicParams.putDataFxn    = NULL;
  dynamicParams->viddecDynamicParams.putDataHandle = NULL;
  dynamicParams->viddecDynamicParams.lateAcquireArg  = 
  IRES_HDVICP2_UNKNOWNLATEACQUIREARG;  

  if((params.viddecParams.inputDataMode == IVIDEO_FIXEDLENGTH)
      || (params.viddecParams.inputDataMode == IVIDEO_SLICEMODE))
  {
    /*------------------------------------------------------------------------*/
    /*    assign dataSynch callBack function pointers to encoder dynamicParams*/
    /*------------------------------------------------------------------------*/
    
    /*------------------------------------------------------------------------*/
    /*    INPUT DATA SYNC Function Pointer                                    */
    /*------------------------------------------------------------------------*/
    dynamicParams->viddecDynamicParams.getDataFxn    =
    (XDM_DataSyncGetFxn)JPEGVDEC_TI_GetDataCallBack;
    /*------------------------------------------------------------------------*/
    /* Populate the function pointer for putBuffer function.                  */
    /* Note: the putBufferHandle and getDataHandle can be used by the app     */
    /* to indicate any additional info related to the putBuffer call          */
    /* Here we do not use this handle for any further processing hence setting*/
    /* them to NULL                                                           */
    /*------------------------------------------------------------------------*/  

    dynamicParams->viddecDynamicParams.putBufferFxn    = 
                                  (XDM_DataSyncPutBufferFxn)&JPEGVDEC_PutBuffer;
    dynamicParams->viddecDynamicParams.putBufferHandle = NULL;

    dynamicParams->viddecDynamicParams.getDataHandle = NULL;
  }
  if(params.viddecParams.outputDataMode == IVIDEO_NUMROWS)
  {  
    /*------------------------------------------------------------------------*/
    /* OUTPUT DATA SYNC Function Pointer                                      */
    /*------------------------------------------------------------------------*/
    dynamicParams->viddecDynamicParams.putDataFxn      =
    (XDM_DataSyncPutFxn)JPEGVDEC_TI_PutDataCallBack;
    dynamicParams->viddecDynamicParams.putDataHandle = NULL;
  }

}/* TestApp_SetDynamicParams */

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
  /*-------------------------------------------------------------------*/
  /* The default values set in gel files is 0x8000000 which will       */
  /* overlap on the .text mapped in client. Hence, to avoid corruption */
  /* of vital memory we are mapping the tiler base address to a        */
  /* different value.                                                  */
  /*-------------------------------------------------------------------*/
#if (HOSTCORTEXM3_NETRA_IVAHD0 || HOSTCORTEXM3_NETRA_IVAHD1 || \
        HOSTCORTEXM3_NETRA_IVAHD2 || HOSTCORTEXM3_NETRASIMULATOR)
  /*-------------------------------------------------------------------*/
  /* Tiler is mapped to following physical container addresses:        */
  /* TILE8_PHY_ADDR -  0xA000 0000 -> 0xA800 0000                      */
  /* TILE16_PHY_ADDR - 0xA800 0000 -> 0xB000 0000                      */
  /* TILE32_PHY_ADDR - 0xB000 0000 -> 0xB800 0000                      */
  /* TILEPG_PHY_ADDR - 0xB000 0000 -> 0xB800 0000                      */
  /* Tiler32 & TilePG are overlayed with assumption that Tile32 is not */ 
  /* used                                                              */
  /*-------------------------------------------------------------------*/

  *(int *)(0x4E000440) = 0x06060504; 
  *(int *)(0x4E000444) = 0x06060504; 
  *(int *)(0x4E000448) = 0x06060504; 
  *(int *)(0x4E00044C) = 0x06060504; 

  *(int *)(0x4E000460) = 0x80000000; 

  *(int *)(0x4E000480) = 0x00000003; 
  *(int *)(0x4E0004C0) = 0x0000000B; 
  *(int *)(0x4E000504) = 0x3FFF20E0;
  *(int *)(0x4E00050C) = 0x8510F010;
#endif  

#if (HOSTCORTEXM3_OMAP4 || HOSTCORTEXM3_OMAP4SIMULATOR)
  /*-------------------------------------------------------------------*/ 
  /* Tiler is mapped to following physical container addresses:        */
  /* TILE8_PHY_ADDR -  0x9000 0000 -> 0x9800 0000                      */
  /* TILE16_PHY_ADDR - 0x9800 0000 -> 0xA000 0000                      */
  /* TILE32_PHY_ADDR - 0xA000 0000 -> 0xA800 0000                      */
  /* TILEPG_PHY_ADDR - 0xA000 0000 -> 0xA800 0000                      */
  /* Tiler32 & TilePG are overlayed with assumption that Tile32 is not */ 
  /* used                                                              */
  /*-------------------------------------------------------------------*/

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
}

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
XDAS_Void testAppTilerInit(XDM2_BufSize *bufSizes)
{
  XDAS_Int8    ret_val;
  /*-----------------------------------------------------------------------*/
  /*  Get the buffers in TILER space                                       */
  /*-----------------------------------------------------------------------*/
  if(tilerEnable)
  {
    sTilerParams *pTilerParams     = &tilerParams;

    /*---------------------------------------------------------------------*/
    /* Set the base address of the tiler memory area allocated by the      */
    /* tiler library.                                                      */
    /*---------------------------------------------------------------------*/
    SetPATViewMapBase();

    /*---------------------------------------------------------------------*/
    /* Get the buffers in TILER space                                      */
    /* Do the allocation for maximum supported resoultion and keep to some */
    /* aligned boundary. Also this allocation assumes that tiled8 and      */
    /* tiled16 are mapped to same physical space                           */
    /*---------------------------------------------------------------------*/
    pTilerParams->tilerSpace[0]    = CONTAINER_8BITS;
    pTilerParams->tilerSpace[1]    = CONTAINER_16BITS;
    
    if(chromaTilerMode)
    {
      pTilerParams->tilerSpace[1]  = CONTAINER_8BITS;
    }

    pTilerParams->imageDim[0]      = 1920;     
    pTilerParams->imageDim[1]      = 1088;

    pTilerParams->totalSizeLuma    = 0x4800000; 

    pTilerParams->memoryOffset[0]  = 0; 
    pTilerParams->memoryOffset[1]  = pTilerParams->totalSizeLuma;

    ret_val = tiler_init(pTilerParams);
    if(ret_val == -1)
    {
      /*-------------------------------------------------------------------*/
      /* If tiler allocation is not successful then Force both the buffer  */
      /* to be in raw region                                               */
      /*-------------------------------------------------------------------*/
      tilerEnable = 0 ;
    }
  }
}
/** 
********************************************************************************
 *  @fn     JPEGVDEC_PutBuffer
 *  @brief  The function is an Application function to release the bit stream 
 *          buffer that is consumed by the decoder.
 *
 *  @param[in] putDataHandle  : Handle for putdata function.
 *          
 *  @param[in] dataSyncParams  : The datasync descriptor
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void JPEGVDEC_PutBuffer(XDM_DataSyncHandle putDataHandle, 
                             XDM_DataSyncDesc *dataSyncParams)
{
  /*------------------------------------------------------------------------*/
  /* Just Increment the putBuffer count and print number of blocks availabel*/
  /* in the putBuffer call                                                  */
  /*------------------------------------------------------------------------*/
  putBufferCount++;
  //printf("PutBufferFxn Count: %d, NumBlocks: %d \n", putBufferCount, 
  //        dataSyncParams->numBlocks);
  
}
