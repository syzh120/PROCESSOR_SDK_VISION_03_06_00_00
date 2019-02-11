/*
 ===========================================================================
 * HDVICP2 Based H.264 HP Encoder
 *
 * "HDVICP2 Based H.264 HP Encoder" is software module developed on TI's
 * HDVICP2 based SOCs. This module is capable of compressing a 4:2:0 Raw
 * video into a high/main/baseline profile bit-stream.
 *
 * Copyright (C) {2009} Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 ===========================================================================
*/


/**
 *****************************************************************************
 * @file h264enc_ti_config.c
 *
 * @brief This File contains function definitions for a standard
 *        implementation of a test configuration file parser.
 *        These functiosn parses the input  configuration files and
 *        assigns user provided values to global instance structures
 *
 *
 * @author: Rama Mohana Reddy (rama.mr@ti.com)
 *
 * @version 0.0 (Jan 2008) : Base version created
 *                           [Pramod]
 * @version 0.1 (Oct 2009) : Review and more commenting along with cleanup
 *                           [Rama Mohan]
 * @version 0.2 (17-2-2010) : Made changes to add input data sync feature
 *                            Rama Mohana Reddy (rama.mr@ti.com)
 * @version 0.3 (Mar 2010) : Added different patterns of corruption in scratch
 *                           contamination [Rama Mohana Reddy]
 * @version 0.4 (April 2010) : Support of tiler buffer control [Pramod]
 * @version 0.5 (May 2010) : Fixed issue in scratch contamination
 *                           function [Nirmal]
 * @version 0.6 (May 2010) : Support of IVAHD sub system selection[Nirmal]
 * @version 0.7 (July 2010) : Changes related to MV & SAD exposure
 *                             support[Nirmal]
 * @version 0.8 (Apr 2010) : Added support for start frame and continuas value
 *                           of initial buffer level  [Uday]
 * @version 0.9 (May 2010) : Modified the name of varibale used for
 *                           ebnabling GMV in SEI   [Uday]
 * @version 1.0 (June2010):  Did changes related to numUnitsInTicks support
 *                           [Pramod]
 * @version 1.1 (Aug 2010):  Added static MB count support[Nirmal]
 * @version 1.2 (Aug2010):  Support for RCDO profile [Girish Murthy]
 * @version 1.3 (Sept 2010): Support for PRC and partial frame skip
 *                           control [Girish]
 * @version 1.4 (Sept 2010) : Added support of testing dynamic parameter change
 *                           at runtime [Nirmal]
 * @version 1.5 (Sept 2010) : Added support of HRDBufferSize, minBlockSizeP,
 *                           minBlockSizeB to be dynamic [Nirmal]
 * @version 1.6 (Sep 2010) :  Added support for long term reference frame
 * @version 1.7 (Sep 2010) : Support of setting value to numBlocks for
 *                           DataSyncGetData from user
 * @version 1.8 (July 2010): StereoVidoeInfo Params added in token mapping
                             & TestApp_SetInitParams()[Gajanan]
* @version 1.9 (July 2011): ROI input Params added in token mapping (Gajanan A)
* @version 2.0 (July 2011): discardSavedBits added in token mapping
                             & TestApp_SetInitParams()[Ramprasad]
 * @version 2.1 (Dec 2011):  Overriding of the maxQP for TRC is not required
 *                           with the new RC model. [Girish]
 * @version 2.2 (Dec 2011) : Added support for HRD compliance control
 * @version 2.3 (Dec  2011): Added frameSkipThMulQ5 & vbvUseLevelThQ5 in
 *                           token mapping [Karthick]
 * @version 2.4 (Mar  2012): Updated scratch contamination to cover HiMP
 *                           case. [Santosh]
 * @version 2.5 (Apr 2012) : code clean up [Santoshkumar S K]
 * @version 2.6 (Aug 2012) : Changed dafault values of scalingMatrixPreset  
 *                           and maxPicSizeRatioI(SDOCM00094509)
 * @version 2.7 (Aug 2012) : Redundant exposure of GDR configuration 
 *                           parameters as a part of Extended Dynamic structure
 *                           are removed(SDOCM00095027). Hence the code related
 *                           the initializations of these parameter is also 
 *                           removed [Santoshkumar S K].
 * @version 2.8 (Aug  2012): Updated scratch contamination memory addresses
 *                           for 02.00.03.00 release. [Santosh]
 * @version 2.9 (Sep 2012) : Updated scratch contamination memory addresses
 *                           for 02.00.04.00 release. [Gajanan]
 * @version 3.0 (Mar 2013) :Code modifications to fix SDOCM00099577(Encoder 
 *                          does not give refined error codes in case of 
 *                          creation fail or run time parameter set fail) 
 *                          [Santosh]
 * @version 3.1 (Mar 2015) :Added, static sections table for HiMP 
                            high Speed mode [Nandu]
 *****************************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <h264enc_ti_config.h>
#include <h264enc_ti_test.h>
#include <H264BPEnc_rman_config.h>

#ifdef SCRATCH_CONTAMINATE
#include <..\..\..\algsrc\inc\h264enc_ti_object_size_HiMP.h>
#include <..\..\..\algsrc\inc\h264enc_ti_object_size.h>
#include <..\..\..\algsrc\inc\dataFormatH264E.h>
#endif
/*----------------------------------------------------------------------------*/
/* Global instance parameters                                                 */
/*----------------------------------------------------------------------------*/
h264BPEncConfig            gConfigOrg;
H264ENC_Params             gParamsOrg;
H264ENC_DynamicParams      gDynamicParamsOrg;
IVIDEO2_BufDesc            gInputBufDescOrg;
IH264ENC_InArgs            gInArgsOrg;


/*----------------------------------------------------------------------------*/
/* Global instance log generation                                             */
/*----------------------------------------------------------------------------*/
sLogGenerate gLogMessge;

/*----------------------------------------------------------------------------*/
/*  Global Structure variables for profile info                               */
/*----------------------------------------------------------------------------*/

sProfileTimeStamps profileTimeStamps;
sProfileData profileData;

extern XDM_DataSyncHandle fGetInpDHandle1;
extern XDM_DataSyncHandle fGetInpDHandle2;
extern XDM_DataSyncDesc   ip_datasyncDesc1;
extern XDM_DataSyncDesc   ip_datasyncDesc2;
extern XDAS_Int32  numFramesEncoded[MAX_ITEMS_TO_RUN];
extern XDAS_Int32 stopPos;
extern XDAS_UInt32 ivaCodeLoadDone;
extern XDAS_Int32 prevProcessCallNumChannel;
extern XDAS_Int32 currProcessCallNumChannel;

XDAS_UInt32 waitCount;
XDAS_UInt32 doneCount;
/*----------------------------------------------------------------------------*/
/* Error strings which are mapped to codec errors                             */
/* Please refer User guide for more details on error strings                  */
/*----------------------------------------------------------------------------*/
static sErrorMapping gErrorStrings[32] =
{
  (XDAS_Int8 *)"IH264ENC_LEVEL_INCOMPLAINT_PARAMETER , 0, \0",
  (XDAS_Int8 *)"IH264ENC_PROFILE_INCOMPLAINT_CONTENTTYPE = 1,\0",
  (XDAS_Int8 *)"IH264ENC_PROFILE_INCOMPLAINT_FMO_SETTING = 2,",
  (XDAS_Int8 *)"IH264ENC_PROFILE_INCOMPLAINT_TRANSFORMBLOCKSIZE = 3,\0",
  (XDAS_Int8 *)"IH264ENC_PROFILE_INCOMPLAINT_INTERFRAMEINTERVAL = 4,\0",
  (XDAS_Int8 *)"IH264ENC_PROFILE_INCOMPLAINT_SCALINGMATRIXPRESET = 5,\0",
  (XDAS_Int8 *)"IH264ENC_PROFILE_INCOMPLAINT_ENTROPYCODINGMODE = 6,\0",
  (XDAS_Int8 *)"IH264ENC_MAX_BIT_RATE_VOILATION  = 7,\0",
  (XDAS_Int8 *)"XDM_PARAMSCHANGE = 8,\0",
  (XDAS_Int8 *)"XDM_APPLIEDCONCEALMENT = 9,\0",
  (XDAS_Int8 *)"XDM_INSUFFICIENTDATA = 10,\0",
  (XDAS_Int8 *)"XDM_CORRUPTEDDATA = 11,\0",
  (XDAS_Int8 *)"XDM_CORRUPTEDHEADER = 12,\0",
  (XDAS_Int8 *)"XDM_UNSUPPORTEDINPUT = 13,\0",
  (XDAS_Int8 *)"XDM_UNSUPPORTEDPARAM = 14,\0",
  (XDAS_Int8 *)"XDM_FATALERROR = 15\0",
  (XDAS_Int8 *)"IH264ENC_IMPROPER_HDVICP2_STATE = 16\0",
  (XDAS_Int8 *)"IH264ENC_IMPROPER_STREAMFORMAT = 17,\0",
  (XDAS_Int8 *)"IH264ENC_IMPROPER_POCTYPE = 18,\0",
  (XDAS_Int8 *)"IH264ENC_IMPROPER_DATASYNC_SETTING = 19,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_VIDENC2PARAMS = 20,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_RATECONTROLPARAMS = 21,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_INTERCODINGPARAMS = 22,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_INTRACODINGPARAMS = 23,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_NALUNITCONTROLPARAMS = 24,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_SLICECODINGPARAMS = 25,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_LOOPFILTERPARAMS = 26,\0",
  (XDAS_Int8 *)
   "IH264ENC_UNSUPPORTED_FMOCODINGPARAMS_or_N_FRAME_PROCESSCALL_PARAMS = 27,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_VUICODINGPARAMS = 28,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_H264ENCPARAMS = 29,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_VIDENC2DYNAMICPARAMS = 30,\0",
  (XDAS_Int8 *)"IH264ENC_UNSUPPORTED_H264ENCDYNAMICPARAMS = 31, \0"
};

/*----------------------------------------------------------------------------*/
/* Error strings which are mapped to codec sub extended errors                */
/* Please refer interface header files for more details on error strings      */
/*----------------------------------------------------------------------------*/
static sErrorMapping gExtErrorStrings[IH264ENC_EXTERROR_NUM_MAXBITS] =
{
  (XDAS_Int8 *)"IH264ENC_EXTERROR_ACTIVEREGION                             \
                                                                    = 0   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_ANALYTICINFO_BUFFERSIZE                  \
                                                                    = 1   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_BITRATE                                  \
                                                                    = 2   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_BITSTREAM_BUFFERSIZE                     \
                                                                    = 3   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CAPTUREWIDTH_FORCEFRAME_LTRP_QPEL        \
                                                                    = 4   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CONTROLCALL_CMD                          \
                                                                    = 5   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_ENTROPY_PROFILE                   \
                                                                    = 6   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_GOPSTRUCT_LOG2MAX_INTRAINTERVAL   \
                                                                    = 7   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_HPLAYERS                          \
                                                                    = 8   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_HPLAYERS_BFRAME                   \
                                                                    = 9   \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_HPLAYERS_POC                      \
                                                                    = 10  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_HPLAYERS_REFPICMRKING             \
                                                                    = 11  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_INTERLACE_TYPE                    \
                                                                    = 12  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_LTRP                              \
                                                                    = 13  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_LTRP_HP                           \
                                                                    = 14  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_LTRP_PERIOD                       \
                                                                    = 15  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_LVL_DPBSIZE                       \
                                                                    = 16  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_POC_BFRAME                        \
                                                                    = 17  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_RCDO_PROFILE                      \
                                                                    = 18  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_TXBLKSIZE_ENTROPY_POC_LTRP        \
                                                                    = 19  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_CREATE_TXBLKSIZE_PROFILE                 \
                                                                    = 20  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_GETFN_PTRNULL                   \
                                                                    = 21  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_MBUNIT_SLICESIZE                \
                                                                    = 22  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_MODE_BFRAME                     \
                                                                    = 23  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_MODE_FNPTRNULL                  \
                                                                    = 24  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_MODE_H241_FNPTRNULL             \
                                                                    = 25  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_MODE_MINBITRATE                 \
                                                                    = 26  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_OUTPUTDATAEXCEED                \
                                                                    = 27  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DATASYNC_UNITS                           \
                                                                    = 28  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DYNAMIC_SRCHCENTRE                       \
                                                                    = 29  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_DYNAMICPARAMS_PTRNULL                    \
                                                                    = 30  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_EARLYEXIT                                \
                                                                    = 31  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_FIFO_EMPTY_NOPROCESS                     \
                                                                    = 32  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_FILLERBYTES_NEGATIVE                     \
                                                                    = 33  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_FMO_PRESET                               \
                                                                    = 34  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_FRMPACKING_PRESET                        \
                                                                    = 35  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_FRMPACKING_TYPE_INPCONTENT               \
                                                                    = 36  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_FRMRATE_NUMUNITSINTICKS                  \
                                                                    = 37  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_GENHEADER_BITSTREAM_BUFFERSIZE           \
                                                                    = 38  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_HANDLE_BUFDESCRIPTORS_PTRNULL            \
                                                                    = 39  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_HIGHSPEED_BFARME                         \
                                                                    = 40  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_HIGHSPEED_MEALGO_TXBLKSIZE_PROFILE       \
                                                                    = 41  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_HIGHSPEED_PARTIALSKIP_INTRAREFRESHMETHOD \
                                                                    = 42  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_HIGHSPEED_TXBLKSIZE_PROFILE              \
                                                                    = 43  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INARGS_BASECLASS_WATERMARKENABLE         \
                                                                    = 44  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INARGS_CONTROL                           \
                                                                    = 45  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INARGS_OUTARGS_SIZE                      \
                                                                    = 46  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INARGS_PTRNULL                           \
                                                                    = 47  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INPCONTENT_TYPE                          \
                                                                    = 48  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INPUT_BUFFERID                           \
                                                                    = 49  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INPUTBUF_MEMTYPE                         \
                                                                    = 50  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INPUTBUF_PTR_SIZE_NULL                   \
                                                                    = 51  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTER_HIGHSPEED_MVPERMB                  \
                                                                    = 52  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTER_HIGHSPEED_QPEL_FRAMEINTERVAL       \
                                                                    = 53  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTER_MVPERMB                            \
                                                                    = 54  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTER_PRESET                             \
                                                                    = 55  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTER_SRCHRGN_SKIPMVBIAS                 \
                                                                    = 56  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTERLACE_DATALAYOUT                     \
                                                                    = 57  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_CBCR8X8                            \
                                                                    = 58  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_GDR_BFRAME_INPCONTENT_RATE         \
                                                                    = 59  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_GDR_REFRESHRATE                    \
                                                                    = 60  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_INTER_FRMINTERVAL                  \
                                                                    = 61  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_LEVEL_MODE                         \
                                                                    = 62  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_PRESET                             \
                                                                    = 63  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_REFRESHMETHOD                      \
                                                                    = 64  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_REFRESHMETHOD_RATE                 \
                                                                    = 65  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_INTRA_REFRESHRATE                        \
                                                                    = 66  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_IVAHD_BADRESET                           \
                                                                    = 67  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_IVAHD_BADSTATE                           \
                                                                    = 68  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_IVAHD_RELEASE                            \
                                                                    = 69  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_LEVEL_INPCONTENT                         \
                                                                    = 70  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_LEVELLIMIT_RESOLUTION                    \
                                                                    = 71  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_LOOPFILTER_OFFST_LFIDC                   \
                                                                    = 72  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_LOOPFILTER_PRESET                        \
                                                                    = 73  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_LUMA_INPUTBUF_MEMTYPE                    \
                                                                    = 74  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_METADATA_NUMBUFFERS                      \
                                                                    = 75  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_METADATABUF_MEMTYPE                      \
                                                                    = 76  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_METADATAPLANE_WGTTABLESIZE               \
                                                                    = 77  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_METADATATYPES                            \
                                                                    = 78  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_MULITCHNL_BFRAME_NOTSUPPORTED            \
                                                                    = 79  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_MULITCHNL_CHNLNUMEXCEEDED                \
                                                                    = 80  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_MULITCHNL_DATASYNC                       \
                                                                    = 81  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_MULITCHNL_FRMPCK_STEREOIINFO             \
                                                                    = 82  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_MULITCHNL_GENHEADER_NOTSUPPORTED         \
                                                                    = 83  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_MULITCHNL_MINBITRATE_NOTSUPPORTED        \
                                                                    = 84  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_MULITCHNL_MVPERMB                        \
                                                                    = 85  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_NALU_GOLDENSPS                           \
                                                                    = 86  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_NALU_PRESET                              \
                                                                    = 87  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_NALU_SPS_VUI                             \
                                                                    = 88  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_NOCLEANEXIT                              \
                                                                    = 89  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_NUM_INPUT_OUTPUT_BUFS                    \
                                                                    = 90  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_OUTPUTBUF_MEMTYPE                        \
                                                                    = 91  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_OUTPUTBUF_PTR_SIZE_NULL                  \
                                                                    = 92  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_OUTPUTDATASIZE_EXCEEDED                  \
                                                                    = 93  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_PRESET_ENC_RATECTRL_LVL                  \
                                                                    = 94  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_PROFILE_BFRAME                           \
                                                                    = 95  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_PROFILE_DATASYNC_INPCONTENT_RES          \
                                                                    = 96  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_PROFILE_INPCONTENT                       \
                                                                    = 97  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_BFRAMEPICSIZE                   \
                                                                    = 98  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_CBCRQPINDEX_INITBUFLVL          \
                                                                    = 99  \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_HRDBUFFER_LVLEXCEED             \
                                                                    = 100 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_IFRAME_QP                       \
                                                                    = 101 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_IFRAMEPICSIZE                   \
                                                                    = 102 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_IPBFRAME_QP                     \
                                                                    = 103 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SCLMATRIX_METADATA                       \
                                                                    = 104 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_PARAMSPRESET                    \
                                                                    = 105 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_PBFRAME_QP                      \
                                                                    = 106 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_PFRAMEPICSIZE                   \
                                                                    = 107 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_PRESET_BFRAME_INPCONTENT        \
                                                                    = 108 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_PROFILE_SCALINGMTRX             \
                                                                    = 109 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_RCALGO                          \
                                                                    = 110 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_RCALGO_INTERLACE_OR_BFRAME      \
                                                                    = 111 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_SKIPDISTWNDW                    \
                                                                    = 112 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RATECTRL_VBR                             \
                                                                    = 113 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_RESOLUTION_BITRATE_FRMINTERVAL_GENHEADER \
                                                                    = 114 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_ROI_COORDINATES                          \
                                                                    = 115 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_ROI_NUMBERROIS                           \
                                                                    = 116 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_ROI_PRIORITY                             \
                                                                    = 117 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_ROI_QP                                   \
                                                                    = 118 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_ROI_TYPE                                 \
                                                                    = 119 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SLICE_NONE_DATASYNC                      \
                                                                    = 120 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SLICE_H241_ENTROPY_INTERFRAME_INTERLACE  \
                                                                    = 121 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SLICE_STRMFORMAT_DATASYNC                \
                                                                    = 122 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SLICE_H241_WIDTH_SLICESIZE               \
                                                                    = 123 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SLICE_MODE_SIZE                          \
                                                                    = 124 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SLICE_PRESET                             \
                                                                    = 125 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_SLICE_STRMFORMAT                         \
                                                                    = 126 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_STATUS_PTRNULL                           \
                                                                    = 127 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_STATUS_SIZE                              \
                                                                    = 128 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_STEREO_INPCONTENT                        \
                                                                    = 129 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_STEREO_PRESET                            \
                                                                    = 130 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_VERSION_BUFFER_NULL_OR_SIZE              \
                                                                    = 131 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_VUI_NUMUNITSINTICKS                      \
                                                                    = 132 \0",
  (XDAS_Int8 *)"IH264ENC_EXTERROR_VUI_PRESET                               \
                                                                    = 133 \0",
  (XDAS_Int8 *)"IH264ENC_NUM_OUTPUT_BUFS_ANALYTICINFO                      \
                                                                    = 134 \0",
};

/*----------------------------------------------------------------------------*/
/*  Structure to hold */
/*----------------------------------------------------------------------------*/
static XDAS_Int8 *pFrameType[19] = {
    (XDAS_Int8 *)"IVIDEO_NA_FRAME",
    (XDAS_Int8 *)"IVIDEO_I_FRAME",
    (XDAS_Int8 *)"IVIDEO_P_FRAME",
    (XDAS_Int8 *)"IVIDEO_B_FRAME",
    (XDAS_Int8 *)"IVIDEO_IDR_FRAME",
    (XDAS_Int8 *)"IVIDEO_II_FRAME",
    (XDAS_Int8 *)"IVIDEO_IP_FRAME",
    (XDAS_Int8 *)"IVIDEO_IB_FRAME",
    (XDAS_Int8 *)"IVIDEO_PI_FRAME",
    (XDAS_Int8 *)"IVIDEO_PP_FRAME",
    (XDAS_Int8 *)"IVIDEO_PB_FRAME",
    (XDAS_Int8 *)"IVIDEO_BI_FRAME",
    (XDAS_Int8 *)"IVIDEO_BP_FRAME",
    (XDAS_Int8 *)"IVIDEO_BB_FRAME",
    (XDAS_Int8 *)"IVIDEO_MBAFF_I_FRAME",
    (XDAS_Int8 *)"IVIDEO_MBAFF_P_FRAME",
    (XDAS_Int8 *)"IVIDEO_MBAFF_B_FRAME",
    (XDAS_Int8 *)"IVIDEO_MBAFF_IDR_FRAME",
    (XDAS_Int8 *)"IVIDEO_FRAMETYPE_DEFAULT"
  };


