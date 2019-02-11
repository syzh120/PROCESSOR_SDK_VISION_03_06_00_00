#ifndef _TI_vcop_block_statistics_kernel_h_
#define _TI_vcop_block_statistics_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_block_statistics[70];

/* Basic Runner Function */
void vcop_block_statistics(
   __vptr_uint8 im_A,
   unsigned short blockStride,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short statBlockWidth,
   unsigned short statBlockHeight,
   __vptr_uint8 scratch_C,
   __vptr_uint16 scratchSum_A,
   __vptr_uint32 scratchSumSq_B,
   __vptr_uint32 scratchSumSq_C,
   __vptr_uint16 scratchSumSq_C_lo,
   __vptr_uint16 scratchSumSq_C_hi,
   __vptr_uint8 min_B,
   __vptr_uint8 max_B,
   __vptr_uint16 mean_B,
   __vptr_uint32 variance_A);
/* Custom Runner Function */
void vcop_block_statistics_custom(
   __vptr_uint8 im_A,
   unsigned short blockStride,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short statBlockWidth,
   unsigned short statBlockHeight,
   __vptr_uint8 scratch_C,
   __vptr_uint16 scratchSum_A,
   __vptr_uint32 scratchSumSq_B,
   __vptr_uint32 scratchSumSq_C,
   __vptr_uint16 scratchSumSq_C_lo,
   __vptr_uint16 scratchSumSq_C_hi,
   __vptr_uint8 min_B,
   __vptr_uint8 max_B,
   __vptr_uint16 mean_B,
   __vptr_uint32 variance_A,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_block_statistics_init(
   __vptr_uint8 im_A,
   unsigned short blockStride,
   unsigned short blockWidth,
   unsigned short blockHeight,
   unsigned short statBlockWidth,
   unsigned short statBlockHeight,
   __vptr_uint8 scratch_C,
   __vptr_uint16 scratchSum_A,
   __vptr_uint32 scratchSumSq_B,
   __vptr_uint32 scratchSumSq_C,
   __vptr_uint16 scratchSumSq_C_lo,
   __vptr_uint16 scratchSumSq_C_hi,
   __vptr_uint8 min_B,
   __vptr_uint8 max_B,
   __vptr_uint16 mean_B,
   __vptr_uint32 variance_A,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_block_statistics_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_block_statistics ((unsigned int)70)
unsigned int vcop_block_statistics_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_block_statistics ((unsigned int)0)
unsigned int vcop_block_statistics_ctrl_count(void);

/***********************************************************/
#endif

