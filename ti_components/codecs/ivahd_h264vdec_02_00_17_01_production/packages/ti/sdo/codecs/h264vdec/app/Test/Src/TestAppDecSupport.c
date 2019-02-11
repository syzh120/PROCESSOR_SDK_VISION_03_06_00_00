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
 * @file <TestAppDecSupport.c>                          
 *                                       
 * @brief  This file has functions to support the main sample test application
 *
 *         This file has H.264 app functions to support   
 *         the main sample test application. 
 *  
 * @author: Ramakrishna Adireddy
 *
 * @version 0.0 (July 2010) : Base version 
 * @version 0.1 (Dec 2010)  : Implemented the configurability for the detection
 *                           of CABAC and IPCM alignment errors. 
 *                           [Ramakrishna Adireddy]
 *
 * @version 0.2 (June 2011)  :Added feature of dual yuv support in order to 
 *                            provide the codec dual yuv buf Descripters.
 *                           [Vijay Kumar Yadav] 
 * @version 0.3 (Oct 2011) : Added WaterMark support to the decoder.
 *                           [Suresh Reddy]
 * @version 0.4 (July 2012): Support to parse new parameter added for 
 *                           decoding only specific frame types as requested by 
 *                           application [Mahantesh]
 ******************************************************************************
*/
/******************************************************************************
*  INCLUDE FILES                                                
******************************************************************************/
#include <xdc/std.h>
#include <TestAppDecoder.h>
#include <TestApp_rmanConfig.h>
/* -------------------------------------------------------------------------- */
/*  Externally declared variables, but referred here.                         */
/* -------------------------------------------------------------------------- */
extern H264VDEC_InArgs    inArgs;
extern H264VDEC_OutArgs   outArgs;

extern XDAS_Int8  inputDataScatBlocks[NUM_BUFS_INPUTDS][
                               INPUT_DATASYNC_BUFFER_SIZE];
extern XDAS_Int8  inputData[INPUT_BUFFER_SIZE];
extern XDAS_UInt32 blockSizeArray[NUM_INPUT_BLOCKS];

extern XDAS_UInt32 bytesConsumedNalFormat;
extern XDAS_UInt16 DataSyncIntrCntr;

extern XDAS_UInt32 curr_ddr_addr;
extern XDAS_UInt32 bytes_ddr;
extern XDAS_UInt32 curr_ddr_bytes;
extern XDAS_UInt32 rowNum;
extern XDAS_UInt32 firstDataSyncCallInFrame;

extern XDAS_UInt8  appIvahdId;
extern XDAS_Int8   configStatus;
extern XDAS_UInt32  dsBufIdx;
extern XDAS_Int32  countConfigSet;

