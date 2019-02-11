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
 * @file <TestApp_bufmanager.c>                          
 *                                       
 * @brief  This is source module for buffer manager functionality
 *         H264 (High Profile) Video Decoder Call using XDM Interface
 *  
 * @author: Multimedia Codecs TI
 *
 * @version 0.0 (Jan 2008)  : Initial version
 * @version 0.2 (Sept 2009) : Code commenting and cleanup
 *                            [Ramakrishna]
 * @version 0.3 (May 2010)  : Changes for metadata buffer allocation
 *                            [Keshava Prasad] 
 * @version 0.4 (Jun 2010)  : Generalization of Reinit function
 *                            [Ramakrishna]
 * @version 0.5 (Jul 2010)  : Code cleanup
 *                            [Ramakrishna]
 * @version 0.6 (June 2011) : Buffer Management  for  Dual yuv support  
 *                            is added
 *                            [Vijay Kumar yadav]
 * @version 0.7 (Oct 2012) : Buffer Management is modified for 4320 width 
 *                            support [Suresh Reddy]
 ******************************************************************************
*/
/******************************************************************************
*  INCLUDE FILES                                                
******************************************************************************/
#include <xdc/std.h>
#include <TestApp_constants.h>
#include <TestAppDecoder.h>
#include <tilerBuf.h>

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
XDAS_UInt8 *globalBufferHandle[XDM_MAX_IO_BUFFERS];
XDAS_UInt32 globalBufferSizes[XDM_MAX_IO_BUFFERS];
XDAS_UInt8 *LumaBufPtr, *ChromaBufPtr, *NextBufPtr;
XDAS_UInt8 *LumaBufPtrDual, *ChromaBufPtrDual;
XDAS_UInt32 LumaBufWidth, ChromaBufWidth;
void SetPATViewMapBase();
/*--------------------------------------------------------------------------*/
/* Externally declared variables, accessed in this file                     */
/*--------------------------------------------------------------------------*/
extern sTilerParams       tilerParams;

extern XDAS_UInt8 metaDataIndex[NUM_DEC_CHANNELS_SUPPORTED][IVIDEO_MAX_NUM_METADATA_PLANES];
extern XDAS_UInt8 metaDataEnable[NUM_DEC_CHANNELS_SUPPORTED][IVIDEO_MAX_NUM_METADATA_PLANES];

