/*****************************************************************************/
/*  IVAHD.H v1.0.7                                                           */
/*                                                                           */
/* Copyright (c) 2010-2015 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

#include <arp32.h>
#include <limits.h>

#define __CONST_UCHAR   __CONST(0, UCHAR_MAX)
#define __CONST_USHRT   __CONST(0, USHRT_MAX)
#define __CONST_UINT    __CONST(0, UINT_MAX)

#if defined(__ARP32_ICONT5__)
/*---------------------------------------------------------------------------*/
/* ARP32 ICONT5 Intrinsics                                                   */
/*---------------------------------------------------------------------------*/
void         __BUILTIN_M _wait_for_event(__CONST_UCHAR unsigned char,
                                         __CONST_UCHAR unsigned char);

void         __BUILTIN_M _BSTRM_Config(__CONST(0,1) unsigned char);
void         __BUILTIN_M _BSTRM_Search_SC(void);
void         __BUILTIN_M _BSTRM_Search_NZ(void);
unsigned int __BUILTIN_M _BSTRM_Show_Bits(unsigned int);
unsigned int __BUILTIN_M _BSTRM_Read_Bits(unsigned int);
void         __BUILTIN_M _BSTRM_Flush_Bits(unsigned int);
void         __BUILTIN_M _BSTRM_Write_SC(void);
void         __BUILTIN_M _BSTRM_Write_Bits(    __CONST(1, 32) unsigned char,
                                                              unsigned int);
void         __BUILTIN_M _BSTRM_Write_Constant(__CONST(1, 32) unsigned char,
                                                              unsigned int);
void         __BUILTIN_M _BSTRM_Write_RBSP(void);
         int __BUILTIN_M _BSTRM_Read_SGlmb(void);
unsigned int __BUILTIN_M _BSTRM_Read_UGlmb(void);
void         __BUILTIN_M _BSTRM_Write_SGlmb(unsigned int);
void         __BUILTIN_M _BSTRM_Write_UGlmb(unsigned int);
void         __BUILTIN_M _BSTRM_Store(__CONST(0,1) unsigned char);

unsigned int __BUILTIN_M _RC_Read_Min0(void);
unsigned int __BUILTIN_M _RC_Read_Min1(void);
unsigned int __BUILTIN_M _RC_Read_Max0(void);
unsigned int __BUILTIN_M _RC_Read_Max1(void);

void         __BUILTIN_M _RC_Write_Min0(unsigned int);
void         __BUILTIN_M _RC_Write_Min1(unsigned int);
void         __BUILTIN_M _RC_Write_Max0(unsigned int);
void         __BUILTIN_M _RC_Write_Max1(unsigned int);

unsigned int __BUILTIN_M _RC_uClip(             unsigned int,
                                   __CONST(0,3) unsigned char,
                                   __CONST(0,3) unsigned char);
         int __BUILTIN_M _RC_sClip(                      int,
                                   __CONST(0,3) unsigned char,
                                   __CONST(0,3) unsigned char);

   long long __BUILTIN_M _RC_MulShift(int, int);
         int __BUILTIN_M _RC_GetProduct(long long);
unsigned int __BUILTIN_M _RC_GetShiftAmt(long long);
#endif

#if defined(__ARP32_ME5__)
/*---------------------------------------------------------------------------*/
/* ARP32 IME5 Intrinsics                                                     */
/*---------------------------------------------------------------------------*/
void __BUILTIN_M _wait_for_event(__CONST_UCHAR unsigned char);
void __BUILTIN_M _copy_reg_c2c(
                    __CONST_UINT  unsigned int,     // SRC memaddr
                    __CONST(0, 4) unsigned char,    // SRC info
                    __CONST_UINT  unsigned int,     // DST memaddr
                    __CONST(0, 4) unsigned char);   // DST info
void __BUILTIN_M _copy_reg_a2c(
                                  unsigned int,     // SRC reg
                    __CONST_UINT  unsigned int,     // DST memaddr
                    __CONST(0, 4) unsigned char);   // DST info
unsigned int __BUILTIN_M _copy_reg_c2a(
                    __CONST_UINT  unsigned int,     // SRC memaddr
                    __CONST(0, 4) unsigned char);   // SRC info
