/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2007 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

#ifndef H264ENC_
#define H264ENC_

/* #include <std.h>                                                           */
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividenc1.h>
#include <ti/xdais/dm/ividenc2.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <ih264enc.h>


/*
 *  ======== H264ENC_Handle ========
 *  This pointer is used to reference all H264ENC instance objects
 */
typedef struct IH264ENC_Obj *H264ENC_Handle;
extern IRES_Fxns H264ENC_TI_IRES;
/*
 *  ======== H264ENC_Params ========
 *  This structure defines the creation parameters for all H264ENC objects
 */
typedef IH264ENC_Params H264ENC_Params;

/*
 *  ======== H264ENC_PARAMS ========
 *  This structure defines the default creation parameters for H264ENC objects
 */
#define H264ENC_PARAMS   IH264ENC_PARAMS


/*  ========================================================================= */
/*  MP4VE_DynamicParams                                                       */
/*                                                                            */
/*  This structure defines the Dynamic parameters for all MP4VE objects       */

typedef IH264ENC_DynamicParams H264ENC_DynamicParams;

/*
 *  ======== H264ENC_DYNAMICPARAMS ========
 *  This structure defines the default creation parameters for H264ENC objects
 */
#define H264ENC_DYNAMICPARAMS   IH264ENC_DYNAMICPARAMS



/*  ========================================================================= */
/*  MP4VE_Status                                                              */
/*                                                                            */
/*  This structure defines the real-time parameters for MP4VE objects         */

typedef IH264ENC_Status H264ENC_Status;

/*
 *  ======== IH264ENC_InArgs ========
 *  This structure defines the runtime input arguments for IH264ENC::process
 */

typedef IH264ENC_InArgs H264ENC_InArgs;

/*
 *  ======== IH264ENC_OutArgs ========
 *  This structure defines the run time output arguments for IH264ENC::process
 *  function.
 */

typedef IH264ENC_OutArgs H264ENC_OutArgs;

typedef IH264ENC_Cmd H264ENC_Cmd;
typedef IH264ENC_Fxns H264ENC_Fxns;


/*  ========================================================================= */
/*  control method commands                                                   */

#define H264ENC_GETSTATUS    IH264ENC_GETSTATUS
#define H264ENC_SETPARAMS    IH264ENC_SETPARAMS
#define H264ENC_PREPROCESS   IH264ENC_PREPROCESS
#define H264ENC_RESET        IH264ENC_RESET
#define H264ENC_FLUSH        IH264ENC_FLUSH
#define H264ENC_SETDEFAULT   IH264ENC_SETDEFAULT
#define H264ENC_GETBUFINFO   IH264ENC_GETBUFINFO

/*
 *  ======== H264ENC_create ========
 *  Create an H264ENC instance object (using parameters specified by prms)
 */
extern H264ENC_Handle H264ENC_create(const H264ENC_Fxns * fxns,
                                     const H264ENC_Params * prms);

/*
 *  ======== H264ENC_delete ========
 *  Delete the H264ENC instance object specified by handle
 */
extern Void H264ENC_delete(H264ENC_Handle handle);

/*
 *  ======== H264ENC_init ========
 */
extern Void H264ENC_init(void);

/*
 *  ======== H264ENC_exit ========
 */
extern Void H264ENC_exit(void);

/*
 *  ======== H264ENC_enodeFrame ========
 */
extern XDAS_Int32 H264ENC_encodeFrame(H264ENC_Handle handle,
                                      IVIDEO2_BufDesc * InBufs,
                                      XDM2_BufDesc * OutBufs,
                                      H264ENC_InArgs * Inargs,
                                      H264ENC_OutArgs * Outargs);

extern XDAS_Int32 H264ENC_encodeFrameMulti(
                                       IH264ENC_ProcessParamsList *processList);
/*
 *  ======== H264ENC_control ========
 * Get, set, and change the parameters of the H264ENC function (using parameters 
 * specified by status).
 */
extern XDAS_Int32 H264ENC_control(H264ENC_Handle handle, H264ENC_Cmd cmd,
                                  H264ENC_DynamicParams * params,
                                  H264ENC_Status * status);


#endif   /* H264ENC_ */