extern sChannelState nChannelState[NUM_DEC_CHANNELS_SUPPORTED];
/** 
********************************************************************************
 *  @fn     BUFFMGR_Init
 *  @brief  The BUFFMGR_Init function is called by the test application to
 *          initialise the global buffer element array to default and to 
 *          allocate required number of memory data for reference and output 
 *          buffers.
 *          The maximum required dpb size is defined by the supported profile & 
 *          level
 *          
 *  @param[in] numBufs   : Number of buffers to be allocated.
 *  @param[in] bufSizes  : Address of array containing the buffer sizes of the 
 *                         numbufs.
 *  @param[in] memType   : Pointer to the memory type to tell whether it is 
 *                         Tiled memory or not  
 *  @param[in] chnlNum   : Decode channel number
 *          
 *  @return Success(0)/failure(-1) in allocating and initialising
********************************************************************************
*/
XDAS_Int32 BUFFMGR_Init(XDAS_Int32    numBufs, 
                        XDM2_BufSize *bufSizes, 
                        XDAS_Int32   *memType,
                        XDAS_Int8     chnlNum
                       )
{
  XDAS_UInt32 tmpCnt, Size ,BufferCount;
  XDAS_UInt8  idx;
  XDAS_UInt8 *BufPtr;

  /*--------------------------------------------------------------------------*/
  /* Initialise the elements in the global buffer array                       */
  /*--------------------------------------------------------------------------*/
  for(tmpCnt = 0; tmpCnt < MAX_BUFF_ELEMENTS; tmpCnt++)
  {
    nChannelState[chnlNum].buffArray[tmpCnt].bufId      = tmpCnt + 1;
    nChannelState[chnlNum].buffArray[tmpCnt].bufStatus  = BUFFMGR_BUFFER_FREE;

    for (idx = 0; idx < MAX_BUFS_IN_FRAME; idx++)
    {
      nChannelState[chnlNum].buffArray[tmpCnt].bufSize[idx].bytes = 0;
      nChannelState[chnlNum].buffArray[tmpCnt].buf[idx]           = NULL;
    }
  }

  if(!nChannelState[chnlNum].dynamicParams.viddec3DynamicParams.decodeHeader)
  {
    /*-----------------------------------------------------------------------*/
    /* Allocate memory from the tiled space                                  */
    /*-----------------------------------------------------------------------*/
    if((nChannelState[chnlNum].appCntrlParams.tilerEnable) && 
       (memType[0] != XDM_MEMTYPE_ROW))
    {
      nChannelState[chnlNum].buffArray[0].buf[0]  = 
                  (volatile XDAS_UInt8 *)(tilerParams.tiledBufferAddr[0]);

      nChannelState[chnlNum].buffArray[0].bufSize[0].tileMem.width  = 
                                                bufSizes[0].tileMem.width;
      nChannelState[chnlNum].buffArray[0].bufSize[0].tileMem.height = 
                                                bufSizes[0].tileMem.height;

      nChannelState[chnlNum].buffArray[0].buf[1] = 
                (volatile XDAS_UInt8 *)(tilerParams.tiledBufferAddr[1]);

      nChannelState[chnlNum].buffArray[0].bufSize[1].tileMem.width  = 
                                                bufSizes[1].tileMem.width;
      nChannelState[chnlNum].buffArray[0].bufSize[1].tileMem.height = 
                                                bufSizes[1].tileMem.height;
      
      if(nChannelState[chnlNum].params.enableDualOutput && 
        nChannelState[chnlNum].appCntrlParams.dualTilerEnable) 
      {
        nChannelState[chnlNum].buffArray[0].buf[2]  = 
                  (volatile XDAS_UInt8 *)(tilerParams.tiledBufferAddr[2]);

        nChannelState[chnlNum].buffArray[0].bufSize[2].tileMem.width  = 
                                                bufSizes[2].tileMem.width;
        nChannelState[chnlNum].buffArray[0].bufSize[2].tileMem.height = 
                                                bufSizes[2].tileMem.height;

        nChannelState[chnlNum].buffArray[0].buf[3] = 
                (volatile XDAS_UInt8 *)(tilerParams.tiledBufferAddr[3]);

        nChannelState[chnlNum].buffArray[0].bufSize[3].tileMem.width  = 
                                                bufSizes[3].tileMem.width;
        nChannelState[chnlNum].buffArray[0].bufSize[3].tileMem.height = 
                                                bufSizes[3].tileMem.height;
      }
      else if(nChannelState[chnlNum].params.enableDualOutput) 
      { /* Dual output is Non -  tiler*/
        /*-------------------------------------------------------------------*/
        /* Set memory for Dual Output as  non tiled                          */
        /*-------------------------------------------------------------------*/
        memType[2] = XDM_MEMTYPE_ROW;
        memType[3] = XDM_MEMTYPE_ROW;
        nChannelState[chnlNum].buffArray[0].bufSize[2].tileMem.height = 0;
        nChannelState[chnlNum].buffArray[0].bufSize[3].tileMem.height = 0;                      
        /*-------------------------------------------------------------------*/
        /* Set memory buffer parameters for Dual output                      */
        /*-------------------------------------------------------------------*/ 
        nChannelState[chnlNum].buffArray[0].bufSize[2].bytes = 
                (bufSizes[0].tileMem.width) * (bufSizes[0].tileMem.height);
  
        nChannelState[chnlNum].buffArray[0].bufSize[3].bytes = 
                (bufSizes[1].tileMem.width) * (bufSizes[1].tileMem.height);
  
        bufSizes[2].bytes = 
                    nChannelState[chnlNum].buffArray[0].bufSize[2].bytes;
        bufSizes[3].bytes = 
                    nChannelState[chnlNum].buffArray[0].bufSize[3].bytes;
        /*-------------------------------------------------------------------*/
        /*  NON-CONTIGUOUS BUFFERS:                                          */
        /*  Separate buffers for Luma                                        */
        /*-------------------------------------------------------------------*/
        Size   = bufSizes[2].bytes;
        BufPtr = my_Memalign (128, Size * sizeof(XDAS_UInt8));
        /*-------------------------------------------------------------------*/
        /* Check if allocation took place properly or not                    */
        /*-------------------------------------------------------------------*/
        if(BufPtr == NULL)
        {
          return -1;
        }
        memset(BufPtr, 0x80,  Size);
        nChannelState[chnlNum].buffArray[0].buf[2]             = BufPtr;
        nChannelState[chnlNum].buffArray[0].bufSize[2].bytes   = Size;
        /*-------------------------------------------------------------------*/
        /*  NON-CONTIGUOUS BUFFERS:                                          */
        /*  Separate buffers for Chroma                                      */
        /*-------------------------------------------------------------------*/        
        Size   = bufSizes[3].bytes;
        BufPtr = my_Memalign (128, Size * sizeof(XDAS_UInt8));
        
        /*-------------------------------------------------------------------*/
        /* Check if allocation took place properly or not                    */
        /*-------------------------------------------------------------------*/
        if(BufPtr == NULL)
        {
          return -1;
        }

        memset(BufPtr, 0x80,  Size);
        nChannelState[chnlNum].buffArray[0].buf[3]             = BufPtr;
        nChannelState[chnlNum].buffArray[0].bufSize[3].bytes   = Size;        
      }
      else
      {
        /*-------------------------------------------------------------------*/
        /* Dual output is not enable ,so in this case another buffer is not  */
        /* required                                                          */
        /*-------------------------------------------------------------------*/
      }      
    }
    else
    {
      memType[0] = XDM_MEMTYPE_ROW;
      memType[1] = XDM_MEMTYPE_ROW;
      /*--------------------------------------------------------------------*/
      /* Set memory for Dual Output as  non tiled                           */
      /*--------------------------------------------------------------------*/      
      if(nChannelState[chnlNum].params.enableDualOutput)
      {
        memType[2] = XDM_MEMTYPE_ROW;
        memType[3] = XDM_MEMTYPE_ROW;
      }
      nChannelState[chnlNum].buffArray[0].bufSize[0].bytes = 
            (bufSizes[0].tileMem.width) * (bufSizes[0].tileMem.height);

      nChannelState[chnlNum].buffArray[0].bufSize[1].bytes = 
            (bufSizes[1].tileMem.width) * (bufSizes[1].tileMem.height);

      bufSizes[0].bytes = nChannelState[chnlNum].buffArray[0].bufSize[0].bytes;
      bufSizes[1].bytes = nChannelState[chnlNum].buffArray[0].bufSize[1].bytes;
      /*--------------------------------------------------------------------*/
      /* Set memory buffer parameters for Dual output                       */
      /*--------------------------------------------------------------------*/       
      if(nChannelState[chnlNum].params.enableDualOutput)
      {    
        nChannelState[chnlNum].buffArray[0].bufSize[2].bytes = 
                (bufSizes[2].tileMem.width) * (bufSizes[2].tileMem.height);

        nChannelState[chnlNum].buffArray[0].bufSize[3].bytes = 
                (bufSizes[3].tileMem.width) * (bufSizes[3].tileMem.height);

        bufSizes[2].bytes = 
                    nChannelState[chnlNum].buffArray[0].bufSize[2].bytes;
        bufSizes[3].bytes = 
                    nChannelState[chnlNum].buffArray[0].bufSize[3].bytes;
      }
    
      /*--------------------------------------------------------------------*/
      /* In case of dual output idx counter should go up to BufferCount -1. */
      /* idx = 0 :: LUMA                                                    */
      /* idx = 1 :: LUMADUAL                                                */
      /* idx = 2 :: CROMA                                                   */
      /* idx = 3 :: CROMADUAL                                               */ 
      /*--------------------------------------------------------------------*/
      BufferCount = 2;
      if(nChannelState[chnlNum].params.enableDualOutput)
      {
        BufferCount <<= 1;
      }
      if (nChannelState[chnlNum].params.viddec3Params.maxWidth > 2048 || 
                  nChannelState[chnlNum].params.viddec3Params.maxHeight > 2048)
      {
        nChannelState[chnlNum].buffArray[0].buf[0]  = 
                                          (volatile XDAS_UInt8 *)0x9B000000;
        nChannelState[chnlNum].buffArray[0].bufSize[0].bytes = 
                                                      bufSizes[0].bytes;
        
        nChannelState[chnlNum].buffArray[0].buf[1] = 
                                             (volatile XDAS_UInt8 *)0x9C200000;
        nChannelState[chnlNum].buffArray[0].bufSize[1].bytes = 
                                              bufSizes[1].bytes;
      }
      else
      {
        for (idx = 0; idx < BufferCount; idx++)
        {
          /*------------------------------------------------------------------*/
          /*  NON-CONTIGUOUS BUFFERS:                                         */
          /*  Separate buffers for Luma & chroma.                             */
          /*------------------------------------------------------------------*/
          Size   = bufSizes[idx].bytes;
          BufPtr = my_Memalign (128, Size * sizeof(XDAS_UInt8));
          
          /*------------------------------------------------------------------*/
          /* Check if allocation took place properly or not                   */
          /*------------------------------------------------------------------*/
          if(BufPtr == NULL)
          {
            return -1;
          }
          
          memset(BufPtr, 0x80,  Size);
          
          nChannelState[chnlNum].buffArray[0].buf[idx]             = BufPtr;
          nChannelState[chnlNum].buffArray[0].bufSize[idx].bytes   = Size;
        }
      }
    }
  }

  /*--------------------------------------------------------------------------*/
  /* Meta Data Buffer allocation & initialization                             */
  /*--------------------------------------------------------------------------*/
  if(TestAppMetaDataBuf(bufSizes,chnlNum))
  {
    return -1;
  }

  return 0;
}

