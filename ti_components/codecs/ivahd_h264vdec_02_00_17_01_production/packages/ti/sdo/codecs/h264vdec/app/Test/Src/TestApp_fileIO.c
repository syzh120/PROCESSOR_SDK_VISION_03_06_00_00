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
 * @file <TestApp_fileIO.c>                          
 *                                       
 * @brief  This File contains file input\output interface functions to standard
 *         C library functions
 *  
 * @author: Ramakrishna Adireddy
 *
 * @version 0.0 (Jan 2010) : Base version created [Ramakrishna]
 * @version 0.2 (Jan 2010) : Code commenting and cleanup
 *                           [Ramakrishna]
 * @version 0.3 (May 2010) : Changes for output datasync
 *                           [Keshava Prasad]
 * @version 0.4 (Jun 2010) : Changes to support SEEK operation
 *                           [Keshava Prasad]
 * @version 0.5 (Jul 2010) : Code cleanup
 *                           [Ramakrishna]
 * @version 0.6 (June 2011)  :Added feature of dual yuv support in order dump 
 *                           dual yuv.
 *                           [Vijay Kumar Yadav] 

 ******************************************************************************
*/
/******************************************************************************
*  INCLUDE FILES                                                
******************************************************************************/
#include <xdc/std.h>
#include <TestAppDecoder.h>
#include <crc.h>
/**
 * Global variables needed for SEEK operation
*/
/*----------------------------------------------------------------------------*/
/*  Temporary buffer allocation used while separating chroma CB and CR for    */
/*  writing to file.                                                          */
/*----------------------------------------------------------------------------*/
XDAS_Int32   bitMismatchDetected   = 0;
XDAS_UInt8   paramsFile[STRING_SIZE];

/*----------------------------------------------------------------------------*/
/*  Temporary buffer allocation used while separating chroma CB and CR for    */
/*  writing to file.                                                          */
/*----------------------------------------------------------------------------*/
XDAS_Int8  Chroma_separate[DISPLAY_YUV_SIZE];

extern H264VDEC_Params    params;
extern H264VDEC_DynamicParams   dynamicParams;
extern sAppControlParams  appControlPrms;
extern XDAS_Int8          inputData[];
extern XDAS_UInt32        rowNum;
extern XDAS_Int8          numChannels;
extern FILE *fLogFile; 
extern FILE *fCycles; 
extern sChannelState nChannelState[NUM_DEC_CHANNELS_SUPPORTED];
/*----------------------------------------------------------------------------*/
/* Error strings which are mapped to codec errors                             */
/* Please refer User guide for more details on error strings                  */
/*----------------------------------------------------------------------------*/
static sEnumToStringMapping gErrorStrings[32] = 
{
  (XDAS_Int8 *)"IH264VDEC_ERR_NOSLICE : 0, \0",
  (XDAS_Int8 *)"IH264VDEC_ERR_SPS : 1,",
  (XDAS_Int8 *)"IH264VDEC_ERR_PPS : 2,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_SLICEHDR : 3,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_MBDATA : 4,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_UNAVAILABLESPS : 5,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_UNAVAILABLEPPS  : 6,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_INVALIDPARAM_IGNORE : 7\0",
  (XDAS_Int8 *)"XDM_PARAMSCHANGE : 8,\0",
  (XDAS_Int8 *)"XDM_APPLIEDCONCEALMENT : 9,\0",
  (XDAS_Int8 *)"XDM_INSUFFICIENTDATA : 10,\0",
  (XDAS_Int8 *)"XDM_CORRUPTEDDATA : 11,\0",
  (XDAS_Int8 *)"XDM_CORRUPTEDHEADER : 12,\0",
  (XDAS_Int8 *)"XDM_UNSUPPORTEDINPUT : 13,\0",
  (XDAS_Int8 *)"XDM_UNSUPPORTEDPARAM : 14,\0",
  (XDAS_Int8 *)"XDM_FATALERROR : 15\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_UNSUPPFEATURE : 16,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_METADATA_BUFOVERFLOW : 17,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_STREAM_END : 18,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_NO_FREEBUF : 19,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_PICSIZECHANGE : 20,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_UNSUPPRESOLUTION : 21,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_NUMREF_FRAMES : 22,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_INVALID_MBOX_MESSAGE : 23,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_DATA_SYNC : 24,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_MISSINGSLICE : 25,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_INPUT_DATASYNC_PARAMS : 26,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_HDVICP2_IMPROPER_STATE : 27,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_TEMPORAL_DIRECT_MODE : 28,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_DISPLAYWIDTH : 29,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_NOHEADER : 30,\0",
  (XDAS_Int8 *)"IH264VDEC_ERR_GAPSINFRAMENUM : 31, \0"
};

/** 
********************************************************************************
 *  @fn     TestApp_ReadByteStream
 *  @brief  The function is an Application function to read bitstream
 *
 *  @param[in] finFile  : Pointer to the Input bit-stream file to be read.
 *          
 *  @param[in] fsizeFile : Pointer to the frame size file.
 *          
 *  @param[in] bytesConsumed : The toal bytes consumbed by the codec till the
 *                             point of this function call.
 *          
 *  @return [out] BytesRead : The number of Bytes that read from file & to be
 *                             supplied to the codec.
 *  @return [in] chnlNum :    Decode channel number
 *                           
********************************************************************************
*/
XDAS_Int32  TestApp_ReadByteStream
(
    FILE      *finFile,
    FILE      *fsizeFile,
    XDAS_UInt32 bytesConsumed,
    XDAS_Int8   chnlNum
)
{
  XDAS_UInt32 BytesRead;
  XDAS_UInt32 frameSizeVal = 0;
  /*------------------------------------------------------------------------*/
  /* Open Input bitstream file                                              */
  /*------------------------------------------------------------------------*/
  finFile = my_fopen((const char *)nChannelState[chnlNum].appCntrlParams.inFile,
                "rb", ARG_FILEIO_TYPE);
  fprintf(stdout,"\n%s\n",nChannelState[chnlNum].appCntrlParams.inFile);
  if(!finFile)
  {
    printf("Couldn't open Input file...   %s\n", 
                        nChannelState[chnlNum].appCntrlParams.inFile);
    return APP_EFAIL;
  }
  /*--------------------------------------------------------------------------*/
  /* Check if the Bit stream reading mode is set to Frame Size mode           */
  /*--------------------------------------------------------------------------*/
  if(nChannelState[chnlNum].appCntrlParams.bitStreamMode == BS_FRAME_MODE)
  {
    /*------------------------------------------------------------------------*/
    /* Check for end of file                                                  */
    /*------------------------------------------------------------------------*/
    if(!feof(fsizeFile))
    {
      /*----------------------------------------------------------------------*/
      /* Read the Frame size value from the file which is holding all frames  */
      /* sizes.                                                               */
      /*----------------------------------------------------------------------*/
      fscanf (fsizeFile,"%ld", &frameSizeVal) ;      

      /*----------------------------------------------------------------------*/
      /* In case of very first frame we need to seek the file pointer to the  */
      /* very begining of the file. Otherwise, need to seek to the location   */
      /* that is correspond to current frame.                                 */
      /*----------------------------------------------------------------------*/
      if(nChannelState[chnlNum].picture_count == 0)
      {
        nChannelState[chnlNum].frameSizeOffset = 0;
        my_fseek(finFile, 0, SEEK_SET, ARG_FILEIO_TYPE) ;
      }
#ifdef TEST_SEEK_OP
      else if(nChannelState[chnlNum].SeekBackwd)
      {
        XDAS_UInt32 frmIdxCntr;

        nChannelState[chnlNum].frameSizeOffset = 0;
        my_fseek(finFile, 0, SEEK_SET, ARG_FILEIO_TYPE) ;
        fseek (fsizeFile, 0, SEEK_SET) ;      

        for(frmIdxCntr = 0; frmIdxCntr < nChannelState[chnlNum].frameCount; 
            frmIdxCntr++)
        {
          fscanf (fsizeFile,"%ld", &frameSizeVal);
          nChannelState[chnlNum].frameSizeOffset += frameSizeVal;
        }
        my_fseek(finFile, nChannelState[chnlNum].frameSizeOffset, SEEK_SET, 
            ARG_FILEIO_TYPE); 
        nChannelState[chnlNum].frameSizeOffset -= frameSizeVal;
      }
#endif
      else
      {
        my_fseek(finFile, nChannelState[chnlNum].frameSizeOffset, SEEK_SET, 
            ARG_FILEIO_TYPE); 
      }

      /*----------------------------------------------------------------------*/
      /* In case both the offset & frame size are zero, return with failure.  */
      /* It means the input file is of zero size or frame size file is wrong. */
      /*----------------------------------------------------------------------*/
      if (nChannelState[chnlNum].frameSizeOffset == 0 && frameSizeVal == 0)
      { 
        my_fclose(finFile, ARG_FILEIO_TYPE);
        return -1;
      }

#ifdef TEST_SEEK_OP
      if(nChannelState[chnlNum].SeekOpStart && 
            (!nChannelState[chnlNum].SeekBackwd))
      {
        BytesRead = frameSizeVal;
      }
      else
#endif
      {
        /*--------------------------------------------------------------------*/
        /* Read the bytes from Bit stream file to Input buffer.               */
        /*--------------------------------------------------------------------*/
        BytesRead  = my_fread((void *)nChannelState[chnlNum].bitStreamData, 
                1, frameSizeVal, finFile, ARG_FILEIO_TYPE);
      }

      /*----------------------------------------------------------------------*/
      /* Update the Frame Size offset with the newly read value/bytes.        */
      /*----------------------------------------------------------------------*/
      nChannelState[chnlNum].frameSizeOffset += frameSizeVal;

      /*----------------------------------------------------------------------*/
      /* Determine end-of-file condition                                      */
      /*----------------------------------------------------------------------*/
      if (BytesRead != frameSizeVal)
      {
        nChannelState[chnlNum].streamEnd = 1;
        my_fclose(finFile, ARG_FILEIO_TYPE);
        return -1;
      }
      my_fclose(finFile, ARG_FILEIO_TYPE);   
      /*----------------------------------------------------------------------*/
      /* Return total bytes available for further decoding                    */
      /*----------------------------------------------------------------------*/
      return (BytesRead);
    }
    else
    {
      my_fclose(finFile, ARG_FILEIO_TYPE);
      nChannelState[chnlNum].streamEnd = 1;
      return 0;
    }
  }
  /*--------------------------------------------------------------------------*/
  /* Bit stream reading mode is Buffer Full read mode.                        */
  /*--------------------------------------------------------------------------*/
  else
  {
    
    my_fseek(finFile, bytesConsumed, SEEK_SET, ARG_FILEIO_TYPE);
    BytesRead = my_fread((void *)nChannelState[chnlNum].bitStreamData, 1, 
        ((INPUT_BUFFER_SIZE/numChannels) - 1), finFile, ARG_FILEIO_TYPE);
    my_fclose(finFile, ARG_FILEIO_TYPE);

    return (BytesRead);
  }
} /* TestApp_ReadByteStream() */

