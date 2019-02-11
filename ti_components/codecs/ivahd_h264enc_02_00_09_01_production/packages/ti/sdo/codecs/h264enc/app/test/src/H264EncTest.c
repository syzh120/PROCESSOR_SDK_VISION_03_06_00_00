/*
********************************************************************************
* HDVICP2.0 Based H.264 HP Encoder
*
* "HDVICP2.0 Based H.264 HP Encoder" is software module developed on TI's
*  HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw
*  video into a high/main/baseline profile bit-stream. Based on ISO/IEC
*  14496-10."
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/


/**
********************************************************************************
* @file H264EncTest.c
*
* @brief This is top level client file IVAHD H264 encoder
*
*        This is the top level client file that drives the H264
*        Video Encoder Call using XDM v2.0 Interface
*
* @author: Pramod Swami (pramods@ti.com)
*
* @version 0.0(Jan 2008) : Base version created
*                          [Pramod]
* @version 0.1(Oct 2009) : Review and more commenting along with cleanup
*                          [Rama Mohan]
* @version 0.2(Feb 2010) : Correction in YUV resding for interlace flow and
*                          top field first case and 30 process call .
* @version 0.3(Feb 2010) : Added code to test frame dynamic parameter
*                          updation support using control call
* @version 0.4(April 2010): Added code to support better handling of meta
*                           data planes [Deepak Poddar]
* @version 0.5(April 2010): Support of tiler buffer control [Pramod]
* @version 0.6(April 2010): Added trace file handle check [Nirmal]
* @version 0.7(April 2010): Added check to make sure HDVICP is released[Nirmal]
* @version 0.8(May 2010) : Added Init file IO function call [Nirmal]
* @version 0.9(May 2010) : Support of IVAHD sub system selection[Nirmal]
* @version 1.0(May 2010) : Fixed bug related to frame height calculation
*                          for Tiler_DataMove() in case of interlaced[Nirmal]
* @version 1.1(Jun 2010) : Changed input buffer start address allignment from
*                          32 to 1 byte to check the support of unaligned
*                          input buffer[Nirmal, Pramod]  ECN: TIDSP00012391
* @version 1.2(July 2010) : Changes related to MV & SAD exposure
*                            support[Nirmal]
* @version 1.3(Apr 2010) : added support for the start frame and feeding in
*                          the initial buffer level. [uday]
* @version 1.4(July 2010) :Modication for Bitstream writing module for
*                          for low delay setting. Added Support for gap between
*                          buffers provided through getBuf calls.
* @version 1.5(Aug 2010) : Added support of testing dynamic parameter change
*                          at runtime [Nirmal]
* @version 1.6(Sep 2010) :  Added support for long term reference frame
* @version 1.7(Dec 2010) :  Adding Support Dump trace data
* @version 1.8(Dec 2010) : Cleanup related to platform specific macros
* @version 1.9(Dec 2010) : Added start code insertion to test NAL stream
*                           format test cases.
* @version 2.0 (Apr 2011):  Enhancement for Long Term Reference Picture
*                           mechnism (SDOCM00080209) [Kumar]
* @version 2.1(July 2011): ROI algorithm implementation (Gajanan Ambi)
* @version 2.2(Feb 2012) : Fixes done for situation when 2nd field offset is 
*                           negative[Deepak]  
* @version 2.3(Mar 2012) : 1.Code Modifications done to avoid Generating-
*                            Only-Header,if IDR is requested for that Frame  
*                          2.Proper close of the waterMar Input key file
*                            [Santoshkumar S K]  
* @version 2.4(Apr 2012) : code clean up [Santoshkumar S K]
* @version 2.4(May 2012) : Fix for compliance fail scenario. Encoder 
*                          used to be in infinite loop, if the compliace 
*                          is ON and the encoded stream doesn't match 
*                          the reference stream.[Gajanan Ambi]
* @version 2.5(Sep 2012) : Modifications done for Recont Dump [Gajanan]
* @version 2.6(Mar 2013) : Code modifications to fix SDOCM00099577(Encoder 
*                          does not give refined error codes in case of creation
*                          fail or run time parameter set fail) [Santosh]
********************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include <xdc/std.h>
#include <h264enc_ti.h>
#include <ti/xdais/dm/ividenc2.h>
#include <ti/xdais/xdas.h>
#include "buffermanager.h"
#include <h264enc.h>
#include <h264enc_ti_test.h>
#include <h264enc_ti_config.h>
#include "H264BPEnc_rman_config.h"
#include <h264enc_ti_file_io.h>
#include "tilerBuf.h"
FILE *fin[MAX_ITEMS_TO_RUN], *fout[MAX_ITEMS_TO_RUN],
                   *ReconFile[MAX_ITEMS_TO_RUN],*pfOutYUVFile[MAX_ITEMS_TO_RUN];
/*----------------------------------------------------------------------------*/
/*   Lenth of Boot code                                                       */
/*----------------------------------------------------------------------------*/
#define LENGTH_BOOT_CODE  14

/**
*  Macro to set sizes of Base Class Objects
*/
/* #define BASE_CLASS                                                         */
#define COMPARE_OUTPUT
/**
*  Macro to have the pattern to fill the extended class objects while testing
*  base class objects
*/
#define PATTERN_FILL_EXT    0xFF

/**
 * Macro to enable testing of providing second field input data with
 * negative offset. This is applicable for interlace 30 process call,
 * IVIDEO_FIELD_SEPARATED mode.
 */
/* #define SECONDFIELD_NEG_OFFSET_TEST */

/*----------------------------------------------------------------------------*/
/*   Hex code to set for Stack setting, Interrupt vector setting              */
/*   and instruction to put ICONT in WFI mode.                                */
/*   This shall be placed at TCM_BASE_ADDRESS of given IVAHD, which is        */
/*   0x0000 locally after reset.                                              */
/*----------------------------------------------------------------------------*/

const unsigned int IVAHD_memory_wfi[LENGTH_BOOT_CODE] = {
  0xEA000006,
  0xEAFFFFFE,
  0xEAFFFFFE,
  0xEAFFFFFE,
  0xEAFFFFFE,
  0xEAFFFFFE,
  0xEAFFFFFE,
  0xEAFFFFFE,
  0xE3A00000,
  0xEE070F9A,
  0xEE070F90,
  0xE3A00000,
  0xEAFFFFFE,
  0xEAFFFFF1
};

XDAS_Int32 gAlgExtendedError[MAX_ITEMS_TO_RUN];
XDAS_Int32 gVbvBufLevel[MAX_ITEMS_TO_RUN];
XDAS_Int32 chanEndReached[MAX_ITEMS_TO_RUN];

/*----------------------------------------------------------------------------*/
/*  Output Bitstream Buffer                                                   */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(gOutputData, ".bitStream_sect");
volatile XDAS_UInt8 gOutputData[MAX_ITEMS_TO_RUN][OUTPUT_BUFFER_SIZE];

/*----------------------------------------------------------------------------*/
/* Output Blocks sizes provided through putDataFxn()                          */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(gBlockSizes, ".bitStream_sect");
XDAS_Int32 gBlockSizes[MAX_ITEMS_TO_RUN][TOT_BLOCKS_IN_PROCESS];
/*----------------------------------------------------------------------------*/
/* Output Blocks izes provided through putDataFxn()                           */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(gBlockAddr, ".bitStream_sect");
XDAS_Int32 gBlockAddr[MAX_ITEMS_TO_RUN][TOT_BLOCKS_IN_PROCESS];
/*----------------------------------------------------------------------------*/
/* Total number of blocks recieved in each process call through putDataFxn()  */
/*----------------------------------------------------------------------------*/
XDAS_Int32 gOutputBlocksRecieved[MAX_ITEMS_TO_RUN];

XDAS_Int32 gInitialDataUnit;
XDAS_Int32 gDataSynchUnit;
/*----------------------------------------------------------------------------*/
/*  Gap between two data synch units                                          */
/*----------------------------------------------------------------------------*/
XDAS_Int32 gDataSyncUnitGap[MAX_ITEMS_TO_RUN];

/*----------------------------------------------------------------------------*/
/*  Analytic info output buffer                                               */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(gAnalyticInfoOutputData, ".analyticinfo_sect");
XDAS_UInt8 gAnalyticInfoOutputData[MAX_ITEMS_TO_RUN]
                                                [ANALYTICINFO_OUTPUT_BUFF_SIZE];

/*----------------------------------------------------------------------------*/
/* Varible holding data fed to the encoder, helps for DATA sync APIs          */
/*----------------------------------------------------------------------------*/
XDAS_UInt32 gOutputDataProvided[MAX_ITEMS_TO_RUN];

XDAS_Int32  numFramesEncoded[MAX_ITEMS_TO_RUN];

/*----------------------------------------------------------------------------*/
/* Varible used to change dynamic parameter at runtime                        */
/*----------------------------------------------------------------------------*/
XDAS_Int32 stopPos[MAX_ITEMS_TO_RUN];
/*---------------------------------------------------------------------------*/
/* Counter for setting Codec Type                                            */
/*---------------------------------------------------------------------------*/
extern Uint32 FrameNum[MAX_ITEMS_TO_RUN];
/*----------------------------------------------------------------------------*/
/* Input data handles, we define 2 just to check some robust ness             */
/*----------------------------------------------------------------------------*/
extern XDM_DataSyncHandle fGetInpDHandle1;
extern XDM_DataSyncHandle fGetInpDHandle2;

extern XDAS_UInt8 InBuffers[];
extern XDAS_UInt8 *InbufPtr;
extern const short h264e_host_scalingMatrix[];
sTilerParams TilerParams;
extern sProfileData profileData[MAX_ITEMS_TO_RUN];
extern IALG_Handle g_handle_last;

/*----------------------------------------------------------------------------*/
/* Structure to hold Cannon user data which is used for encoding Unregistred  */
/* user data SEI message                                                      */
/*----------------------------------------------------------------------------*/
#pragma DATA_SECTION(CameraUserDataUnReg, ".UserDataUnRegSect");
const XDAS_UInt8 CameraUserDataUnReg[] =
{
  56, 00, 00, 00,
  /*uuid_iso_iec_11578 */
  0x17, 0xEE, 0x8C, 0x60, 0xf8, 0x4d, 0x11, 0xd9,
  0x8c, 0xD6, 0x08, 0x00, 0x20, 0x0C, 0x9a, 0x66,
  0x4D, 0x44, 0x50, 0x4D,                         /*TypeIndicator*/
  0x07,                                           /*number_of_modified_
  dv_pack_entries */
  0x18,                                           /* mdp_id */
  0x12, 0x20, 0x07, 0x07,                         /* mp_data */
  0x19,                                           /* mdp_id */
  0x29, 0x12, 0x10, 0x58,                         /* mp_data */
  0x70,                                           /* mdp_id */
  0x10, 0xF1, 0xFF, 0xFF,                         /* mp_data */
  0x71,                                           /* mdp_id */
  0x3F, 0xFF, 0xFF, 0xFF,                         /* mp_data */
  0x7F,                                           /* mdp_id */
  0x00, 0x00, 0x19, 0x01,                         /* mp_data */
  0xE0,                                           /* mdp_id */
  0x10, 0x11, 0x20, 0x00,                         /* mp_data */
  0xE1,                                           /* mdp_id */
  0x00, 0x1F, 0xFF, 0xFF,                         /* mp_data */
};
/*----------------------------------------------------------------------------*/
/* Global instance parameters                                                 */
/*----------------------------------------------------------------------------*/
XDAS_UInt32   insChanid = 0;
h264BPEncConfig            gConfig[MAX_ITEMS_TO_RUN];
H264ENC_Params             gParams[MAX_ITEMS_TO_RUN];
H264ENC_DynamicParams      gDynamicParams[MAX_ITEMS_TO_RUN];
IVIDEO2_BufDesc            gInputBufDesc[MAX_ITEMS_TO_RUN];
IH264ENC_InArgs            gInArgs[MAX_ITEMS_TO_RUN];
extern h264BPEncConfig            gConfigOrg;
extern H264ENC_Params             gParamsOrg;
extern H264ENC_DynamicParams      gDynamicParamsOrg;
extern IVIDEO2_BufDesc            gInputBufDescOrg;
extern IH264ENC_InArgs            gInArgsOrg;

#ifdef TIGHTER_RC_DEBUG
/*----------------------------------------------------------------------------*/
/* Trace routine function defination                                          */
/*----------------------------------------------------------------------------*/
void H264ENC_TI_RateCtrlDump();
#endif

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
#define BITSTREAM_SUBFRAME_SYNC
XDAS_Int32 IVAHD_Standby_power_on_uboot()
{

  unsigned int length =0;
  /*--------------------------------------------------------------------------*/
  /* Assigment of pointers                                                    */
  /* A generic code shall take all address as input parameters                */
  /*--------------------------------------------------------------------------*/
  volatile unsigned int *prcm_ivahd_icont_rst_cntl_addr =
    (unsigned int *)RST_CNTL_BASE;
  volatile unsigned int *icont1_itcm_base_addr =
    (unsigned int *)(REG_BASE + ICONT1_ITCM_OFFSET);
  volatile unsigned int *icont2_itcm_base_addr =
    (unsigned int *)(REG_BASE + ICONT2_ITCM_OFFSET);
  /*--------------------------------------------------------------------------*/
  /* Set IVAHD in reset mode to enable downloading of boot code               */
  /* Please note that this state can be SKIPPED if IVAHD is alredy in reset   */
  /* state during uboot and reset is not de-asserted                          */
  /* Set bit0 to 1 to put ICONT1 in reset state                               */
  /* Set bit1 to 1 to put ICONT2 in reset state                               */
  /*--------------------------------------------------------------------------*/
  *prcm_ivahd_icont_rst_cntl_addr |=  0x00000003;

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
  *prcm_ivahd_icont_rst_cntl_addr &=  0xFFFFFFFC;

  /*--------------------------------------------------------------------------*/
  /* As ICONT goes in WFI and there are no pending VDMA transction            */
  /* entire IVAHD will be go in standby mode and PRCM will fully control      */
  /* further managment of IVAHD power state                                   */
  /*--------------------------------------------------------------------------*/

  return (1);
}

#pragma DATA_SECTION(RawLuma,   ".RawInput");
#pragma DATA_SECTION(RawChroma, ".RawInput");
XDAS_UInt8 RawLuma[2048*1256];
XDAS_UInt8 RawChroma[2048*(1256/2)];

/**
********************************************************************************
*  @fn     TestApp_ReadInputYUVData
*  @brief  Reads the entire frame/field data which is needed for one process
*          call
*
*  @param[in]  inputBuf : Pointer to input buffer discriptors
*
*  @param[in]  frmWidth : buffer width
*
*  @param[in]  frmHeight : buffer Height
*
*  @param[in]  dataLayout : flag to tell whether input data fields are in
*                           are in field interleaved or seperated
*
*  @param[in]  frameCount : Total number of frames encoded till now
*                           Used to calculate offset in input file
*
*  @param[in]  botFieldFirst : Type of encoding in frame in case of interlace
*                              Whether Top field is encoded first or bottom
*                              field
*
*  @param[in]  fin : File pointer to the input file
*
*  @return     -1 in case of error
*               0 in case when there is not error
********************************************************************************
*/

