/******************************************************************************
Copyright (c) [2012 - 2018] Texas Instruments Incorporated

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

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/common/chains_radar_util_read_params.h>

static ChainsUtil_MasterFileInfo gMstFileInfo;
static UInt32 mstFileInfoValid = 0U;

Int32 ChainsUtil_readSensorFileInfo(const char *rootDirName,
                                    const char *sensorFileName,
                                    ChainsUtil_ConfigFileInfo  * cfgInfo)
{
    char        valueSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char        sLine[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char        fileName[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char      * pValueStr;
    char      * pSLine;
    char      * name;
    Int32       fd;
    UInt32      id;
    Bool        done = FALSE;
    Int32       status = SYSTEM_LINK_STATUS_SOK;

    pValueStr = &valueSt[0];
    pSLine    = &sLine[0];

    sprintf(fileName,"%s%s", rootDirName, sensorFileName);

    Vps_printf("Parsing %s\n", fileName);

    fd = File_open(fileName,"r");

    if(fd != SYSTEM_LINK_STATUS_EFAIL)
    {
        memset(cfgInfo, 0, sizeof(ChainsUtil_ConfigFileInfo));

        while (done != TRUE)
        {
            pSLine = File_gets(pSLine, CHAINS_RADAR_UTIL_MAX_LINE_LEN, fd);
            if( pSLine == NULL )
            {
                done = TRUE;
            }
            else
            {
                if (strchr(pSLine, '#') || !strcmp(pSLine, "\n"))
                {
                    continue;
                }
                sscanf(pSLine,"%d %s", &id, pValueStr);
                name = cfgInfo->fileName[id];
                strcpy(name, pValueStr);
            }
        }
        status = File_close(fd);
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}

static Int32 ChainsUtil_readMasterFileInfo(const char *rootDirName,
                                           ChainsUtil_MasterFileInfo  *mstInfo)
{
    char        paramSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char        valueSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char        sLine[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char        fileName[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char      * pParamStr;
    char      * pValueStr;
    char      * pSLine;
    Int32       fd;
    Bool        done = FALSE;
    Int32       status = SYSTEM_LINK_STATUS_SOK;


    pParamStr = &paramSt[0];
    pValueStr = &valueSt[0];
    pSLine    = &sLine[0];

    sprintf(fileName,"%s%s", rootDirName, MASTER_SENSOR_CONFIG_FILENAME);
    Vps_printf("Parsing %s\n", fileName);

    fd = File_open(fileName,"r");

    if (fd != SYSTEM_LINK_STATUS_EFAIL)
    {
        memset(mstInfo, 0, sizeof(ChainsUtil_MasterFileInfo));
        while (done != TRUE)
        {
            pSLine = File_gets(pSLine, CHAINS_RADAR_UTIL_MAX_LINE_LEN, fd);
            if( pSLine == NULL )
            {
                done = TRUE;
            }
            else
            {
                if (strchr(pSLine, '#') || !strcmp(pSLine, "\n"))
                {
                    continue;
                }
                sscanf(pSLine,"%s %s",pParamStr, pValueStr);
                if (strcmp(pParamStr, "FE_PARAMS") == 0)
                {
                    strcpy(mstInfo->feMaster, pValueStr);
                }
                else if (strcmp(pParamStr, "FFT_PARAMS") == 0)
                {
                    strcpy(mstInfo->fftMaster, pValueStr);
                }
                else if (strcmp(pParamStr, "DSPALGO_PARAMS") == 0)
                {
                    strcpy(mstInfo->dspAlgoMaster, pValueStr);
                }
                else if (strcmp(pParamStr, "NUM_SENSORS") == 0)
                {
                    mstInfo->numSensors = atoi(pValueStr);
                }
            }
        }
        Vps_printf("NUM_SENSORS = %d\n", mstInfo->numSensors);
        if (mstInfo->feMaster[0])
        {
            Vps_printf("FE_PARAMS = %s\n", mstInfo->feMaster);
        }
        if (mstInfo->fftMaster[0])
        {
            Vps_printf("FFT_PARAMS = %s\n", mstInfo->fftMaster);
        }
        if (mstInfo->dspAlgoMaster[0])
        {
            Vps_printf("DSPALGO_PARAMS = %s\n", mstInfo->dspAlgoMaster);
        }
        status = File_close(fd);
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}

const ChainsUtil_MasterFileInfo *ChainsUtil_getMstFileInfo(const char *rootDirName)
{
    Int32 status;
    ChainsUtil_MasterFileInfo *pFile = &gMstFileInfo;

    if (0U == mstFileInfoValid)
    {
        status = ChainsUtil_readMasterFileInfo(rootDirName, &gMstFileInfo);
        if (status != SYSTEM_LINK_STATUS_SOK)
        {
            pFile = NULL;
        }
    }

    return pFile;
}

static Void *ChainsUtil_readCfgFile(const char *rootDirName,
                                    const char *cfgFileName,
                                    UInt32 *pFileSize)
{
    char fileName[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    Int32 fd, size;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    Void *pCfgFileBuf;

    sprintf(fileName,"%s%s", rootDirName, cfgFileName);

    Vps_printf("Parsing Front End Config File: %s\n", fileName);

    fd = File_open(fileName,"r");
    if (fd != SYSTEM_LINK_STATUS_EFAIL)
    {
        size = File_size(fd);
        if (size != SYSTEM_LINK_STATUS_EFAIL)
        {
            pCfgFileBuf = malloc(size);
            if (pCfgFileBuf != NULL)
            {
                status = File_read(fd, (UInt8 *) pCfgFileBuf, (UInt32) size, pFileSize);
                if (status != SYSTEM_LINK_STATUS_SOK)
                {
                    free(pCfgFileBuf);
                    pCfgFileBuf = NULL;
                    *pFileSize = 0;
                }
            }
        }
        File_close(fd);
    }

    return pCfgFileBuf;
}

Void ChainsUtil_readFeParams(Void *feCfgFileBuf,
                             UInt32 fileSize,
                             rlFrontEndCfg_t * cfgParams)
{
    char                    paramSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                    valueSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                  * pParamStr;
    char                  * pValueStr;
    char                  * pSLine;
    rlChirpCfg_t          * chirpCfg;
    rlProfileCfg_t        * profileCfg;
    rlAdvFrameSeqCfg_t    * frameSeq;
    rlAdvFrameDataCfg_t   * frameData;
    rlSubFrameDataCfg_t   * subFrameDataCfg;
    rlSubFrameCfg_t       * subFrameCfg;
    UInt8                   numSubFrames;
    UInt8                   forceProfile;
    UInt8                   version;
    Bool                    done = FALSE;
    Void                  * pLineEndFp;
    UInt32                  bufSize, maxLineSize;

    pParamStr       = &paramSt[0];
    pValueStr       = &valueSt[0];
    frameSeq        = &cfgParams->advFrameCfgArgs.frameSeq;
    frameData       = &cfgParams->advFrameCfgArgs.frameData;
    chirpCfg        = NULL;
    profileCfg      = NULL;
    subFrameCfg     = NULL;
    subFrameDataCfg = NULL;
    version         = 1;
    bufSize         = fileSize;

    memset(cfgParams, 0, sizeof(rlFrontEndCfg_t));

    pSLine = feCfgFileBuf;
    while (done != TRUE)
    {
        if(bufSize > CHAINS_RADAR_UTIL_MAX_LINE_LEN)
        {
            maxLineSize = CHAINS_RADAR_UTIL_MAX_LINE_LEN;
        }
        else
        {
            maxLineSize = bufSize;
        }

        pLineEndFp = memchr(pSLine, (UInt8) '\n', maxLineSize);
        if (pLineEndFp != NULL)
        {
            bufSize = fileSize - ((UInt32) pLineEndFp - (UInt32) feCfgFileBuf);
        }
        else
        {
            done = TRUE;
            continue;
        }

        if ((pSLine[0] == '#') || (pSLine[0] == '\r'))
        {
            pSLine = pLineEndFp;
            pSLine++;
            continue;
        }

        sscanf(pSLine,"%s %s",pParamStr, pValueStr);

        if (strcmp(pParamStr, "version") == 0)
        {
            version = (UInt8)atoi(pValueStr);
            (void)version;
        }
        else if (strcmp(pParamStr, "laneClkCfg") == 0)
        {
            cfgParams->dataPathClk.laneClkCfg = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "dataRate") == 0)
        {
            cfgParams->dataPathClk.dataRate = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "hsiClk") == 0)
        {
            cfgParams->hsiClkCfgArgs.hsiClk = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numProfileCfg") == 0)
        {
            cfgParams->numProfileCfg = atoi(pValueStr);

            UTILS_assert(cfgParams->numProfileCfg <=
                         RADAR_LINK_MAX_NUM_PROFILE_CONFIG);
        }
        else if (strcmp(pParamStr, "profileCfgProfileId") == 0)
        {
            UInt8 v = atoi(pValueStr);

            UTILS_assert(v < RADAR_LINK_MAX_NUM_PROFILE_CONFIG);

            profileCfg = &cfgParams->profileCfgArgs[v];
            memset(profileCfg, 0, sizeof(rlProfileCfg_t));

            profileCfg->profileId = v;
        }
        else if (strcmp(pParamStr, "hpfCornerFreq1") == 0)
        {
            if (strcmp(pValueStr, "RL_RX_HPF1_175_KHz") == 0)
            {
                profileCfg->hpfCornerFreq1 = RL_RX_HPF1_175_KHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF1_235_KHz") == 0)
            {
                profileCfg->hpfCornerFreq1 = RL_RX_HPF1_235_KHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF1_350_KHz") == 0)
            {
                profileCfg->hpfCornerFreq1 = RL_RX_HPF1_350_KHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF1_700_KHz") == 0)
            {
                profileCfg->hpfCornerFreq1 = RL_RX_HPF1_700_KHz;
            }
            else
            {
                profileCfg->hpfCornerFreq1 = atoi(pValueStr);
            }
        }
        else if (strcmp(pParamStr, "hpfCornerFreq2") == 0)
        {
            if (strcmp(pValueStr, "RL_RX_HPF2_350_KHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_350_KHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF2_700_KHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_700_KHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF2_1p4_MHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_1p4_MHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF2_2p8_MHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_2p8_MHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF2_5p0_MHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_5p0_MHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF2_7p5_MHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_7p5_MHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF2_10_MHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_10_MHz;
            }
            else if (strcmp(pValueStr, "RL_RX_HPF2_15_MHz") == 0)
            {
                profileCfg->hpfCornerFreq2 = RL_RX_HPF2_15_MHz;
            }
            else
            {
                profileCfg->hpfCornerFreq2 = atoi(pValueStr);
            }
        }
        else if (strcmp(pParamStr, "rxGain") == 0)
        {
            profileCfg->rxGain = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "digOutSampleRate") == 0)
        {
            profileCfg->digOutSampleRate = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numAdcSamples") == 0)
        {
            profileCfg->numAdcSamples = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "adcStartTimeUSec") == 0)
        {
            profileCfg->adcStartTimeConst =
                                      atoi(pValueStr) * 100;
        }
        else if (strcmp(pParamStr, "idleTimeUSec") == 0)
        {
            profileCfg->idleTimeConst = atoi(pValueStr) * 100;
        }
        else if (strcmp(pParamStr, "rampEndTimeUSec") == 0)
        {
            profileCfg->rampEndTime = atoi(pValueStr) * 100;
        }
        else if (strcmp(pParamStr, "startFreqGhz") == 0)
        {
            profileCfg->startFreqConst =
                (UInt32) ((atof(pValueStr) * (1U << 26)) / 3.6);
        }
        else if (strcmp(pParamStr, "txOutPowerBackoffCode") == 0)
        {
            profileCfg->txOutPowerBackoffCode = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "txPhaseShifter") == 0)
        {
            profileCfg->txPhaseShifter = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "freqSlopeConstMhzPerUSec") == 0)
        {
            profileCfg->freqSlopeConst =
                (UInt32)(atof(pValueStr) * (1U << 26) / (3.6*1e3*900));
        }
        else if (strcmp(pParamStr, "txStartTimeUSec") == 0)
        {
            profileCfg->txStartTime = atoi(pValueStr) * 100;
        }
        else if (strcmp(pParamStr, "numChirpCfg") == 0)
        {
            cfgParams->numChirpCfg = atoi(pValueStr);

            UTILS_assert(cfgParams->numChirpCfg <=
                         CHAINS_RADAR_MAX_NUM_CHIRP_CFG);
        }
        else if (strcmp(pParamStr, "chirpCfgArgsID") == 0)
        {
            UInt8 v = atoi(pValueStr);

            UTILS_assert(v < (CHAINS_RADAR_MAX_NUM_CHIRP_CFG - 1));

            chirpCfg = &cfgParams->chirpCfgArgs[v];
            memset(chirpCfg, 0, sizeof(rlChirpCfg_t));

        }
        else if (strcmp(pParamStr, "chirpCfgProfileId") == 0)
        {
            UInt16    v = atoi(pValueStr);
            chirpCfg->profileId = v;
        }
        else if (strcmp(pParamStr, "chirpStartIdx") == 0)
        {
            UInt16    v = atoi(pValueStr);

            chirpCfg->chirpStartIdx = v;
        }
        else if (strcmp(pParamStr, "chirpEndIdx") == 0)
        {
            UInt16    v = atoi(pValueStr);

            chirpCfg->chirpEndIdx = v;
        }
        else if (strcmp(pParamStr, "adcStartTimeVarUSec") == 0)
        {
            chirpCfg->adcStartTimeVar = atoi(pValueStr) * 100;
        }
        else if (strcmp(pParamStr, "idleTimeVarUSec") == 0)
        {
            chirpCfg->idleTimeVar = atoi(pValueStr) * 100;
        }
        else if (strcmp(pParamStr, "txEnable") == 0)
        {
            chirpCfg->txEnable = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "startFreqVarHz") == 0)
        {
            chirpCfg->startFreqVar =
                atoi(pValueStr) * (1<<26) / (3.6*1e9);
        }
        else if (strcmp(pParamStr, "freqSlopeVarHz") == 0)
        {
            chirpCfg->freqSlopeVar =
                atoi(pValueStr) * (1<<26) / (3.6*1e9*900);
        }
        else if (strcmp(pParamStr, "numFrames") == 0)
        {
            cfgParams->frameCfgArgs.numFrames = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numLoops") == 0)
        {
            cfgParams->frameCfgArgs.numLoops = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "triggerSelect") == 0)
        {
            if (strcmp(pValueStr, "RL_FRAMESTRT_API_TRIGGER") == 0)
            {
                cfgParams->frameCfgArgs.triggerSelect = RL_FRAMESTRT_API_TRIGGER;
            }
            else if (strcmp(pValueStr, "RL_FRAMESTRT_SYNCIN_TRIGGER") == 0)
            {
                cfgParams->frameCfgArgs.triggerSelect = RL_FRAMESTRT_SYNCIN_TRIGGER;
            }
            else
            {
                cfgParams->frameCfgArgs.triggerSelect = atoi(pValueStr);
            }
        }
        else if (strcmp(pParamStr, "framePeriodicity") == 0)
        {
            cfgParams->frameCfgArgs.framePeriodicity = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "frameTriggerDelay") == 0)
        {
            cfgParams->frameCfgArgs.frameTriggerDelay = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "frameChirpStartIdx") == 0)
        {
            cfgParams->frameCfgArgs.chirpStartIdx = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "frameChirpEndIdx") == 0)
        {
            cfgParams->frameCfgArgs.chirpEndIdx = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "txAntEnableMask") == 0)
        {
            cfgParams->txAntEnableMask = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "rxAntEnableMask") == 0)
        {
            cfgParams->rxAntEnableMask = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "transferFmtPkt0") == 0)
        {
            cfgParams->dataPathCfgArgs.transferFmtPkt0 = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "transferFmtPkt1") == 0)
        {
            cfgParams->dataPathCfgArgs.transferFmtPkt1 = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "enableAdvFrameCfg") == 0)
        {
            cfgParams->enableAdvFrameCfg = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numSubFrames") == 0)
        {
            numSubFrames = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "forceProfile") == 0)
        {
            forceProfile = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "subFrameIndex") == 0)
        {
            UInt8 v = atoi(pValueStr);

            UTILS_assert(v <= RL_MAX_SUBFRAMES);

            subFrameCfg     = &frameSeq->subFrameCfg[v];
            subFrameDataCfg = &frameData->subframeDataCfg[v];

            memset(subFrameCfg, 0, sizeof(rlSubFrameCfg_t));
            memset(subFrameDataCfg, 0, sizeof(rlSubFrameDataCfg_t));
        }
        else if (strcmp(pParamStr, "forceProfileIdx") == 0)
        {
            subFrameCfg->forceProfileIdx = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "sf_chirpStartIdx") == 0)
        {
            subFrameCfg->chirpStartIdx = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numOfChirps") == 0)
        {
            subFrameCfg->numOfChirps = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "sf_numLoops") == 0)
        {
            subFrameCfg->numLoops = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "chirpStartIdxOffset") == 0)
        {
            subFrameCfg->chirpStartIdxOffset = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numOfBurst") == 0)
        {
            subFrameCfg->numOfBurst = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numOfBurstLoops") == 0)
        {
            subFrameCfg->numOfBurstLoops = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "numChirpsInDataPacket") == 0)
        {
            subFrameDataCfg->numChirpsInDataPacket = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "burstPeriodicity") == 0)
        {
            subFrameCfg->burstPeriodicity = atoi(pValueStr);
        }
        else if (strcmp(pParamStr, "subFramePeriodicity") == 0)
        {
            subFrameCfg->subFramePeriodicity = atoi(pValueStr);
        }
        pSLine = pLineEndFp;
        pSLine++;
    }

    if ( cfgParams->enableAdvFrameCfg )
    {
        UInt32    i;

        frameSeq->numOfSubFrames = numSubFrames;
        frameSeq->loopBackCfg    = 0;
        frameSeq->forceProfile   = forceProfile;
        frameSeq->numFrames      = cfgParams->frameCfgArgs.numFrames;
        frameSeq->triggerSelect  = cfgParams->frameCfgArgs.triggerSelect;
        frameSeq->frameTrigDelay = 0;
        frameSeq->reserved1      = 0;

        frameData->numSubFrames  = numSubFrames;
        frameData->reserved1     = 0;

        for ( i = 0; i < frameSeq->numOfSubFrames; i++ )
        {
            subFrameCfg     = &frameSeq->subFrameCfg[i];
            subFrameDataCfg = &frameData->subframeDataCfg[i];

            subFrameDataCfg->totalChirps = subFrameCfg->numOfChirps *
                                           subFrameCfg->numLoops *
                                           subFrameCfg->numOfBurst;

            if (frameSeq->forceProfile)
            {
                profileCfg = &cfgParams->profileCfgArgs[subFrameCfg->forceProfileIdx];
            }
            else
            {
                rlChirpCfg_t  * chirpCfg;

                chirpCfg   = &cfgParams->chirpCfgArgs[subFrameCfg->chirpStartIdx];
                profileCfg = &cfgParams->profileCfgArgs[chirpCfg->profileId];
            }
            subFrameDataCfg->numAdcSamples = profileCfg->numAdcSamples * 2;
        }
    }

    return;
}

Int32 ChainsUtil_readFeCfgParams(const char *rootDirName,
                                 ChainsUtil_RlFrontEndConfig  *feCfg)
{
    const ChainsUtil_MasterFileInfo *mstInfo;
    rlFrontEndCfg_t *cfgParams;
    ChainsUtil_ConfigFileInfo cfg;
    UInt32 i, j;
    UInt32 numSensors;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Void *pCfgFileBuf;
    UInt32 fileSize;

    /* Get the Master file information. */
    mstInfo = ChainsUtil_getMstFileInfo(rootDirName);

    if ((mstInfo != NULL) && (mstInfo->feMaster != NULL))
    {
        status = ChainsUtil_readSensorFileInfo(rootDirName, mstInfo->feMaster, &cfg);
        if (SYSTEM_LINK_STATUS_SOK == status)
        {
            feCfg->numSensors = 0;
            cfgParams  = feCfg->cfg;
            numSensors = 0;
            for (i = 0; i < mstInfo->numSensors; i++)
            {
                if (cfg.fileName[i][0] != NULL)
                {
                    feCfg->numSensors++;
                    Vps_printf("SENSOR [%d]: ", i);
                    pCfgFileBuf = ChainsUtil_readCfgFile(rootDirName, cfg.fileName[i], &fileSize);
                    if (pCfgFileBuf != NULL)
                    {
                        ChainsUtil_readFeParams(pCfgFileBuf, fileSize, cfgParams);
                        free(pCfgFileBuf);
                        cfgParams->sensorId = i;
                        cfgParams++;
                        if (0 == i)
                        {
                            for (j = 1; j < mstInfo->numSensors; j++)
                            {
                                memcpy(&feCfg->cfg[j], &feCfg->cfg[0], sizeof(rlFrontEndCfg_t));
                            }
                        }
                        if (++numSensors == mstInfo->numSensors)
                        {
                            break;
                        }
                    }
                    else
                    {
                        status = SYSTEM_LINK_STATUS_EFAIL;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;

}

Void ChainsUtil_setFeParams(Bsp_Ar12xxConfigObj    * ar12xxCfgObj,
                            rlFrontEndCfg_t        * feCfgParams)
{
    UInt32    i;

    UTILS_assert(feCfgParams->numProfileCfg <= ar12xxCfgObj->numProfileCfgArgs);

    /* Factor 2 is due to symbols being COMPLEX. */
    feCfgParams->frameCfgArgs.numAdcSamples =
        feCfgParams->profileCfgArgs[0].numAdcSamples * 2;

    memcpy(ar12xxCfgObj->frameCfgArgs, &feCfgParams->frameCfgArgs,
           sizeof(rlFrameCfg_t));

    memcpy(ar12xxCfgObj->profileCfgArgs, feCfgParams->profileCfgArgs,
           feCfgParams->numProfileCfg * sizeof(rlProfileCfg_t));

    memcpy(ar12xxCfgObj->chirpCfgArgs, feCfgParams->chirpCfgArgs,
           feCfgParams->numChirpCfg * sizeof(rlChirpCfg_t));

    if ( feCfgParams->enableAdvFrameCfg )
    {
        memcpy(&ar12xxCfgObj->advFrameCfgArgs, &feCfgParams->advFrameCfgArgs,
               sizeof(rlAdvFrameCfg_t));
    }
    else
    {
        memset(&ar12xxCfgObj->advFrameCfgArgs, 0, sizeof(rlAdvFrameCfg_t));
    }

    for ( i = 0; i < ar12xxCfgObj->numBpmChirpCfgArgs; i++ )
    {
        ar12xxCfgObj->bpmChirpCfgArgs[i].constBpmVal = 0;
    }

    /* Update the other parameters dependent upon the config params just
     * received.
     */
    ar12xxCfgObj->rfChanCfgArgs.txChannelEn  = feCfgParams->txAntEnableMask;
    ar12xxCfgObj->rfChanCfgArgs.rxChannelEn  = feCfgParams->rxAntEnableMask;
    ar12xxCfgObj->dataFmtCfgArgs.rxChannelEn = feCfgParams->rxAntEnableMask;

    ar12xxCfgObj->numProfileCfgArgs = feCfgParams->numProfileCfg;
    ar12xxCfgObj->numChirpCfgArgs   = feCfgParams->numChirpCfg;

    ar12xxCfgObj->dataPathCfgArgs.transferFmtPkt0 =
        feCfgParams->dataPathCfgArgs.transferFmtPkt0;

    ar12xxCfgObj->dataPathCfgArgs.transferFmtPkt1 =
        feCfgParams->dataPathCfgArgs.transferFmtPkt1;

    return;

}

static Int32 ChainsUtil_updateWindowCoeff(char *fileName, Int16 *windowCoeffBuf, UInt32 bufSize)
{
    Int32 fd;
    UInt32 readSize;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    Int16 buf[1024];

    fd = File_open(fileName, "rb");
    if (fd != SYSTEM_LINK_STATUS_EFAIL)
    {
        File_read(fd, (UInt8 *) buf, bufSize, &readSize);
        if (bufSize == readSize)
        {
            memcpy(windowCoeffBuf, buf, bufSize);
            status = SYSTEM_LINK_STATUS_SOK;
        }
        File_close(fd);
    }

    if (SYSTEM_LINK_STATUS_EFAIL == status)
    {
        Vps_printf("!!Warning: Failed to read FFT Window Coeff from %s!!\n", fileName);
    }

    return status;
}

Int32 ChainsUtil_updateFftAlgoParams(const char *rootDirName,
                                     AlgorithmFxn_RadarFftCreateParams *pFftParams,
                                     UInt32 deviceId)
{
    const ChainsUtil_MasterFileInfo    * mstInfo;
    ChainsUtil_ConfigFileInfo            cfg;
    char                            paramSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                            valueSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                            sLine[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                            fileName[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                          * pParamStr;
    char                          * pValueStr;
    char                          * pSLine;
    Int32 fd;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    Bool done = FALSE;
    AlgorithmFxn_RadarFftAlgCreateParams *pFftAlgParams;

    pParamStr = &paramSt[0];
    pValueStr = &valueSt[0];
    pSLine    = &sLine[0];

    pFftAlgParams = &pFftParams->algCreatePrm[0];
    /* Get the Master file information. */
    mstInfo = ChainsUtil_getMstFileInfo(rootDirName);

    if ((mstInfo != NULL) && (mstInfo->fftMaster[0] != NULL))
    {
        ChainsUtil_readSensorFileInfo(rootDirName, mstInfo->fftMaster, &cfg);
        if ( cfg.fileName[deviceId][0] != NULL )
        {
            sprintf(fileName,"%s%s", rootDirName, cfg.fileName[deviceId]);

            Vps_printf("Parsing FFT Algorithm Params File: %s\n", fileName);

            fd = File_open(fileName,"r");
            if(fd != SYSTEM_LINK_STATUS_EFAIL)
            {
                status = SYSTEM_LINK_STATUS_SOK;
            }
        }
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        while (done != TRUE)
        {
            pSLine = File_gets(pSLine, CHAINS_RADAR_UTIL_MAX_LINE_LEN, fd);

            if( pSLine == NULL )
            {
                done = TRUE;
                continue;
            }

            if (strchr(pSLine, '#') || !strcmp(pSLine, "\n"))
            {
                continue;
            }

            sscanf(pSLine,"%s %s",pParamStr, pValueStr);

            /* FFT Alg Create Params */
            if (strcmp(pParamStr, "FFT_Config_ID") == 0)
            {
                if (0 == atoi(pValueStr))
                {
                    pFftAlgParams = &pFftParams->algCreatePrm[0];
                }
                else
                {
                    pFftAlgParams = &pFftParams->algCreatePrm[1];
                }
            }
            else if (strcmp(pParamStr, "enableWindowing") == 0)
            {
                pFftAlgParams->enableWindowing = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "enableDcoffset") == 0)
            {
                pFftAlgParams->enableDcoffset = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "enableInterferenceZeroOut") == 0)
            {
                pFftAlgParams->enableInterferenceZeroOut = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "enableDopplerCorrection") == 0)
            {
                pFftAlgParams->enableDopplerCorrection = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "windowingScaleFactor") == 0)
            {
                pFftAlgParams->windowingScaleFactor = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "interferenceThreshold") == 0)
            {
                pFftAlgParams->interferenceThreshold = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "enableOverFlowDetection") == 0)
            {
                pFftAlgParams->enableOverFlowDetection = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "outputContainerFormat") == 0)
            {
                pFftAlgParams->outputContainerFormat = atoi(pValueStr);
            }
            else if (strcmp(pParamStr,"windowCoeffFileName_1024") == 0)
            {
                UTILS_assert(pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_1024] != 0U);
                sprintf(fileName,"%s%s", rootDirName, pValueStr);
                ChainsUtil_updateWindowCoeff(fileName,
                                             (Int16 *) pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_1024],
                                             1024*sizeof(Int16));
            }
            else if (strcmp(pParamStr,"windowCoeffFileName_512") == 0)
            {
                UTILS_assert(pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_512] != 0U);
                sprintf(fileName,"%s%s", rootDirName, pValueStr);
                ChainsUtil_updateWindowCoeff(fileName,
                                             (Int16 *) pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_512],
                                             512*sizeof(Int16));
            }
            else if (strcmp(pParamStr,"windowCoeffFileName_256") == 0)
            {
                UTILS_assert(pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_256] != 0U);
                sprintf(fileName,"%s%s", rootDirName, pValueStr);
                ChainsUtil_updateWindowCoeff(fileName,
                                             (Int16 *) pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_256],
                                             256*sizeof(Int16));
            }
            else if (strcmp(pParamStr,"windowCoeffFileName_128") == 0)
            {
                UTILS_assert(pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_128] != 0U);
                sprintf(fileName,"%s%s", rootDirName, pValueStr);
                ChainsUtil_updateWindowCoeff(fileName,
                                             (Int16 *) pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_128],
                                             128*sizeof(Int16));
            }
            else if (strcmp(pParamStr,"windowCoeffFileName_64") == 0)
            {
                UTILS_assert(pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_64] != 0U);
                sprintf(fileName,"%s%s", rootDirName, pValueStr);
                ChainsUtil_updateWindowCoeff(fileName,
                                             (Int16 *) pFftAlgParams->windowCoeffAddr[RADAR_FFT_NUM_POINTS_64],
                                             64*sizeof(Int16));
            }
        }
        File_close(fd);
    }

    return status;
}