/** 
********************************************************************************
 *  @fn     TestApp_WriteOutputData
 *  @brief  The function is an Application function to write output data 
 *          to a file.
 *
 *  @param[in] fOutFile : Pointer to output file.
 *          
 *  @param[in] outArgs  : Pointer to outargs. These args filled in process call.
 *          
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
  XDAS_Int8         complianceMode,
  XDAS_Int8         crcEnable,
  XDAS_Int8         chnlNum
)
{
  XDAS_Int16      width, height, paddedheight;
  XDAS_Int16      xOffset, yOffset;
  IVIDEO2_BufDesc *displayBufs;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

#ifdef OUTPUTDS_DUMP
  if(nChannelState[chnlNum].appCntrlParams.outDataSync)
  {
    IVIDEO2_BufDesc *decodedBufs;

    decodedBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.decodedBufs;

    height = decodedBufs->activeFrameRegion.bottomRight.y - 
             decodedBufs->activeFrameRegion.topLeft.y;

    width  = decodedBufs->activeFrameRegion.bottomRight.x - 
             decodedBufs->activeFrameRegion.topLeft.x;

    my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(Uint8), 
                (((width*height)*3)>>1), fOutFile, ARG_FILEIO_TYPE);
  }
  else
#endif
  {
    /*------------------------------------------------------------------------*/
    /*  Pointer to Display buffer structure                                   */
    /*------------------------------------------------------------------------*/
    if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
    {
      displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                        pBufDesc[dualOutputFlag];
    }
    else
    {
      displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                        displayBufs.bufDesc[0];
    }

    paddedheight = displayBufs->imageRegion.bottomRight.y + 
                     displayBufs->imageRegion.topLeft.y;

    xOffset = displayBufs->activeFrameRegion.topLeft.x;
    yOffset = displayBufs->activeFrameRegion.topLeft.y;

    height  = displayBufs->activeFrameRegion.bottomRight.y - yOffset;
    width   = displayBufs->activeFrameRegion.bottomRight.x - xOffset;

    /*------------------------------------------------------------------------*/
    /* contentType indicates if the frame was stored as field or not.         */
    /* contentType :0 , frame storage                                         */
    /*   otherwise, it is field storage                                       */
    /*------------------------------------------------------------------------*/
    if(displayBufs->contentType == IVIDEO_PROGRESSIVE)
    {
      /*----------------------------------------------------------------------*/
      /*     Progressive frame Storage.                                       */
      /*----------------------------------------------------------------------*/
      outputDisplayFrame(outArgs, xOffset, yOffset, paddedheight, width, 
                height, complianceMode,crcEnable,fOutFile,chnlNum);
    }
    else
    {
      /*----------------------------------------------------------------------*/
      /* The frame is stored as 2 fields. So top and bottom fields have to    */
      /* be interleaved. The interleaving is done in                          */
      /* nChannelState[chnlNum].fieldBuf and is then written out              */
      /*----------------------------------------------------------------------*/

      /*----------------------------------------------------------------------*/
      /* Double the paddedheight and height dimensions for two fields         */
      /*----------------------------------------------------------------------*/
      paddedheight <<= 1;
      height       <<= 1;

      /*----------------------------------------------------------------------*/
      /*     Write Top and Bottom field                                       */
      /*----------------------------------------------------------------------*/
      outputDisplayField(outArgs, xOffset, yOffset, paddedheight, width, 
                height, complianceMode,crcEnable,fOutFile,chnlNum);
    }
  }
}
/** 
********************************************************************************
 *  @fn     TestApp_Write_DualOutputData
 *  @brief  The function is an Application function to write Dual output data 
 *          to a file.
 *
 *  @param[in] fDualoutFile : Pointer to dualoutput file.
 *          
 *  @param[in] outArgs  : Pointer to outargs. These args filled in process call.
 *          
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
  XDAS_Int8         complianceMode,
  XDAS_Int8         crcEnable,
  XDAS_Int8         chnlNum
)
{
  XDAS_Int16      width, height, paddedheight;
  XDAS_Int16      xOffset, yOffset;
  IVIDEO2_BufDesc *displayBufs;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

#ifdef OUTPUTDS_DUMP
  if(nChannelState[chnlNum].appCntrlParams.outDataSync)
  {
    IVIDEO2_BufDesc *decodedBufs;

    decodedBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.decodedBufs;

    height = decodedBufs->activeFrameRegion.bottomRight.y - 
             decodedBufs->activeFrameRegion.topLeft.y;

    width  = decodedBufs->activeFrameRegion.bottomRight.x - 
             decodedBufs->activeFrameRegion.topLeft.x;

    my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(Uint8), 
            (((width*height)*3)>>1), fDualoutFile, ARG_FILEIO_TYPE);
  }
  else
#endif
  {
    /*------------------------------------------------------------------------*/
    /*  Pointer to Display buffer structure                                   */
    /*------------------------------------------------------------------------*/
    if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
    {
      displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                    pBufDesc[!dualOutputFlag];
    }
    else
    {
      displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                       displayBufs.bufDesc[0];
    }

    paddedheight = displayBufs->imageRegion.bottomRight.y + 
                     displayBufs->imageRegion.topLeft.y;

    xOffset = displayBufs->activeFrameRegion.topLeft.x;
    yOffset = displayBufs->activeFrameRegion.topLeft.y;

    height  = displayBufs->activeFrameRegion.bottomRight.y - yOffset;
    width   = displayBufs->activeFrameRegion.bottomRight.x - xOffset;

    /*------------------------------------------------------------------------*/
    /* If enableDualOutput flag value is 2, then the dual output destination  */
    /* address in VDMA recon decsriptors have been shifted by 4 bytes for     */
    /* alignment/DDR bandwidth optimization. So, on the application side the  */
    /* output has to be shifted by 4 bytes.                                   */
    /*------------------------------------------------------------------------*/
    if(nChannelState[chnlNum].params.enableDualOutput == 
                                          IH264VDEC_DUALOUTPUTALIGN_ENABLE)
      xOffset += 4;
    /*------------------------------------------------------------------------*/
    /* contentType indicates if the frame was stored as field or not.         */
    /* contentType :0 , frame storage                                         */
    /*   otherwise, it is field storage                                       */
    /*------------------------------------------------------------------------*/
    if(displayBufs->contentType == IVIDEO_PROGRESSIVE)
    {
      /*----------------------------------------------------------------------*/
      /*     Progressive frame Storage.                                       */
      /*----------------------------------------------------------------------*/
      outputDisplayFrame_dual(fDualoutFile,outArgs, xOffset, yOffset, 
              paddedheight, width, height, complianceMode,crcEnable,chnlNum);
    }
    else
    {
      /*----------------------------------------------------------------------*/
      /* The frame is stored as 2 fields. So top and bottom fields have to    */
      /* be interleaved. The interleaving is done in                          */
      /* nChannelState[chnlNum].fieldBuf and is then written out              */
      /*----------------------------------------------------------------------*/

      /*----------------------------------------------------------------------*/
      /* Double the paddedheight and height dimensions for two fields         */
      /*----------------------------------------------------------------------*/
      paddedheight <<= 1;
      height       <<= 1;

      /*----------------------------------------------------------------------*/
      /*     Write Top and Bottom field                                       */
      /*----------------------------------------------------------------------*/
      outputDisplayField_Dual(fDualoutFile,outArgs, xOffset, yOffset, 
            paddedheight, width, height, complianceMode,crcEnable,chnlNum);
    }
  }
}

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
 *  @param[in] fOutFile : Pointer to output file.
 *          
 *  @return none