/** 
********************************************************************************
 *  @fn     BUFFMGR_ReInit
 *  @brief  The BUFFMGR_ReInit function allocates global luma and chroma buffers
 *          and allocates entire space to first element. This element will be
 *          used in first frame decode. After the picture's height and width and
 *          its luma and chroma buffer requirements are obtained the global luma
 *          and chroma buffers are re-initialised to other elements in that
 *          buffer array.
 *           
 *  @param[in] numRefBufs : Number of Buffers that will work as reference
 *                          buffers for decoding of a frame.
 *  @param[in] numOutBufs : pointer to SeqParams.
 *  @param[in] *bufSizes  : Pointer to array containing the buffer sizes.
 *  @param[in] *memType   : Pointer to the arry containing memory type
 *                          (Tiler/Non-Tiler)
 *  @param[in] chnlNum  : Decoder channel number.
 *          
 *  @return Success(0)/failure(-1) in allocating and initialising
********************************************************************************
*/
XDAS_Int32 BUFFMGR_ReInit( XDAS_Int32 numRefBufs,
                           XDAS_Int32 numOutBufs,
                           XDM2_BufSize *bufSizes,
                           XDAS_Int32 *memType,
                           XDAS_Int32 startBufIdx,
                           XDAS_Int8  chnlNum
                         )
{
  XDAS_Int32  idx, size;
  XDAS_Int32  startIdx = startBufIdx;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

  if(nChannelState[chnlNum].dynamicParams.viddec3DynamicParams.decodeHeader)
  {
    startIdx = 0;
  }
  /*--------------------------------------------------------------------------*/
  /*  Freeing up meta data Buffers                                            */
  /*--------------------------------------------------------------------------*/
  if(metaDataEnable[chnlNum][APP_SEI_DATA])
  {
    free((void *)nChannelState[chnlNum].buffArray[0].buf[2 + 
                metaDataIndex[chnlNum][APP_SEI_DATA] + (dualOutputFlag*2)]);
  }

  if(metaDataEnable[chnlNum][APP_VUI_DATA])
  {
    free((void *)nChannelState[chnlNum].buffArray[0].buf[2 + 
                metaDataIndex[chnlNum][APP_VUI_DATA] + (dualOutputFlag*2)]);
  }

  if(metaDataEnable[chnlNum][APP_MB_INFO])
  {
    free((void *)nChannelState[chnlNum].buffArray[0].buf[2 + 
                metaDataIndex[chnlNum][APP_MB_INFO] + (dualOutputFlag*2)]);
  }
  /*--------------------------------------------------------------------------*/
  /* As the application would have already provided one buffer                */
  /* allocate memory for 1 minus the actual number of reference buffers.      */
  /*--------------------------------------------------------------------------*/
  /*--------------------------------------------------------------------------*/
  /* Allocate from Tiled space                                                */
  /*--------------------------------------------------------------------------*/
  if((nChannelState[chnlNum].appCntrlParams.tilerEnable) && 
     (memType[0] != XDM_MEMTYPE_ROW))
  {
    for(idx = startIdx; idx < numRefBufs; idx++)
    {
      if(dualOutputFlag && 
        nChannelState[chnlNum].appCntrlParams.dualTilerEnable) 
      {
        nChannelState[chnlNum].buffArray[idx].buf[0]  = 
                  (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*4];

        nChannelState[chnlNum].buffArray[idx].bufSize[0].tileMem.width  = 
                                                bufSizes[0].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[0].tileMem.height = 
                                                bufSizes[0].tileMem.height;

        nChannelState[chnlNum].buffArray[idx].buf[1] = 
                (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*4+1];

        nChannelState[chnlNum].buffArray[idx].bufSize[1].tileMem.width  = 
                                                bufSizes[1].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[1].tileMem.height = 
                                                bufSizes[1].tileMem.height;
        
        nChannelState[chnlNum].buffArray[idx].buf[2]  = 
                  (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*4 +2];

        nChannelState[chnlNum].buffArray[idx].bufSize[2].tileMem.width  = 
                                                bufSizes[2].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[2].tileMem.height = 
                                                bufSizes[2].tileMem.height;

        nChannelState[chnlNum].buffArray[idx].buf[3] = 
                (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*4+3];

        nChannelState[chnlNum].buffArray[idx].bufSize[3].tileMem.width  = 
                                                bufSizes[3].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[3].tileMem.height = 
                                                bufSizes[3].tileMem.height; 
      }
      else if(dualOutputFlag)
      {/* Dual output is Non-tiler Tiler*/
        nChannelState[chnlNum].buffArray[idx].buf[0]  = 
                  (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*2];

        nChannelState[chnlNum].buffArray[idx].bufSize[0].tileMem.width  = 
                                                bufSizes[0].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[0].tileMem.height = 
                                                bufSizes[0].tileMem.height;

        nChannelState[chnlNum].buffArray[idx].buf[1] = 
                (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*2+1];

        nChannelState[chnlNum].buffArray[idx].bufSize[1].tileMem.width  = 
                                                bufSizes[1].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[1].tileMem.height = 
                                                bufSizes[1].tileMem.height;
        /*--------------------------------------------------------------------*/
        /* Set tha Memory type usases in case of Dual Output mode             */
        /*--------------------------------------------------------------------*/
        memType[2] = XDM_MEMTYPE_ROW;
        memType[3] = XDM_MEMTYPE_ROW;
        nChannelState[chnlNum].buffArray[idx].bufSize[2].tileMem.height = 0;
        nChannelState[chnlNum].buffArray[idx].bufSize[3].tileMem.height = 0;
        nChannelState[chnlNum].buffArray[idx].bufSize[2].bytes = 
                (bufSizes[0].tileMem.width) * (bufSizes[0].tileMem.height);

        nChannelState[chnlNum].buffArray[idx].bufSize[3].bytes = 
                (bufSizes[1].tileMem.width) * (bufSizes[1].tileMem.height);
        bufSizes[2].bytes = 
                nChannelState[chnlNum].buffArray[idx].bufSize[2].bytes;
        bufSizes[3].bytes = 
                nChannelState[chnlNum].buffArray[idx].bufSize[3].bytes;  
      
        /*--------------------------------------------------------------------*/
        /* Allocation for Luma. Check if allocation happened or not           */
        /*--------------------------------------------------------------------*/
        size       = nChannelState[chnlNum].buffArray[idx].bufSize[2].bytes;
        LumaBufPtrDual = my_Memalign (128, size * sizeof(XDAS_UInt8));
        if(LumaBufPtrDual == NULL)
        {
          return -1;
        }
        /*-------------------------------------------------------------------*/
        /* Fill the Buffer with gray value.                                  */
        /*-------------------------------------------------------------------*/
        memset(LumaBufPtrDual, 0x80, size);
        /*--------------------------------------------------------------------*/
        /* Allocation for Chroma. Check if allocation happened or not         */
        /*--------------------------------------------------------------------*/
        size         = nChannelState[chnlNum].buffArray[idx].bufSize[3].bytes;
        /*------------------------------------------------------------------*/
        /* Allocation for Chroma. Check if allocation happened or not       */
        /*------------------------------------------------------------------*/
        ChromaBufPtrDual = my_Memalign (128, size * sizeof(XDAS_UInt8));

        if(ChromaBufPtrDual == NULL)
        {
          free(LumaBufPtrDual);
          return -1;
        }
        /*------------------------------------------------------------------*/
        /* Fill the Buffer with gray value.                                 */
        /*------------------------------------------------------------------*/
        memset(ChromaBufPtrDual, 0x80, size);
        
        nChannelState[chnlNum].buffArray[idx].buf[2] = LumaBufPtrDual;
        nChannelState[chnlNum].buffArray[idx].bufSize[2].bytes = 
                                                       bufSizes[2].bytes;
        nChannelState[chnlNum].buffArray[idx].buf[3] = ChromaBufPtrDual;
        nChannelState[chnlNum].buffArray[idx].bufSize[3].bytes = 
                                                       bufSizes[3].bytes;
      }
      else   /* Dual output is not enable */
      {
        nChannelState[chnlNum].buffArray[idx].buf[0]  = 
                  (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*2];

        nChannelState[chnlNum].buffArray[idx].bufSize[0].tileMem.width  = 
                                                bufSizes[0].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[0].tileMem.height = 
                                                bufSizes[0].tileMem.height;

        nChannelState[chnlNum].buffArray[idx].buf[1] = 
                (volatile XDAS_UInt8 *)tilerParams.tiledBufferAddr[idx*2+1];

        nChannelState[chnlNum].buffArray[idx].bufSize[1].tileMem.width  = 
                                                bufSizes[1].tileMem.width;
        nChannelState[chnlNum].buffArray[idx].bufSize[1].tileMem.height = 
                                                bufSizes[1].tileMem.height;
      }      
    }
  }
  else
  {
    memType[0] = XDM_MEMTYPE_ROW;
    memType[1] = XDM_MEMTYPE_ROW;
    
    /*--------------------------------------------------------------------*/
    /* Set tha Memory type usases in case of Dual Output mode             */
    /*--------------------------------------------------------------------*/
    if(dualOutputFlag)
    {
      memType[2] = XDM_MEMTYPE_ROW;
      memType[3] = XDM_MEMTYPE_ROW;
    }
    for(idx = startIdx; idx < numRefBufs; idx++)
    {
      nChannelState[chnlNum].buffArray[idx].bufSize[0].bytes = 
              (bufSizes[0].tileMem.width) * (bufSizes[0].tileMem.height);

      nChannelState[chnlNum].buffArray[idx].bufSize[1].bytes = 
              (bufSizes[1].tileMem.width) * (bufSizes[1].tileMem.height);
      nChannelState[chnlNum].buffArray[idx].bufSize[2].bytes = 
              (bufSizes[2].tileMem.width) * (bufSizes[2].tileMem.height);

      nChannelState[chnlNum].buffArray[idx].bufSize[3].bytes = 
              (bufSizes[3].tileMem.width) * (bufSizes[3].tileMem.height);
    }
    bufSizes[0].bytes = 
              nChannelState[chnlNum].buffArray[idx-1].bufSize[0].bytes;
    bufSizes[1].bytes = 
              nChannelState[chnlNum].buffArray[idx-1].bufSize[1].bytes;
    
    if(dualOutputFlag)
    {
      bufSizes[2].bytes = 
                nChannelState[chnlNum].buffArray[idx-1].bufSize[0].bytes;
      bufSizes[3].bytes = 
                nChannelState[chnlNum].buffArray[idx-1].bufSize[1].bytes;
    }      
    if (nChannelState[chnlNum].params.viddec3Params.maxWidth > 2048 || 
                 nChannelState[chnlNum].params.viddec3Params.maxHeight > 2048)
    {
      if(numRefBufs >5)
      {
        return -1;
      }
      nChannelState[chnlNum].buffArray[1].buf[0] = 
                                            (volatile XDAS_UInt8 *)0x9CB00000;
      nChannelState[chnlNum].buffArray[1].bufSize[0].bytes = bufSizes[0].bytes;
      nChannelState[chnlNum].buffArray[1].buf[1] = 
                                            (volatile XDAS_UInt8 *)0x9DD00000;
      nChannelState[chnlNum].buffArray[1].bufSize[1].bytes = bufSizes[1].bytes;
       
      /*----------------------------------------------------------------------*/
      /* If the decoder high resolution(4320x4096) is running on OMAP4, Only  */
      /* one reference frame is allocated as OMAP4 has less DDR space.        */
      /*----------------------------------------------------------------------*/
#ifdef NETRA
      nChannelState[chnlNum].buffArray[2].buf[0] = 
                                            (volatile XDAS_UInt8 *)0x9E600000;
      nChannelState[chnlNum].buffArray[2].bufSize[0].bytes = bufSizes[0].bytes;
      nChannelState[chnlNum].buffArray[2].buf[1] = 
                                            (volatile XDAS_UInt8 *)0x9F800000;
      nChannelState[chnlNum].buffArray[2].bufSize[1].bytes = bufSizes[1].bytes;
#endif
    }
    else
    {
      for(idx = startIdx; idx < numRefBufs; idx++)
      {
        /*--------------------------------------------------------------------*/
        /* Allocation for Luma. Check if allocation happened or not           */
        /*--------------------------------------------------------------------*/
        size       = bufSizes[0].bytes;
        LumaBufPtr = my_Memalign (128, size * sizeof(XDAS_UInt8));
        if(LumaBufPtr == NULL)
        {
          return -1;
        }
        /*--------------------------------------------------------------------*/
        /* Fill the Buffer with gray value.                                   */
        /*--------------------------------------------------------------------*/
        memset(LumaBufPtr, 0x80, size);
        
        if(dualOutputFlag)
        {
          LumaBufPtrDual = my_Memalign (128, size * sizeof(XDAS_UInt8));
          if(LumaBufPtrDual == NULL)
          {
            return -1;
          }
          /*------------------------------------------------------------------*/
          /* Fill the Buffer with gray value.                                 */
          /*------------------------------------------------------------------*/
          memset(LumaBufPtrDual, 0x80, size);
          
        }

        /*--------------------------------------------------------------------*/
        /* Allocation for Chroma. Check if allocation happened or not         */
        /*--------------------------------------------------------------------*/
        size         = bufSizes[1].bytes;
        ChromaBufPtr = my_Memalign (128, size * sizeof(XDAS_UInt8));

        if(ChromaBufPtr == NULL)
        {
          free(LumaBufPtr);
          return -1;
        }
        /*--------------------------------------------------------------------*/
        /* Fill the Buffer with gray value.                                   */
        /*--------------------------------------------------------------------*/
        memset(ChromaBufPtr, 0x80, size);
        if(dualOutputFlag)
        {
          /*------------------------------------------------------------------*/
          /* Allocation for Chroma. Check if allocation happened or not       */
          /*------------------------------------------------------------------*/
          ChromaBufPtrDual = my_Memalign (128, size * sizeof(XDAS_UInt8));
  
          if(ChromaBufPtrDual == NULL)
          {
            free(ChromaBufPtrDual);
            return -1;
          }
          /*------------------------------------------------------------------*/
          /* Fill the Buffer with gray value.                                 */
          /*------------------------------------------------------------------*/
          memset(ChromaBufPtrDual, 0x80, size);
        }
        
        nChannelState[chnlNum].buffArray[idx].buf[0] = LumaBufPtr;
        nChannelState[chnlNum].buffArray[idx].bufSize[0].bytes = 
                                                       bufSizes[0].bytes;
        nChannelState[chnlNum].buffArray[idx].buf[1] = ChromaBufPtr;
        nChannelState[chnlNum].buffArray[idx].bufSize[1].bytes = 
                                                       bufSizes[1].bytes;
        if(dualOutputFlag)
        {
          nChannelState[chnlNum].buffArray[idx].buf[2] = LumaBufPtrDual;
          nChannelState[chnlNum].buffArray[idx].bufSize[2].bytes = 
                                                         bufSizes[2].bytes;
          nChannelState[chnlNum].buffArray[idx].buf[3] = ChromaBufPtrDual;
          nChannelState[chnlNum].buffArray[idx].bufSize[3].bytes = 
                                                         bufSizes[3].bytes;
          
        }        
      }
    }

    /*------------------------------------------------------------------------*/
    /* Meta Data Buffer allocation & initialization                           */
    /*------------------------------------------------------------------------*/
    if(TestAppMetaDataBuf(bufSizes,chnlNum))
    {
      return -1;
    }
  }
  return 0;
}

