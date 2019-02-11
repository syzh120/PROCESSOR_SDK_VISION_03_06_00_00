/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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

/**
 *  \ingroup PM_HAL PM HAL API
 *  \defgroup MISC Infrastructure and Domain List
 *
 *  - Contains macros to select module names
 *
 * @{
 */

/**
 *  \file      hw_pmhal_data_names.h
 *
 *  \brief     This file contains macros to select module names.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *              If manual changes are required the implications of the
 *              change in this and other auto generated files has to be
 *              completely understood.
 */

#ifndef HW_PMHAL_DATA_NAMES_H_
#define HW_PMHAL_DATA_NAMES_H_

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include <ti/drv/pm/include/prcm/pmhal_prcm.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

/**
 * \brief Macros for internal use
 */

/** \brief Macro to verify if enum is in Range/Valid */
#define IS_ENUM_INRANGE_(en, id) \
    (((en) ## _MIN <= (id)) && ((id) <= (en) ## _MAX))

/** \brief Macro to Calculate enum offset */
#define CALC_ENUM_OFFSET_(en, id) \
    ((IS_ENUM_INRANGE_((en), (id))) ? (id) - ((en) ## _MIN) : ((en) ## _UNDEF))

/** \brief Macro to print with name_enum */
#define NAME_(x)  (# x)

#ifdef NDEBUG
  #define GET_ENUM_NAME_(en, id) \
    "[name is only available in debug mode (NDEBUG=0)"
  #define GET_NODE_NAME_(en, id) \
    "[name is only available in debug mode (NDEBUG=0)"

#else
/* Name vector for PRCM elements */
/** \brief Macro to access names of pmhalVoltageDomain_t */
  #define VNAME_PMHAL_PRCM_VD_        (pmhalVoltageDomain_t_names)
/** \brief Macro to access names of pmhalPowerDomain_t */
  #define VNAME_PMHAL_PRCM_PD_        (pmhalPowerDomain_t_names)
/** \brief Macro to access names of pmhalClockList */
  #define VNAME_PMHAL_PRCM_CLK_       (pmhalClockList_names)
/** \brief Macro to access names of pmhalResetGroupList */
  #define VNAME_PMHAL_PRCM_RG_        (pmhalResetGroupList_names)
/** \brief Macro to access names of pmhalGlobalResetGroupList */
  #define VNAME_PMHAL_PRCM_GLB_RG_    (pmhalGlobalResetGroupList_names)
/** \brief Macro to access names of pmhalResetList */
  #define VNAME_PMHAL_PRCM_RESET_     (pmhalResetList_names)
/** \brief Macro to access names of pmhalPhysicalMemory_t */
  #define VNAME_PMHAL_PRCM_MEM_       (pmhalPhysicalMemory_t_names)
/** \brief Macro to access names of pmhalPhysicalMemoryBank_t */
  #define VNAME_PMHAL_PRCM_BANK_      (pmhalPhysicalMemoryBank_t_names)
/** \brief Macro to access names of pmhalSysConfigModuleId_t */
  #define VNAME_PMHAL_PRCM_SYSCFG_    (pmhalSysConfigModuleId_t_names)
/** \brief Macro to access names of pmhalNodeList */
  #define VNAME_PMHAL_PRCM_NODE_      (pmhalNodeList_names)
/** \brief Macro to access names of ROOT CLK pmhalNodeList */
  #define VNAME_PMHAL_PRCM_ROOT_CLK_  (VNAME_PMHAL_PRCM_NODE_)
/** \brief Macro to access names of MUX pmhalNodeList */
  #define VNAME_PMHAL_PRCM_MUX_       (VNAME_PMHAL_PRCM_NODE_)
/** \brief Macro to access names of DIV pmhalNodeList */
  #define VNAME_PMHAL_PRCM_DIV_       (VNAME_PMHAL_PRCM_NODE_)
/** \brief Macro to access names of DPLL pmhalNodeList */
  #define VNAME_PMHAL_PRCM_DPLL_      (VNAME_PMHAL_PRCM_NODE_)
/** \brief Macro to access names of MOD pmhalNodeList */
  #define VNAME_PMHAL_PRCM_MOD_       (VNAME_PMHAL_PRCM_NODE_)

/* Minimum index of vector for PRCM elements */
/** Minimum index of VD elements */
  #define VMIN_PMHAL_PRCM_VD_         (PMHAL_PRCM_VD_MIN)
/** Minimum index of PD elements */
  #define VMIN_PMHAL_PRCM_PD_         (PMHAL_PRCM_PD_MIN)
/** Minimum index of CLK elements */
  #define VMIN_PMHAL_PRCM_CLK_        (PMHAL_PRCM_CLK_MIN)
/** Minimum index of RG elements */
  #define VMIN_PMHAL_PRCM_RG_         (PMHAL_PRCM_RG_MIN)
/** Minimum index of GLB_RG elements */
  #define VMIN_PMHAL_PRCM_GLB_RG_     (PMHAL_PRCM_GLB_RG_MIN)
/** Minimum index of RESET elements */
  #define VMIN_PMHAL_PRCM_RESET_      (PMHAL_PRCM_RESET_MIN)
/** Minimum index of MEM elements */
  #define VMIN_PMHAL_PRCM_MEM_        (PMHAL_PRCM_MEM_MIN)
/** Minimum index of BANK elements */
  #define VMIN_PMHAL_PRCM_BANK_       (PMHAL_PRCM_PHY_BANK_MIN)
/** Minimum index of SYSCFG elements */
  #define VMIN_PMHAL_PRCM_SYSCFG_     (PMHAL_PRCM_SYSCFG_MIN)
/** Minimum index of NODE elements */
  #define VMIN_PMHAL_PRCM_NODE_       (PMHAL_PRCM_NODE_MIN)
/** Minimum index of ROOT_CLK elements */
  #define VMIN_PMHAL_PRCM_ROOT_CLK_   (VMIN_PMHAL_PRCM_NODE_)
/** Minimum index of MUX elements */
  #define VMIN_PMHAL_PRCM_MUX_        (VMIN_PMHAL_PRCM_NODE_)
/** Minimum index of DIV elements */
  #define VMIN_PMHAL_PRCM_DIV_        (VMIN_PMHAL_PRCM_NODE_)
/** Minimum index of DPLL elements */
  #define VMIN_PMHAL_PRCM_DPLL_       (VMIN_PMHAL_PRCM_NODE_)
/** Minimum index of MOD elements */
  #define VMIN_PMHAL_PRCM_MOD_        (VMIN_PMHAL_PRCM_NODE_)
/** \brief Macro to get enum name for given id */
  #define GET_ENUM_NAME_(en, id)          \
    (IS_ ## en ? VNAME_ ## en ## _[(id) - \
                                   VMIN_ ## en ## _] : NAME_(en ## _UNDEF))

#endif /* NDEBUG */

/*
 * \brief Macros to confirm membership of a group
 */
/** \brief Macro to confirm membership of VD group */
#define IS_PMHAL_PRCM_VD(id)          (IS_ENUM_INRANGE_(PMHAL_PRCM_VD, (id)))
/** \brief Macro to confirm membership of PD group */
#define IS_PMHAL_PRCM_PD(id)          (IS_ENUM_INRANGE_(PMHAL_PRCM_PD, (id)))
/** \brief Macro to confirm membership of CD group */
#define IS_PMHAL_PRCM_CD(id)          (IS_ENUM_INRANGE_(PMHAL_PRCM_CD, (id)))
/** \brief Macro to confirm membership of CLK group */
#define IS_PMHAL_PRCM_CLK(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_CLK, (id)))
/** \brief Macro to confirm membership of MUX group */
#define IS_PMHAL_PRCM_MUX(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_MUX, (id)))
/** \brief Macro to confirm membership of DIV group */
#define IS_PMHAL_PRCM_DIV(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_DIV, (id)))
/** \brief Macro to confirm membership of ROOT_CLK group */
#define IS_PMHAL_PRCM_ROOT_CLK(id)    (IS_ENUM_INRANGE_(PMHAL_PRCM_ROOT_CLK, \
                                                        (id)))
/** \brief Macro to confirm membership of DPLL group */
#define IS_PMHAL_PRCM_DPLL(id)        (IS_ENUM_INRANGE_(PMHAL_PRCM_DPLL, (id)))
/** \brief Macro to confirm membership of MOD group */
#define IS_PMHAL_PRCM_MOD(id)         (IS_ENUM_INRANGE_(PMHAL_PRCM_MOD, (id)))
/** \brief Macro to confirm membership of NODE group */
#define IS_PMHAL_PRCM_NODE(id) \
    (IS_ENUM_INRANGE_(PMHAL_PRCM_NODE, (id)) || IS_ENUM_INRANGE_(PMHAL_PRCM_MOD))

/*
 * \brief Macros to calculate offset within a group
 */

/** \brief Macro to calculate offset within VD group */
#define GET_PMHAL_PRCM_VD_OFFSET(id)       (CALC_ENUM_OFFSET_(PMHAL_PRCM_VD, \
                                                              (id)))
/** \brief Macro to calculate offset within PD group */
#define GET_PMHAL_PRCM_PD_OFFSET(id)       (CALC_ENUM_OFFSET_(PMHAL_PRCM_PD, \
                                                              (id)))