extern H264VDEC_Params          params;
extern H264VDEC_DynamicParams   dynamicParams;
extern sAppControlParams        appControlPrms;
extern const XDAS_UInt32 IVAHD_memory_wfi[];
extern XDAS_Int32 putBufferCount;
extern sChannelState nChannelState[NUM_DEC_CHANNELS_SUPPORTED];
/*----------------------------------------------------------------------------*/
/*  Token Map array for inputs from testparams.cfg file.                      */
/*----------------------------------------------------------------------------*/
sTokenMapping sTokenMap[] =
{
  {(XDAS_Int8 *)"maxHeight",          &params.viddec3Params.maxHeight, 0},
  {(XDAS_Int8 *)"maxWidth",           &params.viddec3Params.maxWidth, 0},
  {(XDAS_Int8 *)"maxFrameRate",       &params.viddec3Params.maxFrameRate, 0},
  {(XDAS_Int8 *)"maxBitRate",         &params.viddec3Params.maxBitRate, 0},
  {(XDAS_Int8 *)"dataEndianness",     &params.viddec3Params.dataEndianness, 0},
  {(XDAS_Int8 *)"forceChromaFormat",  
                                   &params.viddec3Params.forceChromaFormat, 0},
  {(XDAS_Int8 *)"operatingMode",      &params.viddec3Params.operatingMode, 0},
  {(XDAS_Int8 *)"displayDelay",       &params.viddec3Params.displayDelay, 0},
  {(XDAS_Int8 *)"inputDataMode",      &params.viddec3Params.inputDataMode, 0},
  {(XDAS_Int8 *)"outputDataMode",     &params.viddec3Params.outputDataMode, 0},
  {(XDAS_Int8 *)"numInputDataUnits",  
                                   &params.viddec3Params.numInputDataUnits, 0},
  {(XDAS_Int8 *)"numOutputDataUnits", 
                                  &params.viddec3Params.numOutputDataUnits, 0},
  {(XDAS_Int8 *)"errorInfoMode",      &params.viddec3Params.errorInfoMode, 0},
  {(XDAS_Int8 *)"displayBufsMode",    &params.viddec3Params.displayBufsMode, 0},
  {(XDAS_Int8 *)"dpbSizeInFrames",    &params.dpbSizeInFrames, 0},
  {(XDAS_Int8 *)"bitStreamFormat",    &params.bitStreamFormat, 0},
  {(XDAS_Int8 *)"errConcealmentMode", &params.errConcealmentMode, 0},
  {(XDAS_Int8 *)"temporalDirModePred",&params.temporalDirModePred, 0},
  {(XDAS_Int8 *)"metadataType_0",     &params.viddec3Params.metadataType[0], 0},
  {(XDAS_Int8 *)"metadataType_1",     &params.viddec3Params.metadataType[1], 0},
  {(XDAS_Int8 *)"metadataType_2",     &params.viddec3Params.metadataType[2], 0},
  {(XDAS_Int8 *)"svcExtensionFlag",   &params.svcExtensionFlag, 0},
  {(XDAS_Int8 *)"svcTargetLayerDID",  &params.svcTargetLayerDID, 0},
  {(XDAS_Int8 *)"svcTargetLayerTID",  &params.svcTargetLayerTID, 0},
  {(XDAS_Int8 *)"svcTargetLayerQID",  &params.svcTargetLayerQID, 0},
  {(XDAS_Int8 *)"presetLevelIdc",     &params.presetLevelIdc, 0},
  {(XDAS_Int8 *)"presetProfileIdc",   &params.presetProfileIdc, 0},
  {(XDAS_Int8 *)"detectCabacAlignErr",  &params.detectCabacAlignErr, 0},
  {(XDAS_Int8 *)"detectIPCMAlignErr",   &params.detectIPCMAlignErr, 0},
  {(XDAS_Int8 *)"debugTraceLevel",    &params.debugTraceLevel, 0},
  {(XDAS_Int8 *)"LastNFramesToLog",   &params.lastNFramesToLog},
  {(XDAS_Int8 *)"enableDualOutput",   &params.enableDualOutput,
                                             IH264VDEC_DUALOUTPUT_DISABLE},
  {(XDAS_Int8 *)"processCallLevel",   &params.processCallLevel},
  {(XDAS_Int8 *)"enableWatermark",    &params.enableWatermark, 
                                             IH264VDEC_WATERMARK_DISABLE},
  {(XDAS_Int8 *)"decodeFrameType",  &params.decodeFrameType, 
                                        IH264VDEC_DECODE_ALL},
  {(XDAS_Int8 *)"decodeHeader",      
                          &dynamicParams.viddec3DynamicParams.decodeHeader, 0},
  {(XDAS_Int8 *)"displayWidth",      
                          &dynamicParams.viddec3DynamicParams.displayWidth, 0},
  {(XDAS_Int8 *)"frameSkipMode",     
                         &dynamicParams.viddec3DynamicParams.frameSkipMode, 0},
  {(XDAS_Int8 *)"newFrameFlag",      
                          &dynamicParams.viddec3DynamicParams.newFrameFlag, 0},
  {(XDAS_Int8 *)"lateAcquireArg",      
                        &dynamicParams.viddec3DynamicParams.lateAcquireArg, 0},
  {(XDAS_Int8 *)"deblockFilterMode",   &dynamicParams.deblockFilterMode, 0},
  {(XDAS_Int8 *)"DynSvcTargetLayerDID", &dynamicParams.svcTargetLayerDID, 0},
  {(XDAS_Int8 *)"DynSvcTargetLayerTID", &dynamicParams.svcTargetLayerTID, 0},
  {(XDAS_Int8 *)"DynSvcTargetLayerQID", &dynamicParams.svcTargetLayerQID, 0},
  {(XDAS_Int8 *)"DynSvcELayerDecode",   &dynamicParams.svcELayerDecode, 0},
  {(XDAS_Int8 *)"DynRsvd0",          &dynamicParams.reserved[0], 0},
  {(XDAS_Int8 *)"DynRsvd1",          &dynamicParams.reserved[1], 0},
  {(XDAS_Int8 *)"DynRsvd2",          &dynamicParams.reserved[2], 0},
  {(XDAS_Int8 *)"SeiDataWriteMode",  &appControlPrms.seiDataMode, 0},
  {(XDAS_Int8 *)"VuiDataWriteMode",  &appControlPrms.vuiDataMode, 0},
  {(XDAS_Int8 *)"MbInfoWriteMode",   &appControlPrms.mbInfoWriteMode, 0},  
  {(XDAS_Int8 *)"TilerEnable",       &appControlPrms.tilerEnable, 0},
  {(XDAS_Int8 *)"DualTilerEnable",   &appControlPrms.dualTilerEnable, 0},
  {(XDAS_Int8 *)"ChromaTilerMode",   &appControlPrms.chromaTilerMode, 0},
  {(XDAS_Int8 *)"BitStreamMode",     &appControlPrms.bitStreamMode, 0},
  {(XDAS_Int8 *)"NumFramesToDecode", &appControlPrms.framesToDecode, 0},
  {(XDAS_Int8 *)"parBoundCheck",     &appControlPrms.parBoundCheck, 0},
  {(XDAS_Int8 *)"parExpectedStatus", &appControlPrms.parExpectedStatus, 0},
  {(XDAS_Int8 *)"exitLevel",         &appControlPrms.exitLevel, 0},
  {(XDAS_Int8 *)"xdmReset",          &appControlPrms.xdmReset, 0},
  {(XDAS_Int8 *)"DumpFrom",          &appControlPrms.dumpFrom, 0},
  {(XDAS_Int8 *)"CRCEnable",         &appControlPrms.crcNyuv, 0},
  {(XDAS_Int8 *)"ProfileEnable",     &appControlPrms.profileEnable, 0},
  {(XDAS_Int8 *)"BaseClassOnly",     &appControlPrms.baseClassOnly, 0},
  {(XDAS_Int8 *)"DDRConstLocation",  &appControlPrms.ddrConstLocation, 0},
  {(XDAS_Int8 *)"ivahdID",           &appControlPrms.ivahdId, 0},
  {(XDAS_Int8 *)"AppRsvd0",          &appControlPrms.reserved[0], 0},
  {(XDAS_Int8 *)"inputBitStream",    &appControlPrms.inFile, 1},
  {(XDAS_Int8 *)"outputYUV",         &appControlPrms.outFile, 1},
  {(XDAS_Int8 *)"outputDualYUV",     &appControlPrms.outDualFile, 1},
  {(XDAS_Int8 *)"WaterMarkFile",     &appControlPrms.WaterMarkFile, 1},
  {(XDAS_Int8 *)"referenceYUV",      &appControlPrms.refFile, 1},
  {(XDAS_Int8 *)"frameSizeFile",     &appControlPrms.sizeFile, 1},
  {(XDAS_Int8 *)"TestCompliance",    &appControlPrms.testCompliance, 0},
  {NULL,             NULL}
};
/*------------------------------------------------------------------------*/
/* Arrays to capture the metadata buffer indicies: 3 types of metadata    */
/* are supported by the decoder: SEI, VUI and MBInfo                      */
/*------------------------------------------------------------------------*/
XDAS_UInt8 metaDataIndex[NUM_DEC_CHANNELS_SUPPORTED][IVIDEO_MAX_NUM_METADATA_PLANES];
XDAS_UInt8 metaDataEnable[NUM_DEC_CHANNELS_SUPPORTED][IVIDEO_MAX_NUM_METADATA_PLANES];

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
 *  @param[in] chnlNum  : Decoder channel number.
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void TestApp_updateIObufDesc(XDM2_BufDesc     *inputBufDesc,
                             XDM2_BufDesc     *outputBufDesc,
                             IVIDDEC3_Status  *status,
                             XDAS_UInt32      bytesConsumed,
                             XDAS_Int32       validBytes,
                             XDAS_Int8        chnlNum,
                             XDAS_Int8        outBufsInUseFlag
                            )
{
  XDAS_Int8   tag;
  XDAS_UInt8  metaBufIdx, Idx;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

  if(nChannelState[chnlNum].appCntrlParams.bitStreamMode != BS_FRAME_MODE)
  {
    /*------------------------------------------------------------------------*/
    /*  Reinitialize the input data buf ptr with the right offset from the    */
    /*  the start of inputData with the help of current value of              */
    /*  bytesConsumed which tells the number of bytes used up for the         */
    /*  current config stream.                                                */
    /*------------------------------------------------------------------------*/
    inputBufDesc->descs[0].buf = (XDAS_Int8 *)(
        (XDAS_Int32) nChannelState[chnlNum].bitStreamData + bytesConsumed);
    /*------------------------------------------------------------------------*/
    /* For datasync mode of opearation, the input data is read into the start */
    /* of the buffer in every process call, hence the input pointer is re-    */
    /* initailized to inputBufDesc->descs[0].buf. Also for fixed bytes mode of*/
    /* operation, the input number of bytes are fixed at 4K Bytes.            */
    /*------------------------------------------------------------------------*/
    if(nChannelState[chnlNum].params.viddec3Params.inputDataMode != 
        IVIDEO_ENTIREFRAME)
    {
      curr_ddr_addr  = (XDAS_UInt32)inputBufDesc->descs[0].buf;
      bytes_ddr      = validBytes;
 
      if(nChannelState[chnlNum].params.viddec3Params.inputDataMode == 
        IVIDEO_FIXEDLENGTH)
      {
        curr_ddr_bytes = ((validBytes > FIXEDLENGTH_DSMODE_SIZE) ? 
                          (FIXEDLENGTH_DSMODE_SIZE) : (validBytes));
      }
      else
      {
        curr_ddr_addr  = (XDAS_Int32) nChannelState[chnlNum].bitStreamData + 
                            bytesConsumedNalFormat;
        curr_ddr_bytes = validBytes;
      }
    }
  }
  else
  {
    inputBufDesc->descs[0].buf = (XDAS_Int8 *)(
                        (XDAS_Int32) nChannelState[chnlNum].bitStreamData);
  }

  /*--------------------------------------------------------------------------*/
  /* Do the update of output buffer descriptor only when the decode mode is   */
  /* set to XDM_DECODE_AU                                                     */
  /*--------------------------------------------------------------------------*/
  if((nChannelState[chnlNum].decodeMode == XDM_DECODE_AU) && !outBufsInUseFlag)
  {
    /*------------------------------------------------------------------------*/
    /*  NON_CONTIGUOUS BUFFERS:                                               */
    /*  Separate Buffers for Luma & Chroma.                                   */
    /*  Copy the output buffer size values and pointers from the buffer       */
    /*  element returned by getfreebuffer() function.                         */
    /* The output buffer memType can be TILED or NON-TILED based on the input */
    /* configuration chosen.                                                  */
    /*------------------------------------------------------------------------*/
    for(tag = 0 ; tag < 4 ; tag++)
    {
      outputBufDesc->descs[tag].buf = 
                    (XDAS_Int8 *) nChannelState[chnlNum].buffEle->buf[tag];

      if(nChannelState[chnlNum].appCntrlParams.tilerEnable && 
            nChannelState[chnlNum].appCntrlParams.dualTilerEnable)
      {
        outputBufDesc->descs[tag].memType = 
                                         status->bufInfo.outBufMemoryType[tag];

        if(nChannelState[chnlNum].appCntrlParams.chromaTilerMode && tag)
        {
          outputBufDesc->descs[tag].memType = XDM_MEMTYPE_TILED8;
        }

        outputBufDesc->descs[tag].bufSize.tileMem.width  = 
       (XDAS_Int32) nChannelState[chnlNum].buffEle->bufSize[tag].tileMem.width;

        outputBufDesc->descs[tag].bufSize.tileMem.height = 
       (XDAS_Int32) nChannelState[chnlNum].buffEle->bufSize[tag].tileMem.height;
      }
      /* one is tiler and another is non tiler                                */
      else if (nChannelState[chnlNum].appCntrlParams.tilerEnable) 
      {
        if(tag < 2)
        {
          outputBufDesc->descs[tag].memType = 
                                         status->bufInfo.outBufMemoryType[tag];

          if(nChannelState[chnlNum].appCntrlParams.chromaTilerMode && tag)
          {
            outputBufDesc->descs[tag].memType = XDM_MEMTYPE_TILED8;
          }

          outputBufDesc->descs[tag].bufSize.tileMem.width  = 
        (XDAS_Int32) nChannelState[chnlNum].buffEle->bufSize[tag].tileMem.width;

          outputBufDesc->descs[tag].bufSize.tileMem.height = 
       (XDAS_Int32) nChannelState[chnlNum].buffEle->bufSize[tag].tileMem.height;
        }
        else
        {
          outputBufDesc->descs[tag].bufSize.tileMem.height = 0;
          outputBufDesc->descs[tag].bufSize.tileMem.width = 0;
          outputBufDesc->descs[tag].bufSize.bytes  = 
               (XDAS_Int32) nChannelState[chnlNum].buffEle->bufSize[tag].bytes;

          outputBufDesc->descs[tag].memType = XDM_MEMTYPE_ROW;
        }
      }
      else
      {
        outputBufDesc->descs[tag].bufSize.bytes  = 
               (XDAS_Int32) nChannelState[chnlNum].buffEle->bufSize[tag].bytes;

        outputBufDesc->descs[tag].memType = XDM_MEMTYPE_ROW;
      }
    }
  }

  /*----------------------------------------------------------------------*/
  /* Meta Data (SEI, VUI & MB-Info) buffer addresses update.              */
  /*----------------------------------------------------------------------*/
  for(Idx=0; Idx<IVIDEO_MAX_NUM_METADATA_PLANES; Idx++)
  {
    if(metaDataEnable[chnlNum][Idx])
    {
      metaBufIdx = 2 + metaDataIndex[chnlNum][Idx] + (2 * dualOutputFlag);
      outputBufDesc->descs[metaBufIdx].bufSize.bytes = 
      (XDAS_Int32)nChannelState[chnlNum].buffArray[0].bufSize[metaBufIdx].bytes;
      outputBufDesc->descs[metaBufIdx].buf     = 
            (XDAS_Int8 *) nChannelState[chnlNum].buffArray[0].buf[metaBufIdx];
      outputBufDesc->descs[metaBufIdx].memType = 
                              status->bufInfo.outBufMemoryType[metaBufIdx];
    }
    else
    {
      outputBufDesc->descs[Idx + 2 + (2 * dualOutputFlag)].bufSize.bytes = 0;
      outputBufDesc->descs[Idx + 2 + (2 * dualOutputFlag)].buf = NULL;
      outputBufDesc->descs[Idx + 2 + (2 * dualOutputFlag)].memType = 
                                                        XDM_MEMTYPE_ROW;
    }
  }
}

