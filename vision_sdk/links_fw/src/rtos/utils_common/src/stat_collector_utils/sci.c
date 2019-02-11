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
#include <src/rtos/utils_common/include/sci.h>
#ifdef _OMAP4430
#include "sci_config_omap4430.h"
#endif
#ifdef _OMAP4460
#include "sci_config_omap4460.h"
#endif
#ifdef _OMAP4470
#include "sci_config_omap4470.h"
#endif
#ifdef _OMAP5430
#include "sci_config_omap5430.h"
#endif
#ifdef _DRA7xx
#include "sci_config_dra7xx.h"
#endif
#ifdef _AM437x
#include "sci_config_am437x.h"
#endif
#ifdef _TDA3x
#include "sci_config_tda3x.h"
#endif
#include "sci_common.h"
#ifdef _STM_Logging
#include "StmSupport.h"
#include <stdio.h>
#endif

#include <stdbool.h>
/*
 *
 * Public external function prototypes
 *
 */

#ifndef _DOXYGEN_IGNORE
extern void * cTools_memAlloc(size_t sizeInBytes);
extern void cTools_memFree(void * ptr);
extern void * cTools_memMap(uint32_t phyAddr, uint32_t mapSizeInBytes);
extern void cTools_memUnMap(void * vAddr, uint32_t mapSizeInBytes);
extern int32_t cTools_mutexInit(uint32_t mutexId);
extern int32_t cTools_mutexTrylock(uint32_t mutexId);
extern int32_t cTools_mutexUnlock(uint32_t mutexId);
#endif

/*
 *
 * Private decarations
 *
 */

#if (defined(_SC_VER_1_16) && (SC_VER != 116))
#error "SC_VER of statistic collector in sci_config_<device>.h does not match _SC_VER_1_16"
#endif

#if (defined(_SC_VER_1_12) && (SC_VER != 112))
#error "SC_VER of statistic collector in sci_config_<device>.h does not match _SC_VER_1_12"
#endif

/* Devices that require the master address dump register set (DUMP_MSTADDR) */
#ifdef _AM437x
static const bool     set_mstaddr_enable = (bool)true;
static const uint32_t sdram_mstaddr_value = 0x3cU;
static const uint32_t mstr_mstaddr_value = 0x3cU;
#else
static const bool     set_mstaddr_enable = (bool)true;
static const uint32_t sdram_mstaddr_value = 0x0U;
static const uint32_t mstr_mstaddr_value = 0x0U;
#endif

enum sci_state {SCI_MOD_DISABLED, SCI_MOD_ENABLED };

struct sci_handle_t {
    enum sci_state mod_state;
    sci_callback psci_callback;
    uint32_t sdram_msg_rate;
    uint32_t mstr_msg_rate;
    bool trigger_enable;
    struct sci_usecase_key_t * pusecase_head;     /* use case link list pointer */
    enum sci_mode mode;
#ifdef _STM_Logging
    bool stm_log_enable;
    STMHandle *  pstm_handle;
    int32_t stm_ch;
    uint32_t data_options;
#endif
#ifdef _SC_VER_1_16
    uint32_t * dmm_lisa_vaddr;
#endif
};

struct usecase_parms {
    int32_t num_cntr_req;                      /* Number of SC counters required */
    uint32_t reqevt;
    uint32_t rspevt;
    int32_t port_type;
    uint32_t op_sel[2];
    uint32_t evt_info_sel[2];
};

sci_err_t get_meta_data(psci_handle const phandle, struct sci_usecase_key_t * puc_key,
                           const char * probe_name,
                           const char * trans_type,
                           const char * master_or_slave_name,
                           uint32_t mask );
sci_err_t send_meta_data (psci_handle const phandle);
sci_err_t get_usecase_params( int32_t usecase, struct usecase_parms * pusecase_parms);
sci_err_t get_cntr(enum sc_module_type mod_type, int32_t probe_id, int32_t usecase,
                      int32_t num_filters, int32_t num_cntr_req,
                      uint32_t * mod_index,  uint32_t * cntr_assigned);
void * get_cntr_addr( uint32_t mod, uint32_t cnt_index);
void * get_filter_addr ( uint32_t mod, uint32_t cnt_index, int32_t filter_index);
void put_uckey(psci_handle const phandle, struct sci_usecase_key_t * puc_key);
#ifdef _SC_VER_1_16
sci_err_t sys_to_phys_addr(psci_handle const phandle, uint32_t sys_addr_arg, uint32_t * phys_addr_arg);
#endif

typedef struct sc_module_resources {
        uint32_t * vbase_addr;
        bool owner;
        int32_t usecase;                    /* First use case - used for compatibility testing */
        int32_t usecase_cnt;                /* Number of use case jobs attached */
        bool * used;                   /* points to an array of bools, one per counter to indicate the counter is being used */
}sc_module_resources_t;

const uint32_t mod_cnt = sizeof(sc_map)/sizeof(sc_element_map_t *);
static sc_module_resources_t mod_map[sizeof(sc_map)/sizeof(sc_element_map_t *)];

#define SCI_MAX_COUNTERS    (8U)
#define SCI_MAX_MODULES     (10U)
bool gSCI_usedCounterMem[SCI_MAX_MODULES][SCI_MAX_COUNTERS];
sci_handle gSCI_handle;
int32_t gSCI_isOpen = 0;

/*
 * sci_open
 *
 * [KC] Modified to use static memory alloc, sci_open, can be called only once
 *
 */
