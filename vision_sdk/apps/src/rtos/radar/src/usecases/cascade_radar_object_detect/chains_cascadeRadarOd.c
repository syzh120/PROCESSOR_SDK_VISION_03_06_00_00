/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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
#include "chains_cascadeRadarOd_priv.h"
#include <include/common/chains_radar.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/vps_capture.h>
#include <include/common/chains_radar_util_read_params.h>

#define CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS                         (16U)
#define CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS_LENGTH                  (8U)

/**
 *******************************************************************************
 * \brief Channels with timestamp difference <= SYNC_DELTA_IN_MSEC
 *        are synced together by sync link
 *******************************************************************************
 */
#define SYNC_DELTA_IN_MSEC              (50)

/**
 *******************************************************************************
 * \brief Channels with timestamp older than SYNC_DROP_THRESHOLD_IN_MSEC
 *        are dropped by sync link
 *******************************************************************************
 */
#define SYNC_DROP_THRESHOLD_IN_MSEC     (100)

typedef enum
{
    CASCADE_RADAR_MIMO_MODE,
    CASCADE_RADAR_TX_BEAMFORMING_MODE
} Chains_cascadeRadarOd_UseCaseType;

char Chains_cascadeRadarOd_runTimeMenu();
static Void Chains_parseCmd(char* inputStr, UInt16 *argc, char **argv);
static Void Chains_readString(char* inputString, UInt8 maxNumChar);
static Void Chains_cascadeRadarOd_runTimeSelect();
static Void Chains_cascadeRadarOd_runTimeSelectUC();

static UInt32 g2DFftOnEve = 1U;
static Chains_cascadeRadarOd_UseCaseType gCascadeRadarUC = CASCADE_RADAR_MIMO_MODE;

/**
 *******************************************************************************
 *
 *  \brief  Chains_cascadeRadarOdObj
 *
 *        This structure contains all the LinksId's and create Params.
 *        The same is passed to all create, start, stop functions.
 *
 *******************************************************************************
*/
typedef struct {

    chains_cascadeRadarOdObj ucObj;

    ChainsCommon_Ar12xxConfigOut ar12xxCfg;

    Chains_Ctrl *chainsCfg;

    /* Algorithm */
    AlgorithmFxn_RadarFftCreateParams radarFftParams1;
    AlgorithmFxn_RadarFftCreateParams radarFftParams2;
    AlgorithmFxn_RadarFftCreateParams radarFftParams3;
    AlgorithmFxn_RadarFftCreateParams radarFftParams4;
    AlgorithmFxn_RadarDspProcessCreateParams radarDspOdParams;

    ChainsUtil_RlFrontEndConfig feCfgReq;

} Chains_cascadeRadarOdAppObj;

/**< \brief This structure contains the Transmit antenna offsets in the elevation
 *          and azimuth direction in multiples of lambda by 2.
 */
Chanis_RadarAntOffset gCascadeRadarTxAntArray[CHAINS_RADAR_CASCADE_NUMSENSORS][CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA_PERSENSOR] =
{
    /* Master */
    {   /* TX1, TX2, TX3 - {Azimuth offset, Elevation offset (in lambda/2)} */
        {11U, 6U}, {10U, 4U}, {9U, 1U}
    },
    /* Slave 1 */
    {   /* TX1, TX2, TX3 */
        {32U, 0U}, {28U, 0U}, {24U, 0U}
    },
    /* Slave 2 */
    {   /* TX1, TX2, TX3 */
        {20U, 0U}, {16U, 0U}, {12U, 0U}
    },
    /* Slave 1 */
    {   /* TX1, TX2, TX3 */
        {8U, 0U}, {4U, 0U}, {0U, 0U}
    }
};

/**< \brief This structure contains the Transmit antenna offsets in the elevation
 *          and azimuth direction in multiples of lambda by 2.
 */
typedef struct
{
    UInt16 antAzimOffs[CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA];
    UInt16 antElevOffs[CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA];
    UInt16 antRowOffs[CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA];
} aoa_txAntOffset_t;

typedef struct
{
    UInt16 sensorInd;
    UInt16 txAntInd;
    UInt16 rxAntInd;
    UInt16 pad;
} aoa_overlap_antenna;

typedef struct
{
    aoa_overlap_antenna previous;
    aoa_overlap_antenna current;
} aoa_overlapAntennaPairs;

/**< \brief This structure contains the Recieve antenna offsets in the elevation
 *          and azimuth direction in multiples of lambda by 2.
 */
typedef struct
{
    UInt16 sensorAzimOffs;
    UInt16 antAzimOffs[CHAINS_RADAR_CASCADE_MAX_RX_ANTENNA_PERSENSOR];
    UInt16 antElevOffs[CHAINS_RADAR_CASCADE_MAX_RX_ANTENNA_PERSENSOR];
    UInt16 antRowOffs[CHAINS_RADAR_CASCADE_MAX_RX_ANTENNA_PERSENSOR];
} aoa_rxAntOffset_t;

aoa_txAntOffset_t gAoa_txAntOffset = {0};

aoa_rxAntOffset_t gAoa_sensorRxOffset[CHAINS_RADAR_CASCADE_NUMSENSORS] = {0};

UInt16 gAoa_rowToElevationIdx[CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA] = {0};

aoa_overlapAntennaPairs gAoa_overlapAntennaPairs[] =
{
     {.previous = {1,0,0}, .current = {0,1,3}},
     {.previous = {1,1,0}, .current = {0,2,3}},
     {.previous = {1,2,0}, .current = {0,3,3}},
     {.previous = {1,3,0}, .current = {0,4,3}}
};