/** \brief Macro to calculate offset within CD group */
#define GET_PMHAL_PRCM_CD_OFFSET(id)       (CALC_ENUM_OFFSET_(PMHAL_PRCM_CD, \
                                                              (id)))
/** \brief Macro to calculate offset within CLK group */
#define GET_PMHAL_PRCM_CLK_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_CLK, \
                                                              (id)))
/** \brief Macro to calculate offset within ROOT_CLK group */
#define GET_PMHAL_PRCM_ROOT_CLK_OFFSET(id) \
    (CALC_ENUM_OFFSET_(PMHAL_PRCM_ROOT_CLK, (id)))
/** \brief Macro to calculate offset within MUX group */
#define GET_PMHAL_PRCM_MUX_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_MUX, \
                                                              (id)))
/** \brief Macro to calculate offset within DIV group */
#define GET_PMHAL_PRCM_DIV_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_DIV, \
                                                              (id)))
/** \brief Macro to calculate offset within DPLL group */
#define GET_PMHAL_PRCM_DPLL_OFFSET(id) \
    (CALC_ENUM_OFFSET_(PMHAL_PRCM_DPLL, (id)))
/** \brief Macro to calculate offset within MOD group */
#define GET_PMHAL_PRCM_MOD_OFFSET(id)      (CALC_ENUM_OFFSET_(PMHAL_PRCM_MOD, \
                                                              (id)))

