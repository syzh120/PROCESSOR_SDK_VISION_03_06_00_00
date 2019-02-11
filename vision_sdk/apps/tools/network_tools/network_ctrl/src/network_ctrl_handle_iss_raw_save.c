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

#include "network_ctrl_priv.h"
#include <osa_file.h>

#define NETWORKCTRL_ISS_DCC_FILE_SIZE       (128*1024U)

#define NETWORKCTRL_ISS_QSPI_OFFSET         (24U*1024U*1024U)

#define NETWORKCTRL_ISS_DCC_BIN_HEADER_SIZE (16U)

#define NETWORKCTRL_ISS_DCC_BIN_TAG_ID      (0x00DCCBEEU)

UInt8   pDccDataBuf[NETWORKCTRL_ISS_DCC_FILE_SIZE];

/* Same Structure is present on Target,
   If the definition of this structure changes on target, make the
   change here also */
typedef struct {
    UInt32                aeMode;
    /**< AE Mode, used to enable/disable AE.
         It could be either AUTO (0) or manual (1),
         Auto mode is default and runs the AE algorithms
         Manual mode uses below AE parameters value as AE output */
    UInt32                digitalGain;
    /**< Digital Gain for manual AE mode */
    UInt32                analogGain;
    /**< Analog Gain for manual AE mode */
    UInt32                expTime;
    /**< Exposure time for manual AE mode */
    UInt32                awbMode;
    /**< AWB Mode, used to enable/disable AWB.
         It could be either AUTO (0) or manual (1),
         Auto mode is default and runs the AWB algorithms
         Manual mode uses below AWB parameters value as AE output */
    UInt32                rGain;
    /**< Red color gain for manual AWB mode*/
    UInt32                gGain;
    /**< Green color gain for manual AWB mode*/
    UInt32                bGain;
    /**< Blue color gain for manual AWB mode*/

    UInt32                colorTemp;
    /**< Color Temparature for manual AWB mode*/
} IssAewb2AParams;


void handleIssRawSave()
{
    UInt32 *pMem;
    UInt32 prmSize = 0;

    SendCommand(gNetworkCtrl_obj.command, NULL, 0);
    RecvResponse(gNetworkCtrl_obj.command, &prmSize);

    if(prmSize)
    {
        pMem = malloc(prmSize);
        if(pMem==NULL)
        {
            printf("# ERROR: Command %s: Unable to allocate memory for response parameters\n", gNetworkCtrl_obj.command);
            exit(0);
        }

        RecvResponseParams(gNetworkCtrl_obj.command, (UInt8*)pMem, prmSize);

        OSA_fileWriteFile(gNetworkCtrl_obj.params[0], (UInt8*)pMem, prmSize);
    }
    else
    {
        printf("# ERROR: Command %s: Target unable to save RAW data\n", gNetworkCtrl_obj.command);
    }
}

void handleIssYuvSave()
{
    UInt32 *pMem;
    UInt32 prmSize = 0;

    SendCommand(gNetworkCtrl_obj.command, NULL, 0);
    RecvResponse(gNetworkCtrl_obj.command, &prmSize);

    if(prmSize)
    {
        pMem = malloc(prmSize);
        if(pMem==NULL)
        {
            printf("# ERROR: Command %s: Unable to allocate memory for response parameters\n", gNetworkCtrl_obj.command);
            exit(0);
        }

        RecvResponseParams(gNetworkCtrl_obj.command, (UInt8*)pMem, prmSize);

        OSA_fileWriteFile(gNetworkCtrl_obj.params[0], (UInt8*)pMem, prmSize);
    }
    else
    {
        printf("# ERROR: Command %s: Target unable to save RAW data\n", gNetworkCtrl_obj.command);
    }
}

void handleIssIspSave()
{
    UInt32 *pMem;
    UInt32 prmSize = 0;

    SendCommand(gNetworkCtrl_obj.command, NULL, 0);
    RecvResponse(gNetworkCtrl_obj.command, &prmSize);

    if(prmSize)
    {
        pMem = malloc(prmSize);
        if(pMem==NULL)
        {
            printf("# ERROR: Command %s: Unable to allocate memory for response parameters\n", gNetworkCtrl_obj.command);
            exit(0);
        }

        RecvResponseParams(gNetworkCtrl_obj.command, (UInt8*)pMem, prmSize);

        OSA_fileWriteFile(gNetworkCtrl_obj.params[0], (UInt8*)pMem, prmSize);
    }
    else
    {
        printf("# ERROR: Command %s: Target unable to save RAW data\n", gNetworkCtrl_obj.command);
    }
}

void handleIssSendDccFile()
{
    Int32 status;
    UInt32 size;

    status = OSA_fileReadFile(
        gNetworkCtrl_obj.params[0],
        pDccDataBuf,
        NETWORKCTRL_ISS_DCC_FILE_SIZE,
        &size);

    if (0 == status)
    {
        SendCommand(gNetworkCtrl_obj.command, pDccDataBuf, size);
        RecvResponse(gNetworkCtrl_obj.command, NULL);
    }
}

