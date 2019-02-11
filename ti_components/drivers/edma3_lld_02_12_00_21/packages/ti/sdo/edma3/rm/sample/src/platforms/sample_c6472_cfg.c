/*
 * sample_c6472_cfg.c
 *
 * Platform specific EDMA3 hardware related information like number of transfer
 * controllers, various interrupt ids etc. It is used while interrupts
 * enabling / disabling. It needs to be ported for different SoCs.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
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

#include <ti/sdo/edma3/rm/edma3_rm.h>

/* Number of EDMA3 controllers present in the system */
#define NUM_EDMA3_INSTANCES			1u
const unsigned int numEdma3Instances = NUM_EDMA3_INSTANCES;

/* Number of DSPs present in the system */
#define NUM_DSPS					6u

extern cregister volatile unsigned int DNUM;

#define MAP_LOCAL_TO_GLOBAL_ADDR(addr) ((1<<28)|(DNUM<<24)|(((unsigned int)addr)&0x00ffffff))
/* Determine the processor id by reading DNUM register. */
unsigned short determineProcId()
	{
    /* Identify the core number */
	return (unsigned short)DNUM;
	}

signed char*  getGlobalAddr(signed char* addr)
{
    if (((unsigned int)addr & (unsigned int)0xFF000000) != 0)
    {
        return (addr); /* The address is already a global address */
    }

    return((signed char*)(MAP_LOCAL_TO_GLOBAL_ADDR(addr)));
}


/** Whether global configuration required for EDMA3 or not.
 * This configuration should be done only once for the EDMA3 hardware by
 * any one of the masters (i.e. DSPs).
 * It can be changed depending on the use-case.
 */
unsigned int gblCfgReqdArray [NUM_DSPS] = {
									0,	/* DSP#0 is Master, will do the global init */
									1,	/* DSP#1 is Slave, will not do the global init  */
									1,	/* DSP#2 is Slave, will not do the global init  */
									1,	/* DSP#3 is Slave, will not do the global init  */
									1,	/* DSP#4 is Slave, will not do the global init  */
									1,	/* DSP#5 is Slave, will not do the global init  */
									};

unsigned short isGblConfigRequired(unsigned int dspNum)
	{
	return gblCfgReqdArray[dspNum];
	}

/**
* EDMA3 interrupts (transfer completion, CC error etc.) correspond to different
* ECM events (SoC specific). These ECM events come
* under ECM block XXX (handling those specific ECM events). Normally, block
* 0 handles events 4-31 (events 0-3 are reserved), block 1 handles events
* 32-63 and so on. This ECM block XXX (or interrupt selection number XXX)
* is mapped to a specific HWI_INT YYY in the tcf file.
* For TCI6488, following mappings has been done:
* ECM Block 0 (Events 04-31) --> HWI Interrupt 7
* ECM Block 1 (Events 32-63) --> HWI Interrupt 8
* ECM Block 2 (Events 64-95) --> HWI Interrupt 9
* ECM Block 3 (Events 96-127) --> HWI Interrupt 10
* These defines below specify which ECM event is mapped to which HWI interrupt.
* Define EDMA3_HWI_INT_XFER_COMP[n] to specific HWI_INT, corresponding
* to transfer completion interrupt, on that particular DSP core.
* Define EDMA3_HWI_INT_CC_ERR to specific HWI_INT, corresponding
* to CC error interrupts.
* Define EDMA3_HWI_INT_TC_ERR to specific HWI_INT, corresponding
* to TC error interrupts.
*/
/* Transfer completion interrupt for DSP 0 lies in ECM block 0. */
#define EDMA3_HWI_INT_XFER_COMP_0						(7u)
/* Transfer completion interrupt for DSP 1 lies in ECM block 0. */
#define EDMA3_HWI_INT_XFER_COMP_1						(7u)
/* Transfer completion interrupt for DSP 2 lies in ECM block 0. */
#define EDMA3_HWI_INT_XFER_COMP_2						(7u)
/* Transfer completion interrupt for DSP 3 lies in ECM block 0. */
#define EDMA3_HWI_INT_XFER_COMP_3						(7u)
/* Transfer completion interrupt for DSP 4 lies in ECM block 0. */
#define EDMA3_HWI_INT_XFER_COMP_4						(7u)
/* Transfer completion interrupt for DSP 5 lies in ECM block 0. */
#define EDMA3_HWI_INT_XFER_COMP_5						(7u)

/** CC Error Interrupt lies in ECM block 1.                     */
#define EDMA3_HWI_INT_CC_ERR							(8u)

