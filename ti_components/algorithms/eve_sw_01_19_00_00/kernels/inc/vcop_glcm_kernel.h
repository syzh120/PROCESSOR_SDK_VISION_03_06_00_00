#ifndef _TI_vcop_glcm_kernel_h_
#define _TI_vcop_glcm_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_initialize_glcm[10];

/* Basic Runner Function */
void vcop_initialize_glcm(
   __vptr_uint16 in_glcm_A,
   unsigned char numLevels,
   unsigned char numCopies);
/* Custom Runner Function */
void vcop_initialize_glcm_custom(
   __vptr_uint16 in_glcm_A,
   unsigned char numLevels,
   unsigned char numCopies,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_initialize_glcm_init(
   __vptr_uint16 in_glcm_A,
   unsigned char numLevels,
   unsigned char numCopies,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_initialize_glcm_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_initialize_glcm ((unsigned int)10)
unsigned int vcop_initialize_glcm_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_initialize_glcm ((unsigned int)0)
unsigned int vcop_initialize_glcm_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_glcm_compute_1c[272];

/* Basic Runner Function */
void vcop_glcm_compute_1c(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride);
/* Custom Runner Function */
void vcop_glcm_compute_1c_custom(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_glcm_compute_1c_init(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_glcm_compute_1c_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_glcm_compute_1c ((unsigned int)272)
unsigned int vcop_glcm_compute_1c_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_glcm_compute_1c ((unsigned int)2)
unsigned int vcop_glcm_compute_1c_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_glcm_compute_8c[400];

/* Basic Runner Function */
void vcop_glcm_compute_8c(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint8 wgt_delta_A,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride);
/* Custom Runner Function */
void vcop_glcm_compute_8c_custom(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint8 wgt_delta_A,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_glcm_compute_8c_init(
   __vptr_uint8 inp_data_A,
   __vptr_uint16_arr scratch_index_B,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint8 wgt_delta_A,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned char rowStart[],
   unsigned char colStart[],
   char rowOffsets[],
   char colOffsets[],
   unsigned char numRows,
   unsigned char numCols,
   unsigned short blk_wdth,
   unsigned short blk_hght,
   unsigned short blk_stride,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_glcm_compute_8c_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_glcm_compute_8c ((unsigned int)400)
unsigned int vcop_glcm_compute_8c_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_glcm_compute_8c ((unsigned int)3)
unsigned int vcop_glcm_compute_8c_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_accumulate_8c_glcm[272];

/* Basic Runner Function */
void vcop_accumulate_8c_glcm(
   __vptr_uint16_arr in_glcm_C,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint16_arr scratch_A,
   __vptr_uint16 scatter_offsets_B,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned short scatter_offset);
/* Custom Runner Function */
void vcop_accumulate_8c_glcm_custom(
   __vptr_uint16_arr in_glcm_C,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint16_arr scratch_A,
   __vptr_uint16 scatter_offsets_B,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned short scatter_offset,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_accumulate_8c_glcm_init(
   __vptr_uint16_arr in_glcm_C,
   __vptr_uint16_arr out_glcm_C,
   __vptr_uint16_arr scratch_A,
   __vptr_uint16 scatter_offsets_B,
   unsigned char numLevels,
   unsigned char numOffsets,
   unsigned short scatter_offset,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_accumulate_8c_glcm_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_accumulate_8c_glcm ((unsigned int)272)
unsigned int vcop_accumulate_8c_glcm_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_accumulate_8c_glcm ((unsigned int)2)
unsigned int vcop_accumulate_8c_glcm_ctrl_count(void);

/***********************************************************/
#endif