/** 
********************************************************************************
 *  @fn     TestApp_SetInitParams
 *  @brief  The function is an Application function to set init params
 *
 *  @param[in] params  : Pointer to static params structure
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void TestApp_SetInitParams(H264VDEC_Params *params,
                                XDAS_Int8        chnlNum)
{
  XDAS_UInt8  cntr;
  /*-----------------------------------------------------------------------*/
  /*  Set IVIDDEC3_Params parameters                                       */
  /*-----------------------------------------------------------------------*/

  /*-----------------------------------------------------------------------*/
  /*  inputDataMode :  Video input data mode                               */
  /*-----------------------------------------------------------------------*/
  if((params->viddec3Params.inputDataMode == IVIDEO_SLICEMODE) &&
     (params->bitStreamFormat))
  {
    params->viddec3Params.inputDataMode  = IH264VDEC_NALUNIT_MODE;
  }

  /*-----------------------------------------------------------------------*/
  /* Relocatability of constants:                                          */
  /* If pConstantMemory is set to NULL then decoder assumes that all       */
  /* constants are pointed by symbol H264VDEC_TI_ConstData                 */
  /* i.e If the app does not need this feature, just set it to NULL        */
  /*-----------------------------------------------------------------------*/
  if(nChannelState[chnlNum].appCntrlParams.ddrConstLocation)
  {
    /*---------------------------------------------------------------------*/
    /* TODO: Get the exact size, replace 0x1000 & then do the allocation.  */
    /*---------------------------------------------------------------------*/
    params->pConstantMemory  = (XDAS_Int32)my_Memalign(128, 0x1000);
  }
  else
  {
    params->pConstantMemory  = NULL ;
  }

  /*--------------------------------------------------------------------------*/
  /* Initializing the Metadata arrays.                                        */
  /*--------------------------------------------------------------------------*/
  for(cntr = 0; cntr < IVIDEO_MAX_NUM_METADATA_PLANES; cntr++)
  {
    metaDataIndex[chnlNum][cntr]   = cntr;
    metaDataEnable[chnlNum][cntr]  = 0;
  }

  /*--------------------------------------------------------------------------*/
  /* Check metadata types                                                     */
  /* Based on the metadata types requested, fill the metadataType[] array     */
  /*--------------------------------------------------------------------------*/
  for(cntr = 0; cntr < IVIDEO_MAX_NUM_METADATA_PLANES; cntr++)
  {
    XDAS_Int32 metaType = params->viddec3Params.metadataType[cntr];

    if((metaType > IVIDEO_METADATAPLANE_NONE) && 
       (metaType < IVIDEO_MAX_NUM_METADATA_PLANES))
    {
      metaDataIndex[chnlNum][metaType]  = cntr;
      metaDataEnable[chnlNum][metaType] = 1;

      if(metaType == APP_SEI_DATA)
      {
        params->viddec3Params.metadataType[cntr] = 
                    nChannelState[chnlNum].appCntrlParams.seiDataMode?
                    IH264VDEC_ENCODED_SEI_DATA:IH264VDEC_PARSED_SEI_DATA;
      }
      else if(metaType == APP_VUI_DATA)
      {
        params->viddec3Params.metadataType[cntr] = 
                    nChannelState[chnlNum].appCntrlParams.vuiDataMode?
                    IH264VDEC_ENCODED_VUI_DATA:IH264VDEC_PARSED_VUI_DATA;
      }
      else if(metaType == APP_MB_INFO)
      {
        params->viddec3Params.metadataType[cntr] = IVIDEO_METADATAPLANE_MBINFO;
      }
    }
  }
}