/* For TI RF calibration coefficients. The values are stored as: real value is
 * in odd memory position, negative imaginary value is in even position */
AlgorithmFxn_RadarDspProcessComplexNum gChanCompCoefs [] =
{
     {0.5493532, -0.5382177},
     {0.5768175, -0.5527835},
     {0.5161927, -0.5520395},
     {0.6684260, -0.4948089},
     {0.8705083, -0.0142706},
     {0.9357420, -0.0385306},
     {0.8456463, -0.0404831},
     {0.8996814, 0.0715656},
     {0.8015795, 0.4135538},
     {0.8284975, 0.4534344},
     {0.7886266, 0.3798872},
     {0.7884426, 0.4827199},
     {0.9043464, -0.5787817},
     {0.9169999, -0.4995597},
     {0.7730544, -0.6039488},
     {0.8425182, -0.5128371},
     {0.6421999, -0.6221311},
     {0.7653940, -0.5754842},
     {0.5956402, -0.5352713},
     {0.6980371, -0.5140949},
     {-0.9440165, -0.4547817},
     {-0.9657323, -0.4828662},
     {-0.8692111, -0.3945761},
     {-0.9100713, -0.5279803},
     {-1.0462480, -0.3236595},
     {-1.0991201, -0.4520575},
     {-1.0783755, -0.3171692},
     {-1.0389148, -0.6105903},
     {-0.9620396, -0.5932578},
     {-0.9969274, -0.8560573},
     {-0.9548815, -0.5968009},
     {-0.8344880, -0.6344868},
     {-0.2610382, 0.8056180},
     {-0.0744242, 0.7477865},
     {0.0357804, 0.7951190},
     {-0.0672695, 0.9055505},
     {-0.7162539, 0.7644633},
     {-0.4306506, 0.7946529},
     {-0.3173126, 0.9336312},
     {-0.4023159, 0.9914214},
     {-0.7082964, 0.5728868},
     {-0.4729874, 0.5966918},
     {-0.3494343, 0.6950704},
     {-0.4710852, 0.7765141},
     {0.1380861, 0.9279386},
     {0.2620542, 0.7777091},
     {0.3737004, 0.7224874},
     {0.3094909, 0.8602797},
     {0.0152542, 0.9000005},
     {0.1287354, 0.7438046},
     {0.1883689, 0.7285966},
     {0.0906799, 0.9174668},
     {0.9756498, -0.1790750},
     {0.8663723, -0.3665421},
     {0.8054178, -0.4799407},
     {0.8859414, -0.5562888},
     {0.7894852, -0.2141689},
     {0.6803175, -0.2256978},
     {0.7058089, -0.3263418},
     {0.7997218, -0.4023758},
     {0.7420773, -0.1433966},
     {0.6557204, -0.1798879},
     {0.6311873, -0.2957738},
     {0.7367190, -0.3197846},
     {0.9505693, 0.5551325},
     {1.0414761, 0.2603690},
     {1.0285757, 0.2223947},
     {0.9209221, 0.4473050},
     {0.5513432, 0.9571931},
     {0.6988582, 0.7050428},
     {0.6979669, 0.6630686},
     {0.5570068, 0.8025689},
     {0.0603978, 0.9334203},
     {0.1390159, 0.8628576},
     {0.1593458, 0.8764020},
     {0.0672695, 0.9055505},
     {0.7194937, 0.8075950},
     {0.7881971, 0.8207001},
     {0.9099478, 0.7524568},
     {0.8386164, 0.8298808},
     {0.6049777, 1.3151687},
     {0.6597368, 1.6299380},
     {0.9598035, 1.4212475},
     {0.8693603, 1.3277503},
     {-0.0969632, -1.1811885},
     {-0.1869433, -1.0982921},
     {-0.0996534, -1.1460146},
     {-0.0559669, -1.1273338},
     {0.1046557, -1.5399344},
     {-0.2260024, -1.4831409},
     {-0.1675737, -1.6254649},
     {0.0268146, -1.4613965},
     {0.5782658, -1.3448040},
     {0.3903018, -1.7666292},
     {0.4525752, -1.7119149},
     {0.4306256, -1.4497730},
     {0.7551180, -0.5264555},
     {0.8770092, -0.6521350},
     {0.5232915, -0.9318889},
     {0.8842050, -0.6499285},
     {0.9872881, -0.0490578},
     {1.2393565, -0.1770509},
     {0.9860778, -0.4277838},
     {1.1080856, -0.1248547},
     {0.7946622, 0.3169462},
     {0.9816368, 0.2814026},
     {0.9127659, 0.0524578},
     {0.9422511, 0.3161500},
     {0.8290837, -0.3437664},
     {0.9458543, -0.4355012},
     {0.8430626, -0.6393225},
     {1.0346645, -0.3523857},
     {1.0268174, -0.1486183},
     {1.1788297, -0.1506775},
     {1.1617876, -0.4094825},
     {1.3399067, -0.1717829},
     {-1.0016693, -0.4021300},
     {-1.2705544, -0.4578574},
     {-1.2365324, -0.1864612},
     {-1.1850164, -0.3788167},
     {-1.2087471, -0.5384420},
     {-1.5229037, -0.8674768},
     {-1.7853301, -0.2872945},
     {-1.5511544, -0.6345631},
     {-0.9038273, -0.9582747},
     {-0.9570825, -1.3264828},
     {-1.2853311, -1.0740438},
     {-1.1545604, -1.1380666}
};