/* TC0 Error interrupt in ECM block 1.                          */
#define EDMA3_HWI_INT_TC_ERR_0							(8u)
/* TC1 Error interrupt in ECM block 1.                          */
#define EDMA3_HWI_INT_TC_ERR_1							(8u)
/* TC0 Error interrupt in ECM block 1.                          */
#define EDMA3_HWI_INT_TC_ERR_2							(8u)
/* TC1 Error interrupt in ECM block 1.                          */
#define EDMA3_HWI_INT_TC_ERR_3							(8u)

/* Semaphore handles */
EDMA3_OS_Sem_Handle SemHandle[NUM_EDMA3_INSTANCES] = {NULL};


/* Variable which will be used internally for referring number of Event Queues. */
unsigned int numEdma3EvtQue[NUM_EDMA3_INSTANCES] = {4u};

/* Variable which will be used internally for referring number of TCs. */
unsigned int numEdma3Tc[NUM_EDMA3_INSTANCES] = {4u};

/**
 * Variable which will be used internally for referring transfer completion
 * interrupt. Completion interrupts for all the shadow regions and all the
 * EDMA3 controllers are captured since it is a multi-DSP platform.
 */
unsigned int ccXferCompInt[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] = {
													{
													15u, 15u, 15u, 15u,
													15u, 15u, 67u, 68u,
													},
												};

/**
 * Variable which will be used internally for referring channel controller's
 * error interrupt.
 */
unsigned int ccErrorInt[NUM_EDMA3_INSTANCES] = {57u};

/**
 * Variable which will be used internally for referring transfer controllers'
 * error interrupts.
 */
unsigned int tcErrorInt[NUM_EDMA3_INSTANCES][EDMA3_MAX_TC] =    {
													{
													59u, 60u, 61u, 62u,
													0u, 0u, 0u, 0u,
													},
												};

/**
 * Variables which will be used internally for referring the hardware interrupt
 * for various EDMA3 interrupts.
 */
unsigned int hwIntXferComp[NUM_DSPS] = {
								EDMA3_HWI_INT_XFER_COMP_0,
								EDMA3_HWI_INT_XFER_COMP_1,
								EDMA3_HWI_INT_XFER_COMP_2,
								EDMA3_HWI_INT_XFER_COMP_3,
								EDMA3_HWI_INT_XFER_COMP_4,
								EDMA3_HWI_INT_XFER_COMP_5
								};
unsigned int hwIntCcErr = EDMA3_HWI_INT_CC_ERR;
unsigned int hwIntTcErr[EDMA3_MAX_REGIONS]  = {
								EDMA3_HWI_INT_TC_ERR_0,
								EDMA3_HWI_INT_TC_ERR_1,
								EDMA3_HWI_INT_TC_ERR_2,
								EDMA3_HWI_INT_TC_ERR_3,
								0u,
								0u,
								0u,
								0u
								};

