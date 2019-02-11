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
* @file      jpegenc_ti_api.h
*
* @brief     JPEG user level calling functions
*            JPEG encoder specific functions
*
* @author    Pavan Kumar
*
* @version 0.0 (Dec 2009) : Created the initial version.
*
*******************************************************************************
*/

/* -------------------- compilation control switches -------------------------*/
#ifndef JPEGENC_TI_JPEGENC_H_
#define JPEGENC_TI_JPEGENC_H

/*-----------------------------------------------*/
/* control method commands                       */
/*-----------------------------------------------*/
#define JPEGVENC_GETSTATUS    IJPEGVENC_GETSTATUS
#define JPEGVENC_SETPARAMS    IJPEGVENC_SETPARAMS
#define JPEGVENC_PREPROCESS   IJPEGVENC_PREPROCESS
#define JPEGVENC_RESET        IJPEGVENC_RESET
#define JPEGVENC_FLUSH        IJPEGVENC_FLUSH
#define JPEGVENC_SETDEFAULT   IJPEGVENC_SETDEFAULT
#define JPEGVENC_GETBUFINFO   IJPEGVENC_GETBUFINFO


/*******************************************************************************
*                             INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividenc2.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>

/*--------------------- program files ----------------------------------------*/
#include <iJpegenc.h>

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/
extern IRES_Fxns JPEGVENC_TI_IRES;

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_Handle ========                                         */
/*  This pointer is used to reference all JPEGVENC instance objects           */
/*----------------------------------------------------------------------------*/
typedef struct IJPEGVENC_Obj *JPEGVENC_Handle;

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_Params ========                                         */
/*  This structure defines the creation parameters for all JPEGVENC objects   */
/*----------------------------------------------------------------------------*/
typedef IJPEGVENC_Params JPEGVENC_Params;

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_Params ========                                         */
/*  This structure defines the creation parameters for all JPEGVENC objects   */
/*----------------------------------------------------------------------------*/
#define JPEGVENC_PARAMS   IJPEGVENC_PARAMS
/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_DynamicParams ========                                  */
/*  This structure defines the dynamic parameters for all JPEGVENC objects    */
/*----------------------------------------------------------------------------*/
typedef IJPEGVENC_DynamicParams JPEGVENC_DynamicParams;

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_DynamicParams ========                                  */
/*  This structure defines the dynamic parameters for all JPEGVENC objects    */
/*----------------------------------------------------------------------------*/
#define JPEGVENC_DYNAMICPARAMS   IJPEGVENC_DYNAMICPARAMS

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_Status ========                                         */
/*  This structure defines the status parameters for all JPEGVENC objects     */
/*----------------------------------------------------------------------------*/
typedef IJPEGVENC_Status JPEGVENC_Status;

/*----------------------------------------------------------------------------*/
/*  ======== IJPEGVENC_InArgs ========                                        */
/*  This structure defines the runtime input arguments for IJPEGVENC::process */
/*----------------------------------------------------------------------------*/
typedef IJPEGVENC_InArgs JPEGVENC_InArgs;

/*----------------------------------------------------------------------------*/
/*  ======== IJPEGVENC_OutArgs ========                                       */
/*  This structure defines the runtime output arguments for IJPEGVENC::process*/
/*----------------------------------------------------------------------------*/
typedef IJPEGVENC_OutArgs JPEGVENC_OutArgs;

typedef IJPEGVENC_Cmd JPEGVENC_Cmd;
typedef IJPEGVENC_Fxns JPEGVENC_Fxns;


/*******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

/*---------------------- function prototypes ---------------------------------*/

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_create ========                                         */
/*   Create an JPEGVENC instance object (using parameters specified by prms)  */
/*----------------------------------------------------------------------------*/
extern JPEGVENC_Handle JPEGVENC_create(const JPEGVENC_Fxns *fxns, const
JPEGVENC_Params *prms);

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_delete ========                                         */
/*   Delete the JPEGVENC instance object specified by handle                  */
/*----------------------------------------------------------------------------*/

extern Void JPEGVENC_delete(JPEGVENC_Handle handle);

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_init ========                                           */
/*----------------------------------------------------------------------------*/
extern Void JPEGVENC_init(void);

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_exit ========                                           */
/*----------------------------------------------------------------------------*/
extern Void JPEGVENC_exit(void);

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_encodeFrame ========                                    */
/*----------------------------------------------------------------------------*/
extern XDAS_Int32 JPEGVENC_encodeFrame(JPEGVENC_Handle handle, IVIDEO2_BufDesc
*InBufs, XDM2_BufDesc *OutBufs,JPEGVENC_InArgs *Inargs,
JPEGVENC_OutArgs *Outargs);

/*----------------------------------------------------------------------------*/
/*  ======== JPEGVENC_control ========                                        */
/*   Get, set, and change the parameters of the JPEGVENC function             */
/*  (using parameters specified by status).                                   */
/*----------------------------------------------------------------------------*/

extern XDAS_Int32 JPEGVENC_control(JPEGVENC_Handle handle,
JPEGVENC_Cmd cmd,JPEGVENC_DynamicParams *params,JPEGVENC_Status *status);

#endif /* #ifndef JPEGENC_TI_JPEGENC_H_*/