XDAS_Int16 TestApp_ReadInputYUVData( IVIDEO2_BufDesc *inputBuf,
                                    XDAS_Int32 frameCount,
                                    FILE * fin,
                                    XDAS_UInt8 lumaTilerSpace,
                                    XDAS_UInt8 chromaTilerSpace,
                                    XDAS_UInt32 insChanid)
{

  XDAS_Int32 pic_size;
  XDAS_UInt8 *dst,botFieldFirst;
  XDAS_Int8 fieldOffset = 0;
  XDAS_Int16 frmWidth,frmHeight;
  XDAS_UInt16 dataLayout;
  XDAS_UInt32 fileSize;
  XDAS_UInt32 NumframesInfile;
  XDAS_UInt32 numFields, fieldNo ;
  XDAS_Int32 fieldOffsetLuma   ;
  XDAS_Int32 fieldOffsetChroma ;

  XDAS_UInt8 *pLuma    ;
  XDAS_UInt8 *pChroma  ;
  XDAS_UInt32 BytesRead = 0;


  frmWidth = inputBuf->imageRegion.bottomRight.x;
  frmHeight = inputBuf->imageRegion.bottomRight.y;
  dataLayout = inputBuf->dataLayout;
  botFieldFirst = !inputBuf->topFieldFirstFlag;
  botFieldFirst = (!inputBuf->topFieldFirstFlag) &&
    (inputBuf->contentType == IVIDEO_INTERLACED);

  /*----------------------------------------------------------------------*/
  /* Calculating the Num frames in the YUV file and over writing on the   */
  /* gConfig.numInputDataUnits to avoid any file IO isses                 */
  /*----------------------------------------------------------------------*/
  if(frameCount == 0)
  {
    fileSize        = TestApp_FileLength(fin);
    NumframesInfile = (fileSize / ((3 * frmWidth * frmHeight) >> 1));
    if(inputBuf->contentType == IVIDEO_INTERLACED)
    {
      NumframesInfile >>= 1;
    }
    if(gConfig[insChanid].numInputDataUnits > NumframesInfile)
    {
      gConfig[insChanid].numInputDataUnits = NumframesInfile;
    }
    if(gConfig[insChanid].numProcessCall == 60)
    {
      gConfig[insChanid].numInputDataUnits *= 2;
    }
  }

  /*--------------------------------------------------------*/
  /* For tiled buffer first read into some temporary buffer */
  /*--------------------------------------------------------*/
  if(lumaTilerSpace)
  {
    pLuma   = RawLuma   ;
  }
  else
  {
    pLuma   = (XDAS_UInt8 *) inputBuf->planeDesc[0].buf ;
  }

  if(chromaTilerSpace)
  {
    pChroma = RawChroma ;
  }
  else
  {
    pChroma = (XDAS_UInt8 *) inputBuf->planeDesc[1].buf ;
  }

  /*--------------------------------------------------------------------------*/
  /*  In case of field interleaved format we need to consider twice the height*/
  /*  of the buffer as "frmHeight" represents height of the field             */
  /*--------------------------------------------------------------------------*/
  if((inputBuf->contentType == IVIDEO_INTERLACED) &&
    (dataLayout == IVIDEO_FIELD_INTERLEAVED))
  {
    frmHeight <<= 1;
  }
  /*--------------------------------------------------------------------------*/
  /*                        Size of the picture to be read                    */
  /*--------------------------------------------------------------------------*/
  pic_size = (3 * frmWidth * frmHeight) >> 1;
  /*--------------------------------------------------------------------------*/
  /*In the case of the bottom field first and field seperated YUV we need to  */
  /*capture first the bottom filed and than top field. In this situation we   */
  /*can provide the second field offset or not. If the second field offset is */
  /*provided than it will be 30 process call scenario, and both the field will*/
  /*captured in single process call. So inputBufdsc will point to the bottom  */
  /*field data and second field offset will help in getting second field (top */
  /*field) data.                                                              */
  /*If it is 60 process call scenario ( when second field offset is not set by*/
  /*the user) than in each process call we will be providing one field of data*/
  /*In odd number process call we will have to provide bottom field data and  */
  /*in even numbered process call we will have to provide top field data.     */
  /*--------------------------------------------------------------------------*/
  if(botFieldFirst && (dataLayout == IVIDEO_FIELD_SEPARATED)&&
    (inputBuf->contentType == IVIDEO_INTERLACED) )
  {
    if(((frameCount & 0x1) == 0) || (gConfig[insChanid].numProcessCall == 30))
    {
      fieldOffset = 1;
    }
    else
    {
      fieldOffset = -1;
    }
  }

  if(gConfig[insChanid].numProcessCall != 60 &&
     (dataLayout == IVIDEO_FIELD_SEPARATED) &&
     (inputBuf->contentType == IVIDEO_INTERLACED))
  {
    /* Not 60 process call and data layout = 1 and interlaced */
    numFields         =  2 ;
    fieldOffsetLuma   =
      inputBuf->secondFieldOffsetHeight[0] * frmWidth +
      inputBuf->secondFieldOffsetWidth[0] ;
    fieldOffsetChroma =
      inputBuf->secondFieldOffsetHeight[1] * frmWidth +
      inputBuf->secondFieldOffsetWidth[1] ;
#ifdef SECONDFIELD_NEG_OFFSET_TEST
    if((frameCount & 0x1))
    {
      inputBuf->planeDesc[0].buf += 
        inputBuf->secondFieldOffsetHeight[0]* frmWidth + 0x100;
      inputBuf->planeDesc[1].buf += 
        inputBuf->secondFieldOffsetHeight[1] * frmWidth + 0x200;

      pLuma             = (XDAS_UInt8 *) inputBuf->planeDesc[0].buf;
      pChroma           = (XDAS_UInt8 *) inputBuf->planeDesc[1].buf;

      fieldOffsetLuma    =
                      - (inputBuf->secondFieldOffsetHeight[0]*frmWidth + 0x100);
      fieldOffsetChroma  =
                      - (inputBuf->secondFieldOffsetHeight[1]*frmWidth + 0x100);

      inputBuf->secondFieldOffsetHeight[0] =
                                        -(inputBuf->secondFieldOffsetHeight[0]);
      inputBuf->secondFieldOffsetWidth[0]  = -0x100;

      inputBuf->secondFieldOffsetHeight[1] =
                                        -(inputBuf->secondFieldOffsetHeight[1]);
      inputBuf->secondFieldOffsetWidth[1]  = -0x100;

    }
#endif
    /*------------------------------------------------------------------------*/
    /* Seek to the excact offset in the file                                  */
    /*------------------------------------------------------------------------*/
    /* my_fseek(fin, 2*pic_size * (frameCount), SEEK_SET);                    */
  }
  else
  {
    /*------------------------------------------------------------------------*/
    /* Seek to the excact offset in the file                                  */
    /*------------------------------------------------------------------------*/
    /* my_fseek(fin, pic_size * (frameCount + fieldOffset), SEEK_SET);        */
    numFields       = 1 ;
  }

  /* numFields = 0;                                                           */
  for(fieldNo = 0 ; fieldNo < numFields ; fieldNo++)
  {
    my_fseek(fin, pic_size * (numFields * frameCount + fieldOffset), SEEK_SET);
    if(botFieldFirst)
    {
      fieldOffset = 0;
    }
    else
    {
      fieldOffset = 1;
    }

    /*------------------------------------------------------------------------*/
    /*   Update pointer to luma input buffer read data                        */
    /*------------------------------------------------------------------------*/
    dst = (XDAS_UInt8 *) pLuma + fieldNo * fieldOffsetLuma;
    BytesRead = 
            my_fread((char *)dst, sizeof(XDAS_UInt8), (frmWidth*frmHeight),fin);
    if(BytesRead != (frmWidth*frmHeight))
    {
      return -1;
    }
   /*-------------------------------------------------------------------------*/
   /*   Update pointer to chroma input buffer and read data                   */
   /*-------------------------------------------------------------------------*/
    dst = (XDAS_UInt8*) pChroma + fieldNo * fieldOffsetChroma;
    BytesRead =
          my_fread((char*)dst, sizeof(XDAS_UInt8), (frmWidth*frmHeight>>1),fin);
    if(BytesRead != (frmWidth*frmHeight >>1))
    {
      return -1;
    }
  }

  if(lumaTilerSpace)
  {
    Tiler_DataMove((char *)RawLuma,
      (char *)gInputBufDesc[insChanid].planeDesc[0].buf,frmWidth,
      frmHeight*numFields,
      lumaTilerSpace);
  }

  if(chromaTilerSpace)
  {
    Tiler_DataMove((char *)RawChroma,
      (char *)gInputBufDesc[insChanid].planeDesc[1].buf,frmWidth,
      (frmHeight/2)*numFields,
      chromaTilerSpace);
  }

  return 0;
}

/**
********************************************************************************
*  @fn     TestApp_InsertStartCode
*  @brief  This function inserts the 4 byte start code at the beginning of
*          every slice in case of NAL stream format encoding for bitstream
*          verification
*
*  @param[in]  src : Pointer to output data sync unit
*
*  @return     None
********************************************************************************
*/
void TestApp_InsertStartCode(XDAS_Int8 *src, XDAS_UInt32 insChanid)
{
  *((XDAS_Int32*)(src - gDataSyncUnitGap[insChanid]) )= 0x01000000;
}

/**
********************************************************************************
*  @fn     TestApp_WriteOutputData
*  @brief  This function writes encoded frame data into the output file
*
*  @param[in]  outputBuf : Pointer to output buffer
*
*  @param[in]  uiBytesToWrite : Total number of bytes to be written
*
*  @param[in]  fout : File pointer to the output file
*
*  @return     -1 in case of error
*               0 in case when there is no error
********************************************************************************
*/
/* TODO : Need to relook into return value once my_fwrite is done*/
XDAS_Int16 TestApp_WriteOutputData(XDAS_Int8 *src,
                                   XDAS_Int32 uiBytesToWrite,
                                   FILE *fout, XDAS_Int32 outputDataMode,
                                   XDAS_Int32 outputDataUnit,
                                   XDAS_Int32 streamFormat,
                                   XDAS_UInt32 insChanid )
{
  XDAS_Int32 remainingBytes = uiBytesToWrite;
  XDAS_Int32 totBlocks;
  XDAS_Int32 i,j;
  XDAS_Int8 startCode[4] = {0x0,0x0,0x0,0x1};

  if(outputDataMode == IVIDEO_ENTIREFRAME)
  {
    /*---------------------------------------------------------------*/
    /* Total number of blocks provided through getBufFxn             */
    /*---------------------------------------------------------------*/
    totBlocks = (uiBytesToWrite - gInitialDataUnit)/(gDataSynchUnit);
    if(totBlocks <= 0)
    {
      /*-------------------------------------------------------------*/
      /* Negative value of this indicates no block is provided through*/
      /* getBufFxn                                                   */
      /*-------------------------------------------------------------*/
      totBlocks      = 0;
    }
    {
      uiBytesToWrite = (gInitialDataUnit < uiBytesToWrite) ?
                                    gInitialDataUnit : uiBytesToWrite;
    }
    /*---------------------------------------------------------------- */
    /* Total transfer constitute of mainly 3 transfers , first trf     */
    /* of INITIAL_DATA_UNIT, if totBlocks is positive. Second transfer */
    /* of totBlocks each of size DATA_SYNCH_UNIT. ANd 3rd transfer as  */
    /* portion of last block. if totBlocks is zero then there will be  */
    /* only one transfer of size uiBytesToWrite                        */
    /*-----------------------------------------------------------------*/

    /*-----------------------------------------------------------------*/
    /* #1st transfer ~~~~~~~~~~~~~~~~                                  */
    /*-----------------------------------------------------------------*/
    if(uiBytesToWrite > 0)
    {
      my_fwrite((const char *)src, 1, uiBytesToWrite, fout);
      src += (uiBytesToWrite + gDataSyncUnitGap[insChanid]);
    }
    remainingBytes -=  uiBytesToWrite;
    uiBytesToWrite  =  gDataSynchUnit;
    /*-----------------------------------------------------------------*/
    /* #2nd transfer ~~~~~~~~~~~~~~~~                                  */
    /*-----------------------------------------------------------------*/
    for(i = 0; i < totBlocks; i++)
    {
      my_fwrite((const char *)src, 1, uiBytesToWrite, fout);
      src            += (uiBytesToWrite + gDataSyncUnitGap[insChanid]);
      remainingBytes -= gDataSynchUnit;
    }
    /*-----------------------------------------------------------------*/
    /* #3rd transfer ~~~~~~~~~~~~~~~~                                  */
    /*-----------------------------------------------------------------*/
    if(remainingBytes > 0)
    {
      my_fwrite((const char *)src, 1, remainingBytes, fout);
    }
  }
  else
  {
    for(i = 0; i < (gOutputBlocksRecieved[insChanid]); i++)
    {
      uiBytesToWrite   = gBlockSizes[insChanid][i];
      src              = (XDAS_Int8*)(gBlockAddr[insChanid][i]);

      if(outputDataMode == IVIDEO_SLICEMODE)
      {

#ifdef NALSTREAM_TESTING
        /*---------------------------------------------------------------*/
        /* In case of NALU stream format, the start code is inserted     */
        /* at the gap in the data sync units (gDataSyncUnitGap)          */
        /*---------------------------------------------------------------*/
        if(streamFormat == IH264_NALU_STREAM)
        {
          TestApp_InsertStartCode(src,insChanid);
          src -= gDataSyncUnitGap[insChanid];
        }
#endif /* #ifdef NALSTREAM_TESTING */

        for (j=0 ; j<4 ; j++)
        {
          if(startCode[j] != ((XDAS_Int8*)src)[j])
            break;
        }
        if(j != 0x4)
        {
          printf("\n Start code not found in this NAL");
        }

      }
      if(outputDataMode == IVIDEO_FIXEDLENGTH)
      {
        if(gBlockSizes[insChanid][i] > outputDataUnit * 1024)
        {
          printf("\n Block Size is larger than expected");
        }
      }
#ifdef NALSTREAM_TESTING
      my_fwrite((const char *)src, 1,
             (uiBytesToWrite + gDataSyncUnitGap[insChanid]) , fout);
#else
      my_fwrite((const char *)src, 1, (uiBytesToWrite) , fout);
#endif
      remainingBytes  -= uiBytesToWrite;
    }
    if(gBlockSizes[insChanid][gOutputBlocksRecieved[insChanid]] != 0x1)
    {
      printf("\n Last NAL is still not recieved");
      while(1);
    }
    if((remainingBytes != 0) && (gOutputBlocksRecieved[insChanid] > 0))
    {
      printf("\n Error in BitsStream writing into the file");
    }
  }
  return 0;
}

/**
********************************************************************************
*  @fn     TestApp_CompareOutputData
*  @brief  This function will compare the output generated data to ref data
*
*  @param[in]  fRefFile : File pointer to the ref data
*
*  @param[in]  outputBufDesc : Output buffer discriptors containing encoded
*                              data buffer pointers
*
*  @param[in]  size : Size of the encoded bytes
*
*  @return     -1 in case of error
*               0 in case when there is no error
********************************************************************************
*/

XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,
                                     XDM2_BufDesc *outputBufDesc,
                                     XDAS_Int32 size)
{
  XDAS_Int32 i,retVal;
  XDAS_UInt8 *refData;
  retVal = IVIDENC2_EOK;

  /*--------------------------------------------------------------------------*/
  /*   Allocate memory for the refdata with the size given                    */
  /*--------------------------------------------------------------------------*/
  refData = malloc(size + 32);

  /*--------------------------------------------------------------------------*/
  /* Compare all the output Buffers with the ref File                         */
  /*--------------------------------------------------------------------------*/
  for(i=0; i < outputBufDesc->numBufs ; i++)
  {
    fread(refData, 1, size, fRefFile);
    if(memcmp(refData, outputBufDesc->descs[i].buf, size))
    {
      retVal = IVIDENC2_EFAIL;
    }
    break ;
  }

  free(refData);
  return retVal;
}