void __BUILTIN_M _load_cmb(
                    __CONST(0, 3) unsigned char);   // loop_type: 2 bits
void __BUILTIN_M _search_pred(
                    __CONST(0, 7) unsigned char,    // num_pred: 3 bits
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 3) unsigned char,    // pred_buffer_index: 2 bits
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                    __CONST(0, 7) unsigned char,    // num_best: 3 bits
                    __CONST(0, 1) unsigned char,    // mvcostenable: 1 bits
                                  unsigned short,   // ho/vo: 16 bits
                    __CONST(0, 7) unsigned char,    // offcode: 3 bits
                    __CONST(0, 7) unsigned char);   // pred_start_index: 3 bits
void __BUILTIN_M _load_lsrb(
                    __CONST(0, 1) unsigned char,    // ref_buf: 1 bits
                    __CONST(0, 1) unsigned char,    // reference_mv_src: 1 bits
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                                  unsigned short,   // ho/vo: 16 bits
                    __CONST(0, 7) unsigned char,    // offcode: 3 bits
                    __CONST(0,63) unsigned char,    // height1: 6 bits
                    __CONST(0,63) unsigned char,    // width1: 6 bits
                    __CONST(0, 2) unsigned char);   // search_type: 2 bits
void __BUILTIN_M _search_421(
                    __CONST(0, 1) unsigned char,    // ref_buf: 1 bits
                    __CONST(0, 1) unsigned char,    // srch_mode1: 1 bits
                                  unsigned short,   // {address/search_centre}
                    __CONST(0, 7) unsigned char,    // num_best: 3 bits
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                    __CONST(0, 1) unsigned char);   // mvcostenable: 1 bits
void __BUILTIN_M _copy_bmt_pse_2_vse(
                    __CONST(0, 1) unsigned char,    // reset: 1 bits
                    __CONST(0, 1) unsigned char,    // nine_parts: 1 bits
                    __CONST(0, 1) unsigned char);   // nb_16x16: 1 bits
void __BUILTIN_M _copy_bmt_vse_2_subpel(
                    __CONST(0, 1) unsigned char);   // reset: 1 bits
void __BUILTIN_M _reset_bmt_all(
                    __CONST(0, 3) unsigned char);   // rfpb_index: 2 bits
void __BUILTIN_M _reset_pse_bmt(
                    __CONST(0, 3) unsigned char);   // rfpb_index: 2 bits
void __BUILTIN_M _reset_pse_bmt_shadow(void);
void __BUILTIN_M _reset_vse_bmt(void);
void __BUILTIN_M _reset_subpel_bmt(void);
void __BUILTIN_M _reset_main_bmt(void);
void __BUILTIN_M _reset_sse(void);
void __BUILTIN_M _update_main_bmt(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 1) unsigned char,    // enable_refidcost: 1 bits
                    __CONST(0, 1) unsigned char,    // cost_mode: 1 bits
                    __CONST(0, 1) unsigned char);   // bipred: 1 bits
void __BUILTIN_M _search_hpel(
                    __CONST(0, 1) unsigned char,    // cost_mode: 1 bits
                    __CONST(0, 1) unsigned char,    // ref_buf: 1 bits
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                    __CONST(0, 1) unsigned char,    // mvcostenable: 1 bits
                    __CONST(0, 1) unsigned char,    // write_hpel: 1 bits
                    __CONST(0, 3) unsigned char,    // srch_mode2: 2 bits
                    __CONST(0, 1) unsigned char);   // cp_vse_bmt: 1 bits
void __BUILTIN_M _search_qpel(
                    __CONST(0, 1) unsigned char,    // cost_mode: 1 bits
                    __CONST(0, 1) unsigned char,    // ref_buf: 1 bits
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                    __CONST(0, 1) unsigned char,    // mvcostenable: 1 bits
                    __CONST(0, 1) unsigned char,    // srch_mode1: 1 bits
                    __CONST(0, 1) unsigned char);   // update_stat: 1 bits
