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
* @file      Jpegenc_ti.h
*
* @brief     TI Interface related header file
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
* @version 0.1 (Feb 2010) : Review & clean up
*
* @version 0.2 (Sep 2010) : Review & clean up
********************************************************************************
*/
/* -------------------- compilation control switches -------------------------*/
#ifndef JPEGENC_TI_
#define JPEGENC_TI_

/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>
/*--------------------- program files ----------------------------------------*/


/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/**
* Referene to external symbol JPEGVENC_TI_IALG, holding the pointers to the
* all the basic algorithm creation related functions.
*/
/*----------------------------------------------------------------*/
extern IALG_Fxns JPEGVENC_TI_IALG;

/**
* Referene to external symbol JPEGVENC_TI_IJPEGVENC,holding the pointers to
* the all the mpeg2 decoder algorithm interfaces
*/
extern IVIDENC2_Fxns JPEGVENC_TI_IJPEGVENC;

/**
* Referene to external symbol JPEGVENC_TI_IRES, holding the pointers to the
* all the basic RMAN-IRES reource related functions.
*/
extern IRES_Fxns JPEGVENC_TI_IRES;

/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

#endif /*#ifndef JPEGENC_TI_*/
