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

#define NETWORKCTRL_STEREO_CALIB_LUT_SIZE   		(3*1024U*1024U)

#define NETWORKCTRL_STEREO_CALIB_LUT_QSPI_OFFSET    (29U*1024U*1024U)

#define NETWORKCTRL_STEREO_CALIB_LUT_HEADER_SIZE 	(16U)

#define NETWORKCTRL_STEREO_CALIB_LUT_FILE_NAME_SIZE	(30U)

#define NETWORKCTRL_STEREO_CALIB_LUT_TAG_ID      	(0x00CCAABBU)

UInt8   pCalibData[NETWORKCTRL_STEREO_CALIB_LUT_SIZE];

void handleStereoCalibImageSave()
{
    UInt32 *pMem;
    UInt32 prmSize = 0;
    char filename[100];

    SendCommand(gNetworkCtrl_obj.command, NULL, 0);
    RecvResponse(gNetworkCtrl_obj.command, &prmSize);

    if(prmSize)
    {
        pMem = malloc(prmSize);
        if(pMem==NULL)
        {
            printf("# ERROR: Command %s: Unable to allocate memory for \
                            response parameters\n", gNetworkCtrl_obj.command);
            exit(0);
        }

        RecvResponseParams(gNetworkCtrl_obj.command, (UInt8*)pMem, prmSize);

        strcpy(filename,"right_");
        strcat(filename, gNetworkCtrl_obj.params[0]);
        strcat(filename, ".pgm");
        OSA_fileWriteFile(filename, (UInt8*)pMem, prmSize/2);

        strcpy(filename,"left_");
        strcat(filename, gNetworkCtrl_obj.params[0]);
        strcat(filename, ".pgm");
        OSA_fileWriteFile(filename, (UInt8*)pMem + prmSize/2, prmSize/2);
    }
    else
    {
        printf("# ERROR: Command %s: Target unable to save RAW data\n"
                                                    , gNetworkCtrl_obj.command);
    }
}

void handleStereoWriteCalibLUTDataToQSPI()
{
    Int32 status;
    UInt32 sizeL, sizeR;
    UInt32 *pCalibLUTBuf;

    /* Store the QSPI offset in the first word */
    pCalibLUTBuf = (UInt32 *)pCalibData;

    /* First four words contains header information, so save LUT
       bin file after first four words */
    //RIght Channel LUT
    status = OSA_fileReadFile(
        gNetworkCtrl_obj.params[0],
        (UInt8*)(pCalibLUTBuf + NETWORKCTRL_STEREO_CALIB_LUT_HEADER_SIZE/4),
        NETWORKCTRL_STEREO_CALIB_LUT_SIZE/2,
        &sizeR);

	//Left Channel LUT
	status = OSA_fileReadFile(
        gNetworkCtrl_obj.params[1],
        (UInt8*)(pCalibLUTBuf + NETWORKCTRL_STEREO_CALIB_LUT_HEADER_SIZE/4 + sizeR/4),
        NETWORKCTRL_STEREO_CALIB_LUT_SIZE/2,
        &sizeL);

    if (0 == status)
    {
    
        printf("# Writing the QSPI tags\n");
        /* Set the TAG Word */
        *pCalibLUTBuf = NETWORKCTRL_STEREO_CALIB_LUT_TAG_ID;
        pCalibLUTBuf ++;

        /* Set the Size of the DCC file */
        *pCalibLUTBuf = sizeR+sizeL+NETWORKCTRL_STEREO_CALIB_LUT_HEADER_SIZE;
        pCalibLUTBuf ++;

        *pCalibLUTBuf = NETWORKCTRL_STEREO_CALIB_LUT_QSPI_OFFSET;
		pCalibLUTBuf ++;

		*pCalibLUTBuf = 0U;

        SendCommand(gNetworkCtrl_obj.command, pCalibData,
                    sizeL + sizeR + NETWORKCTRL_STEREO_CALIB_LUT_HEADER_SIZE);
        RecvResponse(gNetworkCtrl_obj.command, NULL);
    }
}
