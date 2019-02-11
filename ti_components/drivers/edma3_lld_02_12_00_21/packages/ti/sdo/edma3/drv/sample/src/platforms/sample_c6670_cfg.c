/*
 * sample_c6670_cfg.c
 *
 * Platform specific EDMA3 hardware related information like number of transfer
 * controllers, various interrupt ids etc. It is used while interrupts
 * enabling / disabling. It needs to be ported for different SoCs.
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

#include <ti/sdo/edma3/rm/edma3_rm.h>

/* Number of EDMA3 controllers present in the system */
#define NUM_EDMA3_INSTANCES			3u
const unsigned int numEdma3Instances = NUM_EDMA3_INSTANCES;

/* Number of DSPs present in the system */
#define NUM_DSPS					4u
//const unsigned int numDsps = NUM_DSPS;

#define CGEM_REG_START                  (0x01800000)


extern cregister volatile unsigned int DNUM;

#define MAP_LOCAL_TO_GLOBAL_ADDR(addr) ((1<<28)|(DNUM<<24)|(((unsigned int)addr)&0x00ffffff))


/* Determine the processor id by reading DNUM register. */
unsigned short determineProcId()
	{
  	volatile unsigned int *addr;
  	unsigned int core_no;

    /* Identify the core number */
    addr = (unsigned int *)(CGEM_REG_START+0x40000);
    core_no = ((*addr) & 0x000F0000)>>16;

	return core_no;
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
									};

unsigned short isGblConfigRequired(unsigned int dspNum)
	{
	return gblCfgReqdArray[dspNum];
	}

/* Semaphore handles */
EDMA3_OS_Sem_Handle semHandle[NUM_EDMA3_INSTANCES] = {NULL,NULL,NULL};


/* Variable which will be used internally for referring number of Event Queues. */
unsigned int numEdma3EvtQue[NUM_EDMA3_INSTANCES] = {2u, 4u, 4u};

/* Variable which will be used internally for referring number of TCs. */
unsigned int numEdma3Tc[NUM_EDMA3_INSTANCES] = {2u, 4u, 4u};

/**
 * Variable which will be used internally for referring transfer completion
 * interrupt. Completion interrupts for all the shadow regions and all the
 * EDMA3 controllers are captured since it is a multi-DSP platform.
 */
unsigned int ccXferCompInt[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] = {
													{
													38u, 39u, 40u, 41u,
													42u, 43u, 44u, 45u,
													},
													{
													8u, 9u, 10u, 11u,
													12u, 13u, 14u, 15u,
													},
													{
													24u, 25u, 26u, 27u,
													28u, 29u, 30u, 31u,
													},
												};

/**
 * Variable which will be used internally for referring channel controller's
 * error interrupt.
 */
unsigned int ccErrorInt[NUM_EDMA3_INSTANCES] = {32u, 0u, 16u};

/**
 * Variable which will be used internally for referring transfer controllers'
 * error interrupts.
 */
unsigned int tcErrorInt[NUM_EDMA3_INSTANCES][EDMA3_MAX_TC] =    {
													{
													34u, 35u, 0u, 0u,
													0u, 0u, 0u, 0u,
													},
													{
													2u, 3u, 4u, 5u,
													0u, 0u, 0u, 0u,
													},
													{
													18u, 19u, 20u, 21u,
													0u, 0u, 0u, 0u,
													},
												};

