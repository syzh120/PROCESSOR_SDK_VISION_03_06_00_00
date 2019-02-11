#ifndef _TI_vcop_dct8x8col_kernel_h_
#define _TI_vcop_dct8x8col_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_dct8x8_OddEven_col_int_int[56];

/* Basic Runner Function */
void vcop_dct8x8_OddEven_col_int_int(
   __vptr_int16 in,
   __vptr_int16 f_ignore,
   __vptr_int16 out,
   int w_input,
   int h_input,
   int w_out,
   int h_out,
   int HBLKS,
   int VBLKS,
   int type_input,
   int type_coeff,
   int type_output,
   int rnd_shift);
/* Custom Runner Function */
void vcop_dct8x8_OddEven_col_int_int_custom(
   __vptr_int16 in,
   __vptr_int16 f_ignore,
   __vptr_int16 out,
   int w_input,
   int h_input,
   int w_out,
   int h_out,
   int HBLKS,
   int VBLKS,
   int type_input,
   int type_coeff,
   int type_output,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_dct8x8_OddEven_col_int_int_init(
   __vptr_int16 in,
   __vptr_int16 f_ignore,
   __vptr_int16 out,
   int w_input,
   int h_input,
   int w_out,
   int h_out,
   int HBLKS,
   int VBLKS,
   int type_input,
   int type_coeff,
   int type_output,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_dct8x8_OddEven_col_int_int_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_dct8x8_OddEven_col_int_int ((unsigned int)56)
unsigned int vcop_dct8x8_OddEven_col_int_int_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_dct8x8_OddEven_col_int_int ((unsigned int)0)
unsigned int vcop_dct8x8_OddEven_col_int_int_ctrl_count(void);

/***********************************************************/
#endif