********************************************************************************
*/
XDAS_Void outputDisplayFrame( H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff, 
                               XDAS_Int16 yoff, XDAS_Int16 ref_height, 
                               XDAS_Int16 width, XDAS_Int16 height, 
                               XDAS_Int8 complianceMode, XDAS_Int8  crcEnable,
                               FILE *fout,
                               XDAS_Int8 chnlNum
)
{
  char *lumaAddr;
  XDAS_Int16 *chromaAddr;
  IVIDEO2_BufDesc *displayBufs;
  XDAS_UInt32  pic_size;
  XDAS_UInt16 ref_width;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

#ifndef DUMP_WITHPADDING

  {
  char *CbBuf, *CrBuf, *YBuf;
  XDAS_UInt32 i, j;
  XDAS_UInt16 ref_width_c;

  if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                            pBufDesc[dualOutputFlag];
  }
  else
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                    displayBufs.bufDesc[0];
  }

  /*--------------------------------------------------------------------------*/
  /* Get the stride for both Luma & Chroma buffers                            */
  /*--------------------------------------------------------------------------*/
  ref_width   = displayBufs->imagePitch[0];
  ref_width_c = displayBufs->imagePitch[1];

  pic_size = width * height;

  lumaAddr   = (char *)((XDAS_Int32)displayBufs->planeDesc[0].buf + 
               (yoff * ref_width) + xoff);

  chromaAddr = (XDAS_Int16 *)((XDAS_Int32)displayBufs->planeDesc[1].buf +  
               ((yoff>>1) * ref_width_c) + xoff);

  if(displayBufs->frameStatus != IVIDEO_FRAME_OUTPUTSKIP)
  {
    YBuf = (char *)nChannelState[chnlNum].fieldBuf;

    for(i=0 ; i < height ; i++)
    {
      memcpy(YBuf, lumaAddr, width);
      YBuf      += width;
      lumaAddr  += ref_width;
    }

    if(displayBufs->chromaFormat != XDM_GRAY)
    {
      CbBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size);
      CrBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size + 
                    (pic_size>>2));

      for(i=0 ; i<(height>>1) ; i++)
      {
        for(j=0 ; j<(width>>1) ; j++)
        {
          CbBuf[j] = (chromaAddr[j] & 0x00FF);
          CrBuf[j] = (chromaAddr[j] >> 8) & 0x00FF;
        }

        CbBuf      += (width>>1);
        CrBuf      += (width>>1);
        chromaAddr += (ref_width_c >> 1);
      }
    }
  }
  else
  {
    memset((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
                                            ((pic_size * 3) >> 1));
  }

  if(!complianceMode)
  {
    if(!crcEnable)
    {
      if(displayBufs->chromaFormat == XDM_GRAY)
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
                  pic_size, fout, ARG_FILEIO_TYPE);
      }
      else
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
                  ((pic_size * 3) >> 1), fout, ARG_FILEIO_TYPE);
      }
    }
    else
    {
      unsigned char *fieldBuf_Luma = 
                    (unsigned char *)nChannelState[chnlNum].fieldBuf;
      unsigned char *fieldBuf_Cb;
      unsigned char *fieldBuf_Cr;
      XDAS_UInt32 dataCRC[3];
      /*---------------------------------------------------------------------*/
      /* Generate the CRC value of Luma for the output yuv                   */
      /*---------------------------------------------------------------------*/
      crcInit();
      dataCRC[0] = crcFast(fieldBuf_Luma, pic_size);

      /*---------------------------------------------------------------------*/
      /* Generate the CRC value of Cb for the output yuv                     */
      /*---------------------------------------------------------------------*/
      fieldBuf_Cb = fieldBuf_Luma + pic_size;
      crcInit();
      dataCRC[1] = crcFast(fieldBuf_Cb, pic_size>>2);

      /*---------------------------------------------------------------------*/
      /* Generate the CRC value of Cr for the output yuv                     */
      /*---------------------------------------------------------------------*/
      fieldBuf_Cr = fieldBuf_Cb + (pic_size >> 2);
      crcInit();
      dataCRC[2] = crcFast(fieldBuf_Cr, pic_size>>2);
      /*----------------------------------------------------------------------*/
      /* Write the CRC value to the Output file                               */
      /*----------------------------------------------------------------------*/
      my_fwrite ((void *)&dataCRC[0], sizeof(XDAS_UInt32), 3, 
                 fout, ARG_FILEIO_TYPE);
    }
  }
  }

#else /* DUMP_WITHPADDING */

  {
    /*------------------------------------------------------------------------*/
    /* Here the frame data (with padding) dumped.                             */
    /* Also UV is interleaved.                                                */
    /* Need to use an off-line utility later.                                 */
    /*------------------------------------------------------------------------*/

    if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
                IVIDDEC3_DISPLAYBUFS_PTRS)
    {
      displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                    pBufDesc[dualOutputFlag];
    }
    else
    {
      displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                    displayBufs.bufDesc[0];
    }

    ref_width   = displayBufs->imagePitch[0];
    pic_size   = ref_width * ref_height;
    lumaAddr   = (char *)displayBufs->planeDesc[0].buf;
    chromaAddr = (XDAS_Int16 *)displayBufs->planeDesc[1].buf;

    if(!complianceMode)
    {
      my_fwrite((void *)lumaAddr, sizeof(char), pic_size, fout,
                ARG_FILEIO_TYPE);
#ifdef USE_HOST_FILE_IO
      my_fwrite((void *)chromaAddr, sizeof(char), (pic_size>>1), 
                fout, ARG_FILEIO_TYPE);
#else
      my_fwrite((void *)chromaAddr, sizeof(XDAS_Int16), (pic_size>>2), 
                fout, ARG_FILEIO_TYPE);
#endif
    }
  }
#endif /* DUMP_WITHPADDING */

}
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