sci_err_t sci_open(psci_handle * const pphandle, struct sci_config * const pcnfg)
{
    uint32_t i, j, n;
    uint32_t mode = 0; /* Default is SCI_MODE_STM */
    sci_err_t ret_val = SCI_SUCCESS;

    if(gSCI_isOpen)
    {
        /* handle is already opened, cannot open again */
        ret_val = SCI_ERR_INVALID_PARM;
    }

    /* If pCPT_Handle is not NULL then return error */
    if (NULL != *pphandle)
    {
        ret_val =   SCI_ERR_INVALID_HANDLE;
    }

    /* If config parameters are provided test they are valid */
    if ((SCI_SUCCESS == ret_val) && ( NULL != pcnfg ))
    {
        if ( 0 == pcnfg->sdram_msg_rate )
        {
            ret_val =  SCI_ERR_INVALID_PARM;
        }
        if ( 0 == pcnfg->mstr_msg_rate )
        {
            ret_val =  SCI_ERR_INVALID_PARM;
        }
    }

    /* Attempt to map the CP Tracer base address of each SC Module*/
    if (SCI_SUCCESS == ret_val)
    {
        for ( i = 0; i < mod_cnt; i++ )
        {

            /* Initialize the module resource values */
            mod_map[i].owner = (bool)false;
            mod_map[i].usecase =  -(int32_t)1;
            mod_map[i].usecase_cnt = 0;

            if((sc_map[i]->num_counters <= SCI_MAX_COUNTERS)
                &&
                (i < SCI_MAX_MODULES))
            {
                mod_map[i].used = gSCI_usedCounterMem[i];
            }
            else
            {
                mod_map[i].used = (bool)NULL;
            }

            if ( NULL == mod_map[i].used )
            {
                ret_val = SCI_ERR_MEM_ALLOC;
            }
            if(ret_val == SCI_SUCCESS)
            {
                for (n = 0; n < sc_map[i]->num_counters; n++)
                {
                /*
                * MISRA.PTR.ARITH
                * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
                * Pointer is used in arithmetic or array index expression
                * KW State: Defer -> Waiver -> Case by case
                */
                    mod_map[i].used[n] = (bool)false;
                }

                mod_map[i].vbase_addr = (uint32_t *)cTools_memMap(sc_map[i]->base_addr,
                                                                sc_map[i]->mod_size);
                /* If any modules fail to map, error out */
                if ( NULL == mod_map[i].vbase_addr )
                {
                    ret_val =  SCI_ERR_MAPPING;
                }
            }
            if(ret_val != SCI_SUCCESS)
            {
                break;
            }
        }
    }

    /* call sci_get_version to check compatibility with the hw module*/
    if ( SCI_SUCCESS == ret_val)
    {
        uint32_t plib_major_ver;
        uint32_t plib_minor_ver;
        uint32_t plib_func_id;
        uint32_t pmod_func_id;

        ret_val = sci_get_version(*pphandle, &plib_major_ver, &plib_minor_ver,
                                  &plib_func_id, &pmod_func_id );
    }

    /* Malloc the handle */
    if (SCI_SUCCESS == ret_val)
    {
        * pphandle = (sci_handle *)&gSCI_handle;
        if ( NULL == * pphandle )
        {
            ret_val = SCI_ERR_MEM_ALLOC;
        }
        else
        {
            /* Intialize the handle */
            (*pphandle)->mod_state = SCI_MOD_DISABLED;
            (*pphandle)->pusecase_head = NULL;
            if (NULL != pcnfg)
            {
                (*pphandle)->psci_callback = pcnfg->errhandler;
                (*pphandle)->sdram_msg_rate = pcnfg->sdram_msg_rate;
                (*pphandle)->mstr_msg_rate = pcnfg->mstr_msg_rate;
                (*pphandle)->trigger_enable = pcnfg->trigger_enable;
                (*pphandle)->mode = pcnfg->mode;
#ifdef _STM_Logging
                (*pphandle)->stm_log_enable = pcnfg->stm_log_enable;
                (*pphandle)->pstm_handle = pcnfg->pstm_handle;
                (*pphandle)->stm_ch = pcnfg->stm_ch;
                (*pphandle)->data_options = pcnfg->data_options;
#endif
            }
            else {
                (*pphandle)->psci_callback = NULL;
                (*pphandle)->sdram_msg_rate = 0U;
                (*pphandle)->mstr_msg_rate = 0U;
                (*pphandle)->trigger_enable = (bool)false;
                (*pphandle)->mode = SCI_MODE_STM;
#ifdef _STM_Logging
                (*pphandle)->stm_log_enable = false;
                (*pphandle)->pstm_handle = NULL;
                (*pphandle)->stm_ch = 0;
                (*pphandle)->data_options = 0;
#endif
            }
#ifdef _SC_VER_1_16
            (*pphandle)->dmm_lisa_vaddr = 0;
#endif
            /* Decide on operation mode */

            /* mode already initialized to the default 0 (for  SCI_MODE_STM) */
            if (NULL != pcnfg)
            {
                switch (pcnfg->mode)
                {
                    case SCI_MODE_DUMP:
                        mode = 0x1U;
                        break;
#ifdef _SC_VER_1_16
                    case SCI_MODE_STM_COND:
                        mode = 0x2U;
                        break;
                    case SCI_MODE_DUMP_COND:
                        mode = 0x3U;
                        break;
#endif
                    default:
                        break;
               }
            }

            /* Initialize each module for operation. Note that if the module
             *  is already in use, the library will override and take control
             *  of the module.
             */
            for ( i=0; i < mod_cnt; i++ )
            {
                if (NULL != mod_map[i].vbase_addr)
                {
                    switch (sc_map[i]->mod_type)
                    {
                        case SDRAM:
                        {
                            sc_sdram_regs * sc_regs;
                            /*
                            * MISRA.CAST.PTR
                            * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                            * and a different pointer to object type
                            * KW State: Defer -> Waiver -> Case by case
                            */
                            sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;

                            /* Disable the module in case it's already running */
                            sc_regs->soften = 0;
                            sc_regs->en = 1;

                            /*setup the master dump register if required */
                            if (set_mstaddr_enable)
                            {
                                sc_regs->dump_mstaddr = sdram_mstaddr_value;
                            }

                            /* Disable all the counters and filters, where
                            * i is the module index
                            * j is the counter index
                            * */
                            for (j = 0; j < sc_map[i]->num_counters; j++)
                            {
                                switch ( sc_map[i]->cnt_map[j].num_filters)
                                {
                                    case 0:
                                    {
                                        struct sc_sdram_cnt_filter0 * sc_cnt_addr =  (struct sc_sdram_cnt_filter0 *)get_cntr_addr( i, j);
                                        sc_cnt_addr->globalen = 0;
                                        break;

                                    }
                                    case 1:
                                    {
                                        struct sc_sdram_cnt_filter1 * sc_cnt_addr =  (struct sc_sdram_cnt_filter1 *)get_cntr_addr( i, j);
                                        sc_cnt_addr->globalen = 0;
                                        sc_cnt_addr->filter[0].en = 0;
                                        break;
                                    }
                                    case 2:
                                    {
                                        struct sc_sdram_cnt_filter2 * sc_cnt_addr =  (struct sc_sdram_cnt_filter2 *)get_cntr_addr( i, j);
                                        sc_cnt_addr->globalen = 0;
                                        sc_cnt_addr->filter[0].en = 0;
                                        sc_cnt_addr->filter[1].en = 0;
                                        break;
                                    }
                                    default:
                                        break;
                                } /* End of the switch */
                            }

                            sc_regs->dump_collecttime = (*pphandle)->sdram_msg_rate;
                            mod_map[i].owner = (bool)true;
                            sc_regs->dump_manual = mode;
#ifdef _SC_VER_1_16
                            sc_regs->dump_disable = 0;
#endif
                            break;
                        }
                        case MSTR:
                        {
                            sc_lat_regs * sc_regs;
                            sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;

                            /* Disable the module in case it's already running */
                            sc_regs->soften = 0;
                            sc_regs->en = 1;

                            /*setup the master dump register if required */
                            if (set_mstaddr_enable)
                            {
                                sc_regs->dump_mstaddr = mstr_mstaddr_value;
                            }

                            /* Disable all the counters and filters, where
                            * i is the module index
                            * j is the counter index
                            * */
                            for (j = 0; j < sc_map[i]->num_counters; j++)
                            {

                                struct sc_lat_cnt_filter1 * sc_cnt_addr =  (struct sc_lat_cnt_filter1 *)get_cntr_addr( i, j);
                                sc_cnt_addr->globalen = 0;
                                sc_cnt_addr->filter[0].en = 0;
                            }

                            sc_regs->dump_collecttime = (*pphandle)->mstr_msg_rate;
                            mod_map[i].owner = (bool)true;
                            sc_regs->dump_manual = mode;
#ifdef _SC_VER_1_16
                            sc_regs->dump_disable = 0;
#endif
                            break;
                        }
                            default:
                             break;
                    } /* End of switch */
                }
            }
        }
    }

    if ( SCI_SUCCESS != ret_val)
    {

        /* unmap each non-null mod_map[i]->vbase_addr */
        for ( i=0; i < mod_cnt; i++ )
        {
            if ( NULL != mod_map[i].vbase_addr )
            {
                cTools_memUnMap(mod_map[i].vbase_addr, sc_map[i]->mod_size);
                mod_map[i].vbase_addr = NULL;
            }
        }

        /* If handle non-null free it and set it back to NULL*/
        if ( NULL != *pphandle )
        {
            *pphandle = NULL;
        }

        /* Call callback - ok to call with NULL handle*/
        if (NULL != pcnfg)
        {
            if ( NULL != pcnfg->errhandler)
            {
                pcnfg->errhandler(*pphandle, __FUNCTION__, ret_val);
            }
        }
    }

    if (SCI_SUCCESS == ret_val)
    {
        gSCI_isOpen = 1;
    }
    return ret_val;
}

/*
 * sci_close
 *
 */
sci_err_t sci_close(psci_handle * const pphandle)
{
    uint32_t i;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == *pphandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }
    /* If any module is running need to disable */

    if( retVal == SCI_SUCCESS)
    {
        if (SCI_MOD_ENABLED == (*pphandle)->mod_state)
        {
            sci_global_disable(*pphandle);
        }

        /* Remove any active use cases.
        * Note - no error handling on call to sci_remove_usecase because
        * we should only be able to add valid usecase pointers to the
        * link list.
        */
        while ( NULL != (*pphandle)->pusecase_head)
        {
            sci_usecase_key *pusecase_key = (*pphandle)->pusecase_head;
            sci_remove_usecase (*pphandle, pusecase_key);
        }

        /*Disable and release ownership of modules */
        for ( i=0; i < mod_cnt; i++ )
        {

            if ((NULL != mod_map[i].vbase_addr) && ( true == mod_map[i].owner ))
            {
                switch (sc_map[i]->mod_type){
                case SDRAM:
                    {
                     /*
                     * MISRA.CAST.PTR
                     * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                     * and a different pointer to object type
                     * KW State: Defer -> Waiver -> Case by case
                     */
                        sc_sdram_regs * sc_regs;
                        sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;
                        sc_regs->en = 0;
                        sc_regs->dump_collecttime = 0;
                        break;
                    }
                case MSTR:
                    {
                        sc_lat_regs * sc_regs;
                        sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;
                        sc_regs->en = 0;
                        sc_regs->dump_collecttime = 0;
                        break;
                    }
                default:
                    break;
                }/* end of switch */
            }/* end of if */
        }/* end of for */

        /* unmap each non-null mod_map[i]->vbase_addr */
        for ( i=0; i < mod_cnt; i++ )
        {
            if ( NULL != mod_map[i].vbase_addr )
            {
                cTools_memUnMap(mod_map[i].vbase_addr, sc_map[i]->mod_size);
                mod_map[i].vbase_addr = NULL;
            }
        }
        *pphandle = NULL;
    }
    if (SCI_SUCCESS == retVal)
    {
        gSCI_isOpen = 0;
    }
    return retVal;
}