/** 
********************************************************************************
 *  @fn     H264Dec_getDataSync
 *  @brief  The function is an Application function to fill datasync parameters
 *
 *  @param[in] XDM_DataSyncHandle  : datasync handle
 *          
 *  @param[in] XDM_DataSyncDesc  : datasync descriptor
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void H264Dec_getDataFixedSize(XDM_DataSyncHandle none, 
                                   XDM_DataSyncDesc *dataSyncParams)
{
  /*------------------------------------------------------------------------*/
  /* Fill the datasync descriptor fields for fixed length datasync call     */
  /*------------------------------------------------------------------------*/
  dataSyncParams->size              = sizeof(XDM_DataSyncDesc);
  dataSyncParams->baseAddr          = (XDAS_Int32 *)curr_ddr_addr;
  /*-------------------------------------------------------------------------*/
  /* For fixed length mode datasync calls, numBlocks should be 1 and         */
  /* varBlockSizesFlag and varBlockSizesFlag should be set to FALSE.         */
  /*-------------------------------------------------------------------------*/
  dataSyncParams->numBlocks         = NUM_INPUT_BLOCKS;
  dataSyncParams->varBlockSizesFlag = FALSE;
  dataSyncParams->scatteredBlocksFlag = FALSE;
  blockSizeArray[0]                 = curr_ddr_bytes;
  dataSyncParams->blockSizes        = (XDAS_Int32 *)&blockSizeArray[0];
  /*-------------------------------------------------------------------------*/
  /* Advance the DDR input buffer pointer to read the next chunk of data     */
  /*-------------------------------------------------------------------------*/
  curr_ddr_addr  += curr_ddr_bytes;
  bytes_ddr      -= curr_ddr_bytes;
  curr_ddr_bytes  = ((bytes_ddr >= FIXEDLENGTH_DSMODE_SIZE) ? 
                     (FIXEDLENGTH_DSMODE_SIZE) : (bytes_ddr));

}
/** 
********************************************************************************
 *  @fn     H264Dec_PutBuffer
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
XDAS_Void H264Dec_PutBuffer(XDM_DataSyncHandle putDataHandle, 
                            XDM_DataSyncDesc *dataSyncParams)
{
  /*------------------------------------------------------------------------*/
  /* Just Increment the putBuffer count and print number of blocks availabel*/
  /* in the putBuffer call                                                  */
  /*------------------------------------------------------------------------*/
  putBufferCount++;
  printf("PutBufferFxn Count: %d, NumBlocks: %d \n", putBufferCount, 
          dataSyncParams->numBlocks);
  
}
/** 
********************************************************************************
 *  @fn     H264Dec_DataSyncSlice
 *  @brief  The function is an Application function to fill datasync parameters
 *
 *  @param[in] XDM_DataSyncHandle  : datasync handle
 *          
 *  @param[in] XDM_DataSyncDesc  : datasync descriptor
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void H264Dec_getDataNALUnits(XDM_DataSyncHandle none,
                                  XDM_DataSyncDesc *dataSyncDesc)
{
  XDAS_Int8   i;
  XDAS_Int32  nalSizeVal,nalSizeCum = 0;
  XDAS_Int32 nalAddrArray[MAX_BLOCKS_PER_INPUTDS];
  XDAS_Int32 nalSizeArray[MAX_BLOCKS_PER_INPUTDS];
  XDAS_Int32 scSize = 0;
  XDAS_UInt8 *sreamDst = (XDAS_UInt8 *)&inputDataScatBlocks[dsBufIdx][0];
  /*------------------------------------------------------------------------*/
  /* File pointers for NAL slizes and input bit stream file                 */
  /*------------------------------------------------------------------------*/
  FILE *fsizeFile = nChannelState[0].appFilePtrs.fpSizeFile;
  /*------------------------------------------------------------------------*/
  /* Initialize the  dataSync desriptor with default values                 */
  /*------------------------------------------------------------------------*/
  dataSyncDesc->baseAddr = (XDAS_Int32 *)curr_ddr_addr;
  nalAddrArray[0] = curr_ddr_addr;
  dataSyncDesc->size = sizeof(XDM_DataSyncDesc);
  dataSyncDesc->varBlockSizesFlag = TRUE;
  dataSyncDesc->scatteredBlocksFlag = TRUE;
  dataSyncDesc->blockSizes = &nalSizeArray[0];

  if(dataSyncDesc->scatteredBlocksFlag)
  {
    dataSyncDesc->baseAddr = &nalAddrArray[0];
  }
  /*------------------------------------------------------------------------*/
  /* Check for end of file                                                  */
  /*------------------------------------------------------------------------*/
  if(!feof(fsizeFile))
  {
    for(i=0; i < (MAX_BLOCKS_PER_INPUTDS+1);i++)
    {
      /*-------------------------------------------------------------------*/
      /* Read NAL Unit size                                                */
      /*-------------------------------------------------------------------*/
      fscanf (fsizeFile,"%ld", &nalSizeVal) ;
      /*-------------------------------------------------------------------*/
      /* nalSizeVal = -1 indicates that the picture has ended              */
      /*-------------------------------------------------------------------*/
      if(nalSizeVal != -1)
      {
        /*-------------------------------------------------------------------*/
        /* Byte stream format: case for Slices with start code.              */
        /*-------------------------------------------------------------------*/
        if(nChannelState[0].params.viddec3Params.inputDataMode == 
            IVIDEO_SLICEMODE)
        {
          /*-----------------------------------------------------------------*/
          /* Fill the Address and size value for the NAL, assuming contigous */
          /* NAL's                                                           */
          /*-----------------------------------------------------------------*/
          nalAddrArray[i]  = curr_ddr_addr;
          nalSizeArray[i] =  nalSizeVal ;

          if(dataSyncDesc->scatteredBlocksFlag)
          {
            /*----------------------------------------------------------------*/
            /* If scatteredBlocksFlag is set, then this means the NAL units   */
            /* are not contigous, so copy the stream to non contigous         */
            /* locations. sreamDst is a separate array to which the stream    */
            /* is copied to mimic the non contigous behavior.                 */
            /*----------------------------------------------------------------*/
            memcpy(sreamDst, (void *)nalAddrArray[i], nalSizeVal);
            nalAddrArray[i] = (XDAS_Int32) sreamDst;
            /*----------------------------------------------------------------*/
            /* increment the sreamDst: GAP_BETWEEN_DS_BLOCKS is some GAP      */
            /* created between 2 blocks to mimic the non contigous behavior   */
            /*----------------------------------------------------------------*/
            sreamDst += (nalSizeVal + GAP_BETWEEN_DS_BLOCKS);
          }
        }
        else
        {
          /*------------------------------------------------------------------*/
          /* APP_INPUTDS_NALMODE :                                            */
          /* NAL stream format Support. In NAL stream format, the start code  */
          /* will not be there. The size of the NAL is communicated by the    */
          /* blockSizes array. The start code can be 3 byte or 4 byte. First  */
          /* check if the SC size is 3 or 4 bytes.The stream without start    */
          /* code need to be copied to sreamDst location .                    */
          /*------------------------------------------------------------------*/
          XDAS_UInt8 *stream =  (XDAS_UInt8 *)curr_ddr_addr;
          scSize = 4;
          /*------------------------------------------------------------------*/
          /* Check for start code size: 3 or 4 bytes                          */
          /*------------------------------------------------------------------*/
          if((stream[0] == 0) && (stream[1] == 0) && (stream[2] == 0x01))
          {
            scSize = 3;
          }
          /*------------------------------------------------------------------*/
          /* The actual size given to the codec is the size without start code*/
          /*------------------------------------------------------------------*/
          nalSizeArray[i] =  nalSizeVal - scSize;
          nalAddrArray[i]  = (XDAS_Int32)sreamDst;
          /*------------------------------------------------------------------*/
          /* Copy the NAL unit into sreamDst : This is needed for both        */
          /* contigous and non-contigous NAL Units                            */
          /*------------------------------------------------------------------*/
          memcpy(sreamDst, (stream + scSize), nalSizeArray[i]);
        
          if(dataSyncDesc->scatteredBlocksFlag)
          {
            /*----------------------------------------------------------------*/
            /* increment the sreamDst: GAP_BETWEEN_DS_BLOCKS is some GAP      */
            /* created between 2 blocks to mimic the non contigous behavior   */
            /*----------------------------------------------------------------*/
            sreamDst += (nalSizeArray[i] + GAP_BETWEEN_DS_BLOCKS);

          }
          else
          {
            /*----------------------------------------------------------------*/
            /* increment the sreamDst: This should form a contigous array of  */
            /* NAL units (witout start code)                                  */
            /*----------------------------------------------------------------*/
            sreamDst += nalSizeArray[i];          
          }
        }
        /*--------------------------------------------------------------------*/
        /* Fill the size array, increment input buffer pointer                */
        /*--------------------------------------------------------------------*/
        curr_ddr_addr  += nalSizeVal;
        bytes_ddr      -= nalSizeVal;
        /*--------------------------------------------------------------------*/
        /* Fill the Address array, increment cumulative NAL size              */
        /* Also update the number of blocks                                   */
        /*--------------------------------------------------------------------*/
        nalSizeCum += (nalSizeVal - scSize) ;
        bytesConsumedNalFormat += nalSizeVal;
        dataSyncDesc->numBlocks  = (i+1);
        /*--------------------------------------------------------------------*/
        /* The first DS call of a picture can have any size(even <1K), so just*/
        /* fill 1 slice and return                                            */
        /*--------------------------------------------------------------------*/
        if(firstDataSyncCallInFrame)
          break;
        /*--------------------------------------------------------------------*/
        /* The subsequent calls (except the last call of a picture) should    */
        /* have at least 1K of data                                           */
        /*--------------------------------------------------------------------*/
        if(nalSizeCum >= MIN_DATASIZE_SLICEDS)
        {
          break;
        }
      }
      else
      {
        /*--------------------------------------------------------------------*/
        /* if the frame has ended (nalSizeVal = -1) and no more data is       */
        /* available, then return 0 bytes                                     */
        /*--------------------------------------------------------------------*/
        if(i==0)
        {
          dataSyncDesc->numBlocks = 0;
          nalSizeArray[0] = 0;
        }
        break;
      }
    }
  }
  else
  {
    /*-----------------------------------------------------------------*/
    /* End of file, retrn 0 bytes                                      */
    /*-----------------------------------------------------------------*/
    dataSyncDesc->blockSizes[0] = 0;
    dataSyncDesc->baseAddr[0]   =  NULL;
    dataSyncDesc->numBlocks     = 0;
    nChannelState[0].streamEnd = 1;
  }

  if (nalSizeCum < 0)
    nalSizeCum = 0;
  /*-----------------------------------------------------------------*/
  /* End of file,Set streamEnd to start decoder flush                */
  /*-----------------------------------------------------------------*/
  if(feof(fsizeFile))
    nChannelState[0].streamEnd = 1;
  /*-----------------------------------------------------------------*/
  /* reset firstCallInFrame                                          */
  /*-----------------------------------------------------------------*/
  firstDataSyncCallInFrame = 0;
  /*-----------------------------------------------------------------*/
  /* There is need for multiple DS buffers since the previous buffer */
  /* may not be fully consumed yet, so the index id incremented and  */
  /* wrapped around when the index reaches NUM_BUFS_INPUTDS.         */
  /*-----------------------------------------------------------------*/
  dsBufIdx++;
  if(dsBufIdx == NUM_BUFS_INPUTDS)
  {
    dsBufIdx = 0;
  }
}

