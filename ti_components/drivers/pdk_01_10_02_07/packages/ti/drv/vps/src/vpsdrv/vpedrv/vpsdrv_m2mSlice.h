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
 *
 *  \brief VPS M2M SubFrame level processing internal header file.
 *
 */

#ifndef VPSDRV_M2MSLICE_H_
#define VPSDRV_M2MSLICE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** struct VpsMdrv_SubFrameChParams
 *  \brief Strucutre containing subframe processing channel instance. This is
 *   initialised for first subframe and will be used and updated for subsequent
 *   subframes
 */
typedef struct
{
    /*
     * Subframe configuration : subframe mdoe enable flag and subframe size
     * in No of Lines
     */
    UInt32 subFrameEnable;
    UInt16 slcSz;
    UInt16 noOfSlcs;

    /*
     * Source and target frame height and Widh Info, used for sc phase
     * calculation per subframe
     */
    UInt32 srcFrmH;
    UInt32 tarFrmH;
    UInt32 srcFrmW;
    UInt32 tarFrmW;

    /* Subframe related information  */
    UInt16 subFrameNum;
    UInt16 slcLnsAvailable;
    UInt16 srcH;
    UInt16 tarH;

    /* Buffer offsets of subframe from frame start address */
    UInt16 srcBufOffset;
    UInt16 tarBufOffset;
    UInt16 rowOffset;

    /*
     * Parameters which affects per subframe Sc phase info and buffer
     * offset calculation
     */
    UInt32 filtType;
    /**< vertical scaling filter type: RAV/PolyPhase
     *   For valid values see #Vps_ScVertScalerType. */
    UInt32 dataFmt;
    /**< input buffer format 422/420 */
    UInt16 chrUsLnMemSlcTop;
    UInt16 chrUsLnMemSlcBtm;
    /***< This value is used for Luma and 1/2 of this is used for Chroma*/
    UInt16 scCropLnsTop;
    UInt16 scCropLnsBtm;

    /* Scaler phase offset values based on filter type */
    /* polyphase */
    Int32  rowAccIncr;
    Int32  rowAccOffset;
    Int32  rowAccOffsetB;
    Int32  rowAcc;
    /* RAV */
    UInt32 ravScFactor;
    Int32  ravRowAccInit;
    Int32  ravRowAccInitB;
    UInt16 ravMaxSrcHtPerSlc;
} VpsMdrv_SubFrameChInst;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void vpsMdrvScSubFrameInitInfo(VpsMdrv_SubFrameChInst *slcData);
void vpsMdrvScSubFrameCalcInfo(VpsMdrv_SubFrameChInst *slcData);
void vpsMdrvScSubFrameCalcPostProcInfo(VpsMdrv_SubFrameChInst *slcData);

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MSLICE_H_ */
