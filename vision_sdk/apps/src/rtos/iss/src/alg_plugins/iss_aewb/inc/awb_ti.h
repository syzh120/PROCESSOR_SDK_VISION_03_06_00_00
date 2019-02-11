/** ==================================================================
 *  @file   awb_ti.h                                                  
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
 *  ======== awb_ti.h ========
 */
#ifndef AWB_TI_
#define AWB_TI_

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== AWB_TI_VIDENCCOPY ========
 *  Our implementation of the IAWB interface
 */
extern IAWB_Fxns AWB_TI_AWB;

#define TIAWB_CMD_CALIBRATION     0x3

#ifdef __cplusplus
}
#endif

#endif