/** 
********************************************************************************
 *  @fn     H264Dec_getDataSync
 *  @brief  The function is an Application function to fill datasync parameters
 *
 *  @param[in] XDM_DataSyncHandle  : datasync handle
 *          
 *  @param[in] XDM_DataSyncDesc  : datasync descriptor
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void H264Dec_putDataSync(XDM_DataSyncHandle none, 
                              XDM_DataSyncDesc *dataSyncParams)
{
  XDAS_UInt32 numRows = dataSyncParams->numBlocks;
  /*--------------------------------------------------------------------------*/
  /* Increment the row counter by number of rows output in this datasync call */
  /*--------------------------------------------------------------------------*/
  rowNum += numRows;
  DataSyncIntrCntr++;
}
/** 
********************************************************************************
 *  @fn     TestApp_SetDynamicParams
 *  @brief  The function is an Application function to set dynamic params
 *
 *  @param[in] dynamicParams  : Pointer to dynamic params structure
 *          
 *  @return  None
********************************************************************************
*/
XDAS_Void TestApp_SetDynamicParams(IVIDDEC3_DynamicParams *dynamicParams,
                                   XDAS_Int8        chnlNum)
{
  /*--------------------------------------------------------------------------*/
  /* Set IVIDDEC3 Run time parameters                                         */
  /*--------------------------------------------------------------------------*/
  if(!nChannelState[chnlNum].appCntrlParams.parBoundCheck)
  {
    dynamicParams->decodeHeader  = nChannelState[chnlNum].decodeMode;
  }

  dynamicParams->putDataFxn    = (XDM_DataSyncPutFxn)&H264Dec_putDataSync;
  dynamicParams->putDataHandle = NULL;
  /*--------------------------------------------------------------------------*/
  /* inputDatasyncMode =1 means fixed size blocks                             */
  /*--------------------------------------------------------------------------*/
  if(nChannelState[chnlNum].params.viddec3Params.inputDataMode == 
    IVIDEO_FIXEDLENGTH)
  {
    dynamicParams->getDataFxn = (XDM_DataSyncGetFxn)&H264Dec_getDataFixedSize;
  }
  else
  {
    /*------------------------------------------------------------------------*/
    /* inputDatasyncMode =2 means slice level datasyc                         */
    /*------------------------------------------------------------------------*/
    dynamicParams->getDataFxn    = (XDM_DataSyncGetFxn)&H264Dec_getDataNALUnits;
  }
  /*------------------------------------------------------------------------*/
  /* Populate the function pointer for putBuffer function.                  */
  /* Note: the putBufferHandle and getDataHandle can be used by the app     */
  /* to indicate any additional info related to the putBuffer call          */
  /* Here we do not use this handle for any further processing hence setting*/
  /* them to NULL                                                           */
  /*------------------------------------------------------------------------*/  
  dynamicParams->putBufferFxn    = (XDM_DataSyncPutBufferFxn)&H264Dec_PutBuffer;
  dynamicParams->putBufferHandle = NULL;
  dynamicParams->getDataHandle   = NULL;
}

/** 
********************************************************************************
 *  @fn     MEMUTILS_getPhysicalAddr
 *
 *  @brief  Sample utility function that need to be implemented by the 
 *          applicationor framework components for address translation
 *           (virtual to physical). This function is SOC/APP specific.
 *
 *  @param[in] Addr  : Address to be translated.
 *          
 *  @return  translated address
********************************************************************************
*/
XDAS_Void *MEMUTILS_getPhysicalAddr(Ptr Addr)
{ 

#ifdef USE_HOST_FILE_IO  
  Uint32 temp1;
#endif
  if(Addr == NULL)
  {
    printf("NULL address sent for V2P conversion: %d\n", Addr);
  }
  
#ifdef USE_HOST_FILE_IO  

  if(((Uint32)Addr<(0x0+0x4000))){
   temp1= ((Uint32)Addr+0x9d000000);
  }else if(((Uint32)Addr>=0x4000)&&((Uint32)Addr<(0x4000+0x1fc000))){
   temp1= ((Uint32)Addr - 0x4000 + 0x9d004000);
  }else if(((Uint32)Addr>=0x200000)&&((Uint32)Addr<(0x200000+0x600000))){
   temp1= ((Uint32)Addr - 0x200000 + 0x9d200000);
  }else if(((Uint32)Addr>=0x800000)&&((Uint32)Addr<(0x800000+0x200000))){
   temp1= ((Uint32)Addr - 0x800000 + 0x9d800000);
  }else if(((Uint32)Addr>=0xa00000)&&((Uint32)Addr<(0xa00000+0x600000))){
   temp1= ((Uint32)Addr - 0xa00000 + 0x9da00000);

  }else if(((Uint32)Addr>=0x80000000)&&((Uint32)Addr<(0x80000000+0x100000))){
   temp1= ((Uint32)Addr - 0x80000000 +0x9e000000);
  }else if(((Uint32)Addr>=0x80100000)&&((Uint32)Addr<(0x80100000+0x100000))){
   temp1= ((Uint32)Addr - 0x80100000 + 0x9e100000);

  }else if(((Uint32)Addr>=0x80200000)&&((Uint32)Addr<(0x80200000+0x100000))){
   temp1= ((Uint32)Addr - 0x80200000 +0x9e200000);

  }else if(((Uint32)Addr>=0x80300000)&&((Uint32)Addr<(0x80300000+0x1000000))){
   temp1= ((Uint32)Addr - 0x80300000 +0x9e300000);

  }else if(((Uint32)Addr>=0x81300000)&&((Uint32)Addr<(0x81300000+0xc00000))){
   temp1= ((Uint32)Addr - 0x81300000 +0x9f300000);

  }else if(((Uint32)Addr>=0x81f00000)&&((Uint32)Addr<(0x81f00000+0x100000))){
   temp1= ((Uint32)Addr - 0x81f00000 +0x9ff00000);

  }else if(((Uint32)Addr>=0xa0000000)&&((Uint32)Addr<(0xa0000000+0x55000))){
   temp1= ((Uint32)Addr - 0xa0000000 +0x9cf00000);

  }else if(((Uint32)Addr>=0xa0055000)&&((Uint32)Addr<(0xa0055000+0x55000))){
   temp1= ((Uint32)Addr - 0xa0055000 +0x9cf55000);

  }else{
   temp1= ((Uint32)Addr & 0xFFFFFFFF);
  }
  return (Void *)temp1;
#else
  /*------------------------------------------------------------------------*/
  /* Address translation based on the SOC/APP                               */
  /*------------------------------------------------------------------------*/
#ifdef HOST_ASIC
  return ((void *)((unsigned int)Addr - 0x20000000));
#elif defined(HOST_ARM9)
  return ((void *)((unsigned int)Addr & VDMAVIEW_EXTMEM));
#else
  return ((void*)Addr);
#endif
#endif
}