void __BUILTIN_M _search_9pt_ls_with_offset(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 3) unsigned char,    // pred_buffer_index: 2 bits
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                                  unsigned short,   // ho/vo: 16 bits
                    __CONST(0, 7) unsigned char,    // offcode: 3 bits
                    __CONST(0,31) unsigned char,    // step_size: 5 bits
                    __CONST(0, 7) unsigned char,    // num_best: 3 bits
                    __CONST(0, 7) unsigned char);   // pred_start_index: 3 bits
void __BUILTIN_M _search_9_points(
                    __CONST(0, 3) unsigned char,    // step_size: 2 bits
                    __CONST(0, 1) unsigned char,    // ref_buf: 1 bits
                    __CONST(0, 1) unsigned char,    // srch_mode1: 1 bits
                                  unsigned short,   // {address/search_centre}
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                    __CONST(0, 7) unsigned char,    // num_best: 3 bits
                    __CONST(0, 1) unsigned char);   // mvcostenable: 1 bits
void __BUILTIN_M _compare_mode(
                    __CONST(0, 1) unsigned char,    // enable_skip: 1 bits
                    __CONST(0, 1) unsigned char,    // enable_direct8x8: 1 bits
                    __CONST(0, 1) unsigned char,    // enable_intra: 1 bits
                    __CONST(0, 1) unsigned char,    // bmt_source: 1 bits
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 1) unsigned char,    // enable_refidcost: 1 bits
                    __CONST(0, 1) unsigned char,    // cost_mode: 1 bits
                    __CONST(0, 1) unsigned char,    // bipred: 1 bits
                    __CONST(0, 1) unsigned char);   // store_left_mvp_info: 1 bit
void __BUILTIN_M _match_zero_load_skip_buffer(
                    __CONST(0, 7) unsigned char,    // num_best: 3 bits
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                    __CONST(0, 1) unsigned char,    // ignore_refindex: 1 bits
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 1) unsigned char,    // mvcostenable: 1 bits
                    __CONST(0, 1) unsigned char);   // match_zero: 1 bits
void __BUILTIN_M _load_skip_buffer(
                    __CONST(0, 1) unsigned char,    // ignore_refindex: 1 bits
                    __CONST(0, 3) unsigned char);   // rfpb_index: 2 bits
void __BUILTIN_M _calculate_skip_sad(
                    __CONST(0, 1) unsigned char,    // cost_mode: 1 bits
                    __CONST(0, 1) unsigned char,    // base_mode: 1 bits
                    __CONST(0, 1) unsigned char);   // res_pred: 1 bits
void __BUILTIN_M _store_skip_buffer(void);
void __BUILTIN_M _calculate_winner_qpel_image(
                    __CONST(0, 1) unsigned char,    // cost_mode: 1 bits
                    __CONST(0, 1) unsigned char,    // ref_buf: 1 bits
                    __CONST(0,15) unsigned char,    // mvtype_index: 4 bits
                    __CONST(0, 1) unsigned char,    // mvcostenable: 1 bits
                    __CONST(0, 1) unsigned char,    // find_bipred_cost: 1 bits
                    __CONST(0, 1) unsigned char);   // store_mean_to_intrb: 1 bit
void __BUILTIN_M _load_cfpb(void);
void __BUILTIN_M _load_rfpb(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0,31) unsigned char);   // sl2_offset: 5 bits
void __BUILTIN_M _load_mvp_info(void);
void __BUILTIN_M _load_top_spatial_predictor(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 7) unsigned char,    // x_off3: 3 bits
                    __CONST(0, 1) unsigned char,    // y_off1: 1 bits
                    __CONST(0, 3) unsigned char,    // pred_buffer_index: 2 bits
                    __CONST(0, 7) unsigned char);   // pred_index: 3 bits
void __BUILTIN_M _load_left_spatial_predictor(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 3) unsigned char,    // x_off2: 2 bits
                    __CONST(0, 3) unsigned char,    // pred_buffer_index: 2 bits
                    __CONST(0, 7) unsigned char);   // pred_index: 3 bits
