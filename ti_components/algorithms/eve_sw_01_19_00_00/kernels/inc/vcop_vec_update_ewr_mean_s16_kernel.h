#ifndef _TI_vcop_vec_update_ewr_mean_s16_kernel_h_
#define _TI_vcop_vec_update_ewr_mean_s16_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_vec_update_ewr_mean_s16[24];

/* Basic Runner Function */
void vcop_vec_update_ewr_mean_s16(
   __vptr_int16 currentMean,
   __vptr_uint8 newestData,
   __vptr_uint8 foreground,
   unsigned short weight,
   unsigned short weight_neg,
   unsigned int frameSize);
/* Custom Runner Function */
void vcop_vec_update_ewr_mean_s16_custom(
   __vptr_int16 currentMean,
   __vptr_uint8 newestData,
   __vptr_uint8 foreground,
   unsigned short weight,
   unsigned short weight_neg,
   unsigned int frameSize,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_vec_update_ewr_mean_s16_init(
   __vptr_int16 currentMean,
   __vptr_uint8 newestData,
   __vptr_uint8 foreground,
   unsigned short weight,
   unsigned short weight_neg,
   unsigned int frameSize,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_vec_update_ewr_mean_s16_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_vec_update_ewr_mean_s16 ((unsigned int)24)
unsigned int vcop_vec_update_ewr_mean_s16_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_vec_update_ewr_mean_s16 ((unsigned int)0)
unsigned int vcop_vec_update_ewr_mean_s16_ctrl_count(void);

/***********************************************************/
#endif