/** 
********************************************************************************
 *  @fn     TestAppMetaDataBuf
 *  @brief  The TestAppMetaDataBuf function is called by the test application to
 *          initialise the Meta data buffers allocation and corresponding
 *          initializations of global buffer arrays.
 *          
 *  @param[in] bufSizes  : Address of array containing the buffer sizes of the 
 *                         numbufs.
 *  @param[in] chnlNum  : Decoder channel number.
 *          
 *  @return Success(0)/failure(-1) in allocating and initialising
********************************************************************************
*/
XDAS_Int32 TestAppMetaDataBuf(XDM2_BufSize *bufSizes,XDAS_Int8  chnlNum)
{
  XDAS_UInt32 Size;
  XDAS_UInt8 *BufPtr, metaBufIdx;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

  /*------------------------------------------------------------------------*/
  /* SEI Allocation                                                         */
  /*------------------------------------------------------------------------*/
  metaBufIdx = 2 + metaDataIndex[chnlNum][APP_SEI_DATA] + (dualOutputFlag*2);
  Size   = bufSizes[metaBufIdx].bytes;

  if(Size && metaDataEnable[chnlNum][APP_SEI_DATA])
  {
    BufPtr = my_Memalign (128, Size * sizeof(XDAS_UInt8));

    if(BufPtr == NULL)
    {
      return -1;
    }

    nChannelState[chnlNum].buffArray[0].buf[metaBufIdx]           = BufPtr;
    nChannelState[chnlNum].buffArray[0].bufSize[metaBufIdx].bytes = Size;
  }

  /*------------------------------------------------------------------------*/
  /* VUI Allocation                                                         */
  /*------------------------------------------------------------------------*/
  metaBufIdx = 2 + metaDataIndex[chnlNum][APP_VUI_DATA] + (dualOutputFlag*2);
  Size        = bufSizes[metaBufIdx].bytes;

  if(Size && metaDataEnable[chnlNum][APP_VUI_DATA])
  {
    BufPtr = my_Memalign (128, Size * sizeof(XDAS_UInt8));

    if(BufPtr == NULL)
    {
      return -1;
    }

    nChannelState[chnlNum].buffArray[0].buf[metaBufIdx]           = BufPtr;
    nChannelState[chnlNum].buffArray[0].bufSize[metaBufIdx].bytes = Size;
  }
  
  /*------------------------------------------------------------------------*/
  /* MB-Info Meta Data buffer Allocation                                    */
  /*------------------------------------------------------------------------*/
  metaBufIdx  = 2 + metaDataIndex[chnlNum][APP_MB_INFO] + (dualOutputFlag*2);
  Size        = bufSizes[metaBufIdx].bytes;

  if(Size && metaDataEnable[chnlNum][APP_MB_INFO])
  {
    BufPtr = my_Memalign (128, Size * sizeof(XDAS_UInt8));

    if(BufPtr == NULL)
    {
      return -1;
    }

    nChannelState[chnlNum].buffArray[0].buf[metaBufIdx]           = BufPtr;
    nChannelState[chnlNum].buffArray[0].bufSize[metaBufIdx].bytes = Size;
  }

  return 0;
}

