/*
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
*/

/**
 *******************************************************************************
 *
 * \file utils_dma_edma3cc.c
 *
 * \brief This file has the implementation EDMA LLD init/deinit routines and any
 *        other routines needed internally by the EDMA LLD driver
 *
 * \version 0.0 (Aug 2013) : [KC] First version
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/src/dma_cfg/utils_dma_edma3cc.h>

#if defined (BUILD_DSP_1) && defined (OPENCL_SUPPORT)
#include <ti/sdo/fc/edma3/edma3_config.h>
#endif



/**
 *******************************************************************************
 * \brief Global holding all information related to EDMA controller on this CPU
 *******************************************************************************
 */
Utils_DmaObj gUtils_dmaObj[UTILS_DMA_MAX_EDMA_INST];


EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *errorCode)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_E_INST_ALREADY_EXISTS;
    EDMA3_DRV_Handle hEdma = NULL;

    hEdma = Utils_dmaGetEdma3Hndl(UTILS_DMA_SYSTEM_EDMA_INST_ID);

    if(hEdma)
    {
        edma3Result = EDMA3_DRV_SOK;
    }

    *errorCode = edma3Result;
    return hEdma;
}

UInt32 determineProcId(void)
{
    return System_getSelfProcId();
}

EDMA3_DRV_Result edma3deinit (UInt32 edma3Id, EDMA3_DRV_Handle hEdma)
{
    return EDMA3_DRV_SOK;
}
/**
 *******************************************************************************
 *
 * \brief EDMA3 Controller Initialization
 *
 *        This function initializes the EDMA3 Driver for the given EDMA3
 *        controller and opens a EDMA3 driver instance.
 *        It internally calls EDMA3_DRV_create() and EDMA3_DRV_open(),
 *        in that order.
 *
 *        It also registers interrupt handlers for various EDMA3 interrupts like
 *        transfer completion or error interrupts.
 *
 *  \param edma3Id   [IN]   EDMA3 Controller Instance Id (Hardware
 *                          instance id, starting from 0)
 *
 *  \return  EDMA3_DRV_SOK if success, else error code
 *
 *******************************************************************************
 */
EDMA3_DRV_Result Utils_edma3Init(UInt32 edma3Id)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_E_INVALID_PARAM;

    EDMA3_DRV_InitConfig initCfg;
    EDMA3_RM_MiscParam miscParam;
    Utils_DmaObj *pObj;

    if (edma3Id < UTILS_DMA_MAX_EDMA_INST)
    {
        pObj = &gUtils_dmaObj[edma3Id];

        memset( pObj, 0, sizeof(Utils_DmaObj) );

        pObj->edma3InstanceId = edma3Id;

        /* Make the semaphore handle as NULL. */
        pObj->semHandle       = NULL;

        pObj->regionId        = Utils_edma3GetRegionId(pObj->edma3InstanceId);
        pObj->pGblCfgParams   = Utils_edma3GetGblCfg  (pObj->edma3InstanceId);
        pObj->pInstInitConfig = Utils_edma3GetInstCfg (pObj->edma3InstanceId);
        pObj->pIntrConfig     = Utils_edma3GetIntrCfg (pObj->edma3InstanceId);

        UTILS_assert(pObj->pGblCfgParams!=NULL);
        UTILS_assert(pObj->pInstInitConfig!=NULL);

        /* Configure it as master, if required */
        miscParam.isSlave = (UInt32) Utils_edma3IsGblConfigRequired(pObj->regionId);

        edma3Result = EDMA3_DRV_create (
                            pObj->edma3InstanceId,
                            pObj->pGblCfgParams ,
                            (void *)&miscParam
                        );

        if (edma3Result == EDMA3_DRV_SOK)
        {
            /*
             * Driver Object created successfully.
             * Create a semaphore now for driver instance.
             */

            initCfg.drvSemHandle = NULL;
            edma3Result = Utils_edma3OsSemCreate(1,
                                                 &initCfg.drvSemHandle);
        }

        if (edma3Result == EDMA3_DRV_SOK)
        {
            /* Save the semaphore handle for future use */
            pObj->semHandle = initCfg.drvSemHandle;

            initCfg.isMaster = TRUE;

            /* Choose shadow region according to the DSP# */
            initCfg.regionId = (EDMA3_RM_RegionId)pObj->regionId;

            /* Driver instance specific config NULL */
            initCfg.drvInstInitConfig = pObj->pInstInitConfig;
            initCfg.gblerrCb          = NULL;
            initCfg.gblerrData        = NULL;

            /* Open the Driver Instance */
            pObj->hEdma = EDMA3_DRV_open (
                            pObj->edma3InstanceId,
                            (void *) &initCfg,
                            &edma3Result
                        );
        }

        if((NULL != pObj->hEdma) &&
           (EDMA3_DRV_SOK == edma3Result) &&
           (NULL != pObj->pIntrConfig))
        {
            /**
            * Register Interrupt Handlers for various interrupts
            * like transfer completion interrupt, CC error
            * interrupt, TC error interrupts etc, if required.
            */
            Utils_edma3RegisterInterrupts(pObj);
        }
    }
    return edma3Result;
}