/** 
********************************************************************************
 *  @fn     paramBoundaryCheck
 *  @brief  main function of Host TestAppDecoder
 *          
 *  @param[in] retVal       : Indicates the value returned by create call or
 *                            control call.
 *  @param[in] checkLevel   : Indicates the check & exit points during param
 *                            boundary checks validation.
 *  @param[in] chnlNum     : Decode channel number
 *                           
 *          
 *  @return IALG_EFAIL/APP_NEXT_CONFIG/APP_SAME_CONFIG
********************************************************************************
*/
XDAS_Int8 paramBoundaryCheck(XDAS_Int8 status, XDAS_Int8 checkLevel,
                             XDAS_Int8 chnlNum)
{
  XDAS_UInt8 freeMem = 0;
  XDAS_Int8  retVal  = APP_SAME_CONFIG;
  /*------------------------------------------------------------------------*/
  /* Check if parameter Boundary Check validation is enabled.               */
  /*------------------------------------------------------------------------*/
  if(nChannelState[chnlNum].appCntrlParams.parBoundCheck)
  {
    if(nChannelState[chnlNum].appCntrlParams.exitLevel == checkLevel)
    {
      if(status != nChannelState[chnlNum].appCntrlParams.parExpectedStatus)
      {
        configStatus = IALG_EFAIL;
      }
      freeMem = 1;
      retVal  = APP_NEXT_CONFIG;
      /*--------------------------------------------------------------------*/
      /* Print each config status in a Log file to check the failures if any*/
      /*--------------------------------------------------------------------*/
      updateConfigStatusFile(configStatus);
    }

    if(retVal == APP_NEXT_CONFIG)
    {
      countConfigSet++;
      my_fclose(nChannelState[chnlNum].appFilePtrs.fpInFile, ARG_FILEIO_TYPE);
      my_fclose(nChannelState[chnlNum].appFilePtrs.fpOutFile, ARG_FILEIO_TYPE);
      fclose(nChannelState[chnlNum].appFilePtrs.fpRefFile);
      nChannelState[chnlNum].algCreated = XDAS_FALSE;
    }

    /*----------------------------------------------------------------------*/
    /* Check if it is time to free up the memory blocks.                    */
    /*----------------------------------------------------------------------*/
    if(freeMem && (nChannelState[chnlNum].h264decHandle != NULL))
    {
      RMAN_FreeResources((IALG_Handle)nChannelState[chnlNum].h264decHandle, 
            chnlNum);
      H264VDEC_delete(nChannelState[chnlNum].h264decHandle);
    }
  }
  else if(nChannelState[chnlNum].h264decHandle == NULL)
  {
    nChannelState[chnlNum].algCreated = XDAS_FALSE;
    retVal  = APP_NEXT_CONFIG;
  }

  return retVal;
}

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
XDAS_Bool TestApp_flushCheck(XDAS_Int32 errMsg)
{
  /*----------------------------------------------------------------------*/
  /* Under certain error conditions, the application need to stop decoding*/
  /* the current stream and do an XDM_FLUSH which enables the codec to    */
  /* flush (display and free up) the frames locked by it. The following   */
  /* error conditions fall in this category.                              */
  /*----------------------------------------------------------------------*/
  if((TestApp_checkErr(errMsg, XDM_INSUFFICIENTDATA)) ||
     (TestApp_checkErr(errMsg, IH264VDEC_ERR_STREAM_END)) ||
     (TestApp_checkErr(errMsg, IH264VDEC_ERR_PICSIZECHANGE)) ||
     (TestApp_checkErr(errMsg, IH264VDEC_ERR_UNSUPPRESOLUTION)) ||
     (TestApp_checkErr(errMsg, IH264VDEC_ERR_NUMREF_FRAMES)) ||
     (TestApp_checkErr(errMsg, IH264VDEC_ERR_INVALID_MBOX_MESSAGE)) ||
     (TestApp_checkErr(errMsg, IH264VDEC_ERR_DATA_SYNC)) ||
     (TestApp_checkErr(errMsg, IH264VDEC_ERR_DISPLAYWIDTH)))
  {
    return XDAS_TRUE;
  }
  else
  {
    return XDAS_FALSE;
  }
}