/* Driver Object Initialization Configuration */
EDMA3_RM_GblConfigParams sampleEdma3GblCfgParams[NUM_EDMA3_INSTANCES] =
	{
		{
		/* EDMA3 INSTANCE# 0 */
		/** Total number of DMA Channels supported by the EDMA3 Controller */
		16u,
		/** Total number of QDMA Channels supported by the EDMA3 Controller */
		8u,
		/** Total number of TCCs supported by the EDMA3 Controller */
		16u,
		/** Total number of PaRAM Sets supported by the EDMA3 Controller */
		128u,
		/** Total number of Event Queues in the EDMA3 Controller */
		2u,
		/** Total number of Transfer Controllers (TCs) in the EDMA3 Controller */
		2u,
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
		(void *)0x02700000u,
		/** Transfer Controller (TC) Registers */
		{
		(void *)0x02760000u,
		(void *)0x02768000u,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL
		},
		/** Interrupt no. for Transfer Completion */
		38u,
		/** Interrupt no. for CC Error */
		32u,
		/** Interrupt no. for TCs Error */
		{
		34u,
		35u,
		0u,
		0u,
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
		0u,
		0u,
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
		0u,
		0u,
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
		128u,
		128u,
		0u,
		0u,
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
		0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
		8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
		/* DMA channels 16-63 DOES NOT exist */
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS,
		EDMA3_MAX_PARAM_SETS, EDMA3_MAX_PARAM_SETS
		},

		 /**
		  * \brief Mapping from each DMA channel to a TCC. This specific
		  * TCC code will be returned when the transfer is completed
		  * on the mapped channel.
		  */
		{
		0u, 1u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		4u, 5u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		8u, 9u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		12u, 13u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		/* DMA channels 16-63 DOES NOT exist */
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC,
		EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC, EDMA3_MAX_TCC
		},

		/**
		 * \brief Mapping of DMA channels to Hardware Events from
		 * various peripherals, which use EDMA for data transfer.
		 * All channels need not be mapped, some can be free also.
		 */
		{
		0x00003333u,
		0x00000000u
		}
		},

		{
		/* EDMA3 INSTANCE# 1 */
		/** Total number of DMA Channels supported by the EDMA3 Controller */
		64u,
		/** Total number of QDMA Channels supported by the EDMA3 Controller */
		8u,
		/** Total number of TCCs supported by the EDMA3 Controller */
		64u,
		/** Total number of PaRAM Sets supported by the EDMA3 Controller */
		512u,
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
		(void *)0x02720000u,
		/** Transfer Controller (TC) Registers */
		{
		(void *)0x02770000u,
		(void *)0x02778000u,
		(void *)0x02780000u,
		(void *)0x02788000u,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL
		},
		/** Interrupt no. for Transfer Completion */
		8u,
		/** Interrupt no. for CC Error */
		0u,
		/** Interrupt no. for TCs Error */
		{
		2u,
		3u,
		4u,
		5u,
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
		0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
		8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
		16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
		24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
		32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
		40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u,
		48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
		56u, 57u, 58u, 59u, 60u, 61u, 62u, 63u
		},

		 /**
		  * \brief Mapping from each DMA channel to a TCC. This specific
		  * TCC code will be returned when the transfer is completed
		  * on the mapped channel.
		  */
		{
		0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
		8u, 9u, 10u, 11u, 12u, 13u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
		24u, 25u, 26u, 27u, 28u, 29u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
		40u, 41u, 42u, 43u, 44u, 45u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
		56u, 57u, 58u, 59u, 60u, 61u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
		},

		/**
		 * \brief Mapping of DMA channels to Hardware Events from
		 * various peripherals, which use EDMA for data transfer.
		 * All channels need not be mapped, some can be free also.
		 */
		{
		0x3FFF3FFFu,
		0x3FFF3FFFu
		}
		},

		{
		/* EDMA3 INSTANCE# 2 */
		/** Total number of DMA Channels supported by the EDMA3 Controller */
		64u,
		/** Total number of QDMA Channels supported by the EDMA3 Controller */
		8u,
		/** Total number of TCCs supported by the EDMA3 Controller */
		64u,
		/** Total number of PaRAM Sets supported by the EDMA3 Controller */
		512u,
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
		(void *)0x02740000u,
		/** Transfer Controller (TC) Registers */
		{
		(void *)0x02790000u,
		(void *)0x02798000u,
		(void *)0x027A0000u,
		(void *)0x027A8000u,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL,
		(void *)NULL
		},
		/** Interrupt no. for Transfer Completion */
		24u,
		/** Interrupt no. for CC Error */
		16u,
		/** Interrupt no. for TCs Error */
		{
		18u,
		19u,
		20u,
		21u,
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
		0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
		8u, 9u, 10u, 11u, 12u, 13u, 14u, 15u,
		16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
		24u, 25u, 26u, 27u, 28u, 29u, 30u, 31u,
		32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
		40u, 41u, 42u, 43u, 44u, 45u, 46u, 47u,
		48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
		56u, 57u, 58u, 59u, 60u, 61u, 62u, 63u
		},

		 /**
		  * \brief Mapping from each DMA channel to a TCC. This specific
		  * TCC code will be returned when the transfer is completed
		  * on the mapped channel.
		  */
		{
		0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
		8u, 9u, 10u, 11u, 12u, 13u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		16u, 17u, 18u, 19u, 20u, 21u, 22u, 23u,
		24u, 25u, 26u, 27u, 28u, 29u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		32u, 33u, 34u, 35u, 36u, 37u, 38u, 39u,
		40u, 41u, 42u, 43u, 44u, 45u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP,
		48u, 49u, 50u, 51u, 52u, 53u, 54u, 55u,
		56u, 57u, 58u, 59u, 60u, 61u, EDMA3_RM_CH_NO_TCC_MAP, EDMA3_RM_CH_NO_TCC_MAP
		},

		/**
		 * \brief Mapping of DMA channels to Hardware Events from
		 * various peripherals, which use EDMA for data transfer.
		 * All channels need not be mapped, some can be free also.
		 */
		{
		0x3FFF3FFFu,
		0x3FFF3FFFu
		}
		},
	};