Void Chains_cascadeRadarFillRxAntennaOffsets (aoa_rxAntOffset_t *aoa_sensorRxOffset)
{
    uint16_t antAzimOffs [] = {0, 1, 2, 3};
    uint16_t antElevOffs [] =  {0, 0, 0, 0};
    uint16_t antRowOffs [] =  {0, 0, 0, 0};
    uint16_t i = 0U;
    aoa_sensorRxOffset[0].sensorAzimOffs = 0;
    aoa_sensorRxOffset[1].sensorAzimOffs = 11;
    aoa_sensorRxOffset[2].sensorAzimOffs = 50;
    aoa_sensorRxOffset[3].sensorAzimOffs = 46;
    for (i = 0U ; i < CHAINS_RADAR_CASCADE_NUMSENSORS; i++)
    {
        memcpy(aoa_sensorRxOffset[i].antAzimOffs, antAzimOffs, sizeof(antAzimOffs));
        memcpy(aoa_sensorRxOffset[i].antElevOffs, antElevOffs, sizeof(antElevOffs));
        memcpy(aoa_sensorRxOffset[i].antRowOffs , antRowOffs , sizeof(antRowOffs ));
    }
}

Void Chains_cascadeRadarFillRowToElevIdx(UInt16 *aoa_rowToElevationIdx,
                                         UInt16 *txAntElevOffs,
                                         UInt32 numTxAzimAnt,
                                         UInt32 numTxElevAnt)
{
    UInt32 i, j;

    if ((gCascadeRadarUC == CASCADE_RADAR_MIMO_MODE) && (numTxElevAnt > 0))
    {
        for (i = 0, j = 1; i < CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA; i++)
        {
            if (txAntElevOffs[i] > 0)
            {
                aoa_rowToElevationIdx[j++] = txAntElevOffs[i];
            }
        }
    }
    else
    {
        memset(aoa_rowToElevationIdx, 0, (sizeof(UInt16)*CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA));
    }
}

Void Chains_aoAReadCascadeCoeffs(
    AlgorithmFxn_RadarDspProcessComplexNum *rxChPhaseComp)
{
    Int32   fpReadDataStream;
    char    filename[64];
    size_t  coffFileSize;
    UInt32  bytesRead = 0;
    AlgorithmFxn_RadarDspProcessComplexNum *pCalibrationTable;

    pCalibrationTable = gChanCompCoefs;
    UTILS_assert(pCalibrationTable != NULL);

    /* read coeff from a file */
    sprintf(filename, "calib_coef.bin");

    /* Open file */
    fpReadDataStream = File_open((Char *)filename, "r");
    if(fpReadDataStream == -1)
    {
        memcpy((Uint8 *) rxChPhaseComp,
               pCalibrationTable,
               sizeof(AlgorithmFxn_RadarDspProcessComplexNum) *
               ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA);
        Vps_printf("FILE_IO: Calibration file(%s) is NOT present in sd card! Used built-in coefficients!\n", filename);
    }
    else
    {
        coffFileSize = File_size(fpReadDataStream);
        if(coffFileSize <=
          (sizeof(AlgorithmFxn_RadarDspProcessComplexNum) *
          ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA))
        {
            File_read(fpReadDataStream, (Uint8 *) rxChPhaseComp,
                      coffFileSize, &bytesRead);
            Vps_printf(
                "FILE_IO: Calibration file(%s) is present in sd card \n",
                filename);
        }
        else
        {
            memcpy((Uint8 *) rxChPhaseComp, pCalibrationTable,
                   sizeof(AlgorithmFxn_RadarDspProcessComplexNum) *
                   ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA);
            Vps_printf(
                "FILE_IO: Calibration file(%s) size is NOT compatible (expected %d Bytes). Used built-in coefficients!\n",
                       filename,
                       (sizeof(AlgorithmFxn_RadarDspProcessComplexNum) *
                       ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_VIRT_ANTENNA));
        }
    }
}

