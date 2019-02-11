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
* @file      alg_control.c                      
*
* @brief     This file contains a simple implementation of the ALG_control API 
*            operation. This is common to all implementations of the
*            ALG module.
*
* @author    Chetan
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan]
********************************************************************************
*/
/*----------------------compilation control switches -------------------------*/

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>

/*----------------------program files ----------------------------------------*/

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/


/** 
********************************************************************************
*  @fn     ALG_control(ALG_Handle alg,
*                     IALG_Cmd cmd, 
*                     IALG_Status *statusPtr)
*
*  @brief  It is an algorithm specific control operations.This is common to 
*          all implementations of the ALG module.
*
*  @param[in]  alg  : This handle type is used to reference all ALG 
*                            instance objects
*
*  @param[in]  cmd    :  Algorithm specific command.
*  
*  @param[out]  statusPtr :  Pointer to algorithm specific status structure.
*          
*  @return IALG_OK or IALG_EFAIL
********************************************************************************
*/
Int ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status *statusPtr)
{
  /*--------------------------------------------------------------------------*/
  /* Check for a valid handle & function pointers.                            */
  /* Return a failure in case one of these are NULL pointers.                 */
  /*--------------------------------------------------------------------------*/
  if (alg && alg->fxns->algControl) 
  {
    /*------------------------------------------------------------------------*/
    /* Make XDM control call with a XDM Command                               */
    /*------------------------------------------------------------------------*/
    return (alg->fxns->algControl(alg, cmd, statusPtr));
  }
  else
  {
    return (IALG_EFAIL);
  }

}