sci_err_t sci_get_version(psci_handle const phandle,
                              uint32_t * const plib_major_ver,
                              uint32_t * const plib_minor_ver,
                              uint32_t * const plib_func_id,
                              uint32_t * const pmod_func_id )
{
    uint32_t i;
    uint32_t tmp_cnt;
    uint32_t pmod_type_id;
    sci_err_t retVal = SCI_SUCCESS;

    pmod_type_id = 0U;

    /* Note that this function can be called with a NULL handle since
     * in this case the handle is used only for error handling
     */

    * plib_major_ver = SCILIB_MAJOR_VERSION;
    * plib_minor_ver = SCILIB_MINOR_VERSION;
    * plib_func_id = SC_LIB_FUNC;


    /* We are making the assumption that for a device all the
     * SC modules are at least the same func and revision level.
     */

    /* Find the first module that is mapped */
    tmp_cnt = 0;
    for ( i=0; i < mod_cnt; i++ )
    {
        if ( NULL != mod_map[i].vbase_addr )
        {
            switch (sc_map[i]->mod_type)
            {
                case SDRAM:
                {
                 /*
                 * MISRA.CAST.PTR
                 * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                 * and a different pointer to object type
                 * KW State: Defer -> Waiver -> Case by case
                 */
                    sc_sdram_regs * sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;
                    /* Request ownership */
                    pmod_type_id = *(volatile uint32_t *)(&sc_regs->stdhosthdr_core);
                    *pmod_func_id = GET_SCMOD_FUNC(*(volatile uint32_t *)(&sc_regs->stdhosthdr_version));
                    break;
                }
                case MSTR:
                {
                    sc_lat_regs * sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;
                    /* Request ownership */
                    pmod_type_id = *(volatile uint32_t *)(&sc_regs->stdhosthdr_core);
                    *pmod_func_id = GET_SCMOD_FUNC(*(volatile uint32_t *)(&sc_regs->stdhosthdr_version));
                    break;
                }
                default:
                    break;
            }

            /* since we found a valid module can break out of for loop */
            tmp_cnt++;
            break;
        }
     }

     if ( 0U == tmp_cnt )
     {
        retVal = SCI_ERR_ACCESS;
     }
     else
     {
        if (*plib_func_id != *pmod_func_id)
        {
            retVal = SCI_ERR_REVISION;
        }
        if ( pmod_type_id != SC_MOD_TYPE )
        {
            retVal = SCI_ERR_REVISION;
        }
     }

     if ((SCI_SUCCESS != retVal) && (NULL != phandle)
        && (NULL != phandle->psci_callback))
        {
            phandle->psci_callback(phandle, __FUNCTION__, retVal);
        }
     return retVal;
}

sci_err_t sci_reg_usecase_sdram(psci_handle const phandle,
                        struct sci_config_sdram *  const pcfg,
                        sci_usecase_key * pusecase_key )
{
    int32_t i,j,k;
    uint32_t cntr_assigned[2];        /* free counter assigned     */
    uint32_t mod;
    int32_t num_filters = 1;
    struct usecase_parms uc_parms;
    sc_sdram_regs * sc_regs = NULL; /* SC register pointer            */
    struct sdram_filter_element filter[2];
#ifdef _SC_VER_1_16
    uint32_t phy_addr_min, phy_addr_max;   /* for System to Physical address conversion */
#endif
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        if ((NULL == pusecase_key) || ( NULL == pcfg ))
        {
            retVal =  SCI_ERR_INVALID_PARM;
        }
        else
        {
            if (SCI_MOD_ENABLED == phandle->mod_state)
            {
                retVal = SCI_ERR_MODULE_ENABLED;
            }
            else
            {
                if ((( SCI_SDRAM_LINKOCCUPY_REQUEST == pcfg->usecase)
                    || ( SCI_SDRAM_LINKOCCUPY_RESPONSE == pcfg->usecase))
                    && ( 0 != pcfg->num_filters ))
                {
                    retVal = SCI_ERR_FILTER_NOT_ALLOWED;
                }
                else
                {
                    get_usecase_params( pcfg->usecase, &uc_parms);

                    if (get_cntr(SDRAM, pcfg->probe_id, pcfg->usecase, pcfg->num_filters,
                                uc_parms.num_cntr_req, &mod, cntr_assigned))
                    {
                        retVal = SCI_ERR_SC_NOT_AVAILABLE;
                    }
                    else
                    {
                        retVal = SCI_SUCCESS;
                    }
                }
            }
        }

        if ( SCI_SUCCESS != retVal )
        {
            if (NULL != phandle->psci_callback)
            {
                phandle->psci_callback(phandle, __FUNCTION__, retVal);
            }
        }
        else
        {
            /* Note - no more errors possible after this point */

            (pusecase_key)->module_index = mod;
            (pusecase_key)->num_counters = uc_parms.num_cntr_req;
            (pusecase_key)->counter_index[0] = cntr_assigned[0];
            (pusecase_key)->counter_index[1] = cntr_assigned[1];
            (pusecase_key)->usecase = pcfg->usecase;

            /* put usecase key in the handle's link list */
            put_uckey(phandle, pusecase_key);

            /* If the number of filters requested by the user is zero
            * then setup the default values
            */
            if (0 == pcfg->num_filters)
            {
                filter[0].en = 1;
                filter[0].mask_mstaddr = 0;     /* Don't care - exclude from match */
                filter[0].mask_rd = 0;          /* Enable all reads */
                filter[0].mask_wr = 0;          /* Enable all writes */
                filter[0].mask_err = 0;         /* no errors */
                filter[0].mask_userinfo = 0;    /* Don't care - exclude from match */
                filter[0].match_mstaddr = 0;
                filter[0].match_rd = 0;
                filter[0].match_wr = 0;
                filter[0].match_err = 0;
                filter[0].match_userinfo = 0;
                filter[1].en = 0;

                pcfg->filter[0].trans_qaul = SCI_RD_OR_WR_DONTCARE;
            }
            else
            {
                num_filters = pcfg->num_filters;
                for ( i= 0; i< pcfg->num_filters; i++)
                {
#ifdef _ES1
                    filter[i].match_mstaddr = pcfg->filter[i].mstr_addr_match >>2;
#else
                    filter[i].match_mstaddr = pcfg->filter[i].mstr_addr_match;
#endif
                    if ( SCI_MASTID_ALL == pcfg->filter[i].mstr_addr_match)
                    {
                        filter[i].mask_mstaddr = 0;
                    }
                    else
                    {
                        filter[i].mask_mstaddr = pcfg->filter[i].mstr_addr_mask;
                    }

                    switch (pcfg->filter[i].trans_qaul)
                    {
                        case SCI_RD_ONLY:
                            filter[i].mask_rd = 1;
                            filter[i].mask_wr = 1;
                            filter[i].match_rd = 1;
                            filter[i].match_wr = 0;
                            break;
                        case SCI_WR_ONLY:
                            filter[i].mask_rd = 1;
                            filter[i].mask_wr = 1;
                            filter[i].match_rd = 0;
                            filter[i].match_wr = 1;
                            break;
                        case SCI_RD_OR_WR_NONE:
                            filter[i].mask_rd = 1;
                            filter[i].mask_wr = 1;
                            filter[i].match_rd = 0;
                            filter[i].match_wr = 0;
                            break;
                        case SCI_RD_OR_WR_DONTCARE:
                            filter[i].mask_rd = 0;
                            filter[i].mask_wr = 0;
                            filter[i].match_rd = 0;
                            filter[i].match_wr = 0;
                            break;
                        default:
                            break;
                    }

                    switch (pcfg->filter[i].error_qual )
                    {
                        case SCI_ERR_ONLY:
                            filter[i].mask_err = 1;
                            filter[i].match_err = 1;
                            break;
                        case SCI_ERR_NONE:
                            filter[i].mask_err = 1;
                            filter[i].match_err = 0;
                            break;
                        case SCI_ERR_DONTCARE:
                            filter[i].mask_err = 0;
                            filter[i].match_err = 0;
                            break;
                        default:
                            break;
                    }

                    /* Set userinfo to don't care */
                    filter[i].mask_userinfo = 0;
                    filter[i].match_userinfo = 0;

                    /* All done so enable the filter last */
                    filter[i].en = 1;
                }
            }

#ifdef _STM_Logging
    /* Setup the meta data */
    int master_index = 0;

    for (master_index = 0; master_index < sizeof(sci_master_addr_table); master_index++) {
        if (filter[0].match_mstaddr == sci_master_addr_table[master_index]) {
            break;
        }
    }

    if (master_index == sizeof(sci_master_addr_table)) {
        return SCI_ERR_INVALID_PARM;
    }
    get_meta_data(phandle, *pusecase_key,
                  sci_sdram_probe_name_table[pcfg->probe_id],
                  trans_type_table[pcfg->filter[0].trans_qaul],
                  sci_master_name_table[master_index],
                  filter[0].mask_mstaddr );
#endif
            /* Mark the counters used */
            for ( j= 0; j < uc_parms.num_cntr_req; j++ )
            {
            /*
            * MISRA.PTR.ARITH
            * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
            * Pointer is used in arithmetic or array index expression
            * KW State: Defer -> Waiver -> Case by case
            */
                mod_map[mod].used[cntr_assigned[j]] = (bool)true;
            }

            /* Set the use case */
            mod_map[mod].usecase = pcfg->usecase;
            mod_map[mod].usecase_cnt++;

            /* Program the sc module for the use case */
           /*
            * MISRA.CAST.PTR
            * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
            * and a different pointer to object type
            * KW State: Defer -> Waiver -> Case by case
            */
            sc_regs = (sc_sdram_regs *)mod_map[mod].vbase_addr;

            if ( phandle->trigger_enable )
            {
                sc_regs->trigen = 1;
            }
            else
            {
                sc_regs->trigen = 0;
            }
            sc_regs->reqevt = uc_parms.reqevt;
            sc_regs->rspevt = uc_parms.rspevt;
#ifdef _SC_VER_1_16
            sc_regs->ignore_suspend = 0;
#endif
            for ( j = 0; j < uc_parms.num_cntr_req; j++)
            {

                const sc_probe_element_t * sdram_probe_map = sc_map[mod]->probe_map;
                int32_t sdram_probe_map_elmcnt = sc_map[mod]->num_probes;

                int32_t probe_index;
                for ( probe_index = 0; probe_index < sdram_probe_map_elmcnt; probe_index++)
                {
                    if ( pcfg->probe_id == sdram_probe_map[probe_index].probe_id)
                    {
                        break;
                    }
                }

                int32_t port = (uc_parms.port_type) ? sdram_probe_map[probe_index].rsp_port_num
                                                    : sdram_probe_map[probe_index].req_port_num;

                if (port ==  -(int32_t)1)
                {
                    retVal = SCI_ERR_INVALID_PARM;
                }
                else
                {
                    sc_regs->evtmux_sel[cntr_assigned[j]] = (uint32_t)port;
                }

            }
            if(retVal == SCI_SUCCESS)
            {
                /* Program the filters
                * Note that if two counters are needed for the use case, the filters of
                * both counters are set identically
                */
                for ( j=0; j < uc_parms.num_cntr_req; j++ )
                {
                    for ( k=0; k < num_filters; k++ )
                    {
                        struct sdram_filter_element * sc_reg_filter = get_filter_addr(mod, cntr_assigned[j],k);
                        if (NULL != sc_reg_filter)
                        {
                            *sc_reg_filter = filter[k];
                        }
                    }
                }

#ifdef _SC_VER_1_16
                /* If address filter enabled convert system address to physical address */
                if (true == pcfg->addr_filter_enable)
                {
                    retVal = sys_to_phys_addr(phandle, pcfg->addr_filter_min, &phy_addr_min);
                    if (SCI_SUCCESS == retVal)
                    {
                        retVal = sys_to_phys_addr(phandle, pcfg->addr_filter_max, &phy_addr_max);
                    }
                }
#endif
                if(retVal == SCI_SUCCESS)
                {
                    /*Program the counter */
                    for ( k=0; k < uc_parms.num_cntr_req; k++ )
                    {
                        num_filters =  sc_map[mod]->cnt_map[cntr_assigned[k]].num_filters;
                        if (2 == num_filters)
                        {
                            struct sc_sdram_cnt_filter2 * sc_cnt_addr =  (struct sc_sdram_cnt_filter2 *)get_cntr_addr( mod, cntr_assigned[k]);
                            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
                            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
                            sc_cnt_addr->globalen = 1;
#ifdef _SC_VER_1_16
                            if (true == pcfg->addr_filter_enable)
                            {
                                sc_cnt_addr->addren = 1;
                                sc_cnt_addr->addrmax= phy_addr_max >> 12;
                                sc_cnt_addr->addrmin= phy_addr_min >> 12;
                            }
                            else
                            {
                                sc_cnt_addr->addren = 0;
                                sc_cnt_addr->addrmax= 0;
                                sc_cnt_addr->addrmin= 0;
                            }
#endif
                        }
                        if (1 == num_filters)
                        {
                            struct sc_sdram_cnt_filter1 * sc_cnt_addr =  (struct sc_sdram_cnt_filter1 *)get_cntr_addr( mod, cntr_assigned[k]);
                            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
                            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
                            sc_cnt_addr->globalen = 1;
#ifdef _SC_VER_1_16
                            if (true == pcfg->addr_filter_enable)
                            {
                                sc_cnt_addr->addren = 1;
                                sc_cnt_addr->addrmax= phy_addr_max >> 12;
                                sc_cnt_addr->addrmin= phy_addr_min >> 12;
                            }
                            else
                            {
                                sc_cnt_addr->addren = 0;
                                sc_cnt_addr->addrmax= 0;
                                sc_cnt_addr->addrmin= 0;
                            }
#endif
                        }
                        if (0 == num_filters)
                        {
                            struct sc_sdram_cnt_filter0 * sc_cnt_addr =  (struct sc_sdram_cnt_filter0 *)get_cntr_addr( mod, cntr_assigned[k]);
                            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
                            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
                            sc_cnt_addr->globalen = 1;
#ifdef _SC_VER_1_16
                            if (true == pcfg->addr_filter_enable)
                            {
                                sc_cnt_addr->addren = 1;
                                sc_cnt_addr->addrmax= phy_addr_max >> 12;
                                sc_cnt_addr->addrmin= phy_addr_min >> 12;
                            }
                            else
                            {
                                sc_cnt_addr->addren = 0;
                                sc_cnt_addr->addrmax= 0;
                                sc_cnt_addr->addrmin= 0;
                            }
#endif
                        }
                    }
                }
            }
        }
    }
    return retVal;
}

