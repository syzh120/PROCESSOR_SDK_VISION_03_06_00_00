/*
 * csl2_dat_edma3lld_config.h
 *
 * Defines the hardware specific parameters required by the CSL DAT2 EDMA3
 * Adapter.
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

#ifndef _CSL_DAT2_EDMA3LLD_CONFIG_H
#define _CSL_DAT2_EDMA3LLD_CONFIG_H


/*
 * Settings to be used with the EDMA3 DRV APIs
 */
#define DAT_EDMA3LLD_HW_REGION_ID     (0x1u) /* DSP mapped to region1 on Davinci */
#define DAT_EDMA3LLD_HW_INST_ID         (0u) /* Hardware instance id */
#define DAT_EDMA3LLD_HW_EVT_QUEUE_ID    (0u) /* Event queue number to be used */
#define DAT_EDMA3LLD_HW_MAXPHYCHANNELS (32u) /* Max number of physical channels */

/*
 * Settings for the DAT adapter layer
 * has to be double checked by system integrator
 */
#define DAT_QUEUEDEPTH                (4u) /* Maximum number of QDMA channels/tcc(s)
                                          * allocated to the DAT layer
                                          */
/*
 * Convenience MACROs for use in DAT adapter layer
 */
/*
 * Clear bit in 32-bit register (task context)
 */
#define CLEAR_REGISTER32_BIT(reg,bit) \
        _dat_critical_section_enter(); (reg) &= (~(0x1 << (bit))); \
    _dat_critical_section_exit();
/*
 * Clear bit in 32-bit register (ISR context)
 */
#define CLEAR_REGISTER32_BIT_DURING_INT(reg,bit) \
        (reg) &= (~(0x1 << (bit)));

/*
 * Set bit in 32-bit register  (task context)
 */
#define SET_REGISTER32_BIT(reg,bit) \
        _dat_critical_section_enter(); ((reg) |= (0x1 << (bit))); \
        _dat_critical_section_exit();
/*
 * Set bit in 32-bit register (ISR context)
 */
#define SET_REGISTER32_BIT_DURING_INT(reg,bit) \
        ((reg) |= (0x1 << (bit)));

/*
 * Get bit from 32-bit register
 */
#define GET_REGISTER32_BIT(reg,bit) \
        (( ((reg)<< (31 - (bit)) ) >> 31) == 0)?0:1

/*
 * Commented out section in csl_dat2.c references these macros
 */
#define DAT_OPT_DEFAULT (0x0010000C) /* Sets up OPT for TCC Interrupt enabling
                                    * AB-sync transfers, static entry with TCC
                                    * not yet set */
#define DAT_OPT_TCC_POS_MASK   (0xC) /* This mask marks the position of TCC in
                                    * OPT
                                    */
#define DAT_INVALID_ID  (0xFFFFFFFF) /* Invalid ID */
#define DAT_NULL_LINK       (0xFFFF) /* Null link in the OPT */


/* OPT Field specific defines */
#define OPT_SYNCDIM_SHIFT                   (0x00000002u)
#define OPT_TCC_MASK                        (0x0003F000u)
#define OPT_TCC_SHIFT                       (0x0000000Cu)
#define OPT_ITCINTEN_SHIFT                  (0x00000015u)
#define OPT_TCINTEN_SHIFT                   (0x00000014u)
#define OPT_STATIC_SHIFT                   	(0x00000003u)


/*
 * Set Tcc in OPT
 */
#define DAT_OPT_TCC(opt,tcc) \
        ((unsigned int)(opt) | ((tcc)<<DAT_OPT_TCC_POS_MASK))

#endif /* _CSL_DAT2_EDMA3LLD_CONFIG_H */