void Chains_RadarDspProcess_SetPrms (AlgorithmFxn_RadarDspProcessCreateParams *pPrms,
                                     ChainsCommon_Ar12xxConfigOut *pAr12xxCfg)
{
    AlgorithmFxn_RadarDspProcChCreateParams    *chCreateParams;
    AlgorithmFxn_RadarDspProcCfarCreateParams  *cfarCreateParams;
    AlgorithmFxn_RadarDspProcAoaCreateParams   *aoaCreateParams;
    UInt16                                     *rxAngleIndxLUT, *rxRowIndxLUT;
    UInt32 i, j, numTx, numChirps;
    AlgorithmFxn_RadarDspProcessOpBlobControlParams *opControlParams;
    UInt32 numTxAzimAnt = 0U;
    UInt32 numTxElevAnt = 0U;
    UInt16 txAntEnableMask = 0U;
    UInt16 txEnable, txAntBitMask, txAntNum;

    AlgorithmFxn_RadarDspProcess_Init(pPrms);
    pPrms->inputBufferType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER;
    pPrms->numChannels = 1U; /* cascade configuration */
    pPrms->enableClutterRemoval = 0U;
    if (g2DFftOnEve == 1U)
    {
        pPrms->skipDopplerFft = 1U;
    }
    else
    {
        pPrms->skipDopplerFft = 0U;
    }
    if (gCascadeRadarUC == CASCADE_RADAR_MIMO_MODE)
    {
        for (j = 0U; j < pAr12xxCfg->numRadars; j++)
        {
            for (numChirps = 0U; numChirps < pAr12xxCfg->radarParams[j].ar12xxConfig.numChirpCfgArgs;
                    numChirps++)
            {
                txEnable = pAr12xxCfg->radarParams[j].ar12xxConfig.chirpCfgArgs[numChirps].txEnable;
                if (txEnable != 0U)
                {
                    txAntNum = 0;
                    while((txEnable != 0U) && (txAntNum < CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA_PERSENSOR))
                    {
                        if ((txEnable & 0x1U) == 1U)
                        {
                            gAoa_txAntOffset.antAzimOffs[numChirps] = gCascadeRadarTxAntArray[j][txAntNum].azimOffset;
                            gAoa_txAntOffset.antElevOffs[numChirps] = gCascadeRadarTxAntArray[j][txAntNum].elevOffset;
                            txAntBitMask = 1U << ((j*CHAINS_RADAR_CASCADE_MAX_TX_ANTENNA_PERSENSOR)+txAntNum);
                            if ((txAntEnableMask & txAntBitMask) == 0)
                            {
                                txAntEnableMask |= txAntBitMask;
                                if ( gCascadeRadarTxAntArray[j][txAntNum].elevOffset > 0 )
                                {
                                    numTxElevAnt++;
                                    gAoa_txAntOffset.antRowOffs[numChirps] = numTxElevAnt;
                                }
                                else
                                {
                                    numTxAzimAnt++;
                                }
                            }
                        }
                        txEnable >>= 1;
                        txAntNum++;
                    }
                }
            }
        }
    }
    else
    {
        numTxElevAnt = 0U;
        numTxAzimAnt = 1U;
        txAntNum = 1U;
    }
    chCreateParams = &pPrms->chCreateParams[0];
    chCreateParams->numSensorDevPerChannel = pAr12xxCfg->numRadars;
    chCreateParams->numProfiles = pAr12xxCfg->radarParams[0].numProfiles;
    for (i = 0U; i < pAr12xxCfg->radarParams[0].numProfiles; i++)
    {
        chCreateParams->numAdcSamples[i] = pAr12xxCfg->radarParams[0].radarWidth[i];
        chCreateParams->numChirpLoops[i] = pAr12xxCfg->radarParams[0].radarHeight[i];
        chCreateParams->rangeRes[i]      = pAr12xxCfg->radarParams[0].rangeRes[i];
        chCreateParams->dopplerRes[i]    = pAr12xxCfg->radarParams[0].velocityRes[i];
        for (j = 0U; j < pAr12xxCfg->numRadars; j++)
        {
            if ((numTxAzimAnt + numTxElevAnt) != 1U)
            {
                numTx = 0U;
                for (numChirps = 0U; numChirps < pAr12xxCfg->radarParams[j].ar12xxConfig.numChirpCfgArgs;
                    numChirps++)
                {
                    numTx = numTx | pAr12xxCfg->radarParams[j].ar12xxConfig.chirpCfgArgs[numChirps].txEnable;
                }
                chCreateParams->numTxAnt[j][i] = Chains_ar12xxCountOnes(numTx);
            }
            else
            {
                chCreateParams->numTxAnt[j][i] = 1U;
            }
            chCreateParams->numRxAnt[j][i] = pAr12xxCfg->radarParams[j].numRxAntenna[i];
        }
    }
    cfarCreateParams = &pPrms->cfarCreateParams;
    cfarCreateParams->cfarType              = ALG_FXN_RADAR_DSP_PROCESS_CFAR_CASO;
    cfarCreateParams->pfa                   = (float)1e-6;
    cfarCreateParams->K0                    = 6.3;
    cfarCreateParams->dopplerSearchRelThr   = 6.3;
    cfarCreateParams->enableSecondPassSearch= 1U;
    cfarCreateParams->searchWinSizeRange    = 16;
    cfarCreateParams->guardSizeRange        = 4;
    cfarCreateParams->searchWinSizeDoppler  = 8;
    cfarCreateParams->guardSizeDoppler      = 0;
    cfarCreateParams->maxNumDetObj          = ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS >> 1U;
    cfarCreateParams->leftSkipSize          = 1;
    cfarCreateParams->rightSkipSize         = 18;
    cfarCreateParams->leftSkipSizeAzimuth   = 0;
    cfarCreateParams->rightSkipSizeAzimuth  = 0;
    cfarCreateParams->log2MagFlag           = 0U;

    aoaCreateParams = &pPrms->aoaCreateParams;
    aoaCreateParams->rxMainRowIndex         = 0;
    aoaCreateParams->azimuthFFTsize         = 128;
    aoaCreateParams->numAzimuthFFTs         = 4;
    aoaCreateParams->elevationFFTsize       = 64;
    aoaCreateParams->multiPeakThresholdScale= 0.95;
    aoaCreateParams->enableClutterRemoval   = 0U;
    aoaCreateParams->enableExtendedMaxVelocity = 0U;
    aoaCreateParams->numOverlapAntennaPairs = 4; /* Board Specific */
    rxAngleIndxLUT = aoaCreateParams->rxAngleIndxLUT;
    rxRowIndxLUT = aoaCreateParams->rxRowIndxLUT;

    ChainsUtil_updateCascadeDspProcessParams(RADAR_CONFIG_PARAM_DIR_NAME, pPrms);

    j = 0; /* Single Profile Assumed */
    numTx = numTxAzimAnt + numTxElevAnt;
    Chains_cascadeRadarFillRxAntennaOffsets(gAoa_sensorRxOffset);
    Chains_cascadeRadarFillRowToElevIdx(gAoa_rowToElevationIdx,
                                        gAoa_txAntOffset.antElevOffs,
                                        numTxAzimAnt,
                                        numTxElevAnt);
    for (i = 0; i < pAr12xxCfg->numRadars; i++)
    {
        UInt32 txInd, rxInd, ind;
        for (txInd = 0; txInd < numTx; txInd++)
        {
            for (rxInd = 0; rxInd < pAr12xxCfg->radarParams[i].numRxAntenna[j]; rxInd++)
            {
                ind = i * (numTx * pAr12xxCfg->radarParams[i].numRxAntenna[j]) +
                      txInd * pAr12xxCfg->radarParams[i].numRxAntenna[j] + rxInd;
                rxAngleIndxLUT[ind] = gAoa_txAntOffset.antAzimOffs[txInd] +
                                      gAoa_sensorRxOffset[i].sensorAzimOffs +
                                      gAoa_sensorRxOffset[i].antAzimOffs[rxInd];
                rxRowIndxLUT[ind] = gAoa_txAntOffset.antRowOffs[txInd] +
                                    gAoa_sensorRxOffset[i].antRowOffs[rxInd];
            }
        }
    }
    for (i = 0; i < aoaCreateParams->numAzimuthFFTs; i++)
    {
        aoaCreateParams->rxRowToElevIdxLUT[i] = gAoa_rowToElevationIdx[i];
    }
    for (i = 0; i < aoaCreateParams->numOverlapAntennaPairs; i++)
    {
        aoaCreateParams->overlapAntennaPairs[i] =
            (Uint32) (gAoa_overlapAntennaPairs[i].previous.sensorInd * numTx *
                      pAr12xxCfg->radarParams[0].numRxAntenna[0] +
                      gAoa_overlapAntennaPairs[i].previous.txAntInd *
                      pAr12xxCfg->radarParams[0].numRxAntenna[0] +
                      gAoa_overlapAntennaPairs[i].previous.rxAntInd) |
           (((Uint32) (gAoa_overlapAntennaPairs[i].current.sensorInd * numTx *
                      pAr12xxCfg->radarParams[0].numRxAntenna[0] +
                      gAoa_overlapAntennaPairs[i].current.txAntInd *
                      pAr12xxCfg->radarParams[0].numRxAntenna[0] +
                      gAoa_overlapAntennaPairs[i].current.rxAntInd)) << 16);
    }
    Chains_aoAReadCascadeCoeffs(aoaCreateParams->rxChPhaseComp);
    aoaCreateParams->calibParams.state =
            ALGORITHMFXN_RADAR_DSP_PROCESS_NORMAL_RUNNING;

    opControlParams = &pPrms->opControlParams;
    opControlParams->pointCloud = 1U;
    opControlParams->rangeProfile = 1U;
    opControlParams->noiseProfile = 0U;
    opControlParams->rangeDopHeatMap = 0U;
    opControlParams->azimuthHeatMap = 0U;
}

