/*
 * sample_tda2xx_int_reg.c
 *
 * Platform specific interrupt registration and un-registration routines.
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

#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/hal/Hwi.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>

/**
  * EDMA3 TC ISRs which need to be registered with the underlying OS by the user
  * (Not all TC error ISRs need to be registered, register only for the
  * available Transfer Controllers).
  */
void (*ptrEdma3TcIsrHandler[EDMA3_MAX_TC])(uint32_t arg) =
                                                {
                                                &lisrEdma3TC0ErrHandler0,
                                                &lisrEdma3TC1ErrHandler0,
                                                &lisrEdma3TC2ErrHandler0,
                                                &lisrEdma3TC3ErrHandler0,
                                                &lisrEdma3TC4ErrHandler0,
                                                &lisrEdma3TC5ErrHandler0,
                                                &lisrEdma3TC6ErrHandler0,
                                                &lisrEdma3TC7ErrHandler0,
                                                };

extern uint32_t ccXferCompInt[EDMA3_MAX_EDMA3_INSTANCES][EDMA3_MAX_REGIONS];
extern uint32_t ccErrorInt[EDMA3_MAX_EDMA3_INSTANCES];
extern uint32_t tcErrorInt[EDMA3_MAX_EDMA3_INSTANCES][EDMA3_MAX_TC];
extern uint32_t numEdma3Tc[EDMA3_MAX_EDMA3_INSTANCES];

/**
 * Variables which will be used internally for referring the hardware interrupt
 * for various EDMA3 interrupts.
 */
extern uint32_t hwIntXferComp[EDMA3_MAX_EDMA3_INSTANCES];
extern uint32_t hwIntCcErr[EDMA3_MAX_EDMA3_INSTANCES];
extern uint32_t hwIntTcErr[EDMA3_MAX_EDMA3_INSTANCES];

extern uint32_t dsp_num;
/* This variable has to be used as an extern */
uint32_t gpp_num = 0;

Hwi_Handle hwiCCXferCompInt;
Hwi_Handle hwiCCErrInt;
Hwi_Handle hwiTCErrInt[EDMA3_MAX_TC];

/* External Instance Specific Configuration Structure */
extern EDMA3_DRV_GblXbarToChanConfigParams 
								sampleXbarChanInitConfig[EDMA3_MAX_EDMA3_INSTANCES][EDMA3_MAX_REGIONS];

typedef struct  {
    volatile Uint32 TPCC_EVTMUX[32];
} CSL_IntmuxRegs;

