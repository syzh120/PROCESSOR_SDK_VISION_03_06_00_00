/* =========================================================================  */
/*            Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/*  Exclusive property of the DSPS R&D Center, Texas Instruments Inc. Any     */
/*   handling, use, disclosure, reproduction, duplication, transmission, or   */
/*   storage of any part of this work by any means is subject to restrictions */
/*  and prior written permission set forth in TI's program license agreements */
/*  and associated software documentation.                                    */
/*                                                                            */
/*  This copyright notice, restricted rights legend, or other proprietary     */
/*  markings must be reproduced without modification in any authorized        */
/*  copies of any part of this work.  Removal or modification of any part     */
/*  of this notice is prohibited.                                             */
/*                                                                            */
/*  ========================================================================  */

/*!  
 *****************************************************************************
 * \file                                     
 *  h264enc_ti.h                       
 *                                       
 * \brief                                   
 *  TI Interface related header file
 *  
 * \version 0.1
 *
 * \date Nov 2008
 *
 * \author                                     
 *  MMCodecs TI India
 *****************************************************************************
 */

#ifndef H264ENC_TI_
#define H264ENC_TI_

/* #include <std.h>                                                           */
#include <ti/xdais/ialg.h>

#include "ih264enc.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== H264ENC_TI_IALG ========
 *  TI's implementation of the IALG interface for H264ENC
 */
  extern const IALG_Fxns H264ENC_TI_IALG;

/*
 *  ======== H264ENC_TI_IH264ENC ========
 *  TI's implementation of the IVIDENC2 interface
 */
  extern const IH264ENC_Fxns H264ENC_TI_IH264ENC;

/*
 *  ======== H264ENC_TI_exit ========
 *  Required module finalization function
 */
  extern Void H264ENC_TI_exit(Void);

/*
 *  ======== H264ENC_TI_init ========
 *  Required module initialization function
 */
  /* extern Void H264ENC_TI_init(Void);                                       */

#ifdef __cplusplus
}
#endif             /* extern "C" */
#endif             /* H264ENC_TI_ */