static Void Chains_setSelectParams(SelectLink_CreateParams *pPrm)
{
    pPrm->numOutQue = 4;

    pPrm->outQueChInfo[0].outQueId   = 0;
    pPrm->outQueChInfo[0].numOutCh   = 1;
    pPrm->outQueChInfo[0].inChNum[0] = 0;

    pPrm->outQueChInfo[1].outQueId   = 1;
    pPrm->outQueChInfo[1].numOutCh   = 1;
    pPrm->outQueChInfo[1].inChNum[0] = 1;

    pPrm->outQueChInfo[2].outQueId   = 2;
    pPrm->outQueChInfo[2].numOutCh   = 1;
    pPrm->outQueChInfo[2].inChNum[0] = 2;

    pPrm->outQueChInfo[3].outQueId   = 3;
    pPrm->outQueChInfo[3].numOutCh   = 1;
    pPrm->outQueChInfo[3].inChNum[0] = 3;
}

/**
 *******************************************************************************
 *
 * \brief   Set Sync Create Parameters
 *
 *          This function is used to set the sync params.
 *          It is called in Create function.
 *
 * \param   pPrm    [OUT]    SyncLink_CreateParams
 *
 *******************************************************************************
*/
static Void Chains_SetSyncParams(SyncLink_CreateParams *pPrm)
{
    pPrm->syncDelta = SYNC_DELTA_IN_MSEC;
    pPrm->syncThreshold = SYNC_DROP_THRESHOLD_IN_MSEC;
}

/**
 *******************************************************************************
 *
 * \brief   Start the Links
 *
 *          Function sends a control command to all the links to
 *          to Start them. Links are started in reverce
 *          order as information of next link is required to connect.
 *          System_linkStart is called with LinkId to start the links.
 *
 * \param   pObj  [IN] Chains_cascadeRadarOdAppObj
 *
 * /return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Void chains_cascadeRadarOd_StartApp(Chains_cascadeRadarOdAppObj *pObj)
{
    Chains_memPrintHeapStatus();

    ChainsCommon_ar12xxStart();
    chains_cascadeRadarOd_Start(&pObj->ucObj);

    Chains_prfLoadCalcEnable(TRUE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Delete the usecase Links
 *
 *          Function sends a control command to all usecase links to
 *          to delete them
 *          System_linkDelete is called with LinkId to delete the links.
 *
 * \param   pObj   [IN]   Chains_cascadeRadarOdAppObj
 *
 *******************************************************************************
*/
Void chains_cascadeRadarOd_StopAndDeleteApp(Chains_cascadeRadarOdAppObj *pObj)
{
    chains_cascadeRadarOd_Stop(&pObj->ucObj);
    chains_cascadeRadarOd_Delete(&pObj->ucObj);
    ChainsCommon_ar12xxStop(&pObj->ar12xxCfg);

    /* Print the HWI, SWI and all tasks load */
    /* Reset the accumulated timer ticks */
    Chains_prfLoadCalcEnable(FALSE, FALSE, FALSE);
}

