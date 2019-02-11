/*
*
* Copyright (c) 2013-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/*==========================================================================*/
/*==========================================================================*/
/**
*  @file       edmacc_config.h
*
*  @brief      Contains edma channel controller configuration
*
*
*/
#ifndef EDMACC_CONFIG_H_
#define EDMACC_CONFIG_H_

#ifndef _TMS320C6X
#ifdef VAYU_PLATFORM

/* Number of param set RAM for EDMA sub module for VAYU platform*/
#define EDMA_NUM_PARAMS 128U
/* Number of Queues available for EDMA sub module for VAYU platform*/
#define EDMA_NUM_QUES   2U

/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    16U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    16U

/* Number of EDMA Events available */
#define NUM_EEVTS       16U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        16U

#endif /* VAYU_PLATFORM */

#ifdef VME_PLATFORM
/* Number of param set RAM for EDMA sub module for VME platform*/
#define EDMA_NUM_PARAMS 64U
/* Number of Queues available for EDMA sub module for VME platform*/
#define EDMA_NUM_QUES   1U

/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    16U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    16U

/* Number of EDMA Events available */
#define NUM_EEVTS       16U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        16U

#endif /* VME_PLATFORM */

#else
/* _TMS320C6X */

/* Number of param set RAM for EDMA sub module for DSP platform*/
#define EDMA_NUM_PARAMS 128U
/* Number of Queues available for EDMA sub module for DSP platform*/
#define EDMA_NUM_QUES   2U

/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* It is important to note that DSP actually supports 64 channels but in order to
keep software efficient and simple we are limitting the number of channels for DSP also
to 32. */

/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    32U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    32U

/* Number of EDMA Events available */
#define NUM_EEVTS       32U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        32U

#endif /* _TMS320C6X */



#ifdef HOST_EMULATION
#define EDMA_NUM_PARAMS 128U
/* Number of Queues available for EDMA sub module for VAYU platform*/
#define EDMA_NUM_QUES   1U
/*-----------------------------------------------------------------------*/
/*  This is the number of logical channels that we need for this test    */
/*-----------------------------------------------------------------------*/
/* Maximum number of channels available */
#define NUM_MAX_CHANNELS    16U

/* Number of QDMA channels available */
#define NUM_QDMA_CHANNELS    8U

/* Number of EDMA channels available */
#define NUM_EDMA_CHANNELS    16U

/* Number of EDMA Events available */
#define NUM_EEVTS       16U

/* Number of QDMA Events available */
#define NUM_QEVTS        8U

/* Number of transfer completion codes available */
#define EDMA_NUM_TCCS        16U

#endif /* HOST_EMULATION */

#endif /*EDMACC_CONFIG_H_*/
