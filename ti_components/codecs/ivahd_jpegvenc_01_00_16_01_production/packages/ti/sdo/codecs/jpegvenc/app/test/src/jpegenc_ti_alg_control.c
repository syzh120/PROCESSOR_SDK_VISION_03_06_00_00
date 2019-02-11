/*
********************************************************************************
* HDVICP2.0 Based JPEG Encoder
*
* "HDVICP2.0 Based JPEG Encoder" is software module developed for
* TI's HDVICP2 based SoCs. This module is capable of encoding a raw image
* by compressing it into a JPEG bitstream compliant with ISO/IEC IS 10918-1.
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
********************************************************************************
*/
/**
********************************************************************************
* @file      jpegenc_ti_alg_control.c
*
* @brief     ALG_control implementation.  This is common to all implementations
*            of the ALG module.
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Aug 2010) : Review & Clean up[Vasudev]
********************************************************************************
*/

/* -------------------- compilation control switches -------------------------*/

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>

/*--------------------- program files ----------------------------------------*/


/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

/**
********************************************************************************
*  @fn     ALG_control(ALG_Handle alg, IALG_Cmd cmd, IALG_Status *statusPtr)
*
*  @brief  It is an algorithm specific control operations.This is common to
*          all implementations of the ALG module.
*
*  @param[in]  alg        :  This handle type is used to reference all ALG
*                            instance objects
*
*  @param[in]  cmd        :  Algorithm specific command.
*
*  @param[out]  statusPtr :  Pointer to algorithm specific status structure.
*
*  @return                :  IALG_OK or IALG_EFAIL
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