/*===========================================================================*/
/**
*@brief This function converts the frame/field data to the raster-scan format.
*
*@param  pubYFrameData
*        Pointer to the Y component of the raster-scan frame.
*
*@param  pubUFrameData
*        Pointer to the U component of the raster-scan frame.
*
*@param  pubVFrameData
*        Pointer to the V component of the raster-scan frame.
*
*@param  pubPictY[2]
*        Pointer to the Luminance (Y) component of the picture for both
*        fields. Populate only the first element for frame data
*
*@param  pubPictUV[2]
*        Pointer to the Chrominance (UV) component of the picture for both
*        fields. populate only the first element for frame data
*
*@param  uiPicWidth
*        Width of the input picture.
*
*@param  uiPicHeight
*        Heigth of the input picture.
*
*@param  uiReconPitch,
*        Pitch of the reconstructed image from encoder
*
*@param  ubIsField
*        Flag to indicate wherther to separate the data into two different
*        fields or not (0 : Frame data / 1 : Field).
*
*@return None
*
*@see    None
*
*@note   None
*/
/*===========================================================================*/

void ConvertFrame_Field_Out(
                            unsigned char *pubYFrameData,
                            unsigned char *pubUFrameData,
                            unsigned char *pubVFrameData,
                            unsigned char *pubPictY[2],
                            unsigned char *pubPictUV[2],
                            unsigned int uiPictWidth,
                            unsigned int uiPictHeight,
                            unsigned int uiReconPitch,
                            unsigned char ubIsField
                            )
{
  /*  Variables declared here                                                 */
  unsigned short j,k;
  unsigned char *pubSrc[2],*PubSrc_field;
  unsigned char *pubDstY, *pubDstU, *pubDstV;
  unsigned char ubIdx = 0;
  unsigned int uiRecWidth;

  /*  Code starts here                                                       */
  /*-------------------------------------------------------------------------*/
  /*                           CONVERT LUMINANCE DATA                        */
  /*-------------------------------------------------------------------------*/
  pubSrc[0] = pubPictY[0] + (32 * uiReconPitch);



  uiRecWidth = uiReconPitch;

  ubIdx = 0;

  for(j = 0; j < uiPictHeight; j++)
  {


    pubDstY = pubYFrameData + j * (uiPictWidth << ubIsField );

    memcpy(pubDstY, pubSrc[ubIdx], uiPictWidth);

    if(ubIsField)
    {
      PubSrc_field = pubSrc[ubIdx]+ uiReconPitch *(uiPictHeight + 64);
      pubDstY = pubDstY + uiPictWidth;
      memcpy(pubDstY, PubSrc_field, uiPictWidth);
    }


    /*  Update the destination pointer                                       */
    pubSrc[ubIdx] += uiRecWidth;                                         
  }/*  0 - uiPictHeight                                                      */

  /*-------------------------------------------------------------------------*/
  /*                           CONVERT CHROMINANCE DATA                      */
  /*-------------------------------------------------------------------------*/
  /* Subtracting 4 from luma horizontal pitch since currently the            */
  /* luma/chroma pitches are not same                                        */
  /*-------------------------------------------------------------------------*/
  /* uiRecWidth = uiReconPitch-4;                                            */
  uiPictHeight >>= 1;
  uiPictWidth >>= 1;

  pubSrc[0] = pubPictUV[0] + (16 * uiReconPitch);

  ubIdx = 0;

  for(j = 0; j < uiPictHeight; j++)
  {
    unsigned char *pubCurSrc;

    pubDstU = pubUFrameData + j * (uiPictWidth << ubIsField );
    pubDstV = pubVFrameData + j * (uiPictWidth <<ubIsField );


    pubCurSrc = pubSrc[ubIdx];

    for(k = 0; k < uiPictWidth; k++)
    {
      *pubDstU++  = *pubCurSrc++;
      *pubDstV++  = *pubCurSrc++;
    }

    if (ubIsField)
    {

      pubCurSrc = pubSrc[ubIdx] + uiRecWidth*(uiPictHeight + 32);;

      for(k = 0; k < uiPictWidth; k++)
      {
        *pubDstU++  = *pubCurSrc++;
        *pubDstV++  = *pubCurSrc++;
      }
    }

    pubSrc[ubIdx] += uiRecWidth;
  }

}

/*===========================================================================*/
/**
*@func   WriteReconOut()
*
*@brief  Write out the Reconstructed frame
*
*@param  pubReconY
*        Pointer to buffer containing Luma data
*
*@param  pubReconU
*        Pointer to buffer containing Chroma Cb data
*
*@param  pubReconV
*        Pointer to buffer containing Chroma Cr data
*
*@param  uiWidth
*        Picture Width
*
*@param  uiHeight
*        Picture Height
*
*@param  pfOutYUVFile
*        Output file pointer
*
*@return Status
*
*@note
*/
/*===========================================================================*/
XDAS_Int32 WriteReconOut(
                         XDAS_UInt8* pubReconY,
                         XDAS_UInt8* pubReconU,
                         XDAS_UInt8* pubReconV,
                         XDAS_Int32 uiWidth,
                         XDAS_Int32 uiHeight,
                         FILE *pfOutYUVFile
                         )
{

  XDAS_Int32 uiSize = uiWidth * uiHeight;

  /*-------------------------------------------------------------------------*/
  /*                        WRITE THE BITSTREAM                              */
  /*-------------------------------------------------------------------------*/
  my_fwrite(pubReconY, 1, uiSize, pfOutYUVFile);
  my_fwrite(pubReconU, 1, (uiSize >> 2), pfOutYUVFile);
  my_fwrite(pubReconV, 1, (uiSize >> 2), pfOutYUVFile);

  return(0);
}/* WriteReconOut */

