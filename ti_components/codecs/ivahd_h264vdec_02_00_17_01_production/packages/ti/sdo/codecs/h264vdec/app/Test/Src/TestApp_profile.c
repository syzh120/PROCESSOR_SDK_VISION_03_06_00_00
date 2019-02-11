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
 * @file <TestApp_profile.c>                          
 *                                       
 * @brief  This file is a H.264 Sample test application
 *
 *         This file has H.264 sample test app functions to understand   
 *         the usage of codec function calls during integration. 
 *  
 * @author: Ramakrishna Adireddy
 *
 * @version 0.0 (Jan 2008)  : Base version borrowed from DSP R&D code base
 * @version 0.1 (Sept 2009) : Code commenting and cleanup
 *                            [Ramakrishna]
 * @version 0.2 (Jun 2010)  : Updated profiling functions for Netra EVM
 *                            [Ramakrishna]
 ******************************************************************************
*/

/******************************************************************************
*  INCLUDE FILES                                                
******************************************************************************/
#include <xdc/std.h>
#include <TestAppDecoder.h>
#include <TestApp_rmanConfig.h>

/******************************************************************************
*  MACRO DEFINITIONS                                               
******************************************************************************/
/**
 *  Mega Hertz
 */
#define MEGA_HZ   (1000000.0)


/**
 *  M3 clock frequency in Hz
 */
#ifdef NETRA
#define M3_CLOCK_FREQ   (250 * MEGA_HZ)
#else
#define M3_CLOCK_FREQ   (166 * MEGA_HZ)
#endif

/**
 *  IVAHD clock frequency in MHz
 */
#ifdef NETRA
#define IVA_CLOCK_FREQ  533.0
#else
#define IVA_CLOCK_FREQ  266.0
#endif

extern sProfileParams      profilePrms;
extern FILE *fCycles; 
extern XDAS_UInt8          appIvahdId;
extern sChannelState nChannelState[NUM_DEC_CHANNELS_SUPPORTED];

XDAS_Int32                 fileOpenDone = 0;
XDAS_UInt32 waitCount;
XDAS_UInt32 doneCount;

FILE *fProfileNums; 

/** 
********************************************************************************
 *  @fn     ConfigureProfile
 *  @brief  Need to configure the system registers for the profiling.
 *
 *  @param[in] void          : None
 *          
 *  @return none
********************************************************************************
*/
XDAS_Void ConfigureProfile(XDAS_Int8  chnlNum)
{
#ifdef DUMP_PROFILE_NUMS
  volatile int *iceCrusherCfgRegs = (volatile int *)(regBaseAdderss[appIvahdId]+
                                                     ICEC_CNT_CTRL);
  if(fileOpenDone == 0)
  {
    fProfileNums = fopen("..\\..\\..\\Test\\TestVecs\\Output\\ProfileNums.csv",
                         "w");
    fileOpenDone = 1;
  }
  if(nChannelState[chnlNum].picture_count == 0)
  {
    fprintf(fProfileNums, "%s\n\n", 
            nChannelState[chnlNum].appCntrlParams.inFile);
    fprintf(fProfileNums, "Frame, Entry, Acquire, wait1, \
            Done1, Post_Msg, Wait2, Done2, Release, Exit, Frame Level\n");
  }

  /*--------------------------------------------------------------------------*/
  /* Initialize the parameters                                                */
  /*--------------------------------------------------------------------------*/
  waitCount = 0;
  doneCount = 0;
  profilePrms.processStartTime[0]   = 0;
  profilePrms.processStartTime[1]   = 0;
  profilePrms.processEndTime[0]     = 0;
  profilePrms.processEndTime[1]     = 0;
  profilePrms.hdvicpAcquireTime[0]  = 0;
  profilePrms.hdvicpAcquireTime[1]  = 0;
  profilePrms.postIvaMsgTime[0]     = 0;
  profilePrms.postIvaMsgTime[1]     = 0;
  profilePrms.hdvicpWaitTime[0]     = 0;
  profilePrms.hdvicpWaitTime[1]     = 0;
  profilePrms.hdvicpWait2Time[0]    = 0;
  profilePrms.hdvicpWait2Time[1]    = 0;
  profilePrms.hdvicpDoneTime[0]     = 0;
  profilePrms.hdvicpDoneTime[1]     = 0;
  profilePrms.hdvicpDone2Time[0]    = 0;
  profilePrms.hdvicpDone2Time[1]    = 0;
  profilePrms.hdvicpReleaseTime[0]  = 0;
  profilePrms.hdvicpReleaseTime[1]  = 0;
  
  profilePrms.procStart_hdvicpAcquire[1]=0;
  profilePrms.hdvicpAcquire_postIvaMsg[1]=0;
  profilePrms.hdvicpAcquire_hdvicpWait[1]=0;
  profilePrms.hdvicpWait_hdvicpDone[1]=0;
  profilePrms.hdvicpDone_hdvicpWait2[1]=0;
  profilePrms.hdvicpWait2_hdvicpDone2[1]=0;
  profilePrms.hdvicpDone_hdvicpRelease[1]=0;
  profilePrms.hdvicpRelease_procEnd[1]=0;

  /*--------------------------------------------------------------------------*/
  /* Enable and Initialise the ICE CRUSHER TIMER (IVAHD)                      */
  /* This is a incrementing counter.                                          */
  /*--------------------------------------------------------------------------*/
  *iceCrusherCfgRegs = 0x40000000;
  *iceCrusherCfgRegs = 0x40000000;
  *iceCrusherCfgRegs = 0x40000000;
  *iceCrusherCfgRegs = 0x40000000;

  while(!(*iceCrusherCfgRegs & (1 << 28)))
  {
    *iceCrusherCfgRegs = 0x40000000;
  }

  /*--------------------------------------------------------------------------*/
  /* Enable Resource                                                          */
  /*--------------------------------------------------------------------------*/
  *iceCrusherCfgRegs = 0x80000000;
  *iceCrusherCfgRegs = 0x80000000 |  (1<<19) | (1<<16) ; 
  *iceCrusherCfgRegs = 0x80000000 |  (1<<19) | (1<<16) | (1<<12);

  /*--------------------------------------------------------------------------*/
  /* Cortex-M3 counter register initialization.                               */
  /* This is a decrementing counter.                                          */
  /*--------------------------------------------------------------------------*/
  SYSTICKREG = 0x4;
  SYSTICKREL = SYSTICKRELVAL;
  SYSTICKREG = 0x5;

#endif /* #ifdef DUMP_PROFILE_NUMS */

}