XDAS_Void outputDisplayFrame_dual( FILE *fout, H264VDEC_OutArgs *outArgs, 
                               XDAS_Int16 xoff, 
                               XDAS_Int16 yoff, XDAS_Int16 ref_height, 
                               XDAS_Int16 width, XDAS_Int16 height, 
                               XDAS_Int8 complianceMode, XDAS_Int8  crcEnable,
                               XDAS_Int8 chnlNum
                             )
{
  char *lumaAddr;
  XDAS_Int16 *chromaAddr;
  IVIDEO2_BufDesc *displayBufs;
  XDAS_UInt32  pic_size;
  XDAS_UInt16 ref_width;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

#ifndef DUMP_WITHPADDING

  {
  char *CbBuf, *CrBuf, *YBuf;
  XDAS_UInt32 i, j;
  XDAS_UInt16 ref_width_c;

  if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                pBufDesc[!dualOutputFlag];
  }
  else
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                        displayBufs.bufDesc[0];
  }

  /*--------------------------------------------------------------------------*/
  /* Get the stride for both Luma & Chroma buffers                            */
  /*--------------------------------------------------------------------------*/
  ref_width   = displayBufs->imagePitch[0];
  ref_width_c = displayBufs->imagePitch[1];

  pic_size = width * height;

  lumaAddr   = (char *)((XDAS_Int32)displayBufs->planeDesc[0].buf + 
               (yoff * ref_width) + xoff);

  chromaAddr = (XDAS_Int16 *)((XDAS_Int32)displayBufs->planeDesc[1].buf +  
               ((yoff>>1) * ref_width_c) + xoff);

  if(displayBufs->frameStatus != IVIDEO_FRAME_OUTPUTSKIP)
  {
    YBuf = (char *)nChannelState[chnlNum].fieldBuf;

    for(i=0 ; i<height ; i++)
    {
      memcpy(YBuf, lumaAddr, width);
      YBuf      += width;
      lumaAddr  += ref_width;
    }

    if(displayBufs->chromaFormat != XDM_GRAY)
    {
      CbBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size);
      CrBuf = 
        (char *)(nChannelState[chnlNum].fieldBuf + pic_size + (pic_size>>2));

      for(i=0 ; i<(height>>1) ; i++)
      {
        for(j=0 ; j<(width>>1) ; j++)
        {
          CbBuf[j] = (chromaAddr[j] & 0x00FF);
          CrBuf[j] = (chromaAddr[j] >> 8) & 0x00FF;
        }

        CbBuf      += (width>>1);
        CrBuf      += (width>>1);
        chromaAddr += (ref_width_c >> 1);
      }
    }
  }
  else
  {
    memset((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
            ((pic_size * 3) >> 1));
  }

  if(!complianceMode)
  {
    if(!crcEnable)
    {
      if(displayBufs->chromaFormat == XDM_GRAY)
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
                  pic_size, fout, ARG_FILEIO_TYPE);
      }
      else
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char),
                  ((pic_size * 3)>> 1), fout, ARG_FILEIO_TYPE);
      }
    }
    else
    {
      unsigned char *fieldBuf_Luma = 
            (unsigned char *)nChannelState[chnlNum].fieldBuf;
      unsigned char *fieldBuf_Cb;
      unsigned char *fieldBuf_Cr;
      XDAS_UInt32 dataCRC[3];
      /*---------------------------------------------------------------------*/
      /* Generate the CRC value of Luma for the output yuv                   */
      /*---------------------------------------------------------------------*/
      crcInit();
      dataCRC[0] = crcFast(fieldBuf_Luma, pic_size);

      /*---------------------------------------------------------------------*/
      /* Generate the CRC value of Cb for the output yuv                     */
      /*---------------------------------------------------------------------*/
      fieldBuf_Cb = fieldBuf_Luma + pic_size;
      crcInit();
      dataCRC[1] = crcFast(fieldBuf_Cb, pic_size>>2);

      /*---------------------------------------------------------------------*/
      /* Generate the CRC value of Cr for the output yuv                     */
      /*---------------------------------------------------------------------*/
      fieldBuf_Cr = fieldBuf_Cb + (pic_size >> 2);
      crcInit();
      dataCRC[2] = crcFast(fieldBuf_Cr, pic_size>>2);
      /*----------------------------------------------------------------------*/
      /* Write the CRC value to the Output file                               */
      /*----------------------------------------------------------------------*/
      my_fwrite ((void *)&dataCRC[0], sizeof(XDAS_UInt32), 3, 
                 fout, ARG_FILEIO_TYPE);
    }
  }
  }
#else /* DUMP_WITHPADDING */

  {
    /*------------------------------------------------------------------------*/
    /* Here the frame data (with padding) dumped.                             */
    /* Also UV is interleaved.                                                */
    /* Need to use an off-line utility later.                                 */
    /*------------------------------------------------------------------------*/

    if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
    {
      displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                    pBufDesc[!dualOutputFlag];
    }
    else
    {
      displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                        displayBufs.bufDesc[1];
    }

    ref_width   = displayBufs->imagePitch[0];
    pic_size   = ref_width * ref_height;
    lumaAddr   = (char *)displayBufs->planeDesc[0].buf;
    chromaAddr = (XDAS_Int16 *)displayBufs->planeDesc[1].buf;

    if(!complianceMode)
    {
      my_fwrite((void *)lumaAddr, sizeof(char), pic_size, fout,
                ARG_FILEIO_TYPE);
#ifdef USE_HOST_FILE_IO
      my_fwrite((void *)chromaAddr, sizeof(char), (pic_size>>1), 
                fout, ARG_FILEIO_TYPE);
#else
      my_fwrite((void *)chromaAddr, sizeof(XDAS_Int16), (pic_size>>2), 
                fout, ARG_FILEIO_TYPE);
#endif
    }
  }
#endif /* DUMP_WITHPADDING */

}

/** 
********************************************************************************
 *  @fn     outputDisplayField
 *  @brief  The function is Sub  Function to interleave 2 fields.
 *           In case of interlaced or PICAFF streams, the frame is stored as
 *           2 separate field. This function is used to interleaved the 2 fields
 *           and form the frame.The interleaving is done in fieldBuf and is then 
 *           written out.
 *
 *  @param[in] fout  : File pointer to dual output.
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
XDAS_Void outputDisplayField(H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff, 
                             XDAS_Int16 yoff, XDAS_Int16 ref_height, 
                             XDAS_Int16 width, XDAS_Int16 height, 
                             XDAS_Int8 complianceMode, XDAS_Int8 crcEnable,
                             FILE *fout,
                             XDAS_Int8 chnlNum
                             )
{
  IVIDEO2_BufDesc *displayBufs;
  char *lumaAddr1, *lumaAddr2;
  XDAS_Int16 *chromaAddr1, *chromaAddr2;
  char *CbBuf, *CrBuf, *YBuf;
  XDAS_UInt32 pic_size;
  XDAS_UInt16  ref_width;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

#ifndef DUMP_WITHPADDING

  {
  XDAS_UInt32  i, j;
  XDAS_Int32  fieldSizeY;
  XDAS_Int32  fieldSizeCbCr;
  XDAS_UInt16  ref_width_c;

  if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
    IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                    pBufDesc[dualOutputFlag];
  }
  else
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                    displayBufs.bufDesc[0];
  }

  /*--------------------------------------------------------------------------*/
  /* Get the stride for both Luma & Chroma buffers                            */
  /*--------------------------------------------------------------------------*/
  ref_width   = displayBufs->imagePitch[0];
  ref_width_c = displayBufs->imagePitch[1];

  fieldSizeY    = (ref_width*ref_height)>>1;
  fieldSizeCbCr = (ref_width_c*ref_height)>>2;

  pic_size = width * height;

  lumaAddr1   = (char *)((XDAS_Int32)displayBufs->planeDesc[0].buf + 
                (yoff * ref_width) + xoff);

  chromaAddr1 = (XDAS_Int16 *)((XDAS_Int32)displayBufs->planeDesc[1].buf + 
                ((yoff>>1) * ref_width_c) + xoff);

  lumaAddr2   = lumaAddr1   + fieldSizeY;
  chromaAddr2 = chromaAddr1 + (fieldSizeCbCr >> 1);

  if(displayBufs->frameStatus != IVIDEO_FRAME_OUTPUTSKIP)
  {
    YBuf = (char *)nChannelState[chnlNum].fieldBuf;
    
    for(i=0 ; i < (height >> 1) ; i++)
    {
      memcpy(YBuf, lumaAddr1, width);
      YBuf      += width;
      lumaAddr1 += ref_width;
      memcpy(YBuf, lumaAddr2, width);
      YBuf      += width;
      lumaAddr2 += ref_width;
    }

    if(displayBufs->chromaFormat != XDM_GRAY)
    {
      CbBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size);
      CrBuf = 
        (char *)(nChannelState[chnlNum].fieldBuf + pic_size + (pic_size>>2));

      for(i=0 ; i<(height>>2) ; i++)
      {
        for(j=0 ; j<(width>>1) ; j++)
        {
          CbBuf[j] = (chromaAddr1[j] & 0x00FF);
          CrBuf[j] = (chromaAddr1[j] >> 8) & 0x00FF;
        }
        CbBuf    += (width>>1);
        CrBuf    += (width>>1);
        chromaAddr1 += (ref_width_c >> 1);

        for(j=0 ; j<(width>>1) ; j++)
        {
          CbBuf[j] = (chromaAddr2[j] & 0x00FF);
          CrBuf[j] = (chromaAddr2[j] >> 8) & 0x00FF;
        }
        CbBuf    += (width>>1);
        CrBuf    += (width>>1);
        chromaAddr2 += (ref_width_c >> 1);
      }
    }
  }
  else
  {
    memset((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
            ((pic_size*3)>>1));
  }

  if(!complianceMode)
  {
    if(!crcEnable)
    {
      if(displayBufs->chromaFormat == XDM_GRAY)
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
              pic_size,fout,ARG_FILEIO_TYPE);
      }
      else
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
                  ((pic_size*3)>>1), fout, ARG_FILEIO_TYPE);
      }
    }
    else
    {
      unsigned char *fieldBuf_Luma = 
            (unsigned char *)nChannelState[chnlNum].fieldBuf;
      unsigned char *fieldBuf_Cb;
      unsigned char *fieldBuf_Cr;
      XDAS_UInt32 dataCRC[3];
      /*----------------------------------------------------------------------*/
      /* Generate the CRC value of Luma for the output yuv                    */
      /*----------------------------------------------------------------------*/
      crcInit();
      dataCRC[0] = crcFast(fieldBuf_Luma, pic_size);

      /*----------------------------------------------------------------------*/
      /* Generate the CRC value of Cb for the output yuv                      */
      /*----------------------------------------------------------------------*/
      fieldBuf_Cb = fieldBuf_Luma + pic_size;
      crcInit();
      dataCRC[1] = crcFast(fieldBuf_Cb, pic_size>>2);

      /*----------------------------------------------------------------------*/
      /* Generate the CRC value of Cr for the output yuv                      */
      /*----------------------------------------------------------------------*/
      fieldBuf_Cr = fieldBuf_Cb + (pic_size >> 2);
      crcInit();
      dataCRC[2] = crcFast(fieldBuf_Cr, pic_size>>2);
      /*----------------------------------------------------------------------*/
      /* Write the CRC value to the Output file                               */
      /*----------------------------------------------------------------------*/
      my_fwrite ((void *)&dataCRC[0], sizeof(XDAS_UInt32), 3, 
                 fout, ARG_FILEIO_TYPE);
    }
  }
  }