/** 
********************************************************************************
 *  @fn     BUFFMGR_GetFreeBuffer
 *
 *  @brief  The BUFFMGR_GetFreeBuffer function searches for a free buffer in the 
 *          global buffer array and returns the address of that element. Incase
 *          if none of the elements are free then it returns NULL
 *  @param[in] chnlNum  : Decoder channel number.
 *
 *  @return Valid buffer element address or NULL incase if no buffers are empty
********************************************************************************
*/
BUFFMGR_buffEleHandle BUFFMGR_GetFreeBuffer(XDAS_Int8  chnlNum)
{
  XDAS_UInt32 tmpCnt;

  for(tmpCnt = 0; tmpCnt < MAX_BUFF_ELEMENTS; tmpCnt++)
  {
    /*------------------------------------------------------------------------*/
    /* Check for first empty buffer in the array and return its address       */
    /*------------------------------------------------------------------------*/
    if(nChannelState[chnlNum].buffArray[tmpCnt].bufStatus == 
        BUFFMGR_BUFFER_FREE)
    {
      /*----------------------------------------------------------------------*/
      /* The staus of the buffer may be free, but allocation might not have   */
      /* happened really                                                      */
      /* So check this condition properly for dual output as well as mono o/p.*/
      /*----------------------------------------------------------------------*/
      if((nChannelState[chnlNum].params.enableDualOutput) &&
        ((nChannelState[chnlNum].buffArray[tmpCnt].buf[0] == NULL) ||
         (nChannelState[chnlNum].buffArray[tmpCnt].buf[1] == NULL) ||
         (nChannelState[chnlNum].buffArray[tmpCnt].buf[2] == NULL) ||
         (nChannelState[chnlNum].buffArray[tmpCnt].buf[3] == NULL)))
      {
        printf("Exceeded the number of allocated buffers...\n");
        return NULL;
      }
      else if((!nChannelState[chnlNum].params.enableDualOutput) &&
             ((nChannelState[chnlNum].buffArray[tmpCnt].buf[0] == NULL) ||
              (nChannelState[chnlNum].buffArray[tmpCnt].buf[1] == NULL)))
      {
        printf("Exceeded the number of allocated buffers...\n");
        return NULL;
      }   
      else
      {
        nChannelState[chnlNum].buffArray[tmpCnt].bufStatus = 
                                                BUFFMGR_BUFFER_USED;
        return (&nChannelState[chnlNum].buffArray[tmpCnt]);
      }
    }
  }

  /*--------------------------------------------------------------------------*/
  /* Incase if no elements in the array are free then return NULL             */
  /*--------------------------------------------------------------------------*/
  return NULL;
}

