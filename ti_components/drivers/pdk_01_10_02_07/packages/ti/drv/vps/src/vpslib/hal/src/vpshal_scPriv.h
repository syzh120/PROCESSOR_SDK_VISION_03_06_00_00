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
 *  \file vpshal_scPriv.h
 *
 *  \brief Private HAL Header file for SC
 *  This file defines internal data-structures and macros for SC
 *
 */

#ifndef VPSHAL_SC_PRIV_H_
#define VPSHAL_SC_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/src/vpslib/hal/vpshal_sc.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 *  enum Vps_ScConfigOvlyReg
 *  \brief Enums for the configuration overlay register offsets - used as array
 *  indices to register offset array in ScInfo object. These enums defines the
 *  registers that will be used to form the configuration register overlay for
 *  DEIH module. This in turn is used by client drivers to configure registers
 *  using VPDMA during context-switching (software channels with different
 *  configurations).
 *
 *  Note: If in future it is decided to remove or add some register, this enum
 *  should be modified accordingly. And make sure that the values of these
 *  enums are in ascending order and it starts from 0.
 */
typedef enum
{
    SC_CONFIG_OVLY_CFG_SC1_IDX = 0,
    SC_CONFIG_OVLY_CFG_SC2_IDX,
    SC_CONFIG_OVLY_CFG_SC3_IDX,
    SC_CONFIG_OVLY_CFG_SC4_IDX,
    SC_CONFIG_OVLY_CFG_SC5_IDX,
    SC_CONFIG_OVLY_CFG_SC6_IDX,
    SC_CONFIG_OVLY_CFG_SC8_IDX,
    SC_CONFIG_OVLY_CFG_SC9_IDX,
    SC_CONFIG_OVLY_CFG_SC10_IDX,
    SC_CONFIG_OVLY_CFG_SC11_IDX,
    SC_CONFIG_OVLY_CFG_SC12_IDX,
    SC_CONFIG_OVLY_CFG_SC13_IDX,
    SC_CONFIG_OVLY_CFG_SC18_IDX,
    SC_CONFIG_OVLY_CFG_SC24_IDX,
    SC_CONFIG_OVLY_CFG_SC25_IDX,
    SC_CONFIG_OVLY_CFG_SC0_IDX,
    SC_CONFIG_OVLY_NUM_IDX
    /**< This must be the last enum */
} Vps_ScConfigOvlyReg;

/* RAV related macros */
#define SC_USE_RAJITHA_METHOD
#define SC_HORZ_SCALE_SHIFT         (10U)
#define SC_VERT_RAV_INIT_MAX        (1024U)

/* PolyPhase related macros */
#define SC_ROW_ACC_INC_SHIFT        (16U)
#define SC_LINEAR_ACC_INC_SHIFT     (24U)

/* Non-linear scaling related macros */
#define SC_NONLINEAR_ACC_INC_SHIFT  (24U)

/**
 *  \brief Masks and shifts used to extract upper 3 bits of lengths for 35
 *  division
 */
#define SC_HORZ_HIGH_VALUE_MASK     (0x00000700U)
#define SC_HORZ_HIGH_VALUE_SHIFT    (8U)

/* (luma, chroma) */
#define VPSHAL_SC_HORZ_NUM_COEFF_SETS     (2U)

/* (luma, chroma) */
#define VPSHAL_SC_VERT_NUM_COEFF_SETS     (2U)

/* (luma, chroma) */
#define VPSHAL_SC_BILINEAR_NUM_COEFF_SETS (2U)

/* Horizontal (luma, chroma), Vertical (luma, chroma) */
#define VPSHAL_SC_NUM_COEFF_SETS          (VPSHAL_SC_HORZ_NUM_COEFF_SETS + \
                                           VPSHAL_SC_VERT_NUM_COEFF_SETS)

/* Horizontal (luma, chroma), Vertical (luma, chroma), Bilinear (luma, chroma)*/
#define VPSHAL_SC_HQ_NUM_COEFF_SETS        (VPSHAL_SC_HORZ_NUM_COEFF_SETS + \
                                            VPSHAL_SC_VERT_NUM_COEFF_SETS + \
                                            VPSHAL_SC_BILINEAR_NUM_COEFF_SETS)

