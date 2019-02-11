#ifndef _TI_vcop_BayerCFA_HorzUpsample_kernel_h_
#define _TI_vcop_BayerCFA_HorzUpsample_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_BayerCFA_HorzUpsample_ushort_short_ushort[24];

/* Basic Runner Function */
void vcop_BayerCFA_HorzUpsample_ushort_short_ushort(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint16 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int U,
   int type_output,
   int rnd_shift);
/* Custom Runner Function */
void vcop_BayerCFA_HorzUpsample_ushort_short_ushort_custom(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint16 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int U,
   int type_output,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_BayerCFA_HorzUpsample_ushort_short_ushort_init(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint16 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int U,
   int type_output,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_BayerCFA_HorzUpsample_ushort_short_ushort_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_BayerCFA_HorzUpsample_ushort_short_ushort ((unsigned int)24)
unsigned int vcop_BayerCFA_HorzUpsample_ushort_short_ushort_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_BayerCFA_HorzUpsample_ushort_short_ushort ((unsigned int)0)
unsigned int vcop_BayerCFA_HorzUpsample_ushort_short_ushort_ctrl_count(void);

/***********************************************************/
#endif

