/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file vpsdrv_m2mDeiFmd.c
 *
 *  \brief VPS VPE M2M driver file handling FMD operations.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <vpedrv/src/vpsdrv_m2mVpePriv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void fmd_Dei_cbfxn(VpsMdrv_VpeHandleObj *hObj);

static Int32 vpsMdrvVpeGetFmdStatusReg(VpsMdrv_VpeHandleObj *hObj,
                                       Vps_DeiFmdStatusReg  *fmdStatusReg);
static Int32 vpsMdrvVpeSetFmdUpdateCfg(VpsMdrv_VpeHandleObj   *hObj,
                                       Vps_DeiFmdUpdateConfig *fmdUpdateCfg);

static void fmd_proc(UInt16             *film_lock,
                     UInt16             *jam_dir,
                     UInt64              diff_frame_in,
                     UInt64              diff_field,
                     UInt64              caf,
                     UInt16              fmd_reset,
                     const fmd_reg_data *reg_blck,
                     fmd_data           *fmd_blck);

static UInt64 min4(const UInt64 *x);
static void film32detection(fmd_data *fmd_blck);
static void film22detection(fmd_data *fmd_blck);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/** VpsMdrv_vpeMlmFmdCbFxn
 * DEI Fmd interrupt call back function
 */
Int32 VpsMdrv_vpeMlmFmdCbFxn(const Mlm_SubmitReqInfo *reqInfo)
{
    Int32 retVal = FVID2_SOK;
    VpsMdrv_VpeQueueObj *qObj;
    VpsMdrv_VpeHandleObj *hObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != reqInfo));
    qObj = (VpsMdrv_VpeQueueObj *) reqInfo->cbArg;
    GT_assert(VpsMdrvVpeTrace, (NULL != qObj));
    hObj = qObj->hObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));

    if (TRUE == hObj->filmMode)
    {
        fmd_Dei_cbfxn(hObj);    /* FMD call back function */
    }

    return (retVal);
}

/**
 * fmd_Dei_cbfxn
 * DEI Fmd interrupt call back function
 */
static void fmd_Dei_cbfxn(VpsMdrv_VpeHandleObj *hObj)
{
    Int32  retVal = FVID2_SOK;
    Vps_DeiFmdUpdateConfig fmdUpdateCfg;
    Vps_DeiFmdStatusReg fmdStatusReg;

    UInt16 film_lock;       /* 0: video mode; 1: film mode */
    UInt16 jam_dir;         /* 0: jam with the previous field; 1: jam with the
                             *following field */
    UInt16 fmd_reset;       /* 1: reset all the state machine */
    UInt64 diff_frame;      /* frame difference (difference between two closest
                             *fields with the same fild parity) */
    UInt64 diff_field;      /* field difference (difference between two
                             *neighboring fields) */
    UInt64 caf;             /* combing artifacts when the following field is
                             *jammed with the current field */

    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));

    /* If FMD is disabled, return */
    if (TRUE == hObj->filmMode)
    {
        /* Read FMD status register values */
        retVal = vpsMdrvVpeGetFmdStatusReg(hObj, &fmdStatusReg);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                      "Get FMD status register failed\r\n");
        }
        else
        {
            /* Run FMD SW */
            fmd_reset  = fmdStatusReg.reset;
            diff_frame = fmdStatusReg.frameDiff;
            diff_field = fmdStatusReg.fldDiff;
            caf        = fmdStatusReg.caf;
            /* 4-field or 5-field */
            hObj->dei_fmd_reg_blck.mdt_num_field_mode = fmdStatusReg.fldMode;

            /*
             * diff_frame, diff_field, caf, fmd_reset are status registers
             * (hardware->software)
             * fime_lock, jam_dir are two hardware registers
             * (software->hardware)
             * This subroutine is invoked once per field
             */

            /* Process FMD */
            fmd_proc(
                &film_lock,
                &jam_dir,
                diff_frame,
                diff_field,
                caf,
                fmd_reset,
                &hObj->dei_fmd_reg_blck,
                &hObj->dei_fmd_blck);

            /* Set FMD SW result to HW registers */
            fmdUpdateCfg.chNum  = 0U;
            fmdUpdateCfg.lock   = film_lock;
            fmdUpdateCfg.jamDir = jam_dir;

            retVal = vpsMdrvVpeSetFmdUpdateCfg(hObj, &fmdUpdateCfg);

            if (FVID2_SOK != retVal)
            {
                GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                          "Set FMD update config failed\r\n");
            }
        }
    }
    return;
}

