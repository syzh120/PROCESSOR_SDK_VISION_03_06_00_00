/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated
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
 *  \ingroup CSL_IP_MODULE_OCMC
 *  \defgroup CSL_OCMC_ECC_L2 ECC L2
 *
 *  @{
 */
/**
 *  \file  ocmc_ecc_l2.h
 *
 *  \brief This module defines the OCMC HAL.
 *         This file contains the OCMC Hardware Abstraction Layer API used for
 *         low-level programming of the OCMC IP
 */

#ifndef OCMC_ECC_L2_H_
#define OCMC_ECC_L2_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define NUM_CBUFS_PER_OCMC ((uint32_t) 12U)
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_AM572x) || defined (SOC_AM574x)
#define OCMC_NUM_INSTANCE  ((uint32_t) 3U)
#else
#define OCMC_NUM_INSTANCE  ((uint32_t) 1U)
#endif
typedef uint8_t ocmc_inst_t;

/**
 * \enum ocmc_ram_controller_t
 * \brief  Enumeration that contains all possible values for ocmc ram regions
 *
 */
typedef enum
{
    e_ocmc_ram1 = 0,
    e_ocmc_ram2,
    e_ocmc_ram3
}ocmc_ram_controller_t;

/**
 * \enum ocmc_ret_type_t
 * \brief  Enumeration that contains all possible return values from OCMC HAL
 *         APIs
 *
 */
typedef enum {
    e_ocmc_null_pointer_in_argument,
    e_ocmc_not_cbuf_capable,
    e_ocmc_insufficient_cbuf_mem,
    e_ocmc_invalid_ocmc_inst,
    e_ocmc_invalid_cbuf_id,
    e_ocmc_illegal_vbuf_start_addr,
    e_ocmc_illegal_vbuf_end_addr,
    e_ocmc_illegal_vbuf_size,
    e_ocmc_vbuf_addr_not_16b_aligned,
    e_ocmc_vbuf_size_not_16b_aligned,
    e_ocmc_illegal_cbuf_start,
    e_ocmc_illegal_cbuf_size,
    e_ocmc_cbuf_addr_not_16b_aligned,
    e_ocmc_cbuf_size_not_16b_aligned,
    e_ocmc_vbuf_size_smaller_than_cbuf_size,
    e_ocmc_reminder_vbuf_mod_cbuf_is_zero,
    e_invalid_intr_group,
    e_invalid_intr_id,
    e_invalid_cbuf_err_type,
    e_ocmc_success
} ocmc_ret_type_t;

/**
 * \enum ocmc_intr_id_t
 * \brief  Enumeration that specifies all possible interrupt sources within the
 *         OCMC
 *
 */
typedef enum {
    e_ecc_sec_err_found,
    e_ecc_ded_err_found,
    e_ecc_addr_err_found,
    e_ocmc_addr_out_of_range,
    e_cbuf_virt_addr_err,
    e_cbuf_wr_out_of_range,
    e_cbuf_wr_vbuf_start_err,
    e_cbuf_wr_addr_seq_err,
    e_cbuf_rd_out_of_range,
    e_cbuf_rd_vbuf_start_err,
    e_cbuf_rd_addr_seq_err,
    e_cbuf_overflow_mid_found,
    e_cbuf_overflow_wrap_found,
    e_cbuf_underflow,
    e_cbuf_short_frame_detect
} ocmc_intr_id_t;

/**
 * \struct vbuf_setup_raw_auto_addr_t
 * \brief  Structure used to setup the parameters for a VBUF configuration with
 *         auto address-generation
 * \details
 *
 * vbuf_size  16-byte aligned VBUF size in bytes
 *
 * cbuf_size  16-byte aligned CBUF size in bytes
 */
typedef struct {
    uint32_t vbuf_size;
    uint32_t cbuf_size;
} vbuf_setup_raw_auto_addr_t;

/**
 * \struct vbuf_setup_raw_t
 * \brief  Structure used to setup the parameters for a VBUF configuration
 * \details
 * vbuf_start 32-bit L3 address for VBUF (16 byte aligned)
 *
 * cbuf_start 32-bit L3 address for CBUF (16 byte aligned)
 *
 * vbuf_size  16-byte aligned VBUF size in bytes
 *
 * cbuf_size  16-byte aligned CBUF size in bytes
 */