/**
 *******************************************************************************
 *
 * \brief   Set link Parameters
 *
 *          It is called in Create function of the auto generated use-case file.
 *
 * \param pUcObj    [IN] Auto-generated usecase object
 * \param appObj    [IN] Application specific object
 *
 *******************************************************************************
*/
Void chains_cascadeRadarOd_SetAppPrms(chains_cascadeRadarOdObj *pUcObj, Void *appObj)
{
    Chains_cascadeRadarOdAppObj *pObj
        = (Chains_cascadeRadarOdAppObj*)appObj;
    UInt32 portId[SYSTEM_CAPTURE_VIP_INST_MAX] = {
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA)
    };
    Int32 status;
    UInt32 i;

    /* Fill params for cascade, params are used in cascade Algo */
    if (gCascadeRadarUC == CASCADE_RADAR_MIMO_MODE)
    {
        Chains_ar12xxGetSampleCascadeConfig(&pObj->ar12xxCfg);
    }
    else
    {
        Chains_ar12xxGetSampleCascadeConfigBeamForm(&pObj->ar12xxCfg);
    }

    status = ChainsUtil_readFeCfgParams(RADAR_CONFIG_PARAM_DIR_NAME, &pObj->feCfgReq);

    if (status != SYSTEM_LINK_STATUS_SOK)
    {
        Vps_printf("!!!No Valid Configuration file is found. Use Default Configurations!!!\n");
    }
    else
    {
        for ( i = 0U; i < pObj->feCfgReq.numSensors; i++ )
        {
            /* Update the Front End configuration parameters. */
            ChainsUtil_setFeParams(&pObj->ar12xxCfg.radarParams[i].ar12xxConfig,
                                   &pObj->feCfgReq.cfg[i]);
        }
    }

    ChainsCommon_ar12xxConfig(&pObj->ar12xxCfg);

    if (gCascadeRadarUC == CASCADE_RADAR_TX_BEAMFORMING_MODE)
    {
        Chains_ar12xxSetCascadePhaseShifterBeamForm();
    }

    ChainsCommon_ar12xxSetMultiVipCaptureParams(&pUcObj->CapturePrm,
                                                &pObj->ar12xxCfg,
                                                portId);

    Chains_setSelectParams(&pUcObj->SelectPrm);

    ChainsCommon_ar12xxSetFFTParams(&pObj->radarFftParams1,
                                    &pObj->ar12xxCfg);
    /* EVE only does 1D FFT at 16 bit and 2D FFT at 32 bit */
    pObj->radarFftParams1.baseClassCreateParams.numOutputBuffers = 4;
    pObj->radarFftParams1.workQcpuId =  SYSTEM_PROC_EVE1;

    ChainsCommon_ar12xxSetFFTParams(&pObj->radarFftParams2,
                                    &pObj->ar12xxCfg);
    /* EVE only does 1D FFT at 16 bit and 2D FFT at 32 bit */
    pObj->radarFftParams2.baseClassCreateParams.numOutputBuffers = 4;
    pObj->radarFftParams2.workQcpuId =  SYSTEM_PROC_EVE2;


    ChainsCommon_ar12xxSetFFTParams(&pObj->radarFftParams3,
                                    &pObj->ar12xxCfg);
    /* EVE only does 1D FFT at 16 bit and 2D FFT at 32 bit */
    pObj->radarFftParams3.baseClassCreateParams.numOutputBuffers = 4;
    pObj->radarFftParams3.workQcpuId =  SYSTEM_PROC_EVE3;

    ChainsCommon_ar12xxSetFFTParams(&pObj->radarFftParams4,
                                    &pObj->ar12xxCfg);
    /* EVE only does 1D FFT at 16 bit and 2D FFT at 32 bit */
    pObj->radarFftParams4.baseClassCreateParams.numOutputBuffers = 4;
    pObj->radarFftParams4.workQcpuId =  SYSTEM_PROC_EVE4;
    if (g2DFftOnEve == 1U)
    {
        pObj->radarFftParams1.algCreatePrm[1].outputContainerFormat = FFT_TI_CONTAINER_FORMAT_32BIT;
        pObj->radarFftParams2.algCreatePrm[1].outputContainerFormat = FFT_TI_CONTAINER_FORMAT_32BIT;
        pObj->radarFftParams3.algCreatePrm[1].outputContainerFormat = FFT_TI_CONTAINER_FORMAT_32BIT;
        pObj->radarFftParams4.algCreatePrm[1].outputContainerFormat = FFT_TI_CONTAINER_FORMAT_32BIT;
    }
    else
    {
        pObj->radarFftParams1.algFFTMode = RADAR_FFT_MODE_HORIZONTAL;
        pObj->radarFftParams2.algFFTMode = RADAR_FFT_MODE_HORIZONTAL;
        pObj->radarFftParams3.algFFTMode = RADAR_FFT_MODE_HORIZONTAL;
        pObj->radarFftParams4.algFFTMode = RADAR_FFT_MODE_HORIZONTAL;
    }

    ChainsUtil_updateFftAlgoParams(RADAR_CONFIG_PARAM_DIR_NAME, &pObj->radarFftParams1, 0);
    ChainsUtil_updateFftAlgoParams(RADAR_CONFIG_PARAM_DIR_NAME, &pObj->radarFftParams2, 1);
    ChainsUtil_updateFftAlgoParams(RADAR_CONFIG_PARAM_DIR_NAME, &pObj->radarFftParams3, 2);
    ChainsUtil_updateFftAlgoParams(RADAR_CONFIG_PARAM_DIR_NAME, &pObj->radarFftParams4, 3);

    Chains_SetSyncParams(&pUcObj->SyncPrm);

    Chains_RadarDspProcess_SetPrms(&pObj->radarDspOdParams,
                                   &pObj->ar12xxCfg);

    /* Select network mode */