/**
 *  vpsMdrvVpeGetFmdStatusReg
 *  Read the FMD status registers in DEI and DEI_H.
 */
static Int32 vpsMdrvVpeGetFmdStatusReg(VpsMdrv_VpeHandleObj *hObj,
                                       Vps_DeiFmdStatusReg  *fmdStatusReg)
{
    Int32 retVal = FVID2_SOK;

    /* Currently FMD only support single channel */
    if (hObj->createPrms.numCh > 1U)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                  "FMD operation not supported for multi-channel mode\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        fmdStatusReg->chNum = 0U;
        retVal = vpsMdrvVpeDeiRdFmdStatIoctl(hObj, fmdStatusReg);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Read FMD stat failed\r\n");
        }
    }

    return (retVal);
}

/**
 *  vpsMdrvVpeSetFmdUpdateCfg
 *  Update the FMD config register in DEI and DEI_H after running SW.
 */
static Int32 vpsMdrvVpeSetFmdUpdateCfg(VpsMdrv_VpeHandleObj   *hObj,
                                       Vps_DeiFmdUpdateConfig *fmdUpdateCfg)
{
    Int32 retVal = FVID2_SOK;

    /* Currently FMD only support single channel */
    if (hObj->createPrms.numCh > 1U)
    {
        GT_0trace(VpsMdrvVpeTrace, GT_ERR,
                  "FMD operation not supported for multi-channel mode\r\n");
        retVal = FVID2_EBADARGS;
    }
    else
    {
        fmdUpdateCfg->chNum = 0U;
        retVal = vpsMdrvVpeDeiUpdateFmdIoctl(hObj, fmdUpdateCfg);

        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsMdrvVpeTrace, GT_ERR, "Update FMD stat failed\r\n");
        }
    }

    return (retVal);
}

/* Initialization for FMD registers */
void reg_init(fmd_reg_data *reg_blck, const VpsMdrv_VpeHandleObj *hObj)
{
    VpsMdrv_VpeInstObj *instObj;

    /* NULL pointer check */
    GT_assert(VpsMdrvVpeTrace, (NULL != hObj));
    instObj = hObj->instObj;
    GT_assert(VpsMdrvVpeTrace, (NULL != instObj));

    reg_blck->fmd_window_width  = hObj->chObjs[0]->vpePrms.inFmt.width;
    reg_blck->fmd_window_height = hObj->chObjs[0]->vpePrms.inFmt.height;

    /* This is a hardware register for DEI_HQ
     * For DEI, there's no such register */
    /* 5-field, use 1 for 4-field mode */
    reg_blck->mdt_num_field_mode = 2;

    /* Don't need to change the following settings. Default values */
    reg_blck->fmd_diff_frame_thr  = 16;
    reg_blck->fmd_diff_frame_thr2 = 912;
    reg_blck->fmd_lock_cnt        = 1;
    reg_blck->fmd_unlock_cnt      = 1;
    reg_blck->fmd_bed_enable      = 1;
    reg_blck->fmd_caf_thr         = 8196;
    reg_blck->fmd_22_caf_thr      = 155;
    reg_blck->fmd_22_caf_thr2     = 155;

    /* TODO: Incase of HQ, this should be 1024 */
    reg_blck->fmd_32_caf_thr = 1800;   /* DEI */

    return;
}