/** 
********************************************************************************
 *  @fn     BUFFMGR_ReleaseBuffer
 *
 *  @brief  The BUFFMGR_ReleaseBuffer function takes an array of buffer-ids
 *          which are released by the test-app. "0" is not a valid buffer Id
 *          hence this function keeps moving until it encounters a buffer Id 
 *          as zero or it hits the MAX_BUFF_ELEMENTS
 *
 *  @param[in] bufffId : Buffer ID for releasing the buffer. 
 *
 *  @param[in] chnlNum  : Decoder channel number.
 *
 *  @return None
********************************************************************************
*/
void BUFFMGR_ReleaseBuffer(XDAS_UInt32 bufffId[],XDAS_Int8  chnlNum)
{
  XDAS_UInt32 tmpCnt, tmpId;

  for(tmpCnt = 0; (tmpCnt < MAX_BUFF_ELEMENTS); tmpCnt++)
  {
    tmpId = bufffId[tmpCnt];

    /*------------------------------------------------------------------------*/
    /* Check if the buffer Id = 0 condition has reached. zero is not a valid  */
    /* buffer Id hence that value is used to identify the end of buffer array */
    /*------------------------------------------------------------------------*/
    if(tmpId == 0)
    {
      break;
    }

    /*------------------------------------------------------------------------*/
    /* convert the buffer-Id to its corresponding index in the global array   */
    /*------------------------------------------------------------------------*/
    tmpId--;

    /*------------------------------------------------------------------------*/
    /* Set the status of the buffer to FREE                                   */
    /*------------------------------------------------------------------------*/
    nChannelState[chnlNum].buffArray[tmpId].bufStatus = BUFFMGR_BUFFER_FREE;
    nChannelState[chnlNum].bufferFreed++;
  }    

  return;
}