#define VPSHAL_SC_COEFF_ALIGN              (16U)

#define VPSHAL_SC_HQ_COEFF_OVLY_SIZE       (VPS_SC_NUM_PHASES *           \
                                            VPSHAL_SC_HQ_NUM_COEFF_SETS * \
                                            VPSHAL_SC_COEFF_ALIGN)

#define VPSHAL_SC_COEFF_OVLY_SIZE          (VPS_SC_NUM_PHASES *        \
                                            VPSHAL_SC_NUM_COEFF_SETS * \
                                            VPSHAL_SC_COEFF_ALIGN)

#define VPSHAL_SC_HORZ_COEFF_OVLY_SIZE     (VPS_SC_NUM_PHASES *             \
                                            VPSHAL_SC_HORZ_NUM_COEFF_SETS * \
                                            VPSHAL_SC_COEFF_ALIGN)

#define VPSHAL_SC_VERT_COEFF_OVLY_SIZE     (VPS_SC_NUM_PHASES *             \
                                            VPSHAL_SC_VERT_NUM_COEFF_SETS * \
                                            VPSHAL_SC_COEFF_ALIGN)

#define VPSHAL_SC_BILINEAR_COEFF_OVLY_SIZE (VPS_SC_NUM_PHASES *                 \
                                            VPSHAL_SC_BILINEAR_NUM_COEFF_SETS * \
                                            VPSHAL_SC_COEFF_ALIGN)

/* Macros required while calculating #VpsHal_ScFactorConfig */
#define VPSHAL_SC_COEFF_SCALE_SHIFT        (4U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  struct VpsHal_ScInfo
 *  \brief Structure containing Instance Information for each SC Instance.
 *         Primarily baseAddress and overlay info for the SC instance.
 */
typedef struct
{
    UInt32                 halId;
    /**< Instance ID of SC */

    UInt32                 openCnt;
    /**< Number of handles opened */

    UInt32                 baseAddr;
    /**< Base address for the current SC instance. */

    VpsHal_VpdmaConfigDest coeffConfigDest;
    /**< VPDMA configuration register destination for the Scaler instance. */

    UInt32                 isHqScaler;
    /**< Type of scaler - high quality or normal quality. */

    Vps_ScCoeff           *userScCoeff;
    /**< User coefficients (if provided) */

    UInt32                 regOvlySize;
    /**< Virtual register overlay size in terms of bytes. Used to allocate
     *   memory for virtual register configured through VPDMA */

    UInt32                *regOffset[(UInt32)SC_CONFIG_OVLY_NUM_IDX];
    /**< Array of physical address of the register configured through
     *   VPDMA register overlay. */

    UInt32                 virtRegOffset[(UInt32)SC_CONFIG_OVLY_NUM_IDX];
    /**< Array of indexes into the Overlay memory where virtual registers are
     *   to be configured */
} VpsHal_ScInfo;

/**
 *  struct VpsHal_Sc
 *  \brief Handle structure for all instances of SC HAL
 */
typedef struct
{
    UInt32        numInst;
    /**< Num instances opened in HALInit */

    VpsHal_ScInfo scInfo[VPSHAL_SC_MAX_INST];
    /**< Instance list for maximum supported instances */
} VpsHal_Sc;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      static Function Declaration                           */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      static Function Definition                            */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                      Internal Function Declarations                        */
/* ========================================================================== */
/**
 *  void VpsHal_scSetRunTimeConfig
 *  \brief Function is used to set the scaling ratio and position specific
 *  parameters in the VPDMA register overlay. It will be called at the
 *  run time when scaling ratio or position is changed at the run
 *  time while display is on. This function will also be used for
 *  memory to memory driver to set the scaling parameters in register
 *  overlay. This function will only change scaling ratio specific
 *  parameters. It will not change scaling algorithm or parameters
 *  configurable in CFG_SC0 register.
 *
 *  \param handle           Scaler Handle
 *  \param memPtr           VPDMA register overlay pointer
 *  \param config           Pointer to structure containing scaler parameters.
 *                          While calling this function ensure
 *                          config->vsType != VPS_SC_VST_AUTO
 *                          config->hsType != VPS_SC_HST_AUTO
 *
 *  \return                 None
 */