/* Initialization for FMD */
void fmd_init(const fmd_reg_data *reg_blck, fmd_data *fmd_blck)
{
    Double adj_factor;

    /******************************************************************************
     * Retrieve the required configuration control values.
     *                       *
     ******************************************************************************/

    /* Initialization */
    fmd_blck->motcmp32            = 0;
    fmd_blck->diff_field_1fd      = 1024; /* arbitrary non-zero number */
    fmd_blck->caf_1fd             = 0;    /* arbitrary number */
    fmd_blck->diff_frame_1fd      = 0;    /* arbitrary number */
    fmd_blck->diff_frame_array[0] = 1024U;
    fmd_blck->diff_frame_array[1] = 1024U;
    fmd_blck->diff_frame_array[2] = 1024U;
    fmd_blck->diff_frame_array[3] = 1024U;
    fmd_blck->motcmp22            = 0;
    fmd_blck->lock_32             = 0;
    fmd_blck->jam_dir_32          = 0;
    fmd_blck->seq_detect_32       = 0;
    fmd_blck->lock_22             = 0;
    fmd_blck->seq_detect_22       = 0;
    fmd_blck->jam_dir_22          = 0;
    fmd_blck->lock_cnt_32         = 0;
    fmd_blck->unlock_cnt_32       = 0;
    fmd_blck->lock_hsy_32         = 0;
    fmd_blck->lock_cnt_22         = 0;
    fmd_blck->unlock_cnt_22       = 0;
    fmd_blck->lock_hsy_22         = 0;
    fmd_blck->state22             = 0;
    fmd_blck->lock_22_reset       = 0;
    fmd_blck->lock_32_reset       = 0;

    fmd_blck->cad32_state33_sh = 1;    /* State 3:3 */
    fmd_blck->cad32_state12_sh = 0;    /* State 1:2 */
    fmd_blck->cad32_state22_sh = 0;    /* State 2:2 */
    fmd_blck->cad32_state13_sh = 0;    /* State 1:3 */
    fmd_blck->cad32_state23_sh = 0;    /* State 2:3 */

    /******************************************************************************
     * Adjust thresholds according to the picture size and fmd window size.
     *      *
     * Note that the thresholds in fmd are set for picture of 720X240
     *            *
     ******************************************************************************/

    adj_factor =
        (reg_blck->fmd_window_width *
         reg_blck->fmd_window_height) / 720.0 / 240.0;

    fmd_blck->fmd_22_caf_thr      = reg_blck->fmd_22_caf_thr * adj_factor;
    fmd_blck->fmd_22_caf_thr2     = reg_blck->fmd_22_caf_thr2 * adj_factor;
    fmd_blck->fmd_32_caf_thr      = reg_blck->fmd_32_caf_thr * adj_factor;
    fmd_blck->fmd_diff_frame_thr  = reg_blck->fmd_diff_frame_thr * adj_factor;
    fmd_blck->fmd_diff_frame_thr2 = reg_blck->fmd_diff_frame_thr2 * adj_factor;
    fmd_blck->fmd_caf_thr         = reg_blck->fmd_caf_thr * adj_factor;

    return;
}

/**
 ********************************************************************************
 * Film mode detection
 *                                                         *
 *
 *                                                                             *
 * Arguments in:
 *                                                               *
 *      diff_frame: frame difference (difference between two closest fields
 *      with the same fild parity)
 *
 *      diff_field: field difference (difference between two neighboring
 *      fields) caf: combing artifacts
 *
 *      film_rest : 1: reset the state machines
 *
 *
 *                                                                             *
 * Arguments out:
 *                                                              *
 *      film_lock: 0: video mode; 1: film mode
 *                                 *
 *      jam_dir  : 0: jam w/ the previous field; 1: w/ the following field
 *     *
 *
 *                                                                             *
 * Remarks:
 *                                                                    *
 *    FMD software part
 *                                                        *
 ********************************************************************************/