sci_err_t sci_reg_usecase_mstr(psci_handle const phandle,
                        struct sci_config_mstr *  const pcfg,
                        sci_usecase_key * usecase_key )
{
    int32_t j,k;
    uint32_t cntr_assigned[2];        /* free counter assigned          */
    uint32_t mod;
    int32_t num_filters = 1;
    struct usecase_parms uc_parms;
    sc_lat_regs * sc_regs = NULL; /* SC register pointer            */
    struct lat_filter_element filter;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if( retVal == SCI_SUCCESS)
    {
        if ((NULL == usecase_key) || ( NULL == pcfg ))
        {
            retVal =  SCI_ERR_INVALID_PARM;
        }
        else
        {
            if (SCI_MOD_ENABLED == phandle->mod_state)
            {
                retVal = SCI_ERR_MODULE_ENABLED;
            }
            else
            {
                if (   (( SCI_MSTR_LINKOCCUPY_REQUEST == pcfg->usecase)
                    || ( SCI_MSTR_LINKOCCUPY_RESPONSE == pcfg->usecase))
                    && ( 0 != pcfg->num_filters ))
                {
                    retVal = SCI_ERR_FILTER_NOT_ALLOWED;
                }
                else
                {
                    get_usecase_params( pcfg->usecase, &uc_parms);

                    if (get_cntr(MSTR, pcfg->probe_id, pcfg->usecase, pcfg->num_filters,
                                uc_parms.num_cntr_req, &mod,  cntr_assigned))
                    {
                        retVal = SCI_ERR_SC_NOT_AVAILABLE;
                    }
                    else
                    {
                        retVal = SCI_SUCCESS;
                    }
                }
            }
        }

        if ( SCI_SUCCESS != retVal )
        {
            if (NULL != phandle->psci_callback)
            {
                phandle->psci_callback(phandle, __FUNCTION__, retVal);
            }
        }
        else
        {
            /* Note - no more errors possible after this point */

            /* Generate and initialize the usecase key */
            (usecase_key)->module_index = mod;
            (usecase_key)->num_counters = uc_parms.num_cntr_req;
            (usecase_key)->counter_index[0] = cntr_assigned[0];
            (usecase_key)->counter_index[1] = cntr_assigned[1];
            (usecase_key)->usecase = pcfg->usecase;

            /* put usecase key in the handle's link list */
            put_uckey(phandle, usecase_key);

            /* If the number of filters requested by the user is zero
            * then setup the default values
            */
            if (0 == pcfg->num_filters)
            {
                filter.en = 1;
                filter.mask_mstaddr = 0;     /* Don't care - exclude from match */
                filter.mask_rd = 0;          /* Enable all reads */
                filter.mask_wr = 0;          /* Enable all writes */
                filter.mask_err = 0;         /* Enable all errors */
                filter.mask_slvaddr = 0;
                filter.mask_requserinfo = 0;
                filter.mask_rspuserinfo = 0;
                filter.match_mstaddr = 0;
                filter.match_rd = 0;
                filter.match_wr = 0;
                filter.match_err = 0;
                filter.match_slvaddr = 0;
                filter.match_requserinfo = 0;
                filter.match_rspuserinfo = 0;

                pcfg->filter.trans_qaul = SCI_RD_OR_WR_DONTCARE;

            }
            else
            {
                /* Only one filter */
#ifdef LAT_SC_HAS_SLAVE_PROBES
                filter.match_mstaddr = pcfg->filter.mstr_addr_match;
                if ( SCI_MASTID_ALL == pcfg->filter.mstr_addr_match)
                {
                    filter.mask_mstaddr = 0;
                }
                else
                {
                    filter.mask_mstaddr = pcfg->filter.mstr_addr_mask;
                }
#else
                filter.match_mstaddr = 0;
                filter.mask_mstaddr = 0;
#endif
                filter.mask_requserinfo = 0;
                filter.mask_rspuserinfo = 0;
                filter.match_requserinfo = 0;
                filter.match_rspuserinfo = 0;

                filter.match_slvaddr = pcfg->filter.slave_addr_match;
                if ( SCI_SLVID_ALL == pcfg->filter.slave_addr_match)
                {
                    filter.mask_slvaddr = 0;
                }
                else
                {
                    filter.mask_slvaddr = pcfg->filter.slave_addr_mask;
                }
                switch (pcfg->filter.trans_qaul)
                {
                    case SCI_RD_ONLY:
                        filter.mask_rd = 1;
                        filter.mask_wr = 1;
                        filter.match_rd = 1;
                        filter.match_wr = 0;
                        break;
                    case SCI_WR_ONLY:
                        filter.mask_rd = 1;
                        filter.mask_wr = 1;
                        filter.match_rd = 0;
                        filter.match_wr = 1;
                        break;
                    case SCI_RD_OR_WR_NONE:
                        filter.mask_rd = 1;
                        filter.mask_wr = 1;
                        filter.match_rd = 0;
                        filter.match_wr = 0;
                        break;
                    case SCI_RD_OR_WR_DONTCARE:
                        filter.mask_rd = 0;
                        filter.mask_wr = 0;
                        filter.match_rd = 0;
                        filter.match_wr = 0;
                        break;
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                }

                switch (pcfg->filter.error_qual )
                {
                    case SCI_ERR_ONLY:
                        filter.mask_err = 1;
                        filter.match_err = 1;
                        break;
                    case SCI_ERR_NONE:
                        filter.mask_err = 1;
                        filter.match_err = 0;
                        break;
                    case SCI_ERR_DONTCARE:
                        filter.mask_err = 0;
                        filter.match_err = 0;
                        break;
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                }
                if(retVal == SCI_SUCCESS)
                {
                /* All done so enable the filter last */
                    filter.en = 1;
                }
#ifdef _STM_Logging
    /* Setup the meta data */
    int slave_index = 0;

    for (slave_index = 0; slave_index < sizeof(sci_slave_addr_table); slave_index++) {
        if (filter.match_slvaddr == sci_slave_addr_table[slave_index]) {
            break;
        }
    }

    if (slave_index == sizeof(sci_slave_addr_table)) {
        return SCI_ERR_INVALID_PARM;
    }

    get_meta_data(phandle, *pusecase_key,
                  sci_mstr_probe_name_table[pcfg->probe_id],
                  trans_type_table[pcfg->filter.trans_qaul],
                  sci_slave_name_table[slave_index],
                  filter.mask_mstaddr );
#endif
            }

            if(retVal == SCI_SUCCESS)
            {
                /* Mark the counters used */
                for ( j= 0; j < uc_parms.num_cntr_req; j++ )
                {
                   /*
                    * MISRA.PTR.ARITH * MISRAC_2004 Rule_17.1 MISRAC_2004 Rule_17.4:
                    * Pointer is used in arithmetic or array index expression
                    * KW State: Defer -> Waiver -> Case by case
                    */
                    mod_map[mod].used[cntr_assigned[j]] = (bool)true;
                }

                /* Set the use case */
                mod_map[mod].usecase = pcfg->usecase;
                mod_map[mod].usecase_cnt++;

                /* Program the sc module for the use case */
                sc_regs = (sc_lat_regs *)mod_map[mod].vbase_addr;
                /*
                 * MISRA.CAST.PTR
                 * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                 * and a different pointer to object type
                 * KW State: Defer -> Waiver -> Case by case
                 */

                if ( phandle->trigger_enable )
                {
                    sc_regs->trigen = 1;
                }
                else
                {
                    sc_regs->trigen = 0;
                }
                sc_regs->reqevt = uc_parms.reqevt;
                sc_regs->rspevt = uc_parms.rspevt;
#ifdef _SC_VER_1_16
                sc_regs->ignore_suspend = 0;
#endif
                for ( j = 0; j < uc_parms.num_cntr_req; j++)
                {

                    const sc_probe_element_t * lat_probe_map = sc_map[mod]->probe_map;
                    uint32_t lat_probe_map_elmcnt = sc_map[mod]->num_probes;

                    uint32_t probe_index = 0U;
                    do
                    {
                        if ( pcfg->probe_id == lat_probe_map[probe_index].probe_id)
                        {
                            break;
                        }
                        probe_index++;
                    }while(probe_index < lat_probe_map_elmcnt);

                    int32_t port = (uc_parms.port_type) ? lat_probe_map[probe_index].rsp_port_num
                                                    : lat_probe_map[probe_index].req_port_num;

                    if (port ==  -(int32_t)1)
                    {
                        retVal = SCI_ERR_INVALID_PARM;
                    }
                    else
                    {
                        sc_regs->evtmux_sel[cntr_assigned[j]] = (uint32_t)port;
                    }
                }

                /* Program the filters
                * Note that if two counters are needed for the use case, the filters of
                * both counters are set identically
                */
                if(retVal == SCI_SUCCESS)
                {
                    for ( j=0; j < uc_parms.num_cntr_req; j++ )
                    {
                        for ( k=0; k < num_filters; k++ )
                        {
                            struct lat_filter_element * sc_reg_filter = get_filter_addr(mod, cntr_assigned[j],k);
                            if (NULL != sc_reg_filter)
                            {
                                *sc_reg_filter = filter;
                            }
                        }
                    }

                    /*Program the counter */
                    for ( k=0; k < uc_parms.num_cntr_req; k++ )
                    {
                        if (1 == sc_map[mod]->cnt_map[cntr_assigned[k]].num_filters)
                        {
                            struct sc_lat_cnt_filter1 * sc_cnt_addr =
                                            (struct sc_lat_cnt_filter1 *)get_cntr_addr(
                                            mod, cntr_assigned[k]);
                            sc_cnt_addr->op_sel = uc_parms.op_sel[k];
                            sc_cnt_addr->op_evt_info_sel = uc_parms.evt_info_sel[k];
                            sc_cnt_addr->globalen = 1;
                        }
                    }
                }
            }
        }
    }
    return retVal;
}

