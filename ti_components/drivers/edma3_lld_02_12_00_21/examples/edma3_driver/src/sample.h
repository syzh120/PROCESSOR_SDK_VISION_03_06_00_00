/*
* bios6_edma3_drv_sample.h
*
* Header file for the Demo application for the EDMA3 Driver.
*
* Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
*
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
*
*/

#ifndef _SAMPLE_H_
#define _SAMPLE_H_

#include <stdio.h>
#include <xdc/std.h>
#include <ti/sysbios/knl/Task.h>

/* Include EDMA3 Driver */
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>

#ifdef __cplusplus
extern "C" {
#endif

    /* MAX ACOUNT */
#define MAX_ACOUNT                  (64u)
    /* MAX BCOUNT */
#define MAX_BCOUNT                  (1u)
    /* MAX CCOUNT */
#define MAX_CCOUNT                  (1u)
    /**
    * Buffers (src and dest) are needed for mem-2-mem data transfers.
    * This define is for the MAXIMUM size and hence the maximum data
    * which could be transferred using the sample test cases below.
    */
#define MAX_BUFFER_SIZE             (MAX_ACOUNT * MAX_BCOUNT * MAX_CCOUNT)

#ifndef BUILD_TDA2XX_MPU
    /* To enable/disable the cache .*/
#define EDMA3_ENABLE_DCACHE                 (1u)
#endif

    /* OPT Field specific defines */
#define OPT_SYNCDIM_SHIFT                   (0x00000002u)
#define OPT_TCC_MASK                        (0x0003F000u)
#define OPT_TCC_SHIFT                       (0x0000000Cu)
#define OPT_ITCINTEN_SHIFT                  (0x00000015u)
#define OPT_TCINTEN_SHIFT                   (0x00000014u)

    extern void callback1 (uint32_t tcc, EDMA3_RM_TccStatus status,
        void *appData);

    extern void callback2 (uint32_t tcc, EDMA3_RM_TccStatus status,
        void *appData);

    extern signed char*  getGlobalAddr(signed char* addr);
    /* Flag variable to check transfer completion on channel 1 */
    extern volatile short irqRaised1;
    /* Flag variable to check transfer completion on channel 2 */
    extern volatile short irqRaised2;

#define MAX_NUM_EDMA_INSTANCES  5

    /* Define to verify the default RM config.
    * Additional configuration required. Update the 
    * gblCfgReqdArray[] to reflect the master/slave config.
    * In the case of multiple instances default configuration
    * may require more than one cores other than core 0 to be master. 
    * #define EDMA3_DRV_USE_DEF_RM_CFG 
    */

#define GLOBAL_ADDR(addr) (getGlobalAddr(addr))

    /**
    *  \brief   EDMA3 mem-to-mem data copy test case, using a DMA channel.
    *
    *
    *  \param  acnt        [IN]      Number of bytes in an array
    *  \param  bcnt        [IN]      Number of arrays in a frame
    *  \param  ccnt        [IN]      Number of frames in a block
    *  \param  syncType    [IN]      Synchronization type (A/AB Sync)
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result edma3_test(
        EDMA3_DRV_Handle hEdma,
        uint32_t acnt,
        uint32_t bcnt,
        uint32_t ccnt,
        EDMA3_DRV_SyncType syncType);



    /**
    *  \brief   EDMA3 mem-to-mem data copy test case, using two DMA
    *              channels, linked to each other.
    *
    *  \param  acnt        [IN]      Number of bytes in an array
    *  \param  bcnt        [IN]      Number of arrays in a frame
    *  \param  ccnt        [IN]      Number of frames in a block
    *  \param  syncType    [IN]      Synchronization type (A/AB Sync)
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result edma3_test_with_link(
        EDMA3_DRV_Handle hEdma,
        uint32_t acnt,
        uint32_t bcnt,
        uint32_t ccnt,
        EDMA3_DRV_SyncType syncType);



    /**
    *  \brief   EDMA3 mem-to-mem data copy test case, using a QDMA channel.
    *
    *
    *  \param  acnt        [IN]      Number of bytes in an array
    *  \param  bcnt        [IN]      Number of arrays in a frame
    *  \param  ccnt        [IN]      Number of frames in a block
    *  \param  syncType    [IN]      Synchronization type (A/AB Sync)
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result qdma_test(
        EDMA3_DRV_Handle hEdma,
        uint32_t acnt,
        uint32_t bcnt,
        uint32_t ccnt,
        EDMA3_DRV_SyncType syncType);



    /**
    *  \brief   EDMA3 misc test cases.
    *              This test case will read/write to some CC registers.
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result edma3_misc_test(EDMA3_DRV_Handle hEdma);


    /**
    *  \brief   EDMA3 mem-to-mem data copy test case, using a QDMA channel,
    *              linked to another LINK channel.
    *
    *  \param  acnt        [IN]      Number of bytes in an array
    *  \param  bcnt        [IN]      Number of arrays in a frame
    *  \param  ccnt        [IN]      Number of frames in a block
    *  \param  syncType    [IN]      Synchronization type (A/AB Sync)
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result qdma_test_with_link(
        EDMA3_DRV_Handle hEdma,
        uint32_t acnt,
        uint32_t bcnt,
        uint32_t ccnt,
        EDMA3_DRV_SyncType syncType);


    /**
    *  \brief   EDMA3 mem-to-mem data copy test case, using two DMA channels,
    *              chained to each other.
    *
    *  \param  acnt        [IN]      Number of bytes in an array
    *  \param  bcnt        [IN]      Number of arrays in a frame
    *  \param  ccnt        [IN]      Number of frames in a block
    *  \param  syncType    [IN]      Synchronization type (A/AB Sync)
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result edma3_test_with_chaining(
        EDMA3_DRV_Handle hEdma,
        uint32_t acnt,
        uint32_t bcnt,
        uint32_t ccnt,
        EDMA3_DRV_SyncType syncType);


    /**
    *  \brief   EDMA3 mem-to-mem data copy test case, using a DMA channel.
    *              This test case doesnot rely on the callback mechanism.
    *              Instead, it Polls the IPR register to check the transfer
    *              completion status.
    *
    *  \param  acnt        [IN]      Number of bytes in an array
    *  \param  bcnt        [IN]      Number of arrays in a frame
    *  \param  ccnt        [IN]      Number of frames in a block
    *  \param  syncType    [IN]      Synchronization type (A/AB Sync)
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result edma3_test_poll_mode(
        EDMA3_DRV_Handle hEdma,
        uint32_t acnt,
        uint32_t bcnt,
        uint32_t ccnt,
        EDMA3_DRV_SyncType syncType);

    /**
    *  \brief   EDMA3 mem-to-mem data copy test case with user requested paRAMId
    *           using a DMA channel.
    *           This test case doesnot rely on the callback mechanism.
    *           Instead, it Polls the IPR register to check the transfer
    *           completion status.
    *
    *  \param  edmaInstance [IN]    EDMA3 Instance number
    *  \param  acnt        [IN]      Number of bytes in an array
    *  \param  bcnt        [IN]      Number of arrays in a frame
    *  \param  ccnt        [IN]      Number of frames in a block
    *  \param  syncType    [IN]      Synchronization type (A/AB Sync)
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result edma3_test_user_req_paRAMId(
        EDMA3_DRV_Handle hEdma,
        uint32_t edmaInstance,
        uint32_t acnt,
        uint32_t bcnt,
        uint32_t ccnt,
        EDMA3_DRV_SyncType syncType);

    /**
    *  \brief   EDMA3 ping-pong based data copy test case, using a DMA and
    *              a link channel.
    *
    *  \return  EDMA3_DRV_SOK or EDMA3_DRV Error Code
    */
    EDMA3_DRV_Result edma3_test_ping_pong_mode(EDMA3_DRV_Handle hEdma);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  /* _SAMPLE_H_ */