static void fmd_proc(UInt16             *film_lock,
                     UInt16             *jam_dir,
                     UInt64              diff_frame_in,
                     UInt64              diff_field,
                     UInt64              caf,
                     UInt16              fmd_reset,
                     const fmd_reg_data *reg_blck,
                     fmd_data           *fmd_blck)
{
    Double  diff_field_ratio;           /* difference ratio of diff_field */
    Double  diff_diff_field;

    UInt64  min_pre_diff_frame;
    UInt64 *diff_frame_array;
    UInt64  caf_pre, caf_fut;
    UInt64  diff_frame;
    UInt16  i;

    diff_frame_array = &fmd_blck->diff_frame_array[0];

    /* caf_pre is one field delay of caf_fut */
    if (reg_blck->mdt_num_field_mode <= 1) /* 4-field MDT */
    {
        caf_pre    = caf;
        caf_fut    = 0;                         /* just make it smaller than
                                                 *caf_Th */
        diff_frame = diff_frame_in;             /* No delay for diff_frame */
    }
    else                                        /* 5-field MDT */
    {
        caf_pre    = fmd_blck->caf_1fd;
        caf_fut    = caf;
        diff_frame = fmd_blck->diff_frame_1fd;  /* one field delay for
                                                 *diff_frame */

        /* deay caf and diff_frame by one field */
        fmd_blck->caf_1fd        = caf;
        fmd_blck->diff_frame_1fd = diff_frame_in;
    }

    /*  fmd_blck->caf_pre = fmd_blck->caf_fut; */
    /*  fmd_blck->caf_fut = caf; */

    /******************************************************************
     * Determine 3:2 motion compare value.                            *
     ******************************************************************/

    /* Obtain the minimum of the previous four diff_frame */
    min_pre_diff_frame = min4(diff_frame_array);

    /* Note that 1) different conditions are set for locked or non-locked cases.
     *           2) different conditions are set for state23_sh state (when
     *              diff_frame is supposed to be small if it is 3:2 film source)
     *              and the other states. Threshold setting:
     *              fmd_diff_frame_thr < fmd_diff_frame_thr2
     */

    fmd_blck->motcmp32 = 0;
    if (diff_frame > fmd_blck->fmd_diff_frame_thr2)
    {
        /* diff_frame is great enough */
        fmd_blck->motcmp32 = 1;
    }
    if ((!((Bool) fmd_blck->cad32_state23_sh)) &&
        ((diff_frame>>1) > min_pre_diff_frame) &&
        (diff_frame > fmd_blck->fmd_diff_frame_thr))
    {
        /* diff_frame is relatively great and much greater than
         * min_pre_diff_frame. */
        fmd_blck->motcmp32 = 1;
    }
    if (fmd_blck->cad32_state23_sh)
    {
        if ((!((Bool) fmd_blck->lock_32)) && (diff_frame>min_pre_diff_frame))
        {
            /* diff_frame > min_pre_diff_frame, if not locked */
            fmd_blck->motcmp32 = 1;
        }
        if (((Bool) (fmd_blck->lock_32)) &&
            ((Bool) (diff_frame > ((UInt64) fmd_blck->fmd_diff_frame_thr<<1))) &&
            ((Bool) (diff_frame > min_pre_diff_frame)))
        {
            /* diff_frame > min_pre_diff_frame, if diff_frame is larger than
             * 2*fmd_diff_frame_thr */
            fmd_blck->motcmp32 = 1;
        }
        if ((diff_frame > fmd_blck->fmd_diff_frame_thr) &&
            ((diff_frame>>1) > min_pre_diff_frame))
        {
            /* diff_frame/2 > min_pre_diff_frame, if diff_frame is larger than
             * fmd_diff_frame_thr */
            fmd_blck->motcmp32 = 1;
        }
        if (caf_pre > fmd_blck->fmd_32_caf_thr)
        {
            /* caf_pre is very large */
            fmd_blck->motcmp32 = 1;
        }
        if ((caf_pre > ((UInt64) fmd_blck->fmd_32_caf_thr>>2)) &&
            ((caf_pre>>4) > caf_fut))
        {
            /* caf_pre is relatively large and caf_pre is much larger than
             * caf_fut */
            fmd_blck->motcmp32 = 1;
        }
    }

    /* Calcuate the minimum diff_frame */
    for (i = 0; i < 3U; i++)
    {
        diff_frame_array[i] = diff_frame_array[i + 1U];
    }
    diff_frame_array[3] = diff_frame;

    /******************************************************************
     * Determine 2:2 motion compare value.                            *
     ******************************************************************/

    /* Calculate the difference ratio of diff_field */
    if (fmd_blck->diff_field_1fd != 0)
    {
        Double tempDiff = ((Double) diff_field -
                           (Double) fmd_blck->diff_field_1fd);
        diff_field_ratio =
            (Double) ((tempDiff *
                       (Double) 16.0) / (Double) fmd_blck->diff_field_1fd);
        tempDiff =
            ((Double) diff_field - (Double) fmd_blck->diff_field_1fd);
        diff_diff_field =
            (Double) (tempDiff * (Double) 16.0);
    }
    else
    {
        diff_field_ratio = (Double) 1023;      /* an arbitrary large number */
        diff_diff_field  = (Double) 2000000;   /* an arbitrary large number */
    }

    if (diff_field < fmd_blck->diff_field_1fd)
    {
        diff_field_ratio = -diff_field_ratio;
        diff_diff_field  = -diff_diff_field;
    }

    /* The 2nd-4th lines are to deal with slow motion or still sequences
     * (That is, diff_field and diff_field_1fd are close, and diff_frame is
     ************very
     * small)
     * Threshold setting: fmd_22_caf_thr < fmd_22_caf_thr2 */
    if ((((Bool) ((diff_field + (diff_field >> 1)) <
                  fmd_blck->diff_field_1fd)) &&
         ((Bool) (caf_pre < (UInt64) fmd_blck->fmd_22_caf_thr2))) ||
        (((((Bool) (diff_field < fmd_blck->diff_field_1fd)) &&
           ((Bool) ((((Double) (diff_frame) *
                      (Double) (fmd_blck->diff_field_1fd))) <
                    (((Double) (diff_diff_field) *
                      (Double) (fmd_blck->fmd_diff_frame_thr2))))))
          || (((Bool) (diff_field < ((UInt64) (fmd_blck->diff_field_1fd +
                                               (fmd_blck->diff_field_1fd >>
                                                4))))) &&
              ((Bool) (diff_frame < (UInt64) fmd_blck->fmd_diff_frame_thr))))
         && ((Bool) (((Bool) (((Bool) (fmd_blck->state22 == (UInt16) 0U)) &&
                              ((Bool) (caf_fut <
                                       ((UInt64) fmd_blck->fmd_22_caf_thr)))))
                     ||
                     ((Bool) (((Bool) (fmd_blck->state22 == (UInt16) 1U))
                              && ((Bool) (caf_pre <
                                          (UInt64) fmd_blck->fmd_22_caf_thr))))))))
    {
        fmd_blck->motcmp22 = 0;
    }
    else if (((Bool) (caf_fut < fmd_blck->fmd_22_caf_thr2)) &&
             ((Bool) (((Bool) (diff_field >
                               ((UInt64) (fmd_blck->diff_field_1fd +
                                          (fmd_blck->diff_field_1fd >>
                                           1))))) ||
                      (((((Bool) (diff_field > fmd_blck->diff_field_1fd)) &&
                         ((Bool) (((Double) (diff_frame) *
                                   (Double) (fmd_blck->diff_field_1fd)) <
                                  ((Double) (diff_diff_field) *
                                   (Double) (fmd_blck->fmd_diff_frame_thr2)))))
                        &&
                        ((Bool) (((Double) (caf_fut) *
                                  (Double) (fmd_blck->diff_field_1fd)) <
                                 ((Double) (diff_diff_field) *
                                  (Double) (fmd_blck->fmd_22_caf_thr)))))))))
    {
        fmd_blck->motcmp22 = 1;
    }
    else
    {
        fmd_blck->lock_22_reset = 1;
    }

    /* diff_field_1fd is one field delay of diff_field */
    fmd_blck->diff_field_1fd = diff_field;

    /******************************************************************
     * perform film mode detection (state machine process)            *
     ******************************************************************/

    /* Perform 3:2 pull-down state machine */
    film32detection(fmd_blck);

    /* Perform 2:2 pull-down state machine */
    film22detection(fmd_blck);

    /* disable the reset signals */
    fmd_blck->lock_22_reset = 0;
    fmd_blck->lock_32_reset = 0;

    /******************************************************************
     * Manage hysteresis counters.                                    *
     ******************************************************************/

    if (fmd_blck->lock_32 == 1)
    {
        ++(fmd_blck->lock_cnt_32);
        if (fmd_blck->lock_cnt_32 > 127)
        {
            fmd_blck->lock_cnt_32 = 127;
        }

        fmd_blck->unlock_cnt_32 = 0;
    }
    else
    {
        ++(fmd_blck->unlock_cnt_32);
        if (fmd_blck->unlock_cnt_32 > 31)
        {
            fmd_blck->unlock_cnt_32 = 31;
        }

        fmd_blck->lock_cnt_32 = 0;
    }

    if (fmd_blck->lock_22 == 1)
    {
        ++(fmd_blck->lock_cnt_22);
        if (fmd_blck->lock_cnt_22 > 127)
        {
            fmd_blck->lock_cnt_22 = 127;
        }

        fmd_blck->unlock_cnt_22 = 0;
    }
    else
    {
        ++(fmd_blck->unlock_cnt_22);
        if (fmd_blck->unlock_cnt_22 > 31)
        {
            fmd_blck->unlock_cnt_22 = 31;
        }

        fmd_blck->lock_cnt_22 = 0;
    }

    /******************************************************************
     * Determine lock from the hysteresis counters.                   *
     ******************************************************************/

    if (fmd_blck->lock_cnt_32 >= reg_blck->fmd_lock_cnt)
    {
        fmd_blck->lock_hsy_32 = 1;
        /* to reset 2-2 lock counter */
        fmd_blck->lock_cnt_22 = 0;
    }
    else if (fmd_blck->unlock_cnt_32 >= reg_blck->fmd_unlock_cnt)
    {
        fmd_blck->lock_hsy_32 = 0;
    }
    else
    {
        /* Do nothing */
    }

    if (fmd_blck->lock_cnt_22 >= (reg_blck->fmd_lock_cnt + 3))
    {
        fmd_blck->lock_hsy_22 = 1;
    }
    else if (fmd_blck->unlock_cnt_22 >= reg_blck->fmd_unlock_cnt)
    {
        fmd_blck->lock_hsy_22 = 0;
    }
    else
    {
        /* Do nothing */
    }

    /******************************************************************
     * Film mode enable short.                                        *
     ******************************************************************/

    *film_lock = (fmd_blck->lock_hsy_32 | fmd_blck->lock_hsy_22);
    *jam_dir   =
        fmd_blck->lock_hsy_32 ? fmd_blck->jam_dir_32 : fmd_blck->jam_dir_22;

    /* Perform combing artifacts detection */
    if (((Bool) fmd_reset) ||
        (((Bool) (((Bool) reg_blck->fmd_bed_enable) &&
                  ((Bool) (*film_lock == ((UInt16) 1))))) &&
         (((Bool) (((Bool) (*jam_dir == 0)) &&
                   ((Bool) (caf_pre > (UInt64) fmd_blck->fmd_caf_thr)))) ||
          ((Bool) (((Bool) (*jam_dir == ((UInt16) 1))) &&
                   ((Bool) (caf_fut > ((UInt64) fmd_blck->fmd_caf_thr))))))))
    {
        *film_lock = 0;
        fmd_blck->lock_cnt_32   = 0;
        fmd_blck->lock_cnt_22   = 0;
        fmd_blck->lock_22_reset = 1;
        fmd_blck->lock_32_reset = 1;
    }
}