void VpsHal_scSetRunTimeConfig(VpsHal_Handle       handle,
                               const Vps_ScConfig *config,
                               Ptr                 memPtr);

/**
 *  static Int32 VpsHal_scSetPeakingParams(VpsHal_ScInfo *scInfo,
 *                                          Vps_ScPeakingConfig *pParams)
 *
 *  \brief  Function to the peaking block parameters in the scaler register.
 *          Expert values for this block is set at the time of init. If
 *          required, expert user can change parameters for this block by
 *          modifying macros given for the peaking block.
 *          scInfo      must be correct pointer
 *          pParams     must be correct pointer
 *
 *  \param  scInfo      Pointer to scaler information structure
 *  \param  pParams     Pointer to structure containing peaking parameters
 *
 *  \return  0          on Success
 *          -1          on Error
 */
static Int32 VpsHal_scSetPeakingParams(const VpsHal_ScInfo       *scInfo,
                                       const Vps_ScPeakingConfig *pParams);

/**
 *  static inline void VpsHal_scCalVertPolyphaseParams(
 *                          const Vps_ScConfig *config,
 *                          UInt32 *rowAccInc,
 *                          UInt32 *offsetA,
 *                          UInt32 *offsetB)
 *
 *  \brief  Function to calculate parameters for polyphase vertical scaler. It
 *          calculates Row accumulator increment and offset value and returns
 *          them to the caller. The value returned from this function can be
 *          directly set into register
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  rowAccInc   Row Accumulator Increment Value
 *  \param  offsetA     Vertical Offset for top field or frame
 *  \param  offsetB     Vertical Offset for bottom field
 *
 *  \return None
 */
static inline void VpsHal_scCalVertPolyphaseParams(
    const Vps_ScConfig *config,
    UInt32             *rowAccInc,
    UInt32             *offsetA,
    UInt32             *offsetB);

/**
 *  static inline UInt32 VpsHal_scCalHorzLinearAccInc(
 *                                     const Vps_ScConfig *config,
 *                                     UInt32 *shift)
 *
 *  \brief  Function to calculate linear accumulator increment value and also
 *          shift required to calculate linear as well non-linear parameters.
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  shift       Returns the shift by which width and internal
 *                      width should be right shifted
 *
 *  \return             Linear Accumulator increment value
 */
static inline UInt32 VpsHal_scCalHorzLinearAccInc(const Vps_ScConfig *config,
                                                  UInt32             *shift);

/**
 *  static inline void VpsHal_scCalHorzNonLinearParams(
 *                          const Vps_ScConfig *config,
 *                          UInt32 shift,
 *                          Int32 *initValue,
 *                          Int32 *incValue)
 *
 *  \brief  Function to calculate non-linear accumulator initial and
 *          increment value. It uses shift returned from scCalHorzLinearAccInc
 *          function and calculates parameters.
 *          scCalHorzLinearAccInc function must be called before calling
 *          this function in order to get value of shift                *
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  shift       As per the equation, width and inner width are
 *                      right shifted by this value
 *  \param  initValue   Row Accumulator initial value
 *  \param  incValue    Row Accumulator increment value
 *
 *  \return None
 */
static inline void VpsHal_scCalHorzNonLinearParams(
    const Vps_ScConfig *config,
    UInt32              shift,
    Int32              *initValue,
    Int32              *incValue);

/**
 *  static inline void VpsHal_scCalVertRavParams(const Vps_ScAdvConfig *config,
 *                                                UInt32 *factor,
 *                                                UInt32 *ravInit)
 *
 *  \brief  Function to calculate parameters for running average scaler. It
 *          calculates scaling factor and row accumulator initial value and
 *          returns them to the caller. The value returned from this function
 *          can be directly set into register.
 *
 *  \param  config      pointers to structure containing source and
 *                      target size
 *  \param  factor      Vertical Scaling factor
 *  \param  ravInit     Row Accumulator initial value
 *
 *  \return None
 */
static inline void VpsHal_scCalVertRavParams(const Vps_ScAdvConfig *advCfg,
                                             UInt32                *factor,
                                             UInt32                *ravInit);