/*----------------------------------------------------------------------------*/
/* Array of elements of type sTokenMapping for parsing and holding the tokens */
/* from the input configuration file.                                         */
/*----------------------------------------------------------------------------*/
static sTokenMapping sTokenMap[MAX_ITEMS_TO_PARSE] =
{
  /*--------------------------------------------------------------------------*/
  /* Input file name along with path and type of element is string            */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"InputFile",&gConfigOrg.inputFile,0},
  /*--------------------------------------------------------------------------*/
  /* Input file name along with path and type of element is string            */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"EncodedFile",&gConfigOrg.outputFile,0},
  /*--------------------------------------------------------------------------*/
  /* Reference file to bitmatch with encoded bit stream                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"ReferenceFile",&gConfigOrg.refFile,0},
  /* file name of Water Mark input key ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"waterMarkInputKeyFile",&gConfigOrg.waterMarkInputKeyFile,0},
  /*--------------------------------------------------------------------------*/
  /* Preset to control encoder quality by using XDM_EncodingPreset enum       */
  /* Expected vaules are                                                      */
  /* XDM_DEFAULT : Default setting of the algorithm specific creation         */
  /*               time parameters                                            */
  /* XDM_USER_DEFINED : User defined configuration using advanced parameters  */
  /* XDM_HIGH_SPEED_MED_QUALITY   : High speed and medium quality             */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"EncodingPreset",&gParamsOrg.videnc2Params.encodingPreset,
                               sizeof(gParamsOrg.videnc2Params.encodingPreset)},
  /*--------------------------------------------------------------------------*/
  /* This is used for setting the maximum number of B frames between two      */
  /* reference frames.                                                        */
  /* Distance from I-frame to P-frame: N were N specifies put N-1 number of B */
  /* frames in the encoded sequence                                           */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"MaxInterFrameInterval",
                &gParamsOrg.videnc2Params.maxInterFrameInterval,
                        sizeof(gParamsOrg.videnc2Params.maxInterFrameInterval)},

  /*--------------------------------------------------------------------------*/
  /* This is used for setting the maximum bit rate                            */
  /* if it is set as -1 then it means that encoder don't have any restriction */
  /* on deviation of avg bit rate                                             */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"maxBitRate",&gParamsOrg.videnc2Params.maxBitRate,
                          sizeof(gParamsOrg.videnc2Params.maxBitRate)},

  /*--------------------------------------------------------------------------*/
  /* This is used for setting the minimum bit rate                            */
  /* Encoder need to insert filler to achieve minimum bit rate                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"minBitRate",&gParamsOrg.videnc2Params.minBitRate,
                          sizeof(gParamsOrg.videnc2Params.minBitRate)},

  /*--------------------------------------------------------------------------*/
  /* Max height of the input frame supported, used at create time to init     */
  /* encoder instance.                                                        */
  /* Supported values are : 80 to 1088 in case of progressive                 */
  /*                        80 to 544 in case of interlaced                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"MaxHeight",&gParamsOrg.videnc2Params.maxHeight,
                                    sizeof(gParamsOrg.videnc2Params.maxHeight)},
  /*--------------------------------------------------------------------------*/
  /* Max Width of the input frame supported, used at create time to init      */
  /* encoder instance.                                                        */
  /* Supported values are : 96 to 1920                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"MaxWidth",&gParamsOrg.videnc2Params.maxWidth,
                                     sizeof(gParamsOrg.videnc2Params.maxWidth)},
  /*--------------------------------------------------------------------------*/
  /* Endianness of data supports only big endian format                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"DataEndianess", &gParamsOrg.videnc2Params.dataEndianness,
                               sizeof(gParamsOrg.videnc2Params.dataEndianness)},
  /*--------------------------------------------------------------------------*/
  /* Input data chroma format, supports only semi planar chroma format        */
  /* XDM_YUV_420SP                                                            */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"InputChromaFormat",&gParamsOrg.videnc2Params.inputChromaFormat,
                            sizeof(gParamsOrg.videnc2Params.inputChromaFormat)},
  /*--------------------------------------------------------------------------*/
  /* Input buffer content type : progresive(0) interlaced (1)                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"InputContentType",&gParamsOrg.videnc2Params.inputContentType,
                             sizeof(gParamsOrg.videnc2Params.inputContentType)},
  /*--------------------------------------------------------------------------*/
  /* Video buffer layout, field interleaved or field separated                */
  /* Only IVIDEO_FIELD_INTERLEAVED and IVIDEO_FIELD_SEPARATED are supported   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"dataLayout",&gInputBufDescOrg.dataLayout,
                                           sizeof(gInputBufDescOrg.dataLayout)},
  /*--------------------------------------------------------------------------*/
  /* Parameter to encode in 30 process call and 60 process call mode          */
  /*   0 - Encode in 30 process call mode                                     */
  /*   1 - Encode in 60 process call mode                                     */
  /*       When data layout is 0 this parameter is ignored                    */
  /*   Default - 0                                                            */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"numProcessCall",&gConfigOrg.numProcessCall,
                                             sizeof(gConfigOrg.numProcessCall)},

  /*--------------------------------------------------------------------------*/
  /* Codec oprating mode, as of now Encode Only mode is sepeated              */
  /* Please refer XDM IVIDEO_OperatingMode for more details                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"OperatingMode",&gParamsOrg.videnc2Params.operatingMode,
                                sizeof(gParamsOrg.videnc2Params.operatingMode)},
  /*--------------------------------------------------------------------------*/
  /* Encoding profile, Supports                                               */
  /*        High profile      - 100                                           */
  /*        Main Profile      - 77                                            */
  /*        Baseline Profile  - 66                                            */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"Profile",&gParamsOrg.videnc2Params.profile,
                                      sizeof(gParamsOrg.videnc2Params.profile)},
  /*--------------------------------------------------------------------------*/
  /* Encoding Level, Supports                                                 */
  /*  Upto Level 4.1 is supported i.e 41                                      */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"Level",&gParamsOrg.videnc2Params.level,
                                        sizeof(gParamsOrg.videnc2Params.level)},
  /*--------------------------------------------------------------------------*/
  /* Method of feeding input to the codec                                     */
  /*    Supports IVIDEO_FIXEDLENGTH, and IVIDEO_ENTIREFRAME modes             */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"InputDataMode",&gParamsOrg.videnc2Params.inputDataMode,
                                sizeof(gParamsOrg.videnc2Params.inputDataMode)},
  /*--------------------------------------------------------------------------*/
  /* Method of providing encoded bitstream to the appication                  */
  /* Supports IVIDEO_ENTIREFRAME,IVIDEO_NUMROWS only                          */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"OutputDataMode",&gParamsOrg.videnc2Params.outputDataMode,
                               sizeof(gParamsOrg.videnc2Params.outputDataMode)},
  /*--------------------------------------------------------------------------*/
  /* The type of rate controll algorithm picked up by the encoder             */
  /* Default algorithm(Perceptual Rate Control) is used when set to 0         */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"RateControlPreset",&gParamsOrg.videnc2Params.rateControlPreset,
                            sizeof(gParamsOrg.videnc2Params.rateControlPreset)},
  /*--------------------------------------------------------------------------*/
  /* Total number of frames to encode                                         */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"NumInputUnits",&gConfigOrg.numInputDataUnits,
                                          sizeof(gConfigOrg.numInputDataUnits)},
  /*--------------------------------------------------------------------------*/
  /* Size of the input data buffer in each chunk                              */
  /* This value to be provided in terms of no of rows in frame                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"NumInputBufferUnits",
                                    &gParamsOrg.videnc2Params.numInputDataUnits,
                            sizeof(gParamsOrg.videnc2Params.numInputDataUnits)},
  /*--------------------------------------------------------------------------*/
  /* Number of data units per frame                                           */
  /* Supports only 1 data unit per frame                                      */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"NumOutputUnits",&gParamsOrg.videnc2Params.numOutputDataUnits,
                           sizeof(gParamsOrg.videnc2Params.numOutputDataUnits)},
  /*--------------------------------------------------------------------------*/
  /* Width of input bit stream                                                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"inputWidth",&gDynamicParamsOrg.videnc2DynamicParams.inputWidth,
                     sizeof(gDynamicParamsOrg.videnc2DynamicParams.inputWidth)},
  /*--------------------------------------------------------------------------*/
  /* Height of the bit stream                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"inputHeight",
                           &gDynamicParamsOrg.videnc2DynamicParams.inputHeight,
                    sizeof(gDynamicParamsOrg.videnc2DynamicParams.inputHeight)},
  /*--------------------------------------------------------------------------*/
  /* Reference or input frame rate in fps * 1000.                             */
  /* For example, if the frame rate is 30, set this field to 30000.           */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"refFrameRate",
                           &gDynamicParamsOrg.videnc2DynamicParams.refFrameRate,
                   sizeof(gDynamicParamsOrg.videnc2DynamicParams.refFrameRate)},
  /*--------------------------------------------------------------------------*/
  /*Target frame rate in fps * 1000. For example, if the frame rate is 30,    */
  /*set this field to 30000.                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"targetFrameRate",
                        &gDynamicParamsOrg.videnc2DynamicParams.targetFrameRate,
                sizeof(gDynamicParamsOrg.videnc2DynamicParams.targetFrameRate)},
  /*--------------------------------------------------------------------------*/
  /* Target bit-rate in bits per second. For example,                         */
  /*if the bit-rate is 2 Mbps, set this field to 2000000.                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"targetBitRate",
                          &gDynamicParamsOrg.videnc2DynamicParams.targetBitRate,
                  sizeof(gDynamicParamsOrg.videnc2DynamicParams.targetBitRate)},
  /*--------------------------------------------------------------------------*/
  /*Interval between two consecutive intra frames. For example:               */
  /*  0 - Only first frame to be intra coded                                  */
  /*   1 - No inter frames (all intra frames)                                 */
  /*   N - One intra frame and N-1 inter frames, where N > 1.                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"intraFrameInterval",
                &gDynamicParamsOrg.videnc2DynamicParams.intraFrameInterval,
             sizeof(gDynamicParamsOrg.videnc2DynamicParams.intraFrameInterval)},
  /*--------------------------------------------------------------------------*/
  /* Number of B frames between two reference frames; that is,                */
  /* the number of B frames between two P frames or I/P frames. DEFAULT(0).   */
  /* For example, this field will be:                                         */
  /*  0 - To use maxInterFrameInterval.                                       */
  /*  1 - Zero B frames between two reference frames.                         */
  /*   2 - One B frame between two reference frames.                          */
  /*  3 - Two B frames between two reference frames. and so on...             */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"interFrameInterval",
                &gDynamicParamsOrg.videnc2DynamicParams.interFrameInterval,
             sizeof(gDynamicParamsOrg.videnc2DynamicParams.interFrameInterval)},
  /*--------------------------------------------------------------------------*/
  /* Encode entire access unit or only header.                                */
  /*    Please refer XDM_EncMode for further details                          */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"generateHeader",
                         &gDynamicParamsOrg.videnc2DynamicParams.generateHeader,
                 sizeof(gDynamicParamsOrg.videnc2DynamicParams.generateHeader)},
  /*--------------------------------------------------------------------------*/
  /* Image capture width                                                      */
  /* If the field is set to:                                                  */
  /*  0 - Encoded image width is used as pitch.                               */
  /*  Any non-zero value, capture width is used as pitch (if capture width    */
  /*  is greater than image width).                                           */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"captureWidth",
                           &gDynamicParamsOrg.videnc2DynamicParams.captureWidth,
                   sizeof(gDynamicParamsOrg.videnc2DynamicParams.captureWidth)},
  /*--------------------------------------------------------------------------*/
  /* Image capture height                                                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"captureHeight",
                    &gConfigOrg.captureHeight,sizeof(gConfigOrg.captureHeight)},
  /*--------------------------------------------------------------------------*/
  /* Exact source position of the pixel to encode in input buffer X direction */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"captureTopLeftx",
                &gConfigOrg.captureTopLeftx,sizeof(gConfigOrg.captureTopLeftx)},
  /*--------------------------------------------------------------------------*/
  /* Exact source position of the pixel to encode in input buffer Y direction */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"captureTopLefty",
                &gConfigOrg.captureTopLefty,sizeof(gConfigOrg.captureTopLefty)},
  /*--------------------------------------------------------------------------*/
  /* forceIDRPeriod specified by user to control encoding                     */
  /* This variable can be used to change the dynamic parameters at specified  */
  /* location , forcing IDR frame etc.                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"forceIDRPeriod",
                  &gConfigOrg.forceIDRPeriod,sizeof(gConfigOrg.forceIDRPeriod)},
  /*--------------------------------------------------------------------------*/
  /* Frame Number in the capture order that needs to be coded as forecs       */
  /* skip MB.                                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"LongTermRefPeriod",
            &gConfigOrg.LongTermRefPeriod,sizeof(gConfigOrg.LongTermRefPeriod)},

  /*--------------------------------------------------------------------------*/
  /* Frame Number in the capture order that needs to be considered as failre  */
  /* frame                                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"LTRPFailureLocation0",
     &gConfigOrg.LTRPFailureLocation0,sizeof(gConfigOrg.LTRPFailureLocation0)},
  /*--------------------------------------------------------------------------*/
  /* Frame Number in the capture order that needs to be considered as failre  */
  /* frame                                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"LTRPFailureLocation1",
      &gConfigOrg.LTRPFailureLocation1,sizeof(gConfigOrg.LTRPFailureLocation1)},

  /*--------------------------------------------------------------------------*/
  /* Frame Number in the capture order that needs to be refereing the long    */
  /* term reference frame                                                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"forceSKIPPeriod",
                &gConfigOrg.forceSKIPPeriod,sizeof(gConfigOrg.forceSKIPPeriod)},

  /*--------------------------------------------------------------------------*/
  /* Read the GDR Period when and all the coded needs to be commanded for GDR */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"gdrPeriod",
                            &gConfigOrg.gdrPeriod,sizeof(gConfigOrg.gdrPeriod)},  
                      
  /*--------------------------------------------------------------------------*/
  /* What should be the first frame number form when on codec needs to be     */
  /*  commanded.                                                              */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"gdrStartFrameNum",
              &gConfigOrg.gdrStartFrameNum,sizeof(gConfigOrg.gdrStartFrameNum)},  
                      
  /*--------------------------------------------------------------------------*/
  /* Force the current(immediate)frame to be encoded as a specific frame type.*/
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"forceFrame",&gDynamicParamsOrg.videnc2DynamicParams.forceFrame,
                     sizeof(gDynamicParamsOrg.videnc2DynamicParams.forceFrame)},
  /*--------------------------------------------------------------------------*/
  /* Motion vector accurary                                                   */
  /* Only Quarter pel (IVIDENC2_MOTIONVECTOR_QUARTERPEL)interpolation         */
  /* is supported                                                             */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"mvAccuracy",&gDynamicParamsOrg.videnc2DynamicParams.mvAccuracy,
                     sizeof(gDynamicParamsOrg.videnc2DynamicParams.mvAccuracy)},
  /*--------------------------------------------------------------------------*/
  /* sampleAspectRatioHeight to placed as VUI parameter while encoding        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sampleAspectRatioHeight",
           &gDynamicParamsOrg.videnc2DynamicParams.sampleAspectRatioHeight,
        sizeof(gDynamicParamsOrg.videnc2DynamicParams.sampleAspectRatioHeight)},
  /*--------------------------------------------------------------------------*/
  /* sampleAspectRatioWidth to placed as VUI parameter while encoding         */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sampleAspectRatioWidth",
            &gDynamicParamsOrg.videnc2DynamicParams.sampleAspectRatioWidth,
         sizeof(gDynamicParamsOrg.videnc2DynamicParams.sampleAspectRatioWidth)},
  /*--------------------------------------------------------------------------*/
  /* Flag to inform for checking output buffer availability inside codec      */
  /* When this flag is FALSE codec has to check for the size of output buffer */
  /* and report error in case of in sufficient buffer                         */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"ignoreOutbufSizeFlag",
              &gDynamicParamsOrg.videnc2DynamicParams.ignoreOutbufSizeFlag,
           sizeof(gDynamicParamsOrg.videnc2DynamicParams.ignoreOutbufSizeFlag)},
  /*--------------------------------------------------------------------------*/
  /* Enropy coding type, Supported values are                                 */
  /* CAVLC - 0, CABAC - 1 and default configuration is CABAC(1)               */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"entropyCodingMode",&gParamsOrg.entropyCodingMode,
                                          sizeof(gParamsOrg.entropyCodingMode)},
  /*--------------------------------------------------------------------------*/
  /* GOP structure either Opne or Closed                                      */
  /* Supported values are                                                     */
  /*        Open or Uniform(IBBPBBP)  - 0                                     */
  /*        Closed or Non Uniform (BBIBBPBB) - 1                              */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"gopStructure",
                      &gParamsOrg.gopStructure,sizeof(gParamsOrg.gopStructure)},
  /*--------------------------------------------------------------------------*/
  /*Interval b/w two IDR frames for example :                                 */
  /*    0 : Only first I frame as IDR                                         */
  /*    1 : All I frames are IDR.                                             */
  /*    2 : 1 out of 2 I frames are IDR starting from first I frame           */
  /*    -ve values are not allowed.                                           */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"IDRFrameInterval",&gParamsOrg.IDRFrameInterval,
                                           sizeof(gParamsOrg.IDRFrameInterval)},
  /*--------------------------------------------------------------------------*/
  /* Force bottom field of Intra frame as Intra field                         */
  /* Supported values are                                                     */
  /*    0 - Bottom field as P frame                                           */
  /*    1 - Bottom field as I frame                                           */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"bottomFieldIntra",&gParamsOrg.bottomFieldIntra,
                                           sizeof(gParamsOrg.bottomFieldIntra)},
  /*--------------------------------------------------------------------------*/
  /* Tranform type used while encoding                                        */
  /* Supported values are                                                     */
  /*  0  - 4x4 trasform type                                                  */
  /*  1  - 8x8 transform type (valid only for High profile )                  */
  /*  2  - Transform type is adaptive based on content                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"transformBlockSize",&gParamsOrg.transformBlockSize,
                                         sizeof(gParamsOrg.transformBlockSize)},
  /*--------------------------------------------------------------------------*/
  /* Limits the maximum frame number in the bit-stream to                     */
  /*  (1<< (log2MaxFNumMinus4 + 4))                                           */
  /* Supported values are : values ranging from 0 to 12                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"log2MaxFNumMinus4",&gParamsOrg.log2MaxFNumMinus4,
                                          sizeof(gParamsOrg.log2MaxFNumMinus4)},
  /*--------------------------------------------------------------------------*/
  /* Picture order count type                                                 */
  /* Supported values are                                                     */
  /*   0 - POC type 0                                                         */
  /*   1 - POC type 1                                                         */
  /*   2 - POC type 2                                                         */
  /*  Default value is 0                                                      */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"picOrderCountType",&gParamsOrg.picOrderCountType,
                                          sizeof(gParamsOrg.picOrderCountType)},
  /*--------------------------------------------------------------------------*/
  /* Flag to indicate field order in interlaced content                       */
  /* Supported values are                                                     */
  /*   0 - Bottom field first                                                 */
  /*   1 - Top filed first                                                    */
  /*    TODO : need to find defalut parameter                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"topFieldFirstFlag",&gInputBufDescOrg.topFieldFirstFlag,
                                    sizeof(gInputBufDescOrg.topFieldFirstFlag)},
  /*--------------------------------------------------------------------------*/
  /* Interlced field coding type selection                                    */
  /* Supported vaues are                                                      */
  /*  2 - Field only coding with fixed partiy scheme and                      */
  /*                                  Use Most recent field for refernece     */
  /*  3 - Field only coding where codec decides the partiy of                 */
  /*           the field to be used based upon content (adaptive)             */
  /*  4 - Use same parity field for refernece                                 */
  /*  Default value is - 3                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"interlaceCodingType",&gParamsOrg.interlaceCodingType,
                                        sizeof(gParamsOrg.interlaceCodingType)},
  /*Rate control */
  /*--------------------------------------------------------------------------*/
  /* Flag used to select rate control algo selection                          */
  /*   Supported values are                                                   */
  /*    0 - Default rate control parameters are used for encoding             */
  /*    1 - User defined parameters are used for encoding                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"rateControlParamPreset",
                          &gParamsOrg.rateControlParams.rateControlParamsPreset,
                  sizeof(gParamsOrg.rateControlParams.rateControlParamsPreset)},
  /*--------------------------------------------------------------------------*/
  /* Scaling Matrix selection of encoder                                      */
  /* Supported values are                                                     */
  /*   0 - No scaling matrix                                                  */
  /*   1 - Scaling Matrix for normal content                                  */
  /*   2 - Scaling Matrix for Noisy content                                   */
  /*   3 - Default Scaling Matrix provided by H.264 standard                  */
  /*   Defalut value is - 0                                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"scalingMatrixPreset",
                              &gParamsOrg.rateControlParams.scalingMatrixPreset,
                      sizeof(gParamsOrg.rateControlParams.scalingMatrixPreset)},
  /*--------------------------------------------------------------------------*/
  /* Initial Quantization Parameter for I/IDR frames.                         */
  /* Supported values are                                                     */
  /*          -1 to  51                                                       */
  /*          -1 : Auto Initialization else other wise Initial QP.            */
  /*          when rateControlPreset = IVIDEO_NONE, this quantization         */
  /*           parameter is used by the whole video frame/field               */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpI",&gParamsOrg.rateControlParams.qpI,
                                      sizeof(gParamsOrg.rateControlParams.qpI)},
  /*--------------------------------------------------------------------------*/
  /* Initial Quantization Parameter for P frames.                             */
  /* Supported values are                                                     */
  /*          -1 to  51                                                       */
  /*          -1 : Auto Initialization else other wise Initial QP.            */
  /*          when rateControlPreset = IVIDEO_NONE, this quantization         */
  /*           parameter is used by the whole video frame/field               */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpP",&gParamsOrg.rateControlParams.qpP,
                                      sizeof(gParamsOrg.rateControlParams.qpP)},
  /*--------------------------------------------------------------------------*/
  /* Offset of B frames Quantization Parameter from P frames.                 */
  /* Supported values are                                                     */
  /*          -1 to 51                                                        */
  /*          -1 : Auto Initialization else other wise user provided offset   */
  /*          if after adding the qpOffsetB into qp of P frame it exceeds     */
  /*            51 then it is clipped to 51                                   */
  /*          when rateControlPreset = IVIDEO_NONE, this offset parameter is  */
  /*          used by the whole video frame/field                             */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpOffsetB",&gParamsOrg.rateControlParams.qpOffsetB,
                                sizeof(gParamsOrg.rateControlParams.qpOffsetB)},
  /*--------------------------------------------------------------------------*/
  /* Rate control algorithm used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"rcAlgo",&gParamsOrg.rateControlParams.rcAlgo,
                                   sizeof(gParamsOrg.rateControlParams.rcAlgo)},
  /*--------------------------------------------------------------------------*/
  /* minPicSizeRatioI to be used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"minPicSizeRatioI",
                                &gParamsOrg.rateControlParams.minPicSizeRatioI,
                         sizeof(gParamsOrg.rateControlParams.minPicSizeRatioI)},

  /*--------------------------------------------------------------------------*/
  /* maxPicSizeRatioI to be used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"maxPicSizeRatioI",
                                 &gParamsOrg.rateControlParams.maxPicSizeRatioI,
                         sizeof(gParamsOrg.rateControlParams.maxPicSizeRatioI)},
  /*--------------------------------------------------------------------------*/
  /* minPicSizeRatioP to be used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"minPicSizeRatioP",
                                 &gParamsOrg.rateControlParams.minPicSizeRatioP,
                         sizeof(gParamsOrg.rateControlParams.minPicSizeRatioP)},

  /*--------------------------------------------------------------------------*/
  /* maxPicSizeRatioP to be used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"maxPicSizeRatioP",
                                 &gParamsOrg.rateControlParams.maxPicSizeRatioP,
                         sizeof(gParamsOrg.rateControlParams.maxPicSizeRatioP)},
  /*--------------------------------------------------------------------------*/
  /* minPicSizeRatioB to be used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"minPicSizeRatioB",
                                 &gParamsOrg.rateControlParams.minPicSizeRatioB,
                         sizeof(gParamsOrg.rateControlParams.minPicSizeRatioB)},

  /*--------------------------------------------------------------------------*/
  /* maxPicSizeRatioB to be used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"maxPicSizeRatioB",
                                 &gParamsOrg.rateControlParams.maxPicSizeRatioB,
                         sizeof(gParamsOrg.rateControlParams.maxPicSizeRatioB)},

  /*--------------------------------------------------------------------------*/
  /* frameSkipThMulQ5 to be used                                              */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"frameSkipThMulQ5",
                                 &gParamsOrg.rateControlParams.frameSkipThMulQ5,
                         sizeof(gParamsOrg.rateControlParams.frameSkipThMulQ5)},
               
  /*--------------------------------------------------------------------------*/
  /* vbvUseLevelThQ5 to be used                                               */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"vbvUseLevelThQ5",&gParamsOrg.rateControlParams.vbvUseLevelThQ5,
                          sizeof(gParamsOrg.rateControlParams.vbvUseLevelThQ5)},

  /*--------------------------------------------------------------------------*/
  /* rcTransitionSpeed used                                                   */
  /* TODO : Need to get clarifications                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"rcTransitSpeed2Lambda3ChromaHNS4",
                                             &gParamsOrg.reservedParams[1],
                                      sizeof(gParamsOrg.reservedParams[1])},

  /*--------------------------------------------------------------------------*/
  /* Maximum Quantization Parameter for I/IDR frame(s).                       */
  /* Supported values are                                                     */
  /*          0 to  51.                                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpMaxI",&gParamsOrg.rateControlParams.qpMaxI,
                                   sizeof(gParamsOrg.rateControlParams.qpMaxI)},
  /*--------------------------------------------------------------------------*/
  /* Minimum Quantization Parameter for I/IDR frame(s).                       */
  /* Supported values are                                                     */
  /*          0 to  51.                                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpMinI",&gParamsOrg.rateControlParams.qpMinI,
                                   sizeof(gParamsOrg.rateControlParams.qpMinI)},
  /*--------------------------------------------------------------------------*/
  /* Maximum Quantization Parameter for P frame(s).                           */
  /* Supported values are                                                     */
  /*          0 to  51.                                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpMaxP",&gParamsOrg.rateControlParams.qpMaxP,
                                   sizeof(gParamsOrg.rateControlParams.qpMaxP)},
  /*--------------------------------------------------------------------------*/
  /* Minimum Quantization Parameter for P frame(s).                           */
  /* Supported values are                                                     */
  /*          0 to  51.                                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpMinP",&gParamsOrg.rateControlParams.qpMinP,
                                   sizeof(gParamsOrg.rateControlParams.qpMinP)},
  /*--------------------------------------------------------------------------*/
  /* Maximum Quantization Parameter for B frame(s).                           */
  /* Supported values are                                                     */
  /*          0 to  51.                                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpMaxB",&gParamsOrg.rateControlParams.qpMaxB,
                                   sizeof(gParamsOrg.rateControlParams.qpMaxB)},
  /*--------------------------------------------------------------------------*/
  /* Minimum Quantization Parameter for B frame(s).                           */
  /* Supported values are                                                     */
  /*          0 to  51.                                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"qpMinB",&gParamsOrg.rateControlParams.qpMinB,
                                   sizeof(gParamsOrg.rateControlParams.qpMinB)},
  /*--------------------------------------------------------------------------*/
  /* Controls Frame Skip. non-zero means frames can be skipped                */
  /* to achieve target bit-rate                                               */
  /* Supported values are                                                     */
  /*    0 - No skip frames                                                    */
  /*    1 - skip frames are allowed                                           */
  /*    Defalult value is - 0                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"allowFrameSkip",&gParamsOrg.rateControlParams.allowFrameSkip,
                           sizeof(gParamsOrg.rateControlParams.allowFrameSkip)},
  /*--------------------------------------------------------------------------*/
  /* Flag to remove high frequency coeff                                      */
  /* Supported values are                                                     */
  /*    0 - Do not suppress high frequency coeff                              */
  /*    1 - Suppress high frequency coeff                                     */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"removeExpensiveCoeff",
                             &gParamsOrg.rateControlParams.removeExpensiveCoeff,
                     sizeof(gParamsOrg.rateControlParams.removeExpensiveCoeff)},
  /*--------------------------------------------------------------------------*/
  /* Specifies offset to be added to luma QP for addressing QPC values table  */
  /* for chroma components                                                    */
  /* Supported values are                                                     */
  /*          -12 to 12                                                       */
  /*          Default value is 0                                              */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"chromaQPIndexOffset",
                              &gParamsOrg.rateControlParams.chromaQPIndexOffset,
                      sizeof(gParamsOrg.rateControlParams.chromaQPIndexOffset)},
  /*--------------------------------------------------------------------------*/
  /* This provides configurality to control I frame Quality wrt to P frame.   */
  /* Higher Quality factor means I frame quality is given higher improtance   */
  /* compared to P frame.                                                     */
  /* Supported values are                                                     */
  /*    0 - Same quality factor                                               */
  /*    1 - High quality factor                                               */
  /*    2 - Highest quality factor                                            */
  /*    Default value is - 1                                                  */
  /* TODO : Need to check whether it is supproted or not                      */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"IPQualityFactor",&gParamsOrg.rateControlParams.IPQualityFactor,
                          sizeof(gParamsOrg.rateControlParams.IPQualityFactor)},
  /*--------------------------------------------------------------------------*/
  /* Initial Buffer level for HRD compliance. It informs that Hypothtical     */
  /* decoder can start after how much time.                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"initialBufferLevel",
                               &gParamsOrg.rateControlParams.initialBufferLevel,
                       sizeof(gParamsOrg.rateControlParams.initialBufferLevel)},
  /*--------------------------------------------------------------------------*/
  /* Hypothetical Reference Decoder Buffer Size. This size controls the frame */
  /* skip logic of the encoder. for low delay applications this size should   */
  /* be small.                                                                */
  /* Supported values are                                                     */
  /*            Should be given based on bitrate of the content               */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"HRDBufferSize",&gParamsOrg.rateControlParams.HRDBufferSize,
                            sizeof(gParamsOrg.rateControlParams.HRDBufferSize)},
  /*inter coding params*/
  /*--------------------------------------------------------------------------*/
  /* Inter coding mode preset                                                 */
  /* Supported values are                                                     */
  /*    0 - Default inter coding mode                                         */
  /*    1 - Uses user defined inter coding parameters                         */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"interCodingPreset",
                                &gParamsOrg.interCodingParams.interCodingPreset,
                        sizeof(gParamsOrg.interCodingParams.interCodingPreset)},
  /*--------------------------------------------------------------------------*/
  /* Horizontal Search Range for P frames                                     */
  /* Supported values are                                                     */
  /*    16 to 144                                                             */
  /*    Default value is 144                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"searchRangeHorP",&gParamsOrg.interCodingParams.searchRangeHorP,
                          sizeof(gParamsOrg.interCodingParams.searchRangeHorP)},
  /*--------------------------------------------------------------------------*/
  /* Vertical Search Range for P frames                                       */
  /* Supported values are                                                     */
  /*    16 to 32                                                              */
  /*    Default value is 32                                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"searchRangeVerP",&gParamsOrg.interCodingParams.searchRangeVerP,
                          sizeof(gParamsOrg.interCodingParams.searchRangeVerP)},
  /*--------------------------------------------------------------------------*/
  /* Horizontal Search Range for B frames                                     */
  /* Supported values are                                                     */
  /*    16 to 144                                                             */
  /*    Default value is 144                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"searchRangeHorB",&gParamsOrg.interCodingParams.searchRangeHorB,
                          sizeof(gParamsOrg.interCodingParams.searchRangeHorB)},
  /*--------------------------------------------------------------------------*/
  /* Vertical Search Range for P frames                                       */
  /* Supported values are                                                     */
  /*    16 to 32                                                              */
  /*    Default value is 16                                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"searchRangeVerB",&gParamsOrg.interCodingParams.searchRangeVerB,
                          sizeof(gParamsOrg.interCodingParams.searchRangeVerB)},
  /*--------------------------------------------------------------------------*/
  /* Bias Control for having a macro block coded as inter vs Intra            */
  /* Supported values are                                                     */
  /*    0 - Low biasing factor                                                */
  /*    1 - Medium biasing factor                                             */
  /*    2 - High biasing factor                                               */
  /*    Default value is 1                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"interCodingBias",&gParamsOrg.interCodingParams.interCodingBias,
                          sizeof(gParamsOrg.interCodingParams.interCodingBias)},
  /*--------------------------------------------------------------------------*/
  /* Bias Control for having a macro block use skip MV vs regular MV          */
  /* Supported values are                                                     */
  /*    0 - Low biasing factor                                                */
  /*    1 - Medium biasing factor                                             */
  /*    2 - High biasing factor                                               */
  /*    Default value is 1                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"skipMVCodingBias",
                                 &gParamsOrg.interCodingParams.skipMVCodingBias,
                         sizeof(gParamsOrg.interCodingParams.skipMVCodingBias)},
  /*--------------------------------------------------------------------------*/
  /* minimum block size for P frames                                          */
  /* Supported values are                                                     */
  /*    0 - 16x16 block size                                                  */
  /*    1 - 8x8 block size                                                    */
  /*    2 - 4x4 block size                                                    */
  /*    Default value is 0                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"minBlockSizeP",&gParamsOrg.interCodingParams.minBlockSizeP,
                            sizeof(gParamsOrg.interCodingParams.minBlockSizeP)},
  /*--------------------------------------------------------------------------*/
  /* minimum block size for B frames                                          */
  /* Supported values are                                                     */
  /*    0 - 16x16 block size                                                  */
  /*    1 - 8x8 block size                                                    */
  /*    2 - 4x4 block size                                                    */
  /*    Default value is 0                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"minBlockSizeB",&gParamsOrg.interCodingParams.minBlockSizeB,
                            sizeof(gParamsOrg.interCodingParams.minBlockSizeB)},
  /*--------------------------------------------------------------------------*/
  /* Search center for Motion estimation i.e global motion vector in X dir    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"searchCenter_x",&gDynamicParamsOrg.searchCenter.x,
                                      sizeof(gDynamicParamsOrg.searchCenter.x)},
  /*--------------------------------------------------------------------------*/
  /* Search center for Motion estimation i.e global motion vector in X dir    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"searchCenter_y",&gDynamicParamsOrg.searchCenter.y,
                                      sizeof(gDynamicParamsOrg.searchCenter.y)},

/*  Intra coding parameters */
  /*--------------------------------------------------------------------------*/
  /* Intra coding mode preset                                                 */
  /* Supported values are                                                     */
  /*    0 - Default intra coding params                                       */
  /*    1 - Uses user defined intra coding parameters                         */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"intraCodingPreset",
                                &gParamsOrg.intraCodingParams.intraCodingPreset,
                        sizeof(gParamsOrg.intraCodingParams.intraCodingPreset)},
  /*--------------------------------------------------------------------------*/
  /*  parameter controls the Luma Intra4x4 encoding in video encoder. A       */
  /*  bit-field is given for each Luma intra4x4 mode as shown below.          */
  /*  This field is H.264 specific                                            */
  /*  HOR_UP|VERT_LEFT|HOR_DOWN|VERT_RIGHT|DIAG_DOWN_RIGHT|                   */
  /*  DIAG_DOWN_LEFT|DC|HOR|VER Set/ reset particular bit to enable/disable   */
  /*  that mode (0=disable, 1=enable) DC (bit-2)is don't care                 */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"lumaIntra4x4Enable",
                               &gParamsOrg.intraCodingParams.lumaIntra4x4Enable,
                       sizeof(gParamsOrg.intraCodingParams.lumaIntra4x4Enable)},
  /*--------------------------------------------------------------------------*/
  /*  parameter controls the Luma Intra8x8 encoding in video encoder.         */
  /*  bit-field is given for each Luma intra8x8 mode as shown below.          */
  /*  HOR_UP|VERT_LEFT|HOR_DOWN|VERT_RIGHT|DIAG_DOWN_RIGHT|                   */
  /*  DIAG_DOWN_LEFT|DC|HOR|VER                                               */
  /*  Set/ reset particular bit to enable/disable that mode                   */
  /*  (0=disable, 1=enable) DC (bit-2)is don't care                           */
  /*  Example : 139(decimal) ==> 0x8B =>> 010001011 (bits)                    */
  /*        ==> HOR, VER, VERT_LEFT are enabled and DC is always enabled      */
  /*  Default value is - 0xFF                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"lumaIntra8x8Enable",
                               &gParamsOrg.intraCodingParams.lumaIntra8x8Enable,
                       sizeof(gParamsOrg.intraCodingParams.lumaIntra8x8Enable)},
  /*--------------------------------------------------------------------------*/
  /* parameter controls the Luma Intra16x16 encoding in video encoder.        */
  /*  A bit-field is given for each Luma intra16x16 mode as shown below.      */
  /*      PLANE|DC|HOR|VER  Set/ reset particular bit to enable/disable that  */
  /*  mode (0=disable, 1=enable)   DC (bit-2)is don't care                    */
  /*  Default value is - 0xF                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"lumaIntra16x16Enable",
                             &gParamsOrg.intraCodingParams.lumaIntra16x16Enable,
                     sizeof(gParamsOrg.intraCodingParams.lumaIntra16x16Enable)},
  /*--------------------------------------------------------------------------*/
  /*  This parameter controls the chroma Intra8x8 encoding in video encoder.  */
  /*  A bit-field is given for each chroma intra8x8 mode as shown below.      */
  /*    PLANE|VER|HOR|DC  Set/ reset particular bit to enable/disable that    */
  /*    mode (0=disable, 1=enable)  DC (bit-0)is don't care                   */
  /* Default value is - 0xF                                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"chromaIntra8x8Enable",
                             &gParamsOrg.intraCodingParams.chromaIntra8x8Enable,
                     sizeof(gParamsOrg.intraCodingParams.chromaIntra8x8Enable)},
  /*--------------------------------------------------------------------------*/
  /* Mechanism to do intra Refresh                                            */
  /* Supported values are                                                     */
  /*    0 - Doesn't insert forcefully intra macro blocks                      */
  /*    1 - Insters intra macro blocks in a cyclic fashion ,cyclic interval is*/
  /*        equal to intraRefreshRate                                         */
  /*    2 - Insters Intra Slices(Row based) in a cyclic fashion, cyclic       */
  /*        interval is equal to intraRefreshRate                             */
  /*    3 - position of intra macro blocks is intelligently chosen by encoder,*/
  /*        but the number of forcely coded intra macro blocks in a frame is  */
  /*        gaurnteed to be equal to totalMbsInFrame/intraRefreshRate         */
  /*    4 - GDR scheme, but needs a inArgs->control to be START_GDR command to*/
  /*         kick start the GDR activity.                                     */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"intraRefreshMethod",
                               &gParamsOrg.intraCodingParams.intraRefreshMethod,
                       sizeof(gParamsOrg.intraCodingParams.intraRefreshMethod)},
  /*--------------------------------------------------------------------------*/
  /* Rate at which intra Refresh is done, This rate is specified as           */
  /* One IntraMB per # MBs. For example if rate is 20 it means that           */
  /* there has to be  one intra MB(s) per 20 Mbs                              */
  /* Default value is - 0 (ignored)                                           */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"intraRefreshRate",
                                 &gParamsOrg.intraCodingParams.intraRefreshRate,
                         sizeof(gParamsOrg.intraCodingParams.intraRefreshRate)},
  /*--------------------------------------------------------------------------*/
  /* Tells the number of MB rows of overlap between Intra refresh regions     */
  /* across two successive frames.                                            */
  /* Default value is - 0 (ignored)                                           */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"gdrOverlapRows",
       &gParamsOrg.intraCodingParams.gdrOverlapRowsBtwFrames,
                  sizeof(gParamsOrg.intraCodingParams.gdrOverlapRowsBtwFrames)},
  /*--------------------------------------------------------------------------*/
  /* Controls the intra macroblock coding in P slices.                        */
  /* Supported values are                                                     */
  /*  TODO : need to update this                                              */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"constrainedIntraPredEnable",
                  &gParamsOrg.intraCodingParams.constrainedIntraPredEnable,
               sizeof(gParamsOrg.intraCodingParams.constrainedIntraPredEnable)},
  /*--------------------------------------------------------------------------*/
  /* parameter controls the chroma Intra prediction search. User can choose   */
  /* to perfom chroma intra estimation for both Cb and Cr samples or          */
  /* only on Cr samples.                                                      */
  /* Supported values are                                                     */
  /*    0 - BOth Cb and Cr component                                          */
  /*    1 - Only Cr Component                                                 */
  /*  Default value is - 1                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"chromaComponentEnable",
                            &gParamsOrg.intraCodingParams.chromaComponentEnable,
                    sizeof(gParamsOrg.intraCodingParams.chromaComponentEnable)},
  /*NALU Control Params*/
  /*--------------------------------------------------------------------------*/
  /* Preset value to use User defined NAL unit control parameters             */
  /* Supported values are                                                     */
  /*    0 - Default NALU insertion                                            */
  /*    1 - User defined NALU insertion                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"naluControlPreset",
                             &gParamsOrg.nalUnitControlParams.naluControlPreset,
                     sizeof(gParamsOrg.nalUnitControlParams.naluControlPreset)},
  /*--------------------------------------------------------------------------*/
  /* parameter controls the insertion of different NALU at Start of Sequence  */
  /* A bit-field is given for each NALU type as shown below.                  */
  /*    14|     13|    12|      11|   10|  9|  8|  7|  6|        5|           */
  /*UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|SPS|SEI|IDR_SLICE|           */
  /*           4|         3|         2|    1|          0                      */
  /*  SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED                      */
  /* This field is  Set/ reset particular bit to enable/disable that insertion*/
  /* of that NALU (0=disable, 1=enable)                                       */
  /* UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3),               */
  /* SLICE_DP_C(bit-4), IDR_SLICE(bit-5), EOSEQ (bit-10) and EOSTREAM (bit-11)*/
  /* are don't care and assumed to be zero .                                  */
  /* SPS (bit-7), PPS(bit-8) are don't care and assumed to be one.            */
  /* Default value is - 0x1A0                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"naluPresentMaskStartOfSequence",
           &gParamsOrg.nalUnitControlParams.naluPresentMaskStartOfSequence,
        sizeof(gParamsOrg.nalUnitControlParams.naluPresentMaskStartOfSequence)},
  /*--------------------------------------------------------------------------*/
  /* parameter controls the insertion of different NALU at IDR picture        */
  /* A bit-field is given for each NALU type as shown below.                  */
  /*       14|     13|    12|      11|   10|  9|  8|  7|  6|        5|        */
  /*   UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|SPS|SEI|IDR_SLICE|        */
  /*            4|         3|         2|    1|          0                     */
  /*   SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED                     */
  /* Set/ reset particular bit to enable/disable that insertion of that NALU  */
  /* (0=disable, 1=enable)                                                    */
  /* UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3),               */
  /* SLICE_DP_C(bit-4), IDR_SLICE(bit-5), EOSEQ (bit-10) and EOSTREAM (bit-11)*/
  /* are don't care and assumed to be zero.                                   */
  /* Default value is - 0x1A0                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"naluPresentMaskIDRPicture",
               &gParamsOrg.nalUnitControlParams.naluPresentMaskIDRPicture,
             sizeof(gParamsOrg.nalUnitControlParams.naluPresentMaskIDRPicture)},
  /*--------------------------------------------------------------------------*/
  /* parameter controls the insertion of different NALU at I picture          */
  /*      A bit-field is given for each NALU type as shown below.             */
  /*     14|     13|    12|      11|   10|  9|  8|  7|  6|        5|          */
  /* UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|SPS|SEI|IDR_SLICE|          */
  /*         4|         3|         2|    1|          0                        */
  /*SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED                        */
  /* Set/ reset particular bit to enable/disable that insertion of that NALU  */
  /* (0=disable, 1=enable)                                                    */
  /* UNSPECIFIED (bit-0), SLICE_DP_A(bit-2), SLICE_DP_B(bit-3),               */
  /* SLICE_DP_C(bit-4), IDR_SLICE(bit-5), EOSEQ (bit-10) and EOSTREAM (bit-11)*/
  /* are don't care and assumed to be zero.                                   */
  /* Default value is - 0x2                                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"naluPresentMaskIntraPicture",
              &gParamsOrg.nalUnitControlParams.naluPresentMaskIntraPicture,
           sizeof(gParamsOrg.nalUnitControlParams.naluPresentMaskIntraPicture)},
  /*--------------------------------------------------------------------------*/
  /* parameter controls the insertion of different NALU at NON intra picture  */
  /* A bit-field is given for each NALU type as shown below.                  */
  /*     14|     13|    12|      11|   10|  9|  8|  7|  6|        5|          */
  /* UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|SPS|SEI|IDR_SLICE|          */
  /*          4|         3|         2|    1|          0                       */
  /* SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED                       */
  /* Set/ reset particular bit to enable/disable that insertion of that       */
  /* NALU (0=disable, 1=enable). UNSPECIFIED (bit-0), SLICE_DP_A(bit-2),      */
  /* SLICE_DP_B(bit-3),SLICE_DP_C(bit-4),IDR_SLICE(bit-5), EOSEQ (bit-10)     */
  /* and EOSTREAM (bit-11) are don't care and assumed to be zero.             */
  /* Default value is 0x2                                                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"naluPresentMaskNonIntraPicture",
           &gParamsOrg.nalUnitControlParams.naluPresentMaskNonIntraPicture,
        sizeof(gParamsOrg.nalUnitControlParams.naluPresentMaskNonIntraPicture)},
  /*--------------------------------------------------------------------------*/
  /* parameter controls the insertion of different NALU at End of Sequence    */
  /* A bit-field is given for each NALU type as shown below.                  */
  /*     14|     13|    12|      11|   10|  9|  8|  7|  6|        5|          */
  /* UD_SEI|SPS_VUI|FILLER|EOSTREAM|EOSEQ|AUD|PPS|SPS|SEI|IDR_SLICE|          */
  /*           4|         3|         2|    1|          0                      */
  /*  SLICE_DP_C|SLICE_DP_B|SLICE_DP_A|SLICE|UNSPECIFIED                      */
  /* Set/ reset particular bit to enable/disable that insertion of that       */
  /* NALU (0=disable, 1=enable). UNSPECIFIED (bit-0), SLICE_DP_A(bit-2),      */
  /* SLICE_DP_B(bit-3), SLICE_DP_C(bit-4), SPS_VUI (bit-13), FILLER (bit-12), */
  /* AUD(bit-9), PPS(bit-8), SPS(bit-7), SEI(bit-6),IDR_SLICE(bit-5),         */
  /* SLICE (bit-1) are don't care and assumed to be zero.                     */
  /* Defalutt value is - 0xC00                                                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"naluPresentMaskEndOfSequence",
            &gParamsOrg.nalUnitControlParams.naluPresentMaskEndOfSequence,
          sizeof(gParamsOrg.nalUnitControlParams.naluPresentMaskEndOfSequence)},
  /*Slice coding Params*/
  /*--------------------------------------------------------------------------*/
  /* Preset value for slice coding mode                                       */
  /* Supported values are                                                     */
  /*      0 - Use default slice coding params                                 */
  /*      1 - Use user defined slice coding params                            */
  /* Default value is - 0                                                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceCodingPreset",
                                &gParamsOrg.sliceCodingParams.sliceCodingPreset,
                        sizeof(gParamsOrg.sliceCodingParams.sliceCodingPreset)},
  /*--------------------------------------------------------------------------*/
  /* Type of slice coding                                                     */
  /* Supported values are                                                     */
  /*    0 - slice coding mode is frame based                                  */
  /*    1 - Slices are controlled based upon number of Macroblocks            */
  /*    2 - Slices are controlled based upon number of bytes                  */
  /*    3 - Slices are controlled based upon user defined offset in unit of   */
  /*        Rows                                                              */
  /* Default value is - 0                                                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceMode",&gParamsOrg.sliceCodingParams.sliceMode,
                                sizeof(gParamsOrg.sliceCodingParams.sliceMode)},
  /*--------------------------------------------------------------------------*/
  /* The meaning of this parameter depends upon sliceMode.                    */
  /* sliceMode == 1 then this parameter informs the number of Macroblocks     */
  /*                in one slice                                              */
  /* sliceMode == 2 then this parameter informs the no of bytes in one slice  */
  /* sliceMode == 3 then this parameter informs the number of offset          */
  /* information provided by user,                                            */
  /* Actual offset are provided with sliceStartOffset                         */
  /* Default value is - 0                                                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceUnitSize",&gParamsOrg.sliceCodingParams.sliceUnitSize,
                            sizeof(gParamsOrg.sliceCodingParams.sliceUnitSize)},
  /*--------------------------------------------------------------------------*/
  /* Type of bitstream to be encoded                                          */
  /* Supported values are                                                     */
  /*    0 - bit-stream contains the start code identifier,Byte format         */
  /*    1 - bit-stream doesn't contain the start code identifier,NAL unit type*/
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"streamFormat",&gParamsOrg.sliceCodingParams.streamFormat,
                            sizeof(gParamsOrg.sliceCodingParams.streamFormat)},
  /*--------------------------------------------------------------------------*/
  /* Offset of the Macroblok from the start of the frame to the 1st slice row */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceStartOffset0",
                              &gParamsOrg.sliceCodingParams.sliceStartOffset[0],
                      sizeof(gParamsOrg.sliceCodingParams.sliceStartOffset[0])},
  /*--------------------------------------------------------------------------*/
  /* Offset of the Macroblok from the start of the frame to the 2nd slice row */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceStartOffset1",
                              &gParamsOrg.sliceCodingParams.sliceStartOffset[1],
                      sizeof(gParamsOrg.sliceCodingParams.sliceStartOffset[1])},
  /*--------------------------------------------------------------------------*/
  /* Offset of the Macroblok from the start of the frame to the 3rd slice row */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceStartOffset2",
                              &gParamsOrg.sliceCodingParams.sliceStartOffset[2],
                      sizeof(gParamsOrg.sliceCodingParams.sliceStartOffset[2])},
  /*Loop filter Params*/
  /*--------------------------------------------------------------------------*/
  /* Preset value for loop filter operation parameters                        */
  /* Supported values are                                                     */
  /*    0 - Use defaulat loop filter operation parameters                     */
  /*    1 - Use user defined loop filter operation parameters                 */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"loopfilterPreset",
                                  &gParamsOrg.loopFilterParams.loopfilterPreset,
                          sizeof(gParamsOrg.loopFilterParams.loopfilterPreset)},
  /*--------------------------------------------------------------------------*/
  /* Disable H.264 loop filter by using this flag                             */
  /* Supporterd values are                                                    */
  /*    0 - Do not use H.264 loop filter                                      */
  /*    1 - Use H.264 loop filter                                             */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"loopfilterDisableIDC",
                              &gParamsOrg.loopFilterParams.loopfilterDisableIDC,
                      sizeof(gParamsOrg.loopFilterParams.loopfilterDisableIDC)},
  /*--------------------------------------------------------------------------*/
  /* alpha offset for loop filter                                             */
  /* Supported values are                                                     */
  /*        from -12 to 12 should be even number                              */
  /*        Default value is 0                                                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"filterOffsetA",&gParamsOrg.loopFilterParams.filterOffsetA,
                             sizeof(gParamsOrg.loopFilterParams.filterOffsetA)},
  /*--------------------------------------------------------------------------*/
  /* Beta offset for loop filter                                              */
  /* Supported values are                                                     */
  /*        from -12 to 12 should be even number                              */
  /*        Default value is 0                                                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"filterOffsetB",&gParamsOrg.loopFilterParams.filterOffsetB,
                             sizeof(gParamsOrg.loopFilterParams.filterOffsetB)},
  /*VUI Coding Params*/
  /*--------------------------------------------------------------------------*/
  /* Preset value for VUI coding parameters encoding                          */
  /* Supported values are                                                     */
  /*    0 - Use default VUI coding parameters                                 */
  /*    1 - Use user defined VUI coding parameters                            */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"vuiCodingPreset",&gParamsOrg.vuiCodingParams.vuiCodingPreset,
                            sizeof(gParamsOrg.vuiCodingParams.vuiCodingPreset)},
  /*--------------------------------------------------------------------------*/
  /* controls the insertion of aspect ratio information in VUI part           */
  /* of bit-stream                                                            */
  /* Supported values are                                                     */
  /*      0 - No aspect ratio related information is transmitted              */
  /*      1 - aspect ratio related information is transmitted                 */
  /*      Default value is - 0                                                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"aspectRatioInfoPresentFlag",
                    &gParamsOrg.vuiCodingParams.aspectRatioInfoPresentFlag,
                 sizeof(gParamsOrg.vuiCodingParams.aspectRatioInfoPresentFlag)},
  /*--------------------------------------------------------------------------*/
  /* Aspect ratio ID, Please refer user guide for further details             */
  /* Default value is - 0                                                     */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"aspectRatioIdc",&gParamsOrg.vuiCodingParams.aspectRatioIdc,
                             sizeof(gParamsOrg.vuiCodingParams.aspectRatioIdc)},
  /*--------------------------------------------------------------------------*/
  /* controls the insertion of video signal type in VUI part of bit-stream    */
  /* Supported values are                                                     */
  /*    0 - No video signal related information is transmitted                */
  /*    1 - video signal related information is transmitted                   */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"videoSignalTypePresentFlag",
                    &gParamsOrg.vuiCodingParams.videoSignalTypePresentFlag,
                 sizeof(gParamsOrg.vuiCodingParams.videoSignalTypePresentFlag)},
  /*--------------------------------------------------------------------------*/
  /* Video signal type                                                        */
  /*    Supported values are                                                  */
  /*    Refer Table E-2 H264 standard                                         */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"videoFormat",&gParamsOrg.vuiCodingParams.videoFormat,
                                sizeof(gParamsOrg.vuiCodingParams.videoFormat)},
  /*--------------------------------------------------------------------------*/
  /* Flag to specigy Range of the pixels                                      */
  /* Supported values are                                                     */
  /*    0 - Video range is not full                                           */
  /*    1 - Video range is full (0 - 255)                                     */
  /*    Default value is - 1                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"videoFullRangeFlag",
                                 &gParamsOrg.vuiCodingParams.videoFullRangeFlag,
                         sizeof(gParamsOrg.vuiCodingParams.videoFullRangeFlag)},
  /*--------------------------------------------------------------------------*/
  /* controls the insertion of timing info related parameters in VUI part     */
  /* of bit-stream                                                            */
  /*    0 - No need to insert timing info the VUI parameters                  */
  /*    1 - Insert timing info to VUI parameter                               */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"timingInfoPresentFlag",
                              &gParamsOrg.vuiCodingParams.timingInfoPresentFlag,
                      sizeof(gParamsOrg.vuiCodingParams.timingInfoPresentFlag)},
  /*--------------------------------------------------------------------------*/
  /* controls the insertion of numUnitsInTicks parameter in VUI part          */
  /* of bit-stream                                                            */
  /*    Default value is - 1000                                               */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"numUnitsInTicks",
                                 &gParamsOrg.vuiCodingParams.numUnitsInTicks,
                         sizeof(gParamsOrg.vuiCodingParams.numUnitsInTicks)},

  {(XDAS_Int8 *)"hrdParamsPresentFlag",
                               &gParamsOrg.vuiCodingParams.hrdParamsPresentFlag,
                       sizeof(gParamsOrg.vuiCodingParams.hrdParamsPresentFlag)},

  /*fmo coding gParamsOrg*/
  /*--------------------------------------------------------------------------*/
  /* Preset flag to use default parameters for FMO encoding                   */
  /* or user defined parameters                                               */
  /* Supported values are                                                     */
  /*  0 - No FMO coding is enabled                                            */
  /*  1 - User defined FMO parameters are used for encding                    */
  /*  Default value is - 0                                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"fmoCodingPreset",&gParamsOrg.fmoCodingParams.fmoCodingPreset,
                            sizeof(gParamsOrg.fmoCodingParams.fmoCodingPreset)},
  /*--------------------------------------------------------------------------*/
  /* Total Number of slice groups                                             */
  /* Supported values are                                                     */
  /*        0 to 8                                                            */
  /*        Default value is - 0                                              */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"numSliceGroups",&gParamsOrg.fmoCodingParams.numSliceGroups,
                             sizeof(gParamsOrg.fmoCodingParams.numSliceGroups)},
  /*--------------------------------------------------------------------------*/
  /* Slice group map type defined by H.264 standard                           */
  /* Supported values are                                                     */
  /*    0 - Interleaved Slice Group                                           */
  /*    1 - Dispersed Slice Group                                             */
  /*    2 - ForeGround with Left Over                                         */
  /*    3 - Box Out                                                           */
  /*    4 - Raster Scan                                                       */
  /*    5 - Wipe slice group                                                  */
  /*    6 - Explicit Slice gropup map                                         */
  /*    Defalut value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceGroupMapType",
                                  &gParamsOrg.fmoCodingParams.sliceGroupMapType,
                          sizeof(gParamsOrg.fmoCodingParams.sliceGroupMapType)},
  /*--------------------------------------------------------------------------*/
  /* Different Scan /rotation order                                           */
  /* Supported values are                                                     */
  /*    0 - Raster scan order                                                 */
  /*    0 - Clockwise (used for BOX OUT FMO Params)                           */
  /*    0 - RIGHT (Used for Wipe FMO type)                                    */
  /*    1 - Reverse Raster Scan Order                                         */
  /*    1 - Counter Clockwise (used for BOX OUT FMO Params)                   */
  /*    1 - LEFT (Used for Wipe FMO type)                                     */
  /*    Default value is 0 (Raster scan order)                                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceGroupChangeDirectionFlag",
                 &gParamsOrg.fmoCodingParams.sliceGroupChangeDirectionFlag,
              sizeof(gParamsOrg.fmoCodingParams.sliceGroupChangeDirectionFlag)},
  /*--------------------------------------------------------------------------*/
  /*  Below is valid only in case of ranser scan order type nad WIPE order    */
  /*  Supported values are                                                    */
  /*    0 and factors of number of MBs in a row                               */
  /*    Default value is - 0                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceGroupChangeRate",
                               &gParamsOrg.fmoCodingParams.sliceGroupChangeRate,
                       sizeof(gParamsOrg.fmoCodingParams.sliceGroupChangeRate)},
  /*--------------------------------------------------------------------------*/
  /*  TODO: need to write proper comment                                      */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceGroupChangeCycle",
                              &gParamsOrg.fmoCodingParams.sliceGroupChangeCycle,
                      sizeof(gParamsOrg.fmoCodingParams.sliceGroupChangeCycle)},
  /*--------------------------------------------------------------------------*/
  /*  TODO: need to write proper comment                                      */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"sliceGroupParams",&gParamsOrg.fmoCodingParams.sliceGroupParams,
                           sizeof(gParamsOrg.fmoCodingParams.sliceGroupParams)},
  /*--------------------------------------------------------------------------*/
  /* Enable encoding GMV data as TI unregistred user data SEI message         */
  /* Supported values are                                                     */
  /*     0 - do not code GMV data SEI message                                 */
  /*     1 - code GMV data as SEI message                                     */
  /*     Default value is - 0                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"GmvDataInSei",
                     &gParamsOrg.enableGMVSei,sizeof(gParamsOrg.enableGMVSei)},

  /*--------------------------------------------------------------------------*/
  /* control of values of constraint set flags in bitstream                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"constraintSetFlags",&gParamsOrg.constraintSetFlags,
                                         sizeof(gParamsOrg.constraintSetFlags)},
  /*--------------------------------------------------------------------------*/
  /* Parameter to get tiler space for luma and chorma buffers                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"lumaTilerSpace",&gConfigOrg.tilerSpace[0],
                                             sizeof(gConfigOrg.tilerSpace[0])},

  {(XDAS_Int8 *)"chromaTilerSpace",&gConfigOrg.tilerSpace[1],
                                             sizeof(gConfigOrg.tilerSpace[1])},

  /*--------------------------------------------------------------------------*/
  /* Parameter to get Ivahd ID                                                */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"ivahdid",&gConfigOrg.ivahdid, sizeof(gConfigOrg.ivahdid)},
  /*--------------------------------------------------------------------------*/
  /* Offset in input sequence for the encoding to start                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"startFrame",&gConfigOrg.startFrame,4},

  /*--------------------------------------------------------------------------*/
  /* Parameter to enable RCDO                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enableRCDO",&gParamsOrg.enableRCDO,
                                                 sizeof(gParamsOrg.enableRCDO)},
  /*--------------------------------------------------------------------------*/
  /* Parameter to enable water marking, as a part of SEI message              */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enableWatermark",&gParamsOrg.enableWatermark,
                                            sizeof(gParamsOrg.enableWatermark)},

  /*-------------------------------------------------------------------------*/
  /* Parameter to get Number  Temporal Layer.                                */
  /* Supported values are                                                    */
  /*    0 - Not supported.This is erroneous case                             */
  /*    1 - Only Base layer available in bit-stream                          */
  /*    2 - Maximum Temporal Level 1 in bit-stream                           */
  /*    3 - Maximum Temporal Level 2 in bit-stream                           */
  /*    4 - Maximum Temporal Level 3 in bit-stream                           */
  /*    Default value is 1 (Only Base Layer)                                 */
  /*-------------------------------------------------------------------------*/
  
  {(XDAS_Int8 *)"numTemporalLayer",&gParamsOrg.numTemporalLayer, 
                                           sizeof(gParamsOrg.numTemporalLayer)},
  /*--------------------------------------------------------------------------*/
  /* This parameter used to control the Reference Picture Marking             */
  /* For any non-zero value means Long-term Picture (MMCO Commands)           */
  /*       0 - Short-term Picture (Sliding Window)                            */
  /*       1 - Long-term Picture (  MMCO Commands)                            */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"referencePicMarking",&gParamsOrg.referencePicMarking,
                                        sizeof(gParamsOrg.referencePicMarking)},
  /*-------------------------------------------------------------------------*/
  /*This parameter configures the codec put SVC extensions in the bit-stream.*/
  /*For normal H.264 operation this Flag needs to be ZERO (default value).   */
  /*For any non-zero value means SVC is Enabled                              */
  /*      0 - SVC Disabled.                                                  */
  /*      1 - SVC Enabled                                                    */
  /*-------------------------------------------------------------------------*/                                              
  {(XDAS_Int8 *)"svcExtensionFlag",&gParamsOrg.svcCodingParams.svcExtensionFlag,
                           sizeof(gParamsOrg.svcCodingParams.svcExtensionFlag)},
  /*--------------------------------------------------------------------------*/
  /* Parameter to enable enableAnalyticinfo                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enableAnalyticinfo", &gParamsOrg.enableAnalyticinfo,
                                         sizeof(gParamsOrg.enableAnalyticinfo)},

  /*--------------------------------------------------------------------------*/
  /* Parameter to enable StaticMBCount                                        */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enableStaticMBCount", &gDynamicParamsOrg.enableStaticMBCount,
                                 sizeof(gDynamicParamsOrg.enableStaticMBCount)},

  /*--------------------------------------------------------------------------*/
  /* Parameter to enable Long Term Ref Frame                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enableLongTermRefFrame",
  &gParamsOrg.enableLongTermRefFrame,sizeof(gParamsOrg.enableLongTermRefFrame)},

  /*--------------------------------------------------------------------------*/
  /* Parameter to give LTRP marking period                                    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"LTRPPeriod",
  &gParamsOrg.LTRPPeriod,sizeof(gParamsOrg.LTRPPeriod)},

  /*--------------------------------------------------------------------------*/
  /* Parameter to enable PRC                                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enablePRC",&gParamsOrg.rateControlParams.enablePRC,
                              sizeof(gParamsOrg.rateControlParams.enablePRC)},

  /*--------------------------------------------------------------------------*/
  /* Parameter to enable partial frame skip                                   */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enablePartialFrameSkip",
                  &gParamsOrg.rateControlParams.enablePartialFrameSkip,
                   sizeof(gParamsOrg.rateControlParams.enablePartialFrameSkip)},

  /*--------------------------------------------------------------------------*/
  /* Parameter to enable VBR clipping                                         */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"discardSavedBits",
                  &gParamsOrg.rateControlParams.discardSavedBits,
                      sizeof(gParamsOrg.rateControlParams.discardSavedBits)},

  /*--------------------------------------------------------------------------*/
  /* Flag to enable testing of runtime parameter change                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enableRunTimeTest", &gConfigOrg.enableRunTimeTest,
                sizeof(gConfigOrg.enableRunTimeTest)},

  /*--------------------------------------------------------------------------*/
  /* Parameter to have frame number at which the dynamic parameters to change */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"DynamicFramePos", &gConfigOrg.DynamicFramePos,
                sizeof(gConfigOrg.DynamicFramePos)},

  /*--------------------------------------------------------------------------*/
  /* Frame Packing SEI preset                                                 */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"framePackingPreset",
                  &gParamsOrg.framePackingSEIParams.framePackingPreset,
                  sizeof(gParamsOrg.framePackingSEIParams.framePackingPreset)},
  {(XDAS_Int8 *)"framePackingType",
                  &gParamsOrg.framePackingSEIParams.framePackingType,
                  sizeof(gParamsOrg.framePackingSEIParams.framePackingType)},
  {(XDAS_Int8 *)"frame0PositionX",
                  &gParamsOrg.framePackingSEIParams.frame0PositionX,
                  sizeof(gParamsOrg.framePackingSEIParams.frame0PositionX)},
  {(XDAS_Int8 *)"frame0PositionY",
                  &gParamsOrg.framePackingSEIParams.frame0PositionY,
                  sizeof(gParamsOrg.framePackingSEIParams.frame0PositionY)},
  {(XDAS_Int8 *)"frame1PositionX",
                  &gParamsOrg.framePackingSEIParams.frame1PositionX,
                  sizeof(gParamsOrg.framePackingSEIParams.frame1PositionX)},
  {(XDAS_Int8 *)"frame1PositionY",
                  &gParamsOrg.framePackingSEIParams.frame1PositionY,
                  sizeof(gParamsOrg.framePackingSEIParams.frame1PositionY)},
  {(XDAS_Int8 *)"reservedByte",
                  &gParamsOrg.framePackingSEIParams.reservedByte,
                  sizeof(gParamsOrg.framePackingSEIParams.reservedByte)},

 /*Stereo Video Inforamation Params*/

 /*--------------------------------------------------------------------------*/
  /* This Preset controls the Enable/Disable of stereo video coding & if its */
  /* enable then controls the USER_DEFINED vs DEFAULT mode. If User need     */
  /* Stereo Video coding & is not aware about other fields, it should be  .  */
  /* set as IH264_STEREOINFO_DEFAULT                                         */
  /*     0  : Stereo Video Coding is Disabled.                               */
  /*     1  : Default stereo video information parameters .                  */
  /*     2  : User defined steroe video information pamameters.              */
  /*-------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"stereoInfoPreset",
                                  &gParamsOrg.stereoInfoParams.stereoInfoPreset,
                          sizeof(gParamsOrg.stereoInfoParams.stereoInfoPreset)},
  /*-------------------------------------------------------------------------*/
  /* This controls the top field in video coded sequence as a left view      */
  /* or right view                                                           */
  /*   1 - Top field in coded video codec sequence is left view              */
  /*   0 - Top field in coded video codec sequence is right view             */
  /*-------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"topFieldIsLeftViewFlag",
                           &gParamsOrg.stereoInfoParams.topFieldIsLeftViewFlag,
                    sizeof(gParamsOrg.stereoInfoParams.topFieldIsLeftViewFlag)},
  /*-------------------------------------------------------------------------*/
  /* This controls the Left/Right view should Refer/NotRefer to              */
  /* Left/Right view.                                                        */
  /*   0 - Leftview can refer to Rightview or Leftview &                     */
  /*       Rightview can refer to Rightview or Leftview.                     */
  /*   1 - Leftview can refer only to Leftview & Rightview can refer         */
  /*       only to Rightview.                                                */
  /*-------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"viewSelfContainedFlag",
                             &gParamsOrg.stereoInfoParams.viewSelfContainedFlag,
                     sizeof(gParamsOrg.stereoInfoParams.viewSelfContainedFlag)},

  /*--------------------------------------------------------------------------*/
  /* Number of blocks to be given as input duringeach DataSyncGetData call    */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"numBlocks0", &gConfigOrg.numBlocks[0],
                sizeof(gConfigOrg.numBlocks[0])},

  {(XDAS_Int8 *)"numBlocks1", &gConfigOrg.numBlocks[1],
                sizeof(gConfigOrg.numBlocks[1])},

  {(XDAS_Int8 *)"numBlocks2", &gConfigOrg.numBlocks[2],
                sizeof(gConfigOrg.numBlocks[2])},

  {(XDAS_Int8 *)"numBlocks3", &gConfigOrg.numBlocks[3],
                sizeof(gConfigOrg.numBlocks[3])},

  {(XDAS_Int8 *)"numBlocks4", &gConfigOrg.numBlocks[4],
                sizeof(gConfigOrg.numBlocks[4])},

  {(XDAS_Int8 *)"numBlocks5", &gConfigOrg.numBlocks[5],
                sizeof(gConfigOrg.numBlocks[5])},

  {(XDAS_Int8 *)"numBlocks6", &gConfigOrg.numBlocks[6],
                sizeof(gConfigOrg.numBlocks[6])},

  {(XDAS_Int8 *)"numBlocks7", &gConfigOrg.numBlocks[7],
                sizeof(gConfigOrg.numBlocks[7])},

  /*--------------------------------------------------------------------------*/
  /*                                  ROI related parameters                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"enableROI",&gDynamicParamsOrg.enableROI,
                                           sizeof(gDynamicParamsOrg.enableROI)},
  {(XDAS_Int8 *)"ROIcfg",&gConfigOrg.roiinputFile,0},                                            
                          
  {(XDAS_Int8 *)"NumOfROI",&gInArgsOrg.roiInputParams.numOfROI,
                                    sizeof(gInArgsOrg.roiInputParams.numOfROI)},

  /*--------------------------------------------------------------------------*/
  /*                                  ROI  1                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"ROI_1_Xmin",&gInArgsOrg.roiInputParams.listROI[0].topLeft.x,
                        sizeof(gInArgsOrg.roiInputParams.listROI[0].topLeft.x)},
  {(XDAS_Int8 *)"ROI_1_Ymin",&gInArgsOrg.roiInputParams.listROI[0].topLeft.y,
                        sizeof(gInArgsOrg.roiInputParams.listROI[0].topLeft.y)},
  {(XDAS_Int8 *)"ROI_1_Xmax",
                            &gInArgsOrg.roiInputParams.listROI[0].bottomRight.x,
                    sizeof(gInArgsOrg.roiInputParams.listROI[0].bottomRight.x)},
  {(XDAS_Int8 *)"ROI_1_Ymax",
                            &gInArgsOrg.roiInputParams.listROI[0].bottomRight.y,
                    sizeof(gInArgsOrg.roiInputParams.listROI[0].bottomRight.y)},
  {(XDAS_Int8 *)"ROI_1_prty",&gInArgsOrg.roiInputParams.roiPriority[0],
                              sizeof(gInArgsOrg.roiInputParams.roiPriority[0])},
  {(XDAS_Int8 *)"ROI_1_type",&gInArgsOrg.roiInputParams.roiType[0],
                                  sizeof(gInArgsOrg.roiInputParams.roiType[0])},

  /*--------------------------------------------------------------------------*/
  /*                                  ROI  2                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"ROI_2_Xmin",&gInArgsOrg.roiInputParams.listROI[1].topLeft.x,
                        sizeof(gInArgsOrg.roiInputParams.listROI[1].topLeft.x)},
  {(XDAS_Int8 *)"ROI_2_Ymin",&gInArgsOrg.roiInputParams.listROI[1].topLeft.y,
                        sizeof(gInArgsOrg.roiInputParams.listROI[1].topLeft.y)},
  {(XDAS_Int8 *)"ROI_2_Xmax",
                           &gInArgsOrg.roiInputParams.listROI[1].bottomRight.x,
                    sizeof(gInArgsOrg.roiInputParams.listROI[1].bottomRight.x)},
  {(XDAS_Int8 *)"ROI_2_Ymax",
                            &gInArgsOrg.roiInputParams.listROI[1].bottomRight.y,
                    sizeof(gInArgsOrg.roiInputParams.listROI[1].bottomRight.y)},
  {(XDAS_Int8 *)"ROI_2_prty",&gInArgsOrg.roiInputParams.roiPriority[1],
                              sizeof(gInArgsOrg.roiInputParams.roiPriority[1])},
  {(XDAS_Int8 *)"ROI_2_type",&gInArgsOrg.roiInputParams.roiType[1],
                                  sizeof(gInArgsOrg.roiInputParams.roiType[1])},
                                     
  /*--------------------------------------------------------------------------*/
  /*                                  ROI  3                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"ROI_3_Xmin",&gInArgsOrg.roiInputParams.listROI[2].topLeft.x,
                        sizeof(gInArgsOrg.roiInputParams.listROI[2].topLeft.x)},
  {(XDAS_Int8 *)"ROI_3_Ymin",&gInArgsOrg.roiInputParams.listROI[2].topLeft.y,
                        sizeof(gInArgsOrg.roiInputParams.listROI[2].topLeft.y)},
  {(XDAS_Int8 *)"ROI_3_Xmax",
                            &gInArgsOrg.roiInputParams.listROI[2].bottomRight.x,
                    sizeof(gInArgsOrg.roiInputParams.listROI[2].bottomRight.x)},
  {(XDAS_Int8 *)"ROI_3_Ymax",
                            &gInArgsOrg.roiInputParams.listROI[2].bottomRight.y, 
                    sizeof(gInArgsOrg.roiInputParams.listROI[2].bottomRight.y)},
  {(XDAS_Int8 *)"ROI_3_prty",&gInArgsOrg.roiInputParams.roiPriority[2],
                              sizeof(gInArgsOrg.roiInputParams.roiPriority[2])},
  {(XDAS_Int8 *)"ROI_3_type",&gInArgsOrg.roiInputParams.roiType[2],
                                  sizeof(gInArgsOrg.roiInputParams.roiType[2])},

  /*--------------------------------------------------------------------------*/
  /*                                  ROI  4                                  */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"ROI_4_Xmin",&gInArgsOrg.roiInputParams.listROI[3].topLeft.x,
                        sizeof(gInArgsOrg.roiInputParams.listROI[3].topLeft.x)},
  {(XDAS_Int8 *)"ROI_4_Ymin",&gInArgsOrg.roiInputParams.listROI[3].topLeft.y,
                        sizeof(gInArgsOrg.roiInputParams.listROI[3].topLeft.y)},
  {(XDAS_Int8 *)"ROI_4_Xmax",
                            &gInArgsOrg.roiInputParams.listROI[3].bottomRight.x,
                    sizeof(gInArgsOrg.roiInputParams.listROI[3].bottomRight.x)},
  {(XDAS_Int8 *)"ROI_4_Ymax",
                            &gInArgsOrg.roiInputParams.listROI[3].bottomRight.y,
                    sizeof(gInArgsOrg.roiInputParams.listROI[3].bottomRight.y)},
  {(XDAS_Int8 *)"ROI_4_prty",&gInArgsOrg.roiInputParams.roiPriority[3],
                              sizeof(gInArgsOrg.roiInputParams.roiPriority[3])},
  {(XDAS_Int8 *)"ROI_4_type",&gInArgsOrg.roiInputParams.roiType[3],
                                  sizeof(gInArgsOrg.roiInputParams.roiType[3])},