/******************************************************************
 * Perfom 3:2 pull-down state machine.                            *
 ******************************************************************/
static void film32detection(fmd_data *fmd_blck) {
    UInt16 sh_code;                     /* state machine code */

    sh_code =
        (UInt16) (fmd_blck->lock_32 <<
                  2) +
        (UInt16) (fmd_blck->motcmp32 << 1) + fmd_blck->seq_detect_32;

    if (fmd_blck->lock_32_reset)
    {
        fmd_blck->cad32_state12_sh = 0;
        fmd_blck->cad32_state22_sh = 0;
        fmd_blck->cad32_state13_sh = 0;
        fmd_blck->cad32_state23_sh = 0;
        fmd_blck->cad32_state33_sh = 1;
        fmd_blck->lock_32          = 0;
        fmd_blck->jam_dir_32       = 0;
        fmd_blck->seq_detect_32    = 0;
    }
    else if (fmd_blck->cad32_state33_sh == 1)
    {
        if ((sh_code == 1U) || (sh_code == 0))
        {
            fmd_blck->lock_32       = 0;
            fmd_blck->jam_dir_32    = 0;
            fmd_blck->seq_detect_32 = 0;
        }
        else if (sh_code == 2U)
        {
            fmd_blck->cad32_state33_sh = 0;
            fmd_blck->cad32_state12_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 1;
        }
        else if ((sh_code == 3U) || (sh_code == 6U) || (sh_code == 7U))
        {
            fmd_blck->cad32_state33_sh = 0;
            fmd_blck->cad32_state12_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 1;
        }
        else
        {
            fmd_blck->cad32_state33_sh = 0;
            fmd_blck->cad32_state12_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 0;
        }
    }
    else if (fmd_blck->cad32_state12_sh == 1)
    {
        if ((sh_code == 0) || (sh_code == 1U))
        {
            fmd_blck->cad32_state12_sh = 0;
            fmd_blck->cad32_state33_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 0;
        }
        else if ((sh_code == 2U) || (sh_code == 3U))
        {
            fmd_blck->cad32_state12_sh = 0;
            fmd_blck->cad32_state22_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 1;
        }
        else if ((sh_code == 6U) || (sh_code == 7U))
        {
            fmd_blck->cad32_state12_sh = 0;
            fmd_blck->cad32_state22_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 1;
        }
        else
        {
            fmd_blck->cad32_state12_sh = 0;
            fmd_blck->cad32_state22_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 0;
        }
    }
    else if (fmd_blck->cad32_state22_sh == 1)
    {
        if ((sh_code == 0) || (sh_code == 1U))
        {
            fmd_blck->cad32_state22_sh = 0;
            fmd_blck->cad32_state33_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 0;
        }
        else if ((sh_code == 2U) || (sh_code == 3U))
        {
            fmd_blck->cad32_state22_sh = 0;
            fmd_blck->cad32_state13_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 1;
        }
        else if ((sh_code == 6U) || (sh_code == 7U))
        {
            fmd_blck->cad32_state22_sh = 0;
            fmd_blck->cad32_state13_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 1;
        }
        else
        {
            fmd_blck->cad32_state22_sh = 0;
            fmd_blck->cad32_state13_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 0;
        }
    }
    else if (fmd_blck->cad32_state13_sh == 1)
    {
        if ((sh_code == 0) || (sh_code == 1U))
        {
            fmd_blck->cad32_state13_sh = 0;
            fmd_blck->cad32_state33_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 0;
        }
        else if ((sh_code == 2U) || (sh_code == 3U))
        {
            fmd_blck->cad32_state13_sh = 0;
            fmd_blck->cad32_state23_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 1;
        }
        else if ((sh_code == 6U) || (sh_code == 7U))
        {
            fmd_blck->cad32_state13_sh = 0;
            fmd_blck->cad32_state23_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 1;
        }
        else
        {
            fmd_blck->cad32_state13_sh = 0;
            fmd_blck->cad32_state23_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 1;
            fmd_blck->seq_detect_32    = 0;
        }
    }
    else
    {
        if (sh_code == 0)
        {
            fmd_blck->cad32_state23_sh = 0;
            fmd_blck->cad32_state33_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 0;
        }
        else if (sh_code == 1U)
        {
            fmd_blck->cad32_state23_sh = 0;
            fmd_blck->cad32_state33_sh = 1;
            fmd_blck->lock_32          = 0;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 1;
        }
        else if ((sh_code == 4U) || (sh_code == 5U))
        {
            fmd_blck->cad32_state23_sh = 0;
            fmd_blck->cad32_state33_sh = 1;
            fmd_blck->lock_32          = 1;
            fmd_blck->jam_dir_32       = 0;
            fmd_blck->seq_detect_32    = 1;
        }
        else      /* stay in state 2:3 */
        {         /* state23_sh = 0; */
                  /* state33_sh = 1; */
            fmd_blck->lock_32       = 0;
            fmd_blck->jam_dir_32    = 0;
            fmd_blck->seq_detect_32 = 0;
        }
    }
}

