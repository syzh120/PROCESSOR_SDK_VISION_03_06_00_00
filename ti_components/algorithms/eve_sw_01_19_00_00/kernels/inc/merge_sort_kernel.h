#ifndef _TI_merge_sort_kernel_h_
#define _TI_merge_sort_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_sort8_simd8_64[36];

/* Basic Runner Function */
void vcop_sort8_simd8_64(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out);
/* Custom Runner Function */
void vcop_sort8_simd8_64_custom(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sort8_simd8_64_init(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sort8_simd8_64_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sort8_simd8_64 ((unsigned int)36)
unsigned int vcop_sort8_simd8_64_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sort8_simd8_64 ((unsigned int)0)
unsigned int vcop_sort8_simd8_64_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_sort8_simd8_XX[38];

/* Basic Runner Function */
void vcop_sort8_simd8_XX(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out);
/* Custom Runner Function */
void vcop_sort8_simd8_XX_custom(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_sort8_simd8_XX_init(
   int niter,
   int out_tr,
   __vptr_uint32 in,
   __vptr_uint32 out,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_sort8_simd8_XX_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_sort8_simd8_XX ((unsigned int)38)
unsigned int vcop_sort8_simd8_XX_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_sort8_simd8_XX ((unsigned int)0)
unsigned int vcop_sort8_simd8_XX_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_psort2_1step_reverse_kernel[28];

/* Basic Runner Function */
void vcop_psort2_1step_reverse_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst);
/* Custom Runner Function */
void vcop_psort2_1step_reverse_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_psort2_1step_reverse_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_psort2_1step_reverse_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_psort2_1step_reverse_kernel ((unsigned int)28)
unsigned int vcop_psort2_1step_reverse_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_psort2_1step_reverse_kernel ((unsigned int)0)
unsigned int vcop_psort2_1step_reverse_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_psort2_1step_kernel[26];

/* Basic Runner Function */
void vcop_psort2_1step_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst);
/* Custom Runner Function */
void vcop_psort2_1step_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_psort2_1step_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_psort2_1step_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_psort2_1step_kernel ((unsigned int)26)
unsigned int vcop_psort2_1step_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_psort2_1step_kernel ((unsigned int)0)
unsigned int vcop_psort2_1step_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_psort2_2steps_reverse_kernel[36];

/* Basic Runner Function */
void vcop_psort2_2steps_reverse_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst);
/* Custom Runner Function */
void vcop_psort2_2steps_reverse_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_psort2_2steps_reverse_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_psort2_2steps_reverse_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_psort2_2steps_reverse_kernel ((unsigned int)36)
unsigned int vcop_psort2_2steps_reverse_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_psort2_2steps_reverse_kernel ((unsigned int)0)
unsigned int vcop_psort2_2steps_reverse_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_psort2_2steps_kernel[34];

/* Basic Runner Function */
void vcop_psort2_2steps_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst);
/* Custom Runner Function */
void vcop_psort2_2steps_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_psort2_2steps_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_psort2_2steps_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_psort2_2steps_kernel ((unsigned int)34)
unsigned int vcop_psort2_2steps_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_psort2_2steps_kernel ((unsigned int)0)
unsigned int vcop_psort2_2steps_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_psort2_3steps_reverse_kernel[54];

/* Basic Runner Function */
void vcop_psort2_3steps_reverse_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst);
/* Custom Runner Function */
void vcop_psort2_3steps_reverse_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_psort2_3steps_reverse_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_psort2_3steps_reverse_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_psort2_3steps_reverse_kernel ((unsigned int)54)
unsigned int vcop_psort2_3steps_reverse_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_psort2_3steps_reverse_kernel ((unsigned int)0)
unsigned int vcop_psort2_3steps_reverse_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_psort2_3steps_kernel[52];

/* Basic Runner Function */
void vcop_psort2_3steps_kernel(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst);
/* Custom Runner Function */
void vcop_psort2_3steps_kernel_custom(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_psort2_3steps_kernel_init(
   int niter1,
   int niter2,
   int niter3,
   int ibase_0,
   int ibase_1,
   int ibase_2,
   int ibase_3,
   int ibase_4,
   int ibase_5,
   int ibase_6,
   int ibase_7,
   int in1ptr_w1,
   int in1ptr_w2,
   int in1ptr_w3,
   int in2ptr_w1,
   int in2ptr_w2,
   int in2ptr_w3,
   int obase_0,
   int obase_1,
   int obase_2,
   int obase_3,
   int obase_4,
   int obase_5,
   int obase_6,
   int obase_7,
   int outptr_w1,
   int outptr_w2,
   int outptr_w3,
   __vptr_uint32 input,
   __vptr_uint32 output,
   __vptr_int32 out_ofst,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_psort2_3steps_kernel_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_psort2_3steps_kernel ((unsigned int)52)
unsigned int vcop_psort2_3steps_kernel_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_psort2_3steps_kernel ((unsigned int)0)
unsigned int vcop_psort2_3steps_kernel_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_remove_ex_col[12];

/* Basic Runner Function */
void vcop_remove_ex_col(
   __vptr_uint32 input,
   __vptr_uint32 output,
   int nitems);
/* Custom Runner Function */
void vcop_remove_ex_col_custom(
   __vptr_uint32 input,
   __vptr_uint32 output,
   int nitems,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_remove_ex_col_init(
   __vptr_uint32 input,
   __vptr_uint32 output,
   int nitems,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_remove_ex_col_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_remove_ex_col ((unsigned int)12)
unsigned int vcop_remove_ex_col_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_remove_ex_col ((unsigned int)0)
unsigned int vcop_remove_ex_col_ctrl_count(void);

/***********************************************************/
#endif