/**
 *******************************************************************************
 *
 * \brief EDMA3 De-initialization
 *
 *        This function de-initializes the EDMA3 Driver for the given EDMA3
 *        controller and closes the previously opened EDMA3 driver instance.
 *        It internally calls EDMA3_DRV_close and EDMA3_DRV_delete(),
 *        in that order.
 *
 *        It also un-registers the previously registered interrupt handlers
 *        for various EDMA3 interrupts.
 *
 *  \param edma3Id   [IN]   EDMA3 Controller Instance Id (Hardware
 *                          instance id, starting from 0)
 *
 *  \return  EDMA3_DRV_SOK if success, else error code
 *
 *******************************************************************************
 */
EDMA3_DRV_Result Utils_edma3DeInit (UInt32 edma3Id)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_E_INVALID_PARAM;
    Utils_DmaObj *pObj;

    if (edma3Id < UTILS_DMA_MAX_EDMA_INST)
    {
        pObj = &gUtils_dmaObj[edma3Id];

        if(pObj->pIntrConfig)
        {
            /* Unregister Interrupt Handlers first */
            Utils_edma3UnRegisterInterrupts(pObj);
        }

        /* Delete the semaphore */
        edma3Result = Utils_edma3OsSemDelete(pObj->semHandle);

        if (EDMA3_DRV_SOK == edma3Result )
        {
            /* Make the semaphore handle as NULL. */
            pObj->semHandle = NULL;

            /* Now, close the EDMA3 Driver Instance */
            edma3Result = EDMA3_DRV_close (pObj->hEdma, NULL);
        }

        if (EDMA3_DRV_SOK == edma3Result )
        {
            /* Now, delete the EDMA3 Driver Object */
            edma3Result = EDMA3_DRV_delete (pObj->edma3InstanceId, NULL);
        }
    }

    return edma3Result;
}

/**
 *******************************************************************************
 *
 * \brief Check if interrupt mode is supported in this EDMA instance ID
 *
 * \param edmaInstId          [IN] EDMA instance
 *
 * \return TRUE, interrupt mode supported, FALSE not supported
 *
 *******************************************************************************
 */
Bool Utils_dmaIsIntrSupported(UInt32 edmaInstId)
{
    Bool rtnVal = (Bool)FALSE;

    if ((edmaInstId < UTILS_DMA_MAX_EDMA_INST))
    {
        if(gUtils_dmaObj[edmaInstId].pIntrConfig)
        {
            rtnVal = (Bool)TRUE;
        }
        else
        {
            rtnVal = (Bool)FALSE;
        }
    }

    return rtnVal;
}

/**
 *******************************************************************************
 *
 * \brief Get handle to EDMA3 LLD driver
 *
 *        This is useful when user wants to directly call EDMA APIs for
 *        doing EDMA transfer's
 *
 * \param edmaInstId          [IN] EDMA instance for which the handle is
 *                                 required
 *
 * \return SYSTEM_LINK_STATUS_SOK on success, else failure
 *
 *******************************************************************************
 */
EDMA3_DRV_Handle Utils_dmaGetEdma3Hndl(UInt32 edmaInstId)
{
    EDMA3_DRV_Handle hndle = NULL;

    if (edmaInstId < UTILS_DMA_MAX_EDMA_INST)
    {
        hndle = gUtils_dmaObj[edmaInstId].hEdma;
    }

    return hndle;
}

/**
 *******************************************************************************
 *
 * \brief Utility APIs to create semaphore required by EDMA3 LLD driver
 *
 *  \param initVal    [IN]  Initial value of the semaphore
 *  \param semParams  [IN]  Semaphore parameters
 *  \param hSem       [OUT] Handle to the semaphore object
 *
 *  \return  EDMA3_DRV_SOK if success, else error code
 *
 *******************************************************************************
 */
EDMA3_DRV_Result Utils_edma3OsSemCreate(Int32 initVal,
                            EDMA3_OS_Sem_Handle *hSem)
{
    EDMA3_DRV_Result semCreateResult = EDMA3_DRV_SOK;

    if(NULL == hSem)
    {
        semCreateResult = EDMA3_DRV_E_INVALID_PARAM;
    }
    else
    {
#if defined (BUILD_DSP_1) && defined (OPENCL_SUPPORT)
        *hSem = (EDMA3_OS_Sem_Handle)EDMA3_semCreate(initVal, (Int32)TRUE);
#else
        *hSem = (EDMA3_OS_Sem_Handle)BspOsal_semCreate(initVal, (Bool)TRUE);
#endif
        if ( (*hSem) == NULL )
        {
            semCreateResult = EDMA3_DRV_E_SEMAPHORE;
        }
    }

    return semCreateResult;
}