typedef volatile CSL_IntmuxRegs     *CSL_IntmuxRegsOvly;

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK (0x00FF0000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT (0x00000010U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_RESETVAL (0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK (0x000000FFU)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_SHIFT (0x00000000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_RESETVAL (0x00000000U)


#define EDMA3_MAX_CROSS_BAR_EVENTS_TDA2XX (127U)
#define EDMA3_NUM_TCC                     (64U)

#define EDMA3_EVENT_MUX_REG_BASE_ADDR               (0x4a002c78)

/*
 * Forward decleration
 */
EDMA3_DRV_Result sampleMapXbarEvtToChan (uint32_t eventNum,
                 uint32_t *chanNum,
                 const EDMA3_DRV_GblXbarToChanConfigParams * edmaGblXbarConfig);
EDMA3_DRV_Result sampleConfigScr (uint32_t eventNum,
                                  uint32_t chanNum);

void Edma3MemProtectionHandler(uint32_t edma3InstanceId);

/**  To Register the ISRs with the underlying OS, if required. */
void registerEdma3Interrupts (uint32_t edma3Id);

/**  To Unregister the ISRs with the underlying OS, if previously registered. */
void unregisterEdma3Interrupts (uint32_t edma3Id);

EDMA3_DRV_Result sampleInitXbarEvt(EDMA3_DRV_Handle hEdma, 
                                   uint32_t edma3Id);
                                   
void Edma3MemProtectionHandler(uint32_t edma3InstanceId);

/**  To Register the ISRs with the underlying OS, if required. */
void registerEdma3Interrupts (uint32_t edma3Id)
    {
    static UInt32 cookie = 0;
    uint32_t numTc = 0;
    Hwi_Params hwiParams; 
    Error_Block      eb;

    /* Initialize the Error Block                                             */
    Error_init(&eb);
        
    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    /* Initialize the HWI parameters with user specified values */
    Hwi_Params_init(&hwiParams);
    
    /* argument for the ISR */
    hwiParams.arg = edma3Id;
	/* set the priority ID     */
	hwiParams.priority = hwIntXferComp[edma3Id];
    
    hwiCCXferCompInt = Hwi_create((Int) ccXferCompInt[edma3Id][gpp_num],
                			((Hwi_FuncPtr)&lisrEdma3ComplHandler0),
                			(const Hwi_Params *) (&hwiParams),
                			&eb);
    if ((bool)TRUE == Error_check(&eb))
    {
        System_printf("HWI Create Failed\n",Error_getCode(&eb));
    }

    /* Initialize the HWI parameters with user specified values */
    Hwi_Params_init(&hwiParams);
    /* argument for the ISR */
    hwiParams.arg = edma3Id;
	/* set the priority ID     */
	hwiParams.priority = hwIntCcErr[edma3Id];
	
	hwiCCErrInt = Hwi_create((Int) ccErrorInt[edma3Id],
                ((Hwi_FuncPtr)&lisrEdma3CCErrHandler0),
                (const Hwi_Params *) (&hwiParams),
                &eb);

    if ((bool)TRUE == Error_check(&eb))
    {
        System_printf("HWI Create Failed\n",Error_getCode(&eb));
    }

    while (numTc < numEdma3Tc[edma3Id])
	    {
        /* Initialize the HWI parameters with user specified values */
        Hwi_Params_init(&hwiParams);
        /* argument for the ISR */
        hwiParams.arg = edma3Id;
    	/* set the priority ID     */
        hwiParams.priority = hwIntTcErr[edma3Id];
        
        hwiTCErrInt[numTc] = Hwi_create((Int) tcErrorInt[edma3Id][numTc],
                    ((Hwi_FuncPtr)ptrEdma3TcIsrHandler[numTc]),
                    (const Hwi_Params *) (&hwiParams),
                    &eb);
        if ((bool)TRUE == Error_check(&eb))
        {
            System_printf("HWI Create Failed\n",Error_getCode(&eb));
        }
        numTc++;
    	}
   /**
    * Enabling the HWI_ID.
    * EDMA3 interrupts (transfer completion, CC error etc.)
    * correspond to different ECM events (SoC specific). These ECM events come
    * under ECM block XXX (handling those specific ECM events). Normally, block
    * 0 handles events 4-31 (events 0-3 are reserved), block 1 handles events
    * 32-63 and so on. This ECM block XXX (or interrupt selection number XXX)
    * is mapped to a specific HWI_INT YYY in the tcf file. So to enable this
    * mapped HWI_INT YYY, one should use the corresponding bitmask in the
    * API C64_enableIER(), in which the YYY bit is SET.
    */
    Hwi_enableInterrupt(ccErrorInt[edma3Id]);
#if 0
    Hwi_enableInterrupt(13);
#endif
    Hwi_enableInterrupt(ccXferCompInt[edma3Id][gpp_num]);
    numTc = 0;
    while (numTc < numEdma3Tc[edma3Id])
	    {
        Hwi_enableInterrupt(tcErrorInt[edma3Id][numTc]);
        numTc++;
    	}

    /* Restore interrupts */
    Hwi_restore(cookie);
    }

/**  To Unregister the ISRs with the underlying OS, if previously registered. */
void unregisterEdma3Interrupts (uint32_t edma3Id)
    {
	static UInt32 cookiee = 0;
    uint32_t numTc = 0;

    /* Disabling the global interrupts */
    cookiee = Hwi_disable();

    Hwi_delete(&hwiCCXferCompInt);
    Hwi_delete(&hwiCCErrInt);
    while (numTc < numEdma3Tc[edma3Id])
	    {
        Hwi_delete(&hwiTCErrInt[numTc]);
        numTc++;
    	}
    /* Restore interrupts */
    Hwi_restore(cookiee);
    }

/**
 * \brief   sampleMapXbarEvtToChan
 *
 * This function reads from the sample configuration structure which specifies 
 * cross bar events mapped to DMA channel.
 *
 * \return  EDMA3_DRV_SOK if success, else error code
 */
EDMA3_DRV_Result sampleMapXbarEvtToChan (uint32_t eventNum,
                 uint32_t *chanNum,
                 const EDMA3_DRV_GblXbarToChanConfigParams * edmaGblXbarConfig)
	{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_E_INVALID_PARAM;
    uint32_t xbarEvtNum = 0;
    int32_t          edmaChanNum = 0;

	if ((eventNum < EDMA3_MAX_CROSS_BAR_EVENTS_TDA2XX) &&
		(chanNum != NULL) &&
		(edmaGblXbarConfig != NULL))
		{
		xbarEvtNum = eventNum - EDMA3_NUM_TCC;
		edmaChanNum = edmaGblXbarConfig->dmaMapXbarToChan[xbarEvtNum];
		if (edmaChanNum != -((int32_t)1))
			{
			*chanNum = (uint32_t) edmaChanNum;
			edma3Result = EDMA3_DRV_SOK;
			}
		}
	return (edma3Result);
	}


/**
 * \brief   sampleConfigScr
 *
 * This function configures control config registers for the cross bar events 
 * mapped to the EDMA channel.
 *
 * \return  EDMA3_DRV_SOK if success, else error code
 */
EDMA3_DRV_Result sampleConfigScr (uint32_t eventNum,
                                  uint32_t chanNum)
	{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    uint32_t scrChanOffset = 0;
    uint32_t scrRegOffset  = 0;
    uint32_t xBarEvtNum    = 0;
    CSL_IntmuxRegsOvly scrEvtMux = (CSL_IntmuxRegsOvly)(EDMA3_EVENT_MUX_REG_BASE_ADDR);


	if ((eventNum < EDMA3_MAX_CROSS_BAR_EVENTS_TDA2XX) &&
		(chanNum < EDMA3_NUM_TCC))
		{
		scrRegOffset = chanNum / 2U;
		scrChanOffset = chanNum - (scrRegOffset * 2U);
		xBarEvtNum = eventNum + 1U;
		
		switch(scrChanOffset)
			{
			case 0:
				scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
					(xBarEvtNum & CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
				break;
			case 1U:
				scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
					((xBarEvtNum << CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT) & 
					(CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK));
				break;
			default:
				edma3Result = EDMA3_DRV_E_INVALID_PARAM;
				break;
			}
		}
	else
		{
		edma3Result = EDMA3_DRV_E_INVALID_PARAM;
		}
	return edma3Result;
	}

EDMA3_DRV_Result sampleInitXbarEvt(EDMA3_DRV_Handle hEdma, 
                                   uint32_t edma3Id)
    {
    EDMA3_DRV_Result retVal = EDMA3_DRV_SOK;
    const EDMA3_DRV_GblXbarToChanConfigParams *sampleXbarToChanConfig =
                                &(sampleXbarChanInitConfig[edma3Id][dsp_num]);
    uint32_t sampleMapXbarEvtToChanTemp = (uint32_t)&sampleMapXbarEvtToChan;
    uint32_t sampleConfigScrTemp = (uint32_t)&sampleConfigScr;
        if (hEdma != NULL)
        {
        retVal = EDMA3_DRV_initXbarEventMap(hEdma, 
                							sampleXbarToChanConfig, 
                							(EDMA3_DRV_mapXbarEvtToChan)sampleMapXbarEvtToChanTemp, 
                							(EDMA3_DRV_xbarConfigScr)sampleConfigScrTemp);
        }
    
    return retVal;
    }

void Edma3MemProtectionHandler(uint32_t edma3InstanceId)
    {
#ifdef EDMA3_RM_DEBUG
    /*  Added to fix Misra C error */
    printf("memory Protection error");
#endif
    }