/**
********************************************************************************
*  @fn     main
*  @brief  Sample main program implementation which uses xDM v2.0 H264
*          encoder's APIs to create a encoder instance and encode multiple
*          input files. It supports dumping of output encoded data or
*          comparision of encoded data with reference encoder.
*          Uses single instance of the encoder.
*
*  @param  none
*
*  @return     0 - when there is no error while encoding
*              0 - when there is error while encoding
********************************************************************************
*/
XDAS_Int32    inschan;
XDAS_Int32    currProcessCallNumChannel;
#define RECON_DUMP 0
XDAS_Int32 main()
{

  /*--------------------------------------------------------------------------*/
  /*  File I/O variables                                                      */
  /*--------------------------------------------------------------------------*/
  FILE      *foutFile[MAX_ITEMS_TO_RUN], *finFile[MAX_ITEMS_TO_RUN];
  FILE      *fTrace_file[MAX_ITEMS_TO_RUN];
  FILE      *fTestCasesFile;
  FILE      *fProfileTrace[MAX_ITEMS_TO_RUN];
  FILE      *fDynamicParamChgFile[MAX_ITEMS_TO_RUN];
  FILE      *waterMarkFile[MAX_ITEMS_TO_RUN];
#ifdef COMPARE_OUTPUT
  FILE      *frefFile[MAX_ITEMS_TO_RUN];
#endif
#if RECON_DUMP
  FILE      *pfOutYUVFile[MAX_ITEMS_TO_RUN];
#endif /* #if RECON_DUMP */

  /*--------------------------------------------------------------------------*/
  /* String arrays to hold the file names along with path                     */
  /*--------------------------------------------------------------------------*/
  XDAS_Int8     inFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
  XDAS_Int8     outFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
  XDAS_Int8     configFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
  XDAS_Int8     testCasesFile[FILE_NAME_SIZE];
#ifdef COMPARE_OUTPUT
  XDAS_Int8     refFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
#endif
  XDAS_Int8     scTraceFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
  XDAS_Int8     scProfileTrace[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
  XDAS_Int8     version[FILE_NAME_SIZE];
  XDAS_Int8     dynamicparamChgFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
  XDAS_Int8     waterMarkInputKeyFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];


#if RECON_DUMP
  XDAS_Int8     ReconFile[MAX_ITEMS_TO_RUN][FILE_NAME_SIZE];
#endif /* #if RECON_DUMP */
  XDAS_UInt32   uiCaptureWidth[MAX_ITEMS_TO_RUN],
                uiCaptureHeight[MAX_ITEMS_TO_RUN],
                uiSize[MAX_ITEMS_TO_RUN],uiSize1[MAX_ITEMS_TO_RUN];
  XDAS_UInt32   uiInputWidth[MAX_ITEMS_TO_RUN], uiInputHeight[MAX_ITEMS_TO_RUN];
  XDAS_UInt32   i;
  XDAS_UInt32   testCaseCounter = 0;
  XDAS_UInt32   testCaseControl;

  XDAS_Int32    ret[MAX_ITEMS_TO_RUN];
  XDAS_UInt32   count;
  XDAS_Int8     rValue = 0;
 /*--------------------------------------------------------------------------*/
  /* Flag to test XDM reset feature                                           */
  /* In normal case this flag must me 0, it should be enabled only when reset */
  /* feature test is required                                                 */
  /*--------------------------------------------------------------------------*/
  XDAS_UInt32   uiReset_Test[MAX_ITEMS_TO_RUN] = {0};
  XDAS_UInt32   tmpMetaPlane[MAX_ITEMS_TO_RUN] = {0};


  /*--------------------------------------------------------------------------*/
  /*  Declaring Algorithm specific handle                                     */
  /*--------------------------------------------------------------------------*/
  H264ENC_Handle      handle[MAX_ITEMS_TO_RUN];
  /*--------------------------------------------------------------------------*/
  /* XDM extended class structre declarations                                 */
  /*--------------------------------------------------------------------------*/
  H264ENC_InArgs            inArgs[MAX_ITEMS_TO_RUN];
  H264ENC_OutArgs           outArgs[MAX_ITEMS_TO_RUN];
  H264ENC_Status            status[MAX_ITEMS_TO_RUN];
  XDM2_BufDesc              outputBufDesc[MAX_ITEMS_TO_RUN];
  /*--------------------------------------------------------------------------*/
  /*  Handle to a buffer element allocated by the buffer manager module       */
  /*--------------------------------------------------------------------------*/
  BUFFMGR_buffEleHandle buffEle[MAX_ITEMS_TO_RUN];
  /*--------------------------------------------------------------------------*/
  /*  Other local variables                                                   */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32        retValue[MAX_ITEMS_TO_RUN];

  XDAS_Int32        frameNum[MAX_ITEMS_TO_RUN] = {0};
  XDAS_Int32        numEntries;
  IH264ENC_ProcessParamsList processList;
  numFramesEncoded[0] = 0 ;

  /*--------------------------------------------------------------------------*/
  /* Initialize file IO                                                       */
  /*--------------------------------------------------------------------------*/
  init_file_io();
  /*--------------------------------------------------------------------------*/
  /* Configaration file with path used for controling encoder                 */
  /*--------------------------------------------------------------------------*/
  strcpy((char *)testCasesFile,
    "..\\..\\..\\Test\\TestVecs\\Config\\testcases.txt");

  /*--------------------------------------------------------------------------*/
  /*  Open Test Config File                                                   */
  /*--------------------------------------------------------------------------*/
  fTestCasesFile = fopen((const char *)testCasesFile,"r");
  if(fTestCasesFile == NULL)
  {
    printf("\n Unable to open TestCases List File(TestCases.txt) %s\n",
      testCasesFile);
    return(XDM_EFAIL);
  }

  while(!feof(fTestCasesFile))
  {
    fscanf(fTestCasesFile, "%d",&testCaseControl);
    inschan = testCaseControl;
    if(testCaseControl == 0) {
      printf("\n\n\n ******** Request to END H264 Encoder ******** \n");
      abort();
    }
    for (count =0 ; count < inschan; count++) {
      fscanf(fTestCasesFile, "%s",configFile[count]);
      if((inschan > MAX_ITEMS_TO_RUN)||(inschan == 0)) {
        printf("\n Given instance channel are greater than the ");
        printf(" max no of channel's \n ");
        abort();
      }
    }
    InbufPtr = (XDAS_UInt8 *)InBuffers;
  
    /*------------------------------------------------------------------------*/
    /* enabling enableErrorCheck  makes execute the code in M3, which         */
    /* checks for the features that are not supported in N channel Api        */
    /* 1.effect of flag is as of now only if (processList->numEntries > 1)    */
    /* 2.Suggested value for this flag is 0 to have better performance        */
    /*------------------------------------------------------------------------*/
    processList.enableErrorCheck  = TRUE;

    for (insChanid=0; insChanid<inschan; insChanid++) 
    {
      testCaseCounter++;
      tmpMetaPlane[insChanid] = 0;
      /*----------------------------------------------------------------------*/
      /* Set Initial default values for all the parameters                    */
      /*----------------------------------------------------------------------*/
      TestApp_SetInitParams(&gParamsOrg,&gDynamicParamsOrg);         
                                                                     
      /*----------------------------------------------------------------------*/
      /* Read Test Config Parameter File                                      */
      /*----------------------------------------------------------------------*/
      gConfigOrg.startFrame     = 0;

      if(readparamfile(configFile[insChanid]) != 0)
      {
        printf("Unable to read Config Parameter File %s\n",
                                                        configFile[insChanid]);
        return(XDM_EFAIL);
      }
      
      if (gDynamicParamsOrg.enableROI)
      {
        if(readparamfile(gConfigOrg.roiinputFile) != 0)
        {
          printf("Unable to read Config Parameter File %s\n", 
                                                      gConfigOrg.roiinputFile);
          return(XDM_EFAIL);
        }
      }
      
      memcpy((void *) (&gConfig[insChanid]), (const void *) (&gConfigOrg),
                                                      sizeof(h264BPEncConfig));
      
      /*---------------------------------------------------------------------*/
      /* Copy the default parameter into respective channel params first     */
      /*---------------------------------------------------------------------*/
      memcpy((void *) (&gParams[insChanid]), (const void *)(&H264ENC_TI_PARAMS),
                                                        sizeof(H264ENC_Params));
      memcpy((void *) (&gDynamicParams[insChanid]),
      (const void *)(&H264ENC_TI_DYNAMICPARAMS), sizeof(H264ENC_DynamicParams));

      /*-------------------------------------------------------------------*/
      /* Now copy based on encoding preset selected by user                */
      /*-------------------------------------------------------------------*/

      /*-------------------------------------------------------------------*/
      /* Test app code usages gParams for enabling the meta planes and also*/
      /* for data synch purposes. It is possible that when encoding preset */
      /* is not user defined then the values present in gParams might not  */
      /* be in synch with what is used inside the codec so some unexpected */
      /* behaviour can be observed. SO to solve that default values are    */
      /* user provided extended class parameter is copied into gParams/dyn */
      /* params only when encoding preset is user defined.                 */
      /*-------------------------------------------------------------------*/

      if(gParamsOrg.videnc2Params.encodingPreset == XDM_USER_DEFINED)
      {
        memcpy((void *) (&gParams[insChanid]), (const void *) (&gParamsOrg),
                                                        sizeof(H264ENC_Params));
        memcpy((void *) (&gDynamicParams[insChanid]),
             (const void *)(&gDynamicParamsOrg), sizeof(H264ENC_DynamicParams));
      }
      else
      {
        memcpy((void *) (&gParams[insChanid]), (const void *) (&gParamsOrg),
                                                       sizeof(IVIDENC2_Params));
        memcpy((void *) (&gDynamicParams[insChanid]),
            (const void *)(&gDynamicParamsOrg), sizeof(IVIDENC2_DynamicParams));
      }
      
      memcpy((void *) (&gInputBufDesc[insChanid]),
                   (const void *) (&gInputBufDescOrg), sizeof(IVIDEO2_BufDesc));
      memcpy((void *) (&gInArgs[insChanid]), (const void *)(&gInArgsOrg), 
                                                       sizeof(IH264ENC_InArgs));
      inArgs[insChanid].roiInputParams = gInArgs[insChanid].roiInputParams;
    
      /*----------------------------------------------------------------------*/
      /*  Get the IVAHD Config, SL2, PRCM base address based on IVAHD ID      */
      /*----------------------------------------------------------------------*/
      Init_IVAHDAddrSpace();

      IVAHD_Standby_power_on_uboot();

      if(inschan > 1)
      {
        gParams[insChanid].videnc2Params.outputDataMode = IVIDEO_ENTIREFRAME;         
        gParams[insChanid].videnc2Params.inputDataMode  = IVIDEO_ENTIREFRAME;    
        gParams[insChanid].interCodingParams.minBlockSizeB =
                          gParams[insChanid].interCodingParams.minBlockSizeP;

        gDynamicParams[insChanid].interCodingParams.minBlockSizeB =
                   gDynamicParams[insChanid].interCodingParams.minBlockSizeP;
        gDynamicParams[insChanid].videnc2DynamicParams.generateHeader = 0x0;
      
      }
      /*----------------------------------------------------------------------*/
      /* Below code enables hrd paramters always.                             */
      /*----------------------------------------------------------------------*/

      gParams[insChanid].vuiCodingParams.hrdParamsPresentFlag  = 1;
      H264ENC_TI_InitDynamicParams(&gParams[insChanid],
                                                    &gDynamicParams[insChanid]);
      gDynamicParams[insChanid].videnc2DynamicParams.ignoreOutbufSizeFlag = 1;
      gDynamicParams[insChanid].videnc2DynamicParams.getBufferFxn = 
                                                    H264ETest_DataSyncGetBufFxn;

      gDynamicParams[insChanid].videnc2DynamicParams.putDataFxn =
                                                   H264ETest_DataSyncPutDataFxn;
      gDynamicParams[insChanid].videnc2DynamicParams.getDataFxn =
                                                  H264ETest_DataSyncGetDataFxn1;
      gDynamicParams[insChanid].videnc2DynamicParams.getDataHandle = 
                                                                fGetInpDHandle1;
      
      /*----------------------------------------------------------------------*/
      /*    Trace file to write the encoding details                          */
      /*----------------------------------------------------------------------*/
      if (insChanid == 0) {
        strcpy((char *)scTraceFile[insChanid], 
                                   (const char *)gConfig[insChanid].outputFile);
        strcat((char *)scTraceFile[insChanid], ".txt");
        fTrace_file[insChanid] =
                               fopen((const char *)scTraceFile[insChanid], "w");
        if(fTrace_file[insChanid]== NULL)
        {
          printf("\nUnable to open Trace file to write encoding details %s\n",
                                                        scTraceFile[insChanid]);
          return(XDM_EFAIL);
        }
      }
#if RECON_DUMP
      strcpy((char *)ReconFile[insChanid],
                                  (const char *)gConfig[insChanid].outputFile);
      strcat((char *)ReconFile[insChanid], ".yuv");
      pfOutYUVFile[insChanid] 
                          = my_fopen((const char *)ReconFile[insChanid],"wb");

      if(pfOutYUVFile[insChanid] == NULL)
      {
        printf("\n Unable to open YUV file to write the Recon Frame %s\n",
          ReconFile[insChanid]);
        return(XDM_EFAIL);
      }
#endif

      /*----------------------------------------------------------------------*/
      /* Configaration file with path used for controling encoder             */
      /*----------------------------------------------------------------------*/

      printf("\n-----------------------------------------------\n");
      printf("Test Case Number : %d",testCaseCounter);
      printf("\n-----------------------------------------------\n");

      printf("No of Instance's : %d \n",inschan);
      printf("Config File   : %s\n",configFile[insChanid]);
      printf("Input YUV     : %s\n",gConfig[insChanid].inputFile);
      printf("Output Stream : %s\n\n",gConfig[insChanid].outputFile);

      if (inschan ==1) 
      {
        fprintf(fTrace_file[insChanid],
                                  "Config File   : %s\n",configFile[insChanid]);
        fprintf(fTrace_file[insChanid],
                           "Input YUV     : %s\n",gConfig[insChanid].inputFile);
        fprintf(fTrace_file[insChanid],
                        "Output Stream : %s\n\n",gConfig[insChanid].outputFile);
      }
      /*----------------------------------------------------------------------*/
      /* Make sure output file is proper and empty the file if it already     */
      /* exists By open and close the file and reopen the file                */
      /*----------------------------------------------------------------------*/
      strcpy((char *)outFile[insChanid],
                                   (const char *)gConfig[insChanid].outputFile);
      foutFile[insChanid] = fopen((const char *)outFile[insChanid], "wb");
      if(foutFile[insChanid] == NULL)
      {
        printf("\n Unable to open Output Bitstream File %s\n", 
                                                           outFile[insChanid]);
        return(XDM_EFAIL);
      }
      fclose(foutFile[insChanid]);

      strcpy((char *)outFile[insChanid],
                                (const char *)gConfig[insChanid].outputFile);
      foutFile[insChanid] = my_fopen((const char *)outFile[insChanid], "wb");
      if(foutFile[insChanid] == NULL)
      {
        printf("\n Unable to open Output Bitstream File %s\n",
                                                            outFile[insChanid]);
        return(XDM_EFAIL);
      }
      my_fclose(foutFile[insChanid]);
#ifdef COMPARE_OUTPUT
      /*----------------------------------------------------------------------*/
      /* Open Test Reference Bitstream file.                                  */
      /*----------------------------------------------------------------------*/
      if(inschan ==1)
      {
        strcpy((char *)refFile[insChanid],
                                  (const char *)gConfig[insChanid].refFile);
        frefFile[insChanid] = fopen((const char *)refFile[insChanid], "rb");
        if(frefFile[insChanid] == NULL)
        {
          printf("\n Unable to open Test reference Bitstream File %s\n", 
                                                       refFile[insChanid]);
          my_fclose(foutFile[insChanid]);
          my_fclose(finFile[insChanid]);
          return(XDM_EFAIL);
        }
      }
#endif
      /*----------------------------------------------------------------------*/
      /*  Setting the sizes of Base Class Objects                             */
      /*----------------------------------------------------------------------*/
#ifdef BASE_CLASS
      status[insChanid].videnc2Status.size         = sizeof(IVIDENC2_Status) ;
      inArgs[insChanid].videnc2InArgs.size         = sizeof(IVIDENC2_InArgs) ;
      outArgs[insChanid].videnc2OutArgs.size       = sizeof(IVIDENC2_OutArgs);
      gParams[insChanid].videnc2Params.size        = sizeof(IVIDENC2_Params) ;
      gDynamicParams[insChanid].videnc2DynamicParams.size  = 
                                              sizeof(IVIDENC2_DynamicParams) ;
      memset((XDAS_Int8*)&status[insChanid] + sizeof(IVIDENC2_Status),
           PATTERN_FILL_EXT,sizeof(H264ENC_Status) - sizeof(IVIDENC2_Status));
      memset((XDAS_Int8*)&gParams[insChanid] + sizeof(IVIDENC2_Params),
           PATTERN_FILL_EXT,sizeof(H264ENC_Params) - sizeof(IVIDENC2_Params));
      memset((XDAS_Int8*)&gDynamicParams[insChanid] + \
                           sizeof(IVIDENC2_DynamicParams), PATTERN_FILL_EXT,
             sizeof(H264ENC_DynamicParams) - sizeof(IVIDENC2_DynamicParams));
#else
      status[insChanid].videnc2Status.size         = sizeof(H264ENC_Status) ;
      inArgs[insChanid].videnc2InArgs.size         = sizeof(H264ENC_InArgs) ;
      outArgs[insChanid].videnc2OutArgs.size       = sizeof(H264ENC_OutArgs);
      gParams[insChanid].videnc2Params.size        = sizeof(H264ENC_Params) ;
      gDynamicParams[insChanid].videnc2DynamicParams.size  = 
                                               sizeof(H264ENC_DynamicParams);
#endif

      /*----------------------------------------------------------------------*/
      /* Setting/Enabling of the meta data type for user data sei             */
      /*----------------------------------------------------------------------*/
      {
        XDAS_Int16* pmask =
      &(gParams[insChanid].nalUnitControlParams.naluPresentMaskStartOfSequence);

        for (i = 0 ; i< 4 ; i++)
        {
          if(((*pmask) & ( 0x1 << IH264_NALU_TYPE_USER_DATA_UNREGD_SEI ))!= 0x0)
          {
            gParams[insChanid].videnc2Params.metadataType[tmpMetaPlane
                                [insChanid]] = IH264_SEI_USER_DATA_UNREGISTERED;
            tmpMetaPlane[insChanid]++;
            break;
          }
          pmask++;
        }
      }
      {
        gDynamicParams[insChanid].videnc2DynamicParams.forceFrame = 
                                                                IVIDEO_NA_FRAME;
        if((gConfig[insChanid].numProcessCall == 60) &&
          (gParams[insChanid].videnc2Params.inputContentType ==
                                                             IVIDEO_INTERLACED))
        {
          gConfig[insChanid].forceIDRPeriod <<= 1;
        }
      }

      /*----------------------------------------------------------------------*/
      /*If user wants scaling matrix content to be difined externally then the*/
      /*preset to be used is IH264_SCALINGMATRIX_USERDEFINED_SPSLEVEL or      */
      /*IH264_SCALINGMATRIX_USERDEFINED_PPSLEVEL. In this situation user need */
      /*A. Enable the corresponding meta data bit.                            */
      /*B. Prvide the scaling matrices via meta data buffer                   */
      /*----------------------------------------------------------------------*/
      if((gParams[insChanid].rateControlParams.scalingMatrixPreset >=
        IH264_SCALINGMATRIX_USERDEFINED_SPSLEVEL) &&
        (gParams[insChanid].rateControlParams.rateControlParamsPreset ==
        IH264_RATECONTROLPARAMS_USERDEFINED)
        )
      {
        gParams[insChanid].videnc2Params.metadataType[tmpMetaPlane[insChanid]] =
          IH264_USER_DEFINED_SCALINGMATRIX;
        tmpMetaPlane[insChanid]++;
      }

      /*----------------------------------------------------------------------*/
      /* opening the file which contains the input key for Water Marking      */
      /*----------------------------------------------------------------------*/
      if(gParams[insChanid].enableWatermark)
      {
        strcpy((char *)waterMarkInputKeyFile[insChanid],
          (const char *)gConfig[insChanid].waterMarkInputKeyFile);
        waterMarkFile[insChanid] =
                               fopen((const char *)waterMarkInputKeyFile, "rb");
        if(waterMarkFile[insChanid] == NULL)
        {
          printf("\n Unable to open Water Mark input Key  File %s\n",
            waterMarkInputKeyFile);
          return(XDM_EFAIL);
        }

      }


      /*----------------------------------------------------------------------*/
      /*Reset the previous extended and sub-extended error status to avoid    */
      /*               unnecessary failures                                   */
      /*----------------------------------------------------------------------*/
      status[insChanid].videnc2Status.extendedError = 0;
      {
        XDAS_Int32 numErrorWords ;
        for(numErrorWords = 0 ; numErrorWords < IH264ENC_EXTERROR_NUM_MAXWORDS ;
                                                                numErrorWords++)
        {
          status->extErrorCode[numErrorWords] = IVIDENC2_EOK ;
        }
      }
      /*gParams.reservedParams[1] = 0x3; */
      gParams[insChanid].reservedParams[1] = 0x1F;

      gParams[insChanid].svcCodingParams.dependencyID = 0;
      gParams[insChanid].svcCodingParams.qualityID = 0;
      gParams[insChanid].svcCodingParams.enhancementProfileID = 0;
      gParams[insChanid].svcCodingParams.layerIndex = 0;

      /*----------------------------------------------------------------------*/
      /*Algorithm create call. This function will allocate memory for the main*/
      /*algorithm handle algorithm and initializes accordingly. The alg handle*/
      /*is returnd.                                                           */
      /*----------------------------------------------------------------------*/
    /*if (gConfig.startFrame != 0)
    {
      gParams.rateControlParams.initialBufferLevel = gVbvBufLevel;
      gDynamicParams.rateControlParams.initialBufferLevel = gVbvBufLevel;
    }*/
      handle[insChanid] = H264ENC_create((H264ENC_Fxns *)&H264ENC_TI_IH264ENC,
                                                           &gParams[insChanid]);
      /*----------------------------------------------------------------------*/
      /*  Initialize the Handle to the MB processing function that is         */
      /*  required to be called by the ISR.                                   */
      /*----------------------------------------------------------------------*/
      g_handle[insChanid][0] = (IALG_Handle)handle[insChanid];

      /*----------------------------------------------------------------------*/
      /*  Check for errors in algorithm handle creation                       */
      /*----------------------------------------------------------------------*/
      if(handle[insChanid] == NULL)
      {
        fprintf(stdout, "Creation Failed.\n");
        fprintf(stdout, "Check the Create-time static parameter settings.\n");
        H264ENC_control(handle[insChanid],XDM_GETSTATUS,
        (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                        (H264ENC_Status *)&status[insChanid]);
        H264ENC_TI_Report_ExtError(fTrace_file[insChanid],
                                          &status[insChanid].extErrorCode[0]);
        goto DELETE_INSTANCE;
      }

      /*----------------------------------------------------------------------*/
      /*  Get the buffers in TILER space                                      */
      /*----------------------------------------------------------------------*/

      {
        /*--------------------------------------------------------------------*/
        /* Get the buffers in TILER space                                     */
        /* Do the allocation for maximum supported resoultion and keep to some*/
        /* aligned boundary. Also this allocation assumes that tiled8 and     */
        /* tiled16 are mapped to same physical space                          */
        /*--------------------------------------------------------------------*/
        sTilerParams *pTilerParams = &TilerParams;
        if( insChanid == 0 )
        {
          pTilerParams->tilerSpace[0] = pTilerParams->tilerSpace[0] = 0;
        }
        
        if(!(pTilerParams->tilerSpace[0]||pTilerParams->tilerSpace[1]))
        {
          pTilerParams->tilerSpace[0]    = gConfig[insChanid].tilerSpace[0];
          pTilerParams->tilerSpace[1]    = gConfig[insChanid].tilerSpace[1];
        }
        
        pTilerParams->memoryOffset[0]  = 0;
        pTilerParams->memoryOffset[1]  = 0x4800000;
        pTilerParams->totalSizeLuma    = 0x4800000;

        if( inschan > 1 )
        {
          pTilerParams->imageDim[0]      = 1920;
          pTilerParams->imageDim[1]      = 1088;
        }
        else
        {
          pTilerParams->imageDim[0]      = 2048;
          pTilerParams->imageDim[1]      = 1536;
        }
        
        SetPATViewMapBase();
        
        ret[insChanid] = tiler_init(pTilerParams);
        
        if(ret[insChanid] == -1)
        {
          /*------------------------------------------------------------------*/
          /* If tiler allocation is not successful then Force both the buffer */
          /* to be in raw region                                              */
          /*------------------------------------------------------------------*/
          gConfig[insChanid].tilerSpace[0]=gConfig[insChanid].tilerSpace[1] =0;
        }
        else
        {
          /*------------------------------------------------------------------*/
          /* Library also overrides few requests so take to the application   */
          /* variables to keep the flow correct                               */
          /*------------------------------------------------------------------*/
          gConfig[insChanid].tilerSpace[0]  = pTilerParams->tilerSpace[0]  ;
          gConfig[insChanid].tilerSpace[1]  = pTilerParams->tilerSpace[1]  ;
        }

      }

      /*----------------------------------------------------------------------*/
      /* Counter for setting Codec Type                                       */
      /*----------------------------------------------------------------------*/
      FrameNum[insChanid] = 0;                                              
      /*----------------------------------------------------------------------*/
      /*  Call to RMAN Assign Resources (to verify the ires-rman functions.   */
      /*----------------------------------------------------------------------*/
      retValue[insChanid] = RMAN_AssignResources((IALG_Handle)handle[insChanid],
           gConfig[insChanid].tilerSpace[0], gConfig[insChanid].tilerSpace[1] );
      if(retValue[insChanid] != IRES_OK)
      {
        printf("Error, not enough memory \n");
        fprintf(fTrace_file[insChanid], " Error, not enough memory \n");
        goto DELETE_INSTANCE;
      }
      /*----------------------------------------------------------------------*/
      /* Get the version of codec and print it                                */
      /*----------------------------------------------------------------------*/
      status[insChanid].videnc2Status.data.buf = (XDAS_Int8*)&version[0];
      status[insChanid].videnc2Status.data.bufSize = FILE_NAME_SIZE;
      retValue[insChanid] = H264ENC_control(handle[insChanid],XDM_GETVERSION,
        (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                         (H264ENC_Status *)&status[insChanid]);
      printf("\nAlgorithm Instance  Creation for the Module %s Done...\n", 
                                                                      version);
      status[insChanid].videnc2Status.data.bufSize = 0;
      /*----------------------------------------------------------------------*/
      /* Check for the create time errors, and print them in log file         */
      /* Controll commands will enabled only after RMAN_AssignResources       */
      /* First we will print codec version when before printig any error      */
      /*----------------------------------------------------------------------*/
      if(inschan == 1) 
      {
        H264ENC_control(handle[insChanid],XDM_GETSTATUS,
          (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
        H264ENC_TI_Report_ExtError(fTrace_file[insChanid],
                                            &status[insChanid].extErrorCode[0]);
        if(H264ENC_TI_Report_Error(fTrace_file[insChanid],
                                status[insChanid].videnc2Status.extendedError))
        {
          printf("Creation Failed.\n");
          fprintf(fTrace_file[insChanid], "Creation Failed.\n");
          goto DELETE_INSTANCE;
        }
      }
      /*----------------------------------------------------------------------*/
      /*  XDM_SETPARAMS is called to pass the Dynamic Parameters to the codec.*/
      /*  The Control function shall validate the parameters. If an error     */
      /*  is found then the Control function returns failure.                 */
      /*----------------------------------------------------------------------*/
      retValue[insChanid] = H264ENC_control(handle[insChanid],XDM_SETPARAMS,
        (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
      if(retValue[insChanid] == XDM_EFAIL)
      {
        printf("Failed in dynamicParams setting.\n");
        printf("Check the dynamicParams settings.\n");
        if (inschan ==1 ) 
        {
          H264ENC_TI_Report_Error(fTrace_file[insChanid],
                                 status[insChanid].videnc2Status.extendedError);
          H264ENC_control(handle[insChanid],XDM_GETSTATUS,
          (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
          H264ENC_TI_Report_ExtError(fTrace_file[insChanid],
                                            &status[insChanid].extErrorCode[0]);
          fprintf(fTrace_file[insChanid], "Failed in dynamicParams settings\n");
          fprintf(fTrace_file[insChanid], "Check the dynamicParams settings\n");
        }
        /* Delete only if it is a FATAL Error else continue */
        if(XDM_ISFATALERROR(status[insChanid].videnc2Status.extendedError))
        {
          goto DELETE_INSTANCE;
        }
      }


      /*----------------------------------------------------------------------*/
      /*  XDM_SETLATEACQUIREARG is called to set the channel ID to codec      */
      /*----------------------------------------------------------------------*/
      gDynamicParams[insChanid].videnc2DynamicParams.lateAcquireArg =CHANNEL_ID;
      retValue[insChanid] = H264ENC_control(handle[insChanid],
      XDM_SETLATEACQUIREARG,(H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
      if(retValue[insChanid] == XDM_EFAIL)
      {
        printf("Failed in dynamicParams setting.\n");
        printf("Check the dynamicParams settings.\n");
        if (inschan ==1 ) {
          H264ENC_TI_Report_Error(fTrace_file[insChanid],
                                 status[insChanid].videnc2Status.extendedError);
          H264ENC_control(handle[insChanid],XDM_GETSTATUS,
          (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
          H264ENC_TI_Report_ExtError(fTrace_file[insChanid],
                                            &status[insChanid].extErrorCode[0]);
          fprintf(fTrace_file[insChanid], "Failed in dynamicParams settings\n");
          fprintf(fTrace_file[insChanid], "Check the dynamicParams settings\n");
        }
        /* Delete only if it is a FATAL Error else continue */
        if(XDM_ISFATALERROR(status[insChanid].videnc2Status.extendedError))
        {
          goto DELETE_INSTANCE;
        }
      }

      /*----------------------------------------------------------------------*/
      /* Get buffer with XDM_GETBUFINFO command and allocate buffers          */
      /* accordingly with Buffer manager                                      */
      /*----------------------------------------------------------------------*/
      H264ENC_control(handle[insChanid],XDM_GETBUFINFO,
        (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
      uiCaptureWidth[insChanid]  =
      (gDynamicParams[insChanid].videnc2DynamicParams.captureWidth + 15 ) & ~15;

      /*----------------------------------------------------------------------*/
      /*uiCaptureWidth ==0  means same as pitch == width                      */
      /*in test application code uiCaptureWidth variable should be used and to*/
      /*codec interface level gDynamicParams.videnc2DynamicParams.captureWidth*/
      /*----------------------------------------------------------------------*/
      if(uiCaptureWidth[insChanid] == 0)
      {
        uiCaptureWidth[insChanid] =
        (gDynamicParams[insChanid].videnc2DynamicParams.inputWidth + 15) & ~15 ;
      }

      uiCaptureHeight[insChanid] = 
                                  (gConfig[insChanid].captureHeight+ 15 ) & ~15;
      if(gParams[insChanid].videnc2Params.inputContentType == IVIDEO_INTERLACED)
      {
        uiCaptureHeight[insChanid] <<= 1;
      }
      /*----------------------------------------------------------------------*/
      /* Loop through the number of buffers and calulate the size required    */
      /* TODO: Need to get some clarification why control will not give size  */
      /*----------------------------------------------------------------------*/
      for(i = 0; i < status[insChanid].videnc2Status.bufInfo.minNumInBufs; i++)
      {

        if(!gConfig[insChanid].enableRunTimeTest)
        {
          if(status[insChanid].videnc2Status.bufInfo.inBufMemoryType[i] !=
                                                                XDM_MEMTYPE_ROW)
          {
            uiSize1[insChanid] =  status[insChanid].
                        videnc2Status.bufInfo.minInBufSize[i].tileMem.width *
                                 status[insChanid].
                           videnc2Status.bufInfo.minInBufSize[i].tileMem.height;
          }
          else
          {
            uiSize1[insChanid] =
               status[insChanid].videnc2Status.bufInfo.minInBufSize[i].bytes;
          }
        }
        else
        {
          /*------------------------------------------------------------------*/
          /* Here for input buffer size calculation maxWidth & maxHeight are  */
          /* used This is done for testing dynamic resolution chage           */
          /*------------------------------------------------------------------*/
          if(i == 0) /*  chroma                                               */
          {
            uiSize1[insChanid] = gParams[insChanid].videnc2Params.maxWidth * 
                                     gParams[insChanid].videnc2Params.maxHeight;
          }
          else
          {
            uiSize1[insChanid] = gParams[insChanid].videnc2Params.maxWidth *
              (gParams[insChanid].videnc2Params.maxHeight / 2);
          }
        }

        if(i == 0) /*  chroma                                                 */
        {
          uiSize[insChanid] =
                         uiCaptureWidth[insChanid] * uiCaptureHeight[insChanid];
        }
        else
        {
          uiSize[insChanid] =
                   uiCaptureWidth[insChanid] * (uiCaptureHeight[insChanid] / 2);
        }

        uiSize[insChanid] = uiSize[insChanid] > (uiSize1[insChanid]) ? 
                                        uiSize[insChanid] : uiSize1[insChanid];
        status[insChanid].videnc2Status.bufInfo.minInBufSize[i].bytes =
                                                             uiSize[insChanid];
      }
      retValue[insChanid] = BUFFMGR_Init(((inschan == 1) ? MAX_BUFF_ELEMENTS:2),
        status[insChanid].videnc2Status.bufInfo.minNumInBufs,
        status[insChanid].videnc2Status.bufInfo.minInBufSize,
        gConfig[insChanid].tilerSpace[0], gConfig[insChanid].tilerSpace[1]
      );
      if (retValue[insChanid])
      {
        printf ("\nMemory could not get allocated for output buffers\n");
        if (inschan == 1) {
          fprintf (fTrace_file[insChanid],
                      "\nMemory could not get allocated for output buffers\n");
        }
        goto DELETE_INSTANCE;
      }
      numFramesEncoded[insChanid] = 0;
      frameNum[insChanid]   = gConfig[insChanid].startFrame;

      if(inschan ==1) {
        /*--------------------------------------------------------------------*/
        /*        profile file to write the encoding details                  */
        /*--------------------------------------------------------------------*/
        strcpy((char *)scProfileTrace[insChanid],
                                  (const char *)gConfig[insChanid].outputFile);
        strcat((char *)scProfileTrace[insChanid], "_profile.bin");
        fProfileTrace[insChanid] = 
                          fopen((const char *)scProfileTrace[insChanid], "wb");
        if(fProfileTrace[insChanid]== NULL)
        {
          printf("\n Unable to open Trace file to write encoding details %s\n",
                                                       scTraceFile[insChanid]);
          return(XDM_EFAIL);
        }
      }

      /*----------------------------------------------------------------------*/
      /*  Check for debug trace parameters             .                      */
      /*----------------------------------------------------------------------*/
      retValue[insChanid] = H264ENC_control(handle[insChanid],XDM_GETSTATUS,
        (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
      printf("Debug Trace (@ Level %d) Buffer in DDR @ 0x%X of size %d bytes\n",
        status[insChanid].debugTraceLevel,
        status[insChanid].extMemoryDebugTraceAddr,
        status[insChanid].extMemoryDebugTraceSize);

      /*----------------------------------------------------------------------*/
      /* Check for Status base class working                                  */
      /* when working in base class, the pattern filled at extended part      */
      /* should be same after XDM_GETSTATUS call                              */
      /*----------------------------------------------------------------------*/
#ifdef BASE_CLASS
      {
        XDAS_Int8 *src[insChanid] = 
                       (XDAS_Int8*)&status[insChanid] + sizeof(IVIDENC2_Status);
        XDAS_Int32 size[insChanid] =
                               sizeof(H264ENC_Status) - sizeof(IVIDENC2_Status);
        for(i = 0; i< size[insChanid]; i++)
        {
          if(*src[insChanid] != (XDAS_Int8)PATTERN_FILL_EXT)
          {
            printf("\n Failed in testing Status Base class mode\n");
            goto DELETE_INSTANCE;
          }
          src[insChanid]++;
        }
      }
#endif
      if(inschan == 1) {
        /*--------------------------------------------------------------------*/
        /*  Dynamic parameter change testing                                  */
        /*--------------------------------------------------------------------*/
        if(gConfig[insChanid].enableRunTimeTest)
        {
          XDAS_Int8 tempDynamicFramePos[40];

          stopPos[insChanid] = 1;
          gConfig[insChanid].DynamicFramePos = 0;
          strcpy((char *)dynamicparamChgFile[insChanid],
            "..\\..\\..\\Test\\TestVecs\\Config\\dynamicparamchg.txt");

          /*------------------------------------------------------------------*/
          /*  Open dynamic parameter change Config File                       */
          /*------------------------------------------------------------------*/
          fDynamicParamChgFile[insChanid] = 
                       fopen((const char *)dynamicparamChgFile[insChanid],"rb");

          if(fDynamicParamChgFile[insChanid] == NULL)
          {
            printf("\nUnable to open dynamic parameter change config File %s\n",
              dynamicparamChgFile[insChanid]);
            return(XDM_EFAIL);
          }
          /*------------------------------------------------------------------*/
          /* Read first dynamic parameter change frame number                 */
          /* In the dynamic param change config file, frame number at which   */
          /* dynamic parameters to be changed is the first parameter and is   */
          /* of format DynamicFramePos = <frameno>. Here first 2 fscanf will  */
          /* read "DynamicFramePos" & "=" and the next fscanf will read the   */
          /* frame number                                                     */
          /*------------------------------------------------------------------*/
          fscanf(fDynamicParamChgFile[insChanid], "%s", tempDynamicFramePos);
          fscanf(fDynamicParamChgFile[insChanid], "%s", tempDynamicFramePos);
          fscanf(fDynamicParamChgFile[insChanid], "%d",
                                        &gConfig[insChanid].DynamicFramePos);
          fclose(fDynamicParamChgFile[insChanid]);
        }
      }
      gDataSyncUnitGap[insChanid] = DATA_SYNCH_UNIT_GAP;
      chanEndReached[insChanid]   = 0x0;
    } /* for loop 1 */

    /*------------------------------------------------------------------------*/
    /*  Do-While Loop for Encode Call                                         */
    /*------------------------------------------------------------------------*/
    do
    {
      for(insChanid=0; insChanid<inschan; insChanid++) 
      {
        if(inschan == 1)
        {
          /*------------------------------------------------------------------*/
          /* Come out of the loop when given number of frames are encoded     */
          /*------------------------------------------------------------------*/
          if(numFramesEncoded[insChanid] >=gConfig[insChanid].numInputDataUnits)
          {
            fwrite(&profileData[insChanid], 1, sizeof(sProfileData), 
                                                      fProfileTrace[insChanid]);
            fclose(fProfileTrace[insChanid]);
            goto XDM_FLUSH;
          }


        }
        else
        {
          /*------------------------------------------------------------------*/
          /* Come out of the loop when given number of frames are encoded     */
          /*------------------------------------------------------------------*/
          if(numFramesEncoded[insChanid] >=gConfig[insChanid].numInputDataUnits)
          {
            chanEndReached[insChanid] = 0x1;
          }
          for(i = 0; i < inschan; i++ )
          {
            if(chanEndReached[i])
            {
              continue;
            }
            else
            {
              break;
            }
          }
          if( i >= inschan)
          {
            goto XDM_FLUSH;
          }
        }
        if(chanEndReached[insChanid])
        {
          continue;
        }
        if((gParams[insChanid].videnc2Params.outputDataMode ==
                                                           IVIDEO_SLICEMODE) &&
          (gParams[insChanid].sliceCodingParams.sliceMode == 
                                                         IH264_SLICEMODE_BYTES))
        {
          gInitialDataUnit = gParams[insChanid].sliceCodingParams.sliceUnitSize;
          gDataSynchUnit   = gParams[insChanid].sliceCodingParams.sliceUnitSize;

#ifdef NALSTREAM_TESTING
        if(gParams[insChanid].sliceCodingParams.streamFormat==IH264_NALU_STREAM)
        {
          /* Hard coded as 4bytes for the start code considered as 0x00000001 */
          gDataSyncUnitGap[insChanid] = 0x4;
        }
        else
        {
          gDataSyncUnitGap[insChanid] = DATA_SYNCH_UNIT_GAP;
        }
#endif /*#ifdef NALSTREAM_TESTING*/

        }
        else if(gParams[insChanid].videnc2Params.outputDataMode == 
                                                               IVIDEO_SLICEMODE)
        {
          if((testCaseCounter & 0x1))
          {
            gInitialDataUnit = OUTPUT_BUFFER_SIZE;
            gDataSynchUnit   = DATA_SYNCH_UNIT;
          }
          else
          {
            gInitialDataUnit = ((numFramesEncoded[insChanid] + 0x2) << 2);
            gDataSynchUnit   = 
                 ((((numFramesEncoded[insChanid] & 0x3) + 1))* DATA_SYNCH_UNIT);
          }
        }
        else if(gParams[insChanid].videnc2Params.outputDataMode == 
                                                             IVIDEO_FIXEDLENGTH)
        {
          gInitialDataUnit = ((numFramesEncoded[insChanid] + 0x2) << 2);
          gDataSynchUnit   = 
                 ((((numFramesEncoded[insChanid] & 0x3) + 1))* DATA_SYNCH_UNIT);
        }
        else
        {
          if(inschan > 1)
          {
            /*----------------------------------------------------------------*/
            /*As getBuf can not be enabled for multi channel use case scenario*/
            /*----------------------------------------------------------------*/
            gInitialDataUnit = OUTPUT_BUFFER_SIZE;
          }
          else
          {
            gInitialDataUnit = OUTPUT_BUFFER_SIZE;
          }
          gDataSynchUnit   = 
                 ((((numFramesEncoded[insChanid] & 0x3) + 1))* DATA_SYNCH_UNIT);
        }
        /*--------------------------------------------------------------------*/
        /*  Call the getfreebuffer() function of buffermanager to get the     */
        /*  buffer element to be supplied to algorithm for the next encode    */
        /*  call.                                                             */
        /*--------------------------------------------------------------------*/
        buffEle[insChanid] = BUFFMGR_GetFreeBuffer();
        if (buffEle[insChanid] == NULL)
        {
          fprintf (stdout,"\nNo free buffer available\n");
          break;
        }
        if(inschan == 1) {
          /*------------------------------------------------------------------*/
          /* Dynamic parameter change test                                    */
          /*------------------------------------------------------------------*/
          if(gConfig[insChanid].enableRunTimeTest)
          {
            if(numFramesEncoded[insChanid] ==gConfig[insChanid].DynamicFramePos)
            {

              uiInputWidth[insChanid] = 
                      gDynamicParams[insChanid].videnc2DynamicParams.inputWidth;
              uiInputHeight[insChanid] = 
                     gDynamicParams[insChanid].videnc2DynamicParams.inputHeight;
              /*--------------------------------------------------------------*/
              /* Read dynamic parameter change config file                    */
              /*--------------------------------------------------------------*/
              if(readparamfile(dynamicparamChgFile[insChanid]) != 0)
              {
                printf("Unable to read runtime parameter change file %s\n",
                  dynamicparamChgFile[insChanid]);
                return(XDM_EFAIL);
              }
              memcpy((void *)(&gDynamicParams[insChanid]),
             (const void *)(&gDynamicParamsOrg), sizeof(H264ENC_DynamicParams));

              printf("\nRequested dynamic parameter change at Frame #%-5d ... ",
                (numFramesEncoded[insChanid]));
              if (inschan == 1)
              {
                fprintf(fTrace_file[insChanid],
                  "\nRequested dynamic parameter change at Frame #%-5d .... ",
                  (numFramesEncoded[insChanid]));
              }
            H264ENC_TI_InitDynamicParams(&gParams[insChanid],
                                                    &gDynamicParams[insChanid]);
              /*--------------------------------------------------------------*/
              /*XDM_SETPARAMS is called to pass the Dynamic Parameters to the */
              /*codec. The Control function shall validate the parameters.    */
              /*If an error is found then the Control function returns failure*/
              /*--------------------------------------------------------------*/
              retValue[insChanid] = H264ENC_control(handle[insChanid],
                XDM_SETPARAMS,
                (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                (H264ENC_Status *)&status[insChanid]);

              if(retValue[insChanid] == XDM_EFAIL)
              {
                printf("Failed in dynamicParams setting.\n");
                printf("Check the dynamicParams settings.\n");
                if(inschan == 1) {
                  H264ENC_TI_Report_Error(fTrace_file[insChanid],
                                 status[insChanid].videnc2Status.extendedError);
                 H264ENC_control(handle[insChanid],XDM_GETSTATUS,
                 (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
                 H264ENC_TI_Report_ExtError(fTrace_file[insChanid],
                                            &status[insChanid].extErrorCode[0]);
                 fprintf(fTrace_file[insChanid], 
                                          "Failed in dynamicParams setting.\n");
                 fprintf(fTrace_file[insChanid], 
                                         "Check the dynamicParams settings.\n");
                }
                /* Delete only if it is a FATAL Error else continue */
                if(XDM_ISFATALERROR(status[insChanid].
                                                  videnc2Status.extendedError))
                {
                  goto DELETE_INSTANCE;
                }
              }
              /*--------------------------------------------------------------*/
              /* Read new yuv if there is a change in resolution              */
              /*--------------------------------------------------------------*/
              if((uiInputWidth[insChanid] != 
                  gDynamicParams[insChanid].videnc2DynamicParams.inputWidth) ||
                (uiInputHeight[insChanid] !=
                    gDynamicParams[insChanid].videnc2DynamicParams.inputHeight))
              {
                /*------------------------------------------------------------*/
                /* Open Input YUV Sequence file.                              */
                /*------------------------------------------------------------*/
                my_fclose(finFile[insChanid]);
                strcpy((char *)inFile[insChanid],
                                    (const char *)gConfig[insChanid].inputFile);
                finFile[insChanid] = 
                                my_fopen((const char *)inFile[insChanid], "rb");
                if(finFile[insChanid] == NULL)
                {
                  printf("\n Unable to open Input YUV Sequence File %s\n", 
                                                             inFile[insChanid]);
                  return(XDM_EFAIL);
                }
                frameNum[insChanid] = 0;
              }

              uiCaptureWidth[insChanid]  =
              (gDynamicParams[insChanid].videnc2DynamicParams.captureWidth +15)&
                                                                            ~15;

              /*--------------------------------------------------------------*/
              /* uiCaptureWidth ==0  means same as pitch == width             */
              /* in test application code uiCaptureWidth variable should be   */
              /* used and to codec interface level                            */
              /* gDynamicParams.videnc2DynamicParams.captureWidth             */
              /*--------------------------------------------------------------*/
              if(uiCaptureWidth[insChanid] == 0)
              {
                uiCaptureWidth[insChanid] =
                (gDynamicParams[insChanid].videnc2DynamicParams.inputWidth+15) &
                                                                           ~15 ;
              }

              printf("\nRequest Dynamic parameter change sucessful  .... \n");
              if(inschan == 1) {
                fprintf(fTrace_file[insChanid], 
                      "\nRequest Dynamic parameter change sucessful  .... \n");
              }
            }
          }
        }
        /*--------------------------------------------------------------------*/
        /*  Initialize the input buffer properties as required by algorithm   */
        /*  based on info received by preceding GETBUFINFO call.              */
        /*--------------------------------------------------------------------*/
        gInputBufDesc[insChanid].numPlanes = 2 ;
                                  /*status.videnc2Status.bufInfo.minNumInBufs;*/
        gInputBufDesc[insChanid].numMetaPlanes = 0;
        /*--------------------------------------------------------------------*/
        /* Set entire Image region in the buffer  by using config parameters  */
        /*--------------------------------------------------------------------*/
        gInputBufDesc[insChanid].imageRegion.topLeft.x = 0;
        gInputBufDesc[insChanid].imageRegion.topLeft.y = 0;
        gInputBufDesc[insChanid].imageRegion.bottomRight.x =
          uiCaptureWidth[insChanid];
        gInputBufDesc[insChanid].imageRegion.bottomRight.y =
                                               gConfig[insChanid].captureHeight;
        /*--------------------------------------------------------------------*/
        /* Set proper Image region in the buffer  by using config parameters  */
        /*--------------------------------------------------------------------*/
        gInputBufDesc[insChanid].activeFrameRegion.topLeft.x =
                                             gConfig[insChanid].captureTopLeftx;
        gInputBufDesc[insChanid].activeFrameRegion.topLeft.y =
                                             gConfig[insChanid].captureTopLefty;
        gInputBufDesc[insChanid].activeFrameRegion.bottomRight.x =
                                            gConfig[insChanid].captureTopLeftx +
                      gDynamicParams[insChanid].videnc2DynamicParams.inputWidth;
        gInputBufDesc[insChanid].activeFrameRegion.bottomRight.y =
                                            gConfig[insChanid].captureTopLefty +
                     gDynamicParams[insChanid].videnc2DynamicParams.inputHeight;
        /*--------------------------------------------------------------------*/
        /* Image pitch is capture width                                       */
        /*--------------------------------------------------------------------*/
        gInputBufDesc[insChanid].imagePitch[0] =                        
          gDynamicParams[insChanid].videnc2DynamicParams.captureWidth;  
        gInputBufDesc[insChanid].imagePitch[1] =                        
          gDynamicParams[insChanid].videnc2DynamicParams.captureWidth;  
        /*--------------------------------------------------------------------*/
        /* Set Content type and chroma format from encoder parameters         */
        /*--------------------------------------------------------------------*/
        gInputBufDesc[insChanid].contentType =
                              gParams[insChanid].videnc2Params.inputContentType;
        gInputBufDesc[insChanid].chromaFormat =
                             gParams[insChanid].videnc2Params.inputChromaFormat;

        /*--------------------------------------------------------------------*/
        /* Assign memory pointers adn sizes for the all the input buffers     */
        /*--------------------------------------------------------------------*/
        for(i = 0; i < status[insChanid].videnc2Status.bufInfo.minNumInBufs;
                                                                            i++)
        {
          gInputBufDesc[insChanid].planeDesc[i].bufSize.bytes  =
            (XDAS_Int32)buffEle[insChanid]->bufSize[i];
          /*------------------------------------------------------------------*/
          /* Make the input buffer start address to 1 byte aligned , This is  */
          /* to make sure support of unaligned input buffer base address      */
          /* working This is just for test purpose. in system until unless    */
          /* required, it should be aligned to 16 byte boundary..             */
          /* Here same line of code for TILED16 & else part is kept intensely */
          /* For testing unaligned input buffer base address support, the     */
          /* allignment should be minimum 2 byte in case of TILED16 & 1 byte  */
          /* for other cases                                                  */
          /*------------------------------------------------------------------*/
          if(gConfig[insChanid].tilerSpace[i] == XDM_MEMTYPE_TILED16)
          {
            gInputBufDesc[insChanid].planeDesc[i].buf =
            (XDAS_Int8 *)((((XDAS_UInt32)buffEle[insChanid]->buf[i]+15)& 
                                                                   (~15)) + 0);
          }
          else
          {
            gInputBufDesc[insChanid].planeDesc[i].buf =
              (XDAS_Int8 *)((((XDAS_UInt32)buffEle[insChanid]->buf[i] + 15) & 
                                                                   (~15)) + 0);
          }
          gInputBufDesc[insChanid].planeDesc[i].memType =
            status[insChanid].videnc2Status.bufInfo.inBufMemoryType[0];

          /*------------------------------------------------------------------*/
          /* Overwrite the memory request from config file                    */
          /*------------------------------------------------------------------*/
          gInputBufDesc[insChanid].planeDesc[i].memType = 
                                             gConfig[insChanid].tilerSpace[i] ;
        }
        /*--------------------------------------------------------------------*/
        /* Set second field offset width and height according to input data   */
        /* When second field of the input data starts at 0 it represents 2    */
        /* fields are seperated and provided at 2 diff process calls          */
        /* (60 process call)                                                  */
        /*--------------------------------------------------------------------*/
        if(((gInputBufDesc[insChanid].dataLayout == IVIDEO_FIELD_SEPARATED) &&
          (gConfig[insChanid].numProcessCall == 60)) &&
          (gParams[insChanid].videnc2Params.inputContentType ==
                                                            IVIDEO_INTERLACED))
        {
          gInputBufDesc[insChanid].secondFieldOffsetHeight[0] = 0;
          gInputBufDesc[insChanid].secondFieldOffsetHeight[1] = 0;
          gInputBufDesc[insChanid].secondFieldOffsetHeight[2] = 0;
        }
        else
        {
          gInputBufDesc[insChanid].secondFieldOffsetHeight[0] =
            gDynamicParams[insChanid].videnc2DynamicParams.inputHeight;
          gInputBufDesc[insChanid].secondFieldOffsetHeight[1] =
            (gDynamicParams[insChanid].videnc2DynamicParams.inputHeight >> 1);
          gInputBufDesc[insChanid].secondFieldOffsetHeight[2] =
            (gDynamicParams[insChanid].videnc2DynamicParams.inputHeight >> 1);
        }
        gInputBufDesc[insChanid].secondFieldOffsetWidth[0]  = 0;
        gInputBufDesc[insChanid].secondFieldOffsetWidth[1]  = 0;
        gInputBufDesc[insChanid].secondFieldOffsetWidth[2]  = 0;

        /*--------------------------------------------------------------------*/
        /* Initialise output discriptors                                      */
        /*--------------------------------------------------------------------*/
        outputBufDesc[insChanid].numBufs = 0;
        for(i=0; i < status[insChanid].videnc2Status.bufInfo.minNumOutBufs; i++)
        {

          outputBufDesc[insChanid].numBufs++;
          outputBufDesc[insChanid].descs[i].memType =
            status[insChanid].videnc2Status.bufInfo.outBufMemoryType[i];
          outputBufDesc[insChanid].descs[i].bufSize.bytes =
            status[insChanid].videnc2Status.bufInfo.minOutBufSize[i].bytes;

          if(i == 0)
          {
            /*----------------------------------------------------------------*/
            /* Set proper buffer addresses for bitstream data                 */
            /*----------------------------------------------------------------*/
            outputBufDesc[insChanid].descs[0].buf =
            (XDAS_Int8*)(gOutputData[insChanid] + gDataSyncUnitGap[insChanid] );
            /* TODO: Need to check thsi*/
#ifdef BITSTREAM_SUBFRAME_SYNC
            outputBufDesc[insChanid].descs[0].bufSize.bytes = gInitialDataUnit ;
#endif
          }
          else
          {
            if(status[insChanid].videnc2Status.bufInfo.minOutBufSize[i].bytes
        > ANALYTICINFO_OUTPUT_BUFF_SIZE)
            {
              printf("\nMemory couldn't get allocated for Analytic_info buf\n");
              if(inschan == 1) {
                fprintf(fTrace_file[insChanid], 
                 "\nMemory could not get allocated for Analytic info buffer\n");
              }
              goto DELETE_INSTANCE;
            }
            /*----------------------------------------------------------------*/
            /* Set proper buffer addresses for MV & SAD data                  */
            /*----------------------------------------------------------------*/
            outputBufDesc[insChanid].descs[i].buf = 
                                 (XDAS_Int8*)gAnalyticInfoOutputData[insChanid];
          }
        }
        /*--------------------------------------------------------------------*/
        /* Update the size of output buffer provided to the codec, this helps */
        /* for Data sync API implimentation                                   */
        /*--------------------------------------------------------------------*/
        gOutputDataProvided[insChanid]   =
                              outputBufDesc[insChanid].descs[0].bufSize.bytes + 
                                                    gDataSyncUnitGap[insChanid];
        /*--------------------------------------------------------------------*/
        /* Reseting of blocks recieved in previous process call. This variable*/
        /* is used only when oututDataMode is not FULL_FRAME_MODE             */
        /*--------------------------------------------------------------------*/
        gOutputBlocksRecieved[insChanid] = 0                                   ;
        /*--------------------------------------------------------------------*/
        /* Set The address of unregistered  user data in meta data plane desc */
        /*--------------------------------------------------------------------*/
        gInputBufDesc[insChanid].numMetaPlanes = 0;
        /*--------------------------------------------------------------------*/
        /* Provide approprate buffer addresses for both supported meta data:  */
        /* A. USer defined SEI message                                        */
        /* B. User Defined Scaling MAtrices                                   */
        /*--------------------------------------------------------------------*/
        if(gParams[insChanid].videnc2Params.
                        metadataType[gInputBufDesc[insChanid].numMetaPlanes]
                                            == IH264_SEI_USER_DATA_UNREGISTERED)
        {
          gInputBufDesc[insChanid].metadataPlaneDesc[gInputBufDesc[insChanid].
                    numMetaPlanes].buf =(XDAS_Int8 *)&(CameraUserDataUnReg[0]);
          gInputBufDesc[insChanid].metadataPlaneDesc[gInputBufDesc[insChanid].
                                             numMetaPlanes].bufSize.bytes = -1;
          /* sizeof(CameraUserDataUnReg); */
          gInputBufDesc[insChanid].numMetaPlanes++;

        }
        /*--------------------------------------------------------------------*/
        /* Set proper buffer addresses for user defined scaling matrix        */
        /*--------------------------------------------------------------------*/
        if(gParams[insChanid].videnc2Params.
                  metadataType[gInputBufDesc[insChanid].numMetaPlanes]
                                            == IH264_USER_DEFINED_SCALINGMATRIX)
        {
          gInputBufDesc[insChanid].
           metadataPlaneDesc[gInputBufDesc[insChanid].numMetaPlanes].buf =
            (XDAS_Int8 *)&(h264e_host_scalingMatrix[0]);
          gInputBufDesc[insChanid].metadataPlaneDesc[gInputBufDesc[insChanid].
                                            numMetaPlanes].bufSize.bytes =
            /*   -1 ;*/
            896;
          gInputBufDesc[insChanid].numMetaPlanes++;

        }
        /*--------------------------------------------------------------------*/
        /* ~~~~~Read the Water Mark input key from the specified file ~~~~~   */
        /*--------------------------------------------------------------------*/
        if(gParams[insChanid].enableWatermark)
        {
          if(!(((gInputBufDesc[insChanid].dataLayout==IVIDEO_FIELD_SEPARATED) &&
            (gConfig[insChanid].numProcessCall == 60)) &&
            (gParams[insChanid].videnc2Params.inputContentType ==
                                                          IVIDEO_INTERLACED) &&
            (numFramesEncoded[insChanid] & 0x1)))
          {          
            fread(&inArgs[insChanid].inputKey, sizeof(XDAS_UInt32), 1,
                                                      waterMarkFile[insChanid]);
          }
        }
  
        /*--------------------------------------------------------------------*/
        /*  Initialize the input ID in input arguments to the bufferid of the */
        /*  buffer element returned from getfreebuffer() function.            */
        /*--------------------------------------------------------------------*/
        inArgs[insChanid].videnc2InArgs.inputID  = buffEle[insChanid]->bufId;

        /*--------------------------------------------------------------------*/
        /*  Set forceSKIP for each frame appearing at forceSKIPPeriod         */
        /*--------------------------------------------------------------------*/
        if(gParams[insChanid].enableLongTermRefFrame == 
                                               IH264ENC_LTRP_REFERTOP_PROACTIVE)
        {
          if((numFramesEncoded[insChanid] % 
                       (XDAS_UInt32)gConfig[insChanid].LongTermRefPeriod) == 0)
          {
            if(((numFramesEncoded[insChanid] / 
                          (XDAS_UInt32)gConfig[insChanid].LongTermRefPeriod) == 
                                     gConfig[insChanid].LTRPFailureLocation0) ||
              ((numFramesEncoded[insChanid] /
                         (XDAS_UInt32)gConfig[insChanid].LongTermRefPeriod) == 
                                       gConfig[insChanid].LTRPFailureLocation1))
            {
              inArgs[insChanid].videnc2InArgs.control  =
                                                IH264ENC_CTRL_WRITE_NOREFUPDATE;
            }
            else
            {
              inArgs[insChanid].videnc2InArgs.control  = 
                                                  IH264ENC_CTRL_WRITE_REFUPDATE;
            }
          }
          else
          {
            inArgs[insChanid].videnc2InArgs.control  = 
                                              IH264ENC_CTRL_NOWRITE_NOREFUPDATE;
          }
        }
        else if((!(numFramesEncoded[insChanid] %
                        (XDAS_UInt32)gConfig[insChanid].LongTermRefPeriod)) &&
                                                  (numFramesEncoded[insChanid]))
        {
          inArgs[insChanid].videnc2InArgs.control      = 
                                            IH264ENC_CTRL_REFER_LONG_TERM_FRAME;
        }
        else if((!((numFramesEncoded[insChanid] >> 
                           ((gConfig[insChanid].numProcessCall == 60))) 
                  % (XDAS_UInt32)gConfig[insChanid].forceSKIPPeriod)) &&
                     (numFramesEncoded[insChanid]))
        {
          inArgs[insChanid].videnc2InArgs.control   = IVIDENC2_CTRL_FORCESKIP;
        }
        else if((!((numFramesEncoded[insChanid]-
           gConfig[insChanid].gdrStartFrameNum) %
          (XDAS_UInt32)gConfig[insChanid].gdrPeriod)) &&
          ((numFramesEncoded[insChanid]-
                                     gConfig[insChanid].gdrStartFrameNum) >= 0))
        {
          inArgs[insChanid].videnc2InArgs.control   = IH264ENC_CTRL_START_GDR;
        }                                         
                                                  
        else                                      
        {                                         
          inArgs[insChanid].videnc2InArgs.control   = IVIDENC2_CTRL_DEFAULT;
        }

        /*--------------------------------------------------------------------*/
        /* Force the frame encoding to IDR frame at user defined place        */
        /*--------------------------------------------------------------------*/
        if((!(numFramesEncoded[insChanid] % 
             (XDAS_UInt32)gConfig[insChanid].forceIDRPeriod)) && 
                                                  (numFramesEncoded[insChanid]))
        {
          /*------------------------------------------------------------------*/
          /* Set the dynamic parameter"forceFrame" to IDR frame and then call */
          /* controll function with setparams as command                      */
          /*------------------------------------------------------------------*/
          gDynamicParams[insChanid].videnc2DynamicParams.forceFrame = 
                                                               IVIDEO_IDR_FRAME;
          /*------------------------------------------------------------------*/
          /* Reset the "generateHeader" flag to avoid genrating only-header   */
          /* in case if IDR is requested                                      */
          /*------------------------------------------------------------------*/
          gDynamicParams[insChanid].videnc2DynamicParams.generateHeader =
                                                                  XDM_ENCODE_AU;
          H264ENC_control(handle[insChanid],XDM_SETPARAMS,
            (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
            (H264ENC_Status *)&status[insChanid]);
          /*------------------------------------------------------------------*/
          /* Reset the "force frame flag to none to avoid encoding sebsequent */
          /* frames as IDR frame                                              */
          /*------------------------------------------------------------------*/
          gDynamicParams[insChanid].videnc2DynamicParams.forceFrame = 
                                                                IVIDEO_NA_FRAME;
          /*------------------------------------------------------------------*/
          /* Set the "genHeaderFlag if it is enabled by user                  */
          /*------------------------------------------------------------------*/
          gDynamicParams[insChanid].videnc2DynamicParams.generateHeader = 
                        gDynamicParamsOrg.videnc2DynamicParams.generateHeader ;
        }

        /*--------------------------------------------------------------------*/
        /* Open Input YUV Sequence file.                                      */
        /*--------------------------------------------------------------------*/
        strcpy((char *)inFile[insChanid],
                                 (const char *)gConfig[insChanid].inputFile);
        finFile[insChanid] = my_fopen((const char *)inFile[insChanid], "rb");
        if(finFile[insChanid] == NULL)
        {
          printf("\n Unable to open Input YUV Sequence File %s\n", 
                                                             inFile[insChanid]);
          my_fclose(foutFile[insChanid]);
          return(XDM_EFAIL);
        }
        /*--------------------------------------------------------------------*/
        /*  Read Input YUV Sequence data.                                     */
        /*--------------------------------------------------------------------*/
        rValue = TestApp_ReadInputYUVData(&gInputBufDesc[insChanid],
                                        frameNum[insChanid],finFile[insChanid],
                                              gConfig[insChanid].tilerSpace[0], 
                                   gConfig[insChanid].tilerSpace[1],insChanid);
          
        if (rValue == -1)
        {  
           printf(" End of file reached \n");
           goto DELETE_INSTANCE;
        }
        /* closing the input file after reading data */
        my_fclose(finFile[insChanid]);

        /*--------------------------------------------------------------------*/
        /*  Start the encode process for one frame/field by calling the       */
        /*  H264ENC_encodeFrame() function.                                   */
        /*--------------------------------------------------------------------*/
        /*TODO: Need to check whether single processor code works are not     */
        /*  with this                           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        RMAN_activateAllResources ((IALG_Handle)handle[insChanid]);
        /*--------------------------------------------------------------------*/
        /* Init the log generation logics                                     */
        /*--------------------------------------------------------------------*/
        /*if (inschan == 1) */                                         
        {                                                              
          H264ENC_TI_Init_Log(fTrace_file[insChanid]);                 
        }                                                              
        /*--------------------------------------------------------------------*/
        /* Capture encode start time when profile is enabled                  */
        /*--------------------------------------------------------------------*/
        fflush(stdout);
      } /* end of for loop 2 */

      processList.numEntries = 0;
    numEntries             = 0;
    
      for(insChanid=0; insChanid<inschan; insChanid++)
      {
        if(!chanEndReached[insChanid])
        {
      numEntries++ ;
        }      
    }    
      for(insChanid=0; insChanid<inschan; insChanid++)
      {
        if(!chanEndReached[insChanid])
        {
         if(frameNum[0] & 0x3)
          {
            processList.processParams[numEntries - 1 - 
            processList.numEntries].handle = (IVIDENC2_Handle)handle[insChanid];
            processList.processParams[numEntries - 1 -
                     processList.numEntries].inBufs = &gInputBufDesc[insChanid];
            processList.processParams[numEntries - 1 -
                    processList.numEntries].outBufs = &outputBufDesc[insChanid];
            processList.processParams[numEntries - 1 -
                    processList.numEntries].inArgs = 
                                           (IVIDENC2_InArgs*)&inArgs[insChanid];
            processList.processParams[numEntries - 1 -
                   processList.numEntries].outArgs = 
                                         (IVIDENC2_OutArgs*)&outArgs[insChanid];
          }
          else
          {
            processList.processParams[processList.numEntries].handle = 
              (IVIDENC2_Handle)handle[insChanid];
            processList.processParams[processList.numEntries].inBufs = 
              &gInputBufDesc[insChanid];
            processList.processParams[processList.numEntries].outBufs =
              &outputBufDesc[insChanid];
            processList.processParams[processList.numEntries].inArgs = 
              (IVIDENC2_InArgs*)&inArgs[insChanid];
            processList.processParams[processList.numEntries].outArgs = 
              (IVIDENC2_OutArgs*)&outArgs[insChanid];
          }
          processList.numEntries++;
        }
      }
      
      g_handle_last             = (IALG_Handle)processList.processParams \
                                  [processList.numEntries - 1].handle;
      currProcessCallNumChannel = processList.numEntries;
      H264ENC_TI_Capture_time(PROCESS_START);
      H264ENC_encodeFrameMulti(&processList);

      /*----------------------------------------------------------------------*/
      /* Capture encode end time when profile is enabled                      */
      /*----------------------------------------------------------------------*/
      H264ENC_TI_Capture_time(PROCESS_END);

      for(insChanid=0; insChanid<inschan; insChanid++)
      {
#ifdef TIGHTER_RC_DEBUG
        H264ENC_TI_RateCtrlDump();
#endif
        if(chanEndReached[insChanid])
        {
          continue;
        }

        RMAN_deactivateAllResources((IALG_Handle)handle[insChanid]);
        gVbvBufLevel[insChanid] = outArgs[insChanid].vbvBufferLevel;
        /*--------------------------------------------------------------------*/
        /*  Check for failure message in the return value.                    */
        /*--------------------------------------------------------------------*/
        if(retValue[insChanid] != IVIDENC2_EOK)
        {
          printf("Frame encoding failed.\n");
          printf("Encoded number of bits = %d\n",
            (outArgs[insChanid].videnc2OutArgs.bytesGenerated +
            outArgs[insChanid].bytesGeneratedBotField) * 8);
          if(inschan == 1) {
            fprintf(fTrace_file[insChanid],"Frame encoding failed.\n");
            fprintf(fTrace_file[insChanid], "Encoded number of bits = %d\n",
              (outArgs[insChanid].videnc2OutArgs.bytesGenerated +
              outArgs[insChanid].bytesGeneratedBotField) * 8);
          }
        }
        /*--------------------------------------------------------------------*/
        /*  Always release buffers - which are released from the algorithm    */
        /*  side   -back to the buffer manager. The freebufID array of outargs*/
        /*  contains the sequence of bufferIds which need to be freed. This   */
        /*  gets populated by the algorithm. The following function will do   */
        /*  the job of freeing up the buffers.                                */
        /*--------------------------------------------------------------------*/
        BUFFMGR_ReleaseBuffer(
                    (XDAS_UInt32 *)outArgs[insChanid].videnc2OutArgs.freeBufID);
        /*--------------------------------------------------------------------*/
        /* Print log for the encoded frame                                    */
        /*--------------------------------------------------------------------*/
        if(gDynamicParams[insChanid].enableStaticMBCount)
        {
          printf(" \n Static MB Count = %d\n", outArgs[insChanid].numStaticMBs);
        }
        /*--------------------------------------------------------------------*/
        /*  Check for extended errors while encoding     .                    */
        /*--------------------------------------------------------------------*/
        retValue[insChanid] = H264ENC_control(handle[insChanid],XDM_GETSTATUS,
          (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
        /*--------------------------------------------------------------------*/
        /* For each and every 10 frames change the handle and Get Input data  */
        /* API to check codec functionality                                   */
        /*--------------------------------------------------------------------*/
        if(!(numFramesEncoded[insChanid] % 10))
        {
          if(gDynamicParams[insChanid].videnc2DynamicParams.getDataHandle ==
            fGetInpDHandle1)
          {
            gDynamicParams[insChanid].videnc2DynamicParams.getDataHandle =
              fGetInpDHandle2;
            gDynamicParams[insChanid].videnc2DynamicParams.getDataFxn =
              H264ETest_DataSyncGetDataFxn2;
          }
          else
          {
            gDynamicParams[insChanid].videnc2DynamicParams.getDataHandle =
              fGetInpDHandle1;
            gDynamicParams[insChanid].videnc2DynamicParams.getDataFxn =
              H264ETest_DataSyncGetDataFxn1;

          }
          H264ENC_control(handle[insChanid],XDM_SETPARAMS,
            (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
            (H264ENC_Status *)&status[insChanid]);
        }
        /* if(insChanid == 0)  */
        {

    H264ENC_TI_Print_Log(fTrace_file[0],
            outArgs[insChanid].videnc2OutArgs.encodedFrameType,
            gInputBufDesc[insChanid].contentType,
            outArgs[insChanid].videnc2OutArgs.bytesGenerated,
            outArgs[insChanid].bytesGeneratedBotField,
            numFramesEncoded[insChanid]);
    
          /*H264ENC_TI_IntraRestrictDump();
          H264ENC_TI_PredictorDump();*/

          H264ENC_TI_Report_ExtError(fTrace_file[insChanid],
                                          &outArgs[insChanid].extErrorCode[0]);
          if(H264ENC_TI_Report_Error(fTrace_file[0],
                               outArgs[insChanid].videnc2OutArgs.extendedError))
          {
            printf("Encode Failed.\n");
            fprintf(fTrace_file[0], "Encode Failed.\n");
            goto DELETE_INSTANCE;
          }
        }
        /* fclose(fTrace_file[insChanid]); */

        /*--------------------------------------------------------------------*/
        /* Make sure output file is proper and empty the file if it already   */
        /* exists By open and close the file and reopen the file              */
        /*--------------------------------------------------------------------*/
        strcpy((char *)outFile[insChanid],
                                   (const char *)gConfig[insChanid].outputFile);
        foutFile[insChanid] = my_fopen((const char *)outFile[insChanid], "ab+");
        if(foutFile[insChanid] == NULL)
        {
          printf("\n Unable to open Output Bitstream File %s\n",
                                                            outFile[insChanid]);
          return(XDM_EFAIL);
        }



        /*--------------------------------------------------------------------*/
        /*  Write the Output Bitstream to a file.                             */
        /*--------------------------------------------------------------------*/
        if((outArgs[insChanid].videnc2OutArgs.bytesGenerated ))
        {
          TestApp_WriteOutputData(outputBufDesc[insChanid].descs[0].buf,
            (outArgs[insChanid].videnc2OutArgs.bytesGenerated),
            foutFile[insChanid],gParams[insChanid].videnc2Params.outputDataMode,
            gParams[insChanid].videnc2Params.numOutputDataUnits,
            gParams[insChanid].sliceCodingParams.streamFormat,insChanid);
        }
        /* closing the outfput file after writing data*/
        my_fclose(foutFile[insChanid]);
        /* TODO : Need to remove this */

#if RECON_DUMP /*  def ENABLE_RECON_PLANES                                    */
        {
          if(outArgs[insChanid].videnc2OutArgs.reconBufs.numPlanes)
          {
            /*----------------------------------------------------------------*/
            /* Buffer Pointers to the reconstructed frame                     */
            /*----------------------------------------------------------------*/
            XDAS_UInt8 *pubYRecon;
            XDAS_UInt8 *pubURecon;
            XDAS_UInt8 *pubVRecon;

            XDAS_UInt8 *pubInBufY[2];
            XDAS_UInt8 *pubInBufUV[2];
            unsigned char ubIsField;
            /*----------------------------------------------------------------*/
            /* Recon Dump of interlace type in progressive format.            */
            /*----------------------------------------------------------------*/

            ubIsField = gParams[insChanid].videnc2Params.inputContentType ;
            uiSize[insChanid] = 
                  (gDynamicParams[insChanid].videnc2DynamicParams.inputHeight 
                                                                  << ubIsField)
              * gDynamicParams[insChanid].videnc2DynamicParams.inputWidth;
            pubYRecon = malloc(uiSize[insChanid] * sizeof(XDAS_Int8));
            pubURecon = malloc((uiSize[insChanid] >> 2) * sizeof(XDAS_Int8));
            pubVRecon = malloc((uiSize[insChanid] >> 2) * sizeof(XDAS_Int8));

            pubInBufY[0]  = (XDAS_UInt8 *)
                   outArgs[insChanid].videnc2OutArgs.reconBufs.planeDesc[0].buf;
            pubInBufUV[0] = (XDAS_UInt8 *)
                   outArgs[insChanid].videnc2OutArgs.reconBufs.planeDesc[1].buf;

            ConvertFrame_Field_Out(pubYRecon,
              pubURecon,
              pubVRecon,
              pubInBufY,
              pubInBufUV,
              gDynamicParams[insChanid].videnc2DynamicParams.inputWidth,
              gDynamicParams[insChanid].videnc2DynamicParams.inputHeight,
              outArgs[insChanid].videnc2OutArgs.reconBufs.imagePitch[0],
              ubIsField
              
              );

            WriteReconOut(pubYRecon,
              pubURecon,
              pubVRecon,
              gDynamicParams[insChanid].videnc2DynamicParams.inputWidth,
              (gDynamicParams[insChanid].videnc2DynamicParams.inputHeight<<
                                                          ubIsField),
              pfOutYUVFile[insChanid]
              );


            free(pubYRecon);
            free(pubURecon);
            free(pubVRecon);
          }
        }
#endif

#ifdef COMPARE_OUTPUT
        if(inschan == 1)
        {
          /*----------------------------------------------------------------*/
          /*  Compare the output frames with the Reference File.            */
          /*----------------------------------------------------------------*/
          retValue[insChanid] = TestApp_CompareOutputData(frefFile[insChanid],
            &outputBufDesc[insChanid],
            (outArgs[insChanid].videnc2OutArgs.bytesGenerated + 
                                    outArgs[insChanid].bytesGeneratedBotField));
          if(retValue[insChanid] != IVIDENC2_EOK)
          {
            /* Test Compliance Failed... Breaking...*/
            fprintf(stdout, "\nFrame Compliance Test: FAIL. \n");
            goto XDM_FLUSH;
          }
          fprintf(stdout,"\nFrame Compliance Test: PASS. \n");
        }
#endif /* COMPARE_OUTPUT */
        /*--------------------------------------------------------------------*/
        /*  Increment the FramesEncoded count.                                */
        /*--------------------------------------------------------------------*/
        numFramesEncoded[insChanid]++;
        frameNum[insChanid] ++;
        /*--------------------------------------------------------------------*/
        /* whether XDM reset test is required, when it is required            */
        /*  - Check whether total number of frames to be encoded is completed */
        /*  - when completed reopen the output and log files Make get encoder */
        /*    state to reset position and continue loop                       */
        /*--------------------------------------------------------------------*/
        if(uiReset_Test[insChanid])
        {
          if(numFramesEncoded[insChanid] >=gConfig[insChanid].numInputDataUnits)
          {
            /*----------------------------------------------------------------*/
            /* Reset then encoder with XDM_RESET controll command             */
            /*----------------------------------------------------------------*/
            H264ENC_control(handle[insChanid],XDM_RESET,
              (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);

            strcpy((char *)outFile[insChanid],
                                   (const char *)gConfig[insChanid].outputFile);
            strcat((char *)outFile[insChanid], "_reset.264");
            foutFile[insChanid] =
                                 fopen((const char *)outFile[insChanid], "ab+");
            if(foutFile[insChanid] == NULL)
            {
              printf("\n Unable to open Output Bitstream File %s\n",
                                                            outFile[insChanid]);
              return(XDM_EFAIL);
            }
            /*----------------------------------------------------------------*/
            /* Close the log file open new files appending ".reset"           */
            /*----------------------------------------------------------------*/

            strcpy((char *)scTraceFile[insChanid], 
                                   (const char *)gConfig[insChanid].outputFile);
            strcat((char *)scTraceFile[insChanid], "_reset");
            strcat((char *)scTraceFile[insChanid], ".txt");
            if(inschan == 1) {
              fclose(fTrace_file[insChanid]);
              fTrace_file[insChanid] = 
                               fopen((const char *)scTraceFile[insChanid], "w");
              if(fTrace_file[insChanid] == NULL)
              {
                printf("\nUnable to open Log File %s\n",fTrace_file[insChanid]);
                return(XDM_EFAIL);
              }
              fprintf(fTrace_file[insChanid], 
                 "Testing: %s\nwith config %s \n",gConfig[insChanid].inputFile,
                  gConfig[insChanid].outputFile);

            }
            printf("Testing: %s\nwith config %s \n",
                    gConfig[insChanid].inputFile,gConfig[insChanid].outputFile);
            /* fprintf(fTrace_file[insChanid], "Testing: %s\nwith config %s \n",
                  gConfig[insChanid].inputFile,gConfig[insChanid].outputFile);*/
            /*----------------------------------------------------------------*/
            /* Make number of frames encoded to zero so that input YUV reading*/
            /* starts from the start and encodes same number of frames        */
            /*----------------------------------------------------------------*/
            numFramesEncoded[insChanid] = 0;
            /*----------------------------------------------------------------*/
            /* Set the reset flag to zero to come of dead lock situation      */
            /*----------------------------------------------------------------*/
            uiReset_Test[insChanid] = 0;
          }
        }
      }    /* end of for loop 4 */
    } while(1);

XDM_FLUSH:
    /*------------------------------------------------------------------------*/
    /*  Flush the codec                                                       */
    /*  Call XDM flush to inform algorithm that we are going to flush all     */
    /*  input frames given                                                    */
    /*------------------------------------------------------------------------*/
    for(insChanid=0; insChanid < inschan; insChanid++) 
    {
      H264ENC_control(handle[insChanid],XDM_FLUSH,
                         (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);
    }
    do
    {
      for(insChanid=0; insChanid < inschan; insChanid++) 
      {
        outputBufDesc[insChanid].numBufs = 1;
        outputBufDesc[insChanid].descs[0].buf = 
                                             (XDAS_Int8*)gOutputData[insChanid];
        /*-------------------------------------------------------------------*/
        /* To verify the data synch while putting EOS/EOSeq.                 */
        /*-------------------------------------------------------------------*/
        if(gDynamicParams[insChanid].videnc2DynamicParams.interFrameInterval <=
                                                                              1)
        {
          gInitialDataUnit = (numFramesEncoded[insChanid] & 0x1) ? 5 : 0x100;
        }
        if(gParams[insChanid].enableAnalyticinfo)
        {
          outputBufDesc[insChanid].numBufs = 2;    
          outputBufDesc[insChanid].descs[1].buf = 
            (XDAS_Int8*)gAnalyticInfoOutputData[insChanid];
          outputBufDesc[insChanid].descs[1].memType = 
            status[insChanid].videnc2Status.bufInfo.outBufMemoryType[1];
          outputBufDesc[insChanid].descs[1].bufSize.bytes =  
            status[insChanid].videnc2Status.bufInfo.minOutBufSize[1].bytes;
        }

        outputBufDesc[insChanid].descs[0].bufSize.bytes = gInitialDataUnit ;
        outputBufDesc[insChanid].descs[0].memType =
          status[insChanid].videnc2Status.bufInfo.outBufMemoryType[0];
        gOutputDataProvided[insChanid] = 
                              outputBufDesc[insChanid].descs[0].bufSize.bytes +
          gDataSyncUnitGap[insChanid] ;
        inArgs[insChanid].videnc2InArgs.inputID = 0;
        RMAN_activateAllResources ((IALG_Handle)handle[insChanid]);
        /*--------------------------------------------------------------------*/
        /* Reseting of blocks recieved in previous process call. This variable*/
        /* is used only when oututDataMode is not FULL_FRAME_MODE             */
        /*--------------------------------------------------------------------*/
        gOutputBlocksRecieved[insChanid] = 0                                   ;

        retValue[insChanid] =
          H264ENC_encodeFrame(handle[insChanid],&gInputBufDesc[insChanid],
                              &outputBufDesc[insChanid],&inArgs[insChanid],
                              &outArgs[insChanid]);

        gVbvBufLevel[insChanid] = outArgs[insChanid].vbvBufferLevel;
        RMAN_deactivateAllResources((IALG_Handle)handle[insChanid]);
        if(XDM_ISINSUFFICIENTDATA (
                               outArgs[insChanid].videnc2OutArgs.extendedError))
        {
          goto XDM_RESET;
        }
        else
        {
          printf(" #%d Bits: %d \n", (numFramesEncoded[insChanid] + 1),
            ((outArgs[insChanid].videnc2OutArgs.bytesGenerated) * 8));
        }
        /*--------------------------------------------------------------------*/
        /*  Always release buffers - which are released from the algorithm    */
        /*  side   -back to the buffer manager. The freebufID array of outargs*/
        /*  contains the sequence of bufferIds which need to be freed. This   */
        /*  gets populated by the algorithm. The following function will do   */
        /*  the job of freeing up the buffers.                                */
        /*--------------------------------------------------------------------*/
        BUFFMGR_ReleaseBuffer((XDAS_UInt32 *)
                                   outArgs[insChanid].videnc2OutArgs.freeBufID);
        /*--------------------------------------------------------------------*/
        /* opening the output file for writing the encoded data               */
        /*--------------------------------------------------------------------*/
        strcpy((char *)outFile[insChanid],
                                   (const char *)gConfig[insChanid].outputFile);


        foutFile[insChanid] = my_fopen((const char *)outFile[insChanid], "ab+");
        if(foutFile[insChanid] == NULL)
        {
          printf("\n Unable to open Output Bitstream File %s\n",
                                                            outFile[insChanid]);
          return(XDM_EFAIL);
        }
        /*--------------------------------------------------------------------*/
        /* Write the out put into buffer                                      */
        /*--------------------------------------------------------------------*/
        if(inschan == 0x1)
        {
          TestApp_WriteOutputData(outputBufDesc[insChanid].descs[0].buf,
            (outArgs[insChanid].videnc2OutArgs.bytesGenerated),
            foutFile[insChanid],gParams[insChanid].videnc2Params.outputDataMode,
            gParams[insChanid].videnc2Params.numOutputDataUnits,
            gParams[insChanid].sliceCodingParams.streamFormat,insChanid);
        }
        my_fclose(foutFile[insChanid]);
      } /* end of for loop 6 */
      /* closing the outfput file after writing data*/

    }while(1);
DELETE_INSTANCE:
   inschan = insChanid + 1;
XDM_RESET:
    for(insChanid=0; insChanid<inschan; insChanid++) 
    {
      gVbvBufLevel[insChanid] = outArgs[insChanid].vbvBufferLevel;
      /*----------------------------------------------------------------------*/
      /*  DO XDM call of Reset                                                */
      /*----------------------------------------------------------------------*/
      H264ENC_control(handle[insChanid],XDM_RESET,
                            (H264ENC_DynamicParams *)&gDynamicParams[insChanid],
                                          (H264ENC_Status *)&status[insChanid]);


      if(isAcquireCallMade != 0)
      {
        fprintf(stdout,"HDVICP is not in released state while exiting..\n");
      }
      if(gParams[insChanid].enableWatermark)
      {
        fclose(waterMarkFile[insChanid]);
      }
      /* if(count == 0) */
      {
        fclose(fTrace_file[0]);
      }
      if(inschan == 1) {
#ifdef COMPARE_OUTPUT
        fclose(frefFile[insChanid]);
#endif
        if(status[insChanid].debugTraceLevel)
        {
          strcpy((char *)scTraceFile[insChanid],
                                   (const char *)gConfig[insChanid].outputFile);
          strcat((char *)scTraceFile[insChanid], "debugTrace.bin");
          fTrace_file[insChanid] = 
                              fopen((const char *)scTraceFile[insChanid], "wb");
          if(NULL == fTrace_file[insChanid])
          {
            fprintf(stdout,"Could not open the debug trace file \n");
          }
          else
          {
            fwrite(status[insChanid].extMemoryDebugTraceAddr,1,
              status[insChanid].extMemoryDebugTraceSize,fTrace_file[insChanid]);
            fclose(fTrace_file[insChanid]);
          }
        }
      }
#if RECON_DUMP
      my_fclose(pfOutYUVFile[insChanid]);
#endif
      /*----------------------------------------------------------------------*/
      /*  The algorithm currently does not guarantee to set freebufid of      */
      /*  all buffers in use.                                                 */
      /*  This is managed for now by an application function. Note that       */
      /*  doing this has significance only when running multiple streams.     */
      /*----------------------------------------------------------------------*/
      BUFFMGR_ReleaseAllBuffers();                                       
      /*----------------------------------------------------------------------*/
      /*  Free the buffers allocated for through IRES-RMAN.                   */
      /*----------------------------------------------------------------------*/
      RMAN_FreeResources((IALG_Handle)handle[insChanid]);                
      /*----------------------------------------------------------------------*/
      /*  Delete the Encoder Instance.                                        */
      /*----------------------------------------------------------------------*/
      H264ENC_delete(handle[insChanid]);
    }/* end of for loop 7 */

  }

  fclose(fTestCasesFile);
  /*--------------------------------------------------------------------------*/
  /* use abort function to go to loader_exit() without doing any thing        */
  /* This helps for PCI driver to reset and run again from the start          */
  /*--------------------------------------------------------------------------*/
  abort();
}


/* ======================================================================== */
/*  End of file:  H264EncTest.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2006 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