/**
 *******************************************************************************
 *
 * \brief Utility APIs to delete semaphore required by EDMA3 LLD driver
 *
 *  \param hSem       [IN] Handle to the semaphore object
 *
 *  \return  EDMA3_DRV_SOK if success, else error code
 *
 *******************************************************************************
 */
EDMA3_Result Utils_edma3OsSemDelete(EDMA3_OS_Sem_Handle hSem)
{
    EDMA3_Result semDeleteResult = EDMA3_DRV_SOK;

    if(NULL == hSem)
    {
        semDeleteResult = EDMA3_DRV_E_INVALID_PARAM;
    }
    else
    {
#if defined (BUILD_DSP_1) && defined (OPENCL_SUPPORT)
        EDMA3_semDelete((EDMA3_OS_Sem_Handle *)&hSem);
#else
        BspOsal_semDelete((BspOsal_SemHandle *)&hSem);
#endif
    }

    return semDeleteResult;
}

/**
 *******************************************************************************
 *
 * \brief Utility APIs to take a semaphore
 *
 *        Called by EDMA LLD driver internally
 *
 * \param hSem          [IN] Handle to the semaphore object
 * \param mSecTimeout   [IN] Timeout in units of msecs
 *
 * \return  EDMA3_DRV_SOK if success, else error code
 *
 *******************************************************************************
 */
#if defined (BUILD_DSP_1) && defined (OPENCL_SUPPORT)
#else
EDMA3_Result edma3OsSemTake(EDMA3_OS_Sem_Handle hSem, int32_t mSecTimeout)
{
    EDMA3_Result semTakeResult = EDMA3_DRV_SOK;
    Bool semPendResult;

    if(NULL == hSem)
    {
        semTakeResult = EDMA3_DRV_E_INVALID_PARAM;
    }
    else
    {
        semPendResult = BspOsal_semWait(hSem, (UInt32)mSecTimeout);
        if (semPendResult == (Bool)FALSE)
        {
            semTakeResult = EDMA3_DRV_E_SEMAPHORE;
        }
    }

    return semTakeResult;
}

/**
 *******************************************************************************
 *
 * \brief Utility APIs to release a semaphore
 *
 *        Called by EDMA LLD driver internally
 *
 * \param hSem          [IN] Handle to the semaphore object
 *
 * \return  EDMA3_DRV_SOK if success, else error code
 *
 *******************************************************************************
 */
EDMA3_Result edma3OsSemGive(EDMA3_OS_Sem_Handle hSem)
{
    EDMA3_Result semGiveResult = EDMA3_DRV_SOK;

    if(NULL == hSem)
    {
        semGiveResult = EDMA3_DRV_E_INVALID_PARAM;
    }
    else
    {
        BspOsal_semPost(hSem);
    }

    return semGiveResult;
}

/**
 *******************************************************************************
 *
 * \brief Protect entry by disabling interrupts
 *
 *        Called by EDMA LLD driver internally
 *
 *        In this implementation always global interrupts are disabled
 *        for simplicity sake
 *
 * \param edma3InstanceId   [IN] EDMA instance
 * \param level             [IN] level of protection required
 * \param intState          [OUT] Old interrupt state
 *
 *******************************************************************************
 */
void edma3OsProtectEntry (uint32_t edma3InstanceId,
                            int32_t level, uint32_t *intState)
{
    if (!(
         ((level == EDMA3_OS_PROTECT_INTERRUPT) ||
         (level == EDMA3_OS_PROTECT_INTERRUPT_TC_ERROR))
        && (intState == NULL)
        ))
    {
        switch (level)
        {
            /* Disable all (global) interrupts */
            case EDMA3_OS_PROTECT_INTERRUPT :
                *intState = Hwi_disable();
                break;

            /* Disable scheduler */
            case EDMA3_OS_PROTECT_SCHEDULER :
                Task_disable();
                break;

            default:
                break;
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief Protect exit by restoring interrupt state
 *
 *        Called by EDMA LLD driver internally
 *
 *        In this implementation always global interrupts are restored
 *        for simplicity sake
 *
 * \param edma3InstanceId   [IN] EDMA instance
 * \param level             [IN] level of protection required
 * \param intState          [IN] Previous interrupt state
 *
 *******************************************************************************
 */
void edma3OsProtectExit(uint32_t edma3InstanceId,
                            int32_t level, uint32_t intState)
{
    switch (level)
    {
        /* Enable all (global) interrupts */
        case EDMA3_OS_PROTECT_INTERRUPT :
            Hwi_restore(intState);
            break;
        /* Enable scheduler */
        case EDMA3_OS_PROTECT_SCHEDULER :
            Task_enable();
            break;
        default:
            break;
    }
}

#endif