/*--------------------------------------------------------------------------*/
/*                                  ROI  4                                  */
/*--------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_5_Xmin",&gInArgsOrg.roiInputParams.listROI[4].topLeft.x,
                        sizeof(gInArgsOrg.roiInputParams.listROI[4].topLeft.x)},
{(XDAS_Int8 *)"ROI_5_Ymin",&gInArgsOrg.roiInputParams.listROI[4].topLeft.y,
                        sizeof(gInArgsOrg.roiInputParams.listROI[4].topLeft.y)},
{(XDAS_Int8 *)"ROI_5_Xmax",&gInArgsOrg.roiInputParams.listROI[4].bottomRight.x,
                    sizeof(gInArgsOrg.roiInputParams.listROI[4].bottomRight.x)},
{(XDAS_Int8 *)"ROI_5_Ymax",&gInArgsOrg.roiInputParams.listROI[4].bottomRight.y,
                    sizeof(gInArgsOrg.roiInputParams.listROI[4].bottomRight.y)},
{(XDAS_Int8 *)"ROI_5_prty",&gInArgsOrg.roiInputParams.roiPriority[4],
                              sizeof(gInArgsOrg.roiInputParams.roiPriority[4])},
{(XDAS_Int8 *)"ROI_5_type",&gInArgsOrg.roiInputParams.roiType[4],
                                  sizeof(gInArgsOrg.roiInputParams.roiType[4])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  5                                    */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_6_Xmin",&gInArgsOrg.roiInputParams.listROI[5].topLeft.x,
                        sizeof(gInArgsOrg.roiInputParams.listROI[5].topLeft.x)},
{(XDAS_Int8 *)"ROI_6_Ymin",&gInArgsOrg.roiInputParams.listROI[5].topLeft.y,
                        sizeof(gInArgsOrg.roiInputParams.listROI[5].topLeft.y)},
{(XDAS_Int8 *)"ROI_6_Xmax",&gInArgsOrg.roiInputParams.listROI[5].bottomRight.x,
                    sizeof(gInArgsOrg.roiInputParams.listROI[5].bottomRight.x)},
{(XDAS_Int8 *)"ROI_6_Ymax",&gInArgsOrg.roiInputParams.listROI[5].bottomRight.y,
                    sizeof(gInArgsOrg.roiInputParams.listROI[5].bottomRight.y)},
{(XDAS_Int8 *)"ROI_6_prty",&gInArgsOrg.roiInputParams.roiPriority[5],
                              sizeof(gInArgsOrg.roiInputParams.roiPriority[5])},
{(XDAS_Int8 *)"ROI_6_type",&gInArgsOrg.roiInputParams.roiType[5],
                                  sizeof(gInArgsOrg.roiInputParams.roiType[5])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  6                                    */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_7_Xmin",&gInArgsOrg.roiInputParams.listROI[6].topLeft.x,
                        sizeof(gInArgsOrg.roiInputParams.listROI[6].topLeft.x)},
{(XDAS_Int8 *)"ROI_7_Ymin",&gInArgsOrg.roiInputParams.listROI[6].topLeft.y,
                        sizeof(gInArgsOrg.roiInputParams.listROI[6].topLeft.y)},
{(XDAS_Int8 *)"ROI_7_Xmax",&gInArgsOrg.roiInputParams.listROI[6].bottomRight.x,
                    sizeof(gInArgsOrg.roiInputParams.listROI[6].bottomRight.x)},
{(XDAS_Int8 *)"ROI_7_Ymax",&gInArgsOrg.roiInputParams.listROI[6].bottomRight.y,
                    sizeof(gInArgsOrg.roiInputParams.listROI[6].bottomRight.y)},
{(XDAS_Int8 *)"ROI_7_prty",&gInArgsOrg.roiInputParams.roiPriority[6],
                              sizeof(gInArgsOrg.roiInputParams.roiPriority[6])},
{(XDAS_Int8 *)"ROI_7_type",&gInArgsOrg.roiInputParams.roiType[6],
                                  sizeof(gInArgsOrg.roiInputParams.roiType[6])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  7                                    */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_8_Xmin",&gInArgsOrg.roiInputParams.listROI[7].topLeft.x,
                       sizeof(gInArgsOrg.roiInputParams.listROI[7].topLeft.x)},
{(XDAS_Int8 *)"ROI_8_Ymin",&gInArgsOrg.roiInputParams.listROI[7].topLeft.y,
                       sizeof(gInArgsOrg.roiInputParams.listROI[7].topLeft.y)},
{(XDAS_Int8 *)"ROI_8_Xmax",&gInArgsOrg.roiInputParams.listROI[7].bottomRight.x,
                   sizeof(gInArgsOrg.roiInputParams.listROI[7].bottomRight.x)},
{(XDAS_Int8 *)"ROI_8_Ymax",&gInArgsOrg.roiInputParams.listROI[7].bottomRight.y,
                   sizeof(gInArgsOrg.roiInputParams.listROI[7].bottomRight.y)},
{(XDAS_Int8 *)"ROI_8_prty",&gInArgsOrg.roiInputParams.roiPriority[7],
                             sizeof(gInArgsOrg.roiInputParams.roiPriority[7])},
{(XDAS_Int8 *)"ROI_8_type",&gInArgsOrg.roiInputParams.roiType[7],
                                 sizeof(gInArgsOrg.roiInputParams.roiType[7])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  8                                    */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_9_Xmin",&gInArgsOrg.roiInputParams.listROI[8].topLeft.x,
                       sizeof(gInArgsOrg.roiInputParams.listROI[8].topLeft.x)},
{(XDAS_Int8 *)"ROI_9_Ymin",&gInArgsOrg.roiInputParams.listROI[8].topLeft.y,
                       sizeof(gInArgsOrg.roiInputParams.listROI[8].topLeft.y)},
{(XDAS_Int8 *)"ROI_9_Xmax",&gInArgsOrg.roiInputParams.listROI[8].bottomRight.x,
                   sizeof(gInArgsOrg.roiInputParams.listROI[8].bottomRight.x)},
{(XDAS_Int8 *)"ROI_9_Ymax",&gInArgsOrg.roiInputParams.listROI[8].bottomRight.y,
                   sizeof(gInArgsOrg.roiInputParams.listROI[8].bottomRight.y)},
{(XDAS_Int8 *)"ROI_9_prty",&gInArgsOrg.roiInputParams.roiPriority[8],
                             sizeof(gInArgsOrg.roiInputParams.roiPriority[8])},
{(XDAS_Int8 *)"ROI_9_type",&gInArgsOrg.roiInputParams.roiType[8],
                                 sizeof(gInArgsOrg.roiInputParams.roiType[8])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  9                                    */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_10_Xmin",&gInArgsOrg.roiInputParams.listROI[9].topLeft.x,
                       sizeof(gInArgsOrg.roiInputParams.listROI[9].topLeft.x)},
{(XDAS_Int8 *)"ROI_10_Ymin",&gInArgsOrg.roiInputParams.listROI[9].topLeft.y,
                       sizeof(gInArgsOrg.roiInputParams.listROI[9].topLeft.y)},
{(XDAS_Int8 *)"ROI_10_Xmax",&gInArgsOrg.roiInputParams.listROI[9].bottomRight.x,
                   sizeof(gInArgsOrg.roiInputParams.listROI[9].bottomRight.x)},
{(XDAS_Int8 *)"ROI_10_Ymax",&gInArgsOrg.roiInputParams.listROI[9].bottomRight.y,
                   sizeof(gInArgsOrg.roiInputParams.listROI[9].bottomRight.y)},
{(XDAS_Int8 *)"ROI_10_prty",&gInArgsOrg.roiInputParams.roiPriority[9],
                             sizeof(gInArgsOrg.roiInputParams.roiPriority[9])},
{(XDAS_Int8 *)"ROI_10_type",&gInArgsOrg.roiInputParams.roiType[9],
                                 sizeof(gInArgsOrg.roiInputParams.roiType[9])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  10                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_11_Xmin",&gInArgsOrg.roiInputParams.listROI[10].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[10].topLeft.x)},
{(XDAS_Int8 *)"ROI_11_Ymin",&gInArgsOrg.roiInputParams.listROI[10].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[10].topLeft.y)},
{(XDAS_Int8 *)"ROI_11_Xmax",
                           &gInArgsOrg.roiInputParams.listROI[10].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[10].bottomRight.x)},
{(XDAS_Int8 *)"ROI_11_Ymax",
                           &gInArgsOrg.roiInputParams.listROI[10].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[10].bottomRight.y)},
{(XDAS_Int8 *)"ROI_11_prty",&gInArgsOrg.roiInputParams.roiPriority[10],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[10])},
{(XDAS_Int8 *)"ROI_11_type",&gInArgsOrg.roiInputParams.roiType[10],
                                sizeof(gInArgsOrg.roiInputParams.roiType[10])},


