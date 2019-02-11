#ifndef _TI_vcop_bhattacharyaDistance_kernel_h_
#define _TI_vcop_bhattacharyaDistance_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_bhattacharyaDistance[14];

/* Basic Runner Function */
void vcop_bhattacharyaDistance(
   __vptr_int16 X_ptr,
   __vptr_int16 Y_ptr,
   unsigned short num,
   __vptr_int16 in1_ptr);
/* Custom Runner Function */
void vcop_bhattacharyaDistance_custom(
   __vptr_int16 X_ptr,
   __vptr_int16 Y_ptr,
   unsigned short num,
   __vptr_int16 in1_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_bhattacharyaDistance_init(
   __vptr_int16 X_ptr,
   __vptr_int16 Y_ptr,
   unsigned short num,
   __vptr_int16 in1_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_bhattacharyaDistance_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_bhattacharyaDistance ((unsigned int)14)
unsigned int vcop_bhattacharyaDistance_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_bhattacharyaDistance ((unsigned int)0)
unsigned int vcop_bhattacharyaDistance_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_eve_array_sqrt_intlv_lut_idx_log4[24];

/* Basic Runner Function */
void eve_array_sqrt_intlv_lut_idx_log4(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 TLU_idx_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   int TLU_Qbits_p1,
   int idx_norm2);
/* Custom Runner Function */
void eve_array_sqrt_intlv_lut_idx_log4_custom(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 TLU_idx_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   int TLU_Qbits_p1,
   int idx_norm2,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_array_sqrt_intlv_lut_idx_log4_init(
   __vptr_uint16 in1_ptr,
   __vptr_uint16 TLU_idx_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   int TLU_Qbits_p1,
   int idx_norm2,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_array_sqrt_intlv_lut_idx_log4_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_array_sqrt_intlv_lut_idx_log4 ((unsigned int)24)
unsigned int eve_array_sqrt_intlv_lut_idx_log4_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_array_sqrt_intlv_lut_idx_log4 ((unsigned int)0)
unsigned int eve_array_sqrt_intlv_lut_idx_log4_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_eve_tlu_1c_hword[12];

/* Basic Runner Function */
void eve_tlu_1c_hword(
   __vptr_uint16 Table,
   __vptr_uint16 inp_data,
   unsigned int blk_hght,
   unsigned int blk_wdth,
   __vptr_uint16 Out);
/* Custom Runner Function */
void eve_tlu_1c_hword_custom(
   __vptr_uint16 Table,
   __vptr_uint16 inp_data,
   unsigned int blk_hght,
   unsigned int blk_wdth,
   __vptr_uint16 Out,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_tlu_1c_hword_init(
   __vptr_uint16 Table,
   __vptr_uint16 inp_data,
   unsigned int blk_hght,
   unsigned int blk_wdth,
   __vptr_uint16 Out,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_tlu_1c_hword_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_tlu_1c_hword ((unsigned int)12)
unsigned int eve_tlu_1c_hword_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_tlu_1c_hword ((unsigned int)0)
unsigned int eve_tlu_1c_hword_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_eve_array_sqrt_intlv_align[14];

/* Basic Runner Function */
void eve_array_sqrt_intlv_align(
   __vptr_uint16 in1_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   __vptr_uint32 out_ptr);
/* Custom Runner Function */
void eve_array_sqrt_intlv_align_custom(
   __vptr_uint16 in1_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   __vptr_uint32 out_ptr,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int eve_array_sqrt_intlv_align_init(
   __vptr_uint16 in1_ptr,
   __vptr_uint8 log4_ptr,
   unsigned short num_data,
   __vptr_uint32 out_ptr,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void eve_array_sqrt_intlv_align_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_eve_array_sqrt_intlv_align ((unsigned int)14)
unsigned int eve_array_sqrt_intlv_align_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_eve_array_sqrt_intlv_align ((unsigned int)0)
unsigned int eve_array_sqrt_intlv_align_ctrl_count(void);

/***********************************************************/
#endif

