#ifndef _TI_vcop_gamma_correction_kernel_h_
#define _TI_vcop_gamma_correction_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_gamma_correction[70];

/* Basic Runner Function */
void gamma_correction(
   __vptr_uint16 iPtrR_in,
   __vptr_uint16 iPtrG_in,
   __vptr_uint16 iPtrB_in,
   __vptr_uint16 iPtrR_out,
   __vptr_uint16 iPtrG_out,
   __vptr_uint16 iPtrB_out,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_uint16 tempPtrR,
   __vptr_uint16 tempPtrG,
   __vptr_uint16 tempPtrB,
   __vptr_uint16 LUT);
/* Custom Runner Function */
void gamma_correction_custom(
   __vptr_uint16 iPtrR_in,
   __vptr_uint16 iPtrG_in,
   __vptr_uint16 iPtrB_in,
   __vptr_uint16 iPtrR_out,
   __vptr_uint16 iPtrG_out,
   __vptr_uint16 iPtrB_out,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_uint16 tempPtrR,
   __vptr_uint16 tempPtrG,
   __vptr_uint16 tempPtrB,
   __vptr_uint16 LUT,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int gamma_correction_init(
   __vptr_uint16 iPtrR_in,
   __vptr_uint16 iPtrG_in,
   __vptr_uint16 iPtrB_in,
   __vptr_uint16 iPtrR_out,
   __vptr_uint16 iPtrG_out,
   __vptr_uint16 iPtrB_out,
   unsigned short blk_w,
   unsigned short blk_h,
   unsigned short input_stride,
   unsigned short output_stride,
   __vptr_uint16 tempPtrR,
   __vptr_uint16 tempPtrG,
   __vptr_uint16 tempPtrB,
   __vptr_uint16 LUT,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void gamma_correction_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_gamma_correction ((unsigned int)70)
unsigned int gamma_correction_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_gamma_correction ((unsigned int)0)
unsigned int gamma_correction_ctrl_count(void);

/***********************************************************/
#endif