/*
 * \brief Macros to determine name of the given ID.
 *        Note: Enabled only in debug mode
 */
/** \brief Macro to determine name of given id in VD */
#define PMHAL_PRCM_GET_VD_NAME(id)        (GET_ENUM_NAME_(PMHAL_PRCM_VD, (id)))
/** \brief Macro to determine name of given id in PD */
#define PMHAL_PRCM_GET_PD_NAME(id)        (GET_ENUM_NAME_(PMHAL_PRCM_PD, (id)))
/** \brief Macro to determine name of given id in CD */
#define PMHAL_PRCM_GET_CD_NAME(id)        (GET_ENUM_NAME_(PMHAL_PRCM_CD, (id)))
/** \brief Macro to determine name of given id in CLK */
#define PMHAL_PRCM_GET_CLK_NAME(id)       (GET_ENUM_NAME_(PMHAL_PRCM_CLK, (id)))
/** \brief Macro to determine name of given id in ROOT_CLK */
#define PMHAL_PRCM_GET_ROOT_CLK_NAME(id) \
    (GET_NODE_NAME_(PMHAL_PRCM_ROOT_CLK, (id)))
/** \brief Macro to determine name of given id in MUX */
#define PMHAL_PRCM_GET_MUX_NAME(id)       (GET_NODE_NAME_(PMHAL_PRCM_MUX, (id)))
/** \brief Macro to determine name of given id in DIV */
#define PMHAL_PRCM_GET_DIV_NAME(id)       (GET_NODE_NAME_(PMHAL_PRCM_DIV, (id)))
/** \brief Macro to determine name of given id in DPLL */
#define PMHAL_PRCM_GET_DPLL_NAME(id)      (GET_NODE_NAME_(PMHAL_PRCM_DPLL, (id)))
/** \brief Macro to determine name of given id in MOD */
#define PMHAL_PRCM_GET_MOD_NAME(id)       (GET_NODE_NAME_(PMHAL_PRCM_MOD, (id)))
/** \brief Macro to determine name of given id in NODE */
#define PMHAL_PRCM_GET_NODE_NAME(id)      (GET_NODE_NAME_(PMHAL_PRCM_NODE, (id)))

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/** Array of Voltage Domain Names */
extern const char *pmhalVoltageDomain_t_names[PMHAL_PRCM_VD_COUNT];
/** Array of Power Domain Names */
extern const char *pmhalPowerDomain_t_names[PMHAL_PRCM_PD_COUNT];
/** Array of Clk Domain Names */
extern const char *pmhalClkDomain_t_names[PMHAL_PRCM_CD_COUNT];
/** Array of ClockList Names */
extern const char *pmhalClockList_names[PMHAL_PRCM_CLK_GENERIC + 1U];
/** Array of ResetGroupList Names */
extern const char *pmhalResetGroupList_names[PMHAL_PRCM_RG_COUNT];
/** Array of GlobalResetGroupList Names */
extern const char *pmhalGlobalResetGroupList_names[PMHAL_PRCM_GLB_RG_COUNT];
/** Array of ResetList Names */
extern const char *pmhalResetList_names[PMHAL_PRCM_RST_COUNT];
/** Array of SysConfigModuleId Names */
extern const char *pmhalSysConfigModuleId_t_names[PMHAL_PRCM_SYSCFG_COUNT];
/** Array of PhysicalMemoryBank Names */
extern const char *pmhalPhysicalMemoryBank_t_names[PMHAL_PRCM_PHY_BANK_COUNT];
/** Array of  NodeList Names */
extern const char *pmhalNodeList_names[PMHAL_PRCM_MOD_COUNT];
/** Array of PostDivList Names */
extern const char *pmhalPostDivList_names[PMHAL_PRCM_DPLL_POST_DIV_COUNT];

#ifdef __cplusplus
}
#endif

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#endif /* HW_PMHAL_DATA_NAMES_H_ */

/* @} */


