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
* @file      jpegvdec_ti_api.h                     
*
* @brief     A header file describing funtion protypes for jpeg decoder
*            interface functions with rapers.
*
* @author    Odanaka
*
* @version 0.0 (Dec 2008) : Created the initial version.[Odanaka]
*
* @version 0.1 (Feb 2010) : Cleaned code to adhere for the coding guidelines
*                           [Chetan] 
*
*******************************************************************************
*/

/* ---------------------compilation control switches -------------------------*/

#ifndef _JPEGVDEC_API_
#define _JPEGVDEC_API_

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

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

/* ------------------------- function prototypes ---------------------------- */

extern IJPEGVDEC_Handle jpgVDEC_create(
const IJPEGVDEC_Fxns   *fxns,
const IJPEGVDEC_Params *prms
);

extern Int  jpgVDEC_control(
IJPEGVDEC_Handle        handle, 
IJPEGVDEC_Cmd           cmd, 
IJPEGVDEC_DynamicParams *params, 
IJPEGVDEC_Status        *status
);


extern void  jpgVDEC_delete(IJPEGVDEC_Handle handle);

extern void  jpgVDEC_init(void);

extern void  jpgVDEC_exit(void);

extern Int jpgVDEC_decode(
IJPEGVDEC_Handle    handle,
XDM2_BufDesc     * input,
XDM2_BufDesc      * output,
IJPEGVDEC_InArgs  * inarg,
IJPEGVDEC_OutArgs * outarg
);

#endif /* _JPGVDEC_API_ */




