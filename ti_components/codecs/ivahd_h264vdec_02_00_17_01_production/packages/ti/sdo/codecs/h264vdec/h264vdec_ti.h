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
 * @file h264vdec_ti.h                        
 *                                       
 * @brief   Interface for the H264VDEC_TI module; TI's implementation of the 
 *          IH264VDEC interface
 *
 *
 * @author: Pavan Shastry (pavanvs@ti.com)
 *
 * @version 0.1 (Jan 2008) : Base version borrowed from DSP RnD
 * @version 0.2 (Oct 2009) : Code commenting/cleanup.
 *                           [Keshav]
 ******************************************************************************
*/

#ifndef H264VDEC_TI_
#define H264VDEC_TI_

#include <ti/xdais/ialg.h>
#include "ih264vdec.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== H264VDEC_TI_IALG ========
 *  TI's implementation of the IALG interface for H264VDEC
 */
  extern IALG_Fxns H264VDEC_TI_IALG;

/*
 *  ======== H264VDEC_TI_IH264VDEC ========
 *  TI's implementation of the IVIDDEC1 interface
 */
  extern IVIDDEC3_Fxns H264VDEC_TI_IH264VDEC;
/*
 *  ======== H264VDEC_TI_IH264VDEC ========
 *  TI's implementation of the IVIDDEC3 interface for multichannel
 */
  extern IH264VDEC_Fxns H264VDEC_TI_IH264VDEC_MULTI;

/*
 *  ======== H264VDEC_TI_exit ========
 *  Required module finalization function
 */
  extern Void H264VDEC_TI_exit(Void);

/*
 *  ======== H264VDEC_TI_init ========
 *  Required module initialization function
 */
  extern Void H264VDEC_TI_init(Void);

#ifdef __cplusplus
}
#endif             /* extern "C" */
#endif             /* H264VDEC_TI_ */
