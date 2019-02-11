
/* ========================================================================= */
/*            Copyright (C) 2008 Texas Instruments, Incorporated.            */
/*                           All Rights Reserved.                            */
/*  Exclusive property of the DSPS R&D Center, Texas Instruments Inc. Any    */
/*   handling, use, disclosure, reproduction, duplication, transmission, or   */
/*   storage of any part of this work by any means is subject to restrictions */
/*  and prior written permission set forth in TI's program license agreements*/
/*  and associated software documentation.                                   */
/*                                       */
/*  This copyright notice, restricted rights legend, or other proprietary    */
/*  markings must be reproduced without modification in any authorized       */
/*  copies of any part of this work.  Removal or modification of any part    */
/*  of this notice is prohibited.                                            */
/*                                       */
/*  =========================================================================*/

/*!  
 *****************************************************************************
 * \file                                     
 *  h264enc.c                         
 *                                       
 * \brief                                   
 *  Encoder specific XDM functions
 *  
 * \version 0.1
 *
 * \date Nov 2008
 *  
 * \author                                     
 *  MMCodecs TI India
 *****************************************************************************
 */

#include <xdc/std.h>

#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/dm/ividenc2.h>
#include <ih264enc.h>
#include <h264enc.h>

/*
 *  ======== H264ENC_create ========
 *  Create an H264ENC instance object (using parameters specified by prms)
 */

H264ENC_Handle H264ENC_create(const H264ENC_Fxns * fxns,
                              const H264ENC_Params * prms)
{
  return ((H264ENC_Handle) ALG_create((IALG_Fxns *) fxns,
                                      NULL, (IALG_Params *) prms));
}

/*
 *  ======== H264ENC_delete ========
 *  Delete the H264ENC instance object specified by handle
 */

Void H264ENC_delete(H264ENC_Handle handle)
{
  ALG_delete((IALG_Handle) handle);
}

/*
 *  ======== H264ENC_init ========
 *  H264ENC module initialization
 */

Void H264ENC_init(Void)
{
}

/*
 *  ======== H264ENC_exit ========
 *  H264ENC module finalization
 */

Void H264ENC_exit(Void)
{
}

/*
 *  ======== H264ENC_control ========
 */

XDAS_Int32 H264ENC_control(H264ENC_Handle handle,
                           H264ENC_Cmd cmd,
                           H264ENC_DynamicParams * params,
                           H264ENC_Status * status)
{
  int error = 0;
  IALG_Fxns *fxns = (IALG_Fxns*)handle->fxns;
  fxns->algActivate((IALG_Handle)handle);

  error = handle->fxns->ividenc.control((IVIDENC2_Handle) handle, cmd,
                                        (IVIDENC2_DynamicParams *) params,
                                        (IVIDENC2_Status *) status);
  fxns->algDeactivate((IALG_Handle)handle);

  return error;
}

/*
 *  ======== H264ENC_encode ========
 */

XDAS_Int32 H264ENC_encodeFrame(H264ENC_Handle handle,
                               IVIDEO2_BufDesc * inBufs,
                               XDM2_BufDesc * outBufs,
                               H264ENC_InArgs * inargs,
                               H264ENC_OutArgs * outargs)
{
  int error;
  IALG_Fxns *fxns = (IALG_Fxns*)handle->fxns;
  fxns->algActivate((IALG_Handle)handle);
  error = handle->fxns->ividenc.process((IVIDENC2_Handle) handle, inBufs,
                                        outBufs,
                                        (IVIDENC2_InArgs *) inargs,
                                        (IVIDENC2_OutArgs *) outargs);
  fxns->algDeactivate((IALG_Handle)handle);

  return (error);
}

XDAS_Int32 H264ENC_encodeFrameMulti(IH264ENC_ProcessParamsList *processList)
{
  int error;
  H264ENC_Handle handle = (H264ENC_Handle)processList->processParams[0].handle;

  error = handle->fxns->processMulti(processList);

  return (error);
}