/** 
********************************************************************************
 *  @fn     printProfileNums
 *  @brief  Printing profiling Numbers.
 *
 *  @param[in] chnlNum      : Decoder channel number.
 *          
 *  @return none
********************************************************************************
*/
XDAS_Void printProfileNums(XDAS_Int8  chnlNum)
{

#ifdef DUMP_PROFILE_NUMS
  XDAS_UInt32 m3PreCycles , m3PostCycles, iVACycles, m3Cycles,totalCycles ;
  
  m3PreCycles  = profilePrms.procStart_hdvicpAcquire[1] +
                 profilePrms.hdvicpAcquire_hdvicpWait[1] ;
  m3PostCycles = profilePrms.hdvicpDone_hdvicpRelease[1] +
                 profilePrms.hdvicpRelease_procEnd[1]  ;

  m3Cycles     = m3PreCycles + m3PostCycles ;
  iVACycles    = profilePrms.hdvicpAcquire_hdvicpWait[1] +
                 profilePrms.hdvicpWait_hdvicpDone[1] +
                 profilePrms.hdvicpDone_hdvicpRelease[1] ;
  
  if(doneCount == 2)
  {
    m3Cycles += profilePrms.hdvicpDone_hdvicpWait2[1];
    iVACycles += profilePrms.hdvicpWait2_hdvicpDone2[1];
  }                  
  
  totalCycles = profilePrms.processStartTime[1];
  if((XDAS_Int32)(totalCycles - profilePrms.processEndTime[1])< 0)
  {
    totalCycles += SYSTICKRELVAL;
  }    
  totalCycles = totalCycles - profilePrms.processEndTime[1];

  printf("frameCount: %d, M3 Usage: %3.2f MHz(M3), IVA Usage : %3.2f MHz(IVA), Total usage: %3.2f MHz(IVA)\n",
             nChannelState[chnlNum].frameCount, ((m3Cycles*30.0)/1000000), 
             (iVACycles*30.0*IVA_CLOCK_FREQ/M3_CLOCK_FREQ), 
             (totalCycles*30.0*IVA_CLOCK_FREQ/M3_CLOCK_FREQ));                 

  /*fprintf(fProfileNums, "Frame:%d,\%f\n", frameCount, 
    (totalCycles*30.0*IVA_CLOCK_FREQ/M3_CLOCK_FREQ));*/
  fprintf(fProfileNums, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %f\n",
        nChannelState[chnlNum].frameCount,
        profilePrms.processStartTime[1],
        profilePrms.hdvicpAcquireTime[1],
        profilePrms.hdvicpWaitTime[1],
        profilePrms.hdvicpDoneTime[1],
        profilePrms.postIvaMsgTime[1],
        profilePrms.hdvicpWait2Time[1], 
        profilePrms.hdvicpDone2Time[1],
        profilePrms.hdvicpReleaseTime[1],
        profilePrms.processEndTime[1],
        (totalCycles*30.0*IVA_CLOCK_FREQ/M3_CLOCK_FREQ)
  );
#endif

  if(nChannelState[chnlNum].appCntrlParams.profileEnable)
  {
    /*-----------------------------------------------------------------------*/
    /*  Last 1K of SL2 is used for dumping profile data                      */
    /*  pProfileInfo needs to be assigned with corresponding                 */
    /*  address (1K before end of SL2)                                       */
    /*-----------------------------------------------------------------------*/
    IH264VDEC_ProfileInfo * pProfileInfo 
      = (IH264VDEC_ProfileInfo *)((Uint32)memBaseAddress[appIvahdId] + 0x3F800);
    XDAS_Int32 sliceCntr;
    
    fprintf(fCycles, "Frame %4d:\t", nChannelState[chnlNum].frameCount);

    fprintf(fCycles, "%14d" ",\t", pProfileInfo->hostPreIva);
    fprintf(fCycles, "%14d" ",\t", pProfileInfo->preMbLoop);
    fprintf(fCycles, "%14d" ",\t", pProfileInfo->inMbLoop);
    fprintf(fCycles, "%14d" ",\t", pProfileInfo->postMbLoop);
    fprintf(fCycles, "%14d" ",\t", pProfileInfo->hostPostIva);
    fprintf(fCycles, "%14d" ",\n", pProfileInfo->ivahdTotalCycles);

    sliceCntr = 0;
    while(pProfileInfo->noOfSlices)
    {
      fprintf(fCycles, "Slice#%4d" ",\t", sliceCntr+1);
      fprintf(fCycles, "%14d" ",\n", pProfileInfo->sliceTask[sliceCntr]);
      sliceCntr++;
      pProfileInfo->noOfSlices--;
    }

    fprintf(fCycles, 
           "|----------------------------------------------------|\n");

  }

}

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
XDAS_Void TestApp_captureTime(XDAS_UInt32 capLoc)
{
#ifdef DUMP_PROFILE_NUMS
  XDAS_UInt32 startTime;
  volatile int *iceCrusherCtrRegs = (volatile int *)(regBaseAdderss[appIvahdId]+
                                                     ICEC_CNT_VAL);
  switch(capLoc)
  {
  case  PROCESS_START :
    profilePrms.processStartTime[0]     = (*iceCrusherCtrRegs);
    profilePrms.processStartTime[1]   = SYSTICKVAL;
    break;
    
  case  HDVICP_ACQUIRE :
    {
      profilePrms.hdvicpAcquireTime[0]     = (*iceCrusherCtrRegs);
      profilePrms.hdvicpAcquireTime[1]   = SYSTICKVAL;
      
      startTime = profilePrms.processStartTime[1];
      if((XDAS_Int32)(startTime - profilePrms.hdvicpAcquireTime[1])< 0)
      {
        startTime += SYSTICKRELVAL;
      }
      profilePrms.procStart_hdvicpAcquire[1] =
      startTime - profilePrms.hdvicpAcquireTime[1];
      profilePrms.procStart_hdvicpAcquire[0] =
      profilePrms.hdvicpAcquireTime[0] - profilePrms.processStartTime[0];
    }
    break;
  case IVAHD_POSTMSG:
    {
      profilePrms.postIvaMsgTime[0]     = (*iceCrusherCtrRegs);
      profilePrms.postIvaMsgTime[1]   = SYSTICKVAL;
      
      startTime = profilePrms.hdvicpAcquireTime[1];
      if((XDAS_Int32)(startTime - profilePrms.postIvaMsgTime[1])< 0)
      {
        startTime += SYSTICKRELVAL;
      }
      profilePrms.hdvicpAcquire_postIvaMsg[1] =
      startTime - profilePrms.postIvaMsgTime[1];
      profilePrms.hdvicpAcquire_postIvaMsg[0] =
      profilePrms.postIvaMsgTime[0] - profilePrms.hdvicpAcquireTime[0];
    }
    break;
  case  HDVICP_WAIT :
    {
      if(waitCount == 0)
      {
        profilePrms.hdvicpWaitTime[0]     = (*iceCrusherCtrRegs);
        profilePrms.hdvicpWaitTime[1]   = SYSTICKVAL;
        
        startTime = profilePrms.hdvicpAcquireTime[1];
        if((XDAS_Int32)(startTime - profilePrms.hdvicpWaitTime[1])< 0)
        {
          startTime += SYSTICKRELVAL;
        }
        profilePrms.hdvicpAcquire_hdvicpWait[1] =
        startTime - profilePrms.hdvicpWaitTime[1];
        profilePrms.hdvicpAcquire_hdvicpWait[0] =
        profilePrms.hdvicpWaitTime[0] - profilePrms.hdvicpAcquireTime[0];
        waitCount++;
      }
      else
      {
        profilePrms.hdvicpWait2Time[0] = ICEC_CNT_VAL;
        profilePrms.hdvicpWait2Time[1] = SYSTICKVAL;
        
        startTime = profilePrms.hdvicpDoneTime[1];

        if((XDAS_Int32)(startTime - profilePrms.hdvicpWait2Time[1]) < 0)
        {
          startTime += SYSTICKRELVAL;
        }
        profilePrms.hdvicpDone_hdvicpWait2[1] =
        startTime - profilePrms.hdvicpWait2Time[1];
        profilePrms.hdvicpDone_hdvicpWait2[0] =
        profilePrms.hdvicpWait2Time[0] -
        profilePrms.hdvicpDoneTime[0];
        waitCount++;
      }
    }
    break;
    
  case  HDVICP_DONE :
    {
      if(doneCount == 0)
      {
        profilePrms.hdvicpDoneTime[0]     = (*iceCrusherCtrRegs);
        profilePrms.hdvicpDoneTime[1]   = SYSTICKVAL;
        
        startTime = profilePrms.hdvicpWaitTime[1];
        if((XDAS_Int32)(startTime - profilePrms.hdvicpDoneTime[1])< 0)
        {
          startTime += SYSTICKRELVAL;
        }
        profilePrms.hdvicpWait_hdvicpDone[1] =
        startTime - profilePrms.hdvicpDoneTime[1];
        profilePrms.hdvicpWait_hdvicpDone[0] =
        profilePrms.hdvicpDoneTime[0] - profilePrms.hdvicpWaitTime[0];
        doneCount++;
      }
      else
      {
        profilePrms.hdvicpDone2Time[0] = ICEC_CNT_VAL;
        profilePrms.hdvicpDone2Time[1] = SYSTICKVAL;

        startTime = profilePrms.hdvicpWait2Time[1];

        if((XDAS_Int32)(startTime - profilePrms.hdvicpDone2Time[1]) < 0)
        {
          startTime += SYSTICKRELVAL;
        }
        profilePrms.hdvicpWait2_hdvicpDone2[1] =
        startTime - profilePrms.hdvicpDone2Time[1];
        profilePrms.hdvicpWait2_hdvicpDone2[0] =
        profilePrms.hdvicpDone2Time[0] -
        profilePrms.hdvicpWait2Time[0];
        doneCount++;
      }
    }
    break;
    
  case  HDVICP_RELEASE :
    {
      profilePrms.hdvicpReleaseTime[0]     = (*iceCrusherCtrRegs);
      profilePrms.hdvicpReleaseTime[1]   = SYSTICKVAL;
      
      startTime = (doneCount == 1) ? 
             profilePrms.hdvicpDoneTime[1] : profilePrms.hdvicpDone2Time[1];
      if((XDAS_Int32)(startTime - profilePrms.hdvicpReleaseTime[1])< 0)
      {
        startTime += SYSTICKRELVAL;
      }
      profilePrms.hdvicpDone_hdvicpRelease[1] =
      startTime - profilePrms.hdvicpReleaseTime[1];
      if(doneCount == 1)
      {
        profilePrms.hdvicpDone_hdvicpRelease[0] =
             profilePrms.hdvicpReleaseTime[0] -
               profilePrms.hdvicpDoneTime[0];
      }
      else
      {
        profilePrms.hdvicpDone_hdvicpRelease[0] =
           profilePrms.hdvicpReleaseTime[0] -
               profilePrms.hdvicpDone2Time[0];
        
      }
    }
    
    break;
    
  case  PROCESS_END :
    {
      profilePrms.processEndTime[0]      = (*iceCrusherCtrRegs);
      profilePrms.processEndTime[1]      = SYSTICKVAL;
      startTime = profilePrms.hdvicpReleaseTime[1];
      if((XDAS_Int32)(startTime - profilePrms.processEndTime[1])< 0)
      {
        startTime += SYSTICKRELVAL;
      }
      profilePrms.hdvicpRelease_procEnd[1] =
      startTime - profilePrms.processEndTime[1];
      profilePrms.hdvicpRelease_procEnd[0] =
      profilePrms.processEndTime[0] - profilePrms.hdvicpReleaseTime[0];
      
    }
    break;

  } 
#endif /* #ifdef DUMP_PROFILE_NUMS */ 

}

