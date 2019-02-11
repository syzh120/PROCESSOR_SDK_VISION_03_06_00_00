/*
 * Remote processor power management
 *
 * Copyright (c) 2011-2013 Texas Instruments. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name Texas Instruments nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <_MultiProc.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef _IPU_PM_H
#define _IPU_PM_H

#define IPU_PM_MAX_PROCS 3

typedef struct ipu_pm_config_tag {
    uint32_t int_id;
    /*!< Mailbox interrupt ID */
    uint32_t num_procs;
    /*!< Number of remote procs to configure */
    uint16_t proc_ids[IPU_PM_MAX_PROCS];
    /*!< Array of proc IDs to configure */
} ipu_pm_config;

typedef enum {
    _NONE,
    _NEED_IVA_OPP50,
    _NEED_IVA_OPP100,
    _NEED_IVA_OPPTURBO
} ipu_pm_requirement_t;

struct ipu_pm_const_req {
    unsigned rsrc;
    unsigned target_rsrc;
    unsigned rate;
};

#define NO_FREQ_CONSTRAINT  0
#define NO_LAT_CONSTRAINT  -1
#define NO_BW_CONSTRAINT   -1

#define FREQ_266Mhz 266000000
#define FREQ_133Mhz 133000000

int ipu_pm_setup(ipu_pm_config *cfg);
int ipu_pm_destroy(void);
int ipu_pm_attach(int proc_id);
int ipu_pm_detach(int proc_id);
int ipu_pm_ivaseq1_disable(void);
int ipu_pm_ivaseq1_enable(void);
int ipu_pm_ivaseq0_disable(void);
int ipu_pm_ivaseq0_enable(void);
int ipu_pm_ivahd_disable(void);
int ipu_pm_ivahd_enable(void);
int ipu_pm_ivahd_off(void);
int ipu_pm_restore_ctx(int proc_id);
int ipu_pm_gpt_enable(int num);
int ipu_pm_gpt_disable(int num);
int ipu_pm_gpt_start(int num);
int ipu_pm_gpt_stop(int num);
void restore_gpt_context(int num);
int ipu_pm_set_bandwidth(unsigned int bandwidth);
int ipu_pm_set_rate(struct ipu_pm_const_req * request);
int ipu_pm_led_enable(unsigned int mode, unsigned int intensity);
int ipu_pm_alloc_sdma(int num_chs, int* channels);
int ipu_pm_free_sdma(int num_chs, int* channels);
int ipu_pm_camera_enable(unsigned int mode, unsigned int on);
int ipu_pm_get_max_freq(unsigned int proc, unsigned int * freq);


#endif /* _IPU_PM_H */