#else /* DUMP_WITHPADDING */
  {
    /*------------------------------------------------------------------------*/
    /* Here the frame data (with padding) dumped.                             */
    /* Also UV is interleaved.                                                */
    /* Top and Bottom fields are not interleaved.                             */
    /* Need to use an off-line utility later.                                 */
    /*------------------------------------------------------------------------*/

    if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
            IVIDDEC3_DISPLAYBUFS_PTRS)
    {
      displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                    pBufDesc[dualOutputFlag];
    }
    else
    {
      displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                        displayBufs.bufDesc[0];
    }

    ref_width   = displayBufs->imagePitch[0];
    lumaAddr1    = (char *)displayBufs->planeDesc[0].buf;
    chromaAddr1  = (XDAS_Int16 *)displayBufs->planeDesc[1].buf;

    pic_size = ref_width * ref_height;

    if(!complianceMode)
    {
      my_fwrite((void *)lumaAddr1, sizeof(char), 
              pic_size,fout, ARG_FILEIO_TYPE);
#ifdef USE_HOST_FILE_IO
      my_fwrite((void *)chromaAddr1, sizeof(char), (pic_size>>1),
                fout, ARG_FILEIO_TYPE);
#else
      my_fwrite((void *)chromaAddr1, sizeof(XDAS_Int16), (pic_size>>2), 
                fout, ARG_FILEIO_TYPE);
#endif
    }
  }
#endif /* DUMP_WITHPADDING */

}

/** 
********************************************************************************
 *  @fn     outputDisplayField_Dual
 *  @brief  The function is Sub  Function to interleave 2 fields for dual o/p.
 *           In case of interlaced or PICAFF streams, the frame is stored as
 *           2 separate field. This function is used to interleaved the 2 fields
 *           and form the frame.The interleaving is done in fieldBuf and is then 
 *           written out.
 *
 *  @param[in] fout  : File pointer to dual output.
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
XDAS_Void outputDisplayField_Dual(FILE *fout, H264VDEC_OutArgs *outArgs, 
                                  XDAS_Int16 xoff, 
                                  XDAS_Int16 yoff, XDAS_Int16 ref_height, 
                                  XDAS_Int16 width, XDAS_Int16 height, 
                                  XDAS_Int8 complianceMode, XDAS_Int8 crcEnable,
                                  XDAS_Int8 chnlNum
                                  )
{
  IVIDEO2_BufDesc *displayBufs;
  char *lumaAddr1, *lumaAddr2;
  XDAS_Int16 *chromaAddr1, *chromaAddr2;
  char *CbBuf, *CrBuf, *YBuf;
  XDAS_UInt32 pic_size;
  XDAS_UInt16  ref_width;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

#ifndef DUMP_WITHPADDING

  {
  XDAS_UInt32  i, j;
  XDAS_Int32  fieldSizeY;
  XDAS_Int32  fieldSizeCbCr;
  XDAS_UInt16  ref_width_c;

  if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                    pBufDesc[!dualOutputFlag];
  }
  else
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                    displayBufs.bufDesc[0];
  }

  /*--------------------------------------------------------------------------*/
  /* Get the stride for both Luma & Chroma buffers                            */
  /*--------------------------------------------------------------------------*/
  ref_width   = displayBufs->imagePitch[0];
  ref_width_c = displayBufs->imagePitch[1];

  fieldSizeY    = (ref_width*ref_height)>>1;
  fieldSizeCbCr = (ref_width_c*ref_height)>>2;

  pic_size = width * height;

  lumaAddr1   = (char *)((XDAS_Int32)displayBufs->planeDesc[0].buf + 
                (yoff * ref_width) + xoff);

  chromaAddr1 = (XDAS_Int16 *)((XDAS_Int32)displayBufs->planeDesc[1].buf + 
                ((yoff>>1) * ref_width_c) + xoff);

  lumaAddr2   = lumaAddr1   + fieldSizeY;
  chromaAddr2 = chromaAddr1 + (fieldSizeCbCr >> 1);

  if(displayBufs->frameStatus != IVIDEO_FRAME_OUTPUTSKIP)
  {
    YBuf = (char *)nChannelState[chnlNum].fieldBuf;
    
    for(i=0 ; i < (height >> 1) ; i++)
    {
      memcpy(YBuf, lumaAddr1, width);
      YBuf      += width;
      lumaAddr1 += ref_width;
      memcpy(YBuf, lumaAddr2, width);
      YBuf      += width;
      lumaAddr2 += ref_width;
    }

    if(displayBufs->chromaFormat != XDM_GRAY)
    {
      CbBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size);
      CrBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size + 
                        (pic_size>>2));

      for(i=0 ; i<(height>>2) ; i++)
      {
        for(j=0 ; j<(width>>1) ; j++)
        {
          CbBuf[j] = (chromaAddr1[j] & 0x00FF);
          CrBuf[j] = (chromaAddr1[j] >> 8) & 0x00FF;
        }
        CbBuf    += (width>>1);
        CrBuf    += (width>>1);
        chromaAddr1 += (ref_width_c >> 1);

        for(j=0 ; j<(width>>1) ; j++)
        {
          CbBuf[j] = (chromaAddr2[j] & 0x00FF);
          CrBuf[j] = (chromaAddr2[j] >> 8) & 0x00FF;
        }
        CbBuf    += (width>>1);
        CrBuf    += (width>>1);
        chromaAddr2 += (ref_width_c >> 1);
      }
    }
  }
  else
  {
    memset((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
            ((pic_size*3)>>1));
  }

  if(!complianceMode)
  {
    if(!crcEnable)
    {
      if(displayBufs->chromaFormat == XDM_GRAY)
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
              pic_size,fout,ARG_FILEIO_TYPE);
      }
      else
      {
        my_fwrite((void *)nChannelState[chnlNum].fieldBuf, sizeof(char), 
                  ((pic_size*3)>>1), fout, ARG_FILEIO_TYPE);
      }
    }
    else
    {
      unsigned char *fieldBuf_Luma = 
                (unsigned char *)nChannelState[chnlNum].fieldBuf;
      unsigned char *fieldBuf_Cb;
      unsigned char *fieldBuf_Cr;
      XDAS_UInt32 dataCRC[3];
      /*----------------------------------------------------------------------*/
      /* Generate the CRC value of Luma for the output yuv                    */
      /*----------------------------------------------------------------------*/
      crcInit();
      dataCRC[0] = crcFast(fieldBuf_Luma, pic_size);

      /*----------------------------------------------------------------------*/
      /* Generate the CRC value of Cb for the output yuv                      */
      /*----------------------------------------------------------------------*/
      fieldBuf_Cb = fieldBuf_Luma + pic_size;
      crcInit();
      dataCRC[1] = crcFast(fieldBuf_Cb, pic_size>>2);

      /*----------------------------------------------------------------------*/
      /* Generate the CRC value of Cr for the output yuv                      */
      /*----------------------------------------------------------------------*/
      fieldBuf_Cr = fieldBuf_Cb + (pic_size >> 2);
      crcInit();
      dataCRC[2] = crcFast(fieldBuf_Cr, pic_size>>2);
      /*----------------------------------------------------------------------*/
      /* Write the CRC value to the Output file                               */
      /*----------------------------------------------------------------------*/
      my_fwrite ((void *)&dataCRC[0], sizeof(XDAS_UInt32), 3, 
                 fout, ARG_FILEIO_TYPE);
    }
  }
  }