#if !defined(NSP_TFDTP_INCLUDE)
    Vps_printf("Chains: Using TCP/IP\n");
    pUcObj->NetworkTxPrm.transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TCPIP;
#else
    Vps_printf("Chains: Using TFDTP. Ensure using --usetfdtp with network tools..\n");
    pUcObj->NetworkTxPrm.transmitDataType = NETWORK_TX_LINK_TRANSMIT_TYPE_TFDTP;
    /* no. of retry count */
    pUcObj->NetworkTxPrm.retryCount = NETWORK_TFDTP_RETRANSMIT_COUNT;
#endif
    return;
}

/**
 *******************************************************************************
 *
 * \brief   Cascade 4 channel radar sensor (AWR1243) capture, object detection
 *          and network output
 *
 *          This functions executes the create, start functions
 *
 *          Further in a while loop displays run time menu and waits
 *          for user inputs to print the statistics or to end the demo.
 *
 *          Once the user inputs end of demo stop and delete
 *          functions are executed.
 *
 * \param   chainsCfg       [IN]   Chains_Ctrl
 *
 *******************************************************************************
*/
Void Chains_cascadeRadarOd(Chains_Ctrl *chainsCfg)
{
    char ch;
    UInt32 done = FALSE;
    UInt32 localDone = FALSE;
    Chains_cascadeRadarOdAppObj chainsObj;
    char inputStr[100];
    UInt16 argc;
    char *argv[CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS];
    AlgorithmFxn_RadarDspProcessControlParams ctrlPrms;

    chainsObj.chainsCfg = chainsCfg;

    chainsObj.ucObj.Alg_RadarProcess_fft1Prm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams1;
    chainsObj.ucObj.Alg_RadarProcess_fft2Prm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams2;
    chainsObj.ucObj.Alg_RadarProcess_fft3Prm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams3;
    chainsObj.ucObj.Alg_RadarProcess_fft4Prm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarFftParams4;

    chainsObj.ucObj.Alg_RadarProcess_objectDetectPrm =
        (AlgorithmLink_RadarProcessCreateParams *)&chainsObj.radarDspOdParams;

    Chains_cascadeRadarOd_runTimeSelect();

    Chains_cascadeRadarOd_runTimeSelectUC();

    chains_cascadeRadarOd_Create(&chainsObj.ucObj, &chainsObj);

    chains_cascadeRadarOd_StartApp(&chainsObj);

    while(!done)
    {
        ch = Chains_cascadeRadarOd_runTimeMenu();

        switch(ch)
        {
            case '0':
                done = TRUE;
                break;
            case 'p':
            case 'P':
                ChainsCommon_PrintStatistics();
                chains_cascadeRadarOd_printStatistics(&chainsObj.ucObj);
                break;
            case 'g':
            case 'G':
#ifdef ENABLE_NETWORK_LOG
                Chains_readChar();
#endif
                localDone = FALSE;
                while(!localDone)
                {
                    Vps_printf("GUI Monitor (0/1) (<pointCloud> <rangeProfile> <noiseProfile> <rangeDopHeatMap> <azimuthHeatMap>):");
                    Chains_readString(inputStr, CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS * (CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS_LENGTH +1));
                    Chains_parseCmd(inputStr, &argc, (char **) &argv);

                    if(argc != 5)
                    {
                        Vps_printf("\nIncorrect number of arguments(%d)'. Please try again\n", argc);
                    }
                    else
                    {
                        ctrlPrms.baseClassControl.baseClassControl.size = sizeof(ctrlPrms);
                        ctrlPrms.baseClassControl.controlCmd = ALGORITHM_LINK_RADAR_PROCESS_CONTROL_CMD;
                        ctrlPrms.opControlParams.pointCloud     = atoi(argv[0]);
                        ctrlPrms.opControlParams.rangeProfile   = atoi(argv[1]);
                        ctrlPrms.opControlParams.noiseProfile   = atoi(argv[2]);
                        ctrlPrms.opControlParams.rangeDopHeatMap= atoi(argv[3]);
                        ctrlPrms.opControlParams.azimuthHeatMap = atoi(argv[4]);
                        ctrlPrms.dspControlCmd = ALGORITHM_FXN_RADAR_DSP_PROCESS_CMD_CHANGE_GUI;
                        System_linkControl(
                                chainsObj.ucObj.Alg_RadarProcess_objectDetectLinkID,
                                ALGORITHM_LINK_CMD_CONFIG,
                                &ctrlPrms,
                                sizeof(ctrlPrms),
                                TRUE
                        );
                        localDone = TRUE;
                    }
                }
                break;
            case 'c':
            case 'C':
#ifdef ENABLE_NETWORK_LOG
                Chains_readChar();
#endif
                localDone = FALSE;
                while(!localDone)
                {
                    Vps_printf("Calibration setting (<numFrames> <rangeStartBin> <rangeEndBin>):");
                    Chains_readString(inputStr, CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS * (CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS_LENGTH +1));
                    Chains_parseCmd(inputStr, &argc, (char **) &argv);

                    if(argc != 3)
                    {
                        Vps_printf("\nIncorrect number of arguments(%d)'. Please try again\n", argc);
                    }
                    else
                    {
                        ctrlPrms.baseClassControl.baseClassControl.size = sizeof(ctrlPrms);
                        ctrlPrms.baseClassControl.controlCmd = ALGORITHM_LINK_RADAR_PROCESS_CONTROL_CMD;
                        ctrlPrms.calibParams.state                      = ALGORITHMFXN_RADAR_DSP_PROCESS_CALIBRATION;
                        ctrlPrms.calibParams.numFrames                  = atoi(argv[0]);
                        ctrlPrms.calibParams.refTargetRangeWindowStart  = atoi(argv[1]);
                        ctrlPrms.calibParams.refTargetRangeWindowEnd    = atoi(argv[2]);
                        ctrlPrms.dspControlCmd = ALGORITHM_FXN_RADAR_DSP_PROCESS_CMD_RUN_CALIBRATION;
                        System_linkControl(
                                chainsObj.ucObj.Alg_RadarProcess_objectDetectLinkID,
                                ALGORITHM_LINK_CMD_CONFIG,
                                &ctrlPrms,
                                sizeof(ctrlPrms),
                                TRUE
                        );
                        localDone = TRUE;
                    }
                }
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }

    chains_cascadeRadarOd_StopAndDeleteApp(&chainsObj);
}

/**
 *******************************************************************************
 * \brief Run Time Menu string.
 *******************************************************************************
 */
char gChains_cascadeRadarOd_customRunTimeMenu[] = {
    "\r\n "
    "\r\n ===================="
    "\r\n Chains Run-time Menu"
    "\r\n ===================="
    "\r\n "
    "\r\n 0: Stop Chain"
    "\r\n "
    "\r\n p: Print Performance Statistics "
    "\r\n "
    "\r\n g: Control GUI output "
    "\r\n "
    "\r\n c: Control Calibration "
    "\r\n "
    "\r\n Enter Choice: "
    "\r\n "
};

char Chains_cascadeRadarOd_runTimeMenu()
{
    Vps_printf(gChains_cascadeRadarOd_customRunTimeMenu);

    return Chains_readChar();
}

static Void Chains_readString(char* inputString, UInt8 maxNumChar)
{
    char ch;
    UInt8 numChar = 0;

    while ( numChar < maxNumChar)
    {
        ch = Chains_readChar();

#ifdef ENABLE_UART_LOG
        Vps_printf("%c",ch);
#endif
        if((ch == 0x0d) || (ch==0x0a))
            break;

        inputString[numChar++] = ch;
    }
    inputString[numChar] = 0;
}
static Void Chains_parseCmd(char* inputStr, UInt16 *argc, char **argv)
{
    UInt16 argIndex = 0;
    while (1)
    {
        /* Tokenize the arguments: */
        argv[argIndex] = strtok(inputStr, " ");
        if (argv[argIndex] == NULL)
            break;

        /* Increment the argument index: */
        argIndex++;
        if (argIndex >= CHAINS_CASCADE_RADAR_MAX_INPUT_ARGS)
            break;

        /* Reset the command string */
        inputStr = NULL;
    }
    *argc = argIndex;
}

static char gChains_cascadeRadarOd_runTimeSelect[] = {
    "\r\n "
    "\r\n ========================"
    "\r\n 2D FFT Core Selection"
    "\r\n ========================"
    "\r\n "
    "\r\n 1: DSP"
    "\r\n "
    "\r\n 2: EVE"
    "\r\n"
    "\r\n Enter Choice: "
    "\r\n "
};

static Void Chains_cascadeRadarOd_runTimeSelect()
{
    char ch;
    UInt32 done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_cascadeRadarOd_runTimeSelect);
        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                g2DFftOnEve = 0U;
                done = TRUE;
                break;
            case '2':
                g2DFftOnEve = 1U;
                done = TRUE;
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}

static char gChains_cascadeRadarOd_runTimeSelectUC[] = {
    "\r\n "
    "\r\n ========================"
    "\r\n Usecase Selection"
    "\r\n ========================"
    "\r\n "
    "\r\n 1: MIMO 8 Tx"
    "\r\n "
    "\r\n 2: Beam Forming (Angle Estimation Not Supported)"
    "\r\n"
    "\r\n Enter Choice: "
    "\r\n "
};

static Void Chains_cascadeRadarOd_runTimeSelectUC()
{
    char ch;
    UInt32 done = FALSE;

    while(!done)
    {
        Vps_printf(gChains_cascadeRadarOd_runTimeSelectUC);
        ch = Chains_readChar();
        switch(ch)
        {
            case '1':
                gCascadeRadarUC = CASCADE_RADAR_MIMO_MODE;
                done = TRUE;
                break;
            case '2':
                gCascadeRadarUC = CASCADE_RADAR_TX_BEAMFORMING_MODE;
                done = TRUE;
                break;
            default:
                Vps_printf("\nUnsupported option '%c'. Please try again\n", ch);
                break;
        }
    }
}