void __BUILTIN_M _load_temporal_predictor(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 7) unsigned char,    // x_off3: 3 bits
                    __CONST(0, 7) unsigned char,    // y_off3: 3 bits
                    __CONST(0, 3) unsigned char,    // pred_buffer_index: 2 bits
                    __CONST(0, 7) unsigned char);   // pred_index: 3 bits
void __BUILTIN_M _get_median_predictor_mv(
                    __CONST(0, 3) unsigned char,    // pred_buffer_index: 2 bits
                    __CONST(0, 7) unsigned char,    // pred_index1: 3 bits
                    __CONST(0, 7) unsigned char,    // pred_index2: 3 bits
                    __CONST(0, 7) unsigned char,    // pred_index3: 3 bits
                    __CONST(0, 7) unsigned char);   // pred_index4: 3 bits
void __BUILTIN_M _load_zflag(void);
void __BUILTIN_M _load_mbinfo(void);
void __BUILTIN_M _write_output(void);
void __BUILTIN_M _store_buffer_to_sl2(
                    __CONST(0, 3) unsigned char,    // buffer_name: 2 bits
                                  unsigned int);    // sl2_address: 32 bits
void __BUILTIN_M _store_lsrb_to_sl2(
                    __CONST(0, 1) unsigned char,    // ref_buf: 1 bits
                                  unsigned int,     // sl2_address: 32 bits
                    __CONST(0,15) unsigned char,    // start_x: 4 bits
                    __CONST(0,15) unsigned char,    // x_stride: 4 bits
                    __CONST(0, 7) unsigned char,    // width2: 3 bits
                    __CONST(0,15) unsigned char);   // height2: 4 bits
void __BUILTIN_M _calculate_mvcost_params(
                    __CONST(0, 3) unsigned char);   // rfpb_index: 2 bits
void __BUILTIN_M _calculate_skip_mv(void);
void __BUILTIN_M _calculate_effective_search_range(
                    __CONST(0, 3) unsigned char);   // rfpb_index: 2 bits
void __BUILTIN_M _store_pred_out(
                    __CONST(0, 3) unsigned char,    // bmt_src: 2 bits
                    __CONST(0, 3) unsigned char);   // rfpb_index: 2 bits
void __BUILTIN_M _update_bbox(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 4) unsigned char,    // pred_type: 3 bits
                    __CONST(0, 7) unsigned char,    // x_off3: 3 bits
                    __CONST(0, 7) unsigned char,    // y_off3: 3 bits
                    __CONST(0, 3) unsigned char,    // pred_buffer_index: 2 bits
                    __CONST(0, 7) unsigned char,    // pred_index: 3 bits
                    __CONST(0, 1) unsigned char);   // last_predictor: 1 bit
void __BUILTIN_M _get_forceintra_flag(void);
void __BUILTIN_M _copy_bmt_pse_2_pse_shadow(
                    __CONST(0, 1) unsigned char);   // reset: 1 bits
void __BUILTIN_M _copy_bmt_pse_shadow_2_vse(
                    __CONST(0, 1) unsigned char,    // reset: 1 bits
                    __CONST(0, 1) unsigned char,    // nine_parts: 1 bits
                    __CONST(0, 1) unsigned char);   // nb_16x16: 1 bits
void __BUILTIN_M _calculate_mvcost_vse_bmt(
                    __CONST(0, 3) unsigned char);   // rfpb_index: 2 bits
void __BUILTIN_M _end_MBloop(
                    __CONST(0, 3) unsigned char);   // loop_type: 2 bits
void __BUILTIN_M _end_pft_loop(void);
void __BUILTIN_M _load_cs_rs(
                    __CONST(0, 1) unsigned char);   // RSnCS: 1 bits
void __BUILTIN_M _load_bl_mbinfo(void);
void __BUILTIN_M _load_skip_buffer_bm(
                    __CONST(0, 4) unsigned char,    // partition_type: 3 bits
                    __CONST(0, 1) unsigned char);   // direction: 2 bits
void __BUILTIN_M _calculate_mvcost_pse_bmt(
                    __CONST(0, 3) unsigned char,    // rfpb_index: 2 bits
                    __CONST(0, 1) unsigned char);   // shadow: 1 bits

#endif

#ifdef __cplusplus
}
#endif