/** 
********************************************************************************
 *  @fn     BUFFMGR_ReleaseAllBuffers
 *
 *  @brief  The BUFFMGR_ReleaseAllBuffers function will set the status of all 
 *          buffer elements in the buffArray[] to free. This is called for cases
 *          when application does not set freebufId of all buffers typically 
 *          when stream has not finished but app wants to end decoding.
 *
 *  @param[in] chnlNum  : Decoder channel number.
 *
 *  @return None
********************************************************************************
*/
void BUFFMGR_ReleaseAllBuffers(XDAS_Int8  chnlNum)
{
  XDAS_UInt32 tmpCnt;

  for(tmpCnt = 0; (tmpCnt < MAX_BUFF_ELEMENTS); tmpCnt++)
  {
    /*------------------------------------------------------------------------*/
    /* Set the status of the buffer to FREE                                   */
    /*------------------------------------------------------------------------*/
    nChannelState[chnlNum].buffArray[tmpCnt].bufStatus = BUFFMGR_BUFFER_FREE;
  }
  return; 
}

/** 
********************************************************************************
 *  @fn     BUFFMGR_DeInit
 *
 *  @brief  The BUFFMGR_DeInit function releases all memory allocated by buffer 
 *          manager.
 *
 *  @param[in] numRefBufs : Number of buffers to be de-allocated. 
 *  @param[in] numOutBufs : Number of buffers to be de-allocated. 
 *  @param[in] chnlNum  : Decoder channel number.
 *
 *  @return None
********************************************************************************
*/
void BUFFMGR_DeInit(XDAS_Int32 numRefBufs, XDAS_Int32 numOutBufs, 
                    XDAS_Int8 chnlNum)
{
  XDAS_Int32  idx;
  XDAS_Int8  dualOutputFlag = nChannelState[chnlNum].params.enableDualOutput;

  if(dualOutputFlag == IH264VDEC_DUALOUTPUTALIGN_ENABLE)
    dualOutputFlag -= 1;

  /*--------------------------------------------------------------------------*/
  /*  Freeing up all the Buffers                                              */
  /*--------------------------------------------------------------------------*/
  if (nChannelState[chnlNum].params.viddec3Params.maxWidth > 2048 || 
                  nChannelState[chnlNum].params.viddec3Params.maxHeight > 2048)
  {
    /* nothing to do */
  }
  else
  {
    for(idx = 0; idx < numRefBufs; idx++)
    {
      free((void *)nChannelState[chnlNum].buffArray[idx].buf[0]);
      free((void *)nChannelState[chnlNum].buffArray[idx].buf[1]);
      if(dualOutputFlag)
      {   
        free((void *)nChannelState[chnlNum].buffArray[idx].buf[2]);
        free((void *)nChannelState[chnlNum].buffArray[idx].buf[3]);
      }
    }
  }

  /*--------------------------------------------------------------------------*/
  /*  Freeing up meta data Buffers                                            */
  /*--------------------------------------------------------------------------*/
  if(metaDataEnable[chnlNum][APP_SEI_DATA])
  {  
    free((void *)nChannelState[chnlNum].buffArray[0].buf[2 + (dualOutputFlag*2)
                 + metaDataIndex[chnlNum][APP_SEI_DATA]]);
  }

  if(metaDataEnable[chnlNum][APP_VUI_DATA])
  {
    free((void *)nChannelState[chnlNum].buffArray[0].buf[2 + (dualOutputFlag*2)
                 + metaDataIndex[chnlNum][APP_VUI_DATA]]);
  }

  if(metaDataEnable[chnlNum][APP_MB_INFO])
  {
    free((void *)nChannelState[chnlNum].buffArray[0].buf[2 + (dualOutputFlag*2)
                 + metaDataIndex[chnlNum][APP_MB_INFO]]);
  }

  return;
}