Int32 ChainsUtil_updateCascadeDspProcessParams(const char *rootDirName,
                                               AlgorithmFxn_RadarDspProcessCreateParams *pDspProcParams)
{
    const ChainsUtil_MasterFileInfo    * mstInfo;
    ChainsUtil_ConfigFileInfo            cfg;
    char                            paramSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                            valueSt[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                            sLine[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                            fileName[CHAINS_RADAR_UTIL_MAX_LINE_LEN];
    char                          * pParamStr;
    char                          * pValueStr;
    char                          * pSLine;
    Int32 fd;
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    Bool done = FALSE;
    AlgorithmFxn_RadarDspProcCfarCreateParams *pCfarParams;
    AlgorithmFxn_RadarDspProcAoaCreateParams *pAoaParams;

    pParamStr = &paramSt[0];
    pValueStr = &valueSt[0];
    pSLine    = &sLine[0];

    pCfarParams = &pDspProcParams->cfarCreateParams;
    pAoaParams = &pDspProcParams->aoaCreateParams;
    /* Get the Master file information. */
    mstInfo = ChainsUtil_getMstFileInfo(rootDirName);

    if ((mstInfo != NULL) && (mstInfo->dspAlgoMaster[0] != NULL))
    {
        ChainsUtil_readSensorFileInfo(rootDirName, mstInfo->dspAlgoMaster, &cfg);
        if ( cfg.fileName[0][0] != NULL )
        {
            sprintf(fileName,"%s%s", rootDirName, cfg.fileName[0]);

            Vps_printf("Parsing Radar DSP Process Algorithm Params File: %s\n", fileName);

            fd = File_open(fileName,"r");
            if(fd != SYSTEM_LINK_STATUS_EFAIL)
            {
                status = SYSTEM_LINK_STATUS_SOK;
            }
        }
    }

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        while (done != TRUE)
        {
            pSLine = File_gets(pSLine, CHAINS_RADAR_UTIL_MAX_LINE_LEN, fd);

            if( pSLine == NULL )
            {
                done = TRUE;
                continue;
            }

            if (strchr(pSLine, '#') || !strcmp(pSLine, "\n"))
            {
                continue;
            }

            sscanf(pSLine,"%s %s",pParamStr, pValueStr);

            /* CFAR Alg Create Params */
            if (strcmp(pParamStr, "pfa") == 0)
            {
                pCfarParams->pfa = (float) atof(pValueStr);
            }
            else if (strcmp(pParamStr, "K0") == 0)
            {
                pCfarParams->K0 = (float) atof(pValueStr);
            }
            else if (strcmp(pParamStr, "dopplerSearchRelThr") == 0)
            {
                pCfarParams->dopplerSearchRelThr = (float) atof(pValueStr);
            }
            else if (strcmp(pParamStr, "enableSecondPassSearch") == 0)
            {
                pCfarParams->enableSecondPassSearch = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "searchWinSizeRange") == 0)
            {
                pCfarParams->searchWinSizeRange = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "guardSizeRange") == 0)
            {
                pCfarParams->guardSizeRange = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "searchWinSizeDoppler") == 0)
            {
                pCfarParams->searchWinSizeDoppler = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "guardSizeDoppler") == 0)
            {
                pCfarParams->guardSizeDoppler = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "maxNumDetObj") == 0)
            {
                pCfarParams->maxNumDetObj = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "leftSkipSize") == 0)
            {
                pCfarParams->leftSkipSize = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "rightSkipSize") == 0)
            {
                pCfarParams->rightSkipSize = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "leftSkipSizeAzimuth") == 0)
            {
                pCfarParams->leftSkipSizeAzimuth = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "rightSkipSizeAzimuth") == 0)
            {
                pCfarParams->rightSkipSizeAzimuth = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "log2MagFlag") == 0)
            {
                pCfarParams->log2MagFlag = atoi(pValueStr);
            }
            /* AoA Alg Create Params */
            else if (strcmp(pParamStr, "rxMainRowIndex") == 0)
            {
                pAoaParams->rxMainRowIndex = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "azimuthFFTsize") == 0)
            {
                pAoaParams->azimuthFFTsize = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "numAzimuthFFTs") == 0)
            {
                pAoaParams->numAzimuthFFTs = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "elevationFFTsize") == 0)
            {
                pAoaParams->elevationFFTsize = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "multiPeakThresholdScale") == 0)
            {
                pAoaParams->multiPeakThresholdScale = (float) atof(pValueStr);
            }
            else if (strcmp(pParamStr, "enableClutterRemoval") == 0)
            {
                pAoaParams->enableClutterRemoval = atoi(pValueStr);
            }
            else if (strcmp(pParamStr, "enableExtendedMaxVelocity") == 0)
            {
                pAoaParams->enableExtendedMaxVelocity = atoi(pValueStr);
            }
        }
        File_close(fd);
    }

    return status;
}