typedef struct {
    ocmc_addr_t vbuf_start;
    uint32_t    vbuf_size;
    ocmc_addr_t cbuf_start;
    uint32_t    cbuf_size;
} vbuf_setup_raw_t;

/**
 * \struct vbuf_setup_image_params_t
 * \brief  Structure used to setup a VBUF configuration using Image parameters
 * \details
 * vbuf_start 32-bit L3 address for VBUF (16 byte aligned)
 *
 * image_width Width of image in pixels
 *
 * image_height Height of image in pixels
 *
 * bytes_per_pixel Number of bytes per pixel
 *
 * cbuf_start 32-bit L3 address for CBUF (16 byte aligned)
 *
 * lines_per_slice Number of lines making up a slice for algorithm prcessing ("N
 * Lines" for N-lines interrupt)
 *
 * num_slices Number of slices that make a CBUF
 */
typedef struct {
    ocmc_addr_t vbuf_start;
    uint32_t    image_width;
    uint32_t    image_height;
    uint32_t    bytes_per_pixel;
    ocmc_addr_t cbuf_start;
    uint32_t    lines_per_slice;
    uint32_t    num_slices;
} vbuf_setup_image_params_t;

/**
 * \struct vbuf_setup_image_params_auto_addr_t
 * \brief  Structure used to setup a VBUF configuration using Image parameters
 *         with auto address generation
 * \details
 * image_width Width of image in pixels
 *
 * image_height Height of image in pixels
 *
 * bytes_per_pixel Number of bytes per pixel
 *
 * lines_per_slice Number of lines making up a slice for algorithm prcessing ("N
 * Lines" for N-lines interrupt)
 *
 * num_slices Number of slices that make a CBUF
 */
typedef struct {
    uint32_t image_width;
    uint32_t image_height;
    uint32_t bytes_per_pixel;
    uint32_t lines_per_slice;
    uint32_t num_slices;
} vbuf_setup_image_params_auto_addr_t;

/*! \brief Query the chip for how many OCMC instances are on the chip.
 * \returns number of OCMC IP instances available on the chip
 * \details Implementation Notes: the API is to be implemented by querying the
 *          chip's SW_ID register
 */
ocmc_inst_t OCMC_GetNumOCMC(void);

/*! \brief Query where GP memory starts and what the GP memory size is.
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[out] gp_mem_base General Purpose memory start address
 * \param[out] gp_mem_size General Purpose memory size in bytes
 * \returns Error if instance id is invalid, success otherwise
 * \details
 * Implementation: Algorithm works by scanning through CBUF_n_START_ADDR and
 *                 CBUF_n_SIZE registers and records the highes start address
 *                 and associated size it finds.
 *
 * GP memory is expected to begin from afterwards.
 *
 * Usage: API is expected to be called after CBUFs have been configured
 *
 */
ocmc_ret_type_t OCMC_Get_GP_MemoryBaseAndSize(uint32_t     baseAddr,
                                              ocmc_addr_t *gp_mem_base,
                                              uint32_t    *gp_mem_size);

/*! \brief API to set up a VBUF using VBUF and CBUF physical addresses
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] vbuf_setup_raw Pointer to vbuf_setup_raw_t structure.
 * \returns Error code
 */
ocmc_ret_type_t OCMC_Setup_VBUF(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                                const vbuf_setup_raw_t *vbuf_setup_raw);

/*! \brief API to set up a VBUF using auto-generated virtual frame and CBUF
 * addresses
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] vbuf_setup_raw_auto_addr Pointer to vbuf_setup_raw_auto_addr_t
 *            structure.
 * \returns Error code
 */
ocmc_ret_type_t OCMC_Setup_VBUF_Address_Auto(
    uint32_t baseAddr, ocmc_buf_id_t buf_id,
    const vbuf_setup_raw_auto_addr_t *vbuf_setup_raw_auto_addr);

/*! \brief API to set up a VBUF using Image Parameters.
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] vbuf_setup_image Pointer to vbuf_setup_image_params_t structure.
 * \returns Error code
 */
ocmc_ret_type_t OCMC_Setup_VBUF_With_Image_Params(
    uint32_t baseAddr, ocmc_buf_id_t buf_id,
    const vbuf_setup_image_params_t *vbuf_setup_image);