/** 
********************************************************************************
 *  @fn     testAppFlushFrames
 *  @brief  Flush implementation : First the application needs to call control 
 *          API with XDM_FLUSH command. Then the buffers provided by the decoder
 *          need to be displayed and freed up. This function implements this 
 *          flush opearation.
 *          
 *  @param[in] inputBufDesc : Pointer to the input Buffer descriptor
 *  @param[in] outputBufDesc: Pointer to the output Buffer descriptor
 *  @param[in] displayBufs  : Pointer to the display Buffers descriptor
 *  @param[in] chnlNum      : Decoder channel number.
 *          
 *  @return IVIDDEC3_EOK/IVIDDEC3_EFAIL
********************************************************************************
*/
XDAS_Int8 testAppFlushFrames(XDM2_BufDesc *inputBufDesc, 
                              XDM2_BufDesc *outputBufDesc,
                              IVIDEO2_BufDesc *displayBufs,
                              XDAS_Int8  chnlNum)
{
  XDAS_Int8         testVal;
  XDAS_Int16 idx = 0;
  XDAS_Int32 retVal;
  IH264VDEC_ProcessParamsList singleChannelList;
  /*--------------------------------------------------------------------*/
  /* Put the decoder in FLUSH mode through the control() call and       */
  /* XDM_FLUSH command.                                                 */
  /*--------------------------------------------------------------------*/
  H264VDEC_control(nChannelState[chnlNum].h264decHandle, XDM_FLUSH, 
    &nChannelState[chnlNum].dynamicParams, &nChannelState[chnlNum].status);
  /*--------------------------------------------------------------------*/
  /* The following loop displays and frees up the buffers locked by the */
  /* decoder. After the XDM_FLUSH command, the app needs to call the    */
  /* process function untill the process returns IVIDDEC3_EOK. The      */
  /* frame ids provided in the OutArgs need to be displayed/freed up.   */
  /* The loop breaks once process call returns failure (IVIDDEC3_EFAIL) */
  /*--------------------------------------------------------------------*/
  singleChannelList.numEntries = 1;
  singleChannelList.processParams[0].handle = 
                                    nChannelState[chnlNum].h264decHandle;
  singleChannelList.processParams[0].inBufs = 
                                   &nChannelState[chnlNum].inputBufDesc;
  singleChannelList.processParams[0].outBufs = 
                                   &nChannelState[chnlNum].outputBufDesc;
  singleChannelList.processParams[0].inArgs = (IVIDDEC3_InArgs *) 
                                              &nChannelState[chnlNum].inArgs;
  singleChannelList.processParams[0].outArgs = (IVIDDEC3_OutArgs *) 
                                              &nChannelState[chnlNum].outArgs;
  
  do
  {
#ifdef MEM_CORRUPTION_TEST
    /*----------------------------------------------------------------------*/
    /* Do scratch corruption of SL2, ITCM, DTCM and IP memories             */
    /* If memory corruption test is enabled                                 */
    /*----------------------------------------------------------------------*/
    H264DEC_ScratchMemoryCorruption();
#endif    
    /*----------------------------------------------------------------------*/
    /* Call process function. This is to flush out the frames and not for   */
    /* stream decoding. The deocder is alredy put in flush mode through     */
    /* the control call XDM_FLUSH                                           */
    /*----------------------------------------------------------------------*/
    retVal = H264VDEC_decodeFrame(&singleChannelList);
    /*----------------------------------------------------------------------*/
    /* Deactivate all resources - Dummy                                     */
    /*----------------------------------------------------------------------*/
    RMAN_DeactivateAllResources((IALG_Handle) 
                                         nChannelState[chnlNum].h264decHandle); 

#ifdef MEM_CORRUPTION_TEST
    /*----------------------------------------------------------------------*/
    /* Deactivate all resources                                             */
    /*----------------------------------------------------------------------*/
    RMAN_DeactivateAllResources((IALG_Handle) 
                                         nChannelState[chnlNum].h264decHandle);          
#endif
    /*----------------------------------------------------------------------*/
    /* If output datasync is enabled and if frame is not marked for diaply, */
    /* then return error.                                                   */
    /*----------------------------------------------------------------------*/
    if(nChannelState[chnlNum].params.viddec3Params.outputDataMode == 
            IVIDEO_NUMROWS)
    {
      if(displayBufs->numPlanes)
      {
        retVal = IVIDDEC3_EOK;
      }
      else
      {
        retVal = IVIDDEC3_EFAIL;
      }
    }
    /*----------------------------------------------------------------------*/
    /* If a frame is available for display, then write it to file           */
    /*----------------------------------------------------------------------*/
    if (retVal == IVIDDEC3_EOK && displayBufs->numPlanes) 
    {
      idx++;
      if(nChannelState[chnlNum].frameCount > 
          nChannelState[chnlNum].appCntrlParams.dumpFrom)
      {
        /*----------------------------------------------------------------*/
        /*  Request frame for display In case of Dual Output mode         */
        /*----------------------------------------------------------------*/
        if(nChannelState[chnlNum].params.enableDualOutput)
        {
          TestApp_Write_DualOutputData(nChannelState[chnlNum].appFilePtrs.
                    fpDualOutFile, &nChannelState[chnlNum].outArgs, 
                    nChannelState[chnlNum].appCntrlParams.testCompliance, 
                    nChannelState[chnlNum].appCntrlParams.crcNyuv, chnlNum);
        }
        testVal = TestApp_outputDataXfr(nChannelState[chnlNum].appFilePtrs.
                    fpOutFile, nChannelState[chnlNum].appFilePtrs.fpRefFile, 
                    nChannelState[chnlNum].outArgs, nChannelState[chnlNum].
                    appCntrlParams.testCompliance,
                    nChannelState[chnlNum].appCntrlParams.crcNyuv,chnlNum);

        if(nChannelState[chnlNum].params.enableWatermark)
        {
          /*--------------------------------------------------------------*/
          /* Write the WaterMark decrypted key to a file. One frame delay */
          /* is maintained to dump WaterMark key to the file Since we get */
          /* the encrypted key of first frame at the beginning of second  */
          /* frame.                                                       */
          /*--------------------------------------------------------------*/
          if(nChannelState[chnlNum].frameCount > 1)
          {
            my_fwrite((void *)&nChannelState[chnlNum].outArgs.decryptedKey, 
                           sizeof(char), 4, nChannelState[chnlNum].
                           appFilePtrs.fpWaterMarkFile, ARG_FILEIO_TYPE);
          }
        }
      }
    }
    
    /*-------------------------------------------------------------------*/
    /*  Check for Break off condition of in test compliance              */
    /*-------------------------------------------------------------------*/
    if(testVal == APP_EFAIL)
    {
      break;
    }

    /*------------------------------------------------------------------*/
    /* Release(FREE UP) buffers - which are released from the algorithm */
    /* side  -back to the buffer manager. The freebufID array of outargs*/
    /* contains the sequence of bufferIds which need to be freed. This  */
    /*  gets populated by the algorithm. The following function will do */
    /*  the job of freeing up the buffers.                              */
    /*------------------------------------------------------------------*/
    BUFFMGR_ReleaseBuffer((XDAS_UInt32 *)nChannelState[chnlNum].
            outArgs.viddec3OutArgs.freeBufID,chnlNum);

  } while (retVal == IVIDDEC3_EOK);
  if((nChannelState[chnlNum].params.enableWatermark) && 
        (!nChannelState[chnlNum].params.viddec3Params.displayDelay))
  {
    my_fwrite((void *)&nChannelState[chnlNum].outArgs.decryptedKey, 
          sizeof(char), 4, nChannelState[chnlNum].appFilePtrs.fpWaterMarkFile,
          ARG_FILEIO_TYPE);
  }

  printf("CH:%d Flushed %d pictures\n",chnlNum,idx);
  nChannelState[chnlNum].bufferDisplayed += idx;

  return testVal;
}

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
Void H264DEC_ScratchMemoryCorruption()
{
  /*---------------------------------------------------------------------*/
  /*  Fill whole of SL2,ITCM,DTCM and IP memories with some data, to     */
  /*  check that codec doesnt depend on SL2,ITCM,DTCM and IP memories    */
  /*  content of previous process call.                                  */
  /*---------------------------------------------------------------------*/
  XDAS_Int8 word_pattern[4] = {0x00, 0xAA, 0x55, 0x99};
  XDAS_Int8 word = word_pattern[nChannelState[0].frameCount & 0x3];

  XDAS_UInt32 regBaseAddr, memBaseAddr;

  regBaseAddr = regBaseAdderss[appIvahdId];
  memBaseAddr = memBaseAddress[appIvahdId];
  /*---------------------------------------------------------------------*/
  /* For IP corruption, turn on clocks                                   */
  /*---------------------------------------------------------------------*/  
  TestApp_turnOnClocks();

  /*------------------------------------------------------------------------*/
  /* Fill SL2 memory with some data                                         */
  /*------------------------------------------------------------------------*/
  memset ((Void*)(memBaseAddr + 0x000000000), word, (256*1024)); 

  /*------------------------------------------------------------------------*/
  /* Fill ITCM memory with some data                                        */
  /*------------------------------------------------------------------------*/
  memset ((Void*)(regBaseAddr + ICONT1_DTCM_OFFSET), word, 16*1024);   
  memset ((Void*)(regBaseAddr + ICONT2_DTCM_OFFSET), word, 16*1024);   

  /*------------------------------------------------------------------------*/
  /* Fill DTCM memory with some data                                        */
  /*------------------------------------------------------------------------*/
  memset ((Void*)(regBaseAddr + ICONT1_ITCM_OFFSET), word, 32*1024);       
  memset ((Void*)(regBaseAddr + ICONT2_ITCM_OFFSET), word, 32*1024);       


  /*------------------------------------------------------------------------*/
  /* Fill all ECD3 buffers with some data                                   */
  /*------------------------------------------------------------------------*/
  /*------------------------------------------------------------------------*/
  /* Set all buffers to full view mode                                      */
  /*------------------------------------------------------------------------*/
  *(XDAS_UInt32 *)(regBaseAddr + ECD3_CFG_OFFSET + 0x200)  = 0;

  /*------------------------------------------------------------------------*/
  /* Get owner ship of all buffers                                          */
  /*------------------------------------------------------------------------*/
  *(XDAS_UInt32 *)(regBaseAddr + ECD3_CFG_OFFSET + 0x200 + 0x4)  = 0; 
  *(XDAS_UInt32 *)(regBaseAddr + ECD3_CFG_OFFSET + 0x200 + 0x8)  = 0; 

  /*------------------------------------------------------------------------*/
  /* Fill buffers with pattern                                              */
  /*------------------------------------------------------------------------*/
  memset ((Void*)(regBaseAddr + ECD3_MEM_OFFSET), word, 0x1000);  
  memset ((Void*)(regBaseAddr + ECD3_MEM_OFFSET + 0x2000), word, 0x1800);
  memset ((Void*)(regBaseAddr + ECD3_MEM_OFFSET + 0x6000), word, 0x1000);

  /*------------------------------------------------------------------------*/
  /* Fill all MC3 buffers with some data                                   */
  /*------------------------------------------------------------------------*/
  /* Set all buffers to full view mode                                      */
  /*------------------------------------------------------------------------*/
  *(XDAS_UInt32*)(regBaseAddr + MC3_CFG_OFFSET + 0x200)   = 0;
  /*------------------------------------------------------------------------*/
  /* Get owner ship of all buffers                                          */
  /*------------------------------------------------------------------------*/
  *(XDAS_UInt32*)(regBaseAddr + MC3_CFG_OFFSET + 0x200 + 4)   = 0;
  *(XDAS_UInt32*)(regBaseAddr + MC3_CFG_OFFSET + 0x200 + 8)   = 0;    
  /*------------------------------------------------------------------------*/
  /* Fill buffers with pattern                                              */
  /*------------------------------------------------------------------------*/
  memset ((Void*)(regBaseAddr + MC3_MEM_OFFSET), word, 10*1024); 
  memset ((Void*)(regBaseAddr + MC3_MEM_OFFSET + 0x5000), word, 2*1024);
        
  /*------------------------------------------------------------------------*/
  /* Fill all CALC3 buffers with some data                                  */
  /*------------------------------------------------------------------------*/
  /* Set all buffers to full view mode                                      */
  /*------------------------------------------------------------------------*/
  *(XDAS_UInt32*)(regBaseAddr + CALC3_CFG_OFFSET + 0x200) = 0;
  /*------------------------------------------------------------------------*/
  /* Get owner ship of all buffers                                          */
  /*------------------------------------------------------------------------*/
  *(XDAS_UInt32*)(regBaseAddr + CALC3_CFG_OFFSET + 0x200 + 4)   = 0;
  *(XDAS_UInt32*)(regBaseAddr + CALC3_CFG_OFFSET + 0x200 + 8)   = 0;  
  /*------------------------------------------------------------------------*/
  /* Fill buffers with pattern                                              */
  /*------------------------------------------------------------------------*/
  memset ((Void*)(regBaseAddr + CALC3_MEM_OFFSET), word, 8*1024);       
  memset ((Void*)(regBaseAddr + CALC3_MEM_OFFSET + 0x2000), word, 
                                                                 4*1024);
  memset ((Void*)(regBaseAddr + CALC3_MEM_OFFSET + 0x3000), word, 
                                                                   4*1024);

  /*---------------------------------------------------------------------*/
  /* after IP corruption Turn off clocks                                 */
  /*---------------------------------------------------------------------*/  
  TestApp_turnOffClocks();
       
}
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
XDAS_UInt32 TestApp_turnOnClocks()
{
  XDAS_UInt32 regBaseAddr = (XDAS_UInt32)regBaseAdderss[appIvahdId]; 

  /*--------------------------------------------------------------------------*/
  /* Enable interrupts for all the required IPs. Here are the explanantion    */
  /* for the bit fields that we write into the clock control reg              */
  /*  31:11  Reserved  Reserved                                               */ 
  /*  10  SMSET  Clock control of SMSET                                       */
  /*    0: Exit idle state and start SMSET clock                              */
  /*    1: Request SMSET to go to idle state and stop SMSET clock             */
  /*        Note: Shutting-down SMSET clock may hang system                   */
  /*        if SW performs SW instrumentation and/or access                   */
  /*        to its configuration port.                                        */
  /*  9  MSGIF  Clock control of MSGIF                                        */
  /*    0: Exit idle state and start MSGIF clock                              */
  /*    1: Request MSGIF to go to idle state and stop MSGIF clock             */
  /*  8  ECD3  Clock control of ECD3                                          */
  /*    0: Exit idle state and start ECD3 clock                               */
  /*    1: Request ECD3 to go to idle state and stop ECD3 clock               */
  /*  7  MC3  Clock control of MC3                                            */
  /*    0: Exit idle state and start MC3 clock                                */
  /*    1: Request MC3 to go to idle state and stop MC3 clock                 */
  /*  6  IPE3  Clock control of IPE3                                          */
  /*    0: Exit idle state and start IPE3 clock                               */
  /*    1: Request IME3 to go to idle state and stop IPE3 clock               */
  /*  5  CALC3  Clock control of CALC3                                        */
  /*    0: Exit idle state and start CALC3 clock                              */
  /*    1: Request CALC3 to go to idle state and stop CALC3 clock             */
  /*  4  ILF3  Clock control of ILF3                                          */
  /*    0: Exit idle state and start ILF3 clock                               */
  /*    1: Request ILF3 to go to idle state and stop ILF3 clock               */
  /*  3  IME3  Clock control of IME3                                          */
  /*    0: Exit idle state and start IME3 clock                               */
  /*    1: Request IME3 to go to idle state and stop IME3 clock               */
  /*  2  VDMA  Clock control of VDMA                                          */
  /*    0: Exit idle state and start VDMA clock                               */
  /*    1: Request VDMA to go to idle state and stop VDMA clock               */
  /*  1  ICONT2  Clock control of ICONT2                                      */
  /*    0: Exit idle state and start ICONT2 clock                             */
  /*    1: Request ICONT2 to go to idle state and stop ICONT2 clock           */
  /*  0  ICONT1  Clock control of ICONT1                                      */
  /*    0: Exit idle state and start ICONT1 clock                             */
  /*    1: Request ICONT1 to go to idle state and stop ICONT1 clock           */
  /*                                                                          */
  /*--------------------------------------------------------------------------*/
  
  /*--------------------------------------------------------------------------*/
  /* Here we DONT enable for following IPs                                    */
  /* IME3 (3), IPE3(6)                                                        */
  /* If SMSET trace is needed for debugging we need to make the bit 10 to 0   */
  /*--------------------------------------------------------------------------*/
  volatile int status; 
  XDAS_UInt32 clock_cntl = 0x00000048; /*See bit defs above*/
  XDAS_UInt32 timeOutCounter = 1000;

  *((XDAS_UInt32 *)(regBaseAddr + SYS_CLKCTRL_OFFSET)) = clock_cntl;

  status = *((XDAS_UInt32 *)(regBaseAddr + SYS_CLKSTATUS_OFFSET));

  while((((~(status)) & 0x7FF) != clock_cntl) && 
       (timeOutCounter > 0))
  {
    timeOutCounter--;
  }
  
  if(timeOutCounter == 0)
  {
    return APP_EFAIL;
  }

  return APP_EOK;
}
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
XDAS_UInt32 TestApp_turnOffClocks()
{
  XDAS_UInt32 regBaseAddr = (XDAS_UInt32)regBaseAdderss[appIvahdId]; 

  volatile int status; 
  XDAS_UInt32 timeOutCounter = 1000;
  XDAS_UInt32 clockCntl;                              

  clockCntl                   = 0x000003F8;

  *((XDAS_UInt32 *)(regBaseAddr + SYS_CLKCTRL_OFFSET)) = clockCntl;

  do{
    status = *((XDAS_UInt32 *)(regBaseAddr + SYS_CLKSTATUS_OFFSET));
    timeOutCounter --;
  }while ((status !=  ((~clockCntl) & 0x7FF) ) && (timeOutCounter > 0));
  
  if(timeOutCounter == 0)
  {
    return APP_EFAIL;
  }

  return APP_EOK;
}
#endif

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
XDAS_Void IVAHD_Standby_power_on_uboot(XDAS_UInt32 IVAHD_CONFIG_REG_BASE,
                                      XDAS_UInt32 PRCM_IVAHD_ICONT_RST_CNTL_ADDR
                                       )
{
  unsigned int length =0;

  /*--------------------------------------------------------------------------*/
  /* Assigment of pointers                                                    */
  /* A generic code shall take all address as input parameters                */
  /*--------------------------------------------------------------------------*/ 
  volatile unsigned int *prcm_ivahd_icont_rst_cntl_addr =
              (unsigned int *)PRCM_IVAHD_ICONT_RST_CNTL_ADDR;
  volatile unsigned int *icont1_itcm_base_addr =
              (unsigned int *)(IVAHD_CONFIG_REG_BASE + ICONT1_ITCM_OFFSET);
  volatile unsigned int *icont2_itcm_base_addr =
              (unsigned int *)(IVAHD_CONFIG_REG_BASE + ICONT2_ITCM_OFFSET);
  /*--------------------------------------------------------------------------*/
  /* Set IVAHD in reset mode to enable downloading of boot code               */
  /* Please note that this state can be SKIPPED if IVAHD is alredy in reset   */
  /* state during uboot and reset is not de-asserted                          */
  /* Set bit0 to 1 to put ICONT1 in reset state                               */
  /* Set bit1 to 1 to put ICONT2 in reset state                               */
  /*--------------------------------------------------------------------------*/
#if defined(HOST_ARM9)
  *prcm_ivahd_icont_rst_cntl_addr &=  0xFFFFFFF3;
#else
  *prcm_ivahd_icont_rst_cntl_addr |=  0x00000003;
#endif

  /*--------------------------------------------------------------------------*/
  /* Copy boot code to ICONT1 & INCOT2 memory                                 */
  /*--------------------------------------------------------------------------*/
  for (length=0; length<LENGTH_BOOT_CODE; length++) {
    *icont1_itcm_base_addr++ = IVAHD_memory_wfi[length];
    *icont2_itcm_base_addr++ = IVAHD_memory_wfi[length];
  }
  /*--------------------------------------------------------------------------*/
  /* Take IVAHD out of reset mode.                                            */
  /* Set bit0 to 0 to take ICONT1 out of reset state                          */
  /* Set bit1 to 0 to take ICONT1 out of reset state                          */
  /* This implies ICONT inside IVAHD will exectute WFI                        */
  /*--------------------------------------------------------------------------*/
#if defined(HOST_ARM9)
  *prcm_ivahd_icont_rst_cntl_addr |=  0x0000000C;
#else
  *prcm_ivahd_icont_rst_cntl_addr &=  0xFFFFFFFC;
#endif

  /*--------------------------------------------------------------------------*/
  /* As ICONT goes in WFI and there are no pending VDMA transction            */
  /* entire IVAHD will be go in standby mode and PRCM will fully control      */
  /* further managment of IVAHD power state                                   */
  /*--------------------------------------------------------------------------*/

  return;
}