/** 
********************************************************************************
 *  @fn     testAppTilerInit
 *
 *  @brief  The testAppTilerInit function initializes & chunks the TILER 
 *          memory into required number with required 2D block sizes.
 *
 *  @param[in] bufSizes  : Address of array containing the buffer sizes of the 
 *                         numbufs.
 *  @param[in] chnlNum  : Decoder channel number.
 *
 *  @return None
********************************************************************************
*/
XDAS_Void testAppTilerInit(XDM2_BufSize *bufSizes, XDAS_Int8  chnlNum)
{
  XDAS_Int8    ret_val;
  /*-----------------------------------------------------------------------*/
  /*  Get the buffers in TILER space                                       */
  /*-----------------------------------------------------------------------*/
  if(nChannelState[chnlNum].appCntrlParams.tilerEnable)
  {
    /*---------------------------------------------------------------------*/
    /* Get the buffers in TILER space                                      */
    /* Do the allocation for maximum supported resoultion and keep to some */
    /* aligned boundary. Also this allocation assumes that tiled8 and      */
    /* tiled16 are mapped to same physical space                           */
    /*---------------------------------------------------------------------*/
    sTilerParams *pTilerParams     = &tilerParams;
    SetPATViewMapBase();
    pTilerParams->tilerSpace[0]    = CONTAINER_8BITS;
    pTilerParams->tilerSpace[1]    = CONTAINER_16BITS;
    if(nChannelState[chnlNum].appCntrlParams.chromaTilerMode)
    {
      pTilerParams->tilerSpace[1]  = CONTAINER_8BITS;
    }

    pTilerParams->imageDim[0]      = bufSizes[0].tileMem.width;
    pTilerParams->imageDim[1]      = bufSizes[0].tileMem.height;
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
      nChannelState[chnlNum].appCntrlParams.tilerEnable = 0;
    }
  }
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
  /*-------------------------------------------------------------------*/
  /* The default values set in gel files is 0x8000000 which will       */
  /* overlap on the .text mapped in client. Hence, to avoid corruption */
  /* of vital memory we are mapping the tiler base address to a        */
  /* different value.                                                  */
  /*-------------------------------------------------------------------*/
#ifdef NETRA
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
#else 
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