void handleIssSaveDccFile()
{
    Int32 status;
    UInt32 size;
    UInt32 *pDccBuf;

    pDccBuf = (UInt32 *)pDccDataBuf;

    /* First four word contains header information, so actual
       buffer is stored after four words */
    status = OSA_fileReadFile(
        gNetworkCtrl_obj.params[1],
        (UInt8*)(pDccBuf + NETWORKCTRL_ISS_DCC_BIN_HEADER_SIZE/4),
        NETWORKCTRL_ISS_DCC_FILE_SIZE,
        &size);

    if (0 == status)
    {
        /* Set the TAG Word */
        *pDccBuf = NETWORKCTRL_ISS_DCC_BIN_TAG_ID;
        pDccBuf ++;

        /* Set the Size of the DCC file */
        *pDccBuf = size;
        pDccBuf ++;

        /* Third word is used to store sensor dcc id information */
        *pDccBuf = (UInt32)atoi(gNetworkCtrl_obj.params[0]);
        pDccBuf ++;

        *pDccBuf = 0U;

        SendCommand(gNetworkCtrl_obj.command, pDccDataBuf,
                    size + NETWORKCTRL_ISS_DCC_BIN_HEADER_SIZE);
        RecvResponse(gNetworkCtrl_obj.command, NULL);
    }
}

void handleIssClearDccQspiMem()
{
    UInt32 dccCameraId;

    dccCameraId = atoi(gNetworkCtrl_obj.params[0]);

    SendCommand(gNetworkCtrl_obj.command, &dccCameraId,
                sizeof(dccCameraId));
    RecvResponse(gNetworkCtrl_obj.command, NULL);
}

void handleIssSensorRegWrite()
{
    UInt32 prms[3];

    prms[0] = atoi(gNetworkCtrl_obj.params[0]); /* Channel number */
    prms[1] = strtol(gNetworkCtrl_obj.params[1], NULL, 0); /* Register Address */
    prms[2] = strtol(gNetworkCtrl_obj.params[2], NULL, 0); /* Register Value */

    printf("\n\nISS Sensor Write: Dev[0x%04x]: Reg[0x%04x] = 0x%04x\n\n",
        prms[0], prms[1], prms[2]);

    SendCommand(gNetworkCtrl_obj.command, prms,
                sizeof(prms));
    RecvResponse(gNetworkCtrl_obj.command, NULL);
}

void handleIssSensorRegRead()
{
    UInt32 prms[2], prmSize, readValue;

    prms[0] = atoi(gNetworkCtrl_obj.params[0]); /* Channel number */
    prms[1] = strtol(gNetworkCtrl_obj.params[1], NULL, 0); /* Register Address */

    SendCommand(gNetworkCtrl_obj.command, prms,
                sizeof(prms));
    RecvResponse(gNetworkCtrl_obj.command, &prmSize);

    if (prmSize)
    {
        RecvResponseParams(gNetworkCtrl_obj.command, (UInt8*)&readValue,
            prmSize);

        printf("\n\nISS Sensor Read: Dev[0x%04x]: Reg[0x%04x] = 0x%04x\n\n",
            prms[0], prms[1], readValue);
    }
    else
    {
        printf("ISS Sensor Read: Could not read data");
    }
}

void handleIssWrite2AParams()
{
    IssAewb2AParams aewb2APrms;

    aewb2APrms.aeMode = atoi(gNetworkCtrl_obj.params[0]);
    aewb2APrms.digitalGain = atoi(gNetworkCtrl_obj.params[1]);
    aewb2APrms.analogGain = atoi(gNetworkCtrl_obj.params[2]);
    aewb2APrms.expTime = atoi(gNetworkCtrl_obj.params[3]);
    aewb2APrms.awbMode = atoi(gNetworkCtrl_obj.params[4]);
    aewb2APrms.rGain = atoi(gNetworkCtrl_obj.params[5]);
    aewb2APrms.gGain = atoi(gNetworkCtrl_obj.params[6]);
    aewb2APrms.bGain = atoi(gNetworkCtrl_obj.params[7]);
    aewb2APrms.colorTemp = atoi(gNetworkCtrl_obj.params[8]);

    SendCommand(gNetworkCtrl_obj.command, &aewb2APrms,
                sizeof(aewb2APrms));
    RecvResponse(gNetworkCtrl_obj.command, NULL);
}

void handleIssRead2AParams()
{
    UInt32 prmSize;
    IssAewb2AParams aewb2APrms;
    char mode[][10] = {"Auto", "Manual"};

    SendCommand(gNetworkCtrl_obj.command, &aewb2APrms,
                sizeof(aewb2APrms));
    RecvResponse(gNetworkCtrl_obj.command, &prmSize);

    if (prmSize == sizeof(aewb2APrms))
    {
        RecvResponseParams(gNetworkCtrl_obj.command,
            (UInt8*)&aewb2APrms,
            prmSize);

        if (aewb2APrms.aeMode)
        {
            aewb2APrms.aeMode = 1;
        }
        if (aewb2APrms.awbMode)
        {
            aewb2APrms.awbMode = 1;
        }

        printf("\n\n");
        printf("  =========================================\n");
        printf("  Auto Exposure Algorithm State Information\n");
        printf("  =========================================\n");
        printf("    Mode                = %s\n", mode[aewb2APrms.aeMode]);
        printf("    Digital Gain        = %d\n", aewb2APrms.digitalGain);
        printf("    Analog Gain         = %d\n", aewb2APrms.analogGain);
        printf("    Exposure Time       = %d\n\n", aewb2APrms.expTime);
        printf("  ==============================================\n");
        printf("  Auto White Balance Algorithm State Information\n");
        printf("  ==============================================\n\n");
        printf("    Mode                = %s\n", mode[aewb2APrms.awbMode]);
        printf("    Red Gain            = %d\n", aewb2APrms.rGain);
        printf("    Green Gain          = %d\n", aewb2APrms.gGain);
        printf("    Blue Gain           = %d\n", aewb2APrms.bGain);
        printf("    Color Temparature   = %d\n", aewb2APrms.colorTemp);
        printf("\n\n");
    }
    else
    {
        printf("ISS Read 2A Params: Could not read data");
    }
}



