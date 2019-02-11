/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#ifndef H264VDEC_
#define H264VDEC_

#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec3.h>

#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>

#include <ih264vdec.h>

extern IRES_Fxns H264VDEC_TI_IRES;

/*
 *  ======== H264VDEC_Handle ========
 *  This pointer is used to reference all H264VDEC instance objects
 */
typedef struct IH264VDEC_Obj *H264VDEC_Handle;

/*
 *  ======== H264VDEC_Params ========
 *  This structure defines the creation parameters for all H264VDEC objects
 */
typedef IH264VDEC_Params H264VDEC_Params;

/*
 *  ======== H264VDEC_PARAMS ========
 *  This structure defines the default creation parameters for H264VDEC objects
 */
#define H264VDEC_PARAMS   IH264VDEC_PARAMS

/*
 *  ======== H264VDEC_DynamicParams ========
 *  This structure defines the Dynamic parameters for all MP4VE objects
 */

typedef IH264VDEC_DynamicParams H264VDEC_DynamicParams;

/*
 *  ======== H264VDEC_DYNAMICPARAMS ========
 *  This structure defines the default dynamic parameters for H264VDEC objects
 */
#define H264VDEC_DYNAMICPARAMS   IH264VDEC_TI_DYNAMICPARAMS


/*
 *
 * This structure defines the status parameters for H264VDEC objects
*/
typedef IH264VDEC_Status H264VDEC_Status;

/*
 *  ======== IH264VDEC_InArgs ========
 *  This structure defines the runtime input arguments for IH264VDEC::process
 */

typedef IH264VDEC_InArgs H264VDEC_InArgs;

/*
 *  ======== IH264VDEC_OutArgs ========
 *  This structure defines the run time output arguments for IH264VDEC::process
 *  function.
 */

typedef IH264VDEC_OutArgs H264VDEC_OutArgs;

typedef IH264VDEC_Cmd H264VDEC_Cmd;
typedef IH264VDEC_Fxns H264VDEC_Fxns;

/*
 *  ======== Control commands ========
 *  control method commands
*/
#define H264VDEC_GETSTATUS    IH264VDEC_GETSTATUS
#define H264VDEC_SETPARAMS    IH264VDEC_SETPARAMS
#define H264VDEC_PREPROCESS   IH264VDEC_PREPROCESS
#define H264VDEC_RESET        IH264VDEC_RESET
#define H264VDEC_FLUSH        IH264VDEC_FLUSH
#define H264VDEC_SETDEFAULT   IH264VDEC_SETDEFAULT
#define H264VDEC_GETBUFINFO   IH264VDEC_GETBUFINFO

/*
 *  ======== H264VDEC_create ========
 *  Create an MPEG4VENC instance object (using parameters specified by prms)
 */
extern H264VDEC_Handle H264VDEC_create(const H264VDEC_Fxns * fxns,
                                     const H264VDEC_Params * prms);

/*
 *  ======== H264VDEC_delete ========
 *  Delete the MPEG4VENC instance object specified by handle
 */
extern XDAS_Void H264VDEC_delete(H264VDEC_Handle handle);

/*
 *  ======== H264VDEC_init ========
 */
extern XDAS_Void H264VDEC_init(void);

/*
 *  ======== H264VDEC_exit ========
 */
extern XDAS_Void H264VDEC_exit(void);

/*
 *  ======== H264VDEC_decodeFrame ========
 */
extern XDAS_Int32 H264VDEC_decodeFrame(
                                      IH264VDEC_ProcessParamsList* processList);

/*
 *  ======== H264VDEC_control ========
 * Get, set, and change the parameters of the MP4VE function (using parameters 
 *                                                         specified by status).
 */
extern XDAS_Int32 H264VDEC_control(H264VDEC_Handle handle, H264VDEC_Cmd cmd,
                                  H264VDEC_DynamicParams * params,
                                  H264VDEC_Status * status);


#endif   /* H264VDEC_ */
