#ifndef _TI_vcop_FilterPoly_kernel_h_
#define _TI_vcop_FilterPoly_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_FilterPoly_ushort_short_ushort[38];

/* Basic Runner Function */
void vcop_FilterPoly_ushort_short_ushort(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint8 smpl_flag,
   __vptr_uint16 inter_out,
   __vptr_uint8 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int h_out,
   int D,
   int U,
   int loop_end,
   int rnd_shift);
/* Custom Runner Function */
void vcop_FilterPoly_ushort_short_ushort_custom(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint8 smpl_flag,
   __vptr_uint16 inter_out,
   __vptr_uint8 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int h_out,
   int D,
   int U,
   int loop_end,
   int rnd_shift,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_FilterPoly_ushort_short_ushort_init(
   __vptr_uint16 in,
   __vptr_int16 f_coef,
   __vptr_uint8 smpl_flag,
   __vptr_uint16 inter_out,
   __vptr_uint8 out,
   int w_input,
   int ntaps,
   int w_compute,
   int h_compute,
   int w_out,
   int h_out,
   int D,
   int U,
   int loop_end,
   int rnd_shift,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_FilterPoly_ushort_short_ushort_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_FilterPoly_ushort_short_ushort ((unsigned int)38)
unsigned int vcop_FilterPoly_ushort_short_ushort_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_FilterPoly_ushort_short_ushort ((unsigned int)0)
unsigned int vcop_FilterPoly_ushort_short_ushort_ctrl_count(void);

/***********************************************************/
#endif