/*----------------------------------------------------------------------------*/
/*                                  ROI  11                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_12_Xmin",&gInArgsOrg.roiInputParams.listROI[11].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[11].topLeft.x)},
{(XDAS_Int8 *)"ROI_12_Ymin",&gInArgsOrg.roiInputParams.listROI[11].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[11].topLeft.y)},
{(XDAS_Int8 *)"ROI_12_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[11].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[11].bottomRight.x)},
{(XDAS_Int8 *)"ROI_12_Ymax",
                         &gInArgsOrg.roiInputParams.listROI[11].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[11].bottomRight.y)},
{(XDAS_Int8 *)"ROI_12_prty",&gInArgsOrg.roiInputParams.roiPriority[11],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[11])},
{(XDAS_Int8 *)"ROI_12_type",&gInArgsOrg.roiInputParams.roiType[11],
                                sizeof(gInArgsOrg.roiInputParams.roiType[11])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  12                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_13_Xmin",&gInArgsOrg.roiInputParams.listROI[12].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[12].topLeft.x)},
{(XDAS_Int8 *)"ROI_13_Ymin",&gInArgsOrg.roiInputParams.listROI[12].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[12].topLeft.y)},
{(XDAS_Int8 *)"ROI_13_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[12].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[12].bottomRight.x)},
{(XDAS_Int8 *)"ROI_13_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[12].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[12].bottomRight.y)},
{(XDAS_Int8 *)"ROI_13_prty",&gInArgsOrg.roiInputParams.roiPriority[12],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[12])},
{(XDAS_Int8 *)"ROI_13_type",&gInArgsOrg.roiInputParams.roiType[12],
                                sizeof(gInArgsOrg.roiInputParams.roiType[12])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  13                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_14_Xmin",&gInArgsOrg.roiInputParams.listROI[13].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[13].topLeft.x)},
{(XDAS_Int8 *)"ROI_14_Ymin",&gInArgsOrg.roiInputParams.listROI[13].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[13].topLeft.y)},
{(XDAS_Int8 *)"ROI_14_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[13].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[13].bottomRight.x)},
{(XDAS_Int8 *)"ROI_14_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[13].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[13].bottomRight.y)},
{(XDAS_Int8 *)"ROI_14_prty",&gInArgsOrg.roiInputParams.roiPriority[13],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[13])},
{(XDAS_Int8 *)"ROI_14_type",&gInArgsOrg.roiInputParams.roiType[13],
                                sizeof(gInArgsOrg.roiInputParams.roiType[13])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  14                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_15_Xmin",&gInArgsOrg.roiInputParams.listROI[14].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[14].topLeft.x)},
{(XDAS_Int8 *)"ROI_15_Ymin",&gInArgsOrg.roiInputParams.listROI[14].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[14].topLeft.y)},
{(XDAS_Int8 *)"ROI_15_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[14].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[14].bottomRight.x)},
{(XDAS_Int8 *)"ROI_15_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[14].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[14].bottomRight.y)},
{(XDAS_Int8 *)"ROI_15_prty",&gInArgsOrg.roiInputParams.roiPriority[14],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[14])},
{(XDAS_Int8 *)"ROI_15_type",&gInArgsOrg.roiInputParams.roiType[14],
                                sizeof(gInArgsOrg.roiInputParams.roiType[14])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  15                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_16_Xmin",&gInArgsOrg.roiInputParams.listROI[15].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[15].topLeft.x)},
{(XDAS_Int8 *)"ROI_16_Ymin",&gInArgsOrg.roiInputParams.listROI[15].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[15].topLeft.y)},
{(XDAS_Int8 *)"ROI_16_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[15].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[15].bottomRight.x)},
{(XDAS_Int8 *)"ROI_16_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[15].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[15].bottomRight.y)},
{(XDAS_Int8 *)"ROI_16_prty",&gInArgsOrg.roiInputParams.roiPriority[15],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[15])},
{(XDAS_Int8 *)"ROI_16_type",&gInArgsOrg.roiInputParams.roiType[15],
                                sizeof(gInArgsOrg.roiInputParams.roiType[15])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  16                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_17_Xmin",&gInArgsOrg.roiInputParams.listROI[16].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[16].topLeft.x)},
{(XDAS_Int8 *)"ROI_17_Ymin",&gInArgsOrg.roiInputParams.listROI[16].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[16].topLeft.y)},
{(XDAS_Int8 *)"ROI_17_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[16].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[16].bottomRight.x)},
{(XDAS_Int8 *)"ROI_17_Ymax",
                         &gInArgsOrg.roiInputParams.listROI[16].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[16].bottomRight.y)},
{(XDAS_Int8 *)"ROI_17_prty",&gInArgsOrg.roiInputParams.roiPriority[16],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[16])},
{(XDAS_Int8 *)"ROI_17_type",&gInArgsOrg.roiInputParams.roiType[16],
                                sizeof(gInArgsOrg.roiInputParams.roiType[16])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  17                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_18_Xmin",&gInArgsOrg.roiInputParams.listROI[17].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[17].topLeft.x)},
{(XDAS_Int8 *)"ROI_18_Ymin",&gInArgsOrg.roiInputParams.listROI[17].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[17].topLeft.y)},
{(XDAS_Int8 *)"ROI_18_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[17].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[17].bottomRight.x)},
{(XDAS_Int8 *)"ROI_18_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[17].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[17].bottomRight.y)},
{(XDAS_Int8 *)"ROI_18_prty",&gInArgsOrg.roiInputParams.roiPriority[17],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[17])},
{(XDAS_Int8 *)"ROI_18_type",&gInArgsOrg.roiInputParams.roiType[17],
                                sizeof(gInArgsOrg.roiInputParams.roiType[17])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  18                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_19_Xmin",&gInArgsOrg.roiInputParams.listROI[18].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[18].topLeft.x)},
{(XDAS_Int8 *)"ROI_19_Ymin",&gInArgsOrg.roiInputParams.listROI[18].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[18].topLeft.y)},
{(XDAS_Int8 *)"ROI_19_Xmax",
                    &gInArgsOrg.roiInputParams.listROI[18].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[18].bottomRight.x)},
{(XDAS_Int8 *)"ROI_19_Ymax",
                         &gInArgsOrg.roiInputParams.listROI[18].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[18].bottomRight.y)},
{(XDAS_Int8 *)"ROI_19_prty",&gInArgsOrg.roiInputParams.roiPriority[18],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[18])},
{(XDAS_Int8 *)"ROI_19_type",&gInArgsOrg.roiInputParams.roiType[18],
                                sizeof(gInArgsOrg.roiInputParams.roiType[18])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  19                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_20_Xmin",&gInArgsOrg.roiInputParams.listROI[19].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[19].topLeft.x)},
{(XDAS_Int8 *)"ROI_20_Ymin",&gInArgsOrg.roiInputParams.listROI[19].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[19].topLeft.y)},
{(XDAS_Int8 *)"ROI_20_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[19].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[19].bottomRight.x)},
{(XDAS_Int8 *)"ROI_20_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[19].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[19].bottomRight.y)},
{(XDAS_Int8 *)"ROI_20_prty",&gInArgsOrg.roiInputParams.roiPriority[19],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[19])},
{(XDAS_Int8 *)"ROI_20_type",&gInArgsOrg.roiInputParams.roiType[19],
                                sizeof(gInArgsOrg.roiInputParams.roiType[19])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  20                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_21_Xmin",&gInArgsOrg.roiInputParams.listROI[20].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[20].topLeft.x)},
{(XDAS_Int8 *)"ROI_21_Ymin",&gInArgsOrg.roiInputParams.listROI[20].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[20].topLeft.y)},
{(XDAS_Int8 *)"ROI_21_Xmax",
                   &gInArgsOrg.roiInputParams.listROI[20].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[20].bottomRight.x)},
{(XDAS_Int8 *)"ROI_21_Ymax",
                   &gInArgsOrg.roiInputParams.listROI[20].bottomRight.y,
            sizeof(gInArgsOrg.roiInputParams.listROI[20].bottomRight.y)},
{(XDAS_Int8 *)"ROI_21_prty",&gInArgsOrg.roiInputParams.roiPriority[20],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[20])},
{(XDAS_Int8 *)"ROI_21_type",&gInArgsOrg.roiInputParams.roiType[20],
                                sizeof(gInArgsOrg.roiInputParams.roiType[20])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  21                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_22_Xmin",&gInArgsOrg.roiInputParams.listROI[21].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[21].topLeft.x)},
{(XDAS_Int8 *)"ROI_22_Ymin",&gInArgsOrg.roiInputParams.listROI[21].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[21].topLeft.y)},
{(XDAS_Int8 *)"ROI_22_Xmax",
                    &gInArgsOrg.roiInputParams.listROI[21].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[21].bottomRight.x)},
{(XDAS_Int8 *)"ROI_22_Ymax",
                         &gInArgsOrg.roiInputParams.listROI[21].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[21].bottomRight.y)},
{(XDAS_Int8 *)"ROI_22_prty",&gInArgsOrg.roiInputParams.roiPriority[21],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[21])},
{(XDAS_Int8 *)"ROI_22_type",&gInArgsOrg.roiInputParams.roiType[21],
                                sizeof(gInArgsOrg.roiInputParams.roiType[21])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  22                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_23_Xmin",&gInArgsOrg.roiInputParams.listROI[22].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[22].topLeft.x)},
{(XDAS_Int8 *)"ROI_23_Ymin",&gInArgsOrg.roiInputParams.listROI[22].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[22].topLeft.y)},
{(XDAS_Int8 *)"ROI_23_Xmax",
                    &gInArgsOrg.roiInputParams.listROI[22].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[22].bottomRight.x)},
{(XDAS_Int8 *)"ROI_23_Ymax",
                         &gInArgsOrg.roiInputParams.listROI[22].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[22].bottomRight.y)},
{(XDAS_Int8 *)"ROI_23_prty",&gInArgsOrg.roiInputParams.roiPriority[22],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[22])},
{(XDAS_Int8 *)"ROI_23_type",&gInArgsOrg.roiInputParams.roiType[22],
                                sizeof(gInArgsOrg.roiInputParams.roiType[22])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  23                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_24_Xmin",&gInArgsOrg.roiInputParams.listROI[23].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[23].topLeft.x)},
{(XDAS_Int8 *)"ROI_24_Ymin",&gInArgsOrg.roiInputParams.listROI[23].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[23].topLeft.y)},
{(XDAS_Int8 *)"ROI_24_Xmax",
                    &gInArgsOrg.roiInputParams.listROI[23].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[23].bottomRight.x)},
{(XDAS_Int8 *)"ROI_24_Ymax",
                         &gInArgsOrg.roiInputParams.listROI[23].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[23].bottomRight.y)},
{(XDAS_Int8 *)"ROI_24_prty",&gInArgsOrg.roiInputParams.roiPriority[23],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[23])},
{(XDAS_Int8 *)"ROI_24_type",&gInArgsOrg.roiInputParams.roiType[23],
                                sizeof(gInArgsOrg.roiInputParams.roiType[23])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  24                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_25_Xmin",&gInArgsOrg.roiInputParams.listROI[24].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[24].topLeft.x)},
{(XDAS_Int8 *)"ROI_25_Ymin",&gInArgsOrg.roiInputParams.listROI[24].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[24].topLeft.y)},
{(XDAS_Int8 *)"ROI_25_Xmax",
                    &gInArgsOrg.roiInputParams.listROI[24].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[24].bottomRight.x)},
{(XDAS_Int8 *)"ROI_25_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[24].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[24].bottomRight.y)},
{(XDAS_Int8 *)"ROI_25_prty",&gInArgsOrg.roiInputParams.roiPriority[24],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[24])},
{(XDAS_Int8 *)"ROI_25_type",&gInArgsOrg.roiInputParams.roiType[24],
                                sizeof(gInArgsOrg.roiInputParams.roiType[24])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  25                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_26_Xmin",&gInArgsOrg.roiInputParams.listROI[25].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[25].topLeft.x)},
{(XDAS_Int8 *)"ROI_26_Ymin",&gInArgsOrg.roiInputParams.listROI[25].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[25].topLeft.y)},
{(XDAS_Int8 *)"ROI_26_Xmax",
                    &gInArgsOrg.roiInputParams.listROI[25].bottomRight.x,
            sizeof(gInArgsOrg.roiInputParams.listROI[25].bottomRight.x)},
{(XDAS_Int8 *)"ROI_26_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[25].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[25].bottomRight.y)},
{(XDAS_Int8 *)"ROI_26_prty",&gInArgsOrg.roiInputParams.roiPriority[25],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[25])},
{(XDAS_Int8 *)"ROI_26_type",&gInArgsOrg.roiInputParams.roiType[25],
                                sizeof(gInArgsOrg.roiInputParams.roiType[25])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  26                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_27_Xmin",&gInArgsOrg.roiInputParams.listROI[26].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[26].topLeft.x)},
{(XDAS_Int8 *)"ROI_27_Ymin",&gInArgsOrg.roiInputParams.listROI[26].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[26].topLeft.y)},
{(XDAS_Int8 *)"ROI_27_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[26].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[26].bottomRight.x)},
{(XDAS_Int8 *)"ROI_27_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[26].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[26].bottomRight.y)},
{(XDAS_Int8 *)"ROI_27_prty",&gInArgsOrg.roiInputParams.roiPriority[26],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[26])},
{(XDAS_Int8 *)"ROI_27_type",&gInArgsOrg.roiInputParams.roiType[26],
                                sizeof(gInArgsOrg.roiInputParams.roiType[26])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  27                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_28_Xmin",&gInArgsOrg.roiInputParams.listROI[27].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[27].topLeft.x)},
{(XDAS_Int8 *)"ROI_28_Ymin",&gInArgsOrg.roiInputParams.listROI[27].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[27].topLeft.y)},
{(XDAS_Int8 *)"ROI_28_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[27].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[27].bottomRight.x)},
{(XDAS_Int8 *)"ROI_28_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[27].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[27].bottomRight.y)},
{(XDAS_Int8 *)"ROI_28_prty",&gInArgsOrg.roiInputParams.roiPriority[27],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[27])},
{(XDAS_Int8 *)"ROI_28_type",&gInArgsOrg.roiInputParams.roiType[27],
                                sizeof(gInArgsOrg.roiInputParams.roiType[27])},


/*----------------------------------------------------------------------------*/
/*                                  ROI  28                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_29_Xmin",&gInArgsOrg.roiInputParams.listROI[28].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[28].topLeft.x)},
{(XDAS_Int8 *)"ROI_29_Ymin",&gInArgsOrg.roiInputParams.listROI[28].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[28].topLeft.y)},
{(XDAS_Int8 *)"ROI_29_Xmax", 
                          &gInArgsOrg.roiInputParams.listROI[28].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[28].bottomRight.x)},
{(XDAS_Int8 *)"ROI_29_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[28].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[28].bottomRight.y)},
{(XDAS_Int8 *)"ROI_29_prty",&gInArgsOrg.roiInputParams.roiPriority[28],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[28])},
{(XDAS_Int8 *)"ROI_29_type",&gInArgsOrg.roiInputParams.roiType[28],
                                sizeof(gInArgsOrg.roiInputParams.roiType[28])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  29                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_30_Xmin",&gInArgsOrg.roiInputParams.listROI[29].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[29].topLeft.x)},
{(XDAS_Int8 *)"ROI_30_Ymin",&gInArgsOrg.roiInputParams.listROI[29].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[29].topLeft.y)},
{(XDAS_Int8 *)"ROI_30_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[29].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[29].bottomRight.x)},
{(XDAS_Int8 *)"ROI_30_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[29].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[29].bottomRight.y)},
{(XDAS_Int8 *)"ROI_30_prty",&gInArgsOrg.roiInputParams.roiPriority[29],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[29])},
{(XDAS_Int8 *)"ROI_30_type",&gInArgsOrg.roiInputParams.roiType[29],
                                sizeof(gInArgsOrg.roiInputParams.roiType[29])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  30                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_31_Xmin",&gInArgsOrg.roiInputParams.listROI[30].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[30].topLeft.x)},
{(XDAS_Int8 *)"ROI_31_Ymin",&gInArgsOrg.roiInputParams.listROI[30].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[30].topLeft.y)},
{(XDAS_Int8 *)"ROI_31_Xmax",
                         &gInArgsOrg.roiInputParams.listROI[30].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[30].bottomRight.x)},
{(XDAS_Int8 *)"ROI_31_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[30].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[30].bottomRight.y)},
{(XDAS_Int8 *)"ROI_31_prty",&gInArgsOrg.roiInputParams.roiPriority[30],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[30])},
{(XDAS_Int8 *)"ROI_31_type",&gInArgsOrg.roiInputParams.roiType[30],
                                sizeof(gInArgsOrg.roiInputParams.roiType[30])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  31                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_32_Xmin",&gInArgsOrg.roiInputParams.listROI[31].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[31].topLeft.x)},
{(XDAS_Int8 *)"ROI_32_Ymin",&gInArgsOrg.roiInputParams.listROI[31].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[31].topLeft.y)},
{(XDAS_Int8 *)"ROI_32_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[31].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[31].bottomRight.x)},
{(XDAS_Int8 *)"ROI_32_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[31].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[31].bottomRight.y)},
{(XDAS_Int8 *)"ROI_32_prty",&gInArgsOrg.roiInputParams.roiPriority[31],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[31])},
{(XDAS_Int8 *)"ROI_32_type",&gInArgsOrg.roiInputParams.roiType[31],
                                sizeof(gInArgsOrg.roiInputParams.roiType[31])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  32                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_33_Xmin",&gInArgsOrg.roiInputParams.listROI[32].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[32].topLeft.x)},
{(XDAS_Int8 *)"ROI_33_Ymin",&gInArgsOrg.roiInputParams.listROI[32].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[32].topLeft.y)},
{(XDAS_Int8 *)"ROI_33_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[32].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[32].bottomRight.x)},
{(XDAS_Int8 *)"ROI_33_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[32].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[32].bottomRight.y)},
{(XDAS_Int8 *)"ROI_33_prty",&gInArgsOrg.roiInputParams.roiPriority[32],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[32])},
{(XDAS_Int8 *)"ROI_33_type",&gInArgsOrg.roiInputParams.roiType[32],
                                sizeof(gInArgsOrg.roiInputParams.roiType[32])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  33                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_34_Xmin",&gInArgsOrg.roiInputParams.listROI[33].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[33].topLeft.x)},
{(XDAS_Int8 *)"ROI_34_Ymin",&gInArgsOrg.roiInputParams.listROI[33].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[33].topLeft.y)},
{(XDAS_Int8 *)"ROI_34_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[33].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[33].bottomRight.x)},
{(XDAS_Int8 *)"ROI_34_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[33].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[33].bottomRight.y)},
{(XDAS_Int8 *)"ROI_34_prty",&gInArgsOrg.roiInputParams.roiPriority[33],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[33])},
{(XDAS_Int8 *)"ROI_34_type",&gInArgsOrg.roiInputParams.roiType[33],
                                sizeof(gInArgsOrg.roiInputParams.roiType[33])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  34                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_35_Xmin",&gInArgsOrg.roiInputParams.listROI[34].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[34].topLeft.x)},
{(XDAS_Int8 *)"ROI_35_Ymin",&gInArgsOrg.roiInputParams.listROI[34].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[34].topLeft.y)},
{(XDAS_Int8 *)"ROI_35_Xmax",
                         &gInArgsOrg.roiInputParams.listROI[34].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[34].bottomRight.x)},
{(XDAS_Int8 *)"ROI_35_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[34].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[34].bottomRight.y)},
{(XDAS_Int8 *)"ROI_35_prty",&gInArgsOrg.roiInputParams.roiPriority[34],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[34])},
{(XDAS_Int8 *)"ROI_35_type",&gInArgsOrg.roiInputParams.roiType[34],
                                sizeof(gInArgsOrg.roiInputParams.roiType[34])},

/*----------------------------------------------------------------------------*/
/*                                  ROI  35                                   */
/*----------------------------------------------------------------------------*/
{(XDAS_Int8 *)"ROI_36_Xmin",&gInArgsOrg.roiInputParams.listROI[35].topLeft.x,
                      sizeof(gInArgsOrg.roiInputParams.listROI[35].topLeft.x)},
{(XDAS_Int8 *)"ROI_36_Ymin",&gInArgsOrg.roiInputParams.listROI[35].topLeft.y,
                      sizeof(gInArgsOrg.roiInputParams.listROI[35].topLeft.y)},
{(XDAS_Int8 *)"ROI_36_Xmax",
                          &gInArgsOrg.roiInputParams.listROI[35].bottomRight.x,
                  sizeof(gInArgsOrg.roiInputParams.listROI[35].bottomRight.x)},
{(XDAS_Int8 *)"ROI_36_Ymax",
                          &gInArgsOrg.roiInputParams.listROI[35].bottomRight.y,
                  sizeof(gInArgsOrg.roiInputParams.listROI[35].bottomRight.y)},
{(XDAS_Int8 *)"ROI_36_prty",&gInArgsOrg.roiInputParams.roiPriority[35],
                            sizeof(gInArgsOrg.roiInputParams.roiPriority[35])},
{(XDAS_Int8 *)"ROI_36_type",&gInArgsOrg.roiInputParams.roiType[35],
                                sizeof(gInArgsOrg.roiInputParams.roiType[35])},
                                    
                
                
  {(XDAS_Int8 *)"VBRDuration",&gParamsOrg.rateControlParams.VBRDuration,
                          sizeof(gParamsOrg.rateControlParams.VBRDuration)},

  {(XDAS_Int8 *)"VBRsensitivity",&gParamsOrg.rateControlParams.VBRsensitivity,
                          sizeof(gParamsOrg.rateControlParams.VBRsensitivity)},

  {(XDAS_Int8 *)"skipDistributionWindowLength",
                &gParamsOrg.rateControlParams.skipDistributionWindowLength,
            sizeof(gParamsOrg.rateControlParams.skipDistributionWindowLength)},

  {(XDAS_Int8 *)"numSkipInDistributionWindow",
                 &gParamsOrg.rateControlParams.numSkipInDistributionWindow,
             sizeof(gParamsOrg.rateControlParams.numSkipInDistributionWindow)},
  {(XDAS_Int8 *)"enableHRDComplianceMode",
                          &gParamsOrg.rateControlParams.enableHRDComplianceMode,
                  sizeof(gParamsOrg.rateControlParams.enableHRDComplianceMode)},
  /*--------------------------------------------------------------------------*/
  /* ALWAYS the last element in the map                                       */
  /*--------------------------------------------------------------------------*/
  {(XDAS_Int8 *)"\0",NULL,0}
};

