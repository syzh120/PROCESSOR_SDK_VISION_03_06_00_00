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


/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
#include <xdc/std.h>
#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/dm/ividdec3.h>
#include <ih264vdec.h>
#include <h264vdec.h>

/** 
********************************************************************************
*  @fn     h264vdec.c
*  @brief  Creates an H264VDEC instance object (using parameters specified 
*          by prms)
*          
*  @param[in] fxns    : Function pointer
*  @param[in] prms    : Parameters used for the object creation
*
*  @return   IALG_EFAIL or IALG_EOK
********************************************************************************
*/
H264VDEC_Handle H264VDEC_create(const H264VDEC_Fxns * fxns,
                                const H264VDEC_Params * prms)
{
  return ((H264VDEC_Handle) ALG_create((IALG_Fxns *) fxns,
          NULL, (IALG_Params *) prms));
}

/**
********************************************************************************
*  @fn     H264VDEC_delete
*  @brief  Deletes H264VDEC instance object 
*          
*  @param[in] handle  : H264 Decoder Hanlde 
*
*  @return None
********************************************************************************
*/
Void H264VDEC_delete(H264VDEC_Handle handle)
{
  ALG_delete((IALG_Handle) handle);
}

/**
********************************************************************************
*  @fn     H264VDEC_init
*  @brief  H264VDEC init
*          
*  @return None
********************************************************************************
*/
Void H264VDEC_init(Void)
{
}

/**
********************************************************************************
*  @fn     H264VDEC_exit
*  @brief  H264VDEC Exit
*          
*  @return None
********************************************************************************
*/
Void H264VDEC_exit(Void)
{
}

/**
********************************************************************************
*  @fn     H264VDEC_control
*  @brief  H264VDEC control
*
*  @param[in] handle      : H264 Decoder Hanlde 
*  @param[in] cmd         : Command 
*  @param[in/out] params  : Parameters 
*  @param[in/out] status  : Status
*          
*  @return IVIDDEC3_EOK or IVIDDEC3_EFAIL
********************************************************************************
*/
XDAS_Int32 H264VDEC_control(H264VDEC_Handle handle,
                            H264VDEC_Cmd cmd,
                            H264VDEC_DynamicParams * params,
                            H264VDEC_Status * status
                           )
{
  int error = 0;

  error = handle->fxns->ividdec3.control((IVIDDEC3_Handle) handle,
                                         (IVIDDEC3_Cmd)cmd,
                                         (IVIDDEC3_DynamicParams *) params,
                                         (IVIDDEC3_Status *) status
                                        );

  return error;
}

/**
********************************************************************************
*  @fn     H264VDEC_decodeFrame
*  @brief  This function decodes one frame
*
*  @param[in] processList: Container for N channels
                          1. H264 Decoder Hanlde 
*                          2. input buffer
*                          3. output buffer 
*                          4. input arguments
*                          5. output Arguments
*          
*  @return IVIDDEC3_EOK or IVIDDEC3_EFAIL
********************************************************************************
*/
XDAS_Int32 H264VDEC_decodeFrame(IH264VDEC_ProcessParamsList* processList)
{
  int error;

  error = processList->processParams[0].handle->fxns->processMulti(
                                                                  processList);

  return (error);
}


