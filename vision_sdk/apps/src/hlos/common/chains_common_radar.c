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

#include <src/hlos/adas/include/chains_common_radar.h>

Int32 ChainsCommon_readSensorFileInfo(const char *rootDirName,
                                      const char *sensorFileName,
                                      ChainsCommon_ConfigFileInfo  * cfgInfo)
{
    char        valueSt[CHAINS_RADAR_MAX_LINE_LEN];
    char        sLine[CHAINS_RADAR_MAX_LINE_LEN];
    char        fileName[CHAINS_RADAR_MAX_LINE_LEN];
    char      * pValueStr;
    char      * pSLine;
    char      * name;
    FILE      * file;
    UInt32      id;
    Bool        done = FALSE;
    Int32       status = SYSTEM_LINK_STATUS_SOK;

    pValueStr = &valueSt[0];
    pSLine    = &sLine[0];

    sprintf(fileName,"%s%s", rootDirName, sensorFileName);
    Vps_printf("Parsing %s\n", fileName);
    file = fopen(fileName, "r");
    if(file != NULL)
    {
        memset(cfgInfo, 0, sizeof(ChainsCommon_ConfigFileInfo));

        while (done != TRUE)
        {
            pSLine = fgets(pSLine, CHAINS_RADAR_MAX_LINE_LEN, file);
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
        status = fclose(file);
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;
}

Int32 ChainsCommon_readMasterFileInfo(const char *rootDirName,
                                      ChainsCommon_MasterFileInfo *mstInfo)
{
    char        paramSt[CHAINS_RADAR_MAX_LINE_LEN];
    char        valueSt[CHAINS_RADAR_MAX_LINE_LEN];
    char        sLine[CHAINS_RADAR_MAX_LINE_LEN];
    char        fileName[CHAINS_RADAR_MAX_LINE_LEN];
    char      * pParamStr;
    char      * pValueStr;
    char      * pSLine;
    FILE      * file;
    Bool        done = FALSE;
    Int32       status = SYSTEM_LINK_STATUS_SOK;


    pParamStr = &paramSt[0];
    pValueStr = &valueSt[0];
    pSLine    = &sLine[0];

    sprintf(fileName,"%s%s", rootDirName, MASTER_SENSOR_CONFIG_FILENAME);
    Vps_printf("Parsing %s\n", fileName);

    file = fopen(fileName, "r");

    if (file != NULL)
    {
        memset(mstInfo, 0, sizeof(ChainsCommon_MasterFileInfo));
        while (done != TRUE)
        {
            pSLine = fgets(pSLine, CHAINS_RADAR_MAX_LINE_LEN, file);
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
        status = fclose(file);
    }
    else
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    return status;

}

Int32 ChainsCommon_OpenRadarConfigFile(char *rootDirName,
                                       AppCtrl_RadarConfigFiles *pConfigFiles)
{
    ChainsCommon_MasterFileInfo mstInfo;
    ChainsCommon_ConfigFileInfo cfg;
    AppCtrl_RadarConfigFileParams *pFileParams;
    UInt8 *pRadarCfg, *pVirtRadarCfg;
    UInt32 fileSize;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 i;
    char fileName[CHAINS_RADAR_MAX_LINE_LEN];

    UTILS_assert(NULL != pConfigFiles);
    pConfigFiles->numFiles = 0;

    /* Get the Master file information. */
    status = ChainsCommon_readMasterFileInfo(rootDirName, &mstInfo);

    if (SYSTEM_LINK_STATUS_SOK == status)
    {
        status = ChainsCommon_readSensorFileInfo(rootDirName, mstInfo.feMaster, &cfg);
        if (SYSTEM_LINK_STATUS_SOK == status)
        {
            for (i = 0; (i < mstInfo.numSensors) && (SYSTEM_LINK_STATUS_SOK == status); i++)
            {
                pFileParams = &pConfigFiles->fileParams[i];
                if (cfg.fileName[i][0] != 0)
                {
                    sprintf(fileName,"%s%s", rootDirName, cfg.fileName[i]);
                    fileSize = OSA_fileGetSize(fileName);
                    if(fileSize != 0)
                    {
                        pRadarCfg = (UInt8 *) ChainsCommon_Osal_memAlloc(fileSize, 32u);
                        if (pRadarCfg != NULL)
                        {
                            pVirtRadarCfg = (UInt8 *) ChainsCommon_Osal_getVirtAddr((UInt32) pRadarCfg);
                            if (pVirtRadarCfg !=0)
                            {
                                Vps_printf("Reading Radar[%d] Config file [%s]\n", i, fileName);
                                OSA_fileReadFile(fileName, pVirtRadarCfg, fileSize, NULL);
                            }
                            else
                            {
                                status = SYSTEM_LINK_STATUS_EFAIL;
                                Vps_printf(
                                    "ChainsCommon_OpenRadarConfigFile: Could not get virtual address\n");
                            }
                        }
                        else
                        {
                            status = SYSTEM_LINK_STATUS_EFAIL;
                            Vps_printf(
                                "ChainsCommon_OpenRadarConfigFile: Could not allocate Radar Config file buffer\n");
                        }
                    }
                    else
                    {
                        status = SYSTEM_LINK_STATUS_EFAIL;
                        Vps_printf("ChainsCommon_OpenRadarConfigFile: Could not open Radar Config file\n");
                    }
                    if (SYSTEM_LINK_STATUS_SOK == status)
                    {
                        /* Make sure the buffer is writen to physical memory */
                        OSA_memCacheWb((unsigned int)pVirtRadarCfg,
                            (unsigned int)pVirtRadarCfg + fileSize);

                        pFileParams->pConfigBuf = pRadarCfg;
                        pFileParams->bufSize = fileSize;
                        pConfigFiles->numFiles++;
                        Vps_printf("ChainsCommon_OpenRadarConfigFile: Radar Config file buffer @ 0x%x\n", pFileParams->pConfigBuf);
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
