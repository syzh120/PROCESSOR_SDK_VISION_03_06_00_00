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
* @file      jpegvdec_ti.h
*
* @brief     This file provides definisions for the interface handles.
*
* @author    Odanaka
*
* @version 0.0 (Dec 2008) : Created the initial version.
* @version 0.1 (Dec 2009)  : Added IRES interface handle[Chetan]
* @version 0.2 (Feb 2010)  : Coding Guidelines[Chetan] 
*
********************************************************************************
*/

/*----------------------compilation control switches -------------------------*/
#ifndef _IJPEGVDEC_TI_
#define _IJPEGVDEC_TI_

/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec3.h>

/*----------------------program files ----------------------------------------*/
#include "ijpegvdec.h"

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/**
* Referene to external symbol JPEGVDEC_TI_IALG, holding the pointers to the
* all the basic algorithm creation related functions.
*/
extern IALG_Fxns     JPEGVDEC_TI_IALG;

/**
* Referene to external symbol JPEGVDEC_TI_IJPEGVDEC,holding the pointers to
* the all the jpeg decoder algorithm interfaces
*/
extern IJPEGVDEC_Fxns JPEGVDEC_TI_IJPEGVDEC;

/**
* Referene to external symbol JPEGVDEC_TI_IRES,holding the pointers to
* the all the jpeg decoder IRES interface functions
*/
extern IRES_Fxns JPEGVDEC_TI_IRES;

/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/* ------------------------ data declarations ------------------------------- */


/* ----------------------- function prototypes ------------------------------ */

/* ------------------------------ macros ------------------------------------ */

#endif /* #ifndef _IJPEGVDEC_TI_ */