/* Driver Object Initialization Configuration */
EDMA3_RM_GblConfigParams sampleEdma3GblCfgParams[NUM_EDMA3_INSTANCES] =
	{
		{
		/** Total number of DMA Channels supported by the EDMA3 Controller */
		64u,
		/** Total number of QDMA Channels supported by the EDMA3 Controller */
		4u,
		/** Total number of TCCs supported by the EDMA3 Controller */
		64u,
		/** Total number of PaRAM Sets supported by the EDMA3 Controller */
		256u,
		/** Total number of Event Queues in the EDMA3 Controller */
		4u,
		/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
		4u,
		/** Number of Regions on this EDMA3 controller */
		8u,

		/**
		 * \brief Channel mapping existence
		 * A value of 0 (No channel mapping) implies that there is fixed association
		 * for a channel number to a parameter entry number or, in other words,
		 * PaRAM entry n corresponds to channel n.
		 */
		1u,

		/** Existence of memory protection feature */
		1u,

		/** Global Register Region of CC Registers */
		(void *)0x02A00000u,
		/** Transfer Controller (TC) Registers */
		{
		(void *)0x02A20000u,
		(void *)0x02A28000u,
		(void *)0x02A30000u,
		(void *)0x02A38000u,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL
		},
		/** Interrupt no. for Transfer Completion */
		15u,
		/** Interrupt no. for CC Error */
		57u,
		/** Interrupt no. for TCs Error */
		{
		59u,
		60u,
		61u,
		62u,
		0u,
		0u,
		0u,
		0u,
		},

		/**
		 * \brief EDMA3 TC priority setting
		 *
		 * User can program the priority of the Event Queues
		 * at a system-wide level.  This means that the user can set the
		 * priority of an IO initiated by either of the TCs (Transfer Controllers)
		 * relative to IO initiated by the other bus masters on the
		 * device (ARM, DSP, USB, etc)
		 */
		{
		0u,
		1u,
		2u,
		3u,
		0u,
		0u,
		0u,
		0u
		},
		/**
		 * \brief To Configure the Threshold level of number of events
		 * that can be queued up in the Event queues. EDMA3CC error register
		 * (CCERR) will indicate whether or not at any instant of time the
		 * number of events queued up in any of the event queues exceeds
		 * or equals the threshold/watermark value that is set
		 * in the queue watermark threshold register (QWMTHRA).
		 */
		{
		16u,
		16u,
		16u,
		16u,
		0u,
		0u,
		0u,
		0u
		},

		/**
		 * \brief To Configure the Default Burst Size (DBS) of TCs.
		 * An optimally-sized command is defined by the transfer controller
		 * default burst size (DBS). Different TCs can have different
		 * DBS values. It is defined in Bytes.
		 */
		{
		64u,
		64u,
		64u,
		64u,
		0u,
		0u,
		0u,
		0u
		},

		/**
		 * \brief Mapping from each DMA channel to a Parameter RAM set,
		 * if it exists, otherwise of no use.
		 */
		{
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP,
        EDMA3_RM_CH_NO_PARAM_MAP, EDMA3_RM_CH_NO_PARAM_MAP
		},

		 /**
		  * \brief Mapping from each DMA channel to a TCC. This specific
		  * TCC code will be returned when the transfer is completed
		  * on the mapped channel.
		  */
		{
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
        EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
		},

		/**
		 * \brief Mapping of DMA channels to Hardware Events from
		 * various peripherals, which use EDMA for data transfer.
		 * All channels need not be mapped, some can be free also.
		 */
		{
		0x00000000u,
		0x00000000u
		}
		}
	};