#else /* DUMP_WITHPADDING */
  {
    /*------------------------------------------------------------------------*/
    /* Here the frame data (with padding) dumped.                             */
    /* Also UV is interleaved.                                                */
    /* Top and Bottom fields are not interleaved.                             */
    /* Need to use an off-line utility later.                                 */
    /*------------------------------------------------------------------------*/

    if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
            IVIDDEC3_DISPLAYBUFS_PTRS)
    {
      displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.displayBufs.
                                    pBufDesc[!dualOutputFlag];
    }
    else
    {
      displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                        displayBufs.bufDesc[0];
    }

    ref_width   = displayBufs->imagePitch[0];
    lumaAddr1    = (char *)displayBufs->planeDesc[0].buf;
    chromaAddr1  = (XDAS_Int16 *)displayBufs->planeDesc[1].buf;

    pic_size = ref_width * ref_height;

    if(!complianceMode)
    {
      my_fwrite((void *)lumaAddr1, sizeof(char), 
              pic_size,fout, ARG_FILEIO_TYPE);
#ifdef USE_HOST_FILE_IO
      my_fwrite((void *)chromaAddr1, sizeof(char), (pic_size>>1),
                fout, ARG_FILEIO_TYPE);
#else
      my_fwrite((void *)chromaAddr1, sizeof(XDAS_Int16), (pic_size>>2), 
                fout, ARG_FILEIO_TYPE);
#endif
    }
  }
#endif /* DUMP_WITHPADDING */

}

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
XDAS_Void outputDisplayRows(H264VDEC_OutArgs *outArgs, XDAS_Int16 xoff, 
                            XDAS_Int16 yoff, XDAS_Int16 ref_height,
                            XDAS_Int16 width, XDAS_Int16 height,
                            XDAS_UInt32 numRows, XDAS_UInt32 rowNumber,
                            XDAS_Int8 picType,
                            XDAS_Int8 chnlNum
                            )
{
  IVIDEO2_BufDesc *decodedBufs = &outArgs->viddec3OutArgs.decodedBufs;
  XDAS_Int16 ref_width, ref_width_c;
  XDAS_UInt32 pic_size, iVec, jVec;
  XDAS_UInt8 pitchFactor;

  /*-------------------------------------------------------------------------*/
  /* Here the actual frame data (w/out padding), is extracted and dumped.    */
  /* Also UV is de-interleaved.                                              */
  /*-------------------------------------------------------------------------*/
  char *lumaAddr   = (char *)decodedBufs->planeDesc[0].buf;
  char *chromaAddr = (char *)decodedBufs->planeDesc[1].buf;
  char *CbBuf, *CrBuf, *YBuf;

  ref_width   = decodedBufs->imagePitch[0];
  ref_width_c = decodedBufs->imagePitch[1];
  pic_size    = width * height;

  YBuf  = (char *)(nChannelState[chnlNum].fieldBuf + (width * rowNum * 16));
  CbBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size + 
                                         ((width>>1) * rowNum * 8));
  CrBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size + (pic_size>>2) + 
                                         ((width>>1) * rowNum * 8));

  /*-------------------------------------------------------------------------*/
  /* In bottom-field case initial offset in destination buffer should be an  */
  /* an odd value. Hence the below modification.                             */
  /*-------------------------------------------------------------------------*/
  if(decodedBufs->contentType == IVIDEO_INTERLACED_BOTTOMFIELD)
  {
    yoff += (ref_height >> 1);
    YBuf  = (char *)(nChannelState[chnlNum].fieldBuf + 
                     (width * (2*rowNum + 1) * 16));
    CbBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size + 
                     ((width>>1) * (2*rowNum + 1) * 8));
    CrBuf = (char *)(nChannelState[chnlNum].fieldBuf + pic_size + (pic_size>>2)
                      + ((width>>1) * (2*rowNum + 1) * 8));
  }

  lumaAddr   = (char *)((XDAS_Int32)decodedBufs->planeDesc[0].buf + 
               (yoff * ref_width) + xoff);
  chromaAddr = (char *)((XDAS_Int32)decodedBufs->planeDesc[1].buf +  
               ((yoff>>1) * ref_width) + xoff);

  /*-------------------------------------------------------------------------*/
  /* In interlaced case, the source will be holding continuous rows data of  */
  /* either top-field or bottom-field. But while dumping we need to make it  */
  /* progressive content. Hence we need to double the pitch for destination  */
  /* for each source row data.                                               */ 
  /*-------------------------------------------------------------------------*/
  pitchFactor = 1;
  if(picType == IVIDEO_INTERLACED)
  {
    pitchFactor = 2;
  }

  /*-------------------------------------------------------------------------*/
  /* Luma data Dumping...                                                    */
  /*-------------------------------------------------------------------------*/
  for(iVec = 0; iVec < (16*numRows); iVec++)
  {
    memcpy(YBuf, lumaAddr, width);
    YBuf    += (width * pitchFactor);
    lumaAddr += ref_width;
  }

  /*-------------------------------------------------------------------------*/
  /* Chroma data Dumping...                                                  */
  /*-------------------------------------------------------------------------*/
  for(iVec = 0; iVec < (8*numRows); iVec++)
  {
    for(jVec = 0; jVec < (width>>1); jVec++)
    {
      CbBuf[jVec] = chromaAddr[(jVec*2)];
      CrBuf[jVec] = chromaAddr[(jVec*2)+1];
    }

    CbBuf      += ((width>>1) * pitchFactor);
    CrBuf      += ((width>>1) * pitchFactor);
    chromaAddr += ref_width_c;
  }
}

/**
********************************************************************************
 *  @fn     TestApp_CompareOutputCRCData
 *  @brief  Sample utility function for comparing the raw decoded output CRC 
 *          with reference output CRC data.
 *
 *  @param[in] fRefFile : Reference CRC file pointer.
 *
 *  @param[in] outArgs  : outArgs structure containing displayable frame.
 *
 *  @param[in] nChannelState[chnlNum].fieldBuf : Scratch buffer for interleaving
 *                                                the data
 *
 *  @return  XDM_EFAIL/XDM_EOK
********************************************************************************
*/
XDAS_Int32 TestApp_CompareOutputCRCData( FILE               *fRefCRCFile,
                                         XDAS_Int32          display_marker,
                                         H264VDEC_OutArgs   *outArgs,
                                         XDAS_Int8           chnlNum
                                         )
{
  XDAS_Int32 width, height,pic_size;
  IVIDEO2_BufDesc *displayBufs;
  unsigned char *fieldBuf_Luma = 
            (unsigned char *)nChannelState[chnlNum].fieldBuf;
  unsigned char *fieldBuf_Cb;
  unsigned char *fieldBuf_Cr;
  XDAS_UInt32 refCRC, dataCRC;

  /*--------------------------------------------------------------------------*/
  /*  Pointer to Display buffer structure                                     */
  /*--------------------------------------------------------------------------*/
  if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.
                                          displayBufs.pBufDesc[display_marker];
  }
  else
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                          displayBufs.bufDesc[display_marker];
  }

  height = displayBufs->activeFrameRegion.bottomRight.y -
           displayBufs->activeFrameRegion.topLeft.y;

  width  = displayBufs->activeFrameRegion.bottomRight.x -
           displayBufs->activeFrameRegion.topLeft.x;

  /*------------------------------------------------------------------------*/
  /* contentType indicates if the frame was stored as field or not.         */
  /* contentType :0 , frame storage                                         */
  /*   otherwise, it is field storage                                       */
  /*------------------------------------------------------------------------*/
  if(displayBufs->contentType != IVIDEO_PROGRESSIVE)
  {
    /*----------------------------------------------------------------------*/
    /* The frame is stored as 2 fields. So top and bottom fields have to    */
    /* be interleaved. The interleaving is done in                          */
    /* nChannelState[chnlNum].fieldBuf and is then written out              */
    /*----------------------------------------------------------------------*/

    /*----------------------------------------------------------------------*/
    /* Double the paddedheight and height dimensions for two fields         */
    /*----------------------------------------------------------------------*/

    height       <<= 1;
    /*----------------------------------------------------------------------*/
    /*     Write Top and Bottom field                                       */
    /*----------------------------------------------------------------------*/
  }
  pic_size = height * width;

  /*--------------------------------------------------------------------------*/
  /* Read the CRC value of Luma from the reference file                       */
  /*--------------------------------------------------------------------------*/
  fread (&refCRC, 1, sizeof(XDAS_UInt32), fRefCRCFile);
  /*--------------------------------------------------------------------------*/
  /* Generate the CRC value of Luma for the output yuv                        */
  /*--------------------------------------------------------------------------*/
  crcInit();
  dataCRC = crcFast(fieldBuf_Luma, pic_size);

  if(dataCRC != refCRC)
  {
    printf("Luma data doesnot match \n");
    return XDM_EFAIL;
  }

  /*--------------------------------------------------------------------------*/
  /* Read the CRC value of Cb from the reference file                         */
  /*--------------------------------------------------------------------------*/
  fread (&refCRC, 1, sizeof(XDAS_UInt32), fRefCRCFile);
  /*--------------------------------------------------------------------------*/
  /* Generate the CRC value of Cb for the output yuv                          */
  /*--------------------------------------------------------------------------*/
  fieldBuf_Cb = fieldBuf_Luma + pic_size;
  crcInit();
  dataCRC = crcFast(fieldBuf_Cb, pic_size>>2);

  if(dataCRC != refCRC)
  {
    printf("Cb data doesnot match \n");
    return XDM_EFAIL;
  }

  /*--------------------------------------------------------------------------*/
  /* Read the CRC value of Cr from the reference file                         */
  /*--------------------------------------------------------------------------*/
  fread (&refCRC, 1, sizeof(XDAS_UInt32), fRefCRCFile);
  /*--------------------------------------------------------------------------*/
  /* Generate the CRC value of Cr for the output yuv                          */
  /*--------------------------------------------------------------------------*/
  fieldBuf_Cr = fieldBuf_Cb + (pic_size >> 2);
  crcInit();
  dataCRC = crcFast(fieldBuf_Cr, pic_size>>2);

  if(dataCRC != refCRC)
  {
    printf("Cr data doesnot match \n");
    return XDM_EFAIL;
  }

  return XDM_EOK;
}

