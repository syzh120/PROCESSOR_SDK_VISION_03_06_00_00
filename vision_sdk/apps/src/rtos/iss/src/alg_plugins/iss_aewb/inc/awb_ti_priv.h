/** ==================================================================
 *  @file   awb_ti_priv.h                                                  
 *                                                                    
 *  @path    /proj/vsi/users/venu/DM812x/IPNetCam_rel_1_8/ti_tools/iss_02_bkup/packages/ti/psp/iss/alg/aewb/ti2a/awb/inc/                                                 
 *                                                                    
 *  @desc   This  File contains.                                      
 * ===================================================================
 *  Copyright (c) Texas Instruments Inc 2011, 2012                    
 *                                                                    
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===================================================================*/
/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*
 *  ======== awb_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for AWB
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the AWB algorithm.
 */
#ifndef AWB_TI_PRIV_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#define AWB_TI_PRIV_

#include "TI_aaa_awb.h"
#include "AWB_config_hardware.txt"
#define MAX_NUM_PAXELS  (128*128)


extern Int AWB_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int AWB_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int AWB_TI_init(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 AWB_TI_process(IAWB_Handle h, IAWB_InArgs *inArgs,
    IAWB_OutArgs *outArgs, IAEWB_Rgb *rgbData, void *customData);

extern XDAS_Int32 AWB_TI_control(IAWB_Handle handle,
    IAWB_Cmd id, IAWB_DynamicParams *params, IAWB_Status *status);

extern int AWB_process(IAEWB_StatMat *statMat, IAEWB_Rgb *rgbData, IAEWB_Wb *wb, int numGainQueue,
    short* r_gain_queue, short *g_gain_queue, short *b_gain_queue, int *wb_gain_queue_index);

#define AWB_AVG_BUF_LENGTH	 6  //maximal length, acctually used 6
#define NUM_BLK_1	(NUM_OF_REF_1 * NUM_OF_GRAY)
#define NUM_BLK_2	(NUM_OF_REF_2 * NUM_OF_GRAY)
#define NUM_BLK_3	(1120)


#define AWB_SCRATCH_MEM_SIZE (4 + 26 * NUM_OF_REF_1 + 16 * NUM_BLK_1 + 13 * NUM_OF_REF_2 + 16 * NUM_BLK_2 + 6 * NUM_BLK_3)


typedef struct {
    awbprm_t prm;
    awb_data_out_t data_out;
    h3a_aewb_paxel_data_t h3a_data[MAX_NUM_PAXELS];
}AWB_TI_Obj;

typedef struct {
   // Algorithm Specific Global arrays
    uint8	histogram[NUM_OF_REF_1];
    uint8	history_index[AWB_AVG_BUF_LENGTH];
    uint32	v_img_ref[NUM_OF_REF_2];

} AWB_TI_InternalDataObj;

static const awb_data_t awb_data;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