sci_err_t sci_remove_usecase (psci_handle const phandle, const sci_usecase_key * usecase_key)
{

    uint32_t i;
    uint32_t mod;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        if (NULL == usecase_key)
        {
            retVal = SCI_ERR_INVALID_PARM;
        }
        else if (SCI_MOD_ENABLED == phandle->mod_state)
        {
            retVal = SCI_ERR_MODULE_ENABLED;
        }
        else
        {
            retVal = SCI_SUCCESS;
        }

        if ( SCI_SUCCESS != retVal )
        {
            if (NULL != phandle->psci_callback)
            {
                phandle->psci_callback(phandle, __FUNCTION__, retVal);
            }
        }
        else
        {
            /* Can't set mod value until after parameter checks */
            mod = (usecase_key)->module_index;

            /* Mark the counters not used */
            for ( i= 0; i < (usecase_key)->num_counters; i++ )
            {
           /*
            * MISRA.PTR.ARITH
            * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
            * Pointer is used in arithmetic or array index expression
            * KW State: Defer -> Waiver -> Case by case
            */
                mod_map[mod].used[(usecase_key)->counter_index[i]] = (bool)false;
            }

            /*Disable each counter used */
            for ( i = 0; i < (usecase_key)->num_counters; i++ )
            {
                switch (sc_map[mod]->mod_type)
                {
                    case SDRAM:
                    {
                        int32_t k;
                        int32_t num_filters = sc_map[mod]->cnt_map[(usecase_key)->counter_index[i]].num_filters;
                        if (2 == num_filters)
                        {
                            struct sc_sdram_cnt_filter2 * sc_cnt_addr =
                                                (struct sc_sdram_cnt_filter2 *)get_cntr_addr(
                                                    mod, (usecase_key)->counter_index[i]);
                            sc_cnt_addr->globalen = 0;

                        }
                        if (1 == num_filters)
                        {
                            struct sc_sdram_cnt_filter1 * sc_cnt_addr =
                                                (struct sc_sdram_cnt_filter1 *)get_cntr_addr(
                                                    mod, (usecase_key)->counter_index[i]);
                            sc_cnt_addr->globalen = 0;

                        }
                        if (0 == num_filters)
                        {
                            struct sc_sdram_cnt_filter0 * sc_cnt_addr =
                                                (struct sc_sdram_cnt_filter0 *)get_cntr_addr(
                                                    mod, (usecase_key)->counter_index[i]);
                            sc_cnt_addr->globalen = 0;
                        }

                        /* disable all filters for the counter(s) used */
                        for (k=0; k < num_filters; k++)
                        {
                            struct sdram_filter_element * filter =
                                                (struct sdram_filter_element *)get_filter_addr(
                                                    mod, (usecase_key)->counter_index[i], k);
                            if (NULL != filter)
                            {
                                filter->en = 0;
                            }
                        }
                        break;
                    }
                    case MSTR:
                    {
                        struct sc_lat_cnt_filter1 * sc_cnt_addr =
                                                    (struct sc_lat_cnt_filter1 *)get_cntr_addr(
                                                        mod, (usecase_key)->counter_index[i]);
                        struct sdram_filter_element * filter =
                                                    (struct sdram_filter_element *)get_filter_addr(
                                                        mod, (usecase_key)->counter_index[i], 0);
                        if (NULL != filter)
                        {
                            sc_cnt_addr->globalen = 0;
                            filter->en = 0;
                        }
                        break;
                    }
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                }
            }

            /* Unlink the usecase from the link list */
            if ( (usecase_key) == phandle->pusecase_head)
            {
                phandle->pusecase_head = (usecase_key)->next;
            }
            else
            {
                ((usecase_key)->prev)->next = (usecase_key)->next;
                ((usecase_key)->next)->prev = (usecase_key)->prev;
            }

            /* If this is the last use case using the module, free it for a new use case */
            mod_map[mod].usecase_cnt--;
            if (0 == mod_map[mod].usecase_cnt)
            {
                    mod_map[mod].usecase =  -(int32_t)1;
            }
        }
        /* free the usecase buf and set the clients copy to NULL */
#ifdef _STM_Logging
        cTools_memFree((usecase_key)->pmeta_data_buf);
#endif
    }
    return retVal;
}

