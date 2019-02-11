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
********************************************************************************
 * @file <alg_create.c>                          
 *                                       
 * @brief This file contains a simple implementation of the ALG_create API 
 *        operation 
 *
 * @author: Multimedia Codecs TI
 *
 *******************************************************************************
*/

/*******************************************************************************
*                             INCLUDE FILES                           
*******************************************************************************/
#include <stdlib.h>
#include <xdc/std.h>
#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/utils/api/_alg.h>


/** 
********************************************************************************
 *  @fn     ALG_create
 *  @brief  This function does required memory callocation for the algorithm 
 *          
 *  @param[in] fxns         : Pointer to Alg Functions structure.
 *  @param[in/out] pHandle  : Handle to Algorithm structure.
 *  @param[in] params       : Pointer to Algorithm params structure required 
 *                            for mem alloc
 *          
 *  @return Poniter to the created algorithm or NULL
********************************************************************************
*/
ALG_Handle ALG_create(IALG_Fxns *fxns, IALG_Handle pHandle, IALG_Params *params)
{
  IALG_MemRec *memTab;
  Int numObjs;
  ALG_Handle alg;
  IALG_Fxns *fxnsPtr;

  if (fxns != NULL) 
  {
    numObjs = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;

    if ((memTab = (IALG_MemRec *) malloc(numObjs * sizeof(IALG_MemRec)))) 
    {
      numObjs = fxns->algAlloc(params, &fxnsPtr, memTab);
      if (numObjs <= 0) 
      {
        return (NULL);
      }

      if (_ALG_allocMemory(memTab, numObjs)) 
      {
        alg = (IALG_Handle) memTab[0].base;
        alg->fxns = fxns;
        if (fxns->algInit(alg, memTab, pHandle, params) == IALG_EOK) 
        {
          free(memTab);
          return (alg);
        }
        fxns->algFree(alg, memTab);
        _ALG_freeMemory(memTab, numObjs);
      }

      free(memTab);
    }
  }

  return (NULL);
}

/** 
********************************************************************************
 *  @fn     ALG_delete
 *  @brief  This function Deletes the instance created 
 *          
 *  @param[in]  alg         : Handle to Algorithm
 *          
 *  @return None
********************************************************************************
*/
Void ALG_delete(ALG_Handle alg)
{
  IALG_MemRec *memTab;
  Int numObjs;
  IALG_Fxns *fxns;

  if (alg != NULL && alg->fxns != NULL) 
  {
    fxns = alg->fxns;
    numObjs = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;

    if ((memTab = (IALG_MemRec *) malloc(numObjs * sizeof(IALG_MemRec)))) 
    {
      memTab[0].base = alg;
      numObjs = fxns->algFree(alg, memTab);
      _ALG_freeMemory((IALG_MemRec *) memTab, numObjs);

      free(memTab);
    }
  }
}