/*! \brief API to set up a VBUF using Image Parameters With Automatic VBUF Start
 * Address Selection
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[in] vbuf_setup_image_auto_addr Pointer to
 *            vbuf_setup_image_params_auto_addr_t structure.
 * \returns Error code
 * \details Implementation Notes: This assumes that the VBUF programming is done
 *          sequentially starting with VBUF0 onwards.
 * VBUF0 is allocated at the start of the virtual frame region. VBUF1 is
 * allocated adjacent to the end of VBUF0, and so on.
 */
ocmc_ret_type_t OCMC_Setup_VBUF_With_Image_Params_Address_Auto(
    uint32_t baseAddr, ocmc_buf_id_t buf_id,
    const vbuf_setup_image_params_auto_addr_t *vbuf_setup_image_auto_addr);

/*! \brief API to read a specified VBUF's programmed parameters
 * \param[in] baseAddr OCMC Instance baseAddr
 * \param[in] buf_id Buffer Id
 * \param[out] vbuf_setup_raw Pointer to a vbuf_setup_raw_t structure.
 * \returns Error code
 */
ocmc_ret_type_t OCMC_Get_VBUF_Params(uint32_t baseAddr, ocmc_buf_id_t buf_id,
                                     vbuf_setup_raw_t *vbuf_setup_raw);

/*! \brief CBUF Memory Heap Initialization.
 * \returns Success if CBUF Heap was created, error otherwise
 * \param[in]  ocmc_inst_id OCMC instance number
 * \details    This function enables global CBUF mode
 */
ocmc_ret_type_t OCMC_CBUF_Heap_Init(ocmc_inst_t ocmc_inst_id);

/*! \brief Allocate CBUF Memory.
 * \param[in]  ocmc_inst_id OCMC instance number
 * \param[in]  vbuf_setup_image_auto_addr Pointer to structure containing image
 * params
 * \param[out] err Returns error or success code
 * \returns    OCMC Address if successful, Null in case of error
 * \details    Implementation Notes: this API uses underlying OCMC HAL API
 * "OCMC_Setup_VBUF_With_Image_Params_Address_Auto" to
 * program the next free buffer in one of the available OCMC instances.
 */
void *OCMC_CBUF_Heap_Alloc(
    ocmc_inst_t                                ocmc_inst_id,
    const vbuf_setup_image_params_auto_addr_t *vbuf_setup_image_auto_addr,
    ocmc_ret_type_t                           *err);

/*! \brief Free CBUF Memory.
 * \param[in]  ocmc_inst_id OCMC instance number
 * \param[in]  addr Memory address to be freed from OCMC CBUF
 * \returns    Success if CBUF memory was successfully freed, error otherwise
 * \details    Memory can be freed up in any order, however the usage of the
 *             overall Alloc/Free pair is expected to occur just once.
 *             ie, a bunch of Alloc calls occurring during the beginning of the
 *             program execution, and a bunch of Free calls occur in the end.
 */
ocmc_ret_type_t OCMC_CBUF_Heap_Free(ocmc_inst_t ocmc_inst_id, const void *addr);

/*! \brief Deinitialize CBUF memory.
 * \param[in]  ocmc_inst_id OCMC instance number
 * \returns    Success if CBUF memory was successfully de-initialized, error
 *             otherwise
 * \details    This function disables global CBUF mode
 */
ocmc_ret_type_t OCMC_CBUF_Deinit(ocmc_inst_t ocmc_inst_id);

/** \brief API to convert error code to string
 * \param[in] err Error code as an enumerated value
 * \returns String description of numeric error code
 */
char *OCMC_Get_Error_String(ocmc_ret_type_t err);

/** \brief API gets OCMC instance base address for the OCMC instance number
 * passed
 * \param[in] ocmc_inst OCMC instance number
 * \returns   OCMC instance base address
 */
uint32_t OCMC_Inst_AddrGet(ocmc_inst_t ocmc_inst);

/** \brief API gets number of circular buffer supported
 *
 * \returns  Total number of circular buffer supported
 */
ocmc_buf_id_t OCMC_GetNumCBUF(void);

#ifdef __cplusplus
}
#endif

#endif
 /** @} */