EDMA3_RM_InstanceInitConfig sampleInstInitConfig[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
{
	{
	  {
		/* Resources owned by Region 0 */
		 /* ownPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0x00000000u, 0x00000000u, 0xFFFFFFFFu, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* ownDmaChannels */
		/* 31     0     63    32 */
		{0x0000FFFFu, 0x00000000u},

		/* ownQdmaChannels */
		/* 31     0 */
		{0x00000001u},

		/* ownTccs */
		/* 31     0     63    32 */
		{0x0000FFFFu, 0x00000000u},

		/* Resources reserved by Region 0 */
		/* resvdPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* resvdDmaChannels */
        /* 31	  0    63     32 */
        {0x00000000u, 0x00000000u},

		/* resvdQdmaChannels */
		/* 31     0 */
		{0x00000000u},

		/* resvdTccs */
        /* 31	  0    63     32 */
        {0x00000000u, 0x00000000u},
	  },

	  {
		/* Resources owned by Region 1 */
		/* ownPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFFFFu,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* ownDmaChannels */
		/* 31     0     63    32 */
   		{0xFFFF0000u, 0x00000000u},

		/* ownQdmaChannels */
		/* 31     0 */
		{0x00000002u},

		/* ownTccs */
		/* 31     0     63    32 */
   		{0xFFFF0000u, 0x00000000u},

		/* Resources reserved by Region 1 */
		/* resvdPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* resvdDmaChannels */
        /* 31	  0    63     32 */
        {0x00000000u, 0x00000000u},

		/* resvdQdmaChannels */
		/* 31     0 */
		{0x00000000u},

		/* resvdTccs */
        /* 31	  0    63     32 */
        {0x00000000u, 0x00000000u},
	  },

	  {
		/* Resources owned by Region 2 */
		 /* ownPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* ownDmaChannels */
		/* 31     0     63    32 */
		{0x00000000u, 0x000000FFu},

		/* ownQdmaChannels */
		/* 31     0 */
		{0x00000004u},

		/* ownTccs */
		/* 31     0     63    32 */
		{0x00000000u, 0x000000FFu},

		/* Resources reserved by Region 2 */
		/* resvdPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* resvdDmaChannels */
        /* 31	  0    63     32 */
        {0x00000000u, 0x00000000u},

		/* resvdQdmaChannels */
		/* 31     0 */
		{0x00000000u},

		/* resvdTccs */
        /* 31	  0    63     32 */
        {0x00000000u, 0x00000000u},
	  },

	  {
		/* Resources owned by Region 3 */
		 /* ownPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* ownDmaChannels */
		/* 31     0     63    32 */
		{0x00000000u, 0x0000FF00u},

		/* ownQdmaChannels */
		/* 31     0 */
		{0x00000008u},

		/* ownTccs */
		/* 31     0     63    32 */
		{0x00000000u, 0x0000FF00u},

		/* Resources reserved by Region 3 */
		/* resvdPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* resvdDmaChannels */
		/* 31     0     63    32 */
		{0x00000000u, 0x00000000u},

		/* resvdQdmaChannels */
		/* 31     0 */
		{0x00000000u},

		/* resvdTccs */
		/* 31     0     63    32 */
		{0x00000000u, 0x00000000u},
	  },

	  {
		/* Resources owned by Region 4 */
		 /* ownPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0xFFFFFFFFu, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* ownDmaChannels */
		/* 31     0     63    32 */
		{0x00000000u, 0x00FF0000u},

		/* ownQdmaChannels */
		/* 31     0 */
		{0x00000008u},

		/* ownTccs */
		/* 31     0     63    32 */
		{0x00000000u, 0x00FF0000u},

		/* Resources reserved by Region 4 */
		/* resvdPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* resvdDmaChannels */
		/* 31     0     63    32 */
		{0x00000000u, 0x00000000u},

		/* resvdQdmaChannels */
		/* 31     0 */
		{0x00000000u},

		/* resvdTccs */
		/* 31     0     63    32 */
		{0x00000000u, 0x00000000u},
	  },

	  {
		/* Resources owned by Region 5 */
		 /* ownPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0xFFFFFFFFu,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* ownDmaChannels */
		/* 31     0     63    32 */
		{0x00000000u, 0xFF000000u},

		/* ownQdmaChannels */
		/* 31     0 */
		{0x00000008u},

		/* ownTccs */
		/* 31     0     63    32 */
		{0x00000000u, 0xFF000000u},

		/* Resources reserved by Region 5 */
		/* resvdPaRAMSets */
		/* 31     0     63    32     95    64     127   96 */
		{0xFFFFFFFFu, 0xFFFFFFFFu, 0x00000000u, 0x00000000u,
		/* 159  128     191  160     223  192     255  224 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 287  256     319  288     351  320     383  352 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
		/* 415  384     447  416     479  448     511  480 */
		 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

		/* resvdDmaChannels */
		/* 31     0     63    32 */
		{0x00000000u, 0x00000000u},

		/* resvdQdmaChannels */
		/* 31     0 */
		{0x00000000u},

		/* resvdTccs */
		/* 31     0     63    32 */
		{0x00000000u, 0x00000000u},
	  },

      {
        /* Resources owned by Region 6 */
         /* ownPaRAMSets */
        /* 31     0     63    32     95    64     127   96 */
        {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 159  128     191  160     223  192     255  224 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 287  256     319  288     351  320     383  352 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 415  384     447  416     479  448     511  480 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

        /* ownDmaChannels */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},

        /* ownQdmaChannels */
        /* 31     0 */
        {0x00000000u},

        /* ownTccs */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},

        /* Resources reserved by Region 6 */
        /* resvdPaRAMSets */
        /* 31     0     63    32     95    64     127   96 */
        {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 159  128     191  160     223  192     255  224 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 287  256     319  288     351  320     383  352 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 415  384     447  416     479  448     511  480 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

        /* resvdDmaChannels */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},

        /* resvdQdmaChannels */
        /* 31     0 */
        {0x00000000u},

        /* resvdTccs */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},
      },

      {
        /* Resources owned by Region 7 */
         /* ownPaRAMSets */
        /* 31     0     63    32     95    64     127   96 */
        {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 159  128     191  160     223  192     255  224 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 287  256     319  288     351  320     383  352 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 415  384     447  416     479  448     511  480 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

        /* ownDmaChannels */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},

        /* ownQdmaChannels */
        /* 31     0 */
        {0x00000000u},

        /* ownTccs */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},

        /* Resources reserved by Region 7 */
        /* resvdPaRAMSets */
        /* 31     0     63    32     95    64     127   96 */
        {0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 159  128     191  160     223  192     255  224 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 287  256     319  288     351  320     383  352 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
        /* 415  384     447  416     479  448     511  480 */
         0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

        /* resvdDmaChannels */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},

        /* resvdQdmaChannels */
        /* 31     0 */
        {0x00000000u},

        /* resvdTccs */
        /* 31     0     63    32 */
        {0x00000000u, 0x00000000u},
      }
	}
};

/* End of File */
