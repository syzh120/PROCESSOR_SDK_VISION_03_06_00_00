#ifndef _TI_vcop_hog_vector_kernel_h_
#define _TI_vcop_hog_vector_kernel_h_

/* Parameter Register Block */
extern unsigned short __pblock_vcop_ti_pd_hog_computation[32];

/* Basic Runner Function */
void vcop_ti_pd_hog_computation(
   __vptr_uint16 pIn,
   unsigned short cb_offset1,
   unsigned short cb_offset2,
   __vptr_uint16 ptemp16,
   __vptr_uint32 ptemp32,
   __vptr_uint32 pOut,
   unsigned short pitch,
   unsigned short width,
   unsigned short height);
/* Custom Runner Function */
void vcop_ti_pd_hog_computation_custom(
   __vptr_uint16 pIn,
   unsigned short cb_offset1,
   unsigned short cb_offset2,
   __vptr_uint16 ptemp16,
   __vptr_uint32 ptemp32,
   __vptr_uint32 pOut,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_ti_pd_hog_computation_init(
   __vptr_uint16 pIn,
   unsigned short cb_offset1,
   unsigned short cb_offset2,
   __vptr_uint16 ptemp16,
   __vptr_uint32 ptemp32,
   __vptr_uint32 pOut,
   unsigned short pitch,
   unsigned short width,
   unsigned short height,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_ti_pd_hog_computation_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_ti_pd_hog_computation ((unsigned int)32)
unsigned int vcop_ti_pd_hog_computation_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_ti_pd_hog_computation ((unsigned int)0)
unsigned int vcop_ti_pd_hog_computation_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_ti_pd_2x2_sum[28];

/* Basic Runner Function */
void vcop_ti_pd_2x2_sum(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   unsigned short width,
   unsigned short height,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_ti_pd_2x2_sum_custom(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_ti_pd_2x2_sum_init(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   __vptr_uint16 pOut2,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_ti_pd_2x2_sum_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_ti_pd_2x2_sum ((unsigned int)28)
unsigned int vcop_ti_pd_2x2_sum_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_ti_pd_2x2_sum ((unsigned int)0)
unsigned int vcop_ti_pd_2x2_sum_ctrl_count(void);

/***********************************************************/
/* Parameter Register Block */
extern unsigned short __pblock_vcop_ti_pd_2x2_sum_planar[28];

/* Basic Runner Function */
void vcop_ti_pd_2x2_sum_planar(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   unsigned short width,
   unsigned short height,
   unsigned short pitch);
/* Custom Runner Function */
void vcop_ti_pd_2x2_sum_planar_custom(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* Parameter Block Initialization Function */
unsigned int vcop_ti_pd_2x2_sum_planar_init(
   __vptr_uint16 pIn,
   __vptr_uint16 pOut1,
   unsigned short width,
   unsigned short height,
   unsigned short pitch,
   unsigned short pblock[]);

/* VCOP VLOOP Execution Function */
void vcop_ti_pd_2x2_sum_planar_vloops(
   unsigned short pblock[]);

/* Parameter Register Count */
#define PARAM_SIZE_vcop_ti_pd_2x2_sum_planar ((unsigned int)28)
unsigned int vcop_ti_pd_2x2_sum_planar_param_count(void);
/* Internal Value Count */
#define CTRL_SIZE_vcop_ti_pd_2x2_sum_planar ((unsigned int)0)
unsigned int vcop_ti_pd_2x2_sum_planar_ctrl_count(void);

/***********************************************************/
#endif

