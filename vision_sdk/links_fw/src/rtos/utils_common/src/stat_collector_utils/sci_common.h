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

#ifndef SCI_COMMON_H
#define SCI_COMMON_H

#include <stdlib.h>
#include <stdint.h>
#include "sc_reg.h"

/* Statistic Collector register typedef */
/* typedef volatile uint32_t reg32_t; */


/*
 * Register definitions
 *
 */
#define SC_REQUEST_PROBE        0x0
#define SC_RESPONSE_PROBE       0x1


#define SC_EVENT_SEL_NONE     0x0 /* No event selected */
#define SC_EVENT_SEL_ANY      0x1 /* Any clock cycles */
#define SC_EVENT_SEL_TRANSFER 0x2 /* Header, necker or data has been accepted by the receiver */
#define SC_EVENT_SEL_WAIT     0x3 /* Transfer initiated but the transmitter has no data to send */
#define SC_EVENT_SEL_BUSY     0x4 /* Receiver applies flow control */
#define SC_EVENT_SEL_PKT      0x5 /* Transfer of a new packet header */
#define SC_EVENT_SEL_DATA     0x6 /* Transfer of a payload word
                                     *   Request link: Store data
                                     *   Respose link: Load data
                                     */
#define SC_EVENT_SEL_IDLE     0x7 /* No communication over the link */
#define SC_EVENT_SEL_LATENCY  0x8 /* Debug bit detection */

/* If op_sel set to MIN_MAX_HIT or EVT_INFO then evt_info_sel applies */
#define SC_EVTINFOSEL_BYTELEN   0x0 /* Length of transfer in bytes */
#define SC_EVTINFOSEL_PRESSURE  0x1 /* Pressure */
#define SC_EVTINFOSEL_LATENCY   0x2U /* Amount of wait time */

/* op_sel determines how the counter functions */
#define SC_OPSEL_FILTER_HIT     0x0U /* Counter increments on a filter hit */
#define SC_OPSEL_MINMAX_HIT     0x1U /* Counter increments when the filter hits
                                     * and the selected event info is in range
                                     * (Min threshold <= Evt_Info <= Max threshold)
                                     */
#define SC_OPSEL_EVT_INFO       0x2U /* Selected Evt_Info added to the counter value
                                     * when the filter hits
                                     */
#define SC_OPSEL_AND_FILTER     0x3 /* Counter increments by one when all unit
                                     * filters hit.
                                     */
#define SC_OPSEL_OR_FILTER      0x4 /* Counter increments by one when at least
                                     * one unit filters hits.
                                     */
#define SC_OPSEL_SUM_REQ_EVT    0x5 /* Counter sums the events from any request
                                     * port.
                                     */
#define SC_OPSEL_SUM_RSP_EVT    0x6 /* Counter sums the events from any response
                                     * port.
                                     */
#define SC_OPSEL_SUM_ALL_EVT    0x7 /* Counter sums the events from any request
                                     * and response ports.
                                     */
#define SC_OPSEL_EX_EVT         0x8 /* Counter increments by one when the selected
                                     * ExtEvt input signal is sampled high
                                     */

#ifdef _STM_Logging
/* The following are common strings and tables shared between all device types */

/* Trasaction type names */
const char trans_type_rd[] = "Rd";
const char trans_type_wr[] = "Wr";
const char trans_type_none[] = "RdWrNone";
const char trans_type_dontcare[] = "RdWrDontCare";

/* Use sci_trans_qual to select */
const char * trans_type_table[] = { trans_type_rd,
                                    trans_type_wr,
                                    trans_type_none,
                                    trans_type_dontcare};



/* Usecase enums for sdram and mstr sc module types are identical
    0 SCI_SDRAM_THROUGHPUT,                    SCI_MSTR_THROUGHPUT
    1 SCI_SDRAM_LINKOCCUPY_REQUEST,            SCI_MSTR_LINKOCCUPY_REQUEST
    2 SCI_SDRAM_LINKOCCUPY_RESPONSE,           SCI_MSTR_LINKOCCUPY_RESPONSE
    3 SCI_SDRAM_AVGBURST_LENGTH,               SCI_MSTR_AVGBURST_LENGTH
    4 SCI_SDRAM_AVGLATENCY_NOT_SUPPORTED       SCI_MSTR_AVGLATENCY
#if _SC_VER_1_16
    5 SCI_SDRAM_THROUGHPUT_MINALARM,           SCI_MSTR_THROUGHPUT_MINALARM
    6 SCI_SDRAM_THROUGHPUT_MAXALARM,           SCI_MSTR_THROUGHPUT_MAXALARM
    7 SCI_SDRAM_LATENCY_MAXALARM_NOT_SUPPORTED SCI_MSTR_LATENCY_MAXALARM
#endif
*/
const char usecase_name_tp[]  = "ThroughPut per Sampling Period";
const char usecase_name_reslo[] ="Request Port Link Occupancy";
const char usecase_name_rsplo[] ="Response Port Link Occupancy";
const char uusecase_name_abl[] = "Average Burst Length";
const char uusecase_name_ald[] = "Average Latency Distribution";
const char uusecase_name_tpmax[]  = "ThroughPut per Sample Period - Max Alarm";
const char uusecase_name_tpmin[]  = "ThroughPut per Sample Period - Min Alarm";
const char uusecase_name_aldmax[]  = "Average Latency - Max Alarm";

/* Use usecaseid to index */
const char * usecase_name_table[] = {
     usecase_name_tp,
     usecase_name_reslo,
     usecase_name_rsplo,
     uusecase_name_abl,
     uusecase_name_ald,
     uusecase_name_tpmax,
     uusecase_name_tpmin,
     uusecase_name_aldmax
};

/* Counter names */
const char cntr_name_payload[]= "Payload Length";
const char cntr_name_idle[] = "Idle";
const char cntr_name_packcnt[] = "Packet Count";
const char cntr_name_latcyc[] = "Latency Cycle Count";
const char cntr_name_lattrans[] = "Latency Transaction Count";

const int usecase_formula_table[] = {2,3,3,1,9,2,2,9};

const char usecase_units_bytesperpacket[] = "Bytes/Packet";
const char usecase_units_bytesperwindow[] = "Bytes/Sample Window";
const char usecase_units_percent[] ="%";
const char usecase_units_cyclespertrans[] = "Cycles/Transaction";

#define SCI_META_BUFSIZE 256

#endif /* End of _STM_Logging */

#define SC_GET_USECASE_COMPAT_VALUE(n) ((n) >> 16)
#define SC_USECASE_MASK(n)             ((n) & 0x000000FF)

#define SC_MOD_TYPE (0x003A0001U)     /* Identifies the module as a SC Module */

#define GET_SCMOD_FUNC(n) ((n) >> 24)

#ifdef _SC_VER_1_16
#define DMM_LISA_MAP_BASE 0x4e000040U
typedef union DMM_LISA_MAP
{
    uint32_t val;
    struct {
        uint32_t sdrc_addr   :8U;
        uint32_t sdrc_map    :2U;
        uint32_t reserved_6  :6U;
        uint32_t sdrc_addrspc:2U;
        uint32_t sdrc_intl   :2U;
        uint32_t sys_size    :3U;
        uint32_t reserved_1  :1U;
        uint32_t sys_addr    :8U;
    } field;
}DMM_LISA_MAP_T;
#endif

#endif /* End of SCI_COMMON_H */
