#ifndef _TI_vcop_yuv420_fir2d_separable_kernel_h_
#define _TI_vcop_yuv420_fir2d_separable_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_yuv420_fir2d_separable_y[38];

/* Basic Runner Function */
void vcop_yuv420_fir2d_separable_y(
   __vptr_uint8 data_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 output_ptr,
   unsigned short rnd_bits);
/* Custom Runner Function */
void vcop_yuv420_fir2d_separable_y_custom(
   __vptr_uint8 data_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 output_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_yuv420_fir2d_separable_y_init(
   __vptr_uint8 data_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 output_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_yuv420_fir2d_separable_y_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_yuv420_fir2d_separable_y ((unsigned int)38)
unsigned int vcop_yuv420_fir2d_separable_y_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_yuv420_fir2d_separable_y ((unsigned int)0)
unsigned int vcop_yuv420_fir2d_separable_y_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_yuv420_fir2d_separable_uv[38];

/* Basic Runner Function */
void vcop_yuv420_fir2d_separable_uv(
   __vptr_uint8 UVdata_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 UVout_ptr,
   unsigned short rnd_bits);
/* Custom Runner Function */
void vcop_yuv420_fir2d_separable_uv_custom(
   __vptr_uint8 UVdata_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 UVout_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_yuv420_fir2d_separable_uv_init(
   __vptr_uint8 UVdata_ptr,
   __vptr_int16 inter_ptr,
   __vptr_int8 coefh_ptr,
   __vptr_int8 coefv_ptr,
   unsigned short blkw,
   unsigned short lofst,
   unsigned short blkh,
   unsigned short num_coef,
   __vptr_uint8 UVout_ptr,
   unsigned short rnd_bits,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_yuv420_fir2d_separable_uv_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_yuv420_fir2d_separable_uv ((unsigned int)38)
unsigned int vcop_yuv420_fir2d_separable_uv_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_yuv420_fir2d_separable_uv ((unsigned int)0)
unsigned int vcop_yuv420_fir2d_separable_uv_ctrl_count(void);

/***********************************************************/
#endif

