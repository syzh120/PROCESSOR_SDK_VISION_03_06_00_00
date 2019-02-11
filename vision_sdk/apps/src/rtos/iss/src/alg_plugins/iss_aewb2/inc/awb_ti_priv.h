/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
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
