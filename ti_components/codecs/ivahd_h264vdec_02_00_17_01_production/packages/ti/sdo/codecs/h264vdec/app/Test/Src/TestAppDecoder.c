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

/**  
*******************************************************************************
 * @file <TestAppDecoder.c>                          
 *                                       
 * @brief  This file is a H.264 Decoder Sample test application
 *
 *         This file has H.264 Decoder sample test app functions to understand
 *         the usage of codec function calls during integration. 
 *  
 * @author: Pavan Shastry
 *
 * @version 0.0 (Jan 2008)  : Base version 
 * @version 0.1 (Sept 2009) : Modifications to read the new config file.
 *                            [Ramakrishna]
 * @version 0.2 (July 2010) : More code commenting and cleanup
 *                            [Ramakrishna]
 * @version 0.3 (Oct 2010) : Fix issue corresponds to Frame Size bit-stream mode
 *                           and parse header combination run
 *                           [Ramakrishna]
 * @version 0.4 (Nov 2010) : Changes for Debug Trace
 *                           [Resmi]
 * @version 0.5 (June 2011)  :Added feature of dual yuv support in order dump 
 *                           dual yuv.
 *                           [Vijay Kumar Yadav] 
 * @version 0.6 (Oct 2011) : Added WaterMark support to the decoder.
 *                           [Suresh Reddy]
 ******************************************************************************
*/
/******************************************************************************
*  INCLUDE FILES                                                
******************************************************************************/
#include <xdc/std.h>
#include <TestAppDecoder.h>
#include <TestApp_rmanConfig.h>
#include <tilerBuf.h>

/******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
******************************************************************************/
#ifdef HOST_ARM9
void dummy(void);
#endif
extern void testAppHandleMetadata(sAppControlParams appControlPrms, 
                           XDM2_BufDesc outputBufDesc, int message, 
                           XDAS_Int32 chnlNum);
/*----------------------------------------------------------------------------*/
/*  Data Sync specific variables.                                             */
/*----------------------------------------------------------------------------*/
XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS];
XDAS_UInt32 curr_ddr_addr, bytes_ddr, curr_ddr_bytes;
XDAS_UInt16 DataSyncIntrCntr;
XDAS_UInt8 *sreamDst;
XDAS_Int32 putBufferCount;

FILE *fCycles; 

/*----------------------------------------------------------------------------*/
/*  Input buffer allocation                                                   */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(inputData, ".input");
#pragma DATA_SECTION(inputDataScatBlocks, ".input");
XDAS_Int8  inputData[INPUT_BUFFER_SIZE];
XDAS_Int8  inputDataScatBlocks[NUM_BUFS_INPUTDS][INPUT_DATASYNC_BUFFER_SIZE];
XDAS_UInt32 dsBufIdx;
/**
 *  Macro to indicate the buffer size needed to hold the version of codec
 */
#define VERSION_BUF_SIZE 100

/*----------------------------------------------------------------------------*/
/*  Global Structure variables for static and dynamic params.                 */
/*----------------------------------------------------------------------------*/
H264VDEC_Params          params;
H264VDEC_DynamicParams   dynamicParams;

/*----------------------------------------------------------------------------*/
/*  Global Structure variables for application control params                 */
/*----------------------------------------------------------------------------*/
sAppControlParams        appControlPrms;

/*----------------------------------------------------------------------------*/
/*  Global Structure variables for application file pointers                  */
/*----------------------------------------------------------------------------*/
sProfileParams           profilePrms;
sTilerParams             tilerParams;

/*----------------------------------------------------------------------------*/
/* Scratch buffer for interleaving the data                                   */
/*----------------------------------------------------------------------------*/
XDAS_Int32          fieldBuf;
XDAS_UInt32         streamEnded = XDAS_FALSE;

/*--------------------------------------------------------------------------*/
/*  Counter for tracking the number of testvectors                          */
/*--------------------------------------------------------------------------*/
XDAS_Int32    countConfigSet;
XDAS_UInt8    appIvahdId;

/*--------------------------------------------------------------------------*/
/* bytesConsumedNalFormat : Bytes consumed for the NAL format, A separate   */           
/*                          variable is needed since there is no start code */
/* firstDataSyncCallInFrame : Flag to distinguish the first datasync call   */
/*                            with the subsequenct calls. This is a special */
/*                            case since the input can have any size for the*/
/*                            first input datasync call.                    */
/*--------------------------------------------------------------------------*/
XDAS_UInt32 bytesConsumedNalFormat;
XDAS_UInt32 firstDataSyncCallInFrame = 1;
/*--------------------------------------------------------------------------*/
/* Conter to keep track of row number when output Datasync is enabled       */
/*--------------------------------------------------------------------------*/
XDAS_UInt32        rowNum;

/*--------------------------------------------------------------------------*/ 
/* File pointer for the file that logs status of each config.               */
/* And variables needed for staus logging                                   */
/*--------------------------------------------------------------------------*/ 
FILE *fLogFile; 
XDAS_Int8  configStatus;

extern IRES_HDVICP2_Obj  IRES_HDVICP2_handle;
extern sTokenMapping     sTokenMap[] ;
extern FILE *fProfileNums; 
extern XDAS_UInt32   ivaCodeLoadDone;
extern XDAS_UInt32   colocBufSize;

static sEnumToStringMapping gContentStrings[4] = 
{
  (XDAS_Int8 *)"IVIDEO_PROGRESSIVE, \0",
  (XDAS_Int8 *)"IVIDEO_INTERLACED, \0",
  (XDAS_Int8 *)"IVIDEO_INTERLACED, \0",
  (XDAS_Int8 *)"IVIDEO_INTERLACED, \0"
};

static sEnumToStringMapping gFrameTypeStrings[3] = 
{
  (XDAS_Int8 *)"IVIDEO_I_FRAME, \0",
  (XDAS_Int8 *)"IVIDEO_P_FRAME, \0",
  (XDAS_Int8 *)"IVIDEO_B_FRAME, \0"
};


sChannelState nChannelState[NUM_DEC_CHANNELS_SUPPORTED];
IH264VDEC_ProcessParamsList processList;
XDAS_Int8 numChannels,allChannelEnded;
/*****************************************************************************/





/*****************************************************************************/


