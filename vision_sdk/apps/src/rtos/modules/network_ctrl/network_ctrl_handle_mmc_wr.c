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
#include "network_ctrl_fileiocmdhandler.h"
#include <src/rtos/utils_common/include/utils_mem.h>
#include <src/include/chains_common_osal.h>

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Void fileIOCmdHandler(UInt32 cmd, Void *pPrm);


/**
 *******************************************************************************
 *
 * \brief   NetworkCtrl_fileIOCmdHandler_Init
 *
 *          This function registers command handler in system
 *          link for file IO comands.
 *
 * \param   NULL
 *
  *******************************************************************************
 */
Void NetworkCtrl_fileIOCmdHandler_Init()
{
    SystemLink_registerHandler(fileIOCmdHandler);
}

/**
 *******************************************************************************
 *
 * \brief   NetworkCtrl_fileIOCmdHandler_DeInit
 *
 *          This function deregisters command handler in system
 *          link for file IO comands.
 *
 * \param   NULL
 *
 *******************************************************************************
 */
Void NetworkCtrl_fileIOCmdHandler_DeInit()
{
    SystemLink_unregisterHandler(fileIOCmdHandler);
}

/**
 *******************************************************************************
 *
 * \brief   callback to handle file IO using system link
 *
 *  \param  cmd [IN] Command that needs to be handled
 *               pPrm [IN/OUT] Parameters for this command
 *
 *******************************************************************************
 */
static Void fileIOCmdHandler(UInt32 cmd, Void *pPrm)
{
    Int32 retVal = 0;
    Int32 chunkSize = CHAINSCOMMON_OSAL_FILEWRITE_CHUNKSIZE;
    UInt8  *curAddr;
    UInt32 numChunks, partChunk, cnt;
    FileIO_NetworkCtrlParams *fileIOPrms;


    if (NULL != pPrm)
    {
        fileIOPrms = (FileIO_NetworkCtrlParams *)pPrm;

        if (SYSTEM_LINK_CMD_OPEN_FILE == cmd)
        {
            Vps_printf(" FILEIO: Received file open command B\n");
            fileIOPrms->filePtr = File_open(fileIOPrms->fileName, fileIOPrms->fileMode);
            UTILS_assert (-1 != fileIOPrms->filePtr);

        }
        else if (SYSTEM_LINK_CMD_CLOSE_FILE == cmd)
        {
            Vps_printf(" FILEIO: Received file close command B\n");
            File_close(fileIOPrms->filePtr);
        }
        else if (SYSTEM_LINK_CMD_WRITE_FILE == cmd)
        {
            Vps_printf(" FILEIO: Received file write command- size is %d B\n",
                                                          fileIOPrms->dataSize);

            curAddr  = fileIOPrms->dataAddr;

            numChunks = fileIOPrms->dataSize/chunkSize;
            partChunk = fileIOPrms->dataSize % chunkSize;

            for(cnt = 0;cnt < numChunks;cnt ++)
            {
                retVal = File_write(fileIOPrms->filePtr, curAddr, (UInt32)chunkSize);
                if(retVal != 0)
                {
                    /* error in writing, abort */
                    UTILS_assert (FALSE);
                    break;
                }

                curAddr += chunkSize;
            }

            if(partChunk != 0)
            {
                retVal = File_write(fileIOPrms->filePtr, curAddr, (UInt32)partChunk);
            }

            Vps_printf(" FILEIO: File write complete \n");

        }
        else if (SYSTEM_LINK_CMD_READ_FILE == cmd)
        {

        }

    }
}