/**
********************************************************************************
 *  @fn     H264ENC_TI_Scratch_Contaminate
 *  @brief  This function will currupt scratch data in IVAHD buffers
 *
 *          This function will currupt DTCM and other SL2 memory. This function
 *          does not contaminate const and stack area of ICONTs
 *          NOTE: Here the addresses depend on ICONT memory map, so when ever
 *          we change ICONT command file we need to change the hot
 *          coded address
 *
 *
 *  @return     None
********************************************************************************
*/

void H264ENC_TI_Scratch_Contaminate(XDAS_Int32 hdvicp_status)
{
#ifdef SCRATCH_CONTAMINATE
   XDAS_Int32 sl2StructSize                          ;
   XDAS_Int32 channelInfoStructSize                  ;
   XDAS_Int8 isHiMP                                  ;
   XDAS_Int8 pattren[5] = {0x55,0x66,0xAA,0x99, 0xFF};
   static XDAS_Int8 index = 0                        ;

   /*-------------------------------------------------------------------------*/
   /* Check whether the code flow is for HighMega pixel or LowMega pixel      */
   /*-------------------------------------------------------------------------*/
   isHiMP = (gParamsOrg.videnc2Params.maxWidth > 2048 || 
            gParamsOrg.videnc2Params.maxHeight > 2048 || \
            (gParamsOrg.videnc2Params.inputContentType && 
            gParamsOrg.videnc2Params.maxHeight > 1024) ||
            ((gParamsOrg.videnc2Params.encodingPreset == XDM_USER_DEFINED )&&
            (((gParamsOrg.interCodingParams.interCodingPreset == 1) &&
            ((gParamsOrg.interCodingParams.searchRangeVerP > 32)||
             (gParamsOrg.interCodingParams.searchRangeVerB > 16)))))) ;

  /*--------------------------------------------------------------------------*/
  /* Contaminate the total IVAHD module memory when FULL_CONTAMINATE flag is  */
  /* flag is enabled. Here the resource mode ID must be DIFFERENTCODEC so that*/
  /* every process call will update entire IVAHD persistant memorys           */
  /*--------------------------------------------------------------------------*/
  if(hdvicp_status == 2)
  {
    /*------------------------------------------------------------------------*/
    /* Currupt SL2 memory, it is of 256 KB                                    */
    /*------------------------------------------------------------------------*/
    memset ((Void*)(MEM_BASE), pattren[index], 256*1024);
    /*------------------------------------------------------------------------*/
    /* Currupt DTCM of both ICONTs                                            */
    /*------------------------------------------------------------------------*/
    memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET), pattren[index],
                                                                     16 * 1024);
    memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET), pattren[index],
                                                                     16 * 1024);
    /*------------------------------------------------------------------------*/
    /* Currupt ITCM of both ICONTs                                            */
    /*------------------------------------------------------------------------*/
    memset ((Void*)(REG_BASE + ICONT1_ITCM_OFFSET), pattren[index],
                                                                     32 * 1024);
    memset ((Void*)(REG_BASE + ICONT2_ITCM_OFFSET), pattren[index],
                                                                     32 * 1024);
  }

  /*--------------------------------------------------------------------------*/
  /* Contamination area for HiMp and LowMp are different. So contaminte the   */
  /* memory according to the code flow   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /*--------------------------------------------------------------------------*/
  if(isHiMP)
  {
     sl2StructSize =  SIZEOF_SSL2INFO_HIMP_T   ;
     channelInfoStructSize = SIZEOF_CHANNELINFO;

     sl2StructSize = (sl2StructSize + 0xF) & 0xFFFFFFF0;
     channelInfoStructSize = (channelInfoStructSize + 0xF) & 0xFFFFFFF0;
     
    /*------------------------------------------------------------------------*/
    /* contamination for SAMECODEC         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*------------------------------------------------------------------------*/
    if(hdvicp_status == 0)
    {
      /*----------------------------------------------------------------------*/
      /*If resource mode is not DIFFERENTCODEC currupt only part of DTCM all  */
      /*others being persistant memorys.                                      */
      /*Please note that we can do selective part of SL2 memory curruption, as*/
      /*now we are not doing that                                             */
      /*----------------------------------------------------------------------*/
      /*----------------------------------------------------------------------*/
      /*   DTCM1_SHARED section in ICONT1 DTCM                                */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET),
                                                  pattren[index], 0x000002700);
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x2700),
                                                  pattren[index], 0x00000550);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x2C90),
                                                  pattren[index], 0x100);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT2_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0xAE0),
                                                  pattren[index], 0x00000A3C);
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0x1560),
                                                  pattren[index], 0x000000A0);
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0x25F0),
                                                  pattren[index], 0x000005D0);
  
      /*----------------------------------------------------------------------*/
      /*Below contamination is based on the flag ADDRS_LAST_CH_CODECPARAMS_SL2*/
      /*change in value of that flag will require below contamination to be   */
      /*changed                                                               */
      /*----------------------------------------------------------------------*/
  
      /*----------------------------------------------------------------------*/
      /* Below number 250936 is size of SL2 data structure                    */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(MEM_BASE), pattren[index], sl2StructSize);
      memset ((Void*)((char*)MEM_BASE + sl2StructSize + channelInfoStructSize),
                                                                pattren[index], 
      (ADDRS_LAST_CH_CODECPARAMS_SL2 -  sl2StructSize - channelInfoStructSize));
      if((prevProcessCallNumChannel > 0x1) || (currProcessCallNumChannel > 0x1))
      {
        memset ((Void*)((char*)MEM_BASE + sl2StructSize), pattren[index],
                                                         channelInfoStructSize);
      }
      if(currProcessCallNumChannel > 0x1)
      {
        memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET),
                                        pattren[index], 0xAE0);
      }
    }
    /*------------------------------------------------------------------------*/
    /* When the resource mode is samecodectype we can currupt total SL2 memory*/
    /*------------------------------------------------------------------------*/
    if(hdvicp_status == 1)
    {
      /*----------------------------------------------------------------------*/
      /*If resource mode is not DIFFERENTCODEC currupt only part of DTCM all  */
      /*others being persistant memorys.                                      */
      /*Please note that we can do selective part of SL2 memory curruption, as*/
      /*now we are not doing that                                             */
      /*----------------------------------------------------------------------*/
      /*----------------------------------------------------------------------*/
      /*   DTCM1_SHARED section in ICONT1 DTCM                                */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET),
                                                  pattren[index], 0x000002700);
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x2700),
                                                  pattren[index], 0x00000550);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x2C90),
                                                  pattren[index], 0x100);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT2_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0xAE0),
                                                  pattren[index], 0x00000A3C);
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0x1560),
                                                  pattren[index], 0x000000A0);
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0x25F0),
                                                  pattren[index], 0x000005D0);
  
      /*----------------------------------------------------------------------*/
      /*Below contamination is based on the flag ADDRS_LAST_CH_CODECPARAMS_SL2*/
      /*change in value of that flag will require below contamination to be   */
      /*changed                                                               */
      /*----------------------------------------------------------------------*/
  
      /*----------------------------------------------------------------------*/
      /* Below number 250936 is size of SL2 data structure                    */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(MEM_BASE), pattren[index], ADDRS_LAST_CH_CODECPARAMS_SL2);
    }
  }
  else
  {
     sl2StructSize =  SIZEOF_SSL2INFO_T        ;
     channelInfoStructSize = SIZEOF_CHANNELINFO;
     
     sl2StructSize = (sl2StructSize + 0xF) & 0xFFFFFFF0;
     channelInfoStructSize = (channelInfoStructSize + 0xF) & 0xFFFFFFF0;
     
    /*------------------------------------------------------------------------*/
    /* contamination for SAMECODEC         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    /*------------------------------------------------------------------------*/
    if(hdvicp_status == 0)
    {
      /*----------------------------------------------------------------------*/
      /*If resource mode is not DIFFERENTCODEC currupt only part of DTCM all  */
      /*others being persistant memorys.                                      */
      /*Please note that we can do selective part of SL2 memory curruption, as*/
      /*now we are not doing that                                             */
      /*----------------------------------------------------------------------*/
      /*----------------------------------------------------------------------*/
      /*   DTCM1_SHARED section in ICONT1 DTCM                                */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET),
                                                  pattren[index], 0x0000013D0);
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x13D0),
                                                  pattren[index], 0x00001780);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x2b90),
                                                  pattren[index], 0x1E0);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT2_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0xAE0),
                                                  pattren[index], 0x00000A90);
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0x2590),
                                                  pattren[index], 0x000005C0);
  
      /*----------------------------------------------------------------------*/
      /*Below contamination is based on the flag ADDRS_LAST_CH_CODECPARAMS_SL2*/
      /*change in value of that flag will require below contamination to be   */
      /*changed                                                               */
      /*----------------------------------------------------------------------*/
  
      /*----------------------------------------------------------------------*/
      /* Below number 250936 is size of SL2 data structure                    */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(MEM_BASE), pattren[index], sl2StructSize);
      memset ((Void*)((char*)MEM_BASE + sl2StructSize + channelInfoStructSize),
                                                                pattren[index], 
      (ADDRS_LAST_CH_CODECPARAMS_SL2 -  sl2StructSize - channelInfoStructSize));
      if((prevProcessCallNumChannel > 0x1) || (currProcessCallNumChannel > 0x1))
      {
        memset ((Void*)((char*)MEM_BASE + sl2StructSize), pattren[index], 
                                                         channelInfoStructSize);
      }
      if(currProcessCallNumChannel > 0x1)
      {
        memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET),
                                        pattren[index], 0xAE0);
      }
    }
    /*------------------------------------------------------------------------*/
    /* When the resource mode is samecodectype we can currupt total SL2 memory*/
    /*------------------------------------------------------------------------*/
    if(hdvicp_status == 1)
    {
      /*----------------------------------------------------------------------*/
      /*If resource mode is not DIFFERENTCODEC currupt only part of DTCM all  */
      /*others being persistant memorys.                                      */
      /*Please note that we can do selective part of SL2 memory curruption, as*/
      /*now we are not doing that                                             */
      /*----------------------------------------------------------------------*/
      /*----------------------------------------------------------------------*/
      /*   DTCM1_SHARED section in ICONT1 DTCM                                */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET),
                                                  pattren[index], 0x0000013D0);
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x13D0),
                                                  pattren[index], 0x00001780);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT1_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT1_DTCM_OFFSET + 0x2b90),
                                                  pattren[index], 0x1E0);
  
      /*----------------------------------------------------------------------*/
      /*    DTCM section in ICONT2_DTCM                                       */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0xAE0),
                                                  pattren[index], 0x00000A90);
      memset ((Void*)(REG_BASE + ICONT2_DTCM_OFFSET + 0x2590),
                                                  pattren[index], 0x000005C0);
  
      /*----------------------------------------------------------------------*/
      /*Below contamination is based on the flag ADDRS_LAST_CH_CODECPARAMS_SL2*/
      /*change in value of that flag will require below contamination to be   */
      /*changed                                                               */
      /*----------------------------------------------------------------------*/
  
      /*----------------------------------------------------------------------*/
      /* Below number 250936 is size of SL2 data structure                    */
      /*----------------------------------------------------------------------*/
      memset ((Void*)(MEM_BASE), pattren[index], ADDRS_LAST_CH_CODECPARAMS_SL2);
    }
   }
 index++ ;
 if(index == 5)
 {
   index = 0;
 }
