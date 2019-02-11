/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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


/**
 *  @file       bam_beam_forming.h
 *
 *  @brief      This header defines interfaces for Beam Forming kernels
 *              into BAM.
 */

#ifndef BAM_BEAM_FORMING_H_
#define BAM_BEAM_FORMING_H_

#include "bam_common.h"

#define BAM_BEAM_FORMING_MAX_NUM_DETECTIONS (2048U)

typedef enum
{
  /* cmdId is this then corresponding args should be BAM_BeamForming_InCtrlArgs */
  BAM_BEAM_FORMING_CTRL_CMD_ID_SET_PARAMS = 0,
  /* cmdId is this then corresponding args should be BAM_BeamForming_OutCtrlArgs */
  BAM_BEAM_FORMING_CTRL_CMD_ID_GET_WBUF_PTR
} eBAM_BEAM_FORMING_CTRL_CMD_ID;


typedef struct
{
  uint16_t       maxNumAntenna;
  uint16_t       maxNumDetectionPerBlock;
  uint16_t       maxNumTotalDetection;
  uint16_t       maxNumAngle;
} BAM_BeamForming_Args;

typedef struct
{
  uint16_t       cmdId;
  void          *ctrlArgs;
} BAM_BeamForming_CtrlArgs;


typedef struct
{
  uint16_t       numDetections;
  uint16_t       numAntennas;
  uint16_t       numAngles;
  uint16_t       beamFormingScaling;
  uint16_t       energyScaling;
  /* This pointer is shared between kernel node and DMA node and is used to
  decide whether to execute copy kernel or not */
  uint32_t        *enableSMcopyShared;
} BAM_BeamForming_InCtrlArgs;

typedef struct
{
  /* These are the pointers allocated by this node but as we need to do further processing on
  this data we are getting these pointers outside of this node so that
  we can do further processing on the same without any need for doing
  EDMA transfer for the same */
  uint16_t       *WBUFptrToAngleBuf;
  uint16_t       *WBUFptrToEnergyBuf;
  /* This pointer is to re-use to memory allocated for param block for other kernels outside the graph */
  uint16_t       *WBUFpBlockPtr;
} BAM_BeamForming_OutCtrlArgs;


typedef struct
{
  /* This field will indicate that among numDetectionPerBlock detections how many
  of them are actually valid for a particular group */
  uint16_t      numValidDetection;
  uint16_t      baseAngleOffset;
} BAM_BeamForming_Info;

extern BAM_KernelHelperFuncDef gBAM_TI_beamFormingHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_beamFormingExecFunc;

extern BAM_KernelInfo gBAM_TI_beamFormingKernel;

typedef enum
{
  BAM_BEAM_FORMING_ANTENNA_DATA_PORT = 0,
  BAM_BEAM_FORMING_STEERING_MATRIX_PORT = 1,
  BAM_BEAM_FORMING_INFO_PORT = 2, /* For sharing BAM_BeamForming_Info structure between DMA and Kernel Node. This will be used for pBlockUpdate */
  BAM_BEAM_FORMING_NUM_INPUT_BLOCKS = 3
} eBAM_BEAM_FORMING_INPUT_PORTS;

typedef enum
{
  BAM_BEAM_FORMING_OUTPUT_PORT = 0,
  BAM_BEAM_FORMING_NUM_OUTPUT_BLOCKS = 1
} eBAM_BEAM_FORMING_OUTPUT_PORTS;

#endif /* BAM_BEAM_FORMING_H_ */

