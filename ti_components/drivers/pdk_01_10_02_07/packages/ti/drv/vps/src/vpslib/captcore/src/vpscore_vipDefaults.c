/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 */

/**
 *  \file vpscore_vipDefaults.c
 *
 *  \brief Default NodeInfo and EdgeInfo structure for VIP
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <ti/drv/vps/src/vpslib/common/vps_graph.h>
#include <ti/drv/vps/src/vpslib/captcore/vpscore_vip.h>
#include <ti/drv/vps/src/vpslib/captcore/src/vpscore_vipPriv.h>

/* {nodeNum,                        inType,     outType,    nodeType,
 *            corePtr, 0, 0, {     input   },  {     input   }},  */
const Vgraph_nodeInfo vipNodeInfoDefaults[GRAPH_VIP_NUM_NODES] =
{ \
    {GRAPH_VIP_INVALID,               EMPTY_IN,  EMPTY_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_16,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_SEC0,               SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_COMP0,              SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CSC_SRC,            SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_SC_SRC,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CSC,                SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_CSC, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_SC,                 SINGLE_IN, MULTI_OUT, VGRAPH_NODETYPE_SC,
                                        NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS0_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS1_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS0_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS1_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS0,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_CHRDS1,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_RGB_HI,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_Y_UP,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_UV_UP,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_Y_LO,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_UV_LO,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTA_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PARSER_PORTB_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTA_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTA_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTB_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTB_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTA_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_PORTB_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ACTA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ACTB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ANCA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S0_MULT_ANCB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
                                               \
                                               \
    {GRAPH_VIP_S1_PARSER_PORTA,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB,       EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB_INTF,  SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_16,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_SEC0,               SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_COMP0,              SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPPORT, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CSC_SRC,            SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_SC_SRC,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CSC,                SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_CSC, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_SC,                 SINGLE_IN, MULTI_OUT, VGRAPH_NODETYPE_SC,
                                        NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS0_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS1_ON,          SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS0_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS1_OFF,         SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS0,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_CHRDS1,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_RGB_HI,             SINGLE_IN, MULTI_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_Y_UP,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_UV_UP,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_Y_LO,               SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_UV_LO,              SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VIPMUX, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTA_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PARSER_PORTB_ANC,   EMPTY_IN,  MULTI_OUT,
                                        VGRAPH_NODETYPE_DUMMY, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTA_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTA_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTB_LUMA,         SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTB_CHROMA,       SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTA_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_PORTB_RGB,          MULTI_IN,  SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ACTA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ACTB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ANCA_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
    {GRAPH_VIP_S1_MULT_ANCB_SRC0,     SINGLE_IN, SINGLE_OUT,
                                        VGRAPH_NODETYPE_VPDMA, NULL, 0, 0,
                                        {0,                               {NULL},
                                        {0}},
                                        {0,                               {NULL},
                                        {0}}}, \
};

/***
 * Defining EdgeList:
 * Muxes: Arrange in terms of mux values, if any entry is invalid, mark as
 * GRAPH_VIP_INVALID
 ***/
const Vgraph_edgeInfo vipEdgeInfoDefaults[GRAPH_VIP_NUM_EDGES] =
{                                                                       \
    {GRAPH_VIP_S0_PARSER_PORTA,       GRAPH_VIP_S0_PARSER_PORTA_ANC  }, \
    {GRAPH_VIP_S0_PARSER_PORTA,       GRAPH_VIP_S0_PARSER_PORTA_INTF }, \
                                                                        \
    {GRAPH_VIP_S0_PARSER_PORTB,       GRAPH_VIP_S0_PARSER_PORTB_ANC  }, \
    {GRAPH_VIP_S0_PARSER_PORTB,       GRAPH_VIP_S0_PARSER_PORTB_INTF }, \
                                                                        \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  GRAPH_VIP_S0_PARSER_PORTA_08   }, \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  GRAPH_VIP_S0_PARSER_PORTA_16   }, \
    {GRAPH_VIP_S0_PARSER_PORTA_INTF,  GRAPH_VIP_S0_PARSER_PORTA_24   }, \
    {GRAPH_VIP_S0_PARSER_PORTB_INTF,  GRAPH_VIP_S0_PARSER_PORTB_08   }, \
                                                                        \
    {GRAPH_VIP_S0_PARSER_PORTA_08,    GRAPH_VIP_S0_PARSER_PORTA_08_16}, \
    {GRAPH_VIP_S0_PARSER_PORTA_16,    GRAPH_VIP_S0_PARSER_PORTA_08_16}, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    GRAPH_VIP_S0_CSC_SRC           }, \
    {GRAPH_VIP_S0_COMP0,              GRAPH_VIP_S0_CSC_SRC           }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_SC_SRC            }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_SC_SRC            }, \
                                                                        \
    {GRAPH_VIP_S0_CSC_SRC,            GRAPH_VIP_S0_CSC               }, \
    {GRAPH_VIP_S0_SC_SRC,             GRAPH_VIP_S0_SC                }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS0_ON         }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS0_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS1_ON         }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS1_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS0_OFF        }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS0_OFF        }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_SC,                 GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_CHRDS1_OFF        }, \
    {GRAPH_VIP_S0_SEC0,               GRAPH_VIP_S0_CHRDS1_OFF        }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS0_ON,          GRAPH_VIP_S0_CHRDS0            }, \
    {GRAPH_VIP_S0_CHRDS0_OFF,         GRAPH_VIP_S0_CHRDS0            }, \
    {GRAPH_VIP_S0_CHRDS1_ON,          GRAPH_VIP_S0_CHRDS1            }, \
    {GRAPH_VIP_S0_CHRDS1_OFF,         GRAPH_VIP_S0_CHRDS1            }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_RGB_HI            }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_RGB_HI            }, \
    {GRAPH_VIP_S0_COMP0,              GRAPH_VIP_S0_RGB_HI            }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_RGB_HI            }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS1,             GRAPH_VIP_S0_Y_LO              }, \
    {GRAPH_VIP_S0_PARSER_PORTA_08_16, GRAPH_VIP_S0_Y_LO              }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_Y_LO              }, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    GRAPH_VIP_S0_Y_LO              }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS1,             GRAPH_VIP_S0_UV_LO             }, \
    {GRAPH_VIP_S0_PARSER_PORTB_08,    GRAPH_VIP_S0_UV_LO             }, \
    {GRAPH_VIP_S0_CSC,                GRAPH_VIP_S0_UV_LO             }, \
    {GRAPH_VIP_S0_PARSER_PORTA_24,    GRAPH_VIP_S0_UV_LO             }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS0,             GRAPH_VIP_S0_Y_UP              }, \
    {GRAPH_VIP_S0_RGB_HI,             GRAPH_VIP_S0_Y_UP              }, \
                                                                        \
    {GRAPH_VIP_S0_CHRDS0,             GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_S0_CHRDS0,             GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_S0_CHRDS1,             GRAPH_VIP_S0_UV_UP             }, \
    {GRAPH_VIP_S0_RGB_HI,             GRAPH_VIP_S0_UV_UP             }, \
                                                                        \
    {GRAPH_VIP_S0_Y_UP,               GRAPH_VIP_S0_PORTA_LUMA        }, \
    {GRAPH_VIP_S0_UV_UP,              GRAPH_VIP_S0_PORTA_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S0_Y_LO,               GRAPH_VIP_S0_PORTB_LUMA        }, \
    {GRAPH_VIP_S0_UV_LO,              GRAPH_VIP_S0_PORTB_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S0_Y_UP,               GRAPH_VIP_S0_PORTA_RGB         }, \
    {GRAPH_VIP_S0_UV_UP,              GRAPH_VIP_S0_PORTA_RGB         }, \
    {GRAPH_VIP_S0_Y_LO,               GRAPH_VIP_S0_PORTB_RGB         }, \
    {GRAPH_VIP_S0_UV_LO,              GRAPH_VIP_S0_PORTB_RGB         }, \
                                                                        \
    {GRAPH_VIP_S0_Y_LO,               GRAPH_VIP_S0_MULT_ACTA_SRC0    }, \
    {GRAPH_VIP_S0_PARSER_PORTA_ANC,   GRAPH_VIP_S0_MULT_ANCA_SRC0    }, \
    {GRAPH_VIP_S0_UV_LO,              GRAPH_VIP_S0_MULT_ACTB_SRC0    }, \
    {GRAPH_VIP_S0_PARSER_PORTB_ANC,   GRAPH_VIP_S0_MULT_ANCB_SRC0    }, \
                                                                        \
                                                                        \
                                                                        \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTA,       GRAPH_VIP_S1_PARSER_PORTA_ANC  }, \
    {GRAPH_VIP_S1_PARSER_PORTA,       GRAPH_VIP_S1_PARSER_PORTA_INTF }, \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTB,       GRAPH_VIP_S1_PARSER_PORTB_ANC  }, \
    {GRAPH_VIP_S1_PARSER_PORTB,       GRAPH_VIP_S1_PARSER_PORTB_INTF }, \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  GRAPH_VIP_S1_PARSER_PORTA_08   }, \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  GRAPH_VIP_S1_PARSER_PORTA_16   }, \
    {GRAPH_VIP_S1_PARSER_PORTA_INTF,  GRAPH_VIP_S1_PARSER_PORTA_24   }, \
    {GRAPH_VIP_S1_PARSER_PORTB_INTF,  GRAPH_VIP_S1_PARSER_PORTB_08   }, \
                                                                        \
    {GRAPH_VIP_S1_PARSER_PORTA_08,    GRAPH_VIP_S1_PARSER_PORTA_08_16}, \
    {GRAPH_VIP_S1_PARSER_PORTA_16,    GRAPH_VIP_S1_PARSER_PORTA_08_16}, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    GRAPH_VIP_S1_CSC_SRC           }, \
    {GRAPH_VIP_S1_COMP0,              GRAPH_VIP_S1_CSC_SRC           }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_SC_SRC            }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_SC_SRC            }, \
                                                                        \
    {GRAPH_VIP_S1_CSC_SRC,            GRAPH_VIP_S1_CSC               }, \
    {GRAPH_VIP_S1_SC_SRC,             GRAPH_VIP_S1_SC                }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS0_ON         }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS0_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS1_ON         }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS1_ON         }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS0_OFF        }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS0_OFF        }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_SC,                 GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_CHRDS1_OFF        }, \
    {GRAPH_VIP_S1_SEC0,               GRAPH_VIP_S1_CHRDS1_OFF        }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS0_ON,          GRAPH_VIP_S1_CHRDS0            }, \
    {GRAPH_VIP_S1_CHRDS0_OFF,         GRAPH_VIP_S1_CHRDS0            }, \
    {GRAPH_VIP_S1_CHRDS1_ON,          GRAPH_VIP_S1_CHRDS1            }, \
    {GRAPH_VIP_S1_CHRDS1_OFF,         GRAPH_VIP_S1_CHRDS1            }, \
                                                                        \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_RGB_HI            }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_RGB_HI            }, \
    {GRAPH_VIP_S1_COMP0,              GRAPH_VIP_S1_RGB_HI            }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_RGB_HI            }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS1,             GRAPH_VIP_S1_Y_LO              }, \
    {GRAPH_VIP_S1_PARSER_PORTA_08_16, GRAPH_VIP_S1_Y_LO              }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_Y_LO              }, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    GRAPH_VIP_S1_Y_LO              }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS1,             GRAPH_VIP_S1_UV_LO             }, \
    {GRAPH_VIP_S1_PARSER_PORTB_08,    GRAPH_VIP_S1_UV_LO             }, \
    {GRAPH_VIP_S1_CSC,                GRAPH_VIP_S1_UV_LO             }, \
    {GRAPH_VIP_S1_PARSER_PORTA_24,    GRAPH_VIP_S1_UV_LO             }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS0,             GRAPH_VIP_S1_Y_UP              }, \
    {GRAPH_VIP_S1_RGB_HI,             GRAPH_VIP_S1_Y_UP              }, \
                                                                        \
    {GRAPH_VIP_S1_CHRDS0,             GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_S1_CHRDS0,             GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_INVALID,               GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_S1_CHRDS1,             GRAPH_VIP_S1_UV_UP             }, \
    {GRAPH_VIP_S1_RGB_HI,             GRAPH_VIP_S1_UV_UP             }, \
                                                                        \
    {GRAPH_VIP_S1_Y_UP,               GRAPH_VIP_S1_PORTA_LUMA        }, \
    {GRAPH_VIP_S1_UV_UP,              GRAPH_VIP_S1_PORTA_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S1_Y_LO,               GRAPH_VIP_S1_PORTB_LUMA        }, \
    {GRAPH_VIP_S1_UV_LO,              GRAPH_VIP_S1_PORTB_CHROMA      }, \
                                                                        \
    {GRAPH_VIP_S1_Y_UP,               GRAPH_VIP_S1_PORTA_RGB         }, \
    {GRAPH_VIP_S1_UV_UP,              GRAPH_VIP_S1_PORTA_RGB         }, \
    {GRAPH_VIP_S1_Y_LO,               GRAPH_VIP_S1_PORTB_RGB         }, \
    {GRAPH_VIP_S1_UV_LO,              GRAPH_VIP_S1_PORTB_RGB         }, \
                                                                        \
    {GRAPH_VIP_S1_Y_LO,               GRAPH_VIP_S1_MULT_ACTA_SRC0    }, \
    {GRAPH_VIP_S1_PARSER_PORTA_ANC,   GRAPH_VIP_S1_MULT_ANCA_SRC0    }, \
    {GRAPH_VIP_S1_UV_LO,              GRAPH_VIP_S1_MULT_ACTB_SRC0    }, \
    {GRAPH_VIP_S1_PARSER_PORTB_ANC,   GRAPH_VIP_S1_MULT_ANCB_SRC0    }, \
};