/**
********************************************************************************
 *  @fn     TestApp_CompareOutputData
 *  @brief  Sample utility function for comparing the raw decoded output with 
 *          reference output data.
 *
 *  @param[in] fRefFile : Reference file pointer.
 *          
 *  @param[in] outArgs  : outArgs structure containing displayable frame.
 *          
 *  @param[in] nChannelState[chnlNum].fieldBuf : Scratch buffer for interleaving
 *                                                the data
 *          
 *  @return  XDM_EFAIL/XDM_EOK
********************************************************************************
*/
XDAS_Int32 TestApp_CompareOutputData( FILE               *fRefFile,
                                      H264VDEC_OutArgs   *outArgs,
                                      XDAS_Int8          chnlNum
                                    )
{
  XDAS_Int32 width, height,pic_size;
  XDAS_Int32 retVal  = XDM_EOK;
  IVIDEO2_BufDesc *displayBufs;

  /*--------------------------------------------------------------------------*/
  /*  Pointer to Display buffer structure                                     */
  /*--------------------------------------------------------------------------*/
  if(nChannelState[chnlNum].params.viddec3Params.displayBufsMode == 
        IVIDDEC3_DISPLAYBUFS_PTRS)
  {
    displayBufs = (IVIDEO2_BufDesc *)outArgs->viddec3OutArgs.
                                                    displayBufs.pBufDesc[0];
  }
  else
  {
    displayBufs = (IVIDEO2_BufDesc *)&outArgs->viddec3OutArgs.
                                                    displayBufs.bufDesc[0];
  }

  height = displayBufs->activeFrameRegion.bottomRight.y - 
           displayBufs->activeFrameRegion.topLeft.y;
  
  width  = displayBufs->activeFrameRegion.bottomRight.x - 
           displayBufs->activeFrameRegion.topLeft.x;
  /*------------------------------------------------------------------------*/
  /* contentType indicates if the frame was stored as field or not.         */
  /* contentType :0 , frame storage                                         */
  /*   otherwise, it is field storage                                       */
  /*------------------------------------------------------------------------*/
  if(displayBufs->contentType == IVIDEO_PROGRESSIVE)
  {
    /*----------------------------------------------------------------------*/
    /*     Progressive frame Storage.                                       */
    /*----------------------------------------------------------------------*/
    pic_size = (3 * height * width)>>1;
  }
  else
  {
    /*----------------------------------------------------------------------*/
    /* The frame is stored as 2 fields. So top and bottom fields have to    */
    /* be interleaved. The interleaving is done in                          */
    /* nChannelState[chnlNum].fieldBuf and is then written out              */
    /*----------------------------------------------------------------------*/

    /*----------------------------------------------------------------------*/
    /* Double the paddedheight and height dimensions for two fields         */
    /*----------------------------------------------------------------------*/
    height       <<= 1;

    /*----------------------------------------------------------------------*/
    /*     Write Top and Bottom field                                       */
    /*----------------------------------------------------------------------*/
    pic_size = (3 * height * width)>>1;
  }


  /*--------------------------------------------------------------------------*/
  /* Compare all the output Buffers with the ref File                         */
  /*--------------------------------------------------------------------------*/
  fread((void *)Chroma_separate, 1, pic_size, fRefFile);
  if(memcmp((void *)Chroma_separate, (void *)nChannelState[chnlNum].fieldBuf,
        pic_size))
  {
    retVal = XDM_EFAIL;
  }

  return retVal;
}

/** 
********************************************************************************
 *  @fn     TestApp_outputDataXfr
 *  @brief  Sample utility function for comparing the raw decoded output with 
 *          reference output data.
 *
 *  @param[in] foutFile : Output file pointer.
 *
 *  @param[in] fRefFile : Reference file pointer.
 *          
 *  @param[in] outArgs  : outArgs structure containing displayable frame.
 *          
 *  @param[in] testCompliance : Scratch buffer for interleaving the data
 *
 *  @param[in] chnlNum      : Decoder channel number.
 *          
 *  @return  APP_EOK/APP_EFAIL
********************************************************************************
*/
XDAS_Int8 TestApp_outputDataXfr( FILE *foutFile, FILE *frefFile,
                                 H264VDEC_OutArgs  outArgs,
                                 XDAS_Int8         testCompliance,
                                 XDAS_Int8         crcEnable,
                                 XDAS_Int8         chnlNum
                               )
{
  XDAS_UInt32  testVal;

  if(testCompliance)
  {
    /*------------------------------------------------------------------------*/
    /* Call the function to write the output frame to a buffer. This function */
    /*  will separate the CB/CR pixels before writing to the file.            */
    /*------------------------------------------------------------------------*/
    TestApp_WriteOutputData(foutFile, &outArgs, 1, crcEnable, chnlNum);

    /*------------------------------------------------------------------------*/
    /* Compare the output frames with the Reference File                      */
    /*------------------------------------------------------------------------*/
    if(crcEnable)
    {
      testVal = TestApp_CompareOutputCRCData(frefFile, 0, &outArgs, chnlNum);
    }
    else
    {
      testVal = TestApp_CompareOutputData(frefFile, &outArgs, chnlNum);
    }
    if(testCompliance > 1)
    {
      fprintf(stdout, 
              "--- Frame # %d: Compliance mode %d is Not Supported ----\n", 
              nChannelState[chnlNum].displayCount++, testCompliance);

      testVal = XDM_EOK;
    }

    if(testVal != XDM_EOK)
    {
      bitMismatchDetected = 1;

      /*----------------------------------------------------------------------*/
      /* Test Compliance Failed... Breaking...                                */
      /*----------------------------------------------------------------------*/
      fprintf(stdout,"--- Frame # %d Failed ----\n",
                        nChannelState[chnlNum].displayCount++);

      /*----------------------------------------------------------------------*/
      /*  Free all buffers                                                    */
      /*----------------------------------------------------------------------*/
      BUFFMGR_ReleaseAllBuffers(1);
      return APP_EFAIL;
    }
    else
    {
      fprintf(stdout,"--- Frame # %d Passed ----\n",
                        nChannelState[chnlNum].displayCount++);
    }
  }
  else
  {
    /*------------------------------------------------------------------------*/
    /* Call the function to write the output frame to the file. This function */
    /* will separate the CB/CR pixels before writing to the file.             */
    /*------------------------------------------------------------------------*/
    TestApp_WriteOutputData(foutFile, &outArgs, 0, crcEnable, chnlNum);
  }
  return APP_EOK;
}