/******************************************************************
 * Perfom 2:2 pull-down state machine.                            *
 ******************************************************************/
static void film22detection(fmd_data *fmd_blck) {
    UInt16 fh_code;                   /* 2:2 state machine code */

    fh_code =
        (UInt16) (fmd_blck->lock_22 <<
                  2) +
        (UInt16) (fmd_blck->motcmp22 << 1) + fmd_blck->seq_detect_22;

    if (fmd_blck->lock_22_reset)
    {
        fmd_blck->state22       = 0;
        fmd_blck->lock_22       = 0;
        fmd_blck->jam_dir_22    = 0;
        fmd_blck->seq_detect_22 = 0;
    }
    else if (fmd_blck->state22 == 0)
    {
        if ((fh_code == 2U) || (fh_code == 3U))
        {
            fmd_blck->state22       = 1;
            fmd_blck->lock_22       = 0;
            fmd_blck->jam_dir_22    = 1;
            fmd_blck->seq_detect_22 = 1;
        }
        else if ((fh_code == 6U) || (fh_code == 7U))
        {
            fmd_blck->state22       = 1;
            fmd_blck->lock_22       = 1;
            fmd_blck->jam_dir_22    = 1;
            fmd_blck->seq_detect_22 = 1;
        }
        else if ((fh_code == 4U) || (fh_code == 5U))
        {
            fmd_blck->state22       = 1;
            fmd_blck->lock_22       = 1;
            fmd_blck->jam_dir_22    = 1;
            fmd_blck->seq_detect_22 = 0;
        }
        else
        {
            fmd_blck->lock_22       = 0;
            fmd_blck->jam_dir_22    = 0;
            fmd_blck->seq_detect_22 = 0;
        }
    }
    else
    {
        fmd_blck->state22 = 0;
        if ((fh_code == 1U) || (fh_code == 5U))
        {
            fmd_blck->lock_22       = 1;
            fmd_blck->jam_dir_22    = 0;
            fmd_blck->seq_detect_22 = 1;
        }
        else if ((fh_code == 0) || (fh_code == 4U))
        {
            fmd_blck->jam_dir_22    = 0;
            fmd_blck->seq_detect_22 = 1;
        }
        else
        {
            fmd_blck->lock_22       = 0;
            fmd_blck->jam_dir_22    = 0;
            fmd_blck->seq_detect_22 = 0;
        }
    }
}

static UInt64 min4(const UInt64 *x)
{
    UInt32 i;
    UInt64 x_min;

    x_min = x[0];
    for (i = 1U; i < 4U; i++)
    {
        if (x_min > x[i])
        {
            x_min = x[i];
        }
    }

    return x_min;
}