sci_err_t sci_global_enable(psci_handle const phandle)
{
    uint32_t i;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        /* If the module's usecase count is > 0 then enable the module*/
        for ( i=0; i < mod_cnt; i++ )
        {
            if ( 0 < mod_map[i].usecase_cnt )
            {
                switch (sc_map[i]->mod_type)
                {
                /*
                 * MISRA.CAST.PTR
                 * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                 * and a different pointer to object type
                 * KW State: Defer -> Waiver -> Case by case
                 */
                    case SDRAM:
                    {
                        sc_sdram_regs * sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;
                        sc_regs->soften = 1;
                        break;
                    }
                    case MSTR:
                    {
                        sc_lat_regs * sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;
                        sc_regs->soften = 1;
                        break;
                    }
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                } /* End of switch */
            }
        }
    }
    return retVal;
}

sci_err_t sci_global_disable(psci_handle const phandle)
{
    uint32_t i;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        /* If the module's usecase count is < 0 then disable the module */
        for ( i=0; i < mod_cnt; i++ )
        {
            if ( 0 < mod_map[i].usecase_cnt )
            {
                switch (sc_map[i]->mod_type)
                {
                 /*
                  * MISRA.CAST.PTR
                  * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                  * and a different pointer to object type
                  * KW State: Defer -> Waiver -> Case by case
                  */
                    case SDRAM:
                    {
                        sc_sdram_regs * sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;
                        sc_regs->soften = 0;
                        break;
                    }
                    case MSTR:
                    {
                        sc_lat_regs * sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;
                        sc_regs->soften = 0;
                        break;
                    }
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                } /* End of switch */
            }
        }
    }

    /* Send all meta data */
#ifdef _STM_Logging
    retVal = send_meta_data(phandle);
#endif
    if (SCI_ERR_INVALID_HANDLE != retVal)
    {
        if (NULL != phandle->psci_callback)
        {
            phandle->psci_callback(phandle, __FUNCTION__, retVal);
        }
    }

    return retVal;
}

sci_err_t sci_dump(psci_handle const phandle )
{
    uint32_t i;
    sci_err_t retVal = SCI_SUCCESS;
    /* Dump the counters for each module that has use cases enabled */
    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        for ( i=0U; i < mod_cnt; i++ )
        {
            if ( 0 != mod_map[i].usecase_cnt)
            {
                switch (sc_map[i]->mod_type)
                {
                     /*
                      * MISRA.CAST.PTR
                      * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                      * and a different pointer to object type
                      * KW State: Defer -> Waiver -> Case by case
                      */
                    case SDRAM:
                    {
                        sc_sdram_regs * sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;
                        sc_regs->dump_send = 1;
                        break;
                    }
                    case MSTR:
                    {
                        sc_lat_regs * sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;
                        sc_regs->dump_send = 1;
                        break;
                    }
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                } /* End of switch */
            }
        }
    }
    return retVal;
}

#ifdef _SC_VER_1_16
sci_err_t sci_dump_info(psci_handle const phandle, const sci_usecase_key * usecase_key, uint32_t usecase_key_num, int32_t * num_sci_cntrs)
{
    uint32_t i;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        if (NULL == usecase_key)
        {
            retVal = SCI_ERR_INVALID_PARM;
            if (NULL != phandle->psci_callback)
            {
                phandle->psci_callback(phandle, __FUNCTION__, retVal);
            }
        }

        if(retVal == SCI_SUCCESS)
        {
            *num_sci_cntrs = 0;
            for (i = 0; i < usecase_key_num; i++)
            {
                *num_sci_cntrs += usecase_key[i].num_counters;
               /*
                * MISRA.PTR.ARITH * MISRAC_2004 Rule_17.1 MISRAC_2004 Rule_17.4:
                * Pointer is used in arithmetic or array index expression
                * KW State: Defer -> Waiver -> Case by case
                */
            }
        }
    }
    return retVal;
}
sci_err_t sci_dump_cntrs(psci_handle const phandle, const sci_usecase_key * usecase_key, uint32_t usecase_key_num, uint32_t * pbuf)
{
/* Dump the counters to pbuf for the provided usecase_key */
/*
* MISRA.PTR.ARITH * MISRAC_2004 Rule_17.1 MISRAC_2004 Rule_17.4:
* Pointer is used in arithmetic or array index expression
* KW State: Defer -> Waiver -> Case by case
*/

    uint32_t i,j;
    sci_err_t retVal = SCI_SUCCESS;
    uint32_t num_sci_cntrs;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        if (NULL == usecase_key)
        {
            retVal = SCI_ERR_INVALID_PARM;
            if (NULL != phandle->psci_callback)
            {
                phandle->psci_callback(phandle, __FUNCTION__, retVal);
            }
        }

        if(retVal == SCI_SUCCESS)
        {
            for (i = 0; i < usecase_key_num; i++)
            {
                num_sci_cntrs = usecase_key[i].num_counters;
                switch (sc_map[usecase_key[i].module_index]->mod_type)
                {
                    case SDRAM:
                    {
                        sc_sdram_regs * sc_regs = (sc_sdram_regs *)mod_map[usecase_key[i].module_index].vbase_addr;

                        for (j = 0; j < num_sci_cntrs; j++)
                        {
                            *pbuf = sc_regs->dump_cnt[usecase_key[i].counter_index[j]];
                            pbuf++;
                        }
                        break;
                    }
                    case MSTR:
                    {
                        sc_lat_regs * sc_regs = (sc_lat_regs *)mod_map[usecase_key[i].module_index].vbase_addr;

                        for (j = 0; j < num_sci_cntrs; j++)
                        {
                            *pbuf = sc_regs->dump_cnt[usecase_key[i].counter_index[j]];
                            pbuf++;
                        }
                        break;
                    }
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                     /*
                      * MISRA.CAST.PTR
                      * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                      * and a different pointer to object type
                      * KW State: Defer -> Waiver -> Case by case
                      */
                } /* End of switch */
            }
        }
    }
    return retVal;
}

sci_err_t sci_dump_disable(psci_handle const phandle)
{
    uint32_t i;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        /* Disable dumping for each module that has usecases assigned */
        for ( i=0; i < mod_cnt; i++ )
        {
            if ( 0 != mod_map[i].usecase_cnt)
            {
                switch (sc_map[i]->mod_type)
                {
                    case SDRAM:
                    {
                        sc_sdram_regs * sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;
                        sc_regs->dump_disable = 1;
                        break;
                    }
                    case MSTR:
                    {
                        sc_lat_regs * sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;
                        sc_regs->dump_disable = 1;
                        break;
                    }
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                     /*
                      * MISRA.CAST.PTR
                      * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                      * and a different pointer to object type
                      * KW State: Defer -> Waiver -> Case by case
                      */
                } /* End of switch */
            }
        }
    }
    return retVal;
}

sci_err_t sci_dump_enable(psci_handle const phandle )
{
    uint32_t i;
    sci_err_t retVal = SCI_SUCCESS;

    if ( NULL == phandle )
    {
        retVal = SCI_ERR_INVALID_HANDLE;
    }

    if(retVal == SCI_SUCCESS)
    {
        /* Enable dumping for each module that has usecases assigned */
        for ( i=0; i < mod_cnt; i++ )
        {
            if ( 0 != mod_map[i].usecase_cnt)
            {
                switch (sc_map[i]->mod_type)
                {
                    case SDRAM:
                    {
                        sc_sdram_regs * sc_regs = (sc_sdram_regs *)mod_map[i].vbase_addr;
                        sc_regs->dump_disable = 0;
                        break;
                    }
                    case MSTR:
                    {
                        sc_lat_regs * sc_regs = (sc_lat_regs *)mod_map[i].vbase_addr;
                        sc_regs->dump_disable = 0;
                        break;
                    }
                    default:
                        retVal = SCI_ERR_INVALID_PARM;
                        break;
                     /*
                      * MISRA.CAST.PTR
                      * MISRAC_2004_Rule_11.4: Cast between a pointer to object type
                      * and a different pointer to object type
                      * KW State: Defer -> Waiver -> Case by case
                      */
                } /* End of switch */
            }
        }
    }
    return retVal;
}
#endif
/*
 * Internal utility functions
 *
 */