/**
 *  static inline UInt32 VpsHal_scMakeScCfg4Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get Target image size in 32 bit
 *          value. Value returned from this function can be directly set into
 *          the register.
 *
 *  \param  config      pointers to structure containing source
 *
 *  \return             target image size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg4Reg(const Vps_ScAdvConfig *advCfg);

/**
 *  static inline UInt32 VpsHal_scMakeScCfg5Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get cropped image size in 32 bit
 *          value. Value returned from this function can be directly set into
 *          the register.
 *
 *  \param  config     pointers to structure containing source
 *
 *  \return            cropped image size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg5Reg(const Vps_ScAdvConfig *advCfg);

/**
 *  static inline UInt32 VpsHal_scMakeScCfg8Reg(const Vps_ScConfig *config)
 *
 *  \brief  Inline Function to calculate and get left and right strip size in
 *          32 bit value. Value returned from this function can be directly
 *          set into the register.
 *
 *  \param  config   pointers to structure containing source
 *
 *  \return          strip size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg8Reg(const Vps_ScConfig *config);

/**
 *  static inline UInt32 VpsHal_scMakeScCfg24Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get the Source image size in
 *          32 bit value. Value returned from this function can be directly
 *          set into the register.
 *
 *  \param  config      pointers to structure containing source
 *
 *  \return             source image size in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg24Reg(const Vps_ScAdvConfig *advCfg);

/**
 *  static inline UInt32 VpsHal_scMakeScCfg25Reg(const Vps_ScAdvConfig *advCfg)
 *
 *  \brief  Inline Function to calculate and get offset from where to crop
 *          image in 32 bit value. Value returned from this function can be
 *          directly set into the register.
 *
 *  \param  config     pointers to structure containing source
 *
 *  \return            offset in 32 bit value
 */
static inline UInt32 VpsHal_scMakeScCfg25Reg(const Vps_ScAdvConfig *advCfg);

/**
 *  VpsHal_scLongDivide UInt32 hiValue, UInt32 loValue, UInt32 divider)
 *
 *  \brief Function is used to divide 64 bit value by 32 bit value. It is used
 *  in calculating linear as well as non-linear horizontal scaling parameters
 */
static UInt32 VpsHal_scLongDivide(UInt32 hiValue,
                                  UInt32 loValue,
                                  UInt32 divider);

/**
 *  VpsHal_scGetStdHorzCoeffOvly
 *
 *  \brief  Function to return the horizontal scaling standard coefficients
 *          as per the scaling ratio.
 *          Register Overlay Memory must be allocated by using size provided
 *          by scaler.
 *  \param  handle          Scaler Handle
 *  \param  horzCoeffMemPtr Location to return a pointer to horizontal scaling
 *                          coefficients
 *  \param  config          Scaler Parameters using which it calculates the
 *                          scaling ratio
 *
 *  \return 0               on Success
 *          -1              on Error
 */
static void VpsHal_scGetStdHorzCoeffOvly(
    VpsHal_Handle                handle,
    const VpsHal_ScFactorConfig *config,
    Ptr                         *
    horzCoeffMemPtr);

/**
 *  VpsHal_scGetStdVertCoeffOvly
 *
 *  \brief  Function to return the vertical scaling standard coefficients as per
 *          the scaling ratio.
 *          Register Overlay Memory must be allocated by using size provided
 *          by scaler.
 *  \param  handle          Scaler Handle
 *  \param  vertCoeffMemPtr Location to return a pointer to vertical scaling
 *                          coefficients
 *  \param  vertBilinearCoeffMemPtr Location to return a pointer to vertical
 *                          bilinear scaling coefficients (only if applicable,
 *                          i.e. for HQ scaler. Can be NULL otherwise).
 *  \param  config          Scaler Parameters using which it calculates the
 *                          scaling ratio
 *
 *  \return 0               on Success
 *          -1              on Error
 */
static void VpsHal_scGetStdVertCoeffOvly(
    VpsHal_Handle                handle,
    const VpsHal_ScFactorConfig *config,
    Ptr                         *vertCoeffMemPtr,
    Ptr                         *vertBilinearCoeffMemPtr);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPSHAL_SC_PRIV_H_ */