#endif
}
/**
********************************************************************************
 *  @fn     H264ENC_TI_Init_Log
 *  @brief  This function will initialize status printing module
 *
 *          This function, this prints log like number of frames encoded,
 *          bits consumed, cycles consumed etc
 *
 *  @param[in]  fTrace_file : File pointer to the trace log file
 *
 *  @return     XDM_EOK -  when there is no fatal error
 *              XDM_EFAIL - when it is fatal error
********************************************************************************
*/

XDAS_Int32 H264ENC_TI_Init_Log(FILE * fTrace_file)
{
  /*--------------------------------------------------------------------------*/
  /* Initialize the parameters                                                */
  /*--------------------------------------------------------------------------*/
  gLogMessge.uiEncodeStart = 0;
  gLogMessge.uiEncodeEnd   = 0;

  profileTimeStamps.processStartTimeStamp[0] =
    profileTimeStamps.processStartTimeStamp[1] = 0;
  profileTimeStamps.processEndTimeStamp[0] =
    profileTimeStamps.processEndTimeStamp[1] = 0;
  profileTimeStamps.hdvicpWaitTimeStamp[0] =
    profileTimeStamps.hdvicpWaitTimeStamp[1] = 0;
  profileTimeStamps.hdvicpAcquireTimeStamp[0] =
    profileTimeStamps.hdvicpAcquireTimeStamp[1] = 0;
  profileTimeStamps.hdvicpDoneTimeStamp[0] =
    profileTimeStamps.hdvicpDoneTimeStamp[1] = 0;
  profileTimeStamps.hdvicpReleaseTimeStamp[0] =
    profileTimeStamps.hdvicpReleaseTimeStamp[1] = 0;

#ifdef GENERATE_PROFILE_NUMBER
  /*--------------------------------------------------------------------------*/
  /* Enable and Initialise the ICE CRUSHER TIMER                              */
  /*--------------------------------------------------------------------------*/
  /* while(ICEC_CNT_CTRL != 0x40000000)                                       */
    ICEC_CNT_CTRL = 0x40000000;
    ICEC_CNT_CTRL = 0x40000000;
    ICEC_CNT_CTRL = 0x40000000;
    ICEC_CNT_CTRL = 0x40000000;
    /*------------------------------------------------------------------------*/
    /* Enable Resource                                                        */
    /*------------------------------------------------------------------------*/
     ICEC_CNT_CTRL = 0x80000000;
     ICEC_CNT_CTRL = 0x80000000 |  (1<<19) | (1<<16) ;
     ICEC_CNT_CTRL = 0x80000000 |  (1<<19) | (1<<16) | (1<<12);
#endif
#ifdef PROFILE_M3
  SYSTICKREG = 0x4;
  SYSTICKREL = SYSTICKRELVAL;
  SYSTICKREG = 0x5;
#endif
  return XDM_EOK;
}

/**
********************************************************************************
 *  @fn     H264ENC_TI_Capture_time
 *  @brief  This function will capture time instance
 *
 *          This function captures time and updates start or end time in log
 *          instance,
 *
 *  @param[in]  uiCapturePoint : tells start time or end time
 *                               0 - start time
 *                               1 - end time
 *
 *  @return     none
********************************************************************************
*/

void H264ENC_TI_Capture_time(XDAS_Int32 uiCapturePoint)
{
  XDAS_UInt32 startTime;
  XDAS_UInt32 idx = numFramesEncoded[0] % NO_OF_PROFILE_INSTANCES;

  sProfileCycles *profileCycles =
  (sProfileCycles *)&profileData.profileCycles[idx];

  switch(uiCapturePoint)
  {
    case PROCESS_START:
  {
      profileTimeStamps.processStartTimeStamp[0] = ICEC_CNT_VAL;
      profileTimeStamps.processStartTimeStamp[1] = SYSTICKVAL;
  }
    break;


    case HDVICP_ACQUIRE:
    {
      profileTimeStamps.hdvicpAcquireTimeStamp[0] = ICEC_CNT_VAL;
      profileTimeStamps.hdvicpAcquireTimeStamp[1] = SYSTICKVAL;

      startTime = profileTimeStamps.processStartTimeStamp[1];

      if((XDAS_Int32)(startTime - 
                  profileTimeStamps.hdvicpAcquireTimeStamp[1])< 0)
  {
        startTime += SYSTICKRELVAL;
  }
      profileCycles->procStart_hdvicpAcquire[1] =
      startTime - profileTimeStamps.hdvicpAcquireTimeStamp[1];
      profileCycles->procStart_hdvicpAcquire[0] =
      profileTimeStamps.hdvicpAcquireTimeStamp[0] -
        profileTimeStamps.processStartTimeStamp[0];
    }
    break;

    case HDVICP_WAIT:
    {
      profileTimeStamps.hdvicpWaitTimeStamp[0] = ICEC_CNT_VAL;
      profileTimeStamps.hdvicpWaitTimeStamp[1] = SYSTICKVAL;

      startTime = profileTimeStamps.hdvicpAcquireTimeStamp[1];

      if((XDAS_Int32)(startTime - profileTimeStamps.hdvicpWaitTimeStamp[1]) < 0)
  {
        startTime += SYSTICKRELVAL;
      }
      profileCycles->hdvicpAcquire_hdvicpWait[1] =
      startTime - profileTimeStamps.hdvicpWaitTimeStamp[1];
      profileCycles->hdvicpAcquire_hdvicpWait[0] =
      profileTimeStamps.hdvicpWaitTimeStamp[0] -
      profileTimeStamps.hdvicpAcquireTimeStamp[0];
  }
    break;

    case HDVICP_DONE:

      profileTimeStamps.hdvicpDoneTimeStamp[0] = ICEC_CNT_VAL;
      profileTimeStamps.hdvicpDoneTimeStamp[1] = SYSTICKVAL;

      startTime = profileTimeStamps.hdvicpWaitTimeStamp[1];

      if((XDAS_Int32)(startTime - profileTimeStamps.hdvicpDoneTimeStamp[1]) < 0)
      {
         startTime += SYSTICKRELVAL;
      }
      profileCycles->hdvicpWait_hdvicpDone[1] =
      startTime - profileTimeStamps.hdvicpDoneTimeStamp[1];
      profileCycles->hdvicpWait_hdvicpDone[0] =
      profileTimeStamps.hdvicpDoneTimeStamp[0] -
        profileTimeStamps.hdvicpWaitTimeStamp[0];
    break;
    case HDVICP_RELEASE:
  {
      profileTimeStamps.hdvicpReleaseTimeStamp[0] = ICEC_CNT_VAL;
      profileTimeStamps.hdvicpReleaseTimeStamp[1] = SYSTICKVAL;

      startTime = profileTimeStamps.hdvicpDoneTimeStamp[1];

      if((XDAS_Int32)(startTime - 
             profileTimeStamps.hdvicpReleaseTimeStamp[1])< 0)
    {
      startTime += SYSTICKRELVAL;
    }
      profileCycles->hdvicpDone_hdvicpRelease[1] =
      startTime - profileTimeStamps.hdvicpReleaseTimeStamp[1];
      profileCycles->hdvicpDone_hdvicpRelease[0] =
      profileTimeStamps.hdvicpReleaseTimeStamp[0] -
        profileTimeStamps.hdvicpDoneTimeStamp[0];
  }
    break;

    case PROCESS_END:
  {
      profileTimeStamps.processEndTimeStamp[0] = ICEC_CNT_VAL;
      profileTimeStamps.processEndTimeStamp[1] = SYSTICKVAL;

      startTime = profileTimeStamps.hdvicpReleaseTimeStamp[1];

      if((XDAS_Int32)(startTime - profileTimeStamps.processEndTimeStamp[1]) < 0)
      {
      startTime += SYSTICKRELVAL;
      }
      profileCycles->hdvicpRelease_procEnd[1] =
      startTime - profileTimeStamps.processEndTimeStamp[1];
      profileCycles->hdvicpRelease_procEnd[0] =
      profileTimeStamps.processEndTimeStamp[0] -
        profileTimeStamps.hdvicpReleaseTimeStamp[0];
    }
    break;
  }
}