sci_err_t get_usecase_params( int32_t usecase, struct usecase_parms * pusecase_parms)
{
    sci_err_t retVal = SCI_SUCCESS;

    /* Initialize use case paramters */
    switch (usecase)
    {
        case SCI_SDRAM_THROUGHPUT:
        case SCI_MSTR_THROUGHPUT:
            pusecase_parms->num_cntr_req = 1;
            pusecase_parms->reqevt = SC_EVENT_SEL_PKT;
            pusecase_parms->rspevt = SC_EVENT_SEL_PKT;
            pusecase_parms->port_type = SC_REQUEST_PROBE;
            pusecase_parms->op_sel[0] = SC_OPSEL_EVT_INFO;
            pusecase_parms->evt_info_sel[0] = SC_EVTINFOSEL_BYTELEN;
            break;
        case SCI_SDRAM_LINKOCCUPY_REQUEST:
        case SCI_MSTR_LINKOCCUPY_REQUEST:
            pusecase_parms->num_cntr_req = 1;
            pusecase_parms->reqevt = SC_EVENT_SEL_IDLE;
            pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
            pusecase_parms->port_type = SC_REQUEST_PROBE;
            pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
            pusecase_parms->evt_info_sel[0] = 0;
            break;
        case SCI_SDRAM_LINKOCCUPY_RESPONSE:
        case SCI_MSTR_LINKOCCUPY_RESPONSE:
            pusecase_parms->num_cntr_req = 1;
            pusecase_parms->reqevt = SC_EVENT_SEL_NONE;
            pusecase_parms->rspevt = SC_EVENT_SEL_IDLE;
            pusecase_parms->port_type = SC_RESPONSE_PROBE;
            pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
            pusecase_parms->evt_info_sel[0] = 0;
            break;
        case SCI_SDRAM_AVGBURST_LENGTH:
        case SCI_MSTR_AVGBURST_LENGTH:
            pusecase_parms->num_cntr_req = 2;
            pusecase_parms->reqevt = SC_EVENT_SEL_PKT;
            pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
            pusecase_parms->port_type = SC_REQUEST_PROBE;
            pusecase_parms->op_sel[0] = SC_OPSEL_EVT_INFO;
            pusecase_parms->evt_info_sel[0] = SC_EVTINFOSEL_BYTELEN;
            pusecase_parms->op_sel[1] = SC_OPSEL_FILTER_HIT;
            pusecase_parms->evt_info_sel[1] = 0;
            break;
        case SCI_MSTR_AVGLATENCY:
            pusecase_parms->num_cntr_req = 2;
            pusecase_parms->reqevt = SC_EVENT_SEL_LATENCY;
            pusecase_parms->rspevt = SC_EVENT_SEL_LATENCY;
            pusecase_parms->port_type = SC_RESPONSE_PROBE; /* SC_REQUEST_PROBE*/
            pusecase_parms->op_sel[0] = SC_OPSEL_EVT_INFO;
            pusecase_parms->evt_info_sel[0] = SC_EVTINFOSEL_LATENCY;
            pusecase_parms->op_sel[1] = SC_OPSEL_FILTER_HIT;
            pusecase_parms->evt_info_sel[1] = 0;
            break;
#ifdef _SC_VER_1_16
        case SCI_MSTR_ARBITRATION_CONFLICT:
            pusecase_parms->num_cntr_req = 1;
            pusecase_parms->reqevt = SC_EVENT_SEL_BUSY;
            pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
            pusecase_parms->port_type = SC_REQUEST_PROBE;
            pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
            pusecase_parms->evt_info_sel[0] = 0;
            break;
        case SCI_MSTR_INITIATOR_BUSY:
            pusecase_parms->num_cntr_req = 1;
            pusecase_parms->reqevt = SC_EVENT_SEL_NONE;
            pusecase_parms->rspevt = SC_EVENT_SEL_BUSY;
            pusecase_parms->port_type = SC_RESPONSE_PROBE;
            pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
            pusecase_parms->evt_info_sel[0] = 0;
            break;
        case SCI_MSTR_TRANSACTION_UNDERFLOW:
            pusecase_parms->num_cntr_req = 1;
            pusecase_parms->reqevt =  SC_EVENT_SEL_WAIT;
            pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
            pusecase_parms->port_type = SC_REQUEST_PROBE;
            pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
            pusecase_parms->evt_info_sel[0] = 0;
            break;
#ifdef _TEST
    case SCI_MSTR_TRANSFER_CYCLES:
        pusecase_parms->num_cntr_req = 1;
        pusecase_parms->reqevt =  SC_EVENT_SEL_TRANSFER;
        pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
        pusecase_parms->port_type = SC_REQUEST_PROBE;
        pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
        pusecase_parms->evt_info_sel[0] = 0;
        break;
    case SCI_MSTR_TOTAL_CLOCKS:
        pusecase_parms->num_cntr_req = 1;
        pusecase_parms->reqevt =  SC_EVENT_SEL_ANY;
        pusecase_parms->rspevt = SC_EVENT_SEL_NONE;
        pusecase_parms->port_type = SC_REQUEST_PROBE;
        pusecase_parms->op_sel[0] = SC_OPSEL_FILTER_HIT;
        pusecase_parms->evt_info_sel[0] = 0;
#endif /* _TEST */
#endif /* _SC_VER_1_16 */
        default:
            retVal = SCI_ERR_INVALID_PARM;
            break;
    }

    return retVal;
}
/* misra not done for get_cntr */
sci_err_t get_cntr (enum sc_module_type mod_type, int32_t probe_id, int32_t usecase,
                       int32_t num_filters, int32_t num_cntr_req,
                       uint32_t * mod_index,  uint32_t * cntr_assigned)
{
    uint32_t i;
    uint32_t j;
    int32_t cntr_assigned_cnt = 0;
    int32_t probe_num =  -(int32_t)1;
    sci_err_t retVal = SCI_SUCCESS;

    /* Search for a SDRAM SC module and available counter elements */
    for ( i=0; i < mod_cnt; i++ )
    {
        if ((NULL != mod_map[i].vbase_addr)
            && (mod_type == sc_map[i]->mod_type)
            && (true == mod_map[i].owner))
        {

            /* Does the module support the probe */
            for (j=0; j < sc_map[i]->num_probes; j++)
            {
            /*
            * MISRA.PTR.ARITH
            * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
            * Pointer is used in arithmetic or array index expression
            * KW State: Defer -> Waiver -> Case by case
            */
                if (probe_id == sc_map[i]->probe_map[j].probe_id)
                {
                    probe_num = (int32_t)j;
                    break;
                }
            }
            if (  -(int32_t)1 == probe_num )
            {
                /* To Avoid Misra Waring*/
            }
            else
            {

                /* If the requested use case is not compatible
                * with the SC module's current use case, then
                * check the next module.
                */

                if ((0 != mod_map[i].usecase_cnt)
                    && (SC_GET_USECASE_COMPAT_VALUE((uint32_t)mod_map[i].usecase) != 0)
                    && (SC_GET_USECASE_COMPAT_VALUE((uint32_t)mod_map[i].usecase)
                        != SC_GET_USECASE_COMPAT_VALUE((uint32_t)usecase)))
                {
                    /* To Avoid Misra Waring*/
                }
                else
                {
                    /* Are there counters available that meet our needs?
                    * Note - this search function does not try to find the best
                    * match, just the first counter that meets the criteria.
                    */
                    for ( j=0; j< sc_map[i]->num_counters; j++ )
                    {
                        /* For no filter counter case check restricted probe  */
                        if (   (NULL != sc_map[i]->sc_no_filter_valid_probe_map )
                            && (0 == (sc_map[i]->cnt_map)[j].num_filters)
                            && (SCI_INVALID_PROBE == sc_map[i]->sc_no_filter_valid_probe_map[probe_num]))
                        {
                            cntr_assigned_cnt = 0;
                            retVal = SCI_ERR_INVALID_PARM;
                        }

                        if ((( false == mod_map[i].used[j])
                            && ( num_filters <= (sc_map[i]->cnt_map)[j].num_filters))
                            && (retVal == SCI_SUCCESS))
                        {
                            cntr_assigned[cntr_assigned_cnt] = j;
                            cntr_assigned_cnt++;
                        }
                        if ( num_cntr_req == cntr_assigned_cnt )
                        {
                            break;
                        }
                    }

                    /* If we could not find the right number release these
                    * and try another module.
                    */
                    if ( num_cntr_req  != cntr_assigned_cnt )
                    {
                        cntr_assigned_cnt = 0;
                    }
                    /* now fall through to check next module */
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    if (0 == cntr_assigned_cnt)
    {
        retVal = SCI_ERR_SC_NOT_AVAILABLE;
    }

    *mod_index = i;

    return retVal;
}

void put_uckey(psci_handle const phandle, struct sci_usecase_key_t * puc_key)
{
    /* Add the usecase struct to the link list */
    struct sci_usecase_key_t * next = phandle->pusecase_head;

    if (NULL == next)
    {
        /* First usecase in link list */
        phandle->pusecase_head = puc_key;
        puc_key->next = NULL;
        puc_key->prev = NULL;
    }
    else
    {
        /* Walk the list until we find the end */
        while ( NULL != next->next )
        {
            next = next->next;
        }
        puc_key->prev = next;
        puc_key->next = NULL;
        next->next = puc_key;
    }
}

#ifdef _STM_Logging
enum sci_err get_meta_data(psci_handle const phandle, struct sci_usecase_key_t * puc_key,
                           const char * probe_name,
                           const char * trans_type,
                           const char * master_or_slave_name,
                           uint32_t mask )
{

    int i;
    int32_t chr_cnt = 0;
    int32_t mod_id = puc_key->module_index;
    const char * cnt_name[2];
    char formula[32];
    int formula_size = sizeof(formula);
    int formula_cnt;
    const char * unit;
    uint32_t ofmask;
    int usecase_index;

    uint32_t msg_rate = ( SDRAM == sc_map[mod_id]->mod_type ) ? phandle->sdram_msg_rate
                                                              : phandle->mstr_msg_rate;

    /* Malloc enough space for the attribute string */
    puc_key->pmeta_data_buf = (char *)cTools_memAlloc(SCI_META_BUFSIZE);
    if ( NULL == puc_key->pmeta_data_buf )
    {
        return SCI_ERR_MEM_ALLOC;
    }

    chr_cnt += snprintf (puc_key->pmeta_data_buf, SCI_META_BUFSIZE,
                         "{type=SC,id=%d,name=%s,sw=%d,suppress=%d,probe=%s:%s:%s+0x%x,",
                         mod_id,
                         sci_unit_name_table[mod_id],
                         msg_rate,
                         phandle->data_options,
                         probe_name,
                         trans_type,
                         master_or_slave_name,
                         mask);

    /* This will get updated if the usecase uses a latency counter */
    ofmask = sc_map[puc_key->module_index]->cnt_overflow_load;

    switch (puc_key->usecase){
    case SCI_SDRAM_THROUGHPUT:
    case SCI_MSTR_THROUGHPUT:
#ifdef _SC_VER_1_16
    case SCI_SDRAM_THROUGHPUT_MINALARM:
    case SCI_SDRAM_THROUGHPUT_MAXALARM:
    case SCI_MSTR_THROUGHPUT_MINALARM:
    case SCI_MSTR_THROUGHPUT_MAXALARM:
#endif
        cnt_name[0] = cntr_name_payload;
        formula_cnt = snprintf(formula, formula_size, "100*(#%d/%d):2",
                               puc_key->counter_index[0],
                               msg_rate);
        unit = usecase_units_bytesperwindow;
        break;
    case SCI_SDRAM_LINKOCCUPY_REQUEST:
    case SCI_SDRAM_LINKOCCUPY_RESPONSE:
    case SCI_MSTR_LINKOCCUPY_REQUEST:
    case SCI_MSTR_LINKOCCUPY_RESPONSE:
        cnt_name[0] = cntr_name_idle;
        formula_cnt = snprintf(formula, formula_size, "100-(100*(#%d/%d)):3",
                               puc_key->counter_index[0],
                               msg_rate);
        unit = usecase_units_percent;
        break;
    case SCI_SDRAM_AVGBURST_LENGTH:
    case SCI_MSTR_AVGBURST_LENGTH:
        cnt_name[0] = cntr_name_payload;
        cnt_name[1] = cntr_name_packcnt;
        formula_cnt = snprintf(formula, formula_size, "#%d/#%d):1",
                               puc_key->counter_index[0],
                               puc_key->counter_index[1]);
        unit = usecase_units_bytesperpacket;
        break;
    case SCI_MSTR_AVGLATENCY:
#ifdef _SC_VER_1_16
    case SCI_MSTR_LATENCY_MAXALARM:
#endif
        cnt_name[0] = cntr_name_latcyc;
        cnt_name[1] = cntr_name_lattrans;
        ofmask = sc_map[puc_key->module_index]->cnt_overflow_lat;
        formula_cnt = snprintf(formula, formula_size, "#%d/#%d):9",
                               puc_key->counter_index[0],
                               puc_key->counter_index[1]);
        unit = usecase_units_cyclespertrans;
        break;
    };

#ifdef _DEBUG
    /* Only time this can occur is if this is a mstr usecase
     * that is using the sdram module - which is not possible.
     */
    if (0 == ofmask)
        return SCI_ERR_STM;
#endif

    if ( formula_size < formula_cnt )
        return SCI_ERR_STM;

    /* Add counter names */
    for (i=0; i< puc_key->num_counters; i++){
        chr_cnt += snprintf ( puc_key->pmeta_data_buf+chr_cnt, SCI_META_BUFSIZE,
                              "#%d=%s,", puc_key->counter_index[i], cnt_name[i]);
    }

    /* Add formula section */
    usecase_index = SC_USECASE_MASK(puc_key->usecase);
    chr_cnt += snprintf ( puc_key->pmeta_data_buf+chr_cnt, SCI_META_BUFSIZE,
                         "/$name=%s,formula=%s,unit=%s,ofmask=%u,$/}\n",
                         usecase_name_table[usecase_index],
                         formula,
                         unit,
                         ofmask);

    puc_key->meta_data_byte_cnt = chr_cnt;

    if ( SCI_META_BUFSIZE < chr_cnt )
    {
        return SCI_ERR_STM;
    }

    return SCI_SUCCESS;
}


enum sci_err send_meta_data(psci_handle const phandle)
{
    eSTM_STATUS stm_retval = eSTM_SUCCESS;
    enum sci_err sci_retval = SCI_SUCCESS;
    struct sci_usecase_key_t * next = phandle->pusecase_head;

#ifdef _DEBUG
    if (NULL == phandle->pusecase_head)
       return SCI_ERR_STM;
    if (NULL == phandle->pstm_handle)
       return SCI_SUCCESS;
#endif

    while (NULL != next){
        /* Export meta data */

        stm_retval = STMExport_putMeta(phandle->pstm_handle,
                                next->pmeta_data_buf,
                                next->meta_data_byte_cnt);
#if 0
        /* Export with a putMsg for debugging meta data */
        stm_retval = STMXport_putMsg(phandle->pstm_handle, 0,
                                next->pmeta_data_buf,
                                next->meta_data_byte_cnt);
#endif
        if ( eSTM_SUCCESS != stm_retval )
        {
            sci_retval = SCI_ERR_STM;
        }
        next = next->next;
    }
    return sci_retval;
}
#endif

void * get_cntr_addr( uint32_t mod, uint32_t cnt_index)
{
    uint32_t tempAddr;

   /* MISRA.CAST.INT
    * MISRAC_2004_Rule_10.3:
    * Pointer is typecasted for arithmetic operation
    */
    tempAddr = (uint32_t)mod_map[mod].vbase_addr;
    tempAddr = tempAddr + sc_map[mod]->cnt_map[cnt_index].cnt_offset;
    return (void *)(tempAddr);
    /*
    * MISRA.PTR.ARITH
    * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
    * Pointer is used in arithmetic or array index expression
    * KW State: Defer -> Waiver -> Case by case
    */
}
void * get_filter_addr ( uint32_t mod, uint32_t cnt_index, int32_t filter_index)
{
    void * retVal;
    switch (sc_map[mod]->mod_type)
    {
        case SDRAM:
        {
            /* Not that sc_sdram_cnt_filter2 and sc_sdram_cnt_filter1 are identical
            * except for the number of filter elements in the array so use the
            * largest to determine the address for all.
            */
            struct sc_sdram_cnt_filter2 * cnt_addr;
            cnt_addr = (struct sc_sdram_cnt_filter2 *)get_cntr_addr( mod, cnt_index);
            retVal = (void *)&(cnt_addr->filter[filter_index]);
        }
        break;
        case MSTR:
        {
            struct sc_lat_cnt_filter1 * cnt_addr;
            cnt_addr = (struct sc_lat_cnt_filter1 *)get_cntr_addr( mod, cnt_index);
            retVal = (void *)&(cnt_addr->filter[filter_index]);
        }
        break;
        default:
            retVal = NULL;
            break;

    }
    return retVal;
}

#if defined(_SC_VER_1_16)
sci_err_t sys_to_phys_addr(psci_handle const phandle, uint32_t sys_addr_arg, uint32_t * phys_addr_arg)
{
    int32_t i;
    uint32_t phys_addr_mask;
    uint32_t sys_addr_msb;
    sci_err_t retVal = SCI_SUCCESS;
    DMM_LISA_MAP_T reg;

    /* If filtering addresses need to map */
    if (NULL == phandle->dmm_lisa_vaddr)
    {
        phandle->dmm_lisa_vaddr = (uint32_t *)cTools_memMap(DMM_LISA_MAP_BASE, 4096U);
        if (NULL == phandle->dmm_lisa_vaddr)
        {
            retVal = SCI_ERR_MAPPING;
        }
    }

    if(retVal == SCI_SUCCESS)
    {
        i=3;
        do
        {
            uint32_t sys_addr_mask;

            reg.val = *(phandle->dmm_lisa_vaddr+i);
            /*
             * MISRA.PTR.ARITH * MISRAC_2004 Rule_17.1 MISRAC_2004 Rule_17.4:
             * Pointer is used in arithmetic or array index expression
             * KW State: Defer -> Waiver -> Case by case
             */

            /* check if we hit the good section */
            sys_addr_mask = ((uint32_t)1U <<(uint32_t) 8U) - ((uint32_t)1U << reg.field.sys_size);
            sys_addr_msb = (sys_addr_arg >> 24U) & 0x000000FFU;
            if(reg.field.sys_addr == (sys_addr_msb & sys_addr_mask))
            {
                break;
            }
            i--;
        }while(i >= 0);

        if ( i<0 )
        {
            retVal = SCI_ERR_INVALID_PARM;
        }
    }

    if(retVal == SCI_SUCCESS)
    {
        phys_addr_mask = ((uint32_t)1U << reg.field.sys_size) - (uint32_t)1U;
        phys_addr_mask <<= 24U;
        phys_addr_mask |= 0x00FFFFFFU;
        sys_addr_arg &= phys_addr_mask;

        /* if interliving is enable */
        if(reg.field.sdrc_intl != 0)
        {
            uint32_t tmp;
            /* compute lower address */
            phys_addr_mask = ((uint32_t)1U << (reg.field.sdrc_intl + (uint32_t)6U)) - (uint32_t)1U;
            *phys_addr_arg = sys_addr_arg & phys_addr_mask;

            tmp = (sys_addr_arg >> reg.field.sdrc_intl) & ~phys_addr_mask;
            *phys_addr_arg |= (tmp & (0xFFFFFFFFU >> reg.field.sdrc_intl));
        }
        else
        {
            *phys_addr_arg = sys_addr_arg;
        }

        *phys_addr_arg |= reg.field.sdrc_addr << 24U;

        retVal = SCI_SUCCESS;
    }
return retVal;
}
#endif