/** 
********************************************************************************
 *  @fn     TestApp_ioFilePtrInit
 *  @brief  Sample utility function for comparing the raw decoded output with 
 *          reference output data.
 *
 *  @param[in] fRefFile : Reference file pointer.
 *          
 *  @param[in] outArgs  : outArgs structure containing displayable frame.
 *          
 *  @return   APP_EOK/APP_EXIT/APP_EFAIL
********************************************************************************
*/
XDAS_Int8 TestApp_ioFilePtrInit(FILE *fpConfig, XDAS_Int8 *testCompliance,
                                XDAS_Int8 *crcEnable,
                                XDAS_Int8  chnlNum)
{
  /*--------------------------------------------------------------------------*/
  /*  File I/O variables                                                      */
  /*--------------------------------------------------------------------------*/
  FILE *fpSize;
  FILE *fpRef, *fpParams;
  FILE *fpOutput, *fpDualOutput, *fpWaterMark;
  XDAS_UInt8  line[STRING_SIZE];

  fpRef    = NULL;
  /*------------------------------------------------------------------------*/
  /*  Read Parameters file name                                             */
  /*------------------------------------------------------------------------*/
  if(fgets((char *)line, 254, fpConfig))
  {
    sscanf((const char *)line,"%s",paramsFile);
  }
  else
  {
    return APP_EXIT;
  }

  /*------------------------------------------------------------------------*/
  /* Open Parameters file, and read the contents of parameters              */
  /* related to the H264 decoder codec.                                     */
  /*------------------------------------------------------------------------*/
  fpParams = fopen ((const char *)paramsFile, "rb");
  if(!fpParams)
  {
    printf("Couldn't open Parameters file...   %s\n", paramsFile);
    return APP_EFAIL;
  }

  /*--------------------------------------------------------------------------*/
  /* Parse the Config file                                                    */
  /*--------------------------------------------------------------------------*/
  if(readparamfile(fpParams) < 0)
  {
    printf("Syntax Error in config file: %s\n", paramsFile);
    return APP_EFAIL;
  }
  memcpy(&nChannelState[chnlNum].appCntrlParams,
          &appControlPrms,
          sizeof(sAppControlParams));

  memcpy(&nChannelState[chnlNum].params,
          &params,
          sizeof(H264VDEC_Params));

  memcpy(&nChannelState[chnlNum].dynamicParams,
          &dynamicParams,
          sizeof(H264VDEC_DynamicParams));

  /*------------------------------------------------------------------------*/
  /*  Open Output file                                                      */
  /*------------------------------------------------------------------------*/
  fpOutput = my_fopen((const char *)nChannelState[chnlNum].
                    appCntrlParams.outFile, "wb", ARG_FILEIO_TYPE);

  /*------------------------------------------------------------------------*/
  /*  Check for file open errors.                                           */
  /*------------------------------------------------------------------------*/
  if(!fpOutput)
  {
    printf("Couldn't open Output File... %s", 
                    nChannelState[chnlNum].appCntrlParams.outFile);
    return APP_EFAIL;
  }
  
  if(nChannelState[chnlNum].params.enableDualOutput)
  {
    /*----------------------------------------------------------------------*/
    /*  Open DualOutput file                                                */
    /*----------------------------------------------------------------------*/
    fpDualOutput = my_fopen((const char *)nChannelState[chnlNum].
                    appCntrlParams.outDualFile, "wb", ARG_FILEIO_TYPE);
    /*----------------------------------------------------------------------*/
    /*  Check for file open errors.                                         */
    /*----------------------------------------------------------------------*/
    if(!fpDualOutput)
    {
      printf("Couldn't open Output File... %s", nChannelState[chnlNum].
                    appCntrlParams.outDualFile);
      return APP_EFAIL;
    }
  }
  if(nChannelState[chnlNum].params.enableWatermark)
  {
    /*------------------------------------------------------------------------*/
    /*  Open Watermark file                                                   */
    /*------------------------------------------------------------------------*/
    fpWaterMark = my_fopen((const char *)appControlPrms.WaterMarkFile, "wb", 
                      ARG_FILEIO_TYPE);

    /*------------------------------------------------------------------------*/
    /*  Check for file open errors.                                           */
    /*------------------------------------------------------------------------*/
    if(!fpWaterMark)
    {
      printf("Couldn't open Watermark File... %s", 
                           appControlPrms.WaterMarkFile);
      return APP_EFAIL;
    }
  }

  *testCompliance = nChannelState[chnlNum].appCntrlParams.testCompliance;
  *crcEnable = nChannelState[chnlNum].appCntrlParams.crcNyuv;

  /*------------------------------------------------------------------------*/
  /*  Open output/reference file depending on whether it is the test        */
  /*  compliance mode or not. Currently, compliance mode not supported.     */
  /*------------------------------------------------------------------------*/
  if(*testCompliance)
  {
    fpRef = (FILE*)fopen((const char *)nChannelState[chnlNum].
                    appCntrlParams.refFile, "rb");

    /*------------------------------------------------------------------------*/
    /*  Check for file open errors.                                           */
    /*------------------------------------------------------------------------*/
    if(!fpRef)
    {
      printf("Couldn't open Output File... %s", nChannelState[chnlNum].
                    appCntrlParams.refFile);
      return APP_EFAIL;
    }
  }

  /*----------------------------------------------------------------------*/
  /* In case the application runs in frame mode or NAL mode, need to      */
  /* use the frame size file or NAL size file.                            */
  /*----------------------------------------------------------------------*/
  if(nChannelState[chnlNum].appCntrlParams.bitStreamMode ||  
     (nChannelState[chnlNum].params.viddec3Params.inputDataMode == 
     IH264VDEC_NALUNIT_MODE) || (nChannelState[chnlNum].params.
     viddec3Params.inputDataMode ==IVIDEO_SLICEMODE))
  {
    fpSize = (FILE*)fopen((const char *)nChannelState[chnlNum].
                appCntrlParams.sizeFile, "rb");
    /*----------------------------------------------------------------------*/
    /*  Check for file open errors.                                         */
    /*----------------------------------------------------------------------*/
    if(!fpSize)
    {
      printf("Couldn't open Output File... %s", nChannelState[chnlNum].
                appCntrlParams.sizeFile);
      return APP_EFAIL;
    }
  }

  /*----------------------------------------------------------------------*/
  /* Capturing all the file pointers at one place.                        */
  /*----------------------------------------------------------------------*/
  nChannelState[chnlNum].appFilePtrs.fpOutFile      = fpOutput;
  nChannelState[chnlNum].appFilePtrs.fpDualOutFile  = fpDualOutput;
  nChannelState[chnlNum].appFilePtrs.fpWaterMarkFile = fpWaterMark;
  nChannelState[chnlNum].appFilePtrs.fpRefFile      = fpRef;
  nChannelState[chnlNum].appFilePtrs.fpSizeFile     = fpSize;
  
  return APP_EOK;
}

/** 
********************************************************************************
 *  @fn     TestApp_errorReport
 *  @brief  Printing all the errors that are set by codec
 *
 *  @param[in] errMsg : Error Message
 *          
 *  @return None
********************************************************************************
*/
XDAS_Void TestApp_errorReport(XDAS_Int32 errMsg)
{
  XDAS_Int32 errBits;
  XDAS_Int32 firstTime = 1;

  for(errBits = 0; errBits < 32; errBits++)
  {
    if(errMsg & (1 << errBits))
    {
      /*if(errBits != IH264VDEC_ERR_STREAM_END) */ 
      {
        if(firstTime)
        {
          printf("Error Name: \t BitPositon in ErrorMessage\n");
          firstTime = 0;
        }
        printf("ERROR: %s \n",  gErrorStrings[errBits].errorName);           
      }
    }
  }

}

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
XDAS_Bool TestApp_checkErr(XDAS_Int32 errMsg, XDAS_Int32 errVal)
{
  if(errMsg & (1 << errVal))
  {
    return XDAS_TRUE;
  }
  else
  {
    return XDAS_FALSE;
  }
}

static sEnumToStringMapping gStatus[2] = 
{
  (XDAS_Int8 *)" : PASS \0",
  (XDAS_Int8 *)" : FAIL \0"
};

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
XDAS_Void updateConfigStatusFile(XDAS_Int8 status)
{
  /*--------------------------------------------------------------------------*/
  /* Capturing the current testVector's config file name.                     */
  /*--------------------------------------------------------------------------*/
  fprintf(fLogFile, "\n %s \t", paramsFile);

  if(status == IALG_EOK)
  {
    fprintf(fLogFile, "%s", gStatus[0]);
  }
  else
  {
    fprintf(fLogFile, "%s", gStatus[1]);
  }
}
