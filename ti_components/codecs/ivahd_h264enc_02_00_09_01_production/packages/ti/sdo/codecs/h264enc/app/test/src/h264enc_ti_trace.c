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
 * @file h264enc_ti_trace.c                         
 *                                       
 * @brief Trace level rootines
 *  
 * @author: Deepak Poddar  (deepak.poddar@ti.com)
 *
 * @version 0.1 (Oct 2009) : Intial version created
 *                           [Deepak Poddar]
********************************************************************************
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <h264enc_ti_config.h>
#include <h264enc_ti_test.h>
#ifdef RC_DEBUG
#include <rateCtrlDebug.h>
void H264ENC_TI_RateCtrlDump()
{
  sRateCtrlDebug_t* rcDebug = (sRateCtrlDebug_t*)((0xBA090000 + 0x000007C0));

  sRateCtrlDebug_t* rcDebug = (sRateCtrlDebug_t*)((0xD7E3BE8C));
  printf("\n gAdj:%d, PrevQs:%d ",rcDebug->globalAdjust,rcDebug->prevPGopQs);

  printf("\n n':%d,N':%d ",   rcDebug->numPicScaledInUnitQ4, 
                              rcDebug->totPicScaledInUnitQ4);

  printf("\n b:%d,T-b:%d ",   rcDebug->numBitsConsumedInCurUnit, 
                              rcDebug->remainingBitsInCurUnit);

  printf("\n wtdAvQs:%d,%d,%d",   rcDebug->wtdAvgQs[2],
                                  rcDebug->wtdAvgQs[0],
                                  rcDebug->wtdAvgQs[1]);
                                  
  printf("\n wtdAvgBits:%d,%d,%d",   rcDebug->wtdAvgBits[2],
                                     rcDebug->wtdAvgBits[0],
                                     rcDebug->wtdAvgBits[1]);
                                     
  printf("\n sumQsInCurUnit:%d,%d,%d",
                                   rcDebug->sumQsInCurUnit[2],
                                   rcDebug->sumQsInCurUnit[0],
                                   rcDebug->sumQsInCurUnit[1]);
                                   
  printf("\n sumBitsInCurUnit:%d,%d,%d",
                                 rcDebug->sumBitsInCurUnit[2],
                                 rcDebug->sumBitsInCurUnit[0],
                                 rcDebug->sumBitsInCurUnit[1]);
                                  
  printf("\n sumQsGop:%d",  rcDebug->qScaleSumOfPGop);
  printf("\n baseQs:%d",    rcDebug->baseQs);
  printf("\n minbaseQs:%d", rcDebug->minCurPicQs);
  printf("\n maxQs:%d",     rcDebug->qsMax);
  printf("\n minQs:%d",     rcDebug->qsMin);

  printf("\n Fulleness Level = %d",rcDebug->FullenessLevel);
  printf("\n runningQsI = %d \n",       rcDebug->runningQsI);



  printf("\n");

}
#endif
#define ICONT1_DTCM_FREE_SPACE_IR (0x5A002C10)
#define ICONT1_DTCM_FREE_SPACE_MD (0x5A002C30) 
void H264ENC_TI_IntraRestrictDump()
{
  printf("\n totalDelay = %d", *((int*)ICONT1_DTCM_FREE_SPACE_IR));
  printf("\n bufferFullness = %d", *((int*)ICONT1_DTCM_FREE_SPACE_IR + 1));
  printf("\n averageIntraCount = %d", *((int*)ICONT1_DTCM_FREE_SPACE_IR + 2));
  printf("\n percIncrease = %d", *((int*)ICONT1_DTCM_FREE_SPACE_IR + 3));
  printf("\n intraInterOffset1 = %d\n", *((int*)ICONT1_DTCM_FREE_SPACE_IR + 4));
  printf("\n intraInterOffset2 = %d\n", *((int*)ICONT1_DTCM_FREE_SPACE_IR + 5));
}

void H264ENC_TI_PredictorDump()
{
  int* Psatck = (int*)ICONT1_DTCM_FREE_SPACE_MD;
  short temp,i;

  printf(" \n Predictors :: ");
  for(i = 0; i < 12; i++)
  {
    temp  = (short)(*Psatck & 0x0000FFFF);
    printf("<%d,",temp);
    temp  = (short)(((*Psatck++) >> 16) & 0x0000FFFF);
    printf(" %d>",temp);
  }
  printf(" \n |MV: |CurrMBAddr =  %5d | directCost = %5d | direct Mvx = %5d | \
  direct Mvy = %5d | minMBCOst = %5d | mvx = %5d | mvy =%5d \n",\
  Psatck[0],\
  Psatck[1],\
  Psatck[2],\
  Psatck[3],\
  Psatck[4], \
  Psatck[5],\
  Psatck[6]);
  printf(" \n ");
}
void printDTCMAddresses(int addr, int size, char** fieldName)
{ 
  int i = 0;
  short* paddr = (short*) addr;
  
  for(i=0; i < size; i++)
  {
    if(fieldName != 0)
    {
      printf("\n %s = %d", fieldName[i], *paddr++);
    }
    else
    {
      printf("\n field[%d] = %d", i , *paddr++);
    }
  }
}