EDMA3_RM_InstanceInitConfig sampleInstInitConfig[NUM_EDMA3_INSTANCES][EDMA3_MAX_REGIONS] =
	{
		/* EDMA3 INSTANCE# 0 */
		{
			/* Resources owned/reserved by region 0 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFF000Fu, 0x00000FFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x0000000Fu, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000003u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x0000000Fu, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000003u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     	0 */
				{0x00000003u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     	0 */
				{0x00000003u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 1 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x000000F0u, 0xFFFFF000u, 0x000000FFu, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x000000F0u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x0000000Cu},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x000000F0u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000030u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000030u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000030u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 2 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000F00u, 0x00000000u, 0xFFFFFF00u, 0x0000000Fu,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000F00u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000030u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000F00u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000300u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000300u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000300u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 3 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0xFFFFFFF0u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x0000F000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000C0u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x0000F000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00003000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00003000u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00003000u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 4 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 5 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 6 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 7 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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
	    },

		/* EDMA3 INSTANCE# 1 */
	    {
	        /* Resources owned/reserved by region 0 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000FFFFu, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x0000FFFFu, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000003u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x0000FFFFu, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00003FFFu, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00003FFFu, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00003FFFu, 0x00000000u},
			},

	        /* Resources owned/reserved by region 1 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFF0000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x0000000Cu},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFF0000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x3FFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x3FFF0000u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x3FFF0000u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 2 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x0000FFFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 415  384     447  416     479  448     511  480 */
				 0x0000FFFFu, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x0000FFFFu},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000030u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x0000FFFFu},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00003FFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00003FFFu},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00003FFFu},
			},

	        /* Resources owned/reserved by region 3 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0xFFFF0000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0xFFFF0000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000C0u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0xFFFF0000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x3FFF0000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x3FFF0000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x3FFF0000u},
			},

	        /* Resources owned/reserved by region 4 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 5 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 6 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 7 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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
	    },

		/* EDMA3 INSTANCE# 2 */
		{
	        /* Resources owned/reserved by region 0 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000FFFFu, 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 159  128     191  160     223  192     255  224 */
				 0xFFFFFFFFu, 0x0000FFFFu, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x0000FFFFu, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000003u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x0000FFFFu, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00003FFFu, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00003FFFu, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00003FFFu, 0x00000000u},
			},

	        /* Resources owned/reserved by region 1 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0xFFFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 287  256     319  288     351  320     383  352 */
				 0xFFFFFFFFu, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0xFFFF0000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x0000000Cu},

				/* ownTccs */
				/* 31     0     63    32 */
				{0xFFFF0000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x3FFF0000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x3FFF0000u, 0x00000000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x3FFF0000u, 0x00000000u},
			},

	        /* Resources owned/reserved by region 2 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x0000FFFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
				/* 415  384     447  416     479  448     511  480 */
				 0x0000FFFFu, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x0000FFFFu},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000030u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x0000FFFFu},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00003FFFu, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00003FFFu},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00003FFFu},
			},

	        /* Resources owned/reserved by region 3 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0xFFFF0000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0xFFFF0000u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0xFFFF0000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x000000C0u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0xFFFF0000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x3FFF0000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,},

				/* resvdDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x3FFF0000u},

				/* resvdQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* resvdTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x3FFF0000u},
			},

	        /* Resources owned/reserved by region 4 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 5 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 6 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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

	        /* Resources owned/reserved by region 7 */
			{
				/* ownPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x0000F000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

				/* ownDmaChannels */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* ownQdmaChannels */
				/* 31     0 */
				{0x00000000u},

				/* ownTccs */
				/* 31     0     63    32 */
				{0x00000000u, 0x00000000u},

				/* resvdPaRAMSets */
				/* 31     0     63    32     95    64     127   96 */
				{0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 159  128     191  160     223  192     255  224 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 287  256     319  288     351  320     383  352 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
				/* 415  384     447  416     479  448     511  480 */
				 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u},

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
	    },
	};

/* End of File */