/**
********************************************************************************
 *  @fn     H264ENC_TI_Print_Log
 *  @brief  This function will print log encoding of the frame
 *          It will print frame type, number of frames encoded, number of bytes
 *          bytes generated for each field, and cycles consumed for each file

 *  @param[in]  fTrace_file : File pointer to the trace log file
 *
 *  @return     XDM_EOK -  when there is no fatal error
 *              XDM_EFAIL - when it is fatal error
********************************************************************************
*/

XDAS_Int32 H264ENC_TI_Print_Log(FILE * fTrace_file,XDAS_Int32 siFrameType,
                                XDAS_Int32 siContentType,
                                XDAS_Int32 siBytesGenerated,
                                XDAS_Int32 siBytesGeneratedBotField,
                                XDAS_Int32 siNumFramesEncoded)
{
  XDAS_UInt32 m3PreCycles , m3PostCycles, iVACycles, m3Cycles ;
  XDAS_UInt32 idx = numFramesEncoded[0] % NO_OF_PROFILE_INSTANCES;
  sProfileCycles *profileCycles =
  (sProfileCycles *)&profileData.profileCycles[idx];

  /*--------------------------------------------------------------------------*/
  /* Encoded frame number                                                     */
  /*--------------------------------------------------------------------------*/
  printf(" #%-5d", (siNumFramesEncoded));
  fprintf(fTrace_file, "\n #%-5d", (siNumFramesEncoded));
  /*--------------------------------------------------------------------------*/
  /* Encoded frame type                                                       */
  /*--------------------------------------------------------------------------*/
  printf(": %-20s ",pFrameType[siFrameType + 1]);
  fprintf(fTrace_file,": %-20s ",
                   pFrameType[siFrameType + 1]);
  /*--------------------------------------------------------------------------*/
  /* Print Total number of bits generated                                     */
  /*--------------------------------------------------------------------------*/
  printf(" : Bits  : %-10d", (siBytesGenerated * 8));
  fprintf(fTrace_file, " : Bits  : %-10d", (siBytesGenerated * 8));
  /*--------------------------------------------------------------------------*/
  /* In case of Interlaced content print bits generated for each field        */
  /*--------------------------------------------------------------------------*/
  if(siContentType == 1)
  {
    printf(" : Bits Feild0: %-10d",(siBytesGenerated * 8) - \
                                              (siBytesGeneratedBotField * 8));
    fprintf(fTrace_file," : Bits Feild0: %-10d",(siBytesGenerated * 8) - \
                                              (siBytesGeneratedBotField * 8));
    printf(" : Bits Feild1: %-10d", (siBytesGeneratedBotField * 8));
    fprintf(fTrace_file," : Bits Feild1: %-10d",(siBytesGeneratedBotField * 8));
  }
  /*--------------------------------------------------------------------------*/
  /* Print the bit rate for this frame                                        */
  /*--------------------------------------------------------------------------*/
  printf(" : %2.2f Mbps", \
        ((((siBytesGenerated) * 8) * 30)/1000000.0));
  fprintf(fTrace_file, " : %2.2f Mbps", \
        ((((siBytesGenerated) * 8) * 30)/1000000.0));

  /* Below all cycles are in M3 clock */
  m3PreCycles  = profileCycles->procStart_hdvicpAcquire[1] +
                 profileCycles->hdvicpAcquire_hdvicpWait[1] ;
  m3PostCycles = profileCycles->hdvicpDone_hdvicpRelease[1] +
                 profileCycles->hdvicpRelease_procEnd[1]  ;

  m3Cycles     = m3PreCycles + m3PostCycles ;
  iVACycles    = profileCycles->hdvicpAcquire_hdvicpWait[1] +
                 profileCycles->hdvicpWait_hdvicpDone[1] +
                 profileCycles->hdvicpDone_hdvicpRelease[1] ;

  /* Print of M3 MHZ in M3 unit and IVA in IVA unit */
  printf(":M3 Usage: %-9d , %3.2f MHz(M3), IVA Usage : %3.2f MHz(IVA)",
           m3Cycles, ((m3Cycles*30.0)/1000000), (iVACycles*30*IVAHD_MHZ/M3_HZ));

  fprintf(fTrace_file,
                ":M3 Usage: %-9d , %3.2f MHz(M3), IVA Usage : %3.2f MHz(IVA)",
           m3Cycles, ((m3Cycles*30.0)/1000000), (iVACycles*30*IVAHD_MHZ/M3_HZ));

#ifdef GENERATE_PROFILE_NUMBER
{
  XDAS_UInt32 uiTotalCycles;
  XDAS_UInt32 M3Cycles;
  XDAS_UInt32 PicLevelCycles;
  XDAS_UInt32 PicInitCycles;

  XDAS_UInt32 uiField0Cycles;
  XDAS_UInt32 uiField1Cycles;
  uiTotalCycles = profileTimeStamps.processEndTimeStamp[0] -
                                  profileTimeStamps.processStartTimeStamp[0];
  printf(" : Total: %3d MHz", (((uiTotalCycles)*30)/1000000));
  fprintf(fTrace_file, " : Total: %3d MHz",(((uiTotalCycles)*30)/1000000));

  PicLevelCycles = profileTimeStamps.hdvicpDoneTimeStamp[0] -
                                  profileTimeStamps.hdvicpWaitTimeStamp[0];

  M3Cycles = uiTotalCycles - PicLevelCycles;
  printf(" : M3: %3d MHz", (((M3Cycles)*30)/1000000));
  fprintf(fTrace_file, " : M3: %3d MHz",(((M3Cycles)*30)/1000000));
  /*--------------------------------------------------------------------------*/
  /* Print MB total MB loop cycles here                                       */
  /* MB loop cycles are stored in last 16 bites of SL2 memory                 */
  /*--------------------------------------------------------------------------*/
  uiField0Cycles = MB_LOOP_FIELD_0;
  uiField1Cycles = MB_LOOP_FIELD_1;
  if(siContentType == 1)
  {
    PicInitCycles = PicLevelCycles - uiField0Cycles - uiField1Cycles;
    printf(" : PicInit: %3d MHz(%3d Cycles)", (((PicInitCycles)*30)/1000000),
                                                                 PicInitCycles);
    fprintf(fTrace_file, " : PicInit: %3d MHz(%3d Cycles)",
                                 (((PicInitCycles)*30)/1000000), PicInitCycles);

    printf(" : MB Loop Field 0: %3d MHz", 
                             (((uiField0Cycles)*30)/1000000),uiField0Cycles );
    fprintf(fTrace_file, " : MB Loop Field 0: %3d MHz (%3d Cycles)",
                              (((uiField0Cycles)*30)/1000000), uiField0Cycles);
    printf(" : MB Loop Field 1: %3d MHz (%3d Cycles)",
                               (((uiField1Cycles)*30)/1000000), uiField1Cycles);
    fprintf(fTrace_file, " : MB Loop Field 1: %3d MHz (%3d Cycles)",
                              (((uiField1Cycles)*30)/1000000), uiField1Cycles);
  }
  else
  {
    PicInitCycles = PicLevelCycles - uiField0Cycles;
    printf(" : PicInit: %3d MHz(%3d Cycles)", (((PicInitCycles)*30)/1000000),
                                                                 PicInitCycles);
    fprintf(fTrace_file, " : PicInit: %3d MHz(%3d Cycles)",
                                 (((PicInitCycles)*30)/1000000), PicInitCycles);

    printf(" : MB Loop Field 1: %3d MHz (%3d Cycles)",
                               (((uiField0Cycles)*30)/1000000), uiField0Cycles);
    fprintf(fTrace_file, " : MB Loop : %3d MHz (%3d Cycles)",
                               (((uiField0Cycles)*30)/1000000), uiField0Cycles);
  }
}
#endif /*#ifdef GENERATE_PROFILE_NUMBER*/

  printf("\n");
  return XDM_EOK;
}
/**
********************************************************************************
 *  @fn     H264ENC_TI_Report_Error
 *  @brief  This function will print error messages
 *
 *          This function will check for codec errors which are mapped to
 *          extended errors in videnc2status structure and prints them in cosole
 *          Returns XDM_EFAIL in case of fatal error
 *
 *  @param[in]  uiErrorMsg  : Extended error message
 *
 *  @param[in]  fTrace_file : File pointer to the trace log file
 *
 *  @return     XDM_EOK -  when there is no fatal error
 *              XDM_EFAIL - when it is fatal error
********************************************************************************
*/

XDAS_Int32 H264ENC_TI_Report_Error(FILE * fTrace_file,XDAS_Int32 uiErrorMsg)
{
  int i;
  if(uiErrorMsg)
  {
    /*------------------------------------------------------------------------*/
    /* Loop through all the bits in error message and map to the glibal       */
    /* error string                                                           */
    /*------------------------------------------------------------------------*/
    for (i = 0; i < 32; i ++)
    {
      if (uiErrorMsg & (1 << i))
      {
        printf("ERROR: %s \n",  gErrorStrings[i].errorName);
        fprintf(fTrace_file, "ERROR: %s \n",  gErrorStrings[i].errorName);
      }
    }
  }
  if (XDM_ISFATALERROR(uiErrorMsg))
  {
    return XDM_EFAIL;
  }
  else
  {
    return XDM_EOK;
  }
}

/** 
********************************************************************************
 *  @fn     H264ENC_TI_Report_ExtError
 *  @brief  This function will print sub extended error messages
 *          
 *          This function will check for codec errors which are mapped to 
 *          sub-extended errors in IH264ENC_Status structure and 
 *          IH264ENC_OutArgs structure and prints them on console
 *
 *  @param[in]  uiErrorMsg  : Extended error message
 *
 *  @param[in]  errorWord   : pointer to error word
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void H264ENC_TI_Report_ExtError(FILE * fTrace_file, 
                                                        XDAS_UInt32 * errorWord)
{
  XDAS_UInt32 i , numErrorWords;
  XDAS_UInt32 uiErrorMsg ;

  for(numErrorWords = 0 ; numErrorWords<IH264ENC_EXTERROR_NUM_MAXWORDS ; 
                                                               numErrorWords++)
  {
    uiErrorMsg = errorWord[numErrorWords] ;
    if(uiErrorMsg)
    {
      /*---------------------------------------------------------------------*/
      /* Loop through all the bits in error message and map to the glibal    */
      /* error string                                                        */
      /*---------------------------------------------------------------------*/
      for (i = 0; i < 32; i ++)
      {
        if (uiErrorMsg & (1 << i))
        {
          printf("EXT_ERROR: %s \n",  
                          gExtErrorStrings[(numErrorWords * 32 )+i].errorName);
          fprintf(fTrace_file, "EXT_ERROR: %s \n", 
                          gExtErrorStrings[(numErrorWords * 32 )+i].errorName);
        }
      }
    }

  }

  return ;
}

/**
********************************************************************************
 *  @fn     GetConfigFileContent
 *  @brief  Function to read contents of the configuration file
 *
 *          This function just checks size of the given file and copies to the
 *          Buffer created with mallocs and returns the buffer pointer.
 *          Allocated buffer will be freed out side the function once parsing of
 *          config parameters is done
 *
 *  @param[in]  fname  : File pointer to be read.
 *
 *  @return bufConfig  : Pointer to the config file data
********************************************************************************
*/
static XDAS_Int8 *GetConfigFileContent (FILE *fname)
{
  XDAS_Int32 FileSize;
  XDAS_Int8 *bufConfig;
  /*--------------------------------------------------------------------------*/
  /* Check size of the file and return in case of error                       */
  /*--------------------------------------------------------------------------*/
  if (0 != fseek (fname, 0, SEEK_END))
  {
    return 0;
  }

  FileSize = ftell (fname);
  if (FileSize < 0 || FileSize > 30000)
  {
    return 0;
  }
  /*--------------------------------------------------------------------------*/
  /* Go to the start of the file to read content                              */
  /*--------------------------------------------------------------------------*/
  if (0 != fseek (fname, 0, SEEK_SET))
  {
    return 0;
  }
  /*--------------------------------------------------------------------------*/
  /* Allocate the buffer with size as file size                               */
  /* One byte extra allocated to insert end of string delimeter               */
  /*--------------------------------------------------------------------------*/
  if ((bufConfig = malloc(FileSize + 1)) == NULL)
  {
    fprintf(stdout, "No Enough memory for Config Buffer");
  }
  FileSize = fread (bufConfig, 1, FileSize, fname);
  /*--------------------------------------------------------------------------*/
  /* Put end of string marker                                                 */
  /*--------------------------------------------------------------------------*/
  bufConfig[FileSize] = '\0';

  return bufConfig;
}/* GetConfigFileContent */

/**
********************************************************************************
 *  @fn     ParameterNameToMapIndex
 *  @brief  Returns the index number from sTokenMap for a given parameter name.
 *
 *
 *  @param[in]  s  : pointer to the TokenMap string to be searched
 *
 *  @return i  : Index number if it finds the sring in token map structure
 *               -1 in case it does not find string in tokem map structure
********************************************************************************
*/

static XDAS_Int32 ParameterNameToMapIndex (XDAS_Int8 *s)
{
  XDAS_Int32 i = 0;

  while (sTokenMap[i].tokenName != NULL)
  {
    if (0==strcmp((const char *)sTokenMap[i].tokenName, (const char *)s))
      return i;
    else
      i++;
  }

  return -1;
}/* ParameterNameToMapIndex */

/**
********************************************************************************
 *  @fn     ParseContent
 *  @brief  Parses the character array buf and writes global variable input,
 *          which is defined above. This hack will continue to be
 *          necessary to facilitate the addition of new parameters through the
 *          sTokenMap[] mechanism-Need compiler-generated addresses in sTokenMap
 *
 *
 *  @param[in]  buf : buffer to be parsed
 *
 *  @param[in]  bufsize : size of the buffer
 *
 *  @return     0 - if successfully parsed all the elements in param file and
 *                  their  values read into the memory addresses given in
 *                  token mappign array.
 *             -1 - For any file read operation related errors or if
 *                  unknown parameter names are entered or if the parameter
 *                  file syntax is not in compliance with the below
 *                  implementation.
********************************************************************************
*/

static XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize)
{
  /*--------------------------------------------------------------------------*/
  /* Total number of parameter initialisation lines in the file this          */
  /* excludes comment lines and blank lines if any                            */
  /*--------------------------------------------------------------------------*/
  XDAS_Int8 *items[MAX_ITEMS_TO_PARSE];
  XDAS_Int32 item = 0;
  /*--------------------------------------------------------------------------*/
  /* Index into the token map array - into which the corresponding            */
  /* parameter values needs to be initialised  from the param file            */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32 MapIdx;
  /*--------------------------------------------------------------------------*/
  /* Flags which indicate the current state of the state machine              */
  /* InString - indicates that buffer pointer is currently in between         */
  /* a valid string, which inturn can contain multiple items.                 */
  /* InItem - indicates that buffer pointer is within a valid item            */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32 InString = 0, InItem = 0;
  /*--------------------------------------------------------------------------*/
  /* Dynamic pointer movign allong the param file buffer byte-by-byte         */
  /*--------------------------------------------------------------------------*/
  XDAS_Int8 *p = buf;
  /*--------------------------------------------------------------------------*/
  /* end of buffer - used for terminating the parse loop                      */
  /*--------------------------------------------------------------------------*/
  XDAS_Int8 *bufend = &buf[bufsize];
  /*--------------------------------------------------------------------------*/
  /* Parameter value read from the file and loop counter                      */
  /*--------------------------------------------------------------------------*/
  XDAS_Int32 IntContent;
  XDAS_Int32 i;
  XDAS_Int32 pos = 0;
  /*--------------------------------------------------------------------------*/
  /*                                STAGE ONE                                 */
  /* Generate an argc/argv-type list in items[], without comments and         */
  /* whitespace. This is context insensitive and could be done most easily    */
  /* with lex(1).                                                             */
  /*--------------------------------------------------------------------------*/
  while (p < bufend)
  {
    switch (*p)
    {
      /*----------------------------------------------------------------------*/
      /* blank space - skip the character and go to next                      */
      /*----------------------------------------------------------------------*/
      case 13:
        p++;
      break;
      /*----------------------------------------------------------------------*/
      /* Found a comment line skip all characters until end-of-line is found  */
      /*----------------------------------------------------------------------*/
      case '#':
        /*--------------------------------------------------------------------*/
        /* Replace '#' with '\0' in case of comment immediately following     */
        /* integer or string Skip till EOL or EOF, whichever comes first      */
        /*--------------------------------------------------------------------*/
        *p = '\0';
        while (*p != '\n' && p < bufend)
          p++;
        InString = 0;
        InItem = 0;
      break;
      /*----------------------------------------------------------------------*/
      /* end of line - skip the character and go to next,reset the InItem flag*/
      /* to indicate that we are not in any valid item                        */
      /*----------------------------------------------------------------------*/
      case '\n':
        InItem = 0;
        InString = 0;
        *p++='\0';
      break;
      /*----------------------------------------------------------------------*/
      /* Whitespaces and tabs indicate end of an item                         */
      /*----------------------------------------------------------------------*/
      case ' ':
      case '\t':
        /*--------------------------------------------------------------------*/
        /* if the state machine is within a string Skip whitespace,           */
        /* leave state unchanged                                              */
        /* else Terminate non-strings once whitespace is found                */
        /*--------------------------------------------------------------------*/
        if (InString)
          p++;
        else
        {
          *p++ = '\0';
          InItem = 0;
        }
      break;
      /*----------------------------------------------------------------------*/
      /* begining or end of string - toggle the string indication flag        */
      /*----------------------------------------------------------------------*/
      case '"':
        *p++ = '\0';
        if (!InString)
        {
          items[item++] = p;
          InItem = ~InItem;
        }
        else
          InItem = 0;
        InString = ~InString;
      break;
      /*----------------------------------------------------------------------*/
      /* Any othe character is taken into the item provided the state machine */
      /* is within a valid Item                                               */
      /*----------------------------------------------------------------------*/
    default:
      if (!InItem)
      {
        items[item++] = p;
        InItem = ~InItem;
      }
      p++;
    }
  }
  item--;
  /*--------------------------------------------------------------------------*/
  /* for all the items found - check if they correspond to any valid parameter*/
  /* names specified by the user through token map array,                     */
  /* Note: Contigous three items are grouped into triplets. Thsi oredered     */
  /* triplet is used to identify the valid parameter entry in the Token map   */
  /* array.                                                                   */
  /* First item in the triplet has to eb a parameter name.                    */
  /* Second item has to be a "=" symbol                                       */
  /* Third item has to be a integer value.                                    */
  /* Any violation of the above order in the triplets found would lead        */
  /* to error condition.                                                      */
  /*--------------------------------------------------------------------------*/
  for (i=0; i<item; i+= 3)
  {
    /*------------------------------------------------------------------------*/
    /* Get the map index into the token map array - corresponding to the      */
    /* first item - in a item-triplet                                         */
    /*------------------------------------------------------------------------*/
    if (0 <= (MapIdx = ParameterNameToMapIndex (items[i])))
    {
      /*----------------------------------------------------------------------*/
      /* Assert if the second item is indeed "=" symbol                       */
      /*----------------------------------------------------------------------*/
      if (strcmp ((const char *)"=", (const char *)items[i+1]))
      {
        printf(
          "\nfile: '=' expected as the second token in each line.");
        return -1;
      }
      /*----------------------------------------------------------------------*/
      /* depending upon the type of content convert them and populate the     */
      /* corresponding entry in the token map array with this value           */
      /*----------------------------------------------------------------------*/
      if(sTokenMap[MapIdx].type == 0)
      {
        strcpy((char *)sTokenMap[MapIdx].place, (char *)items[i+2]);
      }
      else if (sTokenMap[MapIdx].type == 4)
      {
        sscanf ((const char *)items[i+2], "%d", (&IntContent));
        * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
      }
      else if (sTokenMap[MapIdx].type == 2)
      {
        sscanf ((const char *)items[i+2], "%d", &IntContent);
        * ((XDAS_Int16 *) (sTokenMap[MapIdx].place)) = IntContent;
      }
      else
      {
        sscanf ((const char *)items[i+2], "%d", &IntContent);
        * ((XDAS_Int8 *) (sTokenMap[MapIdx].place)) = IntContent;
      }

      /*---------------------------------------------------------------------*/
      /* This part of code is used in reading dynamic parameter change file  */
      /* The parameter to be changed for a particular frame that will present*/
      /* between the token "DynamicFramePos = #frameno" in dynamic parameter */
      /* change file. So for reading changed parameters for a frame,         */
      /* it should read from first "DynamicFramePos = #frameno" till the next*/
      /* "DynamicFramePos = #frameno". Here stopPos is global variable       */
      /* initialized with 1 at the start of sequence and pos is local        */
      /* variable initialized with 0. After reading the token DynamicFramePos*/
      /* for 2 times, it means parameter change for a particular frame is    */
      /* read.                                                               */
      /*---------------------------------------------------------------------*/
      if(gConfigOrg.enableRunTimeTest)
      {
        if (0==strcmp((const char *)sTokenMap[MapIdx].tokenName,
            "DynamicFramePos"))
        {
          if(stopPos == pos)
          {
            stopPos++;
            return 0;
          }
          pos++;
        }
      }
    }
    else
    {
      printf("\nParameter Name '%s' not recognized...  \n", items[i]);
    }
  }
  return 0 ;
}/* ParseContent */

/**
********************************************************************************
 *  @fn     readparamfile
 *  @brief  Reads the entire param file contents into a global buffer,which is
 *          used for parsing and updates the params to given addresses.
 *
 *  @param[in]  file name : Name of the configuration file with path
 *
 *  @return     0 - if successfully parsed all the elements in param file and
 *                  their  values read into the memory addresses given in
 *                  token mappign array.
 *             XDM_EFAIL - For any file read operation related errors or if
 *                  unknown parameter names are entered or if the parameter
 *                  file syntax is not in compliance with the below
 *                  implementation.
********************************************************************************
*/

