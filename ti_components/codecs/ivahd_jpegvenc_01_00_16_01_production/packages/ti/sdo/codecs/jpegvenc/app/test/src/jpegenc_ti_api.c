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
* @file      jpegenc_ti_api.c
*
* @brief     Encoder specific XDM functions
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Aug 2010) : Review & Clean up[Vasudev]
*******************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/


/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <hdvicp20_ti_datatypedefs.h>
#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/dm/ividenc2.h>

/*--------------------- program files ----------------------------------------*/
#include <ijpegenc.h>
#include <jpegenc_ti_api.h>


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
*  @fn     JPEGVENC_create(const JPEGVENC_Fxns *fxns,
*                          const JPEGVENC_Params* prms)
*
*  @brief  Create an JPEGVENC instance object(using parameters specified by
*          prms)
*
*  @param [in]  fxns              :  Handle to ALG functions
*
*  @param [in]  prms              :  Parameter specific to current instance
*
*  @return      handle            :  Algorithm instance handle.
********************************************************************************
*/
JPEGVENC_Handle JPEGVENC_create(const JPEGVENC_Fxns *fxns,
const JPEGVENC_Params *prms)
{
  /*--------------------------------------------------------------------------*/
  /*Call API to create the algorithm instance with the parameters given by the*/
  /*application                                                               */
  /*--------------------------------------------------------------------------*/
  return ((JPEGVENC_Handle)ALG_create((IALG_Fxns*)fxns, NULL,
  (IALG_Params*)prms));
}

/**
********************************************************************************
*  @fn     JPEGVENC_delete(JPEGVENC_Handle handle)
*
*  @brief  Delete the JPEGVENC instance object specified by handle
*
*  @param  handle : Handle to Algorithm
*
*  @return none
*
********************************************************************************
*/
Void JPEGVENC_delete(JPEGVENC_Handle handle)
{
  /*--------------------------------------------------------------------------*/
  /*Call API to delete the algorithm instance                                 */
  /*--------------------------------------------------------------------------*/
  ALG_delete((IALG_Handle)handle);
}

/**
********************************************************************************
*  @fn     JPEGVENC_init(Void)
*
*  @brief  JPEGVENC module initialization
*
*  @return none
*
********************************************************************************
*/
Void JPEGVENC_init(Void){}

/**
********************************************************************************
*  @fn     JPEGVENC_exit(Void)
*
*  @brief  jpgVENC module finalization
*
*  @return none
*
********************************************************************************
*/
Void JPEGVENC_exit(Void){}

/**
********************************************************************************
*  @fn     JPEGVENC_control(JPEGVENC_Handle handle,
*                           JPEGVENC_Cmd cmd,
*                           JPEGVENC_DynamicParams *params,
*                           JPEGVENC_Status *status)
*
*  @brief   Function to either write to the read/write parameters in the
*           status structure or to read all the parameters in the status
*           structure. This function will change the configuration of the
*           decoder before the process call of each frame by using the
*           command type
*
*  @param  handle : Handle to Algorithm
*
*  @param  cmd    : Command
*
*  @param  params : Pointer to Dynamic Parameter Structure
*
*  @param  status : Pointer to Status Structure
*
*  @return none
********************************************************************************
*/
XDAS_Int32 JPEGVENC_control(JPEGVENC_Handle handle,JPEGVENC_Cmd cmd,
JPEGVENC_DynamicParams *params,JPEGVENC_Status *status)
{
  int error = 0;
  
  /*--------------------------------------------------------------------------*/
  /* ALG_activate function to be called before each control call to copy      */
  /* image of handle structure data in the external persistant memory to      */
  /* scarcth memory                                                           */
  /*--------------------------------------------------------------------------*/
  ALG_activate((IALG_Handle)handle);

  error = handle->fxns->ividenc.control((IVIDENC2_Handle)handle, cmd,
  (IVIDENC2_DynamicParams*)params, (IVIDENC2_Status*)status);
  
  /*--------------------------------------------------------------------------*/
  /* ALG_deactivate function to be called after each control call to          */
  /* store image of handle structure data in the scarcth  memory to           */
  /* external persistant memory                                               */
  /*--------------------------------------------------------------------------*/
  ALG_deactivate((IALG_Handle)handle);

  return error;
}

/**
********************************************************************************
*  @fn     JPEGVENC_encodeFrame(JPEGVENC_Handle  handle,
*                               IVIDEO2_BufDesc  *inBufs,
*                               XDM2_BufDesc     *outBufs,
*                               JPEGVENC_InArgs  *inargs,
*                               JPEGVENC_OutArgs *outargs)
*
*  @brief  Implementation of the encode operation.
*
*  @param  handle  : Handle to the Algorithm
*
*  @param  inBufs  : Pointer to Input Buffer Structure
*
*  @param  outBufs : Pointer to Output Buffer Structure
*
*  @param  inargs  : Pointer to InArgs Structure
*
*  @param  outargs : Pointer to OutArgs Structure
*
*  @return Pass/Fail
********************************************************************************
*/
XDAS_Int32 JPEGVENC_encodeFrame(JPEGVENC_Handle  handle,
IVIDEO2_BufDesc  *inBufs,XDM2_BufDesc     *outBufs,JPEGVENC_InArgs  *inargs,
JPEGVENC_OutArgs *outargs)
{
  int error;
  
  /*--------------------------------------------------------------------------*/
  /* ALG_activate function to be called before each process call to copy      */
  /* image of handle structure data in the external persistant memory to      */
  /* scarcth memory                                                           */
  /*--------------------------------------------------------------------------*/
  ALG_activate((IALG_Handle)handle);
  
  error = handle->fxns->ividenc.process((IVIDENC2_Handle)handle, inBufs,
  outBufs,(IVIDENC2_InArgs *) inargs, (IVIDENC2_OutArgs *)outargs);

  /*--------------------------------------------------------------------------*/
  /* ALG_deactivate function to be called after each process call to          */
  /* store image of handle structure data in the scarcth  memory to           */
  /* external persistant memory                                               */
  /*--------------------------------------------------------------------------*/
  ALG_deactivate((IALG_Handle)handle);
  
  return(error);
}

