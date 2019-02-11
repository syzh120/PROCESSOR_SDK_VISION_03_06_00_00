#ifndef _TI_vcop_soft_isp_kernel_h_
#define _TI_vcop_soft_isp_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_decompand_piecewise_linear[44];

/* Basic Runner Function */
void vcop_decompand_piecewise_linear(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_B,
   __vptr_uint16 out_cc_data_A,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short p1,
   unsigned int p2,
   unsigned short pk,
   unsigned char r1,
   unsigned short r1r2,
   unsigned char shift);
/* Custom Runner Function */
void vcop_decompand_piecewise_linear_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_B,
   __vptr_uint16 out_cc_data_A,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short p1,
   unsigned int p2,
   unsigned short pk,
   unsigned char r1,
   unsigned short r1r2,
   unsigned char shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_decompand_piecewise_linear_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_B,
   __vptr_uint16 out_cc_data_A,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short p1,
   unsigned int p2,
   unsigned short pk,
   unsigned char r1,
   unsigned short r1r2,
   unsigned char shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_decompand_piecewise_linear_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_decompand_piecewise_linear ((unsigned int)44)
unsigned int vcop_decompand_piecewise_linear_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_decompand_piecewise_linear ((unsigned int)0)
unsigned int vcop_decompand_piecewise_linear_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_black_clamp_c_balance[34];

/* Basic Runner Function */
void vcop_black_clamp_c_balance(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_A,
   __vptr_uint16 out_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short blackClamp[],
   unsigned short cBalanceGain[],
   unsigned char shift);
/* Custom Runner Function */
void vcop_black_clamp_c_balance_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_A,
   __vptr_uint16 out_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short blackClamp[],
   unsigned short cBalanceGain[],
   unsigned char shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_black_clamp_c_balance_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint16 out_rc_data_A,
   __vptr_uint16 out_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned short out_stride,
   unsigned short blackClamp[],
   unsigned short cBalanceGain[],
   unsigned char shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_black_clamp_c_balance_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_black_clamp_c_balance ((unsigned int)34)
unsigned int vcop_black_clamp_c_balance_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_black_clamp_c_balance ((unsigned int)0)
unsigned int vcop_black_clamp_c_balance_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_soft_isp_extract_r[14];

/* Basic Runner Function */
void vcop_soft_isp_extract_r(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint8 out_r_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char shift);
/* Custom Runner Function */
void vcop_soft_isp_extract_r_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint8 out_r_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_soft_isp_extract_r_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint8 out_r_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_soft_isp_extract_r_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_soft_isp_extract_r ((unsigned int)14)
unsigned int vcop_soft_isp_extract_r_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_soft_isp_extract_r ((unsigned int)0)
unsigned int vcop_soft_isp_extract_r_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_stats_collector_dense[68];

/* Basic Runner Function */
void vcop_stats_collector_dense(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint32 scratch_C,
   __vptr_uint32 out_sum_pix,
   __vptr_uint16 out_cnt_unsat_pix,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char start_x,
   unsigned short saturationLimit);
/* Custom Runner Function */
void vcop_stats_collector_dense_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint32 scratch_C,
   __vptr_uint32 out_sum_pix,
   __vptr_uint16 out_cnt_unsat_pix,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char start_x,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_stats_collector_dense_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint32 scratch_C,
   __vptr_uint32 out_sum_pix,
   __vptr_uint16 out_cnt_unsat_pix,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   unsigned char start_x,
   unsigned short saturationLimit,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_stats_collector_dense_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_stats_collector_dense ((unsigned int)68)
unsigned int vcop_stats_collector_dense_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_stats_collector_dense ((unsigned int)0)
unsigned int vcop_stats_collector_dense_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_rccc_to_cccc[164];

/* Basic Runner Function */
void vcop_rccc_to_cccc(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   __vptr_uint16 sum_c1,
   __vptr_uint16 sum_c2,
   __vptr_uint16 med,
   __vptr_uint16 low,
   __vptr_uint16 high,
   __vptr_uint8 edge_flag,
   __vptr_uint8 strip_flag,
   __vptr_uint8 c1_flag,
   __vptr_uint8 c2_flag,
   __vptr_uint16 ov,
   __vptr_uint16 oh,
   __vptr_uint8 flag_vert,
   __vptr_uint8 flag_horz,
   unsigned char start_x,
   unsigned char offset_cc);
/* Custom Runner Function */
void vcop_rccc_to_cccc_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   __vptr_uint16 sum_c1,
   __vptr_uint16 sum_c2,
   __vptr_uint16 med,
   __vptr_uint16 low,
   __vptr_uint16 high,
   __vptr_uint8 edge_flag,
   __vptr_uint8 strip_flag,
   __vptr_uint8 c1_flag,
   __vptr_uint8 c2_flag,
   __vptr_uint16 ov,
   __vptr_uint16 oh,
   __vptr_uint8 flag_vert,
   __vptr_uint8 flag_horz,
   unsigned char start_x,
   unsigned char offset_cc,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_rccc_to_cccc_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   unsigned short blk_width,
   unsigned short blk_height,
   unsigned short in_stride,
   __vptr_uint16 sum_c1,
   __vptr_uint16 sum_c2,
   __vptr_uint16 med,
   __vptr_uint16 low,
   __vptr_uint16 high,
   __vptr_uint8 edge_flag,
   __vptr_uint8 strip_flag,
   __vptr_uint8 c1_flag,
   __vptr_uint8 c2_flag,
   __vptr_uint16 ov,
   __vptr_uint16 oh,
   __vptr_uint8 flag_vert,
   __vptr_uint8 flag_horz,
   unsigned char start_x,
   unsigned char offset_cc,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_rccc_to_cccc_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_rccc_to_cccc ((unsigned int)164)
unsigned int vcop_rccc_to_cccc_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_rccc_to_cccc ((unsigned int)0)
unsigned int vcop_rccc_to_cccc_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gbce_simple[32];

/* Basic Runner Function */
void vcop_gbce_simple(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   __vptr_uint8 pGbceToneCurve_C);
/* Custom Runner Function */
void vcop_gbce_simple_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gbce_simple_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gbce_simple_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gbce_simple ((unsigned int)32)
unsigned int vcop_gbce_simple_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gbce_simple ((unsigned int)0)
unsigned int vcop_gbce_simple_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_gbce_interp[72];

/* Basic Runner Function */
void vcop_gbce_interp(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 scratch_rc_out_B,
   __vptr_uint8 scratch_cc_out_A,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   unsigned short mask,
   __vptr_uint8 pGbceToneCurve_C);
/* Custom Runner Function */
void vcop_gbce_interp_custom(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 scratch_rc_out_B,
   __vptr_uint8 scratch_cc_out_A,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   unsigned short mask,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_gbce_interp_init(
   __vptr_uint16 inp_rc_data_A,
   __vptr_uint16 inp_cc_data_B,
   __vptr_uint8 scratch_rc_out_B,
   __vptr_uint8 scratch_cc_out_A,
   __vptr_uint8 out_rc_data_B,
   __vptr_uint8 out_cc_data_A,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short blockStride,
   unsigned char shift,
   unsigned short mask,
   __vptr_uint8 pGbceToneCurve_C,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_gbce_interp_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_gbce_interp ((unsigned int)72)
unsigned int vcop_gbce_interp_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_gbce_interp ((unsigned int)0)
unsigned int vcop_gbce_interp_ctrl_count(void);

/***********************************************************/
#endif

