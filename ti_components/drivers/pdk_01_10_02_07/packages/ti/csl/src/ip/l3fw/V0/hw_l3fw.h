/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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

#ifndef HW_L3FW_H_
#define HW_L3FW_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define L3FW_ERROR_LOG(m)                   ((uint32_t) 0x0U + ((m) * 0x10U))
#define L3FW_LOGICAL_ADDR_ERRLOG(m)         ((uint32_t) 0x4U + ((m) * 0x10U))
#define L3FW_REGUPDATE_CONTROL              ((uint32_t) 0x40U)
#define L3FW_START_REGION(m)                ((uint32_t) 0x80U + ((m) * 0x10U))
#define L3FW_END_REGION(m)                  ((uint32_t) 0x84U + ((m) * 0x10U))
#define L3FW_MRM_PERMISSION_REGION_LOW(m)   ((uint32_t) 0x88U + ((m) * 0x10U))
#define L3FW_MRM_PERMISSION_REGION_HIGH(m)  ((uint32_t) 0x8cU + ((m) * 0x10U))

/****************************************************************************************************
 * Field Definition Macros
 ****************************************************************************************************/
#define L3FW_START_REGION_START_REGION_1_SHIFT             (10U)
#define L3FW_START_REGION_START_REGION_1_MASK              (0xFFFFFC00U)

#define L3FW_REGUPDATE_CONTROL_FW_ADDR_SPACE_MSB_SHIFT     (16U)
#define L3FW_REGUPDATE_CONTROL_FW_ADDR_SPACE_MSB_MASK      (0x000F0000U)

#define L3FW_REGUPDATE_CONTROL_BUSY_REQ_SHIFT              (0U)
#define L3FW_REGUPDATE_CONTROL_BUSY_REQ_MASK               (0x00000001U)

#define L3FW_END_REGION_END_REGION_1_SHIFT                 (10U)
#define L3FW_END_REGION_END_REGION_1_MASK                  (0xFFFFFC00U)

#define L3FW_ERROR_LOG_REQINFO_ERRLOG_SHIFT                 (0U)
#define L3FW_ERROR_LOG_REQINFO_ERRLOG_MASK                  (0x00000FFFU)
#define L3FW_ERROR_LOG_REGION_END_ERRLOG_SHIFT              (12U)
#define L3FW_ERROR_LOG_REGION_END_ERRLOG_MASK               (0x0001F000U)
#define L3FW_ERROR_LOG_REGION_START_ERRLOG_SHIFT            (17U)
#define L3FW_ERROR_LOG_REGION_START_ERRLOG_MASK             (0x003E0000U)
#define L3FW_ERROR_LOG_BLK_BURST_VIOLATION_SHIFT            (22U)
#define L3FW_ERROR_LOG_BLK_BURST_VIOLATION_MASK             (0x00800000U)

#define L3FW_LOGICAL_ADDR_ERRLOG_SLVOFS_LOGICAL_SHIFT       (0U)
#define L3FW_LOGICAL_ADDR_ERRLOG_SLVOFS_LOGICAL_MASK        (0xFFFFFFFFU)

#define L3FW_ERROR_LOG_CONNID_SHIFT                              (8U)
#define L3FW_ERROR_LOG_CONNID_MASK                               (0x00000f00U)

#define L3FW_ERROR_LOG_MCMD_SHIFT                                (7U)
#define L3FW_ERROR_LOG_MCMD_MASK                                 (0x00000080U)

#define L3FW_ERROR_LOG_MREQDEBUG_SHIFT                           (3U)
#define L3FW_ERROR_LOG_MREQDEBUG_MASK                            (0x00000008U)
#define L3FW_ERROR_LOG_MREQTYPE_SHIFT                            (0U)
#define L3FW_ERROR_LOG_MREQTYPE_MASK                             (0x00000001U)
#define L3FW_ERROR_LOG_SUPERVISOR_SHIFT                          (1U)
#define L3FW_ERROR_LOG_SUPERVISOR_MASK                           (0x00000002U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_L3FW_H_ */