/** 
********************************************************************************
 *  @fn     main
 *  @brief  Sample main program implementation which uses H264 Decoder APIs 
 *          to create decoder instance and decode multiple input files. 
 *          
 *  @param[in] void          : None
 *          
 *  @return XDM_EFAIL/APP_EFAIL/APP_EXIT
********************************************************************************
*/
XDAS_Int32 main(XDAS_Int32 argc, XDAS_Int8 * argv[])
{
  /*--------------------------------------------------------------------------*/
  /* testCompliance: If set to 1 indicates that the output need to be compared*/
  /*                 against the reference provided and pass/fail need to be  */
  /*                 given out. Otherwise (=0), the output is dumped to file. */
  /* actNumRows: Used when output datasync is enabled, tracks the o/p row     */
  /*             information                                                  */
  /*--------------------------------------------------------------------------*/
  XDAS_Int8     testCompliance,crcEnable;
  XDAS_Int32    actNumRows;
  XDAS_Int32    count =0;
  
  /*--------------------------------------------------------------------------*/
  /*  File pointers for input/output/reference info needed.                   */
  /*--------------------------------------------------------------------------*/
  FILE *fConfigFile, *frefFile;

  /*--------------------------------------------------------------------------*/
  /*  Initializing the path of file containing the test vectors to test.      */
  /*--------------------------------------------------------------------------*/
  XDAS_Int8 fname[]  = "..\\..\\..\\Test\\TestVecs\\Config\\Testvecs.cfg";
  XDAS_Int8 fStatusFileName[] = "..\\..\\..\\Test\\TestVecs\\Output\\Log.txt";

  /*--------------------------------------------------------------------------*/
  /*  One Local variables to store the result of a process or control call,   */
  /*  and also for storing of comparison of results                           */
  /*--------------------------------------------------------------------------*/
  XDAS_Int8    ret_val;
  XDAS_Int8    testVal, chkVal;
  XDAS_Int8    i;
  XDAS_UInt8   line[10];
  //IVIDDEC3_Status           *BaseStatus = &status.viddec3Status;
  XDAS_Int32 allChannelMaxWidth = 0, allChannelMaxHeight = 0;


  
  XDAS_Int32 contentType, frameType;
  XDAS_Int8  versionBuf[VERSION_BUF_SIZE];

#ifdef HOST_ARM9
  dummy();
#endif

  /*--------------------------------------------------------------------------*/
  /*  Enable the clock to IVAHD module. This is required only in case of      */
  /*  HW where GEL files are not used for enabling clock for IVAHD            */
  /*--------------------------------------------------------------------------*/
  my_initFileIO(ARG_FILEIO_TYPE);

  /*--------------------------------------------------------------------------*/
  /* Put IVAHD in standby after power on during booting process of given SoC  */
  /*--------------------------------------------------------------------------*/
  IVAHD_Standby_power_on_uboot(IVAHD0_HOST_L2_BASE, IVA0_RESET_CONTROLLER);
#ifdef NETRA_IVAHD
  IVAHD_Standby_power_on_uboot(IVAHD1_HOST_L2_BASE, IVA1_RESET_CONTROLLER);
  IVAHD_Standby_power_on_uboot(IVAHD2_HOST_L2_BASE, IVA2_RESET_CONTROLLER);
#endif /* NETRA */

  /*--------------------------------------------------------------------------*/
  /*  Open Test Config File                                                   */
  /*--------------------------------------------------------------------------*/
  fConfigFile = fopen((const char *)fname, "r");

  /*--------------------------------------------------------------------------*/
  /* Open the Log file.                                                       */
  /*--------------------------------------------------------------------------*/
  fLogFile = fopen((const char *)fStatusFileName, "w");

  /*--------------------------------------------------------------------------*/
  /*  Perform file open error check.                                          */
  /*--------------------------------------------------------------------------*/
  if (!fConfigFile)
  {
    printf("Couldn't open parameter file %s", fname);
    return XDM_EFAIL;
  }

  /*--------------------------------------------------------------------------*/
  /*  countConfigSet counts the number of the current configuration set       */
  /*  provided in the testvecs.cfg file. Reset countConfigSet value to 1.     */
  /*--------------------------------------------------------------------------*/
  countConfigSet  = 1;

  /*--------------------------------------------------------------------------*/
  /* Initialization of global variables that indicate algorithm creation      */
  /* status and ivahd code load status                                        */
  /*--------------------------------------------------------------------------*/
  ivaCodeLoadDone = XDAS_FALSE;

  /*--------------------------------------------------------------------------*/
  /*  Read the Config File until it reaches the end of file                   */
  /*--------------------------------------------------------------------------*/
  while(!feof(fConfigFile))
  {
    /*------------------------------------------------------------------------*/
    /* Initializing the following variables to zero before first process call */
    /* for each test vector.                                                  */
    /*------------------------------------------------------------------------*/
    allChannelEnded = XDAS_FALSE;
    

    /*------------------------------------------------------------------------*/
    /* Initialize the function return values                                  */
    /*------------------------------------------------------------------------*/
    ret_val               = IVIDDEC3_EOK;
    testVal               = APP_EOK;
    configStatus          = IALG_EOK;
    chkVal                = APP_SAME_CONFIG;

    dsBufIdx  = 0;
    bytesConsumedNalFormat = 0;

    printf("\n*******************************************");
    printf("\n Read Configuration Set %d", countConfigSet );
    printf("\n*******************************************");

    /*------------------------------------------------------------------------*/
    /*  Read the number of channels parameter                                 */
    /*------------------------------------------------------------------------*/
    if(fgets((char *)line, 10, fConfigFile))
    {
      sscanf((const char *)line,"%d",&numChannels);
    }
    else
    {
      return APP_EXIT;
    }
    for(i=0;i<numChannels;i++)
    {
      nChannelState[i].fatalErrorDetected    = 0;
      nChannelState[i].nonFatalErrorDetected = 0;
      nChannelState[i].streamEnd             = 0;
      nChannelState[i].frameCount            = 0;
      nChannelState[i].displayCount          = 0;
      nChannelState[i].picture_count         = 0;
      nChannelState[i].CodecExtError         = 0;
      nChannelState[i].CodecExtErrorFlush    = 0;
      nChannelState[i].bsInFilePos           = 0;
      nChannelState[i].bufferFreed           = 0;
      nChannelState[i].bufferDisplayed       = 0;
      nChannelState[i].channelEnded          = 0; 
      nChannelState[i].algCreated            = XDAS_FALSE;
#ifdef TEST_SEEK_OP
      nChannelState[i].seekIdxCntr           = 0;
      nChannelState[i].SeekOpStart           = 0;
      nChannelState[i].SeekBackwd            = 0;
#endif /* TEST_SEEK_OP */
    }

    /*------------------------------------------------------------------------*/
    /* Exit the loop in case of number of channels is equal to zero           */
    /*------------------------------------------------------------------------*/
    if(numChannels==0)
    {
      break;
    }
    for(i=0;i<numChannels;i++)
    {
      /*----------------------------------------------------------------------*/
      /* Parse the test vecs & params config files                            */
      /*----------------------------------------------------------------------*/
      ret_val = TestApp_ioFilePtrInit(fConfigFile, &testCompliance,
        &crcEnable, i);

      /*----------------------------------------------------------------------*/
      /* modify the operating mode and metadata type based on mbInfoWriteMode */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].appCntrlParams.mbInfoWriteMode)
      {
        /*--------------------------------------------------------------------*/
        /* Set the operating mode as transcode                                */
        /*--------------------------------------------------------------------*/
        nChannelState[i].params.viddec3Params.operatingMode = 
                                            IVIDEO_TRANSCODE_FRAMELEVEL;
      
        for(count = 0; count < IVIDEO_MAX_NUM_METADATA_PLANES; count++)
        {
          /*------------------------------------------------------------------*/
          /* set the available metadata for mb info dump                      */
          /*------------------------------------------------------------------*/
          if(nChannelState[i].params.viddec3Params.metadataType[count] == 
                                                IVIDEO_METADATAPLANE_NONE)
          {
            nChannelState[i].params.viddec3Params.metadataType[count] = 
                                                                APP_MB_INFO;
            break;
          }
          else if(nChannelState[i].params.viddec3Params.metadataType[count] == 
                APP_MB_INFO)
          {
            break;
          }
        }
        /*--------------------------------------------------------------------*/
        /* In case no index of metadata is set to MB-info, then there must be */
        /* some repetition of some metadata type.                             */
        /*--------------------------------------------------------------------*/
        if(count == IVIDEO_MAX_NUM_METADATA_PLANES)
        {
          if(nChannelState[i].params.viddec3Params.metadataType[1] == 
                        nChannelState[i].params.viddec3Params.metadataType[2])
          {
            nChannelState[i].params.viddec3Params.metadataType[2] = APP_MB_INFO;
          }
          else
          {
            nChannelState[i].params.viddec3Params.metadataType[0] = APP_MB_INFO;
          }
        }
      }
      else
      {
        nChannelState[i].params.viddec3Params.operatingMode = 0;
      }
    
      /*----------------------------------------------------------------------*/
      /* If the parser/file reader returns faliure, exit the current config   */
      /*----------------------------------------------------------------------*/
      if(ret_val == APP_EFAIL)
      {
        printf("Exiting for this configuration...\n");
        updateConfigStatusFile(IALG_EFAIL);
        numChannels -= 1;
        continue;
      }
      else if(ret_val == APP_EXIT)
      {
        break;
      }

      /*----------------------------------------------------------------------*/
      /* Setting to default in case the user configured to wrong value.       */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].appCntrlParams.ivahdId >= SOC_TOTAL_IVAHDS)
      {
        appIvahdId = 0;
      }
      else
      {
        appIvahdId = nChannelState[i].appCntrlParams.ivahdId;
      }

      /*----------------------------------------------------------------------*/
      /* File pointer to capture profile info, if enabled                     */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].appCntrlParams.profileEnable)
      {
        if(countConfigSet == 1)
        {
          fCycles = fopen("..\\..\\..\\Test\\TestVecs\\Output\\ProfileInfo.txt", 
                        "w");
          fprintf(fCycles,
"\t\thostPreIva\tpreMbLoop\tinMbLoop\tpostMbLoop\thostPostIva\tivaTotalCycles\n");
          fprintf(fCycles,
                 "|====================================================|\n\n");
        }
        fprintf(fCycles, "%s\n\n",nChannelState[i].appCntrlParams.inFile);
      }

      /*----------------------------------------------------------------------*/
      /* By default decoding mode is Full frame i.e, at Auxiliary Unit based  */
      /* If decodeHeader parameter is set to 1, then change the mode to       */
      /* XDM_PARSE_HEADER (header only decoding mode)                         */
      /*----------------------------------------------------------------------*/
      nChannelState[i].decodeMode =  
            nChannelState[i].dynamicParams.viddec3DynamicParams.decodeHeader;
      /*----------------------------------------------------------------------*/
      /* Check whether Algorithm instance has been already created & still    */
      /* exist.                                                               */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].algCreated == XDAS_FALSE)
      {
        /*--------------------------------------------------------------------*/
        /*  Initialization of static parameters is done by this function call */
        /*--------------------------------------------------------------------*/
        TestApp_SetInitParams(&nChannelState[i].params, i);
    
        /*--------------------------------------------------------------------*/
        /*  Setting the sizes based on baseClassOnly control paramater.       */
        /*  if "baseClassOnly" is true then set base class sizes, elase set   */
        /*  the extended class structure sizes                                */
        /*--------------------------------------------------------------------*/
        if(nChannelState[i].appCntrlParams.baseClassOnly)
        {
          nChannelState[i].params.viddec3Params.size  = sizeof(IVIDDEC3_Params);
          nChannelState[i].status.viddec3Status.size  = sizeof(IVIDDEC3_Status);
          nChannelState[i].inArgs.viddec3InArgs.size  = sizeof(IVIDDEC3_InArgs);
          nChannelState[i].outArgs.viddec3OutArgs.size
                                            = sizeof(IVIDDEC3_OutArgs);
          nChannelState[i].dynamicParams.viddec3DynamicParams.size
                                            = sizeof(IVIDDEC3_DynamicParams);
        }
        else
        {
          nChannelState[i].params.viddec3Params.size = sizeof(H264VDEC_Params);
          nChannelState[i].status.viddec3Status.size = sizeof(H264VDEC_Status);
          nChannelState[i].dynamicParams.viddec3DynamicParams.size
                                              = sizeof(H264VDEC_DynamicParams);
          nChannelState[i].inArgs.viddec3InArgs.size              
                                              = sizeof(H264VDEC_InArgs);
          nChannelState[i].outArgs.viddec3OutArgs.size            
                                              = sizeof(H264VDEC_OutArgs);
        }
        /*--------------------------------------------------------------------*/
        /*  Create the Algorithm object (instance)                            */
        /*--------------------------------------------------------------------*/
        printf("\nCH: %d Creating Algorithm Instance \n",i);
    
        /*--------------------------------------------------------------------*/
        /*  Algorithm create call. This function will allocate memory for the */
        /*  algorithm handle and for all the buffers (memtabs) required by the*/
        /*  algorithm and initialize them accordingly. The alg handle is      */
        /*  returned.                                                         */
        /*--------------------------------------------------------------------*/
        nChannelState[i].h264decHandle = 
          H264VDEC_create((H264VDEC_Fxns *) &H264VDEC_TI_IH264VDEC_MULTI, 
                                                      &nChannelState[i].params);
        if(nChannelState[i].params.viddec3Params.maxWidth > allChannelMaxWidth)
        {
          allChannelMaxWidth = nChannelState[i].params.viddec3Params.maxWidth;
        }
        if(nChannelState[i].params.viddec3Params.maxHeight > 
                                                allChannelMaxHeight)
        {
          allChannelMaxHeight = nChannelState[i].params.viddec3Params.maxHeight;
        }
        /*--------------------------------------------------------------------*/
        /*  Check for errors in algorithm handle creation                     */
        /*--------------------------------------------------------------------*/
        if (nChannelState[i].h264decHandle == NULL)
        {
          fprintf(stdout,"Failed to Create Instance. Exiting this config..\n");
          ret_val = IALG_EFAIL;
        }
        else
        {    
          /*------------------------------------------------------------------*/
          /*  Print success message if handle creation is proper.             */
          /*------------------------------------------------------------------*/
          printf("CH: %d Algorithm Instance Creation Done...\n",i);

          /*------------------------------------------------------------------*/
          /* Call to RMAN Assign Resources (allocate ires-rman resources).    */
          /* For H264 Decoder, Only the alg handle is requested through ialg  */
          /* interface, the rest of the buffers [memtab's] are requested      */
          /* through IRES interface. The function call allocates the resources*/
          /* requested trough IRES interface and initializes them.            */
          /*------------------------------------------------------------------*/
          ret_val = RMAN_AssignResources
                    ((IALG_Handle)nChannelState[i].h264decHandle, i);
        }
        /*--------------------------------------------------------------------*/
        /* Set the variable to indicate that algorithm instance has been      */
        /* created.                                                           */
        /*--------------------------------------------------------------------*/
        nChannelState[i].algCreated = XDAS_TRUE;
        /*--------------------------------------------------------------------*/
        /* Do the parameter Boundary check                                    */
        /*--------------------------------------------------------------------*/
        chkVal = paramBoundaryCheck(ret_val, CREATE_TIME_LEVEL, i);
        
        if(chkVal == APP_NEXT_CONFIG)
        {
          continue;
        }
      }
      /*----------------------------------------------------------------------*/
      /* Check the display Buffer Mode setting & do the corresponding init.   */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].params.viddec3Params.displayBufsMode 
                             == IVIDDEC3_DISPLAYBUFS_PTRS)
      {
        nChannelState[i].displayBufs = 
                                      &nChannelState[i].DisplayBuffers[0];
        nChannelState[i].outArgs.viddec3OutArgs.displayBufs.pBufDesc[0] = 
                                      nChannelState[i].displayBufs;
        nChannelState[i].outArgs.viddec3OutArgs.displayBufs.pBufDesc[1] = 
                                      &nChannelState[i].DisplayBuffers[1];
      }
      else
      {
        nChannelState[i].displayBufs = 
        (IVIDEO2_BufDesc *)&nChannelState[i].outArgs.viddec3OutArgs.displayBufs.
                     bufDesc[0];
      }
      /*-------------------------------------------------------------------*/
      /* Populate the version specific elements of status structure.       */
      /*-------------------------------------------------------------------*/
      nChannelState[i].status.viddec3Status.data.buf     = versionBuf;
      nChannelState[i].status.viddec3Status.data.bufSize = VERSION_BUF_SIZE;

      /*---------------------------------------------------------------------*/
      /* Make XDM_GETVERSION control call to figure out the library version  */
      /*---------------------------------------------------------------------*/
      ret_val = H264VDEC_control
             (
               nChannelState[i].h264decHandle,
               XDM_GETVERSION,
               (H264VDEC_DynamicParams *)&nChannelState[i].dynamicParams.viddec3DynamicParams,
               (H264VDEC_Status *)&nChannelState[i].status
             );
      /*----------------------------------------------------------------------*/
      /* Check if XDM_GETVERSION failed, if not print the version of library  */
      /*----------------------------------------------------------------------*/
      if(ret_val != XDM_EFAIL)
      {
        char *version = NULL;
        /*-------------------------------------------------------------------*/
        /* Print the version of the library                                  */
        /*-------------------------------------------------------------------*/
        version = (char *)&nChannelState[i].status.viddec3Status.data.buf[0];
        printf("Version of H264 library : %s \n",version);
      }
      else
      {
        break;
      }

      /*----------------------------------------------------------------------*/
      /*  The outBufsInUseFlag tells us whether the previous input buffer     */
      /*  given by the application to the algorithm is still in use or not.   */
      /*  Since this is before the first decode call, assign this flag to 0.  */
      /*  The algorithm will take care to initialize this flag appropriately  */
      /*  from hereon for the current configuration.                          */
      /*----------------------------------------------------------------------*/
      nChannelState[i].outArgs.viddec3OutArgs.outBufsInUseFlag     = 0;
      /*----------------------------------------------------------------------*/
      /*  Resetting bytesConsumed variable to 0. This variable will contain   */
      /*  the total number of bytes consumed by the algorithm till now for the*/
      /*  current configuration.                                              */
      /*----------------------------------------------------------------------*/
      nChannelState[i].validBytes                           = 0;
      nChannelState[i].bytesConsumed                        = 0;
      /*----------------------------------------------------------------------*/
      /*  The GETBUFINFO call gives information for number of input and       */
      /*  output buffers. For the first call however, since the buffmgr_init()*/
      /*  has already initialized the luma and chroma buffer handles, the     */
      /*  GETBUFINFO call will not return any sizes for outbufs.              */
      /*----------------------------------------------------------------------*/
      H264VDEC_control
      (
        nChannelState[i].h264decHandle,
        XDM_GETBUFINFO,
        (H264VDEC_DynamicParams *)&nChannelState[i].dynamicParams.viddec3DynamicParams,
        (H264VDEC_Status *)&nChannelState[i].status
      );
      /*----------------------------------------------------------------------*/
      /*  Initialize the TILER params & Get the buffers in TILER space        */
      /*----------------------------------------------------------------------*/
      testAppTilerInit(
            nChannelState[i].status.viddec3Status.bufInfo.minOutBufSize,i);
      /*----------------------------------------------------------------------*/
      /*  The buffermanager init function call allocates the memory for the   */
      /*  number of buffers of the corresponding sizes as passed in arguments */
      /*  to it. This function initializes the output/reference bufs based on */
      /*  the outBuf parameters returned from the GETBUFINFO call above. This */
      /*  call will allocate each of the numOutbufs memory equal to (specified*/
      /*  bufsize * MAX_BUFF_ELEMENTS). MAX_BUFF_ELEMENTS refers to the max   */
      /*  num of ref bufs required by algorithm. The initialization of buff   */
      /*  ptr will take place only for the first ref buffer but allocation    */
      /*  will happen for MAX_BUFF_ELEMENTS so that after the first decode    */
      /*  call, when actual height and width of picture are known, remaining  */
      /*  ref bufs can be initialised in the buffmgr_reinit function.         */
      /*  Note that the allocation of output/ref buffers will happen only once*/
      /*  for the entire bunch of configuration sets provided in the testvecs */
      /*  config file.                                                        */
      /*----------------------------------------------------------------------*/
      ret_val = BUFFMGR_Init( 
            nChannelState[i].status.viddec3Status.bufInfo.minNumOutBufs, 
            nChannelState[i].status.viddec3Status.bufInfo.minOutBufSize,
            nChannelState[i].status.viddec3Status.bufInfo.outBufMemoryType,
            i);
      if (ret_val)
      {
        fprintf (stdout,"\nMemory couldn't get allocated for output buffers\n");
        break;
      }
      /*----------------------------------------------------------------------*/
      /* If decode mode is not the Parse header mode, number of buffers       */
      /* allocated will be 1.                                                 */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].decodeMode == XDM_DECODE_AU)
      {
        nChannelState[i].numBuffersAllocated = 1;
      }
      /*----------------------------------------------------------------------*/
      /*  Increment the countConfigSet value for next iteration.              */
      /*----------------------------------------------------------------------*/
      countConfigSet++;
      /*----------------------------------------------------------------------*/
      /*  Initialize the input buffer properties as required by algorithm     */
      /*  based on info received by preceding GETBUFINFO call. First init the */
      /*  number of input bufs.                                               */
      /*----------------------------------------------------------------------*/
      nChannelState[i].inputBufDesc.numBufs     = 
                     nChannelState[i].status.viddec3Status.bufInfo.minNumInBufs;
      /*----------------------------------------------------------------------*/
      /*  For the num of input bufs, initialize the buffer pointer addresses  */
      /*  and buffer sizes.                                                   */
      /*----------------------------------------------------------------------*/
      nChannelState[i].bitStreamData = 
                (XDAS_Int8 *)&inputData[i*(INPUT_BUFFER_SIZE/numChannels)];
      nChannelState[i].inputBufDesc.descs[0].buf = 
                                        nChannelState[i].bitStreamData;
      nChannelState[i].inputBufDesc.descs[0].bufSize.bytes = 
                                        (INPUT_BUFFER_SIZE/numChannels);
      nChannelState[i].inputBufDesc.descs[0].memType = 
            nChannelState[i].status.viddec3Status.bufInfo.inBufMemoryType[0];

      /*----------------------------------------------------------------------*/
      /*  Initialize the output buffer properties as required by algorithm    */
      /*  based on info received by preceding GETBUFINFO call.                */
      /*----------------------------------------------------------------------*/
      nChannelState[i].outputBufDesc.numBufs = 
                   nChannelState[i].status.viddec3Status.bufInfo.minNumOutBufs;
      /*----------------------------------------------------------------------*/
      /*  Initialize the first time flag to 1 which will get used for the     */
      /*  condition check for reinitializing the buffers after the first      */
      /*  decode call.                                                        */
      /*----------------------------------------------------------------------*/
      nChannelState[i].first_time = 1;
      /*----------------------------------------------------------------------*/
      /*  Read the input bit stream from the file                             */
      /*----------------------------------------------------------------------*/
      nChannelState[i].validBytes = 
        TestApp_ReadByteStream(nChannelState[i].appFilePtrs.fpInFile, 
          nChannelState[i].appFilePtrs.fpSizeFile, nChannelState[i].bsInFilePos,
          i);

      printf("CH: %d Valid bytes read = %d\n",i, nChannelState[i].validBytes);
      /*----------------------------------------------------------------------*/
      /*  Do-While Loop for Decode Calls                                      */
      /*  The loop will break out if:                                         */
      /*  - frameCount >= appControlPrms.framesToDecode                       */
      /*  - Errors encountered in the deocode call that indicates a need for  */
      /*    termination of decoding for the current stream being decoded      */
      /*  - Buffer allocation for recon buffers failed                        */
      /*----------------------------------------------------------------------*/
    }/*for(i=0;i<numChannels;i++)*/

    /*----------------------------------------------------------------------*/
    /* Allocate  memory for a Temporary buffer used for interleaving the    */
    /* two fields to form the output frame (for interlaced cases).          */
    /* (memory allocated for worst case i.e. two fields).                   */
    /*----------------------------------------------------------------------*/
    fieldBuf = (XDAS_Int32)my_Memalign(128, (((allChannelMaxWidth + 
               (2 * PADX)) * (allChannelMaxHeight + 
               (4 * PADY)) * 3) >> 1));
    for(i=0;i<numChannels;i++)
    {
      nChannelState[i].fieldBuf = fieldBuf;
    }

    do
    {
      XDAS_Int8 chCount = 0;
      /*----------------------------------------------------------------------*/
      /* skipChannel is used to make sure for bitStream mode = FrameSizeMode  */
      /* the multiprocess call is not made for that channel when valid bytes=0*/
      /*----------------------------------------------------------------------*/
      XDAS_Int8 skipChannel = 0;
      rowNum = 0;
      DataSyncIntrCntr = 0;
      putBufferCount = 0;
      /*----------------------------------------------------------------------*/
      /* N-Channel loop for pre-process call operations                       */
      /*----------------------------------------------------------------------*/
      for(i=0;i<numChannels;i++)
      {
        skipChannel = 0;
        nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed = 0;
        /*--------------------------------------------------------------------*/
        /*  Read Input bit stram.                                             */
        /*  For frame mode of decoding(provide 1 frame worth of input data),  */
        /*  the fsizeFile will have the info on frame sizes, so at a time we  */
        /*  read the bytes sufficient for one frame decoding.                 */
        /*--------------------------------------------------------------------*/
        if((nChannelState[i].picture_count) && 
            (nChannelState[i].appCntrlParams.bitStreamMode == BS_FRAME_MODE))
        {
          nChannelState[i].validBytes = 
              TestApp_ReadByteStream(nChannelState[i].appFilePtrs.fpInFile, 
              nChannelState[i].appFilePtrs.fpSizeFile, 
              nChannelState[i].bsInFilePos, i);
        }
        else if(nChannelState[i].bytesConsumed > (
        (INPUT_BUFFER_SIZE/numChannels) - (INFLIE_READ_THRESHOLD/numChannels)))
        {
          /*------------------------------------------------------------------*/
          /* Fill the buffer with more input data if bytesRemaining in the    */
          /* input buffer fall below a certain threshold                      */
          /*------------------------------------------------------------------*/
          if((nChannelState[i].params.viddec3Params.inputDataMode == 
             IVIDEO_SLICEMODE)||(nChannelState[i].params.viddec3Params.
             inputDataMode == IH264VDEC_NALUNIT_MODE))
          {
            nChannelState[i].bsInFilePos    +=  bytesConsumedNalFormat;
          }
          else
          {
            nChannelState[i].bsInFilePos    +=  nChannelState[i].bytesConsumed;
          }
          nChannelState[i].bytesConsumed   = 0;
          bytesConsumedNalFormat = 0;
          
          printf("Reading another INPUT_BUFFER_SIZE bytes....\n");

          nChannelState[i].validBytes = 
              TestApp_ReadByteStream(nChannelState[i].appFilePtrs.fpInFile, 
              nChannelState[i].appFilePtrs.fpSizeFile, 
              nChannelState[i].bsInFilePos, i);
        }

        /*--------------------------------------------------------------------*/
        /*  Do the process call only if validBytes is greater than zero.      */
        /*--------------------------------------------------------------------*/
        if (nChannelState[i].validBytes > 0) 
        {
          /*------------------------------------------------------------------*/
          /*  Check for the value of the outBufsInUseFlag. If the previous    */
          /*  decode call was for the first field of an interlaced frame, the */
          /*  previous outbuf supplied by algorithm may still be required for */
          /*  decoding second field. In that case, the algorithm will not need*/
          /* a new buffer from the application. If above is not the case, call*/
          /*  the getfreebuffer() function of buffermanager to get the buffer */
          /*  element to be supplied to algorithm for the next decode call.   */
          /*  Also if the codec is in parseHeader mode, then there is no need */
          /*  to supply o/p buf                                               */
          /*------------------------------------------------------------------*/
          if((nChannelState[i].decodeMode == XDM_DECODE_AU) && 
             (!nChannelState[i].outArgs.viddec3OutArgs.outBufsInUseFlag))
          { 
            nChannelState[i].buffEle = BUFFMGR_GetFreeBuffer(i);

            if (nChannelState[i].buffEle == NULL)
            {
              fprintf (stdout,"\nNo free buffer available\n");
              nChannelState[i].validBytes   = 0;
              nChannelState[i].channelEnded = 1;             
            }
            /*----------------------------------------------------------------*/
            /*  Initialize the input ID in input arguments to the bufferid of */
            /*  buffer element returned from getfreebuffer() function.        */
            /*----------------------------------------------------------------*/
            nChannelState[i].inArgs.viddec3InArgs.inputID = 
                                        nChannelState[i].buffEle->bufId;
          }

          /*------------------------------------------------------------------*/
          /* Update the Input & Output buffer descriptors.                    */
          /*------------------------------------------------------------------*/
          TestApp_updateIObufDesc(&nChannelState[i].inputBufDesc, 
               &nChannelState[i].outputBufDesc, 
               &nChannelState[i].status.viddec3Status, 
               nChannelState[i].bytesConsumed, nChannelState[i].validBytes, 
               i,nChannelState[i].outArgs.viddec3OutArgs.outBufsInUseFlag);

          /*------------------------------------------------------------------*/
          /* Assign the number of bytes available                             */
          /* If application is configured the codec to run in parse-header and*/
          /* frame size bit-stream input mode, the update of inArgs numbytes  */
          /* and inputBufDesc buffer address should be done as if application */
          /* is providing bit-stream in buffer mode (not frame size mode).    */
          /* This care has to be taken care only after the first process call.*/
          /*------------------------------------------------------------------*/
          if((nChannelState[i].picture_count==0) && 
            (nChannelState[i].appCntrlParams.bitStreamMode == BS_FRAME_MODE))
          {
            if(nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed)
            {
              nChannelState[i].inArgs.viddec3InArgs.numBytes -=
                   nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed;
              nChannelState[i].inputBufDesc.descs[0].buf   += 
                   nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed;
            }
            else
            {
              nChannelState[i].inArgs.viddec3InArgs.numBytes = 
                                                nChannelState[i].validBytes;
            }
          }
          else
          {
            nChannelState[i].inArgs.viddec3InArgs.numBytes = 
                                                nChannelState[i].validBytes;
          }
          /*------------------------------------------------------------------*/
          /*  The following function is used to initialize the dynamic params */
          /*  of the IVIDDEC1 handle.                                         */
          /*------------------------------------------------------------------*/
          TestApp_SetDynamicParams(
                &nChannelState[i].dynamicParams.viddec3DynamicParams, i);

          /*------------------------------------------------------------------*/
          /*  The SETPARAMS control call is used to set the codec's dynamic   */
          /*  parameters. Base or extended class is indicated by size field.  */
          /*------------------------------------------------------------------*/
          ret_val = H264VDEC_control
                 (
                   nChannelState[i].h264decHandle,
                   XDM_SETPARAMS,
                  (H264VDEC_DynamicParams *)&nChannelState[i].dynamicParams.viddec3DynamicParams,
                  (H264VDEC_Status *)&nChannelState[i].status
                 );
      
          if(ret_val == IVIDDEC3_EUNSUPPORTED)
          {
            ret_val = IVIDDEC3_EFAIL;
          }
          /*------------------------------------------------------------------*/
          /* Do the parameter Boundary check                                  */
          /*------------------------------------------------------------------*/
          chkVal = paramBoundaryCheck(ret_val, CONTROL_CALL_LEVEL,i);
          if(chkVal == APP_NEXT_CONFIG)
          {
            /*----------------------------------------------------------------*/
            /* In Parameter Boundary check validation, some buffers might get */
            /* allocated by this time. Freeing them up before proceeding to   */
            /* next test vector. Basically avoidng the memory leak during     */
            /* validation                                                     */
            /*----------------------------------------------------------------*/
            BUFFMGR_DeInit(1, 1, i);
            break;
          }
        }
        else
        {
          skipChannel  = 1;
          /*----------------------------------------------------------------*/
          /*  Return if there is an error in reading the file               */
          /*----------------------------------------------------------------*/
          if (nChannelState[i].validBytes < 0) 
          {
            nChannelState[i].validBytes   = 0;
            nChannelState[i].channelEnded = 1;
            fprintf(stdout,
                    "Valid Bytes incorrect,Exiting this configuration\n");
          }
        }
      
#ifdef MEM_CORRUPTION_TEST
        /*------------------------------------------------------------------*/
        /* Do scratch corruption of SL2, ITCM, DTCM and IP memories         */
        /*------------------------------------------------------------------*/
        H264DEC_ScratchMemoryCorruption();
#endif
        /*------------------------------------------------------------------*/
        /* Set the Flag to distinguish the first datasync call in a frame   */
        /* with the subsequenct calls. This is a special case since the     */
        /* input can have any size for the first input datasync call.       */
        /* This flag is applicable only if input datasync is enabled        */
        /*------------------------------------------------------------------*/
        firstDataSyncCallInFrame = 1;

        /*------------------------------------------------------------------*/
        /* Check whether the channel has been ended or not                  */
        /*------------------------------------------------------------------*/
        if(nChannelState[i].channelEnded || skipChannel)
        {
          continue;
        }
        /*--------------------------------------------------------------------*/
        /* Prepare the N channel Container                                    */
        /*--------------------------------------------------------------------*/
        processList.processParams[chCount].handle =
                                        nChannelState[i].h264decHandle;
        processList.processParams[chCount].inBufs =
                                        &nChannelState[i].inputBufDesc;
        processList.processParams[chCount].outBufs =
                                        &nChannelState[i].outputBufDesc;
        processList.processParams[chCount].inArgs = (IVIDDEC3_InArgs *) 
                                              &nChannelState[i].inArgs;
        processList.processParams[chCount].outArgs = (IVIDDEC3_OutArgs *) 
                                              &nChannelState[i].outArgs;
        

        chCount++;
      }/*for(i=0;i<numChannels;i++)*/
      processList.numEntries = chCount;
      if (processList.numEntries !=0)
      {
        /*------------------------------------------------------------------*/
        /*  Configuring ICECRUSHER registers for profiling purpose          */
        /*------------------------------------------------------------------*/
        ConfigureProfile(0);
        /*------------------------------------------------------------------*/
        /* Capture the time just before the process call (for profiling).   */
        /*------------------------------------------------------------------*/
        TestApp_captureTime(PROCESS_START);
        /*--------------------------------------------------------------------*/
        /*  Multi-Channel Process Call                                        */
        /*--------------------------------------------------------------------*/
        ret_val |= H264VDEC_decodeFrame(&processList);
        
        /*--------------------------------------------------------------------*/
        /*  Capture time immediately after the process call(for profiling).   */
        /*--------------------------------------------------------------------*/
        TestApp_captureTime(PROCESS_END);
        printProfileNums(0);
      
        /*--------------------------------------------------------------------*/
        /*  Check for failure message in the return value.                    */
        /*--------------------------------------------------------------------*/
        if(ret_val != IVIDDEC3_EOK)
        {
          fprintf (stdout,"\nProcess Function returned Error\n");
        }
      }
      /*--------------------------------------------------------------------*/
      /* N-Channel loop for post - process call operations                  */
      /*--------------------------------------------------------------------*/
      for(i=0;i<numChannels;i++)
      {
        /*------------------------------------------------------------------*/
        /* Check whether the channel has been ended or not                  */
        /*------------------------------------------------------------------*/
        if(nChannelState[i].channelEnded)
        {
          continue;
        } 
        if(nChannelState[i].validBytes)
        {
#ifdef SEI_VUI_DUMP
          /*------------------------------------------------------------------*/
          /* In order to validate the SEI and VUI data, need to call the below*/
          /* function. This will dump the sei and vui data in parsed mode,    */
          /* element by element                                               */
          /*------------------------------------------------------------------*/
          testAppHandleMetadata(nChannelState[i].appCntrlParams, 
                                    nChannelState[i].outputBufDesc, 0, i);
#endif
          /*------------------------------------------------------------------*/
          /* Update the bytesConsumed by adding the bytes consumed by the     */
          /* algorithm in the last decode call. Similarly, reduce the valid   */
          /* bytes remaining in the application input buffer by subtracting   */
          /* the bytes consumed in the last decode call.                      */
          /*------------------------------------------------------------------*/
          nChannelState[i].bytesConsumed += 
                    nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed;

          /*------------------------------------------------------------------*/
          /* In case of frame Size mode , don't reduce the valid bytes by     */
          /* consumed in last process call. Because the validBytes doesn't    */
          /* get used to update the input buffer pointer as we always load    */
          /* one frame size data at the same address for all frames.          */
          /*------------------------------------------------------------------*/
          if(nChannelState[i].appCntrlParams.bitStreamMode != BS_FRAME_MODE)
          {
            nChannelState[i].validBytes -= 
                    nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed;
          }

          contentType = 
            nChannelState[i].outArgs.viddec3OutArgs.decodedBufs.contentType;
          frameType = 
                nChannelState[i].outArgs.viddec3OutArgs.decodedBufs.frameType;
          /*------------------------------------------------------------------*/
          /* one frame is decoded successfully                                */
          /*------------------------------------------------------------------*/
          printf("CH:%d #%6d, %6d \t%s \t%s",i, nChannelState[i].frameCount, 
                nChannelState[i].picture_count, gFrameTypeStrings[frameType],
                gContentStrings[contentType]);
          printf("Decoded bytes=%d\n", 
                nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed);

          /*------------------------------------------------------------------*/
          /*  Increment the local framecount variable when an entire frame or */
          /*  both fields of an interlaced frame have got decoded.            */
          /*  The outBufsInUseFlag indicates(in case of interlaces streams),  */
          /*  if both the fields of a frame are decoded or not.               */
          /*  The increment should happen only if the process call has run in */
          /*  XDM_DECODE_AU mode.                                             */
          /*------------------------------------------------------------------*/
          if(nChannelState[i].decodeMode == XDM_DECODE_AU)
          {
            /*----------------------------------------------------------------*/
            /* one frame is decoded successfully                              */
            /*----------------------------------------------------------------*/
            if (!nChannelState[i].outArgs.viddec3OutArgs.outBufsInUseFlag)
            {
              nChannelState[i].frameCount++;
            }
            nChannelState[i].picture_count++;
          }
          /*------------------------------------------------------------------*/
          /* If the app needs any additional status info from the decoder,    */
          /* the GETSTATUS control call can be invoked to populate the status */
          /* parameters(see IVIDDEC3_Status structure).                       */
          /*------------------------------------------------------------------*/
          H264VDEC_control
          (
          nChannelState[i].h264decHandle,
          XDM_GETSTATUS,
          (H264VDEC_DynamicParams *)&nChannelState[i].dynamicParams,
          (H264VDEC_Status *)&nChannelState[i].status
          );

          if(nChannelState[i].params.lastNFramesToLog > 0)
          {
            /*----------------------------------------------------------------*/
            /* Print information about the codec's debug information based on */
            /* the result of the GETSTATUS query                              */
            /*----------------------------------------------------------------*/
            printf("Debug trace history configured for previous %d frames\n",
                  nChannelState[i].status.lastNFramesToLog);
            printf("Debug trace dump address in External memory: 0x%x\n",
                  nChannelState[i].status.extMemoryDebugTraceAddr);
            printf("Debug trace dump size in External memory: %d bytes\n",
                  nChannelState[i].status.extMemoryDebugTraceSize);
          }
          /*------------------------------------------------------------------*/
          /* Prepare to Flush the display Frames and write into an output file*/
          /* Also,Check for Break off condition of bytes consumed >=  the     */
          /* bytes in input buffer.                                           */
          /*------------------------------------------------------------------*/
          nChannelState[i].CodecExtError =  
             nChannelState[i].outArgs.viddec3OutArgs.decodedBufs.extendedError;
          /*------------------------------------------------------------------*/
          /* Figure out the status of current test vector.                    */
          /*------------------------------------------------------------------*/
          if(ret_val != IVIDDEC3_EOK)
          {
            XDAS_UInt32 maskEOS;
            /*----------------------------------------------------------------*/
            /* Mask the Stream end erro bit,then check to see if any other    */
            /* error got set.If any other error set means the current testVec */
            /* failed.                                                        */
            /*----------------------------------------------------------------*/
            maskEOS = (~(1 << IH264VDEC_ERR_STREAM_END));
            if(nChannelState[i].CodecExtError & maskEOS)
            {
              /*--------------------------------------------------------------*/
              /* TODO: Keep fine tuning it to achieve the ideal status for    */
              /* each config.                                                 */
              /*--------------------------------------------------------------*/
              if(nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed > 
                                                        END_OF_SEQ_NAL_SIZE)
              {
                configStatus = IALG_EFAIL;
              }
            }
          }
          /*------------------------------------------------------------------*/
          /* Decoding the error message & mapping to corresponding name.      */
          /*------------------------------------------------------------------*/
          TestApp_errorReport(nChannelState[i].CodecExtError);
          /*------------------------------------------------------------------*/
          /* If output datasync is enabled, then print the o/p row information*/
          /*------------------------------------------------------------------*/
          if(nChannelState[i].params.viddec3Params.outputDataMode == 
                                                        IVIDEO_NUMROWS)
          {
            if (nChannelState[i].first_time)  
            {
              actNumRows = 
                    nChannelState[i].status.viddec3Status.outputHeight >> 4;
              printf("*** Actual Number of Rows: %d ***\n", actNumRows);
            }                 
            printf("Total Number of Rows Given Out: %d\n", rowNum);
            printf("Total Number of OutData Sync Interrupts: %d\n", 
                  DataSyncIntrCntr);
            if(actNumRows - rowNum)
            {
              printf("Problem in Output DataSync\n");
            }
          }
          /*------------------------------------------------------------------*/
          /*  Request frame for display                                       */
          /*  Check for frame ready via display buffer pointers. If outputID  */
          /*  of outargs is non-zero, only then a frame is required to be     */
          /*  displayed Call the display routines after performing the check. */
          /*------------------------------------------------------------------*/
          if((nChannelState[i].decodeMode == XDM_DECODE_AU) &&
           (nChannelState[i].outArgs.viddec3OutArgs.outputID[0] != 0) && 
           (nChannelState[i].displayBufs->numPlanes))
          {
            nChannelState[i].bufferDisplayed =  
                        nChannelState[i].bufferDisplayed + 1;
            if(nChannelState[i].frameCount > 
                        nChannelState[i].appCntrlParams.dumpFrom)
            {
              /*--------------------------------------------------------------*/
              /*  Request frame for display In case of Dual Output mode       */
              /*--------------------------------------------------------------*/
              if(nChannelState[i].params.enableDualOutput)
              {
                TestApp_Write_DualOutputData(
                            nChannelState[i].appFilePtrs.fpDualOutFile, 
                            &nChannelState[i].outArgs, 0,crcEnable, i);
              }
              testVal = TestApp_outputDataXfr(
                                nChannelState[i].appFilePtrs.fpOutFile, 
                                nChannelState[i].appFilePtrs.fpRefFile, 
                                nChannelState[i].outArgs,
                                testCompliance, crcEnable,i);
              if(nChannelState[i].params.enableWatermark)
              {
                /*------------------------------------------------------------*/
                /* Write the WaterMark decrypted key to a file. One frame     */
                /* delay is maintained to dump WaterMark key to the file Since*/
                /* we getthe encrypted key of first frame at the beginning of */
                /* second frame.                                              */
                /*------------------------------------------------------------*/
                if(nChannelState[i].frameCount > 1)
                {
                  my_fwrite((void *)&nChannelState[i].outArgs.decryptedKey, 
                  sizeof(char), 4, nChannelState[i].appFilePtrs.fpWaterMarkFile,
                  ARG_FILEIO_TYPE);
                }
              }
            }
          }
          /*------------------------------------------------------------------*/
          /*  Buffer free up checks: If the freeBufId in OutArgs is non-zero  */
          /*  then this indicated frame to be freed. Release the buffers which*/
          /*  are freed  side   -back to the buffer manager. The freebufID    */
          /*  array of outargs contains the sequence of bufferIds which need  */
          /*  to be freed. This gets populated by the algorithm. The following*/
          /*  function will do  the task of freeing up the buffers.           */
          /*  Note: The decoder can free up one or more buffers. The freeBufId*/
          /*        array need to be checked untill we find a zero buffer id  */
          /*        (zero indiates end of the array). Some process calls may  */
          /*        not have any buffers to be freed, in this case, the first */
          /*        element of freeBufid will be zero.                        */
          /*------------------------------------------------------------------*/
          if(nChannelState[i].decodeMode == XDM_DECODE_AU)
          {
            BUFFMGR_ReleaseBuffer(
            (XDAS_UInt32 *)nChannelState[i].outArgs.viddec3OutArgs.freeBufID,i);
          }
          /*------------------------------------------------------------------*/
          /* In the very first process call, Header parsing is done if decode */
          /* header is set by dynamic params. Second process call onwards,    */
          /* the process call is to decode an entire AU.                      */
          /*------------------------------------------------------------------*/
          nChannelState[i].decodeMode = XDM_DECODE_AU;
          if (!nChannelState[i].outArgs.viddec3OutArgs.outBufsInUseFlag)
          {
            printf("|-------------------------------------------------------|\n");
          }
          /*------------------------------------------------------------------*/
          /*  Prepare to Flush the display Frames and write into an output    */
          /*  file Also,Check for Break off condition of bytes consumed >= the*/
          /*  bytes in input buffer.                                          */
          /*------------------------------------------------------------------*/
          nChannelState[i].CodecExtError =  
             nChannelState[i].outArgs.viddec3OutArgs.decodedBufs.extendedError;
        }
        /*------------------------------------------------------------------*/
        /* Do the flush in followig conditions:-                            */
        /* 1.if no more input bit-stream is available.                      */
        /* 2. number of specified frame is decoded.                         */
        /* 3. Even some errors given out by the process call drive the      */
        /*    application to initiate flush operation.                      */
        /*------------------------------------------------------------------*/
        if((nChannelState[i].streamEnd) || (!nChannelState[i].validBytes) ||
            TestApp_flushCheck(nChannelState[i].CodecExtError)|| 
            (nChannelState[i].frameCount >= 
            nChannelState[i].appCntrlParams.framesToDecode))
        {
          testVal= testAppFlushFrames(&nChannelState[i].inputBufDesc, 
                                    &nChannelState[i].outputBufDesc, 
                                    nChannelState[i].displayBufs,i);
          nChannelState[i].first_time = 0;
        }

        nChannelState[i].CodecExtErrorFlush = 
            nChannelState[i].outArgs.viddec3OutArgs.decodedBufs.extendedError;
        /*------------------------------------------------------------------*/
        /* If this is the first decode call in the stream, then reinitialize*/
        /* all the buffers based on the picture width and height.           */
        /* If the picture resolution changes, then also the reinit of the   */
        /* buffers need to be done based on the new height/width.           */
        /*------------------------------------------------------------------*/
        if ((nChannelState[i].first_time) ||
            (TestApp_checkErr(nChannelState[i].CodecExtError, 
            IH264VDEC_ERR_PICSIZECHANGE)))
        {      
          /*----------------------------------------------------------------*/
          /* If there is a resolution change, the current buffers need to be*/
          /* freed and de-allocated and then new buffers need to be         */
          /* allocated based on the changed resolution.                     */
          /*----------------------------------------------------------------*/
          if(TestApp_checkErr(nChannelState[i].CodecExtError, 
                                    IH264VDEC_ERR_PICSIZECHANGE))
          {
            /*--------------------------------------------------------------*/
            /* Mark all the buffers as free                                 */
            /*--------------------------------------------------------------*/
            BUFFMGR_ReleaseAllBuffers(i);          
            /*--------------------------------------------------------------*/
            /*  Free the buffers allocated for output/reference             */
            /*  For picture size change, the buffers need to be reallocated */
            /*--------------------------------------------------------------*/
            BUFFMGR_DeInit(nChannelState[i].numBuffersAllocated, 
                                nChannelState[i].outputBufDesc.numBufs,i);        
          }
          /*----------------------------------------------------------------*/
          /* The GETBUFINFO call will give information for number of output */
          /* buffers. This call is after the first decode call hence the    */
          /* output buffer sizes returned by this call is calculated based  */
          /* on actual pic width and height. Hence, there is need for buffer*/
          /* re-initializations which happens immediately after this call.  */
          /*----------------------------------------------------------------*/
          H264VDEC_control
          (
              nChannelState[i].h264decHandle,
              XDM_GETBUFINFO,
              (H264VDEC_DynamicParams *)&nChannelState[i].dynamicParams.viddec3DynamicParams,
              (H264VDEC_Status *)&nChannelState[i].status
          );
          /*----------------------------------------------------------------*/
          /*  Initialize the TILER params & Get the buffers in TILER space  */
          /*----------------------------------------------------------------*/
          /* testAppTilerInit(BaseStatus->bufInfo.minOutBufSize); */ 

          /*----------------------------------------------------------------*/
          /* Capture Colocated Info ires Buffer Usage details               */
          /*----------------------------------------------------------------*/
          {
            XDAS_UInt32 numColocFrames, totalMbs, colocUseSize;
            XDAS_UInt32 numDispFrames;
            XDAS_Int16  width, height;
            XDAS_Int16  xOffset, yOffset;
            IVIDEO2_BufDesc *decodedBufs;
            
            decodedBufs = (IVIDEO2_BufDesc *)
                        &nChannelState[i].outArgs.viddec3OutArgs.decodedBufs;
            
            if(nChannelState[i].params.viddec3Params.displayDelay == 
                                            IVIDDEC3_DISPLAYDELAY_DEFAULT)
            {
              numDispFrames = nChannelState[i].status.spsMaxRefFrames;
            }
            else
            {
              numDispFrames = 
                        nChannelState[i].params.viddec3Params.displayDelay;
            }
            
            xOffset = decodedBufs->imageRegion.topLeft.x;
            yOffset = decodedBufs->imageRegion.topLeft.y;
            
            height  = decodedBufs->imageRegion.bottomRight.y - yOffset;
            width   = decodedBufs->imageRegion.bottomRight.x - xOffset;
            
            /*--------------------------------------------------------------*/
            /* Double the height in Interlaced case                         */
            /*--------------------------------------------------------------*/
            if(decodedBufs->contentType == IVIDEO_INTERLACED)
            {
              height       <<= 1; 
            }
            totalMbs = (width * height) / 256;
            
            numColocFrames = 
                    (nChannelState[i].status.viddec3Status.maxNumDisplayBufs
                    - numDispFrames);
            /*--------------------------------------------------------------*/
            /* Check if the colocate usage buffer size is greater than      */
            /* allocated                                                    */
            /*--------------------------------------------------------------*/
            colocUseSize = (numColocFrames * totalMbs * 
                                                sizeof(IH264VDEC_TI_MbInfo));
            if(colocBufSize < colocUseSize)
            {
              printf("\nWarning: Buffer corruption may happen.\n");
            }
          }

          /*----------------------------------------------------------------*/
          /* Reinitialize the buffers using the actual buffer sizes for luma*/
          /* and chroma. This call will initialize the buf ptrs for all     */
          /* ADD_DISPLAY_BUFS (In some cases, deocder may need double of the*/
          /* status.maxNumDisplayBufs) unlike the first which               */
          /*  had initialized only buffer pointers for first ref buffers.   */
          /*----------------------------------------------------------------*/
          nChannelState[i].numBuffersAllocated = 
                (nChannelState[i].status.viddec3Status.maxNumDisplayBufs + 
                ADD_DISPLAY_BUFS);
          
          ret_val = BUFFMGR_ReInit
          (
              nChannelState[i].numBuffersAllocated,
              nChannelState[i].status.viddec3Status.bufInfo.minNumOutBufs,
              nChannelState[i].status.viddec3Status.bufInfo.minOutBufSize,
              nChannelState[i].status.viddec3Status.bufInfo.outBufMemoryType,
              nChannelState[i].first_time,
              i
          );
          if (ret_val)
          {
            fprintf(stdout,
                    "\nMemory couldn't get allocated for O/P buffers\n");
            break;
          }
          /*----------------------------------------------------------------*/
          /*  Reset the flag first_time to 0 since the buffers are correctly*/
          /*  reinitialized.                                                */
          /*----------------------------------------------------------------*/
          nChannelState[i].first_time = 0;
        }
        /*------------------------------------------------------------------*/
        /*  Check for Break off condition of in case of test compliance mode*/
        /*------------------------------------------------------------------*/
        if(testVal == APP_EFAIL)
        {
          break;
        }
        /*------------------------------------------------------------------*/
        /*  Check for Break off condition of Error is due to Picture size   */
        /*  Change OR Buffer Under flow.                                    */
        /*  Check for Break off condition of End of Stream                  */
        /*------------------------------------------------------------------*/
        if(TestApp_checkErr(nChannelState[i].CodecExtError, 
            XDM_INSUFFICIENTDATA) || (TestApp_checkErr(
            nChannelState[i].CodecExtErrorFlush, IH264VDEC_ERR_STREAM_END)&&
            (!TestApp_checkErr(nChannelState[i].CodecExtError, 
            IH264VDEC_ERR_PICSIZECHANGE))) )
        {
          /*----------------------------------------------------------------*/
          /*  The algorithm currently does not guarantee to set freebufid of*/
          /*  all buffers in use when the framecount exceeds framestoDecode.*/
          /*  This is managed for now by an application function. Note that */
          /*  doing this has significance only when running multiple streams*/
          /*----------------------------------------------------------------*/
          BUFFMGR_ReleaseAllBuffers(i);
          nChannelState[i].channelEnded = 1;
          nChannelState[i].validBytes = 0;
        }
        /*------------------------------------------------------------------*/
        /*  Update InArgs structure and the numBytes left to be decoded.    */
        /*------------------------------------------------------------------*/
        if ((nChannelState[i].appCntrlParams.bitStreamMode != BS_FRAME_MODE)
              && (nChannelState[i].params.viddec3Params.inputDataMode == 
              IVIDEO_FIXEDLENGTH) && (nChannelState[i].CodecExtError != 
              IH264VDEC_ERR_PICSIZECHANGE)) 
        {
          /*----------------------------------------------------------------*/
          /* update BitsBuffer                                              */
          /*----------------------------------------------------------------*/
          nChannelState[i].inArgs.viddec3InArgs.inputID++;
          nChannelState[i].inArgs.viddec3InArgs.numBytes -= 
                    nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed;
          nChannelState[i].inputBufDesc.descs[0].buf += 
                    nChannelState[i].outArgs.viddec3OutArgs.bytesConsumed;
        }  

#ifdef TEST_SEEK_OP
        if (i == 0)
        {
          /*------------------------------------------------------------------*/
          /*The following code is to check the support for seek operation.    */
          /*Before performing the seek (forward, rewind) operation, the       */
          /*application should do a XDM flush by calling the control function */
          /*H264VDEC_control with XDM_FLUSH. This will flush out the frames   */
          /*currently locked by the decoder (display and then freed).         */
          /*Then the decoder has to latch on to the next frame(forward/rewind)*/
          /*------------------------------------------------------------------*/
          if(nChannelState[i].frameCount == 
                    frameNumsToStop[nChannelState[i].seekIdxCntr])
          {
            /*----------------------------------------------------------------*/
            /* flush Display queue                                            */
            /*----------------------------------------------------------------*/
            XDAS_UInt32 seekVal;

            /*----------------------------------------------------------------*/
            /* First flush the frames present in DPB, then seek to the        */
            /* requested or interested frame.                                 */
            /*----------------------------------------------------------------*/
            testAppFlushFrames(&nChannelState[i].inputBufDesc, 
             &nChannelState[i].outputBufDesc, nChannelState[i].displayBufs, i);

            printf("\nSeek Operation Started......\n");
            nChannelState[i].SeekOpStart = 1;
            nChannelState[i].SeekBackwd  = 0;

            /*----------------------------------------------------------------*/
            /* Check if application want to do the seek opeation in backward  */
            /* direction.                                                     */
            /*----------------------------------------------------------------*/
            if(nChannelState[i].frameCount > 
                    frameNumsToSeek[nChannelState[i].seekIdxCntr])
            {
              nChannelState[i].SeekBackwd = 1;
              nChannelState[i].frameCount = 
                        frameNumsToSeek[nChannelState[i].seekIdxCntr];
              printf("\n*** Seek In Backward Direction ***\n");
            }

            /*----------------------------------------------------------------*/
            /* Seek the input file pointer to the right location in Bitstream */
            /* file for the seeking frame number.                             */
            /*----------------------------------------------------------------*/
            do
            { 
              seekVal = TestApp_ReadByteStream(
                                nChannelState[i].appFilePtrs.fpInFile, 
                                nChannelState[i].appFilePtrs.fpSizeFile, 
                                nChannelState[i].bsInFilePos,i);
              nChannelState[i].frameCount++;
              nChannelState[i].frameCount = 
                    nChannelState[i].frameCount - nChannelState[i].SeekBackwd;
              printf("\t Bytes Read: %d......\n", seekVal);

            }while(nChannelState[i].frameCount != 
                    frameNumsToSeek[nChannelState[i].seekIdxCntr]);

            printf("Seek is done to Frame: %d\n", nChannelState[i].frameCount);
            nChannelState[i].seekIdxCntr++;
            nChannelState[i].SeekOpStart = 0;
            nChannelState[i].SeekBackwd  = 0;
          }
          /*-----------------------------------------------------------------*/
          /* Check if we have decoded the specified number of frames: Break  */
          /* off the while loop if Specified number of Frames are Decoded    */
          /*-----------------------------------------------------------------*/
          if (nChannelState[i].frameCount >= 
                        nChannelState[i].appCntrlParams.framesToDecode)
          {
            printf("CH:%d Specified number of Frames Decoded...\n  ",i);
            nChannelState[i].channelEnded = 1;
          }
        }
#endif /* TEST_SEEK_OP */
      }/*for(i=0;i<numChannels;i++)*/
      /*----------------------------------------------------------------------*/
      /* Check whether all the channels has been ended if so then break from  */
      /* the main decode loop                                                 */
      /*----------------------------------------------------------------------*/
      {
        XDAS_Int8 channelEndCheckFlg = 1;

        for(i=0;i<numChannels;i++)
        {
          channelEndCheckFlg &= nChannelState[i].channelEnded;  
        }
        
        allChannelEnded = channelEndCheckFlg;
        
        if (allChannelEnded)
        {
          printf("\nAll the channels Decoded...\n",i);
          break; 
        }
      }
    } while (1);
    
    streamEnded = XDAS_TRUE;

    /*----------------------------------------------------------------------*/
    /* If the test status indicates decoding of next configuration, then    */
    /* skip current stream decoding and go to next config to be tested.     */
    /*----------------------------------------------------------------------*/
    if(chkVal == APP_NEXT_CONFIG)
    {
      continue;
    }
    /*----------------------------------------------------------------------*/
    /* Print each config status in a Log file to check the failures if any. */
    /*----------------------------------------------------------------------*/
    updateConfigStatusFile(configStatus);

    /*------------------------------------------------------------------------*/
    /* Close the Input/output/reference files.                                */
    /*------------------------------------------------------------------------*/
    if(testCompliance)
    {
      if(frefFile)
      {
        fclose(frefFile);
      }
    }
    
    for(i=0;i<numChannels;i++)
    {
      if( (nChannelState[i].appCntrlParams.bitStreamMode == BS_FRAME_MODE) ||
        (nChannelState[i].params.viddec3Params.inputDataMode == 
        IVIDEO_SLICEMODE)||(nChannelState[i].params.viddec3Params.inputDataMode
        == IH264VDEC_NALUNIT_MODE))
      {
        fclose(nChannelState[i].appFilePtrs.fpSizeFile);
      }

      my_fclose(nChannelState[i].appFilePtrs.fpOutFile, ARG_FILEIO_TYPE);
      if(nChannelState[i].params.enableDualOutput)
      {
        my_fclose(nChannelState[i].appFilePtrs.fpDualOutFile, ARG_FILEIO_TYPE);
      }
      if(nChannelState[i].params.enableWatermark)
      {
        my_fclose(nChannelState[i].appFilePtrs.fpWaterMarkFile,ARG_FILEIO_TYPE);
      }
#ifdef SEI_VUI_DUMP
      /*--------------------------------------------------------------------*/
      /* In order to validate the SEI and VUI data, need to call the below  */
      /* function. This will dump the sei and vui data in parsed mode,      */
      /* element by element                                                 */
      /*--------------------------------------------------------------------*/
      testAppHandleMetadata(nChannelState[i].appCntrlParams, 
                                nChannelState[i].outputBufDesc, 1, i);
#endif

      /*----------------------------------------------------------------------*/
      /*  Free the buffers allocated for output/reference for all the streams */
      /*  that have been executed.                                            */
      /*----------------------------------------------------------------------*/
      BUFFMGR_DeInit(nChannelState[i].numBuffersAllocated, 
                                nChannelState[i].outputBufDesc.numBufs,i);

      printf("CH:%d Valid bytes remaining in the stream: %d\n", i, 
                                nChannelState[i].validBytes);
      /*---------------------------------------------------------------------*/
      /* make the next process call only if at least 4 bytes (needed for     */
      /* start code detection) are available.                                */
      /*---------------------------------------------------------------------*/
      if(nChannelState[i].validBytes > 4)
      {
        printf("Exiting due to error...\n");
      }
      printf("CH:%d Decoding completed \n",i);

      printf("CH:%d Frames Displayed - %d Frames Freed - %d\n",i,
           nChannelState[i].bufferDisplayed, nChannelState[i].bufferFreed);

      /*---------------------------------------------------------------------*/
      /* If xdmReset flag is set, make the XDM_RESET control call instead of */
      /* deleting the current alg instance & re-creating.                    */
      /*---------------------------------------------------------------------*/
      if(nChannelState[i].appCntrlParams.xdmReset)
      {
        /*--------------------------------------------------------------------*/
        /* Do an XDM_RESET call before decoding every bit stream, do not      */
        /* create the instance for each stream.                               */
        /*--------------------------------------------------------------------*/
        H264VDEC_control
        (
         nChannelState[i].h264decHandle,
         XDM_RESET,
         (H264VDEC_DynamicParams *)&nChannelState[i].dynamicParams.viddec3DynamicParams,
         (H264VDEC_Status *)&nChannelState[i].status
        );

        nChannelState[i].algCreated = XDAS_TRUE;
      }
      else
      {
        /*--------------------------------------------------------------------*/
        /* Else of XDM_RESET: Delete the algo instance and free the resources */
        /*--------------------------------------------------------------------*/
        RMAN_FreeResources((IALG_Handle)nChannelState[i].h264decHandle, i);
        H264VDEC_delete(nChannelState[i].h264decHandle);
        nChannelState[i].algCreated = XDAS_FALSE;
      }
      /*----------------------------------------------------------------------*/
      /* Check whether the algorithm instance is still exists, delete if so.  */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].algCreated == XDAS_TRUE)
      {
        RMAN_FreeResources((IALG_Handle)nChannelState[i].h264decHandle, i);
        H264VDEC_delete(nChannelState[i].h264decHandle);
      }
      /*----------------------------------------------------------------------*/
      /* Close the profile info file.                                         */
      /*----------------------------------------------------------------------*/
      if(nChannelState[i].appCntrlParams.profileEnable)
      {
        fclose(fCycles);
      }
    }
    /*------------------------------------------------------------------------*/
    /* Free the temporary buffer                                              */
    /*------------------------------------------------------------------------*/
    free((void *)fieldBuf);
  }
#ifdef DUMP_PROFILE_NUMS
  fclose(fProfileNums);
#endif

  /*--------------------------------------------------------------------------*/
  /* Close the config and Log files                                           */
  /*--------------------------------------------------------------------------*/
  fclose(fConfigFile);
  fclose(fLogFile);

  return (0);

} /* main()*/