XDAS_Int32 readparamfile(XDAS_Int8 *configFile)
{
  XDAS_Int8 *FileBuffer = NULL;
  XDAS_Int32  retVal ;
  FILE        *fConfigFile;
  /*--------------------------------------------------------------------------*/
  /*  Open Test Config File                                                   */
  /*--------------------------------------------------------------------------*/
  fConfigFile = fopen((const char *)configFile,"r");
  /*--------------------------------------------------------------------------*/
  /*  Perform file open error check.                                          */
  /*--------------------------------------------------------------------------*/
  if (!fConfigFile)
  {
    printf("Couldn't open Parameter Config file %s.\n",configFile);
    return XDM_EFAIL;
  }
  /*--------------------------------------------------------------------------*/
  /* read the content in a buffer                                             */
  /*--------------------------------------------------------------------------*/
  FileBuffer = GetConfigFileContent(fConfigFile);

  /*--------------------------------------------------------------------------*/
  /*    Close Config Parameter File.                                          */
  /*--------------------------------------------------------------------------*/
  fclose(fConfigFile);
  /*--------------------------------------------------------------------------*/
  /* if the buffer address is NULL then return error                          */
  /*--------------------------------------------------------------------------*/
  if(FileBuffer)
  {
    /*------------------------------------------------------------------------*/
    /* Parse every string into items and group them into triplets.            */
    /* Decode these ordered triplets into correspondign indices in the global */
    /* Token Map arrray provided by the user.                                 */
    /*------------------------------------------------------------------------*/
    retVal  = ParseContent(FileBuffer,strlen((const char *)FileBuffer));
    /*------------------------------------------------------------------------*/
    /* Free the buffer allocated in "GetConfigFileContent" function           */
    /*------------------------------------------------------------------------*/
    free(FileBuffer) ;
    return retVal;
  }
  else
  {
    return XDM_EFAIL;
  }
}/* readparamfile */

/**
********************************************************************************
 *  @fn     H264ENC_TI_InitDynamicParams
 *  @brief  Function to init dynamic params with Encode params
 *
 *          This fucntion will update the extended dynamic params with the
 *          extended params in encode params structure.
 *          This function should be called as soon as cofig params are parsed
 *          and read from the file. This is due to all the extended params will
 *          be updated in Encode params structure
 *
 *  @param[in] params : pointer to the XDM params interface structure
 *
 *  @param[in] dynamicParams : Pointer to t he XDM dynamicparams structure
 *
 *  @return    None
********************************************************************************
*/

XDAS_Void H264ENC_TI_InitDynamicParams(H264ENC_Params *params,
                                           H264ENC_DynamicParams *dynamicParams)
{

  dynamicParams->videnc2DynamicParams.size  = sizeof(H264ENC_DynamicParams);

  /* For tighter control of Rate Control Limit QPMax */
  if(params->videnc2Params.maxBitRate != -1)
  {
     int intraFrameInterval  =
                         dynamicParams->videnc2DynamicParams.intraFrameInterval;
   /*-------------------------------------------------------------------------*/
   /* even if the content type is IVIDEO_INTERLACED, it is not guranted to be */
   /* interlace coding. But for simplicity it have been assumed here          */
   /*-------------------------------------------------------------------------*/
   if((params->videnc2Params.inputContentType == IVIDEO_INTERLACED) &&
      (params->bottomFieldIntra == 0)
     )
   {
     /*-----------------------------------------------------------------------*/
     /* In case of interlace , bottom field inter acctual intra period is     */
     /* doubled.                                                              */
     /*-----------------------------------------------------------------------*/
     intraFrameInterval <<= 1;
   }
   if(intraFrameInterval == 0)
   {
     intraFrameInterval = 0x7FFFFFFF;
   }
  }
  
  /*--------------------------------------------------------------------------*/
  /* Currently we are using intraFrameInterval and maxIntraFrameInterval same */
  /*--------------------------------------------------------------------------*/
  params->maxIntraFrameInterval =
  dynamicParams->videnc2DynamicParams.intraFrameInterval ;

  memcpy(&((dynamicParams)->rateControlParams),&(params->rateControlParams),
                                           sizeof (IH264ENC_RateControlParams));
  memcpy(&((dynamicParams)->interCodingParams),&(params->interCodingParams),
                                           sizeof (IH264ENC_InterCodingParams));

  memcpy(&((dynamicParams)->intraCodingParams),&(params->intraCodingParams),
                                           sizeof (IH264ENC_IntraCodingParams));
                                           
  memcpy(&((dynamicParams)->sliceCodingParams),&(params->sliceCodingParams),
                                           sizeof (IH264ENC_SliceCodingParams));
  dynamicParams->sliceGroupChangeCycle =
                               gParamsOrg.fmoCodingParams.sliceGroupChangeCycle;


  /*--------------------------------------------------------------------------*/
  /*  Force fully make ignoreOutbufSizeFlag = TRUE for sub-frame level data   */
  /* synchronization                                                          */
  /*--------------------------------------------------------------------------*/
  gDynamicParamsOrg.videnc2DynamicParams.ignoreOutbufSizeFlag = 1;
  gDynamicParamsOrg.videnc2DynamicParams.getBufferFxn =
    H264ETest_DataSyncGetBufFxn;

  gDynamicParamsOrg.videnc2DynamicParams.putDataFxn =
    H264ETest_DataSyncPutDataFxn;
  /*--------------------------------------------------------------------------*/
  /* Set "getDataFxn" pointer to the call back function in application        */
  /*--------------------------------------------------------------------------*/
  fGetInpDHandle1 = (XDM_DataSyncHandle)&ip_datasyncDesc1;
  fGetInpDHandle2 = (XDM_DataSyncHandle)&ip_datasyncDesc2;
  gDynamicParamsOrg.videnc2DynamicParams.getDataFxn =
    H264ETest_DataSyncGetDataFxn1;
  gDynamicParamsOrg.videnc2DynamicParams.getDataHandle =
    fGetInpDHandle1;
  
  dynamicParams->reservedDynParams[0]               = 0;
  dynamicParams->reservedDynParams[1]               = 0;
  dynamicParams->reservedDynParams[2]               = 0;
}

/**
********************************************************************************
 *  @fn     TestApp_SetInitParams
 *  @brief  Function to set default parameters
 *          This function will set default params for params function and
 *          dynamicparams function. This must be called before parsing config
 *          file so that default values are set when config file does not
 *          specify any value
 *
 *  @param[in] params : pointer to the XDM params interface structure
 *
 *  @param[in] dynamicParams : Pointer to t he XDM dynamicparams structure
 *
 *  @return    None
********************************************************************************
*/
XDAS_Void TestApp_SetInitParams(H264ENC_Params *params,
                                           H264ENC_DynamicParams *dynamicParams)
{
  /*--------------------------------------------------------------------------*/
  /* First set default values to base class XDM params structure              */
  /* Please refer User guide Table 4.5 for further details on values          */
  /*--------------------------------------------------------------------------*/
  params->videnc2Params.encodingPreset                = XDM_DEFAULT;
  params->videnc2Params.rateControlPreset             = IVIDEO_STORAGE;
  params->videnc2Params.maxHeight                     = 1088;
  params->videnc2Params.maxWidth                      = 1920;
  params->videnc2Params.dataEndianness                = XDM_BYTE;
  params->videnc2Params.maxInterFrameInterval         = 1;
  params->videnc2Params.maxBitRate                    = -1;
  params->videnc2Params.minBitRate                    = 0;
  params->videnc2Params.inputChromaFormat             = XDM_YUV_420SP ;
  params->videnc2Params.inputContentType              = IVIDEO_PROGRESSIVE;
  params->videnc2Params.operatingMode                 = IVIDEO_ENCODE_ONLY;
  params->videnc2Params.profile                       = IH264_HIGH_PROFILE;
  params->videnc2Params.level                         = IH264_LEVEL_40;
  params->videnc2Params.inputDataMode                 = IVIDEO_ENTIREFRAME;
  params->videnc2Params.outputDataMode                = 0;
  params->videnc2Params.numInputDataUnits             = 1;
  params->videnc2Params.numOutputDataUnits            = 2;

  /*--------------------------------------------------------------------------*/
  /* Set rate controll params in extended XDM params structure                */
  /* Please refer User guide Table 4.7 for further details on values          */
  /*--------------------------------------------------------------------------*/
  params->rateControlParams.rateControlParamsPreset   =
                                                IH264_RATECONTROLPARAMS_DEFAULT;
  params->rateControlParams.scalingMatrixPreset       =
                                                    IH264_SCALINGMATRIX_DEFAULT;
  params->rateControlParams.rcAlgo                    =
                                                      IH264_RATECONTROL_DEFAULT;
  params->rateControlParams.minPicSizeRatioI          = 0;
  params->rateControlParams.maxPicSizeRatioI          = 640;
  params->rateControlParams.minPicSizeRatioP          = 0;
  params->rateControlParams.maxPicSizeRatioP          = 0;
  params->rateControlParams.minPicSizeRatioB          = 0;
  params->rateControlParams.maxPicSizeRatioB          = 0;    
  params->rateControlParams.frameSkipThMulQ5          = 0;
  params->rateControlParams.vbvUseLevelThQ5           = 0;
                                                      
  params->rateControlParams.qpI                       = 28;
  params->rateControlParams.qpMaxI                    = 36;
  params->rateControlParams.qpMinI                    = 10;
  params->rateControlParams.qpP                       = 28;
  params->rateControlParams.qpMaxP                    = 40;
  params->rateControlParams.qpMinP                    = 10;
  params->rateControlParams.qpOffsetB                 = 4;
  params->rateControlParams.qpMaxB                    = 44;
  params->rateControlParams.qpMinB                    = 10;
  params->rateControlParams.allowFrameSkip            = 0;
  params->rateControlParams.removeExpensiveCoeff      = 0;
  params->rateControlParams.chromaQPIndexOffset       = 0;
  params->rateControlParams.IPQualityFactor           =
                                                   IH264_QUALITY_FACTOR_DEFAULT;
  params->rateControlParams.initialBufferLevel        =
                                                        24000000;
  params->rateControlParams.HRDBufferSize             =
                                params->rateControlParams.initialBufferLevel* 2;

  params->rateControlParams.enablePRC                 = 1;
  params->rateControlParams.enablePartialFrameSkip    = 0;
  params->rateControlParams.discardSavedBits          = 0;
  params->rateControlParams.VBRDuration               = 8;
  params->rateControlParams.VBRsensitivity            = 0;
  params->rateControlParams.skipDistributionWindowLength = 5;
  params->rateControlParams.numSkipInDistributionWindow  = 1;
  params->rateControlParams.enableHRDComplianceMode   = 1;
  /*--------------------------------------------------------------------------*/
  /* Set Inter coding params in extended XDM params structure                 */
  /* Please refer User guide Table 4.8 for further details on values          */
  /*--------------------------------------------------------------------------*/
  params->interCodingParams.interCodingPreset         =
                                                      IH264_INTERCODING_DEFAULT;
  params->interCodingParams.searchRangeHorP           = 144;
  params->interCodingParams.searchRangeVerP           = 32;
  params->interCodingParams.searchRangeHorB           = 144;
  params->interCodingParams.searchRangeVerB           = 16;
  params->interCodingParams.interCodingBias           =
                                                       IH264_BIASFACTOR_DEFAULT;
  params->interCodingParams.skipMVCodingBias          =
                                                       IH264_BIASFACTOR_DEFAULT;
  params->interCodingParams.minBlockSizeP             = IH264_BLOCKSIZE_DEFAULT;
  params->interCodingParams.minBlockSizeB             = IH264_BLOCKSIZE_DEFAULT;
  params->interCodingParams.meAlgoMode                =
                                                 IH264ENC_MOTIONESTMODE_DEFAULT;

  /*--------------------------------------------------------------------------*/
  /* Set Intra coding params in extended XDM params structure                 */
  /* Please refer User guide Table 4.9 for further details on values          */
  /*--------------------------------------------------------------------------*/
  params->intraCodingParams.intraCodingPreset         =
                                                      IH264_INTRACODING_DEFAULT;
  params->intraCodingParams.lumaIntra4x4Enable        = 0x0;
  params->intraCodingParams.lumaIntra8x8Enable        = 0x0FF;
  params->intraCodingParams.lumaIntra16x16Enable      = 0xF;
  params->intraCodingParams.chromaIntra8x8Enable      = 0xF;
  params->intraCodingParams.chromaComponentEnable     =
                                                 IH264_CHROMA_COMPONENT_DEFAULT;
  params->intraCodingParams.intraRefreshMethod        =
                                                     IH264_INTRAREFRESH_DEFAULT;
  params->intraCodingParams.intraRefreshRate          = 0;
  params->intraCodingParams.gdrOverlapRowsBtwFrames   = 0;
  params->intraCodingParams.constrainedIntraPredEnable= 0;
  params->intraCodingParams.intraCodingBias           = 0;
  /*--------------------------------------------------------------------------*/
  /* Set NAL unit coding params in extended XDM params structure              */
  /* Please refer User guide Table 4.10 for further details on values         */
  /*--------------------------------------------------------------------------*/

  params->nalUnitControlParams.naluControlPreset      =
                                                     IH264_NALU_CONTROL_DEFAULT;
  params->nalUnitControlParams.naluPresentMaskStartOfSequence = 0x01A0;
  params->nalUnitControlParams.naluPresentMaskIDRPicture      = 0x01A0;
  params->nalUnitControlParams.naluPresentMaskIntraPicture    = 0x0002;
  params->nalUnitControlParams.naluPresentMaskNonIntraPicture = 0x0002;
  params->nalUnitControlParams.naluPresentMaskEndOfSequence   = 0x0C00;

  /*--------------------------------------------------------------------------*/
  /* Set Slice coding params in extended XDM params structure                 */
  /* Please refer User guide Table 4.11 for further details on values         */
  /*--------------------------------------------------------------------------*/

  params->sliceCodingParams.sliceCodingPreset         =
                                                      IH264_SLICECODING_DEFAULT;
  params->sliceCodingParams.sliceMode                 = IH264_SLICEMODE_DEFAULT;
  params->sliceCodingParams.sliceUnitSize             = 0;
  params->sliceCodingParams.sliceStartOffset[0]       = 0;
  params->sliceCodingParams.sliceStartOffset[1]       = 0;
  params->sliceCodingParams.sliceStartOffset[2]       = 0;
  params->sliceCodingParams.streamFormat              =
                                                    IH264_STREAM_FORMAT_DEFAULT;
  /*--------------------------------------------------------------------------*/
  /* Set Loop filter coding params in extended XDM params structure           */
  /* Please refer User guide Table 4.12 for further details on values         */
  /*--------------------------------------------------------------------------*/
  params->loopFilterParams.loopfilterPreset           =
                                                      IH264_LOOPFILTER_DEFAULT;
  params->loopFilterParams.loopfilterDisableIDC       =
                                                  IH264_DISABLE_FILTER_DEFAULT;
  params->loopFilterParams.filterOffsetA              = 0;
  params->loopFilterParams.filterOffsetB              = 0;

  /*--------------------------------------------------------------------------*/
  /* Set VUI coding params in extended XDM params structure                   */
  /* Please refer User guide Table 4.14 for further details on values         */
  /*--------------------------------------------------------------------------*/
  params->vuiCodingParams.vuiCodingPreset             =
                                                        IH264_VUICODING_DEFAULT;
  params->vuiCodingParams.aspectRatioInfoPresentFlag  = 0;
  params->vuiCodingParams.aspectRatioIdc              = 0;
  params->vuiCodingParams.videoSignalTypePresentFlag  = 0;
  params->vuiCodingParams.videoFormat                 =
                                                      IH264ENC_VIDEOFORMAT_NTSC;
  params->vuiCodingParams.videoFullRangeFlag          = 0;
  params->vuiCodingParams.timingInfoPresentFlag       = 0;
  params->vuiCodingParams.numUnitsInTicks             = 1000;
  params->vuiCodingParams.hrdParamsPresentFlag        = 0;

  /*--------------------------------------------------------------------------*/
  /* disable frame packing SEI encoding coding params by default              */
  /*--------------------------------------------------------------------------*/
  params->framePackingSEIParams.framePackingPreset   = 0;

  /*--------------------------------------------------------------------------*/
  /* Set StereoVideoinformation coding params in extended XDM params structure*/
  /* Please refer User guide for further details on values                    */
  /*--------------------------------------------------------------------------*/
  params->stereoInfoParams.stereoInfoPreset        = IH264_STEREOINFO_DISABLE;
  params->stereoInfoParams.topFieldIsLeftViewFlag  = 0;
  params->stereoInfoParams.viewSelfContainedFlag   = 0;

/*--------------------------------------------------------------------------*/
  /* Set FMO coding params in extended XDM params structure                   */
  /* Please refer User guide Table 4.13 for further details on values         */
  /*--------------------------------------------------------------------------*/

  params->fmoCodingParams.fmoCodingPreset            =
                                                        IH264_FMOCODING_DEFAULT;
  params->fmoCodingParams.numSliceGroups             = 1;
  params->fmoCodingParams.sliceGroupMapType          =
                                                    IH264_SLICE_GRP_MAP_DEFAULT;
  params->fmoCodingParams.sliceGroupChangeDirectionFlag =
                                  IH264ENC_SLICEGROUP_CHANGE_DIRECTION_DEFAULT ;
  params->fmoCodingParams.sliceGroupChangeRate       = 0;
  params->fmoCodingParams.sliceGroupChangeCycle      = 0;
  params->fmoCodingParams.sliceGroupParams[0]        = 0;
  params->fmoCodingParams.sliceGroupParams[1]        = 0;

  /*--------------------------------------------------------------------------*/
  /* Set Extended XDM Encode parameters in extended XDM params structure      */
  /* Please refer User guide Table 4.15 for further details on values         */
  /*--------------------------------------------------------------------------*/
  params->interlaceCodingType                       =
                                                  IH264_INTERLACE_FIELDONLY_ARF;
  params->bottomFieldIntra                          = 0;
  params->gopStructure                              =
                                               IH264ENC_GOPSTRUCTURE_NONUNIFORM;
  params->entropyCodingMode                         =
                                                      IH264_ENTROPYCODING_CABAC;
  params->transformBlockSize                        = IH264_TRANSFORM_ADAPTIVE;
  params->log2MaxFNumMinus4                         = 10;
  params->picOrderCountType                         = IH264_POC_TYPE_0;
  params->enableRCDO                         = 0;

  /*----------------------------------------------------------*/
  /* Set meta data type to no meta data usage in the begining */
  /*----------------------------------------------------------*/
  {
    int i ;
    for (i = 0 ; i < IVIDEO_MAX_NUM_METADATA_PLANES; i++)
    {
      params->videnc2Params.metadataType[i] = IVIDEO_METADATAPLANE_NONE;
    }
  }
  params->IDRFrameInterval                          = 0;
  params->pConstantMemory                           = 0;
  params->reservedParams[0]                         = 0;
  params->reservedParams[1]                         = 0;
  params->reservedParams[2]                         = 0;
  params->enableGMVSei                              = 0;
  params->constraintSetFlags                        = 0;
  params->enableLongTermRefFrame                    = 0;
  params->enableWatermark                           = 0;
  params->LTRPPeriod                                = 0xFFFFFFFF;

  params->numTemporalLayer                     = IH264_TEMPORAL_LAYERS_1;
  params->referencePicMarking                  = IH264_LONG_TERM_PICTURE;
  params->svcCodingParams.svcExtensionFlag   = IH264_SVC_EXTENSION_FLAG_DISABLE;

  params->debugTraceLevel                           = 1;
  params->lastNFramesToLog                          = 0;

  params->enableAnalyticinfo = 0;
  /*--------------------------------------------------------------------------*/
  /* Set dynamic parameters                                                   */
  /* Most of the default parameters can be copied from Encdoer params         */
  /*--------------------------------------------------------------------------*/
  memcpy(&((dynamicParams)->rateControlParams),&(params->rateControlParams),
                                           sizeof (IH264ENC_RateControlParams));
  memcpy(&((dynamicParams)->interCodingParams),&(params->interCodingParams),
                                           sizeof (IH264ENC_InterCodingParams));
  memcpy(&((dynamicParams)->intraCodingParams),&(params->intraCodingParams),
                                           sizeof (IH264ENC_IntraCodingParams));
  memcpy(&((dynamicParams)->sliceCodingParams),&(params->sliceCodingParams),
                                           sizeof (IH264ENC_SliceCodingParams));
  /*--------------------------------------------------------------------------*/
  /* Set all the XDM dynamic values to default values                         */
  /*--------------------------------------------------------------------------*/
  dynamicParams->videnc2DynamicParams.captureWidth = 1920;
  dynamicParams->videnc2DynamicParams.forceFrame   = IVIDEO_NA_FRAME;
  dynamicParams->videnc2DynamicParams.generateHeader = XDM_ENCODE_AU;
  dynamicParams->videnc2DynamicParams.ignoreOutbufSizeFlag = 1;
  dynamicParams->videnc2DynamicParams.inputHeight = 1088;
  dynamicParams->videnc2DynamicParams.inputWidth  = 1920;
  dynamicParams->videnc2DynamicParams.interFrameInterval = 1;
  dynamicParams->videnc2DynamicParams.intraFrameInterval = 30;
  dynamicParams->videnc2DynamicParams.mvAccuracy =
                                               IVIDENC2_MOTIONVECTOR_QUARTERPEL;
  dynamicParams->videnc2DynamicParams.putDataFxn = NULL;
  dynamicParams->videnc2DynamicParams.putDataHandle = 0;
  dynamicParams->videnc2DynamicParams.refFrameRate = 30000;
  dynamicParams->videnc2DynamicParams.sampleAspectRatioHeight = 1;
  dynamicParams->videnc2DynamicParams.sampleAspectRatioWidth  = 1;
  dynamicParams->videnc2DynamicParams.targetBitRate = 12000000;
  dynamicParams->videnc2DynamicParams.targetFrameRate = 30000;

  dynamicParams->sliceGroupChangeCycle =
                               gParamsOrg.fmoCodingParams.sliceGroupChangeCycle;

  dynamicParams->searchCenter.x                     = 0x7FFF;
  dynamicParams->searchCenter.y                     = 0x7FFF;
  dynamicParams->enableStaticMBCount                = 0;
  dynamicParams->enableROI                          = 0;
  dynamicParams->reservedDynParams[0]               = 0;
  dynamicParams->reservedDynParams[1]               = 0;
  dynamicParams->reservedDynParams[2]               = 0;

  /*--------------------------------------------------------------------------*/
  /* Set Main gConfigOrg structure parameter values with default values       */
  /*--------------------------------------------------------------------------*/
  gConfigOrg.captureTopLeftx = 0;
  gConfigOrg.captureTopLefty = 0;
  /*--------------------------------------------------------------------------*/
  /* Set forceIDRPeriod, forceSKIPPeriod huge value as default to prevent     */
  /* forced control                                                           */
  /*--------------------------------------------------------------------------*/
  gConfigOrg.forceIDRPeriod       = 0xFFFFFFFF;
  gConfigOrg.forceSKIPPeriod      = 0xFFFFFFFF;
  gConfigOrg.gdrPeriod         = 0xFFFFFFFF;
  gConfigOrg.gdrStartFrameNum  = 0xFFFFFFFF;
  gConfigOrg.LongTermRefPeriod    = 0xFFFFFFFF;
  gConfigOrg.LTRPFailureLocation0 = 0xFFFFFFFF;
  gConfigOrg.LTRPFailureLocation1 = 0xFFFFFFFF;

  /*--------------------------------------------------------------------------*/
  /* Irrespective of content type we always use 30 process call method of     */
  /* encoding for interlced content                                           */
  /*--------------------------------------------------------------------------*/
  gConfigOrg.numProcessCall  = 0;
  gInputBufDescOrg.topFieldFirstFlag = 0;
  gConfigOrg.tilerSpace[0] =  0 ;
  gConfigOrg.tilerSpace[1] =  0 ;

  /*--------------------------------------------------------------------------*/
  /* Set IVAHD0 as default                                                    */
  /*--------------------------------------------------------------------------*/
  gConfigOrg.ivahdid = 0;

  /*--------------------------------------------------------------------------*/
  /* Flag to enable testing of runtime parameter change                       */
  /*--------------------------------------------------------------------------*/
  gConfigOrg.enableRunTimeTest = 0;
  gConfigOrg.DynamicFramePos = 0;

  /*--------------------------------------------------------------------------*/
  /* Number of blocks to be given as input duringeach DataSyncGetData call    */
  /*--------------------------------------------------------------------------*/
  gConfigOrg.numBlocks[0] = 1;
  gConfigOrg.numBlocks[1] = 1;
  gConfigOrg.numBlocks[2] = 1;
  gConfigOrg.numBlocks[3] = 1;
  gConfigOrg.numBlocks[4] = 1;
  gConfigOrg.numBlocks[5] = 1;
  gConfigOrg.numBlocks[6] = 1;
  gConfigOrg.numBlocks[7] = 1;

}

