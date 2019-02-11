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

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/include/chains.h>
#include <src/include/chains_common.h>
#include <src/include/chains_common_tidl.h>

/******************************************************************************
 *  TIDL Common functions:
 *      The following functions should be in sync with the similar functions
 *      defined in the $(tidl_PATH)\modules\ti_dl\test\src\tidl_tb.c file.
 *          Chains_tidlReadNet <->  tidl_readNet
 *          Chains_tidlAllocNetParamsMem <-> tidl_allocNetParamsMem
 *          Chains_tidlFillNetParamsMem <-> tidl_fillNetParamsMem
 ******************************************************************************/

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_tidlReadNet(sTIDL_Network_t *net, char *netFile)
{
    Int32 fp;
    UInt32 readSize;

    fp = ChainsCommon_Osal_fileOpen(
                            netFile,
                            CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
    UTILS_assert(-1 != fp);

    ChainsCommon_Osal_fileRead(
                            fp,
                            (UInt8*)net,
                            sizeof(sTIDL_Network_t),
                            &readSize);
    UTILS_assert(readSize == sizeof(sTIDL_Network_t));

    ChainsCommon_Osal_fileClose(fp);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_tidlAllocNetParamsMem(sTIDL_Network_t *net)
{
    Int32 i;

    for(i = 0; i < net->numLayers; i++)
    {
        if((TIDL_ConvolutionLayer == net->TIDLLayers[i].layerType) ||
           (TIDL_Deconv2DLayer == net->TIDLLayers[i].layerType))
        {
            sTIDL_ConvParams_t *conv2dPrms = \
                                            &net->TIDLLayers[i].layerParams.convParams;
            conv2dPrms->weights.bufSize = \
                net->weightsElementSize * (conv2dPrms->kernelW * conv2dPrms->kernelH *
                conv2dPrms->numInChannels * conv2dPrms->numOutChannels)
                /conv2dPrms->numGroups;
            conv2dPrms->weights.ptr = \
                ChainsCommon_Osal_memAlloc(conv2dPrms->weights.bufSize, 32);

            conv2dPrms->bias.bufSize = net->biasElementSize * conv2dPrms->numOutChannels;
            conv2dPrms->bias.ptr = \
                ChainsCommon_Osal_memAlloc(conv2dPrms->bias.bufSize, 32);
        }
        else if(TIDL_BiasLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_BiasParams_t *biasPrms = &net->TIDLLayers[i].layerParams.biasParams;
            biasPrms->bias.bufSize = net->biasElementSize * biasPrms->numChannels;
            biasPrms->bias.ptr = \
                ChainsCommon_Osal_memAlloc(biasPrms->bias.bufSize, 32);
        }
        else if(TIDL_BatchNormLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_BatchNormParams_t *batchNormPrms = \
                &net->TIDLLayers[i].layerParams.batchNormParams;
            batchNormPrms->weights.bufSize = \
                 net->weightsElementSize * batchNormPrms->numChannels;
            batchNormPrms->weights.ptr =
                ChainsCommon_Osal_memAlloc(batchNormPrms->weights.bufSize, 32);

            batchNormPrms->bias.bufSize = \
                net->biasElementSize * batchNormPrms->numChannels;
            batchNormPrms->bias.ptr =
                ChainsCommon_Osal_memAlloc(batchNormPrms->bias.bufSize, 32);

            batchNormPrms->reluParams.slope.bufSize =
                net->slopeElementSize * batchNormPrms->numChannels;
            if(TIDL_PRelU == batchNormPrms->reluParams.reluType)
            {
                batchNormPrms->reluParams.slope.ptr = \
                    ChainsCommon_Osal_memAlloc(
                            batchNormPrms->reluParams.slope.bufSize, 32);
            }
        }
        else if(TIDL_InnerProductLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_InnerProductParams_t *ipPrms = \
                                    &net->TIDLLayers[i].layerParams.innerProductParams;
            ipPrms->bias.bufSize =  net->biasElementSize * ipPrms->numOutNodes;
            ipPrms->bias.ptr = \
                ChainsCommon_Osal_memAlloc(
                    SystemUtils_align(ipPrms->bias.bufSize, 128), 32);

            ipPrms->weights.bufSize = \
                net->weightsElementSize* ipPrms->numInNodes * ipPrms->numOutNodes;
            ipPrms->weights.ptr = \
                ChainsCommon_Osal_memAlloc(
                    SystemUtils_align((ipPrms->weights.bufSize + 16 * \
                        net->TIDLLayers[i].layerParams.innerProductParams.numInNodes),
                            1024), 32);
        }
        else if(TIDL_DetectionOutputLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_DetectOutputParams_t *detectPrms = \
                             &net->TIDLLayers[i].layerParams.detectOutParams;
            detectPrms->priorBox.bufSize =  detectPrms->priorBoxSize * sizeof(float);
            detectPrms->priorBox.ptr = ChainsCommon_Osal_memAlloc(
                        SystemUtils_align(detectPrms->priorBoxSize *
                                            detectPrms->priorBox.bufSize, 128), 32);
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Void Chains_sparseConv2dCoffesS8(Int8 *ptr, Int32 n, UInt8 thr)
{
    Int32 i0;

    for(i0 = 0; i0 < n; i0++)
    {
        if(((UInt8)(rand() & 0xFF)) > thr)
        {
            ptr[i0] =  0;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Void Chains_createRandPatternS16(Int16 *ptr, Int16 n, Int16 width, Int16 height,
                                 Int16 pitch, Int32 chOffset)
{
    Int16 val;
    Int32 i0, i1, i2;
    for(i0 = 0; i0 < n; i0++)
    {
        for(i1 = 0; i1 < height; i1++)
        {
            for(i2 = 0; i2 < width; i2++)
            {
                val = rand() & 0x7FFF;
                ptr[i0 * chOffset + i1 * pitch + i2] = (rand() & 1) ? val : -val;
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Void Chains_createRandPatternS8(Int8 *ptr, Int16 roi, Int16 n,
                                Int16 width, Int16 height, Int16 pitch,
                                Int32 chOffset)
{
    Int16 val;
    Int32   i0, i1, i2, i3;

    for(i3 = 0; i3 < roi; i3++)
    {
        for(i0 = 0; i0 < n; i0++)
        {
            for(i1 = 0; i1 < height; i1++)
            {
                for(i2 = 0; i2 < width; i2++)
                {
                    val = rand() & 0x7F;
                    ptr[i3 * n * chOffset + i0 * chOffset + i1 * pitch +i2] = \
                        (rand() & 1) ? val : -val;
                }
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_tidlFillNetParamsMem(sTIDL_Network_t *net, char *prmFile)
{
    Int32 i;
    Int32 fp;
    UInt32 dataSize, readSize;

    fp = ChainsCommon_Osal_fileOpen(
                        prmFile,
                        CHAINSCOMMON_OSAL_FILEMODE_READ_BIN);
    UTILS_assert(-1 != fp);

    for(i = 0; i < net->numLayers; i++)
    {
        if((TIDL_ConvolutionLayer == net->TIDLLayers[i].layerType) ||
           (TIDL_Deconv2DLayer == net->TIDLLayers[i].layerType))
        {
            sTIDL_ConvParams_t *conv2dPrms = &net->TIDLLayers[i].layerParams.convParams;

            if(RANDOM_INPUT)
            {
                Chains_createRandPatternS8(
                    (Int8 *)conv2dPrms->weights.ptr, 1,
                    conv2dPrms->numInChannels/conv2dPrms->numGroups,
                    conv2dPrms->numOutChannels,
                    conv2dPrms->kernelW * conv2dPrms->kernelH,
                    conv2dPrms->numOutChannels,
                    conv2dPrms->kernelW * conv2dPrms->kernelW * conv2dPrms->numOutChannels);

                if(NO_ZERO_COEFF_PERCENT < 100)
                {
                    Chains_sparseConv2dCoffesS8((Int8 *)conv2dPrms->weights.ptr,
                                conv2dPrms->weights.bufSize,
                                NO_ZERO_COEFF_PERCENT * 2.55);
                }

                if(conv2dPrms->enableBias)
                {
                    dataSize = conv2dPrms->numOutChannels;
                    Chains_createRandPatternS16((Int16 *)conv2dPrms->bias.ptr,1,dataSize,1,1,1);
                }
                else
                {
                    memset(
                        (Int8 *)conv2dPrms->bias.ptr,0,conv2dPrms->numOutChannels * 2);
                }
            }
            else
            {
                dataSize = (conv2dPrms->numInChannels * conv2dPrms->numOutChannels *
                    conv2dPrms->kernelW * conv2dPrms->kernelH)/conv2dPrms->numGroups;

                /* Read weights based on its size */
                if(net->weightsElementSize == 2)
                {
                    ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)conv2dPrms->weights.ptr,
                        (dataSize * 2),
                        &readSize);
                        UTILS_assert(readSize == (dataSize * 2));
                }
                else
                {
                    ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)conv2dPrms->weights.ptr,
                        dataSize,
                        &readSize);
                        UTILS_assert(readSize == dataSize);
                }

                if(NO_ZERO_COEFF_PERCENT < 100)
                {
                    Chains_sparseConv2dCoffesS8((Int8 *)conv2dPrms->weights.ptr,
                        conv2dPrms->weights.bufSize,
                        NO_ZERO_COEFF_PERCENT * 2.55);
                }

                if(conv2dPrms->enableBias)
                {
                    dataSize = conv2dPrms->numOutChannels;
                    ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)conv2dPrms->bias.ptr,
                        (dataSize * 2),
                        &readSize);
                        UTILS_assert(readSize == (dataSize * 2));
                }
                else
                {
                    memset(
                        (Int8 *)conv2dPrms->bias.ptr,0,conv2dPrms->numOutChannels * 2);
                }
            }

            /* Cache Wb of the buffers */
            dataSize = (conv2dPrms->numInChannels * conv2dPrms->numOutChannels *
                    conv2dPrms->kernelW * conv2dPrms->kernelH)/conv2dPrms->numGroups;
            if(net->weightsElementSize == 2)
            {
                dataSize *= 2;
            }
            Cache_wb(
                (UInt8*)conv2dPrms->weights.ptr,
                dataSize,
                Cache_Type_ALLD,
                TRUE);

            dataSize = conv2dPrms->numOutChannels;
            Cache_wb(
                (UInt8*)conv2dPrms->bias.ptr,
                dataSize,
                Cache_Type_ALLD,
                TRUE);
        }
        else if(TIDL_BiasLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_BiasParams_t *biasPrms =&net->TIDLLayers[i].layerParams.biasParams;
            dataSize = biasPrms->numChannels;
            if(RANDOM_INPUT)
            {
                Chains_createRandPatternS16((Int16 *)biasPrms->bias.ptr,1,dataSize,1,1,1);
                Cache_wb(
                    (UInt8*)biasPrms->bias.ptr,
                    dataSize,
                    Cache_Type_ALLD,
                    TRUE);
            }
            else
            {
                ChainsCommon_Osal_fileRead(
                    fp,
                    (UInt8*)biasPrms->bias.ptr,
                    (dataSize * 2),
                    &readSize);
                    UTILS_assert(readSize == (dataSize * 2));
                Cache_wb(
                    (UInt8*)biasPrms->bias.ptr,
                    (dataSize * 2),
                    Cache_Type_ALLD,
                    TRUE);
            }
        }
        else if(TIDL_BatchNormLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_BatchNormParams_t *bNPrms = \
                                &net->TIDLLayers[i].layerParams.batchNormParams;
            dataSize = bNPrms->numChannels;
            if(RANDOM_INPUT)
            {
                Chains_createRandPatternS16((Int16 *)bNPrms->weights.ptr,1,dataSize,1,1,1);
                Cache_wb(
                    (UInt8*)bNPrms->weights.ptr,
                    dataSize,
                    Cache_Type_ALLD,
                    TRUE);
            }
            else
            {
                if(net->weightsElementSize == 2)
                {
                    ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)bNPrms->weights.ptr,
                        (dataSize * 2),
                        &readSize);
                        UTILS_assert(readSize == (dataSize * 2));
                    Cache_wb(
                        (UInt8*)bNPrms->weights.ptr,
                        (dataSize * 2),
                        Cache_Type_ALLD,
                        TRUE);
                }
                else
                {
                    ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)bNPrms->weights.ptr,
                        dataSize,
                        &readSize);
                        UTILS_assert(readSize == dataSize);
                    Cache_wb(
                        (UInt8*)bNPrms->weights.ptr,
                        dataSize,
                        Cache_Type_ALLD,
                        TRUE);
                }
            }

            if(RANDOM_INPUT)
            {
                Chains_createRandPatternS16((Int16 *)bNPrms->bias.ptr, 1,dataSize,1,1, 1);
                Cache_wb(
                    (UInt8*)bNPrms->bias.ptr,
                    dataSize,
                    Cache_Type_ALLD,
                    TRUE);
            }
            else
            {
                ChainsCommon_Osal_fileRead(
                    fp,
                    (UInt8*)bNPrms->bias.ptr,
                    (dataSize * 2),
                    &readSize);
                    UTILS_assert(readSize == (dataSize * 2));
                Cache_wb(
                    (UInt8*)bNPrms->bias.ptr,
                    (dataSize * 2),
                    Cache_Type_ALLD,
                    TRUE);
            }

            if(TIDL_PRelU == bNPrms->reluParams.reluType)
            {
                if(RANDOM_INPUT)
                {
                    Chains_createRandPatternS16((Int16 *)bNPrms->reluParams.slope.ptr,1,dataSize,1,1,1);
                    Cache_wb(
                        (UInt8*)bNPrms->reluParams.slope.ptr,
                        dataSize,
                        Cache_Type_ALLD,
                        TRUE);
                }
                else
                {
                    if(net->slopeElementSize == 2)
                    {
                        ChainsCommon_Osal_fileRead(
                            fp,
                            (UInt8*)bNPrms->reluParams.slope.ptr,
                            (dataSize * 2),
                            &readSize);
                            UTILS_assert(readSize == (dataSize * 2));
                        Cache_wb(
                            (UInt8*)bNPrms->reluParams.slope.ptr,
                            (dataSize * 2),
                            Cache_Type_ALLD,
                            TRUE);
                    }
                    else
                    {
                        ChainsCommon_Osal_fileRead(
                            fp,
                            (UInt8*)bNPrms->reluParams.slope.ptr,
                            dataSize,
                            &readSize);
                            UTILS_assert(readSize == dataSize);
                        Cache_wb(
                            (UInt8*)bNPrms->reluParams.slope.ptr,
                            dataSize,
                            Cache_Type_ALLD,
                            TRUE);
                    }
                }
            }
        }
        else if(TIDL_InnerProductLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_InnerProductParams_t *ipPrms = \
                             &net->TIDLLayers[i].layerParams.innerProductParams;
            dataSize = ipPrms->numInNodes * ipPrms->numOutNodes;
            if(RANDOM_INPUT)
            {
                Chains_createRandPatternS16((Int16 *)ipPrms->weights.ptr,1,dataSize,1,1,1);
                Cache_wb(
                    (UInt8*)ipPrms->weights.ptr,
                    dataSize,
                    Cache_Type_ALLD,
                    TRUE);
            }
            else
            {
                /* Read weights based on its size */
                if(net->weightsElementSize == 2)
                {
                    ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)ipPrms->weights.ptr,
                        (dataSize * 2),
                        &readSize);
                        UTILS_assert(readSize == (dataSize * 2));
                    Cache_wb(
                        (UInt8*)ipPrms->weights.ptr,
                        (dataSize * 2),
                        Cache_Type_ALLD,
                        TRUE);
                }
                else
                {
                    ChainsCommon_Osal_fileRead(
                        fp,
                        (UInt8*)ipPrms->weights.ptr,
                        dataSize,
                        &readSize);
                        UTILS_assert(readSize == dataSize);
                    Cache_wb(
                        (UInt8*)ipPrms->weights.ptr,
                        dataSize,
                        Cache_Type_ALLD,
                        TRUE);
                }
            }

            dataSize = ipPrms->numOutNodes;
            if(RANDOM_INPUT)
            {
                Chains_createRandPatternS16((Int16 *)ipPrms->bias.ptr,1,dataSize,1,1,1);
                Cache_wb(
                    (UInt8*)ipPrms->bias.ptr,
                    dataSize,
                    Cache_Type_ALLD,
                    TRUE);
            }
            else
            {
                ChainsCommon_Osal_fileRead(
                    fp,
                    (UInt8*)ipPrms->bias.ptr,
                    (dataSize * 2),
                    &readSize);
                    UTILS_assert(readSize == (dataSize * 2));
                Cache_wb(
                    (UInt8*)ipPrms->bias.ptr,
                    (dataSize * 2),
                    Cache_Type_ALLD,
                    TRUE);
            }
        }
        else if(TIDL_DetectionOutputLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_DetectOutputParams_t *detectPrms = \
                             &net->TIDLLayers[i].layerParams.detectOutParams;
            dataSize = detectPrms->priorBoxSize;
            if(RANDOM_INPUT)
            {
                Chains_createRandPatternS16((Int16 *)detectPrms->priorBox.ptr,1,dataSize*4,1,1,1);
                Cache_wb(
                    (UInt8*)detectPrms->priorBox.ptr,
                    dataSize * 4,
                    Cache_Type_ALLD,
                    TRUE);
            }
            else
            {
                ChainsCommon_Osal_fileRead(
                    fp,
                    (UInt8*)detectPrms->priorBox.ptr,
                    (dataSize * 4),
                    &readSize);
                    UTILS_assert(readSize == (dataSize * 4));
                Cache_wb(
                    (UInt8*)detectPrms->priorBox.ptr,
                    (dataSize * 4),
                    Cache_Type_ALLD,
                    TRUE);
            }
        }
    }

    ChainsCommon_Osal_fileClose(fp);

    /* Cache wb since it is read on EVE and DSP */
    Cache_wb(
        (UInt8*)net,
        sizeof(sTIDL_Network_t),
        Cache_Type_ALLD,
        TRUE);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief   This function Reset the statCollector registers
 *          SYSTEM_COMMON_CMD_RESET_STAT_COLL send to only IPU1_0 core.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *******************************************************************************
*/
Int32 Chains_tidlFreeNetParamsMem(sTIDL_Network_t *net)
{
    Int32 i;

    for(i = 0; i < net->numLayers; i++)
    {
        if((TIDL_ConvolutionLayer == net->TIDLLayers[i].layerType) ||
           (TIDL_Deconv2DLayer == net->TIDLLayers[i].layerType))
        {
            sTIDL_ConvParams_t *conv2dPrms = \
                                            &net->TIDLLayers[i].layerParams.convParams;
            conv2dPrms->weights.bufSize = \
                net->weightsElementSize * (conv2dPrms->kernelW * conv2dPrms->kernelH *
                conv2dPrms->numInChannels * conv2dPrms->numOutChannels)
                /conv2dPrms->numGroups;
            ChainsCommon_Osal_memFree(
                                conv2dPrms->weights.ptr, conv2dPrms->weights.bufSize);

            conv2dPrms->bias.bufSize = net->biasElementSize * conv2dPrms->numOutChannels;
            ChainsCommon_Osal_memFree(
                    conv2dPrms->bias.ptr, conv2dPrms->bias.bufSize);
        }
        else if(TIDL_BiasLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_BiasParams_t *biasPrms = &net->TIDLLayers[i].layerParams.biasParams;
            biasPrms->bias.bufSize = net->biasElementSize * biasPrms->numChannels;
            ChainsCommon_Osal_memFree(
                    biasPrms->bias.ptr, biasPrms->bias.bufSize);
        }
        else if(TIDL_BatchNormLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_BatchNormParams_t *batchNormPrms = \
                &net->TIDLLayers[i].layerParams.batchNormParams;
            batchNormPrms->weights.bufSize = \
                 net->weightsElementSize * batchNormPrms->numChannels;
            ChainsCommon_Osal_memFree(
                    batchNormPrms->weights.ptr, batchNormPrms->weights.bufSize);

            batchNormPrms->bias.bufSize = \
                net->biasElementSize * batchNormPrms->numChannels;
            ChainsCommon_Osal_memFree(
                    batchNormPrms->bias.ptr, batchNormPrms->bias.bufSize);

            batchNormPrms->reluParams.slope.bufSize =
                net->slopeElementSize * batchNormPrms->numChannels;
            if(TIDL_PRelU == batchNormPrms->reluParams.reluType)
            {
                ChainsCommon_Osal_memFree(
                        batchNormPrms->reluParams.slope.ptr,
                        batchNormPrms->reluParams.slope.bufSize);
            }
        }
        else if(TIDL_InnerProductLayer == net->TIDLLayers[i].layerType)
        {
            sTIDL_InnerProductParams_t *ipPrms = \
                                    &net->TIDLLayers[i].layerParams.innerProductParams;
            ipPrms->bias.bufSize =  net->biasElementSize * ipPrms->numOutNodes;
            ChainsCommon_Osal_memFree(
                    ipPrms->bias.ptr, SystemUtils_align(ipPrms->bias.bufSize, 128));


            ipPrms->weights.bufSize = \
                net->weightsElementSize* ipPrms->numInNodes * ipPrms->numOutNodes;
            ChainsCommon_Osal_memFree(
                    ipPrms->weights.ptr,
                    SystemUtils_align((ipPrms->weights.bufSize + 16 * \
                        net->TIDLLayers[i].layerParams.innerProductParams.numInNodes),
                            1024));
        }
    }

    return SYSTEM_LINK_STATUS_SOK;
}

