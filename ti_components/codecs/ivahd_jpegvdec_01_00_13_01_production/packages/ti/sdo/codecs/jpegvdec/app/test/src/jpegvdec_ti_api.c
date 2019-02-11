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
* @file      jpegvdec_ti_api.c                      
*
* @brief     This File contains the definition of xDM APIs
*
* @author    Odanaka
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan]  
*
********************************************************************************
*/

/*----------------------compilation control switches -------------------------*/

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>

/*----------------------program files ----------------------------------------*/
#include "ijpegvdec.h"

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/* ------------------------------ macros ------------------------------------ */

/*----------function prototypes ----------------------------------------------*/

/**
********************************************************************************
*  @fn          jpgVDEC_create(const IJPEGVDEC_Fxns   *fxns,
*                              const IJPEGVDEC_Params *prms)
*
*  @brief       Create an jpgVDEC instance object using specified parameters  
*
*  @param [in]  fxns              :  Handle to ALG functions
*
*  @param [in]  prms              :  Parameter specific to current instance
*
*  @return      handle            :  Algorithm instance handle.
********************************************************************************
*/
IJPEGVDEC_Handle jpgVDEC_create(
const IJPEGVDEC_Fxns   *fxns,
const IJPEGVDEC_Params *prms
)
{
  IJPEGVDEC_Handle handle;
  /*--------------------------------------------------------------------------*/
  /*Call API to create the algorithm instance with the parameters given by the*/
  /*application                                                               */
  /*--------------------------------------------------------------------------*/
  handle =  ((IJPEGVDEC_Handle)ALG_create((IALG_Fxns   *)fxns, NULL, 
  (IALG_Params *)prms));
  return handle; 
} /* jpgVDEC_create() */



/**
********************************************************************************
*  @fn          jpgVDEC_control(IJPEGVDEC_Handle        handle,
*                               IJPEGVDEC_Cmd           cmd, 
*                               IJPEGVDEC_DynamicParams *params,
*                               IJPEGVDEC_Status        *status)
*
*  @brief       Function to either write to the read/write parameters in the
*           status structure or to read all the parameters in the status
*           structure. This function will change the configuration of the 
*           decoder before the process call of each frame by using the 
*           command type
*
*  @param [in]  handle            :  Algorithm instance handle
*
*  @param [in]  cmd               :  instance to the control command of JPEG 
*                                    decoder
*
*  @param [in]  params            :  pointer to the structure containing 
*                                   run-time parameters for jpegVDEC objects
*
*  @param [in]  status            :  pointer to the jpgVDEC status structure
*
*  @return      (Pass/Error)      :  Decode call status
********************************************************************************
*/
Int jpgVDEC_control(IJPEGVDEC_Handle        handle,
IJPEGVDEC_Cmd           cmd, 
IJPEGVDEC_DynamicParams *params,
IJPEGVDEC_Status        *status
)
{
  Int error;
  /*--------------------------------------------------------------------------*/
  /* ALG_activate function to be called before each control call to copy      */
  /* image of handle structure data in the external persistant memory to      */
  /* scarcth memory                                                           */
  /*--------------------------------------------------------------------------*/
  ALG_activate((IALG_Handle)handle);                                          
  error =   handle->fxns->ividdec.control ((IVIDDEC3_Handle)handle,           
  cmd,                                                                        
  (IVIDDEC3_DynamicParams *)params,                                           
  (IVIDDEC3_Status *)status                                                   
  );                                                                          
  
  /*--------------------------------------------------------------------------*/
  /* ALG_deactivate function to be called after each control call to          */
  /* store image of handle structure data in the scarcth  memory to           */
  /* external persistant memory                                               */
  /*--------------------------------------------------------------------------*/
  ALG_deactivate((IALG_Handle)handle);
  return (error);
}/* jpgVDEC_control() */


/**
********************************************************************************
*  @fn          jpgVDEC_delete(IJPEGVDEC_Handle handle)
*
*  @brief       Delete the jpgVDEC instance object specified by handle 
*
*  @param [in]  handle            :  Algorithm instance handle
*
*  @return      None.
********************************************************************************
*/
void jpgVDEC_delete(IJPEGVDEC_Handle handle)
{
  ALG_delete((IALG_Handle)handle);
}/* jpgVDEC_delete() */



/**
********************************************************************************
*  @fn          jpgVDEC_init()
*
*  @brief       jpgVDEC module initialization
*
*  @return      None.
********************************************************************************
*/
void  jpgVDEC_init(void)
{
  return;
}/* jpgVDEC_init() */
/**
********************************************************************************
*  @fn          jpgVDEC_exit()
*
*  @brief       jpgVDEC module finalization
*
*  @return      None.
********************************************************************************
*/

void  jpgVDEC_exit(void)
{
  return;
} /* jpgVDEC_exit() */



/**
********************************************************************************
*  @fn          jpgVDEC_decode(IJPEGVDEC_Handle  handle,
*                              XDM2_BufDesc     *input,
*                              XDM2_BufDesc      *output, 
*                              IJPEGVDEC_InArgs  *inarg, 
*                              IJPEGVDEC_OutArgs *outarg)
*
*  @brief       Function to process one decode call
*
*  @param [in]  handle            :  Algorithm instance handle
*
*  @param [in]  input             :  Input buffer descriptors
*
*  @param [in]  output            :  Output buffer descriptors
*
*  @param [in]  inarg             :  Input arguments handle  
*
*  @param [in]  outarg            :  Output arguments handle     
*
*  @return      (Pass/Error)      :  Decode call status
********************************************************************************
*/
Int jpgVDEC_decode(IJPEGVDEC_Handle  handle,
XDM2_BufDesc     *input,
XDM2_BufDesc      *output, 
IJPEGVDEC_InArgs  *inarg, 
IJPEGVDEC_OutArgs *outarg)
{
  Int error;
  /*--------------------------------------------------------------------------*/
  /* ALG_activate function to be called before each process call to copy      */
  /* image of handle structure data in the external persistant memory to      */
  /* scarcth memory                                                           */
  /*--------------------------------------------------------------------------*/
  ALG_activate((IALG_Handle)handle);                                          
  
  error = handle->fxns->ividdec.process ((IVIDDEC3_Handle)handle,             
  input,                                                                      
  output,                                                                     
  (IVIDDEC3_InArgs * )inarg,                                                  
  (IVIDDEC3_OutArgs *)outarg                                                  
  );                                                                          
  
  /*--------------------------------------------------------------------------*/
  /* ALG_deactivate function to be called after each process call to          */
  /* store image of handle structure data in the scarcth  memory to           */
  /* external persistant memory                                               */
  /*--------------------------------------------------------------------------*/
  ALG_deactivate((IALG_Handle)handle);
  return(error);
} /* jpgVDEC_decode() */




